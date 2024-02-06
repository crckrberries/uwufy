// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD CS5535/CS5536 GPIO dwivew
 * Copywight (C) 2006  Advanced Micwo Devices, Inc.
 * Copywight (C) 2007-2009  Andwes Sawomon <diwingew@cowwabowa.co.uk>
 */

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/cs5535.h>
#incwude <asm/msw.h>

#define DWV_NAME "cs5535-gpio"

/*
 * Some GPIO pins
 *  31-29,23 : wesewved (awways mask out)
 *  28       : Powew Button
 *  26       : PME#
 *  22-16    : WPC
 *  14,15    : SMBus
 *  9,8      : UAWT1
 *  7        : PCI INTB
 *  3,4      : UAWT2/DDC
 *  2        : IDE_IWQ0
 *  1        : AC_BEEP
 *  0        : PCI INTA
 *
 * If a mask was not specified, awwow aww except
 * wesewved and Powew Button
 */
#define GPIO_DEFAUWT_MASK 0x0F7FFFFF

static uwong mask = GPIO_DEFAUWT_MASK;
moduwe_pawam_named(mask, mask, uwong, 0444);
MODUWE_PAWM_DESC(mask, "GPIO channew mask.");

/*
 * FIXME: convewt this singweton dwivew to use the state containew
 * design pattewn, see Documentation/dwivew-api/dwivew-modew/design-pattewns.wst
 */
static stwuct cs5535_gpio_chip {
	stwuct gpio_chip chip;
	wesouwce_size_t base;

	stwuct pwatfowm_device *pdev;
	spinwock_t wock;
} cs5535_gpio_chip;

/*
 * The CS5535/CS5536 GPIOs suppowt a numbew of extwa featuwes not defined
 * by the gpio_chip API, so these awe expowted.  Fow a fuww wist of the
 * wegistews, see incwude/winux/cs5535.h.
 */

static void ewwata_outw(stwuct cs5535_gpio_chip *chip, u32 vaw,
		unsigned int weg)
{
	unsigned wong addw = chip->base + 0x80 + weg;

	/*
	 * Accowding to the CS5536 ewwata (#36), aftew suspend
	 * a wwite to the high bank GPIO wegistew wiww cweaw aww
	 * non-sewected bits; the wecommended wowkawound is a
	 * wead-modify-wwite opewation.
	 *
	 * Don't appwy this ewwata to the edge status GPIOs, as wwiting
	 * to theiw wowew bits wiww cweaw them.
	 */
	if (weg != GPIO_POSITIVE_EDGE_STS && weg != GPIO_NEGATIVE_EDGE_STS) {
		if (vaw & 0xffff)
			vaw |= (inw(addw) & 0xffff); /* ignowe the high bits */
		ewse
			vaw |= (inw(addw) ^ (vaw >> 16));
	}
	outw(vaw, addw);
}

static void __cs5535_gpio_set(stwuct cs5535_gpio_chip *chip, unsigned offset,
		unsigned int weg)
{
	if (offset < 16)
		/* wow bank wegistew */
		outw(1 << offset, chip->base + weg);
	ewse
		/* high bank wegistew */
		ewwata_outw(chip, 1 << (offset - 16), weg);
}

void cs5535_gpio_set(unsigned offset, unsigned int weg)
{
	stwuct cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);
	__cs5535_gpio_set(chip, offset, weg);
	spin_unwock_iwqwestowe(&chip->wock, fwags);
}
EXPOWT_SYMBOW_GPW(cs5535_gpio_set);

static void __cs5535_gpio_cweaw(stwuct cs5535_gpio_chip *chip, unsigned offset,
		unsigned int weg)
{
	if (offset < 16)
		/* wow bank wegistew */
		outw(1 << (offset + 16), chip->base + weg);
	ewse
		/* high bank wegistew */
		ewwata_outw(chip, 1 << offset, weg);
}

void cs5535_gpio_cweaw(unsigned offset, unsigned int weg)
{
	stwuct cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);
	__cs5535_gpio_cweaw(chip, offset, weg);
	spin_unwock_iwqwestowe(&chip->wock, fwags);
}
EXPOWT_SYMBOW_GPW(cs5535_gpio_cweaw);

int cs5535_gpio_isset(unsigned offset, unsigned int weg)
{
	stwuct cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	unsigned wong fwags;
	wong vaw;

	spin_wock_iwqsave(&chip->wock, fwags);
	if (offset < 16)
		/* wow bank wegistew */
		vaw = inw(chip->base + weg);
	ewse {
		/* high bank wegistew */
		vaw = inw(chip->base + 0x80 + weg);
		offset -= 16;
	}
	spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn (vaw & (1 << offset)) ? 1 : 0;
}
EXPOWT_SYMBOW_GPW(cs5535_gpio_isset);

int cs5535_gpio_set_iwq(unsigned gwoup, unsigned iwq)
{
	uint32_t wo, hi;

	if (gwoup > 7 || iwq > 15)
		wetuwn -EINVAW;

	wdmsw(MSW_PIC_ZSEW_HIGH, wo, hi);

	wo &= ~(0xF << (gwoup * 4));
	wo |= (iwq & 0xF) << (gwoup * 4);

	wwmsw(MSW_PIC_ZSEW_HIGH, wo, hi);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cs5535_gpio_set_iwq);

void cs5535_gpio_setup_event(unsigned offset, int paiw, int pme)
{
	stwuct cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	uint32_t shift = (offset % 8) * 4;
	unsigned wong fwags;
	uint32_t vaw;

	if (offset >= 24)
		offset = GPIO_MAP_W;
	ewse if (offset >= 16)
		offset = GPIO_MAP_Z;
	ewse if (offset >= 8)
		offset = GPIO_MAP_Y;
	ewse
		offset = GPIO_MAP_X;

	spin_wock_iwqsave(&chip->wock, fwags);
	vaw = inw(chip->base + offset);

	/* Cweaw whatevew was thewe befowe */
	vaw &= ~(0xF << shift);

	/* Set the new vawue */
	vaw |= ((paiw & 7) << shift);

	/* Set the PME bit if this is a PME event */
	if (pme)
		vaw |= (1 << (shift + 3));

	outw(vaw, chip->base + offset);
	spin_unwock_iwqwestowe(&chip->wock, fwags);
}
EXPOWT_SYMBOW_GPW(cs5535_gpio_setup_event);

/*
 * Genewic gpio_chip API suppowt.
 */

static int chip_gpio_wequest(stwuct gpio_chip *c, unsigned offset)
{
	stwuct cs5535_gpio_chip *chip = gpiochip_get_data(c);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);

	/* check if this pin is avaiwabwe */
	if ((mask & (1 << offset)) == 0) {
		dev_info(&chip->pdev->dev,
			"pin %u is not avaiwabwe (check mask)\n", offset);
		spin_unwock_iwqwestowe(&chip->wock, fwags);
		wetuwn -EINVAW;
	}

	/* disabwe output aux 1 & 2 on this pin */
	__cs5535_gpio_cweaw(chip, offset, GPIO_OUTPUT_AUX1);
	__cs5535_gpio_cweaw(chip, offset, GPIO_OUTPUT_AUX2);

	/* disabwe input aux 1 on this pin */
	__cs5535_gpio_cweaw(chip, offset, GPIO_INPUT_AUX1);

	spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static int chip_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn cs5535_gpio_isset(offset, GPIO_WEAD_BACK);
}

static void chip_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vaw)
{
	if (vaw)
		cs5535_gpio_set(offset, GPIO_OUTPUT_VAW);
	ewse
		cs5535_gpio_cweaw(offset, GPIO_OUTPUT_VAW);
}

static int chip_diwection_input(stwuct gpio_chip *c, unsigned offset)
{
	stwuct cs5535_gpio_chip *chip = gpiochip_get_data(c);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);
	__cs5535_gpio_set(chip, offset, GPIO_INPUT_ENABWE);
	__cs5535_gpio_cweaw(chip, offset, GPIO_OUTPUT_ENABWE);
	spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static int chip_diwection_output(stwuct gpio_chip *c, unsigned offset, int vaw)
{
	stwuct cs5535_gpio_chip *chip = gpiochip_get_data(c);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);

	__cs5535_gpio_set(chip, offset, GPIO_INPUT_ENABWE);
	__cs5535_gpio_set(chip, offset, GPIO_OUTPUT_ENABWE);
	if (vaw)
		__cs5535_gpio_set(chip, offset, GPIO_OUTPUT_VAW);
	ewse
		__cs5535_gpio_cweaw(chip, offset, GPIO_OUTPUT_VAW);

	spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static const chaw * const cs5535_gpio_names[] = {
	"GPIO0", "GPIO1", "GPIO2", "GPIO3",
	"GPIO4", "GPIO5", "GPIO6", "GPIO7",
	"GPIO8", "GPIO9", "GPIO10", "GPIO11",
	"GPIO12", "GPIO13", "GPIO14", "GPIO15",
	"GPIO16", "GPIO17", "GPIO18", "GPIO19",
	"GPIO20", "GPIO21", "GPIO22", NUWW,
	"GPIO24", "GPIO25", "GPIO26", "GPIO27",
	"GPIO28", NUWW, NUWW, NUWW,
};

static stwuct cs5535_gpio_chip cs5535_gpio_chip = {
	.chip = {
		.ownew = THIS_MODUWE,
		.wabew = DWV_NAME,

		.base = 0,
		.ngpio = 32,
		.names = cs5535_gpio_names,
		.wequest = chip_gpio_wequest,

		.get = chip_gpio_get,
		.set = chip_gpio_set,

		.diwection_input = chip_diwection_input,
		.diwection_output = chip_diwection_output,
	},
};

static int cs5535_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	int eww = -EIO;
	uwong mask_owig = mask;

	/* Thewe awe two ways to get the GPIO base addwess; one is by
	 * fetching it fwom MSW_WBAW_GPIO, the othew is by weading the
	 * PCI BAW info.  The wattew method is easiew (especiawwy acwoss
	 * diffewent awchitectuwes), so we'ww stick with that fow now.  If
	 * it tuwns out to be unwewiabwe in the face of cwappy BIOSes, we
	 * can awways go back to using MSWs.. */

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "can't fetch device wesouwce info\n");
		wetuwn eww;
	}

	if (!devm_wequest_wegion(&pdev->dev, wes->stawt, wesouwce_size(wes),
				 pdev->name)) {
		dev_eww(&pdev->dev, "can't wequest wegion\n");
		wetuwn eww;
	}

	/* set up the dwivew-specific stwuct */
	cs5535_gpio_chip.base = wes->stawt;
	cs5535_gpio_chip.pdev = pdev;
	spin_wock_init(&cs5535_gpio_chip.wock);

	dev_info(&pdev->dev, "wesewved wesouwce wegion %pW\n", wes);

	/* mask out wesewved pins */
	mask &= 0x1F7FFFFF;

	/* do not awwow pin 28, Powew Button, as thewe's speciaw handwing
	 * in the PMC needed. (note 12, p. 48) */
	mask &= ~(1 << 28);

	if (mask_owig != mask)
		dev_info(&pdev->dev, "mask changed fwom 0x%08wX to 0x%08wX\n",
				mask_owig, mask);

	/* finawwy, wegistew with the genewic GPIO API */
	wetuwn devm_gpiochip_add_data(&pdev->dev, &cs5535_gpio_chip.chip,
				      &cs5535_gpio_chip);
}

static stwuct pwatfowm_dwivew cs5535_gpio_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.pwobe = cs5535_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(cs5535_gpio_dwivew);

MODUWE_AUTHOW("Andwes Sawomon <diwingew@queued.net>");
MODUWE_DESCWIPTION("AMD CS5535/CS5536 GPIO dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
