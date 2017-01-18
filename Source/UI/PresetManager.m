#import "PresetManager.h"

@implementation PresetManager

- (id)init {
    if (self = [super init]) {
        NSUserDefaults* defaults =
            [ScreenSaverDefaults defaultsForModuleWithName:@"Flurry"];
        NSData* presetsData = [defaults objectForKey:@"presets"];

        presets = [[NSMutableArray alloc] init];

        if ([[defaults objectForKey:@"version"] isEqual:VERSION_STRING] &&
            presetsData) {
            NSArray* unarchivedPresets;

            unarchivedPresets =
                [NSUnarchiver unarchiveObjectWithData:presetsData];

            [presets addObjectsFromArray:unarchivedPresets];
        } else {
            presetsData = [NSData data];
            [defaults setObject:presetsData forKey:@"presets"];
            [defaults setInteger:0 forKey:@"viewPresetIndex"];
            [defaults synchronize];
        }

        if ([presets count] == 0) {
            viewPreset = [FlurryPreset classicFlurryPreset];
            [presets addObject:viewPreset];
            [presets addObject:[FlurryPreset rgbFlurryPreset]];
            [presets addObject:[FlurryPreset waterFlurryPreset]];
            [presets addObject:[FlurryPreset fireFlurryPreset]];
            [presets addObject:[FlurryPreset psychedelicFlurryPreset]];
        } else {
            NSInteger index = [defaults integerForKey:@"viewPresetIndex"];
            if (index >= 0 && index < [presets count])
                viewPreset = [presets objectAtIndex:index];
            else
                viewPreset = [presets objectAtIndex:0];  // will never have 0
                                                         // items - so this is
                                                         // OK
        }
    }
    return self;
}

- (void)selectRandomPresetToView {
    NSUserDefaults* defaults =
        [ScreenSaverDefaults defaultsForModuleWithName:@"Flurry"];
    int index = (rand() >> 3 ^ rand() >> 6) % [presets count];
    viewPreset = [presets objectAtIndex:index];

    [defaults setInteger:index forKey:@"currentPresetIndex"];
    [defaults synchronize];
}

- (FlurryPreset*)viewPreset {
    return viewPreset;
}

@end
