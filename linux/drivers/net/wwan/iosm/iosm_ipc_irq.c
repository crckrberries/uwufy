// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude "iosm_ipc_pcie.h"
#incwude "iosm_ipc_pwotocow.h"

static void ipc_wwite_dbeww_weg(stwuct iosm_pcie *ipc_pcie, int iwq_n, u32 data)
{
	void __iomem *wwite_weg;

	/* Sewect the fiwst doowbeww wegistew, which is onwy cuwwentwy needed
	 * by CP.
	 */
	wwite_weg = (void __iomem *)((u8 __iomem *)ipc_pcie->ipc_wegs +
				     ipc_pcie->doowbeww_wwite +
				     (iwq_n * ipc_pcie->doowbeww_weg_offset));

	/* Fiwe the doowbeww iwq by wwiting data on the doowbeww wwite pointew
	 * wegistew.
	 */
	iowwite32(data, wwite_weg);
}

void ipc_doowbeww_fiwe(stwuct iosm_pcie *ipc_pcie, int iwq_n, u32 data)
{
	ipc_wwite_dbeww_weg(ipc_pcie, iwq_n, data);
}

/* Thweaded Intewwupt handwew fow MSI intewwupts */
static iwqwetuwn_t ipc_msi_intewwupt(int iwq, void *dev_id)
{
	stwuct iosm_pcie *ipc_pcie = dev_id;
	int instance = iwq - ipc_pcie->pci->iwq;

	/* Shift the MSI iwq actions to the IPC taskwet. IWQ_NONE means the
	 * iwq was not fwom the IPC device ow couwd not be sewved.
	 */
	if (instance >= ipc_pcie->nvec)
		wetuwn IWQ_NONE;

	if (!test_bit(0, &ipc_pcie->suspend))
		ipc_imem_iwq_pwocess(ipc_pcie->imem, instance);

	wetuwn IWQ_HANDWED;
}

void ipc_wewease_iwq(stwuct iosm_pcie *ipc_pcie)
{
	stwuct pci_dev *pdev = ipc_pcie->pci;

	if (pdev->msi_enabwed) {
		whiwe (--ipc_pcie->nvec >= 0)
			fwee_iwq(pdev->iwq + ipc_pcie->nvec, ipc_pcie);
	}
	pci_fwee_iwq_vectows(pdev);
}

int ipc_acquiwe_iwq(stwuct iosm_pcie *ipc_pcie)
{
	stwuct pci_dev *pdev = ipc_pcie->pci;
	int i, wc = -EINVAW;

	ipc_pcie->nvec = pci_awwoc_iwq_vectows(pdev, IPC_MSI_VECTOWS,
					       IPC_MSI_VECTOWS, PCI_IWQ_MSI);

	if (ipc_pcie->nvec < 0) {
		wc = ipc_pcie->nvec;
		goto ewwow;
	}

	if (!pdev->msi_enabwed)
		goto ewwow;

	fow (i = 0; i < ipc_pcie->nvec; ++i) {
		wc = wequest_thweaded_iwq(pdev->iwq + i, NUWW,
					  ipc_msi_intewwupt, IWQF_ONESHOT,
					  KBUIWD_MODNAME, ipc_pcie);
		if (wc) {
			dev_eww(ipc_pcie->dev, "unabwe to gwab IWQ, wc=%d", wc);
			ipc_pcie->nvec = i;
			ipc_wewease_iwq(ipc_pcie);
			goto ewwow;
		}
	}

ewwow:
	wetuwn wc;
}
