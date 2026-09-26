#include "CppUnitTest.h"
#include "../Task1/Matrix.h"
#include "../Task1/Task1.h"
#include "../Task1/Task2.h"
#include "../Task1/ConstantGenerator.h"
#include "../Task1/ZeroGenerator.h"
#include "../Task1/RandomGenerator.h"
#include "../Task1/IStreamGenerator.h"

#include <sstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace MatrixTestsVariant1
{
    // =====================================================================
    //  ТЕСТЫ КОНСТРУКТОРОВ И ДЕСТРУКТОРА
    // =====================================================================
    TEST_CLASS(MatrixConstructorTests)
    {
    public:
        TEST_METHOD(DefaultConstructor_CreatesEmptyMatrix)
        {
            Matrix<int> matrix;

            Assert::AreEqual<size_t>(0, matrix.getRows());
            Assert::AreEqual<size_t>(0, matrix.getCols());
        }

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
            Assert::AreEqual(0, matrix[0][1]);
            Assert::AreEqual(0, matrix[1][0]);
            Assert::AreEqual(0, matrix[1][1]);
        }

        TEST_METHOD(ConstructorWithZeroRows_CreatesEmpty)
        {
            Matrix<int> matrix(0, 5);

            Assert::AreEqual<size_t>(0, matrix.getRows());
            Assert::AreEqual<size_t>(5, matrix.getCols());
        }

        TEST_METHOD(CopyConstructor_CopiesAllElements)
        {
            Matrix<int> original(2, 2);
            original[0][0] = 1;
            original[0][1] = 2;
            original[1][0] = 3;
            original[1][1] = 4;

            Matrix<int> copy(original);

            Assert::AreEqual<size_t>(2, copy.getRows());
            Assert::AreEqual<size_t>(2, copy.getCols());
            Assert::AreEqual(1, copy[0][0]);
            Assert::AreEqual(2, copy[0][1]);
            Assert::AreEqual(3, copy[1][0]);
            Assert::AreEqual(4, copy[1][1]);

            // Изменение копии не влияет на оригинал
            copy[0][0] = 99;
            Assert::AreEqual(1, original[0][0]);
        }

        TEST_METHOD(MoveConstructor_TransfersData)
        {
            Matrix<int> original(2, 2);
            original[0][0] = 5;
            original[1][1] = 7;

            Matrix<int> moved(std::move(original));

            Assert::AreEqual<size_t>(2, moved.getRows());
            Assert::AreEqual<size_t>(2, moved.getCols());
            Assert::AreEqual(5, moved[0][0]);
            Assert::AreEqual(7, moved[1][1]);

            // Перемещённый объект должен быть в валидном (пустом) состоянии
            Assert::AreEqual<size_t>(0, original.getRows());
            Assert::AreEqual<size_t>(0, original.getCols());
        }
    };

    // =====================================================================
    //  ТЕСТЫ ОПЕРАТОРОВ ПРИСВАИВАНИЯ
    // =====================================================================
    TEST_CLASS(MatrixAssignmentTests)
    {
    public:
        TEST_METHOD(CopyAssignment_CopiesAllElements)
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

        TEST_METHOD(SelfAssignment_DoesNotBreakMatrix)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 1;
            matrix[1][1] = 4;

            matrix = matrix;

            Assert::AreEqual<size_t>(2, matrix.getRows());
            Assert::AreEqual(1, matrix[0][0]);
            Assert::AreEqual(4, matrix[1][1]);
        }

        TEST_METHOD(MoveAssignment_TransfersData)
        {
            Matrix<int> source(2, 2);
            source[0][0] = 9;
            source[1][1] = 8;

            Matrix<int> target(1, 1);
            target = std::move(source);

            Assert::AreEqual<size_t>(2, target.getRows());
            Assert::AreEqual(9, target[0][0]);
            Assert::AreEqual(8, target[1][1]);

            Assert::AreEqual<size_t>(0, source.getRows());
        }
    };

    // =====================================================================
    //  ТЕСТЫ ДОСТУПА ПО ИНДЕКСУ
    // =====================================================================
    TEST_CLASS(MatrixIndexOperatorTests)
    {
    public:
        TEST_METHOD(IndexOperator_AllowsReadingAndWriting)
        {
            Matrix<int> matrix(2, 3);

            matrix[0][0] = 10;
            matrix[0][1] = 20;
            matrix[0][2] = 30;
            matrix[1][0] = 40;
            matrix[1][1] = 50;
            matrix[1][2] = 60;

            Assert::AreEqual(10, matrix[0][0]);
            Assert::AreEqual(30, matrix[0][2]);
            Assert::AreEqual(60, matrix[1][2]);
        }

        TEST_METHOD(ConstIndexOperator_ReturnsConstReference)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 1;

            const Matrix<int>& constRef = matrix;

            Assert::AreEqual(1, constRef[0][0]);
        }
    };

    // =====================================================================
    //  ТЕСТЫ ОПЕРАТОРОВ СДВИГА
    // =====================================================================
    TEST_CLASS(MatrixShiftTests)
    {
    public:
        TEST_METHOD(ShiftLeftByOne_RemovesFirstColumn)
        {
            Matrix<int> matrix(2, 3);
            matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
            matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;

            Matrix<int> result = matrix << 1;

            Assert::AreEqual<size_t>(2, result.getRows());
            Assert::AreEqual<size_t>(2, result.getCols());
            Assert::AreEqual(2, result[0][0]);
            Assert::AreEqual(3, result[0][1]);
            Assert::AreEqual(5, result[1][0]);
            Assert::AreEqual(6, result[1][1]);

            // Оригинал не должен измениться
            Assert::AreEqual<size_t>(3, matrix.getCols());
            Assert::AreEqual(1, matrix[0][0]);
        }

        TEST_METHOD(ShiftLeftByTwo_RemovesTwoColumns)
        {
            Matrix<int> matrix(1, 4);
            matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3; matrix[0][3] = 4;

            Matrix<int> result = matrix << 2;

            Assert::AreEqual<size_t>(2, result.getCols());
            Assert::AreEqual(3, result[0][0]);
            Assert::AreEqual(4, result[0][1]);
        }

        TEST_METHOD(ShiftRightByOne_RemovesLastColumn)
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

            Assert::AreEqual<size_t>(3, matrix.getCols());
            Assert::AreEqual(3, matrix[0][2]);
        }

        TEST_METHOD(ShiftRightByTwo_RemovesTwoLastColumns)
        {
            Matrix<int> matrix(1, 4);
            matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3; matrix[0][3] = 4;

            Matrix<int> result = matrix >> 2;

            Assert::AreEqual<size_t>(2, result.getCols());
            Assert::AreEqual(1, result[0][0]);
            Assert::AreEqual(2, result[0][1]);
        }
    };

    // =====================================================================
    //  ТЕСТЫ ГЕНЕРАТОРОВ
    // =====================================================================
    TEST_CLASS(GeneratorTests)
    {
    public:
        TEST_METHOD(ZeroGenerator_FillsMatrixWithZeros)
        {
            Matrix<int> matrix(2, 3);
            ZeroGenerator generator;

            matrix.fill(generator);

            for (size_t i = 0; i < matrix.getRows(); ++i)
                for (size_t j = 0; j < matrix.getCols(); ++j)
                    Assert::AreEqual(0, matrix[i][j]);
        }

        TEST_METHOD(ConstantGenerator_FillsMatrixWithConstant)
        {
            Matrix<int> matrix(2, 3);
            ConstantGenerator generator(42);

            matrix.fill(generator);

            for (size_t i = 0; i < matrix.getRows(); ++i)
                for (size_t j = 0; j < matrix.getCols(); ++j)
                    Assert::AreEqual(42, matrix[i][j]);
        }

        TEST_METHOD(IStreamGenerator_ReadsValuesFromStream)
        {
            std::istringstream input("1 2 3 4");
            Matrix<int> matrix(2, 2);
            IStreamGenerator generator(input);

            matrix.fill(generator);

            Assert::AreEqual(1, matrix[0][0]);
            Assert::AreEqual(2, matrix[0][1]);
            Assert::AreEqual(3, matrix[1][0]);
            Assert::AreEqual(4, matrix[1][1]);
        }

        TEST_METHOD(RandomGenerator_FillsMatrixInRange)
        {
            Matrix<int> matrix(5, 5);
            RandomGenerator generator(-10, 10);

            matrix.fill(generator);

            for (size_t i = 0; i < matrix.getRows(); ++i)
            {
                for (size_t j = 0; j < matrix.getCols(); ++j)
                {
                    Assert::IsTrue(matrix[i][j] >= -10);
                    Assert::IsTrue(matrix[i][j] <= 10);
                }
            }
        }
    };

    // =====================================================================
    //  ТЕСТЫ toString
    // =====================================================================
    TEST_CLASS(MatrixToStringTests)
    {
    public:
        TEST_METHOD(ToString_FormatsElementsWithSpacesAndNewlines)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 1;
            matrix[0][1] = 2;
            matrix[1][0] = 3;
            matrix[1][1] = 4;

            std::string expected = "1 2\n3 4\n";

            Assert::AreEqual(expected, matrix.toString());
        }

        TEST_METHOD(ToString_EmptyMatrix_ReturnsEmptyString)
        {
            Matrix<int> matrix(0, 0);

            Assert::AreEqual(std::string(""), matrix.toString());
        }

        TEST_METHOD(ToString_SingleElement_NoTrailingSpace)
        {
            Matrix<int> matrix(1, 1);
            matrix[0][0] = 7;

            Assert::AreEqual(std::string("7\n"), matrix.toString());
        }
    };

    // =====================================================================
    //  ТЕСТЫ SWAP
    // =====================================================================
    TEST_CLASS(MatrixSwapTests)
    {
    public:
        TEST_METHOD(Swap_ExchangesContents)
        {
            Matrix<int> a(2, 2);
            a[0][0] = 1; a[0][1] = 2;
            a[1][0] = 3; a[1][1] = 4;

            Matrix<int> b(1, 3);
            b[0][0] = 9; b[0][1] = 8; b[0][2] = 7;

            a.swap(b);

            Assert::AreEqual<size_t>(1, a.getRows());
            Assert::AreEqual<size_t>(3, a.getCols());
            Assert::AreEqual(9, a[0][0]);
            Assert::AreEqual(7, a[0][2]);

            Assert::AreEqual<size_t>(2, b.getRows());
            Assert::AreEqual<size_t>(2, b.getCols());
            Assert::AreEqual(1, b[0][0]);
            Assert::AreEqual(4, b[1][1]);
        }
    };

    // =====================================================================
    //  ТЕСТЫ ЗАДАНИЯ 1
    //  Заменить максимальный по модулю элемент каждой строки
    //  на противоположный по знаку.
    // =====================================================================
    TEST_CLASS(Task1Tests)
    {
    public:
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

        TEST_METHOD(AllZeros_NoChange)
        {
            Matrix<int> matrix(2, 2);
            Task1 task(&matrix);
            task.solve();

            Assert::AreEqual(0, matrix[0][0]);
            Assert::AreEqual(0, matrix[1][1]);
        }

        TEST_METHOD(MultipleRows_MaxAbsInEachRowChanged)
        {
            Matrix<int> matrix(3, 3);
            matrix[0][0] = -10; matrix[0][1] = 1;  matrix[0][2] = 2;
            matrix[1][0] = 3;   matrix[1][1] = -7; matrix[1][2] = 1;
            matrix[2][0] = 1;   matrix[2][1] = 2;  matrix[2][2] = 9;

            Task1 task(&matrix);
            task.solve();

            // Строка 0: max |.| = 10 (-10) -> 10
            Assert::AreEqual(10, matrix[0][0]);
            Assert::AreEqual(1,  matrix[0][1]);
            Assert::AreEqual(2,  matrix[0][2]);

            // Строка 1: max |.| = 7 (-7) -> 7
            Assert::AreEqual(3, matrix[1][0]);
            Assert::AreEqual(7, matrix[1][1]);
            Assert::AreEqual(1, matrix[1][2]);

            // Строка 2: max |.| = 9 (9) -> -9
            Assert::AreEqual(1,  matrix[2][0]);
            Assert::AreEqual(2,  matrix[2][1]);
            Assert::AreEqual(-9, matrix[2][2]);
        }

        TEST_METHOD(EmptyMatrix_DoesNothing)
        {
            Matrix<int> matrix(0, 0);
            Task1 task(&matrix);
            task.solve();

            Assert::AreEqual<size_t>(0, matrix.getRows());
        }
    };

    // =====================================================================
    //  ТЕСТЫ ЗАДАНИЯ 2
    //  Вставить после каждой четной строки первую строку.
    // =====================================================================
    TEST_CLASS(Task2Tests)
    {
    public:
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
            Assert::AreEqual<size_t>(2, matrix.getCols());

            Assert::AreEqual(1, matrix[0][0]); Assert::AreEqual(2, matrix[0][1]);
            Assert::AreEqual(3, matrix[1][0]); Assert::AreEqual(4, matrix[1][1]);
            Assert::AreEqual(1, matrix[2][0]); Assert::AreEqual(2, matrix[2][1]);
            Assert::AreEqual(5, matrix[3][0]); Assert::AreEqual(6, matrix[3][1]);
            Assert::AreEqual(7, matrix[4][0]); Assert::AreEqual(8, matrix[4][1]);
            Assert::AreEqual(1, matrix[5][0]); Assert::AreEqual(2, matrix[5][1]);
        }

        TEST_METHOD(NoEvenRows_NoInsertion)
        {
            Matrix<int> matrix(1, 2);
            matrix[0][0] = 10;
            matrix[0][1] = 20;

            Task2 task(&matrix);
            task.solve();

            // Строка 1 — нечетная, вставки нет
            Assert::AreEqual<size_t>(1, matrix.getRows());
            Assert::AreEqual(10, matrix[0][0]);
            Assert::AreEqual(20, matrix[0][1]);
        }

        TEST_METHOD(OnlyEvenRow_InsertsOnce)
        {
            Matrix<int> matrix(2, 1);
            matrix[0][0] = 10;
            matrix[1][0] = 20;

            Task2 task(&matrix);
            task.solve();

            // Строка 2 (индекс 1) — чётная, вставка после неё
            // Итого: [10], [20], [10]
            Assert::AreEqual<size_t>(3, matrix.getRows());
            Assert::AreEqual(10, matrix[0][0]);
            Assert::AreEqual(20, matrix[1][0]);
            Assert::AreEqual(10, matrix[2][0]);
        }

        TEST_METHOD(EmptyMatrix_DoesNothing)
        {
            Matrix<int> matrix(0, 0);
            Task2 task(&matrix);
            task.solve();

            Assert::AreEqual<size_t>(0, matrix.getRows());
        }

        TEST_METHOD(FirstRowPreservedAfterInsertions)
        {
            Matrix<int> matrix(4, 2);
            matrix[0][0] = 100; matrix[0][1] = 200;
            matrix[1][0] = 1;   matrix[1][1] = 2;
            matrix[2][0] = 3;   matrix[2][1] = 4;
            matrix[3][0] = 5;   matrix[3][1] = 6;

            Task2 task(&matrix);
            task.solve();

            // Первая строка не должна измениться
            Assert::AreEqual(100, matrix[0][0]);
            Assert::AreEqual(200, matrix[0][1]);
        }
    };
}
