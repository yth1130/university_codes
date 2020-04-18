#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define Tbl_Size 36000
#define Max_Size 100

int HeadFW = 0;
int HeadBW = Tbl_Size - 1;

typedef struct str_ty_record {
	char name[100];
	int monincome;
	int link;
	int flink;
	int blink;
} type_record;

typedef void* (FINDINDEX)(type_record* record, int tempHA, char* temp);

float checkTime(LARGE_INTEGER StartTime, LARGE_INTEGER TicksPerSec);
void makeEmptyChain(type_record* record);
void insertName(type_record* record, FILE* fp_r, FINDINDEX findIndexFunc);
void findIndex(type_record* record, int tempHA, char* temp);
void findIndexFast(type_record* record, int tempHA, char* temp);
int hash(char recname[]);
int searchName(type_record* record, char recname[], int* probe);
int deleteName(type_record* record, char recname[]);
float perfomanceCheck(type_record* record);
void totalDelete(type_record* record);
void totalSearch(type_record* record);

int main() {
	char temp[Max_Size];
	int loc, probe, reloc;
	char i;

	float playTime;
	LARGE_INTEGER TicksPerSec;
	LARGE_INTEGER StartTime;
	QueryPerformanceFrequency(&TicksPerSec);

	FILE* fp_r;
	fp_r = fopen("uns.txt", "r");
	if (!fp_r) {
		printf("File open error\n");
		return 0;
	}
	type_record* record = (type_record*)malloc(sizeof(type_record)*Tbl_Size);
	makeEmptyChain(record);	//�ؽ� ���̺� record�� ��� �ּҸ� ����� ���ڸ� ü�ο� �ִ´�.

	QueryPerformanceCounter(&StartTime);
	insertName(record, fp_r, findIndex);
	playTime = checkTime(StartTime, TicksPerSec);
	printf("�ܼ��� ���ڸ� ã���� �ð� : %f \n", playTime);

	free(record);
	
	fp_r = fopen("uns.txt", "r");
	if (!fp_r) {
		printf("File open error\n");
		return 0;
	}
	record = (type_record*)malloc(sizeof(type_record)*Tbl_Size);
	makeEmptyChain(record);	//�ؽ� ���̺� record�� ��� �ּҸ� ����� ���ڸ� ü�ο� �ִ´�.

	QueryPerformanceCounter(&StartTime);
	insertName(record, fp_r, findIndexFast);
	playTime = checkTime(StartTime, TicksPerSec);
	printf("����� ���ڸ� ã���� �ð� : %f \n", playTime);



	printf("��ɵ�:  r(�˻�), d(����), p(��������), t(�ϰ�����), v(��üŽ��), e(����).\n");
	while (1) {
		printf("\n�����? ");
		scanf("%c", &i);
		getchar();

		switch (i) {
		case 'r':
			scanf(" %s", temp);
			getchar();
			loc = searchName(record, temp, &probe);
			if (loc != -1) printf("	������ġ = %d, Probe �� = %d\n", loc, probe);
			else printf("	�׷� ����Ÿ�� �������� �ʽ��ϴ�.\n");
			break;
		case 'd':
			scanf(" %s", temp);
			getchar();
			reloc = deleteName(record, temp, &loc);
			if (reloc != -1) printf("	������ġ = %d, Relocation �� = %d\n", loc, reloc);
			else printf("	�׷� ����Ÿ�� �������� �ʽ��ϴ�.\n");
			break;
		case 'p':
			QueryPerformanceCounter(&StartTime);
			perfomanceCheck(record);
			playTime = checkTime(StartTime, TicksPerSec);
			printf("	�������� �ð� : %f \n", playTime);
			break;
		case 't':
			QueryPerformanceCounter(&StartTime);
			totalDelete(record);
			playTime = checkTime(StartTime, TicksPerSec);
			printf("	�������� �ð� : %f \n", playTime);
			break;
		case 'v':
			QueryPerformanceCounter(&StartTime);
			totalSearch(record);
			playTime = checkTime(StartTime, TicksPerSec);
			printf("	�������� �ð� : %f \n", playTime);
			break;
		case 'e':
			printf("	������ �����մϴ�.\n");
			return 0;
		}
	}
	
	free(record);
	return 0;
}

float checkTime(LARGE_INTEGER StartTime, LARGE_INTEGER TicksPerSec) {
	LARGE_INTEGER EndTime;
	LONGLONG CurTime;
	float playTime;
	QueryPerformanceCounter(&EndTime);
	CurTime = EndTime.QuadPart - StartTime.QuadPart;
	playTime = (float)CurTime / (float)TicksPerSec.QuadPart;
	return playTime;
}

void makeEmptyChain(type_record* record) {
	int i;
	for (i = 0; i < Tbl_Size; i++) {
		strcpy(record[i].name, "\0");
		record[i].link = -1;
		if (i == 0) {
			record[i].flink = i + 1;
			record[i].blink = -1;
		}
		else if (i == Tbl_Size - 1) {
			record[i].flink = -1;
			record[i].blink = i - 1;
		}
		else {
			record[i].flink = i + 1;
			record[i].blink = i - 1;

		}
	}
}

void insertName(type_record* record, FILE* fp_r, FINDINDEX findIndexFunc) {
	char temp[Max_Size];
	int tempHA, x = 0;
	while (1) {	//�����۾�
		fgets(temp, Max_Size, fp_r);
		if (strlen(temp) == 0)	//������ �� Ȯ��
			break;
		while (1) {	//������ �Է¹޾��� �� ������� '\n'�� ���ش�.
			if (temp[x] == '\0')
				break;
			if (temp[x] == '\n') {
				temp[x] = '\0';
				x = 0;
				break;
			}
			x++;
		}
		tempHA = hash(temp);
		findIndexFunc(record, tempHA, temp);
		temp[0] = '\0';
	}
}

void findIndex(type_record* record, int tempHA, char* temp) {	/////////////////////////////flink, blink����ϱ�
	int i = tempHA;
	int x;
	if (strcmp(record[tempHA].name, "\0") == 0) {	//����ü �迭�� tempHA�ε����� �̸��ΰ� ��������� �׳� �ִ´�.
		strcpy(record[tempHA].name, temp);

	}
	else {
		while (record[i].link != -1) {	//�̸��� �������� ��ũ�� ������� ������ ��ũ�� Ÿ�� �̵��Ѵ�.
			x = i;
			i = record[i].link;
		}
		if (strcmp(record[i].name, "\0") == 0) {	//�̸��� ��������� �ְ�
			strcpy(record[i].name, temp);
			record[x].link = i;
		}
		else {	/////////�ƴϸ� ���ڸ� ü�� �̿�
			x = i;
			i = 0;
			while (strcmp(record[i].name, "\0") != 0) {	//ü���� ó������
				i++;
			}
			strcpy(record[i].name, temp);
			record[x].link = i;

		}
	}
}

void findIndexFast(type_record* record, int tempHA, char* temp) {
	int i = tempHA, nextIndex, prevIndex;
	int x;
	if (strcmp(record[i].name, "\0") == 0) {	//����ü �迭�� tempHA�ε����� �̸��ΰ� ��������� �׳� �ִ´�.
		strcpy(record[i].name, temp);
	}
	else {
		while (record[i].link != -1) {	//�̸��� �������� ��ũ�� ������� ������ ��ũ�� Ÿ�� �̵��Ѵ�.
			x = i;
			i = record[i].link;
		}
		if (strcmp(record[i].name, "\0") == 0) {	//�̸��� ��������� �ְ�
			strcpy(record[i].name, temp);
			record[x].link = i;
		}
		else {	/////////�ƴϸ� ���ڸ� ü�� �̿�
			x = i;
			i = HeadFW;

			while (strcmp(record[i].name, "\0") != 0) {
				i = record[i].flink;
			}
			strcpy(record[i].name, temp);
			record[x].link = i;
		}
	}
	if (record[i].blink == -1) HeadFW = i;
	nextIndex = record[i].flink;
	prevIndex = record[i].blink;
	if(prevIndex != -1) record[prevIndex].flink = nextIndex;
	record[nextIndex].blink = prevIndex;
}

void insertNameTop(type_record* record, int tempHA, char* temp) {

}
void insertNameMid(type_record* record, int tempHA, char* temp) {

}
void insertNameBot(type_record* record, int tempHA, char* temp) {

}

void updateChain(type_record* record, int temp) {

}

int hash(char recname[]) {
	unsigned char u; int HA, j, leng, halfleng;
	long sum = 0;
	int A[100];
	// name �� ���� j �� ���Ͽ� ������ �����Ѵ�:
	leng = strlen(recname);
	for (j = 0; j < leng; j++) {
		u = recname[j];
		A[j] = u;
	}
	halfleng = leng / 2;
	for (j = 0; j < halfleng; j++)
		sum = sum + (A[j] * A[leng - 1 - j] * A[(leng - 1) / 2]);
	if (leng % 2 == 1)
		sum = sum + A[halfleng] * A[halfleng + 1] * A[(leng - 1) / 2];
	HA = sum % Tbl_Size;  // HA is a home address given by the hash function.
	return HA;

}

int searchName(type_record* record, char recname[], int* probe) {
	int loc = hash(recname);
	*probe = 1;
	while (strcmp(record[loc].name, recname) != 0) {	//���̺��� ã�� �̸��� �˻�
		loc = record[loc].link;	//��ũ�� ��� ���󰣴�.
		if (loc == -1)	//��ã�� �ε����� -1�� ��
			break;
		(*probe)++;	//Probe�� ����
	}
	return loc;
}

int deleteName(type_record* record, char recname[], int* loc) {	//relocation�� ��ȯ
	int probe;
	*loc = searchName(record, recname, &probe);	//������� �̸��� HA���� ��´�
	int curloc, nextloc, i=0;

	if (*loc != -1) {
		strcpy(record[*loc].name, "\0");
		curloc = *loc;
		while (record[curloc].link != -1) {
			nextloc = record[curloc].link;
			strcpy(record[curloc].name, record[nextloc].name);
			strcpy(record[nextloc].name, "\0");
			curloc = nextloc;
			i++;
		}
		return i;
	}
	else return -1;

}

float perfomanceCheck(type_record* record) {
	char temp[Max_Size];
	int tempHA, x = 0, probe = 1, totalProbe = 0, num=0;
	float averageProbe;
	FILE* fp_r;
	fp_r = fopen("uns.txt", "r");
	if (!fp_r) {
		printf("File open error\n");
		return 0;
	}
	while (1) {
		fgets(temp, Max_Size, fp_r);
		if (strlen(temp) == 0)	//������ �� Ȯ��
			break;
		while (1) {	//������ �Է¹޾��� �� ������� '\n'�� ���ش�.
			if (temp[x] == '\0')
				break;
			if (temp[x] == '\n') {
				temp[x] = '\0';
				x = 0;
				break;
			}
			x++;
		}
		searchName(record, temp, &probe);
		totalProbe += probe;
		num++;
		temp[0] = '\0';
	}
	averageProbe = (float)totalProbe/(float)num;
	printf("	Average probe number = %.2f\n", averageProbe);
}

void totalDelete(type_record* record) { ///////////////////????????????????????????????????????????
	char temp[Max_Size];
	int x = 0, loc, reloc, totalReloc = 0, i;
	FILE* fp_r;
	fp_r = fopen("uns.txt", "r");
	if (!fp_r) {
		printf("File open error\n");
		return 0;
	}
	for (i = 0; i < 30000; i++) {
		fgets(temp, Max_Size, fp_r);
		if (strlen(temp) == 0)	//������ �� Ȯ��
			break;
		while (1) {	//������ �Է¹޾��� �� ������� '\n'�� ���ش�.
			if (temp[x] == '\0')
				break;
			if (temp[x] == '\n') {
				temp[x] = '\0';
				x = 0;
				break;
			}
			x++;
		}
		reloc = deleteName(record, temp, &loc);
		totalReloc += reloc;
		temp[0] = '\0';
	}
	printf("	Total Relocation �� = %d\n", totalReloc);
}

void totalSearch(type_record* record) { ///////////////////????????????????????????????????????????
	char temp[Max_Size];
	int x = 0, success = 0, fail = 0, probe, loc;
	FILE* fp_r;
	fp_r = fopen("uns.txt", "r");
	if (!fp_r) {
		printf("File open error\n");
		return 0;
	}
	while (1) {
		fgets(temp, Max_Size, fp_r);
		if (strlen(temp) == 0)	//������ �� Ȯ��
			break;
		while (1) {	//������ �Է¹޾��� �� ������� '\n'�� ���ش�.
			if (temp[x] == '\0')
				break;
			if (temp[x] == '\n') {
				temp[x] = '\0';
				x = 0;
				break;
			}
			x++;
		}
		loc = searchName(record, temp, &probe);
		
		if (loc != -1) success++;
		else fail++;
		temp[0] = '\0';
	}
	printf("	Success count : %d, Fail count : %d\n", success, fail);

}