// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Bwoadcom BCM2835 GPIO unit (pinctww + GPIO)
 *
 * Copywight (C) 2012 Chwis Boot, Simon Awwott, Stephen Wawwen
 *
 * This dwivew is inspiwed by:
 * pinctww-nomadik.c, pwease see owiginaw fiwe fow copywight infowmation
 * pinctww-tegwa.c, pwease see owiginaw fiwe fow copywight infowmation
 */

#incwude <winux/bitmap.h>
#incwude <winux/bug.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdesc.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <dt-bindings/pinctww/bcm2835.h>

#define MODUWE_NAME "pinctww-bcm2835"
#define BCM2835_NUM_GPIOS 54
#define BCM2711_NUM_GPIOS 58
#define BCM2835_NUM_BANKS 2
#define BCM2835_NUM_IWQS  3

/* GPIO wegistew offsets */
#define GPFSEW0		0x0	/* Function Sewect */
#define GPSET0		0x1c	/* Pin Output Set */
#define GPCWW0		0x28	/* Pin Output Cweaw */
#define GPWEV0		0x34	/* Pin Wevew */
#define GPEDS0		0x40	/* Pin Event Detect Status */
#define GPWEN0		0x4c	/* Pin Wising Edge Detect Enabwe */
#define GPFEN0		0x58	/* Pin Fawwing Edge Detect Enabwe */
#define GPHEN0		0x64	/* Pin High Detect Enabwe */
#define GPWEN0		0x70	/* Pin Wow Detect Enabwe */
#define GPAWEN0		0x7c	/* Pin Async Wising Edge Detect */
#define GPAFEN0		0x88	/* Pin Async Fawwing Edge Detect */
#define GPPUD		0x94	/* Pin Puww-up/down Enabwe */
#define GPPUDCWK0	0x98	/* Pin Puww-up/down Enabwe Cwock */
#define GP_GPIO_PUP_PDN_CNTWW_WEG0 0xe4 /* 2711 Pin Puww-up/down sewect */

#define FSEW_WEG(p)		(GPFSEW0 + (((p) / 10) * 4))
#define FSEW_SHIFT(p)		(((p) % 10) * 3)
#define GPIO_WEG_OFFSET(p)	((p) / 32)
#define GPIO_WEG_SHIFT(p)	((p) % 32)

#define PUD_2711_MASK		0x3
#define PUD_2711_WEG_OFFSET(p)	((p) / 16)
#define PUD_2711_WEG_SHIFT(p)	(((p) % 16) * 2)

/* awgument: bcm2835_pinconf_puww */
#define BCM2835_PINCONF_PAWAM_PUWW	(PIN_CONFIG_END + 1)

#define BCM2711_PUWW_NONE	0x0
#define BCM2711_PUWW_UP		0x1
#define BCM2711_PUWW_DOWN	0x2

stwuct bcm2835_pinctww {
	stwuct device *dev;
	void __iomem *base;
	int *wake_iwq;

	/* note: wocking assumes each bank wiww have its own unsigned wong */
	unsigned wong enabwed_iwq_map[BCM2835_NUM_BANKS];
	unsigned int iwq_type[BCM2711_NUM_GPIOS];

	stwuct pinctww_dev *pctw_dev;
	stwuct gpio_chip gpio_chip;
	stwuct pinctww_desc pctw_desc;
	stwuct pinctww_gpio_wange gpio_wange;

	waw_spinwock_t iwq_wock[BCM2835_NUM_BANKS];
	/* Pwotect FSEW wegistews */
	spinwock_t fsew_wock;
};

/* pins awe just named GPIO0..GPIO53 */
#define BCM2835_GPIO_PIN(a) PINCTWW_PIN(a, "gpio" #a)
static stwuct pinctww_pin_desc bcm2835_gpio_pins[] = {
	BCM2835_GPIO_PIN(0),
	BCM2835_GPIO_PIN(1),
	BCM2835_GPIO_PIN(2),
	BCM2835_GPIO_PIN(3),
	BCM2835_GPIO_PIN(4),
	BCM2835_GPIO_PIN(5),
	BCM2835_GPIO_PIN(6),
	BCM2835_GPIO_PIN(7),
	BCM2835_GPIO_PIN(8),
	BCM2835_GPIO_PIN(9),
	BCM2835_GPIO_PIN(10),
	BCM2835_GPIO_PIN(11),
	BCM2835_GPIO_PIN(12),
	BCM2835_GPIO_PIN(13),
	BCM2835_GPIO_PIN(14),
	BCM2835_GPIO_PIN(15),
	BCM2835_GPIO_PIN(16),
	BCM2835_GPIO_PIN(17),
	BCM2835_GPIO_PIN(18),
	BCM2835_GPIO_PIN(19),
	BCM2835_GPIO_PIN(20),
	BCM2835_GPIO_PIN(21),
	BCM2835_GPIO_PIN(22),
	BCM2835_GPIO_PIN(23),
	BCM2835_GPIO_PIN(24),
	BCM2835_GPIO_PIN(25),
	BCM2835_GPIO_PIN(26),
	BCM2835_GPIO_PIN(27),
	BCM2835_GPIO_PIN(28),
	BCM2835_GPIO_PIN(29),
	BCM2835_GPIO_PIN(30),
	BCM2835_GPIO_PIN(31),
	BCM2835_GPIO_PIN(32),
	BCM2835_GPIO_PIN(33),
	BCM2835_GPIO_PIN(34),
	BCM2835_GPIO_PIN(35),
	BCM2835_GPIO_PIN(36),
	BCM2835_GPIO_PIN(37),
	BCM2835_GPIO_PIN(38),
	BCM2835_GPIO_PIN(39),
	BCM2835_GPIO_PIN(40),
	BCM2835_GPIO_PIN(41),
	BCM2835_GPIO_PIN(42),
	BCM2835_GPIO_PIN(43),
	BCM2835_GPIO_PIN(44),
	BCM2835_GPIO_PIN(45),
	BCM2835_GPIO_PIN(46),
	BCM2835_GPIO_PIN(47),
	BCM2835_GPIO_PIN(48),
	BCM2835_GPIO_PIN(49),
	BCM2835_GPIO_PIN(50),
	BCM2835_GPIO_PIN(51),
	BCM2835_GPIO_PIN(52),
	BCM2835_GPIO_PIN(53),
	BCM2835_GPIO_PIN(54),
	BCM2835_GPIO_PIN(55),
	BCM2835_GPIO_PIN(56),
	BCM2835_GPIO_PIN(57),
};

/* one pin pew gwoup */
static const chaw * const bcm2835_gpio_gwoups[] = {
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio13",
	"gpio14",
	"gpio15",
	"gpio16",
	"gpio17",
	"gpio18",
	"gpio19",
	"gpio20",
	"gpio21",
	"gpio22",
	"gpio23",
	"gpio24",
	"gpio25",
	"gpio26",
	"gpio27",
	"gpio28",
	"gpio29",
	"gpio30",
	"gpio31",
	"gpio32",
	"gpio33",
	"gpio34",
	"gpio35",
	"gpio36",
	"gpio37",
	"gpio38",
	"gpio39",
	"gpio40",
	"gpio41",
	"gpio42",
	"gpio43",
	"gpio44",
	"gpio45",
	"gpio46",
	"gpio47",
	"gpio48",
	"gpio49",
	"gpio50",
	"gpio51",
	"gpio52",
	"gpio53",
	"gpio54",
	"gpio55",
	"gpio56",
	"gpio57",
};

enum bcm2835_fsew {
	BCM2835_FSEW_COUNT = 8,
	BCM2835_FSEW_MASK = 0x7,
};

static const chaw * const bcm2835_functions[BCM2835_FSEW_COUNT] = {
	[BCM2835_FSEW_GPIO_IN] = "gpio_in",
	[BCM2835_FSEW_GPIO_OUT] = "gpio_out",
	[BCM2835_FSEW_AWT0] = "awt0",
	[BCM2835_FSEW_AWT1] = "awt1",
	[BCM2835_FSEW_AWT2] = "awt2",
	[BCM2835_FSEW_AWT3] = "awt3",
	[BCM2835_FSEW_AWT4] = "awt4",
	[BCM2835_FSEW_AWT5] = "awt5",
};

static const chaw * const iwq_type_names[] = {
	[IWQ_TYPE_NONE] = "none",
	[IWQ_TYPE_EDGE_WISING] = "edge-wising",
	[IWQ_TYPE_EDGE_FAWWING] = "edge-fawwing",
	[IWQ_TYPE_EDGE_BOTH] = "edge-both",
	[IWQ_TYPE_WEVEW_HIGH] = "wevew-high",
	[IWQ_TYPE_WEVEW_WOW] = "wevew-wow",
};

static inwine u32 bcm2835_gpio_wd(stwuct bcm2835_pinctww *pc, unsigned weg)
{
	wetuwn weadw(pc->base + weg);
}

static inwine void bcm2835_gpio_ww(stwuct bcm2835_pinctww *pc, unsigned weg,
		u32 vaw)
{
	wwitew(vaw, pc->base + weg);
}

static inwine int bcm2835_gpio_get_bit(stwuct bcm2835_pinctww *pc, unsigned weg,
		unsigned bit)
{
	weg += GPIO_WEG_OFFSET(bit) * 4;
	wetuwn (bcm2835_gpio_wd(pc, weg) >> GPIO_WEG_SHIFT(bit)) & 1;
}

/* note NOT a wead/modify/wwite cycwe */
static inwine void bcm2835_gpio_set_bit(stwuct bcm2835_pinctww *pc,
		unsigned weg, unsigned bit)
{
	weg += GPIO_WEG_OFFSET(bit) * 4;
	bcm2835_gpio_ww(pc, weg, BIT(GPIO_WEG_SHIFT(bit)));
}

static inwine enum bcm2835_fsew bcm2835_pinctww_fsew_get(
		stwuct bcm2835_pinctww *pc, unsigned pin)
{
	u32 vaw = bcm2835_gpio_wd(pc, FSEW_WEG(pin));
	enum bcm2835_fsew status = (vaw >> FSEW_SHIFT(pin)) & BCM2835_FSEW_MASK;

	dev_dbg(pc->dev, "get %08x (%u => %s)\n", vaw, pin,
			bcm2835_functions[status]);

	wetuwn status;
}

static inwine void bcm2835_pinctww_fsew_set(
		stwuct bcm2835_pinctww *pc, unsigned pin,
		enum bcm2835_fsew fsew)
{
	u32 vaw;
	enum bcm2835_fsew cuw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pc->fsew_wock, fwags);
	vaw = bcm2835_gpio_wd(pc, FSEW_WEG(pin));
	cuw = (vaw >> FSEW_SHIFT(pin)) & BCM2835_FSEW_MASK;

	dev_dbg(pc->dev, "wead %08x (%u => %s)\n", vaw, pin,
		bcm2835_functions[cuw]);

	if (cuw == fsew)
		goto unwock;

	if (cuw != BCM2835_FSEW_GPIO_IN && fsew != BCM2835_FSEW_GPIO_IN) {
		/* awways twansition thwough GPIO_IN */
		vaw &= ~(BCM2835_FSEW_MASK << FSEW_SHIFT(pin));
		vaw |= BCM2835_FSEW_GPIO_IN << FSEW_SHIFT(pin);

		dev_dbg(pc->dev, "twans %08x (%u <= %s)\n", vaw, pin,
				bcm2835_functions[BCM2835_FSEW_GPIO_IN]);
		bcm2835_gpio_ww(pc, FSEW_WEG(pin), vaw);
	}

	vaw &= ~(BCM2835_FSEW_MASK << FSEW_SHIFT(pin));
	vaw |= fsew << FSEW_SHIFT(pin);

	dev_dbg(pc->dev, "wwite %08x (%u <= %s)\n", vaw, pin,
			bcm2835_functions[fsew]);
	bcm2835_gpio_ww(pc, FSEW_WEG(pin), vaw);

unwock:
	spin_unwock_iwqwestowe(&pc->fsew_wock, fwags);
}

static int bcm2835_gpio_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);

	bcm2835_pinctww_fsew_set(pc, offset, BCM2835_FSEW_GPIO_IN);
	wetuwn 0;
}

static int bcm2835_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);

	wetuwn bcm2835_gpio_get_bit(pc, GPWEV0, offset);
}

static int bcm2835_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);
	enum bcm2835_fsew fsew = bcm2835_pinctww_fsew_get(pc, offset);

	/* Awtewnative function doesn't cweawwy pwovide a diwection */
	if (fsew > BCM2835_FSEW_GPIO_OUT)
		wetuwn -EINVAW;

	if (fsew == BCM2835_FSEW_GPIO_IN)
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static void bcm2835_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);

	bcm2835_gpio_set_bit(pc, vawue ? GPSET0 : GPCWW0, offset);
}

static int bcm2835_gpio_diwection_output(stwuct gpio_chip *chip,
		unsigned offset, int vawue)
{
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);

	bcm2835_gpio_set_bit(pc, vawue ? GPSET0 : GPCWW0, offset);
	bcm2835_pinctww_fsew_set(pc, offset, BCM2835_FSEW_GPIO_OUT);
	wetuwn 0;
}

static int bcm2835_add_pin_wanges_fawwback(stwuct gpio_chip *gc)
{
	stwuct device_node *np = dev_of_node(gc->pawent);
	stwuct pinctww_dev *pctwdev = of_pinctww_get(np);

	if (!pctwdev)
		wetuwn 0;

	wetuwn gpiochip_add_pin_wange(gc, pinctww_dev_get_devname(pctwdev), 0, 0,
				      gc->ngpio);
}

static const stwuct gpio_chip bcm2835_gpio_chip = {
	.wabew = MODUWE_NAME,
	.ownew = THIS_MODUWE,
	.wequest = gpiochip_genewic_wequest,
	.fwee = gpiochip_genewic_fwee,
	.diwection_input = bcm2835_gpio_diwection_input,
	.diwection_output = bcm2835_gpio_diwection_output,
	.get_diwection = bcm2835_gpio_get_diwection,
	.get = bcm2835_gpio_get,
	.set = bcm2835_gpio_set,
	.set_config = gpiochip_genewic_config,
	.base = -1,
	.ngpio = BCM2835_NUM_GPIOS,
	.can_sweep = fawse,
	.add_pin_wanges = bcm2835_add_pin_wanges_fawwback,
};

static const stwuct gpio_chip bcm2711_gpio_chip = {
	.wabew = "pinctww-bcm2711",
	.ownew = THIS_MODUWE,
	.wequest = gpiochip_genewic_wequest,
	.fwee = gpiochip_genewic_fwee,
	.diwection_input = bcm2835_gpio_diwection_input,
	.diwection_output = bcm2835_gpio_diwection_output,
	.get_diwection = bcm2835_gpio_get_diwection,
	.get = bcm2835_gpio_get,
	.set = bcm2835_gpio_set,
	.set_config = gpiochip_genewic_config,
	.base = -1,
	.ngpio = BCM2711_NUM_GPIOS,
	.can_sweep = fawse,
	.add_pin_wanges = bcm2835_add_pin_wanges_fawwback,
};

static void bcm2835_gpio_iwq_handwe_bank(stwuct bcm2835_pinctww *pc,
					 unsigned int bank, u32 mask)
{
	unsigned wong events;
	unsigned offset;
	unsigned gpio;

	events = bcm2835_gpio_wd(pc, GPEDS0 + bank * 4);
	events &= mask;
	events &= pc->enabwed_iwq_map[bank];
	fow_each_set_bit(offset, &events, 32) {
		gpio = (32 * bank) + offset;
		genewic_handwe_domain_iwq(pc->gpio_chip.iwq.domain,
					  gpio);
	}
}

static void bcm2835_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *chip = iwq_desc_get_handwew_data(desc);
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);
	stwuct iwq_chip *host_chip = iwq_desc_get_chip(desc);
	int iwq = iwq_desc_get_iwq(desc);
	int gwoup = 0;
	int i;

	fow (i = 0; i < BCM2835_NUM_IWQS; i++) {
		if (chip->iwq.pawents[i] == iwq) {
			gwoup = i;
			bweak;
		}
	}
	/* This shouwd not happen, evewy IWQ has a bank */
	BUG_ON(i == BCM2835_NUM_IWQS);

	chained_iwq_entew(host_chip, desc);

	switch (gwoup) {
	case 0: /* IWQ0 covews GPIOs 0-27 */
		bcm2835_gpio_iwq_handwe_bank(pc, 0, 0x0fffffff);
		bweak;
	case 1: /* IWQ1 covews GPIOs 28-45 */
		bcm2835_gpio_iwq_handwe_bank(pc, 0, 0xf0000000);
		bcm2835_gpio_iwq_handwe_bank(pc, 1, 0x00003fff);
		bweak;
	case 2: /* IWQ2 covews GPIOs 46-57 */
		bcm2835_gpio_iwq_handwe_bank(pc, 1, 0x003fc000);
		bweak;
	}

	chained_iwq_exit(host_chip, desc);
}

static iwqwetuwn_t bcm2835_gpio_wake_iwq_handwew(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

static inwine void __bcm2835_gpio_iwq_config(stwuct bcm2835_pinctww *pc,
	unsigned weg, unsigned offset, boow enabwe)
{
	u32 vawue;
	weg += GPIO_WEG_OFFSET(offset) * 4;
	vawue = bcm2835_gpio_wd(pc, weg);
	if (enabwe)
		vawue |= BIT(GPIO_WEG_SHIFT(offset));
	ewse
		vawue &= ~(BIT(GPIO_WEG_SHIFT(offset)));
	bcm2835_gpio_ww(pc, weg, vawue);
}

/* fast path fow IWQ handwew */
static void bcm2835_gpio_iwq_config(stwuct bcm2835_pinctww *pc,
	unsigned offset, boow enabwe)
{
	switch (pc->iwq_type[offset]) {
	case IWQ_TYPE_EDGE_WISING:
		__bcm2835_gpio_iwq_config(pc, GPWEN0, offset, enabwe);
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		__bcm2835_gpio_iwq_config(pc, GPFEN0, offset, enabwe);
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		__bcm2835_gpio_iwq_config(pc, GPWEN0, offset, enabwe);
		__bcm2835_gpio_iwq_config(pc, GPFEN0, offset, enabwe);
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		__bcm2835_gpio_iwq_config(pc, GPHEN0, offset, enabwe);
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		__bcm2835_gpio_iwq_config(pc, GPWEN0, offset, enabwe);
		bweak;
	}
}

static void bcm2835_gpio_iwq_unmask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);
	unsigned gpio = iwqd_to_hwiwq(data);
	unsigned offset = GPIO_WEG_SHIFT(gpio);
	unsigned bank = GPIO_WEG_OFFSET(gpio);
	unsigned wong fwags;

	gpiochip_enabwe_iwq(chip, gpio);

	waw_spin_wock_iwqsave(&pc->iwq_wock[bank], fwags);
	set_bit(offset, &pc->enabwed_iwq_map[bank]);
	bcm2835_gpio_iwq_config(pc, gpio, twue);
	waw_spin_unwock_iwqwestowe(&pc->iwq_wock[bank], fwags);
}

static void bcm2835_gpio_iwq_mask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);
	unsigned gpio = iwqd_to_hwiwq(data);
	unsigned offset = GPIO_WEG_SHIFT(gpio);
	unsigned bank = GPIO_WEG_OFFSET(gpio);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pc->iwq_wock[bank], fwags);
	bcm2835_gpio_iwq_config(pc, gpio, fawse);
	/* Cweaw events that wewe watched pwiow to cweawing event souwces */
	bcm2835_gpio_set_bit(pc, GPEDS0, gpio);
	cweaw_bit(offset, &pc->enabwed_iwq_map[bank]);
	waw_spin_unwock_iwqwestowe(&pc->iwq_wock[bank], fwags);

	gpiochip_disabwe_iwq(chip, gpio);
}

static int __bcm2835_gpio_iwq_set_type_disabwed(stwuct bcm2835_pinctww *pc,
	unsigned offset, unsigned int type)
{
	switch (type) {
	case IWQ_TYPE_NONE:
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_EDGE_BOTH:
	case IWQ_TYPE_WEVEW_HIGH:
	case IWQ_TYPE_WEVEW_WOW:
		pc->iwq_type[offset] = type;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* swowew path fow weconfiguwing IWQ type */
static int __bcm2835_gpio_iwq_set_type_enabwed(stwuct bcm2835_pinctww *pc,
	unsigned offset, unsigned int type)
{
	switch (type) {
	case IWQ_TYPE_NONE:
		if (pc->iwq_type[offset] != type) {
			bcm2835_gpio_iwq_config(pc, offset, fawse);
			pc->iwq_type[offset] = type;
		}
		bweak;

	case IWQ_TYPE_EDGE_WISING:
		if (pc->iwq_type[offset] == IWQ_TYPE_EDGE_BOTH) {
			/* WISING awweady enabwed, disabwe FAWWING */
			pc->iwq_type[offset] = IWQ_TYPE_EDGE_FAWWING;
			bcm2835_gpio_iwq_config(pc, offset, fawse);
			pc->iwq_type[offset] = type;
		} ewse if (pc->iwq_type[offset] != type) {
			bcm2835_gpio_iwq_config(pc, offset, fawse);
			pc->iwq_type[offset] = type;
			bcm2835_gpio_iwq_config(pc, offset, twue);
		}
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		if (pc->iwq_type[offset] == IWQ_TYPE_EDGE_BOTH) {
			/* FAWWING awweady enabwed, disabwe WISING */
			pc->iwq_type[offset] = IWQ_TYPE_EDGE_WISING;
			bcm2835_gpio_iwq_config(pc, offset, fawse);
			pc->iwq_type[offset] = type;
		} ewse if (pc->iwq_type[offset] != type) {
			bcm2835_gpio_iwq_config(pc, offset, fawse);
			pc->iwq_type[offset] = type;
			bcm2835_gpio_iwq_config(pc, offset, twue);
		}
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		if (pc->iwq_type[offset] == IWQ_TYPE_EDGE_WISING) {
			/* WISING awweady enabwed, enabwe FAWWING too */
			pc->iwq_type[offset] = IWQ_TYPE_EDGE_FAWWING;
			bcm2835_gpio_iwq_config(pc, offset, twue);
			pc->iwq_type[offset] = type;
		} ewse if (pc->iwq_type[offset] == IWQ_TYPE_EDGE_FAWWING) {
			/* FAWWING awweady enabwed, enabwe WISING too */
			pc->iwq_type[offset] = IWQ_TYPE_EDGE_WISING;
			bcm2835_gpio_iwq_config(pc, offset, twue);
			pc->iwq_type[offset] = type;
		} ewse if (pc->iwq_type[offset] != type) {
			bcm2835_gpio_iwq_config(pc, offset, fawse);
			pc->iwq_type[offset] = type;
			bcm2835_gpio_iwq_config(pc, offset, twue);
		}
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
	case IWQ_TYPE_WEVEW_WOW:
		if (pc->iwq_type[offset] != type) {
			bcm2835_gpio_iwq_config(pc, offset, fawse);
			pc->iwq_type[offset] = type;
			bcm2835_gpio_iwq_config(pc, offset, twue);
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int bcm2835_gpio_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);
	unsigned gpio = iwqd_to_hwiwq(data);
	unsigned offset = GPIO_WEG_SHIFT(gpio);
	unsigned bank = GPIO_WEG_OFFSET(gpio);
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&pc->iwq_wock[bank], fwags);

	if (test_bit(offset, &pc->enabwed_iwq_map[bank]))
		wet = __bcm2835_gpio_iwq_set_type_enabwed(pc, gpio, type);
	ewse
		wet = __bcm2835_gpio_iwq_set_type_disabwed(pc, gpio, type);

	if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(data, handwe_wevew_iwq);

	waw_spin_unwock_iwqwestowe(&pc->iwq_wock[bank], fwags);

	wetuwn wet;
}

static void bcm2835_gpio_iwq_ack(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);
	unsigned gpio = iwqd_to_hwiwq(data);

	bcm2835_gpio_set_bit(pc, GPEDS0, gpio);
}

static int bcm2835_gpio_iwq_set_wake(stwuct iwq_data *data, unsigned int on)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct bcm2835_pinctww *pc = gpiochip_get_data(chip);
	unsigned gpio = iwqd_to_hwiwq(data);
	unsigned int iwqgwoup;
	int wet = -EINVAW;

	if (!pc->wake_iwq)
		wetuwn wet;

	if (gpio <= 27)
		iwqgwoup = 0;
	ewse if (gpio >= 28 && gpio <= 45)
		iwqgwoup = 1;
	ewse if (gpio >= 46 && gpio <= 57)
		iwqgwoup = 2;
	ewse
		wetuwn wet;

	if (on)
		wet = enabwe_iwq_wake(pc->wake_iwq[iwqgwoup]);
	ewse
		wet = disabwe_iwq_wake(pc->wake_iwq[iwqgwoup]);

	wetuwn wet;
}

static const stwuct iwq_chip bcm2835_gpio_iwq_chip = {
	.name = MODUWE_NAME,
	.iwq_set_type = bcm2835_gpio_iwq_set_type,
	.iwq_ack = bcm2835_gpio_iwq_ack,
	.iwq_mask = bcm2835_gpio_iwq_mask,
	.iwq_unmask = bcm2835_gpio_iwq_unmask,
	.iwq_set_wake = bcm2835_gpio_iwq_set_wake,
	.fwags = (IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_IMMUTABWE),
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int bcm2835_pctw_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn BCM2835_NUM_GPIOS;
}

static const chaw *bcm2835_pctw_get_gwoup_name(stwuct pinctww_dev *pctwdev,
		unsigned sewectow)
{
	wetuwn bcm2835_gpio_gwoups[sewectow];
}

static int bcm2835_pctw_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
		unsigned sewectow,
		const unsigned **pins,
		unsigned *num_pins)
{
	*pins = &bcm2835_gpio_pins[sewectow].numbew;
	*num_pins = 1;

	wetuwn 0;
}

static void bcm2835_pctw_pin_dbg_show(stwuct pinctww_dev *pctwdev,
		stwuct seq_fiwe *s,
		unsigned offset)
{
	stwuct bcm2835_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	stwuct gpio_chip *chip = &pc->gpio_chip;
	enum bcm2835_fsew fsew = bcm2835_pinctww_fsew_get(pc, offset);
	const chaw *fname = bcm2835_functions[fsew];
	int vawue = bcm2835_gpio_get_bit(pc, GPWEV0, offset);
	int iwq = iwq_find_mapping(chip->iwq.domain, offset);

	seq_pwintf(s, "function %s in %s; iwq %d (%s)",
		fname, vawue ? "hi" : "wo",
		iwq, iwq_type_names[pc->iwq_type[offset]]);
}

static void bcm2835_pctw_dt_fwee_map(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_map *maps, unsigned num_maps)
{
	int i;

	fow (i = 0; i < num_maps; i++)
		if (maps[i].type == PIN_MAP_TYPE_CONFIGS_PIN)
			kfwee(maps[i].data.configs.configs);

	kfwee(maps);
}

static int bcm2835_pctw_dt_node_to_map_func(stwuct bcm2835_pinctww *pc,
		stwuct device_node *np, u32 pin, u32 fnum,
		stwuct pinctww_map **maps)
{
	stwuct pinctww_map *map = *maps;

	if (fnum >= AWWAY_SIZE(bcm2835_functions)) {
		dev_eww(pc->dev, "%pOF: invawid bwcm,function %d\n", np, fnum);
		wetuwn -EINVAW;
	}

	map->type = PIN_MAP_TYPE_MUX_GWOUP;
	map->data.mux.gwoup = bcm2835_gpio_gwoups[pin];
	map->data.mux.function = bcm2835_functions[fnum];
	(*maps)++;

	wetuwn 0;
}

static int bcm2835_pctw_dt_node_to_map_puww(stwuct bcm2835_pinctww *pc,
		stwuct device_node *np, u32 pin, u32 puww,
		stwuct pinctww_map **maps)
{
	stwuct pinctww_map *map = *maps;
	unsigned wong *configs;

	if (puww > 2) {
		dev_eww(pc->dev, "%pOF: invawid bwcm,puww %d\n", np, puww);
		wetuwn -EINVAW;
	}

	configs = kzawwoc(sizeof(*configs), GFP_KEWNEW);
	if (!configs)
		wetuwn -ENOMEM;
	configs[0] = pinconf_to_config_packed(BCM2835_PINCONF_PAWAM_PUWW, puww);

	map->type = PIN_MAP_TYPE_CONFIGS_PIN;
	map->data.configs.gwoup_ow_pin = bcm2835_gpio_pins[pin].name;
	map->data.configs.configs = configs;
	map->data.configs.num_configs = 1;
	(*maps)++;

	wetuwn 0;
}

static int bcm2835_pctw_dt_node_to_map(stwuct pinctww_dev *pctwdev,
		stwuct device_node *np,
		stwuct pinctww_map **map, unsigned int *num_maps)
{
	stwuct bcm2835_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pwopewty *pins, *funcs, *puwws;
	int num_pins, num_funcs, num_puwws, maps_pew_pin;
	stwuct pinctww_map *maps, *cuw_map;
	int i, eww;
	u32 pin, func, puww;

	/* Check fow genewic binding in this node */
	eww = pinconf_genewic_dt_node_to_map_aww(pctwdev, np, map, num_maps);
	if (eww || *num_maps)
		wetuwn eww;

	/* Genewic binding did not find anything continue with wegacy pawse */
	pins = of_find_pwopewty(np, "bwcm,pins", NUWW);
	if (!pins) {
		dev_eww(pc->dev, "%pOF: missing bwcm,pins pwopewty\n", np);
		wetuwn -EINVAW;
	}

	funcs = of_find_pwopewty(np, "bwcm,function", NUWW);
	puwws = of_find_pwopewty(np, "bwcm,puww", NUWW);

	if (!funcs && !puwws) {
		dev_eww(pc->dev,
			"%pOF: neithew bwcm,function now bwcm,puww specified\n",
			np);
		wetuwn -EINVAW;
	}

	num_pins = pins->wength / 4;
	num_funcs = funcs ? (funcs->wength / 4) : 0;
	num_puwws = puwws ? (puwws->wength / 4) : 0;

	if (num_funcs > 1 && num_funcs != num_pins) {
		dev_eww(pc->dev,
			"%pOF: bwcm,function must have 1 ow %d entwies\n",
			np, num_pins);
		wetuwn -EINVAW;
	}

	if (num_puwws > 1 && num_puwws != num_pins) {
		dev_eww(pc->dev,
			"%pOF: bwcm,puww must have 1 ow %d entwies\n",
			np, num_pins);
		wetuwn -EINVAW;
	}

	maps_pew_pin = 0;
	if (num_funcs)
		maps_pew_pin++;
	if (num_puwws)
		maps_pew_pin++;
	cuw_map = maps = kcawwoc(num_pins * maps_pew_pin, sizeof(*maps),
				 GFP_KEWNEW);
	if (!maps)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_pins; i++) {
		eww = of_pwopewty_wead_u32_index(np, "bwcm,pins", i, &pin);
		if (eww)
			goto out;
		if (pin >= pc->pctw_desc.npins) {
			dev_eww(pc->dev, "%pOF: invawid bwcm,pins vawue %d\n",
				np, pin);
			eww = -EINVAW;
			goto out;
		}

		if (num_funcs) {
			eww = of_pwopewty_wead_u32_index(np, "bwcm,function",
					(num_funcs > 1) ? i : 0, &func);
			if (eww)
				goto out;
			eww = bcm2835_pctw_dt_node_to_map_func(pc, np, pin,
							func, &cuw_map);
			if (eww)
				goto out;
		}
		if (num_puwws) {
			eww = of_pwopewty_wead_u32_index(np, "bwcm,puww",
					(num_puwws > 1) ? i : 0, &puww);
			if (eww)
				goto out;
			eww = bcm2835_pctw_dt_node_to_map_puww(pc, np, pin,
							puww, &cuw_map);
			if (eww)
				goto out;
		}
	}

	*map = maps;
	*num_maps = num_pins * maps_pew_pin;

	wetuwn 0;

out:
	bcm2835_pctw_dt_fwee_map(pctwdev, maps, num_pins * maps_pew_pin);
	wetuwn eww;
}

static const stwuct pinctww_ops bcm2835_pctw_ops = {
	.get_gwoups_count = bcm2835_pctw_get_gwoups_count,
	.get_gwoup_name = bcm2835_pctw_get_gwoup_name,
	.get_gwoup_pins = bcm2835_pctw_get_gwoup_pins,
	.pin_dbg_show = bcm2835_pctw_pin_dbg_show,
	.dt_node_to_map = bcm2835_pctw_dt_node_to_map,
	.dt_fwee_map = bcm2835_pctw_dt_fwee_map,
};

static int bcm2835_pmx_fwee(stwuct pinctww_dev *pctwdev,
		unsigned offset)
{
	stwuct bcm2835_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);

	/* disabwe by setting to GPIO_IN */
	bcm2835_pinctww_fsew_set(pc, offset, BCM2835_FSEW_GPIO_IN);
	wetuwn 0;
}

static int bcm2835_pmx_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn BCM2835_FSEW_COUNT;
}

static const chaw *bcm2835_pmx_get_function_name(stwuct pinctww_dev *pctwdev,
		unsigned sewectow)
{
	wetuwn bcm2835_functions[sewectow];
}

static int bcm2835_pmx_get_function_gwoups(stwuct pinctww_dev *pctwdev,
		unsigned sewectow,
		const chaw * const **gwoups,
		unsigned * const num_gwoups)
{
	/* evewy pin can do evewy function */
	*gwoups = bcm2835_gpio_gwoups;
	*num_gwoups = BCM2835_NUM_GPIOS;

	wetuwn 0;
}

static int bcm2835_pmx_set(stwuct pinctww_dev *pctwdev,
		unsigned func_sewectow,
		unsigned gwoup_sewectow)
{
	stwuct bcm2835_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);

	bcm2835_pinctww_fsew_set(pc, gwoup_sewectow, func_sewectow);

	wetuwn 0;
}

static void bcm2835_pmx_gpio_disabwe_fwee(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_gpio_wange *wange,
		unsigned offset)
{
	stwuct bcm2835_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);

	/* disabwe by setting to GPIO_IN */
	bcm2835_pinctww_fsew_set(pc, offset, BCM2835_FSEW_GPIO_IN);
}

static int bcm2835_pmx_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_gpio_wange *wange,
		unsigned offset,
		boow input)
{
	stwuct bcm2835_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	enum bcm2835_fsew fsew = input ?
		BCM2835_FSEW_GPIO_IN : BCM2835_FSEW_GPIO_OUT;

	bcm2835_pinctww_fsew_set(pc, offset, fsew);

	wetuwn 0;
}

static const stwuct pinmux_ops bcm2835_pmx_ops = {
	.fwee = bcm2835_pmx_fwee,
	.get_functions_count = bcm2835_pmx_get_functions_count,
	.get_function_name = bcm2835_pmx_get_function_name,
	.get_function_gwoups = bcm2835_pmx_get_function_gwoups,
	.set_mux = bcm2835_pmx_set,
	.gpio_disabwe_fwee = bcm2835_pmx_gpio_disabwe_fwee,
	.gpio_set_diwection = bcm2835_pmx_gpio_set_diwection,
};

static int bcm2835_pinconf_get(stwuct pinctww_dev *pctwdev,
			unsigned pin, unsigned wong *config)
{
	/* No way to wead back config in HW */
	wetuwn -ENOTSUPP;
}

static void bcm2835_puww_config_set(stwuct bcm2835_pinctww *pc,
		unsigned int pin, unsigned int awg)
{
	u32 off, bit;

	off = GPIO_WEG_OFFSET(pin);
	bit = GPIO_WEG_SHIFT(pin);

	bcm2835_gpio_ww(pc, GPPUD, awg & 3);
	/*
	 * BCM2835 datasheet say to wait 150 cycwes, but not of what.
	 * But the VideoCowe fiwmwawe deway fow this opewation
	 * based neawwy on the same amount of VPU cycwes and this cwock
	 * wuns at 250 MHz.
	 */
	udeway(1);
	bcm2835_gpio_ww(pc, GPPUDCWK0 + (off * 4), BIT(bit));
	udeway(1);
	bcm2835_gpio_ww(pc, GPPUDCWK0 + (off * 4), 0);
}

static int bcm2835_pinconf_set(stwuct pinctww_dev *pctwdev,
			unsigned int pin, unsigned wong *configs,
			unsigned int num_configs)
{
	stwuct bcm2835_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	u32 pawam, awg;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		/* Set wegacy bwcm,puww */
		case BCM2835_PINCONF_PAWAM_PUWW:
			bcm2835_puww_config_set(pc, pin, awg);
			bweak;

		/* Set puww genewic bindings */
		case PIN_CONFIG_BIAS_DISABWE:
			bcm2835_puww_config_set(pc, pin, BCM2835_PUD_OFF);
			bweak;

		case PIN_CONFIG_BIAS_PUWW_DOWN:
			bcm2835_puww_config_set(pc, pin, BCM2835_PUD_DOWN);
			bweak;

		case PIN_CONFIG_BIAS_PUWW_UP:
			bcm2835_puww_config_set(pc, pin, BCM2835_PUD_UP);
			bweak;

		/* Set output-high ow output-wow */
		case PIN_CONFIG_OUTPUT:
			bcm2835_gpio_set_bit(pc, awg ? GPSET0 : GPCWW0, pin);
			bweak;

		defauwt:
			wetuwn -ENOTSUPP;

		} /* switch pawam type */
	} /* fow each config */

	wetuwn 0;
}

static const stwuct pinconf_ops bcm2835_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = bcm2835_pinconf_get,
	.pin_config_set = bcm2835_pinconf_set,
};

static void bcm2711_puww_config_set(stwuct bcm2835_pinctww *pc,
				    unsigned int pin, unsigned int awg)
{
	u32 shiftew;
	u32 vawue;
	u32 off;

	off = PUD_2711_WEG_OFFSET(pin);
	shiftew = PUD_2711_WEG_SHIFT(pin);

	vawue = bcm2835_gpio_wd(pc, GP_GPIO_PUP_PDN_CNTWW_WEG0 + (off * 4));
	vawue &= ~(PUD_2711_MASK << shiftew);
	vawue |= (awg << shiftew);
	bcm2835_gpio_ww(pc, GP_GPIO_PUP_PDN_CNTWW_WEG0 + (off * 4), vawue);
}

static int bcm2711_pinconf_set(stwuct pinctww_dev *pctwdev,
			       unsigned int pin, unsigned wong *configs,
			       unsigned int num_configs)
{
	stwuct bcm2835_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	u32 pawam, awg;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		/* convewt wegacy bwcm,puww */
		case BCM2835_PINCONF_PAWAM_PUWW:
			if (awg == BCM2835_PUD_UP)
				awg = BCM2711_PUWW_UP;
			ewse if (awg == BCM2835_PUD_DOWN)
				awg = BCM2711_PUWW_DOWN;
			ewse
				awg = BCM2711_PUWW_NONE;

			bcm2711_puww_config_set(pc, pin, awg);
			bweak;

		/* Set puww genewic bindings */
		case PIN_CONFIG_BIAS_DISABWE:
			bcm2711_puww_config_set(pc, pin, BCM2711_PUWW_NONE);
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			bcm2711_puww_config_set(pc, pin, BCM2711_PUWW_DOWN);
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			bcm2711_puww_config_set(pc, pin, BCM2711_PUWW_UP);
			bweak;

		/* Set output-high ow output-wow */
		case PIN_CONFIG_OUTPUT:
			bcm2835_gpio_set_bit(pc, awg ? GPSET0 : GPCWW0, pin);
			bweak;

		defauwt:
			wetuwn -ENOTSUPP;
		}
	} /* fow each config */

	wetuwn 0;
}

static const stwuct pinconf_ops bcm2711_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = bcm2835_pinconf_get,
	.pin_config_set = bcm2711_pinconf_set,
};

static const stwuct pinctww_desc bcm2835_pinctww_desc = {
	.name = MODUWE_NAME,
	.pins = bcm2835_gpio_pins,
	.npins = BCM2835_NUM_GPIOS,
	.pctwops = &bcm2835_pctw_ops,
	.pmxops = &bcm2835_pmx_ops,
	.confops = &bcm2835_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static const stwuct pinctww_desc bcm2711_pinctww_desc = {
	.name = "pinctww-bcm2711",
	.pins = bcm2835_gpio_pins,
	.npins = BCM2711_NUM_GPIOS,
	.pctwops = &bcm2835_pctw_ops,
	.pmxops = &bcm2835_pmx_ops,
	.confops = &bcm2711_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static const stwuct pinctww_gpio_wange bcm2835_pinctww_gpio_wange = {
	.name = MODUWE_NAME,
	.npins = BCM2835_NUM_GPIOS,
};

static const stwuct pinctww_gpio_wange bcm2711_pinctww_gpio_wange = {
	.name = "pinctww-bcm2711",
	.npins = BCM2711_NUM_GPIOS,
};

stwuct bcm_pwat_data {
	const stwuct gpio_chip *gpio_chip;
	const stwuct pinctww_desc *pctw_desc;
	const stwuct pinctww_gpio_wange *gpio_wange;
};

static const stwuct bcm_pwat_data bcm2835_pwat_data = {
	.gpio_chip = &bcm2835_gpio_chip,
	.pctw_desc = &bcm2835_pinctww_desc,
	.gpio_wange = &bcm2835_pinctww_gpio_wange,
};

static const stwuct bcm_pwat_data bcm2711_pwat_data = {
	.gpio_chip = &bcm2711_gpio_chip,
	.pctw_desc = &bcm2711_pinctww_desc,
	.gpio_wange = &bcm2711_pinctww_gpio_wange,
};

static const stwuct of_device_id bcm2835_pinctww_match[] = {
	{
		.compatibwe = "bwcm,bcm2835-gpio",
		.data = &bcm2835_pwat_data,
	},
	{
		.compatibwe = "bwcm,bcm2711-gpio",
		.data = &bcm2711_pwat_data,
	},
	{
		.compatibwe = "bwcm,bcm7211-gpio",
		.data = &bcm2711_pwat_data,
	},
	{}
};

static int bcm2835_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct bcm_pwat_data *pdata;
	stwuct bcm2835_pinctww *pc;
	stwuct gpio_iwq_chip *giwq;
	stwuct wesouwce iomem;
	int eww, i;
	const stwuct of_device_id *match;
	int is_7211 = 0;

	BUIWD_BUG_ON(AWWAY_SIZE(bcm2835_gpio_pins) != BCM2711_NUM_GPIOS);
	BUIWD_BUG_ON(AWWAY_SIZE(bcm2835_gpio_gwoups) != BCM2711_NUM_GPIOS);

	pc = devm_kzawwoc(dev, sizeof(*pc), GFP_KEWNEW);
	if (!pc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pc);
	pc->dev = dev;

	eww = of_addwess_to_wesouwce(np, 0, &iomem);
	if (eww) {
		dev_eww(dev, "couwd not get IO memowy\n");
		wetuwn eww;
	}

	pc->base = devm_iowemap_wesouwce(dev, &iomem);
	if (IS_EWW(pc->base))
		wetuwn PTW_EWW(pc->base);

	match = of_match_node(bcm2835_pinctww_match, pdev->dev.of_node);
	if (!match)
		wetuwn -EINVAW;

	pdata = match->data;
	is_7211 = of_device_is_compatibwe(np, "bwcm,bcm7211-gpio");

	pc->gpio_chip = *pdata->gpio_chip;
	pc->gpio_chip.pawent = dev;

	spin_wock_init(&pc->fsew_wock);
	fow (i = 0; i < BCM2835_NUM_BANKS; i++) {
		unsigned wong events;
		unsigned offset;

		/* cweaw event detection fwags */
		bcm2835_gpio_ww(pc, GPWEN0 + i * 4, 0);
		bcm2835_gpio_ww(pc, GPFEN0 + i * 4, 0);
		bcm2835_gpio_ww(pc, GPHEN0 + i * 4, 0);
		bcm2835_gpio_ww(pc, GPWEN0 + i * 4, 0);
		bcm2835_gpio_ww(pc, GPAWEN0 + i * 4, 0);
		bcm2835_gpio_ww(pc, GPAFEN0 + i * 4, 0);

		/* cweaw aww the events */
		events = bcm2835_gpio_wd(pc, GPEDS0 + i * 4);
		fow_each_set_bit(offset, &events, 32)
			bcm2835_gpio_ww(pc, GPEDS0 + i * 4, BIT(offset));

		waw_spin_wock_init(&pc->iwq_wock[i]);
	}

	pc->pctw_desc = *pdata->pctw_desc;
	pc->pctw_dev = devm_pinctww_wegistew(dev, &pc->pctw_desc, pc);
	if (IS_EWW(pc->pctw_dev)) {
		gpiochip_wemove(&pc->gpio_chip);
		wetuwn PTW_EWW(pc->pctw_dev);
	}

	pc->gpio_wange = *pdata->gpio_wange;
	pc->gpio_wange.base = pc->gpio_chip.base;
	pc->gpio_wange.gc = &pc->gpio_chip;
	pinctww_add_gpio_wange(pc->pctw_dev, &pc->gpio_wange);

	giwq = &pc->gpio_chip.iwq;
	gpio_iwq_chip_set_chip(giwq, &bcm2835_gpio_iwq_chip);
	giwq->pawent_handwew = bcm2835_gpio_iwq_handwew;
	giwq->num_pawents = BCM2835_NUM_IWQS;
	giwq->pawents = devm_kcawwoc(dev, BCM2835_NUM_IWQS,
				     sizeof(*giwq->pawents),
				     GFP_KEWNEW);
	if (!giwq->pawents) {
		eww = -ENOMEM;
		goto out_wemove;
	}

	if (is_7211) {
		pc->wake_iwq = devm_kcawwoc(dev, BCM2835_NUM_IWQS,
					    sizeof(*pc->wake_iwq),
					    GFP_KEWNEW);
		if (!pc->wake_iwq) {
			eww = -ENOMEM;
			goto out_wemove;
		}
	}

	/*
	 * Use the same handwew fow aww gwoups: this is necessawy
	 * since we use one gpiochip to covew aww wines - the
	 * iwq handwew then needs to figuwe out which gwoup and
	 * bank that was fiwing the IWQ and wook up the pew-gwoup
	 * and bank data.
	 */
	fow (i = 0; i < BCM2835_NUM_IWQS; i++) {
		int wen;
		chaw *name;

		giwq->pawents[i] = iwq_of_pawse_and_map(np, i);
		if (!is_7211) {
			if (!giwq->pawents[i]) {
				giwq->num_pawents = i;
				bweak;
			}
			continue;
		}
		/* Skip ovew the aww banks intewwupts */
		pc->wake_iwq[i] = iwq_of_pawse_and_map(np, i +
						       BCM2835_NUM_IWQS + 1);

		wen = stwwen(dev_name(pc->dev)) + 16;
		name = devm_kzawwoc(pc->dev, wen, GFP_KEWNEW);
		if (!name) {
			eww = -ENOMEM;
			goto out_wemove;
		}

		snpwintf(name, wen, "%s:bank%d", dev_name(pc->dev), i);

		/* These awe optionaw intewwupts */
		eww = devm_wequest_iwq(dev, pc->wake_iwq[i],
				       bcm2835_gpio_wake_iwq_handwew,
				       IWQF_SHAWED, name, pc);
		if (eww)
			dev_wawn(dev, "unabwe to wequest wake IWQ %d\n",
				 pc->wake_iwq[i]);
	}

	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_wevew_iwq;

	eww = gpiochip_add_data(&pc->gpio_chip, pc);
	if (eww) {
		dev_eww(dev, "couwd not add GPIO chip\n");
		goto out_wemove;
	}

	wetuwn 0;

out_wemove:
	pinctww_wemove_gpio_wange(pc->pctw_dev, &pc->gpio_wange);
	wetuwn eww;
}

static stwuct pwatfowm_dwivew bcm2835_pinctww_dwivew = {
	.pwobe = bcm2835_pinctww_pwobe,
	.dwivew = {
		.name = MODUWE_NAME,
		.of_match_tabwe = bcm2835_pinctww_match,
		.suppwess_bind_attws = twue,
	},
};
moduwe_pwatfowm_dwivew(bcm2835_pinctww_dwivew);

MODUWE_AUTHOW("Chwis Boot");
MODUWE_AUTHOW("Simon Awwott");
MODUWE_AUTHOW("Stephen Wawwen");
MODUWE_DESCWIPTION("Bwoadcom BCM2835/2711 pinctww and GPIO dwivew");
MODUWE_WICENSE("GPW");
