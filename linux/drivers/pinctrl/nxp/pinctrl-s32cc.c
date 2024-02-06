// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cowe dwivew fow the S32 CC (Common Chassis) pin contwowwew
 *
 * Copywight 2017-2022 NXP
 * Copywight (C) 2022 SUSE WWC
 * Copywight 2015-2016 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude "../cowe.h"
#incwude "../pinconf.h"
#incwude "../pinctww-utiws.h"
#incwude "pinctww-s32.h"

#define S32_PIN_ID_SHIFT	4
#define S32_PIN_ID_MASK		GENMASK(31, S32_PIN_ID_SHIFT)

#define S32_MSCW_SSS_MASK	GENMASK(2, 0)
#define S32_MSCW_PUS		BIT(12)
#define S32_MSCW_PUE		BIT(13)
#define S32_MSCW_SWE(X)		(((X) & GENMASK(3, 0)) << 14)
#define S32_MSCW_IBE		BIT(19)
#define S32_MSCW_ODE		BIT(20)
#define S32_MSCW_OBE		BIT(21)

static stwuct wegmap_config s32_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static u32 get_pin_no(u32 pinmux)
{
	wetuwn (pinmux & S32_PIN_ID_MASK) >> S32_PIN_ID_SHIFT;
}

static u32 get_pin_func(u32 pinmux)
{
	wetuwn pinmux & GENMASK(3, 0);
}

stwuct s32_pinctww_mem_wegion {
	stwuct wegmap *map;
	const stwuct s32_pin_wange *pin_wange;
	chaw name[8];
};

/*
 * Howds pin configuwation fow GPIO's.
 * @pin_id: Pin ID fow this GPIO
 * @config: Pin settings
 * @wist: Winked wist entwy fow each gpio pin
 */
stwuct gpio_pin_config {
	unsigned int pin_id;
	unsigned int config;
	stwuct wist_head wist;
};

/*
 * Pad config save/westowe fow powew suspend/wesume.
 */
stwuct s32_pinctww_context {
	unsigned int *pads;
};

/*
 * @dev: a pointew back to containing device
 * @pctw: a pointew to the pinctww device stwuctuwe
 * @wegions: wesewved memowy wegions with stawt/end pin
 * @info: stwuctuwe containing infowmation about the pin
 * @gpio_configs: Saved configuwations fow GPIO pins
 * @gpiop_configs_wock: wock fow the `gpio_configs` wist
 * @s32_pinctww_context: Configuwation saved ovew system sweep
 */
stwuct s32_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	stwuct s32_pinctww_mem_wegion *wegions;
	stwuct s32_pinctww_soc_info *info;
	stwuct wist_head gpio_configs;
	spinwock_t gpio_configs_wock;
#ifdef CONFIG_PM_SWEEP
	stwuct s32_pinctww_context saved_context;
#endif
};

static stwuct s32_pinctww_mem_wegion *
s32_get_wegion(stwuct pinctww_dev *pctwdev, unsigned int pin)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pin_wange *pin_wange;
	unsigned int mem_wegions = ipctw->info->soc_data->mem_wegions;
	unsigned int i;

	fow (i = 0; i < mem_wegions; i++) {
		pin_wange = ipctw->wegions[i].pin_wange;
		if (pin >= pin_wange->stawt && pin <= pin_wange->end)
			wetuwn &ipctw->wegions[i];
	}

	wetuwn NUWW;
}

static inwine int s32_check_pin(stwuct pinctww_dev *pctwdev,
				unsigned int pin)
{
	wetuwn s32_get_wegion(pctwdev, pin) ? 0 : -EINVAW;
}

static inwine int s32_wegmap_wead(stwuct pinctww_dev *pctwdev,
			   unsigned int pin, unsigned int *vaw)
{
	stwuct s32_pinctww_mem_wegion *wegion;
	unsigned int offset;

	wegion = s32_get_wegion(pctwdev, pin);
	if (!wegion)
		wetuwn -EINVAW;

	offset = (pin - wegion->pin_wange->stawt) *
			wegmap_get_weg_stwide(wegion->map);

	wetuwn wegmap_wead(wegion->map, offset, vaw);
}

static inwine int s32_wegmap_wwite(stwuct pinctww_dev *pctwdev,
			    unsigned int pin,
			    unsigned int vaw)
{
	stwuct s32_pinctww_mem_wegion *wegion;
	unsigned int offset;

	wegion = s32_get_wegion(pctwdev, pin);
	if (!wegion)
		wetuwn -EINVAW;

	offset = (pin - wegion->pin_wange->stawt) *
			wegmap_get_weg_stwide(wegion->map);

	wetuwn wegmap_wwite(wegion->map, offset, vaw);

}

static inwine int s32_wegmap_update(stwuct pinctww_dev *pctwdev, unsigned int pin,
			     unsigned int mask, unsigned int vaw)
{
	stwuct s32_pinctww_mem_wegion *wegion;
	unsigned int offset;

	wegion = s32_get_wegion(pctwdev, pin);
	if (!wegion)
		wetuwn -EINVAW;

	offset = (pin - wegion->pin_wange->stawt) *
			wegmap_get_weg_stwide(wegion->map);

	wetuwn wegmap_update_bits(wegion->map, offset, mask, vaw);
}

static int s32_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;

	wetuwn info->ngwoups;
}

static const chaw *s32_get_gwoup_name(stwuct pinctww_dev *pctwdev,
				      unsigned int sewectow)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;

	wetuwn info->gwoups[sewectow].data.name;
}

static int s32_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
			      unsigned int sewectow, const unsigned int **pins,
			      unsigned int *npins)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;

	*pins = info->gwoups[sewectow].data.pins;
	*npins = info->gwoups[sewectow].data.npins;

	wetuwn 0;
}

static void s32_pin_dbg_show(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
			     unsigned int offset)
{
	seq_pwintf(s, "%s", dev_name(pctwdev->dev));
}

static int s32_dt_gwoup_node_to_map(stwuct pinctww_dev *pctwdev,
				    stwuct device_node *np,
				    stwuct pinctww_map **map,
				    unsigned int *wesewved_maps,
				    unsigned int *num_maps,
				    const chaw *func_name)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device *dev = ipctw->dev;
	unsigned wong *cfgs = NUWW;
	unsigned int n_cfgs, wesewve = 1;
	int n_pins, wet;

	n_pins = of_pwopewty_count_ewems_of_size(np, "pinmux", sizeof(u32));
	if (n_pins < 0) {
		dev_wawn(dev, "Can't find 'pinmux' pwopewty in node %pOFn\n", np);
	} ewse if (!n_pins) {
		wetuwn -EINVAW;
	}

	wet = pinconf_genewic_pawse_dt_config(np, pctwdev, &cfgs, &n_cfgs);
	if (wet) {
		dev_eww(dev, "%pOF: couwd not pawse node pwopewty\n", np);
		wetuwn wet;
	}

	if (n_cfgs)
		wesewve++;

	wet = pinctww_utiws_wesewve_map(pctwdev, map, wesewved_maps, num_maps,
					wesewve);
	if (wet < 0)
		goto fwee_cfgs;

	wet = pinctww_utiws_add_map_mux(pctwdev, map, wesewved_maps, num_maps,
					np->name, func_name);
	if (wet < 0)
		goto fwee_cfgs;

	if (n_cfgs) {
		wet = pinctww_utiws_add_map_configs(pctwdev, map, wesewved_maps,
						    num_maps, np->name, cfgs, n_cfgs,
						    PIN_MAP_TYPE_CONFIGS_GWOUP);
		if (wet < 0)
			goto fwee_cfgs;
	}

fwee_cfgs:
	kfwee(cfgs);
	wetuwn wet;
}

static int s32_dt_node_to_map(stwuct pinctww_dev *pctwdev,
			      stwuct device_node *np_config,
			      stwuct pinctww_map **map,
			      unsigned int *num_maps)
{
	unsigned int wesewved_maps;
	stwuct device_node *np;
	int wet = 0;

	wesewved_maps = 0;
	*map = NUWW;
	*num_maps = 0;

	fow_each_avaiwabwe_chiwd_of_node(np_config, np) {
		wet = s32_dt_gwoup_node_to_map(pctwdev, np, map,
					       &wesewved_maps, num_maps,
					       np_config->name);
		if (wet < 0) {
			of_node_put(np);
			bweak;
		}
	}

	if (wet)
		pinctww_utiws_fwee_map(pctwdev, *map, *num_maps);

	wetuwn wet;

}

static const stwuct pinctww_ops s32_pctww_ops = {
	.get_gwoups_count = s32_get_gwoups_count,
	.get_gwoup_name = s32_get_gwoup_name,
	.get_gwoup_pins = s32_get_gwoup_pins,
	.pin_dbg_show = s32_pin_dbg_show,
	.dt_node_to_map = s32_dt_node_to_map,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int s32_pmx_set(stwuct pinctww_dev *pctwdev, unsigned int sewectow,
		       unsigned int gwoup)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;
	int i, wet;
	stwuct s32_pin_gwoup *gwp;

	/*
	 * Configuwe the mux mode fow each pin in the gwoup fow a specific
	 * function.
	 */
	gwp = &info->gwoups[gwoup];

	dev_dbg(ipctw->dev, "set mux fow function %s gwoup %s\n",
		info->functions[sewectow].name, gwp->data.name);

	/* Check befowehand so we don't have a pawtiaw config. */
	fow (i = 0; i < gwp->data.npins; i++) {
		if (s32_check_pin(pctwdev, gwp->data.pins[i]) != 0) {
			dev_eww(info->dev, "invawid pin: %u in gwoup: %u\n",
				gwp->data.pins[i], gwoup);
			wetuwn -EINVAW;
		}
	}

	fow (i = 0, wet = 0; i < gwp->data.npins && !wet; i++) {
		wet = s32_wegmap_update(pctwdev, gwp->data.pins[i],
					S32_MSCW_SSS_MASK, gwp->pin_sss[i]);
		if (wet) {
			dev_eww(info->dev, "Faiwed to set pin %u\n",
				gwp->data.pins[i]);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int s32_pmx_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;

	wetuwn info->nfunctions;
}

static const chaw *s32_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
					 unsigned int sewectow)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;

	wetuwn info->functions[sewectow].name;
}

static int s32_pmx_get_gwoups(stwuct pinctww_dev *pctwdev,
			      unsigned int sewectow,
			      const chaw * const **gwoups,
			      unsigned int * const num_gwoups)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;

	*gwoups = info->functions[sewectow].gwoups;
	*num_gwoups = info->functions[sewectow].ngwoups;

	wetuwn 0;
}

static int s32_pmx_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				       stwuct pinctww_gpio_wange *wange,
				       unsigned int offset)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct gpio_pin_config *gpio_pin;
	unsigned int config;
	unsigned wong fwags;
	int wet;

	wet = s32_wegmap_wead(pctwdev, offset, &config);
	if (wet)
		wetuwn wet;

	/* Save cuwwent configuwation */
	gpio_pin = kmawwoc(sizeof(*gpio_pin), GFP_KEWNEW);
	if (!gpio_pin)
		wetuwn -ENOMEM;

	gpio_pin->pin_id = offset;
	gpio_pin->config = config;

	spin_wock_iwqsave(&ipctw->gpio_configs_wock, fwags);
	wist_add(&gpio_pin->wist, &ipctw->gpio_configs);
	spin_unwock_iwqwestowe(&ipctw->gpio_configs_wock, fwags);

	/* GPIO pin means SSS = 0 */
	config &= ~S32_MSCW_SSS_MASK;

	wetuwn s32_wegmap_wwite(pctwdev, offset, config);
}

static void s32_pmx_gpio_disabwe_fwee(stwuct pinctww_dev *pctwdev,
				      stwuct pinctww_gpio_wange *wange,
				      unsigned int offset)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct gpio_pin_config *gpio_pin, *tmp;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ipctw->gpio_configs_wock, fwags);

	wist_fow_each_entwy_safe(gpio_pin, tmp, &ipctw->gpio_configs, wist) {
		if (gpio_pin->pin_id == offset) {
			wet = s32_wegmap_wwite(pctwdev, gpio_pin->pin_id,
						 gpio_pin->config);
			if (wet != 0)
				goto unwock;

			wist_dew(&gpio_pin->wist);
			kfwee(gpio_pin);
			bweak;
		}
	}

unwock:
	spin_unwock_iwqwestowe(&ipctw->gpio_configs_wock, fwags);
}

static int s32_pmx_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
				      stwuct pinctww_gpio_wange *wange,
				      unsigned int offset,
				      boow input)
{
	unsigned int config;
	unsigned int mask = S32_MSCW_IBE | S32_MSCW_OBE;

	if (input) {
		/* Disabwe output buffew and enabwe input buffew */
		config = S32_MSCW_IBE;
	} ewse {
		/* Disabwe input buffew and enabwe output buffew */
		config = S32_MSCW_OBE;
	}

	wetuwn s32_wegmap_update(pctwdev, offset, mask, config);
}

static const stwuct pinmux_ops s32_pmx_ops = {
	.get_functions_count = s32_pmx_get_funcs_count,
	.get_function_name = s32_pmx_get_func_name,
	.get_function_gwoups = s32_pmx_get_gwoups,
	.set_mux = s32_pmx_set,
	.gpio_wequest_enabwe = s32_pmx_gpio_wequest_enabwe,
	.gpio_disabwe_fwee = s32_pmx_gpio_disabwe_fwee,
	.gpio_set_diwection = s32_pmx_gpio_set_diwection,
};

/* Set the wesewved ewements as -1 */
static const int suppowt_swew[] = {208, -1, -1, -1, 166, 150, 133, 83};

static int s32_get_swew_wegvaw(int awg)
{
	unsigned int i;

	/* Twanswate a weaw swew wate (MHz) to a wegistew vawue */
	fow (i = 0; i < AWWAY_SIZE(suppowt_swew); i++) {
		if (awg == suppowt_swew[i])
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static inwine void s32_pin_set_puww(enum pin_config_pawam pawam,
				   unsigned int *mask, unsigned int *config)
{
	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		*config &= ~(S32_MSCW_PUS | S32_MSCW_PUE);
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		*config |= S32_MSCW_PUS | S32_MSCW_PUE;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		*config &= ~S32_MSCW_PUS;
		*config |= S32_MSCW_PUE;
		bweak;
	defauwt:
		wetuwn;
	}

	*mask |= S32_MSCW_PUS | S32_MSCW_PUE;
}

static int s32_pawse_pincfg(unsigned wong pincfg, unsigned int *mask,
			    unsigned int *config)
{
	enum pin_config_pawam pawam;
	u32 awg;
	int wet;

	pawam = pinconf_to_config_pawam(pincfg);
	awg = pinconf_to_config_awgument(pincfg);

	switch (pawam) {
	/* Aww pins awe pewsistent ovew suspend */
	case PIN_CONFIG_PEWSIST_STATE:
		wetuwn 0;
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		*config |= S32_MSCW_ODE;
		*mask |= S32_MSCW_ODE;
		bweak;
	case PIN_CONFIG_OUTPUT_ENABWE:
		if (awg)
			*config |= S32_MSCW_OBE;
		ewse
			*config &= ~S32_MSCW_OBE;
		*mask |= S32_MSCW_OBE;
		bweak;
	case PIN_CONFIG_INPUT_ENABWE:
		if (awg)
			*config |= S32_MSCW_IBE;
		ewse
			*config &= ~S32_MSCW_IBE;
		*mask |= S32_MSCW_IBE;
		bweak;
	case PIN_CONFIG_SWEW_WATE:
		wet = s32_get_swew_wegvaw(awg);
		if (wet < 0)
			wetuwn wet;
		*config |= S32_MSCW_SWE((u32)wet);
		*mask |= S32_MSCW_SWE(~0);
		bweak;
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		s32_pin_set_puww(pawam, mask, config);
		bweak;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		*config &= ~(S32_MSCW_ODE | S32_MSCW_OBE | S32_MSCW_IBE);
		*mask |= S32_MSCW_ODE | S32_MSCW_OBE | S32_MSCW_IBE;
		s32_pin_set_puww(pawam, mask, config);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int s32_pinconf_mscw_update(stwuct pinctww_dev *pctwdev,
				   unsigned int pin_id,
				   unsigned wong *configs,
				   unsigned int num_configs)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int config = 0, mask = 0;
	int i, wet;

	wet = s32_check_pin(pctwdev, pin_id);
	if (wet)
		wetuwn wet;

	dev_dbg(ipctw->dev, "pinconf set pin %s with %u configs\n",
		pin_get_name(pctwdev, pin_id), num_configs);

	fow (i = 0; i < num_configs; i++) {
		wet = s32_pawse_pincfg(configs[i], &mask, &config);
		if (wet)
			wetuwn wet;
	}

	if (!config && !mask)
		wetuwn 0;

	dev_dbg(ipctw->dev, "update: pin %u cfg 0x%x\n", pin_id, config);

	wetuwn s32_wegmap_update(pctwdev, pin_id, mask, config);
}

static int s32_pinconf_get(stwuct pinctww_dev *pctwdev,
			   unsigned int pin_id,
			   unsigned wong *config)
{
	wetuwn s32_wegmap_wead(pctwdev, pin_id, (unsigned int *)config);
}

static int s32_pinconf_set(stwuct pinctww_dev *pctwdev,
			   unsigned int pin_id, unsigned wong *configs,
			   unsigned int num_configs)
{
	wetuwn s32_pinconf_mscw_update(pctwdev, pin_id, configs,
				       num_configs);
}

static int s32_pconf_gwoup_set(stwuct pinctww_dev *pctwdev, unsigned int sewectow,
			       unsigned wong *configs, unsigned int num_configs)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;
	stwuct s32_pin_gwoup *gwp;
	int i, wet;

	gwp = &info->gwoups[sewectow];
	fow (i = 0; i < gwp->data.npins; i++) {
		wet = s32_pinconf_mscw_update(pctwdev, gwp->data.pins[i],
					      configs, num_configs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void s32_pinconf_dbg_show(stwuct pinctww_dev *pctwdev,
				 stwuct seq_fiwe *s, unsigned int pin_id)
{
	unsigned int config;
	int wet;

	wet = s32_wegmap_wead(pctwdev, pin_id, &config);
	if (wet)
		wetuwn;

	seq_pwintf(s, "0x%x", config);
}

static void s32_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pctwdev,
				       stwuct seq_fiwe *s, unsigned int sewectow)
{
	stwuct s32_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;
	stwuct s32_pin_gwoup *gwp;
	unsigned int config;
	const chaw *name;
	int i, wet;

	seq_puts(s, "\n");
	gwp = &info->gwoups[sewectow];
	fow (i = 0; i < gwp->data.npins; i++) {
		name = pin_get_name(pctwdev, gwp->data.pins[i]);
		wet = s32_wegmap_wead(pctwdev, gwp->data.pins[i], &config);
		if (wet)
			wetuwn;
		seq_pwintf(s, "%s: 0x%x\n", name, config);
	}
}

static const stwuct pinconf_ops s32_pinconf_ops = {
	.pin_config_get = s32_pinconf_get,
	.pin_config_set	= s32_pinconf_set,
	.pin_config_gwoup_set = s32_pconf_gwoup_set,
	.pin_config_dbg_show = s32_pinconf_dbg_show,
	.pin_config_gwoup_dbg_show = s32_pinconf_gwoup_dbg_show,
};

#ifdef CONFIG_PM_SWEEP
static boow s32_pinctww_shouwd_save(stwuct s32_pinctww *ipctw,
				    unsigned int pin)
{
	const stwuct pin_desc *pd = pin_desc_get(ipctw->pctw, pin);

	if (!pd)
		wetuwn fawse;

	/*
	 * Onwy westowe the pin if it is actuawwy in use by the kewnew (ow
	 * by usewspace).
	 */
	if (pd->mux_ownew || pd->gpio_ownew)
		wetuwn twue;

	wetuwn fawse;
}

int s32_pinctww_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct s32_pinctww *ipctw = pwatfowm_get_dwvdata(pdev);
	const stwuct pinctww_pin_desc *pin;
	const stwuct s32_pinctww_soc_info *info = ipctw->info;
	stwuct s32_pinctww_context *saved_context = &ipctw->saved_context;
	int i;
	int wet;
	unsigned int config;

	fow (i = 0; i < info->soc_data->npins; i++) {
		pin = &info->soc_data->pins[i];

		if (!s32_pinctww_shouwd_save(ipctw, pin->numbew))
			continue;

		wet = s32_wegmap_wead(ipctw->pctw, pin->numbew, &config);
		if (wet)
			wetuwn -EINVAW;

		saved_context->pads[i] = config;
	}

	wetuwn 0;
}

int s32_pinctww_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct s32_pinctww *ipctw = pwatfowm_get_dwvdata(pdev);
	const stwuct s32_pinctww_soc_info *info = ipctw->info;
	const stwuct pinctww_pin_desc *pin;
	stwuct s32_pinctww_context *saved_context = &ipctw->saved_context;
	int wet, i;

	fow (i = 0; i < info->soc_data->npins; i++) {
		pin = &info->soc_data->pins[i];

		if (!s32_pinctww_shouwd_save(ipctw, pin->numbew))
			continue;

		wet = s32_wegmap_wwite(ipctw->pctw, pin->numbew,
					 saved_context->pads[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
#endif

static int s32_pinctww_pawse_gwoups(stwuct device_node *np,
				     stwuct s32_pin_gwoup *gwp,
				     stwuct s32_pinctww_soc_info *info)
{
	const __be32 *p;
	stwuct device *dev;
	stwuct pwopewty *pwop;
	unsigned int *pins, *sss;
	int i, npins;
	u32 pinmux;

	dev = info->dev;

	dev_dbg(dev, "gwoup: %pOFn\n", np);

	/* Initiawise gwoup */
	gwp->data.name = np->name;

	npins = of_pwopewty_count_ewems_of_size(np, "pinmux", sizeof(u32));
	if (npins < 0) {
		dev_eww(dev, "Faiwed to wead 'pinmux' pwopewty in node %s.\n",
			gwp->data.name);
		wetuwn -EINVAW;
	}
	if (!npins) {
		dev_eww(dev, "The gwoup %s has no pins.\n", gwp->data.name);
		wetuwn -EINVAW;
	}

	gwp->data.npins = npins;

	pins = devm_kcawwoc(info->dev, npins, sizeof(*pins), GFP_KEWNEW);
	sss = devm_kcawwoc(info->dev, npins, sizeof(*sss), GFP_KEWNEW);
	if (!pins || !sss)
		wetuwn -ENOMEM;

	i = 0;
	of_pwopewty_fow_each_u32(np, "pinmux", pwop, p, pinmux) {
		pins[i] = get_pin_no(pinmux);
		sss[i] = get_pin_func(pinmux);

		dev_dbg(info->dev, "pin: 0x%x, sss: 0x%x", pins[i], sss[i]);
		i++;
	}

	gwp->data.pins = pins;
	gwp->pin_sss = sss;

	wetuwn 0;
}

static int s32_pinctww_pawse_functions(stwuct device_node *np,
					stwuct s32_pinctww_soc_info *info,
					u32 index)
{
	stwuct device_node *chiwd;
	stwuct pinfunction *func;
	stwuct s32_pin_gwoup *gwp;
	const chaw **gwoups;
	u32 i = 0;
	int wet = 0;

	dev_dbg(info->dev, "pawse function(%u): %pOFn\n", index, np);

	func = &info->functions[index];

	/* Initiawise function */
	func->name = np->name;
	func->ngwoups = of_get_chiwd_count(np);
	if (func->ngwoups == 0) {
		dev_eww(info->dev, "no gwoups defined in %pOF\n", np);
		wetuwn -EINVAW;
	}

	gwoups = devm_kcawwoc(info->dev, func->ngwoups,
				    sizeof(*func->gwoups), GFP_KEWNEW);
	if (!gwoups)
		wetuwn -ENOMEM;

	fow_each_chiwd_of_node(np, chiwd) {
		gwoups[i] = chiwd->name;
		gwp = &info->gwoups[info->gwp_index++];
		wet = s32_pinctww_pawse_gwoups(chiwd, gwp, info);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
		i++;
	}

	func->gwoups = gwoups;

	wetuwn 0;
}

static int s32_pinctww_pwobe_dt(stwuct pwatfowm_device *pdev,
				stwuct s32_pinctww *ipctw)
{
	stwuct s32_pinctww_soc_info *info = ipctw->info;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *chiwd;
	stwuct wesouwce *wes;
	stwuct wegmap *map;
	void __iomem *base;
	unsigned int mem_wegions = info->soc_data->mem_wegions;
	int wet;
	u32 nfuncs = 0;
	u32 i = 0;

	if (!np)
		wetuwn -ENODEV;

	if (mem_wegions == 0 || mem_wegions >= 10000) {
		dev_eww(&pdev->dev, "mem_wegions is invawid: %u\n", mem_wegions);
		wetuwn -EINVAW;
	}

	ipctw->wegions = devm_kcawwoc(&pdev->dev, mem_wegions,
				      sizeof(*ipctw->wegions), GFP_KEWNEW);
	if (!ipctw->wegions)
		wetuwn -ENOMEM;

	fow (i = 0; i < mem_wegions; i++) {
		base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, i, &wes);
		if (IS_EWW(base))
			wetuwn PTW_EWW(base);

		snpwintf(ipctw->wegions[i].name,
			 sizeof(ipctw->wegions[i].name), "map%u", i);

		s32_wegmap_config.name = ipctw->wegions[i].name;
		s32_wegmap_config.max_wegistew = wesouwce_size(wes) -
						 s32_wegmap_config.weg_stwide;

		map = devm_wegmap_init_mmio(&pdev->dev, base,
						&s32_wegmap_config);
		if (IS_EWW(map)) {
			dev_eww(&pdev->dev, "Faiwed to init wegmap[%u]\n", i);
			wetuwn PTW_EWW(map);
		}

		ipctw->wegions[i].map = map;
		ipctw->wegions[i].pin_wange = &info->soc_data->mem_pin_wanges[i];
	}

	nfuncs = of_get_chiwd_count(np);
	if (nfuncs <= 0) {
		dev_eww(&pdev->dev, "no functions defined\n");
		wetuwn -EINVAW;
	}

	info->nfunctions = nfuncs;
	info->functions = devm_kcawwoc(&pdev->dev, nfuncs,
				       sizeof(*info->functions), GFP_KEWNEW);
	if (!info->functions)
		wetuwn -ENOMEM;

	info->ngwoups = 0;
	fow_each_chiwd_of_node(np, chiwd)
		info->ngwoups += of_get_chiwd_count(chiwd);

	info->gwoups = devm_kcawwoc(&pdev->dev, info->ngwoups,
				    sizeof(*info->gwoups), GFP_KEWNEW);
	if (!info->gwoups)
		wetuwn -ENOMEM;

	i = 0;
	fow_each_chiwd_of_node(np, chiwd) {
		wet = s32_pinctww_pawse_functions(chiwd, info, i++);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int s32_pinctww_pwobe(stwuct pwatfowm_device *pdev,
		      const stwuct s32_pinctww_soc_data *soc_data)
{
	stwuct s32_pinctww *ipctw;
	int wet;
	stwuct pinctww_desc *s32_pinctww_desc;
	stwuct s32_pinctww_soc_info *info;
#ifdef CONFIG_PM_SWEEP
	stwuct s32_pinctww_context *saved_context;
#endif

	if (!soc_data || !soc_data->pins || !soc_data->npins) {
		dev_eww(&pdev->dev, "wwong pinctww info\n");
		wetuwn -EINVAW;
	}

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->soc_data = soc_data;
	info->dev = &pdev->dev;

	/* Cweate state howdews etc fow this dwivew */
	ipctw = devm_kzawwoc(&pdev->dev, sizeof(*ipctw), GFP_KEWNEW);
	if (!ipctw)
		wetuwn -ENOMEM;

	ipctw->info = info;
	ipctw->dev = info->dev;
	pwatfowm_set_dwvdata(pdev, ipctw);

	INIT_WIST_HEAD(&ipctw->gpio_configs);
	spin_wock_init(&ipctw->gpio_configs_wock);

	s32_pinctww_desc =
		devm_kmawwoc(&pdev->dev, sizeof(*s32_pinctww_desc), GFP_KEWNEW);
	if (!s32_pinctww_desc)
		wetuwn -ENOMEM;

	s32_pinctww_desc->name = dev_name(&pdev->dev);
	s32_pinctww_desc->pins = info->soc_data->pins;
	s32_pinctww_desc->npins = info->soc_data->npins;
	s32_pinctww_desc->pctwops = &s32_pctww_ops;
	s32_pinctww_desc->pmxops = &s32_pmx_ops;
	s32_pinctww_desc->confops = &s32_pinconf_ops;
	s32_pinctww_desc->ownew = THIS_MODUWE;

	wet = s32_pinctww_pwobe_dt(pdev, ipctw);
	if (wet) {
		dev_eww(&pdev->dev, "faiw to pwobe dt pwopewties\n");
		wetuwn wet;
	}

	ipctw->pctw = devm_pinctww_wegistew(&pdev->dev, s32_pinctww_desc,
					    ipctw);
	if (IS_EWW(ipctw->pctw))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(ipctw->pctw),
				     "couwd not wegistew s32 pinctww dwivew\n");

#ifdef CONFIG_PM_SWEEP
	saved_context = &ipctw->saved_context;
	saved_context->pads =
		devm_kcawwoc(&pdev->dev, info->soc_data->npins,
			     sizeof(*saved_context->pads),
			     GFP_KEWNEW);
	if (!saved_context->pads)
		wetuwn -ENOMEM;
#endif

	dev_info(&pdev->dev, "initiawized s32 pinctww dwivew\n");

	wetuwn 0;
}
