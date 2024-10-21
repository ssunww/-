#include <stdio.h>
#include<Windows.h>

// 定义信号量句柄
HANDLE sem1, sem2, sem3, sem4;
int n;
//定义第一个线程函数
DWORD WINAPI threadFunc1(LPVOID lpParam)
{
	for (int i = 0; i < n; i++) {
		WaitForSingleObject(sem1, INFINITE);
		printf("This ");
		ReleaseSemaphore(sem2, 1, NULL);
	}
	return 0;
}

//定义第二个线程函数
DWORD WINAPI threadFunc2(LPVOID lpParam)
{
	for (int i = 0; i < n; i++)
	{
		WaitForSingleObject(sem2, INFINITE);
		printf("is ");
		ReleaseSemaphore(sem3, 1, NULL);
	}
	return 0;
}

//定义第三个线程函数
DWORD WINAPI threadFunc3(LPVOID lpParam)
{
	for (int i = 0; i < n; i++)
	{
		WaitForSingleObject(sem3, INFINITE);
		printf("jinan ");
		ReleaseSemaphore(sem4, 1, NULL);
	}
	return 0;
}

//定义第四个线程函数
DWORD WINAPI threadFunc4(LPVOID lpParam)
{
	for (int i = 0; i < n; i++)
	{
		WaitForSingleObject(sem4, INFINITE);
		printf("University!\n");
		ReleaseSemaphore(sem1, 1, NULL);
	}
	return 0;
}

int main()
{
	printf("请输入要输出的次数：");
	if (scanf_s("%d", &n) != 1||n<0)
	{
		printf("请输入正整数！\n");
	}
	sem1 = CreateSemaphore(NULL, 1, 1, NULL);
	sem2 = CreateSemaphore(NULL, 0, 1, NULL);
	sem3 = CreateSemaphore(NULL, 0, 1, NULL);
	sem4 = CreateSemaphore(NULL, 0, 1, NULL);
	HANDLE hThread1 = CreateThread(NULL, 0, threadFunc1, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, threadFunc2, NULL, 0, NULL);
	HANDLE hThread3 = CreateThread(NULL, 0, threadFunc3, NULL, 0, NULL);
	HANDLE hThread4 = CreateThread(NULL, 0, threadFunc4, NULL, 0, NULL);
	//if(hThread1!=0&& hThread2!=0&& hThread3!=0&& hThread4!=0)
	//{
		WaitForSingleObject(hThread1, INFINITE);
		WaitForSingleObject(hThread2, INFINITE);
		WaitForSingleObject(hThread3, INFINITE);
		WaitForSingleObject(hThread4, INFINITE);
		CloseHandle(hThread1);
		CloseHandle(hThread2);
		CloseHandle(hThread3);
		CloseHandle(hThread4);
	//}
	CloseHandle(sem1);
	CloseHandle(sem2);
	CloseHandle(sem3);
	CloseHandle(sem4);
	return 0;
}