#pragma once
#include "Medicine.h"

/**
 * @brief Лекарство в форме мази.
 * Помимо общих полей Medicine хранит массу тюбика в граммах.
 */
class Salve : public Medicine
{
public:
    /**
     * @brief Создать карточку мази.
     * @param title Название.
     * @param bestBefore Срок годности.
     * @param summary Аннотация.
     * @param cost Цена.
     * @param producer Изготовитель.
     * @param indications Болезни, при которых применяется.
     * @param massG Масса тюбика в граммах.
     */
    Salve(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, 
        const std::string& producer, const std::vector<std::string>& indications, const double massG);

    /** @brief Масса тюбика, г. */
    double MassG() const;

    /** @brief Форма выпуска: "Мазь". */
    std::string DescribeForm() const override;

protected:
    /** @brief Масса тюбика одной строкой. */
    std::string DescribeDetails() const override;

private:
    double massG_ = 0.0;
};
