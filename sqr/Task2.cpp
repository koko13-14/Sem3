#include "Task2.h"
#include <vector>

miit::algebra::Task2::Task2(Matrix<int>& matrix)
    : Exercise(matrix)
{
}

void miit::algebra::Task2::solve()
{
    if (this->matrix == nullptr || this->matrix->rows == 0)
    {
        return;
    }

    const size_t oldRows = this->matrix->rows;
    const size_t oldCols = this->matrix->cols;

    const size_t insertionsCount = oldRows / 2;
    const size_t newRows = oldRows + insertionsCount;

    Matrix<int> result(newRows, oldCols);

    const std::vector<int>& firstRow = this->matrix->data[0];

    size_t writeIndex = 0;
    for (size_t i = 0; i < oldRows; ++i)
    {
        result.data[writeIndex++] = this->matrix->data[i];

        if (i % 2 == 1)
        {
            result.data[writeIndex++] = firstRow;
        }
    }

    this->matrix->data = std::move(result.data);
    this->matrix->rows = newRows;
    this->matrix->cols = oldCols;
}
