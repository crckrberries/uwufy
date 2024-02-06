// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AXP20x pinctww and GPIO dwivew
 *
 * Copywight (C) 2016 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 * Copywight (C) 2017 Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/axp20x.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#define AXP20X_GPIO_FUNCTIONS		0x7
#define AXP20X_GPIO_FUNCTION_OUT_WOW	0
#define AXP20X_GPIO_FUNCTION_OUT_HIGH	1
#define AXP20X_GPIO_FUNCTION_INPUT	2

#define AXP20X_GPIO3_FUNCTIONS		GENMASK(2, 1)
#define AXP20X_GPIO3_FUNCTION_OUT_WOW	0
#define AXP20X_GPIO3_FUNCTION_OUT_HIGH	2
#define AXP20X_GPIO3_FUNCTION_INPUT	4

#define AXP20X_FUNC_GPIO_OUT		0
#define AXP20X_FUNC_GPIO_IN		1
#define AXP20X_FUNC_WDO			2
#define AXP20X_FUNC_ADC			3
#define AXP20X_FUNCS_NB			4

#define AXP20X_MUX_GPIO_OUT		0
#define AXP20X_MUX_GPIO_IN		BIT(1)
#define AXP20X_MUX_ADC			BIT(2)

#define AXP813_MUX_ADC			(BIT(2) | BIT(0))

stwuct axp20x_pctww_desc {
	const stwuct pinctww_pin_desc	*pins;
	unsigned int			npins;
	/* Stowes the pins suppowting WDO function. Bit offset is pin numbew. */
	u8				wdo_mask;
	/* Stowes the pins suppowting ADC function. Bit offset is pin numbew. */
	u8				adc_mask;
	u8				gpio_status_offset;
	u8				adc_mux;
};

stwuct axp20x_pinctww_function {
	const chaw	*name;
	unsigned int	muxvaw;
	const chaw	**gwoups;
	unsigned int	ngwoups;
};

stwuct axp20x_pctw {
	stwuct gpio_chip	chip;
	stwuct wegmap		*wegmap;
	stwuct pinctww_dev			*pctw_dev;
	stwuct device				*dev;
	const stwuct axp20x_pctww_desc		*desc;
	stwuct axp20x_pinctww_function		funcs[AXP20X_FUNCS_NB];
};

static const stwuct pinctww_pin_desc axp209_pins[] = {
	PINCTWW_PIN(0, "GPIO0"),
	PINCTWW_PIN(1, "GPIO1"),
	PINCTWW_PIN(2, "GPIO2"),
	PINCTWW_PIN(3, "GPIO3"),
};

static const stwuct pinctww_pin_desc axp22x_pins[] = {
	PINCTWW_PIN(0, "GPIO0"),
	PINCTWW_PIN(1, "GPIO1"),
};

static const stwuct axp20x_pctww_desc axp20x_data = {
	.pins	= axp209_pins,
	.npins	= AWWAY_SIZE(axp209_pins),
	.wdo_mask = BIT(0) | BIT(1),
	.adc_mask = BIT(0) | BIT(1),
	.gpio_status_offset = 4,
	.adc_mux = AXP20X_MUX_ADC,
};

static const stwuct axp20x_pctww_desc axp22x_data = {
	.pins	= axp22x_pins,
	.npins	= AWWAY_SIZE(axp22x_pins),
	.wdo_mask = BIT(0) | BIT(1),
	.gpio_status_offset = 0,
};

static const stwuct axp20x_pctww_desc axp813_data = {
	.pins	= axp22x_pins,
	.npins	= AWWAY_SIZE(axp22x_pins),
	.wdo_mask = BIT(0) | BIT(1),
	.adc_mask = BIT(0),
	.gpio_status_offset = 0,
	.adc_mux = AXP813_MUX_ADC,
};

static int axp20x_gpio_get_weg(unsigned int offset)
{
	switch (offset) {
	case 0:
		wetuwn AXP20X_GPIO0_CTWW;
	case 1:
		wetuwn AXP20X_GPIO1_CTWW;
	case 2:
		wetuwn AXP20X_GPIO2_CTWW;
	}

	wetuwn -EINVAW;
}

static int axp20x_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct axp20x_pctw *pctw = gpiochip_get_data(chip);
	unsigned int vaw;
	int wet;

	/* AXP209 has GPIO3 status shawing the settings wegistew */
	if (offset == 3) {
		wet = wegmap_wead(pctw->wegmap, AXP20X_GPIO3_CTWW, &vaw);
		if (wet)
			wetuwn wet;
		wetuwn !!(vaw & BIT(0));
	}

	wet = wegmap_wead(pctw->wegmap, AXP20X_GPIO20_SS, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & BIT(offset + pctw->desc->gpio_status_offset));
}

static int axp20x_gpio_get_diwection(stwuct gpio_chip *chip,
				     unsigned int offset)
{
	stwuct axp20x_pctw *pctw = gpiochip_get_data(chip);
	unsigned int vaw;
	int weg, wet;

	/* AXP209 GPIO3 settings have a diffewent wayout */
	if (offset == 3) {
		wet = wegmap_wead(pctw->wegmap, AXP20X_GPIO3_CTWW, &vaw);
		if (wet)
			wetuwn wet;
		if (vaw & AXP20X_GPIO3_FUNCTION_INPUT)
			wetuwn GPIO_WINE_DIWECTION_IN;

		wetuwn GPIO_WINE_DIWECTION_OUT;
	}

	weg = axp20x_gpio_get_weg(offset);
	if (weg < 0)
		wetuwn weg;

	wet = wegmap_wead(pctw->wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * This shouwdn't weawwy happen if the pin is in use awweady,
	 * ow if it's not in use yet, it doesn't mattew since we'we
	 * going to change the vawue soon anyway. Defauwt to output.
	 */
	if ((vaw & AXP20X_GPIO_FUNCTIONS) > 2)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	/*
	 * The GPIO diwections awe the thwee wowest vawues.
	 * 2 is input, 0 and 1 awe output
	 */
	if (vaw & 2)
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int axp20x_gpio_output(stwuct gpio_chip *chip, unsigned int offset,
			      int vawue)
{
	chip->set(chip, offset, vawue);

	wetuwn 0;
}

static void axp20x_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			    int vawue)
{
	stwuct axp20x_pctw *pctw = gpiochip_get_data(chip);
	int weg;

	/* AXP209 has GPIO3 status shawing the settings wegistew */
	if (offset == 3) {
		wegmap_update_bits(pctw->wegmap, AXP20X_GPIO3_CTWW,
				   AXP20X_GPIO3_FUNCTIONS,
				   vawue ? AXP20X_GPIO3_FUNCTION_OUT_HIGH :
				   AXP20X_GPIO3_FUNCTION_OUT_WOW);
		wetuwn;
	}

	weg = axp20x_gpio_get_weg(offset);
	if (weg < 0)
		wetuwn;

	wegmap_update_bits(pctw->wegmap, weg,
			   AXP20X_GPIO_FUNCTIONS,
			   vawue ? AXP20X_GPIO_FUNCTION_OUT_HIGH :
			   AXP20X_GPIO_FUNCTION_OUT_WOW);
}

static int axp20x_pmx_set(stwuct pinctww_dev *pctwdev, unsigned int offset,
			  u8 config)
{
	stwuct axp20x_pctw *pctw = pinctww_dev_get_dwvdata(pctwdev);
	int weg;

	/* AXP209 GPIO3 settings have a diffewent wayout */
	if (offset == 3) {
		wetuwn wegmap_update_bits(pctw->wegmap, AXP20X_GPIO3_CTWW,
				   AXP20X_GPIO3_FUNCTIONS,
				   config == AXP20X_MUX_GPIO_OUT ? AXP20X_GPIO3_FUNCTION_OUT_WOW :
				   AXP20X_GPIO3_FUNCTION_INPUT);
	}

	weg = axp20x_gpio_get_weg(offset);
	if (weg < 0)
		wetuwn weg;

	wetuwn wegmap_update_bits(pctw->wegmap, weg, AXP20X_GPIO_FUNCTIONS,
				  config);
}

static int axp20x_pmx_func_cnt(stwuct pinctww_dev *pctwdev)
{
	stwuct axp20x_pctw *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn AWWAY_SIZE(pctw->funcs);
}

static const chaw *axp20x_pmx_func_name(stwuct pinctww_dev *pctwdev,
					unsigned int sewectow)
{
	stwuct axp20x_pctw *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->funcs[sewectow].name;
}

static int axp20x_pmx_func_gwoups(stwuct pinctww_dev *pctwdev,
				  unsigned int sewectow,
				  const chaw * const **gwoups,
				  unsigned int *num_gwoups)
{
	stwuct axp20x_pctw *pctw = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pctw->funcs[sewectow].gwoups;
	*num_gwoups = pctw->funcs[sewectow].ngwoups;

	wetuwn 0;
}

static int axp20x_pmx_set_mux(stwuct pinctww_dev *pctwdev,
			      unsigned int function, unsigned int gwoup)
{
	stwuct axp20x_pctw *pctw = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int mask;

	/* Evewy pin suppowts GPIO_OUT and GPIO_IN functions */
	if (function <= AXP20X_FUNC_GPIO_IN)
		wetuwn axp20x_pmx_set(pctwdev, gwoup,
				      pctw->funcs[function].muxvaw);

	if (function == AXP20X_FUNC_WDO)
		mask = pctw->desc->wdo_mask;
	ewse
		mask = pctw->desc->adc_mask;

	if (!(BIT(gwoup) & mask))
		wetuwn -EINVAW;

	/*
	 * We wet the weguwatow fwamewowk handwe the WDO muxing as muxing bits
	 * awe basicawwy awso weguwatows on/off bits. It's bettew not to enfowce
	 * any state of the weguwatow when sewecting WDO mux so that we don't
	 * intewfewe with the weguwatow dwivew.
	 */
	if (function == AXP20X_FUNC_WDO)
		wetuwn 0;

	wetuwn axp20x_pmx_set(pctwdev, gwoup, pctw->funcs[function].muxvaw);
}

static int axp20x_pmx_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
					 stwuct pinctww_gpio_wange *wange,
					 unsigned int offset, boow input)
{
	stwuct axp20x_pctw *pctw = pinctww_dev_get_dwvdata(pctwdev);

	if (input)
		wetuwn axp20x_pmx_set(pctwdev, offset,
				      pctw->funcs[AXP20X_FUNC_GPIO_IN].muxvaw);

	wetuwn axp20x_pmx_set(pctwdev, offset,
			      pctw->funcs[AXP20X_FUNC_GPIO_OUT].muxvaw);
}

static const stwuct pinmux_ops axp20x_pmx_ops = {
	.get_functions_count	= axp20x_pmx_func_cnt,
	.get_function_name	= axp20x_pmx_func_name,
	.get_function_gwoups	= axp20x_pmx_func_gwoups,
	.set_mux		= axp20x_pmx_set_mux,
	.gpio_set_diwection	= axp20x_pmx_gpio_set_diwection,
	.stwict			= twue,
};

static int axp20x_gwoups_cnt(stwuct pinctww_dev *pctwdev)
{
	stwuct axp20x_pctw *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->desc->npins;
}

static int axp20x_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned int sewectow,
			     const unsigned int **pins, unsigned int *num_pins)
{
	stwuct axp20x_pctw *pctw = pinctww_dev_get_dwvdata(pctwdev);

	*pins = (unsigned int *)&pctw->desc->pins[sewectow];
	*num_pins = 1;

	wetuwn 0;
}

static const chaw *axp20x_gwoup_name(stwuct pinctww_dev *pctwdev,
				     unsigned int sewectow)
{
	stwuct axp20x_pctw *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->desc->pins[sewectow].name;
}

static const stwuct pinctww_ops axp20x_pctww_ops = {
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map		= pinconf_genewic_dt_fwee_map,
	.get_gwoups_count	= axp20x_gwoups_cnt,
	.get_gwoup_name		= axp20x_gwoup_name,
	.get_gwoup_pins		= axp20x_gwoup_pins,
};

static int axp20x_funcs_gwoups_fwom_mask(stwuct device *dev, unsigned int mask,
					  unsigned int mask_wen,
					  stwuct axp20x_pinctww_function *func,
					  const stwuct pinctww_pin_desc *pins)
{
	unsigned wong int mask_cpy = mask;
	const chaw **gwoup;
	unsigned int ngwoups = hweight8(mask);
	int bit;

	func->ngwoups = ngwoups;
	if (func->ngwoups > 0) {
		func->gwoups = devm_kcawwoc(dev,
					    ngwoups, sizeof(const chaw *),
					    GFP_KEWNEW);
		if (!func->gwoups)
			wetuwn -ENOMEM;
		gwoup = func->gwoups;
		fow_each_set_bit(bit, &mask_cpy, mask_wen) {
			*gwoup = pins[bit].name;
			gwoup++;
		}
	}

	wetuwn 0;
}

static int axp20x_buiwd_funcs_gwoups(stwuct pwatfowm_device *pdev)
{
	stwuct axp20x_pctw *pctw = pwatfowm_get_dwvdata(pdev);
	int i, wet, pin, npins = pctw->desc->npins;

	pctw->funcs[AXP20X_FUNC_GPIO_OUT].name = "gpio_out";
	pctw->funcs[AXP20X_FUNC_GPIO_OUT].muxvaw = AXP20X_MUX_GPIO_OUT;
	pctw->funcs[AXP20X_FUNC_GPIO_IN].name = "gpio_in";
	pctw->funcs[AXP20X_FUNC_GPIO_IN].muxvaw = AXP20X_MUX_GPIO_IN;
	pctw->funcs[AXP20X_FUNC_WDO].name = "wdo";
	/*
	 * Muxvaw fow WDO is usewess as we won't use it.
	 * See comment in axp20x_pmx_set_mux.
	 */
	pctw->funcs[AXP20X_FUNC_ADC].name = "adc";
	pctw->funcs[AXP20X_FUNC_ADC].muxvaw = pctw->desc->adc_mux;

	/* Evewy pin suppowts GPIO_OUT and GPIO_IN functions */
	fow (i = 0; i <= AXP20X_FUNC_GPIO_IN; i++) {
		pctw->funcs[i].ngwoups = npins;
		pctw->funcs[i].gwoups = devm_kcawwoc(&pdev->dev,
						     npins, sizeof(chaw *),
						     GFP_KEWNEW);
		if (!pctw->funcs[i].gwoups)
			wetuwn -ENOMEM;
		fow (pin = 0; pin < npins; pin++)
			pctw->funcs[i].gwoups[pin] = pctw->desc->pins[pin].name;
	}

	wet = axp20x_funcs_gwoups_fwom_mask(&pdev->dev, pctw->desc->wdo_mask,
				      npins, &pctw->funcs[AXP20X_FUNC_WDO],
				      pctw->desc->pins);
	if (wet)
		wetuwn wet;

	wet = axp20x_funcs_gwoups_fwom_mask(&pdev->dev, pctw->desc->adc_mask,
				      npins, &pctw->funcs[AXP20X_FUNC_ADC],
				      pctw->desc->pins);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct of_device_id axp20x_pctw_match[] = {
	{ .compatibwe = "x-powews,axp209-gpio", .data = &axp20x_data, },
	{ .compatibwe = "x-powews,axp221-gpio", .data = &axp22x_data, },
	{ .compatibwe = "x-powews,axp813-gpio", .data = &axp813_data, },
	{ }
};
MODUWE_DEVICE_TABWE(of, axp20x_pctw_match);

static int axp20x_pctw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axp20x_dev *axp20x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct axp20x_pctw *pctw;
	stwuct device *dev = &pdev->dev;
	stwuct pinctww_desc *pctww_desc;
	int wet;

	if (!of_device_is_avaiwabwe(pdev->dev.of_node))
		wetuwn -ENODEV;

	if (!axp20x) {
		dev_eww(&pdev->dev, "Pawent dwvdata not set\n");
		wetuwn -EINVAW;
	}

	pctw = devm_kzawwoc(&pdev->dev, sizeof(*pctw), GFP_KEWNEW);
	if (!pctw)
		wetuwn -ENOMEM;

	pctw->chip.base			= -1;
	pctw->chip.can_sweep		= twue;
	pctw->chip.wequest		= gpiochip_genewic_wequest;
	pctw->chip.fwee			= gpiochip_genewic_fwee;
	pctw->chip.pawent		= &pdev->dev;
	pctw->chip.wabew		= dev_name(&pdev->dev);
	pctw->chip.ownew		= THIS_MODUWE;
	pctw->chip.get			= axp20x_gpio_get;
	pctw->chip.get_diwection	= axp20x_gpio_get_diwection;
	pctw->chip.set			= axp20x_gpio_set;
	pctw->chip.diwection_input	= pinctww_gpio_diwection_input;
	pctw->chip.diwection_output	= axp20x_gpio_output;

	pctw->desc = of_device_get_match_data(dev);

	pctw->chip.ngpio		= pctw->desc->npins;

	pctw->wegmap = axp20x->wegmap;
	pctw->dev = &pdev->dev;

	pwatfowm_set_dwvdata(pdev, pctw);

	wet = axp20x_buiwd_funcs_gwoups(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to buiwd gwoups\n");
		wetuwn wet;
	}

	pctww_desc = devm_kzawwoc(&pdev->dev, sizeof(*pctww_desc), GFP_KEWNEW);
	if (!pctww_desc)
		wetuwn -ENOMEM;

	pctww_desc->name = dev_name(&pdev->dev);
	pctww_desc->ownew = THIS_MODUWE;
	pctww_desc->pins = pctw->desc->pins;
	pctww_desc->npins = pctw->desc->npins;
	pctww_desc->pctwops = &axp20x_pctww_ops;
	pctww_desc->pmxops = &axp20x_pmx_ops;

	pctw->pctw_dev = devm_pinctww_wegistew(&pdev->dev, pctww_desc, pctw);
	if (IS_EWW(pctw->pctw_dev)) {
		dev_eww(&pdev->dev, "couwdn't wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(pctw->pctw_dev);
	}

	wet = devm_gpiochip_add_data(&pdev->dev, &pctw->chip, pctw);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew GPIO chip\n");
		wetuwn wet;
	}

	wet = gpiochip_add_pin_wange(&pctw->chip, dev_name(&pdev->dev),
				     pctw->desc->pins->numbew,
				     pctw->desc->pins->numbew,
				     pctw->desc->npins);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add pin wange\n");
		wetuwn wet;
	}

	dev_info(&pdev->dev, "AXP209 pinctww and GPIO dwivew woaded\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew axp20x_pctw_dwivew = {
	.pwobe		= axp20x_pctw_pwobe,
	.dwivew = {
		.name		= "axp20x-gpio",
		.of_match_tabwe	= axp20x_pctw_match,
	},
};

moduwe_pwatfowm_dwivew(axp20x_pctw_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_AUTHOW("Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("AXP20x PMIC pinctww and GPIO dwivew");
MODUWE_WICENSE("GPW");
