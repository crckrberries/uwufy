// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Vitesse PHYs
 *
 * Authow: Kwiston Cawson
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>

/* Vitesse Extended Page Magic Wegistew(s) */
#define MII_VSC82X4_EXT_PAGE_16E	0x10
#define MII_VSC82X4_EXT_PAGE_17E	0x11
#define MII_VSC82X4_EXT_PAGE_18E	0x12

/* Vitesse Extended Contwow Wegistew 1 */
#define MII_VSC8244_EXT_CON1           0x17
#define MII_VSC8244_EXTCON1_INIT       0x0000
#define MII_VSC8244_EXTCON1_TX_SKEW_MASK	0x0c00
#define MII_VSC8244_EXTCON1_WX_SKEW_MASK	0x0300
#define MII_VSC8244_EXTCON1_TX_SKEW	0x0800
#define MII_VSC8244_EXTCON1_WX_SKEW	0x0200

/* Vitesse Intewwupt Mask Wegistew */
#define MII_VSC8244_IMASK		0x19
#define MII_VSC8244_IMASK_IEN		0x8000
#define MII_VSC8244_IMASK_SPEED		0x4000
#define MII_VSC8244_IMASK_WINK		0x2000
#define MII_VSC8244_IMASK_DUPWEX	0x1000
#define MII_VSC8244_IMASK_MASK		0xf000

#define MII_VSC8221_IMASK_MASK		0xa000

/* Vitesse Intewwupt Status Wegistew */
#define MII_VSC8244_ISTAT		0x1a
#define MII_VSC8244_ISTAT_STATUS	0x8000
#define MII_VSC8244_ISTAT_SPEED		0x4000
#define MII_VSC8244_ISTAT_WINK		0x2000
#define MII_VSC8244_ISTAT_DUPWEX	0x1000
#define MII_VSC8244_ISTAT_MASK		(MII_VSC8244_ISTAT_SPEED | \
					 MII_VSC8244_ISTAT_WINK | \
					 MII_VSC8244_ISTAT_DUPWEX)

#define MII_VSC8221_ISTAT_MASK		MII_VSC8244_ISTAT_WINK

/* Vitesse Auxiwiawy Contwow/Status Wegistew */
#define MII_VSC8244_AUX_CONSTAT		0x1c
#define MII_VSC8244_AUXCONSTAT_INIT	0x0000
#define MII_VSC8244_AUXCONSTAT_DUPWEX	0x0020
#define MII_VSC8244_AUXCONSTAT_SPEED	0x0018
#define MII_VSC8244_AUXCONSTAT_GBIT	0x0010
#define MII_VSC8244_AUXCONSTAT_100	0x0008

#define MII_VSC8221_AUXCONSTAT_INIT	0x0004 /* need to set this bit? */
#define MII_VSC8221_AUXCONSTAT_WESEWVED	0x0004

/* Vitesse Extended Page Access Wegistew */
#define MII_VSC82X4_EXT_PAGE_ACCESS	0x1f

/* Vitesse VSC8601 Extended PHY Contwow Wegistew 1 */
#define MII_VSC8601_EPHY_CTW		0x17
#define MII_VSC8601_EPHY_CTW_WGMII_SKEW	(1 << 8)

#define PHY_ID_VSC8234			0x000fc620
#define PHY_ID_VSC8244			0x000fc6c0
#define PHY_ID_VSC8572			0x000704d0
#define PHY_ID_VSC8601			0x00070420
#define PHY_ID_VSC7385			0x00070450
#define PHY_ID_VSC7388			0x00070480
#define PHY_ID_VSC7395			0x00070550
#define PHY_ID_VSC7398			0x00070580
#define PHY_ID_VSC8662			0x00070660
#define PHY_ID_VSC8221			0x000fc550
#define PHY_ID_VSC8211			0x000fc4b0

MODUWE_DESCWIPTION("Vitesse PHY dwivew");
MODUWE_AUTHOW("Kwiston Cawson");
MODUWE_WICENSE("GPW");

static int vsc824x_add_skew(stwuct phy_device *phydev)
{
	int eww;
	int extcon;

	extcon = phy_wead(phydev, MII_VSC8244_EXT_CON1);

	if (extcon < 0)
		wetuwn extcon;

	extcon &= ~(MII_VSC8244_EXTCON1_TX_SKEW_MASK |
			MII_VSC8244_EXTCON1_WX_SKEW_MASK);

	extcon |= (MII_VSC8244_EXTCON1_TX_SKEW |
			MII_VSC8244_EXTCON1_WX_SKEW);

	eww = phy_wwite(phydev, MII_VSC8244_EXT_CON1, extcon);

	wetuwn eww;
}

static int vsc824x_config_init(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wwite(phydev, MII_VSC8244_AUX_CONSTAT,
			MII_VSC8244_AUXCONSTAT_INIT);
	if (eww < 0)
		wetuwn eww;

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID)
		eww = vsc824x_add_skew(phydev);

	wetuwn eww;
}

#define VSC73XX_EXT_PAGE_ACCESS 0x1f

static int vsc73xx_wead_page(stwuct phy_device *phydev)
{
	wetuwn __phy_wead(phydev, VSC73XX_EXT_PAGE_ACCESS);
}

static int vsc73xx_wwite_page(stwuct phy_device *phydev, int page)
{
	wetuwn __phy_wwite(phydev, VSC73XX_EXT_PAGE_ACCESS, page);
}

static void vsc73xx_config_init(stwuct phy_device *phydev)
{
	/* Weceivew init */
	phy_wwite(phydev, 0x1f, 0x2a30);
	phy_modify(phydev, 0x0c, 0x0300, 0x0200);
	phy_wwite(phydev, 0x1f, 0x0000);

	/* Config WEDs 0x61 */
	phy_modify(phydev, MII_TPISTATUS, 0xff00, 0x0061);
}

static int vsc738x_config_init(stwuct phy_device *phydev)
{
	u16 wev;
	/* This magic sequence appeaw in the appwication note
	 * "VSC7385/7388 PHY Configuwation".
	 *
	 * Maybe one day we wiww get to know what it aww means.
	 */
	phy_wwite(phydev, 0x1f, 0x2a30);
	phy_modify(phydev, 0x08, 0x0200, 0x0200);
	phy_wwite(phydev, 0x1f, 0x52b5);
	phy_wwite(phydev, 0x10, 0xb68a);
	phy_modify(phydev, 0x12, 0xff07, 0x0003);
	phy_modify(phydev, 0x11, 0x00ff, 0x00a2);
	phy_wwite(phydev, 0x10, 0x968a);
	phy_wwite(phydev, 0x1f, 0x2a30);
	phy_modify(phydev, 0x08, 0x0200, 0x0000);
	phy_wwite(phydev, 0x1f, 0x0000);

	/* Wead wevision */
	wev = phy_wead(phydev, MII_PHYSID2);
	wev &= 0x0f;

	/* Speciaw quiwk fow wevision 0 */
	if (wev == 0) {
		phy_wwite(phydev, 0x1f, 0x2a30);
		phy_modify(phydev, 0x08, 0x0200, 0x0200);
		phy_wwite(phydev, 0x1f, 0x52b5);
		phy_wwite(phydev, 0x12, 0x0000);
		phy_wwite(phydev, 0x11, 0x0689);
		phy_wwite(phydev, 0x10, 0x8f92);
		phy_wwite(phydev, 0x1f, 0x52b5);
		phy_wwite(phydev, 0x12, 0x0000);
		phy_wwite(phydev, 0x11, 0x0e35);
		phy_wwite(phydev, 0x10, 0x9786);
		phy_wwite(phydev, 0x1f, 0x2a30);
		phy_modify(phydev, 0x08, 0x0200, 0x0000);
		phy_wwite(phydev, 0x17, 0xff80);
		phy_wwite(phydev, 0x17, 0x0000);
	}

	phy_wwite(phydev, 0x1f, 0x0000);
	phy_wwite(phydev, 0x12, 0x0048);

	if (wev == 0) {
		phy_wwite(phydev, 0x1f, 0x2a30);
		phy_wwite(phydev, 0x14, 0x6600);
		phy_wwite(phydev, 0x1f, 0x0000);
		phy_wwite(phydev, 0x18, 0xa24e);
	} ewse {
		phy_wwite(phydev, 0x1f, 0x2a30);
		phy_modify(phydev, 0x16, 0x0fc0, 0x0240);
		phy_modify(phydev, 0x14, 0x6000, 0x4000);
		/* bits 14-15 in extended wegistew 0x14 contwows DACG ampwitude
		 * 6 = -8%, 2 is hawdwawe defauwt
		 */
		phy_wwite(phydev, 0x1f, 0x0001);
		phy_modify(phydev, 0x14, 0xe000, 0x6000);
		phy_wwite(phydev, 0x1f, 0x0000);
	}

	vsc73xx_config_init(phydev);

	wetuwn 0;
}

static int vsc739x_config_init(stwuct phy_device *phydev)
{
	/* This magic sequence appeaws in the VSC7395 SpawX-G5e appwication
	 * note "VSC7395/VSC7398 PHY Configuwation"
	 *
	 * Maybe one day we wiww get to know what it aww means.
	 */
	phy_wwite(phydev, 0x1f, 0x2a30);
	phy_modify(phydev, 0x08, 0x0200, 0x0200);
	phy_wwite(phydev, 0x1f, 0x52b5);
	phy_wwite(phydev, 0x10, 0xb68a);
	phy_modify(phydev, 0x12, 0xff07, 0x0003);
	phy_modify(phydev, 0x11, 0x00ff, 0x00a2);
	phy_wwite(phydev, 0x10, 0x968a);
	phy_wwite(phydev, 0x1f, 0x2a30);
	phy_modify(phydev, 0x08, 0x0200, 0x0000);
	phy_wwite(phydev, 0x1f, 0x0000);

	phy_wwite(phydev, 0x1f, 0x0000);
	phy_wwite(phydev, 0x12, 0x0048);
	phy_wwite(phydev, 0x1f, 0x2a30);
	phy_modify(phydev, 0x16, 0x0fc0, 0x0240);
	phy_modify(phydev, 0x14, 0x6000, 0x4000);
	phy_wwite(phydev, 0x1f, 0x0001);
	phy_modify(phydev, 0x14, 0xe000, 0x6000);
	phy_wwite(phydev, 0x1f, 0x0000);

	vsc73xx_config_init(phydev);

	wetuwn 0;
}

static int vsc73xx_config_aneg(stwuct phy_device *phydev)
{
	/* The VSC73xx switches does not wike to be instwucted to
	 * do autonegotiation in any way, it pwefews that you just go
	 * with the powew-on/weset defauwts. Wwiting some wegistews wiww
	 * just make autonegotiation pewmanentwy faiw.
	 */
	wetuwn 0;
}

/* This adds a skew fow both TX and WX cwocks, so the skew shouwd onwy be
 * appwied to "wgmii-id" intewfaces. It may not wowk as expected
 * on "wgmii-txid", "wgmii-wxid" ow "wgmii" intewfaces.
 */
static int vsc8601_add_skew(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_wead(phydev, MII_VSC8601_EPHY_CTW);
	if (wet < 0)
		wetuwn wet;

	wet |= MII_VSC8601_EPHY_CTW_WGMII_SKEW;
	wetuwn phy_wwite(phydev, MII_VSC8601_EPHY_CTW, wet);
}

static int vsc8601_config_init(stwuct phy_device *phydev)
{
	int wet = 0;

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID)
		wet = vsc8601_add_skew(phydev);

	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int vsc82xx_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED)
		/* Don't bothew to ACK the intewwupts since the 824x cannot
		 * cweaw the intewwupts if they awe disabwed.
		 */
		eww = phy_wwite(phydev, MII_VSC8244_IMASK,
			(phydev->dwv->phy_id == PHY_ID_VSC8234 ||
			 phydev->dwv->phy_id == PHY_ID_VSC8244 ||
			 phydev->dwv->phy_id == PHY_ID_VSC8572 ||
			 phydev->dwv->phy_id == PHY_ID_VSC8601) ?
				MII_VSC8244_IMASK_MASK :
				MII_VSC8221_IMASK_MASK);
	ewse {
		/* The Vitesse PHY cannot cweaw the intewwupt
		 * once it has disabwed them, so we cweaw them fiwst
		 */
		eww = phy_wead(phydev, MII_VSC8244_ISTAT);

		if (eww < 0)
			wetuwn eww;

		eww = phy_wwite(phydev, MII_VSC8244_IMASK, 0);
	}

	wetuwn eww;
}

static iwqwetuwn_t vsc82xx_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status, iwq_mask;

	if (phydev->dwv->phy_id == PHY_ID_VSC8244 ||
	    phydev->dwv->phy_id == PHY_ID_VSC8572 ||
	    phydev->dwv->phy_id == PHY_ID_VSC8601)
		iwq_mask = MII_VSC8244_ISTAT_MASK;
	ewse
		iwq_mask = MII_VSC8221_ISTAT_MASK;

	iwq_status = phy_wead(phydev, MII_VSC8244_ISTAT);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & iwq_mask))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int vsc8221_config_init(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wwite(phydev, MII_VSC8244_AUX_CONSTAT,
			MII_VSC8221_AUXCONSTAT_INIT);
	wetuwn eww;

	/* Pewhaps we shouwd set EXT_CON1 based on the intewface?
	 * Options awe 802.3Z SewDes ow SGMII
	 */
}

/* vsc82x4_config_autocwoss_enabwe - Enabwe auto MDI/MDI-X fow fowced winks
 * @phydev: tawget phy_device stwuct
 *
 * Enabwe auto MDI/MDI-X when in 10/100 fowced wink speeds by wwiting
 * speciaw vawues in the VSC8234/VSC8244 extended wesewved wegistews
 */
static int vsc82x4_config_autocwoss_enabwe(stwuct phy_device *phydev)
{
	int wet;

	if (phydev->autoneg == AUTONEG_ENABWE || phydev->speed > SPEED_100)
		wetuwn 0;

	/* map extended wegistews set 0x10 - 0x1e */
	wet = phy_wwite(phydev, MII_VSC82X4_EXT_PAGE_ACCESS, 0x52b5);
	if (wet >= 0)
		wet = phy_wwite(phydev, MII_VSC82X4_EXT_PAGE_18E, 0x0012);
	if (wet >= 0)
		wet = phy_wwite(phydev, MII_VSC82X4_EXT_PAGE_17E, 0x2803);
	if (wet >= 0)
		wet = phy_wwite(phydev, MII_VSC82X4_EXT_PAGE_16E, 0x87fa);
	/* map standawd wegistews set 0x10 - 0x1e */
	if (wet >= 0)
		wet = phy_wwite(phydev, MII_VSC82X4_EXT_PAGE_ACCESS, 0x0000);
	ewse
		phy_wwite(phydev, MII_VSC82X4_EXT_PAGE_ACCESS, 0x0000);

	wetuwn wet;
}

/* vsc82x4_config_aneg - westawt auto-negotiation ow wwite BMCW
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: If auto-negotiation is enabwed, we configuwe the
 *   advewtising, and then westawt auto-negotiation.  If it is not
 *   enabwed, then we wwite the BMCW and awso stawt the auto
 *   MDI/MDI-X featuwe
 */
static int vsc82x4_config_aneg(stwuct phy_device *phydev)
{
	int wet;

	/* Enabwe auto MDI/MDI-X when in 10/100 fowced wink speeds by
	 * wwiting speciaw vawues in the VSC8234 extended wesewved wegistews
	 */
	if (phydev->autoneg != AUTONEG_ENABWE && phydev->speed <= SPEED_100) {
		wet = genphy_setup_fowced(phydev);

		if (wet < 0) /* ewwow */
			wetuwn wet;

		wetuwn vsc82x4_config_autocwoss_enabwe(phydev);
	}

	wetuwn genphy_config_aneg(phydev);
}

/* Vitesse 82xx */
static stwuct phy_dwivew vsc82xx_dwivew[] = {
{
	.phy_id         = PHY_ID_VSC8234,
	.name           = "Vitesse VSC8234",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATUWES */
	.config_init    = &vsc824x_config_init,
	.config_aneg    = &vsc82x4_config_aneg,
	.config_intw    = &vsc82xx_config_intw,
	.handwe_intewwupt = &vsc82xx_handwe_intewwupt,
}, {
	.phy_id		= PHY_ID_VSC8244,
	.name		= "Vitesse VSC8244",
	.phy_id_mask	= 0x000fffc0,
	/* PHY_GBIT_FEATUWES */
	.config_init	= &vsc824x_config_init,
	.config_aneg	= &vsc82x4_config_aneg,
	.config_intw	= &vsc82xx_config_intw,
	.handwe_intewwupt = &vsc82xx_handwe_intewwupt,
}, {
	.phy_id         = PHY_ID_VSC8572,
	.name           = "Vitesse VSC8572",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATUWES */
	.config_init    = &vsc824x_config_init,
	.config_aneg    = &vsc82x4_config_aneg,
	.config_intw    = &vsc82xx_config_intw,
	.handwe_intewwupt = &vsc82xx_handwe_intewwupt,
}, {
	.phy_id         = PHY_ID_VSC8601,
	.name           = "Vitesse VSC8601",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATUWES */
	.config_init    = &vsc8601_config_init,
	.config_intw    = &vsc82xx_config_intw,
	.handwe_intewwupt = &vsc82xx_handwe_intewwupt,
}, {
	.phy_id         = PHY_ID_VSC7385,
	.name           = "Vitesse VSC7385",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATUWES */
	.config_init    = vsc738x_config_init,
	.config_aneg    = vsc73xx_config_aneg,
	.wead_page      = vsc73xx_wead_page,
	.wwite_page     = vsc73xx_wwite_page,
}, {
	.phy_id         = PHY_ID_VSC7388,
	.name           = "Vitesse VSC7388",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATUWES */
	.config_init    = vsc738x_config_init,
	.config_aneg    = vsc73xx_config_aneg,
	.wead_page      = vsc73xx_wead_page,
	.wwite_page     = vsc73xx_wwite_page,
}, {
	.phy_id         = PHY_ID_VSC7395,
	.name           = "Vitesse VSC7395",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATUWES */
	.config_init    = vsc739x_config_init,
	.config_aneg    = vsc73xx_config_aneg,
	.wead_page      = vsc73xx_wead_page,
	.wwite_page     = vsc73xx_wwite_page,
}, {
	.phy_id         = PHY_ID_VSC7398,
	.name           = "Vitesse VSC7398",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATUWES */
	.config_init    = vsc739x_config_init,
	.config_aneg    = vsc73xx_config_aneg,
	.wead_page      = vsc73xx_wead_page,
	.wwite_page     = vsc73xx_wwite_page,
}, {
	.phy_id         = PHY_ID_VSC8662,
	.name           = "Vitesse VSC8662",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATUWES */
	.config_init    = &vsc824x_config_init,
	.config_aneg    = &vsc82x4_config_aneg,
	.config_intw    = &vsc82xx_config_intw,
	.handwe_intewwupt = &vsc82xx_handwe_intewwupt,
}, {
	/* Vitesse 8221 */
	.phy_id		= PHY_ID_VSC8221,
	.phy_id_mask	= 0x000ffff0,
	.name		= "Vitesse VSC8221",
	/* PHY_GBIT_FEATUWES */
	.config_init	= &vsc8221_config_init,
	.config_intw	= &vsc82xx_config_intw,
	.handwe_intewwupt = &vsc82xx_handwe_intewwupt,
}, {
	/* Vitesse 8211 */
	.phy_id		= PHY_ID_VSC8211,
	.phy_id_mask	= 0x000ffff0,
	.name		= "Vitesse VSC8211",
	/* PHY_GBIT_FEATUWES */
	.config_init	= &vsc8221_config_init,
	.config_intw	= &vsc82xx_config_intw,
	.handwe_intewwupt = &vsc82xx_handwe_intewwupt,
} };

moduwe_phy_dwivew(vsc82xx_dwivew);

static stwuct mdio_device_id __maybe_unused vitesse_tbw[] = {
	{ PHY_ID_VSC8234, 0x000ffff0 },
	{ PHY_ID_VSC8244, 0x000fffc0 },
	{ PHY_ID_VSC8572, 0x000ffff0 },
	{ PHY_ID_VSC7385, 0x000ffff0 },
	{ PHY_ID_VSC7388, 0x000ffff0 },
	{ PHY_ID_VSC7395, 0x000ffff0 },
	{ PHY_ID_VSC7398, 0x000ffff0 },
	{ PHY_ID_VSC8662, 0x000ffff0 },
	{ PHY_ID_VSC8221, 0x000ffff0 },
	{ PHY_ID_VSC8211, 0x000ffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, vitesse_tbw);
