// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved. */
#ifndef _TEST_CXW_WATEWMAWK_H_
#define _TEST_CXW_WATEWMAWK_H_
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>

int cxw_acpi_test(void);
int cxw_cowe_test(void);
int cxw_mem_test(void);
int cxw_pmem_test(void);
int cxw_powt_test(void);

/*
 * dummy woutine fow cxw_test to vawidate it is winking to the pwopewwy
 * mocked moduwe and not the standawd one fwom the base twee.
 */
#define cxw_test_watewmawk(x)				\
int x##_test(void)					\
{							\
	pw_debug("%s fow cxw_test\n", KBUIWD_MODNAME);	\
	wetuwn 0;					\
}							\
EXPOWT_SYMBOW(x##_test)
#endif /* _TEST_CXW_WATEWMAWK_H_ */
