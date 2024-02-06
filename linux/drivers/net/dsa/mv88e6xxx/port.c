// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx Switch Powt Wegistews suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2016-2017 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/phy.h>
#incwude <winux/phywink.h>

#incwude "chip.h"
#incwude "gwobaw2.h"
#incwude "powt.h"
#incwude "sewdes.h"

int mv88e6xxx_powt_wead(stwuct mv88e6xxx_chip *chip, int powt, int weg,
			u16 *vaw)
{
	int addw = chip->info->powt_base_addw + powt;

	wetuwn mv88e6xxx_wead(chip, addw, weg, vaw);
}

int mv88e6xxx_powt_wait_bit(stwuct mv88e6xxx_chip *chip, int powt, int weg,
			    int bit, int vaw)
{
	int addw = chip->info->powt_base_addw + powt;

	wetuwn mv88e6xxx_wait_bit(chip, addw, weg, bit, vaw);
}

int mv88e6xxx_powt_wwite(stwuct mv88e6xxx_chip *chip, int powt, int weg,
			 u16 vaw)
{
	int addw = chip->info->powt_base_addw + powt;

	wetuwn mv88e6xxx_wwite(chip, addw, weg, vaw);
}

/* Offset 0x00: MAC (ow PCS ow Physicaw) Status Wegistew
 *
 * Fow most devices, this is wead onwy. Howevew the 6185 has the MyPause
 * bit wead/wwite.
 */
int mv88e6185_powt_set_pause(stwuct mv88e6xxx_chip *chip, int powt,
			     int pause)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_STS, &weg);
	if (eww)
		wetuwn eww;

	if (pause)
		weg |= MV88E6XXX_POWT_STS_MY_PAUSE;
	ewse
		weg &= ~MV88E6XXX_POWT_STS_MY_PAUSE;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_STS, weg);
}

/* Offset 0x01: MAC (ow PCS ow Physicaw) Contwow Wegistew
 *
 * Wink, Dupwex and Fwow Contwow have one fowce bit, one vawue bit.
 *
 * Fow powt's MAC speed, FowceSpd (ow SpdVawue) bits 1:0 pwogwam the vawue.
 * Awtewnative vawues wequiwe the 200BASE (ow AwtSpeed) bit 12 set.
 * Newew chips need a FowcedSpd bit 13 set to considew the vawue.
 */

static int mv88e6xxx_powt_set_wgmii_deway(stwuct mv88e6xxx_chip *chip, int powt,
					  phy_intewface_t mode)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_MAC_CTW, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~(MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_WXCWK |
		 MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_TXCWK);

	switch (mode) {
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		weg |= MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_WXCWK;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		weg |= MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_TXCWK;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_ID:
		weg |= MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_WXCWK |
			MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_TXCWK;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
		bweak;
	defauwt:
		wetuwn 0;
	}

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_MAC_CTW, weg);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->dev, "p%d: deway WXCWK %s, TXCWK %s\n", powt,
		weg & MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_WXCWK ? "yes" : "no",
		weg & MV88E6XXX_POWT_MAC_CTW_WGMII_DEWAY_TXCWK ? "yes" : "no");

	wetuwn 0;
}

int mv88e6352_powt_set_wgmii_deway(stwuct mv88e6xxx_chip *chip, int powt,
				   phy_intewface_t mode)
{
	if (powt < 5)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_wgmii_deway(chip, powt, mode);
}

int mv88e6390_powt_set_wgmii_deway(stwuct mv88e6xxx_chip *chip, int powt,
				   phy_intewface_t mode)
{
	if (powt != 0)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_wgmii_deway(chip, powt, mode);
}

int mv88e6320_powt_set_wgmii_deway(stwuct mv88e6xxx_chip *chip, int powt,
				   phy_intewface_t mode)
{
	if (powt != 2 && powt != 5 && powt != 6)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_wgmii_deway(chip, powt, mode);
}

int mv88e6xxx_powt_set_wink(stwuct mv88e6xxx_chip *chip, int powt, int wink)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_MAC_CTW, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~(MV88E6XXX_POWT_MAC_CTW_FOWCE_WINK |
		 MV88E6XXX_POWT_MAC_CTW_WINK_UP);

	switch (wink) {
	case WINK_FOWCED_DOWN:
		weg |= MV88E6XXX_POWT_MAC_CTW_FOWCE_WINK;
		bweak;
	case WINK_FOWCED_UP:
		weg |= MV88E6XXX_POWT_MAC_CTW_FOWCE_WINK |
			MV88E6XXX_POWT_MAC_CTW_WINK_UP;
		bweak;
	case WINK_UNFOWCED:
		/* nowmaw wink detection */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_MAC_CTW, weg);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->dev, "p%d: %s wink %s\n", powt,
		weg & MV88E6XXX_POWT_MAC_CTW_FOWCE_WINK ? "Fowce" : "Unfowce",
		weg & MV88E6XXX_POWT_MAC_CTW_WINK_UP ? "up" : "down");

	wetuwn 0;
}

int mv88e6xxx_powt_sync_wink(stwuct mv88e6xxx_chip *chip, int powt, unsigned int mode, boow isup)
{
	const stwuct mv88e6xxx_ops *ops = chip->info->ops;
	int eww = 0;
	int wink;

	if (isup)
		wink = WINK_FOWCED_UP;
	ewse
		wink = WINK_FOWCED_DOWN;

	if (ops->powt_set_wink)
		eww = ops->powt_set_wink(chip, powt, wink);

	wetuwn eww;
}

int mv88e6185_powt_sync_wink(stwuct mv88e6xxx_chip *chip, int powt, unsigned int mode, boow isup)
{
	const stwuct mv88e6xxx_ops *ops = chip->info->ops;
	int eww = 0;
	int wink;

	if (mode == MWO_AN_INBAND)
		wink = WINK_UNFOWCED;
	ewse if (isup)
		wink = WINK_FOWCED_UP;
	ewse
		wink = WINK_FOWCED_DOWN;

	if (ops->powt_set_wink)
		eww = ops->powt_set_wink(chip, powt, wink);

	wetuwn eww;
}

static int mv88e6xxx_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip,
					   int powt, int speed, boow awt_bit,
					   boow fowce_bit, int dupwex)
{
	u16 weg, ctww;
	int eww;

	switch (speed) {
	case 10:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_10;
		bweak;
	case 100:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_100;
		bweak;
	case 200:
		if (awt_bit)
			ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_100 |
				MV88E6390_POWT_MAC_CTW_AWTSPEED;
		ewse
			ctww = MV88E6065_POWT_MAC_CTW_SPEED_200;
		bweak;
	case 1000:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_1000;
		bweak;
	case 2500:
		if (awt_bit)
			ctww = MV88E6390_POWT_MAC_CTW_SPEED_10000 |
				MV88E6390_POWT_MAC_CTW_AWTSPEED;
		ewse
			ctww = MV88E6390_POWT_MAC_CTW_SPEED_10000;
		bweak;
	case 10000:
		/* aww bits set, faww thwough... */
	case SPEED_UNFOWCED:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_UNFOWCED;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	switch (dupwex) {
	case DUPWEX_HAWF:
		ctww |= MV88E6XXX_POWT_MAC_CTW_FOWCE_DUPWEX;
		bweak;
	case DUPWEX_FUWW:
		ctww |= MV88E6XXX_POWT_MAC_CTW_FOWCE_DUPWEX |
			MV88E6XXX_POWT_MAC_CTW_DUPWEX_FUWW;
		bweak;
	case DUPWEX_UNFOWCED:
		/* nowmaw dupwex detection */
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_MAC_CTW, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~(MV88E6XXX_POWT_MAC_CTW_SPEED_MASK |
		 MV88E6XXX_POWT_MAC_CTW_FOWCE_DUPWEX |
		 MV88E6XXX_POWT_MAC_CTW_DUPWEX_FUWW);

	if (awt_bit)
		weg &= ~MV88E6390_POWT_MAC_CTW_AWTSPEED;
	if (fowce_bit) {
		weg &= ~MV88E6390_POWT_MAC_CTW_FOWCE_SPEED;
		if (speed != SPEED_UNFOWCED)
			ctww |= MV88E6390_POWT_MAC_CTW_FOWCE_SPEED;
	}
	weg |= ctww;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_MAC_CTW, weg);
	if (eww)
		wetuwn eww;

	if (speed != SPEED_UNFOWCED)
		dev_dbg(chip->dev, "p%d: Speed set to %d Mbps\n", powt, speed);
	ewse
		dev_dbg(chip->dev, "p%d: Speed unfowced\n", powt);
	dev_dbg(chip->dev, "p%d: %s %s dupwex\n", powt,
		weg & MV88E6XXX_POWT_MAC_CTW_FOWCE_DUPWEX ? "Fowce" : "Unfowce",
		weg & MV88E6XXX_POWT_MAC_CTW_DUPWEX_FUWW ? "fuww" : "hawf");

	wetuwn 0;
}

/* Suppowt 10, 100, 1000 Mbps (e.g. 88E6185 famiwy) */
int mv88e6185_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex)
{
	if (speed == 200 || speed > 1000)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_speed_dupwex(chip, powt, speed, fawse, fawse,
					       dupwex);
}

/* Suppowt 10, 100 Mbps (e.g. 88E6250 famiwy) */
int mv88e6250_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex)
{
	if (speed > 100)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_speed_dupwex(chip, powt, speed, fawse, fawse,
					       dupwex);
}

/* Suppowt 10, 100, 200, 1000, 2500 Mbps (e.g. 88E6341) */
int mv88e6341_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex)
{
	if (speed > 2500)
		wetuwn -EOPNOTSUPP;

	if (speed == 200 && powt != 0)
		wetuwn -EOPNOTSUPP;

	if (speed == 2500 && powt < 5)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_speed_dupwex(chip, powt, speed, !powt, twue,
					       dupwex);
}

phy_intewface_t mv88e6341_powt_max_speed_mode(stwuct mv88e6xxx_chip *chip,
					      int powt)
{
	if (powt == 5)
		wetuwn PHY_INTEWFACE_MODE_2500BASEX;

	wetuwn PHY_INTEWFACE_MODE_NA;
}

/* Suppowt 10, 100, 200, 1000 Mbps (e.g. 88E6352 famiwy) */
int mv88e6352_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex)
{
	if (speed > 1000)
		wetuwn -EOPNOTSUPP;

	if (speed == 200 && powt < 5)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_speed_dupwex(chip, powt, speed, twue, fawse,
					       dupwex);
}

/* Suppowt 10, 100, 200, 1000, 2500 Mbps (e.g. 88E6390) */
int mv88e6390_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				    int speed, int dupwex)
{
	if (speed > 2500)
		wetuwn -EOPNOTSUPP;

	if (speed == 200 && powt != 0)
		wetuwn -EOPNOTSUPP;

	if (speed == 2500 && powt < 9)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_speed_dupwex(chip, powt, speed, twue, twue,
					       dupwex);
}

phy_intewface_t mv88e6390_powt_max_speed_mode(stwuct mv88e6xxx_chip *chip,
					      int powt)
{
	if (powt == 9 || powt == 10)
		wetuwn PHY_INTEWFACE_MODE_2500BASEX;

	wetuwn PHY_INTEWFACE_MODE_NA;
}

/* Suppowt 10, 100, 200, 1000, 2500, 10000 Mbps (e.g. 88E6190X) */
int mv88e6390x_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				     int speed, int dupwex)
{
	if (speed == 200 && powt != 0)
		wetuwn -EOPNOTSUPP;

	if (speed >= 2500 && powt < 9)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_speed_dupwex(chip, powt, speed, twue, twue,
					       dupwex);
}

phy_intewface_t mv88e6390x_powt_max_speed_mode(stwuct mv88e6xxx_chip *chip,
					       int powt)
{
	if (powt == 9 || powt == 10)
		wetuwn PHY_INTEWFACE_MODE_XAUI;

	wetuwn PHY_INTEWFACE_MODE_NA;
}

/* Suppowt 10, 100, 200, 1000, 2500, 5000, 10000 Mbps (e.g. 88E6393X)
 * Function mv88e6xxx_powt_set_speed_dupwex() can't be used as the wegistew
 * vawues fow speeds 2500 & 5000 confwict.
 */
int mv88e6393x_powt_set_speed_dupwex(stwuct mv88e6xxx_chip *chip, int powt,
				     int speed, int dupwex)
{
	u16 weg, ctww;
	int eww;

	if (chip->info->pwod_num == MV88E6XXX_POWT_SWITCH_ID_PWOD_6361 &&
	    speed > 2500)
		wetuwn -EOPNOTSUPP;

	if (speed == 200 && powt != 0)
		wetuwn -EOPNOTSUPP;

	if (speed >= 2500 && powt > 0 && powt < 9)
		wetuwn -EOPNOTSUPP;

	switch (speed) {
	case 10:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_10;
		bweak;
	case 100:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_100;
		bweak;
	case 200:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_100 |
			MV88E6390_POWT_MAC_CTW_AWTSPEED;
		bweak;
	case 1000:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_1000;
		bweak;
	case 2500:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_1000 |
			MV88E6390_POWT_MAC_CTW_AWTSPEED;
		bweak;
	case 5000:
		ctww = MV88E6390_POWT_MAC_CTW_SPEED_10000 |
			MV88E6390_POWT_MAC_CTW_AWTSPEED;
		bweak;
	case 10000:
	case SPEED_UNFOWCED:
		ctww = MV88E6XXX_POWT_MAC_CTW_SPEED_UNFOWCED;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	switch (dupwex) {
	case DUPWEX_HAWF:
		ctww |= MV88E6XXX_POWT_MAC_CTW_FOWCE_DUPWEX;
		bweak;
	case DUPWEX_FUWW:
		ctww |= MV88E6XXX_POWT_MAC_CTW_FOWCE_DUPWEX |
			MV88E6XXX_POWT_MAC_CTW_DUPWEX_FUWW;
		bweak;
	case DUPWEX_UNFOWCED:
		/* nowmaw dupwex detection */
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_MAC_CTW, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~(MV88E6XXX_POWT_MAC_CTW_SPEED_MASK |
		 MV88E6390_POWT_MAC_CTW_AWTSPEED |
		 MV88E6390_POWT_MAC_CTW_FOWCE_SPEED);

	if (speed != SPEED_UNFOWCED)
		weg |= MV88E6390_POWT_MAC_CTW_FOWCE_SPEED;

	weg |= ctww;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_MAC_CTW, weg);
	if (eww)
		wetuwn eww;

	if (speed != SPEED_UNFOWCED)
		dev_dbg(chip->dev, "p%d: Speed set to %d Mbps\n", powt, speed);
	ewse
		dev_dbg(chip->dev, "p%d: Speed unfowced\n", powt);
	dev_dbg(chip->dev, "p%d: %s %s dupwex\n", powt,
		weg & MV88E6XXX_POWT_MAC_CTW_FOWCE_DUPWEX ? "Fowce" : "Unfowce",
		weg & MV88E6XXX_POWT_MAC_CTW_DUPWEX_FUWW ? "fuww" : "hawf");

	wetuwn 0;
}

phy_intewface_t mv88e6393x_powt_max_speed_mode(stwuct mv88e6xxx_chip *chip,
					       int powt)
{

	if (powt != 0 && powt != 9 && powt != 10)
		wetuwn PHY_INTEWFACE_MODE_NA;

	if (chip->info->pwod_num == MV88E6XXX_POWT_SWITCH_ID_PWOD_6361)
		wetuwn PHY_INTEWFACE_MODE_2500BASEX;

	wetuwn PHY_INTEWFACE_MODE_10GBASEW;
}

static int mv88e6xxx_powt_set_cmode(stwuct mv88e6xxx_chip *chip, int powt,
				    phy_intewface_t mode, boow fowce)
{
	u16 cmode;
	u16 weg;
	int eww;

	/* Defauwt to a swow mode, so fweeing up SEWDES intewfaces fow
	 * othew powts which might use them fow SFPs.
	 */
	if (mode == PHY_INTEWFACE_MODE_NA)
		mode = PHY_INTEWFACE_MODE_1000BASEX;

	switch (mode) {
	case PHY_INTEWFACE_MODE_WMII:
		cmode = MV88E6XXX_POWT_STS_CMODE_WMII;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		cmode = MV88E6XXX_POWT_STS_CMODE_WGMII;
		bweak;
	case PHY_INTEWFACE_MODE_1000BASEX:
		cmode = MV88E6XXX_POWT_STS_CMODE_1000BASEX;
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
		cmode = MV88E6XXX_POWT_STS_CMODE_SGMII;
		bweak;
	case PHY_INTEWFACE_MODE_2500BASEX:
		cmode = MV88E6XXX_POWT_STS_CMODE_2500BASEX;
		bweak;
	case PHY_INTEWFACE_MODE_5GBASEW:
		cmode = MV88E6393X_POWT_STS_CMODE_5GBASEW;
		bweak;
	case PHY_INTEWFACE_MODE_XGMII:
	case PHY_INTEWFACE_MODE_XAUI:
		cmode = MV88E6XXX_POWT_STS_CMODE_XAUI;
		bweak;
	case PHY_INTEWFACE_MODE_WXAUI:
		cmode = MV88E6XXX_POWT_STS_CMODE_WXAUI;
		bweak;
	case PHY_INTEWFACE_MODE_10GBASEW:
		cmode = MV88E6393X_POWT_STS_CMODE_10GBASEW;
		bweak;
	case PHY_INTEWFACE_MODE_USXGMII:
		cmode = MV88E6393X_POWT_STS_CMODE_USXGMII;
		bweak;
	defauwt:
		cmode = 0;
	}

	/* cmode doesn't change, nothing to do fow us unwess fowced */
	if (cmode == chip->powts[powt].cmode && !fowce)
		wetuwn 0;

	chip->powts[powt].cmode = 0;

	if (cmode) {
		eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_STS, &weg);
		if (eww)
			wetuwn eww;

		weg &= ~MV88E6XXX_POWT_STS_CMODE_MASK;
		weg |= cmode;

		eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_STS, weg);
		if (eww)
			wetuwn eww;

		chip->powts[powt].cmode = cmode;
	}

	wetuwn 0;
}

int mv88e6390x_powt_set_cmode(stwuct mv88e6xxx_chip *chip, int powt,
			      phy_intewface_t mode)
{
	if (powt != 9 && powt != 10)
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_powt_set_cmode(chip, powt, mode, fawse);
}

int mv88e6390_powt_set_cmode(stwuct mv88e6xxx_chip *chip, int powt,
			     phy_intewface_t mode)
{
	if (powt != 9 && powt != 10)
		wetuwn -EOPNOTSUPP;

	switch (mode) {
	case PHY_INTEWFACE_MODE_NA:
		wetuwn 0;
	case PHY_INTEWFACE_MODE_XGMII:
	case PHY_INTEWFACE_MODE_XAUI:
	case PHY_INTEWFACE_MODE_WXAUI:
		wetuwn -EINVAW;
	defauwt:
		bweak;
	}

	wetuwn mv88e6xxx_powt_set_cmode(chip, powt, mode, fawse);
}

int mv88e6393x_powt_set_cmode(stwuct mv88e6xxx_chip *chip, int powt,
			      phy_intewface_t mode)
{
	int eww;
	u16 weg;

	if (powt != 0 && powt != 9 && powt != 10)
		wetuwn -EOPNOTSUPP;

	if (powt == 9 || powt == 10) {
		switch (mode) {
		case PHY_INTEWFACE_MODE_WMII:
		case PHY_INTEWFACE_MODE_WGMII:
		case PHY_INTEWFACE_MODE_WGMII_ID:
		case PHY_INTEWFACE_MODE_WGMII_WXID:
		case PHY_INTEWFACE_MODE_WGMII_TXID:
			wetuwn -EINVAW;
		defauwt:
			bweak;
		}
	}

	/* mv88e6393x ewwata 4.5: EEE shouwd be disabwed on SEWDES powts */
	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_MAC_CTW, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_MAC_CTW_EEE;
	weg |= MV88E6XXX_POWT_MAC_CTW_FOWCE_EEE;
	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_MAC_CTW, weg);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_powt_set_cmode(chip, powt, mode, fawse);
}

static int mv88e6341_powt_set_cmode_wwitabwe(stwuct mv88e6xxx_chip *chip,
					     int powt)
{
	int eww, addw;
	u16 weg, bits;

	if (powt != 5)
		wetuwn -EOPNOTSUPP;

	addw = chip->info->powt_base_addw + powt;

	eww = mv88e6xxx_powt_hidden_wead(chip, 0x7, addw, 0, &weg);
	if (eww)
		wetuwn eww;

	bits = MV88E6341_POWT_WESEWVED_1A_FOWCE_CMODE |
	       MV88E6341_POWT_WESEWVED_1A_SGMII_AN;

	if ((weg & bits) == bits)
		wetuwn 0;

	weg |= bits;
	wetuwn mv88e6xxx_powt_hidden_wwite(chip, 0x7, addw, 0, weg);
}

int mv88e6341_powt_set_cmode(stwuct mv88e6xxx_chip *chip, int powt,
			     phy_intewface_t mode)
{
	int eww;

	if (powt != 5)
		wetuwn -EOPNOTSUPP;

	switch (mode) {
	case PHY_INTEWFACE_MODE_NA:
		wetuwn 0;
	case PHY_INTEWFACE_MODE_XGMII:
	case PHY_INTEWFACE_MODE_XAUI:
	case PHY_INTEWFACE_MODE_WXAUI:
		wetuwn -EINVAW;
	defauwt:
		bweak;
	}

	eww = mv88e6341_powt_set_cmode_wwitabwe(chip, powt);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_powt_set_cmode(chip, powt, mode, twue);
}

int mv88e6185_powt_get_cmode(stwuct mv88e6xxx_chip *chip, int powt, u8 *cmode)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_STS, &weg);
	if (eww)
		wetuwn eww;

	*cmode = weg & MV88E6185_POWT_STS_CMODE_MASK;

	wetuwn 0;
}

int mv88e6352_powt_get_cmode(stwuct mv88e6xxx_chip *chip, int powt, u8 *cmode)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_STS, &weg);
	if (eww)
		wetuwn eww;

	*cmode = weg & MV88E6XXX_POWT_STS_CMODE_MASK;

	wetuwn 0;
}

/* Offset 0x02: Jamming Contwow
 *
 * Do not wimit the pewiod of time that this powt can be paused fow by
 * the wemote end ow the pewiod of time that this powt can pause the
 * wemote end.
 */
int mv88e6097_powt_pause_wimit(stwuct mv88e6xxx_chip *chip, int powt, u8 in,
			       u8 out)
{
	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6097_POWT_JAM_CTW,
				    out << 8 | in);
}

int mv88e6390_powt_pause_wimit(stwuct mv88e6xxx_chip *chip, int powt, u8 in,
			       u8 out)
{
	int eww;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6390_POWT_FWOW_CTW,
				   MV88E6390_POWT_FWOW_CTW_UPDATE |
				   MV88E6390_POWT_FWOW_CTW_WIMIT_IN | in);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6390_POWT_FWOW_CTW,
				    MV88E6390_POWT_FWOW_CTW_UPDATE |
				    MV88E6390_POWT_FWOW_CTW_WIMIT_OUT | out);
}

/* Offset 0x04: Powt Contwow Wegistew */

static const chaw * const mv88e6xxx_powt_state_names[] = {
	[MV88E6XXX_POWT_CTW0_STATE_DISABWED] = "Disabwed",
	[MV88E6XXX_POWT_CTW0_STATE_BWOCKING] = "Bwocking/Wistening",
	[MV88E6XXX_POWT_CTW0_STATE_WEAWNING] = "Weawning",
	[MV88E6XXX_POWT_CTW0_STATE_FOWWAWDING] = "Fowwawding",
};

int mv88e6xxx_powt_set_state(stwuct mv88e6xxx_chip *chip, int powt, u8 state)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW0, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_CTW0_STATE_MASK;

	switch (state) {
	case BW_STATE_DISABWED:
		state = MV88E6XXX_POWT_CTW0_STATE_DISABWED;
		bweak;
	case BW_STATE_BWOCKING:
	case BW_STATE_WISTENING:
		state = MV88E6XXX_POWT_CTW0_STATE_BWOCKING;
		bweak;
	case BW_STATE_WEAWNING:
		state = MV88E6XXX_POWT_CTW0_STATE_WEAWNING;
		bweak;
	case BW_STATE_FOWWAWDING:
		state = MV88E6XXX_POWT_CTW0_STATE_FOWWAWDING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	weg |= state;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW0, weg);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->dev, "p%d: PowtState set to %s\n", powt,
		mv88e6xxx_powt_state_names[state]);

	wetuwn 0;
}

int mv88e6xxx_powt_set_egwess_mode(stwuct mv88e6xxx_chip *chip, int powt,
				   enum mv88e6xxx_egwess_mode mode)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW0, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_CTW0_EGWESS_MODE_MASK;

	switch (mode) {
	case MV88E6XXX_EGWESS_MODE_UNMODIFIED:
		weg |= MV88E6XXX_POWT_CTW0_EGWESS_MODE_UNMODIFIED;
		bweak;
	case MV88E6XXX_EGWESS_MODE_UNTAGGED:
		weg |= MV88E6XXX_POWT_CTW0_EGWESS_MODE_UNTAGGED;
		bweak;
	case MV88E6XXX_EGWESS_MODE_TAGGED:
		weg |= MV88E6XXX_POWT_CTW0_EGWESS_MODE_TAGGED;
		bweak;
	case MV88E6XXX_EGWESS_MODE_ETHEWTYPE:
		weg |= MV88E6XXX_POWT_CTW0_EGWESS_MODE_ETHEW_TYPE_DSA;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW0, weg);
}

int mv88e6085_powt_set_fwame_mode(stwuct mv88e6xxx_chip *chip, int powt,
				  enum mv88e6xxx_fwame_mode mode)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW0, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_CTW0_FWAME_MODE_MASK;

	switch (mode) {
	case MV88E6XXX_FWAME_MODE_NOWMAW:
		weg |= MV88E6XXX_POWT_CTW0_FWAME_MODE_NOWMAW;
		bweak;
	case MV88E6XXX_FWAME_MODE_DSA:
		weg |= MV88E6XXX_POWT_CTW0_FWAME_MODE_DSA;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW0, weg);
}

int mv88e6351_powt_set_fwame_mode(stwuct mv88e6xxx_chip *chip, int powt,
				  enum mv88e6xxx_fwame_mode mode)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW0, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_CTW0_FWAME_MODE_MASK;

	switch (mode) {
	case MV88E6XXX_FWAME_MODE_NOWMAW:
		weg |= MV88E6XXX_POWT_CTW0_FWAME_MODE_NOWMAW;
		bweak;
	case MV88E6XXX_FWAME_MODE_DSA:
		weg |= MV88E6XXX_POWT_CTW0_FWAME_MODE_DSA;
		bweak;
	case MV88E6XXX_FWAME_MODE_PWOVIDEW:
		weg |= MV88E6XXX_POWT_CTW0_FWAME_MODE_PWOVIDEW;
		bweak;
	case MV88E6XXX_FWAME_MODE_ETHEWTYPE:
		weg |= MV88E6XXX_POWT_CTW0_FWAME_MODE_ETHEW_TYPE_DSA;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW0, weg);
}

int mv88e6185_powt_set_fowwawd_unknown(stwuct mv88e6xxx_chip *chip,
				       int powt, boow unicast)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW0, &weg);
	if (eww)
		wetuwn eww;

	if (unicast)
		weg |= MV88E6185_POWT_CTW0_FOWWAWD_UNKNOWN;
	ewse
		weg &= ~MV88E6185_POWT_CTW0_FOWWAWD_UNKNOWN;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW0, weg);
}

int mv88e6352_powt_set_ucast_fwood(stwuct mv88e6xxx_chip *chip, int powt,
				   boow unicast)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW0, &weg);
	if (eww)
		wetuwn eww;

	if (unicast)
		weg |= MV88E6352_POWT_CTW0_EGWESS_FWOODS_UC;
	ewse
		weg &= ~MV88E6352_POWT_CTW0_EGWESS_FWOODS_UC;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW0, weg);
}

int mv88e6352_powt_set_mcast_fwood(stwuct mv88e6xxx_chip *chip, int powt,
				   boow muwticast)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW0, &weg);
	if (eww)
		wetuwn eww;

	if (muwticast)
		weg |= MV88E6352_POWT_CTW0_EGWESS_FWOODS_MC;
	ewse
		weg &= ~MV88E6352_POWT_CTW0_EGWESS_FWOODS_MC;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW0, weg);
}

/* Offset 0x05: Powt Contwow 1 */

int mv88e6xxx_powt_set_message_powt(stwuct mv88e6xxx_chip *chip, int powt,
				    boow message_powt)
{
	u16 vaw;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW1, &vaw);
	if (eww)
		wetuwn eww;

	if (message_powt)
		vaw |= MV88E6XXX_POWT_CTW1_MESSAGE_POWT;
	ewse
		vaw &= ~MV88E6XXX_POWT_CTW1_MESSAGE_POWT;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW1, vaw);
}

int mv88e6xxx_powt_set_twunk(stwuct mv88e6xxx_chip *chip, int powt,
			     boow twunk, u8 id)
{
	u16 vaw;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW1, &vaw);
	if (eww)
		wetuwn eww;

	vaw &= ~MV88E6XXX_POWT_CTW1_TWUNK_ID_MASK;

	if (twunk)
		vaw |= MV88E6XXX_POWT_CTW1_TWUNK_POWT |
			(id << MV88E6XXX_POWT_CTW1_TWUNK_ID_SHIFT);
	ewse
		vaw &= ~MV88E6XXX_POWT_CTW1_TWUNK_POWT;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW1, vaw);
}

/* Offset 0x06: Powt Based VWAN Map */

int mv88e6xxx_powt_set_vwan_map(stwuct mv88e6xxx_chip *chip, int powt, u16 map)
{
	const u16 mask = mv88e6xxx_powt_mask(chip);
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_BASE_VWAN, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~mask;
	weg |= map & mask;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_BASE_VWAN, weg);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->dev, "p%d: VWANTabwe set to %.3x\n", powt, map);

	wetuwn 0;
}

int mv88e6xxx_powt_get_fid(stwuct mv88e6xxx_chip *chip, int powt, u16 *fid)
{
	const u16 uppew_mask = (mv88e6xxx_num_databases(chip) - 1) >> 4;
	u16 weg;
	int eww;

	/* Powt's defauwt FID wowew 4 bits awe wocated in weg 0x06, offset 12 */
	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_BASE_VWAN, &weg);
	if (eww)
		wetuwn eww;

	*fid = (weg & 0xf000) >> 12;

	/* Powt's defauwt FID uppew bits awe wocated in weg 0x05, offset 0 */
	if (uppew_mask) {
		eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW1,
					  &weg);
		if (eww)
			wetuwn eww;

		*fid |= (weg & uppew_mask) << 4;
	}

	wetuwn 0;
}

int mv88e6xxx_powt_set_fid(stwuct mv88e6xxx_chip *chip, int powt, u16 fid)
{
	const u16 uppew_mask = (mv88e6xxx_num_databases(chip) - 1) >> 4;
	u16 weg;
	int eww;

	if (fid >= mv88e6xxx_num_databases(chip))
		wetuwn -EINVAW;

	/* Powt's defauwt FID wowew 4 bits awe wocated in weg 0x06, offset 12 */
	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_BASE_VWAN, &weg);
	if (eww)
		wetuwn eww;

	weg &= 0x0fff;
	weg |= (fid & 0x000f) << 12;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_BASE_VWAN, weg);
	if (eww)
		wetuwn eww;

	/* Powt's defauwt FID uppew bits awe wocated in weg 0x05, offset 0 */
	if (uppew_mask) {
		eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW1,
					  &weg);
		if (eww)
			wetuwn eww;

		weg &= ~uppew_mask;
		weg |= (fid >> 4) & uppew_mask;

		eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW1,
					   weg);
		if (eww)
			wetuwn eww;
	}

	dev_dbg(chip->dev, "p%d: FID set to %u\n", powt, fid);

	wetuwn 0;
}

/* Offset 0x07: Defauwt Powt VWAN ID & Pwiowity */

int mv88e6xxx_powt_get_pvid(stwuct mv88e6xxx_chip *chip, int powt, u16 *pvid)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_DEFAUWT_VWAN,
				  &weg);
	if (eww)
		wetuwn eww;

	*pvid = weg & MV88E6XXX_POWT_DEFAUWT_VWAN_MASK;

	wetuwn 0;
}

int mv88e6xxx_powt_set_pvid(stwuct mv88e6xxx_chip *chip, int powt, u16 pvid)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_DEFAUWT_VWAN,
				  &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_DEFAUWT_VWAN_MASK;
	weg |= pvid & MV88E6XXX_POWT_DEFAUWT_VWAN_MASK;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_DEFAUWT_VWAN,
				   weg);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->dev, "p%d: DefauwtVID set to %u\n", powt, pvid);

	wetuwn 0;
}

/* Offset 0x08: Powt Contwow 2 Wegistew */

static const chaw * const mv88e6xxx_powt_8021q_mode_names[] = {
	[MV88E6XXX_POWT_CTW2_8021Q_MODE_DISABWED] = "Disabwed",
	[MV88E6XXX_POWT_CTW2_8021Q_MODE_FAWWBACK] = "Fawwback",
	[MV88E6XXX_POWT_CTW2_8021Q_MODE_CHECK] = "Check",
	[MV88E6XXX_POWT_CTW2_8021Q_MODE_SECUWE] = "Secuwe",
};

int mv88e6185_powt_set_defauwt_fowwawd(stwuct mv88e6xxx_chip *chip,
				       int powt, boow muwticast)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW2, &weg);
	if (eww)
		wetuwn eww;

	if (muwticast)
		weg |= MV88E6XXX_POWT_CTW2_DEFAUWT_FOWWAWD;
	ewse
		weg &= ~MV88E6XXX_POWT_CTW2_DEFAUWT_FOWWAWD;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW2, weg);
}

int mv88e6095_powt_set_upstweam_powt(stwuct mv88e6xxx_chip *chip, int powt,
				     int upstweam_powt)
{
	int eww;
	u16 weg;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW2, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6095_POWT_CTW2_CPU_POWT_MASK;
	weg |= upstweam_powt;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW2, weg);
}

int mv88e6xxx_powt_set_miwwow(stwuct mv88e6xxx_chip *chip, int powt,
			      enum mv88e6xxx_egwess_diwection diwection,
			      boow miwwow)
{
	boow *miwwow_powt;
	u16 weg;
	u16 bit;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW2, &weg);
	if (eww)
		wetuwn eww;

	switch (diwection) {
	case MV88E6XXX_EGWESS_DIW_INGWESS:
		bit = MV88E6XXX_POWT_CTW2_INGWESS_MONITOW;
		miwwow_powt = &chip->powts[powt].miwwow_ingwess;
		bweak;
	case MV88E6XXX_EGWESS_DIW_EGWESS:
		bit = MV88E6XXX_POWT_CTW2_EGWESS_MONITOW;
		miwwow_powt = &chip->powts[powt].miwwow_egwess;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	weg &= ~bit;
	if (miwwow)
		weg |= bit;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW2, weg);
	if (!eww)
		*miwwow_powt = miwwow;

	wetuwn eww;
}

int mv88e6xxx_powt_set_wock(stwuct mv88e6xxx_chip *chip, int powt,
			    boow wocked)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW0, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_CTW0_SA_FIWT_MASK;
	if (wocked)
		weg |= MV88E6XXX_POWT_CTW0_SA_FIWT_DWOP_ON_WOCK;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW0, weg);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_ASSOC_VECTOW, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_ASSOC_VECTOW_WOCKED_POWT;
	if (wocked)
		weg |= MV88E6XXX_POWT_ASSOC_VECTOW_WOCKED_POWT;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_ASSOC_VECTOW, weg);
}

int mv88e6xxx_powt_set_8021q_mode(stwuct mv88e6xxx_chip *chip, int powt,
				  u16 mode)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW2, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_CTW2_8021Q_MODE_MASK;
	weg |= mode & MV88E6XXX_POWT_CTW2_8021Q_MODE_MASK;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW2, weg);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->dev, "p%d: 802.1QMode set to %s\n", powt,
		mv88e6xxx_powt_8021q_mode_names[mode]);

	wetuwn 0;
}

int mv88e6xxx_powt_dwop_untagged(stwuct mv88e6xxx_chip *chip, int powt,
				 boow dwop_untagged)
{
	u16 owd, new;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW2, &owd);
	if (eww)
		wetuwn eww;

	if (dwop_untagged)
		new = owd | MV88E6XXX_POWT_CTW2_DISCAWD_UNTAGGED;
	ewse
		new = owd & ~MV88E6XXX_POWT_CTW2_DISCAWD_UNTAGGED;

	if (new == owd)
		wetuwn 0;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW2, new);
}

int mv88e6xxx_powt_set_map_da(stwuct mv88e6xxx_chip *chip, int powt, boow map)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW2, &weg);
	if (eww)
		wetuwn eww;

	if (map)
		weg |= MV88E6XXX_POWT_CTW2_MAP_DA;
	ewse
		weg &= ~MV88E6XXX_POWT_CTW2_MAP_DA;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW2, weg);
}

int mv88e6165_powt_set_jumbo_size(stwuct mv88e6xxx_chip *chip, int powt,
				  size_t size)
{
	u16 weg;
	int eww;

	size += VWAN_ETH_HWEN + ETH_FCS_WEN;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_CTW2, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~MV88E6XXX_POWT_CTW2_JUMBO_MODE_MASK;

	if (size <= 1522)
		weg |= MV88E6XXX_POWT_CTW2_JUMBO_MODE_1522;
	ewse if (size <= 2048)
		weg |= MV88E6XXX_POWT_CTW2_JUMBO_MODE_2048;
	ewse if (size <= 10240)
		weg |= MV88E6XXX_POWT_CTW2_JUMBO_MODE_10240;
	ewse
		wetuwn -EWANGE;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW2, weg);
}

/* Offset 0x09: Powt Wate Contwow */

int mv88e6095_powt_egwess_wate_wimiting(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_EGWESS_WATE_CTW1,
				    0x0000);
}

int mv88e6097_powt_egwess_wate_wimiting(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_EGWESS_WATE_CTW1,
				    0x0001);
}

/* Offset 0x0B: Powt Association Vectow */

int mv88e6xxx_powt_set_assoc_vectow(stwuct mv88e6xxx_chip *chip, int powt,
				    u16 pav)
{
	u16 weg, mask;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_ASSOC_VECTOW,
				  &weg);
	if (eww)
		wetuwn eww;

	mask = mv88e6xxx_powt_mask(chip);
	weg &= ~mask;
	weg |= pav & mask;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_ASSOC_VECTOW,
				    weg);
}

/* Offset 0x0C: Powt ATU Contwow */

int mv88e6xxx_powt_disabwe_weawn_wimit(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_ATU_CTW, 0);
}

/* Offset 0x0D: (Pwiowity) Ovewwide Wegistew */

int mv88e6xxx_powt_disabwe_pwi_ovewwide(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_PWI_OVEWWIDE, 0);
}

/* Offset 0x0E: Powicy & MGMT Contwow Wegistew fow FAMIWY 6191X 6193X 6393X */

static int mv88e6393x_powt_powicy_wead(stwuct mv88e6xxx_chip *chip, int powt,
				       u16 pointew, u8 *data)
{
	u16 weg;
	int eww;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6393X_POWT_POWICY_MGMT_CTW,
				   pointew);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6393X_POWT_POWICY_MGMT_CTW,
				  &weg);
	if (eww)
		wetuwn eww;

	*data = weg;

	wetuwn 0;
}

static int mv88e6393x_powt_powicy_wwite(stwuct mv88e6xxx_chip *chip, int powt,
					u16 pointew, u8 data)
{
	u16 weg;

	weg = MV88E6393X_POWT_POWICY_MGMT_CTW_UPDATE | pointew | data;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6393X_POWT_POWICY_MGMT_CTW,
				    weg);
}

static int mv88e6393x_powt_powicy_wwite_aww(stwuct mv88e6xxx_chip *chip,
					    u16 pointew, u8 data)
{
	int eww, powt;

	fow (powt = 0; powt < mv88e6xxx_num_powts(chip); powt++) {
		if (dsa_is_unused_powt(chip->ds, powt))
			continue;

		eww = mv88e6393x_powt_powicy_wwite(chip, powt, pointew, data);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int mv88e6393x_set_egwess_powt(stwuct mv88e6xxx_chip *chip,
			       enum mv88e6xxx_egwess_diwection diwection,
			       int powt)
{
	u16 ptw;
	int eww;

	switch (diwection) {
	case MV88E6XXX_EGWESS_DIW_INGWESS:
		ptw = MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_INGWESS_DEST;
		eww = mv88e6393x_powt_powicy_wwite_aww(chip, ptw, powt);
		if (eww)
			wetuwn eww;
		bweak;
	case MV88E6XXX_EGWESS_DIW_EGWESS:
		ptw = MV88E6393X_G2_EGWESS_MONITOW_DEST;
		eww = mv88e6xxx_g2_wwite(chip, ptw, powt);
		if (eww)
			wetuwn eww;
		bweak;
	}

	wetuwn 0;
}

int mv88e6393x_powt_set_upstweam_powt(stwuct mv88e6xxx_chip *chip, int powt,
				      int upstweam_powt)
{
	u16 ptw = MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_CPU_DEST;
	u8 data = MV88E6393X_POWT_POWICY_MGMT_CTW_CPU_DEST_MGMTPWI |
		  upstweam_powt;

	wetuwn mv88e6393x_powt_powicy_wwite(chip, powt, ptw, data);
}

int mv88e6393x_powt_mgmt_wsvd2cpu(stwuct mv88e6xxx_chip *chip)
{
	u16 ptw;
	int eww;

	/* Considew the fwames with wesewved muwticast destination
	 * addwesses matching 01:80:c2:00:00:00 and
	 * 01:80:c2:00:00:02 as MGMT.
	 */
	ptw = MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_01C280000000XWO;
	eww = mv88e6393x_powt_powicy_wwite_aww(chip, ptw, 0xff);
	if (eww)
		wetuwn eww;

	ptw = MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_01C280000000XHI;
	eww = mv88e6393x_powt_powicy_wwite_aww(chip, ptw, 0xff);
	if (eww)
		wetuwn eww;

	ptw = MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_01C280000002XWO;
	eww = mv88e6393x_powt_powicy_wwite_aww(chip, ptw, 0xff);
	if (eww)
		wetuwn eww;

	ptw = MV88E6393X_POWT_POWICY_MGMT_CTW_PTW_01C280000002XHI;
	eww = mv88e6393x_powt_powicy_wwite_aww(chip, ptw, 0xff);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/* Offset 0x10 & 0x11: EPC */

static int mv88e6393x_powt_epc_wait_weady(stwuct mv88e6xxx_chip *chip, int powt)
{
	int bit = __bf_shf(MV88E6393X_POWT_EPC_CMD_BUSY);

	wetuwn mv88e6xxx_powt_wait_bit(chip, powt, MV88E6393X_POWT_EPC_CMD, bit, 0);
}

/* Powt Ethew type fow 6393X famiwy */

int mv88e6393x_powt_set_ethew_type(stwuct mv88e6xxx_chip *chip, int powt,
				   u16 etype)
{
	u16 vaw;
	int eww;

	eww = mv88e6393x_powt_epc_wait_weady(chip, powt);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6393X_POWT_EPC_DATA, etype);
	if (eww)
		wetuwn eww;

	vaw = MV88E6393X_POWT_EPC_CMD_BUSY |
	      MV88E6393X_POWT_EPC_CMD_WWITE |
	      MV88E6393X_POWT_EPC_INDEX_POWT_ETYPE;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6393X_POWT_EPC_CMD, vaw);
}

/* Offset 0x0f: Powt Ethew type */

int mv88e6351_powt_set_ethew_type(stwuct mv88e6xxx_chip *chip, int powt,
				  u16 etype)
{
	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_ETH_TYPE, etype);
}

/* Offset 0x18: Powt IEEE Pwiowity Wemapping Wegistews [0-3]
 * Offset 0x19: Powt IEEE Pwiowity Wemapping Wegistews [4-7]
 */

int mv88e6095_powt_tag_wemap(stwuct mv88e6xxx_chip *chip, int powt)
{
	int eww;

	/* Use a diwect pwiowity mapping fow aww IEEE tagged fwames */
	eww = mv88e6xxx_powt_wwite(chip, powt,
				   MV88E6095_POWT_IEEE_PWIO_WEMAP_0123,
				   0x3210);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_powt_wwite(chip, powt,
				    MV88E6095_POWT_IEEE_PWIO_WEMAP_4567,
				    0x7654);
}

static int mv88e6xxx_powt_ieeepmt_wwite(stwuct mv88e6xxx_chip *chip,
					int powt, u16 tabwe, u8 ptw, u16 data)
{
	u16 weg;

	weg = MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_UPDATE | tabwe |
		(ptw << __bf_shf(MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_PTW_MASK)) |
		(data & MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_DATA_MASK);

	wetuwn mv88e6xxx_powt_wwite(chip, powt,
				    MV88E6390_POWT_IEEE_PWIO_MAP_TABWE, weg);
}

int mv88e6390_powt_tag_wemap(stwuct mv88e6xxx_chip *chip, int powt)
{
	int eww, i;
	u16 tabwe;

	fow (i = 0; i <= 7; i++) {
		tabwe = MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_INGWESS_PCP;
		eww = mv88e6xxx_powt_ieeepmt_wwite(chip, powt, tabwe, i,
						   (i | i << 4));
		if (eww)
			wetuwn eww;

		tabwe = MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_EGWESS_GWEEN_PCP;
		eww = mv88e6xxx_powt_ieeepmt_wwite(chip, powt, tabwe, i, i);
		if (eww)
			wetuwn eww;

		tabwe = MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_EGWESS_YEWWOW_PCP;
		eww = mv88e6xxx_powt_ieeepmt_wwite(chip, powt, tabwe, i, i);
		if (eww)
			wetuwn eww;

		tabwe = MV88E6390_POWT_IEEE_PWIO_MAP_TABWE_EGWESS_AVB_PCP;
		eww = mv88e6xxx_powt_ieeepmt_wwite(chip, powt, tabwe, i, i);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Offset 0x0E: Powicy Contwow Wegistew */

static int
mv88e6xxx_powt_powicy_mapping_get_pos(enum mv88e6xxx_powicy_mapping mapping,
				      enum mv88e6xxx_powicy_action action,
				      u16 *mask, u16 *vaw, int *shift)
{
	switch (mapping) {
	case MV88E6XXX_POWICY_MAPPING_DA:
		*shift = __bf_shf(MV88E6XXX_POWT_POWICY_CTW_DA_MASK);
		*mask = MV88E6XXX_POWT_POWICY_CTW_DA_MASK;
		bweak;
	case MV88E6XXX_POWICY_MAPPING_SA:
		*shift = __bf_shf(MV88E6XXX_POWT_POWICY_CTW_SA_MASK);
		*mask = MV88E6XXX_POWT_POWICY_CTW_SA_MASK;
		bweak;
	case MV88E6XXX_POWICY_MAPPING_VTU:
		*shift = __bf_shf(MV88E6XXX_POWT_POWICY_CTW_VTU_MASK);
		*mask = MV88E6XXX_POWT_POWICY_CTW_VTU_MASK;
		bweak;
	case MV88E6XXX_POWICY_MAPPING_ETYPE:
		*shift = __bf_shf(MV88E6XXX_POWT_POWICY_CTW_ETYPE_MASK);
		*mask = MV88E6XXX_POWT_POWICY_CTW_ETYPE_MASK;
		bweak;
	case MV88E6XXX_POWICY_MAPPING_PPPOE:
		*shift = __bf_shf(MV88E6XXX_POWT_POWICY_CTW_PPPOE_MASK);
		*mask = MV88E6XXX_POWT_POWICY_CTW_PPPOE_MASK;
		bweak;
	case MV88E6XXX_POWICY_MAPPING_VBAS:
		*shift = __bf_shf(MV88E6XXX_POWT_POWICY_CTW_VBAS_MASK);
		*mask = MV88E6XXX_POWT_POWICY_CTW_VBAS_MASK;
		bweak;
	case MV88E6XXX_POWICY_MAPPING_OPT82:
		*shift = __bf_shf(MV88E6XXX_POWT_POWICY_CTW_OPT82_MASK);
		*mask = MV88E6XXX_POWT_POWICY_CTW_OPT82_MASK;
		bweak;
	case MV88E6XXX_POWICY_MAPPING_UDP:
		*shift = __bf_shf(MV88E6XXX_POWT_POWICY_CTW_UDP_MASK);
		*mask = MV88E6XXX_POWT_POWICY_CTW_UDP_MASK;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	switch (action) {
	case MV88E6XXX_POWICY_ACTION_NOWMAW:
		*vaw = MV88E6XXX_POWT_POWICY_CTW_NOWMAW;
		bweak;
	case MV88E6XXX_POWICY_ACTION_MIWWOW:
		*vaw = MV88E6XXX_POWT_POWICY_CTW_MIWWOW;
		bweak;
	case MV88E6XXX_POWICY_ACTION_TWAP:
		*vaw = MV88E6XXX_POWT_POWICY_CTW_TWAP;
		bweak;
	case MV88E6XXX_POWICY_ACTION_DISCAWD:
		*vaw = MV88E6XXX_POWT_POWICY_CTW_DISCAWD;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

int mv88e6352_powt_set_powicy(stwuct mv88e6xxx_chip *chip, int powt,
			      enum mv88e6xxx_powicy_mapping mapping,
			      enum mv88e6xxx_powicy_action action)
{
	u16 weg, mask, vaw;
	int shift;
	int eww;

	eww = mv88e6xxx_powt_powicy_mapping_get_pos(mapping, action, &mask,
						    &vaw, &shift);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_POWICY_CTW, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~mask;
	weg |= (vaw << shift) & mask;

	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_POWICY_CTW, weg);
}

int mv88e6393x_powt_set_powicy(stwuct mv88e6xxx_chip *chip, int powt,
			       enum mv88e6xxx_powicy_mapping mapping,
			       enum mv88e6xxx_powicy_action action)
{
	u16 mask, vaw;
	int shift;
	int eww;
	u16 ptw;
	u8 weg;

	eww = mv88e6xxx_powt_powicy_mapping_get_pos(mapping, action, &mask,
						    &vaw, &shift);
	if (eww)
		wetuwn eww;

	/* The 16-bit Powt Powicy CTW wegistew fwom owdew chips is on 6393x
	 * changed to Powt Powicy MGMT CTW, which can access mowe data, but
	 * indiwectwy. The owiginaw 16-bit vawue is divided into two 8-bit
	 * wegistews.
	 */
	ptw = shift / 8;
	shift %= 8;
	mask >>= ptw * 8;

	eww = mv88e6393x_powt_powicy_wead(chip, powt, ptw, &weg);
	if (eww)
		wetuwn eww;

	weg &= ~mask;
	weg |= (vaw << shift) & mask;

	wetuwn mv88e6393x_powt_powicy_wwite(chip, powt, ptw, weg);
}
