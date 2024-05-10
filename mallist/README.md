# Mallist

This library allows you to track down all the dinamically allocate memory pointers.
Because of this, the code can free all of the pointers in the code when needed, mostly for error handling and prevent to have a memory leak

## `memoryArray_t`

It's an `struct` that serves as a dynamically list, allowing the system to know all the dynamically allocated pointers inside of your code at a given moment

```
typedef struct _memoryArray {
    void *ptr;
    struct _memoryArray *next;
}memoryArray_t;
```

The `void *ptr` is the pointer that has been allocated. It has a type of `void` because the pointer type can be a different one depending on the declaration.

And `struct _memoryArray *next` is a pointer that points toward the last pointer initialized on the list.

Because of this `struct`, the pointers can be saved inside a list withouth running out of space IF there is enough memory.

## `mallist()`

This function replaces `malloc()` and returns the position of the memory that has the same amount of bytes as `size`.

The returning value is a `void`, so it is needed to convert the returning value so as to have the same type as the pointer declared.

```
void *mallist(size_t size);

...

char *ptr = (char*)mallist(sizeof(char));
```

## `freeAll()`

This function makes all the pointers inside `memoryArray` to be given to the function `free()`.

```
void freeAll(void);
```

## `freePtr()`

This function replaces `free()` and it makes the pointer given pass down to a `free()`.

Also, it searches where the pointer is inside of `memoryArray` and it gets rid of it withouth loosing track of the other pointers.

```
void freePtr(void *ptr);
```

## `memoryError()`

It's just an error handler when the `malloc()` function returns `NULL`.

It calls `freeAll()` so as not to have a memory leak