#ifndef CONTAINERS_HASHSET_H_
#define CONTAINERS_HASHSET_H_

#include <stdbool.h>
#include <stdlib.h>

#define DEF_HASHSET(Type)\
typedef HashSet##Type##Node {\
    bool in_use;\
    Type data;\
} HashSet##Type##Node;\
typedef HashSet##Type {\
    size_t size, capacity;\
    HashSet##Type##Node *data;\
    bool (*eq)(Type *a, Type *b);\
    size_t (*hash)(Type *a, Type *b);\
} HashSet##Type;\
int HashSet##Type##_initialize(HashSet##Type *hashset, size_t capacity);\
int HashSet##Type##_finalize(HashSet##Type *hashset);\
int HashSet##Type##_insert(HashSet##Type *hashset, Type *data);\
int HashSet##Type##_find(HashSet##Type *hashset, bool *found);

#define DEF_HASHSET_FUNCTIONS(Type)\
int HashSet##Type##_initialize(HashSet##Type *hashset, size_t capacity) {\
    if (!hashset) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    hashset->size = 0;\
    hashset->capacity = capacity;\
    hashset->data = malloc(sizeof(HashSet##Type##Node) * capacity);\
    if (!hashset->data) {\
        return CONTAINERS_ERR_INSUFFICIENT_MEMORY;\
    }\
    return CONTAINERS_ERR_OK;\
}\
int HashSet##Type##_finalize(HashSet##Type *hashset) {\
    if (!hashset) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    free(hashset->data);\
    return CONTAINERS_ERR_OK;\
}

#endif
