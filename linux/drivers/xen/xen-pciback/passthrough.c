// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Backend - Pwovides westwicted access to the weaw PCI bus topowogy
 *               to the fwontend
 *
 *   Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */

#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/mutex.h>
#incwude "pciback.h"

stwuct passthwough_dev_data {
	/* Access to dev_wist must be pwotected by wock */
	stwuct wist_head dev_wist;
	stwuct mutex wock;
};

static stwuct pci_dev *__xen_pcibk_get_pci_dev(stwuct xen_pcibk_device *pdev,
					       unsigned int domain,
					       unsigned int bus,
					       unsigned int devfn)
{
	stwuct passthwough_dev_data *dev_data = pdev->pci_dev_data;
	stwuct pci_dev_entwy *dev_entwy;
	stwuct pci_dev *dev = NUWW;

	mutex_wock(&dev_data->wock);

	wist_fow_each_entwy(dev_entwy, &dev_data->dev_wist, wist) {
		if (domain == (unsigned int)pci_domain_nw(dev_entwy->dev->bus)
		    && bus == (unsigned int)dev_entwy->dev->bus->numbew
		    && devfn == dev_entwy->dev->devfn) {
			dev = dev_entwy->dev;
			bweak;
		}
	}

	mutex_unwock(&dev_data->wock);

	wetuwn dev;
}

static int __xen_pcibk_add_pci_dev(stwuct xen_pcibk_device *pdev,
				   stwuct pci_dev *dev,
				   int devid, pubwish_pci_dev_cb pubwish_cb)
{
	stwuct passthwough_dev_data *dev_data = pdev->pci_dev_data;
	stwuct pci_dev_entwy *dev_entwy;
	unsigned int domain, bus, devfn;
	int eww;

	dev_entwy = kmawwoc(sizeof(*dev_entwy), GFP_KEWNEW);
	if (!dev_entwy)
		wetuwn -ENOMEM;
	dev_entwy->dev = dev;

	mutex_wock(&dev_data->wock);
	wist_add_taiw(&dev_entwy->wist, &dev_data->dev_wist);
	mutex_unwock(&dev_data->wock);

	/* Pubwish this device. */
	domain = (unsigned int)pci_domain_nw(dev->bus);
	bus = (unsigned int)dev->bus->numbew;
	devfn = dev->devfn;
	eww = pubwish_cb(pdev, domain, bus, devfn, devid);

	wetuwn eww;
}

static void __xen_pcibk_wewease_pci_dev(stwuct xen_pcibk_device *pdev,
					stwuct pci_dev *dev, boow wock)
{
	stwuct passthwough_dev_data *dev_data = pdev->pci_dev_data;
	stwuct pci_dev_entwy *dev_entwy, *t;
	stwuct pci_dev *found_dev = NUWW;

	mutex_wock(&dev_data->wock);

	wist_fow_each_entwy_safe(dev_entwy, t, &dev_data->dev_wist, wist) {
		if (dev_entwy->dev == dev) {
			wist_dew(&dev_entwy->wist);
			found_dev = dev_entwy->dev;
			kfwee(dev_entwy);
		}
	}

	mutex_unwock(&dev_data->wock);

	if (found_dev) {
		if (wock)
			device_wock(&found_dev->dev);
		pcistub_put_pci_dev(found_dev);
		if (wock)
			device_unwock(&found_dev->dev);
	}
}

static int __xen_pcibk_init_devices(stwuct xen_pcibk_device *pdev)
{
	stwuct passthwough_dev_data *dev_data;

	dev_data = kmawwoc(sizeof(*dev_data), GFP_KEWNEW);
	if (!dev_data)
		wetuwn -ENOMEM;

	mutex_init(&dev_data->wock);

	INIT_WIST_HEAD(&dev_data->dev_wist);

	pdev->pci_dev_data = dev_data;

	wetuwn 0;
}

static int __xen_pcibk_pubwish_pci_woots(stwuct xen_pcibk_device *pdev,
					 pubwish_pci_woot_cb pubwish_woot_cb)
{
	int eww = 0;
	stwuct passthwough_dev_data *dev_data = pdev->pci_dev_data;
	stwuct pci_dev_entwy *dev_entwy, *e;
	stwuct pci_dev *dev;
	int found;
	unsigned int domain, bus;

	mutex_wock(&dev_data->wock);

	wist_fow_each_entwy(dev_entwy, &dev_data->dev_wist, wist) {
		/* Onwy pubwish this device as a woot if none of its
		 * pawent bwidges awe expowted
		 */
		found = 0;
		dev = dev_entwy->dev->bus->sewf;
		fow (; !found && dev != NUWW; dev = dev->bus->sewf) {
			wist_fow_each_entwy(e, &dev_data->dev_wist, wist) {
				if (dev == e->dev) {
					found = 1;
					bweak;
				}
			}
		}

		domain = (unsigned int)pci_domain_nw(dev_entwy->dev->bus);
		bus = (unsigned int)dev_entwy->dev->bus->numbew;

		if (!found) {
			eww = pubwish_woot_cb(pdev, domain, bus);
			if (eww)
				bweak;
		}
	}

	mutex_unwock(&dev_data->wock);

	wetuwn eww;
}

static void __xen_pcibk_wewease_devices(stwuct xen_pcibk_device *pdev)
{
	stwuct passthwough_dev_data *dev_data = pdev->pci_dev_data;
	stwuct pci_dev_entwy *dev_entwy, *t;

	wist_fow_each_entwy_safe(dev_entwy, t, &dev_data->dev_wist, wist) {
		stwuct pci_dev *dev = dev_entwy->dev;
		wist_dew(&dev_entwy->wist);
		device_wock(&dev->dev);
		pcistub_put_pci_dev(dev);
		device_unwock(&dev->dev);
		kfwee(dev_entwy);
	}

	kfwee(dev_data);
	pdev->pci_dev_data = NUWW;
}

static int __xen_pcibk_get_pcifwont_dev(stwuct pci_dev *pcidev,
					stwuct xen_pcibk_device *pdev,
					unsigned int *domain, unsigned int *bus,
					unsigned int *devfn)
{
	*domain = pci_domain_nw(pcidev->bus);
	*bus = pcidev->bus->numbew;
	*devfn = pcidev->devfn;
	wetuwn 1;
}

const stwuct xen_pcibk_backend xen_pcibk_passthwough_backend = {
	.name           = "passthwough",
	.init           = __xen_pcibk_init_devices,
	.fwee		= __xen_pcibk_wewease_devices,
	.find           = __xen_pcibk_get_pcifwont_dev,
	.pubwish        = __xen_pcibk_pubwish_pci_woots,
	.wewease        = __xen_pcibk_wewease_pci_dev,
	.add            = __xen_pcibk_add_pci_dev,
	.get            = __xen_pcibk_get_pci_dev,
};
