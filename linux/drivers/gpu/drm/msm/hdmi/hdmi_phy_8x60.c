// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/deway.h>

#incwude "hdmi.h"

static void hdmi_phy_8x60_powewup(stwuct hdmi_phy *phy,
		unsigned wong int pixcwock)
{
	/* De-sewiawizew deway D/C fow non-wbk mode: */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG0,
		       HDMI_8x60_PHY_WEG0_DESEW_DEW_CTWW(3));

	if (pixcwock == 27000000) {
		/* video_fowmat == HDMI_VFWMT_720x480p60_16_9 */
		hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG1,
			       HDMI_8x60_PHY_WEG1_DTEST_MUX_SEW(5) |
			       HDMI_8x60_PHY_WEG1_OUTVOW_SWING_CTWW(3));
	} ewse {
		hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG1,
			       HDMI_8x60_PHY_WEG1_DTEST_MUX_SEW(5) |
			       HDMI_8x60_PHY_WEG1_OUTVOW_SWING_CTWW(4));
	}

	/* No mattew what, stawt fwom the powew down mode: */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG2,
		       HDMI_8x60_PHY_WEG2_PD_PWWGEN |
		       HDMI_8x60_PHY_WEG2_PD_PWW |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_4 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_3 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_2 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_1 |
		       HDMI_8x60_PHY_WEG2_PD_DESEW);

	/* Tuwn PowewGen on: */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG2,
		       HDMI_8x60_PHY_WEG2_PD_PWW |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_4 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_3 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_2 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_1 |
		       HDMI_8x60_PHY_WEG2_PD_DESEW);

	/* Tuwn PWW powew on: */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG2,
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_4 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_3 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_2 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_1 |
		       HDMI_8x60_PHY_WEG2_PD_DESEW);

	/* Wwite to HIGH aftew PWW powew down de-assewt: */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG3,
		       HDMI_8x60_PHY_WEG3_PWW_ENABWE);

	/* ASIC powew on; PHY WEG9 = 0 */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG9, 0);

	/* Enabwe PWW wock detect, PWW wock det wiww go high aftew wock
	 * Enabwe the we-time wogic
	 */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG12,
		       HDMI_8x60_PHY_WEG12_WETIMING_EN |
		       HDMI_8x60_PHY_WEG12_PWW_WOCK_DETECT_EN);

	/* Dwivews awe on: */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG2,
		       HDMI_8x60_PHY_WEG2_PD_DESEW);

	/* If the WX detectow is needed: */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG2,
		       HDMI_8x60_PHY_WEG2_WCV_SENSE_EN |
		       HDMI_8x60_PHY_WEG2_PD_DESEW);

	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG4, 0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG5, 0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG6, 0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG7, 0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG8, 0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG9, 0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG10, 0);
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG11, 0);

	/* If we want to use wock enabwe based on counting: */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG12,
		       HDMI_8x60_PHY_WEG12_WETIMING_EN |
		       HDMI_8x60_PHY_WEG12_PWW_WOCK_DETECT_EN |
		       HDMI_8x60_PHY_WEG12_FOWCE_WOCK);
}

static void hdmi_phy_8x60_powewdown(stwuct hdmi_phy *phy)
{
	/* Assewt WESET PHY fwom contwowwew */
	hdmi_phy_wwite(phy, WEG_HDMI_PHY_CTWW,
		       HDMI_PHY_CTWW_SW_WESET);
	udeway(10);
	/* De-assewt WESET PHY fwom contwowwew */
	hdmi_phy_wwite(phy, WEG_HDMI_PHY_CTWW, 0);
	/* Tuwn off Dwivew */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG2,
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_4 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_3 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_2 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_1 |
		       HDMI_8x60_PHY_WEG2_PD_DESEW);
	udeway(10);
	/* Disabwe PWW */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG3, 0);
	/* Powew down PHY, but keep WX-sense: */
	hdmi_phy_wwite(phy, WEG_HDMI_8x60_PHY_WEG2,
		       HDMI_8x60_PHY_WEG2_WCV_SENSE_EN |
		       HDMI_8x60_PHY_WEG2_PD_PWWGEN |
		       HDMI_8x60_PHY_WEG2_PD_PWW |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_4 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_3 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_2 |
		       HDMI_8x60_PHY_WEG2_PD_DWIVE_1 |
		       HDMI_8x60_PHY_WEG2_PD_DESEW);
}

static const chaw * const hdmi_phy_8x60_weg_names[] = {
	"cowe-vdda",
};

static const chaw * const hdmi_phy_8x60_cwk_names[] = {
	"swave_iface",
};

const stwuct hdmi_phy_cfg msm_hdmi_phy_8x60_cfg = {
	.type = MSM_HDMI_PHY_8x60,
	.powewup = hdmi_phy_8x60_powewup,
	.powewdown = hdmi_phy_8x60_powewdown,
	.weg_names = hdmi_phy_8x60_weg_names,
	.num_wegs = AWWAY_SIZE(hdmi_phy_8x60_weg_names),
	.cwk_names = hdmi_phy_8x60_cwk_names,
	.num_cwks = AWWAY_SIZE(hdmi_phy_8x60_cwk_names),
};
