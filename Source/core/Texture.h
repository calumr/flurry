/*
 *  Texture.h
 *  AppleFlurry
 *
 *  Created by Mike Trent on Wed May 22 2002.
 *  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
 *
 */

#import <OpenGL/gl.h>

// Texture builds the textures used by the Flurry streamer. The texture is loaded
// directly into OpenGL. The texture number is returned in the global variable
// named 'theTexture', and is used exclusively by the Windows code.

// Here's the global texture variable
extern GLuint theTexture;

// MakeTexture is a big do-all function that creates the textures and initializes
// the 'theTexture' global variable.
extern void MakeTexture(void);
