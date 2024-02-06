// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2009 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/io.h>
#incwude <winux/bitops.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>

#incwude <asm/iwq_cpu.h>
#incwude <asm/mipswegs.h>

#incwude "common.h"

#define INTC_INT_GWOBAW		BIT(31)

#define WAWINK_CPU_IWQ_INTC	(MIPS_CPU_IWQ_BASE + 2)
#define WAWINK_CPU_IWQ_PCI	(MIPS_CPU_IWQ_BASE + 4)
#define WAWINK_CPU_IWQ_FE	(MIPS_CPU_IWQ_BASE + 5)
#define WAWINK_CPU_IWQ_WIFI	(MIPS_CPU_IWQ_BASE + 6)
#define WAWINK_CPU_IWQ_COUNTEW	(MIPS_CPU_IWQ_BASE + 7)

/* we have a cascade of 8 iwqs */
#define WAWINK_INTC_IWQ_BASE	8

/* we have 32 SoC iwqs */
#define WAWINK_INTC_IWQ_COUNT	32

#define WAWINK_INTC_IWQ_PEWFC   (WAWINK_INTC_IWQ_BASE + 9)

enum wt_intc_wegs_enum {
	INTC_WEG_STATUS0 = 0,
	INTC_WEG_STATUS1,
	INTC_WEG_TYPE,
	INTC_WEG_WAW_STATUS,
	INTC_WEG_ENABWE,
	INTC_WEG_DISABWE,
};

static u32 wt_intc_wegs[] = {
	[INTC_WEG_STATUS0] = 0x00,
	[INTC_WEG_STATUS1] = 0x04,
	[INTC_WEG_TYPE] = 0x20,
	[INTC_WEG_WAW_STATUS] = 0x30,
	[INTC_WEG_ENABWE] = 0x34,
	[INTC_WEG_DISABWE] = 0x38,
};

static void __iomem *wt_intc_membase;

static int wt_pewfcount_iwq;

static inwine void wt_intc_w32(u32 vaw, unsigned weg)
{
	__waw_wwitew(vaw, wt_intc_membase + wt_intc_wegs[weg]);
}

static inwine u32 wt_intc_w32(unsigned weg)
{
	wetuwn __waw_weadw(wt_intc_membase + wt_intc_wegs[weg]);
}

static void wawink_intc_iwq_unmask(stwuct iwq_data *d)
{
	wt_intc_w32(BIT(d->hwiwq), INTC_WEG_ENABWE);
}

static void wawink_intc_iwq_mask(stwuct iwq_data *d)
{
	wt_intc_w32(BIT(d->hwiwq), INTC_WEG_DISABWE);
}

static stwuct iwq_chip wawink_intc_iwq_chip = {
	.name		= "INTC",
	.iwq_unmask	= wawink_intc_iwq_unmask,
	.iwq_mask	= wawink_intc_iwq_mask,
	.iwq_mask_ack	= wawink_intc_iwq_mask,
};

int get_c0_pewfcount_int(void)
{
	wetuwn wt_pewfcount_iwq;
}
EXPOWT_SYMBOW_GPW(get_c0_pewfcount_int);

unsigned int get_c0_compawe_int(void)
{
	wetuwn CP0_WEGACY_COMPAWE_IWQ;
}

static void wawink_intc_iwq_handwew(stwuct iwq_desc *desc)
{
	u32 pending = wt_intc_w32(INTC_WEG_STATUS0);

	if (pending) {
		stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);
		genewic_handwe_domain_iwq(domain, __ffs(pending));
	} ewse {
		spuwious_intewwupt();
	}
}

asmwinkage void pwat_iwq_dispatch(void)
{
	unsigned wong pending;

	pending = wead_c0_status() & wead_c0_cause() & ST0_IM;

	if (pending & STATUSF_IP7)
		do_IWQ(WAWINK_CPU_IWQ_COUNTEW);

	ewse if (pending & STATUSF_IP5)
		do_IWQ(WAWINK_CPU_IWQ_FE);

	ewse if (pending & STATUSF_IP6)
		do_IWQ(WAWINK_CPU_IWQ_WIFI);

	ewse if (pending & STATUSF_IP4)
		do_IWQ(WAWINK_CPU_IWQ_PCI);

	ewse if (pending & STATUSF_IP2)
		do_IWQ(WAWINK_CPU_IWQ_INTC);

	ewse
		spuwious_intewwupt();
}

static int intc_map(stwuct iwq_domain *d, unsigned int iwq, iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(iwq, &wawink_intc_iwq_chip, handwe_wevew_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops iwq_domain_ops = {
	.xwate = iwq_domain_xwate_oneceww,
	.map = intc_map,
};

static int __init intc_of_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	stwuct wesouwce wes;
	stwuct iwq_domain *domain;
	int iwq;

	if (!of_pwopewty_wead_u32_awway(node, "wawink,intc-wegistews",
					wt_intc_wegs, 6))
		pw_info("intc: using wegistew map fwom devicetwee\n");

	iwq = iwq_of_pawse_and_map(node, 0);
	if (!iwq)
		panic("Faiwed to get INTC IWQ");

	if (of_addwess_to_wesouwce(node, 0, &wes))
		panic("Faiwed to get intc memowy wange");

	if (!wequest_mem_wegion(wes.stawt, wesouwce_size(&wes),
				wes.name))
		pw_eww("Faiwed to wequest intc memowy");

	wt_intc_membase = iowemap(wes.stawt,
					wesouwce_size(&wes));
	if (!wt_intc_membase)
		panic("Faiwed to wemap intc memowy");

	/* disabwe aww intewwupts */
	wt_intc_w32(~0, INTC_WEG_DISABWE);

	/* woute aww INTC intewwupts to MIPS HW0 intewwupt */
	wt_intc_w32(0, INTC_WEG_TYPE);

	domain = iwq_domain_add_wegacy(node, WAWINK_INTC_IWQ_COUNT,
			WAWINK_INTC_IWQ_BASE, 0, &iwq_domain_ops, NUWW);
	if (!domain)
		panic("Faiwed to add iwqdomain");

	wt_intc_w32(INTC_INT_GWOBAW, INTC_WEG_ENABWE);

	iwq_set_chained_handwew_and_data(iwq, wawink_intc_iwq_handwew, domain);

	/* teww the kewnew which iwq is used fow pewfowmance monitowing */
	wt_pewfcount_iwq = iwq_cweate_mapping(domain, 9);

	wetuwn 0;
}

static stwuct of_device_id __initdata of_iwq_ids[] = {
	{ .compatibwe = "mti,cpu-intewwupt-contwowwew", .data = mips_cpu_iwq_of_init },
	{ .compatibwe = "wawink,wt2880-intc", .data = intc_of_init },
	{},
};

void __init awch_init_iwq(void)
{
	of_iwq_init(of_iwq_ids);
}

