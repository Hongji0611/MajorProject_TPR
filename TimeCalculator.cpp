#include "TimeCalculator.h"

/**
 * Converts date to timestamp
 * Args: user-input year, month, day
 * return: converted timestamp
 */
time_t TimeCalculator::dateToStamp(int year, int month, int day) {
    struct tm  tm;
    time_t rawtime;
    time(&rawtime);
    tm = *localtime(&rawtime);
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    time_t final_tmp = mktime(&tm);
    return final_tmp;
}

/**
 * Calculate week start info / end info
 * Args: user-input year, month, day / Start || end signal
 * return: start/end info based on signal
 */
time_t TimeCalculator::calculateWeek(int year, int month, int day, bool max) {
    struct tm  tm;
    time_t rawtime;
    time(&rawtime);
    tm = *localtime(&rawtime);
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    mktime(&tm); // calculate tm_wday
    if (!max) {
        tm.tm_mday = tm.tm_mday - tm.tm_wday;
    } else {
        tm.tm_mday = tm.tm_mday + (7 - tm.tm_wday);
    }

    time_t final_tmp = mktime(&tm); // This state, tm contains wday;
    return final_tmp;
}

void TimeCalculator::showDate(time_t rawtime) {
    struct tm* dt;
    char buffer[50];
    //time_t rawtime = 0;//std::time(0);
    dt = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y.%m.%d (%a)", dt); // Convert timestamp to date --> in string
    std::cout << std::string(buffer) << std::endl;
    /*for (int i = 0; i < global_iteration; i++) {
        if (array_used[i].getRawTime() == rawtime) {
            cout << "Schedule Exists!" << endl;
        }
    }*/ 
}

void TimeCalculator::printDate(int year, int month, int day, string specifier) {
    if (specifier == "month") {
        // Whatever, Month means day starts from month to day ends - month
        time_t timestmp_raw = dateToStamp(year, month, 1); // Minum
        time_t tmp = dateToStamp(year, month + 1, 1); // Maximum
        while (timestmp_raw < tmp) {
            showDate(timestmp_raw);
            timestmp_raw += DAY_SEC; // one day increment
        }
    } else if (specifier == "day") {
        time_t timestmp_raw = dateToStamp(year, month, day);
        showDate(timestmp_raw);
    } else if (specifier == "week") {
        // Calculate minimum range
        time_t minimum_range = calculateWeek(year, month, day, false);
        time_t maximum_range = calculateWeek(year, month, day, true);
        while (minimum_range < maximum_range) {
            showDate(minimum_range);
            minimum_range += DAY_SEC;
        }
        // Calculate maximum range
        // iterate.
    } else {
    }
}

/**
 * Calculate Date from timestamp
 * Args: (Ref)year, (Ref)month, (Ref)day, (Ref)wday, timestamp
 * Return: No-Op, but reference value should "act" like return.
 */
void TimeCalculator::calculateDateFromStamp(int& year, int& month, int& day, int& wday, time_t ts) {
    struct tm* tmp_struct;
    tmp_struct = localtime(&ts);
    year = tmp_struct->tm_year+1900;
    month = tmp_struct->tm_mon+1;
    day = tmp_struct->tm_mday;
    wday = tmp_struct->tm_wday;
}

/**
 * Round Off Timestamp
 * Since when iterating through timestamp with single-date-timestamp, it could not really accurate.
 * Args: timestamp
 * return: Adjusted(Rounded off) timestamp
 */
time_t TimeCalculator::roundOffTimeStamp(time_t ts) {
    struct tm* tmp_struct;
    tmp_struct = localtime(&ts);
    tmp_struct->tm_hour = 0;
    tmp_struct->tm_min = 0;
    tmp_struct->tm_sec = 0;
    time_t ret = mktime(tmp_struct);
    return ret;
}

/**
 * Check wheter user-input day is actually "existing" date.
 * Args: User - input_ed year/month/day
 * Return: "true" when user enetered world-existing date, "false" when user entered some strange date
 */
bool TimeCalculator::isCorrectDay(int year, int month, int day) {
    // Converted day - will be compared with original y/m/d
    // conv_wday is not-used, but garbage
    int conv_year, conv_month, conv_day, conv_wday;

    // 1. Convert y/m/d to timestamp
    time_t original = dateToStamp(year, month, day);

    // 2. Re-Calc y/m/d again
    calculateDateFromStamp(conv_year, conv_month, conv_day, conv_wday, original);

    // 3. Compare
    if (year > 2037 || year < 1970 || conv_year != year || conv_month != month || conv_day != day) {
        return false;
    } else {
        return true;
    }
}

bool TimeCalculator::calcDayCorrection(int year, int month, int day) {
    // Converted day - will be compared with original y/m/d
// conv_wday is not-used, but garbage
    int conv_year, conv_month, conv_day, conv_wday;

    // 1. Convert y/m/d to timestamp
    time_t original = dateToStamp(year, month, day);

    // 2. Re-Calc y/m/d again
    calculateDateFromStamp(conv_year, conv_month, conv_day, conv_wday, original);

    // 3. Compare
    if (conv_day != day) {
        return false;
    } else {
        return true;
    }
}

