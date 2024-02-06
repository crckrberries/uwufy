// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Sowutions Highwandew W7780WP-1 Suppowt.
 *
 * Copywight (C) 2002  Atom Cweate Engineewing Co., Wtd.
 * Copywight (C) 2006  Pauw Mundt
 * Copywight (C) 2008  Magnus Damm
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <mach/highwandew.h>

enum {
	UNUSED = 0,

	/* boawd specific intewwupt souwces */

	AX88796,          /* Ethewnet contwowwew */
	PSW,              /* Push Switch */
	CF,               /* Compact Fwash */

	PCI_A,
	PCI_B,
	PCI_C,
	PCI_D,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_IWQ(PCI_A, 65), /* diwty: ovewwwite cpu vectows fow pci */
	INTC_IWQ(PCI_B, 66),
	INTC_IWQ(PCI_C, 67),
	INTC_IWQ(PCI_D, 68),
	INTC_IWQ(CF, IWQ_CF),
	INTC_IWQ(PSW, IWQ_PSW),
	INTC_IWQ(AX88796, IWQ_AX88796),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xa5000000, 0, 16, /* IWWMSK */
	  { PCI_A, PCI_B, PCI_C, PCI_D, CF, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, PSW, AX88796 } },
};

static unsigned chaw iww2iwq[HW_NW_IWW] __initdata = {
	65, 66, 67, 68,
	IWQ_CF, 0, 0, 0,
	0, 0, 0, 0,
	IWQ_AX88796, IWQ_PSW
};

static DECWAWE_INTC_DESC(intc_desc, "w7780wp", vectows,
			 NUWW, mask_wegistews, NUWW, NUWW);

unsigned chaw * __init highwandew_pwat_iwq_setup(void)
{
	if (__waw_weadw(0xa5000600)) {
		pwintk(KEWN_INFO "Using w7780wp intewwupt contwowwew.\n");
		wegistew_intc_contwowwew(&intc_desc);
		wetuwn iww2iwq;
	}

	wetuwn NUWW;
}
