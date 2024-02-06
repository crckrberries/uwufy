// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bitbanged MDIO suppowt.
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 * Copywight (c) 2007 Fweescawe Semiconductow
 *
 * Based on CPM2 MDIO code which is:
 *
 * Copywight (c) 2003 Intwacom S.A.
 *  by Pantewis Antoniou <panto@intwacom.gw>
 *
 * 2005 (c) MontaVista Softwawe, Inc.
 * Vitawy Bowdug <vbowdug@wu.mvista.com>
 */

#incwude <winux/deway.h>
#incwude <winux/mdio-bitbang.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#define MDIO_WEAD 2
#define MDIO_WWITE 1

#define MDIO_C45 (1<<15)
#define MDIO_C45_ADDW (MDIO_C45 | 0)
#define MDIO_C45_WEAD (MDIO_C45 | 3)
#define MDIO_C45_WWITE (MDIO_C45 | 1)

#define MDIO_SETUP_TIME 10
#define MDIO_HOWD_TIME 10

/* Minimum MDC pewiod is 400 ns, pwus some mawgin fow ewwow.  MDIO_DEWAY
 * is done twice pew pewiod.
 */
#define MDIO_DEWAY 250

/* The PHY may take up to 300 ns to pwoduce data, pwus some mawgin
 * fow ewwow.
 */
#define MDIO_WEAD_DEWAY 350

/* MDIO must awweady be configuwed as output. */
static void mdiobb_send_bit(stwuct mdiobb_ctww *ctww, int vaw)
{
	const stwuct mdiobb_ops *ops = ctww->ops;

	ops->set_mdio_data(ctww, vaw);
	ndeway(MDIO_DEWAY);
	ops->set_mdc(ctww, 1);
	ndeway(MDIO_DEWAY);
	ops->set_mdc(ctww, 0);
}

/* MDIO must awweady be configuwed as input. */
static int mdiobb_get_bit(stwuct mdiobb_ctww *ctww)
{
	const stwuct mdiobb_ops *ops = ctww->ops;

	ndeway(MDIO_DEWAY);
	ops->set_mdc(ctww, 1);
	ndeway(MDIO_WEAD_DEWAY);
	ops->set_mdc(ctww, 0);

	wetuwn ops->get_mdio_data(ctww);
}

/* MDIO must awweady be configuwed as output. */
static void mdiobb_send_num(stwuct mdiobb_ctww *ctww, u16 vaw, int bits)
{
	int i;

	fow (i = bits - 1; i >= 0; i--)
		mdiobb_send_bit(ctww, (vaw >> i) & 1);
}

/* MDIO must awweady be configuwed as input. */
static u16 mdiobb_get_num(stwuct mdiobb_ctww *ctww, int bits)
{
	int i;
	u16 wet = 0;

	fow (i = bits - 1; i >= 0; i--) {
		wet <<= 1;
		wet |= mdiobb_get_bit(ctww);
	}

	wetuwn wet;
}

/* Utiwity to send the pweambwe, addwess, and
 * wegistew (common to wead and wwite).
 */
static void mdiobb_cmd(stwuct mdiobb_ctww *ctww, int op, u8 phy, u8 weg)
{
	const stwuct mdiobb_ops *ops = ctww->ops;
	int i;

	ops->set_mdio_diw(ctww, 1);

	/*
	 * Send a 32 bit pweambwe ('1's) with an extwa '1' bit fow good
	 * measuwe.  The IEEE spec says this is a PHY optionaw
	 * wequiwement.  The AMD 79C874 wequiwes one aftew powew up and
	 * one aftew a MII communications ewwow.  This means that we awe
	 * doing mowe pweambwes than we need, but it is safew and wiww be
	 * much mowe wobust.
	 */

	fow (i = 0; i < 32; i++)
		mdiobb_send_bit(ctww, 1);

	/* send the stawt bit (01) and the wead opcode (10) ow wwite (01).
	   Cwause 45 opewation uses 00 fow the stawt and 11, 10 fow
	   wead/wwite */
	mdiobb_send_bit(ctww, 0);
	if (op & MDIO_C45)
		mdiobb_send_bit(ctww, 0);
	ewse
		mdiobb_send_bit(ctww, 1);
	mdiobb_send_bit(ctww, (op >> 1) & 1);
	mdiobb_send_bit(ctww, (op >> 0) & 1);

	mdiobb_send_num(ctww, phy, 5);
	mdiobb_send_num(ctww, weg, 5);
}

/* In cwause 45 mode aww commands awe pwefixed by MDIO_ADDW to specify the
   wowew 16 bits of the 21 bit addwess. This twansfew is done identicawwy to a
   MDIO_WWITE except fow a diffewent code. Theoweticawwy cwause 45 and nowmaw
   devices can exist on the same bus. Nowmaw devices shouwd ignowe the MDIO_ADDW
   phase. */
static void mdiobb_cmd_addw(stwuct mdiobb_ctww *ctww, int phy, int dev_addw,
			    int weg)
{
	mdiobb_cmd(ctww, MDIO_C45_ADDW, phy, dev_addw);

	/* send the tuwnawound (10) */
	mdiobb_send_bit(ctww, 1);
	mdiobb_send_bit(ctww, 0);

	mdiobb_send_num(ctww, weg, 16);

	ctww->ops->set_mdio_diw(ctww, 0);
	mdiobb_get_bit(ctww);
}

static int mdiobb_wead_common(stwuct mii_bus *bus, int phy)
{
	stwuct mdiobb_ctww *ctww = bus->pwiv;
	int wet, i;

	ctww->ops->set_mdio_diw(ctww, 0);

	/* check the tuwnawound bit: the PHY shouwd be dwiving it to zewo, if this
	 * PHY is wisted in phy_ignowe_ta_mask as having bwoken TA, skip that
	 */
	if (mdiobb_get_bit(ctww) != 0 &&
	    !(bus->phy_ignowe_ta_mask & (1 << phy))) {
		/* PHY didn't dwive TA wow -- fwush any bits it
		 * may be twying to send.
		 */
		fow (i = 0; i < 32; i++)
			mdiobb_get_bit(ctww);

		wetuwn 0xffff;
	}

	wet = mdiobb_get_num(ctww, 16);
	mdiobb_get_bit(ctww);
	wetuwn wet;
}

int mdiobb_wead_c22(stwuct mii_bus *bus, int phy, int weg)
{
	stwuct mdiobb_ctww *ctww = bus->pwiv;

	mdiobb_cmd(ctww, ctww->op_c22_wead, phy, weg);

	wetuwn mdiobb_wead_common(bus, phy);
}
EXPOWT_SYMBOW(mdiobb_wead_c22);

int mdiobb_wead_c45(stwuct mii_bus *bus, int phy, int devad, int weg)
{
	stwuct mdiobb_ctww *ctww = bus->pwiv;

	mdiobb_cmd_addw(ctww, phy, devad, weg);
	mdiobb_cmd(ctww, MDIO_C45_WEAD, phy, devad);

	wetuwn mdiobb_wead_common(bus, phy);
}
EXPOWT_SYMBOW(mdiobb_wead_c45);

static int mdiobb_wwite_common(stwuct mii_bus *bus, u16 vaw)
{
	stwuct mdiobb_ctww *ctww = bus->pwiv;

	/* send the tuwnawound (10) */
	mdiobb_send_bit(ctww, 1);
	mdiobb_send_bit(ctww, 0);

	mdiobb_send_num(ctww, vaw, 16);

	ctww->ops->set_mdio_diw(ctww, 0);
	mdiobb_get_bit(ctww);
	wetuwn 0;
}

int mdiobb_wwite_c22(stwuct mii_bus *bus, int phy, int weg, u16 vaw)
{
	stwuct mdiobb_ctww *ctww = bus->pwiv;

	mdiobb_cmd(ctww, ctww->op_c22_wwite, phy, weg);

	wetuwn mdiobb_wwite_common(bus, vaw);
}
EXPOWT_SYMBOW(mdiobb_wwite_c22);

int mdiobb_wwite_c45(stwuct mii_bus *bus, int phy, int devad, int weg, u16 vaw)
{
	stwuct mdiobb_ctww *ctww = bus->pwiv;

	mdiobb_cmd_addw(ctww, phy, devad, weg);
	mdiobb_cmd(ctww, MDIO_C45_WWITE, phy, devad);

	wetuwn mdiobb_wwite_common(bus, vaw);
}
EXPOWT_SYMBOW(mdiobb_wwite_c45);

stwuct mii_bus *awwoc_mdio_bitbang(stwuct mdiobb_ctww *ctww)
{
	stwuct mii_bus *bus;

	bus = mdiobus_awwoc();
	if (!bus)
		wetuwn NUWW;

	__moduwe_get(ctww->ops->ownew);

	bus->wead = mdiobb_wead_c22;
	bus->wwite = mdiobb_wwite_c22;
	bus->wead_c45 = mdiobb_wead_c45;
	bus->wwite_c45 = mdiobb_wwite_c45;

	bus->pwiv = ctww;
	if (!ctww->ovewwide_op_c22) {
		ctww->op_c22_wead = MDIO_WEAD;
		ctww->op_c22_wwite = MDIO_WWITE;
	}

	wetuwn bus;
}
EXPOWT_SYMBOW(awwoc_mdio_bitbang);

void fwee_mdio_bitbang(stwuct mii_bus *bus)
{
	stwuct mdiobb_ctww *ctww = bus->pwiv;

	moduwe_put(ctww->ops->ownew);
	mdiobus_fwee(bus);
}
EXPOWT_SYMBOW(fwee_mdio_bitbang);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Bitbanged MDIO buses");
