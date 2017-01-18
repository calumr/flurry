#import <Cocoa/Cocoa.h>
#import "FlurryUtils.h"

@interface PresetManager : NSObject
{
    NSMutableArray *presets;
	FlurryPreset *viewPreset;
}

- (void)selectRandomPresetToView;

- (FlurryPreset *)viewPreset;
@end
