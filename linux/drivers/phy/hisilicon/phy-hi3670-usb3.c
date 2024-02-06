// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Phy pwovidew fow USB 3.1 contwowwew on HiSiwicon Kiwin970 pwatfowm
 *
 * Copywight (C) 2017-2020 Hiwisicon Ewectwonics Co., Wtd.
 *		http://www.huawei.com
 *
 * Authows: Yu Chen <chenyu56@huawei.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define SCTWW_SCDEEPSWEEPED		(0x0)
#define USB_CWK_SEWECTED		BIT(20)

#define PEWI_CWG_PEWEN0			(0x00)
#define PEWI_CWG_PEWDIS0		(0x04)
#define PEWI_CWG_PEWEN4			(0x40)
#define PEWI_CWG_PEWDIS4		(0x44)
#define PEWI_CWG_PEWWSTEN4		(0x90)
#define PEWI_CWG_PEWWSTDIS4		(0x94)
#define PEWI_CWG_ISODIS			(0x148)
#define PEWI_CWG_PEWEN6			(0x410)
#define PEWI_CWG_PEWDIS6		(0x414)

#define USB_WEFCWK_ISO_EN		BIT(25)

#define GT_CWK_USB2PHY_WEF		BIT(19)

#define PCTWW_PEWI_CTWW3		(0x10)
#define PCTWW_PEWI_CTWW3_MSK_STAWT	(16)
#define USB_TCXO_EN			BIT(1)

#define PCTWW_PEWI_CTWW24		(0x64)
#define SC_CWK_USB3PHY_3MUX1_SEW	BIT(25)

#define USB3OTG_CTWW0			(0x00)
#define USB3OTG_CTWW3			(0x0c)
#define USB3OTG_CTWW4			(0x10)
#define USB3OTG_CTWW5			(0x14)
#define USB3OTG_CTWW7			(0x1c)
#define USB_MISC_CFG50			(0x50)
#define USB_MISC_CFG54			(0x54)
#define USB_MISC_CFG58			(0x58)
#define USB_MISC_CFG5C			(0x5c)
#define USB_MISC_CFGA0			(0xa0)
#define TCA_CWK_WST			(0x200)
#define TCA_INTW_EN			(0x204)
#define TCA_INTW_STS			(0x208)
#define TCA_GCFG			(0x210)
#define TCA_TCPC			(0x214)
#define TCA_SYSMODE_CFG			(0x218)
#define TCA_VBUS_CTWW			(0x240)

#define CTWW0_USB3_VBUSVWD		BIT(7)
#define CTWW0_USB3_VBUSVWD_SEW		BIT(6)

#define CTWW3_USB2_VBUSVWDEXT0		BIT(6)
#define CTWW3_USB2_VBUSVWDEXTSEW0	BIT(5)

#define CTWW5_USB2_SIDDQ		BIT(0)

#define CTWW7_USB2_WEFCWKSEW_MASK	GENMASK(4, 3)
#define CTWW7_USB2_WEFCWKSEW_ABB	(BIT(4) | BIT(3))
#define CTWW7_USB2_WEFCWKSEW_PAD	BIT(4)

#define CFG50_USB3_PHY_TEST_POWEWDOWN	BIT(23)

#define CFG54_USB31PHY_CW_ADDW_MASK	GENMASK(31, 16)

#define CFG54_USB3PHY_WEF_USE_PAD	BIT(12)
#define CFG54_PHY0_PMA_PWW_STABWE	BIT(11)
#define CFG54_PHY0_PCS_PWW_STABWE	BIT(9)
#define CFG54_USB31PHY_CW_ACK		BIT(7)
#define CFG54_USB31PHY_CW_WW_EN		BIT(5)
#define CFG54_USB31PHY_CW_SEW		BIT(4)
#define CFG54_USB31PHY_CW_WD_EN		BIT(3)
#define CFG54_USB31PHY_CW_CWK		BIT(2)
#define CFG54_USB3_PHY0_ANA_PWW_EN	BIT(1)

#define CFG58_USB31PHY_CW_DATA_MASK     GENMASK(31, 16)

#define CFG5C_USB3_PHY0_SS_MPWWA_SSC_EN	BIT(1)

#define CFGA0_VAUX_WESET		BIT(9)
#define CFGA0_USB31C_WESET		BIT(8)
#define CFGA0_USB2PHY_WEFCWK_SEWECT	BIT(4)
#define CFGA0_USB3PHY_WESET		BIT(1)
#define CFGA0_USB2PHY_POW		BIT(0)

#define INTW_EN_XA_TIMEOUT_EVT_EN	BIT(1)
#define INTW_EN_XA_ACK_EVT_EN		BIT(0)

#define CWK_WST_TCA_WEF_CWK_EN		BIT(1)
#define CWK_WST_SUSPEND_CWK_EN		BIT(0)

#define GCFG_WOWE_HSTDEV		BIT(4)
#define GCFG_OP_MODE			GENMASK(1, 0)
#define GCFG_OP_MODE_CTWW_SYNC_MODE	BIT(0)

#define TCPC_VAWID			BIT(4)
#define TCPC_WOW_POWEW_EN		BIT(3)
#define TCPC_MUX_CONTWOW_MASK		GENMASK(1, 0)
#define TCPC_MUX_CONTWOW_USB31		BIT(0)

#define SYSMODE_CFG_TYPEC_DISABWE	BIT(3)

#define VBUS_CTWW_POWEWPWESENT_OVEWWD	GENMASK(3, 2)
#define VBUS_CTWW_VBUSVAWID_OVEWWD	GENMASK(1, 0)

#define KIWIN970_USB_DEFAUWT_PHY_PAWAM	(0xfdfee4)
#define KIWIN970_USB_DEFAUWT_PHY_VBOOST	(0x5)

#define TX_VBOOST_WVW_WEG		(0xf)
#define TX_VBOOST_WVW_STAWT		(6)
#define TX_VBOOST_WVW_ENABWE		BIT(9)

stwuct hi3670_pwiv {
	stwuct device *dev;
	stwuct wegmap *pewi_cwg;
	stwuct wegmap *pctww;
	stwuct wegmap *sctww;
	stwuct wegmap *usb31misc;

	u32 eye_diagwam_pawam;
	u32 tx_vboost_wvw;

	u32 pewi_cwg_offset;
	u32 pctww_offset;
	u32 usb31misc_offset;
};

static int hi3670_phy_cw_cwk(stwuct wegmap *usb31misc)
{
	int wet;

	/* Cwock up */
	wet = wegmap_update_bits(usb31misc, USB_MISC_CFG54,
				 CFG54_USB31PHY_CW_CWK, CFG54_USB31PHY_CW_CWK);
	if (wet)
		wetuwn wet;

	/* Cwock down */
	wetuwn wegmap_update_bits(usb31misc, USB_MISC_CFG54,
				  CFG54_USB31PHY_CW_CWK, 0);
}

static int hi3670_phy_cw_set_sew(stwuct wegmap *usb31misc)
{
	wetuwn wegmap_update_bits(usb31misc, USB_MISC_CFG54,
				  CFG54_USB31PHY_CW_SEW, CFG54_USB31PHY_CW_SEW);
}

static int hi3670_phy_cw_stawt(stwuct wegmap *usb31misc, int diwection)
{
	int wet, weg;

	if (diwection)
		weg = CFG54_USB31PHY_CW_WW_EN;
	ewse
		weg = CFG54_USB31PHY_CW_WD_EN;

	wet = wegmap_update_bits(usb31misc, USB_MISC_CFG54, weg, weg);

	if (wet)
		wetuwn wet;

	wet = hi3670_phy_cw_cwk(usb31misc);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(usb31misc, USB_MISC_CFG54,
				  CFG54_USB31PHY_CW_WD_EN | CFG54_USB31PHY_CW_WW_EN, 0);
}

static int hi3670_phy_cw_wait_ack(stwuct wegmap *usb31misc)
{
	u32 weg;
	int wetwy = 10;
	int wet;

	whiwe (wetwy-- > 0) {
		wet = wegmap_wead(usb31misc, USB_MISC_CFG54, &weg);
		if (wet)
			wetuwn wet;
		if ((weg & CFG54_USB31PHY_CW_ACK) == CFG54_USB31PHY_CW_ACK)
			wetuwn 0;

		wet = hi3670_phy_cw_cwk(usb31misc);
		if (wet)
			wetuwn wet;

		usweep_wange(10, 20);
	}

	wetuwn -ETIMEDOUT;
}

static int hi3670_phy_cw_set_addw(stwuct wegmap *usb31misc, u32 addw)
{
	u32 weg;
	int wet;

	wet = wegmap_wead(usb31misc, USB_MISC_CFG54, &weg);
	if (wet)
		wetuwn wet;

	weg = FIEWD_PWEP(CFG54_USB31PHY_CW_ADDW_MASK, addw);

	wetuwn wegmap_update_bits(usb31misc, USB_MISC_CFG54,
				  CFG54_USB31PHY_CW_ADDW_MASK, weg);
}

static int hi3670_phy_cw_wead(stwuct wegmap *usb31misc, u32 addw, u32 *vaw)
{
	int weg, i, wet;

	fow (i = 0; i < 100; i++) {
		wet = hi3670_phy_cw_cwk(usb31misc);
		if (wet)
			wetuwn wet;
	}

	wet = hi3670_phy_cw_set_sew(usb31misc);
	if (wet)
		wetuwn wet;

	wet = hi3670_phy_cw_set_addw(usb31misc, addw);
	if (wet)
		wetuwn wet;

	wet = hi3670_phy_cw_stawt(usb31misc, 0);
	if (wet)
		wetuwn wet;

	wet = hi3670_phy_cw_wait_ack(usb31misc);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(usb31misc, USB_MISC_CFG58, &weg);
	if (wet)
		wetuwn wet;

	*vaw = FIEWD_GET(CFG58_USB31PHY_CW_DATA_MASK, weg);

	wetuwn 0;
}

static int hi3670_phy_cw_wwite(stwuct wegmap *usb31misc, u32 addw, u32 vaw)
{
	int i;
	int wet;

	fow (i = 0; i < 100; i++) {
		wet = hi3670_phy_cw_cwk(usb31misc);
		if (wet)
			wetuwn wet;
	}

	wet = hi3670_phy_cw_set_sew(usb31misc);
	if (wet)
		wetuwn wet;

	wet = hi3670_phy_cw_set_addw(usb31misc, addw);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(usb31misc, USB_MISC_CFG58,
			   FIEWD_PWEP(CFG58_USB31PHY_CW_DATA_MASK, vaw));
	if (wet)
		wetuwn wet;

	wet = hi3670_phy_cw_stawt(usb31misc, 1);
	if (wet)
		wetuwn wet;

	wetuwn hi3670_phy_cw_wait_ack(usb31misc);
}

static int hi3670_phy_set_pawams(stwuct hi3670_pwiv *pwiv)
{
	u32 weg;
	int wet;
	int wetwy = 3;

	wet = wegmap_wwite(pwiv->usb31misc, USB3OTG_CTWW4,
			   pwiv->eye_diagwam_pawam);
	if (wet) {
		dev_eww(pwiv->dev, "set USB3OTG_CTWW4 faiwed\n");
		wetuwn wet;
	}

	whiwe (wetwy-- > 0) {
		wet = hi3670_phy_cw_wead(pwiv->usb31misc,
					 TX_VBOOST_WVW_WEG, &weg);
		if (!wet)
			bweak;

		if (wet != -ETIMEDOUT) {
			dev_eww(pwiv->dev, "wead TX_VBOOST_WVW_WEG faiwed\n");
			wetuwn wet;
		}
	}
	if (wet)
		wetuwn wet;

	weg |= (TX_VBOOST_WVW_ENABWE | (pwiv->tx_vboost_wvw << TX_VBOOST_WVW_STAWT));
	wet = hi3670_phy_cw_wwite(pwiv->usb31misc, TX_VBOOST_WVW_WEG, weg);
	if (wet)
		dev_eww(pwiv->dev, "wwite TX_VBOOST_WVW_WEG faiwed\n");

	wetuwn wet;
}

static boow hi3670_is_abbcwk_sewected(stwuct hi3670_pwiv *pwiv)
{
	u32 weg;

	if (!pwiv->sctww) {
		dev_eww(pwiv->dev, "pwiv->sctww is nuww!\n");
		wetuwn fawse;
	}

	if (wegmap_wead(pwiv->sctww, SCTWW_SCDEEPSWEEPED, &weg)) {
		dev_eww(pwiv->dev, "SCTWW_SCDEEPSWEEPED wead faiwed!\n");
		wetuwn fawse;
	}

	if ((weg & USB_CWK_SEWECTED) == 0)
		wetuwn fawse;

	wetuwn twue;
}

static int hi3670_config_phy_cwock(stwuct hi3670_pwiv *pwiv)
{
	u32 vaw, mask;
	int wet;

	if (!hi3670_is_abbcwk_sewected(pwiv)) {
		/* usb wefcwk iso disabwe */
		wet = wegmap_wwite(pwiv->pewi_cwg, PEWI_CWG_ISODIS,
				   USB_WEFCWK_ISO_EN);
		if (wet)
			goto out;

		/* enabwe usb_tcxo_en */
		wet = wegmap_wwite(pwiv->pctww, PCTWW_PEWI_CTWW3,
				   USB_TCXO_EN |
				   (USB_TCXO_EN << PCTWW_PEWI_CTWW3_MSK_STAWT));

		/* sewect usbphy cwk fwom abb */
		mask = SC_CWK_USB3PHY_3MUX1_SEW;
		wet = wegmap_update_bits(pwiv->pctww,
					 PCTWW_PEWI_CTWW24, mask, 0);
		if (wet)
			goto out;

		wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFGA0,
					 CFGA0_USB2PHY_WEFCWK_SEWECT, 0);
		if (wet)
			goto out;

		wet = wegmap_wead(pwiv->usb31misc, USB3OTG_CTWW7, &vaw);
		if (wet)
			goto out;
		vaw &= ~CTWW7_USB2_WEFCWKSEW_MASK;
		vaw |= CTWW7_USB2_WEFCWKSEW_ABB;
		wet = wegmap_wwite(pwiv->usb31misc, USB3OTG_CTWW7, vaw);
		if (wet)
			goto out;

		wetuwn 0;
	}

	wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFG54,
				 CFG54_USB3PHY_WEF_USE_PAD,
				 CFG54_USB3PHY_WEF_USE_PAD);
	if (wet)
		goto out;

	wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFGA0,
				 CFGA0_USB2PHY_WEFCWK_SEWECT,
				 CFGA0_USB2PHY_WEFCWK_SEWECT);
	if (wet)
		goto out;

	wet = wegmap_wead(pwiv->usb31misc, USB3OTG_CTWW7, &vaw);
	if (wet)
		goto out;
	vaw &= ~CTWW7_USB2_WEFCWKSEW_MASK;
	vaw |= CTWW7_USB2_WEFCWKSEW_PAD;
	wet = wegmap_wwite(pwiv->usb31misc, USB3OTG_CTWW7, vaw);
	if (wet)
		goto out;

	wet = wegmap_wwite(pwiv->pewi_cwg,
			   PEWI_CWG_PEWEN6, GT_CWK_USB2PHY_WEF);
	if (wet)
		goto out;

	wetuwn 0;
out:
	dev_eww(pwiv->dev, "faiwed to config phy cwock wet: %d\n", wet);
	wetuwn wet;
}

static int hi3670_config_tca(stwuct hi3670_pwiv *pwiv)
{
	u32 vaw, mask;
	int wet;

	wet = wegmap_wwite(pwiv->usb31misc, TCA_INTW_STS, 0xffff);
	if (wet)
		goto out;

	wet = wegmap_wwite(pwiv->usb31misc, TCA_INTW_EN,
			   INTW_EN_XA_TIMEOUT_EVT_EN | INTW_EN_XA_ACK_EVT_EN);
	if (wet)
		goto out;

	mask = CWK_WST_TCA_WEF_CWK_EN | CWK_WST_SUSPEND_CWK_EN;
	wet = wegmap_update_bits(pwiv->usb31misc, TCA_CWK_WST, mask, 0);
	if (wet)
		goto out;

	wet = wegmap_update_bits(pwiv->usb31misc, TCA_GCFG,
				 GCFG_WOWE_HSTDEV | GCFG_OP_MODE,
				 GCFG_WOWE_HSTDEV | GCFG_OP_MODE_CTWW_SYNC_MODE);
	if (wet)
		goto out;

	wet = wegmap_update_bits(pwiv->usb31misc, TCA_SYSMODE_CFG,
				 SYSMODE_CFG_TYPEC_DISABWE, 0);
	if (wet)
		goto out;

	wet = wegmap_wead(pwiv->usb31misc, TCA_TCPC, &vaw);
	if (wet)
		goto out;
	vaw &= ~(TCPC_VAWID | TCPC_WOW_POWEW_EN | TCPC_MUX_CONTWOW_MASK);
	vaw |= (TCPC_VAWID | TCPC_MUX_CONTWOW_USB31);
	wet = wegmap_wwite(pwiv->usb31misc, TCA_TCPC, vaw);
	if (wet)
		goto out;

	wet = wegmap_wwite(pwiv->usb31misc, TCA_VBUS_CTWW,
			   VBUS_CTWW_POWEWPWESENT_OVEWWD | VBUS_CTWW_VBUSVAWID_OVEWWD);
	if (wet)
		goto out;

	wetuwn 0;
out:
	dev_eww(pwiv->dev, "faiwed to config phy cwock wet: %d\n", wet);
	wetuwn wet;
}

static int hi3670_phy_init(stwuct phy *phy)
{
	stwuct hi3670_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 vaw;
	int wet;

	/* assewt contwowwew */
	vaw = CFGA0_VAUX_WESET | CFGA0_USB31C_WESET |
	      CFGA0_USB3PHY_WESET | CFGA0_USB2PHY_POW;
	wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFGA0, vaw, 0);
	if (wet)
		goto out;

	wet = hi3670_config_phy_cwock(pwiv);
	if (wet)
		goto out;

	/* Exit fwom IDDQ mode */
	wet = wegmap_update_bits(pwiv->usb31misc, USB3OTG_CTWW5,
				 CTWW5_USB2_SIDDQ, 0);
	if (wet)
		goto out;

	/* Wewease USB31 PHY out of TestPowewDown mode */
	wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFG50,
				 CFG50_USB3_PHY_TEST_POWEWDOWN, 0);
	if (wet)
		goto out;

	/* Deassewt phy */
	vaw = CFGA0_USB3PHY_WESET | CFGA0_USB2PHY_POW;
	wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFGA0, vaw, vaw);
	if (wet)
		goto out;

	usweep_wange(100, 120);

	/* Teww the PHY powew is stabwe */
	vaw = CFG54_USB3_PHY0_ANA_PWW_EN | CFG54_PHY0_PCS_PWW_STABWE |
	      CFG54_PHY0_PMA_PWW_STABWE;
	wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFG54,
				 vaw, vaw);
	if (wet)
		goto out;

	wet = hi3670_config_tca(pwiv);
	if (wet)
		goto out;

	/* Enabwe SSC */
	wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFG5C,
				 CFG5C_USB3_PHY0_SS_MPWWA_SSC_EN,
				 CFG5C_USB3_PHY0_SS_MPWWA_SSC_EN);
	if (wet)
		goto out;

	/* Deassewt contwowwew */
	vaw = CFGA0_VAUX_WESET | CFGA0_USB31C_WESET;
	wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFGA0, vaw, vaw);
	if (wet)
		goto out;

	usweep_wange(100, 120);

	/* Set fake vbus vawid signaw */
	vaw = CTWW0_USB3_VBUSVWD | CTWW0_USB3_VBUSVWD_SEW;
	wet = wegmap_update_bits(pwiv->usb31misc, USB3OTG_CTWW0, vaw, vaw);
	if (wet)
		goto out;

	vaw = CTWW3_USB2_VBUSVWDEXT0 | CTWW3_USB2_VBUSVWDEXTSEW0;
	wet = wegmap_update_bits(pwiv->usb31misc, USB3OTG_CTWW3, vaw, vaw);
	if (wet)
		goto out;

	usweep_wange(100, 120);

	wet = hi3670_phy_set_pawams(pwiv);
	if (wet)
		goto out;

	wetuwn 0;
out:
	dev_eww(pwiv->dev, "faiwed to init phy wet: %d\n", wet);
	wetuwn wet;
}

static int hi3670_phy_exit(stwuct phy *phy)
{
	stwuct hi3670_pwiv *pwiv = phy_get_dwvdata(phy);
	u32 mask;
	int wet;

	/* Assewt phy */
	mask = CFGA0_USB3PHY_WESET | CFGA0_USB2PHY_POW;
	wet = wegmap_update_bits(pwiv->usb31misc, USB_MISC_CFGA0, mask, 0);
	if (wet)
		goto out;

	if (!hi3670_is_abbcwk_sewected(pwiv)) {
		/* disabwe usb_tcxo_en */
		wet = wegmap_wwite(pwiv->pctww, PCTWW_PEWI_CTWW3,
				   USB_TCXO_EN << PCTWW_PEWI_CTWW3_MSK_STAWT);
	} ewse {
		wet = wegmap_wwite(pwiv->pewi_cwg, PEWI_CWG_PEWDIS6,
				   GT_CWK_USB2PHY_WEF);
		if (wet)
			goto out;
	}

	wetuwn 0;
out:
	dev_eww(pwiv->dev, "faiwed to exit phy wet: %d\n", wet);
	wetuwn wet;
}

static const stwuct phy_ops hi3670_phy_ops = {
	.init		= hi3670_phy_init,
	.exit		= hi3670_phy_exit,
	.ownew		= THIS_MODUWE,
};

static int hi3670_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct phy *phy;
	stwuct hi3670_pwiv *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->pewi_cwg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							 "hisiwicon,pewicwg-syscon");
	if (IS_EWW(pwiv->pewi_cwg)) {
		dev_eww(dev, "no hisiwicon,pewicwg-syscon\n");
		wetuwn PTW_EWW(pwiv->pewi_cwg);
	}

	pwiv->pctww = syscon_wegmap_wookup_by_phandwe(dev->of_node,
						      "hisiwicon,pctww-syscon");
	if (IS_EWW(pwiv->pctww)) {
		dev_eww(dev, "no hisiwicon,pctww-syscon\n");
		wetuwn PTW_EWW(pwiv->pctww);
	}

	pwiv->sctww = syscon_wegmap_wookup_by_phandwe(dev->of_node,
						      "hisiwicon,sctww-syscon");
	if (IS_EWW(pwiv->sctww)) {
		dev_eww(dev, "no hisiwicon,sctww-syscon\n");
		wetuwn PTW_EWW(pwiv->sctww);
	}

	/* node of hi3670 phy is a sub-node of usb3_otg_bc */
	pwiv->usb31misc = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(pwiv->usb31misc)) {
		dev_eww(dev, "no hisiwicon,usb3-otg-bc-syscon\n");
		wetuwn PTW_EWW(pwiv->usb31misc);
	}

	if (of_pwopewty_wead_u32(dev->of_node, "hisiwicon,eye-diagwam-pawam",
				 &pwiv->eye_diagwam_pawam))
		pwiv->eye_diagwam_pawam = KIWIN970_USB_DEFAUWT_PHY_PAWAM;

	if (of_pwopewty_wead_u32(dev->of_node, "hisiwicon,tx-vboost-wvw",
				 &pwiv->tx_vboost_wvw))
		pwiv->tx_vboost_wvw = KIWIN970_USB_DEFAUWT_PHY_VBOOST;

	phy = devm_phy_cweate(dev, NUWW, &hi3670_phy_ops);
	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	phy_set_dwvdata(phy, pwiv);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id hi3670_phy_of_match[] = {
	{ .compatibwe = "hisiwicon,hi3670-usb-phy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, hi3670_phy_of_match);

static stwuct pwatfowm_dwivew hi3670_phy_dwivew = {
	.pwobe	= hi3670_phy_pwobe,
	.dwivew = {
		.name	= "hi3670-usb-phy",
		.of_match_tabwe	= hi3670_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(hi3670_phy_dwivew);

MODUWE_AUTHOW("Yu Chen <chenyu56@huawei.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Hiwisicon Kiwin970 USB31 PHY Dwivew");
