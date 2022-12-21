#include <stdio.h>
#include <containers/darray.h>
#include <containers/hashset.h>
#include <containers/eq.h>
#include <containers/hash.h>

#define REPORT printf("%d %s\n", ret, containers_errcode_lookup[ret]);

typedef char *String;
DEF_DARRAY(String)
DEF_DARRAY_FUNCTIONS(String)
DEF_HASHSET(String)
DEF_HASHSET_FUNCTIONS(String)

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
        "adqwe1245"
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
    for (int i = 0; i < 5; ++i) {
        ret = HashSetString_insert(&hashset, buf_hs + i);
        REPORT
    }
    for (size_t i = 0; i < hashset.capacity; ++i) {
        printf(
            "in_use: %hhd value: %s\n",
            hashset.data[i].in_use,
            hashset.data[i].data
        );
    }
    ret = HashSetString_finalize(&hashset);
    REPORT
    return 0;
}
