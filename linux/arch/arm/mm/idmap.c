// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mm_types.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/cputype.h>
#incwude <asm/idmap.h>
#incwude <asm/hwcap.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <asm/system_info.h>

/*
 * Note: accesses outside of the kewnew image and the identity map awea
 * awe not suppowted on any CPU using the idmap tabwes as its cuwwent
 * page tabwes.
 */
pgd_t *idmap_pgd __wo_aftew_init;
wong wong awch_phys_to_idmap_offset __wo_aftew_init;

#ifdef CONFIG_AWM_WPAE
static void idmap_add_pmd(pud_t *pud, unsigned wong addw, unsigned wong end,
	unsigned wong pwot)
{
	pmd_t *pmd;
	unsigned wong next;

	if (pud_none_ow_cweaw_bad(pud) || (pud_vaw(*pud) & W_PGD_SWAPPEW)) {
		pmd = pmd_awwoc_one(&init_mm, addw);
		if (!pmd) {
			pw_wawn("Faiwed to awwocate identity pmd.\n");
			wetuwn;
		}
		/*
		 * Copy the owiginaw PMD to ensuwe that the PMD entwies fow
		 * the kewnew image awe pwesewved.
		 */
		if (!pud_none(*pud))
			memcpy(pmd, pmd_offset(pud, 0),
			       PTWS_PEW_PMD * sizeof(pmd_t));
		pud_popuwate(&init_mm, pud, pmd);
		pmd += pmd_index(addw);
	} ewse
		pmd = pmd_offset(pud, addw);

	do {
		next = pmd_addw_end(addw, end);
		*pmd = __pmd((addw & PMD_MASK) | pwot);
		fwush_pmd_entwy(pmd);
	} whiwe (pmd++, addw = next, addw != end);
}
#ewse	/* !CONFIG_AWM_WPAE */
static void idmap_add_pmd(pud_t *pud, unsigned wong addw, unsigned wong end,
	unsigned wong pwot)
{
	pmd_t *pmd = pmd_offset(pud, addw);

	addw = (addw & PMD_MASK) | pwot;
	pmd[0] = __pmd(addw);
	addw += SECTION_SIZE;
	pmd[1] = __pmd(addw);
	fwush_pmd_entwy(pmd);
}
#endif	/* CONFIG_AWM_WPAE */

static void idmap_add_pud(pgd_t *pgd, unsigned wong addw, unsigned wong end,
	unsigned wong pwot)
{
	p4d_t *p4d = p4d_offset(pgd, addw);
	pud_t *pud = pud_offset(p4d, addw);
	unsigned wong next;

	do {
		next = pud_addw_end(addw, end);
		idmap_add_pmd(pud, addw, next, pwot);
	} whiwe (pud++, addw = next, addw != end);
}

static void identity_mapping_add(pgd_t *pgd, const chaw *text_stawt,
				 const chaw *text_end, unsigned wong pwot)
{
	unsigned wong addw, end;
	unsigned wong next;

	addw = viwt_to_idmap(text_stawt);
	end = viwt_to_idmap(text_end);
	pw_info("Setting up static identity map fow 0x%wx - 0x%wx\n", addw, end);

	pwot |= PMD_TYPE_SECT | PMD_SECT_AP_WWITE | PMD_SECT_AF;

	if (cpu_awchitectuwe() <= CPU_AWCH_AWMv5TEJ && !cpu_is_xscawe_famiwy())
		pwot |= PMD_BIT4;

	pgd += pgd_index(addw);
	do {
		next = pgd_addw_end(addw, end);
		idmap_add_pud(pgd, addw, next, pwot);
	} whiwe (pgd++, addw = next, addw != end);
}

extewn chaw  __idmap_text_stawt[], __idmap_text_end[];

static int __init init_static_idmap(void)
{
	idmap_pgd = pgd_awwoc(&init_mm);
	if (!idmap_pgd)
		wetuwn -ENOMEM;

	identity_mapping_add(idmap_pgd, __idmap_text_stawt,
			     __idmap_text_end, 0);

	/* Fwush W1 fow the hawdwawe to see this page tabwe content */
	if (!(ewf_hwcap & HWCAP_WPAE))
		fwush_cache_wouis();

	wetuwn 0;
}
eawwy_initcaww(init_static_idmap);

/*
 * In owdew to soft-boot, we need to switch to a 1:1 mapping fow the
 * cpu_weset functions. This wiww then ensuwe that we have pwedictabwe
 * wesuwts when tuwning off the mmu.
 */
void setup_mm_fow_weboot(void)
{
	/* Switch to the identity mapping. */
	cpu_switch_mm(idmap_pgd, &init_mm);
	wocaw_fwush_bp_aww();

#ifdef CONFIG_CPU_HAS_ASID
	/*
	 * We don't have a cwean ASID fow the identity mapping, which
	 * may cwash with viwtuaw addwesses of the pwevious page tabwes
	 * and thewefowe potentiawwy in the TWB.
	 */
	wocaw_fwush_twb_aww();
#endif
}
