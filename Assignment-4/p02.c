#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Stack structure
typedef struct Stack {
    Node* top;
} Stack;

// Function to initialize the stack
void initStack(Stack* stack) {
    stack->top = NULL;
}

// Check if stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Push element onto stack
void push(Stack* stack, char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = c;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop element from stack
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        return '\0'; // Stack underflow
    }
    Node* temp = stack->top;
    char poppedValue = temp->data;
    stack->top = temp->next;
    free(temp);
    return poppedValue;
}

// Function to check if brackets match
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// Function to check if expression is balanced
int isBalanced(const char* expr) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (c == '(' || c == '{' || c == '[') {
            push(&stack, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (isEmpty(&stack)) {
                return 0; // Unbalanced (extra closing)
            }
            char topChar = pop(&stack);
            if (!isMatchingPair(topChar, c)) {
                return 0; // Unbalanced pair
            }
        }
    }

    int balanced = isEmpty(&stack);

    // Clean up any remaining nodes (safety)
    while (!isEmpty(&stack)) {
        pop(&stack);
    }

    return balanced;
}

int main() {
    char expr1[] = "(){(([]))}";
    char expr2[] = "((([]))}";

    if (isBalanced(expr1)) {
        printf("Expression: %s is Balanced.\n", expr1);
    } else {
        printf("Expression: %s is Unbalanced.\n", expr1);
    }

    if (isBalanced(expr2)) {
        printf("Expression: %s is Balanced.\n", expr2);
    } else {
        printf("Expression: %s is Unbalanced.\n", expr2);
    }

    return 0;
}