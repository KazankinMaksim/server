#include "LogWriter.h"

void LogWriter::writeLog(const std::string& logMessage) {
    if (logFile.is_open()) {
        logFile << getCurrentTime() << " " << logMessage << std::endl;
    }
}

std::string LogWriter::getCurrentTime() {
    std::time_t now = std::time(0);
    std::tm* localTime = std::localtime(&now);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
    return std::string(timeStr);
}
