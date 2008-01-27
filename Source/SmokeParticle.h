// SmokeParticle.h: interface for the SmokeParticle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SMOKEPARTICLE_H)
#define SMOKEPARTICLE_H

typedef union {
    float		f[4];
#if __VEC__
    vector float	v;
#endif __VEC__
} floatToVector;

typedef union {
    unsigned int	i[4];
#if __VEC__
    vector unsigned int	v;
#endif __VEC__
} intToVector;

typedef struct SmokeParticleV  
{
	floatToVector color[4];
	floatToVector position[3];
	floatToVector oldposition[3];
	floatToVector delta[3];
	intToVector dead;
	floatToVector time;
	intToVector animFrame;
} SmokeParticleV;

#endif // !defined(SMOKEPARTICLE_H)
