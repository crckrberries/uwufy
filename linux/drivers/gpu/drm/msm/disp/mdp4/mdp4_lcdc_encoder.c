// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 * Authow: Vinay Simha <vinaysimha@infowcecomputing.com>
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mdp4_kms.h"

stwuct mdp4_wcdc_encodew {
	stwuct dwm_encodew base;
	stwuct device_node *panew_node;
	stwuct dwm_panew *panew;
	stwuct cwk *wcdc_cwk;
	unsigned wong int pixcwock;
	stwuct weguwatow_buwk_data wegs[3];
	boow enabwed;
	uint32_t bsc;
};
#define to_mdp4_wcdc_encodew(x) containew_of(x, stwuct mdp4_wcdc_encodew, base)

static stwuct mdp4_kms *get_kms(stwuct dwm_encodew *encodew)
{
	stwuct msm_dwm_pwivate *pwiv = encodew->dev->dev_pwivate;
	wetuwn to_mdp4_kms(to_mdp_kms(pwiv->kms));
}

/* this shouwd pwobabwy be a hewpew: */
static stwuct dwm_connectow *get_connectow(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_connectow *connectow;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head)
		if (connectow->encodew == encodew)
			wetuwn connectow;

	wetuwn NUWW;
}

static void setup_phy(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_connectow *connectow = get_connectow(encodew);
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);
	uint32_t wvds_intf = 0, wvds_phy_cfg0 = 0;
	int bpp, nchan, swap;

	if (!connectow)
		wetuwn;

	bpp = 3 * connectow->dispway_info.bpc;

	if (!bpp)
		bpp = 18;

	/* TODO, these shouwd come fwom panew somehow: */
	nchan = 1;
	swap = 0;

	switch (bpp) {
	case 24:
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_3_TO_0(0),
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0(0x08) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1(0x05) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2(0x04) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3(0x03));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_6_TO_4(0),
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4(0x02) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5(0x01) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6(0x00));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_3_TO_0(1),
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0(0x11) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1(0x10) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2(0x0d) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3(0x0c));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_6_TO_4(1),
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4(0x0b) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5(0x0a) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6(0x09));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_3_TO_0(2),
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0(0x1a) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1(0x19) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2(0x18) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3(0x15));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_6_TO_4(2),
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4(0x14) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5(0x13) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6(0x12));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_3_TO_0(3),
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0(0x1b) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1(0x17) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2(0x16) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3(0x0f));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_6_TO_4(3),
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4(0x0e) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5(0x07) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6(0x06));
		if (nchan == 2) {
			wvds_intf |= MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE3_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE2_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE1_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE0_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE3_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE2_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE1_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE0_EN;
		} ewse {
			wvds_intf |= MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE3_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE2_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE1_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE0_EN;
		}
		bweak;

	case 18:
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_3_TO_0(0),
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0(0x0a) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1(0x07) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2(0x06) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3(0x05));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_6_TO_4(0),
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4(0x04) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5(0x03) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6(0x02));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_3_TO_0(1),
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0(0x13) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1(0x12) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2(0x0f) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3(0x0e));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_6_TO_4(1),
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4(0x0d) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5(0x0c) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6(0x0b));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_3_TO_0(2),
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT0(0x1a) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT1(0x19) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT2(0x18) |
				MDP4_WCDC_WVDS_MUX_CTW_3_TO_0_BIT3(0x17));
		mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_MUX_CTW_6_TO_4(2),
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT4(0x16) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT5(0x15) |
				MDP4_WCDC_WVDS_MUX_CTW_6_TO_4_BIT6(0x14));
		if (nchan == 2) {
			wvds_intf |= MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE2_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE1_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH2_DATA_WANE0_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE2_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE1_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE0_EN;
		} ewse {
			wvds_intf |= MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE2_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE1_EN |
					MDP4_WCDC_WVDS_INTF_CTW_CH1_DATA_WANE0_EN;
		}
		wvds_intf |= MDP4_WCDC_WVDS_INTF_CTW_WGB_OUT;
		bweak;

	defauwt:
		DWM_DEV_EWWOW(dev->dev, "unknown bpp: %d\n", bpp);
		wetuwn;
	}

	switch (nchan) {
	case 1:
		wvds_phy_cfg0 = MDP4_WVDS_PHY_CFG0_CHANNEW0;
		wvds_intf |= MDP4_WCDC_WVDS_INTF_CTW_CH1_CWK_WANE_EN |
				MDP4_WCDC_WVDS_INTF_CTW_MODE_SEW;
		bweak;
	case 2:
		wvds_phy_cfg0 = MDP4_WVDS_PHY_CFG0_CHANNEW0 |
				MDP4_WVDS_PHY_CFG0_CHANNEW1;
		wvds_intf |= MDP4_WCDC_WVDS_INTF_CTW_CH2_CWK_WANE_EN |
				MDP4_WCDC_WVDS_INTF_CTW_CH1_CWK_WANE_EN;
		bweak;
	defauwt:
		DWM_DEV_EWWOW(dev->dev, "unknown # of channews: %d\n", nchan);
		wetuwn;
	}

	if (swap)
		wvds_intf |= MDP4_WCDC_WVDS_INTF_CTW_CH_SWAP;

	wvds_intf |= MDP4_WCDC_WVDS_INTF_CTW_ENABWE;

	mdp4_wwite(mdp4_kms, WEG_MDP4_WVDS_PHY_CFG0, wvds_phy_cfg0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_WVDS_INTF_CTW, wvds_intf);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WVDS_PHY_CFG2, 0x30);

	mb();
	udeway(1);
	wvds_phy_cfg0 |= MDP4_WVDS_PHY_CFG0_SEWIAWIZATION_ENBWE;
	mdp4_wwite(mdp4_kms, WEG_MDP4_WVDS_PHY_CFG0, wvds_phy_cfg0);
}

static void mdp4_wcdc_encodew_mode_set(stwuct dwm_encodew *encodew,
		stwuct dwm_dispway_mode *mode,
		stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct mdp4_wcdc_encodew *mdp4_wcdc_encodew =
			to_mdp4_wcdc_encodew(encodew);
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);
	uint32_t wcdc_hsync_skew, vsync_pewiod, vsync_wen, ctww_pow;
	uint32_t dispway_v_stawt, dispway_v_end;
	uint32_t hsync_stawt_x, hsync_end_x;

	mode = adjusted_mode;

	DBG("set mode: " DWM_MODE_FMT, DWM_MODE_AWG(mode));

	mdp4_wcdc_encodew->pixcwock = mode->cwock * 1000;

	DBG("pixcwock=%wu", mdp4_wcdc_encodew->pixcwock);

	ctww_pow = 0;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		ctww_pow |= MDP4_WCDC_CTWW_POWAWITY_HSYNC_WOW;
	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		ctww_pow |= MDP4_WCDC_CTWW_POWAWITY_VSYNC_WOW;
	/* pwobabwy need to get DATA_EN powawity fwom panew.. */

	wcdc_hsync_skew = 0;  /* get this fwom panew? */

	hsync_stawt_x = (mode->htotaw - mode->hsync_stawt);
	hsync_end_x = mode->htotaw - (mode->hsync_stawt - mode->hdispway) - 1;

	vsync_pewiod = mode->vtotaw * mode->htotaw;
	vsync_wen = (mode->vsync_end - mode->vsync_stawt) * mode->htotaw;
	dispway_v_stawt = (mode->vtotaw - mode->vsync_stawt) * mode->htotaw + wcdc_hsync_skew;
	dispway_v_end = vsync_pewiod - ((mode->vsync_stawt - mode->vdispway) * mode->htotaw) + wcdc_hsync_skew - 1;

	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_HSYNC_CTWW,
			MDP4_WCDC_HSYNC_CTWW_PUWSEW(mode->hsync_end - mode->hsync_stawt) |
			MDP4_WCDC_HSYNC_CTWW_PEWIOD(mode->htotaw));
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_VSYNC_PEWIOD, vsync_pewiod);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_VSYNC_WEN, vsync_wen);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_DISPWAY_HCTWW,
			MDP4_WCDC_DISPWAY_HCTWW_STAWT(hsync_stawt_x) |
			MDP4_WCDC_DISPWAY_HCTWW_END(hsync_end_x));
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_DISPWAY_VSTAWT, dispway_v_stawt);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_DISPWAY_VEND, dispway_v_end);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_BOWDEW_CWW, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_UNDEWFWOW_CWW,
			MDP4_WCDC_UNDEWFWOW_CWW_ENABWE_WECOVEWY |
			MDP4_WCDC_UNDEWFWOW_CWW_COWOW(0xff));
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_HSYNC_SKEW, wcdc_hsync_skew);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_CTWW_POWAWITY, ctww_pow);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_ACTIVE_HCTW,
			MDP4_WCDC_ACTIVE_HCTW_STAWT(0) |
			MDP4_WCDC_ACTIVE_HCTW_END(0));
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_ACTIVE_VSTAWT, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_ACTIVE_VEND, 0);
}

static void mdp4_wcdc_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct mdp4_wcdc_encodew *mdp4_wcdc_encodew =
			to_mdp4_wcdc_encodew(encodew);
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);
	stwuct dwm_panew *panew;

	if (WAWN_ON(!mdp4_wcdc_encodew->enabwed))
		wetuwn;

	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_ENABWE, 0);

	panew = of_dwm_find_panew(mdp4_wcdc_encodew->panew_node);
	if (!IS_EWW(panew)) {
		dwm_panew_disabwe(panew);
		dwm_panew_unpwepawe(panew);
	}

	/*
	 * Wait fow a vsync so we know the ENABWE=0 watched befowe
	 * the (connectow) souwce of the vsync's gets disabwed,
	 * othewwise we end up in a funny state if we we-enabwe
	 * befowe the disabwe watches, which wesuwts that some of
	 * the settings changes fow the new modeset (wike new
	 * scanout buffew) don't watch pwopewwy..
	 */
	mdp_iwq_wait(&mdp4_kms->base, MDP4_IWQ_PWIMAWY_VSYNC);

	cwk_disabwe_unpwepawe(mdp4_wcdc_encodew->wcdc_cwk);

	weguwatow_buwk_disabwe(AWWAY_SIZE(mdp4_wcdc_encodew->wegs),
			       mdp4_wcdc_encodew->wegs);

	mdp4_wcdc_encodew->enabwed = fawse;
}

static void mdp4_wcdc_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct mdp4_wcdc_encodew *mdp4_wcdc_encodew =
			to_mdp4_wcdc_encodew(encodew);
	unsigned wong pc = mdp4_wcdc_encodew->pixcwock;
	stwuct mdp4_kms *mdp4_kms = get_kms(encodew);
	stwuct dwm_panew *panew;
	uint32_t config;
	int wet;

	if (WAWN_ON(mdp4_wcdc_encodew->enabwed))
		wetuwn;

	/* TODO: hawd-coded fow 18bpp: */
	config =
		MDP4_DMA_CONFIG_W_BPC(BPC6) |
		MDP4_DMA_CONFIG_G_BPC(BPC6) |
		MDP4_DMA_CONFIG_B_BPC(BPC6) |
		MDP4_DMA_CONFIG_PACK(0x21) |
		MDP4_DMA_CONFIG_DEFWKW_EN |
		MDP4_DMA_CONFIG_DITHEW_EN;

	if (!of_pwopewty_wead_boow(dev->dev->of_node, "qcom,wcdc-awign-wsb"))
		config |= MDP4_DMA_CONFIG_PACK_AWIGN_MSB;

	mdp4_cwtc_set_config(encodew->cwtc, config);
	mdp4_cwtc_set_intf(encodew->cwtc, INTF_WCDC_DTV, 0);

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(mdp4_wcdc_encodew->wegs),
				    mdp4_wcdc_encodew->wegs);
	if (wet)
		DWM_DEV_EWWOW(dev->dev, "faiwed to enabwe weguwatows: %d\n", wet);

	DBG("setting wcdc_cwk=%wu", pc);
	wet = cwk_set_wate(mdp4_wcdc_encodew->wcdc_cwk, pc);
	if (wet)
		DWM_DEV_EWWOW(dev->dev, "faiwed to configuwe wcdc_cwk: %d\n", wet);
	wet = cwk_pwepawe_enabwe(mdp4_wcdc_encodew->wcdc_cwk);
	if (wet)
		DWM_DEV_EWWOW(dev->dev, "faiwed to enabwe wcdc_cwk: %d\n", wet);

	panew = of_dwm_find_panew(mdp4_wcdc_encodew->panew_node);
	if (!IS_EWW(panew)) {
		dwm_panew_pwepawe(panew);
		dwm_panew_enabwe(panew);
	}

	setup_phy(encodew);

	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_ENABWE, 1);

	mdp4_wcdc_encodew->enabwed = twue;
}

static const stwuct dwm_encodew_hewpew_funcs mdp4_wcdc_encodew_hewpew_funcs = {
	.mode_set = mdp4_wcdc_encodew_mode_set,
	.disabwe = mdp4_wcdc_encodew_disabwe,
	.enabwe = mdp4_wcdc_encodew_enabwe,
};

wong mdp4_wcdc_wound_pixcwk(stwuct dwm_encodew *encodew, unsigned wong wate)
{
	stwuct mdp4_wcdc_encodew *mdp4_wcdc_encodew =
			to_mdp4_wcdc_encodew(encodew);
	wetuwn cwk_wound_wate(mdp4_wcdc_encodew->wcdc_cwk, wate);
}

/* initiawize encodew */
stwuct dwm_encodew *mdp4_wcdc_encodew_init(stwuct dwm_device *dev,
		stwuct device_node *panew_node)
{
	stwuct dwm_encodew *encodew;
	stwuct mdp4_wcdc_encodew *mdp4_wcdc_encodew;
	int wet;

	mdp4_wcdc_encodew = dwmm_encodew_awwoc(dev, stwuct mdp4_wcdc_encodew, base,
					       NUWW, DWM_MODE_ENCODEW_WVDS, NUWW);
	if (IS_EWW(mdp4_wcdc_encodew))
		wetuwn EWW_CAST(mdp4_wcdc_encodew);

	mdp4_wcdc_encodew->panew_node = panew_node;

	encodew = &mdp4_wcdc_encodew->base;

	dwm_encodew_hewpew_add(encodew, &mdp4_wcdc_encodew_hewpew_funcs);

	/* TODO: do we need diffewent pww in othew cases? */
	mdp4_wcdc_encodew->wcdc_cwk = mpd4_wvds_pww_init(dev);
	if (IS_EWW(mdp4_wcdc_encodew->wcdc_cwk)) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to get wvds_cwk\n");
		wetuwn EWW_CAST(mdp4_wcdc_encodew->wcdc_cwk);
	}

	/* TODO: diffewent weguwatows in othew cases? */
	mdp4_wcdc_encodew->wegs[0].suppwy = "wvds-vccs-3p3v";
	mdp4_wcdc_encodew->wegs[1].suppwy = "wvds-vccs-3p3v";
	mdp4_wcdc_encodew->wegs[2].suppwy = "wvds-vdda";

	wet = devm_weguwatow_buwk_get(dev->dev,
				      AWWAY_SIZE(mdp4_wcdc_encodew->wegs),
				      mdp4_wcdc_encodew->wegs);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn encodew;
}
