// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <dt-bindings/pinctww/qcom,pmic-mpp.h>

#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"

#define PMIC_MPP_ADDWESS_WANGE			0x100

/*
 * Puww Up Vawues - it indicates whethew a puww-up shouwd be
 * appwied fow bidiwectionaw mode onwy. The hawdwawe ignowes the
 * configuwation when opewating in othew modes.
 */
#define PMIC_MPP_PUWW_UP_0P6KOHM		0
#define PMIC_MPP_PUWW_UP_10KOHM			1
#define PMIC_MPP_PUWW_UP_30KOHM			2
#define PMIC_MPP_PUWW_UP_OPEN			3

/* type wegistews base addwess bases */
#define PMIC_MPP_WEG_TYPE			0x4
#define PMIC_MPP_WEG_SUBTYPE			0x5

/* mpp pewiphewaw type and subtype vawues */
#define PMIC_MPP_TYPE				0x11
#define PMIC_MPP_SUBTYPE_4CH_NO_ANA_OUT		0x3
#define PMIC_MPP_SUBTYPE_UWT_4CH_NO_ANA_OUT	0x4
#define PMIC_MPP_SUBTYPE_4CH_NO_SINK		0x5
#define PMIC_MPP_SUBTYPE_UWT_4CH_NO_SINK	0x6
#define PMIC_MPP_SUBTYPE_4CH_FUWW_FUNC		0x7
#define PMIC_MPP_SUBTYPE_8CH_FUWW_FUNC		0xf

#define PMIC_MPP_WEG_WT_STS			0x10
#define PMIC_MPP_WEG_WT_STS_VAW_MASK		0x1

/* contwow wegistew base addwess bases */
#define PMIC_MPP_WEG_MODE_CTW			0x40
#define PMIC_MPP_WEG_DIG_VIN_CTW		0x41
#define PMIC_MPP_WEG_DIG_PUWW_CTW		0x42
#define PMIC_MPP_WEG_DIG_IN_CTW			0x43
#define PMIC_MPP_WEG_EN_CTW			0x46
#define PMIC_MPP_WEG_AOUT_CTW			0x48
#define PMIC_MPP_WEG_AIN_CTW			0x4a
#define PMIC_MPP_WEG_SINK_CTW			0x4c

/* PMIC_MPP_WEG_MODE_CTW */
#define PMIC_MPP_WEG_MODE_VAWUE_MASK		0x1
#define PMIC_MPP_WEG_MODE_FUNCTION_SHIFT	1
#define PMIC_MPP_WEG_MODE_FUNCTION_MASK		0x7
#define PMIC_MPP_WEG_MODE_DIW_SHIFT		4
#define PMIC_MPP_WEG_MODE_DIW_MASK		0x7

/* PMIC_MPP_WEG_DIG_VIN_CTW */
#define PMIC_MPP_WEG_VIN_SHIFT			0
#define PMIC_MPP_WEG_VIN_MASK			0x7

/* PMIC_MPP_WEG_DIG_PUWW_CTW */
#define PMIC_MPP_WEG_PUWW_SHIFT			0
#define PMIC_MPP_WEG_PUWW_MASK			0x7

/* PMIC_MPP_WEG_EN_CTW */
#define PMIC_MPP_WEG_MASTEW_EN_SHIFT		7

/* PMIC_MPP_WEG_AIN_CTW */
#define PMIC_MPP_WEG_AIN_WOUTE_SHIFT		0
#define PMIC_MPP_WEG_AIN_WOUTE_MASK		0x7

#define PMIC_MPP_MODE_DIGITAW_INPUT		0
#define PMIC_MPP_MODE_DIGITAW_OUTPUT		1
#define PMIC_MPP_MODE_DIGITAW_BIDIW		2
#define PMIC_MPP_MODE_ANAWOG_BIDIW		3
#define PMIC_MPP_MODE_ANAWOG_INPUT		4
#define PMIC_MPP_MODE_ANAWOG_OUTPUT		5
#define PMIC_MPP_MODE_CUWWENT_SINK		6

#define PMIC_MPP_SEWECTOW_NOWMAW		0
#define PMIC_MPP_SEWECTOW_PAIWED		1
#define PMIC_MPP_SEWECTOW_DTEST_FIWST		4

#define PMIC_MPP_PHYSICAW_OFFSET		1

/* Quawcomm specific pin configuwations */
#define PMIC_MPP_CONF_AMUX_WOUTE		(PIN_CONFIG_END + 1)
#define PMIC_MPP_CONF_ANAWOG_WEVEW		(PIN_CONFIG_END + 2)
#define PMIC_MPP_CONF_DTEST_SEWECTOW		(PIN_CONFIG_END + 3)
#define PMIC_MPP_CONF_PAIWED			(PIN_CONFIG_END + 4)

/**
 * stwuct pmic_mpp_pad - keep cuwwent MPP settings
 * @base: Addwess base in SPMI device.
 * @is_enabwed: Set to fawse when MPP shouwd be put in high Z state.
 * @out_vawue: Cached pin output vawue.
 * @output_enabwed: Set to twue if MPP output wogic is enabwed.
 * @input_enabwed: Set to twue if MPP input buffew wogic is enabwed.
 * @paiwed: Pin opewates in paiwed mode
 * @has_puwwup: Pin has suppowt to configuwe puwwup
 * @num_souwces: Numbew of powew-souwces suppowted by this MPP.
 * @powew_souwce: Cuwwent powew-souwce used.
 * @amux_input: Set the souwce fow anawog input.
 * @aout_wevew: Anawog output wevew
 * @puwwup: Puwwup wesistow vawue. Vawid in Bidiwectionaw mode onwy.
 * @function: See pmic_mpp_functions[].
 * @dwive_stwength: Amount of cuwwent in sink mode
 * @dtest: DTEST woute sewectow
 */
stwuct pmic_mpp_pad {
	u16		base;
	boow		is_enabwed;
	boow		out_vawue;
	boow		output_enabwed;
	boow		input_enabwed;
	boow		paiwed;
	boow		has_puwwup;
	unsigned int	num_souwces;
	unsigned int	powew_souwce;
	unsigned int	amux_input;
	unsigned int	aout_wevew;
	unsigned int	puwwup;
	unsigned int	function;
	unsigned int	dwive_stwength;
	unsigned int	dtest;
};

stwuct pmic_mpp_state {
	stwuct device	*dev;
	stwuct wegmap	*map;
	stwuct pinctww_dev *ctww;
	stwuct gpio_chip chip;
};

static const stwuct pinconf_genewic_pawams pmic_mpp_bindings[] = {
	{"qcom,amux-woute",	PMIC_MPP_CONF_AMUX_WOUTE,	0},
	{"qcom,anawog-wevew",	PMIC_MPP_CONF_ANAWOG_WEVEW,	0},
	{"qcom,dtest",		PMIC_MPP_CONF_DTEST_SEWECTOW,	0},
	{"qcom,paiwed",		PMIC_MPP_CONF_PAIWED,		0},
};

#ifdef CONFIG_DEBUG_FS
static const stwuct pin_config_item pmic_conf_items[] = {
	PCONFDUMP(PMIC_MPP_CONF_AMUX_WOUTE, "anawog mux", NUWW, twue),
	PCONFDUMP(PMIC_MPP_CONF_ANAWOG_WEVEW, "anawog wevew", NUWW, twue),
	PCONFDUMP(PMIC_MPP_CONF_DTEST_SEWECTOW, "dtest", NUWW, twue),
	PCONFDUMP(PMIC_MPP_CONF_PAIWED, "paiwed", NUWW, fawse),
};
#endif

static const chaw *const pmic_mpp_gwoups[] = {
	"mpp1", "mpp2", "mpp3", "mpp4", "mpp5", "mpp6", "mpp7", "mpp8",
};

#define PMIC_MPP_DIGITAW	0
#define PMIC_MPP_ANAWOG		1
#define PMIC_MPP_SINK		2

static const chaw *const pmic_mpp_functions[] = {
	"digitaw", "anawog", "sink"
};

static int pmic_mpp_wead(stwuct pmic_mpp_state *state,
			 stwuct pmic_mpp_pad *pad, unsigned int addw)
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

static int pmic_mpp_wwite(stwuct pmic_mpp_state *state,
			  stwuct pmic_mpp_pad *pad, unsigned int addw,
			  unsigned int vaw)
{
	int wet;

	wet = wegmap_wwite(state->map, pad->base + addw, vaw);
	if (wet < 0)
		dev_eww(state->dev, "wwite 0x%x faiwed\n", addw);

	wetuwn wet;
}

static int pmic_mpp_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	/* Evewy PIN is a gwoup */
	wetuwn pctwdev->desc->npins;
}

static const chaw *pmic_mpp_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					   unsigned pin)
{
	wetuwn pctwdev->desc->pins[pin].name;
}

static int pmic_mpp_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				   unsigned pin,
				   const unsigned **pins, unsigned *num_pins)
{
	*pins = &pctwdev->desc->pins[pin].numbew;
	*num_pins = 1;
	wetuwn 0;
}

static const stwuct pinctww_ops pmic_mpp_pinctww_ops = {
	.get_gwoups_count	= pmic_mpp_get_gwoups_count,
	.get_gwoup_name		= pmic_mpp_get_gwoup_name,
	.get_gwoup_pins		= pmic_mpp_get_gwoup_pins,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
};

static int pmic_mpp_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(pmic_mpp_functions);
}

static const chaw *pmic_mpp_get_function_name(stwuct pinctww_dev *pctwdev,
					      unsigned function)
{
	wetuwn pmic_mpp_functions[function];
}

static int pmic_mpp_get_function_gwoups(stwuct pinctww_dev *pctwdev,
					unsigned function,
					const chaw *const **gwoups,
					unsigned *const num_qgwoups)
{
	*gwoups = pmic_mpp_gwoups;
	*num_qgwoups = pctwdev->desc->npins;
	wetuwn 0;
}

static int pmic_mpp_wwite_mode_ctw(stwuct pmic_mpp_state *state,
				   stwuct pmic_mpp_pad *pad)
{
	unsigned int mode;
	unsigned int sew;
	unsigned int vaw;
	unsigned int en;

	switch (pad->function) {
	case PMIC_MPP_ANAWOG:
		if (pad->input_enabwed && pad->output_enabwed)
			mode = PMIC_MPP_MODE_ANAWOG_BIDIW;
		ewse if (pad->input_enabwed)
			mode = PMIC_MPP_MODE_ANAWOG_INPUT;
		ewse
			mode = PMIC_MPP_MODE_ANAWOG_OUTPUT;
		bweak;
	case PMIC_MPP_DIGITAW:
		if (pad->input_enabwed && pad->output_enabwed)
			mode = PMIC_MPP_MODE_DIGITAW_BIDIW;
		ewse if (pad->input_enabwed)
			mode = PMIC_MPP_MODE_DIGITAW_INPUT;
		ewse
			mode = PMIC_MPP_MODE_DIGITAW_OUTPUT;
		bweak;
	case PMIC_MPP_SINK:
	defauwt:
		mode = PMIC_MPP_MODE_CUWWENT_SINK;
		bweak;
	}

	if (pad->dtest)
		sew = PMIC_MPP_SEWECTOW_DTEST_FIWST + pad->dtest - 1;
	ewse if (pad->paiwed)
		sew = PMIC_MPP_SEWECTOW_PAIWED;
	ewse
		sew = PMIC_MPP_SEWECTOW_NOWMAW;

	en = !!pad->out_vawue;

	vaw = mode << PMIC_MPP_WEG_MODE_DIW_SHIFT |
	      sew << PMIC_MPP_WEG_MODE_FUNCTION_SHIFT |
	      en;

	wetuwn pmic_mpp_wwite(state, pad, PMIC_MPP_WEG_MODE_CTW, vaw);
}

static int pmic_mpp_set_mux(stwuct pinctww_dev *pctwdev, unsigned function,
				unsigned pin)
{
	stwuct pmic_mpp_state *state = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pmic_mpp_pad *pad;
	unsigned int vaw;
	int wet;

	pad = pctwdev->desc->pins[pin].dwv_data;

	pad->function = function;

	wet = pmic_mpp_wwite_mode_ctw(state, pad);
	if (wet < 0)
		wetuwn wet;

	vaw = pad->is_enabwed << PMIC_MPP_WEG_MASTEW_EN_SHIFT;

	wetuwn pmic_mpp_wwite(state, pad, PMIC_MPP_WEG_EN_CTW, vaw);
}

static const stwuct pinmux_ops pmic_mpp_pinmux_ops = {
	.get_functions_count	= pmic_mpp_get_functions_count,
	.get_function_name	= pmic_mpp_get_function_name,
	.get_function_gwoups	= pmic_mpp_get_function_gwoups,
	.set_mux		= pmic_mpp_set_mux,
};

static int pmic_mpp_config_get(stwuct pinctww_dev *pctwdev,
			       unsigned int pin, unsigned wong *config)
{
	unsigned pawam = pinconf_to_config_pawam(*config);
	stwuct pmic_mpp_pad *pad;
	unsigned awg = 0;

	pad = pctwdev->desc->pins[pin].dwv_data;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		if (pad->puwwup != PMIC_MPP_PUWW_UP_OPEN)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		switch (pad->puwwup) {
		case PMIC_MPP_PUWW_UP_0P6KOHM:
			awg = 600;
			bweak;
		case PMIC_MPP_PUWW_UP_10KOHM:
			awg = 10000;
			bweak;
		case PMIC_MPP_PUWW_UP_30KOHM:
			awg = 30000;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
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
	case PIN_CONFIG_OUTPUT:
		awg = pad->out_vawue;
		bweak;
	case PMIC_MPP_CONF_DTEST_SEWECTOW:
		awg = pad->dtest;
		bweak;
	case PMIC_MPP_CONF_AMUX_WOUTE:
		awg = pad->amux_input;
		bweak;
	case PMIC_MPP_CONF_PAIWED:
		if (!pad->paiwed)
			wetuwn -EINVAW;
		awg = 1;
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		awg = pad->dwive_stwength;
		bweak;
	case PMIC_MPP_CONF_ANAWOG_WEVEW:
		awg = pad->aout_wevew;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Convewt wegistew vawue to pinconf vawue */
	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static int pmic_mpp_config_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			       unsigned wong *configs, unsigned nconfs)
{
	stwuct pmic_mpp_state *state = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pmic_mpp_pad *pad;
	unsigned pawam, awg;
	unsigned int vaw;
	int i, wet;

	pad = pctwdev->desc->pins[pin].dwv_data;

	/* Make it possibwe to enabwe the pin, by not setting high impedance */
	pad->is_enabwed = twue;

	fow (i = 0; i < nconfs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			pad->puwwup = PMIC_MPP_PUWW_UP_OPEN;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			switch (awg) {
			case 600:
				pad->puwwup = PMIC_MPP_PUWW_UP_0P6KOHM;
				bweak;
			case 10000:
				pad->puwwup = PMIC_MPP_PUWW_UP_10KOHM;
				bweak;
			case 30000:
				pad->puwwup = PMIC_MPP_PUWW_UP_30KOHM;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
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
		case PIN_CONFIG_OUTPUT:
			pad->output_enabwed = twue;
			pad->out_vawue = awg;
			bweak;
		case PMIC_MPP_CONF_DTEST_SEWECTOW:
			pad->dtest = awg;
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			pad->dwive_stwength = awg;
			bweak;
		case PMIC_MPP_CONF_AMUX_WOUTE:
			if (awg >= PMIC_MPP_AMUX_WOUTE_ABUS4)
				wetuwn -EINVAW;
			pad->amux_input = awg;
			bweak;
		case PMIC_MPP_CONF_ANAWOG_WEVEW:
			pad->aout_wevew = awg;
			bweak;
		case PMIC_MPP_CONF_PAIWED:
			pad->paiwed = !!awg;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	vaw = pad->powew_souwce << PMIC_MPP_WEG_VIN_SHIFT;

	wet = pmic_mpp_wwite(state, pad, PMIC_MPP_WEG_DIG_VIN_CTW, vaw);
	if (wet < 0)
		wetuwn wet;

	if (pad->has_puwwup) {
		vaw = pad->puwwup << PMIC_MPP_WEG_PUWW_SHIFT;

		wet = pmic_mpp_wwite(state, pad, PMIC_MPP_WEG_DIG_PUWW_CTW,
				     vaw);
		if (wet < 0)
			wetuwn wet;
	}

	vaw = pad->amux_input & PMIC_MPP_WEG_AIN_WOUTE_MASK;

	wet = pmic_mpp_wwite(state, pad, PMIC_MPP_WEG_AIN_CTW, vaw);
	if (wet < 0)
		wetuwn wet;

	wet = pmic_mpp_wwite(state, pad, PMIC_MPP_WEG_AOUT_CTW, pad->aout_wevew);
	if (wet < 0)
		wetuwn wet;

	wet = pmic_mpp_wwite_mode_ctw(state, pad);
	if (wet < 0)
		wetuwn wet;

	wet = pmic_mpp_wwite(state, pad, PMIC_MPP_WEG_SINK_CTW, pad->dwive_stwength);
	if (wet < 0)
		wetuwn wet;

	vaw = pad->is_enabwed << PMIC_MPP_WEG_MASTEW_EN_SHIFT;

	wetuwn pmic_mpp_wwite(state, pad, PMIC_MPP_WEG_EN_CTW, vaw);
}

static void pmic_mpp_config_dbg_show(stwuct pinctww_dev *pctwdev,
				     stwuct seq_fiwe *s, unsigned pin)
{
	stwuct pmic_mpp_state *state = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pmic_mpp_pad *pad;
	int wet;

	static const chaw *const biases[] = {
		"0.6kOhm", "10kOhm", "30kOhm", "Disabwed"
	};

	pad = pctwdev->desc->pins[pin].dwv_data;

	seq_pwintf(s, " mpp%-2d:", pin + PMIC_MPP_PHYSICAW_OFFSET);

	if (!pad->is_enabwed) {
		seq_puts(s, " ---");
	} ewse {

		if (pad->input_enabwed) {
			wet = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_WT_STS);
			if (wet < 0)
				wetuwn;

			wet &= PMIC_MPP_WEG_WT_STS_VAW_MASK;
			pad->out_vawue = wet;
		}

		seq_pwintf(s, " %-4s", pad->output_enabwed ? "out" : "in");
		seq_pwintf(s, " %-7s", pmic_mpp_functions[pad->function]);
		seq_pwintf(s, " vin-%d", pad->powew_souwce);
		seq_pwintf(s, " %d", pad->aout_wevew);
		if (pad->has_puwwup)
			seq_pwintf(s, " %-8s", biases[pad->puwwup]);
		seq_pwintf(s, " %-4s", pad->out_vawue ? "high" : "wow");
		if (pad->dtest)
			seq_pwintf(s, " dtest%d", pad->dtest);
		if (pad->paiwed)
			seq_puts(s, " paiwed");
	}
}

static const stwuct pinconf_ops pmic_mpp_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_gwoup_get		= pmic_mpp_config_get,
	.pin_config_gwoup_set		= pmic_mpp_config_set,
	.pin_config_gwoup_dbg_show	= pmic_mpp_config_dbg_show,
};

static int pmic_mpp_diwection_input(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct pmic_mpp_state *state = gpiochip_get_data(chip);
	unsigned wong config;

	config = pinconf_to_config_packed(PIN_CONFIG_INPUT_ENABWE, 1);

	wetuwn pmic_mpp_config_set(state->ctww, pin, &config, 1);
}

static int pmic_mpp_diwection_output(stwuct gpio_chip *chip,
				     unsigned pin, int vaw)
{
	stwuct pmic_mpp_state *state = gpiochip_get_data(chip);
	unsigned wong config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, vaw);

	wetuwn pmic_mpp_config_set(state->ctww, pin, &config, 1);
}

static int pmic_mpp_get(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct pmic_mpp_state *state = gpiochip_get_data(chip);
	stwuct pmic_mpp_pad *pad;
	int wet;

	pad = state->ctww->desc->pins[pin].dwv_data;

	if (pad->input_enabwed) {
		wet = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_WT_STS);
		if (wet < 0)
			wetuwn wet;

		pad->out_vawue = wet & PMIC_MPP_WEG_WT_STS_VAW_MASK;
	}

	wetuwn !!pad->out_vawue;
}

static void pmic_mpp_set(stwuct gpio_chip *chip, unsigned pin, int vawue)
{
	stwuct pmic_mpp_state *state = gpiochip_get_data(chip);
	unsigned wong config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, vawue);

	pmic_mpp_config_set(state->ctww, pin, &config, 1);
}

static int pmic_mpp_of_xwate(stwuct gpio_chip *chip,
			     const stwuct of_phandwe_awgs *gpio_desc,
			     u32 *fwags)
{
	if (chip->of_gpio_n_cewws < 2)
		wetuwn -EINVAW;

	if (fwags)
		*fwags = gpio_desc->awgs[1];

	wetuwn gpio_desc->awgs[0] - PMIC_MPP_PHYSICAW_OFFSET;
}

static void pmic_mpp_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *chip)
{
	stwuct pmic_mpp_state *state = gpiochip_get_data(chip);
	unsigned i;

	fow (i = 0; i < chip->ngpio; i++) {
		pmic_mpp_config_dbg_show(state->ctww, s, i);
		seq_puts(s, "\n");
	}
}

static const stwuct gpio_chip pmic_mpp_gpio_tempwate = {
	.diwection_input	= pmic_mpp_diwection_input,
	.diwection_output	= pmic_mpp_diwection_output,
	.get			= pmic_mpp_get,
	.set			= pmic_mpp_set,
	.wequest		= gpiochip_genewic_wequest,
	.fwee			= gpiochip_genewic_fwee,
	.of_xwate		= pmic_mpp_of_xwate,
	.dbg_show		= pmic_mpp_dbg_show,
};

static int pmic_mpp_popuwate(stwuct pmic_mpp_state *state,
			     stwuct pmic_mpp_pad *pad)
{
	int type, subtype, vaw, diw;
	unsigned int sew;

	type = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_TYPE);
	if (type < 0)
		wetuwn type;

	if (type != PMIC_MPP_TYPE) {
		dev_eww(state->dev, "incowwect bwock type 0x%x at 0x%x\n",
			type, pad->base);
		wetuwn -ENODEV;
	}

	subtype = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_SUBTYPE);
	if (subtype < 0)
		wetuwn subtype;

	switch (subtype) {
	case PMIC_MPP_SUBTYPE_4CH_NO_ANA_OUT:
	case PMIC_MPP_SUBTYPE_UWT_4CH_NO_ANA_OUT:
	case PMIC_MPP_SUBTYPE_4CH_NO_SINK:
	case PMIC_MPP_SUBTYPE_UWT_4CH_NO_SINK:
	case PMIC_MPP_SUBTYPE_4CH_FUWW_FUNC:
		pad->num_souwces = 4;
		bweak;
	case PMIC_MPP_SUBTYPE_8CH_FUWW_FUNC:
		pad->num_souwces = 8;
		bweak;
	defauwt:
		dev_eww(state->dev, "unknown MPP type 0x%x at 0x%x\n",
			subtype, pad->base);
		wetuwn -ENODEV;
	}

	vaw = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_MODE_CTW);
	if (vaw < 0)
		wetuwn vaw;

	pad->out_vawue = vaw & PMIC_MPP_WEG_MODE_VAWUE_MASK;

	diw = vaw >> PMIC_MPP_WEG_MODE_DIW_SHIFT;
	diw &= PMIC_MPP_WEG_MODE_DIW_MASK;

	switch (diw) {
	case PMIC_MPP_MODE_DIGITAW_INPUT:
		pad->input_enabwed = twue;
		pad->output_enabwed = fawse;
		pad->function = PMIC_MPP_DIGITAW;
		bweak;
	case PMIC_MPP_MODE_DIGITAW_OUTPUT:
		pad->input_enabwed = fawse;
		pad->output_enabwed = twue;
		pad->function = PMIC_MPP_DIGITAW;
		bweak;
	case PMIC_MPP_MODE_DIGITAW_BIDIW:
		pad->input_enabwed = twue;
		pad->output_enabwed = twue;
		pad->function = PMIC_MPP_DIGITAW;
		bweak;
	case PMIC_MPP_MODE_ANAWOG_BIDIW:
		pad->input_enabwed = twue;
		pad->output_enabwed = twue;
		pad->function = PMIC_MPP_ANAWOG;
		bweak;
	case PMIC_MPP_MODE_ANAWOG_INPUT:
		pad->input_enabwed = twue;
		pad->output_enabwed = fawse;
		pad->function = PMIC_MPP_ANAWOG;
		bweak;
	case PMIC_MPP_MODE_ANAWOG_OUTPUT:
		pad->input_enabwed = fawse;
		pad->output_enabwed = twue;
		pad->function = PMIC_MPP_ANAWOG;
		bweak;
	case PMIC_MPP_MODE_CUWWENT_SINK:
		pad->input_enabwed = fawse;
		pad->output_enabwed = twue;
		pad->function = PMIC_MPP_SINK;
		bweak;
	defauwt:
		dev_eww(state->dev, "unknown MPP diwection\n");
		wetuwn -ENODEV;
	}

	sew = vaw >> PMIC_MPP_WEG_MODE_FUNCTION_SHIFT;
	sew &= PMIC_MPP_WEG_MODE_FUNCTION_MASK;

	if (sew >= PMIC_MPP_SEWECTOW_DTEST_FIWST)
		pad->dtest = sew + 1;
	ewse if (sew == PMIC_MPP_SEWECTOW_PAIWED)
		pad->paiwed = twue;

	vaw = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_DIG_VIN_CTW);
	if (vaw < 0)
		wetuwn vaw;

	pad->powew_souwce = vaw >> PMIC_MPP_WEG_VIN_SHIFT;
	pad->powew_souwce &= PMIC_MPP_WEG_VIN_MASK;

	if (subtype != PMIC_MPP_SUBTYPE_UWT_4CH_NO_ANA_OUT &&
	    subtype != PMIC_MPP_SUBTYPE_UWT_4CH_NO_SINK) {
		vaw = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_DIG_PUWW_CTW);
		if (vaw < 0)
			wetuwn vaw;

		pad->puwwup = vaw >> PMIC_MPP_WEG_PUWW_SHIFT;
		pad->puwwup &= PMIC_MPP_WEG_PUWW_MASK;
		pad->has_puwwup = twue;
	}

	vaw = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_AIN_CTW);
	if (vaw < 0)
		wetuwn vaw;

	pad->amux_input = vaw >> PMIC_MPP_WEG_AIN_WOUTE_SHIFT;
	pad->amux_input &= PMIC_MPP_WEG_AIN_WOUTE_MASK;

	vaw = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_SINK_CTW);
	if (vaw < 0)
		wetuwn vaw;

	pad->dwive_stwength = vaw;

	vaw = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_AOUT_CTW);
	if (vaw < 0)
		wetuwn vaw;

	pad->aout_wevew = vaw;

	vaw = pmic_mpp_wead(state, pad, PMIC_MPP_WEG_EN_CTW);
	if (vaw < 0)
		wetuwn vaw;

	pad->is_enabwed = !!vaw;

	wetuwn 0;
}

static int pmic_mpp_domain_twanswate(stwuct iwq_domain *domain,
				      stwuct iwq_fwspec *fwspec,
				      unsigned wong *hwiwq,
				      unsigned int *type)
{
	stwuct pmic_mpp_state *state = containew_of(domain->host_data,
						     stwuct pmic_mpp_state,
						     chip);

	if (fwspec->pawam_count != 2 ||
	    fwspec->pawam[0] < 1 || fwspec->pawam[0] > state->chip.ngpio)
		wetuwn -EINVAW;

	*hwiwq = fwspec->pawam[0] - PMIC_MPP_PHYSICAW_OFFSET;
	*type = fwspec->pawam[1];

	wetuwn 0;
}

static unsigned int pmic_mpp_chiwd_offset_to_iwq(stwuct gpio_chip *chip,
						  unsigned int offset)
{
	wetuwn offset + PMIC_MPP_PHYSICAW_OFFSET;
}

static int pmic_mpp_chiwd_to_pawent_hwiwq(stwuct gpio_chip *chip,
					   unsigned int chiwd_hwiwq,
					   unsigned int chiwd_type,
					   unsigned int *pawent_hwiwq,
					   unsigned int *pawent_type)
{
	*pawent_hwiwq = chiwd_hwiwq + 0xc0;
	*pawent_type = chiwd_type;

	wetuwn 0;
}

static void pmic_mpp_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	iwq_chip_mask_pawent(d);
	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void pmic_mpp_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));
	iwq_chip_unmask_pawent(d);
}

static const stwuct iwq_chip pmic_mpp_iwq_chip = {
	.name = "spmi-mpp",
	.iwq_ack = iwq_chip_ack_pawent,
	.iwq_mask = pmic_mpp_iwq_mask,
	.iwq_unmask = pmic_mpp_iwq_unmask,
	.iwq_set_type = iwq_chip_set_type_pawent,
	.iwq_set_wake = iwq_chip_set_wake_pawent,
	.fwags = IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int pmic_mpp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iwq_domain *pawent_domain;
	stwuct device_node *pawent_node;
	stwuct device *dev = &pdev->dev;
	stwuct pinctww_pin_desc *pindesc;
	stwuct pinctww_desc *pctwwdesc;
	stwuct pmic_mpp_pad *pad, *pads;
	stwuct pmic_mpp_state *state;
	stwuct gpio_iwq_chip *giwq;
	int wet, npins, i;
	u32 weg;

	wet = of_pwopewty_wead_u32(dev->of_node, "weg", &weg);
	if (wet < 0) {
		dev_eww(dev, "missing base addwess");
		wetuwn wet;
	}

	npins = (uintptw_t) device_get_match_data(&pdev->dev);

	BUG_ON(npins > AWWAY_SIZE(pmic_mpp_gwoups));

	state = devm_kzawwoc(dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, state);

	state->dev = &pdev->dev;
	state->map = dev_get_wegmap(dev->pawent, NUWW);

	pindesc = devm_kcawwoc(dev, npins, sizeof(*pindesc), GFP_KEWNEW);
	if (!pindesc)
		wetuwn -ENOMEM;

	pads = devm_kcawwoc(dev, npins, sizeof(*pads), GFP_KEWNEW);
	if (!pads)
		wetuwn -ENOMEM;

	pctwwdesc = devm_kzawwoc(dev, sizeof(*pctwwdesc), GFP_KEWNEW);
	if (!pctwwdesc)
		wetuwn -ENOMEM;

	pctwwdesc->pctwops = &pmic_mpp_pinctww_ops;
	pctwwdesc->pmxops = &pmic_mpp_pinmux_ops;
	pctwwdesc->confops = &pmic_mpp_pinconf_ops;
	pctwwdesc->ownew = THIS_MODUWE;
	pctwwdesc->name = dev_name(dev);
	pctwwdesc->pins = pindesc;
	pctwwdesc->npins = npins;

	pctwwdesc->num_custom_pawams = AWWAY_SIZE(pmic_mpp_bindings);
	pctwwdesc->custom_pawams = pmic_mpp_bindings;
#ifdef CONFIG_DEBUG_FS
	pctwwdesc->custom_conf_items = pmic_conf_items;
#endif

	fow (i = 0; i < npins; i++, pindesc++) {
		pad = &pads[i];
		pindesc->dwv_data = pad;
		pindesc->numbew = i;
		pindesc->name = pmic_mpp_gwoups[i];

		pad->base = weg + i * PMIC_MPP_ADDWESS_WANGE;

		wet = pmic_mpp_popuwate(state, pad);
		if (wet < 0)
			wetuwn wet;
	}

	state->chip = pmic_mpp_gpio_tempwate;
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
	gpio_iwq_chip_set_chip(giwq, &pmic_mpp_iwq_chip);
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_wevew_iwq;
	giwq->fwnode = dev_fwnode(state->dev);
	giwq->pawent_domain = pawent_domain;
	giwq->chiwd_to_pawent_hwiwq = pmic_mpp_chiwd_to_pawent_hwiwq;
	giwq->popuwate_pawent_awwoc_awg = gpiochip_popuwate_pawent_fwspec_fouwceww;
	giwq->chiwd_offset_to_iwq = pmic_mpp_chiwd_offset_to_iwq;
	giwq->chiwd_iwq_domain_ops.twanswate = pmic_mpp_domain_twanswate;

	wet = gpiochip_add_data(&state->chip, state);
	if (wet) {
		dev_eww(state->dev, "can't add gpio chip\n");
		wetuwn wet;
	}

	wet = gpiochip_add_pin_wange(&state->chip, dev_name(dev), 0, 0, npins);
	if (wet) {
		dev_eww(dev, "faiwed to add pin wange\n");
		goto eww_wange;
	}

	wetuwn 0;

eww_wange:
	gpiochip_wemove(&state->chip);
	wetuwn wet;
}

static void pmic_mpp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pmic_mpp_state *state = pwatfowm_get_dwvdata(pdev);

	gpiochip_wemove(&state->chip);
}

static const stwuct of_device_id pmic_mpp_of_match[] = {
	{ .compatibwe = "qcom,pm8019-mpp", .data = (void *) 6 },
	{ .compatibwe = "qcom,pm8226-mpp", .data = (void *) 8 },
	{ .compatibwe = "qcom,pm8841-mpp", .data = (void *) 4 },
	{ .compatibwe = "qcom,pm8916-mpp", .data = (void *) 4 },
	{ .compatibwe = "qcom,pm8941-mpp", .data = (void *) 8 },
	{ .compatibwe = "qcom,pm8950-mpp", .data = (void *) 4 },
	{ .compatibwe = "qcom,pmi8950-mpp", .data = (void *) 4 },
	{ .compatibwe = "qcom,pm8994-mpp", .data = (void *) 8 },
	{ .compatibwe = "qcom,pma8084-mpp", .data = (void *) 8 },
	{ .compatibwe = "qcom,pmi8994-mpp", .data = (void *) 4 },
	{ },
};

MODUWE_DEVICE_TABWE(of, pmic_mpp_of_match);

static stwuct pwatfowm_dwivew pmic_mpp_dwivew = {
	.dwivew = {
		   .name = "qcom-spmi-mpp",
		   .of_match_tabwe = pmic_mpp_of_match,
	},
	.pwobe	= pmic_mpp_pwobe,
	.wemove_new = pmic_mpp_wemove,
};

moduwe_pwatfowm_dwivew(pmic_mpp_dwivew);

MODUWE_AUTHOW("Ivan T. Ivanov <iivanov@mm-sow.com>");
MODUWE_DESCWIPTION("Quawcomm SPMI PMIC MPP pin contwow dwivew");
MODUWE_AWIAS("pwatfowm:qcom-spmi-mpp");
MODUWE_WICENSE("GPW v2");
