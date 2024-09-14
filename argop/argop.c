#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include "argop.h"


union _argFlags_t argFlags = { 0 };


uint8_t strArrLen(const char *_Str[]);
void searchArg(int argc, char *argv[], argOp_t _ArgOp[], uint8_t _BoolMultOp, uint8_t _BoolSetOp, uint8_t _NumOp, va_list _Operations);


void checkArgs(int argc, char *argv[], argOp_t argOp[], uint8_t numOp, ...) {
    va_list op;
    va_start(op, numOp);

    searchArg(argc, argv, argOp, 0, 0, numOp, op);

    va_end(op);
}

void checkFullArgs(int argc, char *argv[], argOp_t argOp[], uint8_t hasMult, uint8_t hasSet,  uint8_t numOp, ...) {
    va_list op;
    va_start(op, numOp);

    // The multi operation doesn't count in the operations array
    if(hasMult) numOp--;

    searchArg(argc, argv, argOp, hasMult, hasSet, numOp, op);

    va_end(op);
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

void searchArg(int argc, char *argv[], argOp_t argOp[], uint8_t hasMult, uint8_t hasSet, uint8_t numOp, va_list op) {
    // This will contain the array of operation types
    const char **operations[MAX_OP];
    for(uint8_t i = 0; i < numOp; i++)
        operations[i] = va_arg(op, const char **);

    // Iterate through every argument excluding the command
    for(uint8_t i = 1; i < argc; i++) {
        uint8_t wasFound = 0;
        
        // Iterate through every operation type
        for(uint8_t j = 0; j < numOp; j++) {
            // Get the amount of operations per type
            uint8_t strLen = strArrLen(operations[j]);

            // Iterate through every operation
            for(uint8_t k = 0; k < strLen; k++) {
                // Changed the way of comparing the arguments
                int cmpArg = (hasSet && j == 0)
                    ?   !strncmp(argv[i], operations[0][k], strlen(operations[0][k]))
                    :   !strcmp(argv[i], operations[j][k]);

                // Check if the argument is an operation
                if(cmpArg) {
                    wasFound = 1;

                    // Save the information in the array
                    // The "+ 1" is for the NOT_FOUND
                    argOp[i - 1].type = j + 1;
                    argOp[i - 1].operation = k + 1;

                    // Check if the flag was already set
                    if(argFlags.data & 1 << j) bad_usage = 1;
                    else argFlags.data |= 1 << j;

                    break;
                }
            }

            // In case the operation was found, stops comparing
            // to the other types
            if(wasFound) break;

            // In case it was the last type and wasn't found then check
            // if it is a mult option
            if(hasMult && j == numOp - 1 && argv[i][0] == '-' && argv[i][1] != '-') {
                argOp[i - 1].type = numOp;
                argOp[i - 1].operation = numOp;

                // Check if the flag was already set
                if(argFlags.data & 1 << numOp - 1) bad_usage = 1;
                else argFlags.data |= 1 << numOp - 1;
            }

            // In case it wasn't found at any point
            else if(j == numOp - 1) {
                argOp[i - 1].type = NOT_FOUND;
                argOp[i - 1].operation = NOT_FOUND;
            }
        }
    }
}