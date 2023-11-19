#pragma once
#include <netinet/in.h>
#include <memory>
#include "ErrorHandling.h"
#include "Calculator.h"

class WaitingMode {
private:
    int serverSocket;
    int queueLength;
    std::unique_ptr< sockaddr_in > serverAddress;
    std::unique_ptr< sockaddr_in > clientAddress;
    ErrorHandling& errorHandler;
    std::string clientFile;
    
    int clientSocket;

    int authorizeClient();
    int performCalculation();
    std::string calculateMD5(std::string input);
    void sendMessage(std::string message);
public:
    WaitingMode() = delete;
    WaitingMode(int port, int queueLength, ErrorHandling& errorHandling, std::string clients);

    void runServer();
};
