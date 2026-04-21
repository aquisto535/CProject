#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int heap[MAX_SIZE];
    int count;
} PriorityQueue;

// 초기화
void initPQ(PriorityQueue* pq) {
    pq->count = 0;
}

// 삽입 (Up-Heapify)
void push(PriorityQueue* pq, int data) {
    if (pq->count >= MAX_SIZE) {
        printf("우선순위 큐가 가득 찼습니다.\n");
        return;
    }

    pq->heap[pq->count] = data;
    int now = pq->count;
    int parent = (now - 1) / 2;

    // 부모보다 크면 위로 올림
    while (now > 0 && pq->heap[now] > pq->heap[parent]) {
        int temp = pq->heap[now];
        pq->heap[now] = pq->heap[parent];
        pq->heap[parent] = temp;

        now = parent;
        parent = (now - 1) / 2;
    }

    pq->count++;
}

// 삭제 (Max 값 반환, Down-Heapify)
int pop(PriorityQueue* pq) {
    if (pq->count <= 0) {
        printf("우선순위 큐가 비어있습니다.\n");
        return -999;
    }

    int res = pq->heap[0];
    pq->count--;

    // 마지막 노드를 루트로 가져옴
    pq->heap[0] = pq->heap[pq->count];
    int now = 0, left = 1, right = 2;
    int target = now;

    // 자식들과 비교하며 아래로 내림
    while (left < pq->count) {
        if (pq->heap[target] < pq->heap[left]) target = left;
        if (right < pq->count && pq->heap[target] < pq->heap[right]) target = right;

        if (target == now) break; // 더 이상 내려갈 필요 없음

        int temp = pq->heap[now];
        pq->heap[now] = pq->heap[target];
        pq->heap[target] = temp;

        now = target;
        left = now * 2 + 1;
        right = now * 2 + 2;
    }

    return res;
}

int main() {
    PriorityQueue pq;
    initPQ(&pq);

    push(&pq, 10);
    push(&pq, 50);
    push(&pq, 30);
    push(&pq, 20);

    printf("Pop Max: %d\n", pop(&pq)); // 50
    printf("Pop Max: %d\n", pop(&pq)); // 30
    printf("Pop Max: %d\n", pop(&pq)); // 20
    printf("Pop Max: %d\n", pop(&pq)); // 10

    return 0;
}