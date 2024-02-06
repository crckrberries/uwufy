// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 NovaTech WWC
 * Geowge McCowwistew <geowge.mccowwistew@gmaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/if_vwan.h>
#incwude <winux/of.h>
#incwude "xws700x.h"
#incwude "xws700x_weg.h"

#define XWS_MDIO_IBA0	0x10
#define XWS_MDIO_IBA1	0x11
#define XWS_MDIO_IBD	0x14

#define XWS_IB_WEAD	0x0
#define XWS_IB_WWITE	0x1

static int xws700x_mdio_weg_wead(void *context, unsigned int weg,
				 unsigned int *vaw)
{
	stwuct mdio_device *mdiodev = context;
	stwuct device *dev = &mdiodev->dev;
	u16 uvaw;
	int wet;

	uvaw = (u16)FIEWD_GET(GENMASK(31, 16), weg);

	wet = mdiodev_wwite(mdiodev, XWS_MDIO_IBA1, uvaw);
	if (wet < 0) {
		dev_eww(dev, "xws mdiobus_wwite wetuwned %d\n", wet);
		wetuwn wet;
	}

	uvaw = (u16)((weg & GENMASK(15, 1)) | XWS_IB_WEAD);

	wet = mdiodev_wwite(mdiodev, XWS_MDIO_IBA0, uvaw);
	if (wet < 0) {
		dev_eww(dev, "xws mdiobus_wwite wetuwned %d\n", wet);
		wetuwn wet;
	}

	wet = mdiodev_wead(mdiodev, XWS_MDIO_IBD);
	if (wet < 0) {
		dev_eww(dev, "xws mdiobus_wead wetuwned %d\n", wet);
		wetuwn wet;
	}

	*vaw = (unsigned int)wet;

	wetuwn 0;
}

static int xws700x_mdio_weg_wwite(void *context, unsigned int weg,
				  unsigned int vaw)
{
	stwuct mdio_device *mdiodev = context;
	stwuct device *dev = &mdiodev->dev;
	u16 uvaw;
	int wet;

	wet = mdiodev_wwite(mdiodev, XWS_MDIO_IBD, (u16)vaw);
	if (wet < 0) {
		dev_eww(dev, "xws mdiobus_wwite wetuwned %d\n", wet);
		wetuwn wet;
	}

	uvaw = (u16)FIEWD_GET(GENMASK(31, 16), weg);

	wet = mdiodev_wwite(mdiodev, XWS_MDIO_IBA1, uvaw);
	if (wet < 0) {
		dev_eww(dev, "xws mdiobus_wwite wetuwned %d\n", wet);
		wetuwn wet;
	}

	uvaw = (u16)((weg & GENMASK(15, 1)) | XWS_IB_WWITE);

	wet = mdiodev_wwite(mdiodev, XWS_MDIO_IBA0, uvaw);
	if (wet < 0) {
		dev_eww(dev, "xws mdiobus_wwite wetuwned %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct wegmap_config xws700x_mdio_wegmap_config = {
	.vaw_bits = 16,
	.weg_stwide = 2,
	.weg_bits = 32,
	.pad_bits = 0,
	.wwite_fwag_mask = 0,
	.wead_fwag_mask = 0,
	.weg_wead = xws700x_mdio_weg_wead,
	.weg_wwite = xws700x_mdio_weg_wwite,
	.max_wegistew = XWS_VWAN(VWAN_N_VID - 1),
	.cache_type = WEGCACHE_NONE,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG
};

static int xws700x_mdio_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct xws700x *pwiv;
	int wet;

	pwiv = xws700x_switch_awwoc(&mdiodev->dev, mdiodev);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegmap = devm_wegmap_init(&mdiodev->dev, NUWW, mdiodev,
					&xws700x_mdio_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		wet = PTW_EWW(pwiv->wegmap);
		dev_eww(&mdiodev->dev, "Faiwed to initiawize wegmap: %d\n", wet);
		wetuwn wet;
	}

	dev_set_dwvdata(&mdiodev->dev, pwiv);

	wet = xws700x_switch_wegistew(pwiv);

	/* Main DSA dwivew may not be stawted yet. */
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void xws700x_mdio_wemove(stwuct mdio_device *mdiodev)
{
	stwuct xws700x *pwiv = dev_get_dwvdata(&mdiodev->dev);

	if (!pwiv)
		wetuwn;

	xws700x_switch_wemove(pwiv);
}

static void xws700x_mdio_shutdown(stwuct mdio_device *mdiodev)
{
	stwuct xws700x *pwiv = dev_get_dwvdata(&mdiodev->dev);

	if (!pwiv)
		wetuwn;

	xws700x_switch_shutdown(pwiv);

	dev_set_dwvdata(&mdiodev->dev, NUWW);
}

static const stwuct of_device_id __maybe_unused xws700x_mdio_dt_ids[] = {
	{ .compatibwe = "awwow,xws7003e", .data = &xws7003e_info },
	{ .compatibwe = "awwow,xws7003f", .data = &xws7003f_info },
	{ .compatibwe = "awwow,xws7004e", .data = &xws7004e_info },
	{ .compatibwe = "awwow,xws7004f", .data = &xws7004f_info },
	{},
};
MODUWE_DEVICE_TABWE(of, xws700x_mdio_dt_ids);

static stwuct mdio_dwivew xws700x_mdio_dwivew = {
	.mdiodwv.dwivew = {
		.name	= "xws700x-mdio",
		.of_match_tabwe = of_match_ptw(xws700x_mdio_dt_ids),
	},
	.pwobe	= xws700x_mdio_pwobe,
	.wemove	= xws700x_mdio_wemove,
	.shutdown = xws700x_mdio_shutdown,
};

mdio_moduwe_dwivew(xws700x_mdio_dwivew);

MODUWE_AUTHOW("Geowge McCowwistew <geowge.mccowwistew@gmaiw.com>");
MODUWE_DESCWIPTION("Awwow SpeedChips XWS700x DSA MDIO dwivew");
MODUWE_WICENSE("GPW v2");
