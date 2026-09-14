#include <iostream>
#include <memory>
#include <limits>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ZeroGenerator.h"
#include "ConstantGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace std;
using namespace miit::algebra;

/**
 * @brief Точка входа в программу.
 */
int main()
{
    setlocale(LC_ALL, "Russian");

    size_t rows = 0;
    size_t cols = 0;

    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;

    Matrix<int> matrix(rows, cols);

    cout << "\nВыберите способ заполнения:\n";
    cout << "1 - случайными числами\n";
    cout << "2 - вводом с клавиатуры\n";
    cout << "3 - нулями\n";
    cout << "4 - константным значением\n";
    cout << "Ваш выбор: ";

    int choice = 0;
    cin >> choice;

    unique_ptr<Generator> generator;

    switch (choice)
    {
    case 1:
        generator = make_unique<RandomGenerator>(-100, 100);
        break;
    case 2:
        generator = make_unique<IStreamGenerator>(cin);
        break;
    case 3:
        generator = make_unique<ZeroGenerator>();
        break;
    case 4:
    {
        int value = 0;
        cout << "Введите константу: ";
        cin >> value;
        generator = make_unique<ConstantGenerator>(value);
        break;
    }
    default:
        cout << "Неверный выбор. Используется генератор случайных чисел.\n";
        generator = make_unique<RandomGenerator>(-100, 100);
        break;
    }

    matrix.fill(*generator);

    cout << "\nИсходная матрица:\n";
    cout << matrix.toString();

    // Задание 1
    Matrix<int> matrix1 = matrix;
    Task1 task1(&matrix1);
    task1.solve();
    cout << "\nПосле задания 1 (замена максимального по модулю элемента каждой строки на противоположный):\n";
    cout << matrix1.toString();

    // Задание 2
    Matrix<int> matrix2 = matrix;
    Task2 task2(&matrix2);
    task2.solve();
    cout << "\nПосле задания 2 (вставка первой строки после каждой четной строки):\n";
    cout << matrix2.toString();

    // Демонстрация операторов сдвига
    cout << "\nДемонстрация оператора сдвига влево (удаление первого столбца):\n";
    Matrix<int> shiftedLeft = matrix << 1;
    cout << shiftedLeft.toString();

    cout << "\nДемонстрация оператора сдвига вправо (удаление последнего столбца):\n";
    Matrix<int> shiftedRight = matrix >> 1;
    cout << shiftedRight.toString();

    return 0;
}
