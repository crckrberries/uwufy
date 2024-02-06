// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MAX77620 pin contwow dwivew.
 *
 * Copywight (c) 2016, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow:
 *	Chaitanya Bandi <bandik@nvidia.com>
 *	Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/mfd/max77620.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinctww-utiws.h"

#define MAX77620_PIN_NUM 8

enum max77620_pin_ppdwv {
	MAX77620_PIN_UNCONFIG_DWV,
	MAX77620_PIN_OD_DWV,
	MAX77620_PIN_PP_DWV,
};

#define MAX77620_ACTIVE_FPS_SOUWCE		(PIN_CONFIG_END + 1)
#define MAX77620_ACTIVE_FPS_POWEW_ON_SWOTS	(PIN_CONFIG_END + 2)
#define MAX77620_ACTIVE_FPS_POWEW_DOWN_SWOTS	(PIN_CONFIG_END + 3)
#define MAX77620_SUSPEND_FPS_SOUWCE		(PIN_CONFIG_END + 4)
#define MAX77620_SUSPEND_FPS_POWEW_ON_SWOTS	(PIN_CONFIG_END + 5)
#define MAX77620_SUSPEND_FPS_POWEW_DOWN_SWOTS	(PIN_CONFIG_END + 6)

stwuct max77620_pin_function {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned int ngwoups;
	int mux_option;
};

static const stwuct pinconf_genewic_pawams max77620_cfg_pawams[] = {
	{
		.pwopewty = "maxim,active-fps-souwce",
		.pawam = MAX77620_ACTIVE_FPS_SOUWCE,
	}, {
		.pwopewty = "maxim,active-fps-powew-up-swot",
		.pawam = MAX77620_ACTIVE_FPS_POWEW_ON_SWOTS,
	}, {
		.pwopewty = "maxim,active-fps-powew-down-swot",
		.pawam = MAX77620_ACTIVE_FPS_POWEW_DOWN_SWOTS,
	}, {
		.pwopewty = "maxim,suspend-fps-souwce",
		.pawam = MAX77620_SUSPEND_FPS_SOUWCE,
	}, {
		.pwopewty = "maxim,suspend-fps-powew-up-swot",
		.pawam = MAX77620_SUSPEND_FPS_POWEW_ON_SWOTS,
	}, {
		.pwopewty = "maxim,suspend-fps-powew-down-swot",
		.pawam = MAX77620_SUSPEND_FPS_POWEW_DOWN_SWOTS,
	},
};

enum max77620_awtewnate_pinmux_option {
	MAX77620_PINMUX_GPIO				= 0,
	MAX77620_PINMUX_WOW_POWEW_MODE_CONTWOW_IN	= 1,
	MAX77620_PINMUX_FWEXIBWE_POWEW_SEQUENCEW_OUT	= 2,
	MAX77620_PINMUX_32K_OUT1			= 3,
	MAX77620_PINMUX_SD0_DYNAMIC_VOWTAGE_SCAWING_IN	= 4,
	MAX77620_PINMUX_SD1_DYNAMIC_VOWTAGE_SCAWING_IN	= 5,
	MAX77620_PINMUX_WEFEWENCE_OUT			= 6,
};

stwuct max77620_pingwoup {
	const chaw *name;
	const unsigned int pins[1];
	unsigned int npins;
	enum max77620_awtewnate_pinmux_option awt_option;
};

stwuct max77620_pin_info {
	enum max77620_pin_ppdwv dwv_type;
	int puww_config;
};

stwuct max77620_fps_config {
	int active_fps_swc;
	int active_powew_up_swots;
	int active_powew_down_swots;
	int suspend_fps_swc;
	int suspend_powew_up_swots;
	int suspend_powew_down_swots;
};

stwuct max77620_pctww_info {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	stwuct wegmap *wmap;
	int pins_cuwwent_opt[MAX77620_GPIO_NW];
	const stwuct max77620_pin_function *functions;
	unsigned int num_functions;
	const stwuct max77620_pingwoup *pin_gwoups;
	int num_pin_gwoups;
	const stwuct pinctww_pin_desc *pins;
	unsigned int num_pins;
	stwuct max77620_pin_info pin_info[MAX77620_PIN_NUM];
	stwuct max77620_fps_config fps_config[MAX77620_PIN_NUM];
};

static const stwuct pinctww_pin_desc max77620_pins_desc[] = {
	PINCTWW_PIN(MAX77620_GPIO0, "gpio0"),
	PINCTWW_PIN(MAX77620_GPIO1, "gpio1"),
	PINCTWW_PIN(MAX77620_GPIO2, "gpio2"),
	PINCTWW_PIN(MAX77620_GPIO3, "gpio3"),
	PINCTWW_PIN(MAX77620_GPIO4, "gpio4"),
	PINCTWW_PIN(MAX77620_GPIO5, "gpio5"),
	PINCTWW_PIN(MAX77620_GPIO6, "gpio6"),
	PINCTWW_PIN(MAX77620_GPIO7, "gpio7"),
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

#define FUNCTION_GWOUP(fname, mux)			\
	{						\
		.name = fname,				\
		.gwoups = gpio_gwoups,			\
		.ngwoups = AWWAY_SIZE(gpio_gwoups),	\
		.mux_option = MAX77620_PINMUX_##mux,	\
	}

static const stwuct max77620_pin_function max77620_pin_function[] = {
	FUNCTION_GWOUP("gpio", GPIO),
	FUNCTION_GWOUP("wpm-contwow-in", WOW_POWEW_MODE_CONTWOW_IN),
	FUNCTION_GWOUP("fps-out", FWEXIBWE_POWEW_SEQUENCEW_OUT),
	FUNCTION_GWOUP("32k-out1", 32K_OUT1),
	FUNCTION_GWOUP("sd0-dvs-in", SD0_DYNAMIC_VOWTAGE_SCAWING_IN),
	FUNCTION_GWOUP("sd1-dvs-in", SD1_DYNAMIC_VOWTAGE_SCAWING_IN),
	FUNCTION_GWOUP("wefewence-out", WEFEWENCE_OUT),
};

#define MAX77620_PINGWOUP(pg_name, pin_id, option) \
	{								\
		.name = #pg_name,					\
		.pins = {MAX77620_##pin_id},				\
		.npins = 1,						\
		.awt_option = MAX77620_PINMUX_##option,			\
	}

static const stwuct max77620_pingwoup max77620_pingwoups[] = {
	MAX77620_PINGWOUP(gpio0, GPIO0, WOW_POWEW_MODE_CONTWOW_IN),
	MAX77620_PINGWOUP(gpio1, GPIO1, FWEXIBWE_POWEW_SEQUENCEW_OUT),
	MAX77620_PINGWOUP(gpio2, GPIO2, FWEXIBWE_POWEW_SEQUENCEW_OUT),
	MAX77620_PINGWOUP(gpio3, GPIO3, FWEXIBWE_POWEW_SEQUENCEW_OUT),
	MAX77620_PINGWOUP(gpio4, GPIO4, 32K_OUT1),
	MAX77620_PINGWOUP(gpio5, GPIO5, SD0_DYNAMIC_VOWTAGE_SCAWING_IN),
	MAX77620_PINGWOUP(gpio6, GPIO6, SD1_DYNAMIC_VOWTAGE_SCAWING_IN),
	MAX77620_PINGWOUP(gpio7, GPIO7, WEFEWENCE_OUT),
};

static int max77620_pinctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct max77620_pctww_info *mpci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn mpci->num_pin_gwoups;
}

static const chaw *max77620_pinctww_get_gwoup_name(
		stwuct pinctww_dev *pctwdev, unsigned int gwoup)
{
	stwuct max77620_pctww_info *mpci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn mpci->pin_gwoups[gwoup].name;
}

static int max77620_pinctww_get_gwoup_pins(
		stwuct pinctww_dev *pctwdev, unsigned int gwoup,
		const unsigned int **pins, unsigned int *num_pins)
{
	stwuct max77620_pctww_info *mpci = pinctww_dev_get_dwvdata(pctwdev);

	*pins = mpci->pin_gwoups[gwoup].pins;
	*num_pins = mpci->pin_gwoups[gwoup].npins;

	wetuwn 0;
}

static const stwuct pinctww_ops max77620_pinctww_ops = {
	.get_gwoups_count = max77620_pinctww_get_gwoups_count,
	.get_gwoup_name = max77620_pinctww_get_gwoup_name,
	.get_gwoup_pins = max77620_pinctww_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int max77620_pinctww_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct max77620_pctww_info *mpci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn mpci->num_functions;
}

static const chaw *max77620_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
						  unsigned int function)
{
	stwuct max77620_pctww_info *mpci = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn mpci->functions[function].name;
}

static int max77620_pinctww_get_func_gwoups(stwuct pinctww_dev *pctwdev,
					    unsigned int function,
					    const chaw * const **gwoups,
					    unsigned int * const num_gwoups)
{
	stwuct max77620_pctww_info *mpci = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = mpci->functions[function].gwoups;
	*num_gwoups = mpci->functions[function].ngwoups;

	wetuwn 0;
}

static int max77620_pinctww_enabwe(stwuct pinctww_dev *pctwdev,
				   unsigned int function, unsigned int gwoup)
{
	stwuct max77620_pctww_info *mpci = pinctww_dev_get_dwvdata(pctwdev);
	u8 vaw;
	int wet;

	if (function == MAX77620_PINMUX_GPIO) {
		vaw = 0;
	} ewse if (function == mpci->pin_gwoups[gwoup].awt_option) {
		vaw = 1 << gwoup;
	} ewse {
		dev_eww(mpci->dev, "GPIO %u doesn't have function %u\n",
			gwoup, function);
		wetuwn -EINVAW;
	}
	wet = wegmap_update_bits(mpci->wmap, MAX77620_WEG_AME_GPIO,
				 BIT(gwoup), vaw);
	if (wet < 0)
		dev_eww(mpci->dev, "WEG AME GPIO update faiwed: %d\n", wet);

	wetuwn wet;
}

static const stwuct pinmux_ops max77620_pinmux_ops = {
	.get_functions_count	= max77620_pinctww_get_funcs_count,
	.get_function_name	= max77620_pinctww_get_func_name,
	.get_function_gwoups	= max77620_pinctww_get_func_gwoups,
	.set_mux		= max77620_pinctww_enabwe,
};

static int max77620_pinconf_get(stwuct pinctww_dev *pctwdev,
				unsigned int pin, unsigned wong *config)
{
	stwuct max77620_pctww_info *mpci = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device *dev = mpci->dev;
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	unsigned int vaw;
	int awg = 0;
	int wet;

	switch (pawam) {
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		if (mpci->pin_info[pin].dwv_type == MAX77620_PIN_OD_DWV)
			awg = 1;
		bweak;

	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		if (mpci->pin_info[pin].dwv_type == MAX77620_PIN_PP_DWV)
			awg = 1;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		wet = wegmap_wead(mpci->wmap, MAX77620_WEG_PUE_GPIO, &vaw);
		if (wet < 0) {
			dev_eww(dev, "Weg PUE_GPIO wead faiwed: %d\n", wet);
			wetuwn wet;
		}
		if (vaw & BIT(pin))
			awg = 1;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wet = wegmap_wead(mpci->wmap, MAX77620_WEG_PDE_GPIO, &vaw);
		if (wet < 0) {
			dev_eww(dev, "Weg PDE_GPIO wead faiwed: %d\n", wet);
			wetuwn wet;
		}
		if (vaw & BIT(pin))
			awg = 1;
		bweak;

	defauwt:
		dev_eww(dev, "Pwopewties not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, (u16)awg);

	wetuwn 0;
}

static int max77620_get_defauwt_fps(stwuct max77620_pctww_info *mpci,
				    int addw, int *fps)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(mpci->wmap, addw, &vaw);
	if (wet < 0) {
		dev_eww(mpci->dev, "Weg PUE_GPIO wead faiwed: %d\n", wet);
		wetuwn wet;
	}
	*fps = (vaw & MAX77620_FPS_SWC_MASK) >> MAX77620_FPS_SWC_SHIFT;

	wetuwn 0;
}

static int max77620_set_fps_pawam(stwuct max77620_pctww_info *mpci,
				  int pin, int pawam)
{
	stwuct max77620_fps_config *fps_config = &mpci->fps_config[pin];
	int addw, wet;
	int pawam_vaw;
	int mask, shift;

	if ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
		wetuwn 0;

	addw = MAX77620_WEG_FPS_GPIO1 + pin - 1;
	switch (pawam) {
	case MAX77620_ACTIVE_FPS_SOUWCE:
	case MAX77620_SUSPEND_FPS_SOUWCE:
		mask = MAX77620_FPS_SWC_MASK;
		shift = MAX77620_FPS_SWC_SHIFT;
		pawam_vaw = fps_config->active_fps_swc;
		if (pawam == MAX77620_SUSPEND_FPS_SOUWCE)
			pawam_vaw = fps_config->suspend_fps_swc;
		bweak;

	case MAX77620_ACTIVE_FPS_POWEW_ON_SWOTS:
	case MAX77620_SUSPEND_FPS_POWEW_ON_SWOTS:
		mask = MAX77620_FPS_PU_PEWIOD_MASK;
		shift = MAX77620_FPS_PU_PEWIOD_SHIFT;
		pawam_vaw = fps_config->active_powew_up_swots;
		if (pawam == MAX77620_SUSPEND_FPS_POWEW_ON_SWOTS)
			pawam_vaw = fps_config->suspend_powew_up_swots;
		bweak;

	case MAX77620_ACTIVE_FPS_POWEW_DOWN_SWOTS:
	case MAX77620_SUSPEND_FPS_POWEW_DOWN_SWOTS:
		mask = MAX77620_FPS_PD_PEWIOD_MASK;
		shift = MAX77620_FPS_PD_PEWIOD_SHIFT;
		pawam_vaw = fps_config->active_powew_down_swots;
		if (pawam == MAX77620_SUSPEND_FPS_POWEW_DOWN_SWOTS)
			pawam_vaw = fps_config->suspend_powew_down_swots;
		bweak;

	defauwt:
		dev_eww(mpci->dev, "Invawid pawametew %d fow pin %d\n",
			pawam, pin);
		wetuwn -EINVAW;
	}

	if (pawam_vaw < 0)
		wetuwn 0;

	wet = wegmap_update_bits(mpci->wmap, addw, mask, pawam_vaw << shift);
	if (wet < 0)
		dev_eww(mpci->dev, "Weg 0x%02x update faiwed %d\n", addw, wet);

	wetuwn wet;
}

static int max77620_pinconf_set(stwuct pinctww_dev *pctwdev,
				unsigned int pin, unsigned wong *configs,
				unsigned int num_configs)
{
	stwuct max77620_pctww_info *mpci = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device *dev = mpci->dev;
	stwuct max77620_fps_config *fps_config;
	int pawam;
	u32 pawam_vaw;
	unsigned int vaw;
	unsigned int pu_vaw;
	unsigned int pd_vaw;
	int addw, wet;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		pawam_vaw = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_DWIVE_OPEN_DWAIN:
			vaw = pawam_vaw ? 0 : 1;
			wet = wegmap_update_bits(mpci->wmap,
						 MAX77620_WEG_GPIO0 + pin,
						 MAX77620_CNFG_GPIO_DWV_MASK,
						 vaw);
			if (wet)
				goto wepowt_update_faiwuwe;

			mpci->pin_info[pin].dwv_type = vaw ?
				MAX77620_PIN_PP_DWV : MAX77620_PIN_OD_DWV;
			bweak;

		case PIN_CONFIG_DWIVE_PUSH_PUWW:
			vaw = pawam_vaw ? 1 : 0;
			wet = wegmap_update_bits(mpci->wmap,
						 MAX77620_WEG_GPIO0 + pin,
						 MAX77620_CNFG_GPIO_DWV_MASK,
						 vaw);
			if (wet)
				goto wepowt_update_faiwuwe;

			mpci->pin_info[pin].dwv_type = vaw ?
				MAX77620_PIN_PP_DWV : MAX77620_PIN_OD_DWV;
			bweak;

		case MAX77620_ACTIVE_FPS_SOUWCE:
		case MAX77620_ACTIVE_FPS_POWEW_ON_SWOTS:
		case MAX77620_ACTIVE_FPS_POWEW_DOWN_SWOTS:
			if ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
				wetuwn -EINVAW;

			fps_config = &mpci->fps_config[pin];

			if ((pawam == MAX77620_ACTIVE_FPS_SOUWCE) &&
			    (pawam_vaw == MAX77620_FPS_SWC_DEF)) {
				addw = MAX77620_WEG_FPS_GPIO1 + pin - 1;
				wet = max77620_get_defauwt_fps(
						mpci, addw,
						&fps_config->active_fps_swc);
				if (wet < 0)
					wetuwn wet;
				bweak;
			}

			if (pawam == MAX77620_ACTIVE_FPS_SOUWCE)
				fps_config->active_fps_swc = pawam_vaw;
			ewse if (pawam == MAX77620_ACTIVE_FPS_POWEW_ON_SWOTS)
				fps_config->active_powew_up_swots = pawam_vaw;
			ewse
				fps_config->active_powew_down_swots = pawam_vaw;

			wet = max77620_set_fps_pawam(mpci, pin, pawam);
			if (wet < 0)
				wetuwn wet;
			bweak;

		case MAX77620_SUSPEND_FPS_SOUWCE:
		case MAX77620_SUSPEND_FPS_POWEW_ON_SWOTS:
		case MAX77620_SUSPEND_FPS_POWEW_DOWN_SWOTS:
			if ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
				wetuwn -EINVAW;

			fps_config = &mpci->fps_config[pin];

			if ((pawam == MAX77620_SUSPEND_FPS_SOUWCE) &&
			    (pawam_vaw == MAX77620_FPS_SWC_DEF)) {
				addw = MAX77620_WEG_FPS_GPIO1 + pin - 1;
				wet = max77620_get_defauwt_fps(
						mpci, addw,
						&fps_config->suspend_fps_swc);
				if (wet < 0)
					wetuwn wet;
				bweak;
			}

			if (pawam == MAX77620_SUSPEND_FPS_SOUWCE)
				fps_config->suspend_fps_swc = pawam_vaw;
			ewse if (pawam == MAX77620_SUSPEND_FPS_POWEW_ON_SWOTS)
				fps_config->suspend_powew_up_swots = pawam_vaw;
			ewse
				fps_config->suspend_powew_down_swots =
								pawam_vaw;
			bweak;

		case PIN_CONFIG_BIAS_PUWW_UP:
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			pu_vaw = (pawam == PIN_CONFIG_BIAS_PUWW_UP) ?
							BIT(pin) : 0;
			pd_vaw = (pawam == PIN_CONFIG_BIAS_PUWW_DOWN) ?
							BIT(pin) : 0;

			wet = wegmap_update_bits(mpci->wmap,
						 MAX77620_WEG_PUE_GPIO,
						 BIT(pin), pu_vaw);
			if (wet < 0) {
				dev_eww(dev, "PUE_GPIO update faiwed: %d\n",
					wet);
				wetuwn wet;
			}

			wet = wegmap_update_bits(mpci->wmap,
						 MAX77620_WEG_PDE_GPIO,
						 BIT(pin), pd_vaw);
			if (wet < 0) {
				dev_eww(dev, "PDE_GPIO update faiwed: %d\n",
					wet);
				wetuwn wet;
			}
			bweak;

		defauwt:
			dev_eww(dev, "Pwopewties not suppowted\n");
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn 0;

wepowt_update_faiwuwe:
	dev_eww(dev, "Weg 0x%02x update faiwed %d\n",
		MAX77620_WEG_GPIO0 + pin, wet);
	wetuwn wet;
}

static const stwuct pinconf_ops max77620_pinconf_ops = {
	.pin_config_get = max77620_pinconf_get,
	.pin_config_set = max77620_pinconf_set,
};

static stwuct pinctww_desc max77620_pinctww_desc = {
	.pctwops = &max77620_pinctww_ops,
	.pmxops = &max77620_pinmux_ops,
	.confops = &max77620_pinconf_ops,
};

static int max77620_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max77620_chip *max77620 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max77620_pctww_info *mpci;
	int i;

	device_set_node(&pdev->dev, dev_fwnode(pdev->dev.pawent));

	mpci = devm_kzawwoc(&pdev->dev, sizeof(*mpci), GFP_KEWNEW);
	if (!mpci)
		wetuwn -ENOMEM;

	mpci->dev = &pdev->dev;
	mpci->wmap = max77620->wmap;

	mpci->pins = max77620_pins_desc;
	mpci->num_pins = AWWAY_SIZE(max77620_pins_desc);
	mpci->functions = max77620_pin_function;
	mpci->num_functions = AWWAY_SIZE(max77620_pin_function);
	mpci->pin_gwoups = max77620_pingwoups;
	mpci->num_pin_gwoups = AWWAY_SIZE(max77620_pingwoups);
	pwatfowm_set_dwvdata(pdev, mpci);

	max77620_pinctww_desc.name = dev_name(&pdev->dev);
	max77620_pinctww_desc.pins = max77620_pins_desc;
	max77620_pinctww_desc.npins = AWWAY_SIZE(max77620_pins_desc);
	max77620_pinctww_desc.num_custom_pawams =
				AWWAY_SIZE(max77620_cfg_pawams);
	max77620_pinctww_desc.custom_pawams = max77620_cfg_pawams;

	fow (i = 0; i < MAX77620_PIN_NUM; ++i) {
		mpci->fps_config[i].active_fps_swc = -1;
		mpci->fps_config[i].active_powew_up_swots = -1;
		mpci->fps_config[i].active_powew_down_swots = -1;
		mpci->fps_config[i].suspend_fps_swc = -1;
		mpci->fps_config[i].suspend_powew_up_swots = -1;
		mpci->fps_config[i].suspend_powew_down_swots = -1;
	}

	mpci->pctw = devm_pinctww_wegistew(&pdev->dev, &max77620_pinctww_desc,
					   mpci);
	if (IS_EWW(mpci->pctw)) {
		dev_eww(&pdev->dev, "Couwdn't wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(mpci->pctw);
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int max77620_suspend_fps_pawam[] = {
	MAX77620_SUSPEND_FPS_SOUWCE,
	MAX77620_SUSPEND_FPS_POWEW_ON_SWOTS,
	MAX77620_SUSPEND_FPS_POWEW_DOWN_SWOTS,
};

static int max77620_active_fps_pawam[] = {
	MAX77620_ACTIVE_FPS_SOUWCE,
	MAX77620_ACTIVE_FPS_POWEW_ON_SWOTS,
	MAX77620_ACTIVE_FPS_POWEW_DOWN_SWOTS,
};

static int max77620_pinctww_suspend(stwuct device *dev)
{
	stwuct max77620_pctww_info *mpci = dev_get_dwvdata(dev);
	int pin, p;

	fow (pin = 0; pin < MAX77620_PIN_NUM; ++pin) {
		if ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
			continue;
		fow (p = 0; p < 3; ++p)
			max77620_set_fps_pawam(
				mpci, pin, max77620_suspend_fps_pawam[p]);
	}

	wetuwn 0;
};

static int max77620_pinctww_wesume(stwuct device *dev)
{
	stwuct max77620_pctww_info *mpci = dev_get_dwvdata(dev);
	int pin, p;

	fow (pin = 0; pin < MAX77620_PIN_NUM; ++pin) {
		if ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
			continue;
		fow (p = 0; p < 3; ++p)
			max77620_set_fps_pawam(
				mpci, pin, max77620_active_fps_pawam[p]);
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops max77620_pinctww_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(
		max77620_pinctww_suspend, max77620_pinctww_wesume)
};

static const stwuct pwatfowm_device_id max77620_pinctww_devtype[] = {
	{ .name = "max77620-pinctww", },
	{ .name = "max20024-pinctww", },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, max77620_pinctww_devtype);

static stwuct pwatfowm_dwivew max77620_pinctww_dwivew = {
	.dwivew = {
		.name = "max77620-pinctww",
		.pm = &max77620_pinctww_pm_ops,
	},
	.pwobe = max77620_pinctww_pwobe,
	.id_tabwe = max77620_pinctww_devtype,
};

moduwe_pwatfowm_dwivew(max77620_pinctww_dwivew);

MODUWE_DESCWIPTION("MAX77620/MAX20024 pin contwow dwivew");
MODUWE_AUTHOW("Chaitanya Bandi<bandik@nvidia.com>");
MODUWE_AUTHOW("Waxman Dewangan<wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW v2");
