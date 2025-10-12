#include <stdio.h>
#include <stdlib.h>

// -------- Structure for tree node --------
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// -------- Structure for queue (used in level order printing) --------
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// -------- Queue functions --------
int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->treeNode = node;
    temp->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

Node* dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        return NULL;
    }
    QueueNode* temp = q->front;
    q->front = q->front->next;

    if (isQueueEmpty(q)) {
        q->rear = NULL;
    }
    Node* treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}

// -------- Tree creation and reconstruction --------
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Find index of a value in inorder[]
int findIndex(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1; // not found
}

// Build tree recursively from preorder and inorder arrays
Node* buildTree(int inorder[], int preorder[], int inStart, int inEnd, int* preIndex, int n) {
    if (inStart > inEnd || *preIndex >= n) {
        return NULL;
    }
    int curr = preorder[*preIndex];
    (*preIndex)++;

    Node *node = createNode(curr);

    if (inStart == inEnd) { // leaf node
        return node;
    }
    int pos = findIndex(inorder, inStart, inEnd, curr);
    if (pos == -1) {
        printf("Error: Inconsistent traversals!\n");
        exit(1);
    }

    node->left  = buildTree(inorder, preorder, inStart, pos - 1, preIndex, n);
    node->right = buildTree(inorder, preorder, pos + 1, inEnd, preIndex, n);

    return node;
}

// -------- Level Order Traversal --------
void printLevelOrder(Node *root) {
    if (root == NULL) {
        return;
    }

    Queue* q = createQueue();
    enqueue(q, root);
    enqueue(q, NULL);  // Level delimiter

    printf("\nLevel order traversal of the reconstructed tree:\n");

    while (!isQueueEmpty(q)) {
        Node* temp = dequeue(q);

        if (temp == NULL) {
            printf("\n");
            if (!isQueueEmpty(q)) {
                enqueue(q, NULL);  // Add new level delimiter
            }
        } else {
            printf("%d ", temp->data);
            if (temp->left) {
                enqueue(q, temp->left);
            }
            if (temp->right) {
                enqueue(q, temp->right);
            }
        }
    }
    printf("\n");
}

// -------- Main Function --------
int main() {
    int n;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Tree is empty.\n");
        return 0;
    }

    int* inorder = (int*)malloc(n * sizeof(int));
    int* preorder = (int*)malloc(n * sizeof(int));
    if (!inorder || !preorder) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("\nEnter preorder traversal (%d elements):\n", n);
    for (int i = 0; i < n; i++) {
        printf("\tElement %d: ", i + 1);
        scanf("%d", &preorder[i]);
    }
    printf("\nEnter inorder traversal (%d elements):\n", n);
    for (int i = 0; i < n; i++) {
        printf("\tElement %d: ", i + 1);
        scanf("%d", &inorder[i]);
    }
    int preIndex = 0;
    Node* root = buildTree(inorder, preorder, 0, n - 1, &preIndex, n);

    printLevelOrder(root);

    free(inorder);
    free(preorder);
    return 0;
}