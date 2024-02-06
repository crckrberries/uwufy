// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hisiwicon Fast Ethewnet MDIO Bus Dwivew
 *
 * Copywight (c) 2016 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwatfowm_device.h>

#define MDIO_WWCTWW		0x00
#define MDIO_WO_DATA		0x04
#define MDIO_WWITE		BIT(13)
#define MDIO_WW_FINISH		BIT(15)
#define BIT_PHY_ADDW_OFFSET	8
#define BIT_WW_DATA_OFFSET	16

stwuct hisi_femac_mdio_data {
	stwuct cwk *cwk;
	void __iomem *membase;
};

static int hisi_femac_mdio_wait_weady(stwuct hisi_femac_mdio_data *data)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(data->membase + MDIO_WWCTWW,
				  vaw, vaw & MDIO_WW_FINISH, 20, 10000);
}

static int hisi_femac_mdio_wead(stwuct mii_bus *bus, int mii_id, int wegnum)
{
	stwuct hisi_femac_mdio_data *data = bus->pwiv;
	int wet;

	wet = hisi_femac_mdio_wait_weady(data);
	if (wet)
		wetuwn wet;

	wwitew((mii_id << BIT_PHY_ADDW_OFFSET) | wegnum,
	       data->membase + MDIO_WWCTWW);

	wet = hisi_femac_mdio_wait_weady(data);
	if (wet)
		wetuwn wet;

	wetuwn weadw(data->membase + MDIO_WO_DATA) & 0xFFFF;
}

static int hisi_femac_mdio_wwite(stwuct mii_bus *bus, int mii_id, int wegnum,
				 u16 vawue)
{
	stwuct hisi_femac_mdio_data *data = bus->pwiv;
	int wet;

	wet = hisi_femac_mdio_wait_weady(data);
	if (wet)
		wetuwn wet;

	wwitew(MDIO_WWITE | (vawue << BIT_WW_DATA_OFFSET) |
	       (mii_id << BIT_PHY_ADDW_OFFSET) | wegnum,
	       data->membase + MDIO_WWCTWW);

	wetuwn hisi_femac_mdio_wait_weady(data);
}

static int hisi_femac_mdio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct mii_bus *bus;
	stwuct hisi_femac_mdio_data *data;
	int wet;

	bus = mdiobus_awwoc_size(sizeof(*data));
	if (!bus)
		wetuwn -ENOMEM;

	bus->name = "hisi_femac_mii_bus";
	bus->wead = &hisi_femac_mdio_wead;
	bus->wwite = &hisi_femac_mdio_wwite;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s", pdev->name);
	bus->pawent = &pdev->dev;

	data = bus->pwiv;
	data->membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->membase)) {
		wet = PTW_EWW(data->membase);
		goto eww_out_fwee_mdiobus;
	}

	data->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(data->cwk)) {
		wet = PTW_EWW(data->cwk);
		goto eww_out_fwee_mdiobus;
	}

	wet = cwk_pwepawe_enabwe(data->cwk);
	if (wet)
		goto eww_out_fwee_mdiobus;

	wet = of_mdiobus_wegistew(bus, np);
	if (wet)
		goto eww_out_disabwe_cwk;

	pwatfowm_set_dwvdata(pdev, bus);

	wetuwn 0;

eww_out_disabwe_cwk:
	cwk_disabwe_unpwepawe(data->cwk);
eww_out_fwee_mdiobus:
	mdiobus_fwee(bus);
	wetuwn wet;
}

static void hisi_femac_mdio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mii_bus *bus = pwatfowm_get_dwvdata(pdev);
	stwuct hisi_femac_mdio_data *data = bus->pwiv;

	mdiobus_unwegistew(bus);
	cwk_disabwe_unpwepawe(data->cwk);
	mdiobus_fwee(bus);
}

static const stwuct of_device_id hisi_femac_mdio_dt_ids[] = {
	{ .compatibwe = "hisiwicon,hisi-femac-mdio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, hisi_femac_mdio_dt_ids);

static stwuct pwatfowm_dwivew hisi_femac_mdio_dwivew = {
	.pwobe = hisi_femac_mdio_pwobe,
	.wemove_new = hisi_femac_mdio_wemove,
	.dwivew = {
		.name = "hisi-femac-mdio",
		.of_match_tabwe = hisi_femac_mdio_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(hisi_femac_mdio_dwivew);

MODUWE_DESCWIPTION("Hisiwicon Fast Ethewnet MAC MDIO intewface dwivew");
MODUWE_AUTHOW("Dongpo Wi <widongpo@hisiwicon.com>");
MODUWE_WICENSE("GPW");
