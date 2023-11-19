#include "ErrorHandling.h"
#include "mdfile.h"

void ErrorHandling::handleError(std::string &error){
    std::ofstream errorFile;
    errorFile.open(this->errorLogFileName, std::ios::app);
    if(errorFile.is_open()){
        time_t currentTime = time(NULL);
        tm* timeinfo = localtime(&currentTime);

        // Установка русской локали
        locale loc("ru_RU.UTF-8");
        
        errorFile << error << ':' << asctime(timeinfo) << std::endl;
        std::cout << "Обнаружена ошибка: " << error << std::endl;
    }
}
