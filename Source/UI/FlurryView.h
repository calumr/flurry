#import <Cocoa/Cocoa.h>
#import <ScreenSaver/ScreenSaver.h>
#import "Gl_saver.h"
#import "FlurryUtils.h"
#import "PresetManager.h"

@interface FlurryView
    : ScreenSaverView<NSTableViewDataSource, NSTableViewDelegate> {
    NSOpenGLView* _glView;
    BOOL randomisePreset;
    PresetManager* presetManager;
    double _oldFrameTime;

    BOOL garbageHack;
    /*
        BUG? - When looking at a preview in System Prefernces the OpenGL view is
       full of random data from the video card (eg. click on another GL saver,
       then Flurry). For some reason, glClear in startAnimation doesn't clear.
       When garbageHack is YES, the animateOneFrame method clears the screen to
       black.
    */
}

@end
