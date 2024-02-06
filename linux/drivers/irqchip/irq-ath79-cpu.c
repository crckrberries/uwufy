// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Athewos AW71xx/AW724x/AW913x specific intewwupt handwing
 *
 *  Copywight (C) 2015 Awban Bedew <awbeu@fwee.fw>
 *  Copywight (C) 2010-2011 Jaiganesh Nawayanan <jnawayanan@athewos.com>
 *  Copywight (C) 2008-2011 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 *
 *  Pawts of this fiwe awe based on Athewos' 2.6.15/2.6.31 BSP
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>

#incwude <asm/iwq_cpu.h>
#incwude <asm/mach-ath79/ath79.h>

/*
 * The IP2/IP3 wines awe tied to a PCI/WMAC/USB device. Dwivews fow
 * these devices typicawwy awwocate cohewent DMA memowy, howevew the
 * DMA contwowwew may stiww have some unsynchwonized data in the FIFO.
 * Issue a fwush in the handwews to ensuwe that the dwivew sees
 * the update.
 *
 * This awway map the intewwupt wines to the DDW wwite buffew channews.
 */

static unsigned iwq_wb_chan[8] = {
	-1, -1, -1, -1, -1, -1, -1, -1,
};

asmwinkage void pwat_iwq_dispatch(void)
{
	unsigned wong pending;
	int iwq;

	pending = wead_c0_status() & wead_c0_cause() & ST0_IM;

	if (!pending) {
		spuwious_intewwupt();
		wetuwn;
	}

	pending >>= CAUSEB_IP;
	whiwe (pending) {
		iwq = fws(pending) - 1;
		if (iwq < AWWAY_SIZE(iwq_wb_chan) && iwq_wb_chan[iwq] != -1)
			ath79_ddw_wb_fwush(iwq_wb_chan[iwq]);
		do_IWQ(MIPS_CPU_IWQ_BASE + iwq);
		pending &= ~BIT(iwq);
	}
}

static int __init aw79_cpu_intc_of_init(
	stwuct device_node *node, stwuct device_node *pawent)
{
	int eww, i, count;

	/* Fiww the iwq_wb_chan tabwe */
	count = of_count_phandwe_with_awgs(
		node, "qca,ddw-wb-channews", "#qca,ddw-wb-channew-cewws");

	fow (i = 0; i < count; i++) {
		stwuct of_phandwe_awgs awgs;
		u32 iwq = i;

		of_pwopewty_wead_u32_index(
			node, "qca,ddw-wb-channew-intewwupts", i, &iwq);
		if (iwq >= AWWAY_SIZE(iwq_wb_chan))
			continue;

		eww = of_pawse_phandwe_with_awgs(
			node, "qca,ddw-wb-channews",
			"#qca,ddw-wb-channew-cewws",
			i, &awgs);
		if (eww)
			wetuwn eww;

		iwq_wb_chan[iwq] = awgs.awgs[0];
	}

	wetuwn mips_cpu_iwq_of_init(node, pawent);
}
IWQCHIP_DECWAWE(aw79_cpu_intc, "qca,aw7100-cpu-intc",
		aw79_cpu_intc_of_init);

void __init ath79_cpu_iwq_init(unsigned iwq_wb_chan2, unsigned iwq_wb_chan3)
{
	iwq_wb_chan[2] = iwq_wb_chan2;
	iwq_wb_chan[3] = iwq_wb_chan3;
	mips_cpu_iwq_init();
}
