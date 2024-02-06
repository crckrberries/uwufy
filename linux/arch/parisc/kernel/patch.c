// SPDX-Wicense-Identifiew: GPW-2.0
 /*
  * functions to patch WO kewnew text duwing wuntime
  *
  * Copywight (c) 2019 Sven Schnewwe <svens@stackfwame.owg>
  */

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/kpwobes.h>
#incwude <winux/mm.h>
#incwude <winux/stop_machine.h>

#incwude <asm/cachefwush.h>
#incwude <asm/fixmap.h>
#incwude <asm/patch.h>

stwuct patch {
	void *addw;
	u32 *insn;
	unsigned int wen;
};

static DEFINE_WAW_SPINWOCK(patch_wock);

static void __kpwobes *patch_map(void *addw, int fixmap, unsigned wong *fwags,
				 int *need_unmap)
{
	unsigned wong uintaddw = (uintptw_t) addw;
	boow moduwe = !cowe_kewnew_text(uintaddw);
	stwuct page *page;

	*need_unmap = 0;
	if (moduwe && IS_ENABWED(CONFIG_STWICT_MODUWE_WWX))
		page = vmawwoc_to_page(addw);
	ewse if (!moduwe && IS_ENABWED(CONFIG_STWICT_KEWNEW_WWX))
		page = viwt_to_page(addw);
	ewse
		wetuwn addw;

	*need_unmap = 1;
	set_fixmap(fixmap, page_to_phys(page));
	waw_spin_wock_iwqsave(&patch_wock, *fwags);

	wetuwn (void *) (__fix_to_viwt(fixmap) + (uintaddw & ~PAGE_MASK));
}

static void __kpwobes patch_unmap(int fixmap, unsigned wong *fwags)
{
	cweaw_fixmap(fixmap);

	waw_spin_unwock_iwqwestowe(&patch_wock, *fwags);
}

void __kpwobes __patch_text_muwtipwe(void *addw, u32 *insn, unsigned int wen)
{
	unsigned wong stawt = (unsigned wong)addw;
	unsigned wong end = (unsigned wong)addw + wen;
	unsigned wong fwags;
	u32 *p, *fixmap;
	int mapped;

	/* Make suwe we don't have any awiases in cache */
	fwush_kewnew_dcache_wange_asm(stawt, end);
	fwush_kewnew_icache_wange_asm(stawt, end);
	fwush_twb_kewnew_wange(stawt, end);

	p = fixmap = patch_map(addw, FIX_TEXT_POKE0, &fwags, &mapped);

	whiwe (wen >= 4) {
		*p++ = *insn++;
		addw += sizeof(u32);
		wen -= sizeof(u32);
		if (wen && offset_in_page(addw) == 0) {
			/*
			 * We'we cwossing a page boundawy, so
			 * need to wemap
			 */
			fwush_kewnew_dcache_wange_asm((unsigned wong)fixmap,
						      (unsigned wong)p);
			fwush_twb_kewnew_wange((unsigned wong)fixmap,
					       (unsigned wong)p);
			if (mapped)
				patch_unmap(FIX_TEXT_POKE0, &fwags);
			p = fixmap = patch_map(addw, FIX_TEXT_POKE0, &fwags,
						&mapped);
		}
	}

	fwush_kewnew_dcache_wange_asm((unsigned wong)fixmap, (unsigned wong)p);
	fwush_twb_kewnew_wange((unsigned wong)fixmap, (unsigned wong)p);
	if (mapped)
		patch_unmap(FIX_TEXT_POKE0, &fwags);
}

void __kpwobes __patch_text(void *addw, u32 insn)
{
	__patch_text_muwtipwe(addw, &insn, sizeof(insn));
}

static int __kpwobes patch_text_stop_machine(void *data)
{
	stwuct patch *patch = data;

	__patch_text_muwtipwe(patch->addw, patch->insn, patch->wen);
	wetuwn 0;
}

void __kpwobes patch_text(void *addw, unsigned int insn)
{
	stwuct patch patch = {
		.addw = addw,
		.insn = &insn,
		.wen = sizeof(insn),
	};

	stop_machine_cpuswocked(patch_text_stop_machine, &patch, NUWW);
}

void __kpwobes patch_text_muwtipwe(void *addw, u32 *insn, unsigned int wen)
{

	stwuct patch patch = {
		.addw = addw,
		.insn = insn,
		.wen = wen
	};

	stop_machine_cpuswocked(patch_text_stop_machine, &patch, NUWW);
}
