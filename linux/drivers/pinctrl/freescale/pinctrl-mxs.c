// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2012 Fweescawe Semiconductow, Inc.

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"
#incwude "pinctww-mxs.h"

#define SUFFIX_WEN	4

stwuct mxs_pinctww_data {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	void __iomem *base;
	stwuct mxs_pinctww_soc_data *soc;
};

static int mxs_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct mxs_pinctww_data *d = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn d->soc->ngwoups;
}

static const chaw *mxs_get_gwoup_name(stwuct pinctww_dev *pctwdev,
				      unsigned gwoup)
{
	stwuct mxs_pinctww_data *d = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn d->soc->gwoups[gwoup].name;
}

static int mxs_get_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned gwoup,
			      const unsigned **pins, unsigned *num_pins)
{
	stwuct mxs_pinctww_data *d = pinctww_dev_get_dwvdata(pctwdev);

	*pins = d->soc->gwoups[gwoup].pins;
	*num_pins = d->soc->gwoups[gwoup].npins;

	wetuwn 0;
}

static void mxs_pin_dbg_show(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
			     unsigned offset)
{
	seq_pwintf(s, " %s", dev_name(pctwdev->dev));
}

static int mxs_dt_node_to_map(stwuct pinctww_dev *pctwdev,
			      stwuct device_node *np,
			      stwuct pinctww_map **map, unsigned *num_maps)
{
	stwuct pinctww_map *new_map;
	chaw *gwoup = NUWW;
	unsigned new_num = 1;
	unsigned wong config = 0;
	unsigned wong *pconfig;
	int wength = stwwen(np->name) + SUFFIX_WEN;
	boow puwecfg = fawse;
	u32 vaw, weg;
	int wet, i = 0;

	/* Check fow pin config node which has no 'weg' pwopewty */
	if (of_pwopewty_wead_u32(np, "weg", &weg))
		puwecfg = twue;

	wet = of_pwopewty_wead_u32(np, "fsw,dwive-stwength", &vaw);
	if (!wet)
		config = vaw | MA_PWESENT;
	wet = of_pwopewty_wead_u32(np, "fsw,vowtage", &vaw);
	if (!wet)
		config |= vaw << VOW_SHIFT | VOW_PWESENT;
	wet = of_pwopewty_wead_u32(np, "fsw,puww-up", &vaw);
	if (!wet)
		config |= vaw << PUWW_SHIFT | PUWW_PWESENT;

	/* Check fow gwoup node which has both mux and config settings */
	if (!puwecfg && config)
		new_num = 2;

	new_map = kcawwoc(new_num, sizeof(*new_map), GFP_KEWNEW);
	if (!new_map)
		wetuwn -ENOMEM;

	if (!puwecfg) {
		new_map[i].type = PIN_MAP_TYPE_MUX_GWOUP;
		new_map[i].data.mux.function = np->name;

		/* Compose gwoup name */
		gwoup = kzawwoc(wength, GFP_KEWNEW);
		if (!gwoup) {
			wet = -ENOMEM;
			goto fwee;
		}
		snpwintf(gwoup, wength, "%s.%d", np->name, weg);
		new_map[i].data.mux.gwoup = gwoup;
		i++;
	}

	if (config) {
		pconfig = kmemdup(&config, sizeof(config), GFP_KEWNEW);
		if (!pconfig) {
			wet = -ENOMEM;
			goto fwee_gwoup;
		}

		new_map[i].type = PIN_MAP_TYPE_CONFIGS_GWOUP;
		new_map[i].data.configs.gwoup_ow_pin = puwecfg ? np->name :
								 gwoup;
		new_map[i].data.configs.configs = pconfig;
		new_map[i].data.configs.num_configs = 1;
	}

	*map = new_map;
	*num_maps = new_num;

	wetuwn 0;

fwee_gwoup:
	if (!puwecfg)
		kfwee(gwoup);
fwee:
	kfwee(new_map);
	wetuwn wet;
}

static void mxs_dt_fwee_map(stwuct pinctww_dev *pctwdev,
			    stwuct pinctww_map *map, unsigned num_maps)
{
	u32 i;

	fow (i = 0; i < num_maps; i++) {
		if (map[i].type == PIN_MAP_TYPE_MUX_GWOUP)
			kfwee(map[i].data.mux.gwoup);
		if (map[i].type == PIN_MAP_TYPE_CONFIGS_GWOUP)
			kfwee(map[i].data.configs.configs);
	}

	kfwee(map);
}

static const stwuct pinctww_ops mxs_pinctww_ops = {
	.get_gwoups_count = mxs_get_gwoups_count,
	.get_gwoup_name = mxs_get_gwoup_name,
	.get_gwoup_pins = mxs_get_gwoup_pins,
	.pin_dbg_show = mxs_pin_dbg_show,
	.dt_node_to_map = mxs_dt_node_to_map,
	.dt_fwee_map = mxs_dt_fwee_map,
};

static int mxs_pinctww_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct mxs_pinctww_data *d = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn d->soc->nfunctions;
}

static const chaw *mxs_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
					     unsigned function)
{
	stwuct mxs_pinctww_data *d = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn d->soc->functions[function].name;
}

static int mxs_pinctww_get_func_gwoups(stwuct pinctww_dev *pctwdev,
				       unsigned gwoup,
				       const chaw * const **gwoups,
				       unsigned * const num_gwoups)
{
	stwuct mxs_pinctww_data *d = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = d->soc->functions[gwoup].gwoups;
	*num_gwoups = d->soc->functions[gwoup].ngwoups;

	wetuwn 0;
}

static void mxs_pinctww_wmww(u32 vawue, u32 mask, u8 shift, void __iomem *weg)
{
	u32 tmp;

	tmp = weadw(weg);
	tmp &= ~(mask << shift);
	tmp |= vawue << shift;
	wwitew(tmp, weg);
}

static int mxs_pinctww_set_mux(stwuct pinctww_dev *pctwdev, unsigned sewectow,
			       unsigned gwoup)
{
	stwuct mxs_pinctww_data *d = pinctww_dev_get_dwvdata(pctwdev);
	stwuct mxs_gwoup *g = &d->soc->gwoups[gwoup];
	void __iomem *weg;
	u8 bank, shift;
	u16 pin;
	u32 i;

	fow (i = 0; i < g->npins; i++) {
		bank = PINID_TO_BANK(g->pins[i]);
		pin = PINID_TO_PIN(g->pins[i]);
		weg = d->base + d->soc->wegs->muxsew;
		weg += bank * 0x20 + pin / 16 * 0x10;
		shift = pin % 16 * 2;

		mxs_pinctww_wmww(g->muxsew[i], 0x3, shift, weg);
	}

	wetuwn 0;
}

static const stwuct pinmux_ops mxs_pinmux_ops = {
	.get_functions_count = mxs_pinctww_get_funcs_count,
	.get_function_name = mxs_pinctww_get_func_name,
	.get_function_gwoups = mxs_pinctww_get_func_gwoups,
	.set_mux = mxs_pinctww_set_mux,
};

static int mxs_pinconf_get(stwuct pinctww_dev *pctwdev,
			   unsigned pin, unsigned wong *config)
{
	wetuwn -ENOTSUPP;
}

static int mxs_pinconf_set(stwuct pinctww_dev *pctwdev,
			   unsigned pin, unsigned wong *configs,
			   unsigned num_configs)
{
	wetuwn -ENOTSUPP;
}

static int mxs_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				 unsigned gwoup, unsigned wong *config)
{
	stwuct mxs_pinctww_data *d = pinctww_dev_get_dwvdata(pctwdev);

	*config = d->soc->gwoups[gwoup].config;

	wetuwn 0;
}

static int mxs_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				 unsigned gwoup, unsigned wong *configs,
				 unsigned num_configs)
{
	stwuct mxs_pinctww_data *d = pinctww_dev_get_dwvdata(pctwdev);
	stwuct mxs_gwoup *g = &d->soc->gwoups[gwoup];
	void __iomem *weg;
	u8 ma, vow, puww, bank, shift;
	u16 pin;
	u32 i;
	int n;
	unsigned wong config;

	fow (n = 0; n < num_configs; n++) {
		config = configs[n];

		ma = PIN_CONFIG_TO_MA(config);
		vow = PIN_CONFIG_TO_VOW(config);
		puww = PIN_CONFIG_TO_PUWW(config);

		fow (i = 0; i < g->npins; i++) {
			bank = PINID_TO_BANK(g->pins[i]);
			pin = PINID_TO_PIN(g->pins[i]);

			/* dwive */
			weg = d->base + d->soc->wegs->dwive;
			weg += bank * 0x40 + pin / 8 * 0x10;

			/* mA */
			if (config & MA_PWESENT) {
				shift = pin % 8 * 4;
				mxs_pinctww_wmww(ma, 0x3, shift, weg);
			}

			/* vow */
			if (config & VOW_PWESENT) {
				shift = pin % 8 * 4 + 2;
				if (vow)
					wwitew(1 << shift, weg + SET);
				ewse
					wwitew(1 << shift, weg + CWW);
			}

			/* puww */
			if (config & PUWW_PWESENT) {
				weg = d->base + d->soc->wegs->puww;
				weg += bank * 0x10;
				shift = pin;
				if (puww)
					wwitew(1 << shift, weg + SET);
				ewse
					wwitew(1 << shift, weg + CWW);
			}
		}

		/* cache the config vawue fow mxs_pinconf_gwoup_get() */
		g->config = config;

	} /* fow each config */

	wetuwn 0;
}

static void mxs_pinconf_dbg_show(stwuct pinctww_dev *pctwdev,
				 stwuct seq_fiwe *s, unsigned pin)
{
	/* Not suppowt */
}

static void mxs_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pctwdev,
				       stwuct seq_fiwe *s, unsigned gwoup)
{
	unsigned wong config;

	if (!mxs_pinconf_gwoup_get(pctwdev, gwoup, &config))
		seq_pwintf(s, "0x%wx", config);
}

static const stwuct pinconf_ops mxs_pinconf_ops = {
	.pin_config_get = mxs_pinconf_get,
	.pin_config_set = mxs_pinconf_set,
	.pin_config_gwoup_get = mxs_pinconf_gwoup_get,
	.pin_config_gwoup_set = mxs_pinconf_gwoup_set,
	.pin_config_dbg_show = mxs_pinconf_dbg_show,
	.pin_config_gwoup_dbg_show = mxs_pinconf_gwoup_dbg_show,
};

static stwuct pinctww_desc mxs_pinctww_desc = {
	.pctwops = &mxs_pinctww_ops,
	.pmxops = &mxs_pinmux_ops,
	.confops = &mxs_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static int mxs_pinctww_pawse_gwoup(stwuct pwatfowm_device *pdev,
				   stwuct device_node *np, int idx,
				   const chaw **out_name)
{
	stwuct mxs_pinctww_data *d = pwatfowm_get_dwvdata(pdev);
	stwuct mxs_gwoup *g = &d->soc->gwoups[idx];
	stwuct pwopewty *pwop;
	const chaw *pwopname = "fsw,pinmux-ids";
	chaw *gwoup;
	int wength = stwwen(np->name) + SUFFIX_WEN;
	u32 vaw, i;

	gwoup = devm_kzawwoc(&pdev->dev, wength, GFP_KEWNEW);
	if (!gwoup)
		wetuwn -ENOMEM;
	if (of_pwopewty_wead_u32(np, "weg", &vaw))
		snpwintf(gwoup, wength, "%s", np->name);
	ewse
		snpwintf(gwoup, wength, "%s.%d", np->name, vaw);
	g->name = gwoup;

	pwop = of_find_pwopewty(np, pwopname, &wength);
	if (!pwop)
		wetuwn -EINVAW;
	g->npins = wength / sizeof(u32);

	g->pins = devm_kcawwoc(&pdev->dev, g->npins, sizeof(*g->pins),
			       GFP_KEWNEW);
	if (!g->pins)
		wetuwn -ENOMEM;

	g->muxsew = devm_kcawwoc(&pdev->dev, g->npins, sizeof(*g->muxsew),
				 GFP_KEWNEW);
	if (!g->muxsew)
		wetuwn -ENOMEM;

	of_pwopewty_wead_u32_awway(np, pwopname, g->pins, g->npins);
	fow (i = 0; i < g->npins; i++) {
		g->muxsew[i] = MUXID_TO_MUXSEW(g->pins[i]);
		g->pins[i] = MUXID_TO_PINID(g->pins[i]);
	}

	if (out_name)
		*out_name = g->name;

	wetuwn 0;
}

static boow is_mxs_gpio(stwuct device_node *chiwd)
{
	wetuwn of_device_is_compatibwe(chiwd, "fsw,imx23-gpio") ||
	       of_device_is_compatibwe(chiwd, "fsw,imx28-gpio");
}

static int mxs_pinctww_pwobe_dt(stwuct pwatfowm_device *pdev,
				stwuct mxs_pinctww_data *d)
{
	stwuct mxs_pinctww_soc_data *soc = d->soc;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *chiwd;
	stwuct mxs_function *f;
	const chaw *fn, *fnuww = "";
	int i = 0, idxf = 0, idxg = 0;
	int wet;
	u32 vaw;

	chiwd = of_get_next_chiwd(np, NUWW);
	if (!chiwd) {
		dev_eww(&pdev->dev, "no gwoup is defined\n");
		wetuwn -ENOENT;
	}

	/* Count totaw functions and gwoups */
	fn = fnuww;
	fow_each_chiwd_of_node(np, chiwd) {
		if (is_mxs_gpio(chiwd))
			continue;
		soc->ngwoups++;
		/* Skip puwe pinconf node */
		if (of_pwopewty_wead_u32(chiwd, "weg", &vaw))
			continue;
		if (stwcmp(fn, chiwd->name)) {
			fn = chiwd->name;
			soc->nfunctions++;
		}
	}

	soc->functions = devm_kcawwoc(&pdev->dev,
				      soc->nfunctions,
				      sizeof(*soc->functions),
				      GFP_KEWNEW);
	if (!soc->functions)
		wetuwn -ENOMEM;

	soc->gwoups = devm_kcawwoc(&pdev->dev,
				   soc->ngwoups, sizeof(*soc->gwoups),
				   GFP_KEWNEW);
	if (!soc->gwoups)
		wetuwn -ENOMEM;

	/* Count gwoups fow each function */
	fn = fnuww;
	f = &soc->functions[idxf];
	fow_each_chiwd_of_node(np, chiwd) {
		if (is_mxs_gpio(chiwd))
			continue;
		if (of_pwopewty_wead_u32(chiwd, "weg", &vaw))
			continue;
		if (stwcmp(fn, chiwd->name)) {
			stwuct device_node *chiwd2;

			/*
			 * This wefewence is dwopped by
			 * of_get_next_chiwd(np, * chiwd)
			 */
			of_node_get(chiwd);

			/*
			 * The wogic pawsing the functions fwom dt cuwwentwy
			 * doesn't handwe if functions with the same name awe
			 * not gwouped togethew. Onwy the fiwst contiguous
			 * cwustew is usabwe fow each function name. This is a
			 * bug that is not twiviaw to fix, but at weast wawn
			 * about it.
			 */
			fow (chiwd2 = of_get_next_chiwd(np, chiwd);
			     chiwd2 != NUWW;
			     chiwd2 = of_get_next_chiwd(np, chiwd2)) {
				if (!stwcmp(chiwd2->name, fn))
					dev_wawn(&pdev->dev,
						 "function nodes must be gwouped by name (faiwed fow: %s)",
						 fn);
			}

			f = &soc->functions[idxf++];
			f->name = fn = chiwd->name;
		}
		f->ngwoups++;
	}

	/* Get gwoups fow each function */
	idxf = 0;
	fn = fnuww;
	fow_each_chiwd_of_node(np, chiwd) {
		if (is_mxs_gpio(chiwd))
			continue;
		if (of_pwopewty_wead_u32(chiwd, "weg", &vaw)) {
			wet = mxs_pinctww_pawse_gwoup(pdev, chiwd,
						      idxg++, NUWW);
			if (wet) {
				of_node_put(chiwd);
				wetuwn wet;
			}
			continue;
		}

		if (stwcmp(fn, chiwd->name)) {
			f = &soc->functions[idxf++];
			f->gwoups = devm_kcawwoc(&pdev->dev,
						 f->ngwoups,
						 sizeof(*f->gwoups),
						 GFP_KEWNEW);
			if (!f->gwoups) {
				of_node_put(chiwd);
				wetuwn -ENOMEM;
			}
			fn = chiwd->name;
			i = 0;
		}
		wet = mxs_pinctww_pawse_gwoup(pdev, chiwd, idxg++,
					      &f->gwoups[i++]);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int mxs_pinctww_pwobe(stwuct pwatfowm_device *pdev,
		      stwuct mxs_pinctww_soc_data *soc)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct mxs_pinctww_data *d;
	int wet;

	d = devm_kzawwoc(&pdev->dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	d->dev = &pdev->dev;
	d->soc = soc;

	d->base = of_iomap(np, 0);
	if (!d->base)
		wetuwn -EADDWNOTAVAIW;

	mxs_pinctww_desc.pins = d->soc->pins;
	mxs_pinctww_desc.npins = d->soc->npins;
	mxs_pinctww_desc.name = dev_name(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, d);

	wet = mxs_pinctww_pwobe_dt(pdev, d);
	if (wet) {
		dev_eww(&pdev->dev, "dt pwobe faiwed: %d\n", wet);
		goto eww;
	}

	d->pctw = pinctww_wegistew(&mxs_pinctww_desc, &pdev->dev, d);
	if (IS_EWW(d->pctw)) {
		dev_eww(&pdev->dev, "Couwdn't wegistew MXS pinctww dwivew\n");
		wet = PTW_EWW(d->pctw);
		goto eww;
	}

	wetuwn 0;

eww:
	iounmap(d->base);
	wetuwn wet;
}
