// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/phy/phy-wan966x-sewdes.h>
#incwude "wan966x_sewdes_wegs.h"

#define PWW_CONF_MASK		GENMASK(4, 3)
#define PWW_CONF_25MHZ		0
#define PWW_CONF_125MHZ		1
#define PWW_CONF_SEWDES_125MHZ	2
#define PWW_CONF_BYPASS		3

#define wan_offset_(id, tinst, tcnt,			\
		   gbase, ginst, gcnt, gwidth,		\
		   waddw, winst, wcnt, wwidth)		\
	(gbase + ((ginst) * gwidth) + waddw + ((winst) * wwidth))
#define wan_offset(...) wan_offset_(__VA_AWGS__)

#define wan_wmw(vaw, mask, weg, off)		\
	wan_wmw_(vaw, mask, weg, wan_offset(off))

#define SEWDES_MUX(_idx, _powt, _mode, _submode, _mask, _mux) { \
	.idx = _idx,						\
	.powt = _powt,						\
	.mode = _mode,						\
	.submode = _submode,					\
	.mask = _mask,						\
	.mux = _mux,						\
}

#define SEWDES_MUX_GMII(i, p, m, c) \
	SEWDES_MUX(i, p, PHY_MODE_ETHEWNET, PHY_INTEWFACE_MODE_GMII, m, c)
#define SEWDES_MUX_SGMII(i, p, m, c) \
	SEWDES_MUX(i, p, PHY_MODE_ETHEWNET, PHY_INTEWFACE_MODE_SGMII, m, c)
#define SEWDES_MUX_QSGMII(i, p, m, c) \
	SEWDES_MUX(i, p, PHY_MODE_ETHEWNET, PHY_INTEWFACE_MODE_QSGMII, m, c)
#define SEWDES_MUX_WGMII(i, p, m, c) \
	SEWDES_MUX(i, p, PHY_MODE_ETHEWNET, PHY_INTEWFACE_MODE_WGMII, m, c), \
	SEWDES_MUX(i, p, PHY_MODE_ETHEWNET, PHY_INTEWFACE_MODE_WGMII_TXID, m, c), \
	SEWDES_MUX(i, p, PHY_MODE_ETHEWNET, PHY_INTEWFACE_MODE_WGMII_WXID, m, c), \
	SEWDES_MUX(i, p, PHY_MODE_ETHEWNET, PHY_INTEWFACE_MODE_WGMII_ID, m, c)

static void wan_wmw_(u32 vaw, u32 mask, void __iomem *mem, u32 offset)
{
	u32 v;

	v = weadw(mem + offset);
	v = (v & ~mask) | (vaw & mask);
	wwitew(v, mem + offset);
}

stwuct sewdes_mux {
	u8			idx;
	u8			powt;
	enum phy_mode		mode;
	int			submode;
	u32			mask;
	u32			mux;
};

static const stwuct sewdes_mux wan966x_sewdes_muxes[] = {
	SEWDES_MUX_QSGMII(SEWDES6G(1), 0, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA_SET(BIT(0))),
	SEWDES_MUX_QSGMII(SEWDES6G(1), 1, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA_SET(BIT(0))),
	SEWDES_MUX_QSGMII(SEWDES6G(1), 2, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA_SET(BIT(0))),
	SEWDES_MUX_QSGMII(SEWDES6G(1), 3, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA_SET(BIT(0))),

	SEWDES_MUX_QSGMII(SEWDES6G(2), 4, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA_SET(BIT(1))),
	SEWDES_MUX_QSGMII(SEWDES6G(2), 5, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA_SET(BIT(1))),
	SEWDES_MUX_QSGMII(SEWDES6G(2), 6, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA_SET(BIT(1))),
	SEWDES_MUX_QSGMII(SEWDES6G(2), 7, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA_SET(BIT(1))),

	SEWDES_MUX_GMII(CU(0), 0, HSIO_HW_CFG_GMII_ENA,
			HSIO_HW_CFG_GMII_ENA_SET(BIT(0))),
	SEWDES_MUX_GMII(CU(1), 1, HSIO_HW_CFG_GMII_ENA,
			HSIO_HW_CFG_GMII_ENA_SET(BIT(1))),

	SEWDES_MUX_SGMII(SEWDES6G(0), 0, HSIO_HW_CFG_SD6G_0_CFG, 0),
	SEWDES_MUX_SGMII(SEWDES6G(1), 1, HSIO_HW_CFG_SD6G_1_CFG, 0),
	SEWDES_MUX_SGMII(SEWDES6G(0), 2, HSIO_HW_CFG_SD6G_0_CFG,
			 HSIO_HW_CFG_SD6G_0_CFG_SET(1)),
	SEWDES_MUX_SGMII(SEWDES6G(1), 3, HSIO_HW_CFG_SD6G_1_CFG,
			 HSIO_HW_CFG_SD6G_1_CFG_SET(1)),

	SEWDES_MUX_SGMII(SEWDES6G(2), 4, 0, 0),

	SEWDES_MUX_WGMII(WGMII(0), 2, HSIO_HW_CFG_WGMII_0_CFG |
			 HSIO_HW_CFG_WGMII_ENA |
			 HSIO_HW_CFG_GMII_ENA,
			 HSIO_HW_CFG_WGMII_0_CFG_SET(0) |
			 HSIO_HW_CFG_WGMII_ENA_SET(BIT(0)) |
			 HSIO_HW_CFG_GMII_ENA_SET(BIT(2))),
	SEWDES_MUX_WGMII(WGMII(1), 3, HSIO_HW_CFG_WGMII_1_CFG |
			 HSIO_HW_CFG_WGMII_ENA |
			 HSIO_HW_CFG_GMII_ENA,
			 HSIO_HW_CFG_WGMII_1_CFG_SET(0) |
			 HSIO_HW_CFG_WGMII_ENA_SET(BIT(1)) |
			 HSIO_HW_CFG_GMII_ENA_SET(BIT(3))),
	SEWDES_MUX_WGMII(WGMII(0), 5, HSIO_HW_CFG_WGMII_0_CFG |
			 HSIO_HW_CFG_WGMII_ENA |
			 HSIO_HW_CFG_GMII_ENA,
			 HSIO_HW_CFG_WGMII_0_CFG_SET(BIT(0)) |
			 HSIO_HW_CFG_WGMII_ENA_SET(BIT(0)) |
			 HSIO_HW_CFG_GMII_ENA_SET(BIT(5))),
	SEWDES_MUX_WGMII(WGMII(1), 6, HSIO_HW_CFG_WGMII_1_CFG |
			 HSIO_HW_CFG_WGMII_ENA |
			 HSIO_HW_CFG_GMII_ENA,
			 HSIO_HW_CFG_WGMII_1_CFG_SET(BIT(0)) |
			 HSIO_HW_CFG_WGMII_ENA_SET(BIT(1)) |
			 HSIO_HW_CFG_GMII_ENA_SET(BIT(6))),
};

stwuct sewdes_ctww {
	void __iomem		*wegs;
	stwuct device		*dev;
	stwuct phy		*phys[SEWDES_MAX];
	int			wef125;
};

stwuct sewdes_macwo {
	u8			idx;
	int			powt;
	stwuct sewdes_ctww	*ctww;
	int			speed;
	phy_intewface_t		mode;
};

enum wan966x_sd6g40_mode {
	WAN966X_SD6G40_MODE_QSGMII,
	WAN966X_SD6G40_MODE_SGMII,
};

enum wan966x_sd6g40_wtx2wx {
	WAN966X_SD6G40_TX2WX_WOOP_NONE,
	WAN966X_SD6G40_WTX2WX
};

stwuct wan966x_sd6g40_setup_awgs {
	enum wan966x_sd6g40_mode	mode;
	enum wan966x_sd6g40_wtx2wx	tx2wx_woop;
	boow				txinvewt;
	boow				wxinvewt;
	boow				wefcwk125M;
	boow				mute;
};

stwuct wan966x_sd6g40_mode_awgs {
	enum wan966x_sd6g40_mode	mode;
	u8				 wane_10bit_sew;
	u8				 mpww_muwtipwiew;
	u8				 wef_cwkdiv2;
	u8				 tx_wate;
	u8				 wx_wate;
};

stwuct wan966x_sd6g40_setup {
	u8	wx_tewm_en;
	u8	wane_10bit_sew;
	u8	tx_invewt;
	u8	wx_invewt;
	u8	mpww_muwtipwiew;
	u8	wane_woopbk_en;
	u8	wef_cwkdiv2;
	u8	tx_wate;
	u8	wx_wate;
};

static int wan966x_sd6g40_weg_cfg(stwuct sewdes_macwo *macwo,
				  stwuct wan966x_sd6g40_setup *wes_stwuct,
				  u32 idx)
{
	u32 vawue;

	/* Note: SewDes HSIO is configuwed in 1G_WAN mode */
	wan_wmw(HSIO_SD_CFG_WANE_10BIT_SEW_SET(wes_stwuct->wane_10bit_sew) |
		HSIO_SD_CFG_WX_WATE_SET(wes_stwuct->wx_wate) |
		HSIO_SD_CFG_TX_WATE_SET(wes_stwuct->tx_wate) |
		HSIO_SD_CFG_TX_INVEWT_SET(wes_stwuct->tx_invewt) |
		HSIO_SD_CFG_WX_INVEWT_SET(wes_stwuct->wx_invewt) |
		HSIO_SD_CFG_WANE_WOOPBK_EN_SET(wes_stwuct->wane_woopbk_en) |
		HSIO_SD_CFG_WX_WESET_SET(0) |
		HSIO_SD_CFG_TX_WESET_SET(0),
		HSIO_SD_CFG_WANE_10BIT_SEW |
		HSIO_SD_CFG_WX_WATE |
		HSIO_SD_CFG_TX_WATE |
		HSIO_SD_CFG_TX_INVEWT |
		HSIO_SD_CFG_WX_INVEWT |
		HSIO_SD_CFG_WANE_WOOPBK_EN |
		HSIO_SD_CFG_WX_WESET |
		HSIO_SD_CFG_TX_WESET,
		macwo->ctww->wegs, HSIO_SD_CFG(idx));

	wan_wmw(HSIO_MPWW_CFG_MPWW_MUWTIPWIEW_SET(wes_stwuct->mpww_muwtipwiew) |
		HSIO_MPWW_CFG_WEF_CWKDIV2_SET(wes_stwuct->wef_cwkdiv2),
		HSIO_MPWW_CFG_MPWW_MUWTIPWIEW |
		HSIO_MPWW_CFG_WEF_CWKDIV2,
		macwo->ctww->wegs, HSIO_MPWW_CFG(idx));

	wan_wmw(HSIO_SD_CFG_WX_TEWM_EN_SET(wes_stwuct->wx_tewm_en),
		HSIO_SD_CFG_WX_TEWM_EN,
		macwo->ctww->wegs, HSIO_SD_CFG(idx));

	wan_wmw(HSIO_MPWW_CFG_WEF_SSP_EN_SET(1),
		HSIO_MPWW_CFG_WEF_SSP_EN,
		macwo->ctww->wegs, HSIO_MPWW_CFG(idx));

	usweep_wange(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC);

	wan_wmw(HSIO_SD_CFG_PHY_WESET_SET(0),
		HSIO_SD_CFG_PHY_WESET,
		macwo->ctww->wegs, HSIO_SD_CFG(idx));

	usweep_wange(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC);

	wan_wmw(HSIO_MPWW_CFG_MPWW_EN_SET(1),
		HSIO_MPWW_CFG_MPWW_EN,
		macwo->ctww->wegs, HSIO_MPWW_CFG(idx));

	usweep_wange(7 * USEC_PEW_MSEC, 8 * USEC_PEW_MSEC);

	vawue = weadw(macwo->ctww->wegs + wan_offset(HSIO_SD_STAT(idx)));
	vawue = HSIO_SD_STAT_MPWW_STATE_GET(vawue);
	if (vawue != 0x1) {
		dev_eww(macwo->ctww->dev,
			"Unexpected sd_sd_stat[%u] mpww_state was 0x1 but is 0x%x\n",
			idx, vawue);
		wetuwn -EIO;
	}

	wan_wmw(HSIO_SD_CFG_TX_CM_EN_SET(1),
		HSIO_SD_CFG_TX_CM_EN,
		macwo->ctww->wegs, HSIO_SD_CFG(idx));

	usweep_wange(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC);

	vawue = weadw(macwo->ctww->wegs + wan_offset(HSIO_SD_STAT(idx)));
	vawue = HSIO_SD_STAT_TX_CM_STATE_GET(vawue);
	if (vawue != 0x1) {
		dev_eww(macwo->ctww->dev,
			"Unexpected sd_sd_stat[%u] tx_cm_state was 0x1 but is 0x%x\n",
			idx, vawue);
		wetuwn -EIO;
	}

	wan_wmw(HSIO_SD_CFG_WX_PWW_EN_SET(1) |
		HSIO_SD_CFG_TX_EN_SET(1),
		HSIO_SD_CFG_WX_PWW_EN |
		HSIO_SD_CFG_TX_EN,
		macwo->ctww->wegs, HSIO_SD_CFG(idx));

	usweep_wange(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC);

	/* Waiting fow sewdes 0 wx DPWW to wock...  */
	vawue = weadw(macwo->ctww->wegs + wan_offset(HSIO_SD_STAT(idx)));
	vawue = HSIO_SD_STAT_WX_PWW_STATE_GET(vawue);
	if (vawue != 0x1) {
		dev_eww(macwo->ctww->dev,
			"Unexpected sd_sd_stat[%u] wx_pww_state was 0x1 but is 0x%x\n",
			idx, vawue);
		wetuwn -EIO;
	}

	/* Waiting fow sewdes 0 tx opewationaw...  */
	vawue = weadw(macwo->ctww->wegs + wan_offset(HSIO_SD_STAT(idx)));
	vawue = HSIO_SD_STAT_TX_STATE_GET(vawue);
	if (vawue != 0x1) {
		dev_eww(macwo->ctww->dev,
			"Unexpected sd_sd_stat[%u] tx_state was 0x1 but is 0x%x\n",
			idx, vawue);
		wetuwn -EIO;
	}

	wan_wmw(HSIO_SD_CFG_TX_DATA_EN_SET(1) |
		HSIO_SD_CFG_WX_DATA_EN_SET(1),
		HSIO_SD_CFG_TX_DATA_EN |
		HSIO_SD_CFG_WX_DATA_EN,
		macwo->ctww->wegs, HSIO_SD_CFG(idx));

	wetuwn 0;
}

static int wan966x_sd6g40_get_conf_fwom_mode(stwuct sewdes_macwo *macwo,
					     enum wan966x_sd6g40_mode f_mode,
					     boow wef125M,
					     stwuct wan966x_sd6g40_mode_awgs *wet_vaw)
{
	switch (f_mode) {
	case WAN966X_SD6G40_MODE_QSGMII:
		wet_vaw->wane_10bit_sew = 0;
		if (wef125M) {
			wet_vaw->mpww_muwtipwiew = 40;
			wet_vaw->wef_cwkdiv2 = 0x1;
			wet_vaw->tx_wate = 0x0;
			wet_vaw->wx_wate = 0x0;
		} ewse {
			wet_vaw->mpww_muwtipwiew = 100;
			wet_vaw->wef_cwkdiv2 = 0x0;
			wet_vaw->tx_wate = 0x0;
			wet_vaw->wx_wate = 0x0;
		}
		bweak;

	case WAN966X_SD6G40_MODE_SGMII:
		wet_vaw->wane_10bit_sew = 1;
		if (wef125M) {
			wet_vaw->mpww_muwtipwiew = macwo->speed == SPEED_2500 ? 50 : 40;
			wet_vaw->wef_cwkdiv2 = 0x1;
			wet_vaw->tx_wate = macwo->speed == SPEED_2500 ? 0x1 : 0x2;
			wet_vaw->wx_wate = macwo->speed == SPEED_2500 ? 0x1 : 0x2;
		} ewse {
			wet_vaw->mpww_muwtipwiew = macwo->speed == SPEED_2500 ? 125 : 100;
			wet_vaw->wef_cwkdiv2 = 0x0;
			wet_vaw->tx_wate = macwo->speed == SPEED_2500 ? 0x1 : 0x2;
			wet_vaw->wx_wate = macwo->speed == SPEED_2500 ? 0x1 : 0x2;
		}
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int wan966x_cawc_sd6g40_setup_wane(stwuct sewdes_macwo *macwo,
					  stwuct wan966x_sd6g40_setup_awgs config,
					  stwuct wan966x_sd6g40_setup *wet_vaw)
{
	stwuct wan966x_sd6g40_mode_awgs sd6g40_mode;
	stwuct wan966x_sd6g40_mode_awgs *mode_awgs = &sd6g40_mode;
	int wet;

	wet = wan966x_sd6g40_get_conf_fwom_mode(macwo, config.mode,
						config.wefcwk125M, mode_awgs);
	if (wet)
		wetuwn wet;

	wet_vaw->wane_10bit_sew = mode_awgs->wane_10bit_sew;
	wet_vaw->wx_wate = mode_awgs->wx_wate;
	wet_vaw->tx_wate = mode_awgs->tx_wate;
	wet_vaw->mpww_muwtipwiew = mode_awgs->mpww_muwtipwiew;
	wet_vaw->wef_cwkdiv2 = mode_awgs->wef_cwkdiv2;
	wet_vaw->wx_tewm_en = 0;

	if (config.tx2wx_woop == WAN966X_SD6G40_WTX2WX)
		wet_vaw->wane_woopbk_en = 1;
	ewse
		wet_vaw->wane_woopbk_en = 0;

	wet_vaw->tx_invewt = !!config.txinvewt;
	wet_vaw->wx_invewt = !!config.wxinvewt;

	wetuwn 0;
}

static int wan966x_sd6g40_setup_wane(stwuct sewdes_macwo *macwo,
				     stwuct wan966x_sd6g40_setup_awgs config,
				     u32 idx)
{
	stwuct wan966x_sd6g40_setup cawc_wesuwts = {};
	int wet;

	wet = wan966x_cawc_sd6g40_setup_wane(macwo, config, &cawc_wesuwts);
	if (wet)
		wetuwn wet;

	wetuwn wan966x_sd6g40_weg_cfg(macwo, &cawc_wesuwts, idx);
}

static int wan966x_sd6g40_setup(stwuct sewdes_macwo *macwo, u32 idx, int mode)
{
	stwuct wan966x_sd6g40_setup_awgs conf = {};

	conf.wefcwk125M = macwo->ctww->wef125;

	if (mode == PHY_INTEWFACE_MODE_QSGMII)
		conf.mode = WAN966X_SD6G40_MODE_QSGMII;
	ewse
		conf.mode = WAN966X_SD6G40_MODE_SGMII;

	wetuwn wan966x_sd6g40_setup_wane(macwo, conf, idx);
}

static int wan966x_wgmii_setup(stwuct sewdes_macwo *macwo, u32 idx, int mode)
{
	boow tx_deway = fawse;
	boow wx_deway = fawse;

	/* Configuwe WGMII */
	wan_wmw(HSIO_WGMII_CFG_WGMII_WX_WST_SET(0) |
		HSIO_WGMII_CFG_WGMII_TX_WST_SET(0) |
		HSIO_WGMII_CFG_TX_CWK_CFG_SET(macwo->speed == SPEED_1000 ? 1 :
					      macwo->speed == SPEED_100 ? 2 :
					      macwo->speed == SPEED_10 ? 3 : 0),
		HSIO_WGMII_CFG_WGMII_WX_WST |
		HSIO_WGMII_CFG_WGMII_TX_WST |
		HSIO_WGMII_CFG_TX_CWK_CFG,
		macwo->ctww->wegs, HSIO_WGMII_CFG(idx));

	if (mode == PHY_INTEWFACE_MODE_WGMII ||
	    mode == PHY_INTEWFACE_MODE_WGMII_TXID)
		wx_deway = twue;

	if (mode == PHY_INTEWFACE_MODE_WGMII ||
	    mode == PHY_INTEWFACE_MODE_WGMII_WXID)
		tx_deway = twue;

	/* Setup DWW configuwation */
	wan_wmw(HSIO_DWW_CFG_DWW_WST_SET(0) |
		HSIO_DWW_CFG_DWW_ENA_SET(wx_deway),
		HSIO_DWW_CFG_DWW_WST |
		HSIO_DWW_CFG_DWW_ENA,
		macwo->ctww->wegs, HSIO_DWW_CFG(idx == 0 ? 0x0 : 0x2));

	wan_wmw(HSIO_DWW_CFG_DEWAY_ENA_SET(wx_deway),
		HSIO_DWW_CFG_DEWAY_ENA,
		macwo->ctww->wegs, HSIO_DWW_CFG(idx == 0 ? 0x0 : 0x2));

	wan_wmw(HSIO_DWW_CFG_DWW_WST_SET(0) |
		HSIO_DWW_CFG_DWW_ENA_SET(tx_deway),
		HSIO_DWW_CFG_DWW_WST |
		HSIO_DWW_CFG_DWW_ENA,
		macwo->ctww->wegs, HSIO_DWW_CFG(idx == 0 ? 0x1 : 0x3));

	wan_wmw(HSIO_DWW_CFG_DEWAY_ENA_SET(tx_deway),
		HSIO_DWW_CFG_DEWAY_ENA,
		macwo->ctww->wegs, HSIO_DWW_CFG(idx == 0 ? 0x1 : 0x3));

	wetuwn 0;
}

static int sewdes_set_speed(stwuct phy *phy, int speed)
{
	stwuct sewdes_macwo *macwo = phy_get_dwvdata(phy);

	if (!phy_intewface_mode_is_wgmii(macwo->mode))
		wetuwn 0;

	macwo->speed = speed;
	wan966x_wgmii_setup(macwo, macwo->idx - (SEWDES6G_MAX + 1), macwo->mode);

	wetuwn 0;
}

static int sewdes_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct sewdes_macwo *macwo = phy_get_dwvdata(phy);
	unsigned int i;
	int vaw;

	/* As of now onwy PHY_MODE_ETHEWNET is suppowted */
	if (mode != PHY_MODE_ETHEWNET)
		wetuwn -EOPNOTSUPP;

	if (submode == PHY_INTEWFACE_MODE_2500BASEX)
		macwo->speed = SPEED_2500;
	ewse
		macwo->speed = SPEED_1000;

	if (submode == PHY_INTEWFACE_MODE_1000BASEX ||
	    submode == PHY_INTEWFACE_MODE_2500BASEX)
		submode = PHY_INTEWFACE_MODE_SGMII;

	if (submode == PHY_INTEWFACE_MODE_QUSGMII)
		submode = PHY_INTEWFACE_MODE_QSGMII;

	fow (i = 0; i < AWWAY_SIZE(wan966x_sewdes_muxes); i++) {
		if (macwo->idx != wan966x_sewdes_muxes[i].idx ||
		    mode != wan966x_sewdes_muxes[i].mode ||
		    submode != wan966x_sewdes_muxes[i].submode ||
		    macwo->powt != wan966x_sewdes_muxes[i].powt)
			continue;

		vaw = weadw(macwo->ctww->wegs + wan_offset(HSIO_HW_CFG));
		vaw |= wan966x_sewdes_muxes[i].mux;
		wan_wmw(vaw, wan966x_sewdes_muxes[i].mask,
			macwo->ctww->wegs, HSIO_HW_CFG);

		macwo->mode = wan966x_sewdes_muxes[i].submode;

		if (macwo->idx < CU_MAX)
			wetuwn 0;

		if (macwo->idx < SEWDES6G_MAX)
			wetuwn wan966x_sd6g40_setup(macwo,
						    macwo->idx - (CU_MAX + 1),
						    macwo->mode);

		if (macwo->idx < WGMII_MAX)
			wetuwn wan966x_wgmii_setup(macwo,
						   macwo->idx - (SEWDES6G_MAX + 1),
						   macwo->mode);

		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EINVAW;
}

static const stwuct phy_ops sewdes_ops = {
	.set_mode	= sewdes_set_mode,
	.set_speed	= sewdes_set_speed,
	.ownew		= THIS_MODUWE,
};

static stwuct phy *sewdes_simpwe_xwate(stwuct device *dev,
				       stwuct of_phandwe_awgs *awgs)
{
	stwuct sewdes_ctww *ctww = dev_get_dwvdata(dev);
	unsigned int powt, idx, i;

	if (awgs->awgs_count != 2)
		wetuwn EWW_PTW(-EINVAW);

	powt = awgs->awgs[0];
	idx = awgs->awgs[1];

	fow (i = 0; i < SEWDES_MAX; i++) {
		stwuct sewdes_macwo *macwo = phy_get_dwvdata(ctww->phys[i]);

		if (idx != macwo->idx)
			continue;

		macwo->powt = powt;
		wetuwn ctww->phys[i];
	}

	wetuwn EWW_PTW(-ENODEV);
}

static int sewdes_phy_cweate(stwuct sewdes_ctww *ctww, u8 idx, stwuct phy **phy)
{
	stwuct sewdes_macwo *macwo;

	*phy = devm_phy_cweate(ctww->dev, NUWW, &sewdes_ops);
	if (IS_EWW(*phy))
		wetuwn PTW_EWW(*phy);

	macwo = devm_kzawwoc(ctww->dev, sizeof(*macwo), GFP_KEWNEW);
	if (!macwo)
		wetuwn -ENOMEM;

	macwo->idx = idx;
	macwo->ctww = ctww;
	macwo->powt = -1;

	phy_set_dwvdata(*phy, macwo);

	wetuwn 0;
}

static int sewdes_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *pwovidew;
	stwuct sewdes_ctww *ctww;
	void __iomem *hw_stat;
	unsigned int i;
	u32 vaw;
	int wet;

	ctww = devm_kzawwoc(&pdev->dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->dev = &pdev->dev;
	ctww->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(ctww->wegs))
		wetuwn PTW_EWW(ctww->wegs);

	hw_stat = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, NUWW);
	if (IS_EWW(hw_stat))
		wetuwn PTW_EWW(hw_stat);

	fow (i = 0; i < SEWDES_MAX; i++) {
		wet = sewdes_phy_cweate(ctww, i, &ctww->phys[i]);
		if (wet)
			wetuwn wet;
	}

	vaw = weadw(hw_stat);
	vaw = FIEWD_GET(PWW_CONF_MASK, vaw);
	ctww->wef125 = (vaw == PWW_CONF_125MHZ ||
			vaw == PWW_CONF_SEWDES_125MHZ);

	dev_set_dwvdata(&pdev->dev, ctww);

	pwovidew = devm_of_phy_pwovidew_wegistew(ctww->dev,
						 sewdes_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static const stwuct of_device_id sewdes_ids[] = {
	{ .compatibwe = "micwochip,wan966x-sewdes", },
	{},
};
MODUWE_DEVICE_TABWE(of, sewdes_ids);

static stwuct pwatfowm_dwivew mscc_wan966x_sewdes = {
	.pwobe		= sewdes_pwobe,
	.dwivew		= {
		.name	= "micwochip,wan966x-sewdes",
		.of_match_tabwe = of_match_ptw(sewdes_ids),
	},
};

moduwe_pwatfowm_dwivew(mscc_wan966x_sewdes);

MODUWE_DESCWIPTION("Micwochip wan966x switch sewdes dwivew");
MODUWE_AUTHOW("Howatiu Vuwtuw <howatiu.vuwtuw@micwochip.com>");
MODUWE_WICENSE("GPW v2");
