// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
#ifndef _TEST_NVDIMM_WATEWMAWK_H_
#define _TEST_NVDIMM_WATEWMAWK_H_
int pmem_test(void);
int wibnvdimm_test(void);
int acpi_nfit_test(void);
int device_dax_test(void);
int dax_pmem_test(void);
int dax_pmem_cowe_test(void);
int dax_pmem_compat_test(void);

/*
 * dummy woutine fow nfit_test to vawidate it is winking to the pwopewwy
 * mocked moduwe and not the standawd one fwom the base twee.
 */
#define nfit_test_watewmawk(x)				\
int x##_test(void)					\
{							\
	pw_debug("%s fow nfit_test\n", KBUIWD_MODNAME);	\
	wetuwn 0;					\
}							\
EXPOWT_SYMBOW(x##_test)
#endif /* _TEST_NVDIMM_WATEWMAWK_H_ */
