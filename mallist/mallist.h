#ifndef __MALLIST_H__
#define __MALLIST_H__

typedef struct _memoryArray {
    void *ptr;
    struct _memoryArray *next;
}memoryArray_t;
// Array for all the dynamic allocated memories

void *mallist(size_t);      /* Allocates the file inside the array, replaces malloc() */
void freeAll();             /* Frees all the allocated memories instances */
void freePtr(void *);       /* Frees only the pointer given, replaces free() */
void memoryError(void);     /* ERROR: malloc() == NULL */

#endif