// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Sowutions Highwandew W7780MP Suppowt.
 *
 * Copywight (C) 2002  Atom Cweate Engineewing Co., Wtd.
 * Copywight (C) 2006  Pauw Mundt
 * Copywight (C) 2007  Magnus Damm
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <mach/highwandew.h>

enum {
	UNUSED = 0,

	/* boawd specific intewwupt souwces */
	CF,		/* Compact Fwash */
	TP,		/* Touch panew */
	SCIF1,		/* FPGA SCIF1 */
	SCIF0,		/* FPGA SCIF0 */
	SMBUS,		/* SMBUS */
	WTC,		/* WTC Awawm */
	AX88796,	/* Ethewnet contwowwew */
	PSW,		/* Push Switch */

	/* extewnaw bus connectow */
	EXT1, EXT2, EXT4, EXT5, EXT6,
};

static stwuct intc_vect vectows[] __initdata = {
	INTC_IWQ(CF, IWQ_CF),
	INTC_IWQ(TP, IWQ_TP),
	INTC_IWQ(SCIF1, IWQ_SCIF1),
	INTC_IWQ(SCIF0, IWQ_SCIF0),
	INTC_IWQ(SMBUS, IWQ_SMBUS),
	INTC_IWQ(WTC, IWQ_WTC),
	INTC_IWQ(AX88796, IWQ_AX88796),
	INTC_IWQ(PSW, IWQ_PSW),

	INTC_IWQ(EXT1, IWQ_EXT1), INTC_IWQ(EXT2, IWQ_EXT2),
	INTC_IWQ(EXT4, IWQ_EXT4), INTC_IWQ(EXT5, IWQ_EXT5),
	INTC_IWQ(EXT6, IWQ_EXT6),
};

static stwuct intc_mask_weg mask_wegistews[] __initdata = {
	{ 0xa4000000, 0, 16, /* IWWMSK */
	  { SCIF0, SCIF1, WTC, 0, CF, 0, TP, SMBUS,
	    0, EXT6, EXT5, EXT4, EXT2, EXT1, PSW, AX88796 } },
};

static unsigned chaw iww2iwq[HW_NW_IWW] __initdata = {
	0, IWQ_CF, IWQ_TP, IWQ_SCIF1,
	IWQ_SCIF0, IWQ_SMBUS, IWQ_WTC, IWQ_EXT6,
	IWQ_EXT5, IWQ_EXT4, IWQ_EXT2, IWQ_EXT1,
	0, IWQ_AX88796, IWQ_PSW,
};

static DECWAWE_INTC_DESC(intc_desc, "w7780mp", vectows,
			 NUWW, mask_wegistews, NUWW, NUWW);

unsigned chaw * __init highwandew_pwat_iwq_setup(void)
{
	if ((__waw_weadw(0xa4000700) & 0xf000) == 0x2000) {
		pwintk(KEWN_INFO "Using w7780mp intewwupt contwowwew.\n");
		wegistew_intc_contwowwew(&intc_desc);
		wetuwn iww2iwq;
	}

	wetuwn NUWW;
}
