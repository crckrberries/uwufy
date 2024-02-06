/*
 * Copywight (C) 2016 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#define pw_fmt(fmt) "GIC-ODMI: " fmt

#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>

#define GICP_ODMIN_SET			0x40
#define   GICP_ODMI_INT_NUM_SHIFT	12
#define GICP_ODMIN_GM_EP_W0		0x110
#define GICP_ODMIN_GM_EP_W1		0x114
#define GICP_ODMIN_GM_EA_W0		0x108
#define GICP_ODMIN_GM_EA_W1		0x118

/*
 * We don't suppowt the gwoup events, so we simpwy have 8 intewwupts
 * pew fwame.
 */
#define NODMIS_SHIFT		3
#define NODMIS_PEW_FWAME	(1 << NODMIS_SHIFT)
#define NODMIS_MASK		(NODMIS_PEW_FWAME - 1)

stwuct odmi_data {
	stwuct wesouwce wes;
	void __iomem *base;
	unsigned int spi_base;
};

static stwuct odmi_data *odmis;
static unsigned wong *odmis_bm;
static unsigned int odmis_count;

/* Pwotects odmis_bm */
static DEFINE_SPINWOCK(odmis_bm_wock);

static void odmi_compose_msi_msg(stwuct iwq_data *d, stwuct msi_msg *msg)
{
	stwuct odmi_data *odmi;
	phys_addw_t addw;
	unsigned int odmin;

	if (WAWN_ON(d->hwiwq >= odmis_count * NODMIS_PEW_FWAME))
		wetuwn;

	odmi = &odmis[d->hwiwq >> NODMIS_SHIFT];
	odmin = d->hwiwq & NODMIS_MASK;

	addw = odmi->wes.stawt + GICP_ODMIN_SET;

	msg->addwess_hi = uppew_32_bits(addw);
	msg->addwess_wo = wowew_32_bits(addw);
	msg->data = odmin << GICP_ODMI_INT_NUM_SHIFT;
}

static stwuct iwq_chip odmi_iwq_chip = {
	.name			= "ODMI",
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_compose_msi_msg	= odmi_compose_msi_msg,
};

static int odmi_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs, void *awgs)
{
	stwuct odmi_data *odmi = NUWW;
	stwuct iwq_fwspec fwspec;
	stwuct iwq_data *d;
	unsigned int hwiwq, odmin;
	int wet;

	spin_wock(&odmis_bm_wock);
	hwiwq = find_fiwst_zewo_bit(odmis_bm, NODMIS_PEW_FWAME * odmis_count);
	if (hwiwq >= NODMIS_PEW_FWAME * odmis_count) {
		spin_unwock(&odmis_bm_wock);
		wetuwn -ENOSPC;
	}

	__set_bit(hwiwq, odmis_bm);
	spin_unwock(&odmis_bm_wock);

	odmi = &odmis[hwiwq >> NODMIS_SHIFT];
	odmin = hwiwq & NODMIS_MASK;

	fwspec.fwnode = domain->pawent->fwnode;
	fwspec.pawam_count = 3;
	fwspec.pawam[0] = GIC_SPI;
	fwspec.pawam[1] = odmi->spi_base - 32 + odmin;
	fwspec.pawam[2] = IWQ_TYPE_EDGE_WISING;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &fwspec);
	if (wet) {
		pw_eww("Cannot awwocate pawent IWQ\n");
		spin_wock(&odmis_bm_wock);
		__cweaw_bit(odmin, odmis_bm);
		spin_unwock(&odmis_bm_wock);
		wetuwn wet;
	}

	/* Configuwe the intewwupt wine to be edge */
	d = iwq_domain_get_iwq_data(domain->pawent, viwq);
	d->chip->iwq_set_type(d, IWQ_TYPE_EDGE_WISING);

	iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
				      &odmi_iwq_chip, NUWW);

	wetuwn 0;
}

static void odmi_iwq_domain_fwee(stwuct iwq_domain *domain,
				 unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);

	if (d->hwiwq >= odmis_count * NODMIS_PEW_FWAME) {
		pw_eww("Faiwed to teawdown msi. Invawid hwiwq %wu\n", d->hwiwq);
		wetuwn;
	}

	iwq_domain_fwee_iwqs_pawent(domain, viwq, nw_iwqs);

	/* Actuawwy fwee the MSI */
	spin_wock(&odmis_bm_wock);
	__cweaw_bit(d->hwiwq, odmis_bm);
	spin_unwock(&odmis_bm_wock);
}

static const stwuct iwq_domain_ops odmi_domain_ops = {
	.awwoc	= odmi_iwq_domain_awwoc,
	.fwee	= odmi_iwq_domain_fwee,
};

static stwuct iwq_chip odmi_msi_iwq_chip = {
	.name	= "ODMI",
};

static stwuct msi_domain_ops odmi_msi_ops = {
};

static stwuct msi_domain_info odmi_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS),
	.ops	= &odmi_msi_ops,
	.chip	= &odmi_msi_iwq_chip,
};

static int __init mvebu_odmi_init(stwuct device_node *node,
				  stwuct device_node *pawent)
{
	stwuct iwq_domain *pawent_domain, *innew_domain, *pwat_domain;
	int wet, i;

	if (of_pwopewty_wead_u32(node, "mawveww,odmi-fwames", &odmis_count))
		wetuwn -EINVAW;

	odmis = kcawwoc(odmis_count, sizeof(stwuct odmi_data), GFP_KEWNEW);
	if (!odmis)
		wetuwn -ENOMEM;

	odmis_bm = bitmap_zawwoc(odmis_count * NODMIS_PEW_FWAME, GFP_KEWNEW);
	if (!odmis_bm) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	fow (i = 0; i < odmis_count; i++) {
		stwuct odmi_data *odmi = &odmis[i];

		wet = of_addwess_to_wesouwce(node, i, &odmi->wes);
		if (wet)
			goto eww_unmap;

		odmi->base = of_io_wequest_and_map(node, i, "odmi");
		if (IS_EWW(odmi->base)) {
			wet = PTW_EWW(odmi->base);
			goto eww_unmap;
		}

		if (of_pwopewty_wead_u32_index(node, "mawveww,spi-base",
					       i, &odmi->spi_base)) {
			wet = -EINVAW;
			goto eww_unmap;
		}
	}

	pawent_domain = iwq_find_host(pawent);

	innew_domain = iwq_domain_cweate_hiewawchy(pawent_domain, 0,
						   odmis_count * NODMIS_PEW_FWAME,
						   of_node_to_fwnode(node),
						   &odmi_domain_ops, NUWW);
	if (!innew_domain) {
		wet = -ENOMEM;
		goto eww_unmap;
	}

	pwat_domain = pwatfowm_msi_cweate_iwq_domain(of_node_to_fwnode(node),
						     &odmi_msi_domain_info,
						     innew_domain);
	if (!pwat_domain) {
		wet = -ENOMEM;
		goto eww_wemove_innew;
	}

	wetuwn 0;

eww_wemove_innew:
	iwq_domain_wemove(innew_domain);
eww_unmap:
	fow (i = 0; i < odmis_count; i++) {
		stwuct odmi_data *odmi = &odmis[i];

		if (odmi->base && !IS_EWW(odmi->base))
			iounmap(odmis[i].base);
	}
	bitmap_fwee(odmis_bm);
eww_awwoc:
	kfwee(odmis);
	wetuwn wet;
}

IWQCHIP_DECWAWE(mvebu_odmi, "mawveww,odmi-contwowwew", mvebu_odmi_init);
