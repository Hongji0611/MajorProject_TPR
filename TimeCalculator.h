#pragma once
#include <iostream>
#include <ctime>
#pragma warning(disable:4996)

#define MAX_ARR_CTR 36500 // Approx. 100 years from 1970
#define DAY_SEC 86400

using namespace std;

class TimeCalculator {
public:
    // Human readable date to raw timestamp
    time_t dateToStamp(int year, int month, int day);

    // Calculate Week
    time_t calculateWeek(int year, int month, int day, bool max = false);

    // Calculate and return(modify) year, month, day, wday information based on timestamp
    void calculateDateFromStamp(int& year, int& month, int& day, int& wday, time_t ts);

    time_t roundOffTimeStamp(time_t ts);

    // whaaatever
    bool isCorrectDay(int year, int month, int day);
};