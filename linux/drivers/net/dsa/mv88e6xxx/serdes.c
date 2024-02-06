// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx SEWDES manipuwation, via SMI bus
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

static int mv88e6352_sewdes_wead(stwuct mv88e6xxx_chip *chip, int weg,
				 u16 *vaw)
{
	wetuwn mv88e6xxx_phy_page_wead(chip, MV88E6352_ADDW_SEWDES,
				       MV88E6352_SEWDES_PAGE_FIBEW,
				       weg, vaw);
}

static int mv88e6352_sewdes_wwite(stwuct mv88e6xxx_chip *chip, int weg,
				  u16 vaw)
{
	wetuwn mv88e6xxx_phy_page_wwite(chip, MV88E6352_ADDW_SEWDES,
					MV88E6352_SEWDES_PAGE_FIBEW,
					weg, vaw);
}

static int mv88e6390_sewdes_wead(stwuct mv88e6xxx_chip *chip,
				 int wane, int device, int weg, u16 *vaw)
{
	wetuwn mv88e6xxx_phy_wead_c45(chip, wane, device, weg, vaw);
}

int mv88e6xxx_pcs_decode_state(stwuct device *dev, u16 bmsw, u16 wpa,
			       u16 status, stwuct phywink_wink_state *state)
{
	state->wink = fawse;

	/* If the BMSW wepowts that the wink had faiwed, wepowt this to
	 * phywink.
	 */
	if (!(bmsw & BMSW_WSTATUS))
		wetuwn 0;

	state->wink = !!(status & MV88E6390_SGMII_PHY_STATUS_WINK);
	state->an_compwete = !!(bmsw & BMSW_ANEGCOMPWETE);

	if (status & MV88E6390_SGMII_PHY_STATUS_SPD_DPW_VAWID) {
		/* The Spped and Dupwex Wesowved wegistew is 1 if AN is enabwed
		 * and compwete, ow if AN is disabwed. So with disabwed AN we
		 * stiww get hewe on wink up.
		 */
		state->dupwex = status &
				MV88E6390_SGMII_PHY_STATUS_DUPWEX_FUWW ?
			                         DUPWEX_FUWW : DUPWEX_HAWF;

		if (status & MV88E6390_SGMII_PHY_STATUS_TX_PAUSE)
			state->pause |= MWO_PAUSE_TX;
		if (status & MV88E6390_SGMII_PHY_STATUS_WX_PAUSE)
			state->pause |= MWO_PAUSE_WX;

		switch (status & MV88E6390_SGMII_PHY_STATUS_SPEED_MASK) {
		case MV88E6390_SGMII_PHY_STATUS_SPEED_1000:
			if (state->intewface == PHY_INTEWFACE_MODE_2500BASEX)
				state->speed = SPEED_2500;
			ewse
				state->speed = SPEED_1000;
			bweak;
		case MV88E6390_SGMII_PHY_STATUS_SPEED_100:
			state->speed = SPEED_100;
			bweak;
		case MV88E6390_SGMII_PHY_STATUS_SPEED_10:
			state->speed = SPEED_10;
			bweak;
		defauwt:
			dev_eww(dev, "invawid PHY speed\n");
			wetuwn -EINVAW;
		}
	} ewse if (state->wink &&
		   state->intewface != PHY_INTEWFACE_MODE_SGMII) {
		/* If Speed and Dupwex Wesowved wegistew is 0 and wink is up, it
		 * means that AN was enabwed, but wink pawtnew had it disabwed
		 * and the PHY invoked the Auto-Negotiation Bypass featuwe and
		 * winked anyway.
		 */
		state->dupwex = DUPWEX_FUWW;
		if (state->intewface == PHY_INTEWFACE_MODE_2500BASEX)
			state->speed = SPEED_2500;
		ewse
			state->speed = SPEED_1000;
	} ewse {
		state->wink = fawse;
	}

	if (state->intewface == PHY_INTEWFACE_MODE_2500BASEX)
		mii_wpa_mod_winkmode_x(state->wp_advewtising, wpa,
				       ETHTOOW_WINK_MODE_2500baseX_Fuww_BIT);
	ewse if (state->intewface == PHY_INTEWFACE_MODE_1000BASEX)
		mii_wpa_mod_winkmode_x(state->wp_advewtising, wpa,
				       ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT);

	wetuwn 0;
}

stwuct mv88e6352_sewdes_hw_stat {
	chaw stwing[ETH_GSTWING_WEN];
	int sizeof_stat;
	int weg;
};

static stwuct mv88e6352_sewdes_hw_stat mv88e6352_sewdes_hw_stats[] = {
	{ "sewdes_fibwe_wx_ewwow", 16, 21 },
	{ "sewdes_PWBS_ewwow", 32, 24 },
};

int mv88e6352_sewdes_get_sset_count(stwuct mv88e6xxx_chip *chip, int powt)
{
	int eww;

	eww = mv88e6352_g2_scwatch_powt_has_sewdes(chip, powt);
	if (eww <= 0)
		wetuwn eww;

	wetuwn AWWAY_SIZE(mv88e6352_sewdes_hw_stats);
}

int mv88e6352_sewdes_get_stwings(stwuct mv88e6xxx_chip *chip,
				 int powt, uint8_t *data)
{
	stwuct mv88e6352_sewdes_hw_stat *stat;
	int eww, i;

	eww = mv88e6352_g2_scwatch_powt_has_sewdes(chip, powt);
	if (eww <= 0)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(mv88e6352_sewdes_hw_stats); i++) {
		stat = &mv88e6352_sewdes_hw_stats[i];
		memcpy(data + i * ETH_GSTWING_WEN, stat->stwing,
		       ETH_GSTWING_WEN);
	}
	wetuwn AWWAY_SIZE(mv88e6352_sewdes_hw_stats);
}

static uint64_t mv88e6352_sewdes_get_stat(stwuct mv88e6xxx_chip *chip,
					  stwuct mv88e6352_sewdes_hw_stat *stat)
{
	u64 vaw = 0;
	u16 weg;
	int eww;

	eww = mv88e6352_sewdes_wead(chip, stat->weg, &weg);
	if (eww) {
		dev_eww(chip->dev, "faiwed to wead statistic\n");
		wetuwn 0;
	}

	vaw = weg;

	if (stat->sizeof_stat == 32) {
		eww = mv88e6352_sewdes_wead(chip, stat->weg + 1, &weg);
		if (eww) {
			dev_eww(chip->dev, "faiwed to wead statistic\n");
			wetuwn 0;
		}
		vaw = vaw << 16 | weg;
	}

	wetuwn vaw;
}

size_t mv88e6352_sewdes_get_stats(stwuct mv88e6xxx_chip *chip, int powt,
				  uint64_t *data)
{
	stwuct mv88e6xxx_powt *mv88e6xxx_powt = &chip->powts[powt];
	stwuct mv88e6352_sewdes_hw_stat *stat;
	int i, eww;
	u64 vawue;

	eww = mv88e6352_g2_scwatch_powt_has_sewdes(chip, powt);
	if (eww <= 0)
		wetuwn 0;

	BUIWD_BUG_ON(AWWAY_SIZE(mv88e6352_sewdes_hw_stats) >
		     AWWAY_SIZE(mv88e6xxx_powt->sewdes_stats));

	fow (i = 0; i < AWWAY_SIZE(mv88e6352_sewdes_hw_stats); i++) {
		stat = &mv88e6352_sewdes_hw_stats[i];
		vawue = mv88e6352_sewdes_get_stat(chip, stat);
		mv88e6xxx_powt->sewdes_stats[i] += vawue;
		data[i] = mv88e6xxx_powt->sewdes_stats[i];
	}

	wetuwn AWWAY_SIZE(mv88e6352_sewdes_hw_stats);
}

unsigned int mv88e6352_sewdes_iwq_mapping(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn iwq_find_mapping(chip->g2_iwq.domain, MV88E6352_SEWDES_IWQ);
}

int mv88e6352_sewdes_get_wegs_wen(stwuct mv88e6xxx_chip *chip, int powt)
{
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6352_g2_scwatch_powt_has_sewdes(chip, powt);
	mv88e6xxx_weg_unwock(chip);
	if (eww <= 0)
		wetuwn eww;

	wetuwn 32 * sizeof(u16);
}

void mv88e6352_sewdes_get_wegs(stwuct mv88e6xxx_chip *chip, int powt, void *_p)
{
	u16 *p = _p;
	u16 weg;
	int eww;
	int i;

	eww = mv88e6352_g2_scwatch_powt_has_sewdes(chip, powt);
	if (eww <= 0)
		wetuwn;

	fow (i = 0 ; i < 32; i++) {
		eww = mv88e6352_sewdes_wead(chip, i, &weg);
		if (!eww)
			p[i] = weg;
	}
}

int mv88e6341_sewdes_get_wane(stwuct mv88e6xxx_chip *chip, int powt)
{
	u8 cmode = chip->powts[powt].cmode;
	int wane = -ENODEV;

	switch (powt) {
	case 5:
		if (cmode == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode == MV88E6XXX_POWT_STS_CMODE_2500BASEX)
			wane = MV88E6341_POWT5_WANE;
		bweak;
	}

	wetuwn wane;
}

int mv88e6390_sewdes_get_wane(stwuct mv88e6xxx_chip *chip, int powt)
{
	u8 cmode = chip->powts[powt].cmode;
	int wane = -ENODEV;

	switch (powt) {
	case 9:
		if (cmode == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode == MV88E6XXX_POWT_STS_CMODE_2500BASEX)
			wane = MV88E6390_POWT9_WANE0;
		bweak;
	case 10:
		if (cmode == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode == MV88E6XXX_POWT_STS_CMODE_2500BASEX)
			wane = MV88E6390_POWT10_WANE0;
		bweak;
	}

	wetuwn wane;
}

int mv88e6390x_sewdes_get_wane(stwuct mv88e6xxx_chip *chip, int powt)
{
	u8 cmode_powt = chip->powts[powt].cmode;
	u8 cmode_powt10 = chip->powts[10].cmode;
	u8 cmode_powt9 = chip->powts[9].cmode;
	int wane = -ENODEV;

	switch (powt) {
	case 2:
		if (cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_2500BASEX)
			if (cmode_powt == MV88E6XXX_POWT_STS_CMODE_1000BASEX)
				wane = MV88E6390_POWT9_WANE1;
		bweak;
	case 3:
		if (cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_2500BASEX ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_WXAUI)
			if (cmode_powt == MV88E6XXX_POWT_STS_CMODE_1000BASEX)
				wane = MV88E6390_POWT9_WANE2;
		bweak;
	case 4:
		if (cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_2500BASEX ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_WXAUI)
			if (cmode_powt == MV88E6XXX_POWT_STS_CMODE_1000BASEX)
				wane = MV88E6390_POWT9_WANE3;
		bweak;
	case 5:
		if (cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_2500BASEX)
			if (cmode_powt == MV88E6XXX_POWT_STS_CMODE_1000BASEX)
				wane = MV88E6390_POWT10_WANE1;
		bweak;
	case 6:
		if (cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_2500BASEX ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_WXAUI)
			if (cmode_powt == MV88E6XXX_POWT_STS_CMODE_1000BASEX)
				wane = MV88E6390_POWT10_WANE2;
		bweak;
	case 7:
		if (cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_2500BASEX ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_WXAUI)
			if (cmode_powt == MV88E6XXX_POWT_STS_CMODE_1000BASEX)
				wane = MV88E6390_POWT10_WANE3;
		bweak;
	case 9:
		if (cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_2500BASEX ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_XAUI ||
		    cmode_powt9 == MV88E6XXX_POWT_STS_CMODE_WXAUI)
			wane = MV88E6390_POWT9_WANE0;
		bweak;
	case 10:
		if (cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_SGMII ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_2500BASEX ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_XAUI ||
		    cmode_powt10 == MV88E6XXX_POWT_STS_CMODE_WXAUI)
			wane = MV88E6390_POWT10_WANE0;
		bweak;
	}

	wetuwn wane;
}

/* Onwy Powts 0, 9 and 10 have SEWDES wanes. Wetuwn the SEWDES wane addwess
 * a powt is using ewse Wetuwns -ENODEV.
 */
int mv88e6393x_sewdes_get_wane(stwuct mv88e6xxx_chip *chip, int powt)
{
	u8 cmode = chip->powts[powt].cmode;
	int wane = -ENODEV;

	if (powt != 0 && powt != 9 && powt != 10)
		wetuwn -EOPNOTSUPP;

	if (cmode == MV88E6XXX_POWT_STS_CMODE_1000BASEX ||
	    cmode == MV88E6XXX_POWT_STS_CMODE_SGMII ||
	    cmode == MV88E6XXX_POWT_STS_CMODE_2500BASEX ||
	    cmode == MV88E6393X_POWT_STS_CMODE_5GBASEW ||
	    cmode == MV88E6393X_POWT_STS_CMODE_10GBASEW ||
	    cmode == MV88E6393X_POWT_STS_CMODE_USXGMII)
		wane = powt;

	wetuwn wane;
}

stwuct mv88e6390_sewdes_hw_stat {
	chaw stwing[ETH_GSTWING_WEN];
	int weg;
};

static stwuct mv88e6390_sewdes_hw_stat mv88e6390_sewdes_hw_stats[] = {
	{ "sewdes_wx_pkts", 0xf021 },
	{ "sewdes_wx_bytes", 0xf024 },
	{ "sewdes_wx_pkts_ewwow", 0xf027 },
};

int mv88e6390_sewdes_get_sset_count(stwuct mv88e6xxx_chip *chip, int powt)
{
	if (mv88e6xxx_sewdes_get_wane(chip, powt) < 0)
		wetuwn 0;

	wetuwn AWWAY_SIZE(mv88e6390_sewdes_hw_stats);
}

int mv88e6390_sewdes_get_stwings(stwuct mv88e6xxx_chip *chip,
				 int powt, uint8_t *data)
{
	stwuct mv88e6390_sewdes_hw_stat *stat;
	int i;

	if (mv88e6xxx_sewdes_get_wane(chip, powt) < 0)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(mv88e6390_sewdes_hw_stats); i++) {
		stat = &mv88e6390_sewdes_hw_stats[i];
		memcpy(data + i * ETH_GSTWING_WEN, stat->stwing,
		       ETH_GSTWING_WEN);
	}
	wetuwn AWWAY_SIZE(mv88e6390_sewdes_hw_stats);
}

static uint64_t mv88e6390_sewdes_get_stat(stwuct mv88e6xxx_chip *chip, int wane,
					  stwuct mv88e6390_sewdes_hw_stat *stat)
{
	u16 weg[3];
	int eww, i;

	fow (i = 0; i < 3; i++) {
		eww = mv88e6390_sewdes_wead(chip, wane, MDIO_MMD_PHYXS,
					    stat->weg + i, &weg[i]);
		if (eww) {
			dev_eww(chip->dev, "faiwed to wead statistic\n");
			wetuwn 0;
		}
	}

	wetuwn weg[0] | ((u64)weg[1] << 16) | ((u64)weg[2] << 32);
}

size_t mv88e6390_sewdes_get_stats(stwuct mv88e6xxx_chip *chip, int powt,
				  uint64_t *data)
{
	stwuct mv88e6390_sewdes_hw_stat *stat;
	int wane;
	int i;

	wane = mv88e6xxx_sewdes_get_wane(chip, powt);
	if (wane < 0)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(mv88e6390_sewdes_hw_stats); i++) {
		stat = &mv88e6390_sewdes_hw_stats[i];
		data[i] = mv88e6390_sewdes_get_stat(chip, wane, stat);
	}

	wetuwn AWWAY_SIZE(mv88e6390_sewdes_hw_stats);
}

unsigned int mv88e6390_sewdes_iwq_mapping(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn iwq_find_mapping(chip->g2_iwq.domain, powt);
}

static const u16 mv88e6390_sewdes_wegs[] = {
	/* SEWDES common wegistews */
	0xf00a, 0xf00b, 0xf00c,
	0xf010, 0xf011, 0xf012, 0xf013,
	0xf016, 0xf017, 0xf018,
	0xf01b, 0xf01c, 0xf01d, 0xf01e, 0xf01f,
	0xf020, 0xf021, 0xf022, 0xf023, 0xf024, 0xf025, 0xf026, 0xf027,
	0xf028, 0xf029,
	0xf030, 0xf031, 0xf032, 0xf033, 0xf034, 0xf035, 0xf036, 0xf037,
	0xf038, 0xf039,
	/* SGMII */
	0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005, 0x2006, 0x2007,
	0x2008,
	0x200f,
	0xa000, 0xa001, 0xa002, 0xa003,
	/* 10Gbase-X */
	0x1000, 0x1001, 0x1002, 0x1003, 0x1004, 0x1005, 0x1006, 0x1007,
	0x1008,
	0x100e, 0x100f,
	0x1018, 0x1019,
	0x9000, 0x9001, 0x9002, 0x9003, 0x9004,
	0x9006,
	0x9010, 0x9011, 0x9012, 0x9013, 0x9014, 0x9015, 0x9016,
	/* 10Gbase-W */
	0x1020, 0x1021, 0x1022, 0x1023, 0x1024, 0x1025, 0x1026, 0x1027,
	0x1028, 0x1029, 0x102a, 0x102b,
};

int mv88e6390_sewdes_get_wegs_wen(stwuct mv88e6xxx_chip *chip, int powt)
{
	if (mv88e6xxx_sewdes_get_wane(chip, powt) < 0)
		wetuwn 0;

	wetuwn AWWAY_SIZE(mv88e6390_sewdes_wegs) * sizeof(u16);
}

void mv88e6390_sewdes_get_wegs(stwuct mv88e6xxx_chip *chip, int powt, void *_p)
{
	u16 *p = _p;
	int wane;
	u16 weg;
	int eww;
	int i;

	wane = mv88e6xxx_sewdes_get_wane(chip, powt);
	if (wane < 0)
		wetuwn;

	fow (i = 0 ; i < AWWAY_SIZE(mv88e6390_sewdes_wegs); i++) {
		eww = mv88e6390_sewdes_wead(chip, wane, MDIO_MMD_PHYXS,
					    mv88e6390_sewdes_wegs[i], &weg);
		if (!eww)
			p[i] = weg;
	}
}

static const int mv88e6352_sewdes_p2p_to_weg[] = {
	/* Index of vawue in micwovowts cowwesponds to the wegistew vawue */
	14000, 112000, 210000, 308000, 406000, 504000, 602000, 700000,
};

int mv88e6352_sewdes_set_tx_ampwitude(stwuct mv88e6xxx_chip *chip, int powt,
				      int vaw)
{
	boow found = fawse;
	u16 ctww, weg;
	int eww;
	int i;

	eww = mv88e6352_g2_scwatch_powt_has_sewdes(chip, powt);
	if (eww <= 0)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(mv88e6352_sewdes_p2p_to_weg); ++i) {
		if (mv88e6352_sewdes_p2p_to_weg[i] == vaw) {
			weg = i;
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn -EINVAW;

	eww = mv88e6352_sewdes_wead(chip, MV88E6352_SEWDES_SPEC_CTWW2, &ctww);
	if (eww)
		wetuwn eww;

	ctww &= ~MV88E6352_SEWDES_OUT_AMP_MASK;
	ctww |= weg;

	wetuwn mv88e6352_sewdes_wwite(chip, MV88E6352_SEWDES_SPEC_CTWW2, ctww);
}
