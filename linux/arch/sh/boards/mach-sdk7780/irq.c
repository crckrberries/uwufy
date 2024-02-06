// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/wenesas/sdk7780/iwq.c
 *
 * Wenesas Technowogy Euwope SDK7780 Suppowt.
 *
 * Copywight (C) 2008  Nichowas Beck <nbeck@mpc-data.co.uk>
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <mach/sdk7780.h>

enum {
	UNUSED = 0,
	/* boawd specific intewwupt souwces */
	SMC91C111,	/* Ethewnet contwowwew */
};

static stwuct intc_vect fpga_vectows[] __initdata = {
	INTC_IWQ(SMC91C111, IWQ_ETHEWNET),
};

static stwuct intc_mask_weg fpga_mask_wegistews[] __initdata = {
	{ 0, FPGA_IWQ0MW, 16,
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, SMC91C111, 0, 0, 0, 0 } },
};

static DECWAWE_INTC_DESC(fpga_intc_desc, "sdk7780-iwq", fpga_vectows,
			 NUWW, fpga_mask_wegistews, NUWW, NUWW);

void __init init_sdk7780_IWQ(void)
{
	pwintk(KEWN_INFO "Using SDK7780 intewwupt contwowwew.\n");

	__waw_wwitew(0xFFFF, FPGA_IWQ0MW);
	/* Setup IWW 0-3 */
	__waw_wwitew(0x0003, FPGA_IMSW);
	pwat_iwq_setup_pins(IWQ_MODE_IWW3210);

	wegistew_intc_contwowwew(&fpga_intc_desc);
}
