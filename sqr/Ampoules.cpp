#include "Ampoules.h"
#include "TextUtils.h"

Ampoules::Ampoules(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, const std::string& producer,
    const std::vector<std::string>& indications, const double ampouleMl, const int perPack)
    : Medicine(title, bestBefore, summary, cost, producer, indications, "Ампулы (раствор для инъекций)", MakeDetails(ampouleMl, perPack)),
    ampouleMl_(ampouleMl), perPack_(perPack)
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

std::string Ampoules::MakeDetails(const double ampouleMl, const int perPack)
{
    return "объём ампулы: " + TextUtils::Number(ampouleMl) + " мл, в упаковке: " +
        std::to_string(perPack) + " шт.";
}
