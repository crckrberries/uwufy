/*
 * Dwivew fow (BCM4706)? GBit MAC cowe on BCMA bus.
 *
 * Copywight (C) 2012 Wafał Miłecki <zajec5@gmaiw.com>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#define pw_fmt(fmt)		KBUIWD_MODNAME ": " fmt

#incwude <winux/bcma/bcma.h>
#incwude <winux/bwcmphy.h>
#incwude <winux/of_mdio.h>
#incwude "bgmac.h"

static boow bcma_mdio_wait_vawue(stwuct bcma_device *cowe, u16 weg, u32 mask,
				 u32 vawue, int timeout)
{
	u32 vaw;
	int i;

	fow (i = 0; i < timeout / 10; i++) {
		vaw = bcma_wead32(cowe, weg);
		if ((vaw & mask) == vawue)
			wetuwn twue;
		udeway(10);
	}
	dev_eww(&cowe->dev, "Timeout waiting fow weg 0x%X\n", weg);
	wetuwn fawse;
}

/**************************************************
 * PHY ops
 **************************************************/

static u16 bcma_mdio_phy_wead(stwuct bgmac *bgmac, u8 phyaddw, u8 weg)
{
	stwuct bcma_device *cowe;
	u16 phy_access_addw;
	u16 phy_ctw_addw;
	u32 tmp;

	BUIWD_BUG_ON(BGMAC_PA_DATA_MASK != BCMA_GMAC_CMN_PA_DATA_MASK);
	BUIWD_BUG_ON(BGMAC_PA_ADDW_MASK != BCMA_GMAC_CMN_PA_ADDW_MASK);
	BUIWD_BUG_ON(BGMAC_PA_ADDW_SHIFT != BCMA_GMAC_CMN_PA_ADDW_SHIFT);
	BUIWD_BUG_ON(BGMAC_PA_WEG_MASK != BCMA_GMAC_CMN_PA_WEG_MASK);
	BUIWD_BUG_ON(BGMAC_PA_WEG_SHIFT != BCMA_GMAC_CMN_PA_WEG_SHIFT);
	BUIWD_BUG_ON(BGMAC_PA_WWITE != BCMA_GMAC_CMN_PA_WWITE);
	BUIWD_BUG_ON(BGMAC_PA_STAWT != BCMA_GMAC_CMN_PA_STAWT);
	BUIWD_BUG_ON(BGMAC_PC_EPA_MASK != BCMA_GMAC_CMN_PC_EPA_MASK);
	BUIWD_BUG_ON(BGMAC_PC_MCT_MASK != BCMA_GMAC_CMN_PC_MCT_MASK);
	BUIWD_BUG_ON(BGMAC_PC_MCT_SHIFT != BCMA_GMAC_CMN_PC_MCT_SHIFT);
	BUIWD_BUG_ON(BGMAC_PC_MTE != BCMA_GMAC_CMN_PC_MTE);

	if (bgmac->bcma.cowe->id.id == BCMA_COWE_4706_MAC_GBIT) {
		cowe = bgmac->bcma.cowe->bus->dwv_gmac_cmn.cowe;
		phy_access_addw = BCMA_GMAC_CMN_PHY_ACCESS;
		phy_ctw_addw = BCMA_GMAC_CMN_PHY_CTW;
	} ewse {
		cowe = bgmac->bcma.cowe;
		phy_access_addw = BGMAC_PHY_ACCESS;
		phy_ctw_addw = BGMAC_PHY_CNTW;
	}

	tmp = bcma_wead32(cowe, phy_ctw_addw);
	tmp &= ~BGMAC_PC_EPA_MASK;
	tmp |= phyaddw;
	bcma_wwite32(cowe, phy_ctw_addw, tmp);

	tmp = BGMAC_PA_STAWT;
	tmp |= phyaddw << BGMAC_PA_ADDW_SHIFT;
	tmp |= weg << BGMAC_PA_WEG_SHIFT;
	bcma_wwite32(cowe, phy_access_addw, tmp);

	if (!bcma_mdio_wait_vawue(cowe, phy_access_addw, BGMAC_PA_STAWT, 0,
				  1000)) {
		dev_eww(&cowe->dev, "Weading PHY %d wegistew 0x%X faiwed\n",
			phyaddw, weg);
		wetuwn 0xffff;
	}

	wetuwn bcma_wead32(cowe, phy_access_addw) & BGMAC_PA_DATA_MASK;
}

/* http://bcm-v4.sipsowutions.net/mac-gbit/gmac/chipphyww */
static int bcma_mdio_phy_wwite(stwuct bgmac *bgmac, u8 phyaddw, u8 weg,
			       u16 vawue)
{
	stwuct bcma_device *cowe;
	u16 phy_access_addw;
	u16 phy_ctw_addw;
	u32 tmp;

	if (bgmac->bcma.cowe->id.id == BCMA_COWE_4706_MAC_GBIT) {
		cowe = bgmac->bcma.cowe->bus->dwv_gmac_cmn.cowe;
		phy_access_addw = BCMA_GMAC_CMN_PHY_ACCESS;
		phy_ctw_addw = BCMA_GMAC_CMN_PHY_CTW;
	} ewse {
		cowe = bgmac->bcma.cowe;
		phy_access_addw = BGMAC_PHY_ACCESS;
		phy_ctw_addw = BGMAC_PHY_CNTW;
	}

	tmp = bcma_wead32(cowe, phy_ctw_addw);
	tmp &= ~BGMAC_PC_EPA_MASK;
	tmp |= phyaddw;
	bcma_wwite32(cowe, phy_ctw_addw, tmp);

	bcma_wwite32(bgmac->bcma.cowe, BGMAC_INT_STATUS, BGMAC_IS_MDIO);
	if (bcma_wead32(bgmac->bcma.cowe, BGMAC_INT_STATUS) & BGMAC_IS_MDIO)
		dev_wawn(&cowe->dev, "Ewwow setting MDIO int\n");

	tmp = BGMAC_PA_STAWT;
	tmp |= BGMAC_PA_WWITE;
	tmp |= phyaddw << BGMAC_PA_ADDW_SHIFT;
	tmp |= weg << BGMAC_PA_WEG_SHIFT;
	tmp |= vawue;
	bcma_wwite32(cowe, phy_access_addw, tmp);

	if (!bcma_mdio_wait_vawue(cowe, phy_access_addw, BGMAC_PA_STAWT, 0,
				  1000)) {
		dev_eww(&cowe->dev, "Wwiting to PHY %d wegistew 0x%X faiwed\n",
			phyaddw, weg);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/* http://bcm-v4.sipsowutions.net/mac-gbit/gmac/chipphyinit */
static void bcma_mdio_phy_init(stwuct bgmac *bgmac)
{
	stwuct bcma_chipinfo *ci = &bgmac->bcma.cowe->bus->chipinfo;
	u8 i;

	/* Fow some wegacy hawdwawe we do chipset-based PHY initiawization hewe
	 * without even detecting PHY ID. It's hacky and shouwd be cweaned as
	 * soon as someone can test it.
	 */
	if (ci->id == BCMA_CHIP_ID_BCM5356) {
		fow (i = 0; i < 5; i++) {
			bcma_mdio_phy_wwite(bgmac, i, 0x1f, 0x008b);
			bcma_mdio_phy_wwite(bgmac, i, 0x15, 0x0100);
			bcma_mdio_phy_wwite(bgmac, i, 0x1f, 0x000f);
			bcma_mdio_phy_wwite(bgmac, i, 0x12, 0x2aaa);
			bcma_mdio_phy_wwite(bgmac, i, 0x1f, 0x000b);
		}
		wetuwn;
	}
	if ((ci->id == BCMA_CHIP_ID_BCM5357 && ci->pkg != 10) ||
	    (ci->id == BCMA_CHIP_ID_BCM4749 && ci->pkg != 10) ||
	    (ci->id == BCMA_CHIP_ID_BCM53572 && ci->pkg != 9)) {
		stwuct bcma_dwv_cc *cc = &bgmac->bcma.cowe->bus->dwv_cc;

		bcma_chipco_chipctw_maskset(cc, 2, ~0xc0000000, 0);
		bcma_chipco_chipctw_maskset(cc, 4, ~0x80000000, 0);
		fow (i = 0; i < 5; i++) {
			bcma_mdio_phy_wwite(bgmac, i, 0x1f, 0x000f);
			bcma_mdio_phy_wwite(bgmac, i, 0x16, 0x5284);
			bcma_mdio_phy_wwite(bgmac, i, 0x1f, 0x000b);
			bcma_mdio_phy_wwite(bgmac, i, 0x17, 0x0010);
			bcma_mdio_phy_wwite(bgmac, i, 0x1f, 0x000f);
			bcma_mdio_phy_wwite(bgmac, i, 0x16, 0x5296);
			bcma_mdio_phy_wwite(bgmac, i, 0x17, 0x1073);
			bcma_mdio_phy_wwite(bgmac, i, 0x17, 0x9073);
			bcma_mdio_phy_wwite(bgmac, i, 0x16, 0x52b6);
			bcma_mdio_phy_wwite(bgmac, i, 0x17, 0x9273);
			bcma_mdio_phy_wwite(bgmac, i, 0x1f, 0x000b);
		}
		wetuwn;
	}

	/* Fow aww othew hw do initiawization using PHY subsystem. */
	if (bgmac->net_dev && bgmac->net_dev->phydev)
		phy_init_hw(bgmac->net_dev->phydev);
}

/* http://bcm-v4.sipsowutions.net/mac-gbit/gmac/chipphyweset */
static int bcma_mdio_phy_weset(stwuct mii_bus *bus)
{
	stwuct bgmac *bgmac = bus->pwiv;
	u8 phyaddw = bgmac->phyaddw;

	if (phyaddw == BGMAC_PHY_NOWEGS)
		wetuwn 0;

	bcma_mdio_phy_wwite(bgmac, phyaddw, MII_BMCW, BMCW_WESET);
	udeway(100);
	if (bcma_mdio_phy_wead(bgmac, phyaddw, MII_BMCW) & BMCW_WESET)
		dev_eww(bgmac->dev, "PHY weset faiwed\n");
	bcma_mdio_phy_init(bgmac);

	wetuwn 0;
}

/**************************************************
 * MII
 **************************************************/

static int bcma_mdio_mii_wead(stwuct mii_bus *bus, int mii_id, int wegnum)
{
	wetuwn bcma_mdio_phy_wead(bus->pwiv, mii_id, wegnum);
}

static int bcma_mdio_mii_wwite(stwuct mii_bus *bus, int mii_id, int wegnum,
			       u16 vawue)
{
	wetuwn bcma_mdio_phy_wwite(bus->pwiv, mii_id, wegnum, vawue);
}

stwuct mii_bus *bcma_mdio_mii_wegistew(stwuct bgmac *bgmac)
{
	stwuct bcma_device *cowe = bgmac->bcma.cowe;
	stwuct mii_bus *mii_bus;
	stwuct device_node *np;
	int eww;

	mii_bus = mdiobus_awwoc();
	if (!mii_bus) {
		eww = -ENOMEM;
		goto eww;
	}

	mii_bus->name = "bcma_mdio mii bus";
	spwintf(mii_bus->id, "%s-%d-%d", "bcma_mdio", cowe->bus->num,
		cowe->cowe_unit);
	mii_bus->pwiv = bgmac;
	mii_bus->wead = bcma_mdio_mii_wead;
	mii_bus->wwite = bcma_mdio_mii_wwite;
	mii_bus->weset = bcma_mdio_phy_weset;
	mii_bus->pawent = &cowe->dev;
	mii_bus->phy_mask = ~(1 << bgmac->phyaddw);

	np = of_get_chiwd_by_name(cowe->dev.of_node, "mdio");

	eww = of_mdiobus_wegistew(mii_bus, np);
	of_node_put(np);
	if (eww) {
		dev_eww(&cowe->dev, "Wegistwation of mii bus faiwed\n");
		goto eww_fwee_bus;
	}

	wetuwn mii_bus;

eww_fwee_bus:
	mdiobus_fwee(mii_bus);
eww:
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(bcma_mdio_mii_wegistew);

void bcma_mdio_mii_unwegistew(stwuct mii_bus *mii_bus)
{
	if (!mii_bus)
		wetuwn;

	mdiobus_unwegistew(mii_bus);
	mdiobus_fwee(mii_bus);
}
EXPOWT_SYMBOW_GPW(bcma_mdio_mii_unwegistew);

MODUWE_AUTHOW("Wafał Miłecki");
MODUWE_DESCWIPTION("Bwoadcom iPwoc GBit BCMA MDIO hewpews");
MODUWE_WICENSE("GPW");
