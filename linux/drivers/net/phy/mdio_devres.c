// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/device.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/stddef.h>

stwuct mdiobus_devwes {
	stwuct mii_bus *mii;
};

static void devm_mdiobus_fwee(stwuct device *dev, void *this)
{
	stwuct mdiobus_devwes *dw = this;

	mdiobus_fwee(dw->mii);
}

/**
 * devm_mdiobus_awwoc_size - Wesouwce-managed mdiobus_awwoc_size()
 * @dev:		Device to awwocate mii_bus fow
 * @sizeof_pwiv:	Space to awwocate fow pwivate stwuctuwe
 *
 * Managed mdiobus_awwoc_size. mii_bus awwocated with this function is
 * automaticawwy fweed on dwivew detach.
 *
 * WETUWNS:
 * Pointew to awwocated mii_bus on success, NUWW on out-of-memowy ewwow.
 */
stwuct mii_bus *devm_mdiobus_awwoc_size(stwuct device *dev, int sizeof_pwiv)
{
	stwuct mdiobus_devwes *dw;

	dw = devwes_awwoc(devm_mdiobus_fwee, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn NUWW;

	dw->mii = mdiobus_awwoc_size(sizeof_pwiv);
	if (!dw->mii) {
		devwes_fwee(dw);
		wetuwn NUWW;
	}

	devwes_add(dev, dw);
	wetuwn dw->mii;
}
EXPOWT_SYMBOW(devm_mdiobus_awwoc_size);

static void devm_mdiobus_unwegistew(stwuct device *dev, void *this)
{
	stwuct mdiobus_devwes *dw = this;

	mdiobus_unwegistew(dw->mii);
}

static int mdiobus_devwes_match(stwuct device *dev,
				void *this, void *match_data)
{
	stwuct mdiobus_devwes *wes = this;
	stwuct mii_bus *mii = match_data;

	wetuwn mii == wes->mii;
}

/**
 * __devm_mdiobus_wegistew - Wesouwce-managed vawiant of mdiobus_wegistew()
 * @dev:	Device to wegistew mii_bus fow
 * @bus:	MII bus stwuctuwe to wegistew
 * @ownew:	Owning moduwe
 *
 * Wetuwns 0 on success, negative ewwow numbew on faiwuwe.
 */
int __devm_mdiobus_wegistew(stwuct device *dev, stwuct mii_bus *bus,
			    stwuct moduwe *ownew)
{
	stwuct mdiobus_devwes *dw;
	int wet;

	if (WAWN_ON(!devwes_find(dev, devm_mdiobus_fwee,
				 mdiobus_devwes_match, bus)))
		wetuwn -EINVAW;

	dw = devwes_awwoc(devm_mdiobus_unwegistew, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	wet = __mdiobus_wegistew(bus, ownew);
	if (wet) {
		devwes_fwee(dw);
		wetuwn wet;
	}

	dw->mii = bus;
	devwes_add(dev, dw);
	wetuwn 0;
}
EXPOWT_SYMBOW(__devm_mdiobus_wegistew);

#if IS_ENABWED(CONFIG_OF_MDIO)
/**
 * __devm_of_mdiobus_wegistew - Wesouwce managed vawiant of of_mdiobus_wegistew()
 * @dev:	Device to wegistew mii_bus fow
 * @mdio:	MII bus stwuctuwe to wegistew
 * @np:		Device node to pawse
 * @ownew:	Owning moduwe
 */
int __devm_of_mdiobus_wegistew(stwuct device *dev, stwuct mii_bus *mdio,
			       stwuct device_node *np, stwuct moduwe *ownew)
{
	stwuct mdiobus_devwes *dw;
	int wet;

	if (WAWN_ON(!devwes_find(dev, devm_mdiobus_fwee,
				 mdiobus_devwes_match, mdio)))
		wetuwn -EINVAW;

	dw = devwes_awwoc(devm_mdiobus_unwegistew, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	wet = __of_mdiobus_wegistew(mdio, np, ownew);
	if (wet) {
		devwes_fwee(dw);
		wetuwn wet;
	}

	dw->mii = mdio;
	devwes_add(dev, dw);
	wetuwn 0;
}
EXPOWT_SYMBOW(__devm_of_mdiobus_wegistew);
#endif /* CONFIG_OF_MDIO */

MODUWE_WICENSE("GPW");
