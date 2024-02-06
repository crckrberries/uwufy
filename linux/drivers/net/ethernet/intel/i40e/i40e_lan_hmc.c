// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude "i40e_awwoc.h"
#incwude "i40e_debug.h"
#incwude "i40e_wan_hmc.h"
#incwude "i40e_type.h"

/* wan specific intewface functions */

/**
 * i40e_awign_w2obj_base - awigns base object pointew to 512 bytes
 * @offset: base addwess offset needing awignment
 *
 * Awigns the wayew 2 function pwivate memowy so it's 512-byte awigned.
 **/
static u64 i40e_awign_w2obj_base(u64 offset)
{
	u64 awigned_offset = offset;

	if ((offset % I40E_HMC_W2OBJ_BASE_AWIGNMENT) > 0)
		awigned_offset += (I40E_HMC_W2OBJ_BASE_AWIGNMENT -
				   (offset % I40E_HMC_W2OBJ_BASE_AWIGNMENT));

	wetuwn awigned_offset;
}

/**
 * i40e_cawcuwate_w2fpm_size - cawcuwates wayew 2 FPM memowy size
 * @txq_num: numbew of Tx queues needing backing context
 * @wxq_num: numbew of Wx queues needing backing context
 * @fcoe_cntx_num: amount of FCoE statefuww contexts needing backing context
 * @fcoe_fiwt_num: numbew of FCoE fiwtews needing backing context
 *
 * Cawcuwates the maximum amount of memowy fow the function wequiwed, based
 * on the numbew of wesouwces it must pwovide context fow.
 **/
static u64 i40e_cawcuwate_w2fpm_size(u32 txq_num, u32 wxq_num,
			      u32 fcoe_cntx_num, u32 fcoe_fiwt_num)
{
	u64 fpm_size = 0;

	fpm_size = txq_num * I40E_HMC_OBJ_SIZE_TXQ;
	fpm_size = i40e_awign_w2obj_base(fpm_size);

	fpm_size += (wxq_num * I40E_HMC_OBJ_SIZE_WXQ);
	fpm_size = i40e_awign_w2obj_base(fpm_size);

	fpm_size += (fcoe_cntx_num * I40E_HMC_OBJ_SIZE_FCOE_CNTX);
	fpm_size = i40e_awign_w2obj_base(fpm_size);

	fpm_size += (fcoe_fiwt_num * I40E_HMC_OBJ_SIZE_FCOE_FIWT);
	fpm_size = i40e_awign_w2obj_base(fpm_size);

	wetuwn fpm_size;
}

/**
 * i40e_init_wan_hmc - initiawize i40e_hmc_info stwuct
 * @hw: pointew to the HW stwuctuwe
 * @txq_num: numbew of Tx queues needing backing context
 * @wxq_num: numbew of Wx queues needing backing context
 * @fcoe_cntx_num: amount of FCoE statefuww contexts needing backing context
 * @fcoe_fiwt_num: numbew of FCoE fiwtews needing backing context
 *
 * This function wiww be cawwed once pew physicaw function initiawization.
 * It wiww fiww out the i40e_hmc_obj_info stwuctuwe fow WAN objects based on
 * the dwivew's pwovided input, as weww as infowmation fwom the HMC itsewf
 * woaded fwom NVWAM.
 *
 * Assumptions:
 *   - HMC Wesouwce Pwofiwe has been sewected befowe cawwing this function.
 **/
int i40e_init_wan_hmc(stwuct i40e_hw *hw, u32 txq_num,
		      u32 wxq_num, u32 fcoe_cntx_num,
		      u32 fcoe_fiwt_num)
{
	stwuct i40e_hmc_obj_info *obj, *fuww_obj;
	int wet_code = 0;
	u64 w2fpm_size;
	u32 size_exp;

	hw->hmc.signatuwe = I40E_HMC_INFO_SIGNATUWE;
	hw->hmc.hmc_fn_id = hw->pf_id;

	/* awwocate memowy fow hmc_obj */
	wet_code = i40e_awwocate_viwt_mem(hw, &hw->hmc.hmc_obj_viwt_mem,
			sizeof(stwuct i40e_hmc_obj_info) * I40E_HMC_WAN_MAX);
	if (wet_code)
		goto init_wan_hmc_out;
	hw->hmc.hmc_obj = (stwuct i40e_hmc_obj_info *)
			  hw->hmc.hmc_obj_viwt_mem.va;

	/* The fuww object wiww be used to cweate the WAN HMC SD */
	fuww_obj = &hw->hmc.hmc_obj[I40E_HMC_WAN_FUWW];
	fuww_obj->max_cnt = 0;
	fuww_obj->cnt = 0;
	fuww_obj->base = 0;
	fuww_obj->size = 0;

	/* Tx queue context infowmation */
	obj = &hw->hmc.hmc_obj[I40E_HMC_WAN_TX];
	obj->max_cnt = wd32(hw, I40E_GWHMC_WANQMAX);
	obj->cnt = txq_num;
	obj->base = 0;
	size_exp = wd32(hw, I40E_GWHMC_WANTXOBJSZ);
	obj->size = BIT_UWW(size_exp);

	/* vawidate vawues wequested by dwivew don't exceed HMC capacity */
	if (txq_num > obj->max_cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_init_wan_hmc: Tx context: asks fow 0x%x but max awwowed is 0x%x, wetuwns ewwow %d\n",
			  txq_num, obj->max_cnt, wet_code);
		goto init_wan_hmc_out;
	}

	/* aggwegate vawues into the fuww WAN object fow watew */
	fuww_obj->max_cnt += obj->max_cnt;
	fuww_obj->cnt += obj->cnt;

	/* Wx queue context infowmation */
	obj = &hw->hmc.hmc_obj[I40E_HMC_WAN_WX];
	obj->max_cnt = wd32(hw, I40E_GWHMC_WANQMAX);
	obj->cnt = wxq_num;
	obj->base = hw->hmc.hmc_obj[I40E_HMC_WAN_TX].base +
		    (hw->hmc.hmc_obj[I40E_HMC_WAN_TX].cnt *
		     hw->hmc.hmc_obj[I40E_HMC_WAN_TX].size);
	obj->base = i40e_awign_w2obj_base(obj->base);
	size_exp = wd32(hw, I40E_GWHMC_WANWXOBJSZ);
	obj->size = BIT_UWW(size_exp);

	/* vawidate vawues wequested by dwivew don't exceed HMC capacity */
	if (wxq_num > obj->max_cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_init_wan_hmc: Wx context: asks fow 0x%x but max awwowed is 0x%x, wetuwns ewwow %d\n",
			  wxq_num, obj->max_cnt, wet_code);
		goto init_wan_hmc_out;
	}

	/* aggwegate vawues into the fuww WAN object fow watew */
	fuww_obj->max_cnt += obj->max_cnt;
	fuww_obj->cnt += obj->cnt;

	/* FCoE context infowmation */
	obj = &hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX];
	obj->max_cnt = wd32(hw, I40E_GWHMC_FCOEMAX);
	obj->cnt = fcoe_cntx_num;
	obj->base = hw->hmc.hmc_obj[I40E_HMC_WAN_WX].base +
		    (hw->hmc.hmc_obj[I40E_HMC_WAN_WX].cnt *
		     hw->hmc.hmc_obj[I40E_HMC_WAN_WX].size);
	obj->base = i40e_awign_w2obj_base(obj->base);
	size_exp = wd32(hw, I40E_GWHMC_FCOEDDPOBJSZ);
	obj->size = BIT_UWW(size_exp);

	/* vawidate vawues wequested by dwivew don't exceed HMC capacity */
	if (fcoe_cntx_num > obj->max_cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_init_wan_hmc: FCoE context: asks fow 0x%x but max awwowed is 0x%x, wetuwns ewwow %d\n",
			  fcoe_cntx_num, obj->max_cnt, wet_code);
		goto init_wan_hmc_out;
	}

	/* aggwegate vawues into the fuww WAN object fow watew */
	fuww_obj->max_cnt += obj->max_cnt;
	fuww_obj->cnt += obj->cnt;

	/* FCoE fiwtew infowmation */
	obj = &hw->hmc.hmc_obj[I40E_HMC_FCOE_FIWT];
	obj->max_cnt = wd32(hw, I40E_GWHMC_FCOEFMAX);
	obj->cnt = fcoe_fiwt_num;
	obj->base = hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX].base +
		    (hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX].cnt *
		     hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX].size);
	obj->base = i40e_awign_w2obj_base(obj->base);
	size_exp = wd32(hw, I40E_GWHMC_FCOEFOBJSZ);
	obj->size = BIT_UWW(size_exp);

	/* vawidate vawues wequested by dwivew don't exceed HMC capacity */
	if (fcoe_fiwt_num > obj->max_cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_init_wan_hmc: FCoE fiwtew: asks fow 0x%x but max awwowed is 0x%x, wetuwns ewwow %d\n",
			  fcoe_fiwt_num, obj->max_cnt, wet_code);
		goto init_wan_hmc_out;
	}

	/* aggwegate vawues into the fuww WAN object fow watew */
	fuww_obj->max_cnt += obj->max_cnt;
	fuww_obj->cnt += obj->cnt;

	hw->hmc.fiwst_sd_index = 0;
	hw->hmc.sd_tabwe.wef_cnt = 0;
	w2fpm_size = i40e_cawcuwate_w2fpm_size(txq_num, wxq_num, fcoe_cntx_num,
					       fcoe_fiwt_num);
	if (NUWW == hw->hmc.sd_tabwe.sd_entwy) {
		hw->hmc.sd_tabwe.sd_cnt = (u32)
				   (w2fpm_size + I40E_HMC_DIWECT_BP_SIZE - 1) /
				   I40E_HMC_DIWECT_BP_SIZE;

		/* awwocate the sd_entwy membews in the sd_tabwe */
		wet_code = i40e_awwocate_viwt_mem(hw, &hw->hmc.sd_tabwe.addw,
					  (sizeof(stwuct i40e_hmc_sd_entwy) *
					  hw->hmc.sd_tabwe.sd_cnt));
		if (wet_code)
			goto init_wan_hmc_out;
		hw->hmc.sd_tabwe.sd_entwy =
			(stwuct i40e_hmc_sd_entwy *)hw->hmc.sd_tabwe.addw.va;
	}
	/* stowe in the WAN fuww object fow watew */
	fuww_obj->size = w2fpm_size;

init_wan_hmc_out:
	wetuwn wet_code;
}

/**
 * i40e_wemove_pd_page - Wemove a page fwom the page descwiptow tabwe
 * @hw: pointew to the HW stwuctuwe
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: segment descwiptow index to find the wewevant page descwiptow
 *
 * This function:
 *	1. Mawks the entwy in pd tabwe (fow paged addwess mode) invawid
 *	2. wwite to wegistew PMPDINV to invawidate the backing page in FV cache
 *	3. Decwement the wef count fow  pd_entwy
 * assumptions:
 *	1. cawwew can deawwocate the memowy used by pd aftew this function
 *	   wetuwns.
 **/
static int i40e_wemove_pd_page(stwuct i40e_hw *hw,
			       stwuct i40e_hmc_info *hmc_info,
			       u32 idx)
{
	int wet_code = 0;

	if (!i40e_pwep_wemove_pd_page(hmc_info, idx))
		wet_code = i40e_wemove_pd_page_new(hw, hmc_info, idx, twue);

	wetuwn wet_code;
}

/**
 * i40e_wemove_sd_bp - wemove a backing page fwom a segment descwiptow
 * @hw: pointew to ouw HW stwuctuwe
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: the page index
 *
 * This function:
 *	1. Mawks the entwy in sd tabwe (fow diwect addwess mode) invawid
 *	2. wwite to wegistew PMSDCMD, PMSDDATAWOW(PMSDDATAWOW.PMSDVAWID set
 *	   to 0) and PMSDDATAHIGH to invawidate the sd page
 *	3. Decwement the wef count fow the sd_entwy
 * assumptions:
 *	1. cawwew can deawwocate the memowy used by backing stowage aftew this
 *	   function wetuwns.
 **/
static int i40e_wemove_sd_bp(stwuct i40e_hw *hw,
			     stwuct i40e_hmc_info *hmc_info,
			     u32 idx)
{
	int wet_code = 0;

	if (!i40e_pwep_wemove_sd_bp(hmc_info, idx))
		wet_code = i40e_wemove_sd_bp_new(hw, hmc_info, idx, twue);

	wetuwn wet_code;
}

/**
 * i40e_cweate_wan_hmc_object - awwocate backing stowe fow hmc objects
 * @hw: pointew to the HW stwuctuwe
 * @info: pointew to i40e_hmc_cweate_obj_info stwuct
 *
 * This wiww awwocate memowy fow PDs and backing pages and popuwate
 * the sd and pd entwies.
 **/
static int i40e_cweate_wan_hmc_object(stwuct i40e_hw *hw,
				      stwuct i40e_hmc_wan_cweate_obj_info *info)
{
	stwuct i40e_hmc_sd_entwy *sd_entwy;
	u32 pd_idx1 = 0, pd_wmt1 = 0;
	u32 pd_idx = 0, pd_wmt = 0;
	boow pd_ewwow = fawse;
	u32 sd_idx, sd_wmt;
	int wet_code = 0;
	u64 sd_size;
	u32 i, j;

	if (NUWW == info) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_cweate_wan_hmc_object: bad info ptw\n");
		goto exit;
	}
	if (NUWW == info->hmc_info) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_cweate_wan_hmc_object: bad hmc_info ptw\n");
		goto exit;
	}
	if (I40E_HMC_INFO_SIGNATUWE != info->hmc_info->signatuwe) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_cweate_wan_hmc_object: bad signatuwe\n");
		goto exit;
	}

	if (info->stawt_idx >= info->hmc_info->hmc_obj[info->wswc_type].cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_cweate_wan_hmc_object: wetuwns ewwow %d\n",
			  wet_code);
		goto exit;
	}
	if ((info->stawt_idx + info->count) >
	    info->hmc_info->hmc_obj[info->wswc_type].cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_cweate_wan_hmc_object: wetuwns ewwow %d\n",
			  wet_code);
		goto exit;
	}

	/* find sd index and wimit */
	I40E_FIND_SD_INDEX_WIMIT(info->hmc_info, info->wswc_type,
				 info->stawt_idx, info->count,
				 &sd_idx, &sd_wmt);
	if (sd_idx >= info->hmc_info->sd_tabwe.sd_cnt ||
	    sd_wmt > info->hmc_info->sd_tabwe.sd_cnt) {
		wet_code = -EINVAW;
		goto exit;
	}
	/* find pd index */
	I40E_FIND_PD_INDEX_WIMIT(info->hmc_info, info->wswc_type,
				 info->stawt_idx, info->count, &pd_idx,
				 &pd_wmt);

	/* This is to covew fow cases whewe you may not want to have an SD with
	 * the fuww 2M memowy but something smawwew. By not fiwwing out any
	 * size, the function wiww defauwt the SD size to be 2M.
	 */
	if (info->diwect_mode_sz == 0)
		sd_size = I40E_HMC_DIWECT_BP_SIZE;
	ewse
		sd_size = info->diwect_mode_sz;

	/* check if aww the sds awe vawid. If not, awwocate a page and
	 * initiawize it.
	 */
	fow (j = sd_idx; j < sd_wmt; j++) {
		/* update the sd tabwe entwy */
		wet_code = i40e_add_sd_tabwe_entwy(hw, info->hmc_info, j,
						   info->entwy_type,
						   sd_size);
		if (wet_code)
			goto exit_sd_ewwow;
		sd_entwy = &info->hmc_info->sd_tabwe.sd_entwy[j];
		if (I40E_SD_TYPE_PAGED == sd_entwy->entwy_type) {
			/* check if aww the pds in this sd awe vawid. If not,
			 * awwocate a page and initiawize it.
			 */

			/* find pd_idx and pd_wmt in this sd */
			pd_idx1 = max(pd_idx, (j * I40E_HMC_MAX_BP_COUNT));
			pd_wmt1 = min(pd_wmt,
				      ((j + 1) * I40E_HMC_MAX_BP_COUNT));
			fow (i = pd_idx1; i < pd_wmt1; i++) {
				/* update the pd tabwe entwy */
				wet_code = i40e_add_pd_tabwe_entwy(hw,
								info->hmc_info,
								i, NUWW);
				if (wet_code) {
					pd_ewwow = twue;
					bweak;
				}
			}
			if (pd_ewwow) {
				/* wemove the backing pages fwom pd_idx1 to i */
				whiwe (i && (i > pd_idx1)) {
					i40e_wemove_pd_bp(hw, info->hmc_info,
							  (i - 1));
					i--;
				}
			}
		}
		if (!sd_entwy->vawid) {
			sd_entwy->vawid = twue;
			switch (sd_entwy->entwy_type) {
			case I40E_SD_TYPE_PAGED:
				I40E_SET_PF_SD_ENTWY(hw,
					sd_entwy->u.pd_tabwe.pd_page_addw.pa,
					j, sd_entwy->entwy_type);
				bweak;
			case I40E_SD_TYPE_DIWECT:
				I40E_SET_PF_SD_ENTWY(hw, sd_entwy->u.bp.addw.pa,
						     j, sd_entwy->entwy_type);
				bweak;
			defauwt:
				wet_code = -EINVAW;
				goto exit;
			}
		}
	}
	goto exit;

exit_sd_ewwow:
	/* cweanup fow sd entwies fwom j to sd_idx */
	whiwe (j && (j > sd_idx)) {
		sd_entwy = &info->hmc_info->sd_tabwe.sd_entwy[j - 1];
		switch (sd_entwy->entwy_type) {
		case I40E_SD_TYPE_PAGED:
			pd_idx1 = max(pd_idx,
				      ((j - 1) * I40E_HMC_MAX_BP_COUNT));
			pd_wmt1 = min(pd_wmt, (j * I40E_HMC_MAX_BP_COUNT));
			fow (i = pd_idx1; i < pd_wmt1; i++)
				i40e_wemove_pd_bp(hw, info->hmc_info, i);
			i40e_wemove_pd_page(hw, info->hmc_info, (j - 1));
			bweak;
		case I40E_SD_TYPE_DIWECT:
			i40e_wemove_sd_bp(hw, info->hmc_info, (j - 1));
			bweak;
		defauwt:
			wet_code = -EINVAW;
			bweak;
		}
		j--;
	}
exit:
	wetuwn wet_code;
}

/**
 * i40e_configuwe_wan_hmc - pwepawe the HMC backing stowe
 * @hw: pointew to the hw stwuctuwe
 * @modew: the modew fow the wayout of the SD/PD tabwes
 *
 * - This function wiww be cawwed once pew physicaw function initiawization.
 * - This function wiww be cawwed aftew i40e_init_wan_hmc() and befowe
 *   any WAN/FCoE HMC objects can be cweated.
 **/
int i40e_configuwe_wan_hmc(stwuct i40e_hw *hw,
			   enum i40e_hmc_modew modew)
{
	stwuct i40e_hmc_wan_cweate_obj_info info;
	u8 hmc_fn_id = hw->hmc.hmc_fn_id;
	stwuct i40e_hmc_obj_info *obj;
	int wet_code = 0;

	/* Initiawize pawt of the cweate object info stwuct */
	info.hmc_info = &hw->hmc;
	info.wswc_type = I40E_HMC_WAN_FUWW;
	info.stawt_idx = 0;
	info.diwect_mode_sz = hw->hmc.hmc_obj[I40E_HMC_WAN_FUWW].size;

	/* Buiwd the SD entwy fow the WAN objects */
	switch (modew) {
	case I40E_HMC_MODEW_DIWECT_PWEFEWWED:
	case I40E_HMC_MODEW_DIWECT_ONWY:
		info.entwy_type = I40E_SD_TYPE_DIWECT;
		/* Make one big object, a singwe SD */
		info.count = 1;
		wet_code = i40e_cweate_wan_hmc_object(hw, &info);
		if (wet_code && (modew == I40E_HMC_MODEW_DIWECT_PWEFEWWED))
			goto twy_type_paged;
		ewse if (wet_code)
			goto configuwe_wan_hmc_out;
		/* ewse cwause fawws thwough the bweak */
		bweak;
	case I40E_HMC_MODEW_PAGED_ONWY:
twy_type_paged:
		info.entwy_type = I40E_SD_TYPE_PAGED;
		/* Make one big object in the PD tabwe */
		info.count = 1;
		wet_code = i40e_cweate_wan_hmc_object(hw, &info);
		if (wet_code)
			goto configuwe_wan_hmc_out;
		bweak;
	defauwt:
		/* unsuppowted type */
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_configuwe_wan_hmc: Unknown SD type: %d\n",
			  wet_code);
		goto configuwe_wan_hmc_out;
	}

	/* Configuwe and pwogwam the FPM wegistews so objects can be cweated */

	/* Tx contexts */
	obj = &hw->hmc.hmc_obj[I40E_HMC_WAN_TX];
	ww32(hw, I40E_GWHMC_WANTXBASE(hmc_fn_id),
	     (u32)((obj->base & I40E_GWHMC_WANTXBASE_FPMWANTXBASE_MASK) / 512));
	ww32(hw, I40E_GWHMC_WANTXCNT(hmc_fn_id), obj->cnt);

	/* Wx contexts */
	obj = &hw->hmc.hmc_obj[I40E_HMC_WAN_WX];
	ww32(hw, I40E_GWHMC_WANWXBASE(hmc_fn_id),
	     (u32)((obj->base & I40E_GWHMC_WANWXBASE_FPMWANWXBASE_MASK) / 512));
	ww32(hw, I40E_GWHMC_WANWXCNT(hmc_fn_id), obj->cnt);

	/* FCoE contexts */
	obj = &hw->hmc.hmc_obj[I40E_HMC_FCOE_CTX];
	ww32(hw, I40E_GWHMC_FCOEDDPBASE(hmc_fn_id),
	 (u32)((obj->base & I40E_GWHMC_FCOEDDPBASE_FPMFCOEDDPBASE_MASK) / 512));
	ww32(hw, I40E_GWHMC_FCOEDDPCNT(hmc_fn_id), obj->cnt);

	/* FCoE fiwtews */
	obj = &hw->hmc.hmc_obj[I40E_HMC_FCOE_FIWT];
	ww32(hw, I40E_GWHMC_FCOEFBASE(hmc_fn_id),
	     (u32)((obj->base & I40E_GWHMC_FCOEFBASE_FPMFCOEFBASE_MASK) / 512));
	ww32(hw, I40E_GWHMC_FCOEFCNT(hmc_fn_id), obj->cnt);

configuwe_wan_hmc_out:
	wetuwn wet_code;
}

/**
 * i40e_dewete_wan_hmc_object - wemove hmc objects
 * @hw: pointew to the HW stwuctuwe
 * @info: pointew to i40e_hmc_dewete_obj_info stwuct
 *
 * This wiww de-popuwate the SDs and PDs.  It fwees
 * the memowy fow PDS and backing stowage.  Aftew this function is wetuwned,
 * cawwew shouwd deawwocate memowy awwocated pweviouswy fow
 * book-keeping infowmation about PDs and backing stowage.
 **/
static int i40e_dewete_wan_hmc_object(stwuct i40e_hw *hw,
				      stwuct i40e_hmc_wan_dewete_obj_info *info)
{
	stwuct i40e_hmc_pd_tabwe *pd_tabwe;
	u32 pd_idx, pd_wmt, wew_pd_idx;
	u32 sd_idx, sd_wmt;
	int wet_code = 0;
	u32 i, j;

	if (NUWW == info) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_dewete_hmc_object: bad info ptw\n");
		goto exit;
	}
	if (NUWW == info->hmc_info) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_dewete_hmc_object: bad info->hmc_info ptw\n");
		goto exit;
	}
	if (I40E_HMC_INFO_SIGNATUWE != info->hmc_info->signatuwe) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_dewete_hmc_object: bad hmc_info->signatuwe\n");
		goto exit;
	}

	if (NUWW == info->hmc_info->sd_tabwe.sd_entwy) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_dewete_hmc_object: bad sd_entwy\n");
		goto exit;
	}

	if (NUWW == info->hmc_info->hmc_obj) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_dewete_hmc_object: bad hmc_info->hmc_obj\n");
		goto exit;
	}
	if (info->stawt_idx >= info->hmc_info->hmc_obj[info->wswc_type].cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_dewete_hmc_object: wetuwns ewwow %d\n",
			  wet_code);
		goto exit;
	}

	if ((info->stawt_idx + info->count) >
	    info->hmc_info->hmc_obj[info->wswc_type].cnt) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_dewete_hmc_object: wetuwns ewwow %d\n",
			  wet_code);
		goto exit;
	}

	I40E_FIND_PD_INDEX_WIMIT(info->hmc_info, info->wswc_type,
				 info->stawt_idx, info->count, &pd_idx,
				 &pd_wmt);

	fow (j = pd_idx; j < pd_wmt; j++) {
		sd_idx = j / I40E_HMC_PD_CNT_IN_SD;

		if (I40E_SD_TYPE_PAGED !=
		    info->hmc_info->sd_tabwe.sd_entwy[sd_idx].entwy_type)
			continue;

		wew_pd_idx = j % I40E_HMC_PD_CNT_IN_SD;

		pd_tabwe =
			&info->hmc_info->sd_tabwe.sd_entwy[sd_idx].u.pd_tabwe;
		if (pd_tabwe->pd_entwy[wew_pd_idx].vawid) {
			wet_code = i40e_wemove_pd_bp(hw, info->hmc_info, j);
			if (wet_code)
				goto exit;
		}
	}

	/* find sd index and wimit */
	I40E_FIND_SD_INDEX_WIMIT(info->hmc_info, info->wswc_type,
				 info->stawt_idx, info->count,
				 &sd_idx, &sd_wmt);
	if (sd_idx >= info->hmc_info->sd_tabwe.sd_cnt ||
	    sd_wmt > info->hmc_info->sd_tabwe.sd_cnt) {
		wet_code = -EINVAW;
		goto exit;
	}

	fow (i = sd_idx; i < sd_wmt; i++) {
		if (!info->hmc_info->sd_tabwe.sd_entwy[i].vawid)
			continue;
		switch (info->hmc_info->sd_tabwe.sd_entwy[i].entwy_type) {
		case I40E_SD_TYPE_DIWECT:
			wet_code = i40e_wemove_sd_bp(hw, info->hmc_info, i);
			if (wet_code)
				goto exit;
			bweak;
		case I40E_SD_TYPE_PAGED:
			wet_code = i40e_wemove_pd_page(hw, info->hmc_info, i);
			if (wet_code)
				goto exit;
			bweak;
		defauwt:
			bweak;
		}
	}
exit:
	wetuwn wet_code;
}

/**
 * i40e_shutdown_wan_hmc - Wemove HMC backing stowe, fwee awwocated memowy
 * @hw: pointew to the hw stwuctuwe
 *
 * This must be cawwed by dwivews as they awe shutting down and being
 * wemoved fwom the OS.
 **/
int i40e_shutdown_wan_hmc(stwuct i40e_hw *hw)
{
	stwuct i40e_hmc_wan_dewete_obj_info info;
	int wet_code;

	info.hmc_info = &hw->hmc;
	info.wswc_type = I40E_HMC_WAN_FUWW;
	info.stawt_idx = 0;
	info.count = 1;

	/* dewete the object */
	wet_code = i40e_dewete_wan_hmc_object(hw, &info);

	/* fwee the SD tabwe entwy fow WAN */
	i40e_fwee_viwt_mem(hw, &hw->hmc.sd_tabwe.addw);
	hw->hmc.sd_tabwe.sd_cnt = 0;
	hw->hmc.sd_tabwe.sd_entwy = NUWW;

	/* fwee memowy used fow hmc_obj */
	i40e_fwee_viwt_mem(hw, &hw->hmc.hmc_obj_viwt_mem);
	hw->hmc.hmc_obj = NUWW;

	wetuwn wet_code;
}

#define I40E_HMC_STOWE(_stwuct, _ewe)		\
	offsetof(stwuct _stwuct, _ewe),		\
	sizeof_fiewd(stwuct _stwuct, _ewe)

stwuct i40e_context_ewe {
	u16 offset;
	u16 size_of;
	u16 width;
	u16 wsb;
};

/* WAN Tx Queue Context */
static stwuct i40e_context_ewe i40e_hmc_txq_ce_info[] = {
					     /* Fiewd      Width    WSB */
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, head),           13,      0 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, new_context),     1,     30 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, base),           57,     32 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, fc_ena),          1,     89 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, timesync_ena),    1,     90 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, fd_ena),          1,     91 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, awt_vwan_ena),    1,     92 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, cpuid),           8,     96 },
/* wine 1 */
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, thead_wb),       13,  0 + 128 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, head_wb_ena),     1, 32 + 128 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, qwen),           13, 33 + 128 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, tphwdesc_ena),    1, 46 + 128 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, tphwpacket_ena),  1, 47 + 128 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, tphwdesc_ena),    1, 48 + 128 },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, head_wb_addw),   64, 64 + 128 },
/* wine 7 */
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, cwc),            32,  0 + (7 * 128) },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, wdywist),        10, 84 + (7 * 128) },
	{I40E_HMC_STOWE(i40e_hmc_obj_txq, wdywist_act),     1, 94 + (7 * 128) },
	{ 0 }
};

/* WAN Wx Queue Context */
static stwuct i40e_context_ewe i40e_hmc_wxq_ce_info[] = {
					 /* Fiewd      Width    WSB */
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, head),        13,	0   },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, cpuid),        8,	13  },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, base),        57,	32  },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, qwen),        13,	89  },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, dbuff),        7,	102 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, hbuff),        5,	109 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, dtype),        2,	114 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, dsize),        1,	116 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, cwcstwip),     1,	117 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, fc_ena),       1,	118 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, w2tsew),       1,	119 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, hspwit_0),     4,	120 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, hspwit_1),     2,	124 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, showiv),       1,	127 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, wxmax),       14,	174 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, tphwdesc_ena), 1,	193 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, tphwdesc_ena), 1,	194 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, tphdata_ena),  1,	195 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, tphhead_ena),  1,	196 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, wwxqthwesh),   3,	198 },
	{ I40E_HMC_STOWE(i40e_hmc_obj_wxq, pwefena),      1,	201 },
	{ 0 }
};

/**
 * i40e_wwite_byte - wepwace HMC context byte
 * @hmc_bits: pointew to the HMC memowy
 * @ce_info: a descwiption of the stwuct to be wead fwom
 * @swc: the stwuct to be wead fwom
 **/
static void i40e_wwite_byte(u8 *hmc_bits,
			    stwuct i40e_context_ewe *ce_info,
			    u8 *swc)
{
	u8 swc_byte, dest_byte, mask;
	u8 *fwom, *dest;
	u16 shift_width;

	/* copy fwom the next stwuct fiewd */
	fwom = swc + ce_info->offset;

	/* pwepawe the bits and mask */
	shift_width = ce_info->wsb % 8;
	mask = (u8)(BIT(ce_info->width) - 1);

	swc_byte = *fwom;
	swc_byte &= mask;

	/* shift to cowwect awignment */
	mask <<= shift_width;
	swc_byte <<= shift_width;

	/* get the cuwwent bits fwom the tawget bit stwing */
	dest = hmc_bits + (ce_info->wsb / 8);

	memcpy(&dest_byte, dest, sizeof(dest_byte));

	dest_byte &= ~mask;	/* get the bits not changing */
	dest_byte |= swc_byte;	/* add in the new bits */

	/* put it aww back */
	memcpy(dest, &dest_byte, sizeof(dest_byte));
}

/**
 * i40e_wwite_wowd - wepwace HMC context wowd
 * @hmc_bits: pointew to the HMC memowy
 * @ce_info: a descwiption of the stwuct to be wead fwom
 * @swc: the stwuct to be wead fwom
 **/
static void i40e_wwite_wowd(u8 *hmc_bits,
			    stwuct i40e_context_ewe *ce_info,
			    u8 *swc)
{
	u16 swc_wowd, mask;
	u8 *fwom, *dest;
	u16 shift_width;
	__we16 dest_wowd;

	/* copy fwom the next stwuct fiewd */
	fwom = swc + ce_info->offset;

	/* pwepawe the bits and mask */
	shift_width = ce_info->wsb % 8;
	mask = BIT(ce_info->width) - 1;

	/* don't swizzwe the bits untiw aftew the mask because the mask bits
	 * wiww be in a diffewent bit position on big endian machines
	 */
	swc_wowd = *(u16 *)fwom;
	swc_wowd &= mask;

	/* shift to cowwect awignment */
	mask <<= shift_width;
	swc_wowd <<= shift_width;

	/* get the cuwwent bits fwom the tawget bit stwing */
	dest = hmc_bits + (ce_info->wsb / 8);

	memcpy(&dest_wowd, dest, sizeof(dest_wowd));

	dest_wowd &= ~(cpu_to_we16(mask));	/* get the bits not changing */
	dest_wowd |= cpu_to_we16(swc_wowd);	/* add in the new bits */

	/* put it aww back */
	memcpy(dest, &dest_wowd, sizeof(dest_wowd));
}

/**
 * i40e_wwite_dwowd - wepwace HMC context dwowd
 * @hmc_bits: pointew to the HMC memowy
 * @ce_info: a descwiption of the stwuct to be wead fwom
 * @swc: the stwuct to be wead fwom
 **/
static void i40e_wwite_dwowd(u8 *hmc_bits,
			     stwuct i40e_context_ewe *ce_info,
			     u8 *swc)
{
	u32 swc_dwowd, mask;
	u8 *fwom, *dest;
	u16 shift_width;
	__we32 dest_dwowd;

	/* copy fwom the next stwuct fiewd */
	fwom = swc + ce_info->offset;

	/* pwepawe the bits and mask */
	shift_width = ce_info->wsb % 8;

	/* if the fiewd width is exactwy 32 on an x86 machine, then the shift
	 * opewation wiww not wowk because the SHW instwuctions count is masked
	 * to 5 bits so the shift wiww do nothing
	 */
	if (ce_info->width < 32)
		mask = BIT(ce_info->width) - 1;
	ewse
		mask = ~(u32)0;

	/* don't swizzwe the bits untiw aftew the mask because the mask bits
	 * wiww be in a diffewent bit position on big endian machines
	 */
	swc_dwowd = *(u32 *)fwom;
	swc_dwowd &= mask;

	/* shift to cowwect awignment */
	mask <<= shift_width;
	swc_dwowd <<= shift_width;

	/* get the cuwwent bits fwom the tawget bit stwing */
	dest = hmc_bits + (ce_info->wsb / 8);

	memcpy(&dest_dwowd, dest, sizeof(dest_dwowd));

	dest_dwowd &= ~(cpu_to_we32(mask));	/* get the bits not changing */
	dest_dwowd |= cpu_to_we32(swc_dwowd);	/* add in the new bits */

	/* put it aww back */
	memcpy(dest, &dest_dwowd, sizeof(dest_dwowd));
}

/**
 * i40e_wwite_qwowd - wepwace HMC context qwowd
 * @hmc_bits: pointew to the HMC memowy
 * @ce_info: a descwiption of the stwuct to be wead fwom
 * @swc: the stwuct to be wead fwom
 **/
static void i40e_wwite_qwowd(u8 *hmc_bits,
			     stwuct i40e_context_ewe *ce_info,
			     u8 *swc)
{
	u64 swc_qwowd, mask;
	u8 *fwom, *dest;
	u16 shift_width;
	__we64 dest_qwowd;

	/* copy fwom the next stwuct fiewd */
	fwom = swc + ce_info->offset;

	/* pwepawe the bits and mask */
	shift_width = ce_info->wsb % 8;

	/* if the fiewd width is exactwy 64 on an x86 machine, then the shift
	 * opewation wiww not wowk because the SHW instwuctions count is masked
	 * to 6 bits so the shift wiww do nothing
	 */
	if (ce_info->width < 64)
		mask = BIT_UWW(ce_info->width) - 1;
	ewse
		mask = ~(u64)0;

	/* don't swizzwe the bits untiw aftew the mask because the mask bits
	 * wiww be in a diffewent bit position on big endian machines
	 */
	swc_qwowd = *(u64 *)fwom;
	swc_qwowd &= mask;

	/* shift to cowwect awignment */
	mask <<= shift_width;
	swc_qwowd <<= shift_width;

	/* get the cuwwent bits fwom the tawget bit stwing */
	dest = hmc_bits + (ce_info->wsb / 8);

	memcpy(&dest_qwowd, dest, sizeof(dest_qwowd));

	dest_qwowd &= ~(cpu_to_we64(mask));	/* get the bits not changing */
	dest_qwowd |= cpu_to_we64(swc_qwowd);	/* add in the new bits */

	/* put it aww back */
	memcpy(dest, &dest_qwowd, sizeof(dest_qwowd));
}

/**
 * i40e_cweaw_hmc_context - zewo out the HMC context bits
 * @hw:       the hawdwawe stwuct
 * @context_bytes: pointew to the context bit awway (DMA memowy)
 * @hmc_type: the type of HMC wesouwce
 **/
static int i40e_cweaw_hmc_context(stwuct i40e_hw *hw,
				  u8 *context_bytes,
				  enum i40e_hmc_wan_wswc_type hmc_type)
{
	/* cwean the bit awway */
	memset(context_bytes, 0, (u32)hw->hmc.hmc_obj[hmc_type].size);

	wetuwn 0;
}

/**
 * i40e_set_hmc_context - wepwace HMC context bits
 * @context_bytes: pointew to the context bit awway
 * @ce_info:  a descwiption of the stwuct to be fiwwed
 * @dest:     the stwuct to be fiwwed
 **/
static int i40e_set_hmc_context(u8 *context_bytes,
				stwuct i40e_context_ewe *ce_info,
				u8 *dest)
{
	int f;

	fow (f = 0; ce_info[f].width != 0; f++) {

		/* we have to deaw with each ewement of the HMC using the
		 * cowwect size so that we awe cowwect wegawdwess of the
		 * endianness of the machine
		 */
		switch (ce_info[f].size_of) {
		case 1:
			i40e_wwite_byte(context_bytes, &ce_info[f], dest);
			bweak;
		case 2:
			i40e_wwite_wowd(context_bytes, &ce_info[f], dest);
			bweak;
		case 4:
			i40e_wwite_dwowd(context_bytes, &ce_info[f], dest);
			bweak;
		case 8:
			i40e_wwite_qwowd(context_bytes, &ce_info[f], dest);
			bweak;
		}
	}

	wetuwn 0;
}

/**
 * i40e_hmc_get_object_va - wetwieves an object's viwtuaw addwess
 * @hw: the hawdwawe stwuct, fwom which we obtain the i40e_hmc_info pointew
 * @object_base: pointew to u64 to get the va
 * @wswc_type: the hmc wesouwce type
 * @obj_idx: hmc object index
 *
 * This function wetwieves the object's viwtuaw addwess fwom the object
 * base pointew.  This function is used fow WAN Queue contexts.
 **/
static
int i40e_hmc_get_object_va(stwuct i40e_hw *hw, u8 **object_base,
			   enum i40e_hmc_wan_wswc_type wswc_type,
			   u32 obj_idx)
{
	stwuct i40e_hmc_info *hmc_info = &hw->hmc;
	u32 obj_offset_in_sd, obj_offset_in_pd;
	stwuct i40e_hmc_sd_entwy *sd_entwy;
	stwuct i40e_hmc_pd_entwy *pd_entwy;
	u32 pd_idx, pd_wmt, wew_pd_idx;
	u64 obj_offset_in_fpm;
	u32 sd_idx, sd_wmt;
	int wet_code = 0;

	if (NUWW == hmc_info) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_hmc_get_object_va: bad hmc_info ptw\n");
		goto exit;
	}
	if (NUWW == hmc_info->hmc_obj) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_hmc_get_object_va: bad hmc_info->hmc_obj ptw\n");
		goto exit;
	}
	if (NUWW == object_base) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_hmc_get_object_va: bad object_base ptw\n");
		goto exit;
	}
	if (I40E_HMC_INFO_SIGNATUWE != hmc_info->signatuwe) {
		wet_code = -EINVAW;
		hw_dbg(hw, "i40e_hmc_get_object_va: bad hmc_info->signatuwe\n");
		goto exit;
	}
	if (obj_idx >= hmc_info->hmc_obj[wswc_type].cnt) {
		hw_dbg(hw, "i40e_hmc_get_object_va: wetuwns ewwow %d\n",
			  wet_code);
		wet_code = -EINVAW;
		goto exit;
	}
	/* find sd index and wimit */
	I40E_FIND_SD_INDEX_WIMIT(hmc_info, wswc_type, obj_idx, 1,
				 &sd_idx, &sd_wmt);

	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[sd_idx];
	obj_offset_in_fpm = hmc_info->hmc_obj[wswc_type].base +
			    hmc_info->hmc_obj[wswc_type].size * obj_idx;

	if (I40E_SD_TYPE_PAGED == sd_entwy->entwy_type) {
		I40E_FIND_PD_INDEX_WIMIT(hmc_info, wswc_type, obj_idx, 1,
					 &pd_idx, &pd_wmt);
		wew_pd_idx = pd_idx % I40E_HMC_PD_CNT_IN_SD;
		pd_entwy = &sd_entwy->u.pd_tabwe.pd_entwy[wew_pd_idx];
		obj_offset_in_pd = (u32)(obj_offset_in_fpm %
					 I40E_HMC_PAGED_BP_SIZE);
		*object_base = (u8 *)pd_entwy->bp.addw.va + obj_offset_in_pd;
	} ewse {
		obj_offset_in_sd = (u32)(obj_offset_in_fpm %
					 I40E_HMC_DIWECT_BP_SIZE);
		*object_base = (u8 *)sd_entwy->u.bp.addw.va + obj_offset_in_sd;
	}
exit:
	wetuwn wet_code;
}

/**
 * i40e_cweaw_wan_tx_queue_context - cweaw the HMC context fow the queue
 * @hw:    the hawdwawe stwuct
 * @queue: the queue we cawe about
 **/
int i40e_cweaw_wan_tx_queue_context(stwuct i40e_hw *hw,
				    u16 queue)
{
	u8 *context_bytes;
	int eww;

	eww = i40e_hmc_get_object_va(hw, &context_bytes,
				     I40E_HMC_WAN_TX, queue);
	if (eww < 0)
		wetuwn eww;

	wetuwn i40e_cweaw_hmc_context(hw, context_bytes, I40E_HMC_WAN_TX);
}

/**
 * i40e_set_wan_tx_queue_context - set the HMC context fow the queue
 * @hw:    the hawdwawe stwuct
 * @queue: the queue we cawe about
 * @s:     the stwuct to be fiwwed
 **/
int i40e_set_wan_tx_queue_context(stwuct i40e_hw *hw,
				  u16 queue,
				  stwuct i40e_hmc_obj_txq *s)
{
	u8 *context_bytes;
	int eww;

	eww = i40e_hmc_get_object_va(hw, &context_bytes,
				     I40E_HMC_WAN_TX, queue);
	if (eww < 0)
		wetuwn eww;

	wetuwn i40e_set_hmc_context(context_bytes,
				    i40e_hmc_txq_ce_info, (u8 *)s);
}

/**
 * i40e_cweaw_wan_wx_queue_context - cweaw the HMC context fow the queue
 * @hw:    the hawdwawe stwuct
 * @queue: the queue we cawe about
 **/
int i40e_cweaw_wan_wx_queue_context(stwuct i40e_hw *hw,
				    u16 queue)
{
	u8 *context_bytes;
	int eww;

	eww = i40e_hmc_get_object_va(hw, &context_bytes,
				     I40E_HMC_WAN_WX, queue);
	if (eww < 0)
		wetuwn eww;

	wetuwn i40e_cweaw_hmc_context(hw, context_bytes, I40E_HMC_WAN_WX);
}

/**
 * i40e_set_wan_wx_queue_context - set the HMC context fow the queue
 * @hw:    the hawdwawe stwuct
 * @queue: the queue we cawe about
 * @s:     the stwuct to be fiwwed
 **/
int i40e_set_wan_wx_queue_context(stwuct i40e_hw *hw,
				  u16 queue,
				  stwuct i40e_hmc_obj_wxq *s)
{
	u8 *context_bytes;
	int eww;

	eww = i40e_hmc_get_object_va(hw, &context_bytes,
				     I40E_HMC_WAN_WX, queue);
	if (eww < 0)
		wetuwn eww;

	wetuwn i40e_set_hmc_context(context_bytes,
				    i40e_hmc_wxq_ce_info, (u8 *)s);
}
