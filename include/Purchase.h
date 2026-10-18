#pragma once
#include <string>
#include "CalendarDate.h"

/**
 * @brief Одна покупка лекарства.
 */
class Purchase
{
public:
    /**
     * @brief Создать запись о покупке.
     * @param medicine Название проданного лекарства.
     * @param date Дата покупки.
     * @param count Количество проданных единиц.
     * @param sum Итоговая сумма за покупку.
     */
    Purchase(const std::string& medicine, const CalendarDate& date, const int count, const double sum);

    /**
     * @brief Получить название проданного лекарства.
     * @return Название.
     */
    const std::string& Medicine() const;

    /**
     * @brief Получить дату покупки.
     * @return Дата.
     */
    const CalendarDate& Date() const;

    /**
     * @brief Получить количество проданных единиц.
     * @return Количество.
     */
    int Count() const;

    /**
     * @brief Получить сумму за покупку.
     * @return Сумма в рублях.
     */
    double Sum() const;

    /**
     * @brief Собрать строку с описанием покупки.
     * @return Дата, название лекарства, количество и сумма.
     */
    std::string Describe() const;

private:
    std::string medicine_;
    CalendarDate date_;
    int count_ = 0;
    double sum_ = 0.0;
};
