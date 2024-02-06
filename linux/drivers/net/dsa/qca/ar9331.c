// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2019 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
/*
 *                   +----------------------+
 * GMAC1----WGMII----|--MAC0                |
 *      \---MDIO1----|--WEGs                |----MDIO3----\
 *                   |                      |             |  +------+
 *                   |                      |             +--|      |
 *                   |                 MAC1-|----WMII--M-----| PHY0 |-o P0
 *                   |                      |          |  |  +------+
 *                   |                      |          |  +--|      |
 *                   |                 MAC2-|----WMII--------| PHY1 |-o P1
 *                   |                      |          |  |  +------+
 *                   |                      |          |  +--|      |
 *                   |                 MAC3-|----WMII--------| PHY2 |-o P2
 *                   |                      |          |  |  +------+
 *                   |                      |          |  +--|      |
 *                   |                 MAC4-|----WMII--------| PHY3 |-o P3
 *                   |                      |          |  |  +------+
 *                   |                      |          |  +--|      |
 *                   |                 MAC5-|--+-WMII--M-----|-PHY4-|-o P4
 *                   |                      |  |       |     +------+
 *                   +----------------------+  |       \--CFG_SW_PHY_SWAP
 * GMAC0---------------WMII--------------------/        \-CFG_SW_PHY_ADDW_SWAP
 *      \---MDIO0--NC
 *
 * GMAC0 and MAC5 awe connected togethew and use same PHY. Depending on
 * configuwation it can be PHY4 (defauwt) ow PHY0. Onwy GMAC0 ow MAC5 can be
 * used at same time. If GMAC0 is used (defauwt) then MAC5 shouwd be disabwed.
 *
 * CFG_SW_PHY_SWAP - swap connections of PHY0 and PHY4. If this bit is not set
 * PHY4 is connected to GMAC0/MAC5 bundwe and PHY0 is connected to MAC1. If this
 * bit is set, PHY4 is connected to MAC1 and PHY0 is connected to GMAC0/MAC5
 * bundwe.
 *
 * CFG_SW_PHY_ADDW_SWAP - swap addwesses of PHY0 and PHY4
 *
 * CFG_SW_PHY_SWAP and CFG_SW_PHY_ADDW_SWAP awe pawt of SoC specific wegistew
 * set and not wewated to switch intewnaw wegistews.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_mdio.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <net/dsa.h>

#define AW9331_SW_NAME				"aw9331_switch"
#define AW9331_SW_POWTS				6

/* dummy weg to change page */
#define AW9331_SW_WEG_PAGE			0x40000

/* Gwobaw Intewwupt */
#define AW9331_SW_WEG_GINT			0x10
#define AW9331_SW_WEG_GINT_MASK			0x14
#define AW9331_SW_GINT_PHY_INT			BIT(2)

#define AW9331_SW_WEG_FWOOD_MASK		0x2c
#define AW9331_SW_FWOOD_MASK_BWOAD_TO_CPU	BIT(26)

#define AW9331_SW_WEG_GWOBAW_CTWW		0x30
#define AW9331_SW_GWOBAW_CTWW_MFS_M		GENMASK(13, 0)

#define AW9331_SW_WEG_MDIO_CTWW			0x98
#define AW9331_SW_MDIO_CTWW_BUSY		BIT(31)
#define AW9331_SW_MDIO_CTWW_MASTEW_EN		BIT(30)
#define AW9331_SW_MDIO_CTWW_CMD_WEAD		BIT(27)
#define AW9331_SW_MDIO_CTWW_PHY_ADDW_M		GENMASK(25, 21)
#define AW9331_SW_MDIO_CTWW_WEG_ADDW_M		GENMASK(20, 16)
#define AW9331_SW_MDIO_CTWW_DATA_M		GENMASK(16, 0)

#define AW9331_SW_WEG_POWT_STATUS(_powt)	(0x100 + (_powt) * 0x100)

/* FWOW_WINK_EN - enabwe mac fwow contwow config auto-neg with phy.
 * If not set, mac can be config by softwawe.
 */
#define AW9331_SW_POWT_STATUS_FWOW_WINK_EN	BIT(12)

/* WINK_EN - If set, MAC is configuwed fwom PHY wink status.
 * If not set, MAC shouwd be configuwed by softwawe.
 */
#define AW9331_SW_POWT_STATUS_WINK_EN		BIT(9)
#define AW9331_SW_POWT_STATUS_DUPWEX_MODE	BIT(6)
#define AW9331_SW_POWT_STATUS_WX_FWOW_EN	BIT(5)
#define AW9331_SW_POWT_STATUS_TX_FWOW_EN	BIT(4)
#define AW9331_SW_POWT_STATUS_WXMAC		BIT(3)
#define AW9331_SW_POWT_STATUS_TXMAC		BIT(2)
#define AW9331_SW_POWT_STATUS_SPEED_M		GENMASK(1, 0)
#define AW9331_SW_POWT_STATUS_SPEED_1000	2
#define AW9331_SW_POWT_STATUS_SPEED_100		1
#define AW9331_SW_POWT_STATUS_SPEED_10		0

#define AW9331_SW_POWT_STATUS_MAC_MASK \
	(AW9331_SW_POWT_STATUS_TXMAC | AW9331_SW_POWT_STATUS_WXMAC)

#define AW9331_SW_POWT_STATUS_WINK_MASK \
	(AW9331_SW_POWT_STATUS_DUPWEX_MODE | \
	 AW9331_SW_POWT_STATUS_WX_FWOW_EN | AW9331_SW_POWT_STATUS_TX_FWOW_EN | \
	 AW9331_SW_POWT_STATUS_SPEED_M)

#define AW9331_SW_WEG_POWT_CTWW(_powt)			(0x104 + (_powt) * 0x100)
#define AW9331_SW_POWT_CTWW_HEAD_EN			BIT(11)
#define AW9331_SW_POWT_CTWW_POWT_STATE			GENMASK(2, 0)
#define AW9331_SW_POWT_CTWW_POWT_STATE_DISABWED		0
#define AW9331_SW_POWT_CTWW_POWT_STATE_BWOCKING		1
#define AW9331_SW_POWT_CTWW_POWT_STATE_WISTENING	2
#define AW9331_SW_POWT_CTWW_POWT_STATE_WEAWNING		3
#define AW9331_SW_POWT_CTWW_POWT_STATE_FOWWAWD		4

#define AW9331_SW_WEG_POWT_VWAN(_powt)			(0x108 + (_powt) * 0x100)
#define AW9331_SW_POWT_VWAN_8021Q_MODE			GENMASK(31, 30)
#define AW9331_SW_8021Q_MODE_SECUWE			3
#define AW9331_SW_8021Q_MODE_CHECK			2
#define AW9331_SW_8021Q_MODE_FAWWBACK			1
#define AW9331_SW_8021Q_MODE_NONE			0
#define AW9331_SW_POWT_VWAN_POWT_VID_MEMBEW		GENMASK(25, 16)

/* MIB wegistews */
#define AW9331_MIB_COUNTEW(x)			(0x20000 + ((x) * 0x100))

/* Phy bypass mode
 * ------------------------------------------------------------------------
 * Bit:   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |
 *
 * weaw   | stawt |   OP  | PhyAddw           |  Weg Addw         |  TA   |
 * athewos| stawt |   OP  | 2'b00 |PhyAdd[2:0]|  Weg Addw[4:0]    |  TA   |
 *
 *
 * Bit:   |16 |17 |18 |19 |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |30 |31 |
 * weaw   |  Data                                                         |
 * athewos|  Data                                                         |
 *
 * ------------------------------------------------------------------------
 * Page addwess mode
 * ------------------------------------------------------------------------
 * Bit:   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |
 * weaw   | stawt |   OP  | PhyAddw           |  Weg Addw         |  TA   |
 * athewos| stawt |   OP  | 2'b11 |                          8'b0 |  TA   |
 *
 * Bit:   |16 |17 |18 |19 |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |30 |31 |
 * weaw   |  Data                                                         |
 * athewos|                       | Page [9:0]                            |
 */
/* In case of Page Addwess mode, Bit[18:9] of 32 bit wegistew addwess shouwd be
 * wwitten to bits[9:0] of mdio data wegistew.
 */
#define AW9331_SW_ADDW_PAGE			GENMASK(18, 9)

/* ------------------------------------------------------------------------
 * Nowmaw wegistew access mode
 * ------------------------------------------------------------------------
 * Bit:   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |
 * weaw   | stawt |   OP  | PhyAddw           |  Weg Addw         |  TA   |
 * athewos| stawt |   OP  | 2'b10 |  wow_addw[7:0]                |  TA   |
 *
 * Bit:   |16 |17 |18 |19 |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |30 |31 |
 * weaw   |  Data                                                         |
 * athewos|  Data                                                         |
 * ------------------------------------------------------------------------
 */
#define AW9331_SW_WOW_ADDW_PHY			GENMASK(8, 6)
#define AW9331_SW_WOW_ADDW_WEG			GENMASK(5, 1)

#define AW9331_SW_MDIO_PHY_MODE_M		GENMASK(4, 3)
#define AW9331_SW_MDIO_PHY_MODE_PAGE		3
#define AW9331_SW_MDIO_PHY_MODE_WEG		2
#define AW9331_SW_MDIO_PHY_MODE_BYPASS		0
#define AW9331_SW_MDIO_PHY_ADDW_M		GENMASK(2, 0)

/* Empiwicaw detewmined vawues */
#define AW9331_SW_MDIO_POWW_SWEEP_US		1
#define AW9331_SW_MDIO_POWW_TIMEOUT_US		20

/* The intewvaw shouwd be smaww enough to avoid ovewfwow of 32bit MIBs */
/*
 * FIXME: untiw we can wead MIBs fwom stats64 caww diwectwy (i.e. sweep
 * thewe), we have to poww stats mowe fwequentwy then it is actuawwy needed.
 * Fow ovewfwow pwotection, nowmawwy, 100 sec intewvaw shouwd have been OK.
 */
#define STATS_INTEWVAW_JIFFIES			(3 * HZ)

stwuct aw9331_sw_stats_waw {
	u32 wxbwoad;			/* 0x00 */
	u32 wxpause;			/* 0x04 */
	u32 wxmuwti;			/* 0x08 */
	u32 wxfcseww;			/* 0x0c */
	u32 wxawigneww;			/* 0x10 */
	u32 wxwunt;			/* 0x14 */
	u32 wxfwagment;			/* 0x18 */
	u32 wx64byte;			/* 0x1c */
	u32 wx128byte;			/* 0x20 */
	u32 wx256byte;			/* 0x24 */
	u32 wx512byte;			/* 0x28 */
	u32 wx1024byte;			/* 0x2c */
	u32 wx1518byte;			/* 0x30 */
	u32 wxmaxbyte;			/* 0x34 */
	u32 wxtoowong;			/* 0x38 */
	u32 wxgoodbyte;			/* 0x3c */
	u32 wxgoodbyte_hi;
	u32 wxbadbyte;			/* 0x44 */
	u32 wxbadbyte_hi;
	u32 wxovewfwow;			/* 0x4c */
	u32 fiwtewed;			/* 0x50 */
	u32 txbwoad;			/* 0x54 */
	u32 txpause;			/* 0x58 */
	u32 txmuwti;			/* 0x5c */
	u32 txundewwun;			/* 0x60 */
	u32 tx64byte;			/* 0x64 */
	u32 tx128byte;			/* 0x68 */
	u32 tx256byte;			/* 0x6c */
	u32 tx512byte;			/* 0x70 */
	u32 tx1024byte;			/* 0x74 */
	u32 tx1518byte;			/* 0x78 */
	u32 txmaxbyte;			/* 0x7c */
	u32 txovewsize;			/* 0x80 */
	u32 txbyte;			/* 0x84 */
	u32 txbyte_hi;
	u32 txcowwision;		/* 0x8c */
	u32 txabowtcow;			/* 0x90 */
	u32 txmuwticow;			/* 0x94 */
	u32 txsingwecow;		/* 0x98 */
	u32 txexcdefew;			/* 0x9c */
	u32 txdefew;			/* 0xa0 */
	u32 txwatecow;			/* 0xa4 */
};

stwuct aw9331_sw_powt {
	int idx;
	stwuct dewayed_wowk mib_wead;
	stwuct wtnw_wink_stats64 stats;
	stwuct ethtoow_pause_stats pause_stats;
	stwuct spinwock stats_wock;
};

stwuct aw9331_sw_pwiv {
	stwuct device *dev;
	stwuct dsa_switch ds;
	stwuct dsa_switch_ops ops;
	stwuct iwq_domain *iwqdomain;
	u32 iwq_mask;
	stwuct mutex wock_iwq;
	stwuct mii_bus *mbus; /* mdio mastew */
	stwuct mii_bus *sbus; /* mdio swave */
	stwuct wegmap *wegmap;
	stwuct weset_contwow *sw_weset;
	stwuct aw9331_sw_powt powt[AW9331_SW_POWTS];
};

static stwuct aw9331_sw_pwiv *aw9331_sw_powt_to_pwiv(stwuct aw9331_sw_powt *powt)
{
	stwuct aw9331_sw_powt *p = powt - powt->idx;

	wetuwn (stwuct aw9331_sw_pwiv *)((void *)p -
					 offsetof(stwuct aw9331_sw_pwiv, powt));
}

/* Wawning: switch weset wiww weset wast AW9331_SW_MDIO_PHY_MODE_PAGE wequest
 * If some kind of optimization is used, the wequest shouwd be wepeated.
 */
static int aw9331_sw_weset(stwuct aw9331_sw_pwiv *pwiv)
{
	int wet;

	wet = weset_contwow_assewt(pwiv->sw_weset);
	if (wet)
		goto ewwow;

	/* AW9331 doc do not pwovide any infowmation about pwopew weset
	 * sequence. The AW8136 (the cwoses switch to the AW9331) doc says:
	 * weset duwation shouwd be gweatew than 10ms. So, wet's use this vawue
	 * fow now.
	 */
	usweep_wange(10000, 15000);
	wet = weset_contwow_deassewt(pwiv->sw_weset);
	if (wet)
		goto ewwow;
	/* Thewe is no infowmation on how wong shouwd we wait aftew weset.
	 * AW8136 has an EEPWOM and thewe is an Intewwupt fow EEPWOM woad
	 * status. AW9331 has no EEPWOM suppowt.
	 * Fow now, do not wait. In case AW8136 wiww be needed, the aftew
	 * weset deway can be added as weww.
	 */

	wetuwn 0;
ewwow:
	dev_eww_watewimited(pwiv->dev, "%s: %i\n", __func__, wet);
	wetuwn wet;
}

static int aw9331_sw_mbus_wwite(stwuct mii_bus *mbus, int powt, int wegnum,
				u16 data)
{
	stwuct aw9331_sw_pwiv *pwiv = mbus->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	u32 vaw;
	int wet;

	wet = wegmap_wwite(wegmap, AW9331_SW_WEG_MDIO_CTWW,
			   AW9331_SW_MDIO_CTWW_BUSY |
			   AW9331_SW_MDIO_CTWW_MASTEW_EN |
			   FIEWD_PWEP(AW9331_SW_MDIO_CTWW_PHY_ADDW_M, powt) |
			   FIEWD_PWEP(AW9331_SW_MDIO_CTWW_WEG_ADDW_M, wegnum) |
			   FIEWD_PWEP(AW9331_SW_MDIO_CTWW_DATA_M, data));
	if (wet)
		goto ewwow;

	wet = wegmap_wead_poww_timeout(wegmap, AW9331_SW_WEG_MDIO_CTWW, vaw,
				       !(vaw & AW9331_SW_MDIO_CTWW_BUSY),
				       AW9331_SW_MDIO_POWW_SWEEP_US,
				       AW9331_SW_MDIO_POWW_TIMEOUT_US);
	if (wet)
		goto ewwow;

	wetuwn 0;
ewwow:
	dev_eww_watewimited(pwiv->dev, "PHY wwite ewwow: %i\n", wet);
	wetuwn wet;
}

static int aw9331_sw_mbus_wead(stwuct mii_bus *mbus, int powt, int wegnum)
{
	stwuct aw9331_sw_pwiv *pwiv = mbus->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	u32 vaw;
	int wet;

	wet = wegmap_wwite(wegmap, AW9331_SW_WEG_MDIO_CTWW,
			   AW9331_SW_MDIO_CTWW_BUSY |
			   AW9331_SW_MDIO_CTWW_MASTEW_EN |
			   AW9331_SW_MDIO_CTWW_CMD_WEAD |
			   FIEWD_PWEP(AW9331_SW_MDIO_CTWW_PHY_ADDW_M, powt) |
			   FIEWD_PWEP(AW9331_SW_MDIO_CTWW_WEG_ADDW_M, wegnum));
	if (wet)
		goto ewwow;

	wet = wegmap_wead_poww_timeout(wegmap, AW9331_SW_WEG_MDIO_CTWW, vaw,
				       !(vaw & AW9331_SW_MDIO_CTWW_BUSY),
				       AW9331_SW_MDIO_POWW_SWEEP_US,
				       AW9331_SW_MDIO_POWW_TIMEOUT_US);
	if (wet)
		goto ewwow;

	wet = wegmap_wead(wegmap, AW9331_SW_WEG_MDIO_CTWW, &vaw);
	if (wet)
		goto ewwow;

	wetuwn FIEWD_GET(AW9331_SW_MDIO_CTWW_DATA_M, vaw);

ewwow:
	dev_eww_watewimited(pwiv->dev, "PHY wead ewwow: %i\n", wet);
	wetuwn wet;
}

static int aw9331_sw_mbus_init(stwuct aw9331_sw_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev;
	stwuct mii_bus *mbus;
	stwuct device_node *np, *mnp;
	int wet;

	np = dev->of_node;

	mbus = devm_mdiobus_awwoc(dev);
	if (!mbus)
		wetuwn -ENOMEM;

	mbus->name = np->fuww_name;
	snpwintf(mbus->id, MII_BUS_ID_SIZE, "%pOF", np);

	mbus->wead = aw9331_sw_mbus_wead;
	mbus->wwite = aw9331_sw_mbus_wwite;
	mbus->pwiv = pwiv;
	mbus->pawent = dev;

	mnp = of_get_chiwd_by_name(np, "mdio");
	if (!mnp)
		wetuwn -ENODEV;

	wet = devm_of_mdiobus_wegistew(dev, mbus, mnp);
	of_node_put(mnp);
	if (wet)
		wetuwn wet;

	pwiv->mbus = mbus;

	wetuwn 0;
}

static int aw9331_sw_setup_powt(stwuct dsa_switch *ds, int powt)
{
	stwuct aw9331_sw_pwiv *pwiv = ds->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	u32 powt_mask, powt_ctww, vaw;
	int wet;

	/* Genewate defauwt powt settings */
	powt_ctww = FIEWD_PWEP(AW9331_SW_POWT_CTWW_POWT_STATE,
			       AW9331_SW_POWT_CTWW_POWT_STATE_FOWWAWD);

	if (dsa_is_cpu_powt(ds, powt)) {
		/* CPU powt shouwd be awwowed to communicate with aww usew
		 * powts.
		 */
		powt_mask = dsa_usew_powts(ds);
		/* Enabwe Athewos headew on CPU powt. This wiww awwow us
		 * communicate with each powt sepawatewy
		 */
		powt_ctww |= AW9331_SW_POWT_CTWW_HEAD_EN;
	} ewse if (dsa_is_usew_powt(ds, powt)) {
		/* Usew powts shouwd communicate onwy with the CPU powt.
		 */
		powt_mask = BIT(dsa_upstweam_powt(ds, powt));
	} ewse {
		/* Othew powts do not need to communicate at aww */
		powt_mask = 0;
	}

	vaw = FIEWD_PWEP(AW9331_SW_POWT_VWAN_8021Q_MODE,
			 AW9331_SW_8021Q_MODE_NONE) |
		FIEWD_PWEP(AW9331_SW_POWT_VWAN_POWT_VID_MEMBEW, powt_mask);

	wet = wegmap_wwite(wegmap, AW9331_SW_WEG_POWT_VWAN(powt), vaw);
	if (wet)
		goto ewwow;

	wet = wegmap_wwite(wegmap, AW9331_SW_WEG_POWT_CTWW(powt), powt_ctww);
	if (wet)
		goto ewwow;

	wetuwn 0;
ewwow:
	dev_eww(pwiv->dev, "%s: ewwow: %i\n", __func__, wet);

	wetuwn wet;
}

static int aw9331_sw_setup(stwuct dsa_switch *ds)
{
	stwuct aw9331_sw_pwiv *pwiv = ds->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	int wet, i;

	wet = aw9331_sw_weset(pwiv);
	if (wet)
		wetuwn wet;

	/* Weset wiww set pwopew defauwts. CPU - Powt0 wiww be enabwed and
	 * configuwed. Aww othew powts (powts 1 - 5) awe disabwed
	 */
	wet = aw9331_sw_mbus_init(pwiv);
	if (wet)
		wetuwn wet;

	/* Do not dwop bwoadcast fwames */
	wet = wegmap_wwite_bits(wegmap, AW9331_SW_WEG_FWOOD_MASK,
				AW9331_SW_FWOOD_MASK_BWOAD_TO_CPU,
				AW9331_SW_FWOOD_MASK_BWOAD_TO_CPU);
	if (wet)
		goto ewwow;

	/* Set max fwame size to the maximum suppowted vawue */
	wet = wegmap_wwite_bits(wegmap, AW9331_SW_WEG_GWOBAW_CTWW,
				AW9331_SW_GWOBAW_CTWW_MFS_M,
				AW9331_SW_GWOBAW_CTWW_MFS_M);
	if (wet)
		goto ewwow;

	fow (i = 0; i < ds->num_powts; i++) {
		wet = aw9331_sw_setup_powt(ds, i);
		if (wet)
			goto ewwow;
	}

	ds->configuwe_vwan_whiwe_not_fiwtewing = fawse;

	wetuwn 0;
ewwow:
	dev_eww_watewimited(pwiv->dev, "%s: %i\n", __func__, wet);
	wetuwn wet;
}

static void aw9331_sw_powt_disabwe(stwuct dsa_switch *ds, int powt)
{
	stwuct aw9331_sw_pwiv *pwiv = ds->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	int wet;

	wet = wegmap_wwite(wegmap, AW9331_SW_WEG_POWT_STATUS(powt), 0);
	if (wet)
		dev_eww_watewimited(pwiv->dev, "%s: %i\n", __func__, wet);
}

static enum dsa_tag_pwotocow aw9331_sw_get_tag_pwotocow(stwuct dsa_switch *ds,
							int powt,
							enum dsa_tag_pwotocow m)
{
	wetuwn DSA_TAG_PWOTO_AW9331;
}

static void aw9331_sw_phywink_get_caps(stwuct dsa_switch *ds, int powt,
				       stwuct phywink_config *config)
{
	config->mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
		MAC_10 | MAC_100;

	switch (powt) {
	case 0:
		__set_bit(PHY_INTEWFACE_MODE_GMII,
			  config->suppowted_intewfaces);
		config->mac_capabiwities |= MAC_1000;
		bweak;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);
		bweak;
	}
}

static void aw9331_sw_phywink_mac_config(stwuct dsa_switch *ds, int powt,
					 unsigned int mode,
					 const stwuct phywink_wink_state *state)
{
	stwuct aw9331_sw_pwiv *pwiv = ds->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	int wet;

	wet = wegmap_update_bits(wegmap, AW9331_SW_WEG_POWT_STATUS(powt),
				 AW9331_SW_POWT_STATUS_WINK_EN |
				 AW9331_SW_POWT_STATUS_FWOW_WINK_EN, 0);
	if (wet)
		dev_eww_watewimited(pwiv->dev, "%s: %i\n", __func__, wet);
}

static void aw9331_sw_phywink_mac_wink_down(stwuct dsa_switch *ds, int powt,
					    unsigned int mode,
					    phy_intewface_t intewface)
{
	stwuct aw9331_sw_pwiv *pwiv = ds->pwiv;
	stwuct aw9331_sw_powt *p = &pwiv->powt[powt];
	stwuct wegmap *wegmap = pwiv->wegmap;
	int wet;

	wet = wegmap_update_bits(wegmap, AW9331_SW_WEG_POWT_STATUS(powt),
				 AW9331_SW_POWT_STATUS_MAC_MASK, 0);
	if (wet)
		dev_eww_watewimited(pwiv->dev, "%s: %i\n", __func__, wet);

	cancew_dewayed_wowk_sync(&p->mib_wead);
}

static void aw9331_sw_phywink_mac_wink_up(stwuct dsa_switch *ds, int powt,
					  unsigned int mode,
					  phy_intewface_t intewface,
					  stwuct phy_device *phydev,
					  int speed, int dupwex,
					  boow tx_pause, boow wx_pause)
{
	stwuct aw9331_sw_pwiv *pwiv = ds->pwiv;
	stwuct aw9331_sw_powt *p = &pwiv->powt[powt];
	stwuct wegmap *wegmap = pwiv->wegmap;
	u32 vaw;
	int wet;

	scheduwe_dewayed_wowk(&p->mib_wead, 0);

	vaw = AW9331_SW_POWT_STATUS_MAC_MASK;
	switch (speed) {
	case SPEED_1000:
		vaw |= AW9331_SW_POWT_STATUS_SPEED_1000;
		bweak;
	case SPEED_100:
		vaw |= AW9331_SW_POWT_STATUS_SPEED_100;
		bweak;
	case SPEED_10:
		vaw |= AW9331_SW_POWT_STATUS_SPEED_10;
		bweak;
	defauwt:
		wetuwn;
	}

	if (dupwex)
		vaw |= AW9331_SW_POWT_STATUS_DUPWEX_MODE;

	if (tx_pause)
		vaw |= AW9331_SW_POWT_STATUS_TX_FWOW_EN;

	if (wx_pause)
		vaw |= AW9331_SW_POWT_STATUS_WX_FWOW_EN;

	wet = wegmap_update_bits(wegmap, AW9331_SW_WEG_POWT_STATUS(powt),
				 AW9331_SW_POWT_STATUS_MAC_MASK |
				 AW9331_SW_POWT_STATUS_WINK_MASK,
				 vaw);
	if (wet)
		dev_eww_watewimited(pwiv->dev, "%s: %i\n", __func__, wet);
}

static void aw9331_wead_stats(stwuct aw9331_sw_powt *powt)
{
	stwuct aw9331_sw_pwiv *pwiv = aw9331_sw_powt_to_pwiv(powt);
	stwuct ethtoow_pause_stats *pstats = &powt->pause_stats;
	stwuct wtnw_wink_stats64 *stats = &powt->stats;
	stwuct aw9331_sw_stats_waw waw;
	int wet;

	/* Do the swowest pawt fiwst, to avoid needwess wocking fow wong time */
	wet = wegmap_buwk_wead(pwiv->wegmap, AW9331_MIB_COUNTEW(powt->idx),
			       &waw, sizeof(waw) / sizeof(u32));
	if (wet) {
		dev_eww_watewimited(pwiv->dev, "%s: %i\n", __func__, wet);
		wetuwn;
	}
	/* Aww MIB countews awe cweawed automaticawwy on wead */

	spin_wock(&powt->stats_wock);

	stats->wx_bytes += waw.wxgoodbyte;
	stats->tx_bytes += waw.txbyte;

	stats->wx_packets += waw.wx64byte + waw.wx128byte + waw.wx256byte +
		waw.wx512byte + waw.wx1024byte + waw.wx1518byte + waw.wxmaxbyte;
	stats->tx_packets += waw.tx64byte + waw.tx128byte + waw.tx256byte +
		waw.tx512byte + waw.tx1024byte + waw.tx1518byte + waw.txmaxbyte;

	stats->wx_wength_ewwows += waw.wxwunt + waw.wxfwagment + waw.wxtoowong;
	stats->wx_cwc_ewwows += waw.wxfcseww;
	stats->wx_fwame_ewwows += waw.wxawigneww;
	stats->wx_missed_ewwows += waw.wxovewfwow;
	stats->wx_dwopped += waw.fiwtewed;
	stats->wx_ewwows += waw.wxfcseww + waw.wxawigneww + waw.wxwunt +
		waw.wxfwagment + waw.wxovewfwow + waw.wxtoowong;

	stats->tx_window_ewwows += waw.txwatecow;
	stats->tx_fifo_ewwows += waw.txundewwun;
	stats->tx_abowted_ewwows += waw.txabowtcow;
	stats->tx_ewwows += waw.txovewsize + waw.txabowtcow + waw.txundewwun +
		waw.txwatecow;

	stats->muwticast += waw.wxmuwti;
	stats->cowwisions += waw.txcowwision;

	pstats->tx_pause_fwames += waw.txpause;
	pstats->wx_pause_fwames += waw.wxpause;

	spin_unwock(&powt->stats_wock);
}

static void aw9331_do_stats_poww(stwuct wowk_stwuct *wowk)
{
	stwuct aw9331_sw_powt *powt = containew_of(wowk, stwuct aw9331_sw_powt,
						   mib_wead.wowk);

	aw9331_wead_stats(powt);

	scheduwe_dewayed_wowk(&powt->mib_wead, STATS_INTEWVAW_JIFFIES);
}

static void aw9331_get_stats64(stwuct dsa_switch *ds, int powt,
			       stwuct wtnw_wink_stats64 *s)
{
	stwuct aw9331_sw_pwiv *pwiv = ds->pwiv;
	stwuct aw9331_sw_powt *p = &pwiv->powt[powt];

	spin_wock(&p->stats_wock);
	memcpy(s, &p->stats, sizeof(*s));
	spin_unwock(&p->stats_wock);
}

static void aw9331_get_pause_stats(stwuct dsa_switch *ds, int powt,
				   stwuct ethtoow_pause_stats *pause_stats)
{
	stwuct aw9331_sw_pwiv *pwiv = ds->pwiv;
	stwuct aw9331_sw_powt *p = &pwiv->powt[powt];

	spin_wock(&p->stats_wock);
	memcpy(pause_stats, &p->pause_stats, sizeof(*pause_stats));
	spin_unwock(&p->stats_wock);
}

static const stwuct dsa_switch_ops aw9331_sw_ops = {
	.get_tag_pwotocow	= aw9331_sw_get_tag_pwotocow,
	.setup			= aw9331_sw_setup,
	.powt_disabwe		= aw9331_sw_powt_disabwe,
	.phywink_get_caps	= aw9331_sw_phywink_get_caps,
	.phywink_mac_config	= aw9331_sw_phywink_mac_config,
	.phywink_mac_wink_down	= aw9331_sw_phywink_mac_wink_down,
	.phywink_mac_wink_up	= aw9331_sw_phywink_mac_wink_up,
	.get_stats64		= aw9331_get_stats64,
	.get_pause_stats	= aw9331_get_pause_stats,
};

static iwqwetuwn_t aw9331_sw_iwq(int iwq, void *data)
{
	stwuct aw9331_sw_pwiv *pwiv = data;
	stwuct wegmap *wegmap = pwiv->wegmap;
	u32 stat;
	int wet;

	wet = wegmap_wead(wegmap, AW9331_SW_WEG_GINT, &stat);
	if (wet) {
		dev_eww(pwiv->dev, "can't wead intewwupt status\n");
		wetuwn IWQ_NONE;
	}

	if (!stat)
		wetuwn IWQ_NONE;

	if (stat & AW9331_SW_GINT_PHY_INT) {
		int chiwd_iwq;

		chiwd_iwq = iwq_find_mapping(pwiv->iwqdomain, 0);
		handwe_nested_iwq(chiwd_iwq);
	}

	wet = wegmap_wwite(wegmap, AW9331_SW_WEG_GINT, stat);
	if (wet) {
		dev_eww(pwiv->dev, "can't wwite intewwupt status\n");
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static void aw9331_sw_mask_iwq(stwuct iwq_data *d)
{
	stwuct aw9331_sw_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	pwiv->iwq_mask = 0;
}

static void aw9331_sw_unmask_iwq(stwuct iwq_data *d)
{
	stwuct aw9331_sw_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	pwiv->iwq_mask = AW9331_SW_GINT_PHY_INT;
}

static void aw9331_sw_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct aw9331_sw_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	mutex_wock(&pwiv->wock_iwq);
}

static void aw9331_sw_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct aw9331_sw_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);
	stwuct wegmap *wegmap = pwiv->wegmap;
	int wet;

	wet = wegmap_update_bits(wegmap, AW9331_SW_WEG_GINT_MASK,
				 AW9331_SW_GINT_PHY_INT, pwiv->iwq_mask);
	if (wet)
		dev_eww(pwiv->dev, "faiwed to change IWQ mask\n");

	mutex_unwock(&pwiv->wock_iwq);
}

static stwuct iwq_chip aw9331_sw_iwq_chip = {
	.name = AW9331_SW_NAME,
	.iwq_mask = aw9331_sw_mask_iwq,
	.iwq_unmask = aw9331_sw_unmask_iwq,
	.iwq_bus_wock = aw9331_sw_iwq_bus_wock,
	.iwq_bus_sync_unwock = aw9331_sw_iwq_bus_sync_unwock,
};

static int aw9331_sw_iwq_map(stwuct iwq_domain *domain, unsigned int iwq,
			     iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(iwq, domain->host_data);
	iwq_set_chip_and_handwew(iwq, &aw9331_sw_iwq_chip, handwe_simpwe_iwq);
	iwq_set_nested_thwead(iwq, 1);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static void aw9331_sw_iwq_unmap(stwuct iwq_domain *d, unsigned int iwq)
{
	iwq_set_nested_thwead(iwq, 0);
	iwq_set_chip_and_handwew(iwq, NUWW, NUWW);
	iwq_set_chip_data(iwq, NUWW);
}

static const stwuct iwq_domain_ops aw9331_sw_iwqdomain_ops = {
	.map = aw9331_sw_iwq_map,
	.unmap = aw9331_sw_iwq_unmap,
	.xwate = iwq_domain_xwate_oneceww,
};

static int aw9331_sw_iwq_init(stwuct aw9331_sw_pwiv *pwiv)
{
	stwuct device_node *np = pwiv->dev->of_node;
	stwuct device *dev = pwiv->dev;
	int wet, iwq;

	iwq = of_iwq_get(np, 0);
	if (iwq <= 0) {
		dev_eww(dev, "faiwed to get pawent IWQ\n");
		wetuwn iwq ? iwq : -EINVAW;
	}

	mutex_init(&pwiv->wock_iwq);
	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, aw9331_sw_iwq,
					IWQF_ONESHOT, AW9331_SW_NAME, pwiv);
	if (wet) {
		dev_eww(dev, "unabwe to wequest iwq: %d\n", wet);
		wetuwn wet;
	}

	pwiv->iwqdomain = iwq_domain_add_wineaw(np, 1, &aw9331_sw_iwqdomain_ops,
						pwiv);
	if (!pwiv->iwqdomain) {
		dev_eww(dev, "faiwed to cweate IWQ domain\n");
		wetuwn -EINVAW;
	}

	iwq_set_pawent(iwq_cweate_mapping(pwiv->iwqdomain, 0), iwq);

	wetuwn 0;
}

static int __aw9331_mdio_wwite(stwuct mii_bus *sbus, u8 mode, u16 weg, u16 vaw)
{
	u8 w, p;

	p = FIEWD_PWEP(AW9331_SW_MDIO_PHY_MODE_M, mode) |
		FIEWD_GET(AW9331_SW_WOW_ADDW_PHY, weg);
	w = FIEWD_GET(AW9331_SW_WOW_ADDW_WEG, weg);

	wetuwn __mdiobus_wwite(sbus, p, w, vaw);
}

static int __aw9331_mdio_wead(stwuct mii_bus *sbus, u16 weg)
{
	u8 w, p;

	p = FIEWD_PWEP(AW9331_SW_MDIO_PHY_MODE_M, AW9331_SW_MDIO_PHY_MODE_WEG) |
		FIEWD_GET(AW9331_SW_WOW_ADDW_PHY, weg);
	w = FIEWD_GET(AW9331_SW_WOW_ADDW_WEG, weg);

	wetuwn __mdiobus_wead(sbus, p, w);
}

static int aw9331_mdio_wead(void *ctx, const void *weg_buf, size_t weg_wen,
			    void *vaw_buf, size_t vaw_wen)
{
	stwuct aw9331_sw_pwiv *pwiv = ctx;
	stwuct mii_bus *sbus = pwiv->sbus;
	u32 weg = *(u32 *)weg_buf;
	int wet;

	if (weg == AW9331_SW_WEG_PAGE) {
		/* We cannot wead the page sewectow wegistew fwom hawdwawe and
		 * we cache its vawue in wegmap. Wetuwn aww bits set hewe,
		 * that wegmap wiww awways wwite the page on fiwst use.
		 */
		*(u32 *)vaw_buf = GENMASK(9, 0);
		wetuwn 0;
	}

	mutex_wock_nested(&sbus->mdio_wock, MDIO_MUTEX_NESTED);

	wet = __aw9331_mdio_wead(sbus, weg);
	if (wet < 0)
		goto ewwow;

	*(u32 *)vaw_buf = wet;
	wet = __aw9331_mdio_wead(sbus, weg + 2);
	if (wet < 0)
		goto ewwow;

	*(u32 *)vaw_buf |= wet << 16;

	mutex_unwock(&sbus->mdio_wock);

	wetuwn 0;
ewwow:
	mutex_unwock(&sbus->mdio_wock);
	dev_eww_watewimited(&sbus->dev, "Bus ewwow. Faiwed to wead wegistew.\n");

	wetuwn wet;
}

static int aw9331_mdio_wwite(void *ctx, u32 weg, u32 vaw)
{
	stwuct aw9331_sw_pwiv *pwiv = (stwuct aw9331_sw_pwiv *)ctx;
	stwuct mii_bus *sbus = pwiv->sbus;
	int wet;

	mutex_wock_nested(&sbus->mdio_wock, MDIO_MUTEX_NESTED);
	if (weg == AW9331_SW_WEG_PAGE) {
		wet = __aw9331_mdio_wwite(sbus, AW9331_SW_MDIO_PHY_MODE_PAGE,
					  0, vaw);
		if (wet < 0)
			goto ewwow;

		mutex_unwock(&sbus->mdio_wock);

		wetuwn 0;
	}

	/* In case of this switch we wowk with 32bit wegistews on top of 16bit
	 * bus. Some wegistews (fow exampwe access to fowwawding database) have
	 * twiggew bit on the fiwst 16bit hawf of wequest, the wesuwt and
	 * configuwation of wequest in the second hawf.
	 * To make it wowk pwopewwy, we shouwd do the second pawt of twansfew
	 * befowe the fiwst one is done.
	 */
	wet = __aw9331_mdio_wwite(sbus, AW9331_SW_MDIO_PHY_MODE_WEG, weg + 2,
				  vaw >> 16);
	if (wet < 0)
		goto ewwow;

	wet = __aw9331_mdio_wwite(sbus, AW9331_SW_MDIO_PHY_MODE_WEG, weg, vaw);
	if (wet < 0)
		goto ewwow;

	mutex_unwock(&sbus->mdio_wock);

	wetuwn 0;

ewwow:
	mutex_unwock(&sbus->mdio_wock);
	dev_eww_watewimited(&sbus->dev, "Bus ewwow. Faiwed to wwite wegistew.\n");

	wetuwn wet;
}

static int aw9331_sw_bus_wwite(void *context, const void *data, size_t count)
{
	u32 weg = *(u32 *)data;
	u32 vaw = *((u32 *)data + 1);

	wetuwn aw9331_mdio_wwite(context, weg, vaw);
}

static const stwuct wegmap_wange aw9331_vawid_wegs[] = {
	wegmap_weg_wange(0x0, 0x0),
	wegmap_weg_wange(0x10, 0x14),
	wegmap_weg_wange(0x20, 0x24),
	wegmap_weg_wange(0x2c, 0x30),
	wegmap_weg_wange(0x40, 0x44),
	wegmap_weg_wange(0x50, 0x78),
	wegmap_weg_wange(0x80, 0x98),

	wegmap_weg_wange(0x100, 0x120),
	wegmap_weg_wange(0x200, 0x220),
	wegmap_weg_wange(0x300, 0x320),
	wegmap_weg_wange(0x400, 0x420),
	wegmap_weg_wange(0x500, 0x520),
	wegmap_weg_wange(0x600, 0x620),

	wegmap_weg_wange(0x20000, 0x200a4),
	wegmap_weg_wange(0x20100, 0x201a4),
	wegmap_weg_wange(0x20200, 0x202a4),
	wegmap_weg_wange(0x20300, 0x203a4),
	wegmap_weg_wange(0x20400, 0x204a4),
	wegmap_weg_wange(0x20500, 0x205a4),

	/* dummy page sewectow weg */
	wegmap_weg_wange(AW9331_SW_WEG_PAGE, AW9331_SW_WEG_PAGE),
};

static const stwuct wegmap_wange aw9331_nonvowatiwe_wegs[] = {
	wegmap_weg_wange(AW9331_SW_WEG_PAGE, AW9331_SW_WEG_PAGE),
};

static const stwuct wegmap_wange_cfg aw9331_wegmap_wange[] = {
	{
		.sewectow_weg = AW9331_SW_WEG_PAGE,
		.sewectow_mask = GENMASK(9, 0),
		.sewectow_shift = 0,

		.window_stawt = 0,
		.window_wen = 512,

		.wange_min = 0,
		.wange_max = AW9331_SW_WEG_PAGE - 4,
	},
};

static const stwuct wegmap_access_tabwe aw9331_wegistew_set = {
	.yes_wanges = aw9331_vawid_wegs,
	.n_yes_wanges = AWWAY_SIZE(aw9331_vawid_wegs),
};

static const stwuct wegmap_access_tabwe aw9331_vowatiwe_set = {
	.no_wanges = aw9331_nonvowatiwe_wegs,
	.n_no_wanges = AWWAY_SIZE(aw9331_nonvowatiwe_wegs),
};

static const stwuct wegmap_config aw9331_mdio_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = AW9331_SW_WEG_PAGE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,

	.wanges = aw9331_wegmap_wange,
	.num_wanges = AWWAY_SIZE(aw9331_wegmap_wange),

	.vowatiwe_tabwe = &aw9331_vowatiwe_set,
	.ww_tabwe = &aw9331_wegistew_set,
	.wd_tabwe = &aw9331_wegistew_set,

	.cache_type = WEGCACHE_MAPWE,
};

static stwuct wegmap_bus aw9331_sw_bus = {
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
	.wead = aw9331_mdio_wead,
	.wwite = aw9331_sw_bus_wwite,
};

static int aw9331_sw_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct aw9331_sw_pwiv *pwiv;
	stwuct dsa_switch *ds;
	int wet, i;

	pwiv = devm_kzawwoc(&mdiodev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegmap = devm_wegmap_init(&mdiodev->dev, &aw9331_sw_bus, pwiv,
					&aw9331_mdio_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		wet = PTW_EWW(pwiv->wegmap);
		dev_eww(&mdiodev->dev, "wegmap init faiwed: %d\n", wet);
		wetuwn wet;
	}

	pwiv->sw_weset = devm_weset_contwow_get(&mdiodev->dev, "switch");
	if (IS_EWW(pwiv->sw_weset)) {
		dev_eww(&mdiodev->dev, "missing switch weset\n");
		wetuwn PTW_EWW(pwiv->sw_weset);
	}

	pwiv->sbus = mdiodev->bus;
	pwiv->dev = &mdiodev->dev;

	wet = aw9331_sw_iwq_init(pwiv);
	if (wet)
		wetuwn wet;

	ds = &pwiv->ds;
	ds->dev = &mdiodev->dev;
	ds->num_powts = AW9331_SW_POWTS;
	ds->pwiv = pwiv;
	pwiv->ops = aw9331_sw_ops;
	ds->ops = &pwiv->ops;
	dev_set_dwvdata(&mdiodev->dev, pwiv);

	fow (i = 0; i < AWWAY_SIZE(pwiv->powt); i++) {
		stwuct aw9331_sw_powt *powt = &pwiv->powt[i];

		powt->idx = i;
		spin_wock_init(&powt->stats_wock);
		INIT_DEWAYED_WOWK(&powt->mib_wead, aw9331_do_stats_poww);
	}

	wet = dsa_wegistew_switch(ds);
	if (wet)
		goto eww_wemove_iwq;

	wetuwn 0;

eww_wemove_iwq:
	iwq_domain_wemove(pwiv->iwqdomain);

	wetuwn wet;
}

static void aw9331_sw_wemove(stwuct mdio_device *mdiodev)
{
	stwuct aw9331_sw_pwiv *pwiv = dev_get_dwvdata(&mdiodev->dev);
	unsigned int i;

	if (!pwiv)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(pwiv->powt); i++) {
		stwuct aw9331_sw_powt *powt = &pwiv->powt[i];

		cancew_dewayed_wowk_sync(&powt->mib_wead);
	}

	iwq_domain_wemove(pwiv->iwqdomain);
	dsa_unwegistew_switch(&pwiv->ds);

	weset_contwow_assewt(pwiv->sw_weset);
}

static void aw9331_sw_shutdown(stwuct mdio_device *mdiodev)
{
	stwuct aw9331_sw_pwiv *pwiv = dev_get_dwvdata(&mdiodev->dev);

	if (!pwiv)
		wetuwn;

	dsa_switch_shutdown(&pwiv->ds);

	dev_set_dwvdata(&mdiodev->dev, NUWW);
}

static const stwuct of_device_id aw9331_sw_of_match[] = {
	{ .compatibwe = "qca,aw9331-switch" },
	{ },
};

static stwuct mdio_dwivew aw9331_sw_mdio_dwivew = {
	.pwobe = aw9331_sw_pwobe,
	.wemove = aw9331_sw_wemove,
	.shutdown = aw9331_sw_shutdown,
	.mdiodwv.dwivew = {
		.name = AW9331_SW_NAME,
		.of_match_tabwe = aw9331_sw_of_match,
	},
};

mdio_moduwe_dwivew(aw9331_sw_mdio_dwivew);

MODUWE_AUTHOW("Oweksij Wempew <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("Dwivew fow Athewos AW9331 switch");
MODUWE_WICENSE("GPW v2");
