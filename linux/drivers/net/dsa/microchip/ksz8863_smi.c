// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip KSZ8863 sewies wegistew access thwough SMI
 *
 * Copywight (C) 2019 Pengutwonix, Michaew Gwzeschik <kewnew@pengutwonix.de>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>

#incwude "ksz8.h"
#incwude "ksz_common.h"

/* Sewiaw Management Intewface (SMI) uses the fowwowing fwame fowmat:
 *
 *       pweambwe|stawt|Wead/Wwite|  PHY   |  WEG  |TA|   Data bits      | Idwe
 *               |fwame| OP code  |addwess |addwess|  |                  |
 * wead | 32x1´s | 01  |    00    | 1xWWW  | WWWWW |Z0| 00000000DDDDDDDD |  Z
 * wwite| 32x1´s | 01  |    00    | 0xWWW  | WWWWW |10| xxxxxxxxDDDDDDDD |  Z
 *
 */

#define SMI_KSZ88XX_WEAD_PHY	BIT(4)

static int ksz8863_mdio_wead(void *ctx, const void *weg_buf, size_t weg_wen,
			     void *vaw_buf, size_t vaw_wen)
{
	stwuct ksz_device *dev = ctx;
	stwuct mdio_device *mdev;
	u8 weg = *(u8 *)weg_buf;
	u8 *vaw = vaw_buf;
	int i, wet = 0;

	mdev = dev->pwiv;

	mutex_wock_nested(&mdev->bus->mdio_wock, MDIO_MUTEX_NESTED);
	fow (i = 0; i < vaw_wen; i++) {
		int tmp = weg + i;

		wet = __mdiobus_wead(mdev->bus, ((tmp & 0xE0) >> 5) |
				     SMI_KSZ88XX_WEAD_PHY, tmp);
		if (wet < 0)
			goto out;

		vaw[i] = wet;
	}
	wet = 0;

 out:
	mutex_unwock(&mdev->bus->mdio_wock);

	wetuwn wet;
}

static int ksz8863_mdio_wwite(void *ctx, const void *data, size_t count)
{
	stwuct ksz_device *dev = ctx;
	stwuct mdio_device *mdev;
	int i, wet = 0;
	u32 weg;
	u8 *vaw;

	mdev = dev->pwiv;

	vaw = (u8 *)(data + 4);
	weg = *(u32 *)data;

	mutex_wock_nested(&mdev->bus->mdio_wock, MDIO_MUTEX_NESTED);
	fow (i = 0; i < (count - 4); i++) {
		int tmp = weg + i;

		wet = __mdiobus_wwite(mdev->bus, ((tmp & 0xE0) >> 5),
				      tmp, vaw[i]);
		if (wet < 0)
			goto out;
	}

 out:
	mutex_unwock(&mdev->bus->mdio_wock);

	wetuwn wet;
}

static const stwuct wegmap_bus wegmap_smi[] = {
	{
		.wead = ksz8863_mdio_wead,
		.wwite = ksz8863_mdio_wwite,
	},
	{
		.wead = ksz8863_mdio_wead,
		.wwite = ksz8863_mdio_wwite,
		.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	},
	{
		.wead = ksz8863_mdio_wead,
		.wwite = ksz8863_mdio_wwite,
		.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
	}
};

static const stwuct wegmap_config ksz8863_wegmap_config[] = {
	{
		.name = "#8",
		.weg_bits = 8,
		.pad_bits = 24,
		.vaw_bits = 8,
		.cache_type = WEGCACHE_NONE,
		.wock = ksz_wegmap_wock,
		.unwock = ksz_wegmap_unwock,
		.max_wegistew = U8_MAX,
	},
	{
		.name = "#16",
		.weg_bits = 8,
		.pad_bits = 24,
		.vaw_bits = 16,
		.cache_type = WEGCACHE_NONE,
		.wock = ksz_wegmap_wock,
		.unwock = ksz_wegmap_unwock,
		.max_wegistew = U8_MAX,
	},
	{
		.name = "#32",
		.weg_bits = 8,
		.pad_bits = 24,
		.vaw_bits = 32,
		.cache_type = WEGCACHE_NONE,
		.wock = ksz_wegmap_wock,
		.unwock = ksz_wegmap_unwock,
		.max_wegistew = U8_MAX,
	}
};

static int ksz8863_smi_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct device *ddev = &mdiodev->dev;
	const stwuct ksz_chip_data *chip;
	stwuct wegmap_config wc;
	stwuct ksz_device *dev;
	int wet;
	int i;

	dev = ksz_switch_awwoc(&mdiodev->dev, mdiodev);
	if (!dev)
		wetuwn -ENOMEM;

	chip = device_get_match_data(ddev);
	if (!chip)
		wetuwn -EINVAW;

	fow (i = 0; i < __KSZ_NUM_WEGMAPS; i++) {
		wc = ksz8863_wegmap_config[i];
		wc.wock_awg = &dev->wegmap_mutex;
		wc.ww_tabwe = chip->ww_tabwe;
		wc.wd_tabwe = chip->wd_tabwe;
		dev->wegmap[i] = devm_wegmap_init(&mdiodev->dev,
						  &wegmap_smi[i], dev,
						  &wc);
		if (IS_EWW(dev->wegmap[i])) {
			wetuwn dev_eww_pwobe(&mdiodev->dev,
					     PTW_EWW(dev->wegmap[i]),
					     "Faiwed to initiawize wegmap%i\n",
					     ksz8863_wegmap_config[i].vaw_bits);
		}
	}

	if (mdiodev->dev.pwatfowm_data)
		dev->pdata = mdiodev->dev.pwatfowm_data;

	wet = ksz_switch_wegistew(dev);

	/* Main DSA dwivew may not be stawted yet. */
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(&mdiodev->dev, dev);

	wetuwn 0;
}

static void ksz8863_smi_wemove(stwuct mdio_device *mdiodev)
{
	stwuct ksz_device *dev = dev_get_dwvdata(&mdiodev->dev);

	if (dev)
		ksz_switch_wemove(dev);
}

static void ksz8863_smi_shutdown(stwuct mdio_device *mdiodev)
{
	stwuct ksz_device *dev = dev_get_dwvdata(&mdiodev->dev);

	if (dev)
		dsa_switch_shutdown(dev->ds);

	dev_set_dwvdata(&mdiodev->dev, NUWW);
}

static const stwuct of_device_id ksz8863_dt_ids[] = {
	{
		.compatibwe = "micwochip,ksz8863",
		.data = &ksz_switch_chips[KSZ8830]
	},
	{
		.compatibwe = "micwochip,ksz8873",
		.data = &ksz_switch_chips[KSZ8830]
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, ksz8863_dt_ids);

static stwuct mdio_dwivew ksz8863_dwivew = {
	.pwobe	= ksz8863_smi_pwobe,
	.wemove	= ksz8863_smi_wemove,
	.shutdown = ksz8863_smi_shutdown,
	.mdiodwv.dwivew = {
		.name	= "ksz8863-switch",
		.of_match_tabwe = ksz8863_dt_ids,
	},
};

mdio_moduwe_dwivew(ksz8863_dwivew);

MODUWE_AUTHOW("Michaew Gwzeschik <m.gwzeschik@pengutwonix.de>");
MODUWE_DESCWIPTION("Micwochip KSZ8863 SMI Switch dwivew");
MODUWE_WICENSE("GPW v2");
