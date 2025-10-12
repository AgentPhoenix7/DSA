#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------- Data Structures --------
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// -------- Queue Functions --------
int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue*));
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

// -------- Tree Functions --------
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Level order insertion to keep tree complete
Node* insertLevelOrder(Node* root, int data) {
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
            break;
        } else {
            enqueue(q, temp->left);
        }

        if (temp->right == NULL) {
            temp->right = newNode;
            break;
        } else {
            enqueue(q, temp->right);
        }
    }
    return root;
}

// -------- Traversals --------
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void levelorder(Node* root) {
    if (!root) {
        return;
    }
    Queue* q = createQueue();
    enqueue(q, root);
    while (!isQueueEmpty(q)) {
        Node* temp = dequeue(q);
        printf("%d ", temp->data);
        if (temp->left) {
            enqueue(q, temp->left);
        }
        if (temp->right) {
            enqueue(q, temp->right);
        }
    }
}

// -------- Build Tree from File --------
Node* buildTreeFromFile(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }
    Node* root = NULL;
    int value;
    while (fscanf(fp, "%d", &value) == 1) {
        root = insertLevelOrder(root, value);
    }
    fclose(fp);
    return root;
}

// -------- Menus --------
void traversalMenu(Node *root);

void inputMenu() {
    char filename[100];
    int choice;

    while (1) {
        printf("\n===== INPUT MENU =====\n");
        printf("1. Use default file (p02.txt)\n");
        printf("2. Enter custom file name\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        const char* filenameToUse = "p02.txt";

        switch (choice) {
            case 1:
                filenameToUse = "p02.txt";
                break;

            case 2:
                printf("Enter file name: ");
                scanf("%s", filename);
                filenameToUse = filename;
                break;

            case 3:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
                continue;
        }

        Node *root = buildTreeFromFile(filenameToUse);
        if (!root) {
            printf("Failed to build tree. Try again.\n");
            continue;
        }

        traversalMenu(root);
    }
}

void traversalMenu(Node *root) {
    int choice;
    while (1) {
        printf("\n===== TRAVERSAL MENU =====\n");
        printf("1. Inorder traversal\n");
        printf("2. Preorder traversal\n");
        printf("3. Postorder traversal\n");
        printf("4. Level order traversal\n");
        printf("5. New input file\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 2:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 3:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 4:
                printf("Level order: ");
                levelorder(root);
                printf("\n");
                break;

            case 5:
                inputMenu();  // Go back to input menu
                return;

            case 6:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// -------- Main --------
int main() {
    inputMenu();
    return 0;
}