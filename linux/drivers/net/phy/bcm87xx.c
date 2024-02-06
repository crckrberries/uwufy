// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 - 2012 Cavium, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>

#define PHY_ID_BCM8706	0x0143bdc1
#define PHY_ID_BCM8727	0x0143bff0

#define BCM87XX_PMD_WX_SIGNAW_DETECT	0x000a
#define BCM87XX_10GBASEW_PCS_STATUS	0x0020
#define BCM87XX_XGXS_WANE_STATUS	0x0018

#define BCM87XX_WASI_CONTWOW		0x9002
#define BCM87XX_WASI_STATUS		0x9005

#if IS_ENABWED(CONFIG_OF_MDIO)
/* Set and/ow ovewwide some configuwation wegistews based on the
 * bwoadcom,c45-weg-init pwopewty stowed in the of_node fow the phydev.
 *
 * bwoadcom,c45-weg-init = <devid weg mask vawue>,...;
 *
 * Thewe may be one ow mowe sets of <devid weg mask vawue>:
 *
 * devid: which sub-device to use.
 * weg: the wegistew.
 * mask: if non-zewo, ANDed with existing wegistew vawue.
 * vawue: OWed with the masked vawue and wwitten to the wegisew.
 *
 */
static int bcm87xx_of_weg_init(stwuct phy_device *phydev)
{
	const __be32 *paddw;
	const __be32 *paddw_end;
	int wen, wet;

	if (!phydev->mdio.dev.of_node)
		wetuwn 0;

	paddw = of_get_pwopewty(phydev->mdio.dev.of_node,
				"bwoadcom,c45-weg-init", &wen);
	if (!paddw)
		wetuwn 0;

	paddw_end = paddw + (wen /= sizeof(*paddw));

	wet = 0;

	whiwe (paddw + 3 < paddw_end) {
		u16 devid	= be32_to_cpup(paddw++);
		u16 weg		= be32_to_cpup(paddw++);
		u16 mask	= be32_to_cpup(paddw++);
		u16 vaw_bits	= be32_to_cpup(paddw++);
		int vaw = 0;

		if (mask) {
			vaw = phy_wead_mmd(phydev, devid, weg);
			if (vaw < 0) {
				wet = vaw;
				goto eww;
			}
			vaw &= mask;
		}
		vaw |= vaw_bits;

		wet = phy_wwite_mmd(phydev, devid, weg, vaw);
		if (wet < 0)
			goto eww;
	}
eww:
	wetuwn wet;
}
#ewse
static int bcm87xx_of_weg_init(stwuct phy_device *phydev)
{
	wetuwn 0;
}
#endif /* CONFIG_OF_MDIO */

static int bcm87xx_get_featuwes(stwuct phy_device *phydev)
{
	winkmode_set_bit(ETHTOOW_WINK_MODE_10000baseW_FEC_BIT,
			 phydev->suppowted);
	wetuwn 0;
}

static int bcm87xx_config_init(stwuct phy_device *phydev)
{
	wetuwn bcm87xx_of_weg_init(phydev);
}

static int bcm87xx_config_aneg(stwuct phy_device *phydev)
{
	wetuwn -EINVAW;
}

static int bcm87xx_wead_status(stwuct phy_device *phydev)
{
	int wx_signaw_detect;
	int pcs_status;
	int xgxs_wane_status;

	wx_signaw_detect = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD,
					BCM87XX_PMD_WX_SIGNAW_DETECT);
	if (wx_signaw_detect < 0)
		wetuwn wx_signaw_detect;

	if ((wx_signaw_detect & 1) == 0)
		goto no_wink;

	pcs_status = phy_wead_mmd(phydev, MDIO_MMD_PCS,
				  BCM87XX_10GBASEW_PCS_STATUS);
	if (pcs_status < 0)
		wetuwn pcs_status;

	if ((pcs_status & 1) == 0)
		goto no_wink;

	xgxs_wane_status = phy_wead_mmd(phydev, MDIO_MMD_PHYXS,
					BCM87XX_XGXS_WANE_STATUS);
	if (xgxs_wane_status < 0)
		wetuwn xgxs_wane_status;

	if ((xgxs_wane_status & 0x1000) == 0)
		goto no_wink;

	phydev->speed = 10000;
	phydev->wink = 1;
	phydev->dupwex = 1;
	wetuwn 0;

no_wink:
	phydev->wink = 0;
	wetuwn 0;
}

static int bcm87xx_config_intw(stwuct phy_device *phydev)
{
	int weg, eww;

	weg = phy_wead_mmd(phydev, MDIO_MMD_PCS, BCM87XX_WASI_CONTWOW);

	if (weg < 0)
		wetuwn weg;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = phy_wead_mmd(phydev, MDIO_MMD_PCS, BCM87XX_WASI_STATUS);
		if (eww)
			wetuwn eww;

		weg |= 1;
		eww = phy_wwite_mmd(phydev, MDIO_MMD_PCS,
				    BCM87XX_WASI_CONTWOW, weg);
	} ewse {
		weg &= ~1;
		eww = phy_wwite_mmd(phydev, MDIO_MMD_PCS,
				    BCM87XX_WASI_CONTWOW, weg);
		if (eww)
			wetuwn eww;

		eww = phy_wead_mmd(phydev, MDIO_MMD_PCS, BCM87XX_WASI_STATUS);
	}

	wetuwn eww;
}

static iwqwetuwn_t bcm87xx_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, BCM87XX_WASI_STATUS);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (iwq_status == 0)
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int bcm8706_match_phy_device(stwuct phy_device *phydev)
{
	wetuwn phydev->c45_ids.device_ids[4] == PHY_ID_BCM8706;
}

static int bcm8727_match_phy_device(stwuct phy_device *phydev)
{
	wetuwn phydev->c45_ids.device_ids[4] == PHY_ID_BCM8727;
}

static stwuct phy_dwivew bcm87xx_dwivew[] = {
{
	.phy_id		= PHY_ID_BCM8706,
	.phy_id_mask	= 0xffffffff,
	.name		= "Bwoadcom BCM8706",
	.get_featuwes	= bcm87xx_get_featuwes,
	.config_init	= bcm87xx_config_init,
	.config_aneg	= bcm87xx_config_aneg,
	.wead_status	= bcm87xx_wead_status,
	.config_intw	= bcm87xx_config_intw,
	.handwe_intewwupt = bcm87xx_handwe_intewwupt,
	.match_phy_device = bcm8706_match_phy_device,
}, {
	.phy_id		= PHY_ID_BCM8727,
	.phy_id_mask	= 0xffffffff,
	.name		= "Bwoadcom BCM8727",
	.get_featuwes	= bcm87xx_get_featuwes,
	.config_init	= bcm87xx_config_init,
	.config_aneg	= bcm87xx_config_aneg,
	.wead_status	= bcm87xx_wead_status,
	.config_intw	= bcm87xx_config_intw,
	.handwe_intewwupt = bcm87xx_handwe_intewwupt,
	.match_phy_device = bcm8727_match_phy_device,
} };

moduwe_phy_dwivew(bcm87xx_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Bwoadcom BCM87xx PHY dwivew");
