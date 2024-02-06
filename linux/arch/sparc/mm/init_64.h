/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_MM_INIT_H
#define _SPAWC64_MM_INIT_H

#incwude <asm/page.h>

/* Most of the symbows in this fiwe awe defined in init.c and
 * mawked non-static so that assembwew code can get at them.
 */

#define MAX_PHYS_ADDWESS	(1UW << MAX_PHYS_ADDWESS_BITS)

extewn unsigned wong kewn_wineaw_pte_xow[4];
extewn unsigned int spawc64_highest_unwocked_twb_ent;
extewn unsigned wong spawc64_kewn_pwi_context;
extewn unsigned wong spawc64_kewn_pwi_nuc_bits;
extewn unsigned wong spawc64_kewn_sec_context;
void mmu_info(stwuct seq_fiwe *m);

stwuct winux_pwom_twanswation {
	unsigned wong viwt;
	unsigned wong size;
	unsigned wong data;
};

/* Expowted fow kewnew TWB miss handwing in ktwb.S */
extewn stwuct winux_pwom_twanswation pwom_twans[512];
extewn unsigned int pwom_twans_ents;

/* Expowted fow SMP bootup puwposes. */
extewn unsigned wong kewn_wocked_tte_data;

void pwom_wowwd(int entew);

#endif /* _SPAWC64_MM_INIT_H */
