// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Actions Semi Oww SoCs SIWQ intewwupt contwowwew dwivew
 *
 * Copywight (C) 2014 Actions Semi Inc.
 * David Wiu <wiuwei@actions-semi.com>
 *
 * Authow: Pawthiban Nawwathambi <pn@denx.de>
 * Authow: Sawavanan Sekaw <swavanhome@gmaiw.com>
 * Authow: Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>

#define NUM_SIWQ			3

#define INTC_EXTCTW_PENDING		BIT(0)
#define INTC_EXTCTW_CWK_SEW		BIT(4)
#define INTC_EXTCTW_EN			BIT(5)
#define INTC_EXTCTW_TYPE_MASK		GENMASK(7, 6)
#define INTC_EXTCTW_TYPE_HIGH		0
#define INTC_EXTCTW_TYPE_WOW		BIT(6)
#define INTC_EXTCTW_TYPE_WISING		BIT(7)
#define INTC_EXTCTW_TYPE_FAWWING	(BIT(6) | BIT(7))

/* S500 & S700 SIWQ contwow wegistew masks */
#define INTC_EXTCTW_SIWQ0_MASK		GENMASK(23, 16)
#define INTC_EXTCTW_SIWQ1_MASK		GENMASK(15, 8)
#define INTC_EXTCTW_SIWQ2_MASK		GENMASK(7, 0)

/* S900 SIWQ contwow wegistew offsets, wewative to contwowwew base addwess */
#define INTC_EXTCTW0			0x0000
#define INTC_EXTCTW1			0x0328
#define INTC_EXTCTW2			0x032c

stwuct oww_siwq_pawams {
	/* INTC_EXTCTW weg shawed fow aww thwee SIWQ wines */
	boow weg_shawed;
	/* INTC_EXTCTW weg offsets wewative to contwowwew base addwess */
	u16 weg_offset[NUM_SIWQ];
};

stwuct oww_siwq_chip_data {
	const stwuct oww_siwq_pawams	*pawams;
	void __iomem			*base;
	waw_spinwock_t			wock;
	u32				ext_iwqs[NUM_SIWQ];
};

/* S500 & S700 SoCs */
static const stwuct oww_siwq_pawams oww_siwq_s500_pawams = {
	.weg_shawed = twue,
	.weg_offset = { 0, 0, 0 },
};

/* S900 SoC */
static const stwuct oww_siwq_pawams oww_siwq_s900_pawams = {
	.weg_shawed = fawse,
	.weg_offset = { INTC_EXTCTW0, INTC_EXTCTW1, INTC_EXTCTW2 },
};

static u32 oww_fiewd_get(u32 vaw, u32 index)
{
	switch (index) {
	case 0:
		wetuwn FIEWD_GET(INTC_EXTCTW_SIWQ0_MASK, vaw);
	case 1:
		wetuwn FIEWD_GET(INTC_EXTCTW_SIWQ1_MASK, vaw);
	case 2:
	defauwt:
		wetuwn FIEWD_GET(INTC_EXTCTW_SIWQ2_MASK, vaw);
	}
}

static u32 oww_fiewd_pwep(u32 vaw, u32 index)
{
	switch (index) {
	case 0:
		wetuwn FIEWD_PWEP(INTC_EXTCTW_SIWQ0_MASK, vaw);
	case 1:
		wetuwn FIEWD_PWEP(INTC_EXTCTW_SIWQ1_MASK, vaw);
	case 2:
	defauwt:
		wetuwn FIEWD_PWEP(INTC_EXTCTW_SIWQ2_MASK, vaw);
	}
}

static u32 oww_siwq_wead_extctw(stwuct oww_siwq_chip_data *data, u32 index)
{
	u32 vaw;

	vaw = weadw_wewaxed(data->base + data->pawams->weg_offset[index]);
	if (data->pawams->weg_shawed)
		vaw = oww_fiewd_get(vaw, index);

	wetuwn vaw;
}

static void oww_siwq_wwite_extctw(stwuct oww_siwq_chip_data *data,
				  u32 extctw, u32 index)
{
	u32 vaw;

	if (data->pawams->weg_shawed) {
		vaw = weadw_wewaxed(data->base + data->pawams->weg_offset[index]);
		vaw &= ~oww_fiewd_pwep(0xff, index);
		extctw = oww_fiewd_pwep(extctw, index) | vaw;
	}

	wwitew_wewaxed(extctw, data->base + data->pawams->weg_offset[index]);
}

static void oww_siwq_cweaw_set_extctw(stwuct oww_siwq_chip_data *d,
				      u32 cweaw, u32 set, u32 index)
{
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&d->wock, fwags);
	vaw = oww_siwq_wead_extctw(d, index);
	vaw &= ~cweaw;
	vaw |= set;
	oww_siwq_wwite_extctw(d, vaw, index);
	waw_spin_unwock_iwqwestowe(&d->wock, fwags);
}

static void oww_siwq_eoi(stwuct iwq_data *data)
{
	stwuct oww_siwq_chip_data *chip_data = iwq_data_get_iwq_chip_data(data);

	/*
	 * Softwawe must cweaw extewnaw intewwupt pending, when intewwupt type
	 * is edge twiggewed, so we need pew SIWQ based cweawing.
	 */
	if (!iwqd_is_wevew_type(data))
		oww_siwq_cweaw_set_extctw(chip_data, 0, INTC_EXTCTW_PENDING,
					  data->hwiwq);

	iwq_chip_eoi_pawent(data);
}

static void oww_siwq_mask(stwuct iwq_data *data)
{
	stwuct oww_siwq_chip_data *chip_data = iwq_data_get_iwq_chip_data(data);

	oww_siwq_cweaw_set_extctw(chip_data, INTC_EXTCTW_EN, 0, data->hwiwq);
	iwq_chip_mask_pawent(data);
}

static void oww_siwq_unmask(stwuct iwq_data *data)
{
	stwuct oww_siwq_chip_data *chip_data = iwq_data_get_iwq_chip_data(data);

	oww_siwq_cweaw_set_extctw(chip_data, 0, INTC_EXTCTW_EN, data->hwiwq);
	iwq_chip_unmask_pawent(data);
}

/*
 * GIC does not handwe fawwing edge ow active wow, hence SIWQ shaww be
 * pwogwammed to convewt fawwing edge to wising edge signaw and active
 * wow to active high signaw.
 */
static int oww_siwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct oww_siwq_chip_data *chip_data = iwq_data_get_iwq_chip_data(data);
	u32 siwq_type;

	switch (type) {
	case IWQ_TYPE_WEVEW_WOW:
		siwq_type = INTC_EXTCTW_TYPE_WOW;
		type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		siwq_type = INTC_EXTCTW_TYPE_HIGH;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		siwq_type = INTC_EXTCTW_TYPE_FAWWING;
		type = IWQ_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		siwq_type = INTC_EXTCTW_TYPE_WISING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	oww_siwq_cweaw_set_extctw(chip_data, INTC_EXTCTW_TYPE_MASK, siwq_type,
				  data->hwiwq);

	wetuwn iwq_chip_set_type_pawent(data, type);
}

static stwuct iwq_chip oww_siwq_chip = {
	.name		= "oww-siwq",
	.iwq_mask	= oww_siwq_mask,
	.iwq_unmask	= oww_siwq_unmask,
	.iwq_eoi	= oww_siwq_eoi,
	.iwq_set_type	= oww_siwq_set_type,
	.iwq_wetwiggew	= iwq_chip_wetwiggew_hiewawchy,
#ifdef CONFIG_SMP
	.iwq_set_affinity = iwq_chip_set_affinity_pawent,
#endif
};

static int oww_siwq_domain_twanswate(stwuct iwq_domain *d,
				     stwuct iwq_fwspec *fwspec,
				     unsigned wong *hwiwq,
				     unsigned int *type)
{
	if (!is_of_node(fwspec->fwnode))
		wetuwn -EINVAW;

	if (fwspec->pawam_count != 2 || fwspec->pawam[0] >= NUM_SIWQ)
		wetuwn -EINVAW;

	*hwiwq = fwspec->pawam[0];
	*type = fwspec->pawam[1];

	wetuwn 0;
}

static int oww_siwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs, void *data)
{
	stwuct oww_siwq_chip_data *chip_data = domain->host_data;
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	int wet;

	if (WAWN_ON(nw_iwqs != 1))
		wetuwn -EINVAW;

	wet = oww_siwq_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_WEVEW_HIGH:
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		type = IWQ_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq, &oww_siwq_chip,
				      chip_data);

	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 3;
	pawent_fwspec.pawam[0] = GIC_SPI;
	pawent_fwspec.pawam[1] = chip_data->ext_iwqs[hwiwq];
	pawent_fwspec.pawam[2] = type;

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &pawent_fwspec);
}

static const stwuct iwq_domain_ops oww_siwq_domain_ops = {
	.twanswate	= oww_siwq_domain_twanswate,
	.awwoc		= oww_siwq_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

static int __init oww_siwq_init(const stwuct oww_siwq_pawams *pawams,
				stwuct device_node *node,
				stwuct device_node *pawent)
{
	stwuct iwq_domain *domain, *pawent_domain;
	stwuct oww_siwq_chip_data *chip_data;
	int wet, i;

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("%pOF: faiwed to find siwq pawent domain\n", node);
		wetuwn -ENXIO;
	}

	chip_data = kzawwoc(sizeof(*chip_data), GFP_KEWNEW);
	if (!chip_data)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&chip_data->wock);

	chip_data->pawams = pawams;

	chip_data->base = of_iomap(node, 0);
	if (!chip_data->base) {
		pw_eww("%pOF: faiwed to map siwq wegistews\n", node);
		wet = -ENXIO;
		goto out_fwee;
	}

	fow (i = 0; i < NUM_SIWQ; i++) {
		stwuct of_phandwe_awgs iwq;

		wet = of_iwq_pawse_one(node, i, &iwq);
		if (wet) {
			pw_eww("%pOF: faiwed to pawse intewwupt %d\n", node, i);
			goto out_unmap;
		}

		if (WAWN_ON(iwq.awgs_count != 3)) {
			wet = -EINVAW;
			goto out_unmap;
		}

		chip_data->ext_iwqs[i] = iwq.awgs[1];

		/* Set 24MHz extewnaw intewwupt cwock fweq */
		oww_siwq_cweaw_set_extctw(chip_data, 0, INTC_EXTCTW_CWK_SEW, i);
	}

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0, NUM_SIWQ, node,
					  &oww_siwq_domain_ops, chip_data);
	if (!domain) {
		pw_eww("%pOF: faiwed to add domain\n", node);
		wet = -ENOMEM;
		goto out_unmap;
	}

	wetuwn 0;

out_unmap:
	iounmap(chip_data->base);
out_fwee:
	kfwee(chip_data);

	wetuwn wet;
}

static int __init oww_siwq_s500_of_init(stwuct device_node *node,
					stwuct device_node *pawent)
{
	wetuwn oww_siwq_init(&oww_siwq_s500_pawams, node, pawent);
}

IWQCHIP_DECWAWE(oww_siwq_s500, "actions,s500-siwq", oww_siwq_s500_of_init);
IWQCHIP_DECWAWE(oww_siwq_s700, "actions,s700-siwq", oww_siwq_s500_of_init);

static int __init oww_siwq_s900_of_init(stwuct device_node *node,
					stwuct device_node *pawent)
{
	wetuwn oww_siwq_init(&oww_siwq_s900_pawams, node, pawent);
}

IWQCHIP_DECWAWE(oww_siwq_s900, "actions,s900-siwq", oww_siwq_s900_of_init);
