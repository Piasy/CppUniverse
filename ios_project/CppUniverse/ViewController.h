//
//  ViewController.h
//  HelloWorld
//
//  Created by Piasy on 29/07/2017.
//  Copyright © 2017 Piasy. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

// MARK: Properties
@property(weak, nonatomic) IBOutlet UIView* container;

// MARK: Actions
- (IBAction)onShuffle:(UIButton*)sender;

@end

