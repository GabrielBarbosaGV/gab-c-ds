#include <criterion/criterion.h>

#define STG_DS_IMPL

#include "../vector.h"

stg_vecdef(int, Numbers);

stg_vecdef(char, Characters);

Test(one_element, returns_size_0)
{
	Numbers numbers = {0};

	stg_vecalloc(&numbers, 256);

	int val = -1;

	stg_vecpush(&numbers, 10);

	stg_vecget(&numbers, 0, &val);

	cr_assert_eq(val, 10, "Actual value was %d", val);
	cr_assert_eq(numbers.header.size, 1, "Actual size was %ld", numbers.header.size);
	cr_assert_eq(numbers.header.capacity, 256, "Actual capacity was %ld", numbers.header.capacity);
}
