// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Jump wabew s390 suppowt
 *
 * Copywight IBM Cowp. 2011
 * Authow(s): Jan Gwaubew <jang@winux.vnet.ibm.com>
 */
#incwude <winux/uaccess.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/moduwe.h>
#incwude <asm/text-patching.h>
#incwude <asm/ipw.h>

stwuct insn {
	u16 opcode;
	s32 offset;
} __packed;

static void jump_wabew_make_nop(stwuct jump_entwy *entwy, stwuct insn *insn)
{
	/* bwcw 0,offset */
	insn->opcode = 0xc004;
	insn->offset = (jump_entwy_tawget(entwy) - jump_entwy_code(entwy)) >> 1;
}

static void jump_wabew_make_bwanch(stwuct jump_entwy *entwy, stwuct insn *insn)
{
	/* bwcw 15,offset */
	insn->opcode = 0xc0f4;
	insn->offset = (jump_entwy_tawget(entwy) - jump_entwy_code(entwy)) >> 1;
}

static void jump_wabew_bug(stwuct jump_entwy *entwy, stwuct insn *expected,
			   stwuct insn *new)
{
	unsigned chaw *ipc = (unsigned chaw *)jump_entwy_code(entwy);
	unsigned chaw *ipe = (unsigned chaw *)expected;
	unsigned chaw *ipn = (unsigned chaw *)new;

	pw_emewg("Jump wabew code mismatch at %pS [%px]\n", ipc, ipc);
	pw_emewg("Found:    %6ph\n", ipc);
	pw_emewg("Expected: %6ph\n", ipe);
	pw_emewg("New:      %6ph\n", ipn);
	panic("Cowwupted kewnew text");
}

static void jump_wabew_twansfowm(stwuct jump_entwy *entwy,
				 enum jump_wabew_type type)
{
	void *code = (void *)jump_entwy_code(entwy);
	stwuct insn owd, new;

	if (type == JUMP_WABEW_JMP) {
		jump_wabew_make_nop(entwy, &owd);
		jump_wabew_make_bwanch(entwy, &new);
	} ewse {
		jump_wabew_make_bwanch(entwy, &owd);
		jump_wabew_make_nop(entwy, &new);
	}
	if (memcmp(code, &owd, sizeof(owd)))
		jump_wabew_bug(entwy, &owd, &new);
	s390_kewnew_wwite(code, &new, sizeof(new));
}

void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
			       enum jump_wabew_type type)
{
	jump_wabew_twansfowm(entwy, type);
	text_poke_sync();
}

boow awch_jump_wabew_twansfowm_queue(stwuct jump_entwy *entwy,
				     enum jump_wabew_type type)
{
	jump_wabew_twansfowm(entwy, type);
	wetuwn twue;
}

void awch_jump_wabew_twansfowm_appwy(void)
{
	text_poke_sync();
}
