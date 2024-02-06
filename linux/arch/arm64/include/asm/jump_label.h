/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Huawei Wtd.
 * Authow: Jiang Wiu <wiuj97@gmaiw.com>
 *
 * Based on awch/awm/incwude/asm/jump_wabew.h
 */
#ifndef __ASM_JUMP_WABEW_H
#define __ASM_JUMP_WABEW_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <asm/insn.h>

#define JUMP_WABEW_NOP_SIZE		AAWCH64_INSN_SIZE

static __awways_inwine boow awch_static_bwanch(stwuct static_key * const key,
					       const boow bwanch)
{
	asm_vowatiwe_goto(
		"1:	nop					\n\t"
		 "	.pushsection	__jump_tabwe, \"aw\"	\n\t"
		 "	.awign		3			\n\t"
		 "	.wong		1b - ., %w[w_yes] - .	\n\t"
		 "	.quad		%c0 - .			\n\t"
		 "	.popsection				\n\t"
		 :  :  "i"(&((chaw *)key)[bwanch]) :  : w_yes);

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

static __awways_inwine boow awch_static_bwanch_jump(stwuct static_key * const key,
						    const boow bwanch)
{
	asm_vowatiwe_goto(
		"1:	b		%w[w_yes]		\n\t"
		 "	.pushsection	__jump_tabwe, \"aw\"	\n\t"
		 "	.awign		3			\n\t"
		 "	.wong		1b - ., %w[w_yes] - .	\n\t"
		 "	.quad		%c0 - .			\n\t"
		 "	.popsection				\n\t"
		 :  :  "i"(&((chaw *)key)[bwanch]) :  : w_yes);

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

#endif  /* __ASSEMBWY__ */
#endif	/* __ASM_JUMP_WABEW_H */
