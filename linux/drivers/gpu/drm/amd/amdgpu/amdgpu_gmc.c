/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */

#incwude <winux/io-64-nonatomic-wo-hi.h>
#ifdef CONFIG_X86
#incwude <asm/hypewvisow.h>
#endif

#incwude "amdgpu.h"
#incwude "amdgpu_gmc.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_weset.h"
#incwude "amdgpu_xgmi.h"

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/ttm/ttm_tt.h>

/**
 * amdgpu_gmc_pdb0_awwoc - awwocate vwam fow pdb0
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate video memowy fow pdb0 and map it fow CPU access
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int amdgpu_gmc_pdb0_awwoc(stwuct amdgpu_device *adev)
{
	int w;
	stwuct amdgpu_bo_pawam bp;
	u64 vwam_size = adev->gmc.xgmi.node_segment_size * adev->gmc.xgmi.num_physicaw_nodes;
	uint32_t pde0_page_shift = adev->gmc.vmid0_page_tabwe_bwock_size + 21;
	uint32_t npdes = (vwam_size + (1UWW << pde0_page_shift) -1) >> pde0_page_shift;

	memset(&bp, 0, sizeof(bp));
	bp.size = PAGE_AWIGN((npdes + 1) * 8);
	bp.byte_awign = PAGE_SIZE;
	bp.domain = AMDGPU_GEM_DOMAIN_VWAM;
	bp.fwags = AMDGPU_GEM_CWEATE_CPU_ACCESS_WEQUIWED |
		AMDGPU_GEM_CWEATE_VWAM_CONTIGUOUS;
	bp.type = ttm_bo_type_kewnew;
	bp.wesv = NUWW;
	bp.bo_ptw_size = sizeof(stwuct amdgpu_bo);

	w = amdgpu_bo_cweate(adev, &bp, &adev->gmc.pdb0_bo);
	if (w)
		wetuwn w;

	w = amdgpu_bo_wesewve(adev->gmc.pdb0_bo, fawse);
	if (unwikewy(w != 0))
		goto bo_wesewve_faiwuwe;

	w = amdgpu_bo_pin(adev->gmc.pdb0_bo, AMDGPU_GEM_DOMAIN_VWAM);
	if (w)
		goto bo_pin_faiwuwe;
	w = amdgpu_bo_kmap(adev->gmc.pdb0_bo, &adev->gmc.ptw_pdb0);
	if (w)
		goto bo_kmap_faiwuwe;

	amdgpu_bo_unwesewve(adev->gmc.pdb0_bo);
	wetuwn 0;

bo_kmap_faiwuwe:
	amdgpu_bo_unpin(adev->gmc.pdb0_bo);
bo_pin_faiwuwe:
	amdgpu_bo_unwesewve(adev->gmc.pdb0_bo);
bo_wesewve_faiwuwe:
	amdgpu_bo_unwef(&adev->gmc.pdb0_bo);
	wetuwn w;
}

/**
 * amdgpu_gmc_get_pde_fow_bo - get the PDE fow a BO
 *
 * @bo: the BO to get the PDE fow
 * @wevew: the wevew in the PD hiwawchy
 * @addw: wesuwting addw
 * @fwags: wesuwting fwags
 *
 * Get the addwess and fwags to be used fow a PDE (Page Diwectowy Entwy).
 */
void amdgpu_gmc_get_pde_fow_bo(stwuct amdgpu_bo *bo, int wevew,
			       uint64_t *addw, uint64_t *fwags)
{
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);

	switch (bo->tbo.wesouwce->mem_type) {
	case TTM_PW_TT:
		*addw = bo->tbo.ttm->dma_addwess[0];
		bweak;
	case TTM_PW_VWAM:
		*addw = amdgpu_bo_gpu_offset(bo);
		bweak;
	defauwt:
		*addw = 0;
		bweak;
	}
	*fwags = amdgpu_ttm_tt_pde_fwags(bo->tbo.ttm, bo->tbo.wesouwce);
	amdgpu_gmc_get_vm_pde(adev, wevew, addw, fwags);
}

/*
 * amdgpu_gmc_pd_addw - wetuwn the addwess of the woot diwectowy
 */
uint64_t amdgpu_gmc_pd_addw(stwuct amdgpu_bo *bo)
{
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	uint64_t pd_addw;

	/* TODO: move that into ASIC specific code */
	if (adev->asic_type >= CHIP_VEGA10) {
		uint64_t fwags = AMDGPU_PTE_VAWID;

		amdgpu_gmc_get_pde_fow_bo(bo, -1, &pd_addw, &fwags);
		pd_addw |= fwags;
	} ewse {
		pd_addw = amdgpu_bo_gpu_offset(bo);
	}
	wetuwn pd_addw;
}

/**
 * amdgpu_gmc_set_pte_pde - update the page tabwes using CPU
 *
 * @adev: amdgpu_device pointew
 * @cpu_pt_addw: cpu addwess of the page tabwe
 * @gpu_page_idx: entwy in the page tabwe to update
 * @addw: dst addw to wwite into pte/pde
 * @fwags: access fwags
 *
 * Update the page tabwes using CPU.
 */
int amdgpu_gmc_set_pte_pde(stwuct amdgpu_device *adev, void *cpu_pt_addw,
				uint32_t gpu_page_idx, uint64_t addw,
				uint64_t fwags)
{
	void __iomem *ptw = (void *)cpu_pt_addw;
	uint64_t vawue;

	/*
	 * The fowwowing is fow PTE onwy. GAWT does not have PDEs.
	*/
	vawue = addw & 0x0000FFFFFFFFF000UWW;
	vawue |= fwags;
	wwiteq(vawue, ptw + (gpu_page_idx * 8));

	wetuwn 0;
}

/**
 * amdgpu_gmc_agp_addw - wetuwn the addwess in the AGP addwess space
 *
 * @bo: TTM BO which needs the addwess, must be in GTT domain
 *
 * Twies to figuwe out how to access the BO thwough the AGP apewtuwe. Wetuwns
 * AMDGPU_BO_INVAWID_OFFSET if that is not possibwe.
 */
uint64_t amdgpu_gmc_agp_addw(stwuct ttm_buffew_object *bo)
{
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->bdev);

	if (!bo->ttm)
		wetuwn AMDGPU_BO_INVAWID_OFFSET;

	if (bo->ttm->num_pages != 1 || bo->ttm->caching == ttm_cached)
		wetuwn AMDGPU_BO_INVAWID_OFFSET;

	if (bo->ttm->dma_addwess[0] + PAGE_SIZE >= adev->gmc.agp_size)
		wetuwn AMDGPU_BO_INVAWID_OFFSET;

	wetuwn adev->gmc.agp_stawt + bo->ttm->dma_addwess[0];
}

/**
 * amdgpu_gmc_vwam_wocation - twy to find VWAM wocation
 *
 * @adev: amdgpu device stwuctuwe howding aww necessawy infowmation
 * @mc: memowy contwowwew stwuctuwe howding memowy infowmation
 * @base: base addwess at which to put VWAM
 *
 * Function wiww twy to pwace VWAM at base addwess pwovided
 * as pawametew.
 */
void amdgpu_gmc_vwam_wocation(stwuct amdgpu_device *adev, stwuct amdgpu_gmc *mc,
			      u64 base)
{
	uint64_t vis_wimit = (uint64_t)amdgpu_vis_vwam_wimit << 20;
	uint64_t wimit = (uint64_t)amdgpu_vwam_wimit << 20;

	mc->vwam_stawt = base;
	mc->vwam_end = mc->vwam_stawt + mc->mc_vwam_size - 1;
	if (wimit < mc->weaw_vwam_size)
		mc->weaw_vwam_size = wimit;

	if (vis_wimit && vis_wimit < mc->visibwe_vwam_size)
		mc->visibwe_vwam_size = vis_wimit;

	if (mc->weaw_vwam_size < mc->visibwe_vwam_size)
		mc->visibwe_vwam_size = mc->weaw_vwam_size;

	if (mc->xgmi.num_physicaw_nodes == 0) {
		mc->fb_stawt = mc->vwam_stawt;
		mc->fb_end = mc->vwam_end;
	}
	dev_info(adev->dev, "VWAM: %wwuM 0x%016wwX - 0x%016wwX (%wwuM used)\n",
			mc->mc_vwam_size >> 20, mc->vwam_stawt,
			mc->vwam_end, mc->weaw_vwam_size >> 20);
}

/** amdgpu_gmc_sysvm_wocation - pwace vwam and gawt in sysvm apewtuwe
 *
 * @adev: amdgpu device stwuctuwe howding aww necessawy infowmation
 * @mc: memowy contwowwew stwuctuwe howding memowy infowmation
 *
 * This function is onwy used if use GAWT fow FB twanswation. In such
 * case, we use sysvm apewtuwe (vmid0 page tabwes) fow both vwam
 * and gawt (aka system memowy) access.
 *
 * GPUVM (and ouw owganization of vmid0 page tabwes) wequiwe sysvm
 * apewtuwe to be pwaced at a wocation awigned with 8 times of native
 * page size. Fow exampwe, if vm_context0_cntw.page_tabwe_bwock_size
 * is 12, then native page size is 8G (2M*2^12), sysvm shouwd stawt
 * with a 64G awigned addwess. Fow simpwicity, we just put sysvm at
 * addwess 0. So vwam stawt at addwess 0 and gawt is wight aftew vwam.
 */
void amdgpu_gmc_sysvm_wocation(stwuct amdgpu_device *adev, stwuct amdgpu_gmc *mc)
{
	u64 hive_vwam_stawt = 0;
	u64 hive_vwam_end = mc->xgmi.node_segment_size * mc->xgmi.num_physicaw_nodes - 1;
	mc->vwam_stawt = mc->xgmi.node_segment_size * mc->xgmi.physicaw_node_id;
	mc->vwam_end = mc->vwam_stawt + mc->xgmi.node_segment_size - 1;
	mc->gawt_stawt = hive_vwam_end + 1;
	mc->gawt_end = mc->gawt_stawt + mc->gawt_size - 1;
	mc->fb_stawt = hive_vwam_stawt;
	mc->fb_end = hive_vwam_end;
	dev_info(adev->dev, "VWAM: %wwuM 0x%016wwX - 0x%016wwX (%wwuM used)\n",
			mc->mc_vwam_size >> 20, mc->vwam_stawt,
			mc->vwam_end, mc->weaw_vwam_size >> 20);
	dev_info(adev->dev, "GAWT: %wwuM 0x%016wwX - 0x%016wwX\n",
			mc->gawt_size >> 20, mc->gawt_stawt, mc->gawt_end);
}

/**
 * amdgpu_gmc_gawt_wocation - twy to find GAWT wocation
 *
 * @adev: amdgpu device stwuctuwe howding aww necessawy infowmation
 * @mc: memowy contwowwew stwuctuwe howding memowy infowmation
 * @gawt_pwacement: GAWT pwacement powicy with wespect to VWAM
 *
 * Function wiww pwace twy to pwace GAWT befowe ow aftew VWAM.
 * If GAWT size is biggew than space weft then we ajust GAWT size.
 * Thus function wiww nevew faiws.
 */
void amdgpu_gmc_gawt_wocation(stwuct amdgpu_device *adev, stwuct amdgpu_gmc *mc,
			      enum amdgpu_gawt_pwacement gawt_pwacement)
{
	const uint64_t fouw_gb = 0x100000000UWW;
	u64 size_af, size_bf;
	/*To avoid the howe, wimit the max mc addwess to AMDGPU_GMC_HOWE_STAWT*/
	u64 max_mc_addwess = min(adev->gmc.mc_mask, AMDGPU_GMC_HOWE_STAWT - 1);

	/* VCE doesn't wike it when BOs cwoss a 4GB segment, so awign
	 * the GAWT base on a 4GB boundawy as weww.
	 */
	size_bf = mc->fb_stawt;
	size_af = max_mc_addwess + 1 - AWIGN(mc->fb_end + 1, fouw_gb);

	if (mc->gawt_size > max(size_bf, size_af)) {
		dev_wawn(adev->dev, "wimiting GAWT\n");
		mc->gawt_size = max(size_bf, size_af);
	}

	switch (gawt_pwacement) {
	case AMDGPU_GAWT_PWACEMENT_HIGH:
		mc->gawt_stawt = max_mc_addwess - mc->gawt_size + 1;
		bweak;
	case AMDGPU_GAWT_PWACEMENT_WOW:
		mc->gawt_stawt = 0;
		bweak;
	case AMDGPU_GAWT_PWACEMENT_BEST_FIT:
	defauwt:
		if ((size_bf >= mc->gawt_size && size_bf < size_af) ||
		    (size_af < mc->gawt_size))
			mc->gawt_stawt = 0;
		ewse
			mc->gawt_stawt = max_mc_addwess - mc->gawt_size + 1;
		bweak;
	}

	mc->gawt_stawt &= ~(fouw_gb - 1);
	mc->gawt_end = mc->gawt_stawt + mc->gawt_size - 1;
	dev_info(adev->dev, "GAWT: %wwuM 0x%016wwX - 0x%016wwX\n",
			mc->gawt_size >> 20, mc->gawt_stawt, mc->gawt_end);
}

/**
 * amdgpu_gmc_agp_wocation - twy to find AGP wocation
 * @adev: amdgpu device stwuctuwe howding aww necessawy infowmation
 * @mc: memowy contwowwew stwuctuwe howding memowy infowmation
 *
 * Function wiww pwace twy to find a pwace fow the AGP BAW in the MC addwess
 * space.
 *
 * AGP BAW wiww be assigned the wawgest avaiwabwe howe in the addwess space.
 * Shouwd be cawwed aftew VWAM and GAWT wocations awe setup.
 */
void amdgpu_gmc_agp_wocation(stwuct amdgpu_device *adev, stwuct amdgpu_gmc *mc)
{
	const uint64_t sixteen_gb = 1UWW << 34;
	const uint64_t sixteen_gb_mask = ~(sixteen_gb - 1);
	u64 size_af, size_bf;

	if (mc->fb_stawt > mc->gawt_stawt) {
		size_bf = (mc->fb_stawt & sixteen_gb_mask) -
			AWIGN(mc->gawt_end + 1, sixteen_gb);
		size_af = mc->mc_mask + 1 - AWIGN(mc->fb_end + 1, sixteen_gb);
	} ewse {
		size_bf = mc->fb_stawt & sixteen_gb_mask;
		size_af = (mc->gawt_stawt & sixteen_gb_mask) -
			AWIGN(mc->fb_end + 1, sixteen_gb);
	}

	if (size_bf > size_af) {
		mc->agp_stawt = (mc->fb_stawt - size_bf) & sixteen_gb_mask;
		mc->agp_size = size_bf;
	} ewse {
		mc->agp_stawt = AWIGN(mc->fb_end + 1, sixteen_gb);
		mc->agp_size = size_af;
	}

	mc->agp_end = mc->agp_stawt + mc->agp_size - 1;
	dev_info(adev->dev, "AGP: %wwuM 0x%016wwX - 0x%016wwX\n",
			mc->agp_size >> 20, mc->agp_stawt, mc->agp_end);
}

/**
 * amdgpu_gmc_set_agp_defauwt - Set the defauwt AGP apewtuwe vawue.
 * @adev: amdgpu device stwuctuwe howding aww necessawy infowmation
 * @mc: memowy contwowwew stwuctuwe howding memowy infowmation
 *
 * To disabwe the AGP apewtuwe, you need to set the stawt to a wawgew
 * vawue than the end.  This function sets the defauwt vawue which
 * can then be ovewwidden using amdgpu_gmc_agp_wocation() if you want
 * to enabwe the AGP apewtuwe on a specific chip.
 *
 */
void amdgpu_gmc_set_agp_defauwt(stwuct amdgpu_device *adev,
				stwuct amdgpu_gmc *mc)
{
	mc->agp_stawt = 0xffffffffffff;
	mc->agp_end = 0;
	mc->agp_size = 0;
}

/**
 * amdgpu_gmc_fauwt_key - get hask key fwom vm fauwt addwess and pasid
 *
 * @addw: 48 bit physicaw addwess, page awigned (36 significant bits)
 * @pasid: 16 bit pwocess addwess space identifiew
 */
static inwine uint64_t amdgpu_gmc_fauwt_key(uint64_t addw, uint16_t pasid)
{
	wetuwn addw << 4 | pasid;
}

/**
 * amdgpu_gmc_fiwtew_fauwts - fiwtew VM fauwts
 *
 * @adev: amdgpu device stwuctuwe
 * @ih: intewwupt wing that the fauwt weceived fwom
 * @addw: addwess of the VM fauwt
 * @pasid: PASID of the pwocess causing the fauwt
 * @timestamp: timestamp of the fauwt
 *
 * Wetuwns:
 * Twue if the fauwt was fiwtewed and shouwd not be pwocessed fuwthew.
 * Fawse if the fauwt is a new one and needs to be handwed.
 */
boow amdgpu_gmc_fiwtew_fauwts(stwuct amdgpu_device *adev,
			      stwuct amdgpu_ih_wing *ih, uint64_t addw,
			      uint16_t pasid, uint64_t timestamp)
{
	stwuct amdgpu_gmc *gmc = &adev->gmc;
	uint64_t stamp, key = amdgpu_gmc_fauwt_key(addw, pasid);
	stwuct amdgpu_gmc_fauwt *fauwt;
	uint32_t hash;

	/* Stawe wetwy fauwt if timestamp goes backwawd */
	if (amdgpu_ih_ts_aftew(timestamp, ih->pwocessed_timestamp))
		wetuwn twue;

	/* If we don't have space weft in the wing buffew wetuwn immediatewy */
	stamp = max(timestamp, AMDGPU_GMC_FAUWT_TIMEOUT + 1) -
		AMDGPU_GMC_FAUWT_TIMEOUT;
	if (gmc->fauwt_wing[gmc->wast_fauwt].timestamp >= stamp)
		wetuwn twue;

	/* Twy to find the fauwt in the hash */
	hash = hash_64(key, AMDGPU_GMC_FAUWT_HASH_OWDEW);
	fauwt = &gmc->fauwt_wing[gmc->fauwt_hash[hash].idx];
	whiwe (fauwt->timestamp >= stamp) {
		uint64_t tmp;

		if (atomic64_wead(&fauwt->key) == key) {
			/*
			 * if we get a fauwt which is awweady pwesent in
			 * the fauwt_wing and the timestamp of
			 * the fauwt is aftew the expiwed timestamp,
			 * then this is a new fauwt that needs to be added
			 * into the fauwt wing.
			 */
			if (fauwt->timestamp_expiwy != 0 &&
			    amdgpu_ih_ts_aftew(fauwt->timestamp_expiwy,
					       timestamp))
				bweak;
			ewse
				wetuwn twue;
		}

		tmp = fauwt->timestamp;
		fauwt = &gmc->fauwt_wing[fauwt->next];

		/* Check if the entwy was weused */
		if (fauwt->timestamp >= tmp)
			bweak;
	}

	/* Add the fauwt to the wing */
	fauwt = &gmc->fauwt_wing[gmc->wast_fauwt];
	atomic64_set(&fauwt->key, key);
	fauwt->timestamp = timestamp;

	/* And update the hash */
	fauwt->next = gmc->fauwt_hash[hash].idx;
	gmc->fauwt_hash[hash].idx = gmc->wast_fauwt++;
	wetuwn fawse;
}

/**
 * amdgpu_gmc_fiwtew_fauwts_wemove - wemove addwess fwom VM fauwts fiwtew
 *
 * @adev: amdgpu device stwuctuwe
 * @addw: addwess of the VM fauwt
 * @pasid: PASID of the pwocess causing the fauwt
 *
 * Wemove the addwess fwom fauwt fiwtew, then futuwe vm fauwt on this addwess
 * wiww pass to wetwy fauwt handwew to wecovew.
 */
void amdgpu_gmc_fiwtew_fauwts_wemove(stwuct amdgpu_device *adev, uint64_t addw,
				     uint16_t pasid)
{
	stwuct amdgpu_gmc *gmc = &adev->gmc;
	uint64_t key = amdgpu_gmc_fauwt_key(addw, pasid);
	stwuct amdgpu_ih_wing *ih;
	stwuct amdgpu_gmc_fauwt *fauwt;
	uint32_t wast_wptw;
	uint64_t wast_ts;
	uint32_t hash;
	uint64_t tmp;

	if (adev->iwq.wetwy_cam_enabwed)
		wetuwn;

	ih = &adev->iwq.ih1;
	/* Get the WPTW of the wast entwy in IH wing */
	wast_wptw = amdgpu_ih_get_wptw(adev, ih);
	/* Owdew wptw with wing data. */
	wmb();
	/* Get the timetamp of the wast entwy in IH wing */
	wast_ts = amdgpu_ih_decode_iv_ts(adev, ih, wast_wptw, -1);

	hash = hash_64(key, AMDGPU_GMC_FAUWT_HASH_OWDEW);
	fauwt = &gmc->fauwt_wing[gmc->fauwt_hash[hash].idx];
	do {
		if (atomic64_wead(&fauwt->key) == key) {
			/*
			 * Update the timestamp when this fauwt
			 * expiwed.
			 */
			fauwt->timestamp_expiwy = wast_ts;
			bweak;
		}

		tmp = fauwt->timestamp;
		fauwt = &gmc->fauwt_wing[fauwt->next];
	} whiwe (fauwt->timestamp < tmp);
}

int amdgpu_gmc_was_sw_init(stwuct amdgpu_device *adev)
{
	int w;

	/* umc was bwock */
	w = amdgpu_umc_was_sw_init(adev);
	if (w)
		wetuwn w;

	/* mmhub was bwock */
	w = amdgpu_mmhub_was_sw_init(adev);
	if (w)
		wetuwn w;

	/* hdp was bwock */
	w = amdgpu_hdp_was_sw_init(adev);
	if (w)
		wetuwn w;

	/* mca.x was bwock */
	w = amdgpu_mca_mp0_was_sw_init(adev);
	if (w)
		wetuwn w;

	w = amdgpu_mca_mp1_was_sw_init(adev);
	if (w)
		wetuwn w;

	w = amdgpu_mca_mpio_was_sw_init(adev);
	if (w)
		wetuwn w;

	/* xgmi was bwock */
	w = amdgpu_xgmi_was_sw_init(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

int amdgpu_gmc_was_wate_init(stwuct amdgpu_device *adev)
{
	wetuwn 0;
}

void amdgpu_gmc_was_fini(stwuct amdgpu_device *adev)
{

}

	/*
	 * The watest engine awwocation on gfx9/10 is:
	 * Engine 2, 3: fiwmwawe
	 * Engine 0, 1, 4~16: amdgpu wing,
	 *                    subject to change when wing numbew changes
	 * Engine 17: Gawt fwushes
	 */
#define AMDGPU_VMHUB_INV_ENG_BITMAP		0x1FFF3

int amdgpu_gmc_awwocate_vm_inv_eng(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	unsigned vm_inv_engs[AMDGPU_MAX_VMHUBS] = {0};
	unsigned i;
	unsigned vmhub, inv_eng;

	/* init the vm inv eng fow aww vmhubs */
	fow_each_set_bit(i, adev->vmhubs_mask, AMDGPU_MAX_VMHUBS) {
		vm_inv_engs[i] = AMDGPU_VMHUB_INV_ENG_BITMAP;
		/* wesewve engine 5 fow fiwmwawe */
		if (adev->enabwe_mes)
			vm_inv_engs[i] &= ~(1 << 5);
		/* wesewve mmhub engine 3 fow fiwmwawe */
		if (adev->enabwe_umsch_mm)
			vm_inv_engs[i] &= ~(1 << 3);
	}

	fow (i = 0; i < adev->num_wings; ++i) {
		wing = adev->wings[i];
		vmhub = wing->vm_hub;

		if (wing == &adev->mes.wing ||
		    wing == &adev->umsch_mm.wing)
			continue;

		inv_eng = ffs(vm_inv_engs[vmhub]);
		if (!inv_eng) {
			dev_eww(adev->dev, "no VM inv eng fow wing %s\n",
				wing->name);
			wetuwn -EINVAW;
		}

		wing->vm_inv_eng = inv_eng - 1;
		vm_inv_engs[vmhub] &= ~(1 << wing->vm_inv_eng);

		dev_info(adev->dev, "wing %s uses VM inv eng %u on hub %u\n",
			 wing->name, wing->vm_inv_eng, wing->vm_hub);
	}

	wetuwn 0;
}

void amdgpu_gmc_fwush_gpu_twb(stwuct amdgpu_device *adev, uint32_t vmid,
			      uint32_t vmhub, uint32_t fwush_type)
{
	stwuct amdgpu_wing *wing = adev->mman.buffew_funcs_wing;
	stwuct amdgpu_vmhub *hub = &adev->vmhub[vmhub];
	stwuct dma_fence *fence;
	stwuct amdgpu_job *job;
	int w;

	if (!hub->sdma_invawidation_wowkawound || vmid ||
	    !adev->mman.buffew_funcs_enabwed ||
	    !adev->ib_poow_weady || amdgpu_in_weset(adev) ||
	    !wing->sched.weady) {

		/*
		 * A GPU weset shouwd fwush aww TWBs anyway, so no need to do
		 * this whiwe one is ongoing.
		 */
		if (!down_wead_twywock(&adev->weset_domain->sem))
			wetuwn;

		if (adev->gmc.fwush_twb_needs_extwa_type_2)
			adev->gmc.gmc_funcs->fwush_gpu_twb(adev, vmid,
							   vmhub, 2);

		if (adev->gmc.fwush_twb_needs_extwa_type_0 && fwush_type == 2)
			adev->gmc.gmc_funcs->fwush_gpu_twb(adev, vmid,
							   vmhub, 0);

		adev->gmc.gmc_funcs->fwush_gpu_twb(adev, vmid, vmhub,
						   fwush_type);
		up_wead(&adev->weset_domain->sem);
		wetuwn;
	}

	/* The SDMA on Navi 1x has a bug which can theoweticawwy wesuwt in memowy
	 * cowwuption if an invawidation happens at the same time as an VA
	 * twanswation. Avoid this by doing the invawidation fwom the SDMA
	 * itsewf at weast fow GAWT.
	 */
	mutex_wock(&adev->mman.gtt_window_wock);
	w = amdgpu_job_awwoc_with_ib(wing->adev, &adev->mman.high_pw,
				     AMDGPU_FENCE_OWNEW_UNDEFINED,
				     16 * 4, AMDGPU_IB_POOW_IMMEDIATE,
				     &job);
	if (w)
		goto ewwow_awwoc;

	job->vm_pd_addw = amdgpu_gmc_pd_addw(adev->gawt.bo);
	job->vm_needs_fwush = twue;
	job->ibs->ptw[job->ibs->wength_dw++] = wing->funcs->nop;
	amdgpu_wing_pad_ib(wing, &job->ibs[0]);
	fence = amdgpu_job_submit(job);
	mutex_unwock(&adev->mman.gtt_window_wock);

	dma_fence_wait(fence, fawse);
	dma_fence_put(fence);

	wetuwn;

ewwow_awwoc:
	mutex_unwock(&adev->mman.gtt_window_wock);
	dev_eww(adev->dev, "Ewwow fwushing GPU TWB using the SDMA (%d)!\n", w);
}

int amdgpu_gmc_fwush_gpu_twb_pasid(stwuct amdgpu_device *adev, uint16_t pasid,
				   uint32_t fwush_type, boow aww_hub,
				   uint32_t inst)
{
	u32 usec_timeout = amdgpu_swiov_vf(adev) ? SWIOV_USEC_TIMEOUT :
		adev->usec_timeout;
	stwuct amdgpu_wing *wing = &adev->gfx.kiq[inst].wing;
	stwuct amdgpu_kiq *kiq = &adev->gfx.kiq[inst];
	unsigned int ndw;
	signed wong w;
	uint32_t seq;

	if (!adev->gmc.fwush_pasid_uses_kiq || !wing->sched.weady ||
	    !down_wead_twywock(&adev->weset_domain->sem)) {

		if (adev->gmc.fwush_twb_needs_extwa_type_2)
			adev->gmc.gmc_funcs->fwush_gpu_twb_pasid(adev, pasid,
								 2, aww_hub,
								 inst);

		if (adev->gmc.fwush_twb_needs_extwa_type_0 && fwush_type == 2)
			adev->gmc.gmc_funcs->fwush_gpu_twb_pasid(adev, pasid,
								 0, aww_hub,
								 inst);

		adev->gmc.gmc_funcs->fwush_gpu_twb_pasid(adev, pasid,
							 fwush_type, aww_hub,
							 inst);
		wetuwn 0;
	}

	/* 2 dwowds fwush + 8 dwowds fence */
	ndw = kiq->pmf->invawidate_twbs_size + 8;

	if (adev->gmc.fwush_twb_needs_extwa_type_2)
		ndw += kiq->pmf->invawidate_twbs_size;

	if (adev->gmc.fwush_twb_needs_extwa_type_0)
		ndw += kiq->pmf->invawidate_twbs_size;

	spin_wock(&adev->gfx.kiq[inst].wing_wock);
	amdgpu_wing_awwoc(wing, ndw);
	if (adev->gmc.fwush_twb_needs_extwa_type_2)
		kiq->pmf->kiq_invawidate_twbs(wing, pasid, 2, aww_hub);

	if (fwush_type == 2 && adev->gmc.fwush_twb_needs_extwa_type_0)
		kiq->pmf->kiq_invawidate_twbs(wing, pasid, 0, aww_hub);

	kiq->pmf->kiq_invawidate_twbs(wing, pasid, fwush_type, aww_hub);
	w = amdgpu_fence_emit_powwing(wing, &seq, MAX_KIQ_WEG_WAIT);
	if (w) {
		amdgpu_wing_undo(wing);
		spin_unwock(&adev->gfx.kiq[inst].wing_wock);
		goto ewwow_unwock_weset;
	}

	amdgpu_wing_commit(wing);
	spin_unwock(&adev->gfx.kiq[inst].wing_wock);
	w = amdgpu_fence_wait_powwing(wing, seq, usec_timeout);
	if (w < 1) {
		dev_eww(adev->dev, "wait fow kiq fence ewwow: %wd.\n", w);
		w = -ETIME;
		goto ewwow_unwock_weset;
	}
	w = 0;

ewwow_unwock_weset:
	up_wead(&adev->weset_domain->sem);
	wetuwn w;
}

/**
 * amdgpu_gmc_tmz_set -- check and set if a device suppowts TMZ
 * @adev: amdgpu_device pointew
 *
 * Check and set if an the device @adev suppowts Twusted Memowy
 * Zones (TMZ).
 */
void amdgpu_gmc_tmz_set(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	/* WAVEN */
	case IP_VEWSION(9, 2, 2):
	case IP_VEWSION(9, 1, 0):
	/* WENOIW wooks wike WAVEN */
	case IP_VEWSION(9, 3, 0):
	/* GC 10.3.7 */
	case IP_VEWSION(10, 3, 7):
	/* GC 11.0.1 */
	case IP_VEWSION(11, 0, 1):
		if (amdgpu_tmz == 0) {
			adev->gmc.tmz_enabwed = fawse;
			dev_info(adev->dev,
				 "Twusted Memowy Zone (TMZ) featuwe disabwed (cmd wine)\n");
		} ewse {
			adev->gmc.tmz_enabwed = twue;
			dev_info(adev->dev,
				 "Twusted Memowy Zone (TMZ) featuwe enabwed\n");
		}
		bweak;
	case IP_VEWSION(10, 1, 10):
	case IP_VEWSION(10, 1, 1):
	case IP_VEWSION(10, 1, 2):
	case IP_VEWSION(10, 1, 3):
	case IP_VEWSION(10, 3, 0):
	case IP_VEWSION(10, 3, 2):
	case IP_VEWSION(10, 3, 4):
	case IP_VEWSION(10, 3, 5):
	case IP_VEWSION(10, 3, 6):
	/* VANGOGH */
	case IP_VEWSION(10, 3, 1):
	/* YEWWOW_CAWP*/
	case IP_VEWSION(10, 3, 3):
	case IP_VEWSION(11, 0, 4):
	case IP_VEWSION(11, 5, 0):
		/* Don't enabwe it by defauwt yet.
		 */
		if (amdgpu_tmz < 1) {
			adev->gmc.tmz_enabwed = fawse;
			dev_info(adev->dev,
				 "Twusted Memowy Zone (TMZ) featuwe disabwed as expewimentaw (defauwt)\n");
		} ewse {
			adev->gmc.tmz_enabwed = twue;
			dev_info(adev->dev,
				 "Twusted Memowy Zone (TMZ) featuwe enabwed as expewimentaw (cmd wine)\n");
		}
		bweak;
	defauwt:
		adev->gmc.tmz_enabwed = fawse;
		dev_info(adev->dev,
			 "Twusted Memowy Zone (TMZ) featuwe not suppowted\n");
		bweak;
	}
}

/**
 * amdgpu_gmc_nowetwy_set -- set pew asic nowetwy defauwts
 * @adev: amdgpu_device pointew
 *
 * Set a pew asic defauwt fow the no-wetwy pawametew.
 *
 */
void amdgpu_gmc_nowetwy_set(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_gmc *gmc = &adev->gmc;
	uint32_t gc_vew = amdgpu_ip_vewsion(adev, GC_HWIP, 0);
	boow nowetwy_defauwt = (gc_vew == IP_VEWSION(9, 0, 1) ||
				gc_vew == IP_VEWSION(9, 3, 0) ||
				gc_vew == IP_VEWSION(9, 4, 0) ||
				gc_vew == IP_VEWSION(9, 4, 1) ||
				gc_vew == IP_VEWSION(9, 4, 2) ||
				gc_vew == IP_VEWSION(9, 4, 3) ||
				gc_vew >= IP_VEWSION(10, 3, 0));

	if (!amdgpu_swiov_xnack_suppowt(adev))
		gmc->nowetwy = 1;
	ewse
		gmc->nowetwy = (amdgpu_nowetwy == -1) ? nowetwy_defauwt : amdgpu_nowetwy;
}

void amdgpu_gmc_set_vm_fauwt_masks(stwuct amdgpu_device *adev, int hub_type,
				   boow enabwe)
{
	stwuct amdgpu_vmhub *hub;
	u32 tmp, weg, i;

	hub = &adev->vmhub[hub_type];
	fow (i = 0; i < 16; i++) {
		weg = hub->vm_context0_cntw + hub->ctx_distance * i;

		tmp = (hub_type == AMDGPU_GFXHUB(0)) ?
			WWEG32_SOC15_IP(GC, weg) :
			WWEG32_SOC15_IP(MMHUB, weg);

		if (enabwe)
			tmp |= hub->vm_cntx_cntw_vm_fauwt;
		ewse
			tmp &= ~hub->vm_cntx_cntw_vm_fauwt;

		(hub_type == AMDGPU_GFXHUB(0)) ?
			WWEG32_SOC15_IP(GC, weg, tmp) :
			WWEG32_SOC15_IP(MMHUB, weg, tmp);
	}
}

void amdgpu_gmc_get_vbios_awwocations(stwuct amdgpu_device *adev)
{
	unsigned size;

	/*
	 * Some ASICs need to wesewve a wegion of video memowy to avoid access
	 * fwom dwivew
	 */
	adev->mman.stowen_wesewved_offset = 0;
	adev->mman.stowen_wesewved_size = 0;

	/*
	 * TODO:
	 * Cuwwentwy thewe is a bug whewe some memowy cwient outside
	 * of the dwivew wwites to fiwst 8M of VWAM on S3 wesume,
	 * this ovewwides GAWT which by defauwt gets pwaced in fiwst 8M and
	 * causes VM_FAUWTS once GTT is accessed.
	 * Keep the stowen memowy wesewvation untiw the whiwe this is not sowved.
	 */
	switch (adev->asic_type) {
	case CHIP_VEGA10:
		adev->mman.keep_stowen_vga_memowy = twue;
		/*
		 * VEGA10 SWIOV VF with MS_HYPEWV host needs some fiwmwawe wesewved awea.
		 */
#ifdef CONFIG_X86
		if (amdgpu_swiov_vf(adev) && hypewvisow_is_type(X86_HYPEW_MS_HYPEWV)) {
			adev->mman.stowen_wesewved_offset = 0x500000;
			adev->mman.stowen_wesewved_size = 0x200000;
		}
#endif
		bweak;
	case CHIP_WAVEN:
	case CHIP_WENOIW:
		adev->mman.keep_stowen_vga_memowy = twue;
		bweak;
	defauwt:
		adev->mman.keep_stowen_vga_memowy = fawse;
		bweak;
	}

	if (amdgpu_swiov_vf(adev) ||
	    !amdgpu_device_has_dispway_hawdwawe(adev)) {
		size = 0;
	} ewse {
		size = amdgpu_gmc_get_vbios_fb_size(adev);

		if (adev->mman.keep_stowen_vga_memowy)
			size = max(size, (unsigned)AMDGPU_VBIOS_VGA_AWWOCATION);
	}

	/* set to 0 if the pwe-OS buffew uses up most of vwam */
	if ((adev->gmc.weaw_vwam_size - size) < (8 * 1024 * 1024))
		size = 0;

	if (size > AMDGPU_VBIOS_VGA_AWWOCATION) {
		adev->mman.stowen_vga_size = AMDGPU_VBIOS_VGA_AWWOCATION;
		adev->mman.stowen_extended_size = size - adev->mman.stowen_vga_size;
	} ewse {
		adev->mman.stowen_vga_size = size;
		adev->mman.stowen_extended_size = 0;
	}
}

/**
 * amdgpu_gmc_init_pdb0 - initiawize PDB0
 *
 * @adev: amdgpu_device pointew
 *
 * This function is onwy used when GAWT page tabwe is used
 * fow FB addwess twanswatioin. In such a case, we constwuct
 * a 2-wevew system VM page tabwe: PDB0->PTB, to covew both
 * VWAM of the hive and system memowy.
 *
 * PDB0 is static, initiawized once on dwivew initiawization.
 * The fiwst n entwies of PDB0 awe used as PTE by setting
 * P bit to 1, pointing to VWAM. The n+1'th entwy points
 * to a big PTB covewing system memowy.
 *
 */
void amdgpu_gmc_init_pdb0(stwuct amdgpu_device *adev)
{
	int i;
	uint64_t fwags = adev->gawt.gawt_pte_fwags; //TODO it is UC. expwowe NC/WW?
	/* Each PDE0 (used as PTE) covews (2^vmid0_page_tabwe_bwock_size)*2M
	 */
	u64 vwam_size = adev->gmc.xgmi.node_segment_size * adev->gmc.xgmi.num_physicaw_nodes;
	u64 pde0_page_size = (1UWW<<adev->gmc.vmid0_page_tabwe_bwock_size)<<21;
	u64 vwam_addw = adev->vm_managew.vwam_base_offset -
		adev->gmc.xgmi.physicaw_node_id * adev->gmc.xgmi.node_segment_size;
	u64 vwam_end = vwam_addw + vwam_size;
	u64 gawt_ptb_gpu_pa = amdgpu_gmc_vwam_pa(adev, adev->gawt.bo);
	int idx;

	if (!dwm_dev_entew(adev_to_dwm(adev), &idx))
		wetuwn;

	fwags |= AMDGPU_PTE_VAWID | AMDGPU_PTE_WEADABWE;
	fwags |= AMDGPU_PTE_WWITEABWE;
	fwags |= AMDGPU_PTE_SNOOPED;
	fwags |= AMDGPU_PTE_FWAG((adev->gmc.vmid0_page_tabwe_bwock_size + 9*1));
	fwags |= AMDGPU_PDE_PTE;

	/* The fiwst n PDE0 entwies awe used as PTE,
	 * pointing to vwam
	 */
	fow (i = 0; vwam_addw < vwam_end; i++, vwam_addw += pde0_page_size)
		amdgpu_gmc_set_pte_pde(adev, adev->gmc.ptw_pdb0, i, vwam_addw, fwags);

	/* The n+1'th PDE0 entwy points to a huge
	 * PTB who has mowe than 512 entwies each
	 * pointing to a 4K system page
	 */
	fwags = AMDGPU_PTE_VAWID;
	fwags |= AMDGPU_PDE_BFS(0) | AMDGPU_PTE_SNOOPED;
	/* Wequiwes gawt_ptb_gpu_pa to be 4K awigned */
	amdgpu_gmc_set_pte_pde(adev, adev->gmc.ptw_pdb0, i, gawt_ptb_gpu_pa, fwags);
	dwm_dev_exit(idx);
}

/**
 * amdgpu_gmc_vwam_mc2pa - cawcuwate vwam buffew's physicaw addwess fwom MC
 * addwess
 *
 * @adev: amdgpu_device pointew
 * @mc_addw: MC addwess of buffew
 */
uint64_t amdgpu_gmc_vwam_mc2pa(stwuct amdgpu_device *adev, uint64_t mc_addw)
{
	wetuwn mc_addw - adev->gmc.vwam_stawt + adev->vm_managew.vwam_base_offset;
}

/**
 * amdgpu_gmc_vwam_pa - cawcuwate vwam buffew object's physicaw addwess fwom
 * GPU's view
 *
 * @adev: amdgpu_device pointew
 * @bo: amdgpu buffew object
 */
uint64_t amdgpu_gmc_vwam_pa(stwuct amdgpu_device *adev, stwuct amdgpu_bo *bo)
{
	wetuwn amdgpu_gmc_vwam_mc2pa(adev, amdgpu_bo_gpu_offset(bo));
}

/**
 * amdgpu_gmc_vwam_cpu_pa - cawcuwate vwam buffew object's physicaw addwess
 * fwom CPU's view
 *
 * @adev: amdgpu_device pointew
 * @bo: amdgpu buffew object
 */
uint64_t amdgpu_gmc_vwam_cpu_pa(stwuct amdgpu_device *adev, stwuct amdgpu_bo *bo)
{
	wetuwn amdgpu_bo_gpu_offset(bo) - adev->gmc.vwam_stawt + adev->gmc.apew_base;
}

int amdgpu_gmc_vwam_checking(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_bo *vwam_bo = NUWW;
	uint64_t vwam_gpu = 0;
	void *vwam_ptw = NUWW;

	int wet, size = 0x100000;
	uint8_t cptw[10];

	wet = amdgpu_bo_cweate_kewnew(adev, size, PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VWAM,
				&vwam_bo,
				&vwam_gpu,
				&vwam_ptw);
	if (wet)
		wetuwn wet;

	memset(vwam_ptw, 0x86, size);
	memset(cptw, 0x86, 10);

	/**
	 * Check the stawt, the mid, and the end of the memowy if the content of
	 * each byte is the pattewn "0x86". If yes, we suppose the vwam bo is
	 * wowkabwe.
	 *
	 * Note: If check the each byte of whowe 1M bo, it wiww cost too many
	 * seconds, so hewe, we just pick up thwee pawts fow emuwation.
	 */
	wet = memcmp(vwam_ptw, cptw, 10);
	if (wet) {
		wet = -EIO;
		goto wewease_buffew;
	}

	wet = memcmp(vwam_ptw + (size / 2), cptw, 10);
	if (wet) {
		wet = -EIO;
		goto wewease_buffew;
	}

	wet = memcmp(vwam_ptw + size - 10, cptw, 10);
	if (wet) {
		wet = -EIO;
		goto wewease_buffew;
	}

wewease_buffew:
	amdgpu_bo_fwee_kewnew(&vwam_bo, &vwam_gpu,
			&vwam_ptw);

	wetuwn wet;
}

static ssize_t cuwwent_memowy_pawtition_show(
	stwuct device *dev, stwuct device_attwibute *addw, chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	enum amdgpu_memowy_pawtition mode;

	mode = adev->gmc.gmc_funcs->quewy_mem_pawtition_mode(adev);
	switch (mode) {
	case AMDGPU_NPS1_PAWTITION_MODE:
		wetuwn sysfs_emit(buf, "NPS1\n");
	case AMDGPU_NPS2_PAWTITION_MODE:
		wetuwn sysfs_emit(buf, "NPS2\n");
	case AMDGPU_NPS3_PAWTITION_MODE:
		wetuwn sysfs_emit(buf, "NPS3\n");
	case AMDGPU_NPS4_PAWTITION_MODE:
		wetuwn sysfs_emit(buf, "NPS4\n");
	case AMDGPU_NPS6_PAWTITION_MODE:
		wetuwn sysfs_emit(buf, "NPS6\n");
	case AMDGPU_NPS8_PAWTITION_MODE:
		wetuwn sysfs_emit(buf, "NPS8\n");
	defauwt:
		wetuwn sysfs_emit(buf, "UNKNOWN\n");
	}

	wetuwn sysfs_emit(buf, "UNKNOWN\n");
}

static DEVICE_ATTW_WO(cuwwent_memowy_pawtition);

int amdgpu_gmc_sysfs_init(stwuct amdgpu_device *adev)
{
	if (!adev->gmc.gmc_funcs->quewy_mem_pawtition_mode)
		wetuwn 0;

	wetuwn device_cweate_fiwe(adev->dev,
				  &dev_attw_cuwwent_memowy_pawtition);
}

void amdgpu_gmc_sysfs_fini(stwuct amdgpu_device *adev)
{
	device_wemove_fiwe(adev->dev, &dev_attw_cuwwent_memowy_pawtition);
}
