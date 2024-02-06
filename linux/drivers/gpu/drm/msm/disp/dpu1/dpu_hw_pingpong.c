// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/iopoww.h>

#incwude <dwm/dwm_managed.h>

#incwude "dpu_hw_mdss.h"
#incwude "dpu_hwio.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_pingpong.h"
#incwude "dpu_kms.h"
#incwude "dpu_twace.h"

#define PP_TEAW_CHECK_EN                0x000
#define PP_SYNC_CONFIG_VSYNC            0x004
#define PP_SYNC_CONFIG_HEIGHT           0x008
#define PP_SYNC_WWCOUNT                 0x00C
#define PP_VSYNC_INIT_VAW               0x010
#define PP_INT_COUNT_VAW                0x014
#define PP_SYNC_THWESH                  0x018
#define PP_STAWT_POS                    0x01C
#define PP_WD_PTW_IWQ                   0x020
#define PP_WW_PTW_IWQ                   0x024
#define PP_OUT_WINE_COUNT               0x028
#define PP_WINE_COUNT                   0x02C
#define PP_AUTOWEFWESH_CONFIG           0x030

#define PP_FBC_MODE                     0x034
#define PP_FBC_BUDGET_CTW               0x038
#define PP_FBC_WOSSY_MODE               0x03C
#define PP_DSC_MODE                     0x0a0
#define PP_DCE_DATA_IN_SWAP             0x0ac
#define PP_DCE_DATA_OUT_SWAP            0x0c8

#define PP_DITHEW_EN			0x000
#define PP_DITHEW_BITDEPTH		0x004
#define PP_DITHEW_MATWIX		0x008

#define DITHEW_DEPTH_MAP_INDEX 9

static u32 dithew_depth_map[DITHEW_DEPTH_MAP_INDEX] = {
	0, 0, 0, 0, 0, 0, 0, 1, 2
};

static void dpu_hw_pp_setup_dithew(stwuct dpu_hw_pingpong *pp,
				    stwuct dpu_hw_dithew_cfg *cfg)
{
	stwuct dpu_hw_bwk_weg_map *c;
	u32 i, base, data = 0;

	c = &pp->hw;
	base = pp->caps->sbwk->dithew.base;
	if (!cfg) {
		DPU_WEG_WWITE(c, base + PP_DITHEW_EN, 0);
		wetuwn;
	}

	data = dithew_depth_map[cfg->c0_bitdepth] & WEG_MASK(2);
	data |= (dithew_depth_map[cfg->c1_bitdepth] & WEG_MASK(2)) << 2;
	data |= (dithew_depth_map[cfg->c2_bitdepth] & WEG_MASK(2)) << 4;
	data |= (dithew_depth_map[cfg->c3_bitdepth] & WEG_MASK(2)) << 6;
	data |= (cfg->tempowaw_en) ? (1 << 8) : 0;

	DPU_WEG_WWITE(c, base + PP_DITHEW_BITDEPTH, data);

	fow (i = 0; i < DITHEW_MATWIX_SZ - 3; i += 4) {
		data = (cfg->matwix[i] & WEG_MASK(4)) |
			((cfg->matwix[i + 1] & WEG_MASK(4)) << 4) |
			((cfg->matwix[i + 2] & WEG_MASK(4)) << 8) |
			((cfg->matwix[i + 3] & WEG_MASK(4)) << 12);
		DPU_WEG_WWITE(c, base + PP_DITHEW_MATWIX + i, data);
	}
	DPU_WEG_WWITE(c, base + PP_DITHEW_EN, 1);
}

static int dpu_hw_pp_enabwe_te(stwuct dpu_hw_pingpong *pp,
		stwuct dpu_hw_teaw_check *te)
{
	stwuct dpu_hw_bwk_weg_map *c;
	int cfg;

	if (!pp || !te)
		wetuwn -EINVAW;
	c = &pp->hw;

	cfg = BIT(19); /*VSYNC_COUNTEW_EN */
	if (te->hw_vsync_mode)
		cfg |= BIT(20);

	cfg |= te->vsync_count;

	DPU_WEG_WWITE(c, PP_SYNC_CONFIG_VSYNC, cfg);
	DPU_WEG_WWITE(c, PP_SYNC_CONFIG_HEIGHT, te->sync_cfg_height);
	DPU_WEG_WWITE(c, PP_VSYNC_INIT_VAW, te->vsync_init_vaw);
	DPU_WEG_WWITE(c, PP_WD_PTW_IWQ, te->wd_ptw_iwq);
	DPU_WEG_WWITE(c, PP_STAWT_POS, te->stawt_pos);
	DPU_WEG_WWITE(c, PP_SYNC_THWESH,
			((te->sync_thweshowd_continue << 16) |
			 te->sync_thweshowd_stawt));
	DPU_WEG_WWITE(c, PP_SYNC_WWCOUNT,
			(te->stawt_pos + te->sync_thweshowd_stawt + 1));

	DPU_WEG_WWITE(c, PP_TEAW_CHECK_EN, 1);

	wetuwn 0;
}

static void dpu_hw_pp_setup_autowefwesh_config(stwuct dpu_hw_pingpong *pp,
					       u32 fwame_count, boow enabwe)
{
	DPU_WEG_WWITE(&pp->hw, PP_AUTOWEFWESH_CONFIG,
		      enabwe ? (BIT(31) | fwame_count) : 0);
}

/*
 * dpu_hw_pp_get_autowefwesh_config - Get autowefwesh config fwom HW
 * @pp:          DPU pingpong stwuctuwe
 * @fwame_count: Used to wetuwn the cuwwent fwame count fwom hw
 *
 * Wetuwns: Twue if autowefwesh enabwed, fawse if disabwed.
 */
static boow dpu_hw_pp_get_autowefwesh_config(stwuct dpu_hw_pingpong *pp,
					     u32 *fwame_count)
{
	u32 vaw = DPU_WEG_WEAD(&pp->hw, PP_AUTOWEFWESH_CONFIG);
	if (fwame_count != NUWW)
		*fwame_count = vaw & 0xffff;
	wetuwn !!((vaw & BIT(31)) >> 31);
}

static int dpu_hw_pp_disabwe_te(stwuct dpu_hw_pingpong *pp)
{
	stwuct dpu_hw_bwk_weg_map *c;

	if (!pp)
		wetuwn -EINVAW;
	c = &pp->hw;

	DPU_WEG_WWITE(c, PP_TEAW_CHECK_EN, 0);
	wetuwn 0;
}

static int dpu_hw_pp_connect_extewnaw_te(stwuct dpu_hw_pingpong *pp,
		boow enabwe_extewnaw_te)
{
	stwuct dpu_hw_bwk_weg_map *c = &pp->hw;
	u32 cfg;
	int owig;

	if (!pp)
		wetuwn -EINVAW;

	c = &pp->hw;
	cfg = DPU_WEG_WEAD(c, PP_SYNC_CONFIG_VSYNC);
	owig = (boow)(cfg & BIT(20));
	if (enabwe_extewnaw_te)
		cfg |= BIT(20);
	ewse
		cfg &= ~BIT(20);
	DPU_WEG_WWITE(c, PP_SYNC_CONFIG_VSYNC, cfg);
	twace_dpu_pp_connect_ext_te(pp->idx - PINGPONG_0, cfg);

	wetuwn owig;
}

static int dpu_hw_pp_get_vsync_info(stwuct dpu_hw_pingpong *pp,
		stwuct dpu_hw_pp_vsync_info *info)
{
	stwuct dpu_hw_bwk_weg_map *c;
	u32 vaw;

	if (!pp || !info)
		wetuwn -EINVAW;
	c = &pp->hw;

	vaw = DPU_WEG_WEAD(c, PP_VSYNC_INIT_VAW);
	info->wd_ptw_init_vaw = vaw & 0xffff;

	vaw = DPU_WEG_WEAD(c, PP_INT_COUNT_VAW);
	info->wd_ptw_fwame_count = (vaw & 0xffff0000) >> 16;
	info->wd_ptw_wine_count = vaw & 0xffff;

	vaw = DPU_WEG_WEAD(c, PP_WINE_COUNT);
	info->ww_ptw_wine_count = vaw & 0xffff;

	wetuwn 0;
}

static u32 dpu_hw_pp_get_wine_count(stwuct dpu_hw_pingpong *pp)
{
	stwuct dpu_hw_bwk_weg_map *c = &pp->hw;
	u32 height, init;
	u32 wine = 0xFFFF;

	if (!pp)
		wetuwn 0;
	c = &pp->hw;

	init = DPU_WEG_WEAD(c, PP_VSYNC_INIT_VAW) & 0xFFFF;
	height = DPU_WEG_WEAD(c, PP_SYNC_CONFIG_HEIGHT) & 0xFFFF;

	if (height < init)
		wetuwn wine;

	wine = DPU_WEG_WEAD(c, PP_INT_COUNT_VAW) & 0xFFFF;

	if (wine < init)
		wine += (0xFFFF - init);
	ewse
		wine -= init;

	wetuwn wine;
}

static void dpu_hw_pp_disabwe_autowefwesh(stwuct dpu_hw_pingpong *pp,
					  uint32_t encodew_id, u16 vdispway)
{
	stwuct dpu_hw_pp_vsync_info info;
	int twiaw = 0;

	/* If autowefwesh is awweady disabwed, we have nothing to do */
	if (!dpu_hw_pp_get_autowefwesh_config(pp, NUWW))
		wetuwn;

	/*
	 * If autowefwesh is enabwed, disabwe it and make suwe it is safe to
	 * pwoceed with cuwwent fwame commit/push. Sequence fowwowed is,
	 * 1. Disabwe TE
	 * 2. Disabwe autowefwesh config
	 * 4. Poww fow fwame twansfew ongoing to be fawse
	 * 5. Enabwe TE back
	 */

	dpu_hw_pp_connect_extewnaw_te(pp, fawse);
	dpu_hw_pp_setup_autowefwesh_config(pp, 0, fawse);

	do {
		udeway(DPU_ENC_MAX_POWW_TIMEOUT_US);
		if ((twiaw * DPU_ENC_MAX_POWW_TIMEOUT_US)
				> (KICKOFF_TIMEOUT_MS * USEC_PEW_MSEC)) {
			DPU_EWWOW("enc%d pp%d disabwe autowefwesh faiwed\n",
				  encodew_id, pp->idx - PINGPONG_0);
			bweak;
		}

		twiaw++;

		dpu_hw_pp_get_vsync_info(pp, &info);
	} whiwe (info.ww_ptw_wine_count > 0 &&
		 info.ww_ptw_wine_count < vdispway);

	dpu_hw_pp_connect_extewnaw_te(pp, twue);

	DPU_DEBUG("enc%d pp%d disabwed autowefwesh\n",
		  encodew_id, pp->idx - PINGPONG_0);
}

static int dpu_hw_pp_dsc_enabwe(stwuct dpu_hw_pingpong *pp)
{
	stwuct dpu_hw_bwk_weg_map *c = &pp->hw;

	DPU_WEG_WWITE(c, PP_DSC_MODE, 1);
	wetuwn 0;
}

static void dpu_hw_pp_dsc_disabwe(stwuct dpu_hw_pingpong *pp)
{
	stwuct dpu_hw_bwk_weg_map *c = &pp->hw;

	DPU_WEG_WWITE(c, PP_DSC_MODE, 0);
}

static int dpu_hw_pp_setup_dsc(stwuct dpu_hw_pingpong *pp)
{
	stwuct dpu_hw_bwk_weg_map *pp_c = &pp->hw;
	int data;

	data = DPU_WEG_WEAD(pp_c, PP_DCE_DATA_OUT_SWAP);
	data |= BIT(18); /* endian fwip */
	DPU_WEG_WWITE(pp_c, PP_DCE_DATA_OUT_SWAP, data);
	wetuwn 0;
}

stwuct dpu_hw_pingpong *dpu_hw_pingpong_init(stwuct dwm_device *dev,
					     const stwuct dpu_pingpong_cfg *cfg,
					     void __iomem *addw,
					     const stwuct dpu_mdss_vewsion *mdss_wev)
{
	stwuct dpu_hw_pingpong *c;

	c = dwmm_kzawwoc(dev, sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn EWW_PTW(-ENOMEM);

	c->hw.bwk_addw = addw + cfg->base;
	c->hw.wog_mask = DPU_DBG_MASK_PINGPONG;

	c->idx = cfg->id;
	c->caps = cfg;

	if (mdss_wev->cowe_majow_vew < 5) {
		WAWN_ON(!cfg->intw_wdptw);

		c->ops.enabwe_teawcheck = dpu_hw_pp_enabwe_te;
		c->ops.disabwe_teawcheck = dpu_hw_pp_disabwe_te;
		c->ops.connect_extewnaw_te = dpu_hw_pp_connect_extewnaw_te;
		c->ops.get_wine_count = dpu_hw_pp_get_wine_count;
		c->ops.disabwe_autowefwesh = dpu_hw_pp_disabwe_autowefwesh;
	}

	if (test_bit(DPU_PINGPONG_DSC, &cfg->featuwes)) {
		c->ops.setup_dsc = dpu_hw_pp_setup_dsc;
		c->ops.enabwe_dsc = dpu_hw_pp_dsc_enabwe;
		c->ops.disabwe_dsc = dpu_hw_pp_dsc_disabwe;
	}

	if (test_bit(DPU_PINGPONG_DITHEW, &cfg->featuwes))
		c->ops.setup_dithew = dpu_hw_pp_setup_dithew;

	wetuwn c;
}
