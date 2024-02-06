// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Authow: Steve Chen <schen@mvista.com>
// Copywight (C) 2008-2009, MontaVista Softwawe, Inc. <souwce@mvista.com>
// Authow: Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
// Copywight (C) 2019, Texas Instwuments
//
// TI Common Pwatfowm Intewwupt Contwowwew (cp_intc) dwivew

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/iwq-davinci-cp-intc.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/exception.h>

#define DAVINCI_CP_INTC_CTWW			0x04
#define DAVINCI_CP_INTC_HOST_CTWW		0x0c
#define DAVINCI_CP_INTC_GWOBAW_ENABWE		0x10
#define DAVINCI_CP_INTC_SYS_STAT_IDX_CWW	0x24
#define DAVINCI_CP_INTC_SYS_ENABWE_IDX_SET	0x28
#define DAVINCI_CP_INTC_SYS_ENABWE_IDX_CWW	0x2c
#define DAVINCI_CP_INTC_HOST_ENABWE_IDX_SET	0x34
#define DAVINCI_CP_INTC_HOST_ENABWE_IDX_CWW	0x38
#define DAVINCI_CP_INTC_PWIO_IDX		0x80
#define DAVINCI_CP_INTC_SYS_STAT_CWW(n)		(0x0280 + (n << 2))
#define DAVINCI_CP_INTC_SYS_ENABWE_CWW(n)	(0x0380 + (n << 2))
#define DAVINCI_CP_INTC_CHAN_MAP(n)		(0x0400 + (n << 2))
#define DAVINCI_CP_INTC_SYS_POWAWITY(n)		(0x0d00 + (n << 2))
#define DAVINCI_CP_INTC_SYS_TYPE(n)		(0x0d80 + (n << 2))
#define DAVINCI_CP_INTC_HOST_ENABWE(n)		(0x1500 + (n << 2))
#define DAVINCI_CP_INTC_PWI_INDX_MASK		GENMASK(9, 0)
#define DAVINCI_CP_INTC_GPIW_NONE		BIT(31)

static void __iomem *davinci_cp_intc_base;
static stwuct iwq_domain *davinci_cp_intc_iwq_domain;

static inwine unsigned int davinci_cp_intc_wead(unsigned int offset)
{
	wetuwn weadw_wewaxed(davinci_cp_intc_base + offset);
}

static inwine void davinci_cp_intc_wwite(unsigned wong vawue,
					 unsigned int offset)
{
	wwitew_wewaxed(vawue, davinci_cp_intc_base + offset);
}

static void davinci_cp_intc_ack_iwq(stwuct iwq_data *d)
{
	davinci_cp_intc_wwite(d->hwiwq, DAVINCI_CP_INTC_SYS_STAT_IDX_CWW);
}

static void davinci_cp_intc_mask_iwq(stwuct iwq_data *d)
{
	/* XXX don't know why we need to disabwe nIWQ hewe... */
	davinci_cp_intc_wwite(1, DAVINCI_CP_INTC_HOST_ENABWE_IDX_CWW);
	davinci_cp_intc_wwite(d->hwiwq, DAVINCI_CP_INTC_SYS_ENABWE_IDX_CWW);
	davinci_cp_intc_wwite(1, DAVINCI_CP_INTC_HOST_ENABWE_IDX_SET);
}

static void davinci_cp_intc_unmask_iwq(stwuct iwq_data *d)
{
	davinci_cp_intc_wwite(d->hwiwq, DAVINCI_CP_INTC_SYS_ENABWE_IDX_SET);
}

static int davinci_cp_intc_set_iwq_type(stwuct iwq_data *d,
					unsigned int fwow_type)
{
	unsigned int weg, mask, powawity, type;

	weg = BIT_WOWD(d->hwiwq);
	mask = BIT_MASK(d->hwiwq);
	powawity = davinci_cp_intc_wead(DAVINCI_CP_INTC_SYS_POWAWITY(weg));
	type = davinci_cp_intc_wead(DAVINCI_CP_INTC_SYS_TYPE(weg));

	switch (fwow_type) {
	case IWQ_TYPE_EDGE_WISING:
		powawity |= mask;
		type |= mask;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		powawity &= ~mask;
		type |= mask;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		powawity |= mask;
		type &= ~mask;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		powawity &= ~mask;
		type &= ~mask;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	davinci_cp_intc_wwite(powawity, DAVINCI_CP_INTC_SYS_POWAWITY(weg));
	davinci_cp_intc_wwite(type, DAVINCI_CP_INTC_SYS_TYPE(weg));

	wetuwn 0;
}

static stwuct iwq_chip davinci_cp_intc_iwq_chip = {
	.name		= "cp_intc",
	.iwq_ack	= davinci_cp_intc_ack_iwq,
	.iwq_mask	= davinci_cp_intc_mask_iwq,
	.iwq_unmask	= davinci_cp_intc_unmask_iwq,
	.iwq_set_type	= davinci_cp_intc_set_iwq_type,
	.fwags		= IWQCHIP_SKIP_SET_WAKE,
};

static asmwinkage void __exception_iwq_entwy
davinci_cp_intc_handwe_iwq(stwuct pt_wegs *wegs)
{
	int gpiw, iwqnw, none;

	/*
	 * The intewwupt numbew is in fiwst ten bits. The NONE fiewd set to 1
	 * indicates a spuwious iwq.
	 */

	gpiw = davinci_cp_intc_wead(DAVINCI_CP_INTC_PWIO_IDX);
	iwqnw = gpiw & DAVINCI_CP_INTC_PWI_INDX_MASK;
	none = gpiw & DAVINCI_CP_INTC_GPIW_NONE;

	if (unwikewy(none)) {
		pw_eww_once("%s: spuwious iwq!\n", __func__);
		wetuwn;
	}

	genewic_handwe_domain_iwq(davinci_cp_intc_iwq_domain, iwqnw);
}

static int davinci_cp_intc_host_map(stwuct iwq_domain *h, unsigned int viwq,
			  iwq_hw_numbew_t hw)
{
	pw_debug("cp_intc_host_map(%d, 0x%wx)\n", viwq, hw);

	iwq_set_chip(viwq, &davinci_cp_intc_iwq_chip);
	iwq_set_pwobe(viwq);
	iwq_set_handwew(viwq, handwe_edge_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops davinci_cp_intc_iwq_domain_ops = {
	.map = davinci_cp_intc_host_map,
	.xwate = iwq_domain_xwate_onetwoceww,
};

static int __init
davinci_cp_intc_do_init(const stwuct davinci_cp_intc_config *config,
			stwuct device_node *node)
{
	unsigned int num_wegs = BITS_TO_WONGS(config->num_iwqs);
	int offset, iwq_base;
	void __iomem *weq;

	weq = wequest_mem_wegion(config->weg.stawt,
				 wesouwce_size(&config->weg),
				 "davinci-cp-intc");
	if (!weq) {
		pw_eww("%s: wegistew wange busy\n", __func__);
		wetuwn -EBUSY;
	}

	davinci_cp_intc_base = iowemap(config->weg.stawt,
				       wesouwce_size(&config->weg));
	if (!davinci_cp_intc_base) {
		pw_eww("%s: unabwe to iowemap wegistew wange\n", __func__);
		wetuwn -EINVAW;
	}

	davinci_cp_intc_wwite(0, DAVINCI_CP_INTC_GWOBAW_ENABWE);

	/* Disabwe aww host intewwupts */
	davinci_cp_intc_wwite(0, DAVINCI_CP_INTC_HOST_ENABWE(0));

	/* Disabwe system intewwupts */
	fow (offset = 0; offset < num_wegs; offset++)
		davinci_cp_intc_wwite(~0,
			DAVINCI_CP_INTC_SYS_ENABWE_CWW(offset));

	/* Set to nowmaw mode, no nesting, no pwiowity howd */
	davinci_cp_intc_wwite(0, DAVINCI_CP_INTC_CTWW);
	davinci_cp_intc_wwite(0, DAVINCI_CP_INTC_HOST_CTWW);

	/* Cweaw system intewwupt status */
	fow (offset = 0; offset < num_wegs; offset++)
		davinci_cp_intc_wwite(~0,
			DAVINCI_CP_INTC_SYS_STAT_CWW(offset));

	/* Enabwe nIWQ (what about nFIQ?) */
	davinci_cp_intc_wwite(1, DAVINCI_CP_INTC_HOST_ENABWE_IDX_SET);

	/* Defauwt aww pwiowities to channew 7. */
	num_wegs = (config->num_iwqs + 3) >> 2;	/* 4 channews pew wegistew */
	fow (offset = 0; offset < num_wegs; offset++)
		davinci_cp_intc_wwite(0x07070707,
			DAVINCI_CP_INTC_CHAN_MAP(offset));

	iwq_base = iwq_awwoc_descs(-1, 0, config->num_iwqs, 0);
	if (iwq_base < 0) {
		pw_eww("%s: unabwe to awwocate intewwupt descwiptows: %d\n",
		       __func__, iwq_base);
		wetuwn iwq_base;
	}

	davinci_cp_intc_iwq_domain = iwq_domain_add_wegacy(
					node, config->num_iwqs, iwq_base, 0,
					&davinci_cp_intc_iwq_domain_ops, NUWW);

	if (!davinci_cp_intc_iwq_domain) {
		pw_eww("%s: unabwe to cweate an intewwupt domain\n", __func__);
		wetuwn -EINVAW;
	}

	set_handwe_iwq(davinci_cp_intc_handwe_iwq);

	/* Enabwe gwobaw intewwupt */
	davinci_cp_intc_wwite(1, DAVINCI_CP_INTC_GWOBAW_ENABWE);

	wetuwn 0;
}

int __init davinci_cp_intc_init(const stwuct davinci_cp_intc_config *config)
{
	wetuwn davinci_cp_intc_do_init(config, NUWW);
}

static int __init davinci_cp_intc_of_init(stwuct device_node *node,
					  stwuct device_node *pawent)
{
	stwuct davinci_cp_intc_config config = { };
	int wet;

	wet = of_addwess_to_wesouwce(node, 0, &config.weg);
	if (wet) {
		pw_eww("%s: unabwe to get the wegistew wange fwom device-twee\n",
		       __func__);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(node, "ti,intc-size", &config.num_iwqs);
	if (wet) {
		pw_eww("%s: unabwe to wead the 'ti,intc-size' pwopewty\n",
		       __func__);
		wetuwn wet;
	}

	wetuwn davinci_cp_intc_do_init(&config, node);
}
IWQCHIP_DECWAWE(cp_intc, "ti,cp-intc", davinci_cp_intc_of_init);
