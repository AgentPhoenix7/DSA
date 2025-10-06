#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Queue Node
typedef struct Node {
    char data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Initialize queue
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Enqueue character
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

// Dequeue character
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

// Main check function
int isForm_w_hash_reverse_w(char* str) {
    int i = 0;
    Queue q;
    initQueue(&q);

    // Step 1: enqueue all characters before '#'
    while (str[i] && str[i] != '#') {
        if (!isalnum(str[i])) {
            return 0;  // invalid char
        }
        enqueue(&q, str[i]);
        i++;
    }

    // Must contain '#'
    if (str[i] != '#') {
        return 0;
    }
    int hashIndex = i;
    i++;

    // Step 2: find end of string
    int end = i;
    while (str[end]) {
        if (!isalnum(str[end])) {
            return 0;
        }
        end++;
    }
    end--; // index of last character

    // Step 3: compare queue with reverse part
    while (!isEmpty(&q) && end > hashIndex) {
        if (dequeue(&q) != str[end]) {
            return 0;
        }
        end--;
    }

    // Both must be fully consumed
    return isEmpty(&q) && end == hashIndex;
}

// Main
int main() {
    char input[100];
    printf("Enter string (format w#w'): ");
    scanf("%99s", input);

    if (isForm_w_hash_reverse_w(input)) {
        printf("YES: The string is of the form w#w'\n");
    } else {
        printf("NO: The string is NOT of the form w#w'\n");
    }

    return 0;
}