//
// Created by KyuubiRan on 2021/1/25.
//

#ifndef FUCKDWM_TIMEUTIL_H
#define FUCKDWM_TIMEUTIL_H

#include <ctime>
#include <string>

using std::string;
using std::to_string;

unsigned long long GetCurrentSeconds();

/**
 * 获取格式化后的时间
 * @return yyyy-MM-dd HH:mm:ss
 */
string GetFormatTime();

#endif //FUCKDWM_TIMEUTIL_H
