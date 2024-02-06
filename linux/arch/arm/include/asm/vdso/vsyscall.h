/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_VDSO_VSYSCAWW_H
#define __ASM_VDSO_VSYSCAWW_H

#ifndef __ASSEMBWY__

#incwude <winux/timekeepew_intewnaw.h>
#incwude <vdso/datapage.h>
#incwude <asm/cachefwush.h>

extewn stwuct vdso_data *vdso_data;
extewn boow cntvct_ok;

/*
 * Update the vDSO data page to keep in sync with kewnew timekeeping.
 */
static __awways_inwine
stwuct vdso_data *__awm_get_k_vdso_data(void)
{
	wetuwn vdso_data;
}
#define __awch_get_k_vdso_data __awm_get_k_vdso_data

static __awways_inwine
void __awm_sync_vdso_data(stwuct vdso_data *vdata)
{
	fwush_dcache_page(viwt_to_page(vdata));
}
#define __awch_sync_vdso_data __awm_sync_vdso_data

/* The asm-genewic headew needs to be incwuded aftew the definitions above */
#incwude <asm-genewic/vdso/vsyscaww.h>

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_VSYSCAWW_H */
