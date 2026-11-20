#include "../vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <criterion/logging.h>
#include <stddef.h>

#define gab_zero_ret_assert(ret_name) 							\
	do { 										\
		cr_assert_eq((ret_name), 0, "Expected return value to be 0 (success)"); \
	} while (0) 									\

#define test_vector(capacity, capacity_name, vector_name) 		\
	size_t (capacity_name) = (capacity); 				\
	IntVector (vector_name) = int_vector_create((capacity)); 	\

#define append(vector_name, val) 				\
	do { 							\
		int_vector_append((vector_name), (val)); 	\
	} while (0) 						\

#define get_capacity(vector_name, dest) 			\
	size_t (dest); 						\
	int_vector_write_capacity_into((vector_name), &(dest)); \

#define get_item(vector_name, index, dest) 				\
	int (dest); 							\
	int_vector_write_item_into((vector_name), index, &(dest)); 	\

#define pop(vector_name, dest) 			\
	int (dest); 				\
	int_vector_pop((vector_name), &(dest)); \

Test(empty, writes_initial_capacity)
{
	test_vector(256, cap, vec);

	get_capacity(vec, actual_capacity);

        cr_expect(cap == actual_capacity, "Initial capacity was not equal to actual capacity");

	int_vector_destroy(vec);
}

Test(empty, fails_with_1_for_any_item_retrieval_attempt)
{
	test_vector(256, cap, vec);
	
	int item;

	int ret = int_vector_write_item_into(vec, 0, &item);

	cr_expect(ret == 1, "Return value was different from 1");
}

Test(appending, appends_item)
{
	size_t cap = 256;

	IntVector vec = int_vector_create(cap);

	int item_to_append = 10;

	append(vec, item_to_append);

	int item_to_retrieve;

	int ret = int_vector_write_item_into(vec, 0, &item_to_retrieve);

	gab_zero_ret_assert(ret);

	cr_assert_eq(item_to_retrieve, 10);
}

Test(appending, expands_vector)
{
	test_vector(1, cap, vec);

	append(vec, 1);

	append(vec, 2);

	int item_to_retrieve;

	int ret = int_vector_write_item_into(vec, 1, &item_to_retrieve);

	gab_zero_ret_assert(ret);

	cr_assert_eq(item_to_retrieve, 2);
}

Test(appending, returns_new_capacity)
{
	test_vector(1, cap, vec);

	append(vec, 1);
	append(vec, 2);

	get_capacity(vec, actual_cap);
	cr_assert_eq(actual_cap, 2);

	append(vec, 3);

	get_capacity(vec, actual_cap_2);
	cr_assert_eq(actual_cap_2, 4);

	get_capacity(vec, actual_cap_3);

	cr_expect_eq(actual_cap_3, 4);
}

Test(popping, errors_on_retrieval_of_smaller_item)
{
	test_vector(1, cap, vec);

	append(vec, 1);
	append(vec, 2);

	pop(vec, popped);

	cr_assert_eq(popped, 2);

	int dest;

	int ret = int_vector_write_item_into(vec, 1, &dest);

	cr_assert_eq(ret, 1);
}

#undef test_vector
#undef append
#undef get_capacity
#undef get_item
#undef gab_zero_ret_assert
#undef pop
