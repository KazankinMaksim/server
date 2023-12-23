/** @file
 * @author Казанкин Максим
 * @version 1.0
 * @date 22.12.23
 * @copyright ИБСТ ПГУ
 * @warning Курсовая работа
 * @brief Заголовочный файл для модуля Calculator
 */
#pragma once
#include <cstdint>
#include <limits>
#include <vector>
/** @brief Класс для вычисления произведений
 * @details Класс содержит два метода для вычисления произведений чисел.
 * @warning Реализация только для типа данных int32_t
 */
class Calculator {
public:
    /**
     * @brief Вычисление произведений для каждого вектора
     * @param [in] vectors Вектор векторов, для которых нужно вычислить произведения
     * @return Вектор произведений
     */
    std::vector<int32_t> calculateProducts(const std::vector<std::vector<int32_t>>& vectors);
    /**
     * @brief Вычисление произведения чисел в векторе
     * @param [in] numbers Вектор чисел, для которых нужно вычислить произведение
     * @return Произведение чисел
     */
    int32_t calculateProduct(const std::vector<int32_t>& numbers);
};
