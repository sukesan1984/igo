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

- (void)testHasKokyuAround
{
    Goban* goban1 = new Goban();
    goban1->setGoishi(0, 0, WHITE);
    goban1->setGoishi(1, 0, WHITE);
    goban1->setGoishi(0, 1, WHITE);
    XCTAssertEqual(goban1->hasKokyuAround(0, 0), false);
    XCTAssertEqual(goban1->hasKokyuAround(1, 0), true);
    
    Goban* goban2 = new Goban();
    goban2->setGoishi(1, 1, WHITE);
    goban2->setGoishi(0, 1, BLACK);
    goban2->setGoishi(2, 1, BLACK);
    goban2->setGoishi(1, 0, BLACK);
    goban2->setGoishi(1, 2, BLACK);
    XCTAssertEqual(goban2->hasKokyuAround(1, 1), false);
    XCTAssertEqual(goban2->hasKokyuAround(1, 2), true);
    
    Goban* goban3 = new Goban();
    goban3->setGoishi(8, 8, WHITE);
    goban3->setGoishi(7, 8, WHITE);
    goban3->setGoishi(8, 7, BLACK);
    XCTAssertEqual(goban3->hasKokyuAround(8, 8), false);
}

@end
