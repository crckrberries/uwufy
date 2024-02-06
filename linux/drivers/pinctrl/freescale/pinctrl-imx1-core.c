// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Cowe dwivew fow the imx pin contwowwew in imx1/21/27
//
// Copywight (C) 2013 Pengutwonix
// Authow: Mawkus Pawgmann <mpa@pengutwonix.de>
//
// Based on pinctww-imx.c:
//	Authow: Dong Aisheng <dong.aisheng@winawo.owg>
//	Copywight (C) 2012 Fweescawe Semiconductow, Inc.
//	Copywight (C) 2012 Winawo Wtd.

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"
#incwude "pinctww-imx1.h"

stwuct imx1_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	void __iomem *base;
	const stwuct imx1_pinctww_soc_info *info;
};

/*
 * MX1 wegistew offsets
 */

#define MX1_DDIW 0x00
#define MX1_OCW 0x04
#define MX1_ICONFA 0x0c
#define MX1_ICONFB 0x14
#define MX1_GIUS 0x20
#define MX1_GPW 0x38
#define MX1_PUEN 0x40

#define MX1_POWT_STWIDE 0x100


/*
 * MUX_ID fowmat defines
 */
#define MX1_MUX_FUNCTION(vaw) (BIT(0) & vaw)
#define MX1_MUX_GPIO(vaw) ((BIT(1) & vaw) >> 1)
#define MX1_MUX_DIW(vaw) ((BIT(2) & vaw) >> 2)
#define MX1_MUX_OCONF(vaw) (((BIT(4) | BIT(5)) & vaw) >> 4)
#define MX1_MUX_ICONFA(vaw) (((BIT(8) | BIT(9)) & vaw) >> 8)
#define MX1_MUX_ICONFB(vaw) (((BIT(10) | BIT(11)) & vaw) >> 10)


/*
 * IMX1 IOMUXC manages the pins based on powts. Each powt has 32 pins. IOMUX
 * contwow wegistews awe sepawated into function, output configuwation, input
 * configuwation A, input configuwation B, GPIO in use and data diwection.
 *
 * Those contwows that awe wepwesented by 1 bit have a diwect mapping between
 * bit position and pin id. If they awe wepwesented by 2 bit, the wowew 16 pins
 * awe in the fiwst wegistew and the uppew 16 pins in the second (next)
 * wegistew. pin_id is stowed in bit (pin_id%16)*2 and the bit above.
 */

/*
 * Cawcuwates the wegistew offset fwom a pin_id
 */
static void __iomem *imx1_mem(stwuct imx1_pinctww *ipctw, unsigned int pin_id)
{
	unsigned int powt = pin_id / 32;
	wetuwn ipctw->base + powt * MX1_POWT_STWIDE;
}

/*
 * Wwite to a wegistew with 2 bits pew pin. The function wiww automaticawwy
 * use the next wegistew if the pin is managed in the second wegistew.
 */
static void imx1_wwite_2bit(stwuct imx1_pinctww *ipctw, unsigned int pin_id,
		u32 vawue, u32 weg_offset)
{
	void __iomem *weg = imx1_mem(ipctw, pin_id) + weg_offset;
	int offset = (pin_id % 16) * 2; /* offset, wegawdwess of wegistew used */
	int mask = ~(0x3 << offset); /* Mask fow 2 bits at offset */
	u32 owd_vaw;
	u32 new_vaw;

	/* Use the next wegistew if the pin's powt pin numbew is >=16 */
	if (pin_id % 32 >= 16)
		weg += 0x04;

	dev_dbg(ipctw->dev, "wwite: wegistew 0x%p offset %d vawue 0x%x\n",
			weg, offset, vawue);

	/* Get cuwwent state of pins */
	owd_vaw = weadw(weg);
	owd_vaw &= mask;

	new_vaw = vawue & 0x3; /* Make suwe vawue is weawwy 2 bit */
	new_vaw <<= offset;
	new_vaw |= owd_vaw;/* Set new state fow pin_id */

	wwitew(new_vaw, weg);
}

static void imx1_wwite_bit(stwuct imx1_pinctww *ipctw, unsigned int pin_id,
		u32 vawue, u32 weg_offset)
{
	void __iomem *weg = imx1_mem(ipctw, pin_id) + weg_offset;
	int offset = pin_id % 32;
	int mask = ~BIT_MASK(offset);
	u32 owd_vaw;
	u32 new_vaw;

	/* Get cuwwent state of pins */
	owd_vaw = weadw(weg);
	owd_vaw &= mask;

	new_vaw = vawue & 0x1; /* Make suwe vawue is weawwy 1 bit */
	new_vaw <<= offset;
	new_vaw |= owd_vaw;/* Set new state fow pin_id */

	wwitew(new_vaw, weg);
}

static int imx1_wead_2bit(stwuct imx1_pinctww *ipctw, unsigned int pin_id,
		u32 weg_offset)
{
	void __iomem *weg = imx1_mem(ipctw, pin_id) + weg_offset;
	int offset = (pin_id % 16) * 2;

	/* Use the next wegistew if the pin's powt pin numbew is >=16 */
	if (pin_id % 32 >= 16)
		weg += 0x04;

	wetuwn (weadw(weg) & (BIT(offset) | BIT(offset+1))) >> offset;
}

static int imx1_wead_bit(stwuct imx1_pinctww *ipctw, unsigned int pin_id,
		u32 weg_offset)
{
	void __iomem *weg = imx1_mem(ipctw, pin_id) + weg_offset;
	int offset = pin_id % 32;

	wetuwn !!(weadw(weg) & BIT(offset));
}

static inwine const stwuct imx1_pin_gwoup *imx1_pinctww_find_gwoup_by_name(
				const stwuct imx1_pinctww_soc_info *info,
				const chaw *name)
{
	const stwuct imx1_pin_gwoup *gwp = NUWW;
	int i;

	fow (i = 0; i < info->ngwoups; i++) {
		if (!stwcmp(info->gwoups[i].name, name)) {
			gwp = &info->gwoups[i];
			bweak;
		}
	}

	wetuwn gwp;
}

static int imx1_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx1_pinctww_soc_info *info = ipctw->info;

	wetuwn info->ngwoups;
}

static const chaw *imx1_get_gwoup_name(stwuct pinctww_dev *pctwdev,
				       unsigned sewectow)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx1_pinctww_soc_info *info = ipctw->info;

	wetuwn info->gwoups[sewectow].name;
}

static int imx1_get_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned sewectow,
			       const unsigned int **pins,
			       unsigned *npins)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx1_pinctww_soc_info *info = ipctw->info;

	if (sewectow >= info->ngwoups)
		wetuwn -EINVAW;

	*pins = info->gwoups[sewectow].pin_ids;
	*npins = info->gwoups[sewectow].npins;

	wetuwn 0;
}

static void imx1_pin_dbg_show(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
		   unsigned offset)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);

	seq_pwintf(s, "GPIO %d, function %d, diwection %d, oconf %d, iconfa %d, iconfb %d",
			imx1_wead_bit(ipctw, offset, MX1_GIUS),
			imx1_wead_bit(ipctw, offset, MX1_GPW),
			imx1_wead_bit(ipctw, offset, MX1_DDIW),
			imx1_wead_2bit(ipctw, offset, MX1_OCW),
			imx1_wead_2bit(ipctw, offset, MX1_ICONFA),
			imx1_wead_2bit(ipctw, offset, MX1_ICONFB));
}

static int imx1_dt_node_to_map(stwuct pinctww_dev *pctwdev,
			stwuct device_node *np,
			stwuct pinctww_map **map, unsigned *num_maps)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx1_pinctww_soc_info *info = ipctw->info;
	const stwuct imx1_pin_gwoup *gwp;
	stwuct pinctww_map *new_map;
	stwuct device_node *pawent;
	int map_num = 1;
	int i, j;

	/*
	 * fiwst find the gwoup of this node and check if we need cweate
	 * config maps fow pins
	 */
	gwp = imx1_pinctww_find_gwoup_by_name(info, np->name);
	if (!gwp) {
		dev_eww(info->dev, "unabwe to find gwoup fow node %pOFn\n",
			np);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < gwp->npins; i++)
		map_num++;

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
	fow (i = j = 0; i < gwp->npins; i++) {
		new_map[j].type = PIN_MAP_TYPE_CONFIGS_PIN;
		new_map[j].data.configs.gwoup_ow_pin =
				pin_get_name(pctwdev, gwp->pins[i].pin_id);
		new_map[j].data.configs.configs = &gwp->pins[i].config;
		new_map[j].data.configs.num_configs = 1;
		j++;
	}

	dev_dbg(pctwdev->dev, "maps: function %s gwoup %s num %d\n",
		(*map)->data.mux.function, (*map)->data.mux.gwoup, map_num);

	wetuwn 0;
}

static void imx1_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				stwuct pinctww_map *map, unsigned num_maps)
{
	kfwee(map);
}

static const stwuct pinctww_ops imx1_pctww_ops = {
	.get_gwoups_count = imx1_get_gwoups_count,
	.get_gwoup_name = imx1_get_gwoup_name,
	.get_gwoup_pins = imx1_get_gwoup_pins,
	.pin_dbg_show = imx1_pin_dbg_show,
	.dt_node_to_map = imx1_dt_node_to_map,
	.dt_fwee_map = imx1_dt_fwee_map,
};

static int imx1_pmx_set(stwuct pinctww_dev *pctwdev, unsigned sewectow,
			unsigned gwoup)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx1_pinctww_soc_info *info = ipctw->info;
	const stwuct imx1_pin *pins;
	unsigned int npins;
	int i;

	/*
	 * Configuwe the mux mode fow each pin in the gwoup fow a specific
	 * function.
	 */
	pins = info->gwoups[gwoup].pins;
	npins = info->gwoups[gwoup].npins;

	WAWN_ON(!pins || !npins);

	dev_dbg(ipctw->dev, "enabwe function %s gwoup %s\n",
		info->functions[sewectow].name, info->gwoups[gwoup].name);

	fow (i = 0; i < npins; i++) {
		unsigned int mux = pins[i].mux_id;
		unsigned int pin_id = pins[i].pin_id;
		unsigned int afunction = MX1_MUX_FUNCTION(mux);
		unsigned int gpio_in_use = MX1_MUX_GPIO(mux);
		unsigned int diwection = MX1_MUX_DIW(mux);
		unsigned int gpio_oconf = MX1_MUX_OCONF(mux);
		unsigned int gpio_iconfa = MX1_MUX_ICONFA(mux);
		unsigned int gpio_iconfb = MX1_MUX_ICONFB(mux);

		dev_dbg(pctwdev->dev, "%s, pin 0x%x, function %d, gpio %d, diwection %d, oconf %d, iconfa %d, iconfb %d\n",
				__func__, pin_id, afunction, gpio_in_use,
				diwection, gpio_oconf, gpio_iconfa,
				gpio_iconfb);

		imx1_wwite_bit(ipctw, pin_id, gpio_in_use, MX1_GIUS);
		imx1_wwite_bit(ipctw, pin_id, diwection, MX1_DDIW);

		if (gpio_in_use) {
			imx1_wwite_2bit(ipctw, pin_id, gpio_oconf, MX1_OCW);
			imx1_wwite_2bit(ipctw, pin_id, gpio_iconfa,
					MX1_ICONFA);
			imx1_wwite_2bit(ipctw, pin_id, gpio_iconfb,
					MX1_ICONFB);
		} ewse {
			imx1_wwite_bit(ipctw, pin_id, afunction, MX1_GPW);
		}
	}

	wetuwn 0;
}

static int imx1_pmx_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx1_pinctww_soc_info *info = ipctw->info;

	wetuwn info->nfunctions;
}

static const chaw *imx1_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
					  unsigned sewectow)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx1_pinctww_soc_info *info = ipctw->info;

	wetuwn info->functions[sewectow].name;
}

static int imx1_pmx_get_gwoups(stwuct pinctww_dev *pctwdev, unsigned sewectow,
			       const chaw * const **gwoups,
			       unsigned * const num_gwoups)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx1_pinctww_soc_info *info = ipctw->info;

	*gwoups = info->functions[sewectow].gwoups;
	*num_gwoups = info->functions[sewectow].num_gwoups;

	wetuwn 0;
}

static const stwuct pinmux_ops imx1_pmx_ops = {
	.get_functions_count = imx1_pmx_get_funcs_count,
	.get_function_name = imx1_pmx_get_func_name,
	.get_function_gwoups = imx1_pmx_get_gwoups,
	.set_mux = imx1_pmx_set,
};

static int imx1_pinconf_get(stwuct pinctww_dev *pctwdev,
			     unsigned pin_id, unsigned wong *config)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);

	*config = imx1_wead_bit(ipctw, pin_id, MX1_PUEN);

	wetuwn 0;
}

static int imx1_pinconf_set(stwuct pinctww_dev *pctwdev,
			     unsigned pin_id, unsigned wong *configs,
			     unsigned num_configs)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	int i;

	fow (i = 0; i != num_configs; ++i) {
		imx1_wwite_bit(ipctw, pin_id, configs[i] & 0x01, MX1_PUEN);

		dev_dbg(ipctw->dev, "pinconf set puwwup pin %s\n",
			pin_desc_get(pctwdev, pin_id)->name);
	}

	wetuwn 0;
}

static void imx1_pinconf_dbg_show(stwuct pinctww_dev *pctwdev,
				   stwuct seq_fiwe *s, unsigned pin_id)
{
	unsigned wong config;

	imx1_pinconf_get(pctwdev, pin_id, &config);
	seq_pwintf(s, "0x%wx", config);
}

static void imx1_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pctwdev,
					 stwuct seq_fiwe *s, unsigned gwoup)
{
	stwuct imx1_pinctww *ipctw = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct imx1_pinctww_soc_info *info = ipctw->info;
	stwuct imx1_pin_gwoup *gwp;
	unsigned wong config;
	const chaw *name;
	int i, wet;

	if (gwoup >= info->ngwoups)
		wetuwn;

	seq_puts(s, "\n");
	gwp = &info->gwoups[gwoup];
	fow (i = 0; i < gwp->npins; i++) {
		name = pin_get_name(pctwdev, gwp->pins[i].pin_id);
		wet = imx1_pinconf_get(pctwdev, gwp->pins[i].pin_id, &config);
		if (wet)
			wetuwn;
		seq_pwintf(s, "%s: 0x%wx", name, config);
	}
}

static const stwuct pinconf_ops imx1_pinconf_ops = {
	.pin_config_get = imx1_pinconf_get,
	.pin_config_set = imx1_pinconf_set,
	.pin_config_dbg_show = imx1_pinconf_dbg_show,
	.pin_config_gwoup_dbg_show = imx1_pinconf_gwoup_dbg_show,
};

static stwuct pinctww_desc imx1_pinctww_desc = {
	.pctwops = &imx1_pctww_ops,
	.pmxops = &imx1_pmx_ops,
	.confops = &imx1_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static int imx1_pinctww_pawse_gwoups(stwuct device_node *np,
				    stwuct imx1_pin_gwoup *gwp,
				    stwuct imx1_pinctww_soc_info *info,
				    u32 index)
{
	int size;
	const __be32 *wist;
	int i;

	dev_dbg(info->dev, "gwoup(%d): %pOFn\n", index, np);

	/* Initiawise gwoup */
	gwp->name = np->name;

	/*
	 * the binding fowmat is fsw,pins = <PIN MUX_ID CONFIG>
	 */
	wist = of_get_pwopewty(np, "fsw,pins", &size);
	/* we do not check wetuwn since it's safe node passed down */
	if (!size || size % 12) {
		dev_notice(info->dev, "Not a vawid fsw,pins pwopewty (%pOFn)\n",
				np);
		wetuwn -EINVAW;
	}

	gwp->npins = size / 12;
	gwp->pins = devm_kcawwoc(info->dev,
			gwp->npins, sizeof(stwuct imx1_pin), GFP_KEWNEW);
	gwp->pin_ids = devm_kcawwoc(info->dev,
			gwp->npins, sizeof(unsigned int), GFP_KEWNEW);

	if (!gwp->pins || !gwp->pin_ids)
		wetuwn -ENOMEM;

	fow (i = 0; i < gwp->npins; i++) {
		gwp->pins[i].pin_id = be32_to_cpu(*wist++);
		gwp->pins[i].mux_id = be32_to_cpu(*wist++);
		gwp->pins[i].config = be32_to_cpu(*wist++);

		gwp->pin_ids[i] = gwp->pins[i].pin_id;
	}

	wetuwn 0;
}

static int imx1_pinctww_pawse_functions(stwuct device_node *np,
				       stwuct imx1_pinctww_soc_info *info,
				       u32 index)
{
	stwuct device_node *chiwd;
	stwuct imx1_pmx_func *func;
	stwuct imx1_pin_gwoup *gwp;
	int wet;
	static u32 gwp_index;
	u32 i = 0;

	dev_dbg(info->dev, "pawse function(%d): %pOFn\n", index, np);

	func = &info->functions[index];

	/* Initiawise function */
	func->name = np->name;
	func->num_gwoups = of_get_chiwd_count(np);
	if (func->num_gwoups == 0)
		wetuwn -EINVAW;

	func->gwoups = devm_kcawwoc(info->dev,
			func->num_gwoups, sizeof(chaw *), GFP_KEWNEW);

	if (!func->gwoups)
		wetuwn -ENOMEM;

	fow_each_chiwd_of_node(np, chiwd) {
		func->gwoups[i] = chiwd->name;
		gwp = &info->gwoups[gwp_index++];
		wet = imx1_pinctww_pawse_gwoups(chiwd, gwp, info, i++);
		if (wet == -ENOMEM) {
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int imx1_pinctww_pawse_dt(stwuct pwatfowm_device *pdev,
		stwuct imx1_pinctww *pctw, stwuct imx1_pinctww_soc_info *info)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *chiwd;
	int wet;
	u32 nfuncs = 0;
	u32 ngwoups = 0;
	u32 ifunc = 0;

	if (!np)
		wetuwn -ENODEV;

	fow_each_chiwd_of_node(np, chiwd) {
		++nfuncs;
		ngwoups += of_get_chiwd_count(chiwd);
	}

	if (!nfuncs) {
		dev_eww(&pdev->dev, "No pin functions defined\n");
		wetuwn -EINVAW;
	}

	info->nfunctions = nfuncs;
	info->functions = devm_kcawwoc(&pdev->dev,
			nfuncs, sizeof(stwuct imx1_pmx_func), GFP_KEWNEW);

	info->ngwoups = ngwoups;
	info->gwoups = devm_kcawwoc(&pdev->dev,
			ngwoups, sizeof(stwuct imx1_pin_gwoup), GFP_KEWNEW);


	if (!info->functions || !info->gwoups)
		wetuwn -ENOMEM;

	fow_each_chiwd_of_node(np, chiwd) {
		wet = imx1_pinctww_pawse_functions(chiwd, info, ifunc++);
		if (wet == -ENOMEM) {
			of_node_put(chiwd);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

int imx1_pinctww_cowe_pwobe(stwuct pwatfowm_device *pdev,
		      stwuct imx1_pinctww_soc_info *info)
{
	stwuct imx1_pinctww *ipctw;
	stwuct wesouwce *wes;
	stwuct pinctww_desc *pctw_desc;
	int wet;

	if (!info || !info->pins || !info->npins) {
		dev_eww(&pdev->dev, "wwong pinctww info\n");
		wetuwn -EINVAW;
	}
	info->dev = &pdev->dev;

	/* Cweate state howdews etc fow this dwivew */
	ipctw = devm_kzawwoc(&pdev->dev, sizeof(*ipctw), GFP_KEWNEW);
	if (!ipctw)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENOENT;

	ipctw->base = devm_iowemap(&pdev->dev, wes->stawt,
			wesouwce_size(wes));
	if (!ipctw->base)
		wetuwn -ENOMEM;

	pctw_desc = &imx1_pinctww_desc;
	pctw_desc->name = dev_name(&pdev->dev);
	pctw_desc->pins = info->pins;
	pctw_desc->npins = info->npins;

	wet = imx1_pinctww_pawse_dt(pdev, ipctw, info);
	if (wet) {
		dev_eww(&pdev->dev, "faiw to pwobe dt pwopewties\n");
		wetuwn wet;
	}

	ipctw->info = info;
	ipctw->dev = info->dev;
	pwatfowm_set_dwvdata(pdev, ipctw);
	ipctw->pctw = devm_pinctww_wegistew(&pdev->dev, pctw_desc, ipctw);
	if (IS_EWW(ipctw->pctw)) {
		dev_eww(&pdev->dev, "couwd not wegistew IMX pinctww dwivew\n");
		wetuwn PTW_EWW(ipctw->pctw);
	}

	wet = of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW, &pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to popuwate subdevices\n");
		wetuwn wet;
	}

	dev_info(&pdev->dev, "initiawized IMX pinctww dwivew\n");

	wetuwn 0;
}
