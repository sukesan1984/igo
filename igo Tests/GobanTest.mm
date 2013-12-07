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

using namespace std;

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

- (void)testCanPutGoishi{
    // すでに石が置かれているところには置けない。
    Goban* goban0 = new Goban();
    goban0->setGoishi(0, 0, WHITE);
    XCTAssertEqual(goban0->canPutGoishi(0, 0, WHITE), false);
    goban0->clearCheckBoard();
    XCTAssertEqual(goban0->canPutGoishi(0, 0, BLACK), false);
    
    
    //四方を白で囲まれているので、黒は置けない。白は置ける。
    Goban* goban = new Goban();
    goban->setGoishi(0, 1, WHITE);
    goban->setGoishi(2, 1, WHITE);
    goban->setGoishi(1, 0, WHITE);
    goban->setGoishi(1, 2, WHITE);
    XCTAssertEqual(goban->canPutGoishi(1, 1, BLACK), false);
    goban->clearCheckBoard();
    XCTAssertEqual(goban->canPutGoishi(1, 1, WHITE), true);
}

- (void)testUnsetGoishi{
    Goban* goban = new Goban();
    goban->setGoishi(0, 0, WHITE);
    goban->unsetGoishi(0, 0);
    
    XCTAssertEqual(goban->getGoishi(0, 0), NONE);
}

- (void) testGetGoishi{
    Goban* goban = new Goban();
    goban->setGoishi(0, 0, WHITE);
    goban->setGoishi(0, 2, BLACK);
    
    XCTAssertEqual(goban->getGoishi(0, 0), WHITE);
    XCTAssertEqual(goban->getGoishi(0, 1), NONE);
    XCTAssertEqual(goban->getGoishi(0, 2), BLACK);
}

- (void)testTryToRemoveAround
{
    Goban* goban = new Goban();
    goban->setGoishi(1, 1, BLACK);
    goban->setGoishi(0, 1, WHITE);
    goban->setGoishi(2, 1, WHITE);
    goban->setGoishi(1, 0, WHITE);
    goban->setGoishi(1, 2, WHITE);
    
    goban->tryToRemoveAround(1, 2, WHITE);
    
    XCTAssertEqual(goban->goban[1][1], NONE);
}

- (void)testRemoveGoishi
{
    Goban* goban = new Goban();
    goban->setGoishi(0, 0, BLACK);
    goban->setGoishi(1, 0, BLACK);
    goban->setGoishi(0, 1, BLACK);
    goban->setGoishi(2, 0, WHITE);
    goban->setGoishi(3, 0, BLACK);
    
    
    goban->removeGoishi(0, 0, BLACK);
    
    XCTAssertEqual(goban->goban[0][0], NONE);
    XCTAssertEqual(goban->goban[1][0], NONE);
    XCTAssertEqual(goban->goban[0][1], NONE);
    XCTAssertEqual(goban->goban[2][0], WHITE);
    XCTAssertEqual(goban->goban[3][0], BLACK);
}

- (void)testHasKokyuAround
{
    //左に石があるだけ
    Goban* goban = new Goban();
    goban->setGoishi(1, 1, BLACK);
    goban->setGoishi(0, 1, WHITE);
    XCTAssertEqual(goban->hasKokyuAround(1, 1, BLACK), true);
    
    
    //左上隅
    //空点無し
    Goban* goban1 = new Goban();
    goban1->setGoishi(0, 0, BLACK);
    goban1->setGoishi(1, 0, WHITE);
    goban1->setGoishi(0, 1, WHITE);
    XCTAssertEqual(goban1->hasKokyuAround(0, 0, BLACK), false);
    goban1->clearCheckBoard();
    XCTAssertEqual(goban1->hasKokyuAround(1, 0, WHITE), true);
    goban1->clearCheckBoard();
    XCTAssertEqual(goban1->hasKokyuAround(0, 1, WHITE), true);
    goban1->clearCheckBoard();
    
    //空点無し。2つならび
    Goban* goban11 = new Goban();
    goban11->setGoishi(0, 0, BLACK);
    goban11->setGoishi(1, 0, BLACK);
    goban11->setGoishi(1, 1, WHITE);
    goban11->setGoishi(2, 0, WHITE);
    goban11->setGoishi(0, 1, WHITE);
    XCTAssertEqual(goban11->hasKokyuAround(0, 0, BLACK), false);
    goban11->clearCheckBoard();
    XCTAssertEqual(goban11->hasKokyuAround(1, 0, BLACK), false);
    goban11->clearCheckBoard();
    XCTAssertEqual(goban11->hasKokyuAround(1, 1, WHITE), true);
    goban11->clearCheckBoard();
    XCTAssertEqual(goban11->hasKokyuAround(2, 0, WHITE), true);
    goban11->clearCheckBoard();
    XCTAssertEqual(goban11->hasKokyuAround(0, 1, WHITE), true);
    goban11->clearCheckBoard();
    
    //空点無し。縦横3つならび
    Goban* goban13 = new Goban();
    goban13->setGoishi(0, 0, BLACK);
    goban13->setGoishi(1, 0, BLACK);
    goban13->setGoishi(0, 1, BLACK);
    goban13->setGoishi(2, 0, WHITE);
    goban13->setGoishi(1, 1, WHITE);
    goban13->setGoishi(0, 2, WHITE);
    XCTAssertEqual(goban13->hasKokyuAround(0, 0, BLACK), false);
    goban13->clearCheckBoard();
    XCTAssertEqual(goban13->hasKokyuAround(1, 0, BLACK), false);
    goban13->clearCheckBoard();
    XCTAssertEqual(goban13->hasKokyuAround(0, 1, BLACK), false);
    goban13->clearCheckBoard();
    XCTAssertEqual(goban13->hasKokyuAround(2, 0, WHITE), true);
    goban13->clearCheckBoard();
    XCTAssertEqual(goban13->hasKokyuAround(1, 1, WHITE), true);
    goban13->clearCheckBoard();
    XCTAssertEqual(goban13->hasKokyuAround(0, 2, WHITE), true);
    goban13->clearCheckBoard();
    
    //空点あり
    Goban* goban12 = new Goban();
    goban12->setGoishi(0, 0, BLACK);
    goban12->setGoishi(1, 0, BLACK);
    goban12->setGoishi(0, 1, WHITE);
    XCTAssertEqual(goban12->hasKokyuAround(0, 0, BLACK), true);
    goban12->clearCheckBoard();
    XCTAssertEqual(goban12->hasKokyuAround(1, 0, BLACK), true);
    goban12->clearCheckBoard();
    XCTAssertEqual(goban12->hasKokyuAround(0, 1, WHITE), true);
    goban12->clearCheckBoard();
    
    Goban* goban2 = new Goban();
    goban2->setGoishi(1, 1, WHITE);
    goban2->setGoishi(0, 1, BLACK);
    goban2->setGoishi(2, 1, BLACK);
    goban2->setGoishi(1, 0, BLACK);
    goban2->setGoishi(1, 2, BLACK);
    XCTAssertEqual(goban2->hasKokyuAround(1, 1, WHITE), false);
    goban2->clearCheckBoard();
    XCTAssertEqual(goban2->hasKokyuAround(0, 1, BLACK), true);
    goban2->clearCheckBoard();
    XCTAssertEqual(goban2->hasKokyuAround(2, 1, BLACK), true);
    goban2->clearCheckBoard();
    XCTAssertEqual(goban2->hasKokyuAround(1, 0, BLACK), true);
    goban2->clearCheckBoard();
    XCTAssertEqual(goban2->hasKokyuAround(1, 2, BLACK), true);
    goban2->clearCheckBoard();
    
    Goban* goban21 = new Goban();
    goban21->setGoishi(1, 1, WHITE);
    goban21->setGoishi(2, 1, WHITE);
    goban21->setGoishi(0, 1, BLACK);
    goban21->setGoishi(3, 1, BLACK);
    goban21->setGoishi(1, 0, BLACK);
    goban21->setGoishi(2, 0, BLACK);
    goban21->setGoishi(1, 2, BLACK);
    goban21->setGoishi(2, 2, BLACK);
    XCTAssertEqual(goban21->hasKokyuAround(1, 1, WHITE), false);
    goban21->clearCheckBoard();
    XCTAssertEqual(goban21->hasKokyuAround(2, 1, WHITE), false);
    goban21->clearCheckBoard();
    XCTAssertEqual(goban21->hasKokyuAround(1, 2, BLACK), true);
    goban21->clearCheckBoard();
    
    Goban* goban22 = new Goban();
    goban22->setGoishi(1, 1, WHITE);
    goban22->setGoishi(2, 1, WHITE);
    goban22->setGoishi(1, 2, WHITE);
    goban22->setGoishi(1, 0, BLACK);
    goban22->setGoishi(2, 0, BLACK);
    goban22->setGoishi(0, 1, BLACK);
    goban22->setGoishi(3, 1, BLACK);
    goban22->setGoishi(0, 2, BLACK);
    goban22->setGoishi(2, 2, BLACK);
    goban22->setGoishi(1, 3, BLACK);
    XCTAssertEqual(goban22->hasKokyuAround(1, 1, WHITE), false);
    goban22->clearCheckBoard();
    XCTAssertEqual(goban22->hasKokyuAround(2, 1, WHITE), false);
    goban22->clearCheckBoard();
    XCTAssertEqual(goban22->hasKokyuAround(1, 2, WHITE), false);
    goban22->clearCheckBoard();
    XCTAssertEqual(goban22->hasKokyuAround(1, 3, BLACK), true);
    goban22->clearCheckBoard();
    
    Goban* goban23 = new Goban();
    goban23->setGoishi(1, 1, WHITE);
    goban23->setGoishi(2, 1, WHITE);
    goban23->setGoishi(1, 2, WHITE);
    goban23->setGoishi(1, 0, WHITE);
    goban23->setGoishi(2, 0, BLACK);
    goban23->setGoishi(0, 1, BLACK);
    goban23->setGoishi(3, 1, BLACK);
    goban23->setGoishi(0, 2, BLACK);
    goban23->setGoishi(2, 2, BLACK);
    goban23->setGoishi(1, 3, BLACK);
    XCTAssertEqual(goban23->hasKokyuAround(1, 1, WHITE), true);
    goban23->clearCheckBoard();
    XCTAssertEqual(goban23->hasKokyuAround(2, 1, WHITE), true);
    goban23->clearCheckBoard();
    XCTAssertEqual(goban23->hasKokyuAround(1, 2, WHITE), true);
    goban23->clearCheckBoard();
    XCTAssertEqual(goban23->hasKokyuAround(1, 3, BLACK), true);
    goban23->clearCheckBoard();
    
    Goban* goban4 = new Goban();
    goban4->setGoishi(8, 8, WHITE);
    goban4->setGoishi(7, 8, BLACK);
    goban4->setGoishi(8, 7, BLACK);
    XCTAssertEqual(goban4->hasKokyuAround(8, 8, WHITE), false);
}

@end
