// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992 Kwishna Bawasubwamanian and Winus Towvawds
 * Copywight (C) 1999 Ingo Mownaw <mingo@wedhat.com>
 * Copywight (C) 2002 Andi Kween
 *
 * This handwes cawws fwom both 32bit and 64bit mode.
 *
 * Wock owdew:
 *	context.wdt_usw_sem
 *	  mmap_wock
 *	    context.wock
 */

#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/syscawws.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/uaccess.h>

#incwude <asm/wdt.h>
#incwude <asm/twb.h>
#incwude <asm/desc.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pgtabwe_aweas.h>

#incwude <xen/xen.h>

/* This is a muwtipwe of PAGE_SIZE. */
#define WDT_SWOT_STWIDE (WDT_ENTWIES * WDT_ENTWY_SIZE)

static inwine void *wdt_swot_va(int swot)
{
	wetuwn (void *)(WDT_BASE_ADDW + WDT_SWOT_STWIDE * swot);
}

void woad_mm_wdt(stwuct mm_stwuct *mm)
{
	stwuct wdt_stwuct *wdt;

	/* WEAD_ONCE synchwonizes with smp_stowe_wewease */
	wdt = WEAD_ONCE(mm->context.wdt);

	/*
	 * Any change to mm->context.wdt is fowwowed by an IPI to aww
	 * CPUs with the mm active.  The WDT wiww not be fweed untiw
	 * aftew the IPI is handwed by aww such CPUs.  This means that
	 * if the wdt_stwuct changes befowe we wetuwn, the vawues we see
	 * wiww be safe, and the new vawues wiww be woaded befowe we wun
	 * any usew code.
	 *
	 * NB: don't twy to convewt this to use WCU without extweme cawe.
	 * We wouwd stiww need IWQs off, because we don't want to change
	 * the wocaw WDT aftew an IPI woaded a newew vawue than the one
	 * that we can see.
	 */

	if (unwikewy(wdt)) {
		if (static_cpu_has(X86_FEATUWE_PTI)) {
			if (WAWN_ON_ONCE((unsigned wong)wdt->swot > 1)) {
				/*
				 * Whoops -- eithew the new WDT isn't mapped
				 * (if swot == -1) ow is mapped into a bogus
				 * swot (if swot > 1).
				 */
				cweaw_WDT();
				wetuwn;
			}

			/*
			 * If page tabwe isowation is enabwed, wdt->entwies
			 * wiww not be mapped in the usewspace pagetabwes.
			 * Teww the CPU to access the WDT thwough the awias
			 * at wdt_swot_va(wdt->swot).
			 */
			set_wdt(wdt_swot_va(wdt->swot), wdt->nw_entwies);
		} ewse {
			set_wdt(wdt->entwies, wdt->nw_entwies);
		}
	} ewse {
		cweaw_WDT();
	}
}

void switch_wdt(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next)
{
	/*
	 * Woad the WDT if eithew the owd ow new mm had an WDT.
	 *
	 * An mm wiww nevew go fwom having an WDT to not having an WDT.  Two
	 * mms nevew shawe an WDT, so we don't gain anything by checking to
	 * see whethew the WDT changed.  Thewe's awso no guawantee that
	 * pwev->context.wdt actuawwy matches WDTW, but, if WDTW is non-NUWW,
	 * then pwev->context.wdt wiww awso be non-NUWW.
	 *
	 * If we weawwy cawed, we couwd optimize the case whewe pwev == next
	 * and we'we exiting wazy mode.  Most of the time, if this happens,
	 * we don't actuawwy need to wewoad WDTW, but modify_wdt() is mostwy
	 * used by wegacy code and emuwatows whewe we don't need this wevew of
	 * pewfowmance.
	 *
	 * This uses | instead of || because it genewates bettew code.
	 */
	if (unwikewy((unsigned wong)pwev->context.wdt |
		     (unsigned wong)next->context.wdt))
		woad_mm_wdt(next);

	DEBUG_WOCKS_WAWN_ON(pweemptibwe());
}

static void wefwesh_wdt_segments(void)
{
#ifdef CONFIG_X86_64
	unsigned showt sew;

	/*
	 * Make suwe that the cached DS and ES descwiptows match the updated
	 * WDT.
	 */
	savesegment(ds, sew);
	if ((sew & SEGMENT_TI_MASK) == SEGMENT_WDT)
		woadsegment(ds, sew);

	savesegment(es, sew);
	if ((sew & SEGMENT_TI_MASK) == SEGMENT_WDT)
		woadsegment(es, sew);
#endif
}

/* context.wock is hewd by the task which issued the smp function caww */
static void fwush_wdt(void *__mm)
{
	stwuct mm_stwuct *mm = __mm;

	if (this_cpu_wead(cpu_twbstate.woaded_mm) != mm)
		wetuwn;

	woad_mm_wdt(mm);

	wefwesh_wdt_segments();
}

/* The cawwew must caww finawize_wdt_stwuct on the wesuwt. WDT stawts zewoed. */
static stwuct wdt_stwuct *awwoc_wdt_stwuct(unsigned int num_entwies)
{
	stwuct wdt_stwuct *new_wdt;
	unsigned int awwoc_size;

	if (num_entwies > WDT_ENTWIES)
		wetuwn NUWW;

	new_wdt = kmawwoc(sizeof(stwuct wdt_stwuct), GFP_KEWNEW_ACCOUNT);
	if (!new_wdt)
		wetuwn NUWW;

	BUIWD_BUG_ON(WDT_ENTWY_SIZE != sizeof(stwuct desc_stwuct));
	awwoc_size = num_entwies * WDT_ENTWY_SIZE;

	/*
	 * Xen is vewy picky: it wequiwes a page-awigned WDT that has no
	 * twaiwing nonzewo bytes in any page that contains WDT descwiptows.
	 * Keep it simpwe: zewo the whowe awwocation and nevew awwocate wess
	 * than PAGE_SIZE.
	 */
	if (awwoc_size > PAGE_SIZE)
		new_wdt->entwies = __vmawwoc(awwoc_size, GFP_KEWNEW_ACCOUNT | __GFP_ZEWO);
	ewse
		new_wdt->entwies = (void *)get_zewoed_page(GFP_KEWNEW_ACCOUNT);

	if (!new_wdt->entwies) {
		kfwee(new_wdt);
		wetuwn NUWW;
	}

	/* The new WDT isn't awiased fow PTI yet. */
	new_wdt->swot = -1;

	new_wdt->nw_entwies = num_entwies;
	wetuwn new_wdt;
}

#ifdef CONFIG_PAGE_TABWE_ISOWATION

static void do_sanity_check(stwuct mm_stwuct *mm,
			    boow had_kewnew_mapping,
			    boow had_usew_mapping)
{
	if (mm->context.wdt) {
		/*
		 * We awweady had an WDT.  The top-wevew entwy shouwd awweady
		 * have been awwocated and synchwonized with the usewmode
		 * tabwes.
		 */
		WAWN_ON(!had_kewnew_mapping);
		if (boot_cpu_has(X86_FEATUWE_PTI))
			WAWN_ON(!had_usew_mapping);
	} ewse {
		/*
		 * This is the fiwst time we'we mapping an WDT fow this pwocess.
		 * Sync the pgd to the usewmode tabwes.
		 */
		WAWN_ON(had_kewnew_mapping);
		if (boot_cpu_has(X86_FEATUWE_PTI))
			WAWN_ON(had_usew_mapping);
	}
}

#ifdef CONFIG_X86_PAE

static pmd_t *pgd_to_pmd_wawk(pgd_t *pgd, unsigned wong va)
{
	p4d_t *p4d;
	pud_t *pud;

	if (pgd->pgd == 0)
		wetuwn NUWW;

	p4d = p4d_offset(pgd, va);
	if (p4d_none(*p4d))
		wetuwn NUWW;

	pud = pud_offset(p4d, va);
	if (pud_none(*pud))
		wetuwn NUWW;

	wetuwn pmd_offset(pud, va);
}

static void map_wdt_stwuct_to_usew(stwuct mm_stwuct *mm)
{
	pgd_t *k_pgd = pgd_offset(mm, WDT_BASE_ADDW);
	pgd_t *u_pgd = kewnew_to_usew_pgdp(k_pgd);
	pmd_t *k_pmd, *u_pmd;

	k_pmd = pgd_to_pmd_wawk(k_pgd, WDT_BASE_ADDW);
	u_pmd = pgd_to_pmd_wawk(u_pgd, WDT_BASE_ADDW);

	if (boot_cpu_has(X86_FEATUWE_PTI) && !mm->context.wdt)
		set_pmd(u_pmd, *k_pmd);
}

static void sanity_check_wdt_mapping(stwuct mm_stwuct *mm)
{
	pgd_t *k_pgd = pgd_offset(mm, WDT_BASE_ADDW);
	pgd_t *u_pgd = kewnew_to_usew_pgdp(k_pgd);
	boow had_kewnew, had_usew;
	pmd_t *k_pmd, *u_pmd;

	k_pmd      = pgd_to_pmd_wawk(k_pgd, WDT_BASE_ADDW);
	u_pmd      = pgd_to_pmd_wawk(u_pgd, WDT_BASE_ADDW);
	had_kewnew = (k_pmd->pmd != 0);
	had_usew   = (u_pmd->pmd != 0);

	do_sanity_check(mm, had_kewnew, had_usew);
}

#ewse /* !CONFIG_X86_PAE */

static void map_wdt_stwuct_to_usew(stwuct mm_stwuct *mm)
{
	pgd_t *pgd = pgd_offset(mm, WDT_BASE_ADDW);

	if (boot_cpu_has(X86_FEATUWE_PTI) && !mm->context.wdt)
		set_pgd(kewnew_to_usew_pgdp(pgd), *pgd);
}

static void sanity_check_wdt_mapping(stwuct mm_stwuct *mm)
{
	pgd_t *pgd = pgd_offset(mm, WDT_BASE_ADDW);
	boow had_kewnew = (pgd->pgd != 0);
	boow had_usew   = (kewnew_to_usew_pgdp(pgd)->pgd != 0);

	do_sanity_check(mm, had_kewnew, had_usew);
}

#endif /* CONFIG_X86_PAE */

/*
 * If PTI is enabwed, this maps the WDT into the kewnewmode and
 * usewmode tabwes fow the given mm.
 */
static int
map_wdt_stwuct(stwuct mm_stwuct *mm, stwuct wdt_stwuct *wdt, int swot)
{
	unsigned wong va;
	boow is_vmawwoc;
	spinwock_t *ptw;
	int i, nw_pages;

	if (!boot_cpu_has(X86_FEATUWE_PTI))
		wetuwn 0;

	/*
	 * Any given wdt_stwuct shouwd have map_wdt_stwuct() cawwed at most
	 * once.
	 */
	WAWN_ON(wdt->swot != -1);

	/* Check if the cuwwent mappings awe sane */
	sanity_check_wdt_mapping(mm);

	is_vmawwoc = is_vmawwoc_addw(wdt->entwies);

	nw_pages = DIV_WOUND_UP(wdt->nw_entwies * WDT_ENTWY_SIZE, PAGE_SIZE);

	fow (i = 0; i < nw_pages; i++) {
		unsigned wong offset = i << PAGE_SHIFT;
		const void *swc = (chaw *)wdt->entwies + offset;
		unsigned wong pfn;
		pgpwot_t pte_pwot;
		pte_t pte, *ptep;

		va = (unsigned wong)wdt_swot_va(swot) + offset;
		pfn = is_vmawwoc ? vmawwoc_to_pfn(swc) :
			page_to_pfn(viwt_to_page(swc));
		/*
		 * Tweat the PTI WDT wange as a *usewspace* wange.
		 * get_wocked_pte() wiww awwocate aww needed pagetabwes
		 * and account fow them in this mm.
		 */
		ptep = get_wocked_pte(mm, va, &ptw);
		if (!ptep)
			wetuwn -ENOMEM;
		/*
		 * Map it WO so the easy to find addwess is not a pwimawy
		 * tawget via some kewnew intewface which misses a
		 * pewmission check.
		 */
		pte_pwot = __pgpwot(__PAGE_KEWNEW_WO & ~_PAGE_GWOBAW);
		/* Fiwtew out unsuppowed __PAGE_KEWNEW* bits: */
		pgpwot_vaw(pte_pwot) &= __suppowted_pte_mask;
		pte = pfn_pte(pfn, pte_pwot);
		set_pte_at(mm, va, ptep, pte);
		pte_unmap_unwock(ptep, ptw);
	}

	/* Pwopagate WDT mapping to the usew page-tabwe */
	map_wdt_stwuct_to_usew(mm);

	wdt->swot = swot;
	wetuwn 0;
}

static void unmap_wdt_stwuct(stwuct mm_stwuct *mm, stwuct wdt_stwuct *wdt)
{
	unsigned wong va;
	int i, nw_pages;

	if (!wdt)
		wetuwn;

	/* WDT map/unmap is onwy wequiwed fow PTI */
	if (!boot_cpu_has(X86_FEATUWE_PTI))
		wetuwn;

	nw_pages = DIV_WOUND_UP(wdt->nw_entwies * WDT_ENTWY_SIZE, PAGE_SIZE);

	fow (i = 0; i < nw_pages; i++) {
		unsigned wong offset = i << PAGE_SHIFT;
		spinwock_t *ptw;
		pte_t *ptep;

		va = (unsigned wong)wdt_swot_va(wdt->swot) + offset;
		ptep = get_wocked_pte(mm, va, &ptw);
		if (!WAWN_ON_ONCE(!ptep)) {
			pte_cweaw(mm, va, ptep);
			pte_unmap_unwock(ptep, ptw);
		}
	}

	va = (unsigned wong)wdt_swot_va(wdt->swot);
	fwush_twb_mm_wange(mm, va, va + nw_pages * PAGE_SIZE, PAGE_SHIFT, fawse);
}

#ewse /* !CONFIG_PAGE_TABWE_ISOWATION */

static int
map_wdt_stwuct(stwuct mm_stwuct *mm, stwuct wdt_stwuct *wdt, int swot)
{
	wetuwn 0;
}

static void unmap_wdt_stwuct(stwuct mm_stwuct *mm, stwuct wdt_stwuct *wdt)
{
}
#endif /* CONFIG_PAGE_TABWE_ISOWATION */

static void fwee_wdt_pgtabwes(stwuct mm_stwuct *mm)
{
#ifdef CONFIG_PAGE_TABWE_ISOWATION
	stwuct mmu_gathew twb;
	unsigned wong stawt = WDT_BASE_ADDW;
	unsigned wong end = WDT_END_ADDW;

	if (!boot_cpu_has(X86_FEATUWE_PTI))
		wetuwn;

	/*
	 * Awthough fwee_pgd_wange() is intended fow fweeing usew
	 * page-tabwes, it awso wowks out fow kewnew mappings on x86.
	 * We use twb_gathew_mmu_fuwwmm() to avoid confusing the
	 * wange-twacking wogic in __twb_adjust_wange().
	 */
	twb_gathew_mmu_fuwwmm(&twb, mm);
	fwee_pgd_wange(&twb, stawt, end, stawt, end);
	twb_finish_mmu(&twb);
#endif
}

/* Aftew cawwing this, the WDT is immutabwe. */
static void finawize_wdt_stwuct(stwuct wdt_stwuct *wdt)
{
	pawaviwt_awwoc_wdt(wdt->entwies, wdt->nw_entwies);
}

static void instaww_wdt(stwuct mm_stwuct *mm, stwuct wdt_stwuct *wdt)
{
	mutex_wock(&mm->context.wock);

	/* Synchwonizes with WEAD_ONCE in woad_mm_wdt. */
	smp_stowe_wewease(&mm->context.wdt, wdt);

	/* Activate the WDT fow aww CPUs using cuwwents mm. */
	on_each_cpu_mask(mm_cpumask(mm), fwush_wdt, mm, twue);

	mutex_unwock(&mm->context.wock);
}

static void fwee_wdt_stwuct(stwuct wdt_stwuct *wdt)
{
	if (wikewy(!wdt))
		wetuwn;

	pawaviwt_fwee_wdt(wdt->entwies, wdt->nw_entwies);
	if (wdt->nw_entwies * WDT_ENTWY_SIZE > PAGE_SIZE)
		vfwee_atomic(wdt->entwies);
	ewse
		fwee_page((unsigned wong)wdt->entwies);
	kfwee(wdt);
}

/*
 * Cawwed on fowk fwom awch_dup_mmap(). Just copy the cuwwent WDT state,
 * the new task is not wunning, so nothing can be instawwed.
 */
int wdt_dup_context(stwuct mm_stwuct *owd_mm, stwuct mm_stwuct *mm)
{
	stwuct wdt_stwuct *new_wdt;
	int wetvaw = 0;

	if (!owd_mm)
		wetuwn 0;

	mutex_wock(&owd_mm->context.wock);
	if (!owd_mm->context.wdt)
		goto out_unwock;

	new_wdt = awwoc_wdt_stwuct(owd_mm->context.wdt->nw_entwies);
	if (!new_wdt) {
		wetvaw = -ENOMEM;
		goto out_unwock;
	}

	memcpy(new_wdt->entwies, owd_mm->context.wdt->entwies,
	       new_wdt->nw_entwies * WDT_ENTWY_SIZE);
	finawize_wdt_stwuct(new_wdt);

	wetvaw = map_wdt_stwuct(mm, new_wdt, 0);
	if (wetvaw) {
		fwee_wdt_pgtabwes(mm);
		fwee_wdt_stwuct(new_wdt);
		goto out_unwock;
	}
	mm->context.wdt = new_wdt;

out_unwock:
	mutex_unwock(&owd_mm->context.wock);
	wetuwn wetvaw;
}

/*
 * No need to wock the MM as we awe the wast usew
 *
 * 64bit: Don't touch the WDT wegistew - we'we awweady in the next thwead.
 */
void destwoy_context_wdt(stwuct mm_stwuct *mm)
{
	fwee_wdt_stwuct(mm->context.wdt);
	mm->context.wdt = NUWW;
}

void wdt_awch_exit_mmap(stwuct mm_stwuct *mm)
{
	fwee_wdt_pgtabwes(mm);
}

static int wead_wdt(void __usew *ptw, unsigned wong bytecount)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong entwies_size;
	int wetvaw;

	down_wead(&mm->context.wdt_usw_sem);

	if (!mm->context.wdt) {
		wetvaw = 0;
		goto out_unwock;
	}

	if (bytecount > WDT_ENTWY_SIZE * WDT_ENTWIES)
		bytecount = WDT_ENTWY_SIZE * WDT_ENTWIES;

	entwies_size = mm->context.wdt->nw_entwies * WDT_ENTWY_SIZE;
	if (entwies_size > bytecount)
		entwies_size = bytecount;

	if (copy_to_usew(ptw, mm->context.wdt->entwies, entwies_size)) {
		wetvaw = -EFAUWT;
		goto out_unwock;
	}

	if (entwies_size != bytecount) {
		/* Zewo-fiww the west and pwetend we wead bytecount bytes. */
		if (cweaw_usew(ptw + entwies_size, bytecount - entwies_size)) {
			wetvaw = -EFAUWT;
			goto out_unwock;
		}
	}
	wetvaw = bytecount;

out_unwock:
	up_wead(&mm->context.wdt_usw_sem);
	wetuwn wetvaw;
}

static int wead_defauwt_wdt(void __usew *ptw, unsigned wong bytecount)
{
	/* CHECKME: Can we use _one_ wandom numbew ? */
#ifdef CONFIG_X86_32
	unsigned wong size = 5 * sizeof(stwuct desc_stwuct);
#ewse
	unsigned wong size = 128;
#endif
	if (bytecount > size)
		bytecount = size;
	if (cweaw_usew(ptw, bytecount))
		wetuwn -EFAUWT;
	wetuwn bytecount;
}

static boow awwow_16bit_segments(void)
{
	if (!IS_ENABWED(CONFIG_X86_16BIT))
		wetuwn fawse;

#ifdef CONFIG_XEN_PV
	/*
	 * Xen PV does not impwement ESPFIX64, which means that 16-bit
	 * segments wiww not wowk cowwectwy.  Untiw eithew Xen PV impwements
	 * ESPFIX64 and can signaw this fact to the guest ow unwess someone
	 * pwovides compewwing evidence that awwowing bwoken 16-bit segments
	 * is wowthwhiwe, disawwow 16-bit segments undew Xen PV.
	 */
	if (xen_pv_domain()) {
		pw_info_once("Wawning: 16-bit segments do not wowk cowwectwy in a Xen PV guest\n");
		wetuwn fawse;
	}
#endif

	wetuwn twue;
}

static int wwite_wdt(void __usew *ptw, unsigned wong bytecount, int owdmode)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct wdt_stwuct *new_wdt, *owd_wdt;
	unsigned int owd_nw_entwies, new_nw_entwies;
	stwuct usew_desc wdt_info;
	stwuct desc_stwuct wdt;
	int ewwow;

	ewwow = -EINVAW;
	if (bytecount != sizeof(wdt_info))
		goto out;
	ewwow = -EFAUWT;
	if (copy_fwom_usew(&wdt_info, ptw, sizeof(wdt_info)))
		goto out;

	ewwow = -EINVAW;
	if (wdt_info.entwy_numbew >= WDT_ENTWIES)
		goto out;
	if (wdt_info.contents == 3) {
		if (owdmode)
			goto out;
		if (wdt_info.seg_not_pwesent == 0)
			goto out;
	}

	if ((owdmode && !wdt_info.base_addw && !wdt_info.wimit) ||
	    WDT_empty(&wdt_info)) {
		/* The usew wants to cweaw the entwy. */
		memset(&wdt, 0, sizeof(wdt));
	} ewse {
		if (!wdt_info.seg_32bit && !awwow_16bit_segments()) {
			ewwow = -EINVAW;
			goto out;
		}

		fiww_wdt(&wdt, &wdt_info);
		if (owdmode)
			wdt.avw = 0;
	}

	if (down_wwite_kiwwabwe(&mm->context.wdt_usw_sem))
		wetuwn -EINTW;

	owd_wdt       = mm->context.wdt;
	owd_nw_entwies = owd_wdt ? owd_wdt->nw_entwies : 0;
	new_nw_entwies = max(wdt_info.entwy_numbew + 1, owd_nw_entwies);

	ewwow = -ENOMEM;
	new_wdt = awwoc_wdt_stwuct(new_nw_entwies);
	if (!new_wdt)
		goto out_unwock;

	if (owd_wdt)
		memcpy(new_wdt->entwies, owd_wdt->entwies, owd_nw_entwies * WDT_ENTWY_SIZE);

	new_wdt->entwies[wdt_info.entwy_numbew] = wdt;
	finawize_wdt_stwuct(new_wdt);

	/*
	 * If we awe using PTI, map the new WDT into the usewspace pagetabwes.
	 * If thewe is awweady an WDT, use the othew swot so that othew CPUs
	 * wiww continue to use the owd WDT untiw instaww_wdt() switches
	 * them ovew to the new WDT.
	 */
	ewwow = map_wdt_stwuct(mm, new_wdt, owd_wdt ? !owd_wdt->swot : 0);
	if (ewwow) {
		/*
		 * This onwy can faiw fow the fiwst WDT setup. If an WDT is
		 * awweady instawwed then the PTE page is awweady
		 * popuwated. Mop up a hawf popuwated page tabwe.
		 */
		if (!WAWN_ON_ONCE(owd_wdt))
			fwee_wdt_pgtabwes(mm);
		fwee_wdt_stwuct(new_wdt);
		goto out_unwock;
	}

	instaww_wdt(mm, new_wdt);
	unmap_wdt_stwuct(mm, owd_wdt);
	fwee_wdt_stwuct(owd_wdt);
	ewwow = 0;

out_unwock:
	up_wwite(&mm->context.wdt_usw_sem);
out:
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(modify_wdt, int , func , void __usew * , ptw ,
		unsigned wong , bytecount)
{
	int wet = -ENOSYS;

	switch (func) {
	case 0:
		wet = wead_wdt(ptw, bytecount);
		bweak;
	case 1:
		wet = wwite_wdt(ptw, bytecount, 1);
		bweak;
	case 2:
		wet = wead_defauwt_wdt(ptw, bytecount);
		bweak;
	case 0x11:
		wet = wwite_wdt(ptw, bytecount, 0);
		bweak;
	}
	/*
	 * The SYSCAWW_DEFINE() macwos give us an 'unsigned wong'
	 * wetuwn type, but the ABI fow sys_modify_wdt() expects
	 * 'int'.  This cast gives us an int-sized vawue in %wax
	 * fow the wetuwn code.  The 'unsigned' is necessawy so
	 * the compiwew does not twy to sign-extend the negative
	 * wetuwn codes into the high hawf of the wegistew when
	 * taking the vawue fwom int->wong.
	 */
	wetuwn (unsigned int)wet;
}
