#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Create new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Check if stack is empty
int isEmpty(Node* top) {
    return top == NULL;
}

// PUSH operation
void PUSH(Node** top, int value) {
    Node* newNode = createNode(value);
    newNode->next = *top;
    *top = newNode;
    printf("Pushed %d onto the stack.\n", value);
}

// POP operation
int POP(Node** top) {
    if (isEmpty(*top)) {
        printf("Stack underflow. Nothing to pop.\n");
        return -1;
    }

    Node* temp = *top;
    int poppedValue = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedValue;
}

// Display stack
void display(Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Current Stack: ");
    Node* temp = top;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function
int main() {
    Node* top = NULL;
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
                PUSH(&top, value);
                break;
            
            case 2:
                value = POP(&top);
                if (value != -1) {
                    printf("Popped value: %d\n", value);
                }
                break;
            
            case 3:
                display(top);
                break;
            
            case 4:
                printf("Exiting.\n");
                while(!isEmpty(top)) {
                    POP(&top);
                }
                exit(0);
            
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}