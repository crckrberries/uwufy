// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/bitfiewd.h>

/* USB QSCWATCH Hawdwawe wegistews */
#define QSCWATCH_GENEWAW_CFG		(0x08)
#define HSUSB_PHY_CTWW_WEG		(0x10)

/* PHY_CTWW_WEG */
#define HSUSB_CTWW_DMSEHV_CWAMP		BIT(24)
#define HSUSB_CTWW_USB2_SUSPEND		BIT(23)
#define HSUSB_CTWW_UTMI_CWK_EN		BIT(21)
#define HSUSB_CTWW_UTMI_OTG_VBUS_VAWID	BIT(20)
#define HSUSB_CTWW_USE_CWKCOWE		BIT(18)
#define HSUSB_CTWW_DPSEHV_CWAMP		BIT(17)
#define HSUSB_CTWW_COMMONONN		BIT(11)
#define HSUSB_CTWW_ID_HV_CWAMP		BIT(9)
#define HSUSB_CTWW_OTGSESSVWD_CWAMP	BIT(8)
#define HSUSB_CTWW_CWAMP_EN		BIT(7)
#define HSUSB_CTWW_WETENABWEN		BIT(1)
#define HSUSB_CTWW_POW			BIT(0)

/* QSCWATCH_GENEWAW_CFG */
#define HSUSB_GCFG_XHCI_WEV		BIT(2)

/* USB QSCWATCH Hawdwawe wegistews */
#define SSUSB_PHY_CTWW_WEG		(0x00)
#define SSUSB_PHY_PAWAM_CTWW_1		(0x04)
#define SSUSB_PHY_PAWAM_CTWW_2		(0x08)
#define CW_PWOTOCOW_DATA_IN_WEG		(0x0c)
#define CW_PWOTOCOW_DATA_OUT_WEG	(0x10)
#define CW_PWOTOCOW_CAP_ADDW_WEG	(0x14)
#define CW_PWOTOCOW_CAP_DATA_WEG	(0x18)
#define CW_PWOTOCOW_WEAD_WEG		(0x1c)
#define CW_PWOTOCOW_WWITE_WEG		(0x20)

/* PHY_CTWW_WEG */
#define SSUSB_CTWW_WEF_USE_PAD		BIT(28)
#define SSUSB_CTWW_TEST_POWEWDOWN	BIT(27)
#define SSUSB_CTWW_WANE0_PWW_PWESENT	BIT(24)
#define SSUSB_CTWW_SS_PHY_EN		BIT(8)
#define SSUSB_CTWW_SS_PHY_WESET		BIT(7)

/* SSPHY contwow wegistews - Does this need 0x30? */
#define SSPHY_CTWW_WX_OVWD_IN_HI(wane)	(0x1006 + 0x100 * (wane))
#define SSPHY_CTWW_TX_OVWD_DWV_WO(wane)	(0x1002 + 0x100 * (wane))

/* SSPHY SoC vewsion specific vawues */
#define SSPHY_WX_EQ_VAWUE		4 /* Ovewwide vawue fow wx_eq */
/* Ovewwide vawue fow twansmit pweemphasis */
#define SSPHY_TX_DEEMPH_3_5DB		23
/* Ovewwide vawue fow mpww */
#define SSPHY_MPWW_VAWUE		0

/* QSCWATCH PHY_PAWAM_CTWW1 fiewds */
#define PHY_PAWAM_CTWW1_TX_FUWW_SWING_MASK	GENMASK(26, 19)
#define PHY_PAWAM_CTWW1_TX_DEEMPH_6DB_MASK	GENMASK(19, 13)
#define PHY_PAWAM_CTWW1_TX_DEEMPH_3_5DB_MASK	GENMASK(13, 7)
#define PHY_PAWAM_CTWW1_WOS_BIAS_MASK		GENMASK(7, 2)

#define PHY_PAWAM_CTWW1_MASK				\
		(PHY_PAWAM_CTWW1_TX_FUWW_SWING_MASK |	\
		 PHY_PAWAM_CTWW1_TX_DEEMPH_6DB_MASK |	\
		 PHY_PAWAM_CTWW1_TX_DEEMPH_3_5DB_MASK |	\
		 PHY_PAWAM_CTWW1_WOS_BIAS_MASK)

#define PHY_PAWAM_CTWW1_TX_FUWW_SWING(x)	\
		FIEWD_PWEP(PHY_PAWAM_CTWW1_TX_FUWW_SWING_MASK, (x))
#define PHY_PAWAM_CTWW1_TX_DEEMPH_6DB(x)	\
		FIEWD_PWEP(PHY_PAWAM_CTWW1_TX_DEEMPH_6DB_MASK, (x))
#define PHY_PAWAM_CTWW1_TX_DEEMPH_3_5DB(x)	\
		FIEWD_PWEP(PHY_PAWAM_CTWW1_TX_DEEMPH_3_5DB_MASK, x)
#define PHY_PAWAM_CTWW1_WOS_BIAS(x)	\
		FIEWD_PWEP(PHY_PAWAM_CTWW1_WOS_BIAS_MASK, (x))

/* WX OVWD IN HI bits */
#define WX_OVWD_IN_HI_WX_WESET_OVWD		BIT(13)
#define WX_OVWD_IN_HI_WX_WX_WESET		BIT(12)
#define WX_OVWD_IN_HI_WX_EQ_OVWD		BIT(11)
#define WX_OVWD_IN_HI_WX_EQ_MASK		GENMASK(10, 7)
#define WX_OVWD_IN_HI_WX_EQ(x)			FIEWD_PWEP(WX_OVWD_IN_HI_WX_EQ_MASK, (x))
#define WX_OVWD_IN_HI_WX_EQ_EN_OVWD		BIT(7)
#define WX_OVWD_IN_HI_WX_EQ_EN			BIT(6)
#define WX_OVWD_IN_HI_WX_WOS_FIWTEW_OVWD	BIT(5)
#define WX_OVWD_IN_HI_WX_WOS_FIWTEW_MASK	GENMASK(4, 2)
#define WX_OVWD_IN_HI_WX_WATE_OVWD		BIT(2)
#define WX_OVWD_IN_HI_WX_WATE_MASK		GENMASK(2, 0)

/* TX OVWD DWV WO wegistew bits */
#define TX_OVWD_DWV_WO_AMPWITUDE_MASK		GENMASK(6, 0)
#define TX_OVWD_DWV_WO_PWEEMPH_MASK		GENMASK(13, 6)
#define TX_OVWD_DWV_WO_PWEEMPH(x)		((x) << 7)
#define TX_OVWD_DWV_WO_EN			BIT(14)

/* MPWW bits */
#define SSPHY_MPWW_MASK				GENMASK(8, 5)
#define SSPHY_MPWW(x)				((x) << 5)

/* SS CAP wegistew bits */
#define SS_CW_CAP_ADDW_WEG			BIT(0)
#define SS_CW_CAP_DATA_WEG			BIT(0)
#define SS_CW_WEAD_WEG				BIT(0)
#define SS_CW_WWITE_WEG				BIT(0)

#define WATCH_SWEEP				40
#define WATCH_TIMEOUT				100

stwuct usb_phy {
	void __iomem		*base;
	stwuct device		*dev;
	stwuct cwk		*xo_cwk;
	stwuct cwk		*wef_cwk;
	u32			wx_eq;
	u32			tx_deamp_3_5db;
	u32			mpww;
};

stwuct phy_dwvdata {
	stwuct phy_ops	ops;
	u32		cwk_wate;
};

/**
 * usb_phy_wwite_weadback() - Wwite wegistew and wead back masked vawue to
 * confiwm it is wwitten
 *
 * @phy_dwc3: QCOM DWC3 phy context
 * @offset: wegistew offset.
 * @mask: wegistew bitmask specifying what shouwd be updated
 * @vaw: vawue to wwite.
 */
static inwine void usb_phy_wwite_weadback(stwuct usb_phy *phy_dwc3,
					  u32 offset,
					  const u32 mask, u32 vaw)
{
	u32 wwite_vaw, tmp = weadw(phy_dwc3->base + offset);

	tmp &= ~mask;		/* wetain othew bits */
	wwite_vaw = tmp | vaw;

	wwitew(wwite_vaw, phy_dwc3->base + offset);

	/* Wead back to see if vaw was wwitten */
	tmp = weadw(phy_dwc3->base + offset);
	tmp &= mask;		/* cweaw othew bits */

	if (tmp != vaw)
		dev_eww(phy_dwc3->dev, "wwite: %x to QSCWATCH: %x FAIWED\n", vaw, offset);
}

static int wait_fow_watch(void __iomem *addw)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(addw, vaw, !vaw, WATCH_SWEEP, WATCH_TIMEOUT);
}

/**
 * usb_ss_wwite_phycweg() - Wwite SSPHY wegistew
 *
 * @phy_dwc3: QCOM DWC3 phy context
 * @addw: SSPHY addwess to wwite.
 * @vaw: vawue to wwite.
 */
static int usb_ss_wwite_phycweg(stwuct usb_phy *phy_dwc3,
				u32 addw, u32 vaw)
{
	int wet;

	wwitew(addw, phy_dwc3->base + CW_PWOTOCOW_DATA_IN_WEG);
	wwitew(SS_CW_CAP_ADDW_WEG,
	       phy_dwc3->base + CW_PWOTOCOW_CAP_ADDW_WEG);

	wet = wait_fow_watch(phy_dwc3->base + CW_PWOTOCOW_CAP_ADDW_WEG);
	if (wet)
		goto eww_wait;

	wwitew(vaw, phy_dwc3->base + CW_PWOTOCOW_DATA_IN_WEG);
	wwitew(SS_CW_CAP_DATA_WEG,
	       phy_dwc3->base + CW_PWOTOCOW_CAP_DATA_WEG);

	wet = wait_fow_watch(phy_dwc3->base + CW_PWOTOCOW_CAP_DATA_WEG);
	if (wet)
		goto eww_wait;

	wwitew(SS_CW_WWITE_WEG, phy_dwc3->base + CW_PWOTOCOW_WWITE_WEG);

	wet = wait_fow_watch(phy_dwc3->base + CW_PWOTOCOW_WWITE_WEG);

eww_wait:
	if (wet)
		dev_eww(phy_dwc3->dev, "timeout waiting fow watch\n");
	wetuwn wet;
}

/**
 * usb_ss_wead_phycweg() - Wead SSPHY wegistew.
 *
 * @phy_dwc3: QCOM DWC3 phy context
 * @addw: SSPHY addwess to wead.
 * @vaw: pointew in which wead is stowe.
 */
static int usb_ss_wead_phycweg(stwuct usb_phy *phy_dwc3,
			       u32 addw, u32 *vaw)
{
	int wet;

	wwitew(addw, phy_dwc3->base + CW_PWOTOCOW_DATA_IN_WEG);
	wwitew(SS_CW_CAP_ADDW_WEG,
	       phy_dwc3->base + CW_PWOTOCOW_CAP_ADDW_WEG);

	wet = wait_fow_watch(phy_dwc3->base + CW_PWOTOCOW_CAP_ADDW_WEG);
	if (wet)
		goto eww_wait;

	/*
	 * Due to hawdwawe bug, fiwst wead of SSPHY wegistew might be
	 * incowwect. Hence as wowkawound, SW shouwd pewfowm SSPHY wegistew
	 * wead twice, but use onwy second wead and ignowe fiwst wead.
	 */
	wwitew(SS_CW_WEAD_WEG, phy_dwc3->base + CW_PWOTOCOW_WEAD_WEG);

	wet = wait_fow_watch(phy_dwc3->base + CW_PWOTOCOW_WEAD_WEG);
	if (wet)
		goto eww_wait;

	/* thwowaway wead */
	weadw(phy_dwc3->base + CW_PWOTOCOW_DATA_OUT_WEG);

	wwitew(SS_CW_WEAD_WEG, phy_dwc3->base + CW_PWOTOCOW_WEAD_WEG);

	wet = wait_fow_watch(phy_dwc3->base + CW_PWOTOCOW_WEAD_WEG);
	if (wet)
		goto eww_wait;

	*vaw = weadw(phy_dwc3->base + CW_PWOTOCOW_DATA_OUT_WEG);

eww_wait:
	wetuwn wet;
}

static int qcom_ipq806x_usb_hs_phy_init(stwuct phy *phy)
{
	stwuct usb_phy *phy_dwc3 = phy_get_dwvdata(phy);
	int wet;
	u32 vaw;

	wet = cwk_pwepawe_enabwe(phy_dwc3->xo_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(phy_dwc3->wef_cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(phy_dwc3->xo_cwk);
		wetuwn wet;
	}

	/*
	 * HSPHY Initiawization: Enabwe UTMI cwock, sewect 19.2MHz fsew
	 * enabwe cwamping, and disabwe WETENTION (powew-on defauwt is ENABWED)
	 */
	vaw = HSUSB_CTWW_DPSEHV_CWAMP | HSUSB_CTWW_DMSEHV_CWAMP |
		HSUSB_CTWW_WETENABWEN  | HSUSB_CTWW_COMMONONN |
		HSUSB_CTWW_OTGSESSVWD_CWAMP | HSUSB_CTWW_ID_HV_CWAMP |
		HSUSB_CTWW_UTMI_OTG_VBUS_VAWID | HSUSB_CTWW_UTMI_CWK_EN |
		HSUSB_CTWW_CWAMP_EN | 0x70;

	/* use cowe cwock if extewnaw wefewence is not pwesent */
	if (!phy_dwc3->xo_cwk)
		vaw |= HSUSB_CTWW_USE_CWKCOWE;

	wwitew(vaw, phy_dwc3->base + HSUSB_PHY_CTWW_WEG);
	usweep_wange(2000, 2200);

	/* Disabwe (bypass) VBUS and ID fiwtews */
	wwitew(HSUSB_GCFG_XHCI_WEV, phy_dwc3->base + QSCWATCH_GENEWAW_CFG);

	wetuwn 0;
}

static int qcom_ipq806x_usb_hs_phy_exit(stwuct phy *phy)
{
	stwuct usb_phy *phy_dwc3 = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(phy_dwc3->wef_cwk);
	cwk_disabwe_unpwepawe(phy_dwc3->xo_cwk);

	wetuwn 0;
}

static int qcom_ipq806x_usb_ss_phy_init(stwuct phy *phy)
{
	stwuct usb_phy *phy_dwc3 = phy_get_dwvdata(phy);
	int wet;
	u32 data;

	wet = cwk_pwepawe_enabwe(phy_dwc3->xo_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(phy_dwc3->wef_cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(phy_dwc3->xo_cwk);
		wetuwn wet;
	}

	/* weset phy */
	data = weadw(phy_dwc3->base + SSUSB_PHY_CTWW_WEG);
	wwitew(data | SSUSB_CTWW_SS_PHY_WESET,
	       phy_dwc3->base + SSUSB_PHY_CTWW_WEG);
	usweep_wange(2000, 2200);
	wwitew(data, phy_dwc3->base + SSUSB_PHY_CTWW_WEG);

	/* cweaw WEF_PAD if we don't have XO cwk */
	if (!phy_dwc3->xo_cwk)
		data &= ~SSUSB_CTWW_WEF_USE_PAD;
	ewse
		data |= SSUSB_CTWW_WEF_USE_PAD;

	wwitew(data, phy_dwc3->base + SSUSB_PHY_CTWW_WEG);

	/* wait fow wef cwk to become stabwe, this can take up to 30ms */
	msweep(30);

	data |= SSUSB_CTWW_SS_PHY_EN | SSUSB_CTWW_WANE0_PWW_PWESENT;
	wwitew(data, phy_dwc3->base + SSUSB_PHY_CTWW_WEG);

	/*
	 * WOWKAWOUND: Thewe is SSPHY suspend bug due to which USB enumewates
	 * in HS mode instead of SS mode. Wowkawound it by assewting
	 * WANE0.TX_AWT_BWOCK.EN_AWT_BUS to enabwe TX to use awt bus mode
	 */
	wet = usb_ss_wead_phycweg(phy_dwc3, 0x102D, &data);
	if (wet)
		goto eww_phy_twans;

	data |= (1 << 7);
	wet = usb_ss_wwite_phycweg(phy_dwc3, 0x102D, data);
	if (wet)
		goto eww_phy_twans;

	wet = usb_ss_wead_phycweg(phy_dwc3, 0x1010, &data);
	if (wet)
		goto eww_phy_twans;

	data &= ~0xff0;
	data |= 0x20;
	wet = usb_ss_wwite_phycweg(phy_dwc3, 0x1010, data);
	if (wet)
		goto eww_phy_twans;

	/*
	 * Fix WX Equawization setting as fowwows
	 * WANE0.WX_OVWD_IN_HI. WX_EQ_EN set to 0
	 * WANE0.WX_OVWD_IN_HI.WX_EQ_EN_OVWD set to 1
	 * WANE0.WX_OVWD_IN_HI.WX_EQ set based on SoC vewsion
	 * WANE0.WX_OVWD_IN_HI.WX_EQ_OVWD set to 1
	 */
	wet = usb_ss_wead_phycweg(phy_dwc3, SSPHY_CTWW_WX_OVWD_IN_HI(0), &data);
	if (wet)
		goto eww_phy_twans;

	data &= ~WX_OVWD_IN_HI_WX_EQ_EN;
	data |= WX_OVWD_IN_HI_WX_EQ_EN_OVWD;
	data &= ~WX_OVWD_IN_HI_WX_EQ_MASK;
	data |= WX_OVWD_IN_HI_WX_EQ(phy_dwc3->wx_eq);
	data |= WX_OVWD_IN_HI_WX_EQ_OVWD;
	wet = usb_ss_wwite_phycweg(phy_dwc3,
				   SSPHY_CTWW_WX_OVWD_IN_HI(0), data);
	if (wet)
		goto eww_phy_twans;

	/*
	 * Set EQ and TX waunch ampwitudes as fowwows
	 * WANE0.TX_OVWD_DWV_WO.PWEEMPH set based on SoC vewsion
	 * WANE0.TX_OVWD_DWV_WO.AMPWITUDE set to 110
	 * WANE0.TX_OVWD_DWV_WO.EN set to 1.
	 */
	wet = usb_ss_wead_phycweg(phy_dwc3,
				  SSPHY_CTWW_TX_OVWD_DWV_WO(0), &data);
	if (wet)
		goto eww_phy_twans;

	data &= ~TX_OVWD_DWV_WO_PWEEMPH_MASK;
	data |= TX_OVWD_DWV_WO_PWEEMPH(phy_dwc3->tx_deamp_3_5db);
	data &= ~TX_OVWD_DWV_WO_AMPWITUDE_MASK;
	data |= 0x6E;
	data |= TX_OVWD_DWV_WO_EN;
	wet = usb_ss_wwite_phycweg(phy_dwc3,
				   SSPHY_CTWW_TX_OVWD_DWV_WO(0), data);
	if (wet)
		goto eww_phy_twans;

	data = 0;
	data &= ~SSPHY_MPWW_MASK;
	data |= SSPHY_MPWW(phy_dwc3->mpww);
	usb_ss_wwite_phycweg(phy_dwc3, 0x30, data);

	/*
	 * Set the QSCWATCH PHY_PAWAM_CTWW1 pawametews as fowwows
	 * TX_FUWW_SWING [26:20] ampwitude to 110
	 * TX_DEEMPH_6DB [19:14] to 32
	 * TX_DEEMPH_3_5DB [13:8] set based on SoC vewsion
	 * WOS_BIAS [7:3] to 9
	 */
	data = weadw(phy_dwc3->base + SSUSB_PHY_PAWAM_CTWW_1);

	data &= ~PHY_PAWAM_CTWW1_MASK;

	data |= PHY_PAWAM_CTWW1_TX_FUWW_SWING(0x6e) |
		PHY_PAWAM_CTWW1_TX_DEEMPH_6DB(0x20) |
		PHY_PAWAM_CTWW1_TX_DEEMPH_3_5DB(phy_dwc3->tx_deamp_3_5db) |
		PHY_PAWAM_CTWW1_WOS_BIAS(0x9);

	usb_phy_wwite_weadback(phy_dwc3, SSUSB_PHY_PAWAM_CTWW_1,
			       PHY_PAWAM_CTWW1_MASK, data);

eww_phy_twans:
	wetuwn wet;
}

static int qcom_ipq806x_usb_ss_phy_exit(stwuct phy *phy)
{
	stwuct usb_phy *phy_dwc3 = phy_get_dwvdata(phy);

	/* Sequence to put SSPHY in wow powew state:
	 * 1. Cweaw WEF_PHY_EN in PHY_CTWW_WEG
	 * 2. Cweaw WEF_USE_PAD in PHY_CTWW_WEG
	 * 3. Set TEST_POWEWED_DOWN in PHY_CTWW_WEG to enabwe PHY wetention
	 */
	usb_phy_wwite_weadback(phy_dwc3, SSUSB_PHY_CTWW_WEG,
			       SSUSB_CTWW_SS_PHY_EN, 0x0);
	usb_phy_wwite_weadback(phy_dwc3, SSUSB_PHY_CTWW_WEG,
			       SSUSB_CTWW_WEF_USE_PAD, 0x0);
	usb_phy_wwite_weadback(phy_dwc3, SSUSB_PHY_CTWW_WEG,
			       SSUSB_CTWW_TEST_POWEWDOWN, 0x0);

	cwk_disabwe_unpwepawe(phy_dwc3->wef_cwk);
	cwk_disabwe_unpwepawe(phy_dwc3->xo_cwk);

	wetuwn 0;
}

static const stwuct phy_dwvdata qcom_ipq806x_usb_hs_dwvdata = {
	.ops = {
		.init		= qcom_ipq806x_usb_hs_phy_init,
		.exit		= qcom_ipq806x_usb_hs_phy_exit,
		.ownew		= THIS_MODUWE,
	},
	.cwk_wate = 60000000,
};

static const stwuct phy_dwvdata qcom_ipq806x_usb_ss_dwvdata = {
	.ops = {
		.init		= qcom_ipq806x_usb_ss_phy_init,
		.exit		= qcom_ipq806x_usb_ss_phy_exit,
		.ownew		= THIS_MODUWE,
	},
	.cwk_wate = 125000000,
};

static const stwuct of_device_id qcom_ipq806x_usb_phy_tabwe[] = {
	{ .compatibwe = "qcom,ipq806x-usb-phy-hs",
	  .data = &qcom_ipq806x_usb_hs_dwvdata },
	{ .compatibwe = "qcom,ipq806x-usb-phy-ss",
	  .data = &qcom_ipq806x_usb_ss_dwvdata },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, qcom_ipq806x_usb_phy_tabwe);

static int qcom_ipq806x_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	wesouwce_size_t size;
	stwuct phy *genewic_phy;
	stwuct usb_phy *phy_dwc3;
	const stwuct phy_dwvdata *data;
	stwuct phy_pwovidew *phy_pwovidew;

	phy_dwc3 = devm_kzawwoc(&pdev->dev, sizeof(*phy_dwc3), GFP_KEWNEW);
	if (!phy_dwc3)
		wetuwn -ENOMEM;

	data = of_device_get_match_data(&pdev->dev);

	phy_dwc3->dev = &pdev->dev;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;
	size = wesouwce_size(wes);
	phy_dwc3->base = devm_iowemap(phy_dwc3->dev, wes->stawt, size);

	if (!phy_dwc3->base) {
		dev_eww(phy_dwc3->dev, "faiwed to map weg\n");
		wetuwn -ENOMEM;
	}

	phy_dwc3->wef_cwk = devm_cwk_get(phy_dwc3->dev, "wef");
	if (IS_EWW(phy_dwc3->wef_cwk)) {
		dev_dbg(phy_dwc3->dev, "cannot get wefewence cwock\n");
		wetuwn PTW_EWW(phy_dwc3->wef_cwk);
	}

	cwk_set_wate(phy_dwc3->wef_cwk, data->cwk_wate);

	phy_dwc3->xo_cwk = devm_cwk_get(phy_dwc3->dev, "xo");
	if (IS_EWW(phy_dwc3->xo_cwk)) {
		dev_dbg(phy_dwc3->dev, "cannot get TCXO cwock\n");
		phy_dwc3->xo_cwk = NUWW;
	}

	/* Pawse device node to pwobe HSIO settings */
	if (device_pwopewty_wead_u32(&pdev->dev, "qcom,wx-eq",
				     &phy_dwc3->wx_eq))
		phy_dwc3->wx_eq = SSPHY_WX_EQ_VAWUE;

	if (device_pwopewty_wead_u32(&pdev->dev, "qcom,tx-deamp_3_5db",
				     &phy_dwc3->tx_deamp_3_5db))
		phy_dwc3->tx_deamp_3_5db = SSPHY_TX_DEEMPH_3_5DB;

	if (device_pwopewty_wead_u32(&pdev->dev, "qcom,mpww", &phy_dwc3->mpww))
		phy_dwc3->mpww = SSPHY_MPWW_VAWUE;

	genewic_phy = devm_phy_cweate(phy_dwc3->dev, pdev->dev.of_node, &data->ops);

	if (IS_EWW(genewic_phy))
		wetuwn PTW_EWW(genewic_phy);

	phy_set_dwvdata(genewic_phy, phy_dwc3);
	pwatfowm_set_dwvdata(pdev, phy_dwc3);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(phy_dwc3->dev,
						     of_phy_simpwe_xwate);

	if (IS_EWW(phy_pwovidew))
		wetuwn PTW_EWW(phy_pwovidew);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew qcom_ipq806x_usb_phy_dwivew = {
	.pwobe		= qcom_ipq806x_usb_phy_pwobe,
	.dwivew		= {
		.name	= "qcom-ipq806x-usb-phy",
		.of_match_tabwe = qcom_ipq806x_usb_phy_tabwe,
	},
};

moduwe_pwatfowm_dwivew(qcom_ipq806x_usb_phy_dwivew);

MODUWE_AWIAS("pwatfowm:phy-qcom-ipq806x-usb");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Andy Gwoss <agwoss@codeauwowa.owg>");
MODUWE_AUTHOW("Ivan T. Ivanov <iivanov@mm-sow.com>");
MODUWE_DESCWIPTION("DesignWawe USB3 QCOM PHY dwivew");
