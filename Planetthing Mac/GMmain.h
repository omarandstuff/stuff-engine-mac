#import "IHgamecenter.h"
#import "GEupdatecaller.h"
//#import "GEview.h"

@interface GMmain : NSObject <GEUpdateProtocol, GERenderProtocol>

// -------------------------------------------- //
// ---------------- Properties ---------------- //
// -------------------------------------------- //
#pragma mark Properties


// -------------------------------------------- //
// ----------------- Singleton ---------------- //
// -------------------------------------------- //
#pragma mark Sngleton
+ (instancetype)sharedIntance;

@end
