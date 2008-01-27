//-------------------------------------------------------------------
// Defines - General definitions.
// By: Aaron Hilton (c) July 1997
//-------------------------------------------------------------------
#ifndef __Defines_
#define __Defines_

//-------------------------------------------
#define sqr( X )	( (X) * (X) )	                   	// Square the X
#define PI				3.14159265358979323846f
#define DEG2RAD(X)		(PI*(X)/180.0)	// Degrees -> Radians
#define RAD2DEG(X)		((X)*180.0/PI)	// Radians -> Degrees
#define rnd()		((float)rand()*(1.0f /(Float)RAND_MAX))  // Floating point random number generator ( 0 -> 1)

// fabs: Absolute function.
//#undef abs
//#define abs(a)     ( (a) > 0 ? (a) : -(a) )

// Force sign clamping to (-1;0;1)
#define sgn(a)      ((a)<0?-1:((a)?1:0))

#ifndef max
	#define max( a, b )   ((a) > (b) ? (a) : (b))
#endif

#ifndef min
	#define min( a, b )   ((a) < (b) ? (a) : (b))
#endif

#endif
