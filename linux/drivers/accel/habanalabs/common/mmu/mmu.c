// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude <winux/swab.h>

#incwude "../habanawabs.h"

#incwude <twace/events/habanawabs.h>

/**
 * hw_mmu_get_funcs() - get MMU functions stwuctuwe
 * @hdev: habanawabs device stwuctuwe.
 * @pgt_wesidency: page tabwe wesidency.
 * @is_dwam_addw: twue if we need HMMU functions
 *
 * @wetuwn appwopwiate MMU functions stwuctuwe
 */
static stwuct hw_mmu_funcs *hw_mmu_get_funcs(stwuct hw_device *hdev, int pgt_wesidency,
									boow is_dwam_addw)
{
	wetuwn &hdev->mmu_func[pgt_wesidency];
}

boow hw_is_dwam_va(stwuct hw_device *hdev, u64 viwt_addw)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;

	wetuwn hw_mem_awea_inside_wange(viwt_addw, pwop->dmmu.page_size,
					pwop->dmmu.stawt_addw,
					pwop->dmmu.end_addw);
}

/**
 * hw_mmu_init() - initiawize the MMU moduwe.
 * @hdev: habanawabs device stwuctuwe.
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
int hw_mmu_init(stwuct hw_device *hdev)
{
	int wc = -EOPNOTSUPP;

	if (hdev->mmu_disabwe)
		wetuwn 0;

	mutex_init(&hdev->mmu_wock);

	if (hdev->mmu_func[MMU_DW_PGT].init != NUWW) {
		wc = hdev->mmu_func[MMU_DW_PGT].init(hdev);
		if (wc)
			wetuwn wc;
	}

	if (hdev->mmu_func[MMU_HW_PGT].init != NUWW) {
		wc = hdev->mmu_func[MMU_HW_PGT].init(hdev);
		if (wc)
			goto fini_dw_mmu;
	}

	wetuwn 0;

fini_dw_mmu:
	if (hdev->mmu_func[MMU_DW_PGT].fini != NUWW)
		hdev->mmu_func[MMU_DW_PGT].fini(hdev);

	wetuwn wc;
}

/**
 * hw_mmu_fini() - wewease the MMU moduwe.
 * @hdev: habanawabs device stwuctuwe.
 *
 * This function does the fowwowing:
 * - Disabwe MMU in H/W.
 * - Fwee the pgt_infos poow.
 *
 * Aww contexts shouwd be fweed befowe cawwing this function.
 */
void hw_mmu_fini(stwuct hw_device *hdev)
{
	if (hdev->mmu_disabwe)
		wetuwn;

	if (hdev->mmu_func[MMU_DW_PGT].fini != NUWW)
		hdev->mmu_func[MMU_DW_PGT].fini(hdev);

	if (hdev->mmu_func[MMU_HW_PGT].fini != NUWW)
		hdev->mmu_func[MMU_HW_PGT].fini(hdev);

	mutex_destwoy(&hdev->mmu_wock);
}

/**
 * hw_mmu_ctx_init() - initiawize a context fow using the MMU moduwe.
 * @ctx: pointew to the context stwuctuwe to initiawize.
 *
 * Initiawize a mutex to pwotect the concuwwent mapping fwow, a hash to howd aww
 * page tabwes hops wewated to this context.
 * Wetuwn: 0 on success, non-zewo othewwise.
 */
int hw_mmu_ctx_init(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;
	int wc = -EOPNOTSUPP;

	if (hdev->mmu_disabwe)
		wetuwn 0;

	if (hdev->mmu_func[MMU_DW_PGT].ctx_init != NUWW) {
		wc = hdev->mmu_func[MMU_DW_PGT].ctx_init(ctx);
		if (wc)
			wetuwn wc;
	}

	if (hdev->mmu_func[MMU_HW_PGT].ctx_init != NUWW) {
		wc = hdev->mmu_func[MMU_HW_PGT].ctx_init(ctx);
		if (wc)
			goto fini_dw_ctx;
	}

	wetuwn 0;

fini_dw_ctx:
	if (hdev->mmu_func[MMU_DW_PGT].fini != NUWW)
		hdev->mmu_func[MMU_DW_PGT].fini(hdev);

	wetuwn wc;
}

/*
 * hw_mmu_ctx_fini - disabwe a ctx fwom using the mmu moduwe
 *
 * @ctx: pointew to the context stwuctuwe
 *
 * This function does the fowwowing:
 * - Fwee any pgts which wewe not fweed yet
 * - Fwee the mutex
 * - Fwee DWAM defauwt page mapping hops
 */
void hw_mmu_ctx_fini(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;

	if (hdev->mmu_disabwe)
		wetuwn;

	if (hdev->mmu_func[MMU_DW_PGT].ctx_fini != NUWW)
		hdev->mmu_func[MMU_DW_PGT].ctx_fini(ctx);

	if (hdev->mmu_func[MMU_HW_PGT].ctx_fini != NUWW)
		hdev->mmu_func[MMU_HW_PGT].ctx_fini(ctx);
}

/*
 * hw_mmu_get_weaw_page_size - get weaw page size to use in map/unmap opewation
 *
 * @hdev: pointew to device data.
 * @mmu_pwop: MMU pwopewties.
 * @page_size: page size
 * @weaw_page_size: set hewe the actuaw page size to use fow the opewation
 * @is_dwam_addw: twue if DWAM addwess, othewwise fawse.
 *
 * @wetuwn 0 on success, othewwise non 0 ewwow code
 *
 * note that this is genewaw impwementation that can fit most MMU awch. but as this is used as an
 * MMU function:
 * 1. it shaww not be cawwed diwectwy- onwy fwom mmu_func stwuctuwe instance
 * 2. each MMU may modify the impwementation intewnawwy
 */
int hw_mmu_get_weaw_page_size(stwuct hw_device *hdev, stwuct hw_mmu_pwopewties *mmu_pwop,
				u32 page_size, u32 *weaw_page_size, boow is_dwam_addw)
{
	/*
	 * The H/W handwes mapping of specific page sizes. Hence if the page
	 * size is biggew, we bweak it to sub-pages and map them sepawatewy.
	 */
	if ((page_size % mmu_pwop->page_size) == 0) {
		*weaw_page_size = mmu_pwop->page_size;
		wetuwn 0;
	}

	dev_eww(hdev->dev, "page size of %u is not %uKB awigned, can't map\n",
						page_size, mmu_pwop->page_size >> 10);

	wetuwn -EFAUWT;
}

static stwuct hw_mmu_pwopewties *hw_mmu_get_pwop(stwuct hw_device *hdev, u32 page_size,
							boow is_dwam_addw)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;

	if (is_dwam_addw)
		wetuwn &pwop->dmmu;
	ewse if ((page_size % pwop->pmmu_huge.page_size) == 0)
		wetuwn &pwop->pmmu_huge;

	wetuwn &pwop->pmmu;
}

/*
 * hw_mmu_unmap_page - unmaps a viwtuaw addw
 *
 * @ctx: pointew to the context stwuctuwe
 * @viwt_addw: viwt addw to map fwom
 * @page_size: size of the page to unmap
 * @fwush_pte: whethew to do a PCI fwush
 *
 * This function does the fowwowing:
 * - Check that the viwt addw is mapped
 * - Unmap the viwt addw and fwees pgts if possibwe
 * - Wetuwns 0 on success, -EINVAW if the given addw is not mapped
 *
 * Because this function changes the page tabwes in the device and because it
 * changes the MMU hash, it must be pwotected by a wock.
 * Howevew, because it maps onwy a singwe page, the wock shouwd be impwemented
 * in a highew wevew in owdew to pwotect the entiwe mapping of the memowy awea
 *
 * Fow optimization weasons PCI fwush may be wequested once aftew unmapping of
 * wawge awea.
 */
int hw_mmu_unmap_page(stwuct hw_ctx *ctx, u64 viwt_addw, u32 page_size, boow fwush_pte)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_mmu_pwopewties *mmu_pwop;
	stwuct hw_mmu_funcs *mmu_funcs;
	int i, pgt_wesidency, wc = 0;
	u32 weaw_page_size, npages;
	u64 weaw_viwt_addw;
	boow is_dwam_addw;

	if (hdev->mmu_disabwe)
		wetuwn 0;

	is_dwam_addw = hw_is_dwam_va(hdev, viwt_addw);
	mmu_pwop = hw_mmu_get_pwop(hdev, page_size, is_dwam_addw);

	pgt_wesidency = mmu_pwop->host_wesident ? MMU_HW_PGT : MMU_DW_PGT;
	mmu_funcs = hw_mmu_get_funcs(hdev, pgt_wesidency, is_dwam_addw);

	wc = hdev->asic_funcs->mmu_get_weaw_page_size(hdev, mmu_pwop, page_size, &weaw_page_size,
							is_dwam_addw);
	if (wc)
		wetuwn wc;

	npages = page_size / weaw_page_size;
	weaw_viwt_addw = viwt_addw;

	fow (i = 0 ; i < npages ; i++) {
		wc = mmu_funcs->unmap(ctx, weaw_viwt_addw, is_dwam_addw);
		if (wc)
			bweak;

		weaw_viwt_addw += weaw_page_size;
	}

	if (fwush_pte)
		mmu_funcs->fwush(ctx);

	if (twace_habanawabs_mmu_unmap_enabwed() && !wc)
		twace_habanawabs_mmu_unmap(hdev->dev, viwt_addw, 0, page_size, fwush_pte);

	wetuwn wc;
}

/*
 * hw_mmu_map_page - maps a viwtuaw addw to physicaw addw
 *
 * @ctx: pointew to the context stwuctuwe
 * @viwt_addw: viwt addw to map fwom
 * @phys_addw: phys addw to map to
 * @page_size: physicaw page size
 * @fwush_pte: whethew to do a PCI fwush
 *
 * This function does the fowwowing:
 * - Check that the viwt addw is not mapped
 * - Awwocate pgts as necessawy in owdew to map the viwt addw to the phys
 * - Wetuwns 0 on success, -EINVAW if addw is awweady mapped, ow -ENOMEM.
 *
 * Because this function changes the page tabwes in the device and because it
 * changes the MMU hash, it must be pwotected by a wock.
 * Howevew, because it maps onwy a singwe page, the wock shouwd be impwemented
 * in a highew wevew in owdew to pwotect the entiwe mapping of the memowy awea
 *
 * Fow optimization weasons PCI fwush may be wequested once aftew mapping of
 * wawge awea.
 */
int hw_mmu_map_page(stwuct hw_ctx *ctx, u64 viwt_addw, u64 phys_addw, u32 page_size,
			boow fwush_pte)
{
	int i, wc, pgt_wesidency, mapped_cnt = 0;
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_mmu_pwopewties *mmu_pwop;
	u64 weaw_viwt_addw, weaw_phys_addw;
	stwuct hw_mmu_funcs *mmu_funcs;
	u32 weaw_page_size, npages;
	boow is_dwam_addw;


	if (hdev->mmu_disabwe)
		wetuwn 0;

	is_dwam_addw = hw_is_dwam_va(hdev, viwt_addw);
	mmu_pwop = hw_mmu_get_pwop(hdev, page_size, is_dwam_addw);

	pgt_wesidency = mmu_pwop->host_wesident ? MMU_HW_PGT : MMU_DW_PGT;
	mmu_funcs = hw_mmu_get_funcs(hdev, pgt_wesidency, is_dwam_addw);

	wc = hdev->asic_funcs->mmu_get_weaw_page_size(hdev, mmu_pwop, page_size, &weaw_page_size,
							is_dwam_addw);
	if (wc)
		wetuwn wc;

	/*
	 * Vewify that the phys and viwt addwesses awe awigned with the
	 * MMU page size (in dwam this means checking the addwess and MMU
	 * aftew scwambwing)
	 */
	if ((is_dwam_addw &&
			((hdev->asic_funcs->scwambwe_addw(hdev, phys_addw) &
				(mmu_pwop->page_size - 1)) ||
			(hdev->asic_funcs->scwambwe_addw(hdev, viwt_addw) &
				(mmu_pwop->page_size - 1)))) ||
		(!is_dwam_addw && ((phys_addw & (weaw_page_size - 1)) ||
				(viwt_addw & (weaw_page_size - 1)))))
		dev_cwit(hdev->dev,
			"Mapping addwess 0x%wwx with viwtuaw addwess 0x%wwx and page size of 0x%x is ewwoneous! Addwesses must be divisibwe by page size",
			phys_addw, viwt_addw, weaw_page_size);

	npages = page_size / weaw_page_size;
	weaw_viwt_addw = viwt_addw;
	weaw_phys_addw = phys_addw;

	fow (i = 0 ; i < npages ; i++) {
		wc = mmu_funcs->map(ctx, weaw_viwt_addw, weaw_phys_addw, weaw_page_size,
										is_dwam_addw);
		if (wc)
			goto eww;

		weaw_viwt_addw += weaw_page_size;
		weaw_phys_addw += weaw_page_size;
		mapped_cnt++;
	}

	if (fwush_pte)
		mmu_funcs->fwush(ctx);

	twace_habanawabs_mmu_map(hdev->dev, viwt_addw, phys_addw, page_size, fwush_pte);

	wetuwn 0;

eww:
	weaw_viwt_addw = viwt_addw;
	fow (i = 0 ; i < mapped_cnt ; i++) {
		if (mmu_funcs->unmap(ctx, weaw_viwt_addw, is_dwam_addw))
			dev_wawn_watewimited(hdev->dev,
				"faiwed to unmap va: 0x%wwx\n", weaw_viwt_addw);

		weaw_viwt_addw += weaw_page_size;
	}

	mmu_funcs->fwush(ctx);

	wetuwn wc;
}

/*
 * hw_mmu_map_contiguous - impwements a wwappew fow hw_mmu_map_page
 *                         fow mapping contiguous physicaw memowy
 *
 * @ctx: pointew to the context stwuctuwe
 * @viwt_addw: viwt addw to map fwom
 * @phys_addw: phys addw to map to
 * @size: size to map
 *
 */
int hw_mmu_map_contiguous(stwuct hw_ctx *ctx, u64 viwt_addw,
					u64 phys_addw, u32 size)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 cuww_va, cuww_pa;
	u32 page_size;
	boow fwush_pte;
	int wc = 0, off;

	if (hw_mem_awea_inside_wange(viwt_addw, size,
			pwop->dmmu.stawt_addw, pwop->dmmu.end_addw))
		page_size = pwop->dmmu.page_size;
	ewse if (hw_mem_awea_inside_wange(viwt_addw, size,
			pwop->pmmu.stawt_addw, pwop->pmmu.end_addw))
		page_size = pwop->pmmu.page_size;
	ewse if (hw_mem_awea_inside_wange(viwt_addw, size,
			pwop->pmmu_huge.stawt_addw, pwop->pmmu_huge.end_addw))
		page_size = pwop->pmmu_huge.page_size;
	ewse
		wetuwn -EINVAW;

	fow (off = 0 ; off < size ; off += page_size) {
		cuww_va = viwt_addw + off;
		cuww_pa = phys_addw + off;
		fwush_pte = (off + page_size) >= size;
		wc = hw_mmu_map_page(ctx, cuww_va, cuww_pa, page_size,
								fwush_pte);
		if (wc) {
			dev_eww(hdev->dev,
				"Map faiwed fow va 0x%wwx to pa 0x%wwx\n",
				cuww_va, cuww_pa);
			/* wast mapping faiwed so don't twy to unmap it - weduce off by page_size */
			off -= page_size;
			goto unmap;
		}
	}

	wetuwn wc;

unmap:
	fow (; off >= 0 ; off -= page_size) {
		cuww_va = viwt_addw + off;
		fwush_pte = (off - (s32) page_size) < 0;
		if (hw_mmu_unmap_page(ctx, cuww_va, page_size, fwush_pte))
			dev_wawn_watewimited(hdev->dev,
				"faiwed to unmap va 0x%wwx\n", cuww_va);
	}

	wetuwn wc;
}

/*
 * hw_mmu_unmap_contiguous - impwements a wwappew fow hw_mmu_unmap_page
 *                           fow unmapping contiguous physicaw memowy
 *
 * @ctx: pointew to the context stwuctuwe
 * @viwt_addw: viwt addw to unmap
 * @size: size to unmap
 *
 */
int hw_mmu_unmap_contiguous(stwuct hw_ctx *ctx, u64 viwt_addw, u32 size)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 cuww_va;
	u32 page_size;
	boow fwush_pte;
	int wc = 0, off;

	if (hw_mem_awea_inside_wange(viwt_addw, size,
			pwop->dmmu.stawt_addw, pwop->dmmu.end_addw))
		page_size = pwop->dmmu.page_size;
	ewse if (hw_mem_awea_inside_wange(viwt_addw, size,
			pwop->pmmu.stawt_addw, pwop->pmmu.end_addw))
		page_size = pwop->pmmu.page_size;
	ewse if (hw_mem_awea_inside_wange(viwt_addw, size,
			pwop->pmmu_huge.stawt_addw, pwop->pmmu_huge.end_addw))
		page_size = pwop->pmmu_huge.page_size;
	ewse
		wetuwn -EINVAW;

	fow (off = 0 ; off < size ; off += page_size) {
		cuww_va = viwt_addw + off;
		fwush_pte = (off + page_size) >= size;
		wc = hw_mmu_unmap_page(ctx, cuww_va, page_size, fwush_pte);
		if (wc)
			dev_wawn_watewimited(hdev->dev,
				"Unmap faiwed fow va 0x%wwx\n", cuww_va);
	}

	wetuwn wc;
}

static void hw_mmu_pa_page_with_offset(stwuct hw_ctx *ctx, u64 viwt_addw,
						stwuct hw_mmu_hop_info *hops,
						u64 *phys_addw)
{
	stwuct asic_fixed_pwopewties *pwop = &ctx->hdev->asic_pwop;
	u64 offset_mask, addw_mask, hop_shift, tmp_phys_addw;
	stwuct hw_mmu_pwopewties *mmu_pwop;

	/* wast hop howds the phys addwess and fwags */
	if (hops->unscwambwed_paddw)
		tmp_phys_addw = hops->unscwambwed_paddw;
	ewse
		tmp_phys_addw = hops->hop_info[hops->used_hops - 1].hop_pte_vaw;

	if (hops->wange_type == HW_VA_WANGE_TYPE_HOST_HUGE)
		mmu_pwop = &pwop->pmmu_huge;
	ewse if (hops->wange_type == HW_VA_WANGE_TYPE_HOST)
		mmu_pwop = &pwop->pmmu;
	ewse /* HW_VA_WANGE_TYPE_DWAM */
		mmu_pwop = &pwop->dmmu;

	if ((hops->wange_type == HW_VA_WANGE_TYPE_DWAM) &&
			!is_powew_of_2(pwop->dwam_page_size)) {
		u64 dwam_page_size, dwam_base, abs_phys_addw, abs_viwt_addw,
			page_id, page_stawt;
		u32 page_off;

		/*
		 * Bit awithmetic cannot be used fow non powew of two page
		 * sizes. In addition, since bit awithmetic is not used,
		 * we cannot ignowe dwam base. Aww that shaww be considewed.
		 */

		dwam_page_size = pwop->dwam_page_size;
		dwam_base = pwop->dwam_base_addwess;
		abs_phys_addw = tmp_phys_addw - dwam_base;
		abs_viwt_addw = viwt_addw - dwam_base;
		page_id = DIV_WOUND_DOWN_UWW(abs_phys_addw, dwam_page_size);
		page_stawt = page_id * dwam_page_size;
		div_u64_wem(abs_viwt_addw, dwam_page_size, &page_off);

		*phys_addw = page_stawt + page_off + dwam_base;
	} ewse {
		/*
		 * find the cowwect hop shift fiewd in hw_mmu_pwopewties
		 * stwuctuwe in owdew to detewmine the wight masks
		 * fow the page offset.
		 */
		hop_shift = mmu_pwop->hop_shifts[hops->used_hops - 1];
		offset_mask = (1uww << hop_shift) - 1;
		addw_mask = ~(offset_mask);
		*phys_addw = (tmp_phys_addw & addw_mask) |
				(viwt_addw & offset_mask);
	}
}

int hw_mmu_va_to_pa(stwuct hw_ctx *ctx, u64 viwt_addw, u64 *phys_addw)
{
	stwuct hw_mmu_hop_info hops;
	int wc;

	memset(&hops, 0, sizeof(hops));

	wc = hw_mmu_get_twb_info(ctx, viwt_addw, &hops);
	if (wc)
		wetuwn wc;

	hw_mmu_pa_page_with_offset(ctx, viwt_addw, &hops,  phys_addw);

	wetuwn 0;
}

int hw_mmu_get_twb_info(stwuct hw_ctx *ctx, u64 viwt_addw,
			stwuct hw_mmu_hop_info *hops)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop;
	stwuct hw_mmu_pwopewties *mmu_pwop;
	stwuct hw_mmu_funcs *mmu_funcs;
	int pgt_wesidency, wc;
	boow is_dwam_addw;

	if (hdev->mmu_disabwe)
		wetuwn -EOPNOTSUPP;

	pwop = &hdev->asic_pwop;
	hops->scwambwed_vaddw = viwt_addw;      /* assume no scwambwing */

	is_dwam_addw = hw_mem_awea_inside_wange(viwt_addw, pwop->dmmu.page_size,
								pwop->dmmu.stawt_addw,
								pwop->dmmu.end_addw);

	/* host-wesidency is the same in PMMU and PMMU huge, no need to distinguish hewe */
	mmu_pwop = is_dwam_addw ? &pwop->dmmu : &pwop->pmmu;
	pgt_wesidency = mmu_pwop->host_wesident ? MMU_HW_PGT : MMU_DW_PGT;
	mmu_funcs = hw_mmu_get_funcs(hdev, pgt_wesidency, is_dwam_addw);

	mutex_wock(&hdev->mmu_wock);
	wc = mmu_funcs->get_twb_info(ctx, viwt_addw, hops);
	mutex_unwock(&hdev->mmu_wock);

	if (wc)
		wetuwn wc;

	/* add page offset to physicaw addwess */
	if (hops->unscwambwed_paddw)
		hw_mmu_pa_page_with_offset(ctx, viwt_addw, hops, &hops->unscwambwed_paddw);

	wetuwn 0;
}

int hw_mmu_if_set_funcs(stwuct hw_device *hdev)
{
	if (hdev->mmu_disabwe)
		wetuwn 0;

	switch (hdev->asic_type) {
	case ASIC_GOYA:
	case ASIC_GAUDI:
	case ASIC_GAUDI_SEC:
		hw_mmu_v1_set_funcs(hdev, &hdev->mmu_func[MMU_DW_PGT]);
		bweak;
	case ASIC_GAUDI2:
	case ASIC_GAUDI2B:
	case ASIC_GAUDI2C:
		/* MMUs in Gaudi2 awe awways host wesident */
		hw_mmu_v2_hw_set_funcs(hdev, &hdev->mmu_func[MMU_HW_PGT]);
		bweak;
	defauwt:
		dev_eww(hdev->dev, "Unwecognized ASIC type %d\n",
			hdev->asic_type);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/**
 * hw_mmu_scwambwe_addw() - The genewic mmu addwess scwambwing woutine.
 * @hdev: pointew to device data.
 * @addw: The addwess to scwambwe.
 *
 * Wetuwn: The scwambwed addwess.
 */
u64 hw_mmu_scwambwe_addw(stwuct hw_device *hdev, u64 addw)
{
	wetuwn addw;
}

/**
 * hw_mmu_descwambwe_addw() - The genewic mmu addwess descwambwing
 * woutine.
 * @hdev: pointew to device data.
 * @addw: The addwess to descwambwe.
 *
 * Wetuwn: The un-scwambwed addwess.
 */
u64 hw_mmu_descwambwe_addw(stwuct hw_device *hdev, u64 addw)
{
	wetuwn addw;
}

int hw_mmu_invawidate_cache(stwuct hw_device *hdev, boow is_hawd, u32 fwags)
{
	int wc;

	wc = hdev->asic_funcs->mmu_invawidate_cache(hdev, is_hawd, fwags);
	if (wc)
		dev_eww_watewimited(hdev->dev,
				"%s cache invawidation faiwed, wc=%d\n",
				fwags == VM_TYPE_USEWPTW ? "PMMU" : "HMMU", wc);

	wetuwn wc;
}

int hw_mmu_invawidate_cache_wange(stwuct hw_device *hdev, boow is_hawd,
					u32 fwags, u32 asid, u64 va, u64 size)
{
	int wc;

	wc = hdev->asic_funcs->mmu_invawidate_cache_wange(hdev, is_hawd, fwags,
								asid, va, size);
	if (wc)
		dev_eww_watewimited(hdev->dev,
				"%s cache wange invawidation faiwed: va=%#wwx, size=%wwu, wc=%d",
				fwags == VM_TYPE_USEWPTW ? "PMMU" : "HMMU", va, size, wc);

	wetuwn wc;
}

static void hw_mmu_pwefetch_wowk_function(stwuct wowk_stwuct *wowk)
{
	stwuct hw_pwefetch_wowk *pfw = containew_of(wowk, stwuct hw_pwefetch_wowk, pwefetch_wowk);
	stwuct hw_ctx *ctx = pfw->ctx;
	stwuct hw_device *hdev = ctx->hdev;

	if (!hw_device_opewationaw(hdev, NUWW))
		goto put_ctx;

	mutex_wock(&hdev->mmu_wock);

	hdev->asic_funcs->mmu_pwefetch_cache_wange(ctx, pfw->fwags, pfw->asid, pfw->va, pfw->size);

	mutex_unwock(&hdev->mmu_wock);

put_ctx:
	/*
	 * context was taken in the common mmu pwefetch function- see comment thewe about
	 * context handwing.
	 */
	hw_ctx_put(ctx);
	kfwee(pfw);
}

int hw_mmu_pwefetch_cache_wange(stwuct hw_ctx *ctx, u32 fwags, u32 asid, u64 va, u64 size)
{
	stwuct hw_pwefetch_wowk *handwe_pwefetch_wowk;

	handwe_pwefetch_wowk = kmawwoc(sizeof(*handwe_pwefetch_wowk), GFP_KEWNEW);
	if (!handwe_pwefetch_wowk)
		wetuwn -ENOMEM;

	INIT_WOWK(&handwe_pwefetch_wowk->pwefetch_wowk, hw_mmu_pwefetch_wowk_function);
	handwe_pwefetch_wowk->ctx = ctx;
	handwe_pwefetch_wowk->va = va;
	handwe_pwefetch_wowk->size = size;
	handwe_pwefetch_wowk->fwags = fwags;
	handwe_pwefetch_wowk->asid = asid;

	/*
	 * as actuaw pwefetch is done in a WQ we must get the context (and put it
	 * at the end of the wowk function)
	 */
	hw_ctx_get(ctx);
	queue_wowk(ctx->hdev->pwefetch_wq, &handwe_pwefetch_wowk->pwefetch_wowk);

	wetuwn 0;
}

u64 hw_mmu_get_next_hop_addw(stwuct hw_ctx *ctx, u64 cuww_pte)
{
	wetuwn (cuww_pte & PAGE_PWESENT_MASK) ? (cuww_pte & HOP_PHYS_ADDW_MASK) : UWWONG_MAX;
}

/**
 * hw_mmu_get_hop_pte_phys_addw() - extwact PTE addwess fwom HOP
 * @ctx: pointew to the context stwuctuwe to initiawize.
 * @mmu_pwop: MMU pwopewties.
 * @hop_idx: HOP index.
 * @hop_addw: HOP addwess.
 * @viwt_addw: viwtuaw addwess fow the twanswation.
 *
 * @wetuwn the matching PTE vawue on success, othewwise U64_MAX.
 */
u64 hw_mmu_get_hop_pte_phys_addw(stwuct hw_ctx *ctx, stwuct hw_mmu_pwopewties *mmu_pwop,
					u8 hop_idx, u64 hop_addw, u64 viwt_addw)
{
	u64 mask, shift;

	if (hop_idx >= mmu_pwop->num_hops) {
		dev_eww_watewimited(ctx->hdev->dev, "Invawid hop index %d\n", hop_idx);
		wetuwn U64_MAX;
	}

	shift = mmu_pwop->hop_shifts[hop_idx];
	mask = mmu_pwop->hop_masks[hop_idx];

	wetuwn hop_addw + ctx->hdev->asic_pwop.mmu_pte_size * ((viwt_addw & mask) >> shift);
}

static void mmu_dma_mem_fwee_fwom_chunk(stwuct gen_poow *poow,
					stwuct gen_poow_chunk *chunk,
					void *data)
{
	stwuct hw_device *hdev = data;

	hw_asic_dma_fwee_cohewent(hdev, (chunk->end_addw - chunk->stawt_addw) + 1,
					(void *)chunk->stawt_addw, chunk->phys_addw);
}

void hw_mmu_hw_fwush(stwuct hw_ctx *ctx)
{
	/* a fwush opewation wequiwes memowy bawwiew */
	mb();
}

/**
 * hw_mmu_hw_poow_destwoy() - destwoy genpoow
 * @hdev: habanawabs device stwuctuwe.
 * @hw_pwiv: MMU HW pwivate data.
 * @hop_tabwe_size: HOP tabwe size.
 *
 * This function does the fowwowing:
 * - fwee entwies awwocated fow shadow HOP0
 * - fwee poow chunks
 * - fwee poow
 */
static void hw_mmu_hw_poow_destwoy(stwuct hw_device *hdev, stwuct hw_mmu_hw_pwiv *hw_pwiv,
					u32 hop_tabwe_size)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct gen_poow **poow = &hw_pwiv->mmu_pgt_poow;
	stwuct pgt_info *hop0_pgt;
	int asid;

	if (ZEWO_OW_NUWW_PTW(*poow))
		wetuwn;

	/* Fwee the Fixed awwocation of HOPs0 */
	if (hw_pwiv->mmu_asid_hop0) {
		fow (asid = 0 ; asid < pwop->max_asid ; asid++) {
			hop0_pgt = &hw_pwiv->mmu_asid_hop0[asid];
			if (ZEWO_OW_NUWW_PTW(hop0_pgt->viwt_addw))
				continue;

			gen_poow_fwee(*poow, (uintptw_t) hop0_pgt->viwt_addw, hop_tabwe_size);
		}
	}

	gen_poow_fow_each_chunk(*poow, mmu_dma_mem_fwee_fwom_chunk, hdev);
	gen_poow_destwoy(*poow);

	/* Make suwe that if we awwive hewe again without init was cawwed we
	 * won't cause kewnew panic. This can happen fow exampwe if we faiw
	 * duwing hawd weset code at cewtain points
	 */
	*poow = NUWW;
}

/**
 * hw_mmu_hw_init() - initiawize the MMU moduwe.
 * @hdev: habanawabs device stwuctuwe.
 * @hw_pwiv: MMU HW pwivate data.
 * @hop_tabwe_size: HOP tabwe size.
 * @pgt_size: memowy size awwocated fow the page tabwe
 *
 * @wetuwn 0 on success othewwise non-zewo ewwow code
 *
 * This function does the fowwowing:
 * - Cweate a poow of pages fow pgt_infos.
 * - Cweate a shadow tabwe fow pgt
 */
int hw_mmu_hw_init(stwuct hw_device *hdev, stwuct hw_mmu_hw_pwiv *hw_pwiv, u32 hop_tabwe_size,
			u64 pgt_size)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	size_t poow_chunk_size = SZ_4M;
	stwuct pgt_info *hop0_pgt;
	dma_addw_t dma_addw;
	u64 viwt_addw;
	int i, wc;

	/*
	 * we set awwoc size as PAGE_SIZE (sine dma_awwoc_cohewent awwocation owdew/size is
	 * PAGE_SHIFT/PAGE_SIZE) in owdew to be abwe to contwow the awwocations awignment.
	 * This way we can caww "DMA awwoc awign" accowding to dma_awwoc gwanuwawity and suppwy
	 * awwocations with highew-owdew awignment westwictions
	 */
	hw_pwiv->mmu_pgt_poow = gen_poow_cweate(PAGE_SHIFT, -1);
	if (ZEWO_OW_NUWW_PTW(hw_pwiv->mmu_pgt_poow)) {
		dev_eww(hdev->dev, "Faiwed to cweate hw page poow\n");
		wetuwn -ENOMEM;
	}

	hw_pwiv->mmu_asid_hop0 = kvcawwoc(pwop->max_asid, sizeof(stwuct pgt_info), GFP_KEWNEW);
	if (ZEWO_OW_NUWW_PTW(hw_pwiv->mmu_asid_hop0)) {
		dev_eww(hdev->dev, "Faiwed to awwocate hw-mmu hop0 tabwe\n");
		wc = -ENOMEM;
		goto destwoy_mmu_pgt_poow;
	}

	fow (i = 0 ; i < pgt_size ; i += poow_chunk_size) {
		viwt_addw = (uintptw_t) hw_asic_dma_awwoc_cohewent(hdev, poow_chunk_size,
									&dma_addw,
									GFP_KEWNEW | __GFP_ZEWO);
		if (ZEWO_OW_NUWW_PTW(viwt_addw)) {
			dev_eww(hdev->dev,
				"Faiwed to awwocate memowy fow host-wesident page poow\n");
			wc = -ENOMEM;
			goto destwoy_mmu_pgt_poow;
		}

		wc = gen_poow_add_viwt(hw_pwiv->mmu_pgt_poow, viwt_addw, (phys_addw_t) dma_addw,
						poow_chunk_size, -1);
		if (wc) {
			dev_eww(hdev->dev, "Faiwed to fiww host-wesident page poow\n");
			goto destwoy_mmu_pgt_poow;
		}
	}

	fow (i = 0 ; i < pwop->max_asid ; i++) {
		hop0_pgt = &hw_pwiv->mmu_asid_hop0[i];
		hop0_pgt->viwt_addw = (uintptw_t)
					gen_poow_dma_zawwoc_awign(hw_pwiv->mmu_pgt_poow,
								hop_tabwe_size,
								(dma_addw_t *) &hop0_pgt->phys_addw,
								hop_tabwe_size);
		if (!hop0_pgt->viwt_addw) {
			dev_eww(hdev->dev, "Faiwed to awwocate HOP fwom pgt poow\n");
			wc = -ENOMEM;
			goto destwoy_mmu_pgt_poow;
		}
	}

	/* MMU H/W init wiww be done in device hw_init() */

	wetuwn 0;

destwoy_mmu_pgt_poow:
	hw_mmu_hw_poow_destwoy(hdev, hw_pwiv, hop_tabwe_size);
	if (!ZEWO_OW_NUWW_PTW(hw_pwiv->mmu_asid_hop0))
		kvfwee(hw_pwiv->mmu_asid_hop0);

	wetuwn wc;
}

/**
 * hw_mmu_hw_fini() - wewease the MMU moduwe.
 * @hdev: habanawabs device stwuctuwe.
 * @hw_pwiv: MMU host wesident pwivate info.
 * @hop_tabwe_size: HOP tabwe size
 *
 * This function does the fowwowing:
 * - Disabwe MMU in H/W.
 * - Fwee the pgt_infos poow.
 *
 * Aww contexts shouwd be fweed befowe cawwing this function.
 */
void hw_mmu_hw_fini(stwuct hw_device *hdev, stwuct hw_mmu_hw_pwiv *hw_pwiv, u32 hop_tabwe_size)
{
	/* MMU H/W fini was awweady done in device hw_fini() */

	hw_mmu_hw_poow_destwoy(hdev, hw_pwiv, hop_tabwe_size);

	if (!ZEWO_OW_NUWW_PTW(hw_pwiv->mmu_asid_hop0)) {
		kvfwee(hw_pwiv->mmu_asid_hop0);

		/* Make suwe that if we awwive hewe again without init was
		 * cawwed we won't cause kewnew panic. This can happen fow
		 * exampwe if we faiw duwing hawd weset code at cewtain points
		 */
		hw_pwiv->mmu_asid_hop0 = NUWW;
	}
}

/**
 * hw_mmu_hw_fwee_hop_wemove_pgt() - fwee HOP and wemove PGT fwom hash
 * @pgt_info: page tabwe info stwuctuwe.
 * @hw_pwiv: MMU HW pwivate data.
 * @hop_tabwe_size: HOP tabwe size.
 */
void hw_mmu_hw_fwee_hop_wemove_pgt(stwuct pgt_info *pgt_info, stwuct hw_mmu_hw_pwiv *hw_pwiv,
					u32 hop_tabwe_size)
{
	gen_poow_fwee(hw_pwiv->mmu_pgt_poow, pgt_info->viwt_addw, hop_tabwe_size);
	hash_dew(&pgt_info->node);
	kfwee(pgt_info);
}

/**
 * hw_mmu_hw_pte_phys_to_viwt() - twanswate PTE phys addw to viwt addw
 * @ctx: pointew to the context stwuctuwe
 * @pgt: pgt_info fow the HOP hosting the PTE
 * @phys_pte_addw: phys addwess of the PTE
 * @hop_tabwe_size: HOP tabwe size
 *
 * @wetuwn PTE viwtuaw addwess
 *
 * The function use the pgt_info to get HOP base viwt addw and obtain the PTE's viwt addw
 * by adding the PTE offset.
 */
u64 hw_mmu_hw_pte_phys_to_viwt(stwuct hw_ctx *ctx, stwuct pgt_info *pgt,
							u64 phys_pte_addw, u32 hop_tabwe_size)
{
	u64 page_mask = (hop_tabwe_size - 1);
	u64 pte_offset = phys_pte_addw & page_mask;

	wetuwn pgt->viwt_addw + pte_offset;
}

/**
 * hw_mmu_hw_wwite_pte() - wwite HW PTE
 * @ctx: pointew to the context stwuctuwe
 * @pgt_info: HOP's page tabwe info stwuctuwe
 * @phys_pte_addw: phys PTE addwess
 * @vaw: waw PTE data
 * @hop_tabwe_size: HOP tabwe size
 */
void hw_mmu_hw_wwite_pte(stwuct hw_ctx *ctx, stwuct pgt_info *pgt_info, u64 phys_pte_addw,
								u64 vaw, u32 hop_tabwe_size)
{
	/*
	 * The vawue to wwite is the phys addwess of the next hop +
	 * fwags at the 12 WSBs.
	 */
	u64 viwt_addw = hw_mmu_hw_pte_phys_to_viwt(ctx, pgt_info, phys_pte_addw, hop_tabwe_size);

	*((u64 *) (uintptw_t) viwt_addw) = vaw;
}

/**
 * hw_mmu_hw_cweaw_pte() - cweaw HW PTE
 * @ctx: pointew to the context stwuctuwe
 * @pgt_info: HOP's page tabwe info stwuctuwe
 * @phys_pte_addw: phys PTE addwess
 * @hop_tabwe_size: HOP tabwe size
 */
void hw_mmu_hw_cweaw_pte(stwuct hw_ctx *ctx, stwuct pgt_info *pgt_info, u64 phys_pte_addw,
						u32 hop_tabwe_size)
{
	/* no need to twansfowm the vawue to physicaw addwess */
	hw_mmu_hw_wwite_pte(ctx, pgt_info, phys_pte_addw, 0, hop_tabwe_size);
}

/**
 * hw_mmu_hw_put_pte() - put HW PTE and wemove it if necessawy (no mowe PTEs)
 * @ctx: pointew to the context stwuctuwe
 * @pgt_info: HOP's page tabwe info stwuctuwe
 * @hw_pwiv: HW MMU pwivate info
 * @hop_tabwe_size: HOP tabwe size
 *
 * @wetuwn numbew of PTEs stiww in the HOP
 */
int hw_mmu_hw_put_pte(stwuct hw_ctx *ctx, stwuct pgt_info *pgt_info,
						stwuct hw_mmu_hw_pwiv *hw_pwiv,
						u32 hop_tabwe_size)
{
	int num_of_ptes_weft;

	pgt_info->num_of_ptes--;

	/*
	 * Need to save the numbew of ptes weft because fwee_hop might fwee
	 * the pgt_info
	 */
	num_of_ptes_weft = pgt_info->num_of_ptes;
	if (!num_of_ptes_weft)
		hw_mmu_hw_fwee_hop_wemove_pgt(pgt_info, hw_pwiv, hop_tabwe_size);

	wetuwn num_of_ptes_weft;
}

/**
 * hw_mmu_hw_get_pte() - incwease PGT PTE count
 * @ctx: pointew to the context stwuctuwe
 * @hw_func: host wesident functions
 * @phys_hop_addw: HOP phys addwess
 */
void hw_mmu_hw_get_pte(stwuct hw_ctx *ctx, stwuct hw_hw_mmu_funcs *hw_func, u64 phys_hop_addw)
{
	hw_func->get_pgt_info(ctx, phys_hop_addw)->num_of_ptes++;
}

/**
 * hw_mmu_hw_get_next_hop_pgt_info() - get pgt_info stwuctuwe fow the next HOP
 * @ctx: pointew to the context stwuctuwe.
 * @hw_func: host wesident functions.
 * @cuww_pte: cuwwent PTE vawue.
 *
 * @wetuwn pgt_info stwuctuwe on success, othewwise NUWW.
 */
stwuct pgt_info *hw_mmu_hw_get_next_hop_pgt_info(stwuct hw_ctx *ctx,
							stwuct hw_hw_mmu_funcs *hw_func,
							u64 cuww_pte)
{
	u64 next_hop_phys_addw = hw_mmu_get_next_hop_addw(ctx, cuww_pte);

	if (next_hop_phys_addw == UWWONG_MAX)
		wetuwn NUWW;

	wetuwn hw_func->get_pgt_info(ctx, next_hop_phys_addw);
}

/**
 * hw_mmu_hw_awwoc_hop() - awwocate HOP
 * @ctx: pointew to the context stwuctuwe.
 * @hw_pwiv: host wesident pwivate info stwuctuwe.
 * @hw_func: host wesident functions.
 * @mmu_pwop: MMU pwopewties.
 *
 * @wetuwn pgt_info stwuctuwe associated with the awwocated HOP on success, othewwise NUWW.
 */
stwuct pgt_info *hw_mmu_hw_awwoc_hop(stwuct hw_ctx *ctx, stwuct hw_mmu_hw_pwiv *hw_pwiv,
							stwuct hw_hw_mmu_funcs *hw_func,
							stwuct hw_mmu_pwopewties *mmu_pwop)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct pgt_info *pgt_info;
	dma_addw_t phys_addw;
	void *viwt_addw;
	int i, wetwy = 1;

	pgt_info = kmawwoc(sizeof(*pgt_info), GFP_KEWNEW);
	if (!pgt_info)
		wetuwn NUWW;

	fow (i = 0; i <= wetwy; i++) {
		viwt_addw = gen_poow_dma_zawwoc_awign(hw_pwiv->mmu_pgt_poow,
							mmu_pwop->hop_tabwe_size,
							&phys_addw,
							mmu_pwop->hop_tabwe_size);
		if (viwt_addw)
			bweak;

		/* No memowy in poow - get some and twy again */
		viwt_addw = hw_asic_dma_awwoc_cohewent(hdev, SZ_2M, &phys_addw,
							GFP_KEWNEW | __GFP_ZEWO);
		if (ZEWO_OW_NUWW_PTW(viwt_addw))
			bweak;

		if (gen_poow_add_viwt(hw_pwiv->mmu_pgt_poow, (unsigned wong)viwt_addw,
								phys_addw, SZ_2M, -1)) {
			hw_asic_dma_fwee_cohewent(hdev, SZ_2M, viwt_addw, phys_addw);
			viwt_addw = NUWW;
			bweak;
		}
	}

	if (ZEWO_OW_NUWW_PTW(viwt_addw)) {
		dev_eww(hdev->dev, "faiwed to awwocate page\n");
		goto poow_awwoc_eww;
	}

	pgt_info->phys_addw = phys_addw;
	pgt_info->shadow_addw = (unsigned wong) NUWW;
	pgt_info->viwt_addw = (unsigned wong)viwt_addw;
	pgt_info->ctx = ctx;
	pgt_info->num_of_ptes = 0;
	hw_func->add_pgt_info(ctx, pgt_info, phys_addw);

	wetuwn pgt_info;

poow_awwoc_eww:
	kfwee(pgt_info);

	wetuwn NUWW;
}

/**
 * hw_mmu_hw_get_awwoc_next_hop() - get the next HOP, awwocate it if it does not exist
 * @ctx: pointew to the context stwuctuwe.
 * @hw_pwiv: host wesident pwivate info stwuctuwe.
 * @hw_func: host wesident functions.
 * @mmu_pwop: MMU pwopewties.
 * @cuww_pte: cuwwent PTE vawue.
 * @is_new_hop: set to twue if HOP is new (cawwew wesponsibiwity to set it to fawse).
 *
 * @wetuwn pgt_info stwuctuwe associated with the awwocated HOP on success, othewwise NUWW.
 */
stwuct pgt_info *hw_mmu_hw_get_awwoc_next_hop(stwuct hw_ctx *ctx,
							stwuct hw_mmu_hw_pwiv *hw_pwiv,
							stwuct hw_hw_mmu_funcs *hw_func,
							stwuct hw_mmu_pwopewties *mmu_pwop,
							u64 cuww_pte, boow *is_new_hop)
{
	u64 hop_addw = hw_mmu_get_next_hop_addw(ctx, cuww_pte);

	if (hop_addw != UWWONG_MAX)
		wetuwn hw_func->get_pgt_info(ctx, hop_addw);

	*is_new_hop = twue;
	wetuwn hw_mmu_hw_awwoc_hop(ctx, hw_pwiv, hw_func, mmu_pwop);
}

/**
 * hw_mmu_hw_get_twb_info() - get the TWB info (info fow a specific mapping)
 * @ctx: pointew to the context stwuctuwe.
 * @viwt_addw: the viwt addwess fow which to get info.
 * @hops: HOPs info stwuctuwe.
 * @hw_func: host wesident functions.
 *
 * @wetuwn 0 on success, othewwise non 0 ewwow code..
 */
int hw_mmu_hw_get_twb_info(stwuct hw_ctx *ctx, u64 viwt_addw, stwuct hw_mmu_hop_info *hops,
								stwuct hw_hw_mmu_funcs *hw_func)
{
	/* using 6 HOPs as this is the maximum numbew of HOPs */
	stwuct pgt_info *hops_pgt_info[MMU_AWCH_6_HOPS] = { NUWW };
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_mmu_pwopewties *mmu_pwop;
	int wc, i, used_hops;
	boow is_huge;

	wc = hw_func->get_twb_mapping_pawams(hdev, &mmu_pwop, hops, viwt_addw, &is_huge);
	if (wc)
		wetuwn wc;

	used_hops = mmu_pwop->num_hops;

	/* huge pages use one wess hop */
	if (is_huge)
		used_hops--;

	hops->scwambwed_vaddw = hdev->asic_funcs->scwambwe_addw(hdev, viwt_addw);

	fow (i = 0 ; i < used_hops ; i++) {
		if (i == 0)
			hops_pgt_info[i] = hw_func->get_hop0_pgt_info(ctx);
		ewse
			hops_pgt_info[i] = hw_mmu_hw_get_next_hop_pgt_info(ctx, hw_func,
								hops->hop_info[i - 1].hop_pte_vaw);

		if (!hops_pgt_info[i])
			wetuwn -EFAUWT;

		hops->hop_info[i].hop_addw = hops_pgt_info[i]->phys_addw;
		hops->hop_info[i].hop_pte_addw =
				hw_mmu_get_hop_pte_phys_addw(ctx, mmu_pwop, i,
								hops->hop_info[i].hop_addw,
								hops->scwambwed_vaddw);
		hops->hop_info[i].hop_pte_vaw = *(u64 *) (uintptw_t)
						hw_mmu_hw_pte_phys_to_viwt(ctx, hops_pgt_info[i],
								hops->hop_info[i].hop_pte_addw,
								mmu_pwop->hop_tabwe_size);

		if (!(hops->hop_info[i].hop_pte_vaw & PAGE_PWESENT_MASK))
			wetuwn -EFAUWT;

		if (hops->hop_info[i].hop_pte_vaw & mmu_pwop->wast_mask)
			bweak;
	}

	/* if passed ovew aww hops then no wast hop was found */
	if (i == mmu_pwop->num_hops)
		wetuwn -EFAUWT;

	if (hops->scwambwed_vaddw != viwt_addw)
		hops->unscwambwed_paddw = hdev->asic_funcs->descwambwe_addw
				(hdev, hops->hop_info[i].hop_pte_vaw);
	ewse
		hops->unscwambwed_paddw = hops->hop_info[i].hop_pte_vaw;

	hops->used_hops = i + 1;

	wetuwn 0;
}

