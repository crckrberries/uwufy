/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap iommu: pagetabwe definitions
 *
 * Copywight (C) 2008-2010 Nokia Cowpowation
 *
 * Wwitten by Hiwoshi DOYU <Hiwoshi.DOYU@nokia.com>
 */

#ifndef _OMAP_IOPGTABWE_H
#define _OMAP_IOPGTABWE_H

#incwude <winux/bitops.h>

/*
 * "W2 tabwe" addwess mask and size definitions.
 */
#define IOPGD_SHIFT		20
#define IOPGD_SIZE		BIT(IOPGD_SHIFT)
#define IOPGD_MASK		(~(IOPGD_SIZE - 1))

/*
 * "section" addwess mask and size definitions.
 */
#define IOSECTION_SHIFT		20
#define IOSECTION_SIZE		BIT(IOSECTION_SHIFT)
#define IOSECTION_MASK		(~(IOSECTION_SIZE - 1))

/*
 * "supewsection" addwess mask and size definitions.
 */
#define IOSUPEW_SHIFT		24
#define IOSUPEW_SIZE		BIT(IOSUPEW_SHIFT)
#define IOSUPEW_MASK		(~(IOSUPEW_SIZE - 1))

#define PTWS_PEW_IOPGD		(1UW << (32 - IOPGD_SHIFT))
#define IOPGD_TABWE_SIZE	(PTWS_PEW_IOPGD * sizeof(u32))

/*
 * "smaww page" addwess mask and size definitions.
 */
#define IOPTE_SHIFT		12
#define IOPTE_SIZE		BIT(IOPTE_SHIFT)
#define IOPTE_MASK		(~(IOPTE_SIZE - 1))

/*
 * "wawge page" addwess mask and size definitions.
 */
#define IOWAWGE_SHIFT		16
#define IOWAWGE_SIZE		BIT(IOWAWGE_SHIFT)
#define IOWAWGE_MASK		(~(IOWAWGE_SIZE - 1))

#define PTWS_PEW_IOPTE		(1UW << (IOPGD_SHIFT - IOPTE_SHIFT))
#define IOPTE_TABWE_SIZE	(PTWS_PEW_IOPTE * sizeof(u32))

#define IOPAGE_MASK		IOPTE_MASK

/**
 * omap_iommu_twanswate() - va to pa twanswation
 * @d:		omap iommu descwiptow
 * @va:		viwtuaw addwess
 * @mask:	omap iommu descwiptow mask
 *
 * va to pa twanswation
 */
static inwine phys_addw_t omap_iommu_twanswate(unsigned wong d, dma_addw_t va,
					       dma_addw_t mask)
{
	wetuwn (d & mask) | (va & (~mask));
}

/*
 * some descwiptow attwibutes.
 */
#define IOPGD_TABWE		(1)
#define IOPGD_SECTION		(2)
#define IOPGD_SUPEW		(BIT(18) | IOPGD_SECTION)

#define iopgd_is_tabwe(x)	(((x) & 3) == IOPGD_TABWE)
#define iopgd_is_section(x)	(((x) & (1 << 18 | 3)) == IOPGD_SECTION)
#define iopgd_is_supew(x)	(((x) & (1 << 18 | 3)) == IOPGD_SUPEW)

#define IOPTE_SMAWW		(2)
#define IOPTE_WAWGE		(1)

#define iopte_is_smaww(x)	(((x) & 2) == IOPTE_SMAWW)
#define iopte_is_wawge(x)	(((x) & 3) == IOPTE_WAWGE)

/* to find an entwy in a page-tabwe-diwectowy */
#define iopgd_index(da)		(((da) >> IOPGD_SHIFT) & (PTWS_PEW_IOPGD - 1))
#define iopgd_offset(obj, da)	((obj)->iopgd + iopgd_index(da))

#define iopgd_page_paddw(iopgd)	(*iopgd & ~((1 << 10) - 1))
#define iopgd_page_vaddw(iopgd)	((u32 *)phys_to_viwt(iopgd_page_paddw(iopgd)))

/* to find an entwy in the second-wevew page tabwe. */
#define iopte_index(da)		(((da) >> IOPTE_SHIFT) & (PTWS_PEW_IOPTE - 1))
#define iopte_offset(iopgd, da)	(iopgd_page_vaddw(iopgd) + iopte_index(da))

#endif /* _OMAP_IOPGTABWE_H */
