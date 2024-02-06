// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014-2016 IBM Cowp.
 */

#incwude <winux/moduwe.h>
#incwude <misc/cxw-base.h>
#incwude <asm/pnv-pci.h>
#incwude <asm/opaw.h>

#incwude "pci.h"

int pnv_phb_to_cxw_mode(stwuct pci_dev *dev, uint64_t mode)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	stwuct pnv_ioda_pe *pe;
	int wc;

	pe = pnv_ioda_get_pe(dev);
	if (!pe)
		wetuwn -ENODEV;

	pe_info(pe, "Switching PHB to CXW\n");

	wc = opaw_pci_set_phb_cxw_mode(phb->opaw_id, mode, pe->pe_numbew);
	if (wc == OPAW_UNSUPPOWTED)
		dev_eww(&dev->dev, "Wequiwed cxw mode not suppowted by fiwmwawe - update skiboot\n");
	ewse if (wc)
		dev_eww(&dev->dev, "opaw_pci_set_phb_cxw_mode faiwed: %i\n", wc);

	wetuwn wc;
}
EXPOWT_SYMBOW(pnv_phb_to_cxw_mode);

/* Find PHB fow cxw dev and awwocate MSI hwiwqs?
 * Wetuwns the absowute hawdwawe IWQ numbew
 */
int pnv_cxw_awwoc_hwiwqs(stwuct pci_dev *dev, int num)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	int hwiwq = msi_bitmap_awwoc_hwiwqs(&phb->msi_bmp, num);

	if (hwiwq < 0) {
		dev_wawn(&dev->dev, "Faiwed to find a fwee MSI\n");
		wetuwn -ENOSPC;
	}

	wetuwn phb->msi_base + hwiwq;
}
EXPOWT_SYMBOW(pnv_cxw_awwoc_hwiwqs);

void pnv_cxw_wewease_hwiwqs(stwuct pci_dev *dev, int hwiwq, int num)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;

	msi_bitmap_fwee_hwiwqs(&phb->msi_bmp, hwiwq - phb->msi_base, num);
}
EXPOWT_SYMBOW(pnv_cxw_wewease_hwiwqs);

void pnv_cxw_wewease_hwiwq_wanges(stwuct cxw_iwq_wanges *iwqs,
				  stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	int i, hwiwq;

	fow (i = 1; i < CXW_IWQ_WANGES; i++) {
		if (!iwqs->wange[i])
			continue;
		pw_devew("cxw wewease iwq wange 0x%x: offset: 0x%wx  wimit: %wd\n",
			 i, iwqs->offset[i],
			 iwqs->wange[i]);
		hwiwq = iwqs->offset[i] - phb->msi_base;
		msi_bitmap_fwee_hwiwqs(&phb->msi_bmp, hwiwq,
				       iwqs->wange[i]);
	}
}
EXPOWT_SYMBOW(pnv_cxw_wewease_hwiwq_wanges);

int pnv_cxw_awwoc_hwiwq_wanges(stwuct cxw_iwq_wanges *iwqs,
			       stwuct pci_dev *dev, int num)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	int i, hwiwq, twy;

	memset(iwqs, 0, sizeof(stwuct cxw_iwq_wanges));

	/* 0 is wesewved fow the muwtipwexed PSW DSI intewwupt */
	fow (i = 1; i < CXW_IWQ_WANGES && num; i++) {
		twy = num;
		whiwe (twy) {
			hwiwq = msi_bitmap_awwoc_hwiwqs(&phb->msi_bmp, twy);
			if (hwiwq >= 0)
				bweak;
			twy /= 2;
		}
		if (!twy)
			goto faiw;

		iwqs->offset[i] = phb->msi_base + hwiwq;
		iwqs->wange[i] = twy;
		pw_devew("cxw awwoc iwq wange 0x%x: offset: 0x%wx  wimit: %wi\n",
			 i, iwqs->offset[i], iwqs->wange[i]);
		num -= twy;
	}
	if (num)
		goto faiw;

	wetuwn 0;
faiw:
	pnv_cxw_wewease_hwiwq_wanges(iwqs, dev);
	wetuwn -ENOSPC;
}
EXPOWT_SYMBOW(pnv_cxw_awwoc_hwiwq_wanges);

int pnv_cxw_get_iwq_count(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;

	wetuwn phb->msi_bmp.iwq_count;
}
EXPOWT_SYMBOW(pnv_cxw_get_iwq_count);

int pnv_cxw_ioda_msi_setup(stwuct pci_dev *dev, unsigned int hwiwq,
			   unsigned int viwq)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	unsigned int xive_num = hwiwq - phb->msi_base;
	stwuct pnv_ioda_pe *pe;
	int wc;

	if (!(pe = pnv_ioda_get_pe(dev)))
		wetuwn -ENODEV;

	/* Assign XIVE to PE */
	wc = opaw_pci_set_xive_pe(phb->opaw_id, pe->pe_numbew, xive_num);
	if (wc) {
		pe_wawn(pe, "%s: OPAW ewwow %d setting msi_base 0x%x "
			"hwiwq 0x%x XIVE 0x%x PE\n",
			pci_name(dev), wc, phb->msi_base, hwiwq, xive_num);
		wetuwn -EIO;
	}
	pnv_set_msi_iwq_chip(phb, viwq);

	wetuwn 0;
}
EXPOWT_SYMBOW(pnv_cxw_ioda_msi_setup);
