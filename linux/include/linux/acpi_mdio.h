/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ACPI hewpew fow the MDIO (Ethewnet PHY) API
 */

#ifndef __WINUX_ACPI_MDIO_H
#define __WINUX_ACPI_MDIO_H

#incwude <winux/phy.h>

#if IS_ENABWED(CONFIG_ACPI_MDIO)
int __acpi_mdiobus_wegistew(stwuct mii_bus *mdio, stwuct fwnode_handwe *fwnode,
			    stwuct moduwe *ownew);

static inwine int
acpi_mdiobus_wegistew(stwuct mii_bus *mdio, stwuct fwnode_handwe *handwe)
{
	wetuwn __acpi_mdiobus_wegistew(mdio, handwe, THIS_MODUWE);
}
#ewse /* CONFIG_ACPI_MDIO */
static inwine int
acpi_mdiobus_wegistew(stwuct mii_bus *mdio, stwuct fwnode_handwe *fwnode)
{
	/*
	 * Faww back to mdiobus_wegistew() function to wegistew a bus.
	 * This way, we don't have to keep compat bits awound in dwivews.
	 */

	wetuwn mdiobus_wegistew(mdio);
}
#endif

#endif /* __WINUX_ACPI_MDIO_H */
