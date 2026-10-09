#include "Mixture.h"
#include "TextUtils.h"

Mixture::Mixture(std::string title, CalendarDate bestBefore, std::string summary, double cost,  std::string producer, std::vector<std::string> indications, double volumeMl)
    : Medicine(std::move(title), bestBefore, std::move(summary), cost, std::move(producer), std::move(indications)), volumeMl_(volumeMl)
{
}

double Mixture::VolumeMl() const 
{ 
    return volumeMl_; 
}

std::string Mixture::DescribeForm() const
{
    return "Сироп"; 
}

std::string Mixture::DescribeDetails() const
{
    return "объём флакона: " + TextUtils::Number(volumeMl_) + " мл";
}
