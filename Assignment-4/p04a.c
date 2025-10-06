#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Queue Node
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Queue ADT
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Queue Functions
// Initialize the Queue
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Check if Empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Enqueue (insert at rear)
void enqueue(Queue* q, char ch) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = ch;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Dequeue (remove from front)
char dequeue(Queue* q) {
    if (isEmpty(q)) {
        return '\0';
    }
    Node* temp = q->front;
    char ch = temp->data;
    q->front = temp->next;
    if (isEmpty(q)) {
        q->rear = NULL;
    }
    free(temp);
    return ch;
}

// Problem (a)
// w#w
int isForm_w_hash_w(char* str) {
    int i = 0;
    Queue q1, q2;
    initQueue(&q1);
    initQueue(&q2);

    while (str[i] && str[i] != '#') {
        if (!isalnum(str[i])) {
            return 0;
        }
        enqueue(&q1, str[i]);
        i++;
    }

    if (str[i] != '#') {
        return 0;
    }
    i++;

    while (str[i]) {
        if (!isalnum(str[i])) {
            return 0;
        }
        enqueue(&q2, str[i]);
        i++;
    }

    while (!isEmpty(&q1) && !isEmpty(&q2)) {
        if (dequeue(&q1) != dequeue(&q2)) {
            return 0;
        }
    }

    return isEmpty(&q1) && isEmpty(&q2);
}

// Main
int main() {
    char input[100];
    printf("Enter string (format w#w): ");
    scanf("%99s", input);

    if (isForm_w_hash_w(input)) {
        printf("YES: The string is of the form w#w\n");
    } else {
        printf("NO: The string is NOT of the form w#w\n");
    }
    return 0;
}