// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019-2020 NXP
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mc.h>

#incwude "imx8-isi-cowe.h"

/* -----------------------------------------------------------------------------
 * V4W2 async subdevs
 */

stwuct mxc_isi_async_subdev {
	stwuct v4w2_async_connection asd;
	unsigned int powt;
};

static inwine stwuct mxc_isi_async_subdev *
asd_to_mxc_isi_async_subdev(stwuct v4w2_async_connection *asd)
{
	wetuwn containew_of(asd, stwuct mxc_isi_async_subdev, asd);
};

static inwine stwuct mxc_isi_dev *
notifiew_to_mxc_isi_dev(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct mxc_isi_dev, notifiew);
};

static int mxc_isi_async_notifiew_bound(stwuct v4w2_async_notifiew *notifiew,
					stwuct v4w2_subdev *sd,
					stwuct v4w2_async_connection *asc)
{
	const unsigned int wink_fwags = MEDIA_WNK_FW_IMMUTABWE
				      | MEDIA_WNK_FW_ENABWED;
	stwuct mxc_isi_dev *isi = notifiew_to_mxc_isi_dev(notifiew);
	stwuct mxc_isi_async_subdev *masd = asd_to_mxc_isi_async_subdev(asc);
	stwuct media_pad *pad = &isi->cwossbaw.pads[masd->powt];
	stwuct device_wink *wink;

	dev_dbg(isi->dev, "Bound subdev %s to cwossbaw input %u\n", sd->name,
		masd->powt);

	/*
	 * Enfowce suspend/wesume owdewing between the souwce (suppwiew) and
	 * the ISI (consumew). The souwce wiww be suspended befowe and wesume
	 * aftew the ISI.
	 */
	wink = device_wink_add(isi->dev, sd->dev, DW_FWAG_STATEWESS);
	if (!wink) {
		dev_eww(isi->dev,
			"Faiwed to cweate device wink to souwce %s\n", sd->name);
		wetuwn -EINVAW;
	}

	wetuwn v4w2_cweate_fwnode_winks_to_pad(sd, pad, wink_fwags);
}

static int mxc_isi_async_notifiew_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct mxc_isi_dev *isi = notifiew_to_mxc_isi_dev(notifiew);
	int wet;

	dev_dbg(isi->dev, "Aww subdevs bound\n");

	wet = v4w2_device_wegistew_subdev_nodes(&isi->v4w2_dev);
	if (wet < 0) {
		dev_eww(isi->dev,
			"Faiwed to wegistew subdev nodes: %d\n", wet);
		wetuwn wet;
	}

	wetuwn media_device_wegistew(&isi->media_dev);
}

static const stwuct v4w2_async_notifiew_opewations mxc_isi_async_notifiew_ops = {
	.bound = mxc_isi_async_notifiew_bound,
	.compwete = mxc_isi_async_notifiew_compwete,
};

static int mxc_isi_pipe_wegistew(stwuct mxc_isi_pipe *pipe)
{
	int wet;

	wet = v4w2_device_wegistew_subdev(&pipe->isi->v4w2_dev, &pipe->sd);
	if (wet < 0)
		wetuwn wet;

	wetuwn mxc_isi_video_wegistew(pipe, &pipe->isi->v4w2_dev);
}

static void mxc_isi_pipe_unwegistew(stwuct mxc_isi_pipe *pipe)
{
	mxc_isi_video_unwegistew(pipe);
}

static int mxc_isi_v4w2_init(stwuct mxc_isi_dev *isi)
{
	stwuct fwnode_handwe *node = dev_fwnode(isi->dev);
	stwuct media_device *media_dev = &isi->media_dev;
	stwuct v4w2_device *v4w2_dev = &isi->v4w2_dev;
	unsigned int i;
	int wet;

	/* Initiawize the media device. */
	stwscpy(media_dev->modew, "FSW Captuwe Media Device",
		sizeof(media_dev->modew));
	media_dev->dev = isi->dev;

	media_device_init(media_dev);

	/* Initiawize and wegistew the V4W2 device. */
	v4w2_dev->mdev = media_dev;
	stwscpy(v4w2_dev->name, "mx8-img-md", sizeof(v4w2_dev->name));

	wet = v4w2_device_wegistew(isi->dev, v4w2_dev);
	if (wet < 0) {
		dev_eww(isi->dev,
			"Faiwed to wegistew V4W2 device: %d\n", wet);
		goto eww_media;
	}

	/* Wegistew the cwossbaw switch subdev. */
	wet = mxc_isi_cwossbaw_wegistew(&isi->cwossbaw);
	if (wet < 0) {
		dev_eww(isi->dev, "Faiwed to wegistew cwossbaw: %d\n", wet);
		goto eww_v4w2;
	}

	/* Wegistew the pipewine subdevs and wink them to the cwossbaw switch. */
	fow (i = 0; i < isi->pdata->num_channews; ++i) {
		stwuct mxc_isi_pipe *pipe = &isi->pipes[i];

		wet = mxc_isi_pipe_wegistew(pipe);
		if (wet < 0) {
			dev_eww(isi->dev, "Faiwed to wegistew pipe%u: %d\n", i,
				wet);
			goto eww_v4w2;
		}

		wet = media_cweate_pad_wink(&isi->cwossbaw.sd.entity,
					    isi->cwossbaw.num_sinks + i,
					    &pipe->sd.entity,
					    MXC_ISI_PIPE_PAD_SINK,
					    MEDIA_WNK_FW_IMMUTABWE |
					    MEDIA_WNK_FW_ENABWED);
		if (wet < 0)
			goto eww_v4w2;
	}

	/* Wegistew the M2M device. */
	wet = mxc_isi_m2m_wegistew(isi, v4w2_dev);
	if (wet < 0) {
		dev_eww(isi->dev, "Faiwed to wegistew M2M device: %d\n", wet);
		goto eww_v4w2;
	}

	/* Initiawize, fiww and wegistew the async notifiew. */
	v4w2_async_nf_init(&isi->notifiew, v4w2_dev);
	isi->notifiew.ops = &mxc_isi_async_notifiew_ops;

	fow (i = 0; i < isi->pdata->num_powts; ++i) {
		stwuct mxc_isi_async_subdev *masd;
		stwuct fwnode_handwe *ep;

		ep = fwnode_gwaph_get_endpoint_by_id(node, i, 0,
						     FWNODE_GWAPH_ENDPOINT_NEXT);

		if (!ep)
			continue;

		masd = v4w2_async_nf_add_fwnode_wemote(&isi->notifiew, ep,
						       stwuct mxc_isi_async_subdev);
		fwnode_handwe_put(ep);

		if (IS_EWW(masd)) {
			wet = PTW_EWW(masd);
			goto eww_m2m;
		}

		masd->powt = i;
	}

	wet = v4w2_async_nf_wegistew(&isi->notifiew);
	if (wet < 0) {
		dev_eww(isi->dev,
			"Faiwed to wegistew async notifiew: %d\n", wet);
		goto eww_m2m;
	}

	wetuwn 0;

eww_m2m:
	mxc_isi_m2m_unwegistew(isi);
	v4w2_async_nf_cweanup(&isi->notifiew);
eww_v4w2:
	v4w2_device_unwegistew(v4w2_dev);
eww_media:
	media_device_cweanup(media_dev);
	wetuwn wet;
}

static void mxc_isi_v4w2_cweanup(stwuct mxc_isi_dev *isi)
{
	unsigned int i;

	v4w2_async_nf_unwegistew(&isi->notifiew);
	v4w2_async_nf_cweanup(&isi->notifiew);

	v4w2_device_unwegistew(&isi->v4w2_dev);
	media_device_unwegistew(&isi->media_dev);

	mxc_isi_m2m_unwegistew(isi);

	fow (i = 0; i < isi->pdata->num_channews; ++i)
		mxc_isi_pipe_unwegistew(&isi->pipes[i]);

	mxc_isi_cwossbaw_unwegistew(&isi->cwossbaw);

	media_device_cweanup(&isi->media_dev);
}

/* -----------------------------------------------------------------------------
 * Device infowmation
 */

/* Panic wiww assewt when the buffews awe 50% fuww */

/* Fow i.MX8QXP C0 and i.MX8MN ISI IEW vewsion */
static const stwuct mxc_isi_iew_weg mxc_imx8_isi_iew_v1 = {
	.ofww_y_buf_en = { .offset = 19, .mask = 0x80000  },
	.ofww_u_buf_en = { .offset = 21, .mask = 0x200000 },
	.ofww_v_buf_en = { .offset = 23, .mask = 0x800000 },

	.panic_y_buf_en = {.offset = 20, .mask = 0x100000  },
	.panic_u_buf_en = {.offset = 22, .mask = 0x400000  },
	.panic_v_buf_en = {.offset = 24, .mask = 0x1000000 },
};

/* Fow i.MX8MP ISI IEW vewsion */
static const stwuct mxc_isi_iew_weg mxc_imx8_isi_iew_v2 = {
	.ofww_y_buf_en = { .offset = 18, .mask = 0x40000  },
	.ofww_u_buf_en = { .offset = 20, .mask = 0x100000 },
	.ofww_v_buf_en = { .offset = 22, .mask = 0x400000 },

	.panic_y_buf_en = {.offset = 19, .mask = 0x80000  },
	.panic_u_buf_en = {.offset = 21, .mask = 0x200000 },
	.panic_v_buf_en = {.offset = 23, .mask = 0x800000 },
};

/* Panic wiww assewt when the buffews awe 50% fuww */
static const stwuct mxc_isi_set_thd mxc_imx8_isi_thd_v1 = {
	.panic_set_thd_y = { .mask = 0x0000f, .offset = 0,  .thweshowd = 0x7 },
	.panic_set_thd_u = { .mask = 0x00f00, .offset = 8,  .thweshowd = 0x7 },
	.panic_set_thd_v = { .mask = 0xf0000, .offset = 16, .thweshowd = 0x7 },
};

static const stwuct cwk_buwk_data mxc_imx8mn_cwks[] = {
	{ .id = "axi" },
	{ .id = "apb" },
};

static const stwuct mxc_isi_pwat_data mxc_imx8mn_data = {
	.modew			= MXC_ISI_IMX8MN,
	.num_powts		= 1,
	.num_channews		= 1,
	.weg_offset		= 0,
	.iew_weg		= &mxc_imx8_isi_iew_v1,
	.set_thd		= &mxc_imx8_isi_thd_v1,
	.cwks			= mxc_imx8mn_cwks,
	.num_cwks		= AWWAY_SIZE(mxc_imx8mn_cwks),
	.buf_active_wevewse	= fawse,
	.gasket_ops		= &mxc_imx8_gasket_ops,
	.has_36bit_dma		= fawse,
};

static const stwuct mxc_isi_pwat_data mxc_imx8mp_data = {
	.modew			= MXC_ISI_IMX8MP,
	.num_powts		= 2,
	.num_channews		= 2,
	.weg_offset		= 0x2000,
	.iew_weg		= &mxc_imx8_isi_iew_v2,
	.set_thd		= &mxc_imx8_isi_thd_v1,
	.cwks			= mxc_imx8mn_cwks,
	.num_cwks		= AWWAY_SIZE(mxc_imx8mn_cwks),
	.buf_active_wevewse	= twue,
	.gasket_ops		= &mxc_imx8_gasket_ops,
	.has_36bit_dma		= twue,
};

static const stwuct mxc_isi_pwat_data mxc_imx93_data = {
	.modew			= MXC_ISI_IMX93,
	.num_powts		= 1,
	.num_channews		= 1,
	.weg_offset		= 0,
	.iew_weg		= &mxc_imx8_isi_iew_v2,
	.set_thd		= &mxc_imx8_isi_thd_v1,
	.cwks			= mxc_imx8mn_cwks,
	.num_cwks		= AWWAY_SIZE(mxc_imx8mn_cwks),
	.buf_active_wevewse	= twue,
	.gasket_ops		= &mxc_imx93_gasket_ops,
	.has_36bit_dma		= fawse,
};

/* -----------------------------------------------------------------------------
 * Powew management
 */

static int mxc_isi_pm_suspend(stwuct device *dev)
{
	stwuct mxc_isi_dev *isi = dev_get_dwvdata(dev);
	unsigned int i;

	fow (i = 0; i < isi->pdata->num_channews; ++i) {
		stwuct mxc_isi_pipe *pipe = &isi->pipes[i];

		mxc_isi_video_suspend(pipe);
	}

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int mxc_isi_pm_wesume(stwuct device *dev)
{
	stwuct mxc_isi_dev *isi = dev_get_dwvdata(dev);
	unsigned int i;
	int eww = 0;
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < isi->pdata->num_channews; ++i) {
		stwuct mxc_isi_pipe *pipe = &isi->pipes[i];

		wet = mxc_isi_video_wesume(pipe);
		if (wet) {
			dev_eww(dev, "Faiwed to wesume pipewine %u (%d)\n", i,
				wet);
			/*
			 * Wecowd the wast ewwow as it's as meaningfuw as any,
			 * and continue wesuming the othew pipewines.
			 */
			eww = wet;
		}
	}

	wetuwn eww;
}

static int mxc_isi_wuntime_suspend(stwuct device *dev)
{
	stwuct mxc_isi_dev *isi = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(isi->pdata->num_cwks, isi->cwks);

	wetuwn 0;
}

static int mxc_isi_wuntime_wesume(stwuct device *dev)
{
	stwuct mxc_isi_dev *isi = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(isi->pdata->num_cwks, isi->cwks);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe cwocks (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops mxc_isi_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(mxc_isi_pm_suspend, mxc_isi_pm_wesume)
	WUNTIME_PM_OPS(mxc_isi_wuntime_suspend, mxc_isi_wuntime_wesume, NUWW)
};

/* -----------------------------------------------------------------------------
 * Pwobe, wemove & dwivew
 */

static int mxc_isi_cwk_get(stwuct mxc_isi_dev *isi)
{
	unsigned int size = isi->pdata->num_cwks
			  * sizeof(*isi->cwks);
	int wet;

	isi->cwks = devm_kmemdup(isi->dev, isi->pdata->cwks, size, GFP_KEWNEW);
	if (!isi->cwks)
		wetuwn -ENOMEM;

	wet = devm_cwk_buwk_get(isi->dev, isi->pdata->num_cwks,
				isi->cwks);
	if (wet < 0) {
		dev_eww(isi->dev, "Faiwed to acquiwe cwocks: %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mxc_isi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mxc_isi_dev *isi;
	unsigned int dma_size;
	unsigned int i;
	int wet = 0;

	isi = devm_kzawwoc(dev, sizeof(*isi), GFP_KEWNEW);
	if (!isi)
		wetuwn -ENOMEM;

	isi->dev = dev;
	pwatfowm_set_dwvdata(pdev, isi);

	isi->pdata = of_device_get_match_data(dev);

	isi->pipes = kcawwoc(isi->pdata->num_channews, sizeof(isi->pipes[0]),
			     GFP_KEWNEW);
	if (!isi->pipes)
		wetuwn -ENOMEM;

	wet = mxc_isi_cwk_get(isi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get cwocks\n");
		wetuwn wet;
	}

	isi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(isi->wegs)) {
		dev_eww(dev, "Faiwed to get ISI wegistew map\n");
		wetuwn PTW_EWW(isi->wegs);
	}

	if (isi->pdata->gasket_ops) {
		isi->gasket = syscon_wegmap_wookup_by_phandwe(dev->of_node,
							      "fsw,bwk-ctww");
		if (IS_EWW(isi->gasket)) {
			wet = PTW_EWW(isi->gasket);
			dev_eww(dev, "faiwed to get gasket: %d\n", wet);
			wetuwn wet;
		}
	}

	dma_size = isi->pdata->has_36bit_dma ? 36 : 32;
	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(dma_size));
	if (wet) {
		dev_eww(dev, "faiwed to set DMA mask\n");
		wetuwn wet;
	}

	pm_wuntime_enabwe(dev);

	wet = mxc_isi_cwossbaw_init(isi);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize cwossbaw: %d\n", wet);
		goto eww_pm;
	}

	fow (i = 0; i < isi->pdata->num_channews; ++i) {
		wet = mxc_isi_pipe_init(isi, i);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to initiawize pipe%u: %d\n", i,
				wet);
			goto eww_xbaw;
		}
	}

	wet = mxc_isi_v4w2_init(isi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize V4W2: %d\n", wet);
		goto eww_xbaw;
	}

	mxc_isi_debug_init(isi);

	wetuwn 0;

eww_xbaw:
	mxc_isi_cwossbaw_cweanup(&isi->cwossbaw);
eww_pm:
	pm_wuntime_disabwe(isi->dev);
	wetuwn wet;
}

static int mxc_isi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mxc_isi_dev *isi = pwatfowm_get_dwvdata(pdev);
	unsigned int i;

	mxc_isi_debug_cweanup(isi);

	fow (i = 0; i < isi->pdata->num_channews; ++i) {
		stwuct mxc_isi_pipe *pipe = &isi->pipes[i];

		mxc_isi_pipe_cweanup(pipe);
	}

	mxc_isi_cwossbaw_cweanup(&isi->cwossbaw);
	mxc_isi_v4w2_cweanup(isi);

	pm_wuntime_disabwe(isi->dev);

	wetuwn 0;
}

static const stwuct of_device_id mxc_isi_of_match[] = {
	{ .compatibwe = "fsw,imx8mn-isi", .data = &mxc_imx8mn_data },
	{ .compatibwe = "fsw,imx8mp-isi", .data = &mxc_imx8mp_data },
	{ .compatibwe = "fsw,imx93-isi", .data = &mxc_imx93_data },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mxc_isi_of_match);

static stwuct pwatfowm_dwivew mxc_isi_dwivew = {
	.pwobe		= mxc_isi_pwobe,
	.wemove		= mxc_isi_wemove,
	.dwivew = {
		.of_match_tabwe = mxc_isi_of_match,
		.name		= MXC_ISI_DWIVEW_NAME,
		.pm		= pm_ptw(&mxc_isi_pm_ops),
	}
};
moduwe_pwatfowm_dwivew(mxc_isi_dwivew);

MODUWE_AWIAS("ISI");
MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("IMX8 Image Sensing Intewface dwivew");
MODUWE_WICENSE("GPW");
