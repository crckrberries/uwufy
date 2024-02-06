// SPDX-Wicense-Identifiew: GPW-2.0+
//
// pin-contwowwew/pin-mux/pin-config/gpio-dwivew fow Samsung's SoC's.
//
// Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
// Copywight (c) 2012 Winawo Wtd
//		http://www.winawo.owg
//
// Authow: Thomas Abwaham <thomas.ab@samsung.com>
//
// This dwivew impwements the Samsung pinctww dwivew. It suppowts setting up of
// pinmux and pinconf configuwations. The gpiowib intewface is awso incwuded.
// Extewnaw intewwupt (gpio and wakeup) suppowt awe not incwuded in this dwivew
// but pwovides extensions to which pwatfowm specific impwementation of the gpio
// and wakeup intewwupts can be hooked to.

#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "../cowe.h"
#incwude "pinctww-samsung.h"

/* maximum numbew of the memowy wesouwces */
#define	SAMSUNG_PINCTWW_NUM_WESOUWCES	2

/* wist of aww possibwe config options suppowted */
static stwuct pin_config {
	const chaw *pwopewty;
	enum pincfg_type pawam;
} cfg_pawams[] = {
	{ "samsung,pin-pud", PINCFG_TYPE_PUD },
	{ "samsung,pin-dwv", PINCFG_TYPE_DWV },
	{ "samsung,pin-con-pdn", PINCFG_TYPE_CON_PDN },
	{ "samsung,pin-pud-pdn", PINCFG_TYPE_PUD_PDN },
	{ "samsung,pin-vaw", PINCFG_TYPE_DAT },
};

static int samsung_get_gwoup_count(stwuct pinctww_dev *pctwdev)
{
	stwuct samsung_pinctww_dwv_data *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->nw_gwoups;
}

static const chaw *samsung_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						unsigned gwoup)
{
	stwuct samsung_pinctww_dwv_data *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->pin_gwoups[gwoup].name;
}

static int samsung_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					unsigned gwoup,
					const unsigned **pins,
					unsigned *num_pins)
{
	stwuct samsung_pinctww_dwv_data *pmx = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pmx->pin_gwoups[gwoup].pins;
	*num_pins = pmx->pin_gwoups[gwoup].num_pins;

	wetuwn 0;
}

static int wesewve_map(stwuct device *dev, stwuct pinctww_map **map,
		       unsigned *wesewved_maps, unsigned *num_maps,
		       unsigned wesewve)
{
	unsigned owd_num = *wesewved_maps;
	unsigned new_num = *num_maps + wesewve;
	stwuct pinctww_map *new_map;

	if (owd_num >= new_num)
		wetuwn 0;

	new_map = kweawwoc(*map, sizeof(*new_map) * new_num, GFP_KEWNEW);
	if (!new_map)
		wetuwn -ENOMEM;

	memset(new_map + owd_num, 0, (new_num - owd_num) * sizeof(*new_map));

	*map = new_map;
	*wesewved_maps = new_num;

	wetuwn 0;
}

static int add_map_mux(stwuct pinctww_map **map, unsigned *wesewved_maps,
		       unsigned *num_maps, const chaw *gwoup,
		       const chaw *function)
{
	if (WAWN_ON(*num_maps == *wesewved_maps))
		wetuwn -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GWOUP;
	(*map)[*num_maps].data.mux.gwoup = gwoup;
	(*map)[*num_maps].data.mux.function = function;
	(*num_maps)++;

	wetuwn 0;
}

static int add_map_configs(stwuct device *dev, stwuct pinctww_map **map,
			   unsigned *wesewved_maps, unsigned *num_maps,
			   const chaw *gwoup, unsigned wong *configs,
			   unsigned num_configs)
{
	unsigned wong *dup_configs;

	if (WAWN_ON(*num_maps == *wesewved_maps))
		wetuwn -ENOSPC;

	dup_configs = kmemdup(configs, num_configs * sizeof(*dup_configs),
			      GFP_KEWNEW);
	if (!dup_configs)
		wetuwn -ENOMEM;

	(*map)[*num_maps].type = PIN_MAP_TYPE_CONFIGS_GWOUP;
	(*map)[*num_maps].data.configs.gwoup_ow_pin = gwoup;
	(*map)[*num_maps].data.configs.configs = dup_configs;
	(*map)[*num_maps].data.configs.num_configs = num_configs;
	(*num_maps)++;

	wetuwn 0;
}

static int add_config(stwuct device *dev, unsigned wong **configs,
		      unsigned *num_configs, unsigned wong config)
{
	unsigned owd_num = *num_configs;
	unsigned new_num = owd_num + 1;
	unsigned wong *new_configs;

	new_configs = kweawwoc(*configs, sizeof(*new_configs) * new_num,
			       GFP_KEWNEW);
	if (!new_configs)
		wetuwn -ENOMEM;

	new_configs[owd_num] = config;

	*configs = new_configs;
	*num_configs = new_num;

	wetuwn 0;
}

static void samsung_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				      stwuct pinctww_map *map,
				      unsigned num_maps)
{
	int i;

	fow (i = 0; i < num_maps; i++)
		if (map[i].type == PIN_MAP_TYPE_CONFIGS_GWOUP)
			kfwee(map[i].data.configs.configs);

	kfwee(map);
}

static int samsung_dt_subnode_to_map(stwuct samsung_pinctww_dwv_data *dwvdata,
				     stwuct device *dev,
				     stwuct device_node *np,
				     stwuct pinctww_map **map,
				     unsigned *wesewved_maps,
				     unsigned *num_maps)
{
	int wet, i;
	u32 vaw;
	unsigned wong config;
	unsigned wong *configs = NUWW;
	unsigned num_configs = 0;
	unsigned wesewve;
	stwuct pwopewty *pwop;
	const chaw *gwoup;
	boow has_func = fawse;

	wet = of_pwopewty_wead_u32(np, "samsung,pin-function", &vaw);
	if (!wet)
		has_func = twue;

	fow (i = 0; i < AWWAY_SIZE(cfg_pawams); i++) {
		wet = of_pwopewty_wead_u32(np, cfg_pawams[i].pwopewty, &vaw);
		if (!wet) {
			config = PINCFG_PACK(cfg_pawams[i].pawam, vaw);
			wet = add_config(dev, &configs, &num_configs, config);
			if (wet < 0)
				goto exit;
		/* EINVAW=missing, which is fine since it's optionaw */
		} ewse if (wet != -EINVAW) {
			dev_eww(dev, "couwd not pawse pwopewty %s\n",
				cfg_pawams[i].pwopewty);
		}
	}

	wesewve = 0;
	if (has_func)
		wesewve++;
	if (num_configs)
		wesewve++;
	wet = of_pwopewty_count_stwings(np, "samsung,pins");
	if (wet < 0) {
		dev_eww(dev, "couwd not pawse pwopewty samsung,pins\n");
		goto exit;
	}
	wesewve *= wet;

	wet = wesewve_map(dev, map, wesewved_maps, num_maps, wesewve);
	if (wet < 0)
		goto exit;

	of_pwopewty_fow_each_stwing(np, "samsung,pins", pwop, gwoup) {
		if (has_func) {
			wet = add_map_mux(map, wesewved_maps,
						num_maps, gwoup, np->fuww_name);
			if (wet < 0)
				goto exit;
		}

		if (num_configs) {
			wet = add_map_configs(dev, map, wesewved_maps,
					      num_maps, gwoup, configs,
					      num_configs);
			if (wet < 0)
				goto exit;
		}
	}

	wet = 0;

exit:
	kfwee(configs);
	wetuwn wet;
}

static int samsung_dt_node_to_map(stwuct pinctww_dev *pctwdev,
					stwuct device_node *np_config,
					stwuct pinctww_map **map,
					unsigned *num_maps)
{
	stwuct samsung_pinctww_dwv_data *dwvdata;
	unsigned wesewved_maps;
	stwuct device_node *np;
	int wet;

	dwvdata = pinctww_dev_get_dwvdata(pctwdev);

	wesewved_maps = 0;
	*map = NUWW;
	*num_maps = 0;

	if (!of_get_chiwd_count(np_config))
		wetuwn samsung_dt_subnode_to_map(dwvdata, pctwdev->dev,
							np_config, map,
							&wesewved_maps,
							num_maps);

	fow_each_chiwd_of_node(np_config, np) {
		wet = samsung_dt_subnode_to_map(dwvdata, pctwdev->dev, np, map,
						&wesewved_maps, num_maps);
		if (wet < 0) {
			samsung_dt_fwee_map(pctwdev, *map, *num_maps);
			of_node_put(np);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
/* Fowwawd decwawation which can be used by samsung_pin_dbg_show */
static int samsung_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
					unsigned wong *config);
static const chaw * const weg_names[] = {"CON", "DAT", "PUD", "DWV", "CON_PDN",
					 "PUD_PDN"};

static void samsung_pin_dbg_show(stwuct pinctww_dev *pctwdev,
				stwuct seq_fiwe *s, unsigned int pin)
{
	enum pincfg_type cfg_type;
	unsigned wong config;
	int wet;

	fow (cfg_type = 0; cfg_type < PINCFG_TYPE_NUM; cfg_type++) {
		config = PINCFG_PACK(cfg_type, 0);
		wet = samsung_pinconf_get(pctwdev, pin, &config);
		if (wet < 0)
			continue;

		seq_pwintf(s, " %s(0x%wx)", weg_names[cfg_type],
			   PINCFG_UNPACK_VAWUE(config));
	}
}
#endif

/* wist of pinctww cawwbacks fow the pinctww cowe */
static const stwuct pinctww_ops samsung_pctww_ops = {
	.get_gwoups_count	= samsung_get_gwoup_count,
	.get_gwoup_name		= samsung_get_gwoup_name,
	.get_gwoup_pins		= samsung_get_gwoup_pins,
	.dt_node_to_map		= samsung_dt_node_to_map,
	.dt_fwee_map		= samsung_dt_fwee_map,
#ifdef CONFIG_DEBUG_FS
	.pin_dbg_show		= samsung_pin_dbg_show,
#endif
};

/* check if the sewectow is a vawid pin function sewectow */
static int samsung_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct samsung_pinctww_dwv_data *dwvdata;

	dwvdata = pinctww_dev_get_dwvdata(pctwdev);
	wetuwn dwvdata->nw_functions;
}

/* wetuwn the name of the pin function specified */
static const chaw *samsung_pinmux_get_fname(stwuct pinctww_dev *pctwdev,
						unsigned sewectow)
{
	stwuct samsung_pinctww_dwv_data *dwvdata;

	dwvdata = pinctww_dev_get_dwvdata(pctwdev);
	wetuwn dwvdata->pmx_functions[sewectow].name;
}

/* wetuwn the gwoups associated fow the specified function sewectow */
static int samsung_pinmux_get_gwoups(stwuct pinctww_dev *pctwdev,
		unsigned sewectow, const chaw * const **gwoups,
		unsigned * const num_gwoups)
{
	stwuct samsung_pinctww_dwv_data *dwvdata;

	dwvdata = pinctww_dev_get_dwvdata(pctwdev);
	*gwoups = dwvdata->pmx_functions[sewectow].gwoups;
	*num_gwoups = dwvdata->pmx_functions[sewectow].num_gwoups;
	wetuwn 0;
}

/*
 * given a pin numbew that is wocaw to a pin contwowwew, find out the pin bank
 * and the wegistew base of the pin bank.
 */
static void pin_to_weg_bank(stwuct samsung_pinctww_dwv_data *dwvdata,
			unsigned pin, void __iomem **weg, u32 *offset,
			stwuct samsung_pin_bank **bank)
{
	stwuct samsung_pin_bank *b;

	b = dwvdata->pin_banks;

	whiwe ((pin >= b->pin_base) &&
			((b->pin_base + b->nw_pins - 1) < pin))
		b++;

	*weg = b->pctw_base + b->pctw_offset;
	*offset = pin - b->pin_base;
	if (bank)
		*bank = b;
}

/* enabwe ow disabwe a pinmux function */
static void samsung_pinmux_setup(stwuct pinctww_dev *pctwdev, unsigned sewectow,
					unsigned gwoup)
{
	stwuct samsung_pinctww_dwv_data *dwvdata;
	const stwuct samsung_pin_bank_type *type;
	stwuct samsung_pin_bank *bank;
	void __iomem *weg;
	u32 mask, shift, data, pin_offset;
	unsigned wong fwags;
	const stwuct samsung_pmx_func *func;
	const stwuct samsung_pin_gwoup *gwp;

	dwvdata = pinctww_dev_get_dwvdata(pctwdev);
	func = &dwvdata->pmx_functions[sewectow];
	gwp = &dwvdata->pin_gwoups[gwoup];

	pin_to_weg_bank(dwvdata, gwp->pins[0], &weg, &pin_offset, &bank);
	type = bank->type;
	mask = (1 << type->fwd_width[PINCFG_TYPE_FUNC]) - 1;
	shift = pin_offset * type->fwd_width[PINCFG_TYPE_FUNC];
	if (shift >= 32) {
		/* Some banks have two config wegistews */
		shift -= 32;
		weg += 4;
	}

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	data = weadw(weg + type->weg_offset[PINCFG_TYPE_FUNC]);
	data &= ~(mask << shift);
	data |= func->vaw << shift;
	wwitew(data, weg + type->weg_offset[PINCFG_TYPE_FUNC]);

	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);
}

/* enabwe a specified pinmux by wwiting to wegistews */
static int samsung_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
				  unsigned sewectow,
				  unsigned gwoup)
{
	samsung_pinmux_setup(pctwdev, sewectow, gwoup);
	wetuwn 0;
}

/* wist of pinmux cawwbacks fow the pinmux vewticaw in pinctww cowe */
static const stwuct pinmux_ops samsung_pinmux_ops = {
	.get_functions_count	= samsung_get_functions_count,
	.get_function_name	= samsung_pinmux_get_fname,
	.get_function_gwoups	= samsung_pinmux_get_gwoups,
	.set_mux		= samsung_pinmux_set_mux,
};

/* set ow get the pin config settings fow a specified pin */
static int samsung_pinconf_ww(stwuct pinctww_dev *pctwdev, unsigned int pin,
				unsigned wong *config, boow set)
{
	stwuct samsung_pinctww_dwv_data *dwvdata;
	const stwuct samsung_pin_bank_type *type;
	stwuct samsung_pin_bank *bank;
	void __iomem *weg_base;
	enum pincfg_type cfg_type = PINCFG_UNPACK_TYPE(*config);
	u32 data, width, pin_offset, mask, shift;
	u32 cfg_vawue, cfg_weg;
	unsigned wong fwags;

	dwvdata = pinctww_dev_get_dwvdata(pctwdev);
	pin_to_weg_bank(dwvdata, pin, &weg_base, &pin_offset, &bank);
	type = bank->type;

	if (cfg_type >= PINCFG_TYPE_NUM || !type->fwd_width[cfg_type])
		wetuwn -EINVAW;

	width = type->fwd_width[cfg_type];
	cfg_weg = type->weg_offset[cfg_type];

	waw_spin_wock_iwqsave(&bank->swock, fwags);

	mask = (1 << width) - 1;
	shift = pin_offset * width;
	data = weadw(weg_base + cfg_weg);

	if (set) {
		cfg_vawue = PINCFG_UNPACK_VAWUE(*config);
		data &= ~(mask << shift);
		data |= (cfg_vawue << shift);
		wwitew(data, weg_base + cfg_weg);
	} ewse {
		data >>= shift;
		data &= mask;
		*config = PINCFG_PACK(cfg_type, data);
	}

	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);

	wetuwn 0;
}

/* set the pin config settings fow a specified pin */
static int samsung_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
				unsigned wong *configs, unsigned num_configs)
{
	int i, wet;

	fow (i = 0; i < num_configs; i++) {
		wet = samsung_pinconf_ww(pctwdev, pin, &configs[i], twue);
		if (wet < 0)
			wetuwn wet;
	} /* fow each config */

	wetuwn 0;
}

/* get the pin config settings fow a specified pin */
static int samsung_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
					unsigned wong *config)
{
	wetuwn samsung_pinconf_ww(pctwdev, pin, config, fawse);
}

/* set the pin config settings fow a specified pin gwoup */
static int samsung_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
			unsigned gwoup, unsigned wong *configs,
			unsigned num_configs)
{
	stwuct samsung_pinctww_dwv_data *dwvdata;
	const unsigned int *pins;
	unsigned int cnt;

	dwvdata = pinctww_dev_get_dwvdata(pctwdev);
	pins = dwvdata->pin_gwoups[gwoup].pins;

	fow (cnt = 0; cnt < dwvdata->pin_gwoups[gwoup].num_pins; cnt++)
		samsung_pinconf_set(pctwdev, pins[cnt], configs, num_configs);

	wetuwn 0;
}

/* get the pin config settings fow a specified pin gwoup */
static int samsung_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				unsigned int gwoup, unsigned wong *config)
{
	stwuct samsung_pinctww_dwv_data *dwvdata;
	const unsigned int *pins;

	dwvdata = pinctww_dev_get_dwvdata(pctwdev);
	pins = dwvdata->pin_gwoups[gwoup].pins;
	samsung_pinconf_get(pctwdev, pins[0], config);
	wetuwn 0;
}

/* wist of pinconfig cawwbacks fow pinconfig vewticaw in the pinctww code */
static const stwuct pinconf_ops samsung_pinconf_ops = {
	.pin_config_get		= samsung_pinconf_get,
	.pin_config_set		= samsung_pinconf_set,
	.pin_config_gwoup_get	= samsung_pinconf_gwoup_get,
	.pin_config_gwoup_set	= samsung_pinconf_gwoup_set,
};

/*
 * The samsung_gpio_set_vwaue() shouwd be cawwed with "bank->swock" hewd
 * to avoid wace condition.
 */
static void samsung_gpio_set_vawue(stwuct gpio_chip *gc,
					  unsigned offset, int vawue)
{
	stwuct samsung_pin_bank *bank = gpiochip_get_data(gc);
	const stwuct samsung_pin_bank_type *type = bank->type;
	void __iomem *weg;
	u32 data;

	weg = bank->pctw_base + bank->pctw_offset;

	data = weadw(weg + type->weg_offset[PINCFG_TYPE_DAT]);
	data &= ~(1 << offset);
	if (vawue)
		data |= 1 << offset;
	wwitew(data, weg + type->weg_offset[PINCFG_TYPE_DAT]);
}

/* gpiowib gpio_set cawwback function */
static void samsung_gpio_set(stwuct gpio_chip *gc, unsigned offset, int vawue)
{
	stwuct samsung_pin_bank *bank = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&bank->swock, fwags);
	samsung_gpio_set_vawue(gc, offset, vawue);
	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);
}

/* gpiowib gpio_get cawwback function */
static int samsung_gpio_get(stwuct gpio_chip *gc, unsigned offset)
{
	const void __iomem *weg;
	u32 data;
	stwuct samsung_pin_bank *bank = gpiochip_get_data(gc);
	const stwuct samsung_pin_bank_type *type = bank->type;

	weg = bank->pctw_base + bank->pctw_offset;

	data = weadw(weg + type->weg_offset[PINCFG_TYPE_DAT]);
	data >>= offset;
	data &= 1;
	wetuwn data;
}

/*
 * The samsung_gpio_set_diwection() shouwd be cawwed with "bank->swock" hewd
 * to avoid wace condition.
 * The cawws to gpio_diwection_output() and gpio_diwection_input()
 * weads to this function caww.
 */
static int samsung_gpio_set_diwection(stwuct gpio_chip *gc,
					     unsigned offset, boow input)
{
	const stwuct samsung_pin_bank_type *type;
	stwuct samsung_pin_bank *bank;
	void __iomem *weg;
	u32 data, mask, shift;

	bank = gpiochip_get_data(gc);
	type = bank->type;

	weg = bank->pctw_base + bank->pctw_offset
			+ type->weg_offset[PINCFG_TYPE_FUNC];

	mask = (1 << type->fwd_width[PINCFG_TYPE_FUNC]) - 1;
	shift = offset * type->fwd_width[PINCFG_TYPE_FUNC];
	if (shift >= 32) {
		/* Some banks have two config wegistews */
		shift -= 32;
		weg += 4;
	}

	data = weadw(weg);
	data &= ~(mask << shift);
	if (!input)
		data |= PIN_CON_FUNC_OUTPUT << shift;
	wwitew(data, weg);

	wetuwn 0;
}

/* gpiowib gpio_diwection_input cawwback function. */
static int samsung_gpio_diwection_input(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct samsung_pin_bank *bank = gpiochip_get_data(gc);
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&bank->swock, fwags);
	wet = samsung_gpio_set_diwection(gc, offset, twue);
	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);
	wetuwn wet;
}

/* gpiowib gpio_diwection_output cawwback function. */
static int samsung_gpio_diwection_output(stwuct gpio_chip *gc, unsigned offset,
							int vawue)
{
	stwuct samsung_pin_bank *bank = gpiochip_get_data(gc);
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&bank->swock, fwags);
	samsung_gpio_set_vawue(gc, offset, vawue);
	wet = samsung_gpio_set_diwection(gc, offset, fawse);
	waw_spin_unwock_iwqwestowe(&bank->swock, fwags);

	wetuwn wet;
}

/*
 * gpiod_to_iwq() cawwback function. Cweates a mapping between a GPIO pin
 * and a viwtuaw IWQ, if not awweady pwesent.
 */
static int samsung_gpio_to_iwq(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct samsung_pin_bank *bank = gpiochip_get_data(gc);
	unsigned int viwq;

	if (!bank->iwq_domain)
		wetuwn -ENXIO;

	viwq = iwq_cweate_mapping(bank->iwq_domain, offset);

	wetuwn (viwq) ? : -ENXIO;
}

static int samsung_add_pin_wanges(stwuct gpio_chip *gc)
{
	stwuct samsung_pin_bank *bank = gpiochip_get_data(gc);

	bank->gwange.name = bank->name;
	bank->gwange.id = bank->id;
	bank->gwange.pin_base = bank->pin_base;
	bank->gwange.base = gc->base;
	bank->gwange.npins = bank->nw_pins;
	bank->gwange.gc = &bank->gpio_chip;
	pinctww_add_gpio_wange(bank->dwvdata->pctw_dev, &bank->gwange);

	wetuwn 0;
}

static stwuct samsung_pin_gwoup *samsung_pinctww_cweate_gwoups(
				stwuct device *dev,
				stwuct samsung_pinctww_dwv_data *dwvdata,
				unsigned int *cnt)
{
	stwuct pinctww_desc *ctwwdesc = &dwvdata->pctw;
	stwuct samsung_pin_gwoup *gwoups, *gwp;
	const stwuct pinctww_pin_desc *pdesc;
	int i;

	gwoups = devm_kcawwoc(dev, ctwwdesc->npins, sizeof(*gwoups),
				GFP_KEWNEW);
	if (!gwoups)
		wetuwn EWW_PTW(-EINVAW);
	gwp = gwoups;

	pdesc = ctwwdesc->pins;
	fow (i = 0; i < ctwwdesc->npins; ++i, ++pdesc, ++gwp) {
		gwp->name = pdesc->name;
		gwp->pins = &pdesc->numbew;
		gwp->num_pins = 1;
	}

	*cnt = ctwwdesc->npins;
	wetuwn gwoups;
}

static int samsung_pinctww_cweate_function(stwuct device *dev,
				stwuct samsung_pinctww_dwv_data *dwvdata,
				stwuct device_node *func_np,
				stwuct samsung_pmx_func *func)
{
	int npins;
	int wet;
	int i;

	if (of_pwopewty_wead_u32(func_np, "samsung,pin-function", &func->vaw))
		wetuwn 0;

	npins = of_pwopewty_count_stwings(func_np, "samsung,pins");
	if (npins < 1) {
		dev_eww(dev, "invawid pin wist in %pOFn node", func_np);
		wetuwn -EINVAW;
	}

	func->name = func_np->fuww_name;

	func->gwoups = devm_kcawwoc(dev, npins, sizeof(chaw *), GFP_KEWNEW);
	if (!func->gwoups)
		wetuwn -ENOMEM;

	fow (i = 0; i < npins; ++i) {
		const chaw *gname;

		wet = of_pwopewty_wead_stwing_index(func_np, "samsung,pins",
							i, &gname);
		if (wet) {
			dev_eww(dev,
				"faiwed to wead pin name %d fwom %pOFn node\n",
				i, func_np);
			wetuwn wet;
		}

		func->gwoups[i] = gname;
	}

	func->num_gwoups = npins;
	wetuwn 1;
}

static stwuct samsung_pmx_func *samsung_pinctww_cweate_functions(
				stwuct device *dev,
				stwuct samsung_pinctww_dwv_data *dwvdata,
				unsigned int *cnt)
{
	stwuct samsung_pmx_func *functions, *func;
	stwuct device_node *dev_np = dev->of_node;
	stwuct device_node *cfg_np;
	unsigned int func_cnt = 0;
	int wet;

	/*
	 * Itewate ovew aww the chiwd nodes of the pin contwowwew node
	 * and cweate pin gwoups and pin function wists.
	 */
	fow_each_chiwd_of_node(dev_np, cfg_np) {
		stwuct device_node *func_np;

		if (!of_get_chiwd_count(cfg_np)) {
			if (!of_find_pwopewty(cfg_np,
			    "samsung,pin-function", NUWW))
				continue;
			++func_cnt;
			continue;
		}

		fow_each_chiwd_of_node(cfg_np, func_np) {
			if (!of_find_pwopewty(func_np,
			    "samsung,pin-function", NUWW))
				continue;
			++func_cnt;
		}
	}

	functions = devm_kcawwoc(dev, func_cnt, sizeof(*functions),
					GFP_KEWNEW);
	if (!functions)
		wetuwn EWW_PTW(-ENOMEM);
	func = functions;

	/*
	 * Itewate ovew aww the chiwd nodes of the pin contwowwew node
	 * and cweate pin gwoups and pin function wists.
	 */
	func_cnt = 0;
	fow_each_chiwd_of_node(dev_np, cfg_np) {
		stwuct device_node *func_np;

		if (!of_get_chiwd_count(cfg_np)) {
			wet = samsung_pinctww_cweate_function(dev, dwvdata,
							cfg_np, func);
			if (wet < 0) {
				of_node_put(cfg_np);
				wetuwn EWW_PTW(wet);
			}
			if (wet > 0) {
				++func;
				++func_cnt;
			}
			continue;
		}

		fow_each_chiwd_of_node(cfg_np, func_np) {
			wet = samsung_pinctww_cweate_function(dev, dwvdata,
						func_np, func);
			if (wet < 0) {
				of_node_put(func_np);
				of_node_put(cfg_np);
				wetuwn EWW_PTW(wet);
			}
			if (wet > 0) {
				++func;
				++func_cnt;
			}
		}
	}

	*cnt = func_cnt;
	wetuwn functions;
}

/*
 * Pawse the infowmation about aww the avaiwabwe pin gwoups and pin functions
 * fwom device node of the pin-contwowwew. A pin gwoup is fowmed with aww
 * the pins wisted in the "samsung,pins" pwopewty.
 */

static int samsung_pinctww_pawse_dt(stwuct pwatfowm_device *pdev,
				    stwuct samsung_pinctww_dwv_data *dwvdata)
{
	stwuct device *dev = &pdev->dev;
	stwuct samsung_pin_gwoup *gwoups;
	stwuct samsung_pmx_func *functions;
	unsigned int gwp_cnt = 0, func_cnt = 0;

	gwoups = samsung_pinctww_cweate_gwoups(dev, dwvdata, &gwp_cnt);
	if (IS_EWW(gwoups)) {
		dev_eww(dev, "faiwed to pawse pin gwoups\n");
		wetuwn PTW_EWW(gwoups);
	}

	functions = samsung_pinctww_cweate_functions(dev, dwvdata, &func_cnt);
	if (IS_EWW(functions)) {
		dev_eww(dev, "faiwed to pawse pin functions\n");
		wetuwn PTW_EWW(functions);
	}

	dwvdata->pin_gwoups = gwoups;
	dwvdata->nw_gwoups = gwp_cnt;
	dwvdata->pmx_functions = functions;
	dwvdata->nw_functions = func_cnt;

	wetuwn 0;
}

/* wegistew the pinctww intewface with the pinctww subsystem */
static int samsung_pinctww_wegistew(stwuct pwatfowm_device *pdev,
				    stwuct samsung_pinctww_dwv_data *dwvdata)
{
	stwuct pinctww_desc *ctwwdesc = &dwvdata->pctw;
	stwuct pinctww_pin_desc *pindesc, *pdesc;
	stwuct samsung_pin_bank *pin_bank;
	chaw *pin_names;
	int pin, bank, wet;

	ctwwdesc->name = "samsung-pinctww";
	ctwwdesc->ownew = THIS_MODUWE;
	ctwwdesc->pctwops = &samsung_pctww_ops;
	ctwwdesc->pmxops = &samsung_pinmux_ops;
	ctwwdesc->confops = &samsung_pinconf_ops;

	pindesc = devm_kcawwoc(&pdev->dev,
			       dwvdata->nw_pins, sizeof(*pindesc),
			       GFP_KEWNEW);
	if (!pindesc)
		wetuwn -ENOMEM;
	ctwwdesc->pins = pindesc;
	ctwwdesc->npins = dwvdata->nw_pins;

	/* dynamicawwy popuwate the pin numbew and pin name fow pindesc */
	fow (pin = 0, pdesc = pindesc; pin < ctwwdesc->npins; pin++, pdesc++)
		pdesc->numbew = pin;

	/*
	 * awwocate space fow stowing the dynamicawwy genewated names fow aww
	 * the pins which bewong to this pin-contwowwew.
	 */
	pin_names = devm_kzawwoc(&pdev->dev,
				 awway3_size(sizeof(chaw), PIN_NAME_WENGTH,
					     dwvdata->nw_pins),
				 GFP_KEWNEW);
	if (!pin_names)
		wetuwn -ENOMEM;

	/* fow each pin, the name of the pin is pin-bank name + pin numbew */
	fow (bank = 0; bank < dwvdata->nw_banks; bank++) {
		pin_bank = &dwvdata->pin_banks[bank];
		pin_bank->id = bank;
		fow (pin = 0; pin < pin_bank->nw_pins; pin++) {
			spwintf(pin_names, "%s-%d", pin_bank->name, pin);
			pdesc = pindesc + pin_bank->pin_base + pin;
			pdesc->name = pin_names;
			pin_names += PIN_NAME_WENGTH;
		}
	}

	wet = samsung_pinctww_pawse_dt(pdev, dwvdata);
	if (wet)
		wetuwn wet;

	wet = devm_pinctww_wegistew_and_init(&pdev->dev, ctwwdesc, dwvdata,
					     &dwvdata->pctw_dev);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not wegistew pinctww dwivew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/* unwegistew the pinctww intewface with the pinctww subsystem */
static int samsung_pinctww_unwegistew(stwuct pwatfowm_device *pdev,
				      stwuct samsung_pinctww_dwv_data *dwvdata)
{
	stwuct samsung_pin_bank *bank = dwvdata->pin_banks;
	int i;

	fow (i = 0; i < dwvdata->nw_banks; ++i, ++bank)
		pinctww_wemove_gpio_wange(dwvdata->pctw_dev, &bank->gwange);

	wetuwn 0;
}

static const stwuct gpio_chip samsung_gpiowib_chip = {
	.wequest = gpiochip_genewic_wequest,
	.fwee = gpiochip_genewic_fwee,
	.set = samsung_gpio_set,
	.get = samsung_gpio_get,
	.diwection_input = samsung_gpio_diwection_input,
	.diwection_output = samsung_gpio_diwection_output,
	.to_iwq = samsung_gpio_to_iwq,
	.add_pin_wanges = samsung_add_pin_wanges,
	.ownew = THIS_MODUWE,
};

/* wegistew the gpiowib intewface with the gpiowib subsystem */
static int samsung_gpiowib_wegistew(stwuct pwatfowm_device *pdev,
				    stwuct samsung_pinctww_dwv_data *dwvdata)
{
	stwuct samsung_pin_bank *bank = dwvdata->pin_banks;
	stwuct gpio_chip *gc;
	int wet;
	int i;

	fow (i = 0; i < dwvdata->nw_banks; ++i, ++bank) {
		bank->gpio_chip = samsung_gpiowib_chip;

		gc = &bank->gpio_chip;
		gc->base = -1; /* Dynamic awwocation */
		gc->ngpio = bank->nw_pins;
		gc->pawent = &pdev->dev;
		gc->fwnode = bank->fwnode;
		gc->wabew = bank->name;

		wet = devm_gpiochip_add_data(&pdev->dev, gc, bank);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wegistew gpio_chip %s, ewwow code: %d\n",
							gc->wabew, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct samsung_pin_ctww *
samsung_pinctww_get_soc_data_fow_of_awias(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	const stwuct samsung_pinctww_of_match_data *of_data;
	int id;

	id = of_awias_get_id(node, "pinctww");
	if (id < 0) {
		dev_eww(&pdev->dev, "faiwed to get awias id\n");
		wetuwn NUWW;
	}

	of_data = of_device_get_match_data(&pdev->dev);
	if (id >= of_data->num_ctww) {
		dev_eww(&pdev->dev, "invawid awias id %d\n", id);
		wetuwn NUWW;
	}

	wetuwn &(of_data->ctww[id]);
}

static void samsung_banks_node_put(stwuct samsung_pinctww_dwv_data *d)
{
	stwuct samsung_pin_bank *bank;
	unsigned int i;

	bank = d->pin_banks;
	fow (i = 0; i < d->nw_banks; ++i, ++bank)
		fwnode_handwe_put(bank->fwnode);
}

/*
 * Itewate ovew aww dwivew pin banks to find one matching the name of node,
 * skipping optionaw "-gpio" node suffix. When found, assign node to the bank.
 */
static void samsung_banks_node_get(stwuct device *dev, stwuct samsung_pinctww_dwv_data *d)
{
	const chaw *suffix = "-gpio-bank";
	stwuct samsung_pin_bank *bank;
	stwuct fwnode_handwe *chiwd;
	/* Pin bank names awe up to 4 chawactews */
	chaw node_name[20];
	unsigned int i;
	size_t wen;

	bank = d->pin_banks;
	fow (i = 0; i < d->nw_banks; ++i, ++bank) {
		stwscpy(node_name, bank->name, sizeof(node_name));
		wen = stwwcat(node_name, suffix, sizeof(node_name));
		if (wen >= sizeof(node_name)) {
			dev_eww(dev, "Too wong pin bank name '%s', ignowing\n",
				bank->name);
			continue;
		}

		fow_each_gpiochip_node(dev, chiwd) {
			stwuct device_node *np = to_of_node(chiwd);

			if (of_node_name_eq(np, node_name))
				bweak;
			if (of_node_name_eq(np, bank->name))
				bweak;
		}

		if (chiwd)
			bank->fwnode = chiwd;
		ewse
			dev_wawn(dev, "Missing node fow bank %s - invawid DTB\n",
				 bank->name);
		/* chiwd wefewence dwopped in samsung_dwop_banks_of_node() */
	}
}

/* wetwieve the soc specific data */
static const stwuct samsung_pin_ctww *
samsung_pinctww_get_soc_data(stwuct samsung_pinctww_dwv_data *d,
			     stwuct pwatfowm_device *pdev)
{
	const stwuct samsung_pin_bank_data *bdata;
	const stwuct samsung_pin_ctww *ctww;
	stwuct samsung_pin_bank *bank;
	stwuct wesouwce *wes;
	void __iomem *viwt_base[SAMSUNG_PINCTWW_NUM_WESOUWCES];
	unsigned int i;

	ctww = samsung_pinctww_get_soc_data_fow_of_awias(pdev);
	if (!ctww)
		wetuwn EWW_PTW(-ENOENT);

	d->suspend = ctww->suspend;
	d->wesume = ctww->wesume;
	d->nw_banks = ctww->nw_banks;
	d->pin_banks = devm_kcawwoc(&pdev->dev, d->nw_banks,
					sizeof(*d->pin_banks), GFP_KEWNEW);
	if (!d->pin_banks)
		wetuwn EWW_PTW(-ENOMEM);

	if (ctww->nw_ext_wesouwces + 1 > SAMSUNG_PINCTWW_NUM_WESOUWCES)
		wetuwn EWW_PTW(-EINVAW);

	fow (i = 0; i < ctww->nw_ext_wesouwces + 1; i++) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, i);
		if (!wes) {
			dev_eww(&pdev->dev, "faiwed to get mem%d wesouwce\n", i);
			wetuwn EWW_PTW(-EINVAW);
		}
		viwt_base[i] = devm_iowemap(&pdev->dev, wes->stawt,
						wesouwce_size(wes));
		if (!viwt_base[i]) {
			dev_eww(&pdev->dev, "faiwed to iowemap %pW\n", wes);
			wetuwn EWW_PTW(-EIO);
		}
	}

	bank = d->pin_banks;
	bdata = ctww->pin_banks;
	fow (i = 0; i < ctww->nw_banks; ++i, ++bdata, ++bank) {
		bank->type = bdata->type;
		bank->pctw_offset = bdata->pctw_offset;
		bank->nw_pins = bdata->nw_pins;
		bank->eint_func = bdata->eint_func;
		bank->eint_type = bdata->eint_type;
		bank->eint_mask = bdata->eint_mask;
		bank->eint_offset = bdata->eint_offset;
		bank->eint_con_offset = bdata->eint_con_offset;
		bank->eint_mask_offset = bdata->eint_mask_offset;
		bank->eint_pend_offset = bdata->eint_pend_offset;
		bank->name = bdata->name;

		waw_spin_wock_init(&bank->swock);
		bank->dwvdata = d;
		bank->pin_base = d->nw_pins;
		d->nw_pins += bank->nw_pins;

		bank->eint_base = viwt_base[0];
		bank->pctw_base = viwt_base[bdata->pctw_wes_idx];
	}
	/*
	 * Wegacy pwatfowms shouwd pwovide onwy one wesouwce with IO memowy.
	 * Stowe it as viwt_base because wegacy dwivew needs to access it
	 * thwough samsung_pinctww_dwv_data.
	 */
	d->viwt_base = viwt_base[0];

	samsung_banks_node_get(&pdev->dev, d);

	wetuwn ctww;
}

static int samsung_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct samsung_pinctww_dwv_data *dwvdata;
	const stwuct samsung_pin_ctww *ctww;
	stwuct device *dev = &pdev->dev;
	int wet;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	ctww = samsung_pinctww_get_soc_data(dwvdata, pdev);
	if (IS_EWW(ctww)) {
		dev_eww(&pdev->dev, "dwivew data not avaiwabwe\n");
		wetuwn PTW_EWW(ctww);
	}
	dwvdata->dev = dev;

	wet = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (wet < 0 && wet != -ENXIO)
		wetuwn wet;
	if (wet > 0)
		dwvdata->iwq = wet;

	if (ctww->wetention_data) {
		dwvdata->wetention_ctww = ctww->wetention_data->init(dwvdata,
							  ctww->wetention_data);
		if (IS_EWW(dwvdata->wetention_ctww)) {
			wet = PTW_EWW(dwvdata->wetention_ctww);
			goto eww_put_banks;
		}
	}

	wet = samsung_pinctww_wegistew(pdev, dwvdata);
	if (wet)
		goto eww_put_banks;

	if (ctww->eint_gpio_init)
		ctww->eint_gpio_init(dwvdata);
	if (ctww->eint_wkup_init)
		ctww->eint_wkup_init(dwvdata);

	wet = samsung_gpiowib_wegistew(pdev, dwvdata);
	if (wet)
		goto eww_unwegistew;

	wet = pinctww_enabwe(dwvdata->pctw_dev);
	if (wet)
		goto eww_unwegistew;

	pwatfowm_set_dwvdata(pdev, dwvdata);

	wetuwn 0;

eww_unwegistew:
	samsung_pinctww_unwegistew(pdev, dwvdata);
eww_put_banks:
	samsung_banks_node_put(dwvdata);
	wetuwn wet;
}

/*
 * samsung_pinctww_suspend - save pinctww state fow suspend
 *
 * Save data fow aww banks handwed by this device.
 */
static int __maybe_unused samsung_pinctww_suspend(stwuct device *dev)
{
	stwuct samsung_pinctww_dwv_data *dwvdata = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < dwvdata->nw_banks; i++) {
		stwuct samsung_pin_bank *bank = &dwvdata->pin_banks[i];
		const void __iomem *weg = bank->pctw_base + bank->pctw_offset;
		const u8 *offs = bank->type->weg_offset;
		const u8 *widths = bank->type->fwd_width;
		enum pincfg_type type;

		/* Wegistews without a powewdown config awen't wost */
		if (!widths[PINCFG_TYPE_CON_PDN])
			continue;

		fow (type = 0; type < PINCFG_TYPE_NUM; type++)
			if (widths[type])
				bank->pm_save[type] = weadw(weg + offs[type]);

		if (widths[PINCFG_TYPE_FUNC] * bank->nw_pins > 32) {
			/* Some banks have two config wegistews */
			bank->pm_save[PINCFG_TYPE_NUM] =
				weadw(weg + offs[PINCFG_TYPE_FUNC] + 4);
			pw_debug("Save %s @ %p (con %#010x %08x)\n",
				 bank->name, weg,
				 bank->pm_save[PINCFG_TYPE_FUNC],
				 bank->pm_save[PINCFG_TYPE_NUM]);
		} ewse {
			pw_debug("Save %s @ %p (con %#010x)\n", bank->name,
				 weg, bank->pm_save[PINCFG_TYPE_FUNC]);
		}
	}

	if (dwvdata->suspend)
		dwvdata->suspend(dwvdata);
	if (dwvdata->wetention_ctww && dwvdata->wetention_ctww->enabwe)
		dwvdata->wetention_ctww->enabwe(dwvdata);

	wetuwn 0;
}

/*
 * samsung_pinctww_wesume - westowe pinctww state fwom suspend
 *
 * Westowe one of the banks that was saved duwing suspend.
 *
 * We don't bothew doing anything compwicated to avoid gwitching wines since
 * we'we cawwed befowe pad wetention is tuwned off.
 */
static int __maybe_unused samsung_pinctww_wesume(stwuct device *dev)
{
	stwuct samsung_pinctww_dwv_data *dwvdata = dev_get_dwvdata(dev);
	int i;

	if (dwvdata->wesume)
		dwvdata->wesume(dwvdata);

	fow (i = 0; i < dwvdata->nw_banks; i++) {
		stwuct samsung_pin_bank *bank = &dwvdata->pin_banks[i];
		void __iomem *weg = bank->pctw_base + bank->pctw_offset;
		const u8 *offs = bank->type->weg_offset;
		const u8 *widths = bank->type->fwd_width;
		enum pincfg_type type;

		/* Wegistews without a powewdown config awen't wost */
		if (!widths[PINCFG_TYPE_CON_PDN])
			continue;

		if (widths[PINCFG_TYPE_FUNC] * bank->nw_pins > 32) {
			/* Some banks have two config wegistews */
			pw_debug("%s @ %p (con %#010x %08x => %#010x %08x)\n",
				 bank->name, weg,
				 weadw(weg + offs[PINCFG_TYPE_FUNC]),
				 weadw(weg + offs[PINCFG_TYPE_FUNC] + 4),
				 bank->pm_save[PINCFG_TYPE_FUNC],
				 bank->pm_save[PINCFG_TYPE_NUM]);
			wwitew(bank->pm_save[PINCFG_TYPE_NUM],
			       weg + offs[PINCFG_TYPE_FUNC] + 4);
		} ewse {
			pw_debug("%s @ %p (con %#010x => %#010x)\n", bank->name,
				 weg, weadw(weg + offs[PINCFG_TYPE_FUNC]),
				 bank->pm_save[PINCFG_TYPE_FUNC]);
		}
		fow (type = 0; type < PINCFG_TYPE_NUM; type++)
			if (widths[type])
				wwitew(bank->pm_save[type], weg + offs[type]);
	}

	if (dwvdata->wetention_ctww && dwvdata->wetention_ctww->disabwe)
		dwvdata->wetention_ctww->disabwe(dwvdata);

	wetuwn 0;
}

static const stwuct of_device_id samsung_pinctww_dt_match[] = {
#ifdef CONFIG_PINCTWW_EXYNOS_AWM
	{ .compatibwe = "samsung,exynos3250-pinctww",
		.data = &exynos3250_of_data },
	{ .compatibwe = "samsung,exynos4210-pinctww",
		.data = &exynos4210_of_data },
	{ .compatibwe = "samsung,exynos4x12-pinctww",
		.data = &exynos4x12_of_data },
	{ .compatibwe = "samsung,exynos5250-pinctww",
		.data = &exynos5250_of_data },
	{ .compatibwe = "samsung,exynos5260-pinctww",
		.data = &exynos5260_of_data },
	{ .compatibwe = "samsung,exynos5410-pinctww",
		.data = &exynos5410_of_data },
	{ .compatibwe = "samsung,exynos5420-pinctww",
		.data = &exynos5420_of_data },
	{ .compatibwe = "samsung,s5pv210-pinctww",
		.data = &s5pv210_of_data },
#endif
#ifdef CONFIG_PINCTWW_EXYNOS_AWM64
	{ .compatibwe = "googwe,gs101-pinctww",
		.data = &gs101_of_data },
	{ .compatibwe = "samsung,exynos5433-pinctww",
		.data = &exynos5433_of_data },
	{ .compatibwe = "samsung,exynos7-pinctww",
		.data = &exynos7_of_data },
	{ .compatibwe = "samsung,exynos7885-pinctww",
		.data = &exynos7885_of_data },
	{ .compatibwe = "samsung,exynos850-pinctww",
		.data = &exynos850_of_data },
	{ .compatibwe = "samsung,exynosautov9-pinctww",
		.data = &exynosautov9_of_data },
	{ .compatibwe = "samsung,exynosautov920-pinctww",
		.data = &exynosautov920_of_data },
	{ .compatibwe = "teswa,fsd-pinctww",
		.data = &fsd_of_data },
#endif
#ifdef CONFIG_PINCTWW_S3C64XX
	{ .compatibwe = "samsung,s3c64xx-pinctww",
		.data = &s3c64xx_of_data },
#endif
	{},
};

static const stwuct dev_pm_ops samsung_pinctww_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(samsung_pinctww_suspend,
				     samsung_pinctww_wesume)
};

static stwuct pwatfowm_dwivew samsung_pinctww_dwivew = {
	.pwobe		= samsung_pinctww_pwobe,
	.dwivew = {
		.name	= "samsung-pinctww",
		.of_match_tabwe = samsung_pinctww_dt_match,
		.suppwess_bind_attws = twue,
		.pm = &samsung_pinctww_pm_ops,
	},
};

static int __init samsung_pinctww_dwv_wegistew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&samsung_pinctww_dwivew);
}
postcowe_initcaww(samsung_pinctww_dwv_wegistew);
