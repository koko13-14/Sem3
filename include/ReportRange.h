#pragma once

/**
 * @brief Окно отчёта о продажах.
 */
enum class ReportRange
{
    /**
     * @brief Последние 7 дней.
     */
    Week,  

    /**
     * @brief Последние 30 дней.
     */
    Month,  

    /**
     * @brief Последние 365 дней.
     */
    Year
};
