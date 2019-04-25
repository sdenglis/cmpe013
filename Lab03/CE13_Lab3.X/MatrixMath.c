/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 03         *
 *4/22/2019      *
 *****************/

// Standard libraries:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// User libraries:
#include "MatrixMath.h"

#define TRUE 1
#define FALSE 0

/******************************************************************************
 * MATRIX - FUNCTION DEFINITIONS
 *****************************************************************************/
// Hey, welcome to my MatrixMath.c page!
// Feel free to snoop around, hopefully everything looks nice and tidy.
//
// LAST COMPILED: Apr 24 2019   20:30:46
// BUILD SUCCESSFUL  (total time: 125ms)
// NO additional errors (this acts iffy sometimes, without cause).

/******************************************************************************
 * MATRIX - Print Matrix
 *****************************************************************************/
void MatrixPrint(float mat[3][3])
{
    int r, c; // Row and column counters.

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            printf("%+f ", mat[r][c]);
        }
        printf("\n");
    }
}

/******************************************************************************
 * MATRIX - Print Sub-matrix
 *****************************************************************************/
void MatrixPrintSubmatrix(float mat[2][2])
{
    int r, c; // Row and column counters.

    for (r = 0; r < (DIM - 1); r++) {
        for (c = 0; c < (DIM - 1); c++) {
            printf("%+f ", mat[r][c]);
        }
        printf("\n");
    }
}

/******************************************************************************
 * MATRIX - Matrix Equals
 *****************************************************************************/
int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    float deltaTest; // Stores difference of mat1 & mat2.
    int r, c; // Row and column counters.

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            deltaTest = mat1[r][c] - mat2[r][c];
            deltaTest = abs(deltaTest);
            if (deltaTest > FP_DELTA) {
                return 0; // Return FALSE(0) if any of the matrix values are unequal.
            }
        }
    }
    return 1; // Else, return TRUE(1).
}

/******************************************************************************
 * MATRIX - Scalar Equals
 *****************************************************************************/
int ScalarEquals(float scalar1, float scalar2)
{
    float deltaTest; // Stores difference of scalar1 & scalar2.

    deltaTest = scalar1 - scalar2;
    deltaTest = abs(deltaTest);
    if (deltaTest > FP_DELTA) {
        return 0; // Return FALSE(0) if any of the matrix values are unequal.
    }
    return 1; // Else, return TRUE(1).
}

/******************************************************************************
 * MATRIX - Matrix Add
 *****************************************************************************/
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int r, c; // Row and column counters.

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = (mat1[r][c]) + (mat2[r][c]);
        }
    }
}

/******************************************************************************
 * MATRIX - Matrix Multiply
 *****************************************************************************/
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    float runningSum = 0;
    int r, c, outer; // Row and column counters + outer counter.

    for (outer = 0; outer < DIM; outer++) {
        for (c = 0; c < DIM; c++) {
            for (r = 0; r < DIM; r++) {
                runningSum += (mat1[r][outer]) * (mat2[c][r]);
            }
            result[c][outer] = runningSum;
            runningSum = 0;
        }
    }
}

/******************************************************************************
 * MATRIX - Scalar Add
 *****************************************************************************/
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    int r, c; // Row and column counters.

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = (mat[r][c]) + (x);
        }
    }
}

/******************************************************************************
 * MATRIX - Scalar Multiply
 *****************************************************************************/
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    int r, c; // Row and column counters.

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = (mat[r][c]) * (x);
        }
    }
}

/******************************************************************************
 * MATRIX - Matrix Trace
 *****************************************************************************/
float MatrixTrace(float mat[3][3])
{
    float trace = 0;
    int r, c; // Row and column counters.

    for (r = 0, c = 0; r < DIM; r++, c++) {
        trace += (mat[r][c]);
    }
    return trace;
}

/******************************************************************************
 * MATRIX - Matrix Transpose
 *****************************************************************************/
void MatrixTranspose(float mat[3][3], float result[3][3])
{
    int r, c; // Row and column counters.

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[c][r] = mat[r][c];
            // Reverse storage order to for resulting array.
        }
    }
}

/******************************************************************************
 * MATRIX - Sub-matrix
 *****************************************************************************/
void MatrixSubmatrix(int i, int j, float mat[3][3], float Result[2][2])
{
    // Values here had to be hard-coded.
    // Only function WITHOUT implementation of loops to expedite process.

    if (i == 0 && j == 0) {
        Result[0][0] = mat[1][1];
        Result[1][0] = mat[2][1];
        Result[0][1] = mat[1][2];
        Result[1][1] = mat[2][2];
    }
    if (i == 1 && j == 0) {
        Result[0][0] = mat[0][1];
        Result[1][0] = mat[2][1];
        Result[0][1] = mat[0][2];
        Result[1][1] = mat[2][2];
    }
    if (i == 2 && j == 0) {
        Result[0][0] = mat[0][1];
        Result[1][0] = mat[1][1];
        Result[0][1] = mat[0][2];
        Result[1][1] = mat[1][2];
    }
    if (i == 0 && j == 1) {
        Result[0][0] = mat[1][0];
        Result[1][0] = mat[2][0];
        Result[0][1] = mat[1][2];
        Result[1][1] = mat[2][2];
    }
    if (i == 1 && j == 1) {
        Result[0][0] = mat[0][0];
        Result[1][0] = mat[2][0];
        Result[0][1] = mat[0][2];
        Result[1][1] = mat[2][2];
    }
    if (i == 2 && j == 1) {
        Result[0][0] = mat[0][0];
        Result[1][0] = mat[1][0];
        Result[0][1] = mat[0][2];
        Result[1][1] = mat[1][2];
    }
    if (i == 0 && j == 2) {
        Result[0][0] = mat[1][0];
        Result[1][0] = mat[2][0];
        Result[0][1] = mat[1][1];
        Result[1][1] = mat[2][1];
    }
    if (i == 1 && j == 2) {
        Result[0][0] = mat[0][0];
        Result[1][0] = mat[2][0];
        Result[0][1] = mat[0][1];
        Result[1][1] = mat[2][1];
    }
    if (i == 2 && j == 2) {
        Result[0][0] = mat[0][0];
        Result[1][0] = mat[1][0];
        Result[0][1] = mat[0][1];
        Result[1][1] = mat[1][1];
    }
}

/******************************************************************************
 * MATRIX - Matrix Determinant
 *****************************************************************************/
float MatrixDeterminant(float mat[3][3])
{
    float runningSum = 0;
    float Result[2][2] = {};
    int i, j;

    MatrixSubmatrix(i = 0, j = 0, mat, Result);
    runningSum += mat[0][0] * ((Result[0][0] * Result[1][1]) - (Result[1][0] * Result[0][1]));

    MatrixSubmatrix(i = 1, j = 0, mat, Result);
    runningSum -= mat[1][0] * ((Result[0][0] * Result[1][1]) - (Result[1][0] * Result[0][1]));

    MatrixSubmatrix(i = 2, j = 0, mat, Result);
    runningSum += mat[2][0] * ((Result[0][0] * Result[1][1]) - (Result[1][0] * Result[0][1]));

    return runningSum;
}

/******************************************************************************
 * MATRIX - Inverse Matrix
 *****************************************************************************/
void MatrixInverse(float mat[3][3], float result[3][3])
{
    float Result[2][2] = {};
    float inverseResult[3][3] = {};
    int r, c; // Row and column counters.
    // First, transpose the input matrix.
    MatrixTranspose(mat, result);

    // Check if the determinant == 0, if so, return all zero matrix.
    if ((MatrixDeterminant(mat) == 0)) {
        for (r = 0; r < DIM; r++) {
            for (c = 0; c < DIM; c++) {
                result[r][c] = 0;
            }
        }
        return;
    }

    // Otherwise, continue to set the new matrix to each of the sub-matrices of the input.
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            MatrixSubmatrix(r, c, mat, Result);
            float runningSum = 0;
            if ((r + c) % 2 == 0) {
                runningSum = ((Result[0][0] * Result[1][1]) - (Result[1][0] * Result[0][1]));
                result[r][c] = (runningSum);
            } else {
                runningSum = ((Result[0][0] * Result[1][1]) - (Result[1][0] * Result[0][1]));
                result[r][c] = -(runningSum);
            }
        }
    }

    // Divide each element by the original determinant.
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = (result[r][c]) / (MatrixDeterminant(mat));
        }
    }

    // Finally, set what was calculated back to the output for the function call.
    MatrixTranspose(result, inverseResult);
    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = ((inverseResult[r][c]));
        }
    }
}


