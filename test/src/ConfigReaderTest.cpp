#include <gmock/gmock-matchers.h>
#include "client/test/include/ConfigReaderTest.h"

using namespace testing;

ConfigReaderTest::ConfigReaderTest(): pathToFile("../src/test.txt") {
    reader = new ConfigReader(pathToFile);
}

TEST_F(ConfigReaderTest, readingClientFile) {
//just checking
   reader->readConfigFile();
   std::cout << reader->getIP() << std::endl;
   std::cout << reader->getPort() << std::endl;
}
