#pragma once
#include <string>
#include "CalendarDate.h"

/**
 * @brief Одна покупка лекарства.
 * Нужна классу Drugstore для отчётов о продажах за период
 * (второе задание варианта «Аптека»).
 */
class Purchase
{
public:
    /**
     * @brief Зафиксировать покупку.
     * @param medicine Название проданного лекарства.
     * @param date Дата покупки.
     * @param count Сколько единиц продано.
     * @param sum Итоговая сумма за эту покупку.
     */
    Purchase(std::string medicine, CalendarDate date, int count, double sum);

    /** @brief Название проданного лекарства. */
    const std::string& Medicine() const;

    /** @brief Дата покупки. */
    const CalendarDate& Date() const;

    /** @brief Количество проданных единиц. */
    int Count() const;

    /** @brief Итоговая сумма за покупку. */
    double Sum() const;

    /**
     * @brief Собрать строку с описанием покупки (дата, лекарство, количество, сумма). Печатью занимается вызывающий код.
     */
    std::string Describe() const;

private:
    std::string medicine_;

    CalendarDate date_;

    int count_ = 0;

    double sum_ = 0.0;
};
