#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Initialize Stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// PUSH operation
void PUSH(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow. Cannot push %d.\n", value);
        return;
    }
    s->arr[++(s->top)] = value;
    printf("Pushed %d onto the stack.\n", value);
}

// POP operation
int POP(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow. Nothing to pop.\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

// Display stack
void display(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Current Stack: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    Stack s;
    initStack(&s);

    int choice, value;

    while (1) {
        printf("\nStack Menu\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. Display Stack\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                PUSH(&s, value);
                break;
            
            case 2:
                value = POP(&s);
                if (value != -1) {
                    printf("Popped value: %d\n", value);
                }
                break;
            
            case 3:
                display(&s);
                break;
            
            case 4:
                printf("Exiting.\n");
                exit(0);
            
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}