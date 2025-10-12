#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- Node structure ----------
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// ---------- Queue for level-order ----------
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// ---------- Queue helpers ----------
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isQueueEmpty(Queue* q) {
    return q->front == NULL;
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
    if (isQueueEmpty(q)) q->rear = NULL;
    Node* node = temp->treeNode;
    free(temp);
    return node;
}

// ---------- Utility ----------
Node* createNode(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = n->parent = NULL;
    return n;
}

void swap(Node* a, Node* b) {
    int t = a->data;
    a->data = b->data;
    b->data = t;
}

// ---------- Heapify (up / down) ----------
void heapifyUp(Node* node) {
    while (node->parent && node->data > node->parent->data) {
        swap(node, node->parent);
        node = node->parent;
    }
}

void heapifyDown(Node* node) {
    while (node) {
        Node* largest = node;
        if (node->left && node->left->data > largest->data){
            largest = node->left;
        }
        if (node->right && node->right->data > largest->data) {
            largest = node->right;
        }
        if (largest == node) {
            break;
        }
        swap(node, largest);
        node = largest;
    }
}

// ---------- Insert ----------
Node* insertHeap(Node* root, int data) {
    Node* newNode = createNode(data);
    if (!root) return newNode;

    Queue* q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        Node* temp = dequeue(q);
        if (!temp->left) {
            temp->left = newNode;
            newNode->parent = temp;
            break;
        } else {
            enqueue(q, temp->left);
        }

        if (!temp->right) {
            temp->right = newNode;
            newNode->parent = temp;
            break;
        } else {
            enqueue(q, temp->right);
        }
    }

    heapifyUp(newNode);
    return root;
}

// ---------- Delete max ----------
Node* deleteMax(Node* root) {
    if (!root) {
        printf("Heap is empty.\n");
        return NULL;
    }

    if (!root->left && !root->right) {
        printf("Deleted max element: %d\n", root->data);
        free(root);
        return NULL;
    }

    Queue* q = createQueue();
    enqueue(q, root);
    Node *temp, *last = NULL;

    while (!isQueueEmpty(q)) {
        temp = dequeue(q);
        if (temp->left) {
            enqueue(q, temp->left);
        }
        if (temp->right) {
            enqueue(q, temp->right);
        }
        last = temp;
    }

    printf("Deleted max element: %d\n", root->data);
    root->data = last->data;

    Node* p = last->parent;
    if (p->right == last) {
        p->right = NULL;
    } else {
        p->left = NULL;
    }
    free(last);

    heapifyDown(root);
    return root;
}

// ---------- Display ----------
void printLevelOrder(Node* root) {
    if (!root) {
        printf("(empty heap)\n");
        return;
    }

    Queue* q = createQueue();
    enqueue(q, root);
    enqueue(q, NULL);

    printf("\nCurrent Heap (Level Order):\n");
    while (!isQueueEmpty(q)) {
        Node* temp = dequeue(q);
        if (!temp) {
            printf("\n");
            if (!isQueueEmpty(q)) enqueue(q, NULL);
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

void freeTree(Node* r) {
    if (!r) {
        return;
    }
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

// ---------- Main ----------
int main() {
    Node* root = NULL;
    FILE* fp;
    char filename[100];
    int choice, value;

    printf("----- MAX HEAP (Linked Binary Tree) -----\n");

    // ---------- MENU 1 ----------
    while (1) {
        printf("\nFile Menu:\n");
        printf("1. Use default file (p06.txt)\n");
        printf("2. Enter custom filename\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) {
            printf("Exiting program...\n");
            return 0;
        }

        if (choice == 1) {
            strcpy(filename, "p06.txt");
            printf("Using default file: %s\n", filename);
        } else if (choice == 2) {
            printf("Enter filename: ");
            scanf("%s", filename);
        } else {
            printf("Invalid choice! Try again.\n");
            continue;
        }

        fp = fopen(filename, "r");
        if (!fp) {
            printf("Error opening file: %s\n", filename);
            continue;
        }

        printf("\nReading elements from %s and inserting into max-heap...\n", filename);
        while (fscanf(fp, "%d", &value) == 1) {
            root = insertHeap(root, value);
        }
        fclose(fp);
        printf("Heap created successfully!\n");
        printLevelOrder(root);
        break; // exit file menu
    }

    // ---------- MENU 2 ----------
    while (1) {
        printf("\nHeap Menu:\n");
        printf("1. Insert element\n");
        printf("2. Delete max element\n");
        printf("3. Display heap\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertHeap(root, value);
                printLevelOrder(root);
                break;

            case 2:
                root = deleteMax(root);
                printLevelOrder(root);
                break;

            case 3:
                printLevelOrder(root);
                break;

            case 4:
                freeTree(root);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}