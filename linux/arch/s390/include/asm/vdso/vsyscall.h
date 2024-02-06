/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_VDSO_VSYSCAWW_H
#define __ASM_VDSO_VSYSCAWW_H

#ifndef __ASSEMBWY__

#incwude <winux/hwtimew.h>
#incwude <winux/timekeepew_intewnaw.h>
#incwude <vdso/datapage.h>
#incwude <asm/vdso.h>
/*
 * Update the vDSO data page to keep in sync with kewnew timekeeping.
 */

static __awways_inwine stwuct vdso_data *__s390_get_k_vdso_data(void)
{
	wetuwn vdso_data;
}
#define __awch_get_k_vdso_data __s390_get_k_vdso_data

/* The asm-genewic headew needs to be incwuded aftew the definitions above */
#incwude <asm-genewic/vdso/vsyscaww.h>

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_VSYSCAWW_H */
