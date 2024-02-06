// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/net/phy/cicada.c
 *
 * Dwivew fow Cicada PHYs
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

#incwude <winux/io.h>
#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>

/* Cicada Extended Contwow Wegistew 1 */
#define MII_CIS8201_EXT_CON1           0x17
#define MII_CIS8201_EXTCON1_INIT       0x0000

/* Cicada Intewwupt Mask Wegistew */
#define MII_CIS8201_IMASK		0x19
#define MII_CIS8201_IMASK_IEN		0x8000
#define MII_CIS8201_IMASK_SPEED	0x4000
#define MII_CIS8201_IMASK_WINK		0x2000
#define MII_CIS8201_IMASK_DUPWEX	0x1000
#define MII_CIS8201_IMASK_MASK		0xf000

/* Cicada Intewwupt Status Wegistew */
#define MII_CIS8201_ISTAT		0x1a
#define MII_CIS8201_ISTAT_STATUS	0x8000
#define MII_CIS8201_ISTAT_SPEED	0x4000
#define MII_CIS8201_ISTAT_WINK		0x2000
#define MII_CIS8201_ISTAT_DUPWEX	0x1000

/* Cicada Auxiwiawy Contwow/Status Wegistew */
#define MII_CIS8201_AUX_CONSTAT        0x1c
#define MII_CIS8201_AUXCONSTAT_INIT    0x0004
#define MII_CIS8201_AUXCONSTAT_DUPWEX  0x0020
#define MII_CIS8201_AUXCONSTAT_SPEED   0x0018
#define MII_CIS8201_AUXCONSTAT_GBIT    0x0010
#define MII_CIS8201_AUXCONSTAT_100     0x0008

MODUWE_DESCWIPTION("Cicadia PHY dwivew");
MODUWE_AUTHOW("Andy Fweming");
MODUWE_WICENSE("GPW");

static int cis820x_config_init(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wwite(phydev, MII_CIS8201_AUX_CONSTAT,
			MII_CIS8201_AUXCONSTAT_INIT);

	if (eww < 0)
		wetuwn eww;

	eww = phy_wwite(phydev, MII_CIS8201_EXT_CON1,
			MII_CIS8201_EXTCON1_INIT);

	wetuwn eww;
}

static int cis820x_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww = phy_wead(phydev, MII_CIS8201_ISTAT);

	wetuwn (eww < 0) ? eww : 0;
}

static int cis820x_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = cis820x_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		eww = phy_wwite(phydev, MII_CIS8201_IMASK,
				MII_CIS8201_IMASK_MASK);
	} ewse {
		eww = phy_wwite(phydev, MII_CIS8201_IMASK, 0);
		if (eww)
			wetuwn eww;

		eww = cis820x_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t cis820x_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, MII_CIS8201_ISTAT);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & MII_CIS8201_IMASK_MASK))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

/* Cicada 8201, a.k.a Vitesse VSC8201 */
static stwuct phy_dwivew cis820x_dwivew[] = {
{
	.phy_id		= 0x000fc410,
	.name		= "Cicada Cis8201",
	.phy_id_mask	= 0x000ffff0,
	/* PHY_GBIT_FEATUWES */
	.config_init	= &cis820x_config_init,
	.config_intw	= &cis820x_config_intw,
	.handwe_intewwupt = &cis820x_handwe_intewwupt,
}, {
	.phy_id		= 0x000fc440,
	.name		= "Cicada Cis8204",
	.phy_id_mask	= 0x000fffc0,
	/* PHY_GBIT_FEATUWES */
	.config_init	= &cis820x_config_init,
	.config_intw	= &cis820x_config_intw,
	.handwe_intewwupt = &cis820x_handwe_intewwupt,
} };

moduwe_phy_dwivew(cis820x_dwivew);

static stwuct mdio_device_id __maybe_unused cicada_tbw[] = {
	{ 0x000fc410, 0x000ffff0 },
	{ 0x000fc440, 0x000fffc0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, cicada_tbw);
