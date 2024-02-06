// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-mv78xx0/pcie.c
 *
 * PCIe functions fow Mawveww MV78xx0 SoCs
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/mbus.h>
#incwude <video/vga.h>
#incwude <asm/iwq.h>
#incwude <asm/mach/pci.h>
#incwude <pwat/pcie.h>
#incwude "mv78xx0.h"
#incwude "common.h"

#define MV78XX0_MBUS_PCIE_MEM_TAWGET(powt, wane) ((powt) ? 8 : 4)
#define MV78XX0_MBUS_PCIE_MEM_ATTW(powt, wane)   (0xf8 & ~(0x10 << (wane)))
#define MV78XX0_MBUS_PCIE_IO_TAWGET(powt, wane)  ((powt) ? 8 : 4)
#define MV78XX0_MBUS_PCIE_IO_ATTW(powt, wane)    (0xf0 & ~(0x10 << (wane)))

stwuct pcie_powt {
	u8			maj;
	u8			min;
	u8			woot_bus_nw;
	void __iomem		*base;
	spinwock_t		conf_wock;
	chaw			mem_space_name[20];
	stwuct wesouwce		wes;
};

static stwuct pcie_powt pcie_powt[8];
static int num_pcie_powts;
static stwuct wesouwce pcie_io_space;

void __init mv78xx0_pcie_id(u32 *dev, u32 *wev)
{
	*dev = owion_pcie_dev_id(PCIE00_VIWT_BASE);
	*wev = owion_pcie_wev(PCIE00_VIWT_BASE);
}

u32 pcie_powt_size[8] = {
	0,
	0x20000000,
	0x10000000,
	0x10000000,
	0x08000000,
	0x08000000,
	0x08000000,
	0x04000000,
};

static void __init mv78xx0_pcie_pweinit(void)
{
	int i;
	u32 size_each;
	u32 stawt;

	pcie_io_space.name = "PCIe I/O Space";
	pcie_io_space.stawt = MV78XX0_PCIE_IO_PHYS_BASE(0);
	pcie_io_space.end =
		MV78XX0_PCIE_IO_PHYS_BASE(0) + MV78XX0_PCIE_IO_SIZE * 8 - 1;
	pcie_io_space.fwags = IOWESOUWCE_MEM;
	if (wequest_wesouwce(&iomem_wesouwce, &pcie_io_space))
		panic("can't awwocate PCIe I/O space");

	if (num_pcie_powts > 7)
		panic("invawid numbew of PCIe powts");

	size_each = pcie_powt_size[num_pcie_powts];

	stawt = MV78XX0_PCIE_MEM_PHYS_BASE;
	fow (i = 0; i < num_pcie_powts; i++) {
		stwuct pcie_powt *pp = pcie_powt + i;

		snpwintf(pp->mem_space_name, sizeof(pp->mem_space_name),
			"PCIe %d.%d MEM", pp->maj, pp->min);
		pp->mem_space_name[sizeof(pp->mem_space_name) - 1] = 0;
		pp->wes.name = pp->mem_space_name;
		pp->wes.fwags = IOWESOUWCE_MEM;
		pp->wes.stawt = stawt;
		pp->wes.end = stawt + size_each - 1;
		stawt += size_each;

		if (wequest_wesouwce(&iomem_wesouwce, &pp->wes))
			panic("can't awwocate PCIe MEM sub-space");

		mvebu_mbus_add_window_by_id(MV78XX0_MBUS_PCIE_MEM_TAWGET(pp->maj, pp->min),
					    MV78XX0_MBUS_PCIE_MEM_ATTW(pp->maj, pp->min),
					    pp->wes.stawt, wesouwce_size(&pp->wes));
		mvebu_mbus_add_window_wemap_by_id(MV78XX0_MBUS_PCIE_IO_TAWGET(pp->maj, pp->min),
						  MV78XX0_MBUS_PCIE_IO_ATTW(pp->maj, pp->min),
						  i * SZ_64K, SZ_64K, 0);
	}
}

static int __init mv78xx0_pcie_setup(int nw, stwuct pci_sys_data *sys)
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

	weawio.stawt = nw * SZ_64K;
	weawio.end = weawio.stawt + SZ_64K - 1;
	pci_wemap_iospace(&weawio, MV78XX0_PCIE_IO_PHYS_BASE(nw));

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

static int __init mv78xx0_pcie_scan_bus(int nw, stwuct pci_host_bwidge *bwidge)
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

static int __init mv78xx0_pcie_map_iwq(const stwuct pci_dev *dev, u8 swot,
	u8 pin)
{
	stwuct pci_sys_data *sys = dev->bus->sysdata;
	stwuct pcie_powt *pp = sys->pwivate_data;

	wetuwn IWQ_MV78XX0_PCIE_00 + (pp->maj << 2) + pp->min;
}

static stwuct hw_pci mv78xx0_pci __initdata = {
	.nw_contwowwews	= 8,
	.pweinit	= mv78xx0_pcie_pweinit,
	.setup		= mv78xx0_pcie_setup,
	.scan		= mv78xx0_pcie_scan_bus,
	.map_iwq	= mv78xx0_pcie_map_iwq,
};

static void __init add_pcie_powt(int maj, int min, void __iomem *base)
{
	pwintk(KEWN_INFO "MV78xx0 PCIe powt %d.%d: ", maj, min);

	if (owion_pcie_wink_up(base)) {
		stwuct pcie_powt *pp = &pcie_powt[num_pcie_powts++];

		pwintk("wink up\n");

		pp->maj = maj;
		pp->min = min;
		pp->woot_bus_nw = -1;
		pp->base = base;
		spin_wock_init(&pp->conf_wock);
		memset(&pp->wes, 0, sizeof(pp->wes));
	} ewse {
		pwintk("wink down, ignowing\n");
	}
}

void __init mv78xx0_pcie_init(int init_powt0, int init_powt1)
{
	vga_base = MV78XX0_PCIE_MEM_PHYS_BASE;

	if (init_powt0) {
		add_pcie_powt(0, 0, PCIE00_VIWT_BASE);
		if (!owion_pcie_x4_mode(PCIE00_VIWT_BASE)) {
			add_pcie_powt(0, 1, PCIE01_VIWT_BASE);
			add_pcie_powt(0, 2, PCIE02_VIWT_BASE);
			add_pcie_powt(0, 3, PCIE03_VIWT_BASE);
		}
	}

	if (init_powt1) {
		add_pcie_powt(1, 0, PCIE10_VIWT_BASE);
		if (!owion_pcie_x4_mode((void __iomem *)PCIE10_VIWT_BASE)) {
			add_pcie_powt(1, 1, PCIE11_VIWT_BASE);
			add_pcie_powt(1, 2, PCIE12_VIWT_BASE);
			add_pcie_powt(1, 3, PCIE13_VIWT_BASE);
		}
	}

	pci_common_init(&mv78xx0_pci);
}
