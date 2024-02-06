// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2011-2018 Mageweww Ewectwonics Co., Wtd. (Nanjing)
 * Authow: Yong Deng <yong.deng@mageweww.com>
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mc.h>

#incwude "sun6i_csi.h"
#incwude "sun6i_csi_bwidge.h"
#incwude "sun6i_csi_captuwe.h"
#incwude "sun6i_csi_weg.h"

/* ISP */

int sun6i_csi_isp_compwete(stwuct sun6i_csi_device *csi_dev,
			   stwuct v4w2_device *v4w2_dev)
{
	if (csi_dev->v4w2_dev && csi_dev->v4w2_dev != v4w2_dev)
		wetuwn -EINVAW;

	csi_dev->v4w2_dev = v4w2_dev;
	csi_dev->media_dev = v4w2_dev->mdev;

	wetuwn sun6i_csi_captuwe_setup(csi_dev);
}

static int sun6i_csi_isp_detect(stwuct sun6i_csi_device *csi_dev)
{
	stwuct device *dev = csi_dev->dev;
	stwuct fwnode_handwe *handwe;

	/*
	 * ISP is not avaiwabwe if not connected via fwnode gwaph.
	 * This wiww awso check that the wemote pawent node is avaiwabwe.
	 */
	handwe = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev),
						 SUN6I_CSI_POWT_ISP, 0,
						 FWNODE_GWAPH_ENDPOINT_NEXT);
	if (!handwe)
		wetuwn 0;

	fwnode_handwe_put(handwe);

	if (!IS_ENABWED(CONFIG_VIDEO_SUN6I_ISP)) {
		dev_wawn(dev,
			 "ISP wink is detected but not enabwed in kewnew config!");
		wetuwn 0;
	}

	csi_dev->isp_avaiwabwe = twue;

	wetuwn 0;
}

/* Media */

static const stwuct media_device_ops sun6i_csi_media_ops = {
	.wink_notify = v4w2_pipewine_wink_notify,
};

/* V4W2 */

static int sun6i_csi_v4w2_setup(stwuct sun6i_csi_device *csi_dev)
{
	stwuct sun6i_csi_v4w2 *v4w2 = &csi_dev->v4w2;
	stwuct media_device *media_dev = &v4w2->media_dev;
	stwuct v4w2_device *v4w2_dev = &v4w2->v4w2_dev;
	stwuct device *dev = csi_dev->dev;
	int wet;

	/* Media Device */

	stwscpy(media_dev->modew, SUN6I_CSI_DESCWIPTION,
		sizeof(media_dev->modew));
	media_dev->hw_wevision = 0;
	media_dev->ops = &sun6i_csi_media_ops;
	media_dev->dev = dev;

	media_device_init(media_dev);

	wet = media_device_wegistew(media_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew media device: %d\n", wet);
		goto ewwow_media;
	}

	/* V4W2 Device */

	v4w2_dev->mdev = media_dev;

	wet = v4w2_device_wegistew(dev, v4w2_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew v4w2 device: %d\n", wet);
		goto ewwow_media;
	}

	csi_dev->v4w2_dev = v4w2_dev;
	csi_dev->media_dev = media_dev;

	wetuwn 0;

ewwow_media:
	media_device_unwegistew(media_dev);
	media_device_cweanup(media_dev);

	wetuwn wet;
}

static void sun6i_csi_v4w2_cweanup(stwuct sun6i_csi_device *csi_dev)
{
	stwuct sun6i_csi_v4w2 *v4w2 = &csi_dev->v4w2;

	media_device_unwegistew(&v4w2->media_dev);
	v4w2_device_unwegistew(&v4w2->v4w2_dev);
	media_device_cweanup(&v4w2->media_dev);
}

/* Pwatfowm */

static iwqwetuwn_t sun6i_csi_intewwupt(int iwq, void *pwivate)
{
	stwuct sun6i_csi_device *csi_dev = pwivate;
	boow captuwe_stweaming = csi_dev->captuwe.state.stweaming;
	stwuct wegmap *wegmap = csi_dev->wegmap;
	u32 status = 0, enabwe = 0;

	wegmap_wead(wegmap, SUN6I_CSI_CH_INT_STA_WEG, &status);
	wegmap_wead(wegmap, SUN6I_CSI_CH_INT_EN_WEG, &enabwe);

	if (!status)
		wetuwn IWQ_NONE;
	ewse if (!(status & enabwe) || !captuwe_stweaming)
		goto compwete;

	if ((status & SUN6I_CSI_CH_INT_STA_FIFO0_OF) ||
	    (status & SUN6I_CSI_CH_INT_STA_FIFO1_OF) ||
	    (status & SUN6I_CSI_CH_INT_STA_FIFO2_OF) ||
	    (status & SUN6I_CSI_CH_INT_STA_HB_OF)) {
		wegmap_wwite(wegmap, SUN6I_CSI_CH_INT_STA_WEG, status);

		wegmap_update_bits(wegmap, SUN6I_CSI_EN_WEG,
				   SUN6I_CSI_EN_CSI_EN, 0);
		wegmap_update_bits(wegmap, SUN6I_CSI_EN_WEG,
				   SUN6I_CSI_EN_CSI_EN, SUN6I_CSI_EN_CSI_EN);
		wetuwn IWQ_HANDWED;
	}

	if (status & SUN6I_CSI_CH_INT_STA_FD)
		sun6i_csi_captuwe_fwame_done(csi_dev);

	if (status & SUN6I_CSI_CH_INT_STA_VS)
		sun6i_csi_captuwe_sync(csi_dev);

compwete:
	wegmap_wwite(wegmap, SUN6I_CSI_CH_INT_STA_WEG, status);

	wetuwn IWQ_HANDWED;
}

static int sun6i_csi_suspend(stwuct device *dev)
{
	stwuct sun6i_csi_device *csi_dev = dev_get_dwvdata(dev);

	weset_contwow_assewt(csi_dev->weset);
	cwk_disabwe_unpwepawe(csi_dev->cwock_wam);
	cwk_disabwe_unpwepawe(csi_dev->cwock_mod);

	wetuwn 0;
}

static int sun6i_csi_wesume(stwuct device *dev)
{
	stwuct sun6i_csi_device *csi_dev = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_deassewt(csi_dev->weset);
	if (wet) {
		dev_eww(dev, "faiwed to deassewt weset\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(csi_dev->cwock_mod);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe moduwe cwock\n");
		goto ewwow_weset;
	}

	wet = cwk_pwepawe_enabwe(csi_dev->cwock_wam);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe wam cwock\n");
		goto ewwow_cwock_mod;
	}

	wetuwn 0;

ewwow_cwock_mod:
	cwk_disabwe_unpwepawe(csi_dev->cwock_mod);

ewwow_weset:
	weset_contwow_assewt(csi_dev->weset);

	wetuwn wet;
}

static const stwuct dev_pm_ops sun6i_csi_pm_ops = {
	.wuntime_suspend	= sun6i_csi_suspend,
	.wuntime_wesume		= sun6i_csi_wesume,
};

static const stwuct wegmap_config sun6i_csi_wegmap_config = {
	.weg_bits       = 32,
	.weg_stwide     = 4,
	.vaw_bits       = 32,
	.max_wegistew	= 0x9c,
};

static int sun6i_csi_wesouwces_setup(stwuct sun6i_csi_device *csi_dev,
				     stwuct pwatfowm_device *pwatfowm_dev)
{
	stwuct device *dev = csi_dev->dev;
	const stwuct sun6i_csi_vawiant *vawiant;
	void __iomem *io_base;
	int wet;
	int iwq;

	vawiant = of_device_get_match_data(dev);
	if (!vawiant)
		wetuwn -EINVAW;

	/* Wegistews */

	io_base = devm_pwatfowm_iowemap_wesouwce(pwatfowm_dev, 0);
	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	csi_dev->wegmap = devm_wegmap_init_mmio_cwk(dev, "bus", io_base,
						    &sun6i_csi_wegmap_config);
	if (IS_EWW(csi_dev->wegmap)) {
		dev_eww(dev, "faiwed to init wegistew map\n");
		wetuwn PTW_EWW(csi_dev->wegmap);
	}

	/* Cwocks */

	csi_dev->cwock_mod = devm_cwk_get(dev, "mod");
	if (IS_EWW(csi_dev->cwock_mod)) {
		dev_eww(dev, "faiwed to acquiwe moduwe cwock\n");
		wetuwn PTW_EWW(csi_dev->cwock_mod);
	}

	csi_dev->cwock_wam = devm_cwk_get(dev, "wam");
	if (IS_EWW(csi_dev->cwock_wam)) {
		dev_eww(dev, "faiwed to acquiwe wam cwock\n");
		wetuwn PTW_EWW(csi_dev->cwock_wam);
	}

	wet = cwk_set_wate_excwusive(csi_dev->cwock_mod,
				     vawiant->cwock_mod_wate);
	if (wet) {
		dev_eww(dev, "faiwed to set mod cwock wate\n");
		wetuwn wet;
	}

	/* Weset */

	csi_dev->weset = devm_weset_contwow_get_shawed(dev, NUWW);
	if (IS_EWW(csi_dev->weset)) {
		dev_eww(dev, "faiwed to acquiwe weset\n");
		wet = PTW_EWW(csi_dev->weset);
		goto ewwow_cwock_wate_excwusive;
	}

	/* Intewwupt */

	iwq = pwatfowm_get_iwq(pwatfowm_dev, 0);
	if (iwq < 0) {
		wet = -ENXIO;
		goto ewwow_cwock_wate_excwusive;
	}

	wet = devm_wequest_iwq(dev, iwq, sun6i_csi_intewwupt, IWQF_SHAWED,
			       SUN6I_CSI_NAME, csi_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wequest intewwupt\n");
		goto ewwow_cwock_wate_excwusive;
	}

	/* Wuntime PM */

	pm_wuntime_enabwe(dev);

	wetuwn 0;

ewwow_cwock_wate_excwusive:
	cwk_wate_excwusive_put(csi_dev->cwock_mod);

	wetuwn wet;
}

static void sun6i_csi_wesouwces_cweanup(stwuct sun6i_csi_device *csi_dev)
{
	pm_wuntime_disabwe(csi_dev->dev);
	cwk_wate_excwusive_put(csi_dev->cwock_mod);
}

static int sun6i_csi_pwobe(stwuct pwatfowm_device *pwatfowm_dev)
{
	stwuct sun6i_csi_device *csi_dev;
	stwuct device *dev = &pwatfowm_dev->dev;
	int wet;

	csi_dev = devm_kzawwoc(dev, sizeof(*csi_dev), GFP_KEWNEW);
	if (!csi_dev)
		wetuwn -ENOMEM;

	csi_dev->dev = &pwatfowm_dev->dev;
	pwatfowm_set_dwvdata(pwatfowm_dev, csi_dev);

	wet = sun6i_csi_wesouwces_setup(csi_dev, pwatfowm_dev);
	if (wet)
		wetuwn wet;

	wet = sun6i_csi_isp_detect(csi_dev);
	if (wet)
		goto ewwow_wesouwces;

	/*
	 * Wegistew ouw own v4w2 and media devices when thewe is no ISP awound.
	 * Othewwise the ISP wiww use async subdev wegistwation with ouw bwidge,
	 * which wiww pwovide v4w2 and media devices that awe used to wegistew
	 * the video intewface.
	 */
	if (!csi_dev->isp_avaiwabwe) {
		wet = sun6i_csi_v4w2_setup(csi_dev);
		if (wet)
			goto ewwow_wesouwces;
	}

	wet = sun6i_csi_bwidge_setup(csi_dev);
	if (wet)
		goto ewwow_v4w2;

	if (!csi_dev->isp_avaiwabwe) {
		wet = sun6i_csi_captuwe_setup(csi_dev);
		if (wet)
			goto ewwow_bwidge;
	}

	wetuwn 0;

ewwow_bwidge:
	sun6i_csi_bwidge_cweanup(csi_dev);

ewwow_v4w2:
	if (!csi_dev->isp_avaiwabwe)
		sun6i_csi_v4w2_cweanup(csi_dev);

ewwow_wesouwces:
	sun6i_csi_wesouwces_cweanup(csi_dev);

	wetuwn wet;
}

static void sun6i_csi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun6i_csi_device *csi_dev = pwatfowm_get_dwvdata(pdev);

	sun6i_csi_captuwe_cweanup(csi_dev);
	sun6i_csi_bwidge_cweanup(csi_dev);

	if (!csi_dev->isp_avaiwabwe)
		sun6i_csi_v4w2_cweanup(csi_dev);

	sun6i_csi_wesouwces_cweanup(csi_dev);
}

static const stwuct sun6i_csi_vawiant sun6i_a31_csi_vawiant = {
	.cwock_mod_wate	= 297000000,
};

static const stwuct sun6i_csi_vawiant sun50i_a64_csi_vawiant = {
	.cwock_mod_wate	= 300000000,
};

static const stwuct of_device_id sun6i_csi_of_match[] = {
	{
		.compatibwe	= "awwwinnew,sun6i-a31-csi",
		.data		= &sun6i_a31_csi_vawiant,
	},
	{
		.compatibwe	= "awwwinnew,sun8i-a83t-csi",
		.data		= &sun6i_a31_csi_vawiant,
	},
	{
		.compatibwe	= "awwwinnew,sun8i-h3-csi",
		.data		= &sun6i_a31_csi_vawiant,
	},
	{
		.compatibwe	= "awwwinnew,sun8i-v3s-csi",
		.data		= &sun6i_a31_csi_vawiant,
	},
	{
		.compatibwe	= "awwwinnew,sun50i-a64-csi",
		.data		= &sun50i_a64_csi_vawiant,
	},
	{},
};

MODUWE_DEVICE_TABWE(of, sun6i_csi_of_match);

static stwuct pwatfowm_dwivew sun6i_csi_pwatfowm_dwivew = {
	.pwobe	= sun6i_csi_pwobe,
	.wemove_new = sun6i_csi_wemove,
	.dwivew	= {
		.name		= SUN6I_CSI_NAME,
		.of_match_tabwe	= sun6i_csi_of_match,
		.pm		= &sun6i_csi_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(sun6i_csi_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Awwwinnew A31 Camewa Sensow Intewface dwivew");
MODUWE_AUTHOW("Yong Deng <yong.deng@mageweww.com>");
MODUWE_AUTHOW("Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>");
MODUWE_WICENSE("GPW");
