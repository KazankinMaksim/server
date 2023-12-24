#include "mdfile.h"
#include "ErrorHandling.h"
#include "WaitingMode.h"
#include "LogWriter.h"
using namespace std;

int main(int argc, char *argv[]) {

    int option;
    int serverPort = 33333;
    string databaseFileName = "/ect/vcalc.conf";
    string errorLogFileName = "/var/log/vcalc.log";
    string error;

    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"file", required_argument, 0, 'f'},
        {"port", required_argument, 0, 'p'},
        {"error", required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };
     if (argc == 1) {
        cout << "\n Меню команд  "<< endl;
        cout << "\nВы просматриваете инструкции по запуску сервера. Ниже приведены основные параметры и их назначение:\n"  << endl;
        cout << "-f или --file — параметр ввода имени файла с базы данных пользователей" << endl;
        cout << "-p или --port — параметр ввода порта" << endl;
        cout << "-e или --error — параметр ввода имени файла-журнала ошибок" << endl;
        cout << "\nДля запуска сервера необходимо ввести следующее:\n./server -f/--file *файл базы данных* (base.txt) -p/--port *порт* (33333) -e/--error *журнал ошибок* (error.txt)" << endl;
        return 1;
    }

    int option_index = 0;
    bool fileFlag = false, portFlag = false, errorFlag = false;
    while ((option = getopt_long(argc, argv, "hf:p:e:", long_options, &option_index)) != -1) {
        switch(option){
            case 'h':
            cout << "\n Меню команд  "<< endl;
            cout << "\nВы просматриваете инструкции по запуску сервера. Ниже приведены основные параметры и их назначение:\n"  << endl;
            cout << "-f или --file — параметр ввода имени файла с базы данных пользователей" << endl;
            cout << "-p или --port — параметр ввода порта" << endl;
            cout << "-e или --error — параметр ввода имени файла-журнала ошибок" << endl;
            cout << "\nДля запуска сервера необходимо ввести следующее:\n./server -f/--file *файл базы данных* (base.txt) -p/--port *порт* (33333) -e/--error *журнал ошибок* (error.txt)" << endl;
            return 1;
            break;
            case 'f':
            databaseFileName = string(optarg);
            fileFlag = true;
            break;
            case 'p':
            serverPort = stoi(string(optarg));
            portFlag = true;
            break;
            case 'e':
            errorLogFileName = string(optarg);
            errorFlag = true;
            break;
        }
    }
LogWriter logWriter(errorLogFileName);
ErrorHandling errorHandler;

std::vector<std::string> missingParams;

if (!fileFlag) {
    missingParams.push_back("-f/--file");
}
if (!portFlag) {
    missingParams.push_back("-p/--port");
}
if (!errorFlag) {
    missingParams.push_back("-e/--error");
}

if (!missingParams.empty()) {
    errorHandler.watchMinor();
    for (const auto& param : missingParams) {
        try {
            throw std::runtime_error("Пропущен параметр " + param);
        } catch (const std::exception& e) {
            cout << "Пропущен параметр " << param << endl;
            logWriter.writeLog("Error: Пропущен параметр " + param);
        }
    }
    cout << "Введите -h/--help для просмотра справки" << endl;
    return 1;
}



WaitingMode communicator(serverPort, 10, errorHandler, logWriter, databaseFileName);

communicator.runServer();

return 0;
}

