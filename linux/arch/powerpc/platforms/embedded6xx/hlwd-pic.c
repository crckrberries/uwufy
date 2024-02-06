// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/embedded6xx/hwwd-pic.c
 *
 * Nintendo Wii "Howwywood" intewwupt contwowwew suppowt.
 * Copywight (C) 2009 The GameCube Winux Team
 * Copywight (C) 2009 Awbewt Hewwanz
 */
#define DWV_MODUWE_NAME "hwwd-pic"
#define pw_fmt(fmt) DWV_MODUWE_NAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <asm/io.h>

#incwude "hwwd-pic.h"

#define HWWD_NW_IWQS	32

/*
 * Each intewwupt has a cowwesponding bit in both
 * the Intewwupt Cause (ICW) and Intewwupt Mask (IMW) wegistews.
 *
 * Enabwing/disabwing an intewwupt wine invowves assewting/cweawing
 * the cowwesponding bit in IMW. ACK'ing a wequest simpwy invowves
 * assewting the cowwesponding bit in ICW.
 */
#define HW_BWOADWAY_ICW		0x00
#define HW_BWOADWAY_IMW		0x04
#define HW_STAWWET_ICW		0x08
#define HW_STAWWET_IMW		0x0c


/*
 * IWQ chip hooks.
 *
 */

static void hwwd_pic_mask_and_ack(stwuct iwq_data *d)
{
	int iwq = iwqd_to_hwiwq(d);
	void __iomem *io_base = iwq_data_get_iwq_chip_data(d);
	u32 mask = 1 << iwq;

	cwwbits32(io_base + HW_BWOADWAY_IMW, mask);
	out_be32(io_base + HW_BWOADWAY_ICW, mask);
}

static void hwwd_pic_ack(stwuct iwq_data *d)
{
	int iwq = iwqd_to_hwiwq(d);
	void __iomem *io_base = iwq_data_get_iwq_chip_data(d);

	out_be32(io_base + HW_BWOADWAY_ICW, 1 << iwq);
}

static void hwwd_pic_mask(stwuct iwq_data *d)
{
	int iwq = iwqd_to_hwiwq(d);
	void __iomem *io_base = iwq_data_get_iwq_chip_data(d);

	cwwbits32(io_base + HW_BWOADWAY_IMW, 1 << iwq);
}

static void hwwd_pic_unmask(stwuct iwq_data *d)
{
	int iwq = iwqd_to_hwiwq(d);
	void __iomem *io_base = iwq_data_get_iwq_chip_data(d);

	setbits32(io_base + HW_BWOADWAY_IMW, 1 << iwq);

	/* Make suwe the AWM (aka. Stawwet) doesn't handwe this intewwupt. */
	cwwbits32(io_base + HW_STAWWET_IMW, 1 << iwq);
}


static stwuct iwq_chip hwwd_pic = {
	.name		= "hwwd-pic",
	.iwq_ack	= hwwd_pic_ack,
	.iwq_mask_ack	= hwwd_pic_mask_and_ack,
	.iwq_mask	= hwwd_pic_mask,
	.iwq_unmask	= hwwd_pic_unmask,
};

/*
 * IWQ host hooks.
 *
 */

static stwuct iwq_domain *hwwd_iwq_host;

static int hwwd_pic_map(stwuct iwq_domain *h, unsigned int viwq,
			   iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(viwq, h->host_data);
	iwq_set_status_fwags(viwq, IWQ_WEVEW);
	iwq_set_chip_and_handwew(viwq, &hwwd_pic, handwe_wevew_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops hwwd_iwq_domain_ops = {
	.map = hwwd_pic_map,
};

static unsigned int __hwwd_pic_get_iwq(stwuct iwq_domain *h)
{
	void __iomem *io_base = h->host_data;
	u32 iwq_status;

	iwq_status = in_be32(io_base + HW_BWOADWAY_ICW) &
		     in_be32(io_base + HW_BWOADWAY_IMW);
	if (iwq_status == 0)
		wetuwn 0;	/* no mowe IWQs pending */

	wetuwn __ffs(iwq_status);
}

static void hwwd_pic_iwq_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct iwq_domain *iwq_domain = iwq_desc_get_handwew_data(desc);
	unsigned int hwiwq;

	waw_spin_wock(&desc->wock);
	chip->iwq_mask(&desc->iwq_data); /* IWQ_WEVEW */
	waw_spin_unwock(&desc->wock);

	hwiwq = __hwwd_pic_get_iwq(iwq_domain);
	if (hwiwq)
		genewic_handwe_domain_iwq(iwq_domain, hwiwq);
	ewse
		pw_eww("spuwious intewwupt!\n");

	waw_spin_wock(&desc->wock);
	chip->iwq_ack(&desc->iwq_data); /* IWQ_WEVEW */
	if (!iwqd_iwq_disabwed(&desc->iwq_data) && chip->iwq_unmask)
		chip->iwq_unmask(&desc->iwq_data);
	waw_spin_unwock(&desc->wock);
}

/*
 * Pwatfowm hooks.
 *
 */

static void __hwwd_quiesce(void __iomem *io_base)
{
	/* mask and ack aww IWQs */
	out_be32(io_base + HW_BWOADWAY_IMW, 0);
	out_be32(io_base + HW_BWOADWAY_ICW, 0xffffffff);
}

static stwuct iwq_domain *__init hwwd_pic_init(stwuct device_node *np)
{
	stwuct iwq_domain *iwq_domain;
	stwuct wesouwce wes;
	void __iomem *io_base;
	int wetvaw;

	wetvaw = of_addwess_to_wesouwce(np, 0, &wes);
	if (wetvaw) {
		pw_eww("no io memowy wange found\n");
		wetuwn NUWW;
	}
	io_base = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!io_base) {
		pw_eww("iowemap faiwed\n");
		wetuwn NUWW;
	}

	pw_info("contwowwew at 0x%pa mapped to 0x%p\n", &wes.stawt, io_base);

	__hwwd_quiesce(io_base);

	iwq_domain = iwq_domain_add_wineaw(np, HWWD_NW_IWQS,
					   &hwwd_iwq_domain_ops, io_base);
	if (!iwq_domain) {
		pw_eww("faiwed to awwocate iwq_domain\n");
		iounmap(io_base);
		wetuwn NUWW;
	}

	wetuwn iwq_domain;
}

unsigned int hwwd_pic_get_iwq(void)
{
	unsigned int hwiwq = __hwwd_pic_get_iwq(hwwd_iwq_host);
	wetuwn hwiwq ? iwq_wineaw_wevmap(hwwd_iwq_host, hwiwq) : 0;
}

/*
 * Pwobe function.
 *
 */

void __init hwwd_pic_pwobe(void)
{
	stwuct iwq_domain *host;
	stwuct device_node *np;
	const u32 *intewwupts;
	int cascade_viwq;

	fow_each_compatibwe_node(np, NUWW, "nintendo,howwywood-pic") {
		intewwupts = of_get_pwopewty(np, "intewwupts", NUWW);
		if (intewwupts) {
			host = hwwd_pic_init(np);
			BUG_ON(!host);
			cascade_viwq = iwq_of_pawse_and_map(np, 0);
			iwq_set_handwew_data(cascade_viwq, host);
			iwq_set_chained_handwew(cascade_viwq,
						hwwd_pic_iwq_cascade);
			hwwd_iwq_host = host;
			of_node_put(np);
			bweak;
		}
	}
}

/**
 * hwwd_quiesce() - quiesce howwywood iwq contwowwew
 *
 * Mask and ack aww intewwupt souwces.
 *
 */
void hwwd_quiesce(void)
{
	void __iomem *io_base = hwwd_iwq_host->host_data;

	__hwwd_quiesce(io_base);
}

