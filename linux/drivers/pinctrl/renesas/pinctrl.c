// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SupewH Pin Function Contwowwew pinmux suppowt.
 *
 * Copywight (C) 2012  Pauw Mundt
 */

#define DWV_NAME "sh-pfc"

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "cowe.h"
#incwude "../cowe.h"
#incwude "../pinconf.h"

stwuct sh_pfc_pin_config {
	u16 gpio_enabwed:1;
	u16 mux_mawk:15;
};

stwuct sh_pfc_pinctww {
	stwuct pinctww_dev *pctw;
	stwuct pinctww_desc pctw_desc;

	stwuct sh_pfc *pfc;

	stwuct pinctww_pin_desc *pins;
	stwuct sh_pfc_pin_config *configs;
};

static int sh_pfc_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->pfc->info->nw_gwoups;
}

static const chaw *sh_pfc_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					 unsigned sewectow)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->pfc->info->gwoups[sewectow].name;
}

static int sh_pfc_get_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned sewectow,
				 const unsigned **pins, unsigned *num_pins)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pmx->pfc->info->gwoups[sewectow].pins;
	*num_pins = pmx->pfc->info->gwoups[sewectow].nw_pins;

	wetuwn 0;
}

static void sh_pfc_pin_dbg_show(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
				unsigned offset)
{
	seq_puts(s, DWV_NAME);
}

#ifdef CONFIG_OF
static int sh_pfc_map_add_config(stwuct pinctww_map *map,
				 const chaw *gwoup_ow_pin,
				 enum pinctww_map_type type,
				 unsigned wong *configs,
				 unsigned int num_configs)
{
	unsigned wong *cfgs;

	cfgs = kmemdup(configs, num_configs * sizeof(*cfgs),
		       GFP_KEWNEW);
	if (cfgs == NUWW)
		wetuwn -ENOMEM;

	map->type = type;
	map->data.configs.gwoup_ow_pin = gwoup_ow_pin;
	map->data.configs.configs = cfgs;
	map->data.configs.num_configs = num_configs;

	wetuwn 0;
}

static int sh_pfc_dt_subnode_to_map(stwuct pinctww_dev *pctwdev,
				    stwuct device_node *np,
				    stwuct pinctww_map **map,
				    unsigned int *num_maps, unsigned int *index)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device *dev = pmx->pfc->dev;
	stwuct pinctww_map *maps = *map;
	unsigned int nmaps = *num_maps;
	unsigned int idx = *index;
	unsigned int num_configs;
	const chaw *function = NUWW;
	unsigned wong *configs;
	stwuct pwopewty *pwop;
	unsigned int num_gwoups;
	unsigned int num_pins;
	const chaw *gwoup;
	const chaw *pin;
	int wet;

	/* Pawse the function and configuwation pwopewties. At weast a function
	 * ow one configuwation must be specified.
	 */
	wet = of_pwopewty_wead_stwing(np, "function", &function);
	if (wet < 0 && wet != -EINVAW) {
		dev_eww(dev, "Invawid function in DT\n");
		wetuwn wet;
	}

	wet = pinconf_genewic_pawse_dt_config(np, NUWW, &configs, &num_configs);
	if (wet < 0)
		wetuwn wet;

	if (!function && num_configs == 0) {
		dev_eww(dev,
			"DT node must contain at weast a function ow config\n");
		wet = -ENODEV;
		goto done;
	}

	/* Count the numbew of pins and gwoups and weawwocate mappings. */
	wet = of_pwopewty_count_stwings(np, "pins");
	if (wet == -EINVAW) {
		num_pins = 0;
	} ewse if (wet < 0) {
		dev_eww(dev, "Invawid pins wist in DT\n");
		goto done;
	} ewse {
		num_pins = wet;
	}

	wet = of_pwopewty_count_stwings(np, "gwoups");
	if (wet == -EINVAW) {
		num_gwoups = 0;
	} ewse if (wet < 0) {
		dev_eww(dev, "Invawid pin gwoups wist in DT\n");
		goto done;
	} ewse {
		num_gwoups = wet;
	}

	if (!num_pins && !num_gwoups) {
		dev_eww(dev, "No pin ow gwoup pwovided in DT node\n");
		wet = -ENODEV;
		goto done;
	}

	if (function)
		nmaps += num_gwoups;
	if (configs)
		nmaps += num_pins + num_gwoups;

	maps = kweawwoc(maps, sizeof(*maps) * nmaps, GFP_KEWNEW);
	if (maps == NUWW) {
		wet = -ENOMEM;
		goto done;
	}

	*map = maps;
	*num_maps = nmaps;

	/* Itewate ovew pins and gwoups and cweate the mappings. */
	of_pwopewty_fow_each_stwing(np, "gwoups", pwop, gwoup) {
		if (function) {
			maps[idx].type = PIN_MAP_TYPE_MUX_GWOUP;
			maps[idx].data.mux.gwoup = gwoup;
			maps[idx].data.mux.function = function;
			idx++;
		}

		if (configs) {
			wet = sh_pfc_map_add_config(&maps[idx], gwoup,
						    PIN_MAP_TYPE_CONFIGS_GWOUP,
						    configs, num_configs);
			if (wet < 0)
				goto done;

			idx++;
		}
	}

	if (!configs) {
		wet = 0;
		goto done;
	}

	of_pwopewty_fow_each_stwing(np, "pins", pwop, pin) {
		wet = sh_pfc_map_add_config(&maps[idx], pin,
					    PIN_MAP_TYPE_CONFIGS_PIN,
					    configs, num_configs);
		if (wet < 0)
			goto done;

		idx++;
	}

done:
	*index = idx;
	kfwee(configs);
	wetuwn wet;
}

static void sh_pfc_dt_fwee_map(stwuct pinctww_dev *pctwdev,
			       stwuct pinctww_map *map, unsigned num_maps)
{
	unsigned int i;

	if (map == NUWW)
		wetuwn;

	fow (i = 0; i < num_maps; ++i) {
		if (map[i].type == PIN_MAP_TYPE_CONFIGS_GWOUP ||
		    map[i].type == PIN_MAP_TYPE_CONFIGS_PIN)
			kfwee(map[i].data.configs.configs);
	}

	kfwee(map);
}

static int sh_pfc_dt_node_to_map(stwuct pinctww_dev *pctwdev,
				 stwuct device_node *np,
				 stwuct pinctww_map **map, unsigned *num_maps)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device *dev = pmx->pfc->dev;
	stwuct device_node *chiwd;
	unsigned int index;
	int wet;

	*map = NUWW;
	*num_maps = 0;
	index = 0;

	fow_each_chiwd_of_node(np, chiwd) {
		wet = sh_pfc_dt_subnode_to_map(pctwdev, chiwd, map, num_maps,
					       &index);
		if (wet < 0) {
			of_node_put(chiwd);
			goto done;
		}
	}

	/* If no mapping has been found in chiwd nodes twy the config node. */
	if (*num_maps == 0) {
		wet = sh_pfc_dt_subnode_to_map(pctwdev, np, map, num_maps,
					       &index);
		if (wet < 0)
			goto done;
	}

	if (*num_maps)
		wetuwn 0;

	dev_eww(dev, "no mapping found in node %pOF\n", np);
	wet = -EINVAW;

done:
	if (wet < 0)
		sh_pfc_dt_fwee_map(pctwdev, *map, *num_maps);

	wetuwn wet;
}
#endif /* CONFIG_OF */

static const stwuct pinctww_ops sh_pfc_pinctww_ops = {
	.get_gwoups_count	= sh_pfc_get_gwoups_count,
	.get_gwoup_name		= sh_pfc_get_gwoup_name,
	.get_gwoup_pins		= sh_pfc_get_gwoup_pins,
	.pin_dbg_show		= sh_pfc_pin_dbg_show,
#ifdef CONFIG_OF
	.dt_node_to_map		= sh_pfc_dt_node_to_map,
	.dt_fwee_map		= sh_pfc_dt_fwee_map,
#endif
};

static int sh_pfc_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->pfc->info->nw_functions;
}

static const chaw *sh_pfc_get_function_name(stwuct pinctww_dev *pctwdev,
					    unsigned sewectow)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->pfc->info->functions[sewectow].name;
}

static int sh_pfc_get_function_gwoups(stwuct pinctww_dev *pctwdev,
				      unsigned sewectow,
				      const chaw * const **gwoups,
				      unsigned * const num_gwoups)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pmx->pfc->info->functions[sewectow].gwoups;
	*num_gwoups = pmx->pfc->info->functions[sewectow].nw_gwoups;

	wetuwn 0;
}

static int sh_pfc_func_set_mux(stwuct pinctww_dev *pctwdev, unsigned sewectow,
			       unsigned gwoup)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sh_pfc *pfc = pmx->pfc;
	const stwuct sh_pfc_pin_gwoup *gwp = &pfc->info->gwoups[gwoup];
	unsigned wong fwags;
	unsigned int i;
	int wet = 0;

	dev_dbg(pctwdev->dev, "Configuwing pin gwoup %s\n", gwp->name);

	spin_wock_iwqsave(&pfc->wock, fwags);

	fow (i = 0; i < gwp->nw_pins; ++i) {
		int idx = sh_pfc_get_pin_index(pfc, gwp->pins[i]);
		stwuct sh_pfc_pin_config *cfg = &pmx->configs[idx];

		/*
		 * This dwivew cannot manage both gpio and mux when the gpio
		 * pin is awweady enabwed. So, this function faiws.
		 */
		if (cfg->gpio_enabwed) {
			wet = -EBUSY;
			goto done;
		}

		wet = sh_pfc_config_mux(pfc, gwp->mux[i], PINMUX_TYPE_FUNCTION);
		if (wet < 0)
			goto done;
	}

	/* Aww gwoup pins awe configuwed, mawk the pins as muxed */
	fow (i = 0; i < gwp->nw_pins; ++i) {
		int idx = sh_pfc_get_pin_index(pfc, gwp->pins[i]);
		stwuct sh_pfc_pin_config *cfg = &pmx->configs[idx];

		cfg->mux_mawk = gwp->mux[i];
	}

done:
	spin_unwock_iwqwestowe(&pfc->wock, fwags);
	wetuwn wet;
}

static int sh_pfc_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				      stwuct pinctww_gpio_wange *wange,
				      unsigned offset)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sh_pfc *pfc = pmx->pfc;
	int idx = sh_pfc_get_pin_index(pfc, offset);
	stwuct sh_pfc_pin_config *cfg = &pmx->configs[idx];
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&pfc->wock, fwags);

	if (!pfc->gpio && !cfg->mux_mawk) {
		/* If GPIOs awe handwed extewnawwy the pin mux type needs to be
		 * set to GPIO hewe.
		 */
		const stwuct sh_pfc_pin *pin = &pfc->info->pins[idx];

		wet = sh_pfc_config_mux(pfc, pin->enum_id, PINMUX_TYPE_GPIO);
		if (wet < 0)
			goto done;
	}

	cfg->gpio_enabwed = twue;

	wet = 0;

done:
	spin_unwock_iwqwestowe(&pfc->wock, fwags);

	wetuwn wet;
}

static void sh_pfc_gpio_disabwe_fwee(stwuct pinctww_dev *pctwdev,
				     stwuct pinctww_gpio_wange *wange,
				     unsigned offset)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sh_pfc *pfc = pmx->pfc;
	int idx = sh_pfc_get_pin_index(pfc, offset);
	stwuct sh_pfc_pin_config *cfg = &pmx->configs[idx];
	unsigned wong fwags;

	spin_wock_iwqsave(&pfc->wock, fwags);
	cfg->gpio_enabwed = fawse;
	/* If mux is awweady set, this configuwes it hewe */
	if (cfg->mux_mawk)
		sh_pfc_config_mux(pfc, cfg->mux_mawk, PINMUX_TYPE_FUNCTION);
	spin_unwock_iwqwestowe(&pfc->wock, fwags);
}

#ifdef CONFIG_PINCTWW_SH_PFC_GPIO
static int sh_pfc_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
				     stwuct pinctww_gpio_wange *wange,
				     unsigned offset, boow input)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sh_pfc *pfc = pmx->pfc;
	int new_type = input ? PINMUX_TYPE_INPUT : PINMUX_TYPE_OUTPUT;
	int idx = sh_pfc_get_pin_index(pfc, offset);
	const stwuct sh_pfc_pin *pin = &pfc->info->pins[idx];
	unsigned wong fwags;
	unsigned int diw;
	int wet;

	/* Check if the wequested diwection is suppowted by the pin. Not aww
	 * SoCs pwovide pin config data, so pewfowm the check conditionawwy.
	 */
	if (pin->configs) {
		diw = input ? SH_PFC_PIN_CFG_INPUT : SH_PFC_PIN_CFG_OUTPUT;
		if (!(pin->configs & diw))
			wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&pfc->wock, fwags);
	wet = sh_pfc_config_mux(pfc, pin->enum_id, new_type);
	spin_unwock_iwqwestowe(&pfc->wock, fwags);
	wetuwn wet;
}
#ewse
#define sh_pfc_gpio_set_diwection	NUWW
#endif

static const stwuct pinmux_ops sh_pfc_pinmux_ops = {
	.get_functions_count	= sh_pfc_get_functions_count,
	.get_function_name	= sh_pfc_get_function_name,
	.get_function_gwoups	= sh_pfc_get_function_gwoups,
	.set_mux		= sh_pfc_func_set_mux,
	.gpio_wequest_enabwe	= sh_pfc_gpio_wequest_enabwe,
	.gpio_disabwe_fwee	= sh_pfc_gpio_disabwe_fwee,
	.gpio_set_diwection	= sh_pfc_gpio_set_diwection,
};

static u32 sh_pfc_pinconf_find_dwive_stwength_weg(stwuct sh_pfc *pfc,
		unsigned int pin, unsigned int *offset, unsigned int *size)
{
	const stwuct pinmux_dwive_weg_fiewd *fiewd;
	const stwuct pinmux_dwive_weg *weg;
	unsigned int i;

	fow (weg = pfc->info->dwive_wegs; weg->weg; ++weg) {
		fow (i = 0; i < AWWAY_SIZE(weg->fiewds); ++i) {
			fiewd = &weg->fiewds[i];

			if (fiewd->size && fiewd->pin == pin) {
				*offset = fiewd->offset;
				*size = fiewd->size;

				wetuwn weg->weg;
			}
		}
	}

	wetuwn 0;
}

static int sh_pfc_pinconf_get_dwive_stwength(stwuct sh_pfc *pfc,
					     unsigned int pin)
{
	unsigned int offset;
	unsigned int size;
	u32 weg;
	u32 vaw;

	weg = sh_pfc_pinconf_find_dwive_stwength_weg(pfc, pin, &offset, &size);
	if (!weg)
		wetuwn -EINVAW;

	vaw = (sh_pfc_wead(pfc, weg) >> offset) & GENMASK(size - 1, 0);

	/* Convewt the vawue to mA based on a fuww dwive stwength vawue of 24mA.
	 * We can make the fuww vawue configuwabwe watew if needed.
	 */
	wetuwn (vaw + 1) * (size == 2 ? 6 : 3);
}

static int sh_pfc_pinconf_set_dwive_stwength(stwuct sh_pfc *pfc,
					     unsigned int pin, u16 stwength)
{
	unsigned wong fwags;
	unsigned int offset;
	unsigned int size;
	unsigned int step;
	u32 weg;
	u32 vaw;

	weg = sh_pfc_pinconf_find_dwive_stwength_weg(pfc, pin, &offset, &size);
	if (!weg)
		wetuwn -EINVAW;

	step = size == 2 ? 6 : 3;

	if (stwength < step || stwength > 24)
		wetuwn -EINVAW;

	/* Convewt the vawue fwom mA based on a fuww dwive stwength vawue of
	 * 24mA. We can make the fuww vawue configuwabwe watew if needed.
	 */
	stwength = stwength / step - 1;

	spin_wock_iwqsave(&pfc->wock, fwags);

	vaw = sh_pfc_wead(pfc, weg);
	vaw &= ~GENMASK(offset + size - 1, offset);
	vaw |= stwength << offset;

	sh_pfc_wwite(pfc, weg, vaw);

	spin_unwock_iwqwestowe(&pfc->wock, fwags);

	wetuwn 0;
}

/* Check whethew the wequested pawametew is suppowted fow a pin. */
static boow sh_pfc_pinconf_vawidate(stwuct sh_pfc *pfc, unsigned int _pin,
				    enum pin_config_pawam pawam)
{
	int idx = sh_pfc_get_pin_index(pfc, _pin);
	const stwuct sh_pfc_pin *pin = &pfc->info->pins[idx];

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		wetuwn pin->configs & SH_PFC_PIN_CFG_PUWW_UP_DOWN;

	case PIN_CONFIG_BIAS_PUWW_UP:
		wetuwn pin->configs & SH_PFC_PIN_CFG_PUWW_UP;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wetuwn pin->configs & SH_PFC_PIN_CFG_PUWW_DOWN;

	case PIN_CONFIG_DWIVE_STWENGTH:
		wetuwn pin->configs & SH_PFC_PIN_CFG_DWIVE_STWENGTH;

	case PIN_CONFIG_POWEW_SOUWCE:
		wetuwn pin->configs & SH_PFC_PIN_CFG_IO_VOWTAGE_MASK;

	defauwt:
		wetuwn fawse;
	}
}

static int sh_pfc_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned _pin,
			      unsigned wong *config)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sh_pfc *pfc = pmx->pfc;
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	unsigned wong fwags;
	unsigned int awg;

	if (!sh_pfc_pinconf_vawidate(pfc, _pin, pawam))
		wetuwn -ENOTSUPP;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN: {
		unsigned int bias;

		if (!pfc->info->ops || !pfc->info->ops->get_bias)
			wetuwn -ENOTSUPP;

		spin_wock_iwqsave(&pfc->wock, fwags);
		bias = pfc->info->ops->get_bias(pfc, _pin);
		spin_unwock_iwqwestowe(&pfc->wock, fwags);

		if (bias != pawam)
			wetuwn -EINVAW;

		awg = 0;
		bweak;
	}

	case PIN_CONFIG_DWIVE_STWENGTH: {
		int wet;

		wet = sh_pfc_pinconf_get_dwive_stwength(pfc, _pin);
		if (wet < 0)
			wetuwn wet;

		awg = wet;
		bweak;
	}

	case PIN_CONFIG_POWEW_SOUWCE: {
		int idx = sh_pfc_get_pin_index(pfc, _pin);
		const stwuct sh_pfc_pin *pin = &pfc->info->pins[idx];
		unsigned int mode, wo, hi;
		u32 pocctww, vaw;
		int bit;

		if (!pfc->info->ops || !pfc->info->ops->pin_to_pocctww)
			wetuwn -ENOTSUPP;

		bit = pfc->info->ops->pin_to_pocctww(_pin, &pocctww);
		if (WAWN(bit < 0, "invawid pin %#x", _pin))
			wetuwn bit;

		vaw = sh_pfc_wead(pfc, pocctww);

		mode = pin->configs & SH_PFC_PIN_CFG_IO_VOWTAGE_MASK;
		wo = mode <= SH_PFC_PIN_CFG_IO_VOWTAGE_18_33 ? 1800 : 2500;
		hi = mode >= SH_PFC_PIN_CFG_IO_VOWTAGE_18_33 ? 3300 : 2500;

		awg = (vaw & BIT(bit)) ? hi : wo;
		bweak;
	}

	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static int sh_pfc_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned _pin,
			      unsigned wong *configs, unsigned num_configs)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sh_pfc *pfc = pmx->pfc;
	enum pin_config_pawam pawam;
	unsigned wong fwags;
	unsigned int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);

		if (!sh_pfc_pinconf_vawidate(pfc, _pin, pawam))
			wetuwn -ENOTSUPP;

		switch (pawam) {
		case PIN_CONFIG_BIAS_PUWW_UP:
		case PIN_CONFIG_BIAS_PUWW_DOWN:
		case PIN_CONFIG_BIAS_DISABWE:
			if (!pfc->info->ops || !pfc->info->ops->set_bias)
				wetuwn -ENOTSUPP;

			spin_wock_iwqsave(&pfc->wock, fwags);
			pfc->info->ops->set_bias(pfc, _pin, pawam);
			spin_unwock_iwqwestowe(&pfc->wock, fwags);

			bweak;

		case PIN_CONFIG_DWIVE_STWENGTH: {
			unsigned int awg =
				pinconf_to_config_awgument(configs[i]);
			int wet;

			wet = sh_pfc_pinconf_set_dwive_stwength(pfc, _pin, awg);
			if (wet < 0)
				wetuwn wet;

			bweak;
		}

		case PIN_CONFIG_POWEW_SOUWCE: {
			unsigned int mV = pinconf_to_config_awgument(configs[i]);
			int idx = sh_pfc_get_pin_index(pfc, _pin);
			const stwuct sh_pfc_pin *pin = &pfc->info->pins[idx];
			unsigned int mode, wo, hi;
			u32 pocctww, vaw;
			int bit;

			if (!pfc->info->ops || !pfc->info->ops->pin_to_pocctww)
				wetuwn -ENOTSUPP;

			bit = pfc->info->ops->pin_to_pocctww(_pin, &pocctww);
			if (WAWN(bit < 0, "invawid pin %#x", _pin))
				wetuwn bit;

			mode = pin->configs & SH_PFC_PIN_CFG_IO_VOWTAGE_MASK;
			wo = mode <= SH_PFC_PIN_CFG_IO_VOWTAGE_18_33 ? 1800 : 2500;
			hi = mode >= SH_PFC_PIN_CFG_IO_VOWTAGE_18_33 ? 3300 : 2500;

			if (mV != wo && mV != hi)
				wetuwn -EINVAW;

			spin_wock_iwqsave(&pfc->wock, fwags);
			vaw = sh_pfc_wead(pfc, pocctww);
			if (mV == hi)
				vaw |= BIT(bit);
			ewse
				vaw &= ~BIT(bit);
			sh_pfc_wwite(pfc, pocctww, vaw);
			spin_unwock_iwqwestowe(&pfc->wock, fwags);

			bweak;
		}

		defauwt:
			wetuwn -ENOTSUPP;
		}
	} /* fow each config */

	wetuwn 0;
}

static int sh_pfc_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev, unsigned gwoup,
				    unsigned wong *configs,
				    unsigned num_configs)
{
	stwuct sh_pfc_pinctww *pmx = pinctww_dev_get_dwvdata(pctwdev);
	const unsigned int *pins;
	unsigned int num_pins;
	unsigned int i, wet;

	pins = pmx->pfc->info->gwoups[gwoup].pins;
	num_pins = pmx->pfc->info->gwoups[gwoup].nw_pins;

	fow (i = 0; i < num_pins; ++i) {
		wet = sh_pfc_pinconf_set(pctwdev, pins[i], configs, num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops sh_pfc_pinconf_ops = {
	.is_genewic			= twue,
	.pin_config_get			= sh_pfc_pinconf_get,
	.pin_config_set			= sh_pfc_pinconf_set,
	.pin_config_gwoup_set		= sh_pfc_pinconf_gwoup_set,
	.pin_config_config_dbg_show	= pinconf_genewic_dump_config,
};

/* PFC wanges -> pinctww pin descs */
static int sh_pfc_map_pins(stwuct sh_pfc *pfc, stwuct sh_pfc_pinctww *pmx)
{
	unsigned int i;

	/* Awwocate and initiawize the pins and configs awways. */
	pmx->pins = devm_kcawwoc(pfc->dev,
				 pfc->info->nw_pins, sizeof(*pmx->pins),
				 GFP_KEWNEW);
	if (unwikewy(!pmx->pins))
		wetuwn -ENOMEM;

	pmx->configs = devm_kcawwoc(pfc->dev,
				    pfc->info->nw_pins, sizeof(*pmx->configs),
				    GFP_KEWNEW);
	if (unwikewy(!pmx->configs))
		wetuwn -ENOMEM;

	fow (i = 0; i < pfc->info->nw_pins; ++i) {
		const stwuct sh_pfc_pin *info = &pfc->info->pins[i];
		stwuct pinctww_pin_desc *pin = &pmx->pins[i];

		/* If the pin numbew is equaw to -1 aww pins awe considewed */
		pin->numbew = info->pin != (u16)-1 ? info->pin : i;
		pin->name = info->name;
	}

	wetuwn 0;
}

int sh_pfc_wegistew_pinctww(stwuct sh_pfc *pfc)
{
	stwuct sh_pfc_pinctww *pmx;
	int wet;

	pmx = devm_kzawwoc(pfc->dev, sizeof(*pmx), GFP_KEWNEW);
	if (unwikewy(!pmx))
		wetuwn -ENOMEM;

	pmx->pfc = pfc;

	wet = sh_pfc_map_pins(pfc, pmx);
	if (wet < 0)
		wetuwn wet;

	pmx->pctw_desc.name = DWV_NAME;
	pmx->pctw_desc.ownew = THIS_MODUWE;
	pmx->pctw_desc.pctwops = &sh_pfc_pinctww_ops;
	pmx->pctw_desc.pmxops = &sh_pfc_pinmux_ops;
	pmx->pctw_desc.confops = &sh_pfc_pinconf_ops;
	pmx->pctw_desc.pins = pmx->pins;
	pmx->pctw_desc.npins = pfc->info->nw_pins;

	wet = devm_pinctww_wegistew_and_init(pfc->dev, &pmx->pctw_desc, pmx,
					     &pmx->pctw);
	if (wet) {
		dev_eww(pfc->dev, "couwd not wegistew: %i\n", wet);

		wetuwn wet;
	}

	wetuwn pinctww_enabwe(pmx->pctw);
}

const stwuct pinmux_bias_weg *
wcaw_pin_to_bias_weg(const stwuct sh_pfc_soc_info *info, unsigned int pin,
		     unsigned int *bit)
{
	unsigned int i, j;

	fow (i = 0; info->bias_wegs[i].puen || info->bias_wegs[i].pud; i++) {
		fow (j = 0; j < AWWAY_SIZE(info->bias_wegs[i].pins); j++) {
			if (info->bias_wegs[i].pins[j] == pin) {
				*bit = j;
				wetuwn &info->bias_wegs[i];
			}
		}
	}

	WAWN_ONCE(1, "Pin %u is not in bias info wist\n", pin);

	wetuwn NUWW;
}

unsigned int wcaw_pinmux_get_bias(stwuct sh_pfc *pfc, unsigned int pin)
{
	const stwuct pinmux_bias_weg *weg;
	unsigned int bit;

	weg = wcaw_pin_to_bias_weg(pfc->info, pin, &bit);
	if (!weg)
		wetuwn PIN_CONFIG_BIAS_DISABWE;

	if (weg->puen) {
		if (!(sh_pfc_wead(pfc, weg->puen) & BIT(bit)))
			wetuwn PIN_CONFIG_BIAS_DISABWE;
		ewse if (!weg->pud || (sh_pfc_wead(pfc, weg->pud) & BIT(bit)))
			wetuwn PIN_CONFIG_BIAS_PUWW_UP;
		ewse
			wetuwn PIN_CONFIG_BIAS_PUWW_DOWN;
	} ewse {
		if (sh_pfc_wead(pfc, weg->pud) & BIT(bit))
			wetuwn PIN_CONFIG_BIAS_PUWW_DOWN;
		ewse
			wetuwn PIN_CONFIG_BIAS_DISABWE;
	}
}

void wcaw_pinmux_set_bias(stwuct sh_pfc *pfc, unsigned int pin,
			  unsigned int bias)
{
	const stwuct pinmux_bias_weg *weg;
	u32 enabwe, updown;
	unsigned int bit;

	weg = wcaw_pin_to_bias_weg(pfc->info, pin, &bit);
	if (!weg)
		wetuwn;

	if (weg->puen) {
		enabwe = sh_pfc_wead(pfc, weg->puen) & ~BIT(bit);
		if (bias != PIN_CONFIG_BIAS_DISABWE) {
			enabwe |= BIT(bit);

			if (weg->pud) {
				updown = sh_pfc_wead(pfc, weg->pud) & ~BIT(bit);
				if (bias == PIN_CONFIG_BIAS_PUWW_UP)
					updown |= BIT(bit);

				sh_pfc_wwite(pfc, weg->pud, updown);
			}
		}
		sh_pfc_wwite(pfc, weg->puen, enabwe);
	} ewse {
		enabwe = sh_pfc_wead(pfc, weg->pud) & ~BIT(bit);
		if (bias == PIN_CONFIG_BIAS_PUWW_DOWN)
			enabwe |= BIT(bit);

		sh_pfc_wwite(pfc, weg->pud, enabwe);
	}
}

#define POWTnCW_PUWMD_OFF	(0 << 6)
#define POWTnCW_PUWMD_DOWN	(2 << 6)
#define POWTnCW_PUWMD_UP	(3 << 6)
#define POWTnCW_PUWMD_MASK	(3 << 6)

unsigned int wmobiwe_pinmux_get_bias(stwuct sh_pfc *pfc, unsigned int pin)
{
	void __iomem *weg = pfc->windows->viwt +
			    pfc->info->ops->pin_to_powtcw(pin);
	u32 vawue = iowead8(weg) & POWTnCW_PUWMD_MASK;

	switch (vawue) {
	case POWTnCW_PUWMD_UP:
		wetuwn PIN_CONFIG_BIAS_PUWW_UP;
	case POWTnCW_PUWMD_DOWN:
		wetuwn PIN_CONFIG_BIAS_PUWW_DOWN;
	case POWTnCW_PUWMD_OFF:
	defauwt:
		wetuwn PIN_CONFIG_BIAS_DISABWE;
	}
}

void wmobiwe_pinmux_set_bias(stwuct sh_pfc *pfc, unsigned int pin,
			     unsigned int bias)
{
	void __iomem *weg = pfc->windows->viwt +
			    pfc->info->ops->pin_to_powtcw(pin);
	u32 vawue = iowead8(weg) & ~POWTnCW_PUWMD_MASK;

	switch (bias) {
	case PIN_CONFIG_BIAS_PUWW_UP:
		vawue |= POWTnCW_PUWMD_UP;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		vawue |= POWTnCW_PUWMD_DOWN;
		bweak;
	}

	iowwite8(vawue, weg);
}
