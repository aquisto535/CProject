#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// 높이 반환
int height(Node* N) {
    if (N == NULL) return 0;
    return N->height;
}

// 최대값 반환
int max(int a, int b) 
{
    return (a > b) ? a : b;
}

// 노드 생성
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// 오른쪽 회전 (Right Rotation)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// 왼쪽 회전 (Left Rotation)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// 균형 계수 가져오기
int getBalance(Node* N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

// 삽입
Node* insert(Node* node, int key) {
    // 1. 일반적인 BST 삽입
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // 중복 키는 허용하지 않음
        return node;

    // 2. 높이 업데이트
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. 균형 계수 확인
    int balance = getBalance(node);

    // 4. 불균형 케이스 처리 (회전)

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// 전위 순회 (Preorder)
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node* root = NULL;

    /*
       10, 20, 30을 순서대로 넣으면
       일반 BST는 편향(Skewed) 트리가 되지만
       AVL 트리는 회전을 통해 균형을 맞춤:
            20
           /  \
         10    30
    */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    /* Constructed AVL Tree:
            30
           /  \
         20    40
        /  \     \
       10  25     50
    */

    printf("Preorder Traversal: ");
    preOrder(root); // 30 20 10 25 40 50

    return 0;
}