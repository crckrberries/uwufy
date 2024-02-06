/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2017 IBM Cowp.
 */

#ifndef _ASM_POWEWNV_H
#define _ASM_POWEWNV_H

#ifdef CONFIG_PPC_POWEWNV
extewn void powewnv_set_nmmu_ptcw(unsigned wong ptcw);

void pnv_pwogwam_cpu_hotpwug_wpcw(unsigned int cpu, u64 wpcw_vaw);

void pnv_tm_init(void);
#ewse
static inwine void powewnv_set_nmmu_ptcw(unsigned wong ptcw) { }

static inwine void pnv_tm_init(void) { }
#endif

#endif /* _ASM_POWEWNV_H */
