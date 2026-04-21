#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 초기화
void initStack(Stack* s) {
    s->top = -1;
    memset(s->data, 0, sizeof(s->data));
}

// 빈 스택 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 가득 찼는지 확인
int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

// 데이터 추가 (Push)
void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("스택 오버플로우: 더 이상 추가할 수 없습니다.\n");
        return;
    }
    s->data[++(s->top)] = value;
}

// 데이터 꺼내기 (Pop)
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("스택 언더플로우: 비어있습니다.\n");
        return -999; // 에러 값
    }

    int ret = s->data[s->top];
    s->data[s->top] = 0;
    s->top--;

    return ret;
}

// 맨 위 데이터 확인 (Peek)
int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("스택이 비어있습니다.\n");
        return -999;
    }
    return s->data[s->top];
}

int main() {
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Top: %d\n", peek(&s)); // 30

    printf("Pop: %d\n", pop(&s)); // 30
    printf("Pop: %d\n", pop(&s)); // 20

    printf("Top after pops: %d\n", peek(&s)); // 10

    return 0;
}