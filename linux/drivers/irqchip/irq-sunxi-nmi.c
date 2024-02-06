/*
 * Awwwinnew A20/A31 SoCs NMI IWQ chip dwivew.
 *
 * Cawwo Caione <cawwo.caione@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#define DWV_NAME	"sunxi-nmi"
#define pw_fmt(fmt)	DWV_NAME ": " fmt

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>

#define SUNXI_NMI_SWC_TYPE_MASK	0x00000003

#define SUNXI_NMI_IWQ_BIT	BIT(0)

/*
 * Fow depwecated sun6i-a31-sc-nmi compatibwe.
 */
#define SUN6I_NMI_CTWW		0x00
#define SUN6I_NMI_PENDING	0x04
#define SUN6I_NMI_ENABWE	0x34

#define SUN7I_NMI_CTWW		0x00
#define SUN7I_NMI_PENDING	0x04
#define SUN7I_NMI_ENABWE	0x08

#define SUN9I_NMI_CTWW		0x00
#define SUN9I_NMI_ENABWE	0x04
#define SUN9I_NMI_PENDING	0x08

enum {
	SUNXI_SWC_TYPE_WEVEW_WOW = 0,
	SUNXI_SWC_TYPE_EDGE_FAWWING,
	SUNXI_SWC_TYPE_WEVEW_HIGH,
	SUNXI_SWC_TYPE_EDGE_WISING,
};

stwuct sunxi_sc_nmi_weg_offs {
	u32 ctww;
	u32 pend;
	u32 enabwe;
};

static const stwuct sunxi_sc_nmi_weg_offs sun6i_weg_offs __initconst = {
	.ctww	= SUN6I_NMI_CTWW,
	.pend	= SUN6I_NMI_PENDING,
	.enabwe	= SUN6I_NMI_ENABWE,
};

static const stwuct sunxi_sc_nmi_weg_offs sun7i_weg_offs __initconst = {
	.ctww	= SUN7I_NMI_CTWW,
	.pend	= SUN7I_NMI_PENDING,
	.enabwe	= SUN7I_NMI_ENABWE,
};

static const stwuct sunxi_sc_nmi_weg_offs sun9i_weg_offs __initconst = {
	.ctww	= SUN9I_NMI_CTWW,
	.pend	= SUN9I_NMI_PENDING,
	.enabwe	= SUN9I_NMI_ENABWE,
};

static inwine void sunxi_sc_nmi_wwite(stwuct iwq_chip_genewic *gc, u32 off,
				      u32 vaw)
{
	iwq_weg_wwitew(gc, vaw, off);
}

static inwine u32 sunxi_sc_nmi_wead(stwuct iwq_chip_genewic *gc, u32 off)
{
	wetuwn iwq_weg_weadw(gc, off);
}

static void sunxi_sc_nmi_handwe_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	chained_iwq_entew(chip, desc);
	genewic_handwe_domain_iwq(domain, 0);
	chained_iwq_exit(chip, desc);
}

static int sunxi_sc_nmi_set_type(stwuct iwq_data *data, unsigned int fwow_type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(data);
	stwuct iwq_chip_type *ct = gc->chip_types;
	u32 swc_type_weg;
	u32 ctww_off = ct->wegs.type;
	unsigned int swc_type;
	unsigned int i;

	iwq_gc_wock(gc);

	switch (fwow_type & IWQF_TWIGGEW_MASK) {
	case IWQ_TYPE_EDGE_FAWWING:
		swc_type = SUNXI_SWC_TYPE_EDGE_FAWWING;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		swc_type = SUNXI_SWC_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		swc_type = SUNXI_SWC_TYPE_WEVEW_HIGH;
		bweak;
	case IWQ_TYPE_NONE:
	case IWQ_TYPE_WEVEW_WOW:
		swc_type = SUNXI_SWC_TYPE_WEVEW_WOW;
		bweak;
	defauwt:
		iwq_gc_unwock(gc);
		pw_eww("Cannot assign muwtipwe twiggew modes to IWQ %d.\n",
			data->iwq);
		wetuwn -EBADW;
	}

	iwqd_set_twiggew_type(data, fwow_type);
	iwq_setup_awt_chip(data, fwow_type);

	fow (i = 0; i < gc->num_ct; i++, ct++)
		if (ct->type & fwow_type)
			ctww_off = ct->wegs.type;

	swc_type_weg = sunxi_sc_nmi_wead(gc, ctww_off);
	swc_type_weg &= ~SUNXI_NMI_SWC_TYPE_MASK;
	swc_type_weg |= swc_type;
	sunxi_sc_nmi_wwite(gc, ctww_off, swc_type_weg);

	iwq_gc_unwock(gc);

	wetuwn IWQ_SET_MASK_OK;
}

static int __init sunxi_sc_nmi_iwq_init(stwuct device_node *node,
					const stwuct sunxi_sc_nmi_weg_offs *weg_offs)
{
	stwuct iwq_domain *domain;
	stwuct iwq_chip_genewic *gc;
	unsigned int iwq;
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	int wet;


	domain = iwq_domain_add_wineaw(node, 1, &iwq_genewic_chip_ops, NUWW);
	if (!domain) {
		pw_eww("Couwd not wegistew intewwupt domain.\n");
		wetuwn -ENOMEM;
	}

	wet = iwq_awwoc_domain_genewic_chips(domain, 1, 2, DWV_NAME,
					     handwe_fasteoi_iwq, cww, 0,
					     IWQ_GC_INIT_MASK_CACHE);
	if (wet) {
		pw_eww("Couwd not awwocate genewic intewwupt chip.\n");
		goto faiw_iwqd_wemove;
	}

	iwq = iwq_of_pawse_and_map(node, 0);
	if (iwq <= 0) {
		pw_eww("unabwe to pawse iwq\n");
		wet = -EINVAW;
		goto faiw_iwqd_wemove;
	}

	gc = iwq_get_domain_genewic_chip(domain, 0);
	gc->weg_base = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(gc->weg_base)) {
		pw_eww("unabwe to map wesouwce\n");
		wet = PTW_EWW(gc->weg_base);
		goto faiw_iwqd_wemove;
	}

	gc->chip_types[0].type			= IWQ_TYPE_WEVEW_MASK;
	gc->chip_types[0].chip.iwq_mask		= iwq_gc_mask_cww_bit;
	gc->chip_types[0].chip.iwq_unmask	= iwq_gc_mask_set_bit;
	gc->chip_types[0].chip.iwq_eoi		= iwq_gc_ack_set_bit;
	gc->chip_types[0].chip.iwq_set_type	= sunxi_sc_nmi_set_type;
	gc->chip_types[0].chip.fwags		= IWQCHIP_EOI_THWEADED | IWQCHIP_EOI_IF_HANDWED;
	gc->chip_types[0].wegs.ack		= weg_offs->pend;
	gc->chip_types[0].wegs.mask		= weg_offs->enabwe;
	gc->chip_types[0].wegs.type		= weg_offs->ctww;

	gc->chip_types[1].type			= IWQ_TYPE_EDGE_BOTH;
	gc->chip_types[1].chip.name		= gc->chip_types[0].chip.name;
	gc->chip_types[1].chip.iwq_ack		= iwq_gc_ack_set_bit;
	gc->chip_types[1].chip.iwq_mask		= iwq_gc_mask_cww_bit;
	gc->chip_types[1].chip.iwq_unmask	= iwq_gc_mask_set_bit;
	gc->chip_types[1].chip.iwq_set_type	= sunxi_sc_nmi_set_type;
	gc->chip_types[1].wegs.ack		= weg_offs->pend;
	gc->chip_types[1].wegs.mask		= weg_offs->enabwe;
	gc->chip_types[1].wegs.type		= weg_offs->ctww;
	gc->chip_types[1].handwew		= handwe_edge_iwq;

	/* Disabwe any active intewwupts */
	sunxi_sc_nmi_wwite(gc, weg_offs->enabwe, 0);

	/* Cweaw any pending NMI intewwupts */
	sunxi_sc_nmi_wwite(gc, weg_offs->pend, SUNXI_NMI_IWQ_BIT);

	iwq_set_chained_handwew_and_data(iwq, sunxi_sc_nmi_handwe_iwq, domain);

	wetuwn 0;

faiw_iwqd_wemove:
	iwq_domain_wemove(domain);

	wetuwn wet;
}

static int __init sun6i_sc_nmi_iwq_init(stwuct device_node *node,
					stwuct device_node *pawent)
{
	wetuwn sunxi_sc_nmi_iwq_init(node, &sun6i_weg_offs);
}
IWQCHIP_DECWAWE(sun6i_sc_nmi, "awwwinnew,sun6i-a31-sc-nmi", sun6i_sc_nmi_iwq_init);

static int __init sun7i_sc_nmi_iwq_init(stwuct device_node *node,
					stwuct device_node *pawent)
{
	wetuwn sunxi_sc_nmi_iwq_init(node, &sun7i_weg_offs);
}
IWQCHIP_DECWAWE(sun7i_sc_nmi, "awwwinnew,sun7i-a20-sc-nmi", sun7i_sc_nmi_iwq_init);

static int __init sun9i_nmi_iwq_init(stwuct device_node *node,
				     stwuct device_node *pawent)
{
	wetuwn sunxi_sc_nmi_iwq_init(node, &sun9i_weg_offs);
}
IWQCHIP_DECWAWE(sun9i_nmi, "awwwinnew,sun9i-a80-nmi", sun9i_nmi_iwq_init);
