#ifndef REVERSI_CONFIGREADERTEST_H
#define REVERSI_CONFIGREADERTEST_H

#include <gtest/gtest.h>
#include "../../include/ConfigReader.h"

// This test fixture tests the ConfigReader class.
class ConfigReaderTest : public testing::Test {

public:

    /**
    * A C'tor for ConfigReaderTest.
    */
    ConfigReaderTest();

    /**
    * A D'tor for ConfigReaderTest.
    */
    ~ConfigReaderTest() {
        delete reader;
    }

    /**
    * A SetUp routine for ConfigReaderTest.
    */
    virtual void SetUp() {
    }

    /**
    * A TearDown routine for ConfigReaderTest.
    */
    virtual void TearDown() {
    }

// Members:
protected:
    std::string pathToFile;
    ConfigReader *reader;
};

#endif //REVERSI_CONFIGREADERTEST_H
