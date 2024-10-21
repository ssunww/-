#include <stdio.h>
#include <windows.h>

// 定义信号量句柄，用于控制线程的同步
HANDLE sem1, sem2, sem3, sem4;

// 第一个线程的函数，输出 "This"
DWORD WINAPI threadFunc1(LPVOID lpParam) {
    // 等待信号量 sem1，只有当 sem1 被释放时线程才能继续执行
    WaitForSingleObject(sem1, INFINITE);
    printf("This ");

    // 释放信号量 sem2，通知第二个线程可以开始执行
    ReleaseSemaphore(sem2, 1, NULL);
    return 0;
}

// 第二个线程的函数，输出 "is"
DWORD WINAPI threadFunc2(LPVOID lpParam) {
    // 等待信号量 sem2，只有当 sem2 被释放时线程才能继续执行
    WaitForSingleObject(sem2, INFINITE);
    printf("is ");

    // 释放信号量 sem3，通知第三个线程可以开始执行
    ReleaseSemaphore(sem3, 1, NULL);
    return 0;
}

// 第三个线程的函数，输出 "Jinan"
DWORD WINAPI threadFunc3(LPVOID lpParam) {
    // 等待信号量 sem3，只有当 sem3 被释放时线程才能继续执行
    WaitForSingleObject(sem3, INFINITE);
    printf("Jinan ");

    // 释放信号量 sem4，通知第四个线程可以开始执行
    ReleaseSemaphore(sem4, 1, NULL);
    return 0;
}

// 第四个线程的函数，输出 "University!"
DWORD WINAPI threadFunc4(LPVOID lpParam) {
    // 等待信号量 sem4，只有当 sem4 被释放时线程才能继续执行
    WaitForSingleObject(sem4, INFINITE);
    printf("University!\n");
    return 0;
}

int main() {
    // 创建信号量，sem1初始值为1，允许第一个线程立即执行；其他信号量初始值为0
    sem1 = CreateSemaphore(NULL, 1, 1, NULL);  // sem1初始值为1，允许第一个线程立即执行
    sem2 = CreateSemaphore(NULL, 0, 1, NULL);  // sem2初始值为0，等待第一个线程完成
    sem3 = CreateSemaphore(NULL, 0, 1, NULL);  // sem3初始值为0，等待第二个线程完成
    sem4 = CreateSemaphore(NULL, 0, 1, NULL);  // sem4初始值为0，等待第三个线程完成

    // 创建四个线程，每个线程对应一个输出函数
    HANDLE hThread1 = CreateThread(NULL, 0, threadFunc1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, threadFunc2, NULL, 0, NULL);
    HANDLE hThread3 = CreateThread(NULL, 0, threadFunc3, NULL, 0, NULL);
    HANDLE hThread4 = CreateThread(NULL, 0, threadFunc4, NULL, 0, NULL);

    // 等待所有线程完成执行
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);
    WaitForSingleObject(hThread4, INFINITE);

    // 关闭线程句柄，释放资源
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hThread3);
    CloseHandle(hThread4);

    // 关闭信号量句柄，释放信号量资源
    CloseHandle(sem1);
    CloseHandle(sem2);
    CloseHandle(sem3);
    CloseHandle(sem4);

    return 0;
}