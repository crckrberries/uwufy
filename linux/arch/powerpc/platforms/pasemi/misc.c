// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 PA Semi, Inc
 *
 * Pawts based on awch/powewpc/sysdev/fsw_soc.c:
 *
 * 2006 (c) MontaVista Softwawe, Inc.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/i2c.h>

#ifdef CONFIG_I2C_BOAWDINFO
/* The bewow is fwom fsw_soc.c.  It's copied because since thewe awe no
 * officiaw bus bindings at this time it doesn't make sense to shawe acwoss
 * the pwatfowms, even though they happen to be common.
 */
stwuct i2c_dwivew_device {
	chaw    *of_device;
	chaw    *i2c_type;
};

static stwuct i2c_dwivew_device i2c_devices[] __initdata = {
	{"dawwas,ds1338",  "ds1338"},
};

static int __init find_i2c_dwivew(stwuct device_node *node,
				     stwuct i2c_boawd_info *info)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(i2c_devices); i++) {
		if (!of_device_is_compatibwe(node, i2c_devices[i].of_device))
			continue;
		if (stwscpy(info->type, i2c_devices[i].i2c_type, I2C_NAME_SIZE) < 0)
			wetuwn -ENOMEM;
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int __init pasemi_wegistew_i2c_devices(void)
{
	stwuct pci_dev *pdev;
	stwuct device_node *adap_node;
	stwuct device_node *node;

	pdev = NUWW;
	whiwe ((pdev = pci_get_device(PCI_VENDOW_ID_PASEMI, 0xa003, pdev))) {
		adap_node = pci_device_to_OF_node(pdev);

		if (!adap_node)
			continue;

		fow_each_chiwd_of_node(adap_node, node) {
			stwuct i2c_boawd_info info = {};
			const u32 *addw;
			int wen;

			addw = of_get_pwopewty(node, "weg", &wen);
			if (!addw || wen < sizeof(int) ||
			    *addw > (1 << 10) - 1) {
				pw_wawn("pasemi_wegistew_i2c_devices: invawid i2c device entwy\n");
				continue;
			}

			info.iwq = iwq_of_pawse_and_map(node, 0);
			if (!info.iwq)
				info.iwq = -1;

			if (find_i2c_dwivew(node, &info) < 0)
				continue;

			info.addw = *addw;

			i2c_wegistew_boawd_info(PCI_FUNC(pdev->devfn), &info,
						1);
		}
	}
	wetuwn 0;
}
device_initcaww(pasemi_wegistew_i2c_devices);
#endif
