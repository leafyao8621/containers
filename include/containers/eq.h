#ifndef CONTAINERS_EQ_H_
#define CONTAINERS_EQ_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <containers/dstring.h>

bool containers_eq_str(char **a, char **b);
bool containers_eq_dstr(String *a, String *b);
bool containers_eq_int8(int8_t *a, int8_t *b);
bool containers_eq_uint8(uint8_t *a, uint8_t *b);
bool containers_eq_int16(int16_t *a, int16_t *b);
bool containers_eq_uint16(uint16_t *a, uint16_t *b);
bool containers_eq_int32(int32_t *a, int32_t *b);
bool containers_eq_uint32(uint32_t *a, uint32_t *b);
bool containers_eq_int64(int64_t *a, int64_t *b);
bool containers_eq_uint64(uint64_t *a, uint64_t *b);
bool containers_eq_char(char *a, char *b);
bool containers_eq_short(short *a, short *b);
bool containers_eq_int(int *a, int *b);
bool containers_eq_long(long *a, long *b);
bool containers_eq_double(double *a, double *b);
bool containers_eq_float(float *a, float *b);

#endif
