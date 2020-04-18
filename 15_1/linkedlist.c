#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;	//listNode�� ������
typedef struct listNode {				//����ü listNode�� ����
	char name[20];
	int st_no;
	float gpa;
	char phone[20], address[30];
	listPointer link;
} listNode;

listPointer student, First = NULL;

void search_ins_position(listPointer first);
void Print_between(char nameA[20],char nameB[20]);			//�Ű������� ���� �̸��� ������ �����͸� ����Ѵ�.
int Compute_num_students_of_location(char location[30]);	//� ������ �л����� ������� ��ȯ�Ѵ�.
int delete_node(listPointer first, char stuname[20]);		//� �л��� ��带 �����Ѵ�.
void Print_linked_list(listPointer first);					//��ü ���Ḯ��Ʈ�� ����Ѵ�.

int main() {
	char name[20], tnameA[20], tnameB[20], location[30], stuname[20];
	int num, res;
	FILE *file;
	file = fopen("studentinfo.txt", "r");		//studentinfo.txt ������ �б��������� �����Ѵ�.
	
	for (int i = 0; feof(file) == 0; i++){		//feof�� ������ ������ ������ �� 0��, ������ ������ �� 0�̿��� ���� ��ȯ�Ѵ�.
		if (i == 0) {
			student = (listPointer)malloc(sizeof(listNode));	//����Ʈ�� �����ּҸ� First�� ����Ű���� �Ѵ�.
			First = student;
		}
		else  {
			student->link = (listPointer)malloc(sizeof(listNode));	//listNode����ü�� ũ�⸸ŭ �޸𸮸� �Ҵ��ϰ� student->link�� �� �޸𸮸� ����Ű���� �Ѵ�.
			student = student->link;									//������ �����ϰ�� ����ؼ� �������� �Ҵ����� �޸𸮸� ����Ű���� �Ѵ�.
		}
		fscanf(file, "%s %d %f %s %s", &student->name, &student->st_no, &student->gpa, &student->phone, &student->address); //���Ͽ��� �ҷ��� �����͸� ������� ����ü ��������� �Ҵ��Ѵ�.

	}

	student->link = NULL;

	search_ins_position(First);
	Print_linked_list(First);

	printf("\n�� �л��� �̸��� �����ÿ� > ");
	scanf("%s %s", tnameA, tnameB);
	Print_between(tnameA, tnameB);

	printf("\n���� ���� �����ÿ� > ");
	scanf("%s", location);
	num = Compute_num_students_of_location(location);
	printf("�� ������ �л����� %d�� �Դϴ�.\n", num);

	printf("\n������ �л� �̸��� �����ÿ� > ");
	scanf("%s", stuname);
	res = delete_node(First, stuname);
	if (res == 1)
		printf("���� ����!\n");
	else 
		printf("���� ����\n");

	Print_linked_list(First);
}

void search_ins_position(listPointer first){	//��� ����Ʈ�� ��������
	listPointer prev, next;
	int max, i, j;

	student = first;
	for (max = 0; student->link != NULL; max++) {	//����Ʈ�� ��尡 ��ִ��� max�� �����Ѵ�.
		student = student->link;
	}

	for (i = 0; i < max; i++) {			//��忡 ������ŭ �ٱ� ������ �ݺ��Ѵ�.
		prev = First;
		student = First;
		next = student->link;

		for (j = 0; j < max - i; j++) {	//���� ���������� ���ĵ� ���� ����Ʈ�� ������ ��������ŭ �ݺ��Ѵ�.
			if (j == 0) {						//�� ó���� ���� ���� ������ �ٲ���� �ϸ� ����Ʈ�� ó���� ��Ÿ���� First�� �ٲ��ش�.
				if (strcmp(student->name, next->name) > 0) {		//�ٷ� �յ��� �̸��� strcmp�� ���� �տ� ���� �ڿ� �ͺ��� ũ�� �ڷ� �����ش�.
					First = next;
					student->link = next->link;
					next->link = student;

					prev = next;
					next = student->link;
				}
				else {
					student = student->link;
					next = next->link;
				}
			}
			else {								//ó���� ������ ������ ����Ʈ�κ�
				if (strcmp(student->name, next->name) > 0) {		//���̵��� ���� ����.
					prev->link = next;
					student->link = next->link;
					next->link = student;

					next = student->link;
				}
				else {
					student = student->link;
					next = next->link;
				}
				prev = prev->link;	//prev�� ������ ó���� ������ ������ �κп��� �Ͼ��.
			}

		}

	}
	

}

void Print_between(char nameA[20], char nameB[20]) {
	student = First;
	int check = 0;

	while (student->link != NULL) {	
		if (strcmp(student->name, nameA) == 0)	//ù��° �Ű������� ����ü�� ��������� �̸��� ������� check�� 1�� �ϰ�
			check = 1;
		if (check == 1) {						//check�� 1�� �����̸� �� ����� ��� �������� ��� ����Ѵ�.
			printf("%s %d %.1f %s %s \n", student->name, student->st_no, student->gpa, student->phone, student->address);
		}
		student = student->link;		//student�� ���� ��带 ����Ű���� �Ѵ�.

		if (strcmp(student->name, nameB) == 0) {	//���� ����� �̸� ��������� �ι�° �Ű������� ���� ��� �ϴ� �� ��带 ������ְ�
			printf("%s %d %.1f %s %s \n", student->name, student->st_no, student->gpa, student->phone, student->address);
			check = 0;								//check�� 0���� �ٲ��ش�.
		}
	}
}


int Compute_num_students_of_location(char location[30]) {
	student = First;
	int count = 0;

	while (student->link != NULL) {
		if (strcmp(student->address, location) == 0)	//listNode�� ������� address�� �Ű������� ������� count�� �÷��ش�.
			++count;
		student = student->link;
	}

	return count;	//count�� �� ������ �ο����ν� ��ȯ�Ѵ�.
}


int delete_node(listPointer first, char stuname[20]) {
	student = first;
	listPointer temp;
	for (int i = 0; student->link != NULL; i++) {
		if (strcmp(student->name, stuname) == 0) {	//���� �̸��� ã�����
			if (i == 0) {								//ù��° ����� �̸��� �Ű������� �������� Ư���ϰ�
				First = student->link;					//First�� �ι�° ��带 ����Ű���� ���ش�.

				return 1;
			}
			temp->link = student->link;					//�ι�° ���ʹ� ���� ��带 ���� ����� student��
														//���� ����� temp�� ����Ű���� �Ѵ�.
			return 1;
		}
		temp = student;				//���� student�� ����Ű�� ��带 temp���� ����Ű���� �Ѵ�.
		student = student->link;		//�׸��� student�� ���� ���� ����.

	}

	return 0;
}

void Print_linked_list(listPointer first) {
	student = first;
	for (int i = 1; student->link != NULL; i++) {	//student->link != NULL; i++) {	//���Ḯ��Ʈ�� ��� ������ �� �ٿ� �� ����� ����Ѵ�.
		if (i<10) 
			printf("0%d: %s ", i, student->name);
		else
			printf("%d: %s ", i, student->name);
		printf("%d %.1f %s %s \n", student->st_no, student->gpa, student->phone, student->address);
		student = student->link;

	}
}