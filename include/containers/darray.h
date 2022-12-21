#ifndef CONTAINERS_DARRAY_H_
#define CONTAINERS_DARRAY_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <containers/errcode.h>

#define DEF_DARRAY(Type)\
typedef struct DArray##Type {\
    size_t size, capacity;\
    Type *data;\
} DArray##Type;\
int DArray##Type##_initialize(DArray##Type *darray, size_t capacity);\
int DArray##Type##_finalize(DArray##Type *darray);\
int DArray##Type##_push_back(DArray##Type *darray, Type *item);\
int DArray##Type##_push_back_batch(\
    DArray##Type *darray,\
    Type *items,\
    size_t len);

#define DEF_DARRAY_FUNCTIONS(Type)\
int DArray##Type##_initialize(DArray##Type *darray, size_t capacity) {\
    if (!darray) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    darray->data = malloc(sizeof(Type) * capacity);\
    if (!darray->data) {\
        return CONTAINERS_ERR_INSUFFICIENT_MEMORY;\
    }\
    darray->size = 0;\
    darray->capacity = capacity;\
    return CONTAINERS_ERR_OK;\
}\
int DArray##Type##_finalize(DArray##Type *darray) {\
    if (!darray) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    free(darray->data);\
    return CONTAINERS_ERR_OK;\
}\
int DArray##Type##_push_back(DArray##Type *darray, Type *item) {\
    if (!darray || !item) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    if (darray->size == darray->capacity) {\
        darray->capacity <<= 1;\
        darray->data = realloc(darray->data, sizeof(Type) * darray->capacity);\
        if (!darray->data) {\
            return CONTAINERS_ERR_INSUFFICIENT_MEMORY;\
        }\
    }\
    darray->data[darray->size++] = *item;\
    return CONTAINERS_ERR_OK;\
}\
int DArray##Type##_push_back_batch(\
    DArray##Type *darray,\
    Type *items,\
    size_t len) {\
    if (!darray || !items) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    if (darray->size + len > darray->capacity) {\
        darray->capacity = darray->size + len;\
        darray->data = realloc(darray->data, sizeof(Type) * darray->capacity);\
        if (!darray->data) {\
            return CONTAINERS_ERR_INSUFFICIENT_MEMORY;\
        }\
    }\
    memcpy(darray->data + darray->size, items, sizeof(Type) * len);\
    darray->size += len;\
    return CONTAINERS_ERR_OK;\
}

#endif
