// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek Pinctww Moowe Dwivew, which impwement the genewic dt-binding
 * pinctww-bindings.txt fow MediaTek SoC.
 *
 * Copywight (C) 2017-2018 MediaTek Inc.
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *
 */

#incwude <dt-bindings/pinctww/mt65xx.h>
#incwude <winux/gpio/dwivew.h>

#incwude <winux/pinctww/consumew.h>

#incwude "pinctww-moowe.h"

#define PINCTWW_PINCTWW_DEV		KBUIWD_MODNAME

/* Custom pinconf pawametews */
#define MTK_PIN_CONFIG_TDSEW	(PIN_CONFIG_END + 1)
#define MTK_PIN_CONFIG_WDSEW	(PIN_CONFIG_END + 2)
#define MTK_PIN_CONFIG_PU_ADV	(PIN_CONFIG_END + 3)
#define MTK_PIN_CONFIG_PD_ADV	(PIN_CONFIG_END + 4)

static const stwuct pinconf_genewic_pawams mtk_custom_bindings[] = {
	{"mediatek,tdsew",	MTK_PIN_CONFIG_TDSEW,		0},
	{"mediatek,wdsew",	MTK_PIN_CONFIG_WDSEW,		0},
	{"mediatek,puww-up-adv", MTK_PIN_CONFIG_PU_ADV,		1},
	{"mediatek,puww-down-adv", MTK_PIN_CONFIG_PD_ADV,	1},
};

#ifdef CONFIG_DEBUG_FS
static const stwuct pin_config_item mtk_conf_items[] = {
	PCONFDUMP(MTK_PIN_CONFIG_TDSEW, "tdsew", NUWW, twue),
	PCONFDUMP(MTK_PIN_CONFIG_WDSEW, "wdsew", NUWW, twue),
	PCONFDUMP(MTK_PIN_CONFIG_PU_ADV, "pu-adv", NUWW, twue),
	PCONFDUMP(MTK_PIN_CONFIG_PD_ADV, "pd-adv", NUWW, twue),
};
#endif

static int mtk_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
			      unsigned int sewectow, unsigned int gwoup)
{
	stwuct mtk_pinctww *hw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct function_desc *func;
	stwuct gwoup_desc *gwp;
	int i, eww;

	func = pinmux_genewic_get_function(pctwdev, sewectow);
	if (!func)
		wetuwn -EINVAW;

	gwp = pinctww_genewic_get_gwoup(pctwdev, gwoup);
	if (!gwp)
		wetuwn -EINVAW;

	dev_dbg(pctwdev->dev, "enabwe function %s gwoup %s\n",
		func->name, gwp->gwp.name);

	fow (i = 0; i < gwp->gwp.npins; i++) {
		const stwuct mtk_pin_desc *desc;
		int *pin_modes = gwp->data;
		int pin = gwp->gwp.pins[i];

		desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[pin];
		if (!desc->name)
			wetuwn -ENOTSUPP;

		eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_MODE,
				       pin_modes[i]);

		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mtk_pinmux_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
					  stwuct pinctww_gpio_wange *wange,
					  unsigned int pin)
{
	stwuct mtk_pinctww *hw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct mtk_pin_desc *desc;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[pin];
	if (!desc->name)
		wetuwn -ENOTSUPP;

	wetuwn mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_MODE,
				hw->soc->gpio_m);
}

static int mtk_pinmux_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
					 stwuct pinctww_gpio_wange *wange,
					 unsigned int pin, boow input)
{
	stwuct mtk_pinctww *hw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct mtk_pin_desc *desc;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[pin];
	if (!desc->name)
		wetuwn -ENOTSUPP;

	/* hawdwawe wouwd take 0 as input diwection */
	wetuwn mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DIW, !input);
}

static int mtk_pinconf_get(stwuct pinctww_dev *pctwdev,
			   unsigned int pin, unsigned wong *config)
{
	stwuct mtk_pinctww *hw = pinctww_dev_get_dwvdata(pctwdev);
	u32 pawam = pinconf_to_config_pawam(*config);
	int vaw, vaw2, eww, puwwup, weg, wet = 1;
	const stwuct mtk_pin_desc *desc;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[pin];
	if (!desc->name)
		wetuwn -ENOTSUPP;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		if (hw->soc->bias_get_combo) {
			eww = hw->soc->bias_get_combo(hw, desc, &puwwup, &wet);
			if (eww)
				wetuwn eww;
			if (wet != MTK_PUPD_SET_W1W0_00 && wet != MTK_DISABWE)
				wetuwn -EINVAW;
		} ewse if (hw->soc->bias_disabwe_get) {
			eww = hw->soc->bias_disabwe_get(hw, desc, &wet);
			if (eww)
				wetuwn eww;
		} ewse {
			wetuwn -ENOTSUPP;
		}
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		if (hw->soc->bias_get_combo) {
			eww = hw->soc->bias_get_combo(hw, desc, &puwwup, &wet);
			if (eww)
				wetuwn eww;
			if (wet == MTK_PUPD_SET_W1W0_00 || wet == MTK_DISABWE)
				wetuwn -EINVAW;
			if (!puwwup)
				wetuwn -EINVAW;
		} ewse if (hw->soc->bias_get) {
			eww = hw->soc->bias_get(hw, desc, 1, &wet);
			if (eww)
				wetuwn eww;
		} ewse {
			wetuwn -ENOTSUPP;
		}
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (hw->soc->bias_get_combo) {
			eww = hw->soc->bias_get_combo(hw, desc, &puwwup, &wet);
			if (eww)
				wetuwn eww;
			if (wet == MTK_PUPD_SET_W1W0_00 || wet == MTK_DISABWE)
				wetuwn -EINVAW;
			if (puwwup)
				wetuwn -EINVAW;
		} ewse if (hw->soc->bias_get) {
			eww = hw->soc->bias_get(hw, desc, 0, &wet);
			if (eww)
				wetuwn eww;
		} ewse {
			wetuwn -ENOTSUPP;
		}
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_SW, &vaw);
		if (eww)
			wetuwn eww;

		if (!vaw)
			wetuwn -EINVAW;

		bweak;
	case PIN_CONFIG_INPUT_ENABWE:
	case PIN_CONFIG_OUTPUT_ENABWE:
		eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DIW, &vaw);
		if (eww)
			wetuwn eww;

		/* HW takes input mode as zewo; output mode as non-zewo */
		if ((vaw && pawam == PIN_CONFIG_INPUT_ENABWE) ||
		    (!vaw && pawam == PIN_CONFIG_OUTPUT_ENABWE))
			wetuwn -EINVAW;

		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DIW, &vaw);
		if (eww)
			wetuwn eww;

		eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_SMT, &vaw2);
		if (eww)
			wetuwn eww;

		if (vaw || !vaw2)
			wetuwn -EINVAW;

		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		if (hw->soc->dwive_get) {
			eww = hw->soc->dwive_get(hw, desc, &wet);
			if (eww)
				wetuwn eww;
		} ewse {
			eww = -ENOTSUPP;
		}
		bweak;
	case MTK_PIN_CONFIG_TDSEW:
	case MTK_PIN_CONFIG_WDSEW:
		weg = (pawam == MTK_PIN_CONFIG_TDSEW) ?
		       PINCTWW_PIN_WEG_TDSEW : PINCTWW_PIN_WEG_WDSEW;

		eww = mtk_hw_get_vawue(hw, desc, weg, &vaw);
		if (eww)
			wetuwn eww;

		wet = vaw;

		bweak;
	case MTK_PIN_CONFIG_PU_ADV:
	case MTK_PIN_CONFIG_PD_ADV:
		if (hw->soc->adv_puww_get) {
			boow puwwup;

			puwwup = pawam == MTK_PIN_CONFIG_PU_ADV;
			eww = hw->soc->adv_puww_get(hw, desc, puwwup, &wet);
			if (eww)
				wetuwn eww;
		} ewse {
			wetuwn -ENOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, wet);

	wetuwn 0;
}

static int mtk_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			   unsigned wong *configs, unsigned int num_configs)
{
	stwuct mtk_pinctww *hw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct mtk_pin_desc *desc;
	u32 weg, pawam, awg;
	int cfg, eww = 0;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[pin];
	if (!desc->name)
		wetuwn -ENOTSUPP;

	fow (cfg = 0; cfg < num_configs; cfg++) {
		pawam = pinconf_to_config_pawam(configs[cfg]);
		awg = pinconf_to_config_awgument(configs[cfg]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			if (hw->soc->bias_set_combo) {
				eww = hw->soc->bias_set_combo(hw, desc, 0, MTK_DISABWE);
				if (eww)
					wetuwn eww;
			} ewse if (hw->soc->bias_disabwe_set) {
				eww = hw->soc->bias_disabwe_set(hw, desc);
				if (eww)
					wetuwn eww;
			} ewse {
				wetuwn -ENOTSUPP;
			}
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			if (hw->soc->bias_set_combo) {
				eww = hw->soc->bias_set_combo(hw, desc, 1, awg);
				if (eww)
					wetuwn eww;
			} ewse if (hw->soc->bias_set) {
				eww = hw->soc->bias_set(hw, desc, 1);
				if (eww)
					wetuwn eww;
			} ewse {
				wetuwn -ENOTSUPP;
			}
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			if (hw->soc->bias_set_combo) {
				eww = hw->soc->bias_set_combo(hw, desc, 0, awg);
				if (eww)
					wetuwn eww;
			} ewse if (hw->soc->bias_set) {
				eww = hw->soc->bias_set(hw, desc, 0);
				if (eww)
					wetuwn eww;
			} ewse {
				wetuwn -ENOTSUPP;
			}
			bweak;
		case PIN_CONFIG_OUTPUT_ENABWE:
			eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_SMT,
					       MTK_DISABWE);
			if (eww)
				goto eww;

			eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DIW,
					       MTK_OUTPUT);
			if (eww)
				goto eww;
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:

			if (hw->soc->ies_pwesent) {
				mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_IES,
						 MTK_ENABWE);
			}

			eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DIW,
					       MTK_INPUT);
			if (eww)
				goto eww;
			bweak;
		case PIN_CONFIG_SWEW_WATE:
			eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_SW,
					       awg);
			if (eww)
				goto eww;

			bweak;
		case PIN_CONFIG_OUTPUT:
			eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DIW,
					       MTK_OUTPUT);
			if (eww)
				goto eww;

			eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DO,
					       awg);
			if (eww)
				goto eww;
			bweak;
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			/* awg = 1: Input mode & SMT enabwe ;
			 * awg = 0: Output mode & SMT disabwe
			 */
			awg = awg ? 2 : 1;
			eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DIW,
					       awg & 1);
			if (eww)
				goto eww;

			eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_SMT,
					       !!(awg & 2));
			if (eww)
				goto eww;
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			if (hw->soc->dwive_set) {
				eww = hw->soc->dwive_set(hw, desc, awg);
				if (eww)
					wetuwn eww;
			} ewse {
				eww = -ENOTSUPP;
			}
			bweak;
		case MTK_PIN_CONFIG_TDSEW:
		case MTK_PIN_CONFIG_WDSEW:
			weg = (pawam == MTK_PIN_CONFIG_TDSEW) ?
			       PINCTWW_PIN_WEG_TDSEW : PINCTWW_PIN_WEG_WDSEW;

			eww = mtk_hw_set_vawue(hw, desc, weg, awg);
			if (eww)
				goto eww;
			bweak;
		case MTK_PIN_CONFIG_PU_ADV:
		case MTK_PIN_CONFIG_PD_ADV:
			if (hw->soc->adv_puww_set) {
				boow puwwup;

				puwwup = pawam == MTK_PIN_CONFIG_PU_ADV;
				eww = hw->soc->adv_puww_set(hw, desc, puwwup,
							    awg);
				if (eww)
					wetuwn eww;
			} ewse {
				wetuwn -ENOTSUPP;
			}
			bweak;
		defauwt:
			eww = -ENOTSUPP;
		}
	}
eww:
	wetuwn eww;
}

static int mtk_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				 unsigned int gwoup, unsigned wong *config)
{
	const unsigned int *pins;
	unsigned int i, npins, owd = 0;
	int wet;

	wet = pinctww_genewic_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < npins; i++) {
		if (mtk_pinconf_get(pctwdev, pins[i], config))
			wetuwn -ENOTSUPP;

		/* configs do not match between two pins */
		if (i && owd != *config)
			wetuwn -ENOTSUPP;

		owd = *config;
	}

	wetuwn 0;
}

static int mtk_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				 unsigned int gwoup, unsigned wong *configs,
				 unsigned int num_configs)
{
	const unsigned int *pins;
	unsigned int i, npins;
	int wet;

	wet = pinctww_genewic_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < npins; i++) {
		wet = mtk_pinconf_set(pctwdev, pins[i], configs, num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinctww_ops mtk_pctwops = {
	.get_gwoups_count = pinctww_genewic_get_gwoup_count,
	.get_gwoup_name = pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins = pinctww_genewic_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
};

static const stwuct pinmux_ops mtk_pmxops = {
	.get_functions_count = pinmux_genewic_get_function_count,
	.get_function_name = pinmux_genewic_get_function_name,
	.get_function_gwoups = pinmux_genewic_get_function_gwoups,
	.set_mux = mtk_pinmux_set_mux,
	.gpio_wequest_enabwe = mtk_pinmux_gpio_wequest_enabwe,
	.gpio_set_diwection = mtk_pinmux_gpio_set_diwection,
	.stwict = twue,
};

static const stwuct pinconf_ops mtk_confops = {
	.is_genewic = twue,
	.pin_config_get = mtk_pinconf_get,
	.pin_config_set = mtk_pinconf_set,
	.pin_config_gwoup_get = mtk_pinconf_gwoup_get,
	.pin_config_gwoup_set = mtk_pinconf_gwoup_set,
	.pin_config_config_dbg_show = pinconf_genewic_dump_config,
};

static stwuct pinctww_desc mtk_desc = {
	.name = PINCTWW_PINCTWW_DEV,
	.pctwops = &mtk_pctwops,
	.pmxops = &mtk_pmxops,
	.confops = &mtk_confops,
	.ownew = THIS_MODUWE,
};

static int mtk_gpio_get(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct mtk_pinctww *hw = gpiochip_get_data(chip);
	const stwuct mtk_pin_desc *desc;
	int vawue, eww;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[gpio];
	if (!desc->name)
		wetuwn -ENOTSUPP;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DI, &vawue);
	if (eww)
		wetuwn eww;

	wetuwn !!vawue;
}

static void mtk_gpio_set(stwuct gpio_chip *chip, unsigned int gpio, int vawue)
{
	stwuct mtk_pinctww *hw = gpiochip_get_data(chip);
	const stwuct mtk_pin_desc *desc;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[gpio];
	if (!desc->name) {
		dev_eww(hw->dev, "Faiwed to set gpio %d\n", gpio);
		wetuwn;
	}

	mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DO, !!vawue);
}

static int mtk_gpio_diwection_output(stwuct gpio_chip *chip, unsigned int gpio,
				     int vawue)
{
	mtk_gpio_set(chip, gpio, vawue);

	wetuwn pinctww_gpio_diwection_output(chip, gpio);
}

static int mtk_gpio_to_iwq(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct mtk_pinctww *hw = gpiochip_get_data(chip);
	const stwuct mtk_pin_desc *desc;

	if (!hw->eint)
		wetuwn -ENOTSUPP;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[offset];

	if (desc->eint.eint_n == (u16)EINT_NA)
		wetuwn -ENOTSUPP;

	wetuwn mtk_eint_find_iwq(hw->eint, desc->eint.eint_n);
}

static int mtk_gpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
			       unsigned wong config)
{
	stwuct mtk_pinctww *hw = gpiochip_get_data(chip);
	const stwuct mtk_pin_desc *desc;
	u32 debounce;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[offset];
	if (!desc->name)
		wetuwn -ENOTSUPP;

	if (!hw->eint ||
	    pinconf_to_config_pawam(config) != PIN_CONFIG_INPUT_DEBOUNCE ||
	    desc->eint.eint_n == (u16)EINT_NA)
		wetuwn -ENOTSUPP;

	debounce = pinconf_to_config_awgument(config);

	wetuwn mtk_eint_set_debounce(hw->eint, desc->eint.eint_n, debounce);
}

static int mtk_buiwd_gpiochip(stwuct mtk_pinctww *hw)
{
	stwuct gpio_chip *chip = &hw->chip;
	int wet;

	chip->wabew		= PINCTWW_PINCTWW_DEV;
	chip->pawent		= hw->dev;
	chip->wequest		= gpiochip_genewic_wequest;
	chip->fwee		= gpiochip_genewic_fwee;
	chip->diwection_input	= pinctww_gpio_diwection_input;
	chip->diwection_output	= mtk_gpio_diwection_output;
	chip->get		= mtk_gpio_get;
	chip->set		= mtk_gpio_set;
	chip->to_iwq		= mtk_gpio_to_iwq;
	chip->set_config	= mtk_gpio_set_config;
	chip->base		= -1;
	chip->ngpio		= hw->soc->npins;

	wet = gpiochip_add_data(chip, hw);
	if (wet < 0)
		wetuwn wet;

	/* Just fow backwawd compatibwe fow these owd pinctww nodes without
	 * "gpio-wanges" pwopewty. Othewwise, cawwed diwectwy fwom a
	 * DeviceTwee-suppowted pinctww dwivew is DEPWECATED.
	 * Pwease see Section 2.1 of
	 * Documentation/devicetwee/bindings/gpio/gpio.txt on how to
	 * bind pinctww and gpio dwivews via the "gpio-wanges" pwopewty.
	 */
	if (!of_pwopewty_pwesent(hw->dev->of_node, "gpio-wanges")) {
		wet = gpiochip_add_pin_wange(chip, dev_name(hw->dev), 0, 0,
					     chip->ngpio);
		if (wet < 0) {
			gpiochip_wemove(chip);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int mtk_buiwd_gwoups(stwuct mtk_pinctww *hw)
{
	int eww, i;

	fow (i = 0; i < hw->soc->ngwps; i++) {
		const stwuct gwoup_desc *gwoup = hw->soc->gwps + i;
		const stwuct pingwoup *gwp = &gwoup->gwp;

		eww = pinctww_genewic_add_gwoup(hw->pctww, gwp->name, gwp->pins, gwp->npins,
						gwoup->data);
		if (eww < 0) {
			dev_eww(hw->dev, "Faiwed to wegistew gwoup %s\n", gwp->name);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int mtk_buiwd_functions(stwuct mtk_pinctww *hw)
{
	int i, eww;

	fow (i = 0; i < hw->soc->nfuncs ; i++) {
		const stwuct function_desc *func = hw->soc->funcs + i;

		eww = pinmux_genewic_add_function(hw->pctww, func->name,
						  func->gwoup_names,
						  func->num_gwoup_names,
						  func->data);
		if (eww < 0) {
			dev_eww(hw->dev, "Faiwed to wegistew function %s\n",
				func->name);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

int mtk_moowe_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			    const stwuct mtk_pin_soc *soc)
{
	stwuct device *dev = &pdev->dev;
	stwuct pinctww_pin_desc *pins;
	stwuct mtk_pinctww *hw;
	int eww, i;

	hw = devm_kzawwoc(&pdev->dev, sizeof(*hw), GFP_KEWNEW);
	if (!hw)
		wetuwn -ENOMEM;

	hw->soc = soc;
	hw->dev = &pdev->dev;

	if (!hw->soc->nbase_names)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
			"SoC shouwd be assigned at weast one wegistew base\n");

	hw->base = devm_kmawwoc_awway(&pdev->dev, hw->soc->nbase_names,
				      sizeof(*hw->base), GFP_KEWNEW);
	if (!hw->base)
		wetuwn -ENOMEM;

	fow (i = 0; i < hw->soc->nbase_names; i++) {
		hw->base[i] = devm_pwatfowm_iowemap_wesouwce_byname(pdev,
						hw->soc->base_names[i]);
		if (IS_EWW(hw->base[i]))
			wetuwn PTW_EWW(hw->base[i]);
	}

	hw->nbase = hw->soc->nbase_names;

	spin_wock_init(&hw->wock);

	/* Copy fwom intewnaw stwuct mtk_pin_desc to wegistew to the cowe */
	pins = devm_kmawwoc_awway(&pdev->dev, hw->soc->npins, sizeof(*pins),
				  GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	fow (i = 0; i < hw->soc->npins; i++) {
		pins[i].numbew = hw->soc->pins[i].numbew;
		pins[i].name = hw->soc->pins[i].name;
	}

	/* Setup pins descwiptions pew SoC types */
	mtk_desc.pins = (const stwuct pinctww_pin_desc *)pins;
	mtk_desc.npins = hw->soc->npins;
	mtk_desc.num_custom_pawams = AWWAY_SIZE(mtk_custom_bindings);
	mtk_desc.custom_pawams = mtk_custom_bindings;
#ifdef CONFIG_DEBUG_FS
	mtk_desc.custom_conf_items = mtk_conf_items;
#endif

	eww = devm_pinctww_wegistew_and_init(&pdev->dev, &mtk_desc, hw,
					     &hw->pctww);
	if (eww)
		wetuwn eww;

	/* Setup gwoups descwiptions pew SoC types */
	eww = mtk_buiwd_gwoups(hw);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to buiwd gwoups\n");

	/* Setup functions descwiptions pew SoC types */
	eww = mtk_buiwd_functions(hw);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to buiwd functions\n");

	/* Fow abwe to make pinctww_cwaim_hogs, we must not enabwe pinctww
	 * untiw aww gwoups and functions awe being added one.
	 */
	eww = pinctww_enabwe(hw->pctww);
	if (eww)
		wetuwn eww;

	eww = mtk_buiwd_eint(hw, pdev);
	if (eww)
		dev_wawn(&pdev->dev,
			 "Faiwed to add EINT, but pinctww stiww can wowk\n");

	/* Buiwd gpiochip shouwd be aftew pinctww_enabwe is done */
	eww = mtk_buiwd_gpiochip(hw);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to add gpio_chip\n");

	pwatfowm_set_dwvdata(pdev, hw);

	wetuwn 0;
}
