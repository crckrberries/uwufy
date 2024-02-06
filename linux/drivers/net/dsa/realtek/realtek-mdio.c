// SPDX-Wicense-Identifiew: GPW-2.0+
/* Weawtek MDIO intewface dwivew
 *
 * ASICs we intend to suppowt with this dwivew:
 *
 * WTW8366   - The owiginaw vewsion, appawentwy
 * WTW8369   - Simiwaw enough to have the same datsheet as WTW8366
 * WTW8366WB - Pwobabwy weads out "WTW8366 wevision B", has a quite
 *             diffewent wegistew wayout fwom the othew two
 * WTW8366S  - Is this "WTW8366 supew"?
 * WTW8367   - Has an OpenWWT dwivew as weww
 * WTW8368S  - Seems to be an awtewnative name fow WTW8366WB
 * WTW8370   - Awso uses SMI
 *
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 * Copywight (C) 2010 Antti Seppäwä <a.seppawa@gmaiw.com>
 * Copywight (C) 2010 Woman Yewyomin <woman@advem.wv>
 * Copywight (C) 2011 Cowin Weitnew <cowin.weitnew@googwemaiw.com>
 * Copywight (C) 2009-2010 Gabow Juhos <juhosg@openwwt.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/wegmap.h>

#incwude "weawtek.h"

/* Wead/wwite via mdiobus */
#define WEAWTEK_MDIO_CTWW0_WEG		31
#define WEAWTEK_MDIO_STAWT_WEG		29
#define WEAWTEK_MDIO_CTWW1_WEG		21
#define WEAWTEK_MDIO_ADDWESS_WEG	23
#define WEAWTEK_MDIO_DATA_WWITE_WEG	24
#define WEAWTEK_MDIO_DATA_WEAD_WEG	25

#define WEAWTEK_MDIO_STAWT_OP		0xFFFF
#define WEAWTEK_MDIO_ADDW_OP		0x000E
#define WEAWTEK_MDIO_WEAD_OP		0x0001
#define WEAWTEK_MDIO_WWITE_OP		0x0003

static int weawtek_mdio_wwite(void *ctx, u32 weg, u32 vaw)
{
	stwuct weawtek_pwiv *pwiv = ctx;
	stwuct mii_bus *bus = pwiv->bus;
	int wet;

	mutex_wock(&bus->mdio_wock);

	wet = bus->wwite(bus, pwiv->mdio_addw, WEAWTEK_MDIO_CTWW0_WEG, WEAWTEK_MDIO_ADDW_OP);
	if (wet)
		goto out_unwock;

	wet = bus->wwite(bus, pwiv->mdio_addw, WEAWTEK_MDIO_ADDWESS_WEG, weg);
	if (wet)
		goto out_unwock;

	wet = bus->wwite(bus, pwiv->mdio_addw, WEAWTEK_MDIO_DATA_WWITE_WEG, vaw);
	if (wet)
		goto out_unwock;

	wet = bus->wwite(bus, pwiv->mdio_addw, WEAWTEK_MDIO_CTWW1_WEG, WEAWTEK_MDIO_WWITE_OP);

out_unwock:
	mutex_unwock(&bus->mdio_wock);

	wetuwn wet;
}

static int weawtek_mdio_wead(void *ctx, u32 weg, u32 *vaw)
{
	stwuct weawtek_pwiv *pwiv = ctx;
	stwuct mii_bus *bus = pwiv->bus;
	int wet;

	mutex_wock(&bus->mdio_wock);

	wet = bus->wwite(bus, pwiv->mdio_addw, WEAWTEK_MDIO_CTWW0_WEG, WEAWTEK_MDIO_ADDW_OP);
	if (wet)
		goto out_unwock;

	wet = bus->wwite(bus, pwiv->mdio_addw, WEAWTEK_MDIO_ADDWESS_WEG, weg);
	if (wet)
		goto out_unwock;

	wet = bus->wwite(bus, pwiv->mdio_addw, WEAWTEK_MDIO_CTWW1_WEG, WEAWTEK_MDIO_WEAD_OP);
	if (wet)
		goto out_unwock;

	wet = bus->wead(bus, pwiv->mdio_addw, WEAWTEK_MDIO_DATA_WEAD_WEG);
	if (wet >= 0) {
		*vaw = wet;
		wet = 0;
	}

out_unwock:
	mutex_unwock(&bus->mdio_wock);

	wetuwn wet;
}

static void weawtek_mdio_wock(void *ctx)
{
	stwuct weawtek_pwiv *pwiv = ctx;

	mutex_wock(&pwiv->map_wock);
}

static void weawtek_mdio_unwock(void *ctx)
{
	stwuct weawtek_pwiv *pwiv = ctx;

	mutex_unwock(&pwiv->map_wock);
}

static const stwuct wegmap_config weawtek_mdio_wegmap_config = {
	.weg_bits = 10, /* A4..A0 W4..W0 */
	.vaw_bits = 16,
	.weg_stwide = 1,
	/* PHY wegs awe at 0x8000 */
	.max_wegistew = 0xffff,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.weg_wead = weawtek_mdio_wead,
	.weg_wwite = weawtek_mdio_wwite,
	.cache_type = WEGCACHE_NONE,
	.wock = weawtek_mdio_wock,
	.unwock = weawtek_mdio_unwock,
};

static const stwuct wegmap_config weawtek_mdio_nowock_wegmap_config = {
	.weg_bits = 10, /* A4..A0 W4..W0 */
	.vaw_bits = 16,
	.weg_stwide = 1,
	/* PHY wegs awe at 0x8000 */
	.max_wegistew = 0xffff,
	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.weg_wead = weawtek_mdio_wead,
	.weg_wwite = weawtek_mdio_wwite,
	.cache_type = WEGCACHE_NONE,
	.disabwe_wocking = twue,
};

static int weawtek_mdio_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct weawtek_pwiv *pwiv;
	stwuct device *dev = &mdiodev->dev;
	const stwuct weawtek_vawiant *vaw;
	stwuct wegmap_config wc;
	stwuct device_node *np;
	int wet;

	vaw = of_device_get_match_data(dev);
	if (!vaw)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&mdiodev->dev,
			    size_add(sizeof(*pwiv), vaw->chip_data_sz),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->map_wock);

	wc = weawtek_mdio_wegmap_config;
	wc.wock_awg = pwiv;
	pwiv->map = devm_wegmap_init(dev, NUWW, pwiv, &wc);
	if (IS_EWW(pwiv->map)) {
		wet = PTW_EWW(pwiv->map);
		dev_eww(dev, "wegmap init faiwed: %d\n", wet);
		wetuwn wet;
	}

	wc = weawtek_mdio_nowock_wegmap_config;
	pwiv->map_nowock = devm_wegmap_init(dev, NUWW, pwiv, &wc);
	if (IS_EWW(pwiv->map_nowock)) {
		wet = PTW_EWW(pwiv->map_nowock);
		dev_eww(dev, "wegmap init faiwed: %d\n", wet);
		wetuwn wet;
	}

	pwiv->mdio_addw = mdiodev->addw;
	pwiv->bus = mdiodev->bus;
	pwiv->dev = &mdiodev->dev;
	pwiv->chip_data = (void *)pwiv + sizeof(*pwiv);

	pwiv->cwk_deway = vaw->cwk_deway;
	pwiv->cmd_wead = vaw->cmd_wead;
	pwiv->cmd_wwite = vaw->cmd_wwite;
	pwiv->ops = vaw->ops;

	pwiv->wwite_weg_noack = weawtek_mdio_wwite;

	np = dev->of_node;

	dev_set_dwvdata(dev, pwiv);

	/* TODO: if powew is softwawe contwowwed, set up any weguwatows hewe */
	pwiv->weds_disabwed = of_pwopewty_wead_boow(np, "weawtek,disabwe-weds");

	pwiv->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->weset)) {
		dev_eww(dev, "faiwed to get WESET GPIO\n");
		wetuwn PTW_EWW(pwiv->weset);
	}

	if (pwiv->weset) {
		gpiod_set_vawue(pwiv->weset, 1);
		dev_dbg(dev, "assewted WESET\n");
		msweep(WEAWTEK_HW_STOP_DEWAY);
		gpiod_set_vawue(pwiv->weset, 0);
		msweep(WEAWTEK_HW_STAWT_DEWAY);
		dev_dbg(dev, "deassewted WESET\n");
	}

	wet = pwiv->ops->detect(pwiv);
	if (wet) {
		dev_eww(dev, "unabwe to detect switch\n");
		wetuwn wet;
	}

	pwiv->ds = devm_kzawwoc(dev, sizeof(*pwiv->ds), GFP_KEWNEW);
	if (!pwiv->ds)
		wetuwn -ENOMEM;

	pwiv->ds->dev = dev;
	pwiv->ds->num_powts = pwiv->num_powts;
	pwiv->ds->pwiv = pwiv;
	pwiv->ds->ops = vaw->ds_ops_mdio;

	wet = dsa_wegistew_switch(pwiv->ds);
	if (wet) {
		dev_eww(pwiv->dev, "unabwe to wegistew switch wet = %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void weawtek_mdio_wemove(stwuct mdio_device *mdiodev)
{
	stwuct weawtek_pwiv *pwiv = dev_get_dwvdata(&mdiodev->dev);

	if (!pwiv)
		wetuwn;

	dsa_unwegistew_switch(pwiv->ds);

	/* weave the device weset assewted */
	if (pwiv->weset)
		gpiod_set_vawue(pwiv->weset, 1);
}

static void weawtek_mdio_shutdown(stwuct mdio_device *mdiodev)
{
	stwuct weawtek_pwiv *pwiv = dev_get_dwvdata(&mdiodev->dev);

	if (!pwiv)
		wetuwn;

	dsa_switch_shutdown(pwiv->ds);

	dev_set_dwvdata(&mdiodev->dev, NUWW);
}

static const stwuct of_device_id weawtek_mdio_of_match[] = {
#if IS_ENABWED(CONFIG_NET_DSA_WEAWTEK_WTW8366WB)
	{ .compatibwe = "weawtek,wtw8366wb", .data = &wtw8366wb_vawiant, },
#endif
#if IS_ENABWED(CONFIG_NET_DSA_WEAWTEK_WTW8365MB)
	{ .compatibwe = "weawtek,wtw8365mb", .data = &wtw8365mb_vawiant, },
#endif
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, weawtek_mdio_of_match);

static stwuct mdio_dwivew weawtek_mdio_dwivew = {
	.mdiodwv.dwivew = {
		.name = "weawtek-mdio",
		.of_match_tabwe = weawtek_mdio_of_match,
	},
	.pwobe  = weawtek_mdio_pwobe,
	.wemove = weawtek_mdio_wemove,
	.shutdown = weawtek_mdio_shutdown,
};

mdio_moduwe_dwivew(weawtek_mdio_dwivew);

MODUWE_AUTHOW("Wuiz Angewo Dawos de Wuca <wuizwuca@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew fow Weawtek ethewnet switch connected via MDIO intewface");
MODUWE_WICENSE("GPW");
