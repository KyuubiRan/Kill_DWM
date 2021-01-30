//
// Created by KyuubiRan on 2021/1/20.
//

#ifndef FUCK_DWM_EXE_PROCUTILS_H
#define FUCK_DWM_EXE_PROCUTILS_H

#include "Common.h"

/**
 * 提权
 * @return 是否成功
 */
bool UpPrivilege();

/**
 * 查找进程的函数
 * @param procName 需要查找的进程名称
 * @param dwPid 若查找成功 获取进程的id
 * @return 是否找到指定进程
 */
bool FindProcess(const string &procName, DWORD &dwPid);

/**
 * 根据进程id杀死进程
 * @param dwPid 目标进程id
 * @param exitCode 退出代码
 * @return 是否成功
 */
bool KillProcess(DWORD dwPid, int exitCode = 0);

/**
 * 根据进程名称杀死进程
 * @param procName 进程名称
 * @param exitCode 退出代码
 * @return 是否成功
 */
bool KillProcess(const string &procName, int exitCode = 0);

/**
 * 获取内存占用
 * @param dwPid 目标进程id
 * @return 内存占用(Byte)
 */
UINT64 GetMemSize(DWORD dwPid);

/**
 * 获取内存占用
 * @param procName 目标进程名称
 * @return 内存占用(Byte)
 */
UINT64 GetMemSize(const string &procName);

/**
 * 获取内存占用
 * @param dwPid 目标进程id
 * @return 内存占用(Mb)
 */
double GetMemSizeByMb(DWORD dwPid);

/**
 * 获取内存占用
 * @param procName 目标进程名称
 * @return 内存占用(Mb)
 */
double GetMemSizeByMb(const string &procName);

#endif //FUCK_DWM_EXE_PROCUTILS_H
