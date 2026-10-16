#include "Ampoules.h"
#include "TextUtils.h"

Ampoules::Ampoules(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost,
    const std::string& producer, const std::vector<std::string>& indications, const double ampouleMl, const int perPack)
    : Medicine(title, bestBefore, summary, cost, producer, indications), ampouleMl_(ampouleMl), perPack_(perPack)
{
}

double Ampoules::AmpouleMl() const 
{
    return ampouleMl_; 
}

int Ampoules::PerPack() const 
{
    return perPack_; 
}

std::string Ampoules::DescribeForm() const 
{ 
    return "Ампулы (раствор для инъекций)"; 
}

std::string Ampoules::DescribeDetails() const
{
    return "объём ампулы: " + TextUtils::Number(ampouleMl_) + " мл, в упаковке: " + std::to_string(perPack_) + " шт.";
}
