#include <stddef.h>
#include <stdlib.h>

#ifndef STG_DS_VECTOR_H
#define STG_DS_VECTOR_H

typedef struct {
  size_t size;
  size_t capacity;
} VecHeader;

#ifdef STG_DS_IMPL

#define stg_vecdef(item_type, type_name)                                       \
  typedef struct {                                                             \
    VecHeader header;                                                          \
    item_type *items;                                                          \
  } type_name;

#define stg_vecget(vec, index, dest)                                           \
  (!((vec) && ((index) < (vec)->header.size))                                  \
       ? 0                                                                     \
       : (*(dest) = ((vec)->items[(index)]), 1))

#define stg_vecalloc(vec, initial_capacity)                                    \
  ((vec)->items = malloc((initial_capacity) * sizeof(*((vec)->items))),        \
   ((vec)->header.size = 0), ((vec)->header.capacity = initial_capacity), 1)

#define stg_vecpush(vec, item)                                                 \
  (((vec)->header.capacity <= (vec)->header.size)                              \
       ? 0                                                                     \
       : ((((vec)->items)[(vec)->header.size++] = (item)), 1))

#endif

#endif
