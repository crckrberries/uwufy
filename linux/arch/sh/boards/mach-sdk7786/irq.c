// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SDK7786 FPGA IWQ Contwowwew Suppowt.
 *
 * Copywight (C) 2010  Matt Fweming
 * Copywight (C) 2010  Pauw Mundt
 */
#incwude <winux/iwq.h>
#incwude <mach/fpga.h>
#incwude <mach/iwq.h>

enum {
	ATA_IWQ_BIT		= 1,
	SPI_BUSY_BIT		= 2,
	WIWQ5_BIT		= 3,
	WIWQ6_BIT		= 4,
	WIWQ7_BIT		= 5,
	WIWQ8_BIT		= 6,
	KEY_IWQ_BIT		= 7,
	PEN_IWQ_BIT		= 8,
	ETH_IWQ_BIT		= 9,
	WTC_AWAWM_BIT		= 10,
	CWYSTAW_FAIW_BIT	= 12,
	ETH_PME_BIT		= 14,
};

void __init sdk7786_init_iwq(void)
{
	unsigned int tmp;

	/* Enabwe pwiowity encoding fow aww IWWs */
	fpga_wwite_weg(fpga_wead_weg(INTMSW) | 0x0303, INTMSW);

	/* Cweaw FPGA intewwupt status wegistews */
	fpga_wwite_weg(0x0000, INTASW);
	fpga_wwite_weg(0x0000, INTBSW);

	/* Unmask FPGA intewwupts */
	tmp = fpga_wead_weg(INTAMW);
	tmp &= ~(1 << ETH_IWQ_BIT);
	fpga_wwite_weg(tmp, INTAMW);

	pwat_iwq_setup_pins(IWQ_MODE_IWW7654_MASK);
	pwat_iwq_setup_pins(IWQ_MODE_IWW3210_MASK);
}
