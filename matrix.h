/*
matrix.h
author: Gabriel Bergoc
started: 2021-08-23

objective: basic matrix manipulations

already has:
- createMatrix (to dynamically allocate a 2D matrix)
- inputMatrix (to fill a matrix)
- printMatrix (to make pancakes... lol jk it prints a matrix)
- matrix multiplication
- determinant
- transpose of a matrix
- cofactors matrix
- inverse matrix

to do:


*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>


double** createMatrix(int nRows, int nColumns);
void inputMatrix(double** matrix, int nRows, int nColumns);
void printMatrix(double** matrix, int nRows, int nColumns);
double** sumMatrices(double** matrixA, double** matrixB, int nRows, int nColumns);
double** subtractionMatrices(double** matrixA, double** matrixB, int nRows, int nColumns);
double** scalarMatrixMultiplication(double scalar, double** matrix, int nRows, int nColumns);
double** multiplyMatrices(
    double** matrixA, int nRowsA, int nColumnsA, 
    double** matrixB, int nRowsB, int nColumnsB
    );
double** cutMatrix(double** matrix, int nRows, int excluded_i, int excluded_j);
double determinant(double** matrix, int nRows);
double** transposeMatrix(double** matrix, int nRows, int nColumns);
double** cofactorsMatrix(double** matrix, int nRows);
double** inverseMatrix(double** matrix, int nRows);
double** indentityMatrix(int nRows);
double** augmentedMatrix(
    double** matrixA, int nRowsA, int nColumnsA,
    double** matrixB, int nRowsB, int nColumnsB
    );
void swapLines(int rowA, int rowB, double** matrix, int nColumns);
void multiplyLine(double scalar, int row, double** matrix, int nColumns);
void sumLineMultiple(double scalar, int rowA, int rowB, double** matrix, int nColumns);
bool compareMatrices(double** matrixA, double** matrixB, int nRows, int nColumns);
bool noNullRows(double** matrix, int nRows, int nColumns);
void inverseMatrix2(double** matrix, int nRows);    // work in progress


// returns a pointer to an array of pointers to doubles
// all elements are initialized to 0
double** createMatrix(int nRows, int nColumns) {

    double** matrix = (double**)calloc(nRows, sizeof(double *));

    if (matrix == NULL) {
        printf("Error: insuficient memory\nPress any key to exit...");
        _getch();
        exit(1);
    }
    
    for (int i = 0; i < nRows; i++) {
        *(matrix + i) = (double *)calloc(nColumns, sizeof(double));
        if (*(matrix + i) == NULL) {
            printf("Error: insuficient memory\nPress any key to exit...");
            _getch();
            exit(1);
        }
    }

    return matrix;
}

void inputMatrix(double** matrix, int nRows, int nColumns) {

    if (matrix == NULL) {
        printf("There's no such matrix.\n");
    } else {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nColumns; j++) {
                scanf(" %lf", *(matrix + i) + j);
            }
        }
    }   
}

void printMatrix(double** matrix, int nRows, int nColumns) {

    if (matrix == NULL) {
        printf("There's no such matrix.\n");
    } else {
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nColumns; j++) {
                printf("%.4lf ", *(*(matrix + i) + j));
            }
            printf("\n");
        }
        printf("\n");
    }
}

// returns a pointer to a matrix that is the sum of two matrices
double** sumMatrices(double** matrixA, double** matrixB, int nRows, int nColumns) {
    
    double** resMatrix = createMatrix(nRows, nColumns);

    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            *(*(resMatrix + i) + j) = *(*(matrixA + i) + j) + *(*(matrixB + i) + j);
        }
    }

    return resMatrix;
}

// returns a pointer to a matrix that is the subtraction of two matrices
double** subtractionMatrices(double** matrixA, double** matrixB, int nRows, int nColumns) {
    
    double** resMatrix = createMatrix(nRows, nColumns);

    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            *(*(resMatrix + i) + j) = *(*(matrixA + i) + j) - *(*(matrixB + i) + j);
        }
    }

    return resMatrix;
}

// returns a pointer to a matrix multiplied by a scalar
double** scalarMatrixMultiplication(double scalar, double** matrix, int nRows, int nColumns) {
    
    double** resMatrix = createMatrix(nRows, nColumns);
    
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            *(*(resMatrix + i) + j) = *(*(matrix + i) + j) * scalar;
        }
    }

    return resMatrix;
}

// returns a pointer to a matrix which is the product between matrices A and B
double** multiplyMatrices(
    double** matrixA, int nRowsA, int nColumnsA, 
    double** matrixB, int nRowsB, int nColumnsB
    ) {

    if (nColumnsA != nRowsB) {
        printf("Error: matrix multiplication is defined only between two "
                "matrices when the number of columns of the first is equal "
                "to the number of rows of the second.\n"
                "Press any key to exit...");
        _getch();
        exit(1);
    }
    
    double** matrixC = createMatrix(nRowsA, nColumnsB);

    for (int i = 0; i < nRowsA; i++) {
        for (int j = 0; j < nColumnsB; j++) {
            for (int k = 0; k < nRowsB; k++) {
                *(*(matrixC + i) + j) += *(*(matrixA + i) + k) * *(*(matrixB + k) + j);
            }
        }
    }

    return matrixC;
}

// removes a row and a column from a matrix, returns a pointer to resulting matrix
double** cutMatrix(double** matrix, int nRows, int excluded_i, int excluded_j) {
    
    double** miniMatrix = createMatrix(nRows - 1, nRows - 1);

    for (int i = 0, k = 0; i < nRows; i++) {
        bool atr = false;
        if (i == excluded_i) {
            continue;
        }
        for (int j = 0, l = 0; j < nRows; j++) {
            if (j == excluded_j) {
                continue;
            }
            *(*(miniMatrix + k) + l) = *(*(matrix + i) + j);
            l++;
            atr = true;
        }
        if (atr) {
            k++;
            atr = false;
        }
    }

    return miniMatrix;
}

// returns the determinant of any square matrix
// algorithm: Laplace expansion
// complexity: O(n!)
double determinant(double** matrix, int nRows) {
    
    if (nRows == 1) {
        return** matrix;
    }

    double det = 0;

    for (int i = 0; i < nRows; i++) {
        double** smallMatrix = cutMatrix(matrix, nRows, 0, i);
        if (*(*(matrix) + i) == 0) {
            continue;
        }
        det += pow(-1, 1 + (i + 1)) * determinant(smallMatrix, nRows - 1) * *(*(matrix) + i);
    }

    return det;
}

// returns a pointer to a matrix that is the transpose of original matrix
double** transposeMatrix(double** matrix, int nRows, int nColumns) {
    
    double** resMatrix = createMatrix(nRows, nColumns);

    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            *(*(resMatrix + i) + j) = *(*(matrix + j) + i);
        }
    }

    return resMatrix;
}

// returns a pointer to the cofactor matrix of original matrix
double** cofactorsMatrix(double** matrix, int nRows) {
    
    double** resMatrix = createMatrix(nRows, nRows);

    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nRows; j++) {
            double** miniMatrix = cutMatrix(matrix, nRows, i, j);
            *(*(resMatrix + i) + j) = pow(-1, (i + 1) + (j + 1)) * determinant(miniMatrix, nRows - 1);
        }
    }

    return resMatrix;
}

// returns a pointer to inverse matrix, or NULL pointer if there's no inverse
double** inverseMatrix(double** matrix, int nRows) {
    
    double det = determinant(matrix, nRows);
    if (det == 0) {
        return NULL;
    }

    double** cofactors = cofactorsMatrix(matrix, nRows);
    double** adjugate = transposeMatrix(cofactors, nRows, nRows);
    
    return scalarMatrixMultiplication(1 / det, adjugate, nRows, nRows);
}

double** indentityMatrix(int nRows) {
    double** matrix = createMatrix(nRows, nRows);

    for (int i = 0; i < nRows; i++) {
        *(*(matrix + i) + i) = 1;
    }

    return matrix;
}

double** augmentedMatrix(
    double** matrixA, int nRowsA, int nColumnsA, 
    double** matrixB, int nRowsB, int nColumnsB
    ) {
    
    if (nRowsA != nRowsB) {
        printf("Error: Only matrices with same number of rows can be augmented.\b");
        return NULL;
    }

    double** resMatrix = createMatrix(nRowsA, nColumnsA + nColumnsB);

    for (int i = 0; i < nRowsA; i++) {
        for (int j = 0; j < nColumnsA; j++) {
            *(*(resMatrix + i) + j) = *(*(matrixA + i) + j);
        }
    }

    for (int i = 0; i < nRowsB; i++) {
        for (int j = 0; j < nColumnsB; j++) {
            *(*(resMatrix + i) + j + nColumnsA) = *(*(matrixB + i) + j);
        }
    }

    return resMatrix;

}

void swapLines(int rowA, int rowB, double** matrix, int nColumns) {

    double* temp = (double*) calloc(nColumns, sizeof(double));

    for (int i = 0; i < nColumns; i++) {
        *(temp + i) = *(*(matrix + rowA) + i);
    }

    for (int i = 0; i < nColumns; i++) {
        *(*(matrix + rowA) + i) = *(*(matrix + rowB) + i);
    }

    for (int i = 0; i < nColumns; i++) {
        *(*(matrix + rowB) + i) = *(temp + i);
    }
}

void multiplyLine(double scalar, int row, double** matrix, int nColumns) {

    for (int i = 0; i < nColumns; i++) {
        *(*(matrix + row) + i) *= scalar;
    }
}

void sumLineMultiple(double scalar, int rowA, int rowB, double** matrix, int nColumns) {
    for (int i = 0; i < nColumns; i++) {
        *(*(matrix + rowB) + i) += *(*(matrix + rowA) + i) * scalar;
    }
}

bool compareMatrices(double** matrixA, double** matrixB, int nRows, int nColumns) {
    bool isEqual = true;

    for (int i = 0; i < nRows && isEqual; i++) {
        for (int j = 0; j < nColumns && isEqual; j++) {
            if (*(*(matrixA + i) + j) != *(*(matrixB + i) + j)) {
                isEqual = false;
            }
        }
    }

    return isEqual;
}

bool noNullRows(double** matrix, int nRows, int nColumns) {
    bool hasntNullRow = true;

    for (int i = 0; i < nRows && hasntNullRow; i++) {
        bool rowIsNull = true;

        for (int j = 0; j < nColumns && rowIsNull; j++) {
            if (*(*(matrix + i) + j) != 0) {
                rowIsNull = false;
            }
        }

        if (rowIsNull) {
            hasntNullRow = false;
        }
    }

    return hasntNullRow;
}

void inverseMatrix2(double** matrix, int nRows) {

    bool hasNullRow = !noNullRows(matrix, nRows, nRows);
    if (hasNullRow) {
        return;
    }

    double** resMatrix;
    double** identity = indentityMatrix(nRows);
    resMatrix = augmentedMatrix(matrix, nRows, nRows, 
                                identity, nRows, nRows);
    
    int i = 0;
    while (compareMatrices(resMatrix, identity, nRows, nRows)) {
        hasNullRow = !noNullRows(matrix, nRows, nRows);
        if (hasNullRow) {
            return;
        }
    }
}