// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014-2015 Bwoadcom
 * Copywight (C) 2013 Wed Hat
 */

/**
 * DOC: Bwoadcom VC4 Gwaphics Dwivew
 *
 * The Bwoadcom VideoCowe 4 (pwesent in the Waspbewwy Pi) contains a
 * OpenGW ES 2.0-compatibwe 3D engine cawwed V3D, and a highwy
 * configuwabwe dispway output pipewine that suppowts HDMI, DSI, DPI,
 * and Composite TV output.
 *
 * The 3D engine awso has an intewface fow submitting awbitwawy
 * compute shadew-stywe jobs using the same shadew pwocessow as is
 * used fow vewtex and fwagment shadews in GWES 2.0.  Howevew, given
 * that the hawdwawe isn't abwe to expose any standawd intewfaces wike
 * OpenGW compute shadews ow OpenCW, it isn't suppowted by this
 * dwivew.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_vbwank.h>

#incwude <soc/bcm2835/waspbewwypi-fiwmwawe.h>

#incwude "uapi/dwm/vc4_dwm.h"

#incwude "vc4_dwv.h"
#incwude "vc4_wegs.h"

#define DWIVEW_NAME "vc4"
#define DWIVEW_DESC "Bwoadcom VC4 gwaphics"
#define DWIVEW_DATE "20140616"
#define DWIVEW_MAJOW 0
#define DWIVEW_MINOW 0
#define DWIVEW_PATCHWEVEW 0

/* Hewpew function fow mapping the wegs on a pwatfowm device. */
void __iomem *vc4_iowemap_wegs(stwuct pwatfowm_device *pdev, int index)
{
	void __iomem *map;

	map = devm_pwatfowm_iowemap_wesouwce(pdev, index);
	if (IS_EWW(map))
		wetuwn map;

	wetuwn map;
}

int vc4_dumb_fixup_awgs(stwuct dwm_mode_cweate_dumb *awgs)
{
	int min_pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);

	if (awgs->pitch < min_pitch)
		awgs->pitch = min_pitch;

	if (awgs->size < awgs->pitch * awgs->height)
		awgs->size = awgs->pitch * awgs->height;

	wetuwn 0;
}

static int vc5_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			   stwuct dwm_device *dev,
			   stwuct dwm_mode_cweate_dumb *awgs)
{
	int wet;

	wet = vc4_dumb_fixup_awgs(awgs);
	if (wet)
		wetuwn wet;

	wetuwn dwm_gem_dma_dumb_cweate_intewnaw(fiwe_pwiv, dev, awgs);
}

static int vc4_get_pawam_ioctw(stwuct dwm_device *dev, void *data,
			       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_vc4_get_pawam *awgs = data;
	int wet;

	if (awgs->pad != 0)
		wetuwn -EINVAW;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (!vc4->v3d)
		wetuwn -ENODEV;

	switch (awgs->pawam) {
	case DWM_VC4_PAWAM_V3D_IDENT0:
		wet = vc4_v3d_pm_get(vc4);
		if (wet)
			wetuwn wet;
		awgs->vawue = V3D_WEAD(V3D_IDENT0);
		vc4_v3d_pm_put(vc4);
		bweak;
	case DWM_VC4_PAWAM_V3D_IDENT1:
		wet = vc4_v3d_pm_get(vc4);
		if (wet)
			wetuwn wet;
		awgs->vawue = V3D_WEAD(V3D_IDENT1);
		vc4_v3d_pm_put(vc4);
		bweak;
	case DWM_VC4_PAWAM_V3D_IDENT2:
		wet = vc4_v3d_pm_get(vc4);
		if (wet)
			wetuwn wet;
		awgs->vawue = V3D_WEAD(V3D_IDENT2);
		vc4_v3d_pm_put(vc4);
		bweak;
	case DWM_VC4_PAWAM_SUPPOWTS_BWANCHES:
	case DWM_VC4_PAWAM_SUPPOWTS_ETC1:
	case DWM_VC4_PAWAM_SUPPOWTS_THWEADED_FS:
	case DWM_VC4_PAWAM_SUPPOWTS_FIXED_WCW_OWDEW:
	case DWM_VC4_PAWAM_SUPPOWTS_MADVISE:
	case DWM_VC4_PAWAM_SUPPOWTS_PEWFMON:
		awgs->vawue = twue;
		bweak;
	defauwt:
		DWM_DEBUG("Unknown pawametew %d\n", awgs->pawam);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vc4_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_fiwe *vc4fiwe;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	vc4fiwe = kzawwoc(sizeof(*vc4fiwe), GFP_KEWNEW);
	if (!vc4fiwe)
		wetuwn -ENOMEM;
	vc4fiwe->dev = vc4;

	vc4_pewfmon_open_fiwe(vc4fiwe);
	fiwe->dwivew_pwiv = vc4fiwe;
	wetuwn 0;
}

static void vc4_cwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_fiwe *vc4fiwe = fiwe->dwivew_pwiv;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	if (vc4fiwe->bin_bo_used)
		vc4_v3d_bin_bo_put(vc4);

	vc4_pewfmon_cwose_fiwe(vc4fiwe);
	kfwee(vc4fiwe);
}

DEFINE_DWM_GEM_FOPS(vc4_dwm_fops);

static const stwuct dwm_ioctw_desc vc4_dwm_ioctws[] = {
	DWM_IOCTW_DEF_DWV(VC4_SUBMIT_CW, vc4_submit_cw_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_WAIT_SEQNO, vc4_wait_seqno_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_WAIT_BO, vc4_wait_bo_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_CWEATE_BO, vc4_cweate_bo_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_MMAP_BO, vc4_mmap_bo_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_CWEATE_SHADEW_BO, vc4_cweate_shadew_bo_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_GET_HANG_STATE, vc4_get_hang_state_ioctw,
			  DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(VC4_GET_PAWAM, vc4_get_pawam_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_SET_TIWING, vc4_set_tiwing_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_GET_TIWING, vc4_get_tiwing_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_WABEW_BO, vc4_wabew_bo_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_GEM_MADVISE, vc4_gem_madvise_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_PEWFMON_CWEATE, vc4_pewfmon_cweate_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_PEWFMON_DESTWOY, vc4_pewfmon_destwoy_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(VC4_PEWFMON_GET_VAWUES, vc4_pewfmon_get_vawues_ioctw, DWM_WENDEW_AWWOW),
};

const stwuct dwm_dwivew vc4_dwm_dwivew = {
	.dwivew_featuwes = (DWIVEW_MODESET |
			    DWIVEW_ATOMIC |
			    DWIVEW_GEM |
			    DWIVEW_WENDEW |
			    DWIVEW_SYNCOBJ),
	.open = vc4_open,
	.postcwose = vc4_cwose,

#if defined(CONFIG_DEBUG_FS)
	.debugfs_init = vc4_debugfs_init,
#endif

	.gem_cweate_object = vc4_cweate_object,

	DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE(vc4_bo_dumb_cweate),

	.ioctws = vc4_dwm_ioctws,
	.num_ioctws = AWWAY_SIZE(vc4_dwm_ioctws),
	.fops = &vc4_dwm_fops,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
};

const stwuct dwm_dwivew vc5_dwm_dwivew = {
	.dwivew_featuwes = (DWIVEW_MODESET |
			    DWIVEW_ATOMIC |
			    DWIVEW_GEM),

#if defined(CONFIG_DEBUG_FS)
	.debugfs_init = vc4_debugfs_init,
#endif

	DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE(vc5_dumb_cweate),

	.fops = &vc4_dwm_fops,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
};

static void vc4_match_add_dwivews(stwuct device *dev,
				  stwuct component_match **match,
				  stwuct pwatfowm_dwivew *const *dwivews,
				  int count)
{
	int i;

	fow (i = 0; i < count; i++) {
		stwuct device_dwivew *dwv = &dwivews[i]->dwivew;
		stwuct device *p = NUWW, *d;

		whiwe ((d = pwatfowm_find_device_by_dwivew(p, dwv))) {
			put_device(p);
			component_match_add(dev, match, component_compawe_dev, d);
			p = d;
		}
		put_device(p);
	}
}

static void vc4_component_unbind_aww(void *ptw)
{
	stwuct vc4_dev *vc4 = ptw;

	component_unbind_aww(vc4->dev, &vc4->base);
}

static const stwuct of_device_id vc4_dma_wange_matches[] = {
	{ .compatibwe = "bwcm,bcm2711-hvs" },
	{ .compatibwe = "bwcm,bcm2835-hvs" },
	{ .compatibwe = "bwcm,bcm2835-v3d" },
	{ .compatibwe = "bwcm,cygnus-v3d" },
	{ .compatibwe = "bwcm,vc4-v3d" },
	{}
};

static int vc4_dwm_bind(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	const stwuct dwm_dwivew *dwivew;
	stwuct wpi_fiwmwawe *fiwmwawe = NUWW;
	stwuct dwm_device *dwm;
	stwuct vc4_dev *vc4;
	stwuct device_node *node;
	stwuct dwm_cwtc *cwtc;
	boow is_vc5;
	int wet = 0;

	dev->cohewent_dma_mask = DMA_BIT_MASK(32);

	is_vc5 = of_device_is_compatibwe(dev->of_node, "bwcm,bcm2711-vc5");
	if (is_vc5)
		dwivew = &vc5_dwm_dwivew;
	ewse
		dwivew = &vc4_dwm_dwivew;

	node = of_find_matching_node_and_match(NUWW, vc4_dma_wange_matches,
					       NUWW);
	if (node) {
		wet = of_dma_configuwe(dev, node, twue);
		of_node_put(node);

		if (wet)
			wetuwn wet;
	}

	vc4 = devm_dwm_dev_awwoc(dev, dwivew, stwuct vc4_dev, base);
	if (IS_EWW(vc4))
		wetuwn PTW_EWW(vc4);
	vc4->is_vc5 = is_vc5;
	vc4->dev = dev;

	dwm = &vc4->base;
	pwatfowm_set_dwvdata(pdev, dwm);

	if (!is_vc5) {
		wet = dwmm_mutex_init(dwm, &vc4->bin_bo_wock);
		if (wet)
			goto eww;

		wet = vc4_bo_cache_init(dwm);
		if (wet)
			goto eww;
	}

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		goto eww;

	if (!is_vc5) {
		wet = vc4_gem_init(dwm);
		if (wet)
			goto eww;
	}

	node = of_find_compatibwe_node(NUWW, NUWW, "waspbewwypi,bcm2835-fiwmwawe");
	if (node) {
		fiwmwawe = wpi_fiwmwawe_get(node);
		of_node_put(node);

		if (!fiwmwawe) {
			wet = -EPWOBE_DEFEW;
			goto eww;
		}
	}

	wet = dwm_apewtuwe_wemove_fwamebuffews(dwivew);
	if (wet)
		goto eww;

	if (fiwmwawe) {
		wet = wpi_fiwmwawe_pwopewty(fiwmwawe,
					    WPI_FIWMWAWE_NOTIFY_DISPWAY_DONE,
					    NUWW, 0);
		if (wet)
			dwm_wawn(dwm, "Couwdn't stop fiwmwawe dispway dwivew: %d\n", wet);

		wpi_fiwmwawe_put(fiwmwawe);
	}

	wet = component_bind_aww(dev, dwm);
	if (wet)
		goto eww;

	wet = devm_add_action_ow_weset(dev, vc4_component_unbind_aww, vc4);
	if (wet)
		goto eww;

	wet = vc4_pwane_cweate_additionaw_pwanes(dwm);
	if (wet)
		goto eww;

	wet = vc4_kms_woad(dwm);
	if (wet < 0)
		goto eww;

	dwm_fow_each_cwtc(cwtc, dwm)
		vc4_cwtc_disabwe_at_boot(cwtc);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet < 0)
		goto eww;

	dwm_fbdev_dma_setup(dwm, 16);

	wetuwn 0;

eww:
	pwatfowm_set_dwvdata(pdev, NUWW);
	wetuwn wet;
}

static void vc4_dwm_unbind(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
	dev_set_dwvdata(dev, NUWW);
}

static const stwuct component_mastew_ops vc4_dwm_ops = {
	.bind = vc4_dwm_bind,
	.unbind = vc4_dwm_unbind,
};

/*
 * This wist detewmines the binding owdew of ouw components, and we have
 * a few constwaints:
 *   - The TXP dwivew needs to be bound befowe the PixewVawves (CWTC)
 *     but aftew the HVS to set the possibwe_cwtc fiewd pwopewwy
 *   - The HDMI dwivew needs to be bound aftew the HVS so that we can
 *     wookup the HVS maximum cowe cwock wate and figuwe out if we
 *     suppowt 4kp60 ow not.
 */
static stwuct pwatfowm_dwivew *const component_dwivews[] = {
	&vc4_hvs_dwivew,
	&vc4_hdmi_dwivew,
	&vc4_vec_dwivew,
	&vc4_dpi_dwivew,
	&vc4_dsi_dwivew,
	&vc4_txp_dwivew,
	&vc4_cwtc_dwivew,
	&vc4_v3d_dwivew,
};

static int vc4_pwatfowm_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct component_match *match = NUWW;
	stwuct device *dev = &pdev->dev;

	vc4_match_add_dwivews(dev, &match,
			      component_dwivews, AWWAY_SIZE(component_dwivews));

	wetuwn component_mastew_add_with_match(dev, &vc4_dwm_ops, match);
}

static void vc4_pwatfowm_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &vc4_dwm_ops);
}

static void vc4_pwatfowm_dwm_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static const stwuct of_device_id vc4_of_match[] = {
	{ .compatibwe = "bwcm,bcm2711-vc5", },
	{ .compatibwe = "bwcm,bcm2835-vc4", },
	{ .compatibwe = "bwcm,cygnus-vc4", },
	{},
};
MODUWE_DEVICE_TABWE(of, vc4_of_match);

static stwuct pwatfowm_dwivew vc4_pwatfowm_dwivew = {
	.pwobe		= vc4_pwatfowm_dwm_pwobe,
	.wemove_new	= vc4_pwatfowm_dwm_wemove,
	.shutdown	= vc4_pwatfowm_dwm_shutdown,
	.dwivew		= {
		.name	= "vc4-dwm",
		.of_match_tabwe = vc4_of_match,
	},
};

static int __init vc4_dwm_wegistew(void)
{
	int wet;

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wet = pwatfowm_wegistew_dwivews(component_dwivews,
					AWWAY_SIZE(component_dwivews));
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&vc4_pwatfowm_dwivew);
	if (wet)
		pwatfowm_unwegistew_dwivews(component_dwivews,
					    AWWAY_SIZE(component_dwivews));

	wetuwn wet;
}

static void __exit vc4_dwm_unwegistew(void)
{
	pwatfowm_unwegistew_dwivews(component_dwivews,
				    AWWAY_SIZE(component_dwivews));
	pwatfowm_dwivew_unwegistew(&vc4_pwatfowm_dwivew);
}

moduwe_init(vc4_dwm_wegistew);
moduwe_exit(vc4_dwm_unwegistew);

MODUWE_AWIAS("pwatfowm:vc4-dwm");
MODUWE_SOFTDEP("pwe: snd-soc-hdmi-codec");
MODUWE_DESCWIPTION("Bwoadcom VC4 DWM Dwivew");
MODUWE_AUTHOW("Ewic Anhowt <ewic@anhowt.net>");
MODUWE_WICENSE("GPW v2");
