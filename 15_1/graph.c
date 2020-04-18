#include <stdio.h>
#include <stdlib.h>

#define listEnd 999		//인접 리스트의 마지막을 나타낸다.
#define maxCost 999		//이어져있지 않은 노드들 사이의 비용
#define Max_vertex 12
#define FALSE 0
#define TRUE 1
typedef struct nodestruc *nodePointer;
typedef struct nodestruc {
	int no;		//정점번호
	float cost;	//이 간선의 비용가중치
	nodePointer link;	//다음 노드에 대한 포인터
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

nodePointer vertex[Max_vertex];	//정점의 정보들. vertex[i]는 i로 부터 연결된 노드들의 번호와 비용에 대한 리스트를 갖고있다. vertex[i]에는 no, cost 정보 없음
double cost[Max_vertex][Max_vertex];//두 정점간의 비용정보
int visited[Max_vertex];	//방문 여부. 1이면 방문, 0이면 방문안함표시
int pred[Max_vertex];		//경로
double dist[Max_vertex];	//특정 노드로부터 인덱스까지의 최소비용

void Read_and_make_graph();	//인접그래프의 내용이 저장된 텍스트파일을 읽어 노드리스트에 저장
void dfs(int StartNode);	//깊이우선탐색 방식으로 리스트를 탐색한다. 
int dfs_path(int s, int t); //깊이우선탐색 방식으로 두 정점 사이를 탐색한다.
void shortest_path(int s);	//dijkstra 알고리즘 구현
int choose();				//최저비용 간선 선택 알고리즘
int shortest_path_cost(int s, int d);	//dijkstra 알고리즘으로 두 정점 사이를 탐색한다.
void bfs(int v);			//너비우선탐색 방식으로 리스트를 탐색한다.

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

	for (i = 0; i < Max_vertex; i++){	//cost 초기화
		for (j = 0; j < Max_vertex; j++)
			cost[i][j] = maxCost;
	}
	for (i = 0; i < Max_vertex; i++) {	//cost값 구하기
		now = vertex[i]->link;
		while (now->no != listEnd) {
			j = now->no;
			cost[i][j] = now->cost;
			now = now->link;
		}
	}

	for (i = 0; i < Max_vertex; i++)	//visited 초기화
		visited[i] = 0;

	printf("dfs 시작점(-1이면 종료)> ");		//dfs
	scanf("%d", &startnode);
	while (startnode != -1) {
		dfs(startnode);
		printf("dfs 시작점(-1이면 종료)> ");
		scanf("%d", &startnode);
	}
	printf("dfs 실험을 종료함\n");

	printf("dfs 경로 찾기(-1 -1을 넣으면 종료)> ");	//dfs경로
	scanf("%d %d", &startnode, &endnode);
	while (startnode != -1 || endnode != -1) {
		dfs_path(startnode, endnode);
		printf("dfs 경로 찾기(-1 -1을 넣으면 종료)> ");
		scanf("%d %d", &startnode, &endnode);
	}
	printf("dfs 경로찾기 실험을 종료함\n");

	printf("shortest path 시작점(-1이면 종료)> ");	//shortest path
	scanf("%d", &startnode);
	while (startnode != -1) {
		shortest_path(startnode);
		printf("shortest path 시작점(-1이면 종료)> ");
		scanf("%d", &startnode);
	}
	printf("shortest path 알고리즘 실험을 종료함\n");

	printf("shortest path 경로 찾기(-1 -1을 넣으면 종료)> ");	//shortest path 경로
	scanf("%d %d", &startnode, &endnode);
	while (startnode != -1 || endnode != -1) {
		shortest_path_cost(startnode, endnode);
		printf("shortest path 경로 찾기(-1 -1을 넣으면 종료)> ");
		scanf("%d %d", &startnode, &endnode);
	}
	printf("shortest path 경로찾기 실험을 종료함\n");

	printf("bfs 시작점(-1이면 종료)> ");		//bfs
	scanf("%d", &startnode);
	while (startnode != -1) {
		bfs(startnode);
		printf("bfs 시작점(-1이면 종료)> ");
		scanf("%d", &startnode);
	}
	printf("bfs 실험을 종료함\n");

	return 0;
}

void Read_and_make_graph() {
	FILE *file;
	file = fopen("graphdata.txt", "r");
	int i=0, j=0, k=1, n, max=0;
	char *cp;
	char line[400], buf[20][50];
	nodePointer now;

	fscanf(file, "%d", &max);	//파일의 첫번째 단어인 총 vertex의 개수가 max vertex와 일치하는지 확인
	if (Max_vertex != max) {
		printf("잘못된 파일");
		return;
	}
	cp = fgets(line, 400, file);	//첫번째 줄을 그냥 읽어들인다.

	for (int i = 0; feof(file) == 0; i++) {
		vertex[i] = (nodePointer)malloc(sizeof(ty_node));	//vertex i에 메모리 할당
		cp = fgets(line, 400, file);						//텍스트 파일에서 한줄을 읽어 line배열에 넣는다.
		if (cp) {
			while (line[j] != '\n') {	//배열안의 값이 '\n'이면 반복문을 나온다.
				if (j == 0) {	//첫번째 숫자는 헤더 노드
					vertex[i]->link = (nodePointer)malloc(sizeof(ty_node));
					now = vertex[i]->link;
					j++;
				}
				else {
					n = 0;
					while (line[j] != ' ' && line[j] != '\t' && line[j] != '\n') {
						buf[i][n] = line[j]; //단어를 buf에 저장
						j++;
						n++;
					}
					buf[i][n] = '\0';
					switch (k) {
					case 1: {	//정점 번호가 들어갈 차례
						now->no = atoi(buf[i]);
						k = 2;	//차례를 넘긴다.
						break;
					}
					case 2: {	//간선의 비용이 들어갈 차례
						now->cost = atof(buf[i]);
						now->link = (nodePointer)malloc(sizeof(ty_node));
						now = now->link;	//비용을 넣고 나서 다음 노드로 간다
						k = 1;
						break;
					}
					}

				}
				if (line[j] == '\n') break; //'\n'이면 반복문을 나온다.
				j++;
				while (line[j] == ' ' || line[j] == '\t')
					j++;
				if (line[j] == '\n') break;
			}

		}
		now->no = listEnd;	//리스트에 마지막에 도달했음을 알려준다.
		j = 0;

	}
}

int get_unvisited_neghbor(int v) { //아직 방문하지 않은 v의 이웃노드를 찾아 그 번호를 반환
	nodePointer node = vertex[v]->link;
	while (node->no != listEnd) {
		if (visited[node->no] == 0) {
			totalCost = totalCost + node->cost;
			return node->no;
		}
		else
			node = node->link;
	}
	return -1;	//없으면 -1을 반환
}



void dfs(int StartNode){	//깊이우선탐색 방식으로 리스트를 탐색한다.
	int curr, next;

	pred[StartNode] = -1; //start노드의 부모는 없다는 표시
	visited[StartNode] = TRUE;	//시작노드를 방문했다고 표시
	printf("%d ", StartNode);
	push(StartNode);	//시작번호를 스택에 넣는다. (돌아올 경로를 스택에 쌓는다.)
	temp = StartNode;	//temp는 경로(pred배열)를 구할때 사용한다.
	while (1) {
		if (top < 0)
			break;
		curr = pop();	//다음 vertex에서 갈 수 있는 경로를 다 갔다온 다음 스택에 가장 최근에 들어간 곳으로 돌아가 다시 탐색
		while (1) {
			next = get_unvisited_neghbor(curr);	//다음 인접 노드를 구한다.
			if (next < 0)
				break;
			else {
				push(curr);	//다음 탐색할 노드가 있으므로 지금 번호를 스택에 넣는다.
				pred[next] = temp;	//pred[next]의 값은 마지막으로 탐색한 노드의 번호가 된다.
				temp = next;	//temp와
				curr = next;	//curr를 업데이트
				visited[curr] = TRUE;	//curr방문표시
				printf("-> %d ", curr);
			}
		}
	}
	printf("\n");
	totalCost = 0;	//총 비용 초기화
	for (int i = 0; i < Max_vertex; i++) //방문표시 초기화
		visited[i] = 0;
}

int dfs_path(int s, int t){	//깊이우선탐색 방식으로 두 정점 사이를 탐색한다.
	int curr = -1, next;

	pred[s] = -1; //start노드의 부모는 없다는 표시
	visited[s] = TRUE;	//시작노드를 방문했다고 표시
	printf("%d ", s);
	push(s);	//시작번호를 스택에 넣는다. (돌아올 경로를 스택에 쌓는다.)
	temp = s;	//temp는 경로(pred배열)를 구할때 사용한다.
	while (1) {
		if (top < 0 || curr == t)
			break;
		curr = pop();	//다음 vertex에서 갈 수 있는 경로를 다 갔다온 다음 스택에 가장 최근에 들어간 곳으로 돌아가 다시 탐색
		while (1) {
			next = get_unvisited_neghbor(curr);	//다음 인접 노드를 구한다.
			if (next < 0)
				break;
			else {
				push(curr);	//다음 탐색할 노드가 있으므로 지금 번호를 스택에 넣는다.
				pred[next] = temp;	//pred[next]의 값은 마지막으로 탐색한 노드의 번호가 된다.
				temp = next;	//temp와
				curr = next;	//curr를 업데이트
				visited[curr] = TRUE;	//curr방문표시
				printf("-> %d ", curr);
				if (curr == t)
					break;
			}
		}
	}
	printf("\n총 비용 : %.1f\n", totalCost);
	totalCost = 0;	//총 비용 초기화

	for (int i = 0; i < Max_vertex; i++) //방문표시 초기화
		visited[i] = 0;
}

void shortest_path(int s) {	//dijkstra 알고리즘
	int i, u, w;
	for (i = 0; i < Max_vertex; i++) {	//방문 여부, 거리정보 초기화
		visited[i] = FALSE;
		dist[i] = cost[s][i];
	}
	visited[s] = TRUE;
	printf("%d ", s);
	dist[s] = 0;
	for (i = 0; i < Max_vertex; i++) {
		u = choose();		//비용이 가장 작은것을 선택해서
		visited[u] = TRUE;	//방문하고
		if (u != -1)
			printf("-> %d ", u);
		for (w = 0; w < Max_vertex; w++) {	//u를 거쳐 w로 가는 것이 w로 바로가는것보다 작으면 disi[w]로 바꾼다
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
	printf("\n총 비용 : %.1f\n", totalCost);
	totalCost = 0;
	for (int i = 0; i < Max_vertex; i++) //방문표시 초기화
		visited[i] = 0;
}

int choose() {	//비용이 가장 작은것을 선택한다.
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

int shortest_path_cost(int s, int d) {	//dijkstra 알고리즘
	int i, u, w;
	for (i = 0; i < Max_vertex; i++) {	//방문 여부, 거리정보 초기화
		visited[i] = FALSE;
		dist[i] = cost[s][i];
	}
	visited[s] = TRUE;
	printf("%d ", s);
	dist[s] = 0;
	for (i = 0; i < Max_vertex; i++) {
		u = choose();		//비용이 가장 작은것을 선택해서
		visited[u] = TRUE;	//방문하고
		if (u != -1)
			printf("-> %d ", u);
		for (w = 0; w < Max_vertex; w++) {	//u를 거쳐 w로 가는 것이 w로 바로가는것보다 작으면 disi[w]로 바꾼다
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
	printf("\n비용 : %.1f\n", dist[d]);		//d까지의 비용을 출력한다.
	totalCost = 0;
	for (int i = 0; i < Max_vertex; i++)	//방문표시 초기화
		visited[i] = 0;
}

void bfs(int v) {	//너비우선탐색 방식으로 리스트를 탐색한다.
	nodePointer w;
	front = rear = NULL;
	printf("%d ", v);
	visited[v] = TRUE;
	addq(v);		//v를 큐에 넣고
	while (front) {
		v = deleteq();	//큐에서 뺀 숫자에 인접한 노드들을 탐색한다.
		w = vertex[v];
		w = w->link;
		while (w->no != listEnd) {
			if (!visited[w->no]) {
				printf("-> %d ", w->no);
				addq(w->no);		//방문한 노드를 큐에 넣는다.
				visited[w->no] = TRUE;
			}
			w = w->link;
		}
	}
	printf("\n");
	for (int i = 0; i < Max_vertex; i++)	//방문표시 초기화
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