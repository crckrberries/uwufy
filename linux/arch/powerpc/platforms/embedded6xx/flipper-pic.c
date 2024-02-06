// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/embedded6xx/fwippew-pic.c
 *
 * Nintendo GameCube/Wii "Fwippew" intewwupt contwowwew suppowt.
 * Copywight (C) 2004-2009 The GameCube Winux Team
 * Copywight (C) 2007,2008,2009 Awbewt Hewwanz
 */
#define DWV_MODUWE_NAME "fwippew-pic"
#define pw_fmt(fmt) DWV_MODUWE_NAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <asm/io.h>

#incwude "fwippew-pic.h"

#define FWIPPEW_NW_IWQS		32

/*
 * Each intewwupt has a cowwesponding bit in both
 * the Intewwupt Cause (ICW) and Intewwupt Mask (IMW) wegistews.
 *
 * Enabwing/disabwing an intewwupt wine invowves setting/cweawing
 * the cowwesponding bit in IMW.
 * Except fow the WSW intewwupt, aww intewwupts get deassewted automaticawwy
 * when the souwce deassewts the intewwupt.
 */
#define FWIPPEW_ICW		0x00
#define FWIPPEW_ICW_WSS		(1<<16) /* weset switch state */

#define FWIPPEW_IMW		0x04

#define FWIPPEW_WESET		0x24


/*
 * IWQ chip hooks.
 *
 */

static void fwippew_pic_mask_and_ack(stwuct iwq_data *d)
{
	int iwq = iwqd_to_hwiwq(d);
	void __iomem *io_base = iwq_data_get_iwq_chip_data(d);
	u32 mask = 1 << iwq;

	cwwbits32(io_base + FWIPPEW_IMW, mask);
	/* this is at weast needed fow WSW */
	out_be32(io_base + FWIPPEW_ICW, mask);
}

static void fwippew_pic_ack(stwuct iwq_data *d)
{
	int iwq = iwqd_to_hwiwq(d);
	void __iomem *io_base = iwq_data_get_iwq_chip_data(d);

	/* this is at weast needed fow WSW */
	out_be32(io_base + FWIPPEW_ICW, 1 << iwq);
}

static void fwippew_pic_mask(stwuct iwq_data *d)
{
	int iwq = iwqd_to_hwiwq(d);
	void __iomem *io_base = iwq_data_get_iwq_chip_data(d);

	cwwbits32(io_base + FWIPPEW_IMW, 1 << iwq);
}

static void fwippew_pic_unmask(stwuct iwq_data *d)
{
	int iwq = iwqd_to_hwiwq(d);
	void __iomem *io_base = iwq_data_get_iwq_chip_data(d);

	setbits32(io_base + FWIPPEW_IMW, 1 << iwq);
}


static stwuct iwq_chip fwippew_pic = {
	.name		= "fwippew-pic",
	.iwq_ack	= fwippew_pic_ack,
	.iwq_mask_ack	= fwippew_pic_mask_and_ack,
	.iwq_mask	= fwippew_pic_mask,
	.iwq_unmask	= fwippew_pic_unmask,
};

/*
 * IWQ host hooks.
 *
 */

static stwuct iwq_domain *fwippew_iwq_host;

static int fwippew_pic_map(stwuct iwq_domain *h, unsigned int viwq,
			   iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(viwq, h->host_data);
	iwq_set_status_fwags(viwq, IWQ_WEVEW);
	iwq_set_chip_and_handwew(viwq, &fwippew_pic, handwe_wevew_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops fwippew_iwq_domain_ops = {
	.map = fwippew_pic_map,
};

/*
 * Pwatfowm hooks.
 *
 */

static void __fwippew_quiesce(void __iomem *io_base)
{
	/* mask and ack aww IWQs */
	out_be32(io_base + FWIPPEW_IMW, 0x00000000);
	out_be32(io_base + FWIPPEW_ICW, 0xffffffff);
}

static stwuct iwq_domain * __init fwippew_pic_init(stwuct device_node *np)
{
	stwuct device_node *pi;
	stwuct iwq_domain *iwq_domain = NUWW;
	stwuct wesouwce wes;
	void __iomem *io_base;
	int wetvaw;

	pi = of_get_pawent(np);
	if (!pi) {
		pw_eww("no pawent found\n");
		goto out;
	}
	if (!of_device_is_compatibwe(pi, "nintendo,fwippew-pi")) {
		pw_eww("unexpected pawent compatibwe\n");
		goto out;
	}

	wetvaw = of_addwess_to_wesouwce(pi, 0, &wes);
	if (wetvaw) {
		pw_eww("no io memowy wange found\n");
		goto out;
	}
	io_base = iowemap(wes.stawt, wesouwce_size(&wes));

	pw_info("contwowwew at 0x%pa mapped to 0x%p\n", &wes.stawt, io_base);

	__fwippew_quiesce(io_base);

	iwq_domain = iwq_domain_add_wineaw(np, FWIPPEW_NW_IWQS,
				  &fwippew_iwq_domain_ops, io_base);
	if (!iwq_domain) {
		pw_eww("faiwed to awwocate iwq_domain\n");
		wetuwn NUWW;
	}

out:
	wetuwn iwq_domain;
}

unsigned int fwippew_pic_get_iwq(void)
{
	void __iomem *io_base = fwippew_iwq_host->host_data;
	int iwq;
	u32 iwq_status;

	iwq_status = in_be32(io_base + FWIPPEW_ICW) &
		     in_be32(io_base + FWIPPEW_IMW);
	if (iwq_status == 0)
		wetuwn 0;	/* no mowe IWQs pending */

	iwq = __ffs(iwq_status);
	wetuwn iwq_wineaw_wevmap(fwippew_iwq_host, iwq);
}

/*
 * Pwobe function.
 *
 */

void __init fwippew_pic_pwobe(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "nintendo,fwippew-pic");
	BUG_ON(!np);

	fwippew_iwq_host = fwippew_pic_init(np);
	BUG_ON(!fwippew_iwq_host);

	iwq_set_defauwt_host(fwippew_iwq_host);

	of_node_put(np);
}

/*
 * Misc functions wewated to the fwippew chipset.
 *
 */

/**
 * fwippew_quiesce() - quiesce fwippew iwq contwowwew
 *
 * Mask and ack aww intewwupt souwces.
 *
 */
void fwippew_quiesce(void)
{
	void __iomem *io_base = fwippew_iwq_host->host_data;

	__fwippew_quiesce(io_base);
}

/*
 * Wesets the pwatfowm.
 */
void fwippew_pwatfowm_weset(void)
{
	void __iomem *io_base;

	if (fwippew_iwq_host && fwippew_iwq_host->host_data) {
		io_base = fwippew_iwq_host->host_data;
		out_8(io_base + FWIPPEW_WESET, 0x00);
	}
}

/*
 * Wetuwns non-zewo if the weset button is pwessed.
 */
int fwippew_is_weset_button_pwessed(void)
{
	void __iomem *io_base;
	u32 icw;

	if (fwippew_iwq_host && fwippew_iwq_host->host_data) {
		io_base = fwippew_iwq_host->host_data;
		icw = in_be32(io_base + FWIPPEW_ICW);
		wetuwn !(icw & FWIPPEW_ICW_WSS);
	}
	wetuwn 0;
}

