#include <stdio.h>
#define MAX 100

int main() {
    int arr[MAX];
    int size=0, num;
    printf("Enter integers (End with 0):\n");
    while(1) {
        scanf("%d", &num);
        if (num == 0) {
            break;
        }
        arr[size++] = num;
    }
    printf("The Entered Array Is:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}