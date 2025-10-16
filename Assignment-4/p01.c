#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Initialize the stack
void initStack(Stack* stack) {
    stack->top = NULL;
}

// Push operation
void push(Stack* stack, int value) {
    Node* newNode = createNode(value);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop operation
int pop(Stack* stack) {
    if (stack->top == NULL) {
        return -1; // Stack underflow
    }
    Node* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = temp->next;
    free(temp);
    return poppedValue;
}

// Check if a number is prime
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
    Stack stack;       // Create a stack structure
    initStack(&stack); // Initialize it

    printf("Enter an integer: ");
    scanf("%d", &num);

    if (num < 2) {
        printf("No prime divisors for %d\n", num);
        return 0;
    }

    // Push prime divisors in descending order
    for (int i = num; i >= 2; i--) {
        if (num % i == 0 && isPrime(i)) {
            push(&stack, i);
        }
    }

    // Pop and print in ascending order
    printf("Prime divisors in ascending order: ");
    while (stack.top != NULL) {
        printf("%d ", pop(&stack));
    }
    printf("\n");

    return 0;
}