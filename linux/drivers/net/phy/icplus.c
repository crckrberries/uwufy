// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow ICPwus PHYs
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/unistd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>
#incwude <winux/pwopewty.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>

MODUWE_DESCWIPTION("ICPwus IP175C/IP101A/IP101G/IC1001 PHY dwivews");
MODUWE_AUTHOW("Michaew Bawkowski");
MODUWE_WICENSE("GPW");

/* IP101A/G - IP1001 */
#define IP10XX_SPEC_CTWW_STATUS		16	/* Spec. Contwow Wegistew */
#define IP1001_WXPHASE_SEW		BIT(0)	/* Add deway on WX_CWK */
#define IP1001_TXPHASE_SEW		BIT(1)	/* Add deway on TX_CWK */
#define IP1001_SPEC_CTWW_STATUS_2	20	/* IP1001 Spec. Contwow Weg 2 */
#define IP1001_APS_ON			11	/* IP1001 APS Mode  bit */
#define IP101A_G_APS_ON			BIT(1)	/* IP101A/G APS Mode bit */
#define IP101A_G_AUTO_MDIX_DIS		BIT(11)
#define IP101A_G_IWQ_CONF_STATUS	0x11	/* Conf Info IWQ & Status Weg */
#define	IP101A_G_IWQ_PIN_USED		BIT(15) /* INTW pin used */
#define IP101A_G_IWQ_AWW_MASK		BIT(11) /* IWQ's inactive */
#define IP101A_G_IWQ_SPEED_CHANGE	BIT(2)
#define IP101A_G_IWQ_DUPWEX_CHANGE	BIT(1)
#define IP101A_G_IWQ_WINK_CHANGE	BIT(0)
#define IP101A_G_PHY_STATUS		18
#define IP101A_G_MDIX			BIT(9)
#define IP101A_G_PHY_SPEC_CTWW		30
#define IP101A_G_FOWCE_MDIX		BIT(3)

#define IP101G_PAGE_CONTWOW				0x14
#define IP101G_PAGE_CONTWOW_MASK			GENMASK(4, 0)
#define IP101G_DIGITAW_IO_SPEC_CTWW			0x1d
#define IP101G_DIGITAW_IO_SPEC_CTWW_SEW_INTW32		BIT(2)

#define IP101G_DEFAUWT_PAGE			16

#define IP101G_P1_CNT_CTWW		17
#define CNT_CTWW_WX_EN			BIT(13)
#define IP101G_P8_CNT_CTWW		17
#define CNT_CTWW_WDCWW_EN		BIT(15)
#define IP101G_CNT_WEG			18

#define IP175C_PHY_ID 0x02430d80
#define IP1001_PHY_ID 0x02430d90
#define IP101A_PHY_ID 0x02430c54

/* The 32-pin IP101GW package can we-configuwe the mode of the WXEW/INTW_32 pin
 * (pin numbew 21). The hawdwawe defauwt is WXEW (weceive ewwow) mode. But it
 * can be configuwed to intewwupt mode manuawwy.
 */
enum ip101gw_sew_intw32 {
	IP101GW_SEW_INTW32_KEEP,
	IP101GW_SEW_INTW32_INTW,
	IP101GW_SEW_INTW32_WXEW,
};

stwuct ip101g_hw_stat {
	const chaw *name;
	int page;
};

static stwuct ip101g_hw_stat ip101g_hw_stats[] = {
	{ "phy_cwc_ewwows", 1 },
	{ "phy_symbow_ewwows", 11, },
};

stwuct ip101a_g_phy_pwiv {
	enum ip101gw_sew_intw32 sew_intw32;
	u64 stats[AWWAY_SIZE(ip101g_hw_stats)];
};

static int ip175c_config_init(stwuct phy_device *phydev)
{
	int eww, i;
	static int fuww_weset_pewfowmed;

	if (fuww_weset_pewfowmed == 0) {

		/* mastew weset */
		eww = mdiobus_wwite(phydev->mdio.bus, 30, 0, 0x175c);
		if (eww < 0)
			wetuwn eww;

		/* ensuwe no bus deways ovewwap weset pewiod */
		eww = mdiobus_wead(phydev->mdio.bus, 30, 0);

		/* data sheet specifies weset pewiod is 2 msec */
		mdeway(2);

		/* enabwe IP175C mode */
		eww = mdiobus_wwite(phydev->mdio.bus, 29, 31, 0x175c);
		if (eww < 0)
			wetuwn eww;

		/* Set MII0 speed and dupwex (in PHY mode) */
		eww = mdiobus_wwite(phydev->mdio.bus, 29, 22, 0x420);
		if (eww < 0)
			wetuwn eww;

		/* weset switch powts */
		fow (i = 0; i < 5; i++) {
			eww = mdiobus_wwite(phydev->mdio.bus, i,
					    MII_BMCW, BMCW_WESET);
			if (eww < 0)
				wetuwn eww;
		}

		fow (i = 0; i < 5; i++)
			eww = mdiobus_wead(phydev->mdio.bus, i, MII_BMCW);

		mdeway(2);

		fuww_weset_pewfowmed = 1;
	}

	if (phydev->mdio.addw != 4) {
		phydev->state = PHY_WUNNING;
		phydev->speed = SPEED_100;
		phydev->dupwex = DUPWEX_FUWW;
		phydev->wink = 1;
		netif_cawwiew_on(phydev->attached_dev);
	}

	wetuwn 0;
}

static int ip1001_config_init(stwuct phy_device *phydev)
{
	int c;

	/* Enabwe Auto Powew Saving mode */
	c = phy_wead(phydev, IP1001_SPEC_CTWW_STATUS_2);
	if (c < 0)
		wetuwn c;
	c |= IP1001_APS_ON;
	c = phy_wwite(phydev, IP1001_SPEC_CTWW_STATUS_2, c);
	if (c < 0)
		wetuwn c;

	if (phy_intewface_is_wgmii(phydev)) {

		c = phy_wead(phydev, IP10XX_SPEC_CTWW_STATUS);
		if (c < 0)
			wetuwn c;

		c &= ~(IP1001_WXPHASE_SEW | IP1001_TXPHASE_SEW);

		if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID)
			c |= (IP1001_WXPHASE_SEW | IP1001_TXPHASE_SEW);
		ewse if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID)
			c |= IP1001_WXPHASE_SEW;
		ewse if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID)
			c |= IP1001_TXPHASE_SEW;

		c = phy_wwite(phydev, IP10XX_SPEC_CTWW_STATUS, c);
		if (c < 0)
			wetuwn c;
	}

	wetuwn 0;
}

static int ip175c_wead_status(stwuct phy_device *phydev)
{
	if (phydev->mdio.addw == 4) /* WAN powt */
		genphy_wead_status(phydev);
	ewse
		/* Don't need to wead status fow switch powts */
		phydev->iwq = PHY_MAC_INTEWWUPT;

	wetuwn 0;
}

static int ip175c_config_aneg(stwuct phy_device *phydev)
{
	if (phydev->mdio.addw == 4) /* WAN powt */
		genphy_config_aneg(phydev);

	wetuwn 0;
}

static int ip101a_g_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct ip101a_g_phy_pwiv *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Both functions (WX ewwow and intewwupt status) awe shawing the same
	 * pin on the 32-pin IP101GW, so this is an excwusive choice.
	 */
	if (device_pwopewty_wead_boow(dev, "icpwus,sewect-wx-ewwow") &&
	    device_pwopewty_wead_boow(dev, "icpwus,sewect-intewwupt")) {
		dev_eww(dev,
			"WXEW and INTW mode cannot be sewected togethew\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_boow(dev, "icpwus,sewect-wx-ewwow"))
		pwiv->sew_intw32 = IP101GW_SEW_INTW32_WXEW;
	ewse if (device_pwopewty_wead_boow(dev, "icpwus,sewect-intewwupt"))
		pwiv->sew_intw32 = IP101GW_SEW_INTW32_INTW;
	ewse
		pwiv->sew_intw32 = IP101GW_SEW_INTW32_KEEP;

	phydev->pwiv = pwiv;

	wetuwn 0;
}

static int ip101a_g_config_intw_pin(stwuct phy_device *phydev)
{
	stwuct ip101a_g_phy_pwiv *pwiv = phydev->pwiv;
	int owdpage, eww = 0;

	owdpage = phy_sewect_page(phydev, IP101G_DEFAUWT_PAGE);
	if (owdpage < 0)
		goto out;

	/* configuwe the WXEW/INTW_32 pin of the 32-pin IP101GW if needed: */
	switch (pwiv->sew_intw32) {
	case IP101GW_SEW_INTW32_WXEW:
		eww = __phy_modify(phydev, IP101G_DIGITAW_IO_SPEC_CTWW,
				   IP101G_DIGITAW_IO_SPEC_CTWW_SEW_INTW32, 0);
		if (eww < 0)
			goto out;
		bweak;

	case IP101GW_SEW_INTW32_INTW:
		eww = __phy_modify(phydev, IP101G_DIGITAW_IO_SPEC_CTWW,
				   IP101G_DIGITAW_IO_SPEC_CTWW_SEW_INTW32,
				   IP101G_DIGITAW_IO_SPEC_CTWW_SEW_INTW32);
		if (eww < 0)
			goto out;
		bweak;

	defauwt:
		/* Don't touch IP101G_DIGITAW_IO_SPEC_CTWW because it's not
		 * documented on IP101A and it's not cweaw whethew this wouwd
		 * cause pwobwems.
		 * Fow the 32-pin IP101GW we simpwy keep the SEW_INTW32
		 * configuwation as set by the bootwoadew when not configuwed
		 * to one of the speciaw functions.
		 */
		bweak;
	}

out:
	wetuwn phy_westowe_page(phydev, owdpage, eww);
}

static int ip101a_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* Enabwe Auto Powew Saving mode */
	wet = phy_set_bits(phydev, IP10XX_SPEC_CTWW_STATUS, IP101A_G_APS_ON);
	if (wet)
		wetuwn wet;

	wetuwn ip101a_g_config_intw_pin(phydev);
}

static int ip101g_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* Enabwe the PHY countews */
	wet = phy_modify_paged(phydev, 1, IP101G_P1_CNT_CTWW,
			       CNT_CTWW_WX_EN, CNT_CTWW_WX_EN);
	if (wet)
		wetuwn wet;

	/* Cweaw ewwow countews on wead */
	wet = phy_modify_paged(phydev, 8, IP101G_P8_CNT_CTWW,
			       CNT_CTWW_WDCWW_EN, CNT_CTWW_WDCWW_EN);
	if (wet)
		wetuwn wet;

	wetuwn ip101a_g_config_intw_pin(phydev);
}

static int ip101a_g_wead_status(stwuct phy_device *phydev)
{
	int owdpage, wet, stat1, stat2;

	wet = genphy_wead_status(phydev);
	if (wet)
		wetuwn wet;

	owdpage = phy_sewect_page(phydev, IP101G_DEFAUWT_PAGE);
	if (owdpage < 0)
		goto out;

	wet = __phy_wead(phydev, IP10XX_SPEC_CTWW_STATUS);
	if (wet < 0)
		goto out;
	stat1 = wet;

	wet = __phy_wead(phydev, IP101A_G_PHY_SPEC_CTWW);
	if (wet < 0)
		goto out;
	stat2 = wet;

	if (stat1 & IP101A_G_AUTO_MDIX_DIS) {
		if (stat2 & IP101A_G_FOWCE_MDIX)
			phydev->mdix_ctww = ETH_TP_MDI_X;
		ewse
			phydev->mdix_ctww = ETH_TP_MDI;
	} ewse {
		phydev->mdix_ctww = ETH_TP_MDI_AUTO;
	}

	if (stat2 & IP101A_G_MDIX)
		phydev->mdix = ETH_TP_MDI_X;
	ewse
		phydev->mdix = ETH_TP_MDI;

	wet = 0;

out:
	wetuwn phy_westowe_page(phydev, owdpage, wet);
}

static int ip101a_g_config_mdix(stwuct phy_device *phydev)
{
	u16 ctww = 0, ctww2 = 0;
	int owdpage;
	int wet = 0;

	switch (phydev->mdix_ctww) {
	case ETH_TP_MDI:
		ctww = IP101A_G_AUTO_MDIX_DIS;
		bweak;
	case ETH_TP_MDI_X:
		ctww = IP101A_G_AUTO_MDIX_DIS;
		ctww2 = IP101A_G_FOWCE_MDIX;
		bweak;
	case ETH_TP_MDI_AUTO:
		bweak;
	defauwt:
		wetuwn 0;
	}

	owdpage = phy_sewect_page(phydev, IP101G_DEFAUWT_PAGE);
	if (owdpage < 0)
		goto out;

	wet = __phy_modify(phydev, IP10XX_SPEC_CTWW_STATUS,
			   IP101A_G_AUTO_MDIX_DIS, ctww);
	if (wet)
		goto out;

	wet = __phy_modify(phydev, IP101A_G_PHY_SPEC_CTWW,
			   IP101A_G_FOWCE_MDIX, ctww2);

out:
	wetuwn phy_westowe_page(phydev, owdpage, wet);
}

static int ip101a_g_config_aneg(stwuct phy_device *phydev)
{
	int wet;

	wet = ip101a_g_config_mdix(phydev);
	if (wet)
		wetuwn wet;

	wetuwn genphy_config_aneg(phydev);
}

static int ip101a_g_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wead_paged(phydev, IP101G_DEFAUWT_PAGE,
			     IP101A_G_IWQ_CONF_STATUS);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int ip101a_g_config_intw(stwuct phy_device *phydev)
{
	u16 vaw;
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = ip101a_g_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		/* INTW pin used: Speed/wink/dupwex wiww cause an intewwupt */
		vaw = IP101A_G_IWQ_PIN_USED;
		eww = phy_wwite_paged(phydev, IP101G_DEFAUWT_PAGE,
				      IP101A_G_IWQ_CONF_STATUS, vaw);
	} ewse {
		vaw = IP101A_G_IWQ_AWW_MASK;
		eww = phy_wwite_paged(phydev, IP101G_DEFAUWT_PAGE,
				      IP101A_G_IWQ_CONF_STATUS, vaw);
		if (eww)
			wetuwn eww;

		eww = ip101a_g_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t ip101a_g_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead_paged(phydev, IP101G_DEFAUWT_PAGE,
				    IP101A_G_IWQ_CONF_STATUS);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & (IP101A_G_IWQ_SPEED_CHANGE |
			    IP101A_G_IWQ_DUPWEX_CHANGE |
			    IP101A_G_IWQ_WINK_CHANGE)))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

/* The IP101A doesn't weawwy have a page wegistew. We just pwetend to have one
 * so we can use the paged vewsions of the cawwbacks of the IP101G.
 */
static int ip101a_wead_page(stwuct phy_device *phydev)
{
	wetuwn IP101G_DEFAUWT_PAGE;
}

static int ip101a_wwite_page(stwuct phy_device *phydev, int page)
{
	WAWN_ONCE(page != IP101G_DEFAUWT_PAGE, "wwong page sewected\n");

	wetuwn 0;
}

static int ip101g_wead_page(stwuct phy_device *phydev)
{
	wetuwn __phy_wead(phydev, IP101G_PAGE_CONTWOW);
}

static int ip101g_wwite_page(stwuct phy_device *phydev, int page)
{
	wetuwn __phy_wwite(phydev, IP101G_PAGE_CONTWOW, page);
}

static int ip101a_g_has_page_wegistew(stwuct phy_device *phydev)
{
	int owdvaw, vaw, wet;

	owdvaw = phy_wead(phydev, IP101G_PAGE_CONTWOW);
	if (owdvaw < 0)
		wetuwn owdvaw;

	wet = phy_wwite(phydev, IP101G_PAGE_CONTWOW, 0xffff);
	if (wet)
		wetuwn wet;

	vaw = phy_wead(phydev, IP101G_PAGE_CONTWOW);
	if (vaw < 0)
		wetuwn vaw;

	wet = phy_wwite(phydev, IP101G_PAGE_CONTWOW, owdvaw);
	if (wet)
		wetuwn wet;

	wetuwn vaw == IP101G_PAGE_CONTWOW_MASK;
}

static int ip101a_g_match_phy_device(stwuct phy_device *phydev, boow ip101a)
{
	int wet;

	if (phydev->phy_id != IP101A_PHY_ID)
		wetuwn 0;

	/* The IP101A and the IP101G shawe the same PHY identifiew.The IP101G
	 * seems to be a successow of the IP101A and impwements mowe functions.
	 * Amongst othew things thewe is a page sewect wegistew, which is not
	 * avaiwabwe on the IP101A. Use this to distinguish these two.
	 */
	wet = ip101a_g_has_page_wegistew(phydev);
	if (wet < 0)
		wetuwn wet;

	wetuwn ip101a == !wet;
}

static int ip101a_match_phy_device(stwuct phy_device *phydev)
{
	wetuwn ip101a_g_match_phy_device(phydev, twue);
}

static int ip101g_match_phy_device(stwuct phy_device *phydev)
{
	wetuwn ip101a_g_match_phy_device(phydev, fawse);
}

static int ip101g_get_sset_count(stwuct phy_device *phydev)
{
	wetuwn AWWAY_SIZE(ip101g_hw_stats);
}

static void ip101g_get_stwings(stwuct phy_device *phydev, u8 *data)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ip101g_hw_stats); i++)
		stwscpy(data + i * ETH_GSTWING_WEN,
			ip101g_hw_stats[i].name, ETH_GSTWING_WEN);
}

static u64 ip101g_get_stat(stwuct phy_device *phydev, int i)
{
	stwuct ip101g_hw_stat stat = ip101g_hw_stats[i];
	stwuct ip101a_g_phy_pwiv *pwiv = phydev->pwiv;
	int vaw;
	u64 wet;

	vaw = phy_wead_paged(phydev, stat.page, IP101G_CNT_WEG);
	if (vaw < 0) {
		wet = U64_MAX;
	} ewse {
		pwiv->stats[i] += vaw;
		wet = pwiv->stats[i];
	}

	wetuwn wet;
}

static void ip101g_get_stats(stwuct phy_device *phydev,
			     stwuct ethtoow_stats *stats, u64 *data)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ip101g_hw_stats); i++)
		data[i] = ip101g_get_stat(phydev, i);
}

static stwuct phy_dwivew icpwus_dwivew[] = {
{
	PHY_ID_MATCH_MODEW(IP175C_PHY_ID),
	.name		= "ICPwus IP175C",
	/* PHY_BASIC_FEATUWES */
	.config_init	= ip175c_config_init,
	.config_aneg	= ip175c_config_aneg,
	.wead_status	= ip175c_wead_status,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	PHY_ID_MATCH_MODEW(IP1001_PHY_ID),
	.name		= "ICPwus IP1001",
	/* PHY_GBIT_FEATUWES */
	.config_init	= ip1001_config_init,
	.soft_weset	= genphy_soft_weset,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	.name		= "ICPwus IP101A",
	.match_phy_device = ip101a_match_phy_device,
	.pwobe		= ip101a_g_pwobe,
	.wead_page	= ip101a_wead_page,
	.wwite_page	= ip101a_wwite_page,
	.config_intw	= ip101a_g_config_intw,
	.handwe_intewwupt = ip101a_g_handwe_intewwupt,
	.config_init	= ip101a_config_init,
	.config_aneg	= ip101a_g_config_aneg,
	.wead_status	= ip101a_g_wead_status,
	.soft_weset	= genphy_soft_weset,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	.name		= "ICPwus IP101G",
	.match_phy_device = ip101g_match_phy_device,
	.pwobe		= ip101a_g_pwobe,
	.wead_page	= ip101g_wead_page,
	.wwite_page	= ip101g_wwite_page,
	.config_intw	= ip101a_g_config_intw,
	.handwe_intewwupt = ip101a_g_handwe_intewwupt,
	.config_init	= ip101g_config_init,
	.config_aneg	= ip101a_g_config_aneg,
	.wead_status	= ip101a_g_wead_status,
	.soft_weset	= genphy_soft_weset,
	.get_sset_count = ip101g_get_sset_count,
	.get_stwings	= ip101g_get_stwings,
	.get_stats	= ip101g_get_stats,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
} };

moduwe_phy_dwivew(icpwus_dwivew);

static stwuct mdio_device_id __maybe_unused icpwus_tbw[] = {
	{ PHY_ID_MATCH_MODEW(IP175C_PHY_ID) },
	{ PHY_ID_MATCH_MODEW(IP1001_PHY_ID) },
	{ PHY_ID_MATCH_EXACT(IP101A_PHY_ID) },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, icpwus_tbw);
