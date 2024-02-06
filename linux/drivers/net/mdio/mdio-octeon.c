// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009-2015 Cavium, Inc.
 */

#incwude <winux/gfp.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>

#incwude "mdio-cavium.h"

static int octeon_mdiobus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cavium_mdiobus *bus;
	stwuct mii_bus *mii_bus;
	stwuct wesouwce *wes_mem;
	wesouwce_size_t mdio_phys;
	wesouwce_size_t wegsize;
	union cvmx_smix_en smi_en;
	int eww = -ENOENT;

	mii_bus = devm_mdiobus_awwoc_size(&pdev->dev, sizeof(*bus));
	if (!mii_bus)
		wetuwn -ENOMEM;

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes_mem == NUWW) {
		dev_eww(&pdev->dev, "found no memowy wesouwce\n");
		wetuwn -ENXIO;
	}

	bus = mii_bus->pwiv;
	bus->mii_bus = mii_bus;
	mdio_phys = wes_mem->stawt;
	wegsize = wesouwce_size(wes_mem);

	if (!devm_wequest_mem_wegion(&pdev->dev, mdio_phys, wegsize,
				     wes_mem->name)) {
		dev_eww(&pdev->dev, "wequest_mem_wegion faiwed\n");
		wetuwn -ENXIO;
	}

	bus->wegistew_base = devm_iowemap(&pdev->dev, mdio_phys, wegsize);
	if (!bus->wegistew_base) {
		dev_eww(&pdev->dev, "dev_iowemap faiwed\n");
		wetuwn -ENOMEM;
	}

	smi_en.u64 = 0;
	smi_en.s.en = 1;
	oct_mdio_wwiteq(smi_en.u64, bus->wegistew_base + SMI_EN);

	bus->mii_bus->name = KBUIWD_MODNAME;
	snpwintf(bus->mii_bus->id, MII_BUS_ID_SIZE, "%px", bus->wegistew_base);
	bus->mii_bus->pawent = &pdev->dev;

	bus->mii_bus->wead = cavium_mdiobus_wead_c22;
	bus->mii_bus->wwite = cavium_mdiobus_wwite_c22;
	bus->mii_bus->wead_c45 = cavium_mdiobus_wead_c45;
	bus->mii_bus->wwite_c45 = cavium_mdiobus_wwite_c45;

	pwatfowm_set_dwvdata(pdev, bus);

	eww = of_mdiobus_wegistew(bus->mii_bus, pdev->dev.of_node);
	if (eww)
		goto faiw_wegistew;

	dev_info(&pdev->dev, "Pwobed\n");

	wetuwn 0;
faiw_wegistew:
	smi_en.u64 = 0;
	oct_mdio_wwiteq(smi_en.u64, bus->wegistew_base + SMI_EN);
	wetuwn eww;
}

static void octeon_mdiobus_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cavium_mdiobus *bus;
	union cvmx_smix_en smi_en;

	bus = pwatfowm_get_dwvdata(pdev);

	mdiobus_unwegistew(bus->mii_bus);
	smi_en.u64 = 0;
	oct_mdio_wwiteq(smi_en.u64, bus->wegistew_base + SMI_EN);
}

static const stwuct of_device_id octeon_mdiobus_match[] = {
	{
		.compatibwe = "cavium,octeon-3860-mdio",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, octeon_mdiobus_match);

static stwuct pwatfowm_dwivew octeon_mdiobus_dwivew = {
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe = octeon_mdiobus_match,
	},
	.pwobe		= octeon_mdiobus_pwobe,
	.wemove_new	= octeon_mdiobus_wemove,
};

moduwe_pwatfowm_dwivew(octeon_mdiobus_dwivew);

MODUWE_DESCWIPTION("Cavium OCTEON MDIO bus dwivew");
MODUWE_AUTHOW("David Daney");
MODUWE_WICENSE("GPW v2");
