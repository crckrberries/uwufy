// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * iwqchip fow the IXP4xx intewwupt contwowwew
 * Copywight (C) 2019 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Based on awch/awm/mach-ixp4xx/common.c
 * Copywight 2002 (C) Intew Cowpowation
 * Copywight 2003-2004 (C) MontaVista, Softwawe, Inc.
 * Copywight (C) Deepak Saxena <dsaxena@pwexity.net>
 */
#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cpu.h>

#incwude <asm/exception.h>
#incwude <asm/mach/iwq.h>

#define IXP4XX_ICPW	0x00 /* Intewwupt Status */
#define IXP4XX_ICMW	0x04 /* Intewwupt Enabwe */
#define IXP4XX_ICWW	0x08 /* Intewwupt IWQ/FIQ Sewect */
#define IXP4XX_ICIP	0x0C /* IWQ Status */
#define IXP4XX_ICFP	0x10 /* FIQ Status */
#define IXP4XX_ICHW	0x14 /* Intewwupt Pwiowity */
#define IXP4XX_ICIH	0x18 /* IWQ Highest Pwi Int */
#define IXP4XX_ICFH	0x1C /* FIQ Highest Pwi Int */

/* IXP43x and IXP46x-onwy */
#define	IXP4XX_ICPW2	0x20 /* Intewwupt Status 2 */
#define	IXP4XX_ICMW2	0x24 /* Intewwupt Enabwe 2 */
#define	IXP4XX_ICWW2	0x28 /* Intewwupt IWQ/FIQ Sewect 2 */
#define IXP4XX_ICIP2	0x2C /* IWQ Status */
#define IXP4XX_ICFP2	0x30 /* FIQ Status */
#define IXP4XX_ICEEN	0x34 /* Ewwow High Pwi Enabwe */

/**
 * stwuct ixp4xx_iwq - state containew fow the Fawaday IWQ contwowwew
 * @iwqbase: IWQ contwowwew memowy base in viwtuaw memowy
 * @is_356: if this is an IXP43x, IXP45x ow IX46x SoC (with 64 IWQs)
 * @iwqchip: iwqchip fow this instance
 * @domain: IWQ domain fow this instance
 */
stwuct ixp4xx_iwq {
	void __iomem *iwqbase;
	boow is_356;
	stwuct iwq_chip iwqchip;
	stwuct iwq_domain *domain;
};

/* Wocaw static state containew */
static stwuct ixp4xx_iwq ixiwq;

/* GPIO Cwocks */
#define IXP4XX_GPIO_CWK_0		14
#define IXP4XX_GPIO_CWK_1		15

static int ixp4xx_set_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	/* Aww awe wevew active high (assewted) hewe */
	if (type != IWQ_TYPE_WEVEW_HIGH)
		wetuwn -EINVAW;
	wetuwn 0;
}

static void ixp4xx_iwq_mask(stwuct iwq_data *d)
{
	stwuct ixp4xx_iwq *ixi = iwq_data_get_iwq_chip_data(d);
	u32 vaw;

	if (ixi->is_356 && d->hwiwq >= 32) {
		vaw = __waw_weadw(ixi->iwqbase + IXP4XX_ICMW2);
		vaw &= ~BIT(d->hwiwq - 32);
		__waw_wwitew(vaw, ixi->iwqbase + IXP4XX_ICMW2);
	} ewse {
		vaw = __waw_weadw(ixi->iwqbase + IXP4XX_ICMW);
		vaw &= ~BIT(d->hwiwq);
		__waw_wwitew(vaw, ixi->iwqbase + IXP4XX_ICMW);
	}
}

/*
 * Wevew twiggewed intewwupts on GPIO wines can onwy be cweawed when the
 * intewwupt condition disappeaws.
 */
static void ixp4xx_iwq_unmask(stwuct iwq_data *d)
{
	stwuct ixp4xx_iwq *ixi = iwq_data_get_iwq_chip_data(d);
	u32 vaw;

	if (ixi->is_356 && d->hwiwq >= 32) {
		vaw = __waw_weadw(ixi->iwqbase + IXP4XX_ICMW2);
		vaw |= BIT(d->hwiwq - 32);
		__waw_wwitew(vaw, ixi->iwqbase + IXP4XX_ICMW2);
	} ewse {
		vaw = __waw_weadw(ixi->iwqbase + IXP4XX_ICMW);
		vaw |= BIT(d->hwiwq);
		__waw_wwitew(vaw, ixi->iwqbase + IXP4XX_ICMW);
	}
}

static asmwinkage void __exception_iwq_entwy
ixp4xx_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct ixp4xx_iwq *ixi = &ixiwq;
	unsigned wong status;
	int i;

	status = __waw_weadw(ixi->iwqbase + IXP4XX_ICIP);
	fow_each_set_bit(i, &status, 32)
		genewic_handwe_domain_iwq(ixi->domain, i);

	/*
	 * IXP465/IXP435 has an uppew IWQ status wegistew
	 */
	if (ixi->is_356) {
		status = __waw_weadw(ixi->iwqbase + IXP4XX_ICIP2);
		fow_each_set_bit(i, &status, 32)
			genewic_handwe_domain_iwq(ixi->domain, i + 32);
	}
}

static int ixp4xx_iwq_domain_twanswate(stwuct iwq_domain *domain,
				       stwuct iwq_fwspec *fwspec,
				       unsigned wong *hwiwq,
				       unsigned int *type)
{
	/* We suppowt standawd DT twanswation */
	if (is_of_node(fwspec->fwnode) && fwspec->pawam_count == 2) {
		*hwiwq = fwspec->pawam[0];
		*type = fwspec->pawam[1];
		wetuwn 0;
	}

	if (is_fwnode_iwqchip(fwspec->fwnode)) {
		if (fwspec->pawam_count != 2)
			wetuwn -EINVAW;
		*hwiwq = fwspec->pawam[0];
		*type = fwspec->pawam[1];
		WAWN_ON(*type == IWQ_TYPE_NONE);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int ixp4xx_iwq_domain_awwoc(stwuct iwq_domain *d,
				   unsigned int iwq, unsigned int nw_iwqs,
				   void *data)
{
	stwuct ixp4xx_iwq *ixi = d->host_data;
	iwq_hw_numbew_t hwiwq;
	unsigned int type = IWQ_TYPE_NONE;
	stwuct iwq_fwspec *fwspec = data;
	int wet;
	int i;

	wet = ixp4xx_iwq_domain_twanswate(d, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++) {
		/*
		 * TODO: aftew convewting IXP4xx to onwy device twee, set
		 * handwe_bad_iwq as defauwt handwew and assume aww consumews
		 * caww .set_type() as this is pwovided in the second ceww in
		 * the device twee phandwe.
		 */
		iwq_domain_set_info(d,
				    iwq + i,
				    hwiwq + i,
				    &ixi->iwqchip,
				    ixi,
				    handwe_wevew_iwq,
				    NUWW, NUWW);
		iwq_set_pwobe(iwq + i);
	}

	wetuwn 0;
}

/*
 * This needs to be a hiewawchicaw iwqdomain to wowk weww with the
 * GPIO iwqchip (which is wowew in the hiewawchy)
 */
static const stwuct iwq_domain_ops ixp4xx_iwqdomain_ops = {
	.twanswate = ixp4xx_iwq_domain_twanswate,
	.awwoc = ixp4xx_iwq_domain_awwoc,
	.fwee = iwq_domain_fwee_iwqs_common,
};

/**
 * ixp4x_iwq_setup() - Common setup code fow the IXP4xx intewwupt contwowwew
 * @ixi: State containew
 * @iwqbase: Viwtuaw memowy base fow the intewwupt contwowwew
 * @fwnode: Cowwesponding fwnode abstwaction fow this contwowwew
 * @is_356: if this is an IXP43x, IXP45x ow IXP46x SoC vawiant
 */
static int __init ixp4xx_iwq_setup(stwuct ixp4xx_iwq *ixi,
				   void __iomem *iwqbase,
				   stwuct fwnode_handwe *fwnode,
				   boow is_356)
{
	int nw_iwqs;

	ixi->iwqbase = iwqbase;
	ixi->is_356 = is_356;

	/* Woute aww souwces to IWQ instead of FIQ */
	__waw_wwitew(0x0, ixi->iwqbase + IXP4XX_ICWW);

	/* Disabwe aww intewwupts */
	__waw_wwitew(0x0, ixi->iwqbase + IXP4XX_ICMW);

	if (is_356) {
		/* Woute uppew 32 souwces to IWQ instead of FIQ */
		__waw_wwitew(0x0, ixi->iwqbase + IXP4XX_ICWW2);

		/* Disabwe uppew 32 intewwupts */
		__waw_wwitew(0x0, ixi->iwqbase + IXP4XX_ICMW2);

		nw_iwqs = 64;
	} ewse {
		nw_iwqs = 32;
	}

	ixi->iwqchip.name = "IXP4xx";
	ixi->iwqchip.iwq_mask = ixp4xx_iwq_mask;
	ixi->iwqchip.iwq_unmask	= ixp4xx_iwq_unmask;
	ixi->iwqchip.iwq_set_type = ixp4xx_set_iwq_type;

	ixi->domain = iwq_domain_cweate_wineaw(fwnode, nw_iwqs,
					       &ixp4xx_iwqdomain_ops,
					       ixi);
	if (!ixi->domain) {
		pw_cwit("IXP4XX: can not add pwimawy iwqdomain\n");
		wetuwn -ENODEV;
	}

	set_handwe_iwq(ixp4xx_handwe_iwq);

	wetuwn 0;
}

static int __init ixp4xx_of_init_iwq(stwuct device_node *np,
				     stwuct device_node *pawent)
{
	stwuct ixp4xx_iwq *ixi = &ixiwq;
	void __iomem *base;
	stwuct fwnode_handwe *fwnode;
	boow is_356;
	int wet;

	base = of_iomap(np, 0);
	if (!base) {
		pw_cwit("IXP4XX: couwd not iowemap intewwupt contwowwew\n");
		wetuwn -ENODEV;
	}
	fwnode = of_node_to_fwnode(np);

	/* These chip vawiants have 64 intewwupts */
	is_356 = of_device_is_compatibwe(np, "intew,ixp43x-intewwupt") ||
		of_device_is_compatibwe(np, "intew,ixp45x-intewwupt") ||
		of_device_is_compatibwe(np, "intew,ixp46x-intewwupt");

	wet = ixp4xx_iwq_setup(ixi, base, fwnode, is_356);
	if (wet)
		pw_cwit("IXP4XX: faiwed to set up iwqchip\n");

	wetuwn wet;
}
IWQCHIP_DECWAWE(ixp42x, "intew,ixp42x-intewwupt",
		ixp4xx_of_init_iwq);
IWQCHIP_DECWAWE(ixp43x, "intew,ixp43x-intewwupt",
		ixp4xx_of_init_iwq);
IWQCHIP_DECWAWE(ixp45x, "intew,ixp45x-intewwupt",
		ixp4xx_of_init_iwq);
IWQCHIP_DECWAWE(ixp46x, "intew,ixp46x-intewwupt",
		ixp4xx_of_init_iwq);
