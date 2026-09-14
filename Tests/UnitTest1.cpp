#include "CppUnitTest.h"
#include "../Task1/Matrix.h"
#include "../Task1/Task1.h"
#include "../Task1/Task2.h"
#include "../Task1/ConstantGenerator.h"
#include "../Task1/ZeroGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace MatrixTestsVariant1
{
    TEST_CLASS(MatrixConstructorTests)
    {
    public:
        TEST_METHOD(ConstructorWithSizes_CreatesCorrectDimensions)
        {
            Matrix<int> matrix(2, 3);

            Assert::AreEqual<size_t>(2, matrix.getRows());
            Assert::AreEqual<size_t>(3, matrix.getCols());
        }

        TEST_METHOD(ConstructorWithSizes_InitializesZeros)
        {
            Matrix<int> matrix(2, 2);

            Assert::AreEqual(0, matrix[0][0]);
            Assert::AreEqual(0, matrix[1][1]);
        }
    };

    TEST_CLASS(MatrixAssignmentTests)
    {
    public:
        TEST_METHOD(AssignmentOperator_CopiesAllElements)
        {
            Matrix<int> original(2, 2);
            original[0][0] = 1;
            original[0][1] = 2;
            original[1][0] = 3;
            original[1][1] = 4;

            Matrix<int> copy(1, 1);
            copy = original;

            Assert::AreEqual<size_t>(2, copy.getRows());
            Assert::AreEqual<size_t>(2, copy.getCols());
            Assert::AreEqual(1, copy[0][0]);
            Assert::AreEqual(4, copy[1][1]);
        }
    };

    TEST_CLASS(MatrixShiftTests)
    {
    public:
        TEST_METHOD(ShiftLeft_RemovesFirstColumn)
        {
            Matrix<int> matrix(2, 3);
            matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
            matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;

            Matrix<int> result = matrix << 1;

            Assert::AreEqual<size_t>(2, result.getCols());
            Assert::AreEqual(2, result[0][0]);
            Assert::AreEqual(3, result[0][1]);
            Assert::AreEqual(5, result[1][0]);
            Assert::AreEqual(6, result[1][1]);
        }

        TEST_METHOD(ShiftRight_RemovesLastColumn)
        {
            Matrix<int> matrix(2, 3);
            matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
            matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;

            Matrix<int> result = matrix >> 1;

            Assert::AreEqual<size_t>(2, result.getCols());
            Assert::AreEqual(1, result[0][0]);
            Assert::AreEqual(2, result[0][1]);
            Assert::AreEqual(4, result[1][0]);
            Assert::AreEqual(5, result[1][1]);
        }
    };

    TEST_CLASS(GeneratorTests)
    {
    public:
        TEST_METHOD(ConstantGenerator_FillsWithConstant)
        {
            Matrix<int> matrix(2, 2);
            ConstantGenerator generator(7);
            matrix.fill(generator);

            Assert::AreEqual(7, matrix[0][0]);
            Assert::AreEqual(7, matrix[0][1]);
            Assert::AreEqual(7, matrix[1][0]);
            Assert::AreEqual(7, matrix[1][1]);
        }

        TEST_METHOD(ZeroGenerator_FillsWithZeros)
        {
            Matrix<int> matrix(2, 2);
            ZeroGenerator generator;
            matrix.fill(generator);

            Assert::AreEqual(0, matrix[0][0]);
            Assert::AreEqual(0, matrix[1][1]);
        }
    };

    TEST_CLASS(Task1Tests)
    {
    public:
        // Задание 1: заменить максимальный по модулю элемент каждой строки
        // на противоположный по знаку.

        TEST_METHOD(ReplacesMaxAbsInEachRowWithOppositeSign)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 1;  matrix[0][1] = -5;
            matrix[1][0] = 3;  matrix[1][1] = 2;

            Task1 task(&matrix);
            task.solve();

            // Строка 0: max |.| = 5 (элемент -5) -> 5
            Assert::AreEqual(1, matrix[0][0]);
            Assert::AreEqual(5, matrix[0][1]);

            // Строка 1: max |.| = 3 (элемент 3) -> -3
            Assert::AreEqual(-3, matrix[1][0]);
            Assert::AreEqual(2, matrix[1][1]);
        }

        TEST_METHOD(SingleElementRow_NegatesIt)
        {
            Matrix<int> matrix(1, 1);
            matrix[0][0] = 4;

            Task1 task(&matrix);
            task.solve();

            Assert::AreEqual(-4, matrix[0][0]);
        }

        TEST_METHOD(AlreadyNegativeMaxAbs_BecomesPositive)
        {
            Matrix<int> matrix(1, 3);
            matrix[0][0] = -8;
            matrix[0][1] = 2;
            matrix[0][2] = 3;

            Task1 task(&matrix);
            task.solve();

            Assert::AreEqual(8, matrix[0][0]);
            Assert::AreEqual(2, matrix[0][1]);
            Assert::AreEqual(3, matrix[0][2]);
        }
    };

    TEST_CLASS(Task2Tests)
    {
    public:
        // Задание 2: вставить после каждой четной строки первую строку.

        TEST_METHOD(InsertsFirstRowAfterEachEvenRow)
        {
            Matrix<int> matrix(4, 2);
            // Строка 1 (индекс 0) — нечетная
            matrix[0][0] = 1; matrix[0][1] = 2;
            // Строка 2 (индекс 1) — четная
            matrix[1][0] = 3; matrix[1][1] = 4;
            // Строка 3 (индекс 2) — нечетная
            matrix[2][0] = 5; matrix[2][1] = 6;
            // Строка 4 (индекс 3) — четная
            matrix[3][0] = 7; matrix[3][1] = 8;

            Task2 task(&matrix);
            task.solve();

            // Ожидаем 6 строк:
            // [1,2], [3,4], [1,2], [5,6], [7,8], [1,2]
            Assert::AreEqual<size_t>(6, matrix.getRows());

            Assert::AreEqual(1, matrix[0][0]);
            Assert::AreEqual(2, matrix[0][1]);
            Assert::AreEqual(3, matrix[1][0]);
            Assert::AreEqual(4, matrix[1][1]);
            Assert::AreEqual(1, matrix[2][0]);   // вставка после строки 2
            Assert::AreEqual(2, matrix[2][1]);
            Assert::AreEqual(5, matrix[3][0]);
            Assert::AreEqual(6, matrix[3][1]);
            Assert::AreEqual(7, matrix[4][0]);
            Assert::AreEqual(8, matrix[4][1]);
            Assert::AreEqual(1, matrix[5][0]);   // вставка после строки 4
            Assert::AreEqual(2, matrix[5][1]);
        }

        TEST_METHOD(NoEvenRows_NoInsertion)
        {
            Matrix<int> matrix(3, 1);
            matrix[0][0] = 10;
            matrix[1][0] = 20;
            matrix[2][0] = 30;

            Task2 task(&matrix);
            task.solve();

            // Четных строк нет (строки 1 и 3 — нечетные), размер не меняется
            Assert::AreEqual<size_t>(3, matrix.getRows());
            Assert::AreEqual(10, matrix[0][0]);
            Assert::AreEqual(30, matrix[2][0]);
        }

        TEST_METHOD(EmptyMatrix_DoesNothing)
        {
            Matrix<int> matrix(0, 0);
            Task2 task(&matrix);
            task.solve();

            Assert::AreEqual<size_t>(0, matrix.getRows());
        }
    };
}
