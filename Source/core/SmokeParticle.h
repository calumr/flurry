// SmokeParticle.h: interface for the SmokeParticle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SMOKEPARTICLE_H)
#define SMOKEPARTICLE_H

typedef union { float f[4]; } floatToVector;

typedef union { unsigned int i[4]; } intToVector;

typedef struct SmokeParticleV {
    floatToVector color[4];
    floatToVector position[3];
    floatToVector oldposition[3];
    floatToVector delta[3];
    intToVector dead;
    floatToVector time;
    intToVector animFrame;
} SmokeParticleV;

#endif  // !defined(SMOKEPARTICLE_H)
