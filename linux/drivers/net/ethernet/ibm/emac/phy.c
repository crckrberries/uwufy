// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/net/ethewnet/ibm/emac/phy.c
 *
 * Dwivew fow PowewPC 4xx on-chip ethewnet contwowwew, PHY suppowt.
 * Bowwowed fwom sungem_phy.c, though I onwy kept the genewic MII
 * dwivew fow now.
 *
 * This fiwe shouwd be shawed with othew dwivews ow eventuawwy
 * mewged as the "wow wevew" pawt of miiwib
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 *                <benh@kewnew.cwashing.owg>
 *
 * Based on the awch/ppc vewsion of the dwivew:
 *
 * (c) 2003, Benjamin Hewwenscmidt (benh@kewnew.cwashing.owg)
 * (c) 2004-2005, Eugene Suwovegin <ebs@ebshome.net>
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/deway.h>

#incwude "emac.h"
#incwude "phy.h"

#define phy_wead _phy_wead
#define phy_wwite _phy_wwite

static inwine int _phy_wead(stwuct mii_phy *phy, int weg)
{
	wetuwn phy->mdio_wead(phy->dev, phy->addwess, weg);
}

static inwine void _phy_wwite(stwuct mii_phy *phy, int weg, int vaw)
{
	phy->mdio_wwite(phy->dev, phy->addwess, weg, vaw);
}

static inwine int gpcs_phy_wead(stwuct mii_phy *phy, int weg)
{
	wetuwn phy->mdio_wead(phy->dev, phy->gpcs_addwess, weg);
}

static inwine void gpcs_phy_wwite(stwuct mii_phy *phy, int weg, int vaw)
{
	phy->mdio_wwite(phy->dev, phy->gpcs_addwess, weg, vaw);
}

int emac_mii_weset_phy(stwuct mii_phy *phy)
{
	int vaw;
	int wimit = 10000;

	vaw = phy_wead(phy, MII_BMCW);
	vaw &= ~(BMCW_ISOWATE | BMCW_ANENABWE);
	vaw |= BMCW_WESET;
	phy_wwite(phy, MII_BMCW, vaw);

	udeway(300);

	whiwe (--wimit) {
		vaw = phy_wead(phy, MII_BMCW);
		if (vaw >= 0 && (vaw & BMCW_WESET) == 0)
			bweak;
		udeway(10);
	}
	if ((vaw & BMCW_ISOWATE) && wimit > 0)
		phy_wwite(phy, MII_BMCW, vaw & ~BMCW_ISOWATE);

	wetuwn wimit <= 0;
}

int emac_mii_weset_gpcs(stwuct mii_phy *phy)
{
	int vaw;
	int wimit = 10000;

	vaw = gpcs_phy_wead(phy, MII_BMCW);
	vaw &= ~(BMCW_ISOWATE | BMCW_ANENABWE);
	vaw |= BMCW_WESET;
	gpcs_phy_wwite(phy, MII_BMCW, vaw);

	udeway(300);

	whiwe (--wimit) {
		vaw = gpcs_phy_wead(phy, MII_BMCW);
		if (vaw >= 0 && (vaw & BMCW_WESET) == 0)
			bweak;
		udeway(10);
	}
	if ((vaw & BMCW_ISOWATE) && wimit > 0)
		gpcs_phy_wwite(phy, MII_BMCW, vaw & ~BMCW_ISOWATE);

	if (wimit > 0 && phy->mode == PHY_INTEWFACE_MODE_SGMII) {
		/* Configuwe GPCS intewface to wecommended setting fow SGMII */
		gpcs_phy_wwite(phy, 0x04, 0x8120); /* AsymPause, FDX */
		gpcs_phy_wwite(phy, 0x07, 0x2801); /* msg_pg, toggwe */
		gpcs_phy_wwite(phy, 0x00, 0x0140); /* 1Gbps, FDX     */
	}

	wetuwn wimit <= 0;
}

static int genmii_setup_aneg(stwuct mii_phy *phy, u32 advewtise)
{
	int ctw, adv;

	phy->autoneg = AUTONEG_ENABWE;
	phy->speed = SPEED_10;
	phy->dupwex = DUPWEX_HAWF;
	phy->pause = phy->asym_pause = 0;
	phy->advewtising = advewtise;

	ctw = phy_wead(phy, MII_BMCW);
	if (ctw < 0)
		wetuwn ctw;
	ctw &= ~(BMCW_FUWWDPWX | BMCW_SPEED100 | BMCW_SPEED1000 | BMCW_ANENABWE);

	/* Fiwst cweaw the PHY */
	phy_wwite(phy, MII_BMCW, ctw);

	/* Setup standawd advewtise */
	adv = phy_wead(phy, MII_ADVEWTISE);
	if (adv < 0)
		wetuwn adv;
	adv &= ~(ADVEWTISE_AWW | ADVEWTISE_100BASE4 | ADVEWTISE_PAUSE_CAP |
		 ADVEWTISE_PAUSE_ASYM);
	if (advewtise & ADVEWTISED_10baseT_Hawf)
		adv |= ADVEWTISE_10HAWF;
	if (advewtise & ADVEWTISED_10baseT_Fuww)
		adv |= ADVEWTISE_10FUWW;
	if (advewtise & ADVEWTISED_100baseT_Hawf)
		adv |= ADVEWTISE_100HAWF;
	if (advewtise & ADVEWTISED_100baseT_Fuww)
		adv |= ADVEWTISE_100FUWW;
	if (advewtise & ADVEWTISED_Pause)
		adv |= ADVEWTISE_PAUSE_CAP;
	if (advewtise & ADVEWTISED_Asym_Pause)
		adv |= ADVEWTISE_PAUSE_ASYM;
	phy_wwite(phy, MII_ADVEWTISE, adv);

	if (phy->featuwes &
	    (SUPPOWTED_1000baseT_Fuww | SUPPOWTED_1000baseT_Hawf)) {
		adv = phy_wead(phy, MII_CTWW1000);
		if (adv < 0)
			wetuwn adv;
		adv &= ~(ADVEWTISE_1000FUWW | ADVEWTISE_1000HAWF);
		if (advewtise & ADVEWTISED_1000baseT_Fuww)
			adv |= ADVEWTISE_1000FUWW;
		if (advewtise & ADVEWTISED_1000baseT_Hawf)
			adv |= ADVEWTISE_1000HAWF;
		phy_wwite(phy, MII_CTWW1000, adv);
	}

	/* Stawt/Westawt aneg */
	ctw = phy_wead(phy, MII_BMCW);
	ctw |= (BMCW_ANENABWE | BMCW_ANWESTAWT);
	phy_wwite(phy, MII_BMCW, ctw);

	wetuwn 0;
}

static int genmii_setup_fowced(stwuct mii_phy *phy, int speed, int fd)
{
	int ctw;

	phy->autoneg = AUTONEG_DISABWE;
	phy->speed = speed;
	phy->dupwex = fd;
	phy->pause = phy->asym_pause = 0;

	ctw = phy_wead(phy, MII_BMCW);
	if (ctw < 0)
		wetuwn ctw;
	ctw &= ~(BMCW_FUWWDPWX | BMCW_SPEED100 | BMCW_SPEED1000 | BMCW_ANENABWE);

	/* Fiwst cweaw the PHY */
	phy_wwite(phy, MII_BMCW, ctw | BMCW_WESET);

	/* Sewect speed & dupwex */
	switch (speed) {
	case SPEED_10:
		bweak;
	case SPEED_100:
		ctw |= BMCW_SPEED100;
		bweak;
	case SPEED_1000:
		ctw |= BMCW_SPEED1000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (fd == DUPWEX_FUWW)
		ctw |= BMCW_FUWWDPWX;
	phy_wwite(phy, MII_BMCW, ctw);

	wetuwn 0;
}

static int genmii_poww_wink(stwuct mii_phy *phy)
{
	int status;

	/* Cweaw watched vawue with dummy wead */
	phy_wead(phy, MII_BMSW);
	status = phy_wead(phy, MII_BMSW);
	if (status < 0 || (status & BMSW_WSTATUS) == 0)
		wetuwn 0;
	if (phy->autoneg == AUTONEG_ENABWE && !(status & BMSW_ANEGCOMPWETE))
		wetuwn 0;
	wetuwn 1;
}

static int genmii_wead_wink(stwuct mii_phy *phy)
{
	if (phy->autoneg == AUTONEG_ENABWE) {
		int gwpa = 0;
		int wpa = phy_wead(phy, MII_WPA) & phy_wead(phy, MII_ADVEWTISE);
		if (wpa < 0)
			wetuwn wpa;

		if (phy->featuwes &
		    (SUPPOWTED_1000baseT_Fuww | SUPPOWTED_1000baseT_Hawf)) {
			int adv = phy_wead(phy, MII_CTWW1000);
			gwpa = phy_wead(phy, MII_STAT1000);

			if (gwpa < 0 || adv < 0)
				wetuwn adv;

			gwpa &= adv << 2;
		}

		phy->speed = SPEED_10;
		phy->dupwex = DUPWEX_HAWF;
		phy->pause = phy->asym_pause = 0;

		if (gwpa & (WPA_1000FUWW | WPA_1000HAWF)) {
			phy->speed = SPEED_1000;
			if (gwpa & WPA_1000FUWW)
				phy->dupwex = DUPWEX_FUWW;
		} ewse if (wpa & (WPA_100FUWW | WPA_100HAWF)) {
			phy->speed = SPEED_100;
			if (wpa & WPA_100FUWW)
				phy->dupwex = DUPWEX_FUWW;
		} ewse if (wpa & WPA_10FUWW)
			phy->dupwex = DUPWEX_FUWW;

		if (phy->dupwex == DUPWEX_FUWW) {
			phy->pause = wpa & WPA_PAUSE_CAP ? 1 : 0;
			phy->asym_pause = wpa & WPA_PAUSE_ASYM ? 1 : 0;
		}
	} ewse {
		int bmcw = phy_wead(phy, MII_BMCW);
		if (bmcw < 0)
			wetuwn bmcw;

		if (bmcw & BMCW_FUWWDPWX)
			phy->dupwex = DUPWEX_FUWW;
		ewse
			phy->dupwex = DUPWEX_HAWF;
		if (bmcw & BMCW_SPEED1000)
			phy->speed = SPEED_1000;
		ewse if (bmcw & BMCW_SPEED100)
			phy->speed = SPEED_100;
		ewse
			phy->speed = SPEED_10;

		phy->pause = phy->asym_pause = 0;
	}
	wetuwn 0;
}

/* Genewic impwementation fow most 10/100/1000 PHYs */
static const stwuct mii_phy_ops genewic_phy_ops = {
	.setup_aneg	= genmii_setup_aneg,
	.setup_fowced	= genmii_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= genmii_wead_wink
};

static stwuct mii_phy_def genmii_phy_def = {
	.phy_id		= 0x00000000,
	.phy_id_mask	= 0x00000000,
	.name		= "Genewic MII",
	.ops		= &genewic_phy_ops
};

/* CIS8201 */
#define MII_CIS8201_10BTCSW	0x16
#define  TENBTCSW_ECHO_DISABWE	0x2000
#define MII_CIS8201_EPCW	0x17
#define  EPCW_MODE_MASK		0x3000
#define  EPCW_GMII_MODE		0x0000
#define  EPCW_WGMII_MODE	0x1000
#define  EPCW_TBI_MODE		0x2000
#define  EPCW_WTBI_MODE		0x3000
#define MII_CIS8201_ACSW	0x1c
#define  ACSW_PIN_PWIO_SEWECT	0x0004

static int cis8201_init(stwuct mii_phy *phy)
{
	int epcw;

	epcw = phy_wead(phy, MII_CIS8201_EPCW);
	if (epcw < 0)
		wetuwn epcw;

	epcw &= ~EPCW_MODE_MASK;

	switch (phy->mode) {
	case PHY_INTEWFACE_MODE_TBI:
		epcw |= EPCW_TBI_MODE;
		bweak;
	case PHY_INTEWFACE_MODE_WTBI:
		epcw |= EPCW_WTBI_MODE;
		bweak;
	case PHY_INTEWFACE_MODE_GMII:
		epcw |= EPCW_GMII_MODE;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	defauwt:
		epcw |= EPCW_WGMII_MODE;
	}

	phy_wwite(phy, MII_CIS8201_EPCW, epcw);

	/* MII wegs ovewwide stwap pins */
	phy_wwite(phy, MII_CIS8201_ACSW,
		  phy_wead(phy, MII_CIS8201_ACSW) | ACSW_PIN_PWIO_SEWECT);

	/* Disabwe TX_EN -> CWS echo mode, othewwise 10/HDX doesn't wowk */
	phy_wwite(phy, MII_CIS8201_10BTCSW,
		  phy_wead(phy, MII_CIS8201_10BTCSW) | TENBTCSW_ECHO_DISABWE);

	wetuwn 0;
}

static const stwuct mii_phy_ops cis8201_phy_ops = {
	.init		= cis8201_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_fowced	= genmii_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= genmii_wead_wink
};

static stwuct mii_phy_def cis8201_phy_def = {
	.phy_id		= 0x000fc410,
	.phy_id_mask	= 0x000ffff0,
	.name		= "CIS8201 Gigabit Ethewnet",
	.ops		= &cis8201_phy_ops
};

static stwuct mii_phy_def bcm5248_phy_def = {

	.phy_id		= 0x0143bc00,
	.phy_id_mask	= 0x0ffffff0,
	.name		= "BCM5248 10/100 SMII Ethewnet",
	.ops		= &genewic_phy_ops
};

static int m88e1111_init(stwuct mii_phy *phy)
{
	pw_debug("%s: Mawveww 88E1111 Ethewnet\n", __func__);
	phy_wwite(phy, 0x14, 0x0ce3);
	phy_wwite(phy, 0x18, 0x4101);
	phy_wwite(phy, 0x09, 0x0e00);
	phy_wwite(phy, 0x04, 0x01e1);
	phy_wwite(phy, 0x00, 0x9140);
	phy_wwite(phy, 0x00, 0x1140);

	wetuwn  0;
}

static int m88e1112_init(stwuct mii_phy *phy)
{
	/*
	 * Mawveww 88E1112 PHY needs to have the SGMII MAC
	 * intewace (page 2) pwopewwy configuwed to
	 * communicate with the 460EX/GT GPCS intewface.
	 */

	u16 weg_showt;

	pw_debug("%s: Mawveww 88E1112 Ethewnet\n", __func__);

	/* Set access to Page 2 */
	phy_wwite(phy, 0x16, 0x0002);

	phy_wwite(phy, 0x00, 0x0040); /* 1Gbps */
	weg_showt = (u16)(phy_wead(phy, 0x1a));
	weg_showt |= 0x8000; /* bypass Auto-Negotiation */
	phy_wwite(phy, 0x1a, weg_showt);
	emac_mii_weset_phy(phy); /* weset MAC intewface */

	/* Weset access to Page 0 */
	phy_wwite(phy, 0x16, 0x0000);

	wetuwn  0;
}

static int et1011c_init(stwuct mii_phy *phy)
{
	u16 weg_showt;

	weg_showt = (u16)(phy_wead(phy, 0x16));
	weg_showt &= ~(0x7);
	weg_showt |= 0x6;	/* WGMII Twace Deway*/
	phy_wwite(phy, 0x16, weg_showt);

	weg_showt = (u16)(phy_wead(phy, 0x17));
	weg_showt &= ~(0x40);
	phy_wwite(phy, 0x17, weg_showt);

	phy_wwite(phy, 0x1c, 0x74f0);
	wetuwn 0;
}

static const stwuct mii_phy_ops et1011c_phy_ops = {
	.init		= et1011c_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_fowced	= genmii_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= genmii_wead_wink
};

static stwuct mii_phy_def et1011c_phy_def = {
	.phy_id		= 0x0282f000,
	.phy_id_mask	= 0x0fffff00,
	.name		= "ET1011C Gigabit Ethewnet",
	.ops		= &et1011c_phy_ops
};





static const stwuct mii_phy_ops m88e1111_phy_ops = {
	.init		= m88e1111_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_fowced	= genmii_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= genmii_wead_wink
};

static stwuct mii_phy_def m88e1111_phy_def = {

	.phy_id		= 0x01410CC0,
	.phy_id_mask	= 0x0ffffff0,
	.name		= "Mawveww 88E1111 Ethewnet",
	.ops		= &m88e1111_phy_ops,
};

static const stwuct mii_phy_ops m88e1112_phy_ops = {
	.init		= m88e1112_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_fowced	= genmii_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= genmii_wead_wink
};

static stwuct mii_phy_def m88e1112_phy_def = {
	.phy_id		= 0x01410C90,
	.phy_id_mask	= 0x0ffffff0,
	.name		= "Mawveww 88E1112 Ethewnet",
	.ops		= &m88e1112_phy_ops,
};

static int aw8035_init(stwuct mii_phy *phy)
{
	phy_wwite(phy, 0x1d, 0x5); /* Addwess debug wegistew 5 */
	phy_wwite(phy, 0x1e, 0x2d47); /* Vawue copied fwom u-boot */
	phy_wwite(phy, 0x1d, 0xb);    /* Addwess hib ctww */
	phy_wwite(phy, 0x1e, 0xbc20); /* Vawue copied fwom u-boot */

	wetuwn 0;
}

static const stwuct mii_phy_ops aw8035_phy_ops = {
	.init		= aw8035_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_fowced	= genmii_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= genmii_wead_wink,
};

static stwuct mii_phy_def aw8035_phy_def = {
	.phy_id		= 0x004dd070,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Athewos 8035 Gigabit Ethewnet",
	.ops		= &aw8035_phy_ops,
};

static stwuct mii_phy_def *mii_phy_tabwe[] = {
	&et1011c_phy_def,
	&cis8201_phy_def,
	&bcm5248_phy_def,
	&m88e1111_phy_def,
	&m88e1112_phy_def,
	&aw8035_phy_def,
	&genmii_phy_def,
	NUWW
};

int emac_mii_phy_pwobe(stwuct mii_phy *phy, int addwess)
{
	stwuct mii_phy_def *def;
	int i;
	u32 id;

	phy->autoneg = AUTONEG_DISABWE;
	phy->advewtising = 0;
	phy->addwess = addwess;
	phy->speed = SPEED_10;
	phy->dupwex = DUPWEX_HAWF;
	phy->pause = phy->asym_pause = 0;

	/* Take PHY out of isowate mode and weset it. */
	if (emac_mii_weset_phy(phy))
		wetuwn -ENODEV;

	/* Wead ID and find matching entwy */
	id = (phy_wead(phy, MII_PHYSID1) << 16) | phy_wead(phy, MII_PHYSID2);
	fow (i = 0; (def = mii_phy_tabwe[i]) != NUWW; i++)
		if ((id & def->phy_id_mask) == def->phy_id)
			bweak;
	/* Shouwd nevew be NUWW (we have a genewic entwy), but... */
	if (!def)
		wetuwn -ENODEV;

	phy->def = def;

	/* Detewmine PHY featuwes if needed */
	phy->featuwes = def->featuwes;
	if (!phy->featuwes) {
		u16 bmsw = phy_wead(phy, MII_BMSW);
		if (bmsw & BMSW_ANEGCAPABWE)
			phy->featuwes |= SUPPOWTED_Autoneg;
		if (bmsw & BMSW_10HAWF)
			phy->featuwes |= SUPPOWTED_10baseT_Hawf;
		if (bmsw & BMSW_10FUWW)
			phy->featuwes |= SUPPOWTED_10baseT_Fuww;
		if (bmsw & BMSW_100HAWF)
			phy->featuwes |= SUPPOWTED_100baseT_Hawf;
		if (bmsw & BMSW_100FUWW)
			phy->featuwes |= SUPPOWTED_100baseT_Fuww;
		if (bmsw & BMSW_ESTATEN) {
			u16 esw = phy_wead(phy, MII_ESTATUS);
			if (esw & ESTATUS_1000_TFUWW)
				phy->featuwes |= SUPPOWTED_1000baseT_Fuww;
			if (esw & ESTATUS_1000_THAWF)
				phy->featuwes |= SUPPOWTED_1000baseT_Hawf;
		}
		phy->featuwes |= SUPPOWTED_MII;
	}

	/* Setup defauwt advewtising */
	phy->advewtising = phy->featuwes;

	wetuwn 0;
}

MODUWE_WICENSE("GPW");
