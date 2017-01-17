// Star.c: implementation of the Star class.
//
//////////////////////////////////////////////////////////////////////

#include "Std.h"
#include "Star.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

__private_extern__ void InitStar(Star *s)
{
    int i;
    for (i=0;i<3;i++) {
        s->position[i] = RandFlt(-10000.0, 10000.0);
    }
    s->rotSpeed = RandFlt(0.4, 0.9);
    s->mystery = RandFlt(0.0, 10.0);
}

__private_extern__ void DrawStar(Star *s)
{
    float width,sx,sy;
    float w,z;
    float screenx;
    float screeny;
    float scale;
    float a;
    float c = 0.08f;
    float r,g,b;
    int k;
    
    const float black[4] = {0.0f,0.0f,0.0f,1.0f};

    if(s->ate == false) {
        return;
    }

    width = 50000.0f * info->sys_glWidth / 1024.0f;
    
    z = s->position[2];
    sx = s->position[0] * info->sys_glWidth / z + info->sys_glWidth * 0.5f;
    sy = s->position[1] * info->sys_glWidth / z + info->sys_glHeight * 0.5f;
    w = width*4.0f / z;
    
    screenx = sx;
    screeny = sy;
    
    glPushMatrix();
    glTranslatef(screenx,screeny,0.0f);
    scale = w/100.0f;
    glScalef(scale,scale,0.0f);
    for (k=0;k<30;k++) {
        a = ((float) (rand() % 3600)) / 10.0f;
        glRotatef(a,0.0f,0.0f,1.0f);
        glBegin(GL_QUAD_STRIP);
        glColor4fv(black);
        glVertex2f(-3.0f,0.0f);
        a = 3.0f + (float) (rand() & 2047) * c;
        glVertex2f(-3.0f,a);
        r = 0.125f + (float) (rand() % 875) / 1000.0f;
        g = 0.125f + (float) (rand() % 875) / 1000.0f;
        b = 0.125f + (float) (rand() % 875) / 1000.0f;
        glColor4f(r,g,b,1.0f);
        glVertex2f(0.0f,0.0f);
        glColor4fv(black);
        glVertex2f(0.0f,a);
        glVertex2f(3.0f,0.0f);
        glVertex2f(3.0f,a);
        glEnd();
    }
    glPopMatrix();
}

#define BIGMYSTERY 1800.0
#define MAXANGLES 16384

__private_extern__ void UpdateStar(Star *s)
{
    float rotationsPerSecond = (float) (2.0*PI*12.0/MAXANGLES) * s->rotSpeed /* speed control */;
    double thisPointInRadians;
    double thisAngle = info->fTime*rotationsPerSecond;
    float cf;
    double tmpX1,tmpY1,tmpZ1;
    double tmpX2,tmpY2,tmpZ2;
    double tmpX3,tmpY3,tmpZ3;
    double tmpX4,tmpY4,tmpZ4;
    double rotation;
    double cr;
    double sr;

    s->ate = false;
    
    cf = ((float) (cos(7.0*((info->fTime)*rotationsPerSecond))+cos(3.0*((info->fTime)*rotationsPerSecond))+cos(13.0*((info->fTime)*rotationsPerSecond))));
    cf /= 6.0f;
    cf += 0.75f; 
    thisPointInRadians = 2.0 * PI * (double) s->mystery / (double) BIGMYSTERY;
    
    s->position[0] = 250.0f * cf * (float) cos(11.0 * (thisPointInRadians + (3.0*thisAngle)));
    s->position[1] = 250.0f * cf * (float) sin(12.0 * (thisPointInRadians + (4.0*thisAngle)));
    s->position[2] = 250.0f * (float) cos((23.0 * (thisPointInRadians + (12.0*thisAngle))));
    
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
    
    s->position[0] = (float) tmpX4;
    s->position[1] = (float) tmpY4;
    s->position[2] = (float) tmpZ4;
}
