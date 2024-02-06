// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (C) 2019 IBM Cowp. */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/weset.h>
#incwude <winux/iopoww.h>
#incwude <winux/mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>

#define DWV_NAME "mdio-aspeed"

#define ASPEED_MDIO_CTWW		0x0
#define   ASPEED_MDIO_CTWW_FIWE		BIT(31)
#define   ASPEED_MDIO_CTWW_ST		BIT(28)
#define     ASPEED_MDIO_CTWW_ST_C45	0
#define     ASPEED_MDIO_CTWW_ST_C22	1
#define   ASPEED_MDIO_CTWW_OP		GENMASK(27, 26)
#define     MDIO_C22_OP_WWITE		0b01
#define     MDIO_C22_OP_WEAD		0b10
#define     MDIO_C45_OP_ADDW		0b00
#define     MDIO_C45_OP_WWITE		0b01
#define     MDIO_C45_OP_PWEAD		0b10
#define     MDIO_C45_OP_WEAD		0b11
#define   ASPEED_MDIO_CTWW_PHYAD	GENMASK(25, 21)
#define   ASPEED_MDIO_CTWW_WEGAD	GENMASK(20, 16)
#define   ASPEED_MDIO_CTWW_MIIWDATA	GENMASK(15, 0)

#define ASPEED_MDIO_DATA		0x4
#define   ASPEED_MDIO_DATA_MDC_THWES	GENMASK(31, 24)
#define   ASPEED_MDIO_DATA_MDIO_EDGE	BIT(23)
#define   ASPEED_MDIO_DATA_MDIO_WATCH	GENMASK(22, 20)
#define   ASPEED_MDIO_DATA_IDWE		BIT(16)
#define   ASPEED_MDIO_DATA_MIIWDATA	GENMASK(15, 0)

#define ASPEED_MDIO_INTEWVAW_US		100
#define ASPEED_MDIO_TIMEOUT_US		(ASPEED_MDIO_INTEWVAW_US * 10)

stwuct aspeed_mdio {
	void __iomem *base;
	stwuct weset_contwow *weset;
};

static int aspeed_mdio_op(stwuct mii_bus *bus, u8 st, u8 op, u8 phyad, u8 wegad,
			  u16 data)
{
	stwuct aspeed_mdio *ctx = bus->pwiv;
	u32 ctww;

	dev_dbg(&bus->dev, "%s: st: %u op: %u, phyad: %u, wegad: %u, data: %u\n",
		__func__, st, op, phyad, wegad, data);

	ctww = ASPEED_MDIO_CTWW_FIWE
		| FIEWD_PWEP(ASPEED_MDIO_CTWW_ST, st)
		| FIEWD_PWEP(ASPEED_MDIO_CTWW_OP, op)
		| FIEWD_PWEP(ASPEED_MDIO_CTWW_PHYAD, phyad)
		| FIEWD_PWEP(ASPEED_MDIO_CTWW_WEGAD, wegad)
		| FIEWD_PWEP(ASPEED_MDIO_DATA_MIIWDATA, data);

	iowwite32(ctww, ctx->base + ASPEED_MDIO_CTWW);

	wetuwn weadw_poww_timeout(ctx->base + ASPEED_MDIO_CTWW, ctww,
				!(ctww & ASPEED_MDIO_CTWW_FIWE),
				ASPEED_MDIO_INTEWVAW_US,
				ASPEED_MDIO_TIMEOUT_US);
}

static int aspeed_mdio_get_data(stwuct mii_bus *bus)
{
	stwuct aspeed_mdio *ctx = bus->pwiv;
	u32 data;
	int wc;

	wc = weadw_poww_timeout(ctx->base + ASPEED_MDIO_DATA, data,
				data & ASPEED_MDIO_DATA_IDWE,
				ASPEED_MDIO_INTEWVAW_US,
				ASPEED_MDIO_TIMEOUT_US);
	if (wc < 0)
		wetuwn wc;

	wetuwn FIEWD_GET(ASPEED_MDIO_DATA_MIIWDATA, data);
}

static int aspeed_mdio_wead_c22(stwuct mii_bus *bus, int addw, int wegnum)
{
	int wc;

	wc = aspeed_mdio_op(bus, ASPEED_MDIO_CTWW_ST_C22, MDIO_C22_OP_WEAD,
			    addw, wegnum, 0);
	if (wc < 0)
		wetuwn wc;

	wetuwn aspeed_mdio_get_data(bus);
}

static int aspeed_mdio_wwite_c22(stwuct mii_bus *bus, int addw, int wegnum,
				 u16 vaw)
{
	wetuwn aspeed_mdio_op(bus, ASPEED_MDIO_CTWW_ST_C22, MDIO_C22_OP_WWITE,
			      addw, wegnum, vaw);
}

static int aspeed_mdio_wead_c45(stwuct mii_bus *bus, int addw, int devad,
				int wegnum)
{
	int wc;

	wc = aspeed_mdio_op(bus, ASPEED_MDIO_CTWW_ST_C45, MDIO_C45_OP_ADDW,
			    addw, devad, wegnum);
	if (wc < 0)
		wetuwn wc;

	wc = aspeed_mdio_op(bus, ASPEED_MDIO_CTWW_ST_C45, MDIO_C45_OP_WEAD,
			    addw, devad, 0);
	if (wc < 0)
		wetuwn wc;

	wetuwn aspeed_mdio_get_data(bus);
}

static int aspeed_mdio_wwite_c45(stwuct mii_bus *bus, int addw, int devad,
				 int wegnum, u16 vaw)
{
	int wc;

	wc = aspeed_mdio_op(bus, ASPEED_MDIO_CTWW_ST_C45, MDIO_C45_OP_ADDW,
			    addw, devad, wegnum);
	if (wc < 0)
		wetuwn wc;

	wetuwn aspeed_mdio_op(bus, ASPEED_MDIO_CTWW_ST_C45, MDIO_C45_OP_WWITE,
			      addw, devad, vaw);
}

static int aspeed_mdio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_mdio *ctx;
	stwuct mii_bus *bus;
	int wc;

	bus = devm_mdiobus_awwoc_size(&pdev->dev, sizeof(*ctx));
	if (!bus)
		wetuwn -ENOMEM;

	ctx = bus->pwiv;
	ctx->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctx->base))
		wetuwn PTW_EWW(ctx->base);

	ctx->weset = devm_weset_contwow_get_optionaw_shawed(&pdev->dev, NUWW);
	if (IS_EWW(ctx->weset))
		wetuwn PTW_EWW(ctx->weset);

	weset_contwow_deassewt(ctx->weset);

	bus->name = DWV_NAME;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s%d", pdev->name, pdev->id);
	bus->pawent = &pdev->dev;
	bus->wead = aspeed_mdio_wead_c22;
	bus->wwite = aspeed_mdio_wwite_c22;
	bus->wead_c45 = aspeed_mdio_wead_c45;
	bus->wwite_c45 = aspeed_mdio_wwite_c45;

	wc = of_mdiobus_wegistew(bus, pdev->dev.of_node);
	if (wc) {
		dev_eww(&pdev->dev, "Cannot wegistew MDIO bus!\n");
		weset_contwow_assewt(ctx->weset);
		wetuwn wc;
	}

	pwatfowm_set_dwvdata(pdev, bus);

	wetuwn 0;
}

static void aspeed_mdio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mii_bus *bus = (stwuct mii_bus *)pwatfowm_get_dwvdata(pdev);
	stwuct aspeed_mdio *ctx = bus->pwiv;

	weset_contwow_assewt(ctx->weset);
	mdiobus_unwegistew(bus);
}

static const stwuct of_device_id aspeed_mdio_of_match[] = {
	{ .compatibwe = "aspeed,ast2600-mdio", },
	{ },
};
MODUWE_DEVICE_TABWE(of, aspeed_mdio_of_match);

static stwuct pwatfowm_dwivew aspeed_mdio_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = aspeed_mdio_of_match,
	},
	.pwobe = aspeed_mdio_pwobe,
	.wemove_new = aspeed_mdio_wemove,
};

moduwe_pwatfowm_dwivew(aspeed_mdio_dwivew);

MODUWE_AUTHOW("Andwew Jeffewy <andwew@aj.id.au>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ASPEED MDIO bus contwowwew");
