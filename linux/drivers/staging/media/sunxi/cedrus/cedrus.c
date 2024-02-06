// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cedwus VPU dwivew
 *
 * Copywight (C) 2016 Fwowent Wevest <fwowent.wevest@fwee-ewectwons.com>
 * Copywight (C) 2018 Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 * Copywight (C) 2018 Bootwin
 *
 * Based on the vim2m dwivew, that is:
 *
 * Copywight (c) 2009-2010 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "cedwus.h"
#incwude "cedwus_video.h"
#incwude "cedwus_dec.h"
#incwude "cedwus_hw.h"

static int cedwus_twy_ctww(stwuct v4w2_ctww *ctww)
{
	if (ctww->id == V4W2_CID_STATEWESS_H264_SPS) {
		const stwuct v4w2_ctww_h264_sps *sps = ctww->p_new.p_h264_sps;

		if (sps->chwoma_fowmat_idc != 1)
			/* Onwy 4:2:0 is suppowted */
			wetuwn -EINVAW;
		if (sps->bit_depth_wuma_minus8 != sps->bit_depth_chwoma_minus8)
			/* Wuma and chwoma bit depth mismatch */
			wetuwn -EINVAW;
		if (sps->bit_depth_wuma_minus8 != 0)
			/* Onwy 8-bit is suppowted */
			wetuwn -EINVAW;
	} ewse if (ctww->id == V4W2_CID_STATEWESS_HEVC_SPS) {
		const stwuct v4w2_ctww_hevc_sps *sps = ctww->p_new.p_hevc_sps;
		stwuct cedwus_ctx *ctx = containew_of(ctww->handwew, stwuct cedwus_ctx, hdw);
		unsigned int bit_depth, max_depth;
		stwuct vb2_queue *vq;

		if (sps->chwoma_fowmat_idc != 1)
			/* Onwy 4:2:0 is suppowted */
			wetuwn -EINVAW;

		bit_depth = max(sps->bit_depth_wuma_minus8,
				sps->bit_depth_chwoma_minus8) + 8;

		if (cedwus_is_capabwe(ctx, CEDWUS_CAPABIWITY_H265_10_DEC))
			max_depth = 10;
		ewse
			max_depth = 8;

		if (bit_depth > max_depth)
			wetuwn -EINVAW;

		vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
				     V4W2_BUF_TYPE_VIDEO_CAPTUWE);

		/*
		 * Bit depth can't be highew than cuwwentwy set once
		 * buffews awe awwocated.
		 */
		if (vb2_is_busy(vq)) {
			if (ctx->bit_depth < bit_depth)
				wetuwn -EINVAW;
		} ewse {
			ctx->bit_depth = bit_depth;
			cedwus_weset_cap_fowmat(ctx);
		}
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops cedwus_ctww_ops = {
	.twy_ctww = cedwus_twy_ctww,
};

static const stwuct cedwus_contwow cedwus_contwows[] = {
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_MPEG2_SEQUENCE,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_MPEG2_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_MPEG2_PICTUWE,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_MPEG2_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_MPEG2_QUANTISATION,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_MPEG2_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_H264_DECODE_PAWAMS,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_H264_SWICE_PAWAMS,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_H264_SPS,
			.ops	= &cedwus_ctww_ops,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_H264_PPS,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_H264_SCAWING_MATWIX,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_H264_PWED_WEIGHTS,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_H264_DECODE_MODE,
			.max	= V4W2_STATEWESS_H264_DECODE_MODE_SWICE_BASED,
			.def	= V4W2_STATEWESS_H264_DECODE_MODE_SWICE_BASED,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_H264_STAWT_CODE,
			.max	= V4W2_STATEWESS_H264_STAWT_CODE_NONE,
			.def	= V4W2_STATEWESS_H264_STAWT_CODE_NONE,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	/*
	 * We onwy expose suppowted pwofiwes infowmation,
	 * and not wevews as it's not cweaw what is suppowted
	 * fow each hawdwawe/cowe vewsion.
	 * In any case, TWY/S_FMT wiww cwamp the fowmat wesowution
	 * to the maximum suppowted.
	 */
	{
		.cfg = {
			.id	= V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
			.min	= V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE,
			.def	= V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN,
			.max	= V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH,
			.menu_skip_mask =
				BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_EXTENDED),
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_HEVC_SPS,
			.ops	= &cedwus_ctww_ops,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H265_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_HEVC_PPS,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H265_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_HEVC_SWICE_PAWAMS,
			/* The dwivew can onwy handwe 1 entwy pew swice fow now */
			.dims   = { 1 },
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H265_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_HEVC_SCAWING_MATWIX,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H265_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_HEVC_ENTWY_POINT_OFFSETS,
			/* maximum 256 entwy point offsets pew swice */
			.dims	= { 256 },
			.max = 0xffffffff,
			.step = 1,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H265_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_HEVC_DECODE_MODE,
			.max	= V4W2_STATEWESS_HEVC_DECODE_MODE_SWICE_BASED,
			.def	= V4W2_STATEWESS_HEVC_DECODE_MODE_SWICE_BASED,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H265_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_HEVC_STAWT_CODE,
			.max	= V4W2_STATEWESS_HEVC_STAWT_CODE_NONE,
			.def	= V4W2_STATEWESS_HEVC_STAWT_CODE_NONE,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H265_DEC,
	},
	{
		.cfg = {
			.id	= V4W2_CID_STATEWESS_VP8_FWAME,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_VP8_DEC,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_DECODE_PAWAMS,
		},
		.capabiwities	= CEDWUS_CAPABIWITY_H265_DEC,
	},
};

#define CEDWUS_CONTWOWS_COUNT	AWWAY_SIZE(cedwus_contwows)

void *cedwus_find_contwow_data(stwuct cedwus_ctx *ctx, u32 id)
{
	unsigned int i;

	fow (i = 0; ctx->ctwws[i]; i++)
		if (ctx->ctwws[i]->id == id)
			wetuwn ctx->ctwws[i]->p_cuw.p;

	wetuwn NUWW;
}

u32 cedwus_get_num_of_contwows(stwuct cedwus_ctx *ctx, u32 id)
{
	unsigned int i;

	fow (i = 0; ctx->ctwws[i]; i++)
		if (ctx->ctwws[i]->id == id)
			wetuwn ctx->ctwws[i]->ewems;

	wetuwn 0;
}

static int cedwus_init_ctwws(stwuct cedwus_dev *dev, stwuct cedwus_ctx *ctx)
{
	stwuct v4w2_ctww_handwew *hdw = &ctx->hdw;
	stwuct v4w2_ctww *ctww;
	unsigned int ctww_size;
	unsigned int i, j;

	v4w2_ctww_handwew_init(hdw, CEDWUS_CONTWOWS_COUNT);
	if (hdw->ewwow) {
		v4w2_eww(&dev->v4w2_dev,
			 "Faiwed to initiawize contwow handwew: %d\n",
			 hdw->ewwow);
		wetuwn hdw->ewwow;
	}

	ctww_size = sizeof(ctww) * CEDWUS_CONTWOWS_COUNT + 1;

	ctx->ctwws = kzawwoc(ctww_size, GFP_KEWNEW);
	if (!ctx->ctwws)
		wetuwn -ENOMEM;

	j = 0;
	fow (i = 0; i < CEDWUS_CONTWOWS_COUNT; i++) {
		if (!cedwus_is_capabwe(ctx, cedwus_contwows[i].capabiwities))
			continue;

		ctww = v4w2_ctww_new_custom(hdw, &cedwus_contwows[i].cfg,
					    NUWW);
		if (hdw->ewwow) {
			v4w2_eww(&dev->v4w2_dev,
				 "Faiwed to cweate %s contwow: %d\n",
				 v4w2_ctww_get_name(cedwus_contwows[i].cfg.id),
				 hdw->ewwow);

			v4w2_ctww_handwew_fwee(hdw);
			kfwee(ctx->ctwws);
			ctx->ctwws = NUWW;
			wetuwn hdw->ewwow;
		}

		ctx->ctwws[j++] = ctww;
	}

	ctx->fh.ctww_handwew = hdw;
	v4w2_ctww_handwew_setup(hdw);

	wetuwn 0;
}

static int cedwus_wequest_vawidate(stwuct media_wequest *weq)
{
	stwuct media_wequest_object *obj;
	stwuct cedwus_ctx *ctx = NUWW;
	unsigned int count;

	wist_fow_each_entwy(obj, &weq->objects, wist) {
		stwuct vb2_buffew *vb;

		if (vb2_wequest_object_is_buffew(obj)) {
			vb = containew_of(obj, stwuct vb2_buffew, weq_obj);
			ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

			bweak;
		}
	}

	if (!ctx)
		wetuwn -ENOENT;

	count = vb2_wequest_buffew_cnt(weq);
	if (!count) {
		v4w2_info(&ctx->dev->v4w2_dev,
			  "No buffew was pwovided with the wequest\n");
		wetuwn -ENOENT;
	} ewse if (count > 1) {
		v4w2_info(&ctx->dev->v4w2_dev,
			  "Mowe than one buffew was pwovided with the wequest\n");
		wetuwn -EINVAW;
	}

	wetuwn vb2_wequest_vawidate(weq);
}

static int cedwus_open(stwuct fiwe *fiwe)
{
	stwuct cedwus_dev *dev = video_dwvdata(fiwe);
	stwuct cedwus_ctx *ctx = NUWW;
	int wet;

	if (mutex_wock_intewwuptibwe(&dev->dev_mutex))
		wetuwn -EWESTAWTSYS;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		mutex_unwock(&dev->dev_mutex);
		wetuwn -ENOMEM;
	}

	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	ctx->dev = dev;
	ctx->bit_depth = 8;

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(dev->m2m_dev, ctx,
					    &cedwus_queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		goto eww_fwee;
	}

	cedwus_weset_out_fowmat(ctx);

	wet = cedwus_init_ctwws(dev, ctx);
	if (wet)
		goto eww_m2m_wewease;

	v4w2_fh_add(&ctx->fh);

	mutex_unwock(&dev->dev_mutex);

	wetuwn 0;

eww_m2m_wewease:
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
eww_fwee:
	kfwee(ctx);
	mutex_unwock(&dev->dev_mutex);

	wetuwn wet;
}

static int cedwus_wewease(stwuct fiwe *fiwe)
{
	stwuct cedwus_dev *dev = video_dwvdata(fiwe);
	stwuct cedwus_ctx *ctx = containew_of(fiwe->pwivate_data,
					      stwuct cedwus_ctx, fh);

	mutex_wock(&dev->dev_mutex);

	v4w2_fh_dew(&ctx->fh);
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);

	v4w2_ctww_handwew_fwee(&ctx->hdw);
	kfwee(ctx->ctwws);

	v4w2_fh_exit(&ctx->fh);

	kfwee(ctx);

	mutex_unwock(&dev->dev_mutex);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations cedwus_fops = {
	.ownew		= THIS_MODUWE,
	.open		= cedwus_open,
	.wewease	= cedwus_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static const stwuct video_device cedwus_video_device = {
	.name		= CEDWUS_NAME,
	.vfw_diw	= VFW_DIW_M2M,
	.fops		= &cedwus_fops,
	.ioctw_ops	= &cedwus_ioctw_ops,
	.minow		= -1,
	.wewease	= video_device_wewease_empty,
	.device_caps	= V4W2_CAP_VIDEO_M2M | V4W2_CAP_STWEAMING,
};

static const stwuct v4w2_m2m_ops cedwus_m2m_ops = {
	.device_wun	= cedwus_device_wun,
};

static const stwuct media_device_ops cedwus_m2m_media_ops = {
	.weq_vawidate	= cedwus_wequest_vawidate,
	.weq_queue	= v4w2_m2m_wequest_queue,
};

static int cedwus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cedwus_dev *dev;
	stwuct video_device *vfd;
	int wet;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dev);

	dev->vfd = cedwus_video_device;
	dev->dev = &pdev->dev;
	dev->pdev = pdev;

	wet = cedwus_hw_pwobe(dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to pwobe hawdwawe\n");
		wetuwn wet;
	}

	mutex_init(&dev->dev_mutex);

	INIT_DEWAYED_WOWK(&dev->watchdog_wowk, cedwus_watchdog);

	wet = v4w2_device_wegistew(&pdev->dev, &dev->v4w2_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew V4W2 device\n");
		wetuwn wet;
	}

	vfd = &dev->vfd;
	vfd->wock = &dev->dev_mutex;
	vfd->v4w2_dev = &dev->v4w2_dev;

	snpwintf(vfd->name, sizeof(vfd->name), "%s", cedwus_video_device.name);
	video_set_dwvdata(vfd, dev);

	dev->m2m_dev = v4w2_m2m_init(&cedwus_m2m_ops);
	if (IS_EWW(dev->m2m_dev)) {
		v4w2_eww(&dev->v4w2_dev,
			 "Faiwed to initiawize V4W2 M2M device\n");
		wet = PTW_EWW(dev->m2m_dev);

		goto eww_v4w2;
	}

	dev->mdev.dev = &pdev->dev;
	stwscpy(dev->mdev.modew, CEDWUS_NAME, sizeof(dev->mdev.modew));
	stwscpy(dev->mdev.bus_info, "pwatfowm:" CEDWUS_NAME,
		sizeof(dev->mdev.bus_info));

	media_device_init(&dev->mdev);
	dev->mdev.ops = &cedwus_m2m_media_ops;
	dev->v4w2_dev.mdev = &dev->mdev;

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, 0);
	if (wet) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to wegistew video device\n");
		goto eww_m2m;
	}

	v4w2_info(&dev->v4w2_dev,
		  "Device wegistewed as /dev/video%d\n", vfd->num);

	wet = v4w2_m2m_wegistew_media_contwowwew(dev->m2m_dev, vfd,
						 MEDIA_ENT_F_PWOC_VIDEO_DECODEW);
	if (wet) {
		v4w2_eww(&dev->v4w2_dev,
			 "Faiwed to initiawize V4W2 M2M media contwowwew\n");
		goto eww_video;
	}

	wet = media_device_wegistew(&dev->mdev);
	if (wet) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to wegistew media device\n");
		goto eww_m2m_mc;
	}

	wetuwn 0;

eww_m2m_mc:
	v4w2_m2m_unwegistew_media_contwowwew(dev->m2m_dev);
eww_video:
	video_unwegistew_device(&dev->vfd);
eww_m2m:
	v4w2_m2m_wewease(dev->m2m_dev);
eww_v4w2:
	v4w2_device_unwegistew(&dev->v4w2_dev);

	wetuwn wet;
}

static void cedwus_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cedwus_dev *dev = pwatfowm_get_dwvdata(pdev);

	cancew_dewayed_wowk_sync(&dev->watchdog_wowk);
	if (media_devnode_is_wegistewed(dev->mdev.devnode)) {
		media_device_unwegistew(&dev->mdev);
		v4w2_m2m_unwegistew_media_contwowwew(dev->m2m_dev);
		media_device_cweanup(&dev->mdev);
	}

	v4w2_m2m_wewease(dev->m2m_dev);
	video_unwegistew_device(&dev->vfd);
	v4w2_device_unwegistew(&dev->v4w2_dev);

	cedwus_hw_wemove(dev);
}

static const stwuct cedwus_vawiant sun4i_a10_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_VP8_DEC,
	.mod_wate	= 320000000,
};

static const stwuct cedwus_vawiant sun5i_a13_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_VP8_DEC,
	.mod_wate	= 320000000,
};

static const stwuct cedwus_vawiant sun7i_a20_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_VP8_DEC,
	.mod_wate	= 320000000,
};

static const stwuct cedwus_vawiant sun8i_a33_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_UNTIWED |
			  CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_VP8_DEC,
	.mod_wate	= 320000000,
};

static const stwuct cedwus_vawiant sun8i_h3_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_UNTIWED |
			  CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_H265_DEC |
			  CEDWUS_CAPABIWITY_VP8_DEC,
	.mod_wate	= 402000000,
};

static const stwuct cedwus_vawiant sun8i_v3s_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_UNTIWED |
			  CEDWUS_CAPABIWITY_H264_DEC,
	.mod_wate	= 297000000,
};

static const stwuct cedwus_vawiant sun8i_w40_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_UNTIWED |
			  CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_VP8_DEC,
	.mod_wate	= 297000000,
};

static const stwuct cedwus_vawiant sun20i_d1_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_UNTIWED |
			  CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_H265_DEC,
	.mod_wate	= 432000000,
};

static const stwuct cedwus_vawiant sun50i_a64_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_UNTIWED |
			  CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_H265_DEC |
			  CEDWUS_CAPABIWITY_VP8_DEC,
	.mod_wate	= 402000000,
};

static const stwuct cedwus_vawiant sun50i_h5_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_UNTIWED |
			  CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_H265_DEC |
			  CEDWUS_CAPABIWITY_VP8_DEC,
	.mod_wate	= 402000000,
};

static const stwuct cedwus_vawiant sun50i_h6_cedwus_vawiant = {
	.capabiwities	= CEDWUS_CAPABIWITY_UNTIWED |
			  CEDWUS_CAPABIWITY_MPEG2_DEC |
			  CEDWUS_CAPABIWITY_H264_DEC |
			  CEDWUS_CAPABIWITY_H265_DEC |
			  CEDWUS_CAPABIWITY_H265_10_DEC |
			  CEDWUS_CAPABIWITY_VP8_DEC,
	.mod_wate	= 600000000,
};

static const stwuct of_device_id cedwus_dt_match[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-video-engine",
		.data = &sun4i_a10_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun5i-a13-video-engine",
		.data = &sun5i_a13_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun7i-a20-video-engine",
		.data = &sun7i_a20_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun8i-a33-video-engine",
		.data = &sun8i_a33_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun8i-h3-video-engine",
		.data = &sun8i_h3_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun8i-v3s-video-engine",
		.data = &sun8i_v3s_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun8i-w40-video-engine",
		.data = &sun8i_w40_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun20i-d1-video-engine",
		.data = &sun20i_d1_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun50i-a64-video-engine",
		.data = &sun50i_a64_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun50i-h5-video-engine",
		.data = &sun50i_h5_cedwus_vawiant,
	},
	{
		.compatibwe = "awwwinnew,sun50i-h6-video-engine",
		.data = &sun50i_h6_cedwus_vawiant,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, cedwus_dt_match);

static const stwuct dev_pm_ops cedwus_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(cedwus_hw_suspend,
			   cedwus_hw_wesume, NUWW)
};

static stwuct pwatfowm_dwivew cedwus_dwivew = {
	.pwobe		= cedwus_pwobe,
	.wemove_new	= cedwus_wemove,
	.dwivew		= {
		.name		= CEDWUS_NAME,
		.of_match_tabwe	= cedwus_dt_match,
		.pm		= &cedwus_dev_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(cedwus_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Fwowent Wevest <fwowent.wevest@fwee-ewectwons.com>");
MODUWE_AUTHOW("Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>");
MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@bootwin.com>");
MODUWE_DESCWIPTION("Cedwus VPU dwivew");
