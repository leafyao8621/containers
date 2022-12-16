#ifndef CONTAINERS_DARRAY_H_
#define CONTAINERS_DARRAY_H_

#include <stdint.h>
#include <stdlib.h>
#include <containers/errcode.h>

#define DEF_DARRAY(Type)\
typedef struct DArray##Type {\
    size_t size, capacity;\
    Type *data;\
} DArray##Type;\
int DArray##Type##_initialize(DArray##Type *darray, size_t capacity);\
int DArray##Type##_finalize(DArray##Type *darray);

#define DEF_DARRAY_FUNCTIONS(Type)\
int DArray##Type##_initialize(DArray##Type *darray, size_t capacity) {\
    if (!darray) {\
        return ERR_NULL_PTR;\
    }\
    darray->data = malloc(sizeof(Type) * capacity);\
    if (!darray->data) {\
        return ERR_INSUFFICIENT_MEMORY;\
    }\
    darray->size = 0;\
    darray->capacity = capacity;\
    return ERR_OK;\
}\
int DArray##Type##_finalize(DArray##Type *darray) {\
    if (!darray) {\
        return ERR_NULL_PTR;\
    }\
    free(darray->data);\
    return ERR_OK;\
}

#endif
