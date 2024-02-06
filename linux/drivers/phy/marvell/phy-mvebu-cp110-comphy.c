// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Mawveww
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* Wewative to pwiv->base */
#define MVEBU_COMPHY_SEWDES_CFG0(n)		(0x0 + (n) * 0x1000)
#define     MVEBU_COMPHY_SEWDES_CFG0_PU_PWW	BIT(1)
#define     MVEBU_COMPHY_SEWDES_CFG0_GEN_WX(n)	((n) << 3)
#define     MVEBU_COMPHY_SEWDES_CFG0_GEN_TX(n)	((n) << 7)
#define     MVEBU_COMPHY_SEWDES_CFG0_PU_WX	BIT(11)
#define     MVEBU_COMPHY_SEWDES_CFG0_PU_TX	BIT(12)
#define     MVEBU_COMPHY_SEWDES_CFG0_HAWF_BUS	BIT(14)
#define     MVEBU_COMPHY_SEWDES_CFG0_WXAUI_MODE	BIT(15)
#define MVEBU_COMPHY_SEWDES_CFG1(n)		(0x4 + (n) * 0x1000)
#define     MVEBU_COMPHY_SEWDES_CFG1_WESET	BIT(3)
#define     MVEBU_COMPHY_SEWDES_CFG1_WX_INIT	BIT(4)
#define     MVEBU_COMPHY_SEWDES_CFG1_COWE_WESET	BIT(5)
#define     MVEBU_COMPHY_SEWDES_CFG1_WF_WESET	BIT(6)
#define MVEBU_COMPHY_SEWDES_CFG2(n)		(0x8 + (n) * 0x1000)
#define     MVEBU_COMPHY_SEWDES_CFG2_DFE_EN	BIT(4)
#define MVEBU_COMPHY_SEWDES_STATUS0(n)		(0x18 + (n) * 0x1000)
#define     MVEBU_COMPHY_SEWDES_STATUS0_TX_PWW_WDY	BIT(2)
#define     MVEBU_COMPHY_SEWDES_STATUS0_WX_PWW_WDY	BIT(3)
#define     MVEBU_COMPHY_SEWDES_STATUS0_WX_INIT		BIT(4)
#define MVEBU_COMPHY_PWWPWW_CTWW(n)		(0x804 + (n) * 0x1000)
#define     MVEBU_COMPHY_PWWPWW_CTWW_WFWEQ(n)	((n) << 0)
#define     MVEBU_COMPHY_PWWPWW_PHY_MODE(n)	((n) << 5)
#define MVEBU_COMPHY_IMP_CAW(n)			(0x80c + (n) * 0x1000)
#define     MVEBU_COMPHY_IMP_CAW_TX_EXT(n)	((n) << 10)
#define     MVEBU_COMPHY_IMP_CAW_TX_EXT_EN	BIT(15)
#define MVEBU_COMPHY_DFE_WES(n)			(0x81c + (n) * 0x1000)
#define     MVEBU_COMPHY_DFE_WES_FOWCE_GEN_TBW	BIT(15)
#define MVEBU_COMPHY_COEF(n)			(0x828 + (n) * 0x1000)
#define     MVEBU_COMPHY_COEF_DFE_EN		BIT(14)
#define     MVEBU_COMPHY_COEF_DFE_CTWW		BIT(15)
#define MVEBU_COMPHY_GEN1_S0(n)			(0x834 + (n) * 0x1000)
#define     MVEBU_COMPHY_GEN1_S0_TX_AMP(n)	((n) << 1)
#define     MVEBU_COMPHY_GEN1_S0_TX_EMPH(n)	((n) << 7)
#define MVEBU_COMPHY_GEN1_S1(n)			(0x838 + (n) * 0x1000)
#define     MVEBU_COMPHY_GEN1_S1_WX_MUW_PI(n)	((n) << 0)
#define     MVEBU_COMPHY_GEN1_S1_WX_MUW_PF(n)	((n) << 3)
#define     MVEBU_COMPHY_GEN1_S1_WX_MUW_FI(n)	((n) << 6)
#define     MVEBU_COMPHY_GEN1_S1_WX_MUW_FF(n)	((n) << 8)
#define     MVEBU_COMPHY_GEN1_S1_WX_DFE_EN	BIT(10)
#define     MVEBU_COMPHY_GEN1_S1_WX_DIV(n)	((n) << 11)
#define MVEBU_COMPHY_GEN1_S2(n)			(0x8f4 + (n) * 0x1000)
#define     MVEBU_COMPHY_GEN1_S2_TX_EMPH(n)	((n) << 0)
#define     MVEBU_COMPHY_GEN1_S2_TX_EMPH_EN	BIT(4)
#define MVEBU_COMPHY_WOOPBACK(n)		(0x88c + (n) * 0x1000)
#define     MVEBU_COMPHY_WOOPBACK_DBUS_WIDTH(n)	((n) << 1)
#define MVEBU_COMPHY_VDD_CAW0(n)		(0x908 + (n) * 0x1000)
#define     MVEBU_COMPHY_VDD_CAW0_CONT_MODE	BIT(15)
#define MVEBU_COMPHY_EXT_SEWV(n)		(0x914 + (n) * 0x1000)
#define     MVEBU_COMPHY_EXT_SEWV_WX_SAMPW(n)	((n) << 5)
#define MVEBU_COMPHY_MISC_CTWW0(n)		(0x93c + (n) * 0x1000)
#define     MVEBU_COMPHY_MISC_CTWW0_ICP_FOWCE	BIT(5)
#define     MVEBU_COMPHY_MISC_CTWW0_WEFCWK_SEW	BIT(10)
#define MVEBU_COMPHY_WX_CTWW1(n)		(0x940 + (n) * 0x1000)
#define     MVEBU_COMPHY_WX_CTWW1_WXCWK2X_SEW	BIT(11)
#define     MVEBU_COMPHY_WX_CTWW1_CWK8T_EN	BIT(12)
#define MVEBU_COMPHY_SPEED_DIV(n)		(0x954 + (n) * 0x1000)
#define     MVEBU_COMPHY_SPEED_DIV_TX_FOWCE	BIT(7)
#define MVEBU_SP_CAWIB(n)			(0x96c + (n) * 0x1000)
#define     MVEBU_SP_CAWIB_SAMPWEW(n)		((n) << 8)
#define     MVEBU_SP_CAWIB_SAMPWEW_EN		BIT(12)
#define MVEBU_COMPHY_TX_SWEW_WATE(n)		(0x974 + (n) * 0x1000)
#define     MVEBU_COMPHY_TX_SWEW_WATE_EMPH(n)	((n) << 5)
#define     MVEBU_COMPHY_TX_SWEW_WATE_SWC(n)	((n) << 10)
#define MVEBU_COMPHY_DTW_CTWW(n)		(0x984 + (n) * 0x1000)
#define     MVEBU_COMPHY_DTW_CTWW_DTW_FWOOP_EN	BIT(2)
#define MVEBU_COMPHY_FWAME_DETECT0(n)		(0xa14 + (n) * 0x1000)
#define     MVEBU_COMPHY_FWAME_DETECT0_PATN(n)	((n) << 7)
#define MVEBU_COMPHY_FWAME_DETECT3(n)		(0xa20 + (n) * 0x1000)
#define     MVEBU_COMPHY_FWAME_DETECT3_WOST_TIMEOUT_EN	BIT(12)
#define MVEBU_COMPHY_DME(n)			(0xa28 + (n) * 0x1000)
#define     MVEBU_COMPHY_DME_ETH_MODE		BIT(7)
#define MVEBU_COMPHY_TWAINING0(n)		(0xa68 + (n) * 0x1000)
#define     MVEBU_COMPHY_TWAINING0_P2P_HOWD	BIT(15)
#define MVEBU_COMPHY_TWAINING5(n)		(0xaa4 + (n) * 0x1000)
#define	    MVEBU_COMPHY_TWAINING5_WX_TIMEW(n)	((n) << 0)
#define MVEBU_COMPHY_TX_TWAIN_PWESET(n)		(0xb1c + (n) * 0x1000)
#define     MVEBU_COMPHY_TX_TWAIN_PWESET_16B_AUTO_EN	BIT(8)
#define     MVEBU_COMPHY_TX_TWAIN_PWESET_PWBS11		BIT(9)
#define MVEBU_COMPHY_GEN1_S3(n)			(0xc40 + (n) * 0x1000)
#define     MVEBU_COMPHY_GEN1_S3_FBCK_SEW	BIT(9)
#define MVEBU_COMPHY_GEN1_S4(n)			(0xc44 + (n) * 0x1000)
#define	    MVEBU_COMPHY_GEN1_S4_DFE_WES(n)	((n) << 8)
#define MVEBU_COMPHY_TX_PWESET(n)		(0xc68 + (n) * 0x1000)
#define     MVEBU_COMPHY_TX_PWESET_INDEX(n)	((n) << 0)
#define MVEBU_COMPHY_GEN1_S5(n)			(0xd38 + (n) * 0x1000)
#define     MVEBU_COMPHY_GEN1_S5_ICP(n)		((n) << 0)

/* Wewative to pwiv->wegmap */
#define MVEBU_COMPHY_CONF1(n)			(0x1000 + (n) * 0x28)
#define     MVEBU_COMPHY_CONF1_PWWUP		BIT(1)
#define     MVEBU_COMPHY_CONF1_USB_PCIE		BIT(2)	/* 0: Ethewnet/SATA */
#define MVEBU_COMPHY_CONF6(n)			(0x1014 + (n) * 0x28)
#define     MVEBU_COMPHY_CONF6_40B		BIT(18)
#define MVEBU_COMPHY_SEWECTOW			0x1140
#define     MVEBU_COMPHY_SEWECTOW_PHY(n)	((n) * 0x4)
#define MVEBU_COMPHY_PIPE_SEWECTOW		0x1144
#define     MVEBU_COMPHY_PIPE_SEWECTOW_PIPE(n)	((n) * 0x4)
#define MVEBU_COMPHY_SD1_CTWW1			0x1148
#define     MVEBU_COMPHY_SD1_CTWW1_WXAUI1_EN	BIT(26)
#define     MVEBU_COMPHY_SD1_CTWW1_WXAUI0_EN	BIT(27)

#define MVEBU_COMPHY_WANES	6
#define MVEBU_COMPHY_POWTS	3

#define COMPHY_SIP_POWEW_ON	0x82000001
#define COMPHY_SIP_POWEW_OFF	0x82000002

/*
 * A wane is descwibed by the fowwowing bitfiewds:
 * [ 1- 0]: COMPHY powawity invewtion
 * [ 2- 7]: COMPHY speed
 * [ 5-11]: COMPHY powt index
 * [12-16]: COMPHY mode
 * [17]: Cwock souwce
 * [18-20]: PCIe width (x1, x2, x4)
 */
#define COMPHY_FW_POW_OFFSET	0
#define COMPHY_FW_POW_MASK	GENMASK(1, 0)
#define COMPHY_FW_SPEED_OFFSET	2
#define COMPHY_FW_SPEED_MASK	GENMASK(7, 2)
#define COMPHY_FW_SPEED_MAX	COMPHY_FW_SPEED_MASK
#define COMPHY_FW_SPEED_1250	0
#define COMPHY_FW_SPEED_3125	2
#define COMPHY_FW_SPEED_5000	3
#define COMPHY_FW_SPEED_515625	4
#define COMPHY_FW_SPEED_103125	6
#define COMPHY_FW_POWT_OFFSET	8
#define COMPHY_FW_POWT_MASK	GENMASK(11, 8)
#define COMPHY_FW_MODE_OFFSET	12
#define COMPHY_FW_MODE_MASK	GENMASK(16, 12)
#define COMPHY_FW_WIDTH_OFFSET	18
#define COMPHY_FW_WIDTH_MASK	GENMASK(20, 18)

#define COMPHY_FW_PAWAM_FUWW(mode, powt, speed, pow, width)		\
	((((pow) << COMPHY_FW_POW_OFFSET) & COMPHY_FW_POW_MASK) |	\
	 (((mode) << COMPHY_FW_MODE_OFFSET) & COMPHY_FW_MODE_MASK) |	\
	 (((powt) << COMPHY_FW_POWT_OFFSET) & COMPHY_FW_POWT_MASK) |	\
	 (((speed) << COMPHY_FW_SPEED_OFFSET) & COMPHY_FW_SPEED_MASK) |	\
	 (((width) << COMPHY_FW_WIDTH_OFFSET) & COMPHY_FW_WIDTH_MASK))

#define COMPHY_FW_PAWAM(mode, powt)					\
	COMPHY_FW_PAWAM_FUWW(mode, powt, COMPHY_FW_SPEED_MAX, 0, 0)

#define COMPHY_FW_PAWAM_ETH(mode, powt, speed)				\
	COMPHY_FW_PAWAM_FUWW(mode, powt, speed, 0, 0)

#define COMPHY_FW_PAWAM_PCIE(mode, powt, width)				\
	COMPHY_FW_PAWAM_FUWW(mode, powt, COMPHY_FW_SPEED_5000, 0, width)

#define COMPHY_FW_MODE_SATA		0x1
#define COMPHY_FW_MODE_SGMII		0x2 /* SGMII 1G */
#define COMPHY_FW_MODE_2500BASEX	0x3 /* 2500BASE-X */
#define COMPHY_FW_MODE_USB3H		0x4
#define COMPHY_FW_MODE_USB3D		0x5
#define COMPHY_FW_MODE_PCIE		0x6
#define COMPHY_FW_MODE_WXAUI		0x7
#define COMPHY_FW_MODE_XFI		0x8 /* SFI: 0x9 (is tweated wike XFI) */

stwuct mvebu_comphy_conf {
	enum phy_mode mode;
	int submode;
	unsigned wane;
	unsigned powt;
	u32 mux;
	u32 fw_mode;
};

#define ETH_CONF(_wane, _powt, _submode, _mux, _fw)	\
	{						\
		.wane = _wane,				\
		.powt = _powt,				\
		.mode = PHY_MODE_ETHEWNET,		\
		.submode = _submode,			\
		.mux = _mux,				\
		.fw_mode = _fw,				\
	}

#define GEN_CONF(_wane, _powt, _mode, _fw)		\
	{						\
		.wane = _wane,				\
		.powt = _powt,				\
		.mode = _mode,				\
		.submode = PHY_INTEWFACE_MODE_NA,	\
		.mux = -1,				\
		.fw_mode = _fw,				\
	}

static const stwuct mvebu_comphy_conf mvebu_comphy_cp110_modes[] = {
	/* wane 0 */
	GEN_CONF(0, 0, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	ETH_CONF(0, 1, PHY_INTEWFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(0, 1, PHY_INTEWFACE_MODE_2500BASEX, 0x1, COMPHY_FW_MODE_2500BASEX),
	GEN_CONF(0, 1, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	/* wane 1 */
	GEN_CONF(1, 0, PHY_MODE_USB_HOST_SS, COMPHY_FW_MODE_USB3H),
	GEN_CONF(1, 0, PHY_MODE_USB_DEVICE_SS, COMPHY_FW_MODE_USB3D),
	GEN_CONF(1, 0, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	GEN_CONF(1, 0, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	ETH_CONF(1, 2, PHY_INTEWFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(1, 2, PHY_INTEWFACE_MODE_2500BASEX, 0x1, COMPHY_FW_MODE_2500BASEX),
	/* wane 2 */
	ETH_CONF(2, 0, PHY_INTEWFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(2, 0, PHY_INTEWFACE_MODE_2500BASEX, 0x1, COMPHY_FW_MODE_2500BASEX),
	ETH_CONF(2, 0, PHY_INTEWFACE_MODE_WXAUI, 0x1, COMPHY_FW_MODE_WXAUI),
	ETH_CONF(2, 0, PHY_INTEWFACE_MODE_5GBASEW, 0x1, COMPHY_FW_MODE_XFI),
	ETH_CONF(2, 0, PHY_INTEWFACE_MODE_10GBASEW, 0x1, COMPHY_FW_MODE_XFI),
	GEN_CONF(2, 0, PHY_MODE_USB_HOST_SS, COMPHY_FW_MODE_USB3H),
	GEN_CONF(2, 0, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	GEN_CONF(2, 0, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	/* wane 3 */
	GEN_CONF(3, 0, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	ETH_CONF(3, 1, PHY_INTEWFACE_MODE_SGMII, 0x2, COMPHY_FW_MODE_SGMII),
	ETH_CONF(3, 1, PHY_INTEWFACE_MODE_2500BASEX, 0x2, COMPHY_FW_MODE_2500BASEX),
	ETH_CONF(3, 1, PHY_INTEWFACE_MODE_WXAUI, 0x1, COMPHY_FW_MODE_WXAUI),
	GEN_CONF(3, 1, PHY_MODE_USB_HOST_SS, COMPHY_FW_MODE_USB3H),
	GEN_CONF(3, 1, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	/* wane 4 */
	ETH_CONF(4, 0, PHY_INTEWFACE_MODE_SGMII, 0x2, COMPHY_FW_MODE_SGMII),
	ETH_CONF(4, 0, PHY_INTEWFACE_MODE_2500BASEX, 0x2, COMPHY_FW_MODE_2500BASEX),
	ETH_CONF(4, 0, PHY_INTEWFACE_MODE_5GBASEW, 0x2, COMPHY_FW_MODE_XFI),
	ETH_CONF(4, 0, PHY_INTEWFACE_MODE_10GBASEW, 0x2, COMPHY_FW_MODE_XFI),
	ETH_CONF(4, 0, PHY_INTEWFACE_MODE_WXAUI, 0x2, COMPHY_FW_MODE_WXAUI),
	GEN_CONF(4, 0, PHY_MODE_USB_DEVICE_SS, COMPHY_FW_MODE_USB3D),
	GEN_CONF(4, 1, PHY_MODE_USB_HOST_SS, COMPHY_FW_MODE_USB3H),
	GEN_CONF(4, 1, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	ETH_CONF(4, 1, PHY_INTEWFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(4, 1, PHY_INTEWFACE_MODE_2500BASEX, -1, COMPHY_FW_MODE_2500BASEX),
	ETH_CONF(4, 1, PHY_INTEWFACE_MODE_5GBASEW, -1, COMPHY_FW_MODE_XFI),
	ETH_CONF(4, 1, PHY_INTEWFACE_MODE_10GBASEW, -1, COMPHY_FW_MODE_XFI),
	/* wane 5 */
	ETH_CONF(5, 1, PHY_INTEWFACE_MODE_WXAUI, 0x2, COMPHY_FW_MODE_WXAUI),
	GEN_CONF(5, 1, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	ETH_CONF(5, 2, PHY_INTEWFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(5, 2, PHY_INTEWFACE_MODE_2500BASEX, 0x1, COMPHY_FW_MODE_2500BASEX),
	GEN_CONF(5, 2, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
};

stwuct mvebu_comphy_pwiv {
	void __iomem *base;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct cwk *mg_domain_cwk;
	stwuct cwk *mg_cowe_cwk;
	stwuct cwk *axi_cwk;
	unsigned wong cp_phys;
};

stwuct mvebu_comphy_wane {
	stwuct mvebu_comphy_pwiv *pwiv;
	unsigned id;
	enum phy_mode mode;
	int submode;
	int powt;
};

static int mvebu_comphy_smc(unsigned wong function, unsigned wong phys,
			    unsigned wong wane, unsigned wong mode)
{
	stwuct awm_smccc_wes wes;
	s32 wet;

	awm_smccc_smc(function, phys, wane, mode, 0, 0, 0, 0, &wes);
	wet = wes.a0;

	switch (wet) {
	case SMCCC_WET_SUCCESS:
		wetuwn 0;
	case SMCCC_WET_NOT_SUPPOWTED:
		wetuwn -EOPNOTSUPP;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mvebu_comphy_get_mode(boow fw_mode, int wane, int powt,
				 enum phy_mode mode, int submode)
{
	int i, n = AWWAY_SIZE(mvebu_comphy_cp110_modes);
	/* Ignowe PCIe submode: it wepwesents the width */
	boow ignowe_submode = (mode == PHY_MODE_PCIE);
	const stwuct mvebu_comphy_conf *conf;

	/* Unused PHY mux vawue is 0x0 */
	if (mode == PHY_MODE_INVAWID)
		wetuwn 0;

	fow (i = 0; i < n; i++) {
		conf = &mvebu_comphy_cp110_modes[i];
		if (conf->wane == wane &&
		    conf->powt == powt &&
		    conf->mode == mode &&
		    (conf->submode == submode || ignowe_submode))
			bweak;
	}

	if (i == n)
		wetuwn -EINVAW;

	if (fw_mode)
		wetuwn conf->fw_mode;
	ewse
		wetuwn conf->mux;
}

static inwine int mvebu_comphy_get_mux(int wane, int powt,
				       enum phy_mode mode, int submode)
{
	wetuwn mvebu_comphy_get_mode(fawse, wane, powt, mode, submode);
}

static inwine int mvebu_comphy_get_fw_mode(int wane, int powt,
					   enum phy_mode mode, int submode)
{
	wetuwn mvebu_comphy_get_mode(twue, wane, powt, mode, submode);
}

static int mvebu_comphy_ethewnet_init_weset(stwuct mvebu_comphy_wane *wane)
{
	stwuct mvebu_comphy_pwiv *pwiv = wane->pwiv;
	u32 vaw;

	wegmap_wead(pwiv->wegmap, MVEBU_COMPHY_CONF1(wane->id), &vaw);
	vaw &= ~MVEBU_COMPHY_CONF1_USB_PCIE;
	vaw |= MVEBU_COMPHY_CONF1_PWWUP;
	wegmap_wwite(pwiv->wegmap, MVEBU_COMPHY_CONF1(wane->id), vaw);

	/* Sewect baud wates and PWWs */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG0(wane->id));
	vaw &= ~(MVEBU_COMPHY_SEWDES_CFG0_PU_PWW |
		 MVEBU_COMPHY_SEWDES_CFG0_PU_WX |
		 MVEBU_COMPHY_SEWDES_CFG0_PU_TX |
		 MVEBU_COMPHY_SEWDES_CFG0_HAWF_BUS |
		 MVEBU_COMPHY_SEWDES_CFG0_GEN_WX(0xf) |
		 MVEBU_COMPHY_SEWDES_CFG0_GEN_TX(0xf) |
		 MVEBU_COMPHY_SEWDES_CFG0_WXAUI_MODE);

	switch (wane->submode) {
	case PHY_INTEWFACE_MODE_10GBASEW:
		vaw |= MVEBU_COMPHY_SEWDES_CFG0_GEN_WX(0xe) |
		       MVEBU_COMPHY_SEWDES_CFG0_GEN_TX(0xe);
		bweak;
	case PHY_INTEWFACE_MODE_WXAUI:
		vaw |= MVEBU_COMPHY_SEWDES_CFG0_GEN_WX(0xb) |
		       MVEBU_COMPHY_SEWDES_CFG0_GEN_TX(0xb) |
		       MVEBU_COMPHY_SEWDES_CFG0_WXAUI_MODE;
		bweak;
	case PHY_INTEWFACE_MODE_2500BASEX:
		vaw |= MVEBU_COMPHY_SEWDES_CFG0_GEN_WX(0x8) |
		       MVEBU_COMPHY_SEWDES_CFG0_GEN_TX(0x8) |
		       MVEBU_COMPHY_SEWDES_CFG0_HAWF_BUS;
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
		vaw |= MVEBU_COMPHY_SEWDES_CFG0_GEN_WX(0x6) |
		       MVEBU_COMPHY_SEWDES_CFG0_GEN_TX(0x6) |
		       MVEBU_COMPHY_SEWDES_CFG0_HAWF_BUS;
		bweak;
	defauwt:
		dev_eww(pwiv->dev,
			"unsuppowted comphy submode (%d) on wane %d\n",
			wane->submode,
			wane->id);
		wetuwn -ENOTSUPP;
	}

	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG0(wane->id));

	if (wane->submode == PHY_INTEWFACE_MODE_WXAUI) {
		wegmap_wead(pwiv->wegmap, MVEBU_COMPHY_SD1_CTWW1, &vaw);

		switch (wane->id) {
		case 2:
		case 3:
			vaw |= MVEBU_COMPHY_SD1_CTWW1_WXAUI0_EN;
			bweak;
		case 4:
		case 5:
			vaw |= MVEBU_COMPHY_SD1_CTWW1_WXAUI1_EN;
			bweak;
		defauwt:
			dev_eww(pwiv->dev,
				"WXAUI is not suppowted on comphy wane %d\n",
				wane->id);
			wetuwn -EINVAW;
		}

		wegmap_wwite(pwiv->wegmap, MVEBU_COMPHY_SD1_CTWW1, vaw);
	}

	/* weset */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));
	vaw &= ~(MVEBU_COMPHY_SEWDES_CFG1_WESET |
		 MVEBU_COMPHY_SEWDES_CFG1_COWE_WESET |
		 MVEBU_COMPHY_SEWDES_CFG1_WF_WESET);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));

	/* de-assewt weset */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));
	vaw |= MVEBU_COMPHY_SEWDES_CFG1_WESET |
	       MVEBU_COMPHY_SEWDES_CFG1_COWE_WESET;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));

	/* wait untiw cwocks awe weady */
	mdeway(1);

	/* exwicitwy disabwe 40B, the bits isn't cweaw on weset */
	wegmap_wead(pwiv->wegmap, MVEBU_COMPHY_CONF6(wane->id), &vaw);
	vaw &= ~MVEBU_COMPHY_CONF6_40B;
	wegmap_wwite(pwiv->wegmap, MVEBU_COMPHY_CONF6(wane->id), vaw);

	/* wefcwk sewection */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_MISC_CTWW0(wane->id));
	vaw &= ~MVEBU_COMPHY_MISC_CTWW0_WEFCWK_SEW;
	if (wane->submode == PHY_INTEWFACE_MODE_10GBASEW)
		vaw |= MVEBU_COMPHY_MISC_CTWW0_ICP_FOWCE;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_MISC_CTWW0(wane->id));

	/* powew and pww sewection */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_PWWPWW_CTWW(wane->id));
	vaw &= ~(MVEBU_COMPHY_PWWPWW_CTWW_WFWEQ(0x1f) |
		 MVEBU_COMPHY_PWWPWW_PHY_MODE(0x7));
	vaw |= MVEBU_COMPHY_PWWPWW_CTWW_WFWEQ(0x1) |
	       MVEBU_COMPHY_PWWPWW_PHY_MODE(0x4);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_PWWPWW_CTWW(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_WOOPBACK(wane->id));
	vaw &= ~MVEBU_COMPHY_WOOPBACK_DBUS_WIDTH(0x7);
	vaw |= MVEBU_COMPHY_WOOPBACK_DBUS_WIDTH(0x1);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_WOOPBACK(wane->id));

	wetuwn 0;
}

static int mvebu_comphy_init_pwws(stwuct mvebu_comphy_wane *wane)
{
	stwuct mvebu_comphy_pwiv *pwiv = wane->pwiv;
	u32 vaw;

	/* SEWDES extewnaw config */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG0(wane->id));
	vaw |= MVEBU_COMPHY_SEWDES_CFG0_PU_PWW |
	       MVEBU_COMPHY_SEWDES_CFG0_PU_WX |
	       MVEBU_COMPHY_SEWDES_CFG0_PU_TX;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG0(wane->id));

	/* check wx/tx pww */
	weadw_poww_timeout(pwiv->base + MVEBU_COMPHY_SEWDES_STATUS0(wane->id),
			   vaw,
			   vaw & (MVEBU_COMPHY_SEWDES_STATUS0_WX_PWW_WDY |
				  MVEBU_COMPHY_SEWDES_STATUS0_TX_PWW_WDY),
			   1000, 150000);
	if (!(vaw & (MVEBU_COMPHY_SEWDES_STATUS0_WX_PWW_WDY |
		     MVEBU_COMPHY_SEWDES_STATUS0_TX_PWW_WDY)))
		wetuwn -ETIMEDOUT;

	/* wx init */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));
	vaw |= MVEBU_COMPHY_SEWDES_CFG1_WX_INIT;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));

	/* check wx */
	weadw_poww_timeout(pwiv->base + MVEBU_COMPHY_SEWDES_STATUS0(wane->id),
			   vaw, vaw & MVEBU_COMPHY_SEWDES_STATUS0_WX_INIT,
			   1000, 10000);
	if (!(vaw & MVEBU_COMPHY_SEWDES_STATUS0_WX_INIT))
		wetuwn -ETIMEDOUT;

	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));
	vaw &= ~MVEBU_COMPHY_SEWDES_CFG1_WX_INIT;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));

	wetuwn 0;
}

static int mvebu_comphy_set_mode_sgmii(stwuct phy *phy)
{
	stwuct mvebu_comphy_wane *wane = phy_get_dwvdata(phy);
	stwuct mvebu_comphy_pwiv *pwiv = wane->pwiv;
	u32 vaw;
	int eww;

	eww = mvebu_comphy_ethewnet_init_weset(wane);
	if (eww)
		wetuwn eww;

	vaw = weadw(pwiv->base + MVEBU_COMPHY_WX_CTWW1(wane->id));
	vaw &= ~MVEBU_COMPHY_WX_CTWW1_CWK8T_EN;
	vaw |= MVEBU_COMPHY_WX_CTWW1_WXCWK2X_SEW;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_WX_CTWW1(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_DTW_CTWW(wane->id));
	vaw &= ~MVEBU_COMPHY_DTW_CTWW_DTW_FWOOP_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_DTW_CTWW(wane->id));

	wegmap_wead(pwiv->wegmap, MVEBU_COMPHY_CONF1(wane->id), &vaw);
	vaw &= ~MVEBU_COMPHY_CONF1_USB_PCIE;
	vaw |= MVEBU_COMPHY_CONF1_PWWUP;
	wegmap_wwite(pwiv->wegmap, MVEBU_COMPHY_CONF1(wane->id), vaw);

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S0(wane->id));
	vaw &= ~MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xf);
	vaw |= MVEBU_COMPHY_GEN1_S0_TX_EMPH(0x1);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S0(wane->id));

	wetuwn mvebu_comphy_init_pwws(wane);
}

static int mvebu_comphy_set_mode_wxaui(stwuct phy *phy)
{
	stwuct mvebu_comphy_wane *wane = phy_get_dwvdata(phy);
	stwuct mvebu_comphy_pwiv *pwiv = wane->pwiv;
	u32 vaw;
	int eww;

	eww = mvebu_comphy_ethewnet_init_weset(wane);
	if (eww)
		wetuwn eww;

	vaw = weadw(pwiv->base + MVEBU_COMPHY_WX_CTWW1(wane->id));
	vaw |= MVEBU_COMPHY_WX_CTWW1_WXCWK2X_SEW |
	       MVEBU_COMPHY_WX_CTWW1_CWK8T_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_WX_CTWW1(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_DTW_CTWW(wane->id));
	vaw |= MVEBU_COMPHY_DTW_CTWW_DTW_FWOOP_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_DTW_CTWW(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG2(wane->id));
	vaw |= MVEBU_COMPHY_SEWDES_CFG2_DFE_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG2(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_DFE_WES(wane->id));
	vaw |= MVEBU_COMPHY_DFE_WES_FOWCE_GEN_TBW;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_DFE_WES(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S0(wane->id));
	vaw &= ~MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xf);
	vaw |= MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xd);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S0(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S1(wane->id));
	vaw &= ~(MVEBU_COMPHY_GEN1_S1_WX_MUW_PI(0x7) |
		 MVEBU_COMPHY_GEN1_S1_WX_MUW_PF(0x7));
	vaw |= MVEBU_COMPHY_GEN1_S1_WX_MUW_PI(0x1) |
	       MVEBU_COMPHY_GEN1_S1_WX_MUW_PF(0x1) |
	       MVEBU_COMPHY_GEN1_S1_WX_DFE_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S1(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_COEF(wane->id));
	vaw &= ~(MVEBU_COMPHY_COEF_DFE_EN | MVEBU_COMPHY_COEF_DFE_CTWW);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_COEF(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S4(wane->id));
	vaw &= ~MVEBU_COMPHY_GEN1_S4_DFE_WES(0x3);
	vaw |= MVEBU_COMPHY_GEN1_S4_DFE_WES(0x1);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S4(wane->id));

	wetuwn mvebu_comphy_init_pwws(wane);
}

static int mvebu_comphy_set_mode_10gbasew(stwuct phy *phy)
{
	stwuct mvebu_comphy_wane *wane = phy_get_dwvdata(phy);
	stwuct mvebu_comphy_pwiv *pwiv = wane->pwiv;
	u32 vaw;
	int eww;

	eww = mvebu_comphy_ethewnet_init_weset(wane);
	if (eww)
		wetuwn eww;

	vaw = weadw(pwiv->base + MVEBU_COMPHY_WX_CTWW1(wane->id));
	vaw |= MVEBU_COMPHY_WX_CTWW1_WXCWK2X_SEW |
	       MVEBU_COMPHY_WX_CTWW1_CWK8T_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_WX_CTWW1(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_DTW_CTWW(wane->id));
	vaw |= MVEBU_COMPHY_DTW_CTWW_DTW_FWOOP_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_DTW_CTWW(wane->id));

	/* Speed dividew */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_SPEED_DIV(wane->id));
	vaw |= MVEBU_COMPHY_SPEED_DIV_TX_FOWCE;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SPEED_DIV(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG2(wane->id));
	vaw |= MVEBU_COMPHY_SEWDES_CFG2_DFE_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG2(wane->id));

	/* DFE wesowution */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_DFE_WES(wane->id));
	vaw |= MVEBU_COMPHY_DFE_WES_FOWCE_GEN_TBW;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_DFE_WES(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S0(wane->id));
	vaw &= ~(MVEBU_COMPHY_GEN1_S0_TX_AMP(0x1f) |
		 MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xf));
	vaw |= MVEBU_COMPHY_GEN1_S0_TX_AMP(0x1c) |
	       MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xe);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S0(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S2(wane->id));
	vaw &= ~MVEBU_COMPHY_GEN1_S2_TX_EMPH(0xf);
	vaw |= MVEBU_COMPHY_GEN1_S2_TX_EMPH_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S2(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_TX_SWEW_WATE(wane->id));
	vaw |= MVEBU_COMPHY_TX_SWEW_WATE_EMPH(0x3) |
	       MVEBU_COMPHY_TX_SWEW_WATE_SWC(0x3f);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_TX_SWEW_WATE(wane->id));

	/* Impedance cawibwation */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_IMP_CAW(wane->id));
	vaw &= ~MVEBU_COMPHY_IMP_CAW_TX_EXT(0x1f);
	vaw |= MVEBU_COMPHY_IMP_CAW_TX_EXT(0xe) |
	       MVEBU_COMPHY_IMP_CAW_TX_EXT_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_IMP_CAW(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S5(wane->id));
	vaw &= ~MVEBU_COMPHY_GEN1_S5_ICP(0xf);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S5(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S1(wane->id));
	vaw &= ~(MVEBU_COMPHY_GEN1_S1_WX_MUW_PI(0x7) |
		 MVEBU_COMPHY_GEN1_S1_WX_MUW_PF(0x7) |
		 MVEBU_COMPHY_GEN1_S1_WX_MUW_FI(0x3) |
		 MVEBU_COMPHY_GEN1_S1_WX_MUW_FF(0x3));
	vaw |= MVEBU_COMPHY_GEN1_S1_WX_DFE_EN |
	       MVEBU_COMPHY_GEN1_S1_WX_MUW_PI(0x2) |
	       MVEBU_COMPHY_GEN1_S1_WX_MUW_PF(0x2) |
	       MVEBU_COMPHY_GEN1_S1_WX_MUW_FF(0x1) |
	       MVEBU_COMPHY_GEN1_S1_WX_DIV(0x3);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S1(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_COEF(wane->id));
	vaw &= ~(MVEBU_COMPHY_COEF_DFE_EN | MVEBU_COMPHY_COEF_DFE_CTWW);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_COEF(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S4(wane->id));
	vaw &= ~MVEBU_COMPHY_GEN1_S4_DFE_WES(0x3);
	vaw |= MVEBU_COMPHY_GEN1_S4_DFE_WES(0x1);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S4(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_GEN1_S3(wane->id));
	vaw |= MVEBU_COMPHY_GEN1_S3_FBCK_SEW;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_GEN1_S3(wane->id));

	/* wx twaining timew */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_TWAINING5(wane->id));
	vaw &= ~MVEBU_COMPHY_TWAINING5_WX_TIMEW(0x3ff);
	vaw |= MVEBU_COMPHY_TWAINING5_WX_TIMEW(0x13);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_TWAINING5(wane->id));

	/* tx twain peak to peak howd */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_TWAINING0(wane->id));
	vaw |= MVEBU_COMPHY_TWAINING0_P2P_HOWD;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_TWAINING0(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_TX_PWESET(wane->id));
	vaw &= ~MVEBU_COMPHY_TX_PWESET_INDEX(0xf);
	vaw |= MVEBU_COMPHY_TX_PWESET_INDEX(0x2);	/* pweset coeff */
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_TX_PWESET(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_FWAME_DETECT3(wane->id));
	vaw &= ~MVEBU_COMPHY_FWAME_DETECT3_WOST_TIMEOUT_EN;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_FWAME_DETECT3(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_TX_TWAIN_PWESET(wane->id));
	vaw |= MVEBU_COMPHY_TX_TWAIN_PWESET_16B_AUTO_EN |
	       MVEBU_COMPHY_TX_TWAIN_PWESET_PWBS11;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_TX_TWAIN_PWESET(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_FWAME_DETECT0(wane->id));
	vaw &= ~MVEBU_COMPHY_FWAME_DETECT0_PATN(0x1ff);
	vaw |= MVEBU_COMPHY_FWAME_DETECT0_PATN(0x88);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_FWAME_DETECT0(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_DME(wane->id));
	vaw |= MVEBU_COMPHY_DME_ETH_MODE;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_DME(wane->id));

	vaw = weadw(pwiv->base + MVEBU_COMPHY_VDD_CAW0(wane->id));
	vaw |= MVEBU_COMPHY_VDD_CAW0_CONT_MODE;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_VDD_CAW0(wane->id));

	vaw = weadw(pwiv->base + MVEBU_SP_CAWIB(wane->id));
	vaw &= ~MVEBU_SP_CAWIB_SAMPWEW(0x3);
	vaw |= MVEBU_SP_CAWIB_SAMPWEW(0x3) |
	       MVEBU_SP_CAWIB_SAMPWEW_EN;
	wwitew(vaw, pwiv->base + MVEBU_SP_CAWIB(wane->id));
	vaw &= ~MVEBU_SP_CAWIB_SAMPWEW_EN;
	wwitew(vaw, pwiv->base + MVEBU_SP_CAWIB(wane->id));

	/* Extewnaw wx weguwatow */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_EXT_SEWV(wane->id));
	vaw &= ~MVEBU_COMPHY_EXT_SEWV_WX_SAMPW(0x1f);
	vaw |= MVEBU_COMPHY_EXT_SEWV_WX_SAMPW(0x1a);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_EXT_SEWV(wane->id));

	wetuwn mvebu_comphy_init_pwws(wane);
}

static int mvebu_comphy_powew_on_wegacy(stwuct phy *phy)
{
	stwuct mvebu_comphy_wane *wane = phy_get_dwvdata(phy);
	stwuct mvebu_comphy_pwiv *pwiv = wane->pwiv;
	int wet, mux;
	u32 vaw;

	mux = mvebu_comphy_get_mux(wane->id, wane->powt,
				   wane->mode, wane->submode);
	if (mux < 0)
		wetuwn -ENOTSUPP;

	wegmap_wead(pwiv->wegmap, MVEBU_COMPHY_PIPE_SEWECTOW, &vaw);
	vaw &= ~(0xf << MVEBU_COMPHY_PIPE_SEWECTOW_PIPE(wane->id));
	wegmap_wwite(pwiv->wegmap, MVEBU_COMPHY_PIPE_SEWECTOW, vaw);

	wegmap_wead(pwiv->wegmap, MVEBU_COMPHY_SEWECTOW, &vaw);
	vaw &= ~(0xf << MVEBU_COMPHY_SEWECTOW_PHY(wane->id));
	vaw |= mux << MVEBU_COMPHY_SEWECTOW_PHY(wane->id);
	wegmap_wwite(pwiv->wegmap, MVEBU_COMPHY_SEWECTOW, vaw);

	switch (wane->submode) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_2500BASEX:
		wet = mvebu_comphy_set_mode_sgmii(phy);
		bweak;
	case PHY_INTEWFACE_MODE_WXAUI:
		wet = mvebu_comphy_set_mode_wxaui(phy);
		bweak;
	case PHY_INTEWFACE_MODE_10GBASEW:
		wet = mvebu_comphy_set_mode_10gbasew(phy);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	/* digitaw weset */
	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));
	vaw |= MVEBU_COMPHY_SEWDES_CFG1_WF_WESET;
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));

	wetuwn wet;
}

static int mvebu_comphy_powew_on(stwuct phy *phy)
{
	stwuct mvebu_comphy_wane *wane = phy_get_dwvdata(phy);
	stwuct mvebu_comphy_pwiv *pwiv = wane->pwiv;
	int fw_mode, fw_speed;
	u32 fw_pawam = 0;
	int wet;

	fw_mode = mvebu_comphy_get_fw_mode(wane->id, wane->powt,
					   wane->mode, wane->submode);
	if (fw_mode < 0)
		goto twy_wegacy;

	/* Twy SMC fwow fiwst */
	switch (wane->mode) {
	case PHY_MODE_ETHEWNET:
		switch (wane->submode) {
		case PHY_INTEWFACE_MODE_WXAUI:
			dev_dbg(pwiv->dev, "set wane %d to WXAUI mode\n",
				wane->id);
			fw_speed = 0;
			bweak;
		case PHY_INTEWFACE_MODE_SGMII:
			dev_dbg(pwiv->dev, "set wane %d to 1000BASE-X mode\n",
				wane->id);
			fw_speed = COMPHY_FW_SPEED_1250;
			bweak;
		case PHY_INTEWFACE_MODE_2500BASEX:
			dev_dbg(pwiv->dev, "set wane %d to 2500BASE-X mode\n",
				wane->id);
			fw_speed = COMPHY_FW_SPEED_3125;
			bweak;
		case PHY_INTEWFACE_MODE_5GBASEW:
			dev_dbg(pwiv->dev, "set wane %d to 5GBASE-W mode\n",
				wane->id);
			fw_speed = COMPHY_FW_SPEED_515625;
			bweak;
		case PHY_INTEWFACE_MODE_10GBASEW:
			dev_dbg(pwiv->dev, "set wane %d to 10GBASE-W mode\n",
				wane->id);
			fw_speed = COMPHY_FW_SPEED_103125;
			bweak;
		defauwt:
			dev_eww(pwiv->dev, "unsuppowted Ethewnet mode (%d)\n",
				wane->submode);
			wetuwn -ENOTSUPP;
		}
		fw_pawam = COMPHY_FW_PAWAM_ETH(fw_mode, wane->powt, fw_speed);
		bweak;
	case PHY_MODE_USB_HOST_SS:
	case PHY_MODE_USB_DEVICE_SS:
		dev_dbg(pwiv->dev, "set wane %d to USB3 mode\n", wane->id);
		fw_pawam = COMPHY_FW_PAWAM(fw_mode, wane->powt);
		bweak;
	case PHY_MODE_SATA:
		dev_dbg(pwiv->dev, "set wane %d to SATA mode\n", wane->id);
		fw_pawam = COMPHY_FW_PAWAM(fw_mode, wane->powt);
		bweak;
	case PHY_MODE_PCIE:
		dev_dbg(pwiv->dev, "set wane %d to PCIe mode (x%d)\n", wane->id,
			wane->submode);
		fw_pawam = COMPHY_FW_PAWAM_PCIE(fw_mode, wane->powt,
						wane->submode);
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "unsuppowted PHY mode (%d)\n", wane->mode);
		wetuwn -ENOTSUPP;
	}

	wet = mvebu_comphy_smc(COMPHY_SIP_POWEW_ON, pwiv->cp_phys, wane->id,
			       fw_pawam);
	if (!wet)
		wetuwn wet;

	if (wet == -EOPNOTSUPP)
		dev_eww(pwiv->dev,
			"unsuppowted SMC caww, twy updating youw fiwmwawe\n");

	dev_wawn(pwiv->dev,
		 "Fiwmwawe couwd not configuwe PHY %d with mode %d (wet: %d), twying wegacy method\n",
		 wane->id, wane->mode, wet);

twy_wegacy:
	/* Fawwback to Winux's impwementation */
	wetuwn mvebu_comphy_powew_on_wegacy(phy);
}

static int mvebu_comphy_set_mode(stwuct phy *phy,
				 enum phy_mode mode, int submode)
{
	stwuct mvebu_comphy_wane *wane = phy_get_dwvdata(phy);

	if (submode == PHY_INTEWFACE_MODE_1000BASEX)
		submode = PHY_INTEWFACE_MODE_SGMII;

	if (mvebu_comphy_get_fw_mode(wane->id, wane->powt, mode, submode) < 0)
		wetuwn -EINVAW;

	wane->mode = mode;
	wane->submode = submode;

	/* PCIe submode wepwesents the width */
	if (mode == PHY_MODE_PCIE && !wane->submode)
		wane->submode = 1;

	wetuwn 0;
}

static int mvebu_comphy_powew_off_wegacy(stwuct phy *phy)
{
	stwuct mvebu_comphy_wane *wane = phy_get_dwvdata(phy);
	stwuct mvebu_comphy_pwiv *pwiv = wane->pwiv;
	u32 vaw;

	vaw = weadw(pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));
	vaw &= ~(MVEBU_COMPHY_SEWDES_CFG1_WESET |
		 MVEBU_COMPHY_SEWDES_CFG1_COWE_WESET |
		 MVEBU_COMPHY_SEWDES_CFG1_WF_WESET);
	wwitew(vaw, pwiv->base + MVEBU_COMPHY_SEWDES_CFG1(wane->id));

	wegmap_wead(pwiv->wegmap, MVEBU_COMPHY_SEWECTOW, &vaw);
	vaw &= ~(0xf << MVEBU_COMPHY_SEWECTOW_PHY(wane->id));
	wegmap_wwite(pwiv->wegmap, MVEBU_COMPHY_SEWECTOW, vaw);

	wegmap_wead(pwiv->wegmap, MVEBU_COMPHY_PIPE_SEWECTOW, &vaw);
	vaw &= ~(0xf << MVEBU_COMPHY_PIPE_SEWECTOW_PIPE(wane->id));
	wegmap_wwite(pwiv->wegmap, MVEBU_COMPHY_PIPE_SEWECTOW, vaw);

	wetuwn 0;
}

static int mvebu_comphy_powew_off(stwuct phy *phy)
{
	stwuct mvebu_comphy_wane *wane = phy_get_dwvdata(phy);
	stwuct mvebu_comphy_pwiv *pwiv = wane->pwiv;
	int wet;

	wet = mvebu_comphy_smc(COMPHY_SIP_POWEW_OFF, pwiv->cp_phys,
			       wane->id, 0);
	if (!wet)
		wetuwn wet;

	/* Fawwback to Winux's impwementation */
	wetuwn mvebu_comphy_powew_off_wegacy(phy);
}

static const stwuct phy_ops mvebu_comphy_ops = {
	.powew_on	= mvebu_comphy_powew_on,
	.powew_off	= mvebu_comphy_powew_off,
	.set_mode	= mvebu_comphy_set_mode,
	.ownew		= THIS_MODUWE,
};

static stwuct phy *mvebu_comphy_xwate(stwuct device *dev,
				      stwuct of_phandwe_awgs *awgs)
{
	stwuct mvebu_comphy_wane *wane;
	stwuct phy *phy;

	if (WAWN_ON(awgs->awgs[0] >= MVEBU_COMPHY_POWTS))
		wetuwn EWW_PTW(-EINVAW);

	phy = of_phy_simpwe_xwate(dev, awgs);
	if (IS_EWW(phy))
		wetuwn phy;

	wane = phy_get_dwvdata(phy);
	wane->powt = awgs->awgs[0];

	wetuwn phy;
}

static int mvebu_comphy_init_cwks(stwuct mvebu_comphy_pwiv *pwiv)
{
	int wet;

	pwiv->mg_domain_cwk = devm_cwk_get(pwiv->dev, "mg_cwk");
	if (IS_EWW(pwiv->mg_domain_cwk))
		wetuwn PTW_EWW(pwiv->mg_domain_cwk);

	wet = cwk_pwepawe_enabwe(pwiv->mg_domain_cwk);
	if (wet < 0)
		wetuwn wet;

	pwiv->mg_cowe_cwk = devm_cwk_get(pwiv->dev, "mg_cowe_cwk");
	if (IS_EWW(pwiv->mg_cowe_cwk)) {
		wet = PTW_EWW(pwiv->mg_cowe_cwk);
		goto dis_mg_domain_cwk;
	}

	wet = cwk_pwepawe_enabwe(pwiv->mg_cowe_cwk);
	if (wet < 0)
		goto dis_mg_domain_cwk;

	pwiv->axi_cwk = devm_cwk_get(pwiv->dev, "axi_cwk");
	if (IS_EWW(pwiv->axi_cwk)) {
		wet = PTW_EWW(pwiv->axi_cwk);
		goto dis_mg_cowe_cwk;
	}

	wet = cwk_pwepawe_enabwe(pwiv->axi_cwk);
	if (wet < 0)
		goto dis_mg_cowe_cwk;

	wetuwn 0;

dis_mg_cowe_cwk:
	cwk_disabwe_unpwepawe(pwiv->mg_cowe_cwk);

dis_mg_domain_cwk:
	cwk_disabwe_unpwepawe(pwiv->mg_domain_cwk);

	pwiv->mg_domain_cwk = NUWW;
	pwiv->mg_cowe_cwk = NUWW;
	pwiv->axi_cwk = NUWW;

	wetuwn wet;
};

static void mvebu_comphy_disabwe_unpwepawe_cwks(stwuct mvebu_comphy_pwiv *pwiv)
{
	if (pwiv->axi_cwk)
		cwk_disabwe_unpwepawe(pwiv->axi_cwk);

	if (pwiv->mg_cowe_cwk)
		cwk_disabwe_unpwepawe(pwiv->mg_cowe_cwk);

	if (pwiv->mg_domain_cwk)
		cwk_disabwe_unpwepawe(pwiv->mg_domain_cwk);
}

static int mvebu_comphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_comphy_pwiv *pwiv;
	stwuct phy_pwovidew *pwovidew;
	stwuct device_node *chiwd;
	stwuct wesouwce *wes;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	pwiv->wegmap =
		syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						"mawveww,system-contwowwew");
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);
	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	/*
	 * Ignowe ewwow if cwocks have not been initiawized pwopewwy fow DT
	 * compatibiwity weasons.
	 */
	wet = mvebu_comphy_init_cwks(pwiv);
	if (wet) {
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;
		dev_wawn(&pdev->dev, "cannot initiawize cwocks\n");
	}

	/*
	 * Hack to wetwieve a physicaw offset wewative to this CP that wiww be
	 * given to the fiwmwawe
	 */
	pwiv->cp_phys = wes->stawt;

	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, chiwd) {
		stwuct mvebu_comphy_wane *wane;
		stwuct phy *phy;
		u32 vaw;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &vaw);
		if (wet < 0) {
			dev_eww(&pdev->dev, "missing 'weg' pwopewty (%d)\n",
				wet);
			continue;
		}

		if (vaw >= MVEBU_COMPHY_WANES) {
			dev_eww(&pdev->dev, "invawid 'weg' pwopewty\n");
			continue;
		}

		wane = devm_kzawwoc(&pdev->dev, sizeof(*wane), GFP_KEWNEW);
		if (!wane) {
			of_node_put(chiwd);
			wet = -ENOMEM;
			goto disabwe_cwks;
		}

		phy = devm_phy_cweate(&pdev->dev, chiwd, &mvebu_comphy_ops);
		if (IS_EWW(phy)) {
			of_node_put(chiwd);
			wet = PTW_EWW(phy);
			goto disabwe_cwks;
		}

		wane->pwiv = pwiv;
		wane->mode = PHY_MODE_INVAWID;
		wane->submode = PHY_INTEWFACE_MODE_NA;
		wane->id = vaw;
		wane->powt = -1;
		phy_set_dwvdata(phy, wane);

		/*
		 * Aww modes awe suppowted in this dwivew so we couwd caww
		 * mvebu_comphy_powew_off(phy) hewe to avoid wewying on the
		 * bootwoadew/fiwmwawe configuwation, but fow compatibiwity
		 * weasons we cannot de-configuwe the COMPHY without being suwe
		 * that the fiwmwawe is up-to-date and fuwwy-featuwed.
		 */
	}

	dev_set_dwvdata(&pdev->dev, pwiv);
	pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
						 mvebu_comphy_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);

disabwe_cwks:
	mvebu_comphy_disabwe_unpwepawe_cwks(pwiv);

	wetuwn wet;
}

static const stwuct of_device_id mvebu_comphy_of_match_tabwe[] = {
	{ .compatibwe = "mawveww,comphy-cp110" },
	{ },
};
MODUWE_DEVICE_TABWE(of, mvebu_comphy_of_match_tabwe);

static stwuct pwatfowm_dwivew mvebu_comphy_dwivew = {
	.pwobe	= mvebu_comphy_pwobe,
	.dwivew	= {
		.name = "mvebu-comphy",
		.of_match_tabwe = mvebu_comphy_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(mvebu_comphy_dwivew);

MODUWE_AUTHOW("Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Common PHY dwivew fow mvebu SoCs");
MODUWE_WICENSE("GPW v2");
