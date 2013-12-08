//
//  TeTest.m
//  igo
//
//  Created by Kosuke Takami on 2013/12/08.
//
//

#import <XCTest/XCTest.h>
#import "Te.h"

@interface TeTest : XCTestCase

@end

@implementation TeTest

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

- (void)testCreateWithPositionAndColor
{
    Te* te = Te::createWithPositionAndColor(0, 1, WHITE);
    XCTAssertEqual(te->getX(), 0);
    XCTAssertEqual(te->getY(), 1);
    XCTAssertEqual(te->getColor(), WHITE);
}

- (void)testNew
{
    Te* te = new Te(0, 1, WHITE);
    XCTAssertEqual(te->getX(), 0);
    XCTAssertEqual(te->getY(), 1);
    XCTAssertEqual(te->getColor(), WHITE);
    
    
    Te* te1 = new Te();
    XCTAssertEqual(te1->getX(), -1);
    XCTAssertEqual(te1->getY(), -1);
    XCTAssertEqual(te1->getColor(), NONE);
    
    //XCTAssertThrows(new Te(9, 0, WHITE),"over ban size");
    //XCTAssertThrows(new Te(0, 9, BLACK),"over ban size");
}
- (void)testIsPass
{
    Te* te = new Te(0, 1, WHITE);
    XCTAssertEqual(te->isPass(), false);
    
    Te* te1 = new Te();
    XCTAssertEqual(te1->isPass(), true);
}


@end
