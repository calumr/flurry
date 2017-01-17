// Precompiled "Std" Include Header.

#include "Std.h"

//UInt8  sys_glBPP=32;
//int SSMODE = FALSE;
//int currentVideoMode = 0;
//int cohesiveness = 7;
//int fieldStrength;
//int colorCoherence = 7;
//int fieldIncoherence = 0;
//int ifieldSpeed = 120;

__private_extern__ float FastDistance2D(float x, float y)
{
	// this function computes the distance from 0,0 to x,y with ~3.5% error
	float mn;
	// first compute the absolute value of x,y
	x = (x < 0.0f) ? -x : x;
	y = (y < 0.0f) ? -y : y;
	
	// compute the minimum of x,y
	mn = x<y?x:y;
	
	// return the distance
	return(x+y-(mn*0.5f)-(mn*0.25f)+(mn*0.0625f));
	
}

#ifdef __VEC__

__private_extern__ inline vector float FastDistance2DV(vector float x, vector float y) {
    vector float mn, temp;
    
    x = vec_abs(x);
    y = vec_abs(y);
    mn = vec_min(x,y);
    temp = vec_add(x,y);
    temp = vec_madd(mn, (vector float)(-0.6875), temp);
    return temp;
}

#endif //__VEC__

