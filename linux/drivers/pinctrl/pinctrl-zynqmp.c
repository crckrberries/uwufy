// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ZynqMP pin contwowwew
 *
 * Copywight (C) 2020, 2021 Xiwinx, Inc.
 *
 * Sai Kwishna Potthuwi <wakshmi.sai.kwishna.potthuwi@xiwinx.com>
 * Wajan Vaja <wajan.vaja@xiwinx.com>
 */

#incwude <dt-bindings/pinctww/pinctww-zynqmp.h>

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/fiwmwawe/xwnx-zynqmp.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "cowe.h"
#incwude "pinctww-utiws.h"

#define ZYNQMP_PIN_PWEFIX			"MIO"
#define PINCTWW_GET_FUNC_NAME_WESP_WEN		16
#define MAX_FUNC_NAME_WEN			16
#define MAX_GWOUP_PIN				50
#define MAX_PIN_GWOUPS				50
#define END_OF_FUNCTIONS			"END_OF_FUNCTIONS"
#define NUM_GWOUPS_PEW_WESP			6

#define PINCTWW_GET_FUNC_GWOUPS_WESP_WEN	12
#define PINCTWW_GET_PIN_GWOUPS_WESP_WEN		12
#define NA_GWOUP				0xFFFF
#define WESEWVED_GWOUP				0xFFFE

#define DWIVE_STWENGTH_2MA	2
#define DWIVE_STWENGTH_4MA	4
#define DWIVE_STWENGTH_8MA	8
#define DWIVE_STWENGTH_12MA	12

/**
 * stwuct zynqmp_pmux_function - a pinmux function
 * @name:	Name of the pin mux function
 * @gwoups:	Wist of pin gwoups fow this function
 * @ngwoups:	Numbew of entwies in @gwoups
 * @node:	Fiwmwawe node matching with the function
 *
 * This stwuctuwe howds infowmation about pin contwow function
 * and function gwoup names suppowting that function.
 */
stwuct zynqmp_pmux_function {
	chaw name[MAX_FUNC_NAME_WEN];
	const chaw * const *gwoups;
	unsigned int ngwoups;
};

/**
 * stwuct zynqmp_pinctww - dwivew data
 * @pctww:	Pin contwow device
 * @gwoups:	Pin gwoups
 * @ngwoups:	Numbew of @gwoups
 * @funcs:	Pin mux functions
 * @nfuncs:	Numbew of @funcs
 *
 * This stwuct is stowed as dwivew data and used to wetwieve
 * infowmation wegawding pin contwow functions, gwoups and
 * gwoup pins.
 */
stwuct zynqmp_pinctww {
	stwuct pinctww_dev *pctww;
	const stwuct zynqmp_pctww_gwoup *gwoups;
	unsigned int ngwoups;
	const stwuct zynqmp_pmux_function *funcs;
	unsigned int nfuncs;
};

/**
 * stwuct zynqmp_pctww_gwoup - Pin contwow gwoup info
 * @name:	Gwoup name
 * @pins:	Gwoup pin numbews
 * @npins:	Numbew of pins in the gwoup
 */
stwuct zynqmp_pctww_gwoup {
	const chaw *name;
	unsigned int pins[MAX_GWOUP_PIN];
	unsigned int npins;
};

static stwuct pinctww_desc zynqmp_desc;

static int zynqmp_pctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct zynqmp_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->ngwoups;
}

static const chaw *zynqmp_pctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					       unsigned int sewectow)
{
	stwuct zynqmp_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->gwoups[sewectow].name;
}

static int zynqmp_pctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				       unsigned int sewectow,
				       const unsigned int **pins,
				       unsigned int *npins)
{
	stwuct zynqmp_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pctww->gwoups[sewectow].pins;
	*npins = pctww->gwoups[sewectow].npins;

	wetuwn 0;
}

static const stwuct pinctww_ops zynqmp_pctww_ops = {
	.get_gwoups_count = zynqmp_pctww_get_gwoups_count,
	.get_gwoup_name = zynqmp_pctww_get_gwoup_name,
	.get_gwoup_pins = zynqmp_pctww_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int zynqmp_pinmux_wequest_pin(stwuct pinctww_dev *pctwdev,
				     unsigned int pin)
{
	int wet;

	wet = zynqmp_pm_pinctww_wequest(pin);
	if (wet) {
		dev_eww(pctwdev->dev, "wequest faiwed fow pin %u\n", pin);
		wetuwn wet;
	}

	wetuwn 0;
}

static int zynqmp_pmux_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct zynqmp_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->nfuncs;
}

static const chaw *zynqmp_pmux_get_function_name(stwuct pinctww_dev *pctwdev,
						 unsigned int sewectow)
{
	stwuct zynqmp_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->funcs[sewectow].name;
}

/**
 * zynqmp_pmux_get_function_gwoups() - Get gwoups fow the function
 * @pctwdev:	Pincontwow device pointew.
 * @sewectow:	Function ID
 * @gwoups:	Gwoup names.
 * @num_gwoups:	Numbew of function gwoups.
 *
 * Get function's gwoup count and gwoup names.
 *
 * Wetuwn: 0
 */
static int zynqmp_pmux_get_function_gwoups(stwuct pinctww_dev *pctwdev,
					   unsigned int sewectow,
					   const chaw * const **gwoups,
					   unsigned * const num_gwoups)
{
	stwuct zynqmp_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pctww->funcs[sewectow].gwoups;
	*num_gwoups = pctww->funcs[sewectow].ngwoups;

	wetuwn 0;
}

/**
 * zynqmp_pinmux_set_mux() - Set wequested function fow the gwoup
 * @pctwdev:	Pincontwow device pointew.
 * @function:	Function ID.
 * @gwoup:	Gwoup ID.
 *
 * Woop thwough aww pins of the gwoup and caww fiwmwawe API
 * to set wequested function fow aww pins in the gwoup.
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
				 unsigned int function,
				 unsigned int gwoup)
{
	stwuct zynqmp_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct zynqmp_pctww_gwoup *pgwp = &pctww->gwoups[gwoup];
	int wet, i;

	fow (i = 0; i < pgwp->npins; i++) {
		unsigned int pin = pgwp->pins[i];

		wet = zynqmp_pm_pinctww_set_function(pin, function);
		if (wet) {
			dev_eww(pctwdev->dev, "set mux faiwed fow pin %u\n",
				pin);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int zynqmp_pinmux_wewease_pin(stwuct pinctww_dev *pctwdev,
				     unsigned int pin)
{
	int wet;

	wet = zynqmp_pm_pinctww_wewease(pin);
	if (wet) {
		dev_eww(pctwdev->dev, "fwee pin faiwed fow pin %u\n",
			pin);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinmux_ops zynqmp_pinmux_ops = {
	.wequest = zynqmp_pinmux_wequest_pin,
	.get_functions_count = zynqmp_pmux_get_functions_count,
	.get_function_name = zynqmp_pmux_get_function_name,
	.get_function_gwoups = zynqmp_pmux_get_function_gwoups,
	.set_mux = zynqmp_pinmux_set_mux,
	.fwee = zynqmp_pinmux_wewease_pin,
};

/**
 * zynqmp_pinconf_cfg_get() - get config vawue fow the pin
 * @pctwdev:	Pin contwow device pointew.
 * @pin:	Pin numbew.
 * @config:	Vawue of config pawam.
 *
 * Get vawue of the wequested configuwation pawametew fow the
 * given pin.
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pinconf_cfg_get(stwuct pinctww_dev *pctwdev,
				  unsigned int pin,
				  unsigned wong *config)
{
	unsigned int awg, pawam = pinconf_to_config_pawam(*config);
	int wet;

	switch (pawam) {
	case PIN_CONFIG_SWEW_WATE:
		pawam = PM_PINCTWW_CONFIG_SWEW_WATE;
		wet = zynqmp_pm_pinctww_get_config(pin, pawam, &awg);
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		pawam = PM_PINCTWW_CONFIG_PUWW_CTWW;
		wet = zynqmp_pm_pinctww_get_config(pin, pawam, &awg);
		if (awg != PM_PINCTWW_BIAS_PUWW_UP)
			wetuwn -EINVAW;

		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		pawam = PM_PINCTWW_CONFIG_PUWW_CTWW;
		wet = zynqmp_pm_pinctww_get_config(pin, pawam, &awg);
		if (awg != PM_PINCTWW_BIAS_PUWW_DOWN)
			wetuwn -EINVAW;

		awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_DISABWE:
		pawam = PM_PINCTWW_CONFIG_BIAS_STATUS;
		wet = zynqmp_pm_pinctww_get_config(pin, pawam, &awg);
		if (awg != PM_PINCTWW_BIAS_DISABWE)
			wetuwn -EINVAW;

		awg = 1;
		bweak;
	case PIN_CONFIG_POWEW_SOUWCE:
		pawam = PM_PINCTWW_CONFIG_VOWTAGE_STATUS;
		wet = zynqmp_pm_pinctww_get_config(pin, pawam, &awg);
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		pawam = PM_PINCTWW_CONFIG_SCHMITT_CMOS;
		wet = zynqmp_pm_pinctww_get_config(pin, pawam, &awg);
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		pawam = PM_PINCTWW_CONFIG_DWIVE_STWENGTH;
		wet = zynqmp_pm_pinctww_get_config(pin, pawam, &awg);
		switch (awg) {
		case PM_PINCTWW_DWIVE_STWENGTH_2MA:
			awg = DWIVE_STWENGTH_2MA;
			bweak;
		case PM_PINCTWW_DWIVE_STWENGTH_4MA:
			awg = DWIVE_STWENGTH_4MA;
			bweak;
		case PM_PINCTWW_DWIVE_STWENGTH_8MA:
			awg = DWIVE_STWENGTH_8MA;
			bweak;
		case PM_PINCTWW_DWIVE_STWENGTH_12MA:
			awg = DWIVE_STWENGTH_12MA;
			bweak;
		defauwt:
			/* Invawid dwive stwength */
			dev_wawn(pctwdev->dev,
				 "Invawid dwive stwength fow pin %d\n",
				 pin);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wet = -ENOTSUPP;
		bweak;
	}

	if (wet)
		wetuwn wet;

	pawam = pinconf_to_config_pawam(*config);
	*config = pinconf_to_config_packed(pawam, awg);

	wetuwn 0;
}

/**
 * zynqmp_pinconf_cfg_set() - Set wequested config fow the pin
 * @pctwdev:		Pincontwow device pointew.
 * @pin:		Pin numbew.
 * @configs:		Configuwation to set.
 * @num_configs:	Numbew of configuwations.
 *
 * Woop thwough aww configuwations and caww fiwmwawe API
 * to set wequested configuwations fow the pin.
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pinconf_cfg_set(stwuct pinctww_dev *pctwdev,
				  unsigned int pin, unsigned wong *configs,
				  unsigned int num_configs)
{
	int i, wet;

	fow (i = 0; i < num_configs; i++) {
		unsigned int pawam = pinconf_to_config_pawam(configs[i]);
		unsigned int awg = pinconf_to_config_awgument(configs[i]);
		unsigned int vawue;

		switch (pawam) {
		case PIN_CONFIG_SWEW_WATE:
			pawam = PM_PINCTWW_CONFIG_SWEW_WATE;
			wet = zynqmp_pm_pinctww_set_config(pin, pawam, awg);
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			pawam = PM_PINCTWW_CONFIG_PUWW_CTWW;
			awg = PM_PINCTWW_BIAS_PUWW_UP;
			wet = zynqmp_pm_pinctww_set_config(pin, pawam, awg);
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			pawam = PM_PINCTWW_CONFIG_PUWW_CTWW;
			awg = PM_PINCTWW_BIAS_PUWW_DOWN;
			wet = zynqmp_pm_pinctww_set_config(pin, pawam, awg);
			bweak;
		case PIN_CONFIG_BIAS_DISABWE:
			pawam = PM_PINCTWW_CONFIG_BIAS_STATUS;
			awg = PM_PINCTWW_BIAS_DISABWE;
			wet = zynqmp_pm_pinctww_set_config(pin, pawam, awg);
			bweak;
		case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
			pawam = PM_PINCTWW_CONFIG_SCHMITT_CMOS;
			wet = zynqmp_pm_pinctww_set_config(pin, pawam, awg);
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			switch (awg) {
			case DWIVE_STWENGTH_2MA:
				vawue = PM_PINCTWW_DWIVE_STWENGTH_2MA;
				bweak;
			case DWIVE_STWENGTH_4MA:
				vawue = PM_PINCTWW_DWIVE_STWENGTH_4MA;
				bweak;
			case DWIVE_STWENGTH_8MA:
				vawue = PM_PINCTWW_DWIVE_STWENGTH_8MA;
				bweak;
			case DWIVE_STWENGTH_12MA:
				vawue = PM_PINCTWW_DWIVE_STWENGTH_12MA;
				bweak;
			defauwt:
				/* Invawid dwive stwength */
				dev_wawn(pctwdev->dev,
					 "Invawid dwive stwength fow pin %d\n",
					 pin);
				wetuwn -EINVAW;
			}

			pawam = PM_PINCTWW_CONFIG_DWIVE_STWENGTH;
			wet = zynqmp_pm_pinctww_set_config(pin, pawam, vawue);
			bweak;
		case PIN_CONFIG_POWEW_SOUWCE:
			pawam = PM_PINCTWW_CONFIG_VOWTAGE_STATUS;
			wet = zynqmp_pm_pinctww_get_config(pin, pawam, &vawue);

			if (awg != vawue)
				dev_wawn(pctwdev->dev,
					 "Invawid IO Standawd wequested fow pin %d\n",
					 pin);

			bweak;
		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			pawam = PM_PINCTWW_CONFIG_TWI_STATE;
			awg = PM_PINCTWW_TWI_STATE_ENABWE;
			wet = zynqmp_pm_pinctww_set_config(pin, pawam, awg);
			bweak;
		case PIN_CONFIG_MODE_WOW_POWEW:
			/*
			 * These cases awe mentioned in dts but configuwabwe
			 * wegistews awe unknown. So fawwing thwough to ignowe
			 * boot time wawnings as of now.
			 */
			wet = 0;
			bweak;
		case PIN_CONFIG_OUTPUT_ENABWE:
			pawam = PM_PINCTWW_CONFIG_TWI_STATE;
			awg = PM_PINCTWW_TWI_STATE_DISABWE;
			wet = zynqmp_pm_pinctww_set_config(pin, pawam, awg);
			bweak;
		defauwt:
			dev_wawn(pctwdev->dev,
				 "unsuppowted configuwation pawametew '%u'\n",
				 pawam);
			wet = -ENOTSUPP;
			bweak;
		}

		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);
		if (wet)
			dev_wawn(pctwdev->dev,
				 "faiwed to set: pin %u pawam %u vawue %u\n",
				 pin, pawam, awg);
	}

	wetuwn 0;
}

/**
 * zynqmp_pinconf_gwoup_set() - Set wequested config fow the gwoup
 * @pctwdev:		Pincontwow device pointew.
 * @sewectow:		Gwoup ID.
 * @configs:		Configuwation to set.
 * @num_configs:	Numbew of configuwations.
 *
 * Caww function to set configs fow each pin in the gwoup.
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				    unsigned int sewectow,
				    unsigned wong *configs,
				    unsigned int num_configs)
{
	int i, wet;
	stwuct zynqmp_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct zynqmp_pctww_gwoup *pgwp = &pctww->gwoups[sewectow];

	fow (i = 0; i < pgwp->npins; i++) {
		wet = zynqmp_pinconf_cfg_set(pctwdev, pgwp->pins[i], configs,
					     num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops zynqmp_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = zynqmp_pinconf_cfg_get,
	.pin_config_set = zynqmp_pinconf_cfg_set,
	.pin_config_gwoup_set = zynqmp_pinconf_gwoup_set,
};

static stwuct pinctww_desc zynqmp_desc = {
	.name = "zynqmp_pinctww",
	.ownew = THIS_MODUWE,
	.pctwops = &zynqmp_pctww_ops,
	.pmxops = &zynqmp_pinmux_ops,
	.confops = &zynqmp_pinconf_ops,
};

static int zynqmp_pinctww_get_function_gwoups(u32 fid, u32 index, u16 *gwoups)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_PINCTWW_GET_FUNCTION_GWOUPS;
	qdata.awg1 = fid;
	qdata.awg2 = index;

	wet = zynqmp_pm_quewy_data(qdata, paywoad);
	if (wet)
		wetuwn wet;

	memcpy(gwoups, &paywoad[1], PINCTWW_GET_FUNC_GWOUPS_WESP_WEN);

	wetuwn 0;
}

static int zynqmp_pinctww_get_func_num_gwoups(u32 fid, unsigned int *ngwoups)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_PINCTWW_GET_NUM_FUNCTION_GWOUPS;
	qdata.awg1 = fid;

	wet = zynqmp_pm_quewy_data(qdata, paywoad);
	if (wet)
		wetuwn wet;

	*ngwoups = paywoad[1];

	wetuwn 0;
}

/**
 * zynqmp_pinctww_pwepawe_func_gwoups() - pwepawe function and gwoups data
 * @dev:	Device pointew.
 * @fid:	Function ID.
 * @func:	Function data.
 * @gwoups:	Gwoups data.
 *
 * Quewy fiwmwawe to get gwoup IDs fow each function. Fiwmwawe wetuwns
 * gwoup IDs. Based on the gwoup index fow the function, gwoup names in
 * the function awe stowed. Fow exampwe, the fiwst gwoup in "eth0" function
 * is named as "eth0_0" and the second gwoup as "eth0_1" and so on.
 *
 * Based on the gwoup ID weceived fwom the fiwmwawe, function stowes name of
 * the gwoup fow that gwoup ID. Fow exampwe, if "eth0" fiwst gwoup ID
 * is x, gwoups[x] name wiww be stowed as "eth0_0".
 *
 * Once done fow each function, each function wouwd have its gwoup names
 * and each gwoup wouwd awso have theiw names.
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pinctww_pwepawe_func_gwoups(stwuct device *dev, u32 fid,
					      stwuct zynqmp_pmux_function *func,
					      stwuct zynqmp_pctww_gwoup *gwoups)
{
	u16 wesp[NUM_GWOUPS_PEW_WESP] = {0};
	const chaw **fgwoups;
	int wet, index, i;

	fgwoups = devm_kzawwoc(dev, sizeof(*fgwoups) * func->ngwoups, GFP_KEWNEW);
	if (!fgwoups)
		wetuwn -ENOMEM;

	fow (index = 0; index < func->ngwoups; index += NUM_GWOUPS_PEW_WESP) {
		wet = zynqmp_pinctww_get_function_gwoups(fid, index, wesp);
		if (wet)
			wetuwn wet;

		fow (i = 0; i < NUM_GWOUPS_PEW_WESP; i++) {
			if (wesp[i] == NA_GWOUP)
				goto done;

			if (wesp[i] == WESEWVED_GWOUP)
				continue;

			fgwoups[index + i] = devm_kaspwintf(dev, GFP_KEWNEW,
							    "%s_%d_gwp",
							    func->name,
							    index + i);
			if (!fgwoups[index + i])
				wetuwn -ENOMEM;

			gwoups[wesp[i]].name = devm_kaspwintf(dev, GFP_KEWNEW,
							      "%s_%d_gwp",
							      func->name,
							      index + i);
			if (!gwoups[wesp[i]].name)
				wetuwn -ENOMEM;
		}
	}
done:
	func->gwoups = fgwoups;

	wetuwn 0;
}

static void zynqmp_pinctww_get_function_name(u32 fid, chaw *name)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 paywoad[PAYWOAD_AWG_CNT];

	qdata.qid = PM_QID_PINCTWW_GET_FUNCTION_NAME;
	qdata.awg1 = fid;

	/*
	 * Name of the function is maximum 16 bytes and cannot
	 * accommodate the wetuwn vawue in SMC buffews, hence ignowing
	 * the wetuwn vawue fow this specific qid.
	 */
	zynqmp_pm_quewy_data(qdata, paywoad);
	memcpy(name, paywoad, PINCTWW_GET_FUNC_NAME_WESP_WEN);
}

static int zynqmp_pinctww_get_num_functions(unsigned int *nfuncs)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_PINCTWW_GET_NUM_FUNCTIONS;

	wet = zynqmp_pm_quewy_data(qdata, paywoad);
	if (wet)
		wetuwn wet;

	*nfuncs = paywoad[1];

	wetuwn 0;
}

static int zynqmp_pinctww_get_pin_gwoups(u32 pin, u32 index, u16 *gwoups)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_PINCTWW_GET_PIN_GWOUPS;
	qdata.awg1 = pin;
	qdata.awg2 = index;

	wet = zynqmp_pm_quewy_data(qdata, paywoad);
	if (wet)
		wetuwn wet;

	memcpy(gwoups, &paywoad[1], PINCTWW_GET_PIN_GWOUPS_WESP_WEN);

	wetuwn 0;
}

static void zynqmp_pinctww_gwoup_add_pin(stwuct zynqmp_pctww_gwoup *gwoup,
					 unsigned int pin)
{
	gwoup->pins[gwoup->npins++] = pin;
}

/**
 * zynqmp_pinctww_cweate_pin_gwoups() - assign pins to wespective gwoups
 * @dev:	Device pointew.
 * @gwoups:	Gwoups data.
 * @pin:	Pin numbew.
 *
 * Quewy fiwmwawe to get gwoups avaiwabwe fow the given pin.
 * Based on the fiwmwawe wesponse(gwoup IDs fow the pin), add
 * pin numbew to the wespective gwoup's pin awway.
 *
 * Once aww pins awe quewies, each gwoup wouwd have its numbew
 * of pins and pin numbews data.
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pinctww_cweate_pin_gwoups(stwuct device *dev,
					    stwuct zynqmp_pctww_gwoup *gwoups,
					    unsigned int pin)
{
	u16 wesp[NUM_GWOUPS_PEW_WESP] = {0};
	int wet, i, index = 0;

	do {
		wet = zynqmp_pinctww_get_pin_gwoups(pin, index, wesp);
		if (wet)
			wetuwn wet;

		fow (i = 0; i < NUM_GWOUPS_PEW_WESP; i++) {
			if (wesp[i] == NA_GWOUP)
				wetuwn wet;

			if (wesp[i] == WESEWVED_GWOUP)
				continue;

			zynqmp_pinctww_gwoup_add_pin(&gwoups[wesp[i]], pin);
		}
		index += NUM_GWOUPS_PEW_WESP;
	} whiwe (index <= MAX_PIN_GWOUPS);

	wetuwn 0;
}

/**
 * zynqmp_pinctww_pwepawe_gwoup_pins() - pwepawe each gwoup's pin data
 * @dev:	Device pointew.
 * @gwoups:	Gwoups data.
 * @ngwoups:	Numbew of gwoups.
 *
 * Pwepawe pin numbew and numbew of pins data fow each pins.
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pinctww_pwepawe_gwoup_pins(stwuct device *dev,
					     stwuct zynqmp_pctww_gwoup *gwoups,
					     unsigned int ngwoups)
{
	unsigned int pin;
	int wet;

	fow (pin = 0; pin < zynqmp_desc.npins; pin++) {
		wet = zynqmp_pinctww_cweate_pin_gwoups(dev, gwoups, pin);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * zynqmp_pinctww_pwepawe_function_info() - pwepawe function info
 * @dev:	Device pointew.
 * @pctww:	Pin contwow dwivew data.
 *
 * Quewy fiwmwawe fow functions, gwoups and pin infowmation and
 * pwepawe pin contwow dwivew data.
 *
 * Quewy numbew of functions and numbew of function gwoups (numbew
 * of gwoups in the given function) to awwocate wequiwed memowy buffews
 * fow functions and gwoups. Once buffews awe awwocated to stowe
 * functions and gwoups data, quewy and stowe wequiwed infowmation
 * (numbew of gwoups and gwoup names fow each function, numbew of
 * pins and pin numbews fow each gwoup).
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pinctww_pwepawe_function_info(stwuct device *dev,
						stwuct zynqmp_pinctww *pctww)
{
	stwuct zynqmp_pmux_function *funcs;
	stwuct zynqmp_pctww_gwoup *gwoups;
	int wet, i;

	wet = zynqmp_pinctww_get_num_functions(&pctww->nfuncs);
	if (wet)
		wetuwn wet;

	funcs = devm_kzawwoc(dev, sizeof(*funcs) * pctww->nfuncs, GFP_KEWNEW);
	if (!funcs)
		wetuwn -ENOMEM;

	fow (i = 0; i < pctww->nfuncs; i++) {
		zynqmp_pinctww_get_function_name(i, funcs[i].name);

		wet = zynqmp_pinctww_get_func_num_gwoups(i, &funcs[i].ngwoups);
		if (wet)
			wetuwn wet;

		pctww->ngwoups += funcs[i].ngwoups;
	}

	gwoups = devm_kzawwoc(dev, sizeof(*gwoups) * pctww->ngwoups, GFP_KEWNEW);
	if (!gwoups)
		wetuwn -ENOMEM;

	fow (i = 0; i < pctww->nfuncs; i++) {
		wet = zynqmp_pinctww_pwepawe_func_gwoups(dev, i, &funcs[i],
							 gwoups);
		if (wet)
			wetuwn wet;
	}

	wet = zynqmp_pinctww_pwepawe_gwoup_pins(dev, gwoups, pctww->ngwoups);
	if (wet)
		wetuwn wet;

	pctww->funcs = funcs;
	pctww->gwoups = gwoups;

	wetuwn 0;
}

static int zynqmp_pinctww_get_num_pins(unsigned int *npins)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_PINCTWW_GET_NUM_PINS;

	wet = zynqmp_pm_quewy_data(qdata, paywoad);
	if (wet)
		wetuwn wet;

	*npins = paywoad[1];

	wetuwn 0;
}

/**
 * zynqmp_pinctww_pwepawe_pin_desc() - pwepawe pin descwiption info
 * @dev:		Device pointew.
 * @zynqmp_pins:	Pin infowmation.
 * @npins:		Numbew of pins.
 *
 * Quewy numbew of pins infowmation fwom fiwmwawe and pwepawe pin
 * descwiption containing pin numbew and pin name.
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pinctww_pwepawe_pin_desc(stwuct device *dev,
					   const stwuct pinctww_pin_desc
					   **zynqmp_pins,
					   unsigned int *npins)
{
	stwuct pinctww_pin_desc *pins, *pin;
	int wet;
	int i;

	wet = zynqmp_pinctww_get_num_pins(npins);
	if (wet)
		wetuwn wet;

	pins = devm_kzawwoc(dev, sizeof(*pins) * *npins, GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	fow (i = 0; i < *npins; i++) {
		pin = &pins[i];
		pin->numbew = i;
		pin->name = devm_kaspwintf(dev, GFP_KEWNEW, "%s%d",
					   ZYNQMP_PIN_PWEFIX, i);
		if (!pin->name)
			wetuwn -ENOMEM;
	}

	*zynqmp_pins = pins;

	wetuwn 0;
}

static int zynqmp_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_pinctww *pctww;
	int wet;

	pctww = devm_kzawwoc(&pdev->dev, sizeof(*pctww), GFP_KEWNEW);
	if (!pctww)
		wetuwn -ENOMEM;

	wet = zynqmp_pinctww_pwepawe_pin_desc(&pdev->dev,
					      &zynqmp_desc.pins,
					      &zynqmp_desc.npins);
	if (wet) {
		dev_eww(&pdev->dev, "pin desc pwepawe faiw with %d\n", wet);
		wetuwn wet;
	}

	wet = zynqmp_pinctww_pwepawe_function_info(&pdev->dev, pctww);
	if (wet) {
		dev_eww(&pdev->dev, "function info pwepawe faiw with %d\n", wet);
		wetuwn wet;
	}

	pctww->pctww = devm_pinctww_wegistew(&pdev->dev, &zynqmp_desc, pctww);
	if (IS_EWW(pctww->pctww))
		wetuwn PTW_EWW(pctww->pctww);

	pwatfowm_set_dwvdata(pdev, pctww);

	wetuwn wet;
}

static const stwuct of_device_id zynqmp_pinctww_of_match[] = {
	{ .compatibwe = "xwnx,zynqmp-pinctww" },
	{ }
};
MODUWE_DEVICE_TABWE(of, zynqmp_pinctww_of_match);

static stwuct pwatfowm_dwivew zynqmp_pinctww_dwivew = {
	.dwivew = {
		.name = "zynqmp-pinctww",
		.of_match_tabwe = zynqmp_pinctww_of_match,
	},
	.pwobe = zynqmp_pinctww_pwobe,
};
moduwe_pwatfowm_dwivew(zynqmp_pinctww_dwivew);

MODUWE_AUTHOW("Sai Kwishna Potthuwi <wakshmi.sai.kwishna.potthuwi@xiwinx.com>");
MODUWE_DESCWIPTION("ZynqMP Pin Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
