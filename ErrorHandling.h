#pragma once
#include "mdfile.h"
class ErrorHandling {
private:
    std::string errorLogFileName;
public:
    ErrorHandling(const std::string& errors):errorLogFileName(errors){};
    ErrorHandling(const ErrorHandling& other):errorLogFileName(other.errorLogFileName){};
    void handleError(std::string& error);
};
