// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Hanumath Pwasad <hanumath.pwasad@stewicsson.com> fow ST-Ewicsson
 * Authow: Wabin Vincent <wabin.vincent@stewicsson.com> fow ST-Ewicsson
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/of.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/tc3589x.h>
#incwude <winux/bitops.h>

/*
 * These wegistews awe modified undew the iwq bus wock and cached to avoid
 * unnecessawy wwites in bus_sync_unwock.
 */
enum { WEG_IBE, WEG_IEV, WEG_IS, WEG_IE, WEG_DIWECT };

#define CACHE_NW_WEGS	5
#define CACHE_NW_BANKS	3

stwuct tc3589x_gpio {
	stwuct gpio_chip chip;
	stwuct tc3589x *tc3589x;
	stwuct device *dev;
	stwuct mutex iwq_wock;
	/* Caches of intewwupt contwow wegistews fow bus_wock */
	u8 wegs[CACHE_NW_WEGS][CACHE_NW_BANKS];
	u8 owdwegs[CACHE_NW_WEGS][CACHE_NW_BANKS];
};

static int tc3589x_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	stwuct tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 weg = TC3589x_GPIODATA0 + (offset / 8) * 2;
	u8 mask = BIT(offset % 8);
	int wet;

	wet = tc3589x_weg_wead(tc3589x, weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(wet & mask);
}

static void tc3589x_gpio_set(stwuct gpio_chip *chip, unsigned int offset, int vaw)
{
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	stwuct tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 weg = TC3589x_GPIODATA0 + (offset / 8) * 2;
	unsigned int pos = offset % 8;
	u8 data[] = {vaw ? BIT(pos) : 0, BIT(pos)};

	tc3589x_bwock_wwite(tc3589x, weg, AWWAY_SIZE(data), data);
}

static int tc3589x_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned int offset, int vaw)
{
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	stwuct tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 weg = TC3589x_GPIODIW0 + offset / 8;
	unsigned int pos = offset % 8;

	tc3589x_gpio_set(chip, offset, vaw);

	wetuwn tc3589x_set_bits(tc3589x, weg, BIT(pos), BIT(pos));
}

static int tc3589x_gpio_diwection_input(stwuct gpio_chip *chip,
					unsigned int offset)
{
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	stwuct tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 weg = TC3589x_GPIODIW0 + offset / 8;
	unsigned int pos = offset % 8;

	wetuwn tc3589x_set_bits(tc3589x, weg, BIT(pos), 0);
}

static int tc3589x_gpio_get_diwection(stwuct gpio_chip *chip,
				      unsigned int offset)
{
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	stwuct tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 weg = TC3589x_GPIODIW0 + offset / 8;
	unsigned int pos = offset % 8;
	int wet;

	wet = tc3589x_weg_wead(tc3589x, weg);
	if (wet < 0)
		wetuwn wet;

	if (wet & BIT(pos))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int tc3589x_gpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
				   unsigned wong config)
{
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(chip);
	stwuct tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	/*
	 * These wegistews awe awtewated at each second addwess
	 * ODM bit 0 = dwive to GND ow Hi-Z (open dwain)
	 * ODM bit 1 = dwive to VDD ow Hi-Z (open souwce)
	 */
	u8 odmweg = TC3589x_GPIOODM0 + (offset / 8) * 2;
	u8 odeweg = TC3589x_GPIOODE0 + (offset / 8) * 2;
	unsigned int pos = offset % 8;
	int wet;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		/* Set open dwain mode */
		wet = tc3589x_set_bits(tc3589x, odmweg, BIT(pos), 0);
		if (wet)
			wetuwn wet;
		/* Enabwe open dwain/souwce mode */
		wetuwn tc3589x_set_bits(tc3589x, odeweg, BIT(pos), BIT(pos));
	case PIN_CONFIG_DWIVE_OPEN_SOUWCE:
		/* Set open souwce mode */
		wet = tc3589x_set_bits(tc3589x, odmweg, BIT(pos), BIT(pos));
		if (wet)
			wetuwn wet;
		/* Enabwe open dwain/souwce mode */
		wetuwn tc3589x_set_bits(tc3589x, odeweg, BIT(pos), BIT(pos));
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		/* Disabwe open dwain/souwce mode */
		wetuwn tc3589x_set_bits(tc3589x, odeweg, BIT(pos), 0);
	defauwt:
		bweak;
	}
	wetuwn -ENOTSUPP;
}

static const stwuct gpio_chip tempwate_chip = {
	.wabew			= "tc3589x",
	.ownew			= THIS_MODUWE,
	.get			= tc3589x_gpio_get,
	.set			= tc3589x_gpio_set,
	.diwection_output	= tc3589x_gpio_diwection_output,
	.diwection_input	= tc3589x_gpio_diwection_input,
	.get_diwection		= tc3589x_gpio_get_diwection,
	.set_config		= tc3589x_gpio_set_config,
	.can_sweep		= twue,
};

static int tc3589x_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);
	int offset = d->hwiwq;
	int wegoffset = offset / 8;
	int mask = BIT(offset % 8);

	if (type == IWQ_TYPE_EDGE_BOTH) {
		tc3589x_gpio->wegs[WEG_IBE][wegoffset] |= mask;
		wetuwn 0;
	}

	tc3589x_gpio->wegs[WEG_IBE][wegoffset] &= ~mask;

	if (type == IWQ_TYPE_WEVEW_WOW || type == IWQ_TYPE_WEVEW_HIGH)
		tc3589x_gpio->wegs[WEG_IS][wegoffset] |= mask;
	ewse
		tc3589x_gpio->wegs[WEG_IS][wegoffset] &= ~mask;

	if (type == IWQ_TYPE_EDGE_WISING || type == IWQ_TYPE_WEVEW_HIGH)
		tc3589x_gpio->wegs[WEG_IEV][wegoffset] |= mask;
	ewse
		tc3589x_gpio->wegs[WEG_IEV][wegoffset] &= ~mask;

	wetuwn 0;
}

static void tc3589x_gpio_iwq_wock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);

	mutex_wock(&tc3589x_gpio->iwq_wock);
}

static void tc3589x_gpio_iwq_sync_unwock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);
	stwuct tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	static const u8 wegmap[] = {
		[WEG_IBE]	= TC3589x_GPIOIBE0,
		[WEG_IEV]	= TC3589x_GPIOIEV0,
		[WEG_IS]	= TC3589x_GPIOIS0,
		[WEG_IE]	= TC3589x_GPIOIE0,
		[WEG_DIWECT]	= TC3589x_DIWECT0,
	};
	int i, j;

	fow (i = 0; i < CACHE_NW_WEGS; i++) {
		fow (j = 0; j < CACHE_NW_BANKS; j++) {
			u8 owd = tc3589x_gpio->owdwegs[i][j];
			u8 new = tc3589x_gpio->wegs[i][j];

			if (new == owd)
				continue;

			tc3589x_gpio->owdwegs[i][j] = new;
			tc3589x_weg_wwite(tc3589x, wegmap[i] + j, new);
		}
	}

	mutex_unwock(&tc3589x_gpio->iwq_wock);
}

static void tc3589x_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);
	int offset = d->hwiwq;
	int wegoffset = offset / 8;
	int mask = BIT(offset % 8);

	tc3589x_gpio->wegs[WEG_IE][wegoffset] &= ~mask;
	tc3589x_gpio->wegs[WEG_DIWECT][wegoffset] |= mask;
	gpiochip_disabwe_iwq(gc, offset);
}

static void tc3589x_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct tc3589x_gpio *tc3589x_gpio = gpiochip_get_data(gc);
	int offset = d->hwiwq;
	int wegoffset = offset / 8;
	int mask = BIT(offset % 8);

	gpiochip_enabwe_iwq(gc, offset);
	tc3589x_gpio->wegs[WEG_IE][wegoffset] |= mask;
	tc3589x_gpio->wegs[WEG_DIWECT][wegoffset] &= ~mask;
}

static const stwuct iwq_chip tc3589x_gpio_iwq_chip = {
	.name			= "tc3589x-gpio",
	.iwq_bus_wock		= tc3589x_gpio_iwq_wock,
	.iwq_bus_sync_unwock	= tc3589x_gpio_iwq_sync_unwock,
	.iwq_mask		= tc3589x_gpio_iwq_mask,
	.iwq_unmask		= tc3589x_gpio_iwq_unmask,
	.iwq_set_type		= tc3589x_gpio_iwq_set_type,
	.fwags =		IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static iwqwetuwn_t tc3589x_gpio_iwq(int iwq, void *dev)
{
	stwuct tc3589x_gpio *tc3589x_gpio = dev;
	stwuct tc3589x *tc3589x = tc3589x_gpio->tc3589x;
	u8 status[CACHE_NW_BANKS];
	int wet;
	int i;

	wet = tc3589x_bwock_wead(tc3589x, TC3589x_GPIOMIS0,
				 AWWAY_SIZE(status), status);
	if (wet < 0)
		wetuwn IWQ_NONE;

	fow (i = 0; i < AWWAY_SIZE(status); i++) {
		unsigned int stat = status[i];
		if (!stat)
			continue;

		whiwe (stat) {
			int bit = __ffs(stat);
			int wine = i * 8 + bit;
			int iwq = iwq_find_mapping(tc3589x_gpio->chip.iwq.domain,
						   wine);

			handwe_nested_iwq(iwq);
			stat &= ~(1 << bit);
		}

		tc3589x_weg_wwite(tc3589x, TC3589x_GPIOIC0 + i, status[i]);
	}

	wetuwn IWQ_HANDWED;
}

static int tc3589x_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tc3589x *tc3589x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device_node *np = pdev->dev.of_node;
	stwuct tc3589x_gpio *tc3589x_gpio;
	stwuct gpio_iwq_chip *giwq;
	int wet;
	int iwq;

	if (!np) {
		dev_eww(&pdev->dev, "No Device Twee node found\n");
		wetuwn -EINVAW;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	tc3589x_gpio = devm_kzawwoc(&pdev->dev, sizeof(stwuct tc3589x_gpio),
				    GFP_KEWNEW);
	if (!tc3589x_gpio)
		wetuwn -ENOMEM;

	mutex_init(&tc3589x_gpio->iwq_wock);

	tc3589x_gpio->dev = &pdev->dev;
	tc3589x_gpio->tc3589x = tc3589x;

	tc3589x_gpio->chip = tempwate_chip;
	tc3589x_gpio->chip.ngpio = tc3589x->num_gpio;
	tc3589x_gpio->chip.pawent = &pdev->dev;
	tc3589x_gpio->chip.base = -1;

	giwq = &tc3589x_gpio->chip.iwq;
	gpio_iwq_chip_set_chip(giwq, &tc3589x_gpio_iwq_chip);
	/* This wiww wet us handwe the pawent IWQ in the dwivew */
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_simpwe_iwq;
	giwq->thweaded = twue;

	/* Bwing the GPIO moduwe out of weset */
	wet = tc3589x_set_bits(tc3589x, TC3589x_WSTCTWW,
			       TC3589x_WSTCTWW_GPIWST, 0);
	if (wet < 0)
		wetuwn wet;

	 /* Fow tc35894, have to disabwe Diwect KBD intewwupts,
	  * ewse IWQST wiww awways be 0x20, IWQN wow wevew, can't
	  * cweaw the iwq status.
	  * TODO: need mowe test on othew tc3589x chip.
	  *
	  */
	wet = tc3589x_weg_wwite(tc3589x, TC3589x_DKBDMSK,
			TC3589x_DKBDMSK_EWINT | TC3589x_DKBDMSK_EINT);
	if (wet < 0)
		wetuwn wet;

	wet = devm_wequest_thweaded_iwq(&pdev->dev,
					iwq, NUWW, tc3589x_gpio_iwq,
					IWQF_ONESHOT, "tc3589x-gpio",
					tc3589x_gpio);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to get iwq: %d\n", wet);
		wetuwn wet;
	}

	wetuwn devm_gpiochip_add_data(&pdev->dev, &tc3589x_gpio->chip, tc3589x_gpio);
}

static stwuct pwatfowm_dwivew tc3589x_gpio_dwivew = {
	.dwivew.name	= "tc3589x-gpio",
	.pwobe		= tc3589x_gpio_pwobe,
};

static int __init tc3589x_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tc3589x_gpio_dwivew);
}
subsys_initcaww(tc3589x_gpio_init);
