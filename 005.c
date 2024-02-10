/*
 * Description: This program includes three sections of code. The first section calculates a simple loop operation,
 *              the second section measures the number of additions that can be performed in one second,
 *              and the third section formats a double number with commas.
 * Author: [Your Name]
 * Date: [Current Date]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    char str[50];

    double num = 99999123456.7890;

    format_number(str, num);

    printf("Formatted number: %s\n", str);

    int i;

    for (i = 0; i < 50; i++)
    {
        // printf("ASCII of %c is %d %d\n", str[i], str[i],i);
    }
    return 0;
}
