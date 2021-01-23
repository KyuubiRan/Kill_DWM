#include "ProcUtils.h"

#define MEM_2G 2147483648L
#define MIN_MILLI_SEC 60000

int main() {
    UpPrivilege();
    DWORD pid = 0;
    int count = 0;
    while (FindProcess("dwm.exe", pid)) {
        count++;
        if (GetMemSize(pid) > MEM_2G) {
            cout << "Target proc used mem > 2G,it will be terminated at 5sec.\n";
            Sleep(5000);
            KillProcess(pid);
        }
        cout << "-----" << "COUNT:" << count << "-----\n";
        Sleep(10 * MIN_MILLI_SEC);
    }
    cout << "Target proc not found.Task finished.\n";
    system("pause");
    return 0;
}
