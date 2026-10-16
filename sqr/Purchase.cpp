#include "Purchase.h"
#include "TextUtils.h"

Purchase::Purchase(const std::string& medicine, const CalendarDate& date, const int count, const double sum)
    : medicine_(medicine), date_(date), count_(count), sum_(sum)
{
}

const std::string& Purchase::Medicine() const 
{ 
    return medicine_; 
}

const CalendarDate& Purchase::Date() const 
{ 
    return date_; 
}

int Purchase::Count() const 
{ 
    return count_; 
}

double Purchase::Sum() const 
{ 
    return sum_; 
}

std::string Purchase::Describe() const
{
    return date_.AsString() + ": " + medicine_ + " x" + std::to_string(count_) + " = " + TextUtils::Money(sum_) + " руб.";
}
