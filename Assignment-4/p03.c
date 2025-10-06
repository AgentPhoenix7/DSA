#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TOKENS 100

// -------- Stack using Linked List --------
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Stack structure
typedef struct Stack{
    Node* top;
} Stack;

// Initialize stack
void initStack(Stack* stack) {
    stack->top = NULL;
}

// Check if stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Push value onto stack
void push(Stack* stack, int value) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop value from stack
int pop(Stack* stack, int* poppedValue) {
    if (isEmpty(stack)) {
        return 0; // Error: Stack underflow
    }
    Node* temp = stack->top;
    *poppedValue = temp->data;
    stack->top = temp->next;
    free(temp);
    return 1;
}

// Free entire stack (clean-up)
void freeStack(Stack* stack) {
    int temp;
    while (pop(stack, &temp))
        ;
}

// -------- Expression Evaluation --------

int isOperator(char* token) {
    return (strcmp(token, "+") == 0 ||
            strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 ||
            strcmp(token, "/") == 0);
}

int performOperation(char* operator, int op1, int op2) {
    if (strcmp(operator, "+") == 0) {
        return op1 + op2;
    } else if (strcmp(operator, "-") == 0) {
        return op1 - op2;
    } else if (strcmp(operator, "*") == 0) {
        return op1 * op2;
    } else if (strcmp(operator, "/") == 0) {
        if (op2 == 0) {
            printf("Error: Division by zero.\n");
            exit(1);
        }
        return op1 / op2;
    }
    return 0; // Should never reach here
}

int main(int argc, char *argv[]) {
    const char* filename;

    // Use default filename if not provided
    if (argc < 2) {
        printf("No input file provided. Using default: input.txt\n");
        filename = "input.txt";
    } else {
        filename = argv[1];
    }

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    char line[256];
    int lineNumber = 1;

    while (fgets(line, sizeof(line), fp)) {
        if (strlen(line) <= 1) {
            continue; // Skip empty lines
        }
        // Tokenize the line
        char* tokens[MAX_TOKENS];
        int count = 0;
        char* token = strtok(line, " \n");
        while (token != NULL && count < MAX_TOKENS) {
            tokens[count++] = token;
            token = strtok(NULL, " \n");
        }

        // Initialize a new stack for each line
        Stack stack;
        initStack(&stack);
        int error = 0;

        // Evaluate from right to left
        for (int i = count - 1; i >= 0; i--) {
            if (isOperator(tokens[i])) {
                int operand1, operand2;

                if (!pop(&stack, &operand1) || !pop(&stack, &operand2)) {
                    error = 1;
                    break;
                }

                int result = performOperation(tokens[i], operand1, operand2);
                push(&stack, result);
            } else {
                push(&stack, atoi(tokens[i]));
            }
        }

        if (error || isEmpty(&stack)) {
            printf("Line %d: Error evaluating expression.\n", lineNumber);
            freeStack(&stack);
            lineNumber++;
            continue;
        }

        int finalResult;
        pop(&stack, &finalResult);

        if (!isEmpty(&stack)) {
            printf("Line %d: Error: Invalid expression (extra operands).\n", lineNumber);
        } else {
            printf("Line %d Result: %d\n", lineNumber, finalResult);
        }

        freeStack(&stack);
        lineNumber++;
    }

    fclose(fp);
    return 0;
}