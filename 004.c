/*
 * Description: This program is a simple console application that demonstrates a basic menu-driven interface.
 *              Users can input commands to either execute a function (Foo) or quit the program.
 * Author: [Your Name]
 * Date: [Current Date]
 */

#include <stdio.h>

/*
 * Function: Foo
 * Description: Prints "Hello World!" to the console.
 */
void Foo() {
    printf("Hello World!\n");
}

/*
 * Function: main
 * Description: The main function of the program. It displays a menu and accepts user input to execute functions or quit.
 * Parameters:
 *  - argc: The number of command-line arguments.
 *  - argv: An array of strings containing the command-line arguments.
 * Returns: An integer indicating the exit status of the program.
 */
int main(int argc, char** argv) {
    char input = 0;

    printf("Hello! This is a console application.\n");
    printf("Press q to quit, press a to execute foo.\n");
    
    while(1) {
        if(scanf("%c",&input) == 1) {
            if(input == 'a') {
                Foo();
            } else if(input == 'q') {
                break;
            } else if(input != '\n') {
                printf("Unknown command '%c'! Ignoring...\n",input);
            }
        } else {
            printf("Invalid input! Ignoring...\n");
        }
    }

    return 0;
}
