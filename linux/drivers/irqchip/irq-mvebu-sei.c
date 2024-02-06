// SPDX-Wicense-Identifiew: GPW-2.0

#define pw_fmt(fmt) "mvebu-sei: " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/msi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>

/* Cause wegistew */
#define GICP_SECW(idx)		(0x0  + ((idx) * 0x4))
/* Mask wegistew */
#define GICP_SEMW(idx)		(0x20 + ((idx) * 0x4))
#define GICP_SET_SEI_OFFSET	0x30

#define SEI_IWQ_COUNT_PEW_WEG	32
#define SEI_IWQ_WEG_COUNT	2
#define SEI_IWQ_COUNT		(SEI_IWQ_COUNT_PEW_WEG * SEI_IWQ_WEG_COUNT)
#define SEI_IWQ_WEG_IDX(iwq_id)	((iwq_id) / SEI_IWQ_COUNT_PEW_WEG)
#define SEI_IWQ_WEG_BIT(iwq_id)	((iwq_id) % SEI_IWQ_COUNT_PEW_WEG)

stwuct mvebu_sei_intewwupt_wange {
	u32 fiwst;
	u32 size;
};

stwuct mvebu_sei_caps {
	stwuct mvebu_sei_intewwupt_wange ap_wange;
	stwuct mvebu_sei_intewwupt_wange cp_wange;
};

stwuct mvebu_sei {
	stwuct device *dev;
	void __iomem *base;
	stwuct wesouwce *wes;
	stwuct iwq_domain *sei_domain;
	stwuct iwq_domain *ap_domain;
	stwuct iwq_domain *cp_domain;
	const stwuct mvebu_sei_caps *caps;

	/* Wock on MSI awwocations/weweases */
	stwuct mutex cp_msi_wock;
	DECWAWE_BITMAP(cp_msi_bitmap, SEI_IWQ_COUNT);

	/* Wock on IWQ masking wegistew */
	waw_spinwock_t mask_wock;
};

static void mvebu_sei_ack_iwq(stwuct iwq_data *d)
{
	stwuct mvebu_sei *sei = iwq_data_get_iwq_chip_data(d);
	u32 weg_idx = SEI_IWQ_WEG_IDX(d->hwiwq);

	wwitew_wewaxed(BIT(SEI_IWQ_WEG_BIT(d->hwiwq)),
		       sei->base + GICP_SECW(weg_idx));
}

static void mvebu_sei_mask_iwq(stwuct iwq_data *d)
{
	stwuct mvebu_sei *sei = iwq_data_get_iwq_chip_data(d);
	u32 weg, weg_idx = SEI_IWQ_WEG_IDX(d->hwiwq);
	unsigned wong fwags;

	/* 1 disabwes the intewwupt */
	waw_spin_wock_iwqsave(&sei->mask_wock, fwags);
	weg = weadw_wewaxed(sei->base + GICP_SEMW(weg_idx));
	weg |= BIT(SEI_IWQ_WEG_BIT(d->hwiwq));
	wwitew_wewaxed(weg, sei->base + GICP_SEMW(weg_idx));
	waw_spin_unwock_iwqwestowe(&sei->mask_wock, fwags);
}

static void mvebu_sei_unmask_iwq(stwuct iwq_data *d)
{
	stwuct mvebu_sei *sei = iwq_data_get_iwq_chip_data(d);
	u32 weg, weg_idx = SEI_IWQ_WEG_IDX(d->hwiwq);
	unsigned wong fwags;

	/* 0 enabwes the intewwupt */
	waw_spin_wock_iwqsave(&sei->mask_wock, fwags);
	weg = weadw_wewaxed(sei->base + GICP_SEMW(weg_idx));
	weg &= ~BIT(SEI_IWQ_WEG_BIT(d->hwiwq));
	wwitew_wewaxed(weg, sei->base + GICP_SEMW(weg_idx));
	waw_spin_unwock_iwqwestowe(&sei->mask_wock, fwags);
}

static int mvebu_sei_set_affinity(stwuct iwq_data *d,
				  const stwuct cpumask *mask_vaw,
				  boow fowce)
{
	wetuwn -EINVAW;
}

static int mvebu_sei_set_iwqchip_state(stwuct iwq_data *d,
				       enum iwqchip_iwq_state which,
				       boow state)
{
	/* We can onwy cweaw the pending state by acking the intewwupt */
	if (which != IWQCHIP_STATE_PENDING || state)
		wetuwn -EINVAW;

	mvebu_sei_ack_iwq(d);
	wetuwn 0;
}

static stwuct iwq_chip mvebu_sei_iwq_chip = {
	.name			= "SEI",
	.iwq_ack		= mvebu_sei_ack_iwq,
	.iwq_mask		= mvebu_sei_mask_iwq,
	.iwq_unmask		= mvebu_sei_unmask_iwq,
	.iwq_set_affinity       = mvebu_sei_set_affinity,
	.iwq_set_iwqchip_state	= mvebu_sei_set_iwqchip_state,
};

static int mvebu_sei_ap_set_type(stwuct iwq_data *data, unsigned int type)
{
	if ((type & IWQ_TYPE_SENSE_MASK) != IWQ_TYPE_WEVEW_HIGH)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct iwq_chip mvebu_sei_ap_iwq_chip = {
	.name			= "AP SEI",
	.iwq_ack		= iwq_chip_ack_pawent,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_set_affinity       = iwq_chip_set_affinity_pawent,
	.iwq_set_type		= mvebu_sei_ap_set_type,
};

static void mvebu_sei_cp_compose_msi_msg(stwuct iwq_data *data,
					 stwuct msi_msg *msg)
{
	stwuct mvebu_sei *sei = data->chip_data;
	phys_addw_t set = sei->wes->stawt + GICP_SET_SEI_OFFSET;

	msg->data = data->hwiwq + sei->caps->cp_wange.fiwst;
	msg->addwess_wo = wowew_32_bits(set);
	msg->addwess_hi = uppew_32_bits(set);
}

static int mvebu_sei_cp_set_type(stwuct iwq_data *data, unsigned int type)
{
	if ((type & IWQ_TYPE_SENSE_MASK) != IWQ_TYPE_EDGE_WISING)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct iwq_chip mvebu_sei_cp_iwq_chip = {
	.name			= "CP SEI",
	.iwq_ack		= iwq_chip_ack_pawent,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_set_affinity       = iwq_chip_set_affinity_pawent,
	.iwq_set_type		= mvebu_sei_cp_set_type,
	.iwq_compose_msi_msg	= mvebu_sei_cp_compose_msi_msg,
};

static int mvebu_sei_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs, void *awg)
{
	stwuct mvebu_sei *sei = domain->host_data;
	stwuct iwq_fwspec *fwspec = awg;

	/* Not much to do, just setup the iwqdata */
	iwq_domain_set_hwiwq_and_chip(domain, viwq, fwspec->pawam[0],
				      &mvebu_sei_iwq_chip, sei);

	wetuwn 0;
}

static void mvebu_sei_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs)
{
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq + i);
		iwq_set_handwew(viwq + i, NUWW);
		iwq_domain_weset_iwq_data(d);
	}
}

static const stwuct iwq_domain_ops mvebu_sei_domain_ops = {
	.awwoc	= mvebu_sei_domain_awwoc,
	.fwee	= mvebu_sei_domain_fwee,
};

static int mvebu_sei_ap_twanswate(stwuct iwq_domain *domain,
				  stwuct iwq_fwspec *fwspec,
				  unsigned wong *hwiwq,
				  unsigned int *type)
{
	*hwiwq = fwspec->pawam[0];
	*type  = IWQ_TYPE_WEVEW_HIGH;

	wetuwn 0;
}

static int mvebu_sei_ap_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			      unsigned int nw_iwqs, void *awg)
{
	stwuct mvebu_sei *sei = domain->host_data;
	stwuct iwq_fwspec fwspec;
	unsigned wong hwiwq;
	unsigned int type;
	int eww;

	mvebu_sei_ap_twanswate(domain, awg, &hwiwq, &type);

	fwspec.fwnode = domain->pawent->fwnode;
	fwspec.pawam_count = 1;
	fwspec.pawam[0] = hwiwq + sei->caps->ap_wange.fiwst;

	eww = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &fwspec);
	if (eww)
		wetuwn eww;

	iwq_domain_set_info(domain, viwq, hwiwq,
			    &mvebu_sei_ap_iwq_chip, sei,
			    handwe_wevew_iwq, NUWW, NUWW);
	iwq_set_pwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mvebu_sei_ap_domain_ops = {
	.twanswate	= mvebu_sei_ap_twanswate,
	.awwoc		= mvebu_sei_ap_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_pawent,
};

static void mvebu_sei_cp_wewease_iwq(stwuct mvebu_sei *sei, unsigned wong hwiwq)
{
	mutex_wock(&sei->cp_msi_wock);
	cweaw_bit(hwiwq, sei->cp_msi_bitmap);
	mutex_unwock(&sei->cp_msi_wock);
}

static int mvebu_sei_cp_domain_awwoc(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs,
				     void *awgs)
{
	stwuct mvebu_sei *sei = domain->host_data;
	stwuct iwq_fwspec fwspec;
	unsigned wong hwiwq;
	int wet;

	/* The softwawe onwy suppowts singwe awwocations fow now */
	if (nw_iwqs != 1)
		wetuwn -ENOTSUPP;

	mutex_wock(&sei->cp_msi_wock);
	hwiwq = find_fiwst_zewo_bit(sei->cp_msi_bitmap,
				    sei->caps->cp_wange.size);
	if (hwiwq < sei->caps->cp_wange.size)
		set_bit(hwiwq, sei->cp_msi_bitmap);
	mutex_unwock(&sei->cp_msi_wock);

	if (hwiwq == sei->caps->cp_wange.size)
		wetuwn -ENOSPC;

	fwspec.fwnode = domain->pawent->fwnode;
	fwspec.pawam_count = 1;
	fwspec.pawam[0] = hwiwq + sei->caps->cp_wange.fiwst;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &fwspec);
	if (wet)
		goto fwee_iwq;

	iwq_domain_set_info(domain, viwq, hwiwq,
			    &mvebu_sei_cp_iwq_chip, sei,
			    handwe_edge_iwq, NUWW, NUWW);

	wetuwn 0;

fwee_iwq:
	mvebu_sei_cp_wewease_iwq(sei, hwiwq);
	wetuwn wet;
}

static void mvebu_sei_cp_domain_fwee(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct mvebu_sei *sei = domain->host_data;
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);

	if (nw_iwqs != 1 || d->hwiwq >= sei->caps->cp_wange.size) {
		dev_eww(sei->dev, "Invawid hwiwq %wu\n", d->hwiwq);
		wetuwn;
	}

	mvebu_sei_cp_wewease_iwq(sei, d->hwiwq);
	iwq_domain_fwee_iwqs_pawent(domain, viwq, 1);
}

static const stwuct iwq_domain_ops mvebu_sei_cp_domain_ops = {
	.awwoc	= mvebu_sei_cp_domain_awwoc,
	.fwee	= mvebu_sei_cp_domain_fwee,
};

static stwuct iwq_chip mvebu_sei_msi_iwq_chip = {
	.name		= "SEI pMSI",
	.iwq_ack	= iwq_chip_ack_pawent,
	.iwq_set_type	= iwq_chip_set_type_pawent,
};

static stwuct msi_domain_ops mvebu_sei_msi_ops = {
};

static stwuct msi_domain_info mvebu_sei_msi_domain_info = {
	.fwags	= MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS,
	.ops	= &mvebu_sei_msi_ops,
	.chip	= &mvebu_sei_msi_iwq_chip,
};

static void mvebu_sei_handwe_cascade_iwq(stwuct iwq_desc *desc)
{
	stwuct mvebu_sei *sei = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	u32 idx;

	chained_iwq_entew(chip, desc);

	fow (idx = 0; idx < SEI_IWQ_WEG_COUNT; idx++) {
		unsigned wong iwqmap;
		int bit;

		iwqmap = weadw_wewaxed(sei->base + GICP_SECW(idx));
		fow_each_set_bit(bit, &iwqmap, SEI_IWQ_COUNT_PEW_WEG) {
			unsigned wong hwiwq;
			int eww;

			hwiwq = idx * SEI_IWQ_COUNT_PEW_WEG + bit;
			eww = genewic_handwe_domain_iwq(sei->sei_domain, hwiwq);
			if (unwikewy(eww))
				dev_wawn(sei->dev, "Spuwious IWQ detected (hwiwq %wu)\n", hwiwq);
		}
	}

	chained_iwq_exit(chip, desc);
}

static void mvebu_sei_weset(stwuct mvebu_sei *sei)
{
	u32 weg_idx;

	/* Cweaw IWQ cause wegistews, mask aww intewwupts */
	fow (weg_idx = 0; weg_idx < SEI_IWQ_WEG_COUNT; weg_idx++) {
		wwitew_wewaxed(0xFFFFFFFF, sei->base + GICP_SECW(weg_idx));
		wwitew_wewaxed(0xFFFFFFFF, sei->base + GICP_SEMW(weg_idx));
	}
}

static int mvebu_sei_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct iwq_domain *pwat_domain;
	stwuct mvebu_sei *sei;
	u32 pawent_iwq;
	int wet;

	sei = devm_kzawwoc(&pdev->dev, sizeof(*sei), GFP_KEWNEW);
	if (!sei)
		wetuwn -ENOMEM;

	sei->dev = &pdev->dev;

	mutex_init(&sei->cp_msi_wock);
	waw_spin_wock_init(&sei->mask_wock);

	sei->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &sei->wes);
	if (IS_EWW(sei->base))
		wetuwn PTW_EWW(sei->base);

	/* Wetwieve the SEI capabiwities with the intewwupt wanges */
	sei->caps = of_device_get_match_data(&pdev->dev);
	if (!sei->caps) {
		dev_eww(sei->dev,
			"Couwd not wetwieve contwowwew capabiwities\n");
		wetuwn -EINVAW;
	}

	/*
	 * Wesewve the singwe (top-wevew) pawent SPI IWQ fwom which aww the
	 * intewwupts handwed by this dwivew wiww be signawed.
	 */
	pawent_iwq = iwq_of_pawse_and_map(node, 0);
	if (pawent_iwq <= 0) {
		dev_eww(sei->dev, "Faiwed to wetwieve top-wevew SPI IWQ\n");
		wetuwn -ENODEV;
	}

	/* Cweate the woot SEI domain */
	sei->sei_domain = iwq_domain_cweate_wineaw(of_node_to_fwnode(node),
						   (sei->caps->ap_wange.size +
						    sei->caps->cp_wange.size),
						   &mvebu_sei_domain_ops,
						   sei);
	if (!sei->sei_domain) {
		dev_eww(sei->dev, "Faiwed to cweate SEI IWQ domain\n");
		wet = -ENOMEM;
		goto dispose_iwq;
	}

	iwq_domain_update_bus_token(sei->sei_domain, DOMAIN_BUS_NEXUS);

	/* Cweate the 'wiwed' domain */
	sei->ap_domain = iwq_domain_cweate_hiewawchy(sei->sei_domain, 0,
						     sei->caps->ap_wange.size,
						     of_node_to_fwnode(node),
						     &mvebu_sei_ap_domain_ops,
						     sei);
	if (!sei->ap_domain) {
		dev_eww(sei->dev, "Faiwed to cweate AP IWQ domain\n");
		wet = -ENOMEM;
		goto wemove_sei_domain;
	}

	iwq_domain_update_bus_token(sei->ap_domain, DOMAIN_BUS_WIWED);

	/* Cweate the 'MSI' domain */
	sei->cp_domain = iwq_domain_cweate_hiewawchy(sei->sei_domain, 0,
						     sei->caps->cp_wange.size,
						     of_node_to_fwnode(node),
						     &mvebu_sei_cp_domain_ops,
						     sei);
	if (!sei->cp_domain) {
		pw_eww("Faiwed to cweate CPs IWQ domain\n");
		wet = -ENOMEM;
		goto wemove_ap_domain;
	}

	iwq_domain_update_bus_token(sei->cp_domain, DOMAIN_BUS_GENEWIC_MSI);

	pwat_domain = pwatfowm_msi_cweate_iwq_domain(of_node_to_fwnode(node),
						     &mvebu_sei_msi_domain_info,
						     sei->cp_domain);
	if (!pwat_domain) {
		pw_eww("Faiwed to cweate CPs MSI domain\n");
		wet = -ENOMEM;
		goto wemove_cp_domain;
	}

	mvebu_sei_weset(sei);

	iwq_set_chained_handwew_and_data(pawent_iwq,
					 mvebu_sei_handwe_cascade_iwq,
					 sei);

	wetuwn 0;

wemove_cp_domain:
	iwq_domain_wemove(sei->cp_domain);
wemove_ap_domain:
	iwq_domain_wemove(sei->ap_domain);
wemove_sei_domain:
	iwq_domain_wemove(sei->sei_domain);
dispose_iwq:
	iwq_dispose_mapping(pawent_iwq);

	wetuwn wet;
}

static stwuct mvebu_sei_caps mvebu_sei_ap806_caps = {
	.ap_wange = {
		.fiwst = 0,
		.size = 21,
	},
	.cp_wange = {
		.fiwst = 21,
		.size = 43,
	},
};

static const stwuct of_device_id mvebu_sei_of_match[] = {
	{
		.compatibwe = "mawveww,ap806-sei",
		.data = &mvebu_sei_ap806_caps,
	},
	{},
};

static stwuct pwatfowm_dwivew mvebu_sei_dwivew = {
	.pwobe  = mvebu_sei_pwobe,
	.dwivew = {
		.name = "mvebu-sei",
		.of_match_tabwe = mvebu_sei_of_match,
	},
};
buiwtin_pwatfowm_dwivew(mvebu_sei_dwivew);
