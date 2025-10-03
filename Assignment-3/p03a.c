#include <stdio.h>

void convertToCompact(int rows, int cols, int matrix[rows][cols]) {
    int compact[rows * cols][3];
    int k = 0;

    // Create compact matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                compact[k][0] = i;
                compact[k][1] = j;
                compact[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    printf("\nCompact Matrix Representation:\n");
    printf("Row\tCol\tValue\n");
    for (int i = 0; i < k; i++) {
        printf("%d\t%d\t%d\n", compact[i][0], compact[i][1], compact[i][2]);
    }
}

// Main function
int main() {
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    int matrix[rows][cols];
    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element[%d][%d]: ", i, j);  // Zero index
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nOriginal Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    convertToCompact(rows, cols, matrix);
    return 0;
}