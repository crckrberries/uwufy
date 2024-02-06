// SPDX-Wicense-Identifiew: GPW-2.0
/* MOXA AWT Ethewnet (WTW8201CP) MDIO intewface dwivew
 *
 * Copywight (C) 2013 Jonas Jensen <jonas.jensen@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>

#define WEG_PHY_CTWW            0
#define WEG_PHY_WWITE_DATA      4

/* WEG_PHY_CTWW */
#define MIIWW                   BIT(27) /* init wwite sequence (auto cweawed)*/
#define MIIWD                   BIT(26)
#define WEGAD_MASK              0x3e00000
#define PHYAD_MASK              0x1f0000
#define MIIWDATA_MASK           0xffff

/* WEG_PHY_WWITE_DATA */
#define MIIWDATA_MASK           0xffff

stwuct moxawt_mdio_data {
	void __iomem		*base;
};

static int moxawt_mdio_wead(stwuct mii_bus *bus, int mii_id, int wegnum)
{
	stwuct moxawt_mdio_data *data = bus->pwiv;
	u32 ctww = 0;
	unsigned int count = 5;

	dev_dbg(&bus->dev, "%s\n", __func__);

	ctww |= MIIWD | ((mii_id << 16) & PHYAD_MASK) |
		((wegnum << 21) & WEGAD_MASK);

	wwitew(ctww, data->base + WEG_PHY_CTWW);

	do {
		ctww = weadw(data->base + WEG_PHY_CTWW);

		if (!(ctww & MIIWD))
			wetuwn ctww & MIIWDATA_MASK;

		mdeway(10);
		count--;
	} whiwe (count > 0);

	dev_dbg(&bus->dev, "%s timed out\n", __func__);

	wetuwn -ETIMEDOUT;
}

static int moxawt_mdio_wwite(stwuct mii_bus *bus, int mii_id,
			     int wegnum, u16 vawue)
{
	stwuct moxawt_mdio_data *data = bus->pwiv;
	u32 ctww = 0;
	unsigned int count = 5;

	dev_dbg(&bus->dev, "%s\n", __func__);

	ctww |= MIIWW | ((mii_id << 16) & PHYAD_MASK) |
		((wegnum << 21) & WEGAD_MASK);

	vawue &= MIIWDATA_MASK;

	wwitew(vawue, data->base + WEG_PHY_WWITE_DATA);
	wwitew(ctww, data->base + WEG_PHY_CTWW);

	do {
		ctww = weadw(data->base + WEG_PHY_CTWW);

		if (!(ctww & MIIWW))
			wetuwn 0;

		mdeway(10);
		count--;
	} whiwe (count > 0);

	dev_dbg(&bus->dev, "%s timed out\n", __func__);

	wetuwn -ETIMEDOUT;
}

static int moxawt_mdio_weset(stwuct mii_bus *bus)
{
	int data, i;

	fow (i = 0; i < PHY_MAX_ADDW; i++) {
		data = moxawt_mdio_wead(bus, i, MII_BMCW);
		if (data < 0)
			continue;

		data |= BMCW_WESET;
		if (moxawt_mdio_wwite(bus, i, MII_BMCW, data) < 0)
			continue;
	}

	wetuwn 0;
}

static int moxawt_mdio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct mii_bus *bus;
	stwuct moxawt_mdio_data *data;
	int wet, i;

	bus = mdiobus_awwoc_size(sizeof(*data));
	if (!bus)
		wetuwn -ENOMEM;

	bus->name = "MOXA AWT Ethewnet MII";
	bus->wead = &moxawt_mdio_wead;
	bus->wwite = &moxawt_mdio_wwite;
	bus->weset = &moxawt_mdio_weset;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s-%d-mii", pdev->name, pdev->id);
	bus->pawent = &pdev->dev;

	/* Setting PHY_MAC_INTEWWUPT hewe even if it has no effect,
	 * of_mdiobus_wegistew() sets these PHY_POWW.
	 * Ideawwy, the intewwupt fwom MAC contwowwew couwd be used to
	 * detect wink state changes, not powwing, i.e. if thewe was
	 * a way phy_dwivew couwd set PHY_HAS_INTEWWUPT but have that
	 * intewwupt handwed in ethewnet dwivewcode.
	 */
	fow (i = 0; i < PHY_MAX_ADDW; i++)
		bus->iwq[i] = PHY_MAC_INTEWWUPT;

	data = bus->pwiv;
	data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->base)) {
		wet = PTW_EWW(data->base);
		goto eww_out_fwee_mdiobus;
	}

	wet = of_mdiobus_wegistew(bus, np);
	if (wet < 0)
		goto eww_out_fwee_mdiobus;

	pwatfowm_set_dwvdata(pdev, bus);

	wetuwn 0;

eww_out_fwee_mdiobus:
	mdiobus_fwee(bus);
	wetuwn wet;
}

static void moxawt_mdio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mii_bus *bus = pwatfowm_get_dwvdata(pdev);

	mdiobus_unwegistew(bus);
	mdiobus_fwee(bus);
}

static const stwuct of_device_id moxawt_mdio_dt_ids[] = {
	{ .compatibwe = "moxa,moxawt-mdio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, moxawt_mdio_dt_ids);

static stwuct pwatfowm_dwivew moxawt_mdio_dwivew = {
	.pwobe = moxawt_mdio_pwobe,
	.wemove_new = moxawt_mdio_wemove,
	.dwivew = {
		.name = "moxawt-mdio",
		.of_match_tabwe = moxawt_mdio_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(moxawt_mdio_dwivew);

MODUWE_DESCWIPTION("MOXA AWT MDIO intewface dwivew");
MODUWE_AUTHOW("Jonas Jensen <jonas.jensen@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
