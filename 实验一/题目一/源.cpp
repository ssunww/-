#include<windows.h>
#include<tchar.h>
#include<stdio.h>
int main()
{
	//ָ�����̴����ǵĴ���״̬
	STARTUPINFO si;
	//���洴�����̵���Ϣ
	PROCESS_INFORMATION pi;
	//�洢�ļ�·��
	char executableName[MAX_PATH];
	//����ת������ļ�·��
	wchar_t wExecutanleName[MAX_PATH];
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	printf("�������ִ���ļ���·����");
	fgets(executableName, MAX_PATH, stdin);
	if (executableName[strlen(executableName) - 1] == '\n')
	{
		executableName[strlen(executableName) - 1] = '\0';
	}

	MultiByteToWideChar(CP_ACP, 0, executableName,-1,wExecutanleName, MAX_PATH);
	if (!CreateProcess(
		NULL,//Ӧ�ó�������
		wExecutanleName,//������
		NULL,//���̰�ȫ����
		NULL,//�̰߳�ȫ����
		FALSE,//�Ƿ�̳о��
		0,//�������̵ı�־
		NULL,//��������
		NULL,//��ǰĿ¼
		&si,//ָ��STARTUPINFO��ָ��
		&pi)) {//ָ��PROCESS_INFORMATION��ָ��
		printf("��������ʧ�ܣ�%d).\n", GetLastError());
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("���гɹ���\n");
	return 0;
}