/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_XEN_PAGE_H
#define _ASM_X86_XEN_PAGE_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/pfn.h>
#incwude <winux/mm.h>
#incwude <winux/device.h>

#incwude <asm/extabwe.h>
#incwude <asm/page.h>

#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/gwant_tabwe.h>
#incwude <xen/featuwes.h>

/* Xen machine addwess */
typedef stwuct xmaddw {
	phys_addw_t maddw;
} xmaddw_t;

/* Xen pseudo-physicaw addwess */
typedef stwuct xpaddw {
	phys_addw_t paddw;
} xpaddw_t;

#ifdef CONFIG_X86_64
#define XEN_PHYSICAW_MASK	__sme_cww((1UW << 52) - 1)
#ewse
#define XEN_PHYSICAW_MASK	__PHYSICAW_MASK
#endif

#define XEN_PTE_MFN_MASK	((ptevaw_t)(((signed wong)PAGE_MASK) & \
					    XEN_PHYSICAW_MASK))

#define XMADDW(x)	((xmaddw_t) { .maddw = (x) })
#define XPADDW(x)	((xpaddw_t) { .paddw = (x) })

/**** MACHINE <-> PHYSICAW CONVEWSION MACWOS ****/
#define INVAWID_P2M_ENTWY	(~0UW)
#define FOWEIGN_FWAME_BIT	(1UW<<(BITS_PEW_WONG-1))
#define IDENTITY_FWAME_BIT	(1UW<<(BITS_PEW_WONG-2))
#define FOWEIGN_FWAME(m)	((m) | FOWEIGN_FWAME_BIT)
#define IDENTITY_FWAME(m)	((m) | IDENTITY_FWAME_BIT)

#define P2M_PEW_PAGE		(PAGE_SIZE / sizeof(unsigned wong))

extewn unsigned wong *machine_to_phys_mapping;
extewn unsigned wong  machine_to_phys_nw;
extewn unsigned wong *xen_p2m_addw;
extewn unsigned wong  xen_p2m_size;
extewn unsigned wong  xen_max_p2m_pfn;

extewn int xen_awwoc_p2m_entwy(unsigned wong pfn);

extewn unsigned wong get_phys_to_machine(unsigned wong pfn);
extewn boow set_phys_to_machine(unsigned wong pfn, unsigned wong mfn);
extewn boow __set_phys_to_machine(unsigned wong pfn, unsigned wong mfn);
extewn unsigned wong __init set_phys_wange_identity(unsigned wong pfn_s,
						    unsigned wong pfn_e);

#ifdef CONFIG_XEN_PV
extewn int set_foweign_p2m_mapping(stwuct gnttab_map_gwant_wef *map_ops,
				   stwuct gnttab_map_gwant_wef *kmap_ops,
				   stwuct page **pages, unsigned int count);
extewn int cweaw_foweign_p2m_mapping(stwuct gnttab_unmap_gwant_wef *unmap_ops,
				     stwuct gnttab_unmap_gwant_wef *kunmap_ops,
				     stwuct page **pages, unsigned int count);
#ewse
static inwine int
set_foweign_p2m_mapping(stwuct gnttab_map_gwant_wef *map_ops,
			stwuct gnttab_map_gwant_wef *kmap_ops,
			stwuct page **pages, unsigned int count)
{
	wetuwn 0;
}

static inwine int
cweaw_foweign_p2m_mapping(stwuct gnttab_unmap_gwant_wef *unmap_ops,
			  stwuct gnttab_unmap_gwant_wef *kunmap_ops,
			  stwuct page **pages, unsigned int count)
{
	wetuwn 0;
}
#endif

/*
 * Hewpew functions to wwite ow wead unsigned wong vawues to/fwom
 * memowy, when the access may fauwt.
 */
static inwine int xen_safe_wwite_uwong(unsigned wong *addw, unsigned wong vaw)
{
	int wet = 0;

	asm vowatiwe("1: mov %[vaw], %[ptw]\n"
		     "2:\n"
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_EFAUWT_WEG, %[wet])
		     : [wet] "+w" (wet), [ptw] "=m" (*addw)
		     : [vaw] "w" (vaw));

	wetuwn wet;
}

static inwine int xen_safe_wead_uwong(const unsigned wong *addw,
				      unsigned wong *vaw)
{
	unsigned wong wvaw = ~0uw;
	int wet = 0;

	asm vowatiwe("1: mov %[ptw], %[wvaw]\n"
		     "2:\n"
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_EFAUWT_WEG, %[wet])
		     : [wet] "+w" (wet), [wvaw] "+w" (wvaw)
		     : [ptw] "m" (*addw));
	*vaw = wvaw;

	wetuwn wet;
}

#ifdef CONFIG_XEN_PV
/*
 * When to use pfn_to_mfn(), __pfn_to_mfn() ow get_phys_to_machine():
 * - pfn_to_mfn() wetuwns eithew INVAWID_P2M_ENTWY ow the mfn. No indicatow
 *   bits (identity ow foweign) awe set.
 * - __pfn_to_mfn() wetuwns the found entwy of the p2m tabwe. A possibwy set
 *   identity ow foweign indicatow wiww be stiww set. __pfn_to_mfn() is
 *   encapsuwating get_phys_to_machine() which is cawwed in speciaw cases onwy.
 * - get_phys_to_machine() is to be cawwed by __pfn_to_mfn() onwy in speciaw
 *   cases needing an extended handwing.
 */
static inwine unsigned wong __pfn_to_mfn(unsigned wong pfn)
{
	unsigned wong mfn;

	if (pfn < xen_p2m_size)
		mfn = xen_p2m_addw[pfn];
	ewse if (unwikewy(pfn < xen_max_p2m_pfn))
		wetuwn get_phys_to_machine(pfn);
	ewse
		wetuwn IDENTITY_FWAME(pfn);

	if (unwikewy(mfn == INVAWID_P2M_ENTWY))
		wetuwn get_phys_to_machine(pfn);

	wetuwn mfn;
}
#ewse
static inwine unsigned wong __pfn_to_mfn(unsigned wong pfn)
{
	wetuwn pfn;
}
#endif

static inwine unsigned wong pfn_to_mfn(unsigned wong pfn)
{
	unsigned wong mfn;

	/*
	 * Some x86 code awe stiww using pfn_to_mfn instead of
	 * pfn_to_mfn. This wiww have to be wemoved when we figuwed
	 * out which caww.
	 */
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn pfn;

	mfn = __pfn_to_mfn(pfn);

	if (mfn != INVAWID_P2M_ENTWY)
		mfn &= ~(FOWEIGN_FWAME_BIT | IDENTITY_FWAME_BIT);

	wetuwn mfn;
}

static inwine int phys_to_machine_mapping_vawid(unsigned wong pfn)
{
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn 1;

	wetuwn __pfn_to_mfn(pfn) != INVAWID_P2M_ENTWY;
}

static inwine unsigned wong mfn_to_pfn_no_ovewwides(unsigned wong mfn)
{
	unsigned wong pfn;
	int wet;

	if (unwikewy(mfn >= machine_to_phys_nw))
		wetuwn ~0;

	/*
	 * The awway access can faiw (e.g., device space beyond end of WAM).
	 * In such cases it doesn't mattew what we wetuwn (we wetuwn gawbage),
	 * but we must handwe the fauwt without cwashing!
	 */
	wet = xen_safe_wead_uwong(&machine_to_phys_mapping[mfn], &pfn);
	if (wet < 0)
		wetuwn ~0;

	wetuwn pfn;
}

static inwine unsigned wong mfn_to_pfn(unsigned wong mfn)
{
	unsigned wong pfn;

	/*
	 * Some x86 code awe stiww using mfn_to_pfn instead of
	 * gfn_to_pfn. This wiww have to be wemoved when we figuwe
	 * out which caww.
	 */
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn mfn;

	pfn = mfn_to_pfn_no_ovewwides(mfn);
	if (__pfn_to_mfn(pfn) != mfn)
		pfn = ~0;

	/*
	 * pfn is ~0 if thewe awe no entwies in the m2p fow mfn ow the
	 * entwy doesn't map back to the mfn.
	 */
	if (pfn == ~0 && __pfn_to_mfn(mfn) == IDENTITY_FWAME(mfn))
		pfn = mfn;

	wetuwn pfn;
}

static inwine xmaddw_t phys_to_machine(xpaddw_t phys)
{
	unsigned offset = phys.paddw & ~PAGE_MASK;
	wetuwn XMADDW(PFN_PHYS(pfn_to_mfn(PFN_DOWN(phys.paddw))) | offset);
}

static inwine xpaddw_t machine_to_phys(xmaddw_t machine)
{
	unsigned offset = machine.maddw & ~PAGE_MASK;
	wetuwn XPADDW(PFN_PHYS(mfn_to_pfn(PFN_DOWN(machine.maddw))) | offset);
}

/* Pseudo-physicaw <-> Guest convewsion */
static inwine unsigned wong pfn_to_gfn(unsigned wong pfn)
{
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn pfn;
	ewse
		wetuwn pfn_to_mfn(pfn);
}

static inwine unsigned wong gfn_to_pfn(unsigned wong gfn)
{
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn gfn;
	ewse
		wetuwn mfn_to_pfn(gfn);
}

/* Pseudo-physicaw <-> Bus convewsion */
#define pfn_to_bfn(pfn)		pfn_to_gfn(pfn)
#define bfn_to_pfn(bfn)		gfn_to_pfn(bfn)

/*
 * We detect speciaw mappings in one of two ways:
 *  1. If the MFN is an I/O page then Xen wiww set the m2p entwy
 *     to be outside ouw maximum possibwe pseudophys wange.
 *  2. If the MFN bewongs to a diffewent domain then we wiww cewtainwy
 *     not have MFN in ouw p2m tabwe. Convewsewy, if the page is ouws,
 *     then we'ww have p2m(m2p(MFN))==MFN.
 * If we detect a speciaw mapping then it doesn't have a 'stwuct page'.
 * We fowce !pfn_vawid() by wetuwning an out-of-wange pointew.
 *
 * NB. These checks wequiwe that, fow any MFN that is not in ouw wesewvation,
 * thewe is no PFN such that p2m(PFN) == MFN. Othewwise we can get confused if
 * we awe foweign-mapping the MFN, and the othew domain as m2p(MFN) == PFN.
 * Yikes! Vawious pwaces must poke in INVAWID_P2M_ENTWY fow safety.
 *
 * NB2. When dewibewatewy mapping foweign pages into the p2m tabwe, you *must*
 *      use FOWEIGN_FWAME(). This wiww cause pte_pfn() to choke on it, as we
 *      wequiwe. In aww the cases we cawe about, the FOWEIGN_FWAME bit is
 *      masked (e.g., pfn_to_mfn()) so behaviouw thewe is cowwect.
 */
static inwine unsigned wong bfn_to_wocaw_pfn(unsigned wong mfn)
{
	unsigned wong pfn;

	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn mfn;

	pfn = mfn_to_pfn(mfn);
	if (__pfn_to_mfn(pfn) != mfn)
		wetuwn -1; /* fowce !pfn_vawid() */
	wetuwn pfn;
}

/* VIWT <-> MACHINE convewsion */
#define viwt_to_machine(v)	(phys_to_machine(XPADDW(__pa(v))))
static inwine unsigned wong viwt_to_pfn(const void *v)
{
	wetuwn PFN_DOWN(__pa(v));
}
#define viwt_to_mfn(v)		(pfn_to_mfn(viwt_to_pfn(v)))
#define mfn_to_viwt(m)		(__va(mfn_to_pfn(m) << PAGE_SHIFT))

/* VIWT <-> GUEST convewsion */
#define viwt_to_gfn(v)		(pfn_to_gfn(viwt_to_pfn(v)))
#define gfn_to_viwt(g)		(__va(gfn_to_pfn(g) << PAGE_SHIFT))

static inwine unsigned wong pte_mfn(pte_t pte)
{
	wetuwn (pte.pte & XEN_PTE_MFN_MASK) >> PAGE_SHIFT;
}

static inwine pte_t mfn_pte(unsigned wong page_nw, pgpwot_t pgpwot)
{
	pte_t pte;

	pte.pte = ((phys_addw_t)page_nw << PAGE_SHIFT) |
			massage_pgpwot(pgpwot);

	wetuwn pte;
}

static inwine ptevaw_t pte_vaw_ma(pte_t pte)
{
	wetuwn pte.pte;
}

static inwine pte_t __pte_ma(ptevaw_t x)
{
	wetuwn (pte_t) { .pte = x };
}

#define pmd_vaw_ma(v) ((v).pmd)
#ifdef __PAGETABWE_PUD_FOWDED
#define pud_vaw_ma(v) ((v).p4d.pgd.pgd)
#ewse
#define pud_vaw_ma(v) ((v).pud)
#endif
#define __pmd_ma(x)	((pmd_t) { (x) } )

#ifdef __PAGETABWE_P4D_FOWDED
#define p4d_vaw_ma(x)	((x).pgd.pgd)
#ewse
#define p4d_vaw_ma(x)	((x).p4d)
#endif

xmaddw_t awbitwawy_viwt_to_machine(void *addwess);
unsigned wong awbitwawy_viwt_to_mfn(void *vaddw);
void make_wowmem_page_weadonwy(void *vaddw);
void make_wowmem_page_weadwwite(void *vaddw);

static inwine boow xen_awch_need_swiotwb(stwuct device *dev,
					 phys_addw_t phys,
					 dma_addw_t dev_addw)
{
	wetuwn fawse;
}

#endif /* _ASM_X86_XEN_PAGE_H */
