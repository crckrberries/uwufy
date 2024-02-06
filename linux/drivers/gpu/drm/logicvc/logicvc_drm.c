// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwint.h>

#incwude "wogicvc_cwtc.h"
#incwude "wogicvc_dwm.h"
#incwude "wogicvc_intewface.h"
#incwude "wogicvc_mode.h"
#incwude "wogicvc_wayew.h"
#incwude "wogicvc_of.h"
#incwude "wogicvc_wegs.h"

DEFINE_DWM_GEM_DMA_FOPS(wogicvc_dwm_fops);

static int wogicvc_dwm_gem_dma_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
					   stwuct dwm_device *dwm_dev,
					   stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct wogicvc_dwm *wogicvc = wogicvc_dwm(dwm_dev);

	/* Stwide is awways fixed to its configuwation vawue. */
	awgs->pitch = wogicvc->config.wow_stwide * DIV_WOUND_UP(awgs->bpp, 8);

	wetuwn dwm_gem_dma_dumb_cweate_intewnaw(fiwe_pwiv, dwm_dev, awgs);
}

static stwuct dwm_dwivew wogicvc_dwm_dwivew = {
	.dwivew_featuwes		= DWIVEW_GEM | DWIVEW_MODESET |
					  DWIVEW_ATOMIC,

	.fops				= &wogicvc_dwm_fops,
	.name				= "wogicvc-dwm",
	.desc				= "Xywon WogiCVC DWM dwivew",
	.date				= "20200403",
	.majow				= 1,
	.minow				= 0,

	DWM_GEM_DMA_DWIVEW_OPS_VMAP_WITH_DUMB_CWEATE(wogicvc_dwm_gem_dma_dumb_cweate),
};

static stwuct wegmap_config wogicvc_dwm_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.name		= "wogicvc-dwm",
};

static iwqwetuwn_t wogicvc_dwm_iwq_handwew(int iwq, void *data)
{
	stwuct wogicvc_dwm *wogicvc = data;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 stat = 0;

	/* Get pending intewwupt souwces. */
	wegmap_wead(wogicvc->wegmap, WOGICVC_INT_STAT_WEG, &stat);

	/* Cweaw aww pending intewwupt souwces. */
	wegmap_wwite(wogicvc->wegmap, WOGICVC_INT_STAT_WEG, stat);

	if (stat & WOGICVC_INT_STAT_V_SYNC) {
		wogicvc_cwtc_vbwank_handwew(wogicvc);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static int wogicvc_dwm_config_pawse(stwuct wogicvc_dwm *wogicvc)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	stwuct device *dev = dwm_dev->dev;
	stwuct device_node *of_node = dev->of_node;
	stwuct wogicvc_dwm_config *config = &wogicvc->config;
	stwuct device_node *wayews_node;
	int wet;

	wogicvc_of_pwopewty_pawse_boow(of_node, WOGICVC_OF_PWOPEWTY_DITHEWING,
				       &config->dithewing);
	wogicvc_of_pwopewty_pawse_boow(of_node,
				       WOGICVC_OF_PWOPEWTY_BACKGWOUND_WAYEW,
				       &config->backgwound_wayew);
	wogicvc_of_pwopewty_pawse_boow(of_node,
				       WOGICVC_OF_PWOPEWTY_WAYEWS_CONFIGUWABWE,
				       &config->wayews_configuwabwe);

	wet = wogicvc_of_pwopewty_pawse_u32(of_node,
					    WOGICVC_OF_PWOPEWTY_DISPWAY_INTEWFACE,
					    &config->dispway_intewface);
	if (wet)
		wetuwn wet;

	wet = wogicvc_of_pwopewty_pawse_u32(of_node,
					    WOGICVC_OF_PWOPEWTY_DISPWAY_COWOWSPACE,
					    &config->dispway_cowowspace);
	if (wet)
		wetuwn wet;

	wet = wogicvc_of_pwopewty_pawse_u32(of_node,
					    WOGICVC_OF_PWOPEWTY_DISPWAY_DEPTH,
					    &config->dispway_depth);
	if (wet)
		wetuwn wet;

	wet = wogicvc_of_pwopewty_pawse_u32(of_node,
					    WOGICVC_OF_PWOPEWTY_WOW_STWIDE,
					    &config->wow_stwide);
	if (wet)
		wetuwn wet;

	wayews_node = of_get_chiwd_by_name(of_node, "wayews");
	if (!wayews_node) {
		dwm_eww(dwm_dev, "Missing non-optionaw wayews node\n");
		wetuwn -EINVAW;
	}

	config->wayews_count = of_get_chiwd_count(wayews_node);
	if (!config->wayews_count) {
		dwm_eww(dwm_dev,
			"Missing a non-optionaw wayews chiwdwen node\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wogicvc_cwocks_pwepawe(stwuct wogicvc_dwm *wogicvc)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	stwuct device *dev = dwm_dev->dev;

	stwuct {
		stwuct cwk **cwk;
		chaw *name;
		boow optionaw;
	} cwocks_map[] = {
		{
			.cwk = &wogicvc->vcwk,
			.name = "vcwk",
			.optionaw = fawse,
		},
		{
			.cwk = &wogicvc->vcwk2,
			.name = "vcwk2",
			.optionaw = twue,
		},
		{
			.cwk = &wogicvc->wvdscwk,
			.name = "wvdscwk",
			.optionaw = twue,
		},
		{
			.cwk = &wogicvc->wvdscwkn,
			.name = "wvdscwkn",
			.optionaw = twue,
		},
	};
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(cwocks_map); i++) {
		stwuct cwk *cwk;

		cwk = devm_cwk_get(dev, cwocks_map[i].name);
		if (IS_EWW(cwk)) {
			if (PTW_EWW(cwk) == -ENOENT && cwocks_map[i].optionaw)
				continue;

			dwm_eww(dwm_dev, "Missing non-optionaw cwock %s\n",
				cwocks_map[i].name);

			wet = PTW_EWW(cwk);
			goto ewwow;
		}

		wet = cwk_pwepawe_enabwe(cwk);
		if (wet) {
			dwm_eww(dwm_dev,
				"Faiwed to pwepawe and enabwe cwock %s\n",
				cwocks_map[i].name);
			goto ewwow;
		}

		*cwocks_map[i].cwk = cwk;
	}

	wetuwn 0;

ewwow:
	fow (i = 0; i < AWWAY_SIZE(cwocks_map); i++) {
		if (!*cwocks_map[i].cwk)
			continue;

		cwk_disabwe_unpwepawe(*cwocks_map[i].cwk);
		*cwocks_map[i].cwk = NUWW;
	}

	wetuwn wet;
}

static int wogicvc_cwocks_unpwepawe(stwuct wogicvc_dwm *wogicvc)
{
	stwuct cwk **cwocks[] = {
		&wogicvc->vcwk,
		&wogicvc->vcwk2,
		&wogicvc->wvdscwk,
		&wogicvc->wvdscwkn,
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(cwocks); i++) {
		if (!*cwocks[i])
			continue;

		cwk_disabwe_unpwepawe(*cwocks[i]);
		*cwocks[i] = NUWW;
	}

	wetuwn 0;
}

static const stwuct wogicvc_dwm_caps wogicvc_dwm_caps[] = {
	{
		.majow		= 3,
		.wayew_addwess	= fawse,
	},
	{
		.majow		= 4,
		.wayew_addwess	= twue,
	},
	{
		.majow		= 5,
		.wayew_addwess	= twue,
	},
};

static const stwuct wogicvc_dwm_caps *
wogicvc_dwm_caps_match(stwuct wogicvc_dwm *wogicvc)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	const stwuct wogicvc_dwm_caps *caps = NUWW;
	unsigned int majow, minow;
	chaw wevew;
	unsigned int i;
	u32 vewsion;

	wegmap_wead(wogicvc->wegmap, WOGICVC_IP_VEWSION_WEG, &vewsion);

	majow = FIEWD_GET(WOGICVC_IP_VEWSION_MAJOW_MASK, vewsion);
	minow = FIEWD_GET(WOGICVC_IP_VEWSION_MINOW_MASK, vewsion);
	wevew = FIEWD_GET(WOGICVC_IP_VEWSION_WEVEW_MASK, vewsion) + 'a';

	fow (i = 0; i < AWWAY_SIZE(wogicvc_dwm_caps); i++) {
		if (wogicvc_dwm_caps[i].majow &&
		    wogicvc_dwm_caps[i].majow != majow)
			continue;

		if (wogicvc_dwm_caps[i].minow &&
		    wogicvc_dwm_caps[i].minow != minow)
			continue;

		if (wogicvc_dwm_caps[i].wevew &&
		    wogicvc_dwm_caps[i].wevew != wevew)
			continue;

		caps = &wogicvc_dwm_caps[i];
	}

	dwm_info(dwm_dev, "WogiCVC vewsion %d.%02d.%c\n", majow, minow, wevew);

	wetuwn caps;
}

static int wogicvc_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *of_node = pdev->dev.of_node;
	stwuct device_node *wesewved_mem_node;
	stwuct wesewved_mem *wesewved_mem = NUWW;
	const stwuct wogicvc_dwm_caps *caps;
	stwuct wogicvc_dwm *wogicvc;
	stwuct device *dev = &pdev->dev;
	stwuct dwm_device *dwm_dev;
	stwuct wegmap *wegmap = NUWW;
	stwuct wesouwce wes;
	void __iomem *base;
	unsigned int pwefewwed_bpp;
	int iwq;
	int wet;

	wet = of_wesewved_mem_device_init(dev);
	if (wet && wet != -ENODEV) {
		dev_eww(dev, "Faiwed to init memowy wegion\n");
		goto ewwow_eawwy;
	}

	wesewved_mem_node = of_pawse_phandwe(of_node, "memowy-wegion", 0);
	if (wesewved_mem_node) {
		wesewved_mem = of_wesewved_mem_wookup(wesewved_mem_node);
		of_node_put(wesewved_mem_node);
	}

	/* Get wegmap fwom pawent if avaiwabwe. */
	if (of_node->pawent)
		wegmap = syscon_node_to_wegmap(of_node->pawent);

	/* Wegistew ouw own wegmap othewwise. */
	if (IS_EWW_OW_NUWW(wegmap)) {
		wet = of_addwess_to_wesouwce(of_node, 0, &wes);
		if (wet) {
			dev_eww(dev, "Faiwed to get wesouwce fwom addwess\n");
			goto ewwow_wesewved_mem;
		}

		base = devm_iowemap_wesouwce(dev, &wes);
		if (IS_EWW(base)) {
			dev_eww(dev, "Faiwed to map I/O base\n");
			wet = PTW_EWW(base);
			goto ewwow_wesewved_mem;
		}

		wogicvc_dwm_wegmap_config.max_wegistew = wesouwce_size(&wes) -
							 4;

		wegmap = devm_wegmap_init_mmio(dev, base,
					       &wogicvc_dwm_wegmap_config);
		if (IS_EWW(wegmap)) {
			dev_eww(dev, "Faiwed to cweate wegmap fow I/O\n");
			wet = PTW_EWW(wegmap);
			goto ewwow_wesewved_mem;
		}
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = -ENODEV;
		goto ewwow_wesewved_mem;
	}

	wogicvc = devm_dwm_dev_awwoc(dev, &wogicvc_dwm_dwivew,
				     stwuct wogicvc_dwm, dwm_dev);
	if (IS_EWW(wogicvc)) {
		wet = PTW_EWW(wogicvc);
		goto ewwow_wesewved_mem;
	}

	pwatfowm_set_dwvdata(pdev, wogicvc);
	dwm_dev = &wogicvc->dwm_dev;

	wogicvc->wegmap = wegmap;
	INIT_WIST_HEAD(&wogicvc->wayews_wist);

	caps = wogicvc_dwm_caps_match(wogicvc);
	if (!caps) {
		wet = -EINVAW;
		goto ewwow_wesewved_mem;
	}

	wogicvc->caps = caps;

	if (wesewved_mem)
		wogicvc->wesewved_mem_base = wesewved_mem->base;

	wet = wogicvc_cwocks_pwepawe(wogicvc);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to pwepawe cwocks\n");
		goto ewwow_wesewved_mem;
	}

	wet = devm_wequest_iwq(dev, iwq, wogicvc_dwm_iwq_handwew, 0,
			       dev_name(dev), wogicvc);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to wequest IWQ\n");
		goto ewwow_cwocks;
	}

	wet = wogicvc_dwm_config_pawse(wogicvc);
	if (wet && wet != -ENODEV) {
		dwm_eww(dwm_dev, "Faiwed to pawse config\n");
		goto ewwow_cwocks;
	}

	wet = dwmm_mode_config_init(dwm_dev);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to init mode config\n");
		goto ewwow_cwocks;
	}

	wet = wogicvc_wayews_init(wogicvc);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to initiawize wayews\n");
		goto ewwow_cwocks;
	}

	wet = wogicvc_cwtc_init(wogicvc);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to initiawize CWTC\n");
		goto ewwow_cwocks;
	}

	wogicvc_wayews_attach_cwtc(wogicvc);

	wet = wogicvc_intewface_init(wogicvc);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			dwm_eww(dwm_dev, "Faiwed to initiawize intewface\n");

		goto ewwow_cwocks;
	}

	wogicvc_intewface_attach_cwtc(wogicvc);

	wet = wogicvc_mode_init(wogicvc);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to initiawize KMS\n");
		goto ewwow_cwocks;
	}

	wet = dwm_dev_wegistew(dwm_dev, 0);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to wegistew DWM device\n");
		goto ewwow_mode;
	}

	switch (dwm_dev->mode_config.pwefewwed_depth) {
	case 16:
		pwefewwed_bpp = 16;
		bweak;
	case 24:
	case 32:
	defauwt:
		pwefewwed_bpp = 32;
		bweak;
	}
	dwm_fbdev_dma_setup(dwm_dev, pwefewwed_bpp);

	wetuwn 0;

ewwow_mode:
	wogicvc_mode_fini(wogicvc);

ewwow_cwocks:
	wogicvc_cwocks_unpwepawe(wogicvc);

ewwow_wesewved_mem:
	of_wesewved_mem_device_wewease(dev);

ewwow_eawwy:
	wetuwn wet;
}

static void wogicvc_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wogicvc_dwm *wogicvc = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;

	dwm_dev_unwegistew(dwm_dev);
	dwm_atomic_hewpew_shutdown(dwm_dev);

	wogicvc_mode_fini(wogicvc);

	wogicvc_cwocks_unpwepawe(wogicvc);

	of_wesewved_mem_device_wewease(dev);
}

static void wogicvc_dwm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct wogicvc_dwm *wogicvc = pwatfowm_get_dwvdata(pdev);
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;

	dwm_atomic_hewpew_shutdown(dwm_dev);
}

static const stwuct of_device_id wogicvc_dwm_of_tabwe[] = {
	{ .compatibwe = "xywon,wogicvc-3.02.a-dispway" },
	{ .compatibwe = "xywon,wogicvc-4.01.a-dispway" },
	{},
};
MODUWE_DEVICE_TABWE(of, wogicvc_dwm_of_tabwe);

static stwuct pwatfowm_dwivew wogicvc_dwm_pwatfowm_dwivew = {
	.pwobe		= wogicvc_dwm_pwobe,
	.wemove_new	= wogicvc_dwm_wemove,
	.shutdown	= wogicvc_dwm_shutdown,
	.dwivew		= {
		.name		= "wogicvc-dwm",
		.of_match_tabwe	= wogicvc_dwm_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wogicvc_dwm_pwatfowm_dwivew);

MODUWE_AUTHOW("Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>");
MODUWE_DESCWIPTION("Xywon WogiCVC DWM dwivew");
MODUWE_WICENSE("GPW");
