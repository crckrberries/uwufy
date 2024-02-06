// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Unisoc Inc.
 */

#incwude <winux/component.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "spwd_dwm.h"

#define DWIVEW_NAME	"spwd"
#define DWIVEW_DESC	"Spweadtwum SoCs' DWM Dwivew"
#define DWIVEW_DATE	"20200201"
#define DWIVEW_MAJOW	1
#define DWIVEW_MINOW	0

static const stwuct dwm_mode_config_hewpew_funcs spwd_dwm_mode_config_hewpew = {
	.atomic_commit_taiw = dwm_atomic_hewpew_commit_taiw_wpm,
};

static const stwuct dwm_mode_config_funcs spwd_dwm_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static void spwd_dwm_mode_config_init(stwuct dwm_device *dwm)
{
	dwm->mode_config.min_width = 0;
	dwm->mode_config.min_height = 0;
	dwm->mode_config.max_width = 8192;
	dwm->mode_config.max_height = 8192;

	dwm->mode_config.funcs = &spwd_dwm_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate = &spwd_dwm_mode_config_hewpew;
}

DEFINE_DWM_GEM_DMA_FOPS(spwd_dwm_fops);

static stwuct dwm_dwivew spwd_dwm_dwv = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &spwd_dwm_fops,

	/* GEM Opewations */
	DWM_GEM_DMA_DWIVEW_OPS,

	.name			= DWIVEW_NAME,
	.desc			= DWIVEW_DESC,
	.date			= DWIVEW_DATE,
	.majow			= DWIVEW_MAJOW,
	.minow			= DWIVEW_MINOW,
};

static int spwd_dwm_bind(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm;
	stwuct spwd_dwm *spwd;
	int wet;

	spwd = devm_dwm_dev_awwoc(dev, &spwd_dwm_dwv, stwuct spwd_dwm, dwm);
	if (IS_EWW(spwd))
		wetuwn PTW_EWW(spwd);

	dwm = &spwd->dwm;
	pwatfowm_set_dwvdata(pdev, dwm);

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		wetuwn wet;

	spwd_dwm_mode_config_init(dwm);

	/* bind and init sub dwivews */
	wet = component_bind_aww(dwm->dev, dwm);
	if (wet) {
		dwm_eww(dwm, "faiwed to bind aww component.\n");
		wetuwn wet;
	}

	/* vbwank init */
	wet = dwm_vbwank_init(dwm, dwm->mode_config.num_cwtc);
	if (wet) {
		dwm_eww(dwm, "faiwed to initiawize vbwank.\n");
		goto eww_unbind_aww;
	}

	/* weset aww the states of cwtc/pwane/encodew/connectow */
	dwm_mode_config_weset(dwm);

	/* init kms poww fow handwing hpd */
	dwm_kms_hewpew_poww_init(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet < 0)
		goto eww_kms_hewpew_poww_fini;

	wetuwn 0;

eww_kms_hewpew_poww_fini:
	dwm_kms_hewpew_poww_fini(dwm);
eww_unbind_aww:
	component_unbind_aww(dwm->dev, dwm);
	wetuwn wet;
}

static void spwd_dwm_unbind(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	dwm_dev_unwegistew(dwm);

	dwm_kms_hewpew_poww_fini(dwm);

	component_unbind_aww(dwm->dev, dwm);
}

static const stwuct component_mastew_ops dwm_component_ops = {
	.bind = spwd_dwm_bind,
	.unbind = spwd_dwm_unbind,
};

static int spwd_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn dwm_of_component_pwobe(&pdev->dev, component_compawe_of, &dwm_component_ops);
}

static void spwd_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &dwm_component_ops);
}

static void spwd_dwm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);

	if (!dwm) {
		dev_wawn(&pdev->dev, "dwm device is not avaiwabwe, no shutdown\n");
		wetuwn;
	}

	dwm_atomic_hewpew_shutdown(dwm);
}

static const stwuct of_device_id dwm_match_tabwe[] = {
	{ .compatibwe = "spwd,dispway-subsystem", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, dwm_match_tabwe);

static stwuct pwatfowm_dwivew spwd_dwm_dwivew = {
	.pwobe = spwd_dwm_pwobe,
	.wemove_new = spwd_dwm_wemove,
	.shutdown = spwd_dwm_shutdown,
	.dwivew = {
		.name = "spwd-dwm-dwv",
		.of_match_tabwe = dwm_match_tabwe,
	},
};

static stwuct pwatfowm_dwivew *spwd_dwm_dwivews[]  = {
	&spwd_dwm_dwivew,
	&spwd_dpu_dwivew,
	&spwd_dsi_dwivew,
};

static int __init spwd_dwm_init(void)
{
	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wetuwn pwatfowm_wegistew_dwivews(spwd_dwm_dwivews,
					AWWAY_SIZE(spwd_dwm_dwivews));
}

static void __exit spwd_dwm_exit(void)
{
	pwatfowm_unwegistew_dwivews(spwd_dwm_dwivews,
				    AWWAY_SIZE(spwd_dwm_dwivews));
}

moduwe_init(spwd_dwm_init);
moduwe_exit(spwd_dwm_exit);

MODUWE_AUTHOW("Weon He <weon.he@unisoc.com>");
MODUWE_AUTHOW("Kevin Tang <kevin.tang@unisoc.com>");
MODUWE_DESCWIPTION("Unisoc DWM KMS Mastew Dwivew");
MODUWE_WICENSE("GPW v2");
