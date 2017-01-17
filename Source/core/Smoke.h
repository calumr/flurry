// Smoke.h: interface for the Smoke class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SMOKE_H)
#define SMOKE_H

#include "SmokeParticle.h"

#define NUMSMOKEPARTICLES 3600

typedef struct SmokeV  
{
	SmokeParticleV p[NUMSMOKEPARTICLES/4];
	int nextParticle;
        int nextSubParticle;
	float lastParticleTime;
	int firstTime;
	long frame;
	float old[3];
        floatToVector seraphimVertices[NUMSMOKEPARTICLES*2+1];
        floatToVector seraphimColors[NUMSMOKEPARTICLES*4+1];
	float seraphimTextures[NUMSMOKEPARTICLES*2*4];
} SmokeV;

__private_extern__ void InitSmoke(SmokeV *s);

__private_extern__ void UpdateSmoke_ScalarBase(SmokeV *s);
#ifdef __ppc__
__private_extern__ void UpdateSmoke_ScalarFrsqrte(SmokeV *s);
#endif //__ppc__
#ifdef __VEC__
__private_extern__ void UpdateSmoke_VectorBase(SmokeV *s);
__private_extern__ void UpdateSmoke_VectorUnrolled(SmokeV *s);
#endif //__VEC__

__private_extern__ void DrawSmoke_Scalar(SmokeV *s);
__private_extern__ void DrawSmoke_Vector(SmokeV *s);

#endif // !defined(SMOKE_H)
