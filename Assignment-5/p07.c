#include <stdio.h>
#include <stdlib.h>

// ---------- Node structure ----------
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// ---------- Queue for Level Order ----------
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
    if (isQueueEmpty(q)) return NULL;
    QueueNode* temp = q->front;
    q->front = q->front->next;
    if (isQueueEmpty(q)) {
        q->rear = NULL;
    }
    Node* node = temp->treeNode;
    free(temp);
    return node;
}

// ---------- Create a new node ----------
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

// ---------- Insert into BST ----------
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // Duplicate values are ignored
    return root;
}

// ---------- Level Order Traversal ----------
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

        // Count how many nodes are in the current level
        QueueNode* tempNode = q->front;
        while (tempNode) {
            levelCount++;
            tempNode = tempNode->next;
        }

        // Print all nodes of this level
        while (levelCount > 0) {
            Node* temp = dequeue(q);
            printf("%d ", temp->data);

            if (temp->left) {
                enqueue(q, temp->left);
            }
            if (temp->right) {
                enqueue(q, temp->right);
            }
            levelCount--;
        }
        printf("\n"); // Move to next level
    }
}

// ---------- Inorder, Preorder, Postorder ----------
void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
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
        filename = "p07.txt";  // Default file
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

    // -------- Display traversals --------
    levelOrder(root);

    printf("\nInorder traversal  (sorted order): ");
    inorder(root);
    printf("\nPreorder traversal (root-left-right): ");
    preorder(root);
    printf("\nPostorder traversal (left-right-root): ");
    postorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}