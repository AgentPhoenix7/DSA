#include <stdio.h>
#define MAX 100

int arr[MAX];
int size = 0;

void inputData() {
    int x;
    printf("Enter integers (End with 0):\n");
    while(1) {
        scanf("%d", &x);
        if (x == 0) {
            break;
        }
        arr[size++] = x;
    }
}

void printArray() {
    printf("Current Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertAfter(int key, int newData) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            for (int j = size; j > i + 1; j--) {
                arr[j] = arr[j - 1];
            }
            arr[i + 1] = newData;
            size++;
            return;
        }
    }
    printf("Data not found.\n");
}

void insertBefore(int key, int newData) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            for (int j = size; j > i; j--) {
                arr[j] = arr[j - 1];
            }
            arr[i] = newData;
            size++;
            return;
        }
    }
    printf("Data not found.\n");
}

void deleteData(int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            for (int j = i; j < size - 1; j++) {
                arr[j] = arr[j + 1];
            }
            size--;
            return;
        }
    }
    printf("Data not found.\n");
}

void insertAtN(int pos, int newData) {
    int index = pos - 1;
    if (index < 0 || index > size) {
        printf("Invalid position.\n");
        return;
    }
    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = newData;
    size++;
}

void findMiddle() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }
    if (size % 2 == 0) {
        printf("Middle data: %d and %d\n", arr[size / 2 - 1], arr[size / 2]);
    } else {
        printf("Middle data: %d\n", arr[size / 2]);
    }
}

void nthFromEnd(int n) {
    if (n <= 0 || n > size) {
        printf("Invalid n.\n");
        return;
    }
    printf ("The %d-th data from end: %d\n", n, arr[size - n]);
}

int main() {
    int choice, key, value, n;
    inputData();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert after a value\n");
        printf("2. Insert before a value\n");
        printf("3. Delete a value\n");
        printf("4. Insert at n-th position\n");
        printf("5. Find middle data\n");
        printf("6. Get n-th data from the end\n");
        printf("7. Print array\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Insert after which value? ");
                scanf("%d", &key);
                printf("Enter new value: ");
                scanf("%d", &value);
                insertAfter(key, value);
                break;
            case 2:
                printf("Insert before which value? ");
                scanf("%d", &key);
                printf("Enter new value: ");
                scanf("%d", &value);
                insertBefore(key, value);
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &key);
                deleteData(key);
                break;
            case 4:
                printf("Enter position: ");
                scanf("%d", &n);
                printf("Enter new value: ");
                scanf("%d", &value);
                insertAtN(n, value);
                break;
            case 5:
                findMiddle();
                break;
            case 6:
                printf("Enter n: ");
                scanf("%d", &n);
                nthFromEnd(n);
                break;
            case 7:
                printArray();
                break;
            case 8:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}