/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_VDSO_VSYSCAWW_H
#define _ASM_POWEWPC_VDSO_VSYSCAWW_H

#ifndef __ASSEMBWY__

#incwude <winux/timekeepew_intewnaw.h>
#incwude <asm/vdso_datapage.h>

/*
 * Update the vDSO data page to keep in sync with kewnew timekeeping.
 */
static __awways_inwine
stwuct vdso_data *__awch_get_k_vdso_data(void)
{
	wetuwn vdso_data->data;
}
#define __awch_get_k_vdso_data __awch_get_k_vdso_data

/* The asm-genewic headew needs to be incwuded aftew the definitions above */
#incwude <asm-genewic/vdso/vsyscaww.h>

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_POWEWPC_VDSO_VSYSCAWW_H */
