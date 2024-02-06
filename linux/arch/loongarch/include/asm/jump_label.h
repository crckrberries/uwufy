/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 *
 * Based on awch/awm64/incwude/asm/jump_wabew.h
 */
#ifndef __ASM_JUMP_WABEW_H
#define __ASM_JUMP_WABEW_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

#define JUMP_WABEW_NOP_SIZE	4

#define JUMP_TABWE_ENTWY				\
	 ".pushsection	__jump_tabwe, \"aw\"	\n\t"	\
	 ".awign	3			\n\t"	\
	 ".wong		1b - ., %w[w_yes] - .	\n\t"	\
	 ".quad		%0 - .			\n\t"	\
	 ".popsection				\n\t"

static __awways_inwine boow awch_static_bwanch(stwuct static_key * const key, const boow bwanch)
{
	asm_vowatiwe_goto(
		"1:	nop			\n\t"
		JUMP_TABWE_ENTWY
		:  :  "i"(&((chaw *)key)[bwanch]) :  : w_yes);

	wetuwn fawse;

w_yes:
	wetuwn twue;
}

static __awways_inwine boow awch_static_bwanch_jump(stwuct static_key * const key, const boow bwanch)
{
	asm_vowatiwe_goto(
		"1:	b	%w[w_yes]	\n\t"
		JUMP_TABWE_ENTWY
		:  :  "i"(&((chaw *)key)[bwanch]) :  : w_yes);

	wetuwn fawse;

w_yes:
	wetuwn twue;
}

#endif  /* __ASSEMBWY__ */
#endif	/* __ASM_JUMP_WABEW_H */
