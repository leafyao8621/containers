#include <stdio.h>
#include <containers/darray.h>

#define REPORT printf("%d %s\n", ret, containers_errcode_lookup[ret]);

typedef const char *String;
DEF_DARRAY(String)
DEF_DARRAY_FUNCTIONS(String)

int main(void) {
    DArrayString darray;
    int ret = DArrayString_initialize(&darray, 10);
    REPORT
    ret = DArrayString_finalize(&darray);
    REPORT
    return 0;
}
