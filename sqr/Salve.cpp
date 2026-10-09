#include "Salve.h"
#include "TextUtils.h"

Salve::Salve(std::string title, CalendarDate bestBefore, std::string summary, double cost, std::string producer, std::vector<std::string> indications, double massG)
    : Medicine(std::move(title), bestBefore, std::move(summary), cost, std::move(producer), std::move(indications)), massG_(massG)
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
