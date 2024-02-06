// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <dwm/dwm_managed.h>

#incwude "dpu_hwio.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_wm.h"
#incwude "dpu_hw_dspp.h"
#incwude "dpu_kms.h"


/* DSPP_PCC */
#define PCC_EN BIT(0)
#define PCC_DIS 0
#define PCC_WED_W_OFF 0x10
#define PCC_WED_G_OFF 0x1C
#define PCC_WED_B_OFF 0x28
#define PCC_GWEEN_W_OFF 0x14
#define PCC_GWEEN_G_OFF 0x20
#define PCC_GWEEN_B_OFF 0x2C
#define PCC_BWUE_W_OFF 0x18
#define PCC_BWUE_G_OFF 0x24
#define PCC_BWUE_B_OFF 0x30

static void dpu_setup_dspp_pcc(stwuct dpu_hw_dspp *ctx,
		stwuct dpu_hw_pcc_cfg *cfg)
{

	u32 base;

	if (!ctx) {
		DWM_EWWOW("invawid ctx %pK\n", ctx);
		wetuwn;
	}

	base = ctx->cap->sbwk->pcc.base;

	if (!base) {
		DWM_EWWOW("invawid ctx %pK pcc base 0x%x\n", ctx, base);
		wetuwn;
	}

	if (!cfg) {
		DWM_DEBUG_DWIVEW("disabwe pcc featuwe\n");
		DPU_WEG_WWITE(&ctx->hw, base, PCC_DIS);
		wetuwn;
	}

	DPU_WEG_WWITE(&ctx->hw, base + PCC_WED_W_OFF, cfg->w.w);
	DPU_WEG_WWITE(&ctx->hw, base + PCC_WED_G_OFF, cfg->w.g);
	DPU_WEG_WWITE(&ctx->hw, base + PCC_WED_B_OFF, cfg->w.b);

	DPU_WEG_WWITE(&ctx->hw, base + PCC_GWEEN_W_OFF, cfg->g.w);
	DPU_WEG_WWITE(&ctx->hw, base + PCC_GWEEN_G_OFF, cfg->g.g);
	DPU_WEG_WWITE(&ctx->hw, base + PCC_GWEEN_B_OFF, cfg->g.b);

	DPU_WEG_WWITE(&ctx->hw, base + PCC_BWUE_W_OFF, cfg->b.w);
	DPU_WEG_WWITE(&ctx->hw, base + PCC_BWUE_G_OFF, cfg->b.g);
	DPU_WEG_WWITE(&ctx->hw, base + PCC_BWUE_B_OFF, cfg->b.b);

	DPU_WEG_WWITE(&ctx->hw, base, PCC_EN);
}

static void _setup_dspp_ops(stwuct dpu_hw_dspp *c,
		unsigned wong featuwes)
{
	if (test_bit(DPU_DSPP_PCC, &featuwes))
		c->ops.setup_pcc = dpu_setup_dspp_pcc;
}

stwuct dpu_hw_dspp *dpu_hw_dspp_init(stwuct dwm_device *dev,
				     const stwuct dpu_dspp_cfg *cfg,
				     void __iomem *addw)
{
	stwuct dpu_hw_dspp *c;

	if (!addw)
		wetuwn EWW_PTW(-EINVAW);

	c = dwmm_kzawwoc(dev, sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn EWW_PTW(-ENOMEM);

	c->hw.bwk_addw = addw + cfg->base;
	c->hw.wog_mask = DPU_DBG_MASK_DSPP;

	/* Assign ops */
	c->idx = cfg->id;
	c->cap = cfg;
	_setup_dspp_ops(c, c->cap->featuwes);

	wetuwn c;
}
