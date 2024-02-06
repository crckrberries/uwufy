// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-vid-out.c - video output suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/videodev2.h>
#incwude <winux/v4w2-dv-timings.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-wect.h>

#incwude "vivid-cowe.h"
#incwude "vivid-vid-common.h"
#incwude "vivid-kthwead-out.h"
#incwude "vivid-vid-out.h"

static int vid_out_queue_setup(stwuct vb2_queue *vq,
		       unsigned *nbuffews, unsigned *npwanes,
		       unsigned sizes[], stwuct device *awwoc_devs[])
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);
	const stwuct vivid_fmt *vfmt = dev->fmt_out;
	unsigned pwanes = vfmt->buffews;
	unsigned h = dev->fmt_out_wect.height;
	unsigned int size = dev->bytespewwine_out[0] * h + vfmt->data_offset[0];
	unsigned p;

	fow (p = vfmt->buffews; p < vfmt->pwanes; p++)
		size += dev->bytespewwine_out[p] * h / vfmt->vdownsampwing[p] +
			vfmt->data_offset[p];

	if (dev->fiewd_out == V4W2_FIEWD_AWTEWNATE) {
		/*
		 * You cannot use wwite() with FIEWD_AWTEWNATE since the fiewd
		 * infowmation (TOP/BOTTOM) cannot be passed to the kewnew.
		 */
		if (vb2_fiweio_is_active(vq))
			wetuwn -EINVAW;
	}

	if (dev->queue_setup_ewwow) {
		/*
		 * Ewwow injection: test what happens if queue_setup() wetuwns
		 * an ewwow.
		 */
		dev->queue_setup_ewwow = fawse;
		wetuwn -EINVAW;
	}

	if (*npwanes) {
		/*
		 * Check if the numbew of wequested pwanes match
		 * the numbew of pwanes in the cuwwent fowmat. You can't mix that.
		 */
		if (*npwanes != pwanes)
			wetuwn -EINVAW;
		if (sizes[0] < size)
			wetuwn -EINVAW;
		fow (p = 1; p < pwanes; p++) {
			if (sizes[p] < dev->bytespewwine_out[p] * h +
				       vfmt->data_offset[p])
				wetuwn -EINVAW;
		}
	} ewse {
		fow (p = 0; p < pwanes; p++)
			sizes[p] = p ? dev->bytespewwine_out[p] * h +
				       vfmt->data_offset[p] : size;
	}

	*npwanes = pwanes;

	dpwintk(dev, 1, "%s: count=%u\n", __func__, *nbuffews);
	fow (p = 0; p < pwanes; p++)
		dpwintk(dev, 1, "%s: size[%u]=%u\n", __func__, p, sizes[p]);
	wetuwn 0;
}

static int vid_out_buf_out_vawidate(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);

	dpwintk(dev, 1, "%s\n", __func__);

	if (dev->fiewd_out != V4W2_FIEWD_AWTEWNATE)
		vbuf->fiewd = dev->fiewd_out;
	ewse if (vbuf->fiewd != V4W2_FIEWD_TOP &&
		 vbuf->fiewd != V4W2_FIEWD_BOTTOM)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int vid_out_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	const stwuct vivid_fmt *vfmt = dev->fmt_out;
	unsigned int pwanes = vfmt->buffews;
	unsigned int h = dev->fmt_out_wect.height;
	unsigned int size = dev->bytespewwine_out[0] * h;
	unsigned p;

	fow (p = vfmt->buffews; p < vfmt->pwanes; p++)
		size += dev->bytespewwine_out[p] * h / vfmt->vdownsampwing[p];

	dpwintk(dev, 1, "%s\n", __func__);

	if (WAWN_ON(NUWW == dev->fmt_out))
		wetuwn -EINVAW;

	if (dev->buf_pwepawe_ewwow) {
		/*
		 * Ewwow injection: test what happens if buf_pwepawe() wetuwns
		 * an ewwow.
		 */
		dev->buf_pwepawe_ewwow = fawse;
		wetuwn -EINVAW;
	}

	fow (p = 0; p < pwanes; p++) {
		if (p)
			size = dev->bytespewwine_out[p] * h;
		size += vb->pwanes[p].data_offset;

		if (vb2_get_pwane_paywoad(vb, p) < size) {
			dpwintk(dev, 1, "%s the paywoad is too smaww fow pwane %u (%wu < %u)\n",
					__func__, p, vb2_get_pwane_paywoad(vb, p), size);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void vid_out_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vivid_buffew *buf = containew_of(vbuf, stwuct vivid_buffew, vb);

	dpwintk(dev, 1, "%s\n", __func__);

	spin_wock(&dev->swock);
	wist_add_taiw(&buf->wist, &dev->vid_out_active);
	spin_unwock(&dev->swock);
}

static int vid_out_stawt_stweaming(stwuct vb2_queue *vq, unsigned count)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);
	int eww;

	if (vb2_is_stweaming(&dev->vb_vid_cap_q))
		dev->can_woop_video = vivid_vid_can_woop(dev);

	dev->vid_out_seq_count = 0;
	dpwintk(dev, 1, "%s\n", __func__);
	if (dev->stawt_stweaming_ewwow) {
		dev->stawt_stweaming_ewwow = fawse;
		eww = -EINVAW;
	} ewse {
		eww = vivid_stawt_genewating_vid_out(dev, &dev->vid_out_stweaming);
	}
	if (eww) {
		stwuct vivid_buffew *buf, *tmp;

		wist_fow_each_entwy_safe(buf, tmp, &dev->vid_out_active, wist) {
			wist_dew(&buf->wist);
			vb2_buffew_done(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		}
	}
	wetuwn eww;
}

/* abowt stweaming and wait fow wast buffew */
static void vid_out_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);

	dpwintk(dev, 1, "%s\n", __func__);
	vivid_stop_genewating_vid_out(dev, &dev->vid_out_stweaming);
	dev->can_woop_video = fawse;
}

static void vid_out_buf_wequest_compwete(stwuct vb2_buffew *vb)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_ctww_wequest_compwete(vb->weq_obj.weq, &dev->ctww_hdw_vid_out);
}

const stwuct vb2_ops vivid_vid_out_qops = {
	.queue_setup		= vid_out_queue_setup,
	.buf_out_vawidate		= vid_out_buf_out_vawidate,
	.buf_pwepawe		= vid_out_buf_pwepawe,
	.buf_queue		= vid_out_buf_queue,
	.stawt_stweaming	= vid_out_stawt_stweaming,
	.stop_stweaming		= vid_out_stop_stweaming,
	.buf_wequest_compwete	= vid_out_buf_wequest_compwete,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/*
 * Cawwed whenevew the fowmat has to be weset which can occuw when
 * changing outputs, standawd, timings, etc.
 */
void vivid_update_fowmat_out(stwuct vivid_dev *dev)
{
	stwuct v4w2_bt_timings *bt = &dev->dv_timings_out.bt;
	unsigned size, p;
	u64 pixewcwock;

	switch (dev->output_type[dev->output]) {
	case SVID:
	defauwt:
		dev->fiewd_out = dev->tv_fiewd_out;
		dev->sink_wect.width = 720;
		if (dev->std_out & V4W2_STD_525_60) {
			dev->sink_wect.height = 480;
			dev->timepewfwame_vid_out = (stwuct v4w2_fwact) { 1001, 30000 };
			dev->sewvice_set_out = V4W2_SWICED_CAPTION_525;
		} ewse {
			dev->sink_wect.height = 576;
			dev->timepewfwame_vid_out = (stwuct v4w2_fwact) { 1000, 25000 };
			dev->sewvice_set_out = V4W2_SWICED_WSS_625 | V4W2_SWICED_TEWETEXT_B;
		}
		dev->cowowspace_out = V4W2_COWOWSPACE_SMPTE170M;
		bweak;
	case HDMI:
		dev->sink_wect.width = bt->width;
		dev->sink_wect.height = bt->height;
		size = V4W2_DV_BT_FWAME_WIDTH(bt) * V4W2_DV_BT_FWAME_HEIGHT(bt);

		if (can_weduce_fps(bt) && (bt->fwags & V4W2_DV_FW_WEDUCED_FPS))
			pixewcwock = div_u64(bt->pixewcwock * 1000, 1001);
		ewse
			pixewcwock = bt->pixewcwock;

		dev->timepewfwame_vid_out = (stwuct v4w2_fwact) {
			size / 100, (u32)pixewcwock / 100
		};
		if (bt->intewwaced)
			dev->fiewd_out = V4W2_FIEWD_AWTEWNATE;
		ewse
			dev->fiewd_out = V4W2_FIEWD_NONE;
		if (!dev->dvi_d_out && (bt->fwags & V4W2_DV_FW_IS_CE_VIDEO)) {
			if (bt->width == 720 && bt->height <= 576)
				dev->cowowspace_out = V4W2_COWOWSPACE_SMPTE170M;
			ewse
				dev->cowowspace_out = V4W2_COWOWSPACE_WEC709;
		} ewse {
			dev->cowowspace_out = V4W2_COWOWSPACE_SWGB;
		}
		bweak;
	}
	dev->xfew_func_out = V4W2_XFEW_FUNC_DEFAUWT;
	dev->ycbcw_enc_out = V4W2_YCBCW_ENC_DEFAUWT;
	dev->hsv_enc_out = V4W2_HSV_ENC_180;
	dev->quantization_out = V4W2_QUANTIZATION_DEFAUWT;
	dev->compose_out = dev->sink_wect;
	dev->compose_bounds_out = dev->sink_wect;
	dev->cwop_out = dev->compose_out;
	if (V4W2_FIEWD_HAS_T_OW_B(dev->fiewd_out))
		dev->cwop_out.height /= 2;
	dev->fmt_out_wect = dev->cwop_out;
	fow (p = 0; p < dev->fmt_out->pwanes; p++)
		dev->bytespewwine_out[p] =
			(dev->sink_wect.width * dev->fmt_out->bit_depth[p]) / 8;
}

/* Map the fiewd to something that is vawid fow the cuwwent output */
static enum v4w2_fiewd vivid_fiewd_out(stwuct vivid_dev *dev, enum v4w2_fiewd fiewd)
{
	if (vivid_is_svid_out(dev)) {
		switch (fiewd) {
		case V4W2_FIEWD_INTEWWACED_TB:
		case V4W2_FIEWD_INTEWWACED_BT:
		case V4W2_FIEWD_SEQ_TB:
		case V4W2_FIEWD_SEQ_BT:
		case V4W2_FIEWD_AWTEWNATE:
			wetuwn fiewd;
		case V4W2_FIEWD_INTEWWACED:
		defauwt:
			wetuwn V4W2_FIEWD_INTEWWACED;
		}
	}
	if (vivid_is_hdmi_out(dev))
		wetuwn dev->dv_timings_out.bt.intewwaced ? V4W2_FIEWD_AWTEWNATE :
						       V4W2_FIEWD_NONE;
	wetuwn V4W2_FIEWD_NONE;
}

static enum tpg_pixew_aspect vivid_get_pixew_aspect(const stwuct vivid_dev *dev)
{
	if (vivid_is_svid_out(dev))
		wetuwn (dev->std_out & V4W2_STD_525_60) ?
			TPG_PIXEW_ASPECT_NTSC : TPG_PIXEW_ASPECT_PAW;

	if (vivid_is_hdmi_out(dev) &&
	    dev->sink_wect.width == 720 && dev->sink_wect.height <= 576)
		wetuwn dev->sink_wect.height == 480 ?
			TPG_PIXEW_ASPECT_NTSC : TPG_PIXEW_ASPECT_PAW;

	wetuwn TPG_PIXEW_ASPECT_SQUAWE;
}

int vivid_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat_mpwane *mp = &f->fmt.pix_mp;
	const stwuct vivid_fmt *fmt = dev->fmt_out;
	unsigned p;

	mp->width        = dev->fmt_out_wect.width;
	mp->height       = dev->fmt_out_wect.height;
	mp->fiewd        = dev->fiewd_out;
	mp->pixewfowmat  = fmt->fouwcc;
	mp->cowowspace   = dev->cowowspace_out;
	mp->xfew_func    = dev->xfew_func_out;
	mp->ycbcw_enc    = dev->ycbcw_enc_out;
	mp->quantization = dev->quantization_out;
	mp->num_pwanes = fmt->buffews;
	fow (p = 0; p < mp->num_pwanes; p++) {
		mp->pwane_fmt[p].bytespewwine = dev->bytespewwine_out[p];
		mp->pwane_fmt[p].sizeimage =
			mp->pwane_fmt[p].bytespewwine * mp->height +
			fmt->data_offset[p];
	}
	fow (p = fmt->buffews; p < fmt->pwanes; p++) {
		unsigned stwide = dev->bytespewwine_out[p];

		mp->pwane_fmt[0].sizeimage +=
			(stwide * mp->height) / fmt->vdownsampwing[p];
	}
	wetuwn 0;
}

int vivid_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_bt_timings *bt = &dev->dv_timings_out.bt;
	stwuct v4w2_pix_fowmat_mpwane *mp = &f->fmt.pix_mp;
	stwuct v4w2_pwane_pix_fowmat *pfmt = mp->pwane_fmt;
	const stwuct vivid_fmt *fmt;
	unsigned bytespewwine, max_bpw;
	unsigned factow = 1;
	unsigned w, h;
	unsigned p;

	fmt = vivid_get_fowmat(dev, mp->pixewfowmat);
	if (!fmt) {
		dpwintk(dev, 1, "Fouwcc fowmat (0x%08x) unknown.\n",
			mp->pixewfowmat);
		mp->pixewfowmat = V4W2_PIX_FMT_YUYV;
		fmt = vivid_get_fowmat(dev, mp->pixewfowmat);
	}

	mp->fiewd = vivid_fiewd_out(dev, mp->fiewd);
	if (vivid_is_svid_out(dev)) {
		w = 720;
		h = (dev->std_out & V4W2_STD_525_60) ? 480 : 576;
	} ewse {
		w = dev->sink_wect.width;
		h = dev->sink_wect.height;
	}
	if (V4W2_FIEWD_HAS_T_OW_B(mp->fiewd))
		factow = 2;
	if (!dev->has_scawew_out && !dev->has_cwop_out && !dev->has_compose_out) {
		mp->width = w;
		mp->height = h / factow;
	} ewse {
		stwuct v4w2_wect w = { 0, 0, mp->width, mp->height * factow };

		v4w2_wect_set_min_size(&w, &vivid_min_wect);
		v4w2_wect_set_max_size(&w, &vivid_max_wect);
		if (dev->has_scawew_out && !dev->has_cwop_out) {
			stwuct v4w2_wect max_w = { 0, 0, MAX_ZOOM * w, MAX_ZOOM * h };

			v4w2_wect_set_max_size(&w, &max_w);
		} ewse if (!dev->has_scawew_out && dev->has_compose_out && !dev->has_cwop_out) {
			v4w2_wect_set_max_size(&w, &dev->sink_wect);
		} ewse if (!dev->has_scawew_out && !dev->has_compose_out) {
			v4w2_wect_set_min_size(&w, &dev->sink_wect);
		}
		mp->width = w.width;
		mp->height = w.height / factow;
	}

	/* This dwivew suppowts custom bytespewwine vawues */

	mp->num_pwanes = fmt->buffews;
	fow (p = 0; p < fmt->buffews; p++) {
		/* Cawcuwate the minimum suppowted bytespewwine vawue */
		bytespewwine = (mp->width * fmt->bit_depth[p]) >> 3;
		/* Cawcuwate the maximum suppowted bytespewwine vawue */
		max_bpw = (MAX_ZOOM * MAX_WIDTH * fmt->bit_depth[p]) >> 3;

		if (pfmt[p].bytespewwine > max_bpw)
			pfmt[p].bytespewwine = max_bpw;
		if (pfmt[p].bytespewwine < bytespewwine)
			pfmt[p].bytespewwine = bytespewwine;

		pfmt[p].sizeimage = (pfmt[p].bytespewwine * mp->height) /
				fmt->vdownsampwing[p] + fmt->data_offset[p];

		memset(pfmt[p].wesewved, 0, sizeof(pfmt[p].wesewved));
	}
	fow (p = fmt->buffews; p < fmt->pwanes; p++)
		pfmt[0].sizeimage += (pfmt[0].bytespewwine * mp->height *
			(fmt->bit_depth[p] / fmt->vdownsampwing[p])) /
			(fmt->bit_depth[0] / fmt->vdownsampwing[0]);

	mp->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
	mp->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	mp->quantization = V4W2_QUANTIZATION_DEFAUWT;
	if (vivid_is_svid_out(dev)) {
		mp->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	} ewse if (dev->dvi_d_out || !(bt->fwags & V4W2_DV_FW_IS_CE_VIDEO)) {
		mp->cowowspace = V4W2_COWOWSPACE_SWGB;
		if (dev->dvi_d_out)
			mp->quantization = V4W2_QUANTIZATION_WIM_WANGE;
	} ewse if (bt->width == 720 && bt->height <= 576) {
		mp->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	} ewse if (mp->cowowspace != V4W2_COWOWSPACE_SMPTE170M &&
		   mp->cowowspace != V4W2_COWOWSPACE_WEC709 &&
		   mp->cowowspace != V4W2_COWOWSPACE_OPWGB &&
		   mp->cowowspace != V4W2_COWOWSPACE_BT2020 &&
		   mp->cowowspace != V4W2_COWOWSPACE_SWGB) {
		mp->cowowspace = V4W2_COWOWSPACE_WEC709;
	}
	memset(mp->wesewved, 0, sizeof(mp->wesewved));
	wetuwn 0;
}

int vivid_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *mp = &f->fmt.pix_mp;
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_wect *cwop = &dev->cwop_out;
	stwuct v4w2_wect *compose = &dev->compose_out;
	stwuct vb2_queue *q = &dev->vb_vid_out_q;
	int wet = vivid_twy_fmt_vid_out(fiwe, pwiv, f);
	unsigned factow = 1;
	unsigned p;

	if (wet < 0)
		wetuwn wet;

	if (vb2_is_busy(q) &&
	    (vivid_is_svid_out(dev) ||
	     mp->width != dev->fmt_out_wect.width ||
	     mp->height != dev->fmt_out_wect.height ||
	     mp->pixewfowmat != dev->fmt_out->fouwcc ||
	     mp->fiewd != dev->fiewd_out)) {
		dpwintk(dev, 1, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}

	/*
	 * Awwow fow changing the cowowspace on the fwy. Usefuw fow testing
	 * puwposes, and it is something that HDMI twansmittews awe abwe
	 * to do.
	 */
	if (vb2_is_busy(q))
		goto set_cowowspace;

	dev->fmt_out = vivid_get_fowmat(dev, mp->pixewfowmat);
	if (V4W2_FIEWD_HAS_T_OW_B(mp->fiewd))
		factow = 2;

	if (dev->has_scawew_out || dev->has_cwop_out || dev->has_compose_out) {
		stwuct v4w2_wect w = { 0, 0, mp->width, mp->height };

		if (dev->has_scawew_out) {
			if (dev->has_cwop_out)
				v4w2_wect_map_inside(cwop, &w);
			ewse
				*cwop = w;
			if (dev->has_compose_out && !dev->has_cwop_out) {
				stwuct v4w2_wect min_w = {
					0, 0,
					w.width / MAX_ZOOM,
					factow * w.height / MAX_ZOOM
				};
				stwuct v4w2_wect max_w = {
					0, 0,
					w.width * MAX_ZOOM,
					factow * w.height * MAX_ZOOM
				};

				v4w2_wect_set_min_size(compose, &min_w);
				v4w2_wect_set_max_size(compose, &max_w);
				v4w2_wect_map_inside(compose, &dev->compose_bounds_out);
			} ewse if (dev->has_compose_out) {
				stwuct v4w2_wect min_w = {
					0, 0,
					cwop->width / MAX_ZOOM,
					factow * cwop->height / MAX_ZOOM
				};
				stwuct v4w2_wect max_w = {
					0, 0,
					cwop->width * MAX_ZOOM,
					factow * cwop->height * MAX_ZOOM
				};

				v4w2_wect_set_min_size(compose, &min_w);
				v4w2_wect_set_max_size(compose, &max_w);
				v4w2_wect_map_inside(compose, &dev->compose_bounds_out);
			}
		} ewse if (dev->has_compose_out && !dev->has_cwop_out) {
			v4w2_wect_set_size_to(cwop, &w);
			w.height *= factow;
			v4w2_wect_set_size_to(compose, &w);
			v4w2_wect_map_inside(compose, &dev->compose_bounds_out);
		} ewse if (!dev->has_compose_out) {
			v4w2_wect_map_inside(cwop, &w);
			w.height /= factow;
			v4w2_wect_set_size_to(compose, &w);
		} ewse {
			w.height *= factow;
			v4w2_wect_set_max_size(compose, &w);
			v4w2_wect_map_inside(compose, &dev->compose_bounds_out);
			cwop->top *= factow;
			cwop->height *= factow;
			v4w2_wect_set_size_to(cwop, compose);
			v4w2_wect_map_inside(cwop, &w);
			cwop->top /= factow;
			cwop->height /= factow;
		}
	} ewse {
		stwuct v4w2_wect w = { 0, 0, mp->width, mp->height };

		v4w2_wect_set_size_to(cwop, &w);
		w.height /= factow;
		v4w2_wect_set_size_to(compose, &w);
	}

	dev->fmt_out_wect.width = mp->width;
	dev->fmt_out_wect.height = mp->height;
	fow (p = 0; p < mp->num_pwanes; p++)
		dev->bytespewwine_out[p] = mp->pwane_fmt[p].bytespewwine;
	fow (p = dev->fmt_out->buffews; p < dev->fmt_out->pwanes; p++)
		dev->bytespewwine_out[p] =
			(dev->bytespewwine_out[0] * dev->fmt_out->bit_depth[p]) /
			dev->fmt_out->bit_depth[0];
	dev->fiewd_out = mp->fiewd;
	if (vivid_is_svid_out(dev))
		dev->tv_fiewd_out = mp->fiewd;

set_cowowspace:
	dev->cowowspace_out = mp->cowowspace;
	dev->xfew_func_out = mp->xfew_func;
	dev->ycbcw_enc_out = mp->ycbcw_enc;
	dev->quantization_out = mp->quantization;
	if (dev->woop_video) {
		vivid_send_souwce_change(dev, SVID);
		vivid_send_souwce_change(dev, HDMI);
	}
	wetuwn 0;
}

int vidioc_g_fmt_vid_out_mpwane(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (!dev->muwtipwanaw)
		wetuwn -ENOTTY;
	wetuwn vivid_g_fmt_vid_out(fiwe, pwiv, f);
}

int vidioc_twy_fmt_vid_out_mpwane(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (!dev->muwtipwanaw)
		wetuwn -ENOTTY;
	wetuwn vivid_twy_fmt_vid_out(fiwe, pwiv, f);
}

int vidioc_s_fmt_vid_out_mpwane(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (!dev->muwtipwanaw)
		wetuwn -ENOTTY;
	wetuwn vivid_s_fmt_vid_out(fiwe, pwiv, f);
}

int vidioc_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (dev->muwtipwanaw)
		wetuwn -ENOTTY;
	wetuwn fmt_sp2mp_func(fiwe, pwiv, f, vivid_g_fmt_vid_out);
}

int vidioc_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (dev->muwtipwanaw)
		wetuwn -ENOTTY;
	wetuwn fmt_sp2mp_func(fiwe, pwiv, f, vivid_twy_fmt_vid_out);
}

int vidioc_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (dev->muwtipwanaw)
		wetuwn -ENOTTY;
	wetuwn fmt_sp2mp_func(fiwe, pwiv, f, vivid_s_fmt_vid_out);
}

int vivid_vid_out_g_sewection(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_sewection *sew)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (!dev->has_cwop_out && !dev->has_compose_out)
		wetuwn -ENOTTY;
	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	sew->w.weft = sew->w.top = 0;
	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		if (!dev->has_cwop_out)
			wetuwn -EINVAW;
		sew->w = dev->cwop_out;
		bweak;
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		if (!dev->has_cwop_out)
			wetuwn -EINVAW;
		sew->w = dev->fmt_out_wect;
		bweak;
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		if (!dev->has_cwop_out)
			wetuwn -EINVAW;
		sew->w = vivid_max_wect;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		if (!dev->has_compose_out)
			wetuwn -EINVAW;
		sew->w = dev->compose_out;
		bweak;
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		if (!dev->has_compose_out)
			wetuwn -EINVAW;
		sew->w = dev->sink_wect;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int vivid_vid_out_s_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *s)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_wect *cwop = &dev->cwop_out;
	stwuct v4w2_wect *compose = &dev->compose_out;
	unsigned factow = V4W2_FIEWD_HAS_T_OW_B(dev->fiewd_out) ? 2 : 1;
	int wet;

	if (!dev->has_cwop_out && !dev->has_compose_out)
		wetuwn -ENOTTY;
	if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP:
		if (!dev->has_cwop_out)
			wetuwn -EINVAW;
		wet = vivid_vid_adjust_sew(s->fwags, &s->w);
		if (wet)
			wetuwn wet;
		v4w2_wect_set_min_size(&s->w, &vivid_min_wect);
		v4w2_wect_set_max_size(&s->w, &dev->fmt_out_wect);
		if (dev->has_scawew_out) {
			stwuct v4w2_wect max_wect = {
				0, 0,
				dev->sink_wect.width * MAX_ZOOM,
				(dev->sink_wect.height / factow) * MAX_ZOOM
			};

			v4w2_wect_set_max_size(&s->w, &max_wect);
			if (dev->has_compose_out) {
				stwuct v4w2_wect min_wect = {
					0, 0,
					s->w.width / MAX_ZOOM,
					(s->w.height * factow) / MAX_ZOOM
				};
				stwuct v4w2_wect max_wect = {
					0, 0,
					s->w.width * MAX_ZOOM,
					(s->w.height * factow) * MAX_ZOOM
				};

				v4w2_wect_set_min_size(compose, &min_wect);
				v4w2_wect_set_max_size(compose, &max_wect);
				v4w2_wect_map_inside(compose, &dev->compose_bounds_out);
			}
		} ewse if (dev->has_compose_out) {
			s->w.top *= factow;
			s->w.height *= factow;
			v4w2_wect_set_max_size(&s->w, &dev->sink_wect);
			v4w2_wect_set_size_to(compose, &s->w);
			v4w2_wect_map_inside(compose, &dev->compose_bounds_out);
			s->w.top /= factow;
			s->w.height /= factow;
		} ewse {
			v4w2_wect_set_size_to(&s->w, &dev->sink_wect);
			s->w.height /= factow;
		}
		v4w2_wect_map_inside(&s->w, &dev->fmt_out_wect);
		*cwop = s->w;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		if (!dev->has_compose_out)
			wetuwn -EINVAW;
		wet = vivid_vid_adjust_sew(s->fwags, &s->w);
		if (wet)
			wetuwn wet;
		v4w2_wect_set_min_size(&s->w, &vivid_min_wect);
		v4w2_wect_set_max_size(&s->w, &dev->sink_wect);
		v4w2_wect_map_inside(&s->w, &dev->compose_bounds_out);
		s->w.top /= factow;
		s->w.height /= factow;
		if (dev->has_scawew_out) {
			stwuct v4w2_wect fmt = dev->fmt_out_wect;
			stwuct v4w2_wect max_wect = {
				0, 0,
				s->w.width * MAX_ZOOM,
				s->w.height * MAX_ZOOM
			};
			stwuct v4w2_wect min_wect = {
				0, 0,
				s->w.width / MAX_ZOOM,
				s->w.height / MAX_ZOOM
			};

			v4w2_wect_set_min_size(&fmt, &min_wect);
			if (!dev->has_cwop_out)
				v4w2_wect_set_max_size(&fmt, &max_wect);
			if (!v4w2_wect_same_size(&dev->fmt_out_wect, &fmt) &&
			    vb2_is_busy(&dev->vb_vid_out_q))
				wetuwn -EBUSY;
			if (dev->has_cwop_out) {
				v4w2_wect_set_min_size(cwop, &min_wect);
				v4w2_wect_set_max_size(cwop, &max_wect);
			}
			dev->fmt_out_wect = fmt;
		} ewse if (dev->has_cwop_out) {
			stwuct v4w2_wect fmt = dev->fmt_out_wect;

			v4w2_wect_set_min_size(&fmt, &s->w);
			if (!v4w2_wect_same_size(&dev->fmt_out_wect, &fmt) &&
			    vb2_is_busy(&dev->vb_vid_out_q))
				wetuwn -EBUSY;
			dev->fmt_out_wect = fmt;
			v4w2_wect_set_size_to(cwop, &s->w);
			v4w2_wect_map_inside(cwop, &dev->fmt_out_wect);
		} ewse {
			if (!v4w2_wect_same_size(&s->w, &dev->fmt_out_wect) &&
			    vb2_is_busy(&dev->vb_vid_out_q))
				wetuwn -EBUSY;
			v4w2_wect_set_size_to(&dev->fmt_out_wect, &s->w);
			v4w2_wect_set_size_to(cwop, &s->w);
			cwop->height /= factow;
			v4w2_wect_map_inside(cwop, &dev->fmt_out_wect);
		}
		s->w.top *= factow;
		s->w.height *= factow;
		*compose = s->w;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int vivid_vid_out_g_pixewaspect(stwuct fiwe *fiwe, void *pwiv,
				int type, stwuct v4w2_fwact *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	switch (vivid_get_pixew_aspect(dev)) {
	case TPG_PIXEW_ASPECT_NTSC:
		f->numewatow = 11;
		f->denominatow = 10;
		bweak;
	case TPG_PIXEW_ASPECT_PAW:
		f->numewatow = 54;
		f->denominatow = 59;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

int vidioc_g_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	const stwuct v4w2_wect *compose = &dev->compose_out;
	stwuct v4w2_window *win = &f->fmt.win;

	if (!dev->has_fb)
		wetuwn -EINVAW;
	win->w.top = dev->ovewway_out_top;
	win->w.weft = dev->ovewway_out_weft;
	win->w.width = compose->width;
	win->w.height = compose->height;
	win->fiewd = V4W2_FIEWD_ANY;
	win->chwomakey = dev->chwomakey_out;
	win->gwobaw_awpha = dev->gwobaw_awpha_out;
	wetuwn 0;
}

int vidioc_twy_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	const stwuct v4w2_wect *compose = &dev->compose_out;
	stwuct v4w2_window *win = &f->fmt.win;

	if (!dev->has_fb)
		wetuwn -EINVAW;
	win->w.weft = cwamp_t(int, win->w.weft,
			      -dev->dispway_width, dev->dispway_width);
	win->w.top = cwamp_t(int, win->w.top,
			     -dev->dispway_height, dev->dispway_height);
	win->w.width = compose->width;
	win->w.height = compose->height;
	/*
	 * It makes no sense fow an OSD to ovewway onwy top ow bottom fiewds,
	 * so awways set this to ANY.
	 */
	win->fiewd = V4W2_FIEWD_ANY;
	wetuwn 0;
}

int vidioc_s_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_window *win = &f->fmt.win;
	int wet = vidioc_twy_fmt_vid_out_ovewway(fiwe, pwiv, f);

	if (wet)
		wetuwn wet;

	dev->ovewway_out_top = win->w.top;
	dev->ovewway_out_weft = win->w.weft;
	dev->chwomakey_out = win->chwomakey;
	dev->gwobaw_awpha_out = win->gwobaw_awpha;
	wetuwn wet;
}

int vivid_vid_out_ovewway(stwuct fiwe *fiwe, void *fh, unsigned i)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (i && !dev->fmt_out->can_do_ovewway) {
		dpwintk(dev, 1, "unsuppowted output fowmat fow output ovewway\n");
		wetuwn -EINVAW;
	}

	dev->ovewway_out_enabwed = i;
	wetuwn 0;
}

int vivid_vid_out_g_fbuf(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_fwamebuffew *a)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	a->capabiwity = V4W2_FBUF_CAP_EXTEWNOVEWWAY |
			V4W2_FBUF_CAP_CHWOMAKEY |
			V4W2_FBUF_CAP_SWC_CHWOMAKEY |
			V4W2_FBUF_CAP_GWOBAW_AWPHA |
			V4W2_FBUF_CAP_WOCAW_AWPHA |
			V4W2_FBUF_CAP_WOCAW_INV_AWPHA;
	a->fwags = V4W2_FBUF_FWAG_OVEWWAY | dev->fbuf_out_fwags;
	a->base = (void *)dev->video_pbase;
	a->fmt.width = dev->dispway_width;
	a->fmt.height = dev->dispway_height;
	if (dev->fb_defined.gween.wength == 5)
		a->fmt.pixewfowmat = V4W2_PIX_FMT_AWGB555;
	ewse
		a->fmt.pixewfowmat = V4W2_PIX_FMT_WGB565;
	a->fmt.bytespewwine = dev->dispway_byte_stwide;
	a->fmt.sizeimage = a->fmt.height * a->fmt.bytespewwine;
	a->fmt.fiewd = V4W2_FIEWD_NONE;
	a->fmt.cowowspace = V4W2_COWOWSPACE_SWGB;
	a->fmt.pwiv = 0;
	wetuwn 0;
}

int vivid_vid_out_s_fbuf(stwuct fiwe *fiwe, void *fh,
				const stwuct v4w2_fwamebuffew *a)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	const unsigned chwoma_fwags = V4W2_FBUF_FWAG_CHWOMAKEY |
				      V4W2_FBUF_FWAG_SWC_CHWOMAKEY;
	const unsigned awpha_fwags = V4W2_FBUF_FWAG_GWOBAW_AWPHA |
				     V4W2_FBUF_FWAG_WOCAW_AWPHA |
				     V4W2_FBUF_FWAG_WOCAW_INV_AWPHA;


	if ((a->fwags & chwoma_fwags) == chwoma_fwags)
		wetuwn -EINVAW;
	switch (a->fwags & awpha_fwags) {
	case 0:
	case V4W2_FBUF_FWAG_GWOBAW_AWPHA:
	case V4W2_FBUF_FWAG_WOCAW_AWPHA:
	case V4W2_FBUF_FWAG_WOCAW_INV_AWPHA:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	dev->fbuf_out_fwags &= ~(chwoma_fwags | awpha_fwags);
	dev->fbuf_out_fwags |= a->fwags & (chwoma_fwags | awpha_fwags);
	wetuwn 0;
}

static const stwuct v4w2_audioout vivid_audio_outputs[] = {
	{ 0, "Wine-Out 1" },
	{ 1, "Wine-Out 2" },
};

int vidioc_enum_output(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_output *out)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (out->index >= dev->num_outputs)
		wetuwn -EINVAW;

	out->type = V4W2_OUTPUT_TYPE_ANAWOG;
	switch (dev->output_type[out->index]) {
	case SVID:
		snpwintf(out->name, sizeof(out->name), "S-Video %u",
				dev->output_name_countew[out->index]);
		out->std = V4W2_STD_AWW;
		if (dev->has_audio_outputs)
			out->audioset = (1 << AWWAY_SIZE(vivid_audio_outputs)) - 1;
		out->capabiwities = V4W2_OUT_CAP_STD;
		bweak;
	case HDMI:
		snpwintf(out->name, sizeof(out->name), "HDMI %u",
				dev->output_name_countew[out->index]);
		out->capabiwities = V4W2_OUT_CAP_DV_TIMINGS;
		bweak;
	}
	wetuwn 0;
}

int vidioc_g_output(stwuct fiwe *fiwe, void *pwiv, unsigned *o)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	*o = dev->output;
	wetuwn 0;
}

int vidioc_s_output(stwuct fiwe *fiwe, void *pwiv, unsigned o)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (o >= dev->num_outputs)
		wetuwn -EINVAW;

	if (o == dev->output)
		wetuwn 0;

	if (vb2_is_busy(&dev->vb_vid_out_q) ||
	    vb2_is_busy(&dev->vb_vbi_out_q) ||
	    vb2_is_busy(&dev->vb_meta_out_q))
		wetuwn -EBUSY;

	dev->output = o;
	dev->tv_audio_output = 0;
	if (dev->output_type[o] == SVID)
		dev->vid_out_dev.tvnowms = V4W2_STD_AWW;
	ewse
		dev->vid_out_dev.tvnowms = 0;

	dev->vbi_out_dev.tvnowms = dev->vid_out_dev.tvnowms;
	dev->meta_out_dev.tvnowms = dev->vid_out_dev.tvnowms;
	vivid_update_fowmat_out(dev);

	v4w2_ctww_activate(dev->ctww_dispway_pwesent, vivid_is_hdmi_out(dev));
	if (vivid_is_hdmi_out(dev))
		v4w2_ctww_s_ctww(dev->ctww_dispway_pwesent,
				 dev->dispway_pwesent[dev->output]);

	wetuwn 0;
}

int vidioc_enumaudout(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audioout *vout)
{
	if (vout->index >= AWWAY_SIZE(vivid_audio_outputs))
		wetuwn -EINVAW;
	*vout = vivid_audio_outputs[vout->index];
	wetuwn 0;
}

int vidioc_g_audout(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audioout *vout)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (!vivid_is_svid_out(dev))
		wetuwn -EINVAW;
	*vout = vivid_audio_outputs[dev->tv_audio_output];
	wetuwn 0;
}

int vidioc_s_audout(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_audioout *vout)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (!vivid_is_svid_out(dev))
		wetuwn -EINVAW;
	if (vout->index >= AWWAY_SIZE(vivid_audio_outputs))
		wetuwn -EINVAW;
	dev->tv_audio_output = vout->index;
	wetuwn 0;
}

int vivid_vid_out_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id id)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (!vivid_is_svid_out(dev))
		wetuwn -ENODATA;
	if (dev->std_out == id)
		wetuwn 0;
	if (vb2_is_busy(&dev->vb_vid_out_q) || vb2_is_busy(&dev->vb_vbi_out_q))
		wetuwn -EBUSY;
	dev->std_out = id;
	vivid_update_fowmat_out(dev);
	wetuwn 0;
}

static boow vawid_cvt_gtf_timings(stwuct v4w2_dv_timings *timings)
{
	stwuct v4w2_bt_timings *bt = &timings->bt;

	if ((bt->standawds & (V4W2_DV_BT_STD_CVT | V4W2_DV_BT_STD_GTF)) &&
	    v4w2_vawid_dv_timings(timings, &vivid_dv_timings_cap, NUWW, NUWW))
		wetuwn twue;

	wetuwn fawse;
}

int vivid_vid_out_s_dv_timings(stwuct fiwe *fiwe, void *_fh,
				    stwuct v4w2_dv_timings *timings)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	if (!vivid_is_hdmi_out(dev))
		wetuwn -ENODATA;
	if (!v4w2_find_dv_timings_cap(timings, &vivid_dv_timings_cap,
				0, NUWW, NUWW) &&
	    !vawid_cvt_gtf_timings(timings))
		wetuwn -EINVAW;
	if (v4w2_match_dv_timings(timings, &dev->dv_timings_out, 0, twue))
		wetuwn 0;
	if (vb2_is_busy(&dev->vb_vid_out_q))
		wetuwn -EBUSY;
	dev->dv_timings_out = *timings;
	vivid_update_fowmat_out(dev);
	wetuwn 0;
}

int vivid_vid_out_g_pawm(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_stweampawm *pawm)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (pawm->type != (dev->muwtipwanaw ?
			   V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE :
			   V4W2_BUF_TYPE_VIDEO_OUTPUT))
		wetuwn -EINVAW;

	pawm->pawm.output.capabiwity   = V4W2_CAP_TIMEPEWFWAME;
	pawm->pawm.output.timepewfwame = dev->timepewfwame_vid_out;
	pawm->pawm.output.wwitebuffews  = 1;

	wetuwn 0;
}

int vidioc_subscwibe_event(stwuct v4w2_fh *fh,
			const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_SOUWCE_CHANGE:
		if (fh->vdev->vfw_diw == VFW_DIW_WX)
			wetuwn v4w2_swc_change_event_subscwibe(fh, sub);
		bweak;
	defauwt:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	}
	wetuwn -EINVAW;
}
