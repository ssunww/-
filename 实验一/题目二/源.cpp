#include <stdio.h>
#include <windows.h>

// �����ź�����������ڿ����̵߳�ͬ��
HANDLE sem1, sem2, sem3, sem4;

// ��һ���̵߳ĺ�������� "This"
DWORD WINAPI threadFunc1(LPVOID lpParam) {
    // �ȴ��ź��� sem1��ֻ�е� sem1 ���ͷ�ʱ�̲߳��ܼ���ִ��
    WaitForSingleObject(sem1, INFINITE);
    printf("This ");

    // �ͷ��ź��� sem2��֪ͨ�ڶ����߳̿��Կ�ʼִ��
    ReleaseSemaphore(sem2, 1, NULL);
    return 0;
}

// �ڶ����̵߳ĺ�������� "is"
DWORD WINAPI threadFunc2(LPVOID lpParam) {
    // �ȴ��ź��� sem2��ֻ�е� sem2 ���ͷ�ʱ�̲߳��ܼ���ִ��
    WaitForSingleObject(sem2, INFINITE);
    printf("is ");

    // �ͷ��ź��� sem3��֪ͨ�������߳̿��Կ�ʼִ��
    ReleaseSemaphore(sem3, 1, NULL);
    return 0;
}

// �������̵߳ĺ�������� "Jinan"
DWORD WINAPI threadFunc3(LPVOID lpParam) {
    // �ȴ��ź��� sem3��ֻ�е� sem3 ���ͷ�ʱ�̲߳��ܼ���ִ��
    WaitForSingleObject(sem3, INFINITE);
    printf("Jinan ");

    // �ͷ��ź��� sem4��֪ͨ���ĸ��߳̿��Կ�ʼִ��
    ReleaseSemaphore(sem4, 1, NULL);
    return 0;
}

// ���ĸ��̵߳ĺ�������� "University!"
DWORD WINAPI threadFunc4(LPVOID lpParam) {
    // �ȴ��ź��� sem4��ֻ�е� sem4 ���ͷ�ʱ�̲߳��ܼ���ִ��
    WaitForSingleObject(sem4, INFINITE);
    printf("University!\n");
    return 0;
}

int main() {
    // �����ź�����sem1��ʼֵΪ1�������һ���߳�����ִ�У������ź�����ʼֵΪ0
    sem1 = CreateSemaphore(NULL, 1, 1, NULL);  // sem1��ʼֵΪ1�������һ���߳�����ִ��
    sem2 = CreateSemaphore(NULL, 0, 1, NULL);  // sem2��ʼֵΪ0���ȴ���һ���߳����
    sem3 = CreateSemaphore(NULL, 0, 1, NULL);  // sem3��ʼֵΪ0���ȴ��ڶ����߳����
    sem4 = CreateSemaphore(NULL, 0, 1, NULL);  // sem4��ʼֵΪ0���ȴ��������߳����

    // �����ĸ��̣߳�ÿ���̶߳�Ӧһ���������
    HANDLE hThread1 = CreateThread(NULL, 0, threadFunc1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, threadFunc2, NULL, 0, NULL);
    HANDLE hThread3 = CreateThread(NULL, 0, threadFunc3, NULL, 0, NULL);
    HANDLE hThread4 = CreateThread(NULL, 0, threadFunc4, NULL, 0, NULL);

    // �ȴ������߳����ִ��
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);
    WaitForSingleObject(hThread4, INFINITE);

    // �ر��߳̾�����ͷ���Դ
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hThread3);
    CloseHandle(hThread4);

    // �ر��ź���������ͷ��ź�����Դ
    CloseHandle(sem1);
    CloseHandle(sem2);
    CloseHandle(sem3);
    CloseHandle(sem4);

    return 0;
}