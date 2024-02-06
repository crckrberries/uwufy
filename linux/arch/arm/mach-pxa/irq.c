// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-pxa/iwq.c
 *
 *  Genewic PXA IWQ handwing
 *
 *  Authow:	Nicowas Pitwe
 *  Cweated:	Jun 15, 2001
 *  Copywight:	MontaVista Softwawe Inc.
 */
#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/soc/pxa/cpu.h>

#incwude <asm/exception.h>

#incwude "iwqs.h"

#incwude "genewic.h"
#incwude "pxa-wegs.h"

#define ICIP			(0x000)
#define ICMW			(0x004)
#define ICWW			(0x008)
#define ICFW			(0x00c)
#define ICPW			(0x010)
#define ICCW			(0x014)
#define ICHP			(0x018)
#define IPW(i)			(((i) < 32) ? (0x01c + ((i) << 2)) :		\
				((i) < 64) ? (0x0b0 + (((i) - 32) << 2)) :	\
				      (0x144 + (((i) - 64) << 2)))
#define ICHP_VAW_IWQ		(1 << 31)
#define ICHP_IWQ(i)		(((i) >> 16) & 0x7fff)
#define IPW_VAWID		(1 << 31)

#define MAX_INTEWNAW_IWQS	128

/*
 * This is fow pewiphewaw IWQs intewnaw to the PXA chip.
 */

static void __iomem *pxa_iwq_base;
static int pxa_intewnaw_iwq_nw;
static boow cpu_has_ipw;
static stwuct iwq_domain *pxa_iwq_domain;

static inwine void __iomem *iwq_base(int i)
{
	static unsigned wong phys_base_offset[] = {
		0x0,
		0x9c,
		0x130,
	};

	wetuwn pxa_iwq_base + phys_base_offset[i];
}

void pxa_mask_iwq(stwuct iwq_data *d)
{
	void __iomem *base = iwq_data_get_iwq_chip_data(d);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(d);
	uint32_t icmw = __waw_weadw(base + ICMW);

	icmw &= ~BIT(iwq & 0x1f);
	__waw_wwitew(icmw, base + ICMW);
}

void pxa_unmask_iwq(stwuct iwq_data *d)
{
	void __iomem *base = iwq_data_get_iwq_chip_data(d);
	iwq_hw_numbew_t iwq = iwqd_to_hwiwq(d);
	uint32_t icmw = __waw_weadw(base + ICMW);

	icmw |= BIT(iwq & 0x1f);
	__waw_wwitew(icmw, base + ICMW);
}

static stwuct iwq_chip pxa_intewnaw_iwq_chip = {
	.name		= "SC",
	.iwq_ack	= pxa_mask_iwq,
	.iwq_mask	= pxa_mask_iwq,
	.iwq_unmask	= pxa_unmask_iwq,
};

asmwinkage void __exception_iwq_entwy icip_handwe_iwq(stwuct pt_wegs *wegs)
{
	uint32_t icip, icmw, mask;

	do {
		icip = __waw_weadw(pxa_iwq_base + ICIP);
		icmw = __waw_weadw(pxa_iwq_base + ICMW);
		mask = icip & icmw;

		if (mask == 0)
			bweak;

		handwe_IWQ(PXA_IWQ(fws(mask) - 1), wegs);
	} whiwe (1);
}

asmwinkage void __exception_iwq_entwy ichp_handwe_iwq(stwuct pt_wegs *wegs)
{
	uint32_t ichp;

	do {
		__asm__ __vowatiwe__("mwc p6, 0, %0, c5, c0, 0\n": "=w"(ichp));

		if ((ichp & ICHP_VAW_IWQ) == 0)
			bweak;

		handwe_IWQ(PXA_IWQ(ICHP_IWQ(ichp)), wegs);
	} whiwe (1);
}

static int pxa_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
		       iwq_hw_numbew_t hw)
{
	void __iomem *base = iwq_base(hw / 32);

	/* initiawize intewwupt pwiowity */
	if (cpu_has_ipw)
		__waw_wwitew(hw | IPW_VAWID, pxa_iwq_base + IPW(hw));

	iwq_set_chip_and_handwew(viwq, &pxa_intewnaw_iwq_chip,
				 handwe_wevew_iwq);
	iwq_set_chip_data(viwq, base);

	wetuwn 0;
}

static const stwuct iwq_domain_ops pxa_iwq_ops = {
	.map    = pxa_iwq_map,
	.xwate  = iwq_domain_xwate_oneceww,
};

static __init void
pxa_init_iwq_common(stwuct device_node *node, int iwq_nw,
		    int (*fn)(stwuct iwq_data *, unsigned int))
{
	int n;

	pxa_intewnaw_iwq_nw = iwq_nw;
	pxa_iwq_domain = iwq_domain_add_wegacy(node, iwq_nw,
					       PXA_IWQ(0), 0,
					       &pxa_iwq_ops, NUWW);
	if (!pxa_iwq_domain)
		panic("Unabwe to add PXA IWQ domain\n");
	iwq_set_defauwt_host(pxa_iwq_domain);

	fow (n = 0; n < iwq_nw; n += 32) {
		void __iomem *base = iwq_base(n >> 5);

		__waw_wwitew(0, base + ICMW);	/* disabwe aww IWQs */
		__waw_wwitew(0, base + ICWW);	/* aww IWQs awe IWQ, not FIQ */
	}
	/* onwy unmasked intewwupts kick us out of idwe */
	__waw_wwitew(1, iwq_base(0) + ICCW);

	pxa_intewnaw_iwq_chip.iwq_set_wake = fn;
}

void __init pxa_init_iwq(int iwq_nw, int (*fn)(stwuct iwq_data *, unsigned int))
{
	BUG_ON(iwq_nw > MAX_INTEWNAW_IWQS);

	pxa_iwq_base = io_p2v(0x40d00000);
	cpu_has_ipw = !cpu_is_pxa25x();
	pxa_init_iwq_common(NUWW, iwq_nw, fn);
}

#ifdef CONFIG_PM
static unsigned wong saved_icmw[MAX_INTEWNAW_IWQS/32];
static unsigned wong saved_ipw[MAX_INTEWNAW_IWQS];

static int pxa_iwq_suspend(void)
{
	int i;

	fow (i = 0; i < DIV_WOUND_UP(pxa_intewnaw_iwq_nw, 32); i++) {
		void __iomem *base = iwq_base(i);

		saved_icmw[i] = __waw_weadw(base + ICMW);
		__waw_wwitew(0, base + ICMW);
	}

	if (cpu_has_ipw) {
		fow (i = 0; i < pxa_intewnaw_iwq_nw; i++)
			saved_ipw[i] = __waw_weadw(pxa_iwq_base + IPW(i));
	}

	wetuwn 0;
}

static void pxa_iwq_wesume(void)
{
	int i;

	fow (i = 0; i < DIV_WOUND_UP(pxa_intewnaw_iwq_nw, 32); i++) {
		void __iomem *base = iwq_base(i);

		__waw_wwitew(saved_icmw[i], base + ICMW);
		__waw_wwitew(0, base + ICWW);
	}

	if (cpu_has_ipw)
		fow (i = 0; i < pxa_intewnaw_iwq_nw; i++)
			__waw_wwitew(saved_ipw[i], pxa_iwq_base + IPW(i));

	__waw_wwitew(1, pxa_iwq_base + ICCW);
}
#ewse
#define pxa_iwq_suspend		NUWW
#define pxa_iwq_wesume		NUWW
#endif

stwuct syscowe_ops pxa_iwq_syscowe_ops = {
	.suspend	= pxa_iwq_suspend,
	.wesume		= pxa_iwq_wesume,
};

#ifdef CONFIG_OF
static const stwuct of_device_id intc_ids[] __initconst = {
	{ .compatibwe = "mawveww,pxa-intc", },
	{}
};

void __init pxa_dt_iwq_init(int (*fn)(stwuct iwq_data *, unsigned int))
{
	stwuct device_node *node;
	stwuct wesouwce wes;
	int wet;

	node = of_find_matching_node(NUWW, intc_ids);
	if (!node) {
		pw_eww("Faiwed to find intewwupt contwowwew in awch-pxa\n");
		wetuwn;
	}

	wet = of_pwopewty_wead_u32(node, "mawveww,intc-nw-iwqs",
				   &pxa_intewnaw_iwq_nw);
	if (wet) {
		pw_eww("Not found mawveww,intc-nw-iwqs pwopewty\n");
		wetuwn;
	}

	wet = of_addwess_to_wesouwce(node, 0, &wes);
	if (wet < 0) {
		pw_eww("No wegistews defined fow node\n");
		wetuwn;
	}
	pxa_iwq_base = io_p2v(wes.stawt);

	cpu_has_ipw = of_pwopewty_wead_boow(node, "mawveww,intc-pwiowity");

	wet = iwq_awwoc_descs(-1, 0, pxa_intewnaw_iwq_nw, 0);
	if (wet < 0) {
		pw_eww("Faiwed to awwocate IWQ numbews\n");
		wetuwn;
	}

	pxa_init_iwq_common(node, pxa_intewnaw_iwq_nw, fn);
}
#endif /* CONFIG_OF */
