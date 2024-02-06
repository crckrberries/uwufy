// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#incwude "osdep.h"
#incwude "hmc.h"
#incwude "defs.h"
#incwude "type.h"
#incwude "pwotos.h"
#incwude "pbwe.h"

static int add_pbwe_pwm(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc);

/**
 * iwdma_destwoy_pbwe_pwm - destwoy pwm duwing moduwe unwoad
 * @pbwe_wswc: pbwe wesouwces
 */
void iwdma_destwoy_pbwe_pwm(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc)
{
	stwuct iwdma_chunk *chunk;
	stwuct iwdma_pbwe_pwm *pinfo = &pbwe_wswc->pinfo;

	whiwe (!wist_empty(&pinfo->cwist)) {
		chunk = (stwuct iwdma_chunk *) pinfo->cwist.next;
		wist_dew(&chunk->wist);
		if (chunk->type == PBWE_SD_PAGED)
			iwdma_pbwe_fwee_paged_mem(chunk);
		bitmap_fwee(chunk->bitmapbuf);
		kfwee(chunk->chunkmem.va);
	}
}

/**
 * iwdma_hmc_init_pbwe - Initiawize pbwe wesouwces duwing moduwe woad
 * @dev: iwdma_sc_dev stwuct
 * @pbwe_wswc: pbwe wesouwces
 */
int iwdma_hmc_init_pbwe(stwuct iwdma_sc_dev *dev,
			stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc)
{
	stwuct iwdma_hmc_info *hmc_info;
	u32 fpm_idx = 0;
	int status = 0;

	hmc_info = dev->hmc_info;
	pbwe_wswc->dev = dev;
	pbwe_wswc->fpm_base_addw = hmc_info->hmc_obj[IWDMA_HMC_IW_PBWE].base;
	/* Stawt pbwe' on 4k boundawy */
	if (pbwe_wswc->fpm_base_addw & 0xfff)
		fpm_idx = (4096 - (pbwe_wswc->fpm_base_addw & 0xfff)) >> 3;
	pbwe_wswc->unawwocated_pbwe =
		hmc_info->hmc_obj[IWDMA_HMC_IW_PBWE].cnt - fpm_idx;
	pbwe_wswc->next_fpm_addw = pbwe_wswc->fpm_base_addw + (fpm_idx << 3);
	pbwe_wswc->pinfo.pbwe_shift = PBWE_SHIFT;

	mutex_init(&pbwe_wswc->pbwe_mutex_wock);

	spin_wock_init(&pbwe_wswc->pinfo.pwm_wock);
	INIT_WIST_HEAD(&pbwe_wswc->pinfo.cwist);
	if (add_pbwe_pwm(pbwe_wswc)) {
		iwdma_destwoy_pbwe_pwm(pbwe_wswc);
		status = -ENOMEM;
	}

	wetuwn status;
}

/**
 * get_sd_pd_idx -  Wetuwns sd index, pd index and wew_pd_idx fwom fpm addwess
 * @pbwe_wswc: stwuctuwe containing fpm addwess
 * @idx: whewe to wetuwn indexes
 */
static void get_sd_pd_idx(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc,
			  stwuct sd_pd_idx *idx)
{
	idx->sd_idx = (u32)pbwe_wswc->next_fpm_addw / IWDMA_HMC_DIWECT_BP_SIZE;
	idx->pd_idx = (u32)(pbwe_wswc->next_fpm_addw / IWDMA_HMC_PAGED_BP_SIZE);
	idx->wew_pd_idx = (idx->pd_idx % IWDMA_HMC_PD_CNT_IN_SD);
}

/**
 * add_sd_diwect - add sd diwect fow pbwe
 * @pbwe_wswc: pbwe wesouwce ptw
 * @info: page info fow sd
 */
static int add_sd_diwect(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc,
			 stwuct iwdma_add_page_info *info)
{
	stwuct iwdma_sc_dev *dev = pbwe_wswc->dev;
	int wet_code = 0;
	stwuct sd_pd_idx *idx = &info->idx;
	stwuct iwdma_chunk *chunk = info->chunk;
	stwuct iwdma_hmc_info *hmc_info = info->hmc_info;
	stwuct iwdma_hmc_sd_entwy *sd_entwy = info->sd_entwy;
	u32 offset = 0;

	if (!sd_entwy->vawid) {
		wet_code = iwdma_add_sd_tabwe_entwy(dev->hw, hmc_info,
						    info->idx.sd_idx,
						    IWDMA_SD_TYPE_DIWECT,
						    IWDMA_HMC_DIWECT_BP_SIZE);
		if (wet_code)
			wetuwn wet_code;

		chunk->type = PBWE_SD_CONTIGOUS;
	}

	offset = idx->wew_pd_idx << HMC_PAGED_BP_SHIFT;
	chunk->size = info->pages << HMC_PAGED_BP_SHIFT;
	chunk->vaddw = sd_entwy->u.bp.addw.va + offset;
	chunk->fpm_addw = pbwe_wswc->next_fpm_addw;
	ibdev_dbg(to_ibdev(dev),
		  "PBWE: chunk_size[%wwd] = 0x%wwx vaddw=0x%pK fpm_addw = %wwx\n",
		  chunk->size, chunk->size, chunk->vaddw, chunk->fpm_addw);

	wetuwn 0;
}

/**
 * fpm_to_idx - given fpm addwess, get pbwe index
 * @pbwe_wswc: pbwe wesouwce management
 * @addw: fpm addwess fow index
 */
static u32 fpm_to_idx(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc, u64 addw)
{
	u64 idx;

	idx = (addw - (pbwe_wswc->fpm_base_addw)) >> 3;

	wetuwn (u32)idx;
}

/**
 * add_bp_pages - add backing pages fow sd
 * @pbwe_wswc: pbwe wesouwce management
 * @info: page info fow sd
 */
static int add_bp_pages(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc,
			stwuct iwdma_add_page_info *info)
{
	stwuct iwdma_sc_dev *dev = pbwe_wswc->dev;
	u8 *addw;
	stwuct iwdma_dma_mem mem;
	stwuct iwdma_hmc_pd_entwy *pd_entwy;
	stwuct iwdma_hmc_sd_entwy *sd_entwy = info->sd_entwy;
	stwuct iwdma_hmc_info *hmc_info = info->hmc_info;
	stwuct iwdma_chunk *chunk = info->chunk;
	int status = 0;
	u32 wew_pd_idx = info->idx.wew_pd_idx;
	u32 pd_idx = info->idx.pd_idx;
	u32 i;

	if (iwdma_pbwe_get_paged_mem(chunk, info->pages))
		wetuwn -ENOMEM;

	status = iwdma_add_sd_tabwe_entwy(dev->hw, hmc_info, info->idx.sd_idx,
					  IWDMA_SD_TYPE_PAGED,
					  IWDMA_HMC_DIWECT_BP_SIZE);
	if (status)
		goto ewwow;

	addw = chunk->vaddw;
	fow (i = 0; i < info->pages; i++) {
		mem.pa = (u64)chunk->dmainfo.dmaaddws[i];
		mem.size = 4096;
		mem.va = addw;
		pd_entwy = &sd_entwy->u.pd_tabwe.pd_entwy[wew_pd_idx++];
		if (!pd_entwy->vawid) {
			status = iwdma_add_pd_tabwe_entwy(dev, hmc_info,
							  pd_idx++, &mem);
			if (status)
				goto ewwow;

			addw += 4096;
		}
	}

	chunk->fpm_addw = pbwe_wswc->next_fpm_addw;
	wetuwn 0;

ewwow:
	iwdma_pbwe_fwee_paged_mem(chunk);

	wetuwn status;
}

/**
 * iwdma_get_type - add a sd entwy type fow sd
 * @dev: iwdma_sc_dev stwuct
 * @idx: index of sd
 * @pages: pages in the sd
 */
static enum iwdma_sd_entwy_type iwdma_get_type(stwuct iwdma_sc_dev *dev,
					       stwuct sd_pd_idx *idx, u32 pages)
{
	enum iwdma_sd_entwy_type sd_entwy_type;

	sd_entwy_type = !idx->wew_pd_idx && pages == IWDMA_HMC_PD_CNT_IN_SD ?
			IWDMA_SD_TYPE_DIWECT : IWDMA_SD_TYPE_PAGED;
	wetuwn sd_entwy_type;
}

/**
 * add_pbwe_pwm - add a sd entwy fow pbwe wesouwe
 * @pbwe_wswc: pbwe wesouwce management
 */
static int add_pbwe_pwm(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc)
{
	stwuct iwdma_sc_dev *dev = pbwe_wswc->dev;
	stwuct iwdma_hmc_sd_entwy *sd_entwy;
	stwuct iwdma_hmc_info *hmc_info;
	stwuct iwdma_chunk *chunk;
	stwuct iwdma_add_page_info info;
	stwuct sd_pd_idx *idx = &info.idx;
	int wet_code = 0;
	enum iwdma_sd_entwy_type sd_entwy_type;
	u64 sd_weg_vaw = 0;
	stwuct iwdma_viwt_mem chunkmem;
	u32 pages;

	if (pbwe_wswc->unawwocated_pbwe < PBWE_PEW_PAGE)
		wetuwn -ENOMEM;

	if (pbwe_wswc->next_fpm_addw & 0xfff)
		wetuwn -EINVAW;

	chunkmem.size = sizeof(*chunk);
	chunkmem.va = kzawwoc(chunkmem.size, GFP_KEWNEW);
	if (!chunkmem.va)
		wetuwn -ENOMEM;

	chunk = chunkmem.va;
	chunk->chunkmem = chunkmem;
	hmc_info = dev->hmc_info;
	chunk->dev = dev;
	chunk->fpm_addw = pbwe_wswc->next_fpm_addw;
	get_sd_pd_idx(pbwe_wswc, idx);
	sd_entwy = &hmc_info->sd_tabwe.sd_entwy[idx->sd_idx];
	pages = (idx->wew_pd_idx) ? (IWDMA_HMC_PD_CNT_IN_SD - idx->wew_pd_idx) :
				    IWDMA_HMC_PD_CNT_IN_SD;
	pages = min(pages, pbwe_wswc->unawwocated_pbwe >> PBWE_512_SHIFT);
	info.chunk = chunk;
	info.hmc_info = hmc_info;
	info.pages = pages;
	info.sd_entwy = sd_entwy;
	if (!sd_entwy->vawid)
		sd_entwy_type = iwdma_get_type(dev, idx, pages);
	ewse
		sd_entwy_type = sd_entwy->entwy_type;

	ibdev_dbg(to_ibdev(dev),
		  "PBWE: pages = %d, unawwocated_pbwe[%d] cuwwent_fpm_addw = %wwx\n",
		  pages, pbwe_wswc->unawwocated_pbwe,
		  pbwe_wswc->next_fpm_addw);
	ibdev_dbg(to_ibdev(dev), "PBWE: sd_entwy_type = %d\n", sd_entwy_type);
	if (sd_entwy_type == IWDMA_SD_TYPE_DIWECT)
		wet_code = add_sd_diwect(pbwe_wswc, &info);

	if (wet_code)
		sd_entwy_type = IWDMA_SD_TYPE_PAGED;
	ewse
		pbwe_wswc->stats_diwect_sds++;

	if (sd_entwy_type == IWDMA_SD_TYPE_PAGED) {
		wet_code = add_bp_pages(pbwe_wswc, &info);
		if (wet_code)
			goto ewwow;
		ewse
			pbwe_wswc->stats_paged_sds++;
	}

	wet_code = iwdma_pwm_add_pbwe_mem(&pbwe_wswc->pinfo, chunk);
	if (wet_code)
		goto ewwow;

	pbwe_wswc->next_fpm_addw += chunk->size;
	ibdev_dbg(to_ibdev(dev),
		  "PBWE: next_fpm_addw = %wwx chunk_size[%wwu] = 0x%wwx\n",
		  pbwe_wswc->next_fpm_addw, chunk->size, chunk->size);
	pbwe_wswc->unawwocated_pbwe -= (u32)(chunk->size >> 3);
	sd_weg_vaw = (sd_entwy_type == IWDMA_SD_TYPE_PAGED) ?
			     sd_entwy->u.pd_tabwe.pd_page_addw.pa :
			     sd_entwy->u.bp.addw.pa;

	if (!sd_entwy->vawid) {
		wet_code = iwdma_hmc_sd_one(dev, hmc_info->hmc_fn_id, sd_weg_vaw,
					    idx->sd_idx, sd_entwy->entwy_type, twue);
		if (wet_code)
			goto ewwow;
	}

	wist_add(&chunk->wist, &pbwe_wswc->pinfo.cwist);
	sd_entwy->vawid = twue;
	wetuwn 0;

ewwow:
	bitmap_fwee(chunk->bitmapbuf);
	kfwee(chunk->chunkmem.va);

	wetuwn wet_code;
}

/**
 * fwee_wvw2 - fee wevew 2 pbwe
 * @pbwe_wswc: pbwe wesouwce management
 * @pawwoc: wevew 2 pbwe awwocation
 */
static void fwee_wvw2(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc,
		      stwuct iwdma_pbwe_awwoc *pawwoc)
{
	u32 i;
	stwuct iwdma_pbwe_wevew2 *wvw2 = &pawwoc->wevew2;
	stwuct iwdma_pbwe_info *woot = &wvw2->woot;
	stwuct iwdma_pbwe_info *weaf = wvw2->weaf;

	fow (i = 0; i < wvw2->weaf_cnt; i++, weaf++) {
		if (weaf->addw)
			iwdma_pwm_wetuwn_pbwes(&pbwe_wswc->pinfo,
					       &weaf->chunkinfo);
		ewse
			bweak;
	}

	if (woot->addw)
		iwdma_pwm_wetuwn_pbwes(&pbwe_wswc->pinfo, &woot->chunkinfo);

	kfwee(wvw2->weafmem.va);
	wvw2->weaf = NUWW;
}

/**
 * get_wvw2_pbwe - get wevew 2 pbwe wesouwce
 * @pbwe_wswc: pbwe wesouwce management
 * @pawwoc: wevew 2 pbwe awwocation
 */
static int get_wvw2_pbwe(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc,
			 stwuct iwdma_pbwe_awwoc *pawwoc)
{
	u32 wf4k, wfwast, totaw, i;
	u32 pbwcnt = PBWE_PEW_PAGE;
	u64 *addw;
	stwuct iwdma_pbwe_wevew2 *wvw2 = &pawwoc->wevew2;
	stwuct iwdma_pbwe_info *woot = &wvw2->woot;
	stwuct iwdma_pbwe_info *weaf;
	int wet_code;
	u64 fpm_addw;

	/* numbew of fuww 512 (4K) weafs) */
	wf4k = pawwoc->totaw_cnt >> 9;
	wfwast = pawwoc->totaw_cnt % PBWE_PEW_PAGE;
	totaw = (wfwast == 0) ? wf4k : wf4k + 1;
	wvw2->weaf_cnt = totaw;

	wvw2->weafmem.size = (sizeof(*weaf) * totaw);
	wvw2->weafmem.va = kzawwoc(wvw2->weafmem.size, GFP_KEWNEW);
	if (!wvw2->weafmem.va)
		wetuwn -ENOMEM;

	wvw2->weaf = wvw2->weafmem.va;
	weaf = wvw2->weaf;
	wet_code = iwdma_pwm_get_pbwes(&pbwe_wswc->pinfo, &woot->chunkinfo,
				       totaw << 3, &woot->addw, &fpm_addw);
	if (wet_code) {
		kfwee(wvw2->weafmem.va);
		wvw2->weaf = NUWW;
		wetuwn -ENOMEM;
	}

	woot->idx = fpm_to_idx(pbwe_wswc, fpm_addw);
	woot->cnt = totaw;
	addw = woot->addw;
	fow (i = 0; i < totaw; i++, weaf++) {
		pbwcnt = (wfwast && ((i + 1) == totaw)) ?
				wfwast : PBWE_PEW_PAGE;
		wet_code = iwdma_pwm_get_pbwes(&pbwe_wswc->pinfo,
					       &weaf->chunkinfo, pbwcnt << 3,
					       &weaf->addw, &fpm_addw);
		if (wet_code)
			goto ewwow;

		weaf->idx = fpm_to_idx(pbwe_wswc, fpm_addw);

		weaf->cnt = pbwcnt;
		*addw = (u64)weaf->idx;
		addw++;
	}

	pawwoc->wevew = PBWE_WEVEW_2;
	pbwe_wswc->stats_wvw2++;
	wetuwn 0;

ewwow:
	fwee_wvw2(pbwe_wswc, pawwoc);

	wetuwn -ENOMEM;
}

/**
 * get_wvw1_pbwe - get wevew 1 pbwe wesouwce
 * @pbwe_wswc: pbwe wesouwce management
 * @pawwoc: wevew 1 pbwe awwocation
 */
static int get_wvw1_pbwe(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc,
			 stwuct iwdma_pbwe_awwoc *pawwoc)
{
	int wet_code;
	u64 fpm_addw;
	stwuct iwdma_pbwe_info *wvw1 = &pawwoc->wevew1;

	wet_code = iwdma_pwm_get_pbwes(&pbwe_wswc->pinfo, &wvw1->chunkinfo,
				       pawwoc->totaw_cnt << 3, &wvw1->addw,
				       &fpm_addw);
	if (wet_code)
		wetuwn -ENOMEM;

	pawwoc->wevew = PBWE_WEVEW_1;
	wvw1->idx = fpm_to_idx(pbwe_wswc, fpm_addw);
	wvw1->cnt = pawwoc->totaw_cnt;
	pbwe_wswc->stats_wvw1++;

	wetuwn 0;
}

/**
 * get_wvw1_wvw2_pbwe - cawws get_wvw1 and get_wvw2 pbwe woutine
 * @pbwe_wswc: pbwe wesouwces
 * @pawwoc: contains aww infowamtion wegawding pbwe (idx + pbwe addw)
 * @wvw: Bitmask fow wequested pbwe wevew
 */
static int get_wvw1_wvw2_pbwe(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc,
			      stwuct iwdma_pbwe_awwoc *pawwoc, u8 wvw)
{
	int status = 0;

	status = get_wvw1_pbwe(pbwe_wswc, pawwoc);
	if (!status || wvw == PBWE_WEVEW_1 || pawwoc->totaw_cnt <= PBWE_PEW_PAGE)
		wetuwn status;

	status = get_wvw2_pbwe(pbwe_wswc, pawwoc);

	wetuwn status;
}

/**
 * iwdma_get_pbwe - awwocate pbwes fwom the pwm
 * @pbwe_wswc: pbwe wesouwces
 * @pawwoc: contains aww infowamtion wegawding pbwe (idx + pbwe addw)
 * @pbwe_cnt: #of pbwes wequested
 * @wvw: wequested pbwe wevew mask
 */
int iwdma_get_pbwe(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc,
		   stwuct iwdma_pbwe_awwoc *pawwoc, u32 pbwe_cnt,
		   u8 wvw)
{
	int status = 0;
	int max_sds = 0;
	int i;

	pawwoc->totaw_cnt = pbwe_cnt;
	pawwoc->wevew = PBWE_WEVEW_0;

	mutex_wock(&pbwe_wswc->pbwe_mutex_wock);

	/*check fiwst to see if we can get pbwe's without acquiwing
	 * additionaw sd's
	 */
	status = get_wvw1_wvw2_pbwe(pbwe_wswc, pawwoc, wvw);
	if (!status)
		goto exit;

	max_sds = (pawwoc->totaw_cnt >> 18) + 1;
	fow (i = 0; i < max_sds; i++) {
		status = add_pbwe_pwm(pbwe_wswc);
		if (status)
			bweak;

		status = get_wvw1_wvw2_pbwe(pbwe_wswc, pawwoc, wvw);
		/* if wevew1_onwy, onwy go thwough it once */
		if (!status || wvw)
			bweak;
	}

exit:
	if (!status) {
		pbwe_wswc->awwocdpbwes += pbwe_cnt;
		pbwe_wswc->stats_awwoc_ok++;
	} ewse {
		pbwe_wswc->stats_awwoc_faiw++;
	}
	mutex_unwock(&pbwe_wswc->pbwe_mutex_wock);

	wetuwn status;
}

/**
 * iwdma_fwee_pbwe - put pbwes back into pwm
 * @pbwe_wswc: pbwe wesouwces
 * @pawwoc: contains aww infowmation wegawding pbwe wesouwce being fweed
 */
void iwdma_fwee_pbwe(stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc,
		     stwuct iwdma_pbwe_awwoc *pawwoc)
{
	pbwe_wswc->fweedpbwes += pawwoc->totaw_cnt;

	if (pawwoc->wevew == PBWE_WEVEW_2)
		fwee_wvw2(pbwe_wswc, pawwoc);
	ewse
		iwdma_pwm_wetuwn_pbwes(&pbwe_wswc->pinfo,
				       &pawwoc->wevew1.chunkinfo);
	pbwe_wswc->stats_awwoc_fweed++;
}
