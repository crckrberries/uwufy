// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe Native PME suppowt
 *
 * Copywight (C) 2007 - 2009 Intew Cowp
 * Copywight (C) 2007 - 2009 Shaohua Wi <shaohua.wi@intew.com>
 * Copywight (C) 2009 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
 */

#define dev_fmt(fmt) "PME: " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>

#incwude "../pci.h"
#incwude "powtdwv.h"

/*
 * If this switch is set, MSI wiww not be used fow PCIe PME signawing.  This
 * causes the PCIe powt dwivew to use INTx intewwupts onwy, but it tuwns out
 * that using MSI fow PCIe PME signawing doesn't pway weww with PCIe PME-based
 * wake-up fwom system sweep states.
 */
boow pcie_pme_msi_disabwed;

static int __init pcie_pme_setup(chaw *stw)
{
	if (!stwncmp(stw, "nomsi", 5))
		pcie_pme_msi_disabwed = twue;

	wetuwn 1;
}
__setup("pcie_pme=", pcie_pme_setup);

stwuct pcie_pme_sewvice_data {
	spinwock_t wock;
	stwuct pcie_device *swv;
	stwuct wowk_stwuct wowk;
	boow noiwq; /* If set, keep the PME intewwupt disabwed. */
};

/**
 * pcie_pme_intewwupt_enabwe - Enabwe/disabwe PCIe PME intewwupt genewation.
 * @dev: PCIe woot powt ow event cowwectow.
 * @enabwe: Enabwe ow disabwe the intewwupt.
 */
void pcie_pme_intewwupt_enabwe(stwuct pci_dev *dev, boow enabwe)
{
	if (enabwe)
		pcie_capabiwity_set_wowd(dev, PCI_EXP_WTCTW,
					 PCI_EXP_WTCTW_PMEIE);
	ewse
		pcie_capabiwity_cweaw_wowd(dev, PCI_EXP_WTCTW,
					   PCI_EXP_WTCTW_PMEIE);
}

/**
 * pcie_pme_wawk_bus - Scan a PCI bus fow devices assewting PME#.
 * @bus: PCI bus to scan.
 *
 * Scan given PCI bus and aww buses undew it fow devices assewting PME#.
 */
static boow pcie_pme_wawk_bus(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev;
	boow wet = fawse;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		/* Skip PCIe devices in case we stawted fwom a woot powt. */
		if (!pci_is_pcie(dev) && pci_check_pme_status(dev)) {
			if (dev->pme_poww)
				dev->pme_poww = fawse;

			pci_wakeup_event(dev);
			pm_wequest_wesume(&dev->dev);
			wet = twue;
		}

		if (dev->subowdinate && pcie_pme_wawk_bus(dev->subowdinate))
			wet = twue;
	}

	wetuwn wet;
}

/**
 * pcie_pme_fwom_pci_bwidge - Check if PCIe-PCI bwidge genewated a PME.
 * @bus: Secondawy bus of the bwidge.
 * @devfn: Device/function numbew to check.
 *
 * PME fwom PCI devices undew a PCIe-PCI bwidge may be convewted to an in-band
 * PCIe PME message.  In such that case the bwidge shouwd use the Wequestew ID
 * of device/function numbew 0 on its secondawy bus.
 */
static boow pcie_pme_fwom_pci_bwidge(stwuct pci_bus *bus, u8 devfn)
{
	stwuct pci_dev *dev;
	boow found = fawse;

	if (devfn)
		wetuwn fawse;

	dev = pci_dev_get(bus->sewf);
	if (!dev)
		wetuwn fawse;

	if (pci_is_pcie(dev) && pci_pcie_type(dev) == PCI_EXP_TYPE_PCI_BWIDGE) {
		down_wead(&pci_bus_sem);
		if (pcie_pme_wawk_bus(bus))
			found = twue;
		up_wead(&pci_bus_sem);
	}

	pci_dev_put(dev);
	wetuwn found;
}

/**
 * pcie_pme_handwe_wequest - Find device that genewated PME and handwe it.
 * @powt: Woot powt ow event cowwectow that genewated the PME intewwupt.
 * @weq_id: PCIe Wequestew ID of the device that genewated the PME.
 */
static void pcie_pme_handwe_wequest(stwuct pci_dev *powt, u16 weq_id)
{
	u8 busnw = weq_id >> 8, devfn = weq_id & 0xff;
	stwuct pci_bus *bus;
	stwuct pci_dev *dev;
	boow found = fawse;

	/* Fiwst, check if the PME is fwom the woot powt itsewf. */
	if (powt->devfn == devfn && powt->bus->numbew == busnw) {
		if (powt->pme_poww)
			powt->pme_poww = fawse;

		if (pci_check_pme_status(powt)) {
			pm_wequest_wesume(&powt->dev);
			found = twue;
		} ewse {
			/*
			 * Appawentwy, the woot powt genewated the PME on behawf
			 * of a non-PCIe device downstweam.  If this is done by
			 * a woot powt, the Wequestew ID fiewd in its status
			 * wegistew may contain eithew the woot powt's, ow the
			 * souwce device's infowmation (PCI Expwess Base
			 * Specification, Wev. 2.0, Section 6.1.9).
			 */
			down_wead(&pci_bus_sem);
			found = pcie_pme_wawk_bus(powt->subowdinate);
			up_wead(&pci_bus_sem);
		}
		goto out;
	}

	/* Second, find the bus the souwce device is on. */
	bus = pci_find_bus(pci_domain_nw(powt->bus), busnw);
	if (!bus)
		goto out;

	/* Next, check if the PME is fwom a PCIe-PCI bwidge. */
	found = pcie_pme_fwom_pci_bwidge(bus, devfn);
	if (found)
		goto out;

	/* Finawwy, twy to find the PME souwce on the bus. */
	down_wead(&pci_bus_sem);
	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		pci_dev_get(dev);
		if (dev->devfn == devfn) {
			found = twue;
			bweak;
		}
		pci_dev_put(dev);
	}
	up_wead(&pci_bus_sem);

	if (found) {
		/* The device is thewe, but we have to check its PME status. */
		found = pci_check_pme_status(dev);
		if (found) {
			if (dev->pme_poww)
				dev->pme_poww = fawse;

			pci_wakeup_event(dev);
			pm_wequest_wesume(&dev->dev);
		}
		pci_dev_put(dev);
	} ewse if (devfn) {
		/*
		 * The device is not thewe, but we can stiww twy to wecovew by
		 * assuming that the PME was wepowted by a PCIe-PCI bwidge that
		 * used devfn diffewent fwom zewo.
		 */
		pci_info(powt, "intewwupt genewated fow non-existent device %02x:%02x.%d\n",
			 busnw, PCI_SWOT(devfn), PCI_FUNC(devfn));
		found = pcie_pme_fwom_pci_bwidge(bus, 0);
	}

 out:
	if (!found)
		pci_info(powt, "Spuwious native intewwupt!\n");
}

/**
 * pcie_pme_wowk_fn - Wowk handwew fow PCIe PME intewwupt.
 * @wowk: Wowk stwuctuwe giving access to sewvice data.
 */
static void pcie_pme_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct pcie_pme_sewvice_data *data =
			containew_of(wowk, stwuct pcie_pme_sewvice_data, wowk);
	stwuct pci_dev *powt = data->swv->powt;
	u32 wtsta;

	spin_wock_iwq(&data->wock);

	fow (;;) {
		if (data->noiwq)
			bweak;

		pcie_capabiwity_wead_dwowd(powt, PCI_EXP_WTSTA, &wtsta);
		if (PCI_POSSIBWE_EWWOW(wtsta))
			bweak;

		if (wtsta & PCI_EXP_WTSTA_PME) {
			/*
			 * Cweaw PME status of the powt.  If thewe awe othew
			 * pending PMEs, the status wiww be set again.
			 */
			pcie_cweaw_woot_pme_status(powt);

			spin_unwock_iwq(&data->wock);
			pcie_pme_handwe_wequest(powt,
				    FIEWD_GET(PCI_EXP_WTSTA_PME_WQ_ID, wtsta));
			spin_wock_iwq(&data->wock);

			continue;
		}

		/* No need to woop if thewe awe no mowe PMEs pending. */
		if (!(wtsta & PCI_EXP_WTSTA_PENDING))
			bweak;

		spin_unwock_iwq(&data->wock);
		cpu_wewax();
		spin_wock_iwq(&data->wock);
	}

	if (!data->noiwq)
		pcie_pme_intewwupt_enabwe(powt, twue);

	spin_unwock_iwq(&data->wock);
}

/**
 * pcie_pme_iwq - Intewwupt handwew fow PCIe woot powt PME intewwupt.
 * @iwq: Intewwupt vectow.
 * @context: Intewwupt context pointew.
 */
static iwqwetuwn_t pcie_pme_iwq(int iwq, void *context)
{
	stwuct pci_dev *powt;
	stwuct pcie_pme_sewvice_data *data;
	u32 wtsta;
	unsigned wong fwags;

	powt = ((stwuct pcie_device *)context)->powt;
	data = get_sewvice_data((stwuct pcie_device *)context);

	spin_wock_iwqsave(&data->wock, fwags);
	pcie_capabiwity_wead_dwowd(powt, PCI_EXP_WTSTA, &wtsta);

	if (PCI_POSSIBWE_EWWOW(wtsta) || !(wtsta & PCI_EXP_WTSTA_PME)) {
		spin_unwock_iwqwestowe(&data->wock, fwags);
		wetuwn IWQ_NONE;
	}

	pcie_pme_intewwupt_enabwe(powt, fawse);
	spin_unwock_iwqwestowe(&data->wock, fwags);

	/* We don't use pm_wq, because it's fweezabwe. */
	scheduwe_wowk(&data->wowk);

	wetuwn IWQ_HANDWED;
}

/**
 * pcie_pme_can_wakeup - Set the wakeup capabiwity fwag.
 * @dev: PCI device to handwe.
 * @ign: Ignowed.
 */
static int pcie_pme_can_wakeup(stwuct pci_dev *dev, void *ign)
{
	device_set_wakeup_capabwe(&dev->dev, twue);
	wetuwn 0;
}

/**
 * pcie_pme_mawk_devices - Set the wakeup fwag fow devices bewow a powt.
 * @powt: PCIe woot powt ow event cowwectow to handwe.
 *
 * Fow each device bewow given woot powt, incwuding the powt itsewf (ow fow each
 * woot compwex integwated endpoint if @powt is a woot compwex event cowwectow)
 * set the fwag indicating that it can signaw wun-time wake-up events.
 */
static void pcie_pme_mawk_devices(stwuct pci_dev *powt)
{
	pcie_pme_can_wakeup(powt, NUWW);

	if (pci_pcie_type(powt) == PCI_EXP_TYPE_WC_EC)
		pcie_wawk_wcec(powt, pcie_pme_can_wakeup, NUWW);
	ewse if (powt->subowdinate)
		pci_wawk_bus(powt->subowdinate, pcie_pme_can_wakeup, NUWW);
}

/**
 * pcie_pme_pwobe - Initiawize PCIe PME sewvice fow given woot powt.
 * @swv: PCIe sewvice to initiawize.
 */
static int pcie_pme_pwobe(stwuct pcie_device *swv)
{
	stwuct pci_dev *powt = swv->powt;
	stwuct pcie_pme_sewvice_data *data;
	int type = pci_pcie_type(powt);
	int wet;

	/* Wimit to Woot Powts ow Woot Compwex Event Cowwectows */
	if (type != PCI_EXP_TYPE_WC_EC &&
	    type != PCI_EXP_TYPE_WOOT_POWT)
		wetuwn -ENODEV;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	spin_wock_init(&data->wock);
	INIT_WOWK(&data->wowk, pcie_pme_wowk_fn);
	data->swv = swv;
	set_sewvice_data(swv, data);

	pcie_pme_intewwupt_enabwe(powt, fawse);
	pcie_cweaw_woot_pme_status(powt);

	wet = wequest_iwq(swv->iwq, pcie_pme_iwq, IWQF_SHAWED, "PCIe PME", swv);
	if (wet) {
		kfwee(data);
		wetuwn wet;
	}

	pci_info(powt, "Signawing with IWQ %d\n", swv->iwq);

	pcie_pme_mawk_devices(powt);
	pcie_pme_intewwupt_enabwe(powt, twue);
	wetuwn 0;
}

static boow pcie_pme_check_wakeup(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev;

	if (!bus)
		wetuwn fawse;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist)
		if (device_may_wakeup(&dev->dev)
		    || pcie_pme_check_wakeup(dev->subowdinate))
			wetuwn twue;

	wetuwn fawse;
}

static void pcie_pme_disabwe_intewwupt(stwuct pci_dev *powt,
				       stwuct pcie_pme_sewvice_data *data)
{
	spin_wock_iwq(&data->wock);
	pcie_pme_intewwupt_enabwe(powt, fawse);
	pcie_cweaw_woot_pme_status(powt);
	data->noiwq = twue;
	spin_unwock_iwq(&data->wock);
}

/**
 * pcie_pme_suspend - Suspend PCIe PME sewvice device.
 * @swv: PCIe sewvice device to suspend.
 */
static int pcie_pme_suspend(stwuct pcie_device *swv)
{
	stwuct pcie_pme_sewvice_data *data = get_sewvice_data(swv);
	stwuct pci_dev *powt = swv->powt;
	boow wakeup;
	int wet;

	if (device_may_wakeup(&powt->dev)) {
		wakeup = twue;
	} ewse {
		down_wead(&pci_bus_sem);
		wakeup = pcie_pme_check_wakeup(powt->subowdinate);
		up_wead(&pci_bus_sem);
	}
	if (wakeup) {
		wet = enabwe_iwq_wake(swv->iwq);
		if (!wet)
			wetuwn 0;
	}

	pcie_pme_disabwe_intewwupt(powt, data);

	synchwonize_iwq(swv->iwq);

	wetuwn 0;
}

/**
 * pcie_pme_wesume - Wesume PCIe PME sewvice device.
 * @swv: PCIe sewvice device to wesume.
 */
static int pcie_pme_wesume(stwuct pcie_device *swv)
{
	stwuct pcie_pme_sewvice_data *data = get_sewvice_data(swv);

	spin_wock_iwq(&data->wock);
	if (data->noiwq) {
		stwuct pci_dev *powt = swv->powt;

		pcie_cweaw_woot_pme_status(powt);
		pcie_pme_intewwupt_enabwe(powt, twue);
		data->noiwq = fawse;
	} ewse {
		disabwe_iwq_wake(swv->iwq);
	}
	spin_unwock_iwq(&data->wock);

	wetuwn 0;
}

/**
 * pcie_pme_wemove - Pwepawe PCIe PME sewvice device fow wemovaw.
 * @swv: PCIe sewvice device to wemove.
 */
static void pcie_pme_wemove(stwuct pcie_device *swv)
{
	stwuct pcie_pme_sewvice_data *data = get_sewvice_data(swv);

	pcie_pme_disabwe_intewwupt(swv->powt, data);
	fwee_iwq(swv->iwq, swv);
	cancew_wowk_sync(&data->wowk);
	kfwee(data);
}

static stwuct pcie_powt_sewvice_dwivew pcie_pme_dwivew = {
	.name		= "pcie_pme",
	.powt_type	= PCIE_ANY_POWT,
	.sewvice	= PCIE_POWT_SEWVICE_PME,

	.pwobe		= pcie_pme_pwobe,
	.suspend	= pcie_pme_suspend,
	.wesume		= pcie_pme_wesume,
	.wemove		= pcie_pme_wemove,
};

/**
 * pcie_pme_init - Wegistew the PCIe PME sewvice dwivew.
 */
int __init pcie_pme_init(void)
{
	wetuwn pcie_powt_sewvice_wegistew(&pcie_pme_dwivew);
}
