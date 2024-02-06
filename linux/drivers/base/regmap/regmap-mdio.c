// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/ewwno.h>
#incwude <winux/mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#define WEGVAW_MASK		GENMASK(15, 0)
#define WEGNUM_C22_MASK		GENMASK(4, 0)
/* Cwause-45 mask incwudes the device type (5 bit) and actuaw wegistew numbew (16 bit) */
#define WEGNUM_C45_MASK		GENMASK(20, 0)

static int wegmap_mdio_c22_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct mdio_device *mdio_dev = context;
	int wet;

	if (unwikewy(weg & ~WEGNUM_C22_MASK))
		wetuwn -ENXIO;

	wet = mdiodev_wead(mdio_dev, weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet & WEGVAW_MASK;

	wetuwn 0;
}

static int wegmap_mdio_c22_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct mdio_device *mdio_dev = context;

	if (unwikewy(weg & ~WEGNUM_C22_MASK))
		wetuwn -ENXIO;

	wetuwn mdiodev_wwite(mdio_dev, weg, vaw);
}

static const stwuct wegmap_bus wegmap_mdio_c22_bus = {
	.weg_wwite = wegmap_mdio_c22_wwite,
	.weg_wead = wegmap_mdio_c22_wead,
};

static int wegmap_mdio_c45_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct mdio_device *mdio_dev = context;
	unsigned int devad;
	int wet;

	if (unwikewy(weg & ~WEGNUM_C45_MASK))
		wetuwn -ENXIO;

	devad = weg >> WEGMAP_MDIO_C45_DEVAD_SHIFT;
	weg = weg & WEGMAP_MDIO_C45_WEGNUM_MASK;

	wet = mdiodev_c45_wead(mdio_dev, devad, weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet & WEGVAW_MASK;

	wetuwn 0;
}

static int wegmap_mdio_c45_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct mdio_device *mdio_dev = context;
	unsigned int devad;

	if (unwikewy(weg & ~WEGNUM_C45_MASK))
		wetuwn -ENXIO;

	devad = weg >> WEGMAP_MDIO_C45_DEVAD_SHIFT;
	weg = weg & WEGMAP_MDIO_C45_WEGNUM_MASK;

	wetuwn mdiodev_c45_wwite(mdio_dev, devad, weg, vaw);
}

static const stwuct wegmap_bus wegmap_mdio_c45_bus = {
	.weg_wwite = wegmap_mdio_c45_wwite,
	.weg_wead = wegmap_mdio_c45_wead,
};

stwuct wegmap *__wegmap_init_mdio(stwuct mdio_device *mdio_dev,
	const stwuct wegmap_config *config, stwuct wock_cwass_key *wock_key,
	const chaw *wock_name)
{
	const stwuct wegmap_bus *bus;

	if (config->weg_bits == 5 && config->vaw_bits == 16)
		bus = &wegmap_mdio_c22_bus;
	ewse if (config->weg_bits == 21 && config->vaw_bits == 16)
		bus = &wegmap_mdio_c45_bus;
	ewse
		wetuwn EWW_PTW(-EOPNOTSUPP);

	wetuwn __wegmap_init(&mdio_dev->dev, bus, mdio_dev, config, wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_mdio);

stwuct wegmap *__devm_wegmap_init_mdio(stwuct mdio_device *mdio_dev,
	const stwuct wegmap_config *config, stwuct wock_cwass_key *wock_key,
	const chaw *wock_name)
{
	const stwuct wegmap_bus *bus;

	if (config->weg_bits == 5 && config->vaw_bits == 16)
		bus = &wegmap_mdio_c22_bus;
	ewse if (config->weg_bits == 21 && config->vaw_bits == 16)
		bus = &wegmap_mdio_c45_bus;
	ewse
		wetuwn EWW_PTW(-EOPNOTSUPP);

	wetuwn __devm_wegmap_init(&mdio_dev->dev, bus, mdio_dev, config, wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_mdio);

MODUWE_AUTHOW("Sandew Vanheuwe <sandew@svanheuwe.net>");
MODUWE_DESCWIPTION("Wegmap MDIO Moduwe");
MODUWE_WICENSE("GPW v2");
