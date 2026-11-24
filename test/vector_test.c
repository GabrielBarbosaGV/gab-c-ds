#include <criterion/criterion.h>

#define STG_DS_IMPL

#include "../vector.h"

stg_vecdef(int, Numbers);

stg_vecdef(char, Characters);

Test(with_one_element, writes_element)
{
	Numbers numbers = {0};

	stg_vecalloc(&numbers, 256);

	int val = - 1;

	stg_vecpush(&numbers, 10);

	stg_vecget(&numbers, 0, &val);

	cr_assert_eq(val, 10, "Actual value was %d", val);

	stg_vecfree(&numbers);
}

Test(with_two_elements, writes_element)
{
	Numbers numbers = {0};

	stg_vecalloc(&numbers, 256);

	stg_vecpush(&numbers, 10);
	stg_vecpush(&numbers, 20);

	int val = - 1;

	stg_vecget(&numbers, 1, &val);

	cr_assert_eq(val, 20, "Actual value was %d", val);

	stg_vecfree(&numbers);
}

Test(with_no_elements, returns_false)
{
	Numbers numbers = {0};

	stg_vecalloc(&numbers, 256);

	int val = -1;

	int ret = stg_vecget(&numbers, 1, &val);

	cr_assert_eq(ret, 0, "Return value was actually %c", ret);

	stg_vecfree(&numbers);
}

/*
Test(with_one_element, removes_last)
{

}

*/
