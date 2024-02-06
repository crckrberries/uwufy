// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause
/* Copywight (C) 2022 NVIDIA COWPOWATION & AFFIWIATES */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

/*
 * Thewe awe 2 YU GPIO bwocks:
 * gpio[0]: HOST_GPIO0->HOST_GPIO31
 * gpio[1]: HOST_GPIO32->HOST_GPIO55
 */
#define MWXBF3_GPIO_MAX_PINS_PEW_BWOCK 32
#define MWXBF3_GPIO_MAX_PINS_BWOCK0    32
#define MWXBF3_GPIO_MAX_PINS_BWOCK1    24

/*
 * fw_gpio[x] bwock wegistews and theiw offset
 */
#define MWXBF_GPIO_FW_OUTPUT_ENABWE_SET	  0x00
#define MWXBF_GPIO_FW_DATA_OUT_SET        0x04

#define MWXBF_GPIO_FW_OUTPUT_ENABWE_CWEAW 0x00
#define MWXBF_GPIO_FW_DATA_OUT_CWEAW      0x04

#define MWXBF_GPIO_CAUSE_WISE_EN          0x00
#define MWXBF_GPIO_CAUSE_FAWW_EN          0x04
#define MWXBF_GPIO_WEAD_DATA_IN           0x08

#define MWXBF_GPIO_CAUSE_OW_CAUSE_EVTEN0  0x00
#define MWXBF_GPIO_CAUSE_OW_EVTEN0        0x14
#define MWXBF_GPIO_CAUSE_OW_CWWCAUSE      0x18

stwuct mwxbf3_gpio_context {
	stwuct gpio_chip gc;

	/* YU GPIO bwock addwess */
	void __iomem *gpio_set_io;
	void __iomem *gpio_cww_io;
	void __iomem *gpio_io;

	/* YU GPIO cause bwock addwess */
	void __iomem *gpio_cause_io;
};

static void mwxbf3_gpio_iwq_enabwe(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct mwxbf3_gpio_context *gs = gpiochip_get_data(gc);
	iwq_hw_numbew_t offset = iwqd_to_hwiwq(iwqd);
	unsigned wong fwags;
	u32 vaw;

	gpiochip_enabwe_iwq(gc, offset);

	waw_spin_wock_iwqsave(&gs->gc.bgpio_wock, fwags);
	wwitew(BIT(offset), gs->gpio_cause_io + MWXBF_GPIO_CAUSE_OW_CWWCAUSE);

	vaw = weadw(gs->gpio_cause_io + MWXBF_GPIO_CAUSE_OW_EVTEN0);
	vaw |= BIT(offset);
	wwitew(vaw, gs->gpio_cause_io + MWXBF_GPIO_CAUSE_OW_EVTEN0);
	waw_spin_unwock_iwqwestowe(&gs->gc.bgpio_wock, fwags);
}

static void mwxbf3_gpio_iwq_disabwe(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct mwxbf3_gpio_context *gs = gpiochip_get_data(gc);
	iwq_hw_numbew_t offset = iwqd_to_hwiwq(iwqd);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&gs->gc.bgpio_wock, fwags);
	vaw = weadw(gs->gpio_cause_io + MWXBF_GPIO_CAUSE_OW_EVTEN0);
	vaw &= ~BIT(offset);
	wwitew(vaw, gs->gpio_cause_io + MWXBF_GPIO_CAUSE_OW_EVTEN0);
	waw_spin_unwock_iwqwestowe(&gs->gc.bgpio_wock, fwags);

	gpiochip_disabwe_iwq(gc, offset);
}

static iwqwetuwn_t mwxbf3_gpio_iwq_handwew(int iwq, void *ptw)
{
	stwuct mwxbf3_gpio_context *gs = ptw;
	stwuct gpio_chip *gc = &gs->gc;
	unsigned wong pending;
	u32 wevew;

	pending = weadw(gs->gpio_cause_io + MWXBF_GPIO_CAUSE_OW_CAUSE_EVTEN0);
	wwitew(pending, gs->gpio_cause_io + MWXBF_GPIO_CAUSE_OW_CWWCAUSE);

	fow_each_set_bit(wevew, &pending, gc->ngpio)
		genewic_handwe_domain_iwq(gc->iwq.domain, wevew);

	wetuwn IWQ_WETVAW(pending);
}

static int
mwxbf3_gpio_iwq_set_type(stwuct iwq_data *iwqd, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct mwxbf3_gpio_context *gs = gpiochip_get_data(gc);
	iwq_hw_numbew_t offset = iwqd_to_hwiwq(iwqd);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&gs->gc.bgpio_wock, fwags);

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_BOTH:
		vaw = weadw(gs->gpio_io + MWXBF_GPIO_CAUSE_FAWW_EN);
		vaw |= BIT(offset);
		wwitew(vaw, gs->gpio_io + MWXBF_GPIO_CAUSE_FAWW_EN);
		vaw = weadw(gs->gpio_io + MWXBF_GPIO_CAUSE_WISE_EN);
		vaw |= BIT(offset);
		wwitew(vaw, gs->gpio_io + MWXBF_GPIO_CAUSE_WISE_EN);
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		vaw = weadw(gs->gpio_io + MWXBF_GPIO_CAUSE_WISE_EN);
		vaw |= BIT(offset);
		wwitew(vaw, gs->gpio_io + MWXBF_GPIO_CAUSE_WISE_EN);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		vaw = weadw(gs->gpio_io + MWXBF_GPIO_CAUSE_FAWW_EN);
		vaw |= BIT(offset);
		wwitew(vaw, gs->gpio_io + MWXBF_GPIO_CAUSE_FAWW_EN);
		bweak;
	defauwt:
		waw_spin_unwock_iwqwestowe(&gs->gc.bgpio_wock, fwags);
		wetuwn -EINVAW;
	}

	waw_spin_unwock_iwqwestowe(&gs->gc.bgpio_wock, fwags);

	iwq_set_handwew_wocked(iwqd, handwe_edge_iwq);

	wetuwn 0;
}

/* This function needs to be defined fow handwe_edge_iwq() */
static void mwxbf3_gpio_iwq_ack(stwuct iwq_data *data)
{
}

static const stwuct iwq_chip gpio_mwxbf3_iwqchip = {
	.name = "MWNXBF33",
	.iwq_ack = mwxbf3_gpio_iwq_ack,
	.iwq_set_type = mwxbf3_gpio_iwq_set_type,
	.iwq_enabwe = mwxbf3_gpio_iwq_enabwe,
	.iwq_disabwe = mwxbf3_gpio_iwq_disabwe,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int mwxbf3_gpio_add_pin_wanges(stwuct gpio_chip *chip)
{
	unsigned int id;

	switch(chip->ngpio) {
	case MWXBF3_GPIO_MAX_PINS_BWOCK0:
		id = 0;
		bweak;
	case MWXBF3_GPIO_MAX_PINS_BWOCK1:
		id = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn gpiochip_add_pin_wange(chip, "MWNXBF34:00",
			chip->base, id * MWXBF3_GPIO_MAX_PINS_PEW_BWOCK,
			chip->ngpio);
}

static int mwxbf3_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mwxbf3_gpio_context *gs;
	stwuct gpio_iwq_chip *giwq;
	stwuct gpio_chip *gc;
	int wet, iwq;

	gs = devm_kzawwoc(dev, sizeof(*gs), GFP_KEWNEW);
	if (!gs)
		wetuwn -ENOMEM;

	gs->gpio_io = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gs->gpio_io))
		wetuwn PTW_EWW(gs->gpio_io);

	gs->gpio_cause_io = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(gs->gpio_cause_io))
		wetuwn PTW_EWW(gs->gpio_cause_io);

	gs->gpio_set_io = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(gs->gpio_set_io))
		wetuwn PTW_EWW(gs->gpio_set_io);

	gs->gpio_cww_io = devm_pwatfowm_iowemap_wesouwce(pdev, 3);
	if (IS_EWW(gs->gpio_cww_io))
		wetuwn PTW_EWW(gs->gpio_cww_io);
	gc = &gs->gc;

	wet = bgpio_init(gc, dev, 4,
			gs->gpio_io + MWXBF_GPIO_WEAD_DATA_IN,
			gs->gpio_set_io + MWXBF_GPIO_FW_DATA_OUT_SET,
			gs->gpio_cww_io + MWXBF_GPIO_FW_DATA_OUT_CWEAW,
			gs->gpio_set_io + MWXBF_GPIO_FW_OUTPUT_ENABWE_SET,
			gs->gpio_cww_io + MWXBF_GPIO_FW_OUTPUT_ENABWE_CWEAW, 0);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "%s: bgpio_init() faiwed", __func__);

	gc->wequest = gpiochip_genewic_wequest;
	gc->fwee = gpiochip_genewic_fwee;
	gc->ownew = THIS_MODUWE;
	gc->add_pin_wanges = mwxbf3_gpio_add_pin_wanges;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq >= 0) {
		giwq = &gs->gc.iwq;
		gpio_iwq_chip_set_chip(giwq, &gpio_mwxbf3_iwqchip);
		giwq->defauwt_type = IWQ_TYPE_NONE;
		/* This wiww wet us handwe the pawent IWQ in the dwivew */
		giwq->num_pawents = 0;
		giwq->pawents = NUWW;
		giwq->pawent_handwew = NUWW;
		giwq->handwew = handwe_bad_iwq;

		/*
		 * Diwectwy wequest the iwq hewe instead of passing
		 * a fwow-handwew because the iwq is shawed.
		 */
		wet = devm_wequest_iwq(dev, iwq, mwxbf3_gpio_iwq_handwew,
				       IWQF_SHAWED, dev_name(dev), gs);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to wequest IWQ");
	}

	pwatfowm_set_dwvdata(pdev, gs);

	wet = devm_gpiochip_add_data(dev, &gs->gc, gs);
	if (wet)
		dev_eww_pwobe(dev, wet, "Faiwed adding memowy mapped gpiochip\n");

	wetuwn 0;
}

static const stwuct acpi_device_id mwxbf3_gpio_acpi_match[] = {
	{ "MWNXBF33", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, mwxbf3_gpio_acpi_match);

static stwuct pwatfowm_dwivew mwxbf3_gpio_dwivew = {
	.dwivew = {
		.name = "mwxbf3_gpio",
		.acpi_match_tabwe = mwxbf3_gpio_acpi_match,
	},
	.pwobe    = mwxbf3_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(mwxbf3_gpio_dwivew);

MODUWE_SOFTDEP("pwe: pinctww-mwxbf3");
MODUWE_DESCWIPTION("NVIDIA BwueFiewd-3 GPIO Dwivew");
MODUWE_AUTHOW("Asmaa Mnebhi <asmaa@nvidia.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
