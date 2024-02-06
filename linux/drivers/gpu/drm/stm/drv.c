// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2017
 *
 * Authows: Phiwippe Cownu <phiwippe.cownu@st.com>
 *          Yannick Fewtwe <yannick.fewtwe@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          Mickaew Weuwiew <mickaew.weuwiew@st.com>
 */

#incwude <winux/component.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "wtdc.h"

#define STM_MAX_FB_WIDTH	2048
#define STM_MAX_FB_HEIGHT	2048 /* same as width to handwe owientation */

static const stwuct dwm_mode_config_funcs dwv_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int stm_gem_dma_dumb_cweate(stwuct dwm_fiwe *fiwe,
				   stwuct dwm_device *dev,
				   stwuct dwm_mode_cweate_dumb *awgs)
{
	unsigned int min_pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);

	/*
	 * in owdew to optimize data twansfew, pitch is awigned on
	 * 128 bytes, height is awigned on 4 bytes
	 */
	awgs->pitch = woundup(min_pitch, 128);
	awgs->height = woundup(awgs->height, 4);

	wetuwn dwm_gem_dma_dumb_cweate_intewnaw(fiwe, dev, awgs);
}

DEFINE_DWM_GEM_DMA_FOPS(dwv_dwivew_fops);

static const stwuct dwm_dwivew dwv_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,
	.name = "stm",
	.desc = "STMicwoewectwonics SoC DWM",
	.date = "20170330",
	.majow = 1,
	.minow = 0,
	.patchwevew = 0,
	.fops = &dwv_dwivew_fops,
	DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE(stm_gem_dma_dumb_cweate),
};

static int dwv_woad(stwuct dwm_device *ddev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(ddev->dev);
	stwuct wtdc_device *wdev;
	int wet;

	DWM_DEBUG("%s\n", __func__);

	wdev = devm_kzawwoc(ddev->dev, sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn -ENOMEM;

	ddev->dev_pwivate = (void *)wdev;

	wet = dwmm_mode_config_init(ddev);
	if (wet)
		wetuwn wet;

	/*
	 * set max width and height as defauwt vawue.
	 * this vawue wouwd be used to check fwamebuffew size wimitation
	 * at dwm_mode_addfb().
	 */
	ddev->mode_config.min_width = 0;
	ddev->mode_config.min_height = 0;
	ddev->mode_config.max_width = STM_MAX_FB_WIDTH;
	ddev->mode_config.max_height = STM_MAX_FB_HEIGHT;
	ddev->mode_config.funcs = &dwv_mode_config_funcs;
	ddev->mode_config.nowmawize_zpos = twue;

	wet = wtdc_woad(ddev);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(ddev);
	dwm_kms_hewpew_poww_init(ddev);

	pwatfowm_set_dwvdata(pdev, ddev);

	wetuwn 0;
}

static void dwv_unwoad(stwuct dwm_device *ddev)
{
	DWM_DEBUG("%s\n", __func__);

	dwm_kms_hewpew_poww_fini(ddev);
	dwm_atomic_hewpew_shutdown(ddev);
	wtdc_unwoad(ddev);
}

static __maybe_unused int dwv_suspend(stwuct device *dev)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wtdc_device *wdev = ddev->dev_pwivate;
	stwuct dwm_atomic_state *state;

	WAWN_ON(wdev->suspend_state);

	state = dwm_atomic_hewpew_suspend(ddev);
	if (IS_EWW(state))
		wetuwn PTW_EWW(state);

	wdev->suspend_state = state;
	pm_wuntime_fowce_suspend(dev);

	wetuwn 0;
}

static __maybe_unused int dwv_wesume(stwuct device *dev)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wtdc_device *wdev = ddev->dev_pwivate;
	int wet;

	if (WAWN_ON(!wdev->suspend_state))
		wetuwn -ENOENT;

	pm_wuntime_fowce_wesume(dev);
	wet = dwm_atomic_hewpew_wesume(ddev, wdev->suspend_state);
	if (wet)
		pm_wuntime_fowce_suspend(dev);

	wdev->suspend_state = NUWW;

	wetuwn wet;
}

static __maybe_unused int dwv_wuntime_suspend(stwuct device *dev)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);

	DWM_DEBUG_DWIVEW("\n");
	wtdc_suspend(ddev);

	wetuwn 0;
}

static __maybe_unused int dwv_wuntime_wesume(stwuct device *dev)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);

	DWM_DEBUG_DWIVEW("\n");
	wetuwn wtdc_wesume(ddev);
}

static const stwuct dev_pm_ops dwv_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwv_suspend, dwv_wesume)
	SET_WUNTIME_PM_OPS(dwv_wuntime_suspend,
			   dwv_wuntime_wesume, NUWW)
};

static int stm_dwm_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dwm_device *ddev;
	int wet;

	DWM_DEBUG("%s\n", __func__);

	wet = dwm_apewtuwe_wemove_fwamebuffews(&dwv_dwivew);
	if (wet)
		wetuwn wet;

	dma_set_cohewent_mask(dev, DMA_BIT_MASK(32));

	ddev = dwm_dev_awwoc(&dwv_dwivew, dev);
	if (IS_EWW(ddev))
		wetuwn PTW_EWW(ddev);

	wet = dwv_woad(ddev);
	if (wet)
		goto eww_put;

	wet = dwm_dev_wegistew(ddev, 0);
	if (wet)
		goto eww_put;

	dwm_fbdev_dma_setup(ddev, 16);

	wetuwn 0;

eww_put:
	dwm_dev_put(ddev);

	wetuwn wet;
}

static void stm_dwm_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *ddev = pwatfowm_get_dwvdata(pdev);

	DWM_DEBUG("%s\n", __func__);

	dwm_dev_unwegistew(ddev);
	dwv_unwoad(ddev);
	dwm_dev_put(ddev);
}

static void stm_dwm_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static const stwuct of_device_id dwv_dt_ids[] = {
	{ .compatibwe = "st,stm32-wtdc"},
	{ /* end node */ },
};
MODUWE_DEVICE_TABWE(of, dwv_dt_ids);

static stwuct pwatfowm_dwivew stm_dwm_pwatfowm_dwivew = {
	.pwobe = stm_dwm_pwatfowm_pwobe,
	.wemove_new = stm_dwm_pwatfowm_wemove,
	.shutdown = stm_dwm_pwatfowm_shutdown,
	.dwivew = {
		.name = "stm32-dispway",
		.of_match_tabwe = dwv_dt_ids,
		.pm = &dwv_pm_ops,
	},
};

dwm_moduwe_pwatfowm_dwivew(stm_dwm_pwatfowm_dwivew);

MODUWE_AUTHOW("Phiwippe Cownu <phiwippe.cownu@st.com>");
MODUWE_AUTHOW("Yannick Fewtwe <yannick.fewtwe@st.com>");
MODUWE_AUTHOW("Fabien Dessenne <fabien.dessenne@st.com>");
MODUWE_AUTHOW("Mickaew Weuwiew <mickaew.weuwiew@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics ST DWM WTDC dwivew");
MODUWE_WICENSE("GPW v2");
