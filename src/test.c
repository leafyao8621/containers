#include <stdio.h>
#include <containers/darray.h>
#include <containers/hashset.h>
#include <containers/hashmap.h>
#include <containers/list.h>
#include <containers/eq.h>
#include <containers/hash.h>

#define REPORT printf("%d %s\n", ret, containers_errcode_lookup[ret]);

typedef char *SString;
typedef int Int;
DEF_DARRAY(SString)
DEF_DARRAY_FUNCTIONS(SString)
DEF_HASHSET(SString)
DEF_HASHSET_FUNCTIONS(SString)
DEF_HASHMAP(SString, Int)
DEF_HASHMAP_FUNCTIONS(SString, Int)
DEF_LIST(SString)
DEF_LIST_FUNCTIONS(SString)

int main(void) {
    DArraySString darray;
    int ret = DArraySString_initialize(&darray, 2);
    REPORT
    char *buf[] = {
        "0",
        "1",
        "2",
        "3",
        "4"
    };
    for (int i = 0; i < 5; ++i) {
        ret = DArraySString_push_back(&darray, buf + i);
        REPORT
    }
    ret = DArraySString_push_back_batch(&darray, buf, 5);
    REPORT
    printf("%lu %lu\n", darray.size, darray.capacity);
    for (int i = 0; i < 10; ++i) {
        printf("%s\n", darray.data[i]);
    }
    ret = DArraySString_expand(&darray, 2, true);
    REPORT
    printf("%lu %lu\n", darray.size, darray.capacity);
    for (int i = 0; i < 12; ++i) {
        printf("%p\n", darray.data[i]);
    }
    ret = DArraySString_expand(&darray, 2, false);
    REPORT
    printf("%lu %lu\n", darray.size, darray.capacity);
    for (int i = 0; i < 14; ++i) {
        printf("%p\n", darray.data[i]);
    }
    ret = DArraySString_finalize(&darray);
    REPORT
    char *buf_hs[] = {
        "abcde",
        "adqwe124",
        "adqwe124",
        "qwertttt123",
        "adqwe1245",
        "xxhsaklfjsalfksadljklasd"
    };
    HashSetSString hashset;
    ret =
        HashSetSString_initialize(
            &hashset,
            2,
            containers_eq_str,
            containers_hash_str
        );
    REPORT
    for (int i = 0; i < 6; ++i) {
        ret = HashSetSString_insert(&hashset, buf_hs + i);
        REPORT
    }
    for (size_t i = 0; i < hashset.capacity; ++i) {
        printf(
            "in_use: %hhd data: %s\n",
            hashset.data[i].in_use,
            hashset.data[i].data
        );
    }
    char *buf_hs_find[] = {
        "abcd",
        "adqwe124",
        "adqwe1243",
        "qwertttt123",
        "adqwe1245",
        "ssqkl"
    };
    for (size_t i = 0; i < 6; ++i) {
        bool found = false;
        ret = HashSetSString_find(&hashset, &buf_hs_find[i], &found);
        REPORT
        printf("found: %hhd\n", found);
    }
    ret = HashSetSString_finalize(&hashset);
    REPORT
    int buf_val[] = {
        0,
        1,
        2,
        3,
        4,
        5
    };
    HashMapSStringInt hashmap;
    ret =
        HashMapSStringInt_initialize(
            &hashmap,
            2,
            containers_eq_str,
            containers_hash_str
        );
    REPORT
    for (int i = 0; i < 6; ++i) {
        int *res = 0;
        ret = HashMapSStringInt_fetch(&hashmap, buf_hs + i, &res);
        REPORT
        *res = buf_val[i];
    }
    for (size_t i = 0; i < hashmap.capacity; ++i) {
        printf(
            "in_use: %hhd key: %s value: %d\n",
            hashmap.data[i].in_use,
            hashmap.data[i].key,
            hashmap.data[i].value
        );
    }
    for (size_t i = 0; i < 6; ++i) {
        bool found = false;
        ret = HashMapSStringInt_find(&hashmap, &buf_hs_find[i], &found);
        REPORT
        printf("found: %hhd\n", found);
    }
    ret = HashMapSStringInt_finalize(&hashmap);
    REPORT
    ListSString list;
    ret = ListSString_initialize(&list, NULL);
    REPORT
    for (int i = 0; i < 5; ++i) {
        ret = ListSString_push_back(&list, buf + i);
        REPORT
    }
    printf("size: %lu\n", list.size);
    for (ListSStringNode *i = list.head; i; i = i->next) {
        printf("%s\n", i->data);
    }
    for (ListSStringNode *i = list.tail; i; i = i->prev) {
        printf("%s\n", i->data);
    }
    for (int i = 0; i < 6; ++i) {
        ret = ListSString_pop_back(&list);
        REPORT
    }
    for (int i = 0; i < 5; ++i) {
        ret = ListSString_push_back(&list, buf + i);
        REPORT
    }
    for (ListSStringNode *i = list.head; i; i = i->next) {
        printf("%s\n", i->data);
    }
    for (ListSStringNode *i = list.tail; i; i = i->prev) {
        printf("%s\n", i->data);
    }
    for (int i = 0; i < 3; ++i) {
        ret = ListSString_pop_back(&list);
        REPORT
    }
    for (ListSStringNode *i = list.head; i; i = i->next) {
        printf("%s\n", i->data);
    }
    for (ListSStringNode *i = list.tail; i; i = i->prev) {
        printf("%s\n", i->data);
    }
     for (int i = 0; i < 5; ++i) {
        ret = ListSString_push_back(&list, buf + i);
        REPORT
    }
    for (ListSStringNode *i = list.head; i; i = i->next) {
        printf("%s\n", i->data);
    }
    for (ListSStringNode *i = list.tail; i; i = i->prev) {
        printf("%s\n", i->data);
    }
    ret = ListSString_finalize(&list);
    REPORT
    return 0;
}
