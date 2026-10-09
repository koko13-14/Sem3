#pragma once

#include <string>

/**
 * @brief Календарная дата (год, месяц, день) без времени суток.
 *
 * Не обращается к <ctime>, локали и потокам ввода-вывода. Используется
 * в Medicine (срок годности), Purchase (дата покупки) и Drugstore
 * (для отчётов за период).
 */
class CalendarDate
{
public:
    /**
     * @brief Собрать дату из трёх чисел.
     * @param year Год.
     * @param month Номер месяца, 1..12.
     * @param day День месяца.
     */
    CalendarDate(int year, int month, int day);

    /**
     * @brief Восстановить дату из строки вида "ГГГГ-ММ-ДД".
     * @param text Текст, например "2026-10-3".
     * @return Дата, соответствующая строке.
     */
    static CalendarDate FromString(const std::string& text);

    /** @brief Год. */
    int Year() const;

    /** @brief Номер месяца, 1..12. */
    int Month() const;

    /** @brief День месяца. */
    int Day() const;

    /**
     * @brief Текстовое представление в формате "ГГГГ-ММ-ДД".
     * Месяц и день при необходимости дополняются нулём слева.
     */
    std::string AsString() const;

    /**
     * @brief Условный номер дня относительно начала отсчёта.
     * Чем позже дата, тем больше значение. Удобно для сравнения и подсчёта разницы в днях.
     */
    long Serial() const;

    /**
     * @brief Сколько дней проходит от текущей даты до @p other.
     * @param other Дата, до которой считаем.
     * @return Положительное число, если @p other позже; отрицательное, если раньше; ноль для той же даты.
     */
    long DaysTo(const CalendarDate& other) const;

    /** @brief true, если год, месяц и день совпадают. */
    bool operator==(const CalendarDate& other) const;

    /** @brief true, если даты различаются хотя бы одним полем. */
    bool operator!=(const CalendarDate& other) const;

    /** @brief true, если текущая дата строго раньше @p other. */
    bool operator<(const CalendarDate& other) const;

    /** @brief true, если текущая дата не позже @p other. */
    bool operator<=(const CalendarDate& other) const;

    /** @brief true, если текущая дата строго позже @p other. */
    bool operator>(const CalendarDate& other) const;

    /** @brief true, если текущая дата не раньше @p other. */
    bool operator>=(const CalendarDate& other) const;

private:
    int year_ = 0;
    int month_ = 0;
    int day_ = 0;

    /**
     * @brief Убедиться, что (year, month, day) — существующая дата.
     */
    static void EnsureValid(int year, int month, int day);
};
