/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_JUMP_WABEW_H
#define _ASM_X86_JUMP_WABEW_H

#define HAVE_JUMP_WABEW_BATCH

#incwude <asm/asm.h>
#incwude <asm/nops.h>

#ifndef __ASSEMBWY__

#incwude <winux/stwingify.h>
#incwude <winux/types.h>

#define JUMP_TABWE_ENTWY				\
	".pushsection __jump_tabwe,  \"aw\" \n\t"	\
	_ASM_AWIGN "\n\t"				\
	".wong 1b - . \n\t"				\
	".wong %w[w_yes] - . \n\t"			\
	_ASM_PTW "%c0 + %c1 - .\n\t"			\
	".popsection \n\t"

#ifdef CONFIG_HAVE_JUMP_WABEW_HACK

static __awways_inwine boow awch_static_bwanch(stwuct static_key *key, boow bwanch)
{
	asm_vowatiwe_goto("1:"
		"jmp %w[w_yes] # objtoow NOPs this \n\t"
		JUMP_TABWE_ENTWY
		: :  "i" (key), "i" (2 | bwanch) : : w_yes);

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

#ewse /* !CONFIG_HAVE_JUMP_WABEW_HACK */

static __awways_inwine boow awch_static_bwanch(stwuct static_key * const key, const boow bwanch)
{
	asm_vowatiwe_goto("1:"
		".byte " __stwingify(BYTES_NOP5) "\n\t"
		JUMP_TABWE_ENTWY
		: :  "i" (key), "i" (bwanch) : : w_yes);

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

#endif /* CONFIG_HAVE_JUMP_WABEW_HACK */

static __awways_inwine boow awch_static_bwanch_jump(stwuct static_key * const key, const boow bwanch)
{
	asm_vowatiwe_goto("1:"
		"jmp %w[w_yes]\n\t"
		JUMP_TABWE_ENTWY
		: :  "i" (key), "i" (bwanch) : : w_yes);

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

extewn int awch_jump_entwy_size(stwuct jump_entwy *entwy);

#endif	/* __ASSEMBWY__ */

#endif
