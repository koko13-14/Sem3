#include "Matrix.h"
#include <sstream>
#include <stdexcept>

using namespace std;

namespace miit::algebra
{
    template <typename T>
    Matrix<T>::Matrix()
        : rows{ 0 }, cols{ 0 }
    {
    }

    template <typename T>
    Matrix<T>::Matrix(const size_t rows, const size_t cols)
        : rows{ rows }, cols{ cols }
    {
        this->data.resize(rows);
        for (size_t i = 0; i < rows; ++i)
        {
            this->data[i].resize(cols);
        }
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix& other)
        : data{ other.data }, rows{ other.rows }, cols{ other.cols }
    {
    }

    template <typename T>
    Matrix<T>::Matrix(Matrix&& other) noexcept
        : data{ move(other.data) }, rows{ other.rows }, cols{ other.cols }
    {
        other.rows = 0;
        other.cols = 0;
    }

    template <typename T>
    Matrix<T>::~Matrix()
    {
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& other)
    {
        if (this != &other)
        {
            this->data = other.data;
            this->rows = other.rows;
            this->cols = other.cols;
        }
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
    {
        if (this != &other)
        {
            this->data = move(other.data);
            this->rows = other.rows;
            this->cols = other.cols;
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }

    template <typename T>
    vector<T>& Matrix<T>::operator[](const size_t index)
    {
        return this->data[index];
    }

    template <typename T>
    const vector<T>& Matrix<T>::operator[](const size_t index) const
    {
        return this->data[index];
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator<<(const size_t shift) const
    {
        Matrix<T> result(*this);
        for (size_t s = 0; s < shift && result.cols > 0; ++s)
        {
            result.removeColumn(0);
        }
        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator>>(const size_t shift) const
    {
        Matrix<T> result(*this);
        for (size_t s = 0; s < shift && result.cols > 0; ++s)
        {
            result.removeColumn(result.cols - 1);
        }
        return result;
    }

    template <typename T>
    size_t Matrix<T>::getRows() const
    {
        return this->rows;
    }

    template <typename T>
    size_t Matrix<T>::getCols() const
    {
        return this->cols;
    }

    template <typename T>
    void Matrix<T>::setRows(const size_t newRows)
    {
        this->rows = newRows;
        this->data.resize(newRows);
        for (size_t i = 0; i < newRows; ++i)
        {
            if (this->data[i].size() != this->cols)
            {
                this->data[i].resize(this->cols);
            }
        }
    }

    template <typename T>
    void Matrix<T>::setCols(const size_t newCols)
    {
        this->cols = newCols;
        for (size_t i = 0; i < this->rows; ++i)
        {
            this->data[i].resize(newCols);
        }
    }

    template <typename T>
    void Matrix<T>::fill(const Generator& generator)
    {
        for (size_t i = 0; i < this->rows; ++i)
        {
            for (size_t j = 0; j < this->cols; ++j)
            {
                this->data[i][j] = generator.generate();
            }
        }
    }

    template <typename T>
    string Matrix<T>::toString() const
    {
        ostringstream oss;
        for (size_t i = 0; i < this->rows; ++i)
        {
            for (size_t j = 0; j < this->cols; ++j)
            {
                oss << this->data[i][j];
                if (j + 1 < this->cols)
                {
                    oss << ' ';
                }
            }
            oss << '\n';
        }
        return oss.str();
    }

    template <typename T>
    void Matrix<T>::insertRowAfter(const vector<T>& row, const size_t pos)
    {
        this->data.insert(this->data.begin() + pos + 1, row);
        ++this->rows;
    }

    template <typename T>
    void Matrix<T>::removeRow(const size_t pos)
    {
        if (this->rows == 0)
        {
            return;
        }
        this->data.erase(this->data.begin() + pos);
        --this->rows;
    }

    template <typename T>
    void Matrix<T>::removeColumn(const size_t pos)
    {
        if (this->cols == 0)
        {
            return;
        }
        for (size_t i = 0; i < this->rows; ++i)
        {
            this->data[i].erase(this->data[i].begin() + pos);
        }
        --this->cols;
    }

    template <typename T>
    void Matrix<T>::insertColumnAfter(const vector<T>& col, const size_t pos)
    {
        for (size_t i = 0; i < this->rows; ++i)
        {
            this->data[i].insert(this->data[i].begin() + pos + 1, col[i]);
        }
        ++this->cols;
    }

    template <typename T>
    void Matrix<T>::swap(Matrix& other) noexcept
    {
        swap(this->data, other.data);
        swap(this->rows, other.rows);
        swap(this->cols, other.cols);
    }

}

template class miit::algebra::Matrix<int>;
