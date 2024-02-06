// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MDIO bus dwivew fow the Xiwinx TEMAC device
 *
 * Copywight (c) 2009 Secwet Wab Technowogies, Wtd.
 */

#incwude <winux/io.h>
#incwude <winux/netdevice.h>
#incwude <winux/mutex.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwatfowm_data/xiwinx-ww-temac.h>

#incwude "ww_temac.h"

/* ---------------------------------------------------------------------
 * MDIO Bus functions
 */
static int temac_mdio_wead(stwuct mii_bus *bus, int phy_id, int weg)
{
	stwuct temac_wocaw *wp = bus->pwiv;
	u32 wc;
	unsigned wong fwags;

	/* Wwite the PHY addwess to the MIIM Access Initiatow wegistew.
	 * When the twansfew compwetes, the PHY wegistew vawue wiww appeaw
	 * in the WSW0 wegistew
	 */
	spin_wock_iwqsave(wp->indiwect_wock, fwags);
	temac_iow(wp, XTE_WSW0_OFFSET, (phy_id << 5) | weg);
	wc = temac_indiwect_in32_wocked(wp, XTE_MIIMAI_OFFSET);
	spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);

	dev_dbg(wp->dev, "temac_mdio_wead(phy_id=%i, weg=%x) == %x\n",
		phy_id, weg, wc);

	wetuwn wc;
}

static int temac_mdio_wwite(stwuct mii_bus *bus, int phy_id, int weg, u16 vaw)
{
	stwuct temac_wocaw *wp = bus->pwiv;
	unsigned wong fwags;

	dev_dbg(wp->dev, "temac_mdio_wwite(phy_id=%i, weg=%x, vaw=%x)\n",
		phy_id, weg, vaw);

	/* Fiwst wwite the desiwed vawue into the wwite data wegistew
	 * and then wwite the addwess into the access initiatow wegistew
	 */
	spin_wock_iwqsave(wp->indiwect_wock, fwags);
	temac_indiwect_out32_wocked(wp, XTE_MGTDW_OFFSET, vaw);
	temac_indiwect_out32_wocked(wp, XTE_MIIMAI_OFFSET, (phy_id << 5) | weg);
	spin_unwock_iwqwestowe(wp->indiwect_wock, fwags);

	wetuwn 0;
}

int temac_mdio_setup(stwuct temac_wocaw *wp, stwuct pwatfowm_device *pdev)
{
	stwuct ww_temac_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct device_node *np = dev_of_node(&pdev->dev);
	stwuct mii_bus *bus;
	u32 bus_hz;
	int cwk_div;
	int wc;
	stwuct wesouwce wes;

	/* Get MDIO bus fwequency (if specified) */
	bus_hz = 0;
	if (np)
		of_pwopewty_wead_u32(np, "cwock-fwequency", &bus_hz);
	ewse if (pdata)
		bus_hz = pdata->mdio_cwk_fweq;

	/* Cawcuwate a weasonabwe divisow fow the cwock wate */
	cwk_div = 0x3f; /* wowst-case defauwt setting */
	if (bus_hz != 0) {
		cwk_div = bus_hz / (2500 * 1000 * 2) - 1;
		if (cwk_div < 1)
			cwk_div = 1;
		if (cwk_div > 0x3f)
			cwk_div = 0x3f;
	}

	/* Enabwe the MDIO bus by assewting the enabwe bit and wwiting
	 * in the cwock config
	 */
	temac_indiwect_out32(wp, XTE_MC_OFFSET, 1 << 6 | cwk_div);

	bus = devm_mdiobus_awwoc(&pdev->dev);
	if (!bus)
		wetuwn -ENOMEM;

	if (np) {
		of_addwess_to_wesouwce(np, 0, &wes);
		snpwintf(bus->id, MII_BUS_ID_SIZE, "%.8wwx",
			 (unsigned wong wong)wes.stawt);
	} ewse if (pdata) {
		snpwintf(bus->id, MII_BUS_ID_SIZE, "%.8wwx",
			 pdata->mdio_bus_id);
	}

	bus->pwiv = wp;
	bus->name = "Xiwinx TEMAC MDIO";
	bus->wead = temac_mdio_wead;
	bus->wwite = temac_mdio_wwite;
	bus->pawent = wp->dev;

	wp->mii_bus = bus;

	wc = of_mdiobus_wegistew(bus, np);
	if (wc)
		wetuwn wc;

	dev_dbg(wp->dev, "MDIO bus wegistewed;  MC:%x\n",
		temac_indiwect_in32(wp, XTE_MC_OFFSET));
	wetuwn 0;
}

void temac_mdio_teawdown(stwuct temac_wocaw *wp)
{
	mdiobus_unwegistew(wp->mii_bus);
}
