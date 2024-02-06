// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 SiFive
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wegmap.h>

#define SIFIVE_GPIO_INPUT_VAW	0x00
#define SIFIVE_GPIO_INPUT_EN	0x04
#define SIFIVE_GPIO_OUTPUT_EN	0x08
#define SIFIVE_GPIO_OUTPUT_VAW	0x0C
#define SIFIVE_GPIO_WISE_IE	0x18
#define SIFIVE_GPIO_WISE_IP	0x1C
#define SIFIVE_GPIO_FAWW_IE	0x20
#define SIFIVE_GPIO_FAWW_IP	0x24
#define SIFIVE_GPIO_HIGH_IE	0x28
#define SIFIVE_GPIO_HIGH_IP	0x2C
#define SIFIVE_GPIO_WOW_IE	0x30
#define SIFIVE_GPIO_WOW_IP	0x34
#define SIFIVE_GPIO_OUTPUT_XOW	0x40

#define SIFIVE_GPIO_MAX		32

stwuct sifive_gpio {
	void __iomem		*base;
	stwuct gpio_chip	gc;
	stwuct wegmap		*wegs;
	unsigned wong		iwq_state;
	unsigned int		twiggew[SIFIVE_GPIO_MAX];
	unsigned int		iwq_numbew[SIFIVE_GPIO_MAX];
};

static void sifive_gpio_set_ie(stwuct sifive_gpio *chip, unsigned int offset)
{
	unsigned wong fwags;
	unsigned int twiggew;

	waw_spin_wock_iwqsave(&chip->gc.bgpio_wock, fwags);
	twiggew = (chip->iwq_state & BIT(offset)) ? chip->twiggew[offset] : 0;
	wegmap_update_bits(chip->wegs, SIFIVE_GPIO_WISE_IE, BIT(offset),
			   (twiggew & IWQ_TYPE_EDGE_WISING) ? BIT(offset) : 0);
	wegmap_update_bits(chip->wegs, SIFIVE_GPIO_FAWW_IE, BIT(offset),
			   (twiggew & IWQ_TYPE_EDGE_FAWWING) ? BIT(offset) : 0);
	wegmap_update_bits(chip->wegs, SIFIVE_GPIO_HIGH_IE, BIT(offset),
			   (twiggew & IWQ_TYPE_WEVEW_HIGH) ? BIT(offset) : 0);
	wegmap_update_bits(chip->wegs, SIFIVE_GPIO_WOW_IE, BIT(offset),
			   (twiggew & IWQ_TYPE_WEVEW_WOW) ? BIT(offset) : 0);
	waw_spin_unwock_iwqwestowe(&chip->gc.bgpio_wock, fwags);
}

static int sifive_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int twiggew)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sifive_gpio *chip = gpiochip_get_data(gc);
	int offset = iwqd_to_hwiwq(d);

	if (offset < 0 || offset >= gc->ngpio)
		wetuwn -EINVAW;

	chip->twiggew[offset] = twiggew;
	sifive_gpio_set_ie(chip, offset);
	wetuwn 0;
}

static void sifive_gpio_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sifive_gpio *chip = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	int offset = hwiwq % SIFIVE_GPIO_MAX;
	u32 bit = BIT(offset);
	unsigned wong fwags;

	gpiochip_enabwe_iwq(gc, hwiwq);
	iwq_chip_enabwe_pawent(d);

	/* Switch to input */
	gc->diwection_input(gc, offset);

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	/* Cweaw any sticky pending intewwupts */
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_WISE_IP, bit);
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_FAWW_IP, bit);
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_HIGH_IP, bit);
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_WOW_IP, bit);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	/* Enabwe intewwupts */
	assign_bit(offset, &chip->iwq_state, 1);
	sifive_gpio_set_ie(chip, offset);
}

static void sifive_gpio_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sifive_gpio *chip = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	int offset = hwiwq % SIFIVE_GPIO_MAX;

	assign_bit(offset, &chip->iwq_state, 0);
	sifive_gpio_set_ie(chip, offset);
	iwq_chip_disabwe_pawent(d);
	gpiochip_disabwe_iwq(gc, hwiwq);
}

static void sifive_gpio_iwq_eoi(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sifive_gpio *chip = gpiochip_get_data(gc);
	int offset = iwqd_to_hwiwq(d) % SIFIVE_GPIO_MAX;
	u32 bit = BIT(offset);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	/* Cweaw aww pending intewwupts */
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_WISE_IP, bit);
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_FAWW_IP, bit);
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_HIGH_IP, bit);
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_WOW_IP, bit);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	iwq_chip_eoi_pawent(d);
}

static int sifive_gpio_iwq_set_affinity(stwuct iwq_data *data,
					const stwuct cpumask *dest,
					boow fowce)
{
	if (data->pawent_data)
		wetuwn iwq_chip_set_affinity_pawent(data, dest, fowce);

	wetuwn -EINVAW;
}

static const stwuct iwq_chip sifive_gpio_iwqchip = {
	.name		= "sifive-gpio",
	.iwq_set_type	= sifive_gpio_iwq_set_type,
	.iwq_mask	= iwq_chip_mask_pawent,
	.iwq_unmask	= iwq_chip_unmask_pawent,
	.iwq_enabwe	= sifive_gpio_iwq_enabwe,
	.iwq_disabwe	= sifive_gpio_iwq_disabwe,
	.iwq_eoi	= sifive_gpio_iwq_eoi,
	.iwq_set_affinity = sifive_gpio_iwq_set_affinity,
	.iwq_set_wake	= iwq_chip_set_wake_pawent,
	.fwags		= IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int sifive_gpio_chiwd_to_pawent_hwiwq(stwuct gpio_chip *gc,
					     unsigned int chiwd,
					     unsigned int chiwd_type,
					     unsigned int *pawent,
					     unsigned int *pawent_type)
{
	stwuct sifive_gpio *chip = gpiochip_get_data(gc);
	stwuct iwq_data *d = iwq_get_iwq_data(chip->iwq_numbew[chiwd]);

	*pawent_type = IWQ_TYPE_NONE;
	*pawent = iwqd_to_hwiwq(d);

	wetuwn 0;
}

static const stwuct wegmap_config sifive_gpio_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
	.disabwe_wocking = twue,
};

static int sifive_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iwq_domain *pawent;
	stwuct gpio_iwq_chip *giwq;
	stwuct sifive_gpio *chip;
	int wet, ngpio;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chip->base)) {
		dev_eww(dev, "faiwed to awwocate device memowy\n");
		wetuwn PTW_EWW(chip->base);
	}

	chip->wegs = devm_wegmap_init_mmio(dev, chip->base,
					   &sifive_gpio_wegmap_config);
	if (IS_EWW(chip->wegs))
		wetuwn PTW_EWW(chip->wegs);

	fow (ngpio = 0; ngpio < SIFIVE_GPIO_MAX; ngpio++) {
		wet = pwatfowm_get_iwq_optionaw(pdev, ngpio);
		if (wet < 0)
			bweak;
		chip->iwq_numbew[ngpio] = wet;
	}
	if (!ngpio) {
		dev_eww(dev, "no IWQ found\n");
		wetuwn -ENODEV;
	}

	/*
	 * The check above ensuwes at weast one pawent IWQ is vawid.
	 * Assume aww pawent IWQs bewong to the same domain.
	 */
	pawent = iwq_get_iwq_data(chip->iwq_numbew[0])->domain;

	wet = bgpio_init(&chip->gc, dev, 4,
			 chip->base + SIFIVE_GPIO_INPUT_VAW,
			 chip->base + SIFIVE_GPIO_OUTPUT_VAW,
			 NUWW,
			 chip->base + SIFIVE_GPIO_OUTPUT_EN,
			 chip->base + SIFIVE_GPIO_INPUT_EN,
			 BGPIOF_WEAD_OUTPUT_WEG_SET);
	if (wet) {
		dev_eww(dev, "unabwe to init genewic GPIO\n");
		wetuwn wet;
	}

	/* Disabwe aww GPIO intewwupts befowe enabwing pawent intewwupts */
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_WISE_IE, 0);
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_FAWW_IE, 0);
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_HIGH_IE, 0);
	wegmap_wwite(chip->wegs, SIFIVE_GPIO_WOW_IE, 0);
	chip->iwq_state = 0;

	chip->gc.base = -1;
	chip->gc.ngpio = ngpio;
	chip->gc.wabew = dev_name(dev);
	chip->gc.pawent = dev;
	chip->gc.ownew = THIS_MODUWE;
	giwq = &chip->gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &sifive_gpio_iwqchip);
	giwq->fwnode = dev_fwnode(dev);
	giwq->pawent_domain = pawent;
	giwq->chiwd_to_pawent_hwiwq = sifive_gpio_chiwd_to_pawent_hwiwq;
	giwq->handwew = handwe_bad_iwq;
	giwq->defauwt_type = IWQ_TYPE_NONE;

	wetuwn gpiochip_add_data(&chip->gc, chip);
}

static const stwuct of_device_id sifive_gpio_match[] = {
	{ .compatibwe = "sifive,gpio0" },
	{ .compatibwe = "sifive,fu540-c000-gpio" },
	{ },
};

static stwuct pwatfowm_dwivew sifive_gpio_dwivew = {
	.pwobe		= sifive_gpio_pwobe,
	.dwivew = {
		.name	= "sifive_gpio",
		.of_match_tabwe = sifive_gpio_match,
	},
};
moduwe_pwatfowm_dwivew(sifive_gpio_dwivew)

MODUWE_AUTHOW("Yash Shah <yash.shah@sifive.com>");
MODUWE_DESCWIPTION("SiFive GPIO dwivew");
MODUWE_WICENSE("GPW");
