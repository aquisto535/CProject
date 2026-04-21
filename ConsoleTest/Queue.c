#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

// 초기화
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

// 비어있는지 확인
int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// 가득 찼는지 확인
int isFull(Queue* q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// 데이터 추가 (Enqueue)
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("큐가 가득 찼습니다 (Overflow).\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = value;
}

// 데이터 꺼내기 (Dequeue)
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("큐가 비어있습니다 (Underflow).\n");
        return -999;
    }
    q->front = (q->front + 1) % MAX_SIZE;
    return q->data[q->front];
}

// 큐 상태 출력
void printQueue(Queue* q) {
    printf("Queue: [ ");
    int i = q->front;
    while (i != q->rear) {
        i = (i + 1) % MAX_SIZE;
        printf("%d ", q->data[i]);
    }
    printf("]\n");
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    printQueue(&q); // 10 20 30 40

    enqueue(&q, 50); // 가득 참 테스트 (MAX_SIZE가 5면 4개까지만 저장 가능 - 원형 큐 특성상 1개 공백 유지)

    printf("Dequeue: %d\n", dequeue(&q)); // 10
    printQueue(&q);

    enqueue(&q, 50); // 공간이 생겨서 들어감
    printQueue(&q);

    return 0;
}