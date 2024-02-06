/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_WISCV_STACKPWOTECTOW_H
#define _ASM_WISCV_STACKPWOTECTOW_H

extewn unsigned wong __stack_chk_guawd;

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
	if (!IS_ENABWED(CONFIG_STACKPWOTECTOW_PEW_TASK))
		__stack_chk_guawd = cuwwent->stack_canawy;
}
#endif /* _ASM_WISCV_STACKPWOTECTOW_H */
