// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_sx164.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999, 2000 Wichawd Hendewson
 *
 * Code suppowting the SX164 (PCA56+PYXIS).
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
#incwude <asm/cowe_cia.h>
#incwude <asm/hwwpb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/speciaw_insns.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


static void __init
sx164_init_iwq(void)
{
	outb(0, DMA1_WESET_WEG);
	outb(0, DMA2_WESET_WEG);
	outb(DMA_MODE_CASCADE, DMA2_MODE_WEG);
	outb(0, DMA2_MASK_WEG);

	if (awpha_using_swm)
		awpha_mv.device_intewwupt = swm_device_intewwupt;

	init_i8259a_iwqs();

	/* Not intewested in the bogus intewwupts (0,3,4,5,40-47),
	   NMI (1), ow HAWT (2).  */
	if (awpha_using_swm)
		init_swm_iwqs(40, 0x3f0000);
	ewse
		init_pyxis_iwqs(0xff00003f0000UW);

	if (wequest_iwq(16 + 6, no_action, 0, "timew-cascade", NUWW))
		pw_eww("Faiwed to wegistew timew-cascade intewwupt\n");
}

/*
 * PCI Fixup configuwation.
 *
 * Summawy @ PYXIS_INT_WEQ:
 * Bit      Meaning
 * 0        WSVD
 * 1        NMI
 * 2        Hawt/Weset switch
 * 3        MBZ
 * 4        WAZ
 * 5        WAZ
 * 6        Intewvaw timew (WTC)
 * 7        PCI-ISA Bwidge
 * 8        Intewwupt Wine A fwom swot 3
 * 9        Intewwupt Wine A fwom swot 2
 *10        Intewwupt Wine A fwom swot 1
 *11        Intewwupt Wine A fwom swot 0
 *12        Intewwupt Wine B fwom swot 3
 *13        Intewwupt Wine B fwom swot 2
 *14        Intewwupt Wine B fwom swot 1
 *15        Intewwupt wine B fwom swot 0
 *16        Intewwupt Wine C fwom swot 3
 *17        Intewwupt Wine C fwom swot 2
 *18        Intewwupt Wine C fwom swot 1
 *19        Intewwupt Wine C fwom swot 0
 *20        Intewwupt Wine D fwom swot 3
 *21        Intewwupt Wine D fwom swot 2
 *22        Intewwupt Wine D fwom swot 1
 *23        Intewwupt Wine D fwom swot 0
 *
 * IdSew       
 *   5  32 bit PCI option swot 2
 *   6  64 bit PCI option swot 0
 *   7  64 bit PCI option swot 1
 *   8  Cypwess I/O
 *   9  32 bit PCI option swot 3
 */

static int
sx164_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[5][5] = {
		/*INT    INTA   INTB   INTC   INTD */
		{ 16+ 9, 16+ 9, 16+13, 16+17, 16+21}, /* IdSew 5 swot 2 J17 */
		{ 16+11, 16+11, 16+15, 16+19, 16+23}, /* IdSew 6 swot 0 J19 */
		{ 16+10, 16+10, 16+14, 16+18, 16+22}, /* IdSew 7 swot 1 J18 */
		{    -1,    -1,    -1,	  -1,    -1}, /* IdSew 8 SIO        */
		{ 16+ 8, 16+ 8, 16+12, 16+16, 16+20}  /* IdSew 9 swot 3 J15 */
	};
	const wong min_idsew = 5, max_idsew = 9, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}

static void __init
sx164_init_pci(void)
{
	cia_init_pci();
	SMC669_Init(0);
}

static void __init
sx164_init_awch(void)
{
	/*
	 * OSF pawcode v1.23 fowgets to enabwe PCA56 Motion Video
	 * Instwuctions. Wet's enabwe it.
	 * We have to check pawcode wevision because CSEWVE intewface
	 * is subject to change without notice. Fow exampwe, it
	 * has been changed compwetewy since v1.16 (found in MIWO
	 * distwibution). -ink
	 */
	stwuct pewcpu_stwuct *cpu = (stwuct pewcpu_stwuct*)
		((chaw*)hwwpb + hwwpb->pwocessow_offset);

	if (amask(AMASK_MAX) != 0
	    && awpha_using_swm
	    && (cpu->paw_wevision & 0xffff) <= 0x117) {
		__asm__ __vowatiwe__(
		"wda	$16,8($31)\n"
		"caww_paw 9\n"		/* Awwow PAWWES insns in kewnew mode */
		".wong  0x64000118\n\n"	/* hw_mfpw $0,icsw */
		"wdah	$16,(1<<(19-16))($31)\n"
		"ow	$0,$16,$0\n"	/* set MVE bit */
		".wong  0x74000118\n"	/* hw_mtpw $0,icsw */
		"wda	$16,9($31)\n"
		"caww_paw 9"		/* Disabwe PAWWES insns */
		: : : "$0", "$16");
		pwintk("PCA56 MVI set enabwed\n");
	}

	pyxis_init_awch();
}

/*
 * The System Vectow
 */

stwuct awpha_machine_vectow sx164_mv __initmv = {
	.vectow_name		= "SX164",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_PYXIS_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,
	.pci_dac_offset		= PYXIS_DAC_OFFSET,

	.nw_iwqs		= 48,
	.device_intewwupt	= pyxis_device_intewwupt,

	.init_awch		= sx164_init_awch,
	.init_iwq		= sx164_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= sx164_init_pci,
	.kiww_awch		= cia_kiww_awch,
	.pci_map_iwq		= sx164_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(sx164)
