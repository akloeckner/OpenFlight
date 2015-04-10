/*! \file sd_interface.h
* \brief - sd logger header
* \details - This file declares the standard function prototypes for 
*		  interfacing with the sd data logger
*
* \author University of Minnesota
* \author Aerospace Engineering and Mechanics
* \copyright Copyright 2011 Regents of the University of Minnesota. All rights *  reserved.
*/

#ifndef SD_INTERFACE_H_
#define SD_INTERFACE_H_

void init_sd();
/// Standard function to initialize the send_sd

void send_sd(struct sensorData *sensorData _ptr); ///< pointer to imuData structure
/// Standard function to call the send_telemetry

#endif