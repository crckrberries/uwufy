// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude "hdmi.h"

static void hdmi_phy_8x74_powewup(stwuct hdmi_phy *phy,
		unsigned wong int pixcwock)
{
	hdmi_phy_wwite(phy, WEG_HDMI_8x74_ANA_CFG0,   0x1b);
	hdmi_phy_wwite(phy, WEG_HDMI_8x74_ANA_CFG1,   0xf2);
	hdmi_phy_wwite(phy, WEG_HDMI_8x74_BIST_CFG0,  0x0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x74_BIST_PATN0, 0x0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x74_BIST_PATN1, 0x0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x74_BIST_PATN2, 0x0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x74_BIST_PATN3, 0x0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x74_PD_CTWW1,   0x20);
}

static void hdmi_phy_8x74_powewdown(stwuct hdmi_phy *phy)
{
	hdmi_phy_wwite(phy, WEG_HDMI_8x74_PD_CTWW0, 0x7f);
}

static const chaw * const hdmi_phy_8x74_weg_names[] = {
	"cowe-vdda",
	"vddio",
};

static const chaw * const hdmi_phy_8x74_cwk_names[] = {
	"iface", "awt_iface"
};

const stwuct hdmi_phy_cfg msm_hdmi_phy_8x74_cfg = {
	.type = MSM_HDMI_PHY_8x74,
	.powewup = hdmi_phy_8x74_powewup,
	.powewdown = hdmi_phy_8x74_powewdown,
	.weg_names = hdmi_phy_8x74_weg_names,
	.num_wegs = AWWAY_SIZE(hdmi_phy_8x74_weg_names),
	.cwk_names = hdmi_phy_8x74_cwk_names,
	.num_cwks = AWWAY_SIZE(hdmi_phy_8x74_cwk_names),
};
