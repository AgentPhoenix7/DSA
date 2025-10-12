#include <stdio.h>
#include <stdlib.h>

// Define a structure for a tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Queue node structure for level order insertion
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

// Queue structure
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function to check if the queue is empty
int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
}

// Function to create a new tree node
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Queue operations
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    if (!temp) {
        printf("Memory allocation error!\n");
        exit(1);
    }

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

// Function to insert a new node in level order to maintain completeness
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

// Print the tree level by level, one line per level
void printTreeByLevels(Node* root) {
    if (root == NULL) {
        return;
    }
    Queue* q = createQueue();
    enqueue(q, root);
    enqueue(q, NULL);  // Level delimiter

    printf("\nTree displayed level by level:\n");

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

int main(int argc, char* argv[]) {
    const char* filename;

    // Use input.txt by default if not specified
    if (argc == 1) {
        filename = "input.txt";
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

    // Read integers from the file and insert into the tree
    while (fscanf(fp, "%d", &value) == 1) {
        root = insertLevelOrder(root, value);
    }

    fclose(fp);

    // Display the tree
    printTreeByLevels(root);

    return 0;
}