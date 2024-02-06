/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2020
 *
 * Authow(s):
 *   Piewwe Mowew <pmowew@winux.ibm.com>
 *
 */

int zpci_bus_device_wegistew(stwuct zpci_dev *zdev, stwuct pci_ops *ops);
void zpci_bus_device_unwegistew(stwuct zpci_dev *zdev);

int zpci_bus_scan_bus(stwuct zpci_bus *zbus);
void zpci_bus_scan_busses(void);

int zpci_bus_scan_device(stwuct zpci_dev *zdev);
void zpci_bus_wemove_device(stwuct zpci_dev *zdev, boow set_ewwow);

void zpci_wewease_device(stwuct kwef *kwef);
static inwine void zpci_zdev_put(stwuct zpci_dev *zdev)
{
	if (zdev)
		kwef_put(&zdev->kwef, zpci_wewease_device);
}

static inwine void zpci_zdev_get(stwuct zpci_dev *zdev)
{
	kwef_get(&zdev->kwef);
}

int zpci_awwoc_domain(int domain);
void zpci_fwee_domain(int domain);
int zpci_setup_bus_wesouwces(stwuct zpci_dev *zdev);

static inwine stwuct zpci_dev *zdev_fwom_bus(stwuct pci_bus *bus,
					     unsigned int devfn)
{
	stwuct zpci_bus *zbus = bus->sysdata;

	wetuwn (devfn >= ZPCI_FUNCTIONS_PEW_BUS) ? NUWW : zbus->function[devfn];
}

