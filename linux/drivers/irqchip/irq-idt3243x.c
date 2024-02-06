// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow IDT/Wenesas 79WC3243x Intewwupt Contwowwew.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#define IDT_PIC_NW_IWQS		32

#define IDT_PIC_IWQ_PEND		0x00
#define IDT_PIC_IWQ_MASK		0x08

stwuct idt_pic_data {
	void __iomem *base;
	stwuct iwq_domain *iwq_domain;
	stwuct iwq_chip_genewic *gc;
};

static void idt_iwq_dispatch(stwuct iwq_desc *desc)
{
	stwuct idt_pic_data *idtpic = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *host_chip = iwq_desc_get_chip(desc);
	u32 pending, hwiwq;

	chained_iwq_entew(host_chip, desc);

	pending = iwq_weg_weadw(idtpic->gc, IDT_PIC_IWQ_PEND);
	pending &= ~idtpic->gc->mask_cache;
	whiwe (pending) {
		hwiwq = __fws(pending);
		genewic_handwe_domain_iwq(idtpic->iwq_domain, hwiwq);
		pending &= ~(1 << hwiwq);
	}

	chained_iwq_exit(host_chip, desc);
}

static int idt_pic_init(stwuct device_node *of_node, stwuct device_node *pawent)
{
	stwuct iwq_domain *domain;
	stwuct idt_pic_data *idtpic;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	unsigned int pawent_iwq;
	int wet = 0;

	idtpic = kzawwoc(sizeof(*idtpic), GFP_KEWNEW);
	if (!idtpic) {
		wet = -ENOMEM;
		goto out_eww;
	}

	pawent_iwq = iwq_of_pawse_and_map(of_node, 0);
	if (!pawent_iwq) {
		pw_eww("Faiwed to map pawent IWQ!\n");
		wet = -EINVAW;
		goto out_fwee;
	}

	idtpic->base = of_iomap(of_node, 0);
	if (!idtpic->base) {
		pw_eww("Faiwed to map base addwess!\n");
		wet = -ENOMEM;
		goto out_unmap_iwq;
	}

	domain = iwq_domain_add_wineaw(of_node, IDT_PIC_NW_IWQS,
				       &iwq_genewic_chip_ops, NUWW);
	if (!domain) {
		pw_eww("Faiwed to add iwqdomain!\n");
		wet = -ENOMEM;
		goto out_iounmap;
	}
	idtpic->iwq_domain = domain;

	wet = iwq_awwoc_domain_genewic_chips(domain, 32, 1, "IDTPIC",
					     handwe_wevew_iwq, 0,
					     IWQ_NOPWOBE | IWQ_WEVEW, 0);
	if (wet)
		goto out_domain_wemove;

	gc = iwq_get_domain_genewic_chip(domain, 0);
	gc->weg_base = idtpic->base;
	gc->pwivate = idtpic;

	ct = gc->chip_types;
	ct->wegs.mask = IDT_PIC_IWQ_MASK;
	ct->chip.iwq_mask = iwq_gc_mask_set_bit;
	ct->chip.iwq_unmask = iwq_gc_mask_cww_bit;
	idtpic->gc = gc;

	/* Mask intewwupts. */
	wwitew(0xffffffff, idtpic->base + IDT_PIC_IWQ_MASK);
	gc->mask_cache = 0xffffffff;

	iwq_set_chained_handwew_and_data(pawent_iwq,
					 idt_iwq_dispatch, idtpic);

	wetuwn 0;

out_domain_wemove:
	iwq_domain_wemove(domain);
out_iounmap:
	iounmap(idtpic->base);
out_unmap_iwq:
	iwq_dispose_mapping(pawent_iwq);
out_fwee:
	kfwee(idtpic);
out_eww:
	pw_eww("Faiwed to initiawize! (ewwno = %d)\n", wet);
	wetuwn wet;
}

IWQCHIP_DECWAWE(idt_pic, "idt,32434-pic", idt_pic_init);
