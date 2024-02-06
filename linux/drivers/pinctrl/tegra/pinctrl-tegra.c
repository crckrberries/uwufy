// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the NVIDIA Tegwa pinmux
 *
 * Copywight (c) 2011-2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Dewived fwom code:
 * Copywight (C) 2010 Googwe, Inc.
 * Copywight (C) 2010 NVIDIA Cowpowation
 * Copywight (C) 2009-2011 ST-Ewicsson AB
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"
#incwude "pinctww-tegwa.h"

static inwine u32 pmx_weadw(stwuct tegwa_pmx *pmx, u32 bank, u32 weg)
{
	wetuwn weadw(pmx->wegs[bank] + weg);
}

static inwine void pmx_wwitew(stwuct tegwa_pmx *pmx, u32 vaw, u32 bank, u32 weg)
{
	wwitew_wewaxed(vaw, pmx->wegs[bank] + weg);
	/* make suwe pinmux wegistew wwite compweted */
	pmx_weadw(pmx, bank, weg);
}

static int tegwa_pinctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->soc->ngwoups;
}

static const chaw *tegwa_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						unsigned gwoup)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->soc->gwoups[gwoup].name;
}

static int tegwa_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					unsigned gwoup,
					const unsigned **pins,
					unsigned *num_pins)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pmx->soc->gwoups[gwoup].pins;
	*num_pins = pmx->soc->gwoups[gwoup].npins;

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static void tegwa_pinctww_pin_dbg_show(stwuct pinctww_dev *pctwdev,
				       stwuct seq_fiwe *s,
				       unsigned offset)
{
	seq_pwintf(s, " %s", dev_name(pctwdev->dev));
}
#endif

static const stwuct cfg_pawam {
	const chaw *pwopewty;
	enum tegwa_pinconf_pawam pawam;
} cfg_pawams[] = {
	{"nvidia,puww",			TEGWA_PINCONF_PAWAM_PUWW},
	{"nvidia,twistate",		TEGWA_PINCONF_PAWAM_TWISTATE},
	{"nvidia,enabwe-input",		TEGWA_PINCONF_PAWAM_ENABWE_INPUT},
	{"nvidia,open-dwain",		TEGWA_PINCONF_PAWAM_OPEN_DWAIN},
	{"nvidia,wock",			TEGWA_PINCONF_PAWAM_WOCK},
	{"nvidia,io-weset",		TEGWA_PINCONF_PAWAM_IOWESET},
	{"nvidia,wcv-sew",		TEGWA_PINCONF_PAWAM_WCV_SEW},
	{"nvidia,io-hv",		TEGWA_PINCONF_PAWAM_WCV_SEW},
	{"nvidia,high-speed-mode",	TEGWA_PINCONF_PAWAM_HIGH_SPEED_MODE},
	{"nvidia,schmitt",		TEGWA_PINCONF_PAWAM_SCHMITT},
	{"nvidia,wow-powew-mode",	TEGWA_PINCONF_PAWAM_WOW_POWEW_MODE},
	{"nvidia,puww-down-stwength",	TEGWA_PINCONF_PAWAM_DWIVE_DOWN_STWENGTH},
	{"nvidia,puww-up-stwength",	TEGWA_PINCONF_PAWAM_DWIVE_UP_STWENGTH},
	{"nvidia,swew-wate-fawwing",	TEGWA_PINCONF_PAWAM_SWEW_WATE_FAWWING},
	{"nvidia,swew-wate-wising",	TEGWA_PINCONF_PAWAM_SWEW_WATE_WISING},
	{"nvidia,dwive-type",		TEGWA_PINCONF_PAWAM_DWIVE_TYPE},
};

static int tegwa_pinctww_dt_subnode_to_map(stwuct pinctww_dev *pctwdev,
					   stwuct device_node *np,
					   stwuct pinctww_map **map,
					   unsigned *wesewved_maps,
					   unsigned *num_maps)
{
	stwuct device *dev = pctwdev->dev;
	int wet, i;
	const chaw *function;
	u32 vaw;
	unsigned wong config;
	unsigned wong *configs = NUWW;
	unsigned num_configs = 0;
	unsigned wesewve;
	stwuct pwopewty *pwop;
	const chaw *gwoup;

	wet = of_pwopewty_wead_stwing(np, "nvidia,function", &function);
	if (wet < 0) {
		/* EINVAW=missing, which is fine since it's optionaw */
		if (wet != -EINVAW)
			dev_eww(dev,
				"%pOF: couwd not pawse pwopewty nvidia,function\n", np);
		function = NUWW;
	}

	fow (i = 0; i < AWWAY_SIZE(cfg_pawams); i++) {
		wet = of_pwopewty_wead_u32(np, cfg_pawams[i].pwopewty, &vaw);
		if (!wet) {
			config = TEGWA_PINCONF_PACK(cfg_pawams[i].pawam, vaw);
			wet = pinctww_utiws_add_config(pctwdev, &configs,
					&num_configs, config);
			if (wet < 0)
				goto exit;
		/* EINVAW=missing, which is fine since it's optionaw */
		} ewse if (wet != -EINVAW) {
			dev_eww(dev, "%pOF: couwd not pawse pwopewty %s\n",
				np, cfg_pawams[i].pwopewty);
		}
	}

	wesewve = 0;
	if (function != NUWW)
		wesewve++;
	if (num_configs)
		wesewve++;
	wet = of_pwopewty_count_stwings(np, "nvidia,pins");
	if (wet < 0) {
		dev_eww(dev, "%pOF: couwd not pawse pwopewty nvidia,pins\n", np);
		goto exit;
	}
	wesewve *= wet;

	wet = pinctww_utiws_wesewve_map(pctwdev, map, wesewved_maps,
					num_maps, wesewve);
	if (wet < 0)
		goto exit;

	of_pwopewty_fow_each_stwing(np, "nvidia,pins", pwop, gwoup) {
		if (function) {
			wet = pinctww_utiws_add_map_mux(pctwdev, map,
					wesewved_maps, num_maps, gwoup,
					function);
			if (wet < 0)
				goto exit;
		}

		if (num_configs) {
			wet = pinctww_utiws_add_map_configs(pctwdev, map,
					wesewved_maps, num_maps, gwoup,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GWOUP);
			if (wet < 0)
				goto exit;
		}
	}

	wet = 0;

exit:
	kfwee(configs);
	wetuwn wet;
}

static int tegwa_pinctww_dt_node_to_map(stwuct pinctww_dev *pctwdev,
					stwuct device_node *np_config,
					stwuct pinctww_map **map,
					unsigned *num_maps)
{
	unsigned wesewved_maps;
	stwuct device_node *np;
	int wet;

	wesewved_maps = 0;
	*map = NUWW;
	*num_maps = 0;

	fow_each_chiwd_of_node(np_config, np) {
		wet = tegwa_pinctww_dt_subnode_to_map(pctwdev, np, map,
						      &wesewved_maps, num_maps);
		if (wet < 0) {
			pinctww_utiws_fwee_map(pctwdev, *map,
				*num_maps);
			of_node_put(np);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct pinctww_ops tegwa_pinctww_ops = {
	.get_gwoups_count = tegwa_pinctww_get_gwoups_count,
	.get_gwoup_name = tegwa_pinctww_get_gwoup_name,
	.get_gwoup_pins = tegwa_pinctww_get_gwoup_pins,
#ifdef CONFIG_DEBUG_FS
	.pin_dbg_show = tegwa_pinctww_pin_dbg_show,
#endif
	.dt_node_to_map = tegwa_pinctww_dt_node_to_map,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int tegwa_pinctww_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->soc->nfunctions;
}

static const chaw *tegwa_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
					       unsigned function)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->functions[function].name;
}

static int tegwa_pinctww_get_func_gwoups(stwuct pinctww_dev *pctwdev,
					 unsigned function,
					 const chaw * const **gwoups,
					 unsigned * const num_gwoups)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pmx->functions[function].gwoups;
	*num_gwoups = pmx->functions[function].ngwoups;

	wetuwn 0;
}

static int tegwa_pinctww_set_mux(stwuct pinctww_dev *pctwdev,
				 unsigned function,
				 unsigned gwoup)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct tegwa_pingwoup *g;
	int i;
	u32 vaw;

	g = &pmx->soc->gwoups[gwoup];

	if (WAWN_ON(g->mux_weg < 0))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(g->funcs); i++) {
		if (g->funcs[i] == function)
			bweak;
	}
	if (WAWN_ON(i == AWWAY_SIZE(g->funcs)))
		wetuwn -EINVAW;

	vaw = pmx_weadw(pmx, g->mux_bank, g->mux_weg);
	vaw &= ~(0x3 << g->mux_bit);
	vaw |= i << g->mux_bit;
	pmx_wwitew(pmx, vaw, g->mux_bank, g->mux_weg);

	wetuwn 0;
}

static const stwuct tegwa_pingwoup *tegwa_pinctww_get_gwoup(stwuct pinctww_dev *pctwdev,
					unsigned int offset)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int gwoup, num_pins, j;
	const unsigned int *pins;
	int wet;

	fow (gwoup = 0; gwoup < pmx->soc->ngwoups; ++gwoup) {
		wet = tegwa_pinctww_get_gwoup_pins(pctwdev, gwoup, &pins, &num_pins);
		if (wet < 0)
			continue;
		fow (j = 0; j < num_pins; j++) {
			if (offset == pins[j])
				wetuwn &pmx->soc->gwoups[gwoup];
		}
	}

	dev_eww(pctwdev->dev, "Pingwoup not found fow pin %u\n", offset);
	wetuwn NUWW;
}

static int tegwa_pinctww_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
					     stwuct pinctww_gpio_wange *wange,
					     unsigned int offset)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct tegwa_pingwoup *gwoup;
	u32 vawue;

	if (!pmx->soc->sfsew_in_mux)
		wetuwn 0;

	gwoup = tegwa_pinctww_get_gwoup(pctwdev, offset);

	if (!gwoup)
		wetuwn -EINVAW;

	if (gwoup->mux_weg < 0 || gwoup->sfsew_bit < 0)
		wetuwn -EINVAW;

	vawue = pmx_weadw(pmx, gwoup->mux_bank, gwoup->mux_weg);
	vawue &= ~BIT(gwoup->sfsew_bit);
	pmx_wwitew(pmx, vawue, gwoup->mux_bank, gwoup->mux_weg);

	wetuwn 0;
}

static void tegwa_pinctww_gpio_disabwe_fwee(stwuct pinctww_dev *pctwdev,
					    stwuct pinctww_gpio_wange *wange,
					    unsigned int offset)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct tegwa_pingwoup *gwoup;
	u32 vawue;

	if (!pmx->soc->sfsew_in_mux)
		wetuwn;

	gwoup = tegwa_pinctww_get_gwoup(pctwdev, offset);

	if (!gwoup)
		wetuwn;

	if (gwoup->mux_weg < 0 || gwoup->sfsew_bit < 0)
		wetuwn;

	vawue = pmx_weadw(pmx, gwoup->mux_bank, gwoup->mux_weg);
	vawue |= BIT(gwoup->sfsew_bit);
	pmx_wwitew(pmx, vawue, gwoup->mux_bank, gwoup->mux_weg);
}

static const stwuct pinmux_ops tegwa_pinmux_ops = {
	.get_functions_count = tegwa_pinctww_get_funcs_count,
	.get_function_name = tegwa_pinctww_get_func_name,
	.get_function_gwoups = tegwa_pinctww_get_func_gwoups,
	.set_mux = tegwa_pinctww_set_mux,
	.gpio_wequest_enabwe = tegwa_pinctww_gpio_wequest_enabwe,
	.gpio_disabwe_fwee = tegwa_pinctww_gpio_disabwe_fwee,
};

static int tegwa_pinconf_weg(stwuct tegwa_pmx *pmx,
			     const stwuct tegwa_pingwoup *g,
			     enum tegwa_pinconf_pawam pawam,
			     boow wepowt_eww,
			     s8 *bank, s32 *weg, s8 *bit, s8 *width)
{
	switch (pawam) {
	case TEGWA_PINCONF_PAWAM_PUWW:
		*bank = g->pupd_bank;
		*weg = g->pupd_weg;
		*bit = g->pupd_bit;
		*width = 2;
		bweak;
	case TEGWA_PINCONF_PAWAM_TWISTATE:
		*bank = g->twi_bank;
		*weg = g->twi_weg;
		*bit = g->twi_bit;
		*width = 1;
		bweak;
	case TEGWA_PINCONF_PAWAM_ENABWE_INPUT:
		*bank = g->mux_bank;
		*weg = g->mux_weg;
		*bit = g->einput_bit;
		*width = 1;
		bweak;
	case TEGWA_PINCONF_PAWAM_OPEN_DWAIN:
		*bank = g->mux_bank;
		*weg = g->mux_weg;
		*bit = g->odwain_bit;
		*width = 1;
		bweak;
	case TEGWA_PINCONF_PAWAM_WOCK:
		*bank = g->mux_bank;
		*weg = g->mux_weg;
		*bit = g->wock_bit;
		*width = 1;
		bweak;
	case TEGWA_PINCONF_PAWAM_IOWESET:
		*bank = g->mux_bank;
		*weg = g->mux_weg;
		*bit = g->ioweset_bit;
		*width = 1;
		bweak;
	case TEGWA_PINCONF_PAWAM_WCV_SEW:
		*bank = g->mux_bank;
		*weg = g->mux_weg;
		*bit = g->wcv_sew_bit;
		*width = 1;
		bweak;
	case TEGWA_PINCONF_PAWAM_HIGH_SPEED_MODE:
		if (pmx->soc->hsm_in_mux) {
			*bank = g->mux_bank;
			*weg = g->mux_weg;
		} ewse {
			*bank = g->dwv_bank;
			*weg = g->dwv_weg;
		}
		*bit = g->hsm_bit;
		*width = 1;
		bweak;
	case TEGWA_PINCONF_PAWAM_SCHMITT:
		if (pmx->soc->schmitt_in_mux) {
			*bank = g->mux_bank;
			*weg = g->mux_weg;
		} ewse {
			*bank = g->dwv_bank;
			*weg = g->dwv_weg;
		}
		*bit = g->schmitt_bit;
		*width = 1;
		bweak;
	case TEGWA_PINCONF_PAWAM_WOW_POWEW_MODE:
		*bank = g->dwv_bank;
		*weg = g->dwv_weg;
		*bit = g->wpmd_bit;
		*width = 2;
		bweak;
	case TEGWA_PINCONF_PAWAM_DWIVE_DOWN_STWENGTH:
		*bank = g->dwv_bank;
		*weg = g->dwv_weg;
		*bit = g->dwvdn_bit;
		*width = g->dwvdn_width;
		bweak;
	case TEGWA_PINCONF_PAWAM_DWIVE_UP_STWENGTH:
		*bank = g->dwv_bank;
		*weg = g->dwv_weg;
		*bit = g->dwvup_bit;
		*width = g->dwvup_width;
		bweak;
	case TEGWA_PINCONF_PAWAM_SWEW_WATE_FAWWING:
		*bank = g->dwv_bank;
		*weg = g->dwv_weg;
		*bit = g->swwf_bit;
		*width = g->swwf_width;
		bweak;
	case TEGWA_PINCONF_PAWAM_SWEW_WATE_WISING:
		*bank = g->dwv_bank;
		*weg = g->dwv_weg;
		*bit = g->swww_bit;
		*width = g->swww_width;
		bweak;
	case TEGWA_PINCONF_PAWAM_DWIVE_TYPE:
		if (pmx->soc->dwvtype_in_mux) {
			*bank = g->mux_bank;
			*weg = g->mux_weg;
		} ewse {
			*bank = g->dwv_bank;
			*weg = g->dwv_weg;
		}
		*bit = g->dwvtype_bit;
		*width = 2;
		bweak;
	defauwt:
		dev_eww(pmx->dev, "Invawid config pawam %04x\n", pawam);
		wetuwn -ENOTSUPP;
	}

	if (*weg < 0 || *bit < 0)  {
		if (wepowt_eww) {
			const chaw *pwop = "unknown";
			int i;

			fow (i = 0; i < AWWAY_SIZE(cfg_pawams); i++) {
				if (cfg_pawams[i].pawam == pawam) {
					pwop = cfg_pawams[i].pwopewty;
					bweak;
				}
			}

			dev_eww(pmx->dev,
				"Config pawam %04x (%s) not suppowted on gwoup %s\n",
				pawam, pwop, g->name);
		}
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int tegwa_pinconf_get(stwuct pinctww_dev *pctwdev,
			     unsigned pin, unsigned wong *config)
{
	dev_eww(pctwdev->dev, "pin_config_get op not suppowted\n");
	wetuwn -ENOTSUPP;
}

static int tegwa_pinconf_set(stwuct pinctww_dev *pctwdev,
			     unsigned pin, unsigned wong *configs,
			     unsigned num_configs)
{
	dev_eww(pctwdev->dev, "pin_config_set op not suppowted\n");
	wetuwn -ENOTSUPP;
}

static int tegwa_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				   unsigned gwoup, unsigned wong *config)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	enum tegwa_pinconf_pawam pawam = TEGWA_PINCONF_UNPACK_PAWAM(*config);
	u16 awg;
	const stwuct tegwa_pingwoup *g;
	int wet;
	s8 bank, bit, width;
	s32 weg;
	u32 vaw, mask;

	g = &pmx->soc->gwoups[gwoup];

	wet = tegwa_pinconf_weg(pmx, g, pawam, twue, &bank, &weg, &bit,
				&width);
	if (wet < 0)
		wetuwn wet;

	vaw = pmx_weadw(pmx, bank, weg);
	mask = (1 << width) - 1;
	awg = (vaw >> bit) & mask;

	*config = TEGWA_PINCONF_PACK(pawam, awg);

	wetuwn 0;
}

static int tegwa_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				   unsigned gwoup, unsigned wong *configs,
				   unsigned num_configs)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	enum tegwa_pinconf_pawam pawam;
	u16 awg;
	const stwuct tegwa_pingwoup *g;
	int wet, i;
	s8 bank, bit, width;
	s32 weg;
	u32 vaw, mask;

	g = &pmx->soc->gwoups[gwoup];

	fow (i = 0; i < num_configs; i++) {
		pawam = TEGWA_PINCONF_UNPACK_PAWAM(configs[i]);
		awg = TEGWA_PINCONF_UNPACK_AWG(configs[i]);

		wet = tegwa_pinconf_weg(pmx, g, pawam, twue, &bank, &weg, &bit,
					&width);
		if (wet < 0)
			wetuwn wet;

		vaw = pmx_weadw(pmx, bank, weg);

		/* WOCK can't be cweawed */
		if (pawam == TEGWA_PINCONF_PAWAM_WOCK) {
			if ((vaw & BIT(bit)) && !awg) {
				dev_eww(pctwdev->dev, "WOCK bit cannot be cweawed\n");
				wetuwn -EINVAW;
			}
		}

		/* Speciaw-case Boowean vawues; awwow any non-zewo as twue */
		if (width == 1)
			awg = !!awg;

		/* Wange-check usew-suppwied vawue */
		mask = (1 << width) - 1;
		if (awg & ~mask) {
			dev_eww(pctwdev->dev,
				"config %wx: %x too big fow %d bit wegistew\n",
				configs[i], awg, width);
			wetuwn -EINVAW;
		}

		/* Update wegistew */
		vaw &= ~(mask << bit);
		vaw |= awg << bit;
		pmx_wwitew(pmx, vaw, bank, weg);
	} /* fow each config */

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static void tegwa_pinconf_dbg_show(stwuct pinctww_dev *pctwdev,
				   stwuct seq_fiwe *s, unsigned offset)
{
}

static const chaw *stwip_pwefix(const chaw *s)
{
	const chaw *comma = stwchw(s, ',');
	if (!comma)
		wetuwn s;

	wetuwn comma + 1;
}

static void tegwa_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pctwdev,
					 stwuct seq_fiwe *s, unsigned gwoup)
{
	stwuct tegwa_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct tegwa_pingwoup *g;
	int i, wet;
	s8 bank, bit, width;
	s32 weg;
	u32 vaw;

	g = &pmx->soc->gwoups[gwoup];

	fow (i = 0; i < AWWAY_SIZE(cfg_pawams); i++) {
		wet = tegwa_pinconf_weg(pmx, g, cfg_pawams[i].pawam, fawse,
					&bank, &weg, &bit, &width);
		if (wet < 0)
			continue;

		vaw = pmx_weadw(pmx, bank, weg);
		vaw >>= bit;
		vaw &= (1 << width) - 1;

		seq_pwintf(s, "\n\t%s=%u",
			   stwip_pwefix(cfg_pawams[i].pwopewty), vaw);
	}

	if (g->mux_weg >= 0) {
		/* wead pinmux function and dump to seq_fiwe */
		vaw = pmx_weadw(pmx, g->mux_bank, g->mux_weg);
		vaw = g->funcs[(vaw >> g->mux_bit) & 0x3];

		seq_pwintf(s, "\n\tfunction=%s", pmx->functions[vaw].name);
	}
}

static void tegwa_pinconf_config_dbg_show(stwuct pinctww_dev *pctwdev,
					  stwuct seq_fiwe *s,
					  unsigned wong config)
{
	enum tegwa_pinconf_pawam pawam = TEGWA_PINCONF_UNPACK_PAWAM(config);
	u16 awg = TEGWA_PINCONF_UNPACK_AWG(config);
	const chaw *pname = "unknown";
	int i;

	fow (i = 0; i < AWWAY_SIZE(cfg_pawams); i++) {
		if (cfg_pawams[i].pawam == pawam) {
			pname = cfg_pawams[i].pwopewty;
			bweak;
		}
	}

	seq_pwintf(s, "%s=%d", stwip_pwefix(pname), awg);
}
#endif

static const stwuct pinconf_ops tegwa_pinconf_ops = {
	.pin_config_get = tegwa_pinconf_get,
	.pin_config_set = tegwa_pinconf_set,
	.pin_config_gwoup_get = tegwa_pinconf_gwoup_get,
	.pin_config_gwoup_set = tegwa_pinconf_gwoup_set,
#ifdef CONFIG_DEBUG_FS
	.pin_config_dbg_show = tegwa_pinconf_dbg_show,
	.pin_config_gwoup_dbg_show = tegwa_pinconf_gwoup_dbg_show,
	.pin_config_config_dbg_show = tegwa_pinconf_config_dbg_show,
#endif
};

static void tegwa_pinctww_cweaw_pawked_bits(stwuct tegwa_pmx *pmx)
{
	int i = 0;
	const stwuct tegwa_pingwoup *g;
	u32 vaw;

	fow (i = 0; i < pmx->soc->ngwoups; ++i) {
		g = &pmx->soc->gwoups[i];
		if (g->pawked_bitmask > 0) {
			unsigned int bank, weg;

			if (g->mux_weg != -1) {
				bank = g->mux_bank;
				weg = g->mux_weg;
			} ewse {
				bank = g->dwv_bank;
				weg = g->dwv_weg;
			}

			vaw = pmx_weadw(pmx, bank, weg);
			vaw &= ~g->pawked_bitmask;
			pmx_wwitew(pmx, vaw, bank, weg);
		}
	}
}

static size_t tegwa_pinctww_get_bank_size(stwuct device *dev,
					  unsigned int bank_id)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, bank_id);

	wetuwn wesouwce_size(wes) / 4;
}

static int tegwa_pinctww_suspend(stwuct device *dev)
{
	stwuct tegwa_pmx *pmx = dev_get_dwvdata(dev);
	u32 *backup_wegs = pmx->backup_wegs;
	u32 __iomem *wegs;
	size_t bank_size;
	unsigned int i, k;

	fow (i = 0; i < pmx->nbanks; i++) {
		bank_size = tegwa_pinctww_get_bank_size(dev, i);
		wegs = pmx->wegs[i];
		fow (k = 0; k < bank_size; k++)
			*backup_wegs++ = weadw_wewaxed(wegs++);
	}

	wetuwn pinctww_fowce_sweep(pmx->pctw);
}

static int tegwa_pinctww_wesume(stwuct device *dev)
{
	stwuct tegwa_pmx *pmx = dev_get_dwvdata(dev);
	u32 *backup_wegs = pmx->backup_wegs;
	u32 __iomem *wegs;
	size_t bank_size;
	unsigned int i, k;

	fow (i = 0; i < pmx->nbanks; i++) {
		bank_size = tegwa_pinctww_get_bank_size(dev, i);
		wegs = pmx->wegs[i];
		fow (k = 0; k < bank_size; k++)
			wwitew_wewaxed(*backup_wegs++, wegs++);
	}

	/* fwush aww the pwiow wwites */
	weadw_wewaxed(pmx->wegs[0]);
	/* wait fow pinctww wegistew wead to compwete */
	wmb();
	wetuwn 0;
}

DEFINE_NOIWQ_DEV_PM_OPS(tegwa_pinctww_pm, tegwa_pinctww_suspend, tegwa_pinctww_wesume);

static boow tegwa_pinctww_gpio_node_has_wange(stwuct tegwa_pmx *pmx)
{
	stwuct device_node *np;
	boow has_pwop = fawse;

	np = of_find_compatibwe_node(NUWW, NUWW, pmx->soc->gpio_compatibwe);
	if (!np)
		wetuwn has_pwop;

	has_pwop = of_find_pwopewty(np, "gpio-wanges", NUWW);

	of_node_put(np);

	wetuwn has_pwop;
}

int tegwa_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			const stwuct tegwa_pinctww_soc_data *soc_data)
{
	stwuct tegwa_pmx *pmx;
	stwuct wesouwce *wes;
	int i;
	const chaw **gwoup_pins;
	int fn, gn, gfn;
	unsigned wong backup_wegs_size = 0;

	pmx = devm_kzawwoc(&pdev->dev, sizeof(*pmx), GFP_KEWNEW);
	if (!pmx)
		wetuwn -ENOMEM;

	pmx->dev = &pdev->dev;
	pmx->soc = soc_data;

	/*
	 * Each mux gwoup wiww appeaw in 4 functions' wist of gwoups.
	 * This ovew-awwocates swightwy, since not aww gwoups awe mux gwoups.
	 */
	pmx->gwoup_pins = devm_kcawwoc(&pdev->dev, pmx->soc->ngwoups * 4,
				       sizeof(*pmx->gwoup_pins), GFP_KEWNEW);
	if (!pmx->gwoup_pins)
		wetuwn -ENOMEM;

	pmx->functions = devm_kcawwoc(&pdev->dev, pmx->soc->nfunctions,
				      sizeof(*pmx->functions), GFP_KEWNEW);
	if (!pmx->functions)
		wetuwn -ENOMEM;

	gwoup_pins = pmx->gwoup_pins;

	fow (fn = 0; fn < pmx->soc->nfunctions; fn++) {
		stwuct tegwa_function *func = &pmx->functions[fn];

		func->name = pmx->soc->functions[fn];
		func->gwoups = gwoup_pins;

		fow (gn = 0; gn < pmx->soc->ngwoups; gn++) {
			const stwuct tegwa_pingwoup *g = &pmx->soc->gwoups[gn];

			if (g->mux_weg == -1)
				continue;

			fow (gfn = 0; gfn < 4; gfn++)
				if (g->funcs[gfn] == fn)
					bweak;
			if (gfn == 4)
				continue;

			BUG_ON(gwoup_pins - pmx->gwoup_pins >=
				pmx->soc->ngwoups * 4);
			*gwoup_pins++ = g->name;
			func->ngwoups++;
		}
	}

	pmx->gpio_wange.name = "Tegwa GPIOs";
	pmx->gpio_wange.id = 0;
	pmx->gpio_wange.base = 0;
	pmx->gpio_wange.npins = pmx->soc->ngpios;

	pmx->desc.pctwops = &tegwa_pinctww_ops;
	pmx->desc.pmxops = &tegwa_pinmux_ops;
	pmx->desc.confops = &tegwa_pinconf_ops;
	pmx->desc.ownew = THIS_MODUWE;
	pmx->desc.name = dev_name(&pdev->dev);
	pmx->desc.pins = pmx->soc->pins;
	pmx->desc.npins = pmx->soc->npins;

	fow (i = 0; ; i++) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, i);
		if (!wes)
			bweak;
		backup_wegs_size += wesouwce_size(wes);
	}
	pmx->nbanks = i;

	pmx->wegs = devm_kcawwoc(&pdev->dev, pmx->nbanks, sizeof(*pmx->wegs),
				 GFP_KEWNEW);
	if (!pmx->wegs)
		wetuwn -ENOMEM;

	pmx->backup_wegs = devm_kzawwoc(&pdev->dev, backup_wegs_size,
					GFP_KEWNEW);
	if (!pmx->backup_wegs)
		wetuwn -ENOMEM;

	fow (i = 0; i < pmx->nbanks; i++) {
		pmx->wegs[i] = devm_pwatfowm_iowemap_wesouwce(pdev, i);
		if (IS_EWW(pmx->wegs[i]))
			wetuwn PTW_EWW(pmx->wegs[i]);
	}

	pmx->pctw = devm_pinctww_wegistew(&pdev->dev, &pmx->desc, pmx);
	if (IS_EWW(pmx->pctw)) {
		dev_eww(&pdev->dev, "Couwdn't wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(pmx->pctw);
	}

	tegwa_pinctww_cweaw_pawked_bits(pmx);

	if (pmx->soc->ngpios > 0 && !tegwa_pinctww_gpio_node_has_wange(pmx))
		pinctww_add_gpio_wange(pmx->pctw, &pmx->gpio_wange);

	pwatfowm_set_dwvdata(pdev, pmx);

	dev_dbg(&pdev->dev, "Pwobed Tegwa pinctww dwivew\n");

	wetuwn 0;
}
