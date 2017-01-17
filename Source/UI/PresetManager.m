#import "PresetManager.h"

@implementation PresetManager

- (id)init
{
	if (self = [super init])
	{
		NSUserDefaults *defaults = [ScreenSaverDefaults defaultsForModuleWithName:@"Flurry"];
		NSData *presetsData = [defaults objectForKey:@"presets"];
		
		nibLoaded = NO;
		
		presets = [[NSMutableArray alloc] init];
		
		if ([[defaults objectForKey:@"version"] isEqual:VERSION_STRING] && presetsData)
		{
			NSArray *unarchivedPresets;
			
			unarchivedPresets = [NSUnarchiver unarchiveObjectWithData:presetsData];
		
			[presets addObjectsFromArray:unarchivedPresets];
		}
		else
		{
			presetsData = [NSData data];
			[defaults setObject:presetsData forKey:@"presets"];
			[defaults setInteger:0 forKey:@"viewPresetIndex"];
			[defaults synchronize];
		}
		
		if ([presets count] == 0)
		{
			currentPreset = [FlurryPreset classicFlurryPreset];
			[presets addObject:currentPreset];
			[presets addObject:[FlurryPreset rgbFlurryPreset]];
			[presets addObject:[FlurryPreset waterFlurryPreset]];
			[presets addObject:[FlurryPreset fireFlurryPreset]];
			[presets addObject:[FlurryPreset psychedelicFlurryPreset]];
		}
		else
		{
			NSInteger index = [defaults integerForKey:@"viewPresetIndex"];
			if (index >= 0 && index < [presets count])
				currentPreset = [presets objectAtIndex:index];
			else
				currentPreset = [presets objectAtIndex:0];	// will never have 0 items - so this is OK
		}
		
		viewPreset = currentPreset;
	}
	return self;
}

- (void)selectRandomPresetToView {
	NSUserDefaults *defaults = [ScreenSaverDefaults defaultsForModuleWithName:@"Flurry"];
	int index = (rand() >> 3 ^ rand() >> 6) % [presets count];
	viewPreset = [presets objectAtIndex:index];
	
	[defaults setInteger:index forKey:@"currentPresetIndex"];
	[defaults synchronize];
}

- (void)setViewPresetToCurrent {
	viewPreset = currentPreset;
	[self refreshMenu];
}

- (FlurryPreset *)viewPreset {
	return viewPreset;
}

- (FlurryPreset *)currentPreset {
	return currentPreset;
}

- (BOOL)handleEvent:(NSEvent *)theEvent
{
	int i;
	NSString *keyCodes = [theEvent characters];
	unichar keyCode;
	
	if (keyCodes && [keyCodes length])
	{
		keyCode = [keyCodes characterAtIndex:0];
		
		for (i=0;i<[presets count];i++)
		{
			FlurryPreset *preset = [presets objectAtIndex:i];
			NSString *sc = [preset shortcut];
			if (sc && keyCode == [[preset shortcut] characterAtIndex:0])
			{
				if (viewPreset != preset)
				{
					viewPreset = preset;
					[target selectedPresetDidChange];
				}
				return YES;
			}
		}
	}
	
	return NO;
}

- (void)loadNibIfNeeded
{
	if (!nibLoaded)
        [[NSBundle mainBundle] loadNibNamed:@"EditPreset.nib" owner:self topLevelObjects:nil];
	
	[presetTable setDataSource:self];
	[presetTable setDelegate:self];
	nibLoaded = YES;
}

- (void)setTarget:(NSObject *)newTarget
{
	target = newTarget;
}

- (IBAction)changePreset:(id)sender
{
	viewPreset = currentPreset = [[popupButton selectedItem] representedObject];
	[self refreshMenu];
	[target selectedPresetDidChange];
}

- (void)refreshMenu
{
	int i;
	NSMenuItem *item;
	NSMenu *menu = [[NSMenu alloc] init];
	
	for (i=0;i<[presets count];i++)
	{
		FlurryPreset *preset = [presets objectAtIndex:i];
		item = [menu insertItemWithTitle:[preset name] action:@selector(changePreset:)
												keyEquivalent:@"" atIndex:i];
		//NSLog(@"adding %@ %i", [preset name], i+1);
		[item setTarget:self];
		[item setRepresentedObject:preset];
	}

	[menu insertItem:[NSMenuItem separatorItem] atIndex:i++];

	item = [menu insertItemWithTitle:@"Edit..."
												action:@selector(editPresets:)
												keyEquivalent:@"" atIndex:i++];
	[item setTarget:self];
	[popupButton setMenu:menu];
	
	[popupButton selectItemAtIndex:[presets indexOfObject:currentPreset]];
	
	//[target selectedPresetDidChange];
}

- (NSPopUpButton *)popupButton
{
	[self loadNibIfNeeded];
	[self refreshMenu];
	return popupButton;
}

- (void)writeDefaults
{
	NSUserDefaults *defaults = [ScreenSaverDefaults defaultsForModuleWithName:@"Flurry"];
	
	[defaults setObject:VERSION_STRING forKey:@"version"];
	[defaults setInteger:[presets indexOfObject:viewPreset] forKey:@"viewPresetIndex"];
	[defaults setObject:[NSArchiver archivedDataWithRootObject:presets] forKey:@"presets"];
	
	[defaults synchronize];
}

- (IBAction)deleteCurrentPreset:(id)sender
{
	if ([presetTable numberOfSelectedRows] < [presets count])
	{
		NSUInteger i = [presets count];
		
		// do it backwards (so we don't modify indexes of object we are about to delete)
		while (i--)
		{
			if ([presetTable isRowSelected:i])
			{
				[presets removeObjectAtIndex:i];
			}
		}
		
		[presetTable reloadData];
		
		[self refreshMenu];
	}
	else
		NSBeep();
}

- (IBAction)doneEditing:(id)sender
{
	[self refreshMenu];
	[editWindow orderOut:sender];
	[target selectedPresetDidChange];
}

- (IBAction)editPresets:(id)sender
{
	[popupButton selectItemAtIndex:[presets indexOfObject:currentPreset]];
	[presetTable reloadData];
	[editWindow makeKeyAndOrderFront:sender];
}

- (IBAction)newPreset:(id)sender
{
	int i;
	BOOL added = NO;
	NSMutableArray *newPresets = [[NSMutableArray alloc] init];
	
	for (i=0;i<[presets count];i++)
	{
		if ([presetTable isRowSelected:i])
		{
			added = YES;
			[newPresets addObject:[[presets objectAtIndex:i] copy]];
		}
	}
	
	if (added)
		[presets addObjectsFromArray:newPresets];
	else
		[presets addObject:[FlurryPreset classicFlurryPreset]];
	
	[presetTable reloadData];
	[self refreshMenu];
}

- (NSUInteger)numberOfRowsInTableView:(NSTableView *)tableView
{
	return [presets count];
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(int)row
{
	NSParameterAssert(row >= 0 && row < [presets count]);
	return [[presets objectAtIndex:row] valueForKey:[tableColumn identifier]];
}

- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(int)row
{
	NSParameterAssert(row >= 0 && row < [presets count]);
	[[presets objectAtIndex:row] setValue:object forKey:[tableColumn identifier]];
}

@end
