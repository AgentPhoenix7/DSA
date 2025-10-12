#include <stdio.h>
#include <stdlib.h>

// ---------- Node structure ----------
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// ---------- Queue structures for level order ----------
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// ---------- Queue functions ----------
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
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
    Node* node = temp->treeNode;
    free(temp);
    return node;
}

// ---------- BST functions ----------
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // Duplicate values ignored
    return root;
}

// ---------- Level Order (tree display) ----------
void levelOrder(Node* root) {
    if (root == NULL) {
        printf("(empty tree)\n");
        return;
    }

    Queue* q = createQueue();
    enqueue(q, root);

    printf("\nLevel Order Traversal of BST:\n");
    while (!isQueueEmpty(q)) {
        int levelCount = 0;
        QueueNode* temp = q->front;

        // Count nodes in this level
        while (temp) {
            levelCount++;
            temp = temp->next;
        }

        // Print all nodes of this level
        for (int i = 0; i < levelCount; i++) {
            Node* curr = dequeue(q);
            printf("%d ", curr->data);

            if (curr->left)
                enqueue(q, curr->left);
            if (curr->right)
                enqueue(q, curr->right);
        }
        printf("\n");
    }
}

// ---------- Print BST in descending order ----------
void printDescending(Node* root) {
    if (root == NULL) {
        return;
    }
    printDescending(root->right);
    printf("%d ", root->data);
    printDescending(root->left);
}

// ---------- Free the tree ----------
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ---------- Main ----------
int main(int argc, char* argv[]) {
    const char* filename;

    if (argc == 1) {
        filename = "p08.txt";  // Default file
        printf("No input file specified. Using default: %s\n", filename);
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

    printf("Reading elements from %s and inserting into BST...\n", filename);
    while (fscanf(fp, "%d", &value) == 1) {
        root = insert(root, value);
    }
    fclose(fp);

    if (root == NULL) {
        printf("No valid integers found in file.\n");
        return 0;
    }

    // Step 1: Show the tree structure
    levelOrder(root);

    // Step 2: Show descending order
    printf("\nNodes of BST in descending order:\n");
    printDescending(root);
    printf("\n");

    freeTree(root);
    return 0;
}