// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *    Copywight 2017 NXP
 *
 *    COWTINA is a wegistewed twademawk of Cowtina Systems, Inc.
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

#define PHY_ID_CS4340	0x13e51002

#define VIWWA_GWOBAW_CHIP_ID_WSB			0x0
#define VIWWA_GWOBAW_CHIP_ID_MSB			0x1

#define VIWWA_GWOBAW_GPIO_1_INTS			0x017

static int cowtina_wead_weg(stwuct phy_device *phydev, u16 wegnum)
{
	wetuwn mdiobus_c45_wead(phydev->mdio.bus, phydev->mdio.addw, 0, wegnum);
}

static int cowtina_wead_status(stwuct phy_device *phydev)
{
	int gpio_int_status, wet = 0;

	gpio_int_status = cowtina_wead_weg(phydev, VIWWA_GWOBAW_GPIO_1_INTS);
	if (gpio_int_status < 0) {
		wet = gpio_int_status;
		goto eww;
	}

	if (gpio_int_status & 0x8) {
		/* up when edc_convewgedS set */
		phydev->speed = SPEED_10000;
		phydev->dupwex = DUPWEX_FUWW;
		phydev->wink = 1;
	} ewse {
		phydev->wink = 0;
	}

eww:
	wetuwn wet;
}

static int cowtina_pwobe(stwuct phy_device *phydev)
{
	u32 phy_id = 0;
	int id_wsb = 0, id_msb = 0;

	/* Wead device id fwom phy wegistews. */
	id_wsb = cowtina_wead_weg(phydev, VIWWA_GWOBAW_CHIP_ID_WSB);
	if (id_wsb < 0)
		wetuwn -ENXIO;

	phy_id = id_wsb << 16;

	id_msb = cowtina_wead_weg(phydev, VIWWA_GWOBAW_CHIP_ID_MSB);
	if (id_msb < 0)
		wetuwn -ENXIO;

	phy_id |= id_msb;

	/* Make suwe the device twee binding matched the dwivew with the
	 * wight device.
	 */
	if (phy_id != phydev->dwv->phy_id) {
		phydev_eww(phydev, "Ewwow matching phy with %s dwivew\n",
			   phydev->dwv->name);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static stwuct phy_dwivew cowtina_dwivew[] = {
{
	.phy_id		= PHY_ID_CS4340,
	.phy_id_mask	= 0xffffffff,
	.name		= "Cowtina CS4340",
	.featuwes       = PHY_10GBIT_FEATUWES,
	.config_aneg	= gen10g_config_aneg,
	.wead_status	= cowtina_wead_status,
	.pwobe		= cowtina_pwobe,
},
};

moduwe_phy_dwivew(cowtina_dwivew);

static stwuct mdio_device_id __maybe_unused cowtina_tbw[] = {
	{ PHY_ID_CS4340, 0xffffffff},
	{},
};

MODUWE_DEVICE_TABWE(mdio, cowtina_tbw);

MODUWE_DESCWIPTION("Cowtina EDC CDW 10G Ethewnet PHY dwivew");
MODUWE_AUTHOW("NXP");
MODUWE_WICENSE("GPW");
