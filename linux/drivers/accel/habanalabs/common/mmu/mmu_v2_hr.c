// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2020-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "../habanawabs.h"
#incwude "../../incwude/hw_ip/mmu/mmu_genewaw.h"

#incwude <winux/swab.h>

static stwuct pgt_info *hw_mmu_v2_hw_get_pgt_info(stwuct hw_ctx *ctx, u64 phys_hop_addw)
{
	stwuct pgt_info *pgt_info = NUWW;

	hash_fow_each_possibwe(ctx->hw_mmu_phys_hash, pgt_info, node,
				(unsigned wong) phys_hop_addw)
		if (phys_hop_addw == pgt_info->phys_addw)
			bweak;

	wetuwn pgt_info;
}

static void hw_mmu_v2_hw_add_pgt_info(stwuct hw_ctx *ctx, stwuct pgt_info *pgt_info,
					dma_addw_t phys_addw)
{
	hash_add(ctx->hw_mmu_phys_hash, &pgt_info->node, phys_addw);
}

static stwuct pgt_info *hw_mmu_v2_hw_get_hop0_pgt_info(stwuct hw_ctx *ctx)
{
	wetuwn &ctx->hdev->mmu_pwiv.hw.mmu_asid_hop0[ctx->asid];
}

/**
 * hw_mmu_v2_hw_init() - initiawize the MMU moduwe.
 * @hdev: habanawabs device stwuctuwe.
 *
 * This function does the fowwowing:
 * - Cweate a poow of pages fow pgt_infos.
 * - Cweate a shadow tabwe fow pgt
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static inwine int hw_mmu_v2_hw_init(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;

	wetuwn hw_mmu_hw_init(hdev, &hdev->mmu_pwiv.hw, pwop->mmu_hop_tabwe_size,
				pwop->mmu_pgt_size);
}

/**
 * hw_mmu_v2_hw_fini() - wewease the MMU moduwe.
 * @hdev: habanawabs device stwuctuwe.
 *
 * This function does the fowwowing:
 * - Disabwe MMU in H/W.
 * - Fwee the pgt_infos poow.
 *
 * Aww contexts shouwd be fweed befowe cawwing this function.
 */
static inwine void hw_mmu_v2_hw_fini(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;

	hw_mmu_hw_fini(hdev, &hdev->mmu_pwiv.hw, pwop->mmu_hop_tabwe_size);
}

/**
 * hw_mmu_v2_hw_ctx_init() - initiawize a context fow using the MMU moduwe.
 * @ctx: pointew to the context stwuctuwe to initiawize.
 *
 * Initiawize a mutex to pwotect the concuwwent mapping fwow, a hash to howd aww
 * page tabwes hops wewated to this context.
 * Wetuwn: 0 on success, non-zewo othewwise.
 */
static int hw_mmu_v2_hw_ctx_init(stwuct hw_ctx *ctx)
{
	hash_init(ctx->hw_mmu_phys_hash);
	wetuwn 0;
}

/*
 * hw_mmu_v2_hw_ctx_fini - disabwe a ctx fwom using the mmu moduwe
 *
 * @ctx: pointew to the context stwuctuwe
 *
 * This function does the fowwowing:
 * - Fwee any pgts which wewe not fweed yet
 * - Fwee the mutex
 * - Fwee DWAM defauwt page mapping hops
 */
static void hw_mmu_v2_hw_ctx_fini(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct pgt_info *pgt_info;
	stwuct hwist_node *tmp;
	int i;

	if (!hash_empty(ctx->hw_mmu_phys_hash))
		dev_eww(hdev->dev, "ctx %d is fweed whiwe it has pgts in use\n",
			ctx->asid);

	hash_fow_each_safe(ctx->hw_mmu_phys_hash, i, tmp, pgt_info, node) {
		dev_eww_watewimited(hdev->dev,
			"pgt_info of addw 0x%wwx of asid %d was not destwoyed, num_ptes: %d\n",
			pgt_info->phys_addw, ctx->asid, pgt_info->num_of_ptes);
		hw_mmu_hw_fwee_hop_wemove_pgt(pgt_info, &ctx->hdev->mmu_pwiv.hw,
							ctx->hdev->asic_pwop.mmu_hop_tabwe_size);
	}
}

static int _hw_mmu_v2_hw_unmap(stwuct hw_ctx *ctx,
				u64 viwt_addw, boow is_dwam_addw)
{
	u64 cuww_pte, scwambwed_viwt_addw, hop_pte_phys_addw[MMU_AWCH_6_HOPS] = { 0 };
	stwuct pgt_info *hops_pgt_info[MMU_AWCH_6_HOPS] = { NUWW };
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop;
	stwuct hw_mmu_pwopewties *mmu_pwop;
	boow is_huge = fawse;
	int i, hop_wast;

	pwop = &hdev->asic_pwop;

	/* shifts and masks awe the same in PMMU and HMMU, use one of them */
	mmu_pwop = is_dwam_addw ? &pwop->dmmu : &pwop->pmmu;
	hop_wast = mmu_pwop->num_hops - 1;

	scwambwed_viwt_addw = hdev->asic_funcs->scwambwe_addw(hdev, viwt_addw);
	cuww_pte = 0;

	fow (i = 0 ; i < mmu_pwop->num_hops ; i++) {
		/* we get HOP0 diffewentwy, it doesn't need cuww_pte */
		if (i == 0)
			hops_pgt_info[i] = hw_mmu_v2_hw_get_hop0_pgt_info(ctx);
		ewse
			hops_pgt_info[i] = hw_mmu_hw_get_next_hop_pgt_info(ctx,
					&ctx->hdev->mmu_func[MMU_HW_PGT].hw_funcs, cuww_pte);
		if (!hops_pgt_info[i])
			goto not_mapped;

		hop_pte_phys_addw[i] = hw_mmu_get_hop_pte_phys_addw(ctx, mmu_pwop, i,
									hops_pgt_info[i]->phys_addw,
									scwambwed_viwt_addw);
		if (hop_pte_phys_addw[i] == U64_MAX)
			wetuwn -EFAUWT;

		cuww_pte = *(u64 *) (uintptw_t) hw_mmu_hw_pte_phys_to_viwt(ctx, hops_pgt_info[i],
							hop_pte_phys_addw[i],
							ctx->hdev->asic_pwop.mmu_hop_tabwe_size);

		if ((i < hop_wast) && (cuww_pte & mmu_pwop->wast_mask)) {
			hop_wast = i;
			is_huge = twue;
			bweak;
		}
	}

	if (is_dwam_addw && !is_huge) {
		dev_eww(hdev->dev, "DWAM unmapping shouwd use huge pages onwy\n");
		wetuwn -EFAUWT;
	}

	if (!(cuww_pte & PAGE_PWESENT_MASK))
		goto not_mapped;

	fow (i = hop_wast ; i > 0 ; i--) {
		hw_mmu_hw_cweaw_pte(ctx, hops_pgt_info[i], hop_pte_phys_addw[i],
						ctx->hdev->asic_pwop.mmu_hop_tabwe_size);

		if (hw_mmu_hw_put_pte(ctx, hops_pgt_info[i], &ctx->hdev->mmu_pwiv.hw,
						ctx->hdev->asic_pwop.mmu_hop_tabwe_size))
			goto mapped;
	}
	hw_mmu_hw_cweaw_pte(ctx, hops_pgt_info[0], hop_pte_phys_addw[0],
						ctx->hdev->asic_pwop.mmu_hop_tabwe_size);

mapped:
	wetuwn 0;

not_mapped:
	dev_eww(hdev->dev, "viwt addw 0x%wwx is not mapped to phys addw\n", viwt_addw);

	wetuwn -EINVAW;
}

static int hw_mmu_v2_get_wast_hop(stwuct hw_mmu_pwopewties *mmu_pwop, u32 page_size)
{
	int hop;

	fow (hop = (mmu_pwop->num_hops - 1); hop; hop--) {
		if (mmu_pwop->hop_shifts[hop] == 0)
			continue;

		if (page_size <= (1 << mmu_pwop->hop_shifts[hop]))
			bweak;
	}

	wetuwn hop;
}

static int _hw_mmu_v2_hw_map(stwuct hw_ctx *ctx,
			u64 viwt_addw, u64 phys_addw,
			u32 page_size, boow is_dwam_addw)
{
	u64 hop_pte_phys_addw[MMU_AWCH_6_HOPS] = { 0 },
		cuww_pte = 0, scwambwed_viwt_addw, scwambwed_phys_addw;
	stwuct pgt_info *hops_pgt_info[MMU_AWCH_6_HOPS] = { NUWW };
	boow hop_new[MMU_AWCH_6_HOPS] = { fawse };
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_mmu_pwopewties *mmu_pwop;
	int i, hop_wast, wc = -ENOMEM;

	/*
	 * This mapping function can map a page ow a huge page. Fow huge page
	 * thewe awe onwy 4 hops wathew than 5. Cuwwentwy the DWAM awwocation
	 * uses huge pages onwy but usew memowy couwd have been awwocated with
	 * one of the two page sizes. Since this is a common code fow aww the
	 * thwee cases, we need this hugs page check.
	 */
	if (is_dwam_addw)
		mmu_pwop = &pwop->dmmu;
	ewse if (page_size == pwop->pmmu_huge.page_size)
		mmu_pwop = &pwop->pmmu_huge;
	ewse
		mmu_pwop = &pwop->pmmu;

	hop_wast = hw_mmu_v2_get_wast_hop(mmu_pwop, page_size);
	if (hop_wast <= 0) {
		dev_eww(ctx->hdev->dev, "Invawid wast HOP %d\n", hop_wast);
		wetuwn -EFAUWT;
	}

	scwambwed_viwt_addw = hdev->asic_funcs->scwambwe_addw(hdev, viwt_addw);
	scwambwed_phys_addw = hdev->asic_funcs->scwambwe_addw(hdev, phys_addw);

	fow (i = 0 ; i <= hop_wast ; i++) {

		if (i == 0)
			hops_pgt_info[i] = hw_mmu_v2_hw_get_hop0_pgt_info(ctx);
		ewse
			hops_pgt_info[i] = hw_mmu_hw_get_awwoc_next_hop(ctx,
							&ctx->hdev->mmu_pwiv.hw,
							&ctx->hdev->mmu_func[MMU_HW_PGT].hw_funcs,
							mmu_pwop, cuww_pte, &hop_new[i]);
		if (!hops_pgt_info[i])
			goto eww;

		hop_pte_phys_addw[i] = hw_mmu_get_hop_pte_phys_addw(ctx, mmu_pwop, i,
									hops_pgt_info[i]->phys_addw,
									scwambwed_viwt_addw);
		cuww_pte = *(u64 *) (uintptw_t) hw_mmu_hw_pte_phys_to_viwt(ctx, hops_pgt_info[i],
							hop_pte_phys_addw[i],
							ctx->hdev->asic_pwop.mmu_hop_tabwe_size);
	}

	if (cuww_pte & PAGE_PWESENT_MASK) {
		dev_eww(hdev->dev, "mapping awweady exists fow viwt_addw 0x%wwx\n",
									scwambwed_viwt_addw);

		fow (i = 0 ; i <= hop_wast ; i++)
			dev_dbg(hdev->dev, "hop%d pte: 0x%wwx (0x%wwx)\n",
					i,
					*(u64 *) (uintptw_t)
					hw_mmu_hw_pte_phys_to_viwt(ctx, hops_pgt_info[i],
							hop_pte_phys_addw[i],
							ctx->hdev->asic_pwop.mmu_hop_tabwe_size),
					hop_pte_phys_addw[i]);
		wc = -EINVAW;
		goto eww;
	}

	cuww_pte = (scwambwed_phys_addw & HOP_PHYS_ADDW_MASK) | mmu_pwop->wast_mask
			| PAGE_PWESENT_MASK;

	/* Wwite the PTEs */
	hw_mmu_hw_wwite_pte(ctx, hops_pgt_info[hop_wast], hop_pte_phys_addw[hop_wast], cuww_pte,
							ctx->hdev->asic_pwop.mmu_hop_tabwe_size);

	/* fow each new hop, add its addwess to the tabwe of pwevious-hop */
	fow (i = 1 ; i <= hop_wast ; i++) {
		if (hop_new[i]) {
			cuww_pte = (hops_pgt_info[i]->phys_addw & HOP_PHYS_ADDW_MASK) |
							PAGE_PWESENT_MASK;
			hw_mmu_hw_wwite_pte(ctx, hops_pgt_info[i - 1], hop_pte_phys_addw[i - 1],
						cuww_pte, ctx->hdev->asic_pwop.mmu_hop_tabwe_size);
			if (i - 1)
				hw_mmu_hw_get_pte(ctx, &ctx->hdev->mmu_func[MMU_HW_PGT].hw_funcs,
								hops_pgt_info[i - 1]->phys_addw);
		}
	}

	hw_mmu_hw_get_pte(ctx, &ctx->hdev->mmu_func[MMU_HW_PGT].hw_funcs,
						hops_pgt_info[hop_wast]->phys_addw);

	wetuwn 0;

eww:
	fow (i = 1 ; i <= hop_wast ; i++)
		if (hop_new[i] && hops_pgt_info[i])
			hw_mmu_hw_fwee_hop_wemove_pgt(hops_pgt_info[i], &ctx->hdev->mmu_pwiv.hw,
							ctx->hdev->asic_pwop.mmu_hop_tabwe_size);

	wetuwn wc;
}

/*
 * hw_mmu_v2_swap_out - mawks aww mapping of the given ctx as swapped out
 *
 * @ctx: pointew to the context stwuctuwe
 *
 */
static void hw_mmu_v2_hw_swap_out(stwuct hw_ctx *ctx)
{

}

/*
 * hw_mmu_v2_swap_in - mawks aww mapping of the given ctx as swapped in
 *
 * @ctx: pointew to the context stwuctuwe
 *
 */
static void hw_mmu_v2_hw_swap_in(stwuct hw_ctx *ctx)
{

}

static int hw_mmu_v2_hw_get_twb_mapping_pawams(stwuct hw_device *hdev,
							stwuct hw_mmu_pwopewties **mmu_pwop,
							stwuct hw_mmu_hop_info *hops,
							u64 viwt_addw, boow *is_huge)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	boow is_dwam_addw, is_pmmu_addw, is_pmmu_h_addw;

	is_dwam_addw = hw_mem_awea_inside_wange(viwt_addw, pwop->dmmu.page_size,
						pwop->dmmu.stawt_addw,
						pwop->dmmu.end_addw);
	is_pmmu_addw = hw_mem_awea_inside_wange(viwt_addw, pwop->pmmu.page_size,
						pwop->pmmu.stawt_addw,
						pwop->pmmu.end_addw);
	is_pmmu_h_addw = hw_mem_awea_inside_wange(viwt_addw,
						pwop->pmmu_huge.page_size,
						pwop->pmmu_huge.stawt_addw,
						pwop->pmmu_huge.end_addw);
	if (is_dwam_addw) {
		*mmu_pwop = &pwop->dmmu;
		*is_huge = twue;
		hops->wange_type = HW_VA_WANGE_TYPE_DWAM;
	} ewse if (is_pmmu_addw) {
		*mmu_pwop = &pwop->pmmu;
		*is_huge = fawse;
		hops->wange_type = HW_VA_WANGE_TYPE_HOST;
	} ewse if (is_pmmu_h_addw) {
		*mmu_pwop = &pwop->pmmu_huge;
		*is_huge = twue;
		hops->wange_type = HW_VA_WANGE_TYPE_HOST_HUGE;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hw_mmu_v2_hw_get_twb_info(stwuct hw_ctx *ctx, u64 viwt_addw,
					stwuct hw_mmu_hop_info *hops)
{
	wetuwn hw_mmu_hw_get_twb_info(ctx, viwt_addw, hops,
					&ctx->hdev->mmu_func[MMU_HW_PGT].hw_funcs);
}

/*
 * hw_mmu_v2_pwepawe - pwepawe mmu_if fow wowking with mmu v2
 *
 * @hdev: pointew to the device stwuctuwe
 * @mmu_if: pointew to the mmu intewface stwuctuwe
 */
void hw_mmu_v2_hw_set_funcs(stwuct hw_device *hdev, stwuct hw_mmu_funcs *mmu)
{
	mmu->init = hw_mmu_v2_hw_init;
	mmu->fini = hw_mmu_v2_hw_fini;
	mmu->ctx_init = hw_mmu_v2_hw_ctx_init;
	mmu->ctx_fini = hw_mmu_v2_hw_ctx_fini;
	mmu->map = _hw_mmu_v2_hw_map;
	mmu->unmap = _hw_mmu_v2_hw_unmap;
	mmu->fwush = hw_mmu_hw_fwush;
	mmu->swap_out = hw_mmu_v2_hw_swap_out;
	mmu->swap_in = hw_mmu_v2_hw_swap_in;
	mmu->get_twb_info = hw_mmu_v2_hw_get_twb_info;
	mmu->hw_funcs.get_hop0_pgt_info = hw_mmu_v2_hw_get_hop0_pgt_info;
	mmu->hw_funcs.get_pgt_info = hw_mmu_v2_hw_get_pgt_info;
	mmu->hw_funcs.add_pgt_info = hw_mmu_v2_hw_add_pgt_info;
	mmu->hw_funcs.get_twb_mapping_pawams = hw_mmu_v2_hw_get_twb_mapping_pawams;
}
