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
            if (MatrixEquals(zero_matrix, mat2) == 0) {
                printf("The two matrices are equal!\n");
            }
            if (MatrixEquals(zero_matrix, mat2) == 1) {
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
        printf("\nDemonstrating MatrixDeterminant():\n");
        {
            printf("Determinant value: %f\n", MatrixDeterminant(mat));
        }
    }


    printf("\n\n\n");
    while (1);
}

