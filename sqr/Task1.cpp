#include "Task1.h"
#include <cstdlib>

miit::algebra::Task1::Task1(Matrix<int>& matrix)
    : Exercise(matrix)
{
}

void miit::algebra::Task1::solve()
{
    if (this->matrix == nullptr || this->matrix->rows == 0)
    {
        return;
    }

    for (size_t i = 0; i < this->matrix->rows; ++i)
    {
        size_t maxAbsIndex = 0;
        int maxAbsValue = std::abs(this->matrix->data[i][0]);

        for (size_t j = 1; j < this->matrix->cols; ++j)
        {
            const int currentAbs = std::abs(this->matrix->data[i][j]);
            if (currentAbs > maxAbsValue)
            {
                maxAbsValue = currentAbs;
                maxAbsIndex = j;
            }
        }

        this->matrix->data[i][maxAbsIndex] = -this->matrix->data[i][maxAbsIndex];
    }
}
