//
//  ViewController.m
//  HelloWorld
//
//  Created by Piasy on 29/07/2017.
//  Copyright © 2017 Piasy. All rights reserved.
//

#import "ViewController.h"
#import "PCUWindowManager.h"
#import "PCUiOSGuiWrapper.h"
#import "PCUiOSWindowManagerCallback.h"

@interface ViewController ()

@end

@implementation ViewController {
    PCUiOSGuiWrapper* _guiWrapper;
    PCUiOSWindowManagerCallback* _callback;
    PCUWindowManager* _manager;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    _guiWrapper = [[PCUiOSGuiWrapper alloc] initWithContainer:self.container];
    _callback = [[PCUiOSWindowManagerCallback alloc] init];
    _manager = [PCUWindowManager create:_guiWrapper callback:_callback];

    [_manager loadWindows];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onShuffle:(UIButton*)sender {
    NSString* uid = [_callback nextFc];
    NSLog(@"toggleFc %@", uid);
    NSLog(@"before %@", [_manager getWindows]);
    [_manager toggleFullscreen:uid];
    NSLog(@"after %@", [_manager getWindows]);
}
@end
