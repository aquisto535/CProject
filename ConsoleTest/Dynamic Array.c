#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4

typedef struct {
    int* data;
    int size;
    int capacity;
} DynamicArray;

// 초기화
void initArray(DynamicArray* arr) {
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->data = (int*)malloc(arr->capacity * sizeof(int));
}

// 요소 추가 (크기가 꽉 차면 2배로 확장)
void pushBack(DynamicArray* arr, int value) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(int));
        printf("배열 크기 확장: %d -> %d\n", arr->capacity / 2, arr->capacity);
    }
    arr->data[arr->size++] = value;
}

// 인덱스로 요소 가져오기
int get(DynamicArray* arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf("인덱스 오류\n");
        return -1;
    }
    return arr->data[index];
}

// 요소 수정
void set(DynamicArray* arr, int index, int value) {
    if (index < 0 || index >= arr->size) {
        printf("인덱스 오류\n");
        return;
    }
    arr->data[index] = value;
}

// 메모리 해제
void freeArray(DynamicArray* arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

// 요소 출력
void printArray(DynamicArray* arr) {
    printf("배열 내용: [ ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("] (Size: %d, Capacity: %d)\n", arr->size, arr->capacity);
}

int main() {
    DynamicArray arr;
    initArray(&arr);

    pushBack(&arr, 10);
    pushBack(&arr, 20);
    pushBack(&arr, 30);
    printArray(&arr);

    pushBack(&arr, 40);
    pushBack(&arr, 50); // 여기서 용량 확장 발생
    printArray(&arr);

    printf("Index 2의 값: %d\n", get(&arr, 2));

    freeArray(&arr);
    return 0;
}