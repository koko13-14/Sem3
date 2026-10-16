#pragma once

#include <string>
#include <vector>

#include "CalendarDate.h"
#include "Medicine.h"
#include "Purchase.h"
#include "ReportRange.h"

/**
 @brief Аптека: справочник лекарств и журнал покупок.
 *
 * Лекарства хранятся по значению в std::vector<Medicine>.
 */
class Drugstore
{
public:
    /**
     * @brief Создать пустую аптеку с названием.
     * @param name Название аптеки.
     */
    explicit Drugstore(const std::string& name);

    /**
     * @brief Получить название аптеки.
     * @return Название.
     */
    const std::string& Name() const;

    /**
     * @brief Добавить лекарство в справочник.
     * @param item Лекарство (копируется в вектор).
     */
    void Add(const Medicine& item);

    /**
     * @brief Зарегистрировать покупку.
     * @param purchase Данные о покупке.
     */
    void Record(const Purchase& purchase);

    /**
     * @brief Получить все лекарства справочника.
     * @return Константная ссылка на вектор лекарств.
     */
    const std::vector<Medicine>& All() const;

    /**
     * @brief Найти индекс лекарства по названию.
     * @param name Название.
     * @return Индекс в векторе, либо size() — если не найдено.
     */
    std::size_t FindIndexByName(const std::string& name) const;

    /**
     * @brief Найти лекарство по названию.
     * @param name Название.
     * @return Копия лекарства; пустое название, если не найдено.
     */
    Medicine FindByName(const std::string& name) const;

    /**
     * @brief Получить покупки указанного лекарства за период.
     * @param medicine Название лекарства.
     * @param range Длина окна отчёта.
     * @param base Опорная дата.
     * @return Вектор подходящих покупок.
     */
    std::vector<Purchase> SalesInRange(const std::string& medicine, const ReportRange range, const CalendarDate& base) const;

    /**
     * @brief Суммарное количество проданных единиц за период.
     * @param medicine Название лекарства.
     * @param range Длина окна отчёта.
     * @param base Опорная дата.
     * @return Количество единиц.
     */
    int TotalSold(const std::string& medicine, const ReportRange range, const CalendarDate& base) const;

    /**
     * @brief Суммарная выручка за период.
     * @param medicine Название лекарства.
     * @param range Длина окна отчёта.
     * @param base Опорная дата.
     * @return Сумма в рублях.
     */
    double TotalIncome(const std::string& medicine, const ReportRange range, const CalendarDate& base) const;

    /**
     * @brief Все лекарства, применяемые при указанной болезни.
     * @param illness Название болезни.
     * @return Вектор подходящих лекарств.
     */
    std::vector<Medicine> ForIllness(const std::string& illness) const;

private:
    std::string name_;
    std::vector<Medicine> items_;
    std::vector<Purchase> log_;

    /**
     * @brief Длина окна отчёта в днях.
     * @param range Отчётный период.
     * @return 7, 30 или 365.
     */
    static int RangeDays(const ReportRange range);

    /**
     * @brief Попадает ли дата покупки в окно периода.
     * @param saleDate Дата покупки.
     * @param base Опорная дата.
     * @param range Длина окна.
     * @return true, если дата в окне.
     */
    bool FitsRange(const CalendarDate& saleDate, const CalendarDate& base, const ReportRange range) const;
};
