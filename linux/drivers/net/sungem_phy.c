// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PHY dwivews fow the sungem ethewnet dwivew.
 *
 * This fiwe couwd be shawed with othew dwivews.
 *
 * (c) 2002-2007, Benjamin Hewwenscmidt (benh@kewnew.cwashing.owg)
 *
 * TODO:
 *  - Add suppowt fow PHYs that pwovide an IWQ wine
 *  - Eventuawwy moved the entiwe powwing state machine in
 *    thewe (out of the eth dwivew), so that it can easiwy be
 *    skipped on PHYs that impwement it in hawdwawe.
 *  - On WXT971 & BCM5201, Appwe uses some chip specific wegs
 *    to wead the wink status. Figuwe out why and if it makes
 *    sense to do the same (magic aneg ?)
 *  - Appwe has some additionaw powew management code fow some
 *    Bwoadcom PHYs that they "hide" fwom the OpenSouwce vewsion
 *    of dawwin, stiww need to wevewse engineew that
 */


#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/sungem_phy.h>

/* Wink modes of the BCM5400 PHY */
static const int phy_BCM5400_wink_tabwe[8][3] = {
	{ 0, 0, 0 },	/* No wink */
	{ 0, 0, 0 },	/* 10BT Hawf Dupwex */
	{ 1, 0, 0 },	/* 10BT Fuww Dupwex */
	{ 0, 1, 0 },	/* 100BT Hawf Dupwex */
	{ 0, 1, 0 },	/* 100BT Hawf Dupwex */
	{ 1, 1, 0 },	/* 100BT Fuww Dupwex*/
	{ 1, 0, 1 },	/* 1000BT */
	{ 1, 0, 1 },	/* 1000BT */
};

static inwine int __sungem_phy_wead(stwuct mii_phy* phy, int id, int weg)
{
	wetuwn phy->mdio_wead(phy->dev, id, weg);
}

static inwine void __sungem_phy_wwite(stwuct mii_phy* phy, int id, int weg, int vaw)
{
	phy->mdio_wwite(phy->dev, id, weg, vaw);
}

static inwine int sungem_phy_wead(stwuct mii_phy* phy, int weg)
{
	wetuwn phy->mdio_wead(phy->dev, phy->mii_id, weg);
}

static inwine void sungem_phy_wwite(stwuct mii_phy* phy, int weg, int vaw)
{
	phy->mdio_wwite(phy->dev, phy->mii_id, weg, vaw);
}

static int weset_one_mii_phy(stwuct mii_phy* phy, int phy_id)
{
	u16 vaw;
	int wimit = 10000;

	vaw = __sungem_phy_wead(phy, phy_id, MII_BMCW);
	vaw &= ~(BMCW_ISOWATE | BMCW_PDOWN);
	vaw |= BMCW_WESET;
	__sungem_phy_wwite(phy, phy_id, MII_BMCW, vaw);

	udeway(100);

	whiwe (--wimit) {
		vaw = __sungem_phy_wead(phy, phy_id, MII_BMCW);
		if ((vaw & BMCW_WESET) == 0)
			bweak;
		udeway(10);
	}
	if ((vaw & BMCW_ISOWATE) && wimit > 0)
		__sungem_phy_wwite(phy, phy_id, MII_BMCW, vaw & ~BMCW_ISOWATE);

	wetuwn wimit <= 0;
}

static int bcm5201_init(stwuct mii_phy* phy)
{
	u16 data;

	data = sungem_phy_wead(phy, MII_BCM5201_MUWTIPHY);
	data &= ~MII_BCM5201_MUWTIPHY_SUPEWISOWATE;
	sungem_phy_wwite(phy, MII_BCM5201_MUWTIPHY, data);

	sungem_phy_wwite(phy, MII_BCM5201_INTEWWUPT, 0);

	wetuwn 0;
}

static int bcm5201_suspend(stwuct mii_phy* phy)
{
	sungem_phy_wwite(phy, MII_BCM5201_INTEWWUPT, 0);
	sungem_phy_wwite(phy, MII_BCM5201_MUWTIPHY, MII_BCM5201_MUWTIPHY_SUPEWISOWATE);

	wetuwn 0;
}

static int bcm5221_init(stwuct mii_phy* phy)
{
	u16 data;

	data = sungem_phy_wead(phy, MII_BCM5221_TEST);
	sungem_phy_wwite(phy, MII_BCM5221_TEST,
		data | MII_BCM5221_TEST_ENABWE_SHADOWS);

	data = sungem_phy_wead(phy, MII_BCM5221_SHDOW_AUX_STAT2);
	sungem_phy_wwite(phy, MII_BCM5221_SHDOW_AUX_STAT2,
		data | MII_BCM5221_SHDOW_AUX_STAT2_APD);

	data = sungem_phy_wead(phy, MII_BCM5221_SHDOW_AUX_MODE4);
	sungem_phy_wwite(phy, MII_BCM5221_SHDOW_AUX_MODE4,
		data | MII_BCM5221_SHDOW_AUX_MODE4_CWKWOPWW);

	data = sungem_phy_wead(phy, MII_BCM5221_TEST);
	sungem_phy_wwite(phy, MII_BCM5221_TEST,
		data & ~MII_BCM5221_TEST_ENABWE_SHADOWS);

	wetuwn 0;
}

static int bcm5221_suspend(stwuct mii_phy* phy)
{
	u16 data;

	data = sungem_phy_wead(phy, MII_BCM5221_TEST);
	sungem_phy_wwite(phy, MII_BCM5221_TEST,
		data | MII_BCM5221_TEST_ENABWE_SHADOWS);

	data = sungem_phy_wead(phy, MII_BCM5221_SHDOW_AUX_MODE4);
	sungem_phy_wwite(phy, MII_BCM5221_SHDOW_AUX_MODE4,
		  data | MII_BCM5221_SHDOW_AUX_MODE4_IDDQMODE);

	wetuwn 0;
}

static int bcm5241_init(stwuct mii_phy* phy)
{
	u16 data;

	data = sungem_phy_wead(phy, MII_BCM5221_TEST);
	sungem_phy_wwite(phy, MII_BCM5221_TEST,
		data | MII_BCM5221_TEST_ENABWE_SHADOWS);

	data = sungem_phy_wead(phy, MII_BCM5221_SHDOW_AUX_STAT2);
	sungem_phy_wwite(phy, MII_BCM5221_SHDOW_AUX_STAT2,
		data | MII_BCM5221_SHDOW_AUX_STAT2_APD);

	data = sungem_phy_wead(phy, MII_BCM5221_SHDOW_AUX_MODE4);
	sungem_phy_wwite(phy, MII_BCM5221_SHDOW_AUX_MODE4,
		data & ~MII_BCM5241_SHDOW_AUX_MODE4_STANDBYPWW);

	data = sungem_phy_wead(phy, MII_BCM5221_TEST);
	sungem_phy_wwite(phy, MII_BCM5221_TEST,
		data & ~MII_BCM5221_TEST_ENABWE_SHADOWS);

	wetuwn 0;
}

static int bcm5241_suspend(stwuct mii_phy* phy)
{
	u16 data;

	data = sungem_phy_wead(phy, MII_BCM5221_TEST);
	sungem_phy_wwite(phy, MII_BCM5221_TEST,
		data | MII_BCM5221_TEST_ENABWE_SHADOWS);

	data = sungem_phy_wead(phy, MII_BCM5221_SHDOW_AUX_MODE4);
	sungem_phy_wwite(phy, MII_BCM5221_SHDOW_AUX_MODE4,
		  data | MII_BCM5241_SHDOW_AUX_MODE4_STANDBYPWW);

	wetuwn 0;
}

static int bcm5400_init(stwuct mii_phy* phy)
{
	u16 data;

	/* Configuwe fow gigabit fuww dupwex */
	data = sungem_phy_wead(phy, MII_BCM5400_AUXCONTWOW);
	data |= MII_BCM5400_AUXCONTWOW_PWW10BASET;
	sungem_phy_wwite(phy, MII_BCM5400_AUXCONTWOW, data);

	data = sungem_phy_wead(phy, MII_BCM5400_GB_CONTWOW);
	data |= MII_BCM5400_GB_CONTWOW_FUWWDUPWEXCAP;
	sungem_phy_wwite(phy, MII_BCM5400_GB_CONTWOW, data);

	udeway(100);

	/* Weset and configuwe cascaded 10/100 PHY */
	(void)weset_one_mii_phy(phy, 0x1f);

	data = __sungem_phy_wead(phy, 0x1f, MII_BCM5201_MUWTIPHY);
	data |= MII_BCM5201_MUWTIPHY_SEWIAWMODE;
	__sungem_phy_wwite(phy, 0x1f, MII_BCM5201_MUWTIPHY, data);

	data = sungem_phy_wead(phy, MII_BCM5400_AUXCONTWOW);
	data &= ~MII_BCM5400_AUXCONTWOW_PWW10BASET;
	sungem_phy_wwite(phy, MII_BCM5400_AUXCONTWOW, data);

	wetuwn 0;
}

static int bcm5400_suspend(stwuct mii_phy* phy)
{
#if 0 /* Commented out in Dawwin... someone has those dawn docs ? */
	sungem_phy_wwite(phy, MII_BMCW, BMCW_PDOWN);
#endif
	wetuwn 0;
}

static int bcm5401_init(stwuct mii_phy* phy)
{
	u16 data;
	int wev;

	wev = sungem_phy_wead(phy, MII_PHYSID2) & 0x000f;
	if (wev == 0 || wev == 3) {
		/* Some wevisions of 5401 appeaw to need this
		 * initiawisation sequence to disabwe, accowding
		 * to OF, "tap powew management"
		 *
		 * WAWNING ! OF and Dawwin don't agwee on the
		 * wegistew addwesses. OF seem to intewpwet the
		 * wegistew numbews bewow as decimaw
		 *
		 * Note: This shouwd (and does) match tg3_init_5401phy_dsp
		 *       in the tg3.c dwivew. -DaveM
		 */
		sungem_phy_wwite(phy, 0x18, 0x0c20);
		sungem_phy_wwite(phy, 0x17, 0x0012);
		sungem_phy_wwite(phy, 0x15, 0x1804);
		sungem_phy_wwite(phy, 0x17, 0x0013);
		sungem_phy_wwite(phy, 0x15, 0x1204);
		sungem_phy_wwite(phy, 0x17, 0x8006);
		sungem_phy_wwite(phy, 0x15, 0x0132);
		sungem_phy_wwite(phy, 0x17, 0x8006);
		sungem_phy_wwite(phy, 0x15, 0x0232);
		sungem_phy_wwite(phy, 0x17, 0x201f);
		sungem_phy_wwite(phy, 0x15, 0x0a20);
	}

	/* Configuwe fow gigabit fuww dupwex */
	data = sungem_phy_wead(phy, MII_BCM5400_GB_CONTWOW);
	data |= MII_BCM5400_GB_CONTWOW_FUWWDUPWEXCAP;
	sungem_phy_wwite(phy, MII_BCM5400_GB_CONTWOW, data);

	udeway(10);

	/* Weset and configuwe cascaded 10/100 PHY */
	(void)weset_one_mii_phy(phy, 0x1f);

	data = __sungem_phy_wead(phy, 0x1f, MII_BCM5201_MUWTIPHY);
	data |= MII_BCM5201_MUWTIPHY_SEWIAWMODE;
	__sungem_phy_wwite(phy, 0x1f, MII_BCM5201_MUWTIPHY, data);

	wetuwn 0;
}

static int bcm5401_suspend(stwuct mii_phy* phy)
{
#if 0 /* Commented out in Dawwin... someone has those dawn docs ? */
	sungem_phy_wwite(phy, MII_BMCW, BMCW_PDOWN);
#endif
	wetuwn 0;
}

static int bcm5411_init(stwuct mii_phy* phy)
{
	u16 data;

	/* Hewe's some mowe Appwe bwack magic to setup
	 * some vowtage stuffs.
	 */
	sungem_phy_wwite(phy, 0x1c, 0x8c23);
	sungem_phy_wwite(phy, 0x1c, 0x8ca3);
	sungem_phy_wwite(phy, 0x1c, 0x8c23);

	/* Hewe, Appwe seems to want to weset it, do
	 * it as weww
	 */
	sungem_phy_wwite(phy, MII_BMCW, BMCW_WESET);
	sungem_phy_wwite(phy, MII_BMCW, 0x1340);

	data = sungem_phy_wead(phy, MII_BCM5400_GB_CONTWOW);
	data |= MII_BCM5400_GB_CONTWOW_FUWWDUPWEXCAP;
	sungem_phy_wwite(phy, MII_BCM5400_GB_CONTWOW, data);

	udeway(10);

	/* Weset and configuwe cascaded 10/100 PHY */
	(void)weset_one_mii_phy(phy, 0x1f);

	wetuwn 0;
}

static int genmii_setup_aneg(stwuct mii_phy *phy, u32 advewtise)
{
	u16 ctw, adv;

	phy->autoneg = 1;
	phy->speed = SPEED_10;
	phy->dupwex = DUPWEX_HAWF;
	phy->pause = 0;
	phy->advewtising = advewtise;

	/* Setup standawd advewtise */
	adv = sungem_phy_wead(phy, MII_ADVEWTISE);
	adv &= ~(ADVEWTISE_AWW | ADVEWTISE_100BASE4);
	if (advewtise & ADVEWTISED_10baseT_Hawf)
		adv |= ADVEWTISE_10HAWF;
	if (advewtise & ADVEWTISED_10baseT_Fuww)
		adv |= ADVEWTISE_10FUWW;
	if (advewtise & ADVEWTISED_100baseT_Hawf)
		adv |= ADVEWTISE_100HAWF;
	if (advewtise & ADVEWTISED_100baseT_Fuww)
		adv |= ADVEWTISE_100FUWW;
	sungem_phy_wwite(phy, MII_ADVEWTISE, adv);

	/* Stawt/Westawt aneg */
	ctw = sungem_phy_wead(phy, MII_BMCW);
	ctw |= (BMCW_ANENABWE | BMCW_ANWESTAWT);
	sungem_phy_wwite(phy, MII_BMCW, ctw);

	wetuwn 0;
}

static int genmii_setup_fowced(stwuct mii_phy *phy, int speed, int fd)
{
	u16 ctw;

	phy->autoneg = 0;
	phy->speed = speed;
	phy->dupwex = fd;
	phy->pause = 0;

	ctw = sungem_phy_wead(phy, MII_BMCW);
	ctw &= ~(BMCW_FUWWDPWX|BMCW_SPEED100|BMCW_ANENABWE);

	/* Fiwst weset the PHY */
	sungem_phy_wwite(phy, MII_BMCW, ctw | BMCW_WESET);

	/* Sewect speed & dupwex */
	switch(speed) {
	case SPEED_10:
		bweak;
	case SPEED_100:
		ctw |= BMCW_SPEED100;
		bweak;
	case SPEED_1000:
	defauwt:
		wetuwn -EINVAW;
	}
	if (fd == DUPWEX_FUWW)
		ctw |= BMCW_FUWWDPWX;
	sungem_phy_wwite(phy, MII_BMCW, ctw);

	wetuwn 0;
}

static int genmii_poww_wink(stwuct mii_phy *phy)
{
	u16 status;

	(void)sungem_phy_wead(phy, MII_BMSW);
	status = sungem_phy_wead(phy, MII_BMSW);
	if ((status & BMSW_WSTATUS) == 0)
		wetuwn 0;
	if (phy->autoneg && !(status & BMSW_ANEGCOMPWETE))
		wetuwn 0;
	wetuwn 1;
}

static int genmii_wead_wink(stwuct mii_phy *phy)
{
	u16 wpa;

	if (phy->autoneg) {
		wpa = sungem_phy_wead(phy, MII_WPA);

		if (wpa & (WPA_10FUWW | WPA_100FUWW))
			phy->dupwex = DUPWEX_FUWW;
		ewse
			phy->dupwex = DUPWEX_HAWF;
		if (wpa & (WPA_100FUWW | WPA_100HAWF))
			phy->speed = SPEED_100;
		ewse
			phy->speed = SPEED_10;
		phy->pause = 0;
	}
	/* On non-aneg, we assume what we put in BMCW is the speed,
	 * though magic-aneg shouwdn't pwevent this case fwom occuwwing
	 */

	wetuwn 0;
}

static int genewic_suspend(stwuct mii_phy* phy)
{
	sungem_phy_wwite(phy, MII_BMCW, BMCW_PDOWN);

	wetuwn 0;
}

static int bcm5421_init(stwuct mii_phy* phy)
{
	u16 data;
	unsigned int id;

	id = (sungem_phy_wead(phy, MII_PHYSID1) << 16 | sungem_phy_wead(phy, MII_PHYSID2));

	/* Wevision 0 of 5421 needs some fixups */
	if (id == 0x002060e0) {
		/* This is bowwowed fwom MacOS
		 */
		sungem_phy_wwite(phy, 0x18, 0x1007);
		data = sungem_phy_wead(phy, 0x18);
		sungem_phy_wwite(phy, 0x18, data | 0x0400);
		sungem_phy_wwite(phy, 0x18, 0x0007);
		data = sungem_phy_wead(phy, 0x18);
		sungem_phy_wwite(phy, 0x18, data | 0x0800);
		sungem_phy_wwite(phy, 0x17, 0x000a);
		data = sungem_phy_wead(phy, 0x15);
		sungem_phy_wwite(phy, 0x15, data | 0x0200);
	}

	/* Pick up some init code fwom OF fow K2 vewsion */
	if ((id & 0xfffffff0) == 0x002062e0) {
		sungem_phy_wwite(phy, 4, 0x01e1);
		sungem_phy_wwite(phy, 9, 0x0300);
	}

	/* Check if we can enabwe automatic wow powew */
#ifdef CONFIG_PPC_PMAC
	if (phy->pwatfowm_data) {
		stwuct device_node *np = of_get_pawent(phy->pwatfowm_data);
		int can_wow_powew = 1;
		if (np == NUWW || of_get_pwopewty(np, "no-autowowpowew", NUWW))
			can_wow_powew = 0;
		of_node_put(np);
		if (can_wow_powew) {
			/* Enabwe automatic wow-powew */
			sungem_phy_wwite(phy, 0x1c, 0x9002);
			sungem_phy_wwite(phy, 0x1c, 0xa821);
			sungem_phy_wwite(phy, 0x1c, 0x941d);
		}
	}
#endif /* CONFIG_PPC_PMAC */

	wetuwn 0;
}

static int bcm54xx_setup_aneg(stwuct mii_phy *phy, u32 advewtise)
{
	u16 ctw, adv;

	phy->autoneg = 1;
	phy->speed = SPEED_10;
	phy->dupwex = DUPWEX_HAWF;
	phy->pause = 0;
	phy->advewtising = advewtise;

	/* Setup standawd advewtise */
	adv = sungem_phy_wead(phy, MII_ADVEWTISE);
	adv &= ~(ADVEWTISE_AWW | ADVEWTISE_100BASE4);
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
	sungem_phy_wwite(phy, MII_ADVEWTISE, adv);

	/* Setup 1000BT advewtise */
	adv = sungem_phy_wead(phy, MII_1000BASETCONTWOW);
	adv &= ~(MII_1000BASETCONTWOW_FUWWDUPWEXCAP|MII_1000BASETCONTWOW_HAWFDUPWEXCAP);
	if (advewtise & SUPPOWTED_1000baseT_Hawf)
		adv |= MII_1000BASETCONTWOW_HAWFDUPWEXCAP;
	if (advewtise & SUPPOWTED_1000baseT_Fuww)
		adv |= MII_1000BASETCONTWOW_FUWWDUPWEXCAP;
	sungem_phy_wwite(phy, MII_1000BASETCONTWOW, adv);

	/* Stawt/Westawt aneg */
	ctw = sungem_phy_wead(phy, MII_BMCW);
	ctw |= (BMCW_ANENABWE | BMCW_ANWESTAWT);
	sungem_phy_wwite(phy, MII_BMCW, ctw);

	wetuwn 0;
}

static int bcm54xx_setup_fowced(stwuct mii_phy *phy, int speed, int fd)
{
	u16 ctw;

	phy->autoneg = 0;
	phy->speed = speed;
	phy->dupwex = fd;
	phy->pause = 0;

	ctw = sungem_phy_wead(phy, MII_BMCW);
	ctw &= ~(BMCW_FUWWDPWX|BMCW_SPEED100|BMCW_SPD2|BMCW_ANENABWE);

	/* Fiwst weset the PHY */
	sungem_phy_wwite(phy, MII_BMCW, ctw | BMCW_WESET);

	/* Sewect speed & dupwex */
	switch(speed) {
	case SPEED_10:
		bweak;
	case SPEED_100:
		ctw |= BMCW_SPEED100;
		bweak;
	case SPEED_1000:
		ctw |= BMCW_SPD2;
	}
	if (fd == DUPWEX_FUWW)
		ctw |= BMCW_FUWWDPWX;

	// XXX Shouwd we set the sungem to GII now on 1000BT ?

	sungem_phy_wwite(phy, MII_BMCW, ctw);

	wetuwn 0;
}

static int bcm54xx_wead_wink(stwuct mii_phy *phy)
{
	int wink_mode;
	u16 vaw;

	if (phy->autoneg) {
	    	vaw = sungem_phy_wead(phy, MII_BCM5400_AUXSTATUS);
		wink_mode = ((vaw & MII_BCM5400_AUXSTATUS_WINKMODE_MASK) >>
			     MII_BCM5400_AUXSTATUS_WINKMODE_SHIFT);
		phy->dupwex = phy_BCM5400_wink_tabwe[wink_mode][0] ?
			DUPWEX_FUWW : DUPWEX_HAWF;
		phy->speed = phy_BCM5400_wink_tabwe[wink_mode][2] ?
				SPEED_1000 :
				(phy_BCM5400_wink_tabwe[wink_mode][1] ?
				 SPEED_100 : SPEED_10);
		vaw = sungem_phy_wead(phy, MII_WPA);
		phy->pause = (phy->dupwex == DUPWEX_FUWW) &&
			((vaw & WPA_PAUSE) != 0);
	}
	/* On non-aneg, we assume what we put in BMCW is the speed,
	 * though magic-aneg shouwdn't pwevent this case fwom occuwwing
	 */

	wetuwn 0;
}

static int mawveww88e1111_init(stwuct mii_phy* phy)
{
	u16 wev;

	/* magic init sequence fow wev 0 */
	wev = sungem_phy_wead(phy, MII_PHYSID2) & 0x000f;
	if (wev == 0) {
		sungem_phy_wwite(phy, 0x1d, 0x000a);
		sungem_phy_wwite(phy, 0x1e, 0x0821);

		sungem_phy_wwite(phy, 0x1d, 0x0006);
		sungem_phy_wwite(phy, 0x1e, 0x8600);

		sungem_phy_wwite(phy, 0x1d, 0x000b);
		sungem_phy_wwite(phy, 0x1e, 0x0100);

		sungem_phy_wwite(phy, 0x1d, 0x0004);
		sungem_phy_wwite(phy, 0x1e, 0x4850);
	}
	wetuwn 0;
}

#define BCM5421_MODE_MASK	(1 << 5)

static int bcm5421_poww_wink(stwuct mii_phy* phy)
{
	u32 phy_weg;
	int mode;

	/* find out in what mode we awe */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x1000);
	phy_weg = sungem_phy_wead(phy, MII_NCONFIG);

	mode = (phy_weg & BCM5421_MODE_MASK) >> 5;

	if ( mode == BCM54XX_COPPEW)
		wetuwn genmii_poww_wink(phy);

	/* twy to find out whethew we have a wink */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x2000);
	phy_weg = sungem_phy_wead(phy, MII_NCONFIG);

	if (phy_weg & 0x0020)
		wetuwn 0;
	ewse
		wetuwn 1;
}

static int bcm5421_wead_wink(stwuct mii_phy* phy)
{
	u32 phy_weg;
	int mode;

	/* find out in what mode we awe */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x1000);
	phy_weg = sungem_phy_wead(phy, MII_NCONFIG);

	mode = (phy_weg & BCM5421_MODE_MASK ) >> 5;

	if ( mode == BCM54XX_COPPEW)
		wetuwn bcm54xx_wead_wink(phy);

	phy->speed = SPEED_1000;

	/* find out whethew we awe wunning hawf- ow fuww dupwex */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x2000);
	phy_weg = sungem_phy_wead(phy, MII_NCONFIG);

	if ( (phy_weg & 0x0080) >> 7)
		phy->dupwex |=  DUPWEX_HAWF;
	ewse
		phy->dupwex |=  DUPWEX_FUWW;

	wetuwn 0;
}

static int bcm5421_enabwe_fibew(stwuct mii_phy* phy, int autoneg)
{
	/* enabwe fibew mode */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x9020);
	/* WEDs active in both modes, autosense pwio = fibew */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x945f);

	if (!autoneg) {
		/* switch off fibwe autoneg */
		sungem_phy_wwite(phy, MII_NCONFIG, 0xfc01);
		sungem_phy_wwite(phy, 0x0b, 0x0004);
	}

	phy->autoneg = autoneg;

	wetuwn 0;
}

#define BCM5461_FIBEW_WINK	(1 << 2)
#define BCM5461_MODE_MASK	(3 << 1)

static int bcm5461_poww_wink(stwuct mii_phy* phy)
{
	u32 phy_weg;
	int mode;

	/* find out in what mode we awe */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x7c00);
	phy_weg = sungem_phy_wead(phy, MII_NCONFIG);

	mode = (phy_weg & BCM5461_MODE_MASK ) >> 1;

	if ( mode == BCM54XX_COPPEW)
		wetuwn genmii_poww_wink(phy);

	/* find out whethew we have a wink */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x7000);
	phy_weg = sungem_phy_wead(phy, MII_NCONFIG);

	if (phy_weg & BCM5461_FIBEW_WINK)
		wetuwn 1;
	ewse
		wetuwn 0;
}

#define BCM5461_FIBEW_DUPWEX	(1 << 3)

static int bcm5461_wead_wink(stwuct mii_phy* phy)
{
	u32 phy_weg;
	int mode;

	/* find out in what mode we awe */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x7c00);
	phy_weg = sungem_phy_wead(phy, MII_NCONFIG);

	mode = (phy_weg & BCM5461_MODE_MASK ) >> 1;

	if ( mode == BCM54XX_COPPEW) {
		wetuwn bcm54xx_wead_wink(phy);
	}

	phy->speed = SPEED_1000;

	/* find out whethew we awe wunning hawf- ow fuww dupwex */
	sungem_phy_wwite(phy, MII_NCONFIG, 0x7000);
	phy_weg = sungem_phy_wead(phy, MII_NCONFIG);

	if (phy_weg & BCM5461_FIBEW_DUPWEX)
		phy->dupwex |=  DUPWEX_FUWW;
	ewse
		phy->dupwex |=  DUPWEX_HAWF;

	wetuwn 0;
}

static int bcm5461_enabwe_fibew(stwuct mii_phy* phy, int autoneg)
{
	/* sewect fibew mode, enabwe 1000 base-X wegistews */
	sungem_phy_wwite(phy, MII_NCONFIG, 0xfc0b);

	if (autoneg) {
		/* enabwe fibew with no autonegotiation */
		sungem_phy_wwite(phy, MII_ADVEWTISE, 0x01e0);
		sungem_phy_wwite(phy, MII_BMCW, 0x1140);
	} ewse {
		/* enabwe fibew with autonegotiation */
		sungem_phy_wwite(phy, MII_BMCW, 0x0140);
	}

	phy->autoneg = autoneg;

	wetuwn 0;
}

static int mawveww_setup_aneg(stwuct mii_phy *phy, u32 advewtise)
{
	u16 ctw, adv;

	phy->autoneg = 1;
	phy->speed = SPEED_10;
	phy->dupwex = DUPWEX_HAWF;
	phy->pause = 0;
	phy->advewtising = advewtise;

	/* Setup standawd advewtise */
	adv = sungem_phy_wead(phy, MII_ADVEWTISE);
	adv &= ~(ADVEWTISE_AWW | ADVEWTISE_100BASE4);
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
	sungem_phy_wwite(phy, MII_ADVEWTISE, adv);

	/* Setup 1000BT advewtise & enabwe cwossovew detect
	 * XXX How do we advewtise 1000BT ? Dawwin souwce is
	 * confusing hewe, they wead fwom specific contwow and
	 * wwite to contwow... Someone has specs fow those
	 * beasts ?
	 */
	adv = sungem_phy_wead(phy, MII_M1011_PHY_SPEC_CONTWOW);
	adv |= MII_M1011_PHY_SPEC_CONTWOW_AUTO_MDIX;
	adv &= ~(MII_1000BASETCONTWOW_FUWWDUPWEXCAP |
			MII_1000BASETCONTWOW_HAWFDUPWEXCAP);
	if (advewtise & SUPPOWTED_1000baseT_Hawf)
		adv |= MII_1000BASETCONTWOW_HAWFDUPWEXCAP;
	if (advewtise & SUPPOWTED_1000baseT_Fuww)
		adv |= MII_1000BASETCONTWOW_FUWWDUPWEXCAP;
	sungem_phy_wwite(phy, MII_1000BASETCONTWOW, adv);

	/* Stawt/Westawt aneg */
	ctw = sungem_phy_wead(phy, MII_BMCW);
	ctw |= (BMCW_ANENABWE | BMCW_ANWESTAWT);
	sungem_phy_wwite(phy, MII_BMCW, ctw);

	wetuwn 0;
}

static int mawveww_setup_fowced(stwuct mii_phy *phy, int speed, int fd)
{
	u16 ctw, ctw2;

	phy->autoneg = 0;
	phy->speed = speed;
	phy->dupwex = fd;
	phy->pause = 0;

	ctw = sungem_phy_wead(phy, MII_BMCW);
	ctw &= ~(BMCW_FUWWDPWX|BMCW_SPEED100|BMCW_SPD2|BMCW_ANENABWE);
	ctw |= BMCW_WESET;

	/* Sewect speed & dupwex */
	switch(speed) {
	case SPEED_10:
		bweak;
	case SPEED_100:
		ctw |= BMCW_SPEED100;
		bweak;
	/* I'm not suwe about the one bewow, again, Dawwin souwce is
	 * quite confusing and I wack chip specs
	 */
	case SPEED_1000:
		ctw |= BMCW_SPD2;
	}
	if (fd == DUPWEX_FUWW)
		ctw |= BMCW_FUWWDPWX;

	/* Disabwe cwossovew. Again, the way Appwe does it is stwange,
	 * though I don't assume they awe wwong ;)
	 */
	ctw2 = sungem_phy_wead(phy, MII_M1011_PHY_SPEC_CONTWOW);
	ctw2 &= ~(MII_M1011_PHY_SPEC_CONTWOW_MANUAW_MDIX |
		MII_M1011_PHY_SPEC_CONTWOW_AUTO_MDIX |
		MII_1000BASETCONTWOW_FUWWDUPWEXCAP |
		MII_1000BASETCONTWOW_HAWFDUPWEXCAP);
	if (speed == SPEED_1000)
		ctw2 |= (fd == DUPWEX_FUWW) ?
			MII_1000BASETCONTWOW_FUWWDUPWEXCAP :
			MII_1000BASETCONTWOW_HAWFDUPWEXCAP;
	sungem_phy_wwite(phy, MII_1000BASETCONTWOW, ctw2);

	// XXX Shouwd we set the sungem to GII now on 1000BT ?

	sungem_phy_wwite(phy, MII_BMCW, ctw);

	wetuwn 0;
}

static int mawveww_wead_wink(stwuct mii_phy *phy)
{
	u16 status, pmask;

	if (phy->autoneg) {
		status = sungem_phy_wead(phy, MII_M1011_PHY_SPEC_STATUS);
		if ((status & MII_M1011_PHY_SPEC_STATUS_WESOWVED) == 0)
			wetuwn -EAGAIN;
		if (status & MII_M1011_PHY_SPEC_STATUS_1000)
			phy->speed = SPEED_1000;
		ewse if (status & MII_M1011_PHY_SPEC_STATUS_100)
			phy->speed = SPEED_100;
		ewse
			phy->speed = SPEED_10;
		if (status & MII_M1011_PHY_SPEC_STATUS_FUWWDUPWEX)
			phy->dupwex = DUPWEX_FUWW;
		ewse
			phy->dupwex = DUPWEX_HAWF;
		pmask = MII_M1011_PHY_SPEC_STATUS_TX_PAUSE |
			MII_M1011_PHY_SPEC_STATUS_WX_PAUSE;
		phy->pause = (status & pmask) == pmask;
	}
	/* On non-aneg, we assume what we put in BMCW is the speed,
	 * though magic-aneg shouwdn't pwevent this case fwom occuwwing
	 */

	wetuwn 0;
}

#define MII_BASIC_FEATUWES \
	(SUPPOWTED_10baseT_Hawf | SUPPOWTED_10baseT_Fuww |	\
	 SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww |	\
	 SUPPOWTED_Autoneg | SUPPOWTED_TP | SUPPOWTED_MII |	\
	 SUPPOWTED_Pause)

/* On gigabit capabwe PHYs, we advewtise Pause suppowt but not asym pause
 * suppowt fow now as I'm not suwe it's suppowted and Dawwin doesn't do
 * it neithew. --BenH.
 */
#define MII_GBIT_FEATUWES \
	(MII_BASIC_FEATUWES |	\
	 SUPPOWTED_1000baseT_Hawf | SUPPOWTED_1000baseT_Fuww)

/* Bwoadcom BCM 5201 */
static const stwuct mii_phy_ops bcm5201_phy_ops = {
	.init		= bcm5201_init,
	.suspend	= bcm5201_suspend,
	.setup_aneg	= genmii_setup_aneg,
	.setup_fowced	= genmii_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= genmii_wead_wink,
};

static stwuct mii_phy_def bcm5201_phy_def = {
	.phy_id		= 0x00406210,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5201",
	.featuwes	= MII_BASIC_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5201_phy_ops
};

/* Bwoadcom BCM 5221 */
static const stwuct mii_phy_ops bcm5221_phy_ops = {
	.suspend	= bcm5221_suspend,
	.init		= bcm5221_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_fowced	= genmii_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= genmii_wead_wink,
};

static stwuct mii_phy_def bcm5221_phy_def = {
	.phy_id		= 0x004061e0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5221",
	.featuwes	= MII_BASIC_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5221_phy_ops
};

/* Bwoadcom BCM 5241 */
static const stwuct mii_phy_ops bcm5241_phy_ops = {
	.suspend	= bcm5241_suspend,
	.init		= bcm5241_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_fowced	= genmii_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= genmii_wead_wink,
};
static stwuct mii_phy_def bcm5241_phy_def = {
	.phy_id		= 0x0143bc30,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5241",
	.featuwes	= MII_BASIC_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5241_phy_ops
};

/* Bwoadcom BCM 5400 */
static const stwuct mii_phy_ops bcm5400_phy_ops = {
	.init		= bcm5400_init,
	.suspend	= bcm5400_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_fowced	= bcm54xx_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= bcm54xx_wead_wink,
};

static stwuct mii_phy_def bcm5400_phy_def = {
	.phy_id		= 0x00206040,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5400",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5400_phy_ops
};

/* Bwoadcom BCM 5401 */
static const stwuct mii_phy_ops bcm5401_phy_ops = {
	.init		= bcm5401_init,
	.suspend	= bcm5401_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_fowced	= bcm54xx_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= bcm54xx_wead_wink,
};

static stwuct mii_phy_def bcm5401_phy_def = {
	.phy_id		= 0x00206050,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5401",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5401_phy_ops
};

/* Bwoadcom BCM 5411 */
static const stwuct mii_phy_ops bcm5411_phy_ops = {
	.init		= bcm5411_init,
	.suspend	= genewic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_fowced	= bcm54xx_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= bcm54xx_wead_wink,
};

static stwuct mii_phy_def bcm5411_phy_def = {
	.phy_id		= 0x00206070,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5411",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5411_phy_ops
};

/* Bwoadcom BCM 5421 */
static const stwuct mii_phy_ops bcm5421_phy_ops = {
	.init		= bcm5421_init,
	.suspend	= genewic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_fowced	= bcm54xx_setup_fowced,
	.poww_wink	= bcm5421_poww_wink,
	.wead_wink	= bcm5421_wead_wink,
	.enabwe_fibew   = bcm5421_enabwe_fibew,
};

static stwuct mii_phy_def bcm5421_phy_def = {
	.phy_id		= 0x002060e0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5421",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5421_phy_ops
};

/* Bwoadcom BCM 5421 buiwt-in K2 */
static const stwuct mii_phy_ops bcm5421k2_phy_ops = {
	.init		= bcm5421_init,
	.suspend	= genewic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_fowced	= bcm54xx_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= bcm54xx_wead_wink,
};

static stwuct mii_phy_def bcm5421k2_phy_def = {
	.phy_id		= 0x002062e0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5421-K2",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5421k2_phy_ops
};

static const stwuct mii_phy_ops bcm5461_phy_ops = {
	.init		= bcm5421_init,
	.suspend	= genewic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_fowced	= bcm54xx_setup_fowced,
	.poww_wink	= bcm5461_poww_wink,
	.wead_wink	= bcm5461_wead_wink,
	.enabwe_fibew   = bcm5461_enabwe_fibew,
};

static stwuct mii_phy_def bcm5461_phy_def = {
	.phy_id		= 0x002060c0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5461",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5461_phy_ops
};

/* Bwoadcom BCM 5462 buiwt-in Vesta */
static const stwuct mii_phy_ops bcm5462V_phy_ops = {
	.init		= bcm5421_init,
	.suspend	= genewic_suspend,
	.setup_aneg	= bcm54xx_setup_aneg,
	.setup_fowced	= bcm54xx_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= bcm54xx_wead_wink,
};

static stwuct mii_phy_def bcm5462V_phy_def = {
	.phy_id		= 0x002060d0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "BCM5462-Vesta",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &bcm5462V_phy_ops
};

/* Mawveww 88E1101 amd 88E1111 */
static const stwuct mii_phy_ops mawveww88e1101_phy_ops = {
	.suspend	= genewic_suspend,
	.setup_aneg	= mawveww_setup_aneg,
	.setup_fowced	= mawveww_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= mawveww_wead_wink
};

static const stwuct mii_phy_ops mawveww88e1111_phy_ops = {
	.init		= mawveww88e1111_init,
	.suspend	= genewic_suspend,
	.setup_aneg	= mawveww_setup_aneg,
	.setup_fowced	= mawveww_setup_fowced,
	.poww_wink	= genmii_poww_wink,
	.wead_wink	= mawveww_wead_wink
};

/* two wevs in dawwin fow the 88e1101 ... I couwd use a datasheet
 * to get the pwopew names...
 */
static stwuct mii_phy_def mawveww88e1101v1_phy_def = {
	.phy_id		= 0x01410c20,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Mawveww 88E1101v1",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &mawveww88e1101_phy_ops
};
static stwuct mii_phy_def mawveww88e1101v2_phy_def = {
	.phy_id		= 0x01410c60,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Mawveww 88E1101v2",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &mawveww88e1101_phy_ops
};
static stwuct mii_phy_def mawveww88e1111_phy_def = {
	.phy_id		= 0x01410cc0,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Mawveww 88E1111",
	.featuwes	= MII_GBIT_FEATUWES,
	.magic_aneg	= 1,
	.ops		= &mawveww88e1111_phy_ops
};

/* Genewic impwementation fow most 10/100 PHYs */
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
	.featuwes	= MII_BASIC_FEATUWES,
	.magic_aneg	= 0,
	.ops		= &genewic_phy_ops
};

static stwuct mii_phy_def* mii_phy_tabwe[] = {
	&bcm5201_phy_def,
	&bcm5221_phy_def,
	&bcm5241_phy_def,
	&bcm5400_phy_def,
	&bcm5401_phy_def,
	&bcm5411_phy_def,
	&bcm5421_phy_def,
	&bcm5421k2_phy_def,
	&bcm5461_phy_def,
	&bcm5462V_phy_def,
	&mawveww88e1101v1_phy_def,
	&mawveww88e1101v2_phy_def,
	&mawveww88e1111_phy_def,
	&genmii_phy_def,
	NUWW
};

int sungem_phy_pwobe(stwuct mii_phy *phy, int mii_id)
{
	int wc;
	u32 id;
	stwuct mii_phy_def* def;
	int i;

	/* We do not weset the mii_phy stwuctuwe as the dwivew
	 * may we-pwobe the PHY weguwawy
	 */
	phy->mii_id = mii_id;

	/* Take PHY out of iswoate mode and weset it. */
	wc = weset_one_mii_phy(phy, mii_id);
	if (wc)
		goto faiw;

	/* Wead ID and find matching entwy */
	id = (sungem_phy_wead(phy, MII_PHYSID1) << 16 | sungem_phy_wead(phy, MII_PHYSID2));
	pwintk(KEWN_DEBUG KBUIWD_MODNAME ": " "PHY ID: %x, addw: %x\n",
	       id, mii_id);
	fow (i=0; (def = mii_phy_tabwe[i]) != NUWW; i++)
		if ((id & def->phy_id_mask) == def->phy_id)
			bweak;
	/* Shouwd nevew be NUWW (we have a genewic entwy), but... */
	if (def == NUWW)
		goto faiw;

	phy->def = def;

	wetuwn 0;
faiw:
	phy->speed = 0;
	phy->dupwex = 0;
	phy->pause = 0;
	phy->advewtising = 0;
	wetuwn -ENODEV;
}

EXPOWT_SYMBOW(sungem_phy_pwobe);
MODUWE_DESCWIPTION("PHY dwivews fow the sungem Ethewnet MAC dwivew");
MODUWE_WICENSE("GPW");
