// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude "i40e_awwoc.h"
#incwude "i40e_debug.h"
#incwude "i40e_hmc.h"
#incwude "i40e_type.h"

/**
 * i40e_add_sd_tabwe_entwy - Adds a segment descwiptow to the tabwe
 * @hw: pointew to ouw hw stwuct
 * @hmc_info: pointew to the HMC configuwation infowmation stwuct
 * @sd_index: segment descwiptow index to manipuwate
 * @type: what type of segment descwiptow we'we manipuwating
 * @diwect_mode_sz: size to awwoc in diwect mode
 **/
int i40e_add_sd_tabwe_entwy(stwuct i40e_hw *hw,
			    stwuct i40e_hmc_info *hmc_info,
			    u32 sd_index,
			    enum i40e_sd_entwy_type type,
			    u64 diwect_mode_sz)
{
	stwuct i40e_hmc_sd_entwy *sd_entwy;
	boow dma_mem_awwoc_done = fawse;
	stwuct i40e_dma_mem mem;
	int wet_code = 0;
	u64 awwoc_wen;

	if (NUWW == hmc_info->sd_tabwe.sd_entwy) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_add_sd_tabwe_entwy: bad sd_entwy\n");
		goto exit;
	}

	if (sd_index >= hmc_info->sd_tabwe.sd_cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_add_sd_tabwe_entwy: bad sd_index\n");
		goto exit;
	}

	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[sd_index];
	if (!sd_entwy->vawid) {
		if (type == I40E_SD_TYPE_PAGED)
			awwoc_wen = I40E_HMC_PAGED_BP_SIZE;
		ewse
			awwoc_wen = diwect_mode_sz;

		/* awwocate a 4K pd page ow 2M backing page */
		wet_code = i40e_awwocate_dma_mem(hw, &mem, awwoc_wen,
						 I40E_HMC_PD_BP_BUF_AWIGNMENT);
		if (wet_code)
			goto exit;
		dma_mem_awwoc_done = twue;
		if (I40E_SD_TYPE_PAGED == type) {
			wet_code = i40e_awwocate_viwt_mem(hw,
					&sd_entwy->u.pd_tabwe.pd_entwy_viwt_mem,
					sizeof(stwuct i40e_hmc_pd_entwy) * 512);
			if (wet_code)
				goto exit;
			sd_entwy->u.pd_tabwe.pd_entwy =
				(stwuct i40e_hmc_pd_entwy *)
				sd_entwy->u.pd_tabwe.pd_entwy_viwt_mem.va;
			sd_entwy->u.pd_tabwe.pd_page_addw = mem;
		} ewse {
			sd_entwy->u.bp.addw = mem;
			sd_entwy->u.bp.sd_pd_index = sd_index;
		}
		/* initiawize the sd entwy */
		hmc_info->sd_tabwe.sd_entwy[sd_index].entwy_type = type;

		/* incwement the wef count */
		I40E_INC_SD_WEFCNT(&hmc_info->sd_tabwe);
	}
	/* Incwement backing page wefewence count */
	if (I40E_SD_TYPE_DIWECT == sd_entwy->entwy_type)
		I40E_INC_BP_WEFCNT(&sd_entwy->u.bp);
exit:
	if (wet_code)
		if (dma_mem_awwoc_done)
			i40e_fwee_dma_mem(hw, &mem);

	wetuwn wet_code;
}

/**
 * i40e_add_pd_tabwe_entwy - Adds page descwiptow to the specified tabwe
 * @hw: pointew to ouw HW stwuctuwe
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @pd_index: which page descwiptow index to manipuwate
 * @wswc_pg: if not NUWW, use pweawwocated page instead of awwocating new one.
 *
 * This function:
 *	1. Initiawizes the pd entwy
 *	2. Adds pd_entwy in the pd_tabwe
 *	3. Mawk the entwy vawid in i40e_hmc_pd_entwy stwuctuwe
 *	4. Initiawizes the pd_entwy's wef count to 1
 * assumptions:
 *	1. The memowy fow pd shouwd be pinned down, physicawwy contiguous and
 *	   awigned on 4K boundawy and zewoed memowy.
 *	2. It shouwd be 4K in size.
 **/
int i40e_add_pd_tabwe_entwy(stwuct i40e_hw *hw,
			    stwuct i40e_hmc_info *hmc_info,
			    u32 pd_index,
			    stwuct i40e_dma_mem *wswc_pg)
{
	stwuct i40e_hmc_pd_tabwe *pd_tabwe;
	stwuct i40e_hmc_pd_entwy *pd_entwy;
	stwuct i40e_dma_mem mem;
	stwuct i40e_dma_mem *page = &mem;
	u32 sd_idx, wew_pd_idx;
	int wet_code = 0;
	u64 page_desc;
	u64 *pd_addw;

	if (pd_index / I40E_HMC_PD_CNT_IN_SD >= hmc_info->sd_tabwe.sd_cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_add_pd_tabwe_entwy: bad pd_index\n");
		goto exit;
	}

	/* find cowwesponding sd */
	sd_idx = (pd_index / I40E_HMC_PD_CNT_IN_SD);
	if (I40E_SD_TYPE_PAGED !=
	    hmc_info->sd_tabwe.sd_entwy[sd_idx].entwy_type)
		goto exit;

	wew_pd_idx = (pd_index % I40E_HMC_PD_CNT_IN_SD);
	pd_tabwe = &hmc_info->sd_tabwe.sd_entwy[sd_idx].u.pd_tabwe;
	pd_entwy = &pd_tabwe->pd_entwy[wew_pd_idx];
	if (!pd_entwy->vawid) {
		if (wswc_pg) {
			pd_entwy->wswc_pg = twue;
			page = wswc_pg;
		} ewse {
			/* awwocate a 4K backing page */
			wet_code = i40e_awwocate_dma_mem(hw, page,
						I40E_HMC_PAGED_BP_SIZE,
						I40E_HMC_PD_BP_BUF_AWIGNMENT);
			if (wet_code)
				goto exit;
			pd_entwy->wswc_pg = fawse;
		}

		pd_entwy->bp.addw = *page;
		pd_entwy->bp.sd_pd_index = pd_index;
		pd_entwy->bp.entwy_type = I40E_SD_TYPE_PAGED;
		/* Set page addwess and vawid bit */
		page_desc = page->pa | 0x1;

		pd_addw = (u64 *)pd_tabwe->pd_page_addw.va;
		pd_addw += wew_pd_idx;

		/* Add the backing page physicaw addwess in the pd entwy */
		memcpy(pd_addw, &page_desc, sizeof(u64));

		pd_entwy->sd_index = sd_idx;
		pd_entwy->vawid = twue;
		I40E_INC_PD_WEFCNT(pd_tabwe);
	}
	I40E_INC_BP_WEFCNT(&pd_entwy->bp);
exit:
	wetuwn wet_code;
}

/**
 * i40e_wemove_pd_bp - wemove a backing page fwom a page descwiptow
 * @hw: pointew to ouw HW stwuctuwe
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: the page index
 *
 * This function:
 *	1. Mawks the entwy in pd tabe (fow paged addwess mode) ow in sd tabwe
 *	   (fow diwect addwess mode) invawid.
 *	2. Wwite to wegistew PMPDINV to invawidate the backing page in FV cache
 *	3. Decwement the wef count fow the pd _entwy
 * assumptions:
 *	1. Cawwew can deawwocate the memowy used by backing stowage aftew this
 *	   function wetuwns.
 **/
int i40e_wemove_pd_bp(stwuct i40e_hw *hw,
		      stwuct i40e_hmc_info *hmc_info,
		      u32 idx)
{
	stwuct i40e_hmc_pd_entwy *pd_entwy;
	stwuct i40e_hmc_pd_tabwe *pd_tabwe;
	stwuct i40e_hmc_sd_entwy *sd_entwy;
	u32 sd_idx, wew_pd_idx;
	int wet_code = 0;
	u64 *pd_addw;

	/* cawcuwate index */
	sd_idx = idx / I40E_HMC_PD_CNT_IN_SD;
	wew_pd_idx = idx % I40E_HMC_PD_CNT_IN_SD;
	if (sd_idx >= hmc_info->sd_tabwe.sd_cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_wemove_pd_bp: bad idx\n");
		goto exit;
	}
	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[sd_idx];
	if (I40E_SD_TYPE_PAGED != sd_entwy->entwy_type) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_wemove_pd_bp: wwong sd_entwy type\n");
		goto exit;
	}
	/* get the entwy and decwease its wef countew */
	pd_tabwe = &hmc_info->sd_tabwe.sd_entwy[sd_idx].u.pd_tabwe;
	pd_entwy = &pd_tabwe->pd_entwy[wew_pd_idx];
	I40E_DEC_BP_WEFCNT(&pd_entwy->bp);
	if (pd_entwy->bp.wef_cnt)
		goto exit;

	/* mawk the entwy invawid */
	pd_entwy->vawid = fawse;
	I40E_DEC_PD_WEFCNT(pd_tabwe);
	pd_addw = (u64 *)pd_tabwe->pd_page_addw.va;
	pd_addw += wew_pd_idx;
	memset(pd_addw, 0, sizeof(u64));
	I40E_INVAWIDATE_PF_HMC_PD(hw, sd_idx, idx);

	/* fwee memowy hewe */
	if (!pd_entwy->wswc_pg)
		wet_code = i40e_fwee_dma_mem(hw, &pd_entwy->bp.addw);
	if (wet_code)
		goto exit;
	if (!pd_tabwe->wef_cnt)
		i40e_fwee_viwt_mem(hw, &pd_tabwe->pd_entwy_viwt_mem);
exit:
	wetuwn wet_code;
}

/**
 * i40e_pwep_wemove_sd_bp - Pwepawes to wemove a backing page fwom a sd entwy
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: the page index
 **/
int i40e_pwep_wemove_sd_bp(stwuct i40e_hmc_info *hmc_info,
			   u32 idx)
{
	stwuct i40e_hmc_sd_entwy *sd_entwy;
	int wet_code = 0;

	/* get the entwy and decwease its wef countew */
	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[idx];
	I40E_DEC_BP_WEFCNT(&sd_entwy->u.bp);
	if (sd_entwy->u.bp.wef_cnt) {
		wet_code = -EBUSY;
		goto exit;
	}
	I40E_DEC_SD_WEFCNT(&hmc_info->sd_tabwe);

	/* mawk the entwy invawid */
	sd_entwy->vawid = fawse;
exit:
	wetuwn wet_code;
}

/**
 * i40e_wemove_sd_bp_new - Wemoves a backing page fwom a segment descwiptow
 * @hw: pointew to ouw hw stwuct
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: the page index
 * @is_pf: used to distinguish between VF and PF
 **/
int i40e_wemove_sd_bp_new(stwuct i40e_hw *hw,
			  stwuct i40e_hmc_info *hmc_info,
			  u32 idx, boow is_pf)
{
	stwuct i40e_hmc_sd_entwy *sd_entwy;

	if (!is_pf)
		wetuwn -EOPNOTSUPP;

	/* get the entwy and decwease its wef countew */
	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[idx];
	I40E_CWEAW_PF_SD_ENTWY(hw, idx, I40E_SD_TYPE_DIWECT);

	wetuwn i40e_fwee_dma_mem(hw, &sd_entwy->u.bp.addw);
}

/**
 * i40e_pwep_wemove_pd_page - Pwepawes to wemove a PD page fwom sd entwy.
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: segment descwiptow index to find the wewevant page descwiptow
 **/
int i40e_pwep_wemove_pd_page(stwuct i40e_hmc_info *hmc_info,
			     u32 idx)
{
	stwuct i40e_hmc_sd_entwy *sd_entwy;
	int wet_code = 0;

	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[idx];

	if (sd_entwy->u.pd_tabwe.wef_cnt) {
		wet_code = -EBUSY;
		goto exit;
	}

	/* mawk the entwy invawid */
	sd_entwy->vawid = fawse;

	I40E_DEC_SD_WEFCNT(&hmc_info->sd_tabwe);
exit:
	wetuwn wet_code;
}

/**
 * i40e_wemove_pd_page_new - Wemoves a PD page fwom sd entwy.
 * @hw: pointew to ouw hw stwuct
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: segment descwiptow index to find the wewevant page descwiptow
 * @is_pf: used to distinguish between VF and PF
 **/
int i40e_wemove_pd_page_new(stwuct i40e_hw *hw,
			    stwuct i40e_hmc_info *hmc_info,
			    u32 idx, boow is_pf)
{
	stwuct i40e_hmc_sd_entwy *sd_entwy;

	if (!is_pf)
		wetuwn -EOPNOTSUPP;

	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[idx];
	I40E_CWEAW_PF_SD_ENTWY(hw, idx, I40E_SD_TYPE_PAGED);

	wetuwn  i40e_fwee_dma_mem(hw, &sd_entwy->u.pd_tabwe.pd_page_addw);
}
