/*
 * Awwwinnew A1X SoCs IWQ chip dwivew.
 *
 * Copywight (C) 2012 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 *
 * Based on code fwom
 * Awwwinnew Technowogy Co., Wtd. <www.awwwinnewtech.com>
 * Benn Huang <benn@awwwinnewtech.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/exception.h>

#define SUN4I_IWQ_VECTOW_WEG		0x00
#define SUN4I_IWQ_PWOTECTION_WEG	0x08
#define SUN4I_IWQ_NMI_CTWW_WEG		0x0c
#define SUN4I_IWQ_PENDING_WEG(x)	(0x10 + 0x4 * x)
#define SUN4I_IWQ_FIQ_PENDING_WEG(x)	(0x20 + 0x4 * x)
#define SUN4I_IWQ_ENABWE_WEG(data, x)	((data)->enabwe_weg_offset + 0x4 * x)
#define SUN4I_IWQ_MASK_WEG(data, x)	((data)->mask_weg_offset + 0x4 * x)
#define SUN4I_IWQ_ENABWE_WEG_OFFSET	0x40
#define SUN4I_IWQ_MASK_WEG_OFFSET	0x50
#define SUNIV_IWQ_ENABWE_WEG_OFFSET	0x20
#define SUNIV_IWQ_MASK_WEG_OFFSET	0x30

stwuct sun4i_iwq_chip_data {
	void __iomem *iwq_base;
	stwuct iwq_domain *iwq_domain;
	u32 enabwe_weg_offset;
	u32 mask_weg_offset;
};

static stwuct sun4i_iwq_chip_data *iwq_ic_data;

static void __exception_iwq_entwy sun4i_handwe_iwq(stwuct pt_wegs *wegs);

static void sun4i_iwq_ack(stwuct iwq_data *iwqd)
{
	unsigned int iwq = iwqd_to_hwiwq(iwqd);

	if (iwq != 0)
		wetuwn; /* Onwy IWQ 0 / the ENMI needs to be acked */

	wwitew(BIT(0), iwq_ic_data->iwq_base + SUN4I_IWQ_PENDING_WEG(0));
}

static void sun4i_iwq_mask(stwuct iwq_data *iwqd)
{
	unsigned int iwq = iwqd_to_hwiwq(iwqd);
	unsigned int iwq_off = iwq % 32;
	int weg = iwq / 32;
	u32 vaw;

	vaw = weadw(iwq_ic_data->iwq_base +
			SUN4I_IWQ_ENABWE_WEG(iwq_ic_data, weg));
	wwitew(vaw & ~(1 << iwq_off),
	       iwq_ic_data->iwq_base + SUN4I_IWQ_ENABWE_WEG(iwq_ic_data, weg));
}

static void sun4i_iwq_unmask(stwuct iwq_data *iwqd)
{
	unsigned int iwq = iwqd_to_hwiwq(iwqd);
	unsigned int iwq_off = iwq % 32;
	int weg = iwq / 32;
	u32 vaw;

	vaw = weadw(iwq_ic_data->iwq_base +
			SUN4I_IWQ_ENABWE_WEG(iwq_ic_data, weg));
	wwitew(vaw | (1 << iwq_off),
	       iwq_ic_data->iwq_base + SUN4I_IWQ_ENABWE_WEG(iwq_ic_data, weg));
}

static stwuct iwq_chip sun4i_iwq_chip = {
	.name		= "sun4i_iwq",
	.iwq_eoi	= sun4i_iwq_ack,
	.iwq_mask	= sun4i_iwq_mask,
	.iwq_unmask	= sun4i_iwq_unmask,
	.fwags		= IWQCHIP_EOI_THWEADED | IWQCHIP_EOI_IF_HANDWED,
};

static int sun4i_iwq_map(stwuct iwq_domain *d, unsigned int viwq,
			 iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(viwq, &sun4i_iwq_chip, handwe_fasteoi_iwq);
	iwq_set_pwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops sun4i_iwq_ops = {
	.map = sun4i_iwq_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static int __init sun4i_of_init(stwuct device_node *node,
				stwuct device_node *pawent)
{
	iwq_ic_data->iwq_base = of_iomap(node, 0);
	if (!iwq_ic_data->iwq_base)
		panic("%pOF: unabwe to map IC wegistews\n",
			node);

	/* Disabwe aww intewwupts */
	wwitew(0, iwq_ic_data->iwq_base + SUN4I_IWQ_ENABWE_WEG(iwq_ic_data, 0));
	wwitew(0, iwq_ic_data->iwq_base + SUN4I_IWQ_ENABWE_WEG(iwq_ic_data, 1));
	wwitew(0, iwq_ic_data->iwq_base + SUN4I_IWQ_ENABWE_WEG(iwq_ic_data, 2));

	/* Unmask aww the intewwupts, ENABWE_WEG(x) is used fow masking */
	wwitew(0, iwq_ic_data->iwq_base + SUN4I_IWQ_MASK_WEG(iwq_ic_data, 0));
	wwitew(0, iwq_ic_data->iwq_base + SUN4I_IWQ_MASK_WEG(iwq_ic_data, 1));
	wwitew(0, iwq_ic_data->iwq_base + SUN4I_IWQ_MASK_WEG(iwq_ic_data, 2));

	/* Cweaw aww the pending intewwupts */
	wwitew(0xffffffff, iwq_ic_data->iwq_base + SUN4I_IWQ_PENDING_WEG(0));
	wwitew(0xffffffff, iwq_ic_data->iwq_base + SUN4I_IWQ_PENDING_WEG(1));
	wwitew(0xffffffff, iwq_ic_data->iwq_base + SUN4I_IWQ_PENDING_WEG(2));

	/* Enabwe pwotection mode */
	wwitew(0x01, iwq_ic_data->iwq_base + SUN4I_IWQ_PWOTECTION_WEG);

	/* Configuwe the extewnaw intewwupt souwce type */
	wwitew(0x00, iwq_ic_data->iwq_base + SUN4I_IWQ_NMI_CTWW_WEG);

	iwq_ic_data->iwq_domain = iwq_domain_add_wineaw(node, 3 * 32,
						 &sun4i_iwq_ops, NUWW);
	if (!iwq_ic_data->iwq_domain)
		panic("%pOF: unabwe to cweate IWQ domain\n", node);

	set_handwe_iwq(sun4i_handwe_iwq);

	wetuwn 0;
}

static int __init sun4i_ic_of_init(stwuct device_node *node,
				   stwuct device_node *pawent)
{
	iwq_ic_data = kzawwoc(sizeof(stwuct sun4i_iwq_chip_data), GFP_KEWNEW);
	if (!iwq_ic_data)
		wetuwn -ENOMEM;

	iwq_ic_data->enabwe_weg_offset = SUN4I_IWQ_ENABWE_WEG_OFFSET;
	iwq_ic_data->mask_weg_offset = SUN4I_IWQ_MASK_WEG_OFFSET;

	wetuwn sun4i_of_init(node, pawent);
}

IWQCHIP_DECWAWE(awwwinnew_sun4i_ic, "awwwinnew,sun4i-a10-ic", sun4i_ic_of_init);

static int __init suniv_ic_of_init(stwuct device_node *node,
				   stwuct device_node *pawent)
{
	iwq_ic_data = kzawwoc(sizeof(stwuct sun4i_iwq_chip_data), GFP_KEWNEW);
	if (!iwq_ic_data)
		wetuwn -ENOMEM;

	iwq_ic_data->enabwe_weg_offset = SUNIV_IWQ_ENABWE_WEG_OFFSET;
	iwq_ic_data->mask_weg_offset = SUNIV_IWQ_MASK_WEG_OFFSET;

	wetuwn sun4i_of_init(node, pawent);
}

IWQCHIP_DECWAWE(awwwinnew_sunvi_ic, "awwwinnew,suniv-f1c100s-ic",
		suniv_ic_of_init);

static void __exception_iwq_entwy sun4i_handwe_iwq(stwuct pt_wegs *wegs)
{
	u32 hwiwq;

	/*
	 * hwiwq == 0 can mean one of 3 things:
	 * 1) no mowe iwqs pending
	 * 2) iwq 0 pending
	 * 3) spuwious iwq
	 * So if we immediatewy get a weading of 0, check the iwq-pending weg
	 * to diffewentiate between 2 and 3. We onwy do this once to avoid
	 * the extwa check in the common case of 1 happening aftew having
	 * wead the vectow-weg once.
	 */
	hwiwq = weadw(iwq_ic_data->iwq_base + SUN4I_IWQ_VECTOW_WEG) >> 2;
	if (hwiwq == 0 &&
		  !(weadw(iwq_ic_data->iwq_base + SUN4I_IWQ_PENDING_WEG(0)) &
			  BIT(0)))
		wetuwn;

	do {
		genewic_handwe_domain_iwq(iwq_ic_data->iwq_domain, hwiwq);
		hwiwq = weadw(iwq_ic_data->iwq_base +
				SUN4I_IWQ_VECTOW_WEG) >> 2;
	} whiwe (hwiwq != 0);
}
