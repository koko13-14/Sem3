#include "Task2.h"

miit::algebra::Task2::Task2(Matrix<int>& matrix)
    : Exercise(matrix)
{
}

void miit::algebra::Task2::solve()
{
    if (this->matrix == nullptr || this->matrix->getRows() == 0)
    {
        return;
    }

    std::vector<int> firstRow = this->matrix->data[0];

    for (size_t i = this->matrix->rows; i > 0; --i)
    {
        size_t index = i - 1;

        if (index % 2 == 1)
        {
            this->matrix->data.insert(this->matrix->data.begin() + index + 1, firstRow);
            ++this->matrix->rows;
        }
    }
}
