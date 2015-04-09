/*! \file ibis_config.h
 *	\brief Configuration defines for the IBIS aircraft.
 *
 *	\details This file contains the geometry, surface calibrations and limits, and serial port configuration for the IBIS aircraft.
 *	\ingroup aircraft_cfg
 *
 * \author University of Minnesota
 * \author Aerospace Engineering and Mechanics
 * \copyright Copyright 2011 Regents of the University of Minnesota. All rights reserved.
 *
 * $Id: ibis_config.h 1010 2013-11-27 16:13:09Z brtaylor $
 */
#ifndef IBIS_CONFIG_H_
#define IBIS_CONFIG_H_

#define AIRCRAFT_IBIS	///< Aircraft name. Used in daq() for sensor processing.

// Geometry Data for Pitot Probe
#define PITOT_ALPHA_BIAS  0.0611 ///< [rad], pitch angular offset of 5-hole pitot probe. Positive downwards from level
#define PITOT_BETA_BIAS   0.0    ///< [rad], lateral angular offset of 5-hole pitot probe. Positive right from centerline
#define PITOT2CG_X      0.18 ///< [m], position of pitot probe relative to cg, in body axis frame
#define PITOT2CG_Y		0.36 ///< [m], position of pitot probe relative to cg, in body axis frame
#define PITOT2CG_Z		0.00 ///< [m], position of pitot probe relative to cg, in body axis frame

// Control Surface Trims, from ibis_flight01
#define THROTTLE_TRIM   0.60 ///< [ND], approximate throttle trim value
#define ELEVATOR_TRIM  -0.0466 ///< [rad], approximate elevator trim value
#define RUDDER_TRIM     0.0 ///< [rad], approximate rudder trim value
#define AILERON_TRIM   -0.0255 ///< [rad], approximate aileron trim value

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

// MPC5200 PWM output calibration parameters
#define PWMOUT_DTHR_CAL {2087.0,	3033.0} ///< linear calibration for throttle, based on measured PWM throttle output
//#define PWMOUT_DE_CAL  	{ -1020.3, 	-315.09,   -2288.7, 	4118.4} ///< cubic calibration for elevator
//#define PWMOUT_DR_CAL   { -717.21, 	  52.22,   -2261.8, 	4177.7} ///< cubic calibration for rudder
//#define PWMOUT_DA_L_CAL { -1331.0, 	 540.57,   -2185.0, 	4065.5} ///< cubic calibration for left aileron
//#define PWMOUT_DA_R_CAL {  121.7, 	-444.08,    2447.3, 	4371.7} ///< cubic calibration for right aileron
//#define PWMOUT_DF_L_CAL { -901.75, 	 480.14,   -2336.1, 	4176.2} ///< cubic calibration for left flap
//#define PWMOUT_DF_R_CAL { -769.88, 	 199.77,   -2375.6, 	4094.6} ///< cubic calibration for right flap
#define PWMOUT_DE_CAL  	{ -1020.3, 	-315.09,   -2288.7, 	4118.4} ///< cubic calibration for elevator
#define PWMOUT_DR_CAL   { -717.21, 	  52.22,   -2261.8, 	4177.7} ///< cubic calibration for rudder
#define PWMOUT_DA_L_CAL { -1331.0, 	 540.57,   -2185.0, 	4065.5} ///< cubic calibration for left aileron
#define PWMOUT_DA_R_CAL {  121.7, 	-444.08,    2447.3, 	4371.7} ///< cubic calibration for right aileron
#define PWMOUT_DF_R_CAL { 769.88, 	 -199.77,   2375.6, 	4094.6} ///< cubic calibration for right flap
#define PWMOUT_DF_L_CAL { 769.88, 	 -199.77,   2375.6, 	4094.6} ///< cubic calibration for right flap

// R/C PWM input command channels
#define PWMIN_DTHR_CH	1 ///<  PWM input channel for throttle
#define PWMIN_DE_CH		2 ///<  PWM input channel for elevator
#define PWMIN_DR_CH		0 ///<  PWM input channel for rudder
#define PWMIN_DA_L_CH	3 ///<  PWM input channel for left aileron
#define PWMIN_DA_R_CH	3 ///<  PWM input channel for right aileron

//TODO: check to make sure calibration parameters are correct. These are copied from thor_config.h
// R/C PWM input command calibration parameters 
#define PWMIN_SCALING 10000 	///< scaling parameter to apply to PWM readings prior to applying calibration
#define PWMIN_DTHR_CAL	{0.00098716683119, -2.527147087857848}	///<  linear calibration for throttle PWM input
#define PWMIN_DE_CAL	{-111.529886096001,	96.8294668116000,	-21.5238268564487,	0.763949002413993}	///<  linear calibration for elevator PWM input
#define PWMIN_DR_CAL	{84.7756193670826,	-76.8786260771467,	17.1754736690082,	-0.535104948804940}	///<  linear calibration for rudder PWM input
#define PWMIN_DA_L_CAL	{-42.3502385103704,	40.4850850262976,	-6.72738032331522,	-0.496271142735041}	///<  linear calibration for left aileron PWM input
#define PWMIN_DA_R_CAL	{61.0358884569641,	-52.2900804796504,	8.82735081897271,	0.471140780636548}	///<  linear calibration for right aileron PWM input

	
#endif	

