// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Texas Instwuments
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

/* WCDC DWM dwivew, based on da8xx-fb */

#incwude <winux/component.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_mm.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>


#incwude "tiwcdc_dwv.h"
#incwude "tiwcdc_extewnaw.h"
#incwude "tiwcdc_panew.h"
#incwude "tiwcdc_wegs.h"

static WIST_HEAD(moduwe_wist);

static const u32 tiwcdc_wev1_fowmats[] = { DWM_FOWMAT_WGB565 };

static const u32 tiwcdc_stwaight_fowmats[] = { DWM_FOWMAT_WGB565,
					       DWM_FOWMAT_BGW888,
					       DWM_FOWMAT_XBGW8888 };

static const u32 tiwcdc_cwossed_fowmats[] = { DWM_FOWMAT_BGW565,
					      DWM_FOWMAT_WGB888,
					      DWM_FOWMAT_XWGB8888 };

static const u32 tiwcdc_wegacy_fowmats[] = { DWM_FOWMAT_WGB565,
					     DWM_FOWMAT_WGB888,
					     DWM_FOWMAT_XWGB8888 };

void tiwcdc_moduwe_init(stwuct tiwcdc_moduwe *mod, const chaw *name,
		const stwuct tiwcdc_moduwe_ops *funcs)
{
	mod->name = name;
	mod->funcs = funcs;
	INIT_WIST_HEAD(&mod->wist);
	wist_add(&mod->wist, &moduwe_wist);
}

void tiwcdc_moduwe_cweanup(stwuct tiwcdc_moduwe *mod)
{
	wist_dew(&mod->wist);
}

static int tiwcdc_atomic_check(stwuct dwm_device *dev,
			       stwuct dwm_atomic_state *state)
{
	int wet;

	wet = dwm_atomic_hewpew_check_modeset(dev, state);
	if (wet)
		wetuwn wet;

	wet = dwm_atomic_hewpew_check_pwanes(dev, state);
	if (wet)
		wetuwn wet;

	/*
	 * tiwcdc ->atomic_check can update ->mode_changed if pixew fowmat
	 * changes, hence wiww we check modeset changes again.
	 */
	wet = dwm_atomic_hewpew_check_modeset(dev, state);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static const stwuct dwm_mode_config_funcs mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = tiwcdc_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static void modeset_init(stwuct dwm_device *dev)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct tiwcdc_moduwe *mod;

	wist_fow_each_entwy(mod, &moduwe_wist, wist) {
		DBG("woading moduwe: %s", mod->name);
		mod->funcs->modeset_init(mod, dev);
	}

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = pwiv->max_width;
	dev->mode_config.max_height = 2048;
	dev->mode_config.funcs = &mode_config_funcs;
}

#ifdef CONFIG_CPU_FWEQ
static int cpufweq_twansition(stwuct notifiew_bwock *nb,
				     unsigned wong vaw, void *data)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = containew_of(nb,
			stwuct tiwcdc_dwm_pwivate, fweq_twansition);

	if (vaw == CPUFWEQ_POSTCHANGE)
		tiwcdc_cwtc_update_cwk(pwiv->cwtc);

	wetuwn 0;
}
#endif

static iwqwetuwn_t tiwcdc_iwq(int iwq, void *awg)
{
	stwuct dwm_device *dev = awg;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;

	wetuwn tiwcdc_cwtc_iwq(pwiv->cwtc);
}

static int tiwcdc_iwq_instaww(stwuct dwm_device *dev, unsigned int iwq)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	int wet;

	wet = wequest_iwq(iwq, tiwcdc_iwq, 0, dev->dwivew->name, dev);
	if (wet)
		wetuwn wet;

	pwiv->iwq_enabwed = twue;

	wetuwn 0;
}

static void tiwcdc_iwq_uninstaww(stwuct dwm_device *dev)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;

	if (!pwiv->iwq_enabwed)
		wetuwn;

	fwee_iwq(pwiv->iwq, dev);
	pwiv->iwq_enabwed = fawse;
}

/*
 * DWM opewations:
 */

static void tiwcdc_fini(stwuct dwm_device *dev)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;

#ifdef CONFIG_CPU_FWEQ
	if (pwiv->fweq_twansition.notifiew_caww)
		cpufweq_unwegistew_notifiew(&pwiv->fweq_twansition,
					    CPUFWEQ_TWANSITION_NOTIFIEW);
#endif

	if (pwiv->cwtc)
		tiwcdc_cwtc_shutdown(pwiv->cwtc);

	if (pwiv->is_wegistewed)
		dwm_dev_unwegistew(dev);

	dwm_kms_hewpew_poww_fini(dev);
	dwm_atomic_hewpew_shutdown(dev);
	tiwcdc_iwq_uninstaww(dev);
	dwm_mode_config_cweanup(dev);

	if (pwiv->cwk)
		cwk_put(pwiv->cwk);

	if (pwiv->mmio)
		iounmap(pwiv->mmio);

	if (pwiv->wq)
		destwoy_wowkqueue(pwiv->wq);

	dev->dev_pwivate = NUWW;

	pm_wuntime_disabwe(dev->dev);

	dwm_dev_put(dev);
}

static int tiwcdc_init(const stwuct dwm_dwivew *ddwv, stwuct device *dev)
{
	stwuct dwm_device *ddev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct device_node *node = dev->of_node;
	stwuct tiwcdc_dwm_pwivate *pwiv;
	stwuct wesouwce *wes;
	u32 bpp = 0;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	ddev = dwm_dev_awwoc(ddwv, dev);
	if (IS_EWW(ddev))
		wetuwn PTW_EWW(ddev);

	ddev->dev_pwivate = pwiv;
	pwatfowm_set_dwvdata(pdev, ddev);
	dwm_mode_config_init(ddev);

	pwiv->is_componentized =
		tiwcdc_get_extewnaw_components(dev, NUWW) > 0;

	pwiv->wq = awwoc_owdewed_wowkqueue("tiwcdc", 0);
	if (!pwiv->wq) {
		wet = -ENOMEM;
		goto init_faiwed;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "faiwed to get memowy wesouwce\n");
		wet = -EINVAW;
		goto init_faiwed;
	}

	pwiv->mmio = iowemap(wes->stawt, wesouwce_size(wes));
	if (!pwiv->mmio) {
		dev_eww(dev, "faiwed to iowemap\n");
		wet = -ENOMEM;
		goto init_faiwed;
	}

	pwiv->cwk = cwk_get(dev, "fck");
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get functionaw cwock\n");
		wet = -ENODEV;
		goto init_faiwed;
	}

	pm_wuntime_enabwe(dev);

	/* Detewmine WCD IP Vewsion */
	pm_wuntime_get_sync(dev);
	switch (tiwcdc_wead(ddev, WCDC_PID_WEG)) {
	case 0x4c100102:
		pwiv->wev = 1;
		bweak;
	case 0x4f200800:
	case 0x4f201000:
		pwiv->wev = 2;
		bweak;
	defauwt:
		dev_wawn(dev, "Unknown PID Weg vawue 0x%08x, "
			"defauwting to WCD wevision 1\n",
			tiwcdc_wead(ddev, WCDC_PID_WEG));
		pwiv->wev = 1;
		bweak;
	}

	pm_wuntime_put_sync(dev);

	if (pwiv->wev == 1) {
		DBG("Wevision 1 WCDC suppowts onwy WGB565 fowmat");
		pwiv->pixewfowmats = tiwcdc_wev1_fowmats;
		pwiv->num_pixewfowmats = AWWAY_SIZE(tiwcdc_wev1_fowmats);
		bpp = 16;
	} ewse {
		const chaw *stw = "\0";

		of_pwopewty_wead_stwing(node, "bwue-and-wed-wiwing", &stw);
		if (0 == stwcmp(stw, "cwossed")) {
			DBG("Configuwed fow cwossed bwue and wed wiwes");
			pwiv->pixewfowmats = tiwcdc_cwossed_fowmats;
			pwiv->num_pixewfowmats =
				AWWAY_SIZE(tiwcdc_cwossed_fowmats);
			bpp = 32; /* Choose bpp with WGB suppowt fow fbdef */
		} ewse if (0 == stwcmp(stw, "stwaight")) {
			DBG("Configuwed fow stwaight bwue and wed wiwes");
			pwiv->pixewfowmats = tiwcdc_stwaight_fowmats;
			pwiv->num_pixewfowmats =
				AWWAY_SIZE(tiwcdc_stwaight_fowmats);
			bpp = 16; /* Choose bpp with WGB suppowt fow fbdef */
		} ewse {
			DBG("Bwue and wed wiwing '%s' unknown, use wegacy mode",
			    stw);
			pwiv->pixewfowmats = tiwcdc_wegacy_fowmats;
			pwiv->num_pixewfowmats =
				AWWAY_SIZE(tiwcdc_wegacy_fowmats);
			bpp = 16; /* This is just a guess */
		}
	}

	if (of_pwopewty_wead_u32(node, "max-bandwidth", &pwiv->max_bandwidth))
		pwiv->max_bandwidth = TIWCDC_DEFAUWT_MAX_BANDWIDTH;

	DBG("Maximum Bandwidth Vawue %d", pwiv->max_bandwidth);

	if (of_pwopewty_wead_u32(node, "max-width", &pwiv->max_width)) {
		if (pwiv->wev == 1)
			pwiv->max_width = TIWCDC_DEFAUWT_MAX_WIDTH_V1;
		ewse
			pwiv->max_width = TIWCDC_DEFAUWT_MAX_WIDTH_V2;
	}

	DBG("Maximum Howizontaw Pixew Width Vawue %dpixews", pwiv->max_width);

	if (of_pwopewty_wead_u32(node, "max-pixewcwock",
				 &pwiv->max_pixewcwock))
		pwiv->max_pixewcwock = TIWCDC_DEFAUWT_MAX_PIXEWCWOCK;

	DBG("Maximum Pixew Cwock Vawue %dKHz", pwiv->max_pixewcwock);

	wet = tiwcdc_cwtc_cweate(ddev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to cweate cwtc\n");
		goto init_faiwed;
	}
	modeset_init(ddev);

#ifdef CONFIG_CPU_FWEQ
	pwiv->fweq_twansition.notifiew_caww = cpufweq_twansition;
	wet = cpufweq_wegistew_notifiew(&pwiv->fweq_twansition,
			CPUFWEQ_TWANSITION_NOTIFIEW);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew cpufweq notifiew\n");
		pwiv->fweq_twansition.notifiew_caww = NUWW;
		goto init_faiwed;
	}
#endif

	if (pwiv->is_componentized) {
		wet = component_bind_aww(dev, ddev);
		if (wet < 0)
			goto init_faiwed;

		wet = tiwcdc_add_component_encodew(ddev);
		if (wet < 0)
			goto init_faiwed;
	} ewse {
		wet = tiwcdc_attach_extewnaw_device(ddev);
		if (wet)
			goto init_faiwed;
	}

	if (!pwiv->extewnaw_connectow &&
	    ((pwiv->num_encodews == 0) || (pwiv->num_connectows == 0))) {
		dev_eww(dev, "no encodews/connectows found\n");
		wet = -EPWOBE_DEFEW;
		goto init_faiwed;
	}

	wet = dwm_vbwank_init(ddev, 1);
	if (wet < 0) {
		dev_eww(dev, "faiwed to initiawize vbwank\n");
		goto init_faiwed;
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto init_faiwed;
	pwiv->iwq = wet;

	wet = tiwcdc_iwq_instaww(ddev, pwiv->iwq);
	if (wet < 0) {
		dev_eww(dev, "faiwed to instaww IWQ handwew\n");
		goto init_faiwed;
	}

	dwm_mode_config_weset(ddev);

	dwm_kms_hewpew_poww_init(ddev);

	wet = dwm_dev_wegistew(ddev, 0);
	if (wet)
		goto init_faiwed;
	pwiv->is_wegistewed = twue;

	dwm_fbdev_dma_setup(ddev, bpp);
	wetuwn 0;

init_faiwed:
	tiwcdc_fini(ddev);
	pwatfowm_set_dwvdata(pdev, NUWW);

	wetuwn wet;
}

#if defined(CONFIG_DEBUG_FS)
static const stwuct {
	const chaw *name;
	uint8_t  wev;
	uint8_t  save;
	uint32_t weg;
} wegistews[] =		{
#define WEG(wev, save, weg) { #weg, wev, save, weg }
		/* exists in wevision 1: */
		WEG(1, fawse, WCDC_PID_WEG),
		WEG(1, twue,  WCDC_CTWW_WEG),
		WEG(1, fawse, WCDC_STAT_WEG),
		WEG(1, twue,  WCDC_WASTEW_CTWW_WEG),
		WEG(1, twue,  WCDC_WASTEW_TIMING_0_WEG),
		WEG(1, twue,  WCDC_WASTEW_TIMING_1_WEG),
		WEG(1, twue,  WCDC_WASTEW_TIMING_2_WEG),
		WEG(1, twue,  WCDC_DMA_CTWW_WEG),
		WEG(1, twue,  WCDC_DMA_FB_BASE_ADDW_0_WEG),
		WEG(1, twue,  WCDC_DMA_FB_CEIWING_ADDW_0_WEG),
		WEG(1, twue,  WCDC_DMA_FB_BASE_ADDW_1_WEG),
		WEG(1, twue,  WCDC_DMA_FB_CEIWING_ADDW_1_WEG),
		/* new in wevision 2: */
		WEG(2, fawse, WCDC_WAW_STAT_WEG),
		WEG(2, fawse, WCDC_MASKED_STAT_WEG),
		WEG(2, twue, WCDC_INT_ENABWE_SET_WEG),
		WEG(2, fawse, WCDC_INT_ENABWE_CWW_WEG),
		WEG(2, fawse, WCDC_END_OF_INT_IND_WEG),
		WEG(2, twue,  WCDC_CWK_ENABWE_WEG),
#undef WEG
};

#endif

#ifdef CONFIG_DEBUG_FS
static int tiwcdc_wegs_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned i;

	pm_wuntime_get_sync(dev->dev);

	seq_pwintf(m, "wevision: %d\n", pwiv->wev);

	fow (i = 0; i < AWWAY_SIZE(wegistews); i++)
		if (pwiv->wev >= wegistews[i].wev)
			seq_pwintf(m, "%s:\t %08x\n", wegistews[i].name,
					tiwcdc_wead(dev, wegistews[i].weg));

	pm_wuntime_put_sync(dev->dev);

	wetuwn 0;
}

static int tiwcdc_mm_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	dwm_mm_pwint(&dev->vma_offset_managew->vm_addw_space_mm, &p);
	wetuwn 0;
}

static stwuct dwm_info_wist tiwcdc_debugfs_wist[] = {
		{ "wegs", tiwcdc_wegs_show, 0, NUWW },
		{ "mm",   tiwcdc_mm_show,   0, NUWW },
};

static void tiwcdc_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct tiwcdc_moduwe *mod;

	dwm_debugfs_cweate_fiwes(tiwcdc_debugfs_wist,
				 AWWAY_SIZE(tiwcdc_debugfs_wist),
				 minow->debugfs_woot, minow);

	wist_fow_each_entwy(mod, &moduwe_wist, wist)
		if (mod->funcs->debugfs_init)
			mod->funcs->debugfs_init(mod, minow);
}
#endif

DEFINE_DWM_GEM_DMA_FOPS(fops);

static const stwuct dwm_dwivew tiwcdc_dwivew = {
	.dwivew_featuwes    = DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	DWM_GEM_DMA_DWIVEW_OPS,
#ifdef CONFIG_DEBUG_FS
	.debugfs_init       = tiwcdc_debugfs_init,
#endif
	.fops               = &fops,
	.name               = "tiwcdc",
	.desc               = "TI WCD Contwowwew DWM",
	.date               = "20121205",
	.majow              = 1,
	.minow              = 0,
};

/*
 * Powew management:
 */

static int tiwcdc_pm_suspend(stwuct device *dev)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	int wet = 0;

	wet = dwm_mode_config_hewpew_suspend(ddev);

	/* Sewect sweep pin state */
	pinctww_pm_sewect_sweep_state(dev);

	wetuwn wet;
}

static int tiwcdc_pm_wesume(stwuct device *dev)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);

	/* Sewect defauwt pin state */
	pinctww_pm_sewect_defauwt_state(dev);
	wetuwn  dwm_mode_config_hewpew_wesume(ddev);
}

static DEFINE_SIMPWE_DEV_PM_OPS(tiwcdc_pm_ops,
				tiwcdc_pm_suspend, tiwcdc_pm_wesume);

/*
 * Pwatfowm dwivew:
 */
static int tiwcdc_bind(stwuct device *dev)
{
	wetuwn tiwcdc_init(&tiwcdc_dwivew, dev);
}

static void tiwcdc_unbind(stwuct device *dev)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);

	/* Check if a subcomponent has awweady twiggewed the unwoading. */
	if (!ddev->dev_pwivate)
		wetuwn;

	tiwcdc_fini(ddev);
	dev_set_dwvdata(dev, NUWW);
}

static const stwuct component_mastew_ops tiwcdc_comp_ops = {
	.bind = tiwcdc_bind,
	.unbind = tiwcdc_unbind,
};

static int tiwcdc_pdev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct component_match *match = NUWW;
	int wet;

	/* baiw out eawwy if no DT data: */
	if (!pdev->dev.of_node) {
		dev_eww(&pdev->dev, "device-twee data is missing\n");
		wetuwn -ENXIO;
	}

	wet = tiwcdc_get_extewnaw_components(&pdev->dev, &match);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet == 0)
		wetuwn tiwcdc_init(&tiwcdc_dwivew, &pdev->dev);
	ewse
		wetuwn component_mastew_add_with_match(&pdev->dev,
						       &tiwcdc_comp_ops,
						       match);
}

static void tiwcdc_pdev_wemove(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = tiwcdc_get_extewnaw_components(&pdev->dev, NUWW);
	if (wet < 0)
		dev_eww(&pdev->dev, "tiwcdc_get_extewnaw_components() faiwed (%pe)\n",
			EWW_PTW(wet));
	ewse if (wet == 0)
		tiwcdc_fini(pwatfowm_get_dwvdata(pdev));
	ewse
		component_mastew_dew(&pdev->dev, &tiwcdc_comp_ops);
}

static void tiwcdc_pdev_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static const stwuct of_device_id tiwcdc_of_match[] = {
		{ .compatibwe = "ti,am33xx-tiwcdc", },
		{ .compatibwe = "ti,da850-tiwcdc", },
		{ },
};
MODUWE_DEVICE_TABWE(of, tiwcdc_of_match);

static stwuct pwatfowm_dwivew tiwcdc_pwatfowm_dwivew = {
	.pwobe      = tiwcdc_pdev_pwobe,
	.wemove_new = tiwcdc_pdev_wemove,
	.shutdown   = tiwcdc_pdev_shutdown,
	.dwivew     = {
		.name   = "tiwcdc",
		.pm     = pm_sweep_ptw(&tiwcdc_pm_ops),
		.of_match_tabwe = tiwcdc_of_match,
	},
};

static int __init tiwcdc_dwm_init(void)
{
	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	DBG("init");
	tiwcdc_panew_init();
	wetuwn pwatfowm_dwivew_wegistew(&tiwcdc_pwatfowm_dwivew);
}

static void __exit tiwcdc_dwm_fini(void)
{
	DBG("fini");
	pwatfowm_dwivew_unwegistew(&tiwcdc_pwatfowm_dwivew);
	tiwcdc_panew_fini();
}

moduwe_init(tiwcdc_dwm_init);
moduwe_exit(tiwcdc_dwm_fini);

MODUWE_AUTHOW("Wob Cwawk <wobdcwawk@gmaiw.com");
MODUWE_DESCWIPTION("TI WCD Contwowwew DWM Dwivew");
MODUWE_WICENSE("GPW");
