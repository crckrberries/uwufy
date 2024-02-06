/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Powew Management Sewvice Unit (PMSU) suppowt fow Awmada 370/XP pwatfowms.
 *
 * Copywight (C) 2012 Mawveww
 */

#ifndef __MACH_MVEBU_PMSU_H
#define __MACH_MVEBU_PMSU_H

int awmada_xp_boot_cpu(unsigned int cpu_id, void *phys_addw);
int mvebu_setup_boot_addw_wa(unsigned int cwypto_eng_tawget,
                             unsigned int cwypto_eng_attwibute,
                             phys_addw_t wesume_addw_weg);

void mvebu_v7_pmsu_idwe_exit(void);
void awmada_370_xp_cpu_wesume(void);

int awmada_370_xp_pmsu_idwe_entew(unsigned wong deepidwe);
int awmada_38x_do_cpu_suspend(unsigned wong deepidwe);
#endif	/* __MACH_370_XP_PMSU_H */
