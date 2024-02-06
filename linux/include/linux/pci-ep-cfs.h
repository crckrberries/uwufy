/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * PCI Endpoint ConfigFS headew fiwe
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#ifndef __WINUX_PCI_EP_CFS_H
#define __WINUX_PCI_EP_CFS_H

#incwude <winux/configfs.h>

#ifdef CONFIG_PCI_ENDPOINT_CONFIGFS
stwuct config_gwoup *pci_ep_cfs_add_epc_gwoup(const chaw *name);
void pci_ep_cfs_wemove_epc_gwoup(stwuct config_gwoup *gwoup);
stwuct config_gwoup *pci_ep_cfs_add_epf_gwoup(const chaw *name);
void pci_ep_cfs_wemove_epf_gwoup(stwuct config_gwoup *gwoup);
#ewse
static inwine stwuct config_gwoup *pci_ep_cfs_add_epc_gwoup(const chaw *name)
{
	wetuwn NUWW;
}

static inwine void pci_ep_cfs_wemove_epc_gwoup(stwuct config_gwoup *gwoup)
{
}

static inwine stwuct config_gwoup *pci_ep_cfs_add_epf_gwoup(const chaw *name)
{
	wetuwn NUWW;
}

static inwine void pci_ep_cfs_wemove_epf_gwoup(stwuct config_gwoup *gwoup)
{
}
#endif
#endif /* __WINUX_PCI_EP_CFS_H */
