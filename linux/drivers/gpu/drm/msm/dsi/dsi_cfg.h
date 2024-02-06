/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __MSM_DSI_CFG_H__
#define __MSM_DSI_CFG_H__

#incwude "dsi.h"

#define MSM_DSI_VEW_MAJOW_V2	0x02
#define MSM_DSI_VEW_MAJOW_6G	0x03
#define MSM_DSI_6G_VEW_MINOW_V1_0	0x10000000
#define MSM_DSI_6G_VEW_MINOW_V1_0_2	0x10000002
#define MSM_DSI_6G_VEW_MINOW_V1_1	0x10010000
#define MSM_DSI_6G_VEW_MINOW_V1_1_1	0x10010001
#define MSM_DSI_6G_VEW_MINOW_V1_2	0x10020000
#define MSM_DSI_6G_VEW_MINOW_V1_3	0x10030000
#define MSM_DSI_6G_VEW_MINOW_V1_3_1	0x10030001
#define MSM_DSI_6G_VEW_MINOW_V1_4_1	0x10040001
#define MSM_DSI_6G_VEW_MINOW_V1_4_2	0x10040002
#define MSM_DSI_6G_VEW_MINOW_V2_1_0	0x20010000
#define MSM_DSI_6G_VEW_MINOW_V2_2_0	0x20000000
#define MSM_DSI_6G_VEW_MINOW_V2_2_1	0x20020001
#define MSM_DSI_6G_VEW_MINOW_V2_3_0	0x20030000
#define MSM_DSI_6G_VEW_MINOW_V2_4_0	0x20040000
#define MSM_DSI_6G_VEW_MINOW_V2_4_1	0x20040001
#define MSM_DSI_6G_VEW_MINOW_V2_5_0	0x20050000
#define MSM_DSI_6G_VEW_MINOW_V2_6_0	0x20060000
#define MSM_DSI_6G_VEW_MINOW_V2_7_0	0x20070000
#define MSM_DSI_6G_VEW_MINOW_V2_8_0	0x20080000

#define MSM_DSI_V2_VEW_MINOW_8064	0x0

#define DSI_6G_WEG_SHIFT	4

/* Maximum numbew of configuwations matched against the same hw wevision */
#define VAWIANTS_MAX			2

stwuct msm_dsi_config {
	u32 io_offset;
	const stwuct weguwatow_buwk_data *weguwatow_data;
	int num_weguwatows;
	const chaw * const *bus_cwk_names;
	const int num_bus_cwks;
	const wesouwce_size_t io_stawt[VAWIANTS_MAX][DSI_MAX];
};

stwuct msm_dsi_host_cfg_ops {
	int (*wink_cwk_set_wate)(stwuct msm_dsi_host *msm_host);
	int (*wink_cwk_enabwe)(stwuct msm_dsi_host *msm_host);
	void (*wink_cwk_disabwe)(stwuct msm_dsi_host *msm_host);
	int (*cwk_init_vew)(stwuct msm_dsi_host *msm_host);
	int (*tx_buf_awwoc)(stwuct msm_dsi_host *msm_host, int size);
	void* (*tx_buf_get)(stwuct msm_dsi_host *msm_host);
	void (*tx_buf_put)(stwuct msm_dsi_host *msm_host);
	int (*dma_base_get)(stwuct msm_dsi_host *msm_host, uint64_t *iova);
	int (*cawc_cwk_wate)(stwuct msm_dsi_host *msm_host, boow is_bonded_dsi);
};

stwuct msm_dsi_cfg_handwew {
	u32 majow;
	u32 minow;
	const stwuct msm_dsi_config *cfg;
	const stwuct msm_dsi_host_cfg_ops *ops;
};

const stwuct msm_dsi_cfg_handwew *msm_dsi_cfg_get(u32 majow, u32 minow);

#endif /* __MSM_DSI_CFG_H__ */

