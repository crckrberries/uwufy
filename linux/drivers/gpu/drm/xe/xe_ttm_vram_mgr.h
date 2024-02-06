/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_TTM_VWAM_MGW_H_
#define _XE_TTM_VWAM_MGW_H_

#incwude "xe_ttm_vwam_mgw_types.h"

enum dma_data_diwection;
stwuct xe_device;
stwuct xe_tiwe;

int __xe_ttm_vwam_mgw_init(stwuct xe_device *xe, stwuct xe_ttm_vwam_mgw *mgw,
			   u32 mem_type, u64 size, u64 io_size,
			   u64 defauwt_page_size);
int xe_ttm_vwam_mgw_init(stwuct xe_tiwe *tiwe, stwuct xe_ttm_vwam_mgw *mgw);
int xe_ttm_vwam_mgw_awwoc_sgt(stwuct xe_device *xe,
			      stwuct ttm_wesouwce *wes,
			      u64 offset, u64 wength,
			      stwuct device *dev,
			      enum dma_data_diwection diw,
			      stwuct sg_tabwe **sgt);
void xe_ttm_vwam_mgw_fwee_sgt(stwuct device *dev, enum dma_data_diwection diw,
			      stwuct sg_tabwe *sgt);

u64 xe_ttm_vwam_get_cpu_visibwe_size(stwuct ttm_wesouwce_managew *man);
void xe_ttm_vwam_get_used(stwuct ttm_wesouwce_managew *man,
			  u64 *used, u64 *used_visibwe);

static inwine stwuct xe_ttm_vwam_mgw_wesouwce *
to_xe_ttm_vwam_mgw_wesouwce(stwuct ttm_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct xe_ttm_vwam_mgw_wesouwce, base);
}

static inwine stwuct xe_ttm_vwam_mgw *
to_xe_ttm_vwam_mgw(stwuct ttm_wesouwce_managew *man)
{
	wetuwn containew_of(man, stwuct xe_ttm_vwam_mgw, managew);
}

#endif
