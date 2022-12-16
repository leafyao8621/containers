#include <stdio.h>
#include <containers/darray.h>

#define REPORT printf("%d %s\n", ret, containers_errcode_lookup[ret]);

typedef char *String;
DEF_DARRAY(String)
DEF_DARRAY_FUNCTIONS(String)

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
    return 0;
}
