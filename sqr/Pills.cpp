#include "Pills.h"
#include "TextUtils.h"

Pills::Pills(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, const std::string& producer,
    const std::vector<std::string>& indications, const double doseMg, const int perPack)
    : Medicine(title, bestBefore, summary, cost, producer, indications, "Таблетки", MakeDetails(doseMg, perPack)), doseMg_(doseMg), perPack_(perPack)
{
}

double Pills::DoseMg() const 
{ 
    return doseMg_; 
}

int Pills::PerPack() const 
{ 
    return perPack_; 
}

std::string Pills::MakeDetails(const double doseMg, const int perPack)
{
    return "дозировка: " + TextUtils::Number(doseMg) + " мг, в упаковке: " +
        std::to_string(perPack) + " шт.";
}
