#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

/**
 * @file
 *
 * @section DESCRIPTION
 *
 * This file implements a basic 3x3 matrix math library. Basic matrix operations are provided along
 * with the matrix inverse function (though that function cannot handle singular matrices).
 *
 * Matrices are defined in row-major order, so that the matrix:
 *   0 1 2
 *   3 4 5
 *   6 7 8
 * is represented by the array `float mat[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};`.
 */

/**
 * FP_DELTA defines the tolerance for testing equality for floating-point numbers. 
 * Used within MatrixEquals() 
 * Also used to compare scalar return values, such as the result of MatrixTrace().
 */
#define FP_DELTA 0.0001

/**
 * To avoid using magic numbers, use this macro to iterate over 3 dimensions:
 *  */
#define DIM 3


/******************************************************************************
 * Matrix Display:
 *****************************************************************************/

/**
 * MatrixPrint displays a 3x3 array to standard output with clean, readable, 
 * consistent formatting.  
 * @param: mat, pointer to a 3x3 float array
 * @return: none
 * The printed matrix should be aligned in a grid when called with positive or
 *  negative numbers.  It should be able to display at least FP_DELTA precision, and
 *  should handle numbers as large as 999.0 or -999.0
 */
void MatrixPrint(float mat[3][3])
{

    float mat [3][3] = {};
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM, c++) {
            printf("%f ", mat[r][c]);
        }
        printf("\n");
    }

    return 0;
}


/******************************************************************************
 * Matrix - Matrix Operations
 *****************************************************************************/

/**
 * MatrixEquals checks if the two matrix arguments are equal (to within FP_DELTA).
 * @param: mat1, pointer to a 3x3 float array
 * @param: mat2, pointer to a 3x3 float array
 * @return: FALSE if every element of mat1 is within FP_DELTA of the corresponding element of mat2
 * Neither mat1 nor mat2 is modified by this function.
 */
int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    float mat1 [3][3] = {};
    float mat2 [3][3] = {};
    float deltaTest; // Stores difference of mat1 & mat2
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM, c++) {
            deltaTest = mat1[r][c] - mat2[r][c];
            if (deltaTest < 0) {
                double deltaTest = (deltaTest * (-1));
            }
        }
        if (FP_DELTA > deltaTest) {
            return TRUE; // Return TRUE if any of the matrix values are unequal
        }
    }
    return FALSE;
}

/**
 * MatrixAdd performs an element-wise matrix addition operation on two 3x3 matrices and 
 * "returns" the result by modifying the third argument.
 * @param: mat1, pointer to a summand 3x3 matrix
 * @param: mat2, pointer to a summand 3x3 matrix
 * @param: result, pointer to a 3x3 matrix that is modified to contain the sum of mat1 and mat2.
 * @return:  None
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    float mat1 [3][3] = {};
    float mat2 [3][3] = {};
    float result [3][3] = {};
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM, c++) {
            result[r][c] = (mat1[r][c]) * (mat2[r][c]);
        }
    }
    return 0;
}

/**
 * MatrixMultiply performs a matrix-matrix multiplication operation on two 3x3
 * matrices and "returns" the result by modifying the third argument.
 * @param: mat1, pointer to left factor 3x3 matrix
 * @param: mat2, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain the matrix product of mat1 and mat2.
 * @return: none
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    float mat1 [3][3] = {};
    float mat2 [3][3] = {};
    float result [3][3] = {};
    float runningSum = 0;
    int r, c, outer; // Row and column counters + outer counter
    for (outer = 0, outer < DIM, ++outer)
        for (c = 0; c < DIM; ++c) {
            for (r = 0; r < DIM, ++r) {
                runningSum += (mat1[r][c]) * (mat2[c][outer]);
            }
            result[r][outer] = runningSum;
            runningSum = 0;
        }
    return 0;
}


/******************************************************************************
 * Matrix - Scalar Operations
 *****************************************************************************/

/**
 * MatrixScalarAdd performs the addition of a matrix and a scalar.  Each element of the matrix is increased by x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    float mat [3][3] = {};
    float result [3][3] = {};
    float x;
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM, c++) {
            result[r][c] = (mat[r][c]) + (x);
        }
    }
    return 0;
}

/**
 * MatrixScalarAdd performs the multiplication of a matrix and a scalar.
 * Each element of the matrix is multiplied x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    float mat [3][3] = {};
    float result [3][3] = {};
    float x;
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM, c++) {
            result[r][c] = (mat[r][c]) * (x);
        }
    }
    return 0;
}


/******************************************************************************
 * Unary Matrix Operations
 *****************************************************************************/

/**
 * MatrixTrace calculates the trace of a 3x3 matrix.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the trace of mat
 */
float MatrixTrace(float mat[3][3])
{
    float mat [3][3] = {};
    float trace = 0;
    int r, c; // Row and column counters

    for (r = 0, c = 0; r < DIM && c < DIM; r++, c++) {
        trace = (mat[r][c]) + trace;
    }
    return trace;
}

/**
 * MatrixTranspose calculates the transpose of a matrix and "returns" the
 * result through the second argument.
 * @param: mat, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to transpose of mat
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixTranspose(float mat[3][3], float result[3][3])
{

    float mat [3][3] = {};
    int r, c; // Row and column counters

    for (r = 0; r < DIM; r++) {
        for (c = 0; c < DIM, c++) {
            result[c][r] = mat[r][c]
                    // Reverse storage order to for resulting array
        }
    }

    return 0;
}

/**
 * MatrixSubmatrix finds a submatrix of a 3x3 matrix that is 
 * formed by removing the i-th row and the j-th column.  The 
 * submatrix is "returned" by modifying the final argument.
 * @param: i, a row of the matrix, indexing from 0
 * @param: j, a column of the matrix, indexing from 0
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 2x2 matrix
 * @return: none
 * mat is not modified by this function.  Result is modified by this function.
 */
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{

}

/**
 * MatrixDeterminant calculates the determinant of a 3x3 matrix 
 * and returns the value as a float.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the determinant of mat
 * mat is not modified by this function.
 * */
float MatrixDeterminant(float mat[3][3])
{

}

/* MatrixInverse calculates the inverse of a matrix and
 * "returns" the result by modifying the second argument.
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 3x3 matrix that is modified to contain the inverse of mat
 * @return: none
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixInverse(float mat[3][3], float result[3][3])
{

}

#endif // MATRIX_MATH_H
