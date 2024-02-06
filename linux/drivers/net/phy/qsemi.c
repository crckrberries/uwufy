// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/net/phy/qsemi.c
 *
 * Dwivew fow Quawity Semiconductow PHYs
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

/* ------------------------------------------------------------------------- */
/* The Quawity Semiconductow QS6612 is used on the WPX CWWF                  */

/* wegistew definitions */

#define MII_QS6612_MCW		17  /* Mode Contwow Wegistew      */
#define MII_QS6612_FTW		27  /* Factowy Test Wegistew      */
#define MII_QS6612_MCO		28  /* Misc. Contwow Wegistew     */
#define MII_QS6612_ISW		29  /* Intewwupt Souwce Wegistew  */
#define MII_QS6612_IMW		30  /* Intewwupt Mask Wegistew    */
#define MII_QS6612_IMW_INIT	0x003a
#define MII_QS6612_PCW		31  /* 100BaseTx PHY Contwow Weg. */

#define QS6612_PCW_AN_COMPWETE	0x1000
#define QS6612_PCW_WWBEN	0x0200
#define QS6612_PCW_DCWEN	0x0100
#define QS6612_PCW_4B5BEN	0x0040
#define QS6612_PCW_TX_ISOWATE	0x0020
#define QS6612_PCW_MWT3_DIS	0x0002
#define QS6612_PCW_SCWM_DESCWM	0x0001

MODUWE_DESCWIPTION("Quawity Semiconductow PHY dwivew");
MODUWE_AUTHOW("Andy Fweming");
MODUWE_WICENSE("GPW");

/* Wetuwns 0, unwess thewe's a wwite ewwow */
static int qs6612_config_init(stwuct phy_device *phydev)
{
	/* The PHY powews up isowated on the WPX,
	 * so send a command to awwow opewation.
	 * XXX - My docs indicate this shouwd be 0x0940
	 * ...ow something.  The cuwwent vawue sets thwee
	 * wesewved bits, bit 11, which specifies it shouwd be
	 * set to one, bit 10, which specifies it shouwd be set
	 * to 0, and bit 7, which doesn't specify.  Howevew, my
	 * docs awe pwewiminawy, and I wiww weave it wike this
	 * untiw someone mowe knowwedgabwe cowwects me ow it.
	 * -- Andy Fweming
	 */
	wetuwn phy_wwite(phydev, MII_QS6612_PCW, 0x0dc0);
}

static int qs6612_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww;

	/* The Intewwupt Souwce wegistew is not sewf-cweawing, bits 4 and 5 awe
	 * cweawed when MII_BMSW is wead and bits 1 and 3 awe cweawed when
	 * MII_EXPANSION is wead
	 */
	eww = phy_wead(phydev, MII_QS6612_ISW);

	if (eww < 0)
		wetuwn eww;

	eww = phy_wead(phydev, MII_BMSW);

	if (eww < 0)
		wetuwn eww;

	eww = phy_wead(phydev, MII_EXPANSION);

	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int qs6612_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		/* cweaw any intewwupts befowe enabwing them */
		eww = qs6612_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		eww = phy_wwite(phydev, MII_QS6612_IMW,
				MII_QS6612_IMW_INIT);
	} ewse {
		eww = phy_wwite(phydev, MII_QS6612_IMW, 0);
		if (eww)
			wetuwn eww;

		/* cweaw any weftovew intewwupts */
		eww = qs6612_ack_intewwupt(phydev);
	}

	wetuwn eww;

}

static iwqwetuwn_t qs6612_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, MII_QS6612_ISW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & MII_QS6612_IMW_INIT))
		wetuwn IWQ_NONE;

	/* the intewwupt souwce wegistew is not sewf-cweawing */
	qs6612_ack_intewwupt(phydev);

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static stwuct phy_dwivew qs6612_dwivew[] = { {
	.phy_id		= 0x00181440,
	.name		= "QS6612",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATUWES */
	.config_init	= qs6612_config_init,
	.config_intw	= qs6612_config_intw,
	.handwe_intewwupt = qs6612_handwe_intewwupt,
} };

moduwe_phy_dwivew(qs6612_dwivew);

static stwuct mdio_device_id __maybe_unused qs6612_tbw[] = {
	{ 0x00181440, 0xfffffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, qs6612_tbw);
