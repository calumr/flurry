// Precompiled "Std" Include Header.

#include "Std.h"

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
