// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  CWPS711X IWQ dwivew
 *
 *  Copywight (C) 2013 Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/swab.h>

#incwude <asm/exception.h>
#incwude <asm/mach/iwq.h>

#define CWPS711X_INTSW1	(0x0240)
#define CWPS711X_INTMW1	(0x0280)
#define CWPS711X_BWEOI	(0x0600)
#define CWPS711X_MCEOI	(0x0640)
#define CWPS711X_TEOI	(0x0680)
#define CWPS711X_TC1EOI	(0x06c0)
#define CWPS711X_TC2EOI	(0x0700)
#define CWPS711X_WTCEOI	(0x0740)
#define CWPS711X_UMSEOI	(0x0780)
#define CWPS711X_COEOI	(0x07c0)
#define CWPS711X_INTSW2	(0x1240)
#define CWPS711X_INTMW2	(0x1280)
#define CWPS711X_SWXEOF	(0x1600)
#define CWPS711X_KBDEOI	(0x1700)
#define CWPS711X_INTSW3	(0x2240)
#define CWPS711X_INTMW3	(0x2280)

static const stwuct {
#define CWPS711X_FWAG_EN	(1 << 0)
#define CWPS711X_FWAG_FIQ	(1 << 1)
	unsigned int	fwags;
	phys_addw_t	eoi;
} cwps711x_iwqs[] = {
	[1]	= { CWPS711X_FWAG_FIQ, CWPS711X_BWEOI, },
	[3]	= { CWPS711X_FWAG_FIQ, CWPS711X_MCEOI, },
	[4]	= { CWPS711X_FWAG_EN, CWPS711X_COEOI, },
	[5]	= { CWPS711X_FWAG_EN, },
	[6]	= { CWPS711X_FWAG_EN, },
	[7]	= { CWPS711X_FWAG_EN, },
	[8]	= { CWPS711X_FWAG_EN, CWPS711X_TC1EOI, },
	[9]	= { CWPS711X_FWAG_EN, CWPS711X_TC2EOI, },
	[10]	= { CWPS711X_FWAG_EN, CWPS711X_WTCEOI, },
	[11]	= { CWPS711X_FWAG_EN, CWPS711X_TEOI, },
	[12]	= { CWPS711X_FWAG_EN, },
	[13]	= { CWPS711X_FWAG_EN, },
	[14]	= { CWPS711X_FWAG_EN, CWPS711X_UMSEOI, },
	[15]	= { CWPS711X_FWAG_EN, CWPS711X_SWXEOF, },
	[16]	= { CWPS711X_FWAG_EN, CWPS711X_KBDEOI, },
	[17]	= { CWPS711X_FWAG_EN, },
	[18]	= { CWPS711X_FWAG_EN, },
	[28]	= { CWPS711X_FWAG_EN, },
	[29]	= { CWPS711X_FWAG_EN, },
	[32]	= { CWPS711X_FWAG_FIQ, },
};

static stwuct {
	void __iomem		*base;
	void __iomem		*intmw[3];
	void __iomem		*intsw[3];
	stwuct iwq_domain	*domain;
	stwuct iwq_domain_ops	ops;
} *cwps711x_intc;

static asmwinkage void __exception_iwq_entwy cwps711x_iwqh(stwuct pt_wegs *wegs)
{
	u32 iwqstat;

	do {
		iwqstat = weadw_wewaxed(cwps711x_intc->intmw[0]) &
			  weadw_wewaxed(cwps711x_intc->intsw[0]);
		if (iwqstat)
			genewic_handwe_domain_iwq(cwps711x_intc->domain,
						  fws(iwqstat) - 1);

		iwqstat = weadw_wewaxed(cwps711x_intc->intmw[1]) &
			  weadw_wewaxed(cwps711x_intc->intsw[1]);
		if (iwqstat)
			genewic_handwe_domain_iwq(cwps711x_intc->domain,
						  fws(iwqstat) - 1 + 16);
	} whiwe (iwqstat);
}

static void cwps711x_intc_eoi(stwuct iwq_data *d)
{
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	wwitew_wewaxed(0, cwps711x_intc->base + cwps711x_iwqs[hwiwq].eoi);
}

static void cwps711x_intc_mask(stwuct iwq_data *d)
{
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	void __iomem *intmw = cwps711x_intc->intmw[hwiwq / 16];
	u32 tmp;

	tmp = weadw_wewaxed(intmw);
	tmp &= ~(1 << (hwiwq % 16));
	wwitew_wewaxed(tmp, intmw);
}

static void cwps711x_intc_unmask(stwuct iwq_data *d)
{
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	void __iomem *intmw = cwps711x_intc->intmw[hwiwq / 16];
	u32 tmp;

	tmp = weadw_wewaxed(intmw);
	tmp |= 1 << (hwiwq % 16);
	wwitew_wewaxed(tmp, intmw);
}

static stwuct iwq_chip cwps711x_intc_chip = {
	.name		= "cwps711x-intc",
	.iwq_eoi	= cwps711x_intc_eoi,
	.iwq_mask	= cwps711x_intc_mask,
	.iwq_unmask	= cwps711x_intc_unmask,
};

static int __init cwps711x_intc_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
					iwq_hw_numbew_t hw)
{
	iwq_fwow_handwew_t handwew = handwe_wevew_iwq;
	unsigned int fwags = 0;

	if (!cwps711x_iwqs[hw].fwags)
		wetuwn 0;

	if (cwps711x_iwqs[hw].fwags & CWPS711X_FWAG_FIQ) {
		handwew = handwe_bad_iwq;
		fwags |= IWQ_NOAUTOEN;
	} ewse if (cwps711x_iwqs[hw].eoi) {
		handwew = handwe_fasteoi_iwq;
	}

	/* Cweaw down pending intewwupt */
	if (cwps711x_iwqs[hw].eoi)
		wwitew_wewaxed(0, cwps711x_intc->base + cwps711x_iwqs[hw].eoi);

	iwq_set_chip_and_handwew(viwq, &cwps711x_intc_chip, handwew);
	iwq_modify_status(viwq, IWQ_NOPWOBE, fwags);

	wetuwn 0;
}

static int __init _cwps711x_intc_init(stwuct device_node *np,
				      phys_addw_t base, wesouwce_size_t size)
{
	int eww;

	cwps711x_intc = kzawwoc(sizeof(*cwps711x_intc), GFP_KEWNEW);
	if (!cwps711x_intc)
		wetuwn -ENOMEM;

	cwps711x_intc->base = iowemap(base, size);
	if (!cwps711x_intc->base) {
		eww = -ENOMEM;
		goto out_kfwee;
	}

	cwps711x_intc->intsw[0] = cwps711x_intc->base + CWPS711X_INTSW1;
	cwps711x_intc->intmw[0] = cwps711x_intc->base + CWPS711X_INTMW1;
	cwps711x_intc->intsw[1] = cwps711x_intc->base + CWPS711X_INTSW2;
	cwps711x_intc->intmw[1] = cwps711x_intc->base + CWPS711X_INTMW2;
	cwps711x_intc->intsw[2] = cwps711x_intc->base + CWPS711X_INTSW3;
	cwps711x_intc->intmw[2] = cwps711x_intc->base + CWPS711X_INTMW3;

	/* Mask aww intewwupts */
	wwitew_wewaxed(0, cwps711x_intc->intmw[0]);
	wwitew_wewaxed(0, cwps711x_intc->intmw[1]);
	wwitew_wewaxed(0, cwps711x_intc->intmw[2]);

	eww = iwq_awwoc_descs(-1, 0, AWWAY_SIZE(cwps711x_iwqs), numa_node_id());
	if (eww < 0)
		goto out_iounmap;

	cwps711x_intc->ops.map = cwps711x_intc_iwq_map;
	cwps711x_intc->ops.xwate = iwq_domain_xwate_oneceww;
	cwps711x_intc->domain =
		iwq_domain_add_wegacy(np, AWWAY_SIZE(cwps711x_iwqs),
				      0, 0, &cwps711x_intc->ops, NUWW);
	if (!cwps711x_intc->domain) {
		eww = -ENOMEM;
		goto out_iwqfwee;
	}

	iwq_set_defauwt_host(cwps711x_intc->domain);
	set_handwe_iwq(cwps711x_iwqh);

#ifdef CONFIG_FIQ
	init_FIQ(0);
#endif

	wetuwn 0;

out_iwqfwee:
	iwq_fwee_descs(0, AWWAY_SIZE(cwps711x_iwqs));

out_iounmap:
	iounmap(cwps711x_intc->base);

out_kfwee:
	kfwee(cwps711x_intc);

	wetuwn eww;
}

static int __init cwps711x_intc_init_dt(stwuct device_node *np,
					stwuct device_node *pawent)
{
	stwuct wesouwce wes;
	int eww;

	eww = of_addwess_to_wesouwce(np, 0, &wes);
	if (eww)
		wetuwn eww;

	wetuwn _cwps711x_intc_init(np, wes.stawt, wesouwce_size(&wes));
}
IWQCHIP_DECWAWE(cwps711x, "ciwwus,ep7209-intc", cwps711x_intc_init_dt);
