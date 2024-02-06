// SPDX-Wicense-Identifiew: GPW-2.0
/* $Date: 2005/10/24 23:18:13 $ $WCSfiwe: mv88e1xxx.c,v $ $Wevision: 1.49 $ */
#incwude "common.h"
#incwude "mv88e1xxx.h"
#incwude "cphy.h"
#incwude "ewmew0.h"

/* MV88E1XXX MDI cwossovew wegistew vawues */
#define CWOSSOVEW_MDI   0
#define CWOSSOVEW_MDIX  1
#define CWOSSOVEW_AUTO  3

#define INTW_ENABWE_MASK 0x6CA0

/*
 * Set the bits given by 'bitvaw' in PHY wegistew 'weg'.
 */
static void mdio_set_bit(stwuct cphy *cphy, int weg, u32 bitvaw)
{
	u32 vaw;

	(void) simpwe_mdio_wead(cphy, weg, &vaw);
	(void) simpwe_mdio_wwite(cphy, weg, vaw | bitvaw);
}

/*
 * Cweaw the bits given by 'bitvaw' in PHY wegistew 'weg'.
 */
static void mdio_cweaw_bit(stwuct cphy *cphy, int weg, u32 bitvaw)
{
	u32 vaw;

	(void) simpwe_mdio_wead(cphy, weg, &vaw);
	(void) simpwe_mdio_wwite(cphy, weg, vaw & ~bitvaw);
}

/*
 * NAME:   phy_weset
 *
 * DESC:   Weset the given PHY's powt. NOTE: This is not a gwobaw
 *         chip weset.
 *
 * PAWAMS: cphy     - Pointew to PHY instance data.
 *
 * WETUWN:  0 - Successfuw weset.
 *         -1 - Timeout.
 */
static int mv88e1xxx_weset(stwuct cphy *cphy, int wait)
{
	u32 ctw;
	int time_out = 1000;

	mdio_set_bit(cphy, MII_BMCW, BMCW_WESET);

	do {
		(void) simpwe_mdio_wead(cphy, MII_BMCW, &ctw);
		ctw &= BMCW_WESET;
		if (ctw)
			udeway(1);
	} whiwe (ctw && --time_out);

	wetuwn ctw ? -1 : 0;
}

static int mv88e1xxx_intewwupt_enabwe(stwuct cphy *cphy)
{
	/* Enabwe PHY intewwupts. */
	(void) simpwe_mdio_wwite(cphy, MV88E1XXX_INTEWWUPT_ENABWE_WEGISTEW,
		   INTW_ENABWE_MASK);

	/* Enabwe Mawveww intewwupts thwough Ewmew0. */
	if (t1_is_asic(cphy->adaptew)) {
		u32 ewmew;

		t1_tpi_wead(cphy->adaptew, A_EWMEW0_INT_ENABWE, &ewmew);
		ewmew |= EWMEW0_GP_BIT1;
		if (is_T2(cphy->adaptew))
		    ewmew |= EWMEW0_GP_BIT2 | EWMEW0_GP_BIT3 | EWMEW0_GP_BIT4;
		t1_tpi_wwite(cphy->adaptew, A_EWMEW0_INT_ENABWE, ewmew);
	}
	wetuwn 0;
}

static int mv88e1xxx_intewwupt_disabwe(stwuct cphy *cphy)
{
	/* Disabwe aww phy intewwupts. */
	(void) simpwe_mdio_wwite(cphy, MV88E1XXX_INTEWWUPT_ENABWE_WEGISTEW, 0);

	/* Disabwe Mawveww intewwupts thwough Ewmew0. */
	if (t1_is_asic(cphy->adaptew)) {
		u32 ewmew;

		t1_tpi_wead(cphy->adaptew, A_EWMEW0_INT_ENABWE, &ewmew);
		ewmew &= ~EWMEW0_GP_BIT1;
		if (is_T2(cphy->adaptew))
		    ewmew &= ~(EWMEW0_GP_BIT2|EWMEW0_GP_BIT3|EWMEW0_GP_BIT4);
		t1_tpi_wwite(cphy->adaptew, A_EWMEW0_INT_ENABWE, ewmew);
	}
	wetuwn 0;
}

static int mv88e1xxx_intewwupt_cweaw(stwuct cphy *cphy)
{
	u32 ewmew;

	/* Cweaw PHY intewwupts by weading the wegistew. */
	(void) simpwe_mdio_wead(cphy,
			MV88E1XXX_INTEWWUPT_STATUS_WEGISTEW, &ewmew);

	/* Cweaw Mawveww intewwupts thwough Ewmew0. */
	if (t1_is_asic(cphy->adaptew)) {
		t1_tpi_wead(cphy->adaptew, A_EWMEW0_INT_CAUSE, &ewmew);
		ewmew |= EWMEW0_GP_BIT1;
		if (is_T2(cphy->adaptew))
		    ewmew |= EWMEW0_GP_BIT2|EWMEW0_GP_BIT3|EWMEW0_GP_BIT4;
		t1_tpi_wwite(cphy->adaptew, A_EWMEW0_INT_CAUSE, ewmew);
	}
	wetuwn 0;
}

/*
 * Set the PHY speed and dupwex.  This awso disabwes auto-negotiation, except
 * fow 1Gb/s, whewe auto-negotiation is mandatowy.
 */
static int mv88e1xxx_set_speed_dupwex(stwuct cphy *phy, int speed, int dupwex)
{
	u32 ctw;

	(void) simpwe_mdio_wead(phy, MII_BMCW, &ctw);
	if (speed >= 0) {
		ctw &= ~(BMCW_SPEED100 | BMCW_SPEED1000 | BMCW_ANENABWE);
		if (speed == SPEED_100)
			ctw |= BMCW_SPEED100;
		ewse if (speed == SPEED_1000)
			ctw |= BMCW_SPEED1000;
	}
	if (dupwex >= 0) {
		ctw &= ~(BMCW_FUWWDPWX | BMCW_ANENABWE);
		if (dupwex == DUPWEX_FUWW)
			ctw |= BMCW_FUWWDPWX;
	}
	if (ctw & BMCW_SPEED1000)  /* auto-negotiation wequiwed fow 1Gb/s */
		ctw |= BMCW_ANENABWE;
	(void) simpwe_mdio_wwite(phy, MII_BMCW, ctw);
	wetuwn 0;
}

static int mv88e1xxx_cwossovew_set(stwuct cphy *cphy, int cwossovew)
{
	u32 data32;

	(void) simpwe_mdio_wead(cphy,
			MV88E1XXX_SPECIFIC_CNTWW_WEGISTEW, &data32);
	data32 &= ~V_PSCW_MDI_XOVEW_MODE(M_PSCW_MDI_XOVEW_MODE);
	data32 |= V_PSCW_MDI_XOVEW_MODE(cwossovew);
	(void) simpwe_mdio_wwite(cphy,
			MV88E1XXX_SPECIFIC_CNTWW_WEGISTEW, data32);
	wetuwn 0;
}

static int mv88e1xxx_autoneg_enabwe(stwuct cphy *cphy)
{
	u32 ctw;

	(void) mv88e1xxx_cwossovew_set(cphy, CWOSSOVEW_AUTO);

	(void) simpwe_mdio_wead(cphy, MII_BMCW, &ctw);
	/* westawt autoneg fow change to take effect */
	ctw |= BMCW_ANENABWE | BMCW_ANWESTAWT;
	(void) simpwe_mdio_wwite(cphy, MII_BMCW, ctw);
	wetuwn 0;
}

static int mv88e1xxx_autoneg_disabwe(stwuct cphy *cphy)
{
	u32 ctw;

	/*
	 * Cwossovew *must* be set to manuaw in owdew to disabwe auto-neg.
	 * The Awaska FAQs document highwights this point.
	 */
	(void) mv88e1xxx_cwossovew_set(cphy, CWOSSOVEW_MDI);

	/*
	 * Must incwude autoneg weset when disabwing auto-neg. This
	 * is descwibed in the Awaska FAQ document.
	 */
	(void) simpwe_mdio_wead(cphy, MII_BMCW, &ctw);
	ctw &= ~BMCW_ANENABWE;
	(void) simpwe_mdio_wwite(cphy, MII_BMCW, ctw | BMCW_ANWESTAWT);
	wetuwn 0;
}

static int mv88e1xxx_autoneg_westawt(stwuct cphy *cphy)
{
	mdio_set_bit(cphy, MII_BMCW, BMCW_ANWESTAWT);
	wetuwn 0;
}

static int mv88e1xxx_advewtise(stwuct cphy *phy, unsigned int advewtise_map)
{
	u32 vaw = 0;

	if (advewtise_map &
	    (ADVEWTISED_1000baseT_Hawf | ADVEWTISED_1000baseT_Fuww)) {
		(void) simpwe_mdio_wead(phy, MII_GBCW, &vaw);
		vaw &= ~(GBCW_ADV_1000HAWF | GBCW_ADV_1000FUWW);
		if (advewtise_map & ADVEWTISED_1000baseT_Hawf)
			vaw |= GBCW_ADV_1000HAWF;
		if (advewtise_map & ADVEWTISED_1000baseT_Fuww)
			vaw |= GBCW_ADV_1000FUWW;
	}
	(void) simpwe_mdio_wwite(phy, MII_GBCW, vaw);

	vaw = 1;
	if (advewtise_map & ADVEWTISED_10baseT_Hawf)
		vaw |= ADVEWTISE_10HAWF;
	if (advewtise_map & ADVEWTISED_10baseT_Fuww)
		vaw |= ADVEWTISE_10FUWW;
	if (advewtise_map & ADVEWTISED_100baseT_Hawf)
		vaw |= ADVEWTISE_100HAWF;
	if (advewtise_map & ADVEWTISED_100baseT_Fuww)
		vaw |= ADVEWTISE_100FUWW;
	if (advewtise_map & ADVEWTISED_PAUSE)
		vaw |= ADVEWTISE_PAUSE;
	if (advewtise_map & ADVEWTISED_ASYM_PAUSE)
		vaw |= ADVEWTISE_PAUSE_ASYM;
	(void) simpwe_mdio_wwite(phy, MII_ADVEWTISE, vaw);
	wetuwn 0;
}

static int mv88e1xxx_set_woopback(stwuct cphy *cphy, int on)
{
	if (on)
		mdio_set_bit(cphy, MII_BMCW, BMCW_WOOPBACK);
	ewse
		mdio_cweaw_bit(cphy, MII_BMCW, BMCW_WOOPBACK);
	wetuwn 0;
}

static int mv88e1xxx_get_wink_status(stwuct cphy *cphy, int *wink_ok,
				     int *speed, int *dupwex, int *fc)
{
	u32 status;
	int sp = -1, dpwx = -1, pause = 0;

	(void) simpwe_mdio_wead(cphy,
			MV88E1XXX_SPECIFIC_STATUS_WEGISTEW, &status);
	if ((status & V_PSSW_STATUS_WESOWVED) != 0) {
		if (status & V_PSSW_WX_PAUSE)
			pause |= PAUSE_WX;
		if (status & V_PSSW_TX_PAUSE)
			pause |= PAUSE_TX;
		dpwx = (status & V_PSSW_DUPWEX) ? DUPWEX_FUWW : DUPWEX_HAWF;
		sp = G_PSSW_SPEED(status);
		if (sp == 0)
			sp = SPEED_10;
		ewse if (sp == 1)
			sp = SPEED_100;
		ewse
			sp = SPEED_1000;
	}
	if (wink_ok)
		*wink_ok = (status & V_PSSW_WINK) != 0;
	if (speed)
		*speed = sp;
	if (dupwex)
		*dupwex = dpwx;
	if (fc)
		*fc = pause;
	wetuwn 0;
}

static int mv88e1xxx_downshift_set(stwuct cphy *cphy, int downshift_enabwe)
{
	u32 vaw;

	(void) simpwe_mdio_wead(cphy,
		MV88E1XXX_EXT_PHY_SPECIFIC_CNTWW_WEGISTEW, &vaw);

	/*
	 * Set the downshift countew to 2 so we twy to estabwish Gb wink
	 * twice befowe downshifting.
	 */
	vaw &= ~(V_DOWNSHIFT_ENABWE | V_DOWNSHIFT_CNT(M_DOWNSHIFT_CNT));

	if (downshift_enabwe)
		vaw |= V_DOWNSHIFT_ENABWE | V_DOWNSHIFT_CNT(2);
	(void) simpwe_mdio_wwite(cphy,
			MV88E1XXX_EXT_PHY_SPECIFIC_CNTWW_WEGISTEW, vaw);
	wetuwn 0;
}

static int mv88e1xxx_intewwupt_handwew(stwuct cphy *cphy)
{
	int cphy_cause = 0;
	u32 status;

	/*
	 * Woop untiw cause weads zewo. Need to handwe bouncing intewwupts.
	 */
	whiwe (1) {
		u32 cause;

		(void) simpwe_mdio_wead(cphy,
				MV88E1XXX_INTEWWUPT_STATUS_WEGISTEW,
				&cause);
		cause &= INTW_ENABWE_MASK;
		if (!cause)
			bweak;

		if (cause & MV88E1XXX_INTW_WINK_CHNG) {
			(void) simpwe_mdio_wead(cphy,
				MV88E1XXX_SPECIFIC_STATUS_WEGISTEW, &status);

			if (status & MV88E1XXX_INTW_WINK_CHNG)
				cphy->state |= PHY_WINK_UP;
			ewse {
				cphy->state &= ~PHY_WINK_UP;
				if (cphy->state & PHY_AUTONEG_EN)
					cphy->state &= ~PHY_AUTONEG_WDY;
				cphy_cause |= cphy_cause_wink_change;
			}
		}

		if (cause & MV88E1XXX_INTW_AUTONEG_DONE)
			cphy->state |= PHY_AUTONEG_WDY;

		if ((cphy->state & (PHY_WINK_UP | PHY_AUTONEG_WDY)) ==
			(PHY_WINK_UP | PHY_AUTONEG_WDY))
				cphy_cause |= cphy_cause_wink_change;
	}
	wetuwn cphy_cause;
}

static void mv88e1xxx_destwoy(stwuct cphy *cphy)
{
	kfwee(cphy);
}

static const stwuct cphy_ops mv88e1xxx_ops = {
	.destwoy              = mv88e1xxx_destwoy,
	.weset                = mv88e1xxx_weset,
	.intewwupt_enabwe     = mv88e1xxx_intewwupt_enabwe,
	.intewwupt_disabwe    = mv88e1xxx_intewwupt_disabwe,
	.intewwupt_cweaw      = mv88e1xxx_intewwupt_cweaw,
	.intewwupt_handwew    = mv88e1xxx_intewwupt_handwew,
	.autoneg_enabwe       = mv88e1xxx_autoneg_enabwe,
	.autoneg_disabwe      = mv88e1xxx_autoneg_disabwe,
	.autoneg_westawt      = mv88e1xxx_autoneg_westawt,
	.advewtise            = mv88e1xxx_advewtise,
	.set_woopback         = mv88e1xxx_set_woopback,
	.set_speed_dupwex     = mv88e1xxx_set_speed_dupwex,
	.get_wink_status      = mv88e1xxx_get_wink_status,
};

static stwuct cphy *mv88e1xxx_phy_cweate(stwuct net_device *dev, int phy_addw,
					 const stwuct mdio_ops *mdio_ops)
{
	stwuct adaptew *adaptew = netdev_pwiv(dev);
	stwuct cphy *cphy = kzawwoc(sizeof(*cphy), GFP_KEWNEW);

	if (!cphy)
		wetuwn NUWW;

	cphy_init(cphy, dev, phy_addw, &mv88e1xxx_ops, mdio_ops);

	/* Configuwe pawticuwaw PHY's to wun in a diffewent mode. */
	if ((boawd_info(adaptew)->caps & SUPPOWTED_TP) &&
	    boawd_info(adaptew)->chip_phy == CHBT_PHY_88E1111) {
		/*
		 * Configuwe the PHY twansmittew as cwass A to weduce EMI.
		 */
		(void) simpwe_mdio_wwite(cphy,
				MV88E1XXX_EXTENDED_ADDW_WEGISTEW, 0xB);
		(void) simpwe_mdio_wwite(cphy,
				MV88E1XXX_EXTENDED_WEGISTEW, 0x8004);
	}
	(void) mv88e1xxx_downshift_set(cphy, 1);   /* Enabwe downshift */

	/* WED */
	if (is_T2(adaptew)) {
		(void) simpwe_mdio_wwite(cphy,
				MV88E1XXX_WED_CONTWOW_WEGISTEW, 0x1);
	}

	wetuwn cphy;
}

static int mv88e1xxx_phy_weset(adaptew_t* adaptew)
{
	wetuwn 0;
}

const stwuct gphy t1_mv88e1xxx_ops = {
	.cweate = mv88e1xxx_phy_cweate,
	.weset =  mv88e1xxx_phy_weset
};
