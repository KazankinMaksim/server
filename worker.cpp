#include "mdfile.h"
#include "ErrorHandling.h"
#include "Communicator.h"
#include "Calculator.h"
using namespace std;

WaitingMode::WaitingMode(int serverPort, int queueLength, ErrorHandling& errorHandlerParam, string clientDatabase):
    serverSocket(socket(AF_INET, SOCK_STREAM, 0)),
    queueLength(queueLength),
    serverAddress(new sockaddr_in), 
    clientAddress(new sockaddr_in),
    errorHandler(errorHandlerParam),
    clientFile(clientDatabase) {
    
    if( serverSocket == -1 ) {
        string error = "Ошибка сокета!";
        errorHandler.handleError(error);
        exit(1);
    }

    const int enable = 1;
	if( setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof enable) == -1 ) {
    string error = "Установка повторного подключения не удалась";
    errorHandler.handleError(error);
}

    serverAddress->sin_family = AF_INET;
    serverAddress->sin_port = htons(serverPort);
    serverAddress->sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(serverSocket, reinterpret_cast< const sockaddr* >(serverAddress.get()), sizeof(sockaddr_in)) == -1 ) {
        string error = "Ошибка сокета!";
        errorHandler.handleError(error);
        exit(1);
    }
}
void WaitingMode::runServer(){
    if( listen(serverSocket, queueLength) == -1 ) {
        cout << "Ошибка сокета!" << endl;
        exit(1);
    }
    cout << "Сервер запущен \nОжидается подключение клиента....\n" << endl;

    socklen_t addr_len = sizeof(sockaddr_in);

    while( true ) {
    	clientSocket = accept(serverSocket, reinterpret_cast< sockaddr* >(clientAddress.get()), &addr_len);
        if( clientSocket == -1 ) {
            cout << "Ошибка подключения клиента!" << endl;
            continue;
        }
        
        string clientIP = inet_ntoa(clientAddress->sin_addr);
        int clientPort = ntohs(clientAddress->sin_port);
        
        
        string connectionInfo = "Клиент подключился: IP " + clientIP + ", порт " + std::to_string(clientPort);
        errorHandler.handleError(connectionInfo);
        
        authorizeClient();
    	performCalculation();
    }
}

int WaitingMode::authorizeClient(){

    cout << "Запуск клиентского соединения..." << endl;

    string successMessage = "OK";
    string salt = "7777777777777777";
    string errorMessage = "ERR";
    string error;
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
        error = "Ошибка логина";
        errorHandler.handleError(error);
        close(clientSocket);
        return 1;
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
            error = "Ошибка пароля";
            errorHandler.handleError(error);
            close(clientSocket);
            return 1;
        } else{
            sendMessage(successMessage);
        }
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
    string disconnectionInfo = "Клиент отключен";
    recv(clientSocket, &quantity, sizeof(quantity), 0);

    for(uint32_t j=0; j<quantity; j++){
        recv(clientSocket, &number, sizeof(number), 0);
        std::vector<int32_t> numbers;
        for(uint32_t i=0; i<number; i++){
            recv(clientSocket, &numericVector, sizeof(numericVector), 0);
            numbers.push_back(numericVector);
        }
        int64_t result = calculator.calculateProduct(numbers);
        send(clientSocket, &result, sizeof(result), 0);
        cout << "Операция произведения выполнена\n" <<endl;
    }
                    
    cout << "Операция сервера завершена\n" <<endl;
    errorHandler.handleError(disconnectionInfo);
    close(clientSocket);
    return 1;
}
