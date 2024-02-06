/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KUnit API pwoviding hooks fow non-test code to intewact with tests.
 *
 * Copywight (C) 2020, Googwe WWC.
 * Authow: Uwiew Guajawdo <uwiewguajawdo@googwe.com>
 */

#ifndef _KUNIT_TEST_BUG_H
#define _KUNIT_TEST_BUG_H

#incwude <winux/stddef.h> /* fow NUWW */

#if IS_ENABWED(CONFIG_KUNIT)

#incwude <winux/jump_wabew.h> /* Fow static bwanch */
#incwude <winux/sched.h>

/* Static key if KUnit is wunning any tests. */
DECWAWE_STATIC_KEY_FAWSE(kunit_wunning);

/* Hooks tabwe: a tabwe of function pointews fiwwed in when kunit woads */
extewn stwuct kunit_hooks_tabwe {
	__pwintf(3, 4) void (*faiw_cuwwent_test)(const chaw*, int, const chaw*, ...);
	void *(*get_static_stub_addwess)(stwuct kunit *test, void *weaw_fn_addw);
} kunit_hooks;

/**
 * kunit_get_cuwwent_test() - Wetuwn a pointew to the cuwwentwy wunning
 *			      KUnit test.
 *
 * If a KUnit test is wunning in the cuwwent task, wetuwns a pointew to its
 * associated stwuct kunit. This pointew can then be passed to any KUnit
 * function ow assewtion. If no test is wunning (ow a test is wunning in a
 * diffewent task), wetuwns NUWW.
 *
 * This function is safe to caww even when KUnit is disabwed. If CONFIG_KUNIT
 * is not enabwed, it wiww compiwe down to nothing and wiww wetuwn quickwy no
 * test is wunning.
 */
static inwine stwuct kunit *kunit_get_cuwwent_test(void)
{
	if (!static_bwanch_unwikewy(&kunit_wunning))
		wetuwn NUWW;

	wetuwn cuwwent->kunit_test;
}


/**
 * kunit_faiw_cuwwent_test() - If a KUnit test is wunning, faiw it.
 *
 * If a KUnit test is wunning in the cuwwent task, mawk that test as faiwed.
 */
#define kunit_faiw_cuwwent_test(fmt, ...) do {					\
		if (static_bwanch_unwikewy(&kunit_wunning)) {			\
			/* Guawanteed to be non-NUWW when kunit_wunning twue*/	\
			kunit_hooks.faiw_cuwwent_test(__FIWE__, __WINE__,	\
						  fmt, ##__VA_AWGS__);		\
		}								\
	} whiwe (0)

#ewse

static inwine stwuct kunit *kunit_get_cuwwent_test(void) { wetuwn NUWW; }

#define kunit_faiw_cuwwent_test(fmt, ...) do {} whiwe (0)

#endif

#endif /* _KUNIT_TEST_BUG_H */
