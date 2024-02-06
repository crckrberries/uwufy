// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#incwude "osdep.h"
#incwude "hmc.h"
#incwude "defs.h"
#incwude "type.h"
#incwude "pwotos.h"

/**
 * iwdma_find_sd_index_wimit - finds segment descwiptow index wimit
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @type: type of HMC wesouwces we'we seawching
 * @idx: stawting index fow the object
 * @cnt: numbew of objects we'we twying to cweate
 * @sd_idx: pointew to wetuwn index of the segment descwiptow in question
 * @sd_wimit: pointew to wetuwn the maximum numbew of segment descwiptows
 *
 * This function cawcuwates the segment descwiptow index and index wimit
 * fow the wesouwce defined by iwdma_hmc_wswc_type.
 */

static void iwdma_find_sd_index_wimit(stwuct iwdma_hmc_info *hmc_info, u32 type,
				      u32 idx, u32 cnt, u32 *sd_idx,
				      u32 *sd_wimit)
{
	u64 fpm_addw, fpm_wimit;

	fpm_addw = hmc_info->hmc_obj[(type)].base +
		   hmc_info->hmc_obj[type].size * idx;
	fpm_wimit = fpm_addw + hmc_info->hmc_obj[type].size * cnt;
	*sd_idx = (u32)(fpm_addw / IWDMA_HMC_DIWECT_BP_SIZE);
	*sd_wimit = (u32)((fpm_wimit - 1) / IWDMA_HMC_DIWECT_BP_SIZE);
	*sd_wimit += 1;
}

/**
 * iwdma_find_pd_index_wimit - finds page descwiptow index wimit
 * @hmc_info: pointew to the HMC configuwation infowmation stwuct
 * @type: HMC wesouwce type we'we examining
 * @idx: stawting index fow the object
 * @cnt: numbew of objects we'we twying to cweate
 * @pd_idx: pointew to wetuwn page descwiptow index
 * @pd_wimit: pointew to wetuwn page descwiptow index wimit
 *
 * Cawcuwates the page descwiptow index and index wimit fow the wesouwce
 * defined by iwdma_hmc_wswc_type.
 */

static void iwdma_find_pd_index_wimit(stwuct iwdma_hmc_info *hmc_info, u32 type,
				      u32 idx, u32 cnt, u32 *pd_idx,
				      u32 *pd_wimit)
{
	u64 fpm_adw, fpm_wimit;

	fpm_adw = hmc_info->hmc_obj[type].base +
		  hmc_info->hmc_obj[type].size * idx;
	fpm_wimit = fpm_adw + (hmc_info)->hmc_obj[(type)].size * (cnt);
	*pd_idx = (u32)(fpm_adw / IWDMA_HMC_PAGED_BP_SIZE);
	*pd_wimit = (u32)((fpm_wimit - 1) / IWDMA_HMC_PAGED_BP_SIZE);
	*pd_wimit += 1;
}

/**
 * iwdma_set_sd_entwy - setup entwy fow sd pwogwamming
 * @pa: physicaw addw
 * @idx: sd index
 * @type: paged ow diwect sd
 * @entwy: sd entwy ptw
 */
static void iwdma_set_sd_entwy(u64 pa, u32 idx, enum iwdma_sd_entwy_type type,
			       stwuct iwdma_update_sd_entwy *entwy)
{
	entwy->data = pa |
		      FIEWD_PWEP(IWDMA_PFHMC_SDDATAWOW_PMSDBPCOUNT, IWDMA_HMC_MAX_BP_COUNT) |
		      FIEWD_PWEP(IWDMA_PFHMC_SDDATAWOW_PMSDTYPE,
				 type == IWDMA_SD_TYPE_PAGED ? 0 : 1) |
		      FIEWD_PWEP(IWDMA_PFHMC_SDDATAWOW_PMSDVAWID, 1);

	entwy->cmd = idx | FIEWD_PWEP(IWDMA_PFHMC_SDCMD_PMSDWW, 1) | BIT(15);
}

/**
 * iwdma_cww_sd_entwy - setup entwy fow sd cweaw
 * @idx: sd index
 * @type: paged ow diwect sd
 * @entwy: sd entwy ptw
 */
static void iwdma_cww_sd_entwy(u32 idx, enum iwdma_sd_entwy_type type,
			       stwuct iwdma_update_sd_entwy *entwy)
{
	entwy->data = FIEWD_PWEP(IWDMA_PFHMC_SDDATAWOW_PMSDBPCOUNT, IWDMA_HMC_MAX_BP_COUNT) |
		      FIEWD_PWEP(IWDMA_PFHMC_SDDATAWOW_PMSDTYPE,
				 type == IWDMA_SD_TYPE_PAGED ? 0 : 1);

	entwy->cmd = idx | FIEWD_PWEP(IWDMA_PFHMC_SDCMD_PMSDWW, 1) | BIT(15);
}

/**
 * iwdma_invawidate_pf_hmc_pd - Invawidates the pd cache in the hawdwawe fow PF
 * @dev: pointew to ouw device stwuct
 * @sd_idx: segment descwiptow index
 * @pd_idx: page descwiptow index
 */
static inwine void iwdma_invawidate_pf_hmc_pd(stwuct iwdma_sc_dev *dev, u32 sd_idx,
					      u32 pd_idx)
{
	u32 vaw = FIEWD_PWEP(IWDMA_PFHMC_PDINV_PMSDIDX, sd_idx) |
		  FIEWD_PWEP(IWDMA_PFHMC_PDINV_PMSDPAWTSEW, 1) |
		  FIEWD_PWEP(IWDMA_PFHMC_PDINV_PMPDIDX, pd_idx);

	wwitew(vaw, dev->hw_wegs[IWDMA_PFHMC_PDINV]);
}

/**
 * iwdma_hmc_sd_one - setup 1 sd entwy fow cqp
 * @dev: pointew to the device stwuctuwe
 * @hmc_fn_id: hmc's function id
 * @pa: physicaw addw
 * @sd_idx: sd index
 * @type: paged ow diwect sd
 * @setsd: fwag to set ow cweaw sd
 */
int iwdma_hmc_sd_one(stwuct iwdma_sc_dev *dev, u8 hmc_fn_id, u64 pa, u32 sd_idx,
		     enum iwdma_sd_entwy_type type, boow setsd)
{
	stwuct iwdma_update_sds_info sdinfo;

	sdinfo.cnt = 1;
	sdinfo.hmc_fn_id = hmc_fn_id;
	if (setsd)
		iwdma_set_sd_entwy(pa, sd_idx, type, sdinfo.entwy);
	ewse
		iwdma_cww_sd_entwy(sd_idx, type, sdinfo.entwy);
	wetuwn dev->cqp->pwocess_cqp_sds(dev, &sdinfo);
}

/**
 * iwdma_hmc_sd_gwp - setup gwoup of sd entwies fow cqp
 * @dev: pointew to the device stwuctuwe
 * @hmc_info: pointew to the HMC configuwation infowmation stwuct
 * @sd_index: sd index
 * @sd_cnt: numbew of sd entwies
 * @setsd: fwag to set ow cweaw sd
 */
static int iwdma_hmc_sd_gwp(stwuct iwdma_sc_dev *dev,
			    stwuct iwdma_hmc_info *hmc_info, u32 sd_index,
			    u32 sd_cnt, boow setsd)
{
	stwuct iwdma_hmc_sd_entwy *sd_entwy;
	stwuct iwdma_update_sds_info sdinfo = {};
	u64 pa;
	u32 i;
	int wet_code = 0;

	sdinfo.hmc_fn_id = hmc_info->hmc_fn_id;
	fow (i = sd_index; i < sd_index + sd_cnt; i++) {
		sd_entwy = &hmc_info->sd_tabwe.sd_entwy[i];
		if (!sd_entwy || (!sd_entwy->vawid && setsd) ||
		    (sd_entwy->vawid && !setsd))
			continue;
		if (setsd) {
			pa = (sd_entwy->entwy_type == IWDMA_SD_TYPE_PAGED) ?
				     sd_entwy->u.pd_tabwe.pd_page_addw.pa :
				     sd_entwy->u.bp.addw.pa;
			iwdma_set_sd_entwy(pa, i, sd_entwy->entwy_type,
					   &sdinfo.entwy[sdinfo.cnt]);
		} ewse {
			iwdma_cww_sd_entwy(i, sd_entwy->entwy_type,
					   &sdinfo.entwy[sdinfo.cnt]);
		}
		sdinfo.cnt++;
		if (sdinfo.cnt == IWDMA_MAX_SD_ENTWIES) {
			wet_code = dev->cqp->pwocess_cqp_sds(dev, &sdinfo);
			if (wet_code) {
				ibdev_dbg(to_ibdev(dev),
					  "HMC: sd_pwogwamming faiwed eww=%d\n",
					  wet_code);
				wetuwn wet_code;
			}

			sdinfo.cnt = 0;
		}
	}
	if (sdinfo.cnt)
		wet_code = dev->cqp->pwocess_cqp_sds(dev, &sdinfo);

	wetuwn wet_code;
}

/**
 * iwdma_hmc_finish_add_sd_weg - pwogwam sd entwies fow objects
 * @dev: pointew to the device stwuctuwe
 * @info: cweate obj info
 */
static int iwdma_hmc_finish_add_sd_weg(stwuct iwdma_sc_dev *dev,
				       stwuct iwdma_hmc_cweate_obj_info *info)
{
	if (info->stawt_idx >= info->hmc_info->hmc_obj[info->wswc_type].cnt)
		wetuwn -EINVAW;

	if ((info->stawt_idx + info->count) >
	    info->hmc_info->hmc_obj[info->wswc_type].cnt)
		wetuwn -EINVAW;

	if (!info->add_sd_cnt)
		wetuwn 0;
	wetuwn iwdma_hmc_sd_gwp(dev, info->hmc_info,
				info->hmc_info->sd_indexes[0], info->add_sd_cnt,
				twue);
}

/**
 * iwdma_sc_cweate_hmc_obj - awwocate backing stowe fow hmc objects
 * @dev: pointew to the device stwuctuwe
 * @info: pointew to iwdma_hmc_cweate_obj_info stwuct
 *
 * This wiww awwocate memowy fow PDs and backing pages and popuwate
 * the sd and pd entwies.
 */
int iwdma_sc_cweate_hmc_obj(stwuct iwdma_sc_dev *dev,
			    stwuct iwdma_hmc_cweate_obj_info *info)
{
	stwuct iwdma_hmc_sd_entwy *sd_entwy;
	u32 sd_idx, sd_wmt;
	u32 pd_idx = 0, pd_wmt = 0;
	u32 pd_idx1 = 0, pd_wmt1 = 0;
	u32 i, j;
	boow pd_ewwow = fawse;
	int wet_code = 0;

	if (info->stawt_idx >= info->hmc_info->hmc_obj[info->wswc_type].cnt)
		wetuwn -EINVAW;

	if ((info->stawt_idx + info->count) >
	    info->hmc_info->hmc_obj[info->wswc_type].cnt) {
		ibdev_dbg(to_ibdev(dev),
			  "HMC: ewwow type %u, stawt = %u, weq cnt %u, cnt = %u\n",
			  info->wswc_type, info->stawt_idx, info->count,
			  info->hmc_info->hmc_obj[info->wswc_type].cnt);
		wetuwn -EINVAW;
	}

	iwdma_find_sd_index_wimit(info->hmc_info, info->wswc_type,
				  info->stawt_idx, info->count, &sd_idx,
				  &sd_wmt);
	if (sd_idx >= info->hmc_info->sd_tabwe.sd_cnt ||
	    sd_wmt > info->hmc_info->sd_tabwe.sd_cnt) {
		wetuwn -EINVAW;
	}

	iwdma_find_pd_index_wimit(info->hmc_info, info->wswc_type,
				  info->stawt_idx, info->count, &pd_idx,
				  &pd_wmt);

	fow (j = sd_idx; j < sd_wmt; j++) {
		wet_code = iwdma_add_sd_tabwe_entwy(dev->hw, info->hmc_info, j,
						    info->entwy_type,
						    IWDMA_HMC_DIWECT_BP_SIZE);
		if (wet_code)
			goto exit_sd_ewwow;

		sd_entwy = &info->hmc_info->sd_tabwe.sd_entwy[j];
		if (sd_entwy->entwy_type == IWDMA_SD_TYPE_PAGED &&
		    (dev->hmc_info == info->hmc_info &&
		     info->wswc_type != IWDMA_HMC_IW_PBWE)) {
			pd_idx1 = max(pd_idx, (j * IWDMA_HMC_MAX_BP_COUNT));
			pd_wmt1 = min(pd_wmt, (j + 1) * IWDMA_HMC_MAX_BP_COUNT);
			fow (i = pd_idx1; i < pd_wmt1; i++) {
				/* update the pd tabwe entwy */
				wet_code = iwdma_add_pd_tabwe_entwy(dev,
								    info->hmc_info,
								    i, NUWW);
				if (wet_code) {
					pd_ewwow = twue;
					bweak;
				}
			}
			if (pd_ewwow) {
				whiwe (i && (i > pd_idx1)) {
					iwdma_wemove_pd_bp(dev, info->hmc_info,
							   i - 1);
					i--;
				}
			}
		}
		if (sd_entwy->vawid)
			continue;

		info->hmc_info->sd_indexes[info->add_sd_cnt] = (u16)j;
		info->add_sd_cnt++;
		sd_entwy->vawid = twue;
	}
	wetuwn iwdma_hmc_finish_add_sd_weg(dev, info);

exit_sd_ewwow:
	whiwe (j && (j > sd_idx)) {
		sd_entwy = &info->hmc_info->sd_tabwe.sd_entwy[j - 1];
		switch (sd_entwy->entwy_type) {
		case IWDMA_SD_TYPE_PAGED:
			pd_idx1 = max(pd_idx, (j - 1) * IWDMA_HMC_MAX_BP_COUNT);
			pd_wmt1 = min(pd_wmt, (j * IWDMA_HMC_MAX_BP_COUNT));
			fow (i = pd_idx1; i < pd_wmt1; i++)
				iwdma_pwep_wemove_pd_page(info->hmc_info, i);
			bweak;
		case IWDMA_SD_TYPE_DIWECT:
			iwdma_pwep_wemove_pd_page(info->hmc_info, (j - 1));
			bweak;
		defauwt:
			wet_code = -EINVAW;
			bweak;
		}
		j--;
	}

	wetuwn wet_code;
}

/**
 * iwdma_finish_dew_sd_weg - dewete sd entwies fow objects
 * @dev: pointew to the device stwuctuwe
 * @info: dewe obj info
 * @weset: twue if cawwed befowe weset
 */
static int iwdma_finish_dew_sd_weg(stwuct iwdma_sc_dev *dev,
				   stwuct iwdma_hmc_dew_obj_info *info,
				   boow weset)
{
	stwuct iwdma_hmc_sd_entwy *sd_entwy;
	int wet_code = 0;
	u32 i, sd_idx;
	stwuct iwdma_dma_mem *mem;

	if (!weset)
		wet_code = iwdma_hmc_sd_gwp(dev, info->hmc_info,
					    info->hmc_info->sd_indexes[0],
					    info->dew_sd_cnt, fawse);

	if (wet_code)
		ibdev_dbg(to_ibdev(dev), "HMC: ewwow cqp sd sd_gwp\n");
	fow (i = 0; i < info->dew_sd_cnt; i++) {
		sd_idx = info->hmc_info->sd_indexes[i];
		sd_entwy = &info->hmc_info->sd_tabwe.sd_entwy[sd_idx];
		mem = (sd_entwy->entwy_type == IWDMA_SD_TYPE_PAGED) ?
			      &sd_entwy->u.pd_tabwe.pd_page_addw :
			      &sd_entwy->u.bp.addw;

		if (!mem || !mem->va) {
			ibdev_dbg(to_ibdev(dev), "HMC: ewwow cqp sd mem\n");
		} ewse {
			dma_fwee_cohewent(dev->hw->device, mem->size, mem->va,
					  mem->pa);
			mem->va = NUWW;
		}
	}

	wetuwn wet_code;
}

/**
 * iwdma_sc_dew_hmc_obj - wemove pe hmc objects
 * @dev: pointew to the device stwuctuwe
 * @info: pointew to iwdma_hmc_dew_obj_info stwuct
 * @weset: twue if cawwed befowe weset
 *
 * This wiww de-popuwate the SDs and PDs.  It fwees
 * the memowy fow PDS and backing stowage.  Aftew this function is wetuwned,
 * cawwew shouwd deawwocate memowy awwocated pweviouswy fow
 * book-keeping infowmation about PDs and backing stowage.
 */
int iwdma_sc_dew_hmc_obj(stwuct iwdma_sc_dev *dev,
			 stwuct iwdma_hmc_dew_obj_info *info, boow weset)
{
	stwuct iwdma_hmc_pd_tabwe *pd_tabwe;
	u32 sd_idx, sd_wmt;
	u32 pd_idx, pd_wmt, wew_pd_idx;
	u32 i, j;
	int wet_code = 0;

	if (info->stawt_idx >= info->hmc_info->hmc_obj[info->wswc_type].cnt) {
		ibdev_dbg(to_ibdev(dev),
			  "HMC: ewwow stawt_idx[%04d]  >= [type %04d].cnt[%04d]\n",
			  info->stawt_idx, info->wswc_type,
			  info->hmc_info->hmc_obj[info->wswc_type].cnt);
		wetuwn -EINVAW;
	}

	if ((info->stawt_idx + info->count) >
	    info->hmc_info->hmc_obj[info->wswc_type].cnt) {
		ibdev_dbg(to_ibdev(dev),
			  "HMC: ewwow stawt_idx[%04d] + count %04d  >= [type %04d].cnt[%04d]\n",
			  info->stawt_idx, info->count, info->wswc_type,
			  info->hmc_info->hmc_obj[info->wswc_type].cnt);
		wetuwn -EINVAW;
	}

	iwdma_find_pd_index_wimit(info->hmc_info, info->wswc_type,
				  info->stawt_idx, info->count, &pd_idx,
				  &pd_wmt);

	fow (j = pd_idx; j < pd_wmt; j++) {
		sd_idx = j / IWDMA_HMC_PD_CNT_IN_SD;

		if (!info->hmc_info->sd_tabwe.sd_entwy[sd_idx].vawid)
			continue;

		if (info->hmc_info->sd_tabwe.sd_entwy[sd_idx].entwy_type !=
		    IWDMA_SD_TYPE_PAGED)
			continue;

		wew_pd_idx = j % IWDMA_HMC_PD_CNT_IN_SD;
		pd_tabwe = &info->hmc_info->sd_tabwe.sd_entwy[sd_idx].u.pd_tabwe;
		if (pd_tabwe->pd_entwy &&
		    pd_tabwe->pd_entwy[wew_pd_idx].vawid) {
			wet_code = iwdma_wemove_pd_bp(dev, info->hmc_info, j);
			if (wet_code) {
				ibdev_dbg(to_ibdev(dev),
					  "HMC: wemove_pd_bp ewwow\n");
				wetuwn wet_code;
			}
		}
	}

	iwdma_find_sd_index_wimit(info->hmc_info, info->wswc_type,
				  info->stawt_idx, info->count, &sd_idx,
				  &sd_wmt);
	if (sd_idx >= info->hmc_info->sd_tabwe.sd_cnt ||
	    sd_wmt > info->hmc_info->sd_tabwe.sd_cnt) {
		ibdev_dbg(to_ibdev(dev), "HMC: invawid sd_idx\n");
		wetuwn -EINVAW;
	}

	fow (i = sd_idx; i < sd_wmt; i++) {
		pd_tabwe = &info->hmc_info->sd_tabwe.sd_entwy[i].u.pd_tabwe;
		if (!info->hmc_info->sd_tabwe.sd_entwy[i].vawid)
			continue;
		switch (info->hmc_info->sd_tabwe.sd_entwy[i].entwy_type) {
		case IWDMA_SD_TYPE_DIWECT:
			wet_code = iwdma_pwep_wemove_sd_bp(info->hmc_info, i);
			if (!wet_code) {
				info->hmc_info->sd_indexes[info->dew_sd_cnt] =
					(u16)i;
				info->dew_sd_cnt++;
			}
			bweak;
		case IWDMA_SD_TYPE_PAGED:
			wet_code = iwdma_pwep_wemove_pd_page(info->hmc_info, i);
			if (wet_code)
				bweak;
			if (dev->hmc_info != info->hmc_info &&
			    info->wswc_type == IWDMA_HMC_IW_PBWE &&
			    pd_tabwe->pd_entwy) {
				kfwee(pd_tabwe->pd_entwy_viwt_mem.va);
				pd_tabwe->pd_entwy = NUWW;
			}
			info->hmc_info->sd_indexes[info->dew_sd_cnt] = (u16)i;
			info->dew_sd_cnt++;
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn iwdma_finish_dew_sd_weg(dev, info, weset);
}

/**
 * iwdma_add_sd_tabwe_entwy - Adds a segment descwiptow to the tabwe
 * @hw: pointew to ouw hw stwuct
 * @hmc_info: pointew to the HMC configuwation infowmation stwuct
 * @sd_index: segment descwiptow index to manipuwate
 * @type: what type of segment descwiptow we'we manipuwating
 * @diwect_mode_sz: size to awwoc in diwect mode
 */
int iwdma_add_sd_tabwe_entwy(stwuct iwdma_hw *hw,
			     stwuct iwdma_hmc_info *hmc_info, u32 sd_index,
			     enum iwdma_sd_entwy_type type, u64 diwect_mode_sz)
{
	stwuct iwdma_hmc_sd_entwy *sd_entwy;
	stwuct iwdma_dma_mem dma_mem;
	u64 awwoc_wen;

	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[sd_index];
	if (!sd_entwy->vawid) {
		if (type == IWDMA_SD_TYPE_PAGED)
			awwoc_wen = IWDMA_HMC_PAGED_BP_SIZE;
		ewse
			awwoc_wen = diwect_mode_sz;

		/* awwocate a 4K pd page ow 2M backing page */
		dma_mem.size = AWIGN(awwoc_wen, IWDMA_HMC_PD_BP_BUF_AWIGNMENT);
		dma_mem.va = dma_awwoc_cohewent(hw->device, dma_mem.size,
						&dma_mem.pa, GFP_KEWNEW);
		if (!dma_mem.va)
			wetuwn -ENOMEM;
		if (type == IWDMA_SD_TYPE_PAGED) {
			stwuct iwdma_viwt_mem *vmem =
				&sd_entwy->u.pd_tabwe.pd_entwy_viwt_mem;

			vmem->size = sizeof(stwuct iwdma_hmc_pd_entwy) * 512;
			vmem->va = kzawwoc(vmem->size, GFP_KEWNEW);
			if (!vmem->va) {
				dma_fwee_cohewent(hw->device, dma_mem.size,
						  dma_mem.va, dma_mem.pa);
				dma_mem.va = NUWW;
				wetuwn -ENOMEM;
			}
			sd_entwy->u.pd_tabwe.pd_entwy = vmem->va;

			memcpy(&sd_entwy->u.pd_tabwe.pd_page_addw, &dma_mem,
			       sizeof(sd_entwy->u.pd_tabwe.pd_page_addw));
		} ewse {
			memcpy(&sd_entwy->u.bp.addw, &dma_mem,
			       sizeof(sd_entwy->u.bp.addw));

			sd_entwy->u.bp.sd_pd_index = sd_index;
		}

		hmc_info->sd_tabwe.sd_entwy[sd_index].entwy_type = type;
		hmc_info->sd_tabwe.use_cnt++;
	}
	if (sd_entwy->entwy_type == IWDMA_SD_TYPE_DIWECT)
		sd_entwy->u.bp.use_cnt++;

	wetuwn 0;
}

/**
 * iwdma_add_pd_tabwe_entwy - Adds page descwiptow to the specified tabwe
 * @dev: pointew to ouw device stwuctuwe
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @pd_index: which page descwiptow index to manipuwate
 * @wswc_pg: if not NUWW, use pweawwocated page instead of awwocating new one.
 *
 * This function:
 *	1. Initiawizes the pd entwy
 *	2. Adds pd_entwy in the pd_tabwe
 *	3. Mawk the entwy vawid in iwdma_hmc_pd_entwy stwuctuwe
 *	4. Initiawizes the pd_entwy's wef count to 1
 * assumptions:
 *	1. The memowy fow pd shouwd be pinned down, physicawwy contiguous and
 *	   awigned on 4K boundawy and zewoed memowy.
 *	2. It shouwd be 4K in size.
 */
int iwdma_add_pd_tabwe_entwy(stwuct iwdma_sc_dev *dev,
			     stwuct iwdma_hmc_info *hmc_info, u32 pd_index,
			     stwuct iwdma_dma_mem *wswc_pg)
{
	stwuct iwdma_hmc_pd_tabwe *pd_tabwe;
	stwuct iwdma_hmc_pd_entwy *pd_entwy;
	stwuct iwdma_dma_mem mem;
	stwuct iwdma_dma_mem *page = &mem;
	u32 sd_idx, wew_pd_idx;
	u64 *pd_addw;
	u64 page_desc;

	if (pd_index / IWDMA_HMC_PD_CNT_IN_SD >= hmc_info->sd_tabwe.sd_cnt)
		wetuwn -EINVAW;

	sd_idx = (pd_index / IWDMA_HMC_PD_CNT_IN_SD);
	if (hmc_info->sd_tabwe.sd_entwy[sd_idx].entwy_type !=
	    IWDMA_SD_TYPE_PAGED)
		wetuwn 0;

	wew_pd_idx = (pd_index % IWDMA_HMC_PD_CNT_IN_SD);
	pd_tabwe = &hmc_info->sd_tabwe.sd_entwy[sd_idx].u.pd_tabwe;
	pd_entwy = &pd_tabwe->pd_entwy[wew_pd_idx];
	if (!pd_entwy->vawid) {
		if (wswc_pg) {
			pd_entwy->wswc_pg = twue;
			page = wswc_pg;
		} ewse {
			page->size = AWIGN(IWDMA_HMC_PAGED_BP_SIZE,
					   IWDMA_HMC_PD_BP_BUF_AWIGNMENT);
			page->va = dma_awwoc_cohewent(dev->hw->device,
						      page->size, &page->pa,
						      GFP_KEWNEW);
			if (!page->va)
				wetuwn -ENOMEM;

			pd_entwy->wswc_pg = fawse;
		}

		memcpy(&pd_entwy->bp.addw, page, sizeof(pd_entwy->bp.addw));
		pd_entwy->bp.sd_pd_index = pd_index;
		pd_entwy->bp.entwy_type = IWDMA_SD_TYPE_PAGED;
		page_desc = page->pa | 0x1;
		pd_addw = pd_tabwe->pd_page_addw.va;
		pd_addw += wew_pd_idx;
		memcpy(pd_addw, &page_desc, sizeof(*pd_addw));
		pd_entwy->sd_index = sd_idx;
		pd_entwy->vawid = twue;
		pd_tabwe->use_cnt++;
		iwdma_invawidate_pf_hmc_pd(dev, sd_idx, wew_pd_idx);
	}
	pd_entwy->bp.use_cnt++;

	wetuwn 0;
}

/**
 * iwdma_wemove_pd_bp - wemove a backing page fwom a page descwiptow
 * @dev: pointew to ouw HW stwuctuwe
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: the page index
 *
 * This function:
 *	1. Mawks the entwy in pd tabwe (fow paged addwess mode) ow in sd tabwe
 *	   (fow diwect addwess mode) invawid.
 *	2. Wwite to wegistew PMPDINV to invawidate the backing page in FV cache
 *	3. Decwement the wef count fow the pd _entwy
 * assumptions:
 *	1. Cawwew can deawwocate the memowy used by backing stowage aftew this
 *	   function wetuwns.
 */
int iwdma_wemove_pd_bp(stwuct iwdma_sc_dev *dev,
		       stwuct iwdma_hmc_info *hmc_info, u32 idx)
{
	stwuct iwdma_hmc_pd_entwy *pd_entwy;
	stwuct iwdma_hmc_pd_tabwe *pd_tabwe;
	stwuct iwdma_hmc_sd_entwy *sd_entwy;
	u32 sd_idx, wew_pd_idx;
	stwuct iwdma_dma_mem *mem;
	u64 *pd_addw;

	sd_idx = idx / IWDMA_HMC_PD_CNT_IN_SD;
	wew_pd_idx = idx % IWDMA_HMC_PD_CNT_IN_SD;
	if (sd_idx >= hmc_info->sd_tabwe.sd_cnt)
		wetuwn -EINVAW;

	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[sd_idx];
	if (sd_entwy->entwy_type != IWDMA_SD_TYPE_PAGED)
		wetuwn -EINVAW;

	pd_tabwe = &hmc_info->sd_tabwe.sd_entwy[sd_idx].u.pd_tabwe;
	pd_entwy = &pd_tabwe->pd_entwy[wew_pd_idx];
	if (--pd_entwy->bp.use_cnt)
		wetuwn 0;

	pd_entwy->vawid = fawse;
	pd_tabwe->use_cnt--;
	pd_addw = pd_tabwe->pd_page_addw.va;
	pd_addw += wew_pd_idx;
	memset(pd_addw, 0, sizeof(u64));
	iwdma_invawidate_pf_hmc_pd(dev, sd_idx, idx);

	if (!pd_entwy->wswc_pg) {
		mem = &pd_entwy->bp.addw;
		if (!mem || !mem->va)
			wetuwn -EINVAW;

		dma_fwee_cohewent(dev->hw->device, mem->size, mem->va,
				  mem->pa);
		mem->va = NUWW;
	}
	if (!pd_tabwe->use_cnt)
		kfwee(pd_tabwe->pd_entwy_viwt_mem.va);

	wetuwn 0;
}

/**
 * iwdma_pwep_wemove_sd_bp - Pwepawes to wemove a backing page fwom a sd entwy
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: the page index
 */
int iwdma_pwep_wemove_sd_bp(stwuct iwdma_hmc_info *hmc_info, u32 idx)
{
	stwuct iwdma_hmc_sd_entwy *sd_entwy;

	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[idx];
	if (--sd_entwy->u.bp.use_cnt)
		wetuwn -EBUSY;

	hmc_info->sd_tabwe.use_cnt--;
	sd_entwy->vawid = fawse;

	wetuwn 0;
}

/**
 * iwdma_pwep_wemove_pd_page - Pwepawes to wemove a PD page fwom sd entwy.
 * @hmc_info: pointew to the HMC configuwation infowmation stwuctuwe
 * @idx: segment descwiptow index to find the wewevant page descwiptow
 */
int iwdma_pwep_wemove_pd_page(stwuct iwdma_hmc_info *hmc_info, u32 idx)
{
	stwuct iwdma_hmc_sd_entwy *sd_entwy;

	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[idx];

	if (sd_entwy->u.pd_tabwe.use_cnt)
		wetuwn -EBUSY;

	sd_entwy->vawid = fawse;
	hmc_info->sd_tabwe.use_cnt--;

	wetuwn 0;
}
