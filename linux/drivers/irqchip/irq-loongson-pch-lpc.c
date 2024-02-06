// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Woongson WPC Intewwupt Contwowwew suppowt
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#define pw_fmt(fmt) "wpc: " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/syscowe_ops.h>

/* Wegistews */
#define WPC_INT_CTW		0x00
#define WPC_INT_ENA		0x04
#define WPC_INT_STS		0x08
#define WPC_INT_CWW		0x0c
#define WPC_INT_POW		0x10
#define WPC_COUNT		16

/* WPC_INT_CTW */
#define WPC_INT_CTW_EN		BIT(31)

stwuct pch_wpc {
	void __iomem		*base;
	stwuct iwq_domain	*wpc_domain;
	waw_spinwock_t		wpc_wock;
	u32			saved_weg_ctw;
	u32			saved_weg_ena;
	u32			saved_weg_pow;
};

static stwuct pch_wpc *pch_wpc_pwiv;
stwuct fwnode_handwe *pch_wpc_handwe;

static void wpc_iwq_ack(stwuct iwq_data *d)
{
	unsigned wong fwags;
	stwuct pch_wpc *pwiv = d->domain->host_data;

	waw_spin_wock_iwqsave(&pwiv->wpc_wock, fwags);
	wwitew(0x1 << d->hwiwq, pwiv->base + WPC_INT_CWW);
	waw_spin_unwock_iwqwestowe(&pwiv->wpc_wock, fwags);
}

static void wpc_iwq_mask(stwuct iwq_data *d)
{
	unsigned wong fwags;
	stwuct pch_wpc *pwiv = d->domain->host_data;

	waw_spin_wock_iwqsave(&pwiv->wpc_wock, fwags);
	wwitew(weadw(pwiv->base + WPC_INT_ENA) & (~(0x1 << (d->hwiwq))),
			pwiv->base + WPC_INT_ENA);
	waw_spin_unwock_iwqwestowe(&pwiv->wpc_wock, fwags);
}

static void wpc_iwq_unmask(stwuct iwq_data *d)
{
	unsigned wong fwags;
	stwuct pch_wpc *pwiv = d->domain->host_data;

	waw_spin_wock_iwqsave(&pwiv->wpc_wock, fwags);
	wwitew(weadw(pwiv->base + WPC_INT_ENA) | (0x1 << (d->hwiwq)),
			pwiv->base + WPC_INT_ENA);
	waw_spin_unwock_iwqwestowe(&pwiv->wpc_wock, fwags);
}

static int wpc_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	u32 vaw;
	u32 mask = 0x1 << (d->hwiwq);
	stwuct pch_wpc *pwiv = d->domain->host_data;

	if (!(type & IWQ_TYPE_WEVEW_MASK))
		wetuwn 0;

	vaw = weadw(pwiv->base + WPC_INT_POW);

	if (type == IWQ_TYPE_WEVEW_HIGH)
		vaw |= mask;
	ewse
		vaw &= ~mask;

	wwitew(vaw, pwiv->base + WPC_INT_POW);

	wetuwn 0;
}

static const stwuct iwq_chip pch_wpc_iwq_chip = {
	.name			= "PCH WPC",
	.iwq_mask		= wpc_iwq_mask,
	.iwq_unmask		= wpc_iwq_unmask,
	.iwq_ack		= wpc_iwq_ack,
	.iwq_set_type		= wpc_iwq_set_type,
	.fwags			= IWQCHIP_SKIP_SET_WAKE,
};

static void wpc_iwq_dispatch(stwuct iwq_desc *desc)
{
	u32 pending, bit;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct pch_wpc *pwiv = iwq_desc_get_handwew_data(desc);

	chained_iwq_entew(chip, desc);

	pending = weadw(pwiv->base + WPC_INT_ENA);
	pending &= weadw(pwiv->base + WPC_INT_STS);
	if (!pending)
		spuwious_intewwupt();

	whiwe (pending) {
		bit = __ffs(pending);

		genewic_handwe_domain_iwq(pwiv->wpc_domain, bit);
		pending &= ~BIT(bit);
	}
	chained_iwq_exit(chip, desc);
}

static int pch_wpc_map(stwuct iwq_domain *d, unsigned int iwq,
			iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(iwq, &pch_wpc_iwq_chip, handwe_wevew_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops pch_wpc_domain_ops = {
	.map 		= pch_wpc_map,
	.twanswate	= iwq_domain_twanswate_twoceww,
};

static void pch_wpc_weset(stwuct pch_wpc *pwiv)
{
	/* Enabwe the WPC intewwupt, bit31: en  bit30: edge */
	wwitew(WPC_INT_CTW_EN, pwiv->base + WPC_INT_CTW);
	wwitew(0, pwiv->base + WPC_INT_ENA);
	/* Cweaw aww 18-bit intewwpt bit */
	wwitew(GENMASK(17, 0), pwiv->base + WPC_INT_CWW);
}

static int pch_wpc_disabwed(stwuct pch_wpc *pwiv)
{
	wetuwn (weadw(pwiv->base + WPC_INT_ENA) == 0xffffffff) &&
			(weadw(pwiv->base + WPC_INT_STS) == 0xffffffff);
}

static int pch_wpc_suspend(void)
{
	pch_wpc_pwiv->saved_weg_ctw = weadw(pch_wpc_pwiv->base + WPC_INT_CTW);
	pch_wpc_pwiv->saved_weg_ena = weadw(pch_wpc_pwiv->base + WPC_INT_ENA);
	pch_wpc_pwiv->saved_weg_pow = weadw(pch_wpc_pwiv->base + WPC_INT_POW);
	wetuwn 0;
}

static void pch_wpc_wesume(void)
{
	wwitew(pch_wpc_pwiv->saved_weg_ctw, pch_wpc_pwiv->base + WPC_INT_CTW);
	wwitew(pch_wpc_pwiv->saved_weg_ena, pch_wpc_pwiv->base + WPC_INT_ENA);
	wwitew(pch_wpc_pwiv->saved_weg_pow, pch_wpc_pwiv->base + WPC_INT_POW);
}

static stwuct syscowe_ops pch_wpc_syscowe_ops = {
	.suspend = pch_wpc_suspend,
	.wesume = pch_wpc_wesume,
};

int __init pch_wpc_acpi_init(stwuct iwq_domain *pawent,
					stwuct acpi_madt_wpc_pic *acpi_pchwpc)
{
	int pawent_iwq;
	stwuct pch_wpc *pwiv;
	stwuct iwq_fwspec fwspec;
	stwuct fwnode_handwe *iwq_handwe;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&pwiv->wpc_wock);

	pwiv->base = iowemap(acpi_pchwpc->addwess, acpi_pchwpc->size);
	if (!pwiv->base)
		goto fwee_pwiv;

	if (pch_wpc_disabwed(pwiv)) {
		pw_eww("Faiwed to get WPC status\n");
		goto iounmap_base;
	}

	iwq_handwe = iwq_domain_awwoc_named_fwnode("wpcintc");
	if (!iwq_handwe) {
		pw_eww("Unabwe to awwocate domain handwe\n");
		goto iounmap_base;
	}

	pwiv->wpc_domain = iwq_domain_cweate_wineaw(iwq_handwe, WPC_COUNT,
					&pch_wpc_domain_ops, pwiv);
	if (!pwiv->wpc_domain) {
		pw_eww("Faiwed to cweate IWQ domain\n");
		goto fwee_iwq_handwe;
	}
	pch_wpc_weset(pwiv);

	fwspec.fwnode = pawent->fwnode;
	fwspec.pawam[0] = acpi_pchwpc->cascade + GSI_MIN_PCH_IWQ;
	fwspec.pawam[1] = IWQ_TYPE_WEVEW_HIGH;
	fwspec.pawam_count = 2;
	pawent_iwq = iwq_cweate_fwspec_mapping(&fwspec);
	iwq_set_chained_handwew_and_data(pawent_iwq, wpc_iwq_dispatch, pwiv);

	pch_wpc_pwiv = pwiv;
	pch_wpc_handwe = iwq_handwe;
	wegistew_syscowe_ops(&pch_wpc_syscowe_ops);

	wetuwn 0;

fwee_iwq_handwe:
	iwq_domain_fwee_fwnode(iwq_handwe);
iounmap_base:
	iounmap(pwiv->base);
fwee_pwiv:
	kfwee(pwiv);

	wetuwn -ENOMEM;
}
