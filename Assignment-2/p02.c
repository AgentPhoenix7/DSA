#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int v) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->data = v;
    n->next = NULL;
    return n;
}

void createLinkedList(Node **head, int v) {
    Node *n = createNode(v);
    if (*head == NULL) {
        *head = n;
        return;
    }
    Node *t = *head;
    while (t->next) {
        t = t->next;
    }
    t->next = n;
}

void display(Node* head) {
    Node *t = head;
    printf("Linked List: ");
    while (t != NULL) {
        printf("%d", t->data);
        if (t->next != NULL) {
            printf(" ");
        }
        t = t->next;
    }
    printf("\n");
}

// Insert after given data
int insertAfter(Node *head, int target, int v) {
    for (Node *t = head; t; t = t->next) {
        if (t->data == target) {
            Node *n = createNode(v);
            n->next = t->next;
            t->next = n;
            return 1;
        }
    }
    return 0;   // Not found
}

// Insert before given data
int insertBefore(Node **head, int target, int v) {
    if (*head == NULL) {
        return 0;
    }
    if ((*head)->data == target) {
        Node *n = createNode(v);
        n->next = *head;
        *head = n;
        return 1;
    }
    for (Node *t = *head; t->next; t = t->next) {
        if (t->next->data == target) {
            Node *n = createNode(v);
            n->next = t->next;
            t->next = n;
            return 1;
        }
    }
    return 0;
}

// Delete a given data (First occurrence)
int deleteData(Node **head, int target) {
    if (*head == NULL) {
        return 0;
    }
    if ((*head)->data == target) {
        Node *del = *head;
        *head = (*head)->next;
        free(del);
        return 1;
    }
    for (Node *t= *head; t->next; t= t->next) {
        if (t->next->data == target) {
            Node *del = t->next;
            t->next = del->next;
            free(del);
            return 1;
        }
    }
    return 0;
}

// Insert at n-th position (1-based)
int insertAtPosition(Node **head, int pos, int v) {
    if (pos < 1) {
        return -1;
    }
    if (pos == 1) {
        Node *n = createNode(v);
        n->next = *head;
        *head = n;
        return 1;
    }
    Node *t = *head;
    for (int i = 1; t && i < pos - 1; i++) {
        t = t->next;
    }
    if (!t) {
        return 0;
    }
    Node *n = createNode(v);
    n->next = t->next;
    t->next = n;
    return 1;
}

// Find middle
void findMiddle (Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *slow = head, *fast = head, *prev = NULL;

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
int getNthFromEnd(Node *head, int n, int *out) {
    Node *a = head, *b = head;
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
void clearList(Node **head) {
    Node *t = *head;
    while (t) {
        Node *n = t->next;
        free(t);
        t = n;
    }
    *head = NULL;
}

int main() {
    Node *head = NULL;
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