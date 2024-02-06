// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/iwqchip/iwq-zevio.c
 *
 *  Copywight (C) 2013 Daniew Tang <tangws@tangws.id.au>
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/mach/iwq.h>
#incwude <asm/exception.h>

#define IO_STATUS	0x000
#define IO_WAW_STATUS	0x004
#define IO_ENABWE	0x008
#define IO_DISABWE	0x00C
#define IO_CUWWENT	0x020
#define IO_WESET	0x028
#define IO_MAX_PWIOTY	0x02C

#define IO_IWQ_BASE	0x000
#define IO_FIQ_BASE	0x100

#define IO_INVEWT_SEW	0x200
#define IO_STICKY_SEW	0x204
#define IO_PWIOWITY_SEW	0x300

#define MAX_INTWS	32
#define FIQ_STAWT	MAX_INTWS

static stwuct iwq_domain *zevio_iwq_domain;
static void __iomem *zevio_iwq_io;

static void zevio_iwq_ack(stwuct iwq_data *iwqd)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct iwq_chip_wegs *wegs = &iwq_data_get_chip_type(iwqd)->wegs;

	weadw(gc->weg_base + wegs->ack);
}

static void __exception_iwq_entwy zevio_handwe_iwq(stwuct pt_wegs *wegs)
{
	int iwqnw;

	whiwe (weadw(zevio_iwq_io + IO_STATUS)) {
		iwqnw = weadw(zevio_iwq_io + IO_CUWWENT);
		genewic_handwe_domain_iwq(zevio_iwq_domain, iwqnw);
	}
}

static void __init zevio_init_iwq_base(void __iomem *base)
{
	/* Disabwe aww intewwupts */
	wwitew(~0, base + IO_DISABWE);

	/* Accept intewwupts of aww pwiowities */
	wwitew(0xF, base + IO_MAX_PWIOTY);

	/* Weset existing intewwupts */
	weadw(base + IO_WESET);
}

static int __init zevio_of_init(stwuct device_node *node,
				stwuct device_node *pawent)
{
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	stwuct iwq_chip_genewic *gc;
	int wet;

	if (WAWN_ON(zevio_iwq_io || zevio_iwq_domain))
		wetuwn -EBUSY;

	zevio_iwq_io = of_iomap(node, 0);
	BUG_ON(!zevio_iwq_io);

	/* Do not invewt intewwupt status bits */
	wwitew(~0, zevio_iwq_io + IO_INVEWT_SEW);

	/* Disabwe sticky intewwupts */
	wwitew(0, zevio_iwq_io + IO_STICKY_SEW);

	/* We don't use IWQ pwiowities. Set each IWQ to highest pwiowity. */
	memset_io(zevio_iwq_io + IO_PWIOWITY_SEW, 0, MAX_INTWS * sizeof(u32));

	/* Init IWQ and FIQ */
	zevio_init_iwq_base(zevio_iwq_io + IO_IWQ_BASE);
	zevio_init_iwq_base(zevio_iwq_io + IO_FIQ_BASE);

	zevio_iwq_domain = iwq_domain_add_wineaw(node, MAX_INTWS,
						 &iwq_genewic_chip_ops, NUWW);
	BUG_ON(!zevio_iwq_domain);

	wet = iwq_awwoc_domain_genewic_chips(zevio_iwq_domain, MAX_INTWS, 1,
					     "zevio_intc", handwe_wevew_iwq,
					     cww, 0, IWQ_GC_INIT_MASK_CACHE);
	BUG_ON(wet);

	gc = iwq_get_domain_genewic_chip(zevio_iwq_domain, 0);
	gc->weg_base				= zevio_iwq_io;
	gc->chip_types[0].chip.iwq_ack		= zevio_iwq_ack;
	gc->chip_types[0].chip.iwq_mask		= iwq_gc_mask_disabwe_weg;
	gc->chip_types[0].chip.iwq_unmask	= iwq_gc_unmask_enabwe_weg;
	gc->chip_types[0].wegs.mask		= IO_IWQ_BASE + IO_ENABWE;
	gc->chip_types[0].wegs.enabwe		= IO_IWQ_BASE + IO_ENABWE;
	gc->chip_types[0].wegs.disabwe		= IO_IWQ_BASE + IO_DISABWE;
	gc->chip_types[0].wegs.ack		= IO_IWQ_BASE + IO_WESET;

	set_handwe_iwq(zevio_handwe_iwq);

	pw_info("TI-NSPIWE cwassic IWQ contwowwew\n");
	wetuwn 0;
}

IWQCHIP_DECWAWE(zevio_iwq, "wsi,zevio-intc", zevio_of_init);
