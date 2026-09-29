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

namespace
{
    /**
     * @brief выбор способа заполнения матрицы.
     */
    enum class MenuOption : int
    {
        Random = 1,
        IStream,
        Zero,
        Constant
    };

    /**
     * @brief Преобразует способ заполнения в строку для меню.
     * @param method Выбранный способ заполнения.
     * @return Текст пункта меню.
     */
    string toDescription(const FillMethod method)
    {
        switch (method)
        {
            case FillMethod::Random:   
                return "случайные числа";
            case FillMethod::Stream:   
                return "ввод с клавиатуры";
            case FillMethod::Zero:     
                return "нули";
            case FillMethod::Constant: 
                return "константное значение";
        }
        return "";
}

    constexpr int kDefaultMinValue = -100;
    constexpr int kDefaultMaxValue =  100;
}

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

    cout << "\nКак заполнить матрицу:\n";
    for (int i = 1; i <= 4; ++i)
    {
        const auto method = static_cast<FillMethod>(i);
        cout << i << " - " << toDescription(method) << '\n';
    }
    cout << "Номер пункта: ";

    int choice = 0;
    cin >> choice;

    unique_ptr<Generator> generator;

    switch (choice)
    {
    case MenuOption::Random:
        generator = make_unique<RandomGenerator>(kDefaultMinValue, kDefaultMaxValue);
        break;
    case MenuOption::IStream:
        generator = make_unique<IStreamGenerator>(cin);
        break;
    case MenuOption::Zero:
        generator = make_unique<ZeroGenerator>();
        break;
    case MenuOption::Constant:
    {
        int value = 0;
        cout << "Введите константу: ";
        cin >> value;
        generator = make_unique<ConstantGenerator>(value);
        break;
    }
    default:
        cout << "Неверный выбор. Используется генератор случайных чисел.\n";
        generator = make_unique<RandomGenerator>(kDefaultMinValue, kDefaultMaxValue);
        break;
    }

    Matrix<int> matrix(rows, cols, *generator);

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
