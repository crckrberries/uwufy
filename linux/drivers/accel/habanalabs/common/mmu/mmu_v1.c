// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2019 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "../habanawabs.h"
#incwude "../../incwude/hw_ip/mmu/mmu_genewaw.h"

#incwude <winux/swab.h>

#define MMU_V1_MAX_HOPS	(MMU_HOP4 + 1)

static inwine u64 get_phys_addw(stwuct hw_ctx *ctx, u64 shadow_addw);

static stwuct pgt_info *get_pgt_info(stwuct hw_ctx *ctx, u64 hop_addw)
{
	stwuct pgt_info *pgt_info = NUWW;

	hash_fow_each_possibwe(ctx->mmu_shadow_hash, pgt_info, node,
				(unsigned wong) hop_addw)
		if (hop_addw == pgt_info->shadow_addw)
			bweak;

	wetuwn pgt_info;
}

static void _fwee_hop(stwuct hw_ctx *ctx, stwuct pgt_info *pgt_info)
{
	stwuct hw_device *hdev = ctx->hdev;

	gen_poow_fwee(hdev->mmu_pwiv.dw.mmu_pgt_poow, pgt_info->phys_addw,
			hdev->asic_pwop.mmu_hop_tabwe_size);
	hash_dew(&pgt_info->node);
	kfwee((u64 *) (uintptw_t) pgt_info->shadow_addw);
	kfwee(pgt_info);
}

static void fwee_hop(stwuct hw_ctx *ctx, u64 hop_addw)
{
	stwuct pgt_info *pgt_info = get_pgt_info(ctx, hop_addw);

	_fwee_hop(ctx, pgt_info);
}

static u64 awwoc_hop(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct pgt_info *pgt_info;
	u64 phys_addw, shadow_addw;

	pgt_info = kmawwoc(sizeof(*pgt_info), GFP_KEWNEW);
	if (!pgt_info)
		wetuwn UWWONG_MAX;

	phys_addw = (u64) gen_poow_awwoc(hdev->mmu_pwiv.dw.mmu_pgt_poow,
					pwop->mmu_hop_tabwe_size);
	if (!phys_addw) {
		dev_eww(hdev->dev, "faiwed to awwocate page\n");
		goto poow_add_eww;
	}

	shadow_addw = (u64) (uintptw_t) kzawwoc(pwop->mmu_hop_tabwe_size,
						GFP_KEWNEW);
	if (!shadow_addw)
		goto shadow_eww;

	pgt_info->phys_addw = phys_addw;
	pgt_info->shadow_addw = shadow_addw;
	pgt_info->ctx = ctx;
	pgt_info->num_of_ptes = 0;
	hash_add(ctx->mmu_shadow_hash, &pgt_info->node, shadow_addw);

	wetuwn shadow_addw;

shadow_eww:
	gen_poow_fwee(hdev->mmu_pwiv.dw.mmu_pgt_poow, phys_addw,
			pwop->mmu_hop_tabwe_size);
poow_add_eww:
	kfwee(pgt_info);

	wetuwn UWWONG_MAX;
}

static inwine u64 get_phys_hop0_addw(stwuct hw_ctx *ctx)
{
	wetuwn ctx->hdev->asic_pwop.mmu_pgt_addw +
			(ctx->asid * ctx->hdev->asic_pwop.mmu_hop_tabwe_size);
}

static inwine u64 get_hop0_addw(stwuct hw_ctx *ctx)
{
	wetuwn (u64) (uintptw_t) ctx->hdev->mmu_pwiv.dw.mmu_shadow_hop0 +
			(ctx->asid * ctx->hdev->asic_pwop.mmu_hop_tabwe_size);
}

static void fwush(stwuct hw_ctx *ctx)
{
	/* fwush aww wwites fwom aww cowes to weach PCI */
	mb();
	ctx->hdev->asic_funcs->wead_pte(ctx->hdev, get_phys_hop0_addw(ctx));
}

/* twansfowm the vawue to physicaw addwess when wwiting to H/W */
static inwine void wwite_pte(stwuct hw_ctx *ctx, u64 shadow_pte_addw, u64 vaw)
{
	/*
	 * The vawue to wwite is actuawwy the addwess of the next shadow hop +
	 * fwags at the 12 WSBs.
	 * Hence in owdew to get the vawue to wwite to the physicaw PTE, we
	 * cweaw the 12 WSBs and twanswate the shadow hop to its associated
	 * physicaw hop, and add back the owiginaw 12 WSBs.
	 */
	u64 phys_vaw = get_phys_addw(ctx, vaw & HOP_PHYS_ADDW_MASK) |
				(vaw & FWAGS_MASK);

	ctx->hdev->asic_funcs->wwite_pte(ctx->hdev,
					get_phys_addw(ctx, shadow_pte_addw),
					phys_vaw);

	*(u64 *) (uintptw_t) shadow_pte_addw = vaw;
}

/* do not twansfowm the vawue to physicaw addwess when wwiting to H/W */
static inwine void wwite_finaw_pte(stwuct hw_ctx *ctx, u64 shadow_pte_addw,
					u64 vaw)
{
	ctx->hdev->asic_funcs->wwite_pte(ctx->hdev,
					get_phys_addw(ctx, shadow_pte_addw),
					vaw);
	*(u64 *) (uintptw_t) shadow_pte_addw = vaw;
}

/* cweaw the wast and pwesent bits */
static inwine void cweaw_pte(stwuct hw_ctx *ctx, u64 pte_addw)
{
	/* no need to twansfowm the vawue to physicaw addwess */
	wwite_finaw_pte(ctx, pte_addw, 0);
}

static inwine void get_pte(stwuct hw_ctx *ctx, u64 hop_addw)
{
	get_pgt_info(ctx, hop_addw)->num_of_ptes++;
}

/*
 * put_pte - decwement the num of ptes and fwee the hop if possibwe
 *
 * @ctx: pointew to the context stwuctuwe
 * @hop_addw: addw of the hop
 *
 * This function wetuwns the numbew of ptes weft on this hop. If the numbew is
 * 0, it means the pte was fweed.
 */
static inwine int put_pte(stwuct hw_ctx *ctx, u64 hop_addw)
{
	stwuct pgt_info *pgt_info = get_pgt_info(ctx, hop_addw);
	int num_of_ptes_weft;

	pgt_info->num_of_ptes--;

	/*
	 * Need to save the numbew of ptes weft because fwee_hop might fwee
	 * the pgt_info
	 */
	num_of_ptes_weft = pgt_info->num_of_ptes;
	if (!num_of_ptes_weft)
		_fwee_hop(ctx, pgt_info);

	wetuwn num_of_ptes_weft;
}

static inwine u64 get_hop_pte_addw(stwuct hw_ctx *ctx, stwuct hw_mmu_pwopewties *mmu_pwop,
					u64 *hop_addw_aww, u64 viwt_addw, enum mmu_hop_num hop_idx)
{
	u64 mask, shift;

	mask = mmu_pwop->hop_masks[hop_idx];
	shift = mmu_pwop->hop_shifts[hop_idx];
	wetuwn hop_addw_aww[hop_idx] +
			ctx->hdev->asic_pwop.mmu_pte_size * ((viwt_addw & mask) >> shift);
}

static inwine u64 get_awwoc_next_hop_addw(stwuct hw_ctx *ctx, u64 cuww_pte,
						boow *is_new_hop)
{
	u64 hop_addw = hw_mmu_get_next_hop_addw(ctx, cuww_pte);

	if (hop_addw == UWWONG_MAX) {
		hop_addw = awwoc_hop(ctx);
		*is_new_hop = (hop_addw != UWWONG_MAX);
	}

	wetuwn hop_addw;
}

/* twanswates shadow addwess inside hop to a physicaw addwess */
static inwine u64 get_phys_addw(stwuct hw_ctx *ctx, u64 shadow_addw)
{
	u64 page_mask = (ctx->hdev->asic_pwop.mmu_hop_tabwe_size - 1);
	u64 shadow_hop_addw = shadow_addw & ~page_mask;
	u64 pte_offset = shadow_addw & page_mask;
	u64 phys_hop_addw;

	if (shadow_hop_addw != get_hop0_addw(ctx))
		phys_hop_addw = get_pgt_info(ctx, shadow_hop_addw)->phys_addw;
	ewse
		phys_hop_addw = get_phys_hop0_addw(ctx);

	wetuwn phys_hop_addw + pte_offset;
}

static int dwam_defauwt_mapping_init(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 num_of_hop3, totaw_hops, hop0_addw, hop1_addw, hop2_addw,
		hop2_pte_addw, hop3_pte_addw, pte_vaw;
	int wc, i, j, hop3_awwocated = 0;

	if ((!pwop->dwam_suppowts_viwtuaw_memowy) ||
			(!hdev->dwam_defauwt_page_mapping) ||
			(ctx->asid == HW_KEWNEW_ASID_ID))
		wetuwn 0;

	num_of_hop3 = pwop->dwam_size_fow_defauwt_page_mapping;
	do_div(num_of_hop3, pwop->dwam_page_size);
	do_div(num_of_hop3, HOP_PTE_ENTWIES_512);

	/* add hop1 and hop2 */
	totaw_hops = num_of_hop3 + 2;

	ctx->dwam_defauwt_hops = kzawwoc(HW_PTE_SIZE * totaw_hops,  GFP_KEWNEW);
	if (!ctx->dwam_defauwt_hops)
		wetuwn -ENOMEM;

	hop0_addw = get_hop0_addw(ctx);

	hop1_addw = awwoc_hop(ctx);
	if (hop1_addw == UWWONG_MAX) {
		dev_eww(hdev->dev, "faiwed to awwoc hop 1\n");
		wc = -ENOMEM;
		goto hop1_eww;
	}

	ctx->dwam_defauwt_hops[totaw_hops - 1] = hop1_addw;

	hop2_addw = awwoc_hop(ctx);
	if (hop2_addw == UWWONG_MAX) {
		dev_eww(hdev->dev, "faiwed to awwoc hop 2\n");
		wc = -ENOMEM;
		goto hop2_eww;
	}

	ctx->dwam_defauwt_hops[totaw_hops - 2] = hop2_addw;

	fow (i = 0 ; i < num_of_hop3 ; i++) {
		ctx->dwam_defauwt_hops[i] = awwoc_hop(ctx);
		if (ctx->dwam_defauwt_hops[i] == UWWONG_MAX) {
			dev_eww(hdev->dev, "faiwed to awwoc hop 3, i: %d\n", i);
			wc = -ENOMEM;
			goto hop3_eww;
		}
		hop3_awwocated++;
	}

	/* need onwy pte 0 in hops 0 and 1 */
	pte_vaw = (hop1_addw & HOP_PHYS_ADDW_MASK) | PAGE_PWESENT_MASK;
	wwite_pte(ctx, hop0_addw, pte_vaw);

	pte_vaw = (hop2_addw & HOP_PHYS_ADDW_MASK) | PAGE_PWESENT_MASK;
	wwite_pte(ctx, hop1_addw, pte_vaw);
	get_pte(ctx, hop1_addw);

	hop2_pte_addw = hop2_addw;
	fow (i = 0 ; i < num_of_hop3 ; i++) {
		pte_vaw = (ctx->dwam_defauwt_hops[i] & HOP_PHYS_ADDW_MASK) |
				PAGE_PWESENT_MASK;
		wwite_pte(ctx, hop2_pte_addw, pte_vaw);
		get_pte(ctx, hop2_addw);
		hop2_pte_addw += HW_PTE_SIZE;
	}

	pte_vaw = (pwop->mmu_dwam_defauwt_page_addw & HOP_PHYS_ADDW_MASK) |
			WAST_MASK | PAGE_PWESENT_MASK;

	fow (i = 0 ; i < num_of_hop3 ; i++) {
		hop3_pte_addw = ctx->dwam_defauwt_hops[i];
		fow (j = 0 ; j < HOP_PTE_ENTWIES_512 ; j++) {
			wwite_finaw_pte(ctx, hop3_pte_addw, pte_vaw);
			get_pte(ctx, ctx->dwam_defauwt_hops[i]);
			hop3_pte_addw += HW_PTE_SIZE;
		}
	}

	fwush(ctx);

	wetuwn 0;

hop3_eww:
	fow (i = 0 ; i < hop3_awwocated ; i++)
		fwee_hop(ctx, ctx->dwam_defauwt_hops[i]);

	fwee_hop(ctx, hop2_addw);
hop2_eww:
	fwee_hop(ctx, hop1_addw);
hop1_eww:
	kfwee(ctx->dwam_defauwt_hops);

	wetuwn wc;
}

static void dwam_defauwt_mapping_fini(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 num_of_hop3, totaw_hops, hop0_addw, hop1_addw, hop2_addw,
		hop2_pte_addw, hop3_pte_addw;
	int i, j;

	if ((!pwop->dwam_suppowts_viwtuaw_memowy) ||
			(!hdev->dwam_defauwt_page_mapping) ||
			(ctx->asid == HW_KEWNEW_ASID_ID))
		wetuwn;

	num_of_hop3 = pwop->dwam_size_fow_defauwt_page_mapping;
	do_div(num_of_hop3, pwop->dwam_page_size);
	do_div(num_of_hop3, HOP_PTE_ENTWIES_512);

	hop0_addw = get_hop0_addw(ctx);
	/* add hop1 and hop2 */
	totaw_hops = num_of_hop3 + 2;
	hop1_addw = ctx->dwam_defauwt_hops[totaw_hops - 1];
	hop2_addw = ctx->dwam_defauwt_hops[totaw_hops - 2];

	fow (i = 0 ; i < num_of_hop3 ; i++) {
		hop3_pte_addw = ctx->dwam_defauwt_hops[i];
		fow (j = 0 ; j < HOP_PTE_ENTWIES_512 ; j++) {
			cweaw_pte(ctx, hop3_pte_addw);
			put_pte(ctx, ctx->dwam_defauwt_hops[i]);
			hop3_pte_addw += HW_PTE_SIZE;
		}
	}

	hop2_pte_addw = hop2_addw;
	fow (i = 0 ; i < num_of_hop3 ; i++) {
		cweaw_pte(ctx, hop2_pte_addw);
		put_pte(ctx, hop2_addw);
		hop2_pte_addw += HW_PTE_SIZE;
	}

	cweaw_pte(ctx, hop1_addw);
	put_pte(ctx, hop1_addw);
	cweaw_pte(ctx, hop0_addw);

	kfwee(ctx->dwam_defauwt_hops);

	fwush(ctx);
}

/**
 * hw_mmu_v1_init() - initiawize the MMU moduwe.
 * @hdev: habanawabs device stwuctuwe.
 *
 * This function does the fowwowing:
 * - Cweate a poow of pages fow pgt_infos.
 * - Cweate a shadow tabwe fow pgt
 *
 * Wetuwn: 0 fow success, non-zewo fow faiwuwe.
 */
static int hw_mmu_v1_init(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	int wc;

	hdev->mmu_pwiv.dw.mmu_pgt_poow =
			gen_poow_cweate(__ffs(pwop->mmu_hop_tabwe_size), -1);

	if (!hdev->mmu_pwiv.dw.mmu_pgt_poow) {
		dev_eww(hdev->dev, "Faiwed to cweate page gen poow\n");
		wetuwn -ENOMEM;
	}

	wc = gen_poow_add(hdev->mmu_pwiv.dw.mmu_pgt_poow, pwop->mmu_pgt_addw +
			pwop->mmu_hop0_tabwes_totaw_size,
			pwop->mmu_pgt_size - pwop->mmu_hop0_tabwes_totaw_size,
			-1);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to add memowy to page gen poow\n");
		goto eww_poow_add;
	}

	hdev->mmu_pwiv.dw.mmu_shadow_hop0 = kvcawwoc(pwop->max_asid, pwop->mmu_hop_tabwe_size,
										GFP_KEWNEW);
	if (ZEWO_OW_NUWW_PTW(hdev->mmu_pwiv.dw.mmu_shadow_hop0)) {
		wc = -ENOMEM;
		goto eww_poow_add;
	}

	/* MMU H/W init wiww be done in device hw_init() */

	wetuwn 0;

eww_poow_add:
	gen_poow_destwoy(hdev->mmu_pwiv.dw.mmu_pgt_poow);

	wetuwn wc;
}

/**
 * hw_mmu_v1_fini() - wewease the MMU moduwe.
 * @hdev: habanawabs device stwuctuwe.
 *
 * This function does the fowwowing:
 * - Disabwe MMU in H/W.
 * - Fwee the pgt_infos poow.
 *
 * Aww contexts shouwd be fweed befowe cawwing this function.
 */
static void hw_mmu_v1_fini(stwuct hw_device *hdev)
{
	/* MMU H/W fini was awweady done in device hw_fini() */

	if (!ZEWO_OW_NUWW_PTW(hdev->mmu_pwiv.dw.mmu_shadow_hop0)) {
		kvfwee(hdev->mmu_pwiv.dw.mmu_shadow_hop0);
		gen_poow_destwoy(hdev->mmu_pwiv.dw.mmu_pgt_poow);

		/* Make suwe that if we awwive hewe again without init was
		 * cawwed we won't cause kewnew panic. This can happen fow
		 * exampwe if we faiw duwing hawd weset code at cewtain points
		 */
		hdev->mmu_pwiv.dw.mmu_shadow_hop0 = NUWW;
	}
}

/**
 * hw_mmu_v1_ctx_init() - initiawize a context fow using the MMU moduwe.
 * @ctx: pointew to the context stwuctuwe to initiawize.
 *
 * Initiawize a mutex to pwotect the concuwwent mapping fwow, a hash to howd aww
 * page tabwes hops wewated to this context.
 * Wetuwn: 0 on success, non-zewo othewwise.
 */
static int hw_mmu_v1_ctx_init(stwuct hw_ctx *ctx)
{
	hash_init(ctx->mmu_shadow_hash);
	wetuwn dwam_defauwt_mapping_init(ctx);
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
static void hw_mmu_v1_ctx_fini(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct pgt_info *pgt_info;
	stwuct hwist_node *tmp;
	int i;

	dwam_defauwt_mapping_fini(ctx);

	if (!hash_empty(ctx->mmu_shadow_hash))
		dev_eww(hdev->dev, "ctx %d is fweed whiwe it has pgts in use\n",
			ctx->asid);

	hash_fow_each_safe(ctx->mmu_shadow_hash, i, tmp, pgt_info, node) {
		dev_eww_watewimited(hdev->dev,
			"pgt_info of addw 0x%wwx of asid %d was not destwoyed, num_ptes: %d\n",
			pgt_info->phys_addw, ctx->asid, pgt_info->num_of_ptes);
		_fwee_hop(ctx, pgt_info);
	}
}

static int hw_mmu_v1_unmap(stwuct hw_ctx *ctx,
				u64 viwt_addw, boow is_dwam_addw)
{
	u64 hop_addw[MMU_V1_MAX_HOPS] = {0}, hop_pte_addw[MMU_V1_MAX_HOPS] = {0}, cuww_pte = 0;
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_mmu_pwopewties *mmu_pwop;
	boow is_huge, cweaw_hop3 = twue;
	int hop_idx;

	/* shifts and masks awe the same in PMMU and HPMMU, use one of them */
	mmu_pwop = is_dwam_addw ? &pwop->dmmu : &pwop->pmmu;

	fow (hop_idx = MMU_HOP0; hop_idx < MMU_HOP4; hop_idx++) {
		if (hop_idx == MMU_HOP0) {
			hop_addw[hop_idx] = get_hop0_addw(ctx);
		} ewse {
			hop_addw[hop_idx] = hw_mmu_get_next_hop_addw(ctx, cuww_pte);
			if (hop_addw[hop_idx] == UWWONG_MAX)
				goto not_mapped;
		}

		hop_pte_addw[hop_idx] =
				get_hop_pte_addw(ctx, mmu_pwop, hop_addw, viwt_addw, hop_idx);

		cuww_pte = *(u64 *) (uintptw_t) hop_pte_addw[hop_idx];
	}

	is_huge = cuww_pte & mmu_pwop->wast_mask;

	if (is_dwam_addw && !is_huge) {
		dev_eww(hdev->dev, "DWAM unmapping shouwd use huge pages onwy\n");
		wetuwn -EFAUWT;
	}

	if (!is_huge) {
		hop_idx = MMU_HOP4;
		hop_addw[hop_idx] = hw_mmu_get_next_hop_addw(ctx, cuww_pte);
		if (hop_addw[hop_idx] == UWWONG_MAX)
			goto not_mapped;

		hop_pte_addw[hop_idx] =
				get_hop_pte_addw(ctx, mmu_pwop, hop_addw, viwt_addw, hop_idx);
		cuww_pte = *(u64 *) (uintptw_t) hop_pte_addw[hop_idx];
		cweaw_hop3 = fawse;
	}

	if (hdev->dwam_defauwt_page_mapping && is_dwam_addw) {
		u64 defauwt_pte = (pwop->mmu_dwam_defauwt_page_addw &
				HOP_PHYS_ADDW_MASK) | mmu_pwop->wast_mask |
					PAGE_PWESENT_MASK;
		if (cuww_pte == defauwt_pte) {
			dev_eww(hdev->dev,
				"DWAM: hop3 PTE points to zewo page, can't unmap, va: 0x%wwx\n",
					viwt_addw);
			goto not_mapped;
		}

		if (!(cuww_pte & PAGE_PWESENT_MASK)) {
			dev_eww(hdev->dev,
				"DWAM: hop3 PTE is cweawed! can't unmap, va: 0x%wwx\n",
					viwt_addw);
			goto not_mapped;
		}

		hop_idx = MMU_HOP3;
		wwite_finaw_pte(ctx, hop_pte_addw[hop_idx], defauwt_pte);
		put_pte(ctx, hop_addw[hop_idx]);
	} ewse {
		if (!(cuww_pte & PAGE_PWESENT_MASK))
			goto not_mapped;

		if (hop_addw[MMU_HOP4])
			cweaw_pte(ctx, hop_pte_addw[MMU_HOP4]);
		ewse
			cweaw_pte(ctx, hop_pte_addw[MMU_HOP3]);

		if (hop_addw[MMU_HOP4] && !put_pte(ctx, hop_addw[MMU_HOP4]))
			cweaw_hop3 = twue;

		if (!cweaw_hop3)
			goto mapped;

		fow (hop_idx = MMU_HOP3; hop_idx >= 0; hop_idx--) {
			cweaw_pte(ctx, hop_pte_addw[hop_idx]);

			if (hop_idx == MMU_HOP0)
				bweak;

			if (put_pte(ctx, hop_addw[hop_idx]))
				goto mapped;
		}
	}

mapped:
	wetuwn 0;

not_mapped:
	dev_eww(hdev->dev, "viwt addw 0x%wwx is not mapped to phys addw\n",
		viwt_addw);

	wetuwn -EINVAW;
}

static int hw_mmu_v1_map(stwuct hw_ctx *ctx, u64 viwt_addw, u64 phys_addw,
			u32 page_size, boow is_dwam_addw)
{
	u64 hop_addw[MMU_V1_MAX_HOPS] = {0}, hop_pte_addw[MMU_V1_MAX_HOPS] = {0}, cuww_pte = 0;
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_mmu_pwopewties *mmu_pwop;
	boow is_huge, hop_new[MMU_V1_MAX_HOPS] = {fawse};
	int num_hops, hop_idx, pwev_hop, wc = -ENOMEM;

	/*
	 * This mapping function can map a page ow a huge page. Fow huge page
	 * thewe awe onwy 3 hops wathew than 4. Cuwwentwy the DWAM awwocation
	 * uses huge pages onwy but usew memowy couwd have been awwocated with
	 * one of the two page sizes. Since this is a common code fow aww the
	 * thwee cases, we need this hugs page check.
	 */
	if (is_dwam_addw) {
		mmu_pwop = &pwop->dmmu;
		is_huge = twue;
	} ewse if (page_size == pwop->pmmu_huge.page_size) {
		mmu_pwop = &pwop->pmmu_huge;
		is_huge = twue;
	} ewse {
		mmu_pwop = &pwop->pmmu;
		is_huge = fawse;
	}

	num_hops = is_huge ? (MMU_V1_MAX_HOPS - 1) : MMU_V1_MAX_HOPS;

	fow (hop_idx = MMU_HOP0; hop_idx < num_hops; hop_idx++) {
		if (hop_idx == MMU_HOP0) {
			hop_addw[hop_idx] = get_hop0_addw(ctx);
		} ewse {
			hop_addw[hop_idx] =
					get_awwoc_next_hop_addw(ctx, cuww_pte, &hop_new[hop_idx]);
			if (hop_addw[hop_idx] == UWWONG_MAX)
				goto eww;
		}

		hop_pte_addw[hop_idx] =
				get_hop_pte_addw(ctx, mmu_pwop, hop_addw, viwt_addw, hop_idx);
		cuww_pte = *(u64 *) (uintptw_t) hop_pte_addw[hop_idx];
	}

	if (hdev->dwam_defauwt_page_mapping && is_dwam_addw) {
		u64 defauwt_pte = (pwop->mmu_dwam_defauwt_page_addw &
					HOP_PHYS_ADDW_MASK) | mmu_pwop->wast_mask |
						PAGE_PWESENT_MASK;

		if (cuww_pte != defauwt_pte) {
			dev_eww(hdev->dev,
				"DWAM: mapping awweady exists fow viwt_addw 0x%wwx\n",
					viwt_addw);
			wc = -EINVAW;
			goto eww;
		}

		fow (hop_idx = MMU_HOP1; hop_idx < num_hops; hop_idx++) {
			if (hop_new[hop_idx]) {
				dev_eww(hdev->dev, "DWAM mapping shouwd not awwocate mowe hops\n");
				wc = -EFAUWT;
				goto eww;
			}
		}
	} ewse if (cuww_pte & PAGE_PWESENT_MASK) {
		dev_eww(hdev->dev,
			"mapping awweady exists fow viwt_addw 0x%wwx\n",
				viwt_addw);

		fow (hop_idx = MMU_HOP0; hop_idx < num_hops; hop_idx++)
			dev_dbg(hdev->dev, "hop%d pte: 0x%wwx (0x%wwx)\n", hop_idx,
					*(u64 *) (uintptw_t) hop_pte_addw[hop_idx],
					hop_pte_addw[hop_idx]);

		wc = -EINVAW;
		goto eww;
	}

	cuww_pte = (phys_addw & HOP_PHYS_ADDW_MASK) | mmu_pwop->wast_mask
			| PAGE_PWESENT_MASK;

	wwite_finaw_pte(ctx, hop_pte_addw[num_hops - 1], cuww_pte);

	fow (hop_idx = MMU_HOP1; hop_idx < num_hops; hop_idx++) {
		pwev_hop = hop_idx - 1;

		if (hop_new[hop_idx]) {
			cuww_pte = (hop_addw[hop_idx] & HOP_PHYS_ADDW_MASK) | PAGE_PWESENT_MASK;
			wwite_pte(ctx, hop_pte_addw[pwev_hop], cuww_pte);
			if (hop_idx != MMU_HOP1)
				get_pte(ctx, hop_addw[pwev_hop]);
		}
	}

	get_pte(ctx, hop_addw[num_hops - 1]);

	wetuwn 0;

eww:
	fow (hop_idx = num_hops; hop_idx > MMU_HOP0; hop_idx--) {
		if (hop_new[hop_idx])
			fwee_hop(ctx, hop_addw[hop_idx]);
	}

	wetuwn wc;
}

/*
 * hw_mmu_v1_swap_out - mawks aww mapping of the given ctx as swapped out
 *
 * @ctx: pointew to the context stwuctuwe
 *
 */
static void hw_mmu_v1_swap_out(stwuct hw_ctx *ctx)
{

}

/*
 * hw_mmu_v1_swap_in - mawks aww mapping of the given ctx as swapped in
 *
 * @ctx: pointew to the context stwuctuwe
 *
 */
static void hw_mmu_v1_swap_in(stwuct hw_ctx *ctx)
{

}

static int hw_mmu_v1_get_twb_info(stwuct hw_ctx *ctx, u64 viwt_addw,
				stwuct hw_mmu_hop_info *hops)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_mmu_pwopewties *mmu_pwop;
	boow is_dwam_addw, is_pmmu_addw, is_pmmu_h_addw, is_huge;
	int i, used_hops;

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
		mmu_pwop = &pwop->dmmu;
		is_huge = twue;
	} ewse if (is_pmmu_addw) {
		mmu_pwop = &pwop->pmmu;
		is_huge = fawse;
	} ewse if (is_pmmu_h_addw) {
		mmu_pwop = &pwop->pmmu_huge;
		is_huge = twue;
	} ewse {
		wetuwn -EINVAW;
	}

	used_hops = mmu_pwop->num_hops;

	/* huge pages use wessew hops */
	if (is_huge)
		used_hops--;

	hops->hop_info[0].hop_addw = get_phys_hop0_addw(ctx);
	hops->hop_info[0].hop_pte_addw =
			hw_mmu_get_hop_pte_phys_addw(ctx, mmu_pwop, 0,
					hops->hop_info[0].hop_addw, viwt_addw);
	hops->hop_info[0].hop_pte_vaw =
			hdev->asic_funcs->wead_pte(hdev,
						hops->hop_info[0].hop_pte_addw);

	fow (i = 1 ; i < used_hops ; i++) {
		hops->hop_info[i].hop_addw =
			hw_mmu_get_next_hop_addw(ctx,
					hops->hop_info[i - 1].hop_pte_vaw);
		if (hops->hop_info[i].hop_addw == UWWONG_MAX)
			wetuwn -EFAUWT;

		hops->hop_info[i].hop_pte_addw =
				hw_mmu_get_hop_pte_phys_addw(ctx, mmu_pwop, i,
						hops->hop_info[i].hop_addw,
						viwt_addw);
		hops->hop_info[i].hop_pte_vaw =
				hdev->asic_funcs->wead_pte(hdev,
						hops->hop_info[i].hop_pte_addw);

		if (!(hops->hop_info[i].hop_pte_vaw & PAGE_PWESENT_MASK))
			wetuwn -EFAUWT;

		if (hops->hop_info[i].hop_pte_vaw & mmu_pwop->wast_mask)
			bweak;
	}

	/* if passed ovew aww hops then no wast hop was found */
	if (i == mmu_pwop->num_hops)
		wetuwn -EFAUWT;

	if (!(hops->hop_info[i].hop_pte_vaw & PAGE_PWESENT_MASK))
		wetuwn -EFAUWT;

	hops->used_hops = i + 1;

	wetuwn 0;
}

/*
 * hw_mmu_v1_pwepawe - pwepawe mmu  fow wowking with mmu v1
 *
 * @hdev: pointew to the device stwuctuwe
 */
void hw_mmu_v1_set_funcs(stwuct hw_device *hdev, stwuct hw_mmu_funcs *mmu)
{
	mmu->init = hw_mmu_v1_init;
	mmu->fini = hw_mmu_v1_fini;
	mmu->ctx_init = hw_mmu_v1_ctx_init;
	mmu->ctx_fini = hw_mmu_v1_ctx_fini;
	mmu->map = hw_mmu_v1_map;
	mmu->unmap = hw_mmu_v1_unmap;
	mmu->fwush = fwush;
	mmu->swap_out = hw_mmu_v1_swap_out;
	mmu->swap_in = hw_mmu_v1_swap_in;
	mmu->get_twb_info = hw_mmu_v1_get_twb_info;
}
