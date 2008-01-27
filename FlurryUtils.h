#import <Cocoa/Cocoa.h>
#import <ScreenSaver/ScreenSaver.h>
#import "Gl_saver.h"

#define RANDOM_PRESET_KEY @"randomPreset"
#define RANDOM_DISPLAY_KEY @"randomDisplay"
#define VERSION_STRING [[[NSBundle bundleWithIdentifier:@"com.calumr.Flurry"] infoDictionary] \
								objectForKey:@"CFBundleShortVersionString"]

#define UPDATE_COLOUR_NOTIF @"updateColours"
#define COLOUR_REFRESH_INTERVAL 0.1

@interface Flurry : NSObject <NSCoding, NSCopying> {
	global_info_t *flurry_info;
	NSString *name;
	unsigned int randomFactor;
	unsigned int screens;
}

+ (Flurry *)flurryWithStreams:(int)s colour:(ColorModes)c thickness:(float)t speed:(float)sp;

- (NSString *)name;
- (void)setName:(NSString *)newName;
- (id)colour;
- (NSNumber *)streamCount;
- (void)setStreamCount:(NSNumber *)newStreamCount;
- (global_info_t *)info;

- (void)randomiseDisplays:(BOOL)goRandom;

- (void)setDraws:(BOOL)doesDraw onScreen:(int)screen;
- (BOOL)shouldDrawOnScreenIndex:(int)index randomise:(BOOL)randomise;
- (BOOL)shouldDrawOnScreen:(NSScreen *)screen randomise:(BOOL)randomise;
- (BOOL)shouldDrawInView:(NSView *)view randomise:(BOOL)randomise;
@end

@interface FlurryPreset : NSObject <NSCoding, NSCopying> {
	NSString *name;
	NSMutableArray *flurries;
	NSString *shortcut;
}

+ (FlurryPreset *)classicFlurryPreset;
+ (FlurryPreset *)rgbFlurryPreset;
+ (FlurryPreset *)waterFlurryPreset;
+ (FlurryPreset *)fireFlurryPreset;
+ (FlurryPreset *)psychedelicFlurryPreset;

- (void)addFlurry:(Flurry *)flurry;
- (void)deleteFlurry:(Flurry *)flurry;
- (NSArray *)flurries;
- (NSString *)name;
- (void)setName:(NSString *)newName;
- (NSString *)shortcut;
- (void)setShortcut:(NSString *)newShortcut;
@end

@interface FlurryColour : NSColor {
	Flurry *flurry;
}
- (Flurry *)flurry;
- (void)setFlurry:(Flurry *)new_flurry;
@end

@interface ColourCell : NSCell { }
@end

@interface FlurryOpenGLView : NSOpenGLView { }
@end
