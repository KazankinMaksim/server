/** @file
 * @author Казанкин Максим
 * @version 1.0
 * @date 22.12.23
 * @copyright ИБСТ ПГУ
 * @warning Курсовая работа
 * @brief Заголовочный файл для модуля LogWriter
 */
#pragma once
#include "mdfile.h"
/** @brief Класс для записи логов
 * @details Класс содержит методы для записи логов в файл.
 */
class LogWriter {
public:
    /**
     * @brief Конструктор класса
     * @param [in] errorLogFileName Имя файла для записи логов
     */
    LogWriter(const std::string& errorLogFileName) : logFile(errorLogFileName, std::ios::app) {}
    /// Деструктор класса
    ~LogWriter() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    /**
     * @brief Запись лога
     * @param [in] logMessage Сообщение для записи в лог
     */
    void writeLog(const std::string& logMessage);
private:
    /// Файл для записи логов
    std::ofstream logFile;
    /// Имя файла для записи логов
    std::string errorLogFileName;
    /**
     * @brief Получение текущего времени
     * @return Текущее время в виде строки
     */
    std::string getCurrentTime();
};
