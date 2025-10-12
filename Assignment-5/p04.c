#include <stdio.h>
#include <stdlib.h>

// -------- Structure for heap node --------
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// -------- Queue node (for level order iterations) --------
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

// -------- Queue structure --------
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

// -------- Create a new heap node --------
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// -------- Swap values of two nodes --------
void swap(Node* a, Node* b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// -------- Maintain max-heap property (bottom-up) --------
void heapifyUp(Node* node) {
    while (node->parent != NULL && node->data > node->parent->data) {
        swap(node, node->parent);
        node = node->parent;
    }
}

// -------- Insert a new node to keep heap complete --------
Node* insertHeap(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }

    Queue* q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        Node* temp = dequeue(q);

        if (temp->left == NULL) {
            temp->left = newNode;
            newNode->parent = temp;
            break;
        } else {
            enqueue(q, temp->left);
        }

        if (temp->right == NULL) {
            temp->right = newNode;
            newNode->parent = temp;
            break;
        } else {
            enqueue(q, temp->right);
        }
    }

    heapifyUp(newNode);  // Restore max-heap property
    return root;
}

// -------- Print heap in level order --------
void printLevelOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    Queue* q = createQueue();
    enqueue(q, root);
    enqueue(q, NULL);  // Level delimiter

    printf("\nMax Heap (Level Order):\n");

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

// -------- Free entire tree --------
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// -------- Main function --------
int main(int argc, char* argv[]) {
    const char* filename;

    if (argc == 1) {
        filename = "p04.txt";  // Default file
        printf("Using default input file: %s\n", filename);
    } else if (argc == 2) {
        filename = argv[1];
    } else {
        printf("Usage: %s [input_file]\n", argv[0]);
        return 1;
    }

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    Node* root = NULL;
    int value;

    printf("Reading elements from %s and inserting into max-heap:\n", filename);

    while (fscanf(fp, "%d", &value) == 1) {
        root = insertHeap(root, value);
    }

    fclose(fp);

    if (root == NULL) {
        printf("No valid integer found in %s.\n", filename);
        return 0;
    }

    printLevelOrder(root);
    freeTree(root);
    return 0;
}