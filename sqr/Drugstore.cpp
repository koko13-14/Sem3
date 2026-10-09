#include "Drugstore.h"
#include "TextUtils.h"

Drugstore::Drugstore(std::string name): name_(std::move(name))
{
}

const std::string& Drugstore::Name() const 
{ 
    return name_; 
}

void Drugstore::Add(std::shared_ptr<Medicine> item)
{
    items_.push_back(std::move(item));
}

void Drugstore::Record(const Purchase& purchase)
{
    log_.push_back(purchase);
}

const std::vector<std::shared_ptr<Medicine>>& Drugstore::All() const
{
    return items_;
}

std::shared_ptr<Medicine> Drugstore::FindByName(const std::string& name) const
{
    for (const auto& item : items_)
    {
        if (TextUtils::SameIgnoreCase(item->Title(), name))
        {
            return item;
        }
    }
    return nullptr;
}

int Drugstore::RangeDays(ReportRange range)
{
    switch (range)
    {
    case ReportRange::Week:  
        return 7;
    case ReportRange::Month: 
        return 30;
    case ReportRange::Year:  
        return 365;
    }
    return 0;
}

bool Drugstore::FitsRange(const CalendarDate& saleDate, const CalendarDate& base, ReportRange range) const
{
    const long ago = saleDate.DaysTo(base);
    return ago >= 0 && ago <= RangeDays(range);
}

std::vector<Purchase> Drugstore::SalesInRange(const std::string& medicine, ReportRange range, const CalendarDate& base) const
{
    std::vector<Purchase> result;

    for (const auto& p : log_)
    {
        if (TextUtils::SameIgnoreCase(p.Medicine(), medicine) &&
            FitsRange(p.Date(), base, range))
        {
            result.push_back(p);
        }
    }

    return result;
}

int Drugstore::TotalSold(const std::string& medicine, ReportRange range, const CalendarDate& base) const
{
    int total = 0;
    for (const auto& p : SalesInRange(medicine, range, base))
    {
        total += p.Count();
    }
    return total;
}

double Drugstore::TotalIncome(const std::string& medicine, ReportRange range, const CalendarDate& base) const
{
    double total = 0.0;
    for (const auto& p : SalesInRange(medicine, range, base))
    {
        total += p.Sum();
    }
    return total;
}

std::vector<std::shared_ptr<Medicine>> Drugstore::ForIllness(const std::string& illness) const
{
    std::vector<std::shared_ptr<Medicine>> result;
    for (const auto& item : items_)
    {
        if (item->HelpsWith(illness))
        {
            result.push_back(item);
        }
    }
    return result;
}
