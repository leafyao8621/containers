#include <containers/hash.h>

size_t containers_hash_str(char **a) {
    char buf[sizeof(size_t)] = {0};
    size_t len = strlen(*a);
    if (len < sizeof(size_t)) {
        memcpy(buf, *a, len);
        return *(size_t*)buf;
    }
    char *iter = *a;
    size_t out = *(size_t*)a;
    ++iter;
    for (size_t i = 1; i <= len - sizeof(size_t); ++i, ++iter) {
        out ^= *(size_t*)iter;
    }
    return out;
}

size_t containers_hash_int8(int8_t *a) {
    return *a;
}

size_t containers_hash_uint8(uint8_t *a) {
    return *a;
}

size_t containers_hash_int16(int16_t *a) {
    return *a;
}

size_t containers_hash_uint16(uint16_t *a) {
    return *a;
}

size_t containers_hash_int32(int32_t *a) {
    return *a;
}

size_t containers_hash_uint32(uint32_t *a) {
    return *a;
}

size_t containers_hash_int64(int64_t *a) {
    return *a;
}

size_t containers_hash_uint64(uint64_t *a) {
    return *a;
}

size_t containers_hash_char(char *a) {
    return *a;
}

size_t containers_hash_short(short *a) {
    return *a;
}

size_t containers_hash_int(int *a) {
    return *a;
}

size_t containers_hash_long(long *a) {
    return *a;
}
size_t containers_hash_double(double *a) {
    return *a;
}

size_t containers_hash_float(float *a) {
    return *a;
}
