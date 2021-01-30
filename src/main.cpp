#include "ProcUtils.h"
#include "TimeUtil.h"

#define MEM_2G_B 2147483648L
#define MEM_2G_MB 2048.0
#define MIN_MILLI_SEC 60000

int main() {
    UpPrivilege();
    DWORD pid = 0;
    int count = 0;
    while (FindProcess("dwm.exe", pid)) {
        count++;
        if (GetMemSizeByMb(pid) > MEM_2G_MB) {
            cout << "Target proc used mem > 2G,it will be terminated at 5sec.\n";
            Sleep(5000);
            KillProcess(pid);
        }
        cout << "Time:" << GetFormatTime() << "\n";
        cout << "-----" << "COUNT:" << count << "-----\n";
        Sleep(10 * MIN_MILLI_SEC);
    }
    cout << "Target proc not found.Task finished.\n";
    system("pause");
    return 0;
}
