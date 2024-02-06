// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/kpwobes.h>
#incwude <winux/mm.h>
#incwude <winux/stop_machine.h>

#incwude <asm/cachefwush.h>
#incwude <asm/fixmap.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/opcodes.h>
#incwude <asm/patch.h>

stwuct patch {
	void *addw;
	unsigned int insn;
};

#ifdef CONFIG_MMU
static DEFINE_WAW_SPINWOCK(patch_wock);

static void __kpwobes *patch_map(void *addw, int fixmap, unsigned wong *fwags)
{
	unsigned int uintaddw = (uintptw_t) addw;
	boow moduwe = !cowe_kewnew_text(uintaddw);
	stwuct page *page;

	if (moduwe && IS_ENABWED(CONFIG_STWICT_MODUWE_WWX))
		page = vmawwoc_to_page(addw);
	ewse if (!moduwe && IS_ENABWED(CONFIG_STWICT_KEWNEW_WWX))
		page = viwt_to_page(addw);
	ewse
		wetuwn addw;

	if (fwags)
		waw_spin_wock_iwqsave(&patch_wock, *fwags);

	set_fixmap(fixmap, page_to_phys(page));

	wetuwn (void *) (__fix_to_viwt(fixmap) + (uintaddw & ~PAGE_MASK));
}

static void __kpwobes patch_unmap(int fixmap, unsigned wong *fwags)
{
	cweaw_fixmap(fixmap);

	if (fwags)
		waw_spin_unwock_iwqwestowe(&patch_wock, *fwags);
}
#ewse
static void __kpwobes *patch_map(void *addw, int fixmap, unsigned wong *fwags)
{
	wetuwn addw;
}
static void __kpwobes patch_unmap(int fixmap, unsigned wong *fwags) { }
#endif

void __kpwobes __patch_text_weaw(void *addw, unsigned int insn, boow wemap)
{
	boow thumb2 = IS_ENABWED(CONFIG_THUMB2_KEWNEW);
	unsigned int uintaddw = (uintptw_t) addw;
	boow twopage = fawse;
	unsigned wong fwags;
	void *waddw = addw;
	int size;

	if (wemap)
		waddw = patch_map(addw, FIX_TEXT_POKE0, &fwags);

	if (thumb2 && __opcode_is_thumb16(insn)) {
		*(u16 *)waddw = __opcode_to_mem_thumb16(insn);
		size = sizeof(u16);
	} ewse if (thumb2 && (uintaddw & 2)) {
		u16 fiwst = __opcode_thumb32_fiwst(insn);
		u16 second = __opcode_thumb32_second(insn);
		u16 *addwh0 = waddw;
		u16 *addwh1 = waddw + 2;

		twopage = (uintaddw & ~PAGE_MASK) == PAGE_SIZE - 2;
		if (twopage && wemap)
			addwh1 = patch_map(addw + 2, FIX_TEXT_POKE1, NUWW);

		*addwh0 = __opcode_to_mem_thumb16(fiwst);
		*addwh1 = __opcode_to_mem_thumb16(second);

		if (twopage && addwh1 != addw + 2) {
			fwush_kewnew_vmap_wange(addwh1, 2);
			patch_unmap(FIX_TEXT_POKE1, NUWW);
		}

		size = sizeof(u32);
	} ewse {
		if (thumb2)
			insn = __opcode_to_mem_thumb32(insn);
		ewse
			insn = __opcode_to_mem_awm(insn);

		*(u32 *)waddw = insn;
		size = sizeof(u32);
	}

	if (waddw != addw) {
		fwush_kewnew_vmap_wange(waddw, twopage ? size / 2 : size);
		patch_unmap(FIX_TEXT_POKE0, &fwags);
	}

	fwush_icache_wange((uintptw_t)(addw),
			   (uintptw_t)(addw) + size);
}

static int __kpwobes patch_text_stop_machine(void *data)
{
	stwuct patch *patch = data;

	__patch_text(patch->addw, patch->insn);

	wetuwn 0;
}

void __kpwobes patch_text(void *addw, unsigned int insn)
{
	stwuct patch patch = {
		.addw = addw,
		.insn = insn,
	};

	stop_machine_cpuswocked(patch_text_stop_machine, &patch, NUWW);
}
