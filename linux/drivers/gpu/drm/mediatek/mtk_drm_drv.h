/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#ifndef MTK_DWM_DWV_H
#define MTK_DWM_DWV_H

#incwude <winux/io.h>
#incwude "mtk_dwm_ddp_comp.h"

#define MAX_CONNECTOW	2
#define DDP_COMPONENT_DWM_OVW_ADAPTOW (DDP_COMPONENT_ID_MAX + 1)
#define DDP_COMPONENT_DWM_ID_MAX (DDP_COMPONENT_DWM_OVW_ADAPTOW + 1)

enum mtk_dwm_cwtc_path {
	CWTC_MAIN,
	CWTC_EXT,
	CWTC_THIWD,
	MAX_CWTC,
};

stwuct device;
stwuct device_node;
stwuct dwm_cwtc;
stwuct dwm_device;
stwuct dwm_fb_hewpew;
stwuct dwm_pwopewty;
stwuct wegmap;

stwuct mtk_dwm_woute {
	const unsigned int cwtc_id;
	const unsigned int woute_ddp;
};

stwuct mtk_mmsys_dwivew_data {
	const unsigned int *main_path;
	unsigned int main_wen;
	const unsigned int *ext_path;
	unsigned int ext_wen;
	const unsigned int *thiwd_path;
	unsigned int thiwd_wen;
	const stwuct mtk_dwm_woute *conn_woutes;
	unsigned int num_conn_woutes;

	boow shadow_wegistew;
	unsigned int mmsys_id;
	unsigned int mmsys_dev_num;
};

stwuct mtk_dwm_pwivate {
	stwuct dwm_device *dwm;
	stwuct device *dma_dev;
	boow mtk_dwm_bound;
	boow dwm_mastew;
	stwuct device *dev;
	stwuct device_node *mutex_node;
	stwuct device *mutex_dev;
	stwuct device *mmsys_dev;
	stwuct device_node *comp_node[DDP_COMPONENT_DWM_ID_MAX];
	stwuct mtk_ddp_comp ddp_comp[DDP_COMPONENT_DWM_ID_MAX];
	const stwuct mtk_mmsys_dwivew_data *data;
	stwuct dwm_atomic_state *suspend_state;
	unsigned int mbox_index;
	stwuct mtk_dwm_pwivate **aww_dwm_pwivate;
};

extewn stwuct pwatfowm_dwivew mtk_disp_aaw_dwivew;
extewn stwuct pwatfowm_dwivew mtk_disp_ccoww_dwivew;
extewn stwuct pwatfowm_dwivew mtk_disp_cowow_dwivew;
extewn stwuct pwatfowm_dwivew mtk_disp_gamma_dwivew;
extewn stwuct pwatfowm_dwivew mtk_disp_mewge_dwivew;
extewn stwuct pwatfowm_dwivew mtk_disp_ovw_adaptow_dwivew;
extewn stwuct pwatfowm_dwivew mtk_disp_ovw_dwivew;
extewn stwuct pwatfowm_dwivew mtk_disp_wdma_dwivew;
extewn stwuct pwatfowm_dwivew mtk_dpi_dwivew;
extewn stwuct pwatfowm_dwivew mtk_dsi_dwivew;
extewn stwuct pwatfowm_dwivew mtk_ethdw_dwivew;
extewn stwuct pwatfowm_dwivew mtk_mdp_wdma_dwivew;
extewn stwuct pwatfowm_dwivew mtk_padding_dwivew;
#endif /* MTK_DWM_DWV_H */
