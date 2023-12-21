#include "mdfile.h"
#include "ErrorHandling.h"
#include "Communicator.h"
#include "Calculator.h"
using namespace std;

WaitingMode::WaitingMode(int serverPort, int queueLength, ErrorHandling& errorHandlerParam, LogWriter& logWriter, string clientDatabase):
    serverSocket(socket(AF_INET, SOCK_STREAM, 0)),
    queueLength(queueLength),
    serverAddress(new sockaddr_in), 
    clientAddress(new sockaddr_in),
    errorHandler(errorHandlerParam),
    logWriter(logWriter),
    clientFile(clientDatabase) {
    
    try {
        if( serverSocket == -1 ) {
            throw std::runtime_error("Ошибка сокета!");
        }

        const int enable = 1;
        if( setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof enable) == -1 ) {
            throw std::runtime_error("Установка повторного подключения не удалась");
        }

        serverAddress->sin_family = AF_INET;
        serverAddress->sin_port = htons(serverPort);
        serverAddress->sin_addr.s_addr = htonl(INADDR_ANY);

        if( bind(serverSocket, reinterpret_cast< const sockaddr* >(serverAddress.get()), sizeof(sockaddr_in)) == -1 ) {
            throw std::runtime_error("Ошибка сокета!");
        }
    } catch(const std::exception& e) {
		if( strcmp(e.what(), "Ошибка сокета!") == 0 ) {
    		errorHandler.watchMinor();
            logWriter.writeLog("Minor: Ошибка сокета!");
		} else if( strcmp(e.what(), "Установка повторного подключения не удалась") == 0 ) {
    		errorHandler.watchInfo();
            logWriter.writeLog("Info: Установка повторного подключения не удалась");
		}
        exit(1);
    }
}

void WaitingMode::runServer(){
    try {
        if( listen(serverSocket, queueLength) == -1 ) {
            throw std::runtime_error("Ошибка сокета!");
        }
        errorHandler.watchInfo();
        logWriter.writeLog("Info: Сервер запущен");
        cout << "Сервер запущен \nОжидается подключение клиента....\n" << endl;

        socklen_t addr_len = sizeof(sockaddr_in);

        while( true ) {
            clientSocket = accept(serverSocket, reinterpret_cast< sockaddr* >(clientAddress.get()), &addr_len);
            if( clientSocket == -1 ) {
                throw std::runtime_error("Ошибка подключения клиента!");
            }
            
            string clientIP = inet_ntoa(clientAddress->sin_addr);
            int clientPort = ntohs(clientAddress->sin_port);
            
            
            string connectionInfo = "Клиент подключился: IP " + clientIP + ", порт " + std::to_string(clientPort);
            errorHandler.watchInfo();
            logWriter.writeLog("Info: " + connectionInfo);
            cout << connectionInfo << endl;
            
            authorizeClient();
            performCalculation();
        }
    } catch(const std::exception& e) {
       if( strcmp(e.what(), "Ошибка сокета!") == 0 ) {
    	errorHandler.watchCritical();
        logWriter.writeLog("Critical: Ошибка сокета!");
	} else if( strcmp(e.what(), "Ошибка подключения клиента!") == 0 ) {
   		 errorHandler.watchMinor();
         logWriter.writeLog("Minor: Ошибка подключения клиента!");
	}
	}
    exit(1);
}


int WaitingMode::authorizeClient(){
    try {
        cout << "Запуск клиентского соединения..." << endl;
        logWriter.writeLog("Info: Запуск клиентского соединения...");

        string successMessage = "OK";
        string salt = "7777777777777777";
        string errorMessage = "ERR";
        char receivedMessage[255];
                        
        int messageSize;
        messageSize = recv(clientSocket, &receivedMessage, sizeof(receivedMessage), 0);
        string clientMessage(receivedMessage, messageSize);
        string login, hash;
        fstream file;
        file.open(clientFile);
        getline (file, login, ':');
        getline (file, hash);
        file.close();

        if (clientMessage != login){
            sendMessage(errorMessage);
            throw std::runtime_error("Ошибка логина");
        } else{
            sendMessage(salt);
            messageSize = recv(clientSocket, receivedMessage, sizeof(receivedMessage), 0);
            string clientHash(receivedMessage, messageSize);
            string saltedHash = salt + hash;
            string digest;
            digest = calculateMD5(saltedHash);

            if (digest != clientHash){
                cout << digest << endl;
                cout << clientHash << endl;
                sendMessage(errorMessage);
                throw std::runtime_error("Ошибка пароля");
            } else{
                sendMessage(successMessage);
            }
        }
    } catch(const std::exception& e) {
        if( strcmp(e.what(), "Ошибка логина") == 0 ) {
    		errorHandler.watchMinor();
            logWriter.writeLog("Minor: Ошибка логина");
		} else if( strcmp(e.what(), "Ошибка пароля") == 0 ) {
   			errorHandler.watchMinor();
            logWriter.writeLog("Minor: Ошибка пароля");
		}
        close(clientSocket);
        return 1;
    }
    return 1;
}

void WaitingMode::sendMessage(string message){
    char *buffer = new char[4096];
    strcpy(buffer, message.c_str());
    send(clientSocket, buffer, message.length(), 0);
}

string WaitingMode::calculateMD5(string saltedHash){
    Weak::MD5 hash;
    string digest;
    StringSource(saltedHash, true,  new HashFilter(hash, new HexEncoder(new StringSink(digest))));
    return digest;
}
     
int WaitingMode::performCalculation(){
    Calculator calculator;
    uint32_t quantity;
    uint32_t number;
    int32_t numericVector;
    recv(clientSocket, &quantity, sizeof(quantity), 0);

    for(uint32_t j=0; j<quantity; j++){
        recv(clientSocket, &number, sizeof(number), 0);
        std::vector<int32_t> numbers;
        for(uint32_t i=0; i<number; i++){
            recv(clientSocket, &numericVector, sizeof(numericVector), 0);
            numbers.push_back(numericVector);
        }
        int32_t result = calculator.calculateProduct(numbers);
        send(clientSocket, &result, sizeof(result), 0);
        errorHandler.watchInfo();
        logWriter.writeLog("Info: Операция произведения выполнена");
        cout << "Операция произведения выполнена\n" <<endl;
    }
                    
    errorHandler.watchInfo();
    logWriter.writeLog("Info: Операция сервера завершена");
    cout << "Операция сервера завершена\n" <<endl;
    errorHandler.watchInfo();
    logWriter.writeLog("Info: Клиент отключен");
    cout << "Клиент отключен" << endl;
    close(clientSocket);
    return 1;
}

