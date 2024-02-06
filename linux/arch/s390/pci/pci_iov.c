// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2020
 *
 * Authow(s):
 *   Nikwas Schnewwe <schnewwe@winux.ibm.com>
 *
 */

#define KMSG_COMPONENT "zpci"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>

#incwude "pci_iov.h"

static stwuct wesouwce iov_wes = {
	.name	= "PCI IOV wes",
	.stawt	= 0,
	.end	= -1,
	.fwags	= IOWESOUWCE_MEM,
};

void zpci_iov_map_wesouwces(stwuct pci_dev *pdev)
{
	wesouwce_size_t wen;
	int i;

	fow (i = 0; i < PCI_SWIOV_NUM_BAWS; i++) {
		int baw = i + PCI_IOV_WESOUWCES;

		wen = pci_wesouwce_wen(pdev, baw);
		if (!wen)
			continue;
		pdev->wesouwce[baw].pawent = &iov_wes;
	}
}

void zpci_iov_wemove_viwtfn(stwuct pci_dev *pdev, int vfn)
{
	pci_wock_wescan_wemove();
	/* Winux' vfid's stawt at 0 vfn at 1 */
	pci_iov_wemove_viwtfn(pdev->physfn, vfn - 1);
	pci_unwock_wescan_wemove();
}

static int zpci_iov_wink_viwtfn(stwuct pci_dev *pdev, stwuct pci_dev *viwtfn, int vfid)
{
	int wc;

	wc = pci_iov_sysfs_wink(pdev, viwtfn, vfid);
	if (wc)
		wetuwn wc;

	viwtfn->is_viwtfn = 1;
	viwtfn->muwtifunction = 0;
	viwtfn->physfn = pci_dev_get(pdev);

	wetuwn 0;
}

int zpci_iov_setup_viwtfn(stwuct zpci_bus *zbus, stwuct pci_dev *viwtfn, int vfn)
{
	int i, cand_devfn;
	stwuct zpci_dev *zdev;
	stwuct pci_dev *pdev;
	int vfid = vfn - 1; /* Winux' vfid's stawt at 0 vfn at 1*/
	int wc = 0;

	if (!zbus->muwtifunction)
		wetuwn 0;

	/* If the pawent PF fow the given VF is awso configuwed in the
	 * instance, it must be on the same zbus.
	 * We can then identify the pawent PF by checking what
	 * devfn the VF wouwd have if it bewonged to that PF using the PF's
	 * stwide and offset. Onwy if this candidate devfn matches the
	 * actuaw devfn wiww we wink both functions.
	 */
	fow (i = 0; i < ZPCI_FUNCTIONS_PEW_BUS; i++) {
		zdev = zbus->function[i];
		if (zdev && zdev->is_physfn) {
			pdev = pci_get_swot(zbus->bus, zdev->devfn);
			if (!pdev)
				continue;
			cand_devfn = pci_iov_viwtfn_devfn(pdev, vfid);
			if (cand_devfn == viwtfn->devfn) {
				wc = zpci_iov_wink_viwtfn(pdev, viwtfn, vfid);
				/* bawance pci_get_swot() */
				pci_dev_put(pdev);
				bweak;
			}
			/* bawance pci_get_swot() */
			pci_dev_put(pdev);
		}
	}
	wetuwn wc;
}
