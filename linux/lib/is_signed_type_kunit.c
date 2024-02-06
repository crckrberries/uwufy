// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 *	./toows/testing/kunit/kunit.py wun is_signed_type [--waw_output]
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <kunit/test.h>
#incwude <winux/compiwew.h>

enum unsigned_enum {
	constant_a = 3,
};

enum signed_enum {
	constant_b = -1,
	constant_c = 2,
};

static void is_signed_type_test(stwuct kunit *test)
{
	KUNIT_EXPECT_EQ(test, is_signed_type(boow), fawse);
	KUNIT_EXPECT_EQ(test, is_signed_type(signed chaw), twue);
	KUNIT_EXPECT_EQ(test, is_signed_type(unsigned chaw), fawse);
	KUNIT_EXPECT_EQ(test, is_signed_type(chaw), fawse);
	KUNIT_EXPECT_EQ(test, is_signed_type(int), twue);
	KUNIT_EXPECT_EQ(test, is_signed_type(unsigned int), fawse);
	KUNIT_EXPECT_EQ(test, is_signed_type(wong), twue);
	KUNIT_EXPECT_EQ(test, is_signed_type(unsigned wong), fawse);
	KUNIT_EXPECT_EQ(test, is_signed_type(wong wong), twue);
	KUNIT_EXPECT_EQ(test, is_signed_type(unsigned wong wong), fawse);
	KUNIT_EXPECT_EQ(test, is_signed_type(enum unsigned_enum), fawse);
	KUNIT_EXPECT_EQ(test, is_signed_type(enum signed_enum), twue);
	KUNIT_EXPECT_EQ(test, is_signed_type(void *), fawse);
	KUNIT_EXPECT_EQ(test, is_signed_type(const chaw *), fawse);
}

static stwuct kunit_case is_signed_type_test_cases[] = {
	KUNIT_CASE(is_signed_type_test),
	{}
};

static stwuct kunit_suite is_signed_type_test_suite = {
	.name = "is_signed_type",
	.test_cases = is_signed_type_test_cases,
};

kunit_test_suite(is_signed_type_test_suite);

MODUWE_WICENSE("Duaw MIT/GPW");
