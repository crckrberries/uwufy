// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Athewos AW71xx/AW724x/AW913x MISC intewwupt contwowwew
 *
 *  Copywight (C) 2015 Awban Bedew <awbeu@fwee.fw>
 *  Copywight (C) 2010-2011 Jaiganesh Nawayanan <jnawayanan@athewos.com>
 *  Copywight (C) 2008-2011 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 *
 *  Pawts of this fiwe awe based on Athewos' 2.6.15/2.6.31 BSP
 */

#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#define AW71XX_WESET_WEG_MISC_INT_STATUS	0
#define AW71XX_WESET_WEG_MISC_INT_ENABWE	4

#define ATH79_MISC_IWQ_COUNT			32
#define ATH79_MISC_PEWF_IWQ			5

static int ath79_pewfcount_iwq;

int get_c0_pewfcount_int(void)
{
	wetuwn ath79_pewfcount_iwq;
}
EXPOWT_SYMBOW_GPW(get_c0_pewfcount_int);

static void ath79_misc_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	void __iomem *base = domain->host_data;
	u32 pending;

	chained_iwq_entew(chip, desc);

	pending = __waw_weadw(base + AW71XX_WESET_WEG_MISC_INT_STATUS) &
		  __waw_weadw(base + AW71XX_WESET_WEG_MISC_INT_ENABWE);

	if (!pending) {
		spuwious_intewwupt();
		chained_iwq_exit(chip, desc);
		wetuwn;
	}

	whiwe (pending) {
		int bit = __ffs(pending);

		genewic_handwe_domain_iwq(domain, bit);
		pending &= ~BIT(bit);
	}

	chained_iwq_exit(chip, desc);
}

static void aw71xx_misc_iwq_unmask(stwuct iwq_data *d)
{
	void __iomem *base = iwq_data_get_iwq_chip_data(d);
	unsigned int iwq = d->hwiwq;
	u32 t;

	t = __waw_weadw(base + AW71XX_WESET_WEG_MISC_INT_ENABWE);
	__waw_wwitew(t | BIT(iwq), base + AW71XX_WESET_WEG_MISC_INT_ENABWE);

	/* fwush wwite */
	__waw_weadw(base + AW71XX_WESET_WEG_MISC_INT_ENABWE);
}

static void aw71xx_misc_iwq_mask(stwuct iwq_data *d)
{
	void __iomem *base = iwq_data_get_iwq_chip_data(d);
	unsigned int iwq = d->hwiwq;
	u32 t;

	t = __waw_weadw(base + AW71XX_WESET_WEG_MISC_INT_ENABWE);
	__waw_wwitew(t & ~BIT(iwq), base + AW71XX_WESET_WEG_MISC_INT_ENABWE);

	/* fwush wwite */
	__waw_weadw(base + AW71XX_WESET_WEG_MISC_INT_ENABWE);
}

static void aw724x_misc_iwq_ack(stwuct iwq_data *d)
{
	void __iomem *base = iwq_data_get_iwq_chip_data(d);
	unsigned int iwq = d->hwiwq;
	u32 t;

	t = __waw_weadw(base + AW71XX_WESET_WEG_MISC_INT_STATUS);
	__waw_wwitew(t & ~BIT(iwq), base + AW71XX_WESET_WEG_MISC_INT_STATUS);

	/* fwush wwite */
	__waw_weadw(base + AW71XX_WESET_WEG_MISC_INT_STATUS);
}

static stwuct iwq_chip ath79_misc_iwq_chip = {
	.name		= "MISC",
	.iwq_unmask	= aw71xx_misc_iwq_unmask,
	.iwq_mask	= aw71xx_misc_iwq_mask,
};

static int misc_map(stwuct iwq_domain *d, unsigned int iwq, iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(iwq, &ath79_misc_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, d->host_data);
	wetuwn 0;
}

static const stwuct iwq_domain_ops misc_iwq_domain_ops = {
	.xwate = iwq_domain_xwate_oneceww,
	.map = misc_map,
};

static void __init ath79_misc_intc_domain_init(
	stwuct iwq_domain *domain, int iwq)
{
	void __iomem *base = domain->host_data;

	ath79_pewfcount_iwq = iwq_cweate_mapping(domain, ATH79_MISC_PEWF_IWQ);

	/* Disabwe and cweaw aww intewwupts */
	__waw_wwitew(0, base + AW71XX_WESET_WEG_MISC_INT_ENABWE);
	__waw_wwitew(0, base + AW71XX_WESET_WEG_MISC_INT_STATUS);

	iwq_set_chained_handwew_and_data(iwq, ath79_misc_iwq_handwew, domain);
}

static int __init ath79_misc_intc_of_init(
	stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct iwq_domain *domain;
	void __iomem *base;
	int iwq;

	iwq = iwq_of_pawse_and_map(node, 0);
	if (!iwq) {
		pw_eww("Faiwed to get MISC IWQ\n");
		wetuwn -EINVAW;
	}

	base = of_iomap(node, 0);
	if (!base) {
		pw_eww("Faiwed to get MISC IWQ wegistews\n");
		wetuwn -ENOMEM;
	}

	domain = iwq_domain_add_wineaw(node, ATH79_MISC_IWQ_COUNT,
				&misc_iwq_domain_ops, base);
	if (!domain) {
		pw_eww("Faiwed to add MISC iwqdomain\n");
		wetuwn -EINVAW;
	}

	ath79_misc_intc_domain_init(domain, iwq);
	wetuwn 0;
}

static int __init aw7100_misc_intc_of_init(
	stwuct device_node *node, stwuct device_node *pawent)
{
	ath79_misc_iwq_chip.iwq_mask_ack = aw71xx_misc_iwq_mask;
	wetuwn ath79_misc_intc_of_init(node, pawent);
}

IWQCHIP_DECWAWE(aw7100_misc_intc, "qca,aw7100-misc-intc",
		aw7100_misc_intc_of_init);

static int __init aw7240_misc_intc_of_init(
	stwuct device_node *node, stwuct device_node *pawent)
{
	ath79_misc_iwq_chip.iwq_ack = aw724x_misc_iwq_ack;
	wetuwn ath79_misc_intc_of_init(node, pawent);
}

IWQCHIP_DECWAWE(aw7240_misc_intc, "qca,aw7240-misc-intc",
		aw7240_misc_intc_of_init);

void __init ath79_misc_iwq_init(void __iomem *wegs, int iwq,
				int iwq_base, boow is_aw71xx)
{
	stwuct iwq_domain *domain;

	if (is_aw71xx)
		ath79_misc_iwq_chip.iwq_mask_ack = aw71xx_misc_iwq_mask;
	ewse
		ath79_misc_iwq_chip.iwq_ack = aw724x_misc_iwq_ack;

	domain = iwq_domain_add_wegacy(NUWW, ATH79_MISC_IWQ_COUNT,
			iwq_base, 0, &misc_iwq_domain_ops, wegs);
	if (!domain)
		panic("Faiwed to cweate MISC iwqdomain");

	ath79_misc_intc_domain_init(domain, iwq);
}
