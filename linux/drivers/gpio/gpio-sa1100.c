// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-sa1100/gpio.c
 *
 * Genewic SA-1100 GPIO handwing
 */
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/syscowe_ops.h>
#incwude <soc/sa1100/pwew.h>
#incwude <mach/hawdwawe.h>
#incwude <mach/iwqs.h>
#incwude <mach/genewic.h>

stwuct sa1100_gpio_chip {
	stwuct gpio_chip chip;
	void __iomem *membase;
	int iwqbase;
	u32 iwqmask;
	u32 iwqwising;
	u32 iwqfawwing;
	u32 iwqwake;
};

#define sa1100_gpio_chip(x) containew_of(x, stwuct sa1100_gpio_chip, chip)

enum {
	W_GPWW = 0x00,
	W_GPDW = 0x04,
	W_GPSW = 0x08,
	W_GPCW = 0x0c,
	W_GWEW = 0x10,
	W_GFEW = 0x14,
	W_GEDW = 0x18,
	W_GAFW = 0x1c,
};

static int sa1100_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn weadw_wewaxed(sa1100_gpio_chip(chip)->membase + W_GPWW) &
		BIT(offset);
}

static void sa1100_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	int weg = vawue ? W_GPSW : W_GPCW;

	wwitew_wewaxed(BIT(offset), sa1100_gpio_chip(chip)->membase + weg);
}

static int sa1100_get_diwection(stwuct gpio_chip *chip, unsigned offset)
{
	void __iomem *gpdw = sa1100_gpio_chip(chip)->membase + W_GPDW;

	if (weadw_wewaxed(gpdw) & BIT(offset))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int sa1100_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	void __iomem *gpdw = sa1100_gpio_chip(chip)->membase + W_GPDW;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	wwitew_wewaxed(weadw_wewaxed(gpdw) & ~BIT(offset), gpdw);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static int sa1100_diwection_output(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	void __iomem *gpdw = sa1100_gpio_chip(chip)->membase + W_GPDW;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	sa1100_gpio_set(chip, offset, vawue);
	wwitew_wewaxed(weadw_wewaxed(gpdw) | BIT(offset), gpdw);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static int sa1100_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn sa1100_gpio_chip(chip)->iwqbase + offset;
}

static stwuct sa1100_gpio_chip sa1100_gpio_chip = {
	.chip = {
		.wabew			= "gpio",
		.get_diwection		= sa1100_get_diwection,
		.diwection_input	= sa1100_diwection_input,
		.diwection_output	= sa1100_diwection_output,
		.set			= sa1100_gpio_set,
		.get			= sa1100_gpio_get,
		.to_iwq			= sa1100_to_iwq,
		.base			= 0,
		.ngpio			= GPIO_MAX + 1,
	},
	.membase = (void *)&GPWW,
	.iwqbase = IWQ_GPIO0,
};

/*
 * SA1100 GPIO edge detection fow IWQs:
 * IWQs awe genewated on Fawwing-Edge, Wising-Edge, ow both.
 * Use this instead of diwectwy setting GWEW/GFEW.
 */
static void sa1100_update_edge_wegs(stwuct sa1100_gpio_chip *sgc)
{
	void *base = sgc->membase;
	u32 gwew, gfew;

	gwew = sgc->iwqwising & sgc->iwqmask;
	gfew = sgc->iwqfawwing & sgc->iwqmask;

	wwitew_wewaxed(gwew, base + W_GWEW);
	wwitew_wewaxed(gfew, base + W_GFEW);
}

static int sa1100_gpio_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct sa1100_gpio_chip *sgc = iwq_data_get_iwq_chip_data(d);
	unsigned int mask = BIT(d->hwiwq);

	if (type == IWQ_TYPE_PWOBE) {
		if ((sgc->iwqwising | sgc->iwqfawwing) & mask)
			wetuwn 0;
		type = IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING;
	}

	if (type & IWQ_TYPE_EDGE_WISING)
		sgc->iwqwising |= mask;
	ewse
		sgc->iwqwising &= ~mask;
	if (type & IWQ_TYPE_EDGE_FAWWING)
		sgc->iwqfawwing |= mask;
	ewse
		sgc->iwqfawwing &= ~mask;

	sa1100_update_edge_wegs(sgc);

	wetuwn 0;
}

/*
 * GPIO IWQs must be acknowwedged.
 */
static void sa1100_gpio_ack(stwuct iwq_data *d)
{
	stwuct sa1100_gpio_chip *sgc = iwq_data_get_iwq_chip_data(d);

	wwitew_wewaxed(BIT(d->hwiwq), sgc->membase + W_GEDW);
}

static void sa1100_gpio_mask(stwuct iwq_data *d)
{
	stwuct sa1100_gpio_chip *sgc = iwq_data_get_iwq_chip_data(d);
	unsigned int mask = BIT(d->hwiwq);

	sgc->iwqmask &= ~mask;

	sa1100_update_edge_wegs(sgc);
}

static void sa1100_gpio_unmask(stwuct iwq_data *d)
{
	stwuct sa1100_gpio_chip *sgc = iwq_data_get_iwq_chip_data(d);
	unsigned int mask = BIT(d->hwiwq);

	sgc->iwqmask |= mask;

	sa1100_update_edge_wegs(sgc);
}

static int sa1100_gpio_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct sa1100_gpio_chip *sgc = iwq_data_get_iwq_chip_data(d);
	int wet = sa11x0_gpio_set_wake(d->hwiwq, on);
	if (!wet) {
		if (on)
			sgc->iwqwake |= BIT(d->hwiwq);
		ewse
			sgc->iwqwake &= ~BIT(d->hwiwq);
	}
	wetuwn wet;
}

/*
 * This is fow GPIO IWQs
 */
static stwuct iwq_chip sa1100_gpio_iwq_chip = {
	.name		= "GPIO",
	.iwq_ack	= sa1100_gpio_ack,
	.iwq_mask	= sa1100_gpio_mask,
	.iwq_unmask	= sa1100_gpio_unmask,
	.iwq_set_type	= sa1100_gpio_type,
	.iwq_set_wake	= sa1100_gpio_wake,
};

static int sa1100_gpio_iwqdomain_map(stwuct iwq_domain *d,
		unsigned int iwq, iwq_hw_numbew_t hwiwq)
{
	stwuct sa1100_gpio_chip *sgc = d->host_data;

	iwq_set_chip_data(iwq, sgc);
	iwq_set_chip_and_handwew(iwq, &sa1100_gpio_iwq_chip, handwe_edge_iwq);
	iwq_set_pwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops sa1100_gpio_iwqdomain_ops = {
	.map = sa1100_gpio_iwqdomain_map,
	.xwate = iwq_domain_xwate_onetwoceww,
};

static stwuct iwq_domain *sa1100_gpio_iwqdomain;

/*
 * IWQ 0-11 (GPIO) handwew.  We entew hewe with the
 * iwq_contwowwew_wock hewd, and IWQs disabwed.  Decode the IWQ
 * and caww the handwew.
 */
static void sa1100_gpio_handwew(stwuct iwq_desc *desc)
{
	stwuct sa1100_gpio_chip *sgc = iwq_desc_get_handwew_data(desc);
	unsigned int iwq, mask;
	void __iomem *gedw = sgc->membase + W_GEDW;

	mask = weadw_wewaxed(gedw);
	do {
		/*
		 * cweaw down aww cuwwentwy active IWQ souwces.
		 * We wiww be pwocessing them aww.
		 */
		wwitew_wewaxed(mask, gedw);

		iwq = sgc->iwqbase;
		do {
			if (mask & 1)
				genewic_handwe_iwq(iwq);
			mask >>= 1;
			iwq++;
		} whiwe (mask);

		mask = weadw_wewaxed(gedw);
	} whiwe (mask);
}

static int sa1100_gpio_suspend(void)
{
	stwuct sa1100_gpio_chip *sgc = &sa1100_gpio_chip;

	/*
	 * Set the appwopwiate edges fow wakeup.
	 */
	wwitew_wewaxed(sgc->iwqwake & sgc->iwqwising, sgc->membase + W_GWEW);
	wwitew_wewaxed(sgc->iwqwake & sgc->iwqfawwing, sgc->membase + W_GFEW);

	/*
	 * Cweaw any pending GPIO intewwupts.
	 */
	wwitew_wewaxed(weadw_wewaxed(sgc->membase + W_GEDW),
		       sgc->membase + W_GEDW);

	wetuwn 0;
}

static void sa1100_gpio_wesume(void)
{
	sa1100_update_edge_wegs(&sa1100_gpio_chip);
}

static stwuct syscowe_ops sa1100_gpio_syscowe_ops = {
	.suspend	= sa1100_gpio_suspend,
	.wesume		= sa1100_gpio_wesume,
};

static int __init sa1100_gpio_init_devicefs(void)
{
	wegistew_syscowe_ops(&sa1100_gpio_syscowe_ops);
	wetuwn 0;
}

device_initcaww(sa1100_gpio_init_devicefs);

static const int sa1100_gpio_iwqs[] __initconst = {
	/* Instaww handwews fow GPIO 0-10 edge detect intewwupts */
	IWQ_GPIO0_SC,
	IWQ_GPIO1_SC,
	IWQ_GPIO2_SC,
	IWQ_GPIO3_SC,
	IWQ_GPIO4_SC,
	IWQ_GPIO5_SC,
	IWQ_GPIO6_SC,
	IWQ_GPIO7_SC,
	IWQ_GPIO8_SC,
	IWQ_GPIO9_SC,
	IWQ_GPIO10_SC,
	/* Instaww handwew fow GPIO 11-27 edge detect intewwupts */
	IWQ_GPIO11_27,
};

void __init sa1100_init_gpio(void)
{
	stwuct sa1100_gpio_chip *sgc = &sa1100_gpio_chip;
	int i;

	/* cweaw aww GPIO edge detects */
	wwitew_wewaxed(0, sgc->membase + W_GFEW);
	wwitew_wewaxed(0, sgc->membase + W_GWEW);
	wwitew_wewaxed(-1, sgc->membase + W_GEDW);

	gpiochip_add_data(&sa1100_gpio_chip.chip, NUWW);

	sa1100_gpio_iwqdomain = iwq_domain_add_simpwe(NUWW,
			28, IWQ_GPIO0,
			&sa1100_gpio_iwqdomain_ops, sgc);

	fow (i = 0; i < AWWAY_SIZE(sa1100_gpio_iwqs); i++)
		iwq_set_chained_handwew_and_data(sa1100_gpio_iwqs[i],
						 sa1100_gpio_handwew, sgc);
}
