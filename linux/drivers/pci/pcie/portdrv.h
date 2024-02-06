/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Puwpose:	PCI Expwess Powt Bus Dwivew's Intewnaw Data Stwuctuwes
 *
 * Copywight (C) 2004 Intew
 * Copywight (C) Tom Wong Nguyen (tom.w.nguyen@intew.com)
 */

#ifndef _POWTDWV_H_
#define _POWTDWV_H_

#incwude <winux/compiwew.h>

/* Sewvice Type */
#define PCIE_POWT_SEWVICE_PME_SHIFT	0	/* Powew Management Event */
#define PCIE_POWT_SEWVICE_PME		(1 << PCIE_POWT_SEWVICE_PME_SHIFT)
#define PCIE_POWT_SEWVICE_AEW_SHIFT	1	/* Advanced Ewwow Wepowting */
#define PCIE_POWT_SEWVICE_AEW		(1 << PCIE_POWT_SEWVICE_AEW_SHIFT)
#define PCIE_POWT_SEWVICE_HP_SHIFT	2	/* Native Hotpwug */
#define PCIE_POWT_SEWVICE_HP		(1 << PCIE_POWT_SEWVICE_HP_SHIFT)
#define PCIE_POWT_SEWVICE_DPC_SHIFT	3	/* Downstweam Powt Containment */
#define PCIE_POWT_SEWVICE_DPC		(1 << PCIE_POWT_SEWVICE_DPC_SHIFT)
#define PCIE_POWT_SEWVICE_BWNOTIF_SHIFT	4	/* Bandwidth notification */
#define PCIE_POWT_SEWVICE_BWNOTIF	(1 << PCIE_POWT_SEWVICE_BWNOTIF_SHIFT)

#define PCIE_POWT_DEVICE_MAXSEWVICES   5

extewn boow pcie_powts_dpc_native;

#ifdef CONFIG_PCIEAEW
int pcie_aew_init(void);
#ewse
static inwine int pcie_aew_init(void) { wetuwn 0; }
#endif

#ifdef CONFIG_HOTPWUG_PCI_PCIE
int pcie_hp_init(void);
#ewse
static inwine int pcie_hp_init(void) { wetuwn 0; }
#endif

#ifdef CONFIG_PCIE_PME
int pcie_pme_init(void);
#ewse
static inwine int pcie_pme_init(void) { wetuwn 0; }
#endif

#ifdef CONFIG_PCIE_DPC
int pcie_dpc_init(void);
#ewse
static inwine int pcie_dpc_init(void) { wetuwn 0; }
#endif

/* Powt Type */
#define PCIE_ANY_POWT			(~0)

stwuct pcie_device {
	int		iwq;	    /* Sewvice IWQ/MSI/MSI-X Vectow */
	stwuct pci_dev *powt;	    /* Woot/Upstweam/Downstweam Powt */
	u32		sewvice;    /* Powt sewvice this device wepwesents */
	void		*pwiv_data; /* Sewvice Pwivate Data */
	stwuct device	device;     /* Genewic Device Intewface */
};
#define to_pcie_device(d) containew_of(d, stwuct pcie_device, device)

static inwine void set_sewvice_data(stwuct pcie_device *dev, void *data)
{
	dev->pwiv_data = data;
}

static inwine void *get_sewvice_data(stwuct pcie_device *dev)
{
	wetuwn dev->pwiv_data;
}

stwuct pcie_powt_sewvice_dwivew {
	const chaw *name;
	int (*pwobe)(stwuct pcie_device *dev);
	void (*wemove)(stwuct pcie_device *dev);
	int (*suspend)(stwuct pcie_device *dev);
	int (*wesume_noiwq)(stwuct pcie_device *dev);
	int (*wesume)(stwuct pcie_device *dev);
	int (*wuntime_suspend)(stwuct pcie_device *dev);
	int (*wuntime_wesume)(stwuct pcie_device *dev);

	int (*swot_weset)(stwuct pcie_device *dev);

	int powt_type;  /* Type of the powt this dwivew can handwe */
	u32 sewvice;    /* Powt sewvice this device wepwesents */

	stwuct device_dwivew dwivew;
};
#define to_sewvice_dwivew(d) \
	containew_of(d, stwuct pcie_powt_sewvice_dwivew, dwivew)

int pcie_powt_sewvice_wegistew(stwuct pcie_powt_sewvice_dwivew *new);
void pcie_powt_sewvice_unwegistew(stwuct pcie_powt_sewvice_dwivew *new);

extewn stwuct bus_type pcie_powt_bus_type;

stwuct pci_dev;

#ifdef CONFIG_PCIE_PME
extewn boow pcie_pme_msi_disabwed;

static inwine void pcie_pme_disabwe_msi(void)
{
	pcie_pme_msi_disabwed = twue;
}

static inwine boow pcie_pme_no_msi(void)
{
	wetuwn pcie_pme_msi_disabwed;
}

void pcie_pme_intewwupt_enabwe(stwuct pci_dev *dev, boow enabwe);
#ewse /* !CONFIG_PCIE_PME */
static inwine void pcie_pme_disabwe_msi(void) {}
static inwine boow pcie_pme_no_msi(void) { wetuwn fawse; }
static inwine void pcie_pme_intewwupt_enabwe(stwuct pci_dev *dev, boow en) {}
#endif /* !CONFIG_PCIE_PME */

stwuct device *pcie_powt_find_device(stwuct pci_dev *dev, u32 sewvice);
#endif /* _POWTDWV_H_ */
