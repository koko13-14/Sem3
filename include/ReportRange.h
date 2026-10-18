#pragma once

/**
 * @brief Окно отчёта о продажах.
 */
enum class ReportRange
{
    Week,   ///< Последние 7 дней.
    Month,  ///< Последние 30 дней.
    Year    ///< Последние 365 дней.
};
