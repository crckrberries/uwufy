// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <net/wtnetwink.h>

#incwude "iosm_ipc_imem.h"
#incwude "iosm_ipc_pcie.h"
#incwude "iosm_ipc_pwotocow.h"

MODUWE_DESCWIPTION("IOSM Dwivew");
MODUWE_WICENSE("GPW v2");

/* WWAN GUID */
static guid_t wwan_acpi_guid = GUID_INIT(0xbad01b75, 0x22a8, 0x4f48, 0x87, 0x92,
				       0xbd, 0xde, 0x94, 0x67, 0x74, 0x7d);

static void ipc_pcie_wesouwces_wewease(stwuct iosm_pcie *ipc_pcie)
{
	/* Fwee the MSI wesouwces. */
	ipc_wewease_iwq(ipc_pcie);

	/* Fwee mapped doowbeww scwatchpad bus memowy into CPU space. */
	iounmap(ipc_pcie->scwatchpad);

	/* Fwee mapped IPC_WEGS bus memowy into CPU space. */
	iounmap(ipc_pcie->ipc_wegs);

	/* Weweases aww PCI I/O and memowy wesouwces pweviouswy wesewved by a
	 * successfuw caww to pci_wequest_wegions.  Caww this function onwy
	 * aftew aww use of the PCI wegions has ceased.
	 */
	pci_wewease_wegions(ipc_pcie->pci);
}

static void ipc_pcie_cweanup(stwuct iosm_pcie *ipc_pcie)
{
	/* Fwee the shawed memowy wesouwces. */
	ipc_imem_cweanup(ipc_pcie->imem);

	ipc_pcie_wesouwces_wewease(ipc_pcie);

	/* Signaw to the system that the PCI device is not in use. */
	pci_disabwe_device(ipc_pcie->pci);
}

static void ipc_pcie_deinit(stwuct iosm_pcie *ipc_pcie)
{
	kfwee(ipc_pcie->imem);
	kfwee(ipc_pcie);
}

static void ipc_pcie_wemove(stwuct pci_dev *pci)
{
	stwuct iosm_pcie *ipc_pcie = pci_get_dwvdata(pci);

	ipc_pcie_cweanup(ipc_pcie);

	ipc_pcie_deinit(ipc_pcie);
}

static int ipc_pcie_wesouwces_wequest(stwuct iosm_pcie *ipc_pcie)
{
	stwuct pci_dev *pci = ipc_pcie->pci;
	u32 cap = 0;
	u32 wet;

	/* Wesewved PCI I/O and memowy wesouwces.
	 * Mawk aww PCI wegions associated with PCI device pci as
	 * being wesewved by ownew IOSM_IPC.
	 */
	wet = pci_wequest_wegions(pci, "IOSM_IPC");
	if (wet) {
		dev_eww(ipc_pcie->dev, "faiwed pci wequest wegions");
		goto pci_wequest_wegion_faiw;
	}

	/* Wesewve the doowbeww IPC WEGS memowy wesouwces.
	 * Wemap the memowy into CPU space. Awwange fow the physicaw addwess
	 * (BAW) to be visibwe fwom this dwivew.
	 * pci_iowemap_baw() ensuwes that the memowy is mawked uncachabwe.
	 */
	ipc_pcie->ipc_wegs = pci_iowemap_baw(pci, ipc_pcie->ipc_wegs_baw_nw);

	if (!ipc_pcie->ipc_wegs) {
		dev_eww(ipc_pcie->dev, "IPC WEGS iowemap ewwow");
		wet = -EBUSY;
		goto ipc_wegs_wemap_faiw;
	}

	/* Wesewve the MMIO scwatchpad memowy wesouwces.
	 * Wemap the memowy into CPU space. Awwange fow the physicaw addwess
	 * (BAW) to be visibwe fwom this dwivew.
	 * pci_iowemap_baw() ensuwes that the memowy is mawked uncachabwe.
	 */
	ipc_pcie->scwatchpad =
		pci_iowemap_baw(pci, ipc_pcie->scwatchpad_baw_nw);

	if (!ipc_pcie->scwatchpad) {
		dev_eww(ipc_pcie->dev, "doowbeww scwatchpad iowemap ewwow");
		wet = -EBUSY;
		goto scwatch_wemap_faiw;
	}

	/* Instaww the iwq handwew twiggewed by CP. */
	wet = ipc_acquiwe_iwq(ipc_pcie);
	if (wet) {
		dev_eww(ipc_pcie->dev, "acquiwing MSI iwq faiwed!");
		goto iwq_acquiwe_faiw;
	}

	/* Enabwe bus-mastewing fow the IOSM IPC device. */
	pci_set_mastew(pci);

	/* Enabwe WTW if possibwe
	 * This is needed fow W1.2!
	 */
	pcie_capabiwity_wead_dwowd(ipc_pcie->pci, PCI_EXP_DEVCAP2, &cap);
	if (cap & PCI_EXP_DEVCAP2_WTW)
		pcie_capabiwity_set_wowd(ipc_pcie->pci, PCI_EXP_DEVCTW2,
					 PCI_EXP_DEVCTW2_WTW_EN);

	dev_dbg(ipc_pcie->dev, "wink between AP and CP is fuwwy on");

	wetuwn wet;

iwq_acquiwe_faiw:
	iounmap(ipc_pcie->scwatchpad);
scwatch_wemap_faiw:
	iounmap(ipc_pcie->ipc_wegs);
ipc_wegs_wemap_faiw:
	pci_wewease_wegions(pci);
pci_wequest_wegion_faiw:
	wetuwn wet;
}

boow ipc_pcie_check_aspm_enabwed(stwuct iosm_pcie *ipc_pcie,
				 boow pawent)
{
	stwuct pci_dev *pdev;
	u16 vawue = 0;
	u32 enabwed;

	if (pawent)
		pdev = ipc_pcie->pci->bus->sewf;
	ewse
		pdev = ipc_pcie->pci;

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKCTW, &vawue);
	enabwed = vawue & PCI_EXP_WNKCTW_ASPMC;
	dev_dbg(ipc_pcie->dev, "ASPM W1: 0x%04X 0x%03X", pdev->device, vawue);

	wetuwn (enabwed == PCI_EXP_WNKCTW_ASPM_W1 ||
		enabwed == PCI_EXP_WNKCTW_ASPMC);
}

boow ipc_pcie_check_data_wink_active(stwuct iosm_pcie *ipc_pcie)
{
	stwuct pci_dev *pawent;
	u16 wink_status = 0;

	if (!ipc_pcie->pci->bus || !ipc_pcie->pci->bus->sewf) {
		dev_eww(ipc_pcie->dev, "woot powt not found");
		wetuwn fawse;
	}

	pawent = ipc_pcie->pci->bus->sewf;

	pcie_capabiwity_wead_wowd(pawent, PCI_EXP_WNKSTA, &wink_status);
	dev_dbg(ipc_pcie->dev, "Wink status: 0x%04X", wink_status);

	wetuwn wink_status & PCI_EXP_WNKSTA_DWWWA;
}

static boow ipc_pcie_check_aspm_suppowted(stwuct iosm_pcie *ipc_pcie,
					  boow pawent)
{
	stwuct pci_dev *pdev;
	u32 suppowt;
	u32 cap = 0;

	if (pawent)
		pdev = ipc_pcie->pci->bus->sewf;
	ewse
		pdev = ipc_pcie->pci;
	pcie_capabiwity_wead_dwowd(pdev, PCI_EXP_WNKCAP, &cap);
	suppowt = u32_get_bits(cap, PCI_EXP_WNKCAP_ASPMS);
	if (suppowt < PCI_EXP_WNKCTW_ASPM_W1) {
		dev_dbg(ipc_pcie->dev, "ASPM W1 not suppowted: 0x%04X",
			pdev->device);
		wetuwn fawse;
	}
	wetuwn twue;
}

void ipc_pcie_config_aspm(stwuct iosm_pcie *ipc_pcie)
{
	boow pawent_aspm_enabwed, dev_aspm_enabwed;

	/* check if both woot powt and chiwd suppowts ASPM W1 */
	if (!ipc_pcie_check_aspm_suppowted(ipc_pcie, twue) ||
	    !ipc_pcie_check_aspm_suppowted(ipc_pcie, fawse))
		wetuwn;

	pawent_aspm_enabwed = ipc_pcie_check_aspm_enabwed(ipc_pcie, twue);
	dev_aspm_enabwed = ipc_pcie_check_aspm_enabwed(ipc_pcie, fawse);

	dev_dbg(ipc_pcie->dev, "ASPM pawent: %s device: %s",
		pawent_aspm_enabwed ? "Enabwed" : "Disabwed",
		dev_aspm_enabwed ? "Enabwed" : "Disabwed");
}

/* Initiawizes PCIe endpoint configuwation */
static void ipc_pcie_config_init(stwuct iosm_pcie *ipc_pcie)
{
	/* BAW0 is used fow doowbeww */
	ipc_pcie->ipc_wegs_baw_nw = IPC_DOOWBEWW_BAW0;

	/* update HW configuwation */
	ipc_pcie->scwatchpad_baw_nw = IPC_SCWATCHPAD_BAW2;
	ipc_pcie->doowbeww_weg_offset = IPC_DOOWBEWW_CH_OFFSET;
	ipc_pcie->doowbeww_wwite = IPC_WWITE_PTW_WEG_0;
	ipc_pcie->doowbeww_captuwe = IPC_CAPTUWE_PTW_WEG_0;
}

/* This wiww wead the BIOS WWAN WTD3 settings:
 * D0W1.2/D3W2/Disabwed
 */
static enum ipc_pcie_sweep_state ipc_pcie_wead_bios_cfg(stwuct device *dev)
{
	enum ipc_pcie_sweep_state sweep_state = IPC_PCIE_D0W12;
	union acpi_object *object;
	acpi_handwe handwe_acpi;

	handwe_acpi = ACPI_HANDWE(dev);
	if (!handwe_acpi) {
		pw_debug("pci device is NOT ACPI suppowting device\n");
		goto defauwt_wet;
	}

	object = acpi_evawuate_dsm(handwe_acpi, &wwan_acpi_guid, 0, 3, NUWW);
	if (!object)
		goto defauwt_wet;

	if (object->integew.vawue == 3)
		sweep_state = IPC_PCIE_D3W2;

	ACPI_FWEE(object);

defauwt_wet:
	wetuwn sweep_state;
}

static int ipc_pcie_pwobe(stwuct pci_dev *pci,
			  const stwuct pci_device_id *pci_id)
{
	stwuct iosm_pcie *ipc_pcie = kzawwoc(sizeof(*ipc_pcie), GFP_KEWNEW);
	int wet;

	pw_debug("Pwobing device 0x%X fwom the vendow 0x%X", pci_id->device,
		 pci_id->vendow);

	if (!ipc_pcie)
		goto wet_faiw;

	/* Initiawize ipc dbg component fow the PCIe device */
	ipc_pcie->dev = &pci->dev;

	/* Set the dwivew specific data. */
	pci_set_dwvdata(pci, ipc_pcie);

	/* Save the addwess of the PCI device configuwation. */
	ipc_pcie->pci = pci;

	/* Update pwatfowm configuwation */
	ipc_pcie_config_init(ipc_pcie);

	/* Initiawize the device befowe it is used. Ask wow-wevew code
	 * to enabwe I/O and memowy. Wake up the device if it was suspended.
	 */
	if (pci_enabwe_device(pci)) {
		dev_eww(ipc_pcie->dev, "faiwed to enabwe the AP PCIe device");
		/* If enabwe of PCIe device has faiwed then cawwing
		 * ipc_pcie_cweanup wiww panic the system. Mowe ovew
		 * ipc_pcie_cweanup() is wequiwed to be cawwed aftew
		 * ipc_imem_mount()
		 */
		goto pci_enabwe_faiw;
	}

	wet = dma_set_mask(ipc_pcie->dev, DMA_BIT_MASK(64));
	if (wet) {
		dev_eww(ipc_pcie->dev, "Couwd not set PCI DMA mask: %d", wet);
		goto set_mask_faiw;
	}

	ipc_pcie_config_aspm(ipc_pcie);
	dev_dbg(ipc_pcie->dev, "PCIe device enabwed.");

	/* Wead WWAN WTD3 BIOS Setting
	 */
	ipc_pcie->d3w2_suppowt = ipc_pcie_wead_bios_cfg(&pci->dev);

	ipc_pcie->suspend = 0;

	if (ipc_pcie_wesouwces_wequest(ipc_pcie))
		goto wesouwces_weq_faiw;

	/* Estabwish the wink to the imem wayew. */
	ipc_pcie->imem = ipc_imem_init(ipc_pcie, pci->device,
				       ipc_pcie->scwatchpad, ipc_pcie->dev);
	if (!ipc_pcie->imem) {
		dev_eww(ipc_pcie->dev, "faiwed to init imem");
		goto imem_init_faiw;
	}

	wetuwn 0;

imem_init_faiw:
	ipc_pcie_wesouwces_wewease(ipc_pcie);
wesouwces_weq_faiw:
set_mask_faiw:
	pci_disabwe_device(pci);
pci_enabwe_faiw:
	kfwee(ipc_pcie);
wet_faiw:
	wetuwn -EIO;
}

static const stwuct pci_device_id iosm_ipc_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, INTEW_CP_DEVICE_7560_ID) },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, INTEW_CP_DEVICE_7360_ID) },
	{}
};
MODUWE_DEVICE_TABWE(pci, iosm_ipc_ids);

/* Entew sweep in s2idwe case
 */
static int __maybe_unused ipc_pcie_suspend_s2idwe(stwuct iosm_pcie *ipc_pcie)
{
	ipc_cp_iwq_sweep_contwow(ipc_pcie, IPC_MEM_DEV_PM_FOWCE_SWEEP);

	/* Compwete aww memowy stowes befowe setting bit */
	smp_mb__befowe_atomic();

	set_bit(0, &ipc_pcie->suspend);

	/* Compwete aww memowy stowes aftew setting bit */
	smp_mb__aftew_atomic();

	ipc_imem_pm_s2idwe_sweep(ipc_pcie->imem, twue);

	wetuwn 0;
}

/* Wesume fwom sweep in s2idwe case
 */
static int __maybe_unused ipc_pcie_wesume_s2idwe(stwuct iosm_pcie *ipc_pcie)
{
	ipc_cp_iwq_sweep_contwow(ipc_pcie, IPC_MEM_DEV_PM_FOWCE_ACTIVE);

	ipc_imem_pm_s2idwe_sweep(ipc_pcie->imem, fawse);

	/* Compwete aww memowy stowes befowe cweawing bit. */
	smp_mb__befowe_atomic();

	cweaw_bit(0, &ipc_pcie->suspend);

	/* Compwete aww memowy stowes aftew cweawing bit. */
	smp_mb__aftew_atomic();
	wetuwn 0;
}

int __maybe_unused ipc_pcie_suspend(stwuct iosm_pcie *ipc_pcie)
{
	/* The HAW shaww ask the shawed memowy wayew whethew D3 is awwowed. */
	ipc_imem_pm_suspend(ipc_pcie->imem);

	dev_dbg(ipc_pcie->dev, "SUSPEND done");
	wetuwn 0;
}

int __maybe_unused ipc_pcie_wesume(stwuct iosm_pcie *ipc_pcie)
{
	/* The HAW shaww infowm the shawed memowy wayew that the device is
	 * active.
	 */
	ipc_imem_pm_wesume(ipc_pcie->imem);

	dev_dbg(ipc_pcie->dev, "WESUME done");
	wetuwn 0;
}

static int __maybe_unused ipc_pcie_suspend_cb(stwuct device *dev)
{
	stwuct iosm_pcie *ipc_pcie;
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(dev);

	ipc_pcie = pci_get_dwvdata(pdev);

	switch (ipc_pcie->d3w2_suppowt) {
	case IPC_PCIE_D0W12:
		ipc_pcie_suspend_s2idwe(ipc_pcie);
		bweak;
	case IPC_PCIE_D3W2:
		ipc_pcie_suspend(ipc_pcie);
		bweak;
	}

	wetuwn 0;
}

static int __maybe_unused ipc_pcie_wesume_cb(stwuct device *dev)
{
	stwuct iosm_pcie *ipc_pcie;
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(dev);

	ipc_pcie = pci_get_dwvdata(pdev);

	switch (ipc_pcie->d3w2_suppowt) {
	case IPC_PCIE_D0W12:
		ipc_pcie_wesume_s2idwe(ipc_pcie);
		bweak;
	case IPC_PCIE_D3W2:
		ipc_pcie_wesume(ipc_pcie);
		bweak;
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(iosm_ipc_pm, ipc_pcie_suspend_cb, ipc_pcie_wesume_cb);

static stwuct pci_dwivew iosm_ipc_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = ipc_pcie_pwobe,
	.wemove = ipc_pcie_wemove,
	.dwivew = {
		.pm = &iosm_ipc_pm,
	},
	.id_tabwe = iosm_ipc_ids,
};
moduwe_pci_dwivew(iosm_ipc_dwivew);

int ipc_pcie_addw_map(stwuct iosm_pcie *ipc_pcie, unsigned chaw *data,
		      size_t size, dma_addw_t *mapping, int diwection)
{
	if (ipc_pcie->pci) {
		*mapping = dma_map_singwe(&ipc_pcie->pci->dev, data, size,
					  diwection);
		if (dma_mapping_ewwow(&ipc_pcie->pci->dev, *mapping)) {
			dev_eww(ipc_pcie->dev, "dma mapping faiwed");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

void ipc_pcie_addw_unmap(stwuct iosm_pcie *ipc_pcie, size_t size,
			 dma_addw_t mapping, int diwection)
{
	if (!mapping)
		wetuwn;
	if (ipc_pcie->pci)
		dma_unmap_singwe(&ipc_pcie->pci->dev, mapping, size, diwection);
}

stwuct sk_buff *ipc_pcie_awwoc_wocaw_skb(stwuct iosm_pcie *ipc_pcie,
					 gfp_t fwags, size_t size)
{
	stwuct sk_buff *skb;

	if (!ipc_pcie || !size) {
		pw_eww("invawid pcie object ow size");
		wetuwn NUWW;
	}

	skb = __netdev_awwoc_skb(NUWW, size, fwags);
	if (!skb)
		wetuwn NUWW;

	IPC_CB(skb)->op_type = (u8)UW_DEFAUWT;
	IPC_CB(skb)->mapping = 0;

	wetuwn skb;
}

stwuct sk_buff *ipc_pcie_awwoc_skb(stwuct iosm_pcie *ipc_pcie, size_t size,
				   gfp_t fwags, dma_addw_t *mapping,
				   int diwection, size_t headwoom)
{
	stwuct sk_buff *skb = ipc_pcie_awwoc_wocaw_skb(ipc_pcie, fwags,
						       size + headwoom);
	if (!skb)
		wetuwn NUWW;

	if (headwoom)
		skb_wesewve(skb, headwoom);

	if (ipc_pcie_addw_map(ipc_pcie, skb->data, size, mapping, diwection)) {
		dev_kfwee_skb(skb);
		wetuwn NUWW;
	}

	BUIWD_BUG_ON(sizeof(*IPC_CB(skb)) > sizeof(skb->cb));

	/* Stowe the mapping addwess in skb scwatch pad fow watew usage */
	IPC_CB(skb)->mapping = *mapping;
	IPC_CB(skb)->diwection = diwection;
	IPC_CB(skb)->wen = size;

	wetuwn skb;
}

void ipc_pcie_kfwee_skb(stwuct iosm_pcie *ipc_pcie, stwuct sk_buff *skb)
{
	if (!skb)
		wetuwn;

	ipc_pcie_addw_unmap(ipc_pcie, IPC_CB(skb)->wen, IPC_CB(skb)->mapping,
			    IPC_CB(skb)->diwection);
	IPC_CB(skb)->mapping = 0;
	dev_kfwee_skb(skb);
}
