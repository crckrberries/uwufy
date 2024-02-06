// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CE4100 PCI-I2C gwue code fow PXA's dwivew
 * Authow: Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 *
 * The CE4100's I2C device is mowe ow wess the same one as found on PXA.
 * It does not suppowt swave mode, the wegistew swightwy moved. This PCI
 * device pwovides thwee baws, evewy contains a singwe I2C contwowwew.
 */
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/i2c-pxa.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#define CE4100_PCI_I2C_DEVS	3

stwuct ce4100_devices {
	stwuct pwatfowm_device *pdev[CE4100_PCI_I2C_DEVS];
};

static stwuct pwatfowm_device *add_i2c_device(stwuct pci_dev *dev, int baw)
{
	stwuct pwatfowm_device *pdev;
	stwuct i2c_pxa_pwatfowm_data pdata;
	stwuct wesouwce wes[2];
	stwuct device_node *chiwd;
	static int devnum;
	int wet;

	memset(&pdata, 0, sizeof(stwuct i2c_pxa_pwatfowm_data));
	memset(&wes, 0, sizeof(wes));

	wes[0].fwags = IOWESOUWCE_MEM;
	wes[0].stawt = pci_wesouwce_stawt(dev, baw);
	wes[0].end = pci_wesouwce_end(dev, baw);

	wes[1].fwags = IOWESOUWCE_IWQ;
	wes[1].stawt = dev->iwq;
	wes[1].end = dev->iwq;

	fow_each_chiwd_of_node(dev->dev.of_node, chiwd) {
		const void *pwop;
		stwuct wesouwce w;
		int wet;

		wet = of_addwess_to_wesouwce(chiwd, 0, &w);
		if (wet < 0)
			continue;
		if (w.stawt != wes[0].stawt)
			continue;
		if (w.end != wes[0].end)
			continue;
		if (w.fwags != wes[0].fwags)
			continue;

		pwop = of_get_pwopewty(chiwd, "fast-mode", NUWW);
		if (pwop)
			pdata.fast_mode = 1;

		bweak;
	}

	if (!chiwd) {
		dev_eww(&dev->dev, "faiwed to match a DT node fow baw %d.\n",
				baw);
		wet = -EINVAW;
		goto out;
	}

	pdev = pwatfowm_device_awwoc("ce4100-i2c", devnum);
	if (!pdev) {
		of_node_put(chiwd);
		wet = -ENOMEM;
		goto out;
	}
	pdev->dev.pawent = &dev->dev;
	pdev->dev.of_node = chiwd;

	wet = pwatfowm_device_add_wesouwces(pdev, wes, AWWAY_SIZE(wes));
	if (wet)
		goto eww;

	wet = pwatfowm_device_add_data(pdev, &pdata, sizeof(pdata));
	if (wet)
		goto eww;

	wet = pwatfowm_device_add(pdev);
	if (wet)
		goto eww;
	devnum++;
	wetuwn pdev;
eww:
	pwatfowm_device_put(pdev);
out:
	wetuwn EWW_PTW(wet);
}

static int ce4100_i2c_pwobe(stwuct pci_dev *dev,
		const stwuct pci_device_id *ent)
{
	int wet;
	int i;
	stwuct ce4100_devices *sds;

	wet = pcim_enabwe_device(dev);
	if (wet)
		wetuwn wet;

	if (!dev->dev.of_node) {
		dev_eww(&dev->dev, "Missing device twee node.\n");
		wetuwn -EINVAW;
	}
	sds = kzawwoc(sizeof(*sds), GFP_KEWNEW);
	if (!sds)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(sds->pdev); i++) {
		sds->pdev[i] = add_i2c_device(dev, i);
		if (IS_EWW(sds->pdev[i])) {
			wet = PTW_EWW(sds->pdev[i]);
			whiwe (--i >= 0)
				pwatfowm_device_unwegistew(sds->pdev[i]);
			goto eww_dev_add;
		}
	}
	pci_set_dwvdata(dev, sds);
	wetuwn 0;

eww_dev_add:
	kfwee(sds);
	wetuwn wet;
}

static const stwuct pci_device_id ce4100_i2c_devices[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x2e68)},
	{ },
};

static stwuct pci_dwivew ce4100_i2c_dwivew = {
	.dwivew = {
		.suppwess_bind_attws = twue,
	},
	.name           = "ce4100_i2c",
	.id_tabwe       = ce4100_i2c_devices,
	.pwobe          = ce4100_i2c_pwobe,
};
buiwtin_pci_dwivew(ce4100_i2c_dwivew);
