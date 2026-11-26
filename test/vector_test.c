#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/logging.h>

#define STG_DS_IMPL

#include "../vector.h"

stg_vecdef(int, Numbers);

stg_vecdef(char, Characters);

#define newnums(name, initial_capacity)			\
	Numbers (name) = {0};				\
	stg_vecalloc(&(name), (initial_capacity))

#define getinto(name, index, dest)		\
	int (dest) = -1;			\
	stg_vecget((name), index, &(dest))	

#define reminto(name, dest)		\
	int (dest) = -1;		\
	stg_vecremlast((name), &(dest))

Test(writes_element, with_one_element)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 10);

	getinto(&numbers, 0, val);

	cr_assert_eq(val, 10, "Actual value was %d", val);

	stg_vecfree(&numbers);
}

Test(writes_element, with_two_elements)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 10);
	stg_vecpush(&numbers, 20);

	getinto(&numbers, 1, val);

	cr_assert_eq(val, 20, "Actual value was %d", val);

	stg_vecfree(&numbers);
}

Test(returns_false, with_no_elements)
{
	newnums(numbers, 256);

	getinto(&numbers, 1, val);

	int ret = stg_vecget(&numbers, 1, &val);

	cr_assert_eq(ret, 0, "Return value was actually %c", ret);

	stg_vecfree(&numbers);
}

Test(returns_true_for_remove_last, with_one_element)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 42);

	int val = -1;

	int ret = stg_vecremlast(&numbers, &val);

	cr_assert(ret, "Actual return value was %d", ret);

	stg_vecfree(&numbers);
}

Test(writes_last_value_with_remove_last, with_one_element)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 42);

	reminto(&numbers, val);

	cr_assert_eq(val, 42, "Actual written value was %d", val);

	stg_vecfree(&numbers);
}

Test(writes_last_value_with_remove_last, with_two_elements)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 24);
	stg_vecpush(&numbers, 42);

	reminto(&numbers, val);

	cr_assert_eq(val, 42, "Actual writen value was %d", val);

	stg_vecfree(&numbers);
}

Test(increases_capacity, with_one_element)
{
	newnums(numbers, 0);

	stg_vecpush(&numbers, 100);

	cr_assert_eq(stg_vecgetcap(&numbers), 1, "Actual capacity was %ld", stg_vecgetcap(&numbers));

	stg_vecfree(&numbers);
}

Test(increases_capacity, with_two_elements)
{
	newnums(numbers, 0);

	stg_vecpush(&numbers, 100);
	stg_vecpush(&numbers, 200);

	cr_assert_eq(stg_vecgetcap(&numbers), 2, "Actual capacity was %ld", stg_vecgetcap(&numbers));

	stg_vecfree(&numbers);
}

Test(doubles_capacity, with_three_elements)
{
	newnums(numbers, 0);

	stg_vecpush(&numbers, 1);
	stg_vecpush(&numbers, 2);
	stg_vecpush(&numbers, 3);

	cr_assert_eq(stg_vecgetcap(&numbers), 4, "Actual capacity was %ld", stg_vecgetcap(&numbers));

	stg_vecfree(&numbers);
}

Test(doubles_capacity, with_five_elements)
{
	newnums(numbers, 0);

	stg_vecpush(&numbers, 1);
	stg_vecpush(&numbers, 2);
	stg_vecpush(&numbers, 3);
	stg_vecpush(&numbers, 4);
	stg_vecpush(&numbers, 5);

	cr_assert_eq(stg_vecgetcap(&numbers), 8, "Actual capacity was %ld", stg_vecgetcap(&numbers));

	stg_vecfree(&numbers);
}

Test(shrinks, with_five_elements)
{
	newnums(numbers, 0);

	stg_vecpush(&numbers, 1);
	stg_vecpush(&numbers, 2);
	stg_vecpush(&numbers, 3);
	stg_vecpush(&numbers, 4);
	stg_vecpush(&numbers, 5);

	reminto(&numbers, dest0);
	reminto(&numbers, dest1);
	reminto(&numbers, dest2);

	cr_assert_eq(stg_vecgetcap(&numbers), 4, "Actual capacity was %ld", stg_vecgetcap(&numbers));

	stg_vecfree(&numbers);
}

#undef newnums

#undef getinto

#undef reminto
