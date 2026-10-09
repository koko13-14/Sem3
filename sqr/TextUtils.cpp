#include "TextUtils.h"

#include <cctype>
#include <cmath>
#include <utility>

namespace
{
    const std::pair<const char*, const char*> kCyrPairs[] =
    {
        {"А","а"},{"Б","б"},{"В","в"},{"Г","г"},{"Д","д"},
        {"Е","е"},{"Ж","ж"},{"З","з"},{"И","и"},{"Й","й"},
        {"К","к"},{"Л","л"},{"М","м"},{"Н","н"},{"О","о"},
        {"П","п"},{"Р","р"},{"С","с"},{"Т","т"},{"У","у"},
        {"Ф","ф"},{"Х","х"},{"Ц","ц"},{"Ч","ч"},{"Ш","ш"},
        {"Щ","щ"},{"Ъ","ъ"},{"Ы","ы"},{"Ь","ь"},{"Э","э"},
        {"Ю","ю"},{"Я","я"},{"Ё","ё"}
    };

    // Возвращает указатель на пару (верхняя, нижняя) для позиции pos,
    // либо nullptr, если в pos верхней русской буквы нет.
    const std::pair<const char*, const char*>* FindCyrPair(const std::string& s, std::size_t pos)
    {
        for (const auto& p : kCyrPairs)
        {
            const std::string upper = p.first;
            if (s.compare(pos, upper.size(), upper) == 0)
            {
                return &p;
            }
        }
        return nullptr;
    }

    std::string ToLowerCopy(const std::string& s)
    {
        std::string out;
        out.reserve(s.size());

        std::size_t i = 0;
        while (i < s.size())
        {
            const unsigned char ch = static_cast<unsigned char>(s[i]);

            if (ch < 0x80)
            {
                out += static_cast<char>(std::tolower(ch));
                ++i;
                continue;
            }

            if (const auto* pair = FindCyrPair(s, i))
            {
                out += pair->second;
                i += std::string(pair->first).size();
                continue;
            }

            out += static_cast<char>(ch);
            ++i;
        }

        return out;
    }
}

namespace TextUtils
{
    std::string Number(double value)
    {
        const bool negative = value < 0.0;
        const double absValue = negative ? -value : value;
        const long long hundredths = static_cast<long long>(std::floor(absValue * 100.0 + 0.5));
        const long long whole = hundredths / 100;
        const long long frac = hundredths % 100;

        const std::string sign = (negative && hundredths != 0) ? "-" : "";
        const std::string fracPart = (frac < 10 ? "0" : "") + std::to_string(frac);

        return sign + std::to_string(whole) + "." + fracPart;
    }

    std::string Money(double value)
    {
        return Number(value);
    }

    bool SameIgnoreCase(const std::string& a, const std::string& b)
    {
        return ToLowerCopy(a) == ToLowerCopy(b);
    }
}
