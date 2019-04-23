#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "MatrixMath.h"

void MatrixPrint(float mat[3][3])
{
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            printf("%+f ", mat[r][c]);
        }
        printf("\n");
    }
}

int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    float deltaTest; // Stores difference of mat1 & mat2
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            deltaTest = mat1[r][c] - mat2[r][c];
            deltaTest = abs(deltaTest);
            if (deltaTest > FP_DELTA) {
                return 1; // Return TRUE if any of the matrix values are unequal
            }
        }
    }
    return 0; // Else, return false
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = (mat1[r][c]) + (mat2[r][c]);
        }
    }
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    float runningSum = 0;
    int r, c, outer; // Row and column counters + outer counter

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

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = (mat[r][c]) + (x);
        }
    }
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[r][c] = (mat[r][c]) * (x);
        }
    }
}

float MatrixTrace(float mat[3][3])
{
    float trace = 0;
    int r, c; // Row and column counters

    for (r = 0, c = 0; r < DIM; r++, c++) {
        trace += (mat[r][c]);
    }
    return trace;
}

void MatrixTranspose(float mat[3][3], float result[3][3])
{
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM; c++) {
            result[c][r] = mat[r][c];
            // Reverse storage order to for resulting array
        }
    }
}

void MatrixSubmatrix(int i, int j, float mat[3][3], float Result[2][2])
{
    // Don't forget that the i, j, k positions act as coefficients for the 2x2 submatrices.

    if (i == 0) {
        Result[0][0] = mat[1][1];
        Result[1][0] = mat[2][1];
        Result[0][1] = mat[1][2];
        Result[1][1] = mat[2][2];
    }
    if (i == 1) {
        Result[0][0] = mat[0][1];
        Result[1][0] = mat[2][1];
        Result[0][1] = mat[0][2];
        Result[1][1] = mat[2][2];
    }
    if (i == 2) {
        Result[0][0] = mat[0][1];
        Result[1][0] = mat[1][1];
        Result[0][1] = mat[0][2];
        Result[1][1] = mat[1][2];
    }
}

float MatrixDeterminant(float mat[3][3])
{
    float runningSum = 0;
    float Result[2][2] = {};
    int i, j;

    MatrixSubmatrix(i = 0, j = 0, mat, Result);
    runningSum += mat[0][0] * ((Result[0][0] * Result[1][1]) - (Result[1][0] * Result[0][1]));

    MatrixSubmatrix(i = 1, j, mat, Result);
    runningSum -= mat[1][0] * ((Result[0][0] * Result[1][1]) - (Result[1][0] * Result[0][1]));

    MatrixSubmatrix(i = 2, j, mat, Result);
    runningSum += mat[2][0] * ((Result[0][0] * Result[1][1]) - (Result[1][0] * Result[0][1]));
    
    return 0;
}

