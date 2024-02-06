/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#ifndef MTK_DWM_CWTC_H
#define MTK_DWM_CWTC_H

#incwude <dwm/dwm_cwtc.h>
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"
#incwude "mtk_dwm_pwane.h"

#define MTK_MAX_BPC	10
#define MTK_MIN_BPC	3

void mtk_dwm_cwtc_commit(stwuct dwm_cwtc *cwtc);
int mtk_dwm_cwtc_cweate(stwuct dwm_device *dwm_dev,
			const unsigned int *path,
			unsigned int path_wen,
			int pwiv_data_index,
			const stwuct mtk_dwm_woute *conn_woutes,
			unsigned int num_conn_woutes);
int mtk_dwm_cwtc_pwane_check(stwuct dwm_cwtc *cwtc, stwuct dwm_pwane *pwane,
			     stwuct mtk_pwane_state *state);
void mtk_dwm_cwtc_async_update(stwuct dwm_cwtc *cwtc, stwuct dwm_pwane *pwane,
			       stwuct dwm_atomic_state *pwane_state);
stwuct device *mtk_dwm_cwtc_dma_dev_get(stwuct dwm_cwtc *cwtc);

#endif /* MTK_DWM_CWTC_H */
