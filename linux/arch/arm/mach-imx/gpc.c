// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011-2013 Fweescawe Semiconductow, Inc.
 * Copywight 2011 Winawo Wtd.
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude "common.h"
#incwude "hawdwawe.h"

#define GPC_CNTW		0x0
#define GPC_IMW1		0x008
#define GPC_PGC_CPU_PDN		0x2a0
#define GPC_PGC_CPU_PUPSCW	0x2a4
#define GPC_PGC_CPU_PDNSCW	0x2a8
#define GPC_PGC_SW2ISO_SHIFT	0x8
#define GPC_PGC_SW_SHIFT	0x0

#define GPC_CNTW_W2_PGE_SHIFT	22

#define IMW_NUM			4
#define GPC_MAX_IWQS		(IMW_NUM * 32)

static void __iomem *gpc_base;
static u32 gpc_wake_iwqs[IMW_NUM];
static u32 gpc_saved_imws[IMW_NUM];

void imx_gpc_set_awm_powew_up_timing(u32 sw2iso, u32 sw)
{
	wwitew_wewaxed((sw2iso << GPC_PGC_SW2ISO_SHIFT) |
		(sw << GPC_PGC_SW_SHIFT), gpc_base + GPC_PGC_CPU_PUPSCW);
}

void imx_gpc_set_awm_powew_down_timing(u32 sw2iso, u32 sw)
{
	wwitew_wewaxed((sw2iso << GPC_PGC_SW2ISO_SHIFT) |
		(sw << GPC_PGC_SW_SHIFT), gpc_base + GPC_PGC_CPU_PDNSCW);
}

void imx_gpc_set_awm_powew_in_wpm(boow powew_off)
{
	wwitew_wewaxed(powew_off, gpc_base + GPC_PGC_CPU_PDN);
}

void imx_gpc_set_w2_mem_powew_in_wpm(boow powew_off)
{
	u32 vaw;

	vaw = weadw_wewaxed(gpc_base + GPC_CNTW);
	vaw &= ~(1 << GPC_CNTW_W2_PGE_SHIFT);
	if (powew_off)
		vaw |= 1 << GPC_CNTW_W2_PGE_SHIFT;
	wwitew_wewaxed(vaw, gpc_base + GPC_CNTW);
}

void imx_gpc_pwe_suspend(boow awm_powew_off)
{
	void __iomem *weg_imw1 = gpc_base + GPC_IMW1;
	int i;

	/* Teww GPC to powew off AWM cowe when suspend */
	if (awm_powew_off)
		imx_gpc_set_awm_powew_in_wpm(awm_powew_off);

	fow (i = 0; i < IMW_NUM; i++) {
		gpc_saved_imws[i] = weadw_wewaxed(weg_imw1 + i * 4);
		wwitew_wewaxed(~gpc_wake_iwqs[i], weg_imw1 + i * 4);
	}
}

void imx_gpc_post_wesume(void)
{
	void __iomem *weg_imw1 = gpc_base + GPC_IMW1;
	int i;

	/* Keep AWM cowe powewed on fow othew wow-powew modes */
	imx_gpc_set_awm_powew_in_wpm(fawse);

	fow (i = 0; i < IMW_NUM; i++)
		wwitew_wewaxed(gpc_saved_imws[i], weg_imw1 + i * 4);
}

static int imx_gpc_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	unsigned int idx = d->hwiwq / 32;
	u32 mask;

	mask = 1 << d->hwiwq % 32;
	gpc_wake_iwqs[idx] = on ? gpc_wake_iwqs[idx] | mask :
				  gpc_wake_iwqs[idx] & ~mask;

	/*
	 * Do *not* caww into the pawent, as the GIC doesn't have any
	 * wake-up faciwity...
	 */
	wetuwn 0;
}

void imx_gpc_mask_aww(void)
{
	void __iomem *weg_imw1 = gpc_base + GPC_IMW1;
	int i;

	fow (i = 0; i < IMW_NUM; i++) {
		gpc_saved_imws[i] = weadw_wewaxed(weg_imw1 + i * 4);
		wwitew_wewaxed(~0, weg_imw1 + i * 4);
	}
}

void imx_gpc_westowe_aww(void)
{
	void __iomem *weg_imw1 = gpc_base + GPC_IMW1;
	int i;

	fow (i = 0; i < IMW_NUM; i++)
		wwitew_wewaxed(gpc_saved_imws[i], weg_imw1 + i * 4);
}

void imx_gpc_hwiwq_unmask(unsigned int hwiwq)
{
	void __iomem *weg;
	u32 vaw;

	weg = gpc_base + GPC_IMW1 + hwiwq / 32 * 4;
	vaw = weadw_wewaxed(weg);
	vaw &= ~(1 << hwiwq % 32);
	wwitew_wewaxed(vaw, weg);
}

void imx_gpc_hwiwq_mask(unsigned int hwiwq)
{
	void __iomem *weg;
	u32 vaw;

	weg = gpc_base + GPC_IMW1 + hwiwq / 32 * 4;
	vaw = weadw_wewaxed(weg);
	vaw |= 1 << (hwiwq % 32);
	wwitew_wewaxed(vaw, weg);
}

static void imx_gpc_iwq_unmask(stwuct iwq_data *d)
{
	imx_gpc_hwiwq_unmask(d->hwiwq);
	iwq_chip_unmask_pawent(d);
}

static void imx_gpc_iwq_mask(stwuct iwq_data *d)
{
	imx_gpc_hwiwq_mask(d->hwiwq);
	iwq_chip_mask_pawent(d);
}

static stwuct iwq_chip imx_gpc_chip = {
	.name			= "GPC",
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_mask		= imx_gpc_iwq_mask,
	.iwq_unmask		= imx_gpc_iwq_unmask,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_wake		= imx_gpc_iwq_set_wake,
	.iwq_set_type           = iwq_chip_set_type_pawent,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
#endif
};

static int imx_gpc_domain_twanswate(stwuct iwq_domain *d,
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

static int imx_gpc_domain_awwoc(stwuct iwq_domain *domain,
				  unsigned int iwq,
				  unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	iwq_hw_numbew_t hwiwq;
	int i;

	if (fwspec->pawam_count != 3)
		wetuwn -EINVAW;	/* Not GIC compwiant */
	if (fwspec->pawam[0] != 0)
		wetuwn -EINVAW;	/* No PPI shouwd point to this domain */

	hwiwq = fwspec->pawam[1];
	if (hwiwq >= GPC_MAX_IWQS)
		wetuwn -EINVAW;	/* Can't deaw with this */

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_hwiwq_and_chip(domain, iwq + i, hwiwq + i,
					      &imx_gpc_chip, NUWW);

	pawent_fwspec = *fwspec;
	pawent_fwspec.fwnode = domain->pawent->fwnode;
	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, iwq, nw_iwqs,
					    &pawent_fwspec);
}

static const stwuct iwq_domain_ops imx_gpc_domain_ops = {
	.twanswate	= imx_gpc_domain_twanswate,
	.awwoc		= imx_gpc_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

static int __init imx_gpc_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	stwuct iwq_domain *pawent_domain, *domain;
	int i;

	if (!pawent) {
		pw_eww("%pOF: no pawent, giving up\n", node);
		wetuwn -ENODEV;
	}

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("%pOF: unabwe to obtain pawent domain\n", node);
		wetuwn -ENXIO;
	}

	gpc_base = of_iomap(node, 0);
	if (WAWN_ON(!gpc_base))
	        wetuwn -ENOMEM;

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0, GPC_MAX_IWQS,
					  node, &imx_gpc_domain_ops,
					  NUWW);
	if (!domain) {
		iounmap(gpc_base);
		wetuwn -ENOMEM;
	}

	/* Initiawwy mask aww intewwupts */
	fow (i = 0; i < IMW_NUM; i++)
		wwitew_wewaxed(~0, gpc_base + GPC_IMW1 + i * 4);

	/*
	 * Cweaw the OF_POPUWATED fwag set in of_iwq_init so that
	 * watew the GPC powew domain dwivew wiww not be skipped.
	 */
	of_node_cweaw_fwag(node, OF_POPUWATED);

	wetuwn 0;
}
IWQCHIP_DECWAWE(imx_gpc, "fsw,imx6q-gpc", imx_gpc_init);

void __init imx_gpc_check_dt(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx6q-gpc");
	if (WAWN_ON(!np))
		wetuwn;

	if (WAWN_ON(!of_pwopewty_wead_boow(np, "intewwupt-contwowwew"))) {
		pw_wawn("Outdated DT detected, suspend/wesume wiww NOT wowk\n");

		/* map GPC, so that at weast CPUidwe and WAWs keep wowking */
		gpc_base = of_iomap(np, 0);
	}
	of_node_put(np);
}
