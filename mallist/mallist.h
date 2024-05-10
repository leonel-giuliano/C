#ifndef __MALLIST_H__
#define __MALLIST_H__

typedef enum {
    MALLIST_NOT_FOUND,
    MALLIST_FOUND
}searchMemoryArray_t;
// Enumeration in case the pointer wasn't in the list

typedef struct _memory {
    void *ptr;
    struct _memory *next;
}memoryArray_t;
// Array for all the dynamic allocated memories

// DINAMICALLY ALLOCATED MEMORY
void *mallist(size_t);      /* Allocates the pointer inside the array, replaces malloc() */
void freeAll();             /* Frees all the allocated memories instances */
void freePtr(void *);       /* Frees only the pointer given, replaces free() */

// FILES
FILE *fopenList(const char*, const char*);
// Allocates the file inside the array, replaces fopen()
void fcloseAll(void);       /* Closes all the files in the list */
searchMemoryArray_t fcloseList(FILE*);
// Closes the file given
// Returns a bool depending if the file was found inside the list

#endif