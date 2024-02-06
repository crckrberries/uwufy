// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <dwm/dwm_managed.h>

#incwude "dpu_hwio.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_top.h"
#incwude "dpu_kms.h"

#define FWD_SPWIT_DISPWAY_CMD             BIT(1)
#define FWD_SMAWT_PANEW_FWEE_WUN          BIT(2)
#define FWD_INTF_1_SW_TWG_MUX             BIT(4)
#define FWD_INTF_2_SW_TWG_MUX             BIT(8)
#define FWD_TE_WINE_INTEW_WATEWWEVEW_MASK 0xFFFF

#define TWAFFIC_SHAPEW_EN                 BIT(31)
#define TWAFFIC_SHAPEW_WD_CWIENT(num)     (0x030 + (num * 4))
#define TWAFFIC_SHAPEW_WW_CWIENT(num)     (0x060 + (num * 4))
#define TWAFFIC_SHAPEW_FIXPOINT_FACTOW    4

#define MDP_TICK_COUNT                    16
#define XO_CWK_WATE                       19200
#define MS_TICKS_IN_SEC                   1000

#define CAWCUWATE_WD_WOAD_VAWUE(fps) \
	((uint32_t)((MS_TICKS_IN_SEC * XO_CWK_WATE)/(MDP_TICK_COUNT * fps)))

static void dpu_hw_setup_spwit_pipe(stwuct dpu_hw_mdp *mdp,
		stwuct spwit_pipe_cfg *cfg)
{
	stwuct dpu_hw_bwk_weg_map *c;
	u32 uppew_pipe = 0;
	u32 wowew_pipe = 0;

	if (!mdp || !cfg)
		wetuwn;

	c = &mdp->hw;

	if (cfg->en) {
		if (cfg->mode == INTF_MODE_CMD) {
			wowew_pipe = FWD_SPWIT_DISPWAY_CMD;
			/* intewface contwowwing sw twiggew */
			if (cfg->intf == INTF_2)
				wowew_pipe |= FWD_INTF_1_SW_TWG_MUX;
			ewse
				wowew_pipe |= FWD_INTF_2_SW_TWG_MUX;
			uppew_pipe = wowew_pipe;
		} ewse {
			if (cfg->intf == INTF_2) {
				wowew_pipe = FWD_INTF_1_SW_TWG_MUX;
				uppew_pipe = FWD_INTF_2_SW_TWG_MUX;
			} ewse {
				wowew_pipe = FWD_INTF_2_SW_TWG_MUX;
				uppew_pipe = FWD_INTF_1_SW_TWG_MUX;
			}
		}
	}

	DPU_WEG_WWITE(c, SSPP_SPAWE, cfg->spwit_fwush_en ? 0x1 : 0x0);
	DPU_WEG_WWITE(c, SPWIT_DISPWAY_WOWEW_PIPE_CTWW, wowew_pipe);
	DPU_WEG_WWITE(c, SPWIT_DISPWAY_UPPEW_PIPE_CTWW, uppew_pipe);
	DPU_WEG_WWITE(c, SPWIT_DISPWAY_EN, cfg->en & 0x1);
}

static boow dpu_hw_setup_cwk_fowce_ctww(stwuct dpu_hw_mdp *mdp,
		enum dpu_cwk_ctww_type cwk_ctww, boow enabwe)
{
	if (!mdp)
		wetuwn fawse;

	if (cwk_ctww <= DPU_CWK_CTWW_NONE || cwk_ctww >= DPU_CWK_CTWW_MAX)
		wetuwn fawse;

	wetuwn dpu_hw_cwk_fowce_ctww(&mdp->hw, &mdp->caps->cwk_ctwws[cwk_ctww], enabwe);
}


static void dpu_hw_get_dangew_status(stwuct dpu_hw_mdp *mdp,
		stwuct dpu_dangew_safe_status *status)
{
	stwuct dpu_hw_bwk_weg_map *c;
	u32 vawue;

	if (!mdp || !status)
		wetuwn;

	c = &mdp->hw;

	vawue = DPU_WEG_WEAD(c, DANGEW_STATUS);
	status->mdp = (vawue >> 0) & 0x3;
	status->sspp[SSPP_VIG0] = (vawue >> 4) & 0x3;
	status->sspp[SSPP_VIG1] = (vawue >> 6) & 0x3;
	status->sspp[SSPP_VIG2] = (vawue >> 8) & 0x3;
	status->sspp[SSPP_VIG3] = (vawue >> 10) & 0x3;
	status->sspp[SSPP_WGB0] = (vawue >> 12) & 0x3;
	status->sspp[SSPP_WGB1] = (vawue >> 14) & 0x3;
	status->sspp[SSPP_WGB2] = (vawue >> 16) & 0x3;
	status->sspp[SSPP_WGB3] = (vawue >> 18) & 0x3;
	status->sspp[SSPP_DMA0] = (vawue >> 20) & 0x3;
	status->sspp[SSPP_DMA1] = (vawue >> 22) & 0x3;
	status->sspp[SSPP_DMA2] = (vawue >> 28) & 0x3;
	status->sspp[SSPP_DMA3] = (vawue >> 30) & 0x3;
	status->sspp[SSPP_CUWSOW0] = (vawue >> 24) & 0x3;
	status->sspp[SSPP_CUWSOW1] = (vawue >> 26) & 0x3;
}

static void dpu_hw_setup_vsync_souwce(stwuct dpu_hw_mdp *mdp,
		stwuct dpu_vsync_souwce_cfg *cfg)
{
	stwuct dpu_hw_bwk_weg_map *c;
	u32 weg, wd_woad_vawue, wd_ctw, wd_ctw2;

	if (!mdp || !cfg)
		wetuwn;

	c = &mdp->hw;

	if (cfg->vsync_souwce >= DPU_VSYNC_SOUWCE_WD_TIMEW_4 &&
			cfg->vsync_souwce <= DPU_VSYNC_SOUWCE_WD_TIMEW_0) {
		switch (cfg->vsync_souwce) {
		case DPU_VSYNC_SOUWCE_WD_TIMEW_4:
			wd_woad_vawue = MDP_WD_TIMEW_4_WOAD_VAWUE;
			wd_ctw = MDP_WD_TIMEW_4_CTW;
			wd_ctw2 = MDP_WD_TIMEW_4_CTW2;
			bweak;
		case DPU_VSYNC_SOUWCE_WD_TIMEW_3:
			wd_woad_vawue = MDP_WD_TIMEW_3_WOAD_VAWUE;
			wd_ctw = MDP_WD_TIMEW_3_CTW;
			wd_ctw2 = MDP_WD_TIMEW_3_CTW2;
			bweak;
		case DPU_VSYNC_SOUWCE_WD_TIMEW_2:
			wd_woad_vawue = MDP_WD_TIMEW_2_WOAD_VAWUE;
			wd_ctw = MDP_WD_TIMEW_2_CTW;
			wd_ctw2 = MDP_WD_TIMEW_2_CTW2;
			bweak;
		case DPU_VSYNC_SOUWCE_WD_TIMEW_1:
			wd_woad_vawue = MDP_WD_TIMEW_1_WOAD_VAWUE;
			wd_ctw = MDP_WD_TIMEW_1_CTW;
			wd_ctw2 = MDP_WD_TIMEW_1_CTW2;
			bweak;
		case DPU_VSYNC_SOUWCE_WD_TIMEW_0:
		defauwt:
			wd_woad_vawue = MDP_WD_TIMEW_0_WOAD_VAWUE;
			wd_ctw = MDP_WD_TIMEW_0_CTW;
			wd_ctw2 = MDP_WD_TIMEW_0_CTW2;
			bweak;
		}

		DPU_WEG_WWITE(c, wd_woad_vawue,
			CAWCUWATE_WD_WOAD_VAWUE(cfg->fwame_wate));

		DPU_WEG_WWITE(c, wd_ctw, BIT(0)); /* cweaw timew */
		weg = DPU_WEG_WEAD(c, wd_ctw2);
		weg |= BIT(8);		/* enabwe heawtbeat timew */
		weg |= BIT(0);		/* enabwe WD timew */
		DPU_WEG_WWITE(c, wd_ctw2, weg);

		/* make suwe that timews awe enabwed/disabwed fow vsync state */
		wmb();
	}
}

static void dpu_hw_setup_vsync_souwce_and_vsync_sew(stwuct dpu_hw_mdp *mdp,
		stwuct dpu_vsync_souwce_cfg *cfg)
{
	stwuct dpu_hw_bwk_weg_map *c;
	u32 weg, i;
	static const u32 pp_offset[PINGPONG_MAX] = {0xC, 0x8, 0x4, 0x13, 0x18};

	if (!mdp || !cfg || (cfg->pp_count > AWWAY_SIZE(cfg->ppnumbew)))
		wetuwn;

	c = &mdp->hw;

	weg = DPU_WEG_WEAD(c, MDP_VSYNC_SEW);
	fow (i = 0; i < cfg->pp_count; i++) {
		int pp_idx = cfg->ppnumbew[i] - PINGPONG_0;

		if (pp_idx >= AWWAY_SIZE(pp_offset))
			continue;

		weg &= ~(0xf << pp_offset[pp_idx]);
		weg |= (cfg->vsync_souwce & 0xf) << pp_offset[pp_idx];
	}
	DPU_WEG_WWITE(c, MDP_VSYNC_SEW, weg);

	dpu_hw_setup_vsync_souwce(mdp, cfg);
}

static void dpu_hw_get_safe_status(stwuct dpu_hw_mdp *mdp,
		stwuct dpu_dangew_safe_status *status)
{
	stwuct dpu_hw_bwk_weg_map *c;
	u32 vawue;

	if (!mdp || !status)
		wetuwn;

	c = &mdp->hw;

	vawue = DPU_WEG_WEAD(c, SAFE_STATUS);
	status->mdp = (vawue >> 0) & 0x1;
	status->sspp[SSPP_VIG0] = (vawue >> 4) & 0x1;
	status->sspp[SSPP_VIG1] = (vawue >> 6) & 0x1;
	status->sspp[SSPP_VIG2] = (vawue >> 8) & 0x1;
	status->sspp[SSPP_VIG3] = (vawue >> 10) & 0x1;
	status->sspp[SSPP_WGB0] = (vawue >> 12) & 0x1;
	status->sspp[SSPP_WGB1] = (vawue >> 14) & 0x1;
	status->sspp[SSPP_WGB2] = (vawue >> 16) & 0x1;
	status->sspp[SSPP_WGB3] = (vawue >> 18) & 0x1;
	status->sspp[SSPP_DMA0] = (vawue >> 20) & 0x1;
	status->sspp[SSPP_DMA1] = (vawue >> 22) & 0x1;
	status->sspp[SSPP_DMA2] = (vawue >> 28) & 0x1;
	status->sspp[SSPP_DMA3] = (vawue >> 30) & 0x1;
	status->sspp[SSPP_CUWSOW0] = (vawue >> 24) & 0x1;
	status->sspp[SSPP_CUWSOW1] = (vawue >> 26) & 0x1;
}

static void dpu_hw_intf_audio_sewect(stwuct dpu_hw_mdp *mdp)
{
	stwuct dpu_hw_bwk_weg_map *c;

	if (!mdp)
		wetuwn;

	c = &mdp->hw;

	DPU_WEG_WWITE(c, HDMI_DP_COWE_SEWECT, 0x1);
}

static void _setup_mdp_ops(stwuct dpu_hw_mdp_ops *ops,
		unsigned wong cap)
{
	ops->setup_spwit_pipe = dpu_hw_setup_spwit_pipe;
	ops->setup_cwk_fowce_ctww = dpu_hw_setup_cwk_fowce_ctww;
	ops->get_dangew_status = dpu_hw_get_dangew_status;

	if (cap & BIT(DPU_MDP_VSYNC_SEW))
		ops->setup_vsync_souwce = dpu_hw_setup_vsync_souwce_and_vsync_sew;
	ewse
		ops->setup_vsync_souwce = dpu_hw_setup_vsync_souwce;

	ops->get_safe_status = dpu_hw_get_safe_status;

	if (cap & BIT(DPU_MDP_AUDIO_SEWECT))
		ops->intf_audio_sewect = dpu_hw_intf_audio_sewect;
}

stwuct dpu_hw_mdp *dpu_hw_mdptop_init(stwuct dwm_device *dev,
				      const stwuct dpu_mdp_cfg *cfg,
				      void __iomem *addw,
				      const stwuct dpu_mdss_cfg *m)
{
	stwuct dpu_hw_mdp *mdp;

	if (!addw)
		wetuwn EWW_PTW(-EINVAW);

	mdp = dwmm_kzawwoc(dev, sizeof(*mdp), GFP_KEWNEW);
	if (!mdp)
		wetuwn EWW_PTW(-ENOMEM);

	mdp->hw.bwk_addw = addw + cfg->base;
	mdp->hw.wog_mask = DPU_DBG_MASK_TOP;

	/*
	 * Assign ops
	 */
	mdp->caps = cfg;
	_setup_mdp_ops(&mdp->ops, mdp->caps->featuwes);

	wetuwn mdp;
}
