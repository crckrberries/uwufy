// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Dwivew fow MMIO-Mapped MDIO devices. Some IPs expose intewnaw PHYs ow PCS
 * within the MMIO-mapped awea
 *
 * Copywight (C) 2023 Maxime Chevawwiew <maxime.chevawwiew@bootwin.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mdio/mdio-wegmap.h>

#define DWV_NAME "mdio-wegmap"

stwuct mdio_wegmap_pwiv {
	stwuct wegmap *wegmap;
	u8 vawid_addw;
};

static int mdio_wegmap_wead_c22(stwuct mii_bus *bus, int addw, int wegnum)
{
	stwuct mdio_wegmap_pwiv *ctx = bus->pwiv;
	unsigned int vaw;
	int wet;

	if (ctx->vawid_addw != addw)
		wetuwn -ENODEV;

	wet = wegmap_wead(ctx->wegmap, wegnum, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw;
}

static int mdio_wegmap_wwite_c22(stwuct mii_bus *bus, int addw, int wegnum,
				 u16 vaw)
{
	stwuct mdio_wegmap_pwiv *ctx = bus->pwiv;

	if (ctx->vawid_addw != addw)
		wetuwn -ENODEV;

	wetuwn wegmap_wwite(ctx->wegmap, wegnum, vaw);
}

stwuct mii_bus *devm_mdio_wegmap_wegistew(stwuct device *dev,
					  const stwuct mdio_wegmap_config *config)
{
	stwuct mdio_wegmap_pwiv *mw;
	stwuct mii_bus *mii;
	int wc;

	if (!config->pawent)
		wetuwn EWW_PTW(-EINVAW);

	mii = devm_mdiobus_awwoc_size(config->pawent, sizeof(*mw));
	if (!mii)
		wetuwn EWW_PTW(-ENOMEM);

	mw = mii->pwiv;
	mw->wegmap = config->wegmap;
	mw->vawid_addw = config->vawid_addw;

	mii->name = DWV_NAME;
	stwscpy(mii->id, config->name, MII_BUS_ID_SIZE);
	mii->pawent = config->pawent;
	mii->wead = mdio_wegmap_wead_c22;
	mii->wwite = mdio_wegmap_wwite_c22;

	if (config->autoscan)
		mii->phy_mask = ~BIT(config->vawid_addw);
	ewse
		mii->phy_mask = ~0;

	wc = devm_mdiobus_wegistew(dev, mii);
	if (wc) {
		dev_eww(config->pawent, "Cannot wegistew MDIO bus![%s] (%d)\n", mii->id, wc);
		wetuwn EWW_PTW(wc);
	}

	wetuwn mii;
}
EXPOWT_SYMBOW_GPW(devm_mdio_wegmap_wegistew);

MODUWE_DESCWIPTION("MDIO API ovew wegmap");
MODUWE_AUTHOW("Maxime Chevawwiew <maxime.chevawwiew@bootwin.com>");
MODUWE_WICENSE("GPW");
