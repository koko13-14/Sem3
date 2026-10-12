#pragma once
#include "Medicine.h"

/**
 * @brief Лекарство в форме таблеток.
 * Помимо общих полей Medicine хранит дозировку и количество таблеток
 * в упаковке.
 */
class Pills : public Medicine
{
public:
    /**
     * @brief Создать карточку таблеток.
     * @param title Название.
     * @param bestBefore Срок годности.
     * @param summary Аннотация.
     * @param cost Цена.
     * @param producer Изготовитель.
     * @param indications Болезни, при которых применяется.
     * @param doseMg Дозировка в миллиграммах.
     * @param perPack Сколько таблеток в упаковке.
     */
    Pills(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, double cost, 
        const std::string& producer, const std::vector<std::string>& indications, double doseMg, int perPack);

    /** @brief Дозировка в миллиграммах. */
    double DoseMg() const;

    /** @brief Количество таблеток в упаковке. */
    int PerPack() const;

    /** @brief Форма выпуска: "Таблетки". */
    std::string DescribeForm() const override;

protected:
    /** @brief Дозировка и количество в упаковке одной строкой. */
    std::string DescribeDetails() const override;

private:
    double doseMg_ = 0.0;
    int perPack_ = 0;
};
