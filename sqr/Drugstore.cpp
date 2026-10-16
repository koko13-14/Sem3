#include "Drugstore.h"
#include "TextUtils.h"

Drugstore::Drugstore(const std::string& name)
    : name_(name)
{
}

const std::string& Drugstore::Name() const { return name_; }

void Drugstore::Add(const Medicine& item)
{
    items_.push_back(item);
}

void Drugstore::Record(const Purchase& purchase)
{
    log_.push_back(purchase);
}

const std::vector<Medicine>& Drugstore::All() const
{
    return items_;
}

std::size_t Drugstore::FindIndexByName(const std::string& name) const
{
    for (std::size_t i = 0; i < items_.size(); ++i)
    {
        if (TextUtils::SameIgnoreCase(items_[i].Title(), name))
        {
            return i;
        }
    }
    return items_.size();
}

Medicine Drugstore::FindByName(const std::string& name) const
{
    const std::size_t i = FindIndexByName(name);
    if (i < items_.size())
    {
        return items_[i];
    }
    return Medicine("", CalendarDate(1970, 1, 1), "", 0.0, "", std::vector<std::string>{}, "", "");
}

int Drugstore::RangeDays(const ReportRange range)
{
    switch (range)
    {
    case ReportRange::Week:  return 7;
    case ReportRange::Month: return 30;
    case ReportRange::Year:  return 365;
    }
    return 0;
}

bool Drugstore::FitsRange(const CalendarDate& saleDate, const CalendarDate& base, const ReportRange range) const
{
    const long ago = saleDate.DaysTo(base);
    return ago >= 0 && ago <= RangeDays(range);
}

std::vector<Purchase> Drugstore::SalesInRange(const std::string& medicine, const ReportRange range, const CalendarDate& base) const
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

int Drugstore::TotalSold(const std::string& medicine, const ReportRange range, const CalendarDate& base) const
{
    int total = 0;
    for (const auto& p : SalesInRange(medicine, range, base))
    {
        total += p.Count();
    }
    return total;
}

double Drugstore::TotalIncome(const std::string& medicine, const ReportRange range, const CalendarDate& base) const
{
    double total = 0.0;
    for (const auto& p : SalesInRange(medicine, range, base))
    {
        total += p.Sum();
    }
    return total;
}

std::vector<Medicine> Drugstore::ForIllness(const std::string& illness) const
{
    std::vector<Medicine> result;
    for (const auto& item : items_)
    {
        if (item.HelpsWith(illness))
        {
            result.push_back(item);
        }
    }
    return result;
}
