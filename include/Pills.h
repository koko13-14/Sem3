#pragma once
#include "Medicine.h"

/**
 * @brief Лекарство в форме таблеток.
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
     * @param doseMg Дозировка, мг.
     * @param perPack Количество в упаковке.
     */
    Pills(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, const std::string& producer,
        const std::vector<std::string>& indications, const double doseMg, const int perPack);

    /**
     * @brief Получить дозировку.
     * @return Дозировка в миллиграммах.
     */
    double DoseMg() const;

    /**
     * @brief Получить количество таблеток в упаковке.
     * @return Количество таблеток.
     */
    int PerPack() const;

private:
    double doseMg_ = 0.0;
    int perPack_ = 0;

    /**
     * @brief Сформировать строку с дозировкой и количеством.
     * @param doseMg Дозировка, мг.
     * @param perPack Количество в упаковке.
     * @return Строка для базового класса.
     */
    static std::string MakeDetails(const double doseMg, const int perPack);
};
