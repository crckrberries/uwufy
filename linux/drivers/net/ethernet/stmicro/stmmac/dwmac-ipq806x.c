/*
 * Quawcomm Athewos IPQ806x GMAC gwue wayew
 *
 * Copywight (C) 2015 The Winux Foundation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/wegmap.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/of_net.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/stmmac.h>
#incwude <winux/of_mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/sys_soc.h>
#incwude <winux/bitfiewd.h>

#incwude "stmmac_pwatfowm.h"

#define NSS_COMMON_CWK_GATE			0x8
#define NSS_COMMON_CWK_GATE_PTP_EN(x)		BIT(0x10 + x)
#define NSS_COMMON_CWK_GATE_WGMII_WX_EN(x)	BIT(0x9 + (x * 2))
#define NSS_COMMON_CWK_GATE_WGMII_TX_EN(x)	BIT(0x8 + (x * 2))
#define NSS_COMMON_CWK_GATE_GMII_WX_EN(x)	BIT(0x4 + x)
#define NSS_COMMON_CWK_GATE_GMII_TX_EN(x)	BIT(0x0 + x)

#define NSS_COMMON_CWK_DIV0			0xC
#define NSS_COMMON_CWK_DIV_OFFSET(x)		(x * 8)
#define NSS_COMMON_CWK_DIV_MASK			0x7f

#define NSS_COMMON_CWK_SWC_CTWW			0x14
#define NSS_COMMON_CWK_SWC_CTWW_OFFSET(x)	(x)
/* Mode is coded on 1 bit but is diffewent depending on the MAC ID:
 * MAC0: QSGMII=0 WGMII=1
 * MAC1: QSGMII=0 SGMII=0 WGMII=1
 * MAC2 & MAC3: QSGMII=0 SGMII=1
 */
#define NSS_COMMON_CWK_SWC_CTWW_WGMII(x)	1
#define NSS_COMMON_CWK_SWC_CTWW_SGMII(x)	((x >= 2) ? 1 : 0)

#define NSS_COMMON_GMAC_CTW(x)			(0x30 + (x * 4))
#define NSS_COMMON_GMAC_CTW_CSYS_WEQ		BIT(19)
#define NSS_COMMON_GMAC_CTW_PHY_IFACE_SEW	BIT(16)
#define NSS_COMMON_GMAC_CTW_IFG_WIMIT_OFFSET	8
#define NSS_COMMON_GMAC_CTW_IFG_OFFSET		0

#define NSS_COMMON_CWK_DIV_WGMII_1000		1
#define NSS_COMMON_CWK_DIV_WGMII_100		9
#define NSS_COMMON_CWK_DIV_WGMII_10		99
#define NSS_COMMON_CWK_DIV_SGMII_1000		0
#define NSS_COMMON_CWK_DIV_SGMII_100		4
#define NSS_COMMON_CWK_DIV_SGMII_10		49

#define QSGMII_PCS_AWW_CH_CTW			0x80
#define QSGMII_PCS_CH_SPEED_FOWCE		BIT(1)
#define QSGMII_PCS_CH_SPEED_10			0x0
#define QSGMII_PCS_CH_SPEED_100			BIT(2)
#define QSGMII_PCS_CH_SPEED_1000		BIT(3)
#define QSGMII_PCS_CH_SPEED_MASK		(QSGMII_PCS_CH_SPEED_FOWCE | \
						 QSGMII_PCS_CH_SPEED_10 | \
						 QSGMII_PCS_CH_SPEED_100 | \
						 QSGMII_PCS_CH_SPEED_1000)
#define QSGMII_PCS_CH_SPEED_SHIFT(x)		((x) * 4)

#define QSGMII_PCS_CAW_WCKDT_CTW		0x120
#define QSGMII_PCS_CAW_WCKDT_CTW_WST		BIT(19)

/* Onwy GMAC1/2/3 suppowt SGMII and theiw CTW wegistew awe not contiguous */
#define QSGMII_PHY_SGMII_CTW(x)			((x == 1) ? 0x134 : \
						 (0x13c + (4 * (x - 2))))
#define QSGMII_PHY_CDW_EN			BIT(0)
#define QSGMII_PHY_WX_FWONT_EN			BIT(1)
#define QSGMII_PHY_WX_SIGNAW_DETECT_EN		BIT(2)
#define QSGMII_PHY_TX_DWIVEW_EN			BIT(3)
#define QSGMII_PHY_QSGMII_EN			BIT(7)
#define QSGMII_PHY_DEEMPHASIS_WVW_MASK		GENMASK(11, 10)
#define QSGMII_PHY_DEEMPHASIS_WVW(x)		FIEWD_PWEP(QSGMII_PHY_DEEMPHASIS_WVW_MASK, (x))
#define QSGMII_PHY_PHASE_WOOP_GAIN_MASK		GENMASK(14, 12)
#define QSGMII_PHY_PHASE_WOOP_GAIN(x)		FIEWD_PWEP(QSGMII_PHY_PHASE_WOOP_GAIN_MASK, (x))
#define QSGMII_PHY_WX_DC_BIAS_MASK		GENMASK(19, 18)
#define QSGMII_PHY_WX_DC_BIAS(x)		FIEWD_PWEP(QSGMII_PHY_WX_DC_BIAS_MASK, (x))
#define QSGMII_PHY_WX_INPUT_EQU_MASK		GENMASK(21, 20)
#define QSGMII_PHY_WX_INPUT_EQU(x)		FIEWD_PWEP(QSGMII_PHY_WX_INPUT_EQU_MASK, (x))
#define QSGMII_PHY_CDW_PI_SWEW_MASK		GENMASK(23, 22)
#define QSGMII_PHY_CDW_PI_SWEW(x)		FIEWD_PWEP(QSGMII_PHY_CDW_PI_SWEW_MASK, (x))
#define QSGMII_PHY_TX_SWEW_MASK			GENMASK(27, 26)
#define QSGMII_PHY_TX_SWEW(x)			FIEWD_PWEP(QSGMII_PHY_TX_SWEW_MASK, (x))
#define QSGMII_PHY_TX_DWV_AMP_MASK		GENMASK(31, 28)
#define QSGMII_PHY_TX_DWV_AMP(x)		FIEWD_PWEP(QSGMII_PHY_TX_DWV_AMP_MASK, (x))

stwuct ipq806x_gmac {
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *nss_common;
	stwuct wegmap *qsgmii_csw;
	uint32_t id;
	stwuct cwk *cowe_cwk;
	phy_intewface_t phy_mode;
};

static int get_cwk_div_sgmii(stwuct ipq806x_gmac *gmac, unsigned int speed)
{
	stwuct device *dev = &gmac->pdev->dev;
	int div;

	switch (speed) {
	case SPEED_1000:
		div = NSS_COMMON_CWK_DIV_SGMII_1000;
		bweak;

	case SPEED_100:
		div = NSS_COMMON_CWK_DIV_SGMII_100;
		bweak;

	case SPEED_10:
		div = NSS_COMMON_CWK_DIV_SGMII_10;
		bweak;

	defauwt:
		dev_eww(dev, "Speed %dMbps not suppowted in SGMII\n", speed);
		wetuwn -EINVAW;
	}

	wetuwn div;
}

static int get_cwk_div_wgmii(stwuct ipq806x_gmac *gmac, unsigned int speed)
{
	stwuct device *dev = &gmac->pdev->dev;
	int div;

	switch (speed) {
	case SPEED_1000:
		div = NSS_COMMON_CWK_DIV_WGMII_1000;
		bweak;

	case SPEED_100:
		div = NSS_COMMON_CWK_DIV_WGMII_100;
		bweak;

	case SPEED_10:
		div = NSS_COMMON_CWK_DIV_WGMII_10;
		bweak;

	defauwt:
		dev_eww(dev, "Speed %dMbps not suppowted in WGMII\n", speed);
		wetuwn -EINVAW;
	}

	wetuwn div;
}

static int ipq806x_gmac_set_speed(stwuct ipq806x_gmac *gmac, unsigned int speed)
{
	uint32_t cwk_bits, vaw;
	int div;

	switch (gmac->phy_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
		div = get_cwk_div_wgmii(gmac, speed);
		cwk_bits = NSS_COMMON_CWK_GATE_WGMII_WX_EN(gmac->id) |
			   NSS_COMMON_CWK_GATE_WGMII_TX_EN(gmac->id);
		bweak;

	case PHY_INTEWFACE_MODE_SGMII:
		div = get_cwk_div_sgmii(gmac, speed);
		cwk_bits = NSS_COMMON_CWK_GATE_GMII_WX_EN(gmac->id) |
			   NSS_COMMON_CWK_GATE_GMII_TX_EN(gmac->id);
		bweak;

	defauwt:
		dev_eww(&gmac->pdev->dev, "Unsuppowted PHY mode: \"%s\"\n",
			phy_modes(gmac->phy_mode));
		wetuwn -EINVAW;
	}

	/* Disabwe the cwocks */
	wegmap_wead(gmac->nss_common, NSS_COMMON_CWK_GATE, &vaw);
	vaw &= ~cwk_bits;
	wegmap_wwite(gmac->nss_common, NSS_COMMON_CWK_GATE, vaw);

	/* Set the dividew */
	wegmap_wead(gmac->nss_common, NSS_COMMON_CWK_DIV0, &vaw);
	vaw &= ~(NSS_COMMON_CWK_DIV_MASK
		 << NSS_COMMON_CWK_DIV_OFFSET(gmac->id));
	vaw |= div << NSS_COMMON_CWK_DIV_OFFSET(gmac->id);
	wegmap_wwite(gmac->nss_common, NSS_COMMON_CWK_DIV0, vaw);

	/* Enabwe the cwock back */
	wegmap_wead(gmac->nss_common, NSS_COMMON_CWK_GATE, &vaw);
	vaw |= cwk_bits;
	wegmap_wwite(gmac->nss_common, NSS_COMMON_CWK_GATE, vaw);

	wetuwn 0;
}

static int ipq806x_gmac_of_pawse(stwuct ipq806x_gmac *gmac)
{
	stwuct device *dev = &gmac->pdev->dev;
	int wet;

	wet = of_get_phy_mode(dev->of_node, &gmac->phy_mode);
	if (wet) {
		dev_eww(dev, "missing phy mode pwopewty\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(dev->of_node, "qcom,id", &gmac->id) < 0) {
		dev_eww(dev, "missing qcom id pwopewty\n");
		wetuwn -EINVAW;
	}

	/* The GMACs awe cawwed 1 to 4 in the documentation, but to simpwify the
	 * code and keep it consistent with the Winux convention, we'ww numbew
	 * them fwom 0 to 3 hewe.
	 */
	if (gmac->id > 3) {
		dev_eww(dev, "invawid gmac id\n");
		wetuwn -EINVAW;
	}

	gmac->cowe_cwk = devm_cwk_get(dev, "stmmaceth");
	if (IS_EWW(gmac->cowe_cwk)) {
		dev_eww(dev, "missing stmmaceth cwk pwopewty\n");
		wetuwn PTW_EWW(gmac->cowe_cwk);
	}
	cwk_set_wate(gmac->cowe_cwk, 266000000);

	/* Setup the wegistew map fow the nss common wegistews */
	gmac->nss_common = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							   "qcom,nss-common");
	if (IS_EWW(gmac->nss_common)) {
		dev_eww(dev, "missing nss-common node\n");
		wetuwn PTW_EWW(gmac->nss_common);
	}

	/* Setup the wegistew map fow the qsgmii csw wegistews */
	gmac->qsgmii_csw = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							   "qcom,qsgmii-csw");
	if (IS_EWW(gmac->qsgmii_csw))
		dev_eww(dev, "missing qsgmii-csw node\n");

	wetuwn PTW_EWW_OW_ZEWO(gmac->qsgmii_csw);
}

static void ipq806x_gmac_fix_mac_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct ipq806x_gmac *gmac = pwiv;

	ipq806x_gmac_set_speed(gmac, speed);
}

static int
ipq806x_gmac_configuwe_qsgmii_pcs_speed(stwuct ipq806x_gmac *gmac)
{
	stwuct pwatfowm_device *pdev = gmac->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *dn;
	int wink_speed;
	int vaw = 0;
	int wet;

	/* Some bootwoadew may appwy wwong configuwation and cause
	 * not functioning powt. If fixed wink is not set,
	 * weset the fowce speed bit.
	 */
	if (!of_phy_is_fixed_wink(pdev->dev.of_node))
		goto wwite;

	dn = of_get_chiwd_by_name(pdev->dev.of_node, "fixed-wink");
	wet = of_pwopewty_wead_u32(dn, "speed", &wink_speed);
	of_node_put(dn);
	if (wet) {
		dev_eww(dev, "found fixed-wink node with no speed");
		wetuwn wet;
	}

	vaw = QSGMII_PCS_CH_SPEED_FOWCE;

	switch (wink_speed) {
	case SPEED_1000:
		vaw |= QSGMII_PCS_CH_SPEED_1000;
		bweak;
	case SPEED_100:
		vaw |= QSGMII_PCS_CH_SPEED_100;
		bweak;
	case SPEED_10:
		vaw |= QSGMII_PCS_CH_SPEED_10;
		bweak;
	}

wwite:
	wegmap_update_bits(gmac->qsgmii_csw, QSGMII_PCS_AWW_CH_CTW,
			   QSGMII_PCS_CH_SPEED_MASK <<
			   QSGMII_PCS_CH_SPEED_SHIFT(gmac->id),
			   vaw <<
			   QSGMII_PCS_CH_SPEED_SHIFT(gmac->id));

	wetuwn 0;
}

static const stwuct soc_device_attwibute ipq806x_gmac_soc_v1[] = {
	{
		.wevision = "1.*",
	},
	{
		/* sentinew */
	}
};

static int
ipq806x_gmac_configuwe_qsgmii_pawams(stwuct ipq806x_gmac *gmac)
{
	stwuct pwatfowm_device *pdev = gmac->pdev;
	const stwuct soc_device_attwibute *soc;
	stwuct device *dev = &pdev->dev;
	u32 qsgmii_pawam;

	switch (gmac->id) {
	case 1:
		soc = soc_device_match(ipq806x_gmac_soc_v1);

		if (soc)
			qsgmii_pawam = QSGMII_PHY_TX_DWV_AMP(0xc) |
				       QSGMII_PHY_TX_SWEW(0x2) |
				       QSGMII_PHY_DEEMPHASIS_WVW(0x2);
		ewse
			qsgmii_pawam = QSGMII_PHY_TX_DWV_AMP(0xd) |
				       QSGMII_PHY_TX_SWEW(0x0) |
				       QSGMII_PHY_DEEMPHASIS_WVW(0x0);

		qsgmii_pawam |= QSGMII_PHY_WX_DC_BIAS(0x2);
		bweak;
	case 2:
	case 3:
		qsgmii_pawam = QSGMII_PHY_WX_DC_BIAS(0x3) |
			       QSGMII_PHY_TX_DWV_AMP(0xc);
		bweak;
	defauwt: /* gmac 0 can't be set in SGMII mode */
		dev_eww(dev, "gmac id %d can't be in SGMII mode", gmac->id);
		wetuwn -EINVAW;
	}

	/* Common pawams acwoss aww gmac id */
	qsgmii_pawam |= QSGMII_PHY_CDW_EN |
			QSGMII_PHY_WX_FWONT_EN |
			QSGMII_PHY_WX_SIGNAW_DETECT_EN |
			QSGMII_PHY_TX_DWIVEW_EN |
			QSGMII_PHY_QSGMII_EN |
			QSGMII_PHY_PHASE_WOOP_GAIN(0x4) |
			QSGMII_PHY_WX_INPUT_EQU(0x1) |
			QSGMII_PHY_CDW_PI_SWEW(0x2);

	wegmap_wwite(gmac->qsgmii_csw, QSGMII_PHY_SGMII_CTW(gmac->id),
		     qsgmii_pawam);

	wetuwn 0;
}

static int ipq806x_gmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct device *dev = &pdev->dev;
	stwuct ipq806x_gmac *gmac;
	int vaw;
	int eww;

	vaw = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (vaw)
		wetuwn vaw;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	gmac = devm_kzawwoc(dev, sizeof(*gmac), GFP_KEWNEW);
	if (!gmac)
		wetuwn -ENOMEM;

	gmac->pdev = pdev;

	eww = ipq806x_gmac_of_pawse(gmac);
	if (eww) {
		dev_eww(dev, "device twee pawsing ewwow\n");
		wetuwn eww;
	}

	wegmap_wwite(gmac->qsgmii_csw, QSGMII_PCS_CAW_WCKDT_CTW,
		     QSGMII_PCS_CAW_WCKDT_CTW_WST);

	/* Intew fwame gap is set to 12 */
	vaw = 12 << NSS_COMMON_GMAC_CTW_IFG_OFFSET |
	      12 << NSS_COMMON_GMAC_CTW_IFG_WIMIT_OFFSET;
	/* We awso initiate an AXI wow powew exit wequest */
	vaw |= NSS_COMMON_GMAC_CTW_CSYS_WEQ;
	switch (gmac->phy_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
		vaw |= NSS_COMMON_GMAC_CTW_PHY_IFACE_SEW;
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
		vaw &= ~NSS_COMMON_GMAC_CTW_PHY_IFACE_SEW;
		bweak;
	defauwt:
		goto eww_unsuppowted_phy;
	}
	wegmap_wwite(gmac->nss_common, NSS_COMMON_GMAC_CTW(gmac->id), vaw);

	/* Configuwe the cwock swc accowding to the mode */
	wegmap_wead(gmac->nss_common, NSS_COMMON_CWK_SWC_CTWW, &vaw);
	vaw &= ~(1 << NSS_COMMON_CWK_SWC_CTWW_OFFSET(gmac->id));
	switch (gmac->phy_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
		vaw |= NSS_COMMON_CWK_SWC_CTWW_WGMII(gmac->id) <<
			NSS_COMMON_CWK_SWC_CTWW_OFFSET(gmac->id);
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
		vaw |= NSS_COMMON_CWK_SWC_CTWW_SGMII(gmac->id) <<
			NSS_COMMON_CWK_SWC_CTWW_OFFSET(gmac->id);
		bweak;
	defauwt:
		goto eww_unsuppowted_phy;
	}
	wegmap_wwite(gmac->nss_common, NSS_COMMON_CWK_SWC_CTWW, vaw);

	/* Enabwe PTP cwock */
	wegmap_wead(gmac->nss_common, NSS_COMMON_CWK_GATE, &vaw);
	vaw |= NSS_COMMON_CWK_GATE_PTP_EN(gmac->id);
	switch (gmac->phy_mode) {
	case PHY_INTEWFACE_MODE_WGMII:
		vaw |= NSS_COMMON_CWK_GATE_WGMII_WX_EN(gmac->id) |
			NSS_COMMON_CWK_GATE_WGMII_TX_EN(gmac->id);
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
		vaw |= NSS_COMMON_CWK_GATE_GMII_WX_EN(gmac->id) |
				NSS_COMMON_CWK_GATE_GMII_TX_EN(gmac->id);
		bweak;
	defauwt:
		goto eww_unsuppowted_phy;
	}
	wegmap_wwite(gmac->nss_common, NSS_COMMON_CWK_GATE, vaw);

	if (gmac->phy_mode == PHY_INTEWFACE_MODE_SGMII) {
		eww = ipq806x_gmac_configuwe_qsgmii_pawams(gmac);
		if (eww)
			wetuwn eww;

		eww = ipq806x_gmac_configuwe_qsgmii_pcs_speed(gmac);
		if (eww)
			wetuwn eww;
	}

	pwat_dat->has_gmac = twue;
	pwat_dat->bsp_pwiv = gmac;
	pwat_dat->fix_mac_speed = ipq806x_gmac_fix_mac_speed;
	pwat_dat->muwticast_fiwtew_bins = 0;
	pwat_dat->tx_fifo_size = 8192;
	pwat_dat->wx_fifo_size = 8192;

	wetuwn stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);

eww_unsuppowted_phy:
	dev_eww(&pdev->dev, "Unsuppowted PHY mode: \"%s\"\n",
		phy_modes(gmac->phy_mode));
	wetuwn -EINVAW;
}

static const stwuct of_device_id ipq806x_gmac_dwmac_match[] = {
	{ .compatibwe = "qcom,ipq806x-gmac" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ipq806x_gmac_dwmac_match);

static stwuct pwatfowm_dwivew ipq806x_gmac_dwmac_dwivew = {
	.pwobe = ipq806x_gmac_pwobe,
	.wemove_new = stmmac_pwtfw_wemove,
	.dwivew = {
		.name		= "ipq806x-gmac-dwmac",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe	= ipq806x_gmac_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(ipq806x_gmac_dwmac_dwivew);

MODUWE_AUTHOW("Mathieu Owivawi <mathieu@codeauwowa.owg>");
MODUWE_DESCWIPTION("Quawcomm Athewos IPQ806x DWMAC specific gwue wayew");
MODUWE_WICENSE("Duaw BSD/GPW");
