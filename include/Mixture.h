#pragma once
#include "Medicine.h"

/**
 * @brief Лекарство в форме сиропа.
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
     * @param volumeMl Объём флакона, мл.
     */
    Mixture(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, const std::string& producer,
        const std::vector<std::string>& indications, const double volumeMl);

    /**
     * @brief Получить объём флакона.
     * @return Объём в миллилитрах.
     */
    double VolumeMl() const;

private:

    /*
     * @brief Объём флакона с сиропом в миллилитрах. 
     */
    double volumeMl_ = 0.0;

    /**
     * @brief Сформировать строку с объёмом флакона.
     * @param volumeMl Объём, мл.
     * @return Строка для базового класса.
     */
    static std::string MakeDetails(const double volumeMl);
};
