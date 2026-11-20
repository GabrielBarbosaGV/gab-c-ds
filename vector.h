#ifndef GABRIEL_DS_LIB
#define GABRIEL_DS_LIB

#include <stddef.h>

typedef struct IntVectorInstance *IntVector;

IntVector int_vector_create(size_t initial_capacity);

void int_vector_destroy(IntVector vector);

int int_vector_write_capacity_into(IntVector vector, size_t *capacity);

int int_vector_write_item_into(IntVector vector, size_t index, int *dest);

int int_vector_append(IntVector vector, int item);

int int_vector_pop(IntVector vector, int *dest);

#endif
