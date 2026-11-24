#include <stddef.h>
#include <stdlib.h>

#ifndef STG_DS_VECTOR_H
#define STG_DS_VECTOR_H

typedef struct {
	size_t capacity;
	size_t start_index;
	size_t end_index;
} VecHeader;

#define __stg_vecsize(vec)					\
	((vec)->header.end_index - (vec)->header.start_index)	\

#define __stg_vecgrow(vec) (													\
	(vec)->items = realloc((vec)->items, __stg_vecsize((vec)) > 0 ? sizeof(*(vec)->items) * __stg_vecsize((vec)) : 1),	\
			(vec)->header.end_index = __stg_vecsize((vec)),								\
			(vec)->header.start_index = 0,										\
			1													\
)

#define __stg_vecputend(vec, item)								\
	((vec)->items[(vec)->header.start_index + __stg_vecsize((vec))] = (item), (vec)->header.end_index++, 1)

#define stg_vecdef(item_type, type_name)		\
	typedef struct {				\
		VecHeader header;			\
		item_type *items;			\
	} type_name

#define stg_vecget(vec, index, dest)				\
	(!((vec) && ((index) <= __stg_vecsize(vec)))		\
		? 0						\
		: (*(dest) = ((vec)->items[(index)]), 1))

#define stg_vecalloc(vec, initial_capacity)											\
	((vec)->items = malloc((initial_capacity) * sizeof(*((vec)->items))),							\
		((vec)->header.start_index = 0), ((vec)->header.end_index = 0), ((vec)->header.capacity = initial_capacity), 1)

#define stg_vecpush(vec, item)							\
	(((vec)->header.capacity <= (vec)->header.end_index)			\
		? (__stg_vecgrow((vec)), __stg_vecputend((vec), (item)), 1)	\
		: (__stg_vecputend((vec), (item))), 1)

#define stg_vecfree(vec)					\
	(vec)							\
		? (free((vec)->items), (vec)->items = NULL, 1)	\
		: 0

#define stg_remlast(vec, dest)										\
	(((vec) && (vec)->size > 0) ? (((vec)->size), (*(dest) = (vec)->items[--(vec)->size]) 1) : 0)	\

#ifdef STG_DS_IMPL

#endif

#endif
