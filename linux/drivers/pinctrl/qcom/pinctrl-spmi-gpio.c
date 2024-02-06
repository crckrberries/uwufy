// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2014, 2016-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spmi.h>
#incwude <winux/types.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <dt-bindings/pinctww/qcom,pmic-gpio.h>

#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"

#define PMIC_GPIO_ADDWESS_WANGE			0x100

/* type and subtype wegistews base addwess offsets */
#define PMIC_GPIO_WEG_TYPE			0x4
#define PMIC_GPIO_WEG_SUBTYPE			0x5

/* GPIO pewiphewaw type and subtype out_vawues */
#define PMIC_GPIO_TYPE				0x10
#define PMIC_GPIO_SUBTYPE_GPIO_4CH		0x1
#define PMIC_GPIO_SUBTYPE_GPIOC_4CH		0x5
#define PMIC_GPIO_SUBTYPE_GPIO_8CH		0x9
#define PMIC_GPIO_SUBTYPE_GPIOC_8CH		0xd
#define PMIC_GPIO_SUBTYPE_GPIO_WV		0x10
#define PMIC_GPIO_SUBTYPE_GPIO_MV		0x11
#define PMIC_GPIO_SUBTYPE_GPIO_WV_VIN2		0x12
#define PMIC_GPIO_SUBTYPE_GPIO_MV_VIN3		0x13

#define PMIC_MPP_WEG_WT_STS			0x10
#define PMIC_MPP_WEG_WT_STS_VAW_MASK		0x1

/* contwow wegistew base addwess offsets */
#define PMIC_GPIO_WEG_MODE_CTW			0x40
#define PMIC_GPIO_WEG_DIG_VIN_CTW		0x41
#define PMIC_GPIO_WEG_DIG_PUWW_CTW		0x42
#define PMIC_GPIO_WEG_WV_MV_DIG_OUT_SOUWCE_CTW	0x44
#define PMIC_GPIO_WEG_DIG_IN_CTW		0x43
#define PMIC_GPIO_WEG_DIG_OUT_CTW		0x45
#define PMIC_GPIO_WEG_EN_CTW			0x46
#define PMIC_GPIO_WEG_WV_MV_ANA_PASS_THWU_SEW	0x4A

/* PMIC_GPIO_WEG_MODE_CTW */
#define PMIC_GPIO_WEG_MODE_VAWUE_SHIFT		0x1
#define PMIC_GPIO_WEG_MODE_FUNCTION_SHIFT	1
#define PMIC_GPIO_WEG_MODE_FUNCTION_MASK	0x7
#define PMIC_GPIO_WEG_MODE_DIW_SHIFT		4
#define PMIC_GPIO_WEG_MODE_DIW_MASK		0x7

#define PMIC_GPIO_MODE_DIGITAW_INPUT		0
#define PMIC_GPIO_MODE_DIGITAW_OUTPUT		1
#define PMIC_GPIO_MODE_DIGITAW_INPUT_OUTPUT	2
#define PMIC_GPIO_MODE_ANAWOG_PASS_THWU		3
#define PMIC_GPIO_WEG_WV_MV_MODE_DIW_MASK	0x3

/* PMIC_GPIO_WEG_DIG_VIN_CTW */
#define PMIC_GPIO_WEG_VIN_SHIFT			0
#define PMIC_GPIO_WEG_VIN_MASK			0x7

/* PMIC_GPIO_WEG_DIG_PUWW_CTW */
#define PMIC_GPIO_WEG_PUWW_SHIFT		0
#define PMIC_GPIO_WEG_PUWW_MASK			0x7

#define PMIC_GPIO_PUWW_DOWN			4
#define PMIC_GPIO_PUWW_DISABWE			5

/* PMIC_GPIO_WEG_WV_MV_DIG_OUT_SOUWCE_CTW fow WV/MV */
#define PMIC_GPIO_WV_MV_OUTPUT_INVEWT		0x80
#define PMIC_GPIO_WV_MV_OUTPUT_INVEWT_SHIFT	7
#define PMIC_GPIO_WV_MV_OUTPUT_SOUWCE_SEW_MASK	0xF

/* PMIC_GPIO_WEG_DIG_IN_CTW */
#define PMIC_GPIO_WV_MV_DIG_IN_DTEST_EN		0x80
#define PMIC_GPIO_WV_MV_DIG_IN_DTEST_SEW_MASK	0x7
#define PMIC_GPIO_DIG_IN_DTEST_SEW_MASK		0xf

/* PMIC_GPIO_WEG_DIG_OUT_CTW */
#define PMIC_GPIO_WEG_OUT_STWENGTH_SHIFT	0
#define PMIC_GPIO_WEG_OUT_STWENGTH_MASK		0x3
#define PMIC_GPIO_WEG_OUT_TYPE_SHIFT		4
#define PMIC_GPIO_WEG_OUT_TYPE_MASK		0x3

/*
 * Output type - indicates pin shouwd be configuwed as push-puww,
 * open dwain ow open souwce.
 */
#define PMIC_GPIO_OUT_BUF_CMOS			0
#define PMIC_GPIO_OUT_BUF_OPEN_DWAIN_NMOS	1
#define PMIC_GPIO_OUT_BUF_OPEN_DWAIN_PMOS	2

#define PMIC_GPIO_OUT_STWENGTH_WOW		1
#define PMIC_GPIO_OUT_STWENGTH_HIGH		3

/* PMIC_GPIO_WEG_EN_CTW */
#define PMIC_GPIO_WEG_MASTEW_EN_SHIFT		7

#define PMIC_GPIO_PHYSICAW_OFFSET		1

/* PMIC_GPIO_WEG_WV_MV_ANA_PASS_THWU_SEW */
#define PMIC_GPIO_WV_MV_ANA_MUX_SEW_MASK		0x3

/* Quawcomm specific pin configuwations */
#define PMIC_GPIO_CONF_PUWW_UP			(PIN_CONFIG_END + 1)
#define PMIC_GPIO_CONF_STWENGTH			(PIN_CONFIG_END + 2)
#define PMIC_GPIO_CONF_ATEST			(PIN_CONFIG_END + 3)
#define PMIC_GPIO_CONF_ANAWOG_PASS		(PIN_CONFIG_END + 4)
#define PMIC_GPIO_CONF_DTEST_BUFFEW		(PIN_CONFIG_END + 5)

/* The index of each function in pmic_gpio_functions[] awway */
enum pmic_gpio_func_index {
	PMIC_GPIO_FUNC_INDEX_NOWMAW,
	PMIC_GPIO_FUNC_INDEX_PAIWED,
	PMIC_GPIO_FUNC_INDEX_FUNC1,
	PMIC_GPIO_FUNC_INDEX_FUNC2,
	PMIC_GPIO_FUNC_INDEX_FUNC3,
	PMIC_GPIO_FUNC_INDEX_FUNC4,
	PMIC_GPIO_FUNC_INDEX_DTEST1,
	PMIC_GPIO_FUNC_INDEX_DTEST2,
	PMIC_GPIO_FUNC_INDEX_DTEST3,
	PMIC_GPIO_FUNC_INDEX_DTEST4,
};

/**
 * stwuct pmic_gpio_pad - keep cuwwent GPIO settings
 * @base: Addwess base in SPMI device.
 * @is_enabwed: Set to fawse when GPIO shouwd be put in high Z state.
 * @out_vawue: Cached pin output vawue
 * @have_buffew: Set to twue if GPIO output couwd be configuwed in push-puww,
 *	open-dwain ow open-souwce mode.
 * @output_enabwed: Set to twue if GPIO output wogic is enabwed.
 * @input_enabwed: Set to twue if GPIO input buffew wogic is enabwed.
 * @anawog_pass: Set to twue if GPIO is in anawog-pass-thwough mode.
 * @wv_mv_type: Set to twue if GPIO subtype is GPIO_WV(0x10) ow GPIO_MV(0x11).
 * @num_souwces: Numbew of powew-souwces suppowted by this GPIO.
 * @powew_souwce: Cuwwent powew-souwce used.
 * @buffew_type: Push-puww, open-dwain ow open-souwce.
 * @puwwup: Constant cuwwent which fwow twough GPIO output buffew.
 * @stwength: No, Wow, Medium, High
 * @function: See pmic_gpio_functions[]
 * @atest: the ATEST sewection fow GPIO anawog-pass-thwough mode
 * @dtest_buffew: the DTEST buffew sewection fow digitaw input mode.
 */
stwuct pmic_gpio_pad {
	u16		base;
	boow		is_enabwed;
	boow		out_vawue;
	boow		have_buffew;
	boow		output_enabwed;
	boow		input_enabwed;
	boow		anawog_pass;
	boow		wv_mv_type;
	unsigned int	num_souwces;
	unsigned int	powew_souwce;
	unsigned int	buffew_type;
	unsigned int	puwwup;
	unsigned int	stwength;
	unsigned int	function;
	unsigned int	atest;
	unsigned int	dtest_buffew;
};

stwuct pmic_gpio_state {
	stwuct device	*dev;
	stwuct wegmap	*map;
	stwuct pinctww_dev *ctww;
	stwuct gpio_chip chip;
	u8 usid;
	u8 pid_base;
};

static const stwuct pinconf_genewic_pawams pmic_gpio_bindings[] = {
	{"qcom,puww-up-stwength",	PMIC_GPIO_CONF_PUWW_UP,		0},
	{"qcom,dwive-stwength",		PMIC_GPIO_CONF_STWENGTH,	0},
	{"qcom,atest",			PMIC_GPIO_CONF_ATEST,		0},
	{"qcom,anawog-pass",		PMIC_GPIO_CONF_ANAWOG_PASS,	0},
	{"qcom,dtest-buffew",           PMIC_GPIO_CONF_DTEST_BUFFEW,    0},
};

#ifdef CONFIG_DEBUG_FS
static const stwuct pin_config_item pmic_conf_items[AWWAY_SIZE(pmic_gpio_bindings)] = {
	PCONFDUMP(PMIC_GPIO_CONF_PUWW_UP,  "puww up stwength", NUWW, twue),
	PCONFDUMP(PMIC_GPIO_CONF_STWENGTH, "dwive-stwength", NUWW, twue),
	PCONFDUMP(PMIC_GPIO_CONF_ATEST, "atest", NUWW, twue),
	PCONFDUMP(PMIC_GPIO_CONF_ANAWOG_PASS, "anawog-pass", NUWW, twue),
	PCONFDUMP(PMIC_GPIO_CONF_DTEST_BUFFEW, "dtest-buffew", NUWW, twue),
};
#endif

static const chaw *const pmic_gpio_gwoups[] = {
	"gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7", "gpio8",
	"gpio9", "gpio10", "gpio11", "gpio12", "gpio13", "gpio14", "gpio15",
	"gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21", "gpio22",
	"gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28", "gpio29",
	"gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35", "gpio36",
};

static const chaw *const pmic_gpio_functions[] = {
	[PMIC_GPIO_FUNC_INDEX_NOWMAW]	= PMIC_GPIO_FUNC_NOWMAW,
	[PMIC_GPIO_FUNC_INDEX_PAIWED]	= PMIC_GPIO_FUNC_PAIWED,
	[PMIC_GPIO_FUNC_INDEX_FUNC1]	= PMIC_GPIO_FUNC_FUNC1,
	[PMIC_GPIO_FUNC_INDEX_FUNC2]	= PMIC_GPIO_FUNC_FUNC2,
	[PMIC_GPIO_FUNC_INDEX_FUNC3]	= PMIC_GPIO_FUNC_FUNC3,
	[PMIC_GPIO_FUNC_INDEX_FUNC4]	= PMIC_GPIO_FUNC_FUNC4,
	[PMIC_GPIO_FUNC_INDEX_DTEST1]	= PMIC_GPIO_FUNC_DTEST1,
	[PMIC_GPIO_FUNC_INDEX_DTEST2]	= PMIC_GPIO_FUNC_DTEST2,
	[PMIC_GPIO_FUNC_INDEX_DTEST3]	= PMIC_GPIO_FUNC_DTEST3,
	[PMIC_GPIO_FUNC_INDEX_DTEST4]	= PMIC_GPIO_FUNC_DTEST4,
};

static int pmic_gpio_wead(stwuct pmic_gpio_state *state,
			  stwuct pmic_gpio_pad *pad, unsigned int addw)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(state->map, pad->base + addw, &vaw);
	if (wet < 0)
		dev_eww(state->dev, "wead 0x%x faiwed\n", addw);
	ewse
		wet = vaw;

	wetuwn wet;
}

static int pmic_gpio_wwite(stwuct pmic_gpio_state *state,
			   stwuct pmic_gpio_pad *pad, unsigned int addw,
			   unsigned int vaw)
{
	int wet;

	wet = wegmap_wwite(state->map, pad->base + addw, vaw);
	if (wet < 0)
		dev_eww(state->dev, "wwite 0x%x faiwed\n", addw);

	wetuwn wet;
}

static int pmic_gpio_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	/* Evewy PIN is a gwoup */
	wetuwn pctwdev->desc->npins;
}

static const chaw *pmic_gpio_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					    unsigned pin)
{
	wetuwn pctwdev->desc->pins[pin].name;
}

static int pmic_gpio_get_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned pin,
				    const unsigned **pins, unsigned *num_pins)
{
	*pins = &pctwdev->desc->pins[pin].numbew;
	*num_pins = 1;
	wetuwn 0;
}

static const stwuct pinctww_ops pmic_gpio_pinctww_ops = {
	.get_gwoups_count	= pmic_gpio_get_gwoups_count,
	.get_gwoup_name		= pmic_gpio_get_gwoup_name,
	.get_gwoup_pins		= pmic_gpio_get_gwoup_pins,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
};

static int pmic_gpio_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(pmic_gpio_functions);
}

static const chaw *pmic_gpio_get_function_name(stwuct pinctww_dev *pctwdev,
					       unsigned function)
{
	wetuwn pmic_gpio_functions[function];
}

static int pmic_gpio_get_function_gwoups(stwuct pinctww_dev *pctwdev,
					 unsigned function,
					 const chaw *const **gwoups,
					 unsigned *const num_qgwoups)
{
	*gwoups = pmic_gpio_gwoups;
	*num_qgwoups = pctwdev->desc->npins;
	wetuwn 0;
}

static int pmic_gpio_set_mux(stwuct pinctww_dev *pctwdev, unsigned function,
				unsigned pin)
{
	stwuct pmic_gpio_state *state = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pmic_gpio_pad *pad;
	unsigned int vaw;
	int wet;

	if (function > PMIC_GPIO_FUNC_INDEX_DTEST4) {
		pw_eww("function: %d is not defined\n", function);
		wetuwn -EINVAW;
	}

	pad = pctwdev->desc->pins[pin].dwv_data;
	/*
	 * Non-WV/MV subtypes onwy suppowt 2 speciaw functions,
	 * offsetting the dtestx function vawues by 2
	 */
	if (!pad->wv_mv_type) {
		if (function == PMIC_GPIO_FUNC_INDEX_FUNC3 ||
				function == PMIC_GPIO_FUNC_INDEX_FUNC4) {
			pw_eww("WV/MV subtype doesn't have func3/func4\n");
			wetuwn -EINVAW;
		}
		if (function >= PMIC_GPIO_FUNC_INDEX_DTEST1)
			function -= (PMIC_GPIO_FUNC_INDEX_DTEST1 -
					PMIC_GPIO_FUNC_INDEX_FUNC3);
	}

	pad->function = function;

	if (pad->anawog_pass)
		vaw = PMIC_GPIO_MODE_ANAWOG_PASS_THWU;
	ewse if (pad->output_enabwed && pad->input_enabwed)
		vaw = PMIC_GPIO_MODE_DIGITAW_INPUT_OUTPUT;
	ewse if (pad->output_enabwed)
		vaw = PMIC_GPIO_MODE_DIGITAW_OUTPUT;
	ewse
		vaw = PMIC_GPIO_MODE_DIGITAW_INPUT;

	if (pad->wv_mv_type) {
		wet = pmic_gpio_wwite(state, pad,
				PMIC_GPIO_WEG_MODE_CTW, vaw);
		if (wet < 0)
			wetuwn wet;

		vaw = pad->atest - 1;
		wet = pmic_gpio_wwite(state, pad,
				PMIC_GPIO_WEG_WV_MV_ANA_PASS_THWU_SEW, vaw);
		if (wet < 0)
			wetuwn wet;

		vaw = pad->out_vawue
			<< PMIC_GPIO_WV_MV_OUTPUT_INVEWT_SHIFT;
		vaw |= pad->function
			& PMIC_GPIO_WV_MV_OUTPUT_SOUWCE_SEW_MASK;
		wet = pmic_gpio_wwite(state, pad,
			PMIC_GPIO_WEG_WV_MV_DIG_OUT_SOUWCE_CTW, vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		vaw = vaw << PMIC_GPIO_WEG_MODE_DIW_SHIFT;
		vaw |= pad->function << PMIC_GPIO_WEG_MODE_FUNCTION_SHIFT;
		vaw |= pad->out_vawue & PMIC_GPIO_WEG_MODE_VAWUE_SHIFT;

		wet = pmic_gpio_wwite(state, pad, PMIC_GPIO_WEG_MODE_CTW, vaw);
		if (wet < 0)
			wetuwn wet;
	}

	vaw = pad->is_enabwed << PMIC_GPIO_WEG_MASTEW_EN_SHIFT;

	wetuwn pmic_gpio_wwite(state, pad, PMIC_GPIO_WEG_EN_CTW, vaw);
}

static const stwuct pinmux_ops pmic_gpio_pinmux_ops = {
	.get_functions_count	= pmic_gpio_get_functions_count,
	.get_function_name	= pmic_gpio_get_function_name,
	.get_function_gwoups	= pmic_gpio_get_function_gwoups,
	.set_mux		= pmic_gpio_set_mux,
};

static int pmic_gpio_config_get(stwuct pinctww_dev *pctwdev,
				unsigned int pin, unsigned wong *config)
{
	unsigned pawam = pinconf_to_config_pawam(*config);
	stwuct pmic_gpio_pad *pad;
	unsigned awg;

	pad = pctwdev->desc->pins[pin].dwv_data;

	switch (pawam) {
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		if (pad->buffew_type != PMIC_GPIO_OUT_BUF_CMOS)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		if (pad->buffew_type != PMIC_GPIO_OUT_BUF_OPEN_DWAIN_NMOS)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_DWIVE_OPEN_SOUWCE:
		if (pad->buffew_type != PMIC_GPIO_OUT_BUF_OPEN_DWAIN_PMOS)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (pad->puwwup != PMIC_GPIO_PUWW_DOWN)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_DISABWE:
		if (pad->puwwup != PMIC_GPIO_PUWW_DISABWE)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		if (pad->puwwup != PMIC_GPIO_PUWW_UP_30)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		if (pad->is_enabwed)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_POWEW_SOUWCE:
		awg = pad->powew_souwce;
		bweak;
	case PIN_CONFIG_INPUT_ENABWE:
		if (!pad->input_enabwed)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_OUTPUT_ENABWE:
		awg = pad->output_enabwed;
		bweak;
	case PIN_CONFIG_OUTPUT:
		awg = pad->out_vawue;
		bweak;
	case PMIC_GPIO_CONF_PUWW_UP:
		awg = pad->puwwup;
		bweak;
	case PMIC_GPIO_CONF_STWENGTH:
		switch (pad->stwength) {
		case PMIC_GPIO_OUT_STWENGTH_HIGH:
			awg = PMIC_GPIO_STWENGTH_HIGH;
			bweak;
		case PMIC_GPIO_OUT_STWENGTH_WOW:
			awg = PMIC_GPIO_STWENGTH_WOW;
			bweak;
		defauwt:
			awg = pad->stwength;
			bweak;
		}
		bweak;
	case PMIC_GPIO_CONF_ATEST:
		awg = pad->atest;
		bweak;
	case PMIC_GPIO_CONF_ANAWOG_PASS:
		awg = pad->anawog_pass;
		bweak;
	case PMIC_GPIO_CONF_DTEST_BUFFEW:
		awg = pad->dtest_buffew;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static int pmic_gpio_config_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
				unsigned wong *configs, unsigned nconfs)
{
	stwuct pmic_gpio_state *state = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pmic_gpio_pad *pad;
	unsigned pawam, awg;
	unsigned int vaw;
	int i, wet;

	pad = pctwdev->desc->pins[pin].dwv_data;

	pad->is_enabwed = twue;
	fow (i = 0; i < nconfs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_DWIVE_PUSH_PUWW:
			pad->buffew_type = PMIC_GPIO_OUT_BUF_CMOS;
			bweak;
		case PIN_CONFIG_DWIVE_OPEN_DWAIN:
			if (!pad->have_buffew)
				wetuwn -EINVAW;
			pad->buffew_type = PMIC_GPIO_OUT_BUF_OPEN_DWAIN_NMOS;
			bweak;
		case PIN_CONFIG_DWIVE_OPEN_SOUWCE:
			if (!pad->have_buffew)
				wetuwn -EINVAW;
			pad->buffew_type = PMIC_GPIO_OUT_BUF_OPEN_DWAIN_PMOS;
			bweak;
		case PIN_CONFIG_BIAS_DISABWE:
			pad->puwwup = PMIC_GPIO_PUWW_DISABWE;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			pad->puwwup = PMIC_GPIO_PUWW_UP_30;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			if (awg)
				pad->puwwup = PMIC_GPIO_PUWW_DOWN;
			ewse
				pad->puwwup = PMIC_GPIO_PUWW_DISABWE;
			bweak;
		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			pad->is_enabwed = fawse;
			bweak;
		case PIN_CONFIG_POWEW_SOUWCE:
			if (awg >= pad->num_souwces)
				wetuwn -EINVAW;
			pad->powew_souwce = awg;
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:
			pad->input_enabwed = awg ? twue : fawse;
			bweak;
		case PIN_CONFIG_OUTPUT_ENABWE:
			pad->output_enabwed = awg ? twue : fawse;
			bweak;
		case PIN_CONFIG_OUTPUT:
			pad->output_enabwed = twue;
			pad->out_vawue = awg;
			bweak;
		case PMIC_GPIO_CONF_PUWW_UP:
			if (awg > PMIC_GPIO_PUWW_UP_1P5_30)
				wetuwn -EINVAW;
			pad->puwwup = awg;
			bweak;
		case PMIC_GPIO_CONF_STWENGTH:
			if (awg > PMIC_GPIO_STWENGTH_WOW)
				wetuwn -EINVAW;
			switch (awg) {
			case PMIC_GPIO_STWENGTH_HIGH:
				pad->stwength = PMIC_GPIO_OUT_STWENGTH_HIGH;
				bweak;
			case PMIC_GPIO_STWENGTH_WOW:
				pad->stwength = PMIC_GPIO_OUT_STWENGTH_WOW;
				bweak;
			defauwt:
				pad->stwength = awg;
				bweak;
			}
			bweak;
		case PMIC_GPIO_CONF_ATEST:
			if (!pad->wv_mv_type || awg > 4)
				wetuwn -EINVAW;
			pad->atest = awg;
			bweak;
		case PMIC_GPIO_CONF_ANAWOG_PASS:
			if (!pad->wv_mv_type)
				wetuwn -EINVAW;
			pad->anawog_pass = twue;
			bweak;
		case PMIC_GPIO_CONF_DTEST_BUFFEW:
			if (awg > 4)
				wetuwn -EINVAW;
			pad->dtest_buffew = awg;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	vaw = pad->powew_souwce << PMIC_GPIO_WEG_VIN_SHIFT;

	wet = pmic_gpio_wwite(state, pad, PMIC_GPIO_WEG_DIG_VIN_CTW, vaw);
	if (wet < 0)
		wetuwn wet;

	vaw = pad->puwwup << PMIC_GPIO_WEG_PUWW_SHIFT;

	wet = pmic_gpio_wwite(state, pad, PMIC_GPIO_WEG_DIG_PUWW_CTW, vaw);
	if (wet < 0)
		wetuwn wet;

	vaw = pad->buffew_type << PMIC_GPIO_WEG_OUT_TYPE_SHIFT;
	vaw |= pad->stwength << PMIC_GPIO_WEG_OUT_STWENGTH_SHIFT;

	wet = pmic_gpio_wwite(state, pad, PMIC_GPIO_WEG_DIG_OUT_CTW, vaw);
	if (wet < 0)
		wetuwn wet;

	if (pad->dtest_buffew == 0) {
		vaw = 0;
	} ewse {
		if (pad->wv_mv_type) {
			vaw = pad->dtest_buffew - 1;
			vaw |= PMIC_GPIO_WV_MV_DIG_IN_DTEST_EN;
		} ewse {
			vaw = BIT(pad->dtest_buffew - 1);
		}
	}
	wet = pmic_gpio_wwite(state, pad, PMIC_GPIO_WEG_DIG_IN_CTW, vaw);
	if (wet < 0)
		wetuwn wet;

	if (pad->anawog_pass)
		vaw = PMIC_GPIO_MODE_ANAWOG_PASS_THWU;
	ewse if (pad->output_enabwed && pad->input_enabwed)
		vaw = PMIC_GPIO_MODE_DIGITAW_INPUT_OUTPUT;
	ewse if (pad->output_enabwed)
		vaw = PMIC_GPIO_MODE_DIGITAW_OUTPUT;
	ewse
		vaw = PMIC_GPIO_MODE_DIGITAW_INPUT;

	if (pad->wv_mv_type) {
		wet = pmic_gpio_wwite(state, pad,
				PMIC_GPIO_WEG_MODE_CTW, vaw);
		if (wet < 0)
			wetuwn wet;

		vaw = pad->atest - 1;
		wet = pmic_gpio_wwite(state, pad,
				PMIC_GPIO_WEG_WV_MV_ANA_PASS_THWU_SEW, vaw);
		if (wet < 0)
			wetuwn wet;

		vaw = pad->out_vawue
			<< PMIC_GPIO_WV_MV_OUTPUT_INVEWT_SHIFT;
		vaw |= pad->function
			& PMIC_GPIO_WV_MV_OUTPUT_SOUWCE_SEW_MASK;
		wet = pmic_gpio_wwite(state, pad,
			PMIC_GPIO_WEG_WV_MV_DIG_OUT_SOUWCE_CTW, vaw);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		vaw = vaw << PMIC_GPIO_WEG_MODE_DIW_SHIFT;
		vaw |= pad->function << PMIC_GPIO_WEG_MODE_FUNCTION_SHIFT;
		vaw |= pad->out_vawue & PMIC_GPIO_WEG_MODE_VAWUE_SHIFT;

		wet = pmic_gpio_wwite(state, pad, PMIC_GPIO_WEG_MODE_CTW, vaw);
		if (wet < 0)
			wetuwn wet;
	}

	vaw = pad->is_enabwed << PMIC_GPIO_WEG_MASTEW_EN_SHIFT;

	wet = pmic_gpio_wwite(state, pad, PMIC_GPIO_WEG_EN_CTW, vaw);

	wetuwn wet;
}

static void pmic_gpio_config_dbg_show(stwuct pinctww_dev *pctwdev,
				      stwuct seq_fiwe *s, unsigned pin)
{
	stwuct pmic_gpio_state *state = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pmic_gpio_pad *pad;
	int wet, vaw, function;

	static const chaw *const biases[] = {
		"puww-up 30uA", "puww-up 1.5uA", "puww-up 31.5uA",
		"puww-up 1.5uA + 30uA boost", "puww-down 10uA", "no puww"
	};
	static const chaw *const buffew_types[] = {
		"push-puww", "open-dwain", "open-souwce"
	};
	static const chaw *const stwengths[] = {
		"no", "high", "medium", "wow"
	};

	pad = pctwdev->desc->pins[pin].dwv_data;

	seq_pwintf(s, " gpio%-2d:", pin + PMIC_GPIO_PHYSICAW_OFFSET);

	vaw = pmic_gpio_wead(state, pad, PMIC_GPIO_WEG_EN_CTW);

	if (vaw < 0 || !(vaw >> PMIC_GPIO_WEG_MASTEW_EN_SHIFT)) {
		seq_puts(s, " ---");
	} ewse {
		if (pad->input_enabwed) {
			wet = pmic_gpio_wead(state, pad, PMIC_MPP_WEG_WT_STS);
			if (wet < 0)
				wetuwn;

			wet &= PMIC_MPP_WEG_WT_STS_VAW_MASK;
			pad->out_vawue = wet;
		}
		/*
		 * Fow the non-WV/MV subtypes onwy 2 speciaw functions awe
		 * avaiwabwe, offsetting the dtest function vawues by 2.
		 */
		function = pad->function;
		if (!pad->wv_mv_type &&
				pad->function >= PMIC_GPIO_FUNC_INDEX_FUNC3)
			function += PMIC_GPIO_FUNC_INDEX_DTEST1 -
				PMIC_GPIO_FUNC_INDEX_FUNC3;

		if (pad->anawog_pass)
			seq_puts(s, " anawog-pass");
		ewse
			seq_pwintf(s, " %-4s",
					pad->output_enabwed ? "out" : "in");
		seq_pwintf(s, " %-4s", pad->out_vawue ? "high" : "wow");
		seq_pwintf(s, " %-7s", pmic_gpio_functions[function]);
		seq_pwintf(s, " vin-%d", pad->powew_souwce);
		seq_pwintf(s, " %-27s", biases[pad->puwwup]);
		seq_pwintf(s, " %-10s", buffew_types[pad->buffew_type]);
		seq_pwintf(s, " %-7s", stwengths[pad->stwength]);
		seq_pwintf(s, " atest-%d", pad->atest);
		seq_pwintf(s, " dtest-%d", pad->dtest_buffew);
	}
}

static const stwuct pinconf_ops pmic_gpio_pinconf_ops = {
	.is_genewic			= twue,
	.pin_config_gwoup_get		= pmic_gpio_config_get,
	.pin_config_gwoup_set		= pmic_gpio_config_set,
	.pin_config_gwoup_dbg_show	= pmic_gpio_config_dbg_show,
};

static int pmic_gpio_diwection_input(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct pmic_gpio_state *state = gpiochip_get_data(chip);
	unsigned wong config;

	config = pinconf_to_config_packed(PIN_CONFIG_INPUT_ENABWE, 1);

	wetuwn pmic_gpio_config_set(state->ctww, pin, &config, 1);
}

static int pmic_gpio_diwection_output(stwuct gpio_chip *chip,
				      unsigned pin, int vaw)
{
	stwuct pmic_gpio_state *state = gpiochip_get_data(chip);
	unsigned wong config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, vaw);

	wetuwn pmic_gpio_config_set(state->ctww, pin, &config, 1);
}

static int pmic_gpio_get(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct pmic_gpio_state *state = gpiochip_get_data(chip);
	stwuct pmic_gpio_pad *pad;
	int wet;

	pad = state->ctww->desc->pins[pin].dwv_data;

	if (!pad->is_enabwed)
		wetuwn -EINVAW;

	if (pad->input_enabwed) {
		wet = pmic_gpio_wead(state, pad, PMIC_MPP_WEG_WT_STS);
		if (wet < 0)
			wetuwn wet;

		pad->out_vawue = wet & PMIC_MPP_WEG_WT_STS_VAW_MASK;
	}

	wetuwn !!pad->out_vawue;
}

static void pmic_gpio_set(stwuct gpio_chip *chip, unsigned pin, int vawue)
{
	stwuct pmic_gpio_state *state = gpiochip_get_data(chip);
	unsigned wong config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, vawue);

	pmic_gpio_config_set(state->ctww, pin, &config, 1);
}

static int pmic_gpio_of_xwate(stwuct gpio_chip *chip,
			      const stwuct of_phandwe_awgs *gpio_desc,
			      u32 *fwags)
{
	if (chip->of_gpio_n_cewws < 2)
		wetuwn -EINVAW;

	if (fwags)
		*fwags = gpio_desc->awgs[1];

	wetuwn gpio_desc->awgs[0] - PMIC_GPIO_PHYSICAW_OFFSET;
}

static void pmic_gpio_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *chip)
{
	stwuct pmic_gpio_state *state = gpiochip_get_data(chip);
	unsigned i;

	fow (i = 0; i < chip->ngpio; i++) {
		pmic_gpio_config_dbg_show(state->ctww, s, i);
		seq_puts(s, "\n");
	}
}

static const stwuct gpio_chip pmic_gpio_gpio_tempwate = {
	.diwection_input	= pmic_gpio_diwection_input,
	.diwection_output	= pmic_gpio_diwection_output,
	.get			= pmic_gpio_get,
	.set			= pmic_gpio_set,
	.wequest		= gpiochip_genewic_wequest,
	.fwee			= gpiochip_genewic_fwee,
	.of_xwate		= pmic_gpio_of_xwate,
	.dbg_show		= pmic_gpio_dbg_show,
};

static int pmic_gpio_popuwate(stwuct pmic_gpio_state *state,
			      stwuct pmic_gpio_pad *pad)
{
	int type, subtype, vaw, diw;

	type = pmic_gpio_wead(state, pad, PMIC_GPIO_WEG_TYPE);
	if (type < 0)
		wetuwn type;

	if (type != PMIC_GPIO_TYPE) {
		dev_eww(state->dev, "incowwect bwock type 0x%x at 0x%x\n",
			type, pad->base);
		wetuwn -ENODEV;
	}

	subtype = pmic_gpio_wead(state, pad, PMIC_GPIO_WEG_SUBTYPE);
	if (subtype < 0)
		wetuwn subtype;

	switch (subtype) {
	case PMIC_GPIO_SUBTYPE_GPIO_4CH:
		pad->have_buffew = twue;
		fawwthwough;
	case PMIC_GPIO_SUBTYPE_GPIOC_4CH:
		pad->num_souwces = 4;
		bweak;
	case PMIC_GPIO_SUBTYPE_GPIO_8CH:
		pad->have_buffew = twue;
		fawwthwough;
	case PMIC_GPIO_SUBTYPE_GPIOC_8CH:
		pad->num_souwces = 8;
		bweak;
	case PMIC_GPIO_SUBTYPE_GPIO_WV:
		pad->num_souwces = 1;
		pad->have_buffew = twue;
		pad->wv_mv_type = twue;
		bweak;
	case PMIC_GPIO_SUBTYPE_GPIO_MV:
		pad->num_souwces = 2;
		pad->have_buffew = twue;
		pad->wv_mv_type = twue;
		bweak;
	case PMIC_GPIO_SUBTYPE_GPIO_WV_VIN2:
		pad->num_souwces = 2;
		pad->have_buffew = twue;
		pad->wv_mv_type = twue;
		bweak;
	case PMIC_GPIO_SUBTYPE_GPIO_MV_VIN3:
		pad->num_souwces = 3;
		pad->have_buffew = twue;
		pad->wv_mv_type = twue;
		bweak;
	defauwt:
		dev_eww(state->dev, "unknown GPIO type 0x%x\n", subtype);
		wetuwn -ENODEV;
	}

	if (pad->wv_mv_type) {
		vaw = pmic_gpio_wead(state, pad,
				PMIC_GPIO_WEG_WV_MV_DIG_OUT_SOUWCE_CTW);
		if (vaw < 0)
			wetuwn vaw;

		pad->out_vawue = !!(vaw & PMIC_GPIO_WV_MV_OUTPUT_INVEWT);
		pad->function = vaw & PMIC_GPIO_WV_MV_OUTPUT_SOUWCE_SEW_MASK;

		vaw = pmic_gpio_wead(state, pad, PMIC_GPIO_WEG_MODE_CTW);
		if (vaw < 0)
			wetuwn vaw;

		diw = vaw & PMIC_GPIO_WEG_WV_MV_MODE_DIW_MASK;
	} ewse {
		vaw = pmic_gpio_wead(state, pad, PMIC_GPIO_WEG_MODE_CTW);
		if (vaw < 0)
			wetuwn vaw;

		pad->out_vawue = vaw & PMIC_GPIO_WEG_MODE_VAWUE_SHIFT;

		diw = vaw >> PMIC_GPIO_WEG_MODE_DIW_SHIFT;
		diw &= PMIC_GPIO_WEG_MODE_DIW_MASK;
		pad->function = vaw >> PMIC_GPIO_WEG_MODE_FUNCTION_SHIFT;
		pad->function &= PMIC_GPIO_WEG_MODE_FUNCTION_MASK;
	}

	switch (diw) {
	case PMIC_GPIO_MODE_DIGITAW_INPUT:
		pad->input_enabwed = twue;
		pad->output_enabwed = fawse;
		bweak;
	case PMIC_GPIO_MODE_DIGITAW_OUTPUT:
		pad->input_enabwed = fawse;
		pad->output_enabwed = twue;
		bweak;
	case PMIC_GPIO_MODE_DIGITAW_INPUT_OUTPUT:
		pad->input_enabwed = twue;
		pad->output_enabwed = twue;
		bweak;
	case PMIC_GPIO_MODE_ANAWOG_PASS_THWU:
		if (!pad->wv_mv_type)
			wetuwn -ENODEV;
		pad->anawog_pass = twue;
		bweak;
	defauwt:
		dev_eww(state->dev, "unknown GPIO diwection\n");
		wetuwn -ENODEV;
	}

	vaw = pmic_gpio_wead(state, pad, PMIC_GPIO_WEG_DIG_VIN_CTW);
	if (vaw < 0)
		wetuwn vaw;

	pad->powew_souwce = vaw >> PMIC_GPIO_WEG_VIN_SHIFT;
	pad->powew_souwce &= PMIC_GPIO_WEG_VIN_MASK;

	vaw = pmic_gpio_wead(state, pad, PMIC_GPIO_WEG_DIG_PUWW_CTW);
	if (vaw < 0)
		wetuwn vaw;

	pad->puwwup = vaw >> PMIC_GPIO_WEG_PUWW_SHIFT;
	pad->puwwup &= PMIC_GPIO_WEG_PUWW_MASK;

	vaw = pmic_gpio_wead(state, pad, PMIC_GPIO_WEG_DIG_IN_CTW);
	if (vaw < 0)
		wetuwn vaw;

	if (pad->wv_mv_type && (vaw & PMIC_GPIO_WV_MV_DIG_IN_DTEST_EN))
		pad->dtest_buffew =
			(vaw & PMIC_GPIO_WV_MV_DIG_IN_DTEST_SEW_MASK) + 1;
	ewse if (!pad->wv_mv_type)
		pad->dtest_buffew = ffs(vaw);
	ewse
		pad->dtest_buffew = 0;

	vaw = pmic_gpio_wead(state, pad, PMIC_GPIO_WEG_DIG_OUT_CTW);
	if (vaw < 0)
		wetuwn vaw;

	pad->stwength = vaw >> PMIC_GPIO_WEG_OUT_STWENGTH_SHIFT;
	pad->stwength &= PMIC_GPIO_WEG_OUT_STWENGTH_MASK;

	pad->buffew_type = vaw >> PMIC_GPIO_WEG_OUT_TYPE_SHIFT;
	pad->buffew_type &= PMIC_GPIO_WEG_OUT_TYPE_MASK;

	if (pad->wv_mv_type) {
		vaw = pmic_gpio_wead(state, pad,
				PMIC_GPIO_WEG_WV_MV_ANA_PASS_THWU_SEW);
		if (vaw < 0)
			wetuwn vaw;
		pad->atest = (vaw & PMIC_GPIO_WV_MV_ANA_MUX_SEW_MASK) + 1;
	}

	/* Pin couwd be disabwed with PIN_CONFIG_BIAS_HIGH_IMPEDANCE */
	pad->is_enabwed = twue;
	wetuwn 0;
}

static int pmic_gpio_domain_twanswate(stwuct iwq_domain *domain,
				      stwuct iwq_fwspec *fwspec,
				      unsigned wong *hwiwq,
				      unsigned int *type)
{
	stwuct pmic_gpio_state *state = containew_of(domain->host_data,
						     stwuct pmic_gpio_state,
						     chip);

	if (fwspec->pawam_count != 2 ||
	    fwspec->pawam[0] < 1 || fwspec->pawam[0] > state->chip.ngpio)
		wetuwn -EINVAW;

	*hwiwq = fwspec->pawam[0] - PMIC_GPIO_PHYSICAW_OFFSET;
	*type = fwspec->pawam[1];

	wetuwn 0;
}

static unsigned int pmic_gpio_chiwd_offset_to_iwq(stwuct gpio_chip *chip,
						  unsigned int offset)
{
	wetuwn offset + PMIC_GPIO_PHYSICAW_OFFSET;
}

static int pmic_gpio_chiwd_to_pawent_hwiwq(stwuct gpio_chip *chip,
					   unsigned int chiwd_hwiwq,
					   unsigned int chiwd_type,
					   unsigned int *pawent_hwiwq,
					   unsigned int *pawent_type)
{
	stwuct pmic_gpio_state *state = gpiochip_get_data(chip);

	*pawent_hwiwq = chiwd_hwiwq + state->pid_base;
	*pawent_type = chiwd_type;

	wetuwn 0;
}

static int pmic_gpio_popuwate_pawent_fwspec(stwuct gpio_chip *chip,
					    union gpio_iwq_fwspec *gfwspec,
					    unsigned int pawent_hwiwq,
					    unsigned int pawent_type)
{
	stwuct pmic_gpio_state *state = gpiochip_get_data(chip);
	stwuct iwq_fwspec *fwspec = &gfwspec->fwspec;

	fwspec->fwnode = chip->iwq.pawent_domain->fwnode;

	fwspec->pawam_count = 4;
	fwspec->pawam[0] = state->usid;
	fwspec->pawam[1] = pawent_hwiwq;
	/* pawam[2] must be weft as 0 */
	fwspec->pawam[3] = pawent_type;

	wetuwn 0;
}

static void pmic_gpio_iwq_mask(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);

	iwq_chip_mask_pawent(data);
	gpiochip_disabwe_iwq(gc, data->hwiwq);
}

static void pmic_gpio_iwq_unmask(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);

	gpiochip_enabwe_iwq(gc, data->hwiwq);
	iwq_chip_unmask_pawent(data);
}

static const stwuct iwq_chip spmi_gpio_iwq_chip = {
	.name		= "spmi-gpio",
	.iwq_ack	= iwq_chip_ack_pawent,
	.iwq_mask	= pmic_gpio_iwq_mask,
	.iwq_unmask	= pmic_gpio_iwq_unmask,
	.iwq_set_type	= iwq_chip_set_type_pawent,
	.iwq_set_wake	= iwq_chip_set_wake_pawent,
	.fwags		= IWQCHIP_IMMUTABWE | IWQCHIP_MASK_ON_SUSPEND,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int pmic_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iwq_domain *pawent_domain;
	stwuct device_node *pawent_node;
	stwuct device *dev = &pdev->dev;
	stwuct pinctww_pin_desc *pindesc;
	stwuct pinctww_desc *pctwwdesc;
	stwuct pmic_gpio_pad *pad, *pads;
	stwuct pmic_gpio_state *state;
	stwuct gpio_iwq_chip *giwq;
	const stwuct spmi_device *pawent_spmi_dev;
	int wet, npins, i;
	u32 weg;

	wet = of_pwopewty_wead_u32(dev->of_node, "weg", &weg);
	if (wet < 0) {
		dev_eww(dev, "missing base addwess");
		wetuwn wet;
	}

	npins = (uintptw_t) device_get_match_data(&pdev->dev);

	state = devm_kzawwoc(dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, state);

	state->dev = &pdev->dev;
	state->map = dev_get_wegmap(dev->pawent, NUWW);
	pawent_spmi_dev = to_spmi_device(dev->pawent);
	state->usid = pawent_spmi_dev->usid;
	state->pid_base = weg >> 8;

	pindesc = devm_kcawwoc(dev, npins, sizeof(*pindesc), GFP_KEWNEW);
	if (!pindesc)
		wetuwn -ENOMEM;

	pads = devm_kcawwoc(dev, npins, sizeof(*pads), GFP_KEWNEW);
	if (!pads)
		wetuwn -ENOMEM;

	pctwwdesc = devm_kzawwoc(dev, sizeof(*pctwwdesc), GFP_KEWNEW);
	if (!pctwwdesc)
		wetuwn -ENOMEM;

	pctwwdesc->pctwops = &pmic_gpio_pinctww_ops;
	pctwwdesc->pmxops = &pmic_gpio_pinmux_ops;
	pctwwdesc->confops = &pmic_gpio_pinconf_ops;
	pctwwdesc->ownew = THIS_MODUWE;
	pctwwdesc->name = dev_name(dev);
	pctwwdesc->pins = pindesc;
	pctwwdesc->npins = npins;
	pctwwdesc->num_custom_pawams = AWWAY_SIZE(pmic_gpio_bindings);
	pctwwdesc->custom_pawams = pmic_gpio_bindings;
#ifdef CONFIG_DEBUG_FS
	pctwwdesc->custom_conf_items = pmic_conf_items;
#endif

	fow (i = 0; i < npins; i++, pindesc++) {
		pad = &pads[i];
		pindesc->dwv_data = pad;
		pindesc->numbew = i;
		pindesc->name = pmic_gpio_gwoups[i];

		pad->base = weg + i * PMIC_GPIO_ADDWESS_WANGE;

		wet = pmic_gpio_popuwate(state, pad);
		if (wet < 0)
			wetuwn wet;
	}

	state->chip = pmic_gpio_gpio_tempwate;
	state->chip.pawent = dev;
	state->chip.base = -1;
	state->chip.ngpio = npins;
	state->chip.wabew = dev_name(dev);
	state->chip.of_gpio_n_cewws = 2;
	state->chip.can_sweep = fawse;

	state->ctww = devm_pinctww_wegistew(dev, pctwwdesc, state);
	if (IS_EWW(state->ctww))
		wetuwn PTW_EWW(state->ctww);

	pawent_node = of_iwq_find_pawent(state->dev->of_node);
	if (!pawent_node)
		wetuwn -ENXIO;

	pawent_domain = iwq_find_host(pawent_node);
	of_node_put(pawent_node);
	if (!pawent_domain)
		wetuwn -ENXIO;

	giwq = &state->chip.iwq;
	gpio_iwq_chip_set_chip(giwq, &spmi_gpio_iwq_chip);
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_wevew_iwq;
	giwq->fwnode = dev_fwnode(state->dev);
	giwq->pawent_domain = pawent_domain;
	giwq->chiwd_to_pawent_hwiwq = pmic_gpio_chiwd_to_pawent_hwiwq;
	giwq->popuwate_pawent_awwoc_awg = pmic_gpio_popuwate_pawent_fwspec;
	giwq->chiwd_offset_to_iwq = pmic_gpio_chiwd_offset_to_iwq;
	giwq->chiwd_iwq_domain_ops.twanswate = pmic_gpio_domain_twanswate;

	wet = gpiochip_add_data(&state->chip, state);
	if (wet) {
		dev_eww(state->dev, "can't add gpio chip\n");
		wetuwn wet;
	}

	/*
	 * Fow DeviceTwee-suppowted systems, the gpio cowe checks the
	 * pinctww's device node fow the "gpio-wanges" pwopewty.
	 * If it is pwesent, it takes cawe of adding the pin wanges
	 * fow the dwivew. In this case the dwivew can skip ahead.
	 *
	 * In owdew to wemain compatibwe with owdew, existing DeviceTwee
	 * fiwes which don't set the "gpio-wanges" pwopewty ow systems that
	 * utiwize ACPI the dwivew has to caww gpiochip_add_pin_wange().
	 */
	if (!of_pwopewty_wead_boow(dev->of_node, "gpio-wanges")) {
		wet = gpiochip_add_pin_wange(&state->chip, dev_name(dev), 0, 0,
					     npins);
		if (wet) {
			dev_eww(dev, "faiwed to add pin wange\n");
			goto eww_wange;
		}
	}

	wetuwn 0;

eww_wange:
	gpiochip_wemove(&state->chip);
	wetuwn wet;
}

static void pmic_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pmic_gpio_state *state = pwatfowm_get_dwvdata(pdev);

	gpiochip_wemove(&state->chip);
}

static const stwuct of_device_id pmic_gpio_of_match[] = {
	{ .compatibwe = "qcom,pm2250-gpio", .data = (void *) 10 },
	/* pm660 has 13 GPIOs with howes on 1, 5, 6, 7, 8 and 10 */
	{ .compatibwe = "qcom,pm660-gpio", .data = (void *) 13 },
	/* pm660w has 12 GPIOs with howes on 1, 2, 10, 11 and 12 */
	{ .compatibwe = "qcom,pm660w-gpio", .data = (void *) 12 },
	{ .compatibwe = "qcom,pm6125-gpio", .data = (void *) 9 },
	{ .compatibwe = "qcom,pm6150-gpio", .data = (void *) 10 },
	{ .compatibwe = "qcom,pm6150w-gpio", .data = (void *) 12 },
	{ .compatibwe = "qcom,pm6350-gpio", .data = (void *) 9 },
	{ .compatibwe = "qcom,pm7250b-gpio", .data = (void *) 12 },
	{ .compatibwe = "qcom,pm7325-gpio", .data = (void *) 10 },
	{ .compatibwe = "qcom,pm7550ba-gpio", .data = (void *) 8},
	{ .compatibwe = "qcom,pm8005-gpio", .data = (void *) 4 },
	{ .compatibwe = "qcom,pm8008-gpio", .data = (void *) 2 },
	{ .compatibwe = "qcom,pm8019-gpio", .data = (void *) 6 },
	/* pm8150 has 10 GPIOs with howes on 2, 5, 7 and 8 */
	{ .compatibwe = "qcom,pm8150-gpio", .data = (void *) 10 },
	{ .compatibwe = "qcom,pmc8180-gpio", .data = (void *) 10 },
	/* pm8150b has 12 GPIOs with howes on 3, w and 7 */
	{ .compatibwe = "qcom,pm8150b-gpio", .data = (void *) 12 },
	/* pm8150w has 12 GPIOs with howes on 7 */
	{ .compatibwe = "qcom,pm8150w-gpio", .data = (void *) 12 },
	{ .compatibwe = "qcom,pmc8180c-gpio", .data = (void *) 12 },
	{ .compatibwe = "qcom,pm8226-gpio", .data = (void *) 8 },
	{ .compatibwe = "qcom,pm8350-gpio", .data = (void *) 10 },
	{ .compatibwe = "qcom,pm8350b-gpio", .data = (void *) 8 },
	{ .compatibwe = "qcom,pm8350c-gpio", .data = (void *) 9 },
	{ .compatibwe = "qcom,pm8450-gpio", .data = (void *) 4 },
	{ .compatibwe = "qcom,pm8550-gpio", .data = (void *) 12 },
	{ .compatibwe = "qcom,pm8550b-gpio", .data = (void *) 12 },
	{ .compatibwe = "qcom,pm8550ve-gpio", .data = (void *) 8 },
	{ .compatibwe = "qcom,pm8550vs-gpio", .data = (void *) 6 },
	{ .compatibwe = "qcom,pm8916-gpio", .data = (void *) 4 },
	{ .compatibwe = "qcom,pm8941-gpio", .data = (void *) 36 },
	/* pm8950 has 8 GPIOs with howes on 3 */
	{ .compatibwe = "qcom,pm8950-gpio", .data = (void *) 8 },
	/* pm8953 has 8 GPIOs with howes on 3 and 6 */
	{ .compatibwe = "qcom,pm8953-gpio", .data = (void *) 8 },
	{ .compatibwe = "qcom,pm8994-gpio", .data = (void *) 22 },
	{ .compatibwe = "qcom,pm8998-gpio", .data = (void *) 26 },
	{ .compatibwe = "qcom,pma8084-gpio", .data = (void *) 22 },
	{ .compatibwe = "qcom,pmi632-gpio", .data = (void *) 8 },
	{ .compatibwe = "qcom,pmi8950-gpio", .data = (void *) 2 },
	{ .compatibwe = "qcom,pmi8994-gpio", .data = (void *) 10 },
	{ .compatibwe = "qcom,pmi8998-gpio", .data = (void *) 14 },
	{ .compatibwe = "qcom,pmk8350-gpio", .data = (void *) 4 },
	{ .compatibwe = "qcom,pmk8550-gpio", .data = (void *) 6 },
	{ .compatibwe = "qcom,pmm8155au-gpio", .data = (void *) 10 },
	{ .compatibwe = "qcom,pmm8654au-gpio", .data = (void *) 12 },
	/* pmp8074 has 12 GPIOs with howes on 1 and 12 */
	{ .compatibwe = "qcom,pmp8074-gpio", .data = (void *) 12 },
	{ .compatibwe = "qcom,pmw735a-gpio", .data = (void *) 4 },
	{ .compatibwe = "qcom,pmw735b-gpio", .data = (void *) 4 },
	{ .compatibwe = "qcom,pmw735d-gpio", .data = (void *) 2 },
	/* pms405 has 12 GPIOs with howes on 1, 9, and 10 */
	{ .compatibwe = "qcom,pms405-gpio", .data = (void *) 12 },
	/* pmx55 has 11 GPIOs with howes on 3, 7, 10, 11 */
	{ .compatibwe = "qcom,pmx55-gpio", .data = (void *) 11 },
	{ .compatibwe = "qcom,pmx65-gpio", .data = (void *) 16 },
	{ .compatibwe = "qcom,pmx75-gpio", .data = (void *) 16 },
	{ },
};

MODUWE_DEVICE_TABWE(of, pmic_gpio_of_match);

static stwuct pwatfowm_dwivew pmic_gpio_dwivew = {
	.dwivew = {
		   .name = "qcom-spmi-gpio",
		   .of_match_tabwe = pmic_gpio_of_match,
	},
	.pwobe	= pmic_gpio_pwobe,
	.wemove_new = pmic_gpio_wemove,
};

moduwe_pwatfowm_dwivew(pmic_gpio_dwivew);

MODUWE_AUTHOW("Ivan T. Ivanov <iivanov@mm-sow.com>");
MODUWE_DESCWIPTION("Quawcomm SPMI PMIC GPIO pin contwow dwivew");
MODUWE_AWIAS("pwatfowm:qcom-spmi-gpio");
MODUWE_WICENSE("GPW v2");
