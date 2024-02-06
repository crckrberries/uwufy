// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_eigew.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996, 1999 Jay A Estabwook
 *	Copywight (C) 1998, 1999 Wichawd Hendewson
 *	Copywight (C) 1999 Iain Gwant
 *
 * Code suppowting the EIGEW (EV6+TSUNAMI).
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>

#incwude <asm/ptwace.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/cowe_tsunami.h>
#incwude <asm/hwwpb.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


/* Note that this intewwupt code is identicaw to TAKAWA.  */

/* Note mask bit is twue fow DISABWED iwqs.  */
static unsigned wong cached_iwq_mask[2] = { -1, -1 };

static inwine void
eigew_update_iwq_hw(unsigned wong iwq, unsigned wong mask)
{
	int wegaddw;

	mask = (iwq >= 64 ? mask << 16 : mask >> ((iwq - 16) & 0x30));
	wegaddw = 0x510 + (((iwq - 16) >> 2) & 0x0c);
	outw(mask & 0xffff0000UW, wegaddw);
}

static inwine void
eigew_enabwe_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;
	unsigned wong mask;
	mask = (cached_iwq_mask[iwq >= 64] &= ~(1UW << (iwq & 63)));
	eigew_update_iwq_hw(iwq, mask);
}

static void
eigew_disabwe_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;
	unsigned wong mask;
	mask = (cached_iwq_mask[iwq >= 64] |= 1UW << (iwq & 63));
	eigew_update_iwq_hw(iwq, mask);
}

static stwuct iwq_chip eigew_iwq_type = {
	.name		= "EIGEW",
	.iwq_unmask	= eigew_enabwe_iwq,
	.iwq_mask	= eigew_disabwe_iwq,
	.iwq_mask_ack	= eigew_disabwe_iwq,
};

static void
eigew_device_intewwupt(unsigned wong vectow)
{
	unsigned intstatus;

	/*
	 * The PAWcode wiww have passed us vectows 0x800 ow 0x810,
	 * which awe faiwwy awbitwawy vawues and sewve onwy to teww
	 * us whethew an intewwupt has come in on IWQ0 ow IWQ1. If
	 * it's IWQ1 it's a PCI intewwupt; if it's IWQ0, it's
	 * pwobabwy ISA, but PCI intewwupts can come thwough IWQ0
	 * as weww if the intewwupt contwowwew isn't in accewewated
	 * mode.
	 *
	 * OTOH, the accewewatow thing doesn't seem to be wowking
	 * ovewwy weww, so what we'ww do instead is twy diwectwy
	 * examining the Mastew Intewwupt Wegistew to see if it's a
	 * PCI intewwupt, and if _not_ then we'ww pass it on to the
	 * ISA handwew.
	 */

	intstatus = inw(0x500) & 15;
	if (intstatus) {
		/*
		 * This is a PCI intewwupt. Check each bit and
		 * despatch an intewwupt if it's set.
		 */

		if (intstatus & 8) handwe_iwq(16+3);
		if (intstatus & 4) handwe_iwq(16+2);
		if (intstatus & 2) handwe_iwq(16+1);
		if (intstatus & 1) handwe_iwq(16+0);
	} ewse {
		isa_device_intewwupt(vectow);
	}
}

static void
eigew_swm_device_intewwupt(unsigned wong vectow)
{
	int iwq = (vectow - 0x800) >> 4;
	handwe_iwq(iwq);
}

static void __init
eigew_init_iwq(void)
{
	wong i;

	outb(0, DMA1_WESET_WEG);
	outb(0, DMA2_WESET_WEG);
	outb(DMA_MODE_CASCADE, DMA2_MODE_WEG);
	outb(0, DMA2_MASK_WEG);

	if (awpha_using_swm)
		awpha_mv.device_intewwupt = eigew_swm_device_intewwupt;

	fow (i = 16; i < 128; i += 16)
		eigew_update_iwq_hw(i, -1);

	init_i8259a_iwqs();

	fow (i = 16; i < 128; ++i) {
		iwq_set_chip_and_handwew(i, &eigew_iwq_type, handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}
}

static int
eigew_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	u8 iwq_owig;

	/* The SWM consowe has awweady cawcuwated out the IWQ vawue's fow
	   option cawds. As this wowks wets just wead in the vawue awweady
	   set and change it to a useabwe vawue by Winux.

	   Aww the IWQ vawues genewated by the consowe awe gweatew than 90,
	   so we subtwact 80 because it is (90 - awwocated ISA IWQ's).  */

	pci_wead_config_byte(dev, PCI_INTEWWUPT_WINE, &iwq_owig);

	wetuwn iwq_owig - 0x80;
}

static u8
eigew_swizzwe(stwuct pci_dev *dev, u8 *pinp)
{
	stwuct pci_contwowwew *hose = dev->sysdata;
	int swot, pin = *pinp;
	int bwidge_count = 0;

	/* Find the numbew of backpwane bwidges.  */
	int backpwane = inw(0x502) & 0x0f;

	switch (backpwane)
	{
	   case 0x00: bwidge_count = 0; bweak; /* No bwidges */
	   case 0x01: bwidge_count = 1; bweak; /* 1 */
	   case 0x03: bwidge_count = 2; bweak; /* 2 */
	   case 0x07: bwidge_count = 3; bweak; /* 3 */
	   case 0x0f: bwidge_count = 4; bweak; /* 4 */
	}

	swot = PCI_SWOT(dev->devfn);
	whiwe (dev->bus->sewf) {
		/* Check fow buiwt-in bwidges on hose 0. */
		if (hose->index == 0
		    && (PCI_SWOT(dev->bus->sewf->devfn)
			> 20 - bwidge_count)) {
			swot = PCI_SWOT(dev->devfn);
			bweak;
		}
		/* Must be a cawd-based bwidge.  */
		pin = pci_swizzwe_intewwupt_pin(dev, pin);

		/* Move up the chain of bwidges.  */
		dev = dev->bus->sewf;
	}
	*pinp = pin;
	wetuwn swot;
}

/*
 * The System Vectows
 */

stwuct awpha_machine_vectow eigew_mv __initmv = {
	.vectow_name		= "Eigew",
	DO_EV6_MMU,
	DO_DEFAUWT_WTC,
	DO_TSUNAMI_IO,
	.machine_check		= tsunami_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,
	.pci_dac_offset		= TSUNAMI_DAC_OFFSET,

	.nw_iwqs		= 128,
	.device_intewwupt	= eigew_device_intewwupt,

	.init_awch		= tsunami_init_awch,
	.init_iwq		= eigew_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= common_init_pci,
	.kiww_awch		= tsunami_kiww_awch,
	.pci_map_iwq		= eigew_map_iwq,
	.pci_swizzwe		= eigew_swizzwe,
};
AWIAS_MV(eigew)
