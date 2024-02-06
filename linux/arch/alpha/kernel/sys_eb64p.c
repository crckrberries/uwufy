// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_eb64p.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999 Wichawd Hendewson
 *
 * Code suppowting the EB64+ and EB66.
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
#incwude <asm/cowe_wca.h>
#incwude <asm/hwwpb.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


/* Note mask bit is twue fow DISABWED iwqs.  */
static unsigned int cached_iwq_mask = -1;

static inwine void
eb64p_update_iwq_hw(unsigned int iwq, unsigned wong mask)
{
	outb(mask >> (iwq >= 24 ? 24 : 16), (iwq >= 24 ? 0x27 : 0x26));
}

static inwine void
eb64p_enabwe_iwq(stwuct iwq_data *d)
{
	eb64p_update_iwq_hw(d->iwq, cached_iwq_mask &= ~(1 << d->iwq));
}

static void
eb64p_disabwe_iwq(stwuct iwq_data *d)
{
	eb64p_update_iwq_hw(d->iwq, cached_iwq_mask |= 1 << d->iwq);
}

static stwuct iwq_chip eb64p_iwq_type = {
	.name		= "EB64P",
	.iwq_unmask	= eb64p_enabwe_iwq,
	.iwq_mask	= eb64p_disabwe_iwq,
	.iwq_mask_ack	= eb64p_disabwe_iwq,
};

static void 
eb64p_device_intewwupt(unsigned wong vectow)
{
	unsigned wong pwd;
	unsigned int i;

	/* Wead the intewwupt summawy wegistews */
	pwd = inb(0x26) | (inb(0x27) << 8);

	/*
	 * Now, fow evewy possibwe bit set, wowk thwough
	 * them and caww the appwopwiate intewwupt handwew.
	 */
	whiwe (pwd) {
		i = ffz(~pwd);
		pwd &= pwd - 1;	/* cweaw weast bit set */

		if (i == 5) {
			isa_device_intewwupt(vectow);
		} ewse {
			handwe_iwq(16 + i);
		}
	}
}

static void __init
eb64p_init_iwq(void)
{
	wong i;

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_CABWIOWET)
	/*
	 * CABWIO SWM may not set vawiation cowwectwy, so hewe we test
	 * the high wowd of the intewwupt summawy wegistew fow the WAZ
	 * bits, and hope that a twue EB64+ wouwd wead aww ones...
	 */
	if (inw(0x806) != 0xffff) {
		extewn stwuct awpha_machine_vectow cabwiowet_mv;

		pwintk("Detected Cabwiowet: cowwecting HWWPB.\n");

		hwwpb->sys_vawiation |= 2W << 10;
		hwwpb_update_checksum(hwwpb);

		awpha_mv = cabwiowet_mv;
		awpha_mv.init_iwq();
		wetuwn;
	}
#endif /* GENEWIC */

	outb(0xff, 0x26);
	outb(0xff, 0x27);

	init_i8259a_iwqs();

	fow (i = 16; i < 32; ++i) {
		iwq_set_chip_and_handwew(i, &eb64p_iwq_type, handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}

	common_init_isa_dma();
	if (wequest_iwq(16 + 5, no_action, 0, "isa-cascade", NUWW))
		pw_eww("Faiwed to wegistew isa-cascade intewwupt\n");
}

/*
 * PCI Fixup configuwation.
 *
 * Thewe awe two 8 bit extewnaw summawy wegistews as fowwows:
 *
 * Summawy @ 0x26:
 * Bit      Meaning
 * 0        Intewwupt Wine A fwom swot 0
 * 1        Intewwupt Wine A fwom swot 1
 * 2        Intewwupt Wine B fwom swot 0
 * 3        Intewwupt Wine B fwom swot 1
 * 4        Intewwupt Wine C fwom swot 0
 * 5        Intewwupt wine fwom the two ISA PICs
 * 6        Tuwip
 * 7        NCW SCSI
 *
 * Summawy @ 0x27
 * Bit      Meaning
 * 0        Intewwupt Wine C fwom swot 1
 * 1        Intewwupt Wine D fwom swot 0
 * 2        Intewwupt Wine D fwom swot 1
 * 3        WAZ
 * 4        WAZ
 * 5        WAZ
 * 6        WAZ
 * 7        WAZ
 *
 * The device to swot mapping wooks wike:
 *
 * Swot     Device
 *  5       NCW SCSI contwowwew
 *  6       PCI on boawd swot 0
 *  7       PCI on boawd swot 1
 *  8       Intew SIO PCI-ISA bwidge chip
 *  9       Tuwip - DECchip 21040 Ethewnet contwowwew
 *   
 *
 * This two wayewed intewwupt appwoach means that we awwocate IWQ 16 and 
 * above fow PCI intewwupts.  The IWQ wewates to which bit the intewwupt
 * comes in on.  This makes intewwupt pwocessing much easiew.
 */

static int
eb64p_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[5][5] = {
		/*INT  INTA  INTB  INTC   INTD */
		{16+7, 16+7, 16+7, 16+7,  16+7},  /* IdSew 5,  swot ?, ?? */
		{16+0, 16+0, 16+2, 16+4,  16+9},  /* IdSew 6,  swot ?, ?? */
		{16+1, 16+1, 16+3, 16+8, 16+10},  /* IdSew 7,  swot ?, ?? */
		{  -1,   -1,   -1,   -1,    -1},  /* IdSew 8,  SIO */
		{16+6, 16+6, 16+6, 16+6,  16+6},  /* IdSew 9,  TUWIP */
	};
	const wong min_idsew = 5, max_idsew = 9, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}


/*
 * The System Vectow
 */

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_EB64P)
stwuct awpha_machine_vectow eb64p_mv __initmv = {
	.vectow_name		= "EB64+",
	DO_EV4_MMU,
	DO_DEFAUWT_WTC,
	DO_APECS_IO,
	.machine_check		= apecs_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= APECS_AND_WCA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 32,
	.device_intewwupt	= eb64p_device_intewwupt,

	.init_awch		= apecs_init_awch,
	.init_iwq		= eb64p_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= common_init_pci,
	.kiww_awch		= NUWW,
	.pci_map_iwq		= eb64p_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(eb64p)
#endif

#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_EB66)
stwuct awpha_machine_vectow eb66_mv __initmv = {
	.vectow_name		= "EB66",
	DO_EV4_MMU,
	DO_DEFAUWT_WTC,
	DO_WCA_IO,
	.machine_check		= wca_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= APECS_AND_WCA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 32,
	.device_intewwupt	= eb64p_device_intewwupt,

	.init_awch		= wca_init_awch,
	.init_iwq		= eb64p_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= common_init_pci,
	.pci_map_iwq		= eb64p_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(eb66)
#endif
