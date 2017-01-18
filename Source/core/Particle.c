// Particle.c: implementation of the Particle class.
//
//////////////////////////////////////////////////////////////////////

#include "Std.h"
#include "Particle.h"
#define MAXANGLES 16384
extern int theTexture;

void UpdateParticle(Particle* p) {
    p->oldx = p->x;
    p->oldy = p->y;
    p->oldz = p->z;

    p->x += p->deltax * info->fDeltaTime;
    p->y += p->deltay * info->fDeltaTime;
    p->z += p->deltaz * info->fDeltaTime;
}

void InitParticle(Particle* p) {
    //	float tempx,tempy;
    int r1, r2;
    p->oldz = RandFlt(2500.0f, 22500.0f);
    //	do
    //	{
    r1 = rand();
    r2 = rand();
    p->oldx =
        ((float)(r1 % (int)info->sys_glWidth) - info->sys_glWidth * 0.5f) /
        (info->sys_glWidth / p->oldz);
    p->oldy =
        (info->sys_glHeight * 0.5f - (float)(r2 % (int)info->sys_glHeight)) /
        (info->sys_glWidth / p->oldz);
    //		tempx = (oldx * info->sys_glWidth / 75.0f) +
    // info->sys_glWidth/2.0f;
    //		tempy = (oldy * info->sys_glWidth / 75.0f) +
    // info->sys_glHeight/2.0f;
    //	} while (fabs(tempx) < info->sys_glWidth + 100.0 && fabs(tempy) <
    // info->sys_glHeight + 100.0);
    p->deltax = 0.0f;
    p->deltay = 0.0f;
    p->deltaz = (float)-starSpeed;
    p->x = p->oldx + p->deltax;
    p->y = p->oldy + p->deltay;
    p->z = p->oldz + p->deltaz;
    p->r = RandFlt(0.125f, 1.0f);
    p->g = RandFlt(0.125f, 1.0f);
    p->b = RandFlt(0.125f, 1.0f);
    p->animFrame = 0;
}
