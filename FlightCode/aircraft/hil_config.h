/*! \file hil_config.h
 *	\brief Configuration defines for the HIL simulation.
 *
 *	\details This file contains the geometry, surface calibrations and limits, and serial port configuration for the HIL Simulation.
 *	\ingroup aircraft_cfg
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 */
#ifndef HIL_CONFIG_H_
#define HIL_CONFIG_H_

#define HIL_SIM ///< Aircraft name.

// Actuator/DAQ port configuration
#define HIL_PORT SERIAL_PORT1	///< Serial port used for actuators() and daq()
#define HIL_BAUDRATE B115200	///< Serial port baudrate
int hilPort;					///< Handle for serial port. Used in actuators() and daq().

// GPS Sensor Configuration... not actually used.
#define GPS_PORT 		SERIAL_PORT2	///< unused in this configuration, but needed for init_daq()
#define GPS_BAUDRATE	B57600			///< unused in this configuration, but needed for init_daq()

// Downlink telemetry port configuration
//#define TELEMETRY_PORT SERIAL_PORT0	///< Serial port for telemetry()
//#define TELEMETRY_BAUDRATE B115200	///< Baud rate of serial port for telemetry()

// Made change to use modem for telemetry, instead of the intended second serial port.
// Downlink telemetry configuration
#define TELEMETRY_PORT 		SERIAL_PORT3	///< Serial port for telemetry()
#define TELEMETRY_BAUDRATE	B115200			///< Baud rate of serial port for telemetry()

// Control Surface Trims, from faser_flight01
#define THROTTLE_TRIM   0.507 ///< [ND], approximate throttle trim value
#define ELEVATOR_TRIM  -0.0887 ///< [rad], approximate elevator trim value (right elevator)
#define RUDDER_TRIM     0.0  ///< [rad], approximate rudder trim value (bottom rudder)
#define AILERON_TRIM   -0.0053 ///< [rad], approximate aileron trim value
#define L_FLAP_TRIM		-0.0887 ///< [rad], approximate left flap trim value (left elevator)
#define R_FLAP_TRIM 	0.0 ///< [rad], approximate right flap trim value (top rudder)

// Control Surface Limits, max and min
#define 	THROTTLE_MAX 	 1.0
#define		THROTTLE_MIN	 0.0
#define		RUDDER_MAX		 0.4363	///< [rad], 25deg
#define		RUDDER_MIN		-0.4363 ///< [rad],-25deg
#define		ELEVATOR_MAX	 0.4363	///< [rad], 25deg
#define		ELEVATOR_MIN	-0.4363 ///< [rad],-25deg
#define 	L_AILERON_MAX	 0.4363	///< [rad], 25deg
#define 	L_AILERON_MIN	-0.4363 ///< [rad],-25deg
#define 	R_AILERON_MAX	 0.4363	///< [rad], 25deg
#define 	R_AILERON_MIN	-0.4363 ///< [rad],-25deg
#define 	L_FLAP_MAX	 	 0.4363	///< [rad], 25deg
#define 	L_FLAP_MIN		-0.4363 ///< [rad],-25deg
#define 	R_FLAP_MAX	 	 0.4363	///< [rad], 25deg
#define 	R_FLAP_MIN		-0.4363	///< [rad],-25deg
	
#endif	
