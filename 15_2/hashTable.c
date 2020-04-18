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
	makeEmptyChain(record);	//해쉬 테이블 record의 모든 주소를 양방향 빈자리 체인에 넣는다.

	QueryPerformanceCounter(&StartTime);
	insertName(record, fp_r, findIndex);
	playTime = checkTime(StartTime, TicksPerSec);
	printf("단순한 빈자리 찾기방식 시간 : %f \n", playTime);

	free(record);
	
	fp_r = fopen("uns.txt", "r");
	if (!fp_r) {
		printf("File open error\n");
		return 0;
	}
	record = (type_record*)malloc(sizeof(type_record)*Tbl_Size);
	makeEmptyChain(record);	//해쉬 테이블 record의 모든 주소를 양방향 빈자리 체인에 넣는다.

	QueryPerformanceCounter(&StartTime);
	insertName(record, fp_r, findIndexFast);
	playTime = checkTime(StartTime, TicksPerSec);
	printf("양방향 빈자리 찾기방식 시간 : %f \n", playTime);



	printf("명령들:  r(검색), d(삭제), p(성능측정), t(일괄삭제), v(전체탐색), e(종료).\n");
	while (1) {
		printf("\n명령은? ");
		scanf("%c", &i);
		getchar();

		switch (i) {
		case 'r':
			scanf(" %s", temp);
			getchar();
			loc = searchName(record, temp, &probe);
			if (loc != -1) printf("	저장위치 = %d, Probe 수 = %d\n", loc, probe);
			else printf("	그런 데이타는 존재하지 않습니다.\n");
			break;
		case 'd':
			scanf(" %s", temp);
			getchar();
			reloc = deleteName(record, temp, &loc);
			if (reloc != -1) printf("	저장위치 = %d, Relocation 수 = %d\n", loc, reloc);
			else printf("	그런 데이타는 존재하지 않습니다.\n");
			break;
		case 'p':
			QueryPerformanceCounter(&StartTime);
			perfomanceCheck(record);
			playTime = checkTime(StartTime, TicksPerSec);
			printf("	성능측정 시간 : %f \n", playTime);
			break;
		case 't':
			QueryPerformanceCounter(&StartTime);
			totalDelete(record);
			playTime = checkTime(StartTime, TicksPerSec);
			printf("	성능측정 시간 : %f \n", playTime);
			break;
		case 'v':
			QueryPerformanceCounter(&StartTime);
			totalSearch(record);
			playTime = checkTime(StartTime, TicksPerSec);
			printf("	성능측정 시간 : %f \n", playTime);
			break;
		case 'e':
			printf("	실험을 종료합니다.\n");
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
	while (1) {	//삽입작업
		fgets(temp, Max_Size, fp_r);
		if (strlen(temp) == 0)	//파일의 끝 확인
			break;
		while (1) {	//한줄을 입력받았을 때 따라오는 '\n'를 없앤다.
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

void findIndex(type_record* record, int tempHA, char* temp) {	/////////////////////////////flink, blink고려하기
	int i = tempHA;
	int x;
	if (strcmp(record[tempHA].name, "\0") == 0) {	//구조체 배열의 tempHA인덱스의 이름부가 비어있으면 그냥 넣는다.
		strcpy(record[tempHA].name, temp);

	}
	else {
		while (record[i].link != -1) {	//이름이 차있으면 링크가 비어있을 때까지 링크를 타고 이동한다.
			x = i;
			i = record[i].link;
		}
		if (strcmp(record[i].name, "\0") == 0) {	//이름이 비어있으면 넣고
			strcpy(record[i].name, temp);
			record[x].link = i;
		}
		else {	/////////아니면 빈자리 체인 이용
			x = i;
			i = 0;
			while (strcmp(record[i].name, "\0") != 0) {	//체인의 처음부터
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
	if (strcmp(record[i].name, "\0") == 0) {	//구조체 배열의 tempHA인덱스의 이름부가 비어있으면 그냥 넣는다.
		strcpy(record[i].name, temp);
	}
	else {
		while (record[i].link != -1) {	//이름이 차있으면 링크가 비어있을 때까지 링크를 타고 이동한다.
			x = i;
			i = record[i].link;
		}
		if (strcmp(record[i].name, "\0") == 0) {	//이름이 비어있으면 넣고
			strcpy(record[i].name, temp);
			record[x].link = i;
		}
		else {	/////////아니면 빈자리 체인 이용
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
	// name 의 글자 j 에 대하여 다음을 수행한다:
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
	while (strcmp(record[loc].name, recname) != 0) {	//테이블에서 찾을 이름을 검색
		loc = record[loc].link;	//링크를 계속 따라간다.
		if (loc == -1)	//못찾고 인덱스가 -1이 됨
			break;
		(*probe)++;	//Probe수 증가
	}
	return loc;
}

int deleteName(type_record* record, char recname[], int* loc) {	//relocation수 반환
	int probe;
	*loc = searchName(record, recname, &probe);	//지우려는 이름의 HA값을 얻는다
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
		if (strlen(temp) == 0)	//파일의 끝 확인
			break;
		while (1) {	//한줄을 입력받았을 때 따라오는 '\n'를 없앤다.
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
		if (strlen(temp) == 0)	//파일의 끝 확인
			break;
		while (1) {	//한줄을 입력받았을 때 따라오는 '\n'를 없앤다.
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
	printf("	Total Relocation 수 = %d\n", totalReloc);
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
		if (strlen(temp) == 0)	//파일의 끝 확인
			break;
		while (1) {	//한줄을 입력받았을 때 따라오는 '\n'를 없앤다.
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