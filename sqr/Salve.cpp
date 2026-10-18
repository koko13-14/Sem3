#include "Salve.h"
#include "TextUtils.h"

Salve::Salve(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, const double cost, const std::string& producer,
    const std::vector<std::string>& indications, const double massG)
    : Medicine(title, bestBefore, summary, cost, producer, indications, "Мазь", MakeDetails(massG)), massG_(massG)
{
}

double Salve::MassG() const 
{ 
    return massG_; 
}

std::string Salve::MakeDetails(const double massG)
{
    return "масса тюбика: " + TextUtils::Number(massG) + " г";
}
