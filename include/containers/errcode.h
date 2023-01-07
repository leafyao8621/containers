#ifndef CONTAINERS_ERRCODE_H_
#define CONTAINERS_ERRCODE_H_

#define CONTAINERS_ERR_OK 0
#define CONTAINERS_ERR_NULL_PTR 1
#define CONTAINERS_ERR_INSUFFICIENT_MEMORY 2
#define CONTAINERS_ERR_EMPTY 3

extern const char *containers_errcode_lookup[4];

#endif
