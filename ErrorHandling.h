/** @file
 * @author Казанкин Максим
 * @version 1.0
 * @date 22.12.23
 * @copyright ИБСТ ПГУ
 * @warning Курсовая работа
 * @brief Заголовочный файл для модуля ErrorHandling
 */
#pragma once
#include "mdfile.h"
/** @brief Класс для обработки ошибок
 * @details Класс содержит методы для отслеживания критических, незначительных ошибок и информационных сообщений.
 */
class ErrorHandling {
public:
    /// Конструктор по умолчанию
    ErrorHandling(){};
    /// Конструктор копирования
    ErrorHandling(const ErrorHandling&){};
    /**
     * @brief Отслеживание критических ошибок
     */
    void watchCritical() {
    }
    /**
     * @brief Отслеживание незначительных ошибок
     */
    void watchMinor() {
    }
    /**
     * @brief Отслеживание информационных сообщений
     */
    void watchInfo() {
    }
};

