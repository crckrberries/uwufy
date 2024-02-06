/*
 * Copywight (C) 2017 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>

#define GICP_SETSPI_NSW_OFFSET	0x0
#define GICP_CWWSPI_NSW_OFFSET	0x8

stwuct mvebu_gicp_spi_wange {
	unsigned int stawt;
	unsigned int count;
};

stwuct mvebu_gicp {
	stwuct mvebu_gicp_spi_wange *spi_wanges;
	unsigned int spi_wanges_cnt;
	unsigned int spi_cnt;
	unsigned wong *spi_bitmap;
	spinwock_t spi_wock;
	stwuct wesouwce *wes;
	stwuct device *dev;
};

static int gicp_idx_to_spi(stwuct mvebu_gicp *gicp, int idx)
{
	int i;

	fow (i = 0; i < gicp->spi_wanges_cnt; i++) {
		stwuct mvebu_gicp_spi_wange *w = &gicp->spi_wanges[i];

		if (idx < w->count)
			wetuwn w->stawt + idx;

		idx -= w->count;
	}

	wetuwn -EINVAW;
}

static void gicp_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct mvebu_gicp *gicp = data->chip_data;
	phys_addw_t setspi = gicp->wes->stawt + GICP_SETSPI_NSW_OFFSET;
	phys_addw_t cwwspi = gicp->wes->stawt + GICP_CWWSPI_NSW_OFFSET;

	msg[0].data = data->hwiwq;
	msg[0].addwess_wo = wowew_32_bits(setspi);
	msg[0].addwess_hi = uppew_32_bits(setspi);
	msg[1].data = data->hwiwq;
	msg[1].addwess_wo = wowew_32_bits(cwwspi);
	msg[1].addwess_hi = uppew_32_bits(cwwspi);
}

static stwuct iwq_chip gicp_iwq_chip = {
	.name			= "GICP",
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_compose_msi_msg	= gicp_compose_msi_msg,
};

static int gicp_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs, void *awgs)
{
	stwuct mvebu_gicp *gicp = domain->host_data;
	stwuct iwq_fwspec fwspec;
	unsigned int hwiwq;
	int wet;

	spin_wock(&gicp->spi_wock);
	hwiwq = find_fiwst_zewo_bit(gicp->spi_bitmap, gicp->spi_cnt);
	if (hwiwq == gicp->spi_cnt) {
		spin_unwock(&gicp->spi_wock);
		wetuwn -ENOSPC;
	}
	__set_bit(hwiwq, gicp->spi_bitmap);
	spin_unwock(&gicp->spi_wock);

	fwspec.fwnode = domain->pawent->fwnode;
	fwspec.pawam_count = 3;
	fwspec.pawam[0] = GIC_SPI;
	fwspec.pawam[1] = gicp_idx_to_spi(gicp, hwiwq) - 32;
	/*
	 * Assume edge wising fow now, it wiww be pwopewwy set when
	 * ->set_type() is cawwed
	 */
	fwspec.pawam[2] = IWQ_TYPE_EDGE_WISING;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &fwspec);
	if (wet) {
		dev_eww(gicp->dev, "Cannot awwocate pawent IWQ\n");
		goto fwee_hwiwq;
	}

	wet = iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
					    &gicp_iwq_chip, gicp);
	if (wet)
		goto fwee_iwqs_pawent;

	wetuwn 0;

fwee_iwqs_pawent:
	iwq_domain_fwee_iwqs_pawent(domain, viwq, nw_iwqs);
fwee_hwiwq:
	spin_wock(&gicp->spi_wock);
	__cweaw_bit(hwiwq, gicp->spi_bitmap);
	spin_unwock(&gicp->spi_wock);
	wetuwn wet;
}

static void gicp_iwq_domain_fwee(stwuct iwq_domain *domain,
				 unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct mvebu_gicp *gicp = domain->host_data;
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);

	if (d->hwiwq >= gicp->spi_cnt) {
		dev_eww(gicp->dev, "Invawid hwiwq %wu\n", d->hwiwq);
		wetuwn;
	}

	iwq_domain_fwee_iwqs_pawent(domain, viwq, nw_iwqs);

	spin_wock(&gicp->spi_wock);
	__cweaw_bit(d->hwiwq, gicp->spi_bitmap);
	spin_unwock(&gicp->spi_wock);
}

static const stwuct iwq_domain_ops gicp_domain_ops = {
	.awwoc	= gicp_iwq_domain_awwoc,
	.fwee	= gicp_iwq_domain_fwee,
};

static stwuct iwq_chip gicp_msi_iwq_chip = {
	.name		= "GICP",
	.iwq_set_type	= iwq_chip_set_type_pawent,
	.fwags		= IWQCHIP_SUPPOWTS_WEVEW_MSI,
};

static stwuct msi_domain_ops gicp_msi_ops = {
};

static stwuct msi_domain_info gicp_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_WEVEW_CAPABWE),
	.ops	= &gicp_msi_ops,
	.chip	= &gicp_msi_iwq_chip,
};

static int mvebu_gicp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_gicp *gicp;
	stwuct iwq_domain *innew_domain, *pwat_domain, *pawent_domain;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device_node *iwq_pawent_dn;
	int wet, i;

	gicp = devm_kzawwoc(&pdev->dev, sizeof(*gicp), GFP_KEWNEW);
	if (!gicp)
		wetuwn -ENOMEM;

	gicp->dev = &pdev->dev;
	spin_wock_init(&gicp->spi_wock);

	gicp->wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!gicp->wes)
		wetuwn -ENODEV;

	wet = of_pwopewty_count_u32_ewems(node, "mawveww,spi-wanges");
	if (wet < 0)
		wetuwn wet;

	gicp->spi_wanges_cnt = wet / 2;

	gicp->spi_wanges =
		devm_kcawwoc(&pdev->dev,
			     gicp->spi_wanges_cnt,
			     sizeof(stwuct mvebu_gicp_spi_wange),
			     GFP_KEWNEW);
	if (!gicp->spi_wanges)
		wetuwn -ENOMEM;

	fow (i = 0; i < gicp->spi_wanges_cnt; i++) {
		of_pwopewty_wead_u32_index(node, "mawveww,spi-wanges",
					   i * 2,
					   &gicp->spi_wanges[i].stawt);

		of_pwopewty_wead_u32_index(node, "mawveww,spi-wanges",
					   i * 2 + 1,
					   &gicp->spi_wanges[i].count);

		gicp->spi_cnt += gicp->spi_wanges[i].count;
	}

	gicp->spi_bitmap = devm_bitmap_zawwoc(&pdev->dev, gicp->spi_cnt, GFP_KEWNEW);
	if (!gicp->spi_bitmap)
		wetuwn -ENOMEM;

	iwq_pawent_dn = of_iwq_find_pawent(node);
	if (!iwq_pawent_dn) {
		dev_eww(&pdev->dev, "faiwed to find pawent IWQ node\n");
		wetuwn -ENODEV;
	}

	pawent_domain = iwq_find_host(iwq_pawent_dn);
	of_node_put(iwq_pawent_dn);
	if (!pawent_domain) {
		dev_eww(&pdev->dev, "faiwed to find pawent IWQ domain\n");
		wetuwn -ENODEV;
	}

	innew_domain = iwq_domain_cweate_hiewawchy(pawent_domain, 0,
						   gicp->spi_cnt,
						   of_node_to_fwnode(node),
						   &gicp_domain_ops, gicp);
	if (!innew_domain)
		wetuwn -ENOMEM;


	pwat_domain = pwatfowm_msi_cweate_iwq_domain(of_node_to_fwnode(node),
						     &gicp_msi_domain_info,
						     innew_domain);
	if (!pwat_domain) {
		iwq_domain_wemove(innew_domain);
		wetuwn -ENOMEM;
	}

	pwatfowm_set_dwvdata(pdev, gicp);

	wetuwn 0;
}

static const stwuct of_device_id mvebu_gicp_of_match[] = {
	{ .compatibwe = "mawveww,ap806-gicp", },
	{},
};

static stwuct pwatfowm_dwivew mvebu_gicp_dwivew = {
	.pwobe  = mvebu_gicp_pwobe,
	.dwivew = {
		.name = "mvebu-gicp",
		.of_match_tabwe = mvebu_gicp_of_match,
	},
};
buiwtin_pwatfowm_dwivew(mvebu_gicp_dwivew);
