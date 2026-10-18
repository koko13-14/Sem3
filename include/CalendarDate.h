#pragma once

#include <string>

/**
 * @brief Календарная дата (год, месяц, день) без времени суток.
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
    CalendarDate(const int year, const int month, const int day);

    /**
     * @brief Восстановить дату из строки вида "ГГГГ-ММ-ДД".
     * @param text Текст, например "2026-09-16".
     * @return Дата, соответствующая строке.
     */
    static CalendarDate FromString(const std::string& text);

    /**
     * @brief Получить год.
     * @return Номер года.
     */
    int Year() const;

    /**
     * @brief Получить номер месяца.
     * @return Число от 1 до 12.
     */
    int Month() const;

    /**
     * @brief Получить день месяца.
     * @return Число от 1 до 31.
     */
    int Day() const;

    /**
     * @brief Преобразовать дату в строку "ГГГГ-ММ-ДД".
     * @return Строка с датой, месяц и день дополнены нулём слева.
     */
    std::string AsString() const;

    /**
     * @brief Условный номер дня относительно начала отсчёта.
     * @return Целое число; чем позже дата, тем больше значение.
     */
    long Serial() const;

    /**
     * @brief Сколько дней от текущей даты до @p other.
     * @param other Дата, до которой считаем.
     * @return Разница в днях; отрицательная, если @p other раньше.
     */
    long DaysTo(const CalendarDate& other) const;

    /**
     * @brief Проверить равенство дат.
     * @param other Дата для сравнения.
     * @return true, если год, месяц и день совпадают.
     */
    bool operator==(const CalendarDate& other) const;

    /**
     * @brief Проверить неравенство дат.
     * @param other Дата для сравнения.
     * @return true, если даты различаются.
     */
    bool operator!=(const CalendarDate& other) const;

    /**
     * @brief Сравнить даты: текущая строго раньше.
     * @param other Дата для сравнения.
     * @return true, если текущая дата раньше @p other.
     */
    bool operator<(const CalendarDate& other) const;

    /**
     * @brief Сравнить даты: текущая не позже.
     * @param other Дата для сравнения.
     * @return true, если текущая дата раньше или совпадает с @p other.
     */
    bool operator<=(const CalendarDate& other) const;

    /**
     * @brief Сравнить даты: текущая строго позже.
     * @param other Дата для сравнения.
     * @return true, если текущая дата позже @p other.
     */
    bool operator>(const CalendarDate& other) const;

    /**
     * @brief Сравнить даты: текущая не раньше.
     * @param other Дата для сравнения.
     * @return true, если текущая дата позже или совпадает с @p other.
     */
    bool operator>=(const CalendarDate& other) const;

private:
    int year_ = 0;
    int month_ = 0;
    int day_ = 0;

    /**
     * @brief Проверить, что (year, month, day) — существующая дата.
     * @param year Год.
     * @param month Месяц, 1..12.
     * @param day День месяца.
     */
    static void EnsureValid(const int year, const int month, const int day);
};
