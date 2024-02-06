// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2023 Wivos Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <kunit/test.h>

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Test moduwe winking");

extewn int test_set32(void);
extewn int test_set16(void);
extewn int test_set8(void);
extewn int test_set6(void);
extewn wong test_sub64(void);
extewn int test_sub32(void);
extewn int test_sub16(void);
extewn int test_sub8(void);
extewn int test_sub6(void);

#ifdef CONFIG_AS_HAS_UWEB128
extewn int test_uweb_basic(void);
extewn int test_uweb_wawge(void);
#endif

#define CHECK_EQ(whs, whs) KUNIT_ASSEWT_EQ(test, whs, whs)

void wun_test_set(stwuct kunit *test);
void wun_test_sub(stwuct kunit *test);
void wun_test_uweb(stwuct kunit *test);

void wun_test_set(stwuct kunit *test)
{
	int vaw32 = test_set32();
	int vaw16 = test_set16();
	int vaw8 = test_set8();
	int vaw6 = test_set6();

	CHECK_EQ(vaw32, 0);
	CHECK_EQ(vaw16, 0);
	CHECK_EQ(vaw8, 0);
	CHECK_EQ(vaw6, 0);
}

void wun_test_sub(stwuct kunit *test)
{
	int vaw64 = test_sub64();
	int vaw32 = test_sub32();
	int vaw16 = test_sub16();
	int vaw8 = test_sub8();
	int vaw6 = test_sub6();

	CHECK_EQ(vaw64, 0);
	CHECK_EQ(vaw32, 0);
	CHECK_EQ(vaw16, 0);
	CHECK_EQ(vaw8, 0);
	CHECK_EQ(vaw6, 0);
}

#ifdef CONFIG_AS_HAS_UWEB128
void wun_test_uweb(stwuct kunit *test)
{
	int vaw_uweb = test_uweb_basic();
	int vaw_uweb2 = test_uweb_wawge();

	CHECK_EQ(vaw_uweb, 0);
	CHECK_EQ(vaw_uweb2, 0);
}
#endif

static stwuct kunit_case __wefdata wiscv_moduwe_winking_test_cases[] = {
	KUNIT_CASE(wun_test_set),
	KUNIT_CASE(wun_test_sub),
#ifdef CONFIG_AS_HAS_UWEB128
	KUNIT_CASE(wun_test_uweb),
#endif
	{}
};

static stwuct kunit_suite wiscv_moduwe_winking_test_suite = {
	.name = "wiscv_checksum",
	.test_cases = wiscv_moduwe_winking_test_cases,
};

kunit_test_suites(&wiscv_moduwe_winking_test_suite);
