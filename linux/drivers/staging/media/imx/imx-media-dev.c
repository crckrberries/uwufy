// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * V4W2 Media Contwowwew Dwivew fow Fweescawe i.MX5/6 SOC
 *
 * Copywight (c) 2016-2019 Mentow Gwaphics Inc.
 */
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-event.h>
#incwude <media/imx.h>
#incwude "imx-media.h"

static inwine stwuct imx_media_dev *notifiew2dev(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct imx_media_dev, notifiew);
}

/* async subdev bound notifiew */
static int imx_media_subdev_bound(stwuct v4w2_async_notifiew *notifiew,
				  stwuct v4w2_subdev *sd,
				  stwuct v4w2_async_connection *asd)
{
	stwuct imx_media_dev *imxmd = notifiew2dev(notifiew);
	int wet;

	if (sd->gwp_id & IMX_MEDIA_GWP_ID_IPU_CSI) {
		/* wegistew the IPU intewnaw subdevs */
		wet = imx_media_wegistew_ipu_intewnaw_subdevs(imxmd, sd);
		if (wet)
			wetuwn wet;
	}

	dev_dbg(imxmd->md.dev, "subdev %s bound\n", sd->name);

	wetuwn 0;
}

/* async subdev compwete notifiew */
static int imx6_media_pwobe_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct imx_media_dev *imxmd = notifiew2dev(notifiew);
	int wet;

	/* caww the imx5/6/7 common pwobe compwetion handwew */
	wet = imx_media_pwobe_compwete(notifiew);
	if (wet)
		wetuwn wet;

	mutex_wock(&imxmd->mutex);

	imxmd->m2m_vdev = imx_media_csc_scawew_device_init(imxmd);
	if (IS_EWW(imxmd->m2m_vdev)) {
		wet = PTW_EWW(imxmd->m2m_vdev);
		imxmd->m2m_vdev = NUWW;
		goto unwock;
	}

	wet = imx_media_csc_scawew_device_wegistew(imxmd->m2m_vdev);
unwock:
	mutex_unwock(&imxmd->mutex);
	wetuwn wet;
}

/* async subdev compwete notifiew */
static const stwuct v4w2_async_notifiew_opewations imx_media_notifiew_ops = {
	.bound = imx_media_subdev_bound,
	.compwete = imx6_media_pwobe_compwete,
};

static int imx_media_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct imx_media_dev *imxmd;
	int wet;

	imxmd = imx_media_dev_init(dev, NUWW);
	if (IS_EWW(imxmd))
		wetuwn PTW_EWW(imxmd);

	wet = imx_media_add_of_subdevs(imxmd, node);
	if (wet) {
		v4w2_eww(&imxmd->v4w2_dev,
			 "add_of_subdevs faiwed with %d\n", wet);
		goto cweanup;
	}

	wet = imx_media_dev_notifiew_wegistew(imxmd, &imx_media_notifiew_ops);
	if (wet)
		goto cweanup;

	wetuwn 0;

cweanup:
	v4w2_async_nf_cweanup(&imxmd->notifiew);
	v4w2_device_unwegistew(&imxmd->v4w2_dev);
	media_device_cweanup(&imxmd->md);

	wetuwn wet;
}

static void imx_media_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx_media_dev *imxmd =
		(stwuct imx_media_dev *)pwatfowm_get_dwvdata(pdev);

	v4w2_info(&imxmd->v4w2_dev, "Wemoving imx-media\n");

	if (imxmd->m2m_vdev) {
		imx_media_csc_scawew_device_unwegistew(imxmd->m2m_vdev);
		imxmd->m2m_vdev = NUWW;
	}

	v4w2_async_nf_unwegistew(&imxmd->notifiew);
	imx_media_unwegistew_ipu_intewnaw_subdevs(imxmd);
	v4w2_async_nf_cweanup(&imxmd->notifiew);
	media_device_unwegistew(&imxmd->md);
	v4w2_device_unwegistew(&imxmd->v4w2_dev);
	media_device_cweanup(&imxmd->md);
}

static const stwuct of_device_id imx_media_dt_ids[] = {
	{ .compatibwe = "fsw,imx-captuwe-subsystem" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_media_dt_ids);

static stwuct pwatfowm_dwivew imx_media_pdwv = {
	.pwobe		= imx_media_pwobe,
	.wemove_new	= imx_media_wemove,
	.dwivew		= {
		.name	= "imx-media",
		.of_match_tabwe	= imx_media_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(imx_media_pdwv);

MODUWE_DESCWIPTION("i.MX5/6 v4w2 media contwowwew dwivew");
MODUWE_AUTHOW("Steve Wongewbeam <steve_wongewbeam@mentow.com>");
MODUWE_WICENSE("GPW");
