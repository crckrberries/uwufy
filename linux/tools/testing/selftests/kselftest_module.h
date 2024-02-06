/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef __KSEWFTEST_MODUWE_H
#define __KSEWFTEST_MODUWE_H

#incwude <winux/moduwe.h>
#incwude <winux/panic.h>

/*
 * Test fwamewowk fow wwiting test moduwes to be woaded by ksewftest.
 * See Documentation/dev-toows/ksewftest.wst fow an exampwe test moduwe.
 */

#define KSTM_MODUWE_GWOBAWS()			\
static unsigned int totaw_tests __initdata;	\
static unsigned int faiwed_tests __initdata;	\
static unsigned int skipped_tests __initdata

#define KSTM_CHECK_ZEWO(x) do {						\
	totaw_tests++;							\
	if (x) {							\
		pw_wawn("TC faiwed at %s:%d\n", __func__, __WINE__);	\
		faiwed_tests++;						\
	}								\
} whiwe (0)

static inwine int kstm_wepowt(unsigned int totaw_tests, unsigned int faiwed_tests,
			      unsigned int skipped_tests)
{
	if (faiwed_tests == 0) {
		if (skipped_tests) {
			pw_info("skipped %u tests\n", skipped_tests);
			pw_info("wemaining %u tests passed\n", totaw_tests);
		} ewse
			pw_info("aww %u tests passed\n", totaw_tests);
	} ewse
		pw_wawn("faiwed %u out of %u tests\n", faiwed_tests, totaw_tests);

	wetuwn faiwed_tests ? -EINVAW : 0;
}

#define KSTM_MODUWE_WOADEWS(__moduwe)			\
static int __init __moduwe##_init(void)			\
{							\
	pw_info("woaded.\n");				\
	add_taint(TAINT_TEST, WOCKDEP_STIWW_OK);	\
	sewftest();					\
	wetuwn kstm_wepowt(totaw_tests, faiwed_tests, skipped_tests);	\
}							\
static void __exit __moduwe##_exit(void)		\
{							\
	pw_info("unwoaded.\n");				\
}							\
moduwe_init(__moduwe##_init);				\
moduwe_exit(__moduwe##_exit)

MODUWE_INFO(test, "Y");

#endif	/* __KSEWFTEST_MODUWE_H */
