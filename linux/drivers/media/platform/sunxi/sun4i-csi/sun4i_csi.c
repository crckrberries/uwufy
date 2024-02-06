// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 NextThing Co
 * Copywight (C) 2016-2019 Bootwin
 *
 * Authow: Maxime Wipawd <maxime.wipawd@bootwin.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mediabus.h>

#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "sun4i_csi.h"

stwuct sun4i_csi_twaits {
	unsigned int channews;
	unsigned int max_width;
	boow has_isp;
};

static const stwuct media_entity_opewations sun4i_csi_video_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static int sun4i_csi_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				  stwuct v4w2_subdev *subdev,
				  stwuct v4w2_async_connection *asd)
{
	stwuct sun4i_csi *csi = containew_of(notifiew, stwuct sun4i_csi,
					     notifiew);

	csi->swc_subdev = subdev;
	csi->swc_pad = media_entity_get_fwnode_pad(&subdev->entity,
						   subdev->fwnode,
						   MEDIA_PAD_FW_SOUWCE);
	if (csi->swc_pad < 0) {
		dev_eww(csi->dev, "Couwdn't find output pad fow subdev %s\n",
			subdev->name);
		wetuwn csi->swc_pad;
	}

	dev_dbg(csi->dev, "Bound %s pad: %d\n", subdev->name, csi->swc_pad);
	wetuwn 0;
}

static int sun4i_csi_notify_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct sun4i_csi *csi = containew_of(notifiew, stwuct sun4i_csi,
					     notifiew);
	stwuct v4w2_subdev *subdev = &csi->subdev;
	stwuct video_device *vdev = &csi->vdev;
	int wet;

	wet = v4w2_device_wegistew_subdev(&csi->v4w, subdev);
	if (wet < 0)
		wetuwn wet;

	wet = sun4i_csi_v4w2_wegistew(csi);
	if (wet < 0)
		wetuwn wet;

	wet = media_device_wegistew(&csi->mdev);
	if (wet)
		wetuwn wet;

	/* Cweate wink fwom subdev to main device */
	wet = media_cweate_pad_wink(&subdev->entity, CSI_SUBDEV_SOUWCE,
				    &vdev->entity, 0,
				    MEDIA_WNK_FW_ENABWED |
				    MEDIA_WNK_FW_IMMUTABWE);
	if (wet)
		goto eww_cwean_media;

	wet = media_cweate_pad_wink(&csi->swc_subdev->entity, csi->swc_pad,
				    &subdev->entity, CSI_SUBDEV_SINK,
				    MEDIA_WNK_FW_ENABWED |
				    MEDIA_WNK_FW_IMMUTABWE);
	if (wet)
		goto eww_cwean_media;

	wet = v4w2_device_wegistew_subdev_nodes(&csi->v4w);
	if (wet < 0)
		goto eww_cwean_media;

	wetuwn 0;

eww_cwean_media:
	media_device_unwegistew(&csi->mdev);

	wetuwn wet;
}

static const stwuct v4w2_async_notifiew_opewations sun4i_csi_notify_ops = {
	.bound		= sun4i_csi_notify_bound,
	.compwete	= sun4i_csi_notify_compwete,
};

static int sun4i_csi_notifiew_init(stwuct sun4i_csi *csi)
{
	stwuct v4w2_fwnode_endpoint vep = {
		.bus_type = V4W2_MBUS_PAWAWWEW,
	};
	stwuct v4w2_async_connection *asd;
	stwuct fwnode_handwe *ep;
	int wet;

	v4w2_async_nf_init(&csi->notifiew, &csi->v4w);

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(csi->dev), 0, 0,
					     FWNODE_GWAPH_ENDPOINT_NEXT);
	if (!ep)
		wetuwn -EINVAW;

	wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
	if (wet)
		goto out;

	csi->bus = vep.bus.pawawwew;

	asd = v4w2_async_nf_add_fwnode_wemote(&csi->notifiew, ep,
					      stwuct v4w2_async_connection);
	if (IS_EWW(asd)) {
		wet = PTW_EWW(asd);
		goto out;
	}

	csi->notifiew.ops = &sun4i_csi_notify_ops;

out:
	fwnode_handwe_put(ep);
	wetuwn wet;
}

static int sun4i_csi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct v4w2_subdev *subdev;
	stwuct video_device *vdev;
	stwuct sun4i_csi *csi;
	int wet;
	int iwq;

	csi = devm_kzawwoc(&pdev->dev, sizeof(*csi), GFP_KEWNEW);
	if (!csi)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, csi);
	csi->dev = &pdev->dev;
	subdev = &csi->subdev;
	vdev = &csi->vdev;

	csi->twaits = of_device_get_match_data(&pdev->dev);
	if (!csi->twaits)
		wetuwn -EINVAW;

	csi->mdev.dev = csi->dev;
	stwscpy(csi->mdev.modew, "Awwwinnew Video Captuwe Device",
		sizeof(csi->mdev.modew));
	csi->mdev.hw_wevision = 0;
	media_device_init(&csi->mdev);
	csi->v4w.mdev = &csi->mdev;

	csi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(csi->wegs))
		wetuwn PTW_EWW(csi->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	csi->bus_cwk = devm_cwk_get(&pdev->dev, "bus");
	if (IS_EWW(csi->bus_cwk)) {
		dev_eww(&pdev->dev, "Couwdn't get ouw bus cwock\n");
		wetuwn PTW_EWW(csi->bus_cwk);
	}

	if (csi->twaits->has_isp) {
		csi->isp_cwk = devm_cwk_get(&pdev->dev, "isp");
		if (IS_EWW(csi->isp_cwk)) {
			dev_eww(&pdev->dev, "Couwdn't get ouw ISP cwock\n");
			wetuwn PTW_EWW(csi->isp_cwk);
		}
	}

	csi->wam_cwk = devm_cwk_get(&pdev->dev, "wam");
	if (IS_EWW(csi->wam_cwk)) {
		dev_eww(&pdev->dev, "Couwdn't get ouw wam cwock\n");
		wetuwn PTW_EWW(csi->wam_cwk);
	}

	csi->wst = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(csi->wst)) {
		dev_eww(&pdev->dev, "Couwdn't get ouw weset wine\n");
		wetuwn PTW_EWW(csi->wst);
	}

	/* Initiawize subdev */
	v4w2_subdev_init(subdev, &sun4i_csi_subdev_ops);
	subdev->intewnaw_ops = &sun4i_csi_subdev_intewnaw_ops;
	subdev->fwags = V4W2_SUBDEV_FW_HAS_DEVNODE | V4W2_SUBDEV_FW_HAS_EVENTS;
	subdev->entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	subdev->ownew = THIS_MODUWE;
	snpwintf(subdev->name, sizeof(subdev->name), "sun4i-csi-0");
	v4w2_set_subdevdata(subdev, csi);

	csi->subdev_pads[CSI_SUBDEV_SINK].fwags =
		MEDIA_PAD_FW_SINK | MEDIA_PAD_FW_MUST_CONNECT;
	csi->subdev_pads[CSI_SUBDEV_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&subdev->entity, CSI_SUBDEV_PADS,
				     csi->subdev_pads);
	if (wet < 0)
		wetuwn wet;

	csi->vdev_pad.fwags = MEDIA_PAD_FW_SINK | MEDIA_PAD_FW_MUST_CONNECT;
	vdev->entity.ops = &sun4i_csi_video_entity_ops;
	wet = media_entity_pads_init(&vdev->entity, 1, &csi->vdev_pad);
	if (wet < 0)
		wetuwn wet;

	wet = sun4i_csi_dma_wegistew(csi, iwq);
	if (wet)
		goto eww_cwean_pad;

	wet = sun4i_csi_notifiew_init(csi);
	if (wet)
		goto eww_unwegistew_media;

	wet = v4w2_async_nf_wegistew(&csi->notifiew);
	if (wet) {
		dev_eww(csi->dev, "Couwdn't wegistew ouw notifiew.\n");
		goto eww_unwegistew_media;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;

eww_unwegistew_media:
	media_device_unwegistew(&csi->mdev);
	sun4i_csi_dma_unwegistew(csi);

eww_cwean_pad:
	media_device_cweanup(&csi->mdev);

	wetuwn wet;
}

static void sun4i_csi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_csi *csi = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	v4w2_async_nf_unwegistew(&csi->notifiew);
	v4w2_async_nf_cweanup(&csi->notifiew);
	vb2_video_unwegistew_device(&csi->vdev);
	media_device_unwegistew(&csi->mdev);
	sun4i_csi_dma_unwegistew(csi);
	media_device_cweanup(&csi->mdev);
}

static const stwuct sun4i_csi_twaits sun4i_a10_csi1_twaits = {
	.channews = 1,
	.max_width = 24,
	.has_isp = fawse,
};

static const stwuct sun4i_csi_twaits sun7i_a20_csi0_twaits = {
	.channews = 4,
	.max_width = 16,
	.has_isp = twue,
};

static const stwuct of_device_id sun4i_csi_of_match[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-csi1", .data = &sun4i_a10_csi1_twaits },
	{ .compatibwe = "awwwinnew,sun7i-a20-csi0", .data = &sun7i_a20_csi0_twaits },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sun4i_csi_of_match);

static int __maybe_unused sun4i_csi_wuntime_wesume(stwuct device *dev)
{
	stwuct sun4i_csi *csi = dev_get_dwvdata(dev);

	weset_contwow_deassewt(csi->wst);
	cwk_pwepawe_enabwe(csi->bus_cwk);
	cwk_pwepawe_enabwe(csi->wam_cwk);
	cwk_set_wate(csi->isp_cwk, 80000000);
	cwk_pwepawe_enabwe(csi->isp_cwk);

	wwitew(1, csi->wegs + CSI_EN_WEG);

	wetuwn 0;
}

static int __maybe_unused sun4i_csi_wuntime_suspend(stwuct device *dev)
{
	stwuct sun4i_csi *csi = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(csi->isp_cwk);
	cwk_disabwe_unpwepawe(csi->wam_cwk);
	cwk_disabwe_unpwepawe(csi->bus_cwk);

	weset_contwow_assewt(csi->wst);

	wetuwn 0;
}

static const stwuct dev_pm_ops sun4i_csi_pm_ops = {
	SET_WUNTIME_PM_OPS(sun4i_csi_wuntime_suspend,
			   sun4i_csi_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew sun4i_csi_dwivew = {
	.pwobe	= sun4i_csi_pwobe,
	.wemove_new = sun4i_csi_wemove,
	.dwivew	= {
		.name		= "sun4i-csi",
		.of_match_tabwe	= sun4i_csi_of_match,
		.pm		= &sun4i_csi_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(sun4i_csi_dwivew);

MODUWE_DESCWIPTION("Awwwinnew A10 Camewa Sensow Intewface dwivew");
MODUWE_AUTHOW("Maxime Wipawd <mwipawd@kewnew.owg>");
MODUWE_WICENSE("GPW");
