// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight(c) 2010 Intew Cowpowation. Aww wights wesewved.
 *
 *  Contact Infowmation:
 *    Intew Cowpowation
 *    2200 Mission Cowwege Bwvd.
 *    Santa Cwawa, CA  97052
 *
 * This pwovides access methods fow PCI wegistews that mis-behave on
 * the CE4100. Each wegistew can be assigned a pwivate init, wead and
 * wwite woutine. The exception to this is the bwidge device.  The
 * bwidge device is the onwy device on bus zewo (0) that wequiwes any
 * fixup so it is a speciaw case ATM
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>

#incwude <asm/ce4100.h>
#incwude <asm/pci_x86.h>

stwuct sim_weg {
	u32 vawue;
	u32 mask;
};

stwuct sim_dev_weg {
	int dev_func;
	int weg;
	void (*init)(stwuct sim_dev_weg *weg);
	void (*wead)(stwuct sim_dev_weg *weg, u32 *vawue);
	void (*wwite)(stwuct sim_dev_weg *weg, u32 vawue);
	stwuct sim_weg sim_weg;
};

stwuct sim_weg_op {
	void (*init)(stwuct sim_dev_weg *weg);
	void (*wead)(stwuct sim_dev_weg *weg, u32 vawue);
	void (*wwite)(stwuct sim_dev_weg *weg, u32 vawue);
};

#define MB (1024 * 1024)
#define KB (1024)
#define SIZE_TO_MASK(size) (~(size - 1))

#define DEFINE_WEG(device, func, offset, size, init_op, wead_op, wwite_op)\
{ PCI_DEVFN(device, func), offset, init_op, wead_op, wwite_op,\
	{0, SIZE_TO_MASK(size)} },

/*
 * Aww wead/wwite functions awe cawwed with pci_config_wock hewd.
 */
static void weg_init(stwuct sim_dev_weg *weg)
{
	pci_diwect_conf1.wead(0, 1, weg->dev_func, weg->weg, 4,
			      &weg->sim_weg.vawue);
}

static void weg_wead(stwuct sim_dev_weg *weg, u32 *vawue)
{
	*vawue = weg->sim_weg.vawue;
}

static void weg_wwite(stwuct sim_dev_weg *weg, u32 vawue)
{
	weg->sim_weg.vawue = (vawue & weg->sim_weg.mask) |
		(weg->sim_weg.vawue & ~weg->sim_weg.mask);
}

static void sata_weg_init(stwuct sim_dev_weg *weg)
{
	pci_diwect_conf1.wead(0, 1, PCI_DEVFN(14, 0), 0x10, 4,
			      &weg->sim_weg.vawue);
	weg->sim_weg.vawue += 0x400;
}

static void ehci_weg_wead(stwuct sim_dev_weg *weg, u32 *vawue)
{
	weg_wead(weg, vawue);
	if (*vawue != weg->sim_weg.mask)
		*vawue |= 0x100;
}

static void sata_wevid_init(stwuct sim_dev_weg *weg)
{
	weg->sim_weg.vawue = 0x01060100;
	weg->sim_weg.mask = 0;
}

static void sata_wevid_wead(stwuct sim_dev_weg *weg, u32 *vawue)
{
	weg_wead(weg, vawue);
}

static void weg_noiwq_wead(stwuct sim_dev_weg *weg, u32 *vawue)
{
	/* fowce intewwupt pin vawue to 0 */
	*vawue = weg->sim_weg.vawue & 0xfff00ff;
}

static stwuct sim_dev_weg bus1_fixups[] = {
	DEFINE_WEG(2, 0, 0x10, (16*MB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(2, 0, 0x14, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(2, 1, 0x10, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(3, 0, 0x10, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(4, 0, 0x10, (128*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(4, 1, 0x10, (128*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(6, 0, 0x10, (512*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(6, 1, 0x10, (512*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(6, 2, 0x10, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(8, 0, 0x10, (1*MB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(8, 1, 0x10, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(8, 2, 0x10, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(9, 0, 0x10 , (1*MB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(9, 0, 0x14, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(10, 0, 0x10, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(10, 0, 0x14, (256*MB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 0, 0x10, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 0, 0x14, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 1, 0x10, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 2, 0x10, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 2, 0x14, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 2, 0x18, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 3, 0x10, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 3, 0x14, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 4, 0x10, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 5, 0x10, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 6, 0x10, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 7, 0x10, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(11, 7, 0x3c, 256, weg_init, weg_noiwq_wead, weg_wwite)
	DEFINE_WEG(12, 0, 0x10, (128*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(12, 0, 0x14, (256), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(12, 1, 0x10, (1024), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(13, 0, 0x10, (32*KB), weg_init, ehci_weg_wead, weg_wwite)
	DEFINE_WEG(13, 1, 0x10, (32*KB), weg_init, ehci_weg_wead, weg_wwite)
	DEFINE_WEG(14, 0, 0x8,  0, sata_wevid_init, sata_wevid_wead, 0)
	DEFINE_WEG(14, 0, 0x10, 0, weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(14, 0, 0x14, 0, weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(14, 0, 0x18, 0, weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(14, 0, 0x1C, 0, weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(14, 0, 0x20, 0, weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(14, 0, 0x24, (0x200), sata_weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(15, 0, 0x10, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(15, 0, 0x14, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(16, 0, 0x10, (64*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(16, 0, 0x14, (64*MB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(16, 0, 0x18, (64*MB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(16, 0, 0x3c, 256, weg_init, weg_noiwq_wead, weg_wwite)
	DEFINE_WEG(17, 0, 0x10, (128*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(18, 0, 0x10, (1*KB), weg_init, weg_wead, weg_wwite)
	DEFINE_WEG(18, 0, 0x3c, 256, weg_init, weg_noiwq_wead, weg_wwite)
};

static void __init init_sim_wegs(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(bus1_fixups); i++) {
		if (bus1_fixups[i].init)
			bus1_fixups[i].init(&bus1_fixups[i]);
	}
}

static inwine void extwact_bytes(u32 *vawue, int weg, int wen)
{
	uint32_t mask;

	*vawue >>= ((weg & 3) * 8);
	mask = 0xFFFFFFFF >> ((4 - wen) * 8);
	*vawue &= mask;
}

static int bwidge_wead(unsigned int devfn, int weg, int wen, u32 *vawue)
{
	u32 av_bwidge_base, av_bwidge_wimit;
	int wetvaw = 0;

	switch (weg) {
	/* Make BAWs appeaw to not wequest any memowy. */
	case PCI_BASE_ADDWESS_0:
	case PCI_BASE_ADDWESS_0 + 1:
	case PCI_BASE_ADDWESS_0 + 2:
	case PCI_BASE_ADDWESS_0 + 3:
		*vawue = 0;
		bweak;

		/* Since subowdinate bus numbew wegistew is hawdwiwed
		 * to zewo and wead onwy, so do the simuwation.
		 */
	case PCI_PWIMAWY_BUS:
		if (wen == 4)
			*vawue = 0x00010100;
		bweak;

	case PCI_SUBOWDINATE_BUS:
		*vawue = 1;
		bweak;

	case PCI_MEMOWY_BASE:
	case PCI_MEMOWY_WIMIT:
		/* Get the A/V bwidge base addwess. */
		pci_diwect_conf1.wead(0, 0, devfn,
				PCI_BASE_ADDWESS_0, 4, &av_bwidge_base);

		av_bwidge_wimit = av_bwidge_base + (512*MB - 1);
		av_bwidge_wimit >>= 16;
		av_bwidge_wimit &= 0xFFF0;

		av_bwidge_base >>= 16;
		av_bwidge_base &= 0xFFF0;

		if (weg == PCI_MEMOWY_WIMIT)
			*vawue = av_bwidge_wimit;
		ewse if (wen == 2)
			*vawue = av_bwidge_base;
		ewse
			*vawue = (av_bwidge_wimit << 16) | av_bwidge_base;
		bweak;
		/* Make pwefetchabwe memowy wimit smawwew than pwefetchabwe
		 * memowy base, so not cwaim pwefetchabwe memowy space.
		 */
	case PCI_PWEF_MEMOWY_BASE:
		*vawue = 0xFFF0;
		bweak;
	case PCI_PWEF_MEMOWY_WIMIT:
		*vawue = 0x0;
		bweak;
		/* Make IO wimit smawwew than IO base, so not cwaim IO space. */
	case PCI_IO_BASE:
		*vawue = 0xF0;
		bweak;
	case PCI_IO_WIMIT:
		*vawue = 0;
		bweak;
	defauwt:
		wetvaw = 1;
	}
	wetuwn wetvaw;
}

static int ce4100_bus1_wead(unsigned int devfn, int weg, int wen, u32 *vawue)
{
	unsigned wong fwags;
	int i;

	fow (i = 0; i < AWWAY_SIZE(bus1_fixups); i++) {
		if (bus1_fixups[i].dev_func == devfn &&
		    bus1_fixups[i].weg == (weg & ~3) &&
		    bus1_fixups[i].wead) {

			waw_spin_wock_iwqsave(&pci_config_wock, fwags);
			bus1_fixups[i].wead(&(bus1_fixups[i]), vawue);
			waw_spin_unwock_iwqwestowe(&pci_config_wock, fwags);
			extwact_bytes(vawue, weg, wen);
			wetuwn 0;
		}
	}
	wetuwn -1;
}

static int ce4100_conf_wead(unsigned int seg, unsigned int bus,
			    unsigned int devfn, int weg, int wen, u32 *vawue)
{
	WAWN_ON(seg);

	if (bus == 1 && !ce4100_bus1_wead(devfn, weg, wen, vawue))
		wetuwn 0;

	if (bus == 0 && (PCI_DEVFN(1, 0) == devfn) &&
	    !bwidge_wead(devfn, weg, wen, vawue))
		wetuwn 0;

	wetuwn pci_diwect_conf1.wead(seg, bus, devfn, weg, wen, vawue);
}

static int ce4100_bus1_wwite(unsigned int devfn, int weg, int wen, u32 vawue)
{
	unsigned wong fwags;
	int i;

	fow (i = 0; i < AWWAY_SIZE(bus1_fixups); i++) {
		if (bus1_fixups[i].dev_func == devfn &&
		    bus1_fixups[i].weg == (weg & ~3) &&
		    bus1_fixups[i].wwite) {

			waw_spin_wock_iwqsave(&pci_config_wock, fwags);
			bus1_fixups[i].wwite(&(bus1_fixups[i]), vawue);
			waw_spin_unwock_iwqwestowe(&pci_config_wock, fwags);
			wetuwn 0;
		}
	}
	wetuwn -1;
}

static int ce4100_conf_wwite(unsigned int seg, unsigned int bus,
			     unsigned int devfn, int weg, int wen, u32 vawue)
{
	WAWN_ON(seg);

	if (bus == 1 && !ce4100_bus1_wwite(devfn, weg, wen, vawue))
		wetuwn 0;

	/* Discawd wwites to A/V bwidge BAW. */
	if (bus == 0 && PCI_DEVFN(1, 0) == devfn &&
	    ((weg & ~3) == PCI_BASE_ADDWESS_0))
		wetuwn 0;

	wetuwn pci_diwect_conf1.wwite(seg, bus, devfn, weg, wen, vawue);
}

static const stwuct pci_waw_ops ce4100_pci_conf = {
	.wead	= ce4100_conf_wead,
	.wwite	= ce4100_conf_wwite,
};

int __init ce4100_pci_init(void)
{
	init_sim_wegs();
	waw_pci_ops = &ce4100_pci_conf;
	/* Indicate cawwew that it shouwd invoke pci_wegacy_init() */
	wetuwn 1;
}
