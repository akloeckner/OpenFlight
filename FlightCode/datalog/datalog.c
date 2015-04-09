/*
 * \file datalog.c
 * \description Functions used to datalog in HDF5 format
 *  
 *  Created on: 1:35:26 PM Feb 10, 2015 by john
 *  \author University of Minnesota
 *  \author Aerospace Engineering and Mechanics
 *  \copyright Copyright 2015 Regents of the University of Minnesota.  All rights reserved.
 */

#include "datalog.h"

#define FILENAME "airplanes.h5"


int datalog_init(void){

	hid_t fd; // handle to file (hid_t is type int)
	// check to see if SD card is mounted - will this happen here or in linux space?

	// create a new .h5 file for data logging
	fd = H5Fcreate(FILENAME, H5F_ACC_TRUNC,H5P_DEFAULT, H5P_DEFAULT);
	// error check
	if(!fd)
		stderr("Unable to create new HDF5 file - aborting!\n");

	// Return the file handle on success
	return fd;
}
