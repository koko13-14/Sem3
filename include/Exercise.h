#pragma once

#include "Matrix.h"

namespace miit::algebra
{
    /**
     * @brief Базовый класс для заданий c матрицей.
     */
    class Exercise
    {
    protected:
        Matrix<int>* matrix;

    public:
        /**
         * @brief Конструктор.
         * @param matrix Указатель на матрицу.
         */
        Exercise(Matrix<int>* matrix);

        /**
         * @brief Виртуальный деструктор.
         */
        virtual ~Exercise();

        /**
         * @brief Решить задание.
         */
        virtual void solve() = 0;

        /**
         * @brief Получить матрицу.
         */
        Matrix<int>* getMatrix() const;
    };
}
