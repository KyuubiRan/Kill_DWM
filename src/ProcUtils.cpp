//
// Created by KyuubiRan on 2021/1/20.
//

#include "ProcUtils.h"

bool UpPrivilege() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tps;
    LUID luid;
    bool result;

    //获取token句柄
    result = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
    if (!result) {
        cout << "Open proc token failed.\n";
        return false;
    }

    //查看权限
    result = LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid);
    if (!result) {
        cout << "Lookup privilege value failed.\n";
        CloseHandle(hToken);
        return false;
    }

    tps.Privileges[0].Luid = luid;
    tps.PrivilegeCount = 1;
    tps.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    //提权
    result = AdjustTokenPrivileges(hToken, FALSE, &tps, sizeof tps, nullptr, nullptr);
    if (result) {
        cout << "Adjust token success.\n";
    } else {
        cout << "Adjust token failed.\n";
    }
    CloseHandle(hToken);
    return result;
}

bool FindProcess(const string &procName, DWORD &dwPid) {
    cout << "Start find proc.\n";
    TCHAR tszProcess[64] = {0};
    lstrcpy(tszProcess, _T(procName.c_str()));

    STARTUPINFO st;
    PROCESS_INFORMATION pi;
    PROCESSENTRY32 ps;
    HANDLE hSnapshot;

    memset(&st, 0, sizeof st);
    st.cb = sizeof st;
    memset(&ps, 0, sizeof ps);
    ps.dwSize = sizeof ps;
    memset(&pi, 0, sizeof pi);

    //创建快照
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return false;
    if (!Process32First(hSnapshot, &ps)) return false;
    //查找进程
    do {
        if (lstrcmp(ps.szExeFile, tszProcess) == 0) {
            dwPid = ps.th32ProcessID;
            CloseHandle(hSnapshot);
            cout << "Found proc: " << tszProcess << "\nPid = " << dwPid << "\n";
            return true;
        }
    } while (Process32Next(hSnapshot, &ps));

    cout << "Proc not found.\n";
    //未找到 关闭快照并返回false
    CloseHandle(hSnapshot);
    return false;
}

bool KillProcess(DWORD dwPid, int exitCode) {
    //打开进程
    HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
    //如果获取的进程为空
    if (proc == nullptr) return false;
    //结束进程
    TerminateProcess(proc, exitCode);
    cout << "Pid = " << dwPid << " has been terminated.\n";
    return true;
}

bool KillProcess(const string &procName, int exitCode) {
    DWORD dwPid = 0;
    //查找进程并且获取pid 然后根据pid杀死进程
    if (FindProcess(procName, dwPid)) return KillProcess(dwPid, exitCode);
    //执行失败
    return false;
}

UINT64 GetMemSize(DWORD dwPid) {
    PROCESS_MEMORY_COUNTERS pmc;
    UINT64 mem = 0;
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwPid);
    if (hProc == nullptr) {
        cout << "Get proc mem failed. Err=" << GetLastError() << "\n";
        return 0;
    }
    if (GetProcessMemoryInfo(hProc, &pmc, sizeof pmc)) {
        mem = pmc.WorkingSetSize;
        cout << "Memory = " << mem << " B\n";
    }
    return mem;
}

UINT64 GetMemSize(const string &procName) {
    DWORD dwPid = 0;
    if (FindProcess(procName, dwPid)) return GetMemSize(dwPid);
    return 0;
}

double GetMemSizeByMb(const string &procName) {
    double size = GetMemSize(procName) / 1024.0 / 1024.0;
    cout << "Memory = " << size << " MB\n";
    return size;
}

double GetMemSizeByMb(DWORD dwPid) {
    double size = GetMemSize(dwPid) / 1024.0 / 1024.0;
    cout << "Memory = " << size << " MB\n";
    return size;
}