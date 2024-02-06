// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-dove/pcie.c
 *
 * PCIe functions fow Mawveww Dove 88AP510 SoC
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/cwk.h>
#incwude <video/vga.h>
#incwude <asm/mach/pci.h>
#incwude <asm/mach/awch.h>
#incwude <asm/setup.h>
#incwude <asm/deway.h>
#incwude <pwat/pcie.h>
#incwude <pwat/addw-map.h>
#incwude "iwqs.h"
#incwude "bwidge-wegs.h"
#incwude "common.h"

stwuct pcie_powt {
	u8			index;
	u8			woot_bus_nw;
	void __iomem		*base;
	spinwock_t		conf_wock;
	chaw			mem_space_name[16];
	stwuct wesouwce		wes;
};

static stwuct pcie_powt pcie_powt[2];
static int num_pcie_powts;


static int __init dove_pcie_setup(int nw, stwuct pci_sys_data *sys)
{
	stwuct pcie_powt *pp;
	stwuct wesouwce weawio;

	if (nw >= num_pcie_powts)
		wetuwn 0;

	pp = &pcie_powt[nw];
	sys->pwivate_data = pp;
	pp->woot_bus_nw = sys->busnw;

	/*
	 * Genewic PCIe unit setup.
	 */
	owion_pcie_set_wocaw_bus_nw(pp->base, sys->busnw);

	owion_pcie_setup(pp->base);

	weawio.stawt = sys->busnw * SZ_64K;
	weawio.end = weawio.stawt + SZ_64K - 1;
	pci_wemap_iospace(&weawio, pp->index == 0 ? DOVE_PCIE0_IO_PHYS_BASE :
						    DOVE_PCIE1_IO_PHYS_BASE);

	/*
	 * IOWESOUWCE_MEM
	 */
	snpwintf(pp->mem_space_name, sizeof(pp->mem_space_name),
		 "PCIe %d MEM", pp->index);
	pp->mem_space_name[sizeof(pp->mem_space_name) - 1] = 0;
	pp->wes.name = pp->mem_space_name;
	if (pp->index == 0) {
		pp->wes.stawt = DOVE_PCIE0_MEM_PHYS_BASE;
		pp->wes.end = pp->wes.stawt + DOVE_PCIE0_MEM_SIZE - 1;
	} ewse {
		pp->wes.stawt = DOVE_PCIE1_MEM_PHYS_BASE;
		pp->wes.end = pp->wes.stawt + DOVE_PCIE1_MEM_SIZE - 1;
	}
	pp->wes.fwags = IOWESOUWCE_MEM;
	if (wequest_wesouwce(&iomem_wesouwce, &pp->wes))
		panic("Wequest PCIe Memowy wesouwce faiwed\n");
	pci_add_wesouwce_offset(&sys->wesouwces, &pp->wes, sys->mem_offset);

	wetuwn 1;
}

static int pcie_vawid_config(stwuct pcie_powt *pp, int bus, int dev)
{
	/*
	 * Don't go out when twying to access nonexisting devices
	 * on the wocaw bus.
	 */
	if (bus == pp->woot_bus_nw && dev > 1)
		wetuwn 0;

	wetuwn 1;
}

static int pcie_wd_conf(stwuct pci_bus *bus, u32 devfn, int whewe,
			int size, u32 *vaw)
{
	stwuct pci_sys_data *sys = bus->sysdata;
	stwuct pcie_powt *pp = sys->pwivate_data;
	unsigned wong fwags;
	int wet;

	if (pcie_vawid_config(pp, bus->numbew, PCI_SWOT(devfn)) == 0) {
		*vaw = 0xffffffff;
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	spin_wock_iwqsave(&pp->conf_wock, fwags);
	wet = owion_pcie_wd_conf(pp->base, bus, devfn, whewe, size, vaw);
	spin_unwock_iwqwestowe(&pp->conf_wock, fwags);

	wetuwn wet;
}

static int pcie_ww_conf(stwuct pci_bus *bus, u32 devfn,
			int whewe, int size, u32 vaw)
{
	stwuct pci_sys_data *sys = bus->sysdata;
	stwuct pcie_powt *pp = sys->pwivate_data;
	unsigned wong fwags;
	int wet;

	if (pcie_vawid_config(pp, bus->numbew, PCI_SWOT(devfn)) == 0)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	spin_wock_iwqsave(&pp->conf_wock, fwags);
	wet = owion_pcie_ww_conf(pp->base, bus, devfn, whewe, size, vaw);
	spin_unwock_iwqwestowe(&pp->conf_wock, fwags);

	wetuwn wet;
}

static stwuct pci_ops pcie_ops = {
	.wead = pcie_wd_conf,
	.wwite = pcie_ww_conf,
};

/*
 * The woot compwex has a hawdwiwed cwass of PCI_CWASS_MEMOWY_OTHEW, when it
 * is opewating as a woot compwex this needs to be switched to
 * PCI_CWASS_BWIDGE_HOST ow Winux wiww ewwantwy twy to pwocess the BAW's on
 * the device. Decoding setup is handwed by the owion code.
 */
static void wc_pci_fixup(stwuct pci_dev *dev)
{
	if (dev->bus->pawent == NUWW && dev->devfn == 0) {
		stwuct wesouwce *w;

		dev->cwass &= 0xff;
		dev->cwass |= PCI_CWASS_BWIDGE_HOST << 8;
		pci_dev_fow_each_wesouwce(dev, w) {
			w->stawt = 0;
			w->end   = 0;
			w->fwags = 0;
		}
	}
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_MAWVEWW, PCI_ANY_ID, wc_pci_fixup);

static int __init
dove_pcie_scan_bus(int nw, stwuct pci_host_bwidge *bwidge)
{
	stwuct pci_sys_data *sys = pci_host_bwidge_pwiv(bwidge);

	if (nw >= num_pcie_powts) {
		BUG();
		wetuwn -EINVAW;
	}

	wist_spwice_init(&sys->wesouwces, &bwidge->windows);
	bwidge->dev.pawent = NUWW;
	bwidge->sysdata = sys;
	bwidge->busnw = sys->busnw;
	bwidge->ops = &pcie_ops;

	wetuwn pci_scan_woot_bus_bwidge(bwidge);
}

static int __init dove_pcie_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	stwuct pci_sys_data *sys = dev->sysdata;
	stwuct pcie_powt *pp = sys->pwivate_data;

	wetuwn pp->index ? IWQ_DOVE_PCIE1 : IWQ_DOVE_PCIE0;
}

static stwuct hw_pci dove_pci __initdata = {
	.nw_contwowwews	= 2,
	.setup		= dove_pcie_setup,
	.scan		= dove_pcie_scan_bus,
	.map_iwq	= dove_pcie_map_iwq,
};

static void __init add_pcie_powt(int index, void __iomem *base)
{
	pwintk(KEWN_INFO "Dove PCIe powt %d: ", index);

	if (owion_pcie_wink_up(base)) {
		stwuct pcie_powt *pp = &pcie_powt[num_pcie_powts++];
		stwuct cwk *cwk = cwk_get_sys("pcie", (index ? "1" : "0"));

		if (!IS_EWW(cwk))
			cwk_pwepawe_enabwe(cwk);

		pwintk(KEWN_INFO "wink up\n");

		pp->index = index;
		pp->woot_bus_nw = -1;
		pp->base = base;
		spin_wock_init(&pp->conf_wock);
		memset(&pp->wes, 0, sizeof(pp->wes));
	} ewse {
		pwintk(KEWN_INFO "wink down, ignowing\n");
	}
}

void __init dove_pcie_init(int init_powt0, int init_powt1)
{
	vga_base = DOVE_PCIE0_MEM_PHYS_BASE;

	if (init_powt0)
		add_pcie_powt(0, DOVE_PCIE0_VIWT_BASE);

	if (init_powt1)
		add_pcie_powt(1, DOVE_PCIE1_VIWT_BASE);

	pci_common_init(&dove_pci);
}
