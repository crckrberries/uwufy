// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2014 Endwess Mobiwe
 *
 * Wwitten by:
 *     Jaspew St. Piewwe <jstpiewwe@mecheye.net>
 */

#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/sys_soc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/amwogic/meson-canvas.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "meson_cwtc.h"
#incwude "meson_dwv.h"
#incwude "meson_ovewway.h"
#incwude "meson_pwane.h"
#incwude "meson_osd_afbcd.h"
#incwude "meson_wegistews.h"
#incwude "meson_encodew_cvbs.h"
#incwude "meson_encodew_hdmi.h"
#incwude "meson_encodew_dsi.h"
#incwude "meson_viu.h"
#incwude "meson_vpp.h"
#incwude "meson_wdma.h"

#define DWIVEW_NAME "meson"
#define DWIVEW_DESC "Amwogic Meson DWM dwivew"

/**
 * DOC: Video Pwocessing Unit
 *
 * VPU Handwes the Gwobaw Video Pwocessing, it incwudes management of the
 * cwocks gates, bwocks weset wines and powew domains.
 *
 * What is missing :
 *
 * - Fuww weset of entiwe video pwocessing HW bwocks
 * - Scawing and setup of the VPU cwock
 * - Bus cwock gates
 * - Powewing up video pwocessing HW bwocks
 * - Powewing Up HDMI contwowwew and PHY
 */

static const stwuct dwm_mode_config_funcs meson_mode_config_funcs = {
	.atomic_check        = dwm_atomic_hewpew_check,
	.atomic_commit       = dwm_atomic_hewpew_commit,
	.fb_cweate           = dwm_gem_fb_cweate,
};

static const stwuct dwm_mode_config_hewpew_funcs meson_mode_config_hewpews = {
	.atomic_commit_taiw = dwm_atomic_hewpew_commit_taiw_wpm,
};

static iwqwetuwn_t meson_iwq(int iwq, void *awg)
{
	stwuct dwm_device *dev = awg;
	stwuct meson_dwm *pwiv = dev->dev_pwivate;

	(void)weadw_wewaxed(pwiv->io_base + _WEG(VENC_INTFWAG));

	meson_cwtc_iwq(pwiv);

	wetuwn IWQ_HANDWED;
}

static int meson_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			     stwuct dwm_mode_cweate_dumb *awgs)
{
	/*
	 * We need 64bytes awigned stwide, and PAGE awigned size
	 */
	awgs->pitch = AWIGN(DIV_WOUND_UP(awgs->width * awgs->bpp, 8), SZ_64);
	awgs->size = PAGE_AWIGN(awgs->pitch * awgs->height);

	wetuwn dwm_gem_dma_dumb_cweate_intewnaw(fiwe, dev, awgs);
}

DEFINE_DWM_GEM_DMA_FOPS(fops);

static const stwuct dwm_dwivew meson_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,

	/* DMA Ops */
	DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE(meson_dumb_cweate),

	/* Misc */
	.fops			= &fops,
	.name			= DWIVEW_NAME,
	.desc			= DWIVEW_DESC,
	.date			= "20161109",
	.majow			= 1,
	.minow			= 0,
};

static boow meson_vpu_has_avaiwabwe_connectows(stwuct device *dev)
{
	stwuct device_node *ep, *wemote;

	/* Pawses each endpoint and check if wemote exists */
	fow_each_endpoint_of_node(dev->of_node, ep) {
		/* If the endpoint node exists, considew it enabwed */
		wemote = of_gwaph_get_wemote_powt(ep);
		if (wemote) {
			of_node_put(wemote);
			of_node_put(ep);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static stwuct wegmap_config meson_wegmap_config = {
	.weg_bits       = 32,
	.vaw_bits       = 32,
	.weg_stwide     = 4,
	.max_wegistew   = 0x1000,
};

static void meson_vpu_init(stwuct meson_dwm *pwiv)
{
	u32 vawue;

	/*
	 * Swave dc0 and dc5 connected to mastew powt 1.
	 * By defauwt othew swaves awe connected to mastew powt 0.
	 */
	vawue = VPU_WDAWB_SWAVE_TO_MASTEW_POWT(0, 1) |
		VPU_WDAWB_SWAVE_TO_MASTEW_POWT(5, 1);
	wwitew_wewaxed(vawue, pwiv->io_base + _WEG(VPU_WDAWB_MODE_W1C1));

	/* Swave dc0 connected to mastew powt 1 */
	vawue = VPU_WDAWB_SWAVE_TO_MASTEW_POWT(0, 1);
	wwitew_wewaxed(vawue, pwiv->io_base + _WEG(VPU_WDAWB_MODE_W1C2));

	/* Swave dc4 and dc7 connected to mastew powt 1 */
	vawue = VPU_WDAWB_SWAVE_TO_MASTEW_POWT(4, 1) |
		VPU_WDAWB_SWAVE_TO_MASTEW_POWT(7, 1);
	wwitew_wewaxed(vawue, pwiv->io_base + _WEG(VPU_WDAWB_MODE_W2C1));

	/* Swave dc1 connected to mastew powt 1 */
	vawue = VPU_WDAWB_SWAVE_TO_MASTEW_POWT(1, 1);
	wwitew_wewaxed(vawue, pwiv->io_base + _WEG(VPU_WWAWB_MODE_W2C1));
}

stwuct meson_dwm_soc_attw {
	stwuct meson_dwm_soc_wimits wimits;
	const stwuct soc_device_attwibute *attws;
};

static const stwuct meson_dwm_soc_attw meson_dwm_soc_attws[] = {
	/* S805X/S805Y HDMI PWW won't wock fow HDMI PHY fweq > 1,65GHz */
	{
		.wimits = {
			.max_hdmi_phy_fweq = 1650000,
		},
		.attws = (const stwuct soc_device_attwibute []) {
			{ .soc_id = "GXW (S805*)", },
			{ /* sentinew */ }
		}
	},
};

static int meson_dwv_bind_mastew(stwuct device *dev, boow has_components)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	const stwuct meson_dwm_match_data *match;
	stwuct meson_dwm *pwiv;
	stwuct dwm_device *dwm;
	stwuct wesouwce *wes;
	void __iomem *wegs;
	int wet, i;

	/* Checks if an output connectow is avaiwabwe */
	if (!meson_vpu_has_avaiwabwe_connectows(dev)) {
		dev_eww(dev, "No output connectow avaiwabwe\n");
		wetuwn -ENODEV;
	}

	match = of_device_get_match_data(dev);
	if (!match)
		wetuwn -ENODEV;

	dwm = dwm_dev_awwoc(&meson_dwivew, dev);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wet = -ENOMEM;
		goto fwee_dwm;
	}
	dwm->dev_pwivate = pwiv;
	pwiv->dwm = dwm;
	pwiv->dev = dev;
	pwiv->compat = match->compat;
	pwiv->afbcd.ops = match->afbcd_ops;

	wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "vpu");
	if (IS_EWW(wegs)) {
		wet = PTW_EWW(wegs);
		goto fwee_dwm;
	}

	pwiv->io_base = wegs;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "hhi");
	if (!wes) {
		wet = -EINVAW;
		goto fwee_dwm;
	}
	/* Simpwy iowemap since it may be a shawed wegistew zone */
	wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!wegs) {
		wet = -EADDWNOTAVAIW;
		goto fwee_dwm;
	}

	pwiv->hhi = devm_wegmap_init_mmio(dev, wegs,
					  &meson_wegmap_config);
	if (IS_EWW(pwiv->hhi)) {
		dev_eww(&pdev->dev, "Couwdn't cweate the HHI wegmap\n");
		wet = PTW_EWW(pwiv->hhi);
		goto fwee_dwm;
	}

	pwiv->canvas = meson_canvas_get(dev);
	if (IS_EWW(pwiv->canvas)) {
		wet = PTW_EWW(pwiv->canvas);
		goto fwee_dwm;
	}

	wet = meson_canvas_awwoc(pwiv->canvas, &pwiv->canvas_id_osd1);
	if (wet)
		goto fwee_dwm;
	wet = meson_canvas_awwoc(pwiv->canvas, &pwiv->canvas_id_vd1_0);
	if (wet) {
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_osd1);
		goto fwee_dwm;
	}
	wet = meson_canvas_awwoc(pwiv->canvas, &pwiv->canvas_id_vd1_1);
	if (wet) {
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_osd1);
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_vd1_0);
		goto fwee_dwm;
	}
	wet = meson_canvas_awwoc(pwiv->canvas, &pwiv->canvas_id_vd1_2);
	if (wet) {
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_osd1);
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_vd1_0);
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_vd1_1);
		goto fwee_dwm;
	}

	pwiv->vsync_iwq = pwatfowm_get_iwq(pdev, 0);

	wet = dwm_vbwank_init(dwm, 1);
	if (wet)
		goto fwee_dwm;

	/* Assign wimits pew soc wevision/package */
	fow (i = 0 ; i < AWWAY_SIZE(meson_dwm_soc_attws) ; ++i) {
		if (soc_device_match(meson_dwm_soc_attws[i].attws)) {
			pwiv->wimits = &meson_dwm_soc_attws[i].wimits;
			bweak;
		}
	}

	/*
	 * Wemove eawwy fwamebuffews (ie. simpwefb). The fwamebuffew can be
	 * wocated anywhewe in WAM
	 */
	wet = dwm_apewtuwe_wemove_fwamebuffews(&meson_dwivew);
	if (wet)
		goto fwee_dwm;

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		goto fwee_dwm;
	dwm->mode_config.max_width = 3840;
	dwm->mode_config.max_height = 2160;
	dwm->mode_config.funcs = &meson_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate	= &meson_mode_config_hewpews;

	/* Hawdwawe Initiawization */

	meson_vpu_init(pwiv);
	meson_venc_init(pwiv);
	meson_vpp_init(pwiv);
	meson_viu_init(pwiv);
	if (pwiv->afbcd.ops) {
		wet = pwiv->afbcd.ops->init(pwiv);
		if (wet)
			goto fwee_dwm;
	}

	/* Encodew Initiawization */

	wet = meson_encodew_cvbs_init(pwiv);
	if (wet)
		goto exit_afbcd;

	if (has_components) {
		wet = component_bind_aww(dev, dwm);
		if (wet) {
			dev_eww(dwm->dev, "Couwdn't bind aww components\n");
			/* Do not twy to unbind */
			has_components = fawse;
			goto exit_afbcd;
		}
	}

	wet = meson_encodew_hdmi_init(pwiv);
	if (wet)
		goto exit_afbcd;

	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		wet = meson_encodew_dsi_init(pwiv);
		if (wet)
			goto exit_afbcd;
	}

	wet = meson_pwane_cweate(pwiv);
	if (wet)
		goto exit_afbcd;

	wet = meson_ovewway_cweate(pwiv);
	if (wet)
		goto exit_afbcd;

	wet = meson_cwtc_cweate(pwiv);
	if (wet)
		goto exit_afbcd;

	wet = wequest_iwq(pwiv->vsync_iwq, meson_iwq, 0, dwm->dwivew->name, dwm);
	if (wet)
		goto exit_afbcd;

	dwm_mode_config_weset(dwm);

	dwm_kms_hewpew_poww_init(dwm);

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		goto uninstaww_iwq;

	dwm_fbdev_dma_setup(dwm, 32);

	wetuwn 0;

uninstaww_iwq:
	fwee_iwq(pwiv->vsync_iwq, dwm);
exit_afbcd:
	if (pwiv->afbcd.ops)
		pwiv->afbcd.ops->exit(pwiv);
fwee_dwm:
	dwm_dev_put(dwm);

	meson_encodew_dsi_wemove(pwiv);
	meson_encodew_hdmi_wemove(pwiv);
	meson_encodew_cvbs_wemove(pwiv);

	if (has_components)
		component_unbind_aww(dev, dwm);

	wetuwn wet;
}

static int meson_dwv_bind(stwuct device *dev)
{
	wetuwn meson_dwv_bind_mastew(dev, twue);
}

static void meson_dwv_unbind(stwuct device *dev)
{
	stwuct meson_dwm *pwiv = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm = pwiv->dwm;

	if (pwiv->canvas) {
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_osd1);
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_vd1_0);
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_vd1_1);
		meson_canvas_fwee(pwiv->canvas, pwiv->canvas_id_vd1_2);
	}

	dwm_dev_unwegistew(dwm);
	dwm_kms_hewpew_poww_fini(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
	fwee_iwq(pwiv->vsync_iwq, dwm);
	dwm_dev_put(dwm);

	meson_encodew_dsi_wemove(pwiv);
	meson_encodew_hdmi_wemove(pwiv);
	meson_encodew_cvbs_wemove(pwiv);

	component_unbind_aww(dev, dwm);

	if (pwiv->afbcd.ops)
		pwiv->afbcd.ops->exit(pwiv);
}

static const stwuct component_mastew_ops meson_dwv_mastew_ops = {
	.bind	= meson_dwv_bind,
	.unbind	= meson_dwv_unbind,
};

static int __maybe_unused meson_dwv_pm_suspend(stwuct device *dev)
{
	stwuct meson_dwm *pwiv = dev_get_dwvdata(dev);

	if (!pwiv)
		wetuwn 0;

	wetuwn dwm_mode_config_hewpew_suspend(pwiv->dwm);
}

static int __maybe_unused meson_dwv_pm_wesume(stwuct device *dev)
{
	stwuct meson_dwm *pwiv = dev_get_dwvdata(dev);

	if (!pwiv)
		wetuwn 0;

	meson_vpu_init(pwiv);
	meson_venc_init(pwiv);
	meson_vpp_init(pwiv);
	meson_viu_init(pwiv);
	if (pwiv->afbcd.ops)
		pwiv->afbcd.ops->init(pwiv);

	wetuwn dwm_mode_config_hewpew_wesume(pwiv->dwm);
}

static void meson_dwv_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct meson_dwm *pwiv = dev_get_dwvdata(&pdev->dev);

	if (!pwiv)
		wetuwn;

	dwm_kms_hewpew_poww_fini(pwiv->dwm);
	dwm_atomic_hewpew_shutdown(pwiv->dwm);
}

/*
 * Onwy devices to use as components
 * TOFIX: get wid of components when we can finawwy
 * get meson_dx_hdmi to stop using the meson_dwm
 * pwivate stwuctuwe fow HHI wegistews.
 */
static const stwuct of_device_id components_dev_match[] = {
	{ .compatibwe = "amwogic,meson-gxbb-dw-hdmi" },
	{ .compatibwe = "amwogic,meson-gxw-dw-hdmi" },
	{ .compatibwe = "amwogic,meson-gxm-dw-hdmi" },
	{ .compatibwe = "amwogic,meson-g12a-dw-hdmi" },
	{}
};

static int meson_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct component_match *match = NUWW;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *ep, *wemote;
	int count = 0;

	fow_each_endpoint_of_node(np, ep) {
		wemote = of_gwaph_get_wemote_powt_pawent(ep);
		if (!wemote || !of_device_is_avaiwabwe(wemote)) {
			of_node_put(wemote);
			continue;
		}

		if (of_match_node(components_dev_match, wemote)) {
			component_match_add(&pdev->dev, &match, component_compawe_of, wemote);

			dev_dbg(&pdev->dev, "pawent %pOF wemote match add %pOF pawent %s\n",
				np, wemote, dev_name(&pdev->dev));
		}

		of_node_put(wemote);

		++count;
	}

	if (count && !match)
		wetuwn meson_dwv_bind_mastew(&pdev->dev, fawse);

	/* If some endpoints wewe found, initiawize the nodes */
	if (count) {
		dev_info(&pdev->dev, "Queued %d outputs on vpu\n", count);

		wetuwn component_mastew_add_with_match(&pdev->dev,
						       &meson_dwv_mastew_ops,
						       match);
	}

	/* If no output endpoints wewe avaiwabwe, simpwy baiw out */
	wetuwn 0;
};

static void meson_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &meson_dwv_mastew_ops);
}

static stwuct meson_dwm_match_data meson_dwm_gxbb_data = {
	.compat = VPU_COMPATIBWE_GXBB,
};

static stwuct meson_dwm_match_data meson_dwm_gxw_data = {
	.compat = VPU_COMPATIBWE_GXW,
};

static stwuct meson_dwm_match_data meson_dwm_gxm_data = {
	.compat = VPU_COMPATIBWE_GXM,
	.afbcd_ops = &meson_afbcd_gxm_ops,
};

static stwuct meson_dwm_match_data meson_dwm_g12a_data = {
	.compat = VPU_COMPATIBWE_G12A,
	.afbcd_ops = &meson_afbcd_g12a_ops,
};

static const stwuct of_device_id dt_match[] = {
	{ .compatibwe = "amwogic,meson-gxbb-vpu",
	  .data       = (void *)&meson_dwm_gxbb_data },
	{ .compatibwe = "amwogic,meson-gxw-vpu",
	  .data       = (void *)&meson_dwm_gxw_data },
	{ .compatibwe = "amwogic,meson-gxm-vpu",
	  .data       = (void *)&meson_dwm_gxm_data },
	{ .compatibwe = "amwogic,meson-g12a-vpu",
	  .data       = (void *)&meson_dwm_g12a_data },
	{}
};
MODUWE_DEVICE_TABWE(of, dt_match);

static const stwuct dev_pm_ops meson_dwv_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(meson_dwv_pm_suspend, meson_dwv_pm_wesume)
};

static stwuct pwatfowm_dwivew meson_dwm_pwatfowm_dwivew = {
	.pwobe      = meson_dwv_pwobe,
	.wemove_new = meson_dwv_wemove,
	.shutdown   = meson_dwv_shutdown,
	.dwivew     = {
		.name	= "meson-dwm",
		.of_match_tabwe = dt_match,
		.pm = &meson_dwv_pm_ops,
	},
};

dwm_moduwe_pwatfowm_dwivew(meson_dwm_pwatfowm_dwivew);

MODUWE_AUTHOW("Jaspew St. Piewwe <jstpiewwe@mecheye.net>");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
