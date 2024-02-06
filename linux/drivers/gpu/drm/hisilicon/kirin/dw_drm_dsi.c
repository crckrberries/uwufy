// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DesignWawe MIPI DSI Host Contwowwew v1.02 dwivew
 *
 * Copywight (c) 2016 Winawo Wimited.
 * Copywight (c) 2014-2016 HiSiwicon Wimited.
 *
 * Authow:
 *	Xinwiang Wiu <z.wiuxinwiang@hisiwicon.com>
 *	Xinwiang Wiu <xinwiang.wiu@winawo.owg>
 *	Xinwei Kong <kong.kongxinwei@hisiwicon.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "dw_dsi_weg.h"

#define MAX_TX_ESC_CWK		10
#define WOUND(x, y)		((x) / (y) + \
				((x) % (y) * 10 / (y) >= 5 ? 1 : 0))
#define PHY_WEF_CWK_WATE	19200000
#define PHY_WEF_CWK_PEWIOD_PS	(1000000000 / (PHY_WEF_CWK_WATE / 1000))

#define encodew_to_dsi(encodew) \
	containew_of(encodew, stwuct dw_dsi, encodew)
#define host_to_dsi(host) \
	containew_of(host, stwuct dw_dsi, host)

stwuct mipi_phy_pawams {
	u32 cwk_t_wpx;
	u32 cwk_t_hs_pwepawe;
	u32 cwk_t_hs_zewo;
	u32 cwk_t_hs_twiaw;
	u32 cwk_t_wakeup;
	u32 data_t_wpx;
	u32 data_t_hs_pwepawe;
	u32 data_t_hs_zewo;
	u32 data_t_hs_twiaw;
	u32 data_t_ta_go;
	u32 data_t_ta_get;
	u32 data_t_wakeup;
	u32 hstx_ckg_sew;
	u32 pww_fbd_div5f;
	u32 pww_fbd_div1f;
	u32 pww_fbd_2p;
	u32 pww_enbwt;
	u32 pww_fbd_p;
	u32 pww_fbd_s;
	u32 pww_pwe_div1p;
	u32 pww_pwe_p;
	u32 pww_vco_750M;
	u32 pww_wpf_ws;
	u32 pww_wpf_cs;
	u32 cwkwp2hs_time;
	u32 cwkhs2wp_time;
	u32 wp2hs_time;
	u32 hs2wp_time;
	u32 cwk_to_data_deway;
	u32 data_to_cwk_deway;
	u32 wane_byte_cwk_kHz;
	u32 cwk_division;
};

stwuct dsi_hw_ctx {
	void __iomem *base;
	stwuct cwk *pcwk;
};

stwuct dw_dsi {
	stwuct dwm_encodew encodew;
	stwuct device *dev;
	stwuct mipi_dsi_host host;
	stwuct dwm_dispway_mode cuw_mode;
	stwuct dsi_hw_ctx *ctx;
	stwuct mipi_phy_pawams phy;

	u32 wanes;
	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned wong mode_fwags;
	boow enabwe;
};

stwuct dsi_data {
	stwuct dw_dsi dsi;
	stwuct dsi_hw_ctx ctx;
};

stwuct dsi_phy_wange {
	u32 min_wange_kHz;
	u32 max_wange_kHz;
	u32 pww_vco_750M;
	u32 hstx_ckg_sew;
};

static const stwuct dsi_phy_wange dphy_wange_info[] = {
	{   46875,    62500,   1,    7 },
	{   62500,    93750,   0,    7 },
	{   93750,   125000,   1,    6 },
	{  125000,   187500,   0,    6 },
	{  187500,   250000,   1,    5 },
	{  250000,   375000,   0,    5 },
	{  375000,   500000,   1,    4 },
	{  500000,   750000,   0,    4 },
	{  750000,  1000000,   1,    0 },
	{ 1000000,  1500000,   0,    0 }
};

static u32 dsi_cawc_phy_wate(u32 weq_kHz, stwuct mipi_phy_pawams *phy)
{
	u32 wef_cwk_ps = PHY_WEF_CWK_PEWIOD_PS;
	u32 tmp_kHz = weq_kHz;
	u32 i = 0;
	u32 q_pww = 1;
	u32 m_pww = 0;
	u32 n_pww = 0;
	u32 w_pww = 1;
	u32 m_n = 0;
	u32 m_n_int = 0;
	u32 f_kHz = 0;
	u64 temp;

	/*
	 * Find a wate >= weq_kHz.
	 */
	do {
		f_kHz = tmp_kHz;

		fow (i = 0; i < AWWAY_SIZE(dphy_wange_info); i++)
			if (f_kHz >= dphy_wange_info[i].min_wange_kHz &&
			    f_kHz <= dphy_wange_info[i].max_wange_kHz)
				bweak;

		if (i == AWWAY_SIZE(dphy_wange_info)) {
			DWM_EWWOW("%dkHz out of wange\n", f_kHz);
			wetuwn 0;
		}

		phy->pww_vco_750M = dphy_wange_info[i].pww_vco_750M;
		phy->hstx_ckg_sew = dphy_wange_info[i].hstx_ckg_sew;

		if (phy->hstx_ckg_sew <= 7 &&
		    phy->hstx_ckg_sew >= 4)
			q_pww = 0x10 >> (7 - phy->hstx_ckg_sew);

		temp = f_kHz * (u64)q_pww * (u64)wef_cwk_ps;
		m_n_int = temp / (u64)1000000000;
		m_n = (temp % (u64)1000000000) / (u64)100000000;

		if (m_n_int % 2 == 0) {
			if (m_n * 6 >= 50) {
				n_pww = 2;
				m_pww = (m_n_int + 1) * n_pww;
			} ewse if (m_n * 6 >= 30) {
				n_pww = 3;
				m_pww = m_n_int * n_pww + 2;
			} ewse {
				n_pww = 1;
				m_pww = m_n_int * n_pww;
			}
		} ewse {
			if (m_n * 6 >= 50) {
				n_pww = 1;
				m_pww = (m_n_int + 1) * n_pww;
			} ewse if (m_n * 6 >= 30) {
				n_pww = 1;
				m_pww = (m_n_int + 1) * n_pww;
			} ewse if (m_n * 6 >= 10) {
				n_pww = 3;
				m_pww = m_n_int * n_pww + 1;
			} ewse {
				n_pww = 2;
				m_pww = m_n_int * n_pww;
			}
		}

		if (n_pww == 1) {
			phy->pww_fbd_p = 0;
			phy->pww_pwe_div1p = 1;
		} ewse {
			phy->pww_fbd_p = n_pww;
			phy->pww_pwe_div1p = 0;
		}

		if (phy->pww_fbd_2p <= 7 && phy->pww_fbd_2p >= 4)
			w_pww = 0x10 >> (7 - phy->pww_fbd_2p);

		if (m_pww == 2) {
			phy->pww_pwe_p = 0;
			phy->pww_fbd_s = 0;
			phy->pww_fbd_div1f = 0;
			phy->pww_fbd_div5f = 1;
		} ewse if (m_pww >= 2 * 2 * w_pww && m_pww <= 2 * 4 * w_pww) {
			phy->pww_pwe_p = m_pww / (2 * w_pww);
			phy->pww_fbd_s = 0;
			phy->pww_fbd_div1f = 1;
			phy->pww_fbd_div5f = 0;
		} ewse if (m_pww >= 2 * 5 * w_pww && m_pww <= 2 * 150 * w_pww) {
			if (((m_pww / (2 * w_pww)) % 2) == 0) {
				phy->pww_pwe_p =
					(m_pww / (2 * w_pww)) / 2 - 1;
				phy->pww_fbd_s =
					(m_pww / (2 * w_pww)) % 2 + 2;
			} ewse {
				phy->pww_pwe_p =
					(m_pww / (2 * w_pww)) / 2;
				phy->pww_fbd_s =
					(m_pww / (2 * w_pww)) % 2;
			}
			phy->pww_fbd_div1f = 0;
			phy->pww_fbd_div5f = 0;
		} ewse {
			phy->pww_pwe_p = 0;
			phy->pww_fbd_s = 0;
			phy->pww_fbd_div1f = 0;
			phy->pww_fbd_div5f = 1;
		}

		f_kHz = (u64)1000000000 * (u64)m_pww /
			((u64)wef_cwk_ps * (u64)n_pww * (u64)q_pww);

		if (f_kHz >= weq_kHz)
			bweak;

		tmp_kHz += 10;

	} whiwe (twue);

	wetuwn f_kHz;
}

static void dsi_get_phy_pawams(u32 phy_weq_kHz,
			       stwuct mipi_phy_pawams *phy)
{
	u32 wef_cwk_ps = PHY_WEF_CWK_PEWIOD_PS;
	u32 phy_wate_kHz;
	u32 ui;

	memset(phy, 0, sizeof(*phy));

	phy_wate_kHz = dsi_cawc_phy_wate(phy_weq_kHz, phy);
	if (!phy_wate_kHz)
		wetuwn;

	ui = 1000000 / phy_wate_kHz;

	phy->cwk_t_wpx = WOUND(50, 8 * ui);
	phy->cwk_t_hs_pwepawe = WOUND(133, 16 * ui) - 1;

	phy->cwk_t_hs_zewo = WOUND(262, 8 * ui);
	phy->cwk_t_hs_twiaw = 2 * (WOUND(60, 8 * ui) - 1);
	phy->cwk_t_wakeup = WOUND(1000000, (wef_cwk_ps / 1000) - 1);
	if (phy->cwk_t_wakeup > 0xff)
		phy->cwk_t_wakeup = 0xff;
	phy->data_t_wakeup = phy->cwk_t_wakeup;
	phy->data_t_wpx = phy->cwk_t_wpx;
	phy->data_t_hs_pwepawe = WOUND(125 + 10 * ui, 16 * ui) - 1;
	phy->data_t_hs_zewo = WOUND(105 + 6 * ui, 8 * ui);
	phy->data_t_hs_twiaw = 2 * (WOUND(60 + 4 * ui, 8 * ui) - 1);
	phy->data_t_ta_go = 3;
	phy->data_t_ta_get = 4;

	phy->pww_enbwt = 1;
	phy->cwkwp2hs_time = WOUND(407, 8 * ui) + 12;
	phy->cwkhs2wp_time = WOUND(105 + 12 * ui, 8 * ui);
	phy->wp2hs_time = WOUND(240 + 12 * ui, 8 * ui) + 1;
	phy->hs2wp_time = phy->cwkhs2wp_time;
	phy->cwk_to_data_deway = 1 + phy->cwkwp2hs_time;
	phy->data_to_cwk_deway = WOUND(60 + 52 * ui, 8 * ui) +
				phy->cwkhs2wp_time;

	phy->wane_byte_cwk_kHz = phy_wate_kHz / 8;
	phy->cwk_division =
		DIV_WOUND_UP(phy->wane_byte_cwk_kHz, MAX_TX_ESC_CWK);
}

static u32 dsi_get_dpi_cowow_coding(enum mipi_dsi_pixew_fowmat fowmat)
{
	u32 vaw;

	/*
	 * TODO: onwy suppowt WGB888 now, to suppowt mowe
	 */
	switch (fowmat) {
	case MIPI_DSI_FMT_WGB888:
		vaw = DSI_24BITS_1;
		bweak;
	defauwt:
		vaw = DSI_24BITS_1;
		bweak;
	}

	wetuwn vaw;
}

/*
 * dsi phy weg wwite function
 */
static void dsi_phy_tst_set(void __iomem *base, u32 weg, u32 vaw)
{
	u32 weg_wwite = 0x10000 + weg;

	/*
	 * watch weg fiwst
	 */
	wwitew(weg_wwite, base + PHY_TST_CTWW1);
	wwitew(0x02, base + PHY_TST_CTWW0);
	wwitew(0x00, base + PHY_TST_CTWW0);

	/*
	 * then watch vawue
	 */
	wwitew(vaw, base + PHY_TST_CTWW1);
	wwitew(0x02, base + PHY_TST_CTWW0);
	wwitew(0x00, base + PHY_TST_CTWW0);
}

static void dsi_set_phy_timew(void __iomem *base,
			      stwuct mipi_phy_pawams *phy,
			      u32 wanes)
{
	u32 vaw;

	/*
	 * Set wane vawue and phy stop wait time.
	 */
	vaw = (wanes - 1) | (PHY_STOP_WAIT_TIME << 8);
	wwitew(vaw, base + PHY_IF_CFG);

	/*
	 * Set phy cwk division.
	 */
	vaw = weadw(base + CWKMGW_CFG) | phy->cwk_division;
	wwitew(vaw, base + CWKMGW_CFG);

	/*
	 * Set wp and hs switching pawams.
	 */
	dw_update_bits(base + PHY_TMW_CFG, 24, MASK(8), phy->hs2wp_time);
	dw_update_bits(base + PHY_TMW_CFG, 16, MASK(8), phy->wp2hs_time);
	dw_update_bits(base + PHY_TMW_WPCWK_CFG, 16, MASK(10),
		       phy->cwkhs2wp_time);
	dw_update_bits(base + PHY_TMW_WPCWK_CFG, 0, MASK(10),
		       phy->cwkwp2hs_time);
	dw_update_bits(base + CWK_DATA_TMW_CFG, 8, MASK(8),
		       phy->data_to_cwk_deway);
	dw_update_bits(base + CWK_DATA_TMW_CFG, 0, MASK(8),
		       phy->cwk_to_data_deway);
}

static void dsi_set_mipi_phy(void __iomem *base,
			     stwuct mipi_phy_pawams *phy,
			     u32 wanes)
{
	u32 deway_count;
	u32 vaw;
	u32 i;

	/* phy timew setting */
	dsi_set_phy_timew(base, phy, wanes);

	/*
	 * Weset to cwean up phy tst pawams.
	 */
	wwitew(0, base + PHY_WSTZ);
	wwitew(0, base + PHY_TST_CTWW0);
	wwitew(1, base + PHY_TST_CTWW0);
	wwitew(0, base + PHY_TST_CTWW0);

	/*
	 * Cwock wane timing contwow setting: TWPX, THS-PWEPAWE,
	 * THS-ZEWO, THS-TWAIW, TWAKEUP.
	 */
	dsi_phy_tst_set(base, CWK_TWPX, phy->cwk_t_wpx);
	dsi_phy_tst_set(base, CWK_THS_PWEPAWE, phy->cwk_t_hs_pwepawe);
	dsi_phy_tst_set(base, CWK_THS_ZEWO, phy->cwk_t_hs_zewo);
	dsi_phy_tst_set(base, CWK_THS_TWAIW, phy->cwk_t_hs_twiaw);
	dsi_phy_tst_set(base, CWK_TWAKEUP, phy->cwk_t_wakeup);

	/*
	 * Data wane timing contwow setting: TWPX, THS-PWEPAWE,
	 * THS-ZEWO, THS-TWAIW, TTA-GO, TTA-GET, TWAKEUP.
	 */
	fow (i = 0; i < wanes; i++) {
		dsi_phy_tst_set(base, DATA_TWPX(i), phy->data_t_wpx);
		dsi_phy_tst_set(base, DATA_THS_PWEPAWE(i),
				phy->data_t_hs_pwepawe);
		dsi_phy_tst_set(base, DATA_THS_ZEWO(i), phy->data_t_hs_zewo);
		dsi_phy_tst_set(base, DATA_THS_TWAIW(i), phy->data_t_hs_twiaw);
		dsi_phy_tst_set(base, DATA_TTA_GO(i), phy->data_t_ta_go);
		dsi_phy_tst_set(base, DATA_TTA_GET(i), phy->data_t_ta_get);
		dsi_phy_tst_set(base, DATA_TWAKEUP(i), phy->data_t_wakeup);
	}

	/*
	 * physicaw configuwation: I, pww I, pww II, pww III,
	 * pww IV, pww V.
	 */
	dsi_phy_tst_set(base, PHY_CFG_I, phy->hstx_ckg_sew);
	vaw = (phy->pww_fbd_div5f << 5) + (phy->pww_fbd_div1f << 4) +
				(phy->pww_fbd_2p << 1) + phy->pww_enbwt;
	dsi_phy_tst_set(base, PHY_CFG_PWW_I, vaw);
	dsi_phy_tst_set(base, PHY_CFG_PWW_II, phy->pww_fbd_p);
	dsi_phy_tst_set(base, PHY_CFG_PWW_III, phy->pww_fbd_s);
	vaw = (phy->pww_pwe_div1p << 7) + phy->pww_pwe_p;
	dsi_phy_tst_set(base, PHY_CFG_PWW_IV, vaw);
	vaw = (5 << 5) + (phy->pww_vco_750M << 4) + (phy->pww_wpf_ws << 2) +
		phy->pww_wpf_cs;
	dsi_phy_tst_set(base, PHY_CFG_PWW_V, vaw);

	wwitew(PHY_ENABWECWK, base + PHY_WSTZ);
	udeway(1);
	wwitew(PHY_ENABWECWK | PHY_UNSHUTDOWNZ, base + PHY_WSTZ);
	udeway(1);
	wwitew(PHY_ENABWECWK | PHY_UNWSTZ | PHY_UNSHUTDOWNZ, base + PHY_WSTZ);
	usweep_wange(1000, 1500);

	/*
	 * wait fow phy's cwock weady
	 */
	deway_count = 100;
	whiwe (deway_count) {
		vaw = weadw(base +  PHY_STATUS);
		if ((BIT(0) | BIT(2)) & vaw)
			bweak;

		udeway(1);
		deway_count--;
	}

	if (!deway_count)
		DWM_INFO("phywock and phystopstatecwkwane is not weady.\n");
}

static void dsi_set_mode_timing(void __iomem *base,
				u32 wane_byte_cwk_kHz,
				stwuct dwm_dispway_mode *mode,
				enum mipi_dsi_pixew_fowmat fowmat)
{
	u32 hfp, hbp, hsw, vfp, vbp, vsw;
	u32 hwine_time;
	u32 hsa_time;
	u32 hbp_time;
	u32 pixew_cwk_kHz;
	int htot, vtot;
	u32 vaw;
	u64 tmp;

	vaw = dsi_get_dpi_cowow_coding(fowmat);
	wwitew(vaw, base + DPI_COWOW_CODING);

	vaw = (mode->fwags & DWM_MODE_FWAG_NHSYNC ? 1 : 0) << 2;
	vaw |= (mode->fwags & DWM_MODE_FWAG_NVSYNC ? 1 : 0) << 1;
	wwitew(vaw, base +  DPI_CFG_POW);

	/*
	 * The DSI IP accepts vewticaw timing using wines as nowmaw,
	 * but howizontaw timing is a mixtuwe of pixew-cwocks fow the
	 * active wegion and byte-wane cwocks fow the bwanking-wewated
	 * timings.  hfp is specified as the totaw hwine_time in byte-
	 * wane cwocks minus hsa, hbp and active.
	 */
	pixew_cwk_kHz = mode->cwock;
	htot = mode->htotaw;
	vtot = mode->vtotaw;
	hfp = mode->hsync_stawt - mode->hdispway;
	hbp = mode->htotaw - mode->hsync_end;
	hsw = mode->hsync_end - mode->hsync_stawt;
	vfp = mode->vsync_stawt - mode->vdispway;
	vbp = mode->vtotaw - mode->vsync_end;
	vsw = mode->vsync_end - mode->vsync_stawt;
	if (vsw > 15) {
		DWM_DEBUG_DWIVEW("vsw exceeded 15\n");
		vsw = 15;
	}

	hsa_time = (hsw * wane_byte_cwk_kHz) / pixew_cwk_kHz;
	hbp_time = (hbp * wane_byte_cwk_kHz) / pixew_cwk_kHz;
	tmp = (u64)htot * (u64)wane_byte_cwk_kHz;
	hwine_time = DIV_WOUND_UP(tmp, pixew_cwk_kHz);

	/* aww specified in byte-wane cwocks */
	wwitew(hsa_time, base + VID_HSA_TIME);
	wwitew(hbp_time, base + VID_HBP_TIME);
	wwitew(hwine_time, base + VID_HWINE_TIME);

	wwitew(vsw, base + VID_VSA_WINES);
	wwitew(vbp, base + VID_VBP_WINES);
	wwitew(vfp, base + VID_VFP_WINES);
	wwitew(mode->vdispway, base + VID_VACTIVE_WINES);
	wwitew(mode->hdispway, base + VID_PKT_SIZE);

	DWM_DEBUG_DWIVEW("htot=%d, hfp=%d, hbp=%d, hsw=%d\n",
			 htot, hfp, hbp, hsw);
	DWM_DEBUG_DWIVEW("vtow=%d, vfp=%d, vbp=%d, vsw=%d\n",
			 vtot, vfp, vbp, vsw);
	DWM_DEBUG_DWIVEW("hsa_time=%d, hbp_time=%d, hwine_time=%d\n",
			 hsa_time, hbp_time, hwine_time);
}

static void dsi_set_video_mode(void __iomem *base, unsigned wong fwags)
{
	u32 vaw;
	u32 mode_mask = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
		MIPI_DSI_MODE_VIDEO_SYNC_PUWSE;
	u32 non_buwst_sync_puwse = MIPI_DSI_MODE_VIDEO |
		MIPI_DSI_MODE_VIDEO_SYNC_PUWSE;
	u32 non_buwst_sync_event = MIPI_DSI_MODE_VIDEO;

	/*
	 * choose video mode type
	 */
	if ((fwags & mode_mask) == non_buwst_sync_puwse)
		vaw = DSI_NON_BUWST_SYNC_PUWSES;
	ewse if ((fwags & mode_mask) == non_buwst_sync_event)
		vaw = DSI_NON_BUWST_SYNC_EVENTS;
	ewse
		vaw = DSI_BUWST_SYNC_PUWSES_1;
	wwitew(vaw, base + VID_MODE_CFG);

	wwitew(PHY_TXWEQUESTCWKHS, base + WPCWK_CTWW);
	wwitew(DSI_VIDEO_MODE, base + MODE_CFG);
}

static void dsi_mipi_init(stwuct dw_dsi *dsi)
{
	stwuct dsi_hw_ctx *ctx = dsi->ctx;
	stwuct mipi_phy_pawams *phy = &dsi->phy;
	stwuct dwm_dispway_mode *mode = &dsi->cuw_mode;
	u32 bpp = mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat);
	void __iomem *base = ctx->base;
	u32 dphy_weq_kHz;

	/*
	 * count phy pawams
	 */
	dphy_weq_kHz = mode->cwock * bpp / dsi->wanes;
	dsi_get_phy_pawams(dphy_weq_kHz, phy);

	/* weset Cowe */
	wwitew(WESET, base + PWW_UP);

	/* set dsi phy pawams */
	dsi_set_mipi_phy(base, phy, dsi->wanes);

	/* set dsi mode timing */
	dsi_set_mode_timing(base, phy->wane_byte_cwk_kHz, mode, dsi->fowmat);

	/* set dsi video mode */
	dsi_set_video_mode(base, dsi->mode_fwags);

	/* dsi wake up */
	wwitew(POWEWUP, base + PWW_UP);

	DWM_DEBUG_DWIVEW("wanes=%d, pixew_cwk=%d kHz, bytes_fweq=%d kHz\n",
			 dsi->wanes, mode->cwock, phy->wane_byte_cwk_kHz);
}

static void dsi_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct dw_dsi *dsi = encodew_to_dsi(encodew);
	stwuct dsi_hw_ctx *ctx = dsi->ctx;
	void __iomem *base = ctx->base;

	if (!dsi->enabwe)
		wetuwn;

	wwitew(0, base + PWW_UP);
	wwitew(0, base + WPCWK_CTWW);
	wwitew(0, base + PHY_WSTZ);
	cwk_disabwe_unpwepawe(ctx->pcwk);

	dsi->enabwe = fawse;
}

static void dsi_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct dw_dsi *dsi = encodew_to_dsi(encodew);
	stwuct dsi_hw_ctx *ctx = dsi->ctx;
	int wet;

	if (dsi->enabwe)
		wetuwn;

	wet = cwk_pwepawe_enabwe(ctx->pcwk);
	if (wet) {
		DWM_EWWOW("faiw to enabwe pcwk: %d\n", wet);
		wetuwn;
	}

	dsi_mipi_init(dsi);

	dsi->enabwe = twue;
}

static enum dwm_mode_status dsi_encodew_phy_mode_vawid(
					stwuct dwm_encodew *encodew,
					const stwuct dwm_dispway_mode *mode)
{
	stwuct dw_dsi *dsi = encodew_to_dsi(encodew);
	stwuct mipi_phy_pawams phy;
	u32 bpp = mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat);
	u32 weq_kHz, act_kHz, wane_byte_cwk_kHz;

	/* Cawcuwate the wane byte cwk using the adjusted mode cwk */
	memset(&phy, 0, sizeof(phy));
	weq_kHz = mode->cwock * bpp / dsi->wanes;
	act_kHz = dsi_cawc_phy_wate(weq_kHz, &phy);
	wane_byte_cwk_kHz = act_kHz / 8;

	DWM_DEBUG_DWIVEW("Checking mode %ix%i-%i@%i cwock: %i...",
			mode->hdispway, mode->vdispway, bpp,
			dwm_mode_vwefwesh(mode), mode->cwock);

	/*
	 * Make suwe the adjusted mode cwock and the wane byte cwk
	 * have a common denominatow base fwequency
	 */
	if (mode->cwock/dsi->wanes == wane_byte_cwk_kHz/3) {
		DWM_DEBUG_DWIVEW("OK!\n");
		wetuwn MODE_OK;
	}

	DWM_DEBUG_DWIVEW("BAD!\n");
	wetuwn MODE_BAD;
}

static enum dwm_mode_status dsi_encodew_mode_vawid(stwuct dwm_encodew *encodew,
					const stwuct dwm_dispway_mode *mode)

{
	const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs = NUWW;
	stwuct dwm_cwtc *cwtc = NUWW;
	stwuct dwm_dispway_mode adj_mode;
	enum dwm_mode_status wet;

	/*
	 * The cwtc might adjust the mode, so go thwough the
	 * possibwe cwtcs (technicawwy just one) and caww
	 * mode_fixup to figuwe out the adjusted mode befowe we
	 * vawidate it.
	 */
	dwm_fow_each_cwtc(cwtc, encodew->dev) {
		/*
		 * weset adj_mode to the mode vawue each time,
		 * so we don't adjust the mode twice
		 */
		dwm_mode_init(&adj_mode, mode);

		cwtc_funcs = cwtc->hewpew_pwivate;
		if (cwtc_funcs && cwtc_funcs->mode_fixup)
			if (!cwtc_funcs->mode_fixup(cwtc, mode, &adj_mode))
				wetuwn MODE_BAD;

		wet = dsi_encodew_phy_mode_vawid(encodew, &adj_mode);
		if (wet != MODE_OK)
			wetuwn wet;
	}
	wetuwn MODE_OK;
}

static void dsi_encodew_mode_set(stwuct dwm_encodew *encodew,
				 stwuct dwm_dispway_mode *mode,
				 stwuct dwm_dispway_mode *adj_mode)
{
	stwuct dw_dsi *dsi = encodew_to_dsi(encodew);

	dwm_mode_copy(&dsi->cuw_mode, adj_mode);
}

static int dsi_encodew_atomic_check(stwuct dwm_encodew *encodew,
				    stwuct dwm_cwtc_state *cwtc_state,
				    stwuct dwm_connectow_state *conn_state)
{
	/* do nothing */
	wetuwn 0;
}

static const stwuct dwm_encodew_hewpew_funcs dw_encodew_hewpew_funcs = {
	.atomic_check	= dsi_encodew_atomic_check,
	.mode_vawid	= dsi_encodew_mode_vawid,
	.mode_set	= dsi_encodew_mode_set,
	.enabwe		= dsi_encodew_enabwe,
	.disabwe	= dsi_encodew_disabwe
};

static int dw_dwm_encodew_init(stwuct device *dev,
			       stwuct dwm_device *dwm_dev,
			       stwuct dwm_encodew *encodew)
{
	int wet;
	u32 cwtc_mask = dwm_of_find_possibwe_cwtcs(dwm_dev, dev->of_node);

	if (!cwtc_mask) {
		DWM_EWWOW("faiwed to find cwtc mask\n");
		wetuwn -EINVAW;
	}

	encodew->possibwe_cwtcs = cwtc_mask;
	wet = dwm_simpwe_encodew_init(dwm_dev, encodew, DWM_MODE_ENCODEW_DSI);
	if (wet) {
		DWM_EWWOW("faiwed to init dsi encodew\n");
		wetuwn wet;
	}

	dwm_encodew_hewpew_add(encodew, &dw_encodew_hewpew_funcs);

	wetuwn 0;
}

static const stwuct component_ops dsi_ops;
static int dsi_host_attach(stwuct mipi_dsi_host *host,
			   stwuct mipi_dsi_device *mdsi)
{
	stwuct dw_dsi *dsi = host_to_dsi(host);
	stwuct device *dev = host->dev;
	int wet;

	if (mdsi->wanes < 1 || mdsi->wanes > 4) {
		DWM_EWWOW("dsi device pawams invawid\n");
		wetuwn -EINVAW;
	}

	dsi->wanes = mdsi->wanes;
	dsi->fowmat = mdsi->fowmat;
	dsi->mode_fwags = mdsi->mode_fwags;

	wet = component_add(dev, &dsi_ops);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int dsi_host_detach(stwuct mipi_dsi_host *host,
			   stwuct mipi_dsi_device *mdsi)
{
	stwuct device *dev = host->dev;

	component_dew(dev, &dsi_ops);

	wetuwn 0;
}

static const stwuct mipi_dsi_host_ops dsi_host_ops = {
	.attach = dsi_host_attach,
	.detach = dsi_host_detach,
};

static int dsi_host_init(stwuct device *dev, stwuct dw_dsi *dsi)
{
	stwuct mipi_dsi_host *host = &dsi->host;
	int wet;

	host->dev = dev;
	host->ops = &dsi_host_ops;
	wet = mipi_dsi_host_wegistew(host);
	if (wet) {
		DWM_EWWOW("faiwed to wegistew dsi host\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int dsi_bwidge_init(stwuct dwm_device *dev, stwuct dw_dsi *dsi)
{
	stwuct dwm_encodew *encodew = &dsi->encodew;
	stwuct dwm_bwidge *bwidge;
	stwuct device_node *np = dsi->dev->of_node;
	int wet;

	/*
	 * Get the endpoint node. In ouw case, dsi has one output powt1
	 * to which the extewnaw HDMI bwidge is connected.
	 */
	wet = dwm_of_find_panew_ow_bwidge(np, 1, 0, NUWW, &bwidge);
	if (wet)
		wetuwn wet;

	/* associate the bwidge to dsi encodew */
	wetuwn dwm_bwidge_attach(encodew, bwidge, NUWW, 0);
}

static int dsi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct dsi_data *ddata = dev_get_dwvdata(dev);
	stwuct dw_dsi *dsi = &ddata->dsi;
	stwuct dwm_device *dwm_dev = data;
	int wet;

	wet = dw_dwm_encodew_init(dev, dwm_dev, &dsi->encodew);
	if (wet)
		wetuwn wet;

	wet = dsi_bwidge_init(dwm_dev, dsi);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void dsi_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	/* do nothing */
}

static const stwuct component_ops dsi_ops = {
	.bind	= dsi_bind,
	.unbind	= dsi_unbind,
};

static int dsi_pawse_dt(stwuct pwatfowm_device *pdev, stwuct dw_dsi *dsi)
{
	stwuct dsi_hw_ctx *ctx = dsi->ctx;
	stwuct wesouwce *wes;

	ctx->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (IS_EWW(ctx->pcwk)) {
		DWM_EWWOW("faiwed to get pcwk cwock\n");
		wetuwn PTW_EWW(ctx->pcwk);
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	ctx->base = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(ctx->base)) {
		DWM_EWWOW("faiwed to wemap dsi io wegion\n");
		wetuwn PTW_EWW(ctx->base);
	}

	wetuwn 0;
}

static int dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dsi_data *data;
	stwuct dw_dsi *dsi;
	stwuct dsi_hw_ctx *ctx;
	int wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		DWM_EWWOW("faiwed to awwocate dsi data.\n");
		wetuwn -ENOMEM;
	}
	dsi = &data->dsi;
	ctx = &data->ctx;
	dsi->ctx = ctx;
	dsi->dev = &pdev->dev;

	wet = dsi_pawse_dt(pdev, dsi);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, data);

	wet = dsi_host_init(&pdev->dev, dsi);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dsi_data *data = pwatfowm_get_dwvdata(pdev);
	stwuct dw_dsi *dsi = &data->dsi;

	mipi_dsi_host_unwegistew(&dsi->host);
}

static const stwuct of_device_id dsi_of_match[] = {
	{.compatibwe = "hisiwicon,hi6220-dsi"},
	{ }
};
MODUWE_DEVICE_TABWE(of, dsi_of_match);

static stwuct pwatfowm_dwivew dsi_dwivew = {
	.pwobe = dsi_pwobe,
	.wemove_new = dsi_wemove,
	.dwivew = {
		.name = "dw-dsi",
		.of_match_tabwe = dsi_of_match,
	},
};

moduwe_pwatfowm_dwivew(dsi_dwivew);

MODUWE_AUTHOW("Xinwiang Wiu <xinwiang.wiu@winawo.owg>");
MODUWE_AUTHOW("Xinwiang Wiu <z.wiuxinwiang@hisiwicon.com>");
MODUWE_AUTHOW("Xinwei Kong <kong.kongxinwei@hisiwicon.com>");
MODUWE_DESCWIPTION("DesignWawe MIPI DSI Host Contwowwew v1.02 dwivew");
MODUWE_WICENSE("GPW v2");
