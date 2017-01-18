#import "FlurryView.h"
#import <OpenGL/glu.h>
#import <sys/time.h>

#include <Texture.h>

//#define GL_DONE  [[_glView openGLContext] flushBuffer]
#define GL_DONE  glFlush()

__private_extern__ double CurrentTime(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    
    return time.tv_sec + (time.tv_usec / 1000000.0); 
}

@implementation FlurryView

- (id)initWithFrame:(NSRect)frameRect isPreview:(BOOL) preview
{
    if (self = [super initWithFrame:frameRect isPreview:preview])
    {
        NSOpenGLPixelFormatAttribute attribs[] =
            {
                        NSOpenGLPFAAccelerated,
                        NSOpenGLPFAColorSize, 32,
                        //NSOpenGLPFAMinimumPolicy,
                        //NSOpenGLPFADoubleBuffer, 
                        //NSOpenGLPFAClosestPolicy,
                        0
            };
        NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
        
        _glView = [[FlurryOpenGLView alloc] initWithFrame:NSZeroRect pixelFormat:format];
        [self addSubview:_glView];
		
		garbageHack = YES;
        
        OTSetup();
        
        presetManager = [[PresetManager alloc] init];
        
        randomisePreset = [[ScreenSaverDefaults defaultsForModuleWithName:@"Flurry"] 
            boolForKey:RANDOM_PRESET_KEY];
    }
	
    return self;
}

- (void)dealloc
{
    [_glView removeFromSuperview];
}

- (void)setFrameSize:(NSSize)newSize
{
    [super setFrameSize:newSize];
    [_glView setFrameSize:newSize];
    [[_glView openGLContext] makeCurrentContext];
	
    glViewport(0.0, 0.0, newSize.width, newSize.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, newSize.width, 0, newSize.width);
    glMatrixMode(GL_MODELVIEW);
    
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    GL_DONE;
}

- (void)startAnimation
{
    int i;
	
    [super startAnimation];
    [[_glView openGLContext] makeCurrentContext];
    
    MakeTexture();
    
    if (randomisePreset)
        [presetManager selectRandomPresetToView];
    
    for (i=0;i<[[[presetManager viewPreset] flurries] count];i++)
    {
        Flurry *flurry = [[[presetManager viewPreset] flurries] objectAtIndex:i];
        
        info = [flurry info];
        GLResize([_glView frame].size.width, [_glView frame].size.height);
        GLSetupRC();
    }
	
	garbageHack = YES;
    
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
	
	_oldFrameTime = TimeInSecondsSinceStart();
    
    GL_DONE;
}

- (void)animateOneFrame
{
	int i;
	double newFrameTime, alpha;
	BOOL hasDrawn = NO;
	
	if ([[self window] attachedSheet])
		return;
    
	[[_glView openGLContext] makeCurrentContext];
	
	// dim the existing screen contents
    newFrameTime = TimeInSecondsSinceStart();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    alpha = 5.0 * (newFrameTime - _oldFrameTime);
    if (alpha > 0.2) alpha = 0.2;
	
	if (garbageHack) {
		alpha = 1.0;
		garbageHack = NO;
	}
	
    glColor4f(0.0, 0.0, 0.0, alpha);
    glRectd(0, 0, [_glView frame].size.width, [_glView frame].size.height);
    _oldFrameTime = newFrameTime;
	
	for (i=0;i<[[[presetManager viewPreset] flurries] count];i++)
	{
		Flurry *flurry = [[[presetManager viewPreset] flurries] objectAtIndex:i];
		
        info = [flurry info];
        hasDrawn = YES;
        GLResize([_glView frame].size.width, [_glView frame].size.height);
        GLRenderScene();
	}
	
	if (hasDrawn)
    {
        GL_DONE;
    }
}

- (void)stopAnimation
{
    [super stopAnimation];
}

- (BOOL)hasConfigureSheet
{
    return NO;
}

- (NSWindow*)configureSheet
{
    return nil;
}

@end
