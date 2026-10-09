#pragma once

#include <string>
#include <vector>
#include "CalendarDate.h"

/**
 * @brief Лекарство в справочнике аптеки.
 *
 * Хранит общие поля, которые есть у любой формы выпуска: название,
 * срок годности, аннотацию, цену и изготовителя. Конкретика формы
 * выпуска выносится в наследников (Pills, Mixture, Salve, Ampoules):
 * они переопределяют DescribeForm() и DescribeDetails().
 */
class Medicine
{
public:
    /**
     * @brief Заполнить карточку лекарства общими данными.
     * @param title Название.
     * @param bestBefore Срок годности.
     * @param summary Текст аннотации.
     * @param cost Цена.
     * @param producer Изготовитель.
     * @param indications Болезни, при которых лекарство применяется.
     */
    Medicine(std::string title, CalendarDate bestBefore, std::string summary, double cost, std::string producer, std::vector<std::string> indications);

    /** @brief Виртуальный деструктор — нужен для корректного удаления наследников через базовый указатель. */
    virtual ~Medicine() = default;

    /** @brief Название лекарства. */
    const std::string& Title() const;

    /** @brief Срок годности. */
    const CalendarDate& BestBefore() const;

    /** @brief Аннотация. */
    const std::string& Summary() const;

    /** @brief Цена. */
    double Cost() const;

    /** @brief Изготовитель. */
    const std::string& Producer() const;

    /** @brief Болезни, при которых применяется лекарство. */
    const std::vector<std::string>& Indications() const;

    /**
     * @brief Проверить, истёк ли срок годности к указанной дате.
     * @param at Дата, на которую проверяем (обычно «сегодня»).
     * @return true, если срок годности уже прошёл.
     */
    bool IsOutdated(const CalendarDate& at) const;

    /**
     * @brief Узнать, помогает ли лекарство при указанной болезни.
     * @param illness Название болезни.
     * @return true, если болезнь есть в списке (без учёта регистра).
     */
    bool HelpsWith(const std::string& illness) const;

    /**
     * @brief Строка с описанием лекарства (задание 1 варианта).
     */
    virtual std::string Describe() const;

    /**
     * @brief Название формы выпуска: "Таблетки", "Сироп" и т.п.
     * Реализуется в каждом наследнике.
     */
    virtual std::string DescribeForm() const = 0;

protected:
    /**
     * @brief Дополнительные сведения о лекарстве, зависящие от формы
     * выпуска (дозировка, объём флакона, масса тюбика и т.п.).
     * Реализуется в каждом наследнике.
     */
    virtual std::string DescribeDetails() const = 0;

private:
    std::string title_;
    CalendarDate bestBefore_;
    std::string summary_;
    double cost_ = 0.0;
    std::string producer_;
    std::vector<std::string> indications_;
};
