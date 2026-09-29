#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, возвращающий константное значение.
     */
    class ConstantGenerator : public Generator
    {
    private:
        int value;

    public:
        /**
         * @brief Конструктор.
         * @param value Константное значение.
         */
        ConstantGenerator(const int value);

        /**
         * @brief Сгенерировать константу.
         * @return Заданное значение.
         */
        int generate() override;
    };
}
