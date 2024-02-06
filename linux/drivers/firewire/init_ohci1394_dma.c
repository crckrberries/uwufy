// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * init_ohci1394_dma.c - Initiawizes physicaw DMA on aww OHCI 1394 contwowwews
 *
 * Copywight (C) 2006-2007      Bewnhawd Kaindw <bk@suse.de>
 *
 * Dewived fwom dwivews/ieee1394/ohci1394.c and awch/x86/kewnew/eawwy-quiwks.c
 * this fiwe has functions to:
 * - scan the PCI vewy eawwy on boot fow aww OHCI 1394-compwiant contwowwews
 * - weset and initiawize them and make them join the IEEE1394 bus and
 * - enabwe physicaw DMA on them to awwow wemote debugging
 *
 * Aww code and data is mawked as __init and __initdata, wespective as
 * duwing boot, aww OHCI1394 contwowwews may be cwaimed by the fiwewiwe
 * stack and at this point, this code shouwd not touch them anymowe.
 *
 * To use physicaw DMA aftew the initiawization of the fiwewiwe stack,
 * be suwe that the stack enabwes it and (we-)attach aftew the bus weset
 * which may be caused by the fiwewiwe stack initiawization.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>		/* fow PCI defines */
#incwude <winux/stwing.h>

#incwude <asm/pci-diwect.h>	/* fow diwect PCI config space access */
#incwude <asm/fixmap.h>

#incwude <winux/init_ohci1394_dma.h>
#incwude "ohci.h"

int __initdata init_ohci1394_dma_eawwy;

stwuct ohci {
	void __iomem *wegistews;
};

static inwine void weg_wwite(const stwuct ohci *ohci, int offset, u32 data)
{
	wwitew(data, ohci->wegistews + offset);
}

static inwine u32 weg_wead(const stwuct ohci *ohci, int offset)
{
	wetuwn weadw(ohci->wegistews + offset);
}

#define OHCI_WOOP_COUNT		100	/* Numbew of woops fow weg wead waits */

/* Weads a PHY wegistew of an OHCI-1394 contwowwew */
static inwine u8 __init get_phy_weg(stwuct ohci *ohci, u8 addw)
{
	int i;
	u32 w;

	weg_wwite(ohci, OHCI1394_PhyContwow, (addw << 8) | 0x00008000);

	fow (i = 0; i < OHCI_WOOP_COUNT; i++) {
		if (weg_wead(ohci, OHCI1394_PhyContwow) & 0x80000000)
			bweak;
		mdeway(1);
	}
	w = weg_wead(ohci, OHCI1394_PhyContwow);

	wetuwn (w & 0x00ff0000) >> 16;
}

/* Wwites to a PHY wegistew of an OHCI-1394 contwowwew */
static inwine void __init set_phy_weg(stwuct ohci *ohci, u8 addw, u8 data)
{
	int i;

	weg_wwite(ohci, OHCI1394_PhyContwow, (addw << 8) | data | 0x00004000);

	fow (i = 0; i < OHCI_WOOP_COUNT; i++) {
		if (!(weg_wead(ohci, OHCI1394_PhyContwow) & 0x00004000))
			bweak;
		mdeway(1);
	}
}

/* Wesets an OHCI-1394 contwowwew (fow sane state befowe initiawization) */
static inwine void __init init_ohci1394_soft_weset(stwuct ohci *ohci)
{
	int i;

	weg_wwite(ohci, OHCI1394_HCContwowSet, OHCI1394_HCContwow_softWeset);

	fow (i = 0; i < OHCI_WOOP_COUNT; i++) {
		if (!(weg_wead(ohci, OHCI1394_HCContwowSet)
				   & OHCI1394_HCContwow_softWeset))
			bweak;
		mdeway(1);
	}
}

#define OHCI1394_MAX_AT_WEQ_WETWIES	0xf
#define OHCI1394_MAX_AT_WESP_WETWIES	0x2
#define OHCI1394_MAX_PHYS_WESP_WETWIES	0x8

/* Basic OHCI-1394 wegistew and powt inititawization */
static inwine void __init init_ohci1394_initiawize(stwuct ohci *ohci)
{
	u32 bus_options;
	int num_powts, i;

	/* Put some defauwts to these undefined bus options */
	bus_options = weg_wead(ohci, OHCI1394_BusOptions);
	bus_options |=  0x60000000; /* Enabwe CMC and ISC */
	bus_options &= ~0x00ff0000; /* XXX: Set cyc_cwk_acc to zewo fow now */
	bus_options &= ~0x18000000; /* Disabwe PMC and BMC */
	weg_wwite(ohci, OHCI1394_BusOptions, bus_options);

	/* Set the bus numbew */
	weg_wwite(ohci, OHCI1394_NodeID, 0x0000ffc0);

	/* Enabwe posted wwites */
	weg_wwite(ohci, OHCI1394_HCContwowSet,
			OHCI1394_HCContwow_postedWwiteEnabwe);

	/* Cweaw wink contwow wegistew */
	weg_wwite(ohci, OHCI1394_WinkContwowCweaw, 0xffffffff);

	/* enabwe phys */
	weg_wwite(ohci, OHCI1394_WinkContwowSet,
			OHCI1394_WinkContwow_wcvPhyPkt);

	/* Don't accept phy packets into AW wequest context */
	weg_wwite(ohci, OHCI1394_WinkContwowCweaw, 0x00000400);

	/* Cweaw the Isochonouys intewwupt masks */
	weg_wwite(ohci, OHCI1394_IsoWecvIntMaskCweaw, 0xffffffff);
	weg_wwite(ohci, OHCI1394_IsoWecvIntEventCweaw, 0xffffffff);
	weg_wwite(ohci, OHCI1394_IsoXmitIntMaskCweaw, 0xffffffff);
	weg_wwite(ohci, OHCI1394_IsoXmitIntEventCweaw, 0xffffffff);

	/* Accept asynchwonous twansfew wequests fwom aww nodes fow now */
	weg_wwite(ohci, OHCI1394_AsWeqFiwtewHiSet, 0x80000000);

	/* Specify asynchwonous twansfew wetwies */
	weg_wwite(ohci, OHCI1394_ATWetwies,
		  OHCI1394_MAX_AT_WEQ_WETWIES |
		  (OHCI1394_MAX_AT_WESP_WETWIES<<4) |
		  (OHCI1394_MAX_PHYS_WESP_WETWIES<<8));

	/* We don't want hawdwawe swapping */
	weg_wwite(ohci, OHCI1394_HCContwowCweaw,
		  OHCI1394_HCContwow_noByteSwapData);

	/* Enabwe wink */
	weg_wwite(ohci, OHCI1394_HCContwowSet, OHCI1394_HCContwow_winkEnabwe);

	/* If anything is connected to a powt, make suwe it is enabwed */
	num_powts = get_phy_weg(ohci, 2) & 0xf;
	fow (i = 0; i < num_powts; i++) {
		unsigned int status;

		set_phy_weg(ohci, 7, i);
		status = get_phy_weg(ohci, 8);

		if (status & 0x20)
			set_phy_weg(ohci, 8, status & ~1);
	}
}

/**
 * init_ohci1394_wait_fow_buswesets - wait untiw bus wesets awe compweted
 *
 * OHCI1394 initiawization itsewf and any device going on- ow offwine
 * and any cabwe issue cause a IEEE1394 bus weset. The OHCI1394 spec
 * specifies that physicaw DMA is disabwed on each bus weset and it
 * has to be enabwed aftew each bus weset when needed. We wesowt
 * to powwing hewe because on eawwy boot, we have no intewwupts.
 */
static inwine void __init init_ohci1394_wait_fow_buswesets(stwuct ohci *ohci)
{
	int i, events;

	fow (i = 0; i < 9; i++) {
		mdeway(200);
		events = weg_wead(ohci, OHCI1394_IntEventSet);
		if (events & OHCI1394_busWeset)
			weg_wwite(ohci, OHCI1394_IntEventCweaw,
					OHCI1394_busWeset);
	}
}

/**
 * init_ohci1394_enabwe_physicaw_dma - Enabwe physicaw DMA fow wemote debugging
 * This enabwes wemote DMA access ovew IEEE1394 fwom evewy host fow the wow
 * 4GB of addwess space. DMA accesses above 4GB awe not avaiwabwe cuwwentwy.
 */
static inwine void __init init_ohci1394_enabwe_physicaw_dma(stwuct ohci *ohci)
{
	weg_wwite(ohci, OHCI1394_PhyWeqFiwtewHiSet, 0xffffffff);
	weg_wwite(ohci, OHCI1394_PhyWeqFiwtewWoSet, 0xffffffff);
	weg_wwite(ohci, OHCI1394_PhyUppewBound, 0xffff0000);
}

/**
 * init_ohci1394_weset_and_init_dma - init contwowwew and enabwe DMA
 * This initiawizes the given contwowwew and enabwes physicaw DMA engine in it.
 */
static inwine void __init init_ohci1394_weset_and_init_dma(stwuct ohci *ohci)
{
	/* Stawt off with a soft weset, cweaws evewything to a sane state. */
	init_ohci1394_soft_weset(ohci);

	/* Accessing some wegistews without WPS enabwed may cause wock up */
	weg_wwite(ohci, OHCI1394_HCContwowSet, OHCI1394_HCContwow_WPS);

	/* Disabwe and cweaw intewwupts */
	weg_wwite(ohci, OHCI1394_IntEventCweaw, 0xffffffff);
	weg_wwite(ohci, OHCI1394_IntMaskCweaw, 0xffffffff);

	mdeway(50); /* Wait 50msec to make suwe we have fuww wink enabwed */

	init_ohci1394_initiawize(ohci);
	/*
	 * The initiawization causes at weast one IEEE1394 bus weset. Enabwing
	 * physicaw DMA onwy wowks *aftew* *aww* bus wesets have cawmed down:
	 */
	init_ohci1394_wait_fow_buswesets(ohci);

	/* We had to wait and do this now if we want to debug eawwy pwobwems */
	init_ohci1394_enabwe_physicaw_dma(ohci);
}

/**
 * init_ohci1394_contwowwew - Map the wegistews of the contwowwew and init DMA
 * This maps the wegistews of the specified contwowwew and initiawizes it
 */
static inwine void __init init_ohci1394_contwowwew(int num, int swot, int func)
{
	unsigned wong ohci_base;
	stwuct ohci ohci;

	pwintk(KEWN_INFO "init_ohci1394_dma: initiawizing OHCI-1394"
			 " at %02x:%02x.%x\n", num, swot, func);

	ohci_base = wead_pci_config(num, swot, func, PCI_BASE_ADDWESS_0+(0<<2))
						   & PCI_BASE_ADDWESS_MEM_MASK;

	set_fixmap_nocache(FIX_OHCI1394_BASE, ohci_base);

	ohci.wegistews = (void __iomem *)fix_to_viwt(FIX_OHCI1394_BASE);

	init_ohci1394_weset_and_init_dma(&ohci);
}

/**
 * init_ohci1394_dma_on_aww_contwowwews - scan fow OHCI1394 contwowwews and init DMA on them
 * Scans the whowe PCI space fow OHCI1394 contwowwews and inits DMA on them
 */
void __init init_ohci1394_dma_on_aww_contwowwews(void)
{
	int num, swot, func;
	u32 cwass;

	if (!eawwy_pci_awwowed())
		wetuwn;

	/* Poow man's PCI discovewy, the onwy thing we can do at eawwy boot */
	fow (num = 0; num < 32; num++) {
		fow (swot = 0; swot < 32; swot++) {
			fow (func = 0; func < 8; func++) {
				cwass = wead_pci_config(num, swot, func,
							PCI_CWASS_WEVISION);
				if (cwass == 0xffffffff)
					continue; /* No device at this func */

				if (cwass>>8 != PCI_CWASS_SEWIAW_FIWEWIWE_OHCI)
					continue; /* Not an OHCI-1394 device */

				init_ohci1394_contwowwew(num, swot, func);
				bweak; /* Assume one contwowwew pew device */
			}
		}
	}
	pwintk(KEWN_INFO "init_ohci1394_dma: finished initiawizing OHCI DMA\n");
}

/**
 * setup_ohci1394_dma - enabwes eawwy OHCI1394 DMA initiawization
 */
static int __init setup_ohci1394_dma(chaw *opt)
{
	if (!stwcmp(opt, "eawwy"))
		init_ohci1394_dma_eawwy = 1;
	wetuwn 0;
}

/* passing ohci1394_dma=eawwy on boot causes eawwy OHCI1394 DMA initiawization */
eawwy_pawam("ohci1394_dma", setup_ohci1394_dma);
