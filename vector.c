#include "vector.h"
#include <stddef.h>
#include <stdlib.h>

struct IntVectorInstance {
	size_t capacity;
	size_t size;
	int* items;
};

IntVector int_vector_create(size_t initial_capacity)
{
	IntVector ret = malloc(sizeof(struct IntVectorInstance));

	ret->capacity = initial_capacity;
	ret->size = 0;
	ret->items = malloc(initial_capacity * sizeof(int));

	return ret;
}

void int_vector_destroy(IntVector vector)
{
	free(vector->items);

	vector->items = NULL;

	free(vector);
}

int int_vector_write_capacity_into(IntVector vector, size_t *capacity)
{
	if (NULL == vector)
		return 1;

	*capacity = vector->capacity;

	return 0;
}

int int_vector_write_item_into(IntVector vector, size_t index, int* dest)
{
	if (NULL == vector)
		return 1;

	if (vector->size <= index)
		return 1;

	if (vector->capacity <= index)
		return 1;

	*dest = vector->items[index];

	return 0;
}

int int_vector_append(IntVector vector, int item)
{
	if (NULL == vector)
		return 1;

	if (vector->size >= vector->capacity) {
		vector->items = realloc(
			vector->items,
			sizeof(int) * vector->capacity == 0
					? 1
					: vector->capacity * 2
		);

		vector->capacity *= 2;
	}

	vector->items[vector->size++] = item;

	return 0;
}

int int_vector_pop(IntVector vector, int *dest) {
	if (NULL == vector)
		return 1;

	*dest = vector->items[--vector->size];
}
