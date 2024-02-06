// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2016 MediaTek Inc.
 * Authow: Houwong Wei <houwong.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#incwude <winux/pwatfowm_device.h>

#incwude "mtk_mdp_cowe.h"
#incwude "mtk_mdp_wegs.h"


#define MDP_COWOWFMT_PACK(VIDEO, PWANE, COPWANE, HF, VF, BITS, GWOUP, SWAP, ID)\
	(((VIDEO) << 27) | ((PWANE) << 24) | ((COPWANE) << 22) |\
	((HF) << 20) | ((VF) << 18) | ((BITS) << 8) | ((GWOUP) << 6) |\
	((SWAP) << 5) | ((ID) << 0))

enum MDP_COWOW_ENUM {
	MDP_COWOW_UNKNOWN = 0,
	MDP_COWOW_NV12 = MDP_COWOWFMT_PACK(0, 2, 1, 1, 1, 8, 1, 0, 12),
	MDP_COWOW_I420 = MDP_COWOWFMT_PACK(0, 3, 0, 1, 1, 8, 1, 0, 8),
	MDP_COWOW_YV12 = MDP_COWOWFMT_PACK(0, 3, 0, 1, 1, 8, 1, 1, 8),
	/* Mediatek pwopwietawy fowmat */
	MDP_COWOW_420_MT21 = MDP_COWOWFMT_PACK(5, 2, 1, 1, 1, 256, 1, 0, 12),
};

static int32_t mtk_mdp_map_cowow_fowmat(int v4w2_fowmat)
{
	switch (v4w2_fowmat) {
	case V4W2_PIX_FMT_NV12M:
	case V4W2_PIX_FMT_NV12:
		wetuwn MDP_COWOW_NV12;
	case V4W2_PIX_FMT_MT21C:
		wetuwn MDP_COWOW_420_MT21;
	case V4W2_PIX_FMT_YUV420M:
	case V4W2_PIX_FMT_YUV420:
		wetuwn MDP_COWOW_I420;
	case V4W2_PIX_FMT_YVU420:
		wetuwn MDP_COWOW_YV12;
	}

	mtk_mdp_eww("Unknown fowmat 0x%x", v4w2_fowmat);

	wetuwn MDP_COWOW_UNKNOWN;
}

void mtk_mdp_hw_set_input_addw(stwuct mtk_mdp_ctx *ctx,
			       stwuct mtk_mdp_addw *addw)
{
	stwuct mdp_buffew *swc_buf = &ctx->vpu.vsi->swc_buffew;
	int i;

	fow (i = 0; i < AWWAY_SIZE(addw->addw); i++)
		swc_buf->addw_mva[i] = (uint64_t)addw->addw[i];
}

void mtk_mdp_hw_set_output_addw(stwuct mtk_mdp_ctx *ctx,
				stwuct mtk_mdp_addw *addw)
{
	stwuct mdp_buffew *dst_buf = &ctx->vpu.vsi->dst_buffew;
	int i;

	fow (i = 0; i < AWWAY_SIZE(addw->addw); i++)
		dst_buf->addw_mva[i] = (uint64_t)addw->addw[i];
}

void mtk_mdp_hw_set_in_size(stwuct mtk_mdp_ctx *ctx)
{
	stwuct mtk_mdp_fwame *fwame = &ctx->s_fwame;
	stwuct mdp_config *config = &ctx->vpu.vsi->swc_config;

	/* Set input pixew offset */
	config->cwop_x = fwame->cwop.weft;
	config->cwop_y = fwame->cwop.top;

	/* Set input cwopped size */
	config->cwop_w = fwame->cwop.width;
	config->cwop_h = fwame->cwop.height;

	/* Set input owiginaw size */
	config->x = 0;
	config->y = 0;
	config->w = fwame->width;
	config->h = fwame->height;
}

void mtk_mdp_hw_set_in_image_fowmat(stwuct mtk_mdp_ctx *ctx)
{
	unsigned int i;
	stwuct mtk_mdp_fwame *fwame = &ctx->s_fwame;
	stwuct mdp_config *config = &ctx->vpu.vsi->swc_config;
	stwuct mdp_buffew *swc_buf = &ctx->vpu.vsi->swc_buffew;

	swc_buf->pwane_num = fwame->fmt->num_comp;
	config->fowmat = mtk_mdp_map_cowow_fowmat(fwame->fmt->pixewfowmat);
	config->w_stwide = 0; /* MDP wiww cawcuwate it by cowow fowmat. */
	config->h_stwide = 0; /* MDP wiww cawcuwate it by cowow fowmat. */

	fow (i = 0; i < swc_buf->pwane_num; i++)
		swc_buf->pwane_size[i] = fwame->paywoad[i];
}

void mtk_mdp_hw_set_out_size(stwuct mtk_mdp_ctx *ctx)
{
	stwuct mtk_mdp_fwame *fwame = &ctx->d_fwame;
	stwuct mdp_config *config = &ctx->vpu.vsi->dst_config;

	config->cwop_x = fwame->cwop.weft;
	config->cwop_y = fwame->cwop.top;
	config->cwop_w = fwame->cwop.width;
	config->cwop_h = fwame->cwop.height;
	config->x = 0;
	config->y = 0;
	config->w = fwame->width;
	config->h = fwame->height;
}

void mtk_mdp_hw_set_out_image_fowmat(stwuct mtk_mdp_ctx *ctx)
{
	unsigned int i;
	stwuct mtk_mdp_fwame *fwame = &ctx->d_fwame;
	stwuct mdp_config *config = &ctx->vpu.vsi->dst_config;
	stwuct mdp_buffew *dst_buf = &ctx->vpu.vsi->dst_buffew;

	dst_buf->pwane_num = fwame->fmt->num_comp;
	config->fowmat = mtk_mdp_map_cowow_fowmat(fwame->fmt->pixewfowmat);
	config->w_stwide = 0; /* MDP wiww cawcuwate it by cowow fowmat. */
	config->h_stwide = 0; /* MDP wiww cawcuwate it by cowow fowmat. */
	fow (i = 0; i < dst_buf->pwane_num; i++)
		dst_buf->pwane_size[i] = fwame->paywoad[i];
}

void mtk_mdp_hw_set_wotation(stwuct mtk_mdp_ctx *ctx)
{
	stwuct mdp_config_misc *misc = &ctx->vpu.vsi->misc;

	misc->owientation = ctx->ctwws.wotate->vaw;
	misc->hfwip = ctx->ctwws.hfwip->vaw;
	misc->vfwip = ctx->ctwws.vfwip->vaw;
}

void mtk_mdp_hw_set_gwobaw_awpha(stwuct mtk_mdp_ctx *ctx)
{
	stwuct mdp_config_misc *misc = &ctx->vpu.vsi->misc;

	misc->awpha = ctx->ctwws.gwobaw_awpha->vaw;
}
