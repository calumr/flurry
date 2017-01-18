#import <GLKit/GLKit.h>
#import <OpenGL/gl.h>
#include <chrono>
#include <sys/sysctl.h>

#include "Gl_saver.h"
#include "Std.h"
#include "Smoke.h"
#include "Star.h"
#include "Spark.h"
#include "Particle.h"

// some globals
// long TimeFreq, TimeStart;
global_info_t* info = NULL;

double TimeInSecondsSinceStart(void) {
    static auto start = std::chrono::high_resolution_clock::now();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    return diff.count();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Do any initialization of the rendering context here, such as
// setting background colors, setting up lighting, or performing
// preliminary calculations.
void GLSetupRC(void) {
    int i, k;

    info->spark[0]->mystery = 1800 / 13;
    info->spark[1]->mystery = (1800 * 2) / 13;
    info->spark[2]->mystery = (1800 * 3) / 13;
    info->spark[3]->mystery = (1800 * 4) / 13;
    info->spark[4]->mystery = (1800 * 5) / 13;
    info->spark[5]->mystery = (1800 * 6) / 13;
    info->spark[6]->mystery = (1800 * 7) / 13;
    info->spark[7]->mystery = (1800 * 8) / 13;
    info->spark[8]->mystery = (1800 * 9) / 13;
    info->spark[9]->mystery = (1800 * 10) / 13;
    info->spark[10]->mystery = (1800 * 11) / 13;
    info->spark[11]->mystery = (1800 * 12) / 13;
    for (i = 0; i < NUMSMOKEPARTICLES / 4; i++) {
        for (k = 0; k < 4; k++) {
            info->s->p[i].dead.i[k] = TRUE;
        }
    }

    for (i = 0; i < 12; i++) {
        UpdateSpark(info->spark[i]);
    }

    // setup the defaults for OpenGL
    glDisable(GL_DEPTH_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glEnable(GL_ALPHA_TEST);
    glShadeModel(GL_FLAT);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);

    glViewport(0, 0, (int)info->sys_glWidth, (int)info->sys_glHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLKMatrix4 orthoMat = GLKMatrix4MakeOrtho(0, info->sys_glWidth, 0,
                                              info->sys_glHeight, 0.0, 1.0);
    glLoadMatrixf(orthoMat.m);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    info->fOldTime = TimeInSecondsSinceStart() + info->flurryRandomSeed;
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Render the OpenGL Scene here. Called by the WM_PAINT message
// handler.
void GLRenderScene(void) {
    int i;

    info->dframe++;

    info->fOldTime = info->fTime;
    info->fTime = TimeInSecondsSinceStart() + info->flurryRandomSeed;
    info->fDeltaTime = info->fTime - info->fOldTime;

    info->drag = (float)pow(0.9965, info->fDeltaTime * 85.0);

    for (i = 0; i < numParticles; i++) {
        UpdateParticle(info->p[i]);
    }
    UpdateStar(info->star);
    for (i = 0; i < info->numStreams; i++) {
        UpdateSpark(info->spark[i]);
    }

    UpdateSmoke_ScalarBase(info->s);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_TEXTURE_2D);

    DrawSmoke_Scalar(info->s);

    glDisable(GL_TEXTURE_2D);
}

void GLResize(float w, float h) {
    info->sys_glWidth = w;
    info->sys_glHeight = h;
}
