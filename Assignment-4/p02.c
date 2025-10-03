#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

void push(Node** top, char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = c;
    newNode->next = *top;
    *top = newNode;
}

char pop(Node** top) {
    if (*top == NULL) {
        return '\0';   // stack underflow
    }
    Node* temp = *top;
    char popped = temp->data;
    *top = (*top)->next;
    free(temp);
    return popped;
}

int isEmpty(Node* top) {
    return top == NULL;
}

int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') || (open == '{' && close == '}') || (open == '[' && close == ']'); 
}

int isBalanced(const char* expr) {
    Node* stack = NULL;
    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (c == '(' || c == '{' || c == '[') {
            push(&stack, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (isEmpty(stack)) {
                return 0;
            }
            char topChar = pop (&stack);
            if (!isMatchingPair(topChar, c)) {
                return 0;    // unbalanced
            }
        }
    }
    return isEmpty(stack);
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