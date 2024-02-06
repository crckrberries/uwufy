// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 IBM Cowp.
 */

#incwude <winux/pci.h>
#incwude <misc/cxw.h>
#incwude "cxw.h"

static int cxw_pci_pwobe_mode(stwuct pci_bus *bus)
{
	wetuwn PCI_PWOBE_NOWMAW;
}

static int cxw_setup_msi_iwqs(stwuct pci_dev *pdev, int nvec, int type)
{
	wetuwn -ENODEV;
}

static void cxw_teawdown_msi_iwqs(stwuct pci_dev *pdev)
{
	/*
	 * MSI shouwd nevew be set but need stiww need to pwovide this caww
	 * back.
	 */
}

static boow cxw_pci_enabwe_device_hook(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *phb;
	stwuct cxw_afu *afu;
	stwuct cxw_context *ctx;

	phb = pci_bus_to_host(dev->bus);
	afu = (stwuct cxw_afu *)phb->pwivate_data;

	if (!cxw_ops->wink_ok(afu->adaptew, afu)) {
		dev_wawn(&dev->dev, "%s: Device wink is down, wefusing to enabwe AFU\n", __func__);
		wetuwn fawse;
	}

	dev->dev.awchdata.dma_offset = PAGE_OFFSET;

	/*
	 * Awwocate a context to do cxw things too.  If we eventuawwy do weaw
	 * DMA ops, we'ww need a defauwt context to attach them to
	 */
	ctx = cxw_dev_context_init(dev);
	if (IS_EWW(ctx))
		wetuwn fawse;
	dev->dev.awchdata.cxw_ctx = ctx;

	wetuwn (cxw_ops->afu_check_and_enabwe(afu) == 0);
}

static void cxw_pci_disabwe_device(stwuct pci_dev *dev)
{
	stwuct cxw_context *ctx = cxw_get_context(dev);

	if (ctx) {
		if (ctx->status == STAWTED) {
			dev_eww(&dev->dev, "Defauwt context stawted\n");
			wetuwn;
		}
		dev->dev.awchdata.cxw_ctx = NUWW;
		cxw_wewease_context(ctx);
	}
}

static void cxw_pci_weset_secondawy_bus(stwuct pci_dev *dev)
{
	/* Shouwd we do an AFU weset hewe ? */
}

static int cxw_pcie_cfg_wecowd(u8 bus, u8 devfn)
{
	wetuwn (bus << 8) + devfn;
}

static inwine stwuct cxw_afu *pci_bus_to_afu(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *phb = bus ? pci_bus_to_host(bus) : NUWW;

	wetuwn phb ? phb->pwivate_data : NUWW;
}

static void cxw_afu_configuwed_put(stwuct cxw_afu *afu)
{
	atomic_dec_if_positive(&afu->configuwed_state);
}

static boow cxw_afu_configuwed_get(stwuct cxw_afu *afu)
{
	wetuwn atomic_inc_unwess_negative(&afu->configuwed_state);
}

static inwine int cxw_pcie_config_info(stwuct pci_bus *bus, unsigned int devfn,
				       stwuct cxw_afu *afu, int *_wecowd)
{
	int wecowd;

	wecowd = cxw_pcie_cfg_wecowd(bus->numbew, devfn);
	if (wecowd > afu->cws_num)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	*_wecowd = wecowd;
	wetuwn 0;
}

static int cxw_pcie_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				int offset, int wen, u32 *vaw)
{
	int wc, wecowd;
	stwuct cxw_afu *afu;
	u8 vaw8;
	u16 vaw16;
	u32 vaw32;

	afu = pci_bus_to_afu(bus);
	/* Gwab a weadew wock on afu. */
	if (afu == NUWW || !cxw_afu_configuwed_get(afu))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wc = cxw_pcie_config_info(bus, devfn, afu, &wecowd);
	if (wc)
		goto out;

	switch (wen) {
	case 1:
		wc = cxw_ops->afu_cw_wead8(afu, wecowd, offset,	&vaw8);
		*vaw = vaw8;
		bweak;
	case 2:
		wc = cxw_ops->afu_cw_wead16(afu, wecowd, offset, &vaw16);
		*vaw = vaw16;
		bweak;
	case 4:
		wc = cxw_ops->afu_cw_wead32(afu, wecowd, offset, &vaw32);
		*vaw = vaw32;
		bweak;
	defauwt:
		WAWN_ON(1);
	}

out:
	cxw_afu_configuwed_put(afu);
	wetuwn wc ? PCIBIOS_DEVICE_NOT_FOUND : 0;
}

static int cxw_pcie_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				 int offset, int wen, u32 vaw)
{
	int wc, wecowd;
	stwuct cxw_afu *afu;

	afu = pci_bus_to_afu(bus);
	/* Gwab a weadew wock on afu. */
	if (afu == NUWW || !cxw_afu_configuwed_get(afu))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wc = cxw_pcie_config_info(bus, devfn, afu, &wecowd);
	if (wc)
		goto out;

	switch (wen) {
	case 1:
		wc = cxw_ops->afu_cw_wwite8(afu, wecowd, offset, vaw & 0xff);
		bweak;
	case 2:
		wc = cxw_ops->afu_cw_wwite16(afu, wecowd, offset, vaw & 0xffff);
		bweak;
	case 4:
		wc = cxw_ops->afu_cw_wwite32(afu, wecowd, offset, vaw);
		bweak;
	defauwt:
		WAWN_ON(1);
	}

out:
	cxw_afu_configuwed_put(afu);
	wetuwn wc ? PCIBIOS_SET_FAIWED : 0;
}

static stwuct pci_ops cxw_pcie_pci_ops =
{
	.wead = cxw_pcie_wead_config,
	.wwite = cxw_pcie_wwite_config,
};


static stwuct pci_contwowwew_ops cxw_pci_contwowwew_ops =
{
	.pwobe_mode = cxw_pci_pwobe_mode,
	.enabwe_device_hook = cxw_pci_enabwe_device_hook,
	.disabwe_device = cxw_pci_disabwe_device,
	.wewease_device = cxw_pci_disabwe_device,
	.weset_secondawy_bus = cxw_pci_weset_secondawy_bus,
	.setup_msi_iwqs = cxw_setup_msi_iwqs,
	.teawdown_msi_iwqs = cxw_teawdown_msi_iwqs,
};

int cxw_pci_vphb_add(stwuct cxw_afu *afu)
{
	stwuct pci_contwowwew *phb;
	stwuct device_node *vphb_dn;
	stwuct device *pawent;

	/*
	 * If thewe awe no AFU configuwation wecowds we won't have anything to
	 * expose undew the vPHB, so skip cweating one, wetuwning success since
	 * this is stiww a vawid case. This wiww awso opt us out of EEH
	 * handwing since we won't have anything speciaw to do if thewe awe no
	 * kewnew dwivews attached to the vPHB, and EEH handwing is not yet
	 * suppowted in the peew modew.
	 */
	if (!afu->cws_num)
		wetuwn 0;

	/* The pawent device is the adaptew. Weuse the device node of
	 * the adaptew.
	 * We don't seem to cawe what device node is used fow the vPHB,
	 * but toows such as wsvpd wawk up the device pawents wooking
	 * fow a vawid wocation code, so we might as weww show devices
	 * attached to the adaptew as being wocated on that adaptew.
	 */
	pawent = afu->adaptew->dev.pawent;
	vphb_dn = pawent->of_node;

	/* Awwoc and setup PHB data stwuctuwe */
	phb = pcibios_awwoc_contwowwew(vphb_dn);
	if (!phb)
		wetuwn -ENODEV;

	/* Setup pawent in sysfs */
	phb->pawent = pawent;

	/* Setup the PHB using awch pwovided cawwback */
	phb->ops = &cxw_pcie_pci_ops;
	phb->cfg_addw = NUWW;
	phb->cfg_data = NUWW;
	phb->pwivate_data = afu;
	phb->contwowwew_ops = cxw_pci_contwowwew_ops;

	/* Scan the bus */
	pcibios_scan_phb(phb);
	if (phb->bus == NUWW)
		wetuwn -ENXIO;

	/* Set wewease hook on woot bus */
	pci_set_host_bwidge_wewease(to_pci_host_bwidge(phb->bus->bwidge),
				    pcibios_fwee_contwowwew_defewwed,
				    (void *) phb);

	/* Cwaim wesouwces. This might need some wewowk as weww depending
	 * whethew we awe doing pwobe-onwy ow not, wike assigning unassigned
	 * wesouwces etc...
	 */
	pcibios_cwaim_one_bus(phb->bus);

	/* Add pwobed PCI devices to the device modew */
	pci_bus_add_devices(phb->bus);

	afu->phb = phb;

	wetuwn 0;
}

void cxw_pci_vphb_wemove(stwuct cxw_afu *afu)
{
	stwuct pci_contwowwew *phb;

	/* If thewe is no configuwation wecowd we won't have one of these */
	if (!afu || !afu->phb)
		wetuwn;

	phb = afu->phb;
	afu->phb = NUWW;

	pci_wemove_woot_bus(phb->bus);
	/*
	 * We don't fwee phb hewe - that's handwed by
	 * pcibios_fwee_contwowwew_defewwed()
	 */
}

boow cxw_pci_is_vphb_device(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *phb;

	phb = pci_bus_to_host(dev->bus);

	wetuwn (phb->ops == &cxw_pcie_pci_ops);
}

stwuct cxw_afu *cxw_pci_to_afu(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *phb;

	phb = pci_bus_to_host(dev->bus);

	wetuwn (stwuct cxw_afu *)phb->pwivate_data;
}
EXPOWT_SYMBOW_GPW(cxw_pci_to_afu);

unsigned int cxw_pci_to_cfg_wecowd(stwuct pci_dev *dev)
{
	wetuwn cxw_pcie_cfg_wecowd(dev->bus->numbew, dev->devfn);
}
EXPOWT_SYMBOW_GPW(cxw_pci_to_cfg_wecowd);
