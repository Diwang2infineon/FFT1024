/*
 * Description: This program includes several sections of code. It calculates the product of two 16-bit signed integers,
 *              formats a double number with commas, and measures the number of loops executed per second.
 * Author: [Your Name]
 * Date: [Current Date]
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define false 0
#define true 1

/*
 * Function: format_number
 * Description: Formats a double number with commas.
 * Parameters:
 *  - str: Pointer to a character array where the formatted number will be stored.
 *  - num: The double number to be formatted.
 */
void format_number(char *str, double num)
{
    int i, j = 0, m, len = 50;
    char temp[30];
    int dot = false;

    // convert the number to string
    sprintf(temp, "%.4lf", num);
    len = strlen(temp);

    // insert comma after every 3 digits
    for (i = 50 - 1; i >= 0; i--)
    {
        if (i == 50 - 1)
        {
            str[i] = '\0';
            continue;
        }

        if (j > len - 1)
            break;

        if (temp[len - j - 1] == '.')
        {
            dot = true;
            m = j;
        }

        if ((j - m - 1) % 3 == 0 && (j - m - 1) != 0 && dot == true)
        {
            str[i] = ',';
            i--;
        }
        str[i] = temp[len - j - 1];
        j++;
    }
    for (; i >= 0; i--)
    {
        str[i] = ' ';
    }
}

int main() {
    int c = 0;
    char str[50];
    clock_t start_time, end_time;
    double total_time;
    #define LOOP_N 2100000000

    start_time = clock();
    while (c++ < LOOP_N) {
        str[0]++;
    }
    end_time = clock();
    total_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
    format_number(str, LOOP_N / total_time);
    printf("Loops per second: %s\n", str);
    printf("Total time taken: %.2f s\n", total_time);
    return 0;
}
