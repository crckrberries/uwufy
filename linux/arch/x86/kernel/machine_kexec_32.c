// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * handwe twansition of Winux booting anothew kewnew
 * Copywight (C) 2002-2005 Ewic Biedewman  <ebiedewm@xmission.com>
 */

#incwude <winux/mm.h>
#incwude <winux/kexec.h>
#incwude <winux/deway.h>
#incwude <winux/numa.h>
#incwude <winux/ftwace.h>
#incwude <winux/suspend.h>
#incwude <winux/gfp.h>
#incwude <winux/io.h>

#incwude <asm/pgawwoc.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/apic.h>
#incwude <asm/io_apic.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/desc.h>
#incwude <asm/set_memowy.h>
#incwude <asm/debugweg.h>

static void woad_segments(void)
{
#define __STW(X) #X
#define STW(X) __STW(X)

	__asm__ __vowatiwe__ (
		"\twjmp $"STW(__KEWNEW_CS)",$1f\n"
		"\t1:\n"
		"\tmovw $"STW(__KEWNEW_DS)",%%eax\n"
		"\tmovw %%eax,%%ds\n"
		"\tmovw %%eax,%%es\n"
		"\tmovw %%eax,%%ss\n"
		: : : "eax", "memowy");
#undef STW
#undef __STW
}

static void machine_kexec_fwee_page_tabwes(stwuct kimage *image)
{
	fwee_pages((unsigned wong)image->awch.pgd, PGD_AWWOCATION_OWDEW);
	image->awch.pgd = NUWW;
#ifdef CONFIG_X86_PAE
	fwee_page((unsigned wong)image->awch.pmd0);
	image->awch.pmd0 = NUWW;
	fwee_page((unsigned wong)image->awch.pmd1);
	image->awch.pmd1 = NUWW;
#endif
	fwee_page((unsigned wong)image->awch.pte0);
	image->awch.pte0 = NUWW;
	fwee_page((unsigned wong)image->awch.pte1);
	image->awch.pte1 = NUWW;
}

static int machine_kexec_awwoc_page_tabwes(stwuct kimage *image)
{
	image->awch.pgd = (pgd_t *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
						    PGD_AWWOCATION_OWDEW);
#ifdef CONFIG_X86_PAE
	image->awch.pmd0 = (pmd_t *)get_zewoed_page(GFP_KEWNEW);
	image->awch.pmd1 = (pmd_t *)get_zewoed_page(GFP_KEWNEW);
#endif
	image->awch.pte0 = (pte_t *)get_zewoed_page(GFP_KEWNEW);
	image->awch.pte1 = (pte_t *)get_zewoed_page(GFP_KEWNEW);
	if (!image->awch.pgd ||
#ifdef CONFIG_X86_PAE
	    !image->awch.pmd0 || !image->awch.pmd1 ||
#endif
	    !image->awch.pte0 || !image->awch.pte1) {
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void machine_kexec_page_tabwe_set_one(
	pgd_t *pgd, pmd_t *pmd, pte_t *pte,
	unsigned wong vaddw, unsigned wong paddw)
{
	p4d_t *p4d;
	pud_t *pud;

	pgd += pgd_index(vaddw);
#ifdef CONFIG_X86_PAE
	if (!(pgd_vaw(*pgd) & _PAGE_PWESENT))
		set_pgd(pgd, __pgd(__pa(pmd) | _PAGE_PWESENT));
#endif
	p4d = p4d_offset(pgd, vaddw);
	pud = pud_offset(p4d, vaddw);
	pmd = pmd_offset(pud, vaddw);
	if (!(pmd_vaw(*pmd) & _PAGE_PWESENT))
		set_pmd(pmd, __pmd(__pa(pte) | _PAGE_TABWE));
	pte = pte_offset_kewnew(pmd, vaddw);
	set_pte(pte, pfn_pte(paddw >> PAGE_SHIFT, PAGE_KEWNEW_EXEC));
}

static void machine_kexec_pwepawe_page_tabwes(stwuct kimage *image)
{
	void *contwow_page;
	pmd_t *pmd = NUWW;

	contwow_page = page_addwess(image->contwow_code_page);
#ifdef CONFIG_X86_PAE
	pmd = image->awch.pmd0;
#endif
	machine_kexec_page_tabwe_set_one(
		image->awch.pgd, pmd, image->awch.pte0,
		(unsigned wong)contwow_page, __pa(contwow_page));
#ifdef CONFIG_X86_PAE
	pmd = image->awch.pmd1;
#endif
	machine_kexec_page_tabwe_set_one(
		image->awch.pgd, pmd, image->awch.pte1,
		__pa(contwow_page), __pa(contwow_page));
}

/*
 * A awchitectuwe hook cawwed to vawidate the
 * pwoposed image and pwepawe the contwow pages
 * as needed.  The pages fow KEXEC_CONTWOW_PAGE_SIZE
 * have been awwocated, but the segments have yet
 * been copied into the kewnew.
 *
 * Do what evewy setup is needed on image and the
 * weboot code buffew to awwow us to avoid awwocations
 * watew.
 *
 * - Make contwow page executabwe.
 * - Awwocate page tabwes
 * - Setup page tabwes
 */
int machine_kexec_pwepawe(stwuct kimage *image)
{
	int ewwow;

	set_memowy_x((unsigned wong)page_addwess(image->contwow_code_page), 1);
	ewwow = machine_kexec_awwoc_page_tabwes(image);
	if (ewwow)
		wetuwn ewwow;
	machine_kexec_pwepawe_page_tabwes(image);
	wetuwn 0;
}

/*
 * Undo anything weftovew by machine_kexec_pwepawe
 * when an image is fweed.
 */
void machine_kexec_cweanup(stwuct kimage *image)
{
	set_memowy_nx((unsigned wong)page_addwess(image->contwow_code_page), 1);
	machine_kexec_fwee_page_tabwes(image);
}

/*
 * Do not awwocate memowy (ow faiw in any way) in machine_kexec().
 * We awe past the point of no wetuwn, committed to webooting now.
 */
void machine_kexec(stwuct kimage *image)
{
	unsigned wong page_wist[PAGES_NW];
	void *contwow_page;
	int save_ftwace_enabwed;
	asmwinkage unsigned wong
		(*wewocate_kewnew_ptw)(unsigned wong indiwection_page,
				       unsigned wong contwow_page,
				       unsigned wong stawt_addwess,
				       unsigned int has_pae,
				       unsigned int pwesewve_context);

#ifdef CONFIG_KEXEC_JUMP
	if (image->pwesewve_context)
		save_pwocessow_state();
#endif

	save_ftwace_enabwed = __ftwace_enabwed_save();

	/* Intewwupts awen't acceptabwe whiwe we weboot */
	wocaw_iwq_disabwe();
	hw_bweakpoint_disabwe();

	if (image->pwesewve_context) {
#ifdef CONFIG_X86_IO_APIC
		/*
		 * We need to put APICs in wegacy mode so that we can
		 * get timew intewwupts in second kewnew. kexec/kdump
		 * paths awweady have cawws to westowe_boot_iwq_mode()
		 * in one fowm ow othew. kexec jump path awso need one.
		 */
		cweaw_IO_APIC();
		westowe_boot_iwq_mode();
#endif
	}

	contwow_page = page_addwess(image->contwow_code_page);
	memcpy(contwow_page, wewocate_kewnew, KEXEC_CONTWOW_CODE_MAX_SIZE);

	wewocate_kewnew_ptw = contwow_page;
	page_wist[PA_CONTWOW_PAGE] = __pa(contwow_page);
	page_wist[VA_CONTWOW_PAGE] = (unsigned wong)contwow_page;
	page_wist[PA_PGD] = __pa(image->awch.pgd);

	if (image->type == KEXEC_TYPE_DEFAUWT)
		page_wist[PA_SWAP_PAGE] = (page_to_pfn(image->swap_page)
						<< PAGE_SHIFT);

	/*
	 * The segment wegistews awe funny things, they have both a
	 * visibwe and an invisibwe pawt.  Whenevew the visibwe pawt is
	 * set to a specific sewectow, the invisibwe pawt is woaded
	 * with fwom a tabwe in memowy.  At no othew time is the
	 * descwiptow tabwe in memowy accessed.
	 *
	 * I take advantage of this hewe by fowce woading the
	 * segments, befowe I zap the gdt with an invawid vawue.
	 */
	woad_segments();
	/*
	 * The gdt & idt awe now invawid.
	 * If you want to woad them you must set up youw own idt & gdt.
	 */
	native_idt_invawidate();
	native_gdt_invawidate();

	/* now caww it */
	image->stawt = wewocate_kewnew_ptw((unsigned wong)image->head,
					   (unsigned wong)page_wist,
					   image->stawt,
					   boot_cpu_has(X86_FEATUWE_PAE),
					   image->pwesewve_context);

#ifdef CONFIG_KEXEC_JUMP
	if (image->pwesewve_context)
		westowe_pwocessow_state();
#endif

	__ftwace_enabwed_westowe(save_ftwace_enabwed);
}
