/*
 * \file datalog.h
 * \description
 *  
 *  Created on: 1:35:42 PM Feb 10, 2015 by john
 *  \author University of Minnesota
 *  \author Aerospace Engineering and Mechanics
 *  \copyright Copyright 2015 Regents of the University of Minnesota.  All rights reserved.
 */

#ifndef SOURCE_DATALOG_DATALOG_H_
#define SOURCE_DATALOG_DATALOG_H_

#include "hdf5.h"

int datalog_init(void);
err datalog_save(void);
err datalog_writeHDF5(void);
err datalog_close(void);


#endif /* SOURCE_DATALOG_DATALOG_H_ */
