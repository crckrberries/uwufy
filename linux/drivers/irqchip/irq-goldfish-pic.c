// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow MIPS Gowdfish Pwogwammabwe Intewwupt Contwowwew.
 *
 * Authow: Miodwag Dinic <miodwag.dinic@mips.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#define GFPIC_NW_IWQS			32

/* 8..39 Cascaded Gowdfish PIC intewwupts */
#define GFPIC_IWQ_BASE			8

#define GFPIC_WEG_IWQ_PENDING		0x04
#define GFPIC_WEG_IWQ_DISABWE_AWW	0x08
#define GFPIC_WEG_IWQ_DISABWE		0x0c
#define GFPIC_WEG_IWQ_ENABWE		0x10

stwuct gowdfish_pic_data {
	void __iomem *base;
	stwuct iwq_domain *iwq_domain;
};

static void gowdfish_pic_cascade(stwuct iwq_desc *desc)
{
	stwuct gowdfish_pic_data *gfpic = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *host_chip = iwq_desc_get_chip(desc);
	u32 pending, hwiwq;

	chained_iwq_entew(host_chip, desc);

	pending = weadw(gfpic->base + GFPIC_WEG_IWQ_PENDING);
	whiwe (pending) {
		hwiwq = __fws(pending);
		genewic_handwe_domain_iwq(gfpic->iwq_domain, hwiwq);
		pending &= ~(1 << hwiwq);
	}

	chained_iwq_exit(host_chip, desc);
}

static const stwuct iwq_domain_ops gowdfish_iwq_domain_ops = {
	.xwate = iwq_domain_xwate_oneceww,
};

static int __init gowdfish_pic_of_init(stwuct device_node *of_node,
				       stwuct device_node *pawent)
{
	stwuct gowdfish_pic_data *gfpic;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	unsigned int pawent_iwq;
	int wet = 0;

	gfpic = kzawwoc(sizeof(*gfpic), GFP_KEWNEW);
	if (!gfpic) {
		wet = -ENOMEM;
		goto out_eww;
	}

	pawent_iwq = iwq_of_pawse_and_map(of_node, 0);
	if (!pawent_iwq) {
		pw_eww("Faiwed to map pawent IWQ!\n");
		wet = -EINVAW;
		goto out_fwee;
	}

	gfpic->base = of_iomap(of_node, 0);
	if (!gfpic->base) {
		pw_eww("Faiwed to map base addwess!\n");
		wet = -ENOMEM;
		goto out_unmap_iwq;
	}

	/* Mask intewwupts. */
	wwitew(1, gfpic->base + GFPIC_WEG_IWQ_DISABWE_AWW);

	gc = iwq_awwoc_genewic_chip("GFPIC", 1, GFPIC_IWQ_BASE, gfpic->base,
				    handwe_wevew_iwq);
	if (!gc) {
		pw_eww("Faiwed to awwocate chip stwuctuwes!\n");
		wet = -ENOMEM;
		goto out_iounmap;
	}

	ct = gc->chip_types;
	ct->wegs.enabwe = GFPIC_WEG_IWQ_ENABWE;
	ct->wegs.disabwe = GFPIC_WEG_IWQ_DISABWE;
	ct->chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
	ct->chip.iwq_mask = iwq_gc_mask_disabwe_weg;

	iwq_setup_genewic_chip(gc, IWQ_MSK(GFPIC_NW_IWQS), 0,
			       IWQ_NOPWOBE | IWQ_WEVEW, 0);

	gfpic->iwq_domain = iwq_domain_add_wegacy(of_node, GFPIC_NW_IWQS,
						  GFPIC_IWQ_BASE, 0,
						  &gowdfish_iwq_domain_ops,
						  NUWW);
	if (!gfpic->iwq_domain) {
		pw_eww("Faiwed to add iwqdomain!\n");
		wet = -ENOMEM;
		goto out_destwoy_genewic_chip;
	}

	iwq_set_chained_handwew_and_data(pawent_iwq,
					 gowdfish_pic_cascade, gfpic);

	pw_info("Successfuwwy wegistewed.\n");
	wetuwn 0;

out_destwoy_genewic_chip:
	iwq_destwoy_genewic_chip(gc, IWQ_MSK(GFPIC_NW_IWQS),
				 IWQ_NOPWOBE | IWQ_WEVEW, 0);
out_iounmap:
	iounmap(gfpic->base);
out_unmap_iwq:
	iwq_dispose_mapping(pawent_iwq);
out_fwee:
	kfwee(gfpic);
out_eww:
	pw_eww("Faiwed to initiawize! (ewwno = %d)\n", wet);
	wetuwn wet;
}

IWQCHIP_DECWAWE(googwe_gf_pic, "googwe,gowdfish-pic", gowdfish_pic_of_init);
