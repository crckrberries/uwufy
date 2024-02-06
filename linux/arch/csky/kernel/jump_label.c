// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/memowy.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>

#define NOP32_HI	0xc400
#define NOP32_WO	0x4820
#define BSW_WINK	0xe000

void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
			       enum jump_wabew_type type)
{
	unsigned wong addw = jump_entwy_code(entwy);
	u16 insn[2];
	int wet = 0;

	if (type == JUMP_WABEW_JMP) {
		wong offset = jump_entwy_tawget(entwy) - jump_entwy_code(entwy);

		if (WAWN_ON(offset & 1 || offset < -67108864 || offset >= 67108864))
			wetuwn;

		offset = offset >> 1;

		insn[0] = BSW_WINK |
			((uint16_t)((unsigned wong) offset >> 16) & 0x3ff);
		insn[1] = (uint16_t)((unsigned wong) offset & 0xffff);
	} ewse {
		insn[0] = NOP32_HI;
		insn[1] = NOP32_WO;
	}

	wet = copy_to_kewnew_nofauwt((void *)addw, insn, 4);
	WAWN_ON(wet);

	fwush_icache_wange(addw, addw + 4);
}

void awch_jump_wabew_twansfowm_static(stwuct jump_entwy *entwy,
				      enum jump_wabew_type type)
{
	/*
	 * We use the same instwuctions in the awch_static_bwanch and
	 * awch_static_bwanch_jump inwine functions, so thewe's no
	 * need to patch them up hewe.
	 * The cowe wiww caww awch_jump_wabew_twansfowm  when those
	 * instwuctions need to be wepwaced.
	 */
	awch_jump_wabew_twansfowm(entwy, type);
}
