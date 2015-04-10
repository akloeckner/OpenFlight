/*! \file sd.c
 *	\brief Send sd data through serial port
 *
 *	\details
 *	\ingroup telemetry_fcns
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <pthread.h>
#include <sched.h>
#include <cyg/posix/pthread.h>
#include <cyg/kernel/kapi.h>
#include <cyg/cpuload/cpuload.h>
#include <cyg/io/io.h>
#include <cyg/io/serialio.h>

#include "../globaldefs.h"
#include "../utils/serial_mpc5200.h"
#include "../utils/misc.h"
#include "../extern_vars.h"
#include "telemetry_interface.h"
#include AIRCRAFT_UP1DIR

static int port;

void init_sd(){
	//Open serial port for send_sd. Set in /aircraft/xxx_config.h
	port = open_serial(TELEMETRY_PORT, TELEMETRY_BAUDRATE);	
}	

void send_sd(struct sensorData *sensorData_ptr) {
	
	int bytes=0;
	unsigned short flags=0;
	unsigned long tmp;
	uint16_t tele_data[XX], output_CKSUM=0;
	static byte sendpacket[TELE_PACKET_SIZE]={'U','U','T',};
	
	// Build send_sddata packet
	tmp = (unsigned long)( sensorData_ptr->imuData_ptr->time*1e04 );		// time buffer will now overflow after 59.6 hrs (thats what 4 bytes' worth!)
	memcpy(&tele_data[0],&tmp,4);
	
	tele_data[2] = (uint16_t)( sensorData_ptr->imuData_ptr->p*R2D / 200.0 * 0x7FFF );	//rate = 200 deg/s max saturation
	tele_data[3] = (uint16_t)( sensorData_ptr->imuData_ptr->q*R2D / 200.0 * 0x7FFF );
	tele_data[4] = (uint16_t)( sensorData_ptr->imuData_ptr->r*R2D / 200.0 * 0x7FFF );

	tele_data[5] = (uint16_t)( sensorData_ptr->imuData_ptr->ax);	
	tele_data[6] = (uint16_t)( sensorData_ptr->imuData_ptr->ay);
	tele_data[7] = (uint16_t)( sensorData_ptr->imuData_ptr->az);
	
	tele_data[8] = (uint16_t)( sensorData_ptr->imuData_ptr->hx);
	tele_data[9] = (uint16_t)( sensorData_ptr->imuData_ptr->hy);
	tele_data[10]= (uint16_t)( sensorData_ptr->imuData_ptr->hz);
	
	if ( (sensorData_ptr->imuData_ptr->err_type != checksum_err) && (sensorData_ptr->imuData_ptr->err_type != got_invalid) ) flags = flags | 0x01<<6;
	
	tele_data[11] = flags;
	
	}

