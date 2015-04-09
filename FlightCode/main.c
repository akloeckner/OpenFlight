/*
 * main.c
 *
 *  Created on: Feb 2, 2015
 *      Author: John
 */

/*! \file main.c
 *	\brief Main function, thread 0
 *
 *	\details The main function is here, which creates and runs all threads. It also
 *	is thread 0, the highest priority thread, which runs the primary avionics software
 *	modules.
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: main.c 1006 2013-10-30 15:33:32Z brtaylor $
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

#include "globaldefs.h"
#include "utils/misc.h"

// Interfaces
#include "sensors/AirData/airdata_interface.h"
#include "sensors/daq_interface.h"
#include "actuators/actuator_interface.h"
#include "navigation/nav_interface.h"
#include "guidance/guidance_interface.h"
#include "control/control_interface.h"
#include "system_id/systemid_interface.h"
#include "faults/fault_interface.h"
#include "datalog/datalog_interface.h"
#include "telemetry/telemetry_interface.h"

// External variable definition. Declared in extern_vars.h

// End extern_vars.h

// dataLog structure. External but used only in datalogger.c
struct datalog dataLog;

// Conditional variables. These are external but only used in scheduling.c
pthread_cond_t  trigger_daq, trigger_nav, trigger_guidance, trigger_sensfault, \
trigger_control, trigger_sysid, trigger_surffault, \
trigger_actuators,  trigger_datalogger, trigger_telemetry;


/// Main function, primary avionics functions, thread 0, highest priority.
int main(int argc, char **argv) {

	// Data Structures
	struct  imu   imuData;
	struct  gps   gpsData;
	struct	insgps insgpsData;
	struct	ahrsdr ahrsdrData;
	struct  nav   navData;
	struct  control controlData;
	struct  airdata adData;
	struct  surface surfData;

	// sensor data
	struct sensordata sensorData;

	uint16_t cpuLoad;

	// Timing variables
	double etime_daq, etime_nav, etime_guidance, etime_sensfault, \
	etime_control, etime_sysid, etime_surffault, \
	etime_actuators, etime_datalog, etime_telemetry;

	// Include datalog definition
	#include DATALOG_CONFIG

	// Populate dataLog members with initial values
	dataLog.saveAsDoubleNames = &saveAsDoubleNames[0];
	dataLog.saveAsDoublePointers = &saveAsDoublePointers[0];
	dataLog.saveAsFloatNames = &saveAsFloatNames[0];
	dataLog.saveAsFloatPointers = &saveAsFloatPointers[0];
	dataLog.saveAsIntNames = &saveAsIntNames[0];
	dataLog.saveAsIntPointers = &saveAsIntPointers[0];
	dataLog.saveAsShortNames = &saveAsShortNames[0];
	dataLog.saveAsShortPointers = &saveAsShortPointers[0];
	dataLog.logArraySize = LOG_ARRAY_SIZE;
	dataLog.numDoubleVars = NUM_DOUBLE_VARS;
	dataLog.numFloatVars = NUM_FLOAT_VARS;
	dataLog.numIntVars = NUM_INT_VARS;
	dataLog.numShortVars = NUM_SHORT_VARS;

	double tic,time,t0=0;
	static int t0_latched = FALSE;
	int loop_counter = 0;

	// Populate sensorData structure with pointers to data structures
	sensorData.imuData_ptr = &imuData;
	sensorData.gpsData_ptr = &gpsData;
	sensorData.adData_ptr = &adData;
	sensorData.surfData_ptr = &surfData;

	// Initialize set_actuators (PWM or serial) at zero
	init_actuators();
	set_actuators(&controlData);

	// initialize functions
	init_daq(&sensorData, &insgpsData, &ahrsdrData, &navData, &controlData);
	init_telemetry();

	while(1){
		controlData.mode = 1; // initialize to manual mode
		controlData.run_num = 0; // reset run counter

		//initialize real time clock at zero
		reset_Time();

		// Initialize scheduling
		init_scheduler();

		// start additional threads
		threads_create();

		// Initialize data logging
		init_datalogger();
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		//main-loop
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		while (controlData.mode != 0) {

			loop_counter++; //.increment loop counter

			//**** NAVIGATION ********************************************************

			//*********************************Run Parallel Nav Filters***********************************//
			// Run AHRS
			if (ahrsdrData.err_type == got_invalid){ // check if AHRS filter has been initialized
				// Initialize AHRS filter
				init_ahrs(&sensorData, &ahrsdrData, &controlData);
				send_status("AHRS initialized");
			}
			else{
				// Call AHRS
				get_ahrs(&sensorData, &ahrsdrData, &controlData);
			}

			// Run DR & GPS-aided INS filters
			if (ahrsdrData.err_type_2 == got_invalid){ // Check if DR has been initialized
				if (gpsData.navValid == 0) {// check if GPS is locked
					// Initialize DR & GPS-aided INS filters
					init_dr(&sensorData, &ahrsdrData, &controlData);
					init_insgps(&sensorData, &insgpsData, &controlData, &ahrsdrData);
					send_status("Position initialized");
				}
			}
			else{
				// Call DR & GPS-aided INS filters
				get_dr(&sensorData, &ahrsdrData, &controlData);
				get_insgps(&sensorData, &insgpsData, &controlData, &ahrsdrData);
				// Ensure that GPS newData flag is reset AFTER filters run
				if (gpsData.newData == 1){
					gpsData.newData = 0;
				}
			}
			//********************************************************************************************//

			//********************************Run Blending Nav Filter*************************************//
			if (navData.err_type == got_invalid){ // check if Blending filter has been initialized
				// Initialize Blender
				init_nav(&sensorData, &insgpsData, &ahrsdrData, &navData);
				send_status("Blending initialized");
			}

			else{
				// Call Blender
				get_nav(&sensorData, &insgpsData, &ahrsdrData, &navData);
			}
			//********************************************************************************************//

			//**** END NAVIGATION ********************************************************

			if (controlData.mode == 2) { // autopilot mode
				if (t0_latched == FALSE) {
					t0 = get_Time();
					t0_latched = TRUE;
				}

				time = get_Time()-t0; // Time since in auto mode

				//**** GUIDANCE **********************************************************
				get_guidance(time, &sensorData, &navData, &controlData);
				etime_guidance= get_Time() - tic - etime_nav - etime_daq; // compute execution time
				//************************************************************************

				//**** SENSOR FAULT ******************************************************
				get_sensor_fault(time, &sensorData, &navData, &controlData);
				etime_sensfault = get_Time() - tic - etime_guidance - etime_nav - etime_daq; // compute execution time
				//************************************************************************

				//**** CONTROL ***********************************************************
				get_control(time, &sensorData, &navData, &controlData);
				etime_control = get_Time() - tic - etime_sensfault - etime_guidance - etime_nav - etime_daq; // compute execution time
				//************************************************************************

				//**** SYSTEM ID *********************************************************
				get_system_id(time, &sensorData, &navData, &controlData);
				etime_sysid = get_Time() - tic - etime_control - etime_sensfault - etime_guidance - etime_nav - etime_daq; // compute execution time
				//************************************************************************

				//**** SURACE FAULT ******************************************************
				get_surface_fault(time, &sensorData, &navData, &controlData);
				etime_surffault = get_Time() - tic - etime_sysid - etime_control - etime_sensfault - etime_guidance - etime_nav - etime_daq; // compute execution time
				//************************************************************************

			}
			else{
				if (t0_latched == TRUE) {
					t0_latched = FALSE;
				}
				reset_control(&controlData); // reset controller states and set get_control surfaces to zero
			} // end if (controlData.mode == 2)

			// Add trim biases to get_control surface commands
			add_trim_bias(&controlData);

			//**** ACTUATORS *********************************************************
			set_actuators(&controlData);
			etime_actuators = get_Time() - tic - ACTUATORS_OFFSET; // compute execution time
			//************************************************************************

			//**** DATA LOGGING ******************************************************
			datalogger();
			etime_datalog = get_Time() - tic - etime_actuators - ACTUATORS_OFFSET; // compute execution time
			//************************************************************************

			//**** TELEMETRY *********************************************************
			if(loop_counter >= BASE_HZ/TELEMETRY_HZ){
				loop_counter = 0;

				// get current cpu load
				cyg_cpuload_get (loadhandle, &last100ms, &last1s, &last10s);
				cpuLoad = (uint16_t)last100ms;

				send_telemetry(&sensorData, &navData, &controlData, cpuLoad);

				etime_telemetry = get_Time() - tic - etime_datalog - etime_actuators - ACTUATORS_OFFSET; // compute execution time
			}
			//************************************************************************

#ifndef HIL_SIM
			// Take zero on pressure sensors during first 10 seconds
			if (tic > 4.0 && tic < 10.0){
				airdata_bias_estimate(&adData);
			}
#endif
		} //end while (controlData.mode != 0)

		close_scheduler();
		close_datalogger(); // dump data

	} // end while(1)
	/**********************************************************************
	 * close
	 **********************************************************************/

	close_actuators();
	close_ahrs();
	close_insgps();
	close_dr();
	close_nav();

	return 0;

} // end main


