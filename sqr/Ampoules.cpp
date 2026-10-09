#include "Ampoules.h"
#include "TextUtils.h"

Ampoules::Ampoules(std::string title, CalendarDate bestBefore, std::string summary, double cost, std::string producer, 
    std::vector<std::string> indications, double ampouleMl, int perPack): Medicine(std::move(title), bestBefore, std::move(summary), 
        cost, std::move(producer), std::move(indications)), ampouleMl_(ampouleMl), perPack_(perPack)
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
