#include <iostream>
#include <memory>
#include <vector>

#include "AptekaLibrary.h"

namespace
{
    /* «Сегодня» для демонстрации — фиксированная дата, чтобы отчёты
    * за неделю/месяц/год были предсказуемыми.
    */
    const CalendarDate kToday(2026, 10, 3);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Drugstore store("Аптека на Ленина");

    // Коллекция объектов базового типа, заполненная наследниками.
    std::vector<std::shared_ptr<Medicine>> shelf;

    shelf.push_back(std::make_shared<Pills>("Парацетамол", CalendarDate(2027, 1, 1),
        "обезболивающее и жаропонижающее", 45.50, "Фармстандарт", 
        std::vector<std::string>{"простуда", "головная боль"}, 500.0, 20));

    shelf.push_back(std::make_shared<Mixture>("Доктор МОМ", CalendarDate(2027, 6, 1), "отхаркивающий сироп",
        210.00, "Юник Фармасьютикал", std::vector<std::string>{"кашель"}, 100.0));

    shelf.push_back(std::make_shared<Salve>("Финалгон", CalendarDate(2028, 3, 1), "согревающая мазь", 
        320.00, "БИ", std::vector<std::string>{"боль в мышцах"}, 20.0));

    shelf.push_back(std::make_shared<Ampoules>("Диклофенак", CalendarDate(2027, 9, 1), "противовоспалительное", 
        150.00, "Хемофарм", std::vector<std::string>{"воспаление"}, 3.0, 5));

    for (const auto& item : shelf)
    {
        store.Add(item);
    }

    // Журнал продаж.
    store.Record(Purchase("Парацетамол", CalendarDate(2026, 9, 14), 3, 136.50));
    store.Record(Purchase("Парацетамол", CalendarDate(2026, 8, 25), 5, 227.50));
    store.Record(Purchase("Парацетамол", CalendarDate(2024, 5, 1), 1, 45.50));
    store.Record(Purchase("Доктор МОМ", CalendarDate(2026, 9, 10), 2, 420.00));

    std::cout << "=== Справочник лекарств аптеки \"" << store.Name() << "\" ===\n";
    for (const auto& item : shelf)          // итерация по базовому типу
    {
        std::cout << item->Describe() << '\n';
    }

    std::cout << "\n=== Продажи Парацетамола за неделю ===\n";
    for (const auto& p : store.SalesInRange("Парацетамол", ReportRange::Week, kToday))
    {
        std::cout << p.Describe() << '\n';
    }
    std::cout << "Итого за неделю: " << store.TotalSold("Парацетамол", ReportRange::Week, kToday) << " шт., "
        << TextUtils::Money(store.TotalIncome("Парацетамол", ReportRange::Week, kToday)) << " руб.\n";

    std::cout << "\n=== Продажи Парацетамола за год ===\n";
    std::cout << "Итого за год: " << store.TotalSold("Парацетамол", ReportRange::Year, kToday) << " шт., " 
        << TextUtils::Money(store.TotalIncome("Парацетамол", ReportRange::Year, kToday)) << " руб.\n";

    std::cout << "\n=== Лекарства от кашля ===\n";
    for (const auto& item : store.ForIllness("кашель"))
    {
        std::cout << item->Describe() << '\n';
    }

    return 0;
}
