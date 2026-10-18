#pragma once
#include "Medicine.h"

/**
 * @brief Лекарство в форме мази.
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
     * @param massG Масса тюбика, г.
     */
    Salve(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, const std::string& producer,
        const std::vector<std::string>& indications, const double massG);

    /**
     * @brief Получить массу тюбика.
     * @return Масса в граммах.
     */
    double MassG() const;

private:
    double massG_ = 0.0;

    /**
     * @brief Сформировать строку с массой тюбика.
     * @param massG Масса, г.
     * @return Строка для базового класса.
     */
    static std::string MakeDetails(const double massG);
};
