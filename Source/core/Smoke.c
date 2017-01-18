// Smoke.cpp: implementation of the Smoke class.
//
//////////////////////////////////////////////////////////////////////

#include "Std.h"
#include "Smoke.h"
#include "Spark.h"
#include "Star.h"

#define MAXANGLES 16384
#define NOT_QUITE_DEAD 3

#define intensity 75000.0f;

void InitSmoke(SmokeV *s)
{
    int i;
    s->nextParticle = 0;
    s->nextSubParticle = 0;
    s->lastParticleTime = 0.25f;
    s->firstTime = 1;
    s->frame = 0;
    for (i=0;i<3;i++) {
        s->old[i] = RandFlt(-100.0, 100.0);
    }
}

void UpdateSmoke_ScalarBase(SmokeV *s)
{
    int i,j,k;
    float sx = info->star->position[0];
    float sy = info->star->position[1];
    float sz = info->star->position[2];
    double frameRate;
    double frameRateModifier;


    s->frame++;

    if(!s->firstTime) {
        // release 12 puffs every frame
        if(info->fTime - s->lastParticleTime >= 1.0f / 121.0f) {
            float dx,dy,dz,deltax,deltay,deltaz;
            float f;
            float rsquared;
            float mag;

            dx = s->old[0] - sx;
            dy = s->old[1] - sy;
            dz = s->old[2] - sz;
            mag = 5.0f;
            deltax = (dx * mag);
            deltay = (dy * mag);
            deltaz = (dz * mag);
            for(i=0;i<info->numStreams;i++) {
                float streamSpeedCoherenceFactor;
                
                s->p[s->nextParticle].delta[0].f[s->nextSubParticle] = deltax;
                s->p[s->nextParticle].delta[1].f[s->nextSubParticle] = deltay;
                s->p[s->nextParticle].delta[2].f[s->nextSubParticle] = deltaz;
                s->p[s->nextParticle].position[0].f[s->nextSubParticle] = sx;
                s->p[s->nextParticle].position[1].f[s->nextSubParticle] = sy;
                s->p[s->nextParticle].position[2].f[s->nextSubParticle] = sz;
                s->p[s->nextParticle].oldposition[0].f[s->nextSubParticle] = sx;
                s->p[s->nextParticle].oldposition[1].f[s->nextSubParticle] = sy;
                s->p[s->nextParticle].oldposition[2].f[s->nextSubParticle] = sz;
                streamSpeedCoherenceFactor = max(0.0f,1.0f + RandBell(0.25f*incohesion));
                dx = s->p[s->nextParticle].position[0].f[s->nextSubParticle] - info->spark[i]->position[0];
                dy = s->p[s->nextParticle].position[1].f[s->nextSubParticle] - info->spark[i]->position[1];
                dz = s->p[s->nextParticle].position[2].f[s->nextSubParticle] - info->spark[i]->position[2];
                rsquared = (dx*dx+dy*dy+dz*dz);
                f = streamSpeed * streamSpeedCoherenceFactor;

                mag = f / (float) sqrt(rsquared);

                s->p[s->nextParticle].delta[0].f[s->nextSubParticle] -= (dx * mag);
                s->p[s->nextParticle].delta[1].f[s->nextSubParticle] -= (dy * mag);
                s->p[s->nextParticle].delta[2].f[s->nextSubParticle] -= (dz * mag);
                s->p[s->nextParticle].color[0].f[s->nextSubParticle] = info->spark[i]->color[0] * (1.0f + RandBell(colorIncoherence));
                s->p[s->nextParticle].color[1].f[s->nextSubParticle] = info->spark[i]->color[1] * (1.0f + RandBell(colorIncoherence));
                s->p[s->nextParticle].color[2].f[s->nextSubParticle] = info->spark[i]->color[2] * (1.0f + RandBell(colorIncoherence));
                s->p[s->nextParticle].color[3].f[s->nextSubParticle] = 0.85f * (1.0f + RandBell(0.5f*colorIncoherence));
                s->p[s->nextParticle].time.f[s->nextSubParticle] = info->fTime;
                s->p[s->nextParticle].dead.i[s->nextSubParticle] = FALSE;
                s->p[s->nextParticle].animFrame.i[s->nextSubParticle] = rand()&63;
                s->nextSubParticle++;
                if (s->nextSubParticle==4) {
                    s->nextParticle++;
                    s->nextSubParticle=0;
                }
                if (s->nextParticle >= NUMSMOKEPARTICLES/4) {
                    s->nextParticle = 0;
                    s->nextSubParticle = 0;
                }
            }

            s->lastParticleTime = info->fTime;
        }
    } else {
        s->lastParticleTime = info->fTime;
        s->firstTime = 0;
    }

    for(i=0;i<3;i++) {
        s->old[i] = info->star->position[i];
    }
    
    frameRate = ((double) info->dframe)/(info->fTime);
    frameRateModifier = 42.5f / frameRate;

    for(i=0;i<NUMSMOKEPARTICLES/4;i++) {        
        for(k=0; k<4; k++) {
            float dx,dy,dz;
            float f;
            float rsquared;
            float mag;
            float deltax;
            float deltay;
            float deltaz;
        
            if (s->p[i].dead.i[k]) {
                continue;
            }
            
            deltax = s->p[i].delta[0].f[k];
            deltay = s->p[i].delta[1].f[k];
            deltaz = s->p[i].delta[2].f[k];
            
            for(j=0;j<info->numStreams;j++) {
                dx = s->p[i].position[0].f[k] - info->spark[j]->position[0];
                dy = s->p[i].position[1].f[k] - info->spark[j]->position[1];
                dz = s->p[i].position[2].f[k] - info->spark[j]->position[2];
                rsquared = (dx*dx+dy*dy+dz*dz);

                f = (gravity/rsquared) * frameRateModifier;

                if ((((i*4)+k) % info->numStreams) == j) {
                    f *= 1.0f + streamBias;
                }
                
                mag = f / (float) sqrt(rsquared);
                
                deltax -= (dx * mag);
                deltay -= (dy * mag);
                deltaz -= (dz * mag);
            }
    
            // slow this particle down by info->drag
            deltax *= info->drag;
            deltay *= info->drag;
            deltaz *= info->drag;
            
            if((deltax*deltax+deltay*deltay+deltaz*deltaz) >= 25000000.0f) {
                s->p[i].dead.i[k] = TRUE;
                continue;
            }
    
            // update the position
            s->p[i].delta[0].f[k] = deltax;
            s->p[i].delta[1].f[k] = deltay;
            s->p[i].delta[2].f[k] = deltaz;
            for(j=0;j<3;j++) {
                s->p[i].oldposition[j].f[k] = s->p[i].position[j].f[k];
                s->p[i].position[j].f[k] += (s->p[i].delta[j].f[k])*info->fDeltaTime;
            }
        }
    }
}

void DrawSmoke_Scalar(SmokeV *s)
{
	int svi = 0;
	int sci = 0;
	int sti = 0;
	int si = 0;
	float width;
        float sx,sy;
	float u0,v0,u1,v1;
	float w,z;
	float screenRatio = info->sys_glWidth / 1024.0f;
	float hslash2 = info->sys_glHeight * 0.5f;
	float wslash2 = info->sys_glWidth * 0.5f;
	int i,k;

	width = (streamSize+2.5f*info->streamExpansion) * screenRatio;

	for (i=0;i<NUMSMOKEPARTICLES/4;i++)
	{
            for (k=0; k<4; k++) {
		float thisWidth;
                float oldz;
                
                if (s->p[i].dead.i[k] == TRUE) {
                    continue;
		}
		thisWidth = (streamSize + (info->fTime - s->p[i].time.f[k])*info->streamExpansion) * screenRatio;
		if (thisWidth >= width)
		{
			s->p[i].dead.i[k] = TRUE;
			continue;
		}
		z = s->p[i].position[2].f[k];
		sx = s->p[i].position[0].f[k] * info->sys_glWidth / z + wslash2;
		sy = s->p[i].position[1].f[k] * info->sys_glWidth / z + hslash2;
		oldz = s->p[i].oldposition[2].f[k];
		if (sx > info->sys_glWidth+50.0f || sx < -50.0f || sy > info->sys_glHeight+50.0f || sy < -50.0f || z < 25.0f || oldz < 25.0f)
		{
			continue;
		}

		w = max(1.0f,thisWidth/z);
		{
			float oldx = s->p[i].oldposition[0].f[k];
			float oldy = s->p[i].oldposition[1].f[k];
			float oldscreenx = (oldx * info->sys_glWidth / oldz) + wslash2;
			float oldscreeny = (oldy * info->sys_glWidth / oldz) + hslash2;
			float dx = (sx-oldscreenx);
			float dy = (sy-oldscreeny);
					
			float d = FastDistance2D(dx, dy);
			
			float sm, os, ow;
			if (d)
			{
				sm = w/d;
			}
			else
			{
				sm = 0.0f;
			}
			ow = max(1.0f,thisWidth/oldz);
			if (d)
			{
				os = ow/d;
			}
			else
			{
				os = 0.0f;
			}
			
			{
				floatToVector cmv;
                                float cm;
				float m = 1.0f + sm; 
		
				float dxs = dx*sm;
				float dys = dy*sm;
				float dxos = dx*os;
				float dyos = dy*os;
				float dxm = dx*m;
				float dym = dy*m;
		
				s->p[i].animFrame.i[k]++;
				if (s->p[i].animFrame.i[k] >= 64)
				{
					s->p[i].animFrame.i[k] = 0;
				}
		
				u0 = (s->p[i].animFrame.i[k]) * 0.125f;
				v0 = (s->p[i].animFrame.i[k]>>3) * 0.125f;
				u1 = u0 + 0.125f;
				v1 = v0 + 0.125f;
				cm = (1.375f - thisWidth/width);
				if (s->p[i].dead.i[k] == 3)
				{
					cm *= 0.125f;
					s->p[i].dead.i[k] = TRUE;
				}
				si++;
				cmv.f[0] = s->p[i].color[0].f[k]*cm;
				cmv.f[1] = s->p[i].color[1].f[k]*cm;
				cmv.f[2] = s->p[i].color[2].f[k]*cm;
				cmv.f[3] = s->p[i].color[3].f[k]*cm;

#if 0
                                // MDT we can't use vectors in the Scalar routine
                                s->seraphimColors[sci++].v = cmv.v;
                                s->seraphimColors[sci++].v = cmv.v;
                                s->seraphimColors[sci++].v = cmv.v;
                                s->seraphimColors[sci++].v = cmv.v;
#else
                                {
                                    int ii, jj;
                                    for (jj = 0; jj < 4; jj++) {
                                        for (ii = 0; ii < 4; ii++) {
                                            s->seraphimColors[sci].f[ii] = cmv.f[ii];
                                        }
                                        sci += 1;
                                    }
                                }
#endif //0
                                
                                s->seraphimTextures[sti++] = u0;
                                s->seraphimTextures[sti++] = v0;
                                s->seraphimTextures[sti++] = u0;
                                s->seraphimTextures[sti++] = v1;

                                s->seraphimTextures[sti++] = u1;
                                s->seraphimTextures[sti++] = v1;
                                s->seraphimTextures[sti++] = u1;
                                s->seraphimTextures[sti++] = v0;
                                
                                s->seraphimVertices[svi].f[0] = sx+dxm-dys;
                                s->seraphimVertices[svi].f[1] = sy+dym+dxs;
                                s->seraphimVertices[svi].f[2] = sx+dxm+dys;
                                s->seraphimVertices[svi].f[3] = sy+dym-dxs;
                                svi++;                            
                        
                                s->seraphimVertices[svi].f[0] = oldscreenx-dxm+dyos;
                                s->seraphimVertices[svi].f[1] = oldscreeny-dym-dxos;
                                s->seraphimVertices[svi].f[2] = oldscreenx-dxm-dyos;
                                s->seraphimVertices[svi].f[3] = oldscreeny-dym+dxos;
                                svi++;
			}
		}
            }
	}
	glColorPointer(4,GL_FLOAT,0,s->seraphimColors);
	glVertexPointer(2,GL_FLOAT,0,s->seraphimVertices);
	glTexCoordPointer(2,GL_FLOAT,0,s->seraphimTextures);
	glDrawArrays(GL_QUADS,0,si*4);
}

