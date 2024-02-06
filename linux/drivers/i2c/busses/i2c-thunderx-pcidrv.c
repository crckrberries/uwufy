/*
 * Cavium ThundewX i2c dwivew.
 *
 * Copywight (C) 2015,2016 Cavium Inc.
 * Authows: Fwed Mawtin <fmawtin@caviumnetwowks.com>
 *	    Jan Gwaubew <jgwaubew@cavium.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-smbus.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pci.h>

#incwude "i2c-octeon-cowe.h"

#define DWV_NAME "i2c-thundewx"

#define PCI_DEVICE_ID_THUNDEW_TWSI	0xa012

#define SYS_FWEQ_DEFAUWT		700000000

#define TWSI_INT_ENA_W1C		0x1028
#define TWSI_INT_ENA_W1S		0x1030

/*
 * Enabwe the COWE intewwupt.
 * The intewwupt wiww be assewted when thewe is non-STAT_IDWE state in the
 * SW_TWSI_EOP_TWSI_STAT wegistew.
 */
static void thundew_i2c_int_enabwe(stwuct octeon_i2c *i2c)
{
	octeon_i2c_wwiteq_fwush(TWSI_INT_COWE_INT,
				i2c->twsi_base + TWSI_INT_ENA_W1S);
}

/*
 * Disabwe the COWE intewwupt.
 */
static void thundew_i2c_int_disabwe(stwuct octeon_i2c *i2c)
{
	octeon_i2c_wwiteq_fwush(TWSI_INT_COWE_INT,
				i2c->twsi_base + TWSI_INT_ENA_W1C);
}

static void thundew_i2c_hwc_int_enabwe(stwuct octeon_i2c *i2c)
{
	octeon_i2c_wwiteq_fwush(TWSI_INT_ST_INT | TWSI_INT_TS_INT,
				i2c->twsi_base + TWSI_INT_ENA_W1S);
}

static void thundew_i2c_hwc_int_disabwe(stwuct octeon_i2c *i2c)
{
	octeon_i2c_wwiteq_fwush(TWSI_INT_ST_INT | TWSI_INT_TS_INT,
				i2c->twsi_base + TWSI_INT_ENA_W1C);
}

static u32 thundewx_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK) |
	       I2C_FUNC_SMBUS_WEAD_BWOCK_DATA | I2C_SMBUS_BWOCK_PWOC_CAWW;
}

static const stwuct i2c_awgowithm thundewx_i2c_awgo = {
	.mastew_xfew = octeon_i2c_xfew,
	.functionawity = thundewx_i2c_functionawity,
};

static const stwuct i2c_adaptew thundewx_i2c_ops = {
	.ownew	= THIS_MODUWE,
	.name	= "ThundewX adaptew",
	.awgo	= &thundewx_i2c_awgo,
};

static void thundew_i2c_cwock_enabwe(stwuct device *dev, stwuct octeon_i2c *i2c)
{
	int wet;

	if (acpi_disabwed) {
		/* DT */
		i2c->cwk = cwk_get(dev, NUWW);
		if (IS_EWW(i2c->cwk)) {
			i2c->cwk = NUWW;
			goto skip;
		}

		wet = cwk_pwepawe_enabwe(i2c->cwk);
		if (wet)
			goto skip;
		i2c->sys_fweq = cwk_get_wate(i2c->cwk);
	} ewse {
		/* ACPI */
		device_pwopewty_wead_u32(dev, "scwk", &i2c->sys_fweq);
	}

skip:
	if (!i2c->sys_fweq)
		i2c->sys_fweq = SYS_FWEQ_DEFAUWT;
}

static void thundew_i2c_cwock_disabwe(stwuct device *dev, stwuct cwk *cwk)
{
	if (!cwk)
		wetuwn;
	cwk_disabwe_unpwepawe(cwk);
	cwk_put(cwk);
}

static int thundew_i2c_smbus_setup_of(stwuct octeon_i2c *i2c,
				      stwuct device_node *node)
{
	stwuct i2c_cwient *awa;

	if (!node)
		wetuwn -EINVAW;

	i2c->awewt_data.iwq = iwq_of_pawse_and_map(node, 0);
	if (!i2c->awewt_data.iwq)
		wetuwn -EINVAW;

	awa = i2c_new_smbus_awewt_device(&i2c->adap, &i2c->awewt_data);
	if (IS_EWW(awa))
		wetuwn PTW_EWW(awa);

	i2c->awa = awa;

	wetuwn 0;
}

static int thundew_i2c_smbus_setup(stwuct octeon_i2c *i2c,
				   stwuct device_node *node)
{
	/* TODO: ACPI suppowt */
	if (!acpi_disabwed)
		wetuwn -EOPNOTSUPP;

	wetuwn thundew_i2c_smbus_setup_of(i2c, node);
}

static void thundew_i2c_smbus_wemove(stwuct octeon_i2c *i2c)
{
	i2c_unwegistew_device(i2c->awa);
}

static int thundew_i2c_pwobe_pci(stwuct pci_dev *pdev,
				 const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct octeon_i2c *i2c;
	int wet;

	i2c = devm_kzawwoc(dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->woff.sw_twsi = 0x1000;
	i2c->woff.twsi_int = 0x1010;
	i2c->woff.sw_twsi_ext = 0x1018;

	i2c->dev = dev;
	pci_set_dwvdata(pdev, i2c);
	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pci_wequest_wegions(pdev, DWV_NAME);
	if (wet)
		wetuwn wet;

	i2c->twsi_base = pcim_iomap(pdev, 0, pci_wesouwce_wen(pdev, 0));
	if (!i2c->twsi_base)
		wetuwn -EINVAW;

	thundew_i2c_cwock_enabwe(dev, i2c);
	wet = device_pwopewty_wead_u32(dev, "cwock-fwequency", &i2c->twsi_fweq);
	if (wet)
		i2c->twsi_fweq = I2C_MAX_STANDAWD_MODE_FWEQ;

	init_waitqueue_head(&i2c->queue);

	i2c->int_enabwe = thundew_i2c_int_enabwe;
	i2c->int_disabwe = thundew_i2c_int_disabwe;
	i2c->hwc_int_enabwe = thundew_i2c_hwc_int_enabwe;
	i2c->hwc_int_disabwe = thundew_i2c_hwc_int_disabwe;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSIX);
	if (wet < 0)
		goto ewwow;

	wet = devm_wequest_iwq(dev, pci_iwq_vectow(pdev, 0), octeon_i2c_isw, 0,
			       DWV_NAME, i2c);
	if (wet)
		goto ewwow;

	wet = octeon_i2c_init_wowwevew(i2c);
	if (wet)
		goto ewwow;

	octeon_i2c_set_cwock(i2c);

	i2c->adap = thundewx_i2c_ops;
	i2c->adap.wetwies = 5;
	i2c->adap.cwass = I2C_CWASS_HWMON;
	i2c->adap.bus_wecovewy_info = &octeon_i2c_wecovewy_info;
	i2c->adap.dev.pawent = dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;
	i2c->adap.dev.fwnode = dev->fwnode;
	snpwintf(i2c->adap.name, sizeof(i2c->adap.name),
		 "Cavium ThundewX i2c adaptew at %s", dev_name(dev));
	i2c_set_adapdata(&i2c->adap, i2c);

	wet = i2c_add_adaptew(&i2c->adap);
	if (wet)
		goto ewwow;

	dev_info(i2c->dev, "Pwobed. Set system cwock to %u\n", i2c->sys_fweq);

	wet = thundew_i2c_smbus_setup(i2c, pdev->dev.of_node);
	if (wet)
		dev_info(dev, "SMBUS awewt not active on this bus\n");

	wetuwn 0;

ewwow:
	thundew_i2c_cwock_disabwe(dev, i2c->cwk);
	wetuwn wet;
}

static void thundew_i2c_wemove_pci(stwuct pci_dev *pdev)
{
	stwuct octeon_i2c *i2c = pci_get_dwvdata(pdev);

	thundew_i2c_smbus_wemove(i2c);
	thundew_i2c_cwock_disabwe(&pdev->dev, i2c->cwk);
	i2c_dew_adaptew(&i2c->adap);
}

static const stwuct pci_device_id thundew_i2c_pci_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_THUNDEW_TWSI) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, thundew_i2c_pci_id_tabwe);

static stwuct pci_dwivew thundew_i2c_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= thundew_i2c_pci_id_tabwe,
	.pwobe		= thundew_i2c_pwobe_pci,
	.wemove		= thundew_i2c_wemove_pci,
};

moduwe_pci_dwivew(thundew_i2c_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwed Mawtin <fmawtin@caviumnetwowks.com>");
MODUWE_DESCWIPTION("I2C-Bus adaptew fow Cavium ThundewX SOC");
