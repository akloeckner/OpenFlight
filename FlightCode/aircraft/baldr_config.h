/*! \file baldr_config.h
 *	\brief Configuration defines for the BALDR aircraft.
 *
 *	\details This file contains the geometry, surface calibrations and limits, and serial port configuration for the BALDR aircraft.
 *	\ingroup aircraft_cfg
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: baldr_config.h ID missing $
 */

#ifndef BALDR_CONFIG_H_
#define BALDR_CONFIG_H_

#define AIRCRAFT_BALDR	///< Aircraft name. Used in daq() for sensor processing.

// Set geometry values to zero to 'disable' the rate corrections for now. AMM 9/12/11
// Geometry Data for Left Air Data Vane
#define L_VANE_ALPHA_BIAS    0.00  ///< [rad], pitch angular offset of vane. Positive downwards from level
#define L_VANE_BETA_BIAS     0.00  ///< [rad], pitch angular offset of vane. Positive downwards from level
#define L_VANE2CG_X     0.00 ///< [m], position of vane relative to cg, in body axis frame  0.475
#define L_VANE2CG_Y	    0.00 ///< [m], position of vane relative to cg, in body axis frame -0.999
#define L_VANE2CG_Z		0.00 ///< [m], position of vane relative to cg, in body axis frame -0.070 est

// Geometry Data for Right Air Data Vane
#define R_VANE_ALPHA_BIAS    0.00  ///< [rad], pitch angular offset of vane. Positive downwards from level
#define R_VANE_BETA_BIAS     0.00  ///< [rad], pitch angular offset of vane. Positive downwards from level
#define R_VANE2CG_X     0.00 ///< [m], position of vane relative to cg, in body axis frame  0.480
#define R_VANE2CG_Y		0.00 ///< [m], position of vane relative to cg, in body axis frame  0.982
#define R_VANE2CG_Z		0.00 ///< [m], position of vane relative to cg, in body axis frame -0.070 est

// Calibration data for Left Air Data Vane
#define L_ALPHA1_SLOPE -0.0014576	///< [rad/count]
#define L_ALPHA2_SLOPE	1.0  		///< [rad/count]
#define L_BETA_SLOPE   -0.0010477	///< [rad/count]
#define L_ALPHA1_BIAS	2.3797		///< [rad]
#define L_ALPHA2_BIAS	0.0			///< [rad]
#define L_BETA_BIAS		1.5206		///< [rad]

// Calibration data for Right Air Data Vane
#define R_ALPHA1_SLOPE	0.0013434	///< [rad/count]
#define R_ALPHA2_SLOPE	1.0			///< [rad/count]
#define R_BETA_SLOPE	0.00086635	///< [rad/count]
#define R_ALPHA1_BIAS  -2.1523		///< [rad]
#define R_ALPHA2_BIAS   0.0			///< [rad]
#define R_BETA_BIAS	   -1.3216		///< [rad]

// Geometry Data for Air Data Probe
#define PITOT_ALPHA_BIAS  0.0611 ///< [rad], pitch angular offset of 5-hole pitot probe. Positive downwards from level
#define PITOT_BETA_BIAS   0.0    ///< [rad], lateral angular offset of 5-hole pitot probe. Positive right from centerline
#define PITOT2CG_X      0.18 ///< [m], position of pitot probe relative to cg, in body axis frame
#define PITOT2CG_Y		0.36 ///< [m], position of pitot probe relative to cg, in body axis frame
#define PITOT2CG_Z		0.00 ///< [m], position of pitot probe relative to cg, in body axis frame

// Control Surface Trims, from faser_flight01
#define THROTTLE_TRIM   0.65 ///< [ND], approximate throttle trim value
#define ELEVATOR_TRIM  -0.09 ///< [rad], approximate elevator trim value (right elevator)
#define RUDDER_TRIM     0.0  ///< [rad], approximate rudder trim value (bottom rudder)
#define AILERON_TRIM   -0.06 ///< [rad], approximate aileron trim value
#define L_FLAP_TRIM		-0.09 ///< [rad], approximate left flap trim value (left elevator)
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

// MPC5200 PWM output channel assignments
#define PWMOUT_DTHR_CH  0 ///<  PWM output channel for throttle
#define PWMOUT_DE_CH  	1 ///<  PWM output channel for elevator
#define PWMOUT_DR_CH 	2 ///<  PWM output channel for rudder
#define PWMOUT_DA_L_CH 	3 ///<  PWM output channel for left aileron
#define PWMOUT_DA_R_CH 	4 ///<  PWM output channel for right aileron
#define PWMOUT_DF_L_CH 	5 ///<  PWM output channel for left flap
#define PWMOUT_DF_R_CH	7 ///<  PWM output channel for right flap

// MPC5200 PWM output command calibration parameters
#define PWMOUT_DTHR_CAL {2087,3033} ///< linear calibration for throttle, based on measured PWM throttle output
// Control surface calibrations were completed for BALDR on 10/29/2014 by RV
#define PWMOUT_DE_CAL  	{140.4,		-1232.4,	304.1,		-2483.7,	4108.9} ///< cubic calibration for elevator (right elevator)
#define PWMOUT_DR_CAL   {-34.748,	-373.36,	-5.4729,	-1268.9,	4045.5} ///< cubic calibration for rudder (bottom rudder)
#define PWMOUT_DA_L_CAL {989.75,	-808.94,	-84.252,	-2189.4,	3987.6} ///< cubic calibration for left aileron (left aileron)
#define PWMOUT_DA_R_CAL {-299.72,	848.21,		-18.081,	2094.5,		4093.4} ///< cubic calibration for right aileron (right aileron)
#define PWMOUT_DF_L_CAL {-37.245,	536.94,		7.5885,		1753.7,		4069.2} ///< cubic calibration for left flap (left elevator)
#define PWMOUT_DF_R_CAL {-545.45,	-510.12,	-57.103,	-1912.4,	4073.7} ///< cubic calibration for right flap (top rudder)

// R/C PWM input command channels
#define PWMIN_DTHR_CH	1 ///<  PWM input channel for throttle
#define PWMIN_DE_CH		2 ///<  PWM input channel for elevator
#define PWMIN_DR_CH		0 ///<  PWM input channel for rudder
#define PWMIN_DA_L_CH	3 ///<  PWM input channel for left aileron
#define PWMIN_DA_R_CH	3 ///<  PWM input channel for right aileron

// R/C PWM input command calibration parameters TODO: update these
// These calibration coefficients had the incorrect sign. RV updated them on 11/24/2014.
#define PWMIN_SCALING 10000 	///< scaling parameter to apply to PWM readings prior to applying calibration
#define PWMIN_DTHR_CAL	{0.00098716683119, -2.527147087857848}	///<  linear calibration for throttle PWM input
#define PWMIN_DE_CAL	{111.529886096001,	-96.8294668116000,	21.5238268564487,	-0.763949002413993}	///<  linear calibration for elevator PWM input
#define PWMIN_DR_CAL	{84.7756193670826,	-76.8786260771467,	17.1754736690082,	-0.535104948804940}	///<  linear calibration for rudder PWM input
#define PWMIN_DA_L_CAL	{42.3502385103704,	-40.4850850262976,	6.72738032331522,	0.496271142735041}	///<  linear calibration for left aileron PWM input
#define PWMIN_DA_R_CAL	{-61.0358884569641,	52.2900804796504,	-8.82735081897271,	-0.471140780636548}	///<  linear calibration for right aileron PWM input
#define PWMIN_DF_L_CAL	{-8.19212357279288,	11.0704001359758,	-2.59648820938495}	///<  linear calibration for left flap PWM input
#define PWMIN_DF_R_CAL	{4.70693741824564,	-9.05102546586889,	2.30756437001963}	///<  linear calibration for right flap PWM input
#define PWMIN_DG_THRESHOLD 3000		///<  threshold for gear PWM input; below = 0, above = 1

// Potentiometer calibration parameters
// Control surface calibrations were completed for BALDR on 10/29/2014 by RV
#define POS_DE_L_MU		1230.7 ///< mean for left elevator potentiometer
#define POS_DE_L_SIGMA	581.81 ///< std dev for left elevator potentiometer
#define POS_DE_L_CAL 	{0.0030286,		-0.014807,		-0.0069503,		-0.52896,	0.0082218} ///< cubic calibration for left elevator potentiometer

#define POS_DE_R_MU		1244.1 ///< mean for right elevator potentiometer
#define POS_DE_R_SIGMA	407.24 ///< std dev for right elevator potentiometer
#define POS_DE_R_CAL	{0.0011695,		0.0052719,		-0.0019569,		0.38885,	0.023105} ///< cubic calibration for right elevator potentiometer

// Air data vane  calibrations were completed for BALDR on 10/29/2014 by RV
#define POS_ALPHA_CAL 	{-0.0012822,	1.9707} ///< linear calibration for alpha vane
#define POS_BETA_CAL 	{-0.00091349,	1.29} ///< linear calibration for beta vane

#endif	
