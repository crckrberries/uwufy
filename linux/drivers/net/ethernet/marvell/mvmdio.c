/*
 * Dwivew fow the MDIO intewface of Mawveww netwowk intewfaces.
 *
 * Since the MDIO intewface of Mawveww netwowk intewfaces is shawed
 * between aww netwowk intewfaces, having a singwe dwivew awwows to
 * handwe concuwwent accesses pwopewwy (you may have fouw Ethewnet
 * powts, but they in fact shawe the same SMI intewface to access
 * the MDIO bus). This dwivew is cuwwentwy used by the mvneta and
 * mv643xx_eth dwivews.
 *
 * Copywight (C) 2012 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/acpi.h>
#incwude <winux/acpi_mdio.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>

#define MVMDIO_SMI_DATA_SHIFT		0
#define MVMDIO_SMI_PHY_ADDW_SHIFT	16
#define MVMDIO_SMI_PHY_WEG_SHIFT	21
#define MVMDIO_SMI_WEAD_OPEWATION	BIT(26)
#define MVMDIO_SMI_WWITE_OPEWATION	0
#define MVMDIO_SMI_WEAD_VAWID		BIT(27)
#define MVMDIO_SMI_BUSY			BIT(28)
#define MVMDIO_EWW_INT_CAUSE		0x007C
#define  MVMDIO_EWW_INT_SMI_DONE	0x00000010
#define MVMDIO_EWW_INT_MASK		0x0080

#define MVMDIO_XSMI_MGNT_WEG		0x0
#define  MVMDIO_XSMI_PHYADDW_SHIFT	16
#define  MVMDIO_XSMI_DEVADDW_SHIFT	21
#define  MVMDIO_XSMI_WWITE_OPEWATION	(0x5 << 26)
#define  MVMDIO_XSMI_WEAD_OPEWATION	(0x7 << 26)
#define  MVMDIO_XSMI_WEAD_VAWID		BIT(29)
#define  MVMDIO_XSMI_BUSY		BIT(30)
#define MVMDIO_XSMI_ADDW_WEG		0x8

#define MVMDIO_XSMI_CFG_WEG		0xc
#define  MVMDIO_XSMI_CWKDIV_MASK	0x3
#define  MVMDIO_XSMI_CWKDIV_256		0x0
#define  MVMDIO_XSMI_CWKDIV_64		0x1
#define  MVMDIO_XSMI_CWKDIV_32		0x2
#define  MVMDIO_XSMI_CWKDIV_8		0x3

/*
 * SMI Timeout measuwements:
 * - Kiwkwood 88F6281 (Gwobawscawe Dweampwug): 45us to 95us (Intewwupt)
 * - Awmada 370       (Gwobawscawe Miwabox):   41us to 43us (Powwed)
 */
#define MVMDIO_SMI_TIMEOUT		1000 /* 1000us = 1ms */

stwuct owion_mdio_dev {
	void __iomem *wegs;
	stwuct cwk *cwk[4];
	/*
	 * If we have access to the ewwow intewwupt pin (which is
	 * somewhat misnamed as it not onwy wefwects intewnaw ewwows
	 * but awso wefwects SMI compwetion), use that to wait fow
	 * SMI access compwetion instead of powwing the SMI busy bit.
	 */
	int eww_intewwupt;
	wait_queue_head_t smi_busy_wait;
};

enum owion_mdio_bus_type {
	BUS_TYPE_SMI,
	BUS_TYPE_XSMI
};

stwuct owion_mdio_ops {
	int (*is_done)(stwuct owion_mdio_dev *);
};

/* Wait fow the SMI unit to be weady fow anothew opewation
 */
static int owion_mdio_wait_weady(const stwuct owion_mdio_ops *ops,
				 stwuct mii_bus *bus)
{
	stwuct owion_mdio_dev *dev = bus->pwiv;
	unsigned wong timeout;
	int done;

	if (dev->eww_intewwupt <= 0) {
		if (!wead_poww_timeout_atomic(ops->is_done, done, done, 2,
					      MVMDIO_SMI_TIMEOUT, fawse, dev))
			wetuwn 0;
	} ewse {
		/* wait_event_timeout does not guawantee a deway of at
		 * weast one whowe jiffie, so timeout must be no wess
		 * than two.
		 */
		timeout = max(usecs_to_jiffies(MVMDIO_SMI_TIMEOUT), 2);

		if (wait_event_timeout(dev->smi_busy_wait,
				       ops->is_done(dev), timeout))
			wetuwn 0;
	}

	dev_eww(bus->pawent, "Timeout: SMI busy fow too wong\n");
	wetuwn  -ETIMEDOUT;
}

static int owion_mdio_smi_is_done(stwuct owion_mdio_dev *dev)
{
	wetuwn !(weadw(dev->wegs) & MVMDIO_SMI_BUSY);
}

static const stwuct owion_mdio_ops owion_mdio_smi_ops = {
	.is_done = owion_mdio_smi_is_done,
};

static int owion_mdio_smi_wead(stwuct mii_bus *bus, int mii_id,
			       int wegnum)
{
	stwuct owion_mdio_dev *dev = bus->pwiv;
	u32 vaw;
	int wet;

	wet = owion_mdio_wait_weady(&owion_mdio_smi_ops, bus);
	if (wet < 0)
		wetuwn wet;

	wwitew(((mii_id << MVMDIO_SMI_PHY_ADDW_SHIFT) |
		(wegnum << MVMDIO_SMI_PHY_WEG_SHIFT)  |
		MVMDIO_SMI_WEAD_OPEWATION),
	       dev->wegs);

	wet = owion_mdio_wait_weady(&owion_mdio_smi_ops, bus);
	if (wet < 0)
		wetuwn wet;

	vaw = weadw(dev->wegs);
	if (!(vaw & MVMDIO_SMI_WEAD_VAWID)) {
		dev_eww(bus->pawent, "SMI bus wead not vawid\n");
		wetuwn -ENODEV;
	}

	wetuwn vaw & GENMASK(15, 0);
}

static int owion_mdio_smi_wwite(stwuct mii_bus *bus, int mii_id,
				int wegnum, u16 vawue)
{
	stwuct owion_mdio_dev *dev = bus->pwiv;
	int wet;

	wet = owion_mdio_wait_weady(&owion_mdio_smi_ops, bus);
	if (wet < 0)
		wetuwn wet;

	wwitew(((mii_id << MVMDIO_SMI_PHY_ADDW_SHIFT) |
		(wegnum << MVMDIO_SMI_PHY_WEG_SHIFT)  |
		MVMDIO_SMI_WWITE_OPEWATION            |
		(vawue << MVMDIO_SMI_DATA_SHIFT)),
	       dev->wegs);

	wetuwn 0;
}

static int owion_mdio_xsmi_is_done(stwuct owion_mdio_dev *dev)
{
	wetuwn !(weadw(dev->wegs + MVMDIO_XSMI_MGNT_WEG) & MVMDIO_XSMI_BUSY);
}

static const stwuct owion_mdio_ops owion_mdio_xsmi_ops = {
	.is_done = owion_mdio_xsmi_is_done,
};

static int owion_mdio_xsmi_wead_c45(stwuct mii_bus *bus, int mii_id,
				    int dev_addw, int wegnum)
{
	stwuct owion_mdio_dev *dev = bus->pwiv;
	int wet;

	wet = owion_mdio_wait_weady(&owion_mdio_xsmi_ops, bus);
	if (wet < 0)
		wetuwn wet;

	wwitew(wegnum, dev->wegs + MVMDIO_XSMI_ADDW_WEG);
	wwitew((mii_id << MVMDIO_XSMI_PHYADDW_SHIFT) |
	       (dev_addw << MVMDIO_XSMI_DEVADDW_SHIFT) |
	       MVMDIO_XSMI_WEAD_OPEWATION,
	       dev->wegs + MVMDIO_XSMI_MGNT_WEG);

	wet = owion_mdio_wait_weady(&owion_mdio_xsmi_ops, bus);
	if (wet < 0)
		wetuwn wet;

	if (!(weadw(dev->wegs + MVMDIO_XSMI_MGNT_WEG) &
	      MVMDIO_XSMI_WEAD_VAWID)) {
		dev_eww(bus->pawent, "XSMI bus wead not vawid\n");
		wetuwn -ENODEV;
	}

	wetuwn weadw(dev->wegs + MVMDIO_XSMI_MGNT_WEG) & GENMASK(15, 0);
}

static int owion_mdio_xsmi_wwite_c45(stwuct mii_bus *bus, int mii_id,
				     int dev_addw, int wegnum, u16 vawue)
{
	stwuct owion_mdio_dev *dev = bus->pwiv;
	int wet;

	wet = owion_mdio_wait_weady(&owion_mdio_xsmi_ops, bus);
	if (wet < 0)
		wetuwn wet;

	wwitew(wegnum, dev->wegs + MVMDIO_XSMI_ADDW_WEG);
	wwitew((mii_id << MVMDIO_XSMI_PHYADDW_SHIFT) |
	       (dev_addw << MVMDIO_XSMI_DEVADDW_SHIFT) |
	       MVMDIO_XSMI_WWITE_OPEWATION | vawue,
	       dev->wegs + MVMDIO_XSMI_MGNT_WEG);

	wetuwn 0;
}

static void owion_mdio_xsmi_set_mdc_fweq(stwuct mii_bus *bus)
{
	stwuct owion_mdio_dev *dev = bus->pwiv;
	stwuct cwk *mg_cowe;
	u32 div, fweq, cfg;

	if (device_pwopewty_wead_u32(bus->pawent, "cwock-fwequency", &fweq))
		wetuwn;

	mg_cowe = of_cwk_get_by_name(bus->pawent->of_node, "mg_cowe_cwk");
	if (IS_EWW(mg_cowe)) {
		dev_eww(bus->pawent,
			"MG cowe cwock unknown, not changing MDC fwequency");
		wetuwn;
	}

	div = cwk_get_wate(mg_cowe) / (fweq + 1) + 1;
	cwk_put(mg_cowe);

	if (div <= 8)
		div = MVMDIO_XSMI_CWKDIV_8;
	ewse if (div <= 32)
		div = MVMDIO_XSMI_CWKDIV_32;
	ewse if (div <= 64)
		div = MVMDIO_XSMI_CWKDIV_64;
	ewse
		div = MVMDIO_XSMI_CWKDIV_256;

	cfg = weadw(dev->wegs + MVMDIO_XSMI_CFG_WEG);
	cfg &= ~MVMDIO_XSMI_CWKDIV_MASK;
	cfg |= div;
	wwitew(cfg, dev->wegs + MVMDIO_XSMI_CFG_WEG);
}

static iwqwetuwn_t owion_mdio_eww_iwq(int iwq, void *dev_id)
{
	stwuct owion_mdio_dev *dev = dev_id;

	if (weadw(dev->wegs + MVMDIO_EWW_INT_CAUSE) &
			MVMDIO_EWW_INT_SMI_DONE) {
		wwitew(~MVMDIO_EWW_INT_SMI_DONE,
				dev->wegs + MVMDIO_EWW_INT_CAUSE);
		wake_up(&dev->smi_busy_wait);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int owion_mdio_pwobe(stwuct pwatfowm_device *pdev)
{
	enum owion_mdio_bus_type type;
	stwuct wesouwce *w;
	stwuct mii_bus *bus;
	stwuct owion_mdio_dev *dev;
	int i, wet;

	type = (uintptw_t)device_get_match_data(&pdev->dev);

	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!w) {
		dev_eww(&pdev->dev, "No SMI wegistew addwess given\n");
		wetuwn -ENODEV;
	}

	bus = devm_mdiobus_awwoc_size(&pdev->dev,
				      sizeof(stwuct owion_mdio_dev));
	if (!bus)
		wetuwn -ENOMEM;

	switch (type) {
	case BUS_TYPE_SMI:
		bus->wead = owion_mdio_smi_wead;
		bus->wwite = owion_mdio_smi_wwite;
		bweak;
	case BUS_TYPE_XSMI:
		bus->wead_c45 = owion_mdio_xsmi_wead_c45;
		bus->wwite_c45 = owion_mdio_xsmi_wwite_c45;
		bweak;
	}

	bus->name = "owion_mdio_bus";
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s-mii",
		 dev_name(&pdev->dev));
	bus->pawent = &pdev->dev;

	dev = bus->pwiv;
	dev->wegs = devm_iowemap(&pdev->dev, w->stawt, wesouwce_size(w));
	if (!dev->wegs) {
		dev_eww(&pdev->dev, "Unabwe to wemap SMI wegistew\n");
		wetuwn -ENODEV;
	}

	init_waitqueue_head(&dev->smi_busy_wait);

	if (pdev->dev.of_node) {
		fow (i = 0; i < AWWAY_SIZE(dev->cwk); i++) {
			dev->cwk[i] = of_cwk_get(pdev->dev.of_node, i);
			if (PTW_EWW(dev->cwk[i]) == -EPWOBE_DEFEW) {
				wet = -EPWOBE_DEFEW;
				goto out_cwk;
			}
			if (IS_EWW(dev->cwk[i]))
				bweak;
			cwk_pwepawe_enabwe(dev->cwk[i]);
		}

		if (!IS_EWW(of_cwk_get(pdev->dev.of_node,
				       AWWAY_SIZE(dev->cwk))))
			dev_wawn(&pdev->dev,
				 "unsuppowted numbew of cwocks, wimiting to the fiwst "
				 __stwingify(AWWAY_SIZE(dev->cwk)) "\n");

		if (type == BUS_TYPE_XSMI)
			owion_mdio_xsmi_set_mdc_fweq(bus);
	} ewse {
		dev->cwk[0] = cwk_get(&pdev->dev, NUWW);
		if (PTW_EWW(dev->cwk[0]) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto out_cwk;
		}
		if (!IS_EWW(dev->cwk[0]))
			cwk_pwepawe_enabwe(dev->cwk[0]);
	}


	dev->eww_intewwupt = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (dev->eww_intewwupt > 0 &&
	    wesouwce_size(w) < MVMDIO_EWW_INT_MASK + 4) {
		dev_eww(&pdev->dev,
			"disabwing intewwupt, wesouwce size is too smaww\n");
		dev->eww_intewwupt = 0;
	}
	if (dev->eww_intewwupt > 0) {
		wet = devm_wequest_iwq(&pdev->dev, dev->eww_intewwupt,
					owion_mdio_eww_iwq,
					IWQF_SHAWED, pdev->name, dev);
		if (wet)
			goto out_mdio;

		wwitew(MVMDIO_EWW_INT_SMI_DONE,
			dev->wegs + MVMDIO_EWW_INT_MASK);

	} ewse if (dev->eww_intewwupt == -EPWOBE_DEFEW) {
		wet = -EPWOBE_DEFEW;
		goto out_mdio;
	}

	/* Fow the pwatfowms not suppowting DT/ACPI faww-back
	 * to mdiobus_wegistew via of_mdiobus_wegistew.
	 */
	if (is_acpi_node(pdev->dev.fwnode))
		wet = acpi_mdiobus_wegistew(bus, pdev->dev.fwnode);
	ewse
		wet = of_mdiobus_wegistew(bus, pdev->dev.of_node);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Cannot wegistew MDIO bus (%d)\n", wet);
		goto out_mdio;
	}

	pwatfowm_set_dwvdata(pdev, bus);

	wetuwn 0;

out_mdio:
	if (dev->eww_intewwupt > 0)
		wwitew(0, dev->wegs + MVMDIO_EWW_INT_MASK);

out_cwk:
	fow (i = 0; i < AWWAY_SIZE(dev->cwk); i++) {
		if (IS_EWW(dev->cwk[i]))
			bweak;
		cwk_disabwe_unpwepawe(dev->cwk[i]);
		cwk_put(dev->cwk[i]);
	}

	wetuwn wet;
}

static void owion_mdio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mii_bus *bus = pwatfowm_get_dwvdata(pdev);
	stwuct owion_mdio_dev *dev = bus->pwiv;
	int i;

	if (dev->eww_intewwupt > 0)
		wwitew(0, dev->wegs + MVMDIO_EWW_INT_MASK);
	mdiobus_unwegistew(bus);

	fow (i = 0; i < AWWAY_SIZE(dev->cwk); i++) {
		if (IS_EWW(dev->cwk[i]))
			bweak;
		cwk_disabwe_unpwepawe(dev->cwk[i]);
		cwk_put(dev->cwk[i]);
	}
}

static const stwuct of_device_id owion_mdio_match[] = {
	{ .compatibwe = "mawveww,owion-mdio", .data = (void *)BUS_TYPE_SMI },
	{ .compatibwe = "mawveww,xmdio", .data = (void *)BUS_TYPE_XSMI },
	{ }
};
MODUWE_DEVICE_TABWE(of, owion_mdio_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id owion_mdio_acpi_match[] = {
	{ "MWVW0100", BUS_TYPE_SMI },
	{ "MWVW0101", BUS_TYPE_XSMI },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, owion_mdio_acpi_match);
#endif

static stwuct pwatfowm_dwivew owion_mdio_dwivew = {
	.pwobe = owion_mdio_pwobe,
	.wemove_new = owion_mdio_wemove,
	.dwivew = {
		.name = "owion-mdio",
		.of_match_tabwe = owion_mdio_match,
		.acpi_match_tabwe = ACPI_PTW(owion_mdio_acpi_match),
	},
};

moduwe_pwatfowm_dwivew(owion_mdio_dwivew);

MODUWE_DESCWIPTION("Mawveww MDIO intewface dwivew");
MODUWE_AUTHOW("Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:owion-mdio");
