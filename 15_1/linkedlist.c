#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;	//listNode의 포인터
typedef struct listNode {				//구조체 listNode의 정의
	char name[20];
	int st_no;
	float gpa;
	char phone[20], address[30];
	listPointer link;
} listNode;

listPointer student, First = NULL;

void search_ins_position(listPointer first);
void Print_between(char nameA[20],char nameB[20]);			//매개변수로 들어온 이름들 사이의 데이터를 출력한다.
int Compute_num_students_of_location(char location[30]);	//어떤 지역의 학생수가 몇명인지 반환한다.
int delete_node(listPointer first, char stuname[20]);		//어떤 학생의 노드를 삭제한다.
void Print_linked_list(listPointer first);					//전체 연결리스트를 출력한다.

int main() {
	char name[20], tnameA[20], tnameB[20], location[30], stuname[20];
	int num, res;
	FILE *file;
	file = fopen("studentinfo.txt", "r");		//studentinfo.txt 파일을 읽기전용으로 오픈한다.
	
	for (int i = 0; feof(file) == 0; i++){		//feof는 파일의 내용이 남았을 때 0을, 파일이 끝났을 때 0이외의 수를 반환한다.
		if (i == 0) {
			student = (listPointer)malloc(sizeof(listNode));	//리스트의 시작주소를 First가 가리키도록 한다.
			First = student;
		}
		else  {
			student->link = (listPointer)malloc(sizeof(listNode));	//listNode구조체의 크기만큼 메모리를 할당하고 student->link가 그 메모리를 가리키도록 한다.
			student = student->link;									//시작을 제외하고는 계속해서 다음으로 할당해준 메모리를 가리키도록 한다.
		}
		fscanf(file, "%s %d %f %s %s", &student->name, &student->st_no, &student->gpa, &student->phone, &student->address); //파일에서 불러온 데이터를 순서대로 구조체 멤버변수에 할당한다.

	}

	student->link = NULL;

	search_ins_position(First);
	Print_linked_list(First);

	printf("\n두 학생의 이름을 넣으시오 > ");
	scanf("%s %s", tnameA, tnameB);
	Print_between(tnameA, tnameB);

	printf("\n지역 명을 넣으시오 > ");
	scanf("%s", location);
	num = Compute_num_students_of_location(location);
	printf("그 지역의 학생수는 %d명 입니다.\n", num);

	printf("\n삭제할 학생 이름을 넣으시오 > ");
	scanf("%s", stuname);
	res = delete_node(First, stuname);
	if (res == 1)
		printf("삭제 성공!\n");
	else 
		printf("삭제 실패\n");

	Print_linked_list(First);
}

void search_ins_position(listPointer first){	//노드 리스트의 버블정렬
	listPointer prev, next;
	int max, i, j;

	student = first;
	for (max = 0; student->link != NULL; max++) {	//리스트에 노드가 몇개있는지 max에 저장한다.
		student = student->link;
	}

	for (i = 0; i < max; i++) {			//노드에 개수만큼 바깥 포문을 반복한다.
		prev = First;
		student = First;
		next = student->link;

		for (j = 0; j < max - i; j++) {	//안쪽 포문에서는 정렬된 뒤쪽 리스트를 제외한 나머지만큼 반복한다.
			if (j == 0) {						//맨 처음의 경우로 만약 순서를 바꿔줘야 하면 리스트의 처음을 나타내는 First를 바꿔준다.
				if (strcmp(student->name, next->name) > 0) {		//바로 앞뒤의 이름을 strcmp로 비교해 앞에 것이 뒤에 것보다 크면 뒤로 보내준다.
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
			else {								//처음을 제외한 나머지 리스트부분
				if (strcmp(student->name, next->name) > 0) {		//아이디어는 위와 같다.
					prev->link = next;
					student->link = next->link;
					next->link = student;

					next = student->link;
				}
				else {
					student = student->link;
					next = next->link;
				}
				prev = prev->link;	//prev의 전진은 처음을 제외한 나머지 부분에서 일어난다.
			}

		}

	}
	

}

void Print_between(char nameA[20], char nameB[20]) {
	student = First;
	int check = 0;

	while (student->link != NULL) {	
		if (strcmp(student->name, nameA) == 0)	//첫번째 매개변수와 구조체의 멤버변수의 이름이 같을경우 check를 1로 하고
			check = 1;
		if (check == 1) {						//check가 1인 상태이면 그 노드의 멤버 변수들을 모두 출력한다.
			printf("%s %d %.1f %s %s \n", student->name, student->st_no, student->gpa, student->phone, student->address);
		}
		student = student->link;		//student가 다음 노드를 가리키도록 한다.

		if (strcmp(student->name, nameB) == 0) {	//다음 노드의 이름 멤버변수가 두번째 매개변수와 같을 경우 일단 그 노드를 출력해주고
			printf("%s %d %.1f %s %s \n", student->name, student->st_no, student->gpa, student->phone, student->address);
			check = 0;								//check를 0으로 바꿔준다.
		}
	}
}


int Compute_num_students_of_location(char location[30]) {
	student = First;
	int count = 0;

	while (student->link != NULL) {
		if (strcmp(student->address, location) == 0)	//listNode의 멤버변수 address와 매개변수가 같을경우 count를 늘려준다.
			++count;
		student = student->link;
	}

	return count;	//count를 그 지역의 인원수로써 반환한다.
}


int delete_node(listPointer first, char stuname[20]) {
	student = first;
	listPointer temp;
	for (int i = 0; student->link != NULL; i++) {
		if (strcmp(student->name, stuname) == 0) {	//같은 이름을 찾은경우
			if (i == 0) {								//첫번째 노드의 이름과 매개변수가 같을경우는 특별하게
				First = student->link;					//First가 두번째 노드를 가리키도록 해준다.

				return 1;
			}
			temp->link = student->link;					//두번째 부터는 다음 노드를 현재 노드인 student의
														//이전 노드인 temp가 가리키도록 한다.
			return 1;
		}
		temp = student;				//현재 student가 가리키는 노드를 temp또한 가리키도록 한다.
		student = student->link;		//그리고 student는 다음 노드로 간다.

	}

	return 0;
}

void Print_linked_list(listPointer first) {
	student = first;
	for (int i = 1; student->link != NULL; i++) {	//student->link != NULL; i++) {	//연결리스트의 모든 내용을 한 줄에 한 사람씩 출력한다.
		if (i<10) 
			printf("0%d: %s ", i, student->name);
		else
			printf("%d: %s ", i, student->name);
		printf("%d %.1f %s %s \n", student->st_no, student->gpa, student->phone, student->address);
		student = student->link;

	}
}