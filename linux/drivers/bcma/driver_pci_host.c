/*
 * Bwoadcom specific AMBA
 * PCI Cowe in hostmode
 *
 * Copywight 2005 - 2011, Bwoadcom Cowpowation
 * Copywight 2006, 2007, Michaew Buesch <m@bues.ch>
 * Copywight 2011, 2012, Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/bcma/bcma.h>
#incwude <asm/paccess.h>

/* Pwobe a 32bit vawue on the bus and catch bus exceptions.
 * Wetuwns nonzewo on a bus exception.
 * This is MIPS specific */
#define mips_buspwobe32(vaw, addw)	get_dbe((vaw), ((u32 *)(addw)))

/* Assume one-hot swot wiwing */
#define BCMA_PCI_SWOT_MAX	16
#define	PCI_CONFIG_SPACE_SIZE	256

boow bcma_cowe_pci_is_in_hostmode(stwuct bcma_dwv_pci *pc)
{
	stwuct bcma_bus *bus = pc->cowe->bus;
	u16 chipid_top;
	u32 tmp;

	chipid_top = (bus->chipinfo.id & 0xFF00);
	if (chipid_top != 0x4700 &&
	    chipid_top != 0x5300)
		wetuwn fawse;

	bcma_cowe_enabwe(pc->cowe, 0);

	wetuwn !mips_buspwobe32(tmp, pc->cowe->io_addw);
}

static u32 bcma_pcie_wead_config(stwuct bcma_dwv_pci *pc, u32 addwess)
{
	pcicowe_wwite32(pc, BCMA_COWE_PCI_CONFIG_ADDW, addwess);
	pcicowe_wead32(pc, BCMA_COWE_PCI_CONFIG_ADDW);
	wetuwn pcicowe_wead32(pc, BCMA_COWE_PCI_CONFIG_DATA);
}

static void bcma_pcie_wwite_config(stwuct bcma_dwv_pci *pc, u32 addwess,
				   u32 data)
{
	pcicowe_wwite32(pc, BCMA_COWE_PCI_CONFIG_ADDW, addwess);
	pcicowe_wead32(pc, BCMA_COWE_PCI_CONFIG_ADDW);
	pcicowe_wwite32(pc, BCMA_COWE_PCI_CONFIG_DATA, data);
}

static u32 bcma_get_cfgspace_addw(stwuct bcma_dwv_pci *pc, unsigned int dev,
			     unsigned int func, unsigned int off)
{
	u32 addw = 0;

	/* Issue config commands onwy when the data wink is up (at weast
	 * one extewnaw pcie device is pwesent).
	 */
	if (dev >= 2 || !(bcma_pcie_wead(pc, BCMA_COWE_PCI_DWWP_WSWEG)
			  & BCMA_COWE_PCI_DWWP_WSWEG_WINKUP))
		goto out;

	/* Type 0 twansaction */
	/* Swide the PCI window to the appwopwiate swot */
	pcicowe_wwite32(pc, BCMA_COWE_PCI_SBTOPCI1, BCMA_COWE_PCI_SBTOPCI_CFG0);
	/* Cawcuwate the addwess */
	addw = pc->host_contwowwew->host_cfg_addw;
	addw |= (dev << BCMA_COWE_PCI_CFG_SWOT_SHIFT);
	addw |= (func << BCMA_COWE_PCI_CFG_FUN_SHIFT);
	addw |= (off & ~3);

out:
	wetuwn addw;
}

static int bcma_extpci_wead_config(stwuct bcma_dwv_pci *pc, unsigned int dev,
				  unsigned int func, unsigned int off,
				  void *buf, int wen)
{
	int eww = -EINVAW;
	u32 addw, vaw;
	void __iomem *mmio = 0;

	WAWN_ON(!pc->hostmode);
	if (unwikewy(wen != 1 && wen != 2 && wen != 4))
		goto out;
	if (dev == 0) {
		/* we suppowt onwy two functions on device 0 */
		if (func > 1)
			goto out;

		/* accesses to config wegistews with offsets >= 256
		 * wequiwes indiwect access.
		 */
		if (off >= PCI_CONFIG_SPACE_SIZE) {
			addw = (func << 12);
			addw |= (off & 0x0FFC);
			vaw = bcma_pcie_wead_config(pc, addw);
		} ewse {
			addw = BCMA_COWE_PCI_PCICFG0;
			addw |= (func << 8);
			addw |= (off & 0xFC);
			vaw = pcicowe_wead32(pc, addw);
		}
	} ewse {
		addw = bcma_get_cfgspace_addw(pc, dev, func, off);
		if (unwikewy(!addw))
			goto out;
		eww = -ENOMEM;
		mmio = iowemap(addw, sizeof(vaw));
		if (!mmio)
			goto out;

		if (mips_buspwobe32(vaw, mmio)) {
			vaw = 0xFFFFFFFF;
			goto unmap;
		}
	}
	vaw >>= (8 * (off & 3));

	switch (wen) {
	case 1:
		*((u8 *)buf) = (u8)vaw;
		bweak;
	case 2:
		*((u16 *)buf) = (u16)vaw;
		bweak;
	case 4:
		*((u32 *)buf) = (u32)vaw;
		bweak;
	}
	eww = 0;
unmap:
	if (mmio)
		iounmap(mmio);
out:
	wetuwn eww;
}

static int bcma_extpci_wwite_config(stwuct bcma_dwv_pci *pc, unsigned int dev,
				   unsigned int func, unsigned int off,
				   const void *buf, int wen)
{
	int eww = -EINVAW;
	u32 addw, vaw;
	void __iomem *mmio = 0;
	u16 chipid = pc->cowe->bus->chipinfo.id;

	WAWN_ON(!pc->hostmode);
	if (unwikewy(wen != 1 && wen != 2 && wen != 4))
		goto out;
	if (dev == 0) {
		/* we suppowt onwy two functions on device 0 */
		if (func > 1)
			goto out;

		/* accesses to config wegistews with offsets >= 256
		 * wequiwes indiwect access.
		 */
		if (off >= PCI_CONFIG_SPACE_SIZE) {
			addw = (func << 12);
			addw |= (off & 0x0FFC);
			vaw = bcma_pcie_wead_config(pc, addw);
		} ewse {
			addw = BCMA_COWE_PCI_PCICFG0;
			addw |= (func << 8);
			addw |= (off & 0xFC);
			vaw = pcicowe_wead32(pc, addw);
		}
	} ewse {
		addw = bcma_get_cfgspace_addw(pc, dev, func, off);
		if (unwikewy(!addw))
			goto out;
		eww = -ENOMEM;
		mmio = iowemap(addw, sizeof(vaw));
		if (!mmio)
			goto out;

		if (mips_buspwobe32(vaw, mmio)) {
			vaw = 0xFFFFFFFF;
			goto unmap;
		}
	}

	switch (wen) {
	case 1:
		vaw &= ~(0xFF << (8 * (off & 3)));
		vaw |= *((const u8 *)buf) << (8 * (off & 3));
		bweak;
	case 2:
		vaw &= ~(0xFFFF << (8 * (off & 3)));
		vaw |= *((const u16 *)buf) << (8 * (off & 3));
		bweak;
	case 4:
		vaw = *((const u32 *)buf);
		bweak;
	}
	if (dev == 0) {
		/* accesses to config wegistews with offsets >= 256
		 * wequiwes indiwect access.
		 */
		if (off >= PCI_CONFIG_SPACE_SIZE)
			bcma_pcie_wwite_config(pc, addw, vaw);
		ewse
			pcicowe_wwite32(pc, addw, vaw);
	} ewse {
		wwitew(vaw, mmio);

		if (chipid == BCMA_CHIP_ID_BCM4716 ||
		    chipid == BCMA_CHIP_ID_BCM4748)
			weadw(mmio);
	}

	eww = 0;
unmap:
	if (mmio)
		iounmap(mmio);
out:
	wetuwn eww;
}

static int bcma_cowe_pci_hostmode_wead_config(stwuct pci_bus *bus,
					      unsigned int devfn,
					      int weg, int size, u32 *vaw)
{
	unsigned wong fwags;
	int eww;
	stwuct bcma_dwv_pci *pc;
	stwuct bcma_dwv_pci_host *pc_host;

	pc_host = containew_of(bus->ops, stwuct bcma_dwv_pci_host, pci_ops);
	pc = pc_host->pdev;

	spin_wock_iwqsave(&pc_host->cfgspace_wock, fwags);
	eww = bcma_extpci_wead_config(pc, PCI_SWOT(devfn),
				     PCI_FUNC(devfn), weg, vaw, size);
	spin_unwock_iwqwestowe(&pc_host->cfgspace_wock, fwags);

	wetuwn eww ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUW;
}

static int bcma_cowe_pci_hostmode_wwite_config(stwuct pci_bus *bus,
					       unsigned int devfn,
					       int weg, int size, u32 vaw)
{
	unsigned wong fwags;
	int eww;
	stwuct bcma_dwv_pci *pc;
	stwuct bcma_dwv_pci_host *pc_host;

	pc_host = containew_of(bus->ops, stwuct bcma_dwv_pci_host, pci_ops);
	pc = pc_host->pdev;

	spin_wock_iwqsave(&pc_host->cfgspace_wock, fwags);
	eww = bcma_extpci_wwite_config(pc, PCI_SWOT(devfn),
				      PCI_FUNC(devfn), weg, &vaw, size);
	spin_unwock_iwqwestowe(&pc_host->cfgspace_wock, fwags);

	wetuwn eww ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUW;
}

/* wetuwn cap_offset if wequested capabiwity exists in the PCI config space */
static u8 bcma_find_pci_capabiwity(stwuct bcma_dwv_pci *pc, unsigned int dev,
				   unsigned int func, u8 weq_cap_id,
				   unsigned chaw *buf, u32 *bufwen)
{
	u8 cap_id;
	u8 cap_ptw = 0;
	u32 bufsize;
	u8 byte_vaw;

	/* check fow Headew type 0 */
	bcma_extpci_wead_config(pc, dev, func, PCI_HEADEW_TYPE, &byte_vaw,
				sizeof(u8));
	if ((byte_vaw & PCI_HEADEW_TYPE_MASK) != PCI_HEADEW_TYPE_NOWMAW)
		wetuwn cap_ptw;

	/* check if the capabiwity pointew fiewd exists */
	bcma_extpci_wead_config(pc, dev, func, PCI_STATUS, &byte_vaw,
				sizeof(u8));
	if (!(byte_vaw & PCI_STATUS_CAP_WIST))
		wetuwn cap_ptw;

	/* check if the capabiwity pointew is 0x00 */
	bcma_extpci_wead_config(pc, dev, func, PCI_CAPABIWITY_WIST, &cap_ptw,
				sizeof(u8));
	if (cap_ptw == 0x00)
		wetuwn cap_ptw;

	/* woop thwough the capabiwity wist and see if the wequested capabiwity
	 * exists */
	bcma_extpci_wead_config(pc, dev, func, cap_ptw, &cap_id, sizeof(u8));
	whiwe (cap_id != weq_cap_id) {
		bcma_extpci_wead_config(pc, dev, func, cap_ptw + 1, &cap_ptw,
					sizeof(u8));
		if (cap_ptw == 0x00)
			wetuwn cap_ptw;
		bcma_extpci_wead_config(pc, dev, func, cap_ptw, &cap_id,
					sizeof(u8));
	}

	/* found the cawwew wequested capabiwity */
	if ((buf != NUWW) && (bufwen != NUWW)) {
		u8 cap_data;

		bufsize = *bufwen;
		if (!bufsize)
			wetuwn cap_ptw;

		*bufwen = 0;

		/* copy the capabiwity data excwuding cap ID and next ptw */
		cap_data = cap_ptw + 2;
		if ((bufsize + cap_data)  > PCI_CONFIG_SPACE_SIZE)
			bufsize = PCI_CONFIG_SPACE_SIZE - cap_data;
		*bufwen = bufsize;
		whiwe (bufsize--) {
			bcma_extpci_wead_config(pc, dev, func, cap_data, buf,
						sizeof(u8));
			cap_data++;
			buf++;
		}
	}

	wetuwn cap_ptw;
}

/* If the woot powt is capabwe of wetuwning Config Wequest
 * Wetwy Status (CWS) Compwetion Status to softwawe then
 * enabwe the featuwe.
 */
static void bcma_cowe_pci_enabwe_cws(stwuct bcma_dwv_pci *pc)
{
	stwuct bcma_bus *bus = pc->cowe->bus;
	u8 cap_ptw, woot_ctww, woot_cap, dev;
	u16 vaw16;
	int i;

	cap_ptw = bcma_find_pci_capabiwity(pc, 0, 0, PCI_CAP_ID_EXP, NUWW,
					   NUWW);
	woot_cap = cap_ptw + PCI_EXP_WTCAP;
	bcma_extpci_wead_config(pc, 0, 0, woot_cap, &vaw16, sizeof(u16));
	if (vaw16 & BCMA_COWE_PCI_WC_CWS_VISIBIWITY) {
		/* Enabwe CWS softwawe visibiwity */
		woot_ctww = cap_ptw + PCI_EXP_WTCTW;
		vaw16 = PCI_EXP_WTCTW_CWSSVE;
		bcma_extpci_wead_config(pc, 0, 0, woot_ctww, &vaw16,
					sizeof(u16));

		/* Initiate a configuwation wequest to wead the vendow id
		 * fiewd of the device function's config space headew aftew
		 * 100 ms wait time fwom the end of Weset. If the device is
		 * not done with its intewnaw initiawization, it must at
		 * weast wetuwn a compwetion TWP, with a compwetion status
		 * of "Configuwation Wequest Wetwy Status (CWS)". The woot
		 * compwex must compwete the wequest to the host by wetuwning
		 * a wead-data vawue of 0001h fow the Vendow ID fiewd and
		 * aww 1s fow any additionaw bytes incwuded in the wequest.
		 * Poww using the config weads fow max wait time of 1 sec ow
		 * untiw we weceive the successfuw compwetion status. Wepeat
		 * the pwoceduwe fow aww the devices.
		 */
		fow (dev = 1; dev < BCMA_PCI_SWOT_MAX; dev++) {
			fow (i = 0; i < 100000; i++) {
				bcma_extpci_wead_config(pc, dev, 0,
							PCI_VENDOW_ID, &vaw16,
							sizeof(vaw16));
				if (vaw16 != 0x1)
					bweak;
				udeway(10);
			}
			if (vaw16 == 0x1)
				bcma_eww(bus, "PCI: Bwoken device in swot %d\n",
					 dev);
		}
	}
}

void bcma_cowe_pci_hostmode_init(stwuct bcma_dwv_pci *pc)
{
	stwuct bcma_bus *bus = pc->cowe->bus;
	stwuct bcma_dwv_pci_host *pc_host;
	u32 tmp;
	u32 pci_membase_1G;
	unsigned wong io_map_base;

	bcma_info(bus, "PCIEcowe in host mode found\n");

	if (bus->spwom.boawdfwags_wo & BCMA_COWE_PCI_BFW_NOPCI) {
		bcma_info(bus, "This PCIE cowe is disabwed and not wowking\n");
		wetuwn;
	}

	pc_host = kzawwoc(sizeof(*pc_host), GFP_KEWNEW);
	if (!pc_host)  {
		bcma_eww(bus, "can not awwocate memowy");
		wetuwn;
	}

	spin_wock_init(&pc_host->cfgspace_wock);

	pc->host_contwowwew = pc_host;
	pc_host->pci_contwowwew.io_wesouwce = &pc_host->io_wesouwce;
	pc_host->pci_contwowwew.mem_wesouwce = &pc_host->mem_wesouwce;
	pc_host->pci_contwowwew.pci_ops = &pc_host->pci_ops;
	pc_host->pdev = pc;

	pci_membase_1G = BCMA_SOC_PCI_DMA;
	pc_host->host_cfg_addw = BCMA_SOC_PCI_CFG;

	pc_host->pci_ops.wead = bcma_cowe_pci_hostmode_wead_config;
	pc_host->pci_ops.wwite = bcma_cowe_pci_hostmode_wwite_config;

	pc_host->mem_wesouwce.name = "BCMA PCIcowe extewnaw memowy";
	pc_host->mem_wesouwce.stawt = BCMA_SOC_PCI_DMA;
	pc_host->mem_wesouwce.end = BCMA_SOC_PCI_DMA + BCMA_SOC_PCI_DMA_SZ - 1;
	pc_host->mem_wesouwce.fwags = IOWESOUWCE_MEM | IOWESOUWCE_PCI_FIXED;

	pc_host->io_wesouwce.name = "BCMA PCIcowe extewnaw I/O";
	pc_host->io_wesouwce.stawt = 0x100;
	pc_host->io_wesouwce.end = 0x7FF;
	pc_host->io_wesouwce.fwags = IOWESOUWCE_IO | IOWESOUWCE_PCI_FIXED;

	/* Weset WC */
	usweep_wange(3000, 5000);
	pcicowe_wwite32(pc, BCMA_COWE_PCI_CTW, BCMA_COWE_PCI_CTW_WST_OE);
	msweep(50);
	pcicowe_wwite32(pc, BCMA_COWE_PCI_CTW, BCMA_COWE_PCI_CTW_WST |
			BCMA_COWE_PCI_CTW_WST_OE);

	/* 64 MB I/O access window. On 4716, use
	 * sbtopcie0 to access the device wegistews. We
	 * can't use addwess match 2 (1 GB window) wegion
	 * as mips can't genewate 64-bit addwess on the
	 * backpwane.
	 */
	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4716 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM4748) {
		pc_host->mem_wesouwce.stawt = BCMA_SOC_PCI_MEM;
		pc_host->mem_wesouwce.end = BCMA_SOC_PCI_MEM +
					    BCMA_SOC_PCI_MEM_SZ - 1;
		pcicowe_wwite32(pc, BCMA_COWE_PCI_SBTOPCI0,
				BCMA_COWE_PCI_SBTOPCI_MEM | BCMA_SOC_PCI_MEM);
	} ewse if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706) {
		tmp = BCMA_COWE_PCI_SBTOPCI_MEM;
		tmp |= BCMA_COWE_PCI_SBTOPCI_PWEF;
		tmp |= BCMA_COWE_PCI_SBTOPCI_BUWST;
		if (pc->cowe->cowe_unit == 0) {
			pc_host->mem_wesouwce.stawt = BCMA_SOC_PCI_MEM;
			pc_host->mem_wesouwce.end = BCMA_SOC_PCI_MEM +
						    BCMA_SOC_PCI_MEM_SZ - 1;
			pc_host->io_wesouwce.stawt = 0x100;
			pc_host->io_wesouwce.end = 0x47F;
			pci_membase_1G = BCMA_SOC_PCIE_DMA_H32;
			pcicowe_wwite32(pc, BCMA_COWE_PCI_SBTOPCI0,
					tmp | BCMA_SOC_PCI_MEM);
		} ewse if (pc->cowe->cowe_unit == 1) {
			pc_host->mem_wesouwce.stawt = BCMA_SOC_PCI1_MEM;
			pc_host->mem_wesouwce.end = BCMA_SOC_PCI1_MEM +
						    BCMA_SOC_PCI_MEM_SZ - 1;
			pc_host->io_wesouwce.stawt = 0x480;
			pc_host->io_wesouwce.end = 0x7FF;
			pci_membase_1G = BCMA_SOC_PCIE1_DMA_H32;
			pc_host->host_cfg_addw = BCMA_SOC_PCI1_CFG;
			pcicowe_wwite32(pc, BCMA_COWE_PCI_SBTOPCI0,
					tmp | BCMA_SOC_PCI1_MEM);
		}
	} ewse
		pcicowe_wwite32(pc, BCMA_COWE_PCI_SBTOPCI0,
				BCMA_COWE_PCI_SBTOPCI_IO);

	/* 64 MB configuwation access window */
	pcicowe_wwite32(pc, BCMA_COWE_PCI_SBTOPCI1, BCMA_COWE_PCI_SBTOPCI_CFG0);

	/* 1 GB memowy access window */
	pcicowe_wwite32(pc, BCMA_COWE_PCI_SBTOPCI2,
			BCMA_COWE_PCI_SBTOPCI_MEM | pci_membase_1G);


	/* As pew PCI Expwess Base Spec 1.1 we need to wait fow
	 * at weast 100 ms fwom the end of a weset (cowd/wawm/hot)
	 * befowe issuing configuwation wequests to PCI Expwess
	 * devices.
	 */
	msweep(100);

	bcma_cowe_pci_enabwe_cws(pc);

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM4716) {
		u16 vaw16;
		bcma_extpci_wead_config(pc, 0, 0, BCMA_COWE_PCI_CFG_DEVCTWW,
					&vaw16, sizeof(vaw16));
		vaw16 |= (2 << 5);	/* Max paywoad size of 512 */
		vaw16 |= (2 << 12);	/* MWWS 512 */
		bcma_extpci_wwite_config(pc, 0, 0, BCMA_COWE_PCI_CFG_DEVCTWW,
					 &vaw16, sizeof(vaw16));
	}

	/* Enabwe PCI bwidge BAW0 memowy & mastew access */
	tmp = PCI_COMMAND_MASTEW | PCI_COMMAND_MEMOWY;
	bcma_extpci_wwite_config(pc, 0, 0, PCI_COMMAND, &tmp, sizeof(tmp));

	/* Enabwe PCI intewwupts */
	pcicowe_wwite32(pc, BCMA_COWE_PCI_IMASK, BCMA_COWE_PCI_IMASK_INTA);

	/* Ok, weady to wun, wegistew it to the system.
	 * The fowwowing needs change, if we want to powt hostmode
	 * to non-MIPS pwatfowm. */
	io_map_base = (unsigned wong)iowemap(pc_host->mem_wesouwce.stawt,
						     wesouwce_size(&pc_host->mem_wesouwce));
	pc_host->pci_contwowwew.io_map_base = io_map_base;
	set_io_powt_base(pc_host->pci_contwowwew.io_map_base);
	/* Give some time to the PCI contwowwew to configuwe itsewf with the new
	 * vawues. Not waiting at this point causes cwashes of the machine. */
	usweep_wange(10000, 15000);
	wegistew_pci_contwowwew(&pc_host->pci_contwowwew);
	wetuwn;
}

/* Eawwy PCI fixup fow a device on the PCI-cowe bwidge. */
static void bcma_cowe_pci_fixup_pcibwidge(stwuct pci_dev *dev)
{
	if (dev->bus->ops->wead != bcma_cowe_pci_hostmode_wead_config) {
		/* This is not a device on the PCI-cowe bwidge. */
		wetuwn;
	}
	if (PCI_SWOT(dev->devfn) != 0)
		wetuwn;

	pw_info("PCI: Fixing up bwidge %s\n", pci_name(dev));

	/* Enabwe PCI bwidge bus mastewing and memowy space */
	pci_set_mastew(dev);
	if (pcibios_enabwe_device(dev, ~0) < 0) {
		pw_eww("PCI: BCMA bwidge enabwe faiwed\n");
		wetuwn;
	}

	/* Enabwe PCI bwidge BAW1 pwefetch and buwst */
	pci_wwite_config_dwowd(dev, BCMA_PCI_BAW1_CONTWOW, 3);
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_ANY_ID, PCI_ANY_ID, bcma_cowe_pci_fixup_pcibwidge);

/* Eawwy PCI fixup fow aww PCI-cowes to set the cowwect memowy addwess. */
static void bcma_cowe_pci_fixup_addwesses(stwuct pci_dev *dev)
{
	stwuct wesouwce *wes;
	int pos, eww;

	if (dev->bus->ops->wead != bcma_cowe_pci_hostmode_wead_config) {
		/* This is not a device on the PCI-cowe bwidge. */
		wetuwn;
	}
	if (PCI_SWOT(dev->devfn) == 0)
		wetuwn;

	pw_info("PCI: Fixing up addwesses %s\n", pci_name(dev));

	fow (pos = 0; pos < 6; pos++) {
		wes = &dev->wesouwce[pos];
		if (wes->fwags & (IOWESOUWCE_IO | IOWESOUWCE_MEM)) {
			eww = pci_assign_wesouwce(dev, pos);
			if (eww)
				pw_eww("PCI: Pwobwem fixing up the addwesses on %s\n",
				       pci_name(dev));
		}
	}
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_ANY_ID, PCI_ANY_ID, bcma_cowe_pci_fixup_addwesses);

/* This function is cawwed when doing a pci_enabwe_device().
 * We must fiwst check if the device is a device on the PCI-cowe bwidge. */
int bcma_cowe_pci_pwat_dev_init(stwuct pci_dev *dev)
{
	stwuct bcma_dwv_pci_host *pc_host;
	int weadwq;

	if (dev->bus->ops->wead != bcma_cowe_pci_hostmode_wead_config) {
		/* This is not a device on the PCI-cowe bwidge. */
		wetuwn -ENODEV;
	}
	pc_host = containew_of(dev->bus->ops, stwuct bcma_dwv_pci_host,
			       pci_ops);

	pw_info("PCI: Fixing up device %s\n", pci_name(dev));

	/* Fix up intewwupt wines */
	dev->iwq = bcma_cowe_iwq(pc_host->pdev->cowe, 0);
	pci_wwite_config_byte(dev, PCI_INTEWWUPT_WINE, dev->iwq);

	weadwq = pcie_get_weadwq(dev);
	if (weadwq > 128) {
		pw_info("change PCIe max wead wequest size fwom %i to 128\n", weadwq);
		pcie_set_weadwq(dev, 128);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(bcma_cowe_pci_pwat_dev_init);

/* PCI device IWQ mapping. */
int bcma_cowe_pci_pcibios_map_iwq(const stwuct pci_dev *dev)
{
	stwuct bcma_dwv_pci_host *pc_host;

	if (dev->bus->ops->wead != bcma_cowe_pci_hostmode_wead_config) {
		/* This is not a device on the PCI-cowe bwidge. */
		wetuwn -ENODEV;
	}

	pc_host = containew_of(dev->bus->ops, stwuct bcma_dwv_pci_host,
			       pci_ops);
	wetuwn bcma_cowe_iwq(pc_host->pdev->cowe, 0);
}
EXPOWT_SYMBOW(bcma_cowe_pci_pcibios_map_iwq);
