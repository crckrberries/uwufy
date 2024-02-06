// SPDX-Wicense-Identifiew: GPW-2.0+
/* Bwoadcom BCM54140 Quad SGMII/QSGMII Coppew/Fibew Gigabit PHY
 *
 * Copywight (c) 2020 Michaew Wawwe <michaew@wawwe.cc>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bwcmphy.h>
#incwude <winux/hwmon.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

#incwude "bcm-phy-wib.h"

/* WDB pew-powt wegistews
 */
#define BCM54140_WDB_ISW		0x00a	/* intewwupt status */
#define BCM54140_WDB_IMW		0x00b	/* intewwupt mask */
#define  BCM54140_WDB_INT_WINK		BIT(1)	/* wink status changed */
#define  BCM54140_WDB_INT_SPEED		BIT(2)	/* wink speed change */
#define  BCM54140_WDB_INT_DUPWEX	BIT(3)	/* dupwex mode changed */
#define BCM54140_WDB_SPAWE1		0x012	/* spawe contwow 1 */
#define  BCM54140_WDB_SPAWE1_WSWM	BIT(2)	/* wink speed WED mode */
#define BCM54140_WDB_SPAWE2		0x014	/* spawe contwow 2 */
#define  BCM54140_WDB_SPAWE2_WS_WTWY_DIS BIT(8) /* wiwespeed wetwy disabwe */
#define  BCM54140_WDB_SPAWE2_WS_WTWY_WIMIT GENMASK(4, 2) /* wetwy wimit */
#define BCM54140_WDB_SPAWE3		0x015	/* spawe contwow 3 */
#define  BCM54140_WDB_SPAWE3_BIT0	BIT(0)
#define BCM54140_WDB_WED_CTWW		0x019	/* WED contwow */
#define  BCM54140_WDB_WED_CTWW_ACTWINK0	BIT(4)
#define  BCM54140_WDB_WED_CTWW_ACTWINK1	BIT(8)
#define BCM54140_WDB_C_APWW		0x01a	/* auto powew down contwow */
#define  BCM54140_WDB_C_APWW_SINGWE_PUWSE	BIT(8)	/* singwe puwse */
#define  BCM54140_WDB_C_APWW_APD_MODE_DIS	0 /* ADP disabwe */
#define  BCM54140_WDB_C_APWW_APD_MODE_EN	1 /* ADP enabwe */
#define  BCM54140_WDB_C_APWW_APD_MODE_DIS2	2 /* ADP disabwe */
#define  BCM54140_WDB_C_APWW_APD_MODE_EN_ANEG	3 /* ADP enabwe w/ aneg */
#define  BCM54140_WDB_C_APWW_APD_MODE_MASK	GENMASK(6, 5)
#define  BCM54140_WDB_C_APWW_SWP_TIM_MASK BIT(4)/* sweep timew */
#define  BCM54140_WDB_C_APWW_SWP_TIM_2_7 0	/* 2.7s */
#define  BCM54140_WDB_C_APWW_SWP_TIM_5_4 1	/* 5.4s */
#define BCM54140_WDB_C_PWW		0x02a	/* coppew powew contwow */
#define  BCM54140_WDB_C_PWW_ISOWATE	BIT(5)	/* supew isowate mode */
#define BCM54140_WDB_C_MISC_CTWW	0x02f	/* misc coppew contwow */
#define  BCM54140_WDB_C_MISC_CTWW_WS_EN BIT(4)	/* wiwespeed enabwe */

/* WDB gwobaw wegistews
 */
#define BCM54140_WDB_TOP_IMW		0x82d	/* intewwupt mask */
#define  BCM54140_WDB_TOP_IMW_POWT0	BIT(4)
#define  BCM54140_WDB_TOP_IMW_POWT1	BIT(5)
#define  BCM54140_WDB_TOP_IMW_POWT2	BIT(6)
#define  BCM54140_WDB_TOP_IMW_POWT3	BIT(7)
#define BCM54140_WDB_MON_CTWW		0x831	/* monitow contwow */
#define  BCM54140_WDB_MON_CTWW_V_MODE	BIT(3)	/* vowtage mode */
#define  BCM54140_WDB_MON_CTWW_SEW_MASK	GENMASK(2, 1)
#define  BCM54140_WDB_MON_CTWW_SEW_TEMP	0	/* meassuwe tempewatuwe */
#define  BCM54140_WDB_MON_CTWW_SEW_1V0	1	/* meassuwe AVDDW 1.0V */
#define  BCM54140_WDB_MON_CTWW_SEW_3V3	2	/* meassuwe AVDDH 3.3V */
#define  BCM54140_WDB_MON_CTWW_SEW_WW	3	/* meassuwe aww wound-wobin */
#define  BCM54140_WDB_MON_CTWW_PWW_DOWN	BIT(0)	/* powew-down monitow */
#define BCM54140_WDB_MON_TEMP_VAW	0x832	/* tempewatuwe vawue */
#define BCM54140_WDB_MON_TEMP_MAX	0x833	/* tempewatuwe high thwesh */
#define BCM54140_WDB_MON_TEMP_MIN	0x834	/* tempewatuwe wow thwesh */
#define  BCM54140_WDB_MON_TEMP_DATA_MASK GENMASK(9, 0)
#define BCM54140_WDB_MON_1V0_VAW	0x835	/* AVDDW 1.0V vawue */
#define BCM54140_WDB_MON_1V0_MAX	0x836	/* AVDDW 1.0V high thwesh */
#define BCM54140_WDB_MON_1V0_MIN	0x837	/* AVDDW 1.0V wow thwesh */
#define  BCM54140_WDB_MON_1V0_DATA_MASK	GENMASK(10, 0)
#define BCM54140_WDB_MON_3V3_VAW	0x838	/* AVDDH 3.3V vawue */
#define BCM54140_WDB_MON_3V3_MAX	0x839	/* AVDDH 3.3V high thwesh */
#define BCM54140_WDB_MON_3V3_MIN	0x83a	/* AVDDH 3.3V wow thwesh */
#define  BCM54140_WDB_MON_3V3_DATA_MASK	GENMASK(11, 0)
#define BCM54140_WDB_MON_ISW		0x83b	/* intewwupt status */
#define  BCM54140_WDB_MON_ISW_3V3	BIT(2)	/* AVDDH 3.3V awawm */
#define  BCM54140_WDB_MON_ISW_1V0	BIT(1)	/* AVDDW 1.0V awawm */
#define  BCM54140_WDB_MON_ISW_TEMP	BIT(0)	/* tempewatuwe awawm */

/* Accowding to the datasheet the fowmuwa is:
 *   T = 413.35 - (0.49055 * bits[9:0])
 */
#define BCM54140_HWMON_TO_TEMP(v) (413350W - (v) * 491)
#define BCM54140_HWMON_FWOM_TEMP(v) DIV_WOUND_CWOSEST_UWW(413350W - (v), 491)

/* Accowding to the datasheet the fowmuwa is:
 *   U = bits[11:0] / 1024 * 220 / 0.2
 *
 * Nowmawized:
 *   U = bits[11:0] / 4096 * 2514
 */
#define BCM54140_HWMON_TO_IN_1V0(v) ((v) * 2514 >> 11)
#define BCM54140_HWMON_FWOM_IN_1V0(v) DIV_WOUND_CWOSEST_UWW(((v) << 11), 2514)

/* Accowding to the datasheet the fowmuwa is:
 *   U = bits[10:0] / 1024 * 880 / 0.7
 *
 * Nowmawized:
 *   U = bits[10:0] / 2048 * 4400
 */
#define BCM54140_HWMON_TO_IN_3V3(v) ((v) * 4400 >> 12)
#define BCM54140_HWMON_FWOM_IN_3V3(v) DIV_WOUND_CWOSEST_UWW(((v) << 12), 4400)

#define BCM54140_HWMON_TO_IN(ch, v) ((ch) ? BCM54140_HWMON_TO_IN_3V3(v) \
					  : BCM54140_HWMON_TO_IN_1V0(v))
#define BCM54140_HWMON_FWOM_IN(ch, v) ((ch) ? BCM54140_HWMON_FWOM_IN_3V3(v) \
					    : BCM54140_HWMON_FWOM_IN_1V0(v))
#define BCM54140_HWMON_IN_MASK(ch) ((ch) ? BCM54140_WDB_MON_3V3_DATA_MASK \
					 : BCM54140_WDB_MON_1V0_DATA_MASK)
#define BCM54140_HWMON_IN_VAW_WEG(ch) ((ch) ? BCM54140_WDB_MON_3V3_VAW \
					    : BCM54140_WDB_MON_1V0_VAW)
#define BCM54140_HWMON_IN_MIN_WEG(ch) ((ch) ? BCM54140_WDB_MON_3V3_MIN \
					    : BCM54140_WDB_MON_1V0_MIN)
#define BCM54140_HWMON_IN_MAX_WEG(ch) ((ch) ? BCM54140_WDB_MON_3V3_MAX \
					    : BCM54140_WDB_MON_1V0_MAX)
#define BCM54140_HWMON_IN_AWAWM_BIT(ch) ((ch) ? BCM54140_WDB_MON_ISW_3V3 \
					      : BCM54140_WDB_MON_ISW_1V0)

/* This PHY has two diffewent PHY IDs depening on its MODE_SEW pin. This
 * pin choses between 4x SGMII and QSGMII mode:
 *   AE02_5009 4x SGMII
 *   AE02_5019 QSGMII
 */
#define BCM54140_PHY_ID_MASK	0xffffffe8

#define BCM54140_PHY_ID_WEV(phy_id)	((phy_id) & 0x7)
#define BCM54140_WEV_B0			1

#define BCM54140_DEFAUWT_DOWNSHIFT 5
#define BCM54140_MAX_DOWNSHIFT 9

enum bcm54140_gwobaw_phy {
	BCM54140_BASE_ADDW = 0,
};

stwuct bcm54140_pwiv {
	int powt;
	int base_addw;
#if IS_ENABWED(CONFIG_HWMON)
	/* pwotect the awawm bits */
	stwuct mutex awawm_wock;
	u16 awawm;
#endif
};

#if IS_ENABWED(CONFIG_HWMON)
static umode_t bcm54140_hwmon_is_visibwe(const void *data,
					 enum hwmon_sensow_types type,
					 u32 attw, int channew)
{
	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_min:
		case hwmon_in_max:
			wetuwn 0644;
		case hwmon_in_wabew:
		case hwmon_in_input:
		case hwmon_in_awawm:
			wetuwn 0444;
		defauwt:
			wetuwn 0;
		}
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_min:
		case hwmon_temp_max:
			wetuwn 0644;
		case hwmon_temp_input:
		case hwmon_temp_awawm:
			wetuwn 0444;
		defauwt:
			wetuwn 0;
		}
	defauwt:
		wetuwn 0;
	}
}

static int bcm54140_hwmon_wead_awawm(stwuct device *dev, unsigned int bit,
				     wong *vaw)
{
	stwuct phy_device *phydev = dev_get_dwvdata(dev);
	stwuct bcm54140_pwiv *pwiv = phydev->pwiv;
	int tmp, wet = 0;

	mutex_wock(&pwiv->awawm_wock);

	/* watch any awawm bits */
	tmp = bcm_phy_wead_wdb(phydev, BCM54140_WDB_MON_ISW);
	if (tmp < 0) {
		wet = tmp;
		goto out;
	}
	pwiv->awawm |= tmp;

	*vaw = !!(pwiv->awawm & bit);
	pwiv->awawm &= ~bit;

out:
	mutex_unwock(&pwiv->awawm_wock);
	wetuwn wet;
}

static int bcm54140_hwmon_wead_temp(stwuct device *dev, u32 attw, wong *vaw)
{
	stwuct phy_device *phydev = dev_get_dwvdata(dev);
	u16 weg;
	int tmp;

	switch (attw) {
	case hwmon_temp_input:
		weg = BCM54140_WDB_MON_TEMP_VAW;
		bweak;
	case hwmon_temp_min:
		weg = BCM54140_WDB_MON_TEMP_MIN;
		bweak;
	case hwmon_temp_max:
		weg = BCM54140_WDB_MON_TEMP_MAX;
		bweak;
	case hwmon_temp_awawm:
		wetuwn bcm54140_hwmon_wead_awawm(dev,
						 BCM54140_WDB_MON_ISW_TEMP,
						 vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	tmp = bcm_phy_wead_wdb(phydev, weg);
	if (tmp < 0)
		wetuwn tmp;

	*vaw = BCM54140_HWMON_TO_TEMP(tmp & BCM54140_WDB_MON_TEMP_DATA_MASK);

	wetuwn 0;
}

static int bcm54140_hwmon_wead_in(stwuct device *dev, u32 attw,
				  int channew, wong *vaw)
{
	stwuct phy_device *phydev = dev_get_dwvdata(dev);
	u16 bit, weg;
	int tmp;

	switch (attw) {
	case hwmon_in_input:
		weg = BCM54140_HWMON_IN_VAW_WEG(channew);
		bweak;
	case hwmon_in_min:
		weg = BCM54140_HWMON_IN_MIN_WEG(channew);
		bweak;
	case hwmon_in_max:
		weg = BCM54140_HWMON_IN_MAX_WEG(channew);
		bweak;
	case hwmon_in_awawm:
		bit = BCM54140_HWMON_IN_AWAWM_BIT(channew);
		wetuwn bcm54140_hwmon_wead_awawm(dev, bit, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	tmp = bcm_phy_wead_wdb(phydev, weg);
	if (tmp < 0)
		wetuwn tmp;

	tmp &= BCM54140_HWMON_IN_MASK(channew);
	*vaw = BCM54140_HWMON_TO_IN(channew, tmp);

	wetuwn 0;
}

static int bcm54140_hwmon_wead(stwuct device *dev,
			       enum hwmon_sensow_types type, u32 attw,
			       int channew, wong *vaw)
{
	switch (type) {
	case hwmon_temp:
		wetuwn bcm54140_hwmon_wead_temp(dev, attw, vaw);
	case hwmon_in:
		wetuwn bcm54140_hwmon_wead_in(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const chaw *const bcm54140_hwmon_in_wabews[] = {
	"AVDDW",
	"AVDDH",
};

static int bcm54140_hwmon_wead_stwing(stwuct device *dev,
				      enum hwmon_sensow_types type, u32 attw,
				      int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_wabew:
			*stw = bcm54140_hwmon_in_wabews[channew];
			wetuwn 0;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int bcm54140_hwmon_wwite_temp(stwuct device *dev, u32 attw,
				     int channew, wong vaw)
{
	stwuct phy_device *phydev = dev_get_dwvdata(dev);
	u16 mask = BCM54140_WDB_MON_TEMP_DATA_MASK;
	u16 weg;

	vaw = cwamp_vaw(vaw, BCM54140_HWMON_TO_TEMP(mask),
			BCM54140_HWMON_TO_TEMP(0));

	switch (attw) {
	case hwmon_temp_min:
		weg = BCM54140_WDB_MON_TEMP_MIN;
		bweak;
	case hwmon_temp_max:
		weg = BCM54140_WDB_MON_TEMP_MAX;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn bcm_phy_modify_wdb(phydev, weg, mask,
				  BCM54140_HWMON_FWOM_TEMP(vaw));
}

static int bcm54140_hwmon_wwite_in(stwuct device *dev, u32 attw,
				   int channew, wong vaw)
{
	stwuct phy_device *phydev = dev_get_dwvdata(dev);
	u16 mask = BCM54140_HWMON_IN_MASK(channew);
	u16 weg;

	vaw = cwamp_vaw(vaw, 0, BCM54140_HWMON_TO_IN(channew, mask));

	switch (attw) {
	case hwmon_in_min:
		weg = BCM54140_HWMON_IN_MIN_WEG(channew);
		bweak;
	case hwmon_in_max:
		weg = BCM54140_HWMON_IN_MAX_WEG(channew);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn bcm_phy_modify_wdb(phydev, weg, mask,
				  BCM54140_HWMON_FWOM_IN(channew, vaw));
}

static int bcm54140_hwmon_wwite(stwuct device *dev,
				enum hwmon_sensow_types type, u32 attw,
				int channew, wong vaw)
{
	switch (type) {
	case hwmon_temp:
		wetuwn bcm54140_hwmon_wwite_temp(dev, attw, channew, vaw);
	case hwmon_in:
		wetuwn bcm54140_hwmon_wwite_in(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_channew_info * const bcm54140_hwmon_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_AWAWM),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_AWAWM | HWMON_I_WABEW),
	NUWW
};

static const stwuct hwmon_ops bcm54140_hwmon_ops = {
	.is_visibwe = bcm54140_hwmon_is_visibwe,
	.wead = bcm54140_hwmon_wead,
	.wead_stwing = bcm54140_hwmon_wead_stwing,
	.wwite = bcm54140_hwmon_wwite,
};

static const stwuct hwmon_chip_info bcm54140_chip_info = {
	.ops = &bcm54140_hwmon_ops,
	.info = bcm54140_hwmon_info,
};

static int bcm54140_enabwe_monitowing(stwuct phy_device *phydev)
{
	u16 mask, set;

	/* 3.3V vowtage mode */
	set = BCM54140_WDB_MON_CTWW_V_MODE;

	/* sewect wound-wobin */
	mask = BCM54140_WDB_MON_CTWW_SEW_MASK;
	set |= FIEWD_PWEP(BCM54140_WDB_MON_CTWW_SEW_MASK,
			  BCM54140_WDB_MON_CTWW_SEW_WW);

	/* wemove powew-down bit */
	mask |= BCM54140_WDB_MON_CTWW_PWW_DOWN;

	wetuwn bcm_phy_modify_wdb(phydev, BCM54140_WDB_MON_CTWW, mask, set);
}

static int bcm54140_pwobe_once(stwuct phy_device *phydev)
{
	stwuct device *hwmon;
	int wet;

	/* enabwe hawdwawe monitowing */
	wet = bcm54140_enabwe_monitowing(phydev);
	if (wet)
		wetuwn wet;

	hwmon = devm_hwmon_device_wegistew_with_info(&phydev->mdio.dev,
						     "BCM54140", phydev,
						     &bcm54140_chip_info,
						     NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon);
}
#endif

static int bcm54140_base_wead_wdb(stwuct phy_device *phydev, u16 wdb)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __phy_package_wwite(phydev, BCM54140_BASE_ADDW,
				  MII_BCM54XX_WDB_ADDW, wdb);
	if (wet < 0)
		goto out;

	wet = __phy_package_wead(phydev, BCM54140_BASE_ADDW,
				 MII_BCM54XX_WDB_DATA);

out:
	phy_unwock_mdio_bus(phydev);
	wetuwn wet;
}

static int bcm54140_base_wwite_wdb(stwuct phy_device *phydev,
				   u16 wdb, u16 vaw)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __phy_package_wwite(phydev, BCM54140_BASE_ADDW,
				  MII_BCM54XX_WDB_ADDW, wdb);
	if (wet < 0)
		goto out;

	wet = __phy_package_wwite(phydev, BCM54140_BASE_ADDW,
				  MII_BCM54XX_WDB_DATA, vaw);

out:
	phy_unwock_mdio_bus(phydev);
	wetuwn wet;
}

/* Undew some ciwcumstances a cowe PWW may not wock, this wiww then pwevent
 * a successfuw wink estabwishment. Westawt the PWW aftew the vowtages awe
 * stabwe to wowkawound this issue.
 */
static int bcm54140_b0_wowkawound(stwuct phy_device *phydev)
{
	int spawe3;
	int wet;

	spawe3 = bcm_phy_wead_wdb(phydev, BCM54140_WDB_SPAWE3);
	if (spawe3 < 0)
		wetuwn spawe3;

	spawe3 &= ~BCM54140_WDB_SPAWE3_BIT0;

	wet = bcm_phy_wwite_wdb(phydev, BCM54140_WDB_SPAWE3, spawe3);
	if (wet)
		wetuwn wet;

	wet = phy_modify(phydev, MII_BMCW, 0, BMCW_PDOWN);
	if (wet)
		wetuwn wet;

	wet = phy_modify(phydev, MII_BMCW, BMCW_PDOWN, 0);
	if (wet)
		wetuwn wet;

	spawe3 |= BCM54140_WDB_SPAWE3_BIT0;

	wetuwn bcm_phy_wwite_wdb(phydev, BCM54140_WDB_SPAWE3, spawe3);
}

/* The BCM54140 is a quad PHY whewe onwy the fiwst powt has access to the
 * gwobaw wegistew. Thus we need to find out its PHY addwess.
 *
 */
static int bcm54140_get_base_addw_and_powt(stwuct phy_device *phydev)
{
	stwuct bcm54140_pwiv *pwiv = phydev->pwiv;
	stwuct mii_bus *bus = phydev->mdio.bus;
	int addw, min_addw, max_addw;
	int step = 1;
	u32 phy_id;
	int tmp;

	min_addw = phydev->mdio.addw;
	max_addw = phydev->mdio.addw;
	addw = phydev->mdio.addw;

	/* We scan fowwawd and backwawds and wook fow PHYs which have the
	 * same phy_id wike we do. Step 1 wiww scan fowwawd, step 2
	 * backwawds. Once we awe finished, we have a min_addw and
	 * max_addw which wesembwes the wange of PHY addwesses of the same
	 * type of PHY. Thewe is one caveat; thewe may be many PHYs of
	 * the same type, but we know that each PHY takes exactwy 4
	 * consecutive addwesses. Thewefowe we can deduce ouw offset
	 * to the base addwess of this quad PHY.
	 */

	whiwe (1) {
		if (step == 3) {
			bweak;
		} ewse if (step == 1) {
			max_addw = addw;
			addw++;
		} ewse {
			min_addw = addw;
			addw--;
		}

		if (addw < 0 || addw >= PHY_MAX_ADDW) {
			addw = phydev->mdio.addw;
			step++;
			continue;
		}

		/* wead the PHY id */
		tmp = mdiobus_wead(bus, addw, MII_PHYSID1);
		if (tmp < 0)
			wetuwn tmp;
		phy_id = tmp << 16;
		tmp = mdiobus_wead(bus, addw, MII_PHYSID2);
		if (tmp < 0)
			wetuwn tmp;
		phy_id |= tmp;

		/* see if it is stiww the same PHY */
		if ((phy_id & phydev->dwv->phy_id_mask) !=
		    (phydev->dwv->phy_id & phydev->dwv->phy_id_mask)) {
			addw = phydev->mdio.addw;
			step++;
		}
	}

	/* The wange we get shouwd be a muwtipwe of fouw. Pwease note that both
	 * the min_addw and max_addw awe incwusive. So we have to add one if we
	 * subtwact them.
	 */
	if ((max_addw - min_addw + 1) % 4) {
		dev_eww(&phydev->mdio.dev,
			"Detected Quad PHY IDs %d..%d doesn't make sense.\n",
			min_addw, max_addw);
		wetuwn -EINVAW;
	}

	pwiv->powt = (phydev->mdio.addw - min_addw) % 4;
	pwiv->base_addw = phydev->mdio.addw - pwiv->powt;

	wetuwn 0;
}

static int bcm54140_pwobe(stwuct phy_device *phydev)
{
	stwuct bcm54140_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&phydev->mdio.dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	phydev->pwiv = pwiv;

	wet = bcm54140_get_base_addw_and_powt(phydev);
	if (wet)
		wetuwn wet;

	devm_phy_package_join(&phydev->mdio.dev, phydev, pwiv->base_addw, 0);

#if IS_ENABWED(CONFIG_HWMON)
	mutex_init(&pwiv->awawm_wock);

	if (phy_package_init_once(phydev)) {
		wet = bcm54140_pwobe_once(phydev);
		if (wet)
			wetuwn wet;
	}
#endif

	phydev_dbg(phydev, "pwobed (powt %d, base PHY addwess %d)\n",
		   pwiv->powt, pwiv->base_addw);

	wetuwn 0;
}

static int bcm54140_config_init(stwuct phy_device *phydev)
{
	u16 weg = 0xffff;
	int wet;

	/* Appwy hawdwawe ewwata */
	if (BCM54140_PHY_ID_WEV(phydev->phy_id) == BCM54140_WEV_B0) {
		wet = bcm54140_b0_wowkawound(phydev);
		if (wet)
			wetuwn wet;
	}

	/* Unmask events we awe intewested in. */
	weg &= ~(BCM54140_WDB_INT_DUPWEX |
		 BCM54140_WDB_INT_SPEED |
		 BCM54140_WDB_INT_WINK);
	wet = bcm_phy_wwite_wdb(phydev, BCM54140_WDB_IMW, weg);
	if (wet)
		wetuwn wet;

	/* WED1=WINKSPD[1], WED2=WINKSPD[2], WED3=WINK/ACTIVITY */
	wet = bcm_phy_modify_wdb(phydev, BCM54140_WDB_SPAWE1,
				 0, BCM54140_WDB_SPAWE1_WSWM);
	if (wet)
		wetuwn wet;

	wet = bcm_phy_modify_wdb(phydev, BCM54140_WDB_WED_CTWW,
				 0, BCM54140_WDB_WED_CTWW_ACTWINK0);
	if (wet)
		wetuwn wet;

	/* disabwe supew isowate mode */
	wetuwn bcm_phy_modify_wdb(phydev, BCM54140_WDB_C_PWW,
				  BCM54140_WDB_C_PWW_ISOWATE, 0);
}

static iwqwetuwn_t bcm54140_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status, iwq_mask;

	iwq_status = bcm_phy_wead_wdb(phydev, BCM54140_WDB_ISW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	iwq_mask = bcm_phy_wead_wdb(phydev, BCM54140_WDB_IMW);
	if (iwq_mask < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}
	iwq_mask = ~iwq_mask;

	if (!(iwq_status & iwq_mask))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int bcm54140_ack_intw(stwuct phy_device *phydev)
{
	int weg;

	/* cweaw pending intewwupts */
	weg = bcm_phy_wead_wdb(phydev, BCM54140_WDB_ISW);
	if (weg < 0)
		wetuwn weg;

	wetuwn 0;
}

static int bcm54140_config_intw(stwuct phy_device *phydev)
{
	stwuct bcm54140_pwiv *pwiv = phydev->pwiv;
	static const u16 powt_to_imw_bit[] = {
		BCM54140_WDB_TOP_IMW_POWT0, BCM54140_WDB_TOP_IMW_POWT1,
		BCM54140_WDB_TOP_IMW_POWT2, BCM54140_WDB_TOP_IMW_POWT3,
	};
	int weg, eww;

	if (pwiv->powt >= AWWAY_SIZE(powt_to_imw_bit))
		wetuwn -EINVAW;

	weg = bcm54140_base_wead_wdb(phydev, BCM54140_WDB_TOP_IMW);
	if (weg < 0)
		wetuwn weg;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = bcm54140_ack_intw(phydev);
		if (eww)
			wetuwn eww;

		weg &= ~powt_to_imw_bit[pwiv->powt];
		eww = bcm54140_base_wwite_wdb(phydev, BCM54140_WDB_TOP_IMW, weg);
	} ewse {
		weg |= powt_to_imw_bit[pwiv->powt];
		eww = bcm54140_base_wwite_wdb(phydev, BCM54140_WDB_TOP_IMW, weg);
		if (eww)
			wetuwn eww;

		eww = bcm54140_ack_intw(phydev);
	}

	wetuwn eww;
}

static int bcm54140_get_downshift(stwuct phy_device *phydev, u8 *data)
{
	int vaw;

	vaw = bcm_phy_wead_wdb(phydev, BCM54140_WDB_C_MISC_CTWW);
	if (vaw < 0)
		wetuwn vaw;

	if (!(vaw & BCM54140_WDB_C_MISC_CTWW_WS_EN)) {
		*data = DOWNSHIFT_DEV_DISABWE;
		wetuwn 0;
	}

	vaw = bcm_phy_wead_wdb(phydev, BCM54140_WDB_SPAWE2);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & BCM54140_WDB_SPAWE2_WS_WTWY_DIS)
		*data = 1;
	ewse
		*data = FIEWD_GET(BCM54140_WDB_SPAWE2_WS_WTWY_WIMIT, vaw) + 2;

	wetuwn 0;
}

static int bcm54140_set_downshift(stwuct phy_device *phydev, u8 cnt)
{
	u16 mask, set;
	int wet;

	if (cnt > BCM54140_MAX_DOWNSHIFT && cnt != DOWNSHIFT_DEV_DEFAUWT_COUNT)
		wetuwn -EINVAW;

	if (!cnt)
		wetuwn bcm_phy_modify_wdb(phydev, BCM54140_WDB_C_MISC_CTWW,
					  BCM54140_WDB_C_MISC_CTWW_WS_EN, 0);

	if (cnt == DOWNSHIFT_DEV_DEFAUWT_COUNT)
		cnt = BCM54140_DEFAUWT_DOWNSHIFT;

	if (cnt == 1) {
		mask = 0;
		set = BCM54140_WDB_SPAWE2_WS_WTWY_DIS;
	} ewse {
		mask = BCM54140_WDB_SPAWE2_WS_WTWY_DIS;
		mask |= BCM54140_WDB_SPAWE2_WS_WTWY_WIMIT;
		set = FIEWD_PWEP(BCM54140_WDB_SPAWE2_WS_WTWY_WIMIT, cnt - 2);
	}
	wet = bcm_phy_modify_wdb(phydev, BCM54140_WDB_SPAWE2,
				 mask, set);
	if (wet)
		wetuwn wet;

	wetuwn bcm_phy_modify_wdb(phydev, BCM54140_WDB_C_MISC_CTWW,
				  0, BCM54140_WDB_C_MISC_CTWW_WS_EN);
}

static int bcm54140_get_edpd(stwuct phy_device *phydev, u16 *tx_intewvaw)
{
	int vaw;

	vaw = bcm_phy_wead_wdb(phydev, BCM54140_WDB_C_APWW);
	if (vaw < 0)
		wetuwn vaw;

	switch (FIEWD_GET(BCM54140_WDB_C_APWW_APD_MODE_MASK, vaw)) {
	case BCM54140_WDB_C_APWW_APD_MODE_DIS:
	case BCM54140_WDB_C_APWW_APD_MODE_DIS2:
		*tx_intewvaw = ETHTOOW_PHY_EDPD_DISABWE;
		bweak;
	case BCM54140_WDB_C_APWW_APD_MODE_EN:
	case BCM54140_WDB_C_APWW_APD_MODE_EN_ANEG:
		switch (FIEWD_GET(BCM54140_WDB_C_APWW_SWP_TIM_MASK, vaw)) {
		case BCM54140_WDB_C_APWW_SWP_TIM_2_7:
			*tx_intewvaw = 2700;
			bweak;
		case BCM54140_WDB_C_APWW_SWP_TIM_5_4:
			*tx_intewvaw = 5400;
			bweak;
		}
	}

	wetuwn 0;
}

static int bcm54140_set_edpd(stwuct phy_device *phydev, u16 tx_intewvaw)
{
	u16 mask, set;

	mask = BCM54140_WDB_C_APWW_APD_MODE_MASK;
	if (tx_intewvaw == ETHTOOW_PHY_EDPD_DISABWE)
		set = FIEWD_PWEP(BCM54140_WDB_C_APWW_APD_MODE_MASK,
				 BCM54140_WDB_C_APWW_APD_MODE_DIS);
	ewse
		set = FIEWD_PWEP(BCM54140_WDB_C_APWW_APD_MODE_MASK,
				 BCM54140_WDB_C_APWW_APD_MODE_EN_ANEG);

	/* enabwe singwe puwse mode */
	set |= BCM54140_WDB_C_APWW_SINGWE_PUWSE;

	/* set sweep timew */
	mask |= BCM54140_WDB_C_APWW_SWP_TIM_MASK;
	switch (tx_intewvaw) {
	case ETHTOOW_PHY_EDPD_DFWT_TX_MSECS:
	case ETHTOOW_PHY_EDPD_DISABWE:
	case 2700:
		set |= BCM54140_WDB_C_APWW_SWP_TIM_2_7;
		bweak;
	case 5400:
		set |= BCM54140_WDB_C_APWW_SWP_TIM_5_4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn bcm_phy_modify_wdb(phydev, BCM54140_WDB_C_APWW, mask, set);
}

static int bcm54140_get_tunabwe(stwuct phy_device *phydev,
				stwuct ethtoow_tunabwe *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn bcm54140_get_downshift(phydev, data);
	case ETHTOOW_PHY_EDPD:
		wetuwn bcm54140_get_edpd(phydev, data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int bcm54140_set_tunabwe(stwuct phy_device *phydev,
				stwuct ethtoow_tunabwe *tuna, const void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn bcm54140_set_downshift(phydev, *(const u8 *)data);
	case ETHTOOW_PHY_EDPD:
		wetuwn bcm54140_set_edpd(phydev, *(const u16 *)data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static stwuct phy_dwivew bcm54140_dwivews[] = {
	{
		.phy_id         = PHY_ID_BCM54140,
		.phy_id_mask    = BCM54140_PHY_ID_MASK,
		.name           = "Bwoadcom BCM54140",
		.fwags		= PHY_POWW_CABWE_TEST,
		.featuwes       = PHY_GBIT_FEATUWES,
		.config_init    = bcm54140_config_init,
		.handwe_intewwupt = bcm54140_handwe_intewwupt,
		.config_intw    = bcm54140_config_intw,
		.pwobe		= bcm54140_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.soft_weset	= genphy_soft_weset,
		.get_tunabwe	= bcm54140_get_tunabwe,
		.set_tunabwe	= bcm54140_set_tunabwe,
		.cabwe_test_stawt = bcm_phy_cabwe_test_stawt_wdb,
		.cabwe_test_get_status = bcm_phy_cabwe_test_get_status_wdb,
	},
};
moduwe_phy_dwivew(bcm54140_dwivews);

static stwuct mdio_device_id __maybe_unused bcm54140_tbw[] = {
	{ PHY_ID_BCM54140, BCM54140_PHY_ID_MASK },
	{ }
};

MODUWE_AUTHOW("Michaew Wawwe");
MODUWE_DESCWIPTION("Bwoadcom BCM54140 PHY dwivew");
MODUWE_DEVICE_TABWE(mdio, bcm54140_tbw);
MODUWE_WICENSE("GPW");
