#include <containers/eq.h>

bool containers_eq_str(char **a, char **b) {
    return !strcmp(*a, *b);
}

bool containers_eq_int8(int8_t *a, int8_t *b) {
    return *a == *b;
}

bool containers_eq_uint8(uint8_t *a, uint8_t *b) {
    return *a == *b;
}

bool containers_eq_int16(int16_t *a, int16_t *b) {
    return *a == *b;
}

bool containers_eq_uint16(uint16_t *a, uint16_t *b) {
    return *a == *b;
}

bool containers_eq_int32(int32_t *a, int32_t *b) {
    return *a == *b;
}

bool containers_eq_uint32(uint32_t *a, uint32_t *b) {
    return *a == *b;
}

bool containers_eq_int64(int64_t *a, int64_t *b) {
    return *a == *b;
}

bool containers_eq_uint64(uint64_t *a, uint64_t *b) {
    return *a == *b;
}

bool containers_eq_char(char *a, char *b) {
    return *a == *b;
}

bool containers_eq_short(short *a, short *b) {
    return *a == *b;
}

bool containers_eq_int(int *a, int *b) {
    return *a == *b;
}

bool containers_eq_long(long *a, long *b) {
    return *a == *b;
}

bool containers_eq_double(double *a, double *b) {
    return *a == *b;
}

bool containers_eq_float(float *a, float *b) {
    return *a == *b;
}
