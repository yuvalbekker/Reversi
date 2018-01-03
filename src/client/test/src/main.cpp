#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "client/test/include/NormalRulesetTest.h"
#include "client/test/include/LogicFlipTest.h"
#include "client/test/include/ConfigReaderTest.h"

/**
* This function runs all the tests.
*/
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}