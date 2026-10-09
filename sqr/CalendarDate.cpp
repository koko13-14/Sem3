#include "CalendarDate.h"

#include <cstdlib>
#include <stdexcept>

namespace
{
    bool IsLeap(int y)
    {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int LastDayOfMonth(int year, int month)
    {
        static const int table[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && IsLeap(year))
        {
            return 29;
        }
        return table[month - 1];
    }

    // Алгоритм Говарда Хиннанта: перевод гражданской даты в дни от 1970-01-01.
    long CivilToSerial(int y, unsigned m, unsigned d)
    {
        y -= (m <= 2);
        const long era = (y >= 0 ? y : y - 399) / 400;
        const unsigned yoe = static_cast<unsigned>(y - era * 400);
        const unsigned doy = (153u * (m > 2 ? m - 3u : m + 9u) + 2u) / 5u + d - 1u;
        const unsigned doe = yoe * 365u + yoe / 4u - yoe / 100u + doy;
        return era * 146097L + static_cast<long>(doe) - 719468L;
    }
}

void CalendarDate::EnsureValid(int year, int month, int day)
{
    if (month < 1 || month > 12)
    {
        throw std::invalid_argument("CalendarDate: месяц вне диапазона 1..12");
    }
    if (day < 1 || day > LastDayOfMonth(year, month))
    {
        throw std::invalid_argument("CalendarDate: день не существует в этом месяце");
    }
}

CalendarDate::CalendarDate(int year, int month, int day): year_(year), month_(month), day_(day)
{
    EnsureValid(year_, month_, day_);
}

CalendarDate CalendarDate::FromString(const std::string& text)
{
    if (text.size() != 10 || text[4] != '-' || text[7] != '-')
    {
        throw std::invalid_argument("CalendarDate::FromString: нужен формат ГГГГ-ММ-ДД");
    }

    for (std::size_t i = 0; i < text.size(); ++i)
    {
        if (i == 4 || i == 7) continue;
        if (text[i] < '0' || text[i] > '9')
        {
            throw std::invalid_argument("CalendarDate::FromString: нужен формат ГГГГ-ММ-ДД");
        }
    }

    const int y = std::atoi(text.substr(0, 4).c_str());
    const int m = std::atoi(text.substr(5, 2).c_str());
    const int d = std::atoi(text.substr(8, 2).c_str());

    return CalendarDate(y, m, d);
}

int CalendarDate::Year() const 
{ 
    return year_; 
}

int CalendarDate::Month() const
{ 
    return month_; 
}

int CalendarDate::Day() const 
{
    return day_;
}

std::string CalendarDate::AsString() const
{
    auto two = [](int v) {
        std::string s = std::to_string(v);
        if (s.size() < 2) s = "0" + s;
        return s;
        };

    return std::to_string(year_) + "-" + two(month_) + "-" + two(day_);
}

long CalendarDate::Serial() const
{
    return CivilToSerial(year_, static_cast<unsigned>(month_), static_cast<unsigned>(day_));
}

long CalendarDate::DaysTo(const CalendarDate& other) const
{
    return other.Serial() - Serial();
}

bool CalendarDate::operator==(const CalendarDate& other) const
{
    return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
}

bool CalendarDate::operator!=(const CalendarDate& other) const
{
    return !(*this == other); 
}

bool CalendarDate::operator< (const CalendarDate& other) const 
{ 
    return Serial() < other.Serial(); 
}

bool CalendarDate::operator<=(const CalendarDate& other) const 
{ 
    return Serial() <= other.Serial(); 
}

bool CalendarDate::operator> (const CalendarDate& other) const 
{ 
    return Serial() > other.Serial(); 
}

bool CalendarDate::operator>=(const CalendarDate& other) const 
{ 
    return Serial() >= other.Serial(); 
}
