//
// Created by KyuubiRan on 2021/1/25.
//

#include "TimeUtil.h"


unsigned long long GetCurrentSeconds() {
    return time(nullptr);
}

string GetFormatTime() {
    time_t currentSec = GetCurrentSeconds();
    tm *time = localtime(&currentSec);
    time->tm_year += 1900;
    time->tm_mon += 1;
    char tmp[64];
    sprintf(tmp, "%04d-%02d-%02d %02d:%02d:%02d", time->tm_year, time->tm_mon, time->tm_mday,
            time->tm_hour, time->tm_min, time->tm_sec);
    return string(tmp);
}