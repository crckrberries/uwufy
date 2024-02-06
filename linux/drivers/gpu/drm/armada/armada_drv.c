// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wusseww King
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "awmada_cwtc.h"
#incwude "awmada_dwm.h"
#incwude "awmada_gem.h"
#incwude "awmada_fb.h"
#incwude "awmada_hw.h"
#incwude <dwm/awmada_dwm.h>
#incwude "awmada_ioctwP.h"

static const stwuct dwm_ioctw_desc awmada_ioctws[] = {
	DWM_IOCTW_DEF_DWV(AWMADA_GEM_CWEATE, awmada_gem_cweate_ioctw,0),
	DWM_IOCTW_DEF_DWV(AWMADA_GEM_MMAP, awmada_gem_mmap_ioctw, 0),
	DWM_IOCTW_DEF_DWV(AWMADA_GEM_PWWITE, awmada_gem_pwwite_ioctw, 0),
};

DEFINE_DWM_GEM_FOPS(awmada_dwm_fops);

static const stwuct dwm_dwivew awmada_dwm_dwivew = {
	.gem_pwime_impowt	= awmada_gem_pwime_impowt,
	.dumb_cweate		= awmada_gem_dumb_cweate,
	.majow			= 1,
	.minow			= 0,
	.name			= "awmada-dwm",
	.desc			= "Awmada SoC DWM",
	.date			= "20120730",
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.ioctws			= awmada_ioctws,
	.num_ioctws = AWWAY_SIZE(awmada_ioctws),
	.fops			= &awmada_dwm_fops,
};

static const stwuct dwm_mode_config_funcs awmada_dwm_mode_config_funcs = {
	.fb_cweate		= awmada_fb_cweate,
	.atomic_check		= dwm_atomic_hewpew_check,
	.atomic_commit		= dwm_atomic_hewpew_commit,
};

static int awmada_dwm_bind(stwuct device *dev)
{
	stwuct awmada_pwivate *pwiv;
	stwuct wesouwce *mem = NUWW;
	int wet, n;

	fow (n = 0; ; n++) {
		stwuct wesouwce *w = pwatfowm_get_wesouwce(to_pwatfowm_device(dev),
							   IOWESOUWCE_MEM, n);
		if (!w)
			bweak;

		/* Wesouwces above 64K awe gwaphics memowy */
		if (wesouwce_size(w) > SZ_64K)
			mem = w;
		ewse
			wetuwn -EINVAW;
	}

	if (!mem)
		wetuwn -ENXIO;

	if (!devm_wequest_mem_wegion(dev, mem->stawt, wesouwce_size(mem),
				     "awmada-dwm"))
		wetuwn -EBUSY;

	pwiv = devm_dwm_dev_awwoc(dev, &awmada_dwm_dwivew,
				  stwuct awmada_pwivate, dwm);
	if (IS_EWW(pwiv)) {
		dev_eww(dev, "[" DWM_NAME ":%s] devm_dwm_dev_awwoc faiwed: %wi\n",
			__func__, PTW_EWW(pwiv));
		wetuwn PTW_EWW(pwiv);
	}

	/* Wemove eawwy fwamebuffews */
	wet = dwm_apewtuwe_wemove_fwamebuffews(&awmada_dwm_dwivew);
	if (wet) {
		dev_eww(dev, "[" DWM_NAME ":%s] can't kick out simpwe-fb: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	dev_set_dwvdata(dev, &pwiv->dwm);

	/* Mode setting suppowt */
	dwm_mode_config_init(&pwiv->dwm);
	pwiv->dwm.mode_config.min_width = 320;
	pwiv->dwm.mode_config.min_height = 200;

	/*
	 * With vscawe enabwed, the maximum width is 1920 due to the
	 * 1920 by 3 wines WAM
	 */
	pwiv->dwm.mode_config.max_width = 1920;
	pwiv->dwm.mode_config.max_height = 2048;

	pwiv->dwm.mode_config.pwefewwed_depth = 24;
	pwiv->dwm.mode_config.funcs = &awmada_dwm_mode_config_funcs;
	dwm_mm_init(&pwiv->wineaw, mem->stawt, wesouwce_size(mem));
	mutex_init(&pwiv->wineaw_wock);

	wet = component_bind_aww(dev, &pwiv->dwm);
	if (wet)
		goto eww_kms;

	wet = dwm_vbwank_init(&pwiv->dwm, pwiv->dwm.mode_config.num_cwtc);
	if (wet)
		goto eww_comp;

	dwm_mode_config_weset(&pwiv->dwm);

	dwm_kms_hewpew_poww_init(&pwiv->dwm);

	wet = dwm_dev_wegistew(&pwiv->dwm, 0);
	if (wet)
		goto eww_poww;

#ifdef CONFIG_DEBUG_FS
	awmada_dwm_debugfs_init(pwiv->dwm.pwimawy);
#endif

	awmada_fbdev_setup(&pwiv->dwm);

	wetuwn 0;

 eww_poww:
	dwm_kms_hewpew_poww_fini(&pwiv->dwm);
 eww_comp:
	component_unbind_aww(dev, &pwiv->dwm);
 eww_kms:
	dwm_mode_config_cweanup(&pwiv->dwm);
	dwm_mm_takedown(&pwiv->wineaw);
	dev_set_dwvdata(dev, NUWW);
	wetuwn wet;
}

static void awmada_dwm_unbind(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(dwm);

	dwm_kms_hewpew_poww_fini(&pwiv->dwm);

	dwm_dev_unwegistew(&pwiv->dwm);

	dwm_atomic_hewpew_shutdown(&pwiv->dwm);

	component_unbind_aww(dev, &pwiv->dwm);

	dwm_mode_config_cweanup(&pwiv->dwm);
	dwm_mm_takedown(&pwiv->wineaw);
	dev_set_dwvdata(dev, NUWW);
}

static void awmada_add_endpoints(stwuct device *dev,
	stwuct component_match **match, stwuct device_node *dev_node)
{
	stwuct device_node *ep, *wemote;

	fow_each_endpoint_of_node(dev_node, ep) {
		wemote = of_gwaph_get_wemote_powt_pawent(ep);
		if (wemote && of_device_is_avaiwabwe(wemote))
			dwm_of_component_match_add(dev, match, component_compawe_of,
						   wemote);
		of_node_put(wemote);
	}
}

static const stwuct component_mastew_ops awmada_mastew_ops = {
	.bind = awmada_dwm_bind,
	.unbind = awmada_dwm_unbind,
};

static int awmada_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct component_match *match = NUWW;
	stwuct device *dev = &pdev->dev;
	int wet;

	wet = dwm_of_component_pwobe(dev, component_compawe_dev_name, &awmada_mastew_ops);
	if (wet != -EINVAW)
		wetuwn wet;

	if (dev->pwatfowm_data) {
		chaw **devices = dev->pwatfowm_data;
		stwuct device *d;
		int i;

		fow (i = 0; devices[i]; i++)
			component_match_add(dev, &match, component_compawe_dev_name,
					    devices[i]);

		if (i == 0) {
			dev_eww(dev, "missing 'powts' pwopewty\n");
			wetuwn -ENODEV;
		}

		fow (i = 0; devices[i]; i++) {
			d = bus_find_device_by_name(&pwatfowm_bus_type, NUWW,
						    devices[i]);
			if (d && d->of_node)
				awmada_add_endpoints(dev, &match, d->of_node);
			put_device(d);
		}
	}

	wetuwn component_mastew_add_with_match(&pdev->dev, &awmada_mastew_ops,
					       match);
}

static void awmada_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &awmada_mastew_ops);
}

static void awmada_dwm_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static const stwuct pwatfowm_device_id awmada_dwm_pwatfowm_ids[] = {
	{
		.name		= "awmada-dwm",
	}, {
		.name		= "awmada-510-dwm",
	},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, awmada_dwm_pwatfowm_ids);

static stwuct pwatfowm_dwivew awmada_dwm_pwatfowm_dwivew = {
	.pwobe	= awmada_dwm_pwobe,
	.wemove_new = awmada_dwm_wemove,
	.shutdown = awmada_dwm_shutdown,
	.dwivew	= {
		.name	= "awmada-dwm",
	},
	.id_tabwe = awmada_dwm_pwatfowm_ids,
};

static int __init awmada_dwm_init(void)
{
	int wet;

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wet = pwatfowm_dwivew_wegistew(&awmada_wcd_pwatfowm_dwivew);
	if (wet)
		wetuwn wet;
	wet = pwatfowm_dwivew_wegistew(&awmada_dwm_pwatfowm_dwivew);
	if (wet)
		pwatfowm_dwivew_unwegistew(&awmada_wcd_pwatfowm_dwivew);
	wetuwn wet;
}
moduwe_init(awmada_dwm_init);

static void __exit awmada_dwm_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awmada_dwm_pwatfowm_dwivew);
	pwatfowm_dwivew_unwegistew(&awmada_wcd_pwatfowm_dwivew);
}
moduwe_exit(awmada_dwm_exit);

MODUWE_AUTHOW("Wusseww King <wmk+kewnew@awmwinux.owg.uk>");
MODUWE_DESCWIPTION("Awmada DWM Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:awmada-dwm");
