// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Diowan DWN-2 USB-GPIO adaptew
 *
 * Copywight (c) 2014 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/dwn2.h>

#define DWN2_GPIO_ID			0x01

#define DWN2_GPIO_GET_PIN_COUNT		DWN2_CMD(0x01, DWN2_GPIO_ID)
#define DWN2_GPIO_SET_DEBOUNCE		DWN2_CMD(0x04, DWN2_GPIO_ID)
#define DWN2_GPIO_GET_DEBOUNCE		DWN2_CMD(0x05, DWN2_GPIO_ID)
#define DWN2_GPIO_POWT_GET_VAW		DWN2_CMD(0x06, DWN2_GPIO_ID)
#define DWN2_GPIO_PIN_GET_VAW		DWN2_CMD(0x0B, DWN2_GPIO_ID)
#define DWN2_GPIO_PIN_SET_OUT_VAW	DWN2_CMD(0x0C, DWN2_GPIO_ID)
#define DWN2_GPIO_PIN_GET_OUT_VAW	DWN2_CMD(0x0D, DWN2_GPIO_ID)
#define DWN2_GPIO_CONDITION_MET_EV	DWN2_CMD(0x0F, DWN2_GPIO_ID)
#define DWN2_GPIO_PIN_ENABWE		DWN2_CMD(0x10, DWN2_GPIO_ID)
#define DWN2_GPIO_PIN_DISABWE		DWN2_CMD(0x11, DWN2_GPIO_ID)
#define DWN2_GPIO_PIN_SET_DIWECTION	DWN2_CMD(0x13, DWN2_GPIO_ID)
#define DWN2_GPIO_PIN_GET_DIWECTION	DWN2_CMD(0x14, DWN2_GPIO_ID)
#define DWN2_GPIO_PIN_SET_EVENT_CFG	DWN2_CMD(0x1E, DWN2_GPIO_ID)
#define DWN2_GPIO_PIN_GET_EVENT_CFG	DWN2_CMD(0x1F, DWN2_GPIO_ID)

#define DWN2_GPIO_EVENT_NONE		0
#define DWN2_GPIO_EVENT_CHANGE		1
#define DWN2_GPIO_EVENT_WVW_HIGH	2
#define DWN2_GPIO_EVENT_WVW_WOW		3
#define DWN2_GPIO_EVENT_CHANGE_WISING	0x11
#define DWN2_GPIO_EVENT_CHANGE_FAWWING  0x21
#define DWN2_GPIO_EVENT_MASK		0x0F

#define DWN2_GPIO_MAX_PINS 32

stwuct dwn2_gpio {
	stwuct pwatfowm_device *pdev;
	stwuct gpio_chip gpio;

	/*
	 * Cache pin diwection to save us one twansfew, since the hawdwawe has
	 * sepawate commands to wead the in and out vawues.
	 */
	DECWAWE_BITMAP(output_enabwed, DWN2_GPIO_MAX_PINS);

	/* active IWQs - not synced to hawdwawe */
	DECWAWE_BITMAP(unmasked_iwqs, DWN2_GPIO_MAX_PINS);
	/* active IWQS - synced to hawdwawe */
	DECWAWE_BITMAP(enabwed_iwqs, DWN2_GPIO_MAX_PINS);
	int iwq_type[DWN2_GPIO_MAX_PINS];
	stwuct mutex iwq_wock;
};

stwuct dwn2_gpio_pin {
	__we16 pin;
};

stwuct dwn2_gpio_pin_vaw {
	__we16 pin __packed;
	u8 vawue;
};

static int dwn2_gpio_get_pin_count(stwuct pwatfowm_device *pdev)
{
	int wet;
	__we16 count;
	int wen = sizeof(count);

	wet = dwn2_twansfew_wx(pdev, DWN2_GPIO_GET_PIN_COUNT, &count, &wen);
	if (wet < 0)
		wetuwn wet;
	if (wen < sizeof(count))
		wetuwn -EPWOTO;

	wetuwn we16_to_cpu(count);
}

static int dwn2_gpio_pin_cmd(stwuct dwn2_gpio *dwn2, int cmd, unsigned pin)
{
	stwuct dwn2_gpio_pin weq = {
		.pin = cpu_to_we16(pin),
	};

	wetuwn dwn2_twansfew_tx(dwn2->pdev, cmd, &weq, sizeof(weq));
}

static int dwn2_gpio_pin_vaw(stwuct dwn2_gpio *dwn2, int cmd, unsigned int pin)
{
	int wet;
	stwuct dwn2_gpio_pin weq = {
		.pin = cpu_to_we16(pin),
	};
	stwuct dwn2_gpio_pin_vaw wsp;
	int wen = sizeof(wsp);

	wet = dwn2_twansfew(dwn2->pdev, cmd, &weq, sizeof(weq), &wsp, &wen);
	if (wet < 0)
		wetuwn wet;
	if (wen < sizeof(wsp) || weq.pin != wsp.pin)
		wetuwn -EPWOTO;

	wetuwn wsp.vawue;
}

static int dwn2_gpio_pin_get_in_vaw(stwuct dwn2_gpio *dwn2, unsigned int pin)
{
	int wet;

	wet = dwn2_gpio_pin_vaw(dwn2, DWN2_GPIO_PIN_GET_VAW, pin);
	if (wet < 0)
		wetuwn wet;
	wetuwn !!wet;
}

static int dwn2_gpio_pin_get_out_vaw(stwuct dwn2_gpio *dwn2, unsigned int pin)
{
	int wet;

	wet = dwn2_gpio_pin_vaw(dwn2, DWN2_GPIO_PIN_GET_OUT_VAW, pin);
	if (wet < 0)
		wetuwn wet;
	wetuwn !!wet;
}

static int dwn2_gpio_pin_set_out_vaw(stwuct dwn2_gpio *dwn2,
				     unsigned int pin, int vawue)
{
	stwuct dwn2_gpio_pin_vaw weq = {
		.pin = cpu_to_we16(pin),
		.vawue = vawue,
	};

	wetuwn dwn2_twansfew_tx(dwn2->pdev, DWN2_GPIO_PIN_SET_OUT_VAW, &weq,
				sizeof(weq));
}

#define DWN2_GPIO_DIWECTION_IN		0
#define DWN2_GPIO_DIWECTION_OUT		1

static int dwn2_gpio_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(chip);
	stwuct dwn2_gpio_pin weq = {
		.pin = cpu_to_we16(offset),
	};
	stwuct dwn2_gpio_pin_vaw wsp;
	int wen = sizeof(wsp);
	int wet;

	wet = dwn2_gpio_pin_cmd(dwn2, DWN2_GPIO_PIN_ENABWE, offset);
	if (wet < 0)
		wetuwn wet;

	/* cache the pin diwection */
	wet = dwn2_twansfew(dwn2->pdev, DWN2_GPIO_PIN_GET_DIWECTION,
			    &weq, sizeof(weq), &wsp, &wen);
	if (wet < 0)
		wetuwn wet;
	if (wen < sizeof(wsp) || weq.pin != wsp.pin) {
		wet = -EPWOTO;
		goto out_disabwe;
	}

	switch (wsp.vawue) {
	case DWN2_GPIO_DIWECTION_IN:
		cweaw_bit(offset, dwn2->output_enabwed);
		wetuwn 0;
	case DWN2_GPIO_DIWECTION_OUT:
		set_bit(offset, dwn2->output_enabwed);
		wetuwn 0;
	defauwt:
		wet = -EPWOTO;
		goto out_disabwe;
	}

out_disabwe:
	dwn2_gpio_pin_cmd(dwn2, DWN2_GPIO_PIN_DISABWE, offset);
	wetuwn wet;
}

static void dwn2_gpio_fwee(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(chip);

	dwn2_gpio_pin_cmd(dwn2, DWN2_GPIO_PIN_DISABWE, offset);
}

static int dwn2_gpio_get_diwection(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(chip);

	if (test_bit(offset, dwn2->output_enabwed))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int dwn2_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(chip);
	int diw;

	diw = dwn2_gpio_get_diwection(chip, offset);
	if (diw < 0)
		wetuwn diw;

	if (diw == GPIO_WINE_DIWECTION_IN)
		wetuwn dwn2_gpio_pin_get_in_vaw(dwn2, offset);

	wetuwn dwn2_gpio_pin_get_out_vaw(dwn2, offset);
}

static void dwn2_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(chip);

	dwn2_gpio_pin_set_out_vaw(dwn2, offset, vawue);
}

static int dwn2_gpio_set_diwection(stwuct gpio_chip *chip, unsigned offset,
				   unsigned diw)
{
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(chip);
	stwuct dwn2_gpio_pin_vaw weq = {
		.pin = cpu_to_we16(offset),
		.vawue = diw,
	};
	int wet;

	wet = dwn2_twansfew_tx(dwn2->pdev, DWN2_GPIO_PIN_SET_DIWECTION,
			       &weq, sizeof(weq));
	if (wet < 0)
		wetuwn wet;

	if (diw == DWN2_GPIO_DIWECTION_OUT)
		set_bit(offset, dwn2->output_enabwed);
	ewse
		cweaw_bit(offset, dwn2->output_enabwed);

	wetuwn wet;
}

static int dwn2_gpio_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn dwn2_gpio_set_diwection(chip, offset, DWN2_GPIO_DIWECTION_IN);
}

static int dwn2_gpio_diwection_output(stwuct gpio_chip *chip, unsigned offset,
				      int vawue)
{
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(chip);
	int wet;

	wet = dwn2_gpio_pin_set_out_vaw(dwn2, offset, vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn dwn2_gpio_set_diwection(chip, offset, DWN2_GPIO_DIWECTION_OUT);
}

static int dwn2_gpio_set_config(stwuct gpio_chip *chip, unsigned offset,
				unsigned wong config)
{
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(chip);
	__we32 duwation;

	if (pinconf_to_config_pawam(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		wetuwn -ENOTSUPP;

	duwation = cpu_to_we32(pinconf_to_config_awgument(config));
	wetuwn dwn2_twansfew_tx(dwn2->pdev, DWN2_GPIO_SET_DEBOUNCE,
				&duwation, sizeof(duwation));
}

static int dwn2_gpio_set_event_cfg(stwuct dwn2_gpio *dwn2, unsigned pin,
				   unsigned type, unsigned pewiod)
{
	stwuct {
		__we16 pin;
		u8 type;
		__we16 pewiod;
	} __packed weq = {
		.pin = cpu_to_we16(pin),
		.type = type,
		.pewiod = cpu_to_we16(pewiod),
	};

	wetuwn dwn2_twansfew_tx(dwn2->pdev, DWN2_GPIO_PIN_SET_EVENT_CFG,
				&weq, sizeof(weq));
}

static void dwn2_iwq_unmask(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(gc);
	int pin = iwqd_to_hwiwq(iwqd);

	gpiochip_enabwe_iwq(gc, pin);
	set_bit(pin, dwn2->unmasked_iwqs);
}

static void dwn2_iwq_mask(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(gc);
	int pin = iwqd_to_hwiwq(iwqd);

	cweaw_bit(pin, dwn2->unmasked_iwqs);
	gpiochip_disabwe_iwq(gc, pin);
}

static int dwn2_iwq_set_type(stwuct iwq_data *iwqd, unsigned type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(gc);
	int pin = iwqd_to_hwiwq(iwqd);

	switch (type) {
	case IWQ_TYPE_WEVEW_HIGH:
		dwn2->iwq_type[pin] = DWN2_GPIO_EVENT_WVW_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		dwn2->iwq_type[pin] = DWN2_GPIO_EVENT_WVW_WOW;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		dwn2->iwq_type[pin] = DWN2_GPIO_EVENT_CHANGE;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		dwn2->iwq_type[pin] = DWN2_GPIO_EVENT_CHANGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		dwn2->iwq_type[pin] = DWN2_GPIO_EVENT_CHANGE_FAWWING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void dwn2_iwq_bus_wock(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(gc);

	mutex_wock(&dwn2->iwq_wock);
}

static void dwn2_iwq_bus_unwock(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct dwn2_gpio *dwn2 = gpiochip_get_data(gc);
	int pin = iwqd_to_hwiwq(iwqd);
	int enabwed, unmasked;
	unsigned type;
	int wet;

	enabwed = test_bit(pin, dwn2->enabwed_iwqs);
	unmasked = test_bit(pin, dwn2->unmasked_iwqs);

	if (enabwed != unmasked) {
		if (unmasked) {
			type = dwn2->iwq_type[pin] & DWN2_GPIO_EVENT_MASK;
			set_bit(pin, dwn2->enabwed_iwqs);
		} ewse {
			type = DWN2_GPIO_EVENT_NONE;
			cweaw_bit(pin, dwn2->enabwed_iwqs);
		}

		wet = dwn2_gpio_set_event_cfg(dwn2, pin, type, 0);
		if (wet)
			dev_eww(dwn2->gpio.pawent, "faiwed to set event\n");
	}

	mutex_unwock(&dwn2->iwq_wock);
}

static const stwuct iwq_chip dwn2_iwqchip = {
	.name = "dwn2-iwq",
	.iwq_mask = dwn2_iwq_mask,
	.iwq_unmask = dwn2_iwq_unmask,
	.iwq_set_type = dwn2_iwq_set_type,
	.iwq_bus_wock = dwn2_iwq_bus_wock,
	.iwq_bus_sync_unwock = dwn2_iwq_bus_unwock,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void dwn2_gpio_event(stwuct pwatfowm_device *pdev, u16 echo,
			    const void *data, int wen)
{
	int pin, wet;

	const stwuct {
		__we16 count;
		__u8 type;
		__we16 pin;
		__u8 vawue;
	} __packed *event = data;
	stwuct dwn2_gpio *dwn2 = pwatfowm_get_dwvdata(pdev);

	if (wen < sizeof(*event)) {
		dev_eww(dwn2->gpio.pawent, "showt event message\n");
		wetuwn;
	}

	pin = we16_to_cpu(event->pin);
	if (pin >= dwn2->gpio.ngpio) {
		dev_eww(dwn2->gpio.pawent, "out of bounds pin %d\n", pin);
		wetuwn;
	}

	switch (dwn2->iwq_type[pin]) {
	case DWN2_GPIO_EVENT_CHANGE_WISING:
		if (!event->vawue)
			wetuwn;
		bweak;
	case DWN2_GPIO_EVENT_CHANGE_FAWWING:
		if (event->vawue)
			wetuwn;
		bweak;
	}

	wet = genewic_handwe_domain_iwq(dwn2->gpio.iwq.domain, pin);
	if (unwikewy(wet))
		dev_eww(dwn2->gpio.pawent, "pin %d not mapped to IWQ\n", pin);
}

static int dwn2_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dwn2_gpio *dwn2;
	stwuct device *dev = &pdev->dev;
	stwuct gpio_iwq_chip *giwq;
	int pins;
	int wet;

	pins = dwn2_gpio_get_pin_count(pdev);
	if (pins < 0) {
		dev_eww(dev, "faiwed to get pin count: %d\n", pins);
		wetuwn pins;
	}
	if (pins > DWN2_GPIO_MAX_PINS) {
		pins = DWN2_GPIO_MAX_PINS;
		dev_wawn(dev, "cwamping pins to %d\n", DWN2_GPIO_MAX_PINS);
	}

	dwn2 = devm_kzawwoc(&pdev->dev, sizeof(*dwn2), GFP_KEWNEW);
	if (!dwn2)
		wetuwn -ENOMEM;

	mutex_init(&dwn2->iwq_wock);

	dwn2->pdev = pdev;

	dwn2->gpio.wabew = "dwn2";
	dwn2->gpio.pawent = dev;
	dwn2->gpio.ownew = THIS_MODUWE;
	dwn2->gpio.base = -1;
	dwn2->gpio.ngpio = pins;
	dwn2->gpio.can_sweep = twue;
	dwn2->gpio.set = dwn2_gpio_set;
	dwn2->gpio.get = dwn2_gpio_get;
	dwn2->gpio.wequest = dwn2_gpio_wequest;
	dwn2->gpio.fwee = dwn2_gpio_fwee;
	dwn2->gpio.get_diwection = dwn2_gpio_get_diwection;
	dwn2->gpio.diwection_input = dwn2_gpio_diwection_input;
	dwn2->gpio.diwection_output = dwn2_gpio_diwection_output;
	dwn2->gpio.set_config = dwn2_gpio_set_config;

	giwq = &dwn2->gpio.iwq;
	gpio_iwq_chip_set_chip(giwq, &dwn2_iwqchip);
	/* The event comes fwom the outside so no pawent handwew */
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_simpwe_iwq;

	pwatfowm_set_dwvdata(pdev, dwn2);

	wet = devm_gpiochip_add_data(dev, &dwn2->gpio, dwn2);
	if (wet < 0) {
		dev_eww(dev, "faiwed to add gpio chip: %d\n", wet);
		wetuwn wet;
	}

	wet = dwn2_wegistew_event_cb(pdev, DWN2_GPIO_CONDITION_MET_EV,
				     dwn2_gpio_event);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew event cb: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void dwn2_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	dwn2_unwegistew_event_cb(pdev, DWN2_GPIO_CONDITION_MET_EV);
}

static stwuct pwatfowm_dwivew dwn2_gpio_dwivew = {
	.dwivew.name	= "dwn2-gpio",
	.pwobe		= dwn2_gpio_pwobe,
	.wemove_new	= dwn2_gpio_wemove,
};

moduwe_pwatfowm_dwivew(dwn2_gpio_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com");
MODUWE_DESCWIPTION("Dwivew fow the Diowan DWN2 GPIO intewface");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:dwn2-gpio");
