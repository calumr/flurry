// Spark.cpp: implementation of the Spark class.
//
//////////////////////////////////////////////////////////////////////

#include "Std.h"
#include "Spark.h"

void InitSpark(Spark *s)
{
	int i;
	for (i=0;i<3;i++)
	{
		s->position[i] = RandFlt(-100.0, 100.0);
	}
}

#define BIGMYSTERY 1800.0
#define MAXANGLES 16384

void UpdateSparkColour(Spark *s)
{
	const float rotationsPerSecond = (float) (2.0*PI*fieldSpeed/MAXANGLES);
	double thisPointInRadians;
	double thisAngle = info->fTime*rotationsPerSecond;
	float cycleTime = 20.0f;
	float colorRot;
	float redPhaseShift;
	float greenPhaseShift; 
	float bluePhaseShift;
	float baseRed;
	float baseGreen;
	float baseBlue;
	float colorTime;
	
	if (info->currentColorMode == rainbowColorMode)
	{
		cycleTime = 1.5f;
	}
	else if (info->currentColorMode == tiedyeColorMode)
	{
		cycleTime = 4.5f;
	}
	else if (info->currentColorMode == cyclicColorMode)
	{
		cycleTime = 20.0f;
	}
	else if (info->currentColorMode == slowCyclicColorMode)
	{
		cycleTime = 120.0f;
	}
	colorRot = (float) (2.0*PI/cycleTime);
	redPhaseShift = 0.0f; //cycleTime * 0.0f / 3.0f 
	greenPhaseShift = cycleTime / 3.0f; 
	bluePhaseShift = cycleTime * 2.0f / 3.0f ;
	if (info->currentColorMode == whiteColorMode)
	{
		baseRed = 0.1875f;
		baseGreen = 0.1875f;
		baseBlue = 0.1875f;
	}
	else if (info->currentColorMode == multiColorMode)
	{
		baseRed = 0.0625f;
		baseGreen = 0.0625f;
		baseBlue = 0.0625f;
	}
	else if (info->currentColorMode == darkColorMode)
	{
		baseRed = 0.0f;
		baseGreen = 0.0f;
		baseBlue = 0.0f;
	}
	else
	{
		if (info->currentColorMode < slowCyclicColorMode)
		{
			colorTime = (info->currentColorMode / 6.0f) * cycleTime;
		}
		else
		{
			colorTime = info->fTime + info->flurryRandomSeed;
		}
		baseRed = 0.109375f * ((float) cos((colorTime+redPhaseShift)*colorRot)+1.0f);
		baseGreen = 0.109375f * ((float) cos((colorTime+greenPhaseShift)*colorRot)+1.0f);
		baseBlue = 0.109375f * ((float) cos((colorTime+bluePhaseShift)*colorRot)+1.0f);
	}

	thisPointInRadians = 2.0 * PI * (double) s->mystery / (double) BIGMYSTERY;
	
	s->color[0] = baseRed + 0.0625f * (0.5f + (float) cos((15.0 * (thisPointInRadians + 3.0*thisAngle))) + (float) sin((7.0 * (thisPointInRadians + thisAngle))));
	s->color[1] = baseGreen + 0.0625f * (0.5f + (float) sin(((thisPointInRadians) + thisAngle)));
	s->color[2] = baseBlue + 0.0625f * (0.5f + (float) cos((37.0 * (thisPointInRadians + thisAngle))));
}

void UpdateSpark(Spark *s)
{
    const float rotationsPerSecond = (float) (2.0*PI*fieldSpeed/MAXANGLES);
    double thisPointInRadians;
    double thisAngle = info->fTime*rotationsPerSecond;
    float cf;
    int i;
    double tmpX1,tmpY1,tmpZ1;
    double tmpX2,tmpY2,tmpZ2;
    double tmpX3,tmpY3,tmpZ3;
    double tmpX4,tmpY4,tmpZ4;
    double rotation;
    double cr;
    double sr;
    float cycleTime = 20.0f;
    float colorRot;
    float redPhaseShift;
    float greenPhaseShift; 
    float bluePhaseShift;
    float baseRed;
    float baseGreen;
    float baseBlue;
    float colorTime;
    
    float old[3];
    
    if (info->currentColorMode == rainbowColorMode) {
        cycleTime = 1.5f;
    } else if (info->currentColorMode == tiedyeColorMode) {
        cycleTime = 4.5f;
    } else if (info->currentColorMode == cyclicColorMode) {
        cycleTime = 20.0f;
    } else if (info->currentColorMode == slowCyclicColorMode) {
        cycleTime = 120.0f;
    }
    colorRot = (float) (2.0*PI/cycleTime);
    redPhaseShift = 0.0f; //cycleTime * 0.0f / 3.0f 
    greenPhaseShift = cycleTime / 3.0f; 
    bluePhaseShift = cycleTime * 2.0f / 3.0f ;
    if (info->currentColorMode == whiteColorMode) {
        baseRed = 0.1875f;
        baseGreen = 0.1875f;
        baseBlue = 0.1875f;
    } else if (info->currentColorMode == multiColorMode) {
        baseRed = 0.0625f;
        baseGreen = 0.0625f;
        baseBlue = 0.0625f;
    } else if (info->currentColorMode == darkColorMode) {
        baseRed = 0.0f;
        baseGreen = 0.0f;
        baseBlue = 0.0f;
    } else {
        if(info->currentColorMode < slowCyclicColorMode) {
            colorTime = (info->currentColorMode / 6.0f) * cycleTime;
        } else {
            colorTime = info->fTime + info->flurryRandomSeed;
        }
        baseRed = 0.109375f * ((float) cos((colorTime+redPhaseShift)*colorRot)+1.0f);
        baseGreen = 0.109375f * ((float) cos((colorTime+greenPhaseShift)*colorRot)+1.0f);
        baseBlue = 0.109375f * ((float) cos((colorTime+bluePhaseShift)*colorRot)+1.0f);
    }
    
    for (i=0;i<3;i++) {
        old[i] = s->position[i];
    }
    
    cf = ((float) (cos(7.0*((info->fTime)*rotationsPerSecond))+cos(3.0*((info->fTime)*rotationsPerSecond))+cos(13.0*((info->fTime)*rotationsPerSecond))));
    cf /= 6.0f;
    cf += 2.0f;
    thisPointInRadians = 2.0 * PI * (double) s->mystery / (double) BIGMYSTERY;
    
    s->color[0] = baseRed + 0.0625f * (0.5f + (float) cos((15.0 * (thisPointInRadians + 3.0*thisAngle))) + (float) sin((7.0 * (thisPointInRadians + thisAngle))));
    s->color[1] = baseGreen + 0.0625f * (0.5f + (float) sin(((thisPointInRadians) + thisAngle)));
    s->color[2] = baseBlue + 0.0625f * (0.5f + (float) cos((37.0 * (thisPointInRadians + thisAngle))));
    s->position[0] = fieldRange * cf * (float) cos(11.0 * (thisPointInRadians + (3.0*thisAngle)));
    s->position[1] = fieldRange * cf * (float) sin(12.0 * (thisPointInRadians + (4.0*thisAngle)));
    s->position[2] = fieldRange * (float) cos((23.0 * (thisPointInRadians + (12.0*thisAngle))));
    
    rotation = thisAngle*0.501 + 5.01 * (double) s->mystery / (double) BIGMYSTERY;
    cr = cos(rotation);
    sr = sin(rotation);
    tmpX1 = s->position[0] * cr - s->position[1] * sr;
    tmpY1 = s->position[1] * cr + s->position[0] * sr;
    tmpZ1 = s->position[2];
    
    tmpX2 = tmpX1 * cr - tmpZ1 * sr;
    tmpY2 = tmpY1;
    tmpZ2 = tmpZ1 * cr + tmpX1 * sr;
    
    tmpX3 = tmpX2;
    tmpY3 = tmpY2 * cr - tmpZ2 * sr;
    tmpZ3 = tmpZ2 * cr + tmpY2 * sr + seraphDistance;
    
    rotation = thisAngle*2.501 + 85.01 * (double) s->mystery / (double) BIGMYSTERY;
    cr = cos(rotation);
    sr = sin(rotation);
    tmpX4 = tmpX3 * cr - tmpY3 * sr;
    tmpY4 = tmpY3 * cr + tmpX3 * sr;
    tmpZ4 = tmpZ3;
    
    s->position[0] = (float) tmpX4 + RandBell(5.0f*fieldCoherence);
    s->position[1] = (float) tmpY4 + RandBell(5.0f*fieldCoherence);
    s->position[2] = (float) tmpZ4 + RandBell(5.0f*fieldCoherence);

    for (i=0;i<3;i++) {
        s->delta[i] = (s->position[i] - old[i])/info->fDeltaTime;
    }
}
