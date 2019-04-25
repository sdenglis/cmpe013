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

// CMPE13 Support Library:
#include "BOARD.h"

// Microchip libraries:
#include <xc.h>

// User libraries:
#include "MatrixMath.h"

// Module-level variables:
float result[3][3] = {};
float Result[2][2] = {};
float zero_matrix[3][3] = {};

// Some added helper function prototypes:
void MatrixPrintSubmatrix(float mat[2][2]);
int ScalarEquals(float scalar1, float scalar2);



int main()
{
    BOARD_Init();

    printf("Beginning sdenglis's mml test harness, compiled on %s %s\n\n", __DATE__, __TIME__);



    /******************************************************************************
     * MATRIX - Matrix Equals
     *****************************************************************************/

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
    float matAddResult[3][3] = {};
    float matAddAnotherResult[3][3] = {};
    float matAdd1 [3][3] = {
        {3, 5, 2},
        {1, 2, 7},
        {3, 4, 3}
    };
    float matAdd2 [3][3] = {
        {6, -2, 5},
        {0, 1, -2},
        {5, -3, 3}
    };
    float matAddExpected [3][3] = {
        {9, 3, 7},
        {1, 3, 5},
        {8, 1, 6}
    };
    // Test for equality between MatrixAdd(matAdd1, matAdd2) and known output.
    MatrixAdd(matAdd1, matAdd2, matAddResult);
    if (MatrixEquals(matAddResult, matAddExpected) == 1) {
        MatrixAddTest += 1;
    }
    // Switch the order of addition to test for commutativity.
    // If this works, everything else within reason should as well.
    MatrixAdd(matAdd2, matAdd1, matAddAnotherResult);
    if (MatrixEquals(matAddAnotherResult, matAddExpected) == 1) {
        MatrixAddTest += 1;
    }

    // Testing block for MatrixAdd() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Scalar Add
     *****************************************************************************/

    int MatrixScalarAddTest = 0;
    float scalarAdd = 3.5;
    float scalarAddOutput[3][3] = {};
    float scalarAddInput[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    float anotherScalarAddInput[3][3] = {
        {-3.5, -3.5, -3.5},
        {-3.5, -3.5, -3.5},
        {-3.5, -3.5, -3.5}
    };
    float scalarAddExpected[3][3] = {
        {3.5, 3.5, 3.5},
        {3.5, 3.5, 3.5},
        {3.5, 3.5, 3.5}
    };

    // Add zero matrix input and 3.5 scalar value. (0 + 3.5).
    MatrixScalarAdd(scalarAdd, scalarAddInput, scalarAddOutput);
    if (MatrixEquals(scalarAddOutput, scalarAddExpected) == 1) {
        MatrixScalarAddTest += 1;
    }
    // Compare the resulting matrix to a zero matrix. Should be equal (-3.5 + 3.5).
    // Test if subtraction functions as it should!
    MatrixScalarAdd(scalarAdd, anotherScalarAddInput, scalarAddOutput);
    if (MatrixEquals(scalarAddOutput, scalarAddInput) == 1) {
        MatrixScalarAddTest += 1;
    }

    // Testing block for MatrixScalarAdd() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Inverse
     *****************************************************************************/

    int MatrixInverseTest = 0;
    float inverseResult[3][3] = {};
    float inverseMatrix[3][3] = {
        {7, 3, 6},
        {6, 3, 1},
        {2, 3, 1}
    };
    float inverseExpected[3][3] = {
        {0.0000, 0.2500, -0.2500},
        {-0.0667, -0.0833, 0.4833},
        {0.2000, -0.2500, 0.0500}
    };

    // This should yield the disgusting set of floating point numbers above.
    MatrixInverse(inverseMatrix, inverseResult);
    if (MatrixEquals(inverseResult, inverseExpected) == 1) {
        MatrixInverseTest += 1;
    }
    // Since the matrix input doesn't have a determinant, the function should ERROR.
    // It is set to return an all zero matrix, so here we check for that.
    if (MatrixEquals(inverseResult, zero_matrix) == 1) {
        MatrixInverseTest += 1;
    }

    // Testing block for MatrixInverse() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Transpose
     *****************************************************************************/

    int MatrixTransposeTest = 0;
    float matTransposeResult[3][3] = {};
    float matTranspose[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3}
    };
    float matTransposeExpected[3][3] = {
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3}
    };
    // We see that with a simple case such as this,
    // all of the elements have flipped across the main diagonal.
    MatrixTranspose(matTranspose, matTransposeResult);
    if (MatrixEquals(matTransposeResult, matTransposeExpected) == 1) {
        MatrixTransposeTest += 1;
    }
    // Testing if invertible, whether it would work both directions.
    // SPOILERS** it does.
    MatrixTranspose(matTransposeExpected, matTransposeResult);
    if (MatrixEquals(matTransposeResult, matTranspose) == 1) {
        MatrixTransposeTest += 1;
    }

    // Testing block for MatrixTranspose() function!
    // Will return (2/2) if working correctly.



    /******************************************************************************
     * MATRIX - Matrix Trace
     *****************************************************************************/

    int MatrixTraceTest = 0;
    float scalarTraceExpected = 0;
    float matTrace[3][3] = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    float anotherMatTrace[3][3] = {
        {-5, 1, 7},
        {3, 3, -9},
        {0, -5, 2}
    };

    // Should be equal to zero, since the main diagonal sums up to zero.
    if (ScalarEquals(MatrixTrace(matTrace), scalarTraceExpected) == 1) {
        MatrixTraceTest += 1;
    }
    // Should STILL == zero, since ((-5) + 3 + 2) = 0.
    if (ScalarEquals(MatrixTrace(anotherMatTrace), scalarTraceExpected) == 1) {
        MatrixTraceTest += 1;
    }

    // Testing block for MatrixTrace() function!
    // Will return (2/2) if working correctly.







    /******************************************************************************
     * MATRIX - Print Results
     *****************************************************************************/

    // Declare variables used to print pass rate.
    int total = 0;
    double totalPercentage = 0;

    // Tally the total score for the function harness.
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
        if (MatrixTransposeTest == 2) {
            total += 1;
        }
        if (MatrixTraceTest == 2) {
            total += 1;
        }
    }
    // Calculate percentage for user interface.
    totalPercentage = ((total / 9.0f) * 100);
    // Print nice list of functions and their respective pass rates.
    printf("PASSED (%d/2): MatrixEquals()\n", MatrixEqualsTest);
    printf("PASSED (%d/2): MatrixMultiply()\n", MatrixMultiplyTest);
    printf("PASSED (%d/2): MatrixScalarMultiply()\n", MatrixScalarMultiplyTest);
    printf("PASSED (%d/2): MatrixDeterminant()\n", MatrixDeterminantTest);
    printf("PASSED (%d/2): MatrixAdd()\n", MatrixAddTest);
    printf("PASSED (%d/2): MatrixScalarAdd()\n", MatrixScalarAddTest);
    printf("PASSED (%d/2): MatrixInverse()\n", MatrixInverseTest);
    printf("PASSED (%d/2): MatrixTranspose()\n", MatrixTransposeTest);
    printf("PASSED (%d/2): MatrixTrace()\n", MatrixTraceTest);
    printf("_______________________________________\n");
    printf("%d out of 9 functions passed (%.2f%%).\n\n\n", total, totalPercentage);





    /******************************************************************************
     * MATRIX - Print Matrix / Sub-matrix
     *****************************************************************************/
    // Quick note** I'm not bothering with an equals() test for the sub-matrix function.
    // As I see it, the only way for the determinant to be correct is for the sub-matrix 
    // to also function properly. Thus, since the determinant test was successful,
    // The sub-matrices had to have been correct, equal to their respective expected values.
    
    float submatrixExpected[2][2] = {};
    float matPrint[3][3] = {
        {1, 2, 5},
        {3, 1, 6},
        {6, 5, 3}
    };

    // First print done using the actual function created.
    printf("Output of MatrixPrint():\n");
    MatrixPrint(matPrint);
    // Super rag-tag method of printing the matrix.
    printf("\nExpected output of MatrixPrint():\n");
    printf("+1.000000 +2.000000 +5.000000 \n+3.000000 +1.000000 +6.000000 \n+6.000000 +5.000000 +3.000000");

    printf("\n\n");

    // First print done using the actual function created.
    printf("Output of MatrixSubmatrix(i = 0, j = 0, 'aboveArray'):\n");
    MatrixSubmatrix(0, 0, matPrint, submatrixExpected);
    MatrixPrintSubmatrix(submatrixExpected);
    // Super rag-tag method of printing the matrix.
    printf("\nExpected output of MatrixSubmatrix(i = 0, j = 0, 'aboveArray'):\n");
    printf("+1.000000 +6.000000\n+5.000000 +3.000000 ");





    printf("\n\n\n");
    while (1);
}
