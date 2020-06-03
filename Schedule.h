#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <string>

#pragma warning(disable:4996)
using namespace std;

class Schedule {

private:
    unsigned long long sid;
    string content;
    string keyword;
    vector<time_t> tmp;

public:
    // ���� timestamp, ���� timestamp, duration(�ݺ�)
    // void setRepeat(time_t start_timestamp, time_t limit_timestamp, time_t duration); // ����
    //Schedule();
    Schedule(string con, string key, unsigned long long sid);
    ~Schedule();
    void add(time_t t);
    string getKeyword();
    string getContent();
    void setKeyword(string& s);
    void setContent(string& s);
    bool isDayExists(time_t ts); // returns true if day exists, returns false if not exists.
    void setRepeat(time_t start_timestamp, time_t limit_timestamp, int specifier, int duration); // Set Repeat
    unsigned long long getSid();
    void setSid(unsigned long long val);
    string getAllInfo();
};

