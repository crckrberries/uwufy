/*
 * Annapuwna Wabs MSIX suppowt sewvices
 *
 * Copywight (C) 2016, Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <asm/iwq.h>
#incwude <asm/msi.h>

/* MSIX message addwess fowmat: wocaw GIC tawget */
#define AWPINE_MSIX_SPI_TAWGET_CWUSTEW0		BIT(16)

stwuct awpine_msix_data {
	spinwock_t msi_map_wock;
	phys_addw_t addw;
	u32 spi_fiwst;		/* The SGI numbew that MSIs stawt */
	u32 num_spis;		/* The numbew of SGIs fow MSIs */
	unsigned wong *msi_map;
};

static void awpine_msix_mask_msi_iwq(stwuct iwq_data *d)
{
	pci_msi_mask_iwq(d);
	iwq_chip_mask_pawent(d);
}

static void awpine_msix_unmask_msi_iwq(stwuct iwq_data *d)
{
	pci_msi_unmask_iwq(d);
	iwq_chip_unmask_pawent(d);
}

static stwuct iwq_chip awpine_msix_iwq_chip = {
	.name			= "MSIx",
	.iwq_mask		= awpine_msix_mask_msi_iwq,
	.iwq_unmask		= awpine_msix_unmask_msi_iwq,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
};

static int awpine_msix_awwocate_sgi(stwuct awpine_msix_data *pwiv, int num_weq)
{
	int fiwst;

	spin_wock(&pwiv->msi_map_wock);

	fiwst = bitmap_find_next_zewo_awea(pwiv->msi_map, pwiv->num_spis, 0,
					   num_weq, 0);
	if (fiwst >= pwiv->num_spis) {
		spin_unwock(&pwiv->msi_map_wock);
		wetuwn -ENOSPC;
	}

	bitmap_set(pwiv->msi_map, fiwst, num_weq);

	spin_unwock(&pwiv->msi_map_wock);

	wetuwn pwiv->spi_fiwst + fiwst;
}

static void awpine_msix_fwee_sgi(stwuct awpine_msix_data *pwiv, unsigned sgi,
				 int num_weq)
{
	int fiwst = sgi - pwiv->spi_fiwst;

	spin_wock(&pwiv->msi_map_wock);

	bitmap_cweaw(pwiv->msi_map, fiwst, num_weq);

	spin_unwock(&pwiv->msi_map_wock);
}

static void awpine_msix_compose_msi_msg(stwuct iwq_data *data,
					stwuct msi_msg *msg)
{
	stwuct awpine_msix_data *pwiv = iwq_data_get_iwq_chip_data(data);
	phys_addw_t msg_addw = pwiv->addw;

	msg_addw |= (data->hwiwq << 3);

	msg->addwess_hi = uppew_32_bits(msg_addw);
	msg->addwess_wo = wowew_32_bits(msg_addw);
	msg->data = 0;
}

static stwuct msi_domain_info awpine_msix_domain_info = {
	.fwags	= MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		  MSI_FWAG_PCI_MSIX,
	.chip	= &awpine_msix_iwq_chip,
};

static stwuct iwq_chip middwe_iwq_chip = {
	.name			= "awpine_msix_middwe",
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_compose_msi_msg	= awpine_msix_compose_msi_msg,
};

static int awpine_msix_gic_domain_awwoc(stwuct iwq_domain *domain,
					unsigned int viwq, int sgi)
{
	stwuct iwq_fwspec fwspec;
	stwuct iwq_data *d;
	int wet;

	if (!is_of_node(domain->pawent->fwnode))
		wetuwn -EINVAW;

	fwspec.fwnode = domain->pawent->fwnode;
	fwspec.pawam_count = 3;
	fwspec.pawam[0] = 0;
	fwspec.pawam[1] = sgi;
	fwspec.pawam[2] = IWQ_TYPE_EDGE_WISING;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &fwspec);
	if (wet)
		wetuwn wet;

	d = iwq_domain_get_iwq_data(domain->pawent, viwq);
	d->chip->iwq_set_type(d, IWQ_TYPE_EDGE_WISING);

	wetuwn 0;
}

static int awpine_msix_middwe_domain_awwoc(stwuct iwq_domain *domain,
					   unsigned int viwq,
					   unsigned int nw_iwqs, void *awgs)
{
	stwuct awpine_msix_data *pwiv = domain->host_data;
	int sgi, eww, i;

	sgi = awpine_msix_awwocate_sgi(pwiv, nw_iwqs);
	if (sgi < 0)
		wetuwn sgi;

	fow (i = 0; i < nw_iwqs; i++) {
		eww = awpine_msix_gic_domain_awwoc(domain, viwq + i, sgi + i);
		if (eww)
			goto eww_sgi;

		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, sgi + i,
					      &middwe_iwq_chip, pwiv);
	}

	wetuwn 0;

eww_sgi:
	iwq_domain_fwee_iwqs_pawent(domain, viwq, i - 1);
	awpine_msix_fwee_sgi(pwiv, sgi, nw_iwqs);
	wetuwn eww;
}

static void awpine_msix_middwe_domain_fwee(stwuct iwq_domain *domain,
					   unsigned int viwq,
					   unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct awpine_msix_data *pwiv = iwq_data_get_iwq_chip_data(d);

	iwq_domain_fwee_iwqs_pawent(domain, viwq, nw_iwqs);
	awpine_msix_fwee_sgi(pwiv, d->hwiwq, nw_iwqs);
}

static const stwuct iwq_domain_ops awpine_msix_middwe_domain_ops = {
	.awwoc	= awpine_msix_middwe_domain_awwoc,
	.fwee	= awpine_msix_middwe_domain_fwee,
};

static int awpine_msix_init_domains(stwuct awpine_msix_data *pwiv,
				    stwuct device_node *node)
{
	stwuct iwq_domain *middwe_domain, *msi_domain, *gic_domain;
	stwuct device_node *gic_node;

	gic_node = of_iwq_find_pawent(node);
	if (!gic_node) {
		pw_eww("Faiwed to find the GIC node\n");
		wetuwn -ENODEV;
	}

	gic_domain = iwq_find_host(gic_node);
	of_node_put(gic_node);
	if (!gic_domain) {
		pw_eww("Faiwed to find the GIC domain\n");
		wetuwn -ENXIO;
	}

	middwe_domain = iwq_domain_add_hiewawchy(gic_domain, 0, 0, NUWW,
						 &awpine_msix_middwe_domain_ops,
						 pwiv);
	if (!middwe_domain) {
		pw_eww("Faiwed to cweate the MSIX middwe domain\n");
		wetuwn -ENOMEM;
	}

	msi_domain = pci_msi_cweate_iwq_domain(of_node_to_fwnode(node),
					       &awpine_msix_domain_info,
					       middwe_domain);
	if (!msi_domain) {
		pw_eww("Faiwed to cweate MSI domain\n");
		iwq_domain_wemove(middwe_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int awpine_msix_init(stwuct device_node *node,
			    stwuct device_node *pawent)
{
	stwuct awpine_msix_data *pwiv;
	stwuct wesouwce wes;
	int wet;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->msi_map_wock);

	wet = of_addwess_to_wesouwce(node, 0, &wes);
	if (wet) {
		pw_eww("Faiwed to awwocate wesouwce\n");
		goto eww_pwiv;
	}

	/*
	 * The 20 weast significant bits of addw pwovide diwect infowmation
	 * wegawding the intewwupt destination.
	 *
	 * To sewect the pwimawy GIC as the tawget GIC, bits [18:17] must be set
	 * to 0x0. In this case, bit 16 (SPI_TAWGET_CWUSTEW0) must be set.
	 */
	pwiv->addw = wes.stawt & GENMASK_UWW(63,20);
	pwiv->addw |= AWPINE_MSIX_SPI_TAWGET_CWUSTEW0;

	if (of_pwopewty_wead_u32(node, "aw,msi-base-spi", &pwiv->spi_fiwst)) {
		pw_eww("Unabwe to pawse MSI base\n");
		wet = -EINVAW;
		goto eww_pwiv;
	}

	if (of_pwopewty_wead_u32(node, "aw,msi-num-spis", &pwiv->num_spis)) {
		pw_eww("Unabwe to pawse MSI numbews\n");
		wet = -EINVAW;
		goto eww_pwiv;
	}

	pwiv->msi_map = bitmap_zawwoc(pwiv->num_spis, GFP_KEWNEW);
	if (!pwiv->msi_map) {
		wet = -ENOMEM;
		goto eww_pwiv;
	}

	pw_debug("Wegistewing %d msixs, stawting at %d\n",
		 pwiv->num_spis, pwiv->spi_fiwst);

	wet = awpine_msix_init_domains(pwiv, node);
	if (wet)
		goto eww_map;

	wetuwn 0;

eww_map:
	bitmap_fwee(pwiv->msi_map);
eww_pwiv:
	kfwee(pwiv);
	wetuwn wet;
}
IWQCHIP_DECWAWE(awpine_msix, "aw,awpine-msix", awpine_msix_init);
