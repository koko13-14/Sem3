#include "CppUnitTest.h"
#include "../Task2(11)/AptekaLibrary.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AptekaTests
{
    // =====================================================================
    //  CalendarDate
    // =====================================================================
    TEST_CLASS(CalendarDateTests)
    {
    public:
        TEST_METHOD(Ctor_ValidDate_StoresComponents)
        {
            const CalendarDate d(2026, 9, 16);
            Assert::AreEqual(2026, d.Year());
            Assert::AreEqual(9, d.Month());
            Assert::AreEqual(16, d.Day());
        }

        TEST_METHOD(Ctor_Month13_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([] {
                CalendarDate bad(2026, 13, 1);
                (void)bad;
                });
        }

        TEST_METHOD(Ctor_Month0_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([] {
                CalendarDate bad(2026, 0, 1);
                (void)bad;
                });
        }

        TEST_METHOD(Ctor_Feb30_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([] {
                CalendarDate bad(2026, 2, 30);
                (void)bad;
                });
        }

        TEST_METHOD(Ctor_Feb29_LeapYear_Ok)
        {
            const CalendarDate d(2028, 2, 29);
            Assert::AreEqual(29, d.Day());
        }

        TEST_METHOD(Ctor_Feb29_NonLeap_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([] {
                CalendarDate bad(2026, 2, 29);
                (void)bad;
                });
        }

        TEST_METHOD(FromString_Valid_Parses)
        {
            const CalendarDate d = CalendarDate::FromString("2026-09-16");
            Assert::AreEqual(2026, d.Year());
            Assert::AreEqual(9, d.Month());
            Assert::AreEqual(16, d.Day());
        }

        TEST_METHOD(FromString_WrongFormat_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([] {
                CalendarDate::FromString("16-09-2026");
                });
        }

        TEST_METHOD(FromString_WrongLength_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([] {
                CalendarDate::FromString("2026-9-16");
                });
        }

        TEST_METHOD(FromString_NonDigit_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([] {
                CalendarDate::FromString("2026-XX-16");
                });
        }

        TEST_METHOD(FromString_InvalidDate_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([] {
                CalendarDate::FromString("2026-02-30");
                });
        }

        TEST_METHOD(Getters_ReturnCtorValues)
        {
            const CalendarDate d(2025, 12, 31);
            Assert::AreEqual(2025, d.Year());
            Assert::AreEqual(12, d.Month());
            Assert::AreEqual(31, d.Day());
        }

        TEST_METHOD(AsString_LeadingZeros)
        {
            Assert::AreEqual(std::string("2026-03-05"),
                CalendarDate(2026, 3, 5).AsString());
        }

        TEST_METHOD(AsString_TwoDigit)
        {
            Assert::AreEqual(std::string("2026-12-25"),
                CalendarDate(2026, 12, 25).AsString());
        }

        TEST_METHOD(Serial_LaterDateIsGreater)
        {
            const CalendarDate a(2026, 1, 1);
            const CalendarDate b(2026, 1, 2);
            Assert::IsTrue(b.Serial() > a.Serial());
        }

        TEST_METHOD(Serial_SameDateEqual)
        {
            Assert::AreEqual(CalendarDate(2026, 9, 16).Serial(),
                CalendarDate(2026, 9, 16).Serial());
        }

        TEST_METHOD(DaysTo_SameDay_Zero)
        {
            const CalendarDate d(2026, 9, 16);
            Assert::AreEqual(0L, d.DaysTo(d));
        }

        TEST_METHOD(DaysTo_Week_Seven)
        {
            Assert::AreEqual(7L,
                CalendarDate(2026, 9, 9).DaysTo(CalendarDate(2026, 9, 16)));
        }

        TEST_METHOD(DaysTo_AcrossYear_Three)
        {
            Assert::AreEqual(3L,
                CalendarDate(2025, 12, 30).DaysTo(CalendarDate(2026, 1, 2)));
        }

        TEST_METHOD(DaysTo_Reverse_IsNegative)
        {
            Assert::AreEqual(-7L,
                CalendarDate(2026, 9, 16).DaysTo(CalendarDate(2026, 9, 9)));
        }

        TEST_METHOD(OperatorEqual_SameDates_True)
        {
            Assert::IsTrue(CalendarDate(2026, 1, 1) == CalendarDate(2026, 1, 1));
        }

        TEST_METHOD(OperatorNotEqual_DifferentDates_True)
        {
            Assert::IsTrue(CalendarDate(2026, 1, 1) != CalendarDate(2026, 1, 2));
        }

        TEST_METHOD(OperatorLess_True)
        {
            Assert::IsTrue(CalendarDate(2026, 1, 1) < CalendarDate(2026, 1, 2));
        }

        TEST_METHOD(OperatorLessOrEqual_Equal_True)
        {
            Assert::IsTrue(CalendarDate(2026, 1, 1) <= CalendarDate(2026, 1, 1));
        }

        TEST_METHOD(OperatorGreater_True)
        {
            Assert::IsTrue(CalendarDate(2026, 1, 2) > CalendarDate(2026, 1, 1));
        }

        TEST_METHOD(OperatorGreaterOrEqual_Equal_True)
        {
            Assert::IsTrue(CalendarDate(2026, 1, 1) >= CalendarDate(2026, 1, 1));
        }
    };

    // =====================================================================
    //  Medicine (базовый) и наследники
    // =====================================================================
    TEST_CLASS(MedicineTests)
    {
    public:
        TEST_METHOD(Title_ReturnsCtorValue)
        {
            Pills p("Парацетамол", CalendarDate(2027, 1, 1), "a", 10.0, "M",
                { "простуда" }, 500.0, 20);
            Assert::AreEqual(std::string("Парацетамол"), p.Title());
        }

        TEST_METHOD(BestBefore_ReturnsCtorValue)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 1.0, 1);
            Assert::AreEqual(2027, p.BestBefore().Year());
        }

        TEST_METHOD(Summary_ReturnsCtorValue)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "инструкция", 10.0, "M", {}, 1.0, 1);
            Assert::AreEqual(std::string("инструкция"), p.Summary());
        }

        TEST_METHOD(Cost_ReturnsCtorValue)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 45.5, "M", {}, 1.0, 1);
            Assert::AreEqual(45.5, p.Cost(), 0.0001);
        }

        TEST_METHOD(Producer_ReturnsCtorValue)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "Фармстандарт", {}, 1.0, 1);
            Assert::AreEqual(std::string("Фармстандарт"), p.Producer());
        }

        TEST_METHOD(Indications_ReturnsCtorList)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M",
                { "простуда", "кашель" }, 1.0, 1);
            Assert::AreEqual(std::size_t(2), p.Indications().size());
            Assert::AreEqual(std::string("простуда"), p.Indications()[0]);
        }

        TEST_METHOD(IsOutdated_Past_True)
        {
            Pills p("X", CalendarDate(2020, 1, 1), "a", 10.0, "M", {}, 1.0, 1);
            Assert::IsTrue(p.IsOutdated(CalendarDate(2026, 9, 16)));
        }

        TEST_METHOD(IsOutdated_Future_False)
        {
            Pills p("X", CalendarDate(2030, 1, 1), "a", 10.0, "M", {}, 1.0, 1);
            Assert::IsFalse(p.IsOutdated(CalendarDate(2026, 9, 16)));
        }

        TEST_METHOD(IsOutdated_SameDay_False)
        {
            Pills p("X", CalendarDate(2026, 9, 16), "a", 10.0, "M", {}, 1.0, 1);
            Assert::IsFalse(p.IsOutdated(CalendarDate(2026, 9, 16)));
        }

        TEST_METHOD(HelpsWith_Known_True)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M",
                { "простуда", "головная боль" }, 1.0, 1);
            Assert::IsTrue(p.HelpsWith("головная боль"));
        }

        TEST_METHOD(HelpsWith_CaseInsensitive_True)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M",
                { "Простуда" }, 1.0, 1);
            Assert::IsTrue(p.HelpsWith("простуда"));
        }

        TEST_METHOD(HelpsWith_Unknown_False)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M",
                { "простуда" }, 1.0, 1);
            Assert::IsFalse(p.HelpsWith("ангина"));
        }

        TEST_METHOD(Describe_ContainsTitleAndForm)
        {
            Pills p("Парацетамол", CalendarDate(2027, 1, 1), "a", 10.0, "M",
                { "простуда" }, 1.0, 1);
            const std::string text = p.Describe();
            Assert::IsTrue(text.find("Парацетамол") != std::string::npos);
            Assert::IsTrue(text.find("Таблетки") != std::string::npos);
        }

        TEST_METHOD(Describe_ContainsDetails)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M",
                {}, 500.0, 20);
            const std::string text = p.Describe();
            Assert::IsTrue(text.find("500") != std::string::npos);
            Assert::IsTrue(text.find("20") != std::string::npos);
        }

        TEST_METHOD(Describe_EmptyIndications_ShowsPlaceholder)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 1.0, 1);
            Assert::IsTrue(p.Describe().find("не указано") != std::string::npos);
        }

        TEST_METHOD(Describe_ThroughBasePointer_Polymorphic)
        {
            std::shared_ptr<Medicine> m = std::make_shared<Mixture>(
                "Пертуссин", CalendarDate(2027, 1, 1), "a", 10.0, "M",
                { "кашель" }, 125.0);

            const std::string text = m->Describe();
            Assert::IsTrue(text.find("Пертуссин") != std::string::npos);
            Assert::IsTrue(text.find("Сироп") != std::string::npos);
        }
    };

    // --- Pills ---
    TEST_CLASS(PillsTests)
    {
    public:
        TEST_METHOD(DescribeForm_ReturnsTabletki)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 1.0, 1);
            Assert::AreEqual(std::string("Таблетки"), p.DescribeForm());
        }

        TEST_METHOD(DoseMg_ReturnsCtorValue)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 500.0, 1);
            Assert::AreEqual(500.0, p.DoseMg(), 0.0001);
        }

        TEST_METHOD(PerPack_ReturnsCtorValue)
        {
            Pills p("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 1.0, 20);
            Assert::AreEqual(20, p.PerPack());
        }
    };

    // --- Mixture ---
    TEST_CLASS(MixtureTests)
    {
    public:
        TEST_METHOD(DescribeForm_ReturnsSirop)
        {
            Mixture m("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 100.0);
            Assert::AreEqual(std::string("Сироп"), m.DescribeForm());
        }

        TEST_METHOD(VolumeMl_ReturnsCtorValue)
        {
            Mixture m("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 125.0);
            Assert::AreEqual(125.0, m.VolumeMl(), 0.0001);
        }

        TEST_METHOD(Describe_ContainsVolume)
        {
            Mixture m("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 125.0);
            Assert::IsTrue(m.Describe().find("125") != std::string::npos);
        }
    };

    // --- Salve ---
    TEST_CLASS(SalveTests)
    {
    public:
        TEST_METHOD(DescribeForm_ReturnsMaz)
        {
            Salve s("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 20.0);
            Assert::AreEqual(std::string("Мазь"), s.DescribeForm());
        }

        TEST_METHOD(MassG_ReturnsCtorValue)
        {
            Salve s("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 30.0);
            Assert::AreEqual(30.0, s.MassG(), 0.0001);
        }

        TEST_METHOD(Describe_ContainsMass)
        {
            Salve s("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 30.0);
            Assert::IsTrue(s.Describe().find("30") != std::string::npos);
        }
    };

    // --- Ampoules ---
    TEST_CLASS(AmpoulesTests)
    {
    public:
        TEST_METHOD(DescribeForm_ReturnsAmpuly)
        {
            Ampoules a("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 3.0, 5);
            Assert::AreEqual(std::string("Ампулы (раствор для инъекций)"),
                a.DescribeForm());
        }

        TEST_METHOD(AmpouleMl_ReturnsCtorValue)
        {
            Ampoules a("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 3.0, 5);
            Assert::AreEqual(3.0, a.AmpouleMl(), 0.0001);
        }

        TEST_METHOD(PerPack_ReturnsCtorValue)
        {
            Ampoules a("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 3.0, 5);
            Assert::AreEqual(5, a.PerPack());
        }

        TEST_METHOD(Describe_ContainsVolumeAndCount)
        {
            Ampoules a("X", CalendarDate(2027, 1, 1), "a", 10.0, "M", {}, 3.0, 5);
            const std::string text = a.Describe();
            Assert::IsTrue(text.find("3") != std::string::npos);
            Assert::IsTrue(text.find("5") != std::string::npos);
        }
    };

    // =====================================================================
    //  Purchase
    // =====================================================================
    TEST_CLASS(PurchaseTests)
    {
    public:
        TEST_METHOD(Medicine_ReturnsCtorValue)
        {
            Purchase p("Парацетамол", CalendarDate(2026, 9, 14), 3, 136.5);
            Assert::AreEqual(std::string("Парацетамол"), p.Medicine());
        }

        TEST_METHOD(Date_ReturnsCtorValue)
        {
            Purchase p("X", CalendarDate(2026, 9, 14), 3, 10.0);
            Assert::AreEqual(2026, p.Date().Year());
            Assert::AreEqual(9, p.Date().Month());
            Assert::AreEqual(14, p.Date().Day());
        }

        TEST_METHOD(Count_ReturnsCtorValue)
        {
            Purchase p("X", CalendarDate(2026, 9, 14), 3, 10.0);
            Assert::AreEqual(3, p.Count());
        }

        TEST_METHOD(Sum_ReturnsCtorValue)
        {
            Purchase p("X", CalendarDate(2026, 9, 14), 3, 136.5);
            Assert::AreEqual(136.5, p.Sum(), 0.0001);
        }

        TEST_METHOD(Describe_ContainsAllFields)
        {
            Purchase p("Парацетамол", CalendarDate(2026, 9, 14), 3, 136.5);
            const std::string text = p.Describe();
            Assert::IsTrue(text.find("2026-09-14") != std::string::npos);
            Assert::IsTrue(text.find("Парацетамол") != std::string::npos);
            Assert::IsTrue(text.find("3") != std::string::npos);
            Assert::IsTrue(text.find("136.50") != std::string::npos);
        }
    };

    // =====================================================================
    //  TextUtils
    // =====================================================================
    TEST_CLASS(TextUtilsTests)
    {
    public:
        TEST_METHOD(Number_TwoDecimals)
        {
            Assert::AreEqual(std::string("123.50"), TextUtils::Number(123.5));
        }

        TEST_METHOD(Number_LeadingZeroInFraction)
        {
            Assert::AreEqual(std::string("0.05"), TextUtils::Number(0.05));
        }

        TEST_METHOD(Number_Negative)
        {
            Assert::AreEqual(std::string("-1.25"), TextUtils::Number(-1.25));
        }

        TEST_METHOD(Number_Zero)
        {
            Assert::AreEqual(std::string("0.00"), TextUtils::Number(0.0));
        }

        TEST_METHOD(Money_SameAsNumber)
        {
            Assert::AreEqual(TextUtils::Number(45.5), TextUtils::Money(45.5));
        }

        TEST_METHOD(SameIgnoreCase_Latin_True)
        {
            Assert::IsTrue(TextUtils::SameIgnoreCase("Hello", "hello"));
        }

        TEST_METHOD(SameIgnoreCase_Cyrillic_True)
        {
            Assert::IsTrue(TextUtils::SameIgnoreCase("Простуда", "простуда"));
        }

        TEST_METHOD(SameIgnoreCase_Different_False)
        {
            Assert::IsFalse(TextUtils::SameIgnoreCase("простуда", "ангина"));
        }

        TEST_METHOD(SameIgnoreCase_EmptyStrings_True)
        {
            Assert::IsTrue(TextUtils::SameIgnoreCase("", ""));
        }
    };

    // =====================================================================
    //  Drugstore — все три задания
    // =====================================================================
    namespace
    {
        const CalendarDate kBase(2026, 9, 16);

        Drugstore BuildSample()
        {
            Drugstore store("Test");

            store.Add(std::make_shared<Pills>(
                "Парацетамол", CalendarDate(2027, 1, 1), "a", 45.50, "M",
                { "простуда", "головная боль" }, 500.0, 20));

            store.Add(std::make_shared<Mixture>(
                "Доктор МОМ", CalendarDate(2027, 1, 1), "a", 210.00, "M",
                { "кашель" }, 100.0));

            store.Record(Purchase("Парацетамол", CalendarDate(2026, 9, 14), 3, 136.50));
            store.Record(Purchase("Парацетамол", CalendarDate(2026, 8, 25), 5, 227.50));
            store.Record(Purchase("Парацетамол", CalendarDate(2024, 5, 1), 1, 45.50));

            return store;
        }
    }

    TEST_CLASS(DrugstoreTests)
    {
    public:
        TEST_METHOD(Name_ReturnsCtorValue)
        {
            const Drugstore store("Аптека №1");
            Assert::AreEqual(std::string("Аптека №1"), store.Name());
        }

        TEST_METHOD(All_InitiallyEmpty)
        {
            const Drugstore store("Empty");
            Assert::IsTrue(store.All().empty());
        }

        TEST_METHOD(All_ReturnsAllAdded)
        {
            Assert::AreEqual(std::size_t(2), BuildSample().All().size());
        }

        TEST_METHOD(FindByName_CaseInsensitive)
        {
            auto found = BuildSample().FindByName("парацетамол");
            Assert::IsNotNull(found.get());
            Assert::AreEqual(std::string("Парацетамол"), found->Title());
        }

        TEST_METHOD(FindByName_Exact)
        {
            auto found = BuildSample().FindByName("Доктор МОМ");
            Assert::IsNotNull(found.get());
        }

        TEST_METHOD(FindByName_Missing_Null)
        {
            Assert::IsNull(BuildSample().FindByName("Аспирин").get());
        }

        TEST_METHOD(SalesInRange_Week_OnlyRecent)
        {
            const auto sales = BuildSample().SalesInRange(
                "Парацетамол", ReportRange::Week, kBase);
            Assert::AreEqual(std::size_t(1), sales.size());
            Assert::AreEqual(3, sales[0].Count());
        }

        TEST_METHOD(SalesInRange_Month_Two)
        {
            const auto sales = BuildSample().SalesInRange(
                "Парацетамол", ReportRange::Month, kBase);
            Assert::AreEqual(std::size_t(2), sales.size());
        }

        TEST_METHOD(SalesInRange_Year_Two)
        {
            const auto sales = BuildSample().SalesInRange(
                "Парацетамол", ReportRange::Year, kBase);
            Assert::AreEqual(std::size_t(2), sales.size());
        }

        TEST_METHOD(SalesInRange_Unknown_Empty)
        {
            Assert::IsTrue(BuildSample()
                .SalesInRange("Аспирин", ReportRange::Year, kBase)
                .empty());
        }

        TEST_METHOD(SalesInRange_CaseInsensitiveName)
        {
            Assert::AreEqual(std::size_t(1),
                BuildSample().SalesInRange("ПАРАЦЕТАМОЛ", ReportRange::Week, kBase).size());
        }

        TEST_METHOD(TotalSold_Week_Three)
        {
            Assert::AreEqual(3,
                BuildSample().TotalSold("Парацетамол", ReportRange::Week, kBase));
        }

        TEST_METHOD(TotalSold_Month_Eight)
        {
            Assert::AreEqual(8,
                BuildSample().TotalSold("Парацетамол", ReportRange::Month, kBase));
        }

        TEST_METHOD(TotalSold_Year_Eight)
        {
            Assert::AreEqual(8,
                BuildSample().TotalSold("Парацетамол", ReportRange::Year, kBase));
        }

        TEST_METHOD(TotalSold_Unknown_Zero)
        {
            Assert::AreEqual(0,
                BuildSample().TotalSold("Аспирин", ReportRange::Year, kBase));
        }

        TEST_METHOD(TotalIncome_Week_136_50)
        {
            Assert::AreEqual(136.50,
                BuildSample().TotalIncome("Парацетамол", ReportRange::Week, kBase),
                0.001);
        }

        TEST_METHOD(TotalIncome_Month_364_00)
        {
            Assert::AreEqual(364.00,
                BuildSample().TotalIncome("Парацетамол", ReportRange::Month, kBase),
                0.001);
        }

        TEST_METHOD(TotalIncome_Unknown_Zero)
        {
            Assert::AreEqual(0.0,
                BuildSample().TotalIncome("Аспирин", ReportRange::Year, kBase),
                0.001);
        }

        TEST_METHOD(ForIllness_Cough_One)
        {
            const auto list = BuildSample().ForIllness("кашель");
            Assert::AreEqual(std::size_t(1), list.size());
            Assert::AreEqual(std::string("Доктор МОМ"), list[0]->Title());
        }

        TEST_METHOD(ForIllness_Headache_One)
        {
            const auto list = BuildSample().ForIllness("головная боль");
            Assert::AreEqual(std::size_t(1), list.size());
            Assert::AreEqual(std::string("Парацетамол"), list[0]->Title());
        }

        TEST_METHOD(ForIllness_CaseInsensitive)
        {
            const auto list = BuildSample().ForIllness("КАШЕЛЬ");
            Assert::AreEqual(std::size_t(1), list.size());
        }

        TEST_METHOD(ForIllness_Unknown_Empty)
        {
            Assert::IsTrue(BuildSample().ForIllness("перелом").empty());
        }
    };
}
