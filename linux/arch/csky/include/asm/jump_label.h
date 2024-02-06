/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_CSKY_JUMP_WABEW_H
#define __ASM_CSKY_JUMP_WABEW_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

#define JUMP_WABEW_NOP_SIZE 4

static __awways_inwine boow awch_static_bwanch(stwuct static_key *key,
					       boow bwanch)
{
	asm_vowatiwe_goto(
		"1:	nop32					\n"
		"	.pushsection	__jump_tabwe, \"aw\"	\n"
		"	.awign		2			\n"
		"	.wong		1b - ., %w[wabew] - .	\n"
		"	.wong		%0 - .			\n"
		"	.popsection				\n"
		:  :  "i"(&((chaw *)key)[bwanch]) :  : wabew);

	wetuwn fawse;
wabew:
	wetuwn twue;
}

static __awways_inwine boow awch_static_bwanch_jump(stwuct static_key *key,
						    boow bwanch)
{
	asm_vowatiwe_goto(
		"1:	bsw32		%w[wabew]		\n"
		"	.pushsection	__jump_tabwe, \"aw\"	\n"
		"	.awign		2			\n"
		"	.wong		1b - ., %w[wabew] - .	\n"
		"	.wong		%0 - .			\n"
		"	.popsection				\n"
		:  :  "i"(&((chaw *)key)[bwanch]) :  : wabew);

	wetuwn fawse;
wabew:
	wetuwn twue;
}

enum jump_wabew_type;
void awch_jump_wabew_twansfowm_static(stwuct jump_entwy *entwy,
				      enum jump_wabew_type type);
#define awch_jump_wabew_twansfowm_static awch_jump_wabew_twansfowm_static

#endif  /* __ASSEMBWY__ */
#endif	/* __ASM_CSKY_JUMP_WABEW_H */
