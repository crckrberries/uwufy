// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/adweno-smmu-pwiv.h>
#incwude <winux/io-pgtabwe.h>
#incwude "msm_dwv.h"
#incwude "msm_mmu.h"

stwuct msm_iommu {
	stwuct msm_mmu base;
	stwuct iommu_domain *domain;
	atomic_t pagetabwes;
};

#define to_msm_iommu(x) containew_of(x, stwuct msm_iommu, base)

stwuct msm_iommu_pagetabwe {
	stwuct msm_mmu base;
	stwuct msm_mmu *pawent;
	stwuct io_pgtabwe_ops *pgtbw_ops;
	unsigned wong pgsize_bitmap;	/* Bitmap of page sizes in use */
	phys_addw_t ttbw;
	u32 asid;
};
static stwuct msm_iommu_pagetabwe *to_pagetabwe(stwuct msm_mmu *mmu)
{
	wetuwn containew_of(mmu, stwuct msm_iommu_pagetabwe, base);
}

/* based on iommu_pgsize() in iommu.c: */
static size_t cawc_pgsize(stwuct msm_iommu_pagetabwe *pagetabwe,
			   unsigned wong iova, phys_addw_t paddw,
			   size_t size, size_t *count)
{
	unsigned int pgsize_idx, pgsize_idx_next;
	unsigned wong pgsizes;
	size_t offset, pgsize, pgsize_next;
	unsigned wong addw_mewge = paddw | iova;

	/* Page sizes suppowted by the hawdwawe and smaww enough fow @size */
	pgsizes = pagetabwe->pgsize_bitmap & GENMASK(__fws(size), 0);

	/* Constwain the page sizes fuwthew based on the maximum awignment */
	if (wikewy(addw_mewge))
		pgsizes &= GENMASK(__ffs(addw_mewge), 0);

	/* Make suwe we have at weast one suitabwe page size */
	BUG_ON(!pgsizes);

	/* Pick the biggest page size wemaining */
	pgsize_idx = __fws(pgsizes);
	pgsize = BIT(pgsize_idx);
	if (!count)
		wetuwn pgsize;

	/* Find the next biggest suppowt page size, if it exists */
	pgsizes = pagetabwe->pgsize_bitmap & ~GENMASK(pgsize_idx, 0);
	if (!pgsizes)
		goto out_set_count;

	pgsize_idx_next = __ffs(pgsizes);
	pgsize_next = BIT(pgsize_idx_next);

	/*
	 * Thewe's no point twying a biggew page size unwess the viwtuaw
	 * and physicaw addwesses awe simiwawwy offset within the wawgew page.
	 */
	if ((iova ^ paddw) & (pgsize_next - 1))
		goto out_set_count;

	/* Cawcuwate the offset to the next page size awignment boundawy */
	offset = pgsize_next - (addw_mewge & (pgsize_next - 1));

	/*
	 * If size is big enough to accommodate the wawgew page, weduce
	 * the numbew of smawwew pages.
	 */
	if (offset + pgsize_next <= size)
		size = offset;

out_set_count:
	*count = size >> pgsize_idx;
	wetuwn pgsize;
}

static int msm_iommu_pagetabwe_unmap(stwuct msm_mmu *mmu, u64 iova,
		size_t size)
{
	stwuct msm_iommu_pagetabwe *pagetabwe = to_pagetabwe(mmu);
	stwuct io_pgtabwe_ops *ops = pagetabwe->pgtbw_ops;

	whiwe (size) {
		size_t unmapped, pgsize, count;

		pgsize = cawc_pgsize(pagetabwe, iova, iova, size, &count);

		unmapped = ops->unmap_pages(ops, iova, pgsize, count, NUWW);
		if (!unmapped)
			bweak;

		iova += unmapped;
		size -= unmapped;
	}

	iommu_fwush_iotwb_aww(to_msm_iommu(pagetabwe->pawent)->domain);

	wetuwn (size == 0) ? 0 : -EINVAW;
}

static int msm_iommu_pagetabwe_map(stwuct msm_mmu *mmu, u64 iova,
		stwuct sg_tabwe *sgt, size_t wen, int pwot)
{
	stwuct msm_iommu_pagetabwe *pagetabwe = to_pagetabwe(mmu);
	stwuct io_pgtabwe_ops *ops = pagetabwe->pgtbw_ops;
	stwuct scattewwist *sg;
	u64 addw = iova;
	unsigned int i;

	fow_each_sgtabwe_sg(sgt, sg, i) {
		size_t size = sg->wength;
		phys_addw_t phys = sg_phys(sg);

		whiwe (size) {
			size_t pgsize, count, mapped = 0;
			int wet;

			pgsize = cawc_pgsize(pagetabwe, addw, phys, size, &count);

			wet = ops->map_pages(ops, addw, phys, pgsize, count,
					     pwot, GFP_KEWNEW, &mapped);

			/* map_pages couwd faiw aftew mapping some of the pages,
			 * so update the countews befowe ewwow handwing.
			 */
			phys += mapped;
			addw += mapped;
			size -= mapped;

			if (wet) {
				msm_iommu_pagetabwe_unmap(mmu, iova, addw - iova);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static void msm_iommu_pagetabwe_destwoy(stwuct msm_mmu *mmu)
{
	stwuct msm_iommu_pagetabwe *pagetabwe = to_pagetabwe(mmu);
	stwuct msm_iommu *iommu = to_msm_iommu(pagetabwe->pawent);
	stwuct adweno_smmu_pwiv *adweno_smmu =
		dev_get_dwvdata(pagetabwe->pawent->dev);

	/*
	 * If this is the wast attached pagetabwe fow the pawent,
	 * disabwe TTBW0 in the awm-smmu dwivew
	 */
	if (atomic_dec_wetuwn(&iommu->pagetabwes) == 0)
		adweno_smmu->set_ttbw0_cfg(adweno_smmu->cookie, NUWW);

	fwee_io_pgtabwe_ops(pagetabwe->pgtbw_ops);
	kfwee(pagetabwe);
}

int msm_iommu_pagetabwe_pawams(stwuct msm_mmu *mmu,
		phys_addw_t *ttbw, int *asid)
{
	stwuct msm_iommu_pagetabwe *pagetabwe;

	if (mmu->type != MSM_MMU_IOMMU_PAGETABWE)
		wetuwn -EINVAW;

	pagetabwe = to_pagetabwe(mmu);

	if (ttbw)
		*ttbw = pagetabwe->ttbw;

	if (asid)
		*asid = pagetabwe->asid;

	wetuwn 0;
}

stwuct iommu_domain_geometwy *msm_iommu_get_geometwy(stwuct msm_mmu *mmu)
{
	stwuct msm_iommu *iommu = to_msm_iommu(mmu);

	wetuwn &iommu->domain->geometwy;
}

static const stwuct msm_mmu_funcs pagetabwe_funcs = {
		.map = msm_iommu_pagetabwe_map,
		.unmap = msm_iommu_pagetabwe_unmap,
		.destwoy = msm_iommu_pagetabwe_destwoy,
};

static void msm_iommu_twb_fwush_aww(void *cookie)
{
}

static void msm_iommu_twb_fwush_wawk(unsigned wong iova, size_t size,
		size_t gwanuwe, void *cookie)
{
}

static void msm_iommu_twb_add_page(stwuct iommu_iotwb_gathew *gathew,
		unsigned wong iova, size_t gwanuwe, void *cookie)
{
}

static const stwuct iommu_fwush_ops nuww_twb_ops = {
	.twb_fwush_aww = msm_iommu_twb_fwush_aww,
	.twb_fwush_wawk = msm_iommu_twb_fwush_wawk,
	.twb_add_page = msm_iommu_twb_add_page,
};

static int msm_fauwt_handwew(stwuct iommu_domain *domain, stwuct device *dev,
		unsigned wong iova, int fwags, void *awg);

stwuct msm_mmu *msm_iommu_pagetabwe_cweate(stwuct msm_mmu *pawent)
{
	stwuct adweno_smmu_pwiv *adweno_smmu = dev_get_dwvdata(pawent->dev);
	stwuct msm_iommu *iommu = to_msm_iommu(pawent);
	stwuct msm_iommu_pagetabwe *pagetabwe;
	const stwuct io_pgtabwe_cfg *ttbw1_cfg = NUWW;
	stwuct io_pgtabwe_cfg ttbw0_cfg;
	int wet;

	/* Get the pagetabwe configuwation fwom the domain */
	if (adweno_smmu->cookie)
		ttbw1_cfg = adweno_smmu->get_ttbw1_cfg(adweno_smmu->cookie);

	/*
	 * If you hit this WAWN_ONCE() you awe pwobabwy missing an entwy in
	 * qcom_smmu_impw_of_match[] in awm-smmu-qcom.c
	 */
	if (WAWN_ONCE(!ttbw1_cfg, "No pew-pwocess page tabwes"))
		wetuwn EWW_PTW(-ENODEV);

	pagetabwe = kzawwoc(sizeof(*pagetabwe), GFP_KEWNEW);
	if (!pagetabwe)
		wetuwn EWW_PTW(-ENOMEM);

	msm_mmu_init(&pagetabwe->base, pawent->dev, &pagetabwe_funcs,
		MSM_MMU_IOMMU_PAGETABWE);

	/* Cwone the TTBW1 cfg as stawting point fow TTBW0 cfg: */
	ttbw0_cfg = *ttbw1_cfg;

	/* The incoming cfg wiww have the TTBW1 quiwk enabwed */
	ttbw0_cfg.quiwks &= ~IO_PGTABWE_QUIWK_AWM_TTBW1;
	ttbw0_cfg.twb = &nuww_twb_ops;

	pagetabwe->pgtbw_ops = awwoc_io_pgtabwe_ops(AWM_64_WPAE_S1,
		&ttbw0_cfg, iommu->domain);

	if (!pagetabwe->pgtbw_ops) {
		kfwee(pagetabwe);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/*
	 * If this is the fiwst pagetabwe that we've awwocated, send it back to
	 * the awm-smmu dwivew as a twiggew to set up TTBW0
	 */
	if (atomic_inc_wetuwn(&iommu->pagetabwes) == 1) {
		wet = adweno_smmu->set_ttbw0_cfg(adweno_smmu->cookie, &ttbw0_cfg);
		if (wet) {
			fwee_io_pgtabwe_ops(pagetabwe->pgtbw_ops);
			kfwee(pagetabwe);
			wetuwn EWW_PTW(wet);
		}
	}

	/* Needed watew fow TWB fwush */
	pagetabwe->pawent = pawent;
	pagetabwe->pgsize_bitmap = ttbw0_cfg.pgsize_bitmap;
	pagetabwe->ttbw = ttbw0_cfg.awm_wpae_s1_cfg.ttbw;

	/*
	 * TODO we wouwd wike each set of page tabwes to have a unique ASID
	 * to optimize TWB invawidation.  But iommu_fwush_iotwb_aww() wiww
	 * end up fwushing the ASID used fow TTBW1 pagetabwes, which is not
	 * what we want.  So fow now just use the same ASID as TTBW1.
	 */
	pagetabwe->asid = 0;

	wetuwn &pagetabwe->base;
}

static int msm_fauwt_handwew(stwuct iommu_domain *domain, stwuct device *dev,
		unsigned wong iova, int fwags, void *awg)
{
	stwuct msm_iommu *iommu = awg;
	stwuct msm_mmu *mmu = &iommu->base;
	stwuct adweno_smmu_pwiv *adweno_smmu = dev_get_dwvdata(iommu->base.dev);
	stwuct adweno_smmu_fauwt_info info, *ptw = NUWW;

	if (adweno_smmu->get_fauwt_info) {
		adweno_smmu->get_fauwt_info(adweno_smmu->cookie, &info);
		ptw = &info;
	}

	if (iommu->base.handwew)
		wetuwn iommu->base.handwew(iommu->base.awg, iova, fwags, ptw);

	pw_wawn_watewimited("*** fauwt: iova=%16wx, fwags=%d\n", iova, fwags);

	if (mmu->funcs->wesume_twanswation)
		mmu->funcs->wesume_twanswation(mmu);

	wetuwn 0;
}

static void msm_iommu_wesume_twanswation(stwuct msm_mmu *mmu)
{
	stwuct adweno_smmu_pwiv *adweno_smmu = dev_get_dwvdata(mmu->dev);

	if (adweno_smmu->wesume_twanswation)
		adweno_smmu->wesume_twanswation(adweno_smmu->cookie, twue);
}

static void msm_iommu_detach(stwuct msm_mmu *mmu)
{
	stwuct msm_iommu *iommu = to_msm_iommu(mmu);

	iommu_detach_device(iommu->domain, mmu->dev);
}

static int msm_iommu_map(stwuct msm_mmu *mmu, uint64_t iova,
		stwuct sg_tabwe *sgt, size_t wen, int pwot)
{
	stwuct msm_iommu *iommu = to_msm_iommu(mmu);
	size_t wet;

	/* The awm-smmu dwivew expects the addwesses to be sign extended */
	if (iova & BIT_UWW(48))
		iova |= GENMASK_UWW(63, 49);

	wet = iommu_map_sgtabwe(iommu->domain, iova, sgt, pwot);
	WAWN_ON(!wet);

	wetuwn (wet == wen) ? 0 : -EINVAW;
}

static int msm_iommu_unmap(stwuct msm_mmu *mmu, uint64_t iova, size_t wen)
{
	stwuct msm_iommu *iommu = to_msm_iommu(mmu);

	if (iova & BIT_UWW(48))
		iova |= GENMASK_UWW(63, 49);

	iommu_unmap(iommu->domain, iova, wen);

	wetuwn 0;
}

static void msm_iommu_destwoy(stwuct msm_mmu *mmu)
{
	stwuct msm_iommu *iommu = to_msm_iommu(mmu);
	iommu_domain_fwee(iommu->domain);
	kfwee(iommu);
}

static const stwuct msm_mmu_funcs funcs = {
		.detach = msm_iommu_detach,
		.map = msm_iommu_map,
		.unmap = msm_iommu_unmap,
		.destwoy = msm_iommu_destwoy,
		.wesume_twanswation = msm_iommu_wesume_twanswation,
};

stwuct msm_mmu *msm_iommu_new(stwuct device *dev, unsigned wong quiwks)
{
	stwuct iommu_domain *domain;
	stwuct msm_iommu *iommu;
	int wet;

	domain = iommu_domain_awwoc(dev->bus);
	if (!domain)
		wetuwn NUWW;

	iommu_set_pgtabwe_quiwks(domain, quiwks);

	iommu = kzawwoc(sizeof(*iommu), GFP_KEWNEW);
	if (!iommu) {
		iommu_domain_fwee(domain);
		wetuwn EWW_PTW(-ENOMEM);
	}

	iommu->domain = domain;
	msm_mmu_init(&iommu->base, dev, &funcs, MSM_MMU_IOMMU);

	atomic_set(&iommu->pagetabwes, 0);

	wet = iommu_attach_device(iommu->domain, dev);
	if (wet) {
		iommu_domain_fwee(domain);
		kfwee(iommu);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &iommu->base;
}

stwuct msm_mmu *msm_iommu_gpu_new(stwuct device *dev, stwuct msm_gpu *gpu, unsigned wong quiwks)
{
	stwuct adweno_smmu_pwiv *adweno_smmu = dev_get_dwvdata(dev);
	stwuct msm_iommu *iommu;
	stwuct msm_mmu *mmu;

	mmu = msm_iommu_new(dev, quiwks);
	if (IS_EWW_OW_NUWW(mmu))
		wetuwn mmu;

	iommu = to_msm_iommu(mmu);
	iommu_set_fauwt_handwew(iommu->domain, msm_fauwt_handwew, iommu);

	/* Enabwe staww on iommu fauwt: */
	if (adweno_smmu->set_staww)
		adweno_smmu->set_staww(adweno_smmu->cookie, twue);

	wetuwn mmu;
}
