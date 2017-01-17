#import "FlurryUtils.h"


@implementation FlurryPreset

+ (FlurryPreset *)classicFlurryPreset
{
	FlurryPreset *fp = [[FlurryPreset alloc] init];
	[fp setName:@"Classic Flurry"];
	[fp setShortcut:@"1"];
	[fp addFlurry:[[Flurry alloc] init]];
	return fp;
}

+ (FlurryPreset *)rgbFlurryPreset
{
	FlurryPreset *fp = [[FlurryPreset alloc] init];
	[fp setName:@"RGB Flurry"];
	[fp setShortcut:@"2"];
	[fp addFlurry:[Flurry flurryWithStreams:3 colour:redColorMode thickness:100.0 speed:0.8]];
	[fp addFlurry:[Flurry flurryWithStreams:3 colour:greenColorMode thickness:100.0 speed:0.8]];
	[fp addFlurry:[Flurry flurryWithStreams:3 colour:blueColorMode thickness:100.0 speed:0.8]];
	return fp;
}

+ (FlurryPreset *)waterFlurryPreset
{
	FlurryPreset *fp = [[FlurryPreset alloc] init];
	[fp setName:@"Water"];
	[fp setShortcut:@"3"];
	[fp addFlurry:[Flurry flurryWithStreams:1 colour:blueColorMode thickness:100.0 speed:2.0]];
	[fp addFlurry:[Flurry flurryWithStreams:1 colour:blueColorMode thickness:100.0 speed:2.0]];
	[fp addFlurry:[Flurry flurryWithStreams:1 colour:blueColorMode thickness:100.0 speed:2.0]];
	[fp addFlurry:[Flurry flurryWithStreams:1 colour:blueColorMode thickness:100.0 speed:2.0]];
	[fp addFlurry:[Flurry flurryWithStreams:1 colour:blueColorMode thickness:100.0 speed:2.0]];
	[fp addFlurry:[Flurry flurryWithStreams:1 colour:blueColorMode thickness:100.0 speed:2.0]];
	[fp addFlurry:[Flurry flurryWithStreams:1 colour:blueColorMode thickness:100.0 speed:2.0]];
	[fp addFlurry:[Flurry flurryWithStreams:1 colour:blueColorMode thickness:100.0 speed:2.0]];
	[fp addFlurry:[Flurry flurryWithStreams:1 colour:blueColorMode thickness:100.0 speed:2.0]];
	return fp;
}

+ (FlurryPreset *)fireFlurryPreset
{
	FlurryPreset *fp = [[FlurryPreset alloc] init];
	[fp setName:@"Big Flurry"];
	[fp setShortcut:@"4"];
	[fp addFlurry:[Flurry flurryWithStreams:12 colour:slowCyclicColorMode thickness:10000.0 speed:0.0]];
	return fp;
}

+ (FlurryPreset *)psychedelicFlurryPreset
{
	FlurryPreset *fp = [[FlurryPreset alloc] init];
	[fp setName:@"Psychedelic"];
	[fp setShortcut:@"5"];
	[fp addFlurry:[Flurry flurryWithStreams:10 colour:rainbowColorMode thickness:200.0 speed:2.0]];
	return fp;
}

- (id)init
{
	if (self = [super init])
	{
		flurries = [[NSMutableArray alloc] init];
		name = @"Flurry Preset";
		shortcut = @"0";
	}
	return self;
}

- (id)copyWithZone:(NSZone *)zone
{
	FlurryPreset *copy = [[FlurryPreset alloc] init];
	if (copy)
	{
		int i;
		[copy setName:name];
		[copy setShortcut:shortcut];
		for (i=0;i<[flurries count];i++)
			[copy addFlurry:[(Flurry *)[flurries objectAtIndex:i] copy]];
	}
	return copy;
}

- (void)encodeWithCoder:(NSCoder *)coder
{
	[coder encodeObject:name];
	[coder encodeObject:shortcut];
	[coder encodeObject:flurries];
}

- (id)initWithCoder:(NSCoder *)coder
{
	if (self = [super init])
	{
        name = [coder decodeObject];
		shortcut = [coder decodeObject];
		flurries = [coder decodeObject];
	}
    return self;
}

- (void)addFlurry:(Flurry *)flurry
{
	[flurries addObject:flurry];
}

- (void)deleteFlurry:(Flurry *)flurry
{
	[flurries removeObject:flurry];
}


- (NSArray *)flurries {
	return flurries;
}

- (NSString *)name {
	return name;
}
- (void)setName:(NSString *)newName {
	if (name != newName)
	{
		name = newName;
	}
}

- (NSString *)shortcut {
	return shortcut;
}
- (void)setShortcut:(NSString *)newShortcut {
	if (shortcut != newShortcut)
	{
		shortcut = newShortcut;
	}
}

@end

@implementation Flurry

+ (Flurry *)flurryWithStreams:(int)s colour:(ColorModes)c thickness:(float)t speed:(float)sp
{
	Flurry *f = [[Flurry alloc] init];
	global_info_t *fInfo = [f info];
	
	fInfo->numStreams = s;
	fInfo->currentColorMode = c;
	fInfo->streamExpansion = t;
	fInfo->star->rotSpeed = sp;
	
	return f;
}

- (void)dealloc
{
	if (flurry_info)
	{
		int i;
		for (i=0;i<MAXNUMPARTICLES;i++)
		{
			free(flurry_info->p[i]);
		}
		/*for (i=0;i<NUMSMOKEPARTICLES;i++)
		{
			free(flurry_info->s->p[i]);
		}*/
		free(flurry_info->s);
		free(flurry_info->star);
		for (i=0;i<64;i++)
		{
			free(flurry_info->spark[i]);
		}
		free(flurry_info);
	}
	[[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (id)init
{
	if (self = [super init])
	{
		int i;
		
		screens = 1;
		name = @"Flurry";
		
		flurry_info = (global_info_t *)malloc(sizeof(global_info_t));
		flurry_info->flurryRandomSeed = RandFlt(0.0, 300.0);
	
		flurry_info->numStreams = 5;
		flurry_info->streamExpansion = 100;
		flurry_info->currentColorMode = tiedyeColorMode;
		
		for (i=0;i<MAXNUMPARTICLES;i++)
		{
			flurry_info->p[i] = malloc(sizeof(Particle));
		}
		
		flurry_info->s = malloc(sizeof(SmokeV));
		InitSmoke(flurry_info->s);
		
		flurry_info->star = malloc(sizeof(Star));
		InitStar(flurry_info->star);
		flurry_info->star->rotSpeed = 1.0;
		
		for (i=0;i<64;i++)
		{
			flurry_info->spark[i] = malloc(sizeof(Spark));
			InitSpark(flurry_info->spark[i]);
		}
	}
	
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateColour:)
				name:UPDATE_COLOUR_NOTIF object:NULL];
	
	return self;
}

- (id)copyWithZone:(NSZone *)zone
{
	Flurry *copy = [[Flurry alloc] init];
	if (copy)
	{
		int i;
		[copy setName:name];
		[copy info]->numStreams = flurry_info->numStreams;
		[copy info]->streamExpansion = flurry_info->streamExpansion;
		[copy info]->currentColorMode = flurry_info->currentColorMode;
		[copy info]->star->rotSpeed = flurry_info->star->rotSpeed;
		for (i=0;i<32;i++)
			[copy setDraws:[self shouldDrawOnScreenIndex:i randomise:NO] onScreen:i];
	}
	return copy;
}

- (void)encodeWithCoder:(NSCoder *)coder
{
	[coder encodeValueOfObjCType:@encode(unsigned int) at:&screens];
	[coder encodeValueOfObjCType:@encode(ColorModes) at:&flurry_info->currentColorMode];
	[coder encodeValueOfObjCType:@encode(int) at:&flurry_info->numStreams];
	[coder encodeValueOfObjCType:@encode(float) at:&flurry_info->streamExpansion];
	[coder encodeValueOfObjCType:@encode(float) at:&flurry_info->star->rotSpeed];
	[coder encodeObject:name];
}

- (id)initWithCoder:(NSCoder *)coder
{
	self = [self init];
	
	[coder decodeValueOfObjCType:@encode(unsigned int) at:&screens];
	[coder decodeValueOfObjCType:@encode(ColorModes) at:&flurry_info->currentColorMode];
	[coder decodeValueOfObjCType:@encode(int) at:&flurry_info->numStreams];
	[coder decodeValueOfObjCType:@encode(float) at:&flurry_info->streamExpansion];
	[coder decodeValueOfObjCType:@encode(float) at:&flurry_info->star->rotSpeed];
	name = [coder decodeObject];
	
    return self;
}

- (NSString *)name {
	return name;
}
- (void)setName:(NSString *)newName {
	if (name != newName)
	{
		name = newName;
	}
}

- (void)updateColour:(NSNotification *)notification
{
	info = flurry_info;
	info->fTime += COLOUR_REFRESH_INTERVAL;
	UpdateSparkColour(info->spark[0]);
}

- (id)colour {
	FlurryColour *c = [[FlurryColour alloc] init];
	[c setFlurry:self];
	return c;
}
- (void)setColour:(id)colour { }

- (NSNumber *)streamCount {
	return [NSNumber numberWithInt:flurry_info->numStreams];
}

- (void)setStreamCount:(NSNumber *)newStreamCount {
	int newIntValue = [newStreamCount intValue];
	if (newIntValue >= 0 && newIntValue < NUMSMOKEPARTICLES)
		flurry_info->numStreams = [newStreamCount intValue];
}

- (global_info_t *)info {
	return flurry_info;
}


- (void)randomiseDisplays:(BOOL)goRandom
{
	randomFactor = goRandom ? (rand() >> 3 ^ rand() >> 6) : screens;
}

- (void)setDraws:(BOOL)doesDraw onScreen:(int)screen
{
	screens = (screens & (~(1<<screen))) ^ ((doesDraw?1:0)<<screen);
}

- (BOOL)shouldDrawOnScreenIndex:(int)index randomise:(BOOL)randomise {
	return (randomise ? randomFactor : screens) & 1<<index;
}
- (BOOL)shouldDrawOnScreen:(NSScreen *)screen randomise:(BOOL)randomise {
	int index = [[NSScreen screens] indexOfObject:screen];
	return [self shouldDrawOnScreenIndex:index randomise:randomise];
}
- (BOOL)shouldDrawInView:(NSView *)view randomise:(BOOL)randomise{
	return [self shouldDrawOnScreen:[[view window] screen] randomise:randomise];
}
@end


@implementation FlurryColour
- (id)copyWithZone:(NSZone *)zone
{
	FlurryColour *c = [[FlurryColour allocWithZone:zone] init];
	[c setFlurry:flurry];
	return c;
}
- (Flurry *)flurry {
	return flurry;
}
- (void)setFlurry:(Flurry *)new_flurry {
	flurry = new_flurry;
}
- (void)set
{
	switch ([flurry info]->currentColorMode)
	{
		case redColorMode:
			[[NSColor redColor] set];
			break;
		case magentaColorMode:
			[[NSColor magentaColor] set];
			break;
		case blueColorMode:
			[[NSColor blueColor] set];
			break;
		case cyanColorMode:
			[[NSColor cyanColor] set];
			break;
		case greenColorMode:
			[[NSColor greenColor] set];
			break;
		case yellowColorMode:
			[[NSColor yellowColor] set];
			break;
		default:
			[[NSColor colorWithDeviceRed:[flurry info]->spark[0]->color[0]*3 
									green:[flurry info]->spark[0]->color[1]*3
									blue:[flurry info]->spark[0]->color[2]*3
									alpha:1.0] set];
	}
}
@end

@implementation ColourCell
- (void)drawInteriorWithFrame:(NSRect)cellFrame inView:(NSView *)controlView
{
	[[NSColor selectedControlColor] set];
	if ([self isHighlighted])
		NSRectFill(cellFrame);
	
	if ([(NSObject *)[self objectValue] isKindOfClass:[NSColor class]])
	{
		cellFrame = NSInsetRect(cellFrame, 1, 1);
		[(NSColor *)[self objectValue] drawSwatchInRect:cellFrame];
		//[[NSColor blackColor] set];
		//NSFrameRectWithWidth(cellFrame, 1);
	}
}
@end


@implementation FlurryOpenGLView
/*- (void)drawRect:(NSRect)rects
{
    NSView *superview = [self superview];
    [superview lockFocus];
    [superview drawRect:rects];
    [superview unlockFocus];
}*/
@end
