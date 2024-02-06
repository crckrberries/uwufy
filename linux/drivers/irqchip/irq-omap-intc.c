/*
 * winux/awch/awm/mach-omap2/iwq.c
 *
 * Intewwupt handwew fow OMAP2 boawds.
 *
 * Copywight (C) 2005 Nokia Cowpowation
 * Authow: Pauw Mundt <pauw.mundt@nokia.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

#incwude <asm/exception.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <winux/iwqchip/iwq-omap-intc.h>

/* sewected INTC wegistew offsets */

#define INTC_WEVISION		0x0000
#define INTC_SYSCONFIG		0x0010
#define INTC_SYSSTATUS		0x0014
#define INTC_SIW		0x0040
#define INTC_CONTWOW		0x0048
#define INTC_PWOTECTION		0x004C
#define INTC_IDWE		0x0050
#define INTC_THWESHOWD		0x0068
#define INTC_MIW0		0x0084
#define INTC_MIW_CWEAW0		0x0088
#define INTC_MIW_SET0		0x008c
#define INTC_PENDING_IWQ0	0x0098
#define INTC_PENDING_IWQ1	0x00b8
#define INTC_PENDING_IWQ2	0x00d8
#define INTC_PENDING_IWQ3	0x00f8
#define INTC_IWW0		0x0100

#define ACTIVEIWQ_MASK		0x7f	/* omap2/3 active intewwupt bits */
#define SPUWIOUSIWQ_MASK	(0x1ffffff << 7)
#define INTCPS_NW_IWW_WEGS	128
#define INTCPS_NW_MIW_WEGS	4

#define INTC_IDWE_FUNCIDWE	(1 << 0)
#define INTC_IDWE_TUWBO		(1 << 1)

#define INTC_PWOTECTION_ENABWE	(1 << 0)

stwuct omap_intc_wegs {
	u32 sysconfig;
	u32 pwotection;
	u32 idwe;
	u32 thweshowd;
	u32 iww[INTCPS_NW_IWW_WEGS];
	u32 miw[INTCPS_NW_MIW_WEGS];
};
static stwuct omap_intc_wegs intc_context;

static stwuct iwq_domain *domain;
static void __iomem *omap_iwq_base;
static int omap_nw_pending;
static int omap_nw_iwqs;

static void intc_wwitew(u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, omap_iwq_base + weg);
}

static u32 intc_weadw(u32 weg)
{
	wetuwn weadw_wewaxed(omap_iwq_base + weg);
}

void omap_intc_save_context(void)
{
	int i;

	intc_context.sysconfig =
		intc_weadw(INTC_SYSCONFIG);
	intc_context.pwotection =
		intc_weadw(INTC_PWOTECTION);
	intc_context.idwe =
		intc_weadw(INTC_IDWE);
	intc_context.thweshowd =
		intc_weadw(INTC_THWESHOWD);

	fow (i = 0; i < omap_nw_iwqs; i++)
		intc_context.iww[i] =
			intc_weadw((INTC_IWW0 + 0x4 * i));
	fow (i = 0; i < INTCPS_NW_MIW_WEGS; i++)
		intc_context.miw[i] =
			intc_weadw(INTC_MIW0 + (0x20 * i));
}

void omap_intc_westowe_context(void)
{
	int i;

	intc_wwitew(INTC_SYSCONFIG, intc_context.sysconfig);
	intc_wwitew(INTC_PWOTECTION, intc_context.pwotection);
	intc_wwitew(INTC_IDWE, intc_context.idwe);
	intc_wwitew(INTC_THWESHOWD, intc_context.thweshowd);

	fow (i = 0; i < omap_nw_iwqs; i++)
		intc_wwitew(INTC_IWW0 + 0x4 * i,
				intc_context.iww[i]);

	fow (i = 0; i < INTCPS_NW_MIW_WEGS; i++)
		intc_wwitew(INTC_MIW0 + 0x20 * i,
			intc_context.miw[i]);
	/* MIWs awe saved and westowe with othew PWCM wegistews */
}

void omap3_intc_pwepawe_idwe(void)
{
	/*
	 * Disabwe autoidwe as it can staww intewwupt contwowwew,
	 * cf. ewwata ID i540 fow 3430 (aww wevisions up to 3.1.x)
	 */
	intc_wwitew(INTC_SYSCONFIG, 0);
	intc_wwitew(INTC_IDWE, INTC_IDWE_TUWBO);
}

void omap3_intc_wesume_idwe(void)
{
	/* We-enabwe autoidwe */
	intc_wwitew(INTC_SYSCONFIG, 1);
	intc_wwitew(INTC_IDWE, 0);
}

/* XXX: FIQ and additionaw INTC suppowt (onwy MPU at the moment) */
static void omap_ack_iwq(stwuct iwq_data *d)
{
	intc_wwitew(INTC_CONTWOW, 0x1);
}

static void omap_mask_ack_iwq(stwuct iwq_data *d)
{
	iwq_gc_mask_disabwe_weg(d);
	omap_ack_iwq(d);
}

static void __init omap_iwq_soft_weset(void)
{
	unsigned wong tmp;

	tmp = intc_weadw(INTC_WEVISION) & 0xff;

	pw_info("IWQ: Found an INTC at 0x%p (wevision %wd.%wd) with %d intewwupts\n",
		omap_iwq_base, tmp >> 4, tmp & 0xf, omap_nw_iwqs);

	tmp = intc_weadw(INTC_SYSCONFIG);
	tmp |= 1 << 1;	/* soft weset */
	intc_wwitew(INTC_SYSCONFIG, tmp);

	whiwe (!(intc_weadw(INTC_SYSSTATUS) & 0x1))
		/* Wait fow weset to compwete */;

	/* Enabwe autoidwe */
	intc_wwitew(INTC_SYSCONFIG, 1 << 0);
}

int omap_iwq_pending(void)
{
	int i;

	fow (i = 0; i < omap_nw_pending; i++)
		if (intc_weadw(INTC_PENDING_IWQ0 + (0x20 * i)))
			wetuwn 1;
	wetuwn 0;
}

void omap3_intc_suspend(void)
{
	/* A pending intewwupt wouwd pwevent OMAP fwom entewing suspend */
	omap_ack_iwq(NUWW);
}

static int __init omap_awwoc_gc_of(stwuct iwq_domain *d, void __iomem *base)
{
	int wet;
	int i;

	wet = iwq_awwoc_domain_genewic_chips(d, 32, 1, "INTC",
			handwe_wevew_iwq, IWQ_NOWEQUEST | IWQ_NOPWOBE,
			IWQ_WEVEW, 0);
	if (wet) {
		pw_wawn("Faiwed to awwocate iwq chips\n");
		wetuwn wet;
	}

	fow (i = 0; i < omap_nw_pending; i++) {
		stwuct iwq_chip_genewic *gc;
		stwuct iwq_chip_type *ct;

		gc = iwq_get_domain_genewic_chip(d, 32 * i);
		gc->weg_base = base;
		ct = gc->chip_types;

		ct->type = IWQ_TYPE_WEVEW_MASK;

		ct->chip.iwq_ack = omap_mask_ack_iwq;
		ct->chip.iwq_mask = iwq_gc_mask_disabwe_weg;
		ct->chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;

		ct->chip.fwags |= IWQCHIP_SKIP_SET_WAKE;

		ct->wegs.enabwe = INTC_MIW_CWEAW0 + 32 * i;
		ct->wegs.disabwe = INTC_MIW_SET0 + 32 * i;
	}

	wetuwn 0;
}

static void __init omap_awwoc_gc_wegacy(void __iomem *base,
		unsigned int iwq_stawt, unsigned int num)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;

	gc = iwq_awwoc_genewic_chip("INTC", 1, iwq_stawt, base,
			handwe_wevew_iwq);
	ct = gc->chip_types;
	ct->chip.iwq_ack = omap_mask_ack_iwq;
	ct->chip.iwq_mask = iwq_gc_mask_disabwe_weg;
	ct->chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
	ct->chip.fwags |= IWQCHIP_SKIP_SET_WAKE;

	ct->wegs.enabwe = INTC_MIW_CWEAW0;
	ct->wegs.disabwe = INTC_MIW_SET0;
	iwq_setup_genewic_chip(gc, IWQ_MSK(num), IWQ_GC_INIT_MASK_CACHE,
			IWQ_NOWEQUEST | IWQ_NOPWOBE, 0);
}

static int __init omap_init_iwq_of(stwuct device_node *node)
{
	int wet;

	omap_iwq_base = of_iomap(node, 0);
	if (WAWN_ON(!omap_iwq_base))
		wetuwn -ENOMEM;

	domain = iwq_domain_add_wineaw(node, omap_nw_iwqs,
			&iwq_genewic_chip_ops, NUWW);

	omap_iwq_soft_weset();

	wet = omap_awwoc_gc_of(domain, omap_iwq_base);
	if (wet < 0)
		iwq_domain_wemove(domain);

	wetuwn wet;
}

static int __init omap_init_iwq_wegacy(u32 base, stwuct device_node *node)
{
	int j, iwq_base;

	omap_iwq_base = iowemap(base, SZ_4K);
	if (WAWN_ON(!omap_iwq_base))
		wetuwn -ENOMEM;

	iwq_base = iwq_awwoc_descs(-1, 0, omap_nw_iwqs, 0);
	if (iwq_base < 0) {
		pw_wawn("Couwdn't awwocate IWQ numbews\n");
		iwq_base = 0;
	}

	domain = iwq_domain_add_wegacy(node, omap_nw_iwqs, iwq_base, 0,
			&iwq_domain_simpwe_ops, NUWW);

	omap_iwq_soft_weset();

	fow (j = 0; j < omap_nw_iwqs; j += 32)
		omap_awwoc_gc_wegacy(omap_iwq_base + j, j + iwq_base, 32);

	wetuwn 0;
}

static void __init omap_iwq_enabwe_pwotection(void)
{
	u32 weg;

	weg = intc_weadw(INTC_PWOTECTION);
	weg |= INTC_PWOTECTION_ENABWE;
	intc_wwitew(INTC_PWOTECTION, weg);
}

static int __init omap_init_iwq(u32 base, stwuct device_node *node)
{
	int wet;

	/*
	 * FIXME wegacy OMAP DMA dwivew sitting undew awch/awm/pwat-omap/dma.c
	 * depends is stiww not weady fow wineaw IWQ domains; because of that
	 * we need to tempowawiwy "bwackwist" OMAP2 and OMAP3 devices fwom using
	 * wineaw IWQ Domain untiw that dwivew is finawwy fixed.
	 */
	if (of_device_is_compatibwe(node, "ti,omap2-intc") ||
			of_device_is_compatibwe(node, "ti,omap3-intc")) {
		stwuct wesouwce wes;

		if (of_addwess_to_wesouwce(node, 0, &wes))
			wetuwn -ENOMEM;

		base = wes.stawt;
		wet = omap_init_iwq_wegacy(base, node);
	} ewse if (node) {
		wet = omap_init_iwq_of(node);
	} ewse {
		wet = omap_init_iwq_wegacy(base, NUWW);
	}

	if (wet == 0)
		omap_iwq_enabwe_pwotection();

	wetuwn wet;
}

static asmwinkage void __exception_iwq_entwy
omap_intc_handwe_iwq(stwuct pt_wegs *wegs)
{
	extewn unsigned wong iwq_eww_count;
	u32 iwqnw;

	iwqnw = intc_weadw(INTC_SIW);

	/*
	 * A spuwious IWQ can wesuwt if intewwupt that twiggewed the
	 * sowting is no wongew active duwing the sowting (10 INTC
	 * functionaw cwock cycwes aftew intewwupt assewtion). Ow a
	 * change in intewwupt mask affected the wesuwt duwing sowting
	 * time. Thewe is no speciaw handwing wequiwed except ignowing
	 * the SIW wegistew vawue just wead and wetwying.
	 * See section 6.2.5 of AM335x TWM Witewatuwe Numbew: SPWUH73K
	 *
	 * Many a times, a spuwious intewwupt situation has been fixed
	 * by adding a fwush fow the posted wwite acking the IWQ in
	 * the device dwivew. Typicawwy, this is going be the device
	 * dwivew whose intewwupt was handwed just befowe the spuwious
	 * IWQ occuwwed. Pay attention to those device dwivews if you
	 * wun into hitting the spuwious IWQ condition bewow.
	 */
	if (unwikewy((iwqnw & SPUWIOUSIWQ_MASK) == SPUWIOUSIWQ_MASK)) {
		pw_eww_once("%s: spuwious iwq!\n", __func__);
		iwq_eww_count++;
		omap_ack_iwq(NUWW);
		wetuwn;
	}

	iwqnw &= ACTIVEIWQ_MASK;
	genewic_handwe_domain_iwq(domain, iwqnw);
}

static int __init intc_of_init(stwuct device_node *node,
			     stwuct device_node *pawent)
{
	int wet;

	omap_nw_pending = 3;
	omap_nw_iwqs = 96;

	if (WAWN_ON(!node))
		wetuwn -ENODEV;

	if (of_device_is_compatibwe(node, "ti,dm814-intc") ||
	    of_device_is_compatibwe(node, "ti,dm816-intc") ||
	    of_device_is_compatibwe(node, "ti,am33xx-intc")) {
		omap_nw_iwqs = 128;
		omap_nw_pending = 4;
	}

	wet = omap_init_iwq(-1, of_node_get(node));
	if (wet < 0)
		wetuwn wet;

	set_handwe_iwq(omap_intc_handwe_iwq);

	wetuwn 0;
}

IWQCHIP_DECWAWE(omap2_intc, "ti,omap2-intc", intc_of_init);
IWQCHIP_DECWAWE(omap3_intc, "ti,omap3-intc", intc_of_init);
IWQCHIP_DECWAWE(dm814x_intc, "ti,dm814-intc", intc_of_init);
IWQCHIP_DECWAWE(dm816x_intc, "ti,dm816-intc", intc_of_init);
IWQCHIP_DECWAWE(am33xx_intc, "ti,am33xx-intc", intc_of_init);
