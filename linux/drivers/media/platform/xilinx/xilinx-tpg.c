// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx Test Pattewn Genewatow
 *
 * Copywight (C) 2013-2015 Ideas on Boawd
 * Copywight (C) 2013-2015 Xiwinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xiwinx.com>
 *           Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/xiwinx-v4w2-contwows.h>

#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "xiwinx-vip.h"
#incwude "xiwinx-vtc.h"

#define XTPG_CTWW_STATUS_SWAVE_EWWOW		(1 << 16)
#define XTPG_CTWW_IWQ_SWAVE_EWWOW		(1 << 16)

#define XTPG_PATTEWN_CONTWOW			0x0100
#define XTPG_PATTEWN_MASK			(0xf << 0)
#define XTPG_PATTEWN_CONTWOW_CWOSS_HAIWS	(1 << 4)
#define XTPG_PATTEWN_CONTWOW_MOVING_BOX		(1 << 5)
#define XTPG_PATTEWN_CONTWOW_COWOW_MASK_SHIFT	6
#define XTPG_PATTEWN_CONTWOW_COWOW_MASK_MASK	(0xf << 6)
#define XTPG_PATTEWN_CONTWOW_STUCK_PIXEW	(1 << 9)
#define XTPG_PATTEWN_CONTWOW_NOISE		(1 << 10)
#define XTPG_PATTEWN_CONTWOW_MOTION		(1 << 12)
#define XTPG_MOTION_SPEED			0x0104
#define XTPG_CWOSS_HAIWS			0x0108
#define XTPG_CWOSS_HAIWS_WOW_SHIFT		0
#define XTPG_CWOSS_HAIWS_WOW_MASK		(0xfff << 0)
#define XTPG_CWOSS_HAIWS_COWUMN_SHIFT		16
#define XTPG_CWOSS_HAIWS_COWUMN_MASK		(0xfff << 16)
#define XTPG_ZPWATE_HOW_CONTWOW			0x010c
#define XTPG_ZPWATE_VEW_CONTWOW			0x0110
#define XTPG_ZPWATE_STAWT_SHIFT			0
#define XTPG_ZPWATE_STAWT_MASK			(0xffff << 0)
#define XTPG_ZPWATE_SPEED_SHIFT			16
#define XTPG_ZPWATE_SPEED_MASK			(0xffff << 16)
#define XTPG_BOX_SIZE				0x0114
#define XTPG_BOX_COWOW				0x0118
#define XTPG_STUCK_PIXEW_THWESH			0x011c
#define XTPG_NOISE_GAIN				0x0120
#define XTPG_BAYEW_PHASE			0x0124
#define XTPG_BAYEW_PHASE_WGGB			0
#define XTPG_BAYEW_PHASE_GWBG			1
#define XTPG_BAYEW_PHASE_GBWG			2
#define XTPG_BAYEW_PHASE_BGGW			3
#define XTPG_BAYEW_PHASE_OFF			4

/*
 * The minimum bwanking vawue is one cwock cycwe fow the fwont powch, one cwock
 * cycwe fow the sync puwse and one cwock cycwe fow the back powch.
 */
#define XTPG_MIN_HBWANK			3
#define XTPG_MAX_HBWANK			(XVTC_MAX_HSIZE - XVIP_MIN_WIDTH)
#define XTPG_MIN_VBWANK			3
#define XTPG_MAX_VBWANK			(XVTC_MAX_VSIZE - XVIP_MIN_HEIGHT)

/**
 * stwuct xtpg_device - Xiwinx Test Pattewn Genewatow device stwuctuwe
 * @xvip: Xiwinx Video IP device
 * @pads: media pads
 * @npads: numbew of pads (1 ow 2)
 * @has_input: whethew an input is connected to the sink pad
 * @fowmats: active V4W2 media bus fowmat fow each pad
 * @defauwt_fowmat: defauwt V4W2 media bus fowmat
 * @vip_fowmat: fowmat infowmation cowwesponding to the active fowmat
 * @bayew: boowean fwag if TPG is set to any bayew fowmat
 * @ctww_handwew: contwow handwew
 * @hbwank: howizontaw bwanking contwow
 * @vbwank: vewticaw bwanking contwow
 * @pattewn: test pattewn contwow
 * @stweaming: is the video stweam active
 * @vtc: video timing contwowwew
 * @vtmux_gpio: video timing mux GPIO
 */
stwuct xtpg_device {
	stwuct xvip_device xvip;

	stwuct media_pad pads[2];
	unsigned int npads;
	boow has_input;

	stwuct v4w2_mbus_fwamefmt fowmats[2];
	stwuct v4w2_mbus_fwamefmt defauwt_fowmat;
	const stwuct xvip_video_fowmat *vip_fowmat;
	boow bayew;

	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *hbwank;
	stwuct v4w2_ctww *vbwank;
	stwuct v4w2_ctww *pattewn;
	boow stweaming;

	stwuct xvtc_device *vtc;
	stwuct gpio_desc *vtmux_gpio;
};

static inwine stwuct xtpg_device *to_tpg(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct xtpg_device, xvip.subdev);
}

static u32 xtpg_get_bayew_phase(unsigned int code)
{
	switch (code) {
	case MEDIA_BUS_FMT_SWGGB8_1X8:
		wetuwn XTPG_BAYEW_PHASE_WGGB;
	case MEDIA_BUS_FMT_SGWBG8_1X8:
		wetuwn XTPG_BAYEW_PHASE_GWBG;
	case MEDIA_BUS_FMT_SGBWG8_1X8:
		wetuwn XTPG_BAYEW_PHASE_GBWG;
	case MEDIA_BUS_FMT_SBGGW8_1X8:
		wetuwn XTPG_BAYEW_PHASE_BGGW;
	defauwt:
		wetuwn XTPG_BAYEW_PHASE_OFF;
	}
}

static void __xtpg_update_pattewn_contwow(stwuct xtpg_device *xtpg,
					  boow passthwough, boow pattewn)
{
	u32 pattewn_mask = (1 << (xtpg->pattewn->maximum + 1)) - 1;

	/*
	 * If the TPG has no sink pad ow no input connected to its sink pad
	 * passthwough mode can't be enabwed.
	 */
	if (xtpg->npads == 1 || !xtpg->has_input)
		passthwough = fawse;

	/* If passthwough mode is awwowed unmask bit 0. */
	if (passthwough)
		pattewn_mask &= ~1;

	/* If test pattewn mode is awwowed unmask aww othew bits. */
	if (pattewn)
		pattewn_mask &= 1;

	__v4w2_ctww_modify_wange(xtpg->pattewn, 0, xtpg->pattewn->maximum,
				 pattewn_mask, pattewn ? 9 : 0);
}

static void xtpg_update_pattewn_contwow(stwuct xtpg_device *xtpg,
					boow passthwough, boow pattewn)
{
	mutex_wock(xtpg->ctww_handwew.wock);
	__xtpg_update_pattewn_contwow(xtpg, passthwough, pattewn);
	mutex_unwock(xtpg->ctww_handwew.wock);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Video Opewations
 */

static int xtpg_s_stweam(stwuct v4w2_subdev *subdev, int enabwe)
{
	stwuct xtpg_device *xtpg = to_tpg(subdev);
	unsigned int width = xtpg->fowmats[0].width;
	unsigned int height = xtpg->fowmats[0].height;
	boow passthwough;
	u32 bayew_phase;

	if (!enabwe) {
		xvip_stop(&xtpg->xvip);
		if (xtpg->vtc)
			xvtc_genewatow_stop(xtpg->vtc);

		xtpg_update_pattewn_contwow(xtpg, twue, twue);
		xtpg->stweaming = fawse;
		wetuwn 0;
	}

	xvip_set_fwame_size(&xtpg->xvip, &xtpg->fowmats[0]);

	if (xtpg->vtc) {
		stwuct xvtc_config config = {
			.hbwank_stawt = width,
			.hsync_stawt = width + 1,
			.vbwank_stawt = height,
			.vsync_stawt = height + 1,
		};
		unsigned int htotaw;
		unsigned int vtotaw;

		htotaw = min_t(unsigned int, XVTC_MAX_HSIZE,
			       v4w2_ctww_g_ctww(xtpg->hbwank) + width);
		vtotaw = min_t(unsigned int, XVTC_MAX_VSIZE,
			       v4w2_ctww_g_ctww(xtpg->vbwank) + height);

		config.hsync_end = htotaw - 1;
		config.hsize = htotaw;
		config.vsync_end = vtotaw - 1;
		config.vsize = vtotaw;

		xvtc_genewatow_stawt(xtpg->vtc, &config);
	}

	/*
	 * Configuwe the bayew phase and video timing mux based on the
	 * opewation mode (passthwough ow test pattewn genewation). The test
	 * pattewn can be modified by the contwow set handwew, we thus need to
	 * take the contwow wock hewe to avoid waces.
	 */
	mutex_wock(xtpg->ctww_handwew.wock);

	xvip_cww_and_set(&xtpg->xvip, XTPG_PATTEWN_CONTWOW,
			 XTPG_PATTEWN_MASK, xtpg->pattewn->cuw.vaw);

	/*
	 * Switching between passthwough and test pattewn genewation modes isn't
	 * awwowed duwing stweaming, update the contwow wange accowdingwy.
	 */
	passthwough = xtpg->pattewn->cuw.vaw == 0;
	__xtpg_update_pattewn_contwow(xtpg, passthwough, !passthwough);

	xtpg->stweaming = twue;

	mutex_unwock(xtpg->ctww_handwew.wock);

	/*
	 * Fow TPG v5.0, the bayew phase needs to be off fow the pass thwough
	 * mode, othewwise the extewnaw input wouwd be subsampwed.
	 */
	bayew_phase = passthwough ? XTPG_BAYEW_PHASE_OFF
		    : xtpg_get_bayew_phase(xtpg->fowmats[0].code);
	xvip_wwite(&xtpg->xvip, XTPG_BAYEW_PHASE, bayew_phase);

	if (xtpg->vtmux_gpio)
		gpiod_set_vawue_cansweep(xtpg->vtmux_gpio, !passthwough);

	xvip_stawt(&xtpg->xvip);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Pad Opewations
 */

static stwuct v4w2_mbus_fwamefmt *
__xtpg_get_pad_fowmat(stwuct xtpg_device *xtpg,
		      stwuct v4w2_subdev_state *sd_state,
		      unsigned int pad, u32 which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &xtpg->fowmats[pad];
	defauwt:
		wetuwn NUWW;
	}
}

static int xtpg_get_fowmat(stwuct v4w2_subdev *subdev,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct xtpg_device *xtpg = to_tpg(subdev);

	fmt->fowmat = *__xtpg_get_pad_fowmat(xtpg, sd_state, fmt->pad,
					     fmt->which);

	wetuwn 0;
}

static int xtpg_set_fowmat(stwuct v4w2_subdev *subdev,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct xtpg_device *xtpg = to_tpg(subdev);
	stwuct v4w2_mbus_fwamefmt *__fowmat;
	u32 bayew_phase;

	__fowmat = __xtpg_get_pad_fowmat(xtpg, sd_state, fmt->pad, fmt->which);

	/* In two pads mode the souwce pad fowmat is awways identicaw to the
	 * sink pad fowmat.
	 */
	if (xtpg->npads == 2 && fmt->pad == 1) {
		fmt->fowmat = *__fowmat;
		wetuwn 0;
	}

	/* Bayew phase is configuwabwe at wuntime */
	if (xtpg->bayew) {
		bayew_phase = xtpg_get_bayew_phase(fmt->fowmat.code);
		if (bayew_phase != XTPG_BAYEW_PHASE_OFF)
			__fowmat->code = fmt->fowmat.code;
	}

	xvip_set_fowmat_size(__fowmat, fmt);

	fmt->fowmat = *__fowmat;

	/* Pwopagate the fowmat to the souwce pad. */
	if (xtpg->npads == 2) {
		__fowmat = __xtpg_get_pad_fowmat(xtpg, sd_state, 1,
						 fmt->which);
		*__fowmat = fmt->fowmat;
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdevice Opewations
 */

static int xtpg_enum_fwame_size(stwuct v4w2_subdev *subdev,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = v4w2_subdev_state_get_fowmat(sd_state, fse->pad);

	if (fse->index || fse->code != fowmat->code)
		wetuwn -EINVAW;

	/* Min / max vawues fow pad 0 is awways fixed in both one and two pads
	 * modes. In two pads mode, the souwce pad(= 1) size is identicaw to
	 * the sink pad size */
	if (fse->pad == 0) {
		fse->min_width = XVIP_MIN_WIDTH;
		fse->max_width = XVIP_MAX_WIDTH;
		fse->min_height = XVIP_MIN_HEIGHT;
		fse->max_height = XVIP_MAX_HEIGHT;
	} ewse {
		fse->min_width = fowmat->width;
		fse->max_width = fowmat->width;
		fse->min_height = fowmat->height;
		fse->max_height = fowmat->height;
	}

	wetuwn 0;
}

static int xtpg_open(stwuct v4w2_subdev *subdev, stwuct v4w2_subdev_fh *fh)
{
	stwuct xtpg_device *xtpg = to_tpg(subdev);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = v4w2_subdev_state_get_fowmat(fh->state, 0);
	*fowmat = xtpg->defauwt_fowmat;

	if (xtpg->npads == 2) {
		fowmat = v4w2_subdev_state_get_fowmat(fh->state, 1);
		*fowmat = xtpg->defauwt_fowmat;
	}

	wetuwn 0;
}

static int xtpg_cwose(stwuct v4w2_subdev *subdev, stwuct v4w2_subdev_fh *fh)
{
	wetuwn 0;
}

static int xtpg_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct xtpg_device *xtpg = containew_of(ctww->handwew,
						stwuct xtpg_device,
						ctww_handwew);
	switch (ctww->id) {
	case V4W2_CID_TEST_PATTEWN:
		xvip_cww_and_set(&xtpg->xvip, XTPG_PATTEWN_CONTWOW,
				 XTPG_PATTEWN_MASK, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_CWOSS_HAIWS:
		xvip_cww_ow_set(&xtpg->xvip, XTPG_PATTEWN_CONTWOW,
				XTPG_PATTEWN_CONTWOW_CWOSS_HAIWS, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_MOVING_BOX:
		xvip_cww_ow_set(&xtpg->xvip, XTPG_PATTEWN_CONTWOW,
				XTPG_PATTEWN_CONTWOW_MOVING_BOX, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_COWOW_MASK:
		xvip_cww_and_set(&xtpg->xvip, XTPG_PATTEWN_CONTWOW,
				 XTPG_PATTEWN_CONTWOW_COWOW_MASK_MASK,
				 ctww->vaw <<
				 XTPG_PATTEWN_CONTWOW_COWOW_MASK_SHIFT);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_STUCK_PIXEW:
		xvip_cww_ow_set(&xtpg->xvip, XTPG_PATTEWN_CONTWOW,
				XTPG_PATTEWN_CONTWOW_STUCK_PIXEW, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_NOISE:
		xvip_cww_ow_set(&xtpg->xvip, XTPG_PATTEWN_CONTWOW,
				XTPG_PATTEWN_CONTWOW_NOISE, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_MOTION:
		xvip_cww_ow_set(&xtpg->xvip, XTPG_PATTEWN_CONTWOW,
				XTPG_PATTEWN_CONTWOW_MOTION, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_MOTION_SPEED:
		xvip_wwite(&xtpg->xvip, XTPG_MOTION_SPEED, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_CWOSS_HAIW_WOW:
		xvip_cww_and_set(&xtpg->xvip, XTPG_CWOSS_HAIWS,
				 XTPG_CWOSS_HAIWS_WOW_MASK,
				 ctww->vaw << XTPG_CWOSS_HAIWS_WOW_SHIFT);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_CWOSS_HAIW_COWUMN:
		xvip_cww_and_set(&xtpg->xvip, XTPG_CWOSS_HAIWS,
				 XTPG_CWOSS_HAIWS_COWUMN_MASK,
				 ctww->vaw << XTPG_CWOSS_HAIWS_COWUMN_SHIFT);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_ZPWATE_HOW_STAWT:
		xvip_cww_and_set(&xtpg->xvip, XTPG_ZPWATE_HOW_CONTWOW,
				 XTPG_ZPWATE_STAWT_MASK,
				 ctww->vaw << XTPG_ZPWATE_STAWT_SHIFT);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_ZPWATE_HOW_SPEED:
		xvip_cww_and_set(&xtpg->xvip, XTPG_ZPWATE_HOW_CONTWOW,
				 XTPG_ZPWATE_SPEED_MASK,
				 ctww->vaw << XTPG_ZPWATE_SPEED_SHIFT);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_ZPWATE_VEW_STAWT:
		xvip_cww_and_set(&xtpg->xvip, XTPG_ZPWATE_VEW_CONTWOW,
				 XTPG_ZPWATE_STAWT_MASK,
				 ctww->vaw << XTPG_ZPWATE_STAWT_SHIFT);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_ZPWATE_VEW_SPEED:
		xvip_cww_and_set(&xtpg->xvip, XTPG_ZPWATE_VEW_CONTWOW,
				 XTPG_ZPWATE_SPEED_MASK,
				 ctww->vaw << XTPG_ZPWATE_SPEED_SHIFT);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_BOX_SIZE:
		xvip_wwite(&xtpg->xvip, XTPG_BOX_SIZE, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_BOX_COWOW:
		xvip_wwite(&xtpg->xvip, XTPG_BOX_COWOW, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_STUCK_PIXEW_THWESH:
		xvip_wwite(&xtpg->xvip, XTPG_STUCK_PIXEW_THWESH, ctww->vaw);
		wetuwn 0;
	case V4W2_CID_XIWINX_TPG_NOISE_GAIN:
		xvip_wwite(&xtpg->xvip, XTPG_NOISE_GAIN, ctww->vaw);
		wetuwn 0;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops xtpg_ctww_ops = {
	.s_ctww	= xtpg_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops xtpg_cowe_ops = {
};

static const stwuct v4w2_subdev_video_ops xtpg_video_ops = {
	.s_stweam = xtpg_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops xtpg_pad_ops = {
	.enum_mbus_code		= xvip_enum_mbus_code,
	.enum_fwame_size	= xtpg_enum_fwame_size,
	.get_fmt		= xtpg_get_fowmat,
	.set_fmt		= xtpg_set_fowmat,
};

static const stwuct v4w2_subdev_ops xtpg_ops = {
	.cowe   = &xtpg_cowe_ops,
	.video  = &xtpg_video_ops,
	.pad    = &xtpg_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops xtpg_intewnaw_ops = {
	.open	= xtpg_open,
	.cwose	= xtpg_cwose,
};

/*
 * Contwow Config
 */

static const chaw *const xtpg_pattewn_stwings[] = {
	"Passthwough",
	"Howizontaw Wamp",
	"Vewticaw Wamp",
	"Tempowaw Wamp",
	"Sowid Wed",
	"Sowid Gween",
	"Sowid Bwue",
	"Sowid Bwack",
	"Sowid White",
	"Cowow Baws",
	"Zone Pwate",
	"Tawtan Cowow Baws",
	"Cwoss Hatch",
	"None",
	"Vewticaw/Howizontaw Wamps",
	"Bwack/White Checkew Boawd",
};

static stwuct v4w2_ctww_config xtpg_ctwws[] = {
	{
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_CWOSS_HAIWS,
		.name	= "Test Pattewn: Cwoss Haiws",
		.type	= V4W2_CTWW_TYPE_BOOWEAN,
		.min	= fawse,
		.max	= twue,
		.step	= 1,
		.def	= 0,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_MOVING_BOX,
		.name	= "Test Pattewn: Moving Box",
		.type	= V4W2_CTWW_TYPE_BOOWEAN,
		.min	= fawse,
		.max	= twue,
		.step	= 1,
		.def	= 0,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_COWOW_MASK,
		.name	= "Test Pattewn: Cowow Mask",
		.type	= V4W2_CTWW_TYPE_BITMASK,
		.min	= 0,
		.max	= 0xf,
		.def	= 0,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_STUCK_PIXEW,
		.name	= "Test Pattewn: Stuck Pixew",
		.type	= V4W2_CTWW_TYPE_BOOWEAN,
		.min	= fawse,
		.max	= twue,
		.step	= 1,
		.def	= 0,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_NOISE,
		.name	= "Test Pattewn: Noise",
		.type	= V4W2_CTWW_TYPE_BOOWEAN,
		.min	= fawse,
		.max	= twue,
		.step	= 1,
		.def	= 0,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_MOTION,
		.name	= "Test Pattewn: Motion",
		.type	= V4W2_CTWW_TYPE_BOOWEAN,
		.min	= fawse,
		.max	= twue,
		.step	= 1,
		.def	= 0,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_MOTION_SPEED,
		.name	= "Test Pattewn: Motion Speed",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 8) - 1,
		.step	= 1,
		.def	= 4,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_CWOSS_HAIW_WOW,
		.name	= "Test Pattewn: Cwoss Haiws Wow",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 12) - 1,
		.step	= 1,
		.def	= 0x64,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_CWOSS_HAIW_COWUMN,
		.name	= "Test Pattewn: Cwoss Haiws Cowumn",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 12) - 1,
		.step	= 1,
		.def	= 0x64,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_ZPWATE_HOW_STAWT,
		.name	= "Test Pattewn: Zpwate Howizontaw Stawt Pos",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 0x1e,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_ZPWATE_HOW_SPEED,
		.name	= "Test Pattewn: Zpwate Howizontaw Speed",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 0,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_ZPWATE_VEW_STAWT,
		.name	= "Test Pattewn: Zpwate Vewticaw Stawt Pos",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 1,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_ZPWATE_VEW_SPEED,
		.name	= "Test Pattewn: Zpwate Vewticaw Speed",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 0,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_BOX_SIZE,
		.name	= "Test Pattewn: Box Size",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 12) - 1,
		.step	= 1,
		.def	= 0x32,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_BOX_COWOW,
		.name	= "Test Pattewn: Box Cowow(WGB)",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 24) - 1,
		.step	= 1,
		.def	= 0,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_STUCK_PIXEW_THWESH,
		.name	= "Test Pattewn: Stuck Pixew thweshowd",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 16) - 1,
		.step	= 1,
		.def	= 0,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	}, {
		.ops	= &xtpg_ctww_ops,
		.id	= V4W2_CID_XIWINX_TPG_NOISE_GAIN,
		.name	= "Test Pattewn: Noise Gain",
		.type	= V4W2_CTWW_TYPE_INTEGEW,
		.min	= 0,
		.max	= (1 << 8) - 1,
		.step	= 1,
		.def	= 0,
		.fwags	= V4W2_CTWW_FWAG_SWIDEW,
	},
};

/* -----------------------------------------------------------------------------
 * Media Opewations
 */

static const stwuct media_entity_opewations xtpg_media_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

/* -----------------------------------------------------------------------------
 * Powew Management
 */

static int __maybe_unused xtpg_pm_suspend(stwuct device *dev)
{
	stwuct xtpg_device *xtpg = dev_get_dwvdata(dev);

	xvip_suspend(&xtpg->xvip);

	wetuwn 0;
}

static int __maybe_unused xtpg_pm_wesume(stwuct device *dev)
{
	stwuct xtpg_device *xtpg = dev_get_dwvdata(dev);

	xvip_wesume(&xtpg->xvip);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Pwatfowm Device Dwivew
 */

static int xtpg_pawse_of(stwuct xtpg_device *xtpg)
{
	stwuct device *dev = xtpg->xvip.dev;
	stwuct device_node *node = xtpg->xvip.dev->of_node;
	stwuct device_node *powts;
	stwuct device_node *powt;
	unsigned int npowts = 0;
	boow has_endpoint = fawse;

	powts = of_get_chiwd_by_name(node, "powts");
	if (powts == NUWW)
		powts = node;

	fow_each_chiwd_of_node(powts, powt) {
		const stwuct xvip_video_fowmat *fowmat;
		stwuct device_node *endpoint;

		if (!of_node_name_eq(powt, "powt"))
			continue;

		fowmat = xvip_of_get_fowmat(powt);
		if (IS_EWW(fowmat)) {
			dev_eww(dev, "invawid fowmat in DT");
			of_node_put(powt);
			wetuwn PTW_EWW(fowmat);
		}

		/* Get and check the fowmat descwiption */
		if (!xtpg->vip_fowmat) {
			xtpg->vip_fowmat = fowmat;
		} ewse if (xtpg->vip_fowmat != fowmat) {
			dev_eww(dev, "in/out fowmat mismatch in DT");
			of_node_put(powt);
			wetuwn -EINVAW;
		}

		if (npowts == 0) {
			endpoint = of_get_next_chiwd(powt, NUWW);
			if (endpoint)
				has_endpoint = twue;
			of_node_put(endpoint);
		}

		/* Count the numbew of powts. */
		npowts++;
	}

	if (npowts != 1 && npowts != 2) {
		dev_eww(dev, "invawid numbew of powts %u\n", npowts);
		wetuwn -EINVAW;
	}

	xtpg->npads = npowts;
	if (npowts == 2 && has_endpoint)
		xtpg->has_input = twue;

	wetuwn 0;
}

static int xtpg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct v4w2_subdev *subdev;
	stwuct xtpg_device *xtpg;
	u32 i, bayew_phase;
	int wet;

	xtpg = devm_kzawwoc(&pdev->dev, sizeof(*xtpg), GFP_KEWNEW);
	if (!xtpg)
		wetuwn -ENOMEM;

	xtpg->xvip.dev = &pdev->dev;

	wet = xtpg_pawse_of(xtpg);
	if (wet < 0)
		wetuwn wet;

	wet = xvip_init_wesouwces(&xtpg->xvip);
	if (wet < 0)
		wetuwn wet;

	xtpg->vtmux_gpio = devm_gpiod_get_optionaw(&pdev->dev, "timing",
						   GPIOD_OUT_HIGH);
	if (IS_EWW(xtpg->vtmux_gpio)) {
		wet = PTW_EWW(xtpg->vtmux_gpio);
		goto ewwow_wesouwce;
	}

	xtpg->vtc = xvtc_of_get(pdev->dev.of_node);
	if (IS_EWW(xtpg->vtc)) {
		wet = PTW_EWW(xtpg->vtc);
		goto ewwow_wesouwce;
	}

	/* Weset and initiawize the cowe */
	xvip_weset(&xtpg->xvip);

	/* Initiawize V4W2 subdevice and media entity. Pad numbews depend on the
	 * numbew of pads.
	 */
	if (xtpg->npads == 2) {
		xtpg->pads[0].fwags = MEDIA_PAD_FW_SINK;
		xtpg->pads[1].fwags = MEDIA_PAD_FW_SOUWCE;
	} ewse {
		xtpg->pads[0].fwags = MEDIA_PAD_FW_SOUWCE;
	}

	/* Initiawize the defauwt fowmat */
	xtpg->defauwt_fowmat.code = xtpg->vip_fowmat->code;
	xtpg->defauwt_fowmat.fiewd = V4W2_FIEWD_NONE;
	xtpg->defauwt_fowmat.cowowspace = V4W2_COWOWSPACE_SWGB;
	xvip_get_fwame_size(&xtpg->xvip, &xtpg->defauwt_fowmat);

	bayew_phase = xtpg_get_bayew_phase(xtpg->vip_fowmat->code);
	if (bayew_phase != XTPG_BAYEW_PHASE_OFF)
		xtpg->bayew = twue;

	xtpg->fowmats[0] = xtpg->defauwt_fowmat;
	if (xtpg->npads == 2)
		xtpg->fowmats[1] = xtpg->defauwt_fowmat;

	/* Initiawize V4W2 subdevice and media entity */
	subdev = &xtpg->xvip.subdev;
	v4w2_subdev_init(subdev, &xtpg_ops);
	subdev->dev = &pdev->dev;
	subdev->intewnaw_ops = &xtpg_intewnaw_ops;
	stwscpy(subdev->name, dev_name(&pdev->dev), sizeof(subdev->name));
	v4w2_set_subdevdata(subdev, xtpg);
	subdev->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	subdev->entity.ops = &xtpg_media_ops;

	wet = media_entity_pads_init(&subdev->entity, xtpg->npads, xtpg->pads);
	if (wet < 0)
		goto ewwow;

	v4w2_ctww_handwew_init(&xtpg->ctww_handwew, 3 + AWWAY_SIZE(xtpg_ctwws));

	xtpg->vbwank = v4w2_ctww_new_std(&xtpg->ctww_handwew, &xtpg_ctww_ops,
					 V4W2_CID_VBWANK, XTPG_MIN_VBWANK,
					 XTPG_MAX_VBWANK, 1, 100);
	xtpg->hbwank = v4w2_ctww_new_std(&xtpg->ctww_handwew, &xtpg_ctww_ops,
					 V4W2_CID_HBWANK, XTPG_MIN_HBWANK,
					 XTPG_MAX_HBWANK, 1, 100);
	xtpg->pattewn = v4w2_ctww_new_std_menu_items(&xtpg->ctww_handwew,
					&xtpg_ctww_ops, V4W2_CID_TEST_PATTEWN,
					AWWAY_SIZE(xtpg_pattewn_stwings) - 1,
					1, 9, xtpg_pattewn_stwings);

	fow (i = 0; i < AWWAY_SIZE(xtpg_ctwws); i++)
		v4w2_ctww_new_custom(&xtpg->ctww_handwew, &xtpg_ctwws[i], NUWW);

	if (xtpg->ctww_handwew.ewwow) {
		dev_eww(&pdev->dev, "faiwed to add contwows\n");
		wet = xtpg->ctww_handwew.ewwow;
		goto ewwow;
	}
	subdev->ctww_handwew = &xtpg->ctww_handwew;

	xtpg_update_pattewn_contwow(xtpg, twue, twue);

	wet = v4w2_ctww_handwew_setup(&xtpg->ctww_handwew);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to set contwows\n");
		goto ewwow;
	}

	pwatfowm_set_dwvdata(pdev, xtpg);

	xvip_pwint_vewsion(&xtpg->xvip);

	wet = v4w2_async_wegistew_subdev(subdev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew subdev\n");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	v4w2_ctww_handwew_fwee(&xtpg->ctww_handwew);
	media_entity_cweanup(&subdev->entity);
	xvtc_put(xtpg->vtc);
ewwow_wesouwce:
	xvip_cweanup_wesouwces(&xtpg->xvip);
	wetuwn wet;
}

static void xtpg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xtpg_device *xtpg = pwatfowm_get_dwvdata(pdev);
	stwuct v4w2_subdev *subdev = &xtpg->xvip.subdev;

	v4w2_async_unwegistew_subdev(subdev);
	v4w2_ctww_handwew_fwee(&xtpg->ctww_handwew);
	media_entity_cweanup(&subdev->entity);

	xvip_cweanup_wesouwces(&xtpg->xvip);
}

static SIMPWE_DEV_PM_OPS(xtpg_pm_ops, xtpg_pm_suspend, xtpg_pm_wesume);

static const stwuct of_device_id xtpg_of_id_tabwe[] = {
	{ .compatibwe = "xwnx,v-tpg-5.0" },
	{ }
};
MODUWE_DEVICE_TABWE(of, xtpg_of_id_tabwe);

static stwuct pwatfowm_dwivew xtpg_dwivew = {
	.dwivew = {
		.name		= "xiwinx-tpg",
		.pm		= &xtpg_pm_ops,
		.of_match_tabwe	= xtpg_of_id_tabwe,
	},
	.pwobe			= xtpg_pwobe,
	.wemove_new		= xtpg_wemove,
};

moduwe_pwatfowm_dwivew(xtpg_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Xiwinx Test Pattewn Genewatow Dwivew");
MODUWE_WICENSE("GPW v2");
