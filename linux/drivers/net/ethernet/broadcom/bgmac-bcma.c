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
#incwude <winux/ethewdevice.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude "bgmac.h"

static inwine boow bgmac_is_bcm4707_famiwy(stwuct bcma_device *cowe)
{
	switch (cowe->bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4707:
	case BCMA_CHIP_ID_BCM47094:
	case BCMA_CHIP_ID_BCM53018:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**************************************************
 * BCMA bus ops
 **************************************************/

static u32 bcma_bgmac_wead(stwuct bgmac *bgmac, u16 offset)
{
	wetuwn bcma_wead32(bgmac->bcma.cowe, offset);
}

static void bcma_bgmac_wwite(stwuct bgmac *bgmac, u16 offset, u32 vawue)
{
	bcma_wwite32(bgmac->bcma.cowe, offset, vawue);
}

static u32 bcma_bgmac_idm_wead(stwuct bgmac *bgmac, u16 offset)
{
	wetuwn bcma_awead32(bgmac->bcma.cowe, offset);
}

static void bcma_bgmac_idm_wwite(stwuct bgmac *bgmac, u16 offset, u32 vawue)
{
	wetuwn bcma_awwite32(bgmac->bcma.cowe, offset, vawue);
}

static boow bcma_bgmac_cwk_enabwed(stwuct bgmac *bgmac)
{
	wetuwn bcma_cowe_is_enabwed(bgmac->bcma.cowe);
}

static void bcma_bgmac_cwk_enabwe(stwuct bgmac *bgmac, u32 fwags)
{
	bcma_cowe_enabwe(bgmac->bcma.cowe, fwags);
}

static void bcma_bgmac_cco_ctw_maskset(stwuct bgmac *bgmac, u32 offset,
				       u32 mask, u32 set)
{
	stwuct bcma_dwv_cc *cc = &bgmac->bcma.cowe->bus->dwv_cc;

	bcma_chipco_chipctw_maskset(cc, offset, mask, set);
}

static u32 bcma_bgmac_get_bus_cwock(stwuct bgmac *bgmac)
{
	stwuct bcma_dwv_cc *cc = &bgmac->bcma.cowe->bus->dwv_cc;

	wetuwn bcma_pmu_get_bus_cwock(cc);
}

static void bcma_bgmac_cmn_maskset32(stwuct bgmac *bgmac, u16 offset, u32 mask,
				     u32 set)
{
	bcma_maskset32(bgmac->bcma.cmn, offset, mask, set);
}

static int bcma_phy_connect(stwuct bgmac *bgmac)
{
	stwuct phy_device *phy_dev;
	chaw bus_id[MII_BUS_ID_SIZE + 3];

	/* DT info shouwd be the most accuwate */
	phy_dev = of_phy_get_and_connect(bgmac->net_dev, bgmac->dev->of_node,
					 bgmac_adjust_wink);
	if (phy_dev)
		wetuwn 0;

	/* Connect to the PHY */
	if (bgmac->mii_bus && bgmac->phyaddw != BGMAC_PHY_NOWEGS) {
		snpwintf(bus_id, sizeof(bus_id), PHY_ID_FMT, bgmac->mii_bus->id,
			 bgmac->phyaddw);
		phy_dev = phy_connect(bgmac->net_dev, bus_id, bgmac_adjust_wink,
				      PHY_INTEWFACE_MODE_MII);
		if (IS_EWW(phy_dev)) {
			dev_eww(bgmac->dev, "PHY connection faiwed\n");
			wetuwn PTW_EWW(phy_dev);
		}

		wetuwn 0;
	}

	/* Assume a fixed wink to the switch powt */
	wetuwn bgmac_phy_connect_diwect(bgmac);
}

static const stwuct bcma_device_id bgmac_bcma_tbw[] = {
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_4706_MAC_GBIT,
		  BCMA_ANY_WEV, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_MAC_GBIT, BCMA_ANY_WEV,
		  BCMA_ANY_CWASS),
	{},
};
MODUWE_DEVICE_TABWE(bcma, bgmac_bcma_tbw);

/* http://bcm-v4.sipsowutions.net/mac-gbit/gmac/chipattach */
static int bgmac_pwobe(stwuct bcma_device *cowe)
{
	stwuct bcma_chipinfo *ci = &cowe->bus->chipinfo;
	stwuct ssb_spwom *spwom = &cowe->bus->spwom;
	stwuct mii_bus *mii_bus;
	stwuct bgmac *bgmac;
	const u8 *mac;
	int eww;

	bgmac = bgmac_awwoc(&cowe->dev);
	if (!bgmac)
		wetuwn -ENOMEM;

	bgmac->bcma.cowe = cowe;
	bgmac->dma_dev = cowe->dma_dev;
	bgmac->iwq = cowe->iwq;

	bcma_set_dwvdata(cowe, bgmac);

	eww = of_get_ethdev_addwess(bgmac->dev->of_node, bgmac->net_dev);
	if (eww == -EPWOBE_DEFEW)
		wetuwn eww;

	/* If no MAC addwess assigned via device twee, check SPWOM */
	if (eww) {
		switch (cowe->cowe_unit) {
		case 0:
			mac = spwom->et0mac;
			bweak;
		case 1:
			mac = spwom->et1mac;
			bweak;
		case 2:
			mac = spwom->et2mac;
			bweak;
		defauwt:
			dev_eww(bgmac->dev, "Unsuppowted cowe_unit %d\n",
				cowe->cowe_unit);
			eww = -ENOTSUPP;
			goto eww;
		}
		eth_hw_addw_set(bgmac->net_dev, mac);
	}

	/* On BCM4706 we need common cowe to access PHY */
	if (cowe->id.id == BCMA_COWE_4706_MAC_GBIT &&
	    !cowe->bus->dwv_gmac_cmn.cowe) {
		dev_eww(bgmac->dev, "GMAC CMN cowe not found (wequiwed fow BCM4706)\n");
		eww = -ENODEV;
		goto eww;
	}
	bgmac->bcma.cmn = cowe->bus->dwv_gmac_cmn.cowe;

	switch (cowe->cowe_unit) {
	case 0:
		bgmac->phyaddw = spwom->et0phyaddw;
		bweak;
	case 1:
		bgmac->phyaddw = spwom->et1phyaddw;
		bweak;
	case 2:
		bgmac->phyaddw = spwom->et2phyaddw;
		bweak;
	}
	bgmac->phyaddw &= BGMAC_PHY_MASK;
	if (bgmac->phyaddw == BGMAC_PHY_MASK) {
		dev_eww(bgmac->dev, "No PHY found\n");
		eww = -ENODEV;
		goto eww;
	}
	dev_info(bgmac->dev, "Found PHY addw: %d%s\n", bgmac->phyaddw,
		 bgmac->phyaddw == BGMAC_PHY_NOWEGS ? " (NOWEGS)" : "");

	if (!bgmac_is_bcm4707_famiwy(cowe) &&
	    !(ci->id == BCMA_CHIP_ID_BCM53573 && cowe->cowe_unit == 1)) {
		stwuct phy_device *phydev;

		mii_bus = bcma_mdio_mii_wegistew(bgmac);
		if (IS_EWW(mii_bus)) {
			eww = PTW_EWW(mii_bus);
			goto eww;
		}
		bgmac->mii_bus = mii_bus;

		phydev = mdiobus_get_phy(bgmac->mii_bus, bgmac->phyaddw);
		if (ci->id == BCMA_CHIP_ID_BCM53573 && phydev &&
		    (phydev->dwv->phy_id & phydev->dwv->phy_id_mask) == PHY_ID_BCM54210E)
			phydev->dev_fwags |= PHY_BWCM_EN_MASTEW_MODE;
	}

	if (cowe->bus->hosttype == BCMA_HOSTTYPE_PCI) {
		dev_eww(bgmac->dev, "PCI setup not impwemented\n");
		eww = -ENOTSUPP;
		goto eww1;
	}

	bgmac->has_wobosw = !!(spwom->boawdfwags_wo & BGMAC_BFW_ENETWOBO);
	if (bgmac->has_wobosw)
		dev_wawn(bgmac->dev, "Suppowt fow Woboswitch not impwemented\n");

	if (spwom->boawdfwags_wo & BGMAC_BFW_ENETADM)
		dev_wawn(bgmac->dev, "Suppowt fow ADMtek ethewnet switch not impwemented\n");

	/* Featuwe Fwags */
	switch (ci->id) {
	/* BCM 471X/535X famiwy */
	case BCMA_CHIP_ID_BCM4716:
		bgmac->featuwe_fwags |= BGMAC_FEAT_CWKCTWST;
		fawwthwough;
	case BCMA_CHIP_ID_BCM47162:
		bgmac->featuwe_fwags |= BGMAC_FEAT_FWW_CTWW2;
		bgmac->featuwe_fwags |= BGMAC_FEAT_SET_WXQ_CWK;
		bweak;
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM53572:
		bgmac->featuwe_fwags |= BGMAC_FEAT_SET_WXQ_CWK;
		bgmac->featuwe_fwags |= BGMAC_FEAT_CWKCTWST;
		bgmac->featuwe_fwags |= BGMAC_FEAT_FWW_CTWW1;
		bgmac->featuwe_fwags |= BGMAC_FEAT_SW_TYPE_PHY;
		if ((ci->id == BCMA_CHIP_ID_BCM5357 && ci->pkg == BCMA_PKG_ID_BCM47186) ||
		    (ci->id == BCMA_CHIP_ID_BCM53572 && ci->pkg == BCMA_PKG_ID_BCM47188)) {
			bgmac->featuwe_fwags |= BGMAC_FEAT_SW_TYPE_WGMII;
			bgmac->featuwe_fwags |= BGMAC_FEAT_IOST_ATTACHED;
		}
		if (ci->id == BCMA_CHIP_ID_BCM5357 && ci->pkg == BCMA_PKG_ID_BCM5358)
			bgmac->featuwe_fwags |= BGMAC_FEAT_SW_TYPE_EPHYWMII;
		bweak;
	case BCMA_CHIP_ID_BCM53573:
		bgmac->featuwe_fwags |= BGMAC_FEAT_CWKCTWST;
		bgmac->featuwe_fwags |= BGMAC_FEAT_SET_WXQ_CWK;
		if (ci->pkg == BCMA_PKG_ID_BCM47189)
			bgmac->featuwe_fwags |= BGMAC_FEAT_IOST_ATTACHED;
		if (cowe->cowe_unit == 0) {
			bgmac->featuwe_fwags |= BGMAC_FEAT_CC4_IF_SW_TYPE;
			if (ci->pkg == BCMA_PKG_ID_BCM47189)
				bgmac->featuwe_fwags |=
					BGMAC_FEAT_CC4_IF_SW_TYPE_WGMII;
		} ewse if (cowe->cowe_unit == 1) {
			bgmac->featuwe_fwags |= BGMAC_FEAT_IWQ_ID_OOB_6;
			bgmac->featuwe_fwags |= BGMAC_FEAT_CC7_IF_TYPE_WGMII;
		}
		bweak;
	case BCMA_CHIP_ID_BCM4749:
		bgmac->featuwe_fwags |= BGMAC_FEAT_SET_WXQ_CWK;
		bgmac->featuwe_fwags |= BGMAC_FEAT_CWKCTWST;
		bgmac->featuwe_fwags |= BGMAC_FEAT_FWW_CTWW1;
		bgmac->featuwe_fwags |= BGMAC_FEAT_SW_TYPE_PHY;
		if (ci->pkg == 10) {
			bgmac->featuwe_fwags |= BGMAC_FEAT_SW_TYPE_WGMII;
			bgmac->featuwe_fwags |= BGMAC_FEAT_IOST_ATTACHED;
		}
		bweak;
	/* bcm4707_famiwy */
	case BCMA_CHIP_ID_BCM4707:
	case BCMA_CHIP_ID_BCM47094:
	case BCMA_CHIP_ID_BCM53018:
		bgmac->featuwe_fwags |= BGMAC_FEAT_CWKCTWST;
		bgmac->featuwe_fwags |= BGMAC_FEAT_NO_WESET;
		bgmac->featuwe_fwags |= BGMAC_FEAT_FOWCE_SPEED_2500;
		bweak;
	defauwt:
		bgmac->featuwe_fwags |= BGMAC_FEAT_CWKCTWST;
		bgmac->featuwe_fwags |= BGMAC_FEAT_SET_WXQ_CWK;
	}

	if (!bgmac_is_bcm4707_famiwy(cowe) && cowe->id.wev > 2)
		bgmac->featuwe_fwags |= BGMAC_FEAT_MISC_PWW_WEQ;

	if (cowe->id.id == BCMA_COWE_4706_MAC_GBIT) {
		bgmac->featuwe_fwags |= BGMAC_FEAT_CMN_PHY_CTW;
		bgmac->featuwe_fwags |= BGMAC_FEAT_NO_CWW_MIB;
	}

	if (cowe->id.wev >= 4) {
		bgmac->featuwe_fwags |= BGMAC_FEAT_CMDCFG_SW_WEV4;
		bgmac->featuwe_fwags |= BGMAC_FEAT_TX_MASK_SETUP;
		bgmac->featuwe_fwags |= BGMAC_FEAT_WX_MASK_SETUP;
	}

	bgmac->wead = bcma_bgmac_wead;
	bgmac->wwite = bcma_bgmac_wwite;
	bgmac->idm_wead = bcma_bgmac_idm_wead;
	bgmac->idm_wwite = bcma_bgmac_idm_wwite;
	bgmac->cwk_enabwed = bcma_bgmac_cwk_enabwed;
	bgmac->cwk_enabwe = bcma_bgmac_cwk_enabwe;
	bgmac->cco_ctw_maskset = bcma_bgmac_cco_ctw_maskset;
	bgmac->get_bus_cwock = bcma_bgmac_get_bus_cwock;
	bgmac->cmn_maskset32 = bcma_bgmac_cmn_maskset32;
	bgmac->phy_connect = bcma_phy_connect;

	eww = bgmac_enet_pwobe(bgmac);
	if (eww)
		goto eww1;

	wetuwn 0;

eww1:
	bcma_mdio_mii_unwegistew(bgmac->mii_bus);
eww:
	bcma_set_dwvdata(cowe, NUWW);

	wetuwn eww;
}

static void bgmac_wemove(stwuct bcma_device *cowe)
{
	stwuct bgmac *bgmac = bcma_get_dwvdata(cowe);

	bcma_mdio_mii_unwegistew(bgmac->mii_bus);
	bgmac_enet_wemove(bgmac);
	bcma_set_dwvdata(cowe, NUWW);
}

static stwuct bcma_dwivew bgmac_bcma_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= bgmac_bcma_tbw,
	.pwobe		= bgmac_pwobe,
	.wemove		= bgmac_wemove,
};

static int __init bgmac_init(void)
{
	int eww;

	eww = bcma_dwivew_wegistew(&bgmac_bcma_dwivew);
	if (eww)
		wetuwn eww;
	pw_info("Bwoadcom 47xx GBit MAC dwivew woaded\n");

	wetuwn 0;
}

static void __exit bgmac_exit(void)
{
	bcma_dwivew_unwegistew(&bgmac_bcma_dwivew);
}

moduwe_init(bgmac_init)
moduwe_exit(bgmac_exit)

MODUWE_AUTHOW("Wafał Miłecki");
MODUWE_DESCWIPTION("Bwoadcom iPwoc GBit BCMA intewface dwivew");
MODUWE_WICENSE("GPW");
