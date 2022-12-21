#ifndef CONTAINERS_HASHMAP_H_
#define CONTAINERS_HASHMAP_H_

#include <stdbool.h>
#include <stdlib.h>
#include <containers/errcode.h>

#define DEF_HASHMAP(Key, Value)\
typedef struct HashMap##Key##Value##Node {\
    bool in_use;\
    Key key;\
    Value value;\
} HashMap##Key##Value##Node;\
typedef struct HashMap##Key##Value {\
    size_t size, capacity;\
    HashMap##Key##Value##Node *data;\
    bool (*eq)(Key*, Key*);\
    size_t (*hash)(Key*);\
} HashMap##Key##Value;\
int HashMap##Key##Value##_initialize(\
    HashMap##Key##Value *hashmap,\
    size_t capacity,\
    bool (*eq)(Key*, Key*),\
    size_t (*hash)(Key*));\
int HashMap##Key##Value##_finalize(HashMap##Key##Value *hashmap);\
int HashMap##Key##Value##_fetch(\
    HashMap##Key##Value *hashmap,\
    Key *key,\
    Value **value);\
int HashMap##Key##Value##_find(\
    HashMap##Key##Value *hashmap,\
    Key *key,\
    bool *found);

#define DEF_HASHMAP_FUNCTIONS(Key, Value)\
int HashMap##Key##Value##_initialize(\
    HashMap##Key##Value *hashmap,\
    size_t capacity,\
    bool (*eq)(Key*, Key*),\
    size_t (*hash)(Key*)) {\
    if (!hashmap || !eq || !hash) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    hashmap->size = 0;\
    hashmap->capacity = capacity;\
    hashmap->data = calloc(capacity, sizeof(HashMap##Key##Value##Node));\
    if (!hashmap->data) {\
        return CONTAINERS_ERR_INSUFFICIENT_MEMORY;\
    }\
    hashmap->eq = eq;\
    hashmap->hash = hash;\
    return CONTAINERS_ERR_OK;\
}\
int HashMap##Key##Value##_finalize(HashMap##Key##Value *hashmap) {\
    if (!hashmap) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    free(hashmap->data);\
    return CONTAINERS_ERR_OK;\
}\
int HashMap##Key##Value##_fetch(\
    HashMap##Key##Value *hashmap,\
    Key *key,\
    Value **value) {\
    if (!hashmap || !key || !value) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    if (hashmap->size == hashmap->capacity) {\
        hashmap->capacity <<= 1;\
        HashMap##Key##Value##Node *buf =\
            calloc(hashmap->capacity, sizeof(HashMap##Key##Value##Node));\
        if (!buf) {\
            return CONTAINERS_ERR_INSUFFICIENT_MEMORY;\
        }\
        HashMap##Key##Value##Node *iter = hashmap->data;\
        for (size_t i = 0; i < hashmap->size; ++i, ++iter) {\
            size_t idx = hashmap->hash(&iter->key) % hashmap->capacity;\
            for (\
                ;\
                buf[idx].in_use;\
                idx = (idx + 1) % hashmap->capacity);\
            buf[idx].in_use = true;\
            buf[idx].key = iter->key;\
            buf[idx].value = iter->value;\
        }\
        free(hashmap->data);\
        hashmap->data = buf;\
    }\
    size_t idx = hashmap->hash(key) % hashmap->capacity;\
    for (\
        ;\
        hashmap->data[idx].in_use &&\
        !hashmap->eq(&hashmap->data[idx].key, key);\
        idx = (idx + 1) % hashmap->capacity);\
    if (!hashmap->data[idx].in_use) {\
        ++hashmap->size;\
        hashmap->data[idx].in_use = true;\
        hashmap->data[idx].key = *key;\
    }\
    *value = &hashmap->data[idx].value;\
    return CONTAINERS_ERR_OK;\
}\
int HashMap##Key##Value##_find(\
    HashMap##Key##Value *hashmap,\
    Key *key,\
    bool *found) {\
    if (!hashmap || !key || !found) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    size_t idx = hashmap->hash(key) % hashmap->capacity;\
    size_t cnt = 0;\
    for (\
        ;\
        cnt < hashmap->capacity &&\
        hashmap->data[idx].in_use &&\
        !hashmap->eq(&hashmap->data[idx].key, key);\
        ++cnt, idx = (idx + 1) % hashmap->capacity);\
    *found = hashmap->data[idx].in_use && cnt < hashmap->capacity;\
    return CONTAINERS_ERR_OK;\
}

#endif
