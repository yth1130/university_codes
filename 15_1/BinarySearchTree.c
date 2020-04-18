#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct astr {
	int key;
	char name[50];
} element;

typedef struct anod *Ty_Node_Ptr;
Ty_Node_Ptr root;
int level=1, maxlevel, tlevel=1;

typedef struct anod {
	element data;
	Ty_Node_Ptr leftChild, rightChild; //?
} Ty_Node;

void make_node_and_attach_to_parent(Ty_Node_Ptr parent, Ty_Node_Ptr np);
void print_general_tree(Ty_Node_Ptr curr);
int read_upper(FILE *fp, char buf[20][50]);
Ty_Node_Ptr search_node(Ty_Node_Ptr cur, char sname[]);
void insert_node(Ty_Node_Ptr cur, int key, char sname[]);
Ty_Node_Ptr modifiedSearch(Ty_Node_Ptr tree, char sname[]);
void treelevel(Ty_Node_Ptr cur); 
Ty_Node_Ptr delete_node(Ty_Node_Ptr cur, char sname[]);
Ty_Node_Ptr search_BST(Ty_Node_Ptr cur, char sname[], Ty_Node_Ptr *par);



int main() {
	FILE *fp;
	char job, buf[20][50], irm[50];
	int num_persons, k,hak;
	Ty_Node_Ptr np;

	fp = fopen("sdata.txt", "r");
	if (!fp) {
		printf("file open error.\n");
		return 0;
	}

	do {
		num_persons = read_upper(fp, buf);
		if (num_persons == 0)
			break;
		if (!root) {
			np = (Ty_Node_Ptr)malloc(sizeof(Ty_Node));
			np->data.key = atoi(buf[0]);
			strcpy(np->data.name, buf[1]);
			root = np;
			np->leftChild = NULL;
			np->rightChild = NULL;
			/*for (k = 1; k < num_persons; k++)
				make_node_and_attach_to_parent(np, buf[k], k - 1);*/
		}
		else {
			Ty_Node_Ptr np1;
			np1 = (Ty_Node_Ptr)malloc(sizeof(Ty_Node));
			np1->data.key = atoi(buf[0]);
			strcpy(np1->data.name, buf[1]);
			np1->leftChild = NULL;
			np1->rightChild = NULL;

			make_node_and_attach_to_parent(root, np1);
		}
	} while (1);


	while (1) {
		printf("������ �۾��� (i, p, s, d, h, b, u, e) ? ");
		job=getchar();
		if (job == 'i') {
			scanf("%d %s", &hak, &irm );
			insert_node(root, hak, irm);
			
		}
		else if (job == 'p') {
			printf("ȭ���� ������ ������ �����ϴ�:\n");
			print_general_tree(root);
		}
		else if (job == 's') {
			scanf("%s", &irm);
			if (np = search_node(root, irm))
				printf("�̸�:%s, �й�:%d. ������ġ = %d\n", np->data.name, np->data.key, level);
			level = 1;
		}
		else if (job == 'd') {
			scanf("%s", &irm); 
			delete_node(root, irm);

		}
		else if (job == 'h') {
			treelevel(root);
			printf("�� BST�� ���� = %d\n", maxlevel);
			tlevel = 1;
			maxlevel = 0;
		}

		else if (job == 'b') {
			scanf("%s", &irm);
			np = search_node(root, irm);
			if (np->leftChild != NULL)
				printf("%s�� ���������� %s\n", np->data.name, np->leftChild->data.name);
			if (np->rightChild != NULL)
				printf("%s�� ���������� %s\n", np->data.name, np->rightChild->data.name);
		}
		else if (job == 'u') {
			Ty_Node_Ptr temp = root;
			scanf("%s", &irm);
			np = modifiedSearch(temp, irm);
			temp = search_node(root, irm);
			printf("%s�� �θ�� %s\n", temp->data.name, np->data.name);
		}
		else if (job == 'e') {
			printf("�����մϴ�.\n");
			return 0;
		}
		getchar(); //���ۺ���
	}



}

int read_upper(FILE *fp, char buf[20][50]) {//�迭buf�� �ܾ �ְ� �ܾ� ���� ��ȯ
	int i, j, k;
	char line[400];
	char *cp;
	cp = fgets(line, 400, fp);
	if (!cp) {
		return 0;
	}
	else {
		if (line[0] == '-')
			return 0;

		i = 0;
		j = 0;
		while (1) {
			k = 0;
			while (line[j] != ' ' && line[j] != '\n') {
				buf[i][k] = line[j];
				j++;
				k++;
			}
			buf[i][k] = '\0';
			i++;
			if (line[j] == '\n')
				break;
			else {
				do j++;
				while (line[j] == ' ');
			}
		}
		return i;
	}
}

void make_node_and_attach_to_parent(Ty_Node_Ptr parent, Ty_Node_Ptr np) {
	if (strcmp(parent->data.name, np->data.name) == 0)  {
		return;
	}
	else if (strcmp(parent->data.name, np->data.name) > 0)  {
		if (parent->leftChild == NULL)
			parent->leftChild = np;
		else
			make_node_and_attach_to_parent(parent->leftChild, np);
	}
	else {
		if (parent->rightChild == NULL)
			parent->rightChild = np;
		else
			make_node_and_attach_to_parent(parent->rightChild, np);
	}
}

void print_general_tree(Ty_Node_Ptr curr) {
	int i;
	if (!curr)
		return;
	print_general_tree(curr->leftChild);
	printf("�й�:%.3d �̸�:%s\n", curr->data.key, curr->data.name);
	print_general_tree(curr->rightChild);
}

Ty_Node_Ptr search_node(Ty_Node_Ptr cur, char sname[]) { //sname�� Ʈ���� �ִٸ� �� ��ġ�� ��ȯ
	int i;
	Ty_Node_Ptr rptr;
	if (!cur)
		return NULL;
	
	if (strcmp(cur->data.name, sname) == 0) {
		return cur; // ����.
	}
	else
	{
		if (cur->leftChild != NULL) {
			level++;
			rptr = search_node(cur->leftChild, sname);
			if (rptr)
				return rptr;
			level--;
		}

		if (cur->rightChild != NULL) {
			level++;
			rptr = search_node(cur->rightChild, sname);
			if (rptr)
				return rptr;
			level--;
		}
		return NULL;
	}
}


void insert_node(Ty_Node_Ptr cur, int key, char sname[]) {
	Ty_Node_Ptr ptr, temp;
	ptr = (Ty_Node_Ptr)malloc(sizeof(Ty_Node));
	ptr->data.key = key;
	strcpy(ptr->data.name, sname);
	ptr->leftChild = NULL;
	ptr->rightChild = NULL;
	if (!cur)
		cur = ptr;
	else {
		temp = modifiedSearch(cur, sname);
		if (!temp)
			printf("���� Ű�� ��尡 �̹� �����Ͽ� ���� ������.\n");
		else {
			if (sname < temp->data.name)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
			printf("�Է� ����.\n");
		}
	}
}

Ty_Node_Ptr modifiedSearch(Ty_Node_Ptr tree, char sname[]) {
	Ty_Node_Ptr parent = NULL;
	while (tree) {
		if (strcmp(sname, tree->data.name)== 0)
			return parent;
		parent = tree;
		if (strcmp(sname, tree->data.name) < 0)
			tree = tree->leftChild;
		else
			tree = tree->rightChild;
	}
	return parent; //tree�� null�� �Ǳ� ���� ��带 ����
}

void treelevel(Ty_Node_Ptr cur) { //Ʈ���� ���̸� ���Ѵ�
	if (cur->leftChild != NULL) {
		tlevel++;
		if (tlevel > maxlevel)
			maxlevel = tlevel;
		treelevel(cur->leftChild);
		tlevel--;
	}
	if (cur->rightChild != NULL) {
		tlevel++;
		if (tlevel > maxlevel)
			maxlevel = tlevel;
		treelevel(cur->rightChild);
		tlevel--;
	}


}

Ty_Node_Ptr delete_node(Ty_Node_Ptr cur, char sname[]) {
	int i;
	Ty_Node_Ptr nptr, parent, succ, curr;
	nptr = search_BST(cur, sname, &parent);
	if (!nptr)
		printf("�׷� �̸��� �����ϴ�.\n");
	else {
		if (nptr->leftChild && nptr->rightChild) {
			succ = nptr->rightChild;
			parent = nptr;
			while (succ->leftChild) {
				parent = succ;
				succ = succ->leftChild;
			}
			nptr->data.key = succ->data.key;
			strcpy(nptr->data.name, succ->data.name);
			nptr = succ;
		}
		curr = nptr->leftChild;
		if (!curr)
			curr = nptr->rightChild;
		if (!parent)
			root = curr;
		else if (parent->leftChild == nptr)
			parent->leftChild = curr;
		else
			parent->rightChild = curr;
		free(nptr);
		printf("�����Ǿ����ϴ�.\n");

	}

}

Ty_Node_Ptr search_BST(Ty_Node_Ptr cur, char sname[], Ty_Node_Ptr *par) {
	*par = NULL;
	while (cur) {
		if (strcmp(sname, cur->data.name) == 0)
			return cur;
		else if (strcmp(sname, cur->data.name) < 0) {
			*par = cur;
			cur = cur->leftChild;
		}
		else {
			*par = cur;
			cur = cur->rightChild;
		}
	}
	return NULL;
}


