#include <iostream>
#include <vector>

#include "AptekaLibrary.h"

namespace
{
    // «Сегодня» для демонстрации.
    const CalendarDate kToday(2026, 10, 3);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Drugstore store("Аптека на Ленина");

    // Коллекция значений базового типа, заполненная наследниками.
    std::vector<Medicine> shelf;

    shelf.push_back(Pills(
        "Парацетамол", CalendarDate(2027, 1, 1),
        "обезболивающее и жаропонижающее", 45.50, "Фармстандарт",
        { "простуда", "головная боль" }, 500.0, 20));

    shelf.push_back(Mixture(
        "Доктор МОМ", CalendarDate(2027, 6, 1),
        "отхаркивающий сироп", 210.00, "Юник Фармасьютикал",
        { "кашель" }, 100.0));

    shelf.push_back(Salve(
        "Финалгон", CalendarDate(2028, 3, 1),
        "согревающая мазь", 320.00, "БИ",
        { "боль в мышцах" }, 20.0));

    shelf.push_back(Ampoules(
        "Диклофенак", CalendarDate(2027, 9, 1),
        "противовоспалительное", 150.00, "Хемофарм",
        { "воспаление" }, 3.0, 5));

    for (const auto& item : shelf)
    {
        store.Add(item);
    }

    store.Record(Purchase("Парацетамол", CalendarDate(2026, 9, 14), 3, 136.50));
    store.Record(Purchase("Парацетамол", CalendarDate(2026, 8, 25), 5, 227.50));
    store.Record(Purchase("Парацетамол", CalendarDate(2024, 5, 1), 1, 45.50));
    store.Record(Purchase("Доктор МОМ", CalendarDate(2026, 9, 10), 2, 420.00));

    std::cout << "=== Справочник лекарств аптеки \"" << store.Name() << "\" ===\n";
    for (const auto& item : store.All())
    {
        std::cout << item.Describe() << '\n';
    }

    std::cout << "\n=== Продажи Парацетамола за неделю ===\n";
    for (const auto& p : store.SalesInRange("Парацетамол", ReportRange::Week, kToday))
    {
        std::cout << p.Describe() << '\n';
    }
    std::cout << "Итого за неделю: "
        << store.TotalSold("Парацетамол", ReportRange::Week, kToday)
        << " шт., "
        << TextUtils::Money(store.TotalIncome("Парацетамол", ReportRange::Week, kToday))
        << " руб.\n";

    std::cout << "\n=== Продажи Парацетамола за год ===\n";
    std::cout << "Итого за год: "
        << store.TotalSold("Парацетамол", ReportRange::Year, kToday)
        << " шт., "
        << TextUtils::Money(store.TotalIncome("Парацетамол", ReportRange::Year, kToday))
        << " руб.\n";

    std::cout << "\n=== Лекарства от кашля ===\n";
    for (const auto& m : store.ForIllness("кашель"))
    {
        std::cout << m.Describe() << '\n';
    }

    return 0;
}
