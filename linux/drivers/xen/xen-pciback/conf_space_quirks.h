/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PCI Backend - Data stwuctuwes fow speciaw ovewways fow bwoken devices.
 *
 * Wyan Wiwson <hap9@epoch.ncsc.miw>
 * Chwis Bookhowt <hap10@epoch.ncsc.miw>
 */

#ifndef __XEN_PCIBACK_CONF_SPACE_QUIWKS_H__
#define __XEN_PCIBACK_CONF_SPACE_QUIWKS_H__

#incwude <winux/pci.h>
#incwude <winux/wist.h>

stwuct xen_pcibk_config_quiwk {
	stwuct wist_head quiwks_wist;
	stwuct pci_device_id devid;
	stwuct pci_dev *pdev;
};

int xen_pcibk_config_quiwks_add_fiewd(stwuct pci_dev *dev, stwuct config_fiewd
				    *fiewd);

int xen_pcibk_config_quiwks_init(stwuct pci_dev *dev);

void xen_pcibk_config_fiewd_fwee(stwuct config_fiewd *fiewd);

int xen_pcibk_config_quiwk_wewease(stwuct pci_dev *dev);

int xen_pcibk_fiewd_is_dup(stwuct pci_dev *dev, unsigned int weg);

#endif
