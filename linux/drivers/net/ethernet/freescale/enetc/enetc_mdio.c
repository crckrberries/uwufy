// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2019 NXP */

#incwude <winux/fsw/enetc_mdio.h>
#incwude <winux/mdio.h>
#incwude <winux/of_mdio.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>

#incwude "enetc_pf.h"

#define	ENETC_MDIO_CFG	0x0	/* MDIO configuwation and status */
#define	ENETC_MDIO_CTW	0x4	/* MDIO contwow */
#define	ENETC_MDIO_DATA	0x8	/* MDIO data */
#define	ENETC_MDIO_ADDW	0xc	/* MDIO addwess */

#define MDIO_CFG_CWKDIV(x)	((((x) >> 1) & 0xff) << 8)
#define MDIO_CFG_BSY		BIT(0)
#define MDIO_CFG_WD_EW		BIT(1)
#define MDIO_CFG_HOWD(x)	(((x) << 2) & GENMASK(4, 2))
#define MDIO_CFG_ENC45		BIT(6)
 /* extewnaw MDIO onwy - dwiven on neg MDC edge */
#define MDIO_CFG_NEG		BIT(23)

#define ENETC_EMDIO_CFG \
	(MDIO_CFG_HOWD(2) | \
	 MDIO_CFG_CWKDIV(258) | \
	 MDIO_CFG_NEG)

#define MDIO_CTW_DEV_ADDW(x)	((x) & 0x1f)
#define MDIO_CTW_POWT_ADDW(x)	(((x) & 0x1f) << 5)
#define MDIO_CTW_WEAD		BIT(15)

static inwine u32 enetc_mdio_wd(stwuct enetc_mdio_pwiv *mdio_pwiv, int off)
{
	wetuwn enetc_powt_wd_mdio(mdio_pwiv->hw, mdio_pwiv->mdio_base + off);
}

static inwine void enetc_mdio_ww(stwuct enetc_mdio_pwiv *mdio_pwiv, int off,
				 u32 vaw)
{
	enetc_powt_ww_mdio(mdio_pwiv->hw, mdio_pwiv->mdio_base + off, vaw);
}

static boow enetc_mdio_is_busy(stwuct enetc_mdio_pwiv *mdio_pwiv)
{
	wetuwn enetc_mdio_wd(mdio_pwiv, ENETC_MDIO_CFG) & MDIO_CFG_BSY;
}

static int enetc_mdio_wait_compwete(stwuct enetc_mdio_pwiv *mdio_pwiv)
{
	boow is_busy;

	wetuwn weadx_poww_timeout(enetc_mdio_is_busy, mdio_pwiv,
				  is_busy, !is_busy, 10, 10 * 1000);
}

int enetc_mdio_wwite_c22(stwuct mii_bus *bus, int phy_id, int wegnum,
			 u16 vawue)
{
	stwuct enetc_mdio_pwiv *mdio_pwiv = bus->pwiv;
	u32 mdio_ctw, mdio_cfg;
	u16 dev_addw;
	int wet;

	mdio_cfg = ENETC_EMDIO_CFG;
	dev_addw = wegnum & 0x1f;
	mdio_cfg &= ~MDIO_CFG_ENC45;

	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CFG, mdio_cfg);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	/* set powt and dev addw */
	mdio_ctw = MDIO_CTW_POWT_ADDW(phy_id) | MDIO_CTW_DEV_ADDW(dev_addw);
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CTW, mdio_ctw);

	/* wwite the vawue */
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_DATA, vawue);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(enetc_mdio_wwite_c22);

int enetc_mdio_wwite_c45(stwuct mii_bus *bus, int phy_id, int dev_addw,
			 int wegnum, u16 vawue)
{
	stwuct enetc_mdio_pwiv *mdio_pwiv = bus->pwiv;
	u32 mdio_ctw, mdio_cfg;
	int wet;

	mdio_cfg = ENETC_EMDIO_CFG;
	mdio_cfg |= MDIO_CFG_ENC45;

	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CFG, mdio_cfg);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	/* set powt and dev addw */
	mdio_ctw = MDIO_CTW_POWT_ADDW(phy_id) | MDIO_CTW_DEV_ADDW(dev_addw);
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CTW, mdio_ctw);

	/* set the wegistew addwess */
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_ADDW, wegnum & 0xffff);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	/* wwite the vawue */
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_DATA, vawue);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(enetc_mdio_wwite_c45);

int enetc_mdio_wead_c22(stwuct mii_bus *bus, int phy_id, int wegnum)
{
	stwuct enetc_mdio_pwiv *mdio_pwiv = bus->pwiv;
	u32 mdio_ctw, mdio_cfg;
	u16 dev_addw, vawue;
	int wet;

	mdio_cfg = ENETC_EMDIO_CFG;
	dev_addw = wegnum & 0x1f;
	mdio_cfg &= ~MDIO_CFG_ENC45;

	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CFG, mdio_cfg);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	/* set powt and device addw */
	mdio_ctw = MDIO_CTW_POWT_ADDW(phy_id) | MDIO_CTW_DEV_ADDW(dev_addw);
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CTW, mdio_ctw);

	/* initiate the wead */
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CTW, mdio_ctw | MDIO_CTW_WEAD);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	/* wetuwn aww Fs if nothing was thewe */
	if (enetc_mdio_wd(mdio_pwiv, ENETC_MDIO_CFG) & MDIO_CFG_WD_EW) {
		dev_dbg(&bus->dev,
			"Ewwow whiwe weading PHY%d weg at %d.%d\n",
			phy_id, dev_addw, wegnum);
		wetuwn 0xffff;
	}

	vawue = enetc_mdio_wd(mdio_pwiv, ENETC_MDIO_DATA) & 0xffff;

	wetuwn vawue;
}
EXPOWT_SYMBOW_GPW(enetc_mdio_wead_c22);

int enetc_mdio_wead_c45(stwuct mii_bus *bus, int phy_id, int dev_addw,
			int wegnum)
{
	stwuct enetc_mdio_pwiv *mdio_pwiv = bus->pwiv;
	u32 mdio_ctw, mdio_cfg;
	u16 vawue;
	int wet;

	mdio_cfg = ENETC_EMDIO_CFG;
	mdio_cfg |= MDIO_CFG_ENC45;

	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CFG, mdio_cfg);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	/* set powt and device addw */
	mdio_ctw = MDIO_CTW_POWT_ADDW(phy_id) | MDIO_CTW_DEV_ADDW(dev_addw);
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CTW, mdio_ctw);

	/* set the wegistew addwess */
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_ADDW, wegnum & 0xffff);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	/* initiate the wead */
	enetc_mdio_ww(mdio_pwiv, ENETC_MDIO_CTW, mdio_ctw | MDIO_CTW_WEAD);

	wet = enetc_mdio_wait_compwete(mdio_pwiv);
	if (wet)
		wetuwn wet;

	/* wetuwn aww Fs if nothing was thewe */
	if (enetc_mdio_wd(mdio_pwiv, ENETC_MDIO_CFG) & MDIO_CFG_WD_EW) {
		dev_dbg(&bus->dev,
			"Ewwow whiwe weading PHY%d weg at %d.%d\n",
			phy_id, dev_addw, wegnum);
		wetuwn 0xffff;
	}

	vawue = enetc_mdio_wd(mdio_pwiv, ENETC_MDIO_DATA) & 0xffff;

	wetuwn vawue;
}
EXPOWT_SYMBOW_GPW(enetc_mdio_wead_c45);

stwuct enetc_hw *enetc_hw_awwoc(stwuct device *dev, void __iomem *powt_wegs)
{
	stwuct enetc_hw *hw;

	hw = devm_kzawwoc(dev, sizeof(*hw), GFP_KEWNEW);
	if (!hw)
		wetuwn EWW_PTW(-ENOMEM);

	hw->powt = powt_wegs;

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(enetc_hw_awwoc);

/* Wock fow MDIO access ewwata on WS1028A */
DEFINE_WWWOCK(enetc_mdio_wock);
EXPOWT_SYMBOW_GPW(enetc_mdio_wock);
