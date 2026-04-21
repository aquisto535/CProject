#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Deque;

// 초기화
void initDeque(Deque* dq) {
    dq->front = NULL;
    dq->rear = NULL;
}

// 빈 덱 확인
int isEmpty(Deque* dq) {
    return dq->front == NULL;
}

// 앞쪽 추가
void pushFront(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = dq->front;

    if (isEmpty(dq)) {
        dq->rear = newNode;
    }
    else {
        dq->front->prev = newNode;
    }
    dq->front = newNode;
}

// 뒤쪽 추가
void pushRear(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = dq->rear;

    if (isEmpty(dq)) {
        dq->front = newNode;
    }
    else {
        dq->rear->next = newNode;
    }
    dq->rear = newNode;
}

// 앞쪽 삭제
int popFront(Deque* dq) {
    if (isEmpty(dq)) {
        printf("덱이 비어있습니다.\n");
        return -999;
    }

    Node* temp = dq->front;
    int data = temp->data;

    dq->front = dq->front->next;
    if (dq->front == NULL) {
        dq->rear = NULL;
    }
    else {
        dq->front->prev = NULL;
    }
    free(temp);
    return data;
}

// 뒤쪽 삭제
int popRear(Deque* dq) {
    if (isEmpty(dq)) {
        printf("덱이 비어있습니다.\n");
        return -999;
    }

    Node* temp = dq->rear;
    int data = temp->data;

    dq->rear = dq->rear->prev;
    if (dq->rear == NULL) {
        dq->front = NULL;
    }
    else {
        dq->rear->next = NULL;
    }
    free(temp);
    return data;
}

// 출력
void printDeque(Deque* dq) {
    Node* curr = dq->front;
    printf("Deque: [ ");
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]\n");
}

int main() {
    Deque dq;
    initDeque(&dq);

    pushFront(&dq, 10); // [10]
    pushRear(&dq, 20);  // [10 20]
    pushFront(&dq, 5);  // [5 10 20]
    pushRear(&dq, 30);  // [5 10 20 30]
    printDeque(&dq);

    printf("Pop Front: %d\n", popFront(&dq)); // 5
    printf("Pop Rear: %d\n", popRear(&dq));   // 30
    printDeque(&dq); // [10 20]

    return 0;
}