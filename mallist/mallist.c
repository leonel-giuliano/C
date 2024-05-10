#include <stdio.h>
#include <stdlib.h>

#include "mallist.h"

static memoryArray_t *memoryArray = NULL;   /* List for memory */
static memoryArray_t *fileArray = NULL;     /* List for files */

// DINAMICALLY ALLOCATED MEMORY
void *mallist(size_t size) {
    void *ptrTemp;      /* Pointer withouth a definition type */
    if((ptrTemp = malloc(size)) == NULL) errorHandler(MEMORY_ERROR);

    memoryArray_t *newPtr;
    if((newPtr = (memoryArray_t*)malloc(sizeof(memoryArray_t))) == NULL) errorHandler(MEMORY_ERROR);

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



// FILES
FILE *fopenList(const char *path, const char *mode) {
    FILE *file;
    if((file = fopen(path, mode)) == NULL) errorHandler(FILE_ERROR);
    // Opens the file in the set mode

    memoryArray_t *newFile;
    if((newFile = (FILE *)malloc(sizeof(memoryArray_t))) == NULL) errorHandler(FILE_ERROR);

    newFile->ptr = file;
    newFile->next = fileArray;
    fileArray = newFile;
    // Adds the file to the list

    return file;
}

void fcloseAll() {
    memoryArray_t *closeFile;

    while(fileArray != NULL) {
        closeFile = fileArray;
        fileArray = fileArray->next;
        // Detaches the file

        fclose(closeFile->ptr);
        free(closeFile);
        // One closes the file and the other frees the element from the list
    }
}



// ERROR HANDLER
void errorHandler(error_t event) {
    printf("ERROR: ");

    switch(event) {
        case MEMORY_ERROR:
            printf("There was a problem with the allocation.\n");
            break;

        case FILE_ERROR:
            printf("There was a problem with the file.\n");
            break;

        default:
            printf("Unknown reason.\n");
            break;
    }

    freeAll();
    fcloseAll();

    exit(EXIT_FAILURE);
}