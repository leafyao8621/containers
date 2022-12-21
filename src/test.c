#include <stdio.h>
#include <containers/darray.h>
#include <containers/hashset.h>
#include <containers/hashmap.h>
#include <containers/eq.h>
#include <containers/hash.h>

#define REPORT printf("%d %s\n", ret, containers_errcode_lookup[ret]);

typedef char *String;
typedef int Int;
DEF_DARRAY(String)
DEF_DARRAY_FUNCTIONS(String)
DEF_HASHSET(String)
DEF_HASHSET_FUNCTIONS(String)
DEF_HASHMAP(String, Int)
DEF_HASHMAP_FUNCTIONS(String, Int)

int main(void) {
    DArrayString darray;
    int ret = DArrayString_initialize(&darray, 2);
    REPORT
    char *buf[] = {
        "0",
        "1",
        "2",
        "3",
        "4"
    };
    for (int i = 0; i < 5; ++i) {
        ret = DArrayString_push_back(&darray, buf + i);
        REPORT
    }
    ret = DArrayString_push_back_batch(&darray, buf, 5);
    REPORT
    printf("%lu %lu\n", darray.size, darray.capacity);
    for (int i = 0; i < 10; ++i) {
        printf("%s\n", darray.data[i]);
    }
    ret = DArrayString_finalize(&darray);
    REPORT
    char *buf_hs[] = {
        "abcde",
        "adqwe124",
        "adqwe124",
        "qwertttt123",
        "adqwe1245",
        "xxhsaklfjsalfksadljklasd"
    };
    HashSetString hashset;
    ret =
        HashSetString_initialize(
            &hashset,
            2,
            containers_eq_str,
            containers_hash_str
        );
    REPORT
    for (int i = 0; i < 6; ++i) {
        ret = HashSetString_insert(&hashset, buf_hs + i);
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
        ret = HashSetString_find(&hashset, &buf_hs_find[i], &found);
        REPORT
        printf("found: %hhd\n", found);
    }
    ret = HashSetString_finalize(&hashset);
    REPORT
    int buf_val[] = {
        0,
        1,
        2,
        3,
        4,
        5
    };
    HashMapStringInt hashmap;
    ret =
        HashMapStringInt_initialize(
            &hashmap,
            2,
            containers_eq_str,
            containers_hash_str
        );
    REPORT
    for (int i = 0; i < 6; ++i) {
        int *res = 0;
        ret = HashMapStringInt_fetch(&hashmap, buf_hs + i, &res);
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
        ret = HashMapStringInt_find(&hashmap, &buf_hs_find[i], &found);
        REPORT
        printf("found: %hhd\n", found);
    }
    ret = HashMapStringInt_finalize(&hashmap);
    REPORT
    return 0;
}
