#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include "argop.h"


union _argFlags_t argFlags = { 0 };


// Taking advantage of the flag that isn't used until later
#define operation_found bad_usage


// Static functions

static uint8_t strArrLen(const char *str[]) {
    uint8_t i = 0, loop = 1;
    while(str[i] != NULL && loop) {
        i++;
        loop++;
    }

    return i;
}


void checkArgs(int argc, char *argv[], uint8_t numOp, ...) {
    va_list op;
    va_start(op, numOp);

    // This will contain the array of operation types
    const char **operations[MAX_OP];
    for(uint8_t i = 0; i < numOp; i++)
        operations[i] = va_arg(op, const char **);

    // Iterate through every argument excluding the command
    for(uint8_t i = 1; i < argc; i++) {
        // Iterate through every operation type
        for(uint8_t j = 0; j < numOp; j++) {
            // Get the amount of operations per type
            uint8_t strLen = strArrLen(operations[j]);
        }
    }

    va_end(op);
}