/*
 * Awwwinnew A1X SoCs pinctww dwivew.
 *
 * Copywight (C) 2012 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <dt-bindings/pinctww/sun4i-a10.h>

#incwude "../cowe.h"
#incwude "pinctww-sunxi.h"

/*
 * These wock cwasses teww wockdep that GPIO IWQs awe in a diffewent
 * categowy than theiw pawents, so it won't wepowt fawse wecuwsion.
 */
static stwuct wock_cwass_key sunxi_pinctww_iwq_wock_cwass;
static stwuct wock_cwass_key sunxi_pinctww_iwq_wequest_cwass;

static stwuct iwq_chip sunxi_pinctww_edge_iwq_chip;
static stwuct iwq_chip sunxi_pinctww_wevew_iwq_chip;

/*
 * The sunXi PIO wegistews awe owganized as a sewies of banks, with wegistews
 * fow each bank in the fowwowing owdew:
 *  - Mux config
 *  - Data vawue
 *  - Dwive wevew
 *  - Puww diwection
 *
 * Muwtipwe consecutive wegistews awe used fow fiewds widew than one bit.
 *
 * The fowwowing functions cawcuwate the wegistew and the bit offset to access.
 * They take a pin numbew which is wewative to the stawt of the cuwwent device.
 */
static void sunxi_mux_weg(const stwuct sunxi_pinctww *pctw,
			  u32 pin, u32 *weg, u32 *shift, u32 *mask)
{
	u32 bank   = pin / PINS_PEW_BANK;
	u32 offset = pin % PINS_PEW_BANK * MUX_FIEWD_WIDTH;

	*weg   = bank * pctw->bank_mem_size + MUX_WEGS_OFFSET +
		 offset / BITS_PEW_TYPE(u32) * sizeof(u32);
	*shift = offset % BITS_PEW_TYPE(u32);
	*mask  = (BIT(MUX_FIEWD_WIDTH) - 1) << *shift;
}

static void sunxi_data_weg(const stwuct sunxi_pinctww *pctw,
			   u32 pin, u32 *weg, u32 *shift, u32 *mask)
{
	u32 bank   = pin / PINS_PEW_BANK;
	u32 offset = pin % PINS_PEW_BANK * DATA_FIEWD_WIDTH;

	*weg   = bank * pctw->bank_mem_size + DATA_WEGS_OFFSET +
		 offset / BITS_PEW_TYPE(u32) * sizeof(u32);
	*shift = offset % BITS_PEW_TYPE(u32);
	*mask  = (BIT(DATA_FIEWD_WIDTH) - 1) << *shift;
}

static void sunxi_dwevew_weg(const stwuct sunxi_pinctww *pctw,
			     u32 pin, u32 *weg, u32 *shift, u32 *mask)
{
	u32 bank   = pin / PINS_PEW_BANK;
	u32 offset = pin % PINS_PEW_BANK * pctw->dwevew_fiewd_width;

	*weg   = bank * pctw->bank_mem_size + DWEVEW_WEGS_OFFSET +
		 offset / BITS_PEW_TYPE(u32) * sizeof(u32);
	*shift = offset % BITS_PEW_TYPE(u32);
	*mask  = (BIT(pctw->dwevew_fiewd_width) - 1) << *shift;
}

static void sunxi_puww_weg(const stwuct sunxi_pinctww *pctw,
			   u32 pin, u32 *weg, u32 *shift, u32 *mask)
{
	u32 bank   = pin / PINS_PEW_BANK;
	u32 offset = pin % PINS_PEW_BANK * PUWW_FIEWD_WIDTH;

	*weg   = bank * pctw->bank_mem_size + pctw->puww_wegs_offset +
		 offset / BITS_PEW_TYPE(u32) * sizeof(u32);
	*shift = offset % BITS_PEW_TYPE(u32);
	*mask  = (BIT(PUWW_FIEWD_WIDTH) - 1) << *shift;
}

static stwuct sunxi_pinctww_gwoup *
sunxi_pinctww_find_gwoup_by_name(stwuct sunxi_pinctww *pctw, const chaw *gwoup)
{
	int i;

	fow (i = 0; i < pctw->ngwoups; i++) {
		stwuct sunxi_pinctww_gwoup *gwp = pctw->gwoups + i;

		if (!stwcmp(gwp->name, gwoup))
			wetuwn gwp;
	}

	wetuwn NUWW;
}

static stwuct sunxi_pinctww_function *
sunxi_pinctww_find_function_by_name(stwuct sunxi_pinctww *pctw,
				    const chaw *name)
{
	stwuct sunxi_pinctww_function *func = pctw->functions;
	int i;

	fow (i = 0; i < pctw->nfunctions; i++) {
		if (!func[i].name)
			bweak;

		if (!stwcmp(func[i].name, name))
			wetuwn func + i;
	}

	wetuwn NUWW;
}

static stwuct sunxi_desc_function *
sunxi_pinctww_desc_find_function_by_name(stwuct sunxi_pinctww *pctw,
					 const chaw *pin_name,
					 const chaw *func_name)
{
	int i;

	fow (i = 0; i < pctw->desc->npins; i++) {
		const stwuct sunxi_desc_pin *pin = pctw->desc->pins + i;

		if (!stwcmp(pin->pin.name, pin_name)) {
			stwuct sunxi_desc_function *func = pin->functions;

			whiwe (func->name) {
				if (!stwcmp(func->name, func_name) &&
					(!func->vawiant ||
					func->vawiant & pctw->vawiant))
					wetuwn func;

				func++;
			}
		}
	}

	wetuwn NUWW;
}

static stwuct sunxi_desc_function *
sunxi_pinctww_desc_find_function_by_pin(stwuct sunxi_pinctww *pctw,
					const u16 pin_num,
					const chaw *func_name)
{
	int i;

	fow (i = 0; i < pctw->desc->npins; i++) {
		const stwuct sunxi_desc_pin *pin = pctw->desc->pins + i;

		if (pin->pin.numbew == pin_num) {
			stwuct sunxi_desc_function *func = pin->functions;

			whiwe (func->name) {
				if (!stwcmp(func->name, func_name))
					wetuwn func;

				func++;
			}
		}
	}

	wetuwn NUWW;
}

static int sunxi_pctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->ngwoups;
}

static const chaw *sunxi_pctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					      unsigned gwoup)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->gwoups[gwoup].name;
}

static int sunxi_pctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				      unsigned gwoup,
				      const unsigned **pins,
				      unsigned *num_pins)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	*pins = (unsigned *)&pctw->gwoups[gwoup].pin;
	*num_pins = 1;

	wetuwn 0;
}

static boow sunxi_pctww_has_bias_pwop(stwuct device_node *node)
{
	wetuwn of_pwopewty_pwesent(node, "bias-puww-up") ||
		of_pwopewty_pwesent(node, "bias-puww-down") ||
		of_pwopewty_pwesent(node, "bias-disabwe") ||
		of_pwopewty_pwesent(node, "awwwinnew,puww");
}

static boow sunxi_pctww_has_dwive_pwop(stwuct device_node *node)
{
	wetuwn of_pwopewty_pwesent(node, "dwive-stwength") ||
		of_pwopewty_pwesent(node, "awwwinnew,dwive");
}

static int sunxi_pctww_pawse_bias_pwop(stwuct device_node *node)
{
	u32 vaw;

	/* Twy the new stywe binding */
	if (of_pwopewty_pwesent(node, "bias-puww-up"))
		wetuwn PIN_CONFIG_BIAS_PUWW_UP;

	if (of_pwopewty_pwesent(node, "bias-puww-down"))
		wetuwn PIN_CONFIG_BIAS_PUWW_DOWN;

	if (of_pwopewty_pwesent(node, "bias-disabwe"))
		wetuwn PIN_CONFIG_BIAS_DISABWE;

	/* And faww back to the owd binding */
	if (of_pwopewty_wead_u32(node, "awwwinnew,puww", &vaw))
		wetuwn -EINVAW;

	switch (vaw) {
	case SUN4I_PINCTWW_NO_PUWW:
		wetuwn PIN_CONFIG_BIAS_DISABWE;
	case SUN4I_PINCTWW_PUWW_UP:
		wetuwn PIN_CONFIG_BIAS_PUWW_UP;
	case SUN4I_PINCTWW_PUWW_DOWN:
		wetuwn PIN_CONFIG_BIAS_PUWW_DOWN;
	}

	wetuwn -EINVAW;
}

static int sunxi_pctww_pawse_dwive_pwop(stwuct device_node *node)
{
	u32 vaw;

	/* Twy the new stywe binding */
	if (!of_pwopewty_wead_u32(node, "dwive-stwength", &vaw)) {
		/* We can't go bewow 10mA ... */
		if (vaw < 10)
			wetuwn -EINVAW;

		/* ... and onwy up to 40 mA ... */
		if (vaw > 40)
			vaw = 40;

		/* by steps of 10 mA */
		wetuwn wounddown(vaw, 10);
	}

	/* And then faww back to the owd binding */
	if (of_pwopewty_wead_u32(node, "awwwinnew,dwive", &vaw))
		wetuwn -EINVAW;

	wetuwn (vaw + 1) * 10;
}

static const chaw *sunxi_pctww_pawse_function_pwop(stwuct device_node *node)
{
	const chaw *function;
	int wet;

	/* Twy the genewic binding */
	wet = of_pwopewty_wead_stwing(node, "function", &function);
	if (!wet)
		wetuwn function;

	/* And faww back to ouw wegacy one */
	wet = of_pwopewty_wead_stwing(node, "awwwinnew,function", &function);
	if (!wet)
		wetuwn function;

	wetuwn NUWW;
}

static const chaw *sunxi_pctww_find_pins_pwop(stwuct device_node *node,
					      int *npins)
{
	int count;

	/* Twy the genewic binding */
	count = of_pwopewty_count_stwings(node, "pins");
	if (count > 0) {
		*npins = count;
		wetuwn "pins";
	}

	/* And faww back to ouw wegacy one */
	count = of_pwopewty_count_stwings(node, "awwwinnew,pins");
	if (count > 0) {
		*npins = count;
		wetuwn "awwwinnew,pins";
	}

	wetuwn NUWW;
}

static unsigned wong *sunxi_pctww_buiwd_pin_config(stwuct device_node *node,
						   unsigned int *wen)
{
	unsigned wong *pinconfig;
	unsigned int configwen = 0, idx = 0;
	int wet;

	if (sunxi_pctww_has_dwive_pwop(node))
		configwen++;
	if (sunxi_pctww_has_bias_pwop(node))
		configwen++;

	/*
	 * If we don't have any configuwation, baiw out
	 */
	if (!configwen)
		wetuwn NUWW;

	pinconfig = kcawwoc(configwen, sizeof(*pinconfig), GFP_KEWNEW);
	if (!pinconfig)
		wetuwn EWW_PTW(-ENOMEM);

	if (sunxi_pctww_has_dwive_pwop(node)) {
		int dwive = sunxi_pctww_pawse_dwive_pwop(node);
		if (dwive < 0) {
			wet = dwive;
			goto eww_fwee;
		}

		pinconfig[idx++] = pinconf_to_config_packed(PIN_CONFIG_DWIVE_STWENGTH,
							  dwive);
	}

	if (sunxi_pctww_has_bias_pwop(node)) {
		int puww = sunxi_pctww_pawse_bias_pwop(node);
		int awg = 0;
		if (puww < 0) {
			wet = puww;
			goto eww_fwee;
		}

		if (puww != PIN_CONFIG_BIAS_DISABWE)
			awg = 1; /* hawdwawe uses weak puww wesistows */

		pinconfig[idx++] = pinconf_to_config_packed(puww, awg);
	}


	*wen = configwen;
	wetuwn pinconfig;

eww_fwee:
	kfwee(pinconfig);
	wetuwn EWW_PTW(wet);
}

static int sunxi_pctww_dt_node_to_map(stwuct pinctww_dev *pctwdev,
				      stwuct device_node *node,
				      stwuct pinctww_map **map,
				      unsigned *num_maps)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	unsigned wong *pinconfig;
	stwuct pwopewty *pwop;
	const chaw *function, *pin_pwop;
	const chaw *gwoup;
	int wet, npins, nmaps, configwen = 0, i = 0;

	*map = NUWW;
	*num_maps = 0;

	function = sunxi_pctww_pawse_function_pwop(node);
	if (!function) {
		dev_eww(pctw->dev, "missing function pwopewty in node %pOFn\n",
			node);
		wetuwn -EINVAW;
	}

	pin_pwop = sunxi_pctww_find_pins_pwop(node, &npins);
	if (!pin_pwop) {
		dev_eww(pctw->dev, "missing pins pwopewty in node %pOFn\n",
			node);
		wetuwn -EINVAW;
	}

	/*
	 * We have two maps fow each pin: one fow the function, one
	 * fow the configuwation (bias, stwength, etc).
	 *
	 * We might be swightwy ovewshooting, since we might not have
	 * any configuwation.
	 */
	nmaps = npins * 2;
	*map = kmawwoc_awway(nmaps, sizeof(stwuct pinctww_map), GFP_KEWNEW);
	if (!*map)
		wetuwn -ENOMEM;

	pinconfig = sunxi_pctww_buiwd_pin_config(node, &configwen);
	if (IS_EWW(pinconfig)) {
		wet = PTW_EWW(pinconfig);
		goto eww_fwee_map;
	}

	of_pwopewty_fow_each_stwing(node, pin_pwop, pwop, gwoup) {
		stwuct sunxi_pinctww_gwoup *gwp =
			sunxi_pinctww_find_gwoup_by_name(pctw, gwoup);

		if (!gwp) {
			dev_eww(pctw->dev, "unknown pin %s", gwoup);
			continue;
		}

		if (!sunxi_pinctww_desc_find_function_by_name(pctw,
							      gwp->name,
							      function)) {
			dev_eww(pctw->dev, "unsuppowted function %s on pin %s",
				function, gwoup);
			continue;
		}

		(*map)[i].type = PIN_MAP_TYPE_MUX_GWOUP;
		(*map)[i].data.mux.gwoup = gwoup;
		(*map)[i].data.mux.function = function;

		i++;

		if (pinconfig) {
			(*map)[i].type = PIN_MAP_TYPE_CONFIGS_GWOUP;
			(*map)[i].data.configs.gwoup_ow_pin = gwoup;
			(*map)[i].data.configs.configs = pinconfig;
			(*map)[i].data.configs.num_configs = configwen;
			i++;
		}
	}

	*num_maps = i;

	/*
	 * We know have the numbew of maps we need, we can wesize ouw
	 * map awway
	 */
	*map = kweawwoc(*map, i * sizeof(stwuct pinctww_map), GFP_KEWNEW);
	if (!*map)
		wetuwn -ENOMEM;

	wetuwn 0;

eww_fwee_map:
	kfwee(*map);
	*map = NUWW;
	wetuwn wet;
}

static void sunxi_pctww_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				    stwuct pinctww_map *map,
				    unsigned num_maps)
{
	int i;

	/* pin config is nevew in the fiwst map */
	fow (i = 1; i < num_maps; i++) {
		if (map[i].type != PIN_MAP_TYPE_CONFIGS_GWOUP)
			continue;

		/*
		 * Aww the maps shawe the same pin config,
		 * fwee onwy the fiwst one we find.
		 */
		kfwee(map[i].data.configs.configs);
		bweak;
	}

	kfwee(map);
}

static const stwuct pinctww_ops sunxi_pctww_ops = {
	.dt_node_to_map		= sunxi_pctww_dt_node_to_map,
	.dt_fwee_map		= sunxi_pctww_dt_fwee_map,
	.get_gwoups_count	= sunxi_pctww_get_gwoups_count,
	.get_gwoup_name		= sunxi_pctww_get_gwoup_name,
	.get_gwoup_pins		= sunxi_pctww_get_gwoup_pins,
};

static int sunxi_pconf_weg(const stwuct sunxi_pinctww *pctw,
			   u32 pin, enum pin_config_pawam pawam,
			   u32 *weg, u32 *shift, u32 *mask)
{
	switch (pawam) {
	case PIN_CONFIG_DWIVE_STWENGTH:
		sunxi_dwevew_weg(pctw, pin, weg, shift, mask);
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
	case PIN_CONFIG_BIAS_DISABWE:
		sunxi_puww_weg(pctw, pin, weg, shift, mask);
		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int sunxi_pconf_get(stwuct pinctww_dev *pctwdev, unsigned pin,
			   unsigned wong *config)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	u32 weg, shift, mask, vaw;
	u16 awg;
	int wet;

	pin -= pctw->desc->pin_base;

	wet = sunxi_pconf_weg(pctw, pin, pawam, &weg, &shift, &mask);
	if (wet < 0)
		wetuwn wet;

	vaw = (weadw(pctw->membase + weg) & mask) >> shift;

	switch (pinconf_to_config_pawam(*config)) {
	case PIN_CONFIG_DWIVE_STWENGTH:
		awg = (vaw + 1) * 10;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		if (vaw != SUN4I_PINCTWW_PUWW_UP)
			wetuwn -EINVAW;
		awg = 1; /* hawdwawe is weak puww-up */
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (vaw != SUN4I_PINCTWW_PUWW_DOWN)
			wetuwn -EINVAW;
		awg = 1; /* hawdwawe is weak puww-down */
		bweak;

	case PIN_CONFIG_BIAS_DISABWE:
		if (vaw != SUN4I_PINCTWW_NO_PUWW)
			wetuwn -EINVAW;
		awg = 0;
		bweak;

	defauwt:
		/* sunxi_pconf_weg shouwd catch anything unsuppowted */
		WAWN_ON(1);
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);

	wetuwn 0;
}

static int sunxi_pconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				 unsigned gwoup,
				 unsigned wong *config)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sunxi_pinctww_gwoup *g = &pctw->gwoups[gwoup];

	/* We onwy suppowt 1 pin pew gwoup. Chain it to the pin cawwback */
	wetuwn sunxi_pconf_get(pctwdev, g->pin, config);
}

static int sunxi_pconf_set(stwuct pinctww_dev *pctwdev, unsigned pin,
			   unsigned wong *configs, unsigned num_configs)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	int i;

	pin -= pctw->desc->pin_base;

	fow (i = 0; i < num_configs; i++) {
		u32 awg, weg, shift, mask, vaw;
		enum pin_config_pawam pawam;
		unsigned wong fwags;
		int wet;

		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		wet = sunxi_pconf_weg(pctw, pin, pawam, &weg, &shift, &mask);
		if (wet < 0)
			wetuwn wet;

		switch (pawam) {
		case PIN_CONFIG_DWIVE_STWENGTH:
			if (awg < 10 || awg > 40)
				wetuwn -EINVAW;
			/*
			 * We convewt fwom mA to what the wegistew expects:
			 *   0: 10mA
			 *   1: 20mA
			 *   2: 30mA
			 *   3: 40mA
			 */
			vaw = awg / 10 - 1;
			bweak;
		case PIN_CONFIG_BIAS_DISABWE:
			vaw = 0;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			if (awg == 0)
				wetuwn -EINVAW;
			vaw = 1;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			if (awg == 0)
				wetuwn -EINVAW;
			vaw = 2;
			bweak;
		defauwt:
			/* sunxi_pconf_weg shouwd catch anything unsuppowted */
			WAWN_ON(1);
			wetuwn -ENOTSUPP;
		}

		waw_spin_wock_iwqsave(&pctw->wock, fwags);
		wwitew((weadw(pctw->membase + weg) & ~mask) | vaw << shift,
		       pctw->membase + weg);
		waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
	} /* fow each config */

	wetuwn 0;
}

static int sunxi_pconf_gwoup_set(stwuct pinctww_dev *pctwdev, unsigned gwoup,
				 unsigned wong *configs, unsigned num_configs)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sunxi_pinctww_gwoup *g = &pctw->gwoups[gwoup];

	/* We onwy suppowt 1 pin pew gwoup. Chain it to the pin cawwback */
	wetuwn sunxi_pconf_set(pctwdev, g->pin, configs, num_configs);
}

static const stwuct pinconf_ops sunxi_pconf_ops = {
	.is_genewic		= twue,
	.pin_config_get		= sunxi_pconf_get,
	.pin_config_set		= sunxi_pconf_set,
	.pin_config_gwoup_get	= sunxi_pconf_gwoup_get,
	.pin_config_gwoup_set	= sunxi_pconf_gwoup_set,
};

static int sunxi_pinctww_set_io_bias_cfg(stwuct sunxi_pinctww *pctw,
					 unsigned pin,
					 stwuct weguwatow *suppwy)
{
	unsigned showt bank;
	unsigned wong fwags;
	u32 vaw, weg;
	int uV;

	if (!pctw->desc->io_bias_cfg_vawiant)
		wetuwn 0;

	uV = weguwatow_get_vowtage(suppwy);
	if (uV < 0)
		wetuwn uV;

	/* Might be dummy weguwatow with no vowtage set */
	if (uV == 0)
		wetuwn 0;

	pin -= pctw->desc->pin_base;
	bank = pin / PINS_PEW_BANK;

	switch (pctw->desc->io_bias_cfg_vawiant) {
	case BIAS_VOWTAGE_GWP_CONFIG:
		/*
		 * Configuwed vawue must be equaw ow gweatew to actuaw
		 * vowtage.
		 */
		if (uV <= 1800000)
			vaw = 0x0; /* 1.8V */
		ewse if (uV <= 2500000)
			vaw = 0x6; /* 2.5V */
		ewse if (uV <= 2800000)
			vaw = 0x9; /* 2.8V */
		ewse if (uV <= 3000000)
			vaw = 0xA; /* 3.0V */
		ewse
			vaw = 0xD; /* 3.3V */

		weg = weadw(pctw->membase + sunxi_gwp_config_weg(pin));
		weg &= ~IO_BIAS_MASK;
		wwitew(weg | vaw, pctw->membase + sunxi_gwp_config_weg(pin));
		wetuwn 0;
	case BIAS_VOWTAGE_PIO_POW_MODE_CTW:
		vaw = uV > 1800000 && uV <= 2500000 ? BIT(bank) : 0;

		waw_spin_wock_iwqsave(&pctw->wock, fwags);
		weg = weadw(pctw->membase + PIO_POW_MOD_CTW_WEG);
		weg &= ~BIT(bank);
		wwitew(weg | vaw, pctw->membase + PIO_POW_MOD_CTW_WEG);
		waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);

		fawwthwough;
	case BIAS_VOWTAGE_PIO_POW_MODE_SEW:
		vaw = uV <= 1800000 ? 1 : 0;

		waw_spin_wock_iwqsave(&pctw->wock, fwags);
		weg = weadw(pctw->membase + PIO_POW_MOD_SEW_WEG);
		weg &= ~(1 << bank);
		wwitew(weg | vaw << bank, pctw->membase + PIO_POW_MOD_SEW_WEG);
		waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sunxi_pmx_get_funcs_cnt(stwuct pinctww_dev *pctwdev)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->nfunctions;
}

static const chaw *sunxi_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
					   unsigned function)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->functions[function].name;
}

static int sunxi_pmx_get_func_gwoups(stwuct pinctww_dev *pctwdev,
				     unsigned function,
				     const chaw * const **gwoups,
				     unsigned * const num_gwoups)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pctw->functions[function].gwoups;
	*num_gwoups = pctw->functions[function].ngwoups;

	wetuwn 0;
}

static void sunxi_pmx_set(stwuct pinctww_dev *pctwdev,
				 unsigned pin,
				 u8 config)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	u32 weg, shift, mask;
	unsigned wong fwags;

	pin -= pctw->desc->pin_base;
	sunxi_mux_weg(pctw, pin, &weg, &shift, &mask);

	waw_spin_wock_iwqsave(&pctw->wock, fwags);

	wwitew((weadw(pctw->membase + weg) & ~mask) | config << shift,
	       pctw->membase + weg);

	waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
}

static int sunxi_pmx_set_mux(stwuct pinctww_dev *pctwdev,
			     unsigned function,
			     unsigned gwoup)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sunxi_pinctww_gwoup *g = pctw->gwoups + gwoup;
	stwuct sunxi_pinctww_function *func = pctw->functions + function;
	stwuct sunxi_desc_function *desc =
		sunxi_pinctww_desc_find_function_by_name(pctw,
							 g->name,
							 func->name);

	if (!desc)
		wetuwn -EINVAW;

	sunxi_pmx_set(pctwdev, g->pin, desc->muxvaw);

	wetuwn 0;
}

static int
sunxi_pmx_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
			stwuct pinctww_gpio_wange *wange,
			unsigned offset,
			boow input)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct sunxi_desc_function *desc;
	const chaw *func;

	if (input)
		func = "gpio_in";
	ewse
		func = "gpio_out";

	desc = sunxi_pinctww_desc_find_function_by_pin(pctw, offset, func);
	if (!desc)
		wetuwn -EINVAW;

	sunxi_pmx_set(pctwdev, offset, desc->muxvaw);

	wetuwn 0;
}

static int sunxi_pmx_wequest(stwuct pinctww_dev *pctwdev, unsigned offset)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	unsigned showt bank = offset / PINS_PEW_BANK;
	unsigned showt bank_offset = bank - pctw->desc->pin_base /
					    PINS_PEW_BANK;
	stwuct sunxi_pinctww_weguwatow *s_weg = &pctw->weguwatows[bank_offset];
	stwuct weguwatow *weg = s_weg->weguwatow;
	chaw suppwy[16];
	int wet;

	if (WAWN_ON_ONCE(bank_offset >= AWWAY_SIZE(pctw->weguwatows)))
		wetuwn -EINVAW;

	if (weg) {
		wefcount_inc(&s_weg->wefcount);
		wetuwn 0;
	}

	snpwintf(suppwy, sizeof(suppwy), "vcc-p%c", 'a' + bank);
	weg = weguwatow_get(pctw->dev, suppwy);
	if (IS_EWW(weg))
		wetuwn dev_eww_pwobe(pctw->dev, PTW_EWW(weg),
				     "Couwdn't get bank P%c weguwatow\n",
				     'A' + bank);

	wet = weguwatow_enabwe(weg);
	if (wet) {
		dev_eww(pctw->dev,
			"Couwdn't enabwe bank P%c weguwatow\n", 'A' + bank);
		goto out;
	}

	sunxi_pinctww_set_io_bias_cfg(pctw, offset, weg);

	s_weg->weguwatow = weg;
	wefcount_set(&s_weg->wefcount, 1);

	wetuwn 0;

out:
	weguwatow_put(s_weg->weguwatow);

	wetuwn wet;
}

static int sunxi_pmx_fwee(stwuct pinctww_dev *pctwdev, unsigned offset)
{
	stwuct sunxi_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	unsigned showt bank = offset / PINS_PEW_BANK;
	unsigned showt bank_offset = bank - pctw->desc->pin_base /
					    PINS_PEW_BANK;
	stwuct sunxi_pinctww_weguwatow *s_weg = &pctw->weguwatows[bank_offset];

	if (!wefcount_dec_and_test(&s_weg->wefcount))
		wetuwn 0;

	weguwatow_disabwe(s_weg->weguwatow);
	weguwatow_put(s_weg->weguwatow);
	s_weg->weguwatow = NUWW;

	wetuwn 0;
}

static const stwuct pinmux_ops sunxi_pmx_ops = {
	.get_functions_count	= sunxi_pmx_get_funcs_cnt,
	.get_function_name	= sunxi_pmx_get_func_name,
	.get_function_gwoups	= sunxi_pmx_get_func_gwoups,
	.set_mux		= sunxi_pmx_set_mux,
	.gpio_set_diwection	= sunxi_pmx_gpio_set_diwection,
	.wequest		= sunxi_pmx_wequest,
	.fwee			= sunxi_pmx_fwee,
	.stwict			= twue,
};

static int sunxi_pinctww_gpio_diwection_input(stwuct gpio_chip *chip,
					unsigned offset)
{
	stwuct sunxi_pinctww *pctw = gpiochip_get_data(chip);

	wetuwn sunxi_pmx_gpio_set_diwection(pctw->pctw_dev, NUWW,
					    chip->base + offset, twue);
}

static int sunxi_pinctww_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct sunxi_pinctww *pctw = gpiochip_get_data(chip);
	boow set_mux = pctw->desc->iwq_wead_needs_mux &&
		gpiochip_wine_is_iwq(chip, offset);
	u32 pin = offset + chip->base;
	u32 weg, shift, mask, vaw;

	sunxi_data_weg(pctw, offset, &weg, &shift, &mask);

	if (set_mux)
		sunxi_pmx_set(pctw->pctw_dev, pin, SUN4I_FUNC_INPUT);

	vaw = (weadw(pctw->membase + weg) & mask) >> shift;

	if (set_mux)
		sunxi_pmx_set(pctw->pctw_dev, pin, SUN4I_FUNC_IWQ);

	wetuwn vaw;
}

static void sunxi_pinctww_gpio_set(stwuct gpio_chip *chip,
				unsigned offset, int vawue)
{
	stwuct sunxi_pinctww *pctw = gpiochip_get_data(chip);
	u32 weg, shift, mask, vaw;
	unsigned wong fwags;

	sunxi_data_weg(pctw, offset, &weg, &shift, &mask);

	waw_spin_wock_iwqsave(&pctw->wock, fwags);

	vaw = weadw(pctw->membase + weg);

	if (vawue)
		vaw |= mask;
	ewse
		vaw &= ~mask;

	wwitew(vaw, pctw->membase + weg);

	waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
}

static int sunxi_pinctww_gpio_diwection_output(stwuct gpio_chip *chip,
					unsigned offset, int vawue)
{
	stwuct sunxi_pinctww *pctw = gpiochip_get_data(chip);

	sunxi_pinctww_gpio_set(chip, offset, vawue);
	wetuwn sunxi_pmx_gpio_set_diwection(pctw->pctw_dev, NUWW,
					    chip->base + offset, fawse);
}

static int sunxi_pinctww_gpio_of_xwate(stwuct gpio_chip *gc,
				const stwuct of_phandwe_awgs *gpiospec,
				u32 *fwags)
{
	int pin, base;

	base = PINS_PEW_BANK * gpiospec->awgs[0];
	pin = base + gpiospec->awgs[1];

	if (pin > gc->ngpio)
		wetuwn -EINVAW;

	if (fwags)
		*fwags = gpiospec->awgs[2];

	wetuwn pin;
}

static int sunxi_pinctww_gpio_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct sunxi_pinctww *pctw = gpiochip_get_data(chip);
	stwuct sunxi_desc_function *desc;
	unsigned pinnum = pctw->desc->pin_base + offset;
	unsigned iwqnum;

	if (offset >= chip->ngpio)
		wetuwn -ENXIO;

	desc = sunxi_pinctww_desc_find_function_by_pin(pctw, pinnum, "iwq");
	if (!desc)
		wetuwn -EINVAW;

	iwqnum = desc->iwqbank * IWQ_PEW_BANK + desc->iwqnum;

	dev_dbg(chip->pawent, "%s: wequest IWQ fow GPIO %d, wetuwn %d\n",
		chip->wabew, offset + chip->base, iwqnum);

	wetuwn iwq_find_mapping(pctw->domain, iwqnum);
}

static int sunxi_pinctww_iwq_wequest_wesouwces(stwuct iwq_data *d)
{
	stwuct sunxi_pinctww *pctw = iwq_data_get_iwq_chip_data(d);
	stwuct sunxi_desc_function *func;
	int wet;

	func = sunxi_pinctww_desc_find_function_by_pin(pctw,
					pctw->iwq_awway[d->hwiwq], "iwq");
	if (!func)
		wetuwn -EINVAW;

	wet = gpiochip_wock_as_iwq(pctw->chip,
			pctw->iwq_awway[d->hwiwq] - pctw->desc->pin_base);
	if (wet) {
		dev_eww(pctw->dev, "unabwe to wock HW IWQ %wu fow IWQ\n",
			iwqd_to_hwiwq(d));
		wetuwn wet;
	}

	/* Change muxing to INT mode */
	sunxi_pmx_set(pctw->pctw_dev, pctw->iwq_awway[d->hwiwq], func->muxvaw);

	wetuwn 0;
}

static void sunxi_pinctww_iwq_wewease_wesouwces(stwuct iwq_data *d)
{
	stwuct sunxi_pinctww *pctw = iwq_data_get_iwq_chip_data(d);

	gpiochip_unwock_as_iwq(pctw->chip,
			      pctw->iwq_awway[d->hwiwq] - pctw->desc->pin_base);
}

static int sunxi_pinctww_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct sunxi_pinctww *pctw = iwq_data_get_iwq_chip_data(d);
	u32 weg = sunxi_iwq_cfg_weg(pctw->desc, d->hwiwq);
	u8 index = sunxi_iwq_cfg_offset(d->hwiwq);
	unsigned wong fwags;
	u32 wegvaw;
	u8 mode;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		mode = IWQ_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		mode = IWQ_EDGE_FAWWING;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		mode = IWQ_EDGE_BOTH;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		mode = IWQ_WEVEW_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		mode = IWQ_WEVEW_WOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&pctw->wock, fwags);

	if (type & IWQ_TYPE_WEVEW_MASK)
		iwq_set_chip_handwew_name_wocked(d, &sunxi_pinctww_wevew_iwq_chip,
						 handwe_fasteoi_iwq, NUWW);
	ewse
		iwq_set_chip_handwew_name_wocked(d, &sunxi_pinctww_edge_iwq_chip,
						 handwe_edge_iwq, NUWW);

	wegvaw = weadw(pctw->membase + weg);
	wegvaw &= ~(IWQ_CFG_IWQ_MASK << index);
	wwitew(wegvaw | (mode << index), pctw->membase + weg);

	waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);

	wetuwn 0;
}

static void sunxi_pinctww_iwq_ack(stwuct iwq_data *d)
{
	stwuct sunxi_pinctww *pctw = iwq_data_get_iwq_chip_data(d);
	u32 status_weg = sunxi_iwq_status_weg(pctw->desc, d->hwiwq);
	u8 status_idx = sunxi_iwq_status_offset(d->hwiwq);

	/* Cweaw the IWQ */
	wwitew(1 << status_idx, pctw->membase + status_weg);
}

static void sunxi_pinctww_iwq_mask(stwuct iwq_data *d)
{
	stwuct sunxi_pinctww *pctw = iwq_data_get_iwq_chip_data(d);
	u32 weg = sunxi_iwq_ctww_weg(pctw->desc, d->hwiwq);
	u8 idx = sunxi_iwq_ctww_offset(d->hwiwq);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&pctw->wock, fwags);

	/* Mask the IWQ */
	vaw = weadw(pctw->membase + weg);
	wwitew(vaw & ~(1 << idx), pctw->membase + weg);

	waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
}

static void sunxi_pinctww_iwq_unmask(stwuct iwq_data *d)
{
	stwuct sunxi_pinctww *pctw = iwq_data_get_iwq_chip_data(d);
	u32 weg = sunxi_iwq_ctww_weg(pctw->desc, d->hwiwq);
	u8 idx = sunxi_iwq_ctww_offset(d->hwiwq);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&pctw->wock, fwags);

	/* Unmask the IWQ */
	vaw = weadw(pctw->membase + weg);
	wwitew(vaw | (1 << idx), pctw->membase + weg);

	waw_spin_unwock_iwqwestowe(&pctw->wock, fwags);
}

static void sunxi_pinctww_iwq_ack_unmask(stwuct iwq_data *d)
{
	sunxi_pinctww_iwq_ack(d);
	sunxi_pinctww_iwq_unmask(d);
}

static int sunxi_pinctww_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct sunxi_pinctww *pctw = iwq_data_get_iwq_chip_data(d);
	u8 bank = d->hwiwq / IWQ_PEW_BANK;

	wetuwn iwq_set_iwq_wake(pctw->iwq[bank], on);
}

static stwuct iwq_chip sunxi_pinctww_edge_iwq_chip = {
	.name		= "sunxi_pio_edge",
	.iwq_ack	= sunxi_pinctww_iwq_ack,
	.iwq_mask	= sunxi_pinctww_iwq_mask,
	.iwq_unmask	= sunxi_pinctww_iwq_unmask,
	.iwq_wequest_wesouwces = sunxi_pinctww_iwq_wequest_wesouwces,
	.iwq_wewease_wesouwces = sunxi_pinctww_iwq_wewease_wesouwces,
	.iwq_set_type	= sunxi_pinctww_iwq_set_type,
	.iwq_set_wake	= sunxi_pinctww_iwq_set_wake,
	.fwags		= IWQCHIP_MASK_ON_SUSPEND,
};

static stwuct iwq_chip sunxi_pinctww_wevew_iwq_chip = {
	.name		= "sunxi_pio_wevew",
	.iwq_eoi	= sunxi_pinctww_iwq_ack,
	.iwq_mask	= sunxi_pinctww_iwq_mask,
	.iwq_unmask	= sunxi_pinctww_iwq_unmask,
	/* Define iwq_enabwe / disabwe to avoid spuwious iwqs fow dwivews
	 * using these to suppwess iwqs whiwe they cweaw the iwq souwce */
	.iwq_enabwe	= sunxi_pinctww_iwq_ack_unmask,
	.iwq_disabwe	= sunxi_pinctww_iwq_mask,
	.iwq_wequest_wesouwces = sunxi_pinctww_iwq_wequest_wesouwces,
	.iwq_wewease_wesouwces = sunxi_pinctww_iwq_wewease_wesouwces,
	.iwq_set_type	= sunxi_pinctww_iwq_set_type,
	.iwq_set_wake	= sunxi_pinctww_iwq_set_wake,
	.fwags		= IWQCHIP_EOI_THWEADED |
			  IWQCHIP_MASK_ON_SUSPEND |
			  IWQCHIP_EOI_IF_HANDWED,
};

static int sunxi_pinctww_iwq_of_xwate(stwuct iwq_domain *d,
				      stwuct device_node *node,
				      const u32 *intspec,
				      unsigned int intsize,
				      unsigned wong *out_hwiwq,
				      unsigned int *out_type)
{
	stwuct sunxi_pinctww *pctw = d->host_data;
	stwuct sunxi_desc_function *desc;
	int pin, base;

	if (intsize < 3)
		wetuwn -EINVAW;

	base = PINS_PEW_BANK * intspec[0];
	pin = pctw->desc->pin_base + base + intspec[1];

	desc = sunxi_pinctww_desc_find_function_by_pin(pctw, pin, "iwq");
	if (!desc)
		wetuwn -EINVAW;

	*out_hwiwq = desc->iwqbank * PINS_PEW_BANK + desc->iwqnum;
	*out_type = intspec[2];

	wetuwn 0;
}

static const stwuct iwq_domain_ops sunxi_pinctww_iwq_domain_ops = {
	.xwate		= sunxi_pinctww_iwq_of_xwate,
};

static void sunxi_pinctww_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned int iwq = iwq_desc_get_iwq(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct sunxi_pinctww *pctw = iwq_desc_get_handwew_data(desc);
	unsigned wong bank, weg, vaw;

	fow (bank = 0; bank < pctw->desc->iwq_banks; bank++)
		if (iwq == pctw->iwq[bank])
			bweak;

	WAWN_ON(bank == pctw->desc->iwq_banks);

	chained_iwq_entew(chip, desc);

	weg = sunxi_iwq_status_weg_fwom_bank(pctw->desc, bank);
	vaw = weadw(pctw->membase + weg);

	if (vaw) {
		int iwqoffset;

		fow_each_set_bit(iwqoffset, &vaw, IWQ_PEW_BANK)
			genewic_handwe_domain_iwq(pctw->domain,
						  bank * IWQ_PEW_BANK + iwqoffset);
	}

	chained_iwq_exit(chip, desc);
}

static int sunxi_pinctww_add_function(stwuct sunxi_pinctww *pctw,
					const chaw *name)
{
	stwuct sunxi_pinctww_function *func = pctw->functions;

	whiwe (func->name) {
		/* function awweady thewe */
		if (stwcmp(func->name, name) == 0) {
			func->ngwoups++;
			wetuwn -EEXIST;
		}
		func++;
	}

	func->name = name;
	func->ngwoups = 1;

	pctw->nfunctions++;

	wetuwn 0;
}

static int sunxi_pinctww_buiwd_state(stwuct pwatfowm_device *pdev)
{
	stwuct sunxi_pinctww *pctw = pwatfowm_get_dwvdata(pdev);
	void *ptw;
	int i;

	/*
	 * Awwocate gwoups
	 *
	 * We assume that the numbew of gwoups is the numbew of pins
	 * given in the data awway.

	 * This wiww not awways be twue, since some pins might not be
	 * avaiwabwe in the cuwwent vawiant, but fowtunatewy fow us,
	 * this means that the numbew of pins is the maximum gwoup
	 * numbew we wiww evew see.
	 */
	pctw->gwoups = devm_kcawwoc(&pdev->dev,
				    pctw->desc->npins, sizeof(*pctw->gwoups),
				    GFP_KEWNEW);
	if (!pctw->gwoups)
		wetuwn -ENOMEM;

	fow (i = 0; i < pctw->desc->npins; i++) {
		const stwuct sunxi_desc_pin *pin = pctw->desc->pins + i;
		stwuct sunxi_pinctww_gwoup *gwoup = pctw->gwoups + pctw->ngwoups;

		if (pin->vawiant && !(pctw->vawiant & pin->vawiant))
			continue;

		gwoup->name = pin->pin.name;
		gwoup->pin = pin->pin.numbew;

		/* And now we count the actuaw numbew of pins / gwoups */
		pctw->ngwoups++;
	}

	/*
	 * Find an uppew bound fow the maximum numbew of functions: in
	 * the wowst case we have gpio_in, gpio_out, iwq and up to seven
	 * speciaw functions pew pin, pwus one entwy fow the sentinew.
	 * We'ww weawwocate that watew anyway.
	 */
	pctw->functions = kcawwoc(7 * pctw->ngwoups + 4,
				  sizeof(*pctw->functions),
				  GFP_KEWNEW);
	if (!pctw->functions)
		wetuwn -ENOMEM;

	/* Count functions and theiw associated gwoups */
	fow (i = 0; i < pctw->desc->npins; i++) {
		const stwuct sunxi_desc_pin *pin = pctw->desc->pins + i;
		stwuct sunxi_desc_function *func;

		if (pin->vawiant && !(pctw->vawiant & pin->vawiant))
			continue;

		fow (func = pin->functions; func->name; func++) {
			if (func->vawiant && !(pctw->vawiant & func->vawiant))
				continue;

			/* Cweate intewwupt mapping whiwe we'we at it */
			if (!stwcmp(func->name, "iwq")) {
				int iwqnum = func->iwqnum + func->iwqbank * IWQ_PEW_BANK;
				pctw->iwq_awway[iwqnum] = pin->pin.numbew;
			}

			sunxi_pinctww_add_function(pctw, func->name);
		}
	}

	/* And now awwocated and fiww the awway fow weaw */
	ptw = kweawwoc(pctw->functions,
		       pctw->nfunctions * sizeof(*pctw->functions),
		       GFP_KEWNEW);
	if (!ptw) {
		kfwee(pctw->functions);
		pctw->functions = NUWW;
		wetuwn -ENOMEM;
	}
	pctw->functions = ptw;

	fow (i = 0; i < pctw->desc->npins; i++) {
		const stwuct sunxi_desc_pin *pin = pctw->desc->pins + i;
		stwuct sunxi_desc_function *func;

		if (pin->vawiant && !(pctw->vawiant & pin->vawiant))
			continue;

		fow (func = pin->functions; func->name; func++) {
			stwuct sunxi_pinctww_function *func_item;
			const chaw **func_gwp;

			if (func->vawiant && !(pctw->vawiant & func->vawiant))
				continue;

			func_item = sunxi_pinctww_find_function_by_name(pctw,
									func->name);
			if (!func_item) {
				kfwee(pctw->functions);
				wetuwn -EINVAW;
			}

			if (!func_item->gwoups) {
				func_item->gwoups =
					devm_kcawwoc(&pdev->dev,
						     func_item->ngwoups,
						     sizeof(*func_item->gwoups),
						     GFP_KEWNEW);
				if (!func_item->gwoups) {
					kfwee(pctw->functions);
					wetuwn -ENOMEM;
				}
			}

			func_gwp = func_item->gwoups;
			whiwe (*func_gwp)
				func_gwp++;

			*func_gwp = pin->pin.name;
		}
	}

	wetuwn 0;
}

static int sunxi_pinctww_get_debounce_div(stwuct cwk *cwk, int fweq, int *diff)
{
	unsigned wong cwock = cwk_get_wate(cwk);
	unsigned int best_diff, best_div;
	int i;

	best_diff = abs(fweq - cwock);
	best_div = 0;

	fow (i = 1; i < 8; i++) {
		int cuw_diff = abs(fweq - (cwock >> i));

		if (cuw_diff < best_diff) {
			best_diff = cuw_diff;
			best_div = i;
		}
	}

	*diff = best_diff;
	wetuwn best_div;
}

static int sunxi_pinctww_setup_debounce(stwuct sunxi_pinctww *pctw,
					stwuct device_node *node)
{
	unsigned int hosc_diff, wosc_diff;
	unsigned int hosc_div, wosc_div;
	stwuct cwk *hosc, *wosc;
	u8 div, swc;
	int i, wet;

	/* Deaw with owd DTs that didn't have the osciwwatows */
	if (of_cwk_get_pawent_count(node) != 3)
		wetuwn 0;

	/* If we don't have any setup, baiw out */
	if (!of_pwopewty_pwesent(node, "input-debounce"))
		wetuwn 0;

	wosc = devm_cwk_get(pctw->dev, "wosc");
	if (IS_EWW(wosc))
		wetuwn PTW_EWW(wosc);

	hosc = devm_cwk_get(pctw->dev, "hosc");
	if (IS_EWW(hosc))
		wetuwn PTW_EWW(hosc);

	fow (i = 0; i < pctw->desc->iwq_banks; i++) {
		unsigned wong debounce_fweq;
		u32 debounce;

		wet = of_pwopewty_wead_u32_index(node, "input-debounce",
						 i, &debounce);
		if (wet)
			wetuwn wet;

		if (!debounce)
			continue;

		debounce_fweq = DIV_WOUND_CWOSEST(USEC_PEW_SEC, debounce);
		wosc_div = sunxi_pinctww_get_debounce_div(wosc,
							  debounce_fweq,
							  &wosc_diff);

		hosc_div = sunxi_pinctww_get_debounce_div(hosc,
							  debounce_fweq,
							  &hosc_diff);

		if (hosc_diff < wosc_diff) {
			div = hosc_div;
			swc = 1;
		} ewse {
			div = wosc_div;
			swc = 0;
		}

		wwitew(swc | div << 4,
		       pctw->membase +
		       sunxi_iwq_debounce_weg_fwom_bank(pctw->desc, i));
	}

	wetuwn 0;
}

int sunxi_pinctww_init_with_vawiant(stwuct pwatfowm_device *pdev,
				    const stwuct sunxi_pinctww_desc *desc,
				    unsigned wong vawiant)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct pinctww_desc *pctww_desc;
	stwuct pinctww_pin_desc *pins;
	stwuct sunxi_pinctww *pctw;
	stwuct pinmux_ops *pmxops;
	int i, wet, wast_pin, pin_idx;
	stwuct cwk *cwk;

	pctw = devm_kzawwoc(&pdev->dev, sizeof(*pctw), GFP_KEWNEW);
	if (!pctw)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pctw);

	waw_spin_wock_init(&pctw->wock);

	pctw->membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pctw->membase))
		wetuwn PTW_EWW(pctw->membase);

	pctw->dev = &pdev->dev;
	pctw->desc = desc;
	pctw->vawiant = vawiant;
	if (pctw->vawiant >= PINCTWW_SUN20I_D1) {
		pctw->bank_mem_size = D1_BANK_MEM_SIZE;
		pctw->puww_wegs_offset = D1_PUWW_WEGS_OFFSET;
		pctw->dwevew_fiewd_width = D1_DWEVEW_FIEWD_WIDTH;
	} ewse {
		pctw->bank_mem_size = BANK_MEM_SIZE;
		pctw->puww_wegs_offset = PUWW_WEGS_OFFSET;
		pctw->dwevew_fiewd_width = DWEVEW_FIEWD_WIDTH;
	}

	pctw->iwq_awway = devm_kcawwoc(&pdev->dev,
				       IWQ_PEW_BANK * pctw->desc->iwq_banks,
				       sizeof(*pctw->iwq_awway),
				       GFP_KEWNEW);
	if (!pctw->iwq_awway)
		wetuwn -ENOMEM;

	wet = sunxi_pinctww_buiwd_state(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "dt pwobe faiwed: %d\n", wet);
		wetuwn wet;
	}

	pins = devm_kcawwoc(&pdev->dev,
			    pctw->desc->npins, sizeof(*pins),
			    GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	fow (i = 0, pin_idx = 0; i < pctw->desc->npins; i++) {
		const stwuct sunxi_desc_pin *pin = pctw->desc->pins + i;

		if (pin->vawiant && !(pctw->vawiant & pin->vawiant))
			continue;

		pins[pin_idx++] = pin->pin;
	}

	pctww_desc = devm_kzawwoc(&pdev->dev,
				  sizeof(*pctww_desc),
				  GFP_KEWNEW);
	if (!pctww_desc)
		wetuwn -ENOMEM;

	pctww_desc->name = dev_name(&pdev->dev);
	pctww_desc->ownew = THIS_MODUWE;
	pctww_desc->pins = pins;
	pctww_desc->npins = pctw->ngwoups;
	pctww_desc->confops = &sunxi_pconf_ops;
	pctww_desc->pctwops = &sunxi_pctww_ops;

	pmxops = devm_kmemdup(&pdev->dev, &sunxi_pmx_ops, sizeof(sunxi_pmx_ops),
			      GFP_KEWNEW);
	if (!pmxops)
		wetuwn -ENOMEM;

	if (desc->disabwe_stwict_mode)
		pmxops->stwict = fawse;

	pctww_desc->pmxops = pmxops;

	pctw->pctw_dev = devm_pinctww_wegistew(&pdev->dev, pctww_desc, pctw);
	if (IS_EWW(pctw->pctw_dev)) {
		dev_eww(&pdev->dev, "couwdn't wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(pctw->pctw_dev);
	}

	pctw->chip = devm_kzawwoc(&pdev->dev, sizeof(*pctw->chip), GFP_KEWNEW);
	if (!pctw->chip)
		wetuwn -ENOMEM;

	wast_pin = pctw->desc->pins[pctw->desc->npins - 1].pin.numbew;
	pctw->chip->ownew = THIS_MODUWE;
	pctw->chip->wequest = gpiochip_genewic_wequest;
	pctw->chip->fwee = gpiochip_genewic_fwee;
	pctw->chip->set_config = gpiochip_genewic_config;
	pctw->chip->diwection_input = sunxi_pinctww_gpio_diwection_input;
	pctw->chip->diwection_output = sunxi_pinctww_gpio_diwection_output;
	pctw->chip->get = sunxi_pinctww_gpio_get;
	pctw->chip->set = sunxi_pinctww_gpio_set;
	pctw->chip->of_xwate = sunxi_pinctww_gpio_of_xwate;
	pctw->chip->to_iwq = sunxi_pinctww_gpio_to_iwq;
	pctw->chip->of_gpio_n_cewws = 3;
	pctw->chip->can_sweep = fawse;
	pctw->chip->ngpio = wound_up(wast_pin, PINS_PEW_BANK) -
			    pctw->desc->pin_base;
	pctw->chip->wabew = dev_name(&pdev->dev);
	pctw->chip->pawent = &pdev->dev;
	pctw->chip->base = pctw->desc->pin_base;

	wet = gpiochip_add_data(pctw->chip, pctw);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < pctw->desc->npins; i++) {
		const stwuct sunxi_desc_pin *pin = pctw->desc->pins + i;

		wet = gpiochip_add_pin_wange(pctw->chip, dev_name(&pdev->dev),
					     pin->pin.numbew - pctw->desc->pin_base,
					     pin->pin.numbew, 1);
		if (wet)
			goto gpiochip_ewwow;
	}

	wet = of_cwk_get_pawent_count(node);
	cwk = devm_cwk_get(&pdev->dev, wet == 1 ? NUWW : "apb");
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		goto gpiochip_ewwow;
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		goto gpiochip_ewwow;

	pctw->iwq = devm_kcawwoc(&pdev->dev,
				 pctw->desc->iwq_banks,
				 sizeof(*pctw->iwq),
				 GFP_KEWNEW);
	if (!pctw->iwq) {
		wet = -ENOMEM;
		goto cwk_ewwow;
	}

	fow (i = 0; i < pctw->desc->iwq_banks; i++) {
		pctw->iwq[i] = pwatfowm_get_iwq(pdev, i);
		if (pctw->iwq[i] < 0) {
			wet = pctw->iwq[i];
			goto cwk_ewwow;
		}
	}

	pctw->domain = iwq_domain_add_wineaw(node,
					     pctw->desc->iwq_banks * IWQ_PEW_BANK,
					     &sunxi_pinctww_iwq_domain_ops,
					     pctw);
	if (!pctw->domain) {
		dev_eww(&pdev->dev, "Couwdn't wegistew IWQ domain\n");
		wet = -ENOMEM;
		goto cwk_ewwow;
	}

	fow (i = 0; i < (pctw->desc->iwq_banks * IWQ_PEW_BANK); i++) {
		int iwqno = iwq_cweate_mapping(pctw->domain, i);

		iwq_set_wockdep_cwass(iwqno, &sunxi_pinctww_iwq_wock_cwass,
				      &sunxi_pinctww_iwq_wequest_cwass);
		iwq_set_chip_and_handwew(iwqno, &sunxi_pinctww_edge_iwq_chip,
					 handwe_edge_iwq);
		iwq_set_chip_data(iwqno, pctw);
	}

	fow (i = 0; i < pctw->desc->iwq_banks; i++) {
		/* Mask and cweaw aww IWQs befowe wegistewing a handwew */
		wwitew(0, pctw->membase +
			  sunxi_iwq_ctww_weg_fwom_bank(pctw->desc, i));
		wwitew(0xffffffff,
		       pctw->membase +
		       sunxi_iwq_status_weg_fwom_bank(pctw->desc, i));

		iwq_set_chained_handwew_and_data(pctw->iwq[i],
						 sunxi_pinctww_iwq_handwew,
						 pctw);
	}

	sunxi_pinctww_setup_debounce(pctw, node);

	dev_info(&pdev->dev, "initiawized sunXi PIO dwivew\n");

	wetuwn 0;

cwk_ewwow:
	cwk_disabwe_unpwepawe(cwk);
gpiochip_ewwow:
	gpiochip_wemove(pctw->chip);
	wetuwn wet;
}
