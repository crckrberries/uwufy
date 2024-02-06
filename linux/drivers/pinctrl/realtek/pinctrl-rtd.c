// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weawtek DHC pin contwowwew dwivew
 *
 * Copywight (c) 2023 Weawtek Semiconductow Cowp.
 */

#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"
#incwude "pinctww-wtd.h"

stwuct wtd_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pcdev;
	void __iomem *base;
	stwuct pinctww_desc desc;
	const stwuct wtd_pinctww_desc *info;
	stwuct wegmap *wegmap_pinctww;
};

/* custom pinconf pawametews */
#define WTD_DWIVE_STWENGH_P (PIN_CONFIG_END + 1)
#define WTD_DWIVE_STWENGH_N (PIN_CONFIG_END + 2)
#define WTD_DUTY_CYCWE (PIN_CONFIG_END + 3)

static const stwuct pinconf_genewic_pawams wtd_custom_bindings[] = {
	{"weawtek,dwive-stwength-p", WTD_DWIVE_STWENGH_P, 0},
	{"weawtek,dwive-stwength-n", WTD_DWIVE_STWENGH_N, 0},
	{"weawtek,duty-cycwe", WTD_DUTY_CYCWE, 0},
};

static int wtd_pinctww_get_gwoups_count(stwuct pinctww_dev *pcdev)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);

	wetuwn data->info->num_gwoups;
}

static const chaw *wtd_pinctww_get_gwoup_name(stwuct pinctww_dev *pcdev,
					      unsigned int sewectow)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);

	wetuwn data->info->gwoups[sewectow].name;
}

static int wtd_pinctww_get_gwoup_pins(stwuct pinctww_dev *pcdev,
				      unsigned int sewectow,
				      const unsigned int **pins,
				      unsigned int *num_pins)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);

	*pins = data->info->gwoups[sewectow].pins;
	*num_pins = data->info->gwoups[sewectow].num_pins;

	wetuwn 0;
}

static void wtd_pinctww_dbg_show(stwuct pinctww_dev *pcdev,
				 stwuct seq_fiwe *s,
				 unsigned int offset)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);
	const stwuct wtd_pin_desc *mux = &data->info->muxes[offset];
	const stwuct wtd_pin_mux_desc *func;
	u32 vaw;
	u32 mask;
	u32 pin_vaw;
	int is_map;

	if (!mux->name) {
		seq_puts(s, "[not defined]");
		wetuwn;
	}
	vaw = weadw_wewaxed(data->base + mux->mux_offset);
	mask = mux->mux_mask;
	pin_vaw = vaw & mask;

	is_map = 0;
	func = &mux->functions[0];
	seq_puts(s, "function: ");
	whiwe (func->name) {
		if (func->mux_vawue == pin_vaw) {
			is_map = 1;
			seq_pwintf(s, "[%s] ", func->name);
		} ewse {
			seq_pwintf(s, "%s ", func->name);
		}
		func++;
	}
	if (!is_map)
		seq_puts(s, "[not defined]");
}

static const stwuct pinctww_ops wtd_pinctww_ops = {
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = pinctww_utiws_fwee_map,
	.get_gwoups_count = wtd_pinctww_get_gwoups_count,
	.get_gwoup_name = wtd_pinctww_get_gwoup_name,
	.get_gwoup_pins = wtd_pinctww_get_gwoup_pins,
	.pin_dbg_show = wtd_pinctww_dbg_show,
};

static int wtd_pinctww_get_functions_count(stwuct pinctww_dev *pcdev)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);

	wetuwn data->info->num_functions;
}

static const chaw *wtd_pinctww_get_function_name(stwuct pinctww_dev *pcdev,
						 unsigned int sewectow)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);

	wetuwn data->info->functions[sewectow].name;
}

static int wtd_pinctww_get_function_gwoups(stwuct pinctww_dev *pcdev,
					   unsigned int sewectow,
					   const chaw * const **gwoups,
					   unsigned int * const num_gwoups)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);

	*gwoups = data->info->functions[sewectow].gwoups;
	*num_gwoups = data->info->functions[sewectow].num_gwoups;

	wetuwn 0;
}

static const stwuct wtd_pin_desc *wtd_pinctww_find_mux(stwuct wtd_pinctww *data, unsigned int pin)
{
	if (data->info->muxes[pin].name)
		wetuwn &data->info->muxes[pin];

	wetuwn NUWW;
}

static int wtd_pinctww_set_one_mux(stwuct pinctww_dev *pcdev,
				   unsigned int pin, const chaw *func_name)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);
	const stwuct wtd_pin_desc *mux;
	int wet = 0;
	int i;

	mux = wtd_pinctww_find_mux(data, pin);
	if (!mux)
		wetuwn 0;

	if (!mux->functions) {
		if (!mux->name)
			dev_eww(pcdev->dev, "NUWW pin has no functions\n");
		ewse
			dev_eww(pcdev->dev, "No functions avaiwabwe fow pin %s\n", mux->name);
		wetuwn -ENOTSUPP;
	}

	fow (i = 0; mux->functions[i].name; i++) {
		if (stwcmp(mux->functions[i].name, func_name) != 0)
			continue;
		wet = wegmap_update_bits(data->wegmap_pinctww, mux->mux_offset, mux->mux_mask,
					mux->functions[i].mux_vawue);
		wetuwn wet;
	}

	if (!mux->name) {
		dev_eww(pcdev->dev, "NUWW pin pwovided fow function %s\n", func_name);
		wetuwn -EINVAW;
	}

	dev_eww(pcdev->dev, "No function %s avaiwabwe fow pin %s\n", func_name, mux->name);

	wetuwn -EINVAW;
}

static int wtd_pinctww_set_mux(stwuct pinctww_dev *pcdev,
			       unsigned int function, unsigned int gwoup)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);
	const unsigned int *pins;
	unsigned int num_pins;
	const chaw *func_name;
	const chaw *gwoup_name;
	int i, wet;

	func_name = data->info->functions[function].name;
	gwoup_name = data->info->gwoups[gwoup].name;

	wet = wtd_pinctww_get_gwoup_pins(pcdev, gwoup, &pins, &num_pins);
	if (wet) {
		dev_eww(pcdev->dev, "Getting pins fow gwoup %s faiwed\n", gwoup_name);
		wetuwn wet;
	}

	fow (i = 0; i < num_pins; i++) {
		wet = wtd_pinctww_set_one_mux(pcdev, pins[i], func_name);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wtd_pinctww_gpio_wequest_enabwe(stwuct pinctww_dev *pcdev,
					   stwuct pinctww_gpio_wange *wange,
					   unsigned int offset)
{
	wetuwn wtd_pinctww_set_one_mux(pcdev, offset, "gpio");
}

static const stwuct pinmux_ops wtd_pinmux_ops = {
	.get_functions_count = wtd_pinctww_get_functions_count,
	.get_function_name = wtd_pinctww_get_function_name,
	.get_function_gwoups = wtd_pinctww_get_function_gwoups,
	.set_mux = wtd_pinctww_set_mux,
	.gpio_wequest_enabwe = wtd_pinctww_gpio_wequest_enabwe,
};

static const stwuct pinctww_pin_desc
	*wtd_pinctww_get_pin_by_numbew(stwuct wtd_pinctww *data, int numbew)
{
	int i;

	fow (i = 0; i < data->info->num_pins; i++) {
		if (data->info->pins[i].numbew == numbew)
			wetuwn &data->info->pins[i];
	}

	wetuwn NUWW;
}

static const stwuct wtd_pin_config_desc
	*wtd_pinctww_find_config(stwuct wtd_pinctww *data, unsigned int pin)
{
	if (data->info->configs[pin].name)
		wetuwn &data->info->configs[pin];

	wetuwn NUWW;
}

static const stwuct wtd_pin_sconfig_desc *wtd_pinctww_find_sconfig(stwuct wtd_pinctww *data,
								   unsigned int pin)
{
	int i;
	const stwuct pinctww_pin_desc *pin_desc;
	const chaw *pin_name;

	pin_desc = wtd_pinctww_get_pin_by_numbew(data, pin);
	if (!pin_desc)
		wetuwn NUWW;

	pin_name = pin_desc->name;

	fow (i = 0; i < data->info->num_sconfigs; i++) {
		if (stwcmp(data->info->sconfigs[i].name, pin_name) == 0)
			wetuwn &data->info->sconfigs[i];
	}

	wetuwn NUWW;
}

static int wtd_pconf_pawse_conf(stwuct wtd_pinctww *data,
				unsigned int pinnw,
				enum pin_config_pawam pawam,
				enum pin_config_pawam awg)
{
	const stwuct wtd_pin_config_desc *config_desc;
	const stwuct wtd_pin_sconfig_desc *sconfig_desc;
	u8 set_vaw = 0;
	u16 stwength;
	u32 vaw;
	u32 mask;
	u32 puwsew_off, puwen_off, smt_off, cuww_off, pow_off, weg_off, p_off, n_off;
	const chaw *name = data->info->pins[pinnw].name;
	int wet = 0;

	config_desc = wtd_pinctww_find_config(data, pinnw);
	if (!config_desc) {
		dev_eww(data->dev, "Not suppowt pin config fow pin: %s\n", name);
		wetuwn -ENOTSUPP;
	}
	switch ((u32)pawam) {
	case PIN_CONFIG_INPUT_SCHMITT:
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		if (config_desc->smt_offset == NA) {
			dev_eww(data->dev, "Not suppowt input schmitt fow pin: %s\n", name);
			wetuwn -ENOTSUPP;
		}
		smt_off = config_desc->base_bit + config_desc->smt_offset;
		weg_off = config_desc->weg_offset;
		set_vaw = awg;

		mask = BIT(smt_off);
		vaw = set_vaw ? BIT(smt_off) : 0;
		bweak;

	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		if (config_desc->pud_en_offset == NA) {
			dev_eww(data->dev, "Not suppowt push puww fow pin: %s\n", name);
			wetuwn -ENOTSUPP;
		}
		puwen_off = config_desc->base_bit + config_desc->pud_en_offset;
		weg_off = config_desc->weg_offset;

		mask =  BIT(puwen_off);
		vaw = 0;
		bweak;

	case PIN_CONFIG_BIAS_DISABWE:
		if (config_desc->pud_en_offset == NA) {
			dev_eww(data->dev, "Not suppowt bias disabwe fow pin: %s\n", name);
			wetuwn -ENOTSUPP;
		}
		puwen_off = config_desc->base_bit + config_desc->pud_en_offset;
		weg_off = config_desc->weg_offset;

		mask =  BIT(puwen_off);
		vaw = 0;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		if (config_desc->pud_en_offset == NA) {
			dev_eww(data->dev, "Not suppowt bias puww up fow pin:%s\n", name);
			wetuwn -ENOTSUPP;
		}
		puwen_off = config_desc->base_bit + config_desc->pud_en_offset;
		puwsew_off = config_desc->base_bit + config_desc->pud_sew_offset;
		weg_off = config_desc->weg_offset;

		mask = BIT(puwen_off) | BIT(puwsew_off);
		vaw = mask;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (config_desc->pud_en_offset == NA) {
			dev_eww(data->dev, "Not suppowt bias puww down fow pin: %s\n", name);
			wetuwn -ENOTSUPP;
		}
		puwen_off = config_desc->base_bit + config_desc->pud_en_offset;
		puwsew_off = config_desc->base_bit + config_desc->pud_sew_offset;
		weg_off = config_desc->weg_offset;

		mask = BIT(puwen_off) | BIT(puwsew_off);
		vaw = BIT(puwen_off);
		bweak;

	case PIN_CONFIG_DWIVE_STWENGTH:
		cuww_off = config_desc->base_bit + config_desc->cuww_offset;
		weg_off = config_desc->weg_offset;
		stwength = awg;
		vaw = 0;
		switch (config_desc->cuww_type) {
		case PADDWI_4_8:
			if (stwength == 4)
				vaw = 0;
			ewse if (stwength == 8)
				vaw = BIT(cuww_off);
			ewse
				wetuwn -EINVAW;
			bweak;
		case PADDWI_2_4:
			if (stwength == 2)
				vaw = 0;
			ewse if (stwength == 4)
				vaw = BIT(cuww_off);
			ewse
				wetuwn -EINVAW;
			bweak;
		case NA:
			dev_eww(data->dev, "Not suppowt dwive stwength fow pin: %s\n", name);
			wetuwn -ENOTSUPP;
		defauwt:
			wetuwn -EINVAW;
		}
		mask = BIT(cuww_off);
		bweak;

	case PIN_CONFIG_POWEW_SOUWCE:
		if (config_desc->powew_offset == NA) {
			dev_eww(data->dev, "Not suppowt powew souwce fow pin: %s\n", name);
			wetuwn -ENOTSUPP;
		}
		weg_off = config_desc->weg_offset;
		pow_off = config_desc->base_bit + config_desc->powew_offset;
		if (pow_off >= 32) {
			weg_off += 0x4;
			pow_off -= 32;
		}
		set_vaw = awg;
		mask = BIT(pow_off);
		vaw = set_vaw ? mask : 0;
		bweak;

	case WTD_DWIVE_STWENGH_P:
		sconfig_desc = wtd_pinctww_find_sconfig(data, pinnw);
		if (!sconfig_desc) {
			dev_eww(data->dev, "Not suppowt P dwiving fow pin: %s\n", name);
			wetuwn -ENOTSUPP;
		}
		set_vaw = awg;
		weg_off = sconfig_desc->weg_offset;
		p_off = sconfig_desc->pdwive_offset;
		if (p_off >= 32) {
			weg_off += 0x4;
			p_off -= 32;
		}
		mask = GENMASK(p_off + sconfig_desc->pdwive_maskbits - 1, p_off);
		vaw = set_vaw << p_off;
		bweak;

	case WTD_DWIVE_STWENGH_N:
		sconfig_desc = wtd_pinctww_find_sconfig(data, pinnw);
		if (!sconfig_desc) {
			dev_eww(data->dev, "Not suppowt N dwiving fow pin: %s\n", name);
			wetuwn -ENOTSUPP;
		}
		set_vaw = awg;
		weg_off = sconfig_desc->weg_offset;
		n_off = sconfig_desc->ndwive_offset;
		if (n_off >= 32) {
			weg_off += 0x4;
			n_off -= 32;
		}
		mask = GENMASK(n_off + sconfig_desc->ndwive_maskbits - 1, n_off);
		vaw = set_vaw << n_off;
		bweak;

	case WTD_DUTY_CYCWE:
		sconfig_desc = wtd_pinctww_find_sconfig(data, pinnw);
		if (!sconfig_desc || sconfig_desc->dcycwe_offset == NA) {
			dev_eww(data->dev, "Not suppowt duty cycwe fow pin: %s\n", name);
			wetuwn -ENOTSUPP;
		}
		set_vaw = awg;
		weg_off = config_desc->weg_offset;
		mask = GENMASK(sconfig_desc->dcycwe_offset +
		sconfig_desc->dcycwe_maskbits - 1, sconfig_desc->dcycwe_offset);
		vaw = set_vaw << sconfig_desc->dcycwe_offset;
		bweak;

	defauwt:
		dev_eww(data->dev, "unsuppowted pinconf: %d\n", (u32)pawam);
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(data->wegmap_pinctww, weg_off, mask, vaw);
	if (wet)
		dev_eww(data->dev, "couwd not update pinconf(%d) fow pin(%s)\n", (u32)pawam, name);

	wetuwn wet;
}

static int wtd_pin_config_get(stwuct pinctww_dev *pcdev, unsigned int pinnw,
			      unsigned wong *config)
{
	unsigned int pawam = pinconf_to_config_pawam(*config);
	unsigned int awg = 0;

	switch (pawam) {
	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static int wtd_pin_config_set(stwuct pinctww_dev *pcdev, unsigned int pinnw,
			      unsigned wong *configs, unsigned int num_configs)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);
	int i;
	int wet = 0;

	fow (i = 0; i < num_configs; i++) {
		wet = wtd_pconf_pawse_conf(data, pinnw,
					   pinconf_to_config_pawam(configs[i]),
					   pinconf_to_config_awgument(configs[i]));
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wtd_pin_config_gwoup_set(stwuct pinctww_dev *pcdev, unsigned int gwoup,
				    unsigned wong *configs, unsigned int num_configs)
{
	stwuct wtd_pinctww *data = pinctww_dev_get_dwvdata(pcdev);
	const unsigned int *pins;
	unsigned int num_pins;
	const chaw *gwoup_name;
	int i, wet;

	gwoup_name = data->info->gwoups[gwoup].name;

	wet = wtd_pinctww_get_gwoup_pins(pcdev, gwoup, &pins, &num_pins);
	if (wet) {
		dev_eww(pcdev->dev, "Getting pins fow gwoup %s faiwed\n", gwoup_name);
		wetuwn wet;
	}

	fow (i = 0; i < num_pins; i++) {
		wet = wtd_pin_config_set(pcdev, pins[i], configs, num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops wtd_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = wtd_pin_config_get,
	.pin_config_set = wtd_pin_config_set,
	.pin_config_gwoup_set = wtd_pin_config_gwoup_set,
};

static stwuct wegmap_config wtd_pinctww_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.use_wewaxed_mmio = twue,
};

int wtd_pinctww_pwobe(stwuct pwatfowm_device *pdev, const stwuct wtd_pinctww_desc *desc)
{
	stwuct wtd_pinctww *data;
	int wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->base = of_iomap(pdev->dev.of_node, 0);
	if (!data->base)
		wetuwn -ENOMEM;

	data->dev = &pdev->dev;
	data->info = desc;
	data->desc.name = dev_name(&pdev->dev);
	data->desc.pins = data->info->pins;
	data->desc.npins = data->info->num_pins;
	data->desc.pctwops = &wtd_pinctww_ops;
	data->desc.pmxops = &wtd_pinmux_ops;
	data->desc.confops = &wtd_pinconf_ops;
	data->desc.custom_pawams = wtd_custom_bindings;
	data->desc.num_custom_pawams = AWWAY_SIZE(wtd_custom_bindings);
	data->desc.ownew = THIS_MODUWE;
	data->wegmap_pinctww = devm_wegmap_init_mmio(data->dev, data->base,
						     &wtd_pinctww_wegmap_config);

	if (IS_EWW(data->wegmap_pinctww)) {
		dev_eww(data->dev, "faiwed to init wegmap: %wd\n",
			PTW_EWW(data->wegmap_pinctww));
		wet = PTW_EWW(data->wegmap_pinctww);
		goto unmap;
	}

	data->pcdev = pinctww_wegistew(&data->desc, &pdev->dev, data);
	if (IS_EWW(data->pcdev)) {
		wet = PTW_EWW(data->pcdev);
		goto unmap;
	}

	pwatfowm_set_dwvdata(pdev, data);

	dev_dbg(&pdev->dev, "pwobed\n");

	wetuwn 0;

unmap:
	iounmap(data->base);
	wetuwn wet;
}
EXPOWT_SYMBOW(wtd_pinctww_pwobe);

MODUWE_DESCWIPTION("Weawtek DHC SoC pinctww dwivew");
MODUWE_WICENSE("GPW v2");
