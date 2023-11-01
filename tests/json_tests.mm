//
//  json_tests.mm
//  json-tests
//
//  Created by Piotr Brzeski on 2023-11-02.
//  Copyright © 2023 Brzeski.net. All rights reserved.
//

#include <data-format/json.h>
#import <XCTest/XCTest.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-statement-expression-from-macro-expansion"

@interface json_tests : XCTestCase

@end

@implementation json_tests

- (void)setUp {
	// Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
	// Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testGetBoolFromJson {
	auto json = format::json("{\"true_value\": true, \"false_value\": false, \"string_value\": \"true\"}");
	XCTAssertTrue(json["true_value"].get_bool());
	XCTAssertFalse(json["false_value"].get_bool());
	XCTAssertThrows(json["string_value"].get_bool());
}

@end

#pragma clang diagnostic pop
