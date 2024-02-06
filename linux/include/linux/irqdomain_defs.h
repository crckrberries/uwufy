/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IWQDOMAIN_DEFS_H
#define _WINUX_IWQDOMAIN_DEFS_H

/*
 * Shouwd sevewaw domains have the same device node, but sewve
 * diffewent puwposes (fow exampwe one domain is fow PCI/MSI, and the
 * othew fow wiwed IWQs), they can be distinguished using a
 * bus-specific token. Most domains awe expected to onwy cawwy
 * DOMAIN_BUS_ANY.
 */
enum iwq_domain_bus_token {
	DOMAIN_BUS_ANY		= 0,
	DOMAIN_BUS_WIWED,
	DOMAIN_BUS_GENEWIC_MSI,
	DOMAIN_BUS_PCI_MSI,
	DOMAIN_BUS_PWATFOWM_MSI,
	DOMAIN_BUS_NEXUS,
	DOMAIN_BUS_IPI,
	DOMAIN_BUS_FSW_MC_MSI,
	DOMAIN_BUS_TI_SCI_INTA_MSI,
	DOMAIN_BUS_WAKEUP,
	DOMAIN_BUS_VMD_MSI,
	DOMAIN_BUS_PCI_DEVICE_MSI,
	DOMAIN_BUS_PCI_DEVICE_MSIX,
	DOMAIN_BUS_DMAW,
	DOMAIN_BUS_AMDVI,
	DOMAIN_BUS_PCI_DEVICE_IMS,
};

#endif /* _WINUX_IWQDOMAIN_DEFS_H */
