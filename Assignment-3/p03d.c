#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, col, value;
} Term;

// Convert a 2D matrix to compact form
int convertToCompact(int rows, int cols, int **matrix, Term **compact) {
    int count = 0;
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
                (*compact)[k++] = (Term){i, j, matrix[i][j]};
            }
        }
    }

    return k;
}

// Add two compact matrices
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
            i++;
            j++;
        } else if (a[i].row < b[j].row || (a[i].row == b[j].row && a[i].col < b[j].col)) {
            (*result)[k++] = a[i++];
        } else {
            (*result)[k++] = b[j++];
        }
    }

    while (i < sizeA) {
        (*result)[k++] = a[i++];
    }
    while (j < sizeB) {
        (*result)[k++] = b[j++];
    }

    return k;
}

// Multiply two compact matrices
int multiplyCompactMatrices(Term *a, int sizeA, Term *b, int sizeB, Term **result) {
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
                    *result = (Term *)realloc(*result, (k + 1) * sizeof(Term));
                    (*result)[k++] = (Term){r, c, val};
                }
            }
        }
    }

    return k;
}

// Print compact matrix
void printCompactMatrix(Term *compact, int size) {
    printf("Row\tColumn\tValue\n");
    for (int i = 0; i < size; i++)
        printf("%d\t%d\t%d\n", compact[i].row, compact[i].col, compact[i].value);
}

int **allocateMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(cols * sizeof(int));
    return matrix;
}

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Main function
int main() {
    int r1, c1, r2, c2;

    // Read Matrix A
    FILE *fileA = fopen("matrix1.txt", "r");
    if (!fileA) { perror("Error opening file matrix1.txt"); return 1; }
    fscanf(fileA, "%d %d", &r1, &c1);
    int **A = allocateMatrix(r1, c1);
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            fscanf(fileA, "%d", &A[i][j]);
        }
    }
    fclose(fileA);

    // Convert Matrix A to compact
    Term *compactA;
    int sizeA = convertToCompact(r1, c1, A, &compactA);

    // Read Matrix B
    FILE *fileB = fopen("matrix2.txt", "r");
    if (!fileB) {
        perror("Error opening file matrix2.txt");
        return 1;
    }
    fscanf(fileB, "%d %d", &r2, &c2);
    int **B = allocateMatrix(r2, c2);
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            fscanf(fileB, "%d", &B[i][j]);
        }
    }
    fclose(fileB);

    // Convert Matrix B to compact
    Term *compactB;
    int sizeB = convertToCompact(r2, c2, B, &compactB);

    // Attempt addition if dimensions match
    if (r1 == r2 && c1 == c2) {
        Term *sumResult;
        int sumSize = addCompactMatrices(compactA, sizeA, compactB, sizeB, &sumResult);
        printf("\nResultant Compact Matrix (A + B):\n");
        printCompactMatrix(sumResult, sumSize);
        free(sumResult);
    } else {
        printf("\nAddition not possible due to incompatible dimensions.\n");
    }

    // Attempt multiplication if dimensions are compatible
    if (c1 == r2) {
        Term *mulResult;
        int mulSize = multiplyCompactMatrices(compactA, sizeA, compactB, sizeB, &mulResult);
        printf("\nResultant Compact Matrix (A x B):\n");
        if (mulSize > 0) {
            printCompactMatrix(mulResult, mulSize);
        } else {
            printf("Result matrix is empty (all zeroes).\n");
        }
        free(mulResult);
    } else {
        printf("\nMultiplication not possible due to incompatible dimensions.\n");
    }

    // Free memory
    freeMatrix(A, r1);
    freeMatrix(B, r2);
    free(compactA);
    free(compactB);

    return 0;
}