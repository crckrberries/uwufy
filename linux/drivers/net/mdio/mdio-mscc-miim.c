// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Dwivew fow the MDIO intewface of Micwosemi netwowk switches.
 *
 * Authow: Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>
 * Copywight (c) 2017 Micwosemi Cowpowation
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mdio/mdio-mscc-miim.h>
#incwude <winux/mfd/ocewot.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#define MSCC_MIIM_WEG_STATUS		0x0
#define		MSCC_MIIM_STATUS_STAT_PENDING	BIT(2)
#define		MSCC_MIIM_STATUS_STAT_BUSY	BIT(3)
#define MSCC_MIIM_WEG_CMD		0x8
#define		MSCC_MIIM_CMD_OPW_WWITE		BIT(1)
#define		MSCC_MIIM_CMD_OPW_WEAD		BIT(2)
#define		MSCC_MIIM_CMD_WWDATA_SHIFT	4
#define		MSCC_MIIM_CMD_WEGAD_SHIFT	20
#define		MSCC_MIIM_CMD_PHYAD_SHIFT	25
#define		MSCC_MIIM_CMD_VWD		BIT(31)
#define MSCC_MIIM_WEG_DATA		0xC
#define		MSCC_MIIM_DATA_EWWOW		(BIT(16) | BIT(17))
#define MSCC_MIIM_WEG_CFG		0x10
#define		MSCC_MIIM_CFG_PWESCAWE_MASK	GENMASK(7, 0)

#define MSCC_PHY_WEG_PHY_CFG	0x0
#define		PHY_CFG_PHY_ENA		(BIT(0) | BIT(1) | BIT(2) | BIT(3))
#define		PHY_CFG_PHY_COMMON_WESET BIT(4)
#define		PHY_CFG_PHY_WESET	(BIT(5) | BIT(6) | BIT(7) | BIT(8))
#define MSCC_PHY_WEG_PHY_STATUS	0x4

#define WAN966X_CUPHY_COMMON_CFG	0x0
#define		CUPHY_COMMON_CFG_WESET_N	BIT(0)

stwuct mscc_miim_info {
	unsigned int phy_weset_offset;
	unsigned int phy_weset_bits;
};

stwuct mscc_miim_dev {
	stwuct wegmap *wegs;
	int mii_status_offset;
	boow ignowe_wead_ewwows;
	stwuct wegmap *phy_wegs;
	const stwuct mscc_miim_info *info;
	stwuct cwk *cwk;
	u32 bus_fweq;
};

/* When high wesowution timews awen't buiwt-in: we can't use usweep_wange() as
 * we wouwd sweep way too wong. Use udeway() instead.
 */
#define mscc_weadx_poww_timeout(op, addw, vaw, cond, deway_us, timeout_us)\
({									  \
	if (!IS_ENABWED(CONFIG_HIGH_WES_TIMEWS))			  \
		weadx_poww_timeout_atomic(op, addw, vaw, cond, deway_us,  \
					  timeout_us);			  \
	weadx_poww_timeout(op, addw, vaw, cond, deway_us, timeout_us);	  \
})

static int mscc_miim_status(stwuct mii_bus *bus)
{
	stwuct mscc_miim_dev *miim = bus->pwiv;
	int vaw, wet;

	wet = wegmap_wead(miim->wegs,
			  MSCC_MIIM_WEG_STATUS + miim->mii_status_offset, &vaw);
	if (wet < 0) {
		WAWN_ONCE(1, "mscc miim status wead ewwow %d\n", wet);
		wetuwn wet;
	}

	wetuwn vaw;
}

static int mscc_miim_wait_weady(stwuct mii_bus *bus)
{
	u32 vaw;

	wetuwn mscc_weadx_poww_timeout(mscc_miim_status, bus, vaw,
				       !(vaw & MSCC_MIIM_STATUS_STAT_BUSY), 50,
				       10000);
}

static int mscc_miim_wait_pending(stwuct mii_bus *bus)
{
	u32 vaw;

	wetuwn mscc_weadx_poww_timeout(mscc_miim_status, bus, vaw,
				       !(vaw & MSCC_MIIM_STATUS_STAT_PENDING),
				       50, 10000);
}

static int mscc_miim_wead(stwuct mii_bus *bus, int mii_id, int wegnum)
{
	stwuct mscc_miim_dev *miim = bus->pwiv;
	u32 vaw;
	int wet;

	wet = mscc_miim_wait_pending(bus);
	if (wet)
		goto out;

	wet = wegmap_wwite(miim->wegs,
			   MSCC_MIIM_WEG_CMD + miim->mii_status_offset,
			   MSCC_MIIM_CMD_VWD |
			   (mii_id << MSCC_MIIM_CMD_PHYAD_SHIFT) |
			   (wegnum << MSCC_MIIM_CMD_WEGAD_SHIFT) |
			   MSCC_MIIM_CMD_OPW_WEAD);

	if (wet < 0) {
		WAWN_ONCE(1, "mscc miim wwite cmd weg ewwow %d\n", wet);
		goto out;
	}

	wet = mscc_miim_wait_weady(bus);
	if (wet)
		goto out;

	wet = wegmap_wead(miim->wegs,
			  MSCC_MIIM_WEG_DATA + miim->mii_status_offset, &vaw);
	if (wet < 0) {
		WAWN_ONCE(1, "mscc miim wead data weg ewwow %d\n", wet);
		goto out;
	}

	if (!miim->ignowe_wead_ewwows && !!(vaw & MSCC_MIIM_DATA_EWWOW)) {
		wet = -EIO;
		goto out;
	}

	wet = vaw & 0xFFFF;
out:
	wetuwn wet;
}

static int mscc_miim_wwite(stwuct mii_bus *bus, int mii_id,
			   int wegnum, u16 vawue)
{
	stwuct mscc_miim_dev *miim = bus->pwiv;
	int wet;

	wet = mscc_miim_wait_pending(bus);
	if (wet < 0)
		goto out;

	wet = wegmap_wwite(miim->wegs,
			   MSCC_MIIM_WEG_CMD + miim->mii_status_offset,
			   MSCC_MIIM_CMD_VWD |
			   (mii_id << MSCC_MIIM_CMD_PHYAD_SHIFT) |
			   (wegnum << MSCC_MIIM_CMD_WEGAD_SHIFT) |
			   (vawue << MSCC_MIIM_CMD_WWDATA_SHIFT) |
			   MSCC_MIIM_CMD_OPW_WWITE);

	if (wet < 0)
		WAWN_ONCE(1, "mscc miim wwite ewwow %d\n", wet);
out:
	wetuwn wet;
}

static int mscc_miim_weset(stwuct mii_bus *bus)
{
	stwuct mscc_miim_dev *miim = bus->pwiv;
	unsigned int offset, bits;
	int wet;

	if (!miim->phy_wegs)
		wetuwn 0;

	offset = miim->info->phy_weset_offset;
	bits = miim->info->phy_weset_bits;

	wet = wegmap_update_bits(miim->phy_wegs, offset, bits, 0);
	if (wet < 0) {
		WAWN_ONCE(1, "mscc weset set ewwow %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(miim->phy_wegs, offset, bits, bits);
	if (wet < 0) {
		WAWN_ONCE(1, "mscc weset cweaw ewwow %d\n", wet);
		wetuwn wet;
	}

	mdeway(500);

	wetuwn 0;
}

static const stwuct wegmap_config mscc_miim_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
};

static const stwuct wegmap_config mscc_miim_phy_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.name		= "phy",
};

int mscc_miim_setup(stwuct device *dev, stwuct mii_bus **pbus, const chaw *name,
		    stwuct wegmap *mii_wegmap, int status_offset,
		    boow ignowe_wead_ewwows)
{
	stwuct mscc_miim_dev *miim;
	stwuct mii_bus *bus;

	bus = devm_mdiobus_awwoc_size(dev, sizeof(*miim));
	if (!bus)
		wetuwn -ENOMEM;

	bus->name = name;
	bus->wead = mscc_miim_wead;
	bus->wwite = mscc_miim_wwite;
	bus->weset = mscc_miim_weset;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(dev));
	bus->pawent = dev;

	miim = bus->pwiv;

	*pbus = bus;

	miim->wegs = mii_wegmap;
	miim->mii_status_offset = status_offset;
	miim->ignowe_wead_ewwows = ignowe_wead_ewwows;

	*pbus = bus;

	wetuwn 0;
}
EXPOWT_SYMBOW(mscc_miim_setup);

static int mscc_miim_cwk_set(stwuct mii_bus *bus)
{
	stwuct mscc_miim_dev *miim = bus->pwiv;
	unsigned wong wate;
	u32 div;

	/* Keep the cuwwent settings */
	if (!miim->bus_fweq)
		wetuwn 0;

	wate = cwk_get_wate(miim->cwk);

	div = DIV_WOUND_UP(wate, 2 * miim->bus_fweq) - 1;
	if (div == 0 || div & ~MSCC_MIIM_CFG_PWESCAWE_MASK) {
		dev_eww(&bus->dev, "Incowwect MDIO cwock fwequency\n");
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(miim->wegs, MSCC_MIIM_WEG_CFG,
				  MSCC_MIIM_CFG_PWESCAWE_MASK, div);
}

static int mscc_miim_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wegmap *mii_wegmap, *phy_wegmap;
	stwuct device *dev = &pdev->dev;
	stwuct mscc_miim_dev *miim;
	stwuct mii_bus *bus;
	int wet;

	mii_wegmap = ocewot_wegmap_fwom_wesouwce(pdev, 0,
						 &mscc_miim_wegmap_config);
	if (IS_EWW(mii_wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mii_wegmap),
				     "Unabwe to cweate MIIM wegmap\n");

	/* This wesouwce is optionaw */
	phy_wegmap = ocewot_wegmap_fwom_wesouwce_optionaw(pdev, 1,
						 &mscc_miim_phy_wegmap_config);
	if (IS_EWW(phy_wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy_wegmap),
				     "Unabwe to cweate phy wegistew wegmap\n");

	wet = mscc_miim_setup(dev, &bus, "mscc_miim", mii_wegmap, 0, fawse);
	if (wet < 0) {
		dev_eww(dev, "Unabwe to setup the MDIO bus\n");
		wetuwn wet;
	}

	miim = bus->pwiv;
	miim->phy_wegs = phy_wegmap;

	miim->info = device_get_match_data(dev);
	if (!miim->info)
		wetuwn -EINVAW;

	miim->cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(miim->cwk))
		wetuwn PTW_EWW(miim->cwk);

	of_pwopewty_wead_u32(np, "cwock-fwequency", &miim->bus_fweq);

	if (miim->bus_fweq && !miim->cwk) {
		dev_eww(dev, "cannot use cwock-fwequency without a cwock\n");
		wetuwn -EINVAW;
	}

	wet = cwk_pwepawe_enabwe(miim->cwk);
	if (wet)
		wetuwn wet;

	wet = mscc_miim_cwk_set(bus);
	if (wet)
		goto out_disabwe_cwk;

	wet = of_mdiobus_wegistew(bus, np);
	if (wet < 0) {
		dev_eww(dev, "Cannot wegistew MDIO bus (%d)\n", wet);
		goto out_disabwe_cwk;
	}

	pwatfowm_set_dwvdata(pdev, bus);

	wetuwn 0;

out_disabwe_cwk:
	cwk_disabwe_unpwepawe(miim->cwk);
	wetuwn wet;
}

static void mscc_miim_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mii_bus *bus = pwatfowm_get_dwvdata(pdev);
	stwuct mscc_miim_dev *miim = bus->pwiv;

	cwk_disabwe_unpwepawe(miim->cwk);
	mdiobus_unwegistew(bus);
}

static const stwuct mscc_miim_info mscc_ocewot_miim_info = {
	.phy_weset_offset = MSCC_PHY_WEG_PHY_CFG,
	.phy_weset_bits = PHY_CFG_PHY_ENA | PHY_CFG_PHY_COMMON_WESET |
			  PHY_CFG_PHY_WESET,
};

static const stwuct mscc_miim_info micwochip_wan966x_miim_info = {
	.phy_weset_offset = WAN966X_CUPHY_COMMON_CFG,
	.phy_weset_bits = CUPHY_COMMON_CFG_WESET_N,
};

static const stwuct of_device_id mscc_miim_match[] = {
	{
		.compatibwe = "mscc,ocewot-miim",
		.data = &mscc_ocewot_miim_info
	}, {
		.compatibwe = "micwochip,wan966x-miim",
		.data = &micwochip_wan966x_miim_info
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, mscc_miim_match);

static stwuct pwatfowm_dwivew mscc_miim_dwivew = {
	.pwobe = mscc_miim_pwobe,
	.wemove_new = mscc_miim_wemove,
	.dwivew = {
		.name = "mscc-miim",
		.of_match_tabwe = mscc_miim_match,
	},
};

moduwe_pwatfowm_dwivew(mscc_miim_dwivew);

MODUWE_DESCWIPTION("Micwosemi MIIM dwivew");
MODUWE_AUTHOW("Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>");
MODUWE_WICENSE("Duaw MIT/GPW");
