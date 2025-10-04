#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("malloc");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void createLinkedList(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void display(Node* head) {
    Node* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Insert after given data
int insertAfter(Node* head, int key, int value) {
    for (Node* temp = head; temp; temp = temp->next) {
        if (temp->data == key) {
            Node* newNode = createNode(value);
            newNode->next = temp->next;
            temp->next = newNode;
            return 1;
        }
    }
    return 0;   // Not found
}

// Insert before given data
int insertBefore(Node** head, int key, int value) {
    if (*head == NULL) {
        return 0;
    }
    if ((*head)->data == key) {
        Node* newNode = createNode(value);
        newNode->next = *head;
        *head = newNode;
        return 1;
    }
    for (Node* temp = *head; temp->next; temp = temp->next) {
        if (temp->next->data == key) {
            Node* newNode = createNode(value);
            newNode->next = temp->next;
            temp->next = newNode;
            return 1;
        }
    }
    return 0;
}

// Delete a given data (First occurrence)
int deleteData(Node** head, int key) {
    if (*head == NULL) {
        return 0;
    }
    if ((*head)->data == key) {
        Node* del = *head;
        *head = (*head)->next;
        free(del);
        return 1;
    }
    for (Node* temp = *head; temp->next; temp = temp->next) {
        if (temp->next->data == key) {
            Node* del = temp->next;
            temp->next = del->next;
            free(del);
            return 1;
        }
    }
    return 0;
}

// Insert at n-th position (1-based)
int insertAtPosition(Node** head, int pos, int value) {
    if (pos < 1) {
        return -1;
    }
    if (pos == 1) {
        Node* newNode = createNode(value);
        newNode->next = *head;
        *head = newNode;
        return 1;
    }
    Node* temp = *head;
    for (int i = 1; temp && i < pos - 1; i++) {
        temp = temp->next;
    }
    if (!temp) {
        return 0;
    }
    Node* newNode = createNode(value);
    newNode->next = temp->next;
    temp->next = newNode;
    return 1;
}

// Find middle
void findMiddle (Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* slow = head, *fast = head, *prev = NULL;

    while (fast && fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    if (fast == NULL) {
        printf("Middle values: %d and %d\n", prev->data, slow->data);
    } else {
        printf("Middle value: %d\n", slow->data);
    }
}

// Find n-th from end
int getNthFromEnd(Node* head, int n, int* out) {
    Node* a = head;
    Node* b = head;
    for (int i = 0; i < n; i++) {
        if (!a) {
            return 0;
        }
        a = a->next;
    }
    while (a) {
        a = a->next;
        b = b->next;
    }
    *out = b->data;
    return 1;
}

// Cleanup
void clearList(Node** head) {
    Node* temp = *head;
    while (temp) {
        Node* n = temp->next;
        free(temp);
        temp = n;
    }
    *head = NULL;
}

int main() {
    Node* head = NULL;
    int choice, val, x, y, pos, n;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Append value(s)\n");
        printf("2. Display list\n");
        printf("3. Insert after a value\n");
        printf("4. Insert before a value\n");
        printf("5. Delete a value\n");
        printf("6. Insert at n-th position\n");
        printf("7. Find middle value\n");
        printf("8. Get n-th from end\n");
        printf("9. Clear list\n");
        printf("0. Exit\n");
        printf("\nEnter choice: ");
        if (scanf("%d", &choice) != 1) {
            break;
        }
        switch(choice) {
            case 1:
                printf("Input integers (-1 to stop):\n");
                while(scanf("%d", &val) == 1 && val != -1) {
                    createLinkedList(&head, val);
                }
                break;
            
            case 2:
                display(head);
                break;

            case 3:
                printf("After which value? ");
                scanf("%d", &x);
                printf("Value to insert: ");
                scanf("%d", &y);
                if (!insertAfter(head, x, y)) {
                    printf("Value %d not found.\n", x);
                }
                break;
            
            case 4:
                printf("Before which value? ");
                scanf("%d", &x);
                printf("Value to insert: ");
                scanf("%d", &y);
                if (!insertBefore(&head, x, y)) {
                    printf("Value %d not found.\n", x);
                }
                break;
            
            case 5:
                printf("Value to delete: ");
                scanf("%d", &x);
                if (!deleteData(&head, x)) {
                    printf("Value %d not found.\n", x);
                }
                break;
            
            case 6:
                printf("Position: ");
                scanf("%d", &pos);
                printf("Value to insert: ");
                scanf("%d", &y);
                {
                    int r = insertAtPosition(&head, pos, y);
                    if (r == 0) {
                        printf("Position out of range.\n");
                    }
                    if (r == -1) {
                        printf("Invalid position.\n");
                    }
                }
                break;
            
            case 7:
                findMiddle(head);
                break;
            
            case 8:
                printf("n (from end): ");
                scanf("%d", &n);
                if (getNthFromEnd(head, n, &x)) {
                    printf("%d-th from end: %d\n", n, x);
                } else {
                    printf("List shorter than %d elements.\n", n);
                }
                break;

            case 9:
                clearList(&head);
                printf("List cleared.\n");
                break;
            
            case 0:
                clearList(&head);
                return 0;
            
            default:
                printf("Invalid choice.\n");
        }
    }
    clearList(&head);
    return 0;
}