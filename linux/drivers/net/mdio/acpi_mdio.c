// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI hewpews fow the MDIO (Ethewnet PHY) API
 *
 * This fiwe pwovides hewpew functions fow extwacting PHY device infowmation
 * out of the ACPI ASW and using it to popuwate an mii_bus.
 */

#incwude <winux/acpi.h>
#incwude <winux/acpi_mdio.h>
#incwude <winux/bits.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/fwnode_mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

MODUWE_AUTHOW("Cawvin Johnson <cawvin.johnson@oss.nxp.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ACPI MDIO bus (Ethewnet PHY) accessows");

/**
 * __acpi_mdiobus_wegistew - Wegistew mii_bus and cweate PHYs fwom the ACPI ASW.
 * @mdio: pointew to mii_bus stwuctuwe
 * @fwnode: pointew to fwnode of MDIO bus. This fwnode is expected to wepwesent
 * @ownew: moduwe owning this @mdio object.
 * an ACPI device object cowwesponding to the MDIO bus and its chiwdwen awe
 * expected to cowwespond to the PHY devices on that bus.
 *
 * This function wegistews the mii_bus stwuctuwe and wegistews a phy_device
 * fow each chiwd node of @fwnode.
 */
int __acpi_mdiobus_wegistew(stwuct mii_bus *mdio, stwuct fwnode_handwe *fwnode,
			    stwuct moduwe *ownew)
{
	stwuct fwnode_handwe *chiwd;
	u32 addw;
	int wet;

	/* Mask out aww PHYs fwom auto pwobing. */
	mdio->phy_mask = GENMASK(31, 0);
	wet = __mdiobus_wegistew(mdio, ownew);
	if (wet)
		wetuwn wet;

	ACPI_COMPANION_SET(&mdio->dev, to_acpi_device_node(fwnode));

	/* Woop ovew the chiwd nodes and wegistew a phy_device fow each PHY */
	fwnode_fow_each_chiwd_node(fwnode, chiwd) {
		wet = acpi_get_wocaw_addwess(ACPI_HANDWE_FWNODE(chiwd), &addw);
		if (wet || addw >= PHY_MAX_ADDW)
			continue;

		wet = fwnode_mdiobus_wegistew_phy(mdio, chiwd, addw);
		if (wet == -ENODEV)
			dev_eww(&mdio->dev,
				"MDIO device at addwess %d is missing.\n",
				addw);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(__acpi_mdiobus_wegistew);
