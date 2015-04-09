/*
 * \file nav_interface.h
 *
 *	\details This file declares the standard function prototypes for interfacing with the navigation filter.
 *	All navigation filters must include this file and instantiate the init_nav(), get_nav(), and close_nav() functions.
 *
 *  Created on: 5:28:56 PM Feb 4, 2015 by john
 *  \author University of Minnesota
 *  \author Aerospace Engineering and Mechanics
 *  \copyright Copyright 2015 Regents of the University of Minnesota.  All rights reserved.
 */

#ifndef SOURCE_NAVIGATION_NAV_INTERFACE_H_
#define SOURCE_NAVIGATION_NAV_INTERFACE_H_

//*************************************AHRS FUNCTIONS*************************************//
/// Standard function to initialize the AHRS navigation filter.
/*!
* \sa get_ahrs(), close_ahrs()
* \ingroup nav_fcns
*/
void init_ahrs(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
			   struct ahrsdr *ahrsdrData_ptr,		///< pointer to AHRS-DR Data structure
			   struct control *controlData_ptr		///< pointer to controlData structure
					);

/// Standard function to call the AHRS navigation filter.
/*!
* \sa init_ahrs(), close_ahrs()
* \ingroup nav_fcns
*/
void get_ahrs(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
			  struct ahrsdr *ahrsdrData_ptr,		///< pointer to AHRS-DR Data structure
			  struct control *controlData_ptr		///< pointer to controlData structure
				);

/// Standard function to close the AHRS navigation filter.
/*!
* No input or return parameters
* \sa get_ahrs(), init_ahrs()
* \ingroup nav_fcns
*/
void close_ahrs(void);
//****************************************************************************************//

//********************************DEAD RECKONING FUNCTIONS********************************//
/// Standard function to initialize the Dead Reckoning navigation filter.
/*!
* \sa get_dr(), close_dr()
* \ingroup nav_fcns
*/
void init_dr(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
			 struct ahrsdr *ahrsdrData_ptr,		///< pointer to AHRS-DR Data structure
			 struct control *controlData_ptr	///< pointer to controlData structure
				);

/// Standard function to call the Dead Reckoning navigation filter.
/*!
* \sa init_dr(), close_dr()
* \ingroup nav_fcns
*/
void get_dr(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
			struct ahrsdr *ahrsdrData_ptr,		///< pointer to AHRS-DR Data structure
			struct control *controlData_ptr		///< pointer to controlData structure
				);

/// Standard function to close the Dead Reckoning navigation filter.
/*!
* No input or return parameters
* \sa get_dr(), init_dr()
* \ingroup nav_fcns
*/
void close_dr(void);
//****************************************************************************************//

//******************************GPS-AIDED INS NAV FUNCTIONS*******************************//
/// Standard function to initialize the GPS-aided INS navigation filter.
/*!
* \sa get_insgps(), close_insgps()
* \ingroup nav_fcns
*/
void init_insgps(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
				 struct insgps *insgpsData_ptr,		///< pointer to GPS-aided INS Data structure
				 struct control *controlData_ptr,	///< pointer to controlData structure
				 struct ahrsdr *ahrsdrData_ptr		///< pointer to AHRS-DR Data structure
					);

/// Standard function to call the GPS-aided INS navigation filter.
/*!
* \sa init_insgps(), close_insgps()
* \ingroup nav_fcns
*/
void get_insgps(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
				struct insgps *insgpsData_ptr,		///< pointer to GPS-aided INS Data structure
				struct control *controlData_ptr,	///< pointer to controlData structure
				struct ahrsdr *ahrsdrData_ptr		///< pointer to AHRS-DR Data structure
					);

/// Standard function to close the GPS-aided INS navigation filter.
/*!
* No input or return parameters
* \sa get_insgps(), init_insgps()
* \ingroup nav_fcns
*/
void close_insgps(void);
//****************************************************************************************//

//***********************************BLENDING FUNCTIONS***********************************//
/// Standard function to initialize the Blending navigation filter.
/*!
* \sa get_nav(), close_nav()
* \ingroup nav_fcns
*/
void init_nav(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
			  struct insgps *insgpsData_ptr,		///< pointer to GPS-aided INS Data structure
			  struct ahrsdr *ahrsdrData_ptr,		///< pointer to AHRS-DR Data structure
			  struct nav *navData_ptr				///< pointer to blended nav Data structure
					);

/// Standard function to call the Blending navigation filter.
/*!
* \sa init_nav(), close_nav()
* \ingroup nav_fcns
*/
void get_nav(struct sensordata *sensorData_ptr,	///< pointer to sensorData structure
			 struct insgps *insgpsData_ptr,		///< pointer to GPS-aided INS Data structure
			 struct ahrsdr *ahrsdrData_ptr,		///< pointer to AHRS-DR Data structure
			 struct nav *navData_ptr				///< pointer to blended nav Data structure
					);

/// Standard function to close the Blending navigation filter.
/*!
* No input or return parameters
* \sa get_nav(), init_nav()
* \ingroup nav_fcns
*/
void close_nav(void);
//****************************************************************************************//


#endif /* SOURCE_NAVIGATION_NAV_INTERFACE_H_ */
