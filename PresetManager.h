#import <Cocoa/Cocoa.h>
#import "FlurryUtils.h"

@interface NSObject (PresetMgrTarget)
- (void)selectedPresetDidChange;
@end

@interface PresetManager : NSObject
{
    NSMutableArray *presets;
	FlurryPreset *currentPreset, *viewPreset;
	NSObject *target;
	BOOL nibLoaded;
	
	IBOutlet id popupButton;
	IBOutlet id editWindow;
    IBOutlet id presetTable;
}

- (void)setViewPresetToCurrent;
- (void)selectRandomPresetToView;

- (void)setTarget:(NSObject *)newTarget;

- (BOOL)handleEvent:(NSEvent *)theEvent;

- (FlurryPreset *)viewPreset;
- (FlurryPreset *)currentPreset;
- (void)writeDefaults;

- (void)refreshMenu;
- (NSPopUpButton *)popupButton;

- (IBAction)deleteCurrentPreset:(id)sender;
- (IBAction)doneEditing:(id)sender;
- (IBAction)editPresets:(id)sender;
- (IBAction)newPreset:(id)sender;
@end
