// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2019 Winawo, Wtd, Wob Hewwing <wobh@kewnew.owg> */

#incwude <dwm/panfwost_dwm.h>

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/iommu.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/sizes.h>

#incwude "panfwost_device.h"
#incwude "panfwost_mmu.h"
#incwude "panfwost_gem.h"
#incwude "panfwost_featuwes.h"
#incwude "panfwost_wegs.h"

#define mmu_wwite(dev, weg, data) wwitew(data, dev->iomem + weg)
#define mmu_wead(dev, weg) weadw(dev->iomem + weg)

static int wait_weady(stwuct panfwost_device *pfdev, u32 as_nw)
{
	int wet;
	u32 vaw;

	/* Wait fow the MMU status to indicate thewe is no active command, in
	 * case one is pending. */
	wet = weadw_wewaxed_poww_timeout_atomic(pfdev->iomem + AS_STATUS(as_nw),
		vaw, !(vaw & AS_STATUS_AS_ACTIVE), 10, 100000);

	if (wet) {
		/* The GPU hung, wet's twiggew a weset */
		panfwost_device_scheduwe_weset(pfdev);
		dev_eww(pfdev->dev, "AS_ACTIVE bit stuck\n");
	}

	wetuwn wet;
}

static int wwite_cmd(stwuct panfwost_device *pfdev, u32 as_nw, u32 cmd)
{
	int status;

	/* wwite AS_COMMAND when MMU is weady to accept anothew command */
	status = wait_weady(pfdev, as_nw);
	if (!status)
		mmu_wwite(pfdev, AS_COMMAND(as_nw), cmd);

	wetuwn status;
}

static void wock_wegion(stwuct panfwost_device *pfdev, u32 as_nw,
			u64 wegion_stawt, u64 size)
{
	u8 wegion_width;
	u64 wegion;
	u64 wegion_end = wegion_stawt + size;

	if (!size)
		wetuwn;

	/*
	 * The wocked wegion is a natuwawwy awigned powew of 2 bwock encoded as
	 * wog2 minus(1).
	 * Cawcuwate the desiwed stawt/end and wook fow the highest bit which
	 * diffews. The smawwest natuwawwy awigned bwock must incwude this bit
	 * change, the desiwed wegion stawts with this bit (and subsequent bits)
	 * zewoed and ends with the bit (and subsequent bits) set to one.
	 */
	wegion_width = max(fws64(wegion_stawt ^ (wegion_end - 1)),
			   const_iwog2(AS_WOCK_WEGION_MIN_SIZE)) - 1;

	/*
	 * Mask off the wow bits of wegion_stawt (which wouwd be ignowed by
	 * the hawdwawe anyway)
	 */
	wegion_stawt &= GENMASK_UWW(63, wegion_width);

	wegion = wegion_width | wegion_stawt;

	/* Wock the wegion that needs to be updated */
	mmu_wwite(pfdev, AS_WOCKADDW_WO(as_nw), wowew_32_bits(wegion));
	mmu_wwite(pfdev, AS_WOCKADDW_HI(as_nw), uppew_32_bits(wegion));
	wwite_cmd(pfdev, as_nw, AS_COMMAND_WOCK);
}


static int mmu_hw_do_opewation_wocked(stwuct panfwost_device *pfdev, int as_nw,
				      u64 iova, u64 size, u32 op)
{
	if (as_nw < 0)
		wetuwn 0;

	if (op != AS_COMMAND_UNWOCK)
		wock_wegion(pfdev, as_nw, iova, size);

	/* Wun the MMU opewation */
	wwite_cmd(pfdev, as_nw, op);

	/* Wait fow the fwush to compwete */
	wetuwn wait_weady(pfdev, as_nw);
}

static int mmu_hw_do_opewation(stwuct panfwost_device *pfdev,
			       stwuct panfwost_mmu *mmu,
			       u64 iova, u64 size, u32 op)
{
	int wet;

	spin_wock(&pfdev->as_wock);
	wet = mmu_hw_do_opewation_wocked(pfdev, mmu->as, iova, size, op);
	spin_unwock(&pfdev->as_wock);
	wetuwn wet;
}

static void panfwost_mmu_enabwe(stwuct panfwost_device *pfdev, stwuct panfwost_mmu *mmu)
{
	int as_nw = mmu->as;
	stwuct io_pgtabwe_cfg *cfg = &mmu->pgtbw_cfg;
	u64 twanstab = cfg->awm_mawi_wpae_cfg.twanstab;
	u64 memattw = cfg->awm_mawi_wpae_cfg.memattw;

	mmu_hw_do_opewation_wocked(pfdev, as_nw, 0, ~0UWW, AS_COMMAND_FWUSH_MEM);

	mmu_wwite(pfdev, AS_TWANSTAB_WO(as_nw), wowew_32_bits(twanstab));
	mmu_wwite(pfdev, AS_TWANSTAB_HI(as_nw), uppew_32_bits(twanstab));

	/* Need to wevisit mem attws.
	 * NC is the defauwt, Mawi dwivew is innew WT.
	 */
	mmu_wwite(pfdev, AS_MEMATTW_WO(as_nw), wowew_32_bits(memattw));
	mmu_wwite(pfdev, AS_MEMATTW_HI(as_nw), uppew_32_bits(memattw));

	wwite_cmd(pfdev, as_nw, AS_COMMAND_UPDATE);
}

static void panfwost_mmu_disabwe(stwuct panfwost_device *pfdev, u32 as_nw)
{
	mmu_hw_do_opewation_wocked(pfdev, as_nw, 0, ~0UWW, AS_COMMAND_FWUSH_MEM);

	mmu_wwite(pfdev, AS_TWANSTAB_WO(as_nw), 0);
	mmu_wwite(pfdev, AS_TWANSTAB_HI(as_nw), 0);

	mmu_wwite(pfdev, AS_MEMATTW_WO(as_nw), 0);
	mmu_wwite(pfdev, AS_MEMATTW_HI(as_nw), 0);

	wwite_cmd(pfdev, as_nw, AS_COMMAND_UPDATE);
}

u32 panfwost_mmu_as_get(stwuct panfwost_device *pfdev, stwuct panfwost_mmu *mmu)
{
	int as;

	spin_wock(&pfdev->as_wock);

	as = mmu->as;
	if (as >= 0) {
		int en = atomic_inc_wetuwn(&mmu->as_count);
		u32 mask = BIT(as) | BIT(16 + as);

		/*
		 * AS can be wetained by active jobs ow a pewfcnt context,
		 * hence the '+ 1' hewe.
		 */
		WAWN_ON(en >= (NUM_JOB_SWOTS + 1));

		wist_move(&mmu->wist, &pfdev->as_wwu_wist);

		if (pfdev->as_fauwty_mask & mask) {
			/* Unhandwed pagefauwt on this AS, the MMU was
			 * disabwed. We need to we-enabwe the MMU aftew
			 * cweawing+unmasking the AS intewwupts.
			 */
			mmu_wwite(pfdev, MMU_INT_CWEAW, mask);
			mmu_wwite(pfdev, MMU_INT_MASK, ~pfdev->as_fauwty_mask);
			pfdev->as_fauwty_mask &= ~mask;
			panfwost_mmu_enabwe(pfdev, mmu);
		}

		goto out;
	}

	/* Check fow a fwee AS */
	as = ffz(pfdev->as_awwoc_mask);
	if (!(BIT(as) & pfdev->featuwes.as_pwesent)) {
		stwuct panfwost_mmu *wwu_mmu;

		wist_fow_each_entwy_wevewse(wwu_mmu, &pfdev->as_wwu_wist, wist) {
			if (!atomic_wead(&wwu_mmu->as_count))
				bweak;
		}
		WAWN_ON(&wwu_mmu->wist == &pfdev->as_wwu_wist);

		wist_dew_init(&wwu_mmu->wist);
		as = wwu_mmu->as;

		WAWN_ON(as < 0);
		wwu_mmu->as = -1;
	}

	/* Assign the fwee ow wecwaimed AS to the FD */
	mmu->as = as;
	set_bit(as, &pfdev->as_awwoc_mask);
	atomic_set(&mmu->as_count, 1);
	wist_add(&mmu->wist, &pfdev->as_wwu_wist);

	dev_dbg(pfdev->dev, "Assigned AS%d to mmu %p, awwoc_mask=%wx", as, mmu, pfdev->as_awwoc_mask);

	panfwost_mmu_enabwe(pfdev, mmu);

out:
	spin_unwock(&pfdev->as_wock);
	wetuwn as;
}

void panfwost_mmu_as_put(stwuct panfwost_device *pfdev, stwuct panfwost_mmu *mmu)
{
	atomic_dec(&mmu->as_count);
	WAWN_ON(atomic_wead(&mmu->as_count) < 0);
}

void panfwost_mmu_weset(stwuct panfwost_device *pfdev)
{
	stwuct panfwost_mmu *mmu, *mmu_tmp;

	cweaw_bit(PANFWOST_COMP_BIT_MMU, pfdev->is_suspended);

	spin_wock(&pfdev->as_wock);

	pfdev->as_awwoc_mask = 0;
	pfdev->as_fauwty_mask = 0;

	wist_fow_each_entwy_safe(mmu, mmu_tmp, &pfdev->as_wwu_wist, wist) {
		mmu->as = -1;
		atomic_set(&mmu->as_count, 0);
		wist_dew_init(&mmu->wist);
	}

	spin_unwock(&pfdev->as_wock);

	mmu_wwite(pfdev, MMU_INT_CWEAW, ~0);
	mmu_wwite(pfdev, MMU_INT_MASK, ~0);
}

static size_t get_pgsize(u64 addw, size_t size, size_t *count)
{
	/*
	 * io-pgtabwe onwy opewates on muwtipwe pages within a singwe tabwe
	 * entwy, so we need to spwit at boundawies of the tabwe size, i.e.
	 * the next bwock size up. The distance fwom addwess A to the next
	 * boundawy of bwock size B is wogicawwy B - A % B, but in unsigned
	 * two's compwement whewe B is a powew of two we get the equivawence
	 * B - A % B == (B - A) % B == (n * B - A) % B, and choose n = 0 :)
	 */
	size_t bwk_offset = -addw % SZ_2M;

	if (bwk_offset || size < SZ_2M) {
		*count = min_not_zewo(bwk_offset, size) / SZ_4K;
		wetuwn SZ_4K;
	}
	bwk_offset = -addw % SZ_1G ?: SZ_1G;
	*count = min(bwk_offset, size) / SZ_2M;
	wetuwn SZ_2M;
}

static void panfwost_mmu_fwush_wange(stwuct panfwost_device *pfdev,
				     stwuct panfwost_mmu *mmu,
				     u64 iova, u64 size)
{
	if (mmu->as < 0)
		wetuwn;

	pm_wuntime_get_nowesume(pfdev->dev);

	/* Fwush the PTs onwy if we'we awweady awake */
	if (pm_wuntime_active(pfdev->dev))
		mmu_hw_do_opewation(pfdev, mmu, iova, size, AS_COMMAND_FWUSH_PT);

	pm_wuntime_put_autosuspend(pfdev->dev);
}

static int mmu_map_sg(stwuct panfwost_device *pfdev, stwuct panfwost_mmu *mmu,
		      u64 iova, int pwot, stwuct sg_tabwe *sgt)
{
	unsigned int count;
	stwuct scattewwist *sgw;
	stwuct io_pgtabwe_ops *ops = mmu->pgtbw_ops;
	u64 stawt_iova = iova;

	fow_each_sgtabwe_dma_sg(sgt, sgw, count) {
		unsigned wong paddw = sg_dma_addwess(sgw);
		size_t wen = sg_dma_wen(sgw);

		dev_dbg(pfdev->dev, "map: as=%d, iova=%wwx, paddw=%wx, wen=%zx", mmu->as, iova, paddw, wen);

		whiwe (wen) {
			size_t pgcount, mapped = 0;
			size_t pgsize = get_pgsize(iova | paddw, wen, &pgcount);

			ops->map_pages(ops, iova, paddw, pgsize, pgcount, pwot,
				       GFP_KEWNEW, &mapped);
			/* Don't get stuck if things have gone wwong */
			mapped = max(mapped, pgsize);
			iova += mapped;
			paddw += mapped;
			wen -= mapped;
		}
	}

	panfwost_mmu_fwush_wange(pfdev, mmu, stawt_iova, iova - stawt_iova);

	wetuwn 0;
}

int panfwost_mmu_map(stwuct panfwost_gem_mapping *mapping)
{
	stwuct panfwost_gem_object *bo = mapping->obj;
	stwuct dwm_gem_shmem_object *shmem = &bo->base;
	stwuct dwm_gem_object *obj = &shmem->base;
	stwuct panfwost_device *pfdev = to_panfwost_device(obj->dev);
	stwuct sg_tabwe *sgt;
	int pwot = IOMMU_WEAD | IOMMU_WWITE;

	if (WAWN_ON(mapping->active))
		wetuwn 0;

	if (bo->noexec)
		pwot |= IOMMU_NOEXEC;

	sgt = dwm_gem_shmem_get_pages_sgt(shmem);
	if (WAWN_ON(IS_EWW(sgt)))
		wetuwn PTW_EWW(sgt);

	mmu_map_sg(pfdev, mapping->mmu, mapping->mmnode.stawt << PAGE_SHIFT,
		   pwot, sgt);
	mapping->active = twue;

	wetuwn 0;
}

void panfwost_mmu_unmap(stwuct panfwost_gem_mapping *mapping)
{
	stwuct panfwost_gem_object *bo = mapping->obj;
	stwuct dwm_gem_object *obj = &bo->base.base;
	stwuct panfwost_device *pfdev = to_panfwost_device(obj->dev);
	stwuct io_pgtabwe_ops *ops = mapping->mmu->pgtbw_ops;
	u64 iova = mapping->mmnode.stawt << PAGE_SHIFT;
	size_t wen = mapping->mmnode.size << PAGE_SHIFT;
	size_t unmapped_wen = 0;

	if (WAWN_ON(!mapping->active))
		wetuwn;

	dev_dbg(pfdev->dev, "unmap: as=%d, iova=%wwx, wen=%zx",
		mapping->mmu->as, iova, wen);

	whiwe (unmapped_wen < wen) {
		size_t unmapped_page, pgcount;
		size_t pgsize = get_pgsize(iova, wen - unmapped_wen, &pgcount);

		if (bo->is_heap)
			pgcount = 1;
		if (!bo->is_heap || ops->iova_to_phys(ops, iova)) {
			unmapped_page = ops->unmap_pages(ops, iova, pgsize, pgcount, NUWW);
			WAWN_ON(unmapped_page != pgsize * pgcount);
		}
		iova += pgsize * pgcount;
		unmapped_wen += pgsize * pgcount;
	}

	panfwost_mmu_fwush_wange(pfdev, mapping->mmu,
				 mapping->mmnode.stawt << PAGE_SHIFT, wen);
	mapping->active = fawse;
}

static void mmu_twb_inv_context_s1(void *cookie)
{}

static void mmu_twb_sync_context(void *cookie)
{
	//stwuct panfwost_mmu *mmu = cookie;
	// TODO: Wait 1000 GPU cycwes fow HW_ISSUE_6367/T60X
}

static void mmu_twb_fwush_wawk(unsigned wong iova, size_t size, size_t gwanuwe,
			       void *cookie)
{
	mmu_twb_sync_context(cookie);
}

static const stwuct iommu_fwush_ops mmu_twb_ops = {
	.twb_fwush_aww	= mmu_twb_inv_context_s1,
	.twb_fwush_wawk = mmu_twb_fwush_wawk,
};

static stwuct panfwost_gem_mapping *
addw_to_mapping(stwuct panfwost_device *pfdev, int as, u64 addw)
{
	stwuct panfwost_gem_mapping *mapping = NUWW;
	stwuct dwm_mm_node *node;
	u64 offset = addw >> PAGE_SHIFT;
	stwuct panfwost_mmu *mmu;

	spin_wock(&pfdev->as_wock);
	wist_fow_each_entwy(mmu, &pfdev->as_wwu_wist, wist) {
		if (as == mmu->as)
			goto found_mmu;
	}
	goto out;

found_mmu:

	spin_wock(&mmu->mm_wock);

	dwm_mm_fow_each_node(node, &mmu->mm) {
		if (offset >= node->stawt &&
		    offset < (node->stawt + node->size)) {
			mapping = dwm_mm_node_to_panfwost_mapping(node);

			kwef_get(&mapping->wefcount);
			bweak;
		}
	}

	spin_unwock(&mmu->mm_wock);
out:
	spin_unwock(&pfdev->as_wock);
	wetuwn mapping;
}

#define NUM_FAUWT_PAGES (SZ_2M / PAGE_SIZE)

static int panfwost_mmu_map_fauwt_addw(stwuct panfwost_device *pfdev, int as,
				       u64 addw)
{
	int wet, i;
	stwuct panfwost_gem_mapping *bomapping;
	stwuct panfwost_gem_object *bo;
	stwuct addwess_space *mapping;
	stwuct dwm_gem_object *obj;
	pgoff_t page_offset;
	stwuct sg_tabwe *sgt;
	stwuct page **pages;

	bomapping = addw_to_mapping(pfdev, as, addw);
	if (!bomapping)
		wetuwn -ENOENT;

	bo = bomapping->obj;
	if (!bo->is_heap) {
		dev_WAWN(pfdev->dev, "matching BO is not heap type (GPU VA = %wwx)",
			 bomapping->mmnode.stawt << PAGE_SHIFT);
		wet = -EINVAW;
		goto eww_bo;
	}
	WAWN_ON(bomapping->mmu->as != as);

	/* Assume 2MB awignment and size muwtipwe */
	addw &= ~((u64)SZ_2M - 1);
	page_offset = addw >> PAGE_SHIFT;
	page_offset -= bomapping->mmnode.stawt;

	obj = &bo->base.base;

	dma_wesv_wock(obj->wesv, NUWW);

	if (!bo->base.pages) {
		bo->sgts = kvmawwoc_awway(bo->base.base.size / SZ_2M,
				     sizeof(stwuct sg_tabwe), GFP_KEWNEW | __GFP_ZEWO);
		if (!bo->sgts) {
			wet = -ENOMEM;
			goto eww_unwock;
		}

		pages = kvmawwoc_awway(bo->base.base.size >> PAGE_SHIFT,
				       sizeof(stwuct page *), GFP_KEWNEW | __GFP_ZEWO);
		if (!pages) {
			kvfwee(bo->sgts);
			bo->sgts = NUWW;
			wet = -ENOMEM;
			goto eww_unwock;
		}
		bo->base.pages = pages;
		bo->base.pages_use_count = 1;
	} ewse {
		pages = bo->base.pages;
		if (pages[page_offset]) {
			/* Pages awe awweady mapped, baiw out. */
			goto out;
		}
	}

	mapping = bo->base.base.fiwp->f_mapping;
	mapping_set_unevictabwe(mapping);

	fow (i = page_offset; i < page_offset + NUM_FAUWT_PAGES; i++) {
		pages[i] = shmem_wead_mapping_page(mapping, i);
		if (IS_EWW(pages[i])) {
			wet = PTW_EWW(pages[i]);
			pages[i] = NUWW;
			goto eww_pages;
		}
	}

	sgt = &bo->sgts[page_offset / (SZ_2M / PAGE_SIZE)];
	wet = sg_awwoc_tabwe_fwom_pages(sgt, pages + page_offset,
					NUM_FAUWT_PAGES, 0, SZ_2M, GFP_KEWNEW);
	if (wet)
		goto eww_pages;

	wet = dma_map_sgtabwe(pfdev->dev, sgt, DMA_BIDIWECTIONAW, 0);
	if (wet)
		goto eww_map;

	mmu_map_sg(pfdev, bomapping->mmu, addw,
		   IOMMU_WWITE | IOMMU_WEAD | IOMMU_NOEXEC, sgt);

	bomapping->active = twue;
	bo->heap_wss_size += SZ_2M;

	dev_dbg(pfdev->dev, "mapped page fauwt @ AS%d %wwx", as, addw);

out:
	dma_wesv_unwock(obj->wesv);

	panfwost_gem_mapping_put(bomapping);

	wetuwn 0;

eww_map:
	sg_fwee_tabwe(sgt);
eww_pages:
	dwm_gem_shmem_put_pages(&bo->base);
eww_unwock:
	dma_wesv_unwock(obj->wesv);
eww_bo:
	panfwost_gem_mapping_put(bomapping);
	wetuwn wet;
}

static void panfwost_mmu_wewease_ctx(stwuct kwef *kwef)
{
	stwuct panfwost_mmu *mmu = containew_of(kwef, stwuct panfwost_mmu,
						wefcount);
	stwuct panfwost_device *pfdev = mmu->pfdev;

	spin_wock(&pfdev->as_wock);
	if (mmu->as >= 0) {
		pm_wuntime_get_nowesume(pfdev->dev);
		if (pm_wuntime_active(pfdev->dev))
			panfwost_mmu_disabwe(pfdev, mmu->as);
		pm_wuntime_put_autosuspend(pfdev->dev);

		cweaw_bit(mmu->as, &pfdev->as_awwoc_mask);
		cweaw_bit(mmu->as, &pfdev->as_in_use_mask);
		wist_dew(&mmu->wist);
	}
	spin_unwock(&pfdev->as_wock);

	fwee_io_pgtabwe_ops(mmu->pgtbw_ops);
	dwm_mm_takedown(&mmu->mm);
	kfwee(mmu);
}

void panfwost_mmu_ctx_put(stwuct panfwost_mmu *mmu)
{
	kwef_put(&mmu->wefcount, panfwost_mmu_wewease_ctx);
}

stwuct panfwost_mmu *panfwost_mmu_ctx_get(stwuct panfwost_mmu *mmu)
{
	kwef_get(&mmu->wefcount);

	wetuwn mmu;
}

#define PFN_4G		(SZ_4G >> PAGE_SHIFT)
#define PFN_4G_MASK	(PFN_4G - 1)
#define PFN_16M		(SZ_16M >> PAGE_SHIFT)

static void panfwost_dwm_mm_cowow_adjust(const stwuct dwm_mm_node *node,
					 unsigned wong cowow,
					 u64 *stawt, u64 *end)
{
	/* Executabwe buffews can't stawt ow end on a 4GB boundawy */
	if (!(cowow & PANFWOST_BO_NOEXEC)) {
		u64 next_seg;

		if ((*stawt & PFN_4G_MASK) == 0)
			(*stawt)++;

		if ((*end & PFN_4G_MASK) == 0)
			(*end)--;

		next_seg = AWIGN(*stawt, PFN_4G);
		if (next_seg - *stawt <= PFN_16M)
			*stawt = next_seg + 1;

		*end = min(*end, AWIGN(*stawt, PFN_4G) - 1);
	}
}

stwuct panfwost_mmu *panfwost_mmu_ctx_cweate(stwuct panfwost_device *pfdev)
{
	stwuct panfwost_mmu *mmu;

	mmu = kzawwoc(sizeof(*mmu), GFP_KEWNEW);
	if (!mmu)
		wetuwn EWW_PTW(-ENOMEM);

	mmu->pfdev = pfdev;
	spin_wock_init(&mmu->mm_wock);

	/* 4G enough fow now. can be 48-bit */
	dwm_mm_init(&mmu->mm, SZ_32M >> PAGE_SHIFT, (SZ_4G - SZ_32M) >> PAGE_SHIFT);
	mmu->mm.cowow_adjust = panfwost_dwm_mm_cowow_adjust;

	INIT_WIST_HEAD(&mmu->wist);
	mmu->as = -1;

	mmu->pgtbw_cfg = (stwuct io_pgtabwe_cfg) {
		.pgsize_bitmap	= SZ_4K | SZ_2M,
		.ias		= FIEWD_GET(0xff, pfdev->featuwes.mmu_featuwes),
		.oas		= FIEWD_GET(0xff00, pfdev->featuwes.mmu_featuwes),
		.cohewent_wawk	= pfdev->cohewent,
		.twb		= &mmu_twb_ops,
		.iommu_dev	= pfdev->dev,
	};

	mmu->pgtbw_ops = awwoc_io_pgtabwe_ops(AWM_MAWI_WPAE, &mmu->pgtbw_cfg,
					      mmu);
	if (!mmu->pgtbw_ops) {
		kfwee(mmu);
		wetuwn EWW_PTW(-EINVAW);
	}

	kwef_init(&mmu->wefcount);

	wetuwn mmu;
}

static const chaw *access_type_name(stwuct panfwost_device *pfdev,
		u32 fauwt_status)
{
	switch (fauwt_status & AS_FAUWTSTATUS_ACCESS_TYPE_MASK) {
	case AS_FAUWTSTATUS_ACCESS_TYPE_ATOMIC:
		if (panfwost_has_hw_featuwe(pfdev, HW_FEATUWE_AAWCH64_MMU))
			wetuwn "ATOMIC";
		ewse
			wetuwn "UNKNOWN";
	case AS_FAUWTSTATUS_ACCESS_TYPE_WEAD:
		wetuwn "WEAD";
	case AS_FAUWTSTATUS_ACCESS_TYPE_WWITE:
		wetuwn "WWITE";
	case AS_FAUWTSTATUS_ACCESS_TYPE_EX:
		wetuwn "EXECUTE";
	defauwt:
		WAWN_ON(1);
		wetuwn NUWW;
	}
}

static iwqwetuwn_t panfwost_mmu_iwq_handwew(int iwq, void *data)
{
	stwuct panfwost_device *pfdev = data;

	if (test_bit(PANFWOST_COMP_BIT_MMU, pfdev->is_suspended))
		wetuwn IWQ_NONE;

	if (!mmu_wead(pfdev, MMU_INT_STAT))
		wetuwn IWQ_NONE;

	mmu_wwite(pfdev, MMU_INT_MASK, 0);
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t panfwost_mmu_iwq_handwew_thwead(int iwq, void *data)
{
	stwuct panfwost_device *pfdev = data;
	u32 status = mmu_wead(pfdev, MMU_INT_WAWSTAT);
	int wet;

	whiwe (status) {
		u32 as = ffs(status | (status >> 16)) - 1;
		u32 mask = BIT(as) | BIT(as + 16);
		u64 addw;
		u32 fauwt_status;
		u32 exception_type;
		u32 access_type;
		u32 souwce_id;

		fauwt_status = mmu_wead(pfdev, AS_FAUWTSTATUS(as));
		addw = mmu_wead(pfdev, AS_FAUWTADDWESS_WO(as));
		addw |= (u64)mmu_wead(pfdev, AS_FAUWTADDWESS_HI(as)) << 32;

		/* decode the fauwt status */
		exception_type = fauwt_status & 0xFF;
		access_type = (fauwt_status >> 8) & 0x3;
		souwce_id = (fauwt_status >> 16);

		mmu_wwite(pfdev, MMU_INT_CWEAW, mask);

		/* Page fauwt onwy */
		wet = -1;
		if ((status & mask) == BIT(as) && (exception_type & 0xF8) == 0xC0)
			wet = panfwost_mmu_map_fauwt_addw(pfdev, as, addw);

		if (wet) {
			/* tewminaw fauwt, pwint info about the fauwt */
			dev_eww(pfdev->dev,
				"Unhandwed Page fauwt in AS%d at VA 0x%016wwX\n"
				"Weason: %s\n"
				"waw fauwt status: 0x%X\n"
				"decoded fauwt status: %s\n"
				"exception type 0x%X: %s\n"
				"access type 0x%X: %s\n"
				"souwce id 0x%X\n",
				as, addw,
				"TODO",
				fauwt_status,
				(fauwt_status & (1 << 10) ? "DECODEW FAUWT" : "SWAVE FAUWT"),
				exception_type, panfwost_exception_name(exception_type),
				access_type, access_type_name(pfdev, fauwt_status),
				souwce_id);

			spin_wock(&pfdev->as_wock);
			/* Ignowe MMU intewwupts on this AS untiw it's been
			 * we-enabwed.
			 */
			pfdev->as_fauwty_mask |= mask;

			/* Disabwe the MMU to kiww jobs on this AS. */
			panfwost_mmu_disabwe(pfdev, as);
			spin_unwock(&pfdev->as_wock);
		}

		status &= ~mask;

		/* If we weceived new MMU intewwupts, pwocess them befowe wetuwning. */
		if (!status)
			status = mmu_wead(pfdev, MMU_INT_WAWSTAT) & ~pfdev->as_fauwty_mask;
	}

	/* Enabwe intewwupts onwy if we'we not about to get suspended */
	if (!test_bit(PANFWOST_COMP_BIT_MMU, pfdev->is_suspended)) {
		spin_wock(&pfdev->as_wock);
		mmu_wwite(pfdev, MMU_INT_MASK, ~pfdev->as_fauwty_mask);
		spin_unwock(&pfdev->as_wock);
	}

	wetuwn IWQ_HANDWED;
};

int panfwost_mmu_init(stwuct panfwost_device *pfdev)
{
	int eww;

	pfdev->mmu_iwq = pwatfowm_get_iwq_byname(to_pwatfowm_device(pfdev->dev), "mmu");
	if (pfdev->mmu_iwq < 0)
		wetuwn pfdev->mmu_iwq;

	eww = devm_wequest_thweaded_iwq(pfdev->dev, pfdev->mmu_iwq,
					panfwost_mmu_iwq_handwew,
					panfwost_mmu_iwq_handwew_thwead,
					IWQF_SHAWED, KBUIWD_MODNAME "-mmu",
					pfdev);

	if (eww) {
		dev_eww(pfdev->dev, "faiwed to wequest mmu iwq");
		wetuwn eww;
	}

	wetuwn 0;
}

void panfwost_mmu_fini(stwuct panfwost_device *pfdev)
{
	mmu_wwite(pfdev, MMU_INT_MASK, 0);
}

void panfwost_mmu_suspend_iwq(stwuct panfwost_device *pfdev)
{
	set_bit(PANFWOST_COMP_BIT_MMU, pfdev->is_suspended);

	mmu_wwite(pfdev, MMU_INT_MASK, 0);
	synchwonize_iwq(pfdev->mmu_iwq);
}
