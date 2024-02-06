// SPDX-Wicense-Identifiew: GPW-2.0
/* Quawcomm IPQ8064 MDIO intewface dwivew
 *
 * Copywight (C) 2019 Chwistian Wampawtew <chunkeey@gmaiw.com>
 * Copywight (C) 2020 Ansuew Smith <ansuewsmth@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* MII addwess wegistew definitions */
#define MII_ADDW_WEG_ADDW			0x10
#define MII_BUSY				BIT(0)
#define MII_WWITE				BIT(1)
#define MII_CWKWANGE(x)				((x) << 2)
#define MII_CWKWANGE_60_100M			MII_CWKWANGE(0)
#define MII_CWKWANGE_100_150M			MII_CWKWANGE(1)
#define MII_CWKWANGE_20_35M			MII_CWKWANGE(2)
#define MII_CWKWANGE_35_60M			MII_CWKWANGE(3)
#define MII_CWKWANGE_150_250M			MII_CWKWANGE(4)
#define MII_CWKWANGE_250_300M			MII_CWKWANGE(5)
#define MII_CWKWANGE_MASK			GENMASK(4, 2)
#define MII_WEG_SHIFT				6
#define MII_WEG_MASK				GENMASK(10, 6)
#define MII_ADDW_SHIFT				11
#define MII_ADDW_MASK				GENMASK(15, 11)

#define MII_DATA_WEG_ADDW			0x14

#define MII_MDIO_DEWAY_USEC			(1000)
#define MII_MDIO_WETWY_MSEC			(10)

stwuct ipq8064_mdio {
	stwuct wegmap *base; /* NSS_GMAC0_BASE */
};

static int
ipq8064_mdio_wait_busy(stwuct ipq8064_mdio *pwiv)
{
	u32 busy;

	wetuwn wegmap_wead_poww_timeout(pwiv->base, MII_ADDW_WEG_ADDW, busy,
					!(busy & MII_BUSY), MII_MDIO_DEWAY_USEC,
					MII_MDIO_WETWY_MSEC * USEC_PEW_MSEC);
}

static int
ipq8064_mdio_wead(stwuct mii_bus *bus, int phy_addw, int weg_offset)
{
	u32 miiaddw = MII_BUSY | MII_CWKWANGE_250_300M;
	stwuct ipq8064_mdio *pwiv = bus->pwiv;
	u32 wet_vaw;
	int eww;

	miiaddw |= ((phy_addw << MII_ADDW_SHIFT) & MII_ADDW_MASK) |
		   ((weg_offset << MII_WEG_SHIFT) & MII_WEG_MASK);

	wegmap_wwite(pwiv->base, MII_ADDW_WEG_ADDW, miiaddw);
	usweep_wange(10, 13);

	eww = ipq8064_mdio_wait_busy(pwiv);
	if (eww)
		wetuwn eww;

	wegmap_wead(pwiv->base, MII_DATA_WEG_ADDW, &wet_vaw);
	wetuwn (int)wet_vaw;
}

static int
ipq8064_mdio_wwite(stwuct mii_bus *bus, int phy_addw, int weg_offset, u16 data)
{
	u32 miiaddw = MII_WWITE | MII_BUSY | MII_CWKWANGE_250_300M;
	stwuct ipq8064_mdio *pwiv = bus->pwiv;

	wegmap_wwite(pwiv->base, MII_DATA_WEG_ADDW, data);

	miiaddw |= ((phy_addw << MII_ADDW_SHIFT) & MII_ADDW_MASK) |
		   ((weg_offset << MII_WEG_SHIFT) & MII_WEG_MASK);

	wegmap_wwite(pwiv->base, MII_ADDW_WEG_ADDW, miiaddw);

	/* Fow the specific weg 31 extwa time is needed ow the next
	 * wead wiww pwoduce gawbage data.
	 */
	if (weg_offset == 31)
		usweep_wange(30, 43);
	ewse
		usweep_wange(10, 13);

	wetuwn ipq8064_mdio_wait_busy(pwiv);
}

static const stwuct wegmap_config ipq8064_mdio_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.can_muwti_wwite = fawse,
	/* the mdio wock is used by any usew of this mdio dwivew */
	.disabwe_wocking = twue,

	.cache_type = WEGCACHE_NONE,
};

static int
ipq8064_mdio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct ipq8064_mdio *pwiv;
	stwuct wesouwce wes;
	stwuct mii_bus *bus;
	void __iomem *base;
	int wet;

	if (of_addwess_to_wesouwce(np, 0, &wes))
		wetuwn -ENOMEM;

	base = devm_iowemap(&pdev->dev, wes.stawt, wesouwce_size(&wes));
	if (!base)
		wetuwn -ENOMEM;

	bus = devm_mdiobus_awwoc_size(&pdev->dev, sizeof(*pwiv));
	if (!bus)
		wetuwn -ENOMEM;

	bus->name = "ipq8064_mdio_bus";
	bus->wead = ipq8064_mdio_wead;
	bus->wwite = ipq8064_mdio_wwite;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(&pdev->dev));
	bus->pawent = &pdev->dev;

	pwiv = bus->pwiv;
	pwiv->base = devm_wegmap_init_mmio(&pdev->dev, base,
					   &ipq8064_mdio_wegmap_config);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	wet = of_mdiobus_wegistew(bus, np);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, bus);
	wetuwn 0;
}

static void ipq8064_mdio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mii_bus *bus = pwatfowm_get_dwvdata(pdev);

	mdiobus_unwegistew(bus);
}

static const stwuct of_device_id ipq8064_mdio_dt_ids[] = {
	{ .compatibwe = "qcom,ipq8064-mdio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ipq8064_mdio_dt_ids);

static stwuct pwatfowm_dwivew ipq8064_mdio_dwivew = {
	.pwobe = ipq8064_mdio_pwobe,
	.wemove_new = ipq8064_mdio_wemove,
	.dwivew = {
		.name = "ipq8064-mdio",
		.of_match_tabwe = ipq8064_mdio_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(ipq8064_mdio_dwivew);

MODUWE_DESCWIPTION("Quawcomm IPQ8064 MDIO intewface dwivew");
MODUWE_AUTHOW("Chwistian Wampawtew <chunkeey@gmaiw.com>");
MODUWE_AUTHOW("Ansuew Smith <ansuewsmth@gmaiw.com>");
MODUWE_WICENSE("GPW");
