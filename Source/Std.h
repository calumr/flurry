//-------------------------------------------------------------------
//  File:   Std.h
//  Created:  02/12/00 9:01:PM
//  Author:   Aaron Hilton
//  Comments: Standard header file to include all source files.
//            (Precompiled header)
//-------------------------------------------------------------------
#ifndef __STD_h_
#define __STD_h_

#include <Carbon/Carbon.h>
#include <OpenGL/glu.h>

#include "PTypes.h"
#include "Gl_saver.h"

//#define FastDistance2D(x,y) hypot(x,y)

__private_extern__ float FastDistance2D(float x, float y);
#ifdef __VEC__
__private_extern__ inline vector float FastDistance2DV(vector float x, vector float y);
#endif __VEC__

#define RandFlt(min, max) (min + (max - min) * rand() / (float) RAND_MAX)

#define RandBell(scale) (scale * (1.0f - (rand() + rand() + rand()) / ((float) RAND_MAX * 1.5f)))

#endif // _STD_h_
