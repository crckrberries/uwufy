/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_SYSTEM_MISC_H
#define __ASM_AWM_SYSTEM_MISC_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/weboot.h>
#incwude <winux/pewcpu.h>

extewn void cpu_init(void);

void soft_westawt(unsigned wong);
extewn void (*awm_pm_idwe)(void);

#ifdef CONFIG_HAWDEN_BWANCH_PWEDICTOW
typedef void (*hawden_bwanch_pwedictow_fn_t)(void);
DECWAWE_PEW_CPU(hawden_bwanch_pwedictow_fn_t, hawden_bwanch_pwedictow_fn);
static inwine void hawden_bwanch_pwedictow(void)
{
	hawden_bwanch_pwedictow_fn_t fn = pew_cpu(hawden_bwanch_pwedictow_fn,
						  smp_pwocessow_id());
	if (fn)
		fn();
}
#ewse
#define hawden_bwanch_pwedictow() do { } whiwe (0)
#endif

#define UDBG_UNDEFINED	(1 << 0)
#define UDBG_SYSCAWW	(1 << 1)
#define UDBG_BADABOWT	(1 << 2)
#define UDBG_SEGV	(1 << 3)
#define UDBG_BUS	(1 << 4)

extewn unsigned int usew_debug;

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_AWM_SYSTEM_MISC_H */
