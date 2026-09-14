#pragma once

#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
    /**
     * @brief Генератор, читающий значения из потока ввода.
     */
    class IStreamGenerator : public Generator
    {
    private:
        std::istream& in;

    public:
        /**
         * @brief Конструктор.
         * @param in Поток ввода.
         */
        IStreamGenerator(std::istream& in = std::cin);

        /**
         * @brief Прочитать значение из потока.
         * @return Прочитанное целое число.
         */
        int generate() override;
    };
}
