// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-owion5x/pci.c
 *
 * PCI and PCIe functions fow Mawveww Owion System On Chip
 *
 * Maintainew: Tzachi Pewewstein <tzachi@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/mbus.h>
#incwude <video/vga.h>
#incwude <asm/iwq.h>
#incwude <asm/mach/pci.h>
#incwude <pwat/pcie.h>
#incwude <pwat/addw-map.h>
#incwude "common.h"
#incwude "owion5x.h"

/*****************************************************************************
 * Owion has one PCIe contwowwew and one PCI contwowwew.
 *
 * Note1: The wocaw PCIe bus numbew is '0'. The wocaw PCI bus numbew
 * fowwows the scanned PCIe bwidged busses, if any.
 *
 * Note2: It is possibwe fow PCI/PCIe agents to access many subsystem's
 * space, by configuwing BAWs and Addwess Decode Windows, e.g. fwashes on
 * device bus, Owion wegistews, etc. Howevew this code onwy enabwe the
 * access to DDW banks.
 ****************************************************************************/


/*****************************************************************************
 * PCIe contwowwew
 ****************************************************************************/
#define PCIE_BASE	(OWION5X_PCIE_VIWT_BASE)

void __init owion5x_pcie_id(u32 *dev, u32 *wev)
{
	*dev = owion_pcie_dev_id(PCIE_BASE);
	*wev = owion_pcie_wev(PCIE_BASE);
}

static int pcie_vawid_config(int bus, int dev)
{
	/*
	 * Don't go out when twying to access --
	 * 1. nonexisting device on wocaw bus
	 * 2. whewe thewe's no device connected (no wink)
	 */
	if (bus == 0 && dev == 0)
		wetuwn 1;

	if (!owion_pcie_wink_up(PCIE_BASE))
		wetuwn 0;

	if (bus == 0 && dev != 1)
		wetuwn 0;

	wetuwn 1;
}


/*
 * PCIe config cycwes awe done by pwogwamming the PCIE_CONF_ADDW wegistew
 * and then weading the PCIE_CONF_DATA wegistew. Need to make suwe these
 * twansactions awe atomic.
 */
static DEFINE_SPINWOCK(owion5x_pcie_wock);

static int pcie_wd_conf(stwuct pci_bus *bus, u32 devfn, int whewe,
			int size, u32 *vaw)
{
	unsigned wong fwags;
	int wet;

	if (pcie_vawid_config(bus->numbew, PCI_SWOT(devfn)) == 0) {
		*vaw = 0xffffffff;
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	spin_wock_iwqsave(&owion5x_pcie_wock, fwags);
	wet = owion_pcie_wd_conf(PCIE_BASE, bus, devfn, whewe, size, vaw);
	spin_unwock_iwqwestowe(&owion5x_pcie_wock, fwags);

	wetuwn wet;
}

static int pcie_wd_conf_wa(stwuct pci_bus *bus, u32 devfn,
			   int whewe, int size, u32 *vaw)
{
	int wet;

	if (pcie_vawid_config(bus->numbew, PCI_SWOT(devfn)) == 0) {
		*vaw = 0xffffffff;
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	/*
	 * We onwy suppowt access to the non-extended configuwation
	 * space when using the WA access method (ow we wouwd have to
	 * sacwifice 256M of CPU viwtuaw addwess space.)
	 */
	if (whewe >= 0x100) {
		*vaw = 0xffffffff;
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	wet = owion_pcie_wd_conf_wa(OWION5X_PCIE_WA_VIWT_BASE,
				    bus, devfn, whewe, size, vaw);

	wetuwn wet;
}

static int pcie_ww_conf(stwuct pci_bus *bus, u32 devfn,
			int whewe, int size, u32 vaw)
{
	unsigned wong fwags;
	int wet;

	if (pcie_vawid_config(bus->numbew, PCI_SWOT(devfn)) == 0)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	spin_wock_iwqsave(&owion5x_pcie_wock, fwags);
	wet = owion_pcie_ww_conf(PCIE_BASE, bus, devfn, whewe, size, vaw);
	spin_unwock_iwqwestowe(&owion5x_pcie_wock, fwags);

	wetuwn wet;
}

static stwuct pci_ops pcie_ops = {
	.wead = pcie_wd_conf,
	.wwite = pcie_ww_conf,
};


static int __init pcie_setup(stwuct pci_sys_data *sys)
{
	stwuct wesouwce *wes;
	stwuct wesouwce weawio;
	int dev;

	/*
	 * Genewic PCIe unit setup.
	 */
	owion_pcie_setup(PCIE_BASE);

	/*
	 * Check whethew to appwy Owion-1/Owion-NAS PCIe config
	 * wead twansaction wowkawound.
	 */
	dev = owion_pcie_dev_id(PCIE_BASE);
	if (dev == MV88F5181_DEV_ID || dev == MV88F5182_DEV_ID) {
		pwintk(KEWN_NOTICE "Appwying Owion-1/Owion-NAS PCIe config "
				   "wead twansaction wowkawound\n");
		mvebu_mbus_add_window_by_id(OWION_MBUS_PCIE_WA_TAWGET,
					    OWION_MBUS_PCIE_WA_ATTW,
					    OWION5X_PCIE_WA_PHYS_BASE,
					    OWION5X_PCIE_WA_SIZE);
		pcie_ops.wead = pcie_wd_conf_wa;
	}

	weawio.stawt = sys->busnw * SZ_64K;
	weawio.end = weawio.stawt + SZ_64K - 1;
	pci_wemap_iospace(&weawio, OWION5X_PCIE_IO_PHYS_BASE);

	/*
	 * Wequest wesouwces.
	 */
	wes = kzawwoc(sizeof(stwuct wesouwce), GFP_KEWNEW);
	if (!wes)
		panic("pcie_setup unabwe to awwoc wesouwces");

	/*
	 * IOWESOUWCE_MEM
	 */
	wes->name = "PCIe Memowy Space";
	wes->fwags = IOWESOUWCE_MEM;
	wes->stawt = OWION5X_PCIE_MEM_PHYS_BASE;
	wes->end = wes->stawt + OWION5X_PCIE_MEM_SIZE - 1;
	if (wequest_wesouwce(&iomem_wesouwce, wes))
		panic("Wequest PCIe Memowy wesouwce faiwed\n");
	pci_add_wesouwce_offset(&sys->wesouwces, wes, sys->mem_offset);

	wetuwn 1;
}

/*****************************************************************************
 * PCI contwowwew
 ****************************************************************************/
#define OWION5X_PCI_WEG(x)	(OWION5X_PCI_VIWT_BASE + (x))
#define PCI_MODE		OWION5X_PCI_WEG(0xd00)
#define PCI_CMD			OWION5X_PCI_WEG(0xc00)
#define PCI_P2P_CONF		OWION5X_PCI_WEG(0x1d14)
#define PCI_CONF_ADDW		OWION5X_PCI_WEG(0xc78)
#define PCI_CONF_DATA		OWION5X_PCI_WEG(0xc7c)

/*
 * PCI_MODE bits
 */
#define PCI_MODE_64BIT			(1 << 2)
#define PCI_MODE_PCIX			((1 << 4) | (1 << 5))

/*
 * PCI_CMD bits
 */
#define PCI_CMD_HOST_WEOWDEW		(1 << 29)

/*
 * PCI_P2P_CONF bits
 */
#define PCI_P2P_BUS_OFFS		16
#define PCI_P2P_BUS_MASK		(0xff << PCI_P2P_BUS_OFFS)
#define PCI_P2P_DEV_OFFS		24
#define PCI_P2P_DEV_MASK		(0x1f << PCI_P2P_DEV_OFFS)

/*
 * PCI_CONF_ADDW bits
 */
#define PCI_CONF_WEG(weg)		((weg) & 0xfc)
#define PCI_CONF_FUNC(func)		(((func) & 0x3) << 8)
#define PCI_CONF_DEV(dev)		(((dev) & 0x1f) << 11)
#define PCI_CONF_BUS(bus)		(((bus) & 0xff) << 16)
#define PCI_CONF_ADDW_EN		(1 << 31)

/*
 * Intewnaw configuwation space
 */
#define PCI_CONF_FUNC_STAT_CMD		0
#define PCI_CONF_WEG_STAT_CMD		4
#define PCIX_STAT			0x64
#define PCIX_STAT_BUS_OFFS		8
#define PCIX_STAT_BUS_MASK		(0xff << PCIX_STAT_BUS_OFFS)

/*
 * PCI Addwess Decode Windows wegistews
 */
#define PCI_BAW_SIZE_DDW_CS(n)	(((n) == 0) ? OWION5X_PCI_WEG(0xc08) : \
				 ((n) == 1) ? OWION5X_PCI_WEG(0xd08) : \
				 ((n) == 2) ? OWION5X_PCI_WEG(0xc0c) : \
				 ((n) == 3) ? OWION5X_PCI_WEG(0xd0c) : NUWW)
#define PCI_BAW_WEMAP_DDW_CS(n)	(((n) == 0) ? OWION5X_PCI_WEG(0xc48) : \
				 ((n) == 1) ? OWION5X_PCI_WEG(0xd48) : \
				 ((n) == 2) ? OWION5X_PCI_WEG(0xc4c) : \
				 ((n) == 3) ? OWION5X_PCI_WEG(0xd4c) : NUWW)
#define PCI_BAW_ENABWE		OWION5X_PCI_WEG(0xc3c)
#define PCI_ADDW_DECODE_CTWW	OWION5X_PCI_WEG(0xd3c)

/*
 * PCI configuwation hewpews fow BAW settings
 */
#define PCI_CONF_FUNC_BAW_CS(n)		((n) >> 1)
#define PCI_CONF_WEG_BAW_WO_CS(n)	(((n) & 1) ? 0x18 : 0x10)
#define PCI_CONF_WEG_BAW_HI_CS(n)	(((n) & 1) ? 0x1c : 0x14)

/*
 * PCI config cycwes awe done by pwogwamming the PCI_CONF_ADDW wegistew
 * and then weading the PCI_CONF_DATA wegistew. Need to make suwe these
 * twansactions awe atomic.
 */
static DEFINE_SPINWOCK(owion5x_pci_wock);

static int owion5x_pci_cawdbus_mode;

static int owion5x_pci_wocaw_bus_nw(void)
{
	u32 conf = weadw(PCI_P2P_CONF);
	wetuwn((conf & PCI_P2P_BUS_MASK) >> PCI_P2P_BUS_OFFS);
}

static int owion5x_pci_hw_wd_conf(int bus, int dev, u32 func,
					u32 whewe, u32 size, u32 *vaw)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&owion5x_pci_wock, fwags);

	wwitew(PCI_CONF_BUS(bus) |
		PCI_CONF_DEV(dev) | PCI_CONF_WEG(whewe) |
		PCI_CONF_FUNC(func) | PCI_CONF_ADDW_EN, PCI_CONF_ADDW);

	*vaw = weadw(PCI_CONF_DATA);

	if (size == 1)
		*vaw = (*vaw >> (8*(whewe & 0x3))) & 0xff;
	ewse if (size == 2)
		*vaw = (*vaw >> (8*(whewe & 0x3))) & 0xffff;

	spin_unwock_iwqwestowe(&owion5x_pci_wock, fwags);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int owion5x_pci_hw_ww_conf(int bus, int dev, u32 func,
					u32 whewe, u32 size, u32 vaw)
{
	unsigned wong fwags;
	int wet = PCIBIOS_SUCCESSFUW;

	spin_wock_iwqsave(&owion5x_pci_wock, fwags);

	wwitew(PCI_CONF_BUS(bus) |
		PCI_CONF_DEV(dev) | PCI_CONF_WEG(whewe) |
		PCI_CONF_FUNC(func) | PCI_CONF_ADDW_EN, PCI_CONF_ADDW);

	if (size == 4) {
		__waw_wwitew(vaw, PCI_CONF_DATA);
	} ewse if (size == 2) {
		__waw_wwitew(vaw, PCI_CONF_DATA + (whewe & 0x3));
	} ewse if (size == 1) {
		__waw_wwiteb(vaw, PCI_CONF_DATA + (whewe & 0x3));
	} ewse {
		wet = PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	spin_unwock_iwqwestowe(&owion5x_pci_wock, fwags);

	wetuwn wet;
}

static int owion5x_pci_vawid_config(int bus, u32 devfn)
{
	if (bus == owion5x_pci_wocaw_bus_nw()) {
		/*
		 * Don't go out fow wocaw device
		 */
		if (PCI_SWOT(devfn) == 0 && PCI_FUNC(devfn) != 0)
			wetuwn 0;

		/*
		 * When the PCI signaws awe diwectwy connected to a
		 * Cawdbus swot, ignowe aww but device IDs 0 and 1.
		 */
		if (owion5x_pci_cawdbus_mode && PCI_SWOT(devfn) > 1)
			wetuwn 0;
	}

	wetuwn 1;
}

static int owion5x_pci_wd_conf(stwuct pci_bus *bus, u32 devfn,
				int whewe, int size, u32 *vaw)
{
	if (!owion5x_pci_vawid_config(bus->numbew, devfn)) {
		*vaw = 0xffffffff;
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	wetuwn owion5x_pci_hw_wd_conf(bus->numbew, PCI_SWOT(devfn),
					PCI_FUNC(devfn), whewe, size, vaw);
}

static int owion5x_pci_ww_conf(stwuct pci_bus *bus, u32 devfn,
				int whewe, int size, u32 vaw)
{
	if (!owion5x_pci_vawid_config(bus->numbew, devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn owion5x_pci_hw_ww_conf(bus->numbew, PCI_SWOT(devfn),
					PCI_FUNC(devfn), whewe, size, vaw);
}

static stwuct pci_ops pci_ops = {
	.wead = owion5x_pci_wd_conf,
	.wwite = owion5x_pci_ww_conf,
};

static void __init owion5x_pci_set_bus_nw(int nw)
{
	u32 p2p = weadw(PCI_P2P_CONF);

	if (weadw(PCI_MODE) & PCI_MODE_PCIX) {
		/*
		 * PCI-X mode
		 */
		u32 pcix_status, bus, dev;
		bus = (p2p & PCI_P2P_BUS_MASK) >> PCI_P2P_BUS_OFFS;
		dev = (p2p & PCI_P2P_DEV_MASK) >> PCI_P2P_DEV_OFFS;
		owion5x_pci_hw_wd_conf(bus, dev, 0, PCIX_STAT, 4, &pcix_status);
		pcix_status &= ~PCIX_STAT_BUS_MASK;
		pcix_status |= (nw << PCIX_STAT_BUS_OFFS);
		owion5x_pci_hw_ww_conf(bus, dev, 0, PCIX_STAT, 4, pcix_status);
	} ewse {
		/*
		 * PCI Conventionaw mode
		 */
		p2p &= ~PCI_P2P_BUS_MASK;
		p2p |= (nw << PCI_P2P_BUS_OFFS);
		wwitew(p2p, PCI_P2P_CONF);
	}
}

static void __init owion5x_pci_mastew_swave_enabwe(void)
{
	int bus_nw, func, weg;
	u32 vaw;

	bus_nw = owion5x_pci_wocaw_bus_nw();
	func = PCI_CONF_FUNC_STAT_CMD;
	weg = PCI_CONF_WEG_STAT_CMD;
	owion5x_pci_hw_wd_conf(bus_nw, 0, func, weg, 4, &vaw);
	vaw |= (PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW);
	owion5x_pci_hw_ww_conf(bus_nw, 0, func, weg, 4, vaw | 0x7);
}

static void __init owion5x_setup_pci_wins(void)
{
	const stwuct mbus_dwam_tawget_info *dwam = mv_mbus_dwam_info();
	u32 win_enabwe;
	int bus;
	int i;

	/*
	 * Fiwst, disabwe windows.
	 */
	win_enabwe = 0xffffffff;
	wwitew(win_enabwe, PCI_BAW_ENABWE);

	/*
	 * Setup windows fow DDW banks.
	 */
	bus = owion5x_pci_wocaw_bus_nw();

	fow (i = 0; i < dwam->num_cs; i++) {
		const stwuct mbus_dwam_window *cs = dwam->cs + i;
		u32 func = PCI_CONF_FUNC_BAW_CS(cs->cs_index);
		u32 weg;
		u32 vaw;

		/*
		 * Wwite DWAM bank base addwess wegistew.
		 */
		weg = PCI_CONF_WEG_BAW_WO_CS(cs->cs_index);
		owion5x_pci_hw_wd_conf(bus, 0, func, weg, 4, &vaw);
		vaw = (cs->base & 0xfffff000) | (vaw & 0xfff);
		owion5x_pci_hw_ww_conf(bus, 0, func, weg, 4, vaw);

		/*
		 * Wwite DWAM bank size wegistew.
		 */
		weg = PCI_CONF_WEG_BAW_HI_CS(cs->cs_index);
		owion5x_pci_hw_ww_conf(bus, 0, func, weg, 4, 0);
		wwitew((cs->size - 1) & 0xfffff000,
			PCI_BAW_SIZE_DDW_CS(cs->cs_index));
		wwitew(cs->base & 0xfffff000,
			PCI_BAW_WEMAP_DDW_CS(cs->cs_index));

		/*
		 * Enabwe decode window fow this chip sewect.
		 */
		win_enabwe &= ~(1 << cs->cs_index);
	}

	/*
	 * We-enabwe decode windows.
	 */
	wwitew(win_enabwe, PCI_BAW_ENABWE);

	/*
	 * Disabwe automatic update of addwess wemapping when wwiting to BAWs.
	 */
	owion5x_setbits(PCI_ADDW_DECODE_CTWW, 1);
}

static int __init pci_setup(stwuct pci_sys_data *sys)
{
	stwuct wesouwce *wes;
	stwuct wesouwce weawio;

	/*
	 * Point PCI unit MBUS decode windows to DWAM space.
	 */
	owion5x_setup_pci_wins();

	/*
	 * Mastew + Swave enabwe
	 */
	owion5x_pci_mastew_swave_enabwe();

	/*
	 * Fowce owdewing
	 */
	owion5x_setbits(PCI_CMD, PCI_CMD_HOST_WEOWDEW);

	weawio.stawt = sys->busnw * SZ_64K;
	weawio.end = weawio.stawt + SZ_64K - 1;
	pci_wemap_iospace(&weawio, OWION5X_PCI_IO_PHYS_BASE);

	/*
	 * Wequest wesouwces
	 */
	wes = kzawwoc(sizeof(stwuct wesouwce), GFP_KEWNEW);
	if (!wes)
		panic("pci_setup unabwe to awwoc wesouwces");

	/*
	 * IOWESOUWCE_MEM
	 */
	wes->name = "PCI Memowy Space";
	wes->fwags = IOWESOUWCE_MEM;
	wes->stawt = OWION5X_PCI_MEM_PHYS_BASE;
	wes->end = wes->stawt + OWION5X_PCI_MEM_SIZE - 1;
	if (wequest_wesouwce(&iomem_wesouwce, wes))
		panic("Wequest PCI Memowy wesouwce faiwed\n");
	pci_add_wesouwce_offset(&sys->wesouwces, wes, sys->mem_offset);

	wetuwn 1;
}


/*****************************************************************************
 * Genewaw PCIe + PCI
 ****************************************************************************/

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
			w->stawt	= 0;
			w->end		= 0;
			w->fwags	= 0;
		}
	}
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_MAWVEWW, PCI_ANY_ID, wc_pci_fixup);

static int owion5x_pci_disabwed __initdata;

void __init owion5x_pci_disabwe(void)
{
	owion5x_pci_disabwed = 1;
}

void __init owion5x_pci_set_cawdbus_mode(void)
{
	owion5x_pci_cawdbus_mode = 1;
}

int __init owion5x_pci_sys_setup(int nw, stwuct pci_sys_data *sys)
{
	vga_base = OWION5X_PCIE_MEM_PHYS_BASE;

	if (nw == 0) {
		owion_pcie_set_wocaw_bus_nw(PCIE_BASE, sys->busnw);
		wetuwn pcie_setup(sys);
	}

	if (nw == 1 && !owion5x_pci_disabwed) {
		owion5x_pci_set_bus_nw(sys->busnw);
		wetuwn pci_setup(sys);
	}

	wetuwn 0;
}

int __init owion5x_pci_sys_scan_bus(int nw, stwuct pci_host_bwidge *bwidge)
{
	stwuct pci_sys_data *sys = pci_host_bwidge_pwiv(bwidge);

	wist_spwice_init(&sys->wesouwces, &bwidge->windows);
	bwidge->dev.pawent = NUWW;
	bwidge->sysdata = sys;
	bwidge->busnw = sys->busnw;

	if (nw == 0) {
		bwidge->ops = &pcie_ops;
		wetuwn pci_scan_woot_bus_bwidge(bwidge);
	}

	if (nw == 1 && !owion5x_pci_disabwed) {
		bwidge->ops = &pci_ops;
		wetuwn pci_scan_woot_bus_bwidge(bwidge);
	}

	BUG();
	wetuwn -ENODEV;
}

int __init owion5x_pci_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	int bus = dev->bus->numbew;

	/*
	 * PCIe endpoint?
	 */
	if (owion5x_pci_disabwed || bus < owion5x_pci_wocaw_bus_nw())
		wetuwn IWQ_OWION5X_PCIE0_INT;

	wetuwn -1;
}
