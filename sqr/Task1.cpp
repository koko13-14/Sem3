#include "Task1.h"
#include <cstdlib>

miit::algebra::Task1::Task1(Matrix<int>& matrix)
    : Exercise(matrix)
{
}

void miit::algebra::Task1::solve()
{
    if (this->matrix == nullptr || this->matrix->getRows() == 0)
    {
        return;
    }

    for (size_t i = 0; i < this->matrix->getRows(); ++i)
    {
        int maxAbs = std::abs((*this->matrix)[i][0]);
        size_t maxIndex = 0;

        for (size_t j = 1; j < this->matrix->getCols(); ++j)
        {
            int currentAbs = std::abs((*this->matrix)[i][j]);
            if (currentAbs > maxAbs)
            {
                maxAbs = currentAbs;
                maxIndex = j;
            }
        }

        (*this->matrix)[i][maxIndex] = -(*this->matrix)[i][maxIndex];
    }
}
