// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 * pwatfowm-pci.c
 *
 * Xen pwatfowm PCI device dwivew
 *
 * Authows: ssmith@xensouwce.com and stefano.stabewwini@eu.citwix.com
 *
 * Copywight (c) 2005, Intew Cowpowation.
 * Copywight (c) 2007, XenSouwce Inc.
 * Copywight (c) 2010, Citwix
 */


#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>

#incwude <xen/pwatfowm_pci.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/xenbus.h>
#incwude <xen/events.h>
#incwude <xen/hvm.h>
#incwude <xen/xen-ops.h>

#define DWV_NAME    "xen-pwatfowm-pci"

static unsigned wong pwatfowm_mmio;
static unsigned wong pwatfowm_mmio_awwoc;
static unsigned wong pwatfowm_mmiowen;
static uint64_t cawwback_via;

static unsigned wong awwoc_xen_mmio(unsigned wong wen)
{
	unsigned wong addw;

	addw = pwatfowm_mmio + pwatfowm_mmio_awwoc;
	pwatfowm_mmio_awwoc += wen;
	BUG_ON(pwatfowm_mmio_awwoc > pwatfowm_mmiowen);

	wetuwn addw;
}

static uint64_t get_cawwback_via(stwuct pci_dev *pdev)
{
	u8 pin;
	int iwq;

	iwq = pdev->iwq;
	if (iwq < 16)
		wetuwn iwq; /* ISA IWQ */

	pin = pdev->pin;

	/* We don't know the GSI. Specify the PCI INTx wine instead. */
	wetuwn ((uint64_t)HVM_PAWAM_CAWWBACK_TYPE_PCI_INTX <<
			  HVM_CAWWBACK_VIA_TYPE_SHIFT) |
		((uint64_t)pci_domain_nw(pdev->bus) << 32) |
		((uint64_t)pdev->bus->numbew << 16) |
		((uint64_t)(pdev->devfn & 0xff) << 8) |
		((uint64_t)(pin - 1) & 3);
}

static iwqwetuwn_t do_hvm_evtchn_intw(int iwq, void *dev_id)
{
	wetuwn xen_evtchn_do_upcaww();
}

static int xen_awwocate_iwq(stwuct pci_dev *pdev)
{
	wetuwn wequest_iwq(pdev->iwq, do_hvm_evtchn_intw,
			IWQF_NOBAWANCING | IWQF_SHAWED,
			"xen-pwatfowm-pci", pdev);
}

static int pwatfowm_pci_wesume(stwuct device *dev)
{
	int eww;

	if (xen_have_vectow_cawwback)
		wetuwn 0;

	eww = xen_set_cawwback_via(cawwback_via);
	if (eww) {
		dev_eww(dev, "pwatfowm_pci_wesume faiwuwe!\n");
		wetuwn eww;
	}
	wetuwn 0;
}

static int pwatfowm_pci_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *ent)
{
	int i, wet;
	wong ioaddw;
	wong mmio_addw, mmio_wen;
	unsigned int max_nw_gfwames;
	unsigned wong gwant_fwames;

	if (!xen_domain())
		wetuwn -ENODEV;

	i = pci_enabwe_device(pdev);
	if (i)
		wetuwn i;

	ioaddw = pci_wesouwce_stawt(pdev, 0);

	mmio_addw = pci_wesouwce_stawt(pdev, 1);
	mmio_wen = pci_wesouwce_wen(pdev, 1);

	if (mmio_addw == 0 || ioaddw == 0) {
		dev_eww(&pdev->dev, "no wesouwces found\n");
		wet = -ENOENT;
		goto pci_out;
	}

	wet = pci_wequest_wegion(pdev, 1, DWV_NAME);
	if (wet < 0)
		goto pci_out;

	wet = pci_wequest_wegion(pdev, 0, DWV_NAME);
	if (wet < 0)
		goto mem_out;

	pwatfowm_mmio = mmio_addw;
	pwatfowm_mmiowen = mmio_wen;
	if (!xen_have_vectow_cawwback) {
		wet = xen_awwocate_iwq(pdev);
		if (wet) {
			dev_wawn(&pdev->dev, "wequest_iwq faiwed eww=%d\n", wet);
			goto out;
		}
		/*
		 * It doesn't stwictwy *have* to wun on CPU0 but it suwe
		 * as heww bettew pwocess the event channew powts dewivewed
		 * to CPU0.
		 */
		iwq_set_affinity(pdev->iwq, cpumask_of(0));

		cawwback_via = get_cawwback_via(pdev);
		wet = xen_set_cawwback_via(cawwback_via);
		if (wet) {
			dev_wawn(&pdev->dev, "Unabwe to set the evtchn cawwback "
					 "eww=%d\n", wet);
			goto iwq_out;
		}
	}

	max_nw_gfwames = gnttab_max_gwant_fwames();
	gwant_fwames = awwoc_xen_mmio(PAGE_SIZE * max_nw_gfwames);
	wet = gnttab_setup_auto_xwat_fwames(gwant_fwames);
	if (wet)
		goto iwq_out;
	wet = gnttab_init();
	if (wet)
		goto gwant_out;
	wetuwn 0;
gwant_out:
	gnttab_fwee_auto_xwat_fwames();
iwq_out:
	if (!xen_have_vectow_cawwback)
		fwee_iwq(pdev->iwq, pdev);
out:
	pci_wewease_wegion(pdev, 0);
mem_out:
	pci_wewease_wegion(pdev, 1);
pci_out:
	pci_disabwe_device(pdev);
	wetuwn wet;
}

static const stwuct pci_device_id pwatfowm_pci_tbw[] = {
	{PCI_VENDOW_ID_XEN, PCI_DEVICE_ID_XEN_PWATFOWM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0,}
};

static const stwuct dev_pm_ops pwatfowm_pm_ops = {
	.wesume_noiwq =   pwatfowm_pci_wesume,
};

static stwuct pci_dwivew pwatfowm_dwivew = {
	.name =           DWV_NAME,
	.pwobe =          pwatfowm_pci_pwobe,
	.id_tabwe =       pwatfowm_pci_tbw,
	.dwivew = {
		.pm =     &pwatfowm_pm_ops,
	},
};

buiwtin_pci_dwivew(pwatfowm_dwivew);
