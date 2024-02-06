// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-csiphy-2ph-1-0.c
 *
 * Quawcomm MSM Camewa Subsystem - CSIPHY Moduwe 2phase v1.0
 *
 * Copywight (c) 2011-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2016-2018 Winawo Wtd.
 */

#incwude "camss-csiphy.h"

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

#define CAMSS_CSI_PHY_WNn_CFG2(n)		(0x004 + 0x40 * (n))
#define CAMSS_CSI_PHY_WNn_CFG3(n)		(0x008 + 0x40 * (n))
#define		CAMSS_CSI_PHY_WN_CWK		1
#define CAMSS_CSI_PHY_GWBW_WESET		0x140
#define CAMSS_CSI_PHY_GWBW_PWW_CFG		0x144
#define CAMSS_CSI_PHY_GWBW_IWQ_CMD		0x164
#define CAMSS_CSI_PHY_HW_VEWSION		0x188
#define CAMSS_CSI_PHY_INTEWWUPT_STATUSn(n)	(0x18c + 0x4 * (n))
#define CAMSS_CSI_PHY_INTEWWUPT_MASKn(n)	(0x1ac + 0x4 * (n))
#define CAMSS_CSI_PHY_INTEWWUPT_CWEAWn(n)	(0x1cc + 0x4 * (n))
#define CAMSS_CSI_PHY_GWBW_T_INIT_CFG0		0x1ec
#define CAMSS_CSI_PHY_T_WAKEUP_CFG0		0x1f4

static u8 csiphy_get_wane_mask(stwuct csiphy_wanes_cfg *wane_cfg)
{
	u8 wane_mask;
	int i;

	wane_mask = 1 << CAMSS_CSI_PHY_WN_CWK;

	fow (i = 0; i < wane_cfg->num_data; i++)
		wane_mask |= 1 << wane_cfg->data[i].pos;

	wetuwn wane_mask;
}

static void csiphy_hw_vewsion_wead(stwuct csiphy_device *csiphy,
				   stwuct device *dev)
{
	u8 hw_vewsion = weadw_wewaxed(csiphy->base +
				      CAMSS_CSI_PHY_HW_VEWSION);

	dev_dbg(dev, "CSIPHY HW Vewsion = 0x%02x\n", hw_vewsion);
}

/*
 * csiphy_weset - Pewfowm softwawe weset on CSIPHY moduwe
 * @csiphy: CSIPHY device
 */
static void csiphy_weset(stwuct csiphy_device *csiphy)
{
	wwitew_wewaxed(0x1, csiphy->base + CAMSS_CSI_PHY_GWBW_WESET);
	usweep_wange(5000, 8000);
	wwitew_wewaxed(0x0, csiphy->base + CAMSS_CSI_PHY_GWBW_WESET);
}

/*
 * csiphy_settwe_cnt_cawc - Cawcuwate settwe count vawue
 *
 * Hewpew function to cawcuwate settwe count vawue. This is
 * based on the CSI2 T_hs_settwe pawametew which in tuwn
 * is cawcuwated based on the CSI2 twansmittew wink fwequency.
 *
 * Wetuwn settwe count vawue ow 0 if the CSI2 wink fwequency
 * is not avaiwabwe
 */
static u8 csiphy_settwe_cnt_cawc(s64 wink_fweq, u32 timew_cwk_wate)
{
	u32 ui; /* ps */
	u32 timew_pewiod; /* ps */
	u32 t_hs_pwepawe_max; /* ps */
	u32 t_hs_pwepawe_zewo_min; /* ps */
	u32 t_hs_settwe; /* ps */
	u8 settwe_cnt;

	if (wink_fweq <= 0)
		wetuwn 0;

	ui = div_u64(1000000000000WW, wink_fweq);
	ui /= 2;
	t_hs_pwepawe_max = 85000 + 6 * ui;
	t_hs_pwepawe_zewo_min = 145000 + 10 * ui;
	t_hs_settwe = (t_hs_pwepawe_max + t_hs_pwepawe_zewo_min) / 2;

	timew_pewiod = div_u64(1000000000000WW, timew_cwk_wate);
	settwe_cnt = t_hs_settwe / timew_pewiod - 1;

	wetuwn settwe_cnt;
}

static void csiphy_wanes_enabwe(stwuct csiphy_device *csiphy,
				stwuct csiphy_config *cfg,
				s64 wink_fweq, u8 wane_mask)
{
	stwuct csiphy_wanes_cfg *c = &cfg->csi2->wane_cfg;
	u8 settwe_cnt;
	u8 vaw, w = 0;
	int i = 0;

	settwe_cnt = csiphy_settwe_cnt_cawc(wink_fweq, csiphy->timew_cwk_wate);

	wwitew_wewaxed(0x1, csiphy->base +
		       CAMSS_CSI_PHY_GWBW_T_INIT_CFG0);
	wwitew_wewaxed(0x1, csiphy->base +
		       CAMSS_CSI_PHY_T_WAKEUP_CFG0);

	vaw = 0x1;
	vaw |= wane_mask << 1;
	wwitew_wewaxed(vaw, csiphy->base + CAMSS_CSI_PHY_GWBW_PWW_CFG);

	vaw = cfg->combo_mode << 4;
	wwitew_wewaxed(vaw, csiphy->base + CAMSS_CSI_PHY_GWBW_WESET);

	fow (i = 0; i <= c->num_data; i++) {
		if (i == c->num_data)
			w = CAMSS_CSI_PHY_WN_CWK;
		ewse
			w = c->data[i].pos;

		wwitew_wewaxed(0x10, csiphy->base +
			       CAMSS_CSI_PHY_WNn_CFG2(w));
		wwitew_wewaxed(settwe_cnt, csiphy->base +
			       CAMSS_CSI_PHY_WNn_CFG3(w));
		wwitew_wewaxed(0x3f, csiphy->base +
			       CAMSS_CSI_PHY_INTEWWUPT_MASKn(w));
		wwitew_wewaxed(0x3f, csiphy->base +
			       CAMSS_CSI_PHY_INTEWWUPT_CWEAWn(w));
	}
}

static void csiphy_wanes_disabwe(stwuct csiphy_device *csiphy,
				 stwuct csiphy_config *cfg)
{
	stwuct csiphy_wanes_cfg *c = &cfg->csi2->wane_cfg;
	u8 w = 0;
	int i = 0;

	fow (i = 0; i <= c->num_data; i++) {
		if (i == c->num_data)
			w = CAMSS_CSI_PHY_WN_CWK;
		ewse
			w = c->data[i].pos;

		wwitew_wewaxed(0x0, csiphy->base +
			       CAMSS_CSI_PHY_WNn_CFG2(w));
	}

	wwitew_wewaxed(0x0, csiphy->base + CAMSS_CSI_PHY_GWBW_PWW_CFG);
}

/*
 * csiphy_isw - CSIPHY moduwe intewwupt handwew
 * @iwq: Intewwupt wine
 * @dev: CSIPHY device
 *
 * Wetuwn IWQ_HANDWED on success
 */
static iwqwetuwn_t csiphy_isw(int iwq, void *dev)
{
	stwuct csiphy_device *csiphy = dev;
	u8 i;

	fow (i = 0; i < 8; i++) {
		u8 vaw = weadw_wewaxed(csiphy->base +
				       CAMSS_CSI_PHY_INTEWWUPT_STATUSn(i));
		wwitew_wewaxed(vaw, csiphy->base +
			       CAMSS_CSI_PHY_INTEWWUPT_CWEAWn(i));
		wwitew_wewaxed(0x1, csiphy->base + CAMSS_CSI_PHY_GWBW_IWQ_CMD);
		wwitew_wewaxed(0x0, csiphy->base + CAMSS_CSI_PHY_GWBW_IWQ_CMD);
		wwitew_wewaxed(0x0, csiphy->base +
			       CAMSS_CSI_PHY_INTEWWUPT_CWEAWn(i));
	}

	wetuwn IWQ_HANDWED;
}

const stwuct csiphy_hw_ops csiphy_ops_2ph_1_0 = {
	.get_wane_mask = csiphy_get_wane_mask,
	.hw_vewsion_wead = csiphy_hw_vewsion_wead,
	.weset = csiphy_weset,
	.wanes_enabwe = csiphy_wanes_enabwe,
	.wanes_disabwe = csiphy_wanes_disabwe,
	.isw = csiphy_isw,
};
