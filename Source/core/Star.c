// Star.c: implementation of the Star class.
//
//////////////////////////////////////////////////////////////////////

#include "Std.h"
#include "Star.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void InitStar(Star* s) {
    int i;
    for (i = 0; i < 3; i++) {
        s->position[i] = RandFlt(-10000.0, 10000.0);
    }
    s->rotSpeed = RandFlt(0.4, 0.9);
    s->mystery = RandFlt(0.0, 10.0);
}

#define BIGMYSTERY 1800.0
#define MAXANGLES 16384

void UpdateStar(Star* s) {
    float rotationsPerSecond =
        (float)(2.0 * PI * 12.0 / MAXANGLES) * s->rotSpeed /* speed control */;
    double thisPointInRadians;
    double thisAngle = info->fTime * rotationsPerSecond;
    float cf;
    double tmpX1, tmpY1, tmpZ1;
    double tmpX2, tmpY2, tmpZ2;
    double tmpX3, tmpY3, tmpZ3;
    double tmpX4, tmpY4, tmpZ4;
    double rotation;
    double cr;
    double sr;

    s->ate = false;

    cf = ((float)(cos(7.0 * ((info->fTime) * rotationsPerSecond)) +
                  cos(3.0 * ((info->fTime) * rotationsPerSecond)) +
                  cos(13.0 * ((info->fTime) * rotationsPerSecond))));
    cf /= 6.0f;
    cf += 0.75f;
    thisPointInRadians = 2.0 * PI * (double)s->mystery / (double)BIGMYSTERY;

    s->position[0] =
        250.0f * cf *
        (float)cos(11.0 * (thisPointInRadians + (3.0 * thisAngle)));
    s->position[1] =
        250.0f * cf *
        (float)sin(12.0 * (thisPointInRadians + (4.0 * thisAngle)));
    s->position[2] =
        250.0f * (float)cos((23.0 * (thisPointInRadians + (12.0 * thisAngle))));

    rotation =
        thisAngle * 0.501 + 5.01 * (double)s->mystery / (double)BIGMYSTERY;
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

    rotation =
        thisAngle * 2.501 + 85.01 * (double)s->mystery / (double)BIGMYSTERY;
    cr = cos(rotation);
    sr = sin(rotation);
    tmpX4 = tmpX3 * cr - tmpY3 * sr;
    tmpY4 = tmpY3 * cr + tmpX3 * sr;
    tmpZ4 = tmpZ3;

    s->position[0] = (float)tmpX4;
    s->position[1] = (float)tmpY4;
    s->position[2] = (float)tmpZ4;
}
