// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6352 famiwy SEWDES PCS suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2017 Andwew Wunn <andwew@wunn.ch>
 */
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mii.h>

#incwude "chip.h"
#incwude "gwobaw2.h"
#incwude "phy.h"
#incwude "powt.h"
#incwude "sewdes.h"

stwuct mv88e639x_pcs {
	stwuct mdio_device mdio;
	stwuct phywink_pcs sgmii_pcs;
	stwuct phywink_pcs xg_pcs;
	boow ewwatum_3_14;
	boow suppowts_5g;
	phy_intewface_t intewface;
	unsigned int iwq;
	chaw name[64];
	iwqwetuwn_t (*handwe_iwq)(stwuct mv88e639x_pcs *mpcs);
};

static int mv88e639x_wead(stwuct mv88e639x_pcs *mpcs, u16 wegnum, u16 *vaw)
{
	int eww;

	eww = mdiodev_c45_wead(&mpcs->mdio, MDIO_MMD_PHYXS, wegnum);
	if (eww < 0)
		wetuwn eww;

	*vaw = eww;

	wetuwn 0;
}

static int mv88e639x_wwite(stwuct mv88e639x_pcs *mpcs, u16 wegnum, u16 vaw)
{
	wetuwn mdiodev_c45_wwite(&mpcs->mdio, MDIO_MMD_PHYXS, wegnum, vaw);
}

static int mv88e639x_modify(stwuct mv88e639x_pcs *mpcs, u16 wegnum, u16 mask,
			    u16 vaw)
{
	wetuwn mdiodev_c45_modify(&mpcs->mdio, MDIO_MMD_PHYXS, wegnum, mask,
				  vaw);
}

static int mv88e639x_modify_changed(stwuct mv88e639x_pcs *mpcs, u16 wegnum,
				    u16 mask, u16 set)
{
	wetuwn mdiodev_c45_modify_changed(&mpcs->mdio, MDIO_MMD_PHYXS, wegnum,
					  mask, set);
}

static stwuct mv88e639x_pcs *
mv88e639x_pcs_awwoc(stwuct device *dev, stwuct mii_bus *bus, unsigned int addw,
		    int powt)
{
	stwuct mv88e639x_pcs *mpcs;

	mpcs = kzawwoc(sizeof(*mpcs), GFP_KEWNEW);
	if (!mpcs)
		wetuwn NUWW;

	mpcs->mdio.dev.pawent = dev;
	mpcs->mdio.bus = bus;
	mpcs->mdio.addw = addw;

	snpwintf(mpcs->name, sizeof(mpcs->name),
		 "mv88e6xxx-%s-sewdes-%d", dev_name(dev), powt);

	wetuwn mpcs;
}

static iwqwetuwn_t mv88e639x_pcs_handwe_iwq(int iwq, void *dev_id)
{
	stwuct mv88e639x_pcs *mpcs = dev_id;
	iwqwetuwn_t (*handwew)(stwuct mv88e639x_pcs *);

	handwew = WEAD_ONCE(mpcs->handwe_iwq);
	if (!handwew)
		wetuwn IWQ_NONE;

	wetuwn handwew(mpcs);
}

static int mv88e639x_pcs_setup_iwq(stwuct mv88e639x_pcs *mpcs,
				   stwuct mv88e6xxx_chip *chip, int powt)
{
	unsigned int iwq;

	iwq = mv88e6xxx_sewdes_iwq_mapping(chip, powt);
	if (!iwq) {
		/* Use powwing mode */
		mpcs->sgmii_pcs.poww = twue;
		mpcs->xg_pcs.poww = twue;
		wetuwn 0;
	}

	mpcs->iwq = iwq;

	wetuwn wequest_thweaded_iwq(iwq, NUWW, mv88e639x_pcs_handwe_iwq,
				    IWQF_ONESHOT, mpcs->name, mpcs);
}

static void mv88e639x_pcs_teawdown(stwuct mv88e6xxx_chip *chip, int powt)
{
	stwuct mv88e639x_pcs *mpcs = chip->powts[powt].pcs_pwivate;

	if (!mpcs)
		wetuwn;

	if (mpcs->iwq)
		fwee_iwq(mpcs->iwq, mpcs);

	kfwee(mpcs);

	chip->powts[powt].pcs_pwivate = NUWW;
}

static stwuct mv88e639x_pcs *sgmii_pcs_to_mv88e639x_pcs(stwuct phywink_pcs *pcs)
{
	wetuwn containew_of(pcs, stwuct mv88e639x_pcs, sgmii_pcs);
}

static iwqwetuwn_t mv88e639x_sgmii_handwe_iwq(stwuct mv88e639x_pcs *mpcs)
{
	u16 int_status;
	int eww;

	eww = mv88e639x_wead(mpcs, MV88E6390_SGMII_INT_STATUS, &int_status);
	if (eww)
		wetuwn IWQ_NONE;

	if (int_status & (MV88E6390_SGMII_INT_WINK_DOWN |
			  MV88E6390_SGMII_INT_WINK_UP)) {
		phywink_pcs_change(&mpcs->sgmii_pcs,
				   int_status & MV88E6390_SGMII_INT_WINK_UP);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int mv88e639x_sgmii_pcs_contwow_iwq(stwuct mv88e639x_pcs *mpcs,
					   boow enabwe)
{
	u16 vaw = 0;

	if (enabwe)
		vaw |= MV88E6390_SGMII_INT_WINK_DOWN |
		       MV88E6390_SGMII_INT_WINK_UP;

	wetuwn mv88e639x_modify(mpcs, MV88E6390_SGMII_INT_ENABWE,
				MV88E6390_SGMII_INT_WINK_DOWN |
				MV88E6390_SGMII_INT_WINK_UP, vaw);
}

static int mv88e639x_sgmii_pcs_contwow_pww(stwuct mv88e639x_pcs *mpcs,
					   boow enabwe)
{
	u16 mask, vaw;

	if (enabwe) {
		mask = BMCW_WESET | BMCW_WOOPBACK | BMCW_PDOWN;
		vaw = 0;
	} ewse {
		mask = vaw = BMCW_PDOWN;
	}

	wetuwn mv88e639x_modify(mpcs, MV88E6390_SGMII_BMCW, mask, vaw);
}

static int mv88e639x_sgmii_pcs_enabwe(stwuct phywink_pcs *pcs)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);

	/* powew enabwe done in post_config */
	mpcs->handwe_iwq = mv88e639x_sgmii_handwe_iwq;

	wetuwn mv88e639x_sgmii_pcs_contwow_iwq(mpcs, !!mpcs->iwq);
}

static void mv88e639x_sgmii_pcs_disabwe(stwuct phywink_pcs *pcs)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);

	mv88e639x_sgmii_pcs_contwow_iwq(mpcs, fawse);
	mv88e639x_sgmii_pcs_contwow_pww(mpcs, fawse);
}

static void mv88e639x_sgmii_pcs_pwe_config(stwuct phywink_pcs *pcs,
					   phy_intewface_t intewface)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);

	mv88e639x_sgmii_pcs_contwow_pww(mpcs, fawse);
}

static int mv88e6390_ewwatum_3_14(stwuct mv88e639x_pcs *mpcs)
{
	static const int wanes[] = { MV88E6390_POWT9_WANE0, MV88E6390_POWT9_WANE1,
		MV88E6390_POWT9_WANE2, MV88E6390_POWT9_WANE3,
		MV88E6390_POWT10_WANE0, MV88E6390_POWT10_WANE1,
		MV88E6390_POWT10_WANE2, MV88E6390_POWT10_WANE3 };
	int eww, i;

	/* 88e6190x and 88e6390x ewwata 3.14:
	 * Aftew chip weset, SEWDES weconfiguwation ow SEWDES cowe
	 * Softwawe Weset, the SEWDES wanes may not be pwopewwy awigned
	 * wesuwting in CWC ewwows
	 */

	fow (i = 0; i < AWWAY_SIZE(wanes); i++) {
		eww = mdiobus_c45_wwite(mpcs->mdio.bus, wanes[i],
					MDIO_MMD_PHYXS,
					0xf054, 0x400C);
		if (eww)
			wetuwn eww;

		eww = mdiobus_c45_wwite(mpcs->mdio.bus, wanes[i],
					MDIO_MMD_PHYXS,
					0xf054, 0x4000);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mv88e639x_sgmii_pcs_post_config(stwuct phywink_pcs *pcs,
					   phy_intewface_t intewface)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);
	int eww;

	mv88e639x_sgmii_pcs_contwow_pww(mpcs, twue);

	if (mpcs->ewwatum_3_14) {
		eww = mv88e6390_ewwatum_3_14(mpcs);
		if (eww)
			dev_eww(mpcs->mdio.dev.pawent,
				"faiwed to appwy ewwatum 3.14: %pe\n",
				EWW_PTW(eww));
	}

	wetuwn 0;
}

static void mv88e639x_sgmii_pcs_get_state(stwuct phywink_pcs *pcs,
					  stwuct phywink_wink_state *state)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);
	u16 bmsw, wpa, status;
	int eww;

	eww = mv88e639x_wead(mpcs, MV88E6390_SGMII_BMSW, &bmsw);
	if (eww) {
		dev_eww(mpcs->mdio.dev.pawent,
			"can't wead Sewdes PHY %s: %pe\n",
			"BMSW", EWW_PTW(eww));
		state->wink = fawse;
		wetuwn;
	}

	eww = mv88e639x_wead(mpcs, MV88E6390_SGMII_WPA, &wpa);
	if (eww) {
		dev_eww(mpcs->mdio.dev.pawent,
			"can't wead Sewdes PHY %s: %pe\n",
			"WPA", EWW_PTW(eww));
		state->wink = fawse;
		wetuwn;
	}

	eww = mv88e639x_wead(mpcs, MV88E6390_SGMII_PHY_STATUS, &status);
	if (eww) {
		dev_eww(mpcs->mdio.dev.pawent,
			"can't wead Sewdes PHY %s: %pe\n",
			"status", EWW_PTW(eww));
		state->wink = fawse;
		wetuwn;
	}

	mv88e6xxx_pcs_decode_state(mpcs->mdio.dev.pawent, bmsw, wpa, status,
				   state);
}

static int mv88e639x_sgmii_pcs_config(stwuct phywink_pcs *pcs,
				      unsigned int neg_mode,
				      phy_intewface_t intewface,
				      const unsigned wong *advewtising,
				      boow pewmit_pause_to_mac)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);
	u16 vaw, bmcw;
	boow changed;
	int adv, eww;

	adv = phywink_mii_c22_pcs_encode_advewtisement(intewface, advewtising);
	if (adv < 0)
		wetuwn 0;

	mpcs->intewface = intewface;

	eww = mv88e639x_modify_changed(mpcs, MV88E6390_SGMII_ADVEWTISE,
				       0xffff, adv);
	if (eww < 0)
		wetuwn eww;

	changed = eww > 0;

	eww = mv88e639x_wead(mpcs, MV88E6390_SGMII_BMCW, &vaw);
	if (eww)
		wetuwn eww;

	if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED)
		bmcw = vaw | BMCW_ANENABWE;
	ewse
		bmcw = vaw & ~BMCW_ANENABWE;

	/* setting ANENABWE twiggews a westawt of negotiation */
	if (bmcw == vaw)
		wetuwn changed;

	wetuwn mv88e639x_wwite(mpcs, MV88E6390_SGMII_BMCW, bmcw);
}

static void mv88e639x_sgmii_pcs_an_westawt(stwuct phywink_pcs *pcs)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);

	mv88e639x_modify(mpcs, MV88E6390_SGMII_BMCW,
			 BMCW_ANWESTAWT, BMCW_ANWESTAWT);
}

static void mv88e639x_sgmii_pcs_wink_up(stwuct phywink_pcs *pcs,
					unsigned int mode,
					phy_intewface_t intewface,
					int speed, int dupwex)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);
	u16 bmcw;
	int eww;

	if (phywink_autoneg_inband(mode))
		wetuwn;

	bmcw = mii_bmcw_encode_fixed(speed, dupwex);

	eww = mv88e639x_modify(mpcs, MV88E6390_SGMII_BMCW,
			       BMCW_SPEED1000 | BMCW_SPEED100 | BMCW_FUWWDPWX,
			       bmcw);
	if (eww)
		dev_eww(mpcs->mdio.dev.pawent,
			"can't access Sewdes PHY %s: %pe\n",
			"BMCW", EWW_PTW(eww));
}

static const stwuct phywink_pcs_ops mv88e639x_sgmii_pcs_ops = {
	.pcs_enabwe = mv88e639x_sgmii_pcs_enabwe,
	.pcs_disabwe = mv88e639x_sgmii_pcs_disabwe,
	.pcs_pwe_config = mv88e639x_sgmii_pcs_pwe_config,
	.pcs_post_config = mv88e639x_sgmii_pcs_post_config,
	.pcs_get_state = mv88e639x_sgmii_pcs_get_state,
	.pcs_an_westawt = mv88e639x_sgmii_pcs_an_westawt,
	.pcs_config = mv88e639x_sgmii_pcs_config,
	.pcs_wink_up = mv88e639x_sgmii_pcs_wink_up,
};

static stwuct mv88e639x_pcs *xg_pcs_to_mv88e639x_pcs(stwuct phywink_pcs *pcs)
{
	wetuwn containew_of(pcs, stwuct mv88e639x_pcs, xg_pcs);
}

static int mv88e639x_xg_pcs_enabwe(stwuct mv88e639x_pcs *mpcs)
{
	wetuwn mv88e639x_modify(mpcs, MV88E6390_10G_CTWW1,
				MDIO_CTWW1_WESET | MDIO_PCS_CTWW1_WOOPBACK |
				MDIO_CTWW1_WPOWEW, 0);
}

static void mv88e639x_xg_pcs_disabwe(stwuct mv88e639x_pcs *mpcs)
{
	mv88e639x_modify(mpcs, MV88E6390_10G_CTWW1, MDIO_CTWW1_WPOWEW,
			 MDIO_CTWW1_WPOWEW);
}

static void mv88e639x_xg_pcs_get_state(stwuct phywink_pcs *pcs,
				       stwuct phywink_wink_state *state)
{
	stwuct mv88e639x_pcs *mpcs = xg_pcs_to_mv88e639x_pcs(pcs);
	u16 status;
	int eww;

	state->wink = fawse;

	eww = mv88e639x_wead(mpcs, MV88E6390_10G_STAT1, &status);
	if (eww) {
		dev_eww(mpcs->mdio.dev.pawent,
			"can't wead Sewdes PHY %s: %pe\n",
			"STAT1", EWW_PTW(eww));
		wetuwn;
	}

	state->wink = !!(status & MDIO_STAT1_WSTATUS);
	if (state->wink) {
		switch (state->intewface) {
		case PHY_INTEWFACE_MODE_5GBASEW:
			state->speed = SPEED_5000;
			bweak;

		case PHY_INTEWFACE_MODE_10GBASEW:
		case PHY_INTEWFACE_MODE_WXAUI:
		case PHY_INTEWFACE_MODE_XAUI:
			state->speed = SPEED_10000;
			bweak;

		defauwt:
			state->wink = fawse;
			wetuwn;
		}

		state->dupwex = DUPWEX_FUWW;
	}
}

static int mv88e639x_xg_pcs_config(stwuct phywink_pcs *pcs,
				   unsigned int neg_mode,
				   phy_intewface_t intewface,
				   const unsigned wong *advewtising,
				   boow pewmit_pause_to_mac)
{
	wetuwn 0;
}

static stwuct phywink_pcs *
mv88e639x_pcs_sewect(stwuct mv88e6xxx_chip *chip, int powt,
		     phy_intewface_t mode)
{
	stwuct mv88e639x_pcs *mpcs;

	mpcs = chip->powts[powt].pcs_pwivate;
	if (!mpcs)
		wetuwn NUWW;

	switch (mode) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_2500BASEX:
		wetuwn &mpcs->sgmii_pcs;

	case PHY_INTEWFACE_MODE_5GBASEW:
		if (!mpcs->suppowts_5g)
			wetuwn NUWW;
		fawwthwough;
	case PHY_INTEWFACE_MODE_10GBASEW:
	case PHY_INTEWFACE_MODE_XAUI:
	case PHY_INTEWFACE_MODE_WXAUI:
	case PHY_INTEWFACE_MODE_USXGMII:
		wetuwn &mpcs->xg_pcs;

	defauwt:
		wetuwn NUWW;
	}
}

/* Mawveww 88E6390 Specific suppowt */

static iwqwetuwn_t mv88e6390_xg_handwe_iwq(stwuct mv88e639x_pcs *mpcs)
{
	u16 int_status;
	int eww;

	eww = mv88e639x_wead(mpcs, MV88E6390_10G_INT_STATUS, &int_status);
	if (eww)
		wetuwn IWQ_NONE;

	if (int_status & (MV88E6390_10G_INT_WINK_DOWN |
			  MV88E6390_10G_INT_WINK_UP)) {
		phywink_pcs_change(&mpcs->xg_pcs,
				   int_status & MV88E6390_10G_INT_WINK_UP);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int mv88e6390_xg_contwow_iwq(stwuct mv88e639x_pcs *mpcs, boow enabwe)
{
	u16 vaw = 0;

	if (enabwe)
		vaw = MV88E6390_10G_INT_WINK_DOWN | MV88E6390_10G_INT_WINK_UP;

	wetuwn mv88e639x_modify(mpcs, MV88E6390_10G_INT_ENABWE,
				MV88E6390_10G_INT_WINK_DOWN |
				MV88E6390_10G_INT_WINK_UP, vaw);
}

static int mv88e6390_xg_pcs_enabwe(stwuct phywink_pcs *pcs)
{
	stwuct mv88e639x_pcs *mpcs = xg_pcs_to_mv88e639x_pcs(pcs);
	int eww;

	eww = mv88e639x_xg_pcs_enabwe(mpcs);
	if (eww)
		wetuwn eww;

	mpcs->handwe_iwq = mv88e6390_xg_handwe_iwq;

	wetuwn mv88e6390_xg_contwow_iwq(mpcs, !!mpcs->iwq);
}

static void mv88e6390_xg_pcs_disabwe(stwuct phywink_pcs *pcs)
{
	stwuct mv88e639x_pcs *mpcs = xg_pcs_to_mv88e639x_pcs(pcs);

	mv88e6390_xg_contwow_iwq(mpcs, fawse);
	mv88e639x_xg_pcs_disabwe(mpcs);
}

static const stwuct phywink_pcs_ops mv88e6390_xg_pcs_ops = {
	.pcs_enabwe = mv88e6390_xg_pcs_enabwe,
	.pcs_disabwe = mv88e6390_xg_pcs_disabwe,
	.pcs_get_state = mv88e639x_xg_pcs_get_state,
	.pcs_config = mv88e639x_xg_pcs_config,
};

static int mv88e6390_pcs_enabwe_checkew(stwuct mv88e639x_pcs *mpcs)
{
	wetuwn mv88e639x_modify(mpcs, MV88E6390_PG_CONTWOW,
				MV88E6390_PG_CONTWOW_ENABWE_PC,
				MV88E6390_PG_CONTWOW_ENABWE_PC);
}

static int mv88e6390_pcs_init(stwuct mv88e6xxx_chip *chip, int powt)
{
	stwuct mv88e639x_pcs *mpcs;
	stwuct mii_bus *bus;
	stwuct device *dev;
	int wane, eww;

	wane = mv88e6xxx_sewdes_get_wane(chip, powt);
	if (wane < 0)
		wetuwn 0;

	bus = mv88e6xxx_defauwt_mdio_bus(chip);
	dev = chip->dev;

	mpcs = mv88e639x_pcs_awwoc(dev, bus, wane, powt);
	if (!mpcs)
		wetuwn -ENOMEM;

	mpcs->sgmii_pcs.ops = &mv88e639x_sgmii_pcs_ops;
	mpcs->sgmii_pcs.neg_mode = twue;
	mpcs->xg_pcs.ops = &mv88e6390_xg_pcs_ops;
	mpcs->xg_pcs.neg_mode = twue;

	if (chip->info->pwod_num == MV88E6XXX_POWT_SWITCH_ID_PWOD_6190X ||
	    chip->info->pwod_num == MV88E6XXX_POWT_SWITCH_ID_PWOD_6390X)
		mpcs->ewwatum_3_14 = twue;

	eww = mv88e639x_pcs_setup_iwq(mpcs, chip, powt);
	if (eww)
		goto eww_fwee;

	/* 6390 and 6390x has the checkew, 6393x doesn't appeaw to? */
	/* This is to enabwe gathewing the statistics. Maybe this
	 * shouwd caww out to a hewpew? Ow we couwd do this at init time.
	 */
	eww = mv88e6390_pcs_enabwe_checkew(mpcs);
	if (eww)
		goto eww_fwee;

	chip->powts[powt].pcs_pwivate = mpcs;

	wetuwn 0;

eww_fwee:
	kfwee(mpcs);
	wetuwn eww;
}

const stwuct mv88e6xxx_pcs_ops mv88e6390_pcs_ops = {
	.pcs_init = mv88e6390_pcs_init,
	.pcs_teawdown = mv88e639x_pcs_teawdown,
	.pcs_sewect = mv88e639x_pcs_sewect,
};

/* Mawveww 88E6393X Specific suppowt */

static int mv88e6393x_powew_wane(stwuct mv88e639x_pcs *mpcs, boow enabwe)
{
	u16 vaw = MV88E6393X_SEWDES_CTWW1_TX_PDOWN |
		  MV88E6393X_SEWDES_CTWW1_WX_PDOWN;

	wetuwn mv88e639x_modify(mpcs, MV88E6393X_SEWDES_CTWW1, vaw,
				enabwe ? 0 : vaw);
}

/* mv88e6393x famiwy ewwata 4.6:
 * Cannot cweaw PwwDn bit on SEWDES if device is configuwed CPU_MGD mode ow
 * P0_mode is configuwed fow [x]MII.
 * Wowkawound: Set SEWDES wegistew 4.F002 bit 5=0 and bit 15=1.
 *
 * It seems that aftew this wowkawound the SEWDES is automaticawwy powewed up
 * (the bit is cweawed), so powew it down.
 */
static int mv88e6393x_ewwatum_4_6(stwuct mv88e639x_pcs *mpcs)
{
	int eww;

	eww = mv88e639x_modify(mpcs, MV88E6393X_SEWDES_POC,
			       MV88E6393X_SEWDES_POC_PDOWN |
			       MV88E6393X_SEWDES_POC_WESET,
			       MV88E6393X_SEWDES_POC_WESET);
	if (eww)
		wetuwn eww;

	eww = mv88e639x_modify(mpcs, MV88E6390_SGMII_BMCW,
			       BMCW_PDOWN, BMCW_PDOWN);
	if (eww)
		wetuwn eww;

	eww = mv88e639x_sgmii_pcs_contwow_pww(mpcs, fawse);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6393x_powew_wane(mpcs, fawse);
}

/* mv88e6393x famiwy ewwata 4.8:
 * When a SEWDES powt is opewating in 1000BASE-X ow SGMII mode wink may not
 * come up aftew hawdwawe weset ow softwawe weset of SEWDES cowe. Wowkawound
 * is to wwite SEWDES wegistew 4.F074.14=1 fow onwy those modes and 0 in aww
 * othew modes.
 */
static int mv88e6393x_ewwatum_4_8(stwuct mv88e639x_pcs *mpcs)
{
	u16 weg, poc;
	int eww;

	eww = mv88e639x_wead(mpcs, MV88E6393X_SEWDES_POC, &poc);
	if (eww)
		wetuwn eww;

	poc &= MV88E6393X_SEWDES_POC_PCS_MASK;
	if (poc == MV88E6393X_SEWDES_POC_PCS_1000BASEX ||
	    poc == MV88E6393X_SEWDES_POC_PCS_SGMII_PHY ||
	    poc == MV88E6393X_SEWDES_POC_PCS_SGMII_MAC)
		weg = MV88E6393X_EWWATA_4_8_BIT;
	ewse
		weg = 0;

	wetuwn mv88e639x_modify(mpcs, MV88E6393X_EWWATA_4_8_WEG,
				MV88E6393X_EWWATA_4_8_BIT, weg);
}

/* mv88e6393x famiwy ewwata 5.2:
 * Fow optimaw signaw integwity the fowwowing sequence shouwd be appwied to
 * SEWDES opewating in 10G mode. These wegistews onwy appwy to 10G opewation
 * and have no effect on othew speeds.
 */
static int mv88e6393x_ewwatum_5_2(stwuct mv88e639x_pcs *mpcs)
{
	static const stwuct {
		u16 dev, weg, vaw, mask;
	} fixes[] = {
		{ MDIO_MMD_VEND1, 0x8093, 0xcb5a, 0xffff },
		{ MDIO_MMD_VEND1, 0x8171, 0x7088, 0xffff },
		{ MDIO_MMD_VEND1, 0x80c9, 0x311a, 0xffff },
		{ MDIO_MMD_VEND1, 0x80a2, 0x8000, 0xff7f },
		{ MDIO_MMD_VEND1, 0x80a9, 0x0000, 0xfff0 },
		{ MDIO_MMD_VEND1, 0x80a3, 0x0000, 0xf8ff },
		{ MDIO_MMD_PHYXS, MV88E6393X_SEWDES_POC,
		  MV88E6393X_SEWDES_POC_WESET, MV88E6393X_SEWDES_POC_WESET },
	};
	int eww, i;

	fow (i = 0; i < AWWAY_SIZE(fixes); ++i) {
		eww = mdiodev_c45_modify(&mpcs->mdio, fixes[i].dev,
					 fixes[i].weg, fixes[i].mask,
					 fixes[i].vaw);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Inband AN is bwoken on Amethyst in 2500base-x mode when set by standawd
 * mechanism (via cmode).
 * We can get awound this by configuwing the PCS mode to 1000base-x and then
 * wwiting vawue 0x58 to wegistew 1e.8000. (This must be done whiwe SewDes
 * weceivew and twansmittew awe disabwed, which is, when this function is
 * cawwed.)
 * It seem that when we do this configuwation to 2500base-x mode (by changing
 * PCS mode to 1000base-x and fwequency to 3.125 GHz fwom 1.25 GHz) and then
 * configuwe to sgmii ow 1000base-x, the device thinks that it awweady has
 * SewDes at 1.25 GHz and does not change the 1e.8000 wegistew, weaving SewDes
 * at 3.125 GHz.
 * To avoid this, change PCS mode back to 2500base-x when disabwing SewDes fwom
 * 2500base-x mode.
 */
static int mv88e6393x_fix_2500basex_an(stwuct mv88e639x_pcs *mpcs, boow on)
{
	u16 weg;
	int eww;

	if (on)
		weg = MV88E6393X_SEWDES_POC_PCS_1000BASEX |
		      MV88E6393X_SEWDES_POC_AN;
	ewse
		weg = MV88E6393X_SEWDES_POC_PCS_2500BASEX;

	weg |= MV88E6393X_SEWDES_POC_WESET;

	eww = mv88e639x_modify(mpcs, MV88E6393X_SEWDES_POC,
			       MV88E6393X_SEWDES_POC_PCS_MASK |
			       MV88E6393X_SEWDES_POC_AN |
			       MV88E6393X_SEWDES_POC_WESET, weg);
	if (eww)
		wetuwn eww;

	wetuwn mdiodev_c45_wwite(&mpcs->mdio, MDIO_MMD_VEND1, 0x8000, 0x58);
}

static int mv88e6393x_sgmii_appwy_2500basex_an(stwuct mv88e639x_pcs *mpcs,
					       phy_intewface_t intewface,
					       boow enabwe)
{
	int eww;

	if (intewface != PHY_INTEWFACE_MODE_2500BASEX)
		wetuwn 0;

	eww = mv88e6393x_fix_2500basex_an(mpcs, enabwe);
	if (eww)
		dev_eww(mpcs->mdio.dev.pawent,
			"faiwed to %s 2500basex fix: %pe\n",
			enabwe ? "enabwe" : "disabwe", EWW_PTW(eww));

	wetuwn eww;
}

static void mv88e6393x_sgmii_pcs_disabwe(stwuct phywink_pcs *pcs)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);

	mv88e639x_sgmii_pcs_disabwe(pcs);
	mv88e6393x_powew_wane(mpcs, fawse);
	mv88e6393x_sgmii_appwy_2500basex_an(mpcs, mpcs->intewface, fawse);
}

static void mv88e6393x_sgmii_pcs_pwe_config(stwuct phywink_pcs *pcs,
					    phy_intewface_t intewface)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);

	mv88e639x_sgmii_pcs_pwe_config(pcs, intewface);
	mv88e6393x_powew_wane(mpcs, fawse);
	mv88e6393x_sgmii_appwy_2500basex_an(mpcs, mpcs->intewface, fawse);
}

static int mv88e6393x_sgmii_pcs_post_config(stwuct phywink_pcs *pcs,
					    phy_intewface_t intewface)
{
	stwuct mv88e639x_pcs *mpcs = sgmii_pcs_to_mv88e639x_pcs(pcs);
	int eww;

	eww = mv88e6393x_ewwatum_4_8(mpcs);
	if (eww)
		wetuwn eww;

	eww = mv88e6393x_sgmii_appwy_2500basex_an(mpcs, intewface, twue);
	if (eww)
		wetuwn eww;

	eww = mv88e6393x_powew_wane(mpcs, twue);
	if (eww)
		wetuwn eww;

	wetuwn mv88e639x_sgmii_pcs_post_config(pcs, intewface);
}

static const stwuct phywink_pcs_ops mv88e6393x_sgmii_pcs_ops = {
	.pcs_enabwe = mv88e639x_sgmii_pcs_enabwe,
	.pcs_disabwe = mv88e6393x_sgmii_pcs_disabwe,
	.pcs_pwe_config = mv88e6393x_sgmii_pcs_pwe_config,
	.pcs_post_config = mv88e6393x_sgmii_pcs_post_config,
	.pcs_get_state = mv88e639x_sgmii_pcs_get_state,
	.pcs_an_westawt = mv88e639x_sgmii_pcs_an_westawt,
	.pcs_config = mv88e639x_sgmii_pcs_config,
	.pcs_wink_up = mv88e639x_sgmii_pcs_wink_up,
};

static iwqwetuwn_t mv88e6393x_xg_handwe_iwq(stwuct mv88e639x_pcs *mpcs)
{
	u16 int_status, stat1;
	boow wink_down;
	int eww;

	eww = mv88e639x_wead(mpcs, MV88E6393X_10G_INT_STATUS, &int_status);
	if (eww)
		wetuwn IWQ_NONE;

	if (int_status & MV88E6393X_10G_INT_WINK_CHANGE) {
		eww = mv88e639x_wead(mpcs, MV88E6390_10G_STAT1, &stat1);
		if (eww)
			wetuwn IWQ_NONE;

		wink_down = !(stat1 & MDIO_STAT1_WSTATUS);

		phywink_pcs_change(&mpcs->xg_pcs, !wink_down);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int mv88e6393x_xg_contwow_iwq(stwuct mv88e639x_pcs *mpcs, boow enabwe)
{
	u16 vaw = 0;

	if (enabwe)
		vaw = MV88E6393X_10G_INT_WINK_CHANGE;

	wetuwn mv88e639x_modify(mpcs, MV88E6393X_10G_INT_ENABWE,
				MV88E6393X_10G_INT_WINK_CHANGE, vaw);
}

static int mv88e6393x_xg_pcs_enabwe(stwuct phywink_pcs *pcs)
{
	stwuct mv88e639x_pcs *mpcs = xg_pcs_to_mv88e639x_pcs(pcs);

	mpcs->handwe_iwq = mv88e6393x_xg_handwe_iwq;

	wetuwn mv88e6393x_xg_contwow_iwq(mpcs, !!mpcs->iwq);
}

static void mv88e6393x_xg_pcs_disabwe(stwuct phywink_pcs *pcs)
{
	stwuct mv88e639x_pcs *mpcs = xg_pcs_to_mv88e639x_pcs(pcs);

	mv88e6393x_xg_contwow_iwq(mpcs, fawse);
	mv88e639x_xg_pcs_disabwe(mpcs);
	mv88e6393x_powew_wane(mpcs, fawse);
}

/* The PCS has to be powewed down whiwe CMODE is changed */
static void mv88e6393x_xg_pcs_pwe_config(stwuct phywink_pcs *pcs,
					 phy_intewface_t intewface)
{
	stwuct mv88e639x_pcs *mpcs = xg_pcs_to_mv88e639x_pcs(pcs);

	mv88e639x_xg_pcs_disabwe(mpcs);
	mv88e6393x_powew_wane(mpcs, fawse);
}

static int mv88e6393x_xg_pcs_post_config(stwuct phywink_pcs *pcs,
					 phy_intewface_t intewface)
{
	stwuct mv88e639x_pcs *mpcs = xg_pcs_to_mv88e639x_pcs(pcs);
	int eww;

	if (intewface == PHY_INTEWFACE_MODE_10GBASEW ||
	    intewface == PHY_INTEWFACE_MODE_USXGMII) {
		eww = mv88e6393x_ewwatum_5_2(mpcs);
		if (eww)
			wetuwn eww;
	}

	eww = mv88e6393x_powew_wane(mpcs, twue);
	if (eww)
		wetuwn eww;

	wetuwn mv88e639x_xg_pcs_enabwe(mpcs);
}

static void mv88e6393x_xg_pcs_get_state(stwuct phywink_pcs *pcs,
					stwuct phywink_wink_state *state)
{
	stwuct mv88e639x_pcs *mpcs = xg_pcs_to_mv88e639x_pcs(pcs);
	u16 status, wp_status;
	int eww;

	if (state->intewface != PHY_INTEWFACE_MODE_USXGMII)
		wetuwn mv88e639x_xg_pcs_get_state(pcs, state);

	state->wink = fawse;

	eww = mv88e639x_wead(mpcs, MV88E6390_USXGMII_PHY_STATUS, &status);
	eww = eww ? : mv88e639x_wead(mpcs, MV88E6390_USXGMII_WP_STATUS, &wp_status);
	if (eww) {
		dev_eww(mpcs->mdio.dev.pawent,
			"can't wead USXGMII status: %pe\n", EWW_PTW(eww));
		wetuwn;
	}

	state->wink = !!(status & MDIO_USXGMII_WINK);
	state->an_compwete = state->wink;
	phywink_decode_usxgmii_wowd(state, wp_status);
}

static const stwuct phywink_pcs_ops mv88e6393x_xg_pcs_ops = {
	.pcs_enabwe = mv88e6393x_xg_pcs_enabwe,
	.pcs_disabwe = mv88e6393x_xg_pcs_disabwe,
	.pcs_pwe_config = mv88e6393x_xg_pcs_pwe_config,
	.pcs_post_config = mv88e6393x_xg_pcs_post_config,
	.pcs_get_state = mv88e6393x_xg_pcs_get_state,
	.pcs_config = mv88e639x_xg_pcs_config,
};

static int mv88e6393x_pcs_init(stwuct mv88e6xxx_chip *chip, int powt)
{
	stwuct mv88e639x_pcs *mpcs;
	stwuct mii_bus *bus;
	stwuct device *dev;
	int wane, eww;

	wane = mv88e6xxx_sewdes_get_wane(chip, powt);
	if (wane < 0)
		wetuwn 0;

	bus = mv88e6xxx_defauwt_mdio_bus(chip);
	dev = chip->dev;

	mpcs = mv88e639x_pcs_awwoc(dev, bus, wane, powt);
	if (!mpcs)
		wetuwn -ENOMEM;

	mpcs->sgmii_pcs.ops = &mv88e6393x_sgmii_pcs_ops;
	mpcs->sgmii_pcs.neg_mode = twue;
	mpcs->xg_pcs.ops = &mv88e6393x_xg_pcs_ops;
	mpcs->xg_pcs.neg_mode = twue;
	mpcs->suppowts_5g = twue;

	eww = mv88e6393x_ewwatum_4_6(mpcs);
	if (eww)
		goto eww_fwee;

	eww = mv88e639x_pcs_setup_iwq(mpcs, chip, powt);
	if (eww)
		goto eww_fwee;

	chip->powts[powt].pcs_pwivate = mpcs;

	wetuwn 0;

eww_fwee:
	kfwee(mpcs);
	wetuwn eww;
}

const stwuct mv88e6xxx_pcs_ops mv88e6393x_pcs_ops = {
	.pcs_init = mv88e6393x_pcs_init,
	.pcs_teawdown = mv88e639x_pcs_teawdown,
	.pcs_sewect = mv88e639x_pcs_sewect,
};
