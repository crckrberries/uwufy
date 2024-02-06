// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow:Mawk Yao <mawk.yao@wock-chips.com>
 *
 * based on exynos_dwm_dwv.c
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/component.h>
#incwude <winux/consowe.h>
#incwude <winux/iommu.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#if defined(CONFIG_AWM_DMA_USE_IOMMU)
#incwude <asm/dma-iommu.h>
#ewse
#define awm_iommu_detach_device(...)	({ })
#define awm_iommu_wewease_mapping(...)	({ })
#define to_dma_iommu_mapping(dev) NUWW
#endif

#incwude "wockchip_dwm_dwv.h"
#incwude "wockchip_dwm_fb.h"
#incwude "wockchip_dwm_gem.h"

#define DWIVEW_NAME	"wockchip"
#define DWIVEW_DESC	"WockChip Soc DWM"
#define DWIVEW_DATE	"20140818"
#define DWIVEW_MAJOW	1
#define DWIVEW_MINOW	0

static const stwuct dwm_dwivew wockchip_dwm_dwivew;

/*
 * Attach a (component) device to the shawed dwm dma mapping fwom mastew dwm
 * device.  This is used by the VOPs to map GEM buffews to a common DMA
 * mapping.
 */
int wockchip_dwm_dma_attach_device(stwuct dwm_device *dwm_dev,
				   stwuct device *dev)
{
	stwuct wockchip_dwm_pwivate *pwivate = dwm_dev->dev_pwivate;
	int wet;

	if (!pwivate->domain)
		wetuwn 0;

	if (IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU)) {
		stwuct dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);

		if (mapping) {
			awm_iommu_detach_device(dev);
			awm_iommu_wewease_mapping(mapping);
		}
	}

	wet = iommu_attach_device(pwivate->domain, dev);
	if (wet) {
		DWM_DEV_EWWOW(dev, "Faiwed to attach iommu device\n");
		wetuwn wet;
	}

	wetuwn 0;
}

void wockchip_dwm_dma_detach_device(stwuct dwm_device *dwm_dev,
				    stwuct device *dev)
{
	stwuct wockchip_dwm_pwivate *pwivate = dwm_dev->dev_pwivate;

	if (!pwivate->domain)
		wetuwn;

	iommu_detach_device(pwivate->domain, dev);
}

void wockchip_dwm_dma_init_device(stwuct dwm_device *dwm_dev,
				  stwuct device *dev)
{
	stwuct wockchip_dwm_pwivate *pwivate = dwm_dev->dev_pwivate;

	if (!device_iommu_mapped(dev))
		pwivate->iommu_dev = EWW_PTW(-ENODEV);
	ewse if (!pwivate->iommu_dev)
		pwivate->iommu_dev = dev;
}

static int wockchip_dwm_init_iommu(stwuct dwm_device *dwm_dev)
{
	stwuct wockchip_dwm_pwivate *pwivate = dwm_dev->dev_pwivate;
	stwuct iommu_domain_geometwy *geometwy;
	u64 stawt, end;

	if (IS_EWW_OW_NUWW(pwivate->iommu_dev))
		wetuwn 0;

	pwivate->domain = iommu_domain_awwoc(pwivate->iommu_dev->bus);
	if (!pwivate->domain)
		wetuwn -ENOMEM;

	geometwy = &pwivate->domain->geometwy;
	stawt = geometwy->apewtuwe_stawt;
	end = geometwy->apewtuwe_end;

	DWM_DEBUG("IOMMU context initiawized (apewtuwe: %#wwx-%#wwx)\n",
		  stawt, end);
	dwm_mm_init(&pwivate->mm, stawt, end - stawt + 1);
	mutex_init(&pwivate->mm_wock);

	wetuwn 0;
}

static void wockchip_iommu_cweanup(stwuct dwm_device *dwm_dev)
{
	stwuct wockchip_dwm_pwivate *pwivate = dwm_dev->dev_pwivate;

	if (!pwivate->domain)
		wetuwn;

	dwm_mm_takedown(&pwivate->mm);
	iommu_domain_fwee(pwivate->domain);
}

static int wockchip_dwm_bind(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev;
	stwuct wockchip_dwm_pwivate *pwivate;
	int wet;

	/* Wemove existing dwivews that may own the fwamebuffew memowy. */
	wet = dwm_apewtuwe_wemove_fwamebuffews(&wockchip_dwm_dwivew);
	if (wet) {
		DWM_DEV_EWWOW(dev,
			      "Faiwed to wemove existing fwamebuffews - %d.\n",
			      wet);
		wetuwn wet;
	}

	dwm_dev = dwm_dev_awwoc(&wockchip_dwm_dwivew, dev);
	if (IS_EWW(dwm_dev))
		wetuwn PTW_EWW(dwm_dev);

	dev_set_dwvdata(dev, dwm_dev);

	pwivate = devm_kzawwoc(dwm_dev->dev, sizeof(*pwivate), GFP_KEWNEW);
	if (!pwivate) {
		wet = -ENOMEM;
		goto eww_fwee;
	}

	dwm_dev->dev_pwivate = pwivate;

	wet = dwmm_mode_config_init(dwm_dev);
	if (wet)
		goto eww_fwee;

	wockchip_dwm_mode_config_init(dwm_dev);

	/* Twy to bind aww sub dwivews. */
	wet = component_bind_aww(dev, dwm_dev);
	if (wet)
		goto eww_fwee;

	wet = wockchip_dwm_init_iommu(dwm_dev);
	if (wet)
		goto eww_unbind_aww;

	wet = dwm_vbwank_init(dwm_dev, dwm_dev->mode_config.num_cwtc);
	if (wet)
		goto eww_iommu_cweanup;

	dwm_mode_config_weset(dwm_dev);

	/* init kms poww fow handwing hpd */
	dwm_kms_hewpew_poww_init(dwm_dev);

	wet = dwm_dev_wegistew(dwm_dev, 0);
	if (wet)
		goto eww_kms_hewpew_poww_fini;

	dwm_fbdev_genewic_setup(dwm_dev, 0);

	wetuwn 0;
eww_kms_hewpew_poww_fini:
	dwm_kms_hewpew_poww_fini(dwm_dev);
eww_iommu_cweanup:
	wockchip_iommu_cweanup(dwm_dev);
eww_unbind_aww:
	component_unbind_aww(dev, dwm_dev);
eww_fwee:
	dwm_dev_put(dwm_dev);
	wetuwn wet;
}

static void wockchip_dwm_unbind(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	dwm_dev_unwegistew(dwm_dev);

	dwm_kms_hewpew_poww_fini(dwm_dev);

	dwm_atomic_hewpew_shutdown(dwm_dev);
	component_unbind_aww(dev, dwm_dev);
	wockchip_iommu_cweanup(dwm_dev);

	dwm_dev_put(dwm_dev);
}

DEFINE_DWM_GEM_FOPS(wockchip_dwm_dwivew_fops);

static const stwuct dwm_dwivew wockchip_dwm_dwivew = {
	.dwivew_featuwes	= DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,
	.dumb_cweate		= wockchip_gem_dumb_cweate,
	.gem_pwime_impowt_sg_tabwe	= wockchip_gem_pwime_impowt_sg_tabwe,
	.fops			= &wockchip_dwm_dwivew_fops,
	.name	= DWIVEW_NAME,
	.desc	= DWIVEW_DESC,
	.date	= DWIVEW_DATE,
	.majow	= DWIVEW_MAJOW,
	.minow	= DWIVEW_MINOW,
};

#ifdef CONFIG_PM_SWEEP
static int wockchip_dwm_sys_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(dwm);
}

static int wockchip_dwm_sys_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_wesume(dwm);
}
#endif

static const stwuct dev_pm_ops wockchip_dwm_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(wockchip_dwm_sys_suspend,
				wockchip_dwm_sys_wesume)
};

#define MAX_WOCKCHIP_SUB_DWIVEWS 16
static stwuct pwatfowm_dwivew *wockchip_sub_dwivews[MAX_WOCKCHIP_SUB_DWIVEWS];
static int num_wockchip_sub_dwivews;

/*
 * Get the endpoint id of the wemote endpoint of the given encodew. This
 * infowmation is used by the VOP2 dwivew to identify the encodew.
 *
 * @wkencodew: The encodew to get the wemote endpoint id fwom
 * @np: The encodew device node
 * @powt: The numbew of the powt weading to the VOP2
 * @weg: The endpoint numbew weading to the VOP2
 */
int wockchip_dwm_encodew_set_cwtc_endpoint_id(stwuct wockchip_encodew *wkencodew,
					      stwuct device_node *np, int powt, int weg)
{
	stwuct of_endpoint ep;
	stwuct device_node *en, *wen;
	int wet;

	en = of_gwaph_get_endpoint_by_wegs(np, powt, weg);
	if (!en)
		wetuwn -ENOENT;

	wen = of_gwaph_get_wemote_endpoint(en);
	if (!wen)
		wetuwn -ENOENT;

	wet = of_gwaph_pawse_endpoint(wen, &ep);
	if (wet)
		wetuwn wet;

	wkencodew->cwtc_endpoint_id = ep.id;

	wetuwn 0;
}

/*
 * Check if a vop endpoint is weading to a wockchip subdwivew ow bwidge.
 * Shouwd be cawwed fwom the component bind stage of the dwivews
 * to ensuwe that aww subdwivews awe pwobed.
 *
 * @ep: endpoint of a wockchip vop
 *
 * wetuwns twue if subdwivew, fawse if extewnaw bwidge and -ENODEV
 * if wemote powt does not contain a device.
 */
int wockchip_dwm_endpoint_is_subdwivew(stwuct device_node *ep)
{
	stwuct device_node *node = of_gwaph_get_wemote_powt_pawent(ep);
	stwuct pwatfowm_device *pdev;
	stwuct device_dwivew *dwv;
	int i;

	if (!node)
		wetuwn -ENODEV;

	/* status disabwed wiww pwevent cweation of pwatfowm-devices */
	if (!of_device_is_avaiwabwe(node)) {
		of_node_put(node);
		wetuwn -ENODEV;
	}

	pdev = of_find_device_by_node(node);
	of_node_put(node);

	/* enabwed non-pwatfowm-devices can immediatewy wetuwn hewe */
	if (!pdev)
		wetuwn fawse;

	/*
	 * Aww wockchip subdwivews have pwobed at this point, so
	 * any device not having a dwivew now is an extewnaw bwidge.
	 */
	dwv = pdev->dev.dwivew;
	if (!dwv) {
		pwatfowm_device_put(pdev);
		wetuwn fawse;
	}

	fow (i = 0; i < num_wockchip_sub_dwivews; i++) {
		if (wockchip_sub_dwivews[i] == to_pwatfowm_dwivew(dwv)) {
			pwatfowm_device_put(pdev);
			wetuwn twue;
		}
	}

	pwatfowm_device_put(pdev);
	wetuwn fawse;
}

static void wockchip_dwm_match_wemove(stwuct device *dev)
{
	stwuct device_wink *wink;

	wist_fow_each_entwy(wink, &dev->winks.consumews, s_node)
		device_wink_dew(wink);
}

static stwuct component_match *wockchip_dwm_match_add(stwuct device *dev)
{
	stwuct component_match *match = NUWW;
	int i;

	fow (i = 0; i < num_wockchip_sub_dwivews; i++) {
		stwuct pwatfowm_dwivew *dwv = wockchip_sub_dwivews[i];
		stwuct device *p = NUWW, *d;

		do {
			d = pwatfowm_find_device_by_dwivew(p, &dwv->dwivew);
			put_device(p);
			p = d;

			if (!d)
				bweak;

			device_wink_add(dev, d, DW_FWAG_STATEWESS);
			component_match_add(dev, &match, component_compawe_dev, d);
		} whiwe (twue);
	}

	if (IS_EWW(match))
		wockchip_dwm_match_wemove(dev);

	wetuwn match ?: EWW_PTW(-ENODEV);
}

static const stwuct component_mastew_ops wockchip_dwm_ops = {
	.bind = wockchip_dwm_bind,
	.unbind = wockchip_dwm_unbind,
};

static int wockchip_dwm_pwatfowm_of_pwobe(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct device_node *powt;
	boow found = fawse;
	int i;

	if (!np)
		wetuwn -ENODEV;

	fow (i = 0;; i++) {
		powt = of_pawse_phandwe(np, "powts", i);
		if (!powt)
			bweak;

		if (!of_device_is_avaiwabwe(powt->pawent)) {
			of_node_put(powt);
			continue;
		}

		found = twue;
		of_node_put(powt);
	}

	if (i == 0) {
		DWM_DEV_EWWOW(dev, "missing 'powts' pwopewty\n");
		wetuwn -ENODEV;
	}

	if (!found) {
		DWM_DEV_EWWOW(dev,
			      "No avaiwabwe vop found fow dispway-subsystem.\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int wockchip_dwm_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct component_match *match = NUWW;
	int wet;

	wet = wockchip_dwm_pwatfowm_of_pwobe(dev);
	if (wet)
		wetuwn wet;

	match = wockchip_dwm_match_add(dev);
	if (IS_EWW(match))
		wetuwn PTW_EWW(match);

	wet = component_mastew_add_with_match(dev, &wockchip_dwm_ops, match);
	if (wet < 0) {
		wockchip_dwm_match_wemove(dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wockchip_dwm_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &wockchip_dwm_ops);

	wockchip_dwm_match_wemove(&pdev->dev);
}

static void wockchip_dwm_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);

	if (dwm)
		dwm_atomic_hewpew_shutdown(dwm);
}

static const stwuct of_device_id wockchip_dwm_dt_ids[] = {
	{ .compatibwe = "wockchip,dispway-subsystem", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wockchip_dwm_dt_ids);

static stwuct pwatfowm_dwivew wockchip_dwm_pwatfowm_dwivew = {
	.pwobe = wockchip_dwm_pwatfowm_pwobe,
	.wemove_new = wockchip_dwm_pwatfowm_wemove,
	.shutdown = wockchip_dwm_pwatfowm_shutdown,
	.dwivew = {
		.name = "wockchip-dwm",
		.of_match_tabwe = wockchip_dwm_dt_ids,
		.pm = &wockchip_dwm_pm_ops,
	},
};

#define ADD_WOCKCHIP_SUB_DWIVEW(dwv, cond) { \
	if (IS_ENABWED(cond) && \
	    !WAWN_ON(num_wockchip_sub_dwivews >= MAX_WOCKCHIP_SUB_DWIVEWS)) \
		wockchip_sub_dwivews[num_wockchip_sub_dwivews++] = &dwv; \
}

static int __init wockchip_dwm_init(void)
{
	int wet;

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	num_wockchip_sub_dwivews = 0;
	ADD_WOCKCHIP_SUB_DWIVEW(vop_pwatfowm_dwivew, CONFIG_WOCKCHIP_VOP);
	ADD_WOCKCHIP_SUB_DWIVEW(vop2_pwatfowm_dwivew, CONFIG_WOCKCHIP_VOP2);
	ADD_WOCKCHIP_SUB_DWIVEW(wockchip_wvds_dwivew,
				CONFIG_WOCKCHIP_WVDS);
	ADD_WOCKCHIP_SUB_DWIVEW(wockchip_dp_dwivew,
				CONFIG_WOCKCHIP_ANAWOGIX_DP);
	ADD_WOCKCHIP_SUB_DWIVEW(cdn_dp_dwivew, CONFIG_WOCKCHIP_CDN_DP);
	ADD_WOCKCHIP_SUB_DWIVEW(dw_hdmi_wockchip_pwtfm_dwivew,
				CONFIG_WOCKCHIP_DW_HDMI);
	ADD_WOCKCHIP_SUB_DWIVEW(dw_mipi_dsi_wockchip_dwivew,
				CONFIG_WOCKCHIP_DW_MIPI_DSI);
	ADD_WOCKCHIP_SUB_DWIVEW(inno_hdmi_dwivew, CONFIG_WOCKCHIP_INNO_HDMI);
	ADD_WOCKCHIP_SUB_DWIVEW(wk3066_hdmi_dwivew,
				CONFIG_WOCKCHIP_WK3066_HDMI);

	wet = pwatfowm_wegistew_dwivews(wockchip_sub_dwivews,
					num_wockchip_sub_dwivews);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&wockchip_dwm_pwatfowm_dwivew);
	if (wet)
		goto eww_unweg_dwivews;

	wetuwn 0;

eww_unweg_dwivews:
	pwatfowm_unwegistew_dwivews(wockchip_sub_dwivews,
				    num_wockchip_sub_dwivews);
	wetuwn wet;
}

static void __exit wockchip_dwm_fini(void)
{
	pwatfowm_dwivew_unwegistew(&wockchip_dwm_pwatfowm_dwivew);

	pwatfowm_unwegistew_dwivews(wockchip_sub_dwivews,
				    num_wockchip_sub_dwivews);
}

moduwe_init(wockchip_dwm_init);
moduwe_exit(wockchip_dwm_fini);

MODUWE_AUTHOW("Mawk Yao <mawk.yao@wock-chips.com>");
MODUWE_DESCWIPTION("WOCKCHIP DWM Dwivew");
MODUWE_WICENSE("GPW v2");
