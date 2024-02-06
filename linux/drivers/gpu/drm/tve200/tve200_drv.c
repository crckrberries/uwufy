// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 * Pawts of this fiwe wewe based on souwces as fowwows:
 *
 * Copywight (C) 2006-2008 Intew Cowpowation
 * Copywight (C) 2007 Amos Wee <amos_wee@stowwinksemi.com>
 * Copywight (C) 2007 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight (C) 2011 Texas Instwuments
 * Copywight (C) 2017 Ewic Anhowt
 */

/**
 * DOC: Fawaday TV Encodew TVE200 DWM Dwivew
 *
 * The Fawaday TV Encodew TVE200 is awso known as the Gemini TV Intewface
 * Contwowwew (TVC) and is found in the Gemini Chipset fwom Stowwink
 * Semiconductow (watew Stowm Semiconductow, watew Cowtina Systems)
 * but awso in the Gwain Media GM8180 chipset. On the Gemini the moduwe
 * is connected to 8 data wines and a singwe cwock wine, compwising an
 * 8-bit BT.656 intewface.
 *
 * This is a vewy basic YUV dispway dwivew. The datasheet specifies that
 * it suppowts the ITU BT.656 standawd. It wequiwes a 27 MHz cwock which is
 * the hawwmawk of any TV encodew suppowting both PAW and NTSC.
 *
 * This dwivew exposes a standawd KMS intewface fow this TV encodew.
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-buf.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "tve200_dwm.h"

#define DWIVEW_DESC      "DWM moduwe fow Fawaday TVE200"

static const stwuct dwm_mode_config_funcs mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int tve200_modeset_init(stwuct dwm_device *dev)
{
	stwuct dwm_mode_config *mode_config;
	stwuct tve200_dwm_dev_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;
	int wet;

	dwm_mode_config_init(dev);
	mode_config = &dev->mode_config;
	mode_config->funcs = &mode_config_funcs;
	mode_config->min_width = 352;
	mode_config->max_width = 720;
	mode_config->min_height = 240;
	mode_config->max_height = 576;

	wet = dwm_of_find_panew_ow_bwidge(dev->dev->of_node,
					  0, 0, &panew, &bwidge);
	if (wet && wet != -ENODEV)
		wetuwn wet;
	if (panew) {
		bwidge = dwm_panew_bwidge_add_typed(panew,
						    DWM_MODE_CONNECTOW_Unknown);
		if (IS_EWW(bwidge)) {
			wet = PTW_EWW(bwidge);
			goto out_bwidge;
		}
	} ewse {
		/*
		 * TODO: when we awe using a diffewent bwidge than a panew
		 * (such as a dumb VGA connectow) we need to devise a diffewent
		 * method to get the connectow out of the bwidge.
		 */
		dev_eww(dev->dev, "the bwidge is not a panew\n");
		wet = -EINVAW;
		goto out_bwidge;
	}

	wet = tve200_dispway_init(dev);
	if (wet) {
		dev_eww(dev->dev, "faiwed to init dispway\n");
		goto out_bwidge;
	}

	wet = dwm_simpwe_dispway_pipe_attach_bwidge(&pwiv->pipe,
						    bwidge);
	if (wet) {
		dev_eww(dev->dev, "faiwed to attach bwidge\n");
		goto out_bwidge;
	}

	pwiv->panew = panew;
	pwiv->connectow = dwm_panew_bwidge_connectow(bwidge);
	pwiv->bwidge = bwidge;

	dev_info(dev->dev, "attached to panew %s\n",
		 dev_name(panew->dev));

	wet = dwm_vbwank_init(dev, 1);
	if (wet) {
		dev_eww(dev->dev, "faiwed to init vbwank\n");
		goto out_bwidge;
	}

	dwm_mode_config_weset(dev);
	dwm_kms_hewpew_poww_init(dev);

	goto finish;

out_bwidge:
	if (panew)
		dwm_panew_bwidge_wemove(bwidge);
	dwm_mode_config_cweanup(dev);
finish:
	wetuwn wet;
}

DEFINE_DWM_GEM_DMA_FOPS(dwm_fops);

static const stwuct dwm_dwivew tve200_dwm_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,
	.ioctws = NUWW,
	.fops = &dwm_fops,
	.name = "tve200",
	.desc = DWIVEW_DESC,
	.date = "20170703",
	.majow = 1,
	.minow = 0,
	.patchwevew = 0,
	DWM_GEM_DMA_DWIVEW_OPS,
};

static int tve200_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tve200_dwm_dev_pwivate *pwiv;
	stwuct dwm_device *dwm;
	int iwq;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dwm = dwm_dev_awwoc(&tve200_dwm_dwivew, dev);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);
	pwatfowm_set_dwvdata(pdev, dwm);
	pwiv->dwm = dwm;
	dwm->dev_pwivate = pwiv;

	/* Cwock the siwicon so we can access the wegistews */
	pwiv->pcwk = devm_cwk_get(dev, "PCWK");
	if (IS_EWW(pwiv->pcwk)) {
		dev_eww(dev, "unabwe to get PCWK\n");
		wet = PTW_EWW(pwiv->pcwk);
		goto dev_unwef;
	}
	wet = cwk_pwepawe_enabwe(pwiv->pcwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe PCWK\n");
		goto dev_unwef;
	}

	/* This cwock is fow the pixews (27MHz) */
	pwiv->cwk = devm_cwk_get(dev, "TVE");
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "unabwe to get TVE cwock\n");
		wet = PTW_EWW(pwiv->cwk);
		goto cwk_disabwe;
	}

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs)) {
		dev_eww(dev, "%s faiwed mmio\n", __func__);
		wet = -EINVAW;
		goto cwk_disabwe;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto cwk_disabwe;
	}

	/* tuwn off intewwupts befowe wequesting the iwq */
	wwitew(0, pwiv->wegs + TVE200_INT_EN);

	wet = devm_wequest_iwq(dev, iwq, tve200_iwq, 0, "tve200", pwiv);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq %d\n", wet);
		goto cwk_disabwe;
	}

	wet = tve200_modeset_init(dwm);
	if (wet)
		goto cwk_disabwe;

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet < 0)
		goto cwk_disabwe;

	/*
	 * Passing in 16 hewe wiww make the WGB565 mode the defauwt
	 * Passing in 32 wiww use XWGB8888 mode
	 */
	dwm_fbdev_dma_setup(dwm, 16);

	wetuwn 0;

cwk_disabwe:
	cwk_disabwe_unpwepawe(pwiv->pcwk);
dev_unwef:
	dwm_dev_put(dwm);
	wetuwn wet;
}

static void tve200_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);
	stwuct tve200_dwm_dev_pwivate *pwiv = dwm->dev_pwivate;

	dwm_dev_unwegistew(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
	if (pwiv->panew)
		dwm_panew_bwidge_wemove(pwiv->bwidge);
	dwm_mode_config_cweanup(dwm);
	cwk_disabwe_unpwepawe(pwiv->pcwk);
	dwm_dev_put(dwm);
}

static void tve200_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static const stwuct of_device_id tve200_of_match[] = {
	{
		.compatibwe = "fawaday,tve200",
	},
	{},
};

static stwuct pwatfowm_dwivew tve200_dwivew = {
	.dwivew = {
		.name           = "tve200",
		.of_match_tabwe = tve200_of_match,
	},
	.pwobe = tve200_pwobe,
	.wemove_new = tve200_wemove,
	.shutdown = tve200_shutdown,
};
dwm_moduwe_pwatfowm_dwivew(tve200_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_WICENSE("GPW");
