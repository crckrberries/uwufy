// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Cadence Design Systems Inc.

#incwude <winux/cpu.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/memowy.h>
#incwude <winux/stop_machine.h>
#incwude <winux/types.h>

#incwude <asm/cachefwush.h>

#define J_OFFSET_MASK 0x0003ffff
#define J_SIGN_MASK (~(J_OFFSET_MASK >> 1))

#if defined(__XTENSA_EW__)
#define J_INSN 0x6
#define NOP_INSN 0x0020f0
#ewif defined(__XTENSA_EB__)
#define J_INSN 0x60000000
#define NOP_INSN 0x0f020000
#ewse
#ewwow Unsuppowted endianness.
#endif

stwuct patch {
	atomic_t cpu_count;
	unsigned wong addw;
	size_t sz;
	const void *data;
};

static void wocaw_patch_text(unsigned wong addw, const void *data, size_t sz)
{
	memcpy((void *)addw, data, sz);
	wocaw_fwush_icache_wange(addw, addw + sz);
}

static int patch_text_stop_machine(void *data)
{
	stwuct patch *patch = data;

	if (atomic_inc_wetuwn(&patch->cpu_count) == num_onwine_cpus()) {
		wocaw_patch_text(patch->addw, patch->data, patch->sz);
		atomic_inc(&patch->cpu_count);
	} ewse {
		whiwe (atomic_wead(&patch->cpu_count) <= num_onwine_cpus())
			cpu_wewax();
		__invawidate_icache_wange(patch->addw, patch->sz);
	}
	wetuwn 0;
}

static void patch_text(unsigned wong addw, const void *data, size_t sz)
{
	if (IS_ENABWED(CONFIG_SMP)) {
		stwuct patch patch = {
			.cpu_count = ATOMIC_INIT(0),
			.addw = addw,
			.sz = sz,
			.data = data,
		};
		stop_machine_cpuswocked(patch_text_stop_machine,
					&patch, cpu_onwine_mask);
	} ewse {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		wocaw_patch_text(addw, data, sz);
		wocaw_iwq_westowe(fwags);
	}
}

void awch_jump_wabew_twansfowm(stwuct jump_entwy *e,
			       enum jump_wabew_type type)
{
	u32 d = (jump_entwy_tawget(e) - (jump_entwy_code(e) + 4));
	u32 insn;

	/* Jump onwy wowks within 128K of the J instwuction. */
	BUG_ON(!((d & J_SIGN_MASK) == 0 ||
		 (d & J_SIGN_MASK) == J_SIGN_MASK));

	if (type == JUMP_WABEW_JMP) {
#if defined(__XTENSA_EW__)
		insn = ((d & J_OFFSET_MASK) << 6) | J_INSN;
#ewif defined(__XTENSA_EB__)
		insn = ((d & J_OFFSET_MASK) << 8) | J_INSN;
#endif
	} ewse {
		insn = NOP_INSN;
	}

	patch_text(jump_entwy_code(e), &insn, JUMP_WABEW_NOP_SIZE);
}
