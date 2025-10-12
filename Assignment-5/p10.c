#include <stdio.h>
#include <stdlib.h>

// ---------- AVL Node Structure ----------
typedef struct Node {
    int data;
    struct Node *left, *right;
    int height;
} Node;

// ---------- Utility Functions ----------
int max(int a, int b) { return (a > b) ? a : b; }
int height(Node *n) { return (n == NULL) ? 0 : n->height; }

Node* createNode(int data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// ---------- Rotations ----------
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

// ---------- AVL Insertion ----------
Node* insert(Node *node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node; // no duplicates

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rightRotate(node);
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// ---------- Minimum Value Node ----------
Node* minValueNode(Node *node) {
    Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// ---------- Delete Node ----------
Node* deleteNode(Node *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// ---------- Queue for Level Order ----------
typedef struct QNode {
    Node *treeNode;
    struct QNode *next;
} QNode;

typedef struct Queue {
    QNode *front, *rear;
} Queue;

Queue* createQueue() {
    Queue *q = (Queue*) malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isQueueEmpty(Queue *q) { return q->front == NULL; }

void enqueue(Queue *q, Node *node) {
    QNode *temp = (QNode*) malloc(sizeof(QNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (isQueueEmpty(q))
        q->front = q->rear = temp;
    else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

Node* dequeue(Queue *q) {
    if (isQueueEmpty(q)) return NULL;
    QNode *temp = q->front;
    q->front = q->front->next;
    if (isQueueEmpty(q)) q->rear = NULL;
    Node *node = temp->treeNode;
    free(temp);
    return node;
}

// ---------- Level Order Traversal ----------
void levelOrder(Node *root) {
    if (!root) {
        printf("(empty tree)\n");
        return;
    }

    Queue *q = createQueue();
    enqueue(q, root);

    printf("\nLevel Order Traversal of AVL Tree:\n");
    while (!isQueueEmpty(q)) {
        int count = 0;
        QNode *temp = q->front;
        while (temp) { count++; temp = temp->next; }

        for (int i = 0; i < count; i++) {
            Node *curr = dequeue(q);
            printf("%d ", curr->data);
            if (curr->left) enqueue(q, curr->left);
            if (curr->right) enqueue(q, curr->right);
        }
        printf("\n");
    }
}

// ---------- Inorder Traversal (Sorted Order) ----------
void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// ---------- Free memory ----------
void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ---------- Build AVL from file ----------
Node* buildTreeFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    Node *root = NULL;
    int value;
    while (fscanf(fp, "%d", &value) == 1)
        root = insert(root, value);
    fclose(fp);

    if (root == NULL)
        printf("No valid integers found in file.\n");
    else
        printf("\nAVL Tree created successfully from %s\n", filename);

    return root;
}

// ---------- Display Function (Both Traversals) ----------
void displayTree(Node *root) {
    levelOrder(root);
    printf("\nInorder Traversal (sorted order):\n");
    inorder(root);
    printf("\n");
}

// ---------- Main ----------
int main() {
    int mainChoice, subChoice, value;
    Node *root = NULL;
    char filename[100];

    do {
        printf("\n=========== MAIN MENU ===========\n");
        printf("1. Use default file (p10.txt)\n");
        printf("2. Enter filename manually\n");
        printf("3. Exit\n");
        printf("=================================\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                root = buildTreeFromFile("p10.txt");
                break;
            case 2:
                printf("Enter filename: ");
                scanf("%s", filename);
                root = buildTreeFromFile(filename);
                break;
            case 3:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
                continue;
        }

        if (root == NULL) break;

        do {
            printf("\n---------- AVL TREE MENU ----------\n");
            printf("1. Delete a node\n");
            printf("2. Display AVL Tree (Level + Inorder)\n");
            printf("3. Exit\n");
            printf("-----------------------------------\n");
            printf("Enter your choice: ");
            scanf("%d", &subChoice);

            switch (subChoice) {
                case 1:
                    printf("Enter the value to delete: ");
                    scanf("%d", &value);
                    root = deleteNode(root, value);
                    printf("\nAVL Tree after deleting %d:\n", value);
                    displayTree(root);
                    break;
                case 2:
                    displayTree(root);
                    break;
                case 3:
                    printf("Exiting...\n");
                    return 0;
                default:
                    printf("Invalid choice! Try again.\n");
            }
        } while (subChoice != 3);

        freeTree(root);
        root = NULL;

    } while (mainChoice != 3);

    return 0;
}