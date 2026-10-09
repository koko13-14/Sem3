#include "Pills.h"
#include "TextUtils.h"

Pills::Pills(std::string title, CalendarDate bestBefore, std::string summary, double cost,
    std::string producer, std::vector<std::string> indications, double doseMg, int perPack)
    : Medicine(std::move(title), bestBefore, std::move(summary), cost, std::move(producer), std::move(indications)), doseMg_(doseMg), perPack_(perPack)
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

std::string Pills::DescribeForm() const 
{ 
    return "Таблетки"; 
}

std::string Pills::DescribeDetails() const
{
    return "дозировка: " + TextUtils::Number(doseMg_) + " мг, в упаковке: " + std::to_string(perPack_) + " шт.";
}
