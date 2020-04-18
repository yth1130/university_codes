#include <stdio.h>
#include <string.h>

#define d 2	//capacity order

typedef struct _rec {
	char name[50];
	int leng;
} type_rec;

typedef struct _node* nodePtr;
typedef struct _node {
	type_rec Rec[2*d];
	nodePtr p[2*d + 1];
	int fill_cnt;
} node;

typedef struct _bigNode {
	type_rec Rec[2 * d + 1];
	nodePtr p[2 * d + 2];
} bigNode;

typedef struct two_Bn {
	type_rec Rec[2 * (2 * d)];
	nodePtr p[2 * (2 * d) + 1];
} two_Bnode;

nodePtr Root = NULL;

void FileToBtree(FILE* fp);
void B_tree_Insertion(char ComName[51]);
void getName(char cmd[55], char name[50]);

void B_tree_Retrieval(char ComName[51]);
void B_tree_SequentialPrinting(nodePtr node, FILE* fp);
void B_tree_Deletion(char name[51]);

int main() {
	char cmd[55], name[50] = "\0";
	int leng;

	FILE* fp_r;
	fp_r = fopen("Com_names1.txt", "r");
	if (!fp_r) {
		printf("File open error\n");
		return 0;
	}
	FileToBtree(fp_r);
	fclose(fp_r);

	fp_r = fopen("Com_names2.txt", "r");
	if (!fp_r) {
		printf("File open error\n");
		return 0;
	}
	FileToBtree(fp_r);
	fclose(fp_r);


	while (1) {
		printf("	Command? ");
		gets(cmd);
		fflush(stdin);
		switch (cmd[0]) {
		case 'r': //이름을 찾고 발견된 위치(레벨 및 레코드 내의 위치) 출력
			getName(cmd, name);
			B_tree_Retrieval(name);
			break;
		case 'd': //이름을 제거한 다음 성공 여부를 출력 (그리고 이 과정에서 발생한 redistribution의 총 수,  merging 의 총 수도 출력)
			getName(cmd, name);
			B_tree_Deletion(name);
			break;
		case 's': //B-tree 안의 모든 레코드를 이름순으로 SeqData.txt 화일에 출력
			if (strcmp(cmd, "sp") == 0) {
				FILE* fp = fopen("SeqData.txt", "w");
				B_tree_SequentialPrinting(Root, fp);
				fclose(fp);
			}
			break;
		case 'i': //주어진 상호명을 가지는 레코드를 만들어 b-tree 에 삽입. 삽입과정에서 발생한 split 의 총수를 출력
			getName(cmd, name);
			B_tree_Insertion(name);
			break;
		case 'e': //프로그램 종료
			if (strcmp(cmd, "exit") == 0) {
				return 0;
			}
		}
	}
}

int getLeng(char cmd[55]) {
	int i;
	char x = cmd[0];
	for (i = 0; x != '\0'; i++) {
		x = cmd[i];
	}
	return i-2;
}

void getName(char cmd[55], char name[50]) {
	int i = 0, j;
	char x = cmd[i];
	
	while (x != ' ') {
		i++;
		x = cmd[i];
	}
	i++;
	for (j=0; x != '\0'; j++) {
		name[j] = cmd[i];
		i++;
		x = cmd[i];
	}
	name[j] = cmd[i];
}

void FileToBtree(FILE* fp) {
	char name[50];
	int x = 0;
	while (!feof(fp)) {
		fgets(name, 50, fp);
		if (strlen(name) == 0) break;
		while (1) {
			if (name[x] == '\0') break;
			if (name[x] == '\n') {
				name[x] = '\0';
				break;
			}
			x++;
		}
		B_tree_Insertion(name);
		x = 0;
	}
}

void B_tree_Insertion(char ComName[51]) {
	puts(ComName);
	int found, i, j;	//0이면 false, 1이면 true
	nodePtr curr, P;
	nodePtr stack[1000];
	int stackIndex = 0;

	type_rec newRec;
	strcpy(newRec.name, ComName);
	newRec.leng = strlen(ComName);

	if (Root == NULL) {
		Root = (nodePtr)malloc(sizeof(node));
		Root->Rec[0] = newRec;
		for (int i = 0; i < 2 * d + 1; i++) {
			Root->p[i] = NULL;
		}
		Root->fill_cnt = 1;
		return;
	}
	found = 0;
	P = curr = Root;

	do {
		//if (curr->p[0] == NULL) {	//리프노드를 찾음 ?
		//	P = NULL;
		//	break;
		//}
		//if (strcmp(curr->Rec[curr->fill_cnt - 1].name, ComName) < 0) //마지막 레코드의 키값보다 새로 넣을 레코드의 키값이 클 경우
		//	P = curr->p[curr->fill_cnt];
		//else {
		//	for (i = 0; i < 2 * d; i++) {
		//		if (strcmp(curr->Rec[i].name, ComName) > 0) {	//새로 넣을 레코드의 키값보다 큰 값을 찾음
		//			P = curr->p[i];
		//			break;
		//		}
		//		else if (strcmp(curr->Rec[i].name, ComName) == 0) {	//중복 레코드 발견
		//			found = 1;
		//			break;
		//		}
		//	}
		//	if (found == 1) break;
		//	else if (P != NULL) {
		//		stack[stackIndex] = curr;
		//		stackIndex++;
		//		curr = P;
		//	}
		//}
		for (i = 0; i < 2 * d; i++) {
			if (strcmp(curr->Rec[i].name, ComName) > 0) {	//새로 넣을 레코드의 키값보다 큰 값을 찾음
				break;
			}
			else if (strcmp(curr->Rec[i].name, ComName) == 0) {	//중복 레코드 발견
				found = 1;
				break;
			}
		}
		P = curr->p[i];
		if (found == 1) break;
		else if (P != NULL) {
			stack[stackIndex] = curr;
			stackIndex++;
			curr = P;
		}
	} while (found != 1 && P);

	if (found == 1) {
		printf("The key to be inserted already exists.\n");
		return;
	}

	do {
		if (curr->fill_cnt < 2 * d) { //넣을 공간이 있는 경우
			for (i = 0; i < curr->fill_cnt; i++) {
				if (strcmp(curr->Rec[i].name, ComName) > 0) break;
			}
			for (j = curr->fill_cnt; j > i; j--) {
				curr->Rec[j] = curr->Rec[j - 1];
				curr->p[j + 1] = curr->p[j];
			}
			curr->Rec[i] = newRec;
			curr->p[i + 1] = P;
			curr->fill_cnt++;
			break;
		}
		else { //curr가 가리키는 노드가 이미 꽉 찬 상태

			//bignode 만들기
			bigNode bignode;
			bignode.p[0] = curr->p[0];
			for (i = 0; i < 2 * d + 1; i++) {
				if (strcmp(curr->Rec[i].name, ComName) > 0) break;
			}
			if (i == 2 * d + 1) i--;
			for (j = 0; j < i; j++) {
				bignode.Rec[j] = curr->Rec[j];
				bignode.p[j + 1] = curr->p[j + 1];
			}
			bignode.Rec[j] = newRec;
			bignode.p[j + 1] = P;
			j++;
			for (; i < 2 * d; i++) {
				bignode.Rec[j] = curr->Rec[i];
				bignode.p[j + 1] = curr->p[i + 1];
				j++;
			}

			//bignode나누기
			for (i = 0; i < d; i++) {
				curr->Rec[i] = bignode.Rec[i];
				curr->p[i] = bignode.p[i];
			}
			curr->p[i] = bignode.p[i];
			curr->fill_cnt = d;

			nodePtr NEW;
			NEW = (nodePtr)malloc(sizeof(node));
			for (i = 0; i < d; i++) {
				NEW->Rec[i] = bignode.Rec[i + (d + 1)];
				NEW->p[i] = bignode.p[i + (d + 1)];
			}
			NEW->p[i] = bignode.p[2 * d + 1];
			NEW->fill_cnt = d;

			P = NEW;
			type_rec in_record = bignode.Rec[d];	//center record of bignode

			if (stackIndex > 0) {
				stackIndex--;
				curr = stack[stackIndex];
				stack[stackIndex] = NULL;
				
				newRec = in_record;	//??
			}
			else {
				nodePtr Newroot = (nodePtr)malloc(sizeof(node));
				Newroot->p[0] = curr;
				Newroot->p[1] = P;
				for (i = 2; i < 2 * d + 1; i++) {
					Newroot->p[i] = NULL;
				}
				Newroot->Rec[0] = in_record;
				Newroot->fill_cnt = 1;
				Root = Newroot;
				return;
			}
		}
	} while (1);

}

void B_tree_Retrieval(char ComName[51]) {
	int i, found = 0, level = 0;
	nodePtr curr, P;
	curr = P = Root;
	do {
		level++;
		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(curr->Rec[i].name, ComName) > 0) break;
			else if (strcmp(curr->Rec[i].name, ComName) == 0) {
				found = 1;
				break;
			}
		}
		P = curr->p[i];
		if (P != NULL) curr = P;
	} while (found != 1 && P);
	if (found == 1)
		printf("이름이 있습니다. level = %d, index = %d\n", level, i);
	else printf("이름이 없습니다.\n");
}

void B_tree_SequentialPrinting(nodePtr node, FILE* fp) {
	int i;
	if (node == NULL) return;
	for (i = 0; i < node->fill_cnt; i++) {
		B_tree_SequentialPrinting(node->p[i], fp);
		fprintf(fp, "%s\n", node->Rec[i].name);
	}
	B_tree_SequentialPrinting(node->p[i], fp);
}

void B_tree_Deletion(char name[51]) {
	nodePtr curr, P, r_sibling, l_sibling, father, Pt;
	two_Bnode twoB;
	int i, j, k, n, m, h,  found = 0; 
	int finished = 0;
	nodePtr stack[1000];
	int stackIndex = 0;

	curr = Root;

	do {
		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(curr->Rec[i].name, name) > 0) break;
			else if (strcmp(curr->Rec[i].name, name) == 0) {
				found = 1;
				break;
			}
		}
		if (found == 1) break;
		else {
			P = curr->p[i];
			if (P != NULL) {
				stack[stackIndex] = curr;
				stackIndex++;
				curr = P;
			}
			else break;
		}
	} while (found != 1 && P);

	if (found == 0) { //찾는 이름이 없음
		printf("Key to delete does not exist.");
		return;
	}

	if (curr->p[0]) {
		Pt = curr->p[i + 1];
		stack[stackIndex] = curr;
		stackIndex++;
		while (Pt->p[0]) {
			stack[stackIndex] = Pt;
			stackIndex++;
			Pt = Pt->p[0];
		}
		curr->Rec[i] = Pt->Rec[0];
		curr = Pt;
		i = 0;
	}

	for (j = i + 1; j < curr->fill_cnt; j++) {
		curr->Rec[j - 1] = curr->Rec[j];
		curr->p[j] = curr->p[j + 1];
	}
	curr->fill_cnt--;
	
	do {
		if (curr->fill_cnt >= d)
			return;
		else {
			if (curr == Root) return;
			else {
				stackIndex--;
				father = stack[stackIndex];
				for (j = 0; j<father->fill_cnt; j++)
					if (father->p[j] == curr) break;

				if (j >= 1) 
					l_sibling = father->p[j - 1];
				else l_sibling = NULL;

				if (j<father->fill_cnt)  
					r_sibling = father->p[j + 1];
				else r_sibling = NULL;

				if (r_sibling != NULL && r_sibling->fill_cnt > d) {
					for (i = 0; i<curr->fill_cnt; i++) {
						twoB.p[i] = curr->p[i];
						twoB.Rec[i] = curr->Rec[i];
					}
					twoB.p[i] = curr->p[i];
					twoB.Rec[i] = father->Rec[j];
					i++;
					for (k = 0; k < r_sibling->fill_cnt; k++, i++) {
						twoB.p[i] = r_sibling->p[k];
						twoB.Rec[i] = r_sibling->Rec[k];
					}
					twoB.p[i] = r_sibling->p[k];

					h = i / 2;

					for (n = 0; n<h; n++) {
						curr->p[n] = twoB.p[n];
						curr->Rec[n] = twoB.Rec[n];
					}
					curr->p[n] = twoB.p[n];
					curr->fill_cnt = h;

					n++;
					for (m = 0; m< (i - h - 1); m++, n++) {
						r_sibling->p[m] = twoB.p[n];
						r_sibling->Rec[m] = twoB.Rec[n];
					}
					r_sibling->p[m] = twoB.p[n];
					r_sibling->fill_cnt = i - h - 1;

					father->Rec[j] = twoB.Rec[h];

					finished = 1;
				}
				
				if (!finished && l_sibling != NULL && l_sibling->fill_cnt > d){
					for (i = 0; i<l_sibling->fill_cnt; i++) {
						twoB.p[i] = l_sibling->p[i];
						twoB.Rec[i] = l_sibling->Rec[i];
					}
					twoB.p[i] = l_sibling->p[i];
					twoB.Rec[i] = father->Rec[j];
					i++;
					for (k = 0; k < curr->fill_cnt; k++, i++) {
						twoB.p[i] = curr->p[k];
						twoB.Rec[i] = curr->Rec[k];
					}
					twoB.p[i] = curr->p[k];

					h = i / 2;

					for (n = 0; n < h; n++) {
						l_sibling->p[n] = twoB.p[n];
						l_sibling->Rec[n] = twoB.Rec[n];
					}
					l_sibling->p[n] = twoB.p[n];
					l_sibling->fill_cnt = h;

					n++;
					for (m = 0; m< (i - h - 1); m++, n++) {
						curr->p[m] = twoB.p[n];
						curr->Rec[m] = twoB.Rec[n];
					}
					curr->p[m] = twoB.p[n];
					curr->fill_cnt = i - h - 1;

					father->Rec[j] = twoB.Rec[h];

					finished = 1;
				}

				if (!finished) {
					if (r_sibling != NULL) {
						for (i = 0; i<curr->fill_cnt; i++) {
							twoB.p[i] = curr->p[i];
							twoB.Rec[i] = curr->Rec[i];
						}
						twoB.p[i] = curr->p[i];
						twoB.Rec[i] = father->Rec[j];
						i++;
						for (k = 0; k < r_sibling->fill_cnt; k++, i++) {
							twoB.p[i] = r_sibling->p[k];
							twoB.Rec[i] = r_sibling->Rec[k];
						}
						twoB.p[i] = r_sibling->p[k];

						for (i = 0; i < 2 * d; i++) {
							curr->p[i] = twoB.p[i];
							curr->Rec[i] = twoB.Rec[i];
						}
						curr->p[i] = twoB.p[i];
						curr->fill_cnt = 2 * d;

						for (i = j + 1; j < father->fill_cnt; j++, i++) {
							father->Rec[i - 1] = father->Rec[i];
							father->p[i] = father->p[i + 1];
						}
						father->fill_cnt -= 1;
					}
					else {
						j--;
						for (i = 0; i<l_sibling->fill_cnt; i++) {
							twoB.p[i] = l_sibling->p[i];
							twoB.Rec[i] = l_sibling->Rec[i];
						}
						twoB.p[i] = l_sibling->p[i];
						twoB.Rec[i] = father->Rec[j];
						i++;
						for (k = 0; k < curr->fill_cnt; k++, i++) {
							twoB.p[i] = curr->p[k];
							twoB.Rec[i] = curr->Rec[k];
						}
						twoB.p[i] = curr->p[k];

						for (i = 0; i < 2 * d; i++) {
							l_sibling->p[i] = twoB.p[i];
							l_sibling->Rec[i] = twoB.Rec[i];
						}
						l_sibling->p[i] = twoB.p[i];
						l_sibling->fill_cnt = 2 * d;

						for (i = j + 1; j < father->fill_cnt; j++) {
							father->Rec[i - 1] = father->Rec[i];
							father->p[i] = father->p[i + 1];
						}
						father->fill_cnt -= 1;
					}

					if (father->fill_cnt == 0) {
						Root = curr;
						return;
					}
					curr = father;
					if (curr == Root) finished = 1;
				}
				if (curr->fill_cnt<d) finished = 0;
			}
		}
	} while (finished != 1);
}