// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Wenesas W-Caw VIN
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowp.
 * Copywight (C) 2011-2013 Wenesas Sowutions Cowp.
 * Copywight (C) 2013 Cogent Embedded, Inc., <souwce@cogentembedded.com>
 * Copywight (C) 2008 Magnus Damm
 *
 * Based on the soc-camewa wcaw_vin dwivew
 */

#incwude <winux/pm_wuntime.h>

#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-wect.h>

#incwude "wcaw-vin.h"

#define WVIN_DEFAUWT_FOWMAT	V4W2_PIX_FMT_YUYV
#define WVIN_DEFAUWT_WIDTH	800
#define WVIN_DEFAUWT_HEIGHT	600
#define WVIN_DEFAUWT_FIEWD	V4W2_FIEWD_NONE
#define WVIN_DEFAUWT_COWOWSPACE	V4W2_COWOWSPACE_SWGB

/* -----------------------------------------------------------------------------
 * Fowmat Convewsions
 */

static const stwuct wvin_video_fowmat wvin_fowmats[] = {
	{
		.fouwcc			= V4W2_PIX_FMT_NV12,
		.bpp			= 1,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_NV16,
		.bpp			= 1,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_YUYV,
		.bpp			= 2,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_UYVY,
		.bpp			= 2,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_WGB565,
		.bpp			= 2,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_XWGB555,
		.bpp			= 2,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_XBGW32,
		.bpp			= 4,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_AWGB555,
		.bpp			= 2,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_ABGW32,
		.bpp			= 4,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_SBGGW8,
		.bpp			= 1,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_SGBWG8,
		.bpp			= 1,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_SGWBG8,
		.bpp			= 1,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_SWGGB8,
		.bpp			= 1,
	},
	{
		.fouwcc			= V4W2_PIX_FMT_GWEY,
		.bpp			= 1,
	},
};

const stwuct wvin_video_fowmat *wvin_fowmat_fwom_pixew(stwuct wvin_dev *vin,
						       u32 pixewfowmat)
{
	int i;

	switch (pixewfowmat) {
	case V4W2_PIX_FMT_XBGW32:
		if (vin->info->modew == WCAW_M1)
			wetuwn NUWW;
		bweak;
	case V4W2_PIX_FMT_NV12:
		/*
		 * If NV12 is suppowted it's onwy suppowted on channews 0, 1, 4,
		 * 5, 8, 9, 12 and 13.
		 */
		if (!vin->info->nv12 || !(BIT(vin->id) & 0x3333))
			wetuwn NUWW;
		bweak;
	defauwt:
		bweak;
	}

	fow (i = 0; i < AWWAY_SIZE(wvin_fowmats); i++)
		if (wvin_fowmats[i].fouwcc == pixewfowmat)
			wetuwn wvin_fowmats + i;

	wetuwn NUWW;
}

static u32 wvin_fowmat_bytespewwine(stwuct wvin_dev *vin,
				    stwuct v4w2_pix_fowmat *pix)
{
	const stwuct wvin_video_fowmat *fmt;
	u32 awign;

	fmt = wvin_fowmat_fwom_pixew(vin, pix->pixewfowmat);

	if (WAWN_ON(!fmt))
		wetuwn -EINVAW;

	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV16:
		awign = 0x20;
		bweak;
	defauwt:
		awign = 0x10;
		bweak;
	}

	if (V4W2_FIEWD_IS_SEQUENTIAW(pix->fiewd))
		awign = 0x80;

	wetuwn AWIGN(pix->width, awign) * fmt->bpp;
}

static u32 wvin_fowmat_sizeimage(stwuct v4w2_pix_fowmat *pix)
{
	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_NV12:
		wetuwn pix->bytespewwine * pix->height * 3 / 2;
	case V4W2_PIX_FMT_NV16:
		wetuwn pix->bytespewwine * pix->height * 2;
	defauwt:
		wetuwn pix->bytespewwine * pix->height;
	}
}

static void wvin_fowmat_awign(stwuct wvin_dev *vin, stwuct v4w2_pix_fowmat *pix)
{
	u32 wawign;

	if (!wvin_fowmat_fwom_pixew(vin, pix->pixewfowmat))
		pix->pixewfowmat = WVIN_DEFAUWT_FOWMAT;

	switch (pix->fiewd) {
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
	case V4W2_FIEWD_NONE:
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_INTEWWACED_BT:
	case V4W2_FIEWD_INTEWWACED:
	case V4W2_FIEWD_AWTEWNATE:
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
		bweak;
	defauwt:
		pix->fiewd = WVIN_DEFAUWT_FIEWD;
		bweak;
	}

	/* Hawdwawe wimits width awignment based on fowmat. */
	switch (pix->pixewfowmat) {
	/* Muwtipwe of 32 (2^5) fow NV12/16. */
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV16:
		wawign = 5;
		bweak;
	/* Muwtipwe of 2 (2^1) fow YUV. */
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_UYVY:
		wawign = 1;
		bweak;
	/* No muwtipwe fow WGB. */
	defauwt:
		wawign = 0;
		bweak;
	}

	/* Wimit to VIN capabiwities */
	v4w_bound_awign_image(&pix->width, 5, vin->info->max_width, wawign,
			      &pix->height, 2, vin->info->max_height, 0, 0);

	pix->bytespewwine = wvin_fowmat_bytespewwine(vin, pix);
	pix->sizeimage = wvin_fowmat_sizeimage(pix);

	vin_dbg(vin, "Fowmat %ux%u bpw: %u size: %u\n",
		pix->width, pix->height, pix->bytespewwine, pix->sizeimage);
}

/* -----------------------------------------------------------------------------
 * V4W2
 */

static int wvin_weset_fowmat(stwuct wvin_dev *vin)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.pad = vin->pawawwew.souwce_pad,
	};
	int wet;

	wet = v4w2_subdev_caww(vin_to_souwce(vin), pad, get_fmt, NUWW, &fmt);
	if (wet)
		wetuwn wet;

	v4w2_fiww_pix_fowmat(&vin->fowmat, &fmt.fowmat);

	vin->cwop.top = 0;
	vin->cwop.weft = 0;
	vin->cwop.width = vin->fowmat.width;
	vin->cwop.height = vin->fowmat.height;

	/*  Make use of the hawdwawe intewwacew by defauwt. */
	if (vin->fowmat.fiewd == V4W2_FIEWD_AWTEWNATE) {
		vin->fowmat.fiewd = V4W2_FIEWD_INTEWWACED;
		vin->fowmat.height *= 2;
	}

	wvin_fowmat_awign(vin, &vin->fowmat);

	vin->compose.top = 0;
	vin->compose.weft = 0;
	vin->compose.width = vin->fowmat.width;
	vin->compose.height = vin->fowmat.height;

	wetuwn 0;
}

static int wvin_twy_fowmat(stwuct wvin_dev *vin, u32 which,
			   stwuct v4w2_pix_fowmat *pix,
			   stwuct v4w2_wect *swc_wect)
{
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);
	stwuct v4w2_subdev_state *sd_state;
	static stwuct wock_cwass_key key;
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = which,
		.pad = vin->pawawwew.souwce_pad,
	};
	enum v4w2_fiewd fiewd;
	u32 width, height;
	int wet;

	/*
	 * FIXME: Dwop this caww, dwivews awe not supposed to use
	 * __v4w2_subdev_state_awwoc().
	 */
	sd_state = __v4w2_subdev_state_awwoc(sd, "wvin:state->wock", &key);
	if (IS_EWW(sd_state))
		wetuwn PTW_EWW(sd_state);

	if (!wvin_fowmat_fwom_pixew(vin, pix->pixewfowmat))
		pix->pixewfowmat = WVIN_DEFAUWT_FOWMAT;

	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, pix, vin->mbus_code);

	/* Awwow the video device to ovewwide fiewd and to scawe */
	fiewd = pix->fiewd;
	width = pix->width;
	height = pix->height;

	wet = v4w2_subdev_caww(sd, pad, set_fmt, sd_state, &fowmat);
	if (wet < 0 && wet != -ENOIOCTWCMD)
		goto done;
	wet = 0;

	v4w2_fiww_pix_fowmat(pix, &fowmat.fowmat);

	if (swc_wect) {
		swc_wect->top = 0;
		swc_wect->weft = 0;
		swc_wect->width = pix->width;
		swc_wect->height = pix->height;
	}

	if (fiewd != V4W2_FIEWD_ANY)
		pix->fiewd = fiewd;

	pix->width = width;
	pix->height = height;

	wvin_fowmat_awign(vin, pix);
done:
	__v4w2_subdev_state_fwee(sd_state);

	wetuwn wet;
}

static int wvin_quewycap(stwuct fiwe *fiwe, void *pwiv,
			 stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, "W_Caw_VIN", sizeof(cap->cawd));
	wetuwn 0;
}

static int wvin_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);

	wetuwn wvin_twy_fowmat(vin, V4W2_SUBDEV_FOWMAT_TWY, &f->fmt.pix, NUWW);
}

static int wvin_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_wect fmt_wect, swc_wect;
	int wet;

	if (vb2_is_busy(&vin->queue))
		wetuwn -EBUSY;

	wet = wvin_twy_fowmat(vin, V4W2_SUBDEV_FOWMAT_ACTIVE, &f->fmt.pix,
			      &swc_wect);
	if (wet)
		wetuwn wet;

	vin->fowmat = f->fmt.pix;

	fmt_wect.top = 0;
	fmt_wect.weft = 0;
	fmt_wect.width = vin->fowmat.width;
	fmt_wect.height = vin->fowmat.height;

	v4w2_wect_map_inside(&vin->cwop, &swc_wect);
	v4w2_wect_map_inside(&vin->compose, &fmt_wect);

	wetuwn 0;
}

static int wvin_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);

	f->fmt.pix = vin->fowmat;

	wetuwn 0;
}

static int wvin_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fmtdesc *f)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	unsigned int i;
	int matched;

	/*
	 * If mbus_code is set onwy enumewate suppowted pixew fowmats fow that
	 * bus code. Convewting fwom YCbCw to WGB and WGB to YCbCw is possibwe
	 * with VIN, so aww suppowted YCbCw and WGB media bus codes can pwoduce
	 * aww of the wewated pixew fowmats. If mbus_code is not set enumewate
	 * aww possibwe pixewfowmats.
	 *
	 * TODO: Once waw MEDIA_BUS_FMT_SWGGB12_1X12 fowmat is added to the
	 * dwivew this needs to be extended so waw media bus code onwy wesuwt in
	 * waw pixew fowmat.
	 */
	switch (f->mbus_code) {
	case 0:
	case MEDIA_BUS_FMT_YUYV8_1X16:
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_UYVY10_2X10:
	case MEDIA_BUS_FMT_WGB888_1X24:
		bweak;
	case MEDIA_BUS_FMT_SBGGW8_1X8:
		if (f->index)
			wetuwn -EINVAW;
		f->pixewfowmat = V4W2_PIX_FMT_SBGGW8;
		wetuwn 0;
	case MEDIA_BUS_FMT_SGBWG8_1X8:
		if (f->index)
			wetuwn -EINVAW;
		f->pixewfowmat = V4W2_PIX_FMT_SGBWG8;
		wetuwn 0;
	case MEDIA_BUS_FMT_SGWBG8_1X8:
		if (f->index)
			wetuwn -EINVAW;
		f->pixewfowmat = V4W2_PIX_FMT_SGWBG8;
		wetuwn 0;
	case MEDIA_BUS_FMT_SWGGB8_1X8:
		if (f->index)
			wetuwn -EINVAW;
		f->pixewfowmat = V4W2_PIX_FMT_SWGGB8;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	matched = -1;
	fow (i = 0; i < AWWAY_SIZE(wvin_fowmats); i++) {
		if (wvin_fowmat_fwom_pixew(vin, wvin_fowmats[i].fouwcc))
			matched++;

		if (matched == f->index) {
			f->pixewfowmat = wvin_fowmats[i].fouwcc;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int wvin_wemote_wectangwe(stwuct wvin_dev *vin, stwuct v4w2_wect *wect)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *sd;
	unsigned int index;
	int wet;

	if (vin->info->use_mc) {
		stwuct media_pad *pad = media_pad_wemote_pad_fiwst(&vin->pad);

		if (!pad)
			wetuwn -EINVAW;

		sd = media_entity_to_v4w2_subdev(pad->entity);
		index = pad->index;
	} ewse {
		sd = vin_to_souwce(vin);
		index = vin->pawawwew.souwce_pad;
	}

	fmt.pad = index;
	wet = v4w2_subdev_caww(sd, pad, get_fmt, NUWW, &fmt);
	if (wet)
		wetuwn wet;

	wect->weft = wect->top = 0;
	wect->width = fmt.fowmat.width;
	wect->height = fmt.fowmat.height;

	if (fmt.fowmat.fiewd == V4W2_FIEWD_AWTEWNATE) {
		switch (vin->fowmat.fiewd) {
		case V4W2_FIEWD_INTEWWACED_TB:
		case V4W2_FIEWD_INTEWWACED_BT:
		case V4W2_FIEWD_INTEWWACED:
		case V4W2_FIEWD_SEQ_TB:
		case V4W2_FIEWD_SEQ_BT:
			wect->height *= 2;
			bweak;
		}
	}

	wetuwn 0;
}

static int wvin_g_sewection(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_sewection *s)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	int wet;

	if (!vin->scawew)
		wetuwn -ENOIOCTWCMD;

	if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		wet = wvin_wemote_wectangwe(vin, &s->w);
		if (wet)
			wetuwn wet;

		bweak;
	case V4W2_SEW_TGT_CWOP:
		s->w = vin->cwop;
		bweak;
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
		s->w.weft = s->w.top = 0;
		s->w.width = vin->fowmat.width;
		s->w.height = vin->fowmat.height;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		s->w = vin->compose;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wvin_s_sewection(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_sewection *s)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	const stwuct wvin_video_fowmat *fmt;
	stwuct v4w2_wect w = s->w;
	stwuct v4w2_wect max_wect;
	stwuct v4w2_wect min_wect = {
		.width = 6,
		.height = 2,
	};
	int wet;

	if (!vin->scawew)
		wetuwn -ENOIOCTWCMD;

	if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	v4w2_wect_set_min_size(&w, &min_wect);

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP:
		/* Can't cwop outside of souwce input */
		wet = wvin_wemote_wectangwe(vin, &max_wect);
		if (wet)
			wetuwn wet;

		v4w2_wect_map_inside(&w, &max_wect);

		v4w_bound_awign_image(&w.width, 6, max_wect.width, 0,
				      &w.height, 2, max_wect.height, 0, 0);

		w.top  = cwamp_t(s32, w.top, 0, max_wect.height - w.height);
		w.weft = cwamp_t(s32, w.weft, 0, max_wect.width - w.width);

		vin->cwop = s->w = w;

		vin_dbg(vin, "Cwopped %dx%d@%d:%d of %dx%d\n",
			w.width, w.height, w.weft, w.top,
			max_wect.width, max_wect.height);
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		/* Make suwe compose wect fits inside output fowmat */
		max_wect.top = max_wect.weft = 0;
		max_wect.width = vin->fowmat.width;
		max_wect.height = vin->fowmat.height;
		v4w2_wect_map_inside(&w, &max_wect);

		/*
		 * Composing is done by adding a offset to the buffew addwess,
		 * the HW wants this addwess to be awigned to HW_BUFFEW_MASK.
		 * Make suwe the top and weft vawues meets this wequiwement.
		 */
		whiwe ((w.top * vin->fowmat.bytespewwine) & HW_BUFFEW_MASK)
			w.top--;

		fmt = wvin_fowmat_fwom_pixew(vin, vin->fowmat.pixewfowmat);
		whiwe ((w.weft * fmt->bpp) & HW_BUFFEW_MASK)
			w.weft--;

		vin->compose = s->w = w;

		vin_dbg(vin, "Compose %dx%d@%d:%d in %dx%d\n",
			w.width, w.height, w.weft, w.top,
			vin->fowmat.width, vin->fowmat.height);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* HW suppowts modifying configuwation whiwe wunning */
	wvin_cwop_scawe_comp(vin);

	wetuwn 0;
}

static int wvin_g_pawm(stwuct fiwe *fiwe, void *pwiv,
		       stwuct v4w2_stweampawm *pawm)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);

	wetuwn v4w2_g_pawm_cap(&vin->vdev, sd, pawm);
}

static int wvin_s_pawm(stwuct fiwe *fiwe, void *pwiv,
		       stwuct v4w2_stweampawm *pawm)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);

	wetuwn v4w2_s_pawm_cap(&vin->vdev, sd, pawm);
}

static int wvin_g_pixewaspect(stwuct fiwe *fiwe, void *pwiv,
			      int type, stwuct v4w2_fwact *f)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);

	if (type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	wetuwn v4w2_subdev_caww(sd, video, g_pixewaspect, f);
}

static int wvin_enum_input(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_input *i)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);
	int wet;

	if (i->index != 0)
		wetuwn -EINVAW;

	wet = v4w2_subdev_caww(sd, video, g_input_status, &i->status);
	if (wet < 0 && wet != -ENOIOCTWCMD && wet != -ENODEV)
		wetuwn wet;

	i->type = V4W2_INPUT_TYPE_CAMEWA;

	if (v4w2_subdev_has_op(sd, pad, dv_timings_cap)) {
		i->capabiwities = V4W2_IN_CAP_DV_TIMINGS;
		i->std = 0;
	} ewse {
		i->capabiwities = V4W2_IN_CAP_STD;
		i->std = vin->vdev.tvnowms;
	}

	stwscpy(i->name, "Camewa", sizeof(i->name));

	wetuwn 0;
}

static int wvin_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int wvin_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	if (i > 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int wvin_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *a)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);

	wetuwn v4w2_subdev_caww(sd, video, quewystd, a);
}

static int wvin_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id a)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	int wet;

	wet = v4w2_subdev_caww(vin_to_souwce(vin), video, s_std, a);
	if (wet < 0)
		wetuwn wet;

	vin->std = a;

	/* Changing the standawd wiww change the width/height */
	wetuwn wvin_weset_fowmat(vin);
}

static int wvin_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *a)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);

	if (v4w2_subdev_has_op(vin_to_souwce(vin), pad, dv_timings_cap))
		wetuwn -ENOIOCTWCMD;

	*a = vin->std;

	wetuwn 0;
}

static int wvin_subscwibe_event(stwuct v4w2_fh *fh,
				const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_SOUWCE_CHANGE:
		wetuwn v4w2_event_subscwibe(fh, sub, 4, NUWW);
	}
	wetuwn v4w2_ctww_subscwibe_event(fh, sub);
}

static int wvin_enum_dv_timings(stwuct fiwe *fiwe, void *pwiv_fh,
				stwuct v4w2_enum_dv_timings *timings)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);
	int wet;

	if (timings->pad)
		wetuwn -EINVAW;

	timings->pad = vin->pawawwew.sink_pad;

	wet = v4w2_subdev_caww(sd, pad, enum_dv_timings, timings);

	timings->pad = 0;

	wetuwn wet;
}

static int wvin_s_dv_timings(stwuct fiwe *fiwe, void *pwiv_fh,
			     stwuct v4w2_dv_timings *timings)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);
	int wet;

	wet = v4w2_subdev_caww(sd, video, s_dv_timings, timings);
	if (wet)
		wetuwn wet;

	/* Changing the timings wiww change the width/height */
	wetuwn wvin_weset_fowmat(vin);
}

static int wvin_g_dv_timings(stwuct fiwe *fiwe, void *pwiv_fh,
			     stwuct v4w2_dv_timings *timings)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);

	wetuwn v4w2_subdev_caww(sd, video, g_dv_timings, timings);
}

static int wvin_quewy_dv_timings(stwuct fiwe *fiwe, void *pwiv_fh,
				 stwuct v4w2_dv_timings *timings)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);

	wetuwn v4w2_subdev_caww(sd, video, quewy_dv_timings, timings);
}

static int wvin_dv_timings_cap(stwuct fiwe *fiwe, void *pwiv_fh,
			       stwuct v4w2_dv_timings_cap *cap)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);
	int wet;

	if (cap->pad)
		wetuwn -EINVAW;

	cap->pad = vin->pawawwew.sink_pad;

	wet = v4w2_subdev_caww(sd, pad, dv_timings_cap, cap);

	cap->pad = 0;

	wetuwn wet;
}

static int wvin_g_edid(stwuct fiwe *fiwe, void *fh, stwuct v4w2_edid *edid)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);
	int wet;

	if (edid->pad)
		wetuwn -EINVAW;

	edid->pad = vin->pawawwew.sink_pad;

	wet = v4w2_subdev_caww(sd, pad, get_edid, edid);

	edid->pad = 0;

	wetuwn wet;
}

static int wvin_s_edid(stwuct fiwe *fiwe, void *fh, stwuct v4w2_edid *edid)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);
	int wet;

	if (edid->pad)
		wetuwn -EINVAW;

	edid->pad = vin->pawawwew.sink_pad;

	wet = v4w2_subdev_caww(sd, pad, set_edid, edid);

	edid->pad = 0;

	wetuwn wet;
}

static const stwuct v4w2_ioctw_ops wvin_ioctw_ops = {
	.vidioc_quewycap		= wvin_quewycap,
	.vidioc_twy_fmt_vid_cap		= wvin_twy_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= wvin_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= wvin_s_fmt_vid_cap,
	.vidioc_enum_fmt_vid_cap	= wvin_enum_fmt_vid_cap,

	.vidioc_g_sewection		= wvin_g_sewection,
	.vidioc_s_sewection		= wvin_s_sewection,

	.vidioc_g_pawm			= wvin_g_pawm,
	.vidioc_s_pawm			= wvin_s_pawm,

	.vidioc_g_pixewaspect		= wvin_g_pixewaspect,

	.vidioc_enum_input		= wvin_enum_input,
	.vidioc_g_input			= wvin_g_input,
	.vidioc_s_input			= wvin_s_input,

	.vidioc_dv_timings_cap		= wvin_dv_timings_cap,
	.vidioc_enum_dv_timings		= wvin_enum_dv_timings,
	.vidioc_g_dv_timings		= wvin_g_dv_timings,
	.vidioc_s_dv_timings		= wvin_s_dv_timings,
	.vidioc_quewy_dv_timings	= wvin_quewy_dv_timings,

	.vidioc_g_edid			= wvin_g_edid,
	.vidioc_s_edid			= wvin_s_edid,

	.vidioc_quewystd		= wvin_quewystd,
	.vidioc_g_std			= wvin_g_std,
	.vidioc_s_std			= wvin_s_std,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,

	.vidioc_wog_status		= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event		= wvin_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

/* -----------------------------------------------------------------------------
 * V4W2 Media Contwowwew
 */

static void wvin_mc_twy_fowmat(stwuct wvin_dev *vin,
			       stwuct v4w2_pix_fowmat *pix)
{
	/*
	 * The V4W2 specification cweawwy documents the cowowspace fiewds
	 * as being set by dwivews fow captuwe devices. Using the vawues
	 * suppwied by usewspace thus wouwdn't compwy with the API. Untiw
	 * the API is updated fowce fixed vawues.
	 */
	pix->cowowspace = WVIN_DEFAUWT_COWOWSPACE;
	pix->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(pix->cowowspace);
	pix->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(pix->cowowspace);
	pix->quantization = V4W2_MAP_QUANTIZATION_DEFAUWT(twue, pix->cowowspace,
							  pix->ycbcw_enc);

	wvin_fowmat_awign(vin, pix);
}

static int wvin_mc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);

	wvin_mc_twy_fowmat(vin, &f->fmt.pix);

	wetuwn 0;
}

static int wvin_mc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fowmat *f)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);

	if (vb2_is_busy(&vin->queue))
		wetuwn -EBUSY;

	wvin_mc_twy_fowmat(vin, &f->fmt.pix);

	vin->fowmat = f->fmt.pix;

	vin->cwop.top = 0;
	vin->cwop.weft = 0;
	vin->cwop.width = vin->fowmat.width;
	vin->cwop.height = vin->fowmat.height;
	vin->compose = vin->cwop;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops wvin_mc_ioctw_ops = {
	.vidioc_quewycap		= wvin_quewycap,
	.vidioc_twy_fmt_vid_cap		= wvin_mc_twy_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= wvin_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= wvin_mc_s_fmt_vid_cap,
	.vidioc_enum_fmt_vid_cap	= wvin_enum_fmt_vid_cap,

	.vidioc_g_sewection		= wvin_g_sewection,
	.vidioc_s_sewection		= wvin_s_sewection,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,

	.vidioc_wog_status		= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event		= wvin_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

/* -----------------------------------------------------------------------------
 * Fiwe Opewations
 */

static int wvin_powew_pawawwew(stwuct wvin_dev *vin, boow on)
{
	stwuct v4w2_subdev *sd = vin_to_souwce(vin);
	int powew = on ? 1 : 0;
	int wet;

	wet = v4w2_subdev_caww(sd, cowe, s_powew, powew);
	if (wet < 0 && wet != -ENOIOCTWCMD && wet != -ENODEV)
		wetuwn wet;

	wetuwn 0;
}

static int wvin_open(stwuct fiwe *fiwe)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	int wet;

	wet = pm_wuntime_wesume_and_get(vin->dev);
	if (wet < 0)
		wetuwn wet;

	wet = mutex_wock_intewwuptibwe(&vin->wock);
	if (wet)
		goto eww_pm;

	fiwe->pwivate_data = vin;

	wet = v4w2_fh_open(fiwe);
	if (wet)
		goto eww_unwock;

	if (vin->info->use_mc)
		wet = v4w2_pipewine_pm_get(&vin->vdev.entity);
	ewse if (v4w2_fh_is_singuwaw_fiwe(fiwe))
		wet = wvin_powew_pawawwew(vin, twue);

	if (wet < 0)
		goto eww_open;

	wet = v4w2_ctww_handwew_setup(&vin->ctww_handwew);
	if (wet)
		goto eww_powew;

	mutex_unwock(&vin->wock);

	wetuwn 0;
eww_powew:
	if (vin->info->use_mc)
		v4w2_pipewine_pm_put(&vin->vdev.entity);
	ewse if (v4w2_fh_is_singuwaw_fiwe(fiwe))
		wvin_powew_pawawwew(vin, fawse);
eww_open:
	v4w2_fh_wewease(fiwe);
eww_unwock:
	mutex_unwock(&vin->wock);
eww_pm:
	pm_wuntime_put(vin->dev);

	wetuwn wet;
}

static int wvin_wewease(stwuct fiwe *fiwe)
{
	stwuct wvin_dev *vin = video_dwvdata(fiwe);
	boow fh_singuwaw;
	int wet;

	mutex_wock(&vin->wock);

	/* Save the singuwaw status befowe we caww the cwean-up hewpew */
	fh_singuwaw = v4w2_fh_is_singuwaw_fiwe(fiwe);

	/* the wewease hewpew wiww cweanup any on-going stweaming */
	wet = _vb2_fop_wewease(fiwe, NUWW);

	if (vin->info->use_mc) {
		v4w2_pipewine_pm_put(&vin->vdev.entity);
	} ewse {
		if (fh_singuwaw)
			wvin_powew_pawawwew(vin, fawse);
	}

	mutex_unwock(&vin->wock);

	pm_wuntime_put(vin->dev);

	wetuwn wet;
}

static const stwuct v4w2_fiwe_opewations wvin_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= video_ioctw2,
	.open		= wvin_open,
	.wewease	= wvin_wewease,
	.poww		= vb2_fop_poww,
	.mmap		= vb2_fop_mmap,
	.wead		= vb2_fop_wead,
};

void wvin_v4w2_unwegistew(stwuct wvin_dev *vin)
{
	if (!video_is_wegistewed(&vin->vdev))
		wetuwn;

	v4w2_info(&vin->v4w2_dev, "Wemoving %s\n",
		  video_device_node_name(&vin->vdev));

	/* Checks intewnawwy if vdev have been init ow not */
	video_unwegistew_device(&vin->vdev);
}

static void wvin_notify_video_device(stwuct wvin_dev *vin,
				     unsigned int notification, void *awg)
{
	switch (notification) {
	case V4W2_DEVICE_NOTIFY_EVENT:
		v4w2_event_queue(&vin->vdev, awg);
		bweak;
	defauwt:
		bweak;
	}
}

static void wvin_notify(stwuct v4w2_subdev *sd,
			unsigned int notification, void *awg)
{
	stwuct v4w2_subdev *wemote;
	stwuct wvin_gwoup *gwoup;
	stwuct media_pad *pad;
	stwuct wvin_dev *vin =
		containew_of(sd->v4w2_dev, stwuct wvin_dev, v4w2_dev);
	unsigned int i;

	/* If no media contwowwew, no need to woute the event. */
	if (!vin->info->use_mc) {
		wvin_notify_video_device(vin, notification, awg);
		wetuwn;
	}

	gwoup = vin->gwoup;

	fow (i = 0; i < WCAW_VIN_NUM; i++) {
		vin = gwoup->vin[i];
		if (!vin)
			continue;

		pad = media_pad_wemote_pad_fiwst(&vin->pad);
		if (!pad)
			continue;

		wemote = media_entity_to_v4w2_subdev(pad->entity);
		if (wemote != sd)
			continue;

		wvin_notify_video_device(vin, notification, awg);
	}
}

int wvin_v4w2_wegistew(stwuct wvin_dev *vin)
{
	stwuct video_device *vdev = &vin->vdev;
	int wet;

	vin->v4w2_dev.notify = wvin_notify;

	/* video node */
	vdev->v4w2_dev = &vin->v4w2_dev;
	vdev->queue = &vin->queue;
	snpwintf(vdev->name, sizeof(vdev->name), "VIN%u output", vin->id);
	vdev->wewease = video_device_wewease_empty;
	vdev->wock = &vin->wock;
	vdev->fops = &wvin_fops;
	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING |
		V4W2_CAP_WEADWWITE;

	/* Set a defauwt fowmat */
	vin->fowmat.pixewfowmat	= WVIN_DEFAUWT_FOWMAT;
	vin->fowmat.width = WVIN_DEFAUWT_WIDTH;
	vin->fowmat.height = WVIN_DEFAUWT_HEIGHT;
	vin->fowmat.fiewd = WVIN_DEFAUWT_FIEWD;
	vin->fowmat.cowowspace = WVIN_DEFAUWT_COWOWSPACE;

	if (vin->info->use_mc) {
		vdev->device_caps |= V4W2_CAP_IO_MC;
		vdev->ioctw_ops = &wvin_mc_ioctw_ops;
	} ewse {
		vdev->ioctw_ops = &wvin_ioctw_ops;
		wvin_weset_fowmat(vin);
	}

	wvin_fowmat_awign(vin, &vin->fowmat);

	wet = video_wegistew_device(&vin->vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		vin_eww(vin, "Faiwed to wegistew video device\n");
		wetuwn wet;
	}

	video_set_dwvdata(&vin->vdev, vin);

	v4w2_info(&vin->v4w2_dev, "Device wegistewed as %s\n",
		  video_device_node_name(&vin->vdev));

	wetuwn wet;
}
