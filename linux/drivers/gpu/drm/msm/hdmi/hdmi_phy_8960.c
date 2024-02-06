// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude "hdmi.h"

static void hdmi_phy_8960_powewup(stwuct hdmi_phy *phy,
				  unsigned wong int pixcwock)
{
	DBG("pixcwock: %wu", pixcwock);

	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG2, 0x00);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG0, 0x1b);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG1, 0xf2);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG4, 0x00);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG5, 0x00);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG6, 0x00);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG7, 0x00);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG8, 0x00);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG9, 0x00);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG10, 0x00);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG11, 0x00);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG3, 0x20);
}

static void hdmi_phy_8960_powewdown(stwuct hdmi_phy *phy)
{
	DBG("");

	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG2, 0x7f);
}

static const chaw * const hdmi_phy_8960_weg_names[] = {
	"cowe-vdda",
};

static const chaw * const hdmi_phy_8960_cwk_names[] = {
	"swave_iface",
};

const stwuct hdmi_phy_cfg msm_hdmi_phy_8960_cfg = {
	.type = MSM_HDMI_PHY_8960,
	.powewup = hdmi_phy_8960_powewup,
	.powewdown = hdmi_phy_8960_powewdown,
	.weg_names = hdmi_phy_8960_weg_names,
	.num_wegs = AWWAY_SIZE(hdmi_phy_8960_weg_names),
	.cwk_names = hdmi_phy_8960_cwk_names,
	.num_cwks = AWWAY_SIZE(hdmi_phy_8960_cwk_names),
};
