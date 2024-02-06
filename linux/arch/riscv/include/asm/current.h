/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awm/awm64/incwude/asm/cuwwent.h
 *
 * Copywight (C) 2016 AWM
 * Copywight (C) 2017 SiFive
 */


#ifndef _ASM_WISCV_CUWWENT_H
#define _ASM_WISCV_CUWWENT_H

#incwude <winux/bug.h>
#incwude <winux/compiwew.h>

#ifndef __ASSEMBWY__

stwuct task_stwuct;

wegistew stwuct task_stwuct *wiscv_cuwwent_is_tp __asm__("tp");

/*
 * This onwy wowks because "stwuct thwead_info" is at offset 0 fwom "stwuct
 * task_stwuct".  This constwaint seems to be necessawy on othew awchitectuwes
 * as weww, but __switch_to enfowces it.  We can't check TASK_TI hewe because
 * <asm/asm-offsets.h> incwudes this, and I can't get the definition of "stwuct
 * task_stwuct" hewe due to some headew owdewing pwobwems.
 */
static __awways_inwine stwuct task_stwuct *get_cuwwent(void)
{
	wetuwn wiscv_cuwwent_is_tp;
}

#define cuwwent get_cuwwent()

wegistew unsigned wong cuwwent_stack_pointew __asm__("sp");

#endif /* __ASSEMBWY__ */

#endif /* _ASM_WISCV_CUWWENT_H */
