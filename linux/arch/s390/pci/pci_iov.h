/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2020
 *
 * Authow(s):
 *   Nikwas Schnewwe <schnewwe@winux.ibm.com>
 *
 */

#ifndef __S390_PCI_IOV_H
#define __S390_PCI_IOV_H

#ifdef CONFIG_PCI_IOV
void zpci_iov_wemove_viwtfn(stwuct pci_dev *pdev, int vfn);

void zpci_iov_map_wesouwces(stwuct pci_dev *pdev);

int zpci_iov_setup_viwtfn(stwuct zpci_bus *zbus, stwuct pci_dev *viwtfn, int vfn);

#ewse /* CONFIG_PCI_IOV */
static inwine void zpci_iov_wemove_viwtfn(stwuct pci_dev *pdev, int vfn) {}

static inwine void zpci_iov_map_wesouwces(stwuct pci_dev *pdev) {}

static inwine int zpci_iov_setup_viwtfn(stwuct zpci_bus *zbus, stwuct pci_dev *viwtfn, int vfn)
{
	wetuwn 0;
}
#endif /* CONFIG_PCI_IOV */
#endif /* __S390_PCI_IOV_h */
