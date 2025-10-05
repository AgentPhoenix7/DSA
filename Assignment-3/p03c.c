#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, col, value;
} Term;

// Function to convert 2D sparse matrix to compact form
int convertToCompact(int rows, int cols, int** matrix, Term** compact) {
    int count = 0;

    // Count non-zero elements
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                count++;
            }
        }
    }

    *compact = (Term*)malloc(count * sizeof(Term));
    if (*compact == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                (*compact)[k++] = (Term){i, j, matrix[i][j]};
            }
        }
    }

    return count;
}

// Multiply two compact matrices (A × B)
int multiplyCompactMatrices(Term* a, int sizeA, Term* b, int sizeB, Term** result) {
    int k = 0;
    *result = NULL;

    for (int i = 0; i < sizeA; i++) {
        for (int j = 0; j < sizeB; j++) {
            if (a[i].col == b[j].row) {
                int r = a[i].row;
                int c = b[j].col;
                int val = a[i].value * b[j].value;

                // Check if result already has (r, c)
                int found = 0;
                for (int z = 0; z < k; z++) {
                    if ((*result)[z].row == r && (*result)[z].col == c) {
                        (*result)[z].value += val;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    *result = (Term*)realloc(*result, (k + 1) * sizeof(Term));
                    (*result)[k++] = (Term){r, c, val};
                }
            }
        }
    }

    return k;
}

// Function to print compact matrix
void printCompactMatrix(Term* compact, int size) {
    printf("Row\tCol\tValue\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%d\t%d\n", compact[i].row, compact[i].col, compact[i].value);
    }
}

// Main function
int main() {
    int r1, c1, r2, c2;

    printf("Enter number of rows of Matrix A: ");
    scanf("%d", &r1);
    printf("Enter number of columns of Matrix A: ");
    scanf("%d", &c1);
    
    printf("Enter number of rows of Matrix B: ");
    scanf("%d", &r2);
    printf("Enter number of columns of Matrix B: ");
    scanf("%d", &c2);

    if (c1 != r2) {
        printf("Matrix multiplication not possible: incompatible dimensions.\n");
        return 1;
    }

    // Allocate and input Matrix A
    int** A = (int**)malloc(r1 * sizeof(int*));
    for (int i = 0; i < r1; i++) {
        A[i] = (int*)malloc(c1 * sizeof(int));
    }

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            printf("Element[%d][%d]: ", i, j);  // Zero index
            scanf("%d", &A[i][j]);
        }
    }

    // Allocate and input Matrix B
    int** B = (int**)malloc(r2 * sizeof(int*));
    for (int i = 0; i < r2; i++) {
        B[i] = (int*)malloc(c2 * sizeof(int));
    }

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            printf("Element[%d][%d]: ", i, j);  // Zero index
            scanf("%d", &B[i][j]);
        }
    }

    // Convert to compact
    Term *compactA, *compactB, *result;
    int sizeA = convertToCompact(r1, c1, A, &compactA);
    int sizeB = convertToCompact(r2, c2, B, &compactB);

    // Multiply
    int resultSize = multiplyCompactMatrices(compactA, sizeA, compactB, sizeB, &result);

    // Output result
    printf("\nResultant Compact Matrix (A X B):\n");
    if (resultSize > 0) {
        printCompactMatrix(result, resultSize);
    } else {
        printf("Result matrix is empty (all zeroes).\n");
    }

    // Free memory
    for (int i = 0; i < r1; i++) {
        free(A[i]);
    }
    for (int i = 0; i < r2; i++) {
        free(B[i]);
    }
    free(A);
    free(B);
    free(compactA);
    free(compactB);
    free(result);

    return 0;
}