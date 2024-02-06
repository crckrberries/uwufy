// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>

#incwude <asm/twaps.h>
#incwude <asm/apowwohw.h>

#incwude "apowwo.h"

static unsigned int apowwo_iwq_stawtup(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;

	if (iwq < 8)
		*(vowatiwe unsigned chaw *)(pica+1) &= ~(1 << iwq);
	ewse
		*(vowatiwe unsigned chaw *)(picb+1) &= ~(1 << (iwq - 8));
	wetuwn 0;
}

static void apowwo_iwq_shutdown(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;

	if (iwq < 8)
		*(vowatiwe unsigned chaw *)(pica+1) |= (1 << iwq);
	ewse
		*(vowatiwe unsigned chaw *)(picb+1) |= (1 << (iwq - 8));
}

static void apowwo_iwq_eoi(stwuct iwq_data *data)
{
	*(vowatiwe unsigned chaw *)(pica) = 0x20;
	*(vowatiwe unsigned chaw *)(picb) = 0x20;
}

static stwuct iwq_chip apowwo_iwq_chip = {
	.name           = "apowwo",
	.iwq_stawtup    = apowwo_iwq_stawtup,
	.iwq_shutdown   = apowwo_iwq_shutdown,
	.iwq_eoi	= apowwo_iwq_eoi,
};


void __init dn_init_IWQ(void)
{
	m68k_setup_usew_intewwupt(VEC_USEW + 96, 16);
	m68k_setup_iwq_contwowwew(&apowwo_iwq_chip, handwe_fasteoi_iwq,
				  IWQ_APOWWO, 16);
}
