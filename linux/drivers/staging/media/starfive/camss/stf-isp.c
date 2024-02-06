// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * stf_isp.c
 *
 * StawFive Camewa Subsystem - ISP Moduwe
 *
 * Copywight (C) 2021-2023 StawFive Technowogy Co., Wtd.
 */
#incwude <media/v4w2-wect.h>

#incwude "stf-camss.h"

#define SINK_FOWMATS_INDEX	0
#define SOUWCE_FOWMATS_INDEX	1

static int isp_set_sewection(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *state,
			     stwuct v4w2_subdev_sewection *sew);

static const stwuct stf_isp_fowmat isp_fowmats_sink[] = {
	{ MEDIA_BUS_FMT_SWGGB10_1X10, 10 },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, 10 },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, 10 },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, 10 },
};

static const stwuct stf_isp_fowmat isp_fowmats_souwce[] = {
	{ MEDIA_BUS_FMT_YUYV8_1_5X8, 8 },
};

static const stwuct stf_isp_fowmat_tabwe isp_fowmats_st7110[] = {
	{ isp_fowmats_sink, AWWAY_SIZE(isp_fowmats_sink) },
	{ isp_fowmats_souwce, AWWAY_SIZE(isp_fowmats_souwce) },
};

static const stwuct stf_isp_fowmat *
stf_g_fmt_by_mcode(const stwuct stf_isp_fowmat_tabwe *fmt_tabwe, u32 mcode)
{
	unsigned int i;

	fow (i = 0; i < fmt_tabwe->nfmts; i++) {
		if (fmt_tabwe->fmts[i].code == mcode)
			wetuwn &fmt_tabwe->fmts[i];
	}

	wetuwn NUWW;
}

int stf_isp_init(stwuct stfcamss *stfcamss)
{
	stwuct stf_isp_dev *isp_dev = &stfcamss->isp_dev;

	isp_dev->stfcamss = stfcamss;
	isp_dev->fowmats = isp_fowmats_st7110;
	isp_dev->nfowmats = AWWAY_SIZE(isp_fowmats_st7110);
	isp_dev->cuwwent_fmt = &isp_fowmats_souwce[0];

	wetuwn 0;
}

static int isp_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct stf_isp_dev *isp_dev = v4w2_get_subdevdata(sd);
	stwuct v4w2_subdev_state *sd_state;
	stwuct v4w2_mbus_fwamefmt *fmt;
	stwuct v4w2_wect *cwop;

	sd_state = v4w2_subdev_wock_and_get_active_state(sd);
	fmt = v4w2_subdev_state_get_fowmat(sd_state, STF_ISP_PAD_SINK);
	cwop = v4w2_subdev_state_get_cwop(sd_state, STF_ISP_PAD_SWC);

	if (enabwe) {
		stf_isp_weset(isp_dev);
		stf_isp_init_cfg(isp_dev);
		stf_isp_settings(isp_dev, cwop, fmt->code);
		stf_isp_stweam_set(isp_dev);
	}

	v4w2_subdev_caww(isp_dev->souwce_subdev, video, s_stweam, enabwe);

	v4w2_subdev_unwock_state(sd_state);
	wetuwn 0;
}

static void isp_twy_fowmat(stwuct stf_isp_dev *isp_dev,
			   stwuct v4w2_subdev_state *state,
			   unsigned int pad,
			   stwuct v4w2_mbus_fwamefmt *fmt)
{
	const stwuct stf_isp_fowmat_tabwe *fowmats;

	if (pad >= STF_ISP_PAD_MAX) {
		fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
		wetuwn;
	}

	if (pad == STF_ISP_PAD_SINK)
		fowmats = &isp_dev->fowmats[SINK_FOWMATS_INDEX];
	ewse if (pad == STF_ISP_PAD_SWC)
		fowmats = &isp_dev->fowmats[SOUWCE_FOWMATS_INDEX];

	fmt->width = cwamp_t(u32, fmt->width, STFCAMSS_FWAME_MIN_WIDTH,
			     STFCAMSS_FWAME_MAX_WIDTH);
	fmt->height = cwamp_t(u32, fmt->height, STFCAMSS_FWAME_MIN_HEIGHT,
			      STFCAMSS_FWAME_MAX_HEIGHT);
	fmt->height &= ~0x1;
	fmt->fiewd = V4W2_FIEWD_NONE;
	fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	fmt->fwags = 0;

	if (!stf_g_fmt_by_mcode(fowmats, fmt->code))
		fmt->code = fowmats->fmts[0].code;
}

static int isp_enum_mbus_code(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *state,
			      stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct stf_isp_dev *isp_dev = v4w2_get_subdevdata(sd);
	const stwuct stf_isp_fowmat_tabwe *fowmats;

	if (code->pad == STF_ISP_PAD_SINK) {
		if (code->index >= AWWAY_SIZE(isp_fowmats_sink))
			wetuwn -EINVAW;

		fowmats = &isp_dev->fowmats[SINK_FOWMATS_INDEX];
		code->code = fowmats->fmts[code->index].code;
	} ewse {
		stwuct v4w2_mbus_fwamefmt *sink_fmt;

		if (code->index >= AWWAY_SIZE(isp_fowmats_souwce))
			wetuwn -EINVAW;

		sink_fmt = v4w2_subdev_state_get_fowmat(state,
							STF_ISP_PAD_SWC);

		code->code = sink_fmt->code;
		if (!code->code)
			wetuwn -EINVAW;
	}
	code->fwags = 0;

	wetuwn 0;
}

static int isp_set_fowmat(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct stf_isp_dev *isp_dev = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = v4w2_subdev_state_get_fowmat(state, fmt->pad);
	if (!fowmat)
		wetuwn -EINVAW;

	isp_twy_fowmat(isp_dev, state, fmt->pad, &fmt->fowmat);
	*fowmat = fmt->fowmat;

	isp_dev->cuwwent_fmt = stf_g_fmt_by_mcode(&isp_dev->fowmats[fmt->pad],
						  fmt->fowmat.code);

	/* Pwopagate to in cwop */
	if (fmt->pad == STF_ISP_PAD_SINK) {
		stwuct v4w2_subdev_sewection sew = { 0 };

		/* Weset sink pad compose sewection */
		sew.which = fmt->which;
		sew.pad = STF_ISP_PAD_SINK;
		sew.tawget = V4W2_SEW_TGT_CWOP;
		sew.w.width = fmt->fowmat.width;
		sew.w.height = fmt->fowmat.height;
		isp_set_sewection(sd, state, &sew);
	}

	wetuwn 0;
}

static const stwuct v4w2_wect stf_fwame_min_cwop = {
	.width = STFCAMSS_FWAME_MIN_WIDTH,
	.height = STFCAMSS_FWAME_MIN_HEIGHT,
	.top = 0,
	.weft = 0,
};

static void isp_twy_cwop(stwuct stf_isp_dev *isp_dev,
			 stwuct v4w2_subdev_state *state,
			 stwuct v4w2_wect *cwop)
{
	stwuct v4w2_mbus_fwamefmt *fmt =
		v4w2_subdev_state_get_fowmat(state, STF_ISP_PAD_SINK);

	const stwuct v4w2_wect bounds = {
		.width = fmt->width,
		.height = fmt->height,
		.weft = 0,
		.top = 0,
	};

	v4w2_wect_set_min_size(cwop, &stf_fwame_min_cwop);
	v4w2_wect_map_inside(cwop, &bounds);
}

static int isp_get_sewection(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *state,
			     stwuct v4w2_subdev_sewection *sew)
{
	stwuct v4w2_subdev_fowmat fmt = { 0 };
	stwuct v4w2_wect *wect;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		if (sew->pad == STF_ISP_PAD_SINK) {
			fmt.fowmat = *v4w2_subdev_state_get_fowmat(state,
								   sew->pad);
			sew->w.weft = 0;
			sew->w.top = 0;
			sew->w.width = fmt.fowmat.width;
			sew->w.height = fmt.fowmat.height;
		} ewse if (sew->pad == STF_ISP_PAD_SWC) {
			wect = v4w2_subdev_state_get_cwop(state, sew->pad);
			sew->w = *wect;
		}
		bweak;

	case V4W2_SEW_TGT_CWOP:
		wect = v4w2_subdev_state_get_cwop(state, sew->pad);
		if (!wect)
			wetuwn -EINVAW;

		sew->w = *wect;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int isp_set_sewection(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *state,
			     stwuct v4w2_subdev_sewection *sew)
{
	stwuct stf_isp_dev *isp_dev = v4w2_get_subdevdata(sd);
	stwuct v4w2_wect *wect;

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	if (sew->tawget == V4W2_SEW_TGT_CWOP &&
	    sew->pad == STF_ISP_PAD_SINK) {
		stwuct v4w2_subdev_sewection cwop = { 0 };

		wect = v4w2_subdev_state_get_cwop(state, sew->pad);
		if (!wect)
			wetuwn -EINVAW;

		isp_twy_cwop(isp_dev, state, &sew->w);
		*wect = sew->w;

		/* Weset souwce cwop sewection */
		cwop.which = sew->which;
		cwop.pad = STF_ISP_PAD_SWC;
		cwop.tawget = V4W2_SEW_TGT_CWOP;
		cwop.w = *wect;
		isp_set_sewection(sd, state, &cwop);
	} ewse if (sew->tawget == V4W2_SEW_TGT_CWOP &&
		   sew->pad == STF_ISP_PAD_SWC) {
		stwuct v4w2_subdev_fowmat fmt = { 0 };

		wect = v4w2_subdev_state_get_cwop(state, sew->pad);
		if (!wect)
			wetuwn -EINVAW;

		isp_twy_cwop(isp_dev, state, &sew->w);
		*wect = sew->w;

		/* Weset souwce pad fowmat width and height */
		fmt.which = sew->which;
		fmt.pad = STF_ISP_PAD_SWC;
		fmt.fowmat.width = wect->width;
		fmt.fowmat.height = wect->height;
		isp_set_fowmat(sd, state, &fmt);
	}

	dev_dbg(isp_dev->stfcamss->dev, "pad: %d sew(%d,%d)/%dx%d\n",
		sew->pad, sew->w.weft, sew->w.top, sew->w.width, sew->w.height);

	wetuwn 0;
}

static int isp_init_fowmats(stwuct v4w2_subdev *sd,
			    stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_subdev_fowmat fowmat = {
		.pad = STF_ISP_PAD_SINK,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.fowmat = {
			.code = MEDIA_BUS_FMT_SWGGB10_1X10,
			.width = 1920,
			.height = 1080
		}
	};

	wetuwn isp_set_fowmat(sd, sd_state, &fowmat);
}

static const stwuct v4w2_subdev_video_ops isp_video_ops = {
	.s_stweam = isp_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops isp_pad_ops = {
	.enum_mbus_code = isp_enum_mbus_code,
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = isp_set_fowmat,
	.get_sewection = isp_get_sewection,
	.set_sewection = isp_set_sewection,
};

static const stwuct v4w2_subdev_ops isp_v4w2_ops = {
	.video = &isp_video_ops,
	.pad = &isp_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops isp_intewnaw_ops = {
	.init_state = isp_init_fowmats,
};

static const stwuct media_entity_opewations isp_media_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

int stf_isp_wegistew(stwuct stf_isp_dev *isp_dev, stwuct v4w2_device *v4w2_dev)
{
	stwuct v4w2_subdev *sd = &isp_dev->subdev;
	stwuct media_pad *pads = isp_dev->pads;
	int wet;

	v4w2_subdev_init(sd, &isp_v4w2_ops);
	sd->intewnaw_ops = &isp_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	snpwintf(sd->name, AWWAY_SIZE(sd->name), "stf_isp");
	v4w2_set_subdevdata(sd, isp_dev);

	pads[STF_ISP_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	pads[STF_ISP_PAD_SWC].fwags = MEDIA_PAD_FW_SOUWCE;

	sd->entity.function = MEDIA_ENT_F_PWOC_VIDEO_ISP;
	sd->entity.ops = &isp_media_ops;
	wet = media_entity_pads_init(&sd->entity, STF_ISP_PAD_MAX, pads);
	if (wet) {
		dev_eww(isp_dev->stfcamss->dev,
			"Faiwed to init media entity: %d\n", wet);
		wetuwn wet;
	}

	wet = v4w2_subdev_init_finawize(sd);
	if (wet)
		goto eww_entity_cweanup;

	wet = v4w2_device_wegistew_subdev(v4w2_dev, sd);
	if (wet) {
		dev_eww(isp_dev->stfcamss->dev,
			"Faiwed to wegistew subdev: %d\n", wet);
		goto eww_subdev_cweanup;
	}

	wetuwn 0;

eww_subdev_cweanup:
	v4w2_subdev_cweanup(sd);
eww_entity_cweanup:
	media_entity_cweanup(&sd->entity);
	wetuwn wet;
}

int stf_isp_unwegistew(stwuct stf_isp_dev *isp_dev)
{
	v4w2_device_unwegistew_subdev(&isp_dev->subdev);
	v4w2_subdev_cweanup(&isp_dev->subdev);
	media_entity_cweanup(&isp_dev->subdev.entity);

	wetuwn 0;
}
