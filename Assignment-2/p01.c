#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void createLinkedList(Node** head, int value) {
    Node* newNode = createNode(value);
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void display(Node* head) {
    Node* temp = head;
    printf("Linked List: ");
    while(temp != NULL) {
        printf("%d", temp->data);
        if(temp->next != NULL) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    int num;
    printf("Input integers (-1 to stop):\n");
    while(1) {
        scanf("%d", &num);
        if(num == -1) {
            break;
        }
        createLinkedList(&head, num);
    }
    display(head);
    return 0;
}