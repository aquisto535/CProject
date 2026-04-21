#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

// 인접 리스트 노드
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// 그래프 구조체
typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX_VERTICES];
    int visited[MAX_VERTICES];
} Graph;

// 노드 생성
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// 그래프 초기화
void initGraph(Graph* g, int vertices) {
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        g->adjLists[i] = NULL;
        g->visited[i] = 0;
    }
}

// 간선 추가 (무방향 그래프)
void addEdge(Graph* g, int src, int dest) {
    // src -> dest
    Node* newNode = createNode(dest);
    newNode->next = g->adjLists[src];
    g->adjLists[src] = newNode;

    // dest -> src
    newNode = createNode(src);
    newNode->next = g->adjLists[dest];
    g->adjLists[dest] = newNode;
}

// 방문 배열 초기화
void resetVisited(Graph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        g->visited[i] = 0;
    }
}

// DFS (재귀)
void DFS(Graph* g, int vertex) {
    Node* adjList = g->adjLists[vertex];
    Node* temp = adjList;

    g->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->dest;
        if (g->visited[connectedVertex] == 0) {
            DFS(g, connectedVertex);
        }
        temp = temp->next;
    }
}

// 큐 자료구조 for BFS
int queue[MAX_VERTICES];
int front = 0, rear = 0;

void enqueue(int v) {
    queue[rear++] = v;
}

int dequeue() {
    return queue[front++];
}

int isQueueEmpty() {
    return front == rear;
}

// BFS
void BFS(Graph* g, int startVertex) {
    resetVisited(g); // BFS를 위해 방문 기록 초기화

    // 큐 초기화
    front = 0; rear = 0;

    g->visited[startVertex] = 1;
    enqueue(startVertex);

    while (!isQueueEmpty()) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        Node* temp = g->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->dest;
            if (g->visited[adjVertex] == 0) {
                g->visited[adjVertex] = 1;
                enqueue(adjVertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    Graph g;
    initGraph(&g, 6);

    /*
       0 -- 1 -- 3
       |    |
       2 -- 4 -- 5
    */
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 1, 4);
    addEdge(&g, 2, 4);
    addEdge(&g, 4, 5);

    printf("DFS 탐색 (시작 0): ");
    resetVisited(&g);
    DFS(&g, 0); // 0 2 4 5 1 3 (순서는 연결 순서에 따라 다를 수 있음)
    printf("\n");

    printf("BFS 탐색 (시작 0): ");
    BFS(&g, 0); // 0 1 2 3 4 5
    printf("\n");

    return 0;
}