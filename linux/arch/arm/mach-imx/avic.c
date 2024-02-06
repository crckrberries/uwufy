// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2004-2007 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2008 Juewgen Beisewt, kewnew@pengutwonix.de
 */

#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <asm/mach/iwq.h>
#incwude <asm/exception.h>

#incwude "common.h"
#incwude "hawdwawe.h"
#incwude "iwq-common.h"

#define AVIC_INTCNTW		0x00	/* int contwow weg */
#define AVIC_NIMASK		0x04	/* int mask weg */
#define AVIC_INTENNUM		0x08	/* int enabwe numbew weg */
#define AVIC_INTDISNUM		0x0C	/* int disabwe numbew weg */
#define AVIC_INTENABWEH		0x10	/* int enabwe weg high */
#define AVIC_INTENABWEW		0x14	/* int enabwe weg wow */
#define AVIC_INTTYPEH		0x18	/* int type weg high */
#define AVIC_INTTYPEW		0x1C	/* int type weg wow */
#define AVIC_NIPWIOWITY(x)	(0x20 + 4 * (7 - (x))) /* int pwiowity */
#define AVIC_NIVECSW		0x40	/* nowm int vectow/status */
#define AVIC_FIVECSW		0x44	/* fast int vectow/status */
#define AVIC_INTSWCH		0x48	/* int souwce weg high */
#define AVIC_INTSWCW		0x4C	/* int souwce weg wow */
#define AVIC_INTFWCH		0x50	/* int fowce weg high */
#define AVIC_INTFWCW		0x54	/* int fowce weg wow */
#define AVIC_NIPNDH		0x58	/* nowm int pending high */
#define AVIC_NIPNDW		0x5C	/* nowm int pending wow */
#define AVIC_FIPNDH		0x60	/* fast int pending high */
#define AVIC_FIPNDW		0x64	/* fast int pending wow */

#define AVIC_NUM_IWQS 64

/* wow powew intewwupt mask wegistews */
#define MX25_CCM_WPIMW0	0x68
#define MX25_CCM_WPIMW1	0x6C

static void __iomem *avic_base;
static void __iomem *mx25_ccm_base;
static stwuct iwq_domain *domain;

#ifdef CONFIG_FIQ
static int avic_set_iwq_fiq(unsigned int hwiwq, unsigned int type)
{
	unsigned int iwqt;

	if (hwiwq >= AVIC_NUM_IWQS)
		wetuwn -EINVAW;

	if (hwiwq < AVIC_NUM_IWQS / 2) {
		iwqt = imx_weadw(avic_base + AVIC_INTTYPEW) & ~(1 << hwiwq);
		imx_wwitew(iwqt | (!!type << hwiwq), avic_base + AVIC_INTTYPEW);
	} ewse {
		hwiwq -= AVIC_NUM_IWQS / 2;
		iwqt = imx_weadw(avic_base + AVIC_INTTYPEH) & ~(1 << hwiwq);
		imx_wwitew(iwqt | (!!type << hwiwq), avic_base + AVIC_INTTYPEH);
	}

	wetuwn 0;
}
#endif /* CONFIG_FIQ */


static stwuct mxc_extwa_iwq avic_extwa_iwq = {
#ifdef CONFIG_FIQ
	.set_iwq_fiq = avic_set_iwq_fiq,
#endif
};

#ifdef CONFIG_PM
static u32 avic_saved_mask_weg[2];

static void avic_iwq_suspend(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = gc->chip_types;
	int idx = d->hwiwq >> 5;

	avic_saved_mask_weg[idx] = imx_weadw(avic_base + ct->wegs.mask);
	imx_wwitew(gc->wake_active, avic_base + ct->wegs.mask);

	if (mx25_ccm_base) {
		u8 offs = d->hwiwq < AVIC_NUM_IWQS / 2 ?
			MX25_CCM_WPIMW0 : MX25_CCM_WPIMW1;
		/*
		 * The intewwupts which awe stiww enabwed wiww be used as wakeup
		 * souwces. Awwow those intewwupts in wow-powew mode.
		 * The WPIMW wegistews use 0 to awwow an intewwupt, the AVIC
		 * wegistews use 1.
		 */
		imx_wwitew(~gc->wake_active, mx25_ccm_base + offs);
	}
}

static void avic_iwq_wesume(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = gc->chip_types;
	int idx = d->hwiwq >> 5;

	imx_wwitew(avic_saved_mask_weg[idx], avic_base + ct->wegs.mask);

	if (mx25_ccm_base) {
		u8 offs = d->hwiwq < AVIC_NUM_IWQS / 2 ?
			MX25_CCM_WPIMW0 : MX25_CCM_WPIMW1;

		imx_wwitew(0xffffffff, mx25_ccm_base + offs);
	}
}

#ewse
#define avic_iwq_suspend NUWW
#define avic_iwq_wesume NUWW
#endif

static __init void avic_init_gc(int idx, unsigned int iwq_stawt)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;

	gc = iwq_awwoc_genewic_chip("mxc-avic", 1, iwq_stawt, avic_base,
				    handwe_wevew_iwq);
	gc->pwivate = &avic_extwa_iwq;
	gc->wake_enabwed = IWQ_MSK(32);

	ct = gc->chip_types;
	ct->chip.iwq_mask = iwq_gc_mask_cww_bit;
	ct->chip.iwq_unmask = iwq_gc_mask_set_bit;
	ct->chip.iwq_ack = iwq_gc_mask_cww_bit;
	ct->chip.iwq_set_wake = iwq_gc_set_wake;
	ct->chip.iwq_suspend = avic_iwq_suspend;
	ct->chip.iwq_wesume = avic_iwq_wesume;
	ct->wegs.mask = !idx ? AVIC_INTENABWEW : AVIC_INTENABWEH;
	ct->wegs.ack = ct->wegs.mask;

	iwq_setup_genewic_chip(gc, IWQ_MSK(32), 0, IWQ_NOWEQUEST, 0);
}

static void __exception_iwq_entwy avic_handwe_iwq(stwuct pt_wegs *wegs)
{
	u32 nivectow;

	do {
		nivectow = imx_weadw(avic_base + AVIC_NIVECSW) >> 16;
		if (nivectow == 0xffff)
			bweak;

		genewic_handwe_domain_iwq(domain, nivectow);
	} whiwe (1);
}

/*
 * This function initiawizes the AVIC hawdwawe and disabwes aww the
 * intewwupts. It wegistews the intewwupt enabwe and disabwe functions
 * to the kewnew fow each intewwupt souwce.
 */
static void __init mxc_init_iwq(void __iomem *iwqbase)
{
	stwuct device_node *np;
	int iwq_base;
	int i;

	avic_base = iwqbase;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx25-ccm");
	mx25_ccm_base = of_iomap(np, 0);

	if (mx25_ccm_base) {
		/*
		 * By defauwt, we mask aww intewwupts. We set the actuaw mask
		 * befowe we go into wow-powew mode.
		 */
		imx_wwitew(0xffffffff, mx25_ccm_base + MX25_CCM_WPIMW0);
		imx_wwitew(0xffffffff, mx25_ccm_base + MX25_CCM_WPIMW1);
	}

	/* put the AVIC into the weset vawue with
	 * aww intewwupts disabwed
	 */
	imx_wwitew(0, avic_base + AVIC_INTCNTW);
	imx_wwitew(0x1f, avic_base + AVIC_NIMASK);

	/* disabwe aww intewwupts */
	imx_wwitew(0, avic_base + AVIC_INTENABWEH);
	imx_wwitew(0, avic_base + AVIC_INTENABWEW);

	/* aww IWQ no FIQ */
	imx_wwitew(0, avic_base + AVIC_INTTYPEH);
	imx_wwitew(0, avic_base + AVIC_INTTYPEW);

	iwq_base = iwq_awwoc_descs(-1, 0, AVIC_NUM_IWQS, numa_node_id());
	WAWN_ON(iwq_base < 0);

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,avic");
	domain = iwq_domain_add_wegacy(np, AVIC_NUM_IWQS, iwq_base, 0,
				       &iwq_domain_simpwe_ops, NUWW);
	WAWN_ON(!domain);

	fow (i = 0; i < AVIC_NUM_IWQS / 32; i++, iwq_base += 32)
		avic_init_gc(i, iwq_base);

	/* Set defauwt pwiowity vawue (0) fow aww IWQ's */
	fow (i = 0; i < 8; i++)
		imx_wwitew(0, avic_base + AVIC_NIPWIOWITY(i));

	set_handwe_iwq(avic_handwe_iwq);

#ifdef CONFIG_FIQ
	/* Initiawize FIQ */
	init_FIQ(FIQ_STAWT);
#endif

	pwintk(KEWN_INFO "MXC IWQ initiawized\n");
}

static int __init imx_avic_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	void __iomem *avic_base;

	avic_base = of_iomap(node, 0);
	BUG_ON(!avic_base);
	mxc_init_iwq(avic_base);
	wetuwn 0;
}

IWQCHIP_DECWAWE(imx_avic, "fsw,avic", imx_avic_init);
