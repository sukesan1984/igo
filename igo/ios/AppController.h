//
//  igoAppController.h
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

@class RootViewController;
extern "C"{
#import "GADBannerView.h"
};

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADBannerView *bannerView_;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

