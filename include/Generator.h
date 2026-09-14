#pragma once

namespace miit::algebra
{
    /**
     * @brief Абстрактный базовый класс генератора значений.
     */
    class Generator
    {
    public:
        /**
         * @brief Виртуальный деструктор.
         */
        virtual ~Generator() = 0;

        /**
         * @brief Сгенерировать очередное значение.
         * @return Целое число.
         */
        virtual int generate() = 0;
    };
}
