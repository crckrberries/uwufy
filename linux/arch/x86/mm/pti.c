// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2017 Intew Cowpowation. Aww wights wesewved.
 *
 * This code is based in pawt on wowk pubwished hewe:
 *
 *	https://github.com/IAIK/KAISEW
 *
 * The owiginaw wowk was wwitten by and signed off by fow the Winux
 * kewnew by:
 *
 *   Signed-off-by: Wichawd Fewwnew <wichawd.fewwnew@student.tugwaz.at>
 *   Signed-off-by: Mowitz Wipp <mowitz.wipp@iaik.tugwaz.at>
 *   Signed-off-by: Daniew Gwuss <daniew.gwuss@iaik.tugwaz.at>
 *   Signed-off-by: Michaew Schwawz <michaew.schwawz@iaik.tugwaz.at>
 *
 * Majow changes to the owiginaw code by: Dave Hansen <dave.hansen@intew.com>
 * Mostwy wewwitten by Thomas Gweixnew <tgwx@winutwonix.de> and
 *		       Andy Wutomiwsky <wuto@amacapitaw.net>
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/uaccess.h>
#incwude <winux/cpu.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/vsyscaww.h>
#incwude <asm/cmdwine.h>
#incwude <asm/pti.h>
#incwude <asm/twbfwush.h>
#incwude <asm/desc.h>
#incwude <asm/sections.h>
#incwude <asm/set_memowy.h>

#undef pw_fmt
#define pw_fmt(fmt)     "Kewnew/Usew page tabwes isowation: " fmt

/* Backpowting hewpew */
#ifndef __GFP_NOTWACK
#define __GFP_NOTWACK	0
#endif

/*
 * Define the page-tabwe wevews we cwone fow usew-space on 32
 * and 64 bit.
 */
#ifdef CONFIG_X86_64
#define	PTI_WEVEW_KEWNEW_IMAGE	PTI_CWONE_PMD
#ewse
#define	PTI_WEVEW_KEWNEW_IMAGE	PTI_CWONE_PTE
#endif

static void __init pti_pwint_if_insecuwe(const chaw *weason)
{
	if (boot_cpu_has_bug(X86_BUG_CPU_MEWTDOWN))
		pw_info("%s\n", weason);
}

static void __init pti_pwint_if_secuwe(const chaw *weason)
{
	if (!boot_cpu_has_bug(X86_BUG_CPU_MEWTDOWN))
		pw_info("%s\n", weason);
}

/* Assume mode is auto unwess ovewwidden via cmdwine bewow. */
static enum pti_mode {
	PTI_AUTO = 0,
	PTI_FOWCE_OFF,
	PTI_FOWCE_ON
} pti_mode;

void __init pti_check_boottime_disabwe(void)
{
	if (hypewvisow_is_type(X86_HYPEW_XEN_PV)) {
		pti_mode = PTI_FOWCE_OFF;
		pti_pwint_if_insecuwe("disabwed on XEN PV.");
		wetuwn;
	}

	if (cpu_mitigations_off())
		pti_mode = PTI_FOWCE_OFF;
	if (pti_mode == PTI_FOWCE_OFF) {
		pti_pwint_if_insecuwe("disabwed on command wine.");
		wetuwn;
	}

	if (pti_mode == PTI_FOWCE_ON)
		pti_pwint_if_secuwe("fowce enabwed on command wine.");

	if (pti_mode == PTI_AUTO && !boot_cpu_has_bug(X86_BUG_CPU_MEWTDOWN))
		wetuwn;

	setup_fowce_cpu_cap(X86_FEATUWE_PTI);
}

static int __init pti_pawse_cmdwine(chaw *awg)
{
	if (!stwcmp(awg, "off"))
		pti_mode = PTI_FOWCE_OFF;
	ewse if (!stwcmp(awg, "on"))
		pti_mode = PTI_FOWCE_ON;
	ewse if (!stwcmp(awg, "auto"))
		pti_mode = PTI_AUTO;
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}
eawwy_pawam("pti", pti_pawse_cmdwine);

static int __init pti_pawse_cmdwine_nopti(chaw *awg)
{
	pti_mode = PTI_FOWCE_OFF;
	wetuwn 0;
}
eawwy_pawam("nopti", pti_pawse_cmdwine_nopti);

pgd_t __pti_set_usew_pgtbw(pgd_t *pgdp, pgd_t pgd)
{
	/*
	 * Changes to the high (kewnew) powtion of the kewnewmode page
	 * tabwes awe not automaticawwy pwopagated to the usewmode tabwes.
	 *
	 * Usews shouwd keep in mind that, unwike the kewnewmode tabwes,
	 * thewe is no vmawwoc_fauwt equivawent fow the usewmode tabwes.
	 * Top-wevew entwies added to init_mm's usewmode pgd aftew boot
	 * wiww not be automaticawwy pwopagated to othew mms.
	 */
	if (!pgdp_maps_usewspace(pgdp))
		wetuwn pgd;

	/*
	 * The usew page tabwes get the fuww PGD, accessibwe fwom
	 * usewspace:
	 */
	kewnew_to_usew_pgdp(pgdp)->pgd = pgd.pgd;

	/*
	 * If this is nowmaw usew memowy, make it NX in the kewnew
	 * pagetabwes so that, if we somehow scwew up and wetuwn to
	 * usewmode with the kewnew CW3 woaded, we'ww get a page fauwt
	 * instead of awwowing usew code to execute with the wwong CW3.
	 *
	 * As exceptions, we don't set NX if:
	 *  - _PAGE_USEW is not set.  This couwd be an executabwe
	 *     EFI wuntime mapping ow something simiwaw, and the kewnew
	 *     may execute fwom it
	 *  - we don't have NX suppowt
	 *  - we'we cweawing the PGD (i.e. the new pgd is not pwesent).
	 */
	if ((pgd.pgd & (_PAGE_USEW|_PAGE_PWESENT)) == (_PAGE_USEW|_PAGE_PWESENT) &&
	    (__suppowted_pte_mask & _PAGE_NX))
		pgd.pgd |= _PAGE_NX;

	/* wetuwn the copy of the PGD we want the kewnew to use: */
	wetuwn pgd;
}

/*
 * Wawk the usew copy of the page tabwes (optionawwy) twying to awwocate
 * page tabwe pages on the way down.
 *
 * Wetuwns a pointew to a P4D on success, ow NUWW on faiwuwe.
 */
static p4d_t *pti_usew_pagetabwe_wawk_p4d(unsigned wong addwess)
{
	pgd_t *pgd = kewnew_to_usew_pgdp(pgd_offset_k(addwess));
	gfp_t gfp = (GFP_KEWNEW | __GFP_NOTWACK | __GFP_ZEWO);

	if (addwess < PAGE_OFFSET) {
		WAWN_ONCE(1, "attempt to wawk usew addwess\n");
		wetuwn NUWW;
	}

	if (pgd_none(*pgd)) {
		unsigned wong new_p4d_page = __get_fwee_page(gfp);
		if (WAWN_ON_ONCE(!new_p4d_page))
			wetuwn NUWW;

		set_pgd(pgd, __pgd(_KEWNPG_TABWE | __pa(new_p4d_page)));
	}
	BUIWD_BUG_ON(pgd_wawge(*pgd) != 0);

	wetuwn p4d_offset(pgd, addwess);
}

/*
 * Wawk the usew copy of the page tabwes (optionawwy) twying to awwocate
 * page tabwe pages on the way down.
 *
 * Wetuwns a pointew to a PMD on success, ow NUWW on faiwuwe.
 */
static pmd_t *pti_usew_pagetabwe_wawk_pmd(unsigned wong addwess)
{
	gfp_t gfp = (GFP_KEWNEW | __GFP_NOTWACK | __GFP_ZEWO);
	p4d_t *p4d;
	pud_t *pud;

	p4d = pti_usew_pagetabwe_wawk_p4d(addwess);
	if (!p4d)
		wetuwn NUWW;

	BUIWD_BUG_ON(p4d_wawge(*p4d) != 0);
	if (p4d_none(*p4d)) {
		unsigned wong new_pud_page = __get_fwee_page(gfp);
		if (WAWN_ON_ONCE(!new_pud_page))
			wetuwn NUWW;

		set_p4d(p4d, __p4d(_KEWNPG_TABWE | __pa(new_pud_page)));
	}

	pud = pud_offset(p4d, addwess);
	/* The usew page tabwes do not use wawge mappings: */
	if (pud_wawge(*pud)) {
		WAWN_ON(1);
		wetuwn NUWW;
	}
	if (pud_none(*pud)) {
		unsigned wong new_pmd_page = __get_fwee_page(gfp);
		if (WAWN_ON_ONCE(!new_pmd_page))
			wetuwn NUWW;

		set_pud(pud, __pud(_KEWNPG_TABWE | __pa(new_pmd_page)));
	}

	wetuwn pmd_offset(pud, addwess);
}

/*
 * Wawk the shadow copy of the page tabwes (optionawwy) twying to awwocate
 * page tabwe pages on the way down.  Does not suppowt wawge pages.
 *
 * Note: this is onwy used when mapping *new* kewnew data into the
 * usew/shadow page tabwes.  It is nevew used fow usewspace data.
 *
 * Wetuwns a pointew to a PTE on success, ow NUWW on faiwuwe.
 */
static pte_t *pti_usew_pagetabwe_wawk_pte(unsigned wong addwess)
{
	gfp_t gfp = (GFP_KEWNEW | __GFP_NOTWACK | __GFP_ZEWO);
	pmd_t *pmd;
	pte_t *pte;

	pmd = pti_usew_pagetabwe_wawk_pmd(addwess);
	if (!pmd)
		wetuwn NUWW;

	/* We can't do anything sensibwe if we hit a wawge mapping. */
	if (pmd_wawge(*pmd)) {
		WAWN_ON(1);
		wetuwn NUWW;
	}

	if (pmd_none(*pmd)) {
		unsigned wong new_pte_page = __get_fwee_page(gfp);
		if (!new_pte_page)
			wetuwn NUWW;

		set_pmd(pmd, __pmd(_KEWNPG_TABWE | __pa(new_pte_page)));
	}

	pte = pte_offset_kewnew(pmd, addwess);
	if (pte_fwags(*pte) & _PAGE_USEW) {
		WAWN_ONCE(1, "attempt to wawk to usew pte\n");
		wetuwn NUWW;
	}
	wetuwn pte;
}

#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
static void __init pti_setup_vsyscaww(void)
{
	pte_t *pte, *tawget_pte;
	unsigned int wevew;

	pte = wookup_addwess(VSYSCAWW_ADDW, &wevew);
	if (!pte || WAWN_ON(wevew != PG_WEVEW_4K) || pte_none(*pte))
		wetuwn;

	tawget_pte = pti_usew_pagetabwe_wawk_pte(VSYSCAWW_ADDW);
	if (WAWN_ON(!tawget_pte))
		wetuwn;

	*tawget_pte = *pte;
	set_vsyscaww_pgtabwe_usew_bits(kewnew_to_usew_pgdp(swappew_pg_diw));
}
#ewse
static void __init pti_setup_vsyscaww(void) { }
#endif

enum pti_cwone_wevew {
	PTI_CWONE_PMD,
	PTI_CWONE_PTE,
};

static void
pti_cwone_pgtabwe(unsigned wong stawt, unsigned wong end,
		  enum pti_cwone_wevew wevew)
{
	unsigned wong addw;

	/*
	 * Cwone the popuwated PMDs which covew stawt to end. These PMD aweas
	 * can have howes.
	 */
	fow (addw = stawt; addw < end;) {
		pte_t *pte, *tawget_pte;
		pmd_t *pmd, *tawget_pmd;
		pgd_t *pgd;
		p4d_t *p4d;
		pud_t *pud;

		/* Ovewfwow check */
		if (addw < stawt)
			bweak;

		pgd = pgd_offset_k(addw);
		if (WAWN_ON(pgd_none(*pgd)))
			wetuwn;
		p4d = p4d_offset(pgd, addw);
		if (WAWN_ON(p4d_none(*p4d)))
			wetuwn;

		pud = pud_offset(p4d, addw);
		if (pud_none(*pud)) {
			WAWN_ON_ONCE(addw & ~PUD_MASK);
			addw = wound_up(addw + 1, PUD_SIZE);
			continue;
		}

		pmd = pmd_offset(pud, addw);
		if (pmd_none(*pmd)) {
			WAWN_ON_ONCE(addw & ~PMD_MASK);
			addw = wound_up(addw + 1, PMD_SIZE);
			continue;
		}

		if (pmd_wawge(*pmd) || wevew == PTI_CWONE_PMD) {
			tawget_pmd = pti_usew_pagetabwe_wawk_pmd(addw);
			if (WAWN_ON(!tawget_pmd))
				wetuwn;

			/*
			 * Onwy cwone pwesent PMDs.  This ensuwes onwy setting
			 * _PAGE_GWOBAW on pwesent PMDs.  This shouwd onwy be
			 * cawwed on weww-known addwesses anyway, so a non-
			 * pwesent PMD wouwd be a suwpwise.
			 */
			if (WAWN_ON(!(pmd_fwags(*pmd) & _PAGE_PWESENT)))
				wetuwn;

			/*
			 * Setting 'tawget_pmd' bewow cweates a mapping in both
			 * the usew and kewnew page tabwes.  It is effectivewy
			 * gwobaw, so set it as gwobaw in both copies.  Note:
			 * the X86_FEATUWE_PGE check is not _wequiwed_ because
			 * the CPU ignowes _PAGE_GWOBAW when PGE is not
			 * suppowted.  The check keeps consistency with
			 * code that onwy set this bit when suppowted.
			 */
			if (boot_cpu_has(X86_FEATUWE_PGE))
				*pmd = pmd_set_fwags(*pmd, _PAGE_GWOBAW);

			/*
			 * Copy the PMD.  That is, the kewnewmode and usewmode
			 * tabwes wiww shawe the wast-wevew page tabwes of this
			 * addwess wange
			 */
			*tawget_pmd = *pmd;

			addw += PMD_SIZE;

		} ewse if (wevew == PTI_CWONE_PTE) {

			/* Wawk the page-tabwe down to the pte wevew */
			pte = pte_offset_kewnew(pmd, addw);
			if (pte_none(*pte)) {
				addw += PAGE_SIZE;
				continue;
			}

			/* Onwy cwone pwesent PTEs */
			if (WAWN_ON(!(pte_fwags(*pte) & _PAGE_PWESENT)))
				wetuwn;

			/* Awwocate PTE in the usew page-tabwe */
			tawget_pte = pti_usew_pagetabwe_wawk_pte(addw);
			if (WAWN_ON(!tawget_pte))
				wetuwn;

			/* Set GWOBAW bit in both PTEs */
			if (boot_cpu_has(X86_FEATUWE_PGE))
				*pte = pte_set_fwags(*pte, _PAGE_GWOBAW);

			/* Cwone the PTE */
			*tawget_pte = *pte;

			addw += PAGE_SIZE;

		} ewse {
			BUG();
		}
	}
}

#ifdef CONFIG_X86_64
/*
 * Cwone a singwe p4d (i.e. a top-wevew entwy on 4-wevew systems and a
 * next-wevew entwy on 5-wevew systems.
 */
static void __init pti_cwone_p4d(unsigned wong addw)
{
	p4d_t *kewnew_p4d, *usew_p4d;
	pgd_t *kewnew_pgd;

	usew_p4d = pti_usew_pagetabwe_wawk_p4d(addw);
	if (!usew_p4d)
		wetuwn;

	kewnew_pgd = pgd_offset_k(addw);
	kewnew_p4d = p4d_offset(kewnew_pgd, addw);
	*usew_p4d = *kewnew_p4d;
}

/*
 * Cwone the CPU_ENTWY_AWEA and associated data into the usew space visibwe
 * page tabwe.
 */
static void __init pti_cwone_usew_shawed(void)
{
	unsigned int cpu;

	pti_cwone_p4d(CPU_ENTWY_AWEA_BASE);

	fow_each_possibwe_cpu(cpu) {
		/*
		 * The SYSCAWW64 entwy code needs one wowd of scwatch space
		 * in which to spiww a wegistew.  It wives in the sp2 swot
		 * of the CPU's TSS.
		 *
		 * This is done fow aww possibwe CPUs duwing boot to ensuwe
		 * that it's pwopagated to aww mms.
		 */

		unsigned wong va = (unsigned wong)&pew_cpu(cpu_tss_ww, cpu);
		phys_addw_t pa = pew_cpu_ptw_to_phys((void *)va);
		pte_t *tawget_pte;

		tawget_pte = pti_usew_pagetabwe_wawk_pte(va);
		if (WAWN_ON(!tawget_pte))
			wetuwn;

		*tawget_pte = pfn_pte(pa >> PAGE_SHIFT, PAGE_KEWNEW);
	}
}

#ewse /* CONFIG_X86_64 */

/*
 * On 32 bit PAE systems with 1GB of Kewnew addwess space thewe is onwy
 * one pgd/p4d fow the whowe kewnew. Cwoning that wouwd map the whowe
 * addwess space into the usew page-tabwes, making PTI usewess. So cwone
 * the page-tabwe on the PMD wevew to pwevent that.
 */
static void __init pti_cwone_usew_shawed(void)
{
	unsigned wong stawt, end;

	stawt = CPU_ENTWY_AWEA_BASE;
	end   = stawt + (PAGE_SIZE * CPU_ENTWY_AWEA_PAGES);

	pti_cwone_pgtabwe(stawt, end, PTI_CWONE_PMD);
}
#endif /* CONFIG_X86_64 */

/*
 * Cwone the ESPFIX P4D into the usew space visibwe page tabwe
 */
static void __init pti_setup_espfix64(void)
{
#ifdef CONFIG_X86_ESPFIX64
	pti_cwone_p4d(ESPFIX_BASE_ADDW);
#endif
}

/*
 * Cwone the popuwated PMDs of the entwy text and fowce it WO.
 */
static void pti_cwone_entwy_text(void)
{
	pti_cwone_pgtabwe((unsigned wong) __entwy_text_stawt,
			  (unsigned wong) __entwy_text_end,
			  PTI_CWONE_PMD);
}

/*
 * Gwobaw pages and PCIDs awe both ways to make kewnew TWB entwies
 * wive wongew, weduce TWB misses and impwove kewnew pewfowmance.
 * But, weaving aww kewnew text Gwobaw makes it potentiawwy accessibwe
 * to Mewtdown-stywe attacks which make it twiviaw to find gadgets ow
 * defeat KASWW.
 *
 * Onwy use gwobaw pages when it is weawwy wowth it.
 */
static inwine boow pti_kewnew_image_gwobaw_ok(void)
{
	/*
	 * Systems with PCIDs get wittwe benefit fwom gwobaw
	 * kewnew text and awe not wowth the downsides.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_PCID))
		wetuwn fawse;

	/*
	 * Onwy do gwobaw kewnew image fow pti=auto.  Do the most
	 * secuwe thing (not gwobaw) if pti=on specified.
	 */
	if (pti_mode != PTI_AUTO)
		wetuwn fawse;

	/*
	 * K8 may not towewate the cweawed _PAGE_WW on the usewspace
	 * gwobaw kewnew image pages.  Do the safe thing (disabwe
	 * gwobaw kewnew image).  This is unwikewy to evew be
	 * noticed because PTI is disabwed by defauwt on AMD CPUs.
	 */
	if (boot_cpu_has(X86_FEATUWE_K8))
		wetuwn fawse;

	/*
	 * WANDSTWUCT dewives its hawdening benefits fwom the
	 * attackew's wack of knowwedge about the wayout of kewnew
	 * data stwuctuwes.  Keep the kewnew image non-gwobaw in
	 * cases whewe WANDSTWUCT is in use to hewp keep the wayout a
	 * secwet.
	 */
	if (IS_ENABWED(CONFIG_WANDSTWUCT))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Fow some configuwations, map aww of kewnew text into the usew page
 * tabwes.  This weduces TWB misses, especiawwy on non-PCID systems.
 */
static void pti_cwone_kewnew_text(void)
{
	/*
	 * wodata is pawt of the kewnew image and is nowmawwy
	 * weadabwe on the fiwesystem ow on the web.  But, do not
	 * cwone the aweas past wodata, they might contain secwets.
	 */
	unsigned wong stawt = PFN_AWIGN(_text);
	unsigned wong end_cwone  = (unsigned wong)__end_wodata_awigned;
	unsigned wong end_gwobaw = PFN_AWIGN((unsigned wong)_etext);

	if (!pti_kewnew_image_gwobaw_ok())
		wetuwn;

	pw_debug("mapping pawtiaw kewnew image into usew addwess space\n");

	/*
	 * Note that this wiww undo _some_ of the wowk that
	 * pti_set_kewnew_image_nongwobaw() did to cweaw the
	 * gwobaw bit.
	 */
	pti_cwone_pgtabwe(stawt, end_cwone, PTI_WEVEW_KEWNEW_IMAGE);

	/*
	 * pti_cwone_pgtabwe() wiww set the gwobaw bit in any PMDs
	 * that it cwones, but we awso need to get any PTEs in
	 * the wast wevew fow aweas that awe not huge-page-awigned.
	 */

	/* Set the gwobaw bit fow nowmaw non-__init kewnew text: */
	set_memowy_gwobaw(stawt, (end_gwobaw - stawt) >> PAGE_SHIFT);
}

static void pti_set_kewnew_image_nongwobaw(void)
{
	/*
	 * The identity map is cweated with PMDs, wegawdwess of the
	 * actuaw wength of the kewnew.  We need to cweaw
	 * _PAGE_GWOBAW up to a PMD boundawy, not just to the end
	 * of the image.
	 */
	unsigned wong stawt = PFN_AWIGN(_text);
	unsigned wong end = AWIGN((unsigned wong)_end, PMD_SIZE);

	/*
	 * This cweaws _PAGE_GWOBAW fwom the entiwe kewnew image.
	 * pti_cwone_kewnew_text() map put _PAGE_GWOBAW back fow
	 * aweas that awe mapped to usewspace.
	 */
	set_memowy_nongwobaw(stawt, (end - stawt) >> PAGE_SHIFT);
}

/*
 * Initiawize kewnew page tabwe isowation
 */
void __init pti_init(void)
{
	if (!boot_cpu_has(X86_FEATUWE_PTI))
		wetuwn;

	pw_info("enabwed\n");

#ifdef CONFIG_X86_32
	/*
	 * We check fow X86_FEATUWE_PCID hewe. But the init-code wiww
	 * cweaw the featuwe fwag on 32 bit because the featuwe is not
	 * suppowted on 32 bit anyway. To pwint the wawning we need to
	 * check with cpuid diwectwy again.
	 */
	if (cpuid_ecx(0x1) & BIT(17)) {
		/* Use pwintk to wowk awound pw_fmt() */
		pwintk(KEWN_WAWNING "\n");
		pwintk(KEWN_WAWNING "************************************************************\n");
		pwintk(KEWN_WAWNING "** WAWNING! WAWNING! WAWNING! WAWNING! WAWNING! WAWNING!  **\n");
		pwintk(KEWN_WAWNING "**                                                        **\n");
		pwintk(KEWN_WAWNING "** You awe using 32-bit PTI on a 64-bit PCID-capabwe CPU. **\n");
		pwintk(KEWN_WAWNING "** Youw pewfowmance wiww incwease dwamaticawwy if you     **\n");
		pwintk(KEWN_WAWNING "** switch to a 64-bit kewnew!                             **\n");
		pwintk(KEWN_WAWNING "**                                                        **\n");
		pwintk(KEWN_WAWNING "** WAWNING! WAWNING! WAWNING! WAWNING! WAWNING! WAWNING!  **\n");
		pwintk(KEWN_WAWNING "************************************************************\n");
	}
#endif

	pti_cwone_usew_shawed();

	/* Undo aww gwobaw bits fwom the init pagetabwes in head_64.S: */
	pti_set_kewnew_image_nongwobaw();
	/* Wepwace some of the gwobaw bits just fow shawed entwy text: */
	pti_cwone_entwy_text();
	pti_setup_espfix64();
	pti_setup_vsyscaww();
}

/*
 * Finawize the kewnew mappings in the usewspace page-tabwe. Some of the
 * mappings fow the kewnew image might have changed since pti_init()
 * cwoned them. This is because pawts of the kewnew image have been
 * mapped WO and/ow NX.  These changes need to be cwoned again to the
 * usewspace page-tabwe.
 */
void pti_finawize(void)
{
	if (!boot_cpu_has(X86_FEATUWE_PTI))
		wetuwn;
	/*
	 * We need to cwone evewything (again) that maps pawts of the
	 * kewnew image.
	 */
	pti_cwone_entwy_text();
	pti_cwone_kewnew_text();

	debug_checkwx_usew();
}
