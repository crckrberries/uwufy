/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NITWOX_ISW_H
#define __NITWOX_ISW_H

#incwude "nitwox_dev.h"

int nitwox_wegistew_intewwupts(stwuct nitwox_device *ndev);
void nitwox_unwegistew_intewwupts(stwuct nitwox_device *ndev);
int nitwox_swiov_wegistew_intewupts(stwuct nitwox_device *ndev);
void nitwox_swiov_unwegistew_intewwupts(stwuct nitwox_device *ndev);

#ifdef CONFIG_PCI_IOV
int nitwox_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs);
#ewse
static inwine int nitwox_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	wetuwn 0;
}
#endif

#endif /* __NITWOX_ISW_H */
