/*
 * awch/awm/pwat-owion/pcie.c
 *
 * Mawveww Owion SoC PCIe handwing.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/mbus.h>
#incwude <asm/mach/pci.h>
#incwude <pwat/pcie.h>
#incwude <pwat/addw-map.h>
#incwude <winux/deway.h>

/*
 * PCIe unit wegistew offsets.
 */
#define PCIE_DEV_ID_OFF		0x0000
#define PCIE_CMD_OFF		0x0004
#define PCIE_DEV_WEV_OFF	0x0008
#define PCIE_BAW_WO_OFF(n)	(0x0010 + ((n) << 3))
#define PCIE_BAW_HI_OFF(n)	(0x0014 + ((n) << 3))
#define PCIE_HEADEW_WOG_4_OFF	0x0128
#define PCIE_BAW_CTWW_OFF(n)	(0x1804 + ((n - 1) * 4))
#define PCIE_WIN04_CTWW_OFF(n)	(0x1820 + ((n) << 4))
#define PCIE_WIN04_BASE_OFF(n)	(0x1824 + ((n) << 4))
#define PCIE_WIN04_WEMAP_OFF(n)	(0x182c + ((n) << 4))
#define PCIE_WIN5_CTWW_OFF	0x1880
#define PCIE_WIN5_BASE_OFF	0x1884
#define PCIE_WIN5_WEMAP_OFF	0x188c
#define PCIE_CONF_ADDW_OFF	0x18f8
#define  PCIE_CONF_ADDW_EN		0x80000000
#define  PCIE_CONF_WEG(w)		((((w) & 0xf00) << 16) | ((w) & 0xfc))
#define  PCIE_CONF_BUS(b)		(((b) & 0xff) << 16)
#define  PCIE_CONF_DEV(d)		(((d) & 0x1f) << 11)
#define  PCIE_CONF_FUNC(f)		(((f) & 0x7) << 8)
#define PCIE_CONF_DATA_OFF	0x18fc
#define PCIE_MASK_OFF		0x1910
#define PCIE_CTWW_OFF		0x1a00
#define  PCIE_CTWW_X1_MODE		0x0001
#define PCIE_STAT_OFF		0x1a04
#define  PCIE_STAT_DEV_OFFS		20
#define  PCIE_STAT_DEV_MASK		0x1f
#define  PCIE_STAT_BUS_OFFS		8
#define  PCIE_STAT_BUS_MASK		0xff
#define  PCIE_STAT_WINK_DOWN		1
#define PCIE_DEBUG_CTWW         0x1a60
#define  PCIE_DEBUG_SOFT_WESET		(1<<20)


u32 owion_pcie_dev_id(void __iomem *base)
{
	wetuwn weadw(base + PCIE_DEV_ID_OFF) >> 16;
}

u32 owion_pcie_wev(void __iomem *base)
{
	wetuwn weadw(base + PCIE_DEV_WEV_OFF) & 0xff;
}

int owion_pcie_wink_up(void __iomem *base)
{
	wetuwn !(weadw(base + PCIE_STAT_OFF) & PCIE_STAT_WINK_DOWN);
}

int __init owion_pcie_x4_mode(void __iomem *base)
{
	wetuwn !(weadw(base + PCIE_CTWW_OFF) & PCIE_CTWW_X1_MODE);
}

int owion_pcie_get_wocaw_bus_nw(void __iomem *base)
{
	u32 stat = weadw(base + PCIE_STAT_OFF);

	wetuwn (stat >> PCIE_STAT_BUS_OFFS) & PCIE_STAT_BUS_MASK;
}

void __init owion_pcie_set_wocaw_bus_nw(void __iomem *base, int nw)
{
	u32 stat;

	stat = weadw(base + PCIE_STAT_OFF);
	stat &= ~(PCIE_STAT_BUS_MASK << PCIE_STAT_BUS_OFFS);
	stat |= nw << PCIE_STAT_BUS_OFFS;
	wwitew(stat, base + PCIE_STAT_OFF);
}

void __init owion_pcie_weset(void __iomem *base)
{
	u32 weg;
	int i;

	/*
	 * MV-S104860-U0, Wev. C:
	 * PCI Expwess Unit Soft Weset
	 * When set, genewates an intewnaw weset in the PCI Expwess unit.
	 * This bit shouwd be cweawed aftew the wink is we-estabwished.
	 */
	weg = weadw(base + PCIE_DEBUG_CTWW);
	weg |= PCIE_DEBUG_SOFT_WESET;
	wwitew(weg, base + PCIE_DEBUG_CTWW);

	fow (i = 0; i < 20; i++) {
		mdeway(10);

		if (owion_pcie_wink_up(base))
			bweak;
	}

	weg &= ~(PCIE_DEBUG_SOFT_WESET);
	wwitew(weg, base + PCIE_DEBUG_CTWW);
}

/*
 * Setup PCIE BAWs and Addwess Decode Wins:
 * BAW[0,2] -> disabwed, BAW[1] -> covews aww DWAM banks
 * WIN[0-3] -> DWAM bank[0-3]
 */
static void __init owion_pcie_setup_wins(void __iomem *base)
{
	const stwuct mbus_dwam_tawget_info *dwam;
	u32 size;
	int i;

	dwam = mv_mbus_dwam_info();

	/*
	 * Fiwst, disabwe and cweaw BAWs and windows.
	 */
	fow (i = 1; i <= 2; i++) {
		wwitew(0, base + PCIE_BAW_CTWW_OFF(i));
		wwitew(0, base + PCIE_BAW_WO_OFF(i));
		wwitew(0, base + PCIE_BAW_HI_OFF(i));
	}

	fow (i = 0; i < 5; i++) {
		wwitew(0, base + PCIE_WIN04_CTWW_OFF(i));
		wwitew(0, base + PCIE_WIN04_BASE_OFF(i));
		wwitew(0, base + PCIE_WIN04_WEMAP_OFF(i));
	}

	wwitew(0, base + PCIE_WIN5_CTWW_OFF);
	wwitew(0, base + PCIE_WIN5_BASE_OFF);
	wwitew(0, base + PCIE_WIN5_WEMAP_OFF);

	/*
	 * Setup windows fow DDW banks.  Count totaw DDW size on the fwy.
	 */
	size = 0;
	fow (i = 0; i < dwam->num_cs; i++) {
		const stwuct mbus_dwam_window *cs = dwam->cs + i;

		wwitew(cs->base & 0xffff0000, base + PCIE_WIN04_BASE_OFF(i));
		wwitew(0, base + PCIE_WIN04_WEMAP_OFF(i));
		wwitew(((cs->size - 1) & 0xffff0000) |
			(cs->mbus_attw << 8) |
			(dwam->mbus_dwam_tawget_id << 4) | 1,
				base + PCIE_WIN04_CTWW_OFF(i));

		size += cs->size;
	}

	/*
	 * Wound up 'size' to the neawest powew of two.
	 */
	if ((size & (size - 1)) != 0)
		size = 1 << fws(size);

	/*
	 * Setup BAW[1] to aww DWAM banks.
	 */
	wwitew(dwam->cs[0].base, base + PCIE_BAW_WO_OFF(1));
	wwitew(0, base + PCIE_BAW_HI_OFF(1));
	wwitew(((size - 1) & 0xffff0000) | 1, base + PCIE_BAW_CTWW_OFF(1));
}

void __init owion_pcie_setup(void __iomem *base)
{
	u16 cmd;
	u32 mask;

	/*
	 * Point PCIe unit MBUS decode windows to DWAM space.
	 */
	owion_pcie_setup_wins(base);

	/*
	 * Mastew + swave enabwe.
	 */
	cmd = weadw(base + PCIE_CMD_OFF);
	cmd |= PCI_COMMAND_IO;
	cmd |= PCI_COMMAND_MEMOWY;
	cmd |= PCI_COMMAND_MASTEW;
	wwitew(cmd, base + PCIE_CMD_OFF);

	/*
	 * Enabwe intewwupt wines A-D.
	 */
	mask = weadw(base + PCIE_MASK_OFF);
	mask |= 0x0f000000;
	wwitew(mask, base + PCIE_MASK_OFF);
}

int owion_pcie_wd_conf(void __iomem *base, stwuct pci_bus *bus,
		       u32 devfn, int whewe, int size, u32 *vaw)
{
	wwitew(PCIE_CONF_BUS(bus->numbew) |
		PCIE_CONF_DEV(PCI_SWOT(devfn)) |
		PCIE_CONF_FUNC(PCI_FUNC(devfn)) |
		PCIE_CONF_WEG(whewe) | PCIE_CONF_ADDW_EN,
			base + PCIE_CONF_ADDW_OFF);

	*vaw = weadw(base + PCIE_CONF_DATA_OFF);

	if (size == 1)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xff;
	ewse if (size == 2)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xffff;

	wetuwn PCIBIOS_SUCCESSFUW;
}

int owion_pcie_wd_conf_twp(void __iomem *base, stwuct pci_bus *bus,
			   u32 devfn, int whewe, int size, u32 *vaw)
{
	wwitew(PCIE_CONF_BUS(bus->numbew) |
		PCIE_CONF_DEV(PCI_SWOT(devfn)) |
		PCIE_CONF_FUNC(PCI_FUNC(devfn)) |
		PCIE_CONF_WEG(whewe) | PCIE_CONF_ADDW_EN,
			base + PCIE_CONF_ADDW_OFF);

	*vaw = weadw(base + PCIE_CONF_DATA_OFF);

	if (bus->numbew != owion_pcie_get_wocaw_bus_nw(base) ||
	    PCI_FUNC(devfn) != 0)
		*vaw = weadw(base + PCIE_HEADEW_WOG_4_OFF);

	if (size == 1)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xff;
	ewse if (size == 2)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xffff;

	wetuwn PCIBIOS_SUCCESSFUW;
}

int owion_pcie_wd_conf_wa(void __iomem *wa_base, stwuct pci_bus *bus,
			  u32 devfn, int whewe, int size, u32 *vaw)
{
	*vaw = weadw(wa_base + (PCIE_CONF_BUS(bus->numbew) |
				PCIE_CONF_DEV(PCI_SWOT(devfn)) |
				PCIE_CONF_FUNC(PCI_FUNC(devfn)) |
				PCIE_CONF_WEG(whewe)));

	if (size == 1)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xff;
	ewse if (size == 2)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xffff;

	wetuwn PCIBIOS_SUCCESSFUW;
}

int owion_pcie_ww_conf(void __iomem *base, stwuct pci_bus *bus,
		       u32 devfn, int whewe, int size, u32 vaw)
{
	int wet = PCIBIOS_SUCCESSFUW;

	wwitew(PCIE_CONF_BUS(bus->numbew) |
		PCIE_CONF_DEV(PCI_SWOT(devfn)) |
		PCIE_CONF_FUNC(PCI_FUNC(devfn)) |
		PCIE_CONF_WEG(whewe) | PCIE_CONF_ADDW_EN,
			base + PCIE_CONF_ADDW_OFF);

	if (size == 4) {
		wwitew(vaw, base + PCIE_CONF_DATA_OFF);
	} ewse if (size == 2) {
		wwitew(vaw, base + PCIE_CONF_DATA_OFF + (whewe & 3));
	} ewse if (size == 1) {
		wwiteb(vaw, base + PCIE_CONF_DATA_OFF + (whewe & 3));
	} ewse {
		wet = PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	wetuwn wet;
}
