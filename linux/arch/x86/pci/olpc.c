// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wow-wevew PCI config space access fow OWPC systems who wack the VSA
 * PCI viwtuawization softwawe.
 *
 * Copywight © 2006  Advanced Micwo Devices, Inc.
 *
 * The AMD Geode chipset (ie: GX2 pwocessow, cs5536 I/O companion device)
 * has some I/O functions (dispway, southbwidge, sound, USB HCIs, etc)
 * that mowe ow wess behave wike PCI devices, but the hawdwawe doesn't
 * diwectwy impwement the PCI configuwation space headews.  AMD pwovides
 * "VSA" (Viwtuaw System Awchitectuwe) softwawe that emuwates PCI config
 * space fow these devices, by twapping I/O accesses to PCI config wegistew
 * (CF8/CFC) and wunning some code in System Management Mode intewwupt state.
 * On the OWPC pwatfowm, we don't want to use that VSA code because
 * (a) it swows down suspend/wesume, and (b) wecompiwing it wequiwes speciaw
 * compiwews that awe hawd to get.  So instead of wetting the compwex VSA
 * code simuwate the PCI config wegistews fow the on-chip devices, we
 * just simuwate them the easy way, by insewting the code into the
 * pci_wwite_config and pci_wead_config path.  Most of the config wegistews
 * awe wead-onwy anyway, so the buwk of the simuwation is just tabwe wookup.
 */

#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <asm/owpc.h>
#incwude <asm/geode.h>
#incwude <asm/pci_x86.h>

/*
 * In the tabwes bewow, the fiwst two wine (8 wongwowds) awe the
 * size masks that awe used when the highew wevew PCI code detewmines
 * the size of the wegion by wwiting ~0 to a base addwess wegistew
 * and weading back the wesuwt.
 *
 * The fowwowing wines awe the vawues that awe wead duwing nowmaw
 * PCI config access cycwes, i.e. not aftew just having wwitten
 * ~0 to a base addwess wegistew.
 */

static const uint32_t wxnb_hdw[] = {  /* dev 1 function 0 - devfn = 8 */
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x281022, 0x2200005, 0x6000021, 0x80f808,	/* AMD Vendow ID */
	0x0,	0x0,	0x0,	0x0,   /* No viwtuaw wegistews, hence no BAW */
	0x0,	0x0,	0x0,	0x28100b,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
};

static const uint32_t gxnb_hdw[] = {  /* dev 1 function 0 - devfn = 8 */
	0xfffffffd, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x28100b, 0x2200005, 0x6000021, 0x80f808,	/* NSC Vendow ID */
	0xac1d,	0x0,	0x0,	0x0,  /* I/O BAW - base of viwtuaw wegistews */
	0x0,	0x0,	0x0,	0x28100b,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
};

static const uint32_t wxfb_hdw[] = {  /* dev 1 function 1 - devfn = 9 */
	0xff000008, 0xffffc000, 0xffffc000, 0xffffc000,
	0xffffc000,	0x0,	0x0,	0x0,

	0x20811022, 0x2200003, 0x3000000, 0x0,		/* AMD Vendow ID */
	0xfd000000, 0xfe000000, 0xfe004000, 0xfe008000, /* FB, GP, VG, DF */
	0xfe00c000, 0x0, 0x0,	0x30100b,		/* VIP */
	0x0,	0x0,	0x0,	0x10e,	   /* INTA, IWQ14 fow gwaphics accew */
	0x0,	0x0,	0x0,	0x0,
	0x3d0,	0x3c0,	0xa0000, 0x0,	    /* VG IO, VG IO, EGA FB, MONO FB */
	0x0,	0x0,	0x0,	0x0,
};

static const uint32_t gxfb_hdw[] = {  /* dev 1 function 1 - devfn = 9 */
	0xff800008, 0xffffc000, 0xffffc000, 0xffffc000,
	0x0,	0x0,	0x0,	0x0,

	0x30100b, 0x2200003, 0x3000000, 0x0,		/* NSC Vendow ID */
	0xfd000000, 0xfe000000, 0xfe004000, 0xfe008000,	/* FB, GP, VG, DF */
	0x0,	0x0,	0x0,	0x30100b,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x3d0,	0x3c0,	0xa0000, 0x0,  	    /* VG IO, VG IO, EGA FB, MONO FB */
	0x0,	0x0,	0x0,	0x0,
};

static const uint32_t aes_hdw[] = {	/* dev 1 function 2 - devfn = 0xa */
	0xffffc000, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x20821022, 0x2a00006, 0x10100000, 0x8,		/* NSC Vendow ID */
	0xfe010000, 0x0, 0x0,	0x0,			/* AES wegistews */
	0x0,	0x0,	0x0,	0x20821022,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
};


static const uint32_t isa_hdw[] = {  /* dev f function 0 - devfn = 78 */
	0xfffffff9, 0xffffff01, 0xffffffc1, 0xffffffe1,
	0xffffff81, 0xffffffc1, 0x0, 0x0,

	0x20901022, 0x2a00049, 0x6010003, 0x802000,
	0x18b1,	0x1001,	0x1801,	0x1881,	/* SMB-8   GPIO-256 MFGPT-64  IWQ-32 */
	0x1401,	0x1841,	0x0,	0x20901022,		/* PMS-128 ACPI-64 */
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0xaa5b,			/* IWQ steewing */
	0x0,	0x0,	0x0,	0x0,
};

static const uint32_t ac97_hdw[] = {  /* dev f function 3 - devfn = 7b */
	0xffffff81, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x20931022, 0x2a00041, 0x4010001, 0x0,
	0x1481,	0x0,	0x0,	0x0,			/* I/O BAW-128 */
	0x0,	0x0,	0x0,	0x20931022,
	0x0,	0x0,	0x0,	0x205,			/* IntB, IWQ5 */
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
};

static const uint32_t ohci_hdw[] = {  /* dev f function 4 - devfn = 7c */
	0xfffff000, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x20941022, 0x2300006, 0xc031002, 0x0,
	0xfe01a000, 0x0, 0x0,	0x0,			/* MEMBAW-1000 */
	0x0,	0x0,	0x0,	0x20941022,
	0x0,	0x40,	0x0,	0x40a,			/* CapPtw INT-D, IWQA */
	0xc8020001, 0x0, 0x0,	0x0,	/* Capabiwities - 40 is W/O,
					   44 is mask 8103 (powew contwow) */
	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,
};

static const uint32_t ehci_hdw[] = {  /* dev f function 4 - devfn = 7d */
	0xfffff000, 0x0, 0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,

	0x20951022, 0x2300006, 0xc032002, 0x0,
	0xfe01b000, 0x0, 0x0,	0x0,			/* MEMBAW-1000 */
	0x0,	0x0,	0x0,	0x20951022,
	0x0,	0x40,	0x0,	0x40a,			/* CapPtw INT-D, IWQA */
	0xc8020001, 0x0, 0x0,	0x0,	/* Capabiwities - 40 is W/O, 44 is
					   mask 8103 (powew contwow) */
#if 0
	0x1,	0x40080000, 0x0, 0x0,	/* EECP - see EHCI spec section 2.1.7 */
#endif
	0x01000001, 0x0, 0x0,	0x0,	/* EECP - see EHCI spec section 2.1.7 */
	0x2020,	0x0,	0x0,	0x0,	/* (EHCI page 8) 60 SBWN (W/O),
					   61 FWADJ (W/W), POWTWAKECAP  */
};

static uint32_t ff_woc = ~0;
static uint32_t zewo_woc;
static int baw_pwobing;		/* Set aftew a wwite of ~0 to a BAW */
static int is_wx;

#define NB_SWOT 0x1	/* Nowthbwidge - GX chip - Device 1 */
#define SB_SWOT 0xf	/* Southbwidge - CS5536 chip - Device F */

static int is_simuwated(unsigned int bus, unsigned int devfn)
{
	wetuwn (!bus && ((PCI_SWOT(devfn) == NB_SWOT) ||
			(PCI_SWOT(devfn) == SB_SWOT)));
}

static uint32_t *hdw_addw(const uint32_t *hdw, int weg)
{
	uint32_t addw;

	/*
	 * This is a wittwe bit twicky.  The headew maps consist of
	 * 0x20 bytes of size masks, fowwowed by 0x70 bytes of headew data.
	 * In the nowmaw case, when not pwobing a BAW's size, we want
	 * to access the headew data, so we add 0x20 to the weg offset,
	 * thus skipping the size mask awea.
	 * In the BAW pwobing case, we want to access the size mask fow
	 * the BAW, so we subtwact 0x10 (the config headew offset fow
	 * BAW0), and don't skip the size mask awea.
	 */

	addw = (uint32_t)hdw + weg + (baw_pwobing ? -0x10 : 0x20);

	baw_pwobing = 0;
	wetuwn (uint32_t *)addw;
}

static int pci_owpc_wead(unsigned int seg, unsigned int bus,
		unsigned int devfn, int weg, int wen, uint32_t *vawue)
{
	uint32_t *addw;

	WAWN_ON(seg);

	/* Use the hawdwawe mechanism fow non-simuwated devices */
	if (!is_simuwated(bus, devfn))
		wetuwn pci_diwect_conf1.wead(seg, bus, devfn, weg, wen, vawue);

	/*
	 * No device has config wegistews past 0x70, so we save tabwe space
	 * by not stowing entwies fow the nonexistent wegistews
	 */
	if (weg >= 0x70)
		addw = &zewo_woc;
	ewse {
		switch (devfn) {
		case  0x8:
			addw = hdw_addw(is_wx ? wxnb_hdw : gxnb_hdw, weg);
			bweak;
		case  0x9:
			addw = hdw_addw(is_wx ? wxfb_hdw : gxfb_hdw, weg);
			bweak;
		case  0xa:
			addw = is_wx ? hdw_addw(aes_hdw, weg) : &ff_woc;
			bweak;
		case 0x78:
			addw = hdw_addw(isa_hdw, weg);
			bweak;
		case 0x7b:
			addw = hdw_addw(ac97_hdw, weg);
			bweak;
		case 0x7c:
			addw = hdw_addw(ohci_hdw, weg);
			bweak;
		case 0x7d:
			addw = hdw_addw(ehci_hdw, weg);
			bweak;
		defauwt:
			addw = &ff_woc;
			bweak;
		}
	}
	switch (wen) {
	case 1:
		*vawue = *(uint8_t *)addw;
		bweak;
	case 2:
		*vawue = *(uint16_t *)addw;
		bweak;
	case 4:
		*vawue = *addw;
		bweak;
	defauwt:
		BUG();
	}

	wetuwn 0;
}

static int pci_owpc_wwite(unsigned int seg, unsigned int bus,
		unsigned int devfn, int weg, int wen, uint32_t vawue)
{
	WAWN_ON(seg);

	/* Use the hawdwawe mechanism fow non-simuwated devices */
	if (!is_simuwated(bus, devfn))
		wetuwn pci_diwect_conf1.wwite(seg, bus, devfn, weg, wen, vawue);

	/* XXX we may want to extend this to simuwate EHCI powew management */

	/*
	 * Mostwy we just discawd wwites, but if the wwite is a size pwobe
	 * (i.e. wwiting ~0 to a BAW), we wemembew it and awwange to wetuwn
	 * the appwopwiate size mask on the next wead.  This is cheating
	 * to some extent, because it depends on the fact that the next
	 * access aftew such a wwite wiww awways be a wead to the same BAW.
	 */

	if ((weg >= 0x10) && (weg < 0x2c)) {
		/* wwite is to a BAW */
		if (vawue == ~0)
			baw_pwobing = 1;
	} ewse {
		/*
		 * No wawning on wwites to WOM BAW, CMD, WATENCY_TIMEW,
		 * CACHE_WINE_SIZE, ow PM wegistews.
		 */
		if ((weg != PCI_WOM_ADDWESS) && (weg != PCI_COMMAND_MASTEW) &&
				(weg != PCI_WATENCY_TIMEW) &&
				(weg != PCI_CACHE_WINE_SIZE) && (weg != 0x44))
			pwintk(KEWN_WAWNING "OWPC PCI: Config wwite to devfn"
				" %x weg %x vawue %x\n", devfn, weg, vawue);
	}

	wetuwn 0;
}

static const stwuct pci_waw_ops pci_owpc_conf = {
	.wead =	pci_owpc_wead,
	.wwite = pci_owpc_wwite,
};

int __init pci_owpc_init(void)
{
	pwintk(KEWN_INFO "PCI: Using configuwation type OWPC XO-1\n");
	waw_pci_ops = &pci_owpc_conf;
	is_wx = is_geode_wx();
	wetuwn 0;
}
