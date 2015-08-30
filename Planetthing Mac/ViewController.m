#import "ViewController.h"
#import "IHgamecenter.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [IHGameCenter sharedIntance];
    // Do any additional setup after loading the view.
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

@end
