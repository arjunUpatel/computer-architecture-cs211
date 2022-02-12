#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

unsigned int cost(
    unsigned int matrixCount,
    unsigned int *rowSizes,
    unsigned int *colSizes)
{
    if (matrixCount == 1)
    {             // Base case.
        return 0; // No multplication to be done.
    }
    else
    {

        unsigned int numPossibleSplits = matrixCount - 1; // if there are two matrices to multiply, there is one way to split.
        // AB: (A)(B)
        // ABC: (A)(BC) and (AB)(C)
        unsigned int costs[numPossibleSplits];
        for (unsigned int split = 0; split < numPossibleSplits; split++)
        {

            unsigned int l = rowSizes[0];
            if (colSizes[split] == rowSizes[split + 1])
            {
                unsigned int m = colSizes[split];
                unsigned int n = colSizes[matrixCount - 1];

                costs[split] =
                    cost(split + 1, rowSizes, colSizes) +                                      // cost of left subchain
                    l * m * n +                                                                // cost of multiplying the two chains
                    cost(matrixCount - split - 1, rowSizes + split + 1, colSizes + split + 1); // cost of right subchain
            }
        }

        unsigned int minCost = costs[0];
        for (unsigned int split = 1; split < numPossibleSplits; split++)
        {
            if (costs[split] < minCost)
            {
                minCost = costs[split];
            }
        }

        return minCost;
    }
}

void matMul(
    unsigned int l, // num of rows in mat A
    unsigned int m, // num of cols in mat A and num of rows in mat B
    unsigned int n, // num of rows in mat B
    int **matrix_a,
    int **matrix_b,
    int **matMulProduct)
{
    for (unsigned int i = 0; i < l; i++)
    {
        for (unsigned int k = 0; k < n; k++)
        {
            matMulProduct[i][k] = 0;
            for (unsigned int j = 0; j < m; j++)
            {
                matMulProduct[i][k] += matrix_a[i][j] * matrix_b[j][k];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    unsigned int matrixCount;
    unsigned int *rowSizes;
    unsigned int *colSizes;

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    if (!fscanf(fp, "%d\n", &matrixCount))
    {
        perror("reading the number of matrices failed");
        exit(EXIT_FAILURE);
    }

    rowSizes = (unsigned int *)calloc(matrixCount, sizeof(int));
    colSizes = (unsigned int *)calloc(matrixCount, sizeof(int));

    int ***matrices = (int ***)calloc(matrixCount, sizeof(int **));
    for (unsigned int matIndex = 0; matIndex < matrixCount; matIndex++)
    {
        unsigned int rows, cols;
        if (!fscanf(fp, "%d %d\n", &rows, &cols))
        {
            perror("reading the dimensions of matrix failed");
            exit(EXIT_FAILURE);
        }
        rowSizes[matIndex] = rows;
        colSizes[matIndex] = cols;

        int **matrix = (int **)calloc(rows, sizeof(int *));
        for (unsigned int i = 0; i < rows; i++)
        {
            matrix[i] = (int *)calloc(cols, sizeof(int));
            for (unsigned int j = 0; j < cols; j++)
            {
                unsigned int element;
                if (!fscanf(fp, "%d\n", &element))
                {
                    perror("reading the elements of the matrix failed");
                    exit(EXIT_FAILURE);
                }
                matrix[i][j] = element;
            }
        }
        matrices[matIndex] = matrix;
    }
    printf("%d\n", cost(matrixCount, rowSizes, colSizes));

    unsigned int matA_col = colSizes[0];
    unsigned int matB_col = colSizes[1];
    int **prevRes = (int **)calloc(rowSizes[0], sizeof(int *));
    for (int row = 0; row < rowSizes[0]; row++)
    {
        prevRes[row] = (int *)calloc(matB_col, sizeof(int));
    }

    matMul(rowSizes[0], matA_col, matB_col, matrices[0], matrices[1], prevRes);
    for (int i = 2; i < matrixCount; i++)
    {
        matA_col = matB_col;
        matB_col = colSizes[i];
        int **temp = (int **)calloc(rowSizes[0], sizeof(int *));
        for (int row = 0; row < rowSizes[0]; row++)
        {
            temp[row] = (int *)calloc(matB_col, sizeof(int));
        }
        matMul(rowSizes[0], matA_col, matB_col, prevRes, matrices[i], temp);
        for (int i = 0; i < rowSizes[0]; i++)
        {
            free(*(prevRes + i));
            prevRes[i] = (int *)calloc(matB_col, sizeof(int));
            for (int j = 0; j < matB_col; j++)
            {
                prevRes[i][j] = temp[i][j];
            }
        }
        for (int i = 0; i < rowSizes[0]; i++)
        {
            free(*(temp + i));
        }
        free(temp);
    }

    for (int i = 0; i < rowSizes[0]; i++)
    {
        int *arr = *(prevRes + i);
        for (int j = 0; j < matB_col; j++)
        {
            printf("%d ", *(arr + j));
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < rowSizes[0]; i++)
    {
        free(*(prevRes + i));
    }
    free(prevRes);

    for (int i = 0; i < matrixCount; i++)
    {
        int **mat = *(matrices + i);
        for (int row = 0; row < rowSizes[i]; row++)
        {
            free(*(mat + row));
        }
        free(mat);
    }
    free(matrices);

    free(colSizes);
    free(rowSizes);
    fclose(fp);

    exit(EXIT_SUCCESS);
}
