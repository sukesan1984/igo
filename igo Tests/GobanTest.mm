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

- (void)testPass
{
    Goban* goban = new Goban();
    goban->pass();
    XCTAssertEqual(goban->getHistory()->getLast()->isPass(), true);
}

- (void)testPutGoishi
{
    Goban* goban0 = new Goban();
    //置ける。
    XCTAssertEqual(goban0->putGoishi(0, 0, WHITE), true);
    XCTAssertEqual(goban0->getGoishi(0, 0), WHITE);
    
    //置けない。
    Goban* goban1 = new Goban();
    goban1->putGoishi(1, 0, WHITE);
    goban1->putGoishi(4, 4, BLACK);
    goban1->putGoishi(0, 1, WHITE);
    
    XCTAssertEqual(goban1->putGoishi(0, 0, BLACK), false);
    
    //取って、数が保存される。
    Goban* goban2 = new Goban();
    goban2->putGoishi(1, 0, WHITE);
    goban2->putGoishi(0, 0, BLACK);
    XCTAssertEqual(goban2->putGoishi(0, 1, WHITE), true);
    XCTAssertEqual(goban2->getHistory()->getLast()->getRemovedNum(), 1);
    XCTAssertEqual(goban2->getAgehamaShiro(), 1);
}

- (void)testCalcJinchi
{
    Goban* goban = new Goban();
    goban->setGoishi(4, 0, WHITE);
    goban->setGoishi(4, 1, WHITE);
    goban->setGoishi(4, 2, WHITE);
    goban->setGoishi(4, 3, WHITE);
    goban->setGoishi(3, 4, WHITE);
    goban->setGoishi(4, 5, WHITE);
    goban->setGoishi(4, 6, WHITE);
    goban->setGoishi(4, 7, WHITE);
    goban->setGoishi(4, 8, WHITE);
    
    goban->setGoishi(5, 0, BLACK);
    goban->setGoishi(5, 1, BLACK);
    goban->setGoishi(5, 2, BLACK);
    goban->setGoishi(5, 3, BLACK);
    goban->setGoishi(5, 4, BLACK);
    goban->setGoishi(5, 5, BLACK);
    goban->setGoishi(5, 6, BLACK);
    goban->setGoishi(5, 7, BLACK);
    goban->setGoishi(5, 8, BLACK);
    
    
    int i, j;
    for (i = 0; i < BAN_SIZE; i++){
        for(j = 0; j < BAN_SIZE; j++){
            goban->calcJinchi(i, j);
        }
    }
    Jinchi::Value result[BAN_SIZE][BAN_SIZE] = {
        {Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE,Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE },
        {Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE,Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE },
        {Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE,Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE },
        {Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE,Jinchi::WHITE_STONE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE, Jinchi::WHITE },
        {Jinchi::WHITE_STONE, Jinchi::WHITE_STONE, Jinchi::WHITE_STONE, Jinchi::WHITE_STONE,Jinchi::DAME, Jinchi::WHITE_STONE, Jinchi::WHITE_STONE, Jinchi::WHITE_STONE, Jinchi::WHITE_STONE },
        {Jinchi::BLACK_STONE, Jinchi::BLACK_STONE, Jinchi::BLACK_STONE, Jinchi::BLACK_STONE,Jinchi::BLACK_STONE, Jinchi::BLACK_STONE, Jinchi::BLACK_STONE, Jinchi::BLACK_STONE, Jinchi::BLACK_STONE },
        {Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK,Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK },
        {Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK,Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK },
        {Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK,Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK, Jinchi::BLACK },
    };
    
    for (i = 0; i < BAN_SIZE; i++){
        for(j = 0; j < BAN_SIZE; j++){
            XCTAssertEqual(result[i][j], goban->getJinchi(i, j));
        }
    }
}

- (void)testChangeJinchiState
{
    Goban* goban = new Goban();
    Jinchi::Value before = Jinchi::NONE;
    Jinchi::Value after = Jinchi::BLACK;
    XCTAssertEqual(Jinchi::BLACK, goban->changeJinchiState(before, after));
    
    Jinchi::Value before1 = Jinchi::NONE;
    Jinchi::Value after1 = Jinchi::WHITE;
    XCTAssertEqual(Jinchi::WHITE, goban->changeJinchiState(before1, after1));
    
    Jinchi::Value before2 = Jinchi::NONE;
    Jinchi::Value after2 = Jinchi::DAME;
    XCTAssertEqual(Jinchi::DAME, goban->changeJinchiState(before2, after2));
    
    Jinchi::Value before3 = Jinchi::WHITE;
    Jinchi::Value after3 = Jinchi::BLACK;
    XCTAssertEqual(Jinchi::DAME, goban->changeJinchiState(before3, after3));
    
    Jinchi::Value before4 = Jinchi::BLACK;
    Jinchi::Value after4 = Jinchi::WHITE;
    XCTAssertEqual(Jinchi::DAME, goban->changeJinchiState(before4, after4));
    
    Jinchi::Value before5 = Jinchi::NONE;
    Jinchi::Value after5 = Jinchi::WHITE_STONE;
    XCTAssertEqual(Jinchi::WHITE, goban->changeJinchiState(before5, after5));
}

- (void)testSetGoishi
{
    Goban* goban = new Goban();
    goban->setGoishi(0, 0, WHITE);
    XCTAssertEqual(goban->getGoishi(0, 0), WHITE);
}

- (void)testSetGoishiKari
{
    Goban* goban = new Goban();
    goban->setGoishiKari(0, 0, WHITE);
    XCTAssertEqual(goban->getGoishi(0, 0), WHITE);
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
    
    //四方を白で囲まれているけど、今回とれるので置ける。
    Goban* goban1 = new Goban();
    goban1->setGoishi(0, 1, WHITE);
    goban1->setGoishi(2, 1, WHITE);
    goban1->setGoishi(1, 0, WHITE);
    goban1->setGoishi(1, 2, WHITE);
    
    goban1->setGoishi(2, 0, BLACK);
    goban1->setGoishi(3, 1, BLACK);
    goban1->setGoishi(2, 2, BLACK);
    
    XCTAssertEqual(goban1->canPutGoishi(1, 1, BLACK) ,true);
    
    Goban* goban2 = new Goban();
    goban2->setGoishi(1, 0, WHITE);
    goban2->setGoishi(2, 0, BLACK);
    goban2->setGoishi(0, 1, WHITE);
    goban2->setGoishi(1, 1, WHITE);
    goban2->setGoishi(2, 1, BLACK);
    goban2->setGoishi(0, 2, BLACK);
    goban2->setGoishi(1, 2, BLACK);
    
    XCTAssertEqual(goban2->canPutGoishi(0, 0, WHITE), false);
    
    //劫の時は、置けない。
    Goban* goban3 = new Goban();
    goban3->putGoishi(1, 0, WHITE);
    goban3->putGoishi(2, 0, BLACK);
    goban3->putGoishi(0, 1, WHITE);
    goban3->putGoishi(3, 1, BLACK);
    goban3->putGoishi(1, 2, WHITE);
    goban3->putGoishi(2, 2, BLACK);
    goban3->putGoishi(1, 1, BLACK);
    XCTAssertEqual(goban3->putGoishi(2, 1, WHITE), true);
    XCTAssertEqual(goban3->putGoishi(1, 1, BLACK), false);
}

- (void) testHasCanGetGoishiAround{
    Goban* goban1 = new Goban();
    goban1->setGoishi(0, 1, WHITE);
    goban1->setGoishi(2, 1, WHITE);
    goban1->setGoishi(1, 0, WHITE);
    goban1->setGoishi(1, 2, WHITE);
    
    goban1->setGoishi(2, 0, BLACK);
    goban1->setGoishi(3, 1, BLACK);
    goban1->setGoishi(2, 2, BLACK);
    goban1->setGoishi(1, 1, BLACK);
    
    XCTAssertEqual(goban1->hasCanGetGoishiAround(1, 1), true);
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
    
    XCTAssertEqual(goban->tryToRemoveAround(1, 2, WHITE), 1);
    
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
    
    
    XCTAssertEqual(goban->removeGoishi(0, 0, BLACK), 3);
    
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
