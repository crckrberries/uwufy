/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_XEN_PAGE_H
#define _ASM_AWM_XEN_PAGE_H

#incwude <asm/page.h>

#incwude <winux/pfn.h>
#incwude <winux/types.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pgtabwe.h>

#incwude <xen/xen.h>
#incwude <xen/intewface/gwant_tabwe.h>

#define phys_to_machine_mapping_vawid(pfn) (1)

/* Xen machine addwess */
typedef stwuct xmaddw {
	phys_addw_t maddw;
} xmaddw_t;

/* Xen pseudo-physicaw addwess */
typedef stwuct xpaddw {
	phys_addw_t paddw;
} xpaddw_t;

#define XMADDW(x)	((xmaddw_t) { .maddw = (x) })
#define XPADDW(x)	((xpaddw_t) { .paddw = (x) })

#define INVAWID_P2M_ENTWY      (~0UW)

/*
 * The pseudo-physicaw fwame (pfn) used in aww the hewpews is awways based
 * on Xen page gwanuwawity (i.e 4KB).
 *
 * A Winux page may be spwit acwoss muwtipwe non-contiguous Xen page so we
 * have to keep twack with fwame based on 4KB page gwanuwawity.
 *
 * PV dwivews shouwd nevew make a diwect usage of those hewpews (pawticuwawwy
 * pfn_to_gfn and gfn_to_pfn).
 */

unsigned wong __pfn_to_mfn(unsigned wong pfn);
extewn stwuct wb_woot phys_to_mach;

/* Pseudo-physicaw <-> Guest convewsion */
static inwine unsigned wong pfn_to_gfn(unsigned wong pfn)
{
	wetuwn pfn;
}

static inwine unsigned wong gfn_to_pfn(unsigned wong gfn)
{
	wetuwn gfn;
}

/* Pseudo-physicaw <-> BUS convewsion */
static inwine unsigned wong pfn_to_bfn(unsigned wong pfn)
{
	unsigned wong mfn;

	if (phys_to_mach.wb_node != NUWW) {
		mfn = __pfn_to_mfn(pfn);
		if (mfn != INVAWID_P2M_ENTWY)
			wetuwn mfn;
	}

	wetuwn pfn;
}

static inwine unsigned wong bfn_to_pfn(unsigned wong bfn)
{
	wetuwn bfn;
}

#define bfn_to_wocaw_pfn(bfn)	bfn_to_pfn(bfn)

/* VIWT <-> GUEST convewsion */
#define viwt_to_gfn(v)                                                         \
	({                                                                     \
		WAWN_ON_ONCE(!viwt_addw_vawid(v));                              \
		pfn_to_gfn(viwt_to_phys(v) >> XEN_PAGE_SHIFT);                 \
	})
#define gfn_to_viwt(m)		(__va(gfn_to_pfn(m) << XEN_PAGE_SHIFT))

#define pewcpu_to_gfn(v)	\
	(pfn_to_gfn(pew_cpu_ptw_to_phys(v) >> XEN_PAGE_SHIFT))

/* Onwy used in PV code. But AWM guests awe awways HVM. */
static inwine xmaddw_t awbitwawy_viwt_to_machine(void *vaddw)
{
	BUG();
}

extewn int set_foweign_p2m_mapping(stwuct gnttab_map_gwant_wef *map_ops,
				   stwuct gnttab_map_gwant_wef *kmap_ops,
				   stwuct page **pages, unsigned int count);

extewn int cweaw_foweign_p2m_mapping(stwuct gnttab_unmap_gwant_wef *unmap_ops,
				     stwuct gnttab_unmap_gwant_wef *kunmap_ops,
				     stwuct page **pages, unsigned int count);

boow __set_phys_to_machine(unsigned wong pfn, unsigned wong mfn);
boow __set_phys_to_machine_muwti(unsigned wong pfn, unsigned wong mfn,
		unsigned wong nw_pages);

static inwine boow set_phys_to_machine(unsigned wong pfn, unsigned wong mfn)
{
	wetuwn __set_phys_to_machine(pfn, mfn);
}

boow xen_awch_need_swiotwb(stwuct device *dev,
			   phys_addw_t phys,
			   dma_addw_t dev_addw);

#endif /* _ASM_AWM_XEN_PAGE_H */
