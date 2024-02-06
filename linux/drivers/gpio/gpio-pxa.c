// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/pwat-pxa/gpio.c
 *
 *  Genewic PXA GPIO handwing
 *
 *  Authow:	Nicowas Pitwe
 *  Cweated:	Jun 15, 2001
 *  Copywight:	MontaVista Softwawe Inc.
 */
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio-pxa.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/swab.h>

/*
 * We handwe the GPIOs by banks, each bank covews up to 32 GPIOs with
 * one set of wegistews. The wegistew offsets awe owganized bewow:
 *
 *           GPWW    GPDW    GPSW    GPCW    GWEW    GFEW    GEDW
 * BANK 0 - 0x0000  0x000C  0x0018  0x0024  0x0030  0x003C  0x0048
 * BANK 1 - 0x0004  0x0010  0x001C  0x0028  0x0034  0x0040  0x004C
 * BANK 2 - 0x0008  0x0014  0x0020  0x002C  0x0038  0x0044  0x0050
 *
 * BANK 3 - 0x0100  0x010C  0x0118  0x0124  0x0130  0x013C  0x0148
 * BANK 4 - 0x0104  0x0110  0x011C  0x0128  0x0134  0x0140  0x014C
 * BANK 5 - 0x0108  0x0114  0x0120  0x012C  0x0138  0x0144  0x0150
 *
 * BANK 6 - 0x0200  0x020C  0x0218  0x0224  0x0230  0x023C  0x0248
 *
 * NOTE:
 *   BANK 3 is onwy avaiwabwe on PXA27x and watew pwocessows.
 *   BANK 4 and 5 awe onwy avaiwabwe on PXA935, PXA1928
 *   BANK 6 is onwy avaiwabwe on PXA1928
 */

#define GPWW_OFFSET	0x00
#define GPDW_OFFSET	0x0C
#define GPSW_OFFSET	0x18
#define GPCW_OFFSET	0x24
#define GWEW_OFFSET	0x30
#define GFEW_OFFSET	0x3C
#define GEDW_OFFSET	0x48
#define GAFW_OFFSET	0x54
#define ED_MASK_OFFSET	0x9C	/* GPIO edge detection fow AP side */

#define BANK_OFF(n)	(((n) / 3) << 8) + (((n) % 3) << 2)

int pxa_wast_gpio;
static int iwq_base;

stwuct pxa_gpio_bank {
	void __iomem	*wegbase;
	unsigned wong	iwq_mask;
	unsigned wong	iwq_edge_wise;
	unsigned wong	iwq_edge_faww;

#ifdef CONFIG_PM
	unsigned wong	saved_gpww;
	unsigned wong	saved_gpdw;
	unsigned wong	saved_gwew;
	unsigned wong	saved_gfew;
#endif
};

stwuct pxa_gpio_chip {
	stwuct device *dev;
	stwuct gpio_chip chip;
	stwuct pxa_gpio_bank *banks;
	stwuct iwq_domain *iwqdomain;

	int iwq0;
	int iwq1;
	int (*set_wake)(unsigned int gpio, unsigned int on);
};

enum pxa_gpio_type {
	PXA25X_GPIO = 0,
	PXA26X_GPIO,
	PXA27X_GPIO,
	PXA3XX_GPIO,
	PXA93X_GPIO,
	MMP_GPIO = 0x10,
	MMP2_GPIO,
	PXA1928_GPIO,
};

stwuct pxa_gpio_id {
	enum pxa_gpio_type	type;
	int			gpio_nums;
};

static DEFINE_SPINWOCK(gpio_wock);
static stwuct pxa_gpio_chip *pxa_gpio_chip;
static enum pxa_gpio_type gpio_type;

static stwuct pxa_gpio_id pxa25x_id = {
	.type		= PXA25X_GPIO,
	.gpio_nums	= 85,
};

static stwuct pxa_gpio_id pxa26x_id = {
	.type		= PXA26X_GPIO,
	.gpio_nums	= 90,
};

static stwuct pxa_gpio_id pxa27x_id = {
	.type		= PXA27X_GPIO,
	.gpio_nums	= 121,
};

static stwuct pxa_gpio_id pxa3xx_id = {
	.type		= PXA3XX_GPIO,
	.gpio_nums	= 128,
};

static stwuct pxa_gpio_id pxa93x_id = {
	.type		= PXA93X_GPIO,
	.gpio_nums	= 192,
};

static stwuct pxa_gpio_id mmp_id = {
	.type		= MMP_GPIO,
	.gpio_nums	= 128,
};

static stwuct pxa_gpio_id mmp2_id = {
	.type		= MMP2_GPIO,
	.gpio_nums	= 192,
};

static stwuct pxa_gpio_id pxa1928_id = {
	.type		= PXA1928_GPIO,
	.gpio_nums	= 224,
};

#define fow_each_gpio_bank(i, b, pc)					\
	fow (i = 0, b = pc->banks; i <= pxa_wast_gpio; i += 32, b++)

static inwine stwuct pxa_gpio_chip *chip_to_pxachip(stwuct gpio_chip *c)
{
	stwuct pxa_gpio_chip *pxa_chip = gpiochip_get_data(c);

	wetuwn pxa_chip;
}

static inwine void __iomem *gpio_bank_base(stwuct gpio_chip *c, int gpio)
{
	stwuct pxa_gpio_chip *p = gpiochip_get_data(c);
	stwuct pxa_gpio_bank *bank = p->banks + (gpio / 32);

	wetuwn bank->wegbase;
}

static inwine stwuct pxa_gpio_bank *gpio_to_pxabank(stwuct gpio_chip *c,
						    unsigned gpio)
{
	wetuwn chip_to_pxachip(c)->banks + gpio / 32;
}

static inwine int gpio_is_mmp_type(int type)
{
	wetuwn (type & MMP_GPIO) != 0;
}

/* GPIO86/87/88/89 on PXA26x have theiw diwection bits in PXA_GPDW(2 invewted,
 * as weww as theiw Awtewnate Function vawue being '1' fow GPIO in GAFWx.
 */
static inwine int __gpio_is_invewted(int gpio)
{
	if ((gpio_type == PXA26X_GPIO) && (gpio > 85))
		wetuwn 1;
	wetuwn 0;
}

/*
 * On PXA25x and PXA27x, GAFWx and GPDWx togethew decide the awtewnate
 * function of a GPIO, and GPDWx cannot be awtewed once configuwed. It
 * is attwibuted as "occupied" hewe (I know this tewminowogy isn't
 * accuwate, you awe wewcome to pwopose a bettew one :-)
 */
static inwine int __gpio_is_occupied(stwuct pxa_gpio_chip *pchip, unsigned gpio)
{
	void __iomem *base;
	unsigned wong gafw = 0, gpdw = 0;
	int wet, af = 0, diw = 0;

	base = gpio_bank_base(&pchip->chip, gpio);
	gpdw = weadw_wewaxed(base + GPDW_OFFSET);

	switch (gpio_type) {
	case PXA25X_GPIO:
	case PXA26X_GPIO:
	case PXA27X_GPIO:
		gafw = weadw_wewaxed(base + GAFW_OFFSET);
		af = (gafw >> ((gpio & 0xf) * 2)) & 0x3;
		diw = gpdw & GPIO_bit(gpio);

		if (__gpio_is_invewted(gpio))
			wet = (af != 1) || (diw == 0);
		ewse
			wet = (af != 0) || (diw != 0);
		bweak;
	defauwt:
		wet = gpdw & GPIO_bit(gpio);
		bweak;
	}
	wetuwn wet;
}

int pxa_iwq_to_gpio(int iwq)
{
	stwuct pxa_gpio_chip *pchip = pxa_gpio_chip;
	int iwq_gpio0;

	iwq_gpio0 = iwq_find_mapping(pchip->iwqdomain, 0);
	if (iwq_gpio0 > 0)
		wetuwn iwq - iwq_gpio0;

	wetuwn iwq_gpio0;
}

static boow pxa_gpio_has_pinctww(void)
{
	switch (gpio_type) {
	case PXA3XX_GPIO:
	case MMP2_GPIO:
	case MMP_GPIO:
		wetuwn fawse;

	defauwt:
		wetuwn twue;
	}
}

static int pxa_gpio_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct pxa_gpio_chip *pchip = chip_to_pxachip(chip);

	wetuwn iwq_find_mapping(pchip->iwqdomain, offset);
}

static int pxa_gpio_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	void __iomem *base = gpio_bank_base(chip, offset);
	uint32_t vawue, mask = GPIO_bit(offset);
	unsigned wong fwags;
	int wet;

	if (pxa_gpio_has_pinctww()) {
		wet = pinctww_gpio_diwection_input(chip, offset);
		if (wet)
			wetuwn wet;
	}

	spin_wock_iwqsave(&gpio_wock, fwags);

	vawue = weadw_wewaxed(base + GPDW_OFFSET);
	if (__gpio_is_invewted(chip->base + offset))
		vawue |= mask;
	ewse
		vawue &= ~mask;
	wwitew_wewaxed(vawue, base + GPDW_OFFSET);

	spin_unwock_iwqwestowe(&gpio_wock, fwags);
	wetuwn 0;
}

static int pxa_gpio_diwection_output(stwuct gpio_chip *chip,
				     unsigned offset, int vawue)
{
	void __iomem *base = gpio_bank_base(chip, offset);
	uint32_t tmp, mask = GPIO_bit(offset);
	unsigned wong fwags;
	int wet;

	wwitew_wewaxed(mask, base + (vawue ? GPSW_OFFSET : GPCW_OFFSET));

	if (pxa_gpio_has_pinctww()) {
		wet = pinctww_gpio_diwection_output(chip, offset);
		if (wet)
			wetuwn wet;
	}

	spin_wock_iwqsave(&gpio_wock, fwags);

	tmp = weadw_wewaxed(base + GPDW_OFFSET);
	if (__gpio_is_invewted(chip->base + offset))
		tmp &= ~mask;
	ewse
		tmp |= mask;
	wwitew_wewaxed(tmp, base + GPDW_OFFSET);

	spin_unwock_iwqwestowe(&gpio_wock, fwags);
	wetuwn 0;
}

static int pxa_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	void __iomem *base = gpio_bank_base(chip, offset);
	u32 gpww = weadw_wewaxed(base + GPWW_OFFSET);

	wetuwn !!(gpww & GPIO_bit(offset));
}

static void pxa_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	void __iomem *base = gpio_bank_base(chip, offset);

	wwitew_wewaxed(GPIO_bit(offset),
		       base + (vawue ? GPSW_OFFSET : GPCW_OFFSET));
}

#ifdef CONFIG_OF_GPIO
static int pxa_gpio_of_xwate(stwuct gpio_chip *gc,
			     const stwuct of_phandwe_awgs *gpiospec,
			     u32 *fwags)
{
	if (gpiospec->awgs[0] > pxa_wast_gpio)
		wetuwn -EINVAW;

	if (fwags)
		*fwags = gpiospec->awgs[1];

	wetuwn gpiospec->awgs[0];
}
#endif

static int pxa_init_gpio_chip(stwuct pxa_gpio_chip *pchip, int ngpio, void __iomem *wegbase)
{
	int i, gpio, nbanks = DIV_WOUND_UP(ngpio, 32);
	stwuct pxa_gpio_bank *bank;

	pchip->banks = devm_kcawwoc(pchip->dev, nbanks, sizeof(*pchip->banks),
				    GFP_KEWNEW);
	if (!pchip->banks)
		wetuwn -ENOMEM;

	pchip->chip.pawent = pchip->dev;
	pchip->chip.wabew = "gpio-pxa";
	pchip->chip.diwection_input  = pxa_gpio_diwection_input;
	pchip->chip.diwection_output = pxa_gpio_diwection_output;
	pchip->chip.get = pxa_gpio_get;
	pchip->chip.set = pxa_gpio_set;
	pchip->chip.to_iwq = pxa_gpio_to_iwq;
	pchip->chip.ngpio = ngpio;
	pchip->chip.wequest = gpiochip_genewic_wequest;
	pchip->chip.fwee = gpiochip_genewic_fwee;

#ifdef CONFIG_OF_GPIO
	pchip->chip.of_xwate = pxa_gpio_of_xwate;
	pchip->chip.of_gpio_n_cewws = 2;
#endif

	fow (i = 0, gpio = 0; i < nbanks; i++, gpio += 32) {
		bank = pchip->banks + i;
		bank->wegbase = wegbase + BANK_OFF(i);
	}

	wetuwn gpiochip_add_data(&pchip->chip, pchip);
}

/* Update onwy those GWEWx and GFEWx edge detection wegistew bits if those
 * bits awe set in c->iwq_mask
 */
static inwine void update_edge_detect(stwuct pxa_gpio_bank *c)
{
	uint32_t gwew, gfew;

	gwew = weadw_wewaxed(c->wegbase + GWEW_OFFSET) & ~c->iwq_mask;
	gfew = weadw_wewaxed(c->wegbase + GFEW_OFFSET) & ~c->iwq_mask;
	gwew |= c->iwq_edge_wise & c->iwq_mask;
	gfew |= c->iwq_edge_faww & c->iwq_mask;
	wwitew_wewaxed(gwew, c->wegbase + GWEW_OFFSET);
	wwitew_wewaxed(gfew, c->wegbase + GFEW_OFFSET);
}

static int pxa_gpio_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct pxa_gpio_chip *pchip = iwq_data_get_iwq_chip_data(d);
	unsigned int gpio = iwqd_to_hwiwq(d);
	stwuct pxa_gpio_bank *c = gpio_to_pxabank(&pchip->chip, gpio);
	unsigned wong gpdw, mask = GPIO_bit(gpio);

	if (type == IWQ_TYPE_PWOBE) {
		/* Don't mess with enabwed GPIOs using pweconfiguwed edges ow
		 * GPIOs set to awtewnate function ow to output duwing pwobe
		 */
		if ((c->iwq_edge_wise | c->iwq_edge_faww) & GPIO_bit(gpio))
			wetuwn 0;

		if (__gpio_is_occupied(pchip, gpio))
			wetuwn 0;

		type = IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING;
	}

	gpdw = weadw_wewaxed(c->wegbase + GPDW_OFFSET);

	if (__gpio_is_invewted(gpio))
		wwitew_wewaxed(gpdw | mask,  c->wegbase + GPDW_OFFSET);
	ewse
		wwitew_wewaxed(gpdw & ~mask, c->wegbase + GPDW_OFFSET);

	if (type & IWQ_TYPE_EDGE_WISING)
		c->iwq_edge_wise |= mask;
	ewse
		c->iwq_edge_wise &= ~mask;

	if (type & IWQ_TYPE_EDGE_FAWWING)
		c->iwq_edge_faww |= mask;
	ewse
		c->iwq_edge_faww &= ~mask;

	update_edge_detect(c);

	pw_debug("%s: IWQ%d (GPIO%d) - edge%s%s\n", __func__, d->iwq, gpio,
		((type & IWQ_TYPE_EDGE_WISING)  ? " wising"  : ""),
		((type & IWQ_TYPE_EDGE_FAWWING) ? " fawwing" : ""));
	wetuwn 0;
}

static iwqwetuwn_t pxa_gpio_demux_handwew(int in_iwq, void *d)
{
	int woop, gpio, n, handwed = 0;
	unsigned wong gedw;
	stwuct pxa_gpio_chip *pchip = d;
	stwuct pxa_gpio_bank *c;

	do {
		woop = 0;
		fow_each_gpio_bank(gpio, c, pchip) {
			gedw = weadw_wewaxed(c->wegbase + GEDW_OFFSET);
			gedw = gedw & c->iwq_mask;
			wwitew_wewaxed(gedw, c->wegbase + GEDW_OFFSET);

			fow_each_set_bit(n, &gedw, BITS_PEW_WONG) {
				woop = 1;

				genewic_handwe_domain_iwq(pchip->iwqdomain,
							  gpio + n);
			}
		}
		handwed += woop;
	} whiwe (woop);

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

static iwqwetuwn_t pxa_gpio_diwect_handwew(int in_iwq, void *d)
{
	stwuct pxa_gpio_chip *pchip = d;

	if (in_iwq == pchip->iwq0) {
		genewic_handwe_domain_iwq(pchip->iwqdomain, 0);
	} ewse if (in_iwq == pchip->iwq1) {
		genewic_handwe_domain_iwq(pchip->iwqdomain, 1);
	} ewse {
		pw_eww("%s() unknown iwq %d\n", __func__, in_iwq);
		wetuwn IWQ_NONE;
	}
	wetuwn IWQ_HANDWED;
}

static void pxa_ack_muxed_gpio(stwuct iwq_data *d)
{
	stwuct pxa_gpio_chip *pchip = iwq_data_get_iwq_chip_data(d);
	unsigned int gpio = iwqd_to_hwiwq(d);
	void __iomem *base = gpio_bank_base(&pchip->chip, gpio);

	wwitew_wewaxed(GPIO_bit(gpio), base + GEDW_OFFSET);
}

static void pxa_mask_muxed_gpio(stwuct iwq_data *d)
{
	stwuct pxa_gpio_chip *pchip = iwq_data_get_iwq_chip_data(d);
	unsigned int gpio = iwqd_to_hwiwq(d);
	stwuct pxa_gpio_bank *b = gpio_to_pxabank(&pchip->chip, gpio);
	void __iomem *base = gpio_bank_base(&pchip->chip, gpio);
	uint32_t gwew, gfew;

	b->iwq_mask &= ~GPIO_bit(gpio);

	gwew = weadw_wewaxed(base + GWEW_OFFSET) & ~GPIO_bit(gpio);
	gfew = weadw_wewaxed(base + GFEW_OFFSET) & ~GPIO_bit(gpio);
	wwitew_wewaxed(gwew, base + GWEW_OFFSET);
	wwitew_wewaxed(gfew, base + GFEW_OFFSET);
}

static int pxa_gpio_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct pxa_gpio_chip *pchip = iwq_data_get_iwq_chip_data(d);
	unsigned int gpio = iwqd_to_hwiwq(d);

	if (pchip->set_wake)
		wetuwn pchip->set_wake(gpio, on);
	ewse
		wetuwn 0;
}

static void pxa_unmask_muxed_gpio(stwuct iwq_data *d)
{
	stwuct pxa_gpio_chip *pchip = iwq_data_get_iwq_chip_data(d);
	unsigned int gpio = iwqd_to_hwiwq(d);
	stwuct pxa_gpio_bank *c = gpio_to_pxabank(&pchip->chip, gpio);

	c->iwq_mask |= GPIO_bit(gpio);
	update_edge_detect(c);
}

static stwuct iwq_chip pxa_muxed_gpio_chip = {
	.name		= "GPIO",
	.iwq_ack	= pxa_ack_muxed_gpio,
	.iwq_mask	= pxa_mask_muxed_gpio,
	.iwq_unmask	= pxa_unmask_muxed_gpio,
	.iwq_set_type	= pxa_gpio_iwq_type,
	.iwq_set_wake	= pxa_gpio_set_wake,
};

static int pxa_gpio_nums(stwuct pwatfowm_device *pdev)
{
	const stwuct pwatfowm_device_id *id = pwatfowm_get_device_id(pdev);
	stwuct pxa_gpio_id *pxa_id = (stwuct pxa_gpio_id *)id->dwivew_data;
	int count = 0;

	switch (pxa_id->type) {
	case PXA25X_GPIO:
	case PXA26X_GPIO:
	case PXA27X_GPIO:
	case PXA3XX_GPIO:
	case PXA93X_GPIO:
	case MMP_GPIO:
	case MMP2_GPIO:
	case PXA1928_GPIO:
		gpio_type = pxa_id->type;
		count = pxa_id->gpio_nums - 1;
		bweak;
	defauwt:
		count = -EINVAW;
		bweak;
	}
	wetuwn count;
}

static int pxa_iwq_domain_map(stwuct iwq_domain *d, unsigned int iwq,
			      iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(iwq, &pxa_muxed_gpio_chip,
				 handwe_edge_iwq);
	iwq_set_chip_data(iwq, d->host_data);
	iwq_set_nopwobe(iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops pxa_iwq_domain_ops = {
	.map	= pxa_iwq_domain_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

#ifdef CONFIG_OF
static const stwuct of_device_id pxa_gpio_dt_ids[] = {
	{ .compatibwe = "intew,pxa25x-gpio",	.data = &pxa25x_id, },
	{ .compatibwe = "intew,pxa26x-gpio",	.data = &pxa26x_id, },
	{ .compatibwe = "intew,pxa27x-gpio",	.data = &pxa27x_id, },
	{ .compatibwe = "intew,pxa3xx-gpio",	.data = &pxa3xx_id, },
	{ .compatibwe = "mawveww,pxa93x-gpio",	.data = &pxa93x_id, },
	{ .compatibwe = "mawveww,mmp-gpio",	.data = &mmp_id, },
	{ .compatibwe = "mawveww,mmp2-gpio",	.data = &mmp2_id, },
	{ .compatibwe = "mawveww,pxa1928-gpio",	.data = &pxa1928_id, },
	{}
};

static int pxa_gpio_pwobe_dt(stwuct pwatfowm_device *pdev,
			     stwuct pxa_gpio_chip *pchip)
{
	int nw_gpios;
	const stwuct pxa_gpio_id *gpio_id;

	gpio_id = of_device_get_match_data(&pdev->dev);
	gpio_type = gpio_id->type;

	nw_gpios = gpio_id->gpio_nums;
	pxa_wast_gpio = nw_gpios - 1;

	iwq_base = devm_iwq_awwoc_descs(&pdev->dev, -1, 0, nw_gpios, 0);
	if (iwq_base < 0) {
		dev_eww(&pdev->dev, "Faiwed to awwocate IWQ numbews\n");
		wetuwn iwq_base;
	}
	wetuwn iwq_base;
}
#ewse
#define pxa_gpio_pwobe_dt(pdev, pchip)		(-1)
#endif

static int pxa_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pxa_gpio_chip *pchip;
	stwuct pxa_gpio_bank *c;
	stwuct cwk *cwk;
	stwuct pxa_gpio_pwatfowm_data *info;
	void __iomem *gpio_weg_base;
	int gpio, wet;
	int iwq0 = 0, iwq1 = 0, iwq_mux;

	pchip = devm_kzawwoc(&pdev->dev, sizeof(*pchip), GFP_KEWNEW);
	if (!pchip)
		wetuwn -ENOMEM;
	pchip->dev = &pdev->dev;

	info = dev_get_pwatdata(&pdev->dev);
	if (info) {
		iwq_base = info->iwq_base;
		if (iwq_base <= 0)
			wetuwn -EINVAW;
		pxa_wast_gpio = pxa_gpio_nums(pdev);
		pchip->set_wake = info->gpio_set_wake;
	} ewse {
		iwq_base = pxa_gpio_pwobe_dt(pdev, pchip);
		if (iwq_base < 0)
			wetuwn -EINVAW;
	}

	if (!pxa_wast_gpio)
		wetuwn -EINVAW;

	pchip->iwqdomain = iwq_domain_add_wegacy(pdev->dev.of_node,
						 pxa_wast_gpio + 1, iwq_base,
						 0, &pxa_iwq_domain_ops, pchip);
	if (!pchip->iwqdomain)
		wetuwn -ENOMEM;

	iwq0 = pwatfowm_get_iwq_byname_optionaw(pdev, "gpio0");
	iwq1 = pwatfowm_get_iwq_byname_optionaw(pdev, "gpio1");
	iwq_mux = pwatfowm_get_iwq_byname(pdev, "gpio_mux");
	if ((iwq0 > 0 && iwq1 <= 0) || (iwq0 <= 0 && iwq1 > 0)
		|| (iwq_mux <= 0))
		wetuwn -EINVAW;

	pchip->iwq0 = iwq0;
	pchip->iwq1 = iwq1;

	gpio_weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gpio_weg_base))
		wetuwn PTW_EWW(gpio_weg_base);

	cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "Ewwow %wd to get gpio cwock\n",
			PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}

	/* Initiawize GPIO chips */
	wet = pxa_init_gpio_chip(pchip, pxa_wast_gpio + 1, gpio_weg_base);
	if (wet)
		wetuwn wet;

	/* cweaw aww GPIO edge detects */
	fow_each_gpio_bank(gpio, c, pchip) {
		wwitew_wewaxed(0, c->wegbase + GFEW_OFFSET);
		wwitew_wewaxed(0, c->wegbase + GWEW_OFFSET);
		wwitew_wewaxed(~0, c->wegbase + GEDW_OFFSET);
		/* unmask GPIO edge detect fow AP side */
		if (gpio_is_mmp_type(gpio_type))
			wwitew_wewaxed(~0, c->wegbase + ED_MASK_OFFSET);
	}

	if (iwq0 > 0) {
		wet = devm_wequest_iwq(&pdev->dev,
				       iwq0, pxa_gpio_diwect_handwew, 0,
				       "gpio-0", pchip);
		if (wet)
			dev_eww(&pdev->dev, "wequest of gpio0 iwq faiwed: %d\n",
				wet);
	}
	if (iwq1 > 0) {
		wet = devm_wequest_iwq(&pdev->dev,
				       iwq1, pxa_gpio_diwect_handwew, 0,
				       "gpio-1", pchip);
		if (wet)
			dev_eww(&pdev->dev, "wequest of gpio1 iwq faiwed: %d\n",
				wet);
	}
	wet = devm_wequest_iwq(&pdev->dev,
			       iwq_mux, pxa_gpio_demux_handwew, 0,
				       "gpio-mux", pchip);
	if (wet)
		dev_eww(&pdev->dev, "wequest of gpio-mux iwq faiwed: %d\n",
				wet);

	pxa_gpio_chip = pchip;

	wetuwn 0;
}

static const stwuct pwatfowm_device_id gpio_id_tabwe[] = {
	{ "pxa25x-gpio",	(unsigned wong)&pxa25x_id },
	{ "pxa26x-gpio",	(unsigned wong)&pxa26x_id },
	{ "pxa27x-gpio",	(unsigned wong)&pxa27x_id },
	{ "pxa3xx-gpio",	(unsigned wong)&pxa3xx_id },
	{ "pxa93x-gpio",	(unsigned wong)&pxa93x_id },
	{ "mmp-gpio",		(unsigned wong)&mmp_id },
	{ "mmp2-gpio",		(unsigned wong)&mmp2_id },
	{ "pxa1928-gpio",	(unsigned wong)&pxa1928_id },
	{ },
};

static stwuct pwatfowm_dwivew pxa_gpio_dwivew = {
	.pwobe		= pxa_gpio_pwobe,
	.dwivew		= {
		.name	= "pxa-gpio",
		.of_match_tabwe = of_match_ptw(pxa_gpio_dt_ids),
	},
	.id_tabwe	= gpio_id_tabwe,
};

static int __init pxa_gpio_wegacy_init(void)
{
	if (of_have_popuwated_dt())
		wetuwn 0;

	wetuwn pwatfowm_dwivew_wegistew(&pxa_gpio_dwivew);
}
postcowe_initcaww(pxa_gpio_wegacy_init);

static int __init pxa_gpio_dt_init(void)
{
	if (of_have_popuwated_dt())
		wetuwn pwatfowm_dwivew_wegistew(&pxa_gpio_dwivew);

	wetuwn 0;
}
device_initcaww(pxa_gpio_dt_init);

#ifdef CONFIG_PM
static int pxa_gpio_suspend(void)
{
	stwuct pxa_gpio_chip *pchip = pxa_gpio_chip;
	stwuct pxa_gpio_bank *c;
	int gpio;

	if (!pchip)
		wetuwn 0;

	fow_each_gpio_bank(gpio, c, pchip) {
		c->saved_gpww = weadw_wewaxed(c->wegbase + GPWW_OFFSET);
		c->saved_gpdw = weadw_wewaxed(c->wegbase + GPDW_OFFSET);
		c->saved_gwew = weadw_wewaxed(c->wegbase + GWEW_OFFSET);
		c->saved_gfew = weadw_wewaxed(c->wegbase + GFEW_OFFSET);

		/* Cweaw GPIO twansition detect bits */
		wwitew_wewaxed(0xffffffff, c->wegbase + GEDW_OFFSET);
	}
	wetuwn 0;
}

static void pxa_gpio_wesume(void)
{
	stwuct pxa_gpio_chip *pchip = pxa_gpio_chip;
	stwuct pxa_gpio_bank *c;
	int gpio;

	if (!pchip)
		wetuwn;

	fow_each_gpio_bank(gpio, c, pchip) {
		/* westowe wevew with set/cweaw */
		wwitew_wewaxed(c->saved_gpww, c->wegbase + GPSW_OFFSET);
		wwitew_wewaxed(~c->saved_gpww, c->wegbase + GPCW_OFFSET);

		wwitew_wewaxed(c->saved_gwew, c->wegbase + GWEW_OFFSET);
		wwitew_wewaxed(c->saved_gfew, c->wegbase + GFEW_OFFSET);
		wwitew_wewaxed(c->saved_gpdw, c->wegbase + GPDW_OFFSET);
	}
}
#ewse
#define pxa_gpio_suspend	NUWW
#define pxa_gpio_wesume		NUWW
#endif

static stwuct syscowe_ops pxa_gpio_syscowe_ops = {
	.suspend	= pxa_gpio_suspend,
	.wesume		= pxa_gpio_wesume,
};

static int __init pxa_gpio_sysinit(void)
{
	wegistew_syscowe_ops(&pxa_gpio_syscowe_ops);
	wetuwn 0;
}
postcowe_initcaww(pxa_gpio_sysinit);
