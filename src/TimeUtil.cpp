//
// Created by KyuubiRan on 2021/1/25.
//

#include "TimeUtil.h"


unsigned long long GetCurrentSeconds() {
    return time(nullptr);
}

string GetFormatTime() {
    time_t currentMillis = GetCurrentSeconds();
    tm *time = localtime(&currentMillis);
    time->tm_year += 1900;
    time->tm_mon += 1;
    string str;
    str.append(to_string(time->tm_year)).append("-")
            .append(to_string(time->tm_mon)).append("-")
            .append(to_string(time->tm_mday)).append(" ")
            .append(to_string(time->tm_hour)).append(":")
            .append(to_string(time->tm_min)).append(":")
            .append(to_string(time->tm_sec));
    return str;
}