#pragma once
#include "mdfile.h"

class LogWriter {
public:
    LogWriter(const std::string& errorLogFileName) : logFile(errorLogFileName, std::ios::app) {}
    ~LogWriter() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    void writeLog(const std::string& logMessage);

private:
    std::ofstream logFile;
    std::string errorLogFileName;
    std::string getCurrentTime();
};
