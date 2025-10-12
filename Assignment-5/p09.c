#include <stdio.h>
#include <stdlib.h>

// ---------- Structure for AVL Tree Node ----------
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// ---------- Function to get height of a node ----------
int height(Node* n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

// ---------- Utility: maximum of two integers ----------
int max(int a, int b) {
    return (a > b) ? a : b;
}

// ---------- Create a new node ----------
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;  // new node is initially at height 1
    return node;
}

// ---------- Right rotation ----------
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// ---------- Left rotation ----------
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// ---------- Get balance factor of node ----------
int getBalance(Node* n) {
    if (n == NULL) {
        return 0;
    }
    return height(n->left) - height(n->right);
}

// ---------- Insert into AVL tree ----------
Node* insert(Node* node, int data) {
    // 1. Normal BST insertion
    if (node == NULL) {
        return createNode(data);
    }

    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        return node; // no duplicates
    }
    // 2. Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Get the balance factor
    int balance = getBalance(node);

    // 4. If unbalanced, perform rotations

    // Case 1 - Left Left
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Case 2 - Right Right
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Case 3 - Left Right
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Case 4 - Right Left
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // return unchanged node pointer
    return node;
}

// ---------- Inorder traversal (sorted order) ----------
void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// ---------- Level order traversal ----------
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

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

void levelOrder(Node* root) {
    if (root == NULL) {
        printf("(empty tree)\n");
        return;
    }

    Queue* q = createQueue();
    enqueue(q, root);

    printf("\nLevel Order Traversal of AVL Tree:\n");
    while (!isQueueEmpty(q)) {
        int levelCount = 0;
        QueueNode* temp = q->front;
        while (temp) {
            levelCount++;
            temp = temp->next;
        }

        for (int i = 0; i < levelCount; i++) {
            Node* curr = dequeue(q);
            printf("%d ", curr->data);

            if (curr->left) {
                enqueue(q, curr->left);
            }
            if (curr->right) {
                enqueue(q, curr->right);
            }
        }
        printf("\n");
    }
}

// ---------- Free memory ----------
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ---------- Main function ----------
int main(int argc, char* argv[]) {
    const char* filename;

    if (argc == 1) {
        filename = "p09.txt";  // Default file
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

    printf("Reading elements from %s and inserting into AVL Tree...\n", filename);
    while (fscanf(fp, "%d", &value) == 1) {
        root = insert(root, value);
    }
    fclose(fp);

    if (root == NULL) {
        printf("No valid integers found in file.\n");
        return 0;
    }

    levelOrder(root);
    printf("\nInorder Traversal (sorted order): ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}