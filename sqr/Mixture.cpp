#include "Mixture.h"
#include "TextUtils.h"

Mixture::Mixture(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, 
    double cost, const std::string& producer, const std::vector<std::string>& indications, double volumeMl)
    : Medicine(title, bestBefore, summary, cost, producer, indications), volumeMl_(volumeMl)
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
