/******************************************************************************
 * \file Atan2Example.c
 *
 * \brief Example usage of atan2 function
 *
 * This file demonstrates the usage of the atan2 function from the math.h library.
 * It calculates the arctangent of the quotient of its arguments and prints the result.
 *
 * \version 1.0
 *
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

/** \brief Main function */
int main() {
    // Define input arrays
    float x[4] = {1.0, -1.0, 1.0, -1.0};
    float y[4] = {1.0, -1.0, -1.0, 1.0};

    // Iterate through the arrays and calculate arctangent
    for (int i = 0; i < 4; i++) {
        float angle = atan2f(y[i], x[i]);

        // Print input values and corresponding arctangent
        printf("x = %.2f, y = %.2f\n", x[i], y[i]);
        printf("atan2(y, x) = %.2f pi\n", angle/3.14159);
    }

    return 0;
}
