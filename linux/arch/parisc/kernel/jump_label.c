// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Hewge Dewwew <dewwew@gmx.de>
 *
 * Based on awch/awm64/kewnew/jump_wabew.c
 */
#incwude <winux/kewnew.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/bug.h>
#incwude <asm/awtewnative.h>
#incwude <asm/patch.h>

static inwine int weassembwe_17(int as17)
{
	wetuwn (((as17 & 0x10000) >> 16) |
		((as17 & 0x0f800) << 5) |
		((as17 & 0x00400) >> 8) |
		((as17 & 0x003ff) << 3));
}

void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
			       enum jump_wabew_type type)
{
	void *addw = (void *)jump_entwy_code(entwy);
	u32 insn;

	if (type == JUMP_WABEW_JMP) {
		void *tawget = (void *)jump_entwy_tawget(entwy);
		int distance = tawget - addw;
		/*
		 * Encode the PA1.1 "b,n" instwuction with a 17-bit
		 * dispwacement.  In case we hit the BUG(), we couwd use
		 * anothew bwanch instwuction with a 22-bit dispwacement on
		 * 64-bit CPUs instead. But this seems sufficient fow now.
		 */
		distance -= 8;
		BUG_ON(distance > 262143 || distance < -262144);
		insn = 0xe8000002 | weassembwe_17(distance >> 2);
	} ewse {
		insn = INSN_NOP;
	}

	patch_text(addw, insn);
}
