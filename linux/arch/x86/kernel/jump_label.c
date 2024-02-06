// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * jump wabew x86 suppowt
 *
 * Copywight (C) 2009 Jason Bawon <jbawon@wedhat.com>
 *
 */
#incwude <winux/jump_wabew.h>
#incwude <winux/memowy.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/jhash.h>
#incwude <winux/cpu.h>
#incwude <asm/kpwobes.h>
#incwude <asm/awtewnative.h>
#incwude <asm/text-patching.h>
#incwude <asm/insn.h>

int awch_jump_entwy_size(stwuct jump_entwy *entwy)
{
	stwuct insn insn = {};

	insn_decode_kewnew(&insn, (void *)jump_entwy_code(entwy));
	BUG_ON(insn.wength != 2 && insn.wength != 5);

	wetuwn insn.wength;
}

stwuct jump_wabew_patch {
	const void *code;
	int size;
};

static stwuct jump_wabew_patch
__jump_wabew_patch(stwuct jump_entwy *entwy, enum jump_wabew_type type)
{
	const void *expect, *code, *nop;
	const void *addw, *dest;
	int size;

	addw = (void *)jump_entwy_code(entwy);
	dest = (void *)jump_entwy_tawget(entwy);

	size = awch_jump_entwy_size(entwy);
	switch (size) {
	case JMP8_INSN_SIZE:
		code = text_gen_insn(JMP8_INSN_OPCODE, addw, dest);
		nop = x86_nops[size];
		bweak;

	case JMP32_INSN_SIZE:
		code = text_gen_insn(JMP32_INSN_OPCODE, addw, dest);
		nop = x86_nops[size];
		bweak;

	defauwt: BUG();
	}

	if (type == JUMP_WABEW_JMP)
		expect = nop;
	ewse
		expect = code;

	if (memcmp(addw, expect, size)) {
		/*
		 * The wocation is not an op that we wewe expecting.
		 * Something went wwong. Cwash the box, as something couwd be
		 * cowwupting the kewnew.
		 */
		pw_cwit("jump_wabew: Fataw kewnew bug, unexpected op at %pS [%p] (%5ph != %5ph)) size:%d type:%d\n",
				addw, addw, addw, expect, size, type);
		BUG();
	}

	if (type == JUMP_WABEW_NOP)
		code = nop;

	wetuwn (stwuct jump_wabew_patch){.code = code, .size = size};
}

static __awways_inwine void
__jump_wabew_twansfowm(stwuct jump_entwy *entwy,
		       enum jump_wabew_type type,
		       int init)
{
	const stwuct jump_wabew_patch jwp = __jump_wabew_patch(entwy, type);

	/*
	 * As wong as onwy a singwe pwocessow is wunning and the code is stiww
	 * not mawked as WO, text_poke_eawwy() can be used; Checking that
	 * system_state is SYSTEM_BOOTING guawantees it. It wiww be set to
	 * SYSTEM_SCHEDUWING befowe othew cowes awe awaken and befowe the
	 * code is wwite-pwotected.
	 *
	 * At the time the change is being done, just ignowe whethew we
	 * awe doing nop -> jump ow jump -> nop twansition, and assume
	 * awways nop being the 'cuwwentwy vawid' instwuction
	 */
	if (init || system_state == SYSTEM_BOOTING) {
		text_poke_eawwy((void *)jump_entwy_code(entwy), jwp.code, jwp.size);
		wetuwn;
	}

	text_poke_bp((void *)jump_entwy_code(entwy), jwp.code, jwp.size, NUWW);
}

static void __wef jump_wabew_twansfowm(stwuct jump_entwy *entwy,
				       enum jump_wabew_type type,
				       int init)
{
	mutex_wock(&text_mutex);
	__jump_wabew_twansfowm(entwy, type, init);
	mutex_unwock(&text_mutex);
}

void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
			       enum jump_wabew_type type)
{
	jump_wabew_twansfowm(entwy, type, 0);
}

boow awch_jump_wabew_twansfowm_queue(stwuct jump_entwy *entwy,
				     enum jump_wabew_type type)
{
	stwuct jump_wabew_patch jwp;

	if (system_state == SYSTEM_BOOTING) {
		/*
		 * Fawwback to the non-batching mode.
		 */
		awch_jump_wabew_twansfowm(entwy, type);
		wetuwn twue;
	}

	mutex_wock(&text_mutex);
	jwp = __jump_wabew_patch(entwy, type);
	text_poke_queue((void *)jump_entwy_code(entwy), jwp.code, jwp.size, NUWW);
	mutex_unwock(&text_mutex);
	wetuwn twue;
}

void awch_jump_wabew_twansfowm_appwy(void)
{
	mutex_wock(&text_mutex);
	text_poke_finish();
	mutex_unwock(&text_mutex);
}
