/* 
   Name: Print Asterisks
   Description: This program prints a rectangular grid of asterisks. The dimensions of the grid (number of rows and columns) are set at the beginning of the main function. It uses nested loops to iterate through each row and column, printing an asterisk followed by a space for each cell in the grid. After printing each row, a newline character is added to move to the next row.
*/


#include <stdio.h>

int main() {
    // Set the number of rows and columns for the loop
    int rows = 5;
    int columns = 10;

    // Nested loop to print the asterisks
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("* ");
        }
        printf("\n");
    }

    return 0;
}

