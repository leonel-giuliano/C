#include <stdarg.h>
#include <stdint.h>

#include "argop.h"


union _argFlags_t argFlags = { 0 };


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
            
        }
    }

    va_end(op);
}