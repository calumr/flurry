#import <Cocoa/Cocoa.h>
#import <ScreenSaver/ScreenSaver.h>
#import "Gl_saver.h"
#import "FlurryUtils.h"
#import "PresetManager.h"

@interface FlurryView : ScreenSaverView <NSTableViewDataSource, NSTableViewDelegate>
{
    NSOpenGLView *_glView;
    BOOL randomisePreset, randomiseDisplay;
    NSTimer *tableRefreshTimer;
    PresetManager *presetManager;
    double _oldFrameTime;
    
    BOOL garbageHack;
    /*
        BUG? - When looking at a preview in System Prefernces the OpenGL view is full of random data from the video card (eg. click on another GL saver, then Flurry). For some reason, glClear in startAnimation doesn't clear. When garbageHack is YES, the animateOneFrame method clears the screen to black. 
    */
    
    IBOutlet id presetMenuSpace;
    IBOutlet NSTableView *flurryTable;
    IBOutlet id streamCountSlider;
    IBOutlet id thicknessSlider;
    IBOutlet id speedSlider;
    IBOutlet id colourMenu;
    IBOutlet id window;
    IBOutlet id randomPresetCheckbox;
    IBOutlet id randomDisplayCheckbox;
}

- (void)writeDefaults;

- (IBAction)testNow:(id)sender;
- (IBAction)displayReadMe:(id)sender;
- (IBAction)addFlurry:(id)sender;
- (IBAction)deleteFlurry:(id)sender;
- (IBAction)saveAndCloseSheet:(id)sender;
- (IBAction)somethingChanged:(id)sender;
@end
