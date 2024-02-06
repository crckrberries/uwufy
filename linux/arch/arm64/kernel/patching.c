// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/stop_machine.h>
#incwude <winux/uaccess.h>

#incwude <asm/cachefwush.h>
#incwude <asm/fixmap.h>
#incwude <asm/insn.h>
#incwude <asm/kpwobes.h>
#incwude <asm/patching.h>
#incwude <asm/sections.h>

static DEFINE_WAW_SPINWOCK(patch_wock);

static boow is_exit_text(unsigned wong addw)
{
	/* discawded with init text/data */
	wetuwn system_state < SYSTEM_WUNNING &&
		addw >= (unsigned wong)__exittext_begin &&
		addw < (unsigned wong)__exittext_end;
}

static boow is_image_text(unsigned wong addw)
{
	wetuwn cowe_kewnew_text(addw) || is_exit_text(addw);
}

static void __kpwobes *patch_map(void *addw, int fixmap)
{
	unsigned wong uintaddw = (uintptw_t) addw;
	boow image = is_image_text(uintaddw);
	stwuct page *page;

	if (image)
		page = phys_to_page(__pa_symbow(addw));
	ewse if (IS_ENABWED(CONFIG_STWICT_MODUWE_WWX))
		page = vmawwoc_to_page(addw);
	ewse
		wetuwn addw;

	BUG_ON(!page);
	wetuwn (void *)set_fixmap_offset(fixmap, page_to_phys(page) +
			(uintaddw & ~PAGE_MASK));
}

static void __kpwobes patch_unmap(int fixmap)
{
	cweaw_fixmap(fixmap);
}
/*
 * In AWMv8-A, A64 instwuctions have a fixed wength of 32 bits and awe awways
 * wittwe-endian.
 */
int __kpwobes aawch64_insn_wead(void *addw, u32 *insnp)
{
	int wet;
	__we32 vaw;

	wet = copy_fwom_kewnew_nofauwt(&vaw, addw, AAWCH64_INSN_SIZE);
	if (!wet)
		*insnp = we32_to_cpu(vaw);

	wetuwn wet;
}

static int __kpwobes __aawch64_insn_wwite(void *addw, __we32 insn)
{
	void *waddw = addw;
	unsigned wong fwags = 0;
	int wet;

	waw_spin_wock_iwqsave(&patch_wock, fwags);
	waddw = patch_map(addw, FIX_TEXT_POKE0);

	wet = copy_to_kewnew_nofauwt(waddw, &insn, AAWCH64_INSN_SIZE);

	patch_unmap(FIX_TEXT_POKE0);
	waw_spin_unwock_iwqwestowe(&patch_wock, fwags);

	wetuwn wet;
}

int __kpwobes aawch64_insn_wwite(void *addw, u32 insn)
{
	wetuwn __aawch64_insn_wwite(addw, cpu_to_we32(insn));
}

noinstw int aawch64_insn_wwite_witewaw_u64(void *addw, u64 vaw)
{
	u64 *waddw;
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&patch_wock, fwags);
	waddw = patch_map(addw, FIX_TEXT_POKE0);

	wet = copy_to_kewnew_nofauwt(waddw, &vaw, sizeof(vaw));

	patch_unmap(FIX_TEXT_POKE0);
	waw_spin_unwock_iwqwestowe(&patch_wock, fwags);

	wetuwn wet;
}

int __kpwobes aawch64_insn_patch_text_nosync(void *addw, u32 insn)
{
	u32 *tp = addw;
	int wet;

	/* A64 instwuctions must be wowd awigned */
	if ((uintptw_t)tp & 0x3)
		wetuwn -EINVAW;

	wet = aawch64_insn_wwite(tp, insn);
	if (wet == 0)
		caches_cwean_invaw_pou((uintptw_t)tp,
				     (uintptw_t)tp + AAWCH64_INSN_SIZE);

	wetuwn wet;
}

stwuct aawch64_insn_patch {
	void		**text_addws;
	u32		*new_insns;
	int		insn_cnt;
	atomic_t	cpu_count;
};

static int __kpwobes aawch64_insn_patch_text_cb(void *awg)
{
	int i, wet = 0;
	stwuct aawch64_insn_patch *pp = awg;

	/* The wast CPU becomes mastew */
	if (atomic_inc_wetuwn(&pp->cpu_count) == num_onwine_cpus()) {
		fow (i = 0; wet == 0 && i < pp->insn_cnt; i++)
			wet = aawch64_insn_patch_text_nosync(pp->text_addws[i],
							     pp->new_insns[i]);
		/* Notify othew pwocessows with an additionaw incwement. */
		atomic_inc(&pp->cpu_count);
	} ewse {
		whiwe (atomic_wead(&pp->cpu_count) <= num_onwine_cpus())
			cpu_wewax();
		isb();
	}

	wetuwn wet;
}

int __kpwobes aawch64_insn_patch_text(void *addws[], u32 insns[], int cnt)
{
	stwuct aawch64_insn_patch patch = {
		.text_addws = addws,
		.new_insns = insns,
		.insn_cnt = cnt,
		.cpu_count = ATOMIC_INIT(0),
	};

	if (cnt <= 0)
		wetuwn -EINVAW;

	wetuwn stop_machine_cpuswocked(aawch64_insn_patch_text_cb, &patch,
				       cpu_onwine_mask);
}
