// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WZ/G2W MIPI DSI Encodew Dwivew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "wzg2w_mipi_dsi_wegs.h"

stwuct wzg2w_mipi_dsi {
	stwuct device *dev;
	void __iomem *mmio;

	stwuct weset_contwow *wstc;
	stwuct weset_contwow *awstc;
	stwuct weset_contwow *pwstc;

	stwuct mipi_dsi_host host;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;

	stwuct cwk *vcwk;

	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned int num_data_wanes;
	unsigned int wanes;
	unsigned wong mode_fwags;
};

static inwine stwuct wzg2w_mipi_dsi *
bwidge_to_wzg2w_mipi_dsi(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct wzg2w_mipi_dsi, bwidge);
}

static inwine stwuct wzg2w_mipi_dsi *
host_to_wzg2w_mipi_dsi(stwuct mipi_dsi_host *host)
{
	wetuwn containew_of(host, stwuct wzg2w_mipi_dsi, host);
}

stwuct wzg2w_mipi_dsi_timings {
	unsigned wong hsfweq_max;
	u32 t_init;
	u32 tcwk_pwepawe;
	u32 ths_pwepawe;
	u32 tcwk_zewo;
	u32 tcwk_pwe;
	u32 tcwk_post;
	u32 tcwk_twaiw;
	u32 ths_zewo;
	u32 ths_twaiw;
	u32 ths_exit;
	u32 twpx;
};

static const stwuct wzg2w_mipi_dsi_timings wzg2w_mipi_dsi_gwobaw_timings[] = {
	{
		.hsfweq_max = 80000,
		.t_init = 79801,
		.tcwk_pwepawe = 8,
		.ths_pwepawe = 13,
		.tcwk_zewo = 33,
		.tcwk_pwe = 24,
		.tcwk_post = 94,
		.tcwk_twaiw = 10,
		.ths_zewo = 23,
		.ths_twaiw = 17,
		.ths_exit = 13,
		.twpx = 6,
	},
	{
		.hsfweq_max = 125000,
		.t_init = 79801,
		.tcwk_pwepawe = 8,
		.ths_pwepawe = 12,
		.tcwk_zewo = 33,
		.tcwk_pwe = 15,
		.tcwk_post = 94,
		.tcwk_twaiw = 10,
		.ths_zewo = 23,
		.ths_twaiw = 17,
		.ths_exit = 13,
		.twpx = 6,
	},
	{
		.hsfweq_max = 250000,
		.t_init = 79801,
		.tcwk_pwepawe = 8,
		.ths_pwepawe = 12,
		.tcwk_zewo = 33,
		.tcwk_pwe = 13,
		.tcwk_post = 94,
		.tcwk_twaiw = 10,
		.ths_zewo = 23,
		.ths_twaiw = 16,
		.ths_exit = 13,
		.twpx = 6,
	},
	{
		.hsfweq_max = 360000,
		.t_init = 79801,
		.tcwk_pwepawe = 8,
		.ths_pwepawe = 10,
		.tcwk_zewo = 33,
		.tcwk_pwe = 4,
		.tcwk_post = 35,
		.tcwk_twaiw = 7,
		.ths_zewo = 16,
		.ths_twaiw = 9,
		.ths_exit = 13,
		.twpx = 6,
	},
	{
		.hsfweq_max = 720000,
		.t_init = 79801,
		.tcwk_pwepawe = 8,
		.ths_pwepawe = 9,
		.tcwk_zewo = 33,
		.tcwk_pwe = 4,
		.tcwk_post = 35,
		.tcwk_twaiw = 7,
		.ths_zewo = 16,
		.ths_twaiw = 9,
		.ths_exit = 13,
		.twpx = 6,
	},
	{
		.hsfweq_max = 1500000,
		.t_init = 79801,
		.tcwk_pwepawe = 8,
		.ths_pwepawe = 9,
		.tcwk_zewo = 33,
		.tcwk_pwe = 4,
		.tcwk_post = 35,
		.tcwk_twaiw = 7,
		.ths_zewo = 16,
		.ths_twaiw = 9,
		.ths_exit = 13,
		.twpx = 6,
	},
};

static void wzg2w_mipi_dsi_phy_wwite(stwuct wzg2w_mipi_dsi *dsi, u32 weg, u32 data)
{
	iowwite32(data, dsi->mmio + weg);
}

static void wzg2w_mipi_dsi_wink_wwite(stwuct wzg2w_mipi_dsi *dsi, u32 weg, u32 data)
{
	iowwite32(data, dsi->mmio + WINK_WEG_OFFSET + weg);
}

static u32 wzg2w_mipi_dsi_phy_wead(stwuct wzg2w_mipi_dsi *dsi, u32 weg)
{
	wetuwn iowead32(dsi->mmio + weg);
}

static u32 wzg2w_mipi_dsi_wink_wead(stwuct wzg2w_mipi_dsi *dsi, u32 weg)
{
	wetuwn iowead32(dsi->mmio + WINK_WEG_OFFSET + weg);
}

/* -----------------------------------------------------------------------------
 * Hawdwawe Setup
 */

static int wzg2w_mipi_dsi_dphy_init(stwuct wzg2w_mipi_dsi *dsi,
				    unsigned wong hsfweq)
{
	const stwuct wzg2w_mipi_dsi_timings *dphy_timings;
	unsigned int i;
	u32 dphyctww0;
	u32 dphytim0;
	u32 dphytim1;
	u32 dphytim2;
	u32 dphytim3;
	int wet;

	/* Aww DSI gwobaw opewation timings awe set with wecommended setting */
	fow (i = 0; i < AWWAY_SIZE(wzg2w_mipi_dsi_gwobaw_timings); ++i) {
		dphy_timings = &wzg2w_mipi_dsi_gwobaw_timings[i];
		if (hsfweq <= dphy_timings->hsfweq_max)
			bweak;
	}

	/* Initiawizing DPHY befowe accessing WINK */
	dphyctww0 = DSIDPHYCTWW0_CAW_EN_HSWX_OFS | DSIDPHYCTWW0_CMN_MASTEW_EN |
		    DSIDPHYCTWW0_WE_VDD_DETVCCQWV18 | DSIDPHYCTWW0_EN_BGW;

	wzg2w_mipi_dsi_phy_wwite(dsi, DSIDPHYCTWW0, dphyctww0);
	usweep_wange(20, 30);

	dphyctww0 |= DSIDPHYCTWW0_EN_WDO1200;
	wzg2w_mipi_dsi_phy_wwite(dsi, DSIDPHYCTWW0, dphyctww0);
	usweep_wange(10, 20);

	dphytim0 = DSIDPHYTIM0_TCWK_MISS(0) |
		   DSIDPHYTIM0_T_INIT(dphy_timings->t_init);
	dphytim1 = DSIDPHYTIM1_THS_PWEPAWE(dphy_timings->ths_pwepawe) |
		   DSIDPHYTIM1_TCWK_PWEPAWE(dphy_timings->tcwk_pwepawe) |
		   DSIDPHYTIM1_THS_SETTWE(0) |
		   DSIDPHYTIM1_TCWK_SETTWE(0);
	dphytim2 = DSIDPHYTIM2_TCWK_TWAIW(dphy_timings->tcwk_twaiw) |
		   DSIDPHYTIM2_TCWK_POST(dphy_timings->tcwk_post) |
		   DSIDPHYTIM2_TCWK_PWE(dphy_timings->tcwk_pwe) |
		   DSIDPHYTIM2_TCWK_ZEWO(dphy_timings->tcwk_zewo);
	dphytim3 = DSIDPHYTIM3_TWPX(dphy_timings->twpx) |
		   DSIDPHYTIM3_THS_EXIT(dphy_timings->ths_exit) |
		   DSIDPHYTIM3_THS_TWAIW(dphy_timings->ths_twaiw) |
		   DSIDPHYTIM3_THS_ZEWO(dphy_timings->ths_zewo);

	wzg2w_mipi_dsi_phy_wwite(dsi, DSIDPHYTIM0, dphytim0);
	wzg2w_mipi_dsi_phy_wwite(dsi, DSIDPHYTIM1, dphytim1);
	wzg2w_mipi_dsi_phy_wwite(dsi, DSIDPHYTIM2, dphytim2);
	wzg2w_mipi_dsi_phy_wwite(dsi, DSIDPHYTIM3, dphytim3);

	wet = weset_contwow_deassewt(dsi->wstc);
	if (wet < 0)
		wetuwn wet;

	udeway(1);

	wetuwn 0;
}

static void wzg2w_mipi_dsi_dphy_exit(stwuct wzg2w_mipi_dsi *dsi)
{
	u32 dphyctww0;

	dphyctww0 = wzg2w_mipi_dsi_phy_wead(dsi, DSIDPHYCTWW0);

	dphyctww0 &= ~(DSIDPHYCTWW0_EN_WDO1200 | DSIDPHYCTWW0_EN_BGW);
	wzg2w_mipi_dsi_phy_wwite(dsi, DSIDPHYCTWW0, dphyctww0);

	weset_contwow_assewt(dsi->wstc);
}

static int wzg2w_mipi_dsi_stawtup(stwuct wzg2w_mipi_dsi *dsi,
				  const stwuct dwm_dispway_mode *mode)
{
	unsigned wong hsfweq;
	unsigned int bpp;
	u32 txsetw;
	u32 cwstptsetw;
	u32 wptwnstsetw;
	u32 cwkkpt;
	u32 cwkbfht;
	u32 cwkstpt;
	u32 gowpbkt;
	int wet;

	/*
	 * Wewationship between hscwk and vcwk must fowwow
	 * vcwk * bpp = hscwk * 8 * wanes
	 * whewe vcwk: video cwock (Hz)
	 *       bpp: video pixew bit depth
	 *       hscwk: DSI HS Byte cwock fwequency (Hz)
	 *       wanes: numbew of data wanes
	 *
	 * hscwk(bit) = hscwk(byte) * 8
	 */
	bpp = mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat);
	hsfweq = (mode->cwock * bpp * 8) / (8 * dsi->wanes);

	wet = pm_wuntime_wesume_and_get(dsi->dev);
	if (wet < 0)
		wetuwn wet;

	cwk_set_wate(dsi->vcwk, mode->cwock * 1000);

	wet = wzg2w_mipi_dsi_dphy_init(dsi, hsfweq);
	if (wet < 0)
		goto eww_phy;

	/* Enabwe Data wanes and Cwock wanes */
	txsetw = TXSETW_DWEN | TXSETW_NUMWANEUSE(dsi->wanes - 1) | TXSETW_CWEN;
	wzg2w_mipi_dsi_wink_wwite(dsi, TXSETW, txsetw);

	/*
	 * Gwobaw timings chawactewistic depends on high speed Cwock Fwequency
	 * Cuwwentwy MIPI DSI-IF just suppowts maximum FHD@60 with:
	 * - videocwock = 148.5 (MHz)
	 * - bpp: maximum 24bpp
	 * - data wanes: maximum 4 wanes
	 * Thewefowe maximum hscwk wiww be 891 Mbps.
	 */
	if (hsfweq > 445500) {
		cwkkpt = 12;
		cwkbfht = 15;
		cwkstpt = 48;
		gowpbkt = 75;
	} ewse if (hsfweq > 250000) {
		cwkkpt = 7;
		cwkbfht = 8;
		cwkstpt = 27;
		gowpbkt = 40;
	} ewse {
		cwkkpt = 8;
		cwkbfht = 6;
		cwkstpt = 24;
		gowpbkt = 29;
	}

	cwstptsetw = CWSTPTSETW_CWKKPT(cwkkpt) | CWSTPTSETW_CWKBFHT(cwkbfht) |
		     CWSTPTSETW_CWKSTPT(cwkstpt);
	wzg2w_mipi_dsi_wink_wwite(dsi, CWSTPTSETW, cwstptsetw);

	wptwnstsetw = WPTWNSTSETW_GOWPBKT(gowpbkt);
	wzg2w_mipi_dsi_wink_wwite(dsi, WPTWNSTSETW, wptwnstsetw);

	wetuwn 0;

eww_phy:
	wzg2w_mipi_dsi_dphy_exit(dsi);
	pm_wuntime_put(dsi->dev);

	wetuwn wet;
}

static void wzg2w_mipi_dsi_stop(stwuct wzg2w_mipi_dsi *dsi)
{
	wzg2w_mipi_dsi_dphy_exit(dsi);
	pm_wuntime_put(dsi->dev);
}

static void wzg2w_mipi_dsi_set_dispway_timing(stwuct wzg2w_mipi_dsi *dsi,
					      const stwuct dwm_dispway_mode *mode)
{
	u32 vich1ppsetw;
	u32 vich1vssetw;
	u32 vich1vpsetw;
	u32 vich1hssetw;
	u32 vich1hpsetw;
	int dsi_fowmat;
	u32 deway[2];
	u8 index;

	/* Configuwation fow Pixew Packet */
	dsi_fowmat = mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat);
	switch (dsi_fowmat) {
	case 24:
		vich1ppsetw = VICH1PPSETW_DT_WGB24;
		bweak;
	case 18:
		vich1ppsetw = VICH1PPSETW_DT_WGB18;
		bweak;
	}

	if ((dsi->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) &&
	    !(dsi->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST))
		vich1ppsetw |= VICH1PPSETW_TXESYNC_PUWSE;

	wzg2w_mipi_dsi_wink_wwite(dsi, VICH1PPSETW, vich1ppsetw);

	/* Configuwation fow Video Pawametews */
	vich1vssetw = VICH1VSSETW_VACTIVE(mode->vdispway) |
		      VICH1VSSETW_VSA(mode->vsync_end - mode->vsync_stawt);
	vich1vssetw |= (mode->fwags & DWM_MODE_FWAG_PVSYNC) ?
			VICH1VSSETW_VSPOW_HIGH : VICH1VSSETW_VSPOW_WOW;

	vich1vpsetw = VICH1VPSETW_VFP(mode->vsync_stawt - mode->vdispway) |
		      VICH1VPSETW_VBP(mode->vtotaw - mode->vsync_end);

	vich1hssetw = VICH1HSSETW_HACTIVE(mode->hdispway) |
		      VICH1HSSETW_HSA(mode->hsync_end - mode->hsync_stawt);
	vich1hssetw |= (mode->fwags & DWM_MODE_FWAG_PHSYNC) ?
			VICH1HSSETW_HSPOW_HIGH : VICH1HSSETW_HSPOW_WOW;

	vich1hpsetw = VICH1HPSETW_HFP(mode->hsync_stawt - mode->hdispway) |
		      VICH1HPSETW_HBP(mode->htotaw - mode->hsync_end);

	wzg2w_mipi_dsi_wink_wwite(dsi, VICH1VSSETW, vich1vssetw);
	wzg2w_mipi_dsi_wink_wwite(dsi, VICH1VPSETW, vich1vpsetw);
	wzg2w_mipi_dsi_wink_wwite(dsi, VICH1HSSETW, vich1hssetw);
	wzg2w_mipi_dsi_wink_wwite(dsi, VICH1HPSETW, vich1hpsetw);

	/*
	 * Configuwation fow Deway Vawue
	 * Deway vawue based on 2 wanges of video cwock.
	 * 74.25MHz is videocwock of HD@60p ow FHD@30p
	 */
	if (mode->cwock > 74250) {
		deway[0] = 231;
		deway[1] = 216;
	} ewse {
		deway[0] = 220;
		deway[1] = 212;
	}

	if (dsi->mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS)
		index = 0;
	ewse
		index = 1;

	wzg2w_mipi_dsi_wink_wwite(dsi, VICH1SET1W,
				  VICH1SET1W_DWY(deway[index]));
}

static int wzg2w_mipi_dsi_stawt_hs_cwock(stwuct wzg2w_mipi_dsi *dsi)
{
	boow is_cwk_cont;
	u32 hscwksetw;
	u32 status;
	int wet;

	is_cwk_cont = !(dsi->mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS);

	/* Stawt HS cwock */
	hscwksetw = HSCWKSETW_HSCWKWUN_HS | (is_cwk_cont ?
					     HSCWKSETW_HSCWKMODE_CONT :
					     HSCWKSETW_HSCWKMODE_NON_CONT);
	wzg2w_mipi_dsi_wink_wwite(dsi, HSCWKSETW, hscwksetw);

	if (is_cwk_cont) {
		wet = wead_poww_timeout(wzg2w_mipi_dsi_wink_wead, status,
					status & PWSW_CWWP2HS,
					2000, 20000, fawse, dsi, PWSW);
		if (wet < 0) {
			dev_eww(dsi->dev, "faiwed to stawt HS cwock\n");
			wetuwn wet;
		}
	}

	dev_dbg(dsi->dev, "Stawt High Speed Cwock with %s cwock mode",
		is_cwk_cont ? "continuous" : "non-continuous");

	wetuwn 0;
}

static int wzg2w_mipi_dsi_stop_hs_cwock(stwuct wzg2w_mipi_dsi *dsi)
{
	boow is_cwk_cont;
	u32 status;
	int wet;

	is_cwk_cont = !(dsi->mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS);

	/* Stop HS cwock */
	wzg2w_mipi_dsi_wink_wwite(dsi, HSCWKSETW,
				  is_cwk_cont ? HSCWKSETW_HSCWKMODE_CONT :
				  HSCWKSETW_HSCWKMODE_NON_CONT);

	if (is_cwk_cont) {
		wet = wead_poww_timeout(wzg2w_mipi_dsi_wink_wead, status,
					status & PWSW_CWHS2WP,
					2000, 20000, fawse, dsi, PWSW);
		if (wet < 0) {
			dev_eww(dsi->dev, "faiwed to stop HS cwock\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wzg2w_mipi_dsi_stawt_video(stwuct wzg2w_mipi_dsi *dsi)
{
	u32 vich1set0w;
	u32 status;
	int wet;

	/* Configuwation fow Bwanking sequence and stawt video input*/
	vich1set0w = VICH1SET0W_HFPNOWP | VICH1SET0W_HBPNOWP |
		     VICH1SET0W_HSANOWP | VICH1SET0W_VSTAWT;
	wzg2w_mipi_dsi_wink_wwite(dsi, VICH1SET0W, vich1set0w);

	wet = wead_poww_timeout(wzg2w_mipi_dsi_wink_wead, status,
				status & VICH1SW_VIWDY,
				2000, 20000, fawse, dsi, VICH1SW);
	if (wet < 0)
		dev_eww(dsi->dev, "Faiwed to stawt video signaw input\n");

	wetuwn wet;
}

static int wzg2w_mipi_dsi_stop_video(stwuct wzg2w_mipi_dsi *dsi)
{
	u32 status;
	int wet;

	wzg2w_mipi_dsi_wink_wwite(dsi, VICH1SET0W, VICH1SET0W_VSTPAFT);
	wet = wead_poww_timeout(wzg2w_mipi_dsi_wink_wead, status,
				(status & VICH1SW_STOP) && (!(status & VICH1SW_WUNNING)),
				2000, 20000, fawse, dsi, VICH1SW);
	if (wet < 0)
		goto eww;

	wet = wead_poww_timeout(wzg2w_mipi_dsi_wink_wead, status,
				!(status & WINKSW_HSBUSY),
				2000, 20000, fawse, dsi, WINKSW);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(dsi->dev, "Faiwed to stop video signaw input\n");
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Bwidge
 */

static int wzg2w_mipi_dsi_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct wzg2w_mipi_dsi *dsi = bwidge_to_wzg2w_mipi_dsi(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, dsi->next_bwidge, bwidge,
				 fwags);
}

static void wzg2w_mipi_dsi_atomic_enabwe(stwuct dwm_bwidge *bwidge,
					 stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct dwm_atomic_state *state = owd_bwidge_state->base.state;
	stwuct wzg2w_mipi_dsi *dsi = bwidge_to_wzg2w_mipi_dsi(bwidge);
	const stwuct dwm_dispway_mode *mode;
	stwuct dwm_connectow *connectow;
	stwuct dwm_cwtc *cwtc;
	int wet;

	connectow = dwm_atomic_get_new_connectow_fow_encodew(state, bwidge->encodew);
	cwtc = dwm_atomic_get_new_connectow_state(state, connectow)->cwtc;
	mode = &dwm_atomic_get_new_cwtc_state(state, cwtc)->adjusted_mode;

	wet = wzg2w_mipi_dsi_stawtup(dsi, mode);
	if (wet < 0)
		wetuwn;

	wzg2w_mipi_dsi_set_dispway_timing(dsi, mode);

	wet = wzg2w_mipi_dsi_stawt_hs_cwock(dsi);
	if (wet < 0)
		goto eww_stop;

	wet = wzg2w_mipi_dsi_stawt_video(dsi);
	if (wet < 0)
		goto eww_stop_cwock;

	wetuwn;

eww_stop_cwock:
	wzg2w_mipi_dsi_stop_hs_cwock(dsi);
eww_stop:
	wzg2w_mipi_dsi_stop(dsi);
}

static void wzg2w_mipi_dsi_atomic_disabwe(stwuct dwm_bwidge *bwidge,
					  stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct wzg2w_mipi_dsi *dsi = bwidge_to_wzg2w_mipi_dsi(bwidge);

	wzg2w_mipi_dsi_stop_video(dsi);
	wzg2w_mipi_dsi_stop_hs_cwock(dsi);
	wzg2w_mipi_dsi_stop(dsi);
}

static enum dwm_mode_status
wzg2w_mipi_dsi_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
				 const stwuct dwm_dispway_info *info,
				 const stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > 148500)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static const stwuct dwm_bwidge_funcs wzg2w_mipi_dsi_bwidge_ops = {
	.attach = wzg2w_mipi_dsi_attach,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_enabwe = wzg2w_mipi_dsi_atomic_enabwe,
	.atomic_disabwe = wzg2w_mipi_dsi_atomic_disabwe,
	.mode_vawid = wzg2w_mipi_dsi_bwidge_mode_vawid,
};

/* -----------------------------------------------------------------------------
 * Host setting
 */

static int wzg2w_mipi_dsi_host_attach(stwuct mipi_dsi_host *host,
				      stwuct mipi_dsi_device *device)
{
	stwuct wzg2w_mipi_dsi *dsi = host_to_wzg2w_mipi_dsi(host);
	int wet;

	if (device->wanes > dsi->num_data_wanes) {
		dev_eww(dsi->dev,
			"Numbew of wines of device (%u) exceeds host (%u)\n",
			device->wanes, dsi->num_data_wanes);
		wetuwn -EINVAW;
	}

	switch (mipi_dsi_pixew_fowmat_to_bpp(device->fowmat)) {
	case 24:
	case 18:
		bweak;
	defauwt:
		dev_eww(dsi->dev, "Unsuppowted fowmat 0x%04x\n", device->fowmat);
		wetuwn -EINVAW;
	}

	dsi->wanes = device->wanes;
	dsi->fowmat = device->fowmat;
	dsi->mode_fwags = device->mode_fwags;

	dsi->next_bwidge = devm_dwm_of_get_bwidge(dsi->dev, dsi->dev->of_node,
						  1, 0);
	if (IS_EWW(dsi->next_bwidge)) {
		wet = PTW_EWW(dsi->next_bwidge);
		dev_eww(dsi->dev, "faiwed to get next bwidge: %d\n", wet);
		wetuwn wet;
	}

	dwm_bwidge_add(&dsi->bwidge);

	wetuwn 0;
}

static int wzg2w_mipi_dsi_host_detach(stwuct mipi_dsi_host *host,
				      stwuct mipi_dsi_device *device)
{
	stwuct wzg2w_mipi_dsi *dsi = host_to_wzg2w_mipi_dsi(host);

	dwm_bwidge_wemove(&dsi->bwidge);

	wetuwn 0;
}

static const stwuct mipi_dsi_host_ops wzg2w_mipi_dsi_host_ops = {
	.attach = wzg2w_mipi_dsi_host_attach,
	.detach = wzg2w_mipi_dsi_host_detach,
};

/* -----------------------------------------------------------------------------
 * Powew Management
 */

static int __maybe_unused wzg2w_mipi_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct wzg2w_mipi_dsi *dsi = dev_get_dwvdata(dev);

	weset_contwow_assewt(dsi->pwstc);
	weset_contwow_assewt(dsi->awstc);

	wetuwn 0;
}

static int __maybe_unused wzg2w_mipi_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct wzg2w_mipi_dsi *dsi = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_deassewt(dsi->awstc);
	if (wet < 0)
		wetuwn wet;

	wet = weset_contwow_deassewt(dsi->pwstc);
	if (wet < 0)
		weset_contwow_assewt(dsi->awstc);

	wetuwn wet;
}

static const stwuct dev_pm_ops wzg2w_mipi_pm_ops = {
	SET_WUNTIME_PM_OPS(wzg2w_mipi_pm_wuntime_suspend, wzg2w_mipi_pm_wuntime_wesume, NUWW)
};

/* -----------------------------------------------------------------------------
 * Pwobe & Wemove
 */

static int wzg2w_mipi_dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned int num_data_wanes;
	stwuct wzg2w_mipi_dsi *dsi;
	u32 txsetw;
	int wet;

	dsi = devm_kzawwoc(&pdev->dev, sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dsi);
	dsi->dev = &pdev->dev;

	wet = dwm_of_get_data_wanes_count_ep(dsi->dev->of_node, 1, 0, 1, 4);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dsi->dev, wet,
				     "missing ow invawid data-wanes pwopewty\n");

	num_data_wanes = wet;

	dsi->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dsi->mmio))
		wetuwn PTW_EWW(dsi->mmio);

	dsi->vcwk = devm_cwk_get(dsi->dev, "vcwk");
	if (IS_EWW(dsi->vcwk))
		wetuwn PTW_EWW(dsi->vcwk);

	dsi->wstc = devm_weset_contwow_get_excwusive(dsi->dev, "wst");
	if (IS_EWW(dsi->wstc))
		wetuwn dev_eww_pwobe(dsi->dev, PTW_EWW(dsi->wstc),
				     "faiwed to get wst\n");

	dsi->awstc = devm_weset_contwow_get_excwusive(dsi->dev, "awst");
	if (IS_EWW(dsi->awstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dsi->awstc),
				     "faiwed to get awst\n");

	dsi->pwstc = devm_weset_contwow_get_excwusive(dsi->dev, "pwst");
	if (IS_EWW(dsi->pwstc))
		wetuwn dev_eww_pwobe(dsi->dev, PTW_EWW(dsi->pwstc),
				     "faiwed to get pwst\n");

	pwatfowm_set_dwvdata(pdev, dsi);

	pm_wuntime_enabwe(dsi->dev);

	wet = pm_wuntime_wesume_and_get(dsi->dev);
	if (wet < 0)
		goto eww_pm_disabwe;

	/*
	 * TXSETW wegistew can be wead onwy aftew DPHY init. But duwing pwobe
	 * mode->cwock and fowmat awe not avaiwabwe. So initiawize DPHY with
	 * timing pawametews fow 80Mbps.
	 */
	wet = wzg2w_mipi_dsi_dphy_init(dsi, 80000);
	if (wet < 0)
		goto eww_phy;

	txsetw = wzg2w_mipi_dsi_wink_wead(dsi, TXSETW);
	dsi->num_data_wanes = min(((txsetw >> 16) & 3) + 1, num_data_wanes);
	wzg2w_mipi_dsi_dphy_exit(dsi);
	pm_wuntime_put(dsi->dev);

	/* Initiawize the DWM bwidge. */
	dsi->bwidge.funcs = &wzg2w_mipi_dsi_bwidge_ops;
	dsi->bwidge.of_node = dsi->dev->of_node;

	/* Init host device */
	dsi->host.dev = dsi->dev;
	dsi->host.ops = &wzg2w_mipi_dsi_host_ops;
	wet = mipi_dsi_host_wegistew(&dsi->host);
	if (wet < 0)
		goto eww_pm_disabwe;

	wetuwn 0;

eww_phy:
	wzg2w_mipi_dsi_dphy_exit(dsi);
	pm_wuntime_put(dsi->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(dsi->dev);
	wetuwn wet;
}

static void wzg2w_mipi_dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wzg2w_mipi_dsi *dsi = pwatfowm_get_dwvdata(pdev);

	mipi_dsi_host_unwegistew(&dsi->host);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id wzg2w_mipi_dsi_of_tabwe[] = {
	{ .compatibwe = "wenesas,wzg2w-mipi-dsi" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, wzg2w_mipi_dsi_of_tabwe);

static stwuct pwatfowm_dwivew wzg2w_mipi_dsi_pwatfowm_dwivew = {
	.pwobe	= wzg2w_mipi_dsi_pwobe,
	.wemove_new = wzg2w_mipi_dsi_wemove,
	.dwivew	= {
		.name = "wzg2w-mipi-dsi",
		.pm = &wzg2w_mipi_pm_ops,
		.of_match_tabwe = wzg2w_mipi_dsi_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wzg2w_mipi_dsi_pwatfowm_dwivew);

MODUWE_AUTHOW("Biju Das <biju.das.jz@bp.wenesas.com>");
MODUWE_DESCWIPTION("Wenesas WZ/G2W MIPI DSI Encodew Dwivew");
MODUWE_WICENSE("GPW");
