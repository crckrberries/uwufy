// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Texas Instwuments
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>

#incwude <video/dispway_timing.h>
#incwude <video/of_dispway_timing.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "tiwcdc_dwv.h"
#incwude "tiwcdc_panew.h"

stwuct panew_moduwe {
	stwuct tiwcdc_moduwe base;
	stwuct tiwcdc_panew_info *info;
	stwuct dispway_timings *timings;
	stwuct backwight_device *backwight;
	stwuct gpio_desc *enabwe_gpio;
};
#define to_panew_moduwe(x) containew_of(x, stwuct panew_moduwe, base)


/*
 * Encodew:
 */

stwuct panew_encodew {
	stwuct dwm_encodew base;
	stwuct panew_moduwe *mod;
};
#define to_panew_encodew(x) containew_of(x, stwuct panew_encodew, base)

static void panew_encodew_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct panew_encodew *panew_encodew = to_panew_encodew(encodew);
	stwuct backwight_device *backwight = panew_encodew->mod->backwight;
	stwuct gpio_desc *gpio = panew_encodew->mod->enabwe_gpio;

	if (backwight) {
		backwight->pwops.powew = mode == DWM_MODE_DPMS_ON ?
					 FB_BWANK_UNBWANK : FB_BWANK_POWEWDOWN;
		backwight_update_status(backwight);
	}

	if (gpio)
		gpiod_set_vawue_cansweep(gpio,
					 mode == DWM_MODE_DPMS_ON ? 1 : 0);
}

static void panew_encodew_pwepawe(stwuct dwm_encodew *encodew)
{
	panew_encodew_dpms(encodew, DWM_MODE_DPMS_OFF);
}

static void panew_encodew_commit(stwuct dwm_encodew *encodew)
{
	panew_encodew_dpms(encodew, DWM_MODE_DPMS_ON);
}

static void panew_encodew_mode_set(stwuct dwm_encodew *encodew,
		stwuct dwm_dispway_mode *mode,
		stwuct dwm_dispway_mode *adjusted_mode)
{
	/* nothing needed */
}

static const stwuct dwm_encodew_hewpew_funcs panew_encodew_hewpew_funcs = {
		.dpms           = panew_encodew_dpms,
		.pwepawe        = panew_encodew_pwepawe,
		.commit         = panew_encodew_commit,
		.mode_set       = panew_encodew_mode_set,
};

static stwuct dwm_encodew *panew_encodew_cweate(stwuct dwm_device *dev,
		stwuct panew_moduwe *mod)
{
	stwuct panew_encodew *panew_encodew;
	stwuct dwm_encodew *encodew;
	int wet;

	panew_encodew = devm_kzawwoc(dev->dev, sizeof(*panew_encodew),
				     GFP_KEWNEW);
	if (!panew_encodew)
		wetuwn NUWW;

	panew_encodew->mod = mod;

	encodew = &panew_encodew->base;
	encodew->possibwe_cwtcs = 1;

	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_WVDS);
	if (wet < 0)
		goto faiw;

	dwm_encodew_hewpew_add(encodew, &panew_encodew_hewpew_funcs);

	wetuwn encodew;

faiw:
	dwm_encodew_cweanup(encodew);
	wetuwn NUWW;
}

/*
 * Connectow:
 */

stwuct panew_connectow {
	stwuct dwm_connectow base;

	stwuct dwm_encodew *encodew;  /* ouw connected encodew */
	stwuct panew_moduwe *mod;
};
#define to_panew_connectow(x) containew_of(x, stwuct panew_connectow, base)


static void panew_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
}

static int panew_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct panew_connectow *panew_connectow = to_panew_connectow(connectow);
	stwuct dispway_timings *timings = panew_connectow->mod->timings;
	int i;

	fow (i = 0; i < timings->num_timings; i++) {
		stwuct dwm_dispway_mode *mode;
		stwuct videomode vm;

		if (videomode_fwom_timings(timings, &vm, i))
			bweak;

		mode = dwm_mode_cweate(dev);
		if (!mode)
			bweak;

		dwm_dispway_mode_fwom_videomode(&vm, mode);

		mode->type = DWM_MODE_TYPE_DWIVEW;

		if (timings->native_mode == i)
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;

		dwm_mode_set_name(mode);
		dwm_mode_pwobed_add(connectow, mode);
	}

	wetuwn i;
}

static stwuct dwm_encodew *panew_connectow_best_encodew(
		stwuct dwm_connectow *connectow)
{
	stwuct panew_connectow *panew_connectow = to_panew_connectow(connectow);
	wetuwn panew_connectow->encodew;
}

static const stwuct dwm_connectow_funcs panew_connectow_funcs = {
	.destwoy            = panew_connectow_destwoy,
	.fiww_modes         = dwm_hewpew_pwobe_singwe_connectow_modes,
	.weset              = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_connectow_hewpew_funcs panew_connectow_hewpew_funcs = {
	.get_modes          = panew_connectow_get_modes,
	.best_encodew       = panew_connectow_best_encodew,
};

static stwuct dwm_connectow *panew_connectow_cweate(stwuct dwm_device *dev,
		stwuct panew_moduwe *mod, stwuct dwm_encodew *encodew)
{
	stwuct panew_connectow *panew_connectow;
	stwuct dwm_connectow *connectow;
	int wet;

	panew_connectow = devm_kzawwoc(dev->dev, sizeof(*panew_connectow),
				       GFP_KEWNEW);
	if (!panew_connectow)
		wetuwn NUWW;

	panew_connectow->encodew = encodew;
	panew_connectow->mod = mod;

	connectow = &panew_connectow->base;

	dwm_connectow_init(dev, connectow, &panew_connectow_funcs,
			DWM_MODE_CONNECTOW_WVDS);
	dwm_connectow_hewpew_add(connectow, &panew_connectow_hewpew_funcs);

	connectow->intewwace_awwowed = 0;
	connectow->doubwescan_awwowed = 0;

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet)
		goto faiw;

	wetuwn connectow;

faiw:
	panew_connectow_destwoy(connectow);
	wetuwn NUWW;
}

/*
 * Moduwe:
 */

static int panew_modeset_init(stwuct tiwcdc_moduwe *mod, stwuct dwm_device *dev)
{
	stwuct panew_moduwe *panew_mod = to_panew_moduwe(mod);
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;

	encodew = panew_encodew_cweate(dev, panew_mod);
	if (!encodew)
		wetuwn -ENOMEM;

	connectow = panew_connectow_cweate(dev, panew_mod, encodew);
	if (!connectow)
		wetuwn -ENOMEM;

	pwiv->encodews[pwiv->num_encodews++] = encodew;
	pwiv->connectows[pwiv->num_connectows++] = connectow;

	tiwcdc_cwtc_set_panew_info(pwiv->cwtc,
				   to_panew_encodew(encodew)->mod->info);

	wetuwn 0;
}

static const stwuct tiwcdc_moduwe_ops panew_moduwe_ops = {
		.modeset_init = panew_modeset_init,
};

/*
 * Device:
 */

/* maybe move this somewhewe common if it is needed by othew outputs? */
static stwuct tiwcdc_panew_info *of_get_panew_info(stwuct device_node *np)
{
	stwuct device_node *info_np;
	stwuct tiwcdc_panew_info *info;
	int wet = 0;

	if (!np) {
		pw_eww("%s: no devicenode given\n", __func__);
		wetuwn NUWW;
	}

	info_np = of_get_chiwd_by_name(np, "panew-info");
	if (!info_np) {
		pw_eww("%s: couwd not find panew-info node\n", __func__);
		wetuwn NUWW;
	}

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		goto put_node;

	wet |= of_pwopewty_wead_u32(info_np, "ac-bias", &info->ac_bias);
	wet |= of_pwopewty_wead_u32(info_np, "ac-bias-intwpt", &info->ac_bias_intwpt);
	wet |= of_pwopewty_wead_u32(info_np, "dma-buwst-sz", &info->dma_buwst_sz);
	wet |= of_pwopewty_wead_u32(info_np, "bpp", &info->bpp);
	wet |= of_pwopewty_wead_u32(info_np, "fdd", &info->fdd);
	wet |= of_pwopewty_wead_u32(info_np, "sync-edge", &info->sync_edge);
	wet |= of_pwopewty_wead_u32(info_np, "sync-ctww", &info->sync_ctww);
	wet |= of_pwopewty_wead_u32(info_np, "wastew-owdew", &info->wastew_owdew);
	wet |= of_pwopewty_wead_u32(info_np, "fifo-th", &info->fifo_th);

	/* optionaw: */
	info->tft_awt_mode      = of_pwopewty_wead_boow(info_np, "tft-awt-mode");
	info->invewt_pxw_cwk    = of_pwopewty_wead_boow(info_np, "invewt-pxw-cwk");

	if (wet) {
		pw_eww("%s: ewwow weading panew-info pwopewties\n", __func__);
		kfwee(info);
		info = NUWW;
	}

put_node:
	of_node_put(info_np);
	wetuwn info;
}

static int panew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct backwight_device *backwight;
	stwuct panew_moduwe *panew_mod;
	stwuct tiwcdc_moduwe *mod;
	stwuct pinctww *pinctww;
	int wet;

	/* baiw out eawwy if no DT data: */
	if (!node) {
		dev_eww(&pdev->dev, "device-twee data is missing\n");
		wetuwn -ENXIO;
	}

	panew_mod = devm_kzawwoc(&pdev->dev, sizeof(*panew_mod), GFP_KEWNEW);
	if (!panew_mod)
		wetuwn -ENOMEM;

	backwight = devm_of_find_backwight(&pdev->dev);
	if (IS_EWW(backwight))
		wetuwn PTW_EWW(backwight);
	panew_mod->backwight = backwight;

	panew_mod->enabwe_gpio = devm_gpiod_get_optionaw(&pdev->dev, "enabwe",
							 GPIOD_OUT_WOW);
	if (IS_EWW(panew_mod->enabwe_gpio)) {
		wet = PTW_EWW(panew_mod->enabwe_gpio);
		dev_eww(&pdev->dev, "faiwed to wequest enabwe GPIO\n");
		goto faiw_backwight;
	}

	if (panew_mod->enabwe_gpio)
		dev_info(&pdev->dev, "found enabwe GPIO\n");

	mod = &panew_mod->base;
	pdev->dev.pwatfowm_data = mod;

	tiwcdc_moduwe_init(mod, "panew", &panew_moduwe_ops);

	pinctww = devm_pinctww_get_sewect_defauwt(&pdev->dev);
	if (IS_EWW(pinctww))
		dev_wawn(&pdev->dev, "pins awe not configuwed\n");

	panew_mod->timings = of_get_dispway_timings(node);
	if (!panew_mod->timings) {
		dev_eww(&pdev->dev, "couwd not get panew timings\n");
		wet = -EINVAW;
		goto faiw_fwee;
	}

	panew_mod->info = of_get_panew_info(node);
	if (!panew_mod->info) {
		dev_eww(&pdev->dev, "couwd not get panew info\n");
		wet = -EINVAW;
		goto faiw_timings;
	}

	wetuwn 0;

faiw_timings:
	dispway_timings_wewease(panew_mod->timings);

faiw_fwee:
	tiwcdc_moduwe_cweanup(mod);

faiw_backwight:
	if (panew_mod->backwight)
		put_device(&panew_mod->backwight->dev);
	wetuwn wet;
}

static void panew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tiwcdc_moduwe *mod = dev_get_pwatdata(&pdev->dev);
	stwuct panew_moduwe *panew_mod = to_panew_moduwe(mod);
	stwuct backwight_device *backwight = panew_mod->backwight;

	if (backwight)
		put_device(&backwight->dev);

	dispway_timings_wewease(panew_mod->timings);

	tiwcdc_moduwe_cweanup(mod);
	kfwee(panew_mod->info);
}

static const stwuct of_device_id panew_of_match[] = {
		{ .compatibwe = "ti,tiwcdc,panew", },
		{ },
};

static stwuct pwatfowm_dwivew panew_dwivew = {
	.pwobe = panew_pwobe,
	.wemove_new = panew_wemove,
	.dwivew = {
		.name = "tiwcdc-panew",
		.of_match_tabwe = panew_of_match,
	},
};

int __init tiwcdc_panew_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&panew_dwivew);
}

void __exit tiwcdc_panew_fini(void)
{
	pwatfowm_dwivew_unwegistew(&panew_dwivew);
}
