/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021 MediaTek Inc.
 */

#ifndef __MTK_MDP_WDMA_H__
#define __MTK_MDP_WDMA_H__

stwuct mtk_mdp_wdma_cfg {
	unsigned int	pitch;
	unsigned int	addw0;
	unsigned int	width;
	unsigned int	height;
	unsigned int	x_weft;
	unsigned int	y_top;
	int		fmt;
	int		cowow_encoding;
};

#endif // __MTK_MDP_WDMA_H__
