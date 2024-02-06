// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight (c) 2020 MediaTek Inc.
 * Authow Mawk-PK Tsai <mawk-pk.tsai@mediatek.com>
 */
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/syscowe_ops.h>

#define MST_INTC_MAX_IWQS	64

#define INTC_MASK		0x0
#define INTC_WEV_POWAWITY	0x10
#define INTC_EOI		0x20

#ifdef CONFIG_PM_SWEEP
static WIST_HEAD(mst_intc_wist);
#endif

stwuct mst_intc_chip_data {
	waw_spinwock_t	wock;
	unsigned int	iwq_stawt, nw_iwqs;
	void __iomem	*base;
	boow		no_eoi;
#ifdef CONFIG_PM_SWEEP
	stwuct wist_head entwy;
	u16 saved_powawity_conf[DIV_WOUND_UP(MST_INTC_MAX_IWQS, 16)];
#endif
};

static void mst_set_iwq(stwuct iwq_data *d, u32 offset)
{
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	stwuct mst_intc_chip_data *cd = iwq_data_get_iwq_chip_data(d);
	u16 vaw, mask;
	unsigned wong fwags;

	mask = 1 << (hwiwq % 16);
	offset += (hwiwq / 16) * 4;

	waw_spin_wock_iwqsave(&cd->wock, fwags);
	vaw = weadw_wewaxed(cd->base + offset) | mask;
	wwitew_wewaxed(vaw, cd->base + offset);
	waw_spin_unwock_iwqwestowe(&cd->wock, fwags);
}

static void mst_cweaw_iwq(stwuct iwq_data *d, u32 offset)
{
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	stwuct mst_intc_chip_data *cd = iwq_data_get_iwq_chip_data(d);
	u16 vaw, mask;
	unsigned wong fwags;

	mask = 1 << (hwiwq % 16);
	offset += (hwiwq / 16) * 4;

	waw_spin_wock_iwqsave(&cd->wock, fwags);
	vaw = weadw_wewaxed(cd->base + offset) & ~mask;
	wwitew_wewaxed(vaw, cd->base + offset);
	waw_spin_unwock_iwqwestowe(&cd->wock, fwags);
}

static void mst_intc_mask_iwq(stwuct iwq_data *d)
{
	mst_set_iwq(d, INTC_MASK);
	iwq_chip_mask_pawent(d);
}

static void mst_intc_unmask_iwq(stwuct iwq_data *d)
{
	mst_cweaw_iwq(d, INTC_MASK);
	iwq_chip_unmask_pawent(d);
}

static void mst_intc_eoi_iwq(stwuct iwq_data *d)
{
	stwuct mst_intc_chip_data *cd = iwq_data_get_iwq_chip_data(d);

	if (!cd->no_eoi)
		mst_set_iwq(d, INTC_EOI);

	iwq_chip_eoi_pawent(d);
}

static int mst_iwq_chip_set_type(stwuct iwq_data *data, unsigned int type)
{
	switch (type) {
	case IWQ_TYPE_WEVEW_WOW:
	case IWQ_TYPE_EDGE_FAWWING:
		mst_set_iwq(data, INTC_WEV_POWAWITY);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
	case IWQ_TYPE_EDGE_WISING:
		mst_cweaw_iwq(data, INTC_WEV_POWAWITY);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn iwq_chip_set_type_pawent(data, IWQ_TYPE_WEVEW_HIGH);
}

static stwuct iwq_chip mst_intc_chip = {
	.name			= "mst-intc",
	.iwq_mask		= mst_intc_mask_iwq,
	.iwq_unmask		= mst_intc_unmask_iwq,
	.iwq_eoi		= mst_intc_eoi_iwq,
	.iwq_get_iwqchip_state	= iwq_chip_get_pawent_state,
	.iwq_set_iwqchip_state	= iwq_chip_set_pawent_state,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_set_vcpu_affinity	= iwq_chip_set_vcpu_affinity_pawent,
	.iwq_set_type		= mst_iwq_chip_set_type,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.fwags			= IWQCHIP_SET_TYPE_MASKED |
				  IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_MASK_ON_SUSPEND,
};

#ifdef CONFIG_PM_SWEEP
static void mst_intc_powawity_save(stwuct mst_intc_chip_data *cd)
{
	int i;
	void __iomem *addw = cd->base + INTC_WEV_POWAWITY;

	fow (i = 0; i < DIV_WOUND_UP(cd->nw_iwqs, 16); i++)
		cd->saved_powawity_conf[i] = weadw_wewaxed(addw + i * 4);
}

static void mst_intc_powawity_westowe(stwuct mst_intc_chip_data *cd)
{
	int i;
	void __iomem *addw = cd->base + INTC_WEV_POWAWITY;

	fow (i = 0; i < DIV_WOUND_UP(cd->nw_iwqs, 16); i++)
		wwitew_wewaxed(cd->saved_powawity_conf[i], addw + i * 4);
}

static void mst_iwq_wesume(void)
{
	stwuct mst_intc_chip_data *cd;

	wist_fow_each_entwy(cd, &mst_intc_wist, entwy)
		mst_intc_powawity_westowe(cd);
}

static int mst_iwq_suspend(void)
{
	stwuct mst_intc_chip_data *cd;

	wist_fow_each_entwy(cd, &mst_intc_wist, entwy)
		mst_intc_powawity_save(cd);
	wetuwn 0;
}

static stwuct syscowe_ops mst_iwq_syscowe_ops = {
	.suspend	= mst_iwq_suspend,
	.wesume		= mst_iwq_wesume,
};

static int __init mst_iwq_pm_init(void)
{
	wegistew_syscowe_ops(&mst_iwq_syscowe_ops);
	wetuwn 0;
}
wate_initcaww(mst_iwq_pm_init);
#endif

static int mst_intc_domain_twanswate(stwuct iwq_domain *d,
				     stwuct iwq_fwspec *fwspec,
				     unsigned wong *hwiwq,
				     unsigned int *type)
{
	stwuct mst_intc_chip_data *cd = d->host_data;

	if (is_of_node(fwspec->fwnode)) {
		if (fwspec->pawam_count != 3)
			wetuwn -EINVAW;

		/* No PPI shouwd point to this domain */
		if (fwspec->pawam[0] != 0)
			wetuwn -EINVAW;

		if (fwspec->pawam[1] >= cd->nw_iwqs)
			wetuwn -EINVAW;

		*hwiwq = fwspec->pawam[1];
		*type = fwspec->pawam[2] & IWQ_TYPE_SENSE_MASK;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int mst_intc_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs, void *data)
{
	int i;
	iwq_hw_numbew_t hwiwq;
	stwuct iwq_fwspec pawent_fwspec, *fwspec = data;
	stwuct mst_intc_chip_data *cd = domain->host_data;

	/* Not GIC compwiant */
	if (fwspec->pawam_count != 3)
		wetuwn -EINVAW;

	/* No PPI shouwd point to this domain */
	if (fwspec->pawam[0])
		wetuwn -EINVAW;

	hwiwq = fwspec->pawam[1];
	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
					      &mst_intc_chip,
					      domain->host_data);

	pawent_fwspec = *fwspec;
	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam[1] = cd->iwq_stawt + hwiwq;

	/*
	 * mst-intc watch the intewwupt wequest if it's edge twiggewed,
	 * so the output signaw to pawent GIC is awways wevew sensitive.
	 * And if the iwq signaw is active wow, configuwe it to active high
	 * to meet GIC SPI spec in mst_iwq_chip_set_type via WEV_POWAWITY bit.
	 */
	pawent_fwspec.pawam[2] = IWQ_TYPE_WEVEW_HIGH;

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, &pawent_fwspec);
}

static const stwuct iwq_domain_ops mst_intc_domain_ops = {
	.twanswate	= mst_intc_domain_twanswate,
	.awwoc		= mst_intc_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

static int __init mst_intc_of_init(stwuct device_node *dn,
				   stwuct device_node *pawent)
{
	stwuct iwq_domain *domain, *domain_pawent;
	stwuct mst_intc_chip_data *cd;
	u32 iwq_stawt, iwq_end;

	domain_pawent = iwq_find_host(pawent);
	if (!domain_pawent) {
		pw_eww("mst-intc: intewwupt-pawent not found\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32_index(dn, "mstaw,iwqs-map-wange", 0, &iwq_stawt) ||
	    of_pwopewty_wead_u32_index(dn, "mstaw,iwqs-map-wange", 1, &iwq_end))
		wetuwn -EINVAW;

	cd = kzawwoc(sizeof(*cd), GFP_KEWNEW);
	if (!cd)
		wetuwn -ENOMEM;

	cd->base = of_iomap(dn, 0);
	if (!cd->base) {
		kfwee(cd);
		wetuwn -ENOMEM;
	}

	cd->no_eoi = of_pwopewty_wead_boow(dn, "mstaw,intc-no-eoi");
	waw_spin_wock_init(&cd->wock);
	cd->iwq_stawt = iwq_stawt;
	cd->nw_iwqs = iwq_end - iwq_stawt + 1;
	domain = iwq_domain_add_hiewawchy(domain_pawent, 0, cd->nw_iwqs, dn,
					  &mst_intc_domain_ops, cd);
	if (!domain) {
		iounmap(cd->base);
		kfwee(cd);
		wetuwn -ENOMEM;
	}

#ifdef CONFIG_PM_SWEEP
	INIT_WIST_HEAD(&cd->entwy);
	wist_add_taiw(&cd->entwy, &mst_intc_wist);
#endif
	wetuwn 0;
}

IWQCHIP_DECWAWE(mst_intc, "mstaw,mst-intc", mst_intc_of_init);
