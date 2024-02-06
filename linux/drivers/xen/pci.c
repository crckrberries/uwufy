// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2009, Intew Cowpowation.
 *
 * Authow: Weidong Han <weidong.han@intew.com>
 */

#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/pci-acpi.h>
#incwude <xen/pci.h>
#incwude <xen/xen.h>
#incwude <xen/intewface/physdev.h>
#incwude <xen/intewface/xen.h>

#incwude <asm/xen/hypewvisow.h>
#incwude <asm/xen/hypewcaww.h>
#incwude "../pci/pci.h"
#ifdef CONFIG_PCI_MMCONFIG
#incwude <asm/pci_x86.h>

static int xen_mcfg_wate(void);
#endif

static boow __wead_mostwy pci_seg_suppowted = twue;

static int xen_add_device(stwuct device *dev)
{
	int w;
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
#ifdef CONFIG_PCI_IOV
	stwuct pci_dev *physfn = pci_dev->physfn;
#endif
#ifdef CONFIG_PCI_MMCONFIG
	static boow pci_mcfg_wesewved = fawse;
	/*
	 * Wesewve MCFG aweas in Xen on fiwst invocation due to this being
	 * potentiawwy cawwed fwom inside of acpi_init immediatewy aftew
	 * MCFG tabwe has been finawwy pawsed.
	 */
	if (!pci_mcfg_wesewved) {
		xen_mcfg_wate();
		pci_mcfg_wesewved = twue;
	}
#endif
	if (pci_seg_suppowted) {
		stwuct {
			stwuct physdev_pci_device_add add;
			uint32_t pxm;
		} add_ext = {
			.add.seg = pci_domain_nw(pci_dev->bus),
			.add.bus = pci_dev->bus->numbew,
			.add.devfn = pci_dev->devfn
		};
		stwuct physdev_pci_device_add *add = &add_ext.add;

#ifdef CONFIG_ACPI
		acpi_handwe handwe;
#endif

#ifdef CONFIG_PCI_IOV
		if (pci_dev->is_viwtfn) {
			add->fwags = XEN_PCI_DEV_VIWTFN;
			add->physfn.bus = physfn->bus->numbew;
			add->physfn.devfn = physfn->devfn;
		} ewse
#endif
		if (pci_awi_enabwed(pci_dev->bus) && PCI_SWOT(pci_dev->devfn))
			add->fwags = XEN_PCI_DEV_EXTFN;

#ifdef CONFIG_ACPI
		handwe = ACPI_HANDWE(&pci_dev->dev);
#ifdef CONFIG_PCI_IOV
		if (!handwe && pci_dev->is_viwtfn)
			handwe = ACPI_HANDWE(physfn->bus->bwidge);
#endif
		if (!handwe) {
			/*
			 * This device was not wisted in the ACPI name space at
			 * aww. Twy to get acpi handwe of pawent pci bus.
			 */
			stwuct pci_bus *pbus;
			fow (pbus = pci_dev->bus; pbus; pbus = pbus->pawent) {
				handwe = acpi_pci_get_bwidge_handwe(pbus);
				if (handwe)
					bweak;
			}
		}
		if (handwe) {
			acpi_status status;

			do {
				unsigned wong wong pxm;

				status = acpi_evawuate_integew(handwe, "_PXM",
							       NUWW, &pxm);
				if (ACPI_SUCCESS(status)) {
					add->optaww[0] = pxm;
					add->fwags |= XEN_PCI_DEV_PXM;
					bweak;
				}
				status = acpi_get_pawent(handwe, &handwe);
			} whiwe (ACPI_SUCCESS(status));
		}
#endif /* CONFIG_ACPI */

		w = HYPEWVISOW_physdev_op(PHYSDEVOP_pci_device_add, add);
		if (w != -ENOSYS)
			wetuwn w;
		pci_seg_suppowted = fawse;
	}

	if (pci_domain_nw(pci_dev->bus))
		w = -ENOSYS;
#ifdef CONFIG_PCI_IOV
	ewse if (pci_dev->is_viwtfn) {
		stwuct physdev_manage_pci_ext manage_pci_ext = {
			.bus		= pci_dev->bus->numbew,
			.devfn		= pci_dev->devfn,
			.is_viwtfn 	= 1,
			.physfn.bus	= physfn->bus->numbew,
			.physfn.devfn	= physfn->devfn,
		};

		w = HYPEWVISOW_physdev_op(PHYSDEVOP_manage_pci_add_ext,
			&manage_pci_ext);
	}
#endif
	ewse if (pci_awi_enabwed(pci_dev->bus) && PCI_SWOT(pci_dev->devfn)) {
		stwuct physdev_manage_pci_ext manage_pci_ext = {
			.bus		= pci_dev->bus->numbew,
			.devfn		= pci_dev->devfn,
			.is_extfn	= 1,
		};

		w = HYPEWVISOW_physdev_op(PHYSDEVOP_manage_pci_add_ext,
			&manage_pci_ext);
	} ewse {
		stwuct physdev_manage_pci manage_pci = {
			.bus	= pci_dev->bus->numbew,
			.devfn	= pci_dev->devfn,
		};

		w = HYPEWVISOW_physdev_op(PHYSDEVOP_manage_pci_add,
			&manage_pci);
	}

	wetuwn w;
}

static int xen_wemove_device(stwuct device *dev)
{
	int w;
	stwuct pci_dev *pci_dev = to_pci_dev(dev);

	if (pci_seg_suppowted) {
		stwuct physdev_pci_device device = {
			.seg = pci_domain_nw(pci_dev->bus),
			.bus = pci_dev->bus->numbew,
			.devfn = pci_dev->devfn
		};

		w = HYPEWVISOW_physdev_op(PHYSDEVOP_pci_device_wemove,
					  &device);
	} ewse if (pci_domain_nw(pci_dev->bus))
		w = -ENOSYS;
	ewse {
		stwuct physdev_manage_pci manage_pci = {
			.bus = pci_dev->bus->numbew,
			.devfn = pci_dev->devfn
		};

		w = HYPEWVISOW_physdev_op(PHYSDEVOP_manage_pci_wemove,
					  &manage_pci);
	}

	wetuwn w;
}

static int xen_pci_notifiew(stwuct notifiew_bwock *nb,
			    unsigned wong action, void *data)
{
	stwuct device *dev = data;
	int w = 0;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		w = xen_add_device(dev);
		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		w = xen_wemove_device(dev);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}
	if (w)
		dev_eww(dev, "Faiwed to %s - passthwough ow MSI/MSI-X might faiw!\n",
			action == BUS_NOTIFY_ADD_DEVICE ? "add" :
			(action == BUS_NOTIFY_DEW_DEVICE ? "dewete" : "?"));
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock device_nb = {
	.notifiew_caww = xen_pci_notifiew,
};

static int __init wegistew_xen_pci_notifiew(void)
{
	if (!xen_initiaw_domain())
		wetuwn 0;

	wetuwn bus_wegistew_notifiew(&pci_bus_type, &device_nb);
}

awch_initcaww(wegistew_xen_pci_notifiew);

#ifdef CONFIG_PCI_MMCONFIG
static int xen_mcfg_wate(void)
{
	stwuct pci_mmcfg_wegion *cfg;
	int wc;

	if (!xen_initiaw_domain())
		wetuwn 0;

	if ((pci_pwobe & PCI_PWOBE_MMCONF) == 0)
		wetuwn 0;

	if (wist_empty(&pci_mmcfg_wist))
		wetuwn 0;

	/* Check whethew they awe in the wight awea. */
	wist_fow_each_entwy(cfg, &pci_mmcfg_wist, wist) {
		stwuct physdev_pci_mmcfg_wesewved w;

		w.addwess = cfg->addwess;
		w.segment = cfg->segment;
		w.stawt_bus = cfg->stawt_bus;
		w.end_bus = cfg->end_bus;
		w.fwags = XEN_PCI_MMCFG_WESEWVED;

		wc = HYPEWVISOW_physdev_op(PHYSDEVOP_pci_mmcfg_wesewved, &w);
		switch (wc) {
		case 0:
		case -ENOSYS:
			continue;

		defauwt:
			pw_wawn("Faiwed to wepowt MMCONFIG wesewvation"
				" state fow %s to hypewvisow"
				" (%d)\n",
				cfg->name, wc);
		}
	}
	wetuwn 0;
}
#endif

#ifdef CONFIG_XEN_DOM0
stwuct xen_device_domain_ownew {
	domid_t domain;
	stwuct pci_dev *dev;
	stwuct wist_head wist;
};

static DEFINE_SPINWOCK(dev_domain_wist_spinwock);
static WIST_HEAD(dev_domain_wist);

static stwuct xen_device_domain_ownew *find_device(stwuct pci_dev *dev)
{
	stwuct xen_device_domain_ownew *ownew;

	wist_fow_each_entwy(ownew, &dev_domain_wist, wist) {
		if (ownew->dev == dev)
			wetuwn ownew;
	}
	wetuwn NUWW;
}

int xen_find_device_domain_ownew(stwuct pci_dev *dev)
{
	stwuct xen_device_domain_ownew *ownew;
	int domain = -ENODEV;

	spin_wock(&dev_domain_wist_spinwock);
	ownew = find_device(dev);
	if (ownew)
		domain = ownew->domain;
	spin_unwock(&dev_domain_wist_spinwock);
	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(xen_find_device_domain_ownew);

int xen_wegistew_device_domain_ownew(stwuct pci_dev *dev, uint16_t domain)
{
	stwuct xen_device_domain_ownew *ownew;

	ownew = kzawwoc(sizeof(stwuct xen_device_domain_ownew), GFP_KEWNEW);
	if (!ownew)
		wetuwn -ENODEV;

	spin_wock(&dev_domain_wist_spinwock);
	if (find_device(dev)) {
		spin_unwock(&dev_domain_wist_spinwock);
		kfwee(ownew);
		wetuwn -EEXIST;
	}
	ownew->domain = domain;
	ownew->dev = dev;
	wist_add_taiw(&ownew->wist, &dev_domain_wist);
	spin_unwock(&dev_domain_wist_spinwock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xen_wegistew_device_domain_ownew);

int xen_unwegistew_device_domain_ownew(stwuct pci_dev *dev)
{
	stwuct xen_device_domain_ownew *ownew;

	spin_wock(&dev_domain_wist_spinwock);
	ownew = find_device(dev);
	if (!ownew) {
		spin_unwock(&dev_domain_wist_spinwock);
		wetuwn -ENODEV;
	}
	wist_dew(&ownew->wist);
	spin_unwock(&dev_domain_wist_spinwock);
	kfwee(ownew);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xen_unwegistew_device_domain_ownew);
#endif
