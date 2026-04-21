#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_DEGREE 3 // 최소 차수 t (노드는 최소 t-1개, 최대 2t-1개의 키를 가짐)

typedef struct BTreeNode {
    int* keys;              // 키 배열
    struct BTreeNode** C;   // 자식 포인터 배열
    int n;                  // 현재 키의 개수
    bool leaf;              // 리프 노드 여부
} BTreeNode;

// 노드 생성
BTreeNode* createNode(bool leaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->leaf = leaf;
    newNode->keys = (int*)malloc(sizeof(int) * (2 * MIN_DEGREE - 1));
    newNode->C = (BTreeNode**)malloc(sizeof(BTreeNode*) * (2 * MIN_DEGREE));
    newNode->n = 0;
    return newNode;
}

// 순회
void traverse(BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf) traverse(root->C[i]);
        printf(" %d", root->keys[i]);
    }
    if (!root->leaf) traverse(root->C[i]);
}

// 검색
BTreeNode* search(BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i]) i++;
    if (i < root->n && root->keys[i] == k) return root;
    if (root->leaf) return NULL;
    return search(root->C[i], k);
}

// 자식 분할 (꽉 찬 노드를 분할)
void splitChild(BTreeNode* x, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->leaf);
    z->n = MIN_DEGREE - 1;

    // y의 후반부 키들을 z로 이동
    for (int j = 0; j < MIN_DEGREE - 1; j++)
        z->keys[j] = y->keys[j + MIN_DEGREE];

    // 리프가 아니면 자식들도 이동
    if (!y->leaf) {
        for (int j = 0; j < MIN_DEGREE; j++)
            z->C[j] = y->C[j + MIN_DEGREE];
    }

    y->n = MIN_DEGREE - 1;

    // x의 자식 포인터 공간 확보
    for (int j = x->n; j >= i + 1; j--)
        x->C[j + 1] = x->C[j];

    x->C[i + 1] = z;

    // x의 키 공간 확보 및 y의 중간 키를 x로 이동
    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];

    x->keys[i] = y->keys[MIN_DEGREE - 1];
    x->n = x->n + 1;
}

// 꽉 차지 않은 노드에 삽입
void insertNonFull(BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    }
    else {
        while (i >= 0 && x->keys[i] > k) i--;
        i++;
        if (x->C[i]->n == 2 * MIN_DEGREE - 1) {
            splitChild(x, i, x->C[i]);
            if (x->keys[i] < k) i++;
        }
        insertNonFull(x->C[i], k);
    }
}

// 삽입 메인 함수
void insert(BTreeNode** root, int k) {
    if (*root == NULL) {
        *root = createNode(true);
        (*root)->keys[0] = k;
        (*root)->n = 1;
    }
    else {
        if ((*root)->n == 2 * MIN_DEGREE - 1) {
            BTreeNode* s = createNode(false);
            s->C[0] = *root;
            splitChild(s, 0, *root);
            int i = 0;
            if (s->keys[0] < k) i++;
            insertNonFull(s->C[i], k);
            *root = s;
        }
        else {
            insertNonFull(*root, k);
        }
    }
}

int main() {
    BTreeNode* root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);

    printf("B-Tree Traversal:");
    traverse(root);
    printf("\n");

    int k = 6;
    (search(root, k) != NULL) ? printf("%d Found\n", k) : printf("%d Not Found\n", k);

    k = 15;
    (search(root, k) != NULL) ? printf("%d Found\n", k) : printf("%d Not Found\n", k);

    return 0;
}