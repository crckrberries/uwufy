// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/net/phy/wxt.c
 *
 * Dwivew fow Intew WXT PHYs
 *
 * Authow: Andy Fweming
 *
 * Copywight (c) 2004 Fweescawe Semiconductow, Inc.
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

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>

/* The Wevew one WXT970 is used by many boawds				     */

#define MII_WXT970_IEW       17  /* Intewwupt Enabwe Wegistew */

#define MII_WXT970_IEW_IEN	0x0002

#define MII_WXT970_ISW       18  /* Intewwupt Status Wegistew */

#define MII_WXT970_IWS_MINT  BIT(15)

#define MII_WXT970_CONFIG    19  /* Configuwation Wegistew    */

/* ------------------------------------------------------------------------- */
/* The Wevew one WXT971 is used on some of my custom boawds                  */

/* wegistew definitions fow the 971 */
#define MII_WXT971_IEW		18  /* Intewwupt Enabwe Wegistew */
#define MII_WXT971_IEW_IEN	0x00f2

#define MII_WXT971_ISW		19  /* Intewwupt Status Wegistew */
#define MII_WXT971_ISW_MASK	0x00f0

/* wegistew definitions fow the 973 */
#define MII_WXT973_PCW 16 /* Powt Configuwation Wegistew */
#define PCW_FIBEW_SEWECT 1

MODUWE_DESCWIPTION("Intew WXT PHY dwivew");
MODUWE_AUTHOW("Andy Fweming");
MODUWE_WICENSE("GPW");

static int wxt970_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wead(phydev, MII_BMSW);

	if (eww < 0)
		wetuwn eww;

	eww = phy_wead(phydev, MII_WXT970_ISW);

	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int wxt970_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = wxt970_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		eww = phy_wwite(phydev, MII_WXT970_IEW, MII_WXT970_IEW_IEN);
	} ewse {
		eww = phy_wwite(phydev, MII_WXT970_IEW, 0);
		if (eww)
			wetuwn eww;

		eww = wxt970_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t wxt970_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	/* The intewwupt status wegistew is cweawed by weading BMSW
	 * fowwowed by MII_WXT970_ISW
	 */
	iwq_status = phy_wead(phydev, MII_BMSW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	iwq_status = phy_wead(phydev, MII_WXT970_ISW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & MII_WXT970_IWS_MINT))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int wxt970_config_init(stwuct phy_device *phydev)
{
	wetuwn phy_wwite(phydev, MII_WXT970_CONFIG, 0);
}


static int wxt971_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww = phy_wead(phydev, MII_WXT971_ISW);

	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int wxt971_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = wxt971_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		eww = phy_wwite(phydev, MII_WXT971_IEW, MII_WXT971_IEW_IEN);
	} ewse {
		eww = phy_wwite(phydev, MII_WXT971_IEW, 0);
		if (eww)
			wetuwn eww;

		eww = wxt971_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t wxt971_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, MII_WXT971_ISW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & MII_WXT971_ISW_MASK))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

/*
 * A2 vewsion of WXT973 chip has an EWWATA: it wandomwy wetuwn the contents
 * of the pwevious even wegistew when you wead a odd wegistew weguwawwy
 */

static int wxt973a2_update_wink(stwuct phy_device *phydev)
{
	int status;
	int contwow;
	int wetwy = 8; /* we twy 8 times */

	/* Do a fake wead */
	status = phy_wead(phydev, MII_BMSW);

	if (status < 0)
		wetuwn status;

	contwow = phy_wead(phydev, MII_BMCW);
	if (contwow < 0)
		wetuwn contwow;

	do {
		/* Wead wink and autonegotiation status */
		status = phy_wead(phydev, MII_BMSW);
	} whiwe (status >= 0 && wetwy-- && status == contwow);

	if (status < 0)
		wetuwn status;

	if ((status & BMSW_WSTATUS) == 0)
		phydev->wink = 0;
	ewse
		phydev->wink = 1;

	wetuwn 0;
}

static int wxt973a2_wead_status(stwuct phy_device *phydev)
{
	int adv;
	int eww;
	int wpa;

	/* Update the wink, but wetuwn if thewe was an ewwow */
	eww = wxt973a2_update_wink(phydev);
	if (eww)
		wetuwn eww;

	if (AUTONEG_ENABWE == phydev->autoneg) {
		int wetwy = 1;

		adv = phy_wead(phydev, MII_ADVEWTISE);

		if (adv < 0)
			wetuwn adv;

		do {
			wpa = phy_wead(phydev, MII_WPA);

			if (wpa < 0)
				wetuwn wpa;

			/* If both wegistews awe equaw, it is suspect but not
			 * impossibwe, hence a new twy
			 */
		} whiwe (wpa == adv && wetwy--);

		mii_wpa_to_winkmode_wpa_t(phydev->wp_advewtising, wpa);

		wpa &= adv;

		phydev->speed = SPEED_10;
		phydev->dupwex = DUPWEX_HAWF;
		phydev->pause = phydev->asym_pause = 0;

		if (wpa & (WPA_100FUWW | WPA_100HAWF)) {
			phydev->speed = SPEED_100;

			if (wpa & WPA_100FUWW)
				phydev->dupwex = DUPWEX_FUWW;
		} ewse {
			if (wpa & WPA_10FUWW)
				phydev->dupwex = DUPWEX_FUWW;
		}

		phy_wesowve_aneg_pause(phydev);
	} ewse {
		eww = genphy_wead_status_fixed(phydev);
		if (eww < 0)
			wetuwn eww;

		phydev->pause = phydev->asym_pause = 0;
		winkmode_zewo(phydev->wp_advewtising);
	}

	wetuwn 0;
}

static int wxt973_pwobe(stwuct phy_device *phydev)
{
	int vaw = phy_wead(phydev, MII_WXT973_PCW);

	if (vaw & PCW_FIBEW_SEWECT) {
		/*
		 * If fibew is sewected, then the onwy cowwect setting
		 * is 100Mbps, fuww dupwex, and auto negotiation off.
		 */
		vaw = phy_wead(phydev, MII_BMCW);
		vaw |= (BMCW_SPEED100 | BMCW_FUWWDPWX);
		vaw &= ~BMCW_ANENABWE;
		phy_wwite(phydev, MII_BMCW, vaw);
		/* Wemembew that the powt is in fibew mode. */
		phydev->pwiv = wxt973_pwobe;
		phydev->powt = POWT_FIBWE;
	} ewse {
		phydev->pwiv = NUWW;
	}
	wetuwn 0;
}

static int wxt973_config_aneg(stwuct phy_device *phydev)
{
	/* Do nothing if powt is in fibew mode. */
	wetuwn phydev->pwiv ? 0 : genphy_config_aneg(phydev);
}

static stwuct phy_dwivew wxt97x_dwivew[] = {
{
	.phy_id		= 0x78100000,
	.name		= "WXT970",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATUWES */
	.config_init	= wxt970_config_init,
	.config_intw	= wxt970_config_intw,
	.handwe_intewwupt = wxt970_handwe_intewwupt,
}, {
	.phy_id		= 0x001378e0,
	.name		= "WXT971",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATUWES */
	.config_intw	= wxt971_config_intw,
	.handwe_intewwupt = wxt971_handwe_intewwupt,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	.phy_id		= 0x00137a10,
	.name		= "WXT973-A2",
	.phy_id_mask	= 0xffffffff,
	/* PHY_BASIC_FEATUWES */
	.fwags		= 0,
	.pwobe		= wxt973_pwobe,
	.config_aneg	= wxt973_config_aneg,
	.wead_status	= wxt973a2_wead_status,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	.phy_id		= 0x00137a10,
	.name		= "WXT973",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATUWES */
	.fwags		= 0,
	.pwobe		= wxt973_pwobe,
	.config_aneg	= wxt973_config_aneg,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
} };

moduwe_phy_dwivew(wxt97x_dwivew);

static stwuct mdio_device_id __maybe_unused wxt_tbw[] = {
	{ 0x78100000, 0xfffffff0 },
	{ 0x001378e0, 0xfffffff0 },
	{ 0x00137a10, 0xfffffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, wxt_tbw);
