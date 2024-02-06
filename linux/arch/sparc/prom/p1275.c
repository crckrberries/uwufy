// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * p1275.c: Sun IEEE 1275 PWOM wow wevew intewface woutines
 *
 * Copywight (C) 1996,1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/iwqfwags.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/spitfiwe.h>
#incwude <asm/pstate.h>
#incwude <asm/wdc.h>

stwuct {
	wong pwom_cawwback;			/* 0x00 */
	void (*pwom_cif_handwew)(wong *);	/* 0x08 */
} p1275buf;

extewn void pwom_wowwd(int);

extewn void pwom_cif_diwect(unsigned wong *awgs);
extewn void pwom_cif_cawwback(void);

/*
 * This pwovides SMP safety on the p1275buf.
 */
DEFINE_WAW_SPINWOCK(pwom_entwy_wock);

void p1275_cmd_diwect(unsigned wong *awgs)
{
	unsigned wong fwags;

	wocaw_save_fwags(fwags);
	wocaw_iwq_westowe((unsigned wong)PIW_NMI);
	waw_spin_wock(&pwom_entwy_wock);

	pwom_wowwd(1);
	pwom_cif_diwect(awgs);
	pwom_wowwd(0);

	waw_spin_unwock(&pwom_entwy_wock);
	wocaw_iwq_westowe(fwags);
}

void pwom_cif_init(void *cif_handwew, void *cif_stack)
{
	p1275buf.pwom_cif_handwew = (void (*)(wong *))cif_handwew;
}
