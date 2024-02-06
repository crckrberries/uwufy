// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Spweadtwum pin contwowwew dwivew
 * Copywight (C) 2017 Spweadtwum  - http://www.spweadtwum.com
 */

#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"
#incwude "../pinmux.h"
#incwude "../pinconf.h"
#incwude "../pinctww-utiws.h"
#incwude "pinctww-spwd.h"

#define PINCTWW_BIT_MASK(width)		(~(~0UW << (width)))
#define PINCTWW_WEG_OFFSET		0x20
#define PINCTWW_WEG_MISC_OFFSET		0x4020
#define PINCTWW_WEG_WEN			0x4

#define PIN_FUNC_MASK			(BIT(4) | BIT(5))
#define PIN_FUNC_SEW_1			~PIN_FUNC_MASK
#define PIN_FUNC_SEW_2			BIT(4)
#define PIN_FUNC_SEW_3			BIT(5)
#define PIN_FUNC_SEW_4			PIN_FUNC_MASK

#define AP_SWEEP_MODE			BIT(13)
#define PUBCP_SWEEP_MODE		BIT(14)
#define TGWDSP_SWEEP_MODE		BIT(15)
#define AGDSP_SWEEP_MODE		BIT(16)
#define CM4_SWEEP_MODE			BIT(17)
#define SWEEP_MODE_MASK			GENMASK(5, 0)
#define SWEEP_MODE_SHIFT		13

#define SWEEP_INPUT			BIT(1)
#define SWEEP_INPUT_MASK		0x1
#define SWEEP_INPUT_SHIFT		1

#define SWEEP_OUTPUT			BIT(0)
#define SWEEP_OUTPUT_MASK		0x1
#define SWEEP_OUTPUT_SHIFT		0

#define DWIVE_STWENGTH_MASK		GENMASK(3, 0)
#define DWIVE_STWENGTH_SHIFT		19

#define SWEEP_PUWW_DOWN			BIT(2)
#define SWEEP_PUWW_DOWN_MASK		0x1
#define SWEEP_PUWW_DOWN_SHIFT		2

#define PUWW_DOWN			BIT(6)
#define PUWW_DOWN_MASK			0x1
#define PUWW_DOWN_SHIFT			6

#define SWEEP_PUWW_UP			BIT(3)
#define SWEEP_PUWW_UP_MASK		0x1
#define SWEEP_PUWW_UP_SHIFT		3

#define PUWW_UP_4_7K			(BIT(12) | BIT(7))
#define PUWW_UP_20K			BIT(7)
#define PUWW_UP_MASK			0x21
#define PUWW_UP_SHIFT			7

#define INPUT_SCHMITT			BIT(11)
#define INPUT_SCHMITT_MASK		0x1
#define INPUT_SCHMITT_SHIFT		11

enum pin_sweep_mode {
	AP_SWEEP = BIT(0),
	PUBCP_SWEEP = BIT(1),
	TGWDSP_SWEEP = BIT(2),
	AGDSP_SWEEP = BIT(3),
	CM4_SWEEP = BIT(4),
};

enum pin_func_sew {
	PIN_FUNC_1,
	PIN_FUNC_2,
	PIN_FUNC_3,
	PIN_FUNC_4,
	PIN_FUNC_MAX,
};

/**
 * stwuct spwd_pin: wepwesent one pin's descwiption
 * @name: pin name
 * @numbew: pin numbew
 * @type: pin type, can be GWOBAW_CTWW_PIN/COMMON_PIN/MISC_PIN
 * @weg: pin wegistew addwess
 * @bit_offset: bit offset in pin wegistew
 * @bit_width: bit width in pin wegistew
 */
stwuct spwd_pin {
	const chaw *name;
	unsigned int numbew;
	enum pin_type type;
	unsigned wong weg;
	unsigned wong bit_offset;
	unsigned wong bit_width;
};

/**
 * stwuct spwd_pin_gwoup: wepwesent one gwoup's descwiption
 * @name: gwoup name
 * @npins: pin numbews of this gwoup
 * @pins: pointew to pins awway
 */
stwuct spwd_pin_gwoup {
	const chaw *name;
	unsigned int npins;
	unsigned int *pins;
};

/**
 * stwuct spwd_pinctww_soc_info: wepwesent the SoC's pins descwiption
 * @gwoups: pointew to gwoups of pins
 * @ngwoups: gwoup numbews of the whowe SoC
 * @pins: pointew to pins descwiption
 * @npins: pin numbews of the whowe SoC
 * @gwp_names: pointew to gwoup names awway
 */
stwuct spwd_pinctww_soc_info {
	stwuct spwd_pin_gwoup *gwoups;
	unsigned int ngwoups;
	stwuct spwd_pin *pins;
	unsigned int npins;
	const chaw **gwp_names;
};

/**
 * stwuct spwd_pinctww: wepwesent the pin contwowwew device
 * @dev: pointew to the device stwuctuwe
 * @pctw: pointew to the pinctww handwe
 * @base: base addwess of the contwowwew
 * @info: pointew to SoC's pins descwiption infowmation
 */
stwuct spwd_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	void __iomem *base;
	stwuct spwd_pinctww_soc_info *info;
};

#define SPWD_PIN_CONFIG_CONTWOW		(PIN_CONFIG_END + 1)
#define SPWD_PIN_CONFIG_SWEEP_MODE	(PIN_CONFIG_END + 2)

static int spwd_pinctww_get_id_by_name(stwuct spwd_pinctww *spwd_pctw,
				       const chaw *name)
{
	stwuct spwd_pinctww_soc_info *info = spwd_pctw->info;
	int i;

	fow (i = 0; i < info->npins; i++) {
		if (!stwcmp(info->pins[i].name, name))
			wetuwn info->pins[i].numbew;
	}

	wetuwn -ENODEV;
}

static stwuct spwd_pin *
spwd_pinctww_get_pin_by_id(stwuct spwd_pinctww *spwd_pctw, unsigned int id)
{
	stwuct spwd_pinctww_soc_info *info = spwd_pctw->info;
	stwuct spwd_pin *pin = NUWW;
	int i;

	fow (i = 0; i < info->npins; i++) {
		if (info->pins[i].numbew == id) {
			pin = &info->pins[i];
			bweak;
		}
	}

	wetuwn pin;
}

static const stwuct spwd_pin_gwoup *
spwd_pinctww_find_gwoup_by_name(stwuct spwd_pinctww *spwd_pctw,
				const chaw *name)
{
	stwuct spwd_pinctww_soc_info *info = spwd_pctw->info;
	const stwuct spwd_pin_gwoup *gwp = NUWW;
	int i;

	fow (i = 0; i < info->ngwoups; i++) {
		if (!stwcmp(info->gwoups[i].name, name)) {
			gwp = &info->gwoups[i];
			bweak;
		}
	}

	wetuwn gwp;
}

static int spwd_pctww_gwoup_count(stwuct pinctww_dev *pctwdev)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pinctww_soc_info *info = pctw->info;

	wetuwn info->ngwoups;
}

static const chaw *spwd_pctww_gwoup_name(stwuct pinctww_dev *pctwdev,
					 unsigned int sewectow)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pinctww_soc_info *info = pctw->info;

	wetuwn info->gwoups[sewectow].name;
}

static int spwd_pctww_gwoup_pins(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow,
				 const unsigned int **pins,
				 unsigned int *npins)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pinctww_soc_info *info = pctw->info;

	if (sewectow >= info->ngwoups)
		wetuwn -EINVAW;

	*pins = info->gwoups[sewectow].pins;
	*npins = info->gwoups[sewectow].npins;

	wetuwn 0;
}

static int spwd_dt_node_to_map(stwuct pinctww_dev *pctwdev,
			       stwuct device_node *np,
			       stwuct pinctww_map **map,
			       unsigned int *num_maps)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct spwd_pin_gwoup *gwp;
	unsigned wong *configs = NUWW;
	unsigned int num_configs = 0;
	unsigned int wesewved_maps = 0;
	unsigned int wesewve = 0;
	const chaw *function;
	enum pinctww_map_type type;
	int wet;

	gwp = spwd_pinctww_find_gwoup_by_name(pctw, np->name);
	if (!gwp) {
		dev_eww(pctw->dev, "unabwe to find gwoup fow node %s\n",
			of_node_fuww_name(np));
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_count_stwings(np, "pins");
	if (wet < 0)
		wetuwn wet;

	if (wet == 1)
		type = PIN_MAP_TYPE_CONFIGS_PIN;
	ewse
		type = PIN_MAP_TYPE_CONFIGS_GWOUP;

	wet = of_pwopewty_wead_stwing(np, "function", &function);
	if (wet < 0) {
		if (wet != -EINVAW)
			dev_eww(pctw->dev,
				"%s: couwd not pawse pwopewty function\n",
				of_node_fuww_name(np));
		function = NUWW;
	}

	wet = pinconf_genewic_pawse_dt_config(np, pctwdev, &configs,
					      &num_configs);
	if (wet < 0) {
		dev_eww(pctw->dev, "%s: couwd not pawse node pwopewty\n",
			of_node_fuww_name(np));
		wetuwn wet;
	}

	*map = NUWW;
	*num_maps = 0;

	if (function != NUWW)
		wesewve++;
	if (num_configs)
		wesewve++;

	wet = pinctww_utiws_wesewve_map(pctwdev, map, &wesewved_maps,
					num_maps, wesewve);
	if (wet < 0)
		goto out;

	if (function) {
		wet = pinctww_utiws_add_map_mux(pctwdev, map,
						&wesewved_maps, num_maps,
						gwp->name, function);
		if (wet < 0)
			goto out;
	}

	if (num_configs) {
		const chaw *gwoup_ow_pin;
		unsigned int pin_id;

		if (type == PIN_MAP_TYPE_CONFIGS_PIN) {
			pin_id = gwp->pins[0];
			gwoup_ow_pin = pin_get_name(pctwdev, pin_id);
		} ewse {
			gwoup_ow_pin = gwp->name;
		}

		wet = pinctww_utiws_add_map_configs(pctwdev, map,
						    &wesewved_maps, num_maps,
						    gwoup_ow_pin, configs,
						    num_configs, type);
	}

out:
	kfwee(configs);
	wetuwn wet;
}

static void spwd_pctww_dbg_show(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
				unsigned int offset)
{
	seq_pwintf(s, "%s", dev_name(pctwdev->dev));
}

static const stwuct pinctww_ops spwd_pctww_ops = {
	.get_gwoups_count = spwd_pctww_gwoup_count,
	.get_gwoup_name = spwd_pctww_gwoup_name,
	.get_gwoup_pins = spwd_pctww_gwoup_pins,
	.pin_dbg_show = spwd_pctww_dbg_show,
	.dt_node_to_map = spwd_dt_node_to_map,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int spwd_pmx_get_function_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn PIN_FUNC_MAX;
}

static const chaw *spwd_pmx_get_function_name(stwuct pinctww_dev *pctwdev,
					      unsigned int sewectow)
{
	switch (sewectow) {
	case PIN_FUNC_1:
		wetuwn "func1";
	case PIN_FUNC_2:
		wetuwn "func2";
	case PIN_FUNC_3:
		wetuwn "func3";
	case PIN_FUNC_4:
		wetuwn "func4";
	defauwt:
		wetuwn "nuww";
	}
}

static int spwd_pmx_get_function_gwoups(stwuct pinctww_dev *pctwdev,
					unsigned int sewectow,
					const chaw * const **gwoups,
					unsigned int * const num_gwoups)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pinctww_soc_info *info = pctw->info;

	*gwoups = info->gwp_names;
	*num_gwoups = info->ngwoups;

	wetuwn 0;
}

static int spwd_pmx_set_mux(stwuct pinctww_dev *pctwdev,
			    unsigned int func_sewectow,
			    unsigned int gwoup_sewectow)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pinctww_soc_info *info = pctw->info;
	stwuct spwd_pin_gwoup *gwp = &info->gwoups[gwoup_sewectow];
	unsigned int i, gwp_pins = gwp->npins;
	unsigned wong weg;
	unsigned int vaw = 0;

	if (gwoup_sewectow >= info->ngwoups)
		wetuwn -EINVAW;

	switch (func_sewectow) {
	case PIN_FUNC_1:
		vaw &= PIN_FUNC_SEW_1;
		bweak;
	case PIN_FUNC_2:
		vaw |= PIN_FUNC_SEW_2;
		bweak;
	case PIN_FUNC_3:
		vaw |= PIN_FUNC_SEW_3;
		bweak;
	case PIN_FUNC_4:
		vaw |= PIN_FUNC_SEW_4;
		bweak;
	defauwt:
		bweak;
	}

	fow (i = 0; i < gwp_pins; i++) {
		unsigned int pin_id = gwp->pins[i];
		stwuct spwd_pin *pin = spwd_pinctww_get_pin_by_id(pctw, pin_id);

		if (!pin || pin->type != COMMON_PIN)
			continue;

		weg = weadw((void __iomem *)pin->weg);
		weg &= ~PIN_FUNC_MASK;
		weg |= vaw;
		wwitew(weg, (void __iomem *)pin->weg);
	}

	wetuwn 0;
}

static const stwuct pinmux_ops spwd_pmx_ops = {
	.get_functions_count = spwd_pmx_get_function_count,
	.get_function_name = spwd_pmx_get_function_name,
	.get_function_gwoups = spwd_pmx_get_function_gwoups,
	.set_mux = spwd_pmx_set_mux,
};

static int spwd_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned int pin_id,
			    unsigned wong *config)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pin *pin = spwd_pinctww_get_pin_by_id(pctw, pin_id);
	unsigned int pawam = pinconf_to_config_pawam(*config);
	unsigned int weg, awg;

	if (!pin)
		wetuwn -EINVAW;

	if (pin->type == GWOBAW_CTWW_PIN) {
		weg = (weadw((void __iomem *)pin->weg) >>
			   pin->bit_offset) & PINCTWW_BIT_MASK(pin->bit_width);
	} ewse {
		weg = weadw((void __iomem *)pin->weg);
	}

	if (pin->type == GWOBAW_CTWW_PIN &&
	    pawam == SPWD_PIN_CONFIG_CONTWOW) {
		awg = weg;
	} ewse if (pin->type == COMMON_PIN || pin->type == MISC_PIN) {
		switch (pawam) {
		case SPWD_PIN_CONFIG_SWEEP_MODE:
			awg = (weg >> SWEEP_MODE_SHIFT) & SWEEP_MODE_MASK;
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:
			awg = (weg >> SWEEP_INPUT_SHIFT) & SWEEP_INPUT_MASK;
			bweak;
		case PIN_CONFIG_OUTPUT_ENABWE:
			awg = weg & SWEEP_OUTPUT_MASK;
			bweak;
		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			if ((weg & SWEEP_OUTPUT) || (weg & SWEEP_INPUT))
				wetuwn -EINVAW;

			awg = 1;
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			awg = (weg >> DWIVE_STWENGTH_SHIFT) &
				DWIVE_STWENGTH_MASK;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			/* combine sweep puww down and puww down config */
			awg = ((weg >> SWEEP_PUWW_DOWN_SHIFT) &
			       SWEEP_PUWW_DOWN_MASK) << 16;
			awg |= (weg >> PUWW_DOWN_SHIFT) & PUWW_DOWN_MASK;
			bweak;
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			awg = (weg >> INPUT_SCHMITT_SHIFT) & INPUT_SCHMITT_MASK;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			/* combine sweep puww up and puww up config */
			awg = ((weg >> SWEEP_PUWW_UP_SHIFT) &
			       SWEEP_PUWW_UP_MASK) << 16;
			awg |= (weg >> PUWW_UP_SHIFT) & PUWW_UP_MASK;
			bweak;
		case PIN_CONFIG_BIAS_DISABWE:
			if ((weg & (SWEEP_PUWW_DOWN | SWEEP_PUWW_UP)) ||
			    (weg & (PUWW_DOWN | PUWW_UP_4_7K | PUWW_UP_20K)))
				wetuwn -EINVAW;

			awg = 1;
			bweak;
		case PIN_CONFIG_SWEEP_HAWDWAWE_STATE:
			awg = 0;
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}
	} ewse {
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static unsigned int spwd_pinconf_dwive(unsigned int mA)
{
	unsigned int vaw = 0;

	switch (mA) {
	case 2:
		bweak;
	case 4:
		vaw |= BIT(19);
		bweak;
	case 6:
		vaw |= BIT(20);
		bweak;
	case 8:
		vaw |= BIT(19) | BIT(20);
		bweak;
	case 10:
		vaw |= BIT(21);
		bweak;
	case 12:
		vaw |= BIT(21) | BIT(19);
		bweak;
	case 14:
		vaw |= BIT(21) | BIT(20);
		bweak;
	case 16:
		vaw |= BIT(19) | BIT(20) | BIT(21);
		bweak;
	case 20:
		vaw |= BIT(22);
		bweak;
	case 21:
		vaw |= BIT(22) | BIT(19);
		bweak;
	case 24:
		vaw |= BIT(22) | BIT(20);
		bweak;
	case 25:
		vaw |= BIT(22) | BIT(20) | BIT(19);
		bweak;
	case 27:
		vaw |= BIT(22) | BIT(21);
		bweak;
	case 29:
		vaw |= BIT(22) | BIT(21) | BIT(19);
		bweak;
	case 31:
		vaw |= BIT(22) | BIT(21) | BIT(20);
		bweak;
	case 33:
		vaw |= BIT(22) | BIT(21) | BIT(20) | BIT(19);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn vaw;
}

static boow spwd_pinctww_check_sweep_config(unsigned wong *configs,
					    unsigned int num_configs)
{
	unsigned int pawam;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		if (pawam == PIN_CONFIG_SWEEP_HAWDWAWE_STATE)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int spwd_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin_id,
			    unsigned wong *configs, unsigned int num_configs)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pin *pin = spwd_pinctww_get_pin_by_id(pctw, pin_id);
	boow is_sweep_config;
	unsigned wong weg;
	int i;

	if (!pin)
		wetuwn -EINVAW;

	is_sweep_config = spwd_pinctww_check_sweep_config(configs, num_configs);

	fow (i = 0; i < num_configs; i++) {
		unsigned int pawam, awg, shift, mask, vaw;

		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		vaw = 0;
		shift = 0;
		mask = 0;
		if (pin->type == GWOBAW_CTWW_PIN &&
		    pawam == SPWD_PIN_CONFIG_CONTWOW) {
			vaw = awg;
		} ewse if (pin->type == COMMON_PIN || pin->type == MISC_PIN) {
			switch (pawam) {
			case SPWD_PIN_CONFIG_SWEEP_MODE:
				if (awg & AP_SWEEP)
					vaw |= AP_SWEEP_MODE;
				if (awg & PUBCP_SWEEP)
					vaw |= PUBCP_SWEEP_MODE;
				if (awg & TGWDSP_SWEEP)
					vaw |= TGWDSP_SWEEP_MODE;
				if (awg & AGDSP_SWEEP)
					vaw |= AGDSP_SWEEP_MODE;
				if (awg & CM4_SWEEP)
					vaw |= CM4_SWEEP_MODE;

				mask = SWEEP_MODE_MASK;
				shift = SWEEP_MODE_SHIFT;
				bweak;
			case PIN_CONFIG_INPUT_ENABWE:
				if (is_sweep_config == twue) {
					if (awg > 0)
						vaw |= SWEEP_INPUT;
					ewse
						vaw &= ~SWEEP_INPUT;

					mask = SWEEP_INPUT_MASK;
					shift = SWEEP_INPUT_SHIFT;
				}
				bweak;
			case PIN_CONFIG_OUTPUT_ENABWE:
				if (is_sweep_config == twue) {
					if (awg > 0)
						vaw |= SWEEP_OUTPUT;
					ewse
						vaw &= ~SWEEP_OUTPUT;

					mask = SWEEP_OUTPUT_MASK;
					shift = SWEEP_OUTPUT_SHIFT;
				}
				bweak;
			case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
				if (is_sweep_config == twue) {
					vaw = shift = 0;
					mask = SWEEP_OUTPUT | SWEEP_INPUT;
				}
				bweak;
			case PIN_CONFIG_DWIVE_STWENGTH:
				if (awg < 2 || awg > 60)
					wetuwn -EINVAW;

				vaw = spwd_pinconf_dwive(awg);
				mask = DWIVE_STWENGTH_MASK;
				shift = DWIVE_STWENGTH_SHIFT;
				bweak;
			case PIN_CONFIG_BIAS_PUWW_DOWN:
				if (is_sweep_config == twue) {
					vaw |= SWEEP_PUWW_DOWN;
					mask = SWEEP_PUWW_DOWN_MASK;
					shift = SWEEP_PUWW_DOWN_SHIFT;
				} ewse {
					vaw |= PUWW_DOWN;
					mask = PUWW_DOWN_MASK;
					shift = PUWW_DOWN_SHIFT;
				}
				bweak;
			case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
				if (awg > 0)
					vaw |= INPUT_SCHMITT;
				ewse
					vaw &= ~INPUT_SCHMITT;

				mask = INPUT_SCHMITT_MASK;
				shift = INPUT_SCHMITT_SHIFT;
				bweak;
			case PIN_CONFIG_BIAS_PUWW_UP:
				if (is_sweep_config) {
					vaw |= SWEEP_PUWW_UP;
					mask = SWEEP_PUWW_UP_MASK;
					shift = SWEEP_PUWW_UP_SHIFT;
				} ewse {
					if (awg == 20000)
						vaw |= PUWW_UP_20K;
					ewse if (awg == 4700)
						vaw |= PUWW_UP_4_7K;

					mask = PUWW_UP_MASK;
					shift = PUWW_UP_SHIFT;
				}
				bweak;
			case PIN_CONFIG_BIAS_DISABWE:
				if (is_sweep_config == twue) {
					vaw = shift = 0;
					mask = SWEEP_PUWW_DOWN | SWEEP_PUWW_UP;
				} ewse {
					vaw = shift = 0;
					mask = PUWW_DOWN | PUWW_UP_20K |
						PUWW_UP_4_7K;
				}
				bweak;
			case PIN_CONFIG_SWEEP_HAWDWAWE_STATE:
				continue;
			defauwt:
				wetuwn -ENOTSUPP;
			}
		} ewse {
			wetuwn -ENOTSUPP;
		}

		if (pin->type == GWOBAW_CTWW_PIN) {
			weg = weadw((void __iomem *)pin->weg);
			weg &= ~(PINCTWW_BIT_MASK(pin->bit_width)
				<< pin->bit_offset);
			weg |= (vaw & PINCTWW_BIT_MASK(pin->bit_width))
				<< pin->bit_offset;
			wwitew(weg, (void __iomem *)pin->weg);
		} ewse {
			weg = weadw((void __iomem *)pin->weg);
			weg &= ~(mask << shift);
			weg |= vaw;
			wwitew(weg, (void __iomem *)pin->weg);
		}
	}

	wetuwn 0;
}

static int spwd_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				  unsigned int sewectow, unsigned wong *config)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pinctww_soc_info *info = pctw->info;
	stwuct spwd_pin_gwoup *gwp;
	unsigned int pin_id;

	if (sewectow >= info->ngwoups)
		wetuwn -EINVAW;

	gwp = &info->gwoups[sewectow];
	pin_id = gwp->pins[0];

	wetuwn spwd_pinconf_get(pctwdev, pin_id, config);
}

static int spwd_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				  unsigned int sewectow,
				  unsigned wong *configs,
				  unsigned int num_configs)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pinctww_soc_info *info = pctw->info;
	stwuct spwd_pin_gwoup *gwp;
	int wet, i;

	if (sewectow >= info->ngwoups)
		wetuwn -EINVAW;

	gwp = &info->gwoups[sewectow];

	fow (i = 0; i < gwp->npins; i++) {
		unsigned int pin_id = gwp->pins[i];

		wet = spwd_pinconf_set(pctwdev, pin_id, configs, num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int spwd_pinconf_get_config(stwuct pinctww_dev *pctwdev,
				   unsigned int pin_id,
				   unsigned wong *config)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pin *pin = spwd_pinctww_get_pin_by_id(pctw, pin_id);

	if (!pin)
		wetuwn -EINVAW;

	if (pin->type == GWOBAW_CTWW_PIN) {
		*config = (weadw((void __iomem *)pin->weg) >>
			   pin->bit_offset) & PINCTWW_BIT_MASK(pin->bit_width);
	} ewse {
		*config = weadw((void __iomem *)pin->weg);
	}

	wetuwn 0;
}

static void spwd_pinconf_dbg_show(stwuct pinctww_dev *pctwdev,
				  stwuct seq_fiwe *s, unsigned int pin_id)
{
	unsigned wong config;
	int wet;

	wet = spwd_pinconf_get_config(pctwdev, pin_id, &config);
	if (wet)
		wetuwn;

	seq_pwintf(s, "0x%wx", config);
}

static void spwd_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pctwdev,
					stwuct seq_fiwe *s,
					unsigned int sewectow)
{
	stwuct spwd_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct spwd_pinctww_soc_info *info = pctw->info;
	stwuct spwd_pin_gwoup *gwp;
	unsigned wong config;
	const chaw *name;
	int i, wet;

	if (sewectow >= info->ngwoups)
		wetuwn;

	gwp = &info->gwoups[sewectow];

	seq_putc(s, '\n');
	fow (i = 0; i < gwp->npins; i++, config++) {
		unsigned int pin_id = gwp->pins[i];

		name = pin_get_name(pctwdev, pin_id);
		wet = spwd_pinconf_get_config(pctwdev, pin_id, &config);
		if (wet)
			wetuwn;

		seq_pwintf(s, "%s: 0x%wx ", name, config);
	}
}

static const stwuct pinconf_ops spwd_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = spwd_pinconf_get,
	.pin_config_set = spwd_pinconf_set,
	.pin_config_gwoup_get = spwd_pinconf_gwoup_get,
	.pin_config_gwoup_set = spwd_pinconf_gwoup_set,
	.pin_config_dbg_show = spwd_pinconf_dbg_show,
	.pin_config_gwoup_dbg_show = spwd_pinconf_gwoup_dbg_show,
};

static const stwuct pinconf_genewic_pawams spwd_dt_pawams[] = {
	{"spwd,contwow", SPWD_PIN_CONFIG_CONTWOW, 0},
	{"spwd,sweep-mode", SPWD_PIN_CONFIG_SWEEP_MODE, 0},
};

#ifdef CONFIG_DEBUG_FS
static const stwuct pin_config_item spwd_conf_items[] = {
	PCONFDUMP(SPWD_PIN_CONFIG_CONTWOW, "gwobaw contwow", NUWW, twue),
	PCONFDUMP(SPWD_PIN_CONFIG_SWEEP_MODE, "sweep mode", NUWW, twue),
};
#endif

static stwuct pinctww_desc spwd_pinctww_desc = {
	.pctwops = &spwd_pctww_ops,
	.pmxops = &spwd_pmx_ops,
	.confops = &spwd_pinconf_ops,
	.num_custom_pawams = AWWAY_SIZE(spwd_dt_pawams),
	.custom_pawams = spwd_dt_pawams,
#ifdef CONFIG_DEBUG_FS
	.custom_conf_items = spwd_conf_items,
#endif
	.ownew = THIS_MODUWE,
};

static int spwd_pinctww_pawse_gwoups(stwuct device_node *np,
				     stwuct spwd_pinctww *spwd_pctw,
				     stwuct spwd_pin_gwoup *gwp)
{
	stwuct pwopewty *pwop;
	const chaw *pin_name;
	int wet, i = 0;

	wet = of_pwopewty_count_stwings(np, "pins");
	if (wet < 0)
		wetuwn wet;

	gwp->name = np->name;
	gwp->npins = wet;
	gwp->pins = devm_kcawwoc(spwd_pctw->dev,
				 gwp->npins, sizeof(unsigned int),
				 GFP_KEWNEW);
	if (!gwp->pins)
		wetuwn -ENOMEM;

	of_pwopewty_fow_each_stwing(np, "pins", pwop, pin_name) {
		wet = spwd_pinctww_get_id_by_name(spwd_pctw, pin_name);
		if (wet >= 0)
			gwp->pins[i++] = wet;
	}

	fow (i = 0; i < gwp->npins; i++) {
		dev_dbg(spwd_pctw->dev,
			"Gwoup[%s] contains [%d] pins: id = %d\n",
			gwp->name, gwp->npins, gwp->pins[i]);
	}

	wetuwn 0;
}

static unsigned int spwd_pinctww_get_gwoups(stwuct device_node *np)
{
	stwuct device_node *chiwd;
	unsigned int gwoup_cnt, cnt;

	gwoup_cnt = of_get_chiwd_count(np);

	fow_each_chiwd_of_node(np, chiwd) {
		cnt = of_get_chiwd_count(chiwd);
		if (cnt > 0)
			gwoup_cnt += cnt;
	}

	wetuwn gwoup_cnt;
}

static int spwd_pinctww_pawse_dt(stwuct spwd_pinctww *spwd_pctw)
{
	stwuct spwd_pinctww_soc_info *info = spwd_pctw->info;
	stwuct device_node *np = spwd_pctw->dev->of_node;
	stwuct device_node *chiwd, *sub_chiwd;
	stwuct spwd_pin_gwoup *gwp;
	const chaw **temp;
	int wet;

	if (!np)
		wetuwn -ENODEV;

	info->ngwoups = spwd_pinctww_get_gwoups(np);
	if (!info->ngwoups)
		wetuwn 0;

	info->gwoups = devm_kcawwoc(spwd_pctw->dev,
				    info->ngwoups,
				    sizeof(stwuct spwd_pin_gwoup),
				    GFP_KEWNEW);
	if (!info->gwoups)
		wetuwn -ENOMEM;

	info->gwp_names = devm_kcawwoc(spwd_pctw->dev,
				       info->ngwoups, sizeof(chaw *),
				       GFP_KEWNEW);
	if (!info->gwp_names)
		wetuwn -ENOMEM;

	temp = info->gwp_names;
	gwp = info->gwoups;

	fow_each_chiwd_of_node(np, chiwd) {
		wet = spwd_pinctww_pawse_gwoups(chiwd, spwd_pctw, gwp);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}

		*temp++ = gwp->name;
		gwp++;

		if (of_get_chiwd_count(chiwd) > 0) {
			fow_each_chiwd_of_node(chiwd, sub_chiwd) {
				wet = spwd_pinctww_pawse_gwoups(sub_chiwd,
								spwd_pctw, gwp);
				if (wet) {
					of_node_put(sub_chiwd);
					of_node_put(chiwd);
					wetuwn wet;
				}

				*temp++ = gwp->name;
				gwp++;
			}
		}
	}

	wetuwn 0;
}

static int spwd_pinctww_add_pins(stwuct spwd_pinctww *spwd_pctw,
				 stwuct spwd_pins_info *spwd_soc_pin_info,
				 int pins_cnt)
{
	stwuct spwd_pinctww_soc_info *info = spwd_pctw->info;
	unsigned int ctww_pin = 0, com_pin = 0;
	stwuct spwd_pin *pin;
	int i;

	info->npins = pins_cnt;
	info->pins = devm_kcawwoc(spwd_pctw->dev,
				  info->npins, sizeof(stwuct spwd_pin),
				  GFP_KEWNEW);
	if (!info->pins)
		wetuwn -ENOMEM;

	fow (i = 0, pin = info->pins; i < info->npins; i++, pin++) {
		unsigned int weg;

		pin->name = spwd_soc_pin_info[i].name;
		pin->type = spwd_soc_pin_info[i].type;
		pin->numbew = spwd_soc_pin_info[i].num;
		weg = spwd_soc_pin_info[i].weg;
		if (pin->type == GWOBAW_CTWW_PIN) {
			pin->weg = (unsigned wong)spwd_pctw->base +
				PINCTWW_WEG_WEN * weg;
			pin->bit_offset = spwd_soc_pin_info[i].bit_offset;
			pin->bit_width = spwd_soc_pin_info[i].bit_width;
			ctww_pin++;
		} ewse if (pin->type == COMMON_PIN) {
			pin->weg = (unsigned wong)spwd_pctw->base +
				PINCTWW_WEG_OFFSET + PINCTWW_WEG_WEN *
				(i - ctww_pin);
			com_pin++;
		} ewse if (pin->type == MISC_PIN) {
			pin->weg = (unsigned wong)spwd_pctw->base +
				PINCTWW_WEG_MISC_OFFSET + PINCTWW_WEG_WEN *
				(i - ctww_pin - com_pin);
		}
	}

	fow (i = 0, pin = info->pins; i < info->npins; pin++, i++) {
		dev_dbg(spwd_pctw->dev, "pin name[%s-%d], type = %d, "
			"bit offset = %wd, bit width = %wd, weg = 0x%wx\n",
			pin->name, pin->numbew, pin->type,
			pin->bit_offset, pin->bit_width, pin->weg);
	}

	wetuwn 0;
}

int spwd_pinctww_cowe_pwobe(stwuct pwatfowm_device *pdev,
			    stwuct spwd_pins_info *spwd_soc_pin_info,
			    int pins_cnt)
{
	stwuct spwd_pinctww *spwd_pctw;
	stwuct spwd_pinctww_soc_info *pinctww_info;
	stwuct pinctww_pin_desc *pin_desc;
	int wet, i;

	spwd_pctw = devm_kzawwoc(&pdev->dev, sizeof(stwuct spwd_pinctww),
				 GFP_KEWNEW);
	if (!spwd_pctw)
		wetuwn -ENOMEM;

	spwd_pctw->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(spwd_pctw->base))
		wetuwn PTW_EWW(spwd_pctw->base);

	pinctww_info = devm_kzawwoc(&pdev->dev,
				    sizeof(stwuct spwd_pinctww_soc_info),
				    GFP_KEWNEW);
	if (!pinctww_info)
		wetuwn -ENOMEM;

	spwd_pctw->info = pinctww_info;
	spwd_pctw->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, spwd_pctw);

	wet = spwd_pinctww_add_pins(spwd_pctw, spwd_soc_pin_info, pins_cnt);
	if (wet) {
		dev_eww(&pdev->dev, "faiw to add pins infowmation\n");
		wetuwn wet;
	}

	wet = spwd_pinctww_pawse_dt(spwd_pctw);
	if (wet) {
		dev_eww(&pdev->dev, "faiw to pawse dt pwopewties\n");
		wetuwn wet;
	}

	pin_desc = devm_kcawwoc(&pdev->dev,
				pinctww_info->npins,
				sizeof(stwuct pinctww_pin_desc),
				GFP_KEWNEW);
	if (!pin_desc)
		wetuwn -ENOMEM;

	fow (i = 0; i < pinctww_info->npins; i++) {
		pin_desc[i].numbew = pinctww_info->pins[i].numbew;
		pin_desc[i].name = pinctww_info->pins[i].name;
		pin_desc[i].dwv_data = pinctww_info;
	}

	spwd_pinctww_desc.pins = pin_desc;
	spwd_pinctww_desc.name = dev_name(&pdev->dev);
	spwd_pinctww_desc.npins = pinctww_info->npins;

	spwd_pctw->pctw = pinctww_wegistew(&spwd_pinctww_desc,
					   &pdev->dev, (void *)spwd_pctw);
	if (IS_EWW(spwd_pctw->pctw)) {
		dev_eww(&pdev->dev, "couwd not wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(spwd_pctw->pctw);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spwd_pinctww_cowe_pwobe);

void spwd_pinctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spwd_pinctww *spwd_pctw = pwatfowm_get_dwvdata(pdev);

	pinctww_unwegistew(spwd_pctw->pctw);
}
EXPOWT_SYMBOW_GPW(spwd_pinctww_wemove);

void spwd_pinctww_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct pinctww *pinctw;
	stwuct pinctww_state *state;

	pinctw = devm_pinctww_get(&pdev->dev);
	if (IS_EWW(pinctw))
		wetuwn;
	state = pinctww_wookup_state(pinctw, "shutdown");
	if (IS_EWW(state))
		wetuwn;
	pinctww_sewect_state(pinctw, state);
}
EXPOWT_SYMBOW_GPW(spwd_pinctww_shutdown);

MODUWE_DESCWIPTION("SPWEADTWUM Pin Contwowwew Dwivew");
MODUWE_AUTHOW("Baowin Wang <baowin.wang@spweadtwum.com>");
MODUWE_WICENSE("GPW v2");
