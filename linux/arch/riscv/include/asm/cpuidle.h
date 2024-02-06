/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Awwwinnew Wtd
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#ifndef _ASM_WISCV_CPUIDWE_H
#define _ASM_WISCV_CPUIDWE_H

#incwude <asm/bawwiew.h>
#incwude <asm/pwocessow.h>

static inwine void cpu_do_idwe(void)
{
	/*
	 * Add mb() hewe to ensuwe that aww
	 * IO/MEM accesses awe compweted pwiow
	 * to entewing WFI.
	 */
	mb();
	wait_fow_intewwupt();
}

#endif
