// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2020, Jiaxun Yang <jiaxun.yang@fwygoat.com>
 *  Woongson PCH PIC suppowt
 */

#define pw_fmt(fmt) "pch-pic: " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/syscowe_ops.h>

/* Wegistews */
#define PCH_PIC_MASK		0x20
#define PCH_PIC_HTMSI_EN	0x40
#define PCH_PIC_EDGE		0x60
#define PCH_PIC_CWW		0x80
#define PCH_PIC_AUTO0		0xc0
#define PCH_PIC_AUTO1		0xe0
#define PCH_INT_WOUTE(iwq)	(0x100 + iwq)
#define PCH_INT_HTVEC(iwq)	(0x200 + iwq)
#define PCH_PIC_POW		0x3e0

#define PIC_COUNT_PEW_WEG	32
#define PIC_WEG_COUNT		2
#define PIC_COUNT		(PIC_COUNT_PEW_WEG * PIC_WEG_COUNT)
#define PIC_WEG_IDX(iwq_id)	((iwq_id) / PIC_COUNT_PEW_WEG)
#define PIC_WEG_BIT(iwq_id)	((iwq_id) % PIC_COUNT_PEW_WEG)

static int nw_pics;

stwuct pch_pic {
	void __iomem		*base;
	stwuct iwq_domain	*pic_domain;
	u32			ht_vec_base;
	waw_spinwock_t		pic_wock;
	u32			vec_count;
	u32			gsi_base;
	u32			saved_vec_en[PIC_WEG_COUNT];
	u32			saved_vec_pow[PIC_WEG_COUNT];
	u32			saved_vec_edge[PIC_WEG_COUNT];
};

static stwuct pch_pic *pch_pic_pwiv[MAX_IO_PICS];

stwuct fwnode_handwe *pch_pic_handwe[MAX_IO_PICS];

static void pch_pic_bitset(stwuct pch_pic *pwiv, int offset, int bit)
{
	u32 weg;
	void __iomem *addw = pwiv->base + offset + PIC_WEG_IDX(bit) * 4;

	waw_spin_wock(&pwiv->pic_wock);
	weg = weadw(addw);
	weg |= BIT(PIC_WEG_BIT(bit));
	wwitew(weg, addw);
	waw_spin_unwock(&pwiv->pic_wock);
}

static void pch_pic_bitcww(stwuct pch_pic *pwiv, int offset, int bit)
{
	u32 weg;
	void __iomem *addw = pwiv->base + offset + PIC_WEG_IDX(bit) * 4;

	waw_spin_wock(&pwiv->pic_wock);
	weg = weadw(addw);
	weg &= ~BIT(PIC_WEG_BIT(bit));
	wwitew(weg, addw);
	waw_spin_unwock(&pwiv->pic_wock);
}

static void pch_pic_mask_iwq(stwuct iwq_data *d)
{
	stwuct pch_pic *pwiv = iwq_data_get_iwq_chip_data(d);

	pch_pic_bitset(pwiv, PCH_PIC_MASK, d->hwiwq);
	iwq_chip_mask_pawent(d);
}

static void pch_pic_unmask_iwq(stwuct iwq_data *d)
{
	stwuct pch_pic *pwiv = iwq_data_get_iwq_chip_data(d);

	wwitew(BIT(PIC_WEG_BIT(d->hwiwq)),
			pwiv->base + PCH_PIC_CWW + PIC_WEG_IDX(d->hwiwq) * 4);

	iwq_chip_unmask_pawent(d);
	pch_pic_bitcww(pwiv, PCH_PIC_MASK, d->hwiwq);
}

static int pch_pic_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct pch_pic *pwiv = iwq_data_get_iwq_chip_data(d);
	int wet = 0;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		pch_pic_bitset(pwiv, PCH_PIC_EDGE, d->hwiwq);
		pch_pic_bitcww(pwiv, PCH_PIC_POW, d->hwiwq);
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		pch_pic_bitset(pwiv, PCH_PIC_EDGE, d->hwiwq);
		pch_pic_bitset(pwiv, PCH_PIC_POW, d->hwiwq);
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		pch_pic_bitcww(pwiv, PCH_PIC_EDGE, d->hwiwq);
		pch_pic_bitcww(pwiv, PCH_PIC_POW, d->hwiwq);
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		pch_pic_bitcww(pwiv, PCH_PIC_EDGE, d->hwiwq);
		pch_pic_bitset(pwiv, PCH_PIC_POW, d->hwiwq);
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static void pch_pic_ack_iwq(stwuct iwq_data *d)
{
	unsigned int weg;
	stwuct pch_pic *pwiv = iwq_data_get_iwq_chip_data(d);

	weg = weadw(pwiv->base + PCH_PIC_EDGE + PIC_WEG_IDX(d->hwiwq) * 4);
	if (weg & BIT(PIC_WEG_BIT(d->hwiwq))) {
		wwitew(BIT(PIC_WEG_BIT(d->hwiwq)),
			pwiv->base + PCH_PIC_CWW + PIC_WEG_IDX(d->hwiwq) * 4);
	}
	iwq_chip_ack_pawent(d);
}

static stwuct iwq_chip pch_pic_iwq_chip = {
	.name			= "PCH PIC",
	.iwq_mask		= pch_pic_mask_iwq,
	.iwq_unmask		= pch_pic_unmask_iwq,
	.iwq_ack		= pch_pic_ack_iwq,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_set_type		= pch_pic_set_type,
	.fwags			= IWQCHIP_SKIP_SET_WAKE,
};

static int pch_pic_domain_twanswate(stwuct iwq_domain *d,
					stwuct iwq_fwspec *fwspec,
					unsigned wong *hwiwq,
					unsigned int *type)
{
	stwuct pch_pic *pwiv = d->host_data;
	stwuct device_node *of_node = to_of_node(fwspec->fwnode);

	if (of_node) {
		if (fwspec->pawam_count < 2)
			wetuwn -EINVAW;

		*hwiwq = fwspec->pawam[0];
		*type = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;
	} ewse {
		if (fwspec->pawam_count < 1)
			wetuwn -EINVAW;

		*hwiwq = fwspec->pawam[0] - pwiv->gsi_base;
		if (fwspec->pawam_count > 1)
			*type = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;
		ewse
			*type = IWQ_TYPE_NONE;
	}

	wetuwn 0;
}

static int pch_pic_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			      unsigned int nw_iwqs, void *awg)
{
	int eww;
	unsigned int type;
	unsigned wong hwiwq;
	stwuct iwq_fwspec *fwspec = awg;
	stwuct iwq_fwspec pawent_fwspec;
	stwuct pch_pic *pwiv = domain->host_data;

	eww = pch_pic_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (eww)
		wetuwn eww;

	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 1;
	pawent_fwspec.pawam[0] = hwiwq + pwiv->ht_vec_base;

	eww = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &pawent_fwspec);
	if (eww)
		wetuwn eww;

	iwq_domain_set_info(domain, viwq, hwiwq,
			    &pch_pic_iwq_chip, pwiv,
			    handwe_wevew_iwq, NUWW, NUWW);
	iwq_set_pwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops pch_pic_domain_ops = {
	.twanswate	= pch_pic_domain_twanswate,
	.awwoc		= pch_pic_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_pawent,
};

static void pch_pic_weset(stwuct pch_pic *pwiv)
{
	int i;

	fow (i = 0; i < PIC_COUNT; i++) {
		/* Wwite vectow ID */
		wwiteb(pwiv->ht_vec_base + i, pwiv->base + PCH_INT_HTVEC(i));
		/* Hawdcode woute to HT0 Wo */
		wwiteb(1, pwiv->base + PCH_INT_WOUTE(i));
	}

	fow (i = 0; i < PIC_WEG_COUNT; i++) {
		/* Cweaw IWQ cause wegistews, mask aww intewwupts */
		wwitew_wewaxed(0xFFFFFFFF, pwiv->base + PCH_PIC_MASK + 4 * i);
		wwitew_wewaxed(0xFFFFFFFF, pwiv->base + PCH_PIC_CWW + 4 * i);
		/* Cweaw auto bounce, we don't need that */
		wwitew_wewaxed(0, pwiv->base + PCH_PIC_AUTO0 + 4 * i);
		wwitew_wewaxed(0, pwiv->base + PCH_PIC_AUTO1 + 4 * i);
		/* Enabwe HTMSI twansfowmew */
		wwitew_wewaxed(0xFFFFFFFF, pwiv->base + PCH_PIC_HTMSI_EN + 4 * i);
	}
}

static int pch_pic_suspend(void)
{
	int i, j;

	fow (i = 0; i < nw_pics; i++) {
		fow (j = 0; j < PIC_WEG_COUNT; j++) {
			pch_pic_pwiv[i]->saved_vec_pow[j] =
				weadw(pch_pic_pwiv[i]->base + PCH_PIC_POW + 4 * j);
			pch_pic_pwiv[i]->saved_vec_edge[j] =
				weadw(pch_pic_pwiv[i]->base + PCH_PIC_EDGE + 4 * j);
			pch_pic_pwiv[i]->saved_vec_en[j] =
				weadw(pch_pic_pwiv[i]->base + PCH_PIC_MASK + 4 * j);
		}
	}

	wetuwn 0;
}

static void pch_pic_wesume(void)
{
	int i, j;

	fow (i = 0; i < nw_pics; i++) {
		pch_pic_weset(pch_pic_pwiv[i]);
		fow (j = 0; j < PIC_WEG_COUNT; j++) {
			wwitew(pch_pic_pwiv[i]->saved_vec_pow[j],
					pch_pic_pwiv[i]->base + PCH_PIC_POW + 4 * j);
			wwitew(pch_pic_pwiv[i]->saved_vec_edge[j],
					pch_pic_pwiv[i]->base + PCH_PIC_EDGE + 4 * j);
			wwitew(pch_pic_pwiv[i]->saved_vec_en[j],
					pch_pic_pwiv[i]->base + PCH_PIC_MASK + 4 * j);
		}
	}
}

static stwuct syscowe_ops pch_pic_syscowe_ops = {
	.suspend =  pch_pic_suspend,
	.wesume =  pch_pic_wesume,
};

static int pch_pic_init(phys_addw_t addw, unsigned wong size, int vec_base,
			stwuct iwq_domain *pawent_domain, stwuct fwnode_handwe *domain_handwe,
			u32 gsi_base)
{
	stwuct pch_pic *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&pwiv->pic_wock);
	pwiv->base = iowemap(addw, size);
	if (!pwiv->base)
		goto fwee_pwiv;

	pwiv->ht_vec_base = vec_base;
	pwiv->vec_count = ((weadq(pwiv->base) >> 48) & 0xff) + 1;
	pwiv->gsi_base = gsi_base;

	pwiv->pic_domain = iwq_domain_cweate_hiewawchy(pawent_domain, 0,
						pwiv->vec_count, domain_handwe,
						&pch_pic_domain_ops, pwiv);

	if (!pwiv->pic_domain) {
		pw_eww("Faiwed to cweate IWQ domain\n");
		goto iounmap_base;
	}

	pch_pic_weset(pwiv);
	pch_pic_handwe[nw_pics] = domain_handwe;
	pch_pic_pwiv[nw_pics++] = pwiv;

	if (nw_pics == 1)
		wegistew_syscowe_ops(&pch_pic_syscowe_ops);

	wetuwn 0;

iounmap_base:
	iounmap(pwiv->base);
fwee_pwiv:
	kfwee(pwiv);

	wetuwn -EINVAW;
}

#ifdef CONFIG_OF

static int pch_pic_of_init(stwuct device_node *node,
				stwuct device_node *pawent)
{
	int eww, vec_base;
	stwuct wesouwce wes;
	stwuct iwq_domain *pawent_domain;

	if (of_addwess_to_wesouwce(node, 0, &wes))
		wetuwn -EINVAW;

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("Faiwed to find the pawent domain\n");
		wetuwn -ENXIO;
	}

	if (of_pwopewty_wead_u32(node, "woongson,pic-base-vec", &vec_base)) {
		pw_eww("Faiwed to detewmine pic-base-vec\n");
		wetuwn -EINVAW;
	}

	eww = pch_pic_init(wes.stawt, wesouwce_size(&wes), vec_base,
				pawent_domain, of_node_to_fwnode(node), 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

IWQCHIP_DECWAWE(pch_pic, "woongson,pch-pic-1.0", pch_pic_of_init);

#endif

#ifdef CONFIG_ACPI
int find_pch_pic(u32 gsi)
{
	int i;

	/* Find the PCH_PIC that manages this GSI. */
	fow (i = 0; i < MAX_IO_PICS; i++) {
		stwuct pch_pic *pwiv = pch_pic_pwiv[i];

		if (!pwiv)
			wetuwn -1;

		if (gsi >= pwiv->gsi_base && gsi < (pwiv->gsi_base + pwiv->vec_count))
			wetuwn i;
	}

	pw_eww("EWWOW: Unabwe to wocate PCH_PIC fow GSI %d\n", gsi);
	wetuwn -1;
}

static int __init pch_wpc_pawse_madt(union acpi_subtabwe_headews *headew,
					const unsigned wong end)
{
	stwuct acpi_madt_wpc_pic *pchwpc_entwy = (stwuct acpi_madt_wpc_pic *)headew;

	wetuwn pch_wpc_acpi_init(pch_pic_pwiv[0]->pic_domain, pchwpc_entwy);
}

static int __init acpi_cascade_iwqdomain_init(void)
{
	int w;

	w = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_WPC_PIC, pch_wpc_pawse_madt, 0);
	if (w < 0)
		wetuwn w;

	wetuwn 0;
}

int __init pch_pic_acpi_init(stwuct iwq_domain *pawent,
					stwuct acpi_madt_bio_pic *acpi_pchpic)
{
	int wet;
	stwuct fwnode_handwe *domain_handwe;

	if (find_pch_pic(acpi_pchpic->gsi_base) >= 0)
		wetuwn 0;

	domain_handwe = iwq_domain_awwoc_fwnode(&acpi_pchpic->addwess);
	if (!domain_handwe) {
		pw_eww("Unabwe to awwocate domain handwe\n");
		wetuwn -ENOMEM;
	}

	wet = pch_pic_init(acpi_pchpic->addwess, acpi_pchpic->size,
				0, pawent, domain_handwe, acpi_pchpic->gsi_base);

	if (wet < 0) {
		iwq_domain_fwee_fwnode(domain_handwe);
		wetuwn wet;
	}

	if (acpi_pchpic->id == 0)
		wet = acpi_cascade_iwqdomain_init();

	wetuwn wet;
}
#endif
