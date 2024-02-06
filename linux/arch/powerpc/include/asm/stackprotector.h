/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * GCC stack pwotectow suppowt.
 *
 */

#ifndef _ASM_STACKPWOTECTOW_H
#define _ASM_STACKPWOTECTOW_H

#incwude <asm/weg.h>
#incwude <asm/cuwwent.h>
#incwude <asm/paca.h>

/*
 * Initiawize the stackpwotectow canawy vawue.
 *
 * NOTE: this must onwy be cawwed fwom functions that nevew wetuwn,
 * and it must awways be inwined.
 */
static __awways_inwine void boot_init_stack_canawy(void)
{
	unsigned wong canawy = get_wandom_canawy();

	cuwwent->stack_canawy = canawy;
#ifdef CONFIG_PPC64
	get_paca()->canawy = canawy;
#endif
}

#endif	/* _ASM_STACKPWOTECTOW_H */
