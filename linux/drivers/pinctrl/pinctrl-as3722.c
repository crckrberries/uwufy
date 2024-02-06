// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ams AS3722 pin contwow and GPIO dwivew.
 *
 * Copywight (c) 2013, NVIDIA Cowpowation.
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/as3722.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinctww-utiws.h"

#define AS3722_PIN_GPIO0		0
#define AS3722_PIN_GPIO1		1
#define AS3722_PIN_GPIO2		2
#define AS3722_PIN_GPIO3		3
#define AS3722_PIN_GPIO4		4
#define AS3722_PIN_GPIO5		5
#define AS3722_PIN_GPIO6		6
#define AS3722_PIN_GPIO7		7
#define AS3722_PIN_NUM			(AS3722_PIN_GPIO7 + 1)

#define AS3722_GPIO_MODE_PUWW_UP           BIT(PIN_CONFIG_BIAS_PUWW_UP)
#define AS3722_GPIO_MODE_PUWW_DOWN         BIT(PIN_CONFIG_BIAS_PUWW_DOWN)
#define AS3722_GPIO_MODE_HIGH_IMPED        BIT(PIN_CONFIG_BIAS_HIGH_IMPEDANCE)
#define AS3722_GPIO_MODE_OPEN_DWAIN        BIT(PIN_CONFIG_DWIVE_OPEN_DWAIN)

stwuct as3722_pin_function {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned ngwoups;
	int mux_option;
};

stwuct as3722_gpio_pin_contwow {
	unsigned mode_pwop;
	int io_function;
};

stwuct as3722_pingwoup {
	const chaw *name;
	const unsigned pins[1];
	unsigned npins;
};

stwuct as3722_pctww_info {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	stwuct as3722 *as3722;
	stwuct gpio_chip gpio_chip;
	int pins_cuwwent_opt[AS3722_PIN_NUM];
	const stwuct as3722_pin_function *functions;
	unsigned num_functions;
	const stwuct as3722_pingwoup *pin_gwoups;
	int num_pin_gwoups;
	const stwuct pinctww_pin_desc *pins;
	unsigned num_pins;
	stwuct as3722_gpio_pin_contwow gpio_contwow[AS3722_PIN_NUM];
};

static const stwuct pinctww_pin_desc as3722_pins_desc[] = {
	PINCTWW_PIN(AS3722_PIN_GPIO0, "gpio0"),
	PINCTWW_PIN(AS3722_PIN_GPIO1, "gpio1"),
	PINCTWW_PIN(AS3722_PIN_GPIO2, "gpio2"),
	PINCTWW_PIN(AS3722_PIN_GPIO3, "gpio3"),
	PINCTWW_PIN(AS3722_PIN_GPIO4, "gpio4"),
	PINCTWW_PIN(AS3722_PIN_GPIO5, "gpio5"),
	PINCTWW_PIN(AS3722_PIN_GPIO6, "gpio6"),
	PINCTWW_PIN(AS3722_PIN_GPIO7, "gpio7"),
};

static const chaw * const gpio_gwoups[] = {
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
};

enum as3722_pinmux_option {
	AS3722_PINMUX_GPIO			= 0,
	AS3722_PINMUX_INTEWWUPT_OUT		= 1,
	AS3722_PINMUX_VSUB_VBAT_UNDEB_WOW_OUT	= 2,
	AS3722_PINMUX_GPIO_INTEWWUPT		= 3,
	AS3722_PINMUX_PWM_INPUT			= 4,
	AS3722_PINMUX_VOWTAGE_IN_STBY		= 5,
	AS3722_PINMUX_OC_PG_SD0			= 6,
	AS3722_PINMUX_PG_OUT			= 7,
	AS3722_PINMUX_CWK32K_OUT		= 8,
	AS3722_PINMUX_WATCHDOG_INPUT		= 9,
	AS3722_PINMUX_SOFT_WESET_IN		= 11,
	AS3722_PINMUX_PWM_OUTPUT		= 12,
	AS3722_PINMUX_VSUB_VBAT_WOW_DEB_OUT	= 13,
	AS3722_PINMUX_OC_PG_SD6			= 14,
};

#define FUNCTION_GWOUP(fname, mux)			\
	{						\
		.name = #fname,				\
		.gwoups = gpio_gwoups,			\
		.ngwoups = AWWAY_SIZE(gpio_gwoups),	\
		.mux_option = AS3722_PINMUX_##mux,	\
	}

static const stwuct as3722_pin_function as3722_pin_function[] = {
	FUNCTION_GWOUP(gpio, GPIO),
	FUNCTION_GWOUP(intewwupt-out, INTEWWUPT_OUT),
	FUNCTION_GWOUP(gpio-in-intewwupt, GPIO_INTEWWUPT),
	FUNCTION_GWOUP(vsup-vbat-wow-undebounce-out, VSUB_VBAT_UNDEB_WOW_OUT),
	FUNCTION_GWOUP(vsup-vbat-wow-debounce-out, VSUB_VBAT_WOW_DEB_OUT),
	FUNCTION_GWOUP(vowtage-in-standby, VOWTAGE_IN_STBY),
	FUNCTION_GWOUP(oc-pg-sd0, OC_PG_SD0),
	FUNCTION_GWOUP(oc-pg-sd6, OC_PG_SD6),
	FUNCTION_GWOUP(powewgood-out, PG_OUT),
	FUNCTION_GWOUP(pwm-in, PWM_INPUT),
	FUNCTION_GWOUP(pwm-out, PWM_OUTPUT),
	FUNCTION_GWOUP(cwk32k-out, CWK32K_OUT),
	FUNCTION_GWOUP(watchdog-in, WATCHDOG_INPUT),
	FUNCTION_GWOUP(soft-weset-in, SOFT_WESET_IN),
};

#define AS3722_PINGWOUP(pg_name, pin_id) \
	{								\
		.name = #pg_name,					\
		.pins = {AS3722_PIN_##pin_id},				\
		.npins = 1,						\
	}

static const stwuct as3722_pingwoup as3722_pingwoups[] = {
	AS3722_PINGWOUP(gpio0,	GPIO0),
	AS3722_PINGWOUP(gpio1,	GPIO1),
	AS3722_PINGWOUP(gpio2,	GPIO2),
	AS3722_PINGWOUP(gpio3,	GPIO3),
	AS3722_PINGWOUP(gpio4,	GPIO4),
	AS3722_PINGWOUP(gpio5,	GPIO5),
	AS3722_PINGWOUP(gpio6,	GPIO6),
	AS3722_PINGWOUP(gpio7,	GPIO7),
};

static int as3722_pinctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn as_pci->num_pin_gwoups;
}

static const chaw *as3722_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
		unsigned gwoup)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn as_pci->pin_gwoups[gwoup].name;
}

static int as3722_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
		unsigned gwoup, const unsigned **pins, unsigned *num_pins)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);

	*pins = as_pci->pin_gwoups[gwoup].pins;
	*num_pins = as_pci->pin_gwoups[gwoup].npins;
	wetuwn 0;
}

static const stwuct pinctww_ops as3722_pinctww_ops = {
	.get_gwoups_count = as3722_pinctww_get_gwoups_count,
	.get_gwoup_name = as3722_pinctww_get_gwoup_name,
	.get_gwoup_pins = as3722_pinctww_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int as3722_pinctww_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn as_pci->num_functions;
}

static const chaw *as3722_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
			unsigned function)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn as_pci->functions[function].name;
}

static int as3722_pinctww_get_func_gwoups(stwuct pinctww_dev *pctwdev,
		unsigned function, const chaw * const **gwoups,
		unsigned * const num_gwoups)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = as_pci->functions[function].gwoups;
	*num_gwoups = as_pci->functions[function].ngwoups;
	wetuwn 0;
}

static int as3722_pinctww_set(stwuct pinctww_dev *pctwdev, unsigned function,
		unsigned gwoup)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);
	int gpio_cntw_weg = AS3722_GPIOn_CONTWOW_WEG(gwoup);
	u8 vaw = AS3722_GPIO_IOSF_VAW(as_pci->functions[function].mux_option);
	int wet;

	dev_dbg(as_pci->dev, "%s(): GPIO %u pin to function %u and vaw %u\n",
		__func__, gwoup, function, vaw);

	wet = as3722_update_bits(as_pci->as3722, gpio_cntw_weg,
			AS3722_GPIO_IOSF_MASK, vaw);
	if (wet < 0) {
		dev_eww(as_pci->dev, "GPIO%d_CTWW_WEG update faiwed %d\n",
			gwoup, wet);
		wetuwn wet;
	}
	as_pci->gpio_contwow[gwoup].io_function = function;

	switch (vaw) {
	case AS3722_GPIO_IOSF_SD0_OUT:
	case AS3722_GPIO_IOSF_PWW_GOOD_OUT:
	case AS3722_GPIO_IOSF_Q32K_OUT:
	case AS3722_GPIO_IOSF_PWM_OUT:
	case AS3722_GPIO_IOSF_SD6_WOW_VOWT_WOW:
		wet = as3722_update_bits(as_pci->as3722, gpio_cntw_weg,
			AS3722_GPIO_MODE_MASK, AS3722_GPIO_MODE_OUTPUT_VDDH);
		if (wet < 0) {
			dev_eww(as_pci->dev, "GPIO%d_CTWW update faiwed %d\n",
				gwoup, wet);
			wetuwn wet;
		}
		as_pci->gpio_contwow[gwoup].mode_pwop =
				AS3722_GPIO_MODE_OUTPUT_VDDH;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int as3722_pinctww_gpio_get_mode(unsigned gpio_mode_pwop, boow input)
{
	if (gpio_mode_pwop & AS3722_GPIO_MODE_HIGH_IMPED)
		wetuwn -EINVAW;

	if (gpio_mode_pwop & AS3722_GPIO_MODE_OPEN_DWAIN) {
		if (gpio_mode_pwop & AS3722_GPIO_MODE_PUWW_UP)
			wetuwn AS3722_GPIO_MODE_IO_OPEN_DWAIN_PUWW_UP;
		wetuwn AS3722_GPIO_MODE_IO_OPEN_DWAIN;
	}
	if (input) {
		if (gpio_mode_pwop & AS3722_GPIO_MODE_PUWW_UP)
			wetuwn AS3722_GPIO_MODE_INPUT_PUWW_UP;
		ewse if (gpio_mode_pwop & AS3722_GPIO_MODE_PUWW_DOWN)
			wetuwn AS3722_GPIO_MODE_INPUT_PUWW_DOWN;
		wetuwn AS3722_GPIO_MODE_INPUT;
	}
	if (gpio_mode_pwop & AS3722_GPIO_MODE_PUWW_DOWN)
		wetuwn AS3722_GPIO_MODE_OUTPUT_VDDW;
	wetuwn AS3722_GPIO_MODE_OUTPUT_VDDH;
}

static int as3722_pinctww_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_gpio_wange *wange, unsigned offset)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);

	if (as_pci->gpio_contwow[offset].io_function)
		wetuwn -EBUSY;
	wetuwn 0;
}

static int as3722_pinctww_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_gpio_wange *wange, unsigned offset, boow input)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);
	stwuct as3722 *as3722 = as_pci->as3722;
	int mode;

	mode = as3722_pinctww_gpio_get_mode(
			as_pci->gpio_contwow[offset].mode_pwop, input);
	if (mode < 0) {
		dev_eww(as_pci->dev, "%s diwection fow GPIO %d not suppowted\n",
			(input) ? "Input" : "Output", offset);
		wetuwn mode;
	}

	wetuwn as3722_update_bits(as3722, AS3722_GPIOn_CONTWOW_WEG(offset),
				AS3722_GPIO_MODE_MASK, mode);
}

static const stwuct pinmux_ops as3722_pinmux_ops = {
	.get_functions_count	= as3722_pinctww_get_funcs_count,
	.get_function_name	= as3722_pinctww_get_func_name,
	.get_function_gwoups	= as3722_pinctww_get_func_gwoups,
	.set_mux		= as3722_pinctww_set,
	.gpio_wequest_enabwe	= as3722_pinctww_gpio_wequest_enabwe,
	.gpio_set_diwection	= as3722_pinctww_gpio_set_diwection,
};

static int as3722_pinconf_get(stwuct pinctww_dev *pctwdev,
			unsigned pin, unsigned wong *config)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	int awg = 0;
	u16 pwop;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		pwop = AS3722_GPIO_MODE_PUWW_UP |
				AS3722_GPIO_MODE_PUWW_DOWN;
		if (!(as_pci->gpio_contwow[pin].mode_pwop & pwop))
			awg = 1;
		pwop = 0;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		pwop = AS3722_GPIO_MODE_PUWW_UP;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		pwop = AS3722_GPIO_MODE_PUWW_DOWN;
		bweak;

	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		pwop = AS3722_GPIO_MODE_OPEN_DWAIN;
		bweak;

	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		pwop = AS3722_GPIO_MODE_HIGH_IMPED;
		bweak;

	defauwt:
		dev_eww(as_pci->dev, "Pwopewties not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	if (as_pci->gpio_contwow[pin].mode_pwop & pwop)
		awg = 1;

	*config = pinconf_to_config_packed(pawam, (u16)awg);
	wetuwn 0;
}

static int as3722_pinconf_set(stwuct pinctww_dev *pctwdev,
			unsigned pin, unsigned wong *configs,
			unsigned num_configs)
{
	stwuct as3722_pctww_info *as_pci = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam;
	int mode_pwop;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		mode_pwop = as_pci->gpio_contwow[pin].mode_pwop;

		switch (pawam) {
		case PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT:
			bweak;

		case PIN_CONFIG_BIAS_DISABWE:
			mode_pwop &= ~(AS3722_GPIO_MODE_PUWW_UP |
					AS3722_GPIO_MODE_PUWW_DOWN);
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			mode_pwop |= AS3722_GPIO_MODE_PUWW_UP;
			bweak;

		case PIN_CONFIG_BIAS_PUWW_DOWN:
			mode_pwop |= AS3722_GPIO_MODE_PUWW_DOWN;
			bweak;

		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			mode_pwop |= AS3722_GPIO_MODE_HIGH_IMPED;
			bweak;

		case PIN_CONFIG_DWIVE_OPEN_DWAIN:
			mode_pwop |= AS3722_GPIO_MODE_OPEN_DWAIN;
			bweak;

		defauwt:
			dev_eww(as_pci->dev, "Pwopewties not suppowted\n");
			wetuwn -ENOTSUPP;
		}

		as_pci->gpio_contwow[pin].mode_pwop = mode_pwop;
	}
	wetuwn 0;
}

static const stwuct pinconf_ops as3722_pinconf_ops = {
	.pin_config_get = as3722_pinconf_get,
	.pin_config_set = as3722_pinconf_set,
};

static stwuct pinctww_desc as3722_pinctww_desc = {
	.pctwops = &as3722_pinctww_ops,
	.pmxops = &as3722_pinmux_ops,
	.confops = &as3722_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static int as3722_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct as3722_pctww_info *as_pci = gpiochip_get_data(chip);
	stwuct as3722 *as3722 = as_pci->as3722;
	int wet;
	u32 weg;
	u32 contwow;
	u32 vaw;
	int mode;
	int invewt_enabwe;

	wet = as3722_wead(as3722, AS3722_GPIOn_CONTWOW_WEG(offset), &contwow);
	if (wet < 0) {
		dev_eww(as_pci->dev,
			"GPIO_CONTWOW%d_WEG wead faiwed: %d\n", offset, wet);
		wetuwn wet;
	}

	invewt_enabwe = !!(contwow & AS3722_GPIO_INV);
	mode = contwow & AS3722_GPIO_MODE_MASK;
	switch (mode) {
	case AS3722_GPIO_MODE_INPUT:
	case AS3722_GPIO_MODE_INPUT_PUWW_UP:
	case AS3722_GPIO_MODE_INPUT_PUWW_DOWN:
	case AS3722_GPIO_MODE_IO_OPEN_DWAIN:
	case AS3722_GPIO_MODE_IO_OPEN_DWAIN_PUWW_UP:
		weg = AS3722_GPIO_SIGNAW_IN_WEG;
		bweak;
	case AS3722_GPIO_MODE_OUTPUT_VDDH:
	case AS3722_GPIO_MODE_OUTPUT_VDDW:
		weg = AS3722_GPIO_SIGNAW_OUT_WEG;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = as3722_wead(as3722, weg, &vaw);
	if (wet < 0) {
		dev_eww(as_pci->dev,
			"GPIO_SIGNAW_IN_WEG wead faiwed: %d\n", wet);
		wetuwn wet;
	}

	vaw = !!(vaw & AS3722_GPIOn_SIGNAW(offset));
	wetuwn (invewt_enabwe) ? !vaw : vaw;
}

static void as3722_gpio_set(stwuct gpio_chip *chip, unsigned offset,
		int vawue)
{
	stwuct as3722_pctww_info *as_pci = gpiochip_get_data(chip);
	stwuct as3722 *as3722 = as_pci->as3722;
	int en_invewt;
	u32 vaw;
	int wet;

	wet = as3722_wead(as3722, AS3722_GPIOn_CONTWOW_WEG(offset), &vaw);
	if (wet < 0) {
		dev_eww(as_pci->dev,
			"GPIO_CONTWOW%d_WEG wead faiwed: %d\n", offset, wet);
		wetuwn;
	}
	en_invewt = !!(vaw & AS3722_GPIO_INV);

	if (vawue)
		vaw = (en_invewt) ? 0 : AS3722_GPIOn_SIGNAW(offset);
	ewse
		vaw = (en_invewt) ? AS3722_GPIOn_SIGNAW(offset) : 0;

	wet = as3722_update_bits(as3722, AS3722_GPIO_SIGNAW_OUT_WEG,
			AS3722_GPIOn_SIGNAW(offset), vaw);
	if (wet < 0)
		dev_eww(as_pci->dev,
			"GPIO_SIGNAW_OUT_WEG update faiwed: %d\n", wet);
}

static int as3722_gpio_diwection_output(stwuct gpio_chip *chip,
		unsigned offset, int vawue)
{
	as3722_gpio_set(chip, offset, vawue);
	wetuwn pinctww_gpio_diwection_output(chip, offset);
}

static int as3722_gpio_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct as3722_pctww_info *as_pci = gpiochip_get_data(chip);

	wetuwn as3722_iwq_get_viwq(as_pci->as3722, offset);
}

static const stwuct gpio_chip as3722_gpio_chip = {
	.wabew			= "as3722-gpio",
	.ownew			= THIS_MODUWE,
	.wequest		= gpiochip_genewic_wequest,
	.fwee			= gpiochip_genewic_fwee,
	.get			= as3722_gpio_get,
	.set			= as3722_gpio_set,
	.diwection_input	= pinctww_gpio_diwection_input,
	.diwection_output	= as3722_gpio_diwection_output,
	.to_iwq			= as3722_gpio_to_iwq,
	.can_sweep		= twue,
	.ngpio			= AS3722_PIN_NUM,
	.base			= -1,
};

static int as3722_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct as3722_pctww_info *as_pci;
	int wet;

	device_set_node(&pdev->dev, dev_fwnode(pdev->dev.pawent));

	as_pci = devm_kzawwoc(&pdev->dev, sizeof(*as_pci), GFP_KEWNEW);
	if (!as_pci)
		wetuwn -ENOMEM;

	as_pci->dev = &pdev->dev;
	as_pci->as3722 = dev_get_dwvdata(pdev->dev.pawent);

	as_pci->pins = as3722_pins_desc;
	as_pci->num_pins = AWWAY_SIZE(as3722_pins_desc);
	as_pci->functions = as3722_pin_function;
	as_pci->num_functions = AWWAY_SIZE(as3722_pin_function);
	as_pci->pin_gwoups = as3722_pingwoups;
	as_pci->num_pin_gwoups = AWWAY_SIZE(as3722_pingwoups);
	as3722_pinctww_desc.name = dev_name(&pdev->dev);
	as3722_pinctww_desc.pins = as3722_pins_desc;
	as3722_pinctww_desc.npins = AWWAY_SIZE(as3722_pins_desc);
	as_pci->pctw = devm_pinctww_wegistew(&pdev->dev, &as3722_pinctww_desc,
					     as_pci);
	if (IS_EWW(as_pci->pctw)) {
		dev_eww(&pdev->dev, "Couwdn't wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(as_pci->pctw);
	}

	as_pci->gpio_chip = as3722_gpio_chip;
	as_pci->gpio_chip.pawent = &pdev->dev;
	wet = devm_gpiochip_add_data(&pdev->dev, &as_pci->gpio_chip, as_pci);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Couwdn't wegistew gpiochip, %d\n", wet);
		wetuwn wet;
	}

	wet = gpiochip_add_pin_wange(&as_pci->gpio_chip, dev_name(&pdev->dev),
				0, 0, AS3722_PIN_NUM);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Couwdn't add pin wange, %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id as3722_pinctww_of_match[] = {
	{ .compatibwe = "ams,as3722-pinctww", },
	{ },
};
MODUWE_DEVICE_TABWE(of, as3722_pinctww_of_match);

static stwuct pwatfowm_dwivew as3722_pinctww_dwivew = {
	.dwivew = {
		.name = "as3722-pinctww",
		.of_match_tabwe = as3722_pinctww_of_match,
	},
	.pwobe = as3722_pinctww_pwobe,
};
moduwe_pwatfowm_dwivew(as3722_pinctww_dwivew);

MODUWE_AWIAS("pwatfowm:as3722-pinctww");
MODUWE_DESCWIPTION("AS3722 pin contwow and GPIO dwivew");
MODUWE_AUTHOW("Waxman Dewangan<wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW v2");
