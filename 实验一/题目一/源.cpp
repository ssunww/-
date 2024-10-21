#include<windows.h>
#include<tchar.h>
#include<stdio.h>
int main()
{
	//指定进程创建是的窗口状态
	STARTUPINFO si;
	//储存创建进程的信息
	PROCESS_INFORMATION pi;
	//存储文件路径
	char executableName[MAX_PATH];
	//储存转换后的文件路径
	wchar_t wExecutanleName[MAX_PATH];
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	printf("请输入可执行文件的路径：");
	fgets(executableName, MAX_PATH, stdin);
	if (executableName[strlen(executableName) - 1] == '\n')
	{
		executableName[strlen(executableName) - 1] = '\0';
	}

	MultiByteToWideChar(CP_ACP, 0, executableName,-1,wExecutanleName, MAX_PATH);
	if (!CreateProcess(
		NULL,//应用程序名称
		wExecutanleName,//命令行
		NULL,//进程安全属性
		NULL,//线程安全属性
		FALSE,//是否继承句柄
		0,//创建进程的标志
		NULL,//环境变量
		NULL,//当前目录
		&si,//指向STARTUPINFO的指针
		&pi)) {//指向PROCESS_INFORMATION的指针
		printf("创建进程失败（%d).\n", GetLastError());
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("运行成功。\n");
	return 0;
}