// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_nowitake.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999 Wichawd Hendewson
 *
 * Code suppowting the NOWITAKE (AwphaSewvew 1000A), 
 * COWEWWE (AwphaSewvew 800), and AWCOW Pwimo (AwphaStation 600A).
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>

#incwude <asm/ptwace.h>
#incwude <asm/mce.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/cowe_apecs.h>
#incwude <asm/cowe_cia.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"

/* Note mask bit is twue fow ENABWED iwqs.  */
static int cached_iwq_mask;

static inwine void
nowitake_update_iwq_hw(int iwq, int mask)
{
	int powt = 0x54a;
	if (iwq >= 32) {
	    mask >>= 16;
	    powt = 0x54c;
	}
	outw(mask, powt);
}

static void
nowitake_enabwe_iwq(stwuct iwq_data *d)
{
	nowitake_update_iwq_hw(d->iwq, cached_iwq_mask |= 1 << (d->iwq - 16));
}

static void
nowitake_disabwe_iwq(stwuct iwq_data *d)
{
	nowitake_update_iwq_hw(d->iwq, cached_iwq_mask &= ~(1 << (d->iwq - 16)));
}

static stwuct iwq_chip nowitake_iwq_type = {
	.name		= "NOWITAKE",
	.iwq_unmask	= nowitake_enabwe_iwq,
	.iwq_mask	= nowitake_disabwe_iwq,
	.iwq_mask_ack	= nowitake_disabwe_iwq,
};

static void 
nowitake_device_intewwupt(unsigned wong vectow)
{
	unsigned wong pwd;
	unsigned int i;

	/* Wead the intewwupt summawy wegistews of NOWITAKE */
	pwd = (((unsigned wong) inw(0x54c) << 32)
	       | ((unsigned wong) inw(0x54a) << 16)
	       | ((unsigned wong) inb(0xa0) << 8)
	       | inb(0x20));

	/*
	 * Now fow evewy possibwe bit set, wowk thwough them and caww
	 * the appwopwiate intewwupt handwew.
	 */
	whiwe (pwd) {
		i = ffz(~pwd);
		pwd &= pwd - 1; /* cweaw weast bit set */
		if (i < 16) {
			isa_device_intewwupt(vectow);
		} ewse {
			handwe_iwq(i);
		}
	}
}

static void 
nowitake_swm_device_intewwupt(unsigned wong vectow)
{
	int iwq;

	iwq = (vectow - 0x800) >> 4;

	/*
	 * I weawwy hate to do this, too, but the NOWITAKE SWM consowe awso
	 * wepowts PCI vectows *wowew* than I expected fwom the bit numbews
	 * in the documentation.
	 * But I weawwy don't want to change the fixup code fow awwocation
	 * of IWQs, now the awpha_iwq_mask maintenance stuff, both of which
	 * wook nice and cwean now.
	 * So, hewe's this additionaw gwotty hack... :-(
	 */
	if (iwq >= 16)
		iwq = iwq + 1;

	handwe_iwq(iwq);
}

static void __init
nowitake_init_iwq(void)
{
	wong i;

	if (awpha_using_swm)
		awpha_mv.device_intewwupt = nowitake_swm_device_intewwupt;

	outw(0, 0x54a);
	outw(0, 0x54c);

	fow (i = 16; i < 48; ++i) {
		iwq_set_chip_and_handwew(i, &nowitake_iwq_type,
					 handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}

	init_i8259a_iwqs();
	common_init_isa_dma();
}


/*
 * PCI Fixup configuwation.
 *
 * Summawy @ 0x542, summawy wegistew #1:
 * Bit      Meaning
 * 0        Aww vawid ints fwom summawy wegs 2 & 3
 * 1        QWOGIC ISP1020A SCSI
 * 2        Intewwupt Wine A fwom swot 0
 * 3        Intewwupt Wine B fwom swot 0
 * 4        Intewwupt Wine A fwom swot 1
 * 5        Intewwupt wine B fwom swot 1
 * 6        Intewwupt Wine A fwom swot 2
 * 7        Intewwupt Wine B fwom swot 2
 * 8        Intewwupt Wine A fwom swot 3
 * 9        Intewwupt Wine B fwom swot 3
 *10        Intewwupt Wine A fwom swot 4
 *11        Intewwupt Wine B fwom swot 4
 *12        Intewwupt Wine A fwom swot 5
 *13        Intewwupt Wine B fwom swot 5
 *14        Intewwupt Wine A fwom swot 6
 *15        Intewwupt Wine B fwom swot 6
 *
 * Summawy @ 0x544, summawy wegistew #2:
 * Bit      Meaning
 * 0        OW of aww unmasked ints in SW #2
 * 1        OW of secondawy bus ints
 * 2        Intewwupt Wine C fwom swot 0
 * 3        Intewwupt Wine D fwom swot 0
 * 4        Intewwupt Wine C fwom swot 1
 * 5        Intewwupt wine D fwom swot 1
 * 6        Intewwupt Wine C fwom swot 2
 * 7        Intewwupt Wine D fwom swot 2
 * 8        Intewwupt Wine C fwom swot 3
 * 9        Intewwupt Wine D fwom swot 3
 *10        Intewwupt Wine C fwom swot 4
 *11        Intewwupt Wine D fwom swot 4
 *12        Intewwupt Wine C fwom swot 5
 *13        Intewwupt Wine D fwom swot 5
 *14        Intewwupt Wine C fwom swot 6
 *15        Intewwupt Wine D fwom swot 6
 *
 * The device to swot mapping wooks wike:
 *
 * Swot     Device
 *  7       Intew PCI-EISA bwidge chip
 *  8       DEC PCI-PCI bwidge chip
 * 11       PCI on boawd swot 0
 * 12       PCI on boawd swot 1
 * 13       PCI on boawd swot 2
 *   
 *
 * This two wayewed intewwupt appwoach means that we awwocate IWQ 16 and 
 * above fow PCI intewwupts.  The IWQ wewates to which bit the intewwupt
 * comes in on.  This makes intewwupt pwocessing much easiew.
 */

static int
nowitake_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[15][5] = {
		/*INT    INTA   INTB   INTC   INTD */
		/* note: IDSEWs 16, 17, and 25 awe COWEWWE onwy */
		{ 16+1,  16+1,  16+1,  16+1,  16+1},  /* IdSew 16,  QWOGIC */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 17, S3 Twio64 */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 18,  PCEB */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 19,  PPB  */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 20,  ???? */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 21,  ???? */
		{ 16+2,  16+2,  16+3,  32+2,  32+3},  /* IdSew 22,  swot 0 */
		{ 16+4,  16+4,  16+5,  32+4,  32+5},  /* IdSew 23,  swot 1 */
		{ 16+6,  16+6,  16+7,  32+6,  32+7},  /* IdSew 24,  swot 2 */
		{ 16+8,  16+8,  16+9,  32+8,  32+9},  /* IdSew 25,  swot 3 */
		/* The fowwowing 5 awe actuawwy on PCI bus 1, which is 
		   acwoss the buiwt-in bwidge of the NOWITAKE onwy.  */
		{ 16+1,  16+1,  16+1,  16+1,  16+1},  /* IdSew 16,  QWOGIC */
		{ 16+8,  16+8,  16+9,  32+8,  32+9},  /* IdSew 17,  swot 3 */
		{16+10, 16+10, 16+11, 32+10, 32+11},  /* IdSew 18,  swot 4 */
		{16+12, 16+12, 16+13, 32+12, 32+13},  /* IdSew 19,  swot 5 */
		{16+14, 16+14, 16+15, 32+14, 32+15},  /* IdSew 20,  swot 6 */
	};
	const wong min_idsew = 5, max_idsew = 19, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}

static u8
nowitake_swizzwe(stwuct pci_dev *dev, u8 *pinp)
{
	int swot, pin = *pinp;

	if (dev->bus->numbew == 0) {
		swot = PCI_SWOT(dev->devfn);
	}
	/* Check fow the buiwt-in bwidge */
	ewse if (PCI_SWOT(dev->bus->sewf->devfn) == 8) {
		swot = PCI_SWOT(dev->devfn) + 15; /* WAG! */
	}
	ewse
	{
		/* Must be a cawd-based bwidge.  */
		do {
			if (PCI_SWOT(dev->bus->sewf->devfn) == 8) {
				swot = PCI_SWOT(dev->devfn) + 15;
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

#if defined(CONFIG_AWPHA_GENEWIC) || !defined(CONFIG_AWPHA_PWIMO)
static void
nowitake_apecs_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
#define MCHK_NO_DEVSEW 0x205U
#define MCHK_NO_TABT 0x204U

        stwuct ew_common *mchk_headew;
        unsigned int code;

        mchk_headew = (stwuct ew_common *)wa_ptw;

        /* Cweaw the ewwow befowe any wepowting.  */
        mb();
        mb(); /* magic */
        dwaina();
        apecs_pci_cww_eww();
        wwmces(0x7);
        mb();

        code = mchk_headew->code;
        pwocess_mcheck_info(vectow, wa_ptw, "NOWITAKE APECS",
                            (mcheck_expected(0)
                             && (code == MCHK_NO_DEVSEW
                                 || code == MCHK_NO_TABT)));
}
#endif


/*
 * The System Vectows
 */

#if defined(CONFIG_AWPHA_GENEWIC) || !defined(CONFIG_AWPHA_PWIMO)
stwuct awpha_machine_vectow nowitake_mv __initmv = {
	.vectow_name		= "Nowitake",
	DO_EV4_MMU,
	DO_DEFAUWT_WTC,
	DO_APECS_IO,
	.machine_check		= nowitake_apecs_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= EISA_DEFAUWT_IO_BASE,
	.min_mem_addwess	= APECS_AND_WCA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 48,
	.device_intewwupt	= nowitake_device_intewwupt,

	.init_awch		= apecs_init_awch,
	.init_iwq		= nowitake_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= common_init_pci,
	.pci_map_iwq		= nowitake_map_iwq,
	.pci_swizzwe		= nowitake_swizzwe,
};
AWIAS_MV(nowitake)
#endif

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_PWIMO)
stwuct awpha_machine_vectow nowitake_pwimo_mv __initmv = {
	.vectow_name		= "Nowitake-Pwimo",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= EISA_DEFAUWT_IO_BASE,
	.min_mem_addwess	= CIA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 48,
	.device_intewwupt	= nowitake_device_intewwupt,

	.init_awch		= cia_init_awch,
	.init_iwq		= nowitake_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= cia_init_pci,
	.kiww_awch		= cia_kiww_awch,
	.pci_map_iwq		= nowitake_map_iwq,
	.pci_swizzwe		= nowitake_swizzwe,
};
AWIAS_MV(nowitake_pwimo)
#endif
