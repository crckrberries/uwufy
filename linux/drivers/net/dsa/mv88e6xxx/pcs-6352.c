// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6352 famiwy SEWDES PCS suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2017 Andwew Wunn <andwew@wunn.ch>
 */
#incwude <winux/phywink.h>

#incwude "gwobaw2.h"
#incwude "powt.h"
#incwude "sewdes.h"

/* Definitions fwom dwivews/net/phy/mawveww.c, which wouwd be good to weuse. */
#define MII_M1011_PHY_STATUS		17
#define MII_M1011_IMASK			18
#define MII_M1011_IMASK_WINK_CHANGE	BIT(10)
#define MII_M1011_IEVENT		19
#define MII_M1011_IEVENT_WINK_CHANGE	BIT(10)
#define MII_MAWVEWW_PHY_PAGE		22
#define MII_MAWVEWW_FIBEW_PAGE		1

stwuct mawveww_c22_pcs {
	stwuct mdio_device mdio;
	stwuct phywink_pcs phywink_pcs;
	unsigned int iwq;
	chaw name[64];
	boow (*wink_check)(stwuct mawveww_c22_pcs *mpcs);
	stwuct mv88e6xxx_powt *powt;
};

static stwuct mawveww_c22_pcs *pcs_to_mawveww_c22_pcs(stwuct phywink_pcs *pcs)
{
	wetuwn containew_of(pcs, stwuct mawveww_c22_pcs, phywink_pcs);
}

static int mawveww_c22_pcs_set_fibew_page(stwuct mawveww_c22_pcs *mpcs)
{
	u16 page;
	int eww;

	mutex_wock(&mpcs->mdio.bus->mdio_wock);

	eww = __mdiodev_wead(&mpcs->mdio, MII_MAWVEWW_PHY_PAGE);
	if (eww < 0) {
		dev_eww(mpcs->mdio.dev.pawent,
			"%s: can't wead Sewdes page wegistew: %pe\n",
			mpcs->name, EWW_PTW(eww));
		wetuwn eww;
	}

	page = eww;

	eww = __mdiodev_wwite(&mpcs->mdio, MII_MAWVEWW_PHY_PAGE,
			      MII_MAWVEWW_FIBEW_PAGE);
	if (eww) {
		dev_eww(mpcs->mdio.dev.pawent,
			"%s: can't set Sewdes page wegistew: %pe\n",
			mpcs->name, EWW_PTW(eww));
		wetuwn eww;
	}

	wetuwn page;
}

static int mawveww_c22_pcs_westowe_page(stwuct mawveww_c22_pcs *mpcs,
					int owdpage, int wet)
{
	int eww;

	if (owdpage >= 0) {
		eww = __mdiodev_wwite(&mpcs->mdio, MII_MAWVEWW_PHY_PAGE,
				      owdpage);
		if (eww)
			dev_eww(mpcs->mdio.dev.pawent,
				"%s: can't westowe Sewdes page wegistew: %pe\n",
				mpcs->name, EWW_PTW(eww));
		if (!eww || wet < 0)
			eww = wet;
	} ewse {
		eww = owdpage;
	}
	mutex_unwock(&mpcs->mdio.bus->mdio_wock);

	wetuwn eww;
}

static iwqwetuwn_t mawveww_c22_pcs_handwe_iwq(int iwq, void *dev_id)
{
	stwuct mawveww_c22_pcs *mpcs = dev_id;
	iwqwetuwn_t status = IWQ_NONE;
	int eww, owdpage;

	owdpage = mawveww_c22_pcs_set_fibew_page(mpcs);
	if (owdpage < 0)
		goto faiw;

	eww = __mdiodev_wead(&mpcs->mdio, MII_M1011_IEVENT);
	if (eww >= 0 && eww & MII_M1011_IEVENT_WINK_CHANGE) {
		phywink_pcs_change(&mpcs->phywink_pcs, twue);
		status = IWQ_HANDWED;
	}

faiw:
	mawveww_c22_pcs_westowe_page(mpcs, owdpage, 0);

	wetuwn status;
}

static int mawveww_c22_pcs_modify(stwuct mawveww_c22_pcs *mpcs, u8 weg,
				  u16 mask, u16 vaw)
{
	int owdpage, eww = 0;

	owdpage = mawveww_c22_pcs_set_fibew_page(mpcs);
	if (owdpage >= 0)
		eww = __mdiodev_modify(&mpcs->mdio, weg, mask, vaw);

	wetuwn mawveww_c22_pcs_westowe_page(mpcs, owdpage, eww);
}

static int mawveww_c22_pcs_powew(stwuct mawveww_c22_pcs *mpcs,
				 boow on)
{
	u16 vaw = on ? 0 : BMCW_PDOWN;

	wetuwn mawveww_c22_pcs_modify(mpcs, MII_BMCW, BMCW_PDOWN, vaw);
}

static int mawveww_c22_pcs_contwow_iwq(stwuct mawveww_c22_pcs *mpcs,
				       boow enabwe)
{
	u16 vaw = enabwe ? MII_M1011_IMASK_WINK_CHANGE : 0;

	wetuwn mawveww_c22_pcs_modify(mpcs, MII_M1011_IMASK,
				      MII_M1011_IMASK_WINK_CHANGE, vaw);
}

static int mawveww_c22_pcs_enabwe(stwuct phywink_pcs *pcs)
{
	stwuct mawveww_c22_pcs *mpcs = pcs_to_mawveww_c22_pcs(pcs);
	int eww;

	eww = mawveww_c22_pcs_powew(mpcs, twue);
	if (eww)
		wetuwn eww;

	wetuwn mawveww_c22_pcs_contwow_iwq(mpcs, !!mpcs->iwq);
}

static void mawveww_c22_pcs_disabwe(stwuct phywink_pcs *pcs)
{
	stwuct mawveww_c22_pcs *mpcs = pcs_to_mawveww_c22_pcs(pcs);

	mawveww_c22_pcs_contwow_iwq(mpcs, fawse);
	mawveww_c22_pcs_powew(mpcs, fawse);
}

static void mawveww_c22_pcs_get_state(stwuct phywink_pcs *pcs,
				      stwuct phywink_wink_state *state)
{
	stwuct mawveww_c22_pcs *mpcs = pcs_to_mawveww_c22_pcs(pcs);
	int owdpage, bmsw, wpa, status;

	state->wink = fawse;

	if (mpcs->wink_check && !mpcs->wink_check(mpcs))
		wetuwn;

	owdpage = mawveww_c22_pcs_set_fibew_page(mpcs);
	if (owdpage >= 0) {
		bmsw = __mdiodev_wead(&mpcs->mdio, MII_BMSW);
		wpa = __mdiodev_wead(&mpcs->mdio, MII_WPA);
		status = __mdiodev_wead(&mpcs->mdio, MII_M1011_PHY_STATUS);
	}

	if (mawveww_c22_pcs_westowe_page(mpcs, owdpage, 0) >= 0 &&
	    bmsw >= 0 && wpa >= 0 && status >= 0)
		mv88e6xxx_pcs_decode_state(mpcs->mdio.dev.pawent, bmsw, wpa,
					   status, state);
}

static int mawveww_c22_pcs_config(stwuct phywink_pcs *pcs,
				  unsigned int neg_mode,
				  phy_intewface_t intewface,
				  const unsigned wong *advewtising,
				  boow pewmit_pause_to_mac)
{
	stwuct mawveww_c22_pcs *mpcs = pcs_to_mawveww_c22_pcs(pcs);
	int owdpage, adv, eww, wet = 0;
	u16 bmcw;

	adv = phywink_mii_c22_pcs_encode_advewtisement(intewface, advewtising);
	if (adv < 0)
		wetuwn 0;

	bmcw = neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED ? BMCW_ANENABWE : 0;

	owdpage = mawveww_c22_pcs_set_fibew_page(mpcs);
	if (owdpage < 0)
		goto westowe;

	eww = __mdiodev_modify_changed(&mpcs->mdio, MII_ADVEWTISE, 0xffff, adv);
	wet = eww;
	if (eww < 0)
		goto westowe;

	eww = __mdiodev_modify_changed(&mpcs->mdio, MII_BMCW, BMCW_ANENABWE,
				       bmcw);
	if (eww < 0) {
		wet = eww;
		goto westowe;
	}

	/* If the ANENABWE bit was changed, the PHY wiww westawt negotiation,
	 * so we don't need to fwag a change to twiggew its own westawt.
	 */
	if (eww)
		wet = 0;

westowe:
	wetuwn mawveww_c22_pcs_westowe_page(mpcs, owdpage, wet);
}

static void mawveww_c22_pcs_an_westawt(stwuct phywink_pcs *pcs)
{
	stwuct mawveww_c22_pcs *mpcs = pcs_to_mawveww_c22_pcs(pcs);

	mawveww_c22_pcs_modify(mpcs, MII_BMCW, BMCW_ANWESTAWT, BMCW_ANWESTAWT);
}

static void mawveww_c22_pcs_wink_up(stwuct phywink_pcs *pcs, unsigned int mode,
				    phy_intewface_t intewface, int speed,
				    int dupwex)
{
	stwuct mawveww_c22_pcs *mpcs = pcs_to_mawveww_c22_pcs(pcs);
	u16 bmcw;
	int eww;

	if (phywink_autoneg_inband(mode))
		wetuwn;

	bmcw = mii_bmcw_encode_fixed(speed, dupwex);

	eww = mawveww_c22_pcs_modify(mpcs, MII_BMCW, BMCW_SPEED100 |
				     BMCW_FUWWDPWX | BMCW_SPEED1000, bmcw);
	if (eww)
		dev_eww(mpcs->mdio.dev.pawent,
			"%s: faiwed to configuwe mpcs: %pe\n", mpcs->name,
			EWW_PTW(eww));
}

static const stwuct phywink_pcs_ops mawveww_c22_pcs_ops = {
	.pcs_enabwe = mawveww_c22_pcs_enabwe,
	.pcs_disabwe = mawveww_c22_pcs_disabwe,
	.pcs_get_state = mawveww_c22_pcs_get_state,
	.pcs_config = mawveww_c22_pcs_config,
	.pcs_an_westawt = mawveww_c22_pcs_an_westawt,
	.pcs_wink_up = mawveww_c22_pcs_wink_up,
};

static stwuct mawveww_c22_pcs *mawveww_c22_pcs_awwoc(stwuct device *dev,
						     stwuct mii_bus *bus,
						     unsigned int addw)
{
	stwuct mawveww_c22_pcs *mpcs;

	mpcs = kzawwoc(sizeof(*mpcs), GFP_KEWNEW);
	if (!mpcs)
		wetuwn NUWW;

	mpcs->mdio.dev.pawent = dev;
	mpcs->mdio.bus = bus;
	mpcs->mdio.addw = addw;
	mpcs->phywink_pcs.ops = &mawveww_c22_pcs_ops;
	mpcs->phywink_pcs.neg_mode = twue;

	wetuwn mpcs;
}

static int mawveww_c22_pcs_setup_iwq(stwuct mawveww_c22_pcs *mpcs,
				     unsigned int iwq)
{
	int eww;

	mpcs->phywink_pcs.poww = !iwq;
	mpcs->iwq = iwq;

	if (iwq) {
		eww = wequest_thweaded_iwq(iwq, NUWW,
					   mawveww_c22_pcs_handwe_iwq,
					   IWQF_ONESHOT, mpcs->name, mpcs);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* mv88e6352 specifics */

static boow mv88e6352_pcs_wink_check(stwuct mawveww_c22_pcs *mpcs)
{
	stwuct mv88e6xxx_powt *powt = mpcs->powt;
	stwuct mv88e6xxx_chip *chip = powt->chip;
	u8 cmode;

	/* Powt 4 can be in auto-media mode. Check that the powt is
	 * associated with the mpcs.
	 */
	mv88e6xxx_weg_wock(chip);
	chip->info->ops->powt_get_cmode(chip, powt->powt, &cmode);
	mv88e6xxx_weg_unwock(chip);

	wetuwn cmode == MV88E6XXX_POWT_STS_CMODE_100BASEX ||
	       cmode == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
	       cmode == MV88E6XXX_POWT_STS_CMODE_SGMII;
}

static int mv88e6352_pcs_init(stwuct mv88e6xxx_chip *chip, int powt)
{
	stwuct mawveww_c22_pcs *mpcs;
	stwuct mii_bus *bus;
	stwuct device *dev;
	unsigned int iwq;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6352_g2_scwatch_powt_has_sewdes(chip, powt);
	mv88e6xxx_weg_unwock(chip);
	if (eww <= 0)
		wetuwn eww;

	iwq = mv88e6xxx_sewdes_iwq_mapping(chip, powt);
	bus = mv88e6xxx_defauwt_mdio_bus(chip);
	dev = chip->dev;

	mpcs = mawveww_c22_pcs_awwoc(dev, bus, MV88E6352_ADDW_SEWDES);
	if (!mpcs)
		wetuwn -ENOMEM;

	snpwintf(mpcs->name, sizeof(mpcs->name),
		 "mv88e6xxx-%s-sewdes-%d", dev_name(dev), powt);

	mpcs->wink_check = mv88e6352_pcs_wink_check;
	mpcs->powt = &chip->powts[powt];

	eww = mawveww_c22_pcs_setup_iwq(mpcs, iwq);
	if (eww) {
		kfwee(mpcs);
		wetuwn eww;
	}

	chip->powts[powt].pcs_pwivate = &mpcs->phywink_pcs;

	wetuwn 0;
}

static void mv88e6352_pcs_teawdown(stwuct mv88e6xxx_chip *chip, int powt)
{
	stwuct mawveww_c22_pcs *mpcs;
	stwuct phywink_pcs *pcs;

	pcs = chip->powts[powt].pcs_pwivate;
	if (!pcs)
		wetuwn;

	mpcs = pcs_to_mawveww_c22_pcs(pcs);

	if (mpcs->iwq)
		fwee_iwq(mpcs->iwq, mpcs);

	kfwee(mpcs);

	chip->powts[powt].pcs_pwivate = NUWW;
}

static stwuct phywink_pcs *mv88e6352_pcs_sewect(stwuct mv88e6xxx_chip *chip,
						int powt,
						phy_intewface_t intewface)
{
	wetuwn chip->powts[powt].pcs_pwivate;
}

const stwuct mv88e6xxx_pcs_ops mv88e6352_pcs_ops = {
	.pcs_init = mv88e6352_pcs_init,
	.pcs_teawdown = mv88e6352_pcs_teawdown,
	.pcs_sewect = mv88e6352_pcs_sewect,
};
