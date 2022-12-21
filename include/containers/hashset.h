#ifndef CONTAINERS_HASHSET_H_
#define CONTAINERS_HASHSET_H_

#include <stdbool.h>
#include <stdlib.h>
#include <containers/errcode.h>

#define DEF_HASHSET(Type)\
typedef struct HashSet##Type##Node {\
    bool in_use;\
    Type data;\
} HashSet##Type##Node;\
typedef struct HashSet##Type {\
    size_t size, capacity;\
    HashSet##Type##Node *data;\
    bool (*eq)(Type*, Type*);\
    size_t (*hash)(Type*);\
} HashSet##Type;\
int HashSet##Type##_initialize(\
    HashSet##Type *hashset,\
    size_t capacity,\
    bool (*eq)(Type*, Type*),\
    size_t (*hash)(Type*));\
int HashSet##Type##_finalize(HashSet##Type *hashset);\
int HashSet##Type##_insert(HashSet##Type *hashset, Type *data);\
int HashSet##Type##_find(HashSet##Type *hashset, bool *found);

#define DEF_HASHSET_FUNCTIONS(Type)\
int HashSet##Type##_initialize(\
    HashSet##Type *hashset,\
    size_t capacity,\
    bool (*eq)(Type*, Type*),\
    size_t (*hash)(Type*)) {\
    if (!hashset) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    hashset->size = 0;\
    hashset->capacity = capacity;\
    hashset->data = calloc(capacity, sizeof(HashSet##Type##Node));\
    if (!hashset->data) {\
        return CONTAINERS_ERR_INSUFFICIENT_MEMORY;\
    }\
    hashset->eq = eq;\
    hashset->hash = hash;\
    return CONTAINERS_ERR_OK;\
}\
int HashSet##Type##_finalize(HashSet##Type *hashset) {\
    if (!hashset) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    free(hashset->data);\
    return CONTAINERS_ERR_OK;\
}\
int HashSet##Type##_insert(HashSet##Type *hashset, Type *data) {\
    if (!hashset || !data) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    if (hashset->size == hashset->capacity) {\
        hashset->capacity <<= 1;\
        HashSet##Type##Node *buf =\
            calloc(hashset->capacity, sizeof(HashSet##Type##Node));\
        if (!buf) {\
            return CONTAINERS_ERR_INSUFFICIENT_MEMORY;\
        }\
        HashSet##Type##Node *iter = hashset->data;\
        for (size_t i = 0; i < hashset->size; ++i, ++iter) {\
            size_t idx = hashset->hash(&iter->data) % hashset->capacity;\
            for (\
                ;\
                buf[idx].in_use &&\
                !hashset->eq(&buf[idx].data, &iter->data);\
                idx = (idx + 1) % hashset->capacity);\
            buf[idx].in_use = true;\
            buf[idx].data = iter->data;\
        }\
        free(hashset->data);\
        hashset->data = buf;\
    }\
    size_t idx = hashset->hash(data) % hashset->capacity;\
    for (\
        ;\
        hashset->data[idx].in_use &&\
        !hashset->eq(&hashset->data[idx].data, data);\
        idx = (idx + 1) % hashset->capacity);\
    if (!hashset->data[idx].in_use) {\
        ++hashset->size;\
        hashset->data[idx].in_use = true;\
        hashset->data[idx].data = *data;\
    }\
    return CONTAINERS_ERR_OK;\
}

#endif
