#include <stdio.h>
#include <stdlib.h>

// Define struct for one term in compact matrix
typedef struct {
    int row, col, value;
} Term;

// Function to convert sparse to compact using dynamic array
int convertToCompact(int rows, int cols, int **matrix, Term **compact) {
    int count = 0;

    // First pass to count non-zero elements
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                count++;
            }
        }
    }

    *compact = (Term *)malloc(count * sizeof(Term));
    if (*compact == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                (*compact)[k].row = i;
                (*compact)[k].col = j;
                (*compact)[k].value = matrix[i][j];
                k++;
            }
        }
    }

    return count;
}

// Function to add two compact matrices
int addCompactMatrices(Term *a, int sizeA, Term *b, int sizeB, Term **result) {
    int i = 0, j = 0, k = 0;

    *result = (Term *)malloc((sizeA + sizeB) * sizeof(Term));
    if (*result == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    while (i < sizeA && j < sizeB) {
        if (a[i].row == b[j].row && a[i].col == b[j].col) {
            int sum = a[i].value + b[j].value;
            if (sum != 0) {
                (*result)[k++] = (Term){a[i].row, a[i].col, sum};
            }
            i++; j++;
        } else if (a[i].row < b[j].row || (a[i].row == b[j].row && a[i].col < b[j].col)) {
            (*result)[k++] = a[i++];
        } else {
            (*result)[k++] = b[j++];
        }
    }

    while (i < sizeA) (*result)[k++] = a[i++];
    while (j < sizeB) (*result)[k++] = b[j++];

    return k;
}

// Function to print a compact matrix
void printCompactMatrix(Term *compact, int size) {
    printf("Row\tCol\tValue\n");
    for (int i = 0; i < size; i++)
        printf("%d\t%d\t%d\n", compact[i].row, compact[i].col, compact[i].value);
}

// Main function
int main() {
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    // Allocate matrix 1
    int **matrix1 = (int **)malloc(rows * sizeof(int *));
    int **matrix2 = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix1[i] = (int *)malloc(cols * sizeof(int));
        matrix2[i] = (int *)malloc(cols * sizeof(int));
    }

    printf("\nEnter elements of first matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element[%d][%d]: ", i, j);  // Zero index
            scanf("%d", &matrix1[i][j]);
        }
    }

    printf("\nEnter elements of second matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element[%d][%d]: ", i, j);  // Zero index
            scanf("%d", &matrix2[i][j]);
        }
    }

    // Convert to compact form
    Term *compact1, *compact2, *result;
    int size1 = convertToCompact(rows, cols, matrix1, &compact1);
    int size2 = convertToCompact(rows, cols, matrix2, &compact2);

    // Add compact matrices
    int resultSize = addCompactMatrices(compact1, size1, compact2, size2, &result);

    // Output
    printf("\nResultant Compact Matrix:\n");
    printCompactMatrix(result, resultSize);

    // Free allocated memory
    free(compact1);
    free(compact2);
    free(result);
    for (int i = 0; i < rows; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);

    return 0;
}