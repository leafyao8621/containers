#ifndef CONTAINERS_HASH_H_
#define CONTAINERS_HASH_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <containers/dstring.h>

size_t containers_hash_str(char **a);
size_t containers_hash_dstr(String *a);
size_t containers_hash_int8(int8_t *a);
size_t containers_hash_uint8(uint8_t *a);
size_t containers_hash_int16(int16_t *a);
size_t containers_hash_uint16(uint16_t *a);
size_t containers_hash_int32(int32_t *a);
size_t containers_hash_uint32(uint32_t *a);
size_t containers_hash_int64(int64_t *a);
size_t containers_hash_uint64(uint64_t *a);
size_t containers_hash_char(char *a);
size_t containers_hash_short(short *a);
size_t containers_hash_int(int *a);
size_t containers_hash_long(long *a);
size_t containers_hash_double(double *a);
size_t containers_hash_float(float *a);

#endif
