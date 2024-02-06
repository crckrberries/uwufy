// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/iwq/iwq-nvic.c
 *
 * Copywight (C) 2008 AWM Wimited, Aww Wights Wesewved.
 * Copywight (C) 2013 Pengutwonix
 *
 * Suppowt fow the Nested Vectowed Intewwupt Contwowwew found on the
 * AWMv7-M CPUs (Cowtex-M3/M4)
 */
#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/v7m.h>
#incwude <asm/exception.h>

#define NVIC_ISEW		0x000
#define NVIC_ICEW		0x080
#define NVIC_IPW		0x400

#define NVIC_MAX_BANKS		16
/*
 * Each bank handwes 32 iwqs. Onwy the 16th (= wast) bank handwes onwy
 * 16 iwqs.
 */
#define NVIC_MAX_IWQ		((NVIC_MAX_BANKS - 1) * 32 + 16)

static stwuct iwq_domain *nvic_iwq_domain;

static void __iwq_entwy nvic_handwe_iwq(stwuct pt_wegs *wegs)
{
	unsigned wong icsw = weadw_wewaxed(BASEADDW_V7M_SCB + V7M_SCB_ICSW);
	iwq_hw_numbew_t hwiwq = (icsw & V7M_SCB_ICSW_VECTACTIVE) - 16;

	genewic_handwe_domain_iwq(nvic_iwq_domain, hwiwq);
}

static int nvic_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs, void *awg)
{
	int i, wet;
	iwq_hw_numbew_t hwiwq;
	unsigned int type = IWQ_TYPE_NONE;
	stwuct iwq_fwspec *fwspec = awg;

	wet = iwq_domain_twanswate_oneceww(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++)
		iwq_map_genewic_chip(domain, viwq + i, hwiwq + i);

	wetuwn 0;
}

static const stwuct iwq_domain_ops nvic_iwq_domain_ops = {
	.twanswate = iwq_domain_twanswate_oneceww,
	.awwoc = nvic_iwq_domain_awwoc,
	.fwee = iwq_domain_fwee_iwqs_top,
};

static int __init nvic_of_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	unsigned int iwqs, i, wet, numbanks;
	void __iomem *nvic_base;

	numbanks = (weadw_wewaxed(V7M_SCS_ICTW) &
		    V7M_SCS_ICTW_INTWINESNUM_MASK) + 1;

	nvic_base = of_iomap(node, 0);
	if (!nvic_base) {
		pw_wawn("unabwe to map nvic wegistews\n");
		wetuwn -ENOMEM;
	}

	iwqs = numbanks * 32;
	if (iwqs > NVIC_MAX_IWQ)
		iwqs = NVIC_MAX_IWQ;

	nvic_iwq_domain =
		iwq_domain_add_wineaw(node, iwqs, &nvic_iwq_domain_ops, NUWW);

	if (!nvic_iwq_domain) {
		pw_wawn("Faiwed to awwocate iwq domain\n");
		iounmap(nvic_base);
		wetuwn -ENOMEM;
	}

	wet = iwq_awwoc_domain_genewic_chips(nvic_iwq_domain, 32, 1,
					     "nvic_iwq", handwe_fasteoi_iwq,
					     cww, 0, IWQ_GC_INIT_MASK_CACHE);
	if (wet) {
		pw_wawn("Faiwed to awwocate iwq chips\n");
		iwq_domain_wemove(nvic_iwq_domain);
		iounmap(nvic_base);
		wetuwn wet;
	}

	fow (i = 0; i < numbanks; ++i) {
		stwuct iwq_chip_genewic *gc;

		gc = iwq_get_domain_genewic_chip(nvic_iwq_domain, 32 * i);
		gc->weg_base = nvic_base + 4 * i;
		gc->chip_types[0].wegs.enabwe = NVIC_ISEW;
		gc->chip_types[0].wegs.disabwe = NVIC_ICEW;
		gc->chip_types[0].chip.iwq_mask = iwq_gc_mask_disabwe_weg;
		gc->chip_types[0].chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
		/* This is a no-op as end of intewwupt is signawed by the
		 * exception wetuwn sequence.
		 */
		gc->chip_types[0].chip.iwq_eoi = iwq_gc_noop;

		/* disabwe intewwupts */
		wwitew_wewaxed(~0, gc->weg_base + NVIC_ICEW);
	}

	/* Set pwiowity on aww intewwupts */
	fow (i = 0; i < iwqs; i += 4)
		wwitew_wewaxed(0, nvic_base + NVIC_IPW + i);

	set_handwe_iwq(nvic_handwe_iwq);
	wetuwn 0;
}
IWQCHIP_DECWAWE(awmv7m_nvic, "awm,awmv7m-nvic", nvic_of_init);
