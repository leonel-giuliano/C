#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include "argop.h"


union _argFlags_t argFlags = { 0 };


// Taking advantage of the flag that isn't used until later
#define operation_found bad_usage


uint8_t strArrLen(const char *_Str[]);


void checkArgs(int argc, char *argv[], argOp_t argOp[], uint8_t numOp, ...) {
    va_list op;
    va_start(op, numOp);

    // This will contain the array of operation types
    const char **operations[MAX_OP];
    for(uint8_t i = 0; i < numOp; i++)
        operations[i] = va_arg(op, const char **);

    va_end(op);

    // Iterate through every argument excluding the command
    for(uint8_t i = 1; i < argc; i++) {
        operation_found = 0;
        
        // Iterate through every operation type
        for(uint8_t j = 0; j < numOp; j++) {
            // Get the amount of operations per type
            uint8_t strLen = strArrLen(operations[j]);

            // Iterate through every operation
            for(uint8_t k = 0; k < strLen; k++) {
                // Check if the argument is an operation
                if(!strcmp(argv[i], operations[j][k])) {
                    operation_found = 1;

                    // Save the information in the array
                    // The "+ 1" is for the NOT_FOUND
                    argOp[i - 1].type = j + 1;
                    argOp[i - 1].operation = k + 1;

                    // Activate the flag depending on the ix
                    // to tell the type operation it has
                    argFlags.data |= 1 << j;

                    break;
                }
            }

            // In case the operation was found, stops comparing
            // to the other types
            if(operation_found) break;

            // In case it was the last type and wasn't found
            if(j == numOp - 1) {
                argOp[i - 1].type = NOT_FOUND;
                argOp[i - 1].operation = NOT_FOUND;
            }
        }
    }

    // Set the flag back to 0 for the bad_usage
    operation_found = 0;
}


// Private functions

uint8_t strArrLen(const char *str[]) {
    uint8_t i = 0, loop = 1;
    while(str[i] != NULL && loop) {
        i++;
        loop++;
    }

    return i;
}