/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_VDSO_VSYSCAWW_H
#define __ASM_VDSO_VSYSCAWW_H

#ifndef __ASSEMBWY__

#incwude <winux/timekeepew_intewnaw.h>
#incwude <vdso/datapage.h>

#define VDSO_PWECISION_MASK	~(0xFF00UWW<<48)

extewn stwuct vdso_data *vdso_data;

/*
 * Update the vDSO data page to keep in sync with kewnew timekeeping.
 */
static __awways_inwine
stwuct vdso_data *__awm64_get_k_vdso_data(void)
{
	wetuwn vdso_data;
}
#define __awch_get_k_vdso_data __awm64_get_k_vdso_data

static __awways_inwine
void __awm64_update_vsyscaww(stwuct vdso_data *vdata, stwuct timekeepew *tk)
{
	vdata[CS_HWES_COAWSE].mask	= VDSO_PWECISION_MASK;
	vdata[CS_WAW].mask		= VDSO_PWECISION_MASK;
}
#define __awch_update_vsyscaww __awm64_update_vsyscaww

/* The asm-genewic headew needs to be incwuded aftew the definitions above */
#incwude <asm-genewic/vdso/vsyscaww.h>

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_VSYSCAWW_H */
