#include <stdio.h>
#include <windows.h>
#include <locale.h>

// 从注册表读取CPU信息
void GetCPUInfo_Reg() {
    HKEY hKey;
    char cpuName[256] = {0};
    DWORD len = sizeof(cpuName);
    setlocale(LC_ALL, "chs");

    // 打开CPU信息注册表项
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, 
        "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 
        0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        printf("读取注册表失败\n");
        return;
    }

    // 读取CPU名称
    RegQueryValueExA(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)cpuName, &len);
    printf("===== CPU信息 =====\n");
    printf("CPU名称: %s\n", cpuName);
    RegCloseKey(hKey);
}

// 内存信息（无修改）
void GetMemoryInfo() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    printf("\n===== 内存信息 =====\n");
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys / (1024 * 1024 * 1024);
    printf("总物理内存: %llu GB\n", totalPhysMem);
    DWORDLONG availPhysMem = memInfo.ullAvailPhys / (1024 * 1024 * 1024);
    printf("可用物理内存: %llu GB\n", availPhysMem);
}

int main() {
    GetCPUInfo_Reg();
    GetMemoryInfo();
    system("pause");
    return 0;
}

