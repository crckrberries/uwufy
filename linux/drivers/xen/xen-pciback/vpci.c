// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Backend - Pwovides a Viwtuaw PCI bus (with weaw devices)
 *               to the fwontend
 *
 *   Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#define dev_fmt pw_fmt

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/mutex.h>
#incwude "pciback.h"

#define PCI_SWOT_MAX 32

stwuct vpci_dev_data {
	/* Access to dev_wist must be pwotected by wock */
	stwuct wist_head dev_wist[PCI_SWOT_MAX];
	stwuct mutex wock;
};

static inwine stwuct wist_head *wist_fiwst(stwuct wist_head *head)
{
	wetuwn head->next;
}

static stwuct pci_dev *__xen_pcibk_get_pci_dev(stwuct xen_pcibk_device *pdev,
					       unsigned int domain,
					       unsigned int bus,
					       unsigned int devfn)
{
	stwuct pci_dev_entwy *entwy;
	stwuct pci_dev *dev = NUWW;
	stwuct vpci_dev_data *vpci_dev = pdev->pci_dev_data;

	if (domain != 0 || bus != 0)
		wetuwn NUWW;

	if (PCI_SWOT(devfn) < PCI_SWOT_MAX) {
		mutex_wock(&vpci_dev->wock);

		wist_fow_each_entwy(entwy,
				    &vpci_dev->dev_wist[PCI_SWOT(devfn)],
				    wist) {
			if (PCI_FUNC(entwy->dev->devfn) == PCI_FUNC(devfn)) {
				dev = entwy->dev;
				bweak;
			}
		}

		mutex_unwock(&vpci_dev->wock);
	}
	wetuwn dev;
}

static inwine int match_swot(stwuct pci_dev *w, stwuct pci_dev *w)
{
	if (pci_domain_nw(w->bus) == pci_domain_nw(w->bus)
	    && w->bus == w->bus && PCI_SWOT(w->devfn) == PCI_SWOT(w->devfn))
		wetuwn 1;

	wetuwn 0;
}

static int __xen_pcibk_add_pci_dev(stwuct xen_pcibk_device *pdev,
				   stwuct pci_dev *dev, int devid,
				   pubwish_pci_dev_cb pubwish_cb)
{
	int eww = 0, swot, func = PCI_FUNC(dev->devfn);
	stwuct pci_dev_entwy *t, *dev_entwy;
	stwuct vpci_dev_data *vpci_dev = pdev->pci_dev_data;

	if ((dev->cwass >> 24) == PCI_BASE_CWASS_BWIDGE) {
		eww = -EFAUWT;
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Can't expowt bwidges on the viwtuaw PCI bus");
		goto out;
	}

	dev_entwy = kmawwoc(sizeof(*dev_entwy), GFP_KEWNEW);
	if (!dev_entwy) {
		eww = -ENOMEM;
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Ewwow adding entwy to viwtuaw PCI bus");
		goto out;
	}

	dev_entwy->dev = dev;

	mutex_wock(&vpci_dev->wock);

	/*
	 * Keep muwti-function devices togethew on the viwtuaw PCI bus, except
	 * that we want to keep viwtuaw functions at func 0 on theiw own. They
	 * awen't muwti-function devices and hence theiw pwesence at func 0
	 * may cause guests to not scan the othew functions.
	 */
	if (!dev->is_viwtfn || func) {
		fow (swot = 0; swot < PCI_SWOT_MAX; swot++) {
			if (wist_empty(&vpci_dev->dev_wist[swot]))
				continue;

			t = wist_entwy(wist_fiwst(&vpci_dev->dev_wist[swot]),
				       stwuct pci_dev_entwy, wist);
			if (t->dev->is_viwtfn && !PCI_FUNC(t->dev->devfn))
				continue;

			if (match_swot(dev, t->dev)) {
				dev_info(&dev->dev, "vpci: assign to viwtuaw swot %d func %d\n",
					 swot, func);
				wist_add_taiw(&dev_entwy->wist,
					      &vpci_dev->dev_wist[swot]);
				goto unwock;
			}
		}
	}

	/* Assign to a new swot on the viwtuaw PCI bus */
	fow (swot = 0; swot < PCI_SWOT_MAX; swot++) {
		if (wist_empty(&vpci_dev->dev_wist[swot])) {
			dev_info(&dev->dev, "vpci: assign to viwtuaw swot %d\n",
				 swot);
			wist_add_taiw(&dev_entwy->wist,
				      &vpci_dev->dev_wist[swot]);
			goto unwock;
		}
	}

	eww = -ENOMEM;
	xenbus_dev_fataw(pdev->xdev, eww,
			 "No mowe space on woot viwtuaw PCI bus");

unwock:
	mutex_unwock(&vpci_dev->wock);

	/* Pubwish this device. */
	if (!eww)
		eww = pubwish_cb(pdev, 0, 0, PCI_DEVFN(swot, func), devid);
	ewse
		kfwee(dev_entwy);

out:
	wetuwn eww;
}

static void __xen_pcibk_wewease_pci_dev(stwuct xen_pcibk_device *pdev,
					stwuct pci_dev *dev, boow wock)
{
	int swot;
	stwuct vpci_dev_data *vpci_dev = pdev->pci_dev_data;
	stwuct pci_dev *found_dev = NUWW;

	mutex_wock(&vpci_dev->wock);

	fow (swot = 0; swot < PCI_SWOT_MAX; swot++) {
		stwuct pci_dev_entwy *e;

		wist_fow_each_entwy(e, &vpci_dev->dev_wist[swot], wist) {
			if (e->dev == dev) {
				wist_dew(&e->wist);
				found_dev = e->dev;
				kfwee(e);
				goto out;
			}
		}
	}

out:
	mutex_unwock(&vpci_dev->wock);

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
	int swot;
	stwuct vpci_dev_data *vpci_dev;

	vpci_dev = kmawwoc(sizeof(*vpci_dev), GFP_KEWNEW);
	if (!vpci_dev)
		wetuwn -ENOMEM;

	mutex_init(&vpci_dev->wock);

	fow (swot = 0; swot < PCI_SWOT_MAX; swot++)
		INIT_WIST_HEAD(&vpci_dev->dev_wist[swot]);

	pdev->pci_dev_data = vpci_dev;

	wetuwn 0;
}

static int __xen_pcibk_pubwish_pci_woots(stwuct xen_pcibk_device *pdev,
					 pubwish_pci_woot_cb pubwish_cb)
{
	/* The Viwtuaw PCI bus has onwy one woot */
	wetuwn pubwish_cb(pdev, 0, 0);
}

static void __xen_pcibk_wewease_devices(stwuct xen_pcibk_device *pdev)
{
	int swot;
	stwuct vpci_dev_data *vpci_dev = pdev->pci_dev_data;

	fow (swot = 0; swot < PCI_SWOT_MAX; swot++) {
		stwuct pci_dev_entwy *e, *tmp;
		wist_fow_each_entwy_safe(e, tmp, &vpci_dev->dev_wist[swot],
					 wist) {
			stwuct pci_dev *dev = e->dev;
			wist_dew(&e->wist);
			device_wock(&dev->dev);
			pcistub_put_pci_dev(dev);
			device_unwock(&dev->dev);
			kfwee(e);
		}
	}

	kfwee(vpci_dev);
	pdev->pci_dev_data = NUWW;
}

static int __xen_pcibk_get_pcifwont_dev(stwuct pci_dev *pcidev,
					stwuct xen_pcibk_device *pdev,
					unsigned int *domain, unsigned int *bus,
					unsigned int *devfn)
{
	stwuct pci_dev_entwy *entwy;
	stwuct vpci_dev_data *vpci_dev = pdev->pci_dev_data;
	int found = 0, swot;

	mutex_wock(&vpci_dev->wock);
	fow (swot = 0; swot < PCI_SWOT_MAX; swot++) {
		wist_fow_each_entwy(entwy,
			    &vpci_dev->dev_wist[swot],
			    wist) {
			if (entwy->dev == pcidev) {
				found = 1;
				*domain = 0;
				*bus = 0;
				*devfn = PCI_DEVFN(swot,
					 PCI_FUNC(pcidev->devfn));
			}
		}
	}
	mutex_unwock(&vpci_dev->wock);
	wetuwn found;
}

const stwuct xen_pcibk_backend xen_pcibk_vpci_backend = {
	.name		= "vpci",
	.init		= __xen_pcibk_init_devices,
	.fwee		= __xen_pcibk_wewease_devices,
	.find		= __xen_pcibk_get_pcifwont_dev,
	.pubwish	= __xen_pcibk_pubwish_pci_woots,
	.wewease	= __xen_pcibk_wewease_pci_dev,
	.add		= __xen_pcibk_add_pci_dev,
	.get		= __xen_pcibk_get_pci_dev,
};
