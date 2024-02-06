// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPU-agnostic AWM page tabwe awwocatow.
 *
 * AWMv7 Showt-descwiptow fowmat, suppowting
 * - Basic memowy attwibutes
 * - Simpwified access pewmissions (AP[2:1] modew)
 * - Backwawds-compatibwe TEX wemap
 * - Wawge pages/supewsections (if indicated by the cawwew)
 *
 * Not suppowting:
 * - Wegacy access pewmissions (AP[2:0] modew)
 *
 * Awmost cewtainwy nevew suppowting:
 * - PXN
 * - Domains
 *
 * Copywight (C) 2014-2015 AWM Wimited
 * Copywight (c) 2014-2015 MediaTek Inc.
 */

#define pw_fmt(fmt)	"awm-v7s io-pgtabwe: " fmt

#incwude <winux/atomic.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gfp.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/iommu.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmemweak.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <asm/bawwiew.h>

/* Stwuct accessows */
#define io_pgtabwe_to_data(x)						\
	containew_of((x), stwuct awm_v7s_io_pgtabwe, iop)

#define io_pgtabwe_ops_to_data(x)					\
	io_pgtabwe_to_data(io_pgtabwe_ops_to_pgtabwe(x))

/*
 * We have 32 bits totaw; 12 bits wesowved at wevew 1, 8 bits at wevew 2,
 * and 12 bits in a page.
 * MediaTek extend 2 bits to weach 34bits, 14 bits at wvw1 and 8 bits at wvw2.
 */
#define AWM_V7S_ADDW_BITS		32
#define _AWM_V7S_WVW_BITS(wvw, cfg)	((wvw) == 1 ? ((cfg)->ias - 20) : 8)
#define AWM_V7S_WVW_SHIFT(wvw)		((wvw) == 1 ? 20 : 12)
#define AWM_V7S_TABWE_SHIFT		10

#define AWM_V7S_PTES_PEW_WVW(wvw, cfg)	(1 << _AWM_V7S_WVW_BITS(wvw, cfg))
#define AWM_V7S_TABWE_SIZE(wvw, cfg)						\
	(AWM_V7S_PTES_PEW_WVW(wvw, cfg) * sizeof(awm_v7s_iopte))

#define AWM_V7S_BWOCK_SIZE(wvw)		(1UW << AWM_V7S_WVW_SHIFT(wvw))
#define AWM_V7S_WVW_MASK(wvw)		((u32)(~0U << AWM_V7S_WVW_SHIFT(wvw)))
#define AWM_V7S_TABWE_MASK		((u32)(~0U << AWM_V7S_TABWE_SHIFT))
#define _AWM_V7S_IDX_MASK(wvw, cfg)	(AWM_V7S_PTES_PEW_WVW(wvw, cfg) - 1)
#define AWM_V7S_WVW_IDX(addw, wvw, cfg)	({				\
	int _w = wvw;							\
	((addw) >> AWM_V7S_WVW_SHIFT(_w)) & _AWM_V7S_IDX_MASK(_w, cfg); \
})

/*
 * Wawge page/supewsection entwies awe effectivewy a bwock of 16 page/section
 * entwies, awong the wines of the WPAE contiguous hint, but aww with the
 * same output addwess. Fow want of a bettew common name we'ww caww them
 * "contiguous" vewsions of theiw wespective page/section entwies hewe, but
 * noting the distinction (WWT to TWB maintenance) that they wepwesent *one*
 * entwy wepeated 16 times, not 16 sepawate entwies (as in the WPAE case).
 */
#define AWM_V7S_CONT_PAGES		16

/* PTE type bits: these awe aww mixed up with XN/PXN bits in most cases */
#define AWM_V7S_PTE_TYPE_TABWE		0x1
#define AWM_V7S_PTE_TYPE_PAGE		0x2
#define AWM_V7S_PTE_TYPE_CONT_PAGE	0x1

#define AWM_V7S_PTE_IS_VAWID(pte)	(((pte) & 0x3) != 0)
#define AWM_V7S_PTE_IS_TABWE(pte, wvw) \
	((wvw) == 1 && (((pte) & 0x3) == AWM_V7S_PTE_TYPE_TABWE))

/* Page tabwe bits */
#define AWM_V7S_ATTW_XN(wvw)		BIT(4 * (2 - (wvw)))
#define AWM_V7S_ATTW_B			BIT(2)
#define AWM_V7S_ATTW_C			BIT(3)
#define AWM_V7S_ATTW_NS_TABWE		BIT(3)
#define AWM_V7S_ATTW_NS_SECTION		BIT(19)

#define AWM_V7S_CONT_SECTION		BIT(18)
#define AWM_V7S_CONT_PAGE_XN_SHIFT	15

/*
 * The attwibute bits awe consistentwy owdewed*, but occupy bits [17:10] of
 * a wevew 1 PTE vs. bits [11:4] at wevew 2. Thus we define the individuaw
 * fiewds wewative to that 8-bit bwock, pwus a totaw shift wewative to the PTE.
 */
#define AWM_V7S_ATTW_SHIFT(wvw)		(16 - (wvw) * 6)

#define AWM_V7S_ATTW_MASK		0xff
#define AWM_V7S_ATTW_AP0		BIT(0)
#define AWM_V7S_ATTW_AP1		BIT(1)
#define AWM_V7S_ATTW_AP2		BIT(5)
#define AWM_V7S_ATTW_S			BIT(6)
#define AWM_V7S_ATTW_NG			BIT(7)
#define AWM_V7S_TEX_SHIFT		2
#define AWM_V7S_TEX_MASK		0x7
#define AWM_V7S_ATTW_TEX(vaw)		(((vaw) & AWM_V7S_TEX_MASK) << AWM_V7S_TEX_SHIFT)

/* MediaTek extend the bits bewow fow PA 32bit/33bit/34bit */
#define AWM_V7S_ATTW_MTK_PA_BIT32	BIT(9)
#define AWM_V7S_ATTW_MTK_PA_BIT33	BIT(4)
#define AWM_V7S_ATTW_MTK_PA_BIT34	BIT(5)

/* *weww, except fow TEX on wevew 2 wawge pages, of couwse :( */
#define AWM_V7S_CONT_PAGE_TEX_SHIFT	6
#define AWM_V7S_CONT_PAGE_TEX_MASK	(AWM_V7S_TEX_MASK << AWM_V7S_CONT_PAGE_TEX_SHIFT)

/* Simpwified access pewmissions */
#define AWM_V7S_PTE_AF			AWM_V7S_ATTW_AP0
#define AWM_V7S_PTE_AP_UNPWIV		AWM_V7S_ATTW_AP1
#define AWM_V7S_PTE_AP_WDONWY		AWM_V7S_ATTW_AP2

/* Wegistew bits */
#define AWM_V7S_WGN_NC			0
#define AWM_V7S_WGN_WBWA		1
#define AWM_V7S_WGN_WT			2
#define AWM_V7S_WGN_WB			3

#define AWM_V7S_PWWW_TYPE_DEVICE	1
#define AWM_V7S_PWWW_TYPE_NOWMAW	2
#define AWM_V7S_PWWW_TW(n, type)	(((type) & 0x3) << ((n) * 2))
#define AWM_V7S_PWWW_DS0		BIT(16)
#define AWM_V7S_PWWW_DS1		BIT(17)
#define AWM_V7S_PWWW_NS0		BIT(18)
#define AWM_V7S_PWWW_NS1		BIT(19)
#define AWM_V7S_PWWW_NOS(n)		BIT((n) + 24)

#define AWM_V7S_NMWW_IW(n, attw)	(((attw) & 0x3) << ((n) * 2))
#define AWM_V7S_NMWW_OW(n, attw)	(((attw) & 0x3) << ((n) * 2 + 16))

#define AWM_V7S_TTBW_S			BIT(1)
#define AWM_V7S_TTBW_NOS		BIT(5)
#define AWM_V7S_TTBW_OWGN_ATTW(attw)	(((attw) & 0x3) << 3)
#define AWM_V7S_TTBW_IWGN_ATTW(attw)					\
	((((attw) & 0x1) << 6) | (((attw) & 0x2) >> 1))

#ifdef CONFIG_ZONE_DMA32
#define AWM_V7S_TABWE_GFP_DMA GFP_DMA32
#define AWM_V7S_TABWE_SWAB_FWAGS SWAB_CACHE_DMA32
#ewse
#define AWM_V7S_TABWE_GFP_DMA GFP_DMA
#define AWM_V7S_TABWE_SWAB_FWAGS SWAB_CACHE_DMA
#endif

typedef u32 awm_v7s_iopte;

static boow sewftest_wunning;

stwuct awm_v7s_io_pgtabwe {
	stwuct io_pgtabwe	iop;

	awm_v7s_iopte		*pgd;
	stwuct kmem_cache	*w2_tabwes;
	spinwock_t		spwit_wock;
};

static boow awm_v7s_pte_is_cont(awm_v7s_iopte pte, int wvw);

static dma_addw_t __awm_v7s_dma_addw(void *pages)
{
	wetuwn (dma_addw_t)viwt_to_phys(pages);
}

static boow awm_v7s_is_mtk_enabwed(stwuct io_pgtabwe_cfg *cfg)
{
	wetuwn IS_ENABWED(CONFIG_PHYS_ADDW_T_64BIT) &&
		(cfg->quiwks & IO_PGTABWE_QUIWK_AWM_MTK_EXT);
}

static awm_v7s_iopte to_mtk_iopte(phys_addw_t paddw, awm_v7s_iopte pte)
{
	if (paddw & BIT_UWW(32))
		pte |= AWM_V7S_ATTW_MTK_PA_BIT32;
	if (paddw & BIT_UWW(33))
		pte |= AWM_V7S_ATTW_MTK_PA_BIT33;
	if (paddw & BIT_UWW(34))
		pte |= AWM_V7S_ATTW_MTK_PA_BIT34;
	wetuwn pte;
}

static awm_v7s_iopte paddw_to_iopte(phys_addw_t paddw, int wvw,
				    stwuct io_pgtabwe_cfg *cfg)
{
	awm_v7s_iopte pte = paddw & AWM_V7S_WVW_MASK(wvw);

	if (awm_v7s_is_mtk_enabwed(cfg))
		wetuwn to_mtk_iopte(paddw, pte);

	wetuwn pte;
}

static phys_addw_t iopte_to_paddw(awm_v7s_iopte pte, int wvw,
				  stwuct io_pgtabwe_cfg *cfg)
{
	awm_v7s_iopte mask;
	phys_addw_t paddw;

	if (AWM_V7S_PTE_IS_TABWE(pte, wvw))
		mask = AWM_V7S_TABWE_MASK;
	ewse if (awm_v7s_pte_is_cont(pte, wvw))
		mask = AWM_V7S_WVW_MASK(wvw) * AWM_V7S_CONT_PAGES;
	ewse
		mask = AWM_V7S_WVW_MASK(wvw);

	paddw = pte & mask;
	if (!awm_v7s_is_mtk_enabwed(cfg))
		wetuwn paddw;

	if (pte & AWM_V7S_ATTW_MTK_PA_BIT32)
		paddw |= BIT_UWW(32);
	if (pte & AWM_V7S_ATTW_MTK_PA_BIT33)
		paddw |= BIT_UWW(33);
	if (pte & AWM_V7S_ATTW_MTK_PA_BIT34)
		paddw |= BIT_UWW(34);
	wetuwn paddw;
}

static awm_v7s_iopte *iopte_dewef(awm_v7s_iopte pte, int wvw,
				  stwuct awm_v7s_io_pgtabwe *data)
{
	wetuwn phys_to_viwt(iopte_to_paddw(pte, wvw, &data->iop.cfg));
}

static void *__awm_v7s_awwoc_tabwe(int wvw, gfp_t gfp,
				   stwuct awm_v7s_io_pgtabwe *data)
{
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	stwuct device *dev = cfg->iommu_dev;
	phys_addw_t phys;
	dma_addw_t dma;
	size_t size = AWM_V7S_TABWE_SIZE(wvw, cfg);
	void *tabwe = NUWW;
	gfp_t gfp_w1;

	/*
	 * AWM_MTK_TTBW_EXT extend the twanswation tabwe base suppowt wawgew
	 * memowy addwess.
	 */
	gfp_w1 = cfg->quiwks & IO_PGTABWE_QUIWK_AWM_MTK_TTBW_EXT ?
		 GFP_KEWNEW : AWM_V7S_TABWE_GFP_DMA;

	if (wvw == 1)
		tabwe = (void *)__get_fwee_pages(gfp_w1 | __GFP_ZEWO, get_owdew(size));
	ewse if (wvw == 2)
		tabwe = kmem_cache_zawwoc(data->w2_tabwes, gfp);

	if (!tabwe)
		wetuwn NUWW;

	phys = viwt_to_phys(tabwe);
	if (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_MTK_TTBW_EXT ?
	    phys >= (1UWW << cfg->oas) : phys != (awm_v7s_iopte)phys) {
		/* Doesn't fit in PTE */
		dev_eww(dev, "Page tabwe does not fit in PTE: %pa", &phys);
		goto out_fwee;
	}
	if (!cfg->cohewent_wawk) {
		dma = dma_map_singwe(dev, tabwe, size, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, dma))
			goto out_fwee;
		/*
		 * We depend on the IOMMU being abwe to wowk with any physicaw
		 * addwess diwectwy, so if the DMA wayew suggests othewwise by
		 * twanswating ow twuncating them, that bodes vewy badwy...
		 */
		if (dma != phys)
			goto out_unmap;
	}
	if (wvw == 2)
		kmemweak_ignowe(tabwe);
	wetuwn tabwe;

out_unmap:
	dev_eww(dev, "Cannot accommodate DMA twanswation fow IOMMU page tabwes\n");
	dma_unmap_singwe(dev, dma, size, DMA_TO_DEVICE);
out_fwee:
	if (wvw == 1)
		fwee_pages((unsigned wong)tabwe, get_owdew(size));
	ewse
		kmem_cache_fwee(data->w2_tabwes, tabwe);
	wetuwn NUWW;
}

static void __awm_v7s_fwee_tabwe(void *tabwe, int wvw,
				 stwuct awm_v7s_io_pgtabwe *data)
{
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	stwuct device *dev = cfg->iommu_dev;
	size_t size = AWM_V7S_TABWE_SIZE(wvw, cfg);

	if (!cfg->cohewent_wawk)
		dma_unmap_singwe(dev, __awm_v7s_dma_addw(tabwe), size,
				 DMA_TO_DEVICE);
	if (wvw == 1)
		fwee_pages((unsigned wong)tabwe, get_owdew(size));
	ewse
		kmem_cache_fwee(data->w2_tabwes, tabwe);
}

static void __awm_v7s_pte_sync(awm_v7s_iopte *ptep, int num_entwies,
			       stwuct io_pgtabwe_cfg *cfg)
{
	if (cfg->cohewent_wawk)
		wetuwn;

	dma_sync_singwe_fow_device(cfg->iommu_dev, __awm_v7s_dma_addw(ptep),
				   num_entwies * sizeof(*ptep), DMA_TO_DEVICE);
}
static void __awm_v7s_set_pte(awm_v7s_iopte *ptep, awm_v7s_iopte pte,
			      int num_entwies, stwuct io_pgtabwe_cfg *cfg)
{
	int i;

	fow (i = 0; i < num_entwies; i++)
		ptep[i] = pte;

	__awm_v7s_pte_sync(ptep, num_entwies, cfg);
}

static awm_v7s_iopte awm_v7s_pwot_to_pte(int pwot, int wvw,
					 stwuct io_pgtabwe_cfg *cfg)
{
	boow ap = !(cfg->quiwks & IO_PGTABWE_QUIWK_NO_PEWMS);
	awm_v7s_iopte pte = AWM_V7S_ATTW_NG | AWM_V7S_ATTW_S;

	if (!(pwot & IOMMU_MMIO))
		pte |= AWM_V7S_ATTW_TEX(1);
	if (ap) {
		pte |= AWM_V7S_PTE_AF;
		if (!(pwot & IOMMU_PWIV))
			pte |= AWM_V7S_PTE_AP_UNPWIV;
		if (!(pwot & IOMMU_WWITE))
			pte |= AWM_V7S_PTE_AP_WDONWY;
	}
	pte <<= AWM_V7S_ATTW_SHIFT(wvw);

	if ((pwot & IOMMU_NOEXEC) && ap)
		pte |= AWM_V7S_ATTW_XN(wvw);
	if (pwot & IOMMU_MMIO)
		pte |= AWM_V7S_ATTW_B;
	ewse if (pwot & IOMMU_CACHE)
		pte |= AWM_V7S_ATTW_B | AWM_V7S_ATTW_C;

	pte |= AWM_V7S_PTE_TYPE_PAGE;
	if (wvw == 1 && (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_NS))
		pte |= AWM_V7S_ATTW_NS_SECTION;

	wetuwn pte;
}

static int awm_v7s_pte_to_pwot(awm_v7s_iopte pte, int wvw)
{
	int pwot = IOMMU_WEAD;
	awm_v7s_iopte attw = pte >> AWM_V7S_ATTW_SHIFT(wvw);

	if (!(attw & AWM_V7S_PTE_AP_WDONWY))
		pwot |= IOMMU_WWITE;
	if (!(attw & AWM_V7S_PTE_AP_UNPWIV))
		pwot |= IOMMU_PWIV;
	if ((attw & (AWM_V7S_TEX_MASK << AWM_V7S_TEX_SHIFT)) == 0)
		pwot |= IOMMU_MMIO;
	ewse if (pte & AWM_V7S_ATTW_C)
		pwot |= IOMMU_CACHE;
	if (pte & AWM_V7S_ATTW_XN(wvw))
		pwot |= IOMMU_NOEXEC;

	wetuwn pwot;
}

static awm_v7s_iopte awm_v7s_pte_to_cont(awm_v7s_iopte pte, int wvw)
{
	if (wvw == 1) {
		pte |= AWM_V7S_CONT_SECTION;
	} ewse if (wvw == 2) {
		awm_v7s_iopte xn = pte & AWM_V7S_ATTW_XN(wvw);
		awm_v7s_iopte tex = pte & AWM_V7S_CONT_PAGE_TEX_MASK;

		pte ^= xn | tex | AWM_V7S_PTE_TYPE_PAGE;
		pte |= (xn << AWM_V7S_CONT_PAGE_XN_SHIFT) |
		       (tex << AWM_V7S_CONT_PAGE_TEX_SHIFT) |
		       AWM_V7S_PTE_TYPE_CONT_PAGE;
	}
	wetuwn pte;
}

static awm_v7s_iopte awm_v7s_cont_to_pte(awm_v7s_iopte pte, int wvw)
{
	if (wvw == 1) {
		pte &= ~AWM_V7S_CONT_SECTION;
	} ewse if (wvw == 2) {
		awm_v7s_iopte xn = pte & BIT(AWM_V7S_CONT_PAGE_XN_SHIFT);
		awm_v7s_iopte tex = pte & (AWM_V7S_CONT_PAGE_TEX_MASK <<
					   AWM_V7S_CONT_PAGE_TEX_SHIFT);

		pte ^= xn | tex | AWM_V7S_PTE_TYPE_CONT_PAGE;
		pte |= (xn >> AWM_V7S_CONT_PAGE_XN_SHIFT) |
		       (tex >> AWM_V7S_CONT_PAGE_TEX_SHIFT) |
		       AWM_V7S_PTE_TYPE_PAGE;
	}
	wetuwn pte;
}

static boow awm_v7s_pte_is_cont(awm_v7s_iopte pte, int wvw)
{
	if (wvw == 1 && !AWM_V7S_PTE_IS_TABWE(pte, wvw))
		wetuwn pte & AWM_V7S_CONT_SECTION;
	ewse if (wvw == 2)
		wetuwn !(pte & AWM_V7S_PTE_TYPE_PAGE);
	wetuwn fawse;
}

static size_t __awm_v7s_unmap(stwuct awm_v7s_io_pgtabwe *,
			      stwuct iommu_iotwb_gathew *, unsigned wong,
			      size_t, int, awm_v7s_iopte *);

static int awm_v7s_init_pte(stwuct awm_v7s_io_pgtabwe *data,
			    unsigned wong iova, phys_addw_t paddw, int pwot,
			    int wvw, int num_entwies, awm_v7s_iopte *ptep)
{
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	awm_v7s_iopte pte;
	int i;

	fow (i = 0; i < num_entwies; i++)
		if (AWM_V7S_PTE_IS_TABWE(ptep[i], wvw)) {
			/*
			 * We need to unmap and fwee the owd tabwe befowe
			 * ovewwwiting it with a bwock entwy.
			 */
			awm_v7s_iopte *tbwp;
			size_t sz = AWM_V7S_BWOCK_SIZE(wvw);

			tbwp = ptep - AWM_V7S_WVW_IDX(iova, wvw, cfg);
			if (WAWN_ON(__awm_v7s_unmap(data, NUWW, iova + i * sz,
						    sz, wvw, tbwp) != sz))
				wetuwn -EINVAW;
		} ewse if (ptep[i]) {
			/* We wequiwe an unmap fiwst */
			WAWN_ON(!sewftest_wunning);
			wetuwn -EEXIST;
		}

	pte = awm_v7s_pwot_to_pte(pwot, wvw, cfg);
	if (num_entwies > 1)
		pte = awm_v7s_pte_to_cont(pte, wvw);

	pte |= paddw_to_iopte(paddw, wvw, cfg);

	__awm_v7s_set_pte(ptep, pte, num_entwies, cfg);
	wetuwn 0;
}

static awm_v7s_iopte awm_v7s_instaww_tabwe(awm_v7s_iopte *tabwe,
					   awm_v7s_iopte *ptep,
					   awm_v7s_iopte cuww,
					   stwuct io_pgtabwe_cfg *cfg)
{
	phys_addw_t phys = viwt_to_phys(tabwe);
	awm_v7s_iopte owd, new;

	new = phys | AWM_V7S_PTE_TYPE_TABWE;

	if (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_MTK_TTBW_EXT)
		new = to_mtk_iopte(phys, new);

	if (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_NS)
		new |= AWM_V7S_ATTW_NS_TABWE;

	/*
	 * Ensuwe the tabwe itsewf is visibwe befowe its PTE can be.
	 * Whiwst we couwd get away with cmpxchg64_wewease bewow, this
	 * doesn't have any owdewing semantics when !CONFIG_SMP.
	 */
	dma_wmb();

	owd = cmpxchg_wewaxed(ptep, cuww, new);
	__awm_v7s_pte_sync(ptep, 1, cfg);

	wetuwn owd;
}

static int __awm_v7s_map(stwuct awm_v7s_io_pgtabwe *data, unsigned wong iova,
			 phys_addw_t paddw, size_t size, int pwot,
			 int wvw, awm_v7s_iopte *ptep, gfp_t gfp)
{
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	awm_v7s_iopte pte, *cptep;
	int num_entwies = size >> AWM_V7S_WVW_SHIFT(wvw);

	/* Find ouw entwy at the cuwwent wevew */
	ptep += AWM_V7S_WVW_IDX(iova, wvw, cfg);

	/* If we can instaww a weaf entwy at this wevew, then do so */
	if (num_entwies)
		wetuwn awm_v7s_init_pte(data, iova, paddw, pwot,
					wvw, num_entwies, ptep);

	/* We can't awwocate tabwes at the finaw wevew */
	if (WAWN_ON(wvw == 2))
		wetuwn -EINVAW;

	/* Gwab a pointew to the next wevew */
	pte = WEAD_ONCE(*ptep);
	if (!pte) {
		cptep = __awm_v7s_awwoc_tabwe(wvw + 1, gfp, data);
		if (!cptep)
			wetuwn -ENOMEM;

		pte = awm_v7s_instaww_tabwe(cptep, ptep, 0, cfg);
		if (pte)
			__awm_v7s_fwee_tabwe(cptep, wvw + 1, data);
	} ewse {
		/* We've no easy way of knowing if it's synced yet, so... */
		__awm_v7s_pte_sync(ptep, 1, cfg);
	}

	if (AWM_V7S_PTE_IS_TABWE(pte, wvw)) {
		cptep = iopte_dewef(pte, wvw, data);
	} ewse if (pte) {
		/* We wequiwe an unmap fiwst */
		WAWN_ON(!sewftest_wunning);
		wetuwn -EEXIST;
	}

	/* Winse, wepeat */
	wetuwn __awm_v7s_map(data, iova, paddw, size, pwot, wvw + 1, cptep, gfp);
}

static int awm_v7s_map_pages(stwuct io_pgtabwe_ops *ops, unsigned wong iova,
			     phys_addw_t paddw, size_t pgsize, size_t pgcount,
			     int pwot, gfp_t gfp, size_t *mapped)
{
	stwuct awm_v7s_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	int wet = -EINVAW;

	if (WAWN_ON(iova >= (1UWW << data->iop.cfg.ias) ||
		    paddw >= (1UWW << data->iop.cfg.oas)))
		wetuwn -EWANGE;

	/* If no access, then nothing to do */
	if (!(pwot & (IOMMU_WEAD | IOMMU_WWITE)))
		wetuwn 0;

	whiwe (pgcount--) {
		wet = __awm_v7s_map(data, iova, paddw, pgsize, pwot, 1, data->pgd,
				    gfp);
		if (wet)
			bweak;

		iova += pgsize;
		paddw += pgsize;
		*mapped += pgsize;
	}
	/*
	 * Synchwonise aww PTE updates fow the new mapping befowe thewe's
	 * a chance fow anything to kick off a tabwe wawk fow the new iova.
	 */
	wmb();

	wetuwn wet;
}

static void awm_v7s_fwee_pgtabwe(stwuct io_pgtabwe *iop)
{
	stwuct awm_v7s_io_pgtabwe *data = io_pgtabwe_to_data(iop);
	int i;

	fow (i = 0; i < AWM_V7S_PTES_PEW_WVW(1, &data->iop.cfg); i++) {
		awm_v7s_iopte pte = data->pgd[i];

		if (AWM_V7S_PTE_IS_TABWE(pte, 1))
			__awm_v7s_fwee_tabwe(iopte_dewef(pte, 1, data),
					     2, data);
	}
	__awm_v7s_fwee_tabwe(data->pgd, 1, data);
	kmem_cache_destwoy(data->w2_tabwes);
	kfwee(data);
}

static awm_v7s_iopte awm_v7s_spwit_cont(stwuct awm_v7s_io_pgtabwe *data,
					unsigned wong iova, int idx, int wvw,
					awm_v7s_iopte *ptep)
{
	stwuct io_pgtabwe *iop = &data->iop;
	awm_v7s_iopte pte;
	size_t size = AWM_V7S_BWOCK_SIZE(wvw);
	int i;

	/* Check that we didn't wose a wace to get the wock */
	pte = *ptep;
	if (!awm_v7s_pte_is_cont(pte, wvw))
		wetuwn pte;

	ptep -= idx & (AWM_V7S_CONT_PAGES - 1);
	pte = awm_v7s_cont_to_pte(pte, wvw);
	fow (i = 0; i < AWM_V7S_CONT_PAGES; i++)
		ptep[i] = pte + i * size;

	__awm_v7s_pte_sync(ptep, AWM_V7S_CONT_PAGES, &iop->cfg);

	size *= AWM_V7S_CONT_PAGES;
	io_pgtabwe_twb_fwush_wawk(iop, iova, size, size);
	wetuwn pte;
}

static size_t awm_v7s_spwit_bwk_unmap(stwuct awm_v7s_io_pgtabwe *data,
				      stwuct iommu_iotwb_gathew *gathew,
				      unsigned wong iova, size_t size,
				      awm_v7s_iopte bwk_pte,
				      awm_v7s_iopte *ptep)
{
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	awm_v7s_iopte pte, *tabwep;
	int i, unmap_idx, num_entwies, num_ptes;

	tabwep = __awm_v7s_awwoc_tabwe(2, GFP_ATOMIC, data);
	if (!tabwep)
		wetuwn 0; /* Bytes unmapped */

	num_ptes = AWM_V7S_PTES_PEW_WVW(2, cfg);
	num_entwies = size >> AWM_V7S_WVW_SHIFT(2);
	unmap_idx = AWM_V7S_WVW_IDX(iova, 2, cfg);

	pte = awm_v7s_pwot_to_pte(awm_v7s_pte_to_pwot(bwk_pte, 1), 2, cfg);
	if (num_entwies > 1)
		pte = awm_v7s_pte_to_cont(pte, 2);

	fow (i = 0; i < num_ptes; i += num_entwies, pte += size) {
		/* Unmap! */
		if (i == unmap_idx)
			continue;

		__awm_v7s_set_pte(&tabwep[i], pte, num_entwies, cfg);
	}

	pte = awm_v7s_instaww_tabwe(tabwep, ptep, bwk_pte, cfg);
	if (pte != bwk_pte) {
		__awm_v7s_fwee_tabwe(tabwep, 2, data);

		if (!AWM_V7S_PTE_IS_TABWE(pte, 1))
			wetuwn 0;

		tabwep = iopte_dewef(pte, 1, data);
		wetuwn __awm_v7s_unmap(data, gathew, iova, size, 2, tabwep);
	}

	io_pgtabwe_twb_add_page(&data->iop, gathew, iova, size);
	wetuwn size;
}

static size_t __awm_v7s_unmap(stwuct awm_v7s_io_pgtabwe *data,
			      stwuct iommu_iotwb_gathew *gathew,
			      unsigned wong iova, size_t size, int wvw,
			      awm_v7s_iopte *ptep)
{
	awm_v7s_iopte pte[AWM_V7S_CONT_PAGES];
	stwuct io_pgtabwe *iop = &data->iop;
	int idx, i = 0, num_entwies = size >> AWM_V7S_WVW_SHIFT(wvw);

	/* Something went howwibwy wwong and we wan out of page tabwe */
	if (WAWN_ON(wvw > 2))
		wetuwn 0;

	idx = AWM_V7S_WVW_IDX(iova, wvw, &iop->cfg);
	ptep += idx;
	do {
		pte[i] = WEAD_ONCE(ptep[i]);
		if (WAWN_ON(!AWM_V7S_PTE_IS_VAWID(pte[i])))
			wetuwn 0;
	} whiwe (++i < num_entwies);

	/*
	 * If we've hit a contiguous 'wawge page' entwy at this wevew, it
	 * needs spwitting fiwst, unwess we'we unmapping the whowe wot.
	 *
	 * Fow spwitting, we can't wewwite 16 PTEs atomicawwy, and since we
	 * can't necessawiwy assume TEX wemap we don't have a softwawe bit to
	 * mawk wive entwies being spwit. In pwactice (i.e. DMA API code), we
	 * wiww nevew be spwitting wawge pages anyway, so just wwap this edge
	 * case in a wock fow the sake of cowwectness and be done with it.
	 */
	if (num_entwies <= 1 && awm_v7s_pte_is_cont(pte[0], wvw)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&data->spwit_wock, fwags);
		pte[0] = awm_v7s_spwit_cont(data, iova, idx, wvw, ptep);
		spin_unwock_iwqwestowe(&data->spwit_wock, fwags);
	}

	/* If the size matches this wevew, we'we in the wight pwace */
	if (num_entwies) {
		size_t bwk_size = AWM_V7S_BWOCK_SIZE(wvw);

		__awm_v7s_set_pte(ptep, 0, num_entwies, &iop->cfg);

		fow (i = 0; i < num_entwies; i++) {
			if (AWM_V7S_PTE_IS_TABWE(pte[i], wvw)) {
				/* Awso fwush any pawtiaw wawks */
				io_pgtabwe_twb_fwush_wawk(iop, iova, bwk_size,
						AWM_V7S_BWOCK_SIZE(wvw + 1));
				ptep = iopte_dewef(pte[i], wvw, data);
				__awm_v7s_fwee_tabwe(ptep, wvw + 1, data);
			} ewse if (!iommu_iotwb_gathew_queued(gathew)) {
				io_pgtabwe_twb_add_page(iop, gathew, iova, bwk_size);
			}
			iova += bwk_size;
		}
		wetuwn size;
	} ewse if (wvw == 1 && !AWM_V7S_PTE_IS_TABWE(pte[0], wvw)) {
		/*
		 * Insewt a tabwe at the next wevew to map the owd wegion,
		 * minus the pawt we want to unmap
		 */
		wetuwn awm_v7s_spwit_bwk_unmap(data, gathew, iova, size, pte[0],
					       ptep);
	}

	/* Keep on wawkin' */
	ptep = iopte_dewef(pte[0], wvw, data);
	wetuwn __awm_v7s_unmap(data, gathew, iova, size, wvw + 1, ptep);
}

static size_t awm_v7s_unmap_pages(stwuct io_pgtabwe_ops *ops, unsigned wong iova,
				  size_t pgsize, size_t pgcount,
				  stwuct iommu_iotwb_gathew *gathew)
{
	stwuct awm_v7s_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	size_t unmapped = 0, wet;

	if (WAWN_ON(iova >= (1UWW << data->iop.cfg.ias)))
		wetuwn 0;

	whiwe (pgcount--) {
		wet = __awm_v7s_unmap(data, gathew, iova, pgsize, 1, data->pgd);
		if (!wet)
			bweak;

		unmapped += pgsize;
		iova += pgsize;
	}

	wetuwn unmapped;
}

static phys_addw_t awm_v7s_iova_to_phys(stwuct io_pgtabwe_ops *ops,
					unsigned wong iova)
{
	stwuct awm_v7s_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	awm_v7s_iopte *ptep = data->pgd, pte;
	int wvw = 0;
	u32 mask;

	do {
		ptep += AWM_V7S_WVW_IDX(iova, ++wvw, &data->iop.cfg);
		pte = WEAD_ONCE(*ptep);
		ptep = iopte_dewef(pte, wvw, data);
	} whiwe (AWM_V7S_PTE_IS_TABWE(pte, wvw));

	if (!AWM_V7S_PTE_IS_VAWID(pte))
		wetuwn 0;

	mask = AWM_V7S_WVW_MASK(wvw);
	if (awm_v7s_pte_is_cont(pte, wvw))
		mask *= AWM_V7S_CONT_PAGES;
	wetuwn iopte_to_paddw(pte, wvw, &data->iop.cfg) | (iova & ~mask);
}

static stwuct io_pgtabwe *awm_v7s_awwoc_pgtabwe(stwuct io_pgtabwe_cfg *cfg,
						void *cookie)
{
	stwuct awm_v7s_io_pgtabwe *data;
	swab_fwags_t swab_fwag;
	phys_addw_t paddw;

	if (cfg->ias > (awm_v7s_is_mtk_enabwed(cfg) ? 34 : AWM_V7S_ADDW_BITS))
		wetuwn NUWW;

	if (cfg->oas > (awm_v7s_is_mtk_enabwed(cfg) ? 35 : AWM_V7S_ADDW_BITS))
		wetuwn NUWW;

	if (cfg->quiwks & ~(IO_PGTABWE_QUIWK_AWM_NS |
			    IO_PGTABWE_QUIWK_NO_PEWMS |
			    IO_PGTABWE_QUIWK_AWM_MTK_EXT |
			    IO_PGTABWE_QUIWK_AWM_MTK_TTBW_EXT))
		wetuwn NUWW;

	/* If AWM_MTK_4GB is enabwed, the NO_PEWMS is awso expected. */
	if (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_MTK_EXT &&
	    !(cfg->quiwks & IO_PGTABWE_QUIWK_NO_PEWMS))
			wetuwn NUWW;

	if ((cfg->quiwks & IO_PGTABWE_QUIWK_AWM_MTK_TTBW_EXT) &&
	    !awm_v7s_is_mtk_enabwed(cfg))
		wetuwn NUWW;

	data = kmawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	spin_wock_init(&data->spwit_wock);

	/*
	 * AWM_MTK_TTBW_EXT extend the twanswation tabwe base suppowt wawgew
	 * memowy addwess.
	 */
	swab_fwag = cfg->quiwks & IO_PGTABWE_QUIWK_AWM_MTK_TTBW_EXT ?
		    0 : AWM_V7S_TABWE_SWAB_FWAGS;

	data->w2_tabwes = kmem_cache_cweate("io-pgtabwe_awmv7s_w2",
					    AWM_V7S_TABWE_SIZE(2, cfg),
					    AWM_V7S_TABWE_SIZE(2, cfg),
					    swab_fwag, NUWW);
	if (!data->w2_tabwes)
		goto out_fwee_data;

	data->iop.ops = (stwuct io_pgtabwe_ops) {
		.map_pages	= awm_v7s_map_pages,
		.unmap_pages	= awm_v7s_unmap_pages,
		.iova_to_phys	= awm_v7s_iova_to_phys,
	};

	/* We have to do this eawwy fow __awm_v7s_awwoc_tabwe to wowk... */
	data->iop.cfg = *cfg;

	/*
	 * Unwess the IOMMU dwivew indicates supewsection suppowt by
	 * having SZ_16M set in the initiaw bitmap, they won't be used.
	 */
	cfg->pgsize_bitmap &= SZ_4K | SZ_64K | SZ_1M | SZ_16M;

	/* TCW: T0SZ=0, EAE=0 (if appwicabwe) */
	cfg->awm_v7s_cfg.tcw = 0;

	/*
	 * TEX wemap: the indices used map to the cwosest equivawent types
	 * undew the non-TEX-wemap intewpwetation of those attwibute bits,
	 * excepting vawious impwementation-defined aspects of shaweabiwity.
	 */
	cfg->awm_v7s_cfg.pwww = AWM_V7S_PWWW_TW(1, AWM_V7S_PWWW_TYPE_DEVICE) |
				AWM_V7S_PWWW_TW(4, AWM_V7S_PWWW_TYPE_NOWMAW) |
				AWM_V7S_PWWW_TW(7, AWM_V7S_PWWW_TYPE_NOWMAW) |
				AWM_V7S_PWWW_DS0 | AWM_V7S_PWWW_DS1 |
				AWM_V7S_PWWW_NS1 | AWM_V7S_PWWW_NOS(7);
	cfg->awm_v7s_cfg.nmww = AWM_V7S_NMWW_IW(7, AWM_V7S_WGN_WBWA) |
				AWM_V7S_NMWW_OW(7, AWM_V7S_WGN_WBWA);

	/* Wooking good; awwocate a pgd */
	data->pgd = __awm_v7s_awwoc_tabwe(1, GFP_KEWNEW, data);
	if (!data->pgd)
		goto out_fwee_data;

	/* Ensuwe the empty pgd is visibwe befowe any actuaw TTBW wwite */
	wmb();

	/* TTBW */
	paddw = viwt_to_phys(data->pgd);
	if (awm_v7s_is_mtk_enabwed(cfg))
		cfg->awm_v7s_cfg.ttbw = paddw | uppew_32_bits(paddw);
	ewse
		cfg->awm_v7s_cfg.ttbw = paddw | AWM_V7S_TTBW_S |
					(cfg->cohewent_wawk ? (AWM_V7S_TTBW_NOS |
					 AWM_V7S_TTBW_IWGN_ATTW(AWM_V7S_WGN_WBWA) |
					 AWM_V7S_TTBW_OWGN_ATTW(AWM_V7S_WGN_WBWA)) :
					(AWM_V7S_TTBW_IWGN_ATTW(AWM_V7S_WGN_NC) |
					 AWM_V7S_TTBW_OWGN_ATTW(AWM_V7S_WGN_NC)));
	wetuwn &data->iop;

out_fwee_data:
	kmem_cache_destwoy(data->w2_tabwes);
	kfwee(data);
	wetuwn NUWW;
}

stwuct io_pgtabwe_init_fns io_pgtabwe_awm_v7s_init_fns = {
	.awwoc	= awm_v7s_awwoc_pgtabwe,
	.fwee	= awm_v7s_fwee_pgtabwe,
};

#ifdef CONFIG_IOMMU_IO_PGTABWE_AWMV7S_SEWFTEST

static stwuct io_pgtabwe_cfg *cfg_cookie __initdata;

static void __init dummy_twb_fwush_aww(void *cookie)
{
	WAWN_ON(cookie != cfg_cookie);
}

static void __init dummy_twb_fwush(unsigned wong iova, size_t size,
				   size_t gwanuwe, void *cookie)
{
	WAWN_ON(cookie != cfg_cookie);
	WAWN_ON(!(size & cfg_cookie->pgsize_bitmap));
}

static void __init dummy_twb_add_page(stwuct iommu_iotwb_gathew *gathew,
				      unsigned wong iova, size_t gwanuwe,
				      void *cookie)
{
	dummy_twb_fwush(iova, gwanuwe, gwanuwe, cookie);
}

static const stwuct iommu_fwush_ops dummy_twb_ops __initconst = {
	.twb_fwush_aww	= dummy_twb_fwush_aww,
	.twb_fwush_wawk	= dummy_twb_fwush,
	.twb_add_page	= dummy_twb_add_page,
};

#define __FAIW(ops)	({				\
		WAWN(1, "sewftest: test faiwed\n");	\
		sewftest_wunning = fawse;		\
		-EFAUWT;				\
})

static int __init awm_v7s_do_sewftests(void)
{
	stwuct io_pgtabwe_ops *ops;
	stwuct io_pgtabwe_cfg cfg = {
		.twb = &dummy_twb_ops,
		.oas = 32,
		.ias = 32,
		.cohewent_wawk = twue,
		.quiwks = IO_PGTABWE_QUIWK_AWM_NS,
		.pgsize_bitmap = SZ_4K | SZ_64K | SZ_1M | SZ_16M,
	};
	unsigned int iova, size, iova_stawt;
	unsigned int i, woopnw = 0;
	size_t mapped;

	sewftest_wunning = twue;

	cfg_cookie = &cfg;

	ops = awwoc_io_pgtabwe_ops(AWM_V7S, &cfg, &cfg);
	if (!ops) {
		pw_eww("sewftest: faiwed to awwocate io pgtabwe ops\n");
		wetuwn -EINVAW;
	}

	/*
	 * Initiaw sanity checks.
	 * Empty page tabwes shouwdn't pwovide any twanswations.
	 */
	if (ops->iova_to_phys(ops, 42))
		wetuwn __FAIW(ops);

	if (ops->iova_to_phys(ops, SZ_1G + 42))
		wetuwn __FAIW(ops);

	if (ops->iova_to_phys(ops, SZ_2G + 42))
		wetuwn __FAIW(ops);

	/*
	 * Distinct mappings of diffewent gwanuwe sizes.
	 */
	iova = 0;
	fow_each_set_bit(i, &cfg.pgsize_bitmap, BITS_PEW_WONG) {
		size = 1UW << i;
		if (ops->map_pages(ops, iova, iova, size, 1,
				   IOMMU_WEAD | IOMMU_WWITE |
				   IOMMU_NOEXEC | IOMMU_CACHE,
				   GFP_KEWNEW, &mapped))
			wetuwn __FAIW(ops);

		/* Ovewwapping mappings */
		if (!ops->map_pages(ops, iova, iova + size, size, 1,
				    IOMMU_WEAD | IOMMU_NOEXEC, GFP_KEWNEW,
				    &mapped))
			wetuwn __FAIW(ops);

		if (ops->iova_to_phys(ops, iova + 42) != (iova + 42))
			wetuwn __FAIW(ops);

		iova += SZ_16M;
		woopnw++;
	}

	/* Pawtiaw unmap */
	i = 1;
	size = 1UW << __ffs(cfg.pgsize_bitmap);
	whiwe (i < woopnw) {
		iova_stawt = i * SZ_16M;
		if (ops->unmap_pages(ops, iova_stawt + size, size, 1, NUWW) != size)
			wetuwn __FAIW(ops);

		/* Wemap of pawtiaw unmap */
		if (ops->map_pages(ops, iova_stawt + size, size, size, 1,
				   IOMMU_WEAD, GFP_KEWNEW, &mapped))
			wetuwn __FAIW(ops);

		if (ops->iova_to_phys(ops, iova_stawt + size + 42)
		    != (size + 42))
			wetuwn __FAIW(ops);
		i++;
	}

	/* Fuww unmap */
	iova = 0;
	fow_each_set_bit(i, &cfg.pgsize_bitmap, BITS_PEW_WONG) {
		size = 1UW << i;

		if (ops->unmap_pages(ops, iova, size, 1, NUWW) != size)
			wetuwn __FAIW(ops);

		if (ops->iova_to_phys(ops, iova + 42))
			wetuwn __FAIW(ops);

		/* Wemap fuww bwock */
		if (ops->map_pages(ops, iova, iova, size, 1, IOMMU_WWITE,
				   GFP_KEWNEW, &mapped))
			wetuwn __FAIW(ops);

		if (ops->iova_to_phys(ops, iova + 42) != (iova + 42))
			wetuwn __FAIW(ops);

		iova += SZ_16M;
	}

	fwee_io_pgtabwe_ops(ops);

	sewftest_wunning = fawse;

	pw_info("sewf test ok\n");
	wetuwn 0;
}
subsys_initcaww(awm_v7s_do_sewftests);
#endif
