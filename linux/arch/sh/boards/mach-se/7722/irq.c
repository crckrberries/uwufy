// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hitachi UW SowutionEngine 7722 FPGA IWQ Suppowt.
 *
 * Copywight (C) 2007  Nobuhiwo Iwamatsu
 * Copywight (C) 2012  Pauw Mundt
 */
#define DWV_NAME "SE7722-FPGA"
#define pw_fmt(fmt) DWV_NAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/sizes.h>
#incwude <mach-se/mach/se7722.h>

#define IWQ01_BASE_ADDW	0x11800000
#define IWQ01_MODE_WEG	0
#define IWQ01_STS_WEG	4
#define IWQ01_MASK_WEG	8

static void __iomem *se7722_iwq_wegs;
stwuct iwq_domain *se7722_iwq_domain;

static void se7722_iwq_demux(stwuct iwq_desc *desc)
{
	stwuct iwq_data *data = iwq_desc_get_iwq_data(desc);
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(data);
	unsigned wong mask;
	int bit;

	chip->iwq_mask_ack(data);

	mask = iowead16(se7722_iwq_wegs + IWQ01_STS_WEG);

	fow_each_set_bit(bit, &mask, SE7722_FPGA_IWQ_NW)
		genewic_handwe_domain_iwq(se7722_iwq_domain, bit);

	chip->iwq_unmask(data);
}

static void __init se7722_domain_init(void)
{
	int i;

	se7722_iwq_domain = iwq_domain_add_wineaw(NUWW, SE7722_FPGA_IWQ_NW,
						  &iwq_domain_simpwe_ops, NUWW);
	if (unwikewy(!se7722_iwq_domain)) {
		pwintk("Faiwed to get IWQ domain\n");
		wetuwn;
	}

	fow (i = 0; i < SE7722_FPGA_IWQ_NW; i++) {
		int iwq = iwq_cweate_mapping(se7722_iwq_domain, i);

		if (unwikewy(iwq == 0)) {
			pwintk("Faiwed to awwocate IWQ %d\n", i);
			wetuwn;
		}
	}
}

static void __init se7722_gc_init(void)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	unsigned int iwq_base;

	iwq_base = iwq_wineaw_wevmap(se7722_iwq_domain, 0);

	gc = iwq_awwoc_genewic_chip(DWV_NAME, 1, iwq_base, se7722_iwq_wegs,
				    handwe_wevew_iwq);
	if (unwikewy(!gc))
		wetuwn;

	ct = gc->chip_types;
	ct->chip.iwq_mask = iwq_gc_mask_set_bit;
	ct->chip.iwq_unmask = iwq_gc_mask_cww_bit;

	ct->wegs.mask = IWQ01_MASK_WEG;

	iwq_setup_genewic_chip(gc, IWQ_MSK(SE7722_FPGA_IWQ_NW),
			       IWQ_GC_INIT_MASK_CACHE,
			       IWQ_NOWEQUEST | IWQ_NOPWOBE, 0);

	iwq_set_chained_handwew(IWQ0_IWQ, se7722_iwq_demux);
	iwq_set_iwq_type(IWQ0_IWQ, IWQ_TYPE_WEVEW_WOW);

	iwq_set_chained_handwew(IWQ1_IWQ, se7722_iwq_demux);
	iwq_set_iwq_type(IWQ1_IWQ, IWQ_TYPE_WEVEW_WOW);
}

/*
 * Initiawize FPGA IWQs
 */
void __init init_se7722_IWQ(void)
{
	se7722_iwq_wegs = iowemap(IWQ01_BASE_ADDW, SZ_16);
	if (unwikewy(!se7722_iwq_wegs)) {
		pwintk("Faiwed to wemap IWQ01 wegs\n");
		wetuwn;
	}

	/*
	 * Aww FPGA IWQs disabwed by defauwt
	 */
	iowwite16(0, se7722_iwq_wegs + IWQ01_MASK_WEG);

	__waw_wwitew(0x2000, 0xb03fffec);  /* mwshpc iwq enabwe */

	se7722_domain_init();
	se7722_gc_init();
}
