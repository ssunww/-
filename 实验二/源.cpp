#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>

int initial_balance = 10;//z������
HANDLE mutex = CreateMutex(NULL, false, NULL);
typedef struct
{
	char  name[20];//����
	int amount;//Ǯ��
	int is_deposit;//1Ϊ��0Ϊȡ��
}person;

//��ȡ��
DWORD Transaction(LPVOID lpParam) 
{
	person* p = (person*)lpParam;
	while (1)
	{
		WaitForSingleObject(mutex, INFINITE);
		if (p->is_deposit)//���
		{
			initial_balance += p->amount;
			printf("%s��%dԪ�����Ϊ%dԪ��\n", p->name, p->amount, initial_balance);
			ReleaseMutex(mutex);
			break;
		}
		else//ȡ��
		{
			if (initial_balance >= p->amount)
			{
				initial_balance -= p->amount;
				printf("%sȡ%dԪ�����Ϊ%dԪ��\n", p->name, p->amount, initial_balance);
				ReleaseMutex(mutex);
				break;
			}
			else {
				printf("%sȡ%dԪ�����㣬��ȳ�ֵ����ȡ��\n", p->name, p->amount);
				ReleaseMutex(mutex);
				Sleep(10);//�ȴ�ʮ����
			}
		}
	}
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	person* p = (person*)lpParam;
	for (int i = 0; i < 2; i++)
	{
		Transaction(p);
	}
	return 0;
}

void shuffle(person arr[], int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		person temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	if (mutex == NULL)
	{
		printf("%d", GetLastError());
		return 1;
	}
	/*else
	{
		printf("111");
	}*/
	person transactions[7] = { 
		{"dad",10,1},
		{"mam",20,1},
		{"grandma",30,1},
		{"grandpa",40,1} ,
		{"uncle",50,1},
		{"Mary", 50,0}, 
		{ "Sally",100,0} };
	int n = sizeof(transactions) / sizeof(transactions[0]);
	shuffle(transactions,n);
	HANDLE threads[7];//�߳̾��
	int thread_index = 0;
	for (int i = 0; i < n; i++)
	{
		threads[thread_index++] = CreateThread(NULL, 0, ThreadFunc, &transactions[i], 0, NULL);
	}
	WaitForMultipleObjects(thread_index, threads, TRUE, INFINITE);
	for (int i = 0; i < thread_index; i++) {
		CloseHandle(threads[i]);
	}
	CloseHandle(mutex);
	printf("���ʣ�� %d Ԫ��", initial_balance);
	return 0;
}