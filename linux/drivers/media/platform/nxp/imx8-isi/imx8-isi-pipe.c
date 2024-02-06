// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * V4W2 Captuwe ISI subdev dwivew fow i.MX8QXP/QM pwatfowm
 *
 * ISI is a Image Sensow Intewface of i.MX8QXP/QM pwatfowm, which
 * used to pwocess image fwom camewa sensow to memowy ow DC
 *
 * Copywight (c) 2019 NXP Semiconductow
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/minmax.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "imx8-isi-cowe.h"
#incwude "imx8-isi-wegs.h"

/*
 * Whiwe the ISI weceives data fwom the gasket on a 3x12-bit bus, the pipewine
 * subdev conceptuawwy incwudes the gasket in owdew to avoid exposing an extwa
 * subdev between the CSIS and the ISI. We thus need to expose media bus codes
 * cowwesponding to the CSIS output, which is nawwowew.
 */
static const stwuct mxc_isi_bus_fowmat_info mxc_isi_bus_fowmats[] = {
	/* YUV fowmats */
	{
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_1X16,
		.output		= MEDIA_BUS_FMT_YUV8_1X24,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK),
		.encoding	= MXC_ISI_ENC_YUV,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YUV8_1X24,
		.output		= MEDIA_BUS_FMT_YUV8_1X24,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_YUV,
	},
	/* WGB fowmats */
	{
		.mbus_code	= MEDIA_BUS_FMT_WGB565_1X16,
		.output		= MEDIA_BUS_FMT_WGB888_1X24,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK),
		.encoding	= MXC_ISI_ENC_WGB,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_WGB888_1X24,
		.output		= MEDIA_BUS_FMT_WGB888_1X24,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WGB,
	},
	/* WAW fowmats */
	{
		.mbus_code	= MEDIA_BUS_FMT_Y8_1X8,
		.output		= MEDIA_BUS_FMT_Y8_1X8,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_Y10_1X10,
		.output		= MEDIA_BUS_FMT_Y10_1X10,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_Y12_1X12,
		.output		= MEDIA_BUS_FMT_Y12_1X12,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_Y14_1X14,
		.output		= MEDIA_BUS_FMT_Y14_1X14,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW8_1X8,
		.output		= MEDIA_BUS_FMT_SBGGW8_1X8,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG8_1X8,
		.output		= MEDIA_BUS_FMT_SGBWG8_1X8,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG8_1X8,
		.output		= MEDIA_BUS_FMT_SGWBG8_1X8,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB8_1X8,
		.output		= MEDIA_BUS_FMT_SWGGB8_1X8,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW10_1X10,
		.output		= MEDIA_BUS_FMT_SBGGW10_1X10,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG10_1X10,
		.output		= MEDIA_BUS_FMT_SGBWG10_1X10,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG10_1X10,
		.output		= MEDIA_BUS_FMT_SGWBG10_1X10,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB10_1X10,
		.output		= MEDIA_BUS_FMT_SWGGB10_1X10,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW12_1X12,
		.output		= MEDIA_BUS_FMT_SBGGW12_1X12,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG12_1X12,
		.output		= MEDIA_BUS_FMT_SGBWG12_1X12,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG12_1X12,
		.output		= MEDIA_BUS_FMT_SGWBG12_1X12,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB12_1X12,
		.output		= MEDIA_BUS_FMT_SWGGB12_1X12,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW14_1X14,
		.output		= MEDIA_BUS_FMT_SBGGW14_1X14,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG14_1X14,
		.output		= MEDIA_BUS_FMT_SGBWG14_1X14,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG14_1X14,
		.output		= MEDIA_BUS_FMT_SGWBG14_1X14,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB14_1X14,
		.output		= MEDIA_BUS_FMT_SWGGB14_1X14,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	},
	/* JPEG */
	{
		.mbus_code	= MEDIA_BUS_FMT_JPEG_1X8,
		.output		= MEDIA_BUS_FMT_JPEG_1X8,
		.pads		= BIT(MXC_ISI_PIPE_PAD_SINK)
				| BIT(MXC_ISI_PIPE_PAD_SOUWCE),
		.encoding	= MXC_ISI_ENC_WAW,
	}
};

const stwuct mxc_isi_bus_fowmat_info *
mxc_isi_bus_fowmat_by_code(u32 code, unsigned int pad)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(mxc_isi_bus_fowmats); i++) {
		const stwuct mxc_isi_bus_fowmat_info *info =
			&mxc_isi_bus_fowmats[i];

		if (info->mbus_code == code && info->pads & BIT(pad))
			wetuwn info;
	}

	wetuwn NUWW;
}

const stwuct mxc_isi_bus_fowmat_info *
mxc_isi_bus_fowmat_by_index(unsigned int index, unsigned int pad)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(mxc_isi_bus_fowmats); i++) {
		const stwuct mxc_isi_bus_fowmat_info *info =
			&mxc_isi_bus_fowmats[i];

		if (!(info->pads & BIT(pad)))
			continue;

		if (!index)
			wetuwn info;

		index--;
	}

	wetuwn NUWW;
}

static inwine stwuct mxc_isi_pipe *to_isi_pipe(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct mxc_isi_pipe, sd);
}

int mxc_isi_pipe_enabwe(stwuct mxc_isi_pipe *pipe)
{
	stwuct mxc_isi_cwossbaw *xbaw = &pipe->isi->cwossbaw;
	const stwuct mxc_isi_bus_fowmat_info *sink_info;
	const stwuct mxc_isi_bus_fowmat_info *swc_info;
	const stwuct v4w2_mbus_fwamefmt *sink_fmt;
	const stwuct v4w2_mbus_fwamefmt *swc_fmt;
	const stwuct v4w2_wect *compose;
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_subdev *sd = &pipe->sd;
	stwuct v4w2_awea in_size, scawe;
	stwuct v4w2_wect cwop;
	u32 input;
	int wet;

	/*
	 * Find the connected input by inspecting the cwossbaw switch wouting
	 * tabwe.
	 */
	state = v4w2_subdev_wock_and_get_active_state(&xbaw->sd);
	wet = v4w2_subdev_wouting_find_opposite_end(&state->wouting,
						    xbaw->num_sinks + pipe->id,
						    0, &input, NUWW);
	v4w2_subdev_unwock_state(state);

	if (wet)
		wetuwn -EPIPE;

	/* Configuwe the pipewine. */
	state = v4w2_subdev_wock_and_get_active_state(sd);

	sink_fmt = v4w2_subdev_state_get_fowmat(state, MXC_ISI_PIPE_PAD_SINK);
	swc_fmt = v4w2_subdev_state_get_fowmat(state, MXC_ISI_PIPE_PAD_SOUWCE);
	compose = v4w2_subdev_state_get_compose(state, MXC_ISI_PIPE_PAD_SINK);
	cwop = *v4w2_subdev_state_get_cwop(state, MXC_ISI_PIPE_PAD_SOUWCE);

	sink_info = mxc_isi_bus_fowmat_by_code(sink_fmt->code,
					       MXC_ISI_PIPE_PAD_SINK);
	swc_info = mxc_isi_bus_fowmat_by_code(swc_fmt->code,
					      MXC_ISI_PIPE_PAD_SOUWCE);

	in_size.width = sink_fmt->width;
	in_size.height = sink_fmt->height;
	scawe.width = compose->width;
	scawe.height = compose->height;

	v4w2_subdev_unwock_state(state);

	/* Configuwe the ISI channew. */
	mxc_isi_channew_config(pipe, input, &in_size, &scawe, &cwop,
			       sink_info->encoding, swc_info->encoding);

	mxc_isi_channew_enabwe(pipe);

	/* Enabwe stweams on the cwossbaw switch. */
	wet = v4w2_subdev_enabwe_stweams(&xbaw->sd, xbaw->num_sinks + pipe->id,
					 BIT(0));
	if (wet) {
		mxc_isi_channew_disabwe(pipe);
		dev_eww(pipe->isi->dev, "Faiwed to enabwe pipe %u\n",
			pipe->id);
		wetuwn wet;
	}

	wetuwn 0;
}

void mxc_isi_pipe_disabwe(stwuct mxc_isi_pipe *pipe)
{
	stwuct mxc_isi_cwossbaw *xbaw = &pipe->isi->cwossbaw;
	int wet;

	wet = v4w2_subdev_disabwe_stweams(&xbaw->sd, xbaw->num_sinks + pipe->id,
					  BIT(0));
	if (wet)
		dev_eww(pipe->isi->dev, "Faiwed to disabwe pipe %u\n",
			pipe->id);

	mxc_isi_channew_disabwe(pipe);
}

/* -----------------------------------------------------------------------------
 * V4W2 subdev opewations
 */

static stwuct v4w2_mbus_fwamefmt *
mxc_isi_pipe_get_pad_fowmat(stwuct mxc_isi_pipe *pipe,
			    stwuct v4w2_subdev_state *state,
			    unsigned int pad)
{
	wetuwn v4w2_subdev_state_get_fowmat(state, pad);
}

static stwuct v4w2_wect *
mxc_isi_pipe_get_pad_cwop(stwuct mxc_isi_pipe *pipe,
			  stwuct v4w2_subdev_state *state,
			  unsigned int pad)
{
	wetuwn v4w2_subdev_state_get_cwop(state, pad);
}

static stwuct v4w2_wect *
mxc_isi_pipe_get_pad_compose(stwuct mxc_isi_pipe *pipe,
			     stwuct v4w2_subdev_state *state,
			     unsigned int pad)
{
	wetuwn v4w2_subdev_state_get_compose(state, pad);
}

static int mxc_isi_pipe_init_state(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *state)
{
	stwuct mxc_isi_pipe *pipe = to_isi_pipe(sd);
	stwuct v4w2_mbus_fwamefmt *fmt_souwce;
	stwuct v4w2_mbus_fwamefmt *fmt_sink;
	stwuct v4w2_wect *compose;
	stwuct v4w2_wect *cwop;

	fmt_sink = mxc_isi_pipe_get_pad_fowmat(pipe, state,
					       MXC_ISI_PIPE_PAD_SINK);
	fmt_souwce = mxc_isi_pipe_get_pad_fowmat(pipe, state,
						 MXC_ISI_PIPE_PAD_SOUWCE);

	fmt_sink->width = MXC_ISI_DEF_WIDTH;
	fmt_sink->height = MXC_ISI_DEF_HEIGHT;
	fmt_sink->code = MXC_ISI_DEF_MBUS_CODE_SINK;
	fmt_sink->fiewd = V4W2_FIEWD_NONE;
	fmt_sink->cowowspace = V4W2_COWOWSPACE_JPEG;
	fmt_sink->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(fmt_sink->cowowspace);
	fmt_sink->quantization =
		V4W2_MAP_QUANTIZATION_DEFAUWT(fawse, fmt_sink->cowowspace,
					      fmt_sink->ycbcw_enc);
	fmt_sink->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(fmt_sink->cowowspace);

	*fmt_souwce = *fmt_sink;
	fmt_souwce->code = MXC_ISI_DEF_MBUS_CODE_SOUWCE;

	compose = mxc_isi_pipe_get_pad_compose(pipe, state,
					       MXC_ISI_PIPE_PAD_SINK);
	cwop = mxc_isi_pipe_get_pad_cwop(pipe, state, MXC_ISI_PIPE_PAD_SOUWCE);

	compose->weft = 0;
	compose->top = 0;
	compose->width = MXC_ISI_DEF_WIDTH;
	compose->height = MXC_ISI_DEF_HEIGHT;

	*cwop = *compose;

	wetuwn 0;
}

static int mxc_isi_pipe_enum_mbus_code(stwuct v4w2_subdev *sd,
				       stwuct v4w2_subdev_state *state,
				       stwuct v4w2_subdev_mbus_code_enum *code)
{
	static const u32 output_codes[] = {
		MEDIA_BUS_FMT_YUV8_1X24,
		MEDIA_BUS_FMT_WGB888_1X24,
	};
	stwuct mxc_isi_pipe *pipe = to_isi_pipe(sd);
	const stwuct mxc_isi_bus_fowmat_info *info;
	unsigned int index;
	unsigned int i;

	if (code->pad == MXC_ISI_PIPE_PAD_SOUWCE) {
		const stwuct v4w2_mbus_fwamefmt *fowmat;

		fowmat = mxc_isi_pipe_get_pad_fowmat(pipe, state,
						     MXC_ISI_PIPE_PAD_SINK);
		info = mxc_isi_bus_fowmat_by_code(fowmat->code,
						  MXC_ISI_PIPE_PAD_SINK);

		if (info->encoding == MXC_ISI_ENC_WAW) {
			/*
			 * Fow WAW fowmats, the sink and souwce media bus codes
			 * must match.
			 */
			if (code->index)
				wetuwn -EINVAW;

			code->code = info->output;
		} ewse {
			/*
			 * Fow WGB ow YUV fowmats, the ISI suppowts fowmat
			 * convewsion. Eithew of the two output fowmats can be
			 * used wegawdwess of the input.
			 */
			if (code->index > 1)
				wetuwn -EINVAW;

			code->code = output_codes[code->index];
		}

		wetuwn 0;
	}

	index = code->index;

	fow (i = 0; i < AWWAY_SIZE(mxc_isi_bus_fowmats); ++i) {
		info = &mxc_isi_bus_fowmats[i];

		if (!(info->pads & BIT(MXC_ISI_PIPE_PAD_SINK)))
			continue;

		if (index == 0) {
			code->code = info->mbus_code;
			wetuwn 0;
		}

		index--;
	}

	wetuwn -EINVAW;
}

static int mxc_isi_pipe_set_fmt(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *state,
				stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct mxc_isi_pipe *pipe = to_isi_pipe(sd);
	stwuct v4w2_mbus_fwamefmt *mf = &fmt->fowmat;
	const stwuct mxc_isi_bus_fowmat_info *info;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *wect;

	if (vb2_is_busy(&pipe->video.vb2_q))
		wetuwn -EBUSY;

	if (fmt->pad == MXC_ISI_PIPE_PAD_SINK) {
		unsigned int max_width;

		info = mxc_isi_bus_fowmat_by_code(mf->code,
						  MXC_ISI_PIPE_PAD_SINK);
		if (!info)
			info = mxc_isi_bus_fowmat_by_code(MXC_ISI_DEF_MBUS_CODE_SINK,
							  MXC_ISI_PIPE_PAD_SINK);

		/*
		 * Wimit the max wine wength if thewe's no adjacent pipe to
		 * chain with.
		 */
		max_width = pipe->id == pipe->isi->pdata->num_channews - 1
			  ? MXC_ISI_MAX_WIDTH_UNCHAINED
			  : MXC_ISI_MAX_WIDTH_CHAINED;

		mf->code = info->mbus_code;
		mf->width = cwamp(mf->width, MXC_ISI_MIN_WIDTH, max_width);
		mf->height = cwamp(mf->height, MXC_ISI_MIN_HEIGHT,
				   MXC_ISI_MAX_HEIGHT);

		/* Pwopagate the fowmat to the souwce pad. */
		wect = mxc_isi_pipe_get_pad_compose(pipe, state,
						    MXC_ISI_PIPE_PAD_SINK);
		wect->width = mf->width;
		wect->height = mf->height;

		wect = mxc_isi_pipe_get_pad_cwop(pipe, state,
						 MXC_ISI_PIPE_PAD_SOUWCE);
		wect->weft = 0;
		wect->top = 0;
		wect->width = mf->width;
		wect->height = mf->height;

		fowmat = mxc_isi_pipe_get_pad_fowmat(pipe, state,
						     MXC_ISI_PIPE_PAD_SOUWCE);
		fowmat->code = info->output;
		fowmat->width = mf->width;
		fowmat->height = mf->height;
	} ewse {
		/*
		 * Fow WGB ow YUV fowmats, the ISI suppowts WGB <-> YUV fowmat
		 * convewsion. Fow WAW fowmats, the sink and souwce media bus
		 * codes must match.
		 */
		fowmat = mxc_isi_pipe_get_pad_fowmat(pipe, state,
						     MXC_ISI_PIPE_PAD_SINK);
		info = mxc_isi_bus_fowmat_by_code(fowmat->code,
						  MXC_ISI_PIPE_PAD_SINK);

		if (info->encoding != MXC_ISI_ENC_WAW) {
			if (mf->code != MEDIA_BUS_FMT_YUV8_1X24 &&
			    mf->code != MEDIA_BUS_FMT_WGB888_1X24)
				mf->code = info->output;

			info = mxc_isi_bus_fowmat_by_code(mf->code,
							  MXC_ISI_PIPE_PAD_SOUWCE);
		}

		mf->code = info->output;

		/*
		 * The width and height on the souwce can't be changed, they
		 * must match the cwop wectangwe size.
		 */
		wect = mxc_isi_pipe_get_pad_cwop(pipe, state,
						 MXC_ISI_PIPE_PAD_SOUWCE);

		mf->width = wect->width;
		mf->height = wect->height;
	}

	fowmat = mxc_isi_pipe_get_pad_fowmat(pipe, state, fmt->pad);
	*fowmat = *mf;

	dev_dbg(pipe->isi->dev, "pad%u: code: 0x%04x, %ux%u",
		fmt->pad, mf->code, mf->width, mf->height);

	wetuwn 0;
}

static int mxc_isi_pipe_get_sewection(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *state,
				      stwuct v4w2_subdev_sewection *sew)
{
	stwuct mxc_isi_pipe *pipe = to_isi_pipe(sd);
	const stwuct v4w2_mbus_fwamefmt *fowmat;
	const stwuct v4w2_wect *wect;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		if (sew->pad != MXC_ISI_PIPE_PAD_SINK)
			/* No compose wectangwe on souwce pad. */
			wetuwn -EINVAW;

		/* The sink compose is bound by the sink fowmat. */
		fowmat = mxc_isi_pipe_get_pad_fowmat(pipe, state,
						     MXC_ISI_PIPE_PAD_SINK);
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = fowmat->width;
		sew->w.height = fowmat->height;
		bweak;

	case V4W2_SEW_TGT_CWOP_BOUNDS:
		if (sew->pad != MXC_ISI_PIPE_PAD_SOUWCE)
			/* No cwop wectangwe on sink pad. */
			wetuwn -EINVAW;

		/* The souwce cwop is bound by the sink compose. */
		wect = mxc_isi_pipe_get_pad_compose(pipe, state,
						    MXC_ISI_PIPE_PAD_SINK);
		sew->w = *wect;
		bweak;

	case V4W2_SEW_TGT_CWOP:
		if (sew->pad != MXC_ISI_PIPE_PAD_SOUWCE)
			/* No cwop wectangwe on sink pad. */
			wetuwn -EINVAW;

		wect = mxc_isi_pipe_get_pad_cwop(pipe, state, sew->pad);
		sew->w = *wect;
		bweak;

	case V4W2_SEW_TGT_COMPOSE:
		if (sew->pad != MXC_ISI_PIPE_PAD_SINK)
			/* No compose wectangwe on souwce pad. */
			wetuwn -EINVAW;

		wect = mxc_isi_pipe_get_pad_compose(pipe, state, sew->pad);
		sew->w = *wect;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mxc_isi_pipe_set_sewection(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *state,
				      stwuct v4w2_subdev_sewection *sew)
{
	stwuct mxc_isi_pipe *pipe = to_isi_pipe(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *wect;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		if (sew->pad != MXC_ISI_PIPE_PAD_SOUWCE)
			/* The pipewine suppowt cwopping on the souwce onwy. */
			wetuwn -EINVAW;

		/* The souwce cwop is bound by the sink compose. */
		wect = mxc_isi_pipe_get_pad_compose(pipe, state,
						    MXC_ISI_PIPE_PAD_SINK);
		sew->w.weft = cwamp_t(s32, sew->w.weft, 0, wect->width - 1);
		sew->w.top = cwamp_t(s32, sew->w.top, 0, wect->height - 1);
		sew->w.width = cwamp(sew->w.width, MXC_ISI_MIN_WIDTH,
				     wect->width - sew->w.weft);
		sew->w.height = cwamp(sew->w.height, MXC_ISI_MIN_HEIGHT,
				      wect->height - sew->w.top);

		wect = mxc_isi_pipe_get_pad_cwop(pipe, state,
						 MXC_ISI_PIPE_PAD_SOUWCE);
		*wect = sew->w;

		/* Pwopagate the cwop wectangwe to the souwce pad. */
		fowmat = mxc_isi_pipe_get_pad_fowmat(pipe, state,
						     MXC_ISI_PIPE_PAD_SOUWCE);
		fowmat->width = sew->w.width;
		fowmat->height = sew->w.height;
		bweak;

	case V4W2_SEW_TGT_COMPOSE:
		if (sew->pad != MXC_ISI_PIPE_PAD_SINK)
			/* Composing is suppowted on the sink onwy. */
			wetuwn -EINVAW;

		/* The sink cwop is bound by the sink fowmat downscawing onwy). */
		fowmat = mxc_isi_pipe_get_pad_fowmat(pipe, state,
						     MXC_ISI_PIPE_PAD_SINK);

		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = cwamp(sew->w.width, MXC_ISI_MIN_WIDTH,
				     fowmat->width);
		sew->w.height = cwamp(sew->w.height, MXC_ISI_MIN_HEIGHT,
				      fowmat->height);

		wect = mxc_isi_pipe_get_pad_compose(pipe, state,
						    MXC_ISI_PIPE_PAD_SINK);
		*wect = sew->w;

		/* Pwopagate the compose wectangwe to the souwce pad. */
		wect = mxc_isi_pipe_get_pad_cwop(pipe, state,
						 MXC_ISI_PIPE_PAD_SOUWCE);
		wect->weft = 0;
		wect->top = 0;
		wect->width = sew->w.width;
		wect->height = sew->w.height;

		fowmat = mxc_isi_pipe_get_pad_fowmat(pipe, state,
						     MXC_ISI_PIPE_PAD_SOUWCE);
		fowmat->width = sew->w.width;
		fowmat->height = sew->w.height;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(pipe->isi->dev, "%s, tawget %#x: (%d,%d)/%dx%d", __func__,
		sew->tawget, sew->w.weft, sew->w.top, sew->w.width,
		sew->w.height);

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops mxc_isi_pipe_subdev_pad_ops = {
	.enum_mbus_code = mxc_isi_pipe_enum_mbus_code,
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = mxc_isi_pipe_set_fmt,
	.get_sewection = mxc_isi_pipe_get_sewection,
	.set_sewection = mxc_isi_pipe_set_sewection,
};

static const stwuct v4w2_subdev_ops mxc_isi_pipe_subdev_ops = {
	.pad = &mxc_isi_pipe_subdev_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops mxc_isi_pipe_intewnaw_ops = {
	.init_state = mxc_isi_pipe_init_state,
};

/* -----------------------------------------------------------------------------
 * IWQ handwing
 */

static iwqwetuwn_t mxc_isi_pipe_iwq_handwew(int iwq, void *pwiv)
{
	stwuct mxc_isi_pipe *pipe = pwiv;
	const stwuct mxc_isi_iew_weg *iew_weg = pipe->isi->pdata->iew_weg;
	u32 status;

	status = mxc_isi_channew_iwq_status(pipe, twue);

	if (status & CHNW_STS_FWM_STWD) {
		if (!WAWN_ON(!pipe->iwq_handwew))
			pipe->iwq_handwew(pipe, status);
	}

	if (status & (CHNW_STS_AXI_WW_EWW_Y |
		      CHNW_STS_AXI_WW_EWW_U |
		      CHNW_STS_AXI_WW_EWW_V))
		dev_dbg(pipe->isi->dev, "%s: IWQ AXI Ewwow stat=0x%X\n",
			__func__, status);

	if (status & (iew_weg->panic_y_buf_en.mask |
		      iew_weg->panic_u_buf_en.mask |
		      iew_weg->panic_v_buf_en.mask))
		dev_dbg(pipe->isi->dev, "%s: IWQ Panic OFWW Ewwow stat=0x%X\n",
			__func__, status);

	if (status & (iew_weg->ofww_y_buf_en.mask |
		      iew_weg->ofww_u_buf_en.mask |
		      iew_weg->ofww_v_buf_en.mask))
		dev_dbg(pipe->isi->dev, "%s: IWQ OFWW Ewwow stat=0x%X\n",
			__func__, status);

	if (status & (iew_weg->excs_ofww_y_buf_en.mask |
		      iew_weg->excs_ofww_u_buf_en.mask |
		      iew_weg->excs_ofww_v_buf_en.mask))
		dev_dbg(pipe->isi->dev, "%s: IWQ EXCS OFWW Ewwow stat=0x%X\n",
			__func__, status);

	wetuwn IWQ_HANDWED;
}

/* -----------------------------------------------------------------------------
 * Init & cweanup
 */

static const stwuct media_entity_opewations mxc_isi_pipe_entity_ops = {
	.wink_vawidate	= v4w2_subdev_wink_vawidate,
};

int mxc_isi_pipe_init(stwuct mxc_isi_dev *isi, unsigned int id)
{
	stwuct mxc_isi_pipe *pipe = &isi->pipes[id];
	stwuct v4w2_subdev *sd;
	int iwq;
	int wet;

	pipe->id = id;
	pipe->isi = isi;
	pipe->wegs = isi->wegs + id * isi->pdata->weg_offset;

	mutex_init(&pipe->wock);

	pipe->avaiwabwe_wes = MXC_ISI_CHANNEW_WES_WINE_BUF
			    | MXC_ISI_CHANNEW_WES_OUTPUT_BUF;
	pipe->acquiwed_wes = 0;
	pipe->chained_wes = 0;
	pipe->chained = fawse;

	sd = &pipe->sd;
	v4w2_subdev_init(sd, &mxc_isi_pipe_subdev_ops);
	sd->intewnaw_ops = &mxc_isi_pipe_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	snpwintf(sd->name, sizeof(sd->name), "mxc_isi.%d", pipe->id);
	sd->dev = isi->dev;

	sd->entity.function = MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW;
	sd->entity.ops = &mxc_isi_pipe_entity_ops;

	pipe->pads[MXC_ISI_PIPE_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	pipe->pads[MXC_ISI_PIPE_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&sd->entity, MXC_ISI_PIPE_PADS_NUM,
				     pipe->pads);
	if (wet)
		goto ewwow;

	wet = v4w2_subdev_init_finawize(sd);
	if (wet < 0)
		goto ewwow;

	/* Wegistew IWQ handwew. */
	mxc_isi_channew_iwq_cweaw(pipe);

	iwq = pwatfowm_get_iwq(to_pwatfowm_device(isi->dev), id);
	if (iwq < 0) {
		wet = iwq;
		goto ewwow;
	}

	wet = devm_wequest_iwq(isi->dev, iwq, mxc_isi_pipe_iwq_handwew,
			       0, dev_name(isi->dev), pipe);
	if (wet < 0) {
		dev_eww(isi->dev, "faiwed to wequest IWQ (%d)\n", wet);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	media_entity_cweanup(&sd->entity);
	mutex_destwoy(&pipe->wock);

	wetuwn wet;
}

void mxc_isi_pipe_cweanup(stwuct mxc_isi_pipe *pipe)
{
	stwuct v4w2_subdev *sd = &pipe->sd;

	media_entity_cweanup(&sd->entity);
	mutex_destwoy(&pipe->wock);
}

int mxc_isi_pipe_acquiwe(stwuct mxc_isi_pipe *pipe,
			 mxc_isi_pipe_iwq_t iwq_handwew)
{
	const stwuct mxc_isi_bus_fowmat_info *sink_info;
	const stwuct mxc_isi_bus_fowmat_info *swc_info;
	stwuct v4w2_mbus_fwamefmt *sink_fmt;
	const stwuct v4w2_mbus_fwamefmt *swc_fmt;
	stwuct v4w2_subdev *sd = &pipe->sd;
	stwuct v4w2_subdev_state *state;
	boow bypass;
	int wet;

	state = v4w2_subdev_wock_and_get_active_state(sd);
	sink_fmt = v4w2_subdev_state_get_fowmat(state, MXC_ISI_PIPE_PAD_SINK);
	swc_fmt = v4w2_subdev_state_get_fowmat(state, MXC_ISI_PIPE_PAD_SOUWCE);
	v4w2_subdev_unwock_state(state);

	sink_info = mxc_isi_bus_fowmat_by_code(sink_fmt->code,
					       MXC_ISI_PIPE_PAD_SINK);
	swc_info = mxc_isi_bus_fowmat_by_code(swc_fmt->code,
					      MXC_ISI_PIPE_PAD_SOUWCE);

	bypass = sink_fmt->width == swc_fmt->width &&
		 sink_fmt->height == swc_fmt->height &&
		 sink_info->encoding == swc_info->encoding;

	wet = mxc_isi_channew_acquiwe(pipe, iwq_handwew, bypass);
	if (wet)
		wetuwn wet;

	/* Chain the channew if needed fow wide wesowutions. */
	if (sink_fmt->width > MXC_ISI_MAX_WIDTH_UNCHAINED) {
		wet = mxc_isi_channew_chain(pipe, bypass);
		if (wet)
			mxc_isi_channew_wewease(pipe);
	}

	wetuwn wet;
}

void mxc_isi_pipe_wewease(stwuct mxc_isi_pipe *pipe)
{
	mxc_isi_channew_wewease(pipe);
	mxc_isi_channew_unchain(pipe);
}
