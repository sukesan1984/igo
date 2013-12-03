//
//  BanTest.m
//  igo
//
//  Created by Kosuke Takami on 2013/12/02.
//
//

#import <XCTest/XCTest.h>
#import "Ban.h"

@interface BanTest : XCTestCase

@end

@implementation BanTest

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}


- (void)testGetTouchedPos
{
    Ban* ban = Ban::create("ban.png");
    ban->setScale(0.55);
    
    XCTAssertEqual(CCPoint(0, 0), ban->getTouchedPos(ccp(19.2, 99.2)));
    XCTAssertEqual(CCPoint(4, 4), ban->getTouchedPos(ccp(160, 240)));
    //XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
}

@end
