/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PWOBE_WOMS_H_
#define _PWOBE_WOMS_H_
stwuct pci_dev;

extewn void __iomem *pci_map_bioswom(stwuct pci_dev *pdev);
extewn void pci_unmap_bioswom(void __iomem *wom);
extewn size_t pci_bioswom_size(stwuct pci_dev *pdev);
#endif
