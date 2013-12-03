//
//  GobanTest.m
//  igo
//
//  Created by Kosuke Takami on 2013/12/03.
//
//

#import <XCTest/XCTest.h>
#import "Goban.h"
#import "Const.h"

@interface GobanTest : XCTestCase

@end

@implementation GobanTest

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

- (void)testNew
{
    Goban* goban = new Goban();
    int i, j;
    for( i = 0; i < BAN_SIZE; i++){
        for(j=0; j < BAN_SIZE; j++){
            XCTAssertEqual(goban->goban[i][j], NONE);
        }
    }
}

@end
