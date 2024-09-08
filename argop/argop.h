#ifndef __LIBARGOP_H__
#define __LIBARGOP_H__

// Operations

// Max amount of operations type
#define MAX_OP 6


// Flags

// Flag declared for the user, is not used in the functions
// Should be used to tell the program there are problems on the usage
#define bad_usage argFlags.flags.flag7

// Union to use 8 bits as flags
union _argFlags_t {
    struct {
        unsigned int flag0 : 1;
        unsigned int flag1 : 1;
        unsigned int flag2 : 1;
        unsigned int flag3 : 1;
        unsigned int flag4 : 1;
        unsigned int flag5 : 1;
        unsigned int flag6 : 1;
        unsigned int flag7 : 1;
    }flags;

    unsigned char data;
};

extern union _argFlags_t argFlags;


#endif