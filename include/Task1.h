#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Задание 1: заменить максимальный по модулю элемент каждой строки
     * на противоположный по знаку.
     */
    class Task1 : public Exercise
    {
    public:
        /**
         * @brief Конструктор.
         * @param matrix Указатель на матрицу.
         */
        Task1(Matrix<int>* matrix);

        /**
         * @brief Выполнить задание.
         */
        void solve() override;
    };
}
