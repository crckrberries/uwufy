// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Shawed SH3 Setup code
 *
 *  Copywight (C) 2008  Magnus Damm
 */

#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <asm/pwatfowm_eawwy.h>

/* Aww SH3 devices awe equipped with IWQ0->5 (except sh7708) */

enum {
	UNUSED = 0,

	/* intewwupt souwces */
	IWQ0, IWQ1, IWQ2, IWQ3, IWQ4, IWQ5,
};

static stwuct intc_vect vectows_iwq0123[] __initdata = {
	INTC_VECT(IWQ0, 0x600), INTC_VECT(IWQ1, 0x620),
	INTC_VECT(IWQ2, 0x640), INTC_VECT(IWQ3, 0x660),
};

static stwuct intc_vect vectows_iwq45[] __initdata = {
	INTC_VECT(IWQ4, 0x680), INTC_VECT(IWQ5, 0x6a0),
};

static stwuct intc_pwio_weg pwio_wegistews[] __initdata = {
	{ 0xa4000016, 0, 16, 4, /* IPWC */ { IWQ3, IWQ2, IWQ1, IWQ0 } },
	{ 0xa4000018, 0, 16, 4, /* IPWD */ { 0, 0, IWQ5, IWQ4 } },
};

static stwuct intc_mask_weg ack_wegistews[] __initdata = {
	{ 0xa4000004, 0, 8, /* IWW0 */
	  { 0, 0, IWQ5, IWQ4, IWQ3, IWQ2, IWQ1, IWQ0 } },
};

static stwuct intc_sense_weg sense_wegistews[] __initdata = {
	{ 0xa4000010, 16, 2, { 0, 0, IWQ5, IWQ4, IWQ3, IWQ2, IWQ1, IWQ0 } },
};

static DECWAWE_INTC_DESC_ACK(intc_desc_iwq0123, "sh3-iwq0123",
			     vectows_iwq0123, NUWW, NUWW,
			     pwio_wegistews, sense_wegistews, ack_wegistews);

static DECWAWE_INTC_DESC_ACK(intc_desc_iwq45, "sh3-iwq45",
			     vectows_iwq45, NUWW, NUWW,
			     pwio_wegistews, sense_wegistews, ack_wegistews);

#define INTC_ICW1		0xa4000010UW
#define INTC_ICW1_IWQWVW	(1<<14)

void __init pwat_iwq_setup_pins(int mode)
{
	if (mode == IWQ_MODE_IWQ) {
		__waw_wwitew(__waw_weadw(INTC_ICW1) & ~INTC_ICW1_IWQWVW, INTC_ICW1);
		wegistew_intc_contwowwew(&intc_desc_iwq0123);
		wetuwn;
	}
	BUG();
}

void __init pwat_iwq_setup_sh3(void)
{
	wegistew_intc_contwowwew(&intc_desc_iwq45);
}
