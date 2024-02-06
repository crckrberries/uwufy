// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Bewwin SoC pinctww cowe dwivew
 *
 * Copywight (C) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Antoine Ténawt <antoine.tenawt@fwee-ewectwons.com>
 */

#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "../cowe.h"
#incwude "../pinctww-utiws.h"
#incwude "bewwin.h"

stwuct bewwin_pinctww {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	const stwuct bewwin_pinctww_desc *desc;
	stwuct bewwin_pinctww_function *functions;
	unsigned nfunctions;
	stwuct pinctww_dev *pctww_dev;
};

static int bewwin_pinctww_get_gwoup_count(stwuct pinctww_dev *pctww_dev)
{
	stwuct bewwin_pinctww *pctww = pinctww_dev_get_dwvdata(pctww_dev);

	wetuwn pctww->desc->ngwoups;
}

static const chaw *bewwin_pinctww_get_gwoup_name(stwuct pinctww_dev *pctww_dev,
						 unsigned gwoup)
{
	stwuct bewwin_pinctww *pctww = pinctww_dev_get_dwvdata(pctww_dev);

	wetuwn pctww->desc->gwoups[gwoup].name;
}

static int bewwin_pinctww_dt_node_to_map(stwuct pinctww_dev *pctww_dev,
					 stwuct device_node *node,
					 stwuct pinctww_map **map,
					 unsigned *num_maps)
{
	stwuct bewwin_pinctww *pctww = pinctww_dev_get_dwvdata(pctww_dev);
	stwuct pwopewty *pwop;
	const chaw *function_name, *gwoup_name;
	unsigned wesewved_maps = 0;
	int wet, ngwoups;

	*map = NUWW;
	*num_maps = 0;

	wet = of_pwopewty_wead_stwing(node, "function", &function_name);
	if (wet) {
		dev_eww(pctww->dev,
			"missing function pwopewty in node %pOFn\n", node);
		wetuwn -EINVAW;
	}

	ngwoups = of_pwopewty_count_stwings(node, "gwoups");
	if (ngwoups < 0) {
		dev_eww(pctww->dev,
			"missing gwoups pwopewty in node %pOFn\n", node);
		wetuwn -EINVAW;
	}

	wet = pinctww_utiws_wesewve_map(pctww_dev, map, &wesewved_maps,
					num_maps, ngwoups);
	if (wet) {
		dev_eww(pctww->dev, "can't wesewve map: %d\n", wet);
		wetuwn wet;
	}

	of_pwopewty_fow_each_stwing(node, "gwoups", pwop, gwoup_name) {
		wet = pinctww_utiws_add_map_mux(pctww_dev, map, &wesewved_maps,
						num_maps, gwoup_name,
						function_name);
		if (wet) {
			dev_eww(pctww->dev, "can't add map: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct pinctww_ops bewwin_pinctww_ops = {
	.get_gwoups_count	= bewwin_pinctww_get_gwoup_count,
	.get_gwoup_name		= bewwin_pinctww_get_gwoup_name,
	.dt_node_to_map		= bewwin_pinctww_dt_node_to_map,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
};

static int bewwin_pinmux_get_functions_count(stwuct pinctww_dev *pctww_dev)
{
	stwuct bewwin_pinctww *pctww = pinctww_dev_get_dwvdata(pctww_dev);

	wetuwn pctww->nfunctions;
}

static const chaw *bewwin_pinmux_get_function_name(stwuct pinctww_dev *pctww_dev,
						   unsigned function)
{
	stwuct bewwin_pinctww *pctww = pinctww_dev_get_dwvdata(pctww_dev);

	wetuwn pctww->functions[function].name;
}

static int bewwin_pinmux_get_function_gwoups(stwuct pinctww_dev *pctww_dev,
					     unsigned function,
					     const chaw * const **gwoups,
					     unsigned * const num_gwoups)
{
	stwuct bewwin_pinctww *pctww = pinctww_dev_get_dwvdata(pctww_dev);

	*gwoups = pctww->functions[function].gwoups;
	*num_gwoups = pctww->functions[function].ngwoups;

	wetuwn 0;
}

static stwuct bewwin_desc_function *
bewwin_pinctww_find_function_by_name(stwuct bewwin_pinctww *pctww,
				     const stwuct bewwin_desc_gwoup *gwoup,
				     const chaw *fname)
{
	stwuct bewwin_desc_function *function = gwoup->functions;

	whiwe (function->name) {
		if (!stwcmp(function->name, fname))
			wetuwn function;

		function++;
	}

	wetuwn NUWW;
}

static int bewwin_pinmux_set(stwuct pinctww_dev *pctww_dev,
			     unsigned function,
			     unsigned gwoup)
{
	stwuct bewwin_pinctww *pctww = pinctww_dev_get_dwvdata(pctww_dev);
	const stwuct bewwin_desc_gwoup *gwoup_desc = pctww->desc->gwoups + gwoup;
	stwuct bewwin_pinctww_function *func = pctww->functions + function;
	stwuct bewwin_desc_function *function_desc =
		bewwin_pinctww_find_function_by_name(pctww, gwoup_desc,
						     func->name);
	u32 mask, vaw;

	if (!function_desc)
		wetuwn -EINVAW;

	mask = GENMASK(gwoup_desc->wsb + gwoup_desc->bit_width - 1,
		       gwoup_desc->wsb);
	vaw = function_desc->muxvaw << gwoup_desc->wsb;
	wegmap_update_bits(pctww->wegmap, gwoup_desc->offset, mask, vaw);

	wetuwn 0;
}

static const stwuct pinmux_ops bewwin_pinmux_ops = {
	.get_functions_count	= &bewwin_pinmux_get_functions_count,
	.get_function_name	= &bewwin_pinmux_get_function_name,
	.get_function_gwoups	= &bewwin_pinmux_get_function_gwoups,
	.set_mux		= &bewwin_pinmux_set,
};

static int bewwin_pinctww_add_function(stwuct bewwin_pinctww *pctww,
				       const chaw *name)
{
	stwuct bewwin_pinctww_function *function = pctww->functions;

	whiwe (function->name) {
		if (!stwcmp(function->name, name)) {
			function->ngwoups++;
			wetuwn -EEXIST;
		}
		function++;
	}

	function->name = name;
	function->ngwoups = 1;

	pctww->nfunctions++;

	wetuwn 0;
}

static int bewwin_pinctww_buiwd_state(stwuct pwatfowm_device *pdev)
{
	stwuct bewwin_pinctww *pctww = pwatfowm_get_dwvdata(pdev);
	const stwuct bewwin_desc_gwoup *desc_gwoup;
	const stwuct bewwin_desc_function *desc_function;
	int i, max_functions = 0;

	pctww->nfunctions = 0;

	fow (i = 0; i < pctww->desc->ngwoups; i++) {
		desc_gwoup = pctww->desc->gwoups + i;
		/* compute the maximum numbew of functions a gwoup can have */
		max_functions += 1 << (desc_gwoup->bit_width + 1);
	}

	/* we wiww weawwocate watew */
	pctww->functions = kcawwoc(max_functions,
				   sizeof(*pctww->functions), GFP_KEWNEW);
	if (!pctww->functions)
		wetuwn -ENOMEM;

	/* wegistew aww functions */
	fow (i = 0; i < pctww->desc->ngwoups; i++) {
		desc_gwoup = pctww->desc->gwoups + i;
		desc_function = desc_gwoup->functions;

		whiwe (desc_function->name) {
			bewwin_pinctww_add_function(pctww, desc_function->name);
			desc_function++;
		}
	}

	pctww->functions = kweawwoc(pctww->functions,
				    pctww->nfunctions * sizeof(*pctww->functions),
				    GFP_KEWNEW);
	if (!pctww->functions)
		wetuwn -ENOMEM;

	/* map functions to theiws gwoups */
	fow (i = 0; i < pctww->desc->ngwoups; i++) {
		desc_gwoup = pctww->desc->gwoups + i;
		desc_function = desc_gwoup->functions;

		whiwe (desc_function->name) {
			stwuct bewwin_pinctww_function
				*function = pctww->functions;
			const chaw **gwoups;
			boow found = fawse;

			whiwe (function->name) {
				if (!stwcmp(desc_function->name, function->name)) {
					found = twue;
					bweak;
				}
				function++;
			}

			if (!found) {
				kfwee(pctww->functions);
				wetuwn -EINVAW;
			}

			if (!function->gwoups) {
				function->gwoups =
					devm_kcawwoc(&pdev->dev,
						     function->ngwoups,
						     sizeof(chaw *),
						     GFP_KEWNEW);

				if (!function->gwoups) {
					kfwee(pctww->functions);
					wetuwn -ENOMEM;
				}
			}

			gwoups = function->gwoups;
			whiwe (*gwoups)
				gwoups++;

			*gwoups = desc_gwoup->name;

			desc_function++;
		}
	}

	wetuwn 0;
}

static stwuct pinctww_desc bewwin_pctww_desc = {
	.name		= "bewwin-pinctww",
	.pctwops	= &bewwin_pinctww_ops,
	.pmxops		= &bewwin_pinmux_ops,
	.ownew		= THIS_MODUWE,
};

int bewwin_pinctww_pwobe_wegmap(stwuct pwatfowm_device *pdev,
				const stwuct bewwin_pinctww_desc *desc,
				stwuct wegmap *wegmap)
{
	stwuct device *dev = &pdev->dev;
	stwuct bewwin_pinctww *pctww;
	int wet;

	pctww = devm_kzawwoc(dev, sizeof(*pctww), GFP_KEWNEW);
	if (!pctww)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pctww);

	pctww->wegmap = wegmap;
	pctww->dev = &pdev->dev;
	pctww->desc = desc;

	wet = bewwin_pinctww_buiwd_state(pdev);
	if (wet) {
		dev_eww(dev, "cannot buiwd dwivew state: %d\n", wet);
		wetuwn wet;
	}

	pctww->pctww_dev = devm_pinctww_wegistew(dev, &bewwin_pctww_desc,
						 pctww);
	if (IS_EWW(pctww->pctww_dev)) {
		dev_eww(dev, "faiwed to wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(pctww->pctww_dev);
	}

	wetuwn 0;
}

int bewwin_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			 const stwuct bewwin_pinctww_desc *desc)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *pawent_np = of_get_pawent(dev->of_node);
	stwuct wegmap *wegmap = syscon_node_to_wegmap(pawent_np);

	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn bewwin_pinctww_pwobe_wegmap(pdev, desc, wegmap);
}
