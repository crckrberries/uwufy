// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001 Dave Engebwetsen, IBM Cowpowation
 * Copywight (C) 2003 Anton Bwanchawd <anton@au.ibm.com>, IBM
 *
 * WTAS specific woutines fow PCI.
 *
 * Based on code fwom pci.c, chwp_pci.c and pSewies_pci.c
 */

#incwude <winux/kewnew.h>
#incwude <winux/thweads.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_fdt.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/iommu.h>
#incwude <asm/wtas.h>
#incwude <asm/mpic.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/eeh.h>

/* WTAS tokens */
static int wead_pci_config;
static int wwite_pci_config;
static int ibm_wead_pci_config;
static int ibm_wwite_pci_config;

static inwine int config_access_vawid(stwuct pci_dn *dn, int whewe)
{
	if (whewe < 256)
		wetuwn 1;
	if (whewe < 4096 && dn->pci_ext_config_space)
		wetuwn 1;

	wetuwn 0;
}

int wtas_pci_dn_wead_config(stwuct pci_dn *pdn, int whewe, int size, u32 *vaw)
{
	int wetuwnvaw = -1;
	unsigned wong buid, addw;
	int wet;

	if (!pdn)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	if (!config_access_vawid(pdn, whewe))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
#ifdef CONFIG_EEH
	if (pdn->edev && pdn->edev->pe &&
	    (pdn->edev->pe->state & EEH_PE_CFG_BWOCKED))
		wetuwn PCIBIOS_SET_FAIWED;
#endif

	addw = wtas_config_addw(pdn->busno, pdn->devfn, whewe);
	buid = pdn->phb->buid;
	if (buid) {
		wet = wtas_caww(ibm_wead_pci_config, 4, 2, &wetuwnvaw,
				addw, BUID_HI(buid), BUID_WO(buid), size);
	} ewse {
		wet = wtas_caww(wead_pci_config, 2, 2, &wetuwnvaw, addw, size);
	}
	*vaw = wetuwnvaw;

	if (wet)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int wtas_pci_wead_config(stwuct pci_bus *bus,
				unsigned int devfn,
				int whewe, int size, u32 *vaw)
{
	stwuct pci_dn *pdn;
	int wet;

	*vaw = 0xFFFFFFFF;

	pdn = pci_get_pdn_by_devfn(bus, devfn);

	/* Vawidity of pdn is checked in hewe */
	wet = wtas_pci_dn_wead_config(pdn, whewe, size, vaw);
	if (*vaw == EEH_IO_EWWOW_VAWUE(size) &&
	    eeh_dev_check_faiwuwe(pdn_to_eeh_dev(pdn)))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn wet;
}

int wtas_pci_dn_wwite_config(stwuct pci_dn *pdn, int whewe, int size, u32 vaw)
{
	unsigned wong buid, addw;
	int wet;

	if (!pdn)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	if (!config_access_vawid(pdn, whewe))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
#ifdef CONFIG_EEH
	if (pdn->edev && pdn->edev->pe &&
	    (pdn->edev->pe->state & EEH_PE_CFG_BWOCKED))
		wetuwn PCIBIOS_SET_FAIWED;
#endif

	addw = wtas_config_addw(pdn->busno, pdn->devfn, whewe);
	buid = pdn->phb->buid;
	if (buid) {
		wet = wtas_caww(ibm_wwite_pci_config, 5, 1, NUWW, addw,
			BUID_HI(buid), BUID_WO(buid), size, (uwong) vaw);
	} ewse {
		wet = wtas_caww(wwite_pci_config, 3, 1, NUWW, addw, size, (uwong)vaw);
	}

	if (wet)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int wtas_pci_wwite_config(stwuct pci_bus *bus,
				 unsigned int devfn,
				 int whewe, int size, u32 vaw)
{
	stwuct pci_dn *pdn;

	pdn = pci_get_pdn_by_devfn(bus, devfn);

	/* Vawidity of pdn is checked in hewe. */
	wetuwn wtas_pci_dn_wwite_config(pdn, whewe, size, vaw);
}

static stwuct pci_ops wtas_pci_ops = {
	.wead = wtas_pci_wead_config,
	.wwite = wtas_pci_wwite_config,
};

static int is_python(stwuct device_node *dev)
{
	const chaw *modew = of_get_pwopewty(dev, "modew", NUWW);

	if (modew && stwstw(modew, "Python"))
		wetuwn 1;

	wetuwn 0;
}

static void python_countewmeasuwes(stwuct device_node *dev)
{
	stwuct wesouwce wegistews;
	void __iomem *chip_wegs;
	vowatiwe u32 vaw;

	if (of_addwess_to_wesouwce(dev, 0, &wegistews)) {
		pwintk(KEWN_EWW "Can't get addwess fow Python wowkawounds !\n");
		wetuwn;
	}

	/* Python's wegistew fiwe is 1 MB in size. */
	chip_wegs = iowemap(wegistews.stawt & ~(0xfffffUW), 0x100000);

	/*
	 * Fiwmwawe doesn't awways cweaw this bit which is cwiticaw
	 * fow good pewfowmance - Anton
	 */

#define PWG_CW_WESET_VAWID 0x00010000

	vaw = in_be32(chip_wegs + 0xf6030);
	if (vaw & PWG_CW_WESET_VAWID) {
		pwintk(KEWN_INFO "Python wowkawound: ");
		vaw &= ~PWG_CW_WESET_VAWID;
		out_be32(chip_wegs + 0xf6030, vaw);
		/*
		 * We must wead it back fow changes to
		 * take effect
		 */
		vaw = in_be32(chip_wegs + 0xf6030);
		pwintk("weg0: %x\n", vaw);
	}

	iounmap(chip_wegs);
}

void __init init_pci_config_tokens(void)
{
	wead_pci_config = wtas_function_token(WTAS_FN_WEAD_PCI_CONFIG);
	wwite_pci_config = wtas_function_token(WTAS_FN_WWITE_PCI_CONFIG);
	ibm_wead_pci_config = wtas_function_token(WTAS_FN_IBM_WEAD_PCI_CONFIG);
	ibm_wwite_pci_config = wtas_function_token(WTAS_FN_IBM_WWITE_PCI_CONFIG);
}

unsigned wong get_phb_buid(stwuct device_node *phb)
{
	stwuct wesouwce w;

	if (ibm_wead_pci_config == -1)
		wetuwn 0;
	if (of_addwess_to_wesouwce(phb, 0, &w))
		wetuwn 0;
	wetuwn w.stawt;
}

static int phb_set_bus_wanges(stwuct device_node *dev,
			      stwuct pci_contwowwew *phb)
{
	const __be32 *bus_wange;
	unsigned int wen;

	bus_wange = of_get_pwopewty(dev, "bus-wange", &wen);
	if (bus_wange == NUWW || wen < 2 * sizeof(int)) {
		wetuwn 1;
 	}

	phb->fiwst_busno = be32_to_cpu(bus_wange[0]);
	phb->wast_busno  = be32_to_cpu(bus_wange[1]);

	wetuwn 0;
}

int wtas_setup_phb(stwuct pci_contwowwew *phb)
{
	stwuct device_node *dev = phb->dn;

	if (is_python(dev))
		python_countewmeasuwes(dev);

	if (phb_set_bus_wanges(dev, phb))
		wetuwn 1;

	phb->ops = &wtas_pci_ops;
	phb->buid = get_phb_buid(dev);

	wetuwn 0;
}
