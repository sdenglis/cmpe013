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
float x = 3.0;
float trace = 0;
float zero_matrix[3][3] = {};
float result[3][3] = {};
float Result[2][2] = {};
float mat [3][3] = {
    {1, -2, 3},
    {1, 2, -3},
    {-1, 2, 3}
};
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

int main()
{
    BOARD_Init();

    printf("Beginning sdenglis's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    printf("Demonstrating MatrixPrint():\n");
    {
        // Print out first matrix
        MatrixPrint(mat1);
        printf("\n");
        // Print out second matrix
        MatrixPrint(mat2);

        // Print condition runs through MatrixEquals function
        printf("Demonstrating MatrixEquals():\n");
        {
            if (MatrixEquals(mat1, mat2) == 0) {
                printf("The two matrices are equal!\n");
            }
            if (MatrixEquals(mat1, mat2) == 1) {
                printf("The two matrices are NOT equal.\n");
            }
        }
    }

    printf("\n");

    printf("Demonstrating MatrixPrint():\n");
    {

        MatrixPrint(zero_matrix);
        printf("\n");
        MatrixPrint(mat2);

        // Print condition runs through MatrixEquals function
        printf("Demonstrating MatrixEquals():\n");
        {
            if (MatrixEquals(zero_matrix, mat2) == 1) {
                printf("The two matrices are equal!\n");
            }
            if (MatrixEquals(zero_matrix, mat2) == 0) {
                printf("The two matrices are NOT equal.\n");
            }
        }

    }

    printf("\n");

    printf("Demonstrating MatrixPrint():\n");
    {
        // Print out first matrix
        MatrixPrint(mat1);
        printf("\n");
        // Print out second matrix
        MatrixPrint(mat2);
        printf("\nDemonstrating MatrixAdd():\n");
        {
            MatrixAdd(mat1, mat2, result);
            MatrixPrint(result);
        }
        printf("\nDemonstrating MatrixMultiply():\n");
        {
            // float result[3][3] = {};
            MatrixMultiply(mat1, mat2, result);
            // Function not correctly implemented
            MatrixPrint(result);
        }
        printf("\nDemonstrating MatrixScalarAdd():\n");
        {
            // float result[3][3] = {};
            MatrixScalarAdd(x, mat, result);
            MatrixPrint(result);
        }
        printf("\nDemonstrating MatrixScalarMultiply():\n");
        {
            // float result[3][3] = {};
            MatrixScalarMultiply(x, mat, result);
            MatrixPrint(result);
        }
        printf("\nDemonstrating MatrixTrace():\n");
        {
            // float result[3][3] = {};
            printf("Trace value: %f\n", MatrixTrace(mat));
        }
        printf("\nDemonstrating MatrixTranspose():\n");
        {
            MatrixTranspose(mat, result);
            MatrixPrint(result);
        }
        float result[3][3] = {};
        printf("\nDemonstrating MatrixDeterminant():\n");
        {
            printf("Determinant value: %f\n", MatrixDeterminant(mat));
        }
        printf("\nDemonstrating MatrixInverse():\n");
        {
            MatrixInverse(mat, result);
            MatrixPrint(result);
        }
    }

    printf("\n\n\n");

    /******************************************************************************
     * MATRIX - Matrix Equals
     *****************************************************************************/

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
    MatrixPrint(result);
    if (MatrixEquals(result, MatrixMultiplyResult2) == 1) {
        MatrixMultiplyTest += 1;
    }

    // Testing block for MatrixMultiply() function!
    // Will return (2/2) if working correctly.

    
    
    /******************************************************************************
     * MATRIX - Matrix Scalar Multiply
     *****************************************************************************/
    
    int MatrixScalarMultiplyTest = 0;


    int MatrixDeterminantTest, MatrixAddTest, MatrixScalarAddTest;
    int MatrixInverseTest, MatrixTranposeTest, MatrixTraceTest;

    int total;
    float totalPercentage;

    printf("PASSED (%d/2): MatrixEqualsTest()\n", MatrixEqualsTest);
    printf("PASSED (%d/2): MatrixMultiplyTest()\n", MatrixMultiplyTest);
    printf("PASSED (%d/2): MatrixScalarMultiplyTest()\n", MatrixScalarMultiplyTest);
    printf("PASSED (%d/2): MatrixDeterminantTest()\n", MatrixDeterminantTest);
    printf("PASSED (%d/2): MatrixAddTest()\n", MatrixAddTest);
    printf("PASSED (%d/2): MatrixScalarAddTest()\n", MatrixScalarAddTest);
    printf("PASSED (%d/2): MatrixInverseTest()\n", MatrixInverseTest);
    printf("PASSED (%d/2): MatrixTranposeTest()\n", MatrixTranposeTest);
    printf("PASSED (%d/2): MatrixTraceTest()\n", MatrixTraceTest);
    printf("_______________________________________\n");
    printf("%d out of 9 functions passed (%.2f%%).", total, totalPercentage);


    printf("\n\n\n");
    while (1);
}

