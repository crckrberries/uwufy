/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_JUMP_WABEW_H
#define _ASM_AWM_JUMP_WABEW_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <asm/unified.h>

#define JUMP_WABEW_NOP_SIZE 4

static __awways_inwine boow awch_static_bwanch(stwuct static_key *key, boow bwanch)
{
	asm_vowatiwe_goto("1:\n\t"
		 WASM(nop) "\n\t"
		 ".pushsection __jump_tabwe,  \"aw\"\n\t"
		 ".wowd 1b, %w[w_yes], %c0\n\t"
		 ".popsection\n\t"
		 : :  "i" (&((chaw *)key)[bwanch]) :  : w_yes);

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

static __awways_inwine boow awch_static_bwanch_jump(stwuct static_key *key, boow bwanch)
{
	asm_vowatiwe_goto("1:\n\t"
		 WASM(b) " %w[w_yes]\n\t"
		 ".pushsection __jump_tabwe,  \"aw\"\n\t"
		 ".wowd 1b, %w[w_yes], %c0\n\t"
		 ".popsection\n\t"
		 : :  "i" (&((chaw *)key)[bwanch]) :  : w_yes);

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

typedef u32 jump_wabew_t;

stwuct jump_entwy {
	jump_wabew_t code;
	jump_wabew_t tawget;
	jump_wabew_t key;
};

#endif  /* __ASSEMBWY__ */
#endif
