#pragma once

#include <memory>
#include <string>
#include <vector>

#include "CalendarDate.h"
#include "Medicine.h"
#include "Purchase.h"
#include "ReportRange.h"

/**
 * @brief Аптека: справочник лекарств и журнал покупок.
 *
 * Хранит список лекарств и историю продаж и отвечает на три запроса
 * варианта «Аптека»:
 *   1) выдать данные о лекарствах;
 *   2) выдать информацию о продажах за неделю/месяц/год;
 *   3) выдать список лекарств, применяемых при выбранной болезни.
 */
class Drugstore
{
public:
    /**
     * @brief Создать пустую аптеку с названием.
     * @param name Название аптеки.
     */
    explicit Drugstore(std::string name);

    /** @brief Yазвание аптеки. */
    const std::string& Name() const;

    /**
     * @brief Добавить лекарство в справочник.
     * @param item Указатель на Medicine или его наследника.
     */
    void Add(std::shared_ptr<Medicine> item);

    /**
     * @brief Добавить запись в журнал покупок.
     * @param purchase Данные о покупке.
     */
    void Record(const Purchase& purchase);

    // Задание 1: данные о лекарствах 

    /** @brief Весь справочник лекарств. */
    const std::vector<std::shared_ptr<Medicine>>& All() const;

    /**
     * @brief Найти лекарство по названию без учёта регистра.
     * @param name Что искать.
     * @return Указатель на найденное лекарство или nullptr.
     */
    std::shared_ptr<Medicine> FindByName(const std::string& name) const;

    // Задание 2: продажи за период 

     /**
     * @brief Все покупки указанного лекарства, попавшие в окно @p range дней до @p base включительно.
     * @param medicine Название лекарства.
     * @param range Длина окна.
     * @param base Опорная дата.
     * @return Подходящие записи.
     */
    std::vector<Purchase> SalesInRange(const std::string& medicine, ReportRange range, const CalendarDate& base) const;

    /**
     * @brief Суммарное количество проданных единиц за период.
     * @param medicine Название лекарства.
     * @param range Длина окна.
     * @param base Опорная дата.
     * @return Сумма Count() по всем подходящим покупкам.
     */
    int TotalSold(const std::string& medicine, ReportRange range, const CalendarDate& base) const;

    /**
     * @brief Суммарная выручка за период.
     * @param medicine Название лекарства.
     * @param range Длина окна.
     * @param base Опорная дата.
     * @return Сумма Sum() по всем подходящим покупкам.
     */
    double TotalIncome(const std::string& medicine, ReportRange range, const CalendarDate& base) const;

    // Задание 3: лекарства для выбранной болезни 

    /**
     * @brief Все лекарства, применяемые при указанной болезни.
     * @param illness Название болезни (без учёта регистра).
     * @return Подходящие лекарства в порядке следования в справочнике.
     */
    std::vector<std::shared_ptr<Medicine>> ForIllness(const std::string& illness) const;

private:
    std::string name_;
    std::vector<std::shared_ptr<Medicine>> items_;
    std::vector<Purchase> log_;

    /**
     * @brief Сколько дней содержит окно @p range.
     * @param range Длина окна.
     * @return 7, 30 или 365.
     */
    static int RangeDays(ReportRange range);

    /**
     * @brief Попадает ли @p saleDate в окно @p range дней до @p base
     * включительно.
     */
    bool FitsRange(const CalendarDate& saleDate, const CalendarDate& base, ReportRange range) const;
};
