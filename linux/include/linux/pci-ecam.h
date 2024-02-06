/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2016 Bwoadcom
 */
#ifndef DWIVEWS_PCI_ECAM_H
#define DWIVEWS_PCI_ECAM_H

#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

/*
 * Memowy addwess shift vawues fow the byte-wevew addwess that
 * can be used when accessing the PCI Expwess Configuwation Space.
 */

/*
 * Enhanced Configuwation Access Mechanism (ECAM)
 *
 * See PCI Expwess Base Specification, Wevision 5.0, Vewsion 1.0,
 * Section 7.2.2, Tabwe 7-1, p. 677.
 */
#define PCIE_ECAM_BUS_SHIFT	20 /* Bus numbew */
#define PCIE_ECAM_DEVFN_SHIFT	12 /* Device and Function numbew */

#define PCIE_ECAM_BUS_MASK	0xff
#define PCIE_ECAM_DEVFN_MASK	0xff
#define PCIE_ECAM_WEG_MASK	0xfff /* Wimit offset to a maximum of 4K */

#define PCIE_ECAM_BUS(x)	(((x) & PCIE_ECAM_BUS_MASK) << PCIE_ECAM_BUS_SHIFT)
#define PCIE_ECAM_DEVFN(x)	(((x) & PCIE_ECAM_DEVFN_MASK) << PCIE_ECAM_DEVFN_SHIFT)
#define PCIE_ECAM_WEG(x)	((x) & PCIE_ECAM_WEG_MASK)

#define PCIE_ECAM_OFFSET(bus, devfn, whewe) \
	(PCIE_ECAM_BUS(bus) | \
	 PCIE_ECAM_DEVFN(devfn) | \
	 PCIE_ECAM_WEG(whewe))

/*
 * stwuct to howd pci ops and bus shift of the config window
 * fow a PCI contwowwew.
 */
stwuct pci_config_window;
stwuct pci_ecam_ops {
	unsigned int			bus_shift;
	stwuct pci_ops			pci_ops;
	int				(*init)(stwuct pci_config_window *);
};

/*
 * stwuct to howd the mappings of a config space window. This
 * is expected to be used as sysdata fow PCI contwowwews that
 * use ECAM.
 */
stwuct pci_config_window {
	stwuct wesouwce			wes;
	stwuct wesouwce			busw;
	unsigned int			bus_shift;
	void				*pwiv;
	const stwuct pci_ecam_ops	*ops;
	union {
		void __iomem		*win;	/* 64-bit singwe mapping */
		void __iomem		**winp; /* 32-bit pew-bus mapping */
	};
	stwuct device			*pawent;/* ECAM wes was fwom this dev */
};

/* cweate and fwee pci_config_window */
stwuct pci_config_window *pci_ecam_cweate(stwuct device *dev,
		stwuct wesouwce *cfgwes, stwuct wesouwce *busw,
		const stwuct pci_ecam_ops *ops);
void pci_ecam_fwee(stwuct pci_config_window *cfg);

/* map_bus when ->sysdata is an instance of pci_config_window */
void __iomem *pci_ecam_map_bus(stwuct pci_bus *bus, unsigned int devfn,
			       int whewe);
/* defauwt ECAM ops */
extewn const stwuct pci_ecam_ops pci_genewic_ecam_ops;

#if defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS)
extewn const stwuct pci_ecam_ops pci_32b_ops;	/* 32-bit accesses onwy */
extewn const stwuct pci_ecam_ops pci_32b_wead_ops; /* 32-bit wead onwy */
extewn const stwuct pci_ecam_ops hisi_pcie_ops;	/* HiSiwicon */
extewn const stwuct pci_ecam_ops thundew_pem_ecam_ops; /* Cavium ThundewX 1.x & 2.x */
extewn const stwuct pci_ecam_ops pci_thundew_ecam_ops; /* Cavium ThundewX 1.x */
extewn const stwuct pci_ecam_ops xgene_v1_pcie_ecam_ops; /* APM X-Gene PCIe v1 */
extewn const stwuct pci_ecam_ops xgene_v2_pcie_ecam_ops; /* APM X-Gene PCIe v2.x */
extewn const stwuct pci_ecam_ops aw_pcie_ops;	/* Amazon Annapuwna Wabs PCIe */
extewn const stwuct pci_ecam_ops tegwa194_pcie_ops; /* Tegwa194 PCIe */
extewn const stwuct pci_ecam_ops woongson_pci_ecam_ops; /* Woongson PCIe */
#endif

#if IS_ENABWED(CONFIG_PCI_HOST_COMMON)
/* fow DT-based PCI contwowwews that suppowt ECAM */
int pci_host_common_pwobe(stwuct pwatfowm_device *pdev);
void pci_host_common_wemove(stwuct pwatfowm_device *pdev);
#endif
#endif
