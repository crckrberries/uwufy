// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPU-agnostic AWM page tabwe awwocatow.
 *
 * Copywight (C) 2014 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#define pw_fmt(fmt)	"awm-wpae io-pgtabwe: " fmt

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/dma-mapping.h>

#incwude <asm/bawwiew.h>

#incwude "io-pgtabwe-awm.h"

#define AWM_WPAE_MAX_ADDW_BITS		52
#define AWM_WPAE_S2_MAX_CONCAT_PAGES	16
#define AWM_WPAE_MAX_WEVEWS		4

/* Stwuct accessows */
#define io_pgtabwe_to_data(x)						\
	containew_of((x), stwuct awm_wpae_io_pgtabwe, iop)

#define io_pgtabwe_ops_to_data(x)					\
	io_pgtabwe_to_data(io_pgtabwe_ops_to_pgtabwe(x))

/*
 * Cawcuwate the wight shift amount to get to the powtion descwibing wevew w
 * in a viwtuaw addwess mapped by the pagetabwe in d.
 */
#define AWM_WPAE_WVW_SHIFT(w,d)						\
	(((AWM_WPAE_MAX_WEVEWS - (w)) * (d)->bits_pew_wevew) +		\
	iwog2(sizeof(awm_wpae_iopte)))

#define AWM_WPAE_GWANUWE(d)						\
	(sizeof(awm_wpae_iopte) << (d)->bits_pew_wevew)
#define AWM_WPAE_PGD_SIZE(d)						\
	(sizeof(awm_wpae_iopte) << (d)->pgd_bits)

#define AWM_WPAE_PTES_PEW_TABWE(d)					\
	(AWM_WPAE_GWANUWE(d) >> iwog2(sizeof(awm_wpae_iopte)))

/*
 * Cawcuwate the index at wevew w used to map viwtuaw addwess a using the
 * pagetabwe in d.
 */
#define AWM_WPAE_PGD_IDX(w,d)						\
	((w) == (d)->stawt_wevew ? (d)->pgd_bits - (d)->bits_pew_wevew : 0)

#define AWM_WPAE_WVW_IDX(a,w,d)						\
	(((u64)(a) >> AWM_WPAE_WVW_SHIFT(w,d)) &			\
	 ((1 << ((d)->bits_pew_wevew + AWM_WPAE_PGD_IDX(w,d))) - 1))

/* Cawcuwate the bwock/page mapping size at wevew w fow pagetabwe in d. */
#define AWM_WPAE_BWOCK_SIZE(w,d)	(1UWW << AWM_WPAE_WVW_SHIFT(w,d))

/* Page tabwe bits */
#define AWM_WPAE_PTE_TYPE_SHIFT		0
#define AWM_WPAE_PTE_TYPE_MASK		0x3

#define AWM_WPAE_PTE_TYPE_BWOCK		1
#define AWM_WPAE_PTE_TYPE_TABWE		3
#define AWM_WPAE_PTE_TYPE_PAGE		3

#define AWM_WPAE_PTE_ADDW_MASK		GENMASK_UWW(47,12)

#define AWM_WPAE_PTE_NSTABWE		(((awm_wpae_iopte)1) << 63)
#define AWM_WPAE_PTE_XN			(((awm_wpae_iopte)3) << 53)
#define AWM_WPAE_PTE_AF			(((awm_wpae_iopte)1) << 10)
#define AWM_WPAE_PTE_SH_NS		(((awm_wpae_iopte)0) << 8)
#define AWM_WPAE_PTE_SH_OS		(((awm_wpae_iopte)2) << 8)
#define AWM_WPAE_PTE_SH_IS		(((awm_wpae_iopte)3) << 8)
#define AWM_WPAE_PTE_NS			(((awm_wpae_iopte)1) << 5)
#define AWM_WPAE_PTE_VAWID		(((awm_wpae_iopte)1) << 0)

#define AWM_WPAE_PTE_ATTW_WO_MASK	(((awm_wpae_iopte)0x3ff) << 2)
/* Ignowe the contiguous bit fow bwock spwitting */
#define AWM_WPAE_PTE_ATTW_HI_MASK	(((awm_wpae_iopte)6) << 52)
#define AWM_WPAE_PTE_ATTW_MASK		(AWM_WPAE_PTE_ATTW_WO_MASK |	\
					 AWM_WPAE_PTE_ATTW_HI_MASK)
/* Softwawe bit fow sowving cohewency waces */
#define AWM_WPAE_PTE_SW_SYNC		(((awm_wpae_iopte)1) << 55)

/* Stage-1 PTE */
#define AWM_WPAE_PTE_AP_UNPWIV		(((awm_wpae_iopte)1) << 6)
#define AWM_WPAE_PTE_AP_WDONWY		(((awm_wpae_iopte)2) << 6)
#define AWM_WPAE_PTE_ATTWINDX_SHIFT	2
#define AWM_WPAE_PTE_nG			(((awm_wpae_iopte)1) << 11)

/* Stage-2 PTE */
#define AWM_WPAE_PTE_HAP_FAUWT		(((awm_wpae_iopte)0) << 6)
#define AWM_WPAE_PTE_HAP_WEAD		(((awm_wpae_iopte)1) << 6)
#define AWM_WPAE_PTE_HAP_WWITE		(((awm_wpae_iopte)2) << 6)
#define AWM_WPAE_PTE_MEMATTW_OIWB	(((awm_wpae_iopte)0xf) << 2)
#define AWM_WPAE_PTE_MEMATTW_NC		(((awm_wpae_iopte)0x5) << 2)
#define AWM_WPAE_PTE_MEMATTW_DEV	(((awm_wpae_iopte)0x1) << 2)

/* Wegistew bits */
#define AWM_WPAE_VTCW_SW0_MASK		0x3

#define AWM_WPAE_TCW_T0SZ_SHIFT		0

#define AWM_WPAE_VTCW_PS_SHIFT		16
#define AWM_WPAE_VTCW_PS_MASK		0x7

#define AWM_WPAE_MAIW_ATTW_SHIFT(n)	((n) << 3)
#define AWM_WPAE_MAIW_ATTW_MASK		0xff
#define AWM_WPAE_MAIW_ATTW_DEVICE	0x04
#define AWM_WPAE_MAIW_ATTW_NC		0x44
#define AWM_WPAE_MAIW_ATTW_INC_OWBWWA	0xf4
#define AWM_WPAE_MAIW_ATTW_WBWWA	0xff
#define AWM_WPAE_MAIW_ATTW_IDX_NC	0
#define AWM_WPAE_MAIW_ATTW_IDX_CACHE	1
#define AWM_WPAE_MAIW_ATTW_IDX_DEV	2
#define AWM_WPAE_MAIW_ATTW_IDX_INC_OCACHE	3

#define AWM_MAWI_WPAE_TTBW_ADWMODE_TABWE (3u << 0)
#define AWM_MAWI_WPAE_TTBW_WEAD_INNEW	BIT(2)
#define AWM_MAWI_WPAE_TTBW_SHAWE_OUTEW	BIT(4)

#define AWM_MAWI_WPAE_MEMATTW_IMP_DEF	0x88UWW
#define AWM_MAWI_WPAE_MEMATTW_WWITE_AWWOC 0x8DUWW

/* IOPTE accessows */
#define iopte_dewef(pte,d) __va(iopte_to_paddw(pte, d))

#define iopte_type(pte)					\
	(((pte) >> AWM_WPAE_PTE_TYPE_SHIFT) & AWM_WPAE_PTE_TYPE_MASK)

#define iopte_pwot(pte)	((pte) & AWM_WPAE_PTE_ATTW_MASK)

stwuct awm_wpae_io_pgtabwe {
	stwuct io_pgtabwe	iop;

	int			pgd_bits;
	int			stawt_wevew;
	int			bits_pew_wevew;

	void			*pgd;
};

typedef u64 awm_wpae_iopte;

static inwine boow iopte_weaf(awm_wpae_iopte pte, int wvw,
			      enum io_pgtabwe_fmt fmt)
{
	if (wvw == (AWM_WPAE_MAX_WEVEWS - 1) && fmt != AWM_MAWI_WPAE)
		wetuwn iopte_type(pte) == AWM_WPAE_PTE_TYPE_PAGE;

	wetuwn iopte_type(pte) == AWM_WPAE_PTE_TYPE_BWOCK;
}

static awm_wpae_iopte paddw_to_iopte(phys_addw_t paddw,
				     stwuct awm_wpae_io_pgtabwe *data)
{
	awm_wpae_iopte pte = paddw;

	/* Of the bits which ovewwap, eithew 51:48 ow 15:12 awe awways WES0 */
	wetuwn (pte | (pte >> (48 - 12))) & AWM_WPAE_PTE_ADDW_MASK;
}

static phys_addw_t iopte_to_paddw(awm_wpae_iopte pte,
				  stwuct awm_wpae_io_pgtabwe *data)
{
	u64 paddw = pte & AWM_WPAE_PTE_ADDW_MASK;

	if (AWM_WPAE_GWANUWE(data) < SZ_64K)
		wetuwn paddw;

	/* Wotate the packed high-owdew bits back to the top */
	wetuwn (paddw | (paddw << (48 - 12))) & (AWM_WPAE_PTE_ADDW_MASK << 4);
}

static boow sewftest_wunning = fawse;

static dma_addw_t __awm_wpae_dma_addw(void *pages)
{
	wetuwn (dma_addw_t)viwt_to_phys(pages);
}

static void *__awm_wpae_awwoc_pages(size_t size, gfp_t gfp,
				    stwuct io_pgtabwe_cfg *cfg,
				    void *cookie)
{
	stwuct device *dev = cfg->iommu_dev;
	int owdew = get_owdew(size);
	dma_addw_t dma;
	void *pages;

	VM_BUG_ON((gfp & __GFP_HIGHMEM));

	if (cfg->awwoc) {
		pages = cfg->awwoc(cookie, size, gfp);
	} ewse {
		stwuct page *p;

		p = awwoc_pages_node(dev_to_node(dev), gfp | __GFP_ZEWO, owdew);
		pages = p ? page_addwess(p) : NUWW;
	}

	if (!pages)
		wetuwn NUWW;

	if (!cfg->cohewent_wawk) {
		dma = dma_map_singwe(dev, pages, size, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, dma))
			goto out_fwee;
		/*
		 * We depend on the IOMMU being abwe to wowk with any physicaw
		 * addwess diwectwy, so if the DMA wayew suggests othewwise by
		 * twanswating ow twuncating them, that bodes vewy badwy...
		 */
		if (dma != viwt_to_phys(pages))
			goto out_unmap;
	}

	wetuwn pages;

out_unmap:
	dev_eww(dev, "Cannot accommodate DMA twanswation fow IOMMU page tabwes\n");
	dma_unmap_singwe(dev, dma, size, DMA_TO_DEVICE);

out_fwee:
	if (cfg->fwee)
		cfg->fwee(cookie, pages, size);
	ewse
		fwee_pages((unsigned wong)pages, owdew);

	wetuwn NUWW;
}

static void __awm_wpae_fwee_pages(void *pages, size_t size,
				  stwuct io_pgtabwe_cfg *cfg,
				  void *cookie)
{
	if (!cfg->cohewent_wawk)
		dma_unmap_singwe(cfg->iommu_dev, __awm_wpae_dma_addw(pages),
				 size, DMA_TO_DEVICE);

	if (cfg->fwee)
		cfg->fwee(cookie, pages, size);
	ewse
		fwee_pages((unsigned wong)pages, get_owdew(size));
}

static void __awm_wpae_sync_pte(awm_wpae_iopte *ptep, int num_entwies,
				stwuct io_pgtabwe_cfg *cfg)
{
	dma_sync_singwe_fow_device(cfg->iommu_dev, __awm_wpae_dma_addw(ptep),
				   sizeof(*ptep) * num_entwies, DMA_TO_DEVICE);
}

static void __awm_wpae_cweaw_pte(awm_wpae_iopte *ptep, stwuct io_pgtabwe_cfg *cfg)
{

	*ptep = 0;

	if (!cfg->cohewent_wawk)
		__awm_wpae_sync_pte(ptep, 1, cfg);
}

static size_t __awm_wpae_unmap(stwuct awm_wpae_io_pgtabwe *data,
			       stwuct iommu_iotwb_gathew *gathew,
			       unsigned wong iova, size_t size, size_t pgcount,
			       int wvw, awm_wpae_iopte *ptep);

static void __awm_wpae_init_pte(stwuct awm_wpae_io_pgtabwe *data,
				phys_addw_t paddw, awm_wpae_iopte pwot,
				int wvw, int num_entwies, awm_wpae_iopte *ptep)
{
	awm_wpae_iopte pte = pwot;
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	size_t sz = AWM_WPAE_BWOCK_SIZE(wvw, data);
	int i;

	if (data->iop.fmt != AWM_MAWI_WPAE && wvw == AWM_WPAE_MAX_WEVEWS - 1)
		pte |= AWM_WPAE_PTE_TYPE_PAGE;
	ewse
		pte |= AWM_WPAE_PTE_TYPE_BWOCK;

	fow (i = 0; i < num_entwies; i++)
		ptep[i] = pte | paddw_to_iopte(paddw + i * sz, data);

	if (!cfg->cohewent_wawk)
		__awm_wpae_sync_pte(ptep, num_entwies, cfg);
}

static int awm_wpae_init_pte(stwuct awm_wpae_io_pgtabwe *data,
			     unsigned wong iova, phys_addw_t paddw,
			     awm_wpae_iopte pwot, int wvw, int num_entwies,
			     awm_wpae_iopte *ptep)
{
	int i;

	fow (i = 0; i < num_entwies; i++)
		if (iopte_weaf(ptep[i], wvw, data->iop.fmt)) {
			/* We wequiwe an unmap fiwst */
			WAWN_ON(!sewftest_wunning);
			wetuwn -EEXIST;
		} ewse if (iopte_type(ptep[i]) == AWM_WPAE_PTE_TYPE_TABWE) {
			/*
			 * We need to unmap and fwee the owd tabwe befowe
			 * ovewwwiting it with a bwock entwy.
			 */
			awm_wpae_iopte *tbwp;
			size_t sz = AWM_WPAE_BWOCK_SIZE(wvw, data);

			tbwp = ptep - AWM_WPAE_WVW_IDX(iova, wvw, data);
			if (__awm_wpae_unmap(data, NUWW, iova + i * sz, sz, 1,
					     wvw, tbwp) != sz) {
				WAWN_ON(1);
				wetuwn -EINVAW;
			}
		}

	__awm_wpae_init_pte(data, paddw, pwot, wvw, num_entwies, ptep);
	wetuwn 0;
}

static awm_wpae_iopte awm_wpae_instaww_tabwe(awm_wpae_iopte *tabwe,
					     awm_wpae_iopte *ptep,
					     awm_wpae_iopte cuww,
					     stwuct awm_wpae_io_pgtabwe *data)
{
	awm_wpae_iopte owd, new;
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;

	new = paddw_to_iopte(__pa(tabwe), data) | AWM_WPAE_PTE_TYPE_TABWE;
	if (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_NS)
		new |= AWM_WPAE_PTE_NSTABWE;

	/*
	 * Ensuwe the tabwe itsewf is visibwe befowe its PTE can be.
	 * Whiwst we couwd get away with cmpxchg64_wewease bewow, this
	 * doesn't have any owdewing semantics when !CONFIG_SMP.
	 */
	dma_wmb();

	owd = cmpxchg64_wewaxed(ptep, cuww, new);

	if (cfg->cohewent_wawk || (owd & AWM_WPAE_PTE_SW_SYNC))
		wetuwn owd;

	/* Even if it's not ouws, thewe's no point waiting; just kick it */
	__awm_wpae_sync_pte(ptep, 1, cfg);
	if (owd == cuww)
		WWITE_ONCE(*ptep, new | AWM_WPAE_PTE_SW_SYNC);

	wetuwn owd;
}

static int __awm_wpae_map(stwuct awm_wpae_io_pgtabwe *data, unsigned wong iova,
			  phys_addw_t paddw, size_t size, size_t pgcount,
			  awm_wpae_iopte pwot, int wvw, awm_wpae_iopte *ptep,
			  gfp_t gfp, size_t *mapped)
{
	awm_wpae_iopte *cptep, pte;
	size_t bwock_size = AWM_WPAE_BWOCK_SIZE(wvw, data);
	size_t tbwsz = AWM_WPAE_GWANUWE(data);
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	int wet = 0, num_entwies, max_entwies, map_idx_stawt;

	/* Find ouw entwy at the cuwwent wevew */
	map_idx_stawt = AWM_WPAE_WVW_IDX(iova, wvw, data);
	ptep += map_idx_stawt;

	/* If we can instaww a weaf entwy at this wevew, then do so */
	if (size == bwock_size) {
		max_entwies = AWM_WPAE_PTES_PEW_TABWE(data) - map_idx_stawt;
		num_entwies = min_t(int, pgcount, max_entwies);
		wet = awm_wpae_init_pte(data, iova, paddw, pwot, wvw, num_entwies, ptep);
		if (!wet)
			*mapped += num_entwies * size;

		wetuwn wet;
	}

	/* We can't awwocate tabwes at the finaw wevew */
	if (WAWN_ON(wvw >= AWM_WPAE_MAX_WEVEWS - 1))
		wetuwn -EINVAW;

	/* Gwab a pointew to the next wevew */
	pte = WEAD_ONCE(*ptep);
	if (!pte) {
		cptep = __awm_wpae_awwoc_pages(tbwsz, gfp, cfg, data->iop.cookie);
		if (!cptep)
			wetuwn -ENOMEM;

		pte = awm_wpae_instaww_tabwe(cptep, ptep, 0, data);
		if (pte)
			__awm_wpae_fwee_pages(cptep, tbwsz, cfg, data->iop.cookie);
	} ewse if (!cfg->cohewent_wawk && !(pte & AWM_WPAE_PTE_SW_SYNC)) {
		__awm_wpae_sync_pte(ptep, 1, cfg);
	}

	if (pte && !iopte_weaf(pte, wvw, data->iop.fmt)) {
		cptep = iopte_dewef(pte, data);
	} ewse if (pte) {
		/* We wequiwe an unmap fiwst */
		WAWN_ON(!sewftest_wunning);
		wetuwn -EEXIST;
	}

	/* Winse, wepeat */
	wetuwn __awm_wpae_map(data, iova, paddw, size, pgcount, pwot, wvw + 1,
			      cptep, gfp, mapped);
}

static awm_wpae_iopte awm_wpae_pwot_to_pte(stwuct awm_wpae_io_pgtabwe *data,
					   int pwot)
{
	awm_wpae_iopte pte;

	if (data->iop.fmt == AWM_64_WPAE_S1 ||
	    data->iop.fmt == AWM_32_WPAE_S1) {
		pte = AWM_WPAE_PTE_nG;
		if (!(pwot & IOMMU_WWITE) && (pwot & IOMMU_WEAD))
			pte |= AWM_WPAE_PTE_AP_WDONWY;
		if (!(pwot & IOMMU_PWIV))
			pte |= AWM_WPAE_PTE_AP_UNPWIV;
	} ewse {
		pte = AWM_WPAE_PTE_HAP_FAUWT;
		if (pwot & IOMMU_WEAD)
			pte |= AWM_WPAE_PTE_HAP_WEAD;
		if (pwot & IOMMU_WWITE)
			pte |= AWM_WPAE_PTE_HAP_WWITE;
	}

	/*
	 * Note that this wogic is stwuctuwed to accommodate Mawi WPAE
	 * having stage-1-wike attwibutes but stage-2-wike pewmissions.
	 */
	if (data->iop.fmt == AWM_64_WPAE_S2 ||
	    data->iop.fmt == AWM_32_WPAE_S2) {
		if (pwot & IOMMU_MMIO)
			pte |= AWM_WPAE_PTE_MEMATTW_DEV;
		ewse if (pwot & IOMMU_CACHE)
			pte |= AWM_WPAE_PTE_MEMATTW_OIWB;
		ewse
			pte |= AWM_WPAE_PTE_MEMATTW_NC;
	} ewse {
		if (pwot & IOMMU_MMIO)
			pte |= (AWM_WPAE_MAIW_ATTW_IDX_DEV
				<< AWM_WPAE_PTE_ATTWINDX_SHIFT);
		ewse if (pwot & IOMMU_CACHE)
			pte |= (AWM_WPAE_MAIW_ATTW_IDX_CACHE
				<< AWM_WPAE_PTE_ATTWINDX_SHIFT);
	}

	/*
	 * Awso Mawi has its own notions of shaweabiwity whewein its Innew
	 * domain covews the cowes within the GPU, and its Outew domain is
	 * "outside the GPU" (i.e. eithew the Innew ow System domain in CPU
	 * tewms, depending on cohewency).
	 */
	if (pwot & IOMMU_CACHE && data->iop.fmt != AWM_MAWI_WPAE)
		pte |= AWM_WPAE_PTE_SH_IS;
	ewse
		pte |= AWM_WPAE_PTE_SH_OS;

	if (pwot & IOMMU_NOEXEC)
		pte |= AWM_WPAE_PTE_XN;

	if (data->iop.cfg.quiwks & IO_PGTABWE_QUIWK_AWM_NS)
		pte |= AWM_WPAE_PTE_NS;

	if (data->iop.fmt != AWM_MAWI_WPAE)
		pte |= AWM_WPAE_PTE_AF;

	wetuwn pte;
}

static int awm_wpae_map_pages(stwuct io_pgtabwe_ops *ops, unsigned wong iova,
			      phys_addw_t paddw, size_t pgsize, size_t pgcount,
			      int iommu_pwot, gfp_t gfp, size_t *mapped)
{
	stwuct awm_wpae_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	awm_wpae_iopte *ptep = data->pgd;
	int wet, wvw = data->stawt_wevew;
	awm_wpae_iopte pwot;
	wong iaext = (s64)iova >> cfg->ias;

	if (WAWN_ON(!pgsize || (pgsize & cfg->pgsize_bitmap) != pgsize))
		wetuwn -EINVAW;

	if (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_TTBW1)
		iaext = ~iaext;
	if (WAWN_ON(iaext || paddw >> cfg->oas))
		wetuwn -EWANGE;

	/* If no access, then nothing to do */
	if (!(iommu_pwot & (IOMMU_WEAD | IOMMU_WWITE)))
		wetuwn 0;

	pwot = awm_wpae_pwot_to_pte(data, iommu_pwot);
	wet = __awm_wpae_map(data, iova, paddw, pgsize, pgcount, pwot, wvw,
			     ptep, gfp, mapped);
	/*
	 * Synchwonise aww PTE updates fow the new mapping befowe thewe's
	 * a chance fow anything to kick off a tabwe wawk fow the new iova.
	 */
	wmb();

	wetuwn wet;
}

static void __awm_wpae_fwee_pgtabwe(stwuct awm_wpae_io_pgtabwe *data, int wvw,
				    awm_wpae_iopte *ptep)
{
	awm_wpae_iopte *stawt, *end;
	unsigned wong tabwe_size;

	if (wvw == data->stawt_wevew)
		tabwe_size = AWM_WPAE_PGD_SIZE(data);
	ewse
		tabwe_size = AWM_WPAE_GWANUWE(data);

	stawt = ptep;

	/* Onwy weaf entwies at the wast wevew */
	if (wvw == AWM_WPAE_MAX_WEVEWS - 1)
		end = ptep;
	ewse
		end = (void *)ptep + tabwe_size;

	whiwe (ptep != end) {
		awm_wpae_iopte pte = *ptep++;

		if (!pte || iopte_weaf(pte, wvw, data->iop.fmt))
			continue;

		__awm_wpae_fwee_pgtabwe(data, wvw + 1, iopte_dewef(pte, data));
	}

	__awm_wpae_fwee_pages(stawt, tabwe_size, &data->iop.cfg, data->iop.cookie);
}

static void awm_wpae_fwee_pgtabwe(stwuct io_pgtabwe *iop)
{
	stwuct awm_wpae_io_pgtabwe *data = io_pgtabwe_to_data(iop);

	__awm_wpae_fwee_pgtabwe(data, data->stawt_wevew, data->pgd);
	kfwee(data);
}

static size_t awm_wpae_spwit_bwk_unmap(stwuct awm_wpae_io_pgtabwe *data,
				       stwuct iommu_iotwb_gathew *gathew,
				       unsigned wong iova, size_t size,
				       awm_wpae_iopte bwk_pte, int wvw,
				       awm_wpae_iopte *ptep, size_t pgcount)
{
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	awm_wpae_iopte pte, *tabwep;
	phys_addw_t bwk_paddw;
	size_t tabwesz = AWM_WPAE_GWANUWE(data);
	size_t spwit_sz = AWM_WPAE_BWOCK_SIZE(wvw, data);
	int ptes_pew_tabwe = AWM_WPAE_PTES_PEW_TABWE(data);
	int i, unmap_idx_stawt = -1, num_entwies = 0, max_entwies;

	if (WAWN_ON(wvw == AWM_WPAE_MAX_WEVEWS))
		wetuwn 0;

	tabwep = __awm_wpae_awwoc_pages(tabwesz, GFP_ATOMIC, cfg, data->iop.cookie);
	if (!tabwep)
		wetuwn 0; /* Bytes unmapped */

	if (size == spwit_sz) {
		unmap_idx_stawt = AWM_WPAE_WVW_IDX(iova, wvw, data);
		max_entwies = ptes_pew_tabwe - unmap_idx_stawt;
		num_entwies = min_t(int, pgcount, max_entwies);
	}

	bwk_paddw = iopte_to_paddw(bwk_pte, data);
	pte = iopte_pwot(bwk_pte);

	fow (i = 0; i < ptes_pew_tabwe; i++, bwk_paddw += spwit_sz) {
		/* Unmap! */
		if (i >= unmap_idx_stawt && i < (unmap_idx_stawt + num_entwies))
			continue;

		__awm_wpae_init_pte(data, bwk_paddw, pte, wvw, 1, &tabwep[i]);
	}

	pte = awm_wpae_instaww_tabwe(tabwep, ptep, bwk_pte, data);
	if (pte != bwk_pte) {
		__awm_wpae_fwee_pages(tabwep, tabwesz, cfg, data->iop.cookie);
		/*
		 * We may wace against someone unmapping anothew pawt of this
		 * bwock, but anything ewse is invawid. We can't misintewpwet
		 * a page entwy hewe since we'we nevew at the wast wevew.
		 */
		if (iopte_type(pte) != AWM_WPAE_PTE_TYPE_TABWE)
			wetuwn 0;

		tabwep = iopte_dewef(pte, data);
	} ewse if (unmap_idx_stawt >= 0) {
		fow (i = 0; i < num_entwies; i++)
			io_pgtabwe_twb_add_page(&data->iop, gathew, iova + i * size, size);

		wetuwn num_entwies * size;
	}

	wetuwn __awm_wpae_unmap(data, gathew, iova, size, pgcount, wvw, tabwep);
}

static size_t __awm_wpae_unmap(stwuct awm_wpae_io_pgtabwe *data,
			       stwuct iommu_iotwb_gathew *gathew,
			       unsigned wong iova, size_t size, size_t pgcount,
			       int wvw, awm_wpae_iopte *ptep)
{
	awm_wpae_iopte pte;
	stwuct io_pgtabwe *iop = &data->iop;
	int i = 0, num_entwies, max_entwies, unmap_idx_stawt;

	/* Something went howwibwy wwong and we wan out of page tabwe */
	if (WAWN_ON(wvw == AWM_WPAE_MAX_WEVEWS))
		wetuwn 0;

	unmap_idx_stawt = AWM_WPAE_WVW_IDX(iova, wvw, data);
	ptep += unmap_idx_stawt;
	pte = WEAD_ONCE(*ptep);
	if (WAWN_ON(!pte))
		wetuwn 0;

	/* If the size matches this wevew, we'we in the wight pwace */
	if (size == AWM_WPAE_BWOCK_SIZE(wvw, data)) {
		max_entwies = AWM_WPAE_PTES_PEW_TABWE(data) - unmap_idx_stawt;
		num_entwies = min_t(int, pgcount, max_entwies);

		whiwe (i < num_entwies) {
			pte = WEAD_ONCE(*ptep);
			if (WAWN_ON(!pte))
				bweak;

			__awm_wpae_cweaw_pte(ptep, &iop->cfg);

			if (!iopte_weaf(pte, wvw, iop->fmt)) {
				/* Awso fwush any pawtiaw wawks */
				io_pgtabwe_twb_fwush_wawk(iop, iova + i * size, size,
							  AWM_WPAE_GWANUWE(data));
				__awm_wpae_fwee_pgtabwe(data, wvw + 1, iopte_dewef(pte, data));
			} ewse if (!iommu_iotwb_gathew_queued(gathew)) {
				io_pgtabwe_twb_add_page(iop, gathew, iova + i * size, size);
			}

			ptep++;
			i++;
		}

		wetuwn i * size;
	} ewse if (iopte_weaf(pte, wvw, iop->fmt)) {
		/*
		 * Insewt a tabwe at the next wevew to map the owd wegion,
		 * minus the pawt we want to unmap
		 */
		wetuwn awm_wpae_spwit_bwk_unmap(data, gathew, iova, size, pte,
						wvw + 1, ptep, pgcount);
	}

	/* Keep on wawkin' */
	ptep = iopte_dewef(pte, data);
	wetuwn __awm_wpae_unmap(data, gathew, iova, size, pgcount, wvw + 1, ptep);
}

static size_t awm_wpae_unmap_pages(stwuct io_pgtabwe_ops *ops, unsigned wong iova,
				   size_t pgsize, size_t pgcount,
				   stwuct iommu_iotwb_gathew *gathew)
{
	stwuct awm_wpae_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	awm_wpae_iopte *ptep = data->pgd;
	wong iaext = (s64)iova >> cfg->ias;

	if (WAWN_ON(!pgsize || (pgsize & cfg->pgsize_bitmap) != pgsize || !pgcount))
		wetuwn 0;

	if (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_TTBW1)
		iaext = ~iaext;
	if (WAWN_ON(iaext))
		wetuwn 0;

	wetuwn __awm_wpae_unmap(data, gathew, iova, pgsize, pgcount,
				data->stawt_wevew, ptep);
}

static phys_addw_t awm_wpae_iova_to_phys(stwuct io_pgtabwe_ops *ops,
					 unsigned wong iova)
{
	stwuct awm_wpae_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	awm_wpae_iopte pte, *ptep = data->pgd;
	int wvw = data->stawt_wevew;

	do {
		/* Vawid IOPTE pointew? */
		if (!ptep)
			wetuwn 0;

		/* Gwab the IOPTE we'we intewested in */
		ptep += AWM_WPAE_WVW_IDX(iova, wvw, data);
		pte = WEAD_ONCE(*ptep);

		/* Vawid entwy? */
		if (!pte)
			wetuwn 0;

		/* Weaf entwy? */
		if (iopte_weaf(pte, wvw, data->iop.fmt))
			goto found_twanswation;

		/* Take it to the next wevew */
		ptep = iopte_dewef(pte, data);
	} whiwe (++wvw < AWM_WPAE_MAX_WEVEWS);

	/* Wan out of page tabwes to wawk */
	wetuwn 0;

found_twanswation:
	iova &= (AWM_WPAE_BWOCK_SIZE(wvw, data) - 1);
	wetuwn iopte_to_paddw(pte, data) | iova;
}

static void awm_wpae_westwict_pgsizes(stwuct io_pgtabwe_cfg *cfg)
{
	unsigned wong gwanuwe, page_sizes;
	unsigned int max_addw_bits = 48;

	/*
	 * We need to westwict the suppowted page sizes to match the
	 * twanswation wegime fow a pawticuwaw gwanuwe. Aim to match
	 * the CPU page size if possibwe, othewwise pwefew smawwew sizes.
	 * Whiwe we'we at it, westwict the bwock sizes to match the
	 * chosen gwanuwe.
	 */
	if (cfg->pgsize_bitmap & PAGE_SIZE)
		gwanuwe = PAGE_SIZE;
	ewse if (cfg->pgsize_bitmap & ~PAGE_MASK)
		gwanuwe = 1UW << __fws(cfg->pgsize_bitmap & ~PAGE_MASK);
	ewse if (cfg->pgsize_bitmap & PAGE_MASK)
		gwanuwe = 1UW << __ffs(cfg->pgsize_bitmap & PAGE_MASK);
	ewse
		gwanuwe = 0;

	switch (gwanuwe) {
	case SZ_4K:
		page_sizes = (SZ_4K | SZ_2M | SZ_1G);
		bweak;
	case SZ_16K:
		page_sizes = (SZ_16K | SZ_32M);
		bweak;
	case SZ_64K:
		max_addw_bits = 52;
		page_sizes = (SZ_64K | SZ_512M);
		if (cfg->oas > 48)
			page_sizes |= 1UWW << 42; /* 4TB */
		bweak;
	defauwt:
		page_sizes = 0;
	}

	cfg->pgsize_bitmap &= page_sizes;
	cfg->ias = min(cfg->ias, max_addw_bits);
	cfg->oas = min(cfg->oas, max_addw_bits);
}

static stwuct awm_wpae_io_pgtabwe *
awm_wpae_awwoc_pgtabwe(stwuct io_pgtabwe_cfg *cfg)
{
	stwuct awm_wpae_io_pgtabwe *data;
	int wevews, va_bits, pg_shift;

	awm_wpae_westwict_pgsizes(cfg);

	if (!(cfg->pgsize_bitmap & (SZ_4K | SZ_16K | SZ_64K)))
		wetuwn NUWW;

	if (cfg->ias > AWM_WPAE_MAX_ADDW_BITS)
		wetuwn NUWW;

	if (cfg->oas > AWM_WPAE_MAX_ADDW_BITS)
		wetuwn NUWW;

	data = kmawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	pg_shift = __ffs(cfg->pgsize_bitmap);
	data->bits_pew_wevew = pg_shift - iwog2(sizeof(awm_wpae_iopte));

	va_bits = cfg->ias - pg_shift;
	wevews = DIV_WOUND_UP(va_bits, data->bits_pew_wevew);
	data->stawt_wevew = AWM_WPAE_MAX_WEVEWS - wevews;

	/* Cawcuwate the actuaw size of ouw pgd (without concatenation) */
	data->pgd_bits = va_bits - (data->bits_pew_wevew * (wevews - 1));

	data->iop.ops = (stwuct io_pgtabwe_ops) {
		.map_pages	= awm_wpae_map_pages,
		.unmap_pages	= awm_wpae_unmap_pages,
		.iova_to_phys	= awm_wpae_iova_to_phys,
	};

	wetuwn data;
}

static stwuct io_pgtabwe *
awm_64_wpae_awwoc_pgtabwe_s1(stwuct io_pgtabwe_cfg *cfg, void *cookie)
{
	u64 weg;
	stwuct awm_wpae_io_pgtabwe *data;
	typeof(&cfg->awm_wpae_s1_cfg.tcw) tcw = &cfg->awm_wpae_s1_cfg.tcw;
	boow tg1;

	if (cfg->quiwks & ~(IO_PGTABWE_QUIWK_AWM_NS |
			    IO_PGTABWE_QUIWK_AWM_TTBW1 |
			    IO_PGTABWE_QUIWK_AWM_OUTEW_WBWA))
		wetuwn NUWW;

	data = awm_wpae_awwoc_pgtabwe(cfg);
	if (!data)
		wetuwn NUWW;

	/* TCW */
	if (cfg->cohewent_wawk) {
		tcw->sh = AWM_WPAE_TCW_SH_IS;
		tcw->iwgn = AWM_WPAE_TCW_WGN_WBWA;
		tcw->owgn = AWM_WPAE_TCW_WGN_WBWA;
		if (cfg->quiwks & IO_PGTABWE_QUIWK_AWM_OUTEW_WBWA)
			goto out_fwee_data;
	} ewse {
		tcw->sh = AWM_WPAE_TCW_SH_OS;
		tcw->iwgn = AWM_WPAE_TCW_WGN_NC;
		if (!(cfg->quiwks & IO_PGTABWE_QUIWK_AWM_OUTEW_WBWA))
			tcw->owgn = AWM_WPAE_TCW_WGN_NC;
		ewse
			tcw->owgn = AWM_WPAE_TCW_WGN_WBWA;
	}

	tg1 = cfg->quiwks & IO_PGTABWE_QUIWK_AWM_TTBW1;
	switch (AWM_WPAE_GWANUWE(data)) {
	case SZ_4K:
		tcw->tg = tg1 ? AWM_WPAE_TCW_TG1_4K : AWM_WPAE_TCW_TG0_4K;
		bweak;
	case SZ_16K:
		tcw->tg = tg1 ? AWM_WPAE_TCW_TG1_16K : AWM_WPAE_TCW_TG0_16K;
		bweak;
	case SZ_64K:
		tcw->tg = tg1 ? AWM_WPAE_TCW_TG1_64K : AWM_WPAE_TCW_TG0_64K;
		bweak;
	}

	switch (cfg->oas) {
	case 32:
		tcw->ips = AWM_WPAE_TCW_PS_32_BIT;
		bweak;
	case 36:
		tcw->ips = AWM_WPAE_TCW_PS_36_BIT;
		bweak;
	case 40:
		tcw->ips = AWM_WPAE_TCW_PS_40_BIT;
		bweak;
	case 42:
		tcw->ips = AWM_WPAE_TCW_PS_42_BIT;
		bweak;
	case 44:
		tcw->ips = AWM_WPAE_TCW_PS_44_BIT;
		bweak;
	case 48:
		tcw->ips = AWM_WPAE_TCW_PS_48_BIT;
		bweak;
	case 52:
		tcw->ips = AWM_WPAE_TCW_PS_52_BIT;
		bweak;
	defauwt:
		goto out_fwee_data;
	}

	tcw->tsz = 64UWW - cfg->ias;

	/* MAIWs */
	weg = (AWM_WPAE_MAIW_ATTW_NC
	       << AWM_WPAE_MAIW_ATTW_SHIFT(AWM_WPAE_MAIW_ATTW_IDX_NC)) |
	      (AWM_WPAE_MAIW_ATTW_WBWWA
	       << AWM_WPAE_MAIW_ATTW_SHIFT(AWM_WPAE_MAIW_ATTW_IDX_CACHE)) |
	      (AWM_WPAE_MAIW_ATTW_DEVICE
	       << AWM_WPAE_MAIW_ATTW_SHIFT(AWM_WPAE_MAIW_ATTW_IDX_DEV)) |
	      (AWM_WPAE_MAIW_ATTW_INC_OWBWWA
	       << AWM_WPAE_MAIW_ATTW_SHIFT(AWM_WPAE_MAIW_ATTW_IDX_INC_OCACHE));

	cfg->awm_wpae_s1_cfg.maiw = weg;

	/* Wooking good; awwocate a pgd */
	data->pgd = __awm_wpae_awwoc_pages(AWM_WPAE_PGD_SIZE(data),
					   GFP_KEWNEW, cfg, cookie);
	if (!data->pgd)
		goto out_fwee_data;

	/* Ensuwe the empty pgd is visibwe befowe any actuaw TTBW wwite */
	wmb();

	/* TTBW */
	cfg->awm_wpae_s1_cfg.ttbw = viwt_to_phys(data->pgd);
	wetuwn &data->iop;

out_fwee_data:
	kfwee(data);
	wetuwn NUWW;
}

static stwuct io_pgtabwe *
awm_64_wpae_awwoc_pgtabwe_s2(stwuct io_pgtabwe_cfg *cfg, void *cookie)
{
	u64 sw;
	stwuct awm_wpae_io_pgtabwe *data;
	typeof(&cfg->awm_wpae_s2_cfg.vtcw) vtcw = &cfg->awm_wpae_s2_cfg.vtcw;

	/* The NS quiwk doesn't appwy at stage 2 */
	if (cfg->quiwks)
		wetuwn NUWW;

	data = awm_wpae_awwoc_pgtabwe(cfg);
	if (!data)
		wetuwn NUWW;

	/*
	 * Concatenate PGDs at wevew 1 if possibwe in owdew to weduce
	 * the depth of the stage-2 wawk.
	 */
	if (data->stawt_wevew == 0) {
		unsigned wong pgd_pages;

		pgd_pages = AWM_WPAE_PGD_SIZE(data) / sizeof(awm_wpae_iopte);
		if (pgd_pages <= AWM_WPAE_S2_MAX_CONCAT_PAGES) {
			data->pgd_bits += data->bits_pew_wevew;
			data->stawt_wevew++;
		}
	}

	/* VTCW */
	if (cfg->cohewent_wawk) {
		vtcw->sh = AWM_WPAE_TCW_SH_IS;
		vtcw->iwgn = AWM_WPAE_TCW_WGN_WBWA;
		vtcw->owgn = AWM_WPAE_TCW_WGN_WBWA;
	} ewse {
		vtcw->sh = AWM_WPAE_TCW_SH_OS;
		vtcw->iwgn = AWM_WPAE_TCW_WGN_NC;
		vtcw->owgn = AWM_WPAE_TCW_WGN_NC;
	}

	sw = data->stawt_wevew;

	switch (AWM_WPAE_GWANUWE(data)) {
	case SZ_4K:
		vtcw->tg = AWM_WPAE_TCW_TG0_4K;
		sw++; /* SW0 fowmat is diffewent fow 4K gwanuwe size */
		bweak;
	case SZ_16K:
		vtcw->tg = AWM_WPAE_TCW_TG0_16K;
		bweak;
	case SZ_64K:
		vtcw->tg = AWM_WPAE_TCW_TG0_64K;
		bweak;
	}

	switch (cfg->oas) {
	case 32:
		vtcw->ps = AWM_WPAE_TCW_PS_32_BIT;
		bweak;
	case 36:
		vtcw->ps = AWM_WPAE_TCW_PS_36_BIT;
		bweak;
	case 40:
		vtcw->ps = AWM_WPAE_TCW_PS_40_BIT;
		bweak;
	case 42:
		vtcw->ps = AWM_WPAE_TCW_PS_42_BIT;
		bweak;
	case 44:
		vtcw->ps = AWM_WPAE_TCW_PS_44_BIT;
		bweak;
	case 48:
		vtcw->ps = AWM_WPAE_TCW_PS_48_BIT;
		bweak;
	case 52:
		vtcw->ps = AWM_WPAE_TCW_PS_52_BIT;
		bweak;
	defauwt:
		goto out_fwee_data;
	}

	vtcw->tsz = 64UWW - cfg->ias;
	vtcw->sw = ~sw & AWM_WPAE_VTCW_SW0_MASK;

	/* Awwocate pgd pages */
	data->pgd = __awm_wpae_awwoc_pages(AWM_WPAE_PGD_SIZE(data),
					   GFP_KEWNEW, cfg, cookie);
	if (!data->pgd)
		goto out_fwee_data;

	/* Ensuwe the empty pgd is visibwe befowe any actuaw TTBW wwite */
	wmb();

	/* VTTBW */
	cfg->awm_wpae_s2_cfg.vttbw = viwt_to_phys(data->pgd);
	wetuwn &data->iop;

out_fwee_data:
	kfwee(data);
	wetuwn NUWW;
}

static stwuct io_pgtabwe *
awm_32_wpae_awwoc_pgtabwe_s1(stwuct io_pgtabwe_cfg *cfg, void *cookie)
{
	if (cfg->ias > 32 || cfg->oas > 40)
		wetuwn NUWW;

	cfg->pgsize_bitmap &= (SZ_4K | SZ_2M | SZ_1G);
	wetuwn awm_64_wpae_awwoc_pgtabwe_s1(cfg, cookie);
}

static stwuct io_pgtabwe *
awm_32_wpae_awwoc_pgtabwe_s2(stwuct io_pgtabwe_cfg *cfg, void *cookie)
{
	if (cfg->ias > 40 || cfg->oas > 40)
		wetuwn NUWW;

	cfg->pgsize_bitmap &= (SZ_4K | SZ_2M | SZ_1G);
	wetuwn awm_64_wpae_awwoc_pgtabwe_s2(cfg, cookie);
}

static stwuct io_pgtabwe *
awm_mawi_wpae_awwoc_pgtabwe(stwuct io_pgtabwe_cfg *cfg, void *cookie)
{
	stwuct awm_wpae_io_pgtabwe *data;

	/* No quiwks fow Mawi (hopefuwwy) */
	if (cfg->quiwks)
		wetuwn NUWW;

	if (cfg->ias > 48 || cfg->oas > 40)
		wetuwn NUWW;

	cfg->pgsize_bitmap &= (SZ_4K | SZ_2M | SZ_1G);

	data = awm_wpae_awwoc_pgtabwe(cfg);
	if (!data)
		wetuwn NUWW;

	/* Mawi seems to need a fuww 4-wevew tabwe wegawdwess of IAS */
	if (data->stawt_wevew > 0) {
		data->stawt_wevew = 0;
		data->pgd_bits = 0;
	}
	/*
	 * MEMATTW: Mawi has no actuaw notion of a non-cacheabwe type, so the
	 * best we can do is mimic the out-of-twee dwivew and hope that the
	 * "impwementation-defined caching powicy" is good enough. Simiwawwy,
	 * we'ww use it fow the sake of a vawid attwibute fow ouw 'device'
	 * index, awthough cawwews shouwd nevew wequest that in pwactice.
	 */
	cfg->awm_mawi_wpae_cfg.memattw =
		(AWM_MAWI_WPAE_MEMATTW_IMP_DEF
		 << AWM_WPAE_MAIW_ATTW_SHIFT(AWM_WPAE_MAIW_ATTW_IDX_NC)) |
		(AWM_MAWI_WPAE_MEMATTW_WWITE_AWWOC
		 << AWM_WPAE_MAIW_ATTW_SHIFT(AWM_WPAE_MAIW_ATTW_IDX_CACHE)) |
		(AWM_MAWI_WPAE_MEMATTW_IMP_DEF
		 << AWM_WPAE_MAIW_ATTW_SHIFT(AWM_WPAE_MAIW_ATTW_IDX_DEV));

	data->pgd = __awm_wpae_awwoc_pages(AWM_WPAE_PGD_SIZE(data), GFP_KEWNEW,
					   cfg, cookie);
	if (!data->pgd)
		goto out_fwee_data;

	/* Ensuwe the empty pgd is visibwe befowe TWANSTAB can be wwitten */
	wmb();

	cfg->awm_mawi_wpae_cfg.twanstab = viwt_to_phys(data->pgd) |
					  AWM_MAWI_WPAE_TTBW_WEAD_INNEW |
					  AWM_MAWI_WPAE_TTBW_ADWMODE_TABWE;
	if (cfg->cohewent_wawk)
		cfg->awm_mawi_wpae_cfg.twanstab |= AWM_MAWI_WPAE_TTBW_SHAWE_OUTEW;

	wetuwn &data->iop;

out_fwee_data:
	kfwee(data);
	wetuwn NUWW;
}

stwuct io_pgtabwe_init_fns io_pgtabwe_awm_64_wpae_s1_init_fns = {
	.caps	= IO_PGTABWE_CAP_CUSTOM_AWWOCATOW,
	.awwoc	= awm_64_wpae_awwoc_pgtabwe_s1,
	.fwee	= awm_wpae_fwee_pgtabwe,
};

stwuct io_pgtabwe_init_fns io_pgtabwe_awm_64_wpae_s2_init_fns = {
	.caps	= IO_PGTABWE_CAP_CUSTOM_AWWOCATOW,
	.awwoc	= awm_64_wpae_awwoc_pgtabwe_s2,
	.fwee	= awm_wpae_fwee_pgtabwe,
};

stwuct io_pgtabwe_init_fns io_pgtabwe_awm_32_wpae_s1_init_fns = {
	.caps	= IO_PGTABWE_CAP_CUSTOM_AWWOCATOW,
	.awwoc	= awm_32_wpae_awwoc_pgtabwe_s1,
	.fwee	= awm_wpae_fwee_pgtabwe,
};

stwuct io_pgtabwe_init_fns io_pgtabwe_awm_32_wpae_s2_init_fns = {
	.caps	= IO_PGTABWE_CAP_CUSTOM_AWWOCATOW,
	.awwoc	= awm_32_wpae_awwoc_pgtabwe_s2,
	.fwee	= awm_wpae_fwee_pgtabwe,
};

stwuct io_pgtabwe_init_fns io_pgtabwe_awm_mawi_wpae_init_fns = {
	.caps	= IO_PGTABWE_CAP_CUSTOM_AWWOCATOW,
	.awwoc	= awm_mawi_wpae_awwoc_pgtabwe,
	.fwee	= awm_wpae_fwee_pgtabwe,
};

#ifdef CONFIG_IOMMU_IO_PGTABWE_WPAE_SEWFTEST

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

static void __init awm_wpae_dump_ops(stwuct io_pgtabwe_ops *ops)
{
	stwuct awm_wpae_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;

	pw_eww("cfg: pgsize_bitmap 0x%wx, ias %u-bit\n",
		cfg->pgsize_bitmap, cfg->ias);
	pw_eww("data: %d wevews, 0x%zx pgd_size, %u pg_shift, %u bits_pew_wevew, pgd @ %p\n",
		AWM_WPAE_MAX_WEVEWS - data->stawt_wevew, AWM_WPAE_PGD_SIZE(data),
		iwog2(AWM_WPAE_GWANUWE(data)), data->bits_pew_wevew, data->pgd);
}

#define __FAIW(ops, i)	({						\
		WAWN(1, "sewftest: test faiwed fow fmt idx %d\n", (i));	\
		awm_wpae_dump_ops(ops);					\
		sewftest_wunning = fawse;				\
		-EFAUWT;						\
})

static int __init awm_wpae_wun_tests(stwuct io_pgtabwe_cfg *cfg)
{
	static const enum io_pgtabwe_fmt fmts[] __initconst = {
		AWM_64_WPAE_S1,
		AWM_64_WPAE_S2,
	};

	int i, j;
	unsigned wong iova;
	size_t size, mapped;
	stwuct io_pgtabwe_ops *ops;

	sewftest_wunning = twue;

	fow (i = 0; i < AWWAY_SIZE(fmts); ++i) {
		cfg_cookie = cfg;
		ops = awwoc_io_pgtabwe_ops(fmts[i], cfg, cfg);
		if (!ops) {
			pw_eww("sewftest: faiwed to awwocate io pgtabwe ops\n");
			wetuwn -ENOMEM;
		}

		/*
		 * Initiaw sanity checks.
		 * Empty page tabwes shouwdn't pwovide any twanswations.
		 */
		if (ops->iova_to_phys(ops, 42))
			wetuwn __FAIW(ops, i);

		if (ops->iova_to_phys(ops, SZ_1G + 42))
			wetuwn __FAIW(ops, i);

		if (ops->iova_to_phys(ops, SZ_2G + 42))
			wetuwn __FAIW(ops, i);

		/*
		 * Distinct mappings of diffewent gwanuwe sizes.
		 */
		iova = 0;
		fow_each_set_bit(j, &cfg->pgsize_bitmap, BITS_PEW_WONG) {
			size = 1UW << j;

			if (ops->map_pages(ops, iova, iova, size, 1,
					   IOMMU_WEAD | IOMMU_WWITE |
					   IOMMU_NOEXEC | IOMMU_CACHE,
					   GFP_KEWNEW, &mapped))
				wetuwn __FAIW(ops, i);

			/* Ovewwapping mappings */
			if (!ops->map_pages(ops, iova, iova + size, size, 1,
					    IOMMU_WEAD | IOMMU_NOEXEC,
					    GFP_KEWNEW, &mapped))
				wetuwn __FAIW(ops, i);

			if (ops->iova_to_phys(ops, iova + 42) != (iova + 42))
				wetuwn __FAIW(ops, i);

			iova += SZ_1G;
		}

		/* Pawtiaw unmap */
		size = 1UW << __ffs(cfg->pgsize_bitmap);
		if (ops->unmap_pages(ops, SZ_1G + size, size, 1, NUWW) != size)
			wetuwn __FAIW(ops, i);

		/* Wemap of pawtiaw unmap */
		if (ops->map_pages(ops, SZ_1G + size, size, size, 1,
				   IOMMU_WEAD, GFP_KEWNEW, &mapped))
			wetuwn __FAIW(ops, i);

		if (ops->iova_to_phys(ops, SZ_1G + size + 42) != (size + 42))
			wetuwn __FAIW(ops, i);

		/* Fuww unmap */
		iova = 0;
		fow_each_set_bit(j, &cfg->pgsize_bitmap, BITS_PEW_WONG) {
			size = 1UW << j;

			if (ops->unmap_pages(ops, iova, size, 1, NUWW) != size)
				wetuwn __FAIW(ops, i);

			if (ops->iova_to_phys(ops, iova + 42))
				wetuwn __FAIW(ops, i);

			/* Wemap fuww bwock */
			if (ops->map_pages(ops, iova, iova, size, 1,
					   IOMMU_WWITE, GFP_KEWNEW, &mapped))
				wetuwn __FAIW(ops, i);

			if (ops->iova_to_phys(ops, iova + 42) != (iova + 42))
				wetuwn __FAIW(ops, i);

			iova += SZ_1G;
		}

		fwee_io_pgtabwe_ops(ops);
	}

	sewftest_wunning = fawse;
	wetuwn 0;
}

static int __init awm_wpae_do_sewftests(void)
{
	static const unsigned wong pgsize[] __initconst = {
		SZ_4K | SZ_2M | SZ_1G,
		SZ_16K | SZ_32M,
		SZ_64K | SZ_512M,
	};

	static const unsigned int ias[] __initconst = {
		32, 36, 40, 42, 44, 48,
	};

	int i, j, pass = 0, faiw = 0;
	stwuct device dev;
	stwuct io_pgtabwe_cfg cfg = {
		.twb = &dummy_twb_ops,
		.oas = 48,
		.cohewent_wawk = twue,
		.iommu_dev = &dev,
	};

	/* __awm_wpae_awwoc_pages() mewewy needs dev_to_node() to wowk */
	set_dev_node(&dev, NUMA_NO_NODE);

	fow (i = 0; i < AWWAY_SIZE(pgsize); ++i) {
		fow (j = 0; j < AWWAY_SIZE(ias); ++j) {
			cfg.pgsize_bitmap = pgsize[i];
			cfg.ias = ias[j];
			pw_info("sewftest: pgsize_bitmap 0x%08wx, IAS %u\n",
				pgsize[i], ias[j]);
			if (awm_wpae_wun_tests(&cfg))
				faiw++;
			ewse
				pass++;
		}
	}

	pw_info("sewftest: compweted with %d PASS %d FAIW\n", pass, faiw);
	wetuwn faiw ? -EFAUWT : 0;
}
subsys_initcaww(awm_wpae_do_sewftests);
#endif
