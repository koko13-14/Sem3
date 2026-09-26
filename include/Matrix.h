#pragma once

#include <vector>
#include <string>
#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Шаблонный класс матрицы.
     * @tparam T Тип хранимых элементов.
     */
    template <typename T>
    class Matrix
    {
    private:
        std::vector<std::vector<T>> data;
        size_t rows;
        size_t cols;

    public:
        /**
         * @brief Конструктор по умолчанию.
         */
        Matrix();

        /**
         * @brief Конструктор с размерами.
         * @param rows Количество строк.
         * @param cols Количество столбцов.
         */
        Matrix(const size_t rows, const size_t cols);

        /**
         * @brief Конструктор копирования.
         */
        Matrix(const Matrix& other);

        /**
         * @brief Конструктор перемещения.
         */
        Matrix(Matrix&& other) noexcept;

        /**
         * @brief Деструктор.
         */
        ~Matrix();

        /**
         * @brief Оператор присваивания копированием.
         */
        Matrix& operator=(const Matrix& other);

        /**
         * @brief Оператор присваивания перемещением.
         */
        Matrix& operator=(Matrix&& other) noexcept;

        /**
         * @brief Оператор доступа по индексу (неконстантный).
         * @param index Индекс строки.
         * @return Ссылка на строку.
         */
        std::vector<T>& operator[](const size_t index);

        /**
         * @brief Оператор доступа по индексу (константный).
         * @param index Индекс строки.
         * @return Константная ссылка на строку.
         */
        const std::vector<T>& operator[](const size_t index) const;

        /**
         * @brief Оператор сдвига влево (удаление первого столбца).
         * @param shift Количество столбцов для удаления слева.
         * @return Новая матрица.
         */
        Matrix operator<<(const size_t shift) const;

        /**
         * @brief Оператор сдвига вправо (удаление последнего столбца).
         * @param shift Количество столбцов для удаления справа.
         * @return Новая матрица.
         */
        Matrix operator>>(const size_t shift) const;

        /**
         * @brief Получить количество строк.
         */
        size_t getRows() const;

        /**
         * @brief Получить количество столбцов.
         */
        size_t getCols() const;

        /**
         * @brief Заполнить матрицу с помощью генератора.
         * @param generator Генератор значений.
         */
        void fill(const Generator& generator);

        /**
         * @brief Преобразовать матрицу в строку.
         * @return Строковое представление.
         */
        std::string toString() const;

        /**
         * @brief Обменять две матрицы.
         */
        void swap(Matrix& other) noexcept;
    };


}
