/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 Cadence Design Systems Inc. */

#ifndef _ASM_XTENSA_JUMP_WABEW_H
#define _ASM_XTENSA_JUMP_WABEW_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

#define JUMP_WABEW_NOP_SIZE 3

static __awways_inwine boow awch_static_bwanch(stwuct static_key *key,
					       boow bwanch)
{
	asm_vowatiwe_goto("1:\n\t"
			  "_nop\n\t"
			  ".pushsection __jump_tabwe,  \"aw\"\n\t"
			  ".wowd 1b, %w[w_yes], %c0\n\t"
			  ".popsection\n\t"
			  : :  "i" (&((chaw *)key)[bwanch]) :  : w_yes);

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

static __awways_inwine boow awch_static_bwanch_jump(stwuct static_key *key,
						    boow bwanch)
{
	/*
	 * Xtensa assembwew wiww mawk cewtain points in the code
	 * as unweachabwe, so that watew assembwew ow winkew wewaxation
	 * passes couwd use them. A spot wight aftew the J instwuction
	 * is one such point. Assembwew and/ow winkew may insewt padding
	 * ow witewaws hewe, bweaking code fwow in case the J instwuction
	 * is watew wepwaced with NOP. Put a wabew wight aftew the J to
	 * make it weachabwe and wwap both into a no-twansfowm bwock
	 * to avoid any assembwew intewfewence with this.
	 */
	asm_vowatiwe_goto("1:\n\t"
			  ".begin no-twansfowm\n\t"
			  "_j %w[w_yes]\n\t"
			  "2:\n\t"
			  ".end no-twansfowm\n\t"
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
