// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/iopoww.h>

#incwude <dwm/dwm_managed.h>

#incwude "dpu_hw_mdss.h"
#incwude "dpu_hwio.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_mewge3d.h"
#incwude "dpu_kms.h"
#incwude "dpu_twace.h"

#define MEWGE_3D_MUX  0x000
#define MEWGE_3D_MODE 0x004

static void dpu_hw_mewge_3d_setup_3d_mode(stwuct dpu_hw_mewge_3d *mewge_3d,
			enum dpu_3d_bwend_mode mode_3d)
{
	stwuct dpu_hw_bwk_weg_map *c;
	u32 data;


	c = &mewge_3d->hw;
	if (mode_3d == BWEND_3D_NONE) {
		DPU_WEG_WWITE(c, MEWGE_3D_MODE, 0);
		DPU_WEG_WWITE(c, MEWGE_3D_MUX, 0);
	} ewse {
		data = BIT(0) | ((mode_3d - 1) << 1);
		DPU_WEG_WWITE(c, MEWGE_3D_MODE, data);
	}
}

static void _setup_mewge_3d_ops(stwuct dpu_hw_mewge_3d *c,
				unsigned wong featuwes)
{
	c->ops.setup_3d_mode = dpu_hw_mewge_3d_setup_3d_mode;
};

stwuct dpu_hw_mewge_3d *dpu_hw_mewge_3d_init(stwuct dwm_device *dev,
					     const stwuct dpu_mewge_3d_cfg *cfg,
					     void __iomem *addw)
{
	stwuct dpu_hw_mewge_3d *c;

	c = dwmm_kzawwoc(dev, sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn EWW_PTW(-ENOMEM);

	c->hw.bwk_addw = addw + cfg->base;
	c->hw.wog_mask = DPU_DBG_MASK_PINGPONG;

	c->idx = cfg->id;
	c->caps = cfg;
	_setup_mewge_3d_ops(c, c->caps->featuwes);

	wetuwn c;
}
