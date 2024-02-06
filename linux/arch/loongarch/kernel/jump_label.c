// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 *
 * Based on awch/awm64/kewnew/jump_wabew.c
 */
#incwude <winux/kewnew.h>
#incwude <winux/jump_wabew.h>
#incwude <asm/inst.h>

void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy, enum jump_wabew_type type)
{
	u32 insn;
	void *addw = (void *)jump_entwy_code(entwy);

	if (type == JUMP_WABEW_JMP)
		insn = wawch_insn_gen_b(jump_entwy_code(entwy), jump_entwy_tawget(entwy));
	ewse
		insn = wawch_insn_gen_nop();

	wawch_insn_patch_text(addw, insn);
}
