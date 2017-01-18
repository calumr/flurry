// Particle.c: implementation of the Particle class.
//
//////////////////////////////////////////////////////////////////////

#include "Std.h"
#include "Particle.h"
#define MAXANGLES 16384
extern int theTexture;


void DrawParticle(Particle *p) // the math was easier in 2D - so 2D it is
{
    float screenx = (p->x * info->sys_glWidth / p->z) + info->sys_glWidth * 0.5f;
    float screeny = (p->y * info->sys_glWidth / p->z) + info->sys_glHeight * 0.5f;
    float oldscreenx = (p->oldx * info->sys_glWidth / p->oldz) + info->sys_glWidth * 0.5f;
    float oldscreeny = (p->oldy * info->sys_glWidth / p->oldz) + info->sys_glHeight * 0.5f;
    
    // near clip
    if(p->z < 100.0f) {
        InitParticle(p);
        return;
    }
    
    // side clip
    if(screenx > info->sys_glWidth + 100.0f || screenx < -100.0f) {
        InitParticle(p);
        return;
    }
    
    // vertical clip
    if(screeny > info->sys_glHeight + 100.0f || screeny < -100.0f) {
        InitParticle(p);
        return;
    }
    
    info->starfieldColor[info->starfieldColorIndex++] = p->r;
    info->starfieldColor[info->starfieldColorIndex++] = p->g;
    info->starfieldColor[info->starfieldColorIndex++] = p->b;
    info->starfieldColor[info->starfieldColorIndex++] = 1.0f;
    info->starfieldColor[info->starfieldColorIndex++] = p->r;
    info->starfieldColor[info->starfieldColorIndex++] = p->g;
    info->starfieldColor[info->starfieldColorIndex++] = p->b;
    info->starfieldColor[info->starfieldColorIndex++] = 1.0f;
    info->starfieldColor[info->starfieldColorIndex++] = p->r;
    info->starfieldColor[info->starfieldColorIndex++] = p->g;
    info->starfieldColor[info->starfieldColorIndex++] = p->b;
    info->starfieldColor[info->starfieldColorIndex++] = 1.0f;
    info->starfieldColor[info->starfieldColorIndex++] = p->r;
    info->starfieldColor[info->starfieldColorIndex++] = p->g;
    info->starfieldColor[info->starfieldColorIndex++] = p->b;
    info->starfieldColor[info->starfieldColorIndex++] = 1.0f;
    
    p->animFrame++;
    if (p->animFrame == 64) {
        p->animFrame = 0;
    }
    
    {
        float dx = (screenx-oldscreenx);
        float dy = (screeny-oldscreeny);
        float m = FastDistance2D(dx, dy);
        float u0 = (p->animFrame) * 0.125f;
        float v0 = (p->animFrame>>3) * 0.125f;
        float u1 = u0 + 0.125f;
        float v1 = v0 + 0.125f;
        float size = (3500.0f*(info->sys_glWidth/1024.0f));
        float w = max(1.5f,size/p->z);
        float ow = max(1.5f,size/p->oldz);
        float d = FastDistance2D(dx, dy);
        float s, os, dxs, dys, dxos, dyos, dxm, dym;
        
        if(d) {
            s = w/d;
        } else {
            s = 0.0f;
        }
        
        if(d) {
            os = ow/d;
        } else {
            os = 0.0f;
        }
        
        m = 2.0f + s; 
        
        dxs = dx*s;
        dys = dy*s;
        dxos = dx*os;
        dyos = dy*os;
        dxm = dx*m;
        dym = dy*m;
                
        info->starfieldTextures[info->starfieldTexturesIndex++] = u0;
        info->starfieldTextures[info->starfieldTexturesIndex++] = v0;
        info->starfieldVertices[info->starfieldVerticesIndex++] = screenx+dxm-dys;
        info->starfieldVertices[info->starfieldVerticesIndex++] = screeny+dym+dxs;
        info->starfieldTextures[info->starfieldTexturesIndex++] = u0;
        info->starfieldTextures[info->starfieldTexturesIndex++] = v1;
        info->starfieldVertices[info->starfieldVerticesIndex++] = screenx+dxm+dys;
        info->starfieldVertices[info->starfieldVerticesIndex++] = screeny+dym-dxs;
        info->starfieldTextures[info->starfieldTexturesIndex++] = u1;
        info->starfieldTextures[info->starfieldTexturesIndex++] = v1;
        info->starfieldVertices[info->starfieldVerticesIndex++] = oldscreenx-dxm+dyos;
        info->starfieldVertices[info->starfieldVerticesIndex++] = oldscreeny-dym-dxos;
        info->starfieldTextures[info->starfieldTexturesIndex++] = u1;
        info->starfieldTextures[info->starfieldTexturesIndex++] = v0;
        info->starfieldVertices[info->starfieldVerticesIndex++] = oldscreenx-dxm-dyos;
        info->starfieldVertices[info->starfieldVerticesIndex++] = oldscreeny-dym+dxos;
    }
}

void UpdateParticle(Particle *p)
{
	p->oldx = p->x;
	p->oldy = p->y;
	p->oldz = p->z;

	p->x += p->deltax*info->fDeltaTime;
	p->y += p->deltay*info->fDeltaTime;
	p->z += p->deltaz*info->fDeltaTime;
}

void InitParticle(Particle *p)
{
//	float tempx,tempy;
	int r1,r2;
	p->oldz = RandFlt(2500.0f,22500.0f);
//	do
//	{
		r1 = rand();
		r2 = rand();
		p->oldx = ((float) (r1 % (int) info->sys_glWidth) - info->sys_glWidth * 0.5f) / 
								(info->sys_glWidth / p->oldz);
		p->oldy = (info->sys_glHeight * 0.5f - (float) (r2 % (int) info->sys_glHeight)) / 
								(info->sys_glWidth / p->oldz);
//		tempx = (oldx * info->sys_glWidth / 75.0f) + info->sys_glWidth/2.0f;
//		tempy = (oldy * info->sys_glWidth / 75.0f) + info->sys_glHeight/2.0f;
//	} while (fabs(tempx) < info->sys_glWidth + 100.0 && fabs(tempy) < info->sys_glHeight + 100.0);
	p->deltax = 0.0f;
	p->deltay = 0.0f;
	p->deltaz = (float) -starSpeed;
	p->x = p->oldx + p->deltax;
	p->y = p->oldy + p->deltay;
	p->z = p->oldz + p->deltaz;
	p->r = RandFlt(0.125f,1.0f);
	p->g = RandFlt(0.125f,1.0f);
	p->b = RandFlt(0.125f,1.0f);
	p->animFrame = 0;
}
