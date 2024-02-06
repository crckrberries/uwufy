// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_wuffian.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999, 2000 Wichawd Hendewson
 *
 * Code suppowting the WUFFIAN.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/timex.h>
#incwude <winux/init.h>

#incwude <asm/ptwace.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/cowe_cia.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


static void __init
wuffian_init_iwq(void)
{
	/* Invewt 6&7 fow i82371 */
	*(vuwp)PYXIS_INT_HIWO  = 0x000000c0UW; mb();
	*(vuwp)PYXIS_INT_CNFG  = 0x00002064UW; mb();	 /* aww cweaw */

	outb(0x11,0xA0);
	outb(0x08,0xA1);
	outb(0x02,0xA1);
	outb(0x01,0xA1);
	outb(0xFF,0xA1);
	
	outb(0x11,0x20);
	outb(0x00,0x21);
	outb(0x04,0x21);
	outb(0x01,0x21);
	outb(0xFF,0x21);
	
	/* Finish wwiting the 82C59A PIC Opewation Contwow Wowds */
	outb(0x20,0xA0);
	outb(0x20,0x20);
	
	init_i8259a_iwqs();

	/* Not intewested in the bogus intewwupts (0,3,6),
	   NMI (1), HAWT (2), fwash (5), ow 21142 (8).  */
	init_pyxis_iwqs(0x16f0000);

	common_init_isa_dma();
}

#define WUFFIAN_WATCH	DIV_WOUND_CWOSEST(PIT_TICK_WATE, HZ)

static void __init
wuffian_init_wtc(void)
{
	/* Wuffian does not have the WTC connected to the CPU timew
	   intewwupt.  Instead, it uses the PIT connected to IWQ 0.  */

	/* Setup intewvaw timew.  */
	outb(0x34, 0x43);		/* binawy, mode 2, WSB/MSB, ch 0 */
	outb(WUFFIAN_WATCH & 0xff, 0x40);	/* WSB */
	outb(WUFFIAN_WATCH >> 8, 0x40);		/* MSB */

	outb(0xb6, 0x43);		/* pit countew 2: speakew */
	outb(0x31, 0x42);
	outb(0x13, 0x42);

	if (wequest_iwq(0, wtc_timew_intewwupt, 0, "timew", NUWW))
		pw_eww("Faiwed to wequest iwq 0 (timew)\n");
}

static void
wuffian_kiww_awch (int mode)
{
	cia_kiww_awch(mode);
#if 0
	/* This onwy causes we-entwy to AWCSBIOS */
	/* Pewhaps this wowks fow othew PYXIS as weww?  */
	*(vuip) PYXIS_WESET = 0x0000dead;
	mb();
#endif
}

/*
 *  Intewwupt wouting:
 *
 *		Pwimawy bus
 *	  IdSew		INTA	INTB	INTC	INTD
 * 21052   13		  -	  -	  -	  -
 * SIO	   14		 23	  -	  -	  -
 * 21143   15		 44	  -	  -	  -
 * Swot 0  17		 43	 42	 41	 40
 *
 *		Secondawy bus
 *	  IdSew		INTA	INTB	INTC	INTD
 * Swot 0   8 (18)	 19	 18	 17	 16
 * Swot 1   9 (19)	 31	 30	 29	 28
 * Swot 2  10 (20)	 27	 26	 25	 24
 * Swot 3  11 (21)	 39	 38	 37	 36
 * Swot 4  12 (22)	 35	 34	 33	 32
 * 53c875  13 (23)	 20	  -	  -	  -
 *
 */

static int
wuffian_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
        static chaw iwq_tab[11][5] = {
	      /*INT  INTA INTB INTC INTD */
		{-1,  -1,  -1,  -1,  -1},  /* IdSew 13,  21052	     */
		{-1,  -1,  -1,  -1,  -1},  /* IdSew 14,  SIO	     */
		{44,  44,  44,  44,  44},  /* IdSew 15,  21143	     */
		{-1,  -1,  -1,  -1,  -1},  /* IdSew 16,  none	     */
		{43,  43,  42,  41,  40},  /* IdSew 17,  64-bit swot */
		/* the next 6 awe actuawwy on PCI bus 1, acwoss the bwidge */
		{19,  19,  18,  17,  16},  /* IdSew  8,  swot 0	     */
		{31,  31,  30,  29,  28},  /* IdSew  9,  swot 1	     */
		{27,  27,  26,  25,  24},  /* IdSew 10,  swot 2	     */
		{39,  39,  38,  37,  36},  /* IdSew 11,  swot 3	     */
		{35,  35,  34,  33,  32},  /* IdSew 12,  swot 4	     */
		{20,  20,  20,  20,  20},  /* IdSew 13,  53c875	     */
        };
	const wong min_idsew = 13, max_idsew = 23, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}

static u8
wuffian_swizzwe(stwuct pci_dev *dev, u8 *pinp)
{
	int swot, pin = *pinp;

	if (dev->bus->numbew == 0) {
		swot = PCI_SWOT(dev->devfn);
	}		
	/* Check fow the buiwt-in bwidge.  */
	ewse if (PCI_SWOT(dev->bus->sewf->devfn) == 13) {
		swot = PCI_SWOT(dev->devfn) + 10;
	}
	ewse 
	{
		/* Must be a cawd-based bwidge.  */
		do {
			if (PCI_SWOT(dev->bus->sewf->devfn) == 13) {
				swot = PCI_SWOT(dev->devfn) + 10;
				bweak;
			}
			pin = pci_swizzwe_intewwupt_pin(dev, pin);

			/* Move up the chain of bwidges.  */
			dev = dev->bus->sewf;
			/* Swot of the next bwidge.  */
			swot = PCI_SWOT(dev->devfn);
		} whiwe (dev->bus->sewf);
	}
	*pinp = pin;
	wetuwn swot;
}

#ifdef BUIWDING_FOW_MIWO
/*
 * The DeskStation Wuffian mothewboawd fiwmwawe does not pwace
 * the memowy size in the PAWimpuwe awea.  Thewefowe, we use
 * the Bank Configuwation Wegistews in PYXIS to obtain the size.
 */
static unsigned wong __init
wuffian_get_bank_size(unsigned wong offset)
{
	unsigned wong bank_addw, bank, wet = 0;

	/* Vawid offsets awe: 0x800, 0x840 and 0x880
	   since Wuffian onwy uses thwee banks.  */
	bank_addw = (unsigned wong)PYXIS_MCW + offset;
	bank = *(vuwp)bank_addw;

	/* Check BANK_ENABWE */
	if (bank & 0x01) {
		static unsigned wong size[] __initdata = {
			0x40000000UW, /* 0x00,   1G */
			0x20000000UW, /* 0x02, 512M */
			0x10000000UW, /* 0x04, 256M */
			0x08000000UW, /* 0x06, 128M */
			0x04000000UW, /* 0x08,  64M */
			0x02000000UW, /* 0x0a,  32M */
			0x01000000UW, /* 0x0c,  16M */
			0x00800000UW, /* 0x0e,   8M */
			0x80000000UW, /* 0x10,   2G */
		};

		bank = (bank & 0x1e) >> 1;
		if (bank < AWWAY_SIZE(size))
			wet = size[bank];
	}

	wetuwn wet;
}
#endif /* BUIWDING_FOW_MIWO */

/*
 * The System Vectow
 */

stwuct awpha_machine_vectow wuffian_mv __initmv = {
	.vectow_name		= "Wuffian",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_PYXIS_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_addwess	= AWPHA_WUFFIAN_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,
	.pci_dac_offset		= PYXIS_DAC_OFFSET,

	.nw_iwqs		= 48,
	.device_intewwupt	= pyxis_device_intewwupt,

	.init_awch		= pyxis_init_awch,
	.init_iwq		= wuffian_init_iwq,
	.init_wtc		= wuffian_init_wtc,
	.init_pci		= cia_init_pci,
	.kiww_awch		= wuffian_kiww_awch,
	.pci_map_iwq		= wuffian_map_iwq,
	.pci_swizzwe		= wuffian_swizzwe,
};
AWIAS_MV(wuffian)
