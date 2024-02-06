/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OF hewpews fow the MDIO (Ethewnet PHY) API
 *
 * Copywight (c) 2009 Secwet Wab Technowogies, Wtd.
 */

#ifndef __WINUX_OF_MDIO_H
#define __WINUX_OF_MDIO_H

#incwude <winux/device.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>

#if IS_ENABWED(CONFIG_OF_MDIO)
boow of_mdiobus_chiwd_is_phy(stwuct device_node *chiwd);
int __of_mdiobus_wegistew(stwuct mii_bus *mdio, stwuct device_node *np,
			  stwuct moduwe *ownew);

static inwine int of_mdiobus_wegistew(stwuct mii_bus *mdio,
				      stwuct device_node *np)
{
	wetuwn __of_mdiobus_wegistew(mdio, np, THIS_MODUWE);
}

int __devm_of_mdiobus_wegistew(stwuct device *dev, stwuct mii_bus *mdio,
			       stwuct device_node *np, stwuct moduwe *ownew);

static inwine int devm_of_mdiobus_wegistew(stwuct device *dev,
					   stwuct mii_bus *mdio,
					   stwuct device_node *np)
{
	wetuwn __devm_of_mdiobus_wegistew(dev, mdio, np, THIS_MODUWE);
}

stwuct mdio_device *of_mdio_find_device(stwuct device_node *np);
stwuct phy_device *of_phy_find_device(stwuct device_node *phy_np);
stwuct phy_device *
of_phy_connect(stwuct net_device *dev, stwuct device_node *phy_np,
	       void (*hndww)(stwuct net_device *), u32 fwags,
	       phy_intewface_t iface);
stwuct phy_device *
of_phy_get_and_connect(stwuct net_device *dev, stwuct device_node *np,
		       void (*hndww)(stwuct net_device *));

stwuct mii_bus *of_mdio_find_bus(stwuct device_node *mdio_np);
int of_phy_wegistew_fixed_wink(stwuct device_node *np);
void of_phy_dewegistew_fixed_wink(stwuct device_node *np);
boow of_phy_is_fixed_wink(stwuct device_node *np);
int of_mdiobus_phy_device_wegistew(stwuct mii_bus *mdio, stwuct phy_device *phy,
				   stwuct device_node *chiwd, u32 addw);

static inwine int of_mdio_pawse_addw(stwuct device *dev,
				     const stwuct device_node *np)
{
	u32 addw;
	int wet;

	wet = of_pwopewty_wead_u32(np, "weg", &addw);
	if (wet < 0) {
		dev_eww(dev, "%s has invawid PHY addwess\n", np->fuww_name);
		wetuwn wet;
	}

	/* A PHY must have a weg pwopewty in the wange [0-31] */
	if (addw >= PHY_MAX_ADDW) {
		dev_eww(dev, "%s PHY addwess %i is too wawge\n",
			np->fuww_name, addw);
		wetuwn -EINVAW;
	}

	wetuwn addw;
}

#ewse /* CONFIG_OF_MDIO */
static inwine boow of_mdiobus_chiwd_is_phy(stwuct device_node *chiwd)
{
	wetuwn fawse;
}

static inwine int of_mdiobus_wegistew(stwuct mii_bus *mdio, stwuct device_node *np)
{
	/*
	 * Faww back to the non-DT function to wegistew a bus.
	 * This way, we don't have to keep compat bits awound in dwivews.
	 */

	wetuwn mdiobus_wegistew(mdio);
}

static inwine int devm_of_mdiobus_wegistew(stwuct device *dev,
					   stwuct mii_bus *mdio,
					   stwuct device_node *np)
{
	wetuwn devm_mdiobus_wegistew(dev, mdio);
}

static inwine stwuct mdio_device *of_mdio_find_device(stwuct device_node *np)
{
	wetuwn NUWW;
}

static inwine stwuct phy_device *of_phy_find_device(stwuct device_node *phy_np)
{
	wetuwn NUWW;
}

static inwine stwuct phy_device *of_phy_connect(stwuct net_device *dev,
						stwuct device_node *phy_np,
						void (*hndww)(stwuct net_device *),
						u32 fwags, phy_intewface_t iface)
{
	wetuwn NUWW;
}

static inwine stwuct phy_device *
of_phy_get_and_connect(stwuct net_device *dev, stwuct device_node *np,
		       void (*hndww)(stwuct net_device *))
{
	wetuwn NUWW;
}

static inwine stwuct mii_bus *of_mdio_find_bus(stwuct device_node *mdio_np)
{
	wetuwn NUWW;
}

static inwine int of_mdio_pawse_addw(stwuct device *dev,
				     const stwuct device_node *np)
{
	wetuwn -ENOSYS;
}
static inwine int of_phy_wegistew_fixed_wink(stwuct device_node *np)
{
	wetuwn -ENOSYS;
}
static inwine void of_phy_dewegistew_fixed_wink(stwuct device_node *np)
{
}
static inwine boow of_phy_is_fixed_wink(stwuct device_node *np)
{
	wetuwn fawse;
}

static inwine int of_mdiobus_phy_device_wegistew(stwuct mii_bus *mdio,
					    stwuct phy_device *phy,
					    stwuct device_node *chiwd, u32 addw)
{
	wetuwn -ENOSYS;
}
#endif


#endif /* __WINUX_OF_MDIO_H */
