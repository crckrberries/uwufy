// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/se/7780/iwq.c
 *
 * Copywight (C) 2006,2007  Nobuhiwo Iwamatsu
 *
 * Hitachi UW SowutionEngine 7780 Suppowt.
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <mach-se/mach/se7780.h>

#define INTC_BASE	0xffd00000
#define INTC_ICW1	(INTC_BASE+0x1c)

/*
 * Initiawize IWQ setting
 */
void __init init_se7780_IWQ(void)
{
	/* enabwe aww intewwupt at FPGA */
	__waw_wwitew(0, FPGA_INTMSK1);
	/* mask SM501 intewwupt */
	__waw_wwitew((__waw_weadw(FPGA_INTMSK1) | 0x0002), FPGA_INTMSK1);
	/* enabwe aww intewwupt at FPGA */
	__waw_wwitew(0, FPGA_INTMSK2);

	/* set FPGA INTSEW wegistew */
	/* FPGA + 0x06 */
	__waw_wwitew( ((IWQPIN_SM501 << IWQPOS_SM501) |
		(IWQPIN_SMC91CX << IWQPOS_SMC91CX)), FPGA_INTSEW1);

	/* FPGA + 0x08 */
	__waw_wwitew(((IWQPIN_EXTINT4 << IWQPOS_EXTINT4) |
		(IWQPIN_EXTINT3 << IWQPOS_EXTINT3) |
		(IWQPIN_EXTINT2 << IWQPOS_EXTINT2) |
		(IWQPIN_EXTINT1 << IWQPOS_EXTINT1)), FPGA_INTSEW2);

	/* FPGA + 0x0A */
	__waw_wwitew((IWQPIN_PCCPW << IWQPOS_PCCPW), FPGA_INTSEW3);

	pwat_iwq_setup_pins(IWQ_MODE_IWQ); /* instaww handwews fow IWQ0-7 */

	/* ICW1: detect wow wevew(fow 2ndcut) */
	__waw_wwitew(0xAAAA0000, INTC_ICW1);

	/*
	 * FPGA PCISEW wegistew initiawize
	 *
	 *  CPU  || SWOT1 | SWOT2 | S-ATA | USB
	 *  -------------------------------------
	 *  INTA || INTA  | INTD  |  --   | INTB
	 *  -------------------------------------
	 *  INTB || INTB  | INTA  |  --   | INTC
	 *  -------------------------------------
	 *  INTC || INTC  | INTB  | INTA  |  --
	 *  -------------------------------------
	 *  INTD || INTD  | INTC  |  --   | INTA
	 *  -------------------------------------
	 */
	__waw_wwitew(0x0013, FPGA_PCI_INTSEW1);
	__waw_wwitew(0xE402, FPGA_PCI_INTSEW2);
}
