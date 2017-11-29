#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "include/NormalRulesetTest.h"
#include "include/LogicFlipTest.h"

/**
* This function runs all the tests.
*/
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}