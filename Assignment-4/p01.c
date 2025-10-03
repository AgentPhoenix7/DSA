#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(Node** top, int data) {
    Node* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}

int pop(Node** top) {
    if (*top == NULL) {
        return -1;
    }
    Node* temp = *top;
    int popped = temp->data;
    *top = (*top)->next;
    free(temp);
    return popped;
}

int isPrime(int num) {
    if (num < 2) {
        return 0;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);

    if (num < 2) {
        printf("No prime divisors for %d\n", num);
    }

    Node* stack = NULL;
    for (int i = num; i >= 2; i--) {
        if (num % i == 0 && isPrime(i)) {
            push(&stack, i);
        }
    }

    printf("Prime divisors: ");
    while (stack != NULL) {
        printf("%d ", pop(&stack));
    }
    printf("\n");

    return 0;
}