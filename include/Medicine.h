#pragma once

#include <string>
#include <vector>
#include "CalendarDate.h"

/**
 * @brief Лекарство в справочнике аптеки.
 *
 * Хранит общие поля и строки с формой выпуска и деталями. Наследники
 * (Pills, Mixture, Salve, Ampoules) наполняют строки формы и деталей
 * в своём конструкторе.
 */
class Medicine
{
public:
    /** @brief Виртуальный деструктор. */
    virtual ~Medicine() = default;

    /**
     * @brief Заполнить карточку лекарства.
     * @param title Название.
     * @param bestBefore Срок годности.
     * @param summary Текст аннотации.
     * @param cost Цена.
     * @param producer Изготовитель.
     * @param indications Болезни, при которых лекарство применяется.
     * @param form Форма выпуска ("Таблетки", "Сироп" и т.п.).
     * @param details Сведения, зависящие от формы выпуска.
     */
    Medicine(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, const std::string& producer,
        const std::vector<std::string>& indications, const std::string& form, const std::string& details);

    /**
     * @brief Получить название лекарства.
     * @return Название.
     */
    const std::string& Title() const;

    /**
     * @brief Получить срок годности.
     * @return Дата, до которой лекарство годно.
     */
    const CalendarDate& BestBefore() const;

    /**
     * @brief Получить аннотацию.
     * @return Текст аннотации.
     */
    const std::string& Summary() const;

    /**
     * @brief Получить цену.
     * @return Цена в рублях.
     */
    double Cost() const;

    /**
     * @brief Получить изготовителя.
     * @return Название изготовителя.
     */
    const std::string& Producer() const;

    /**
     * @brief Получить список болезней, при которых применяется лекарство.
     * @return Список названий болезней.
     */
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
     * @brief Собрать строку с полным описанием лекарства.
     * @return Название, форма, цена, изготовитель, срок годности,
     *         список болезней, детали формы выпуска и аннотация.
     */
    std::string Describe() const;

private:

    /*
     * @brief Название лекарства. 
     */
    std::string title_;

    /*
     * @brief Срок годности. 
     */
    CalendarDate bestBefore_;

    /*
     * @brief Текст инструкции/аннотации. 
     */
    std::string summary_;

    /*
     * @brief Цена в рублях. 
     */
    double cost_ = 0.0;

    /* 
     * @brief Название завода-изготовителя. 
     */
    std::string producer_;

    /*
     * @brief Список болезней, от которых помогает лекарство. 
     */
    std::vector<std::string> indications_;

    /*
     * @brief Название формы выпуска (например, "Таблетки", "Сироп"). 
     */
    std::string form_;

    /*
     * @brief Специфичные для формы детали (дозировка, объём и т.п.). 
     */
    std::string details_;
};
