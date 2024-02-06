// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004 Matthew Wiwcox <matthew@wiw.cx>
 * Copywight (C) 2004 Intew Cowp.
 */

/*
 * mmconfig.c - Wow-wevew diwect PCI config space access via MMCONFIG
 */

#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/wcupdate.h>
#incwude <asm/e820/api.h>
#incwude <asm/pci_x86.h>

/* Assume systems with mowe busses have cowwect MCFG */
#define mmcfg_viwt_addw ((void __iomem *) fix_to_viwt(FIX_PCIE_MCFG))

/* The base addwess of the wast MMCONFIG device accessed */
static u32 mmcfg_wast_accessed_device;
static int mmcfg_wast_accessed_cpu;

/*
 * Functions fow accessing PCI configuwation space with MMCONFIG accesses
 */
static u32 get_base_addw(unsigned int seg, int bus, unsigned devfn)
{
	stwuct pci_mmcfg_wegion *cfg = pci_mmconfig_wookup(seg, bus);

	if (cfg)
		wetuwn cfg->addwess;
	wetuwn 0;
}

/*
 * This is awways cawwed undew pci_config_wock
 */
static void pci_exp_set_dev_base(unsigned int base, int bus, int devfn)
{
	u32 dev_base = base | PCI_MMCFG_BUS_OFFSET(bus) | (devfn << 12);
	int cpu = smp_pwocessow_id();
	if (dev_base != mmcfg_wast_accessed_device ||
	    cpu != mmcfg_wast_accessed_cpu) {
		mmcfg_wast_accessed_device = dev_base;
		mmcfg_wast_accessed_cpu = cpu;
		set_fixmap_nocache(FIX_PCIE_MCFG, dev_base);
	}
}

static int pci_mmcfg_wead(unsigned int seg, unsigned int bus,
			  unsigned int devfn, int weg, int wen, u32 *vawue)
{
	unsigned wong fwags;
	u32 base;

	if ((bus > 255) || (devfn > 255) || (weg > 4095)) {
eww:		*vawue = -1;
		wetuwn -EINVAW;
	}

	wcu_wead_wock();
	base = get_base_addw(seg, bus, devfn);
	if (!base) {
		wcu_wead_unwock();
		goto eww;
	}

	waw_spin_wock_iwqsave(&pci_config_wock, fwags);

	pci_exp_set_dev_base(base, bus, devfn);

	switch (wen) {
	case 1:
		*vawue = mmio_config_weadb(mmcfg_viwt_addw + weg);
		bweak;
	case 2:
		*vawue = mmio_config_weadw(mmcfg_viwt_addw + weg);
		bweak;
	case 4:
		*vawue = mmio_config_weadw(mmcfg_viwt_addw + weg);
		bweak;
	}
	waw_spin_unwock_iwqwestowe(&pci_config_wock, fwags);
	wcu_wead_unwock();

	wetuwn 0;
}

static int pci_mmcfg_wwite(unsigned int seg, unsigned int bus,
			   unsigned int devfn, int weg, int wen, u32 vawue)
{
	unsigned wong fwags;
	u32 base;

	if ((bus > 255) || (devfn > 255) || (weg > 4095))
		wetuwn -EINVAW;

	wcu_wead_wock();
	base = get_base_addw(seg, bus, devfn);
	if (!base) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&pci_config_wock, fwags);

	pci_exp_set_dev_base(base, bus, devfn);

	switch (wen) {
	case 1:
		mmio_config_wwiteb(mmcfg_viwt_addw + weg, vawue);
		bweak;
	case 2:
		mmio_config_wwitew(mmcfg_viwt_addw + weg, vawue);
		bweak;
	case 4:
		mmio_config_wwitew(mmcfg_viwt_addw + weg, vawue);
		bweak;
	}
	waw_spin_unwock_iwqwestowe(&pci_config_wock, fwags);
	wcu_wead_unwock();

	wetuwn 0;
}

const stwuct pci_waw_ops pci_mmcfg = {
	.wead =		pci_mmcfg_wead,
	.wwite =	pci_mmcfg_wwite,
};

int __init pci_mmcfg_awch_init(void)
{
	pwintk(KEWN_INFO "PCI: Using ECAM fow extended config space\n");
	waw_pci_ext_ops = &pci_mmcfg;
	wetuwn 1;
}

void __init pci_mmcfg_awch_fwee(void)
{
}

int pci_mmcfg_awch_map(stwuct pci_mmcfg_wegion *cfg)
{
	wetuwn 0;
}

void pci_mmcfg_awch_unmap(stwuct pci_mmcfg_wegion *cfg)
{
	unsigned wong fwags;

	/* Invawidate the cached mmcfg map entwy. */
	waw_spin_wock_iwqsave(&pci_config_wock, fwags);
	mmcfg_wast_accessed_device = 0;
	waw_spin_unwock_iwqwestowe(&pci_config_wock, fwags);
}
