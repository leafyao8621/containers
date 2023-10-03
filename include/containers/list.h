#ifndef CONTAINERS_LIST_H_
#define CONTAINERS_LIST_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <containers/errcode.h>

#define DEF_LIST(Type)\
typedef struct List##Type##Node {\
    Type data;\
    struct List##Type##Node *prev;\
    struct List##Type##Node *next;\
} List##Type##Node;\
typedef struct List##Type {\
    size_t size;\
    List##Type##Node *head;\
    List##Type##Node *tail;\
    int (*finalizer)(Type*);\
} List##Type;\
int List##Type##_initialize(List##Type *list, int (*finalizer)(Type*));\
int List##Type##_finalize(List##Type *list);\
int List##Type##_push_back(List##Type *list, Type *data);\

#define DEF_LIST_FUNCTIONS(Type)\
int List##Type##_initialize(List##Type *list, int (*finalizer)(Type*)) {\
    if (!list) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    list->size = 0;\
    list->head = NULL;\
    list->tail = NULL;\
    list->finalizer = finalizer;\
    return CONTAINERS_ERR_OK;\
}\
int List##Type##_finalize(List##Type *list) {\
    if (!list) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    int ret = CONTAINERS_ERR_OK;\
    List##Type##Node *temp = NULL;\
    for (List##Type##Node *i = list->head; i;) {\
        if (list->finalizer) {\
            ret = list->finalizer(&i->data);\
            if (ret) {\
                return CONTAINERS_ERR_FINALIZER;\
            }\
        }\
        temp = i;\
        i = i->next;\
        free(temp);\
    }\
    return ret;\
}\
int List##Type##_push_back(List##Type *list, Type *data) {\
    if (!list) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    List##Type##Node *temp = malloc(sizeof(List##Type##Node));\
    temp->data = *data;\
    temp->prev = list->tail;\
    temp->next = NULL;\
    if (list->size) {\
        list->tail->next = temp;\
    }\
    list->tail = temp;\
    if (!list->size) {\
        list->head = temp;\
    }\
    ++list->size;\
    return CONTAINERS_ERR_OK;\
}\
int List##Type##_pop_back(List##Type *list) {\
    if (!list) {\
        return CONTAINERS_ERR_NULL_PTR;\
    }\
    if (!list->size) {\
        return CONTAINERS_ERR_EMPTY;\
    }\
    if (list->finalizer) {\
        list->finalizer(&list->tail->data);\
    }\
    list->tail = list->tail->prev;\
    if (list->tail) {\
        list->tail->next = NULL;\
    } else {\
        list->head = NULL;\
    }\
    --list->size;\
    return CONTAINERS_ERR_OK;\
}\

#endif
