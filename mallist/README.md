# Mallist

This library allows you to track down all the dinamically allocate memory pointers.

Because of this, the code can free all of the pointers in the code when needed, mostly for error handling and prevent to have a memory leak.

When there is an expected error that exits the code, you should use `freeAll()` and `fcloseAll()`.



## Definitions


### `memoryArray_t`

```
typedef struct _memory {
    void *ptr;
    struct _memory *next;
}memoryArray_t;
```

It's an `struct` that serves as a dynamically list, allowing the system to know all the dynamically allocated pointers inside of your code at a given moment.

The `void *ptr` is the pointer that has been allocated or the file opened. It has a type of `void` because the pointer type can be a different one depending on the declaration.

And `struct _memory *next` is a pointer that points toward the last pointer initialized on the list.

Because of this `struct`, the pointers can be saved inside a list withouth running out of space if there is enough memory.


### `searchMemoryArray_t`

```
typedef enum {
    MALLIST_NOT_FOUND,
    MALLIST_FOUND
}searchMemoryArray_t;
```

It's an `enum` that indicated wether a pointer was found inside of the list or not, only used as a returning value from `freePtr()` and `fcloseList()`.



## Dinamically Allocated Functions


### `mallist()`

```
void *mallist(size_t size);
```

This function replaces `malloc()` and returns the position of the memory that has the same amount of bytes as `size` and it saves the pointer inside of `memoryArray`.

The returning value is a `void`, so it is needed to convert the returning value so as to have the same type as the pointer declared.

In case there was a problem with the allocation of the pointer or inside the list, it returns `NULL`.


### `freeAll()`

```
void freeAll(void);
```

This function makes all the pointers inside `memoryArray` to be given to the function `free()` and also all the elements within the list.

This function is essential when there is an expected error inside the function because it frees all the pointers from the code.


### `freePtr()`

```
searchMemoryArray_t freePtr(void *ptr);
```

This function replaces `free()`.

Also, it searches where the pointer is inside of `memoryArray` and it gets rid of it withouth loosing track of the other pointers.

In case that the pointer couldn't been allocated inside the list, it frees it anyway but returning `MEMORY_NOT_FOUND` instead of `MEMORY_FOUND`.



## File Funcions


### `fopenList()`

```
FILE *fopenList(const char *path, const char *mode);
```

This function replaces `fopen()`, saves the pointer inside `fileArray` and returns the `FILE` type pointer of the file.

In case the was a problem with the file or allocating it inside the list, it returns `NULL`.

### `fcloseAll()`

```
void fcloseAll(void);
```

This function makes all the pointers to the files inside `fileArray` to be given to the function `fclose()` and also frees all the elements within the list.

This function is essential when there is an expected error inside the function because it closes all the files and frees the list.


### `fcloseList()`

```
searchMemoryArray_t fcloseList(FILE *closeFile);
```

This function replaces `fclose()`.

Also, it searches where the pointer is inside of `fileArray` and it gets rid of it withouth loosing track of the other files.

In case that the file couldn't been allocated inside the list, it closes it anyway but returning `MEMORY_NOT_FOUND` instead of `MEMORY_FOUND`.