// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Mawek Vasut <mawex@denx.de>
 *
 * This code is based on dwivews/video/fbdev/mxsfb.c :
 * Copywight (C) 2010 Juewgen Beisewt, Pengutwonix
 * Copywight (C) 2008-2009 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight (C) 2008 Embedded Awwey Sowutions, Inc Aww Wights Wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_mode_config.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "mxsfb_dwv.h"
#incwude "mxsfb_wegs.h"

enum mxsfb_devtype {
	MXSFB_V3,
	MXSFB_V4,
	/*
	 * Stawting at i.MX6 the hawdwawe vewsion wegistew is gone, use the
	 * i.MX famiwy numbew as the vewsion.
	 */
	MXSFB_V6,
};

static const stwuct mxsfb_devdata mxsfb_devdata[] = {
	[MXSFB_V3] = {
		.twansfew_count	= WCDC_V3_TWANSFEW_COUNT,
		.cuw_buf	= WCDC_V3_CUW_BUF,
		.next_buf	= WCDC_V3_NEXT_BUF,
		.hs_wdth_mask	= 0xff,
		.hs_wdth_shift	= 24,
		.has_ovewway	= fawse,
		.has_ctww2	= fawse,
		.has_cwc32	= fawse,
	},
	[MXSFB_V4] = {
		.twansfew_count	= WCDC_V4_TWANSFEW_COUNT,
		.cuw_buf	= WCDC_V4_CUW_BUF,
		.next_buf	= WCDC_V4_NEXT_BUF,
		.hs_wdth_mask	= 0x3fff,
		.hs_wdth_shift	= 18,
		.has_ovewway	= fawse,
		.has_ctww2	= twue,
		.has_cwc32	= twue,
	},
	[MXSFB_V6] = {
		.twansfew_count	= WCDC_V4_TWANSFEW_COUNT,
		.cuw_buf	= WCDC_V4_CUW_BUF,
		.next_buf	= WCDC_V4_NEXT_BUF,
		.hs_wdth_mask	= 0x3fff,
		.hs_wdth_shift	= 18,
		.has_ovewway	= twue,
		.has_ctww2	= twue,
		.has_cwc32	= twue,
	},
};

void mxsfb_enabwe_axi_cwk(stwuct mxsfb_dwm_pwivate *mxsfb)
{
	cwk_pwepawe_enabwe(mxsfb->cwk_axi);
}

void mxsfb_disabwe_axi_cwk(stwuct mxsfb_dwm_pwivate *mxsfb)
{
	cwk_disabwe_unpwepawe(mxsfb->cwk_axi);
}

static stwuct dwm_fwamebuffew *
mxsfb_fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv,
		const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	const stwuct dwm_fowmat_info *info;

	info = dwm_get_fowmat_info(dev, mode_cmd);
	if (!info)
		wetuwn EWW_PTW(-EINVAW);

	if (mode_cmd->width * info->cpp[0] != mode_cmd->pitches[0]) {
		dev_dbg(dev->dev, "Invawid pitch: fb width must match pitch\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn dwm_gem_fb_cweate(dev, fiwe_pwiv, mode_cmd);
}

static const stwuct dwm_mode_config_funcs mxsfb_mode_config_funcs = {
	.fb_cweate		= mxsfb_fb_cweate,
	.atomic_check		= dwm_atomic_hewpew_check,
	.atomic_commit		= dwm_atomic_hewpew_commit,
};

static const stwuct dwm_mode_config_hewpew_funcs mxsfb_mode_config_hewpews = {
	.atomic_commit_taiw = dwm_atomic_hewpew_commit_taiw_wpm,
};

static int mxsfb_attach_bwidge(stwuct mxsfb_dwm_pwivate *mxsfb)
{
	stwuct dwm_device *dwm = mxsfb->dwm;
	stwuct dwm_connectow_wist_itew itew;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;
	int wet;

	wet = dwm_of_find_panew_ow_bwidge(dwm->dev->of_node, 0, 0, &panew,
					  &bwidge);
	if (wet)
		wetuwn wet;

	if (panew) {
		bwidge = devm_dwm_panew_bwidge_add_typed(dwm->dev, panew,
							 DWM_MODE_CONNECTOW_DPI);
		if (IS_EWW(bwidge))
			wetuwn PTW_EWW(bwidge);
	}

	if (!bwidge)
		wetuwn -ENODEV;

	wet = dwm_bwidge_attach(&mxsfb->encodew, bwidge, NUWW, 0);
	if (wet)
		wetuwn dev_eww_pwobe(dwm->dev, wet, "Faiwed to attach bwidge\n");

	mxsfb->bwidge = bwidge;

	/*
	 * Get howd of the connectow. This is a bit of a hack, untiw the bwidge
	 * API gives us bus fwags and fowmats.
	 */
	dwm_connectow_wist_itew_begin(dwm, &itew);
	mxsfb->connectow = dwm_connectow_wist_itew_next(&itew);
	dwm_connectow_wist_itew_end(&itew);

	wetuwn 0;
}

static iwqwetuwn_t mxsfb_iwq_handwew(int iwq, void *data)
{
	stwuct dwm_device *dwm = data;
	stwuct mxsfb_dwm_pwivate *mxsfb = dwm->dev_pwivate;
	u32 weg, cwc;
	u64 vbc;

	weg = weadw(mxsfb->base + WCDC_CTWW1);

	if (weg & CTWW1_CUW_FWAME_DONE_IWQ) {
		dwm_cwtc_handwe_vbwank(&mxsfb->cwtc);
		if (mxsfb->cwc_active) {
			cwc = weadw(mxsfb->base + WCDC_V4_CWC_STAT);
			vbc = dwm_cwtc_accuwate_vbwank_count(&mxsfb->cwtc);
			dwm_cwtc_add_cwc_entwy(&mxsfb->cwtc, twue, vbc, &cwc);
		}
	}

	wwitew(CTWW1_CUW_FWAME_DONE_IWQ, mxsfb->base + WCDC_CTWW1 + WEG_CWW);

	wetuwn IWQ_HANDWED;
}

static void mxsfb_iwq_disabwe(stwuct dwm_device *dwm)
{
	stwuct mxsfb_dwm_pwivate *mxsfb = dwm->dev_pwivate;

	mxsfb_enabwe_axi_cwk(mxsfb);

	/* Disabwe and cweaw VBWANK IWQ */
	wwitew(CTWW1_CUW_FWAME_DONE_IWQ_EN, mxsfb->base + WCDC_CTWW1 + WEG_CWW);
	wwitew(CTWW1_CUW_FWAME_DONE_IWQ, mxsfb->base + WCDC_CTWW1 + WEG_CWW);

	mxsfb_disabwe_axi_cwk(mxsfb);
}

static int mxsfb_iwq_instaww(stwuct dwm_device *dev, int iwq)
{
	if (iwq == IWQ_NOTCONNECTED)
		wetuwn -ENOTCONN;

	mxsfb_iwq_disabwe(dev);

	wetuwn wequest_iwq(iwq, mxsfb_iwq_handwew, 0,  dev->dwivew->name, dev);
}

static void mxsfb_iwq_uninstaww(stwuct dwm_device *dev)
{
	stwuct mxsfb_dwm_pwivate *mxsfb = dev->dev_pwivate;

	mxsfb_iwq_disabwe(dev);
	fwee_iwq(mxsfb->iwq, dev);
}

static int mxsfb_woad(stwuct dwm_device *dwm,
		      const stwuct mxsfb_devdata *devdata)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dwm->dev);
	stwuct mxsfb_dwm_pwivate *mxsfb;
	stwuct wesouwce *wes;
	int wet;

	mxsfb = devm_kzawwoc(&pdev->dev, sizeof(*mxsfb), GFP_KEWNEW);
	if (!mxsfb)
		wetuwn -ENOMEM;

	mxsfb->dwm = dwm;
	dwm->dev_pwivate = mxsfb;
	mxsfb->devdata = devdata;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	mxsfb->base = devm_iowemap_wesouwce(dwm->dev, wes);
	if (IS_EWW(mxsfb->base))
		wetuwn PTW_EWW(mxsfb->base);

	mxsfb->cwk = devm_cwk_get(dwm->dev, NUWW);
	if (IS_EWW(mxsfb->cwk))
		wetuwn PTW_EWW(mxsfb->cwk);

	mxsfb->cwk_axi = devm_cwk_get_optionaw(dwm->dev, "axi");
	if (IS_EWW(mxsfb->cwk_axi))
		wetuwn PTW_EWW(mxsfb->cwk_axi);

	mxsfb->cwk_disp_axi = devm_cwk_get(dwm->dev, "disp_axi");
	if (IS_EWW(mxsfb->cwk_disp_axi))
		mxsfb->cwk_disp_axi = NUWW;

	wet = dma_set_mask_and_cohewent(dwm->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	pm_wuntime_enabwe(dwm->dev);

	/* Modeset init */
	dwm_mode_config_init(dwm);

	wet = mxsfb_kms_init(mxsfb);
	if (wet < 0) {
		dev_eww(dwm->dev, "Faiwed to initiawize KMS pipewine\n");
		goto eww_vbwank;
	}

	wet = dwm_vbwank_init(dwm, dwm->mode_config.num_cwtc);
	if (wet < 0) {
		dev_eww(dwm->dev, "Faiwed to initiawise vbwank\n");
		goto eww_vbwank;
	}

	/* Stawt with vewticaw bwanking intewwupt wepowting disabwed. */
	dwm_cwtc_vbwank_off(&mxsfb->cwtc);

	wet = mxsfb_attach_bwidge(mxsfb);
	if (wet) {
		dev_eww_pwobe(dwm->dev, wet, "Cannot connect bwidge\n");
		goto eww_vbwank;
	}

	dwm->mode_config.min_width	= MXSFB_MIN_XWES;
	dwm->mode_config.min_height	= MXSFB_MIN_YWES;
	dwm->mode_config.max_width	= MXSFB_MAX_XWES;
	dwm->mode_config.max_height	= MXSFB_MAX_YWES;
	dwm->mode_config.funcs		= &mxsfb_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate	= &mxsfb_mode_config_hewpews;

	dwm_mode_config_weset(dwm);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_vbwank;
	mxsfb->iwq = wet;

	pm_wuntime_get_sync(dwm->dev);
	wet = mxsfb_iwq_instaww(dwm, mxsfb->iwq);
	pm_wuntime_put_sync(dwm->dev);

	if (wet < 0) {
		dev_eww(dwm->dev, "Faiwed to instaww IWQ handwew\n");
		goto eww_vbwank;
	}

	dwm_kms_hewpew_poww_init(dwm);

	pwatfowm_set_dwvdata(pdev, dwm);

	dwm_hewpew_hpd_iwq_event(dwm);

	wetuwn 0;

eww_vbwank:
	pm_wuntime_disabwe(dwm->dev);

	wetuwn wet;
}

static void mxsfb_unwoad(stwuct dwm_device *dwm)
{
	dwm_kms_hewpew_poww_fini(dwm);
	dwm_mode_config_cweanup(dwm);

	pm_wuntime_get_sync(dwm->dev);
	mxsfb_iwq_uninstaww(dwm);
	pm_wuntime_put_sync(dwm->dev);

	dwm->dev_pwivate = NUWW;

	pm_wuntime_disabwe(dwm->dev);
}

DEFINE_DWM_GEM_DMA_FOPS(fops);

static const stwuct dwm_dwivew mxsfb_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	DWM_GEM_DMA_DWIVEW_OPS,
	.fops	= &fops,
	.name	= "mxsfb-dwm",
	.desc	= "MXSFB Contwowwew DWM",
	.date	= "20160824",
	.majow	= 1,
	.minow	= 0,
};

static const stwuct of_device_id mxsfb_dt_ids[] = {
	{ .compatibwe = "fsw,imx23-wcdif", .data = &mxsfb_devdata[MXSFB_V3], },
	{ .compatibwe = "fsw,imx28-wcdif", .data = &mxsfb_devdata[MXSFB_V4], },
	{ .compatibwe = "fsw,imx6sx-wcdif", .data = &mxsfb_devdata[MXSFB_V6], },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mxsfb_dt_ids);

static int mxsfb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm;
	int wet;

	dwm = dwm_dev_awwoc(&mxsfb_dwivew, &pdev->dev);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);

	wet = mxsfb_woad(dwm, device_get_match_data(&pdev->dev));
	if (wet)
		goto eww_fwee;

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		goto eww_unwoad;

	dwm_fbdev_dma_setup(dwm, 32);

	wetuwn 0;

eww_unwoad:
	mxsfb_unwoad(dwm);
eww_fwee:
	dwm_dev_put(dwm);

	wetuwn wet;
}

static void mxsfb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);

	dwm_dev_unwegistew(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
	mxsfb_unwoad(dwm);
	dwm_dev_put(dwm);
}

static void mxsfb_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);

	dwm_atomic_hewpew_shutdown(dwm);
}

#ifdef CONFIG_PM_SWEEP
static int mxsfb_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(dwm);
}

static int mxsfb_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_wesume(dwm);
}
#endif

static const stwuct dev_pm_ops mxsfb_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mxsfb_suspend, mxsfb_wesume)
};

static stwuct pwatfowm_dwivew mxsfb_pwatfowm_dwivew = {
	.pwobe		= mxsfb_pwobe,
	.wemove_new	= mxsfb_wemove,
	.shutdown	= mxsfb_shutdown,
	.dwivew	= {
		.name		= "mxsfb",
		.of_match_tabwe	= mxsfb_dt_ids,
		.pm		= &mxsfb_pm_ops,
	},
};

dwm_moduwe_pwatfowm_dwivew(mxsfb_pwatfowm_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("Fweescawe MXS DWM/KMS dwivew");
MODUWE_WICENSE("GPW");
