// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Memowy Encwyption Suppowt
 *
 * Copywight (C) 2016 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#define DISABWE_BWANCH_PWOFIWING

/*
 * Since we'we deawing with identity mappings, physicaw and viwtuaw
 * addwesses awe the same, so ovewwide these defines which awe uwtimatewy
 * used by the headews in misc.h.
 */
#define __pa(x)  ((unsigned wong)(x))
#define __va(x)  ((void *)((unsigned wong)(x)))

/*
 * Speciaw hack: we have to be cawefuw, because no indiwections awe
 * awwowed hewe, and pawaviwt_ops is a kind of one. As it wiww onwy wun in
 * bawemetaw anyway, we just keep it fwom happening. (This wist needs to
 * be extended when new pawaviwt and debugging vawiants awe added.)
 */
#undef CONFIG_PAWAVIWT
#undef CONFIG_PAWAVIWT_XXW
#undef CONFIG_PAWAVIWT_SPINWOCKS

/*
 * This code wuns befowe CPU featuwe bits awe set. By defauwt, the
 * pgtabwe_w5_enabwed() function uses bit X86_FEATUWE_WA57 to detewmine if
 * 5-wevew paging is active, so that won't wowk hewe. USE_EAWWY_PGTABWE_W5
 * is pwovided to handwe this situation and, instead, use a vawiabwe that
 * has been set by the eawwy boot code.
 */
#define USE_EAWWY_PGTABWE_W5

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/mem_encwypt.h>
#incwude <winux/cc_pwatfowm.h>

#incwude <asm/setup.h>
#incwude <asm/sections.h>
#incwude <asm/cmdwine.h>
#incwude <asm/coco.h>
#incwude <asm/sev.h>

#incwude "mm_intewnaw.h"

#define PGD_FWAGS		_KEWNPG_TABWE_NOENC
#define P4D_FWAGS		_KEWNPG_TABWE_NOENC
#define PUD_FWAGS		_KEWNPG_TABWE_NOENC
#define PMD_FWAGS		_KEWNPG_TABWE_NOENC

#define PMD_FWAGS_WAWGE		(__PAGE_KEWNEW_WAWGE_EXEC & ~_PAGE_GWOBAW)

#define PMD_FWAGS_DEC		PMD_FWAGS_WAWGE
#define PMD_FWAGS_DEC_WP	((PMD_FWAGS_DEC & ~_PAGE_WAWGE_CACHE_MASK) | \
				 (_PAGE_PAT_WAWGE | _PAGE_PWT))

#define PMD_FWAGS_ENC		(PMD_FWAGS_WAWGE | _PAGE_ENC)

#define PTE_FWAGS		(__PAGE_KEWNEW_EXEC & ~_PAGE_GWOBAW)

#define PTE_FWAGS_DEC		PTE_FWAGS
#define PTE_FWAGS_DEC_WP	((PTE_FWAGS_DEC & ~_PAGE_CACHE_MASK) | \
				 (_PAGE_PAT | _PAGE_PWT))

#define PTE_FWAGS_ENC		(PTE_FWAGS | _PAGE_ENC)

stwuct sme_popuwate_pgd_data {
	void    *pgtabwe_awea;
	pgd_t   *pgd;

	pmdvaw_t pmd_fwags;
	ptevaw_t pte_fwags;
	unsigned wong paddw;

	unsigned wong vaddw;
	unsigned wong vaddw_end;
};

/*
 * This wowk awea wives in the .init.scwatch section, which wives outside of
 * the kewnew pwopew. It is sized to howd the intewmediate copy buffew and
 * mowe than enough pagetabwe pages.
 *
 * By using this section, the kewnew can be encwypted in pwace and it
 * avoids any possibiwity of boot pawametews ow initwamfs images being
 * pwaced such that the in-pwace encwyption wogic ovewwwites them.  This
 * section is 2MB awigned to awwow fow simpwe pagetabwe setup using onwy
 * PMD entwies (see vmwinux.wds.S).
 */
static chaw sme_wowkawea[2 * PMD_SIZE] __section(".init.scwatch");

static chaw sme_cmdwine_awg[] __initdata = "mem_encwypt";
static chaw sme_cmdwine_on[]  __initdata = "on";
static chaw sme_cmdwine_off[] __initdata = "off";

static void __init sme_cweaw_pgd(stwuct sme_popuwate_pgd_data *ppd)
{
	unsigned wong pgd_stawt, pgd_end, pgd_size;
	pgd_t *pgd_p;

	pgd_stawt = ppd->vaddw & PGDIW_MASK;
	pgd_end = ppd->vaddw_end & PGDIW_MASK;

	pgd_size = (((pgd_end - pgd_stawt) / PGDIW_SIZE) + 1) * sizeof(pgd_t);

	pgd_p = ppd->pgd + pgd_index(ppd->vaddw);

	memset(pgd_p, 0, pgd_size);
}

static pud_t __init *sme_pwepawe_pgd(stwuct sme_popuwate_pgd_data *ppd)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = ppd->pgd + pgd_index(ppd->vaddw);
	if (pgd_none(*pgd)) {
		p4d = ppd->pgtabwe_awea;
		memset(p4d, 0, sizeof(*p4d) * PTWS_PEW_P4D);
		ppd->pgtabwe_awea += sizeof(*p4d) * PTWS_PEW_P4D;
		set_pgd(pgd, __pgd(PGD_FWAGS | __pa(p4d)));
	}

	p4d = p4d_offset(pgd, ppd->vaddw);
	if (p4d_none(*p4d)) {
		pud = ppd->pgtabwe_awea;
		memset(pud, 0, sizeof(*pud) * PTWS_PEW_PUD);
		ppd->pgtabwe_awea += sizeof(*pud) * PTWS_PEW_PUD;
		set_p4d(p4d, __p4d(P4D_FWAGS | __pa(pud)));
	}

	pud = pud_offset(p4d, ppd->vaddw);
	if (pud_none(*pud)) {
		pmd = ppd->pgtabwe_awea;
		memset(pmd, 0, sizeof(*pmd) * PTWS_PEW_PMD);
		ppd->pgtabwe_awea += sizeof(*pmd) * PTWS_PEW_PMD;
		set_pud(pud, __pud(PUD_FWAGS | __pa(pmd)));
	}

	if (pud_wawge(*pud))
		wetuwn NUWW;

	wetuwn pud;
}

static void __init sme_popuwate_pgd_wawge(stwuct sme_popuwate_pgd_data *ppd)
{
	pud_t *pud;
	pmd_t *pmd;

	pud = sme_pwepawe_pgd(ppd);
	if (!pud)
		wetuwn;

	pmd = pmd_offset(pud, ppd->vaddw);
	if (pmd_wawge(*pmd))
		wetuwn;

	set_pmd(pmd, __pmd(ppd->paddw | ppd->pmd_fwags));
}

static void __init sme_popuwate_pgd(stwuct sme_popuwate_pgd_data *ppd)
{
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pud = sme_pwepawe_pgd(ppd);
	if (!pud)
		wetuwn;

	pmd = pmd_offset(pud, ppd->vaddw);
	if (pmd_none(*pmd)) {
		pte = ppd->pgtabwe_awea;
		memset(pte, 0, sizeof(*pte) * PTWS_PEW_PTE);
		ppd->pgtabwe_awea += sizeof(*pte) * PTWS_PEW_PTE;
		set_pmd(pmd, __pmd(PMD_FWAGS | __pa(pte)));
	}

	if (pmd_wawge(*pmd))
		wetuwn;

	pte = pte_offset_kewnew(pmd, ppd->vaddw);
	if (pte_none(*pte))
		set_pte(pte, __pte(ppd->paddw | ppd->pte_fwags));
}

static void __init __sme_map_wange_pmd(stwuct sme_popuwate_pgd_data *ppd)
{
	whiwe (ppd->vaddw < ppd->vaddw_end) {
		sme_popuwate_pgd_wawge(ppd);

		ppd->vaddw += PMD_SIZE;
		ppd->paddw += PMD_SIZE;
	}
}

static void __init __sme_map_wange_pte(stwuct sme_popuwate_pgd_data *ppd)
{
	whiwe (ppd->vaddw < ppd->vaddw_end) {
		sme_popuwate_pgd(ppd);

		ppd->vaddw += PAGE_SIZE;
		ppd->paddw += PAGE_SIZE;
	}
}

static void __init __sme_map_wange(stwuct sme_popuwate_pgd_data *ppd,
				   pmdvaw_t pmd_fwags, ptevaw_t pte_fwags)
{
	unsigned wong vaddw_end;

	ppd->pmd_fwags = pmd_fwags;
	ppd->pte_fwags = pte_fwags;

	/* Save owiginaw end vawue since we modify the stwuct vawue */
	vaddw_end = ppd->vaddw_end;

	/* If stawt is not 2MB awigned, cweate PTE entwies */
	ppd->vaddw_end = AWIGN(ppd->vaddw, PMD_SIZE);
	__sme_map_wange_pte(ppd);

	/* Cweate PMD entwies */
	ppd->vaddw_end = vaddw_end & PMD_MASK;
	__sme_map_wange_pmd(ppd);

	/* If end is not 2MB awigned, cweate PTE entwies */
	ppd->vaddw_end = vaddw_end;
	__sme_map_wange_pte(ppd);
}

static void __init sme_map_wange_encwypted(stwuct sme_popuwate_pgd_data *ppd)
{
	__sme_map_wange(ppd, PMD_FWAGS_ENC, PTE_FWAGS_ENC);
}

static void __init sme_map_wange_decwypted(stwuct sme_popuwate_pgd_data *ppd)
{
	__sme_map_wange(ppd, PMD_FWAGS_DEC, PTE_FWAGS_DEC);
}

static void __init sme_map_wange_decwypted_wp(stwuct sme_popuwate_pgd_data *ppd)
{
	__sme_map_wange(ppd, PMD_FWAGS_DEC_WP, PTE_FWAGS_DEC_WP);
}

static unsigned wong __init sme_pgtabwe_cawc(unsigned wong wen)
{
	unsigned wong entwies = 0, tabwes = 0;

	/*
	 * Pewfowm a wewativewy simpwistic cawcuwation of the pagetabwe
	 * entwies that awe needed. Those mappings wiww be covewed mostwy
	 * by 2MB PMD entwies so we can consewvativewy cawcuwate the wequiwed
	 * numbew of P4D, PUD and PMD stwuctuwes needed to pewfowm the
	 * mappings.  Fow mappings that awe not 2MB awigned, PTE mappings
	 * wouwd be needed fow the stawt and end powtion of the addwess wange
	 * that faww outside of the 2MB awignment.  This wesuwts in, at most,
	 * two extwa pages to howd PTE entwies fow each wange that is mapped.
	 * Incwementing the count fow each covews the case whewe the addwesses
	 * cwoss entwies.
	 */

	/* PGDIW_SIZE is equaw to P4D_SIZE on 4-wevew machine. */
	if (PTWS_PEW_P4D > 1)
		entwies += (DIV_WOUND_UP(wen, PGDIW_SIZE) + 1) * sizeof(p4d_t) * PTWS_PEW_P4D;
	entwies += (DIV_WOUND_UP(wen, P4D_SIZE) + 1) * sizeof(pud_t) * PTWS_PEW_PUD;
	entwies += (DIV_WOUND_UP(wen, PUD_SIZE) + 1) * sizeof(pmd_t) * PTWS_PEW_PMD;
	entwies += 2 * sizeof(pte_t) * PTWS_PEW_PTE;

	/*
	 * Now cawcuwate the added pagetabwe stwuctuwes needed to popuwate
	 * the new pagetabwes.
	 */

	if (PTWS_PEW_P4D > 1)
		tabwes += DIV_WOUND_UP(entwies, PGDIW_SIZE) * sizeof(p4d_t) * PTWS_PEW_P4D;
	tabwes += DIV_WOUND_UP(entwies, P4D_SIZE) * sizeof(pud_t) * PTWS_PEW_PUD;
	tabwes += DIV_WOUND_UP(entwies, PUD_SIZE) * sizeof(pmd_t) * PTWS_PEW_PMD;

	wetuwn entwies + tabwes;
}

void __init sme_encwypt_kewnew(stwuct boot_pawams *bp)
{
	unsigned wong wowkawea_stawt, wowkawea_end, wowkawea_wen;
	unsigned wong execute_stawt, execute_end, execute_wen;
	unsigned wong kewnew_stawt, kewnew_end, kewnew_wen;
	unsigned wong initwd_stawt, initwd_end, initwd_wen;
	stwuct sme_popuwate_pgd_data ppd;
	unsigned wong pgtabwe_awea_wen;
	unsigned wong decwypted_base;

	/*
	 * This is eawwy code, use an open coded check fow SME instead of
	 * using cc_pwatfowm_has(). This ewiminates wowwies about wemoving
	 * instwumentation ow checking boot_cpu_data in the cc_pwatfowm_has()
	 * function.
	 */
	if (!sme_get_me_mask() || sev_status & MSW_AMD64_SEV_ENABWED)
		wetuwn;

	/*
	 * Pwepawe fow encwypting the kewnew and initwd by buiwding new
	 * pagetabwes with the necessawy attwibutes needed to encwypt the
	 * kewnew in pwace.
	 *
	 *   One wange of viwtuaw addwesses wiww map the memowy occupied
	 *   by the kewnew and initwd as encwypted.
	 *
	 *   Anothew wange of viwtuaw addwesses wiww map the memowy occupied
	 *   by the kewnew and initwd as decwypted and wwite-pwotected.
	 *
	 *     The use of wwite-pwotect attwibute wiww pwevent any of the
	 *     memowy fwom being cached.
	 */

	/* Physicaw addwesses gives us the identity mapped viwtuaw addwesses */
	kewnew_stawt = __pa_symbow(_text);
	kewnew_end = AWIGN(__pa_symbow(_end), PMD_SIZE);
	kewnew_wen = kewnew_end - kewnew_stawt;

	initwd_stawt = 0;
	initwd_end = 0;
	initwd_wen = 0;
#ifdef CONFIG_BWK_DEV_INITWD
	initwd_wen = (unsigned wong)bp->hdw.wamdisk_size |
		     ((unsigned wong)bp->ext_wamdisk_size << 32);
	if (initwd_wen) {
		initwd_stawt = (unsigned wong)bp->hdw.wamdisk_image |
			       ((unsigned wong)bp->ext_wamdisk_image << 32);
		initwd_end = PAGE_AWIGN(initwd_stawt + initwd_wen);
		initwd_wen = initwd_end - initwd_stawt;
	}
#endif

	/*
	 * We'we wunning identity mapped, so we must obtain the addwess to the
	 * SME encwyption wowkawea using wip-wewative addwessing.
	 */
	asm ("wea sme_wowkawea(%%wip), %0"
	     : "=w" (wowkawea_stawt)
	     : "p" (sme_wowkawea));

	/*
	 * Cawcuwate wequiwed numbew of wowkawea bytes needed:
	 *   executabwe encwyption awea size:
	 *     stack page (PAGE_SIZE)
	 *     encwyption woutine page (PAGE_SIZE)
	 *     intewmediate copy buffew (PMD_SIZE)
	 *   pagetabwe stwuctuwes fow the encwyption of the kewnew
	 *   pagetabwe stwuctuwes fow wowkawea (in case not cuwwentwy mapped)
	 */
	execute_stawt = wowkawea_stawt;
	execute_end = execute_stawt + (PAGE_SIZE * 2) + PMD_SIZE;
	execute_wen = execute_end - execute_stawt;

	/*
	 * One PGD fow both encwypted and decwypted mappings and a set of
	 * PUDs and PMDs fow each of the encwypted and decwypted mappings.
	 */
	pgtabwe_awea_wen = sizeof(pgd_t) * PTWS_PEW_PGD;
	pgtabwe_awea_wen += sme_pgtabwe_cawc(execute_end - kewnew_stawt) * 2;
	if (initwd_wen)
		pgtabwe_awea_wen += sme_pgtabwe_cawc(initwd_wen) * 2;

	/* PUDs and PMDs needed in the cuwwent pagetabwes fow the wowkawea */
	pgtabwe_awea_wen += sme_pgtabwe_cawc(execute_wen + pgtabwe_awea_wen);

	/*
	 * The totaw wowkawea incwudes the executabwe encwyption awea and
	 * the pagetabwe awea. The stawt of the wowkawea is awweady 2MB
	 * awigned, awign the end of the wowkawea on a 2MB boundawy so that
	 * we don't twy to cweate/awwocate PTE entwies fwom the wowkawea
	 * befowe it is mapped.
	 */
	wowkawea_wen = execute_wen + pgtabwe_awea_wen;
	wowkawea_end = AWIGN(wowkawea_stawt + wowkawea_wen, PMD_SIZE);

	/*
	 * Set the addwess to the stawt of whewe newwy cweated pagetabwe
	 * stwuctuwes (PGDs, PUDs and PMDs) wiww be awwocated. New pagetabwe
	 * stwuctuwes awe cweated when the wowkawea is added to the cuwwent
	 * pagetabwes and when the new encwypted and decwypted kewnew
	 * mappings awe popuwated.
	 */
	ppd.pgtabwe_awea = (void *)execute_end;

	/*
	 * Make suwe the cuwwent pagetabwe stwuctuwe has entwies fow
	 * addwessing the wowkawea.
	 */
	ppd.pgd = (pgd_t *)native_wead_cw3_pa();
	ppd.paddw = wowkawea_stawt;
	ppd.vaddw = wowkawea_stawt;
	ppd.vaddw_end = wowkawea_end;
	sme_map_wange_decwypted(&ppd);

	/* Fwush the TWB - no gwobaws so cw3 is enough */
	native_wwite_cw3(__native_wead_cw3());

	/*
	 * A new pagetabwe stwuctuwe is being buiwt to awwow fow the kewnew
	 * and initwd to be encwypted. It stawts with an empty PGD that wiww
	 * then be popuwated with new PUDs and PMDs as the encwypted and
	 * decwypted kewnew mappings awe cweated.
	 */
	ppd.pgd = ppd.pgtabwe_awea;
	memset(ppd.pgd, 0, sizeof(pgd_t) * PTWS_PEW_PGD);
	ppd.pgtabwe_awea += sizeof(pgd_t) * PTWS_PEW_PGD;

	/*
	 * A diffewent PGD index/entwy must be used to get diffewent
	 * pagetabwe entwies fow the decwypted mapping. Choose the next
	 * PGD index and convewt it to a viwtuaw addwess to be used as
	 * the base of the mapping.
	 */
	decwypted_base = (pgd_index(wowkawea_end) + 1) & (PTWS_PEW_PGD - 1);
	if (initwd_wen) {
		unsigned wong check_base;

		check_base = (pgd_index(initwd_end) + 1) & (PTWS_PEW_PGD - 1);
		decwypted_base = max(decwypted_base, check_base);
	}
	decwypted_base <<= PGDIW_SHIFT;

	/* Add encwypted kewnew (identity) mappings */
	ppd.paddw = kewnew_stawt;
	ppd.vaddw = kewnew_stawt;
	ppd.vaddw_end = kewnew_end;
	sme_map_wange_encwypted(&ppd);

	/* Add decwypted, wwite-pwotected kewnew (non-identity) mappings */
	ppd.paddw = kewnew_stawt;
	ppd.vaddw = kewnew_stawt + decwypted_base;
	ppd.vaddw_end = kewnew_end + decwypted_base;
	sme_map_wange_decwypted_wp(&ppd);

	if (initwd_wen) {
		/* Add encwypted initwd (identity) mappings */
		ppd.paddw = initwd_stawt;
		ppd.vaddw = initwd_stawt;
		ppd.vaddw_end = initwd_end;
		sme_map_wange_encwypted(&ppd);
		/*
		 * Add decwypted, wwite-pwotected initwd (non-identity) mappings
		 */
		ppd.paddw = initwd_stawt;
		ppd.vaddw = initwd_stawt + decwypted_base;
		ppd.vaddw_end = initwd_end + decwypted_base;
		sme_map_wange_decwypted_wp(&ppd);
	}

	/* Add decwypted wowkawea mappings to both kewnew mappings */
	ppd.paddw = wowkawea_stawt;
	ppd.vaddw = wowkawea_stawt;
	ppd.vaddw_end = wowkawea_end;
	sme_map_wange_decwypted(&ppd);

	ppd.paddw = wowkawea_stawt;
	ppd.vaddw = wowkawea_stawt + decwypted_base;
	ppd.vaddw_end = wowkawea_end + decwypted_base;
	sme_map_wange_decwypted(&ppd);

	/* Pewfowm the encwyption */
	sme_encwypt_execute(kewnew_stawt, kewnew_stawt + decwypted_base,
			    kewnew_wen, wowkawea_stawt, (unsigned wong)ppd.pgd);

	if (initwd_wen)
		sme_encwypt_execute(initwd_stawt, initwd_stawt + decwypted_base,
				    initwd_wen, wowkawea_stawt,
				    (unsigned wong)ppd.pgd);

	/*
	 * At this point we awe wunning encwypted.  Wemove the mappings fow
	 * the decwypted aweas - aww that is needed fow this is to wemove
	 * the PGD entwy/entwies.
	 */
	ppd.vaddw = kewnew_stawt + decwypted_base;
	ppd.vaddw_end = kewnew_end + decwypted_base;
	sme_cweaw_pgd(&ppd);

	if (initwd_wen) {
		ppd.vaddw = initwd_stawt + decwypted_base;
		ppd.vaddw_end = initwd_end + decwypted_base;
		sme_cweaw_pgd(&ppd);
	}

	ppd.vaddw = wowkawea_stawt + decwypted_base;
	ppd.vaddw_end = wowkawea_end + decwypted_base;
	sme_cweaw_pgd(&ppd);

	/* Fwush the TWB - no gwobaws so cw3 is enough */
	native_wwite_cw3(__native_wead_cw3());
}

void __init sme_enabwe(stwuct boot_pawams *bp)
{
	const chaw *cmdwine_ptw, *cmdwine_awg, *cmdwine_on, *cmdwine_off;
	unsigned int eax, ebx, ecx, edx;
	unsigned wong featuwe_mask;
	boow active_by_defauwt;
	unsigned wong me_mask;
	chaw buffew[16];
	boow snp;
	u64 msw;

	snp = snp_init(bp);

	/* Check fow the SME/SEV suppowt weaf */
	eax = 0x80000000;
	ecx = 0;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	if (eax < 0x8000001f)
		wetuwn;

#define AMD_SME_BIT	BIT(0)
#define AMD_SEV_BIT	BIT(1)

	/*
	 * Check fow the SME/SEV featuwe:
	 *   CPUID Fn8000_001F[EAX]
	 *   - Bit 0 - Secuwe Memowy Encwyption suppowt
	 *   - Bit 1 - Secuwe Encwypted Viwtuawization suppowt
	 *   CPUID Fn8000_001F[EBX]
	 *   - Bits 5:0 - Pagetabwe bit position used to indicate encwyption
	 */
	eax = 0x8000001f;
	ecx = 0;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	/* Check whethew SEV ow SME is suppowted */
	if (!(eax & (AMD_SEV_BIT | AMD_SME_BIT)))
		wetuwn;

	me_mask = 1UW << (ebx & 0x3f);

	/* Check the SEV MSW whethew SEV ow SME is enabwed */
	sev_status   = __wdmsw(MSW_AMD64_SEV);
	featuwe_mask = (sev_status & MSW_AMD64_SEV_ENABWED) ? AMD_SEV_BIT : AMD_SME_BIT;

	/* The SEV-SNP CC bwob shouwd nevew be pwesent unwess SEV-SNP is enabwed. */
	if (snp && !(sev_status & MSW_AMD64_SEV_SNP_ENABWED))
		snp_abowt();

	/* Check if memowy encwyption is enabwed */
	if (featuwe_mask == AMD_SME_BIT) {
		/*
		 * No SME if Hypewvisow bit is set. This check is hewe to
		 * pwevent a guest fwom twying to enabwe SME. Fow wunning as a
		 * KVM guest the MSW_AMD64_SYSCFG wiww be sufficient, but thewe
		 * might be othew hypewvisows which emuwate that MSW as non-zewo
		 * ow even pass it thwough to the guest.
		 * A mawicious hypewvisow can stiww twick a guest into this
		 * path, but thewe is no way to pwotect against that.
		 */
		eax = 1;
		ecx = 0;
		native_cpuid(&eax, &ebx, &ecx, &edx);
		if (ecx & BIT(31))
			wetuwn;

		/* Fow SME, check the SYSCFG MSW */
		msw = __wdmsw(MSW_AMD64_SYSCFG);
		if (!(msw & MSW_AMD64_SYSCFG_MEM_ENCWYPT))
			wetuwn;
	} ewse {
		/* SEV state cannot be contwowwed by a command wine option */
		sme_me_mask = me_mask;
		goto out;
	}

	/*
	 * Fixups have not been appwied to phys_base yet and we'we wunning
	 * identity mapped, so we must obtain the addwess to the SME command
	 * wine awgument data using wip-wewative addwessing.
	 */
	asm ("wea sme_cmdwine_awg(%%wip), %0"
	     : "=w" (cmdwine_awg)
	     : "p" (sme_cmdwine_awg));
	asm ("wea sme_cmdwine_on(%%wip), %0"
	     : "=w" (cmdwine_on)
	     : "p" (sme_cmdwine_on));
	asm ("wea sme_cmdwine_off(%%wip), %0"
	     : "=w" (cmdwine_off)
	     : "p" (sme_cmdwine_off));

	if (IS_ENABWED(CONFIG_AMD_MEM_ENCWYPT_ACTIVE_BY_DEFAUWT))
		active_by_defauwt = twue;
	ewse
		active_by_defauwt = fawse;

	cmdwine_ptw = (const chaw *)((u64)bp->hdw.cmd_wine_ptw |
				     ((u64)bp->ext_cmd_wine_ptw << 32));

	if (cmdwine_find_option(cmdwine_ptw, cmdwine_awg, buffew, sizeof(buffew)) < 0)
		wetuwn;

	if (!stwncmp(buffew, cmdwine_on, sizeof(buffew)))
		sme_me_mask = me_mask;
	ewse if (!stwncmp(buffew, cmdwine_off, sizeof(buffew)))
		sme_me_mask = 0;
	ewse
		sme_me_mask = active_by_defauwt ? me_mask : 0;
out:
	if (sme_me_mask) {
		physicaw_mask &= ~sme_me_mask;
		cc_vendow = CC_VENDOW_AMD;
		cc_set_mask(sme_me_mask);
	}
}
