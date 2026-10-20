#include "Mixture.h"
#include "TextUtils.h"

Mixture::Mixture(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, const std::string& producer,
    const std::vector<std::string>& indications, const double volumeMl)
    : Medicine(title, bestBefore, summary, cost, producer, indications, "Сироп", MakeDetails(volumeMl)), volumeMl_(volumeMl)
{
}

double Mixture::VolumeMl() const 
{ 
    return volumeMl_; 
}

std::string Mixture::MakeDetails(const double volumeMl)
{
    return "объём флакона: " + TextUtils::Number(volumeMl) + " мл";
}
