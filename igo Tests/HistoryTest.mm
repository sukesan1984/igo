//
//  HistoryTest.m
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#import <XCTest/XCTest.h>
#import "History.h"
#import "Te.h"

@interface HistoryTest : XCTestCase

@end

@implementation HistoryTest

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

- (void)testGetTe
{
    History* history0 = History::create();
    Te* te01 = history0->getTe(1);
    
    Te* null = NULL;
    XCTAssertEqual(te01, null, "まだ打たれていない手を取ろうとした");
    
    History* history1 = History::create();
    Te* te11 = Te::createWithPositionAndColor(0, 0, WHITE);
    history1->pushTe(te11);
    XCTAssertEqual(history1->getTe(1), te11, "一手目");
    Te* te12 = history1->getTe(2);
    XCTAssertEqual(te12, null, "二手目はまだ打たれていない。");
}

- (void)testGetLast
{
    History* history = History::create();
    history->pushTe(Te::createWithPositionAndColor(0, 0, WHITE));
    history->pushTe(Te::createWithPositionAndColor(0, 1, WHITE));
    history->pushTe(Te::createWithPositionAndColor(0, 2, BLACK));
    Te* last = history->getLast();
    XCTAssertEqual(last->getColor(), BLACK);
    XCTAssertEqual(last->getX(), 0);
    XCTAssertEqual(last->getY(), 2);
}

- (void)testGetBeforeLast
{
    History* history = History::create();
    history->pushTe(Te::createWithPositionAndColor(0, 0, WHITE));
    history->pushTe(Te::createWithPositionAndColor(0, 1, WHITE));
    history->pushTe(Te::createWithPositionAndColor(0, 2, BLACK));
    Te* last = history->getBeforeLast();
    XCTAssertEqual(last->getColor(), WHITE);
    XCTAssertEqual(last->getX(), 0);
    XCTAssertEqual(last->getY(), 1);
}

@end