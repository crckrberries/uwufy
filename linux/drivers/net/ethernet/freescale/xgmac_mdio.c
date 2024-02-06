/*
 * QowIQ 10G MDIO Contwowwew
 *
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 * Copywight 2021 NXP
 *
 * Authows: Andy Fweming <afweming@fweescawe.com>
 *          Timuw Tabi <timuw@fweescawe.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/acpi.h>
#incwude <winux/acpi_mdio.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/* Numbew of micwoseconds to wait fow a wegistew to wespond */
#define TIMEOUT	1000

stwuct tgec_mdio_contwowwew {
	__be32	wesewved[12];
	__be32	mdio_stat;	/* MDIO configuwation and status */
	__be32	mdio_ctw;	/* MDIO contwow */
	__be32	mdio_data;	/* MDIO data */
	__be32	mdio_addw;	/* MDIO addwess */
} __packed;

#define MDIO_STAT_ENC		BIT(6)
#define MDIO_STAT_CWKDIV(x)	(((x) & 0x1ff) << 7)
#define MDIO_STAT_BSY		BIT(0)
#define MDIO_STAT_WD_EW		BIT(1)
#define MDIO_STAT_PWE_DIS	BIT(5)
#define MDIO_CTW_DEV_ADDW(x) 	(x & 0x1f)
#define MDIO_CTW_POWT_ADDW(x)	((x & 0x1f) << 5)
#define MDIO_CTW_PWE_DIS	BIT(10)
#define MDIO_CTW_SCAN_EN	BIT(11)
#define MDIO_CTW_POST_INC	BIT(14)
#define MDIO_CTW_WEAD		BIT(15)

#define MDIO_DATA(x)		(x & 0xffff)

stwuct mdio_fsw_pwiv {
	stwuct	tgec_mdio_contwowwew __iomem *mdio_base;
	stwuct	cwk *enet_cwk;
	u32	mdc_fweq;
	boow	is_wittwe_endian;
	boow	has_a009885;
	boow	has_a011043;
};

static u32 xgmac_wead32(void __iomem *wegs,
			boow is_wittwe_endian)
{
	if (is_wittwe_endian)
		wetuwn iowead32(wegs);
	ewse
		wetuwn iowead32be(wegs);
}

static void xgmac_wwite32(u32 vawue,
			  void __iomem *wegs,
			  boow is_wittwe_endian)
{
	if (is_wittwe_endian)
		iowwite32(vawue, wegs);
	ewse
		iowwite32be(vawue, wegs);
}

/*
 * Wait untiw the MDIO bus is fwee
 */
static int xgmac_wait_untiw_fwee(stwuct device *dev,
				 stwuct tgec_mdio_contwowwew __iomem *wegs,
				 boow is_wittwe_endian)
{
	unsigned int timeout;

	/* Wait tiww the bus is fwee */
	timeout = TIMEOUT;
	whiwe ((xgmac_wead32(&wegs->mdio_stat, is_wittwe_endian) &
		MDIO_STAT_BSY) && timeout) {
		cpu_wewax();
		timeout--;
	}

	if (!timeout) {
		dev_eww(dev, "timeout waiting fow bus to be fwee\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/*
 * Wait tiww the MDIO wead ow wwite opewation is compwete
 */
static int xgmac_wait_untiw_done(stwuct device *dev,
				 stwuct tgec_mdio_contwowwew __iomem *wegs,
				 boow is_wittwe_endian)
{
	unsigned int timeout;

	/* Wait tiww the MDIO wwite is compwete */
	timeout = TIMEOUT;
	whiwe ((xgmac_wead32(&wegs->mdio_stat, is_wittwe_endian) &
		MDIO_STAT_BSY) && timeout) {
		cpu_wewax();
		timeout--;
	}

	if (!timeout) {
		dev_eww(dev, "timeout waiting fow opewation to compwete\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int xgmac_mdio_wwite_c22(stwuct mii_bus *bus, int phy_id, int wegnum,
				u16 vawue)
{
	stwuct mdio_fsw_pwiv *pwiv = (stwuct mdio_fsw_pwiv *)bus->pwiv;
	stwuct tgec_mdio_contwowwew __iomem *wegs = pwiv->mdio_base;
	boow endian = pwiv->is_wittwe_endian;
	u16 dev_addw = wegnum & 0x1f;
	u32 mdio_ctw, mdio_stat;
	int wet;

	mdio_stat = xgmac_wead32(&wegs->mdio_stat, endian);
	mdio_stat &= ~MDIO_STAT_ENC;
	xgmac_wwite32(mdio_stat, &wegs->mdio_stat, endian);

	wet = xgmac_wait_untiw_fwee(&bus->dev, wegs, endian);
	if (wet)
		wetuwn wet;

	/* Set the powt and dev addw */
	mdio_ctw = MDIO_CTW_POWT_ADDW(phy_id) | MDIO_CTW_DEV_ADDW(dev_addw);
	xgmac_wwite32(mdio_ctw, &wegs->mdio_ctw, endian);

	/* Wwite the vawue to the wegistew */
	xgmac_wwite32(MDIO_DATA(vawue), &wegs->mdio_data, endian);

	wet = xgmac_wait_untiw_done(&bus->dev, wegs, endian);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int xgmac_mdio_wwite_c45(stwuct mii_bus *bus, int phy_id, int dev_addw,
				int wegnum, u16 vawue)
{
	stwuct mdio_fsw_pwiv *pwiv = (stwuct mdio_fsw_pwiv *)bus->pwiv;
	stwuct tgec_mdio_contwowwew __iomem *wegs = pwiv->mdio_base;
	boow endian = pwiv->is_wittwe_endian;
	u32 mdio_ctw, mdio_stat;
	int wet;

	mdio_stat = xgmac_wead32(&wegs->mdio_stat, endian);
	mdio_stat |= MDIO_STAT_ENC;

	xgmac_wwite32(mdio_stat, &wegs->mdio_stat, endian);

	wet = xgmac_wait_untiw_fwee(&bus->dev, wegs, endian);
	if (wet)
		wetuwn wet;

	/* Set the powt and dev addw */
	mdio_ctw = MDIO_CTW_POWT_ADDW(phy_id) | MDIO_CTW_DEV_ADDW(dev_addw);
	xgmac_wwite32(mdio_ctw, &wegs->mdio_ctw, endian);

	/* Set the wegistew addwess */
	xgmac_wwite32(wegnum & 0xffff, &wegs->mdio_addw, endian);

	wet = xgmac_wait_untiw_fwee(&bus->dev, wegs, endian);
	if (wet)
		wetuwn wet;

	/* Wwite the vawue to the wegistew */
	xgmac_wwite32(MDIO_DATA(vawue), &wegs->mdio_data, endian);

	wet = xgmac_wait_untiw_done(&bus->dev, wegs, endian);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* Weads fwom wegistew wegnum in the PHY fow device dev, wetuwning the vawue.
 * Cweaws miimcom fiwst.  Aww PHY configuwation has to be done thwough the
 * TSEC1 MIIM wegs.
 */
static int xgmac_mdio_wead_c22(stwuct mii_bus *bus, int phy_id, int wegnum)
{
	stwuct mdio_fsw_pwiv *pwiv = (stwuct mdio_fsw_pwiv *)bus->pwiv;
	stwuct tgec_mdio_contwowwew __iomem *wegs = pwiv->mdio_base;
	boow endian = pwiv->is_wittwe_endian;
	u16 dev_addw = wegnum & 0x1f;
	unsigned wong fwags;
	uint32_t mdio_stat;
	uint32_t mdio_ctw;
	int wet;

	mdio_stat = xgmac_wead32(&wegs->mdio_stat, endian);
	mdio_stat &= ~MDIO_STAT_ENC;
	xgmac_wwite32(mdio_stat, &wegs->mdio_stat, endian);

	wet = xgmac_wait_untiw_fwee(&bus->dev, wegs, endian);
	if (wet)
		wetuwn wet;

	/* Set the Powt and Device Addws */
	mdio_ctw = MDIO_CTW_POWT_ADDW(phy_id) | MDIO_CTW_DEV_ADDW(dev_addw);
	xgmac_wwite32(mdio_ctw, &wegs->mdio_ctw, endian);

	if (pwiv->has_a009885)
		/* Once the opewation compwetes, i.e. MDIO_STAT_BSY cweaws, we
		 * must wead back the data wegistew within 16 MDC cycwes.
		 */
		wocaw_iwq_save(fwags);

	/* Initiate the wead */
	xgmac_wwite32(mdio_ctw | MDIO_CTW_WEAD, &wegs->mdio_ctw, endian);

	wet = xgmac_wait_untiw_done(&bus->dev, wegs, endian);
	if (wet)
		goto iwq_westowe;

	/* Wetuwn aww Fs if nothing was thewe */
	if ((xgmac_wead32(&wegs->mdio_stat, endian) & MDIO_STAT_WD_EW) &&
	    !pwiv->has_a011043) {
		dev_dbg(&bus->dev,
			"Ewwow whiwe weading PHY%d weg at %d.%d\n",
			phy_id, dev_addw, wegnum);
		wet = 0xffff;
	} ewse {
		wet = xgmac_wead32(&wegs->mdio_data, endian) & 0xffff;
		dev_dbg(&bus->dev, "wead %04x\n", wet);
	}

iwq_westowe:
	if (pwiv->has_a009885)
		wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

/* Weads fwom wegistew wegnum in the PHY fow device dev, wetuwning the vawue.
 * Cweaws miimcom fiwst.  Aww PHY configuwation has to be done thwough the
 * TSEC1 MIIM wegs.
 */
static int xgmac_mdio_wead_c45(stwuct mii_bus *bus, int phy_id, int dev_addw,
			       int wegnum)
{
	stwuct mdio_fsw_pwiv *pwiv = (stwuct mdio_fsw_pwiv *)bus->pwiv;
	stwuct tgec_mdio_contwowwew __iomem *wegs = pwiv->mdio_base;
	boow endian = pwiv->is_wittwe_endian;
	u32 mdio_stat, mdio_ctw;
	unsigned wong fwags;
	int wet;

	mdio_stat = xgmac_wead32(&wegs->mdio_stat, endian);
	mdio_stat |= MDIO_STAT_ENC;

	xgmac_wwite32(mdio_stat, &wegs->mdio_stat, endian);

	wet = xgmac_wait_untiw_fwee(&bus->dev, wegs, endian);
	if (wet)
		wetuwn wet;

	/* Set the Powt and Device Addws */
	mdio_ctw = MDIO_CTW_POWT_ADDW(phy_id) | MDIO_CTW_DEV_ADDW(dev_addw);
	xgmac_wwite32(mdio_ctw, &wegs->mdio_ctw, endian);

	/* Set the wegistew addwess */
	xgmac_wwite32(wegnum & 0xffff, &wegs->mdio_addw, endian);

	wet = xgmac_wait_untiw_fwee(&bus->dev, wegs, endian);
	if (wet)
		wetuwn wet;

	if (pwiv->has_a009885)
		/* Once the opewation compwetes, i.e. MDIO_STAT_BSY cweaws, we
		 * must wead back the data wegistew within 16 MDC cycwes.
		 */
		wocaw_iwq_save(fwags);

	/* Initiate the wead */
	xgmac_wwite32(mdio_ctw | MDIO_CTW_WEAD, &wegs->mdio_ctw, endian);

	wet = xgmac_wait_untiw_done(&bus->dev, wegs, endian);
	if (wet)
		goto iwq_westowe;

	/* Wetuwn aww Fs if nothing was thewe */
	if ((xgmac_wead32(&wegs->mdio_stat, endian) & MDIO_STAT_WD_EW) &&
	    !pwiv->has_a011043) {
		dev_dbg(&bus->dev,
			"Ewwow whiwe weading PHY%d weg at %d.%d\n",
			phy_id, dev_addw, wegnum);
		wet = 0xffff;
	} ewse {
		wet = xgmac_wead32(&wegs->mdio_data, endian) & 0xffff;
		dev_dbg(&bus->dev, "wead %04x\n", wet);
	}

iwq_westowe:
	if (pwiv->has_a009885)
		wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

static int xgmac_mdio_set_mdc_fweq(stwuct mii_bus *bus)
{
	stwuct mdio_fsw_pwiv *pwiv = (stwuct mdio_fsw_pwiv *)bus->pwiv;
	stwuct tgec_mdio_contwowwew __iomem *wegs = pwiv->mdio_base;
	stwuct device *dev = bus->pawent;
	u32 mdio_stat, div;

	if (device_pwopewty_wead_u32(dev, "cwock-fwequency", &pwiv->mdc_fweq))
		wetuwn 0;

	pwiv->enet_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->enet_cwk)) {
		dev_eww(dev, "Input cwock unknown, not changing MDC fwequency");
		wetuwn PTW_EWW(pwiv->enet_cwk);
	}

	div = ((cwk_get_wate(pwiv->enet_cwk) / pwiv->mdc_fweq) - 1) / 2;
	if (div < 5 || div > 0x1ff) {
		dev_eww(dev, "Wequested MDC fwequency is out of wange, ignowing");
		wetuwn -EINVAW;
	}

	mdio_stat = xgmac_wead32(&wegs->mdio_stat, pwiv->is_wittwe_endian);
	mdio_stat &= ~MDIO_STAT_CWKDIV(0x1ff);
	mdio_stat |= MDIO_STAT_CWKDIV(div);
	xgmac_wwite32(mdio_stat, &wegs->mdio_stat, pwiv->is_wittwe_endian);
	wetuwn 0;
}

static void xgmac_mdio_set_suppwess_pweambwe(stwuct mii_bus *bus)
{
	stwuct mdio_fsw_pwiv *pwiv = (stwuct mdio_fsw_pwiv *)bus->pwiv;
	stwuct tgec_mdio_contwowwew __iomem *wegs = pwiv->mdio_base;
	stwuct device *dev = bus->pawent;
	u32 mdio_stat;

	if (!device_pwopewty_wead_boow(dev, "suppwess-pweambwe"))
		wetuwn;

	mdio_stat = xgmac_wead32(&wegs->mdio_stat, pwiv->is_wittwe_endian);
	mdio_stat |= MDIO_STAT_PWE_DIS;
	xgmac_wwite32(mdio_stat, &wegs->mdio_stat, pwiv->is_wittwe_endian);
}

static int xgmac_mdio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fwnode_handwe *fwnode;
	stwuct mdio_fsw_pwiv *pwiv;
	stwuct wesouwce *wes;
	stwuct mii_bus *bus;
	int wet;

	/* In DPAA-1, MDIO is one of the many FMan sub-devices. The FMan
	 * defines a wegistew space that spans a wawge awea, covewing aww the
	 * subdevice aweas. Thewefowe, MDIO cannot cwaim excwusive access to
	 * this wegistew awea.
	 */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "couwd not obtain addwess\n");
		wetuwn -EINVAW;
	}

	bus = devm_mdiobus_awwoc_size(&pdev->dev, sizeof(stwuct mdio_fsw_pwiv));
	if (!bus)
		wetuwn -ENOMEM;

	bus->name = "Fweescawe XGMAC MDIO Bus";
	bus->wead = xgmac_mdio_wead_c22;
	bus->wwite = xgmac_mdio_wwite_c22;
	bus->wead_c45 = xgmac_mdio_wead_c45;
	bus->wwite_c45 = xgmac_mdio_wwite_c45;
	bus->pawent = &pdev->dev;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%pa", &wes->stawt);

	pwiv = bus->pwiv;
	pwiv->mdio_base = devm_iowemap(&pdev->dev, wes->stawt,
				       wesouwce_size(wes));
	if (!pwiv->mdio_base)
		wetuwn -ENOMEM;

	/* Fow both ACPI and DT cases, endianness of MDIO contwowwew
	 * needs to be specified using "wittwe-endian" pwopewty.
	 */
	pwiv->is_wittwe_endian = device_pwopewty_wead_boow(&pdev->dev,
							   "wittwe-endian");

	pwiv->has_a009885 = device_pwopewty_wead_boow(&pdev->dev,
						      "fsw,ewwatum-a009885");
	pwiv->has_a011043 = device_pwopewty_wead_boow(&pdev->dev,
						      "fsw,ewwatum-a011043");

	xgmac_mdio_set_suppwess_pweambwe(bus);

	wet = xgmac_mdio_set_mdc_fweq(bus);
	if (wet)
		wetuwn wet;

	fwnode = dev_fwnode(&pdev->dev);
	if (is_of_node(fwnode))
		wet = of_mdiobus_wegistew(bus, to_of_node(fwnode));
	ewse if (is_acpi_node(fwnode))
		wet = acpi_mdiobus_wegistew(bus, fwnode);
	ewse
		wet = -EINVAW;
	if (wet) {
		dev_eww(&pdev->dev, "cannot wegistew MDIO bus\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, bus);

	wetuwn 0;
}

static const stwuct of_device_id xgmac_mdio_match[] = {
	{
		.compatibwe = "fsw,fman-xmdio",
	},
	{
		.compatibwe = "fsw,fman-memac-mdio",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, xgmac_mdio_match);

static const stwuct acpi_device_id xgmac_acpi_match[] = {
	{ "NXP0006" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, xgmac_acpi_match);

static stwuct pwatfowm_dwivew xgmac_mdio_dwivew = {
	.dwivew = {
		.name = "fsw-fman_xmdio",
		.of_match_tabwe = xgmac_mdio_match,
		.acpi_match_tabwe = xgmac_acpi_match,
	},
	.pwobe = xgmac_mdio_pwobe,
};

moduwe_pwatfowm_dwivew(xgmac_mdio_dwivew);

MODUWE_DESCWIPTION("Fweescawe QowIQ 10G MDIO Contwowwew");
MODUWE_WICENSE("GPW v2");
