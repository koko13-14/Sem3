#include "Salve.h"
#include "TextUtils.h"

Salve::Salve(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, 
    double cost, const std::string& producer, const std::vector<std::string>& indications, double massG)
    : Medicine(title, bestBefore, summary, cost, producer, indications), massG_(massG)
{
}

double Salve::MassG() const
{
    return massG_;
}

std::string Salve::DescribeForm() const
{
    return "Мазь";
}

std::string Salve::DescribeDetails() const
{
    return "масса тюбика: " + TextUtils::Number(massG_) + " г";
}
