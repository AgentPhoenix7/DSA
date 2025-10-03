#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    int size;
    Node* front;
    Node* rear;
} Queue;

// Create new node
Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Initialize Queue
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

bool isEmpty(Queue* q) {
    return (q->front == NULL);
}

// Enqueue: Adds a new element to the queue
void enqueue(Queue* q, int value) {
    Node* newNode = createNode(value);
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
    printf("%d enqueued to the queue.\n", value);
}

// Dequeue: Removes and returns the first (front) element from the queue
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    Node* temp = q->front;
    int value = temp-> data;
    q->front = q->front->next;

    // Make rear NULL in case of NULL front
    if (isEmpty(q)) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;
    printf("%d dequeued from the queue.\n", value);
    return value;
}

// Peak: Returns the first element in the queue
int peek(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty. Nothing to peek.\n");
        return -1;
    }
    return q->front->data;
}

// Size: Finds the number of elements in the queue
int size(Queue* q) {
    return q->size;
}

// Display the queue
void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    Node* temp = q->front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Free all nodes
void freeQueue(Queue* q) {
    while (!isEmpty(q)) {
        Node* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
    q->size = 0;
}

// Main function
int main() {
    Queue q;
    initQueue(&q);
    int choice, value;

    while (1) {
        printf("\nQueue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Check if Empty\n");
        printf("5. Size\n");
        printf("6. Display Queue\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            
            case 2:
                dequeue(&q);
                break;
            
            case 3:
                value = peek(&q);
                if (value != -1) {
                    printf("Front element: %d\n", value);
                }
                break;
            
            case 4:
                if (isEmpty(&q)) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Queue is not empty.\n");
                }
                break;
            
            case 5:
                printf("Queue size: %d\n", size(&q));
                break;
            
            case 6:
                displayQueue(&q);
                break;
            
            case 7:
                printf("Exiting.\n");
                freeQueue(&q);
                exit(0);
            
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}