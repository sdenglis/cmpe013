// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"


// Microchip libraries
#include <xc.h>

// User libraries:
#include "MatrixMath.h"

// Module-level variables:
float result[3][3] = {};
float Result[2][2] = {};



int main()
{
    BOARD_Init();

    printf("Beginning sdenglis's mml test harness, compiled on %s %s\n\n", __DATE__, __TIME__);



    /******************************************************************************
     * MATRIX - Matrix Equals
     *****************************************************************************/

    float zero_matrix[3][3] = {};
    float mat1[3][3] = {
        {1, -2, 3},
        {1, 2, -3},
        {-1, 2, 3}
    };
    float mat2[3][3] = {
        {1, -2, 3},
        {1, 2, -3},
        {-1, 2, 3}
    };


    int MatrixEqualsTest = 0;
    // These two matrices should be equal!
    if (MatrixEquals(mat1, mat2) == 1) {
        MatrixEqualsTest += 1;
    }

    // These two matrices should NOT be equal.
    if (MatrixEquals(zero_matrix, mat2) == 0) {
        MatrixEqualsTest += 1;
    }
    // Testing block for MatrixEquals() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Multiply
     *****************************************************************************/

    int MatrixMultiplyTest = 0;
    float MatrixMultiplyResult[3][3] = {
        {-4, 0, 18},
        {6, -4, -12},
        {-2, 12, 0}
    };
    float MatrixMultiplyResult2[3][3] = {
        {-20, 216, -72},
        {-24, -128, 156},
        {80, -48, -180}
    };

    // Compare MatrixMultiply() function to hard-coded array.
    MatrixMultiply(mat1, mat2, result);
    if (MatrixEquals(result, MatrixMultiplyResult) == 1) {
        MatrixMultiplyTest += 1;
    }

    // Compare MatrixMultiply() function to hard-coded array.
    MatrixMultiply(MatrixMultiplyResult, MatrixMultiplyResult, result);
    if (MatrixEquals(result, MatrixMultiplyResult2) == 1) {
        MatrixMultiplyTest += 1;
    }

    // Testing block for MatrixMultiply() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Scalar Multiply
     *****************************************************************************/

    int MatrixScalarMultiplyTest = 0;
    // Arbitrary test values for scalar function
    float scalarValue = 3;
    float scalarSecondValue = 1.5;

    float matScalarResult [3][3] = {};
    // We'll be using this matrix for the function operations
    float matScalar [3][3] = {
        {1, -2, 3},
        {1, 2, -3},
        {-1, 2, 3}
    };
    // What we expect from the first calculation
    float matScalarExpected [3][3] = {
        {3, -6, 9},
        {3, 6, -9},
        {-3, 6, 9}
    };
    // What we expect from the second calculation
    float matSecondScalarExpected [3][3] = {
        {1.5, -3, 4.5},
        {1.5, 3, -4.5},
        {-1.5, 3, 4.5}
    };

    // (matScalar * scalarValue) should equal matScalarExpected.
    MatrixScalarMultiply(scalarValue, matScalar, matScalarResult);
    if (MatrixEquals(matScalarResult, matScalarExpected) == 1) {
        MatrixScalarMultiplyTest += 1;
    }

    // (matScalar * scalarSecondValue) should equal matSecondScalarExpected.
    MatrixScalarMultiply(scalarSecondValue, matScalar, matScalarResult);
    if (MatrixEquals(matScalarResult, matSecondScalarExpected) == 1) {
        MatrixScalarMultiplyTest += 1;
    }

    // Testing block for MatrixScalarMultiply() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Determinant
     *****************************************************************************/

    int MatrixDeterminantTest = 0;
    float knownDeterminant = 24;
    float anotherKnownDeterminant = 763.7;

    float knownMatrix[3][3] = {
        {1, -2, 3},
        {1, 2, -3},
        {-1, 2, 3}
    };
    float anotherKnownMatrix[3][3] = {
        {5, -8, 3.5},
        {4, 6.2, -3},
        {-4, 7.1, 9}
    };

    float experimentalDeterminant = MatrixDeterminant(knownMatrix);
    // Calculate the determinant of knownMatrix and compare to hard-coded value
    if (ScalarEquals(experimentalDeterminant, knownDeterminant) == 1) {
        MatrixDeterminantTest += 1;
    }

    float anotherExperimentalDeterminant = MatrixDeterminant(anotherKnownMatrix);
    // Calculate the determinant of anotherKnownMatrix and compare to hard-coded value
    if (ScalarEquals(anotherExperimentalDeterminant, anotherKnownDeterminant) == 1) {
        MatrixDeterminantTest += 1;
    }

    // Testing block for MatrixDeterminant() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Add
     *****************************************************************************/

    int MatrixAddTest = 0;

    // Testing block for MatrixAdd() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Scalar Add
     *****************************************************************************/

    int MatrixScalarAddTest = 0;

    // Testing block for MatrixScalarAdd() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Inverse
     *****************************************************************************/

    int MatrixInverseTest = 0;

    // Testing block for MatrixInverse() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Transpose
     *****************************************************************************/

    int MatrixTranposeTest = 0;

    // Testing block for MatrixTranspose() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Trace
     *****************************************************************************/

    int MatrixTraceTest = 0;

    // Testing block for MatrixTrace() function!
    // Will return (2/2) if working correctly.




    // Declare variables used to pass through printf())
    int total = 0;
    float totalPercentage = 0;

    // Tally the total score for the function harness
    {
        if (MatrixEqualsTest == 2) {
            total += 1;
        }
        if (MatrixMultiplyTest == 2) {
            total += 1;
        }
        if (MatrixScalarMultiplyTest == 2) {
            total += 1;
        }
        if (MatrixDeterminantTest == 2) {
            total += 1;
        }
        if (MatrixAddTest == 2) {
            total += 1;
        }
        if (MatrixScalarAddTest == 2) {
            total += 1;
        }
        if (MatrixInverseTest == 2) {
            total += 1;
        }
        if (MatrixTranposeTest == 2) {
            total += 1;
        }
        if (MatrixTraceTest == 2) {
            total += 1;
        }
    }
    // Calculate percentage for user interface
    totalPercentage = ((total / 9.0f) * 100);


    printf("PASSED (%d/2): MatrixEquals()\n", MatrixEqualsTest);
    printf("PASSED (%d/2): MatrixMultiply()\n", MatrixMultiplyTest);
    printf("PASSED (%d/2): MatrixScalarMultiply()\n", MatrixScalarMultiplyTest);
    printf("PASSED (%d/2): MatrixDeterminant()\n", MatrixDeterminantTest);
    printf("PASSED (%d/2): MatrixAdd()\n", MatrixAddTest);
    printf("PASSED (%d/2): MatrixScalarAdd()\n", MatrixScalarAddTest);
    printf("PASSED (%d/2): MatrixInverse()\n", MatrixInverseTest);
    printf("PASSED (%d/2): MatrixTranpose()\n", MatrixTranposeTest);
    printf("PASSED (%d/2): MatrixTrace()\n", MatrixTraceTest);
    printf("_______________________________________\n");
    printf("%d out of 9 functions passed (%.2f%%).", total, totalPercentage);


    printf("\n\n\n");
    while (1);
}

