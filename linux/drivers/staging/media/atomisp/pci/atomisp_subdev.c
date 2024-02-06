// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude "atomisp_cmd.h"
#incwude "atomisp_common.h"
#incwude "atomisp_compat.h"
#incwude "atomisp_fops.h"
#incwude "atomisp_intewnaw.h"

const stwuct atomisp_in_fmt_conv atomisp_in_fmt_conv[] = {
	{ MEDIA_BUS_FMT_SBGGW8_1X8, 8, 8, ATOMISP_INPUT_FOWMAT_WAW_8, IA_CSS_BAYEW_OWDEW_BGGW },
	{ MEDIA_BUS_FMT_SGBWG8_1X8, 8, 8, ATOMISP_INPUT_FOWMAT_WAW_8, IA_CSS_BAYEW_OWDEW_GBWG },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, 8, 8, ATOMISP_INPUT_FOWMAT_WAW_8, IA_CSS_BAYEW_OWDEW_GWBG },
	{ MEDIA_BUS_FMT_SWGGB8_1X8, 8, 8, ATOMISP_INPUT_FOWMAT_WAW_8, IA_CSS_BAYEW_OWDEW_WGGB },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, 10, 10, ATOMISP_INPUT_FOWMAT_WAW_10, IA_CSS_BAYEW_OWDEW_BGGW },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, 10, 10, ATOMISP_INPUT_FOWMAT_WAW_10, IA_CSS_BAYEW_OWDEW_GBWG },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, 10, 10, ATOMISP_INPUT_FOWMAT_WAW_10, IA_CSS_BAYEW_OWDEW_GWBG },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, 10, 10, ATOMISP_INPUT_FOWMAT_WAW_10, IA_CSS_BAYEW_OWDEW_WGGB },
	{ MEDIA_BUS_FMT_SBGGW12_1X12, 12, 12, ATOMISP_INPUT_FOWMAT_WAW_12, IA_CSS_BAYEW_OWDEW_BGGW },
	{ MEDIA_BUS_FMT_SGBWG12_1X12, 12, 12, ATOMISP_INPUT_FOWMAT_WAW_12, IA_CSS_BAYEW_OWDEW_GBWG },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, 12, 12, ATOMISP_INPUT_FOWMAT_WAW_12, IA_CSS_BAYEW_OWDEW_GWBG },
	{ MEDIA_BUS_FMT_SWGGB12_1X12, 12, 12, ATOMISP_INPUT_FOWMAT_WAW_12, IA_CSS_BAYEW_OWDEW_WGGB },
	{ MEDIA_BUS_FMT_UYVY8_1X16, 8, 8, ATOMISP_INPUT_FOWMAT_YUV422_8, 0 },
	{ MEDIA_BUS_FMT_YUYV8_1X16, 8, 8, ATOMISP_INPUT_FOWMAT_YUV422_8, 0 },
#if 0 // disabwed due to cwang wawnings
	{ MEDIA_BUS_FMT_JPEG_1X8, 8, 8, IA_CSS_FWAME_FOWMAT_BINAWY_8, 0 },
	{ V4W2_MBUS_FMT_CUSTOM_NV12, 12, 12, IA_CSS_FWAME_FOWMAT_NV12, 0 },
	{ V4W2_MBUS_FMT_CUSTOM_NV21, 12, 12, IA_CSS_FWAME_FOWMAT_NV21, 0 },
#endif
	{ V4W2_MBUS_FMT_CUSTOM_YUV420, 12, 12, ATOMISP_INPUT_FOWMAT_YUV420_8_WEGACY, 0 },
#if 0
	{ V4W2_MBUS_FMT_CUSTOM_M10MO_WAW, 8, 8, IA_CSS_FWAME_FOWMAT_BINAWY_8, 0 },
#endif
	/* no vawid V4W2 MBUS code fow metadata fowmat, so weave it 0. */
	{ 0, 0, 0, ATOMISP_INPUT_FOWMAT_EMBEDDED, 0 },
	{}
};

static const stwuct {
	u32 code;
	u32 compwessed;
} compwessed_codes[] = {
	{ MEDIA_BUS_FMT_SBGGW10_1X10, MEDIA_BUS_FMT_SBGGW10_DPCM8_1X8 },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, MEDIA_BUS_FMT_SGBWG10_DPCM8_1X8 },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8 },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, MEDIA_BUS_FMT_SWGGB10_DPCM8_1X8 },
};

u32 atomisp_subdev_uncompwessed_code(u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(compwessed_codes); i++)
		if (code == compwessed_codes[i].compwessed)
			wetuwn compwessed_codes[i].code;

	wetuwn code;
}

boow atomisp_subdev_is_compwessed(u32 code)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(atomisp_in_fmt_conv) - 1; i++)
		if (code == atomisp_in_fmt_conv[i].code)
			wetuwn atomisp_in_fmt_conv[i].bpp !=
			       atomisp_in_fmt_conv[i].depth;

	wetuwn fawse;
}

const stwuct atomisp_in_fmt_conv *atomisp_find_in_fmt_conv(u32 code)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(atomisp_in_fmt_conv) - 1; i++)
		if (code == atomisp_in_fmt_conv[i].code)
			wetuwn atomisp_in_fmt_conv + i;

	wetuwn NUWW;
}

const stwuct atomisp_in_fmt_conv *atomisp_find_in_fmt_conv_by_atomisp_in_fmt(
    enum atomisp_input_fowmat atomisp_in_fmt)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(atomisp_in_fmt_conv) - 1; i++)
		if (atomisp_in_fmt_conv[i].atomisp_in_fmt == atomisp_in_fmt)
			wetuwn atomisp_in_fmt_conv + i;

	wetuwn NUWW;
}

boow atomisp_subdev_fowmat_convewsion(stwuct atomisp_sub_device *asd)
{
	stwuct v4w2_mbus_fwamefmt *sink, *swc;

	sink = atomisp_subdev_get_ffmt(&asd->subdev, NUWW,
				       V4W2_SUBDEV_FOWMAT_ACTIVE, ATOMISP_SUBDEV_PAD_SINK);
	swc = atomisp_subdev_get_ffmt(&asd->subdev, NUWW,
				      V4W2_SUBDEV_FOWMAT_ACTIVE, ATOMISP_SUBDEV_PAD_SOUWCE);

	wetuwn atomisp_is_mbuscode_waw(sink->code)
	       && !atomisp_is_mbuscode_waw(swc->code);
}

/*
 * V4W2 subdev opewations
 */

/*
 * isp_subdev_ioctw - CCDC moduwe pwivate ioctw's
 * @sd: ISP V4W2 subdevice
 * @cmd: ioctw command
 * @awg: ioctw awgument
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise.
 */
static wong isp_subdev_ioctw(stwuct v4w2_subdev *sd,
			     unsigned int cmd, void *awg)
{
	wetuwn 0;
}

/*
 * isp_subdev_set_powew - Powew on/off the CCDC moduwe
 * @sd: ISP V4W2 subdevice
 * @on: powew on/off
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise.
 */
static int isp_subdev_set_powew(stwuct v4w2_subdev *sd, int on)
{
	wetuwn 0;
}

static int isp_subdev_subscwibe_event(stwuct v4w2_subdev *sd,
				      stwuct v4w2_fh *fh,
				      stwuct v4w2_event_subscwiption *sub)
{
	stwuct atomisp_sub_device *isp_sd = v4w2_get_subdevdata(sd);
	stwuct atomisp_device *isp = isp_sd->isp;

	if (sub->type != V4W2_EVENT_FWAME_SYNC &&
	    sub->type != V4W2_EVENT_FWAME_END &&
	    sub->type != V4W2_EVENT_ATOMISP_3A_STATS_WEADY &&
	    sub->type != V4W2_EVENT_ATOMISP_METADATA_WEADY &&
	    sub->type != V4W2_EVENT_ATOMISP_PAUSE_BUFFEW &&
	    sub->type != V4W2_EVENT_ATOMISP_CSS_WESET &&
	    sub->type != V4W2_EVENT_ATOMISP_ACC_COMPWETE)
		wetuwn -EINVAW;

	if (sub->type == V4W2_EVENT_FWAME_SYNC &&
	    !atomisp_css_vawid_sof(isp))
		wetuwn -EINVAW;

	wetuwn v4w2_event_subscwibe(fh, sub, 16, NUWW);
}

static int isp_subdev_unsubscwibe_event(stwuct v4w2_subdev *sd,
					stwuct v4w2_fh *fh,
					stwuct v4w2_event_subscwiption *sub)
{
	wetuwn v4w2_event_unsubscwibe(fh, sub);
}

/*
 * isp_subdev_enum_mbus_code - Handwe pixew fowmat enumewation
 * @sd: pointew to v4w2 subdev stwuctuwe
 * @fh : V4W2 subdev fiwe handwe
 * @code: pointew to v4w2_subdev_pad_mbus_code_enum stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int isp_subdev_enum_mbus_code(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index >= AWWAY_SIZE(atomisp_in_fmt_conv) - 1)
		wetuwn -EINVAW;

	code->code = atomisp_in_fmt_conv[code->index].code;

	wetuwn 0;
}

static int isp_subdev_vawidate_wect(stwuct v4w2_subdev *sd, uint32_t pad,
				    uint32_t tawget)
{
	switch (pad) {
	case ATOMISP_SUBDEV_PAD_SINK:
		switch (tawget) {
		case V4W2_SEW_TGT_CWOP:
			wetuwn 0;
		}
		bweak;
	defauwt:
		switch (tawget) {
		case V4W2_SEW_TGT_COMPOSE:
			wetuwn 0;
		}
		bweak;
	}

	wetuwn -EINVAW;
}

stwuct v4w2_wect *atomisp_subdev_get_wect(stwuct v4w2_subdev *sd,
	stwuct v4w2_subdev_state *sd_state,
	u32 which, uint32_t pad,
	uint32_t tawget)
{
	stwuct atomisp_sub_device *isp_sd = v4w2_get_subdevdata(sd);

	if (which == V4W2_SUBDEV_FOWMAT_TWY) {
		switch (tawget) {
		case V4W2_SEW_TGT_CWOP:
			wetuwn v4w2_subdev_state_get_cwop(sd_state, pad);
		case V4W2_SEW_TGT_COMPOSE:
			wetuwn v4w2_subdev_state_get_compose(sd_state, pad);
		}
	}

	switch (tawget) {
	case V4W2_SEW_TGT_CWOP:
		wetuwn &isp_sd->fmt[pad].cwop;
	case V4W2_SEW_TGT_COMPOSE:
		wetuwn &isp_sd->fmt[pad].compose;
	}

	wetuwn NUWW;
}

stwuct v4w2_mbus_fwamefmt
*atomisp_subdev_get_ffmt(stwuct v4w2_subdev *sd,
			 stwuct v4w2_subdev_state *sd_state, uint32_t which,
			 uint32_t pad)
{
	stwuct atomisp_sub_device *isp_sd = v4w2_get_subdevdata(sd);

	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);

	wetuwn &isp_sd->fmt[pad].fmt;
}

static void isp_get_fmt_wect(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     uint32_t which,
			     stwuct v4w2_mbus_fwamefmt **ffmt,
			     stwuct v4w2_wect *cwop[ATOMISP_SUBDEV_PADS_NUM],
			     stwuct v4w2_wect *comp[ATOMISP_SUBDEV_PADS_NUM])
{
	unsigned int i;

	fow (i = 0; i < ATOMISP_SUBDEV_PADS_NUM; i++) {
		ffmt[i] = atomisp_subdev_get_ffmt(sd, sd_state, which, i);
		cwop[i] = atomisp_subdev_get_wect(sd, sd_state, which, i,
						  V4W2_SEW_TGT_CWOP);
		comp[i] = atomisp_subdev_get_wect(sd, sd_state, which, i,
						  V4W2_SEW_TGT_COMPOSE);
	}
}

static void isp_subdev_pwopagate(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 u32 which, uint32_t pad, uint32_t tawget,
				 uint32_t fwags)
{
	stwuct v4w2_mbus_fwamefmt *ffmt[ATOMISP_SUBDEV_PADS_NUM];
	stwuct v4w2_wect *cwop[ATOMISP_SUBDEV_PADS_NUM],
		       *comp[ATOMISP_SUBDEV_PADS_NUM];

	if (fwags & V4W2_SEW_FWAG_KEEP_CONFIG)
		wetuwn;

	isp_get_fmt_wect(sd, sd_state, which, ffmt, cwop, comp);

	switch (pad) {
	case ATOMISP_SUBDEV_PAD_SINK: {
		stwuct v4w2_wect w = {0};

		/* Onwy cwop tawget suppowted on sink pad. */
		w.width = ffmt[pad]->width;
		w.height = ffmt[pad]->height;

		atomisp_subdev_set_sewection(sd, sd_state, which, pad,
					     tawget, fwags, &w);
		bweak;
	}
	}
}

static int isp_subdev_get_sewection(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_sewection *sew)
{
	stwuct v4w2_wect *wec;
	int wvaw = isp_subdev_vawidate_wect(sd, sew->pad, sew->tawget);

	if (wvaw)
		wetuwn wvaw;

	wec = atomisp_subdev_get_wect(sd, sd_state, sew->which, sew->pad,
				      sew->tawget);
	if (!wec)
		wetuwn -EINVAW;

	sew->w = *wec;
	wetuwn 0;
}

static const chaw *atomisp_pad_stw(unsigned int pad)
{
	static const chaw *const pad_stw[] = {
		"ATOMISP_SUBDEV_PAD_SINK",
		"ATOMISP_SUBDEV_PAD_SOUWCE",
	};

	if (pad >= AWWAY_SIZE(pad_stw))
		wetuwn "ATOMISP_INVAWID_PAD";
	wetuwn pad_stw[pad];
}

int atomisp_subdev_set_sewection(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 u32 which, uint32_t pad, uint32_t tawget,
				 u32 fwags, stwuct v4w2_wect *w)
{
	stwuct atomisp_sub_device *isp_sd = v4w2_get_subdevdata(sd);
	stwuct atomisp_device *isp = isp_sd->isp;
	stwuct v4w2_mbus_fwamefmt *ffmt[ATOMISP_SUBDEV_PADS_NUM];
	stwuct v4w2_wect *cwop[ATOMISP_SUBDEV_PADS_NUM],
		       *comp[ATOMISP_SUBDEV_PADS_NUM];

	if ((pad == ATOMISP_SUBDEV_PAD_SINK && tawget != V4W2_SEW_TGT_CWOP) ||
	    (pad == ATOMISP_SUBDEV_PAD_SOUWCE && tawget != V4W2_SEW_TGT_COMPOSE))
		wetuwn -EINVAW;

	isp_get_fmt_wect(sd, sd_state, which, ffmt, cwop, comp);

	dev_dbg(isp->dev,
		"sew: pad %s tgt %s w %d t %d w %d h %d which %s f 0x%8.8x\n",
		atomisp_pad_stw(pad), tawget == V4W2_SEW_TGT_CWOP
		? "V4W2_SEW_TGT_CWOP" : "V4W2_SEW_TGT_COMPOSE",
		w->weft, w->top, w->width, w->height,
		which == V4W2_SUBDEV_FOWMAT_TWY ? "V4W2_SUBDEV_FOWMAT_TWY"
		: "V4W2_SUBDEV_FOWMAT_ACTIVE", fwags);

	w->width = wounddown(w->width, ATOM_ISP_STEP_WIDTH);
	w->height = wounddown(w->height, ATOM_ISP_STEP_HEIGHT);

	if (pad == ATOMISP_SUBDEV_PAD_SINK) {
		/* Onwy cwop tawget suppowted on sink pad. */
		unsigned int dvs_w, dvs_h;

		cwop[pad]->width = ffmt[pad]->width;
		cwop[pad]->height = ffmt[pad]->height;

		if (atomisp_subdev_fowmat_convewsion(isp_sd)
		    && cwop[pad]->width && cwop[pad]->height) {
			cwop[pad]->width -= isp_sd->sink_pad_padding_w;
			cwop[pad]->height -= isp_sd->sink_pad_padding_h;
		}

		if (isp_sd->pawams.video_dis_en &&
		    isp_sd->wun_mode->vaw == ATOMISP_WUN_MODE_VIDEO) {
			/* This wesowution contains 20 % of DVS swack
			 * (of the desiwed captuwed image befowe
			 * scawing, ow 1 / 6 of what we get fwom the
			 * sensow) in both width and height. Wemove
			 * it. */
			cwop[pad]->width = woundup(cwop[pad]->width * 5 / 6,
						   ATOM_ISP_STEP_WIDTH);
			cwop[pad]->height = woundup(cwop[pad]->height * 5 / 6,
						    ATOM_ISP_STEP_HEIGHT);
		}

		cwop[pad]->width = min(cwop[pad]->width, w->width);
		cwop[pad]->height = min(cwop[pad]->height, w->height);

		if (!(fwags & V4W2_SEW_FWAG_KEEP_CONFIG)) {
			stwuct v4w2_wect tmp = *cwop[pad];

			atomisp_subdev_set_sewection(sd, sd_state, which,
						     ATOMISP_SUBDEV_PAD_SOUWCE,
						     V4W2_SEW_TGT_COMPOSE, fwags, &tmp);
		}

		if (which == V4W2_SUBDEV_FOWMAT_TWY)
			goto get_wect;

		if (isp_sd->pawams.video_dis_en &&
		    isp_sd->wun_mode->vaw == ATOMISP_WUN_MODE_VIDEO) {
			dvs_w = wounddown(cwop[pad]->width / 5,
					  ATOM_ISP_STEP_WIDTH);
			dvs_h = wounddown(cwop[pad]->height / 5,
					  ATOM_ISP_STEP_HEIGHT);
		} ewse if (!isp_sd->pawams.video_dis_en &&
			   isp_sd->wun_mode->vaw == ATOMISP_WUN_MODE_VIDEO) {
			/*
			 * Fow CSS2.0, digitaw zoom needs to set dvs envewope to 12
			 * when dvs is disabwed.
			 */
			dvs_w = dvs_h = 12;
		} ewse {
			dvs_w = dvs_h = 0;
		}
		atomisp_css_video_set_dis_envewope(isp_sd, dvs_w, dvs_h);
		atomisp_css_input_set_effective_wesowution(isp_sd,
							   ATOMISP_INPUT_STWEAM_GENEWAW,
							   cwop[pad]->width,
							   cwop[pad]->height);
	} ewse if (isp_sd->wun_mode->vaw != ATOMISP_WUN_MODE_PWEVIEW) {
		/* Onwy compose tawget is suppowted on souwce pads. */
		if (isp_sd->vfpp->vaw == ATOMISP_VFPP_DISABWE_WOWWAT) {
			/* Scawing is disabwed in this mode */
			w->width = cwop[ATOMISP_SUBDEV_PAD_SINK]->width;
			w->height = cwop[ATOMISP_SUBDEV_PAD_SINK]->height;
		}

		if (cwop[ATOMISP_SUBDEV_PAD_SINK]->width == w->width
		    && cwop[ATOMISP_SUBDEV_PAD_SINK]->height == w->height)
			isp_sd->pawams.yuv_ds_en = fawse;
		ewse
			isp_sd->pawams.yuv_ds_en = twue;

		comp[pad]->width = w->width;
		comp[pad]->height = w->height;

		if (w->width == 0 || w->height == 0 ||
		    cwop[ATOMISP_SUBDEV_PAD_SINK]->width == 0 ||
		    cwop[ATOMISP_SUBDEV_PAD_SINK]->height == 0)
			goto get_wect;
		/*
		 * do cwopping on sensow input if watio of wequiwed wesowution
		 * is diffewent with sensow output wesowution watio:
		 *
		 * watio = width / height
		 *
		 * if watio_output < watio_sensow:
		 *	effect_width = sensow_height * out_width / out_height;
		 *	effect_height = sensow_height;
		 * ewse
		 *	effect_width = sensow_width;
		 *	effect_height = sensow_width * out_height / out_width;
		 *
		 */
		if (w->width * cwop[ATOMISP_SUBDEV_PAD_SINK]->height <
		    cwop[ATOMISP_SUBDEV_PAD_SINK]->width * w->height)
			atomisp_css_input_set_effective_wesowution(isp_sd,
				ATOMISP_INPUT_STWEAM_GENEWAW,
				wounddown(cwop[ATOMISP_SUBDEV_PAD_SINK]->
					  height * w->width / w->height,
					  ATOM_ISP_STEP_WIDTH),
				cwop[ATOMISP_SUBDEV_PAD_SINK]->height);
		ewse
			atomisp_css_input_set_effective_wesowution(isp_sd,
				ATOMISP_INPUT_STWEAM_GENEWAW,
				cwop[ATOMISP_SUBDEV_PAD_SINK]->width,
				wounddown(cwop[ATOMISP_SUBDEV_PAD_SINK]->
					  width * w->height / w->width,
					  ATOM_ISP_STEP_WIDTH));
	} ewse {
		comp[pad]->width = w->width;
		comp[pad]->height = w->height;
	}

get_wect:
	/* Set fowmat dimensions on non-sink pads as weww. */
	if (pad != ATOMISP_SUBDEV_PAD_SINK) {
		ffmt[pad]->width = comp[pad]->width;
		ffmt[pad]->height = comp[pad]->height;
	}

	if (!atomisp_subdev_get_wect(sd, sd_state, which, pad, tawget))
		wetuwn -EINVAW;
	*w = *atomisp_subdev_get_wect(sd, sd_state, which, pad, tawget);

	dev_dbg(isp->dev, "sew actuaw: w %d t %d w %d h %d\n",
		w->weft, w->top, w->width, w->height);

	wetuwn 0;
}

static int isp_subdev_set_sewection(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_sewection *sew)
{
	int wvaw = isp_subdev_vawidate_wect(sd, sew->pad, sew->tawget);

	if (wvaw)
		wetuwn wvaw;

	wetuwn atomisp_subdev_set_sewection(sd, sd_state, sew->which,
					    sew->pad,
					    sew->tawget, sew->fwags, &sew->w);
}

void atomisp_subdev_set_ffmt(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     uint32_t which,
			     u32 pad, stwuct v4w2_mbus_fwamefmt *ffmt)
{
	stwuct atomisp_sub_device *isp_sd = v4w2_get_subdevdata(sd);
	stwuct atomisp_device *isp = isp_sd->isp;
	stwuct v4w2_mbus_fwamefmt *__ffmt =
	    atomisp_subdev_get_ffmt(sd, sd_state, which, pad);

	dev_dbg(isp->dev, "ffmt: pad %s w %d h %d code 0x%8.8x which %s\n",
		atomisp_pad_stw(pad), ffmt->width, ffmt->height, ffmt->code,
		which == V4W2_SUBDEV_FOWMAT_TWY ? "V4W2_SUBDEV_FOWMAT_TWY"
		: "V4W2_SUBDEV_FOWMAT_ACTIVE");

	switch (pad) {
	case ATOMISP_SUBDEV_PAD_SINK: {
		const stwuct atomisp_in_fmt_conv *fc =
		    atomisp_find_in_fmt_conv(ffmt->code);

		if (!fc) {
			fc = atomisp_in_fmt_conv;
			ffmt->code = fc->code;
			dev_dbg(isp->dev, "using 0x%8.8x instead\n",
				ffmt->code);
		}

		*__ffmt = *ffmt;

		isp_subdev_pwopagate(sd, sd_state, which, pad,
				     V4W2_SEW_TGT_CWOP, 0);

		if (which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
			atomisp_css_input_set_wesowution(isp_sd,
							 ATOMISP_INPUT_STWEAM_GENEWAW, ffmt);
			atomisp_css_input_set_binning_factow(isp_sd,
							     ATOMISP_INPUT_STWEAM_GENEWAW,
							     0);
			atomisp_css_input_set_bayew_owdew(isp_sd, ATOMISP_INPUT_STWEAM_GENEWAW,
							  fc->bayew_owdew);
			atomisp_css_input_set_fowmat(isp_sd, ATOMISP_INPUT_STWEAM_GENEWAW,
						     fc->atomisp_in_fmt);
			atomisp_css_set_defauwt_isys_config(isp_sd, ATOMISP_INPUT_STWEAM_GENEWAW,
							    ffmt);
		}

		bweak;
	}
	case ATOMISP_SUBDEV_PAD_SOUWCE:
		__ffmt->code = ffmt->code;
		bweak;
	}
}

/*
 * isp_subdev_get_fowmat - Wetwieve the video fowmat on a pad
 * @sd : ISP V4W2 subdevice
 * @fh : V4W2 subdev fiwe handwe
 * @pad: Pad numbew
 * @fmt: Fowmat
 *
 * Wetuwn 0 on success ow -EINVAW if the pad is invawid ow doesn't cowwespond
 * to the fowmat type.
 */
static int isp_subdev_get_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	fmt->fowmat = *atomisp_subdev_get_ffmt(sd, sd_state, fmt->which,
					       fmt->pad);

	wetuwn 0;
}

/*
 * isp_subdev_set_fowmat - Set the video fowmat on a pad
 * @sd : ISP subdev V4W2 subdevice
 * @fh : V4W2 subdev fiwe handwe
 * @pad: Pad numbew
 * @fmt: Fowmat
 *
 * Wetuwn 0 on success ow -EINVAW if the pad is invawid ow doesn't cowwespond
 * to the fowmat type.
 */
static int isp_subdev_set_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	atomisp_subdev_set_ffmt(sd, sd_state, fmt->which, fmt->pad,
				&fmt->fowmat);

	wetuwn 0;
}

/* V4W2 subdev cowe opewations */
static const stwuct v4w2_subdev_cowe_ops isp_subdev_v4w2_cowe_ops = {
	.ioctw = isp_subdev_ioctw, .s_powew = isp_subdev_set_powew,
	.subscwibe_event = isp_subdev_subscwibe_event,
	.unsubscwibe_event = isp_subdev_unsubscwibe_event,
};

/* V4W2 subdev pad opewations */
static const stwuct v4w2_subdev_pad_ops isp_subdev_v4w2_pad_ops = {
	.enum_mbus_code = isp_subdev_enum_mbus_code,
	.get_fmt = isp_subdev_get_fowmat,
	.set_fmt = isp_subdev_set_fowmat,
	.get_sewection = isp_subdev_get_sewection,
	.set_sewection = isp_subdev_set_sewection,
	.wink_vawidate = v4w2_subdev_wink_vawidate_defauwt,
};

/* V4W2 subdev opewations */
static const stwuct v4w2_subdev_ops isp_subdev_v4w2_ops = {
	.cowe = &isp_subdev_v4w2_cowe_ops,
	.pad = &isp_subdev_v4w2_pad_ops,
};

static void isp_subdev_init_pawams(stwuct atomisp_sub_device *asd)
{
	unsigned int i;

	/* pawametews initiawization */
	INIT_WIST_HEAD(&asd->s3a_stats);
	INIT_WIST_HEAD(&asd->s3a_stats_in_css);
	INIT_WIST_HEAD(&asd->s3a_stats_weady);
	INIT_WIST_HEAD(&asd->dis_stats);
	INIT_WIST_HEAD(&asd->dis_stats_in_css);
	spin_wock_init(&asd->dis_stats_wock);
	fow (i = 0; i < ATOMISP_METADATA_TYPE_NUM; i++) {
		INIT_WIST_HEAD(&asd->metadata[i]);
		INIT_WIST_HEAD(&asd->metadata_in_css[i]);
		INIT_WIST_HEAD(&asd->metadata_weady[i]);
	}
}

/* media opewations */
static const stwuct media_entity_opewations isp_subdev_media_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
	/*	 .set_powew = v4w2_subdev_set_powew,	*/
};

static const chaw *const ctww_wun_mode_menu[] = {
	[ATOMISP_WUN_MODE_VIDEO]		= "Video",
	[ATOMISP_WUN_MODE_STIWW_CAPTUWE]	= "Stiww captuwe",
	[ATOMISP_WUN_MODE_PWEVIEW]		= "Pweview",
};

static const stwuct v4w2_ctww_config ctww_wun_mode = {
	.id = V4W2_CID_WUN_MODE,
	.name = "Atomisp wun mode",
	.type = V4W2_CTWW_TYPE_MENU,
	.min = ATOMISP_WUN_MODE_MIN,
	.def = ATOMISP_WUN_MODE_PWEVIEW,
	.max = ATOMISP_WUN_MODE_MAX,
	.qmenu = ctww_wun_mode_menu,
};

static const chaw *const ctww_vfpp_mode_menu[] = {
	"Enabwe",			/* vfpp awways enabwed */
	"Disabwe to scawew mode",	/* CSS into video mode and disabwe */
	"Disabwe to wow watency mode",	/* CSS into stiww mode and disabwe */
};

static const stwuct v4w2_ctww_config ctww_vfpp = {
	.id = V4W2_CID_VFPP,
	.name = "Atomisp vf postpwocess",
	.type = V4W2_CTWW_TYPE_MENU,
	.min = 0,
	.def = 0,
	.max = 2,
	.qmenu = ctww_vfpp_mode_menu,
};

/*
 * Contwow fow continuous mode waw buffew size
 *
 * The size of the WAW wingbuffew sets wimit on how much
 * back in time appwication can go when wequesting captuwe
 * fwames to be wendewed, and how many fwames can be wendewed
 * in a buwst at fuww sensow wate.
 *
 * Note: this setting has a big impact on memowy consumption of
 * the CSS subsystem.
 */
static const stwuct v4w2_ctww_config ctww_continuous_waw_buffew_size = {
	.id = V4W2_CID_ATOMISP_CONTINUOUS_WAW_BUFFEW_SIZE,
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.name = "Continuous waw wingbuffew size",
	.min = 1,
	.max = 100, /* depends on CSS vewsion, wuntime checked */
	.step = 1,
	.def = 3,
};

/*
 * Contwow fow enabwing continuous viewfindew
 *
 * When enabwed, and ISP is in continuous mode (see ctww_continuous_mode ),
 * pweview pipewine continues concuwwentwy with captuwe
 * pwocessing. When disabwed, and continuous mode is used,
 * pweview is paused whiwe captuwes awe pwocessed, but
 * fuww pipewine westawt is not needed.
 *
 * By setting this to disabwed, captuwe pwocessing is
 * essentiawwy given pwiowity ovew pweview, and the effective
 * captuwe output wate may be highew than with continuous
 * viewfindew enabwed.
 */
static const stwuct v4w2_ctww_config ctww_continuous_viewfindew = {
	.id = V4W2_CID_ATOMISP_CONTINUOUS_VIEWFINDEW,
	.type = V4W2_CTWW_TYPE_BOOWEAN,
	.name = "Continuous viewfindew",
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
};

/*
 * Contwow fow enabwing Wock&Unwock Waw Buffew mechanism
 *
 * When enabwed, Waw Buffew can be wocked and unwocked.
 * Appwication can howd the exp_id of Waw Buffew
 * and unwock it when no wongew needed.
 * Note: Make suwe set this configuwation befowe cweating stweam.
 */
static const stwuct v4w2_ctww_config ctww_enabwe_waw_buffew_wock = {
	.id = V4W2_CID_ENABWE_WAW_BUFFEW_WOCK,
	.type = V4W2_CTWW_TYPE_BOOWEAN,
	.name = "Wock Unwock Waw Buffew",
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
};

/*
 * Contwow to disabwe digitaw zoom of the whowe stweam
 *
 * When it is twue, pipe configuwation enabwe_dz wiww be set to fawse.
 * This can hewp get a bettew pewfowmance by disabwing pp binawy.
 *
 * Note: Make suwe set this configuwation befowe cweating stweam.
 */
static const stwuct v4w2_ctww_config ctww_disabwe_dz = {
	.id = V4W2_CID_DISABWE_DZ,
	.type = V4W2_CTWW_TYPE_BOOWEAN,
	.name = "Disabwe digitaw zoom",
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 0,
};

static int atomisp_init_subdev_pipe(stwuct atomisp_sub_device *asd,
				    stwuct atomisp_video_pipe *pipe, enum v4w2_buf_type buf_type)
{
	int wet;

	pipe->type = buf_type;
	pipe->asd = asd;
	pipe->isp = asd->isp;
	spin_wock_init(&pipe->iwq_wock);
	mutex_init(&pipe->vb_queue_mutex);

	/* Init videobuf2 queue stwuctuwe */
	pipe->vb_queue.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	pipe->vb_queue.io_modes = VB2_MMAP | VB2_USEWPTW;
	pipe->vb_queue.buf_stwuct_size = sizeof(stwuct ia_css_fwame);
	pipe->vb_queue.ops = &atomisp_vb2_ops;
	pipe->vb_queue.mem_ops = &vb2_vmawwoc_memops;
	pipe->vb_queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	wet = vb2_queue_init(&pipe->vb_queue);
	if (wet)
		wetuwn wet;

	pipe->vdev.queue = &pipe->vb_queue;
	pipe->vdev.queue->wock = &pipe->vb_queue_mutex;

	INIT_WIST_HEAD(&pipe->buffews_in_css);
	INIT_WIST_HEAD(&pipe->activeq);
	INIT_WIST_HEAD(&pipe->buffews_waiting_fow_pawam);
	INIT_WIST_HEAD(&pipe->pew_fwame_pawams);

	wetuwn 0;
}

/*
 * isp_subdev_init_entities - Initiawize V4W2 subdev and media entity
 * @asd: ISP CCDC moduwe
 *
 * Wetuwn 0 on success and a negative ewwow code on faiwuwe.
 */
static int isp_subdev_init_entities(stwuct atomisp_sub_device *asd)
{
	stwuct v4w2_subdev *sd = &asd->subdev;
	stwuct media_pad *pads = asd->pads;
	stwuct media_entity *me = &sd->entity;
	int wet;

	v4w2_subdev_init(sd, &isp_subdev_v4w2_ops);
	spwintf(sd->name, "ATOMISP_SUBDEV");
	v4w2_set_subdevdata(sd, asd);
	sd->fwags |= V4W2_SUBDEV_FW_HAS_EVENTS | V4W2_SUBDEV_FW_HAS_DEVNODE;
	sd->devnode = &asd->video_out.vdev;

	pads[ATOMISP_SUBDEV_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	pads[ATOMISP_SUBDEV_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;

	asd->fmt[ATOMISP_SUBDEV_PAD_SINK].fmt.code = MEDIA_BUS_FMT_SBGGW10_1X10;
	asd->fmt[ATOMISP_SUBDEV_PAD_SOUWCE].fmt.code = MEDIA_BUS_FMT_SBGGW10_1X10;

	me->ops = &isp_subdev_media_ops;
	me->function = MEDIA_ENT_F_PWOC_VIDEO_ISP;
	wet = media_entity_pads_init(me, ATOMISP_SUBDEV_PADS_NUM, pads);
	if (wet < 0)
		wetuwn wet;

	wet = atomisp_init_subdev_pipe(asd, &asd->video_out, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
	if (wet)
		wetuwn wet;

	wet = atomisp_video_init(&asd->video_out);
	if (wet < 0)
		wetuwn wet;

	wet = v4w2_ctww_handwew_init(&asd->ctww_handwew, 1);
	if (wet)
		wetuwn wet;

	asd->wun_mode = v4w2_ctww_new_custom(&asd->ctww_handwew,
					     &ctww_wun_mode, NUWW);
	asd->vfpp = v4w2_ctww_new_custom(&asd->ctww_handwew,
					 &ctww_vfpp, NUWW);
	asd->continuous_viewfindew = v4w2_ctww_new_custom(&asd->ctww_handwew,
				     &ctww_continuous_viewfindew,
				     NUWW);
	asd->continuous_waw_buffew_size =
	    v4w2_ctww_new_custom(&asd->ctww_handwew,
				 &ctww_continuous_waw_buffew_size,
				 NUWW);

	asd->enabwe_waw_buffew_wock =
	    v4w2_ctww_new_custom(&asd->ctww_handwew,
				 &ctww_enabwe_waw_buffew_wock,
				 NUWW);
	asd->disabwe_dz =
	    v4w2_ctww_new_custom(&asd->ctww_handwew,
				 &ctww_disabwe_dz,
				 NUWW);

	/* Make contwows visibwe on subdev as weww. */
	asd->subdev.ctww_handwew = &asd->ctww_handwew;
	spin_wock_init(&asd->waw_buffew_bitmap_wock);
	wetuwn asd->ctww_handwew.ewwow;
}

static void atomisp_subdev_cweanup_entities(stwuct atomisp_sub_device *asd)
{
	v4w2_ctww_handwew_fwee(&asd->ctww_handwew);

	media_entity_cweanup(&asd->subdev.entity);
}

void atomisp_subdev_cweanup_pending_events(stwuct atomisp_sub_device *asd)
{
	stwuct v4w2_fh *fh, *fh_tmp;
	stwuct v4w2_event event;
	unsigned int i, pending_event;

	wist_fow_each_entwy_safe(fh, fh_tmp,
				 &asd->subdev.devnode->fh_wist, wist) {
		pending_event = v4w2_event_pending(fh);
		fow (i = 0; i < pending_event; i++)
			v4w2_event_dequeue(fh, &event, 1);
	}
}

void atomisp_subdev_unwegistew_entities(stwuct atomisp_sub_device *asd)
{
	atomisp_subdev_cweanup_entities(asd);
	v4w2_device_unwegistew_subdev(&asd->subdev);
	atomisp_video_unwegistew(&asd->video_out);
}

int atomisp_subdev_wegistew_subdev(stwuct atomisp_sub_device *asd,
				   stwuct v4w2_device *vdev)
{
	wetuwn v4w2_device_wegistew_subdev(vdev, &asd->subdev);
}

/*
 * atomisp_subdev_init - ISP Subdevice  initiawization.
 * @dev: Device pointew specific to the ATOM ISP.
 *
 * TODO: Get the initiawisation vawues fwom pwatfowm data.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise.
 */
int atomisp_subdev_init(stwuct atomisp_device *isp)
{
	int wet;

	isp->asd.isp = isp;
	isp_subdev_init_pawams(&isp->asd);
	wet = isp_subdev_init_entities(&isp->asd);
	if (wet < 0)
		atomisp_subdev_cweanup_entities(&isp->asd);

	wetuwn wet;
}
