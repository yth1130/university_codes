#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100
#define MAX_INCOME 20000

typedef struct arec *recptr;
typedef struct arec {
	char Company[100];
	int monincome;
}rectype;

void MakeBinaryFile(FILE* fp_r, FILE* fp_w, int* line);

void adjust(recptr Rec, int root, int n);
void SWAP(rectype* rec1, rectype* rec2);
void heapSort(recptr Rec, int n);

void binSWAP(FILE* fp, int i, int j);
void binHeapSort(FILE* fp, int n);
void binAdjust(FILE* fp, int root, int n);

void BinToTxt(FILE* fpBin, FILE* fpTxt, int n);

int main() {
	char Text_File_Name[MAX_SIZE];
	int num_ret, line = 0, i;
	FILE *fp_r, *fp_w, *fp;

	srand((unsigned)time(NULL));

	printf("입력 텍스트 화일명은? : ");
	scanf("%s", Text_File_Name);

	fp_r = fopen(Text_File_Name, "r");
	if (!fp_r) {
		printf("File open error\n");
		return 0;
	}
	fp_w = fopen("Companies.bin", "wb");

	MakeBinaryFile(fp_r, fp_w, &line);	//바이너리파일 만들기

	fclose(fp_r); 
	fclose(fp_w);

	printf("%d\n", line);

	fp = fopen("Companies.bin", "r+b");

	recptr Rec = (recptr)malloc((line + 1) * sizeof(rectype));

	for (i = 1; i <= line; i++) {
		num_ret = fseek(fp, (i-1) * sizeof(rectype), SEEK_SET);
		if (num_ret != 0) {
			printf("fseek error\n");
			continue;
		}
		fread(&Rec[i], sizeof(rectype), 1, fp);
	}

	heapSort(Rec, line);	//힙 정렬

	fclose(fp);

	fp = fopen("Companies_selection.txt", "w");
	for (i = 1; i <= line; i++) {
		fprintf(fp, "%s %d\n", Rec[i].Company, Rec[i].monincome);
	}
	fclose(fp);

	fp = fopen("Companies.bin", "r+b");
	if (!fp) {
		printf("File open error\n");
		return 0;
	}
	binHeapSort(fp, line);	//바이너리파일의 힙정렬
	
	fp_w = fopen("Companies_heap.txt", "w");

	BinToTxt(fp, fp_w, line);	//바이너리파일을 텍스트파일로

	fclose(fp);
	fclose(fp_w);

	return 0;
}

void MakeBinaryFile(FILE* fp_r, FILE* fp_w, int* line) {
	char name[MAX_SIZE];
	int i;
	size_t sz;
	rectype loadrec;
	while (1) {
		fgets(name, MAX_SIZE, fp_r);
		if (strlen(name) == 0)
			break;
		for (i = 0; name[i] != '\0'; i++) {
			if (name[i] == '\n')
				name[i] = '\0';
		}
		*line += 1;
		strcpy(loadrec.Company, name);
		loadrec.monincome = (rand() % MAX_INCOME) * 1000;
		sz = fwrite(&loadrec, sizeof(rectype), 1, fp_w);
		name[0] = '\0';
		if (sz != 1)
		{
			printf("Error in fwrite. \n");
		}
	}
}

void BinToTxt(FILE* fpBin, FILE* fpTxt, int n) {
	int i;
	rectype temp;

	for (i = 0; i < n; i++) {
		fseek(fpBin, i * sizeof(rectype), SEEK_SET);
		fread(&temp, sizeof(rectype), 1, fpBin);
		fprintf(fpTxt, "%s %d\n", temp.Company, temp.monincome);
	}
}

void adjust(recptr Rec, int root, int n) {
	int child;
	char rootkey[100];
	rectype temp;

	temp = Rec[root];
	strcpy(rootkey, Rec[root].Company);
	child = 2 * root;

	while (child <= n) {
		if ((child < n) && (strcmp(Rec[child].Company, Rec[child + 1].Company) < 0))
			child++;
		if ((child > n) || strcmp(rootkey, Rec[child].Company) > 0)
			break;
		else {
			/*strcpy(Rec[child / 2].Company, Rec[child].Company);
			Rec[child / 2].monincome = Rec[child].monincome;*/
			Rec[child / 2] = Rec[child];
			child *= 2;
		}
	}
	Rec[child / 2] = temp;

}

void SWAP(rectype* rec1, rectype* rec2) {	///////////////
	rectype temp = *rec1;
	*rec1 = *rec2;
	*rec2 = temp;
}

void heapSort(recptr Rec, int n) {
	int i;

	for (i = n / 2; i > 0; i--)
		adjust(Rec, i, n);
	for (i = n - 1; i > 0; i--) {
		SWAP(&Rec[1], &Rec[i+1]);
		adjust(Rec, 1, i);
	}
}

void binSWAP(FILE* fp, int i, int j) {
	rectype rec1, rec2;
	fseek(fp, (i - 1)*sizeof(rectype), SEEK_SET);
	fread(&rec1, sizeof(rectype), 1, fp);
	fseek(fp, (j - 1)*sizeof(rectype), SEEK_SET);
	fread(&rec2, sizeof(rectype), 1, fp);

	fseek(fp, (i - 1)*sizeof(rectype), SEEK_SET);
	fwrite(&rec2, sizeof(rectype), 1, fp);
	fseek(fp, (j - 1)*sizeof(rectype), SEEK_SET);
	fwrite(&rec1, sizeof(rectype), 1, fp);
}

void binHeapSort(FILE* fp, int n) {
	int i;

	for (i = n / 2; i > 0; i--) {
		binAdjust(fp, i, n);	
	}
	fseek(fp, 0, SEEK_SET);
	for (i = n - 1; i > 0; i--) {
		binSWAP(fp, 1, i + 1);
		binAdjust(fp, 1, i);
	}
	fseek(fp, 0, SEEK_SET);
}

void binAdjust(FILE* fp, int root, int n) {
	int child, status = 0;
	char rootkey[100];
	rectype temp, lChild, rChild;

	fseek(fp, (root - 1) * sizeof(rectype), SEEK_SET);
	fread(&temp, sizeof(rectype), 1, fp);
	strcpy(rootkey, temp.Company);

	child = 2 * root;

	while (child <= n) {
		fseek(fp, (child - 1) * sizeof(rectype), SEEK_SET);
		fread(&lChild, sizeof(rectype), 1, fp);
		fseek(fp, child * sizeof(rectype), SEEK_SET);
		fread(&rChild, sizeof(rectype), 1, fp);

		if ((child < n) && (strcmp(lChild.Company, rChild.Company) < 0)) {
			child++;
			status = 1;
		}
		if (child > n)
			break;
		if (status == 0 && strcmp(rootkey, lChild.Company) > 0)
			break;
		if (status == 1 && strcmp(rootkey, rChild.Company) > 0)
			break;
		else {
			fseek(fp, (child / 2 - 1)*sizeof(rectype), SEEK_SET);
			if (status == 0)
				fwrite(&lChild, sizeof(rectype), 1, fp);
			else if (status == 1) {
				fwrite(&rChild, sizeof(rectype), 1, fp);
				status = 0;
			}
			child *= 2;
		}
	}
	fseek(fp, (child / 2 - 1)*sizeof(rectype), SEEK_SET);
	fwrite(&temp, sizeof(rectype), 1, fp);
}