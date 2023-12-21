#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestReporterStdout.h>
#include "mdfile.h"
#include "Calculator.h"
#include "LogWriter.h"

SUITE(CalculatorTests) {
    TEST(CalculateProductTest) {
        Calculator calculator;
        std::vector<int32_t> numbers = {5, 5, 5, 5};
        int32_t expectedProduct = 625;
        CHECK_EQUAL(expectedProduct, calculator.calculateProduct(numbers));
    }
    TEST(CalculateProductTestOverflowUp) {
        Calculator calculator;
        std::vector<int32_t> numbers = {5000, 7000, 9000, 12000};
        int32_t expectedProduct = 2147483647;
        CHECK_EQUAL(expectedProduct, calculator.calculateProduct(numbers));
    }
    TEST(CalculateProductTestOverflowDown) {
        Calculator calculator;
        std::vector<int32_t> numbers = {-5000, -7000, -9000, -12000};
        int32_t expectedProduct = -2147483648;
        CHECK_EQUAL(expectedProduct, calculator.calculateProduct(numbers));
    }
    TEST(CalculateProductTestZero) {
        Calculator calculator;
        std::vector<int32_t> numbers = {0, 0, 0, 0};
        int32_t expectedProduct = 0;
        CHECK_EQUAL(expectedProduct, calculator.calculateProduct(numbers));
    }
    TEST(CalculateProductTestSingleElement) {
    	Calculator calculator;
   	 	std::vector<int32_t> numbers = {5};
    	int32_t expectedProduct = 5;
    	CHECK_EQUAL(expectedProduct, calculator.calculateProduct(numbers));
	}
	TEST(CalculateProductTestMinez) {
        Calculator calculator;
        std::vector<int32_t> numbers = {-5, -5, -5, -5};
        int32_t expectedProduct = 625;
        CHECK_EQUAL(expectedProduct, calculator.calculateProduct(numbers));
    }
}

SUITE(LogWriterTestSuite) {
    TEST(WriteLogTest) {
        std::string logFileName = "test_log.txt";
        LogWriter logWriter(logFileName);
        std::string testMessage = "Test message";
        logWriter.writeLog(testMessage);

        std::ifstream logFile(logFileName);
        std::string line;
        CHECK(std::getline(logFile, line));
        CHECK(line.find(testMessage) != std::string::npos);
    }
   	TEST(TimeStampTest) {
    std::string logFileName = "test_log.txt";
    LogWriter logWriter(logFileName);
    std::string testMessage = "Test message";
    logWriter.writeLog(testMessage);

    std::ifstream logFile(logFileName);
    std::string line;
    CHECK(std::getline(logFile, line));
    
    std::string timestamp = line.substr(0, 19);
    CHECK_EQUAL(19, timestamp.size());  
    CHECK_EQUAL('-', timestamp[4]);  
    CHECK_EQUAL('-', timestamp[7]);  
    CHECK_EQUAL(' ', timestamp[10]);  
    CHECK_EQUAL(':', timestamp[13]);  
    CHECK_EQUAL(':', timestamp[16]); 

}

    
}

int main() {
    return UnitTest::RunAllTests();
}
