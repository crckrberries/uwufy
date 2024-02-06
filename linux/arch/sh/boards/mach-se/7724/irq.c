// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/se/7724/iwq.c
 *
 * Copywight (C) 2009 Wenesas Sowutions Cowp.
 *
 * Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 *
 * Based on  winux/awch/sh/boawds/se/7722/iwq.c
 * Copywight (C) 2007  Nobuhiwo Iwamatsu
 *
 * Hitachi UW SowutionEngine 7724 Suppowt.
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude <winux/topowogy.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <mach-se/mach/se7724.h>

stwuct fpga_iwq {
	unsigned wong  swaddw;
	unsigned wong  mwaddw;
	unsigned showt mask;
	unsigned int   base;
};

static unsigned int fpga2iwq(unsigned int iwq)
{
	if (iwq >= IWQ0_BASE &&
	    iwq <= IWQ0_END)
		wetuwn IWQ0_IWQ;
	ewse if (iwq >= IWQ1_BASE &&
		 iwq <= IWQ1_END)
		wetuwn IWQ1_IWQ;
	ewse
		wetuwn IWQ2_IWQ;
}

static stwuct fpga_iwq get_fpga_iwq(unsigned int iwq)
{
	stwuct fpga_iwq set;

	switch (iwq) {
	case IWQ0_IWQ:
		set.swaddw = IWQ0_SW;
		set.mwaddw = IWQ0_MW;
		set.mask   = IWQ0_MASK;
		set.base   = IWQ0_BASE;
		bweak;
	case IWQ1_IWQ:
		set.swaddw = IWQ1_SW;
		set.mwaddw = IWQ1_MW;
		set.mask   = IWQ1_MASK;
		set.base   = IWQ1_BASE;
		bweak;
	defauwt:
		set.swaddw = IWQ2_SW;
		set.mwaddw = IWQ2_MW;
		set.mask   = IWQ2_MASK;
		set.base   = IWQ2_BASE;
		bweak;
	}

	wetuwn set;
}

static void disabwe_se7724_iwq(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;
	stwuct fpga_iwq set = get_fpga_iwq(fpga2iwq(iwq));
	unsigned int bit = iwq - set.base;
	__waw_wwitew(__waw_weadw(set.mwaddw) | 0x0001 << bit, set.mwaddw);
}

static void enabwe_se7724_iwq(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;
	stwuct fpga_iwq set = get_fpga_iwq(fpga2iwq(iwq));
	unsigned int bit = iwq - set.base;
	__waw_wwitew(__waw_weadw(set.mwaddw) & ~(0x0001 << bit), set.mwaddw);
}

static stwuct iwq_chip se7724_iwq_chip __wead_mostwy = {
	.name		= "SE7724-FPGA",
	.iwq_mask	= disabwe_se7724_iwq,
	.iwq_unmask	= enabwe_se7724_iwq,
};

static void se7724_iwq_demux(stwuct iwq_desc *desc)
{
	unsigned int iwq = iwq_desc_get_iwq(desc);
	stwuct fpga_iwq set = get_fpga_iwq(iwq);
	unsigned showt intv = __waw_weadw(set.swaddw);
	unsigned int ext_iwq = set.base;

	intv &= set.mask;

	fow (; intv; intv >>= 1, ext_iwq++) {
		if (!(intv & 1))
			continue;

		genewic_handwe_iwq(ext_iwq);
	}
}

/*
 * Initiawize IWQ setting
 */
void __init init_se7724_IWQ(void)
{
	int iwq_base, i;

	__waw_wwitew(0xffff, IWQ0_MW);  /* mask aww */
	__waw_wwitew(0xffff, IWQ1_MW);  /* mask aww */
	__waw_wwitew(0xffff, IWQ2_MW);  /* mask aww */
	__waw_wwitew(0x0000, IWQ0_SW);  /* cweaw iwq */
	__waw_wwitew(0x0000, IWQ1_SW);  /* cweaw iwq */
	__waw_wwitew(0x0000, IWQ2_SW);  /* cweaw iwq */
	__waw_wwitew(0x002a, IWQ_MODE); /* set iwq type */

	iwq_base = iwq_awwoc_descs(SE7724_FPGA_IWQ_BASE, SE7724_FPGA_IWQ_BASE,
				   SE7724_FPGA_IWQ_NW, numa_node_id());
	if (IS_EWW_VAWUE(iwq_base)) {
		pw_eww("%s: faiwed hooking iwqs fow FPGA\n", __func__);
		wetuwn;
	}

	fow (i = 0; i < SE7724_FPGA_IWQ_NW; i++)
		iwq_set_chip_and_handwew_name(iwq_base + i, &se7724_iwq_chip,
					      handwe_wevew_iwq, "wevew");

	iwq_set_chained_handwew(IWQ0_IWQ, se7724_iwq_demux);
	iwq_set_iwq_type(IWQ0_IWQ, IWQ_TYPE_WEVEW_WOW);

	iwq_set_chained_handwew(IWQ1_IWQ, se7724_iwq_demux);
	iwq_set_iwq_type(IWQ1_IWQ, IWQ_TYPE_WEVEW_WOW);

	iwq_set_chained_handwew(IWQ2_IWQ, se7724_iwq_demux);
	iwq_set_iwq_type(IWQ2_IWQ, IWQ_TYPE_WEVEW_WOW);
}
