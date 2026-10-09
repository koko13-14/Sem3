#pragma once

#include <string>

/**
 * @brief Мелкие утилиты для строк и чисел.
 * Не описывает объект предметной области, поэтому не делится на пару .h/.cpp по правилу «каждый класс — в своих двух файлах». Как и вся
 * библиотека, не работает с потоками ввода-вывода.
 */
namespace TextUtils
{
    /**
     * @brief Перевести число в строку с двумя знаками после запятой.
     * @param value Исходное значение.
     * @return Например, "123.50" или "-0.05".
     */
    std::string Number(double value);

    /**
     * @brief То же, что Number(), но с именем под денежные суммы.
     * @param value Сумма.
     * @return Строка с двумя знаками после запятой.
     */
    std::string Money(double value);

    /**
     * @brief Сравнить строки, игнорируя регистр букв.
     * @param a Первая строка.
     * @param b Вторая строка.
     * @return true, если строки совпадают без учёта регистра.
     */
    bool SameIgnoreCase(const std::string& a, const std::string& b);
}
