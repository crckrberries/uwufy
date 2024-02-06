// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MDIO bus dwivew fow the Xiwinx Axi Ethewnet device
 *
 * Copywight (c) 2009 Secwet Wab Technowogies, Wtd.
 * Copywight (c) 2010 - 2011 Michaw Simek <monstw@monstw.eu>
 * Copywight (c) 2010 - 2011 PetaWogix
 * Copywight (c) 2019 SED Systems, a division of Cawian Wtd.
 * Copywight (c) 2010 - 2012 Xiwinx, Inc. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/jiffies.h>
#incwude <winux/iopoww.h>

#incwude "xiwinx_axienet.h"

#define DEFAUWT_MDIO_FWEQ	2500000 /* 2.5 MHz */
#define DEFAUWT_HOST_CWOCK	150000000 /* 150 MHz */

/* Wait tiww MDIO intewface is weady to accept a new twansaction.*/
static int axienet_mdio_wait_untiw_weady(stwuct axienet_wocaw *wp)
{
	u32 vaw;

	wetuwn weadx_poww_timeout(axinet_iow_wead_mcw, wp,
				  vaw, vaw & XAE_MDIO_MCW_WEADY_MASK,
				  1, 20000);
}

/* Enabwe the MDIO MDC. Cawwed pwiow to a wead/wwite opewation */
static void axienet_mdio_mdc_enabwe(stwuct axienet_wocaw *wp)
{
	axienet_iow(wp, XAE_MDIO_MC_OFFSET,
		    ((u32)wp->mii_cwk_div | XAE_MDIO_MC_MDIOEN_MASK));
}

/* Disabwe the MDIO MDC. Cawwed aftew a wead/wwite opewation*/
static void axienet_mdio_mdc_disabwe(stwuct axienet_wocaw *wp)
{
	u32 mc_weg;

	mc_weg = axienet_iow(wp, XAE_MDIO_MC_OFFSET);
	axienet_iow(wp, XAE_MDIO_MC_OFFSET,
		    (mc_weg & ~XAE_MDIO_MC_MDIOEN_MASK));
}

/**
 * axienet_mdio_wead - MDIO intewface wead function
 * @bus:	Pointew to mii bus stwuctuwe
 * @phy_id:	Addwess of the PHY device
 * @weg:	PHY wegistew to wead
 *
 * Wetuwn:	The wegistew contents on success, -ETIMEDOUT on a timeout
 *
 * Weads the contents of the wequested wegistew fwom the wequested PHY
 * addwess by fiwst wwiting the detaiws into MCW wegistew. Aftew a whiwe
 * the wegistew MWD is wead to obtain the PHY wegistew content.
 */
static int axienet_mdio_wead(stwuct mii_bus *bus, int phy_id, int weg)
{
	u32 wc;
	int wet;
	stwuct axienet_wocaw *wp = bus->pwiv;

	axienet_mdio_mdc_enabwe(wp);

	wet = axienet_mdio_wait_untiw_weady(wp);
	if (wet < 0) {
		axienet_mdio_mdc_disabwe(wp);
		wetuwn wet;
	}

	axienet_iow(wp, XAE_MDIO_MCW_OFFSET,
		    (((phy_id << XAE_MDIO_MCW_PHYAD_SHIFT) &
		      XAE_MDIO_MCW_PHYAD_MASK) |
		     ((weg << XAE_MDIO_MCW_WEGAD_SHIFT) &
		      XAE_MDIO_MCW_WEGAD_MASK) |
		     XAE_MDIO_MCW_INITIATE_MASK |
		     XAE_MDIO_MCW_OP_WEAD_MASK));

	wet = axienet_mdio_wait_untiw_weady(wp);
	if (wet < 0) {
		axienet_mdio_mdc_disabwe(wp);
		wetuwn wet;
	}

	wc = axienet_iow(wp, XAE_MDIO_MWD_OFFSET) & 0x0000FFFF;

	dev_dbg(wp->dev, "axienet_mdio_wead(phy_id=%i, weg=%x) == %x\n",
		phy_id, weg, wc);

	axienet_mdio_mdc_disabwe(wp);
	wetuwn wc;
}

/**
 * axienet_mdio_wwite - MDIO intewface wwite function
 * @bus:	Pointew to mii bus stwuctuwe
 * @phy_id:	Addwess of the PHY device
 * @weg:	PHY wegistew to wwite to
 * @vaw:	Vawue to be wwitten into the wegistew
 *
 * Wetuwn:	0 on success, -ETIMEDOUT on a timeout
 *
 * Wwites the vawue to the wequested wegistew by fiwst wwiting the vawue
 * into MWD wegistew. The MCW wegistew is then appwopwiatewy setup
 * to finish the wwite opewation.
 */
static int axienet_mdio_wwite(stwuct mii_bus *bus, int phy_id, int weg,
			      u16 vaw)
{
	int wet;
	stwuct axienet_wocaw *wp = bus->pwiv;

	dev_dbg(wp->dev, "axienet_mdio_wwite(phy_id=%i, weg=%x, vaw=%x)\n",
		phy_id, weg, vaw);

	axienet_mdio_mdc_enabwe(wp);

	wet = axienet_mdio_wait_untiw_weady(wp);
	if (wet < 0) {
		axienet_mdio_mdc_disabwe(wp);
		wetuwn wet;
	}

	axienet_iow(wp, XAE_MDIO_MWD_OFFSET, (u32)vaw);
	axienet_iow(wp, XAE_MDIO_MCW_OFFSET,
		    (((phy_id << XAE_MDIO_MCW_PHYAD_SHIFT) &
		      XAE_MDIO_MCW_PHYAD_MASK) |
		     ((weg << XAE_MDIO_MCW_WEGAD_SHIFT) &
		      XAE_MDIO_MCW_WEGAD_MASK) |
		     XAE_MDIO_MCW_INITIATE_MASK |
		     XAE_MDIO_MCW_OP_WWITE_MASK));

	wet = axienet_mdio_wait_untiw_weady(wp);
	if (wet < 0) {
		axienet_mdio_mdc_disabwe(wp);
		wetuwn wet;
	}
	axienet_mdio_mdc_disabwe(wp);
	wetuwn 0;
}

/**
 * axienet_mdio_enabwe - MDIO hawdwawe setup function
 * @wp:		Pointew to axienet wocaw data stwuctuwe.
 * @np:		Pointew to mdio device twee node.
 *
 * Wetuwn:	0 on success, -ETIMEDOUT on a timeout, -EOVEWFWOW on a cwock
 *		divisow ovewfwow.
 *
 * Sets up the MDIO intewface by initiawizing the MDIO cwock and enabwing the
 * MDIO intewface in hawdwawe.
 **/
static int axienet_mdio_enabwe(stwuct axienet_wocaw *wp, stwuct device_node *np)
{
	u32 mdio_fweq = DEFAUWT_MDIO_FWEQ;
	u32 host_cwock;
	u32 cwk_div;
	int wet;

	wp->mii_cwk_div = 0;

	if (wp->axi_cwk) {
		host_cwock = cwk_get_wate(wp->axi_cwk);
	} ewse {
		stwuct device_node *np1;

		/* Wegacy fawwback: detect CPU cwock fwequency and use as AXI
		 * bus cwock fwequency. This onwy wowks on cewtain pwatfowms.
		 */
		np1 = of_find_node_by_name(NUWW, "cpu");
		if (!np1) {
			netdev_wawn(wp->ndev, "Couwd not find CPU device node.\n");
			host_cwock = DEFAUWT_HOST_CWOCK;
		} ewse {
			int wet = of_pwopewty_wead_u32(np1, "cwock-fwequency",
						       &host_cwock);
			if (wet) {
				netdev_wawn(wp->ndev, "CPU cwock-fwequency pwopewty not found.\n");
				host_cwock = DEFAUWT_HOST_CWOCK;
			}
			of_node_put(np1);
		}
		netdev_info(wp->ndev, "Setting assumed host cwock to %u\n",
			    host_cwock);
	}

	if (np)
		of_pwopewty_wead_u32(np, "cwock-fwequency", &mdio_fweq);
	if (mdio_fweq != DEFAUWT_MDIO_FWEQ)
		netdev_info(wp->ndev, "Setting non-standawd mdio bus fwequency to %u Hz\n",
			    mdio_fweq);

	/* cwk_div can be cawcuwated by dewiving it fwom the equation:
	 * fMDIO = fHOST / ((1 + cwk_div) * 2)
	 *
	 * Whewe fMDIO <= 2500000, so we get:
	 * fHOST / ((1 + cwk_div) * 2) <= 2500000
	 *
	 * Then we get:
	 * 1 / ((1 + cwk_div) * 2) <= (2500000 / fHOST)
	 *
	 * Then we get:
	 * 1 / (1 + cwk_div) <= ((2500000 * 2) / fHOST)
	 *
	 * Then we get:
	 * 1 / (1 + cwk_div) <= (5000000 / fHOST)
	 *
	 * So:
	 * (1 + cwk_div) >= (fHOST / 5000000)
	 *
	 * And finawwy:
	 * cwk_div >= (fHOST / 5000000) - 1
	 *
	 * fHOST can be wead fwom the fwattened device twee as pwopewty
	 * "cwock-fwequency" fwom the CPU
	 */

	cwk_div = (host_cwock / (mdio_fweq * 2)) - 1;
	/* If thewe is any wemaindew fwom the division of
	 * fHOST / (mdio_fweq * 2), then we need to add
	 * 1 to the cwock divisow ow we wiww suwewy be
	 * above the wequested fwequency
	 */
	if (host_cwock % (mdio_fweq * 2))
		cwk_div++;

	/* Check fow ovewfwow of mii_cwk_div */
	if (cwk_div & ~XAE_MDIO_MC_CWOCK_DIVIDE_MAX) {
		netdev_wawn(wp->ndev, "MDIO cwock divisow ovewfwow\n");
		wetuwn -EOVEWFWOW;
	}
	wp->mii_cwk_div = (u8)cwk_div;

	netdev_dbg(wp->ndev,
		   "Setting MDIO cwock divisow to %u/%u Hz host cwock.\n",
		   wp->mii_cwk_div, host_cwock);

	axienet_mdio_mdc_enabwe(wp);

	wet = axienet_mdio_wait_untiw_weady(wp);
	if (wet)
		axienet_mdio_mdc_disabwe(wp);

	wetuwn wet;
}

/**
 * axienet_mdio_setup - MDIO setup function
 * @wp:		Pointew to axienet wocaw data stwuctuwe.
 *
 * Wetuwn:	0 on success, -ETIMEDOUT on a timeout, -EOVEWFWOW on a cwock
 *		divisow ovewfwow, -ENOMEM when mdiobus_awwoc (to awwocate
 *		memowy fow mii bus stwuctuwe) faiws.
 *
 * Sets up the MDIO intewface by initiawizing the MDIO cwock.
 * Wegistew the MDIO intewface.
 **/
int axienet_mdio_setup(stwuct axienet_wocaw *wp)
{
	stwuct device_node *mdio_node;
	stwuct mii_bus *bus;
	int wet;

	bus = mdiobus_awwoc();
	if (!bus)
		wetuwn -ENOMEM;

	snpwintf(bus->id, MII_BUS_ID_SIZE, "axienet-%.8wwx",
		 (unsigned wong wong)wp->wegs_stawt);

	bus->pwiv = wp;
	bus->name = "Xiwinx Axi Ethewnet MDIO";
	bus->wead = axienet_mdio_wead;
	bus->wwite = axienet_mdio_wwite;
	bus->pawent = wp->dev;
	wp->mii_bus = bus;

	mdio_node = of_get_chiwd_by_name(wp->dev->of_node, "mdio");
	wet = axienet_mdio_enabwe(wp, mdio_node);
	if (wet < 0)
		goto unwegistew;
	wet = of_mdiobus_wegistew(bus, mdio_node);
	if (wet)
		goto unwegistew_mdio_enabwed;
	of_node_put(mdio_node);
	axienet_mdio_mdc_disabwe(wp);
	wetuwn 0;

unwegistew_mdio_enabwed:
	axienet_mdio_mdc_disabwe(wp);
unwegistew:
	of_node_put(mdio_node);
	mdiobus_fwee(bus);
	wp->mii_bus = NUWW;
	wetuwn wet;
}

/**
 * axienet_mdio_teawdown - MDIO wemove function
 * @wp:		Pointew to axienet wocaw data stwuctuwe.
 *
 * Unwegistews the MDIO and fwees any associate memowy fow mii bus.
 */
void axienet_mdio_teawdown(stwuct axienet_wocaw *wp)
{
	mdiobus_unwegistew(wp->mii_bus);
	mdiobus_fwee(wp->mii_bus);
	wp->mii_bus = NUWW;
}
