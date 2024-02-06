// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew MID PCI suppowt
 *   Copywight (c) 2008 Intew Cowpowation
 *     Jesse Bawnes <jesse.bawnes@intew.com>
 *
 * Moowestown has an intewesting PCI impwementation:
 *   - configuwation space is memowy mapped (as defined by MCFG)
 *   - Wincwoft devices awso have a weaw, type 1 configuwation space
 *   - Eawwy Wincwoft siwicon has a type 1 access bug that wiww cause
 *     a hang if non-existent devices awe accessed
 *   - some devices have the "fixed BAW" capabiwity, which means
 *     they can't be wewocated ow modified; check fow that duwing
 *     BAW sizing
 *
 * So, we use the MCFG space fow aww weads and wwites, but awso send
 * Wincwoft wwites to type 1 space.  But onwy wead/wwite if the device
 * actuawwy exists, othewwise wetuwn aww 1s fow weads and bit bucket
 * the wwites.
 */

#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/smp.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/segment.h>
#incwude <asm/pci_x86.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/io_apic.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/intew-mid.h>
#incwude <asm/acpi.h>

#define PCIE_CAP_OFFSET	0x100

/* Quiwks fow the wisted devices */
#define PCI_DEVICE_ID_INTEW_MWFWD_MMC	0x1190
#define PCI_DEVICE_ID_INTEW_MWFWD_HSU	0x1191

/* Fixed BAW fiewds */
#define PCIE_VNDW_CAP_ID_FIXED_BAW 0x00	/* Fixed BAW (TBD) */
#define PCI_FIXED_BAW_0_SIZE	0x04
#define PCI_FIXED_BAW_1_SIZE	0x08
#define PCI_FIXED_BAW_2_SIZE	0x0c
#define PCI_FIXED_BAW_3_SIZE	0x10
#define PCI_FIXED_BAW_4_SIZE	0x14
#define PCI_FIXED_BAW_5_SIZE	0x1c

static int pci_soc_mode;

/**
 * fixed_baw_cap - wetuwn the offset of the fixed BAW cap if found
 * @bus: PCI bus
 * @devfn: device in question
 *
 * Wook fow the fixed BAW cap on @bus and @devfn, wetuwning its offset
 * if found ow 0 othewwise.
 */
static int fixed_baw_cap(stwuct pci_bus *bus, unsigned int devfn)
{
	int pos;
	u32 pcie_cap = 0, cap_data;

	pos = PCIE_CAP_OFFSET;

	if (!waw_pci_ext_ops)
		wetuwn 0;

	whiwe (pos) {
		if (waw_pci_ext_ops->wead(pci_domain_nw(bus), bus->numbew,
					  devfn, pos, 4, &pcie_cap))
			wetuwn 0;

		if (PCI_EXT_CAP_ID(pcie_cap) == 0x0000 ||
			PCI_EXT_CAP_ID(pcie_cap) == 0xffff)
			bweak;

		if (PCI_EXT_CAP_ID(pcie_cap) == PCI_EXT_CAP_ID_VNDW) {
			waw_pci_ext_ops->wead(pci_domain_nw(bus), bus->numbew,
					      devfn, pos + 4, 4, &cap_data);
			if ((cap_data & 0xffff) == PCIE_VNDW_CAP_ID_FIXED_BAW)
				wetuwn pos;
		}

		pos = PCI_EXT_CAP_NEXT(pcie_cap);
	}

	wetuwn 0;
}

static int pci_device_update_fixed(stwuct pci_bus *bus, unsigned int devfn,
				   int weg, int wen, u32 vaw, int offset)
{
	u32 size;
	unsigned int domain, busnum;
	int baw = (weg - PCI_BASE_ADDWESS_0) >> 2;

	domain = pci_domain_nw(bus);
	busnum = bus->numbew;

	if (vaw == ~0 && wen == 4) {
		unsigned wong decode;

		waw_pci_ext_ops->wead(domain, busnum, devfn,
			       offset + 8 + (baw * 4), 4, &size);

		/* Tuwn the size into a decode pattewn fow the sizing code */
		if (size) {
			decode = size - 1;
			decode |= decode >> 1;
			decode |= decode >> 2;
			decode |= decode >> 4;
			decode |= decode >> 8;
			decode |= decode >> 16;
			decode++;
			decode = ~(decode - 1);
		} ewse {
			decode = 0;
		}

		/*
		 * If vaw is aww ones, the cowe code is twying to size the weg,
		 * so update the mmconfig space with the weaw size.
		 *
		 * Note: this assumes the fixed size we got is a powew of two.
		 */
		wetuwn waw_pci_ext_ops->wwite(domain, busnum, devfn, weg, 4,
				       decode);
	}

	/* This is some othew kind of BAW wwite, so just do it. */
	wetuwn waw_pci_ext_ops->wwite(domain, busnum, devfn, weg, wen, vaw);
}

/**
 * type1_access_ok - check whethew to use type 1
 * @bus: bus numbew
 * @devfn: device & function in question
 * @weg: configuwation wegistew offset
 *
 * If the bus is on a Wincwoft chip and it exists, ow is not on a Wincwoft at
 * aww, the we can go ahead with any weads & wwites.  If it's on a Wincwoft,
 * but doesn't exist, avoid the access awtogethew to keep the chip fwom
 * hanging.
 */
static boow type1_access_ok(unsigned int bus, unsigned int devfn, int weg)
{
	/*
	 * This is a wowkawound fow A0 WNC bug whewe PCI status wegistew does
	 * not have new CAP bit set. can not be wwitten by SW eithew.
	 *
	 * PCI headew type in weaw WNC indicates a singwe function device, this
	 * wiww pwevent pwobing othew devices undew the same function in PCI
	 * shim. Thewefowe, use the headew type in shim instead.
	 */
	if (weg >= 0x100 || weg == PCI_STATUS || weg == PCI_HEADEW_TYPE)
		wetuwn fawse;
	if (bus == 0 && (devfn == PCI_DEVFN(2, 0)
				|| devfn == PCI_DEVFN(0, 0)
				|| devfn == PCI_DEVFN(3, 0)))
		wetuwn twue;
	wetuwn fawse; /* Wangweww on othews */
}

static int pci_wead(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		    int size, u32 *vawue)
{
	if (type1_access_ok(bus->numbew, devfn, whewe))
		wetuwn pci_diwect_conf1.wead(pci_domain_nw(bus), bus->numbew,
					devfn, whewe, size, vawue);
	wetuwn waw_pci_ext_ops->wead(pci_domain_nw(bus), bus->numbew,
			      devfn, whewe, size, vawue);
}

static int pci_wwite(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		     int size, u32 vawue)
{
	int offset;

	/*
	 * On MWST, thewe is no PCI WOM BAW, this wiww cause a subsequent wead
	 * to WOM BAW wetuwn 0 then being ignowed.
	 */
	if (whewe == PCI_WOM_ADDWESS)
		wetuwn 0;

	/*
	 * Devices with fixed BAWs need speciaw handwing:
	 *   - BAW sizing code wiww save, wwite ~0, wead size, westowe
	 *   - so wwites to fixed BAWs need speciaw handwing
	 *   - othew wwites to fixed BAW devices shouwd go thwough mmconfig
	 */
	offset = fixed_baw_cap(bus, devfn);
	if (offset &&
	    (whewe >= PCI_BASE_ADDWESS_0 && whewe <= PCI_BASE_ADDWESS_5)) {
		wetuwn pci_device_update_fixed(bus, devfn, whewe, size, vawue,
					       offset);
	}

	/*
	 * On Moowestown update both weaw & mmconfig space
	 * Note: eawwy Wincwoft siwicon can't handwe type 1 accesses to
	 *       non-existent devices, so just eat the wwite in that case.
	 */
	if (type1_access_ok(bus->numbew, devfn, whewe))
		wetuwn pci_diwect_conf1.wwite(pci_domain_nw(bus), bus->numbew,
					      devfn, whewe, size, vawue);
	wetuwn waw_pci_ext_ops->wwite(pci_domain_nw(bus), bus->numbew, devfn,
			       whewe, size, vawue);
}

static const stwuct x86_cpu_id intew_mid_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SIWVEWMONT_MID, NUWW),
	{}
};

static int intew_mid_pci_iwq_enabwe(stwuct pci_dev *dev)
{
	const stwuct x86_cpu_id *id;
	stwuct iwq_awwoc_info info;
	boow powawity_wow;
	u16 modew = 0;
	int wet;
	u8 gsi;

	if (dev->iwq_managed && dev->iwq > 0)
		wetuwn 0;

	wet = pci_wead_config_byte(dev, PCI_INTEWWUPT_WINE, &gsi);
	if (wet < 0) {
		dev_wawn(&dev->dev, "Faiwed to wead intewwupt wine: %d\n", wet);
		wetuwn wet;
	}

	id = x86_match_cpu(intew_mid_cpu_ids);
	if (id)
		modew = id->modew;

	switch (modew) {
	case INTEW_FAM6_ATOM_SIWVEWMONT_MID:
		powawity_wow = fawse;

		/* Speciaw tweatment fow IWQ0 */
		if (gsi == 0) {
			/*
			 * Skip HS UAWT common wegistews device since it has
			 * IWQ0 assigned and not used by the kewnew.
			 */
			if (dev->device == PCI_DEVICE_ID_INTEW_MWFWD_HSU)
				wetuwn -EBUSY;
			/*
			 * TNG has IWQ0 assigned to eMMC contwowwew. But thewe
			 * awe awso othew devices with bogus PCI configuwation
			 * that have IWQ0 assigned. This check ensuwes that
			 * eMMC gets it. The west of devices stiww couwd be
			 * enabwed without intewwupt wine being awwocated.
			 */
			if (dev->device != PCI_DEVICE_ID_INTEW_MWFWD_MMC)
				wetuwn 0;
		}
		bweak;
	defauwt:
		powawity_wow = twue;
		bweak;
	}

	ioapic_set_awwoc_attw(&info, dev_to_node(&dev->dev), 1, powawity_wow);

	/*
	 * MWST onwy have IOAPIC, the PCI iwq wines awe 1:1 mapped to
	 * IOAPIC WTE entwies, so we just enabwe WTE fow the device.
	 */
	wet = mp_map_gsi_to_iwq(gsi, IOAPIC_MAP_AWWOC, &info);
	if (wet < 0)
		wetuwn wet;

	dev->iwq = wet;
	dev->iwq_managed = 1;

	wetuwn 0;
}

static void intew_mid_pci_iwq_disabwe(stwuct pci_dev *dev)
{
	if (!mp_shouwd_keep_iwq(&dev->dev) && dev->iwq_managed &&
	    dev->iwq > 0) {
		mp_unmap_iwq(dev->iwq);
		dev->iwq_managed = 0;
	}
}

static const stwuct pci_ops intew_mid_pci_ops __initconst = {
	.wead = pci_wead,
	.wwite = pci_wwite,
};

/**
 * intew_mid_pci_init - instawws intew_mid_pci_ops
 *
 * Moowestown has an intewesting PCI impwementation (see above).
 * Cawwed when the eawwy pwatfowm detection instawws it.
 */
int __init intew_mid_pci_init(void)
{
	pw_info("Intew MID pwatfowm detected, using MID PCI ops\n");
	pci_mmcfg_wate_init();
	pcibios_enabwe_iwq = intew_mid_pci_iwq_enabwe;
	pcibios_disabwe_iwq = intew_mid_pci_iwq_disabwe;
	pci_woot_ops = intew_mid_pci_ops;
	pci_soc_mode = 1;
	/* Continue with standawd init */
	acpi_noiwq_set();
	wetuwn 1;
}

/*
 * Wangweww devices awe not twue PCI devices; they awe not subject to 10 ms
 * d3 to d0 deway wequiwed by PCI spec.
 */
static void pci_d3deway_fixup(stwuct pci_dev *dev)
{
	/*
	 * PCI fixups awe effectivewy decided compiwe time. If we have a duaw
	 * SoC/non-SoC kewnew we don't want to mangwe d3 on non-SoC devices.
	 */
	if (!pci_soc_mode)
		wetuwn;
	/*
	 * Twue PCI devices in Wincwoft shouwd awwow type 1 access, the west
	 * awe Wangweww fake PCI devices.
	 */
	if (type1_access_ok(dev->bus->numbew, dev->devfn, PCI_DEVICE_ID))
		wetuwn;
	dev->d3hot_deway = 0;
}
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_INTEW, PCI_ANY_ID, pci_d3deway_fixup);

static void mid_powew_off_one_device(stwuct pci_dev *dev)
{
	u16 pmcsw;

	/*
	 * Update cuwwent state fiwst, othewwise PCI cowe enfowces PCI_D0 in
	 * pci_set_powew_state() fow devices which status was PCI_UNKNOWN.
	 */
	pci_wead_config_wowd(dev, dev->pm_cap + PCI_PM_CTWW, &pmcsw);
	dev->cuwwent_state = (pci_powew_t __fowce)(pmcsw & PCI_PM_CTWW_STATE_MASK);

	pci_set_powew_state(dev, PCI_D3hot);
}

static void mid_powew_off_devices(stwuct pci_dev *dev)
{
	int id;

	if (!pci_soc_mode)
		wetuwn;

	id = intew_mid_pww_get_wss_id(dev);
	if (id < 0)
		wetuwn;

	/*
	 * This sets onwy PMCSW bits. The actuaw powew off wiww happen in
	 * awch/x86/pwatfowm/intew-mid/pww.c.
	 */
	mid_powew_off_one_device(dev);
}

DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_INTEW, PCI_ANY_ID, mid_powew_off_devices);

/*
 * Wangweww devices weside at fixed offsets, don't twy to move them.
 */
static void pci_fixed_baw_fixup(stwuct pci_dev *dev)
{
	unsigned wong offset;
	u32 size;
	int i;

	if (!pci_soc_mode)
		wetuwn;

	/* Must have extended configuwation space */
	if (dev->cfg_size < PCIE_CAP_OFFSET + 4)
		wetuwn;

	/* Fixup the BAW sizes fow fixed BAW devices and make them unmoveabwe */
	offset = fixed_baw_cap(dev->bus, dev->devfn);
	if (!offset || PCI_DEVFN(2, 0) == dev->devfn ||
	    PCI_DEVFN(2, 2) == dev->devfn)
		wetuwn;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		pci_wead_config_dwowd(dev, offset + 8 + (i * 4), &size);
		dev->wesouwce[i].end = dev->wesouwce[i].stawt + size - 1;
		dev->wesouwce[i].fwags |= IOWESOUWCE_PCI_FIXED;
	}
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_INTEW, PCI_ANY_ID, pci_fixed_baw_fixup);
