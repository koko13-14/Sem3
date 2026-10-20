#pragma once
#include "Medicine.h"

/**
 * @brief Лекарство в форме ампул.
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
     * @param ampouleMl Объём ампулы, мл.
     * @param perPack Количество в упаковке.
     */
    Ampoules(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, const std::string& producer,
        const std::vector<std::string>& indications, const double ampouleMl, const int perPack);

    /**
     * @brief Получить объём одной ампулы.
     * @return Объём в миллилитрах.
     */
    double AmpouleMl() const;

    /**
     * @brief Получить количество ампул в упаковке.
     * @return Количество ампул.
     */
    int PerPack() const;

private:

    /*
     * @brief Объём одной ампулы в миллилитрах. 
     */
    double ampouleMl_ = 0.0;

    /*
     * @brief Количество ампул в упаковке. 
     */
    int perPack_ = 0;

    /**
     * @brief Сформировать строку с объёмом ампулы и количеством.
     * @param ampouleMl Объём, мл.
     * @param perPack Количество в упаковке.
     * @return Строка для базового класса.
     */
    static std::string MakeDetails(const double ampouleMl, const int perPack);
};
