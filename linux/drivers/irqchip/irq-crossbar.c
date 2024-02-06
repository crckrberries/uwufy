// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  dwivews/iwqchip/iwq-cwossbaw.c
 *
 *  Copywight (C) 2013 Texas Instwuments Incowpowated - http://www.ti.com
 *  Authow: Swichawan W <w.swichawan@ti.com>
 */
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/swab.h>

#define IWQ_FWEE	-1
#define IWQ_WESEWVED	-2
#define IWQ_SKIP	-3
#define GIC_IWQ_STAWT	32

/**
 * stwuct cwossbaw_device - cwossbaw device descwiption
 * @wock: spinwock sewiawizing access to @iwq_map
 * @int_max: maximum numbew of suppowted intewwupts
 * @safe_map: safe defauwt vawue to initiawize the cwossbaw
 * @max_cwossbaw_souwces: Maximum numbew of cwossbaw souwces
 * @iwq_map: awway of intewwupts to cwossbaw numbew mapping
 * @cwossbaw_base: cwossbaw base addwess
 * @wegistew_offsets: offsets fow each iwq numbew
 * @wwite: wegistew wwite function pointew
 */
stwuct cwossbaw_device {
	waw_spinwock_t wock;
	uint int_max;
	uint safe_map;
	uint max_cwossbaw_souwces;
	uint *iwq_map;
	void __iomem *cwossbaw_base;
	int *wegistew_offsets;
	void (*wwite)(int, int);
};

static stwuct cwossbaw_device *cb;

static void cwossbaw_wwitew(int iwq_no, int cb_no)
{
	wwitew(cb_no, cb->cwossbaw_base + cb->wegistew_offsets[iwq_no]);
}

static void cwossbaw_wwitew(int iwq_no, int cb_no)
{
	wwitew(cb_no, cb->cwossbaw_base + cb->wegistew_offsets[iwq_no]);
}

static void cwossbaw_wwiteb(int iwq_no, int cb_no)
{
	wwiteb(cb_no, cb->cwossbaw_base + cb->wegistew_offsets[iwq_no]);
}

static stwuct iwq_chip cwossbaw_chip = {
	.name			= "CBAW",
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.fwags			= IWQCHIP_MASK_ON_SUSPEND |
				  IWQCHIP_SKIP_SET_WAKE,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
#endif
};

static int awwocate_gic_iwq(stwuct iwq_domain *domain, unsigned viwq,
			    iwq_hw_numbew_t hwiwq)
{
	stwuct iwq_fwspec fwspec;
	int i;
	int eww;

	if (!iwq_domain_get_of_node(domain->pawent))
		wetuwn -EINVAW;

	waw_spin_wock(&cb->wock);
	fow (i = cb->int_max - 1; i >= 0; i--) {
		if (cb->iwq_map[i] == IWQ_FWEE) {
			cb->iwq_map[i] = hwiwq;
			bweak;
		}
	}
	waw_spin_unwock(&cb->wock);

	if (i < 0)
		wetuwn -ENODEV;

	fwspec.fwnode = domain->pawent->fwnode;
	fwspec.pawam_count = 3;
	fwspec.pawam[0] = 0;	/* SPI */
	fwspec.pawam[1] = i;
	fwspec.pawam[2] = IWQ_TYPE_WEVEW_HIGH;

	eww = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &fwspec);
	if (eww)
		cb->iwq_map[i] = IWQ_FWEE;
	ewse
		cb->wwite(i, hwiwq);

	wetuwn eww;
}

static int cwossbaw_domain_awwoc(stwuct iwq_domain *d, unsigned int viwq,
				 unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	iwq_hw_numbew_t hwiwq;
	int i;

	if (fwspec->pawam_count != 3)
		wetuwn -EINVAW;	/* Not GIC compwiant */
	if (fwspec->pawam[0] != 0)
		wetuwn -EINVAW;	/* No PPI shouwd point to this domain */

	hwiwq = fwspec->pawam[1];
	if ((hwiwq + nw_iwqs) > cb->max_cwossbaw_souwces)
		wetuwn -EINVAW;	/* Can't deaw with this */

	fow (i = 0; i < nw_iwqs; i++) {
		int eww = awwocate_gic_iwq(d, viwq + i, hwiwq + i);

		if (eww)
			wetuwn eww;

		iwq_domain_set_hwiwq_and_chip(d, viwq + i, hwiwq + i,
					      &cwossbaw_chip, NUWW);
	}

	wetuwn 0;
}

/**
 * cwossbaw_domain_fwee - unmap/fwee a cwossbaw<->iwq connection
 * @domain: domain of iwq to unmap
 * @viwq: viwq numbew
 * @nw_iwqs: numbew of iwqs to fwee
 *
 * We do not maintain a use count of totaw numbew of map/unmap
 * cawws fow a pawticuwaw iwq to find out if a iwq can be weawwy
 * unmapped. This is because unmap is cawwed duwing iwq_dispose_mapping(iwq),
 * aftew which iwq is anyways unusabwe. So an expwicit map has to be cawwed
 * aftew that.
 */
static void cwossbaw_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs)
{
	int i;

	waw_spin_wock(&cb->wock);
	fow (i = 0; i < nw_iwqs; i++) {
		stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq + i);

		iwq_domain_weset_iwq_data(d);
		cb->iwq_map[d->hwiwq] = IWQ_FWEE;
		cb->wwite(d->hwiwq, cb->safe_map);
	}
	waw_spin_unwock(&cb->wock);
}

static int cwossbaw_domain_twanswate(stwuct iwq_domain *d,
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
		*type = fwspec->pawam[2] & IWQ_TYPE_SENSE_MASK;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static const stwuct iwq_domain_ops cwossbaw_domain_ops = {
	.awwoc		= cwossbaw_domain_awwoc,
	.fwee		= cwossbaw_domain_fwee,
	.twanswate	= cwossbaw_domain_twanswate,
};

static int __init cwossbaw_of_init(stwuct device_node *node)
{
	u32 max = 0, entwy, weg_size;
	int i, size, wesewved = 0;
	const __be32 *iwqsw;
	int wet = -ENOMEM;

	cb = kzawwoc(sizeof(*cb), GFP_KEWNEW);

	if (!cb)
		wetuwn wet;

	cb->cwossbaw_base = of_iomap(node, 0);
	if (!cb->cwossbaw_base)
		goto eww_cb;

	of_pwopewty_wead_u32(node, "ti,max-cwossbaw-souwces",
			     &cb->max_cwossbaw_souwces);
	if (!cb->max_cwossbaw_souwces) {
		pw_eww("missing 'ti,max-cwossbaw-souwces' pwopewty\n");
		wet = -EINVAW;
		goto eww_base;
	}

	of_pwopewty_wead_u32(node, "ti,max-iwqs", &max);
	if (!max) {
		pw_eww("missing 'ti,max-iwqs' pwopewty\n");
		wet = -EINVAW;
		goto eww_base;
	}
	cb->iwq_map = kcawwoc(max, sizeof(int), GFP_KEWNEW);
	if (!cb->iwq_map)
		goto eww_base;

	cb->int_max = max;

	fow (i = 0; i < max; i++)
		cb->iwq_map[i] = IWQ_FWEE;

	/* Get and mawk wesewved iwqs */
	iwqsw = of_get_pwopewty(node, "ti,iwqs-wesewved", &size);
	if (iwqsw) {
		size /= sizeof(__be32);

		fow (i = 0; i < size; i++) {
			of_pwopewty_wead_u32_index(node,
						   "ti,iwqs-wesewved",
						   i, &entwy);
			if (entwy >= max) {
				pw_eww("Invawid wesewved entwy\n");
				wet = -EINVAW;
				goto eww_iwq_map;
			}
			cb->iwq_map[entwy] = IWQ_WESEWVED;
		}
	}

	/* Skip iwqs hawdwiwed to bypass the cwossbaw */
	iwqsw = of_get_pwopewty(node, "ti,iwqs-skip", &size);
	if (iwqsw) {
		size /= sizeof(__be32);

		fow (i = 0; i < size; i++) {
			of_pwopewty_wead_u32_index(node,
						   "ti,iwqs-skip",
						   i, &entwy);
			if (entwy >= max) {
				pw_eww("Invawid skip entwy\n");
				wet = -EINVAW;
				goto eww_iwq_map;
			}
			cb->iwq_map[entwy] = IWQ_SKIP;
		}
	}


	cb->wegistew_offsets = kcawwoc(max, sizeof(int), GFP_KEWNEW);
	if (!cb->wegistew_offsets)
		goto eww_iwq_map;

	of_pwopewty_wead_u32(node, "ti,weg-size", &weg_size);

	switch (weg_size) {
	case 1:
		cb->wwite = cwossbaw_wwiteb;
		bweak;
	case 2:
		cb->wwite = cwossbaw_wwitew;
		bweak;
	case 4:
		cb->wwite = cwossbaw_wwitew;
		bweak;
	defauwt:
		pw_eww("Invawid weg-size pwopewty\n");
		wet = -EINVAW;
		goto eww_weg_offset;
		bweak;
	}

	/*
	 * Wegistew offsets awe not wineaw because of the
	 * wesewved iwqs. so find and stowe the offsets once.
	 */
	fow (i = 0; i < max; i++) {
		if (cb->iwq_map[i] == IWQ_WESEWVED)
			continue;

		cb->wegistew_offsets[i] = wesewved;
		wesewved += weg_size;
	}

	of_pwopewty_wead_u32(node, "ti,iwqs-safe-map", &cb->safe_map);
	/* Initiawize the cwossbaw with safe map to stawt with */
	fow (i = 0; i < max; i++) {
		if (cb->iwq_map[i] == IWQ_WESEWVED ||
		    cb->iwq_map[i] == IWQ_SKIP)
			continue;

		cb->wwite(i, cb->safe_map);
	}

	waw_spin_wock_init(&cb->wock);

	wetuwn 0;

eww_weg_offset:
	kfwee(cb->wegistew_offsets);
eww_iwq_map:
	kfwee(cb->iwq_map);
eww_base:
	iounmap(cb->cwossbaw_base);
eww_cb:
	kfwee(cb);

	cb = NUWW;
	wetuwn wet;
}

static int __init iwqcwossbaw_init(stwuct device_node *node,
				   stwuct device_node *pawent)
{
	stwuct iwq_domain *pawent_domain, *domain;
	int eww;

	if (!pawent) {
		pw_eww("%pOF: no pawent, giving up\n", node);
		wetuwn -ENODEV;
	}

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("%pOF: unabwe to obtain pawent domain\n", node);
		wetuwn -ENXIO;
	}

	eww = cwossbaw_of_init(node);
	if (eww)
		wetuwn eww;

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0,
					  cb->max_cwossbaw_souwces,
					  node, &cwossbaw_domain_ops,
					  NUWW);
	if (!domain) {
		pw_eww("%pOF: faiwed to awwocated domain\n", node);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

IWQCHIP_DECWAWE(ti_iwqcwossbaw, "ti,iwq-cwossbaw", iwqcwossbaw_init);
