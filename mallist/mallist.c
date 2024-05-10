#include <stdlib.h>

#include "mallist.h"

static memoryArray_t *memoryArray = NULL;

void *mallist(size_t size) {
    void *ptrTemp;      /* Pointer withouth a definition type */
    if((ptrTemp = malloc(size)) == NULL) memoryError();

    memoryArray_t *newPtr;
    if((newPtr = (memoryArray_t*)malloc(sizeof(memoryArray_t))) == NULL) memoryError();

    newPtr->ptr = ptrTemp;
    newPtr->next = memoryArray;
    memoryArray = newPtr;
    // Adds the pointer to the list

    return ptrTemp;
}

void freeAll() {
    memoryArray_t *delPtr;

    while(memoryArray != NULL) {
        delPtr = memoryArray;
        memoryArray = memoryArray->next;
        // Detaches the delPtr from the list

        free(delPtr->ptr);
        free(delPtr);
    }
}

void freePtr(void *delPtr) {
    memoryArray_t *beforePtr = NULL, *iPtr = memoryArray;
    // beforePtr helps to attach the list when the ptr gets deleted
    // iPtr iterates the list

    while(delPtr != iPtr->ptr) {
        beforePtr = iPtr;
        iPtr = iPtr->next;
    }

    if(beforePtr != NULL) beforePtr->next = iPtr->next;
    // The last ptr skips over the given ptr

    free(delPtr);
    free(iPtr);
}

void memoryError() {
    printf("There is no memory left.\n");
    freeAll();

    exit(EXIT_FAILURE);
}