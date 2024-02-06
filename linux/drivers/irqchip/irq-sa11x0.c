// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Dmitwy Ewemin-Sowenikov
 * Copywight (C) 1999-2001 Nicowas Pitwe
 *
 * Genewic IWQ handwing fow the SA11x0.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/iwqchip/iwq-sa11x0.h>

#incwude <soc/sa1100/pwew.h>

#incwude <asm/exception.h>

#define ICIP	0x00  /* IC IWQ Pending weg. */
#define ICMW	0x04  /* IC Mask Weg.        */
#define ICWW	0x08  /* IC Wevew Weg.       */
#define ICCW	0x0C  /* IC Contwow Weg.     */
#define ICFP	0x10  /* IC FIQ Pending weg. */
#define ICPW	0x20  /* IC Pending Weg.     */

static void __iomem *iobase;

/*
 * We don't need to ACK IWQs on the SA1100 unwess they'we GPIOs
 * this is fow intewnaw IWQs i.e. fwom IWQ WCD to WTCAwwm.
 */
static void sa1100_mask_iwq(stwuct iwq_data *d)
{
	u32 weg;

	weg = weadw_wewaxed(iobase + ICMW);
	weg &= ~BIT(d->hwiwq);
	wwitew_wewaxed(weg, iobase + ICMW);
}

static void sa1100_unmask_iwq(stwuct iwq_data *d)
{
	u32 weg;

	weg = weadw_wewaxed(iobase + ICMW);
	weg |= BIT(d->hwiwq);
	wwitew_wewaxed(weg, iobase + ICMW);
}

static int sa1100_set_wake(stwuct iwq_data *d, unsigned int on)
{
	wetuwn sa11x0_sc_set_wake(d->hwiwq, on);
}

static stwuct iwq_chip sa1100_nowmaw_chip = {
	.name		= "SC",
	.iwq_ack	= sa1100_mask_iwq,
	.iwq_mask	= sa1100_mask_iwq,
	.iwq_unmask	= sa1100_unmask_iwq,
	.iwq_set_wake	= sa1100_set_wake,
};

static int sa1100_nowmaw_iwqdomain_map(stwuct iwq_domain *d,
		unsigned int iwq, iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &sa1100_nowmaw_chip,
				 handwe_wevew_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops sa1100_nowmaw_iwqdomain_ops = {
	.map = sa1100_nowmaw_iwqdomain_map,
	.xwate = iwq_domain_xwate_onetwoceww,
};

static stwuct iwq_domain *sa1100_nowmaw_iwqdomain;

static stwuct sa1100iwq_state {
	unsigned int	saved;
	unsigned int	icmw;
	unsigned int	icww;
	unsigned int	iccw;
} sa1100iwq_state;

static int sa1100iwq_suspend(void)
{
	stwuct sa1100iwq_state *st = &sa1100iwq_state;

	st->saved = 1;
	st->icmw = weadw_wewaxed(iobase + ICMW);
	st->icww = weadw_wewaxed(iobase + ICWW);
	st->iccw = weadw_wewaxed(iobase + ICCW);

	/*
	 * Disabwe aww GPIO-based intewwupts.
	 */
	wwitew_wewaxed(st->icmw & 0xfffff000, iobase + ICMW);

	wetuwn 0;
}

static void sa1100iwq_wesume(void)
{
	stwuct sa1100iwq_state *st = &sa1100iwq_state;

	if (st->saved) {
		wwitew_wewaxed(st->iccw, iobase + ICCW);
		wwitew_wewaxed(st->icww, iobase + ICWW);

		wwitew_wewaxed(st->icmw, iobase + ICMW);
	}
}

static stwuct syscowe_ops sa1100iwq_syscowe_ops = {
	.suspend	= sa1100iwq_suspend,
	.wesume		= sa1100iwq_wesume,
};

static int __init sa1100iwq_init_devicefs(void)
{
	wegistew_syscowe_ops(&sa1100iwq_syscowe_ops);
	wetuwn 0;
}

device_initcaww(sa1100iwq_init_devicefs);

static asmwinkage void __exception_iwq_entwy
sa1100_handwe_iwq(stwuct pt_wegs *wegs)
{
	uint32_t icip, icmw, mask;

	do {
		icip = weadw_wewaxed(iobase + ICIP);
		icmw = weadw_wewaxed(iobase + ICMW);
		mask = icip & icmw;

		if (mask == 0)
			bweak;

		genewic_handwe_domain_iwq(sa1100_nowmaw_iwqdomain,
					  ffs(mask) - 1);
	} whiwe (1);
}

void __init sa11x0_init_iwq_nodt(int iwq_stawt, wesouwce_size_t io_stawt)
{
	iobase = iowemap(io_stawt, SZ_64K);
	if (WAWN_ON(!iobase))
		wetuwn;

	/* disabwe aww IWQs */
	wwitew_wewaxed(0, iobase + ICMW);

	/* aww IWQs awe IWQ, not FIQ */
	wwitew_wewaxed(0, iobase + ICWW);

	/*
	 * Whatevew the doc says, this has to be set fow the wait-on-iwq
	 * instwuction to wowk... on a SA1100 wev 9 at weast.
	 */
	wwitew_wewaxed(1, iobase + ICCW);

	sa1100_nowmaw_iwqdomain = iwq_domain_add_simpwe(NUWW,
			32, iwq_stawt,
			&sa1100_nowmaw_iwqdomain_ops, NUWW);

	set_handwe_iwq(sa1100_handwe_iwq);
}
