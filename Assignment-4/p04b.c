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
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = ch;
    temp->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

// Dequeue (remove from front)
char dequeue(Queue* q) {
    if (isEmpty(q)) {
        return '\0';
    }
    Node* temp = q->front;
    char ch = temp->data;
    q->front = q->front->next;
    if (isEmpty(q)) {
        q->rear = NULL;
    }
    free(temp);
    return ch;
}

// Problem (b)
// ww
int isForm_ww(char* str) {
    int len = strlen(str);
    if (len % 2 != 0) {
        return 0;
    }
    int mid = len / 2;
    Queue q1, q2;
    initQueue(&q1);
    initQueue(&q2);

    for (int i = 0; i < mid; i++) {
        if (!isalnum(str[i])) return 0;
        enqueue(&q1, str[i]);
    }

    for (int i = mid; i < len; i++) {
        if (!isalnum(str[i])) return 0;
        enqueue(&q2, str[i]);
    }

    while (!isEmpty(&q1) && !isEmpty(&q2)) {
        if (dequeue(&q1) != dequeue(&q2)) return 0;
    }

    return isEmpty(&q1) && isEmpty(&q2);
}

// Main
int main() {
    char input[100];
    printf("Enter string (format ww): ");
    scanf("%99s", input);

    if (isForm_ww(input)) {
        printf("YES: The string is of the form ww\n");
    } else {
        printf("NO: The string is NOT of the form ww\n");
    }
    return 0;
}