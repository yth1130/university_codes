#include <stdio.h>
#include <stdlib.h>

#define listEnd 999		//���� ����Ʈ�� �������� ��Ÿ����.
#define maxCost 999		//�̾������� ���� ���� ������ ���
#define Max_vertex 12
#define FALSE 0
#define TRUE 1
typedef struct nodestruc *nodePointer;
typedef struct nodestruc {
	int no;		//������ȣ
	float cost;	//�� ������ ��밡��ġ
	nodePointer link;	//���� ��忡 ���� ������
}ty_node;

int top = -1, temp;
int stack[Max_vertex];
float totalCost = 0;

typedef struct queue *queuePointer;
typedef struct queue{
	int data;
	queuePointer link;
} queue;
queuePointer front, rear;

nodePointer vertex[Max_vertex];	//������ ������. vertex[i]�� i�� ���� ����� ������ ��ȣ�� ��뿡 ���� ����Ʈ�� �����ִ�. vertex[i]���� no, cost ���� ����
double cost[Max_vertex][Max_vertex];//�� �������� �������
int visited[Max_vertex];	//�湮 ����. 1�̸� �湮, 0�̸� �湮����ǥ��
int pred[Max_vertex];		//���
double dist[Max_vertex];	//Ư�� ���κ��� �ε��������� �ּҺ��

void Read_and_make_graph();	//�����׷����� ������ ����� �ؽ�Ʈ������ �о� ��帮��Ʈ�� ����
void dfs(int StartNode);	//���̿켱Ž�� ������� ����Ʈ�� Ž���Ѵ�. 
int dfs_path(int s, int t); //���̿켱Ž�� ������� �� ���� ���̸� Ž���Ѵ�.
void shortest_path(int s);	//dijkstra �˰��� ����
int choose();				//������� ���� ���� �˰���
int shortest_path_cost(int s, int d);	//dijkstra �˰������� �� ���� ���̸� Ž���Ѵ�.
void bfs(int v);			//�ʺ�켱Ž�� ������� ����Ʈ�� Ž���Ѵ�.

int get_unvisited_neghbor(int v);

void push(int item);
int pop();
void stackFull();
int stackEmpty();
void addq(int item);
int deleteq();

int main() {
	int i, j, startnode, endnode;
	nodePointer now;
	Read_and_make_graph();

	for (i = 0; i < Max_vertex; i++){	//cost �ʱ�ȭ
		for (j = 0; j < Max_vertex; j++)
			cost[i][j] = maxCost;
	}
	for (i = 0; i < Max_vertex; i++) {	//cost�� ���ϱ�
		now = vertex[i]->link;
		while (now->no != listEnd) {
			j = now->no;
			cost[i][j] = now->cost;
			now = now->link;
		}
	}

	for (i = 0; i < Max_vertex; i++)	//visited �ʱ�ȭ
		visited[i] = 0;

	printf("dfs ������(-1�̸� ����)> ");		//dfs
	scanf("%d", &startnode);
	while (startnode != -1) {
		dfs(startnode);
		printf("dfs ������(-1�̸� ����)> ");
		scanf("%d", &startnode);
	}
	printf("dfs ������ ������\n");

	printf("dfs ��� ã��(-1 -1�� ������ ����)> ");	//dfs���
	scanf("%d %d", &startnode, &endnode);
	while (startnode != -1 || endnode != -1) {
		dfs_path(startnode, endnode);
		printf("dfs ��� ã��(-1 -1�� ������ ����)> ");
		scanf("%d %d", &startnode, &endnode);
	}
	printf("dfs ���ã�� ������ ������\n");

	printf("shortest path ������(-1�̸� ����)> ");	//shortest path
	scanf("%d", &startnode);
	while (startnode != -1) {
		shortest_path(startnode);
		printf("shortest path ������(-1�̸� ����)> ");
		scanf("%d", &startnode);
	}
	printf("shortest path �˰��� ������ ������\n");

	printf("shortest path ��� ã��(-1 -1�� ������ ����)> ");	//shortest path ���
	scanf("%d %d", &startnode, &endnode);
	while (startnode != -1 || endnode != -1) {
		shortest_path_cost(startnode, endnode);
		printf("shortest path ��� ã��(-1 -1�� ������ ����)> ");
		scanf("%d %d", &startnode, &endnode);
	}
	printf("shortest path ���ã�� ������ ������\n");

	printf("bfs ������(-1�̸� ����)> ");		//bfs
	scanf("%d", &startnode);
	while (startnode != -1) {
		bfs(startnode);
		printf("bfs ������(-1�̸� ����)> ");
		scanf("%d", &startnode);
	}
	printf("bfs ������ ������\n");

	return 0;
}

void Read_and_make_graph() {
	FILE *file;
	file = fopen("graphdata.txt", "r");
	int i=0, j=0, k=1, n, max=0;
	char *cp;
	char line[400], buf[20][50];
	nodePointer now;

	fscanf(file, "%d", &max);	//������ ù��° �ܾ��� �� vertex�� ������ max vertex�� ��ġ�ϴ��� Ȯ��
	if (Max_vertex != max) {
		printf("�߸��� ����");
		return;
	}
	cp = fgets(line, 400, file);	//ù��° ���� �׳� �о���δ�.

	for (int i = 0; feof(file) == 0; i++) {
		vertex[i] = (nodePointer)malloc(sizeof(ty_node));	//vertex i�� �޸� �Ҵ�
		cp = fgets(line, 400, file);						//�ؽ�Ʈ ���Ͽ��� ������ �о� line�迭�� �ִ´�.
		if (cp) {
			while (line[j] != '\n') {	//�迭���� ���� '\n'�̸� �ݺ����� ���´�.
				if (j == 0) {	//ù��° ���ڴ� ��� ���
					vertex[i]->link = (nodePointer)malloc(sizeof(ty_node));
					now = vertex[i]->link;
					j++;
				}
				else {
					n = 0;
					while (line[j] != ' ' && line[j] != '\t' && line[j] != '\n') {
						buf[i][n] = line[j]; //�ܾ buf�� ����
						j++;
						n++;
					}
					buf[i][n] = '\0';
					switch (k) {
					case 1: {	//���� ��ȣ�� �� ����
						now->no = atoi(buf[i]);
						k = 2;	//���ʸ� �ѱ��.
						break;
					}
					case 2: {	//������ ����� �� ����
						now->cost = atof(buf[i]);
						now->link = (nodePointer)malloc(sizeof(ty_node));
						now = now->link;	//����� �ְ� ���� ���� ���� ����
						k = 1;
						break;
					}
					}

				}
				if (line[j] == '\n') break; //'\n'�̸� �ݺ����� ���´�.
				j++;
				while (line[j] == ' ' || line[j] == '\t')
					j++;
				if (line[j] == '\n') break;
			}

		}
		now->no = listEnd;	//����Ʈ�� �������� ���������� �˷��ش�.
		j = 0;

	}
}

int get_unvisited_neghbor(int v) { //���� �湮���� ���� v�� �̿���带 ã�� �� ��ȣ�� ��ȯ
	nodePointer node = vertex[v]->link;
	while (node->no != listEnd) {
		if (visited[node->no] == 0) {
			totalCost = totalCost + node->cost;
			return node->no;
		}
		else
			node = node->link;
	}
	return -1;	//������ -1�� ��ȯ
}



void dfs(int StartNode){	//���̿켱Ž�� ������� ����Ʈ�� Ž���Ѵ�.
	int curr, next;

	pred[StartNode] = -1; //start����� �θ�� ���ٴ� ǥ��
	visited[StartNode] = TRUE;	//���۳�带 �湮�ߴٰ� ǥ��
	printf("%d ", StartNode);
	push(StartNode);	//���۹�ȣ�� ���ÿ� �ִ´�. (���ƿ� ��θ� ���ÿ� �״´�.)
	temp = StartNode;	//temp�� ���(pred�迭)�� ���Ҷ� ����Ѵ�.
	while (1) {
		if (top < 0)
			break;
		curr = pop();	//���� vertex���� �� �� �ִ� ��θ� �� ���ٿ� ���� ���ÿ� ���� �ֱٿ� �� ������ ���ư� �ٽ� Ž��
		while (1) {
			next = get_unvisited_neghbor(curr);	//���� ���� ��带 ���Ѵ�.
			if (next < 0)
				break;
			else {
				push(curr);	//���� Ž���� ��尡 �����Ƿ� ���� ��ȣ�� ���ÿ� �ִ´�.
				pred[next] = temp;	//pred[next]�� ���� ���������� Ž���� ����� ��ȣ�� �ȴ�.
				temp = next;	//temp��
				curr = next;	//curr�� ������Ʈ
				visited[curr] = TRUE;	//curr�湮ǥ��
				printf("-> %d ", curr);
			}
		}
	}
	printf("\n");
	totalCost = 0;	//�� ��� �ʱ�ȭ
	for (int i = 0; i < Max_vertex; i++) //�湮ǥ�� �ʱ�ȭ
		visited[i] = 0;
}

int dfs_path(int s, int t){	//���̿켱Ž�� ������� �� ���� ���̸� Ž���Ѵ�.
	int curr = -1, next;

	pred[s] = -1; //start����� �θ�� ���ٴ� ǥ��
	visited[s] = TRUE;	//���۳�带 �湮�ߴٰ� ǥ��
	printf("%d ", s);
	push(s);	//���۹�ȣ�� ���ÿ� �ִ´�. (���ƿ� ��θ� ���ÿ� �״´�.)
	temp = s;	//temp�� ���(pred�迭)�� ���Ҷ� ����Ѵ�.
	while (1) {
		if (top < 0 || curr == t)
			break;
		curr = pop();	//���� vertex���� �� �� �ִ� ��θ� �� ���ٿ� ���� ���ÿ� ���� �ֱٿ� �� ������ ���ư� �ٽ� Ž��
		while (1) {
			next = get_unvisited_neghbor(curr);	//���� ���� ��带 ���Ѵ�.
			if (next < 0)
				break;
			else {
				push(curr);	//���� Ž���� ��尡 �����Ƿ� ���� ��ȣ�� ���ÿ� �ִ´�.
				pred[next] = temp;	//pred[next]�� ���� ���������� Ž���� ����� ��ȣ�� �ȴ�.
				temp = next;	//temp��
				curr = next;	//curr�� ������Ʈ
				visited[curr] = TRUE;	//curr�湮ǥ��
				printf("-> %d ", curr);
				if (curr == t)
					break;
			}
		}
	}
	printf("\n�� ��� : %.1f\n", totalCost);
	totalCost = 0;	//�� ��� �ʱ�ȭ

	for (int i = 0; i < Max_vertex; i++) //�湮ǥ�� �ʱ�ȭ
		visited[i] = 0;
}

void shortest_path(int s) {	//dijkstra �˰���
	int i, u, w;
	for (i = 0; i < Max_vertex; i++) {	//�湮 ����, �Ÿ����� �ʱ�ȭ
		visited[i] = FALSE;
		dist[i] = cost[s][i];
	}
	visited[s] = TRUE;
	printf("%d ", s);
	dist[s] = 0;
	for (i = 0; i < Max_vertex; i++) {
		u = choose();		//����� ���� �������� �����ؼ�
		visited[u] = TRUE;	//�湮�ϰ�
		if (u != -1)
			printf("-> %d ", u);
		for (w = 0; w < Max_vertex; w++) {	//u�� ���� w�� ���� ���� w�� �ٷΰ��°ͺ��� ������ disi[w]�� �ٲ۴�
			if (!visited[w]) {
				if (dist[u] + cost[u][w] < dist[w])
					dist[w] = dist[u] + cost[u][w];
			}
		}
	}
	for (i = 0; i < Max_vertex; i++) {
		if (dist[i] != maxCost)
			totalCost = totalCost + dist[i];
	}
	printf("\n�� ��� : %.1f\n", totalCost);
	totalCost = 0;
	for (int i = 0; i < Max_vertex; i++) //�湮ǥ�� �ʱ�ȭ
		visited[i] = 0;
}

int choose() {	//����� ���� �������� �����Ѵ�.
	int i, min, minpos;
	min = maxCost;
	minpos = -1;
	for (i = 0; i < Max_vertex; i++) {
		if (dist[i] < min && !visited[i]) {
			min = dist[i];
			minpos = i;
		}
	}
	return minpos;
}

int shortest_path_cost(int s, int d) {	//dijkstra �˰���
	int i, u, w;
	for (i = 0; i < Max_vertex; i++) {	//�湮 ����, �Ÿ����� �ʱ�ȭ
		visited[i] = FALSE;
		dist[i] = cost[s][i];
	}
	visited[s] = TRUE;
	printf("%d ", s);
	dist[s] = 0;
	for (i = 0; i < Max_vertex; i++) {
		u = choose();		//����� ���� �������� �����ؼ�
		visited[u] = TRUE;	//�湮�ϰ�
		if (u != -1)
			printf("-> %d ", u);
		for (w = 0; w < Max_vertex; w++) {	//u�� ���� w�� ���� ���� w�� �ٷΰ��°ͺ��� ������ disi[w]�� �ٲ۴�
			if (!visited[w]) {
				if (dist[u] + cost[u][w] < dist[w])
					dist[w] = dist[u] + cost[u][w];
			}
		}
		if (u == d)
			break;
	}
	for (i = 0; i < Max_vertex; i++) {
		if (dist[i] != maxCost)
			totalCost = totalCost + dist[i];
	}
	printf("\n��� : %.1f\n", dist[d]);		//d������ ����� ����Ѵ�.
	totalCost = 0;
	for (int i = 0; i < Max_vertex; i++)	//�湮ǥ�� �ʱ�ȭ
		visited[i] = 0;
}

void bfs(int v) {	//�ʺ�켱Ž�� ������� ����Ʈ�� Ž���Ѵ�.
	nodePointer w;
	front = rear = NULL;
	printf("%d ", v);
	visited[v] = TRUE;
	addq(v);		//v�� ť�� �ְ�
	while (front) {
		v = deleteq();	//ť���� �� ���ڿ� ������ ������ Ž���Ѵ�.
		w = vertex[v];
		w = w->link;
		while (w->no != listEnd) {
			if (!visited[w->no]) {
				printf("-> %d ", w->no);
				addq(w->no);		//�湮�� ��带 ť�� �ִ´�.
				visited[w->no] = TRUE;
			}
			w = w->link;
		}
	}
	printf("\n");
	for (int i = 0; i < Max_vertex; i++)	//�湮ǥ�� �ʱ�ȭ
		visited[i] = 0;
}

void push(int item) {
	if (top >= Max_vertex - 1)
		stackFull();
	stack[++top] = item;
}


int pop() {
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}

void stackFull() {
	printf("Stack is full, cannot add element");
	exit(EXIT_FAILURE);
}

int stackEmpty() {
	printf("Stack is empty");
	return -1;
}

void addq(int item) {
	queuePointer tem;

	tem = malloc(sizeof(*tem));
	tem->data = item;
	tem->link = NULL;
	if (front)
		rear->link = tem;
	else
		front = tem;
	rear = tem;
}

int deleteq() {
	queuePointer tem = front;
	int item;
	if (!tem)
		return -1;
	item = tem->data;
	front = tem->link;
	free(tem);
	return item;
}