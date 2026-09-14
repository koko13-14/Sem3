#include "Task2.h"

miit::algebra::Task2::Task2(Matrix<int>* matrix)
    : Exercise(matrix)
{
}

void miit::algebra::Task2::solve()
{
    if (this->matrix == nullptr || this->matrix->getRows() == 0)
    {
        return;
    }

    std::vector<int> firstRow = (*this->matrix)[0];

    for (size_t i = this->matrix->getRows(); i > 0; --i)
    {
        size_t index = i - 1; 
        if ((index + 1) % 2 == 0)
        {
            this->matrix->insertRowAfter(firstRow, index);
        }
    }
}
