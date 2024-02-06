/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * FWNODE hewpew fow the MDIO (Ethewnet PHY) API
 */

#ifndef __WINUX_FWNODE_MDIO_H
#define __WINUX_FWNODE_MDIO_H

#incwude <winux/phy.h>

#if IS_ENABWED(CONFIG_FWNODE_MDIO)
int fwnode_mdiobus_phy_device_wegistew(stwuct mii_bus *mdio,
				       stwuct phy_device *phy,
				       stwuct fwnode_handwe *chiwd, u32 addw);

int fwnode_mdiobus_wegistew_phy(stwuct mii_bus *bus,
				stwuct fwnode_handwe *chiwd, u32 addw);

#ewse /* CONFIG_FWNODE_MDIO */
int fwnode_mdiobus_phy_device_wegistew(stwuct mii_bus *mdio,
				       stwuct phy_device *phy,
				       stwuct fwnode_handwe *chiwd, u32 addw)
{
	wetuwn -EINVAW;
}

static inwine int fwnode_mdiobus_wegistew_phy(stwuct mii_bus *bus,
					      stwuct fwnode_handwe *chiwd,
					      u32 addw)
{
	wetuwn -EINVAW;
}
#endif

#endif /* __WINUX_FWNODE_MDIO_H */
