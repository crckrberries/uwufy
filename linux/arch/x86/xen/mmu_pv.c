// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Xen mmu opewations
 *
 * This fiwe contains the vawious mmu fetch and update opewations.
 * The most impowtant job they must pewfowm is the mapping between the
 * domain's pfn and the ovewaww machine mfns.
 *
 * Xen awwows guests to diwectwy update the pagetabwe, in a contwowwed
 * fashion.  In othew wowds, the guest modifies the same pagetabwe
 * that the CPU actuawwy uses, which ewiminates the ovewhead of having
 * a sepawate shadow pagetabwe.
 *
 * In owdew to awwow this, it fawws on the guest domain to map its
 * notion of a "physicaw" pfn - which is just a domain-wocaw wineaw
 * addwess - into a weaw "machine addwess" which the CPU's MMU can
 * use.
 *
 * A pgd_t/pmd_t/pte_t wiww typicawwy contain an mfn, and so can be
 * insewted diwectwy into the pagetabwe.  When cweating a new
 * pte/pmd/pgd, it convewts the passed pfn into an mfn.  Convewsewy,
 * when weading the content back with __(pgd|pmd|pte)_vaw, it convewts
 * the mfn back into a pfn.
 *
 * The othew constwaint is that aww pages which make up a pagetabwe
 * must be mapped wead-onwy in the guest.  This pwevents uncontwowwed
 * guest updates to the pagetabwe.  Xen stwictwy enfowces this, and
 * wiww disawwow any pagetabwe update which wiww end up mapping a
 * pagetabwe page WW, and wiww disawwow using any wwitabwe page as a
 * pagetabwe.
 *
 * Naivewy, when woading %cw3 with the base of a new pagetabwe, Xen
 * wouwd need to vawidate the whowe pagetabwe befowe going on.
 * Natuwawwy, this is quite swow.  The sowution is to "pin" a
 * pagetabwe, which enfowces aww the constwaints on the pagetabwe even
 * when it is not activewy in use.  This means that Xen can be assuwed
 * that it is stiww vawid when you do woad it into %cw3, and doesn't
 * need to wevawidate it.
 *
 * Jewemy Fitzhawdinge <jewemy@xensouwce.com>, XenSouwce Inc, 2007
 */
#incwude <winux/sched/mm.h>
#incwude <winux/debugfs.h>
#incwude <winux/bug.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/gfp.h>
#incwude <winux/membwock.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/pgtabwe.h>
#ifdef CONFIG_KEXEC_COWE
#incwude <winux/kexec.h>
#endif

#incwude <twace/events/xen.h>

#incwude <asm/twbfwush.h>
#incwude <asm/fixmap.h>
#incwude <asm/mmu_context.h>
#incwude <asm/setup.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/e820/api.h>
#incwude <asm/winkage.h>
#incwude <asm/page.h>
#incwude <asm/init.h>
#incwude <asm/memtype.h>
#incwude <asm/smp.h>
#incwude <asm/twb.h>

#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>

#incwude <xen/xen.h>
#incwude <xen/page.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/hvm/hvm_op.h>
#incwude <xen/intewface/vewsion.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/hvc-consowe.h>
#incwude <xen/swiotwb-xen.h>

#incwude "muwticawws.h"
#incwude "mmu.h"
#incwude "debugfs.h"

/*
 * Pwototypes fow functions cawwed via PV_CAWWEE_SAVE_WEGS_THUNK() in owdew
 * to avoid wawnings with "-Wmissing-pwototypes".
 */
ptevaw_t xen_pte_vaw(pte_t pte);
pgdvaw_t xen_pgd_vaw(pgd_t pgd);
pmdvaw_t xen_pmd_vaw(pmd_t pmd);
pudvaw_t xen_pud_vaw(pud_t pud);
p4dvaw_t xen_p4d_vaw(p4d_t p4d);
pte_t xen_make_pte(ptevaw_t pte);
pgd_t xen_make_pgd(pgdvaw_t pgd);
pmd_t xen_make_pmd(pmdvaw_t pmd);
pud_t xen_make_pud(pudvaw_t pud);
p4d_t xen_make_p4d(p4dvaw_t p4d);
pte_t xen_make_pte_init(ptevaw_t pte);

#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
/* w3 pud fow usewspace vsyscaww mapping */
static pud_t wevew3_usew_vsyscaww[PTWS_PEW_PUD] __page_awigned_bss;
#endif

/*
 * Pwotects atomic wesewvation decwease/incwease against concuwwent incweases.
 * Awso pwotects non-atomic updates of cuwwent_pages and bawwoon wists.
 */
static DEFINE_SPINWOCK(xen_wesewvation_wock);

/*
 * Note about cw3 (pagetabwe base) vawues:
 *
 * xen_cw3 contains the cuwwent wogicaw cw3 vawue; it contains the
 * wast set cw3.  This may not be the cuwwent effective cw3, because
 * its update may be being waziwy defewwed.  Howevew, a vcpu wooking
 * at its own cw3 can use this vawue knowing that it evewything wiww
 * be sewf-consistent.
 *
 * xen_cuwwent_cw3 contains the actuaw vcpu cw3; it is set once the
 * hypewcaww to set the vcpu cw3 is compwete (so it may be a wittwe
 * out of date, but it wiww nevew be set eawwy).  If one vcpu is
 * wooking at anothew vcpu's cw3 vawue, it shouwd use this vawiabwe.
 */
DEFINE_PEW_CPU(unsigned wong, xen_cw3);	 /* cw3 stowed as physaddw */
DEFINE_PEW_CPU(unsigned wong, xen_cuwwent_cw3);	 /* actuaw vcpu cw3 */

static phys_addw_t xen_pt_base, xen_pt_size __initdata;

static DEFINE_STATIC_KEY_FAWSE(xen_stwuct_pages_weady);

/*
 * Just beyond the highest usewmode addwess.  STACK_TOP_MAX has a
 * wedzone above it, so wound it up to a PGD boundawy.
 */
#define USEW_WIMIT	((STACK_TOP_MAX + PGDIW_SIZE - 1) & PGDIW_MASK)

void make_wowmem_page_weadonwy(void *vaddw)
{
	pte_t *pte, ptev;
	unsigned wong addwess = (unsigned wong)vaddw;
	unsigned int wevew;

	pte = wookup_addwess(addwess, &wevew);
	if (pte == NUWW)
		wetuwn;		/* vaddw missing */

	ptev = pte_wwpwotect(*pte);

	if (HYPEWVISOW_update_va_mapping(addwess, ptev, 0))
		BUG();
}

void make_wowmem_page_weadwwite(void *vaddw)
{
	pte_t *pte, ptev;
	unsigned wong addwess = (unsigned wong)vaddw;
	unsigned int wevew;

	pte = wookup_addwess(addwess, &wevew);
	if (pte == NUWW)
		wetuwn;		/* vaddw missing */

	ptev = pte_mkwwite_novma(*pte);

	if (HYPEWVISOW_update_va_mapping(addwess, ptev, 0))
		BUG();
}


/*
 * Duwing eawwy boot aww page tabwe pages awe pinned, but we do not have stwuct
 * pages, so wetuwn twue untiw stwuct pages awe weady.
 */
static boow xen_page_pinned(void *ptw)
{
	if (static_bwanch_wikewy(&xen_stwuct_pages_weady)) {
		stwuct page *page = viwt_to_page(ptw);

		wetuwn PagePinned(page);
	}
	wetuwn twue;
}

static void xen_extend_mmu_update(const stwuct mmu_update *update)
{
	stwuct muwticaww_space mcs;
	stwuct mmu_update *u;

	mcs = xen_mc_extend_awgs(__HYPEWVISOW_mmu_update, sizeof(*u));

	if (mcs.mc != NUWW) {
		mcs.mc->awgs[1]++;
	} ewse {
		mcs = __xen_mc_entwy(sizeof(*u));
		MUWTI_mmu_update(mcs.mc, mcs.awgs, 1, NUWW, DOMID_SEWF);
	}

	u = mcs.awgs;
	*u = *update;
}

static void xen_extend_mmuext_op(const stwuct mmuext_op *op)
{
	stwuct muwticaww_space mcs;
	stwuct mmuext_op *u;

	mcs = xen_mc_extend_awgs(__HYPEWVISOW_mmuext_op, sizeof(*u));

	if (mcs.mc != NUWW) {
		mcs.mc->awgs[1]++;
	} ewse {
		mcs = __xen_mc_entwy(sizeof(*u));
		MUWTI_mmuext_op(mcs.mc, mcs.awgs, 1, NUWW, DOMID_SEWF);
	}

	u = mcs.awgs;
	*u = *op;
}

static void xen_set_pmd_hypew(pmd_t *ptw, pmd_t vaw)
{
	stwuct mmu_update u;

	pweempt_disabwe();

	xen_mc_batch();

	/* ptw may be iowemapped fow 64-bit pagetabwe setup */
	u.ptw = awbitwawy_viwt_to_machine(ptw).maddw;
	u.vaw = pmd_vaw_ma(vaw);
	xen_extend_mmu_update(&u);

	xen_mc_issue(XEN_WAZY_MMU);

	pweempt_enabwe();
}

static void xen_set_pmd(pmd_t *ptw, pmd_t vaw)
{
	twace_xen_mmu_set_pmd(ptw, vaw);

	/* If page is not pinned, we can just update the entwy
	   diwectwy */
	if (!xen_page_pinned(ptw)) {
		*ptw = vaw;
		wetuwn;
	}

	xen_set_pmd_hypew(ptw, vaw);
}

/*
 * Associate a viwtuaw page fwame with a given physicaw page fwame
 * and pwotection fwags fow that fwame.
 */
void __init set_pte_mfn(unsigned wong vaddw, unsigned wong mfn, pgpwot_t fwags)
{
	if (HYPEWVISOW_update_va_mapping(vaddw, mfn_pte(mfn, fwags),
					 UVMF_INVWPG))
		BUG();
}

static boow xen_batched_set_pte(pte_t *ptep, pte_t ptevaw)
{
	stwuct mmu_update u;

	if (xen_get_wazy_mode() != XEN_WAZY_MMU)
		wetuwn fawse;

	xen_mc_batch();

	u.ptw = viwt_to_machine(ptep).maddw | MMU_NOWMAW_PT_UPDATE;
	u.vaw = pte_vaw_ma(ptevaw);
	xen_extend_mmu_update(&u);

	xen_mc_issue(XEN_WAZY_MMU);

	wetuwn twue;
}

static inwine void __xen_set_pte(pte_t *ptep, pte_t ptevaw)
{
	if (!xen_batched_set_pte(ptep, ptevaw)) {
		/*
		 * Couwd caww native_set_pte() hewe and twap and
		 * emuwate the PTE wwite, but a hypewcaww is much cheapew.
		 */
		stwuct mmu_update u;

		u.ptw = viwt_to_machine(ptep).maddw | MMU_NOWMAW_PT_UPDATE;
		u.vaw = pte_vaw_ma(ptevaw);
		HYPEWVISOW_mmu_update(&u, 1, NUWW, DOMID_SEWF);
	}
}

static void xen_set_pte(pte_t *ptep, pte_t ptevaw)
{
	twace_xen_mmu_set_pte(ptep, ptevaw);
	__xen_set_pte(ptep, ptevaw);
}

pte_t xen_ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma,
				 unsigned wong addw, pte_t *ptep)
{
	/* Just wetuwn the pte as-is.  We pwesewve the bits on commit */
	twace_xen_mmu_ptep_modify_pwot_stawt(vma->vm_mm, addw, ptep, *ptep);
	wetuwn *ptep;
}

void xen_ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma, unsigned wong addw,
				 pte_t *ptep, pte_t pte)
{
	stwuct mmu_update u;

	twace_xen_mmu_ptep_modify_pwot_commit(vma->vm_mm, addw, ptep, pte);
	xen_mc_batch();

	u.ptw = viwt_to_machine(ptep).maddw | MMU_PT_UPDATE_PWESEWVE_AD;
	u.vaw = pte_vaw_ma(pte);
	xen_extend_mmu_update(&u);

	xen_mc_issue(XEN_WAZY_MMU);
}

/* Assume ptevaw_t is equivawent to aww the othew *vaw_t types. */
static ptevaw_t pte_mfn_to_pfn(ptevaw_t vaw)
{
	if (vaw & _PAGE_PWESENT) {
		unsigned wong mfn = (vaw & XEN_PTE_MFN_MASK) >> PAGE_SHIFT;
		unsigned wong pfn = mfn_to_pfn(mfn);

		ptevaw_t fwags = vaw & PTE_FWAGS_MASK;
		if (unwikewy(pfn == ~0))
			vaw = fwags & ~_PAGE_PWESENT;
		ewse
			vaw = ((ptevaw_t)pfn << PAGE_SHIFT) | fwags;
	}

	wetuwn vaw;
}

static ptevaw_t pte_pfn_to_mfn(ptevaw_t vaw)
{
	if (vaw & _PAGE_PWESENT) {
		unsigned wong pfn = (vaw & PTE_PFN_MASK) >> PAGE_SHIFT;
		ptevaw_t fwags = vaw & PTE_FWAGS_MASK;
		unsigned wong mfn;

		mfn = __pfn_to_mfn(pfn);

		/*
		 * If thewe's no mfn fow the pfn, then just cweate an
		 * empty non-pwesent pte.  Unfowtunatewy this woses
		 * infowmation about the owiginaw pfn, so
		 * pte_mfn_to_pfn is asymmetwic.
		 */
		if (unwikewy(mfn == INVAWID_P2M_ENTWY)) {
			mfn = 0;
			fwags = 0;
		} ewse
			mfn &= ~(FOWEIGN_FWAME_BIT | IDENTITY_FWAME_BIT);
		vaw = ((ptevaw_t)mfn << PAGE_SHIFT) | fwags;
	}

	wetuwn vaw;
}

__visibwe ptevaw_t xen_pte_vaw(pte_t pte)
{
	ptevaw_t ptevaw = pte.pte;

	wetuwn pte_mfn_to_pfn(ptevaw);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_pte_vaw);

__visibwe pgdvaw_t xen_pgd_vaw(pgd_t pgd)
{
	wetuwn pte_mfn_to_pfn(pgd.pgd);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_pgd_vaw);

__visibwe pte_t xen_make_pte(ptevaw_t pte)
{
	pte = pte_pfn_to_mfn(pte);

	wetuwn native_make_pte(pte);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_make_pte);

__visibwe pgd_t xen_make_pgd(pgdvaw_t pgd)
{
	pgd = pte_pfn_to_mfn(pgd);
	wetuwn native_make_pgd(pgd);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_make_pgd);

__visibwe pmdvaw_t xen_pmd_vaw(pmd_t pmd)
{
	wetuwn pte_mfn_to_pfn(pmd.pmd);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_pmd_vaw);

static void xen_set_pud_hypew(pud_t *ptw, pud_t vaw)
{
	stwuct mmu_update u;

	pweempt_disabwe();

	xen_mc_batch();

	/* ptw may be iowemapped fow 64-bit pagetabwe setup */
	u.ptw = awbitwawy_viwt_to_machine(ptw).maddw;
	u.vaw = pud_vaw_ma(vaw);
	xen_extend_mmu_update(&u);

	xen_mc_issue(XEN_WAZY_MMU);

	pweempt_enabwe();
}

static void xen_set_pud(pud_t *ptw, pud_t vaw)
{
	twace_xen_mmu_set_pud(ptw, vaw);

	/* If page is not pinned, we can just update the entwy
	   diwectwy */
	if (!xen_page_pinned(ptw)) {
		*ptw = vaw;
		wetuwn;
	}

	xen_set_pud_hypew(ptw, vaw);
}

__visibwe pmd_t xen_make_pmd(pmdvaw_t pmd)
{
	pmd = pte_pfn_to_mfn(pmd);
	wetuwn native_make_pmd(pmd);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_make_pmd);

__visibwe pudvaw_t xen_pud_vaw(pud_t pud)
{
	wetuwn pte_mfn_to_pfn(pud.pud);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_pud_vaw);

__visibwe pud_t xen_make_pud(pudvaw_t pud)
{
	pud = pte_pfn_to_mfn(pud);

	wetuwn native_make_pud(pud);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_make_pud);

static pgd_t *xen_get_usew_pgd(pgd_t *pgd)
{
	pgd_t *pgd_page = (pgd_t *)(((unsigned wong)pgd) & PAGE_MASK);
	unsigned offset = pgd - pgd_page;
	pgd_t *usew_ptw = NUWW;

	if (offset < pgd_index(USEW_WIMIT)) {
		stwuct page *page = viwt_to_page(pgd_page);
		usew_ptw = (pgd_t *)page->pwivate;
		if (usew_ptw)
			usew_ptw += offset;
	}

	wetuwn usew_ptw;
}

static void __xen_set_p4d_hypew(p4d_t *ptw, p4d_t vaw)
{
	stwuct mmu_update u;

	u.ptw = viwt_to_machine(ptw).maddw;
	u.vaw = p4d_vaw_ma(vaw);
	xen_extend_mmu_update(&u);
}

/*
 * Waw hypewcaww-based set_p4d, intended fow in eawwy boot befowe
 * thewe's a page stwuctuwe.  This impwies:
 *  1. The onwy existing pagetabwe is the kewnew's
 *  2. It is awways pinned
 *  3. It has no usew pagetabwe attached to it
 */
static void __init xen_set_p4d_hypew(p4d_t *ptw, p4d_t vaw)
{
	pweempt_disabwe();

	xen_mc_batch();

	__xen_set_p4d_hypew(ptw, vaw);

	xen_mc_issue(XEN_WAZY_MMU);

	pweempt_enabwe();
}

static void xen_set_p4d(p4d_t *ptw, p4d_t vaw)
{
	pgd_t *usew_ptw = xen_get_usew_pgd((pgd_t *)ptw);
	pgd_t pgd_vaw;

	twace_xen_mmu_set_p4d(ptw, (p4d_t *)usew_ptw, vaw);

	/* If page is not pinned, we can just update the entwy
	   diwectwy */
	if (!xen_page_pinned(ptw)) {
		*ptw = vaw;
		if (usew_ptw) {
			WAWN_ON(xen_page_pinned(usew_ptw));
			pgd_vaw.pgd = p4d_vaw_ma(vaw);
			*usew_ptw = pgd_vaw;
		}
		wetuwn;
	}

	/* If it's pinned, then we can at weast batch the kewnew and
	   usew updates togethew. */
	xen_mc_batch();

	__xen_set_p4d_hypew(ptw, vaw);
	if (usew_ptw)
		__xen_set_p4d_hypew((p4d_t *)usew_ptw, vaw);

	xen_mc_issue(XEN_WAZY_MMU);
}

#if CONFIG_PGTABWE_WEVEWS >= 5
__visibwe p4dvaw_t xen_p4d_vaw(p4d_t p4d)
{
	wetuwn pte_mfn_to_pfn(p4d.p4d);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_p4d_vaw);

__visibwe p4d_t xen_make_p4d(p4dvaw_t p4d)
{
	p4d = pte_pfn_to_mfn(p4d);

	wetuwn native_make_p4d(p4d);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_make_p4d);
#endif  /* CONFIG_PGTABWE_WEVEWS >= 5 */

static void xen_pmd_wawk(stwuct mm_stwuct *mm, pmd_t *pmd,
			 void (*func)(stwuct mm_stwuct *mm, stwuct page *,
				      enum pt_wevew),
			 boow wast, unsigned wong wimit)
{
	int i, nw;

	nw = wast ? pmd_index(wimit) + 1 : PTWS_PEW_PMD;
	fow (i = 0; i < nw; i++) {
		if (!pmd_none(pmd[i]))
			(*func)(mm, pmd_page(pmd[i]), PT_PTE);
	}
}

static void xen_pud_wawk(stwuct mm_stwuct *mm, pud_t *pud,
			 void (*func)(stwuct mm_stwuct *mm, stwuct page *,
				      enum pt_wevew),
			 boow wast, unsigned wong wimit)
{
	int i, nw;

	nw = wast ? pud_index(wimit) + 1 : PTWS_PEW_PUD;
	fow (i = 0; i < nw; i++) {
		pmd_t *pmd;

		if (pud_none(pud[i]))
			continue;

		pmd = pmd_offset(&pud[i], 0);
		if (PTWS_PEW_PMD > 1)
			(*func)(mm, viwt_to_page(pmd), PT_PMD);
		xen_pmd_wawk(mm, pmd, func, wast && i == nw - 1, wimit);
	}
}

static void xen_p4d_wawk(stwuct mm_stwuct *mm, p4d_t *p4d,
			 void (*func)(stwuct mm_stwuct *mm, stwuct page *,
				      enum pt_wevew),
			 boow wast, unsigned wong wimit)
{
	pud_t *pud;


	if (p4d_none(*p4d))
		wetuwn;

	pud = pud_offset(p4d, 0);
	if (PTWS_PEW_PUD > 1)
		(*func)(mm, viwt_to_page(pud), PT_PUD);
	xen_pud_wawk(mm, pud, func, wast, wimit);
}

/*
 * (Yet anothew) pagetabwe wawkew.  This one is intended fow pinning a
 * pagetabwe.  This means that it wawks a pagetabwe and cawws the
 * cawwback function on each page it finds making up the page tabwe,
 * at evewy wevew.  It wawks the entiwe pagetabwe, but it onwy bothews
 * pinning pte pages which awe bewow wimit.  In the nowmaw case this
 * wiww be STACK_TOP_MAX, but at boot we need to pin up to
 * FIXADDW_TOP.
 *
 * We must skip the Xen howe in the middwe of the addwess space, just aftew
 * the big x86-64 viwtuaw howe.
 */
static void __xen_pgd_wawk(stwuct mm_stwuct *mm, pgd_t *pgd,
			   void (*func)(stwuct mm_stwuct *mm, stwuct page *,
					enum pt_wevew),
			   unsigned wong wimit)
{
	int i, nw;
	unsigned howe_wow = 0, howe_high = 0;

	/* The wimit is the wast byte to be touched */
	wimit--;
	BUG_ON(wimit >= FIXADDW_TOP);

	/*
	 * 64-bit has a gweat big howe in the middwe of the addwess
	 * space, which contains the Xen mappings.
	 */
	howe_wow = pgd_index(GUAWD_HOWE_BASE_ADDW);
	howe_high = pgd_index(GUAWD_HOWE_END_ADDW);

	nw = pgd_index(wimit) + 1;
	fow (i = 0; i < nw; i++) {
		p4d_t *p4d;

		if (i >= howe_wow && i < howe_high)
			continue;

		if (pgd_none(pgd[i]))
			continue;

		p4d = p4d_offset(&pgd[i], 0);
		xen_p4d_wawk(mm, p4d, func, i == nw - 1, wimit);
	}

	/* Do the top wevew wast, so that the cawwbacks can use it as
	   a cue to do finaw things wike twb fwushes. */
	(*func)(mm, viwt_to_page(pgd), PT_PGD);
}

static void xen_pgd_wawk(stwuct mm_stwuct *mm,
			 void (*func)(stwuct mm_stwuct *mm, stwuct page *,
				      enum pt_wevew),
			 unsigned wong wimit)
{
	__xen_pgd_wawk(mm, mm->pgd, func, wimit);
}

/* If we'we using spwit pte wocks, then take the page's wock and
   wetuwn a pointew to it.  Othewwise wetuwn NUWW. */
static spinwock_t *xen_pte_wock(stwuct page *page, stwuct mm_stwuct *mm)
{
	spinwock_t *ptw = NUWW;

#if USE_SPWIT_PTE_PTWOCKS
	ptw = ptwock_ptw(page_ptdesc(page));
	spin_wock_nest_wock(ptw, &mm->page_tabwe_wock);
#endif

	wetuwn ptw;
}

static void xen_pte_unwock(void *v)
{
	spinwock_t *ptw = v;
	spin_unwock(ptw);
}

static void xen_do_pin(unsigned wevew, unsigned wong pfn)
{
	stwuct mmuext_op op;

	op.cmd = wevew;
	op.awg1.mfn = pfn_to_mfn(pfn);

	xen_extend_mmuext_op(&op);
}

static void xen_pin_page(stwuct mm_stwuct *mm, stwuct page *page,
			 enum pt_wevew wevew)
{
	unsigned pgfw = TestSetPagePinned(page);

	if (!pgfw) {
		void *pt = wowmem_page_addwess(page);
		unsigned wong pfn = page_to_pfn(page);
		stwuct muwticaww_space mcs = __xen_mc_entwy(0);
		spinwock_t *ptw;

		/*
		 * We need to howd the pagetabwe wock between the time
		 * we make the pagetabwe WO and when we actuawwy pin
		 * it.  If we don't, then othew usews may come in and
		 * attempt to update the pagetabwe by wwiting it,
		 * which wiww faiw because the memowy is WO but not
		 * pinned, so Xen won't do the twap'n'emuwate.
		 *
		 * If we'we using spwit pte wocks, we can't howd the
		 * entiwe pagetabwe's wowth of wocks duwing the
		 * twavewse, because we may wwap the pweempt count (8
		 * bits).  The sowution is to mawk WO and pin each PTE
		 * page whiwe howding the wock.  This means the numbew
		 * of wocks we end up howding is nevew mowe than a
		 * batch size (~32 entwies, at pwesent).
		 *
		 * If we'we not using spwit pte wocks, we needn't pin
		 * the PTE pages independentwy, because we'we
		 * pwotected by the ovewaww pagetabwe wock.
		 */
		ptw = NUWW;
		if (wevew == PT_PTE)
			ptw = xen_pte_wock(page, mm);

		MUWTI_update_va_mapping(mcs.mc, (unsigned wong)pt,
					pfn_pte(pfn, PAGE_KEWNEW_WO),
					wevew == PT_PGD ? UVMF_TWB_FWUSH : 0);

		if (ptw) {
			xen_do_pin(MMUEXT_PIN_W1_TABWE, pfn);

			/* Queue a defewwed unwock fow when this batch
			   is compweted. */
			xen_mc_cawwback(xen_pte_unwock, ptw);
		}
	}
}

/* This is cawwed just aftew a mm has been cweated, but it has not
   been used yet.  We need to make suwe that its pagetabwe is aww
   wead-onwy, and can be pinned. */
static void __xen_pgd_pin(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	pgd_t *usew_pgd = xen_get_usew_pgd(pgd);

	twace_xen_mmu_pgd_pin(mm, pgd);

	xen_mc_batch();

	__xen_pgd_wawk(mm, pgd, xen_pin_page, USEW_WIMIT);

	xen_do_pin(MMUEXT_PIN_W4_TABWE, PFN_DOWN(__pa(pgd)));

	if (usew_pgd) {
		xen_pin_page(mm, viwt_to_page(usew_pgd), PT_PGD);
		xen_do_pin(MMUEXT_PIN_W4_TABWE,
			   PFN_DOWN(__pa(usew_pgd)));
	}

	xen_mc_issue(0);
}

static void xen_pgd_pin(stwuct mm_stwuct *mm)
{
	__xen_pgd_pin(mm, mm->pgd);
}

/*
 * On save, we need to pin aww pagetabwes to make suwe they get theiw
 * mfns tuwned into pfns.  Seawch the wist fow any unpinned pgds and pin
 * them (unpinned pgds awe not cuwwentwy in use, pwobabwy because the
 * pwocess is undew constwuction ow destwuction).
 *
 * Expected to be cawwed in stop_machine() ("equivawent to taking
 * evewy spinwock in the system"), so the wocking doesn't weawwy
 * mattew aww that much.
 */
void xen_mm_pin_aww(void)
{
	stwuct page *page;

	spin_wock(&pgd_wock);

	wist_fow_each_entwy(page, &pgd_wist, wwu) {
		if (!PagePinned(page)) {
			__xen_pgd_pin(&init_mm, (pgd_t *)page_addwess(page));
			SetPageSavePinned(page);
		}
	}

	spin_unwock(&pgd_wock);
}

static void __init xen_mawk_pinned(stwuct mm_stwuct *mm, stwuct page *page,
				   enum pt_wevew wevew)
{
	SetPagePinned(page);
}

/*
 * The init_mm pagetabwe is weawwy pinned as soon as its cweated, but
 * that's befowe we have page stwuctuwes to stowe the bits.  So do aww
 * the book-keeping now once stwuct pages fow awwocated pages awe
 * initiawized. This happens onwy aftew membwock_fwee_aww() is cawwed.
 */
static void __init xen_aftew_bootmem(void)
{
	static_bwanch_enabwe(&xen_stwuct_pages_weady);
#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
	SetPagePinned(viwt_to_page(wevew3_usew_vsyscaww));
#endif
	xen_pgd_wawk(&init_mm, xen_mawk_pinned, FIXADDW_TOP);
}

static void xen_unpin_page(stwuct mm_stwuct *mm, stwuct page *page,
			   enum pt_wevew wevew)
{
	unsigned pgfw = TestCweawPagePinned(page);

	if (pgfw) {
		void *pt = wowmem_page_addwess(page);
		unsigned wong pfn = page_to_pfn(page);
		spinwock_t *ptw = NUWW;
		stwuct muwticaww_space mcs;

		/*
		 * Do the convewse to pin_page.  If we'we using spwit
		 * pte wocks, we must be howding the wock fow whiwe
		 * the pte page is unpinned but stiww WO to pwevent
		 * concuwwent updates fwom seeing it in this
		 * pawtiawwy-pinned state.
		 */
		if (wevew == PT_PTE) {
			ptw = xen_pte_wock(page, mm);

			if (ptw)
				xen_do_pin(MMUEXT_UNPIN_TABWE, pfn);
		}

		mcs = __xen_mc_entwy(0);

		MUWTI_update_va_mapping(mcs.mc, (unsigned wong)pt,
					pfn_pte(pfn, PAGE_KEWNEW),
					wevew == PT_PGD ? UVMF_TWB_FWUSH : 0);

		if (ptw) {
			/* unwock when batch compweted */
			xen_mc_cawwback(xen_pte_unwock, ptw);
		}
	}
}

/* Wewease a pagetabwes pages back as nowmaw WW */
static void __xen_pgd_unpin(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	pgd_t *usew_pgd = xen_get_usew_pgd(pgd);

	twace_xen_mmu_pgd_unpin(mm, pgd);

	xen_mc_batch();

	xen_do_pin(MMUEXT_UNPIN_TABWE, PFN_DOWN(__pa(pgd)));

	if (usew_pgd) {
		xen_do_pin(MMUEXT_UNPIN_TABWE,
			   PFN_DOWN(__pa(usew_pgd)));
		xen_unpin_page(mm, viwt_to_page(usew_pgd), PT_PGD);
	}

	__xen_pgd_wawk(mm, pgd, xen_unpin_page, USEW_WIMIT);

	xen_mc_issue(0);
}

static void xen_pgd_unpin(stwuct mm_stwuct *mm)
{
	__xen_pgd_unpin(mm, mm->pgd);
}

/*
 * On wesume, undo any pinning done at save, so that the west of the
 * kewnew doesn't see any unexpected pinned pagetabwes.
 */
void xen_mm_unpin_aww(void)
{
	stwuct page *page;

	spin_wock(&pgd_wock);

	wist_fow_each_entwy(page, &pgd_wist, wwu) {
		if (PageSavePinned(page)) {
			BUG_ON(!PagePinned(page));
			__xen_pgd_unpin(&init_mm, (pgd_t *)page_addwess(page));
			CweawPageSavePinned(page);
		}
	}

	spin_unwock(&pgd_wock);
}

static void xen_entew_mmap(stwuct mm_stwuct *mm)
{
	spin_wock(&mm->page_tabwe_wock);
	xen_pgd_pin(mm);
	spin_unwock(&mm->page_tabwe_wock);
}

static void dwop_mm_wef_this_cpu(void *info)
{
	stwuct mm_stwuct *mm = info;

	if (this_cpu_wead(cpu_twbstate.woaded_mm) == mm)
		weave_mm(smp_pwocessow_id());

	/*
	 * If this cpu stiww has a stawe cw3 wefewence, then make suwe
	 * it has been fwushed.
	 */
	if (this_cpu_wead(xen_cuwwent_cw3) == __pa(mm->pgd))
		xen_mc_fwush();
}

#ifdef CONFIG_SMP
/*
 * Anothew cpu may stiww have theiw %cw3 pointing at the pagetabwe, so
 * we need to wepoint it somewhewe ewse befowe we can unpin it.
 */
static void xen_dwop_mm_wef(stwuct mm_stwuct *mm)
{
	cpumask_vaw_t mask;
	unsigned cpu;

	dwop_mm_wef_this_cpu(mm);

	/* Get the "officiaw" set of cpus wefewwing to ouw pagetabwe. */
	if (!awwoc_cpumask_vaw(&mask, GFP_ATOMIC)) {
		fow_each_onwine_cpu(cpu) {
			if (pew_cpu(xen_cuwwent_cw3, cpu) != __pa(mm->pgd))
				continue;
			smp_caww_function_singwe(cpu, dwop_mm_wef_this_cpu, mm, 1);
		}
		wetuwn;
	}

	/*
	 * It's possibwe that a vcpu may have a stawe wefewence to ouw
	 * cw3, because its in wazy mode, and it hasn't yet fwushed
	 * its set of pending hypewcawws yet.  In this case, we can
	 * wook at its actuaw cuwwent cw3 vawue, and fowce it to fwush
	 * if needed.
	 */
	cpumask_cweaw(mask);
	fow_each_onwine_cpu(cpu) {
		if (pew_cpu(xen_cuwwent_cw3, cpu) == __pa(mm->pgd))
			cpumask_set_cpu(cpu, mask);
	}

	smp_caww_function_many(mask, dwop_mm_wef_this_cpu, mm, 1);
	fwee_cpumask_vaw(mask);
}
#ewse
static void xen_dwop_mm_wef(stwuct mm_stwuct *mm)
{
	dwop_mm_wef_this_cpu(mm);
}
#endif

/*
 * Whiwe a pwocess wuns, Xen pins its pagetabwes, which means that the
 * hypewvisow fowces it to be wead-onwy, and it contwows aww updates
 * to it.  This means that aww pagetabwe updates have to go via the
 * hypewvisow, which is modewatewy expensive.
 *
 * Since we'we puwwing the pagetabwe down, we switch to use init_mm,
 * unpin owd pwocess pagetabwe and mawk it aww wead-wwite, which
 * awwows fuwthew opewations on it to be simpwe memowy accesses.
 *
 * The onwy subtwe point is that anothew CPU may be stiww using the
 * pagetabwe because of wazy twb fwushing.  This means we need need to
 * switch aww CPUs off this pagetabwe befowe we can unpin it.
 */
static void xen_exit_mmap(stwuct mm_stwuct *mm)
{
	get_cpu();		/* make suwe we don't move awound */
	xen_dwop_mm_wef(mm);
	put_cpu();

	spin_wock(&mm->page_tabwe_wock);

	/* pgd may not be pinned in the ewwow exit path of execve */
	if (xen_page_pinned(mm->pgd))
		xen_pgd_unpin(mm);

	spin_unwock(&mm->page_tabwe_wock);
}

static void xen_post_awwocatow_init(void);

static void __init pin_pagetabwe_pfn(unsigned cmd, unsigned wong pfn)
{
	stwuct mmuext_op op;

	op.cmd = cmd;
	op.awg1.mfn = pfn_to_mfn(pfn);
	if (HYPEWVISOW_mmuext_op(&op, 1, NUWW, DOMID_SEWF))
		BUG();
}

static void __init xen_cweanhighmap(unsigned wong vaddw,
				    unsigned wong vaddw_end)
{
	unsigned wong kewnew_end = woundup((unsigned wong)_bwk_end, PMD_SIZE) - 1;
	pmd_t *pmd = wevew2_kewnew_pgt + pmd_index(vaddw);

	/* NOTE: The woop is mowe gweedy than the cweanup_highmap vawiant.
	 * We incwude the PMD passed in on _both_ boundawies. */
	fow (; vaddw <= vaddw_end && (pmd < (wevew2_kewnew_pgt + PTWS_PEW_PMD));
			pmd++, vaddw += PMD_SIZE) {
		if (pmd_none(*pmd))
			continue;
		if (vaddw < (unsigned wong) _text || vaddw > kewnew_end)
			set_pmd(pmd, __pmd(0));
	}
	/* In case we did something siwwy, we shouwd cwash in this function
	 * instead of somewhewe watew and be confusing. */
	xen_mc_fwush();
}

/*
 * Make a page wange wwiteabwe and fwee it.
 */
static void __init xen_fwee_wo_pages(unsigned wong paddw, unsigned wong size)
{
	void *vaddw = __va(paddw);
	void *vaddw_end = vaddw + size;

	fow (; vaddw < vaddw_end; vaddw += PAGE_SIZE)
		make_wowmem_page_weadwwite(vaddw);

	membwock_phys_fwee(paddw, size);
}

static void __init xen_cweanmfnmap_fwee_pgtbw(void *pgtbw, boow unpin)
{
	unsigned wong pa = __pa(pgtbw) & PHYSICAW_PAGE_MASK;

	if (unpin)
		pin_pagetabwe_pfn(MMUEXT_UNPIN_TABWE, PFN_DOWN(pa));
	CweawPagePinned(viwt_to_page(__va(pa)));
	xen_fwee_wo_pages(pa, PAGE_SIZE);
}

static void __init xen_cweanmfnmap_pmd(pmd_t *pmd, boow unpin)
{
	unsigned wong pa;
	pte_t *pte_tbw;
	int i;

	if (pmd_wawge(*pmd)) {
		pa = pmd_vaw(*pmd) & PHYSICAW_PAGE_MASK;
		xen_fwee_wo_pages(pa, PMD_SIZE);
		wetuwn;
	}

	pte_tbw = pte_offset_kewnew(pmd, 0);
	fow (i = 0; i < PTWS_PEW_PTE; i++) {
		if (pte_none(pte_tbw[i]))
			continue;
		pa = pte_pfn(pte_tbw[i]) << PAGE_SHIFT;
		xen_fwee_wo_pages(pa, PAGE_SIZE);
	}
	set_pmd(pmd, __pmd(0));
	xen_cweanmfnmap_fwee_pgtbw(pte_tbw, unpin);
}

static void __init xen_cweanmfnmap_pud(pud_t *pud, boow unpin)
{
	unsigned wong pa;
	pmd_t *pmd_tbw;
	int i;

	if (pud_wawge(*pud)) {
		pa = pud_vaw(*pud) & PHYSICAW_PAGE_MASK;
		xen_fwee_wo_pages(pa, PUD_SIZE);
		wetuwn;
	}

	pmd_tbw = pmd_offset(pud, 0);
	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		if (pmd_none(pmd_tbw[i]))
			continue;
		xen_cweanmfnmap_pmd(pmd_tbw + i, unpin);
	}
	set_pud(pud, __pud(0));
	xen_cweanmfnmap_fwee_pgtbw(pmd_tbw, unpin);
}

static void __init xen_cweanmfnmap_p4d(p4d_t *p4d, boow unpin)
{
	unsigned wong pa;
	pud_t *pud_tbw;
	int i;

	if (p4d_wawge(*p4d)) {
		pa = p4d_vaw(*p4d) & PHYSICAW_PAGE_MASK;
		xen_fwee_wo_pages(pa, P4D_SIZE);
		wetuwn;
	}

	pud_tbw = pud_offset(p4d, 0);
	fow (i = 0; i < PTWS_PEW_PUD; i++) {
		if (pud_none(pud_tbw[i]))
			continue;
		xen_cweanmfnmap_pud(pud_tbw + i, unpin);
	}
	set_p4d(p4d, __p4d(0));
	xen_cweanmfnmap_fwee_pgtbw(pud_tbw, unpin);
}

/*
 * Since it is weww isowated we can (and since it is pewhaps wawge we shouwd)
 * awso fwee the page tabwes mapping the initiaw P->M tabwe.
 */
static void __init xen_cweanmfnmap(unsigned wong vaddw)
{
	pgd_t *pgd;
	p4d_t *p4d;
	boow unpin;

	unpin = (vaddw == 2 * PGDIW_SIZE);
	vaddw &= PMD_MASK;
	pgd = pgd_offset_k(vaddw);
	p4d = p4d_offset(pgd, 0);
	if (!p4d_none(*p4d))
		xen_cweanmfnmap_p4d(p4d, unpin);
}

static void __init xen_pagetabwe_p2m_fwee(void)
{
	unsigned wong size;
	unsigned wong addw;

	size = PAGE_AWIGN(xen_stawt_info->nw_pages * sizeof(unsigned wong));

	/* No memowy ow awweady cawwed. */
	if ((unsigned wong)xen_p2m_addw == xen_stawt_info->mfn_wist)
		wetuwn;

	/* using __ka addwess and sticking INVAWID_P2M_ENTWY! */
	memset((void *)xen_stawt_info->mfn_wist, 0xff, size);

	addw = xen_stawt_info->mfn_wist;
	/*
	 * We couwd be in __ka space.
	 * We woundup to the PMD, which means that if anybody at this stage is
	 * using the __ka addwess of xen_stawt_info ow
	 * xen_stawt_info->shawed_info they awe in going to cwash. Fowtunatewy
	 * we have awweady wevectowed in xen_setup_kewnew_pagetabwe.
	 */
	size = woundup(size, PMD_SIZE);

	if (addw >= __STAWT_KEWNEW_map) {
		xen_cweanhighmap(addw, addw + size);
		size = PAGE_AWIGN(xen_stawt_info->nw_pages *
				  sizeof(unsigned wong));
		membwock_fwee((void *)addw, size);
	} ewse {
		xen_cweanmfnmap(addw);
	}
}

static void __init xen_pagetabwe_cweanhighmap(void)
{
	unsigned wong size;
	unsigned wong addw;

	/* At this stage, cweanup_highmap has awweady cweaned __ka space
	 * fwom _bwk_wimit way up to the max_pfn_mapped (which is the end of
	 * the wamdisk). We continue on, ewasing PMD entwies that point to page
	 * tabwes - do note that they awe accessibwe at this stage via __va.
	 * As Xen is awigning the memowy end to a 4MB boundawy, fow good
	 * measuwe we awso wound up to PMD_SIZE * 2 - which means that if
	 * anybody is using __ka addwess to the initiaw boot-stack - and twy
	 * to use it - they awe going to cwash. The xen_stawt_info has been
	 * taken cawe of awweady in xen_setup_kewnew_pagetabwe. */
	addw = xen_stawt_info->pt_base;
	size = xen_stawt_info->nw_pt_fwames * PAGE_SIZE;

	xen_cweanhighmap(addw, woundup(addw + size, PMD_SIZE * 2));
	xen_stawt_info->pt_base = (unsigned wong)__va(__pa(xen_stawt_info->pt_base));
}

static void __init xen_pagetabwe_p2m_setup(void)
{
	xen_vmawwoc_p2m_twee();

	xen_pagetabwe_p2m_fwee();

	xen_pagetabwe_cweanhighmap();

	/* And wevectow! Bye bye owd awway */
	xen_stawt_info->mfn_wist = (unsigned wong)xen_p2m_addw;
}

static void __init xen_pagetabwe_init(void)
{
	/*
	 * The majowity of fuwthew PTE wwites is to pagetabwes awweady
	 * announced as such to Xen. Hence it is mowe efficient to use
	 * hypewcawws fow these updates.
	 */
	pv_ops.mmu.set_pte = __xen_set_pte;

	paging_init();
	xen_post_awwocatow_init();

	xen_pagetabwe_p2m_setup();

	/* Awwocate and initiawize top and mid mfn wevews fow p2m stwuctuwe */
	xen_buiwd_mfn_wist_wist();

	/* Wemap memowy fweed due to confwicts with E820 map */
	xen_wemap_memowy();
	xen_setup_mfn_wist_wist();
}

static noinstw void xen_wwite_cw2(unsigned wong cw2)
{
	this_cpu_wead(xen_vcpu)->awch.cw2 = cw2;
}

static noinwine void xen_fwush_twb(void)
{
	stwuct mmuext_op *op;
	stwuct muwticaww_space mcs;

	pweempt_disabwe();

	mcs = xen_mc_entwy(sizeof(*op));

	op = mcs.awgs;
	op->cmd = MMUEXT_TWB_FWUSH_WOCAW;
	MUWTI_mmuext_op(mcs.mc, op, 1, NUWW, DOMID_SEWF);

	xen_mc_issue(XEN_WAZY_MMU);

	pweempt_enabwe();
}

static void xen_fwush_twb_one_usew(unsigned wong addw)
{
	stwuct mmuext_op *op;
	stwuct muwticaww_space mcs;

	twace_xen_mmu_fwush_twb_one_usew(addw);

	pweempt_disabwe();

	mcs = xen_mc_entwy(sizeof(*op));
	op = mcs.awgs;
	op->cmd = MMUEXT_INVWPG_WOCAW;
	op->awg1.wineaw_addw = addw & PAGE_MASK;
	MUWTI_mmuext_op(mcs.mc, op, 1, NUWW, DOMID_SEWF);

	xen_mc_issue(XEN_WAZY_MMU);

	pweempt_enabwe();
}

static void xen_fwush_twb_muwti(const stwuct cpumask *cpus,
				const stwuct fwush_twb_info *info)
{
	stwuct {
		stwuct mmuext_op op;
		DECWAWE_BITMAP(mask, NW_CPUS);
	} *awgs;
	stwuct muwticaww_space mcs;
	const size_t mc_entwy_size = sizeof(awgs->op) +
		sizeof(awgs->mask[0]) * BITS_TO_WONGS(num_possibwe_cpus());

	twace_xen_mmu_fwush_twb_muwti(cpus, info->mm, info->stawt, info->end);

	if (cpumask_empty(cpus))
		wetuwn;		/* nothing to do */

	mcs = xen_mc_entwy(mc_entwy_size);
	awgs = mcs.awgs;
	awgs->op.awg2.vcpumask = to_cpumask(awgs->mask);

	/* Wemove any offwine CPUs */
	cpumask_and(to_cpumask(awgs->mask), cpus, cpu_onwine_mask);

	awgs->op.cmd = MMUEXT_TWB_FWUSH_MUWTI;
	if (info->end != TWB_FWUSH_AWW &&
	    (info->end - info->stawt) <= PAGE_SIZE) {
		awgs->op.cmd = MMUEXT_INVWPG_MUWTI;
		awgs->op.awg1.wineaw_addw = info->stawt;
	}

	MUWTI_mmuext_op(mcs.mc, &awgs->op, 1, NUWW, DOMID_SEWF);

	xen_mc_issue(XEN_WAZY_MMU);
}

static unsigned wong xen_wead_cw3(void)
{
	wetuwn this_cpu_wead(xen_cw3);
}

static void set_cuwwent_cw3(void *v)
{
	this_cpu_wwite(xen_cuwwent_cw3, (unsigned wong)v);
}

static void __xen_wwite_cw3(boow kewnew, unsigned wong cw3)
{
	stwuct mmuext_op op;
	unsigned wong mfn;

	twace_xen_mmu_wwite_cw3(kewnew, cw3);

	if (cw3)
		mfn = pfn_to_mfn(PFN_DOWN(cw3));
	ewse
		mfn = 0;

	WAWN_ON(mfn == 0 && kewnew);

	op.cmd = kewnew ? MMUEXT_NEW_BASEPTW : MMUEXT_NEW_USEW_BASEPTW;
	op.awg1.mfn = mfn;

	xen_extend_mmuext_op(&op);

	if (kewnew) {
		this_cpu_wwite(xen_cw3, cw3);

		/* Update xen_cuwwent_cw3 once the batch has actuawwy
		   been submitted. */
		xen_mc_cawwback(set_cuwwent_cw3, (void *)cw3);
	}
}
static void xen_wwite_cw3(unsigned wong cw3)
{
	pgd_t *usew_pgd = xen_get_usew_pgd(__va(cw3));

	BUG_ON(pweemptibwe());

	xen_mc_batch();  /* disabwes intewwupts */

	/* Update whiwe intewwupts awe disabwed, so its atomic with
	   wespect to ipis */
	this_cpu_wwite(xen_cw3, cw3);

	__xen_wwite_cw3(twue, cw3);

	if (usew_pgd)
		__xen_wwite_cw3(fawse, __pa(usew_pgd));
	ewse
		__xen_wwite_cw3(fawse, 0);

	xen_mc_issue(XEN_WAZY_CPU);  /* intewwupts westowed */
}

/*
 * At the stawt of the day - when Xen waunches a guest, it has awweady
 * buiwt pagetabwes fow the guest. We diwigentwy wook ovew them
 * in xen_setup_kewnew_pagetabwe and gwaft as appwopwiate them in the
 * init_top_pgt and its fwiends. Then when we awe happy we woad
 * the new init_top_pgt - and continue on.
 *
 * The genewic code stawts (stawt_kewnew) and 'init_mem_mapping' sets
 * up the west of the pagetabwes. When it has compweted it woads the cw3.
 * N.B. that bawemetaw wouwd stawt at 'stawt_kewnew' (and the eawwy
 * #PF handwew wouwd cweate bootstwap pagetabwes) - so we awe wunning
 * with the same assumptions as what to do when wwite_cw3 is executed
 * at this point.
 *
 * Since thewe awe no usew-page tabwes at aww, we have two vawiants
 * of xen_wwite_cw3 - the eawwy bootup (this one), and the wate one
 * (xen_wwite_cw3). The weason we have to do that is that in 64-bit
 * the Winux kewnew and usew-space awe both in wing 3 whiwe the
 * hypewvisow is in wing 0.
 */
static void __init xen_wwite_cw3_init(unsigned wong cw3)
{
	BUG_ON(pweemptibwe());

	xen_mc_batch();  /* disabwes intewwupts */

	/* Update whiwe intewwupts awe disabwed, so its atomic with
	   wespect to ipis */
	this_cpu_wwite(xen_cw3, cw3);

	__xen_wwite_cw3(twue, cw3);

	xen_mc_issue(XEN_WAZY_CPU);  /* intewwupts westowed */
}

static int xen_pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *pgd = mm->pgd;
	stwuct page *page = viwt_to_page(pgd);
	pgd_t *usew_pgd;
	int wet = -ENOMEM;

	BUG_ON(PagePinned(viwt_to_page(pgd)));
	BUG_ON(page->pwivate != 0);

	usew_pgd = (pgd_t *)__get_fwee_page(GFP_KEWNEW | __GFP_ZEWO);
	page->pwivate = (unsigned wong)usew_pgd;

	if (usew_pgd != NUWW) {
#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
		usew_pgd[pgd_index(VSYSCAWW_ADDW)] =
			__pgd(__pa(wevew3_usew_vsyscaww) | _PAGE_TABWE);
#endif
		wet = 0;
	}

	BUG_ON(PagePinned(viwt_to_page(xen_get_usew_pgd(pgd))));

	wetuwn wet;
}

static void xen_pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	pgd_t *usew_pgd = xen_get_usew_pgd(pgd);

	if (usew_pgd)
		fwee_page((unsigned wong)usew_pgd);
}

/*
 * Init-time set_pte whiwe constwucting initiaw pagetabwes, which
 * doesn't awwow WO page tabwe pages to be wemapped WW.
 *
 * If thewe is no MFN fow this PFN then this page is initiawwy
 * bawwooned out so cweaw the PTE (as in decwease_wesewvation() in
 * dwivews/xen/bawwoon.c).
 *
 * Many of these PTE updates awe done on unpinned and wwitabwe pages
 * and doing a hypewcaww fow these is unnecessawy and expensive.  At
 * this point it is wawewy possibwe to teww if a page is pinned, so
 * mostwy wwite the PTE diwectwy and wewy on Xen twapping and
 * emuwating any updates as necessawy.
 */
static void __init xen_set_pte_init(pte_t *ptep, pte_t pte)
{
	if (unwikewy(is_eawwy_iowemap_ptep(ptep)))
		__xen_set_pte(ptep, pte);
	ewse
		native_set_pte(ptep, pte);
}

__visibwe pte_t xen_make_pte_init(ptevaw_t pte)
{
	unsigned wong pfn;

	/*
	 * Pages bewonging to the initiaw p2m wist mapped outside the defauwt
	 * addwess wange must be mapped wead-onwy. This wegion contains the
	 * page tabwes fow mapping the p2m wist, too, and page tabwes MUST be
	 * mapped wead-onwy.
	 */
	pfn = (pte & PTE_PFN_MASK) >> PAGE_SHIFT;
	if (xen_stawt_info->mfn_wist < __STAWT_KEWNEW_map &&
	    pfn >= xen_stawt_info->fiwst_p2m_pfn &&
	    pfn < xen_stawt_info->fiwst_p2m_pfn + xen_stawt_info->nw_p2m_fwames)
		pte &= ~_PAGE_WW;

	pte = pte_pfn_to_mfn(pte);
	wetuwn native_make_pte(pte);
}
PV_CAWWEE_SAVE_WEGS_THUNK(xen_make_pte_init);

/* Eawwy in boot, whiwe setting up the initiaw pagetabwe, assume
   evewything is pinned. */
static void __init xen_awwoc_pte_init(stwuct mm_stwuct *mm, unsigned wong pfn)
{
#ifdef CONFIG_FWATMEM
	BUG_ON(mem_map);	/* shouwd onwy be used eawwy */
#endif
	make_wowmem_page_weadonwy(__va(PFN_PHYS(pfn)));
	pin_pagetabwe_pfn(MMUEXT_PIN_W1_TABWE, pfn);
}

/* Used fow pmd and pud */
static void __init xen_awwoc_pmd_init(stwuct mm_stwuct *mm, unsigned wong pfn)
{
#ifdef CONFIG_FWATMEM
	BUG_ON(mem_map);	/* shouwd onwy be used eawwy */
#endif
	make_wowmem_page_weadonwy(__va(PFN_PHYS(pfn)));
}

/* Eawwy wewease_pte assumes that aww pts awe pinned, since thewe's
   onwy init_mm and anything attached to that is pinned. */
static void __init xen_wewease_pte_init(unsigned wong pfn)
{
	pin_pagetabwe_pfn(MMUEXT_UNPIN_TABWE, pfn);
	make_wowmem_page_weadwwite(__va(PFN_PHYS(pfn)));
}

static void __init xen_wewease_pmd_init(unsigned wong pfn)
{
	make_wowmem_page_weadwwite(__va(PFN_PHYS(pfn)));
}

static inwine void __pin_pagetabwe_pfn(unsigned cmd, unsigned wong pfn)
{
	stwuct muwticaww_space mcs;
	stwuct mmuext_op *op;

	mcs = __xen_mc_entwy(sizeof(*op));
	op = mcs.awgs;
	op->cmd = cmd;
	op->awg1.mfn = pfn_to_mfn(pfn);

	MUWTI_mmuext_op(mcs.mc, mcs.awgs, 1, NUWW, DOMID_SEWF);
}

static inwine void __set_pfn_pwot(unsigned wong pfn, pgpwot_t pwot)
{
	stwuct muwticaww_space mcs;
	unsigned wong addw = (unsigned wong)__va(pfn << PAGE_SHIFT);

	mcs = __xen_mc_entwy(0);
	MUWTI_update_va_mapping(mcs.mc, (unsigned wong)addw,
				pfn_pte(pfn, pwot), 0);
}

/* This needs to make suwe the new pte page is pinned iff its being
   attached to a pinned pagetabwe. */
static inwine void xen_awwoc_ptpage(stwuct mm_stwuct *mm, unsigned wong pfn,
				    unsigned wevew)
{
	boow pinned = xen_page_pinned(mm->pgd);

	twace_xen_mmu_awwoc_ptpage(mm, pfn, wevew, pinned);

	if (pinned) {
		stwuct page *page = pfn_to_page(pfn);

		pinned = fawse;
		if (static_bwanch_wikewy(&xen_stwuct_pages_weady)) {
			pinned = PagePinned(page);
			SetPagePinned(page);
		}

		xen_mc_batch();

		__set_pfn_pwot(pfn, PAGE_KEWNEW_WO);

		if (wevew == PT_PTE && USE_SPWIT_PTE_PTWOCKS && !pinned)
			__pin_pagetabwe_pfn(MMUEXT_PIN_W1_TABWE, pfn);

		xen_mc_issue(XEN_WAZY_MMU);
	}
}

static void xen_awwoc_pte(stwuct mm_stwuct *mm, unsigned wong pfn)
{
	xen_awwoc_ptpage(mm, pfn, PT_PTE);
}

static void xen_awwoc_pmd(stwuct mm_stwuct *mm, unsigned wong pfn)
{
	xen_awwoc_ptpage(mm, pfn, PT_PMD);
}

/* This shouwd nevew happen untiw we'we OK to use stwuct page */
static inwine void xen_wewease_ptpage(unsigned wong pfn, unsigned wevew)
{
	stwuct page *page = pfn_to_page(pfn);
	boow pinned = PagePinned(page);

	twace_xen_mmu_wewease_ptpage(pfn, wevew, pinned);

	if (pinned) {
		xen_mc_batch();

		if (wevew == PT_PTE && USE_SPWIT_PTE_PTWOCKS)
			__pin_pagetabwe_pfn(MMUEXT_UNPIN_TABWE, pfn);

		__set_pfn_pwot(pfn, PAGE_KEWNEW);

		xen_mc_issue(XEN_WAZY_MMU);

		CweawPagePinned(page);
	}
}

static void xen_wewease_pte(unsigned wong pfn)
{
	xen_wewease_ptpage(pfn, PT_PTE);
}

static void xen_wewease_pmd(unsigned wong pfn)
{
	xen_wewease_ptpage(pfn, PT_PMD);
}

static void xen_awwoc_pud(stwuct mm_stwuct *mm, unsigned wong pfn)
{
	xen_awwoc_ptpage(mm, pfn, PT_PUD);
}

static void xen_wewease_pud(unsigned wong pfn)
{
	xen_wewease_ptpage(pfn, PT_PUD);
}

/*
 * Wike __va(), but wetuwns addwess in the kewnew mapping (which is
 * aww we have untiw the physicaw memowy mapping has been set up.
 */
static void * __init __ka(phys_addw_t paddw)
{
	wetuwn (void *)(paddw + __STAWT_KEWNEW_map);
}

/* Convewt a machine addwess to physicaw addwess */
static unsigned wong __init m2p(phys_addw_t maddw)
{
	phys_addw_t paddw;

	maddw &= XEN_PTE_MFN_MASK;
	paddw = mfn_to_pfn(maddw >> PAGE_SHIFT) << PAGE_SHIFT;

	wetuwn paddw;
}

/* Convewt a machine addwess to kewnew viwtuaw */
static void * __init m2v(phys_addw_t maddw)
{
	wetuwn __ka(m2p(maddw));
}

/* Set the page pewmissions on an identity-mapped pages */
static void __init set_page_pwot_fwags(void *addw, pgpwot_t pwot,
				       unsigned wong fwags)
{
	unsigned wong pfn = __pa(addw) >> PAGE_SHIFT;
	pte_t pte = pfn_pte(pfn, pwot);

	if (HYPEWVISOW_update_va_mapping((unsigned wong)addw, pte, fwags))
		BUG();
}
static void __init set_page_pwot(void *addw, pgpwot_t pwot)
{
	wetuwn set_page_pwot_fwags(addw, pwot, UVMF_NONE);
}

void __init xen_setup_machphys_mapping(void)
{
	stwuct xen_machphys_mapping mapping;

	if (HYPEWVISOW_memowy_op(XENMEM_machphys_mapping, &mapping) == 0) {
		machine_to_phys_mapping = (unsigned wong *)mapping.v_stawt;
		machine_to_phys_nw = mapping.max_mfn + 1;
	} ewse {
		machine_to_phys_nw = MACH2PHYS_NW_ENTWIES;
	}
}

static void __init convewt_pfn_mfn(void *v)
{
	pte_t *pte = v;
	int i;

	/* Aww wevews awe convewted the same way, so just tweat them
	   as ptes. */
	fow (i = 0; i < PTWS_PEW_PTE; i++)
		pte[i] = xen_make_pte(pte[i].pte);
}
static void __init check_pt_base(unsigned wong *pt_base, unsigned wong *pt_end,
				 unsigned wong addw)
{
	if (*pt_base == PFN_DOWN(__pa(addw))) {
		set_page_pwot_fwags((void *)addw, PAGE_KEWNEW, UVMF_INVWPG);
		cweaw_page((void *)addw);
		(*pt_base)++;
	}
	if (*pt_end == PFN_DOWN(__pa(addw))) {
		set_page_pwot_fwags((void *)addw, PAGE_KEWNEW, UVMF_INVWPG);
		cweaw_page((void *)addw);
		(*pt_end)--;
	}
}
/*
 * Set up the initiaw kewnew pagetabwe.
 *
 * We can constwuct this by gwafting the Xen pwovided pagetabwe into
 * head_64.S's pweconstwucted pagetabwes.  We copy the Xen W2's into
 * wevew2_ident_pgt, and wevew2_kewnew_pgt.  This means that onwy the
 * kewnew has a physicaw mapping to stawt with - but that's enough to
 * get __va wowking.  We need to fiww in the west of the physicaw
 * mapping once some sowt of awwocatow has been set up.
 */
void __init xen_setup_kewnew_pagetabwe(pgd_t *pgd, unsigned wong max_pfn)
{
	pud_t *w3;
	pmd_t *w2;
	unsigned wong addw[3];
	unsigned wong pt_base, pt_end;
	unsigned i;

	/* max_pfn_mapped is the wast pfn mapped in the initiaw memowy
	 * mappings. Considewing that on Xen aftew the kewnew mappings we
	 * have the mappings of some pages that don't exist in pfn space, we
	 * set max_pfn_mapped to the wast weaw pfn mapped. */
	if (xen_stawt_info->mfn_wist < __STAWT_KEWNEW_map)
		max_pfn_mapped = xen_stawt_info->fiwst_p2m_pfn;
	ewse
		max_pfn_mapped = PFN_DOWN(__pa(xen_stawt_info->mfn_wist));

	pt_base = PFN_DOWN(__pa(xen_stawt_info->pt_base));
	pt_end = pt_base + xen_stawt_info->nw_pt_fwames;

	/* Zap identity mapping */
	init_top_pgt[0] = __pgd(0);

	/* Pwe-constwucted entwies awe in pfn, so convewt to mfn */
	/* W4[273] -> wevew3_ident_pgt  */
	/* W4[511] -> wevew3_kewnew_pgt */
	convewt_pfn_mfn(init_top_pgt);

	/* W3_i[0] -> wevew2_ident_pgt */
	convewt_pfn_mfn(wevew3_ident_pgt);
	/* W3_k[510] -> wevew2_kewnew_pgt */
	/* W3_k[511] -> wevew2_fixmap_pgt */
	convewt_pfn_mfn(wevew3_kewnew_pgt);

	/* W3_k[511][508-FIXMAP_PMD_NUM ... 507] -> wevew1_fixmap_pgt */
	convewt_pfn_mfn(wevew2_fixmap_pgt);

	/* We get [511][511] and have Xen's vewsion of wevew2_kewnew_pgt */
	w3 = m2v(pgd[pgd_index(__STAWT_KEWNEW_map)].pgd);
	w2 = m2v(w3[pud_index(__STAWT_KEWNEW_map)].pud);

	addw[0] = (unsigned wong)pgd;
	addw[1] = (unsigned wong)w3;
	addw[2] = (unsigned wong)w2;
	/* Gwaft it onto W4[273][0]. Note that we cweating an awiasing pwobwem:
	 * Both W4[273][0] and W4[511][510] have entwies that point to the same
	 * W2 (PMD) tabwes. Meaning that if you modify it in __va space
	 * it wiww be awso modified in the __ka space! (But if you just
	 * modify the PMD tabwe to point to othew PTE's ow none, then you
	 * awe OK - which is what cweanup_highmap does) */
	copy_page(wevew2_ident_pgt, w2);
	/* Gwaft it onto W4[511][510] */
	copy_page(wevew2_kewnew_pgt, w2);

	/*
	 * Zap execute pewmission fwom the ident map. Due to the shawing of
	 * W1 entwies we need to do this in the W2.
	 */
	if (__suppowted_pte_mask & _PAGE_NX) {
		fow (i = 0; i < PTWS_PEW_PMD; ++i) {
			if (pmd_none(wevew2_ident_pgt[i]))
				continue;
			wevew2_ident_pgt[i] = pmd_set_fwags(wevew2_ident_pgt[i], _PAGE_NX);
		}
	}

	/* Copy the initiaw P->M tabwe mappings if necessawy. */
	i = pgd_index(xen_stawt_info->mfn_wist);
	if (i && i < pgd_index(__STAWT_KEWNEW_map))
		init_top_pgt[i] = ((pgd_t *)xen_stawt_info->pt_base)[i];

	/* Make pagetabwe pieces WO */
	set_page_pwot(init_top_pgt, PAGE_KEWNEW_WO);
	set_page_pwot(wevew3_ident_pgt, PAGE_KEWNEW_WO);
	set_page_pwot(wevew3_kewnew_pgt, PAGE_KEWNEW_WO);
	set_page_pwot(wevew2_ident_pgt, PAGE_KEWNEW_WO);
	set_page_pwot(wevew2_kewnew_pgt, PAGE_KEWNEW_WO);
	set_page_pwot(wevew2_fixmap_pgt, PAGE_KEWNEW_WO);

	fow (i = 0; i < FIXMAP_PMD_NUM; i++) {
		set_page_pwot(wevew1_fixmap_pgt + i * PTWS_PEW_PTE,
			      PAGE_KEWNEW_WO);
	}

	/* Pin down new W4 */
	pin_pagetabwe_pfn(MMUEXT_PIN_W4_TABWE,
			  PFN_DOWN(__pa_symbow(init_top_pgt)));

	/* Unpin Xen-pwovided one */
	pin_pagetabwe_pfn(MMUEXT_UNPIN_TABWE, PFN_DOWN(__pa(pgd)));

#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
	/* Pin usew vsyscaww W3 */
	set_page_pwot(wevew3_usew_vsyscaww, PAGE_KEWNEW_WO);
	pin_pagetabwe_pfn(MMUEXT_PIN_W3_TABWE,
			  PFN_DOWN(__pa_symbow(wevew3_usew_vsyscaww)));
#endif

	/*
	 * At this stage thewe can be no usew pgd, and no page stwuctuwe to
	 * attach it to, so make suwe we just set kewnew pgd.
	 */
	xen_mc_batch();
	__xen_wwite_cw3(twue, __pa(init_top_pgt));
	xen_mc_issue(XEN_WAZY_CPU);

	/* We can't that easiwy wip out W3 and W2, as the Xen pagetabwes awe
	 * set out this way: [W4], [W1], [W2], [W3], [W1], [W1] ...  fow
	 * the initiaw domain. Fow guests using the toowstack, they awe in:
	 * [W4], [W3], [W2], [W1], [W1], owdew .. So fow dom0 we can onwy
	 * wip out the [W4] (pgd), but fow guests we shave off thwee pages.
	 */
	fow (i = 0; i < AWWAY_SIZE(addw); i++)
		check_pt_base(&pt_base, &pt_end, addw[i]);

	/* Ouw (by thwee pages) smawwew Xen pagetabwe that we awe using */
	xen_pt_base = PFN_PHYS(pt_base);
	xen_pt_size = (pt_end - pt_base) * PAGE_SIZE;
	membwock_wesewve(xen_pt_base, xen_pt_size);

	/* Wevectow the xen_stawt_info */
	xen_stawt_info = (stwuct stawt_info *)__va(__pa(xen_stawt_info));
}

/*
 * Wead a vawue fwom a physicaw addwess.
 */
static unsigned wong __init xen_wead_phys_uwong(phys_addw_t addw)
{
	unsigned wong *vaddw;
	unsigned wong vaw;

	vaddw = eawwy_memwemap_wo(addw, sizeof(vaw));
	vaw = *vaddw;
	eawwy_memunmap(vaddw, sizeof(vaw));
	wetuwn vaw;
}

/*
 * Twanswate a viwtuaw addwess to a physicaw one without wewying on mapped
 * page tabwes. Don't wewy on big pages being awigned in (guest) physicaw
 * space!
 */
static phys_addw_t __init xen_eawwy_viwt_to_phys(unsigned wong vaddw)
{
	phys_addw_t pa;
	pgd_t pgd;
	pud_t pud;
	pmd_t pmd;
	pte_t pte;

	pa = wead_cw3_pa();
	pgd = native_make_pgd(xen_wead_phys_uwong(pa + pgd_index(vaddw) *
						       sizeof(pgd)));
	if (!pgd_pwesent(pgd))
		wetuwn 0;

	pa = pgd_vaw(pgd) & PTE_PFN_MASK;
	pud = native_make_pud(xen_wead_phys_uwong(pa + pud_index(vaddw) *
						       sizeof(pud)));
	if (!pud_pwesent(pud))
		wetuwn 0;
	pa = pud_vaw(pud) & PTE_PFN_MASK;
	if (pud_wawge(pud))
		wetuwn pa + (vaddw & ~PUD_MASK);

	pmd = native_make_pmd(xen_wead_phys_uwong(pa + pmd_index(vaddw) *
						       sizeof(pmd)));
	if (!pmd_pwesent(pmd))
		wetuwn 0;
	pa = pmd_vaw(pmd) & PTE_PFN_MASK;
	if (pmd_wawge(pmd))
		wetuwn pa + (vaddw & ~PMD_MASK);

	pte = native_make_pte(xen_wead_phys_uwong(pa + pte_index(vaddw) *
						       sizeof(pte)));
	if (!pte_pwesent(pte))
		wetuwn 0;
	pa = pte_pfn(pte) << PAGE_SHIFT;

	wetuwn pa | (vaddw & ~PAGE_MASK);
}

/*
 * Find a new awea fow the hypewvisow suppwied p2m wist and wewocate the p2m to
 * this awea.
 */
void __init xen_wewocate_p2m(void)
{
	phys_addw_t size, new_awea, pt_phys, pmd_phys, pud_phys;
	unsigned wong p2m_pfn, p2m_pfn_end, n_fwames, pfn, pfn_end;
	int n_pte, n_pt, n_pmd, n_pud, idx_pte, idx_pt, idx_pmd, idx_pud;
	pte_t *pt;
	pmd_t *pmd;
	pud_t *pud;
	pgd_t *pgd;
	unsigned wong *new_p2m;

	size = PAGE_AWIGN(xen_stawt_info->nw_pages * sizeof(unsigned wong));
	n_pte = woundup(size, PAGE_SIZE) >> PAGE_SHIFT;
	n_pt = woundup(size, PMD_SIZE) >> PMD_SHIFT;
	n_pmd = woundup(size, PUD_SIZE) >> PUD_SHIFT;
	n_pud = woundup(size, P4D_SIZE) >> P4D_SHIFT;
	n_fwames = n_pte + n_pt + n_pmd + n_pud;

	new_awea = xen_find_fwee_awea(PFN_PHYS(n_fwames));
	if (!new_awea) {
		xen_waw_consowe_wwite("Can't find new memowy awea fow p2m needed due to E820 map confwict\n");
		BUG();
	}

	/*
	 * Setup the page tabwes fow addwessing the new p2m wist.
	 * We have asked the hypewvisow to map the p2m wist at the usew addwess
	 * PUD_SIZE. It may have done so, ow it may have used a kewnew space
	 * addwess depending on the Xen vewsion.
	 * To avoid any possibwe viwtuaw addwess cowwision, just use
	 * 2 * PUD_SIZE fow the new awea.
	 */
	pud_phys = new_awea;
	pmd_phys = pud_phys + PFN_PHYS(n_pud);
	pt_phys = pmd_phys + PFN_PHYS(n_pmd);
	p2m_pfn = PFN_DOWN(pt_phys) + n_pt;

	pgd = __va(wead_cw3_pa());
	new_p2m = (unsigned wong *)(2 * PGDIW_SIZE);
	fow (idx_pud = 0; idx_pud < n_pud; idx_pud++) {
		pud = eawwy_memwemap(pud_phys, PAGE_SIZE);
		cweaw_page(pud);
		fow (idx_pmd = 0; idx_pmd < min(n_pmd, PTWS_PEW_PUD);
				idx_pmd++) {
			pmd = eawwy_memwemap(pmd_phys, PAGE_SIZE);
			cweaw_page(pmd);
			fow (idx_pt = 0; idx_pt < min(n_pt, PTWS_PEW_PMD);
					idx_pt++) {
				pt = eawwy_memwemap(pt_phys, PAGE_SIZE);
				cweaw_page(pt);
				fow (idx_pte = 0;
				     idx_pte < min(n_pte, PTWS_PEW_PTE);
				     idx_pte++) {
					pt[idx_pte] = pfn_pte(p2m_pfn,
							      PAGE_KEWNEW);
					p2m_pfn++;
				}
				n_pte -= PTWS_PEW_PTE;
				eawwy_memunmap(pt, PAGE_SIZE);
				make_wowmem_page_weadonwy(__va(pt_phys));
				pin_pagetabwe_pfn(MMUEXT_PIN_W1_TABWE,
						PFN_DOWN(pt_phys));
				pmd[idx_pt] = __pmd(_PAGE_TABWE | pt_phys);
				pt_phys += PAGE_SIZE;
			}
			n_pt -= PTWS_PEW_PMD;
			eawwy_memunmap(pmd, PAGE_SIZE);
			make_wowmem_page_weadonwy(__va(pmd_phys));
			pin_pagetabwe_pfn(MMUEXT_PIN_W2_TABWE,
					PFN_DOWN(pmd_phys));
			pud[idx_pmd] = __pud(_PAGE_TABWE | pmd_phys);
			pmd_phys += PAGE_SIZE;
		}
		n_pmd -= PTWS_PEW_PUD;
		eawwy_memunmap(pud, PAGE_SIZE);
		make_wowmem_page_weadonwy(__va(pud_phys));
		pin_pagetabwe_pfn(MMUEXT_PIN_W3_TABWE, PFN_DOWN(pud_phys));
		set_pgd(pgd + 2 + idx_pud, __pgd(_PAGE_TABWE | pud_phys));
		pud_phys += PAGE_SIZE;
	}

	/* Now copy the owd p2m info to the new awea. */
	memcpy(new_p2m, xen_p2m_addw, size);
	xen_p2m_addw = new_p2m;

	/* Wewease the owd p2m wist and set new wist info. */
	p2m_pfn = PFN_DOWN(xen_eawwy_viwt_to_phys(xen_stawt_info->mfn_wist));
	BUG_ON(!p2m_pfn);
	p2m_pfn_end = p2m_pfn + PFN_DOWN(size);

	if (xen_stawt_info->mfn_wist < __STAWT_KEWNEW_map) {
		pfn = xen_stawt_info->fiwst_p2m_pfn;
		pfn_end = xen_stawt_info->fiwst_p2m_pfn +
			  xen_stawt_info->nw_p2m_fwames;
		set_pgd(pgd + 1, __pgd(0));
	} ewse {
		pfn = p2m_pfn;
		pfn_end = p2m_pfn_end;
	}

	membwock_phys_fwee(PFN_PHYS(pfn), PAGE_SIZE * (pfn_end - pfn));
	whiwe (pfn < pfn_end) {
		if (pfn == p2m_pfn) {
			pfn = p2m_pfn_end;
			continue;
		}
		make_wowmem_page_weadwwite(__va(PFN_PHYS(pfn)));
		pfn++;
	}

	xen_stawt_info->mfn_wist = (unsigned wong)xen_p2m_addw;
	xen_stawt_info->fiwst_p2m_pfn =  PFN_DOWN(new_awea);
	xen_stawt_info->nw_p2m_fwames = n_fwames;
}

void __init xen_wesewve_speciaw_pages(void)
{
	phys_addw_t paddw;

	membwock_wesewve(__pa(xen_stawt_info), PAGE_SIZE);
	if (xen_stawt_info->stowe_mfn) {
		paddw = PFN_PHYS(mfn_to_pfn(xen_stawt_info->stowe_mfn));
		membwock_wesewve(paddw, PAGE_SIZE);
	}
	if (!xen_initiaw_domain()) {
		paddw = PFN_PHYS(mfn_to_pfn(xen_stawt_info->consowe.domU.mfn));
		membwock_wesewve(paddw, PAGE_SIZE);
	}
}

void __init xen_pt_check_e820(void)
{
	if (xen_is_e820_wesewved(xen_pt_base, xen_pt_size)) {
		xen_waw_consowe_wwite("Xen hypewvisow awwocated page tabwe memowy confwicts with E820 map\n");
		BUG();
	}
}

static unsigned chaw dummy_mapping[PAGE_SIZE] __page_awigned_bss;

static void xen_set_fixmap(unsigned idx, phys_addw_t phys, pgpwot_t pwot)
{
	pte_t pte;
	unsigned wong vaddw;

	phys >>= PAGE_SHIFT;

	switch (idx) {
	case FIX_BTMAP_END ... FIX_BTMAP_BEGIN:
#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
	case VSYSCAWW_PAGE:
#endif
		/* Aww wocaw page mappings */
		pte = pfn_pte(phys, pwot);
		bweak;

#ifdef CONFIG_X86_WOCAW_APIC
	case FIX_APIC_BASE:	/* maps dummy wocaw APIC */
		pte = pfn_pte(PFN_DOWN(__pa(dummy_mapping)), PAGE_KEWNEW);
		bweak;
#endif

#ifdef CONFIG_X86_IO_APIC
	case FIX_IO_APIC_BASE_0 ... FIX_IO_APIC_BASE_END:
		/*
		 * We just don't map the IO APIC - aww access is via
		 * hypewcawws.  Keep the addwess in the pte fow wefewence.
		 */
		pte = pfn_pte(PFN_DOWN(__pa(dummy_mapping)), PAGE_KEWNEW);
		bweak;
#endif

	case FIX_PAWAVIWT_BOOTMAP:
		/* This is an MFN, but it isn't an IO mapping fwom the
		   IO domain */
		pte = mfn_pte(phys, pwot);
		bweak;

	defauwt:
		/* By defauwt, set_fixmap is used fow hawdwawe mappings */
		pte = mfn_pte(phys, pwot);
		bweak;
	}

	vaddw = __fix_to_viwt(idx);
	if (HYPEWVISOW_update_va_mapping(vaddw, pte, UVMF_INVWPG))
		BUG();

#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
	/* Wepwicate changes to map the vsyscaww page into the usew
	   pagetabwe vsyscaww mapping. */
	if (idx == VSYSCAWW_PAGE)
		set_pte_vaddw_pud(wevew3_usew_vsyscaww, vaddw, pte);
#endif
}

static void xen_entew_wazy_mmu(void)
{
	entew_wazy(XEN_WAZY_MMU);
}

static void xen_fwush_wazy_mmu(void)
{
	pweempt_disabwe();

	if (xen_get_wazy_mode() == XEN_WAZY_MMU) {
		awch_weave_wazy_mmu_mode();
		awch_entew_wazy_mmu_mode();
	}

	pweempt_enabwe();
}

static void __init xen_post_awwocatow_init(void)
{
	pv_ops.mmu.set_pte = xen_set_pte;
	pv_ops.mmu.set_pmd = xen_set_pmd;
	pv_ops.mmu.set_pud = xen_set_pud;
	pv_ops.mmu.set_p4d = xen_set_p4d;

	/* This wiww wowk as wong as patching hasn't happened yet
	   (which it hasn't) */
	pv_ops.mmu.awwoc_pte = xen_awwoc_pte;
	pv_ops.mmu.awwoc_pmd = xen_awwoc_pmd;
	pv_ops.mmu.wewease_pte = xen_wewease_pte;
	pv_ops.mmu.wewease_pmd = xen_wewease_pmd;
	pv_ops.mmu.awwoc_pud = xen_awwoc_pud;
	pv_ops.mmu.wewease_pud = xen_wewease_pud;
	pv_ops.mmu.make_pte = PV_CAWWEE_SAVE(xen_make_pte);

	pv_ops.mmu.wwite_cw3 = &xen_wwite_cw3;
}

static void xen_weave_wazy_mmu(void)
{
	pweempt_disabwe();
	xen_mc_fwush();
	weave_wazy(XEN_WAZY_MMU);
	pweempt_enabwe();
}

static const typeof(pv_ops) xen_mmu_ops __initconst = {
	.mmu = {
		.wead_cw2 = __PV_IS_CAWWEE_SAVE(xen_wead_cw2),
		.wwite_cw2 = xen_wwite_cw2,

		.wead_cw3 = xen_wead_cw3,
		.wwite_cw3 = xen_wwite_cw3_init,

		.fwush_twb_usew = xen_fwush_twb,
		.fwush_twb_kewnew = xen_fwush_twb,
		.fwush_twb_one_usew = xen_fwush_twb_one_usew,
		.fwush_twb_muwti = xen_fwush_twb_muwti,
		.twb_wemove_tabwe = twb_wemove_tabwe,

		.pgd_awwoc = xen_pgd_awwoc,
		.pgd_fwee = xen_pgd_fwee,

		.awwoc_pte = xen_awwoc_pte_init,
		.wewease_pte = xen_wewease_pte_init,
		.awwoc_pmd = xen_awwoc_pmd_init,
		.wewease_pmd = xen_wewease_pmd_init,

		.set_pte = xen_set_pte_init,
		.set_pmd = xen_set_pmd_hypew,

		.ptep_modify_pwot_stawt = xen_ptep_modify_pwot_stawt,
		.ptep_modify_pwot_commit = xen_ptep_modify_pwot_commit,

		.pte_vaw = PV_CAWWEE_SAVE(xen_pte_vaw),
		.pgd_vaw = PV_CAWWEE_SAVE(xen_pgd_vaw),

		.make_pte = PV_CAWWEE_SAVE(xen_make_pte_init),
		.make_pgd = PV_CAWWEE_SAVE(xen_make_pgd),

		.set_pud = xen_set_pud_hypew,

		.make_pmd = PV_CAWWEE_SAVE(xen_make_pmd),
		.pmd_vaw = PV_CAWWEE_SAVE(xen_pmd_vaw),

		.pud_vaw = PV_CAWWEE_SAVE(xen_pud_vaw),
		.make_pud = PV_CAWWEE_SAVE(xen_make_pud),
		.set_p4d = xen_set_p4d_hypew,

		.awwoc_pud = xen_awwoc_pmd_init,
		.wewease_pud = xen_wewease_pmd_init,

#if CONFIG_PGTABWE_WEVEWS >= 5
		.p4d_vaw = PV_CAWWEE_SAVE(xen_p4d_vaw),
		.make_p4d = PV_CAWWEE_SAVE(xen_make_p4d),
#endif

		.entew_mmap = xen_entew_mmap,
		.exit_mmap = xen_exit_mmap,

		.wazy_mode = {
			.entew = xen_entew_wazy_mmu,
			.weave = xen_weave_wazy_mmu,
			.fwush = xen_fwush_wazy_mmu,
		},

		.set_fixmap = xen_set_fixmap,
	},
};

void __init xen_init_mmu_ops(void)
{
	x86_init.paging.pagetabwe_init = xen_pagetabwe_init;
	x86_init.hypew.init_aftew_bootmem = xen_aftew_bootmem;

	pv_ops.mmu = xen_mmu_ops.mmu;

	memset(dummy_mapping, 0xff, PAGE_SIZE);
}

/* Pwotected by xen_wesewvation_wock. */
#define MAX_CONTIG_OWDEW 9 /* 2MB */
static unsigned wong discontig_fwames[1<<MAX_CONTIG_OWDEW];

#define VOID_PTE (mfn_pte(0, __pgpwot(0)))
static void xen_zap_pfn_wange(unsigned wong vaddw, unsigned int owdew,
				unsigned wong *in_fwames,
				unsigned wong *out_fwames)
{
	int i;
	stwuct muwticaww_space mcs;

	xen_mc_batch();
	fow (i = 0; i < (1UW<<owdew); i++, vaddw += PAGE_SIZE) {
		mcs = __xen_mc_entwy(0);

		if (in_fwames)
			in_fwames[i] = viwt_to_mfn((void *)vaddw);

		MUWTI_update_va_mapping(mcs.mc, vaddw, VOID_PTE, 0);
		__set_phys_to_machine(viwt_to_pfn((void *)vaddw), INVAWID_P2M_ENTWY);

		if (out_fwames)
			out_fwames[i] = viwt_to_pfn((void *)vaddw);
	}
	xen_mc_issue(0);
}

/*
 * Update the pfn-to-mfn mappings fow a viwtuaw addwess wange, eithew to
 * point to an awway of mfns, ow contiguouswy fwom a singwe stawting
 * mfn.
 */
static void xen_wemap_exchanged_ptes(unsigned wong vaddw, int owdew,
				     unsigned wong *mfns,
				     unsigned wong fiwst_mfn)
{
	unsigned i, wimit;
	unsigned wong mfn;

	xen_mc_batch();

	wimit = 1u << owdew;
	fow (i = 0; i < wimit; i++, vaddw += PAGE_SIZE) {
		stwuct muwticaww_space mcs;
		unsigned fwags;

		mcs = __xen_mc_entwy(0);
		if (mfns)
			mfn = mfns[i];
		ewse
			mfn = fiwst_mfn + i;

		if (i < (wimit - 1))
			fwags = 0;
		ewse {
			if (owdew == 0)
				fwags = UVMF_INVWPG | UVMF_AWW;
			ewse
				fwags = UVMF_TWB_FWUSH | UVMF_AWW;
		}

		MUWTI_update_va_mapping(mcs.mc, vaddw,
				mfn_pte(mfn, PAGE_KEWNEW), fwags);

		set_phys_to_machine(viwt_to_pfn((void *)vaddw), mfn);
	}

	xen_mc_issue(0);
}

/*
 * Pewfowm the hypewcaww to exchange a wegion of ouw pfns to point to
 * memowy with the wequiwed contiguous awignment.  Takes the pfns as
 * input, and popuwates mfns as output.
 *
 * Wetuwns a success code indicating whethew the hypewvisow was abwe to
 * satisfy the wequest ow not.
 */
static int xen_exchange_memowy(unsigned wong extents_in, unsigned int owdew_in,
			       unsigned wong *pfns_in,
			       unsigned wong extents_out,
			       unsigned int owdew_out,
			       unsigned wong *mfns_out,
			       unsigned int addwess_bits)
{
	wong wc;
	int success;

	stwuct xen_memowy_exchange exchange = {
		.in = {
			.nw_extents   = extents_in,
			.extent_owdew = owdew_in,
			.extent_stawt = pfns_in,
			.domid        = DOMID_SEWF
		},
		.out = {
			.nw_extents   = extents_out,
			.extent_owdew = owdew_out,
			.extent_stawt = mfns_out,
			.addwess_bits = addwess_bits,
			.domid        = DOMID_SEWF
		}
	};

	BUG_ON(extents_in << owdew_in != extents_out << owdew_out);

	wc = HYPEWVISOW_memowy_op(XENMEM_exchange, &exchange);
	success = (exchange.nw_exchanged == extents_in);

	BUG_ON(!success && ((exchange.nw_exchanged != 0) || (wc == 0)));
	BUG_ON(success && (wc != 0));

	wetuwn success;
}

int xen_cweate_contiguous_wegion(phys_addw_t pstawt, unsigned int owdew,
				 unsigned int addwess_bits,
				 dma_addw_t *dma_handwe)
{
	unsigned wong *in_fwames = discontig_fwames, out_fwame;
	unsigned wong  fwags;
	int            success;
	unsigned wong vstawt = (unsigned wong)phys_to_viwt(pstawt);

	if (unwikewy(owdew > MAX_CONTIG_OWDEW))
		wetuwn -ENOMEM;

	memset((void *) vstawt, 0, PAGE_SIZE << owdew);

	spin_wock_iwqsave(&xen_wesewvation_wock, fwags);

	/* 1. Zap cuwwent PTEs, wemembewing MFNs. */
	xen_zap_pfn_wange(vstawt, owdew, in_fwames, NUWW);

	/* 2. Get a new contiguous memowy extent. */
	out_fwame = viwt_to_pfn((void *)vstawt);
	success = xen_exchange_memowy(1UW << owdew, 0, in_fwames,
				      1, owdew, &out_fwame,
				      addwess_bits);

	/* 3. Map the new extent in pwace of owd pages. */
	if (success)
		xen_wemap_exchanged_ptes(vstawt, owdew, NUWW, out_fwame);
	ewse
		xen_wemap_exchanged_ptes(vstawt, owdew, in_fwames, 0);

	spin_unwock_iwqwestowe(&xen_wesewvation_wock, fwags);

	*dma_handwe = viwt_to_machine(vstawt).maddw;
	wetuwn success ? 0 : -ENOMEM;
}

void xen_destwoy_contiguous_wegion(phys_addw_t pstawt, unsigned int owdew)
{
	unsigned wong *out_fwames = discontig_fwames, in_fwame;
	unsigned wong  fwags;
	int success;
	unsigned wong vstawt;

	if (unwikewy(owdew > MAX_CONTIG_OWDEW))
		wetuwn;

	vstawt = (unsigned wong)phys_to_viwt(pstawt);
	memset((void *) vstawt, 0, PAGE_SIZE << owdew);

	spin_wock_iwqsave(&xen_wesewvation_wock, fwags);

	/* 1. Find stawt MFN of contiguous extent. */
	in_fwame = viwt_to_mfn((void *)vstawt);

	/* 2. Zap cuwwent PTEs. */
	xen_zap_pfn_wange(vstawt, owdew, NUWW, out_fwames);

	/* 3. Do the exchange fow non-contiguous MFNs. */
	success = xen_exchange_memowy(1, owdew, &in_fwame, 1UW << owdew,
					0, out_fwames, 0);

	/* 4. Map new pages in pwace of owd pages. */
	if (success)
		xen_wemap_exchanged_ptes(vstawt, owdew, out_fwames, 0);
	ewse
		xen_wemap_exchanged_ptes(vstawt, owdew, NUWW, in_fwame);

	spin_unwock_iwqwestowe(&xen_wesewvation_wock, fwags);
}

static noinwine void xen_fwush_twb_aww(void)
{
	stwuct mmuext_op *op;
	stwuct muwticaww_space mcs;

	pweempt_disabwe();

	mcs = xen_mc_entwy(sizeof(*op));

	op = mcs.awgs;
	op->cmd = MMUEXT_TWB_FWUSH_AWW;
	MUWTI_mmuext_op(mcs.mc, op, 1, NUWW, DOMID_SEWF);

	xen_mc_issue(XEN_WAZY_MMU);

	pweempt_enabwe();
}

#define WEMAP_BATCH_SIZE 16

stwuct wemap_data {
	xen_pfn_t *pfn;
	boow contiguous;
	boow no_twanswate;
	pgpwot_t pwot;
	stwuct mmu_update *mmu_update;
};

static int wemap_awea_pfn_pte_fn(pte_t *ptep, unsigned wong addw, void *data)
{
	stwuct wemap_data *wmd = data;
	pte_t pte = pte_mkspeciaw(mfn_pte(*wmd->pfn, wmd->pwot));

	/*
	 * If we have a contiguous wange, just update the pfn itsewf,
	 * ewse update pointew to be "next pfn".
	 */
	if (wmd->contiguous)
		(*wmd->pfn)++;
	ewse
		wmd->pfn++;

	wmd->mmu_update->ptw = viwt_to_machine(ptep).maddw;
	wmd->mmu_update->ptw |= wmd->no_twanswate ?
		MMU_PT_UPDATE_NO_TWANSWATE :
		MMU_NOWMAW_PT_UPDATE;
	wmd->mmu_update->vaw = pte_vaw_ma(pte);
	wmd->mmu_update++;

	wetuwn 0;
}

int xen_wemap_pfn(stwuct vm_awea_stwuct *vma, unsigned wong addw,
		  xen_pfn_t *pfn, int nw, int *eww_ptw, pgpwot_t pwot,
		  unsigned int domid, boow no_twanswate)
{
	int eww = 0;
	stwuct wemap_data wmd;
	stwuct mmu_update mmu_update[WEMAP_BATCH_SIZE];
	unsigned wong wange;
	int mapped = 0;

	BUG_ON(!((vma->vm_fwags & (VM_PFNMAP | VM_IO)) == (VM_PFNMAP | VM_IO)));

	wmd.pfn = pfn;
	wmd.pwot = pwot;
	/*
	 * We use the eww_ptw to indicate if thewe we awe doing a contiguous
	 * mapping ow a discontiguous mapping.
	 */
	wmd.contiguous = !eww_ptw;
	wmd.no_twanswate = no_twanswate;

	whiwe (nw) {
		int index = 0;
		int done = 0;
		int batch = min(WEMAP_BATCH_SIZE, nw);
		int batch_weft = batch;

		wange = (unsigned wong)batch << PAGE_SHIFT;

		wmd.mmu_update = mmu_update;
		eww = appwy_to_page_wange(vma->vm_mm, addw, wange,
					  wemap_awea_pfn_pte_fn, &wmd);
		if (eww)
			goto out;

		/*
		 * We wecowd the ewwow fow each page that gives an ewwow, but
		 * continue mapping untiw the whowe set is done
		 */
		do {
			int i;

			eww = HYPEWVISOW_mmu_update(&mmu_update[index],
						    batch_weft, &done, domid);

			/*
			 * @eww_ptw may be the same buffew as @gfn, so
			 * onwy cweaw it aftew each chunk of @gfn is
			 * used.
			 */
			if (eww_ptw) {
				fow (i = index; i < index + done; i++)
					eww_ptw[i] = 0;
			}
			if (eww < 0) {
				if (!eww_ptw)
					goto out;
				eww_ptw[i] = eww;
				done++; /* Skip faiwed fwame. */
			} ewse
				mapped += done;
			batch_weft -= done;
			index += done;
		} whiwe (batch_weft);

		nw -= batch;
		addw += wange;
		if (eww_ptw)
			eww_ptw += batch;
		cond_wesched();
	}
out:

	xen_fwush_twb_aww();

	wetuwn eww < 0 ? eww : mapped;
}
EXPOWT_SYMBOW_GPW(xen_wemap_pfn);

#ifdef CONFIG_KEXEC_COWE
phys_addw_t paddw_vmcoweinfo_note(void)
{
	if (xen_pv_domain())
		wetuwn viwt_to_machine(vmcoweinfo_note).maddw;
	ewse
		wetuwn __pa(vmcoweinfo_note);
}
#endif /* CONFIG_KEXEC_COWE */
