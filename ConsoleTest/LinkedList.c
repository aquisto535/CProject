#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

// 초기화
void initList(LinkedList* list) {
    list->head = NULL;
}

// 노드 추가 (마지막에 추가)
void append(LinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        return;
    }

    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// 노드 추가 (앞에 추가)
void prepend(LinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
}

// 노드 삭제 (특정 값)
void deleteNode(LinkedList* list, int value) {
    if (list->head == NULL) return;

    Node* current = list->head;
    Node* prev = NULL;

    // 헤드 삭제 경우
    if (current->data == value) {
        list->head = current->next;
        free(current);
        return;
    }

    // 중간/끝 삭제 검색
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }

    // 값을 찾지 못한 경우
    if (current == NULL) {
        printf("값 %d을(를) 찾을 수 없습니다.\n", value);
        return;
    }

    prev->next = current->next;
    free(current);
}

// 리스트 출력
void printList(LinkedList* list) {
    Node* current = list->head;
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 메모리 전체 해제
void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

int main() {
    LinkedList list;
    initList(&list);

    append(&list, 10);
    append(&list, 20);
    append(&list, 30);
    prepend(&list, 5);
    printList(&list); // 5 -> 10 -> 20 -> 30 -> NULL

    deleteNode(&list, 20);
    printList(&list); // 5 -> 10 -> 30 -> NULL

    deleteNode(&list, 5);
    printList(&list); // 10 -> 30 -> NULL

    freeList(&list);
    return 0;
}