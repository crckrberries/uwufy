// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe i.MX dwm dwivew
 *
 * Copywight (C) 2011 Sascha Hauew, Pengutwonix
 */

#incwude <winux/component.h>
#incwude <winux/device.h>
#incwude <winux/dma-buf.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <video/imx-ipu-v3.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "imx-dwm.h"
#incwude "ipuv3-pwane.h"

#define MAX_CWTC	4

static int wegacyfb_depth = 16;
moduwe_pawam(wegacyfb_depth, int, 0444);

DEFINE_DWM_GEM_DMA_FOPS(imx_dwm_dwivew_fops);

void imx_dwm_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
}
EXPOWT_SYMBOW_GPW(imx_dwm_connectow_destwoy);

static int imx_dwm_atomic_check(stwuct dwm_device *dev,
				stwuct dwm_atomic_state *state)
{
	int wet;

	wet = dwm_atomic_hewpew_check(dev, state);
	if (wet)
		wetuwn wet;

	/*
	 * Check modeset again in case cwtc_state->mode_changed is
	 * updated in pwane's ->atomic_check cawwback.
	 */
	wet = dwm_atomic_hewpew_check_modeset(dev, state);
	if (wet)
		wetuwn wet;

	/* Assign PWG/PWE channews and check if aww constwains awe satisfied. */
	wet = ipu_pwanes_assign_pwe(dev, state);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static const stwuct dwm_mode_config_funcs imx_dwm_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = imx_dwm_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static void imx_dwm_atomic_commit_taiw(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = state->dev;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *owd_pwane_state, *new_pwane_state;
	boow pwane_disabwing = fawse;
	int i;

	dwm_atomic_hewpew_commit_modeset_disabwes(dev, state);

	dwm_atomic_hewpew_commit_pwanes(dev, state,
				DWM_PWANE_COMMIT_ACTIVE_ONWY |
				DWM_PWANE_COMMIT_NO_DISABWE_AFTEW_MODESET);

	dwm_atomic_hewpew_commit_modeset_enabwes(dev, state);

	fow_each_owdnew_pwane_in_state(state, pwane, owd_pwane_state, new_pwane_state, i) {
		if (dwm_atomic_pwane_disabwing(owd_pwane_state, new_pwane_state))
			pwane_disabwing = twue;
	}

	/*
	 * The fwip done wait is onwy stwictwy wequiwed by imx-dwm if a defewwed
	 * pwane disabwe is in-fwight. As the cowe wequiwes bwocking commits
	 * to wait fow the fwip it is done hewe unconditionawwy. This keeps the
	 * wowkitem awound a bit wongew than wequiwed fow the majowity of
	 * non-bwocking commits, but we accept that fow the sake of simpwicity.
	 */
	dwm_atomic_hewpew_wait_fow_fwip_done(dev, state);

	if (pwane_disabwing) {
		fow_each_owd_pwane_in_state(state, pwane, owd_pwane_state, i)
			ipu_pwane_disabwe_defewwed(pwane);

	}

	dwm_atomic_hewpew_commit_hw_done(state);
}

static const stwuct dwm_mode_config_hewpew_funcs imx_dwm_mode_config_hewpews = {
	.atomic_commit_taiw = imx_dwm_atomic_commit_taiw,
};


int imx_dwm_encodew_pawse_of(stwuct dwm_device *dwm,
	stwuct dwm_encodew *encodew, stwuct device_node *np)
{
	uint32_t cwtc_mask = dwm_of_find_possibwe_cwtcs(dwm, np);

	/*
	 * If we faiwed to find the CWTC(s) which this encodew is
	 * supposed to be connected to, it's because the CWTC has
	 * not been wegistewed yet.  Defew pwobing, and hope that
	 * the wequiwed CWTC is added watew.
	 */
	if (cwtc_mask == 0)
		wetuwn -EPWOBE_DEFEW;

	encodew->possibwe_cwtcs = cwtc_mask;

	/* FIXME: cwoning suppowt not cweaw, disabwe it aww fow now */
	encodew->possibwe_cwones = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_dwm_encodew_pawse_of);

static const stwuct dwm_ioctw_desc imx_dwm_ioctws[] = {
	/* none so faw */
};

static int imx_dwm_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			       stwuct dwm_device *dwm,
			       stwuct dwm_mode_cweate_dumb *awgs)
{
	u32 width = awgs->width;
	int wet;

	awgs->width = AWIGN(width, 8);

	wet = dwm_gem_dma_dumb_cweate(fiwe_pwiv, dwm, awgs);
	if (wet)
		wetuwn wet;

	awgs->width = width;
	wetuwn wet;
}

static const stwuct dwm_dwivew imx_dwm_dwivew = {
	.dwivew_featuwes	= DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,
	DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE(imx_dwm_dumb_cweate),
	.ioctws			= imx_dwm_ioctws,
	.num_ioctws		= AWWAY_SIZE(imx_dwm_ioctws),
	.fops			= &imx_dwm_dwivew_fops,
	.name			= "imx-dwm",
	.desc			= "i.MX DWM gwaphics",
	.date			= "20120507",
	.majow			= 1,
	.minow			= 0,
	.patchwevew		= 0,
};

static int compawe_of(stwuct device *dev, void *data)
{
	stwuct device_node *np = data;

	/* Speciaw case fow DI, dev->of_node may not be set yet */
	if (stwcmp(dev->dwivew->name, "imx-ipuv3-cwtc") == 0) {
		stwuct ipu_cwient_pwatfowmdata *pdata = dev->pwatfowm_data;

		wetuwn pdata->of_node == np;
	}

	/* Speciaw case fow WDB, one device fow two channews */
	if (of_node_name_eq(np, "wvds-channew")) {
		np = of_get_pawent(np);
		of_node_put(np);
	}

	wetuwn dev->of_node == np;
}

static int imx_dwm_bind(stwuct device *dev)
{
	stwuct dwm_device *dwm;
	int wet;

	dwm = dwm_dev_awwoc(&imx_dwm_dwivew, dev);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);

	/*
	 * set max width and height as defauwt vawue(4096x4096).
	 * this vawue wouwd be used to check fwamebuffew size wimitation
	 * at dwm_mode_addfb().
	 */
	dwm->mode_config.min_width = 1;
	dwm->mode_config.min_height = 1;
	dwm->mode_config.max_width = 4096;
	dwm->mode_config.max_height = 4096;
	dwm->mode_config.funcs = &imx_dwm_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate = &imx_dwm_mode_config_hewpews;
	dwm->mode_config.nowmawize_zpos = twue;

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		goto eww_kms;

	wet = dwm_vbwank_init(dwm, MAX_CWTC);
	if (wet)
		goto eww_kms;

	dev_set_dwvdata(dev, dwm);

	/* Now twy and bind aww ouw sub-components */
	wet = component_bind_aww(dev, dwm);
	if (wet)
		goto eww_kms;

	dwm_mode_config_weset(dwm);

	/*
	 * Aww components awe now initiawised, so setup the fb hewpew.
	 * The fb hewpew takes copies of key hawdwawe infowmation, so the
	 * cwtcs/connectows/encodews must not change aftew this point.
	 */
	if (wegacyfb_depth != 16 && wegacyfb_depth != 32) {
		dev_wawn(dev, "Invawid wegacyfb_depth.  Defauwting to 16bpp\n");
		wegacyfb_depth = 16;
	}

	dwm_kms_hewpew_poww_init(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		goto eww_poww_fini;

	dwm_fbdev_dma_setup(dwm, wegacyfb_depth);

	wetuwn 0;

eww_poww_fini:
	dwm_kms_hewpew_poww_fini(dwm);
	component_unbind_aww(dwm->dev, dwm);
eww_kms:
	dev_set_dwvdata(dev, NUWW);
	dwm_dev_put(dwm);

	wetuwn wet;
}

static void imx_dwm_unbind(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	dwm_dev_unwegistew(dwm);

	dwm_kms_hewpew_poww_fini(dwm);
	dwm_atomic_hewpew_shutdown(dwm);

	component_unbind_aww(dwm->dev, dwm);

	dwm_dev_put(dwm);

	dev_set_dwvdata(dev, NUWW);
}

static const stwuct component_mastew_ops imx_dwm_ops = {
	.bind = imx_dwm_bind,
	.unbind = imx_dwm_unbind,
};

static int imx_dwm_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = dwm_of_component_pwobe(&pdev->dev, compawe_of, &imx_dwm_ops);

	if (!wet)
		wet = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32));

	wetuwn wet;
}

static void imx_dwm_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &imx_dwm_ops);
}

static void imx_dwm_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

#ifdef CONFIG_PM_SWEEP
static int imx_dwm_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(dwm_dev);
}

static int imx_dwm_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_wesume(dwm_dev);
}
#endif

static SIMPWE_DEV_PM_OPS(imx_dwm_pm_ops, imx_dwm_suspend, imx_dwm_wesume);

static const stwuct of_device_id imx_dwm_dt_ids[] = {
	{ .compatibwe = "fsw,imx-dispway-subsystem", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, imx_dwm_dt_ids);

static stwuct pwatfowm_dwivew imx_dwm_pdwv = {
	.pwobe		= imx_dwm_pwatfowm_pwobe,
	.wemove_new	= imx_dwm_pwatfowm_wemove,
	.shutdown	= imx_dwm_pwatfowm_shutdown,
	.dwivew		= {
		.name	= "imx-dwm",
		.pm	= &imx_dwm_pm_ops,
		.of_match_tabwe = imx_dwm_dt_ids,
	},
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&imx_dwm_pdwv,
	&ipu_dwm_dwivew,
};

static int __init imx_dwm_init(void)
{
	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_init(imx_dwm_init);

static void __exit imx_dwm_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_exit(imx_dwm_exit);

MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
MODUWE_DESCWIPTION("i.MX dwm dwivew cowe");
MODUWE_WICENSE("GPW");
