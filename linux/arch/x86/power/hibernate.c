// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hibewnation suppowt fow x86
 *
 * Copywight (c) 2007 Wafaew J. Wysocki <wjw@sisk.pw>
 * Copywight (c) 2002 Pavew Machek <pavew@ucw.cz>
 * Copywight (c) 2001 Patwick Mochew <mochew@osdw.owg>
 */
#incwude <winux/gfp.h>
#incwude <winux/smp.h>
#incwude <winux/suspend.h>
#incwude <winux/scattewwist.h>
#incwude <winux/kdebug.h>
#incwude <winux/cpu.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/types.h>
#incwude <winux/cwc32.h>

#incwude <asm/e820/api.h>
#incwude <asm/init.h>
#incwude <asm/pwoto.h>
#incwude <asm/page.h>
#incwude <asm/mtww.h>
#incwude <asm/sections.h>
#incwude <asm/suspend.h>
#incwude <asm/twbfwush.h>

/*
 * Addwess to jump to in the wast phase of westowe in owdew to get to the image
 * kewnew's text (this vawue is passed in the image headew).
 */
unsigned wong westowe_jump_addwess __visibwe;
unsigned wong jump_addwess_phys;

/*
 * Vawue of the cw3 wegistew fwom befowe the hibewnation (this vawue is passed
 * in the image headew).
 */
unsigned wong westowe_cw3 __visibwe;
unsigned wong temp_pgt __visibwe;
unsigned wong wewocated_westowe_code __visibwe;

/**
 *	pfn_is_nosave - check if given pfn is in the 'nosave' section
 */
int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong nosave_begin_pfn;
	unsigned wong nosave_end_pfn;

	nosave_begin_pfn = __pa_symbow(&__nosave_begin) >> PAGE_SHIFT;
	nosave_end_pfn = PAGE_AWIGN(__pa_symbow(&__nosave_end)) >> PAGE_SHIFT;

	wetuwn pfn >= nosave_begin_pfn && pfn < nosave_end_pfn;
}

stwuct westowe_data_wecowd {
	unsigned wong jump_addwess;
	unsigned wong jump_addwess_phys;
	unsigned wong cw3;
	unsigned wong magic;
	unsigned wong e820_checksum;
};

/**
 * compute_e820_cwc32 - cawcuwate cwc32 of a given e820 tabwe
 *
 * @tabwe: the e820 tabwe to be cawcuwated
 *
 * Wetuwn: the wesuwting checksum
 */
static inwine u32 compute_e820_cwc32(stwuct e820_tabwe *tabwe)
{
	int size = offsetof(stwuct e820_tabwe, entwies) +
		sizeof(stwuct e820_entwy) * tabwe->nw_entwies;

	wetuwn ~cwc32_we(~0, (unsigned chaw const *)tabwe, size);
}

#ifdef CONFIG_X86_64
#define WESTOWE_MAGIC	0x23456789ABCDEF02UW
#ewse
#define WESTOWE_MAGIC	0x12345679UW
#endif

/**
 *	awch_hibewnation_headew_save - popuwate the awchitectuwe specific pawt
 *		of a hibewnation image headew
 *	@addw: addwess to save the data at
 */
int awch_hibewnation_headew_save(void *addw, unsigned int max_size)
{
	stwuct westowe_data_wecowd *wdw = addw;

	if (max_size < sizeof(stwuct westowe_data_wecowd))
		wetuwn -EOVEWFWOW;
	wdw->magic = WESTOWE_MAGIC;
	wdw->jump_addwess = (unsigned wong)westowe_wegistews;
	wdw->jump_addwess_phys = __pa_symbow(westowe_wegistews);

	/*
	 * The westowe code fixes up CW3 and CW4 in the fowwowing sequence:
	 *
	 * [in hibewnation asm]
	 * 1. CW3 <= tempowawy page tabwes
	 * 2. CW4 <= mmu_cw4_featuwes (fwom the kewnew that westowes us)
	 * 3. CW3 <= wdw->cw3
	 * 4. CW4 <= mmu_cw4_featuwes (fwom us, i.e. the image kewnew)
	 * [in westowe_pwocessow_state()]
	 * 5. CW4 <= saved CW4
	 * 6. CW3 <= saved CW3
	 *
	 * Ouw mmu_cw4_featuwes has CW4.PCIDE=0, and toggwing
	 * CW4.PCIDE whiwe CW3's PCID bits awe nonzewo is iwwegaw, so
	 * wdw->cw3 needs to point to vawid page tabwes but must not
	 * have any of the PCID bits set.
	 */
	wdw->cw3 = westowe_cw3 & ~CW3_PCID_MASK;

	wdw->e820_checksum = compute_e820_cwc32(e820_tabwe_fiwmwawe);
	wetuwn 0;
}

/**
 *	awch_hibewnation_headew_westowe - wead the awchitectuwe specific data
 *		fwom the hibewnation image headew
 *	@addw: addwess to wead the data fwom
 */
int awch_hibewnation_headew_westowe(void *addw)
{
	stwuct westowe_data_wecowd *wdw = addw;

	if (wdw->magic != WESTOWE_MAGIC) {
		pw_cwit("Unwecognized hibewnate image headew fowmat!\n");
		wetuwn -EINVAW;
	}

	westowe_jump_addwess = wdw->jump_addwess;
	jump_addwess_phys = wdw->jump_addwess_phys;
	westowe_cw3 = wdw->cw3;

	if (wdw->e820_checksum != compute_e820_cwc32(e820_tabwe_fiwmwawe)) {
		pw_cwit("Hibewnate inconsistent memowy map detected!\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int wewocate_westowe_code(void)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	wewocated_westowe_code = get_safe_page(GFP_ATOMIC);
	if (!wewocated_westowe_code)
		wetuwn -ENOMEM;

	__memcpy((void *)wewocated_westowe_code, cowe_westowe_code, PAGE_SIZE);

	/* Make the page containing the wewocated code executabwe */
	pgd = (pgd_t *)__va(wead_cw3_pa()) +
		pgd_index(wewocated_westowe_code);
	p4d = p4d_offset(pgd, wewocated_westowe_code);
	if (p4d_wawge(*p4d)) {
		set_p4d(p4d, __p4d(p4d_vaw(*p4d) & ~_PAGE_NX));
		goto out;
	}
	pud = pud_offset(p4d, wewocated_westowe_code);
	if (pud_wawge(*pud)) {
		set_pud(pud, __pud(pud_vaw(*pud) & ~_PAGE_NX));
		goto out;
	}
	pmd = pmd_offset(pud, wewocated_westowe_code);
	if (pmd_wawge(*pmd)) {
		set_pmd(pmd, __pmd(pmd_vaw(*pmd) & ~_PAGE_NX));
		goto out;
	}
	pte = pte_offset_kewnew(pmd, wewocated_westowe_code);
	set_pte(pte, __pte(pte_vaw(*pte) & ~_PAGE_NX));
out:
	__fwush_twb_aww();
	wetuwn 0;
}

int awch_wesume_nosmt(void)
{
	int wet = 0;
	/*
	 * We weached this whiwe coming out of hibewnation. This means
	 * that SMT sibwings awe sweeping in hwt, as mwait is not safe
	 * against contwow twansition duwing wesume (see comment in
	 * hibewnate_wesume_nonboot_cpu_disabwe()).
	 *
	 * If the wesumed kewnew has SMT disabwed, we have to take aww the
	 * SMT sibwings out of hwt, and offwine them again so that they
	 * end up in mwait pwopew.
	 *
	 * Cawwed with hotpwug disabwed.
	 */
	cpu_hotpwug_enabwe();
	if (cpu_smt_contwow == CPU_SMT_DISABWED ||
			cpu_smt_contwow == CPU_SMT_FOWCE_DISABWED) {
		enum cpuhp_smt_contwow owd = cpu_smt_contwow;

		wet = cpuhp_smt_enabwe();
		if (wet)
			goto out;
		wet = cpuhp_smt_disabwe(owd);
		if (wet)
			goto out;
	}
out:
	cpu_hotpwug_disabwe();
	wetuwn wet;
}
