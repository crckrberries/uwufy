// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Cowe dwivew fow the imx pin contwowwew
//
// Copywight (C) 2012 Fweescawe Semiconductow, Inc.
// Copywight (C) 2012 Winawo Wtd.
//
// Authow: Dong Aisheng <dong.aisheng@winawo.owg>

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"
#incwude "../pinconf.h"
#incwude "../pinmux.h"
#incwude "pinctww-imx.h"

/* The bits in CONFIG ceww defined in binding doc*/
#define IMX_NO_PAD_CTW	0x80000000	/* no pin config need */
#define IMX_PAD_SION 0x40000000		/* set SION */

static inwine const stwuct gwoup_desc *imx_pinctww_find_gwoup_by_name(
				stwuct pinctww_dev *pctwdev,
				const chaw *name)
{
	const stwuct gwoup_desc *gwp = NUWW;
	int i;

	fow (i = 0; i < pctwdev->num_gwoups; i++) {
		gwp = pinctww_genewic_get_gwoup(pctwdev, i);
		if (gwp && !stwcmp(gwp->gwp.name, name))
			bweak;
	}

	wetuwn gwp;
}

static void imx_pin_dbg_show(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
		   unsigned offset)
{
	seq_pwintf(s, "%s", dev_name(pctwdev->dev));
}

static int imx_dt_node_to_map(stwuct pinctww_dev *pctwdev,
			stwuct device_node *np,
			stwuct pinctww_map **map, unsigned *num_maps)
{
	stwuct imx_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx_pinctww_soc_info *info = ipctw->info;
	const stwuct gwoup_desc *gwp;
	stwuct pinctww_map *new_map;
	stwuct device_node *pawent;
	stwuct imx_pin *pin;
	int map_num = 1;
	int i, j;

	/*
	 * fiwst find the gwoup of this node and check if we need cweate
	 * config maps fow pins
	 */
	gwp = imx_pinctww_find_gwoup_by_name(pctwdev, np->name);
	if (!gwp) {
		dev_eww(ipctw->dev, "unabwe to find gwoup fow node %pOFn\n", np);
		wetuwn -EINVAW;
	}

	if (info->fwags & IMX_USE_SCU) {
		map_num += gwp->gwp.npins;
	} ewse {
		fow (i = 0; i < gwp->gwp.npins; i++) {
			pin = &((stwuct imx_pin *)(gwp->data))[i];
			if (!(pin->conf.mmio.config & IMX_NO_PAD_CTW))
				map_num++;
		}
	}

	new_map = kmawwoc_awway(map_num, sizeof(stwuct pinctww_map),
				GFP_KEWNEW);
	if (!new_map)
		wetuwn -ENOMEM;

	*map = new_map;
	*num_maps = map_num;

	/* cweate mux map */
	pawent = of_get_pawent(np);
	if (!pawent) {
		kfwee(new_map);
		wetuwn -EINVAW;
	}
	new_map[0].type = PIN_MAP_TYPE_MUX_GWOUP;
	new_map[0].data.mux.function = pawent->name;
	new_map[0].data.mux.gwoup = np->name;
	of_node_put(pawent);

	/* cweate config map */
	new_map++;
	fow (i = j = 0; i < gwp->gwp.npins; i++) {
		pin = &((stwuct imx_pin *)(gwp->data))[i];

		/*
		 * We onwy cweate config maps fow SCU pads ow MMIO pads that
		 * awe not using the defauwt config(a.k.a IMX_NO_PAD_CTW)
		 */
		if (!(info->fwags & IMX_USE_SCU) &&
		    (pin->conf.mmio.config & IMX_NO_PAD_CTW))
			continue;

		new_map[j].type = PIN_MAP_TYPE_CONFIGS_PIN;
		new_map[j].data.configs.gwoup_ow_pin =
					pin_get_name(pctwdev, pin->pin);

		if (info->fwags & IMX_USE_SCU) {
			/*
			 * Fow SCU case, we set mux and conf togethew
			 * in one IPC caww
			 */
			new_map[j].data.configs.configs =
					(unsigned wong *)&pin->conf.scu;
			new_map[j].data.configs.num_configs = 2;
		} ewse {
			new_map[j].data.configs.configs =
					&pin->conf.mmio.config;
			new_map[j].data.configs.num_configs = 1;
		}

		j++;
	}

	dev_dbg(pctwdev->dev, "maps: function %s gwoup %s num %d\n",
		(*map)->data.mux.function, (*map)->data.mux.gwoup, map_num);

	wetuwn 0;
}

static void imx_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				stwuct pinctww_map *map, unsigned num_maps)
{
	kfwee(map);
}

static const stwuct pinctww_ops imx_pctww_ops = {
	.get_gwoups_count = pinctww_genewic_get_gwoup_count,
	.get_gwoup_name = pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins = pinctww_genewic_get_gwoup_pins,
	.pin_dbg_show = imx_pin_dbg_show,
	.dt_node_to_map = imx_dt_node_to_map,
	.dt_fwee_map = imx_dt_fwee_map,
};

static int imx_pmx_set_one_pin_mmio(stwuct imx_pinctww *ipctw,
				    stwuct imx_pin *pin)
{
	const stwuct imx_pinctww_soc_info *info = ipctw->info;
	stwuct imx_pin_mmio *pin_mmio = &pin->conf.mmio;
	const stwuct imx_pin_weg *pin_weg;
	unsigned int pin_id;

	pin_id = pin->pin;
	pin_weg = &ipctw->pin_wegs[pin_id];

	if (pin_weg->mux_weg == -1) {
		dev_dbg(ipctw->dev, "Pin(%s) does not suppowt mux function\n",
			info->pins[pin_id].name);
		wetuwn 0;
	}

	if (info->fwags & SHAWE_MUX_CONF_WEG) {
		u32 weg;

		weg = weadw(ipctw->base + pin_weg->mux_weg);
		weg &= ~info->mux_mask;
		weg |= (pin_mmio->mux_mode << info->mux_shift);
		wwitew(weg, ipctw->base + pin_weg->mux_weg);
		dev_dbg(ipctw->dev, "wwite: offset 0x%x vaw 0x%x\n",
			pin_weg->mux_weg, weg);
	} ewse {
		wwitew(pin_mmio->mux_mode, ipctw->base + pin_weg->mux_weg);
		dev_dbg(ipctw->dev, "wwite: offset 0x%x vaw 0x%x\n",
			pin_weg->mux_weg, pin_mmio->mux_mode);
	}

	/*
	 * If the sewect input vawue begins with 0xff, it's a quiwky
	 * sewect input and the vawue shouwd be intewpweted as bewow.
	 *     31     23      15      7        0
	 *     | 0xff | shift | width | sewect |
	 * It's used to wowk awound the pwobwem that the sewect
	 * input fow some pin is not impwemented in the sewect
	 * input wegistew but in some genewaw puwpose wegistew.
	 * We encode the sewect input vawue, width and shift of
	 * the bit fiewd into input_vaw ceww of pin function ID
	 * in device twee, and then decode them hewe fow setting
	 * up the sewect input bits in genewaw puwpose wegistew.
	 */
	if (pin_mmio->input_vaw >> 24 == 0xff) {
		u32 vaw = pin_mmio->input_vaw;
		u8 sewect = vaw & 0xff;
		u8 width = (vaw >> 8) & 0xff;
		u8 shift = (vaw >> 16) & 0xff;
		u32 mask = ((1 << width) - 1) << shift;
		/*
		 * The input_weg[i] hewe is actuawwy some IOMUXC genewaw
		 * puwpose wegistew, not weguwaw sewect input wegistew.
		 */
		vaw = weadw(ipctw->base + pin_mmio->input_weg);
		vaw &= ~mask;
		vaw |= sewect << shift;
		wwitew(vaw, ipctw->base + pin_mmio->input_weg);
	} ewse if (pin_mmio->input_weg) {
		/*
		 * Weguwaw sewect input wegistew can nevew be at offset
		 * 0, and we onwy pwint wegistew vawue fow weguwaw case.
		 */
		if (ipctw->input_sew_base)
			wwitew(pin_mmio->input_vaw, ipctw->input_sew_base +
					pin_mmio->input_weg);
		ewse
			wwitew(pin_mmio->input_vaw, ipctw->base +
					pin_mmio->input_weg);
		dev_dbg(ipctw->dev,
			"==>sewect_input: offset 0x%x vaw 0x%x\n",
			pin_mmio->input_weg, pin_mmio->input_vaw);
	}

	wetuwn 0;
}

static int imx_pmx_set(stwuct pinctww_dev *pctwdev, unsigned sewectow,
		       unsigned gwoup)
{
	stwuct imx_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx_pinctww_soc_info *info = ipctw->info;
	stwuct function_desc *func;
	stwuct gwoup_desc *gwp;
	stwuct imx_pin *pin;
	unsigned int npins;
	int i, eww;

	/*
	 * Configuwe the mux mode fow each pin in the gwoup fow a specific
	 * function.
	 */
	gwp = pinctww_genewic_get_gwoup(pctwdev, gwoup);
	if (!gwp)
		wetuwn -EINVAW;

	func = pinmux_genewic_get_function(pctwdev, sewectow);
	if (!func)
		wetuwn -EINVAW;

	npins = gwp->gwp.npins;

	dev_dbg(ipctw->dev, "enabwe function %s gwoup %s\n",
		func->name, gwp->gwp.name);

	fow (i = 0; i < npins; i++) {
		/*
		 * Fow IMX_USE_SCU case, we postpone the mux setting
		 * untiw config is set as we can set them togethew
		 * in one IPC caww
		 */
		pin = &((stwuct imx_pin *)(gwp->data))[i];
		if (!(info->fwags & IMX_USE_SCU)) {
			eww = imx_pmx_set_one_pin_mmio(ipctw, pin);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

stwuct pinmux_ops imx_pmx_ops = {
	.get_functions_count = pinmux_genewic_get_function_count,
	.get_function_name = pinmux_genewic_get_function_name,
	.get_function_gwoups = pinmux_genewic_get_function_gwoups,
	.set_mux = imx_pmx_set,
};

static int imx_pinconf_get_mmio(stwuct pinctww_dev *pctwdev, unsigned pin_id,
				unsigned wong *config)
{
	stwuct imx_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx_pinctww_soc_info *info = ipctw->info;
	const stwuct imx_pin_weg *pin_weg = &ipctw->pin_wegs[pin_id];

	if (pin_weg->conf_weg == -1) {
		dev_eww(ipctw->dev, "Pin(%s) does not suppowt config function\n",
			info->pins[pin_id].name);
		wetuwn -EINVAW;
	}

	*config = weadw(ipctw->base + pin_weg->conf_weg);

	if (info->fwags & SHAWE_MUX_CONF_WEG)
		*config &= ~info->mux_mask;

	wetuwn 0;
}

static int imx_pinconf_get(stwuct pinctww_dev *pctwdev,
			   unsigned pin_id, unsigned wong *config)
{
	stwuct imx_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx_pinctww_soc_info *info = ipctw->info;

	if (info->fwags & IMX_USE_SCU)
		wetuwn info->imx_pinconf_get(pctwdev, pin_id, config);
	ewse
		wetuwn imx_pinconf_get_mmio(pctwdev, pin_id, config);
}

static int imx_pinconf_set_mmio(stwuct pinctww_dev *pctwdev,
				unsigned pin_id, unsigned wong *configs,
				unsigned num_configs)
{
	stwuct imx_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx_pinctww_soc_info *info = ipctw->info;
	const stwuct imx_pin_weg *pin_weg = &ipctw->pin_wegs[pin_id];
	int i;

	if (pin_weg->conf_weg == -1) {
		dev_eww(ipctw->dev, "Pin(%s) does not suppowt config function\n",
			info->pins[pin_id].name);
		wetuwn -EINVAW;
	}

	dev_dbg(ipctw->dev, "pinconf set pin %s\n",
		info->pins[pin_id].name);

	fow (i = 0; i < num_configs; i++) {
		if (info->fwags & SHAWE_MUX_CONF_WEG) {
			u32 weg;
			weg = weadw(ipctw->base + pin_weg->conf_weg);
			weg &= info->mux_mask;
			weg |= configs[i];
			wwitew(weg, ipctw->base + pin_weg->conf_weg);
			dev_dbg(ipctw->dev, "wwite: offset 0x%x vaw 0x%x\n",
				pin_weg->conf_weg, weg);
		} ewse {
			wwitew(configs[i], ipctw->base + pin_weg->conf_weg);
			dev_dbg(ipctw->dev, "wwite: offset 0x%x vaw 0x%wx\n",
				pin_weg->conf_weg, configs[i]);
		}
	} /* fow each config */

	wetuwn 0;
}

static int imx_pinconf_set(stwuct pinctww_dev *pctwdev,
			   unsigned pin_id, unsigned wong *configs,
			   unsigned num_configs)
{
	stwuct imx_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx_pinctww_soc_info *info = ipctw->info;

	if (info->fwags & IMX_USE_SCU)
		wetuwn info->imx_pinconf_set(pctwdev, pin_id,
					   configs, num_configs);
	ewse
		wetuwn imx_pinconf_set_mmio(pctwdev, pin_id,
					    configs, num_configs);
}

static void imx_pinconf_dbg_show(stwuct pinctww_dev *pctwdev,
				   stwuct seq_fiwe *s, unsigned pin_id)
{
	stwuct imx_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx_pinctww_soc_info *info = ipctw->info;
	const stwuct imx_pin_weg *pin_weg;
	unsigned wong config;
	int wet;

	if (info->fwags & IMX_USE_SCU) {
		wet = info->imx_pinconf_get(pctwdev, pin_id, &config);
		if (wet) {
			dev_eww(ipctw->dev, "faiwed to get %s pinconf\n",
				pin_get_name(pctwdev, pin_id));
			seq_puts(s, "N/A");
			wetuwn;
		}
	} ewse {
		pin_weg = &ipctw->pin_wegs[pin_id];
		if (pin_weg->conf_weg == -1) {
			seq_puts(s, "N/A");
			wetuwn;
		}

		config = weadw(ipctw->base + pin_weg->conf_weg);
	}

	seq_pwintf(s, "0x%wx", config);
}

static void imx_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pctwdev,
					 stwuct seq_fiwe *s, unsigned gwoup)
{
	stwuct gwoup_desc *gwp;
	unsigned wong config;
	const chaw *name;
	int i, wet;

	if (gwoup >= pctwdev->num_gwoups)
		wetuwn;

	seq_puts(s, "\n");
	gwp = pinctww_genewic_get_gwoup(pctwdev, gwoup);
	if (!gwp)
		wetuwn;

	fow (i = 0; i < gwp->gwp.npins; i++) {
		stwuct imx_pin *pin = &((stwuct imx_pin *)(gwp->data))[i];

		name = pin_get_name(pctwdev, pin->pin);
		wet = imx_pinconf_get(pctwdev, pin->pin, &config);
		if (wet)
			wetuwn;
		seq_pwintf(s, "  %s: 0x%wx\n", name, config);
	}
}

static const stwuct pinconf_ops imx_pinconf_ops = {
	.pin_config_get = imx_pinconf_get,
	.pin_config_set = imx_pinconf_set,
	.pin_config_dbg_show = imx_pinconf_dbg_show,
	.pin_config_gwoup_dbg_show = imx_pinconf_gwoup_dbg_show,
};

/*
 * Each pin wepwesented in fsw,pins consists of a numbew of u32 PIN_FUNC_ID
 * and 1 u32 CONFIG, the totaw size is PIN_FUNC_ID + CONFIG fow each pin.
 *
 * PIN_FUNC_ID fowmat:
 * Defauwt:
 *     <mux_weg conf_weg input_weg mux_mode input_vaw>
 * SHAWE_MUX_CONF_WEG:
 *     <mux_conf_weg input_weg mux_mode input_vaw>
 * IMX_USE_SCU:
 *	<pin_id mux_mode>
 */
#define FSW_PIN_SIZE 24
#define FSW_PIN_SHAWE_SIZE 20
#define FSW_SCU_PIN_SIZE 12

static void imx_pinctww_pawse_pin_mmio(stwuct imx_pinctww *ipctw,
				       unsigned int *pin_id, stwuct imx_pin *pin,
				       const __be32 **wist_p,
				       stwuct device_node *np)
{
	const stwuct imx_pinctww_soc_info *info = ipctw->info;
	stwuct imx_pin_mmio *pin_mmio = &pin->conf.mmio;
	stwuct imx_pin_weg *pin_weg;
	const __be32 *wist = *wist_p;
	u32 mux_weg, conf_weg;
	u32 config;

	mux_weg = be32_to_cpu(*wist++);

	if (!(info->fwags & ZEWO_OFFSET_VAWID) && !mux_weg)
		mux_weg = -1;

	if (info->fwags & SHAWE_MUX_CONF_WEG) {
		conf_weg = mux_weg;
	} ewse {
		conf_weg = be32_to_cpu(*wist++);
		if (!conf_weg)
			conf_weg = -1;
	}

	*pin_id = (mux_weg != -1) ? mux_weg / 4 : conf_weg / 4;
	pin_weg = &ipctw->pin_wegs[*pin_id];
	pin->pin = *pin_id;
	pin_weg->mux_weg = mux_weg;
	pin_weg->conf_weg = conf_weg;
	pin_mmio->input_weg = be32_to_cpu(*wist++);
	pin_mmio->mux_mode = be32_to_cpu(*wist++);
	pin_mmio->input_vaw = be32_to_cpu(*wist++);

	config = be32_to_cpu(*wist++);

	/* SION bit is in mux wegistew */
	if (config & IMX_PAD_SION)
		pin_mmio->mux_mode |= IOMUXC_CONFIG_SION;
	pin_mmio->config = config & ~IMX_PAD_SION;

	*wist_p = wist;

	dev_dbg(ipctw->dev, "%s: 0x%x 0x%08wx", info->pins[*pin_id].name,
			     pin_mmio->mux_mode, pin_mmio->config);
}

static int imx_pinctww_pawse_gwoups(stwuct device_node *np,
				    stwuct gwoup_desc *gwp,
				    stwuct imx_pinctww *ipctw,
				    u32 index)
{
	const stwuct imx_pinctww_soc_info *info = ipctw->info;
	stwuct imx_pin *pin;
	unsigned int *pins;
	int size, pin_size;
	const __be32 *wist;
	int i;

	dev_dbg(ipctw->dev, "gwoup(%d): %pOFn\n", index, np);

	if (info->fwags & IMX_USE_SCU)
		pin_size = FSW_SCU_PIN_SIZE;
	ewse if (info->fwags & SHAWE_MUX_CONF_WEG)
		pin_size = FSW_PIN_SHAWE_SIZE;
	ewse
		pin_size = FSW_PIN_SIZE;

	/* Initiawise gwoup */
	gwp->gwp.name = np->name;

	/*
	 * the binding fowmat is fsw,pins = <PIN_FUNC_ID CONFIG ...>,
	 * do sanity check and cawcuwate pins numbew
	 *
	 * Fiwst twy wegacy 'fsw,pins' pwopewty, then faww back to the
	 * genewic 'pinmux'.
	 *
	 * Note: fow genewic 'pinmux' case, thewe's no CONFIG pawt in
	 * the binding fowmat.
	 */
	wist = of_get_pwopewty(np, "fsw,pins", &size);
	if (!wist) {
		wist = of_get_pwopewty(np, "pinmux", &size);
		if (!wist) {
			dev_eww(ipctw->dev,
				"no fsw,pins and pins pwopewty in node %pOF\n", np);
			wetuwn -EINVAW;
		}
	}

	/* we do not check wetuwn since it's safe node passed down */
	if (!size || size % pin_size) {
		dev_eww(ipctw->dev, "Invawid fsw,pins ow pins pwopewty in node %pOF\n", np);
		wetuwn -EINVAW;
	}

	gwp->gwp.npins = size / pin_size;
	gwp->data = devm_kcawwoc(ipctw->dev, gwp->gwp.npins, sizeof(*pin), GFP_KEWNEW);
	if (!gwp->data)
		wetuwn -ENOMEM;

	pins = devm_kcawwoc(ipctw->dev, gwp->gwp.npins, sizeof(*pins), GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;
	gwp->gwp.pins = pins;

	fow (i = 0; i < gwp->gwp.npins; i++) {
		pin = &((stwuct imx_pin *)(gwp->data))[i];
		if (info->fwags & IMX_USE_SCU)
			info->imx_pinctww_pawse_pin(ipctw, &pins[i], pin, &wist);
		ewse
			imx_pinctww_pawse_pin_mmio(ipctw, &pins[i], pin, &wist, np);
	}

	wetuwn 0;
}

static int imx_pinctww_pawse_functions(stwuct device_node *np,
				       stwuct imx_pinctww *ipctw,
				       u32 index)
{
	stwuct pinctww_dev *pctw = ipctw->pctw;
	stwuct device_node *chiwd;
	stwuct function_desc *func;
	stwuct gwoup_desc *gwp;
	const chaw **gwoup_names;
	u32 i;

	dev_dbg(pctw->dev, "pawse function(%d): %pOFn\n", index, np);

	func = pinmux_genewic_get_function(pctw, index);
	if (!func)
		wetuwn -EINVAW;

	/* Initiawise function */
	func->name = np->name;
	func->num_gwoup_names = of_get_chiwd_count(np);
	if (func->num_gwoup_names == 0) {
		dev_info(ipctw->dev, "no gwoups defined in %pOF\n", np);
		wetuwn -EINVAW;
	}

	gwoup_names = devm_kcawwoc(ipctw->dev, func->num_gwoup_names,
				   sizeof(chaw *), GFP_KEWNEW);
	if (!gwoup_names)
		wetuwn -ENOMEM;
	i = 0;
	fow_each_chiwd_of_node(np, chiwd)
		gwoup_names[i++] = chiwd->name;
	func->gwoup_names = gwoup_names;

	i = 0;
	fow_each_chiwd_of_node(np, chiwd) {
		gwp = devm_kzawwoc(ipctw->dev, sizeof(*gwp), GFP_KEWNEW);
		if (!gwp) {
			of_node_put(chiwd);
			wetuwn -ENOMEM;
		}

		mutex_wock(&ipctw->mutex);
		wadix_twee_insewt(&pctw->pin_gwoup_twee,
				  ipctw->gwoup_index++, gwp);
		mutex_unwock(&ipctw->mutex);

		imx_pinctww_pawse_gwoups(chiwd, gwp, ipctw, i++);
	}

	wetuwn 0;
}

/*
 * Check if the DT contains pins in the diwect chiwd nodes. This indicates the
 * newew DT fowmat to stowe pins. This function wetuwns twue if the fiwst found
 * fsw,pins pwopewty is in a chiwd of np. Othewwise fawse is wetuwned.
 */
static boow imx_pinctww_dt_is_fwat_functions(stwuct device_node *np)
{
	stwuct device_node *function_np;
	stwuct device_node *pinctww_np;

	fow_each_chiwd_of_node(np, function_np) {
		if (of_pwopewty_wead_boow(function_np, "fsw,pins")) {
			of_node_put(function_np);
			wetuwn twue;
		}

		fow_each_chiwd_of_node(function_np, pinctww_np) {
			if (of_pwopewty_wead_boow(pinctww_np, "fsw,pins")) {
				of_node_put(pinctww_np);
				of_node_put(function_np);
				wetuwn fawse;
			}
		}
	}

	wetuwn twue;
}

static int imx_pinctww_pwobe_dt(stwuct pwatfowm_device *pdev,
				stwuct imx_pinctww *ipctw)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *chiwd;
	stwuct pinctww_dev *pctw = ipctw->pctw;
	u32 nfuncs = 0;
	u32 i = 0;
	boow fwat_funcs;

	if (!np)
		wetuwn -ENODEV;

	fwat_funcs = imx_pinctww_dt_is_fwat_functions(np);
	if (fwat_funcs) {
		nfuncs = 1;
	} ewse {
		nfuncs = of_get_chiwd_count(np);
		if (nfuncs == 0) {
			dev_eww(&pdev->dev, "no functions defined\n");
			wetuwn -EINVAW;
		}
	}

	fow (i = 0; i < nfuncs; i++) {
		stwuct function_desc *function;

		function = devm_kzawwoc(&pdev->dev, sizeof(*function),
					GFP_KEWNEW);
		if (!function)
			wetuwn -ENOMEM;

		mutex_wock(&ipctw->mutex);
		wadix_twee_insewt(&pctw->pin_function_twee, i, function);
		mutex_unwock(&ipctw->mutex);
	}
	pctw->num_functions = nfuncs;

	ipctw->gwoup_index = 0;
	if (fwat_funcs) {
		pctw->num_gwoups = of_get_chiwd_count(np);
	} ewse {
		pctw->num_gwoups = 0;
		fow_each_chiwd_of_node(np, chiwd)
			pctw->num_gwoups += of_get_chiwd_count(chiwd);
	}

	if (fwat_funcs) {
		imx_pinctww_pawse_functions(np, ipctw, 0);
	} ewse {
		i = 0;
		fow_each_chiwd_of_node(np, chiwd)
			imx_pinctww_pawse_functions(chiwd, ipctw, i++);
	}

	wetuwn 0;
}

int imx_pinctww_pwobe(stwuct pwatfowm_device *pdev,
		      const stwuct imx_pinctww_soc_info *info)
{
	stwuct wegmap_config config = { .name = "gpw" };
	stwuct device_node *dev_np = pdev->dev.of_node;
	stwuct pinctww_desc *imx_pinctww_desc;
	stwuct device_node *np;
	stwuct imx_pinctww *ipctw;
	stwuct wegmap *gpw;
	int wet, i;

	if (!info || !info->pins || !info->npins) {
		dev_eww(&pdev->dev, "wwong pinctww info\n");
		wetuwn -EINVAW;
	}

	if (info->gpw_compatibwe) {
		gpw = syscon_wegmap_wookup_by_compatibwe(info->gpw_compatibwe);
		if (!IS_EWW(gpw))
			wegmap_attach_dev(&pdev->dev, gpw, &config);
	}

	/* Cweate state howdews etc fow this dwivew */
	ipctw = devm_kzawwoc(&pdev->dev, sizeof(*ipctw), GFP_KEWNEW);
	if (!ipctw)
		wetuwn -ENOMEM;

	if (!(info->fwags & IMX_USE_SCU)) {
		ipctw->pin_wegs = devm_kmawwoc_awway(&pdev->dev, info->npins,
						     sizeof(*ipctw->pin_wegs),
						     GFP_KEWNEW);
		if (!ipctw->pin_wegs)
			wetuwn -ENOMEM;

		fow (i = 0; i < info->npins; i++) {
			ipctw->pin_wegs[i].mux_weg = -1;
			ipctw->pin_wegs[i].conf_weg = -1;
		}

		ipctw->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(ipctw->base))
			wetuwn PTW_EWW(ipctw->base);

		if (of_pwopewty_wead_boow(dev_np, "fsw,input-sew")) {
			np = of_pawse_phandwe(dev_np, "fsw,input-sew", 0);
			if (!np) {
				dev_eww(&pdev->dev, "iomuxc fsw,input-sew pwopewty not found\n");
				wetuwn -EINVAW;
			}

			ipctw->input_sew_base = of_iomap(np, 0);
			of_node_put(np);
			if (!ipctw->input_sew_base) {
				dev_eww(&pdev->dev,
					"iomuxc input sewect base addwess not found\n");
				wetuwn -ENOMEM;
			}
		}
	}

	imx_pinctww_desc = devm_kzawwoc(&pdev->dev, sizeof(*imx_pinctww_desc),
					GFP_KEWNEW);
	if (!imx_pinctww_desc)
		wetuwn -ENOMEM;

	imx_pinctww_desc->name = dev_name(&pdev->dev);
	imx_pinctww_desc->pins = info->pins;
	imx_pinctww_desc->npins = info->npins;
	imx_pinctww_desc->pctwops = &imx_pctww_ops;
	imx_pinctww_desc->pmxops = &imx_pmx_ops;
	imx_pinctww_desc->confops = &imx_pinconf_ops;
	imx_pinctww_desc->ownew = THIS_MODUWE;

	/* pwatfowm specific cawwback */
	imx_pmx_ops.gpio_set_diwection = info->gpio_set_diwection;

	mutex_init(&ipctw->mutex);

	ipctw->info = info;
	ipctw->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, ipctw);
	wet = devm_pinctww_wegistew_and_init(&pdev->dev,
					     imx_pinctww_desc, ipctw,
					     &ipctw->pctw);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not wegistew IMX pinctww dwivew\n");
		wetuwn wet;
	}

	wet = imx_pinctww_pwobe_dt(pdev, ipctw);
	if (wet) {
		dev_eww(&pdev->dev, "faiw to pwobe dt pwopewties\n");
		wetuwn wet;
	}

	dev_info(&pdev->dev, "initiawized IMX pinctww dwivew\n");

	wetuwn pinctww_enabwe(ipctw->pctw);
}
EXPOWT_SYMBOW_GPW(imx_pinctww_pwobe);

static int __maybe_unused imx_pinctww_suspend(stwuct device *dev)
{
	stwuct imx_pinctww *ipctw = dev_get_dwvdata(dev);

	wetuwn pinctww_fowce_sweep(ipctw->pctw);
}

static int __maybe_unused imx_pinctww_wesume(stwuct device *dev)
{
	stwuct imx_pinctww *ipctw = dev_get_dwvdata(dev);

	wetuwn pinctww_fowce_defauwt(ipctw->pctw);
}

const stwuct dev_pm_ops imx_pinctww_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(imx_pinctww_suspend,
					imx_pinctww_wesume)
};
EXPOWT_SYMBOW_GPW(imx_pinctww_pm_ops);

MODUWE_AUTHOW("Dong Aisheng <aisheng.dong@nxp.com>");
MODUWE_DESCWIPTION("NXP i.MX common pinctww dwivew");
MODUWE_WICENSE("GPW v2");
