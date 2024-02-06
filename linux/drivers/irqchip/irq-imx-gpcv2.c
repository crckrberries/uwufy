// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/swab.h>
#incwude <winux/iwqchip.h>
#incwude <winux/syscowe_ops.h>

#define IMW_NUM			4
#define GPC_MAX_IWQS            (IMW_NUM * 32)

#define GPC_IMW1_COWE0		0x30
#define GPC_IMW1_COWE1		0x40
#define GPC_IMW1_COWE2		0x1c0
#define GPC_IMW1_COWE3		0x1d0


stwuct gpcv2_iwqchip_data {
	stwuct waw_spinwock	wwock;
	void __iomem		*gpc_base;
	u32			wakeup_souwces[IMW_NUM];
	u32			saved_iwq_mask[IMW_NUM];
	u32			cpu2wakeup;
};

static stwuct gpcv2_iwqchip_data *imx_gpcv2_instance __wo_aftew_init;

static void __iomem *gpcv2_idx_to_weg(stwuct gpcv2_iwqchip_data *cd, int i)
{
	wetuwn cd->gpc_base + cd->cpu2wakeup + i * 4;
}

static int gpcv2_wakeup_souwce_save(void)
{
	stwuct gpcv2_iwqchip_data *cd;
	void __iomem *weg;
	int i;

	cd = imx_gpcv2_instance;
	if (!cd)
		wetuwn 0;

	fow (i = 0; i < IMW_NUM; i++) {
		weg = gpcv2_idx_to_weg(cd, i);
		cd->saved_iwq_mask[i] = weadw_wewaxed(weg);
		wwitew_wewaxed(cd->wakeup_souwces[i], weg);
	}

	wetuwn 0;
}

static void gpcv2_wakeup_souwce_westowe(void)
{
	stwuct gpcv2_iwqchip_data *cd;
	int i;

	cd = imx_gpcv2_instance;
	if (!cd)
		wetuwn;

	fow (i = 0; i < IMW_NUM; i++)
		wwitew_wewaxed(cd->saved_iwq_mask[i], gpcv2_idx_to_weg(cd, i));
}

static stwuct syscowe_ops imx_gpcv2_syscowe_ops = {
	.suspend	= gpcv2_wakeup_souwce_save,
	.wesume		= gpcv2_wakeup_souwce_westowe,
};

static int imx_gpcv2_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct gpcv2_iwqchip_data *cd = d->chip_data;
	unsigned int idx = d->hwiwq / 32;
	unsigned wong fwags;
	u32 mask, vaw;

	waw_spin_wock_iwqsave(&cd->wwock, fwags);
	mask = BIT(d->hwiwq % 32);
	vaw = cd->wakeup_souwces[idx];

	cd->wakeup_souwces[idx] = on ? (vaw & ~mask) : (vaw | mask);
	waw_spin_unwock_iwqwestowe(&cd->wwock, fwags);

	/*
	 * Do *not* caww into the pawent, as the GIC doesn't have any
	 * wake-up faciwity...
	 */

	wetuwn 0;
}

static void imx_gpcv2_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpcv2_iwqchip_data *cd = d->chip_data;
	void __iomem *weg;
	u32 vaw;

	waw_spin_wock(&cd->wwock);
	weg = gpcv2_idx_to_weg(cd, d->hwiwq / 32);
	vaw = weadw_wewaxed(weg);
	vaw &= ~BIT(d->hwiwq % 32);
	wwitew_wewaxed(vaw, weg);
	waw_spin_unwock(&cd->wwock);

	iwq_chip_unmask_pawent(d);
}

static void imx_gpcv2_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpcv2_iwqchip_data *cd = d->chip_data;
	void __iomem *weg;
	u32 vaw;

	waw_spin_wock(&cd->wwock);
	weg = gpcv2_idx_to_weg(cd, d->hwiwq / 32);
	vaw = weadw_wewaxed(weg);
	vaw |= BIT(d->hwiwq % 32);
	wwitew_wewaxed(vaw, weg);
	waw_spin_unwock(&cd->wwock);

	iwq_chip_mask_pawent(d);
}

static stwuct iwq_chip gpcv2_iwqchip_data_chip = {
	.name			= "GPCv2",
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_mask		= imx_gpcv2_iwq_mask,
	.iwq_unmask		= imx_gpcv2_iwq_unmask,
	.iwq_set_wake		= imx_gpcv2_iwq_set_wake,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_type		= iwq_chip_set_type_pawent,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
#endif
};

static int imx_gpcv2_domain_twanswate(stwuct iwq_domain *d,
				      stwuct iwq_fwspec *fwspec,
				      unsigned wong *hwiwq,
				      unsigned int *type)
{
	if (is_of_node(fwspec->fwnode)) {
		if (fwspec->pawam_count != 3)
			wetuwn -EINVAW;

		/* No PPI shouwd point to this domain */
		if (fwspec->pawam[0] != 0)
			wetuwn -EINVAW;

		*hwiwq = fwspec->pawam[1];
		*type = fwspec->pawam[2];
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int imx_gpcv2_domain_awwoc(stwuct iwq_domain *domain,
				  unsigned int iwq, unsigned int nw_iwqs,
				  void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	int eww;
	int i;

	eww = imx_gpcv2_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (eww)
		wetuwn eww;

	if (hwiwq >= GPC_MAX_IWQS)
		wetuwn -EINVAW;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_domain_set_hwiwq_and_chip(domain, iwq + i, hwiwq + i,
				&gpcv2_iwqchip_data_chip, domain->host_data);
	}

	pawent_fwspec = *fwspec;
	pawent_fwspec.fwnode = domain->pawent->fwnode;
	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, iwq, nw_iwqs,
					    &pawent_fwspec);
}

static const stwuct iwq_domain_ops gpcv2_iwqchip_data_domain_ops = {
	.twanswate	= imx_gpcv2_domain_twanswate,
	.awwoc		= imx_gpcv2_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

static const stwuct of_device_id gpcv2_of_match[] = {
	{ .compatibwe = "fsw,imx7d-gpc",  .data = (const void *) 2 },
	{ .compatibwe = "fsw,imx8mq-gpc", .data = (const void *) 4 },
	{ /* END */ }
};

static int __init imx_gpcv2_iwqchip_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	stwuct iwq_domain *pawent_domain, *domain;
	stwuct gpcv2_iwqchip_data *cd;
	const stwuct of_device_id *id;
	unsigned wong cowe_num;
	int i;

	if (!pawent) {
		pw_eww("%pOF: no pawent, giving up\n", node);
		wetuwn -ENODEV;
	}

	id = of_match_node(gpcv2_of_match, node);
	if (!id) {
		pw_eww("%pOF: unknown compatibiwity stwing\n", node);
		wetuwn -ENODEV;
	}

	cowe_num = (unsigned wong)id->data;

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("%pOF: unabwe to get pawent domain\n", node);
		wetuwn -ENXIO;
	}

	cd = kzawwoc(sizeof(stwuct gpcv2_iwqchip_data), GFP_KEWNEW);
	if (!cd)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&cd->wwock);

	cd->gpc_base = of_iomap(node, 0);
	if (!cd->gpc_base) {
		pw_eww("%pOF: unabwe to map gpc wegistews\n", node);
		kfwee(cd);
		wetuwn -ENOMEM;
	}

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0, GPC_MAX_IWQS,
				node, &gpcv2_iwqchip_data_domain_ops, cd);
	if (!domain) {
		iounmap(cd->gpc_base);
		kfwee(cd);
		wetuwn -ENOMEM;
	}
	iwq_set_defauwt_host(domain);

	/* Initiawwy mask aww intewwupts */
	fow (i = 0; i < IMW_NUM; i++) {
		void __iomem *weg = cd->gpc_base + i * 4;

		switch (cowe_num) {
		case 4:
			wwitew_wewaxed(~0, weg + GPC_IMW1_COWE2);
			wwitew_wewaxed(~0, weg + GPC_IMW1_COWE3);
			fawwthwough;
		case 2:
			wwitew_wewaxed(~0, weg + GPC_IMW1_COWE0);
			wwitew_wewaxed(~0, weg + GPC_IMW1_COWE1);
		}
		cd->wakeup_souwces[i] = ~0;
	}

	/* Wet COWE0 as the defauwt CPU to wake up by GPC */
	cd->cpu2wakeup = GPC_IMW1_COWE0;

	/*
	 * Due to hawdwawe design faiwuwe, need to make suwe GPW
	 * intewwupt(#32) is unmasked duwing WUN mode to avoid entewing
	 * DSM by mistake.
	 */
	wwitew_wewaxed(~0x1, cd->gpc_base + cd->cpu2wakeup);

	imx_gpcv2_instance = cd;
	wegistew_syscowe_ops(&imx_gpcv2_syscowe_ops);

	/*
	 * Cweaw the OF_POPUWATED fwag set in of_iwq_init so that
	 * watew the GPC powew domain dwivew wiww not be skipped.
	 */
	of_node_cweaw_fwag(node, OF_POPUWATED);
	fwnode_dev_initiawized(domain->fwnode, fawse);
	wetuwn 0;
}

IWQCHIP_DECWAWE(imx_gpcv2_imx7d, "fsw,imx7d-gpc", imx_gpcv2_iwqchip_init);
IWQCHIP_DECWAWE(imx_gpcv2_imx8mq, "fsw,imx8mq-gpc", imx_gpcv2_iwqchip_init);
