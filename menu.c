#include <stdio.h>
#include <stdbool.h>
#include "matrix.h"


void askforMatrixSize(int matrixId) {
    printf("Enter number of rows and columns of matrix #%d:\n", matrixId);
}

void askforMatrixElements(int matrixId) {
    printf("Enter elements of matrix #%d:\n", matrixId);
}

bool checkSizeValues(int nRows, int nColumns) {
    return nRows > 0 && nColumns > 0;
}

bool checkIfSquare(int nRows, int nColumns) {
    return nRows == nColumns;
}

int main() {
    int option = 0;
    int nRows1 = 0;
    int nColumns1 = 0;
    int nRows2 = 0;
    int nColumns2 = 0;
    double** matrix1;
    double** matrix2;
    double** resMatrix;
    
    do {
        printf("\nChoose an option from the menu below:\n"
            "0 - Exit program\n"
            "1 - Addition of two matrices\n"
            "2 - Subtraction of two matrices\n"
            "3 - Multiplication of a matrix by a scalar\n"
            "4 - Multiplication of two matrices\n"
            "5 - Calculate the determinant of a matrix\n"
            "6 - Calculate the transpose of a matrix\n"
            "7 - Calculate the cofactors matrix of a matrix\n"
            "8 - Calculate the inverse of a matrix\n"
            "9 - Create an identity matrix nxn\n"
            "10 - Join two matrices to make and augmented matrix\n");
        
        scanf(" %d", &option);

        switch (option)
        {
        case 0:
            break;

        case 1: // addition
        
            // create and input first matrix
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            matrix1 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(1);
            inputMatrix(matrix1, nRows1, nColumns1);

            // create and input second matrix
            matrix2 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(2);
            inputMatrix(matrix2, nRows1, nColumns1);

            resMatrix = sumMatrices(matrix1, matrix2, nRows1, nColumns1);
            printMatrix(resMatrix, nRows1, nColumns1);

            break;

        case 2: // subtraction
        
            // create and input first matrix
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            matrix1 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(1);
            inputMatrix(matrix1, nRows1, nColumns1);

            // create and input second matrix
            matrix2 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(2);
            inputMatrix(matrix2, nRows1, nColumns1);

            resMatrix = subtractionMatrices(matrix1, matrix2, nRows1, nColumns1);
            printMatrix(resMatrix, nRows1, nColumns1);

            break;

        case 3:; // scalar multiplication

            // get scalar
            double scalar = 0;
            printf("Enter the scalar: ");
            scanf(" %lf", &scalar);
        
            // create and input matrix
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            matrix1 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(1);
            inputMatrix(matrix1, nRows1, nColumns1);

            resMatrix = scalarMatrixMultiplication(
                scalar, matrix1, nRows1, nColumns1
            );
            printMatrix(resMatrix, nRows1, nColumns1);

            break;

        case 4: // matrix multiplication
        
            // create and input first matrix
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            matrix1 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(1);
            inputMatrix(matrix1, nRows1, nColumns1);

            // create and input second matrix
            askforMatrixSize(2);
            scanf(" %d %d", &nRows2, &nColumns2);

            if (!checkSizeValues(nRows2, nColumns2)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            matrix2 = createMatrix(nRows2, nColumns2);
            askforMatrixElements(2);
            inputMatrix(matrix2, nRows2, nColumns2);

            resMatrix = multiplyMatrices(
                matrix1, nRows1, nColumns1, 
                matrix2, nRows2, nColumns2
            );
            printMatrix(resMatrix, nRows1, nColumns2);

            break;

        case 5: // determinant

            // create and input matrix
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            if (!checkIfSquare(nRows1, nColumns1)) {
                printf("Only square matrices have determinants.\n");
                break;
            }

            matrix1 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(1);
            inputMatrix(matrix1, nRows1, nColumns1);

            double det = determinant(matrix1, nRows1);
            printf("%.2lf\n", det);

            break;

        case 6: // transpose of a matrix

            // create and input matrix
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            matrix1 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(1);
            inputMatrix(matrix1, nRows1, nColumns1);

            resMatrix = transposeMatrix(matrix1, nRows1, nColumns1);
            printMatrix(resMatrix, nRows1, nColumns1);

            break;

        case 7: // cofactors matrix

            // create and input matrix
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            if (!checkIfSquare(nRows1, nColumns1)) {
                printf("Only square matrices have a cofactors matrix.\n");
                break;
            }

            matrix1 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(1);
            inputMatrix(matrix1, nRows1, nColumns1);

            resMatrix = cofactorsMatrix(matrix1, nRows1);
            printMatrix(resMatrix, nRows1, nColumns1);

            break;

        case 8: // inverse matrix

            // create and input matrix
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            if (!checkIfSquare(nRows1, nColumns1)) {
                printf("Only square matrices can have an inverse matrix.\n");
                break;
            }

            matrix1 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(1);
            inputMatrix(matrix1, nRows1, nColumns1);

            resMatrix = inverseMatrix(matrix1, nRows1);
            if (resMatrix == NULL) {
                printf("This matrix doesn't have an inverse.\n");
            } else {
                printMatrix(resMatrix, nRows1, nColumns1);
            }
            
            break;

        case 9: // identity matrix

            // ask for size
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            if (!checkIfSquare(nRows1, nColumns1)) {
                printf("Only square matrices can be identity matrix.\n");
                break;
            }

            matrix1 = indentityMatrix(nRows1);
            printMatrix(matrix1, nRows1, nRows1);

            break;

        case 10: // augmented matrix

            // create and input first matrix
            askforMatrixSize(1);
            scanf(" %d %d", &nRows1, &nColumns1);

            if (!checkSizeValues(nRows1, nColumns1)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            matrix1 = createMatrix(nRows1, nColumns1);
            askforMatrixElements(1);
            inputMatrix(matrix1, nRows1, nColumns1);

            // create and input second matrix
            askforMatrixSize(2);
            scanf(" %d %d", &nRows2, &nColumns2);

            if (!checkSizeValues(nRows2, nColumns2)) {
                printf("Sizes must be positive integers.\n");
                break;
            }

            matrix2 = createMatrix(nRows2, nColumns2);
            askforMatrixElements(2);
            inputMatrix(matrix2, nRows2, nColumns2);

            resMatrix = augmentedMatrix(
                matrix1, nRows1, nColumns1, 
                matrix2, nRows2, nColumns2
            );
            printMatrix(resMatrix, nRows1, nColumns1 + nColumns2);

            break;
            
        default:
            printf("Invalid option\n");
            break;
        }

    } while (option != 0);
    
    
    return 0;
}