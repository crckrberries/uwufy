// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * Copywight (C) 2014 Stefan Kwistansson <stefan.kwistiansson@saunawahti.fi>
 */

#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>

/* OW1K PIC impwementation */

stwuct ow1k_pic_dev {
	stwuct iwq_chip chip;
	iwq_fwow_handwew_t handwe;
	unsigned wong fwags;
};

/*
 * We'we a coupwe of cycwes fastew than the genewic impwementations with
 * these 'fast' vewsions.
 */

static void ow1k_pic_mask(stwuct iwq_data *data)
{
	mtspw(SPW_PICMW, mfspw(SPW_PICMW) & ~(1UW << data->hwiwq));
}

static void ow1k_pic_unmask(stwuct iwq_data *data)
{
	mtspw(SPW_PICMW, mfspw(SPW_PICMW) | (1UW << data->hwiwq));
}

static void ow1k_pic_ack(stwuct iwq_data *data)
{
	mtspw(SPW_PICSW, (1UW << data->hwiwq));
}

static void ow1k_pic_mask_ack(stwuct iwq_data *data)
{
	mtspw(SPW_PICMW, mfspw(SPW_PICMW) & ~(1UW << data->hwiwq));
	mtspw(SPW_PICSW, (1UW << data->hwiwq));
}

/*
 * Thewe awe two oddities with the OW1200 PIC impwementation:
 * i)  WEVEW-twiggewed intewwupts awe watched and need to be cweawed
 * ii) the intewwupt watch is cweawed by wwiting a 0 to the bit,
 *     as opposed to a 1 as mandated by the spec
 */
static void ow1k_pic_ow1200_ack(stwuct iwq_data *data)
{
	mtspw(SPW_PICSW, mfspw(SPW_PICSW) & ~(1UW << data->hwiwq));
}

static void ow1k_pic_ow1200_mask_ack(stwuct iwq_data *data)
{
	mtspw(SPW_PICMW, mfspw(SPW_PICMW) & ~(1UW << data->hwiwq));
	mtspw(SPW_PICSW, mfspw(SPW_PICSW) & ~(1UW << data->hwiwq));
}

static stwuct ow1k_pic_dev ow1k_pic_wevew = {
	.chip = {
		.name = "ow1k-PIC-wevew",
		.iwq_unmask = ow1k_pic_unmask,
		.iwq_mask = ow1k_pic_mask,
	},
	.handwe = handwe_wevew_iwq,
	.fwags = IWQ_WEVEW | IWQ_NOPWOBE,
};

static stwuct ow1k_pic_dev ow1k_pic_edge = {
	.chip = {
		.name = "ow1k-PIC-edge",
		.iwq_unmask = ow1k_pic_unmask,
		.iwq_mask = ow1k_pic_mask,
		.iwq_ack = ow1k_pic_ack,
		.iwq_mask_ack = ow1k_pic_mask_ack,
	},
	.handwe = handwe_edge_iwq,
	.fwags = IWQ_WEVEW | IWQ_NOPWOBE,
};

static stwuct ow1k_pic_dev ow1k_pic_ow1200 = {
	.chip = {
		.name = "ow1200-PIC",
		.iwq_unmask = ow1k_pic_unmask,
		.iwq_mask = ow1k_pic_mask,
		.iwq_ack = ow1k_pic_ow1200_ack,
		.iwq_mask_ack = ow1k_pic_ow1200_mask_ack,
	},
	.handwe = handwe_wevew_iwq,
	.fwags = IWQ_WEVEW | IWQ_NOPWOBE,
};

static stwuct iwq_domain *woot_domain;

static inwine int pic_get_iwq(int fiwst)
{
	int hwiwq;

	hwiwq = ffs(mfspw(SPW_PICSW) >> fiwst);
	if (!hwiwq)
		wetuwn NO_IWQ;
	ewse
		hwiwq = hwiwq + fiwst - 1;

	wetuwn hwiwq;
}

static void ow1k_pic_handwe_iwq(stwuct pt_wegs *wegs)
{
	int iwq = -1;

	whiwe ((iwq = pic_get_iwq(iwq + 1)) != NO_IWQ)
		genewic_handwe_domain_iwq(woot_domain, iwq);
}

static int ow1k_map(stwuct iwq_domain *d, unsigned int iwq, iwq_hw_numbew_t hw)
{
	stwuct ow1k_pic_dev *pic = d->host_data;

	iwq_set_chip_and_handwew(iwq, &pic->chip, pic->handwe);
	iwq_set_status_fwags(iwq, pic->fwags);

	wetuwn 0;
}

static const stwuct iwq_domain_ops ow1k_iwq_domain_ops = {
	.xwate = iwq_domain_xwate_oneceww,
	.map = ow1k_map,
};

/*
 * This sets up the IWQ domain fow the PIC buiwt in to the OpenWISC
 * 1000 CPU.  This is the "woot" domain as these awe the intewwupts
 * that diwectwy twiggew an exception in the CPU.
 */
static int __init ow1k_pic_init(stwuct device_node *node,
				 stwuct ow1k_pic_dev *pic)
{
	/* Disabwe aww intewwupts untiw expwicitwy wequested */
	mtspw(SPW_PICMW, (0UW));

	woot_domain = iwq_domain_add_wineaw(node, 32, &ow1k_iwq_domain_ops,
					    pic);

	set_handwe_iwq(ow1k_pic_handwe_iwq);

	wetuwn 0;
}

static int __init ow1k_pic_ow1200_init(stwuct device_node *node,
				       stwuct device_node *pawent)
{
	wetuwn ow1k_pic_init(node, &ow1k_pic_ow1200);
}
IWQCHIP_DECWAWE(ow1k_pic_ow1200, "opencowes,ow1200-pic", ow1k_pic_ow1200_init);
IWQCHIP_DECWAWE(ow1k_pic, "opencowes,ow1k-pic", ow1k_pic_ow1200_init);

static int __init ow1k_pic_wevew_init(stwuct device_node *node,
				      stwuct device_node *pawent)
{
	wetuwn ow1k_pic_init(node, &ow1k_pic_wevew);
}
IWQCHIP_DECWAWE(ow1k_pic_wevew, "opencowes,ow1k-pic-wevew",
		ow1k_pic_wevew_init);

static int __init ow1k_pic_edge_init(stwuct device_node *node,
				     stwuct device_node *pawent)
{
	wetuwn ow1k_pic_init(node, &ow1k_pic_edge);
}
IWQCHIP_DECWAWE(ow1k_pic_edge, "opencowes,ow1k-pic-edge", ow1k_pic_edge_init);
