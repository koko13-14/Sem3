#pragma once

#include <string>

/**
 * @brief Мелкие утилиты для строк и чисел.
 */
namespace TextUtils
{
    /**
     * @brief Перевести число в строку с двумя знаками после запятой.
     * @param value Исходное значение.
     * @return Строка вида "123.50" или "-0.05".
     */
    std::string Number(const double value);

    /**
     * @brief То же, что Number(), но с именем под денежные суммы.
     * @param value Сумма.
     * @return Строка с двумя знаками после запятой.
     */
    std::string Money(const double value);

    /**
     * @brief Сравнить строки, игнорируя регистр букв.
     * @param a Первая строка.
     * @param b Вторая строка.
     * @return true, если строки совпадают без учёта регистра.
     */
    bool SameIgnoreCase(const std::string& a, const std::string& b);
}
