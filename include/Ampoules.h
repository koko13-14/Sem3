#pragma once
#include "Medicine.h"

/**
 * @brief Лекарство в форме ампул (раствор для инъекций).
 * Помимо общих полей Medicine хранит объём одной ампулы и количество
 * ампул в упаковке.
 */
class Ampoules : public Medicine
{
public:
    /**
     * @brief Создать карточку ампул.
     * @param title Название.
     * @param bestBefore Срок годности.
     * @param summary Аннотация.
     * @param cost Цена.
     * @param producer Изготовитель.
     * @param indications Болезни, при которых применяется.
     * @param ampouleMl Объём одной ампулы в миллилитрах.
     * @param perPack Сколько ампул в упаковке.
     */
    Ampoules(std::string title, CalendarDate bestBefore, std::string summary, double cost, 
        std::string producer, std::vector<std::string> indications, double ampouleMl, int perPack);

    /** @brief Объём одной ампулы, мл. */
    double AmpouleMl() const;

    /** @brief Количество ампул в упаковке. */
    int PerPack() const;

    /** @brief Форма выпуска: "Ампулы (раствор для инъекций)". */
    std::string DescribeForm() const override;

protected:
    /** @brief Объём ампулы и количество в упаковке одной строкой. */
    std::string DescribeDetails() const override;

private:
    double ampouleMl_ = 0.0;
    int perPack_ = 0;
};
