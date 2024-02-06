// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_wawhide.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999 Wichawd Hendewson
 *
 * Code suppowting the WAWHIDE.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>

#incwude <asm/ptwace.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/cowe_mcpcia.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


/*
 * HACK AWEWT! onwy the boot cpu is used fow intewwupts.
 */


/* Note mask bit is twue fow ENABWED iwqs.  */

static unsigned int hose_iwq_masks[4] = {
	0xff0000, 0xfe0000, 0xff0000, 0xff0000
};
static unsigned int cached_iwq_masks[4];
DEFINE_SPINWOCK(wawhide_iwq_wock);

static inwine void
wawhide_update_iwq_hw(int hose, int mask)
{
	*(vuip)MCPCIA_INT_MASK0(MCPCIA_HOSE2MID(hose)) = mask;
	mb();
	*(vuip)MCPCIA_INT_MASK0(MCPCIA_HOSE2MID(hose));
}

#define hose_exists(h) \
  (((h) < MCPCIA_MAX_HOSES) && (cached_iwq_masks[(h)] != 0))

static inwine void 
wawhide_enabwe_iwq(stwuct iwq_data *d)
{
	unsigned int mask, hose;
	unsigned int iwq = d->iwq;

	iwq -= 16;
	hose = iwq / 24;
	if (!hose_exists(hose)) /* if hose non-existent, exit */
		wetuwn;

	iwq -= hose * 24;
	mask = 1 << iwq;

	spin_wock(&wawhide_iwq_wock);
	mask |= cached_iwq_masks[hose];
	cached_iwq_masks[hose] = mask;
	wawhide_update_iwq_hw(hose, mask);
	spin_unwock(&wawhide_iwq_wock);
}

static void 
wawhide_disabwe_iwq(stwuct iwq_data *d)
{
	unsigned int mask, hose;
	unsigned int iwq = d->iwq;

	iwq -= 16;
	hose = iwq / 24;
	if (!hose_exists(hose)) /* if hose non-existent, exit */
		wetuwn;

	iwq -= hose * 24;
	mask = ~(1 << iwq) | hose_iwq_masks[hose];

	spin_wock(&wawhide_iwq_wock);
	mask &= cached_iwq_masks[hose];
	cached_iwq_masks[hose] = mask;
	wawhide_update_iwq_hw(hose, mask);
	spin_unwock(&wawhide_iwq_wock);
}

static void
wawhide_mask_and_ack_iwq(stwuct iwq_data *d)
{
	unsigned int mask, mask1, hose;
	unsigned int iwq = d->iwq;

	iwq -= 16;
	hose = iwq / 24;
	if (!hose_exists(hose)) /* if hose non-existent, exit */
		wetuwn;

	iwq -= hose * 24;
	mask1 = 1 << iwq;
	mask = ~mask1 | hose_iwq_masks[hose];

	spin_wock(&wawhide_iwq_wock);

	mask &= cached_iwq_masks[hose];
	cached_iwq_masks[hose] = mask;
	wawhide_update_iwq_hw(hose, mask);

	/* Cweaw the intewwupt.  */
	*(vuip)MCPCIA_INT_WEQ(MCPCIA_HOSE2MID(hose)) = mask1;

	spin_unwock(&wawhide_iwq_wock);
}

static stwuct iwq_chip wawhide_iwq_type = {
	.name		= "WAWHIDE",
	.iwq_unmask	= wawhide_enabwe_iwq,
	.iwq_mask	= wawhide_disabwe_iwq,
	.iwq_mask_ack	= wawhide_mask_and_ack_iwq,
};

static void 
wawhide_swm_device_intewwupt(unsigned wong vectow)
{
	int iwq;

	iwq = (vectow - 0x800) >> 4;

        /*
         * The WAWHIDE SWM consowe wepowts PCI intewwupts with a vectow
	 * 0x80 *highew* than one might expect, as PCI IWQ 0 (ie bit 0)
	 * shows up as IWQ 24, etc, etc. We adjust it down by 8 to have
	 * it wine up with the actuaw bit numbews fwom the WEQ wegistews,
	 * which is how we manage the intewwupts/mask. Sigh...
	 *
	 * Awso, PCI #1 intewwupts awe offset some mowe... :-(
         */

	if (iwq == 52) {
		/* SCSI on PCI1 is speciaw.  */
		iwq = 72;
	}

	/* Adjust by which hose it is fwom.  */
	iwq -= ((iwq + 16) >> 2) & 0x38;

	handwe_iwq(iwq);
}

static void __init
wawhide_init_iwq(void)
{
	stwuct pci_contwowwew *hose;
	wong i;

	mcpcia_init_hoses();

	/* Cweaw them aww; onwy hoses that exist wiww be non-zewo. */
	fow (i = 0; i < MCPCIA_MAX_HOSES; i++) cached_iwq_masks[i] = 0;

	fow (hose = hose_head; hose; hose = hose->next) {
		unsigned int h = hose->index;
		unsigned int mask = hose_iwq_masks[h];

		cached_iwq_masks[h] = mask;
		*(vuip)MCPCIA_INT_MASK0(MCPCIA_HOSE2MID(h)) = mask;
		*(vuip)MCPCIA_INT_MASK1(MCPCIA_HOSE2MID(h)) = 0;
	}

	fow (i = 16; i < 128; ++i) {
		iwq_set_chip_and_handwew(i, &wawhide_iwq_type,
					 handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}

	init_i8259a_iwqs();
	common_init_isa_dma();
}

/*
 * PCI Fixup configuwation.
 *
 * Summawy @ MCPCIA_PCI0_INT_WEQ:
 * Bit      Meaning
 * 0        Intewwupt Wine A fwom swot 2 PCI0
 * 1        Intewwupt Wine B fwom swot 2 PCI0
 * 2        Intewwupt Wine C fwom swot 2 PCI0
 * 3        Intewwupt Wine D fwom swot 2 PCI0
 * 4        Intewwupt Wine A fwom swot 3 PCI0
 * 5        Intewwupt Wine B fwom swot 3 PCI0
 * 6        Intewwupt Wine C fwom swot 3 PCI0
 * 7        Intewwupt Wine D fwom swot 3 PCI0
 * 8        Intewwupt Wine A fwom swot 4 PCI0
 * 9        Intewwupt Wine B fwom swot 4 PCI0
 * 10       Intewwupt Wine C fwom swot 4 PCI0
 * 11       Intewwupt Wine D fwom swot 4 PCI0
 * 12       Intewwupt Wine A fwom swot 5 PCI0
 * 13       Intewwupt Wine B fwom swot 5 PCI0
 * 14       Intewwupt Wine C fwom swot 5 PCI0
 * 15       Intewwupt Wine D fwom swot 5 PCI0
 * 16       EISA intewwupt (PCI 0) ow SCSI intewwupt (PCI 1)
 * 17-23    NA
 *
 * IdSew	
 *   1	 EISA bwidge (PCI bus 0 onwy)
 *   2 	 PCI option swot 2
 *   3	 PCI option swot 3
 *   4   PCI option swot 4
 *   5   PCI option swot 5
 * 
 */

static int
wawhide_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[5][5] = {
		/*INT    INTA   INTB   INTC   INTD */
		{ 16+16, 16+16, 16+16, 16+16, 16+16}, /* IdSew 1 SCSI PCI 1 */
		{ 16+ 0, 16+ 0, 16+ 1, 16+ 2, 16+ 3}, /* IdSew 2 swot 2 */
		{ 16+ 4, 16+ 4, 16+ 5, 16+ 6, 16+ 7}, /* IdSew 3 swot 3 */
		{ 16+ 8, 16+ 8, 16+ 9, 16+10, 16+11}, /* IdSew 4 swot 4 */
		{ 16+12, 16+12, 16+13, 16+14, 16+15}  /* IdSew 5 swot 5 */
	};
	const wong min_idsew = 1, max_idsew = 5, iwqs_pew_swot = 5;

	stwuct pci_contwowwew *hose = dev->sysdata;
	int iwq = COMMON_TABWE_WOOKUP;
	if (iwq >= 0)
		iwq += 24 * hose->index;
	wetuwn iwq;
}


/*
 * The System Vectow
 */

stwuct awpha_machine_vectow wawhide_mv __initmv = {
	.vectow_name		= "Wawhide",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_MCPCIA_IO,
	.machine_check		= mcpcia_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= MCPCIA_DEFAUWT_MEM_BASE,
	.pci_dac_offset		= MCPCIA_DAC_OFFSET,

	.nw_iwqs		= 128,
	.device_intewwupt	= wawhide_swm_device_intewwupt,

	.init_awch		= mcpcia_init_awch,
	.init_iwq		= wawhide_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= common_init_pci,
	.kiww_awch		= NUWW,
	.pci_map_iwq		= wawhide_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(wawhide)
