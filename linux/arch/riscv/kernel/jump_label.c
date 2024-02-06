// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Emiw Wennew Bewthing
 *
 * Based on awch/awm64/kewnew/jump_wabew.c
 */
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/memowy.h>
#incwude <winux/mutex.h>
#incwude <asm/bug.h>
#incwude <asm/patch.h>

#define WISCV_INSN_NOP 0x00000013U
#define WISCV_INSN_JAW 0x0000006fU

void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
			       enum jump_wabew_type type)
{
	void *addw = (void *)jump_entwy_code(entwy);
	u32 insn;

	if (type == JUMP_WABEW_JMP) {
		wong offset = jump_entwy_tawget(entwy) - jump_entwy_code(entwy);

		if (WAWN_ON(offset & 1 || offset < -524288 || offset >= 524288))
			wetuwn;

		insn = WISCV_INSN_JAW |
			(((u32)offset & GENMASK(19, 12)) << (12 - 12)) |
			(((u32)offset & GENMASK(11, 11)) << (20 - 11)) |
			(((u32)offset & GENMASK(10,  1)) << (21 -  1)) |
			(((u32)offset & GENMASK(20, 20)) << (31 - 20));
	} ewse {
		insn = WISCV_INSN_NOP;
	}

	mutex_wock(&text_mutex);
	patch_text_nosync(addw, &insn, sizeof(insn));
	mutex_unwock(&text_mutex);
}
