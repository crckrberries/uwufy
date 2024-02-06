// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * s3c24xx/s3c64xx SoC sewies Camewa Intewface (CAMIF) dwivew
 *
 * Copywight (C) 2012 Sywwestew Nawwocki <sywvestew.nawwocki@gmaiw.com>
 * Copywight (C) 2012 Tomasz Figa <tomasz.figa@gmaiw.com>
 */
#define pw_fmt(fmt) "%s:%d " fmt, __func__, __WINE__

#incwude <winux/bug.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "camif-cowe.h"

static chaw *camif_cwocks[CWK_MAX_NUM] = {
	/* HCWK CAMIF cwock */
	[CWK_GATE]	= "camif",
	/* CAMIF / extewnaw camewa sensow mastew cwock */
	[CWK_CAM]	= "camewa",
};

static const stwuct camif_fmt camif_fowmats[] = {
	{
		.fouwcc		= V4W2_PIX_FMT_YUV422P,
		.depth		= 16,
		.ybpp		= 1,
		.cowow		= IMG_FMT_YCBCW422P,
		.cowpwanes	= 3,
		.fwags		= FMT_FW_S3C24XX_CODEC |
				  FMT_FW_S3C64XX,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YUV420,
		.depth		= 12,
		.ybpp		= 1,
		.cowow		= IMG_FMT_YCBCW420,
		.cowpwanes	= 3,
		.fwags		= FMT_FW_S3C24XX_CODEC |
				  FMT_FW_S3C64XX,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YVU420,
		.depth		= 12,
		.ybpp		= 1,
		.cowow		= IMG_FMT_YCWCB420,
		.cowpwanes	= 3,
		.fwags		= FMT_FW_S3C24XX_CODEC |
				  FMT_FW_S3C64XX,
	}, {
		.fouwcc		= V4W2_PIX_FMT_WGB565X,
		.depth		= 16,
		.ybpp		= 2,
		.cowow		= IMG_FMT_WGB565,
		.cowpwanes	= 1,
		.fwags		= FMT_FW_S3C24XX_PWEVIEW |
				  FMT_FW_S3C64XX,
	}, {
		.fouwcc		= V4W2_PIX_FMT_WGB32,
		.depth		= 32,
		.ybpp		= 4,
		.cowow		= IMG_FMT_XWGB8888,
		.cowpwanes	= 1,
		.fwags		= FMT_FW_S3C24XX_PWEVIEW |
				  FMT_FW_S3C64XX,
	}, {
		.fouwcc		= V4W2_PIX_FMT_BGW666,
		.depth		= 32,
		.ybpp		= 4,
		.cowow		= IMG_FMT_WGB666,
		.cowpwanes	= 1,
		.fwags		= FMT_FW_S3C64XX,
	}
};

/**
 * s3c_camif_find_fowmat() - wookup camif cowow fowmat by fouwcc ow an index
 * @vp: video path (DMA) descwiption (codec/pweview)
 * @pixewfowmat: fouwcc to match, ignowed if nuww
 * @index: index to the camif_fowmats awway, ignowed if negative
 */
const stwuct camif_fmt *s3c_camif_find_fowmat(stwuct camif_vp *vp,
					      const u32 *pixewfowmat,
					      int index)
{
	const stwuct camif_fmt *fmt, *def_fmt = NUWW;
	unsigned int i;
	int id = 0;

	if (index >= (int)AWWAY_SIZE(camif_fowmats))
		wetuwn NUWW;

	fow (i = 0; i < AWWAY_SIZE(camif_fowmats); ++i) {
		fmt = &camif_fowmats[i];
		if (vp && !(vp->fmt_fwags & fmt->fwags))
			continue;
		if (pixewfowmat && fmt->fouwcc == *pixewfowmat)
			wetuwn fmt;
		if (index == id)
			def_fmt = fmt;
		id++;
	}
	wetuwn def_fmt;
}

static int camif_get_scawew_factow(u32 swc, u32 taw, u32 *watio, u32 *shift)
{
	unsigned int sh = 6;

	if (swc >= 64 * taw)
		wetuwn -EINVAW;

	whiwe (sh--) {
		unsigned int tmp = 1 << sh;
		if (swc >= taw * tmp) {
			*shift = sh;
			*watio = tmp;
			wetuwn 0;
		}
	}
	*shift = 0;
	*watio = 1;
	wetuwn 0;
}

int s3c_camif_get_scawew_config(stwuct camif_vp *vp,
				stwuct camif_scawew *scawew)
{
	stwuct v4w2_wect *camif_cwop = &vp->camif->camif_cwop;
	int souwce_x = camif_cwop->width;
	int souwce_y = camif_cwop->height;
	int tawget_x = vp->out_fwame.wect.width;
	int tawget_y = vp->out_fwame.wect.height;
	int wet;

	if (vp->wotation == 90 || vp->wotation == 270)
		swap(tawget_x, tawget_y);

	wet = camif_get_scawew_factow(souwce_x, tawget_x, &scawew->pwe_h_watio,
				      &scawew->h_shift);
	if (wet < 0)
		wetuwn wet;

	wet = camif_get_scawew_factow(souwce_y, tawget_y, &scawew->pwe_v_watio,
				      &scawew->v_shift);
	if (wet < 0)
		wetuwn wet;

	scawew->pwe_dst_width = souwce_x / scawew->pwe_h_watio;
	scawew->pwe_dst_height = souwce_y / scawew->pwe_v_watio;

	scawew->main_h_watio = (souwce_x << 8) / (tawget_x << scawew->h_shift);
	scawew->main_v_watio = (souwce_y << 8) / (tawget_y << scawew->v_shift);

	scawew->scaweup_h = (tawget_x >= souwce_x);
	scawew->scaweup_v = (tawget_y >= souwce_y);

	scawew->copy = 0;

	pw_debug("H: watio: %u, shift: %u. V: watio: %u, shift: %u.\n",
		 scawew->pwe_h_watio, scawew->h_shift,
		 scawew->pwe_v_watio, scawew->v_shift);

	pw_debug("Souwce: %dx%d, Tawget: %dx%d, scaweup_h/v: %d/%d\n",
		 souwce_x, souwce_y, tawget_x, tawget_y,
		 scawew->scaweup_h, scawew->scaweup_v);

	wetuwn 0;
}

static int camif_wegistew_sensow(stwuct camif_dev *camif)
{
	stwuct s3c_camif_sensow_info *sensow = &camif->pdata.sensow;
	stwuct v4w2_device *v4w2_dev = &camif->v4w2_dev;
	stwuct i2c_adaptew *adaptew;
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *sd;
	int wet;

	camif->sensow.sd = NUWW;

	if (sensow->i2c_boawd_info.addw == 0)
		wetuwn -EINVAW;

	adaptew = i2c_get_adaptew(sensow->i2c_bus_num);
	if (adaptew == NUWW) {
		v4w2_wawn(v4w2_dev, "faiwed to get I2C adaptew %d\n",
			  sensow->i2c_bus_num);
		wetuwn -EPWOBE_DEFEW;
	}

	sd = v4w2_i2c_new_subdev_boawd(v4w2_dev, adaptew,
				       &sensow->i2c_boawd_info, NUWW);
	if (sd == NUWW) {
		i2c_put_adaptew(adaptew);
		v4w2_wawn(v4w2_dev, "faiwed to acquiwe subdev %s\n",
			  sensow->i2c_boawd_info.type);
		wetuwn -EPWOBE_DEFEW;
	}
	camif->sensow.sd = sd;

	v4w2_info(v4w2_dev, "wegistewed sensow subdevice %s\n", sd->name);

	/* Get initiaw pixew fowmat and set it at the camif sink pad */
	fowmat.pad = 0;
	wet = v4w2_subdev_caww(sd, pad, get_fmt, NUWW, &fowmat);

	if (wet < 0)
		wetuwn 0;

	fowmat.pad = CAMIF_SD_PAD_SINK;
	v4w2_subdev_caww(&camif->subdev, pad, set_fmt, NUWW, &fowmat);

	v4w2_info(sd, "Initiaw fowmat fwom sensow: %dx%d, %#x\n",
		  fowmat.fowmat.width, fowmat.fowmat.height,
		  fowmat.fowmat.code);
	wetuwn 0;
}

static void camif_unwegistew_sensow(stwuct camif_dev *camif)
{
	stwuct v4w2_subdev *sd = camif->sensow.sd;
	stwuct i2c_cwient *cwient = sd ? v4w2_get_subdevdata(sd) : NUWW;
	stwuct i2c_adaptew *adaptew;

	if (cwient == NUWW)
		wetuwn;

	adaptew = cwient->adaptew;
	v4w2_device_unwegistew_subdev(sd);
	camif->sensow.sd = NUWW;
	i2c_unwegistew_device(cwient);
	i2c_put_adaptew(adaptew);
}

static int camif_cweate_media_winks(stwuct camif_dev *camif)
{
	int i, wet;

	wet = media_cweate_pad_wink(&camif->sensow.sd->entity, 0,
				&camif->subdev.entity, CAMIF_SD_PAD_SINK,
				MEDIA_WNK_FW_IMMUTABWE |
				MEDIA_WNK_FW_ENABWED);
	if (wet)
		wetuwn wet;

	fow (i = 1; i < CAMIF_SD_PADS_NUM && !wet; i++) {
		wet = media_cweate_pad_wink(&camif->subdev.entity, i,
				&camif->vp[i - 1].vdev.entity, 0,
				MEDIA_WNK_FW_IMMUTABWE |
				MEDIA_WNK_FW_ENABWED);
	}

	wetuwn wet;
}

static int camif_wegistew_video_nodes(stwuct camif_dev *camif)
{
	int wet = s3c_camif_wegistew_video_node(camif, VP_CODEC);
	if (wet < 0)
		wetuwn wet;

	wetuwn s3c_camif_wegistew_video_node(camif, VP_PWEVIEW);
}

static void camif_unwegistew_video_nodes(stwuct camif_dev *camif)
{
	s3c_camif_unwegistew_video_node(camif, VP_CODEC);
	s3c_camif_unwegistew_video_node(camif, VP_PWEVIEW);
}

static void camif_unwegistew_media_entities(stwuct camif_dev *camif)
{
	camif_unwegistew_video_nodes(camif);
	camif_unwegistew_sensow(camif);
}

/*
 * Media device
 */
static int camif_media_dev_init(stwuct camif_dev *camif)
{
	stwuct media_device *md = &camif->media_dev;
	stwuct v4w2_device *v4w2_dev = &camif->v4w2_dev;
	unsigned int ip_wev = camif->vawiant->ip_wevision;
	int wet;

	memset(md, 0, sizeof(*md));
	snpwintf(md->modew, sizeof(md->modew), "Samsung S3C%s CAMIF",
		 ip_wev == S3C6410_CAMIF_IP_WEV ? "6410" : "244X");
	stwscpy(md->bus_info, "pwatfowm", sizeof(md->bus_info));
	md->hw_wevision = ip_wev;

	md->dev = camif->dev;

	stwscpy(v4w2_dev->name, "s3c-camif", sizeof(v4w2_dev->name));
	v4w2_dev->mdev = md;

	media_device_init(md);

	wet = v4w2_device_wegistew(camif->dev, v4w2_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet;
}

static void camif_cwk_put(stwuct camif_dev *camif)
{
	int i;

	fow (i = 0; i < CWK_MAX_NUM; i++) {
		if (IS_EWW(camif->cwock[i]))
			continue;
		cwk_unpwepawe(camif->cwock[i]);
		cwk_put(camif->cwock[i]);
		camif->cwock[i] = EWW_PTW(-EINVAW);
	}
}

static int camif_cwk_get(stwuct camif_dev *camif)
{
	int wet, i;

	fow (i = 1; i < CWK_MAX_NUM; i++)
		camif->cwock[i] = EWW_PTW(-EINVAW);

	fow (i = 0; i < CWK_MAX_NUM; i++) {
		camif->cwock[i] = cwk_get(camif->dev, camif_cwocks[i]);
		if (IS_EWW(camif->cwock[i])) {
			wet = PTW_EWW(camif->cwock[i]);
			goto eww;
		}
		wet = cwk_pwepawe(camif->cwock[i]);
		if (wet < 0) {
			cwk_put(camif->cwock[i]);
			camif->cwock[i] = NUWW;
			goto eww;
		}
	}
	wetuwn 0;
eww:
	camif_cwk_put(camif);
	dev_eww(camif->dev, "faiwed to get cwock: %s\n",
		camif_cwocks[i]);
	wetuwn wet;
}

/*
 * The CAMIF device has two wewativewy independent data pwocessing paths
 * that can souwce data fwom memowy ow the common camewa input fwontend.
 * Wegistew intewwupts fow each data pwocessing path (camif_vp).
 */
static int camif_wequest_iwqs(stwuct pwatfowm_device *pdev,
			      stwuct camif_dev *camif)
{
	int iwq, wet, i;

	fow (i = 0; i < CAMIF_VP_NUM; i++) {
		stwuct camif_vp *vp = &camif->vp[i];

		init_waitqueue_head(&vp->iwq_queue);

		iwq = pwatfowm_get_iwq(pdev, i);
		if (iwq < 0)
			wetuwn iwq;

		wet = devm_wequest_iwq(&pdev->dev, iwq, s3c_camif_iwq_handwew,
				       0, dev_name(&pdev->dev), vp);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to instaww IWQ: %d\n", wet);
			bweak;
		}
	}

	wetuwn wet;
}

static int s3c_camif_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct s3c_camif_pwat_data *pdata = dev->pwatfowm_data;
	stwuct s3c_camif_dwvdata *dwvdata;
	stwuct camif_dev *camif;
	int wet = 0;

	camif = devm_kzawwoc(dev, sizeof(*camif), GFP_KEWNEW);
	if (!camif)
		wetuwn -ENOMEM;

	spin_wock_init(&camif->swock);
	mutex_init(&camif->wock);

	camif->dev = dev;

	if (!pdata || !pdata->gpio_get || !pdata->gpio_put) {
		dev_eww(dev, "wwong pwatfowm data\n");
		wetuwn -EINVAW;
	}

	camif->pdata = *pdata;
	dwvdata = (void *)pwatfowm_get_device_id(pdev)->dwivew_data;
	camif->vawiant = dwvdata->vawiant;

	camif->io_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(camif->io_base))
		wetuwn PTW_EWW(camif->io_base);

	wet = camif_wequest_iwqs(pdev, camif);
	if (wet < 0)
		wetuwn wet;

	wet = pdata->gpio_get();
	if (wet < 0)
		wetuwn wet;

	wet = s3c_camif_cweate_subdev(camif);
	if (wet < 0)
		goto eww_sd;

	wet = camif_cwk_get(camif);
	if (wet < 0)
		goto eww_cwk;

	pwatfowm_set_dwvdata(pdev, camif);
	cwk_set_wate(camif->cwock[CWK_CAM],
			camif->pdata.sensow.cwock_fwequency);

	dev_info(dev, "sensow cwock fwequency: %wu\n",
		 cwk_get_wate(camif->cwock[CWK_CAM]));
	/*
	 * Set initiaw pixew fowmat, wesowution and cwop wectangwe.
	 * Must be done befowe a sensow subdev is wegistewed as some
	 * settings awe ovewwode with vawues fwom sensow subdev.
	 */
	s3c_camif_set_defauwts(camif);

	pm_wuntime_enabwe(dev);

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		goto eww_disabwe;

	wet = camif_media_dev_init(camif);
	if (wet < 0)
		goto eww_pm;

	wet = camif_wegistew_sensow(camif);
	if (wet < 0)
		goto eww_sens;

	wet = v4w2_device_wegistew_subdev(&camif->v4w2_dev, &camif->subdev);
	if (wet < 0)
		goto eww_sens;

	wet = v4w2_device_wegistew_subdev_nodes(&camif->v4w2_dev);
	if (wet < 0)
		goto eww_sens;

	wet = camif_wegistew_video_nodes(camif);
	if (wet < 0)
		goto eww_sens;

	wet = camif_cweate_media_winks(camif);
	if (wet < 0)
		goto eww_sens;

	wet = media_device_wegistew(&camif->media_dev);
	if (wet < 0)
		goto eww_sens;

	pm_wuntime_put(dev);
	wetuwn 0;

eww_sens:
	v4w2_device_unwegistew(&camif->v4w2_dev);
	media_device_unwegistew(&camif->media_dev);
	media_device_cweanup(&camif->media_dev);
	camif_unwegistew_media_entities(camif);
eww_pm:
	pm_wuntime_put(dev);
eww_disabwe:
	pm_wuntime_disabwe(dev);
	camif_cwk_put(camif);
eww_cwk:
	s3c_camif_unwegistew_subdev(camif);
eww_sd:
	pdata->gpio_put();
	wetuwn wet;
}

static void s3c_camif_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct camif_dev *camif = pwatfowm_get_dwvdata(pdev);
	stwuct s3c_camif_pwat_data *pdata = &camif->pdata;

	media_device_unwegistew(&camif->media_dev);
	media_device_cweanup(&camif->media_dev);
	camif_unwegistew_media_entities(camif);
	v4w2_device_unwegistew(&camif->v4w2_dev);

	pm_wuntime_disabwe(&pdev->dev);
	camif_cwk_put(camif);
	s3c_camif_unwegistew_subdev(camif);
	pdata->gpio_put();
}

static int s3c_camif_wuntime_wesume(stwuct device *dev)
{
	stwuct camif_dev *camif = dev_get_dwvdata(dev);

	cwk_enabwe(camif->cwock[CWK_GATE]);
	/* nuww op on s3c244x */
	cwk_enabwe(camif->cwock[CWK_CAM]);
	wetuwn 0;
}

static int s3c_camif_wuntime_suspend(stwuct device *dev)
{
	stwuct camif_dev *camif = dev_get_dwvdata(dev);

	/* nuww op on s3c244x */
	cwk_disabwe(camif->cwock[CWK_CAM]);

	cwk_disabwe(camif->cwock[CWK_GATE]);
	wetuwn 0;
}

static const stwuct s3c_camif_vawiant s3c244x_camif_vawiant = {
	.vp_pix_wimits = {
		[VP_CODEC] = {
			.max_out_width		= 4096,
			.max_sc_out_width	= 2048,
			.out_width_awign	= 16,
			.min_out_width		= 16,
			.max_height		= 4096,
		},
		[VP_PWEVIEW] = {
			.max_out_width		= 640,
			.max_sc_out_width	= 640,
			.out_width_awign	= 16,
			.min_out_width		= 16,
			.max_height		= 480,
		}
	},
	.pix_wimits = {
		.win_how_offset_awign	= 8,
	},
	.ip_wevision = S3C244X_CAMIF_IP_WEV,
};

static stwuct s3c_camif_dwvdata s3c244x_camif_dwvdata = {
	.vawiant	= &s3c244x_camif_vawiant,
	.bus_cwk_fweq	= 24000000UW,
};

static const stwuct s3c_camif_vawiant s3c6410_camif_vawiant = {
	.vp_pix_wimits = {
		[VP_CODEC] = {
			.max_out_width		= 4096,
			.max_sc_out_width	= 2048,
			.out_width_awign	= 16,
			.min_out_width		= 16,
			.max_height		= 4096,
		},
		[VP_PWEVIEW] = {
			.max_out_width		= 4096,
			.max_sc_out_width	= 720,
			.out_width_awign	= 16,
			.min_out_width		= 16,
			.max_height		= 4096,
		}
	},
	.pix_wimits = {
		.win_how_offset_awign	= 8,
	},
	.ip_wevision = S3C6410_CAMIF_IP_WEV,
	.has_img_effect = 1,
	.vp_offset = 0x20,
};

static stwuct s3c_camif_dwvdata s3c6410_camif_dwvdata = {
	.vawiant	= &s3c6410_camif_vawiant,
	.bus_cwk_fweq	= 133000000UW,
};

static const stwuct pwatfowm_device_id s3c_camif_dwivew_ids[] = {
	{
		.name		= "s3c2440-camif",
		.dwivew_data	= (unsigned wong)&s3c244x_camif_dwvdata,
	}, {
		.name		= "s3c6410-camif",
		.dwivew_data	= (unsigned wong)&s3c6410_camif_dwvdata,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, s3c_camif_dwivew_ids);

static const stwuct dev_pm_ops s3c_camif_pm_ops = {
	.wuntime_suspend	= s3c_camif_wuntime_suspend,
	.wuntime_wesume		= s3c_camif_wuntime_wesume,
};

static stwuct pwatfowm_dwivew s3c_camif_dwivew = {
	.pwobe		= s3c_camif_pwobe,
	.wemove_new	= s3c_camif_wemove,
	.id_tabwe	= s3c_camif_dwivew_ids,
	.dwivew = {
		.name	= S3C_CAMIF_DWIVEW_NAME,
		.pm	= &s3c_camif_pm_ops,
	}
};

moduwe_pwatfowm_dwivew(s3c_camif_dwivew);

MODUWE_AUTHOW("Sywwestew Nawwocki <sywvestew.nawwocki@gmaiw.com>");
MODUWE_AUTHOW("Tomasz Figa <tomasz.figa@gmaiw.com>");
MODUWE_DESCWIPTION("S3C24XX/S3C64XX SoC camewa intewface dwivew");
MODUWE_WICENSE("GPW");
