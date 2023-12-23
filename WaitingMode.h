/** @file
 * @author Казанкин Максим
 * @version 1.0
 * @date 22.12.23
 * @copyright ИБСТ ПГУ
 * @warning Курсовая работа
 * @brief Заголовочный файл для модуля WaitingMode
 */
#pragma once
#include <netinet/in.h>
#include <memory>
#include "ErrorHandling.h"
#include "Calculator.h"
#include "LogWriter.h"
/** @brief Класс для работы сервера в режиме ожидания
 * @details Класс содержит методы для авторизации клиента, выполнения вычислений, отправки сообщений и запуска сервера.
 */
class WaitingMode {
private:
    /// Сокет сервера
	int serverSocket;
	/// Длина очереди
	int queueLength;
	/// Адрес сервера
	std::unique_ptr< sockaddr_in > serverAddress;
	/// Адрес клиента
	std::unique_ptr< sockaddr_in > clientAddress;
	/// Обработчик ошибок
	ErrorHandling& errorHandler;
	/// Записыватель логов
	LogWriter& logWriter;
	/// Файл клиента
	std::string clientFile;    
	/// Сокет клиента
	int clientSocket;
    /**
     * @brief Авторизация клиента
     * @return Результат авторизации
     */
    int authorizeClient();
    /**
     * @brief Выполнение вычислений
     * @return Результат вычислений
     */
    int performCalculation();
    /**
     * @brief Вычисление MD5 хеша
     * @param [in] input Входная строка для вычисления хеша
     * @return MD5 хеш входной строки
     */
    std::string calculateMD5(std::string input);
    /**
     * @brief Отправка сообщения
     * @param [in] message Сообщение для отправки
     */
    void sendMessage(std::string message);
public:
	///Запретим конструктор без параметров
    WaitingMode() = delete;
    /**
     * @brief Конструктор класса
     * @param [in] port Порт для подключения
     * @param [in] queueLength Длина очереди
     * @param [in] errorHandling Обработчик ошибок
     * @param [in] logWriter Записыватель логов
     * @param [in] clients Клиенты
     */
    WaitingMode(int port, int queueLength, ErrorHandling& errorHandling, LogWriter& logWriter, std::string clients);
    /**
     * @brief Запуск сервера
     */
    void runServer();
};
