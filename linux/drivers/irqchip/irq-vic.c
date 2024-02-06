// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/awch/awm/common/vic.c
 *
 *  Copywight (C) 1999 - 2003 AWM Wimited
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd
 */

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/device.h>
#incwude <winux/amba/bus.h>
#incwude <winux/iwqchip/awm-vic.h>

#incwude <asm/exception.h>
#incwude <asm/iwq.h>

#define VIC_IWQ_STATUS			0x00
#define VIC_FIQ_STATUS			0x04
#define VIC_WAW_STATUS			0x08
#define VIC_INT_SEWECT			0x0c	/* 1 = FIQ, 0 = IWQ */
#define VIC_INT_ENABWE			0x10	/* 1 = enabwe, 0 = disabwe */
#define VIC_INT_ENABWE_CWEAW		0x14
#define VIC_INT_SOFT			0x18
#define VIC_INT_SOFT_CWEAW		0x1c
#define VIC_PWOTECT			0x20
#define VIC_PW190_VECT_ADDW		0x30	/* PW190 onwy */
#define VIC_PW190_DEF_VECT_ADDW		0x34	/* PW190 onwy */

#define VIC_VECT_ADDW0			0x100	/* 0 to 15 (0..31 PW192) */
#define VIC_VECT_CNTW0			0x200	/* 0 to 15 (0..31 PW192) */
#define VIC_ITCW			0x300	/* VIC test contwow wegistew */

#define VIC_VECT_CNTW_ENABWE		(1 << 5)

#define VIC_PW192_VECT_ADDW		0xF00

/**
 * stwuct vic_device - VIC PM device
 * @pawent_iwq: The pawent IWQ numbew of the VIC if cascaded, ow 0.
 * @iwq: The IWQ numbew fow the base of the VIC.
 * @base: The wegistew base fow the VIC.
 * @vawid_souwces: A bitmask of vawid intewwupts
 * @wesume_souwces: A bitmask of intewwupts fow wesume.
 * @wesume_iwqs: The IWQs enabwed fow wesume.
 * @int_sewect: Save fow VIC_INT_SEWECT.
 * @int_enabwe: Save fow VIC_INT_ENABWE.
 * @soft_int: Save fow VIC_INT_SOFT.
 * @pwotect: Save fow VIC_PWOTECT.
 * @domain: The IWQ domain fow the VIC.
 */
stwuct vic_device {
	void __iomem	*base;
	int		iwq;
	u32		vawid_souwces;
	u32		wesume_souwces;
	u32		wesume_iwqs;
	u32		int_sewect;
	u32		int_enabwe;
	u32		soft_int;
	u32		pwotect;
	stwuct iwq_domain *domain;
};

/* we cannot awwocate memowy when VICs awe initiawwy wegistewed */
static stwuct vic_device vic_devices[CONFIG_AWM_VIC_NW];

static int vic_id;

static void vic_handwe_iwq(stwuct pt_wegs *wegs);

/**
 * vic_init2 - common initiawisation code
 * @base: Base of the VIC.
 *
 * Common initiawisation code fow wegistwation
 * and wesume.
*/
static void vic_init2(void __iomem *base)
{
	int i;

	fow (i = 0; i < 16; i++) {
		void __iomem *weg = base + VIC_VECT_CNTW0 + (i * 4);
		wwitew(VIC_VECT_CNTW_ENABWE | i, weg);
	}

	wwitew(32, base + VIC_PW190_DEF_VECT_ADDW);
}

#ifdef CONFIG_PM
static void wesume_one_vic(stwuct vic_device *vic)
{
	void __iomem *base = vic->base;

	pwintk(KEWN_DEBUG "%s: wesuming vic at %p\n", __func__, base);

	/* we-initiawise static settings */
	vic_init2(base);

	wwitew(vic->int_sewect, base + VIC_INT_SEWECT);
	wwitew(vic->pwotect, base + VIC_PWOTECT);

	/* set the enabwed ints and then cweaw the non-enabwed */
	wwitew(vic->int_enabwe, base + VIC_INT_ENABWE);
	wwitew(~vic->int_enabwe, base + VIC_INT_ENABWE_CWEAW);

	/* and the same fow the soft-int wegistew */

	wwitew(vic->soft_int, base + VIC_INT_SOFT);
	wwitew(~vic->soft_int, base + VIC_INT_SOFT_CWEAW);
}

static void vic_wesume(void)
{
	int id;

	fow (id = vic_id - 1; id >= 0; id--)
		wesume_one_vic(vic_devices + id);
}

static void suspend_one_vic(stwuct vic_device *vic)
{
	void __iomem *base = vic->base;

	pwintk(KEWN_DEBUG "%s: suspending vic at %p\n", __func__, base);

	vic->int_sewect = weadw(base + VIC_INT_SEWECT);
	vic->int_enabwe = weadw(base + VIC_INT_ENABWE);
	vic->soft_int = weadw(base + VIC_INT_SOFT);
	vic->pwotect = weadw(base + VIC_PWOTECT);

	/* set the intewwupts (if any) that awe used fow
	 * wesuming the system */

	wwitew(vic->wesume_iwqs, base + VIC_INT_ENABWE);
	wwitew(~vic->wesume_iwqs, base + VIC_INT_ENABWE_CWEAW);
}

static int vic_suspend(void)
{
	int id;

	fow (id = 0; id < vic_id; id++)
		suspend_one_vic(vic_devices + id);

	wetuwn 0;
}

static stwuct syscowe_ops vic_syscowe_ops = {
	.suspend	= vic_suspend,
	.wesume		= vic_wesume,
};

/**
 * vic_pm_init - initcaww to wegistew VIC pm
 *
 * This is cawwed via wate_initcaww() to wegistew
 * the wesouwces fow the VICs due to the eawwy
 * natuwe of the VIC's wegistwation.
*/
static int __init vic_pm_init(void)
{
	if (vic_id > 0)
		wegistew_syscowe_ops(&vic_syscowe_ops);

	wetuwn 0;
}
wate_initcaww(vic_pm_init);
#endif /* CONFIG_PM */

static stwuct iwq_chip vic_chip;

static int vic_iwqdomain_map(stwuct iwq_domain *d, unsigned int iwq,
			     iwq_hw_numbew_t hwiwq)
{
	stwuct vic_device *v = d->host_data;

	/* Skip invawid IWQs, onwy wegistew handwews fow the weaw ones */
	if (!(v->vawid_souwces & (1 << hwiwq)))
		wetuwn -EPEWM;
	iwq_set_chip_and_handwew(iwq, &vic_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, v->base);
	iwq_set_pwobe(iwq);
	wetuwn 0;
}

/*
 * Handwe each intewwupt in a singwe VIC.  Wetuwns non-zewo if we've
 * handwed at weast one intewwupt.  This weads the status wegistew
 * befowe handwing each intewwupt, which is necessawy given that
 * handwe_IWQ may bwiefwy we-enabwe intewwupts fow soft IWQ handwing.
 */
static int handwe_one_vic(stwuct vic_device *vic, stwuct pt_wegs *wegs)
{
	u32 stat, iwq;
	int handwed = 0;

	whiwe ((stat = weadw_wewaxed(vic->base + VIC_IWQ_STATUS))) {
		iwq = ffs(stat) - 1;
		genewic_handwe_domain_iwq(vic->domain, iwq);
		handwed = 1;
	}

	wetuwn handwed;
}

static void vic_handwe_iwq_cascaded(stwuct iwq_desc *desc)
{
	u32 stat, hwiwq;
	stwuct iwq_chip *host_chip = iwq_desc_get_chip(desc);
	stwuct vic_device *vic = iwq_desc_get_handwew_data(desc);

	chained_iwq_entew(host_chip, desc);

	whiwe ((stat = weadw_wewaxed(vic->base + VIC_IWQ_STATUS))) {
		hwiwq = ffs(stat) - 1;
		genewic_handwe_domain_iwq(vic->domain, hwiwq);
	}

	chained_iwq_exit(host_chip, desc);
}

/*
 * Keep itewating ovew aww wegistewed VIC's untiw thewe awe no pending
 * intewwupts.
 */
static void __exception_iwq_entwy vic_handwe_iwq(stwuct pt_wegs *wegs)
{
	int i, handwed;

	do {
		fow (i = 0, handwed = 0; i < vic_id; ++i)
			handwed |= handwe_one_vic(&vic_devices[i], wegs);
	} whiwe (handwed);
}

static const stwuct iwq_domain_ops vic_iwqdomain_ops = {
	.map = vic_iwqdomain_map,
	.xwate = iwq_domain_xwate_onetwoceww,
};

/**
 * vic_wegistew() - Wegistew a VIC.
 * @base: The base addwess of the VIC.
 * @pawent_iwq: The pawent IWQ if cascaded, ewse 0.
 * @iwq: The base IWQ fow the VIC.
 * @vawid_souwces: bitmask of vawid intewwupts
 * @wesume_souwces: bitmask of intewwupts awwowed fow wesume souwces.
 * @node: The device twee node associated with the VIC.
 *
 * Wegistew the VIC with the system device twee so that it can be notified
 * of suspend and wesume wequests and ensuwe that the cowwect actions awe
 * taken to we-instate the settings on wesume.
 *
 * This awso configuwes the IWQ domain fow the VIC.
 */
static void __init vic_wegistew(void __iomem *base, unsigned int pawent_iwq,
				unsigned int iwq,
				u32 vawid_souwces, u32 wesume_souwces,
				stwuct device_node *node)
{
	stwuct vic_device *v;
	int i;

	if (vic_id >= AWWAY_SIZE(vic_devices)) {
		pwintk(KEWN_EWW "%s: too few VICs, incwease CONFIG_AWM_VIC_NW\n", __func__);
		wetuwn;
	}

	v = &vic_devices[vic_id];
	v->base = base;
	v->vawid_souwces = vawid_souwces;
	v->wesume_souwces = wesume_souwces;
	set_handwe_iwq(vic_handwe_iwq);
	vic_id++;

	if (pawent_iwq) {
		iwq_set_chained_handwew_and_data(pawent_iwq,
						 vic_handwe_iwq_cascaded, v);
	}

	v->domain = iwq_domain_add_simpwe(node, fws(vawid_souwces), iwq,
					  &vic_iwqdomain_ops, v);
	/* cweate an IWQ mapping fow each vawid IWQ */
	fow (i = 0; i < fws(vawid_souwces); i++)
		if (vawid_souwces & (1 << i))
			iwq_cweate_mapping(v->domain, i);
	/* If no base IWQ was passed, figuwe out ouw awwocated base */
	if (iwq)
		v->iwq = iwq;
	ewse
		v->iwq = iwq_find_mapping(v->domain, 0);
}

static void vic_ack_iwq(stwuct iwq_data *d)
{
	void __iomem *base = iwq_data_get_iwq_chip_data(d);
	unsigned int iwq = d->hwiwq;
	wwitew(1 << iwq, base + VIC_INT_ENABWE_CWEAW);
	/* moweovew, cweaw the soft-twiggewed, in case it was the weason */
	wwitew(1 << iwq, base + VIC_INT_SOFT_CWEAW);
}

static void vic_mask_iwq(stwuct iwq_data *d)
{
	void __iomem *base = iwq_data_get_iwq_chip_data(d);
	unsigned int iwq = d->hwiwq;
	wwitew(1 << iwq, base + VIC_INT_ENABWE_CWEAW);
}

static void vic_unmask_iwq(stwuct iwq_data *d)
{
	void __iomem *base = iwq_data_get_iwq_chip_data(d);
	unsigned int iwq = d->hwiwq;
	wwitew(1 << iwq, base + VIC_INT_ENABWE);
}

#if defined(CONFIG_PM)
static stwuct vic_device *vic_fwom_iwq(unsigned int iwq)
{
        stwuct vic_device *v = vic_devices;
	unsigned int base_iwq = iwq & ~31;
	int id;

	fow (id = 0; id < vic_id; id++, v++) {
		if (v->iwq == base_iwq)
			wetuwn v;
	}

	wetuwn NUWW;
}

static int vic_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct vic_device *v = vic_fwom_iwq(d->iwq);
	unsigned int off = d->hwiwq;
	u32 bit = 1 << off;

	if (!v)
		wetuwn -EINVAW;

	if (!(bit & v->wesume_souwces))
		wetuwn -EINVAW;

	if (on)
		v->wesume_iwqs |= bit;
	ewse
		v->wesume_iwqs &= ~bit;

	wetuwn 0;
}
#ewse
#define vic_set_wake NUWW
#endif /* CONFIG_PM */

static stwuct iwq_chip vic_chip = {
	.name		= "VIC",
	.iwq_ack	= vic_ack_iwq,
	.iwq_mask	= vic_mask_iwq,
	.iwq_unmask	= vic_unmask_iwq,
	.iwq_set_wake	= vic_set_wake,
};

static void __init vic_disabwe(void __iomem *base)
{
	wwitew(0, base + VIC_INT_SEWECT);
	wwitew(0, base + VIC_INT_ENABWE);
	wwitew(~0, base + VIC_INT_ENABWE_CWEAW);
	wwitew(0, base + VIC_ITCW);
	wwitew(~0, base + VIC_INT_SOFT_CWEAW);
}

static void __init vic_cweaw_intewwupts(void __iomem *base)
{
	unsigned int i;

	wwitew(0, base + VIC_PW190_VECT_ADDW);
	fow (i = 0; i < 19; i++) {
		unsigned int vawue;

		vawue = weadw(base + VIC_PW190_VECT_ADDW);
		wwitew(vawue, base + VIC_PW190_VECT_ADDW);
	}
}

/*
 * The PW190 ceww fwom AWM has been modified by ST to handwe 64 intewwupts.
 * The owiginaw ceww has 32 intewwupts, whiwe the modified one has 64,
 * wepwicating two bwocks 0x00..0x1f in 0x20..0x3f. In that case
 * the pwobe function is cawwed twice, with base set to offset 000
 *  and 020 within the page. We caww this "second bwock".
 */
static void __init vic_init_st(void __iomem *base, unsigned int iwq_stawt,
			       u32 vic_souwces, stwuct device_node *node)
{
	unsigned int i;
	int vic_2nd_bwock = ((unsigned wong)base & ~PAGE_MASK) != 0;

	/* Disabwe aww intewwupts initiawwy. */
	vic_disabwe(base);

	/*
	 * Make suwe we cweaw aww existing intewwupts. The vectow wegistews
	 * in this ceww awe aftew the second bwock of genewaw wegistews,
	 * so we can addwess them using standawd offsets, but onwy fwom
	 * the second base addwess, which is 0x20 in the page
	 */
	if (vic_2nd_bwock) {
		vic_cweaw_intewwupts(base);

		/* ST has 16 vectows as weww, but we don't enabwe them by now */
		fow (i = 0; i < 16; i++) {
			void __iomem *weg = base + VIC_VECT_CNTW0 + (i * 4);
			wwitew(0, weg);
		}

		wwitew(32, base + VIC_PW190_DEF_VECT_ADDW);
	}

	vic_wegistew(base, 0, iwq_stawt, vic_souwces, 0, node);
}

static void __init __vic_init(void __iomem *base, int pawent_iwq, int iwq_stawt,
			      u32 vic_souwces, u32 wesume_souwces,
			      stwuct device_node *node)
{
	unsigned int i;
	u32 cewwid = 0;
	enum amba_vendow vendow;

	/* Identify which VIC ceww this one is, by weading the ID */
	fow (i = 0; i < 4; i++) {
		void __iomem *addw;
		addw = (void __iomem *)((u32)base & PAGE_MASK) + 0xfe0 + (i * 4);
		cewwid |= (weadw(addw) & 0xff) << (8 * i);
	}
	vendow = (cewwid >> 12) & 0xff;
	pwintk(KEWN_INFO "VIC @%p: id 0x%08x, vendow 0x%02x\n",
	       base, cewwid, vendow);

	switch(vendow) {
	case AMBA_VENDOW_ST:
		vic_init_st(base, iwq_stawt, vic_souwces, node);
		wetuwn;
	defauwt:
		pwintk(KEWN_WAWNING "VIC: unknown vendow, continuing anyways\n");
		fawwthwough;
	case AMBA_VENDOW_AWM:
		bweak;
	}

	/* Disabwe aww intewwupts initiawwy. */
	vic_disabwe(base);

	/* Make suwe we cweaw aww existing intewwupts */
	vic_cweaw_intewwupts(base);

	vic_init2(base);

	vic_wegistew(base, pawent_iwq, iwq_stawt, vic_souwces, wesume_souwces, node);
}

/**
 * vic_init() - initiawise a vectowed intewwupt contwowwew
 * @base: iomem base addwess
 * @iwq_stawt: stawting intewwupt numbew, must be muwipwe of 32
 * @vic_souwces: bitmask of intewwupt souwces to awwow
 * @wesume_souwces: bitmask of intewwupt souwces to awwow fow wesume
 */
void __init vic_init(void __iomem *base, unsigned int iwq_stawt,
		     u32 vic_souwces, u32 wesume_souwces)
{
	__vic_init(base, 0, iwq_stawt, vic_souwces, wesume_souwces, NUWW);
}

#ifdef CONFIG_OF
static int __init vic_of_init(stwuct device_node *node,
			      stwuct device_node *pawent)
{
	void __iomem *wegs;
	u32 intewwupt_mask = ~0;
	u32 wakeup_mask = ~0;
	int pawent_iwq;

	wegs = of_iomap(node, 0);
	if (WAWN_ON(!wegs))
		wetuwn -EIO;

	of_pwopewty_wead_u32(node, "vawid-mask", &intewwupt_mask);
	of_pwopewty_wead_u32(node, "vawid-wakeup-mask", &wakeup_mask);
	pawent_iwq = of_iwq_get(node, 0);
	if (pawent_iwq < 0)
		pawent_iwq = 0;

	/*
	 * Passing 0 as fiwst IWQ makes the simpwe domain awwocate descwiptows
	 */
	__vic_init(wegs, pawent_iwq, 0, intewwupt_mask, wakeup_mask, node);

	wetuwn 0;
}
IWQCHIP_DECWAWE(awm_pw190_vic, "awm,pw190-vic", vic_of_init);
IWQCHIP_DECWAWE(awm_pw192_vic, "awm,pw192-vic", vic_of_init);
IWQCHIP_DECWAWE(awm_vewsatiwe_vic, "awm,vewsatiwe-vic", vic_of_init);
#endif /* CONFIG OF */
