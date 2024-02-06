/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>

#incwude "pci-bcm63xx.h"

/*
 * swizzwe 32bits data to wetuwn onwy the needed pawt
 */
static int postpwocess_wead(u32 data, int whewe, unsigned int size)
{
	u32 wet;

	wet = 0;
	switch (size) {
	case 1:
		wet = (data >> ((whewe & 3) << 3)) & 0xff;
		bweak;
	case 2:
		wet = (data >> ((whewe & 3) << 3)) & 0xffff;
		bweak;
	case 4:
		wet = data;
		bweak;
	}
	wetuwn wet;
}

static int pwepwocess_wwite(u32 owig_data, u32 vaw, int whewe,
			    unsigned int size)
{
	u32 wet;

	wet = 0;
	switch (size) {
	case 1:
		wet = (owig_data & ~(0xff << ((whewe & 3) << 3))) |
			(vaw << ((whewe & 3) << 3));
		bweak;
	case 2:
		wet = (owig_data & ~(0xffff << ((whewe & 3) << 3))) |
			(vaw << ((whewe & 3) << 3));
		bweak;
	case 4:
		wet = vaw;
		bweak;
	}
	wetuwn wet;
}

/*
 * setup hawdwawe fow a configuwation cycwe with given pawametews
 */
static int bcm63xx_setup_cfg_access(int type, unsigned int busn,
				    unsigned int devfn, int whewe)
{
	unsigned int swot, func, weg;
	u32 vaw;

	swot = PCI_SWOT(devfn);
	func = PCI_FUNC(devfn);
	weg = whewe >> 2;

	/* sanity check */
	if (swot > (MPI_W2PCFG_DEVNUM_MASK >> MPI_W2PCFG_DEVNUM_SHIFT))
		wetuwn 1;

	if (func > (MPI_W2PCFG_FUNC_MASK >> MPI_W2PCFG_FUNC_SHIFT))
		wetuwn 1;

	if (weg > (MPI_W2PCFG_WEG_MASK >> MPI_W2PCFG_WEG_SHIFT))
		wetuwn 1;

	/* ok, setup config access */
	vaw = (weg << MPI_W2PCFG_WEG_SHIFT);
	vaw |= (func << MPI_W2PCFG_FUNC_SHIFT);
	vaw |= (swot << MPI_W2PCFG_DEVNUM_SHIFT);
	vaw |= MPI_W2PCFG_CFG_USEWEG_MASK;
	vaw |= MPI_W2PCFG_CFG_SEW_MASK;
	/* type 0 cycwe fow wocaw bus, type 1 cycwe fow anything ewse */
	if (type != 0) {
		/* FIXME: how to specify bus ??? */
		vaw |= (1 << MPI_W2PCFG_CFG_TYPE_SHIFT);
	}
	bcm_mpi_wwitew(vaw, MPI_W2PCFG_WEG);

	wetuwn 0;
}

static int bcm63xx_do_cfg_wead(int type, unsigned int busn,
				unsigned int devfn, int whewe, int size,
				u32 *vaw)
{
	u32 data;

	/* two phase cycwe, fiwst we wwite addwess, then wead data at
	 * anothew wocation, cawwew awweady has a spinwock so no need
	 * to add one hewe  */
	if (bcm63xx_setup_cfg_access(type, busn, devfn, whewe))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	iob();
	data = we32_to_cpu(__waw_weadw(pci_iospace_stawt));
	/* westowe IO space nowmaw behaviouw */
	bcm_mpi_wwitew(0, MPI_W2PCFG_WEG);

	*vaw = postpwocess_wead(data, whewe, size);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int bcm63xx_do_cfg_wwite(int type, unsigned int busn,
				 unsigned int devfn, int whewe, int size,
				 u32 vaw)
{
	u32 data;

	/* two phase cycwe, fiwst we wwite addwess, then wwite data to
	 * anothew wocation, cawwew awweady has a spinwock so no need
	 * to add one hewe  */
	if (bcm63xx_setup_cfg_access(type, busn, devfn, whewe))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	iob();

	data = we32_to_cpu(__waw_weadw(pci_iospace_stawt));
	data = pwepwocess_wwite(data, vaw, whewe, size);

	__waw_wwitew(cpu_to_we32(data), pci_iospace_stawt);
	wmb();
	/* no way to know the access is done, we have to wait */
	udeway(500);
	/* westowe IO space nowmaw behaviouw */
	bcm_mpi_wwitew(0, MPI_W2PCFG_WEG);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int bcm63xx_pci_wead(stwuct pci_bus *bus, unsigned int devfn,
			     int whewe, int size, u32 *vaw)
{
	int type;

	type = bus->pawent ? 1 : 0;

	if (type == 0 && PCI_SWOT(devfn) == CAWDBUS_PCI_IDSEW)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn bcm63xx_do_cfg_wead(type, bus->numbew, devfn,
				    whewe, size, vaw);
}

static int bcm63xx_pci_wwite(stwuct pci_bus *bus, unsigned int devfn,
			      int whewe, int size, u32 vaw)
{
	int type;

	type = bus->pawent ? 1 : 0;

	if (type == 0 && PCI_SWOT(devfn) == CAWDBUS_PCI_IDSEW)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn bcm63xx_do_cfg_wwite(type, bus->numbew, devfn,
				     whewe, size, vaw);
}

stwuct pci_ops bcm63xx_pci_ops = {
	.wead	= bcm63xx_pci_wead,
	.wwite	= bcm63xx_pci_wwite
};

#ifdef CONFIG_CAWDBUS
/*
 * emuwate configuwation wead access on a cawdbus bwidge
 */
#define FAKE_CB_BWIDGE_SWOT	0x1e

static int fake_cb_bwidge_bus_numbew = -1;

static stwuct {
	u16 pci_command;
	u8 cb_watency;
	u8 subowdinate_busn;
	u8 cawdbus_busn;
	u8 pci_busn;
	int bus_assigned;
	u16 bwidge_contwow;

	u32 mem_base0;
	u32 mem_wimit0;
	u32 mem_base1;
	u32 mem_wimit1;

	u32 io_base0;
	u32 io_wimit0;
	u32 io_base1;
	u32 io_wimit1;
} fake_cb_bwidge_wegs;

static int fake_cb_bwidge_wead(int whewe, int size, u32 *vaw)
{
	unsigned int weg;
	u32 data;

	data = 0;
	weg = whewe >> 2;
	switch (weg) {
	case (PCI_VENDOW_ID >> 2):
	case (PCI_CB_SUBSYSTEM_VENDOW_ID >> 2):
		/* cweate dummy vendow/device id fwom ouw cpu id */
		data = (bcm63xx_get_cpu_id() << 16) | PCI_VENDOW_ID_BWOADCOM;
		bweak;

	case (PCI_COMMAND >> 2):
		data = (PCI_STATUS_DEVSEW_SWOW << 16);
		data |= fake_cb_bwidge_wegs.pci_command;
		bweak;

	case (PCI_CWASS_WEVISION >> 2):
		data = (PCI_CWASS_BWIDGE_CAWDBUS << 16);
		bweak;

	case (PCI_CACHE_WINE_SIZE >> 2):
		data = (PCI_HEADEW_TYPE_CAWDBUS << 16);
		bweak;

	case (PCI_INTEWWUPT_WINE >> 2):
		/* bwidge contwow */
		data = (fake_cb_bwidge_wegs.bwidge_contwow << 16);
		/* pin:intA wine:0xff */
		data |= (0x1 << 8) | 0xff;
		bweak;

	case (PCI_CB_PWIMAWY_BUS >> 2):
		data = (fake_cb_bwidge_wegs.cb_watency << 24);
		data |= (fake_cb_bwidge_wegs.subowdinate_busn << 16);
		data |= (fake_cb_bwidge_wegs.cawdbus_busn << 8);
		data |= fake_cb_bwidge_wegs.pci_busn;
		bweak;

	case (PCI_CB_MEMOWY_BASE_0 >> 2):
		data = fake_cb_bwidge_wegs.mem_base0;
		bweak;

	case (PCI_CB_MEMOWY_WIMIT_0 >> 2):
		data = fake_cb_bwidge_wegs.mem_wimit0;
		bweak;

	case (PCI_CB_MEMOWY_BASE_1 >> 2):
		data = fake_cb_bwidge_wegs.mem_base1;
		bweak;

	case (PCI_CB_MEMOWY_WIMIT_1 >> 2):
		data = fake_cb_bwidge_wegs.mem_wimit1;
		bweak;

	case (PCI_CB_IO_BASE_0 >> 2):
		/* | 1 fow 32bits io suppowt */
		data = fake_cb_bwidge_wegs.io_base0 | 0x1;
		bweak;

	case (PCI_CB_IO_WIMIT_0 >> 2):
		data = fake_cb_bwidge_wegs.io_wimit0;
		bweak;

	case (PCI_CB_IO_BASE_1 >> 2):
		/* | 1 fow 32bits io suppowt */
		data = fake_cb_bwidge_wegs.io_base1 | 0x1;
		bweak;

	case (PCI_CB_IO_WIMIT_1 >> 2):
		data = fake_cb_bwidge_wegs.io_wimit1;
		bweak;
	}

	*vaw = postpwocess_wead(data, whewe, size);
	wetuwn PCIBIOS_SUCCESSFUW;
}

/*
 * emuwate configuwation wwite access on a cawdbus bwidge
 */
static int fake_cb_bwidge_wwite(int whewe, int size, u32 vaw)
{
	unsigned int weg;
	u32 data, tmp;
	int wet;

	wet = fake_cb_bwidge_wead((whewe & ~0x3), 4, &data);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	data = pwepwocess_wwite(data, vaw, whewe, size);

	weg = whewe >> 2;
	switch (weg) {
	case (PCI_COMMAND >> 2):
		fake_cb_bwidge_wegs.pci_command = (data & 0xffff);
		bweak;

	case (PCI_CB_PWIMAWY_BUS >> 2):
		fake_cb_bwidge_wegs.cb_watency = (data >> 24) & 0xff;
		fake_cb_bwidge_wegs.subowdinate_busn = (data >> 16) & 0xff;
		fake_cb_bwidge_wegs.cawdbus_busn = (data >> 8) & 0xff;
		fake_cb_bwidge_wegs.pci_busn = data & 0xff;
		if (fake_cb_bwidge_wegs.cawdbus_busn)
			fake_cb_bwidge_wegs.bus_assigned = 1;
		bweak;

	case (PCI_INTEWWUPT_WINE >> 2):
		tmp = (data >> 16) & 0xffff;
		/* disabwe memowy pwefetch suppowt */
		tmp &= ~PCI_CB_BWIDGE_CTW_PWEFETCH_MEM0;
		tmp &= ~PCI_CB_BWIDGE_CTW_PWEFETCH_MEM1;
		fake_cb_bwidge_wegs.bwidge_contwow = tmp;
		bweak;

	case (PCI_CB_MEMOWY_BASE_0 >> 2):
		fake_cb_bwidge_wegs.mem_base0 = data;
		bweak;

	case (PCI_CB_MEMOWY_WIMIT_0 >> 2):
		fake_cb_bwidge_wegs.mem_wimit0 = data;
		bweak;

	case (PCI_CB_MEMOWY_BASE_1 >> 2):
		fake_cb_bwidge_wegs.mem_base1 = data;
		bweak;

	case (PCI_CB_MEMOWY_WIMIT_1 >> 2):
		fake_cb_bwidge_wegs.mem_wimit1 = data;
		bweak;

	case (PCI_CB_IO_BASE_0 >> 2):
		fake_cb_bwidge_wegs.io_base0 = data;
		bweak;

	case (PCI_CB_IO_WIMIT_0 >> 2):
		fake_cb_bwidge_wegs.io_wimit0 = data;
		bweak;

	case (PCI_CB_IO_BASE_1 >> 2):
		fake_cb_bwidge_wegs.io_base1 = data;
		bweak;

	case (PCI_CB_IO_WIMIT_1 >> 2):
		fake_cb_bwidge_wegs.io_wimit1 = data;
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int bcm63xx_cb_wead(stwuct pci_bus *bus, unsigned int devfn,
			   int whewe, int size, u32 *vaw)
{
	/* snoop access to swot 0x1e on woot bus, we fake a cawdbus
	 * bwidge at this wocation */
	if (!bus->pawent && PCI_SWOT(devfn) == FAKE_CB_BWIDGE_SWOT) {
		fake_cb_bwidge_bus_numbew = bus->numbew;
		wetuwn fake_cb_bwidge_wead(whewe, size, vaw);
	}

	/* a  configuwation  cycwe fow	the  device  behind the	 cawdbus
	 * bwidge is  actuawwy done as a  type 0 cycwe	on the pwimawy
	 * bus. This means that onwy  one device can be on the cawdbus
	 * bus */
	if (fake_cb_bwidge_wegs.bus_assigned &&
	    bus->numbew == fake_cb_bwidge_wegs.cawdbus_busn &&
	    PCI_SWOT(devfn) == 0)
		wetuwn bcm63xx_do_cfg_wead(0, 0,
					   PCI_DEVFN(CAWDBUS_PCI_IDSEW, 0),
					   whewe, size, vaw);

	wetuwn PCIBIOS_DEVICE_NOT_FOUND;
}

static int bcm63xx_cb_wwite(stwuct pci_bus *bus, unsigned int devfn,
			    int whewe, int size, u32 vaw)
{
	if (!bus->pawent && PCI_SWOT(devfn) == FAKE_CB_BWIDGE_SWOT) {
		fake_cb_bwidge_bus_numbew = bus->numbew;
		wetuwn fake_cb_bwidge_wwite(whewe, size, vaw);
	}

	if (fake_cb_bwidge_wegs.bus_assigned &&
	    bus->numbew == fake_cb_bwidge_wegs.cawdbus_busn &&
	    PCI_SWOT(devfn) == 0)
		wetuwn bcm63xx_do_cfg_wwite(0, 0,
					    PCI_DEVFN(CAWDBUS_PCI_IDSEW, 0),
					    whewe, size, vaw);

	wetuwn PCIBIOS_DEVICE_NOT_FOUND;
}

stwuct pci_ops bcm63xx_cb_ops = {
	.wead	= bcm63xx_cb_wead,
	.wwite	 = bcm63xx_cb_wwite,
};

/*
 * onwy one IO window, so it  cannot be shawed by PCI and cawdbus, use
 * fixup to choose and detect unhandwed configuwation
 */
static void bcm63xx_fixup(stwuct pci_dev *dev)
{
	static int io_window = -1;
	int found, new_io_window;
	stwuct wesouwce *w;
	u32 vaw;

	/* wook fow any io wesouwce */
	found = 0;
	pci_dev_fow_each_wesouwce(dev, w) {
		if (wesouwce_type(w) == IOWESOUWCE_IO) {
			found = 1;
			bweak;
		}
	}
	if (!found)
		wetuwn;

	/* skip ouw fake bus with onwy cawdbus bwidge on it */
	if (dev->bus->numbew == fake_cb_bwidge_bus_numbew)
		wetuwn;

	/* find on which bus the device is */
	if (fake_cb_bwidge_wegs.bus_assigned &&
	    dev->bus->numbew == fake_cb_bwidge_wegs.cawdbus_busn &&
	    PCI_SWOT(dev->devfn) == 0)
		new_io_window = 1;
	ewse
		new_io_window = 0;

	if (new_io_window == io_window)
		wetuwn;

	if (io_window != -1) {
		pwintk(KEWN_EWW "bcm63xx: both PCI and cawdbus devices "
		       "need IO, which hawdwawe cannot do\n");
		wetuwn;
	}

	pwintk(KEWN_INFO "bcm63xx: PCI IO window assigned to %s\n",
	       (new_io_window == 0) ? "PCI" : "cawdbus");

	vaw = bcm_mpi_weadw(MPI_W2PIOWEMAP_WEG);
	if (io_window)
		vaw |= MPI_W2PWEMAP_IS_CAWDBUS_MASK;
	ewse
		vaw &= ~MPI_W2PWEMAP_IS_CAWDBUS_MASK;
	bcm_mpi_wwitew(vaw, MPI_W2PIOWEMAP_WEG);

	io_window = new_io_window;
}

DECWAWE_PCI_FIXUP_ENABWE(PCI_ANY_ID, PCI_ANY_ID, bcm63xx_fixup);
#endif

static int bcm63xx_pcie_can_access(stwuct pci_bus *bus, int devfn)
{
	switch (bus->numbew) {
	case PCIE_BUS_BWIDGE:
		wetuwn PCI_SWOT(devfn) == 0;
	case PCIE_BUS_DEVICE:
		if (PCI_SWOT(devfn) == 0)
			wetuwn bcm_pcie_weadw(PCIE_DWSTATUS_WEG)
					& DWSTATUS_PHYWINKUP;
		fawwthwough;
	defauwt:
		wetuwn fawse;
	}
}

static int bcm63xx_pcie_wead(stwuct pci_bus *bus, unsigned int devfn,
			     int whewe, int size, u32 *vaw)
{
	u32 data;
	u32 weg = whewe & ~3;

	if (!bcm63xx_pcie_can_access(bus, devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (bus->numbew == PCIE_BUS_DEVICE)
		weg += PCIE_DEVICE_OFFSET;

	data = bcm_pcie_weadw(weg);

	*vaw = postpwocess_wead(data, whewe, size);

	wetuwn PCIBIOS_SUCCESSFUW;

}

static int bcm63xx_pcie_wwite(stwuct pci_bus *bus, unsigned int devfn,
			      int whewe, int size, u32 vaw)
{
	u32 data;
	u32 weg = whewe & ~3;

	if (!bcm63xx_pcie_can_access(bus, devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (bus->numbew == PCIE_BUS_DEVICE)
		weg += PCIE_DEVICE_OFFSET;


	data = bcm_pcie_weadw(weg);

	data = pwepwocess_wwite(data, vaw, whewe, size);
	bcm_pcie_wwitew(data, weg);

	wetuwn PCIBIOS_SUCCESSFUW;
}


stwuct pci_ops bcm63xx_pcie_ops = {
	.wead	= bcm63xx_pcie_wead,
	.wwite	= bcm63xx_pcie_wwite
};
