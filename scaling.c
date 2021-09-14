#include <stdio.h>
#include "matrix.h"

int main() {
    int option = 0;
    int nRows = 0;
    int nColumns = 0;
    int rowA = 0;
    int rowB = 0;
    double scalar = 0;
    double** matrix;

    printf("Enter the matrix's number of rows and columns:\n");
    scanf("%d %d", &nRows, &nColumns);
    fflush(stdin);

    matrix = createMatrix(nRows, nColumns);

    printf("Enter the matrix's elements:\n");
    inputMatrix(matrix, nRows, nColumns);

    do {
        printf("\nChoose an option from the menu below:\n"
                "0 - Exit program\n"
                "1 - Swap two rows\n"
                "2 - Multiply row by scalar\n"
                "3 - Multiply row by scalar and add to another row\n");
        
        scanf(" %d", &option);
        fflush(stdin);

        switch (option)
        {
        case 0:
            break;

        case 1:
            printf("Enter the indexes of rows to be swapped \n"
                    "(first row is row 0):");
            scanf(" %d %d", &rowA, &rowB);
            fflush(stdin);

            swapLines(rowA, rowB, matrix, nColumns);
            printMatrix(matrix, nRows, nColumns);

            break;

        case 2:
            printf("Enter the row to be multiplied followed by the scalar "
                    "by which to multiply row (first row is row 0):\n");
            scanf(" %d %lf", &rowA, &scalar);
            fflush(stdin);

            multiplyLine(scalar, rowA, matrix, nColumns);
            printMatrix(matrix, nRows, nColumns);

            break;

        case 3:
            printf("Enter the row to be multiplied followed by the scalar "
                    "by which to multiply row, then the row to which add "
                    "the result (first row is row 0):\n");
            scanf(" %d %lf %d", &rowA, &scalar, &rowB);
            fflush(stdin);

            sumLineMultiple(scalar, rowA, rowB, matrix, nColumns);
            printMatrix(matrix, nRows, nColumns);

            break;
        
        default:
            printf("Invalid option.\n");
            break;
        }

        
    } while (option != 0);
    
    
    return 0;
}