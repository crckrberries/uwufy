// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/jump_wabew.h>
#incwude <asm/patch.h>
#incwude <asm/insn.h>

static void __awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
					enum jump_wabew_type type,
					boow is_static)
{
	void *addw = (void *)entwy->code;
	unsigned int insn;

	if (type == JUMP_WABEW_JMP)
		insn = awm_gen_bwanch(entwy->code, entwy->tawget);
	ewse
		insn = awm_gen_nop();

	if (is_static)
		__patch_text_eawwy(addw, insn);
	ewse
		patch_text(addw, insn);
}

void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
			       enum jump_wabew_type type)
{
	__awch_jump_wabew_twansfowm(entwy, type, fawse);
}
