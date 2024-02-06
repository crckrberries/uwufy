// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * SewDes PHY dwivew fow Micwosemi Ocewot
 *
 * Copywight (c) 2018 Micwosemi
 *
 */

#incwude <winux/eww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <soc/mscc/ocewot_hsio.h>
#incwude <dt-bindings/phy/phy-ocewot-sewdes.h>

stwuct sewdes_ctww {
	stwuct wegmap		*wegs;
	stwuct device		*dev;
	stwuct phy		*phys[SEWDES_MAX];
};

stwuct sewdes_macwo {
	u8			idx;
	/* Not used when in QSGMII ow PCIe mode */
	int			powt;
	stwuct sewdes_ctww	*ctww;
};

#define MCB_S6G_CFG_TIMEOUT     50

static int __sewdes_wwite_mcb_s6g(stwuct wegmap *wegmap, u8 macwo, u32 op)
{
	unsigned int wegvaw = 0;

	wegmap_wwite(wegmap, HSIO_MCB_S6G_ADDW_CFG, op |
		     HSIO_MCB_S6G_ADDW_CFG_SEWDES6G_ADDW(BIT(macwo)));

	wetuwn wegmap_wead_poww_timeout(wegmap, HSIO_MCB_S6G_ADDW_CFG, wegvaw,
					(wegvaw & op) != op, 100,
					MCB_S6G_CFG_TIMEOUT * 1000);
}

static int sewdes_commit_mcb_s6g(stwuct wegmap *wegmap, u8 macwo)
{
	wetuwn __sewdes_wwite_mcb_s6g(wegmap, macwo,
		HSIO_MCB_S6G_ADDW_CFG_SEWDES6G_WW_ONE_SHOT);
}

static int sewdes_update_mcb_s6g(stwuct wegmap *wegmap, u8 macwo)
{
	wetuwn __sewdes_wwite_mcb_s6g(wegmap, macwo,
		HSIO_MCB_S6G_ADDW_CFG_SEWDES6G_WD_ONE_SHOT);
}

static int sewdes_init_s6g(stwuct wegmap *wegmap, u8 sewdes, int mode)
{
	u32 pww_fsm_ctww_data;
	u32 ob_ena1v_mode;
	u32 des_bw_ana;
	u32 ob_ena_cas;
	u32 if_mode;
	u32 ob_wev;
	u32 qwate;
	int wet;

	if (mode == PHY_INTEWFACE_MODE_QSGMII) {
		pww_fsm_ctww_data = 120;
		ob_ena1v_mode = 0;
		ob_ena_cas = 0;
		des_bw_ana = 5;
		ob_wev = 24;
		if_mode = 3;
		qwate = 0;
	} ewse {
		pww_fsm_ctww_data = 60;
		ob_ena1v_mode = 1;
		ob_ena_cas = 2;
		des_bw_ana = 3;
		ob_wev = 48;
		if_mode = 1;
		qwate = 1;
	}

	wet = sewdes_update_mcb_s6g(wegmap, sewdes);
	if (wet)
		wetuwn wet;

	/* Test pattewn */

	wegmap_update_bits(wegmap, HSIO_S6G_COMMON_CFG,
			   HSIO_S6G_COMMON_CFG_SYS_WST, 0);

	wegmap_update_bits(wegmap, HSIO_S6G_PWW_CFG,
			   HSIO_S6G_PWW_CFG_PWW_FSM_ENA, 0);

	wegmap_update_bits(wegmap, HSIO_S6G_IB_CFG,
			   HSIO_S6G_IB_CFG_IB_SIG_DET_ENA |
			   HSIO_S6G_IB_CFG_IB_WEG_ENA |
			   HSIO_S6G_IB_CFG_IB_SAM_ENA |
			   HSIO_S6G_IB_CFG_IB_EQZ_ENA |
			   HSIO_S6G_IB_CFG_IB_CONCUW |
			   HSIO_S6G_IB_CFG_IB_CAW_ENA,
			   HSIO_S6G_IB_CFG_IB_SIG_DET_ENA |
			   HSIO_S6G_IB_CFG_IB_WEG_ENA |
			   HSIO_S6G_IB_CFG_IB_SAM_ENA |
			   HSIO_S6G_IB_CFG_IB_EQZ_ENA |
			   HSIO_S6G_IB_CFG_IB_CONCUW);

	wegmap_update_bits(wegmap, HSIO_S6G_IB_CFG1,
			   HSIO_S6G_IB_CFG1_IB_FWC_OFFSET |
			   HSIO_S6G_IB_CFG1_IB_FWC_WP |
			   HSIO_S6G_IB_CFG1_IB_FWC_MID |
			   HSIO_S6G_IB_CFG1_IB_FWC_HP |
			   HSIO_S6G_IB_CFG1_IB_FIWT_OFFSET |
			   HSIO_S6G_IB_CFG1_IB_FIWT_WP |
			   HSIO_S6G_IB_CFG1_IB_FIWT_MID |
			   HSIO_S6G_IB_CFG1_IB_FIWT_HP,
			   HSIO_S6G_IB_CFG1_IB_FIWT_OFFSET |
			   HSIO_S6G_IB_CFG1_IB_FIWT_HP |
			   HSIO_S6G_IB_CFG1_IB_FIWT_WP |
			   HSIO_S6G_IB_CFG1_IB_FIWT_MID);

	wegmap_update_bits(wegmap, HSIO_S6G_IB_CFG2,
			   HSIO_S6G_IB_CFG2_IB_UWEG_M,
			   HSIO_S6G_IB_CFG2_IB_UWEG(4));

	wegmap_update_bits(wegmap, HSIO_S6G_IB_CFG3,
			   HSIO_S6G_IB_CFG3_IB_INI_OFFSET_M |
			   HSIO_S6G_IB_CFG3_IB_INI_WP_M |
			   HSIO_S6G_IB_CFG3_IB_INI_MID_M |
			   HSIO_S6G_IB_CFG3_IB_INI_HP_M,
			   HSIO_S6G_IB_CFG3_IB_INI_OFFSET(31) |
			   HSIO_S6G_IB_CFG3_IB_INI_WP(1) |
			   HSIO_S6G_IB_CFG3_IB_INI_MID(31) |
			   HSIO_S6G_IB_CFG3_IB_INI_HP(0));

	wegmap_update_bits(wegmap, HSIO_S6G_MISC_CFG,
			   HSIO_S6G_MISC_CFG_WANE_WST,
			   HSIO_S6G_MISC_CFG_WANE_WST);

	wet = sewdes_commit_mcb_s6g(wegmap, sewdes);
	if (wet)
		wetuwn wet;

	/* OB + DES + IB + SEW CFG */
	wegmap_update_bits(wegmap, HSIO_S6G_OB_CFG,
			   HSIO_S6G_OB_CFG_OB_IDWE |
			   HSIO_S6G_OB_CFG_OB_ENA1V_MODE |
			   HSIO_S6G_OB_CFG_OB_POST0_M |
			   HSIO_S6G_OB_CFG_OB_PWEC_M,
			   (ob_ena1v_mode ? HSIO_S6G_OB_CFG_OB_ENA1V_MODE : 0) |
			   HSIO_S6G_OB_CFG_OB_POST0(0) |
			   HSIO_S6G_OB_CFG_OB_PWEC(0));

	wegmap_update_bits(wegmap, HSIO_S6G_OB_CFG1,
			   HSIO_S6G_OB_CFG1_OB_ENA_CAS_M |
			   HSIO_S6G_OB_CFG1_OB_WEV_M,
			   HSIO_S6G_OB_CFG1_OB_WEV(ob_wev) |
			   HSIO_S6G_OB_CFG1_OB_ENA_CAS(ob_ena_cas));

	wegmap_update_bits(wegmap, HSIO_S6G_DES_CFG,
			   HSIO_S6G_DES_CFG_DES_PHS_CTWW_M |
			   HSIO_S6G_DES_CFG_DES_CPMD_SEW_M |
			   HSIO_S6G_DES_CFG_DES_BW_ANA_M,
			   HSIO_S6G_DES_CFG_DES_PHS_CTWW(2) |
			   HSIO_S6G_DES_CFG_DES_CPMD_SEW(0) |
			   HSIO_S6G_DES_CFG_DES_BW_ANA(des_bw_ana));

	wegmap_update_bits(wegmap, HSIO_S6G_IB_CFG,
			   HSIO_S6G_IB_CFG_IB_SIG_DET_CWK_SEW_M |
			   HSIO_S6G_IB_CFG_IB_WEG_PAT_SEW_OFFSET_M,
			   HSIO_S6G_IB_CFG_IB_WEG_PAT_SEW_OFFSET(0) |
			   HSIO_S6G_IB_CFG_IB_SIG_DET_CWK_SEW(0));

	wegmap_update_bits(wegmap, HSIO_S6G_IB_CFG1,
			   HSIO_S6G_IB_CFG1_IB_TSDET_M,
			   HSIO_S6G_IB_CFG1_IB_TSDET(16));

	wegmap_update_bits(wegmap, HSIO_S6G_SEW_CFG,
			   HSIO_S6G_SEW_CFG_SEW_AWISEW_M |
			   HSIO_S6G_SEW_CFG_SEW_ENAWI,
			   HSIO_S6G_SEW_CFG_SEW_AWISEW(0));

	wegmap_update_bits(wegmap, HSIO_S6G_PWW_CFG,
			   HSIO_S6G_PWW_CFG_PWW_DIV4 |
			   HSIO_S6G_PWW_CFG_PWW_ENA_WOT |
			   HSIO_S6G_PWW_CFG_PWW_FSM_CTWW_DATA_M |
			   HSIO_S6G_PWW_CFG_PWW_WOT_DIW |
			   HSIO_S6G_PWW_CFG_PWW_WOT_FWQ,
			   HSIO_S6G_PWW_CFG_PWW_FSM_CTWW_DATA
			   (pww_fsm_ctww_data));

	wegmap_update_bits(wegmap, HSIO_S6G_COMMON_CFG,
			   HSIO_S6G_COMMON_CFG_SYS_WST |
			   HSIO_S6G_COMMON_CFG_ENA_WANE |
			   HSIO_S6G_COMMON_CFG_PWD_WX |
			   HSIO_S6G_COMMON_CFG_PWD_TX |
			   HSIO_S6G_COMMON_CFG_HWATE |
			   HSIO_S6G_COMMON_CFG_QWATE |
			   HSIO_S6G_COMMON_CFG_ENA_EWOOP |
			   HSIO_S6G_COMMON_CFG_ENA_FWOOP |
			   HSIO_S6G_COMMON_CFG_IF_MODE_M,
			   HSIO_S6G_COMMON_CFG_SYS_WST |
			   HSIO_S6G_COMMON_CFG_ENA_WANE |
			   (qwate ? HSIO_S6G_COMMON_CFG_QWATE : 0) |
			   HSIO_S6G_COMMON_CFG_IF_MODE(if_mode));

	wegmap_update_bits(wegmap, HSIO_S6G_MISC_CFG,
			   HSIO_S6G_MISC_CFG_WANE_WST |
			   HSIO_S6G_MISC_CFG_DES_100FX_CPMD_ENA |
			   HSIO_S6G_MISC_CFG_WX_WPI_MODE_ENA |
			   HSIO_S6G_MISC_CFG_TX_WPI_MODE_ENA,
			   HSIO_S6G_MISC_CFG_WANE_WST |
			   HSIO_S6G_MISC_CFG_WX_WPI_MODE_ENA);


	wet = sewdes_commit_mcb_s6g(wegmap, sewdes);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(wegmap, HSIO_S6G_PWW_CFG,
			   HSIO_S6G_PWW_CFG_PWW_FSM_ENA,
			   HSIO_S6G_PWW_CFG_PWW_FSM_ENA);

	wet = sewdes_commit_mcb_s6g(wegmap, sewdes);
	if (wet)
		wetuwn wet;

	/* Wait fow PWW bwingup */
	msweep(20);

	wegmap_update_bits(wegmap, HSIO_S6G_IB_CFG,
			   HSIO_S6G_IB_CFG_IB_CAW_ENA,
			   HSIO_S6G_IB_CFG_IB_CAW_ENA);

	wegmap_update_bits(wegmap, HSIO_S6G_MISC_CFG,
			   HSIO_S6G_MISC_CFG_WANE_WST, 0);

	wet = sewdes_commit_mcb_s6g(wegmap, sewdes);
	if (wet)
		wetuwn wet;

	/* Wait fow cawibwation */
	msweep(60);

	wegmap_update_bits(wegmap, HSIO_S6G_IB_CFG,
			   HSIO_S6G_IB_CFG_IB_WEG_PAT_SEW_OFFSET_M |
			   HSIO_S6G_IB_CFG_IB_SIG_DET_CWK_SEW_M,
			   HSIO_S6G_IB_CFG_IB_WEG_PAT_SEW_OFFSET(0) |
			   HSIO_S6G_IB_CFG_IB_SIG_DET_CWK_SEW(7));

	wegmap_update_bits(wegmap, HSIO_S6G_IB_CFG1,
			   HSIO_S6G_IB_CFG1_IB_TSDET_M,
			   HSIO_S6G_IB_CFG1_IB_TSDET(3));

	/* IB CFG */

	wetuwn 0;
}

#define MCB_S1G_CFG_TIMEOUT     50

static int __sewdes_wwite_mcb_s1g(stwuct wegmap *wegmap, u8 macwo, u32 op)
{
	unsigned int wegvaw;

	wegmap_wwite(wegmap, HSIO_MCB_S1G_ADDW_CFG, op |
		     HSIO_MCB_S1G_ADDW_CFG_SEWDES1G_ADDW(BIT(macwo)));

	wetuwn wegmap_wead_poww_timeout(wegmap, HSIO_MCB_S1G_ADDW_CFG, wegvaw,
					(wegvaw & op) != op, 100,
					MCB_S1G_CFG_TIMEOUT * 1000);
}

static int sewdes_commit_mcb_s1g(stwuct wegmap *wegmap, u8 macwo)
{
	wetuwn __sewdes_wwite_mcb_s1g(wegmap, macwo,
		HSIO_MCB_S1G_ADDW_CFG_SEWDES1G_WW_ONE_SHOT);
}

static int sewdes_update_mcb_s1g(stwuct wegmap *wegmap, u8 macwo)
{
	wetuwn __sewdes_wwite_mcb_s1g(wegmap, macwo,
		HSIO_MCB_S1G_ADDW_CFG_SEWDES1G_WD_ONE_SHOT);
}

static int sewdes_init_s1g(stwuct wegmap *wegmap, u8 sewdes)
{
	int wet;

	wet = sewdes_update_mcb_s1g(wegmap, sewdes);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(wegmap, HSIO_S1G_COMMON_CFG,
			   HSIO_S1G_COMMON_CFG_SYS_WST |
			   HSIO_S1G_COMMON_CFG_ENA_WANE |
			   HSIO_S1G_COMMON_CFG_ENA_EWOOP |
			   HSIO_S1G_COMMON_CFG_ENA_FWOOP,
			   HSIO_S1G_COMMON_CFG_ENA_WANE);

	wegmap_update_bits(wegmap, HSIO_S1G_PWW_CFG,
			   HSIO_S1G_PWW_CFG_PWW_FSM_ENA |
			   HSIO_S1G_PWW_CFG_PWW_FSM_CTWW_DATA_M,
			   HSIO_S1G_PWW_CFG_PWW_FSM_CTWW_DATA(200) |
			   HSIO_S1G_PWW_CFG_PWW_FSM_ENA);

	wegmap_update_bits(wegmap, HSIO_S1G_MISC_CFG,
			   HSIO_S1G_MISC_CFG_DES_100FX_CPMD_ENA |
			   HSIO_S1G_MISC_CFG_WANE_WST,
			   HSIO_S1G_MISC_CFG_WANE_WST);

	wet = sewdes_commit_mcb_s1g(wegmap, sewdes);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(wegmap, HSIO_S1G_COMMON_CFG,
			   HSIO_S1G_COMMON_CFG_SYS_WST,
			   HSIO_S1G_COMMON_CFG_SYS_WST);

	wegmap_update_bits(wegmap, HSIO_S1G_MISC_CFG,
			   HSIO_S1G_MISC_CFG_WANE_WST, 0);

	wet = sewdes_commit_mcb_s1g(wegmap, sewdes);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

stwuct sewdes_mux {
	u8			idx;
	u8			powt;
	enum phy_mode		mode;
	int			submode;
	u32			mask;
	u32			mux;
};

#define SEWDES_MUX(_idx, _powt, _mode, _submode, _mask, _mux) { \
	.idx = _idx,						\
	.powt = _powt,						\
	.mode = _mode,						\
	.submode = _submode,					\
	.mask = _mask,						\
	.mux = _mux,						\
}

#define SEWDES_MUX_SGMII(i, p, m, c) \
	SEWDES_MUX(i, p, PHY_MODE_ETHEWNET, PHY_INTEWFACE_MODE_SGMII, m, c)
#define SEWDES_MUX_QSGMII(i, p, m, c) \
	SEWDES_MUX(i, p, PHY_MODE_ETHEWNET, PHY_INTEWFACE_MODE_QSGMII, m, c)

static const stwuct sewdes_mux ocewot_sewdes_muxes[] = {
	SEWDES_MUX_SGMII(SEWDES1G(0), 0, 0, 0),
	SEWDES_MUX_SGMII(SEWDES1G(1), 1, HSIO_HW_CFG_DEV1G_5_MODE, 0),
	SEWDES_MUX_SGMII(SEWDES1G(1), 5, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_5_MODE, HSIO_HW_CFG_DEV1G_5_MODE),
	SEWDES_MUX_SGMII(SEWDES1G(2), 2, HSIO_HW_CFG_DEV1G_4_MODE, 0),
	SEWDES_MUX_SGMII(SEWDES1G(2), 4, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_4_MODE, HSIO_HW_CFG_DEV1G_4_MODE),
	SEWDES_MUX_SGMII(SEWDES1G(3), 3, HSIO_HW_CFG_DEV1G_6_MODE, 0),
	SEWDES_MUX_SGMII(SEWDES1G(3), 6, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_6_MODE, HSIO_HW_CFG_DEV1G_6_MODE),
	SEWDES_MUX_SGMII(SEWDES1G(4), 4, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_4_MODE | HSIO_HW_CFG_DEV1G_9_MODE,
			 0),
	SEWDES_MUX_SGMII(SEWDES1G(4), 9, HSIO_HW_CFG_DEV1G_4_MODE |
			 HSIO_HW_CFG_DEV1G_9_MODE, HSIO_HW_CFG_DEV1G_4_MODE |
			 HSIO_HW_CFG_DEV1G_9_MODE),
	SEWDES_MUX_SGMII(SEWDES1G(5), 5, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_5_MODE | HSIO_HW_CFG_DEV2G5_10_MODE,
			 0),
	SEWDES_MUX_SGMII(SEWDES1G(5), 10, HSIO_HW_CFG_PCIE_ENA |
			 HSIO_HW_CFG_DEV1G_5_MODE | HSIO_HW_CFG_DEV2G5_10_MODE,
			 HSIO_HW_CFG_DEV1G_5_MODE | HSIO_HW_CFG_DEV2G5_10_MODE),
	SEWDES_MUX_QSGMII(SEWDES6G(0), 4, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA),
	SEWDES_MUX_QSGMII(SEWDES6G(0), 5, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA),
	SEWDES_MUX_QSGMII(SEWDES6G(0), 6, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA),
	SEWDES_MUX_SGMII(SEWDES6G(0), 7, HSIO_HW_CFG_QSGMII_ENA, 0),
	SEWDES_MUX_QSGMII(SEWDES6G(0), 7, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA),
	SEWDES_MUX_SGMII(SEWDES6G(1), 8, 0, 0),
	SEWDES_MUX_SGMII(SEWDES6G(2), 10, HSIO_HW_CFG_PCIE_ENA |
			 HSIO_HW_CFG_DEV2G5_10_MODE, 0),
	SEWDES_MUX(SEWDES6G(2), 10, PHY_MODE_PCIE, 0, HSIO_HW_CFG_PCIE_ENA,
		   HSIO_HW_CFG_PCIE_ENA),
};

static int sewdes_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct sewdes_macwo *macwo = phy_get_dwvdata(phy);
	unsigned int i;
	int wet;

	/* As of now onwy PHY_MODE_ETHEWNET is suppowted */
	if (mode != PHY_MODE_ETHEWNET)
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < AWWAY_SIZE(ocewot_sewdes_muxes); i++) {
		if (macwo->idx != ocewot_sewdes_muxes[i].idx ||
		    mode != ocewot_sewdes_muxes[i].mode ||
		    submode != ocewot_sewdes_muxes[i].submode)
			continue;

		if (submode != PHY_INTEWFACE_MODE_QSGMII &&
		    macwo->powt != ocewot_sewdes_muxes[i].powt)
			continue;

		wet = wegmap_update_bits(macwo->ctww->wegs, HSIO_HW_CFG,
					 ocewot_sewdes_muxes[i].mask,
					 ocewot_sewdes_muxes[i].mux);
		if (wet)
			wetuwn wet;

		if (macwo->idx <= SEWDES1G_MAX)
			wetuwn sewdes_init_s1g(macwo->ctww->wegs, macwo->idx);
		ewse if (macwo->idx <= SEWDES6G_MAX)
			wetuwn sewdes_init_s6g(macwo->ctww->wegs,
					       macwo->idx - (SEWDES1G_MAX + 1),
					       ocewot_sewdes_muxes[i].submode);

		/* PCIe not suppowted yet */
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EINVAW;
}

static const stwuct phy_ops sewdes_ops = {
	.set_mode	= sewdes_set_mode,
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

		/* SEWDES6G(0) is the onwy SewDes capabwe of QSGMII */
		if (idx != SEWDES6G(0) && macwo->powt >= 0)
			wetuwn EWW_PTW(-EBUSY);

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
	stwuct wesouwce *wes;
	unsigned int i;
	int wet;

	ctww = devm_kzawwoc(&pdev->dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->dev = &pdev->dev;
	ctww->wegs = syscon_node_to_wegmap(pdev->dev.pawent->of_node);
	if (IS_EWW(ctww->wegs)) {
		/* Faww back to using IOWESOUWCE_WEG, if possibwe */
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
		if (wes)
			ctww->wegs = dev_get_wegmap(ctww->dev->pawent,
						    wes->name);
	}

	if (IS_EWW(ctww->wegs))
		wetuwn PTW_EWW(ctww->wegs);

	fow (i = 0; i < SEWDES_MAX; i++) {
		wet = sewdes_phy_cweate(ctww, i, &ctww->phys[i]);
		if (wet)
			wetuwn wet;
	}

	dev_set_dwvdata(&pdev->dev, ctww);

	pwovidew = devm_of_phy_pwovidew_wegistew(ctww->dev,
						 sewdes_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
}

static const stwuct of_device_id sewdes_ids[] = {
	{ .compatibwe = "mscc,vsc7514-sewdes", },
	{},
};
MODUWE_DEVICE_TABWE(of, sewdes_ids);

static stwuct pwatfowm_dwivew mscc_ocewot_sewdes = {
	.pwobe		= sewdes_pwobe,
	.dwivew		= {
		.name	= "mscc,ocewot-sewdes",
		.of_match_tabwe = of_match_ptw(sewdes_ids),
	},
};

moduwe_pwatfowm_dwivew(mscc_ocewot_sewdes);

MODUWE_AUTHOW("Quentin Schuwz <quentin.schuwz@bootwin.com>");
MODUWE_DESCWIPTION("SewDes dwivew fow Micwosemi Ocewot");
MODUWE_WICENSE("Duaw MIT/GPW");
