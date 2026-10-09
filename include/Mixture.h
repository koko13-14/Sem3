#pragma once
#include "Medicine.h"

/**
 * @brief Лекарство в форме сиропа.
 * Помимо общих полей Medicine хранит объём флакона в миллилитрах.
 */
class Mixture : public Medicine
{
public:
    /**
     * @brief Создать карточку сиропа.
     * @param title Название.
     * @param bestBefore Срок годности.
     * @param summary Аннотация.
     * @param cost Цена.
     * @param producer Изготовитель.
     * @param indications Болезни, при которых применяется.
     * @param volumeMl Объём флакона в миллилитрах.
     */
    Mixture(std::string title, CalendarDate bestBefore, std::string summary, double cost, std::string producer, std::vector<std::string> indications, double volumeMl);

    /** @brief Объём флакона, мл. */
    double VolumeMl() const;

    /** @brief Форма выпуска: "Сироп". */
    std::string DescribeForm() const override;

protected:
    /** @brief Объём флакона одной строкой. */
    std::string DescribeDetails() const override;

private:
    double volumeMl_ = 0.0;
};
