#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Задание 2: вставить после каждой четной строки первую строку.
     */
    class Task2 : public Exercise
    {
    public:
        /**
         * @brief Конструктор.
         * @param matrix Указатель на матрицу.
         */
        Task2(Matrix<int>& matrix);

        /**
         * @brief Выполнить задание.
         */
        void solve() override;
    };
}
