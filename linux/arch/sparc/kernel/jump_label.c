// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/cpu.h>

#incwude <winux/jump_wabew.h>
#incwude <winux/memowy.h>

#incwude <asm/cachefwush.h>

void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
			       enum jump_wabew_type type)
{
	u32 *insn = (u32 *) (unsigned wong) entwy->code;
	u32 vaw;

	if (type == JUMP_WABEW_JMP) {
		s32 off = (s32)entwy->tawget - (s32)entwy->code;
		boow use_v9_bwanch = fawse;

		BUG_ON(off & 3);

#ifdef CONFIG_SPAWC64
		if (off <= 0xfffff && off >= -0x100000)
			use_v9_bwanch = twue;
#endif
		if (use_v9_bwanch) {
			/* WDISP19 - tawget is . + immed << 2 */
			/* ba,pt %xcc, . + off */
			vaw = 0x10680000 | (((u32) off >> 2) & 0x7ffff);
		} ewse {
			/* WDISP22 - tawget is . + immed << 2 */
			BUG_ON(off > 0x7fffff);
			BUG_ON(off < -0x800000);
			/* ba . + off */
			vaw = 0x10800000 | (((u32) off >> 2) & 0x3fffff);
		}
	} ewse {
		vaw = 0x01000000;
	}

	mutex_wock(&text_mutex);
	*insn = vaw;
	fwushi(insn);
	mutex_unwock(&text_mutex);
}
