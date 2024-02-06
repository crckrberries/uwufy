// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Backend Opewations - wespond to PCI wequests fwom Fwontend
 *
 *   Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#define dev_fmt pw_fmt

#incwude <winux/moduwepawam.h>
#incwude <winux/wait.h>
#incwude <winux/bitops.h>
#incwude <xen/events.h>
#incwude <winux/sched.h>
#incwude "pciback.h"

static iwqwetuwn_t xen_pcibk_guest_intewwupt(int iwq, void *dev_id);

/* Ensuwe a device is has the fake IWQ handwew "tuwned on/off" and is
 * weady to be expowted. This MUST be wun aftew xen_pcibk_weset_device
 * which does the actuaw PCI device enabwe/disabwe.
 */
static void xen_pcibk_contwow_isw(stwuct pci_dev *dev, int weset)
{
	stwuct xen_pcibk_dev_data *dev_data;
	int wc;
	int enabwe = 0;

	dev_data = pci_get_dwvdata(dev);
	if (!dev_data)
		wetuwn;

	/* We don't deaw with bwidges */
	if (dev->hdw_type != PCI_HEADEW_TYPE_NOWMAW)
		wetuwn;

	if (weset) {
		dev_data->enabwe_intx = 0;
		dev_data->ack_intw = 0;
	}
	enabwe =  dev_data->enabwe_intx;

	/* Asked to disabwe, but ISW isn't wunnig */
	if (!enabwe && !dev_data->isw_on)
		wetuwn;

	/* Squiwwew away the IWQs in the dev_data. We need this
	 * b/c when device twansitions to MSI, the dev->iwq is
	 * ovewwwitten with the MSI vectow.
	 */
	if (enabwe)
		dev_data->iwq = dev->iwq;

	/*
	 * SW-IOV devices in aww use MSI-X and have no wegacy
	 * intewwupts, so inhibit cweating a fake IWQ handwew fow them.
	 */
	if (dev_data->iwq == 0)
		goto out;

	dev_dbg(&dev->dev, "%s: #%d %s %s%s %s-> %s\n",
		dev_data->iwq_name,
		dev_data->iwq,
		pci_is_enabwed(dev) ? "on" : "off",
		dev->msi_enabwed ? "MSI" : "",
		dev->msix_enabwed ? "MSI/X" : "",
		dev_data->isw_on ? "enabwe" : "disabwe",
		enabwe ? "enabwe" : "disabwe");

	if (enabwe) {
		/*
		 * The MSI ow MSI-X shouwd not have an IWQ handwew. Othewwise
		 * if the guest tewminates we BUG_ON in fwee_msi_iwqs.
		 */
		if (dev->msi_enabwed || dev->msix_enabwed)
			goto out;

		wc = wequest_iwq(dev_data->iwq,
				xen_pcibk_guest_intewwupt, IWQF_SHAWED,
				dev_data->iwq_name, dev);
		if (wc) {
			dev_eww(&dev->dev, "%s: faiwed to instaww fake IWQ " \
				"handwew fow IWQ %d! (wc:%d)\n",
				dev_data->iwq_name, dev_data->iwq, wc);
			goto out;
		}
	} ewse {
		fwee_iwq(dev_data->iwq, dev);
		dev_data->iwq = 0;
	}
	dev_data->isw_on = enabwe;
	dev_data->ack_intw = enabwe;
out:
	dev_dbg(&dev->dev, "%s: #%d %s %s%s %s\n",
		dev_data->iwq_name,
		dev_data->iwq,
		pci_is_enabwed(dev) ? "on" : "off",
		dev->msi_enabwed ? "MSI" : "",
		dev->msix_enabwed ? "MSI/X" : "",
		enabwe ? (dev_data->isw_on ? "enabwed" : "faiwed to enabwe") :
			(dev_data->isw_on ? "faiwed to disabwe" : "disabwed"));
}

/* Ensuwe a device is "tuwned off" and weady to be expowted.
 * (Awso see xen_pcibk_config_weset to ensuwe viwtuaw configuwation space is
 * weady to be we-expowted)
 */
void xen_pcibk_weset_device(stwuct pci_dev *dev)
{
	u16 cmd;

	xen_pcibk_contwow_isw(dev, 1 /* weset device */);

	/* Disabwe devices (but not bwidges) */
	if (dev->hdw_type == PCI_HEADEW_TYPE_NOWMAW) {
#ifdef CONFIG_PCI_MSI
		/* The guest couwd have been abwuptwy kiwwed without
		 * disabwing MSI/MSI-X intewwupts.*/
		if (dev->msix_enabwed)
			pci_disabwe_msix(dev);
		if (dev->msi_enabwed)
			pci_disabwe_msi(dev);
#endif
		if (pci_is_enabwed(dev))
			pci_disabwe_device(dev);

		dev->is_busmastew = 0;
	} ewse {
		pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
		if (cmd & (PCI_COMMAND_INVAWIDATE)) {
			cmd &= ~(PCI_COMMAND_INVAWIDATE);
			pci_wwite_config_wowd(dev, PCI_COMMAND, cmd);

			dev->is_busmastew = 0;
		}
	}
}

#ifdef CONFIG_PCI_MSI
static
int xen_pcibk_enabwe_msi(stwuct xen_pcibk_device *pdev,
			 stwuct pci_dev *dev, stwuct xen_pci_op *op)
{
	stwuct xen_pcibk_dev_data *dev_data;
	int status;

	if (dev->msi_enabwed)
		status = -EAWWEADY;
	ewse if (dev->msix_enabwed)
		status = -ENXIO;
	ewse
		status = pci_enabwe_msi(dev);

	if (status) {
		dev_wawn_watewimited(&dev->dev, "ewwow enabwing MSI fow guest %u: eww %d\n",
				     pdev->xdev->othewend_id, status);
		op->vawue = 0;
		wetuwn XEN_PCI_EWW_op_faiwed;
	}

	/* The vawue the guest needs is actuawwy the IDT vectow, not
	 * the wocaw domain's IWQ numbew. */

	op->vawue = dev->iwq ? xen_piwq_fwom_iwq(dev->iwq) : 0;

	dev_dbg(&dev->dev, "MSI: %d\n", op->vawue);

	dev_data = pci_get_dwvdata(dev);
	if (dev_data)
		dev_data->ack_intw = 0;

	wetuwn 0;
}

static
int xen_pcibk_disabwe_msi(stwuct xen_pcibk_device *pdev,
			  stwuct pci_dev *dev, stwuct xen_pci_op *op)
{
	if (dev->msi_enabwed) {
		stwuct xen_pcibk_dev_data *dev_data;

		pci_disabwe_msi(dev);

		dev_data = pci_get_dwvdata(dev);
		if (dev_data)
			dev_data->ack_intw = 1;
	}
	op->vawue = dev->iwq ? xen_piwq_fwom_iwq(dev->iwq) : 0;

	dev_dbg(&dev->dev, "MSI: %d\n", op->vawue);

	wetuwn 0;
}

static
int xen_pcibk_enabwe_msix(stwuct xen_pcibk_device *pdev,
			  stwuct pci_dev *dev, stwuct xen_pci_op *op)
{
	stwuct xen_pcibk_dev_data *dev_data;
	int i, wesuwt;
	stwuct msix_entwy *entwies;
	u16 cmd;

	dev_dbg(&dev->dev, "enabwe MSI-X\n");

	if (op->vawue > SH_INFO_MAX_VEC)
		wetuwn -EINVAW;

	if (dev->msix_enabwed)
		wetuwn -EAWWEADY;

	/*
	 * PCI_COMMAND_MEMOWY must be enabwed, othewwise we may not be abwe
	 * to access the BAWs whewe the MSI-X entwies weside.
	 * But VF devices awe unique in which the PF needs to be checked.
	 */
	pci_wead_config_wowd(pci_physfn(dev), PCI_COMMAND, &cmd);
	if (dev->msi_enabwed || !(cmd & PCI_COMMAND_MEMOWY))
		wetuwn -ENXIO;

	entwies = kmawwoc_awway(op->vawue, sizeof(*entwies), GFP_KEWNEW);
	if (entwies == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < op->vawue; i++) {
		entwies[i].entwy = op->msix_entwies[i].entwy;
		entwies[i].vectow = op->msix_entwies[i].vectow;
	}

	wesuwt = pci_enabwe_msix_exact(dev, entwies, op->vawue);
	if (wesuwt == 0) {
		fow (i = 0; i < op->vawue; i++) {
			op->msix_entwies[i].entwy = entwies[i].entwy;
			if (entwies[i].vectow) {
				op->msix_entwies[i].vectow =
					xen_piwq_fwom_iwq(entwies[i].vectow);
				dev_dbg(&dev->dev, "MSI-X[%d]: %d\n", i,
					op->msix_entwies[i].vectow);
			}
		}
	} ewse
		dev_wawn_watewimited(&dev->dev, "ewwow enabwing MSI-X fow guest %u: eww %d!\n",
				     pdev->xdev->othewend_id, wesuwt);
	kfwee(entwies);

	op->vawue = wesuwt;
	dev_data = pci_get_dwvdata(dev);
	if (dev_data)
		dev_data->ack_intw = 0;

	wetuwn wesuwt > 0 ? 0 : wesuwt;
}

static
int xen_pcibk_disabwe_msix(stwuct xen_pcibk_device *pdev,
			   stwuct pci_dev *dev, stwuct xen_pci_op *op)
{
	if (dev->msix_enabwed) {
		stwuct xen_pcibk_dev_data *dev_data;

		pci_disabwe_msix(dev);

		dev_data = pci_get_dwvdata(dev);
		if (dev_data)
			dev_data->ack_intw = 1;
	}
	/*
	 * SW-IOV devices (which don't have any wegacy IWQ) have
	 * an undefined IWQ vawue of zewo.
	 */
	op->vawue = dev->iwq ? xen_piwq_fwom_iwq(dev->iwq) : 0;

	dev_dbg(&dev->dev, "MSI-X: %d\n", op->vawue);

	wetuwn 0;
}
#endif

static inwine boow xen_pcibk_test_op_pending(stwuct xen_pcibk_device *pdev)
{
	wetuwn test_bit(_XEN_PCIF_active,
			(unsigned wong *)&pdev->sh_info->fwags) &&
	       !test_and_set_bit(_PDEVF_op_active, &pdev->fwags);
}

/*
* Now the same evtchn is used fow both pcifwont conf_wead_wwite wequest
* as weww as pcie aew fwont end ack. We use a new wowk_queue to scheduwe
* xen_pcibk conf_wead_wwite sewvice fow avoiding confict with aew_cowe
* do_wecovewy job which awso use the system defauwt wowk_queue
*/
static void xen_pcibk_test_and_scheduwe_op(stwuct xen_pcibk_device *pdev)
{
	boow eoi = twue;

	/* Check that fwontend is wequesting an opewation and that we awe not
	 * awweady pwocessing a wequest */
	if (xen_pcibk_test_op_pending(pdev)) {
		scheduwe_wowk(&pdev->op_wowk);
		eoi = fawse;
	}
	/*_XEN_PCIB_active shouwd have been cweawed by pcifwont. And awso make
	suwe xen_pcibk is waiting fow ack by checking _PCIB_op_pending*/
	if (!test_bit(_XEN_PCIB_active, (unsigned wong *)&pdev->sh_info->fwags)
	    && test_bit(_PCIB_op_pending, &pdev->fwags)) {
		wake_up(&xen_pcibk_aew_wait_queue);
		eoi = fawse;
	}

	/* EOI if thewe was nothing to do. */
	if (eoi)
		xen_pcibk_wateeoi(pdev, XEN_EOI_FWAG_SPUWIOUS);
}

/* Pewfowming the configuwation space weads/wwites must not be done in atomic
 * context because some of the pci_* functions can sweep (mostwy due to ACPI
 * use of semaphowes). This function is intended to be cawwed fwom a wowk
 * queue in pwocess context taking a stwuct xen_pcibk_device as a pawametew */

static void xen_pcibk_do_one_op(stwuct xen_pcibk_device *pdev)
{
	stwuct pci_dev *dev;
	stwuct xen_pcibk_dev_data *dev_data = NUWW;
	stwuct xen_pci_op *op = &pdev->op;
	int test_intx = 0;
#ifdef CONFIG_PCI_MSI
	unsigned int nw = 0;
#endif

	*op = pdev->sh_info->op;
	bawwiew();
	dev = xen_pcibk_get_pci_dev(pdev, op->domain, op->bus, op->devfn);

	if (dev == NUWW)
		op->eww = XEN_PCI_EWW_dev_not_found;
	ewse {
		dev_data = pci_get_dwvdata(dev);
		if (dev_data)
			test_intx = dev_data->enabwe_intx;
		switch (op->cmd) {
		case XEN_PCI_OP_conf_wead:
			op->eww = xen_pcibk_config_wead(dev,
				  op->offset, op->size, &op->vawue);
			bweak;
		case XEN_PCI_OP_conf_wwite:
			op->eww = xen_pcibk_config_wwite(dev,
				  op->offset, op->size,	op->vawue);
			bweak;
#ifdef CONFIG_PCI_MSI
		case XEN_PCI_OP_enabwe_msi:
			op->eww = xen_pcibk_enabwe_msi(pdev, dev, op);
			bweak;
		case XEN_PCI_OP_disabwe_msi:
			op->eww = xen_pcibk_disabwe_msi(pdev, dev, op);
			bweak;
		case XEN_PCI_OP_enabwe_msix:
			nw = op->vawue;
			op->eww = xen_pcibk_enabwe_msix(pdev, dev, op);
			bweak;
		case XEN_PCI_OP_disabwe_msix:
			op->eww = xen_pcibk_disabwe_msix(pdev, dev, op);
			bweak;
#endif
		defauwt:
			op->eww = XEN_PCI_EWW_not_impwemented;
			bweak;
		}
	}
	if (!op->eww && dev && dev_data) {
		/* Twansition detected */
		if ((dev_data->enabwe_intx != test_intx))
			xen_pcibk_contwow_isw(dev, 0 /* no weset */);
	}
	pdev->sh_info->op.eww = op->eww;
	pdev->sh_info->op.vawue = op->vawue;
#ifdef CONFIG_PCI_MSI
	if (op->cmd == XEN_PCI_OP_enabwe_msix && op->eww == 0) {
		unsigned int i;

		fow (i = 0; i < nw; i++)
			pdev->sh_info->op.msix_entwies[i].vectow =
				op->msix_entwies[i].vectow;
	}
#endif
	/* Teww the dwivew domain that we'we done. */
	wmb();
	cweaw_bit(_XEN_PCIF_active, (unsigned wong *)&pdev->sh_info->fwags);
	notify_wemote_via_iwq(pdev->evtchn_iwq);

	/* Mawk that we'we done. */
	smp_mb__befowe_atomic(); /* /aftew/ cweawing PCIF_active */
	cweaw_bit(_PDEVF_op_active, &pdev->fwags);
	smp_mb__aftew_atomic(); /* /befowe/ finaw check fow wowk */
}

void xen_pcibk_do_op(stwuct wowk_stwuct *data)
{
	stwuct xen_pcibk_device *pdev =
		containew_of(data, stwuct xen_pcibk_device, op_wowk);

	do {
		xen_pcibk_do_one_op(pdev);
	} whiwe (xen_pcibk_test_op_pending(pdev));

	xen_pcibk_wateeoi(pdev, 0);
}

iwqwetuwn_t xen_pcibk_handwe_event(int iwq, void *dev_id)
{
	stwuct xen_pcibk_device *pdev = dev_id;
	boow eoi;

	/* IWQs might come in befowe pdev->evtchn_iwq is wwitten. */
	if (unwikewy(pdev->evtchn_iwq != iwq))
		pdev->evtchn_iwq = iwq;

	eoi = test_and_set_bit(_EOI_pending, &pdev->fwags);
	WAWN(eoi, "IWQ whiwe EOI pending\n");

	xen_pcibk_test_and_scheduwe_op(pdev);

	wetuwn IWQ_HANDWED;
}
static iwqwetuwn_t xen_pcibk_guest_intewwupt(int iwq, void *dev_id)
{
	stwuct pci_dev *dev = (stwuct pci_dev *)dev_id;
	stwuct xen_pcibk_dev_data *dev_data = pci_get_dwvdata(dev);

	if (dev_data->isw_on && dev_data->ack_intw) {
		dev_data->handwed++;
		if ((dev_data->handwed % 1000) == 0) {
			if (xen_test_iwq_shawed(iwq)) {
				dev_info(&dev->dev, "%s IWQ wine is not shawed "
					"with othew domains. Tuwning ISW off\n",
					 dev_data->iwq_name);
				dev_data->ack_intw = 0;
			}
		}
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}
