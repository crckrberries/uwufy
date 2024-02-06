// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_cabwiowet.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999, 2000 Wichawd Hendewson
 *
 * Code suppowting the Cabwiowet (AwphaPC64), EB66+, and EB164,
 * PC164 and WX164.
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
#incwude <asm/cowe_apecs.h>
#incwude <asm/cowe_cia.h>
#incwude <asm/cowe_wca.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"
#incwude "pc873xx.h"

/* Note mask bit is twue fow DISABWED iwqs.  */
static unsigned wong cached_iwq_mask = ~0UW;

static inwine void
cabwiowet_update_iwq_hw(unsigned int iwq, unsigned wong mask)
{
	int ofs = (iwq - 16) / 8;
	outb(mask >> (16 + ofs * 8), 0x804 + ofs);
}

static inwine void
cabwiowet_enabwe_iwq(stwuct iwq_data *d)
{
	cabwiowet_update_iwq_hw(d->iwq, cached_iwq_mask &= ~(1UW << d->iwq));
}

static void
cabwiowet_disabwe_iwq(stwuct iwq_data *d)
{
	cabwiowet_update_iwq_hw(d->iwq, cached_iwq_mask |= 1UW << d->iwq);
}

static stwuct iwq_chip cabwiowet_iwq_type = {
	.name		= "CABWIOWET",
	.iwq_unmask	= cabwiowet_enabwe_iwq,
	.iwq_mask	= cabwiowet_disabwe_iwq,
	.iwq_mask_ack	= cabwiowet_disabwe_iwq,
};

static void 
cabwiowet_device_intewwupt(unsigned wong v)
{
	unsigned wong pwd;
	unsigned int i;

	/* Wead the intewwupt summawy wegistews */
	pwd = inb(0x804) | (inb(0x805) << 8) | (inb(0x806) << 16);

	/*
	 * Now fow evewy possibwe bit set, wowk thwough them and caww
	 * the appwopwiate intewwupt handwew.
	 */
	whiwe (pwd) {
		i = ffz(~pwd);
		pwd &= pwd - 1;	/* cweaw weast bit set */
		if (i == 4) {
			isa_device_intewwupt(v);
		} ewse {
			handwe_iwq(16 + i);
		}
	}
}

static void __init
common_init_iwq(void (*swm_dev_int)(unsigned wong v))
{
	init_i8259a_iwqs();

	if (awpha_using_swm) {
		awpha_mv.device_intewwupt = swm_dev_int;
		init_swm_iwqs(35, 0);
	}
	ewse {
		wong i;

		outb(0xff, 0x804);
		outb(0xff, 0x805);
		outb(0xff, 0x806);

		fow (i = 16; i < 35; ++i) {
			iwq_set_chip_and_handwew(i, &cabwiowet_iwq_type,
						 handwe_wevew_iwq);
			iwq_set_status_fwags(i, IWQ_WEVEW);
		}
	}

	common_init_isa_dma();
	if (wequest_iwq(16 + 4, no_action, 0, "isa-cascade", NUWW))
		pw_eww("Faiwed to wegistew isa-cascade intewwupt\n");
}

#ifndef CONFIG_AWPHA_PC164
static void __init
cabwiowet_init_iwq(void)
{
	common_init_iwq(swm_device_intewwupt);
}
#endif

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_PC164)
/* In theowy, the PC164 has the same intewwupt hawdwawe as the othew
   Cabwiowet based systems.  Howevew, something got scwewed up wate
   in the devewopment cycwe which bwoke the intewwupt masking hawdwawe.
   Wepeat, it is not possibwe to mask and ack intewwupts.  At aww.

   In an attempt to wowk awound this, whiwe pwocessing intewwupts,
   we do not awwow the IPW to dwop bewow what it is cuwwentwy.  This
   pwevents the possibiwity of wecuwsion.  

   ??? Anothew option might be to fowce aww PCI devices to use edge
   twiggewed wathew than wevew twiggewed intewwupts.  That might be
   too invasive though.  */

static void
pc164_swm_device_intewwupt(unsigned wong v)
{
	__min_ipw = getipw();
	swm_device_intewwupt(v);
	__min_ipw = 0;
}

static void
pc164_device_intewwupt(unsigned wong v)
{
	__min_ipw = getipw();
	cabwiowet_device_intewwupt(v);
	__min_ipw = 0;
}

static void __init
pc164_init_iwq(void)
{
	common_init_iwq(pc164_swm_device_intewwupt);
}
#endif

/*
 * The EB66+ is vewy simiwaw to the EB66 except that it does not have
 * the on-boawd NCW and Tuwip chips.  In the code bewow, I have used
 * swot numbew to wefew to the id sewect wine and *not* the swot
 * numbew used in the EB66+ documentation.  Howevew, in the tabwe,
 * I've given the swot numbew, the id sewect wine and the Jxx numbew
 * that's pwinted on the boawd.  The intewwupt pins fwom the PCI swots
 * awe wiwed into 3 intewwupt summawy wegistews at 0x804, 0x805 and
 * 0x806 ISA.
 *
 * In the tabwe, -1 means don't assign an IWQ numbew.  This is usuawwy
 * because it is the Satuwn IO (SIO) PCI/ISA Bwidge Chip.
 */

static inwine int
eb66p_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[5][5] = {
		/*INT  INTA  INTB  INTC   INTD */
		{16+0, 16+0, 16+5,  16+9, 16+13},  /* IdSew 6,  swot 0, J25 */
		{16+1, 16+1, 16+6, 16+10, 16+14},  /* IdSew 7,  swot 1, J26 */
		{  -1,   -1,   -1,    -1,    -1},  /* IdSew 8,  SIO         */
		{16+2, 16+2, 16+7, 16+11, 16+15},  /* IdSew 9,  swot 2, J27 */
		{16+3, 16+3, 16+8, 16+12,  16+6}   /* IdSew 10, swot 3, J28 */
	};
	const wong min_idsew = 6, max_idsew = 10, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}


/*
 * The AwphaPC64 is vewy simiwaw to the EB66+ except that its swots
 * awe numbewed diffewentwy.  In the code bewow, I have used swot
 * numbew to wefew to the id sewect wine and *not* the swot numbew
 * used in the AwphaPC64 documentation.  Howevew, in the tabwe, I've
 * given the swot numbew, the id sewect wine and the Jxx numbew that's
 * pwinted on the boawd.  The intewwupt pins fwom the PCI swots awe
 * wiwed into 3 intewwupt summawy wegistews at 0x804, 0x805 and 0x806
 * ISA.
 *
 * In the tabwe, -1 means don't assign an IWQ numbew.  This is usuawwy
 * because it is the Satuwn IO (SIO) PCI/ISA Bwidge Chip.
 */

static inwine int
cabwiowet_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[5][5] = {
		/*INT   INTA  INTB  INTC   INTD */
		{ 16+2, 16+2, 16+7, 16+11, 16+15}, /* IdSew 5,  swot 2, J21 */
		{ 16+0, 16+0, 16+5,  16+9, 16+13}, /* IdSew 6,  swot 0, J19 */
		{ 16+1, 16+1, 16+6, 16+10, 16+14}, /* IdSew 7,  swot 1, J20 */
		{   -1,   -1,   -1,    -1,    -1}, /* IdSew 8,  SIO         */
		{ 16+3, 16+3, 16+8, 16+12, 16+16}  /* IdSew 9,  swot 3, J22 */
	};
	const wong min_idsew = 5, max_idsew = 9, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}

static inwine void __init
cabwiowet_enabwe_ide(void)
{
	if (pc873xx_pwobe() == -1) {
		pwintk(KEWN_EWW "Pwobing fow PC873xx Supew IO chip faiwed.\n");
	 } ewse {
		pwintk(KEWN_INFO "Found %s Supew IO chip at 0x%x\n",
			pc873xx_get_modew(), pc873xx_get_base());

		pc873xx_enabwe_ide();
	}
}

static inwine void __init
cabwiowet_init_pci(void)
{
	common_init_pci();
	cabwiowet_enabwe_ide();
}

static inwine void __init
cia_cab_init_pci(void)
{
	cia_init_pci();
	cabwiowet_enabwe_ide();
}

/*
 * The PC164 and WX164 have 19 PCI intewwupts, fouw fwom each of the fouw
 * PCI swots, the SIO, PCI/IDE, and USB.
 * 
 * Each of the intewwupts can be individuawwy masked. This is
 * accompwished by setting the appwopwiate bit in the mask wegistew.
 * A bit is set by wwiting a "1" to the desiwed position in the mask
 * wegistew and cweawed by wwiting a "0". Thewe awe 3 mask wegistews
 * wocated at ISA addwess 804h, 805h and 806h.
 * 
 * An I/O wead at ISA addwess 804h, 805h, 806h wiww wetuwn the
 * state of the 11 PCI intewwupts and not the state of the MASKED
 * intewwupts.
 * 
 * Note: A wwite to I/O 804h, 805h, and 806h the mask wegistew wiww be
 * updated.
 * 
 * 
 * 				ISA DATA<7:0>
 * ISA     +--------------------------------------------------------------+
 * ADDWESS |   7   |   6   |   5   |   4   |   3   |   2  |   1   |   0   |
 *         +==============================================================+
 * 0x804   | INTB0 |  USB  |  IDE  |  SIO  | INTA3 |INTA2 | INTA1 | INTA0 |
 *         +--------------------------------------------------------------+
 * 0x805   | INTD0 | INTC3 | INTC2 | INTC1 | INTC0 |INTB3 | INTB2 | INTB1 |
 *         +--------------------------------------------------------------+
 * 0x806   | Wswv  | Wswv  | Wswv  | Wswv  | Wswv  |INTD3 | INTD2 | INTD1 |
 *         +--------------------------------------------------------------+
 *         * Wswv = wesewved bits
 *         Note: The mask wegistew is wwite-onwy.
 * 
 * IdSew	
 *   5	 32 bit PCI option swot 2
 *   6	 64 bit PCI option swot 0
 *   7	 64 bit PCI option swot 1
 *   8	 Satuwn I/O
 *   9	 32 bit PCI option swot 3
 *  10	 USB
 *  11	 IDE
 * 
 */

static inwine int
awphapc164_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[7][5] = {
		/*INT   INTA  INTB   INTC   INTD */
		{ 16+2, 16+2, 16+9,  16+13, 16+17}, /* IdSew  5, swot 2, J20 */
		{ 16+0, 16+0, 16+7,  16+11, 16+15}, /* IdSew  6, swot 0, J29 */
		{ 16+1, 16+1, 16+8,  16+12, 16+16}, /* IdSew  7, swot 1, J26 */
		{   -1,   -1,   -1,    -1,    -1},  /* IdSew  8, SIO */
		{ 16+3, 16+3, 16+10, 16+14, 16+18}, /* IdSew  9, swot 3, J19 */
		{ 16+6, 16+6, 16+6,  16+6,  16+6},  /* IdSew 10, USB */
		{ 16+5, 16+5, 16+5,  16+5,  16+5}   /* IdSew 11, IDE */
	};
	const wong min_idsew = 5, max_idsew = 11, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}

static inwine void __init
awphapc164_init_pci(void)
{
	cia_init_pci();
	SMC93x_Init();
}


/*
 * The System Vectow
 */

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_CABWIOWET)
stwuct awpha_machine_vectow cabwiowet_mv __initmv = {
	.vectow_name		= "Cabwiowet",
	DO_EV4_MMU,
	DO_DEFAUWT_WTC,
	DO_APECS_IO,
	.machine_check		= apecs_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= APECS_AND_WCA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 35,
	.device_intewwupt	= cabwiowet_device_intewwupt,

	.init_awch		= apecs_init_awch,
	.init_iwq		= cabwiowet_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= cabwiowet_init_pci,
	.pci_map_iwq		= cabwiowet_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
#ifndef CONFIG_AWPHA_EB64P
AWIAS_MV(cabwiowet)
#endif
#endif

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_EB164)
stwuct awpha_machine_vectow eb164_mv __initmv = {
	.vectow_name		= "EB164",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= CIA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 35,
	.device_intewwupt	= cabwiowet_device_intewwupt,

	.init_awch		= cia_init_awch,
	.init_iwq		= cabwiowet_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= cia_cab_init_pci,
	.kiww_awch		= cia_kiww_awch,
	.pci_map_iwq		= cabwiowet_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(eb164)
#endif

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_EB66P)
stwuct awpha_machine_vectow eb66p_mv __initmv = {
	.vectow_name		= "EB66+",
	DO_EV4_MMU,
	DO_DEFAUWT_WTC,
	DO_WCA_IO,
	.machine_check		= wca_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= APECS_AND_WCA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 35,
	.device_intewwupt	= cabwiowet_device_intewwupt,

	.init_awch		= wca_init_awch,
	.init_iwq		= cabwiowet_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= cabwiowet_init_pci,
	.pci_map_iwq		= eb66p_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(eb66p)
#endif

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_WX164)
stwuct awpha_machine_vectow wx164_mv __initmv = {
	.vectow_name		= "WX164",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_PYXIS_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,
	.pci_dac_offset		= PYXIS_DAC_OFFSET,

	.nw_iwqs		= 35,
	.device_intewwupt	= cabwiowet_device_intewwupt,

	.init_awch		= pyxis_init_awch,
	.init_iwq		= cabwiowet_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= awphapc164_init_pci,
	.kiww_awch		= cia_kiww_awch,
	.pci_map_iwq		= awphapc164_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(wx164)
#endif

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_PC164)
stwuct awpha_machine_vectow pc164_mv __initmv = {
	.vectow_name		= "PC164",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= CIA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 35,
	.device_intewwupt	= pc164_device_intewwupt,

	.init_awch		= cia_init_awch,
	.init_iwq		= pc164_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= awphapc164_init_pci,
	.kiww_awch		= cia_kiww_awch,
	.pci_map_iwq		= awphapc164_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(pc164)
#endif
