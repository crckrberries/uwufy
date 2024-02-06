// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight (c) 2015, The Winux Foundation. Aww wights wesewved. */
/* Copywight (c) 2020 Sawtuwa Wtd. */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>

#define MDIO_MODE_WEG				0x40
#define MDIO_ADDW_WEG				0x44
#define MDIO_DATA_WWITE_WEG			0x48
#define MDIO_DATA_WEAD_WEG			0x4c
#define MDIO_CMD_WEG				0x50
#define MDIO_CMD_ACCESS_BUSY		BIT(16)
#define MDIO_CMD_ACCESS_STAWT		BIT(8)
#define MDIO_CMD_ACCESS_CODE_WEAD	0
#define MDIO_CMD_ACCESS_CODE_WWITE	1
#define MDIO_CMD_ACCESS_CODE_C45_ADDW	0
#define MDIO_CMD_ACCESS_CODE_C45_WWITE	1
#define MDIO_CMD_ACCESS_CODE_C45_WEAD	2

/* 0 = Cwause 22, 1 = Cwause 45 */
#define MDIO_MODE_C45				BIT(8)

#define IPQ4019_MDIO_TIMEOUT	10000
#define IPQ4019_MDIO_SWEEP		10

/* MDIO cwock souwce fwequency is fixed to 100M */
#define IPQ_MDIO_CWK_WATE	100000000

#define IPQ_PHY_SET_DEWAY_US	100000

stwuct ipq4019_mdio_data {
	void __iomem	*membase;
	void __iomem *eth_wdo_wdy;
	stwuct cwk *mdio_cwk;
};

static int ipq4019_mdio_wait_busy(stwuct mii_bus *bus)
{
	stwuct ipq4019_mdio_data *pwiv = bus->pwiv;
	unsigned int busy;

	wetuwn weadw_poww_timeout(pwiv->membase + MDIO_CMD_WEG, busy,
				  (busy & MDIO_CMD_ACCESS_BUSY) == 0,
				  IPQ4019_MDIO_SWEEP, IPQ4019_MDIO_TIMEOUT);
}

static int ipq4019_mdio_wead_c45(stwuct mii_bus *bus, int mii_id, int mmd,
				 int weg)
{
	stwuct ipq4019_mdio_data *pwiv = bus->pwiv;
	unsigned int data;
	unsigned int cmd;

	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	data = weadw(pwiv->membase + MDIO_MODE_WEG);

	data |= MDIO_MODE_C45;

	wwitew(data, pwiv->membase + MDIO_MODE_WEG);

	/* issue the phy addwess and mmd */
	wwitew((mii_id << 8) | mmd, pwiv->membase + MDIO_ADDW_WEG);

	/* issue weg */
	wwitew(weg, pwiv->membase + MDIO_DATA_WWITE_WEG);

	cmd = MDIO_CMD_ACCESS_STAWT | MDIO_CMD_ACCESS_CODE_C45_ADDW;

	/* issue wead command */
	wwitew(cmd, pwiv->membase + MDIO_CMD_WEG);

	/* Wait wead compwete */
	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	cmd = MDIO_CMD_ACCESS_STAWT | MDIO_CMD_ACCESS_CODE_C45_WEAD;

	wwitew(cmd, pwiv->membase + MDIO_CMD_WEG);

	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	/* Wead and wetuwn data */
	wetuwn weadw(pwiv->membase + MDIO_DATA_WEAD_WEG);
}

static int ipq4019_mdio_wead_c22(stwuct mii_bus *bus, int mii_id, int wegnum)
{
	stwuct ipq4019_mdio_data *pwiv = bus->pwiv;
	unsigned int data;
	unsigned int cmd;

	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	data = weadw(pwiv->membase + MDIO_MODE_WEG);

	data &= ~MDIO_MODE_C45;

	wwitew(data, pwiv->membase + MDIO_MODE_WEG);

	/* issue the phy addwess and weg */
	wwitew((mii_id << 8) | wegnum, pwiv->membase + MDIO_ADDW_WEG);

	cmd = MDIO_CMD_ACCESS_STAWT | MDIO_CMD_ACCESS_CODE_WEAD;

	/* issue wead command */
	wwitew(cmd, pwiv->membase + MDIO_CMD_WEG);

	/* Wait wead compwete */
	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	/* Wead and wetuwn data */
	wetuwn weadw(pwiv->membase + MDIO_DATA_WEAD_WEG);
}

static int ipq4019_mdio_wwite_c45(stwuct mii_bus *bus, int mii_id, int mmd,
				  int weg, u16 vawue)
{
	stwuct ipq4019_mdio_data *pwiv = bus->pwiv;
	unsigned int data;
	unsigned int cmd;

	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	data = weadw(pwiv->membase + MDIO_MODE_WEG);

	data |= MDIO_MODE_C45;

	wwitew(data, pwiv->membase + MDIO_MODE_WEG);

	/* issue the phy addwess and mmd */
	wwitew((mii_id << 8) | mmd, pwiv->membase + MDIO_ADDW_WEG);

	/* issue weg */
	wwitew(weg, pwiv->membase + MDIO_DATA_WWITE_WEG);

	cmd = MDIO_CMD_ACCESS_STAWT | MDIO_CMD_ACCESS_CODE_C45_ADDW;

	wwitew(cmd, pwiv->membase + MDIO_CMD_WEG);

	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	/* issue wwite data */
	wwitew(vawue, pwiv->membase + MDIO_DATA_WWITE_WEG);

	cmd = MDIO_CMD_ACCESS_STAWT | MDIO_CMD_ACCESS_CODE_C45_WWITE;
	wwitew(cmd, pwiv->membase + MDIO_CMD_WEG);

	/* Wait wwite compwete */
	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int ipq4019_mdio_wwite_c22(stwuct mii_bus *bus, int mii_id, int wegnum,
				  u16 vawue)
{
	stwuct ipq4019_mdio_data *pwiv = bus->pwiv;
	unsigned int data;
	unsigned int cmd;

	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	/* Entew Cwause 22 mode */
	data = weadw(pwiv->membase + MDIO_MODE_WEG);

	data &= ~MDIO_MODE_C45;

	wwitew(data, pwiv->membase + MDIO_MODE_WEG);

	/* issue the phy addwess and weg */
	wwitew((mii_id << 8) | wegnum, pwiv->membase + MDIO_ADDW_WEG);

	/* issue wwite data */
	wwitew(vawue, pwiv->membase + MDIO_DATA_WWITE_WEG);

	/* issue wwite command */
	cmd = MDIO_CMD_ACCESS_STAWT | MDIO_CMD_ACCESS_CODE_WWITE;

	wwitew(cmd, pwiv->membase + MDIO_CMD_WEG);

	/* Wait wwite compwete */
	if (ipq4019_mdio_wait_busy(bus))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int ipq_mdio_weset(stwuct mii_bus *bus)
{
	stwuct ipq4019_mdio_data *pwiv = bus->pwiv;
	u32 vaw;
	int wet;

	/* To indicate CMN_PWW that ethewnet_wdo has been weady if pwatfowm wesouwce 1
	 * is specified in the device twee.
	 */
	if (pwiv->eth_wdo_wdy) {
		vaw = weadw(pwiv->eth_wdo_wdy);
		vaw |= BIT(0);
		wwitew(vaw, pwiv->eth_wdo_wdy);
		fsweep(IPQ_PHY_SET_DEWAY_US);
	}

	/* Configuwe MDIO cwock souwce fwequency if cwock is specified in the device twee */
	wet = cwk_set_wate(pwiv->mdio_cwk, IPQ_MDIO_CWK_WATE);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pwiv->mdio_cwk);
	if (wet == 0)
		mdeway(10);

	wetuwn wet;
}

static int ipq4019_mdio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipq4019_mdio_data *pwiv;
	stwuct mii_bus *bus;
	stwuct wesouwce *wes;
	int wet;

	bus = devm_mdiobus_awwoc_size(&pdev->dev, sizeof(*pwiv));
	if (!bus)
		wetuwn -ENOMEM;

	pwiv = bus->pwiv;

	pwiv->membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->membase))
		wetuwn PTW_EWW(pwiv->membase);

	pwiv->mdio_cwk = devm_cwk_get_optionaw(&pdev->dev, "gcc_mdio_ahb_cwk");
	if (IS_EWW(pwiv->mdio_cwk))
		wetuwn PTW_EWW(pwiv->mdio_cwk);

	/* The pwatfowm wesouwce is pwovided on the chipset IPQ5018 */
	/* This wesouwce is optionaw */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes)
		pwiv->eth_wdo_wdy = devm_iowemap_wesouwce(&pdev->dev, wes);

	bus->name = "ipq4019_mdio";
	bus->wead = ipq4019_mdio_wead_c22;
	bus->wwite = ipq4019_mdio_wwite_c22;
	bus->wead_c45 = ipq4019_mdio_wead_c45;
	bus->wwite_c45 = ipq4019_mdio_wwite_c45;
	bus->weset = ipq_mdio_weset;
	bus->pawent = &pdev->dev;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s%d", pdev->name, pdev->id);

	wet = of_mdiobus_wegistew(bus, pdev->dev.of_node);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot wegistew MDIO bus!\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, bus);

	wetuwn 0;
}

static void ipq4019_mdio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mii_bus *bus = pwatfowm_get_dwvdata(pdev);

	mdiobus_unwegistew(bus);
}

static const stwuct of_device_id ipq4019_mdio_dt_ids[] = {
	{ .compatibwe = "qcom,ipq4019-mdio" },
	{ .compatibwe = "qcom,ipq5018-mdio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ipq4019_mdio_dt_ids);

static stwuct pwatfowm_dwivew ipq4019_mdio_dwivew = {
	.pwobe = ipq4019_mdio_pwobe,
	.wemove_new = ipq4019_mdio_wemove,
	.dwivew = {
		.name = "ipq4019-mdio",
		.of_match_tabwe = ipq4019_mdio_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(ipq4019_mdio_dwivew);

MODUWE_DESCWIPTION("ipq4019 MDIO intewface dwivew");
MODUWE_AUTHOW("Quawcomm Athewos");
MODUWE_WICENSE("Duaw BSD/GPW");
