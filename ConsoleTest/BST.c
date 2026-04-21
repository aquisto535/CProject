#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// 노드 생성
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 삽입 (재귀)
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // data == root->data인 경우(중복)는 무시하거나 처리 정책에 따름
    return root;
}

// 탐색 (재귀)
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    }
    return search(root->right, data);
}

// 최소값 노드 찾기 (삭제 시 후계자 찾기용)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// 삭제
Node* deleteNode(Node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // 자식이 하나거나 없는 경우
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // 자식이 둘인 경우: 오른쪽 서브트리의 최소값(Inorder Successor)을 가져옴
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// 중위 순회 (Inorder Traversal: 정렬된 순서로 출력)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder Traversal: ");
    inorder(root); // 20 30 40 50 60 70 80
    printf("\n");

    printf("Search 40: %s\n", search(root, 40) ? "Found" : "Not Found");
    printf("Search 90: %s\n", search(root, 90) ? "Found" : "Not Found");

    printf("Delete 20\n");
    root = deleteNode(root, 20);
    inorder(root);
    printf("\n");

    printf("Delete 30 (자식 1개)\n");
    root = deleteNode(root, 30);
    inorder(root);
    printf("\n");

    printf("Delete 50 (자식 2개 - 루트)\n");
    root = deleteNode(root, 50);
    inorder(root);
    printf("\n");

    return 0;
}