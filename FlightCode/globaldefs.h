/*
 * globaldefs.h
 *
 *  Created on: Feb 2, 2015
 *      Author: John
 */

#ifndef SOURCE_GLOBALDEFS_H_
#define SOURCE_GLOBALDEFS_H_

// ****** Macro function definitions *******************************************
#define	mymin(arg1,arg2) 	(arg1<=arg2 ? arg1:arg2) 	///< Return the lesser of two input arguments */
#define	mymax(arg1,arg2)	(arg1>=arg2 ? arg1:arg2)	///< Return the greater of two input arguments */
#define sign(arg) 			(arg>=0 ? 1:-1) 			///< Return the sign of the input argument */
// *****************************************************************************

// ******  Thread Settings *****************************************************
#define TIMESTEP 0.02 ///< Base time step, needed for control laws */
// *****************************************************************************

// ****** Unit conversions and constant definitions: ***************************
#define NSECS_PER_SEC	1000000000 		///< [nsec/sec] nanoseconds per second */
#define D2R			0.017453292519943	///< [rad] degrees to radians */
#define R2D			57.295779513082323	///< [deg] radians to degrees */
#define PSI_TO_KPA  6.89475729  		///< [KPa] PSI to KPa */
#define	g			9.814				///< [m/sec^2] gravity */
#define g2      	19.62   			///< [m/sec^2] 2*g */
#define PI      	3.14159265358979    ///< pi */
#define PI2     	6.28318530717958	///< pi*2 */
#define half_pi		1.57079632679490	///< pi/2 */
#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif
// *****************************************************************************

//****** NEED TO BE UPDATED BEFORE EVERY FLIGHT FOR DAY AND LOCATION ***********
// Resourse for local magnetic field: http://www.ngdc.noaa.gov/geomag-web/#igrfwmm
#define		hn_x	0.174935	// X componenet of magnetometer vector in NED frame from the NOAA > NESDIS > NGDC > Geomagnetism Magnetic Field Calculators using the IGRF 11 Model for location and date being tested
#define		hn_y	0.001217	// Y componenet of magnetometer vector in NED frame from the NOAA > NESDIS > NGDC > Geomagnetism Magnetic Field Calculators using the IGRF 11 Model for location and date being tested
#define		hn_z	0.526664	// Z componenet of magnetometer vector in NED frame from the NOAA > NESDIS > NGDC > Geomagnetism Magnetic Field Calculators using the IGRF 11 Model for location and date being tested
//******************************************************************************

// ****** Type definitions *****************************************************
typedef unsigned char	byte;	///< typedef of byte */
typedef unsigned short	word;	///< typedef of word */

/// Define status message enum list
enum   errdefs	{
	got_invalid,		///< No data received //0
	checksum_err,		///< Checksum mismatch //1
	gps_nolock,			///< No GPS lock //2
	data_valid,			///< Data valid //3
	noPacketHeader,		///< Some data received, but cannot find packet header //4
	incompletePacket,	///< Packet header found, but complete packet not received //5
	TU_only,			///< NAV filters, time update only //6
	gps_aided,			///< NAV filters, GPS aided //7
	inflated_gps_aided,	///< NAV filters, Inflated noise with GPS aiding //8
	refining,			///< NAV filter, Refining at intialization //9
	MU_ahrs				///< NAV filter, AHRS Measurement Update //10
	};

/// IMU Data Structure
struct imu {
	double p;				///< [rad/sec], body X axis angular rate (roll)
	double q;				///< [rad/sec], body Y axis angular rate (pitch)
	double r;				///< [rad/sec], body Z axis angular rate (yaw)
	double ax;				///< [m/sec^2], body X axis acceleration
	double ay;				///< [m/sec^2], body Y axis acceleration
	double az;				///< [m/sec^2], body Z axis acceleration
	double hx;				///< [Gauss], body X axis magnetic field
	double hy;				///< [Gauss], body Y axis magnetic field
	double hz;				///< [Gauss], body Z axis magnetic field
	double phi;				///< [rad], Euler roll angle. Only used if IMU sensor reports attitude.
	double the;				///< [rad], Euler pitch angle. Only used if IMU sensor reports attitude.
	double psi;				///< [rad], Euler yaw angle. Only used if IMU sensor reports attitude.
	float  T;				///< [degC], temperature of IMU sensor
	float  Vs;				///< [Volts], supply voltage of IMU sensor
	double adc;				///< [counts], ADC reading
	enum errdefs err_type;	///< IMU status
	double time;			///< [sec], timestamp of IMU data
};

/// GPS Data Structure
struct gps {
	double lat;					///< [deg], Geodetic latitude
	double lon;					///< [deg], Geodetic longitude
	double alt;					///< [m], altitude relative to WGS84
	double ve;					///< [m/sec], East velocity
	double vn;					///< [m/sec], North velocity
	double vd;					///< [m/sec], Down velocity
	double Xe;					///< [m], X position, ECEF
	double Ye;					///< [m], Y position, ECEF
	double Ze;					///< [m], Z position, ECEF
	double Ue;					///< [m/sec], X velocity, ECEF
	double Ve;					///< [m/sec], Y velocity, ECEF
	double We;					///< [m/sec], Z velocity, ECEF
    double sig_N;				///< [m], Position error standard deviation in the North direction
    double sig_E;				///< [m], Position error standard deviation in the East direction
    double sig_D;				///< [m], Position error standard deviation in the Down direction
    double sig_vn;				///< [m/sec], Velocity error standard deviation in the North direction
    double sig_ve;				///< [m/sec], Velocity error standard deviation in the East direction
    double sig_vd;				///< [m/sec], Velocity error standard deviation in the Down direction
	double GPS_TOW;				///< [sec], GPS Time Of Week
	double courseOverGround;	///< [rad], course over the ground, relative to true North
	double speedOverGround;		///< [rad], speed over the ground
	double time;				///< [sec], timestamp of GPS data
	unsigned short newData;		///< [bool], flag set when GPS data has been updated
	unsigned short satVisible;	///< Number satellites used in the position solution
	unsigned short navValid;	///< flag indicating whether the solution is valid, 0 = valid
	unsigned short GPS_week;	///< GPS week since current epoch.
	enum errdefs err_type;		///< GPS status
	int baudRate;				///< Baud rate for serial port
	char* portName;				///< Name of serial port
	int port;					///< handle for accessing serial port
    unsigned char* localBuffer; ///< local buffer to store partial serial data packets
    int bytesInLocalBuffer;		///< number of bytes in the local buffer
    int readState;				///< current state of serial data reader function
    int read_calls;				///< number of times the read_gps function has been called
};

/// Air Data Structure
struct airdata {
	double h;				///< [m], barometric altitude above ground level (AGL)
	double h_msl;			///< [m], barometric altitude mean sea level (MSL)
	double ias;				///< [m/sec], indicated airspeed
	double h_filt;			///< [m], filtered altitude
	double ias_filt;		///< [m/s], filtered airspeed
	double Ps;				///< [KPa], static pressure
	double Pd;				///< [KPa], dynamic pressure
	double aoa;				///< [rad], angle of attack from 5-hole Pitot probe
	double aos;				///< [rad], angle of sideslip from 5-hole Pitot probe
	double l_alpha;			///< [rad], angle of attack, from left vane
	double r_alpha;			///< [rad], angle of attack, from right vane
	double l_beta;			///< [rad], angle of sideslip, from left vane
	double r_beta;			///< [rad], angle of sideslip, from right vane
	double Pd_aoa;			///< [KPa], dynamic pressure for aoa, from 5-hole Pitot probe
	double Pd_aos;			///< [KPa], dynamic pressure for aos, from 5-hole Pitot probe
	double bias[10];		///< array for storing biases for air data.
	unsigned short status;	///< status bitfield for air data sensors.
};

/// Control surface deflections
struct surface {
	double dthr_pos;	///< [0-1], measured throttle position
	double de_pos;		///< [rad], measured elevator position, +TED
	double de_l_pos;	///< [rad], measured left elevator position, +TED
	double de_r_pos;	///< [rad], measured right elevator position, +TED
	double dr_pos; 		///< [rad], measured rudder position, +TEL
	double dr_t_pos; 	///< [rad], measured top rudder position, +TEL
	double dr_b_pos; 	///< [rad], measured bottom rudder position, +TEL
	double da_l_pos;	///< [rad], measured left aileron position, +TED
	double da_r_pos;	///< [rad], measured right aileron position, +TED
	double df_l_pos;	///< [rad], measured left flap position, +TED
	double df_r_pos;	///< [rad], measured right flap position, +TED
};

/// Control Data structure
struct control {
	double dthr_in;			///< [0-1], throttle command from R/C
	double de_in;			///< [rad], elevator command, +TED, from R/C
	double dr_in;			///< [rad], rudder command, +TEL, from R/C
	double da_l_in;			///< [rad], left aileron command, +TED, from R/C
	double da_r_in;			///< [rad], right aileron command, +TED, from R/C
	double df_l_in;			///< [rad], left flap command, +TED, from R/C
	double df_r_in;			///< [rad], right flap command, +TED, from R/C
	double dg_in;			///< [rad], gear command, from R/C, controls RxMux
	double dthr;			///< [0-1], throttle command
	double de;				///< [rad], elevator command, +TED
	double dr; 				///< [rad], rudder command, +TEL
	double da_l;			///< [rad], left aileron command, +TED
	double da_r;			///< [rad], right aileron command, +TED
	double df_l;			///< [rad], left flap command, +TED
	double df_r;			///< [rad], right flap command, +TED
	double phi_cmd;			///< [rad], Euler roll angle command
	double theta_cmd;		///< [rad], Euler pitch angle command
	double psi_cmd;			///< [rad], Euler yaw angle command
	double p_cmd;			///< [rad/sec], body axis roll rate command
	double q_cmd;			///< [rad/sec], body axis pitch rate command
	double r_cmd;			///< [rad/sec], body axis yaw rate command
	double ias_cmd;			///< [m/sec], airspeed command
	double h_cmd;			///< [m], altitude command
	double gndtrk_cmd;		///< [rad], ground track angle command, relative to true north
	double aoa_cmd;			///< [rad], angle of attack command
	double aos_cmd;			///< [rad], angle of sideslip command
	double gamma_cmd;		///< [rad], flight path angle command
	double signal_0;		///< user defined dummy variable
	double signal_1;		///< user defined dummy variable
	double signal_2;	    ///< user defined dummy variable
	double signal_3;		///< user defined dummy variable
	double signal_4;		///< user defined dummy variable
	double signal_5;		///< user defined dummy variable
	double signal_6;		///< user defined dummy variable
	double signal_7;		///< user defined dummy variable
	double signal_8;		///< user defined dummy variable
	double signal_9;		///< user defined dummy variable
	unsigned short mode;	///< mode variable; 0 = dump data, 1 = manual control, 2 = autopilot control
	unsigned short run_num;	///< counter for number of autopilot engagements
};

/// GPS-aided INS Filter Data Structure
struct insgps {
	double lat;						///< [rad], geodetic latitude estimate
	double lon;						///< [rad], geodetic longitude estimate
	double alt;						///< [m], altitude relative to WGS84 estimate
	double vn;						///< [m/sec], north velocity estimate
	double ve;						///< [m/sec], east velocity estimate
	double vd;						///< [m/sec], down velocity estimate
	double phi;						///< [rad], Euler roll angle estimate
	double the;						///< [rad], Euler pitch angle estimate
	double psi;						///< [rad], Euler yaw angle estimate
	double quat[4];					///< Quaternions estimate
	double ab[3];					///< [m/sec^2], accelerometer bias estimate
	double gb[3];					///< [rad/sec], rate gyro bias estimate
	double Pp[3];					///< [rad^2], covariance estimate for position
	double Pv[3];					///< [rad^2], covariance estimate for velocity
	double Pa[3];					///< [rad^2], covariance estimate for angles
	double Pab[3];					///< [(m/sec^2)^2], covariance estimate for accelerometer bias
	double Pgb[3];					///< [(rad/sec)^2], covariance estimate for rate gyro bias
	enum errdefs err_type;			///< GPS-aided INS filter status
	double gpsmu_innov_covar[6];	///< diagonal elements of innovation covariance H*P*H'+R from GPS measurement update
	double gpsmu_innov[6];			///< innovation from GPS measurement update
};

/// AHRS & Dead Reckoning Navigator Data Structure
struct ahrsdr {
	double lat;						///< [rad], geodetic latitude estimate
	double lon;						///< [rad], geodetic longitude estimate
	double alt;						///< [m], altitude relative to WGS84 estimate
	double vn;						///< [m/sec], north velocity estimate
	double ve;						///< [m/sec], east velocity estimate
	double vd;						///< [m/sec], down velocity estimate
	double phi;						///< [rad], Euler roll angle estimate
	double the;						///< [rad], Euler pitch angle estimate
	double psi;						///< [rad], Euler yaw angle estimate
	double ab[3];					///< [m/sec^2], accelerometer bias estimate
	double gb[3];					///< [rad/sec], rate gyro bias estimate
	double Pp[3];					///< [rad^2], covariance estimate for position
	double Pv[3];					///< [rad^2], covariance estimate for velocity
	double Pa[3];					///< [rad^2], covariance estimate for angles
	double Pgb[3];					///< [rad^2], covariance estimate for rate gyro bias
	double wind[3]; 				///< [m/sec], wind estimate
	double Pwind[3];				///< [(m/sec)^2], covariance estimate for wind components
	double est_del_vb_bias[3];		///< [m/sec], estimate of body velocity bias
	double est_delYaw;				///< [rad] delYaw
	double est_delPitch;			///< [rad] delPitch
	double est_hoffset;				///< [m^2] Offset between barometric and GPS altitudes
	double Pdel_Yaw;				///< [rad^2] covariance estimate for del_Yaw
	double Pdel_Pitch;				///< [rad^2] covariance estimate for del_Pitch
	double Phoffset;				///< [m^2] covariance estimate forhoffset
	enum errdefs err_type;			///< AHRS filter status
	enum errdefs err_type_2;		///< DR filter status
	double gpsmu_innov_covar[6];	///< Diagonal elements of innovation covariance H*P*H'+R from GPS measureement update
	double gpsmu_innov[6];			///< Innovation from GPS measurement update
};

/// Blended Navigation Filter Data Structure (Optimally blends GPS-aided INS and AHRS-DR solutions)
struct nav {
	double lat;					///< [rad], geodetic latitude estimate
	double lon;					///< [rad], geodetic longitude estimate
	double alt;					///< [m], altitude relative to WGS84 estimate
	double vn;					///< [m/sec], north velocity estimate
	double ve;					///< [m/sec], east velocity estimate
	double vd;					///< [m/sec], down velocity estimate
	double phi;					///< [rad], Euler roll angle estimate
	double the;					///< [rad], Euler pitch angle estimate
	double psi;					///< [rad], Euler yaw angle estimate
	double gb[3];				///< [rad/sec], rate gyro bias estimate
	double ab[3];					///< [m/sec^2], accelerometer bias estimate
	double ahrsdr_att_weight;	///< Fraction of weight put on AHRS/DR attitude solution during blending
	double insgps_att_weight;	///< Fraction of weight put on GPS-aided INS attitude solution during blending
	double ahrsdr_pos_weight;	///< Fraction of weight put on AHRS/DR position and velocity solution during blending
	double insgps_pos_weight;	///< Fraction of weight put on GPS-aided INS position and velocity solution during blending
	enum errdefs err_type;		///< Blending filter status
	double time;				///< [sec], timestamp of NAV filter
};

/// Combined sensor data structure
struct sensordata {
	struct imu *imuData_ptr; 		///< pointer to imu data structure
	struct gps *gpsData_ptr;		///< pointer to gps data structure
	struct gps *gpsData_l_ptr;		///< pointer to left gps data structure
	struct gps *gpsData_r_ptr;		///< pointer to right gps data structure
	struct airdata *adData_ptr;		///< pointer to airdata data structure
	struct surface *surfData_ptr;	///< pointer to surface data structure
};

/// Datalogging data structure
struct datalog {
	char** saveAsDoubleNames;		///< pointer to char array of variable names for doubles
	double** saveAsDoublePointers;	///< pointer to double pointer array to variables that will be saved as doubles
	char** saveAsFloatNames;		///< pointer to char array of variable names for floats
	double** saveAsFloatPointers;	///< pointer to double pointer array to variables that will be saved as floats
	char** saveAsIntNames;			///< pointer to char array of variable names for ints
	int** saveAsIntPointers;		///< pointer to int32_t pointer array to variables that will be saved as ints
	char** saveAsShortNames;		///< pointer to char array of variable names for shorts
	unsigned short** saveAsShortPointers;	///< pointer to uint16_t pointer array to variables that will be saved as shorts
	int logArraySize; 	///< Number of data points in the logging array. 50 Hz * 60 sec/min * 30 minutes = 90000
	int numDoubleVars;	///< Number of variables that will be logged as doubles
	int numFloatVars;	///< Number of variables that will be logged as floats
	int numIntVars;		///< Number of variables that will be logged as ints
	int numShortVars;	///< Number of variables that will be logged as shorts
};

// ****** Aircraft-specific settings *****************************************************
/// Roll and pitch angle digital controller - parameters and variables, Altitude, & Speed Controller Gains
#ifdef AIRCRAFT_THOR
	static double roll_gain[3]  = {-0.64,-0.20,-0.07};  // PI gains for roll tracker and roll damper
	static double pitch_gain[3] = {-0.90,-0.30,-0.08};  // PI gains for theta tracker and pitch damper
	double base_pitch_cmd= 0.0872664;  // (Thor Trim value) use 5 deg (0.0872664 rad) for flight, use 3.082 deg (0.0537910 rad) in sim
	static double alt_gain[2] 	= {0.023,0.0010}; 		// PI gains for altitude tracker
	static double v_gain[2] 	= {0.15, 0.040};		// PI gains for speed tracker
	static double head_gain 	= 1.5;					// P gain for heading tracker
#endif
#ifdef AIRCRAFT_TYR
	static double roll_gain[3]  = {-0.64,-0.20,-0.07};  // PI gains for roll tracker and roll damper
	static double pitch_gain[3] = {-0.90,-0.30,-0.08};  // PI gains for theta tracker and pitch damper
	double base_pitch_cmd= 0.0872664;  // (Faser Trim value) use 5 deg (0.0872664  rad) for flight, use 4.669 deg (0.0814990 rad) in sim
	static double alt_gain[2] 	= {0.023,0.0010}; 		// PI gains for altitude tracker
	static double v_gain[2] 	= {0.15, 0.040};		// PI gains for speed tracker
	static double head_gain 	= 1.5;					// P gain for heading tracker
#endif
#ifdef AIRCRAFT_FASER
	static double roll_gain[3]  = {-0.52,-0.20,-0.07};  // PI gains for roll tracker and roll damper
	static double pitch_gain[3] = {-0.84,-0.23,-0.08};  // PI gains for theta tracker and pitch damper
	double base_pitch_cmd= 0.0872664;  // (Faser Trim value) use 5 deg (0.0872664  rad) for flight, use 4.669 deg (0.0814990 rad) in sim
	static double alt_gain[2] 	= {0.021,0.0017};
	static double v_gain[2] 	= {0.091, 0.020};
	static double head_gain 	= 1.2;
#endif
#ifdef AIRCRAFT_IBIS
	static double roll_gain[3]  = {-0.52,-0.20,-0.07};  // PI gains for roll tracker and roll damper
	static double pitch_gain[3] = {-0.84,-0.23,-0.08};  // PI gains for theta tracker and pitch damper
	double base_pitch_cmd= 0.0872664;  // (Faser Trim value) use 5 deg (0.0872664  rad) for flight, use 4.669 deg (0.0814990 rad) in sim
	static double alt_gain[2] 	= {0.021,0.0017};
	static double v_gain[2] 	= {0.091, 0.020};
	static double head_gain 	= 1.2;
#endif
#ifdef AIRCRAFT_BALDR
	static double roll_gain[3]  = {-0.52,-0.20,-0.07};  // PI gains for roll tracker and roll damper
	static double pitch_gain[3] = {-0.84,-0.23,-0.08};  // PI gains for theta tracker and pitch damper
	double base_pitch_cmd= 0.0872664;  // (Faser Trim value) use 5 deg (0.0872664  rad) for flight, use 4.669 deg (0.0814990 rad) in sim
	static double alt_gain[2] 	= {0.021,0.0017};
	static double v_gain[2] 	= {0.091, 0.020};
	static double head_gain 	= 1.2;
#endif
#ifdef HIL_SIM
	static double roll_gain[3]  = {-0.52,-0.20,-0.07};  // PI gains for roll tracker and roll damper
	static double pitch_gain[3] = {-0.84,-0.23,-0.08};  // PI gains for theta tracker and pitch damper
	double base_pitch_cmd= 0.0907;  // (Faser Trim value) use 5 deg (0.0872664  rad) for flight, use 4.669 deg (0.0814990 rad) in sim
#endif

#endif /* SOURCE_GLOBALDEFS_H_ */
