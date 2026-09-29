#include "Exercise.h"

miit::algebra::Exercise::Exercise(const Matrix<int>* matrix)
    : matrix{ matrix }
{
}

miit::algebra::Exercise::~Exercise()
{
}

miit::algebra::Matrix<int>* miit::algebra::Exercise::getMatrix() const
{
    return this->matrix;
}
