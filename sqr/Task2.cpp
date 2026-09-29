#include "Task2.h"
#include <vector>
#include <utility>

using namespace std;

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

    const vector<int>& firstRow = this->matrix->data[0];

    size_t writeIndex = 0;
    for (size_t i = 0; i < oldRows; ++i)
    {
        result.data[writeIndex++] = this->matrix->data[i];

        if (i % 2 == 1)
        {
            result.data[writeIndex++] = firstRow;
        }
    }

    swap(this->matrix->data, result.data);
    swap(this->matrix->rows, newRows)
    swap(this->matrix->cols, oldCols);
}
