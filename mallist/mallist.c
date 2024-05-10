#include <stdio.h>

#include "mallist.h"

static memoryArray_t *memoryArray = NULL;   /* List for memory */
static memoryArray_t *fileArray = NULL;     /* List for files */

// DINAMICALLY ALLOCATED MEMORY
void *mallist(size_t size) {
    void *ptrTemp = malloc(size);      /* Pointer withouth a definition type */
    memoryArray_t *newPtr = (memoryArray_t*)malloc(sizeof(memoryArray_t));

    if(ptrTemp != NULL && newPtr != NULL) {
        newPtr->ptr = ptrTemp;
        newPtr->next = memoryArray;
        memoryArray = newPtr;
    }
    // Adds the pointer to the list

    return ptrTemp;
    // Returns NULL if there is a problem allocating
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

searchMemoryArray_t freePtr(void *delPtr) {
    searchMemoryArray_t exitStatus = MALLIST_FOUND;
    // Flag if the pointer was found inside of the list

    memoryArray_t *lastPtr = NULL, *iPtr = memoryArray;
    // lastPtr helps to attach the list when the ptr gets deleted
    // iPtr iterates the list

    while(delPtr != iPtr->ptr && iPtr != NULL) {
        lastPtr = iPtr;
        iPtr = iPtr->next;
        // Searches for the pointer inside the list

        if(iPtr == NULL) exitStatus = MALLIST_NOT_FOUND;
        // In case the file wasn't inside of the list, saves it inside a flag
    }

    if(exitStatus == MALLIST_FOUND) {
        if(lastPtr != NULL) lastPtr->next = iPtr->next;
        // The last ptr skips over the given ptr

        free(iPtr);
    }

    free(delPtr);
    // Frees the pointer regarding if it was inside of the list or not

    return exitStatus;
}



// FILES
FILE *fopenList(const char *path, const char *mode) {
    FILE *file = fopen(path, mode);
    memoryArray_t *newFile = (FILE *)malloc(sizeof(memoryArray_t));

    if(file != NULL && newFile != NULL) {
        newFile->ptr = file;
        newFile->next = fileArray;
        fileArray = newFile;
        // Adds the file to the list
    }

    return file;
    // Returns NULL if there was a problem opening the file
    // If it couldn't allocate it, it skips it
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

searchMemoryArray_t fcloseList(FILE *closeFile) {
    searchMemoryArray_t exitStatus = MALLIST_FOUND;
    // Flag if the file was found inside of the list

    memoryArray_t *lastFile = NULL, *iFile = fileArray;

    while(closeFile != iFile->ptr && iFile != NULL) {
        lastFile = iFile;
        iFile = iFile->next;
        // Searches for the file inside the list

        if(iFile == NULL) exitStatus = MALLIST_NOT_FOUND;
        // In case the file wasn't inside of the list, saves it inside a flag
    }

    if(exitStatus == MALLIST_FOUND) {
        if(lastFile != NULL) lastFile->next = iFile->next;
        // The last ptr skips over the given ptr

        free(iFile);
    }
    
    fclose(closeFile);
    // Closes the file regarding if it was inside of the list or not

    return exitStatus;
}