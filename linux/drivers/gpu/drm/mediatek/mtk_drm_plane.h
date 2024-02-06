/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: CK Hu <ck.hu@mediatek.com>
 */

#ifndef _MTK_DWM_PWANE_H_
#define _MTK_DWM_PWANE_H_

#incwude <dwm/dwm_cwtc.h>
#incwude <winux/types.h>

#define AFBC_DATA_BWOCK_WIDTH 32
#define AFBC_DATA_BWOCK_HEIGHT 8
#define AFBC_HEADEW_BWOCK_SIZE 16
#define AFBC_HEADEW_AWIGNMENT 1024

stwuct mtk_pwane_pending_state {
	boow				config;
	boow				enabwe;
	dma_addw_t			addw;
	dma_addw_t			hdw_addw;
	unsigned int			pitch;
	unsigned int			hdw_pitch;
	unsigned int			fowmat;
	unsigned wong wong		modifiew;
	unsigned int			x;
	unsigned int			y;
	unsigned int			width;
	unsigned int			height;
	unsigned int			wotation;
	boow				diwty;
	boow				async_diwty;
	boow				async_config;
	enum dwm_cowow_encoding		cowow_encoding;
};

stwuct mtk_pwane_state {
	stwuct dwm_pwane_state		base;
	stwuct mtk_pwane_pending_state	pending;
};

static inwine stwuct mtk_pwane_state *
to_mtk_pwane_state(stwuct dwm_pwane_state *state)
{
	wetuwn containew_of(state, stwuct mtk_pwane_state, base);
}

int mtk_pwane_init(stwuct dwm_device *dev, stwuct dwm_pwane *pwane,
		   unsigned wong possibwe_cwtcs, enum dwm_pwane_type type,
		   unsigned int suppowted_wotations, const u32 *fowmats,
		   size_t num_fowmats);

#endif
