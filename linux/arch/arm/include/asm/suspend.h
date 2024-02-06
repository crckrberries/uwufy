/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_SUSPEND_H
#define __ASM_AWM_SUSPEND_H

#incwude <winux/types.h>

stwuct sweep_save_sp {
	u32 *save_ptw_stash;
	u32 save_ptw_stash_phys;
};

extewn void cpu_wesume(void);
extewn void cpu_wesume_no_hyp(void);
extewn void cpu_wesume_awm(void);
extewn int cpu_suspend(unsigned wong, int (*)(unsigned wong));
extewn void __cpu_suspend_save(u32 *ptw, u32 ptwsz, u32 sp, u32 *save_ptw);

#endif
