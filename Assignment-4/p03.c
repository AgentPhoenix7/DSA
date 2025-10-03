#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TOKENS 100

// -------- Stack using Linked List --------
typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* push(Node* top, int value) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = top;
    return newNode;
}

Node* pop(Node* top, int* poppedValue) {
    if (top == NULL) {
        printf("Error: Stack underflow.\n");
        exit(1);
    }
    *poppedValue = top->data;
    Node* temp = top;
    top = top->next;
    free(temp);
    return top;
}

int isOperator(char* token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0);
}

int performOperation(char* operator, int op1, int op2) {
    if (strcmp(operator, "+") == 0) {
        return op1 + op2;
    }
    if (strcmp(operator, "-") == 0) {
        return op1 - op2;
    }
    if (strcmp(operator, "*") == 0) {
        return op1 * op2;
    }
    if (strcmp(operator, "/") == 0) {
        if (op2 == 0) {
            printf("Error: Division by zero.\n");
            exit(1);
        }
        return op1 / op2;
    }
    return 0; // Should not reach here
}

int main(int argc, char* argv[]) {
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
        // Skip empty lines
        if (strlen(line) <= 1) continue;

        // Tokenize the line
        char* tokens[MAX_TOKENS];
        int count = 0;
        char* token = strtok(line, " \n");
        while (token != NULL && count < MAX_TOKENS) {
            tokens[count++] = token;
            token = strtok(NULL, " \n");
        }

        // Evaluate from right to left
        Node* stack = NULL;
        int error = 0;

        for (int i = count - 1; i >= 0; i--) {
            if (isOperator(tokens[i])) {
                int operand1, operand2;
                if (!stack) {
                    error = 1;
                    break;
                }
                stack = pop(stack, &operand1);
                if (!stack) {
                    error = 1;
                    break;
                }
                stack = pop(stack, &operand2);
                int result = performOperation(tokens[i], operand1, operand2);
                stack = push(stack, result);
            } else {
                stack = push(stack, atoi(tokens[i]));
            }
        }

        if (error || !stack) {
            printf("Line %d: Error evaluating expression.\n", lineNumber);
            lineNumber++;
            continue;
        }

        int finalResult;
        stack = pop(stack, &finalResult);
        if (stack != NULL) {
            printf("Line %d: Error: Invalid expression (extra operands).\n", lineNumber);
            // Clean up remaining stack
            while (stack != NULL) {
                int temp;
                stack = pop(stack, &temp);
            }
        } else {
            printf("Line %d Result: %d\n", lineNumber, finalResult);
        }

        lineNumber++;
    }

    fclose(fp);
    return 0;
}
