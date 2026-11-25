#include <criterion/criterion.h>

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

Test(with_one_element, writes_element)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 10);

	getinto(&numbers, 0, val);

	cr_assert_eq(val, 10, "Actual value was %d", val);

	stg_vecfree(&numbers);
}

Test(with_two_elements, writes_element)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 10);
	stg_vecpush(&numbers, 20);

	getinto(&numbers, 1, val);

	cr_assert_eq(val, 20, "Actual value was %d", val);

	stg_vecfree(&numbers);
}

Test(with_no_elements, returns_false)
{
	newnums(numbers, 256);

	getinto(&numbers, 1, val);

	int ret = stg_vecget(&numbers, 1, &val);

	cr_assert_eq(ret, 0, "Return value was actually %c", ret);

	stg_vecfree(&numbers);
}

Test(with_one_element, returns_true_for_remove_last)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 42);

	int val = -1;

	int ret = stg_vecremlast(&numbers, &val);

	cr_assert(ret, "Actual return value was %d", ret);

	stg_vecfree(&numbers);
}

Test(with_one_element, writes_last_value_with_remove_last)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 42);

	reminto(&numbers, val);

	cr_assert_eq(val, 42, "Actual written value was %d", val);

	stg_vecfree(&numbers);
}

Test(with_two_elements, writes_last_value_with_remove_last)
{
	newnums(numbers, 256);

	stg_vecpush(&numbers, 24);
	stg_vecpush(&numbers, 42);

	reminto(&numbers, val);

	cr_assert_eq(val, 42, "Actual writen value was %d", val);

	stg_vecfree(&numbers);
}

Test(with_one_element, increases_capacity)
{
	newnums(numbers, 0);

	stg_vecpush(&numbers, 100);

	cr_assert_eq(stg_vecgetcap(&numbers), 1, "Actual capacity was %ld", stg_vecgetcap(&numbers));

	stg_vecfree(&numbers);
}

Test(with_two_elements, increases_capacity)
{
	newnums(numbers, 1);

	stg_vecpush(&numbers, 100);
	stg_vecpush(&numbers, 200);

	cr_assert_eq(stg_vecgetcap(&numbers), 2, "Actual capacity was %ld", stg_vecgetcap(&numbers));

	stg_vecfree(&numbers);
}

#undef newnums

#undef getinto

#undef reminto
