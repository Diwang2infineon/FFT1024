/******************************************************************************
 * \file CallbackExample.c
 *
 * \brief Callback example implementation
 *
 * This file demonstrates the usage of callback functions in C programming.
 * It defines a function that takes a callback function as a parameter and
 * calls it within the function body.
 *
 * \version 1.0
 *
 ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>



typedef void cb_func(void);

// Function that takes a callback function as a parameter
void performCallback(cb_func* callback) {
    // Call the callback function
    callback();
}

// Example callback function
void myCallback() {
    printf("Callback function called.\n");
}

int main() {
    // Declare a variable of type cb_func
    cb_func* callbackPtr = myCallback;

    // Call the performCallback function and pass the callback function
    performCallback(callbackPtr);

    return 0;
}
