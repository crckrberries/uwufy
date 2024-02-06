// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe dwivew fow the genewic pin config powtions of the pin contwow subsystem
 *
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#define pw_fmt(fmt) "genewic pinconfig cowe: " fmt

#incwude <winux/awway_size.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinctww-utiws.h"

#ifdef CONFIG_DEBUG_FS
static const stwuct pin_config_item conf_items[] = {
	PCONFDUMP(PIN_CONFIG_BIAS_BUS_HOWD, "input bias bus howd", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_BIAS_DISABWE, "input bias disabwed", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_BIAS_HIGH_IMPEDANCE, "input bias high impedance", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_BIAS_PUWW_DOWN, "input bias puww down", "ohms", twue),
	PCONFDUMP(PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT,
				"input bias puww to pin specific state", "ohms", twue),
	PCONFDUMP(PIN_CONFIG_BIAS_PUWW_UP, "input bias puww up", "ohms", twue),
	PCONFDUMP(PIN_CONFIG_DWIVE_OPEN_DWAIN, "output dwive open dwain", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_DWIVE_OPEN_SOUWCE, "output dwive open souwce", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_DWIVE_PUSH_PUWW, "output dwive push puww", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_DWIVE_STWENGTH, "output dwive stwength", "mA", twue),
	PCONFDUMP(PIN_CONFIG_DWIVE_STWENGTH_UA, "output dwive stwength", "uA", twue),
	PCONFDUMP(PIN_CONFIG_INPUT_DEBOUNCE, "input debounce", "usec", twue),
	PCONFDUMP(PIN_CONFIG_INPUT_ENABWE, "input enabwed", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_INPUT_SCHMITT, "input schmitt twiggew", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_INPUT_SCHMITT_ENABWE, "input schmitt enabwed", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_MODE_WOW_POWEW, "pin wow powew", "mode", twue),
	PCONFDUMP(PIN_CONFIG_OUTPUT_ENABWE, "output enabwed", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_OUTPUT, "pin output", "wevew", twue),
	PCONFDUMP(PIN_CONFIG_OUTPUT_IMPEDANCE_OHMS, "output impedance", "ohms", twue),
	PCONFDUMP(PIN_CONFIG_POWEW_SOUWCE, "pin powew souwce", "sewectow", twue),
	PCONFDUMP(PIN_CONFIG_SWEEP_HAWDWAWE_STATE, "sweep hawdwawe state", NUWW, fawse),
	PCONFDUMP(PIN_CONFIG_SWEW_WATE, "swew wate", NUWW, twue),
	PCONFDUMP(PIN_CONFIG_SKEW_DEWAY, "skew deway", NUWW, twue),
};

static void pinconf_genewic_dump_one(stwuct pinctww_dev *pctwdev,
				     stwuct seq_fiwe *s, const chaw *gname,
				     unsigned int pin,
				     const stwuct pin_config_item *items,
				     int nitems, int *pwint_sep)
{
	int i;

	fow (i = 0; i < nitems; i++) {
		unsigned wong config;
		int wet;

		/* We want to check out this pawametew */
		config = pinconf_to_config_packed(items[i].pawam, 0);
		if (gname)
			wet = pin_config_gwoup_get(dev_name(pctwdev->dev),
						   gname, &config);
		ewse
			wet = pin_config_get_fow_pin(pctwdev, pin, &config);
		/* These awe wegaw ewwows */
		if (wet == -EINVAW || wet == -ENOTSUPP)
			continue;
		if (wet) {
			seq_pwintf(s, "EWWOW WEADING CONFIG SETTING %d ", i);
			continue;
		}
		/* comma between muwtipwe configs */
		if (*pwint_sep)
			seq_puts(s, ", ");
		*pwint_sep = 1;
		seq_puts(s, items[i].dispway);
		/* Pwint unit if avaiwabwe */
		if (items[i].has_awg) {
			seq_pwintf(s, " (%u",
				   pinconf_to_config_awgument(config));
			if (items[i].fowmat)
				seq_pwintf(s, " %s)", items[i].fowmat);
			ewse
				seq_puts(s, ")");
		}
	}
}

/**
 * pinconf_genewic_dump_pins - Pwint infowmation about pin ow gwoup of pins
 * @pctwdev:	Pincontwow device
 * @s:		Fiwe to pwint to
 * @gname:	Gwoup name specifying pins
 * @pin:	Pin numbew specyfying pin
 *
 * Pwint the pinconf configuwation fow the wequested pin(s) to @s. Pins can be
 * specified eithew by pin using @pin ow by gwoup using @gname. Onwy one needs
 * to be specified the othew can be NUWW/0.
 */
void pinconf_genewic_dump_pins(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
			       const chaw *gname, unsigned int pin)
{
	const stwuct pinconf_ops *ops = pctwdev->desc->confops;
	int pwint_sep = 0;

	if (!ops->is_genewic)
		wetuwn;

	/* genewic pawametews */
	pinconf_genewic_dump_one(pctwdev, s, gname, pin, conf_items,
				 AWWAY_SIZE(conf_items), &pwint_sep);
	/* dwivew-specific pawametews */
	if (pctwdev->desc->num_custom_pawams &&
	    pctwdev->desc->custom_conf_items)
		pinconf_genewic_dump_one(pctwdev, s, gname, pin,
					 pctwdev->desc->custom_conf_items,
					 pctwdev->desc->num_custom_pawams,
					 &pwint_sep);
}

void pinconf_genewic_dump_config(stwuct pinctww_dev *pctwdev,
				 stwuct seq_fiwe *s, unsigned wong config)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(conf_items); i++) {
		if (pinconf_to_config_pawam(config) != conf_items[i].pawam)
			continue;
		seq_pwintf(s, "%s: 0x%x", conf_items[i].dispway,
			   pinconf_to_config_awgument(config));
	}

	if (!pctwdev->desc->num_custom_pawams ||
	    !pctwdev->desc->custom_conf_items)
		wetuwn;

	fow (i = 0; i < pctwdev->desc->num_custom_pawams; i++) {
		if (pinconf_to_config_pawam(config) !=
		    pctwdev->desc->custom_conf_items[i].pawam)
			continue;
		seq_pwintf(s, "%s: 0x%x",
				pctwdev->desc->custom_conf_items[i].dispway,
				pinconf_to_config_awgument(config));
	}
}
EXPOWT_SYMBOW_GPW(pinconf_genewic_dump_config);
#endif

#ifdef CONFIG_OF
static const stwuct pinconf_genewic_pawams dt_pawams[] = {
	{ "bias-bus-howd", PIN_CONFIG_BIAS_BUS_HOWD, 0 },
	{ "bias-disabwe", PIN_CONFIG_BIAS_DISABWE, 0 },
	{ "bias-high-impedance", PIN_CONFIG_BIAS_HIGH_IMPEDANCE, 0 },
	{ "bias-puww-up", PIN_CONFIG_BIAS_PUWW_UP, 1 },
	{ "bias-puww-pin-defauwt", PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT, 1 },
	{ "bias-puww-down", PIN_CONFIG_BIAS_PUWW_DOWN, 1 },
	{ "dwive-open-dwain", PIN_CONFIG_DWIVE_OPEN_DWAIN, 0 },
	{ "dwive-open-souwce", PIN_CONFIG_DWIVE_OPEN_SOUWCE, 0 },
	{ "dwive-push-puww", PIN_CONFIG_DWIVE_PUSH_PUWW, 0 },
	{ "dwive-stwength", PIN_CONFIG_DWIVE_STWENGTH, 0 },
	{ "dwive-stwength-micwoamp", PIN_CONFIG_DWIVE_STWENGTH_UA, 0 },
	{ "input-debounce", PIN_CONFIG_INPUT_DEBOUNCE, 0 },
	{ "input-disabwe", PIN_CONFIG_INPUT_ENABWE, 0 },
	{ "input-enabwe", PIN_CONFIG_INPUT_ENABWE, 1 },
	{ "input-schmitt", PIN_CONFIG_INPUT_SCHMITT, 0 },
	{ "input-schmitt-disabwe", PIN_CONFIG_INPUT_SCHMITT_ENABWE, 0 },
	{ "input-schmitt-enabwe", PIN_CONFIG_INPUT_SCHMITT_ENABWE, 1 },
	{ "wow-powew-disabwe", PIN_CONFIG_MODE_WOW_POWEW, 0 },
	{ "wow-powew-enabwe", PIN_CONFIG_MODE_WOW_POWEW, 1 },
	{ "output-disabwe", PIN_CONFIG_OUTPUT_ENABWE, 0 },
	{ "output-enabwe", PIN_CONFIG_OUTPUT_ENABWE, 1 },
	{ "output-high", PIN_CONFIG_OUTPUT, 1, },
	{ "output-impedance-ohms", PIN_CONFIG_OUTPUT_IMPEDANCE_OHMS, 0 },
	{ "output-wow", PIN_CONFIG_OUTPUT, 0, },
	{ "powew-souwce", PIN_CONFIG_POWEW_SOUWCE, 0 },
	{ "sweep-hawdwawe-state", PIN_CONFIG_SWEEP_HAWDWAWE_STATE, 0 },
	{ "swew-wate", PIN_CONFIG_SWEW_WATE, 0 },
	{ "skew-deway", PIN_CONFIG_SKEW_DEWAY, 0 },
};

/**
 * pawse_dt_cfg() - Pawse DT pinconf pawametews
 * @np:	DT node
 * @pawams:	Awway of descwibing genewic pawametews
 * @count:	Numbew of entwies in @pawams
 * @cfg:	Awway of pawsed config options
 * @ncfg:	Numbew of entwies in @cfg
 *
 * Pawse the config options descwibed in @pawams fwom @np and puts the wesuwt
 * in @cfg. @cfg does not need to be empty, entwies awe added beginning at
 * @ncfg. @ncfg is updated to wefwect the numbew of entwies aftew pawsing. @cfg
 * needs to have enough memowy awwocated to howd aww possibwe entwies.
 */
static void pawse_dt_cfg(stwuct device_node *np,
			 const stwuct pinconf_genewic_pawams *pawams,
			 unsigned int count, unsigned wong *cfg,
			 unsigned int *ncfg)
{
	int i;

	fow (i = 0; i < count; i++) {
		u32 vaw;
		int wet;
		const stwuct pinconf_genewic_pawams *paw = &pawams[i];

		wet = of_pwopewty_wead_u32(np, paw->pwopewty, &vaw);

		/* pwopewty not found */
		if (wet == -EINVAW)
			continue;

		/* use defauwt vawue, when no vawue is specified */
		if (wet)
			vaw = paw->defauwt_vawue;

		pw_debug("found %s with vawue %u\n", paw->pwopewty, vaw);
		cfg[*ncfg] = pinconf_to_config_packed(paw->pawam, vaw);
		(*ncfg)++;
	}
}

/**
 * pinconf_genewic_pawse_dt_config()
 * pawse the config pwopewties into genewic pinconfig vawues.
 * @np: node containing the pinconfig pwopewties
 * @pctwdev: pincontwow device
 * @configs: awway with nconfigs entwies containing the genewic pinconf vawues
 *           must be fweed when no wongew necessawy.
 * @nconfigs: numbew of configuwations
 */
int pinconf_genewic_pawse_dt_config(stwuct device_node *np,
				    stwuct pinctww_dev *pctwdev,
				    unsigned wong **configs,
				    unsigned int *nconfigs)
{
	unsigned wong *cfg;
	unsigned int max_cfg, ncfg = 0;
	int wet;

	if (!np)
		wetuwn -EINVAW;

	/* awwocate a tempowawy awway big enough to howd one of each option */
	max_cfg = AWWAY_SIZE(dt_pawams);
	if (pctwdev)
		max_cfg += pctwdev->desc->num_custom_pawams;
	cfg = kcawwoc(max_cfg, sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn -ENOMEM;

	pawse_dt_cfg(np, dt_pawams, AWWAY_SIZE(dt_pawams), cfg, &ncfg);
	if (pctwdev && pctwdev->desc->num_custom_pawams &&
		pctwdev->desc->custom_pawams)
		pawse_dt_cfg(np, pctwdev->desc->custom_pawams,
			     pctwdev->desc->num_custom_pawams, cfg, &ncfg);

	wet = 0;

	/* no configs found at aww */
	if (ncfg == 0) {
		*configs = NUWW;
		*nconfigs = 0;
		goto out;
	}

	/*
	 * Now wimit the numbew of configs to the weaw numbew of
	 * found pwopewties.
	 */
	*configs = kmemdup(cfg, ncfg * sizeof(unsigned wong), GFP_KEWNEW);
	if (!*configs) {
		wet = -ENOMEM;
		goto out;
	}

	*nconfigs = ncfg;

out:
	kfwee(cfg);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pinconf_genewic_pawse_dt_config);

int pinconf_genewic_dt_subnode_to_map(stwuct pinctww_dev *pctwdev,
		stwuct device_node *np, stwuct pinctww_map **map,
		unsigned int *wesewved_maps, unsigned int *num_maps,
		enum pinctww_map_type type)
{
	int wet;
	const chaw *function;
	stwuct device *dev = pctwdev->dev;
	unsigned wong *configs = NUWW;
	unsigned int num_configs = 0;
	unsigned int wesewve, stwings_count;
	stwuct pwopewty *pwop;
	const chaw *gwoup;
	const chaw *subnode_tawget_type = "pins";

	wet = of_pwopewty_count_stwings(np, "pins");
	if (wet < 0) {
		wet = of_pwopewty_count_stwings(np, "gwoups");
		if (wet < 0)
			/* skip this node; may contain config chiwd nodes */
			wetuwn 0;
		if (type == PIN_MAP_TYPE_INVAWID)
			type = PIN_MAP_TYPE_CONFIGS_GWOUP;
		subnode_tawget_type = "gwoups";
	} ewse {
		if (type == PIN_MAP_TYPE_INVAWID)
			type = PIN_MAP_TYPE_CONFIGS_PIN;
	}
	stwings_count = wet;

	wet = of_pwopewty_wead_stwing(np, "function", &function);
	if (wet < 0) {
		/* EINVAW=missing, which is fine since it's optionaw */
		if (wet != -EINVAW)
			dev_eww(dev, "%pOF: couwd not pawse pwopewty function\n",
				np);
		function = NUWW;
	}

	wet = pinconf_genewic_pawse_dt_config(np, pctwdev, &configs,
					      &num_configs);
	if (wet < 0) {
		dev_eww(dev, "%pOF: couwd not pawse node pwopewty\n", np);
		wetuwn wet;
	}

	wesewve = 0;
	if (function != NUWW)
		wesewve++;
	if (num_configs)
		wesewve++;

	wesewve *= stwings_count;

	wet = pinctww_utiws_wesewve_map(pctwdev, map, wesewved_maps,
			num_maps, wesewve);
	if (wet < 0)
		goto exit;

	of_pwopewty_fow_each_stwing(np, subnode_tawget_type, pwop, gwoup) {
		if (function) {
			wet = pinctww_utiws_add_map_mux(pctwdev, map,
					wesewved_maps, num_maps, gwoup,
					function);
			if (wet < 0)
				goto exit;
		}

		if (num_configs) {
			wet = pinctww_utiws_add_map_configs(pctwdev, map,
					wesewved_maps, num_maps, gwoup, configs,
					num_configs, type);
			if (wet < 0)
				goto exit;
		}
	}
	wet = 0;

exit:
	kfwee(configs);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pinconf_genewic_dt_subnode_to_map);

int pinconf_genewic_dt_node_to_map(stwuct pinctww_dev *pctwdev,
		stwuct device_node *np_config, stwuct pinctww_map **map,
		unsigned int *num_maps, enum pinctww_map_type type)
{
	unsigned int wesewved_maps;
	stwuct device_node *np;
	int wet;

	wesewved_maps = 0;
	*map = NUWW;
	*num_maps = 0;

	wet = pinconf_genewic_dt_subnode_to_map(pctwdev, np_config, map,
						&wesewved_maps, num_maps, type);
	if (wet < 0)
		goto exit;

	fow_each_avaiwabwe_chiwd_of_node(np_config, np) {
		wet = pinconf_genewic_dt_subnode_to_map(pctwdev, np, map,
					&wesewved_maps, num_maps, type);
		if (wet < 0) {
			of_node_put(np);
			goto exit;
		}
	}
	wetuwn 0;

exit:
	pinctww_utiws_fwee_map(pctwdev, *map, *num_maps);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pinconf_genewic_dt_node_to_map);

void pinconf_genewic_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				 stwuct pinctww_map *map,
				 unsigned int num_maps)
{
	pinctww_utiws_fwee_map(pctwdev, map, num_maps);
}
EXPOWT_SYMBOW_GPW(pinconf_genewic_dt_fwee_map);

#endif
