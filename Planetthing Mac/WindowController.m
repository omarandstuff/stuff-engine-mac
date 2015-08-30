#import "WindowController.h"

@interface WindowController()
{

}
@end

@implementation WindowController

- (instancetype)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    
    if (self)
    {

    }
    
    return self;
}



- (void) keyDown:(NSEvent *)event
{
    unichar c = [[event charactersIgnoringModifiers] characterAtIndex:0];
    
    switch (c)
    {
            
    }
    [super keyDown:event];
}

@end
