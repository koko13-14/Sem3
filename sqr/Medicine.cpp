#include "Medicine.h"
#include "TextUtils.h"

Medicine::Medicine(const std::string& title, const CalendarDate& bestBefore, const std::string& summary, 
    const double cost, const std::string& producer, const std::vector<std::string>& indications)
    : title_(title), bestBefore_(bestBefore), summary_(summary), cost_(cost), producer_(producer), indications_(indications)
{
}

const std::string& Medicine::Title() const 
{ 
    return title_; 
}

const CalendarDate& Medicine::BestBefore() const 
{ 
    return bestBefore_; 
}

const std::string& Medicine::Summary() const 
{ 
    return summary_;
}

double Medicine::Cost() const 
{ 
    return cost_; 
}

const std::string& Medicine::Producer() const 
{ 
    return producer_; 
}

const std::vector<std::string>& Medicine::Indications() const 
{ 
    return indications_; 
}

bool Medicine::IsOutdated(const CalendarDate& at) const
{
    return bestBefore_ < at;
}

bool Medicine::HelpsWith(const std::string& illness) const
{
    for (const auto& item : indications_)
    {
        if (TextUtils::SameIgnoreCase(item, illness))
        {
            return true;
        }
    }
    return false;
}

std::string Medicine::Describe() const
{
    std::string list;
    for (std::size_t i = 0; i < indications_.size(); ++i)
    {
        if (i > 0) list += ", ";
        list += indications_[i];
    }
    if (list.empty()) list = "не указано";

    return title_ + " [" + DescribeForm() + "]" + " | цена: " + TextUtils::Money(cost_) + " руб." + " | изготовитель: " 
        + producer_ + " | годен до: " + bestBefore_.AsString() + " | применяется при: " + list + " | " + DescribeDetails() + " | " + summary_;
}
