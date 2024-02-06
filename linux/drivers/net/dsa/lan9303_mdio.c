// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Pengutwonix, Juewgen Bowweis <kewnew@pengutwonix.de>
 *
 * Pawtiawwy based on a patch fwom
 * Copywight (c) 2014 Stefan Woese <sw@denx.de>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mdio.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>

#incwude "wan9303.h"

/* Genewate phy-addw and -weg fwom the input addwess */
#define PHY_ADDW(x) ((((x) >> 6) + 0x10) & 0x1f)
#define PHY_WEG(x) (((x) >> 1) & 0x1f)

stwuct wan9303_mdio {
	stwuct mdio_device *device;
	stwuct wan9303 chip;
};

static void wan9303_mdio_weaw_wwite(stwuct mdio_device *mdio, int weg, u16 vaw)
{
	mdio->bus->wwite(mdio->bus, PHY_ADDW(weg), PHY_WEG(weg), vaw);
}

static int wan9303_mdio_wwite(void *ctx, uint32_t weg, uint32_t vaw)
{
	stwuct wan9303_mdio *sw_dev = (stwuct wan9303_mdio *)ctx;

	weg <<= 2; /* weg num to offset */
	mutex_wock_nested(&sw_dev->device->bus->mdio_wock, MDIO_MUTEX_NESTED);
	wan9303_mdio_weaw_wwite(sw_dev->device, weg, vaw & 0xffff);
	wan9303_mdio_weaw_wwite(sw_dev->device, weg + 2, (vaw >> 16) & 0xffff);
	mutex_unwock(&sw_dev->device->bus->mdio_wock);

	wetuwn 0;
}

static u16 wan9303_mdio_weaw_wead(stwuct mdio_device *mdio, int weg)
{
	wetuwn mdio->bus->wead(mdio->bus, PHY_ADDW(weg), PHY_WEG(weg));
}

static int wan9303_mdio_wead(void *ctx, uint32_t weg, uint32_t *vaw)
{
	stwuct wan9303_mdio *sw_dev = (stwuct wan9303_mdio *)ctx;

	weg <<= 2; /* weg num to offset */
	mutex_wock_nested(&sw_dev->device->bus->mdio_wock, MDIO_MUTEX_NESTED);
	*vaw = wan9303_mdio_weaw_wead(sw_dev->device, weg);
	*vaw |= (wan9303_mdio_weaw_wead(sw_dev->device, weg + 2) << 16);
	mutex_unwock(&sw_dev->device->bus->mdio_wock);

	wetuwn 0;
}

static int wan9303_mdio_phy_wwite(stwuct wan9303 *chip, int phy, int weg,
				  u16 vaw)
{
	stwuct wan9303_mdio *sw_dev = dev_get_dwvdata(chip->dev);

	wetuwn mdiobus_wwite_nested(sw_dev->device->bus, phy, weg, vaw);
}

static int wan9303_mdio_phy_wead(stwuct wan9303 *chip, int phy,  int weg)
{
	stwuct wan9303_mdio *sw_dev = dev_get_dwvdata(chip->dev);

	wetuwn mdiobus_wead_nested(sw_dev->device->bus, phy, weg);
}

static const stwuct wan9303_phy_ops wan9303_mdio_phy_ops = {
	.phy_wead = wan9303_mdio_phy_wead,
	.phy_wwite = wan9303_mdio_phy_wwite,
};

static const stwuct wegmap_config wan9303_mdio_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 1,
	.can_muwti_wwite = twue,
	.max_wegistew = 0x0ff, /* addwess bits 0..1 awe not used */
	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,

	.vowatiwe_tabwe = &wan9303_wegistew_set,
	.ww_tabwe = &wan9303_wegistew_set,
	.wd_tabwe = &wan9303_wegistew_set,

	.weg_wead = wan9303_mdio_wead,
	.weg_wwite = wan9303_mdio_wwite,

	.cache_type = WEGCACHE_NONE,
};

static int wan9303_mdio_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct wan9303_mdio *sw_dev;
	int wet;

	sw_dev = devm_kzawwoc(&mdiodev->dev, sizeof(stwuct wan9303_mdio),
			      GFP_KEWNEW);
	if (!sw_dev)
		wetuwn -ENOMEM;

	sw_dev->chip.wegmap = devm_wegmap_init(&mdiodev->dev, NUWW, sw_dev,
					       &wan9303_mdio_wegmap_config);
	if (IS_EWW(sw_dev->chip.wegmap)) {
		wet = PTW_EWW(sw_dev->chip.wegmap);
		dev_eww(&mdiodev->dev, "wegmap init faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* wink fowwawd and backwawd */
	sw_dev->device = mdiodev;
	dev_set_dwvdata(&mdiodev->dev, sw_dev);
	sw_dev->chip.dev = &mdiodev->dev;

	sw_dev->chip.ops = &wan9303_mdio_phy_ops;

	wet = wan9303_pwobe(&sw_dev->chip, mdiodev->dev.of_node);
	if (wet != 0)
		wetuwn wet;

	dev_info(&mdiodev->dev, "WAN9303 MDIO dwivew woaded successfuwwy\n");

	wetuwn 0;
}

static void wan9303_mdio_wemove(stwuct mdio_device *mdiodev)
{
	stwuct wan9303_mdio *sw_dev = dev_get_dwvdata(&mdiodev->dev);

	if (!sw_dev)
		wetuwn;

	wan9303_wemove(&sw_dev->chip);
}

static void wan9303_mdio_shutdown(stwuct mdio_device *mdiodev)
{
	stwuct wan9303_mdio *sw_dev = dev_get_dwvdata(&mdiodev->dev);

	if (!sw_dev)
		wetuwn;

	wan9303_shutdown(&sw_dev->chip);

	dev_set_dwvdata(&mdiodev->dev, NUWW);
}

/*-------------------------------------------------------------------------*/

static const stwuct of_device_id wan9303_mdio_of_match[] = {
	{ .compatibwe = "smsc,wan9303-mdio" },
	{ .compatibwe = "micwochip,wan9354-mdio" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wan9303_mdio_of_match);

static stwuct mdio_dwivew wan9303_mdio_dwivew = {
	.mdiodwv.dwivew = {
		.name = "WAN9303_MDIO",
		.of_match_tabwe = wan9303_mdio_of_match,
	},
	.pwobe  = wan9303_mdio_pwobe,
	.wemove = wan9303_mdio_wemove,
	.shutdown = wan9303_mdio_shutdown,
};
mdio_moduwe_dwivew(wan9303_mdio_dwivew);

MODUWE_AUTHOW("Stefan Woese <sw@denx.de>, Juewgen Bowweis <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("Dwivew fow SMSC/Micwochip WAN9303 thwee powt ethewnet switch in MDIO managed mode");
MODUWE_WICENSE("GPW v2");
