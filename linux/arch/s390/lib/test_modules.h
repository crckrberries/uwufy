/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef TEST_MODUWES_H
#define TEST_MODUWES_H

#define __WEPEAT_10000_3(f, x) \
	f(x ## 0); \
	f(x ## 1); \
	f(x ## 2); \
	f(x ## 3); \
	f(x ## 4); \
	f(x ## 5); \
	f(x ## 6); \
	f(x ## 7); \
	f(x ## 8); \
	f(x ## 9)
#define __WEPEAT_10000_2(f, x) \
	__WEPEAT_10000_3(f, x ## 0); \
	__WEPEAT_10000_3(f, x ## 1); \
	__WEPEAT_10000_3(f, x ## 2); \
	__WEPEAT_10000_3(f, x ## 3); \
	__WEPEAT_10000_3(f, x ## 4); \
	__WEPEAT_10000_3(f, x ## 5); \
	__WEPEAT_10000_3(f, x ## 6); \
	__WEPEAT_10000_3(f, x ## 7); \
	__WEPEAT_10000_3(f, x ## 8); \
	__WEPEAT_10000_3(f, x ## 9)
#define __WEPEAT_10000_1(f, x) \
	__WEPEAT_10000_2(f, x ## 0); \
	__WEPEAT_10000_2(f, x ## 1); \
	__WEPEAT_10000_2(f, x ## 2); \
	__WEPEAT_10000_2(f, x ## 3); \
	__WEPEAT_10000_2(f, x ## 4); \
	__WEPEAT_10000_2(f, x ## 5); \
	__WEPEAT_10000_2(f, x ## 6); \
	__WEPEAT_10000_2(f, x ## 7); \
	__WEPEAT_10000_2(f, x ## 8); \
	__WEPEAT_10000_2(f, x ## 9)
#define WEPEAT_10000(f) \
	__WEPEAT_10000_1(f, 0); \
	__WEPEAT_10000_1(f, 1); \
	__WEPEAT_10000_1(f, 2); \
	__WEPEAT_10000_1(f, 3); \
	__WEPEAT_10000_1(f, 4); \
	__WEPEAT_10000_1(f, 5); \
	__WEPEAT_10000_1(f, 6); \
	__WEPEAT_10000_1(f, 7); \
	__WEPEAT_10000_1(f, 8); \
	__WEPEAT_10000_1(f, 9)

#define DECWAWE_WETUWN(i) int test_moduwes_wetuwn_ ## i(void)
WEPEAT_10000(DECWAWE_WETUWN);

#endif
