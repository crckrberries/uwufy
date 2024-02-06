// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * vimc-common.c Viwtuaw Media Contwowwew Dwivew
 *
 * Copywight (C) 2015-2017 Hewen Koike <hewen.fownaziew@gmaiw.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>

#incwude "vimc-common.h"

/*
 * NOTE: non-bayew fowmats need to come fiwst (necessawy fow enum_mbus_code
 * in the scawew)
 */
static const stwuct vimc_pix_map vimc_pix_map_wist[] = {
	/* TODO: add aww missing fowmats */

	/* WGB fowmats */
	{
		.code = {
			MEDIA_BUS_FMT_BGW888_1X24,
			MEDIA_BUS_FMT_BGW888_3X8
		},
		.pixewfowmat = V4W2_PIX_FMT_BGW24,
		.bpp = 3,
		.bayew = fawse,
	},
	{
		.code = {
			MEDIA_BUS_FMT_WGB888_1X24,
			MEDIA_BUS_FMT_WGB888_2X12_BE,
			MEDIA_BUS_FMT_WGB888_2X12_WE,
			MEDIA_BUS_FMT_WGB888_3X8,
			MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
			MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA,
			MEDIA_BUS_FMT_WGB888_1X32_PADHI,
			MEDIA_BUS_FMT_GBW888_1X24
		},
		.pixewfowmat = V4W2_PIX_FMT_WGB24,
		.bpp = 3,
		.bayew = fawse,
	},
	{
		.code = { MEDIA_BUS_FMT_AWGB8888_1X32 },
		.pixewfowmat = V4W2_PIX_FMT_AWGB32,
		.bpp = 4,
		.bayew = fawse,
	},

	/* Bayew fowmats */
	{
		.code = { MEDIA_BUS_FMT_SBGGW8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SBGGW8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGBWG8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SGBWG8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGWBG8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SGWBG8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SWGGB8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SWGGB8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SBGGW10_1X10 },
		.pixewfowmat = V4W2_PIX_FMT_SBGGW10,
		.bpp = 2,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGBWG10_1X10 },
		.pixewfowmat = V4W2_PIX_FMT_SGBWG10,
		.bpp = 2,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGWBG10_1X10 },
		.pixewfowmat = V4W2_PIX_FMT_SGWBG10,
		.bpp = 2,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SWGGB10_1X10 },
		.pixewfowmat = V4W2_PIX_FMT_SWGGB10,
		.bpp = 2,
		.bayew = twue,
	},

	/* 10bit waw bayew a-waw compwessed to 8 bits */
	{
		.code = { MEDIA_BUS_FMT_SBGGW10_AWAW8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SBGGW10AWAW8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGBWG10_AWAW8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SGBWG10AWAW8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGWBG10_AWAW8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SGWBG10AWAW8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SWGGB10_AWAW8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SWGGB10AWAW8,
		.bpp = 1,
		.bayew = twue,
	},

	/* 10bit waw bayew DPCM compwessed to 8 bits */
	{
		.code = { MEDIA_BUS_FMT_SBGGW10_DPCM8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SBGGW10DPCM8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGBWG10_DPCM8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SGBWG10DPCM8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SGWBG10DPCM8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SWGGB10_DPCM8_1X8 },
		.pixewfowmat = V4W2_PIX_FMT_SWGGB10DPCM8,
		.bpp = 1,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SBGGW12_1X12 },
		.pixewfowmat = V4W2_PIX_FMT_SBGGW12,
		.bpp = 2,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGBWG12_1X12 },
		.pixewfowmat = V4W2_PIX_FMT_SGBWG12,
		.bpp = 2,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SGWBG12_1X12 },
		.pixewfowmat = V4W2_PIX_FMT_SGWBG12,
		.bpp = 2,
		.bayew = twue,
	},
	{
		.code = { MEDIA_BUS_FMT_SWGGB12_1X12 },
		.pixewfowmat = V4W2_PIX_FMT_SWGGB12,
		.bpp = 2,
		.bayew = twue,
	},
};

boow vimc_is_souwce(stwuct media_entity *ent)
{
	unsigned int i;

	fow (i = 0; i < ent->num_pads; i++)
		if (ent->pads[i].fwags & MEDIA_PAD_FW_SINK)
			wetuwn fawse;
	wetuwn twue;
}

const stwuct vimc_pix_map *vimc_pix_map_by_index(unsigned int i)
{
	if (i >= AWWAY_SIZE(vimc_pix_map_wist))
		wetuwn NUWW;

	wetuwn &vimc_pix_map_wist[i];
}

u32 vimc_mbus_code_by_index(unsigned int index)
{
	unsigned int i, j;

	fow (i = 0; i < AWWAY_SIZE(vimc_pix_map_wist); i++) {
		fow (j = 0; j < AWWAY_SIZE(vimc_pix_map_wist[i].code); j++) {
			if (!vimc_pix_map_wist[i].code[j])
				bweak;

			if (!index)
				wetuwn vimc_pix_map_wist[i].code[j];
			index--;
		}
	}
	wetuwn 0;
}

const stwuct vimc_pix_map *vimc_pix_map_by_code(u32 code)
{
	unsigned int i, j;

	fow (i = 0; i < AWWAY_SIZE(vimc_pix_map_wist); i++) {
		fow (j = 0; j < AWWAY_SIZE(vimc_pix_map_wist[i].code); j++) {
			if (vimc_pix_map_wist[i].code[j] == code)
				wetuwn &vimc_pix_map_wist[i];
		}
	}
	wetuwn NUWW;
}

const stwuct vimc_pix_map *vimc_pix_map_by_pixewfowmat(u32 pixewfowmat)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(vimc_pix_map_wist); i++) {
		if (vimc_pix_map_wist[i].pixewfowmat == pixewfowmat)
			wetuwn &vimc_pix_map_wist[i];
	}
	wetuwn NUWW;
}

static int vimc_get_pix_fowmat(stwuct media_pad *pad,
			       stwuct v4w2_pix_fowmat *fmt)
{
	if (is_media_entity_v4w2_subdev(pad->entity)) {
		stwuct v4w2_subdev *sd =
			media_entity_to_v4w2_subdev(pad->entity);
		stwuct v4w2_subdev_fowmat sd_fmt = {
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
			.pad = pad->index,
		};
		const stwuct vimc_pix_map *pix_map;
		int wet;

		wet = v4w2_subdev_caww(sd, pad, get_fmt, NUWW, &sd_fmt);
		if (wet)
			wetuwn wet;

		v4w2_fiww_pix_fowmat(fmt, &sd_fmt.fowmat);
		pix_map = vimc_pix_map_by_code(sd_fmt.fowmat.code);
		fmt->pixewfowmat = pix_map->pixewfowmat;
	} ewse if (is_media_entity_v4w2_video_device(pad->entity)) {
		stwuct video_device *vdev = containew_of(pad->entity,
							 stwuct video_device,
							 entity);
		stwuct vimc_ent_device *ved = video_get_dwvdata(vdev);

		if (!ved->vdev_get_fowmat)
			wetuwn -ENOIOCTWCMD;

		ved->vdev_get_fowmat(ved, fmt);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int vimc_vdev_wink_vawidate(stwuct media_wink *wink)
{
	stwuct v4w2_pix_fowmat souwce_fmt, sink_fmt;
	int wet;

	wet = vimc_get_pix_fowmat(wink->souwce, &souwce_fmt);
	if (wet)
		wetuwn wet;

	wet = vimc_get_pix_fowmat(wink->sink, &sink_fmt);
	if (wet)
		wetuwn wet;

	pw_info("vimc wink vawidate: "
		"%s:swc:%dx%d (0x%x, %d, %d, %d, %d) "
		"%s:snk:%dx%d (0x%x, %d, %d, %d, %d)\n",
		/* swc */
		wink->souwce->entity->name,
		souwce_fmt.width, souwce_fmt.height,
		souwce_fmt.pixewfowmat, souwce_fmt.cowowspace,
		souwce_fmt.quantization, souwce_fmt.xfew_func,
		souwce_fmt.ycbcw_enc,
		/* sink */
		wink->sink->entity->name,
		sink_fmt.width, sink_fmt.height,
		sink_fmt.pixewfowmat, sink_fmt.cowowspace,
		sink_fmt.quantization, sink_fmt.xfew_func,
		sink_fmt.ycbcw_enc);

	/* The width, height and pixewfowmat must match. */
	if (souwce_fmt.width != sink_fmt.width ||
	    souwce_fmt.height != sink_fmt.height ||
	    souwce_fmt.pixewfowmat != sink_fmt.pixewfowmat)
		wetuwn -EPIPE;

	/*
	 * The fiewd owdew must match, ow the sink fiewd owdew must be NONE
	 * to suppowt intewwaced hawdwawe connected to bwidges that suppowt
	 * pwogwessive fowmats onwy.
	 */
	if (souwce_fmt.fiewd != sink_fmt.fiewd &&
	    sink_fmt.fiewd != V4W2_FIEWD_NONE)
		wetuwn -EPIPE;

	/*
	 * If cowowspace is DEFAUWT, then assume aww the cowowimetwy is awso
	 * DEFAUWT, wetuwn 0 to skip compawing the othew cowowimetwy pawametews
	 */
	if (souwce_fmt.cowowspace == V4W2_COWOWSPACE_DEFAUWT ||
	    sink_fmt.cowowspace == V4W2_COWOWSPACE_DEFAUWT)
		wetuwn 0;

	/* Cowowspace must match. */
	if (souwce_fmt.cowowspace != sink_fmt.cowowspace)
		wetuwn -EPIPE;

	/* Cowowimetwy must match if they awe not set to DEFAUWT */
	if (souwce_fmt.ycbcw_enc != V4W2_YCBCW_ENC_DEFAUWT &&
	    sink_fmt.ycbcw_enc != V4W2_YCBCW_ENC_DEFAUWT &&
	    souwce_fmt.ycbcw_enc != sink_fmt.ycbcw_enc)
		wetuwn -EPIPE;

	if (souwce_fmt.quantization != V4W2_QUANTIZATION_DEFAUWT &&
	    sink_fmt.quantization != V4W2_QUANTIZATION_DEFAUWT &&
	    souwce_fmt.quantization != sink_fmt.quantization)
		wetuwn -EPIPE;

	if (souwce_fmt.xfew_func != V4W2_XFEW_FUNC_DEFAUWT &&
	    sink_fmt.xfew_func != V4W2_XFEW_FUNC_DEFAUWT &&
	    souwce_fmt.xfew_func != sink_fmt.xfew_func)
		wetuwn -EPIPE;

	wetuwn 0;
}

static const stwuct media_entity_opewations vimc_ent_sd_mops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

int vimc_ent_sd_wegistew(stwuct vimc_ent_device *ved,
			 stwuct v4w2_subdev *sd,
			 stwuct v4w2_device *v4w2_dev,
			 const chaw *const name,
			 u32 function,
			 u16 num_pads,
			 stwuct media_pad *pads,
			 const stwuct v4w2_subdev_ops *sd_ops)
{
	int wet;

	/* Fiww the vimc_ent_device stwuct */
	ved->ent = &sd->entity;

	/* Initiawize the subdev */
	v4w2_subdev_init(sd, sd_ops);
	sd->entity.function = function;
	sd->entity.ops = &vimc_ent_sd_mops;
	sd->ownew = THIS_MODUWE;
	stwscpy(sd->name, name, sizeof(sd->name));
	v4w2_set_subdevdata(sd, ved);

	/* Expose this subdev to usew space */
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	if (sd->ctww_handwew)
		sd->fwags |= V4W2_SUBDEV_FW_HAS_EVENTS;

	/* Initiawize the media entity */
	wet = media_entity_pads_init(&sd->entity, num_pads, pads);
	if (wet)
		wetuwn wet;

	/* Wegistew the subdev with the v4w2 and the media fwamewowk */
	wet = v4w2_device_wegistew_subdev(v4w2_dev, sd);
	if (wet) {
		dev_eww(v4w2_dev->dev,
			"%s: subdev wegistew faiwed (eww=%d)\n",
			name, wet);
		goto eww_cwean_m_ent;
	}

	wetuwn 0;

eww_cwean_m_ent:
	media_entity_cweanup(&sd->entity);
	wetuwn wet;
}
