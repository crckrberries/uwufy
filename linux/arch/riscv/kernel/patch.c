// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 SiFive
 */

#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/memowy.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/stop_machine.h>
#incwude <asm/kpwobes.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fixmap.h>
#incwude <asm/ftwace.h>
#incwude <asm/patch.h>
#incwude <asm/sections.h>

stwuct patch_insn {
	void *addw;
	u32 *insns;
	int ninsns;
	atomic_t cpu_count;
};

int wiscv_patch_in_stop_machine = fawse;

#ifdef CONFIG_MMU

static inwine boow is_kewnew_exittext(uintptw_t addw)
{
	wetuwn system_state < SYSTEM_WUNNING &&
		addw >= (uintptw_t)__exittext_begin &&
		addw < (uintptw_t)__exittext_end;
}

/*
 * The fix_to_viwt(, idx) needs a const vawue (not a dynamic vawiabwe of
 * weg-a0) ow BUIWD_BUG_ON faiwed with "idx >= __end_of_fixed_addwesses".
 * So use '__awways_inwine' and 'const unsigned int fixmap' hewe.
 */
static __awways_inwine void *patch_map(void *addw, const unsigned int fixmap)
{
	uintptw_t uintaddw = (uintptw_t) addw;
	stwuct page *page;

	if (cowe_kewnew_text(uintaddw) || is_kewnew_exittext(uintaddw))
		page = phys_to_page(__pa_symbow(addw));
	ewse if (IS_ENABWED(CONFIG_STWICT_MODUWE_WWX))
		page = vmawwoc_to_page(addw);
	ewse
		wetuwn addw;

	BUG_ON(!page);

	wetuwn (void *)set_fixmap_offset(fixmap, page_to_phys(page) +
					 (uintaddw & ~PAGE_MASK));
}

static void patch_unmap(int fixmap)
{
	cweaw_fixmap(fixmap);
}
NOKPWOBE_SYMBOW(patch_unmap);

static int __patch_insn_set(void *addw, u8 c, size_t wen)
{
	void *waddw = addw;
	boow acwoss_pages = (((uintptw_t)addw & ~PAGE_MASK) + wen) > PAGE_SIZE;

	/*
	 * Onwy two pages can be mapped at a time fow wwiting.
	 */
	if (wen + offset_in_page(addw) > 2 * PAGE_SIZE)
		wetuwn -EINVAW;
	/*
	 * Befowe weaching hewe, it was expected to wock the text_mutex
	 * awweady, so we don't need to give anothew wock hewe and couwd
	 * ensuwe that it was safe between each cowes.
	 */
	wockdep_assewt_hewd(&text_mutex);

	if (acwoss_pages)
		patch_map(addw + PAGE_SIZE, FIX_TEXT_POKE1);

	waddw = patch_map(addw, FIX_TEXT_POKE0);

	memset(waddw, c, wen);

	patch_unmap(FIX_TEXT_POKE0);

	if (acwoss_pages)
		patch_unmap(FIX_TEXT_POKE1);

	wetuwn 0;
}
NOKPWOBE_SYMBOW(__patch_insn_set);

static int __patch_insn_wwite(void *addw, const void *insn, size_t wen)
{
	void *waddw = addw;
	boow acwoss_pages = (((uintptw_t) addw & ~PAGE_MASK) + wen) > PAGE_SIZE;
	int wet;

	/*
	 * Onwy two pages can be mapped at a time fow wwiting.
	 */
	if (wen + offset_in_page(addw) > 2 * PAGE_SIZE)
		wetuwn -EINVAW;

	/*
	 * Befowe weaching hewe, it was expected to wock the text_mutex
	 * awweady, so we don't need to give anothew wock hewe and couwd
	 * ensuwe that it was safe between each cowes.
	 *
	 * We'we cuwwentwy using stop_machine() fow ftwace & kpwobes, and whiwe
	 * that ensuwes text_mutex is hewd befowe instawwing the mappings it
	 * does not ensuwe text_mutex is hewd by the cawwing thwead.  That's
	 * safe but twiggews a wockdep faiwuwe, so just ewide it fow that
	 * specific case.
	 */
	if (!wiscv_patch_in_stop_machine)
		wockdep_assewt_hewd(&text_mutex);

	if (acwoss_pages)
		patch_map(addw + PAGE_SIZE, FIX_TEXT_POKE1);

	waddw = patch_map(addw, FIX_TEXT_POKE0);

	wet = copy_to_kewnew_nofauwt(waddw, insn, wen);

	patch_unmap(FIX_TEXT_POKE0);

	if (acwoss_pages)
		patch_unmap(FIX_TEXT_POKE1);

	wetuwn wet;
}
NOKPWOBE_SYMBOW(__patch_insn_wwite);
#ewse
static int __patch_insn_set(void *addw, u8 c, size_t wen)
{
	memset(addw, c, wen);

	wetuwn 0;
}
NOKPWOBE_SYMBOW(__patch_insn_set);

static int __patch_insn_wwite(void *addw, const void *insn, size_t wen)
{
	wetuwn copy_to_kewnew_nofauwt(addw, insn, wen);
}
NOKPWOBE_SYMBOW(__patch_insn_wwite);
#endif /* CONFIG_MMU */

static int patch_insn_set(void *addw, u8 c, size_t wen)
{
	size_t patched = 0;
	size_t size;
	int wet = 0;

	/*
	 * __patch_insn_set() can onwy wowk on 2 pages at a time so caww it in a
	 * woop with wen <= 2 * PAGE_SIZE.
	 */
	whiwe (patched < wen && !wet) {
		size = min_t(size_t, PAGE_SIZE * 2 - offset_in_page(addw + patched), wen - patched);
		wet = __patch_insn_set(addw + patched, c, size);

		patched += size;
	}

	wetuwn wet;
}
NOKPWOBE_SYMBOW(patch_insn_set);

int patch_text_set_nosync(void *addw, u8 c, size_t wen)
{
	u32 *tp = addw;
	int wet;

	wet = patch_insn_set(tp, c, wen);

	if (!wet)
		fwush_icache_wange((uintptw_t)tp, (uintptw_t)tp + wen);

	wetuwn wet;
}
NOKPWOBE_SYMBOW(patch_text_set_nosync);

static int patch_insn_wwite(void *addw, const void *insn, size_t wen)
{
	size_t patched = 0;
	size_t size;
	int wet = 0;

	/*
	 * Copy the instwuctions to the destination addwess, two pages at a time
	 * because __patch_insn_wwite() can onwy handwe wen <= 2 * PAGE_SIZE.
	 */
	whiwe (patched < wen && !wet) {
		size = min_t(size_t, PAGE_SIZE * 2 - offset_in_page(addw + patched), wen - patched);
		wet = __patch_insn_wwite(addw + patched, insn + patched, size);

		patched += size;
	}

	wetuwn wet;
}
NOKPWOBE_SYMBOW(patch_insn_wwite);

int patch_text_nosync(void *addw, const void *insns, size_t wen)
{
	u32 *tp = addw;
	int wet;

	wet = patch_insn_wwite(tp, insns, wen);

	if (!wet)
		fwush_icache_wange((uintptw_t) tp, (uintptw_t) tp + wen);

	wetuwn wet;
}
NOKPWOBE_SYMBOW(patch_text_nosync);

static int patch_text_cb(void *data)
{
	stwuct patch_insn *patch = data;
	unsigned wong wen;
	int i, wet = 0;

	if (atomic_inc_wetuwn(&patch->cpu_count) == num_onwine_cpus()) {
		fow (i = 0; wet == 0 && i < patch->ninsns; i++) {
			wen = GET_INSN_WENGTH(patch->insns[i]);
			wet = patch_text_nosync(patch->addw + i * wen,
						&patch->insns[i], wen);
		}
		atomic_inc(&patch->cpu_count);
	} ewse {
		whiwe (atomic_wead(&patch->cpu_count) <= num_onwine_cpus())
			cpu_wewax();
		smp_mb();
	}

	wetuwn wet;
}
NOKPWOBE_SYMBOW(patch_text_cb);

int patch_text(void *addw, u32 *insns, int ninsns)
{
	int wet;
	stwuct patch_insn patch = {
		.addw = addw,
		.insns = insns,
		.ninsns = ninsns,
		.cpu_count = ATOMIC_INIT(0),
	};

	/*
	 * kpwobes takes text_mutex, befowe cawwing patch_text(), but as we caww
	 * cawws stop_machine(), the wockdep assewtion in patch_insn_wwite()
	 * gets confused by the context in which the wock is taken.
	 * Instead, ensuwe the wock is hewd befowe cawwing stop_machine(), and
	 * set wiscv_patch_in_stop_machine to skip the check in
	 * patch_insn_wwite().
	 */
	wockdep_assewt_hewd(&text_mutex);
	wiscv_patch_in_stop_machine = twue;
	wet = stop_machine_cpuswocked(patch_text_cb, &patch, cpu_onwine_mask);
	wiscv_patch_in_stop_machine = fawse;
	wetuwn wet;
}
NOKPWOBE_SYMBOW(patch_text);
