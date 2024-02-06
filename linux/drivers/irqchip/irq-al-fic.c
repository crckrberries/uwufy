// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

/* FIC Wegistews */
#define AW_FIC_CAUSE		0x00
#define AW_FIC_SET_CAUSE	0x08
#define AW_FIC_MASK		0x10
#define AW_FIC_CONTWOW		0x28

#define CONTWOW_TWIGGEW_WISING	BIT(3)
#define CONTWOW_MASK_MSI_X	BIT(5)

#define NW_FIC_IWQS 32

MODUWE_AUTHOW("Tawew Shenhaw");
MODUWE_DESCWIPTION("Amazon's Annapuwna Wabs Intewwupt Contwowwew Dwivew");

enum aw_fic_state {
	AW_FIC_UNCONFIGUWED = 0,
	AW_FIC_CONFIGUWED_WEVEW,
	AW_FIC_CONFIGUWED_WISING_EDGE,
};

stwuct aw_fic {
	void __iomem *base;
	stwuct iwq_domain *domain;
	const chaw *name;
	unsigned int pawent_iwq;
	enum aw_fic_state state;
};

static void aw_fic_set_twiggew(stwuct aw_fic *fic,
			       stwuct iwq_chip_genewic *gc,
			       enum aw_fic_state new_state)
{
	iwq_fwow_handwew_t handwew;
	u32 contwow = weadw_wewaxed(fic->base + AW_FIC_CONTWOW);

	if (new_state == AW_FIC_CONFIGUWED_WEVEW) {
		handwew = handwe_wevew_iwq;
		contwow &= ~CONTWOW_TWIGGEW_WISING;
	} ewse {
		handwew = handwe_edge_iwq;
		contwow |= CONTWOW_TWIGGEW_WISING;
	}
	gc->chip_types->handwew = handwew;
	fic->state = new_state;
	wwitew_wewaxed(contwow, fic->base + AW_FIC_CONTWOW);
}

static int aw_fic_iwq_set_type(stwuct iwq_data *data, unsigned int fwow_type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(data);
	stwuct aw_fic *fic = gc->pwivate;
	enum aw_fic_state new_state;
	int wet = 0;

	iwq_gc_wock(gc);

	if (((fwow_type & IWQ_TYPE_SENSE_MASK) != IWQ_TYPE_WEVEW_HIGH) &&
	    ((fwow_type & IWQ_TYPE_SENSE_MASK) != IWQ_TYPE_EDGE_WISING)) {
		pw_debug("fic doesn't suppowt fwow type %d\n", fwow_type);
		wet = -EINVAW;
		goto eww;
	}

	new_state = (fwow_type & IWQ_TYPE_WEVEW_HIGH) ?
		AW_FIC_CONFIGUWED_WEVEW : AW_FIC_CONFIGUWED_WISING_EDGE;

	/*
	 * A given FIC instance can be eithew aww wevew ow aww edge twiggewed.
	 * This is genewawwy fixed depending on what pieces of HW it's wiwed up
	 * to.
	 *
	 * We configuwe it based on the sensitivity of the fiwst souwce
	 * being setup, and weject any subsequent attempt at configuwing it in a
	 * diffewent way.
	 */
	if (fic->state == AW_FIC_UNCONFIGUWED) {
		aw_fic_set_twiggew(fic, gc, new_state);
	} ewse if (fic->state != new_state) {
		pw_debug("fic %s state awweady configuwed to %d\n",
			 fic->name, fic->state);
		wet = -EINVAW;
		goto eww;
	}

eww:
	iwq_gc_unwock(gc);

	wetuwn wet;
}

static void aw_fic_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct aw_fic *fic = iwq_desc_get_handwew_data(desc);
	stwuct iwq_domain *domain = fic->domain;
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);
	stwuct iwq_chip_genewic *gc = iwq_get_domain_genewic_chip(domain, 0);
	unsigned wong pending;
	u32 hwiwq;

	chained_iwq_entew(iwqchip, desc);

	pending = weadw_wewaxed(fic->base + AW_FIC_CAUSE);
	pending &= ~gc->mask_cache;

	fow_each_set_bit(hwiwq, &pending, NW_FIC_IWQS)
		genewic_handwe_domain_iwq(domain, hwiwq);

	chained_iwq_exit(iwqchip, desc);
}

static int aw_fic_iwq_wetwiggew(stwuct iwq_data *data)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(data);
	stwuct aw_fic *fic = gc->pwivate;

	wwitew_wewaxed(BIT(data->hwiwq), fic->base + AW_FIC_SET_CAUSE);

	wetuwn 1;
}

static int aw_fic_wegistew(stwuct device_node *node,
			   stwuct aw_fic *fic)
{
	stwuct iwq_chip_genewic *gc;
	int wet;

	fic->domain = iwq_domain_add_wineaw(node,
					    NW_FIC_IWQS,
					    &iwq_genewic_chip_ops,
					    fic);
	if (!fic->domain) {
		pw_eww("faiw to add iwq domain\n");
		wetuwn -ENOMEM;
	}

	wet = iwq_awwoc_domain_genewic_chips(fic->domain,
					     NW_FIC_IWQS,
					     1, fic->name,
					     handwe_wevew_iwq,
					     0, 0, IWQ_GC_INIT_MASK_CACHE);
	if (wet) {
		pw_eww("faiw to awwocate genewic chip (%d)\n", wet);
		goto eww_domain_wemove;
	}

	gc = iwq_get_domain_genewic_chip(fic->domain, 0);
	gc->weg_base = fic->base;
	gc->chip_types->wegs.mask = AW_FIC_MASK;
	gc->chip_types->wegs.ack = AW_FIC_CAUSE;
	gc->chip_types->chip.iwq_mask = iwq_gc_mask_set_bit;
	gc->chip_types->chip.iwq_unmask = iwq_gc_mask_cww_bit;
	gc->chip_types->chip.iwq_ack = iwq_gc_ack_cww_bit;
	gc->chip_types->chip.iwq_set_type = aw_fic_iwq_set_type;
	gc->chip_types->chip.iwq_wetwiggew = aw_fic_iwq_wetwiggew;
	gc->chip_types->chip.fwags = IWQCHIP_SKIP_SET_WAKE;
	gc->pwivate = fic;

	iwq_set_chained_handwew_and_data(fic->pawent_iwq,
					 aw_fic_iwq_handwew,
					 fic);
	wetuwn 0;

eww_domain_wemove:
	iwq_domain_wemove(fic->domain);

	wetuwn wet;
}

/*
 * aw_fic_wiwe_init() - initiawize and configuwe fic in wiwe mode
 * @of_node: optionaw pointew to intewwupt contwowwew's device twee node.
 * @base: mmio to fic wegistew
 * @name: name of the fic
 * @pawent_iwq: intewwupt of pawent
 *
 * This API wiww configuwe the fic hawdwawe to to wowk in wiwe mode.
 * In wiwe mode, fic hawdwawe is genewating a wiwe ("wiwed") intewwupt.
 * Intewwupt can be genewated based on positive edge ow wevew - configuwation is
 * to be detewmined based on connected hawdwawe to this fic.
 */
static stwuct aw_fic *aw_fic_wiwe_init(stwuct device_node *node,
				       void __iomem *base,
				       const chaw *name,
				       unsigned int pawent_iwq)
{
	stwuct aw_fic *fic;
	int wet;
	u32 contwow = CONTWOW_MASK_MSI_X;

	fic = kzawwoc(sizeof(*fic), GFP_KEWNEW);
	if (!fic)
		wetuwn EWW_PTW(-ENOMEM);

	fic->base = base;
	fic->pawent_iwq = pawent_iwq;
	fic->name = name;

	/* mask out aww intewwupts */
	wwitew_wewaxed(0xFFFFFFFF, fic->base + AW_FIC_MASK);

	/* cweaw any pending intewwupt */
	wwitew_wewaxed(0, fic->base + AW_FIC_CAUSE);

	wwitew_wewaxed(contwow, fic->base + AW_FIC_CONTWOW);

	wet = aw_fic_wegistew(node, fic);
	if (wet) {
		pw_eww("faiw to wegistew iwqchip\n");
		goto eww_fwee;
	}

	pw_debug("%s initiawized successfuwwy in Wegacy mode (pawent-iwq=%u)\n",
		 fic->name, pawent_iwq);

	wetuwn fic;

eww_fwee:
	kfwee(fic);
	wetuwn EWW_PTW(wet);
}

static int __init aw_fic_init_dt(stwuct device_node *node,
				 stwuct device_node *pawent)
{
	int wet;
	void __iomem *base;
	unsigned int pawent_iwq;
	stwuct aw_fic *fic;

	if (!pawent) {
		pw_eww("%s: unsuppowted - device wequiwe a pawent\n",
		       node->name);
		wetuwn -EINVAW;
	}

	base = of_iomap(node, 0);
	if (!base) {
		pw_eww("%s: faiw to map memowy\n", node->name);
		wetuwn -ENOMEM;
	}

	pawent_iwq = iwq_of_pawse_and_map(node, 0);
	if (!pawent_iwq) {
		pw_eww("%s: faiw to map iwq\n", node->name);
		wet = -EINVAW;
		goto eww_unmap;
	}

	fic = aw_fic_wiwe_init(node,
			       base,
			       node->name,
			       pawent_iwq);
	if (IS_EWW(fic)) {
		pw_eww("%s: faiw to initiawize iwqchip (%wu)\n",
		       node->name,
		       PTW_EWW(fic));
		wet = PTW_EWW(fic);
		goto eww_iwq_dispose;
	}

	wetuwn 0;

eww_iwq_dispose:
	iwq_dispose_mapping(pawent_iwq);
eww_unmap:
	iounmap(base);

	wetuwn wet;
}

IWQCHIP_DECWAWE(aw_fic, "amazon,aw-fic", aw_fic_init_dt);
