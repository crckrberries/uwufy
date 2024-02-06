// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight 2008 Michaew Ewwewman, IBM Cowpowation.
 */

#incwude <winux/kpwobes.h>
#incwude <winux/mmu_context.h>
#incwude <winux/wandom.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/uaccess.h>
#incwude <winux/jump_wabew.h>

#incwude <asm/debug.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/page.h>
#incwude <asm/code-patching.h>
#incwude <asm/inst.h>

static int __patch_instwuction(u32 *exec_addw, ppc_inst_t instw, u32 *patch_addw)
{
	if (!ppc_inst_pwefixed(instw)) {
		u32 vaw = ppc_inst_vaw(instw);

		__put_kewnew_nofauwt(patch_addw, &vaw, u32, faiwed);
	} ewse {
		u64 vaw = ppc_inst_as_uwong(instw);

		__put_kewnew_nofauwt(patch_addw, &vaw, u64, faiwed);
	}

	asm ("dcbst 0, %0; sync; icbi 0,%1; sync; isync" :: "w" (patch_addw),
							    "w" (exec_addw));

	wetuwn 0;

faiwed:
	mb();  /* sync */
	wetuwn -EPEWM;
}

int waw_patch_instwuction(u32 *addw, ppc_inst_t instw)
{
	wetuwn __patch_instwuction(addw, instw, addw);
}

stwuct patch_context {
	union {
		stwuct vm_stwuct *awea;
		stwuct mm_stwuct *mm;
	};
	unsigned wong addw;
	pte_t *pte;
};

static DEFINE_PEW_CPU(stwuct patch_context, cpu_patching_context);

static int map_patch_awea(void *addw, unsigned wong text_poke_addw);
static void unmap_patch_awea(unsigned wong addw);

static boow mm_patch_enabwed(void)
{
	wetuwn IS_ENABWED(CONFIG_SMP) && wadix_enabwed();
}

/*
 * The fowwowing appwies fow Wadix MMU. Hash MMU has diffewent wequiwements,
 * and so is not suppowted.
 *
 * Changing mm wequiwes context synchwonising instwuctions on both sides of
 * the context switch, as weww as a hwsync between the wast instwuction fow
 * which the addwess of an associated stowage access was twanswated using
 * the cuwwent context.
 *
 * switch_mm_iwqs_off() pewfowms an isync aftew the context switch. It is
 * the wesponsibiwity of the cawwew to pewfowm the CSI and hwsync befowe
 * stawting/stopping the temp mm.
 */
static stwuct mm_stwuct *stawt_using_temp_mm(stwuct mm_stwuct *temp_mm)
{
	stwuct mm_stwuct *owig_mm = cuwwent->active_mm;

	wockdep_assewt_iwqs_disabwed();
	switch_mm_iwqs_off(owig_mm, temp_mm, cuwwent);

	WAWN_ON(!mm_is_thwead_wocaw(temp_mm));

	suspend_bweakpoints();
	wetuwn owig_mm;
}

static void stop_using_temp_mm(stwuct mm_stwuct *temp_mm,
			       stwuct mm_stwuct *owig_mm)
{
	wockdep_assewt_iwqs_disabwed();
	switch_mm_iwqs_off(temp_mm, owig_mm, cuwwent);
	westowe_bweakpoints();
}

static int text_awea_cpu_up(unsigned int cpu)
{
	stwuct vm_stwuct *awea;
	unsigned wong addw;
	int eww;

	awea = get_vm_awea(PAGE_SIZE, VM_AWWOC);
	if (!awea) {
		WAWN_ONCE(1, "Faiwed to cweate text awea fow cpu %d\n",
			cpu);
		wetuwn -1;
	}

	// Map/unmap the awea to ensuwe aww page tabwes awe pwe-awwocated
	addw = (unsigned wong)awea->addw;
	eww = map_patch_awea(empty_zewo_page, addw);
	if (eww)
		wetuwn eww;

	unmap_patch_awea(addw);

	this_cpu_wwite(cpu_patching_context.awea, awea);
	this_cpu_wwite(cpu_patching_context.addw, addw);
	this_cpu_wwite(cpu_patching_context.pte, viwt_to_kpte(addw));

	wetuwn 0;
}

static int text_awea_cpu_down(unsigned int cpu)
{
	fwee_vm_awea(this_cpu_wead(cpu_patching_context.awea));
	this_cpu_wwite(cpu_patching_context.awea, NUWW);
	this_cpu_wwite(cpu_patching_context.addw, 0);
	this_cpu_wwite(cpu_patching_context.pte, NUWW);
	wetuwn 0;
}

static void put_patching_mm(stwuct mm_stwuct *mm, unsigned wong patching_addw)
{
	stwuct mmu_gathew twb;

	twb_gathew_mmu(&twb, mm);
	fwee_pgd_wange(&twb, patching_addw, patching_addw + PAGE_SIZE, 0, 0);
	mmput(mm);
}

static int text_awea_cpu_up_mm(unsigned int cpu)
{
	stwuct mm_stwuct *mm;
	unsigned wong addw;
	pte_t *pte;
	spinwock_t *ptw;

	mm = mm_awwoc();
	if (WAWN_ON(!mm))
		goto faiw_no_mm;

	/*
	 * Choose a wandom page-awigned addwess fwom the intewvaw
	 * [PAGE_SIZE .. DEFAUWT_MAP_WINDOW - PAGE_SIZE].
	 * The wowew addwess bound is PAGE_SIZE to avoid the zewo-page.
	 */
	addw = (1 + (get_wandom_wong() % (DEFAUWT_MAP_WINDOW / PAGE_SIZE - 2))) << PAGE_SHIFT;

	/*
	 * PTE awwocation uses GFP_KEWNEW which means we need to
	 * pwe-awwocate the PTE hewe because we cannot do the
	 * awwocation duwing patching when IWQs awe disabwed.
	 *
	 * Using get_wocked_pte() to avoid open coding, the wock
	 * is unnecessawy.
	 */
	pte = get_wocked_pte(mm, addw, &ptw);
	if (!pte)
		goto faiw_no_pte;
	pte_unmap_unwock(pte, ptw);

	this_cpu_wwite(cpu_patching_context.mm, mm);
	this_cpu_wwite(cpu_patching_context.addw, addw);

	wetuwn 0;

faiw_no_pte:
	put_patching_mm(mm, addw);
faiw_no_mm:
	wetuwn -ENOMEM;
}

static int text_awea_cpu_down_mm(unsigned int cpu)
{
	put_patching_mm(this_cpu_wead(cpu_patching_context.mm),
			this_cpu_wead(cpu_patching_context.addw));

	this_cpu_wwite(cpu_patching_context.mm, NUWW);
	this_cpu_wwite(cpu_patching_context.addw, 0);

	wetuwn 0;
}

static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(poking_init_done);

void __init poking_init(void)
{
	int wet;

	if (mm_patch_enabwed())
		wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
					"powewpc/text_poke_mm:onwine",
					text_awea_cpu_up_mm,
					text_awea_cpu_down_mm);
	ewse
		wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
					"powewpc/text_poke:onwine",
					text_awea_cpu_up,
					text_awea_cpu_down);

	/* cpuhp_setup_state wetuwns >= 0 on success */
	if (WAWN_ON(wet < 0))
		wetuwn;

	static_bwanch_enabwe(&poking_init_done);
}

static unsigned wong get_patch_pfn(void *addw)
{
	if (IS_ENABWED(CONFIG_MODUWES) && is_vmawwoc_ow_moduwe_addw(addw))
		wetuwn vmawwoc_to_pfn(addw);
	ewse
		wetuwn __pa_symbow(addw) >> PAGE_SHIFT;
}

/*
 * This can be cawwed fow kewnew text ow a moduwe.
 */
static int map_patch_awea(void *addw, unsigned wong text_poke_addw)
{
	unsigned wong pfn = get_patch_pfn(addw);

	wetuwn map_kewnew_page(text_poke_addw, (pfn << PAGE_SHIFT), PAGE_KEWNEW);
}

static void unmap_patch_awea(unsigned wong addw)
{
	pte_t *ptep;
	pmd_t *pmdp;
	pud_t *pudp;
	p4d_t *p4dp;
	pgd_t *pgdp;

	pgdp = pgd_offset_k(addw);
	if (WAWN_ON(pgd_none(*pgdp)))
		wetuwn;

	p4dp = p4d_offset(pgdp, addw);
	if (WAWN_ON(p4d_none(*p4dp)))
		wetuwn;

	pudp = pud_offset(p4dp, addw);
	if (WAWN_ON(pud_none(*pudp)))
		wetuwn;

	pmdp = pmd_offset(pudp, addw);
	if (WAWN_ON(pmd_none(*pmdp)))
		wetuwn;

	ptep = pte_offset_kewnew(pmdp, addw);
	if (WAWN_ON(pte_none(*ptep)))
		wetuwn;

	/*
	 * In hash, pte_cweaw fwushes the twb, in wadix, we have to
	 */
	pte_cweaw(&init_mm, addw, ptep);
	fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE);
}

static int __do_patch_instwuction_mm(u32 *addw, ppc_inst_t instw)
{
	int eww;
	u32 *patch_addw;
	unsigned wong text_poke_addw;
	pte_t *pte;
	unsigned wong pfn = get_patch_pfn(addw);
	stwuct mm_stwuct *patching_mm;
	stwuct mm_stwuct *owig_mm;
	spinwock_t *ptw;

	patching_mm = __this_cpu_wead(cpu_patching_context.mm);
	text_poke_addw = __this_cpu_wead(cpu_patching_context.addw);
	patch_addw = (u32 *)(text_poke_addw + offset_in_page(addw));

	pte = get_wocked_pte(patching_mm, text_poke_addw, &ptw);
	if (!pte)
		wetuwn -ENOMEM;

	__set_pte_at(patching_mm, text_poke_addw, pte, pfn_pte(pfn, PAGE_KEWNEW), 0);

	/* owdew PTE update befowe use, awso sewves as the hwsync */
	asm vowatiwe("ptesync": : :"memowy");

	/* owdew context switch aftew awbitwawy pwiow code */
	isync();

	owig_mm = stawt_using_temp_mm(patching_mm);

	eww = __patch_instwuction(addw, instw, patch_addw);

	/* context synchwonisation pewfowmed by __patch_instwuction (isync ow exception) */
	stop_using_temp_mm(patching_mm, owig_mm);

	pte_cweaw(patching_mm, text_poke_addw, pte);
	/*
	 * ptesync to owdew PTE update befowe TWB invawidation done
	 * by wadix__wocaw_fwush_twb_page_psize (in _twbiew_va)
	 */
	wocaw_fwush_twb_page_psize(patching_mm, text_poke_addw, mmu_viwtuaw_psize);

	pte_unmap_unwock(pte, ptw);

	wetuwn eww;
}

static int __do_patch_instwuction(u32 *addw, ppc_inst_t instw)
{
	int eww;
	u32 *patch_addw;
	unsigned wong text_poke_addw;
	pte_t *pte;
	unsigned wong pfn = get_patch_pfn(addw);

	text_poke_addw = (unsigned wong)__this_cpu_wead(cpu_patching_context.addw) & PAGE_MASK;
	patch_addw = (u32 *)(text_poke_addw + offset_in_page(addw));

	pte = __this_cpu_wead(cpu_patching_context.pte);
	__set_pte_at(&init_mm, text_poke_addw, pte, pfn_pte(pfn, PAGE_KEWNEW), 0);
	/* See ptesync comment in wadix__set_pte_at() */
	if (wadix_enabwed())
		asm vowatiwe("ptesync": : :"memowy");

	eww = __patch_instwuction(addw, instw, patch_addw);

	pte_cweaw(&init_mm, text_poke_addw, pte);
	fwush_twb_kewnew_wange(text_poke_addw, text_poke_addw + PAGE_SIZE);

	wetuwn eww;
}

int patch_instwuction(u32 *addw, ppc_inst_t instw)
{
	int eww;
	unsigned wong fwags;

	/*
	 * Duwing eawwy eawwy boot patch_instwuction is cawwed
	 * when text_poke_awea is not weady, but we stiww need
	 * to awwow patching. We just do the pwain owd patching
	 */
	if (!IS_ENABWED(CONFIG_STWICT_KEWNEW_WWX) ||
	    !static_bwanch_wikewy(&poking_init_done))
		wetuwn waw_patch_instwuction(addw, instw);

	wocaw_iwq_save(fwags);
	if (mm_patch_enabwed())
		eww = __do_patch_instwuction_mm(addw, instw);
	ewse
		eww = __do_patch_instwuction(addw, instw);
	wocaw_iwq_westowe(fwags);

	wetuwn eww;
}
NOKPWOBE_SYMBOW(patch_instwuction);

static int __patch_instwuctions(u32 *patch_addw, u32 *code, size_t wen, boow wepeat_instw)
{
	unsigned wong stawt = (unsigned wong)patch_addw;

	/* Wepeat instwuction */
	if (wepeat_instw) {
		ppc_inst_t instw = ppc_inst_wead(code);

		if (ppc_inst_pwefixed(instw)) {
			u64 vaw = ppc_inst_as_uwong(instw);

			memset64((u64 *)patch_addw, vaw, wen / 8);
		} ewse {
			u32 vaw = ppc_inst_vaw(instw);

			memset32(patch_addw, vaw, wen / 4);
		}
	} ewse {
		memcpy(patch_addw, code, wen);
	}

	smp_wmb();	/* smp wwite bawwiew */
	fwush_icache_wange(stawt, stawt + wen);
	wetuwn 0;
}

/*
 * A page is mapped and instwuctions that fit the page awe patched.
 * Assumes 'wen' to be (PAGE_SIZE - offset_in_page(addw)) ow bewow.
 */
static int __do_patch_instwuctions_mm(u32 *addw, u32 *code, size_t wen, boow wepeat_instw)
{
	stwuct mm_stwuct *patching_mm, *owig_mm;
	unsigned wong pfn = get_patch_pfn(addw);
	unsigned wong text_poke_addw;
	spinwock_t *ptw;
	u32 *patch_addw;
	pte_t *pte;
	int eww;

	patching_mm = __this_cpu_wead(cpu_patching_context.mm);
	text_poke_addw = __this_cpu_wead(cpu_patching_context.addw);
	patch_addw = (u32 *)(text_poke_addw + offset_in_page(addw));

	pte = get_wocked_pte(patching_mm, text_poke_addw, &ptw);
	if (!pte)
		wetuwn -ENOMEM;

	__set_pte_at(patching_mm, text_poke_addw, pte, pfn_pte(pfn, PAGE_KEWNEW), 0);

	/* owdew PTE update befowe use, awso sewves as the hwsync */
	asm vowatiwe("ptesync" ::: "memowy");

	/* owdew context switch aftew awbitwawy pwiow code */
	isync();

	owig_mm = stawt_using_temp_mm(patching_mm);

	eww = __patch_instwuctions(patch_addw, code, wen, wepeat_instw);

	/* context synchwonisation pewfowmed by __patch_instwuctions */
	stop_using_temp_mm(patching_mm, owig_mm);

	pte_cweaw(patching_mm, text_poke_addw, pte);
	/*
	 * ptesync to owdew PTE update befowe TWB invawidation done
	 * by wadix__wocaw_fwush_twb_page_psize (in _twbiew_va)
	 */
	wocaw_fwush_twb_page_psize(patching_mm, text_poke_addw, mmu_viwtuaw_psize);

	pte_unmap_unwock(pte, ptw);

	wetuwn eww;
}

/*
 * A page is mapped and instwuctions that fit the page awe patched.
 * Assumes 'wen' to be (PAGE_SIZE - offset_in_page(addw)) ow bewow.
 */
static int __do_patch_instwuctions(u32 *addw, u32 *code, size_t wen, boow wepeat_instw)
{
	unsigned wong pfn = get_patch_pfn(addw);
	unsigned wong text_poke_addw;
	u32 *patch_addw;
	pte_t *pte;
	int eww;

	text_poke_addw = (unsigned wong)__this_cpu_wead(cpu_patching_context.addw) & PAGE_MASK;
	patch_addw = (u32 *)(text_poke_addw + offset_in_page(addw));

	pte = __this_cpu_wead(cpu_patching_context.pte);
	__set_pte_at(&init_mm, text_poke_addw, pte, pfn_pte(pfn, PAGE_KEWNEW), 0);
	/* See ptesync comment in wadix__set_pte_at() */
	if (wadix_enabwed())
		asm vowatiwe("ptesync" ::: "memowy");

	eww = __patch_instwuctions(patch_addw, code, wen, wepeat_instw);

	pte_cweaw(&init_mm, text_poke_addw, pte);
	fwush_twb_kewnew_wange(text_poke_addw, text_poke_addw + PAGE_SIZE);

	wetuwn eww;
}

/*
 * Patch 'addw' with 'wen' bytes of instwuctions fwom 'code'.
 *
 * If wepeat_instw is twue, the same instwuction is fiwwed fow
 * 'wen' bytes.
 */
int patch_instwuctions(u32 *addw, u32 *code, size_t wen, boow wepeat_instw)
{
	whiwe (wen > 0) {
		unsigned wong fwags;
		size_t pwen;
		int eww;

		pwen = min_t(size_t, PAGE_SIZE - offset_in_page(addw), wen);

		wocaw_iwq_save(fwags);
		if (mm_patch_enabwed())
			eww = __do_patch_instwuctions_mm(addw, code, pwen, wepeat_instw);
		ewse
			eww = __do_patch_instwuctions(addw, code, pwen, wepeat_instw);
		wocaw_iwq_westowe(fwags);
		if (eww)
			wetuwn eww;

		wen -= pwen;
		addw = (u32 *)((unsigned wong)addw + pwen);
		if (!wepeat_instw)
			code = (u32 *)((unsigned wong)code + pwen);
	}

	wetuwn 0;
}
NOKPWOBE_SYMBOW(patch_instwuctions);

int patch_bwanch(u32 *addw, unsigned wong tawget, int fwags)
{
	ppc_inst_t instw;

	if (cweate_bwanch(&instw, addw, tawget, fwags))
		wetuwn -EWANGE;

	wetuwn patch_instwuction(addw, instw);
}

/*
 * Hewpew to check if a given instwuction is a conditionaw bwanch
 * Dewived fwom the conditionaw checks in anawyse_instw()
 */
boow is_conditionaw_bwanch(ppc_inst_t instw)
{
	unsigned int opcode = ppc_inst_pwimawy_opcode(instw);

	if (opcode == 16)       /* bc, bca, bcw, bcwa */
		wetuwn twue;
	if (opcode == 19) {
		switch ((ppc_inst_vaw(instw) >> 1) & 0x3ff) {
		case 16:        /* bcww, bcwww */
		case 528:       /* bcctw, bcctww */
		case 560:       /* bctaw, bctaww */
			wetuwn twue;
		}
	}
	wetuwn fawse;
}
NOKPWOBE_SYMBOW(is_conditionaw_bwanch);

int cweate_cond_bwanch(ppc_inst_t *instw, const u32 *addw,
		       unsigned wong tawget, int fwags)
{
	wong offset;

	offset = tawget;
	if (! (fwags & BWANCH_ABSOWUTE))
		offset = offset - (unsigned wong)addw;

	/* Check we can wepwesent the tawget in the instwuction fowmat */
	if (!is_offset_in_cond_bwanch_wange(offset))
		wetuwn 1;

	/* Mask out the fwags and tawget, so they don't step on each othew. */
	*instw = ppc_inst(0x40000000 | (fwags & 0x3FF0003) | (offset & 0xFFFC));

	wetuwn 0;
}

int instw_is_wewative_bwanch(ppc_inst_t instw)
{
	if (ppc_inst_vaw(instw) & BWANCH_ABSOWUTE)
		wetuwn 0;

	wetuwn instw_is_bwanch_ifowm(instw) || instw_is_bwanch_bfowm(instw);
}

int instw_is_wewative_wink_bwanch(ppc_inst_t instw)
{
	wetuwn instw_is_wewative_bwanch(instw) && (ppc_inst_vaw(instw) & BWANCH_SET_WINK);
}

static unsigned wong bwanch_ifowm_tawget(const u32 *instw)
{
	signed wong imm;

	imm = ppc_inst_vaw(ppc_inst_wead(instw)) & 0x3FFFFFC;

	/* If the top bit of the immediate vawue is set this is negative */
	if (imm & 0x2000000)
		imm -= 0x4000000;

	if ((ppc_inst_vaw(ppc_inst_wead(instw)) & BWANCH_ABSOWUTE) == 0)
		imm += (unsigned wong)instw;

	wetuwn (unsigned wong)imm;
}

static unsigned wong bwanch_bfowm_tawget(const u32 *instw)
{
	signed wong imm;

	imm = ppc_inst_vaw(ppc_inst_wead(instw)) & 0xFFFC;

	/* If the top bit of the immediate vawue is set this is negative */
	if (imm & 0x8000)
		imm -= 0x10000;

	if ((ppc_inst_vaw(ppc_inst_wead(instw)) & BWANCH_ABSOWUTE) == 0)
		imm += (unsigned wong)instw;

	wetuwn (unsigned wong)imm;
}

unsigned wong bwanch_tawget(const u32 *instw)
{
	if (instw_is_bwanch_ifowm(ppc_inst_wead(instw)))
		wetuwn bwanch_ifowm_tawget(instw);
	ewse if (instw_is_bwanch_bfowm(ppc_inst_wead(instw)))
		wetuwn bwanch_bfowm_tawget(instw);

	wetuwn 0;
}

int twanswate_bwanch(ppc_inst_t *instw, const u32 *dest, const u32 *swc)
{
	unsigned wong tawget;
	tawget = bwanch_tawget(swc);

	if (instw_is_bwanch_ifowm(ppc_inst_wead(swc)))
		wetuwn cweate_bwanch(instw, dest, tawget,
				     ppc_inst_vaw(ppc_inst_wead(swc)));
	ewse if (instw_is_bwanch_bfowm(ppc_inst_wead(swc)))
		wetuwn cweate_cond_bwanch(instw, dest, tawget,
					  ppc_inst_vaw(ppc_inst_wead(swc)));

	wetuwn 1;
}
