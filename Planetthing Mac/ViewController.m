#import "ViewController.h"

@interface ViewController()
{
     GEUpdateCaller* m_updateCaller;
}

- (void)viewDidLoad;
- (void)update:(float) time;
- (void)render;

@end

@implementation ViewController

// ------------------------------------------------------------------------------ //
// ------------------------------ View Load - Unload ---------------------------- //
// ------------------------------------------------------------------------------ //
#pragma mark View Load - Unload

- (void)viewDidLoad
{
    // Initialize the updater
    m_updateCaller = [GEUpdateCaller sharedIntance];
    
    // Initalize the Game
    [GMmain sharedIntance];
}

// ------------------------------------------------------------------------------ //
// -------------------------- Update - Render - Layout -------------------------- //
// ------------------------------------------------------------------------------ //
#pragma mark Update - Render - Layout

- (void)update:(float) time
{
    [m_updateCaller preUpdate];
    
    [m_updateCaller update:time];
    
    [m_updateCaller posUpdate];
}

- (void)render
{

    
    [m_updateCaller render];
}

- (void)layoutForWidth:(int)width andHeight:(int)height
{
    [m_updateCaller layoutForWidth:width AndHeight:height];
}

// ------------------------------------------------------------------------------ //
// -------------------------- Weird Mac initialization -------------------------- //
// ------------------------------------------------------------------------------ //
#pragma mark Weird Mac initialization

- (CVReturn)getFrameForTime:(const float)time
{
    @autoreleasepool
    {
        [self update:time];
        [self drawView];
    }
    return kCVReturnSuccess;
}

// This is the renderer output callback function
static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    CVReturn result = [(__bridge ViewController*)displayLinkContext getFrameForTime:(outputTime->hostTime - now->hostTime) / CVGetHostClockFrequency()];
    return result;
}

- (void) awakeFromNib
{
    NSOpenGLPixelFormatAttribute attrs[] =
    {
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAOpenGLProfile,
        NSOpenGLProfileVersion3_2Core,
        0
    };
    
    NSOpenGLPixelFormat *pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
    if (!pf)
    {
        NSLog(@"No OpenGL pixel format");
    }
	   
    NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil];
    
#if defined(DEBUG)
    CGLEnable([context CGLContextObj], kCGLCECrashOnRemovedFunctions);
#endif
    
    [self setPixelFormat:pf];
    [self setOpenGLContext:context];
    [self setWantsBestResolutionOpenGLSurface:YES];
}

- (void) windowWillClose:(NSNotification*)notification
{
    CVDisplayLinkStop(displayLink);
}


- (void) prepareOpenGL
{
    [super prepareOpenGL];
    
    [[self openGLContext] makeCurrentContext];
    
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    
    [self viewDidLoad];
    
    // Create a display link capable of being used with all active displays
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    
    // Set the renderer output callback function
    CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, (__bridge void*)self);
    
    // Set the display link for the current renderer
    CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
    
    // Activate the display link
    CVDisplayLinkStart(displayLink);
    
    // Register to be notified when the window closes so we can stop the displaylink
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowWillClose:) name:NSWindowWillCloseNotification object:[self window]];
}

- (void)reshape
{
    [super reshape];
    
    // We draw on a secondary thread through the display link. However, when
    // resizing the view, -drawRect is called on the main thread.
    // Add a mutex around to avoid the threads accessing the context
    // simultaneously when resizing.
    CGLLockContext([[self openGLContext] CGLContextObj]);
    
    // Get the view size in Points
    NSRect viewRectPoints = [self bounds];
    
    NSRect viewRectPixels = [self convertRectToBacking:viewRectPoints];
    
    // This view layput.
    [self layoutForWidth:viewRectPixels.size.width andHeight:viewRectPixels.size.height];
    
    CGLUnlockContext([[self openGLContext] CGLContextObj]);
}

- (void)renewGState
{
    // Called whenever graphics state updated (such as window resize)
    
    // OpenGL rendering is not synchronous with other rendering on the OSX.
    // Therefore, call disableScreenUpdatesUntilFlush so the window server
    // doesn't render non-OpenGL content in the window asynchronously from
    // OpenGL content, which could cause flickering.  (non-OpenGL content
    // includes the title bar and drawing done by the app with other APIs)
    [[self window] disableScreenUpdatesUntilFlush];
    
    [super renewGState];
}


- (void)drawRect:(NSRect)dirtyRect
{
    [self drawView];
}

- (void) drawView
{
    [[self openGLContext] makeCurrentContext];
    
    // We draw on a secondary thread through the display link
    // When resizing the view, -reshape is called automatically on the main
    // thread. Add a mutex around to avoid the threads accessing the context
    // simultaneously when resizing
    CGLLockContext([[self openGLContext] CGLContextObj]);
    
    //  Render form here bewcouse the swaping and stuff.
    [self render];
    
    
    CGLFlushDrawable([[self openGLContext] CGLContextObj]);
    CGLUnlockContext([[self openGLContext] CGLContextObj]);
}

- (void) dealloc
{
    CVDisplayLinkStop(displayLink);
    CVDisplayLinkRelease(displayLink);
}

@end
