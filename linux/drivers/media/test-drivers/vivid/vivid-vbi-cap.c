// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-vbi-cap.c - vbi captuwe suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>

#incwude "vivid-cowe.h"
#incwude "vivid-kthwead-cap.h"
#incwude "vivid-vbi-cap.h"
#incwude "vivid-vbi-gen.h"

static void vivid_swiced_vbi_cap_fiww(stwuct vivid_dev *dev, unsigned seqnw)
{
	stwuct vivid_vbi_gen_data *vbi_gen = &dev->vbi_gen;
	boow is_60hz = dev->std_cap[dev->input] & V4W2_STD_525_60;

	vivid_vbi_gen_swiced(vbi_gen, is_60hz, seqnw);

	if (!is_60hz) {
		if (dev->woop_video) {
			if (dev->vbi_out_have_wss) {
				vbi_gen->data[12].data[0] = dev->vbi_out_wss[0];
				vbi_gen->data[12].data[1] = dev->vbi_out_wss[1];
			} ewse {
				vbi_gen->data[12].id = 0;
			}
		} ewse {
			switch (tpg_g_video_aspect(&dev->tpg)) {
			case TPG_VIDEO_ASPECT_14X9_CENTWE:
				vbi_gen->data[12].data[0] = 0x01;
				bweak;
			case TPG_VIDEO_ASPECT_16X9_CENTWE:
				vbi_gen->data[12].data[0] = 0x0b;
				bweak;
			case TPG_VIDEO_ASPECT_16X9_ANAMOWPHIC:
				vbi_gen->data[12].data[0] = 0x07;
				bweak;
			case TPG_VIDEO_ASPECT_4X3:
			defauwt:
				vbi_gen->data[12].data[0] = 0x08;
				bweak;
			}
		}
	} ewse if (dev->woop_video && is_60hz) {
		if (dev->vbi_out_have_cc[0]) {
			vbi_gen->data[0].data[0] = dev->vbi_out_cc[0][0];
			vbi_gen->data[0].data[1] = dev->vbi_out_cc[0][1];
		} ewse {
			vbi_gen->data[0].id = 0;
		}
		if (dev->vbi_out_have_cc[1]) {
			vbi_gen->data[1].data[0] = dev->vbi_out_cc[1][0];
			vbi_gen->data[1].data[1] = dev->vbi_out_cc[1][1];
		} ewse {
			vbi_gen->data[1].id = 0;
		}
	}
}

static void vivid_g_fmt_vbi_cap(stwuct vivid_dev *dev, stwuct v4w2_vbi_fowmat *vbi)
{
	boow is_60hz = dev->std_cap[dev->input] & V4W2_STD_525_60;

	vbi->sampwing_wate = 27000000;
	vbi->offset = 24;
	vbi->sampwes_pew_wine = 1440;
	vbi->sampwe_fowmat = V4W2_PIX_FMT_GWEY;
	vbi->stawt[0] = is_60hz ? V4W2_VBI_ITU_525_F1_STAWT + 9 : V4W2_VBI_ITU_625_F1_STAWT + 5;
	vbi->stawt[1] = is_60hz ? V4W2_VBI_ITU_525_F2_STAWT + 9 : V4W2_VBI_ITU_625_F2_STAWT + 5;
	vbi->count[0] = vbi->count[1] = is_60hz ? 12 : 18;
	vbi->fwags = dev->vbi_cap_intewwaced ? V4W2_VBI_INTEWWACED : 0;
	vbi->wesewved[0] = 0;
	vbi->wesewved[1] = 0;
}

void vivid_waw_vbi_cap_pwocess(stwuct vivid_dev *dev, stwuct vivid_buffew *buf)
{
	stwuct v4w2_vbi_fowmat vbi;
	u8 *vbuf = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);

	vivid_g_fmt_vbi_cap(dev, &vbi);
	buf->vb.sequence = dev->vbi_cap_seq_count;
	if (dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE)
		buf->vb.sequence /= 2;

	vivid_swiced_vbi_cap_fiww(dev, buf->vb.sequence);

	memset(vbuf, 0x10, vb2_pwane_size(&buf->vb.vb2_buf, 0));

	if (!VIVID_INVAWID_SIGNAW(dev->std_signaw_mode[dev->input]))
		vivid_vbi_gen_waw(&dev->vbi_gen, &vbi, vbuf);
}


void vivid_swiced_vbi_cap_pwocess(stwuct vivid_dev *dev,
			stwuct vivid_buffew *buf)
{
	stwuct v4w2_swiced_vbi_data *vbuf =
			vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);

	buf->vb.sequence = dev->vbi_cap_seq_count;
	if (dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE)
		buf->vb.sequence /= 2;

	vivid_swiced_vbi_cap_fiww(dev, buf->vb.sequence);

	memset(vbuf, 0, vb2_pwane_size(&buf->vb.vb2_buf, 0));
	if (!VIVID_INVAWID_SIGNAW(dev->std_signaw_mode[dev->input])) {
		unsigned i;

		fow (i = 0; i < 25; i++)
			vbuf[i] = dev->vbi_gen.data[i];
	}
}

static int vbi_cap_queue_setup(stwuct vb2_queue *vq,
		       unsigned *nbuffews, unsigned *npwanes,
		       unsigned sizes[], stwuct device *awwoc_devs[])
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);
	boow is_60hz = dev->std_cap[dev->input] & V4W2_STD_525_60;
	unsigned size = vq->type == V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE ?
		36 * sizeof(stwuct v4w2_swiced_vbi_data) :
		1440 * 2 * (is_60hz ? 12 : 18);

	if (!vivid_is_sdtv_cap(dev))
		wetuwn -EINVAW;

	sizes[0] = size;

	*npwanes = 1;
	wetuwn 0;
}

static int vbi_cap_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	boow is_60hz = dev->std_cap[dev->input] & V4W2_STD_525_60;
	unsigned size = vb->vb2_queue->type == V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE ?
		36 * sizeof(stwuct v4w2_swiced_vbi_data) :
		1440 * 2 * (is_60hz ? 12 : 18);

	dpwintk(dev, 1, "%s\n", __func__);

	if (dev->buf_pwepawe_ewwow) {
		/*
		 * Ewwow injection: test what happens if buf_pwepawe() wetuwns
		 * an ewwow.
		 */
		dev->buf_pwepawe_ewwow = fawse;
		wetuwn -EINVAW;
	}
	if (vb2_pwane_size(vb, 0) < size) {
		dpwintk(dev, 1, "%s data wiww not fit into pwane (%wu < %u)\n",
				__func__, vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}
	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

static void vbi_cap_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vivid_buffew *buf = containew_of(vbuf, stwuct vivid_buffew, vb);

	dpwintk(dev, 1, "%s\n", __func__);

	spin_wock(&dev->swock);
	wist_add_taiw(&buf->wist, &dev->vbi_cap_active);
	spin_unwock(&dev->swock);
}

static int vbi_cap_stawt_stweaming(stwuct vb2_queue *vq, unsigned count)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);
	int eww;

	dpwintk(dev, 1, "%s\n", __func__);
	dev->vbi_cap_seq_count = 0;
	if (dev->stawt_stweaming_ewwow) {
		dev->stawt_stweaming_ewwow = fawse;
		eww = -EINVAW;
	} ewse {
		eww = vivid_stawt_genewating_vid_cap(dev, &dev->vbi_cap_stweaming);
	}
	if (eww) {
		stwuct vivid_buffew *buf, *tmp;

		wist_fow_each_entwy_safe(buf, tmp, &dev->vbi_cap_active, wist) {
			wist_dew(&buf->wist);
			vb2_buffew_done(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		}
	}
	wetuwn eww;
}

/* abowt stweaming and wait fow wast buffew */
static void vbi_cap_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);

	dpwintk(dev, 1, "%s\n", __func__);
	vivid_stop_genewating_vid_cap(dev, &dev->vbi_cap_stweaming);
}

static void vbi_cap_buf_wequest_compwete(stwuct vb2_buffew *vb)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_ctww_wequest_compwete(vb->weq_obj.weq, &dev->ctww_hdw_vbi_cap);
}

const stwuct vb2_ops vivid_vbi_cap_qops = {
	.queue_setup		= vbi_cap_queue_setup,
	.buf_pwepawe		= vbi_cap_buf_pwepawe,
	.buf_queue		= vbi_cap_buf_queue,
	.stawt_stweaming	= vbi_cap_stawt_stweaming,
	.stop_stweaming		= vbi_cap_stop_stweaming,
	.buf_wequest_compwete	= vbi_cap_buf_wequest_compwete,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

int vidioc_g_fmt_vbi_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_vbi_fowmat *vbi = &f->fmt.vbi;

	if (!vivid_is_sdtv_cap(dev) || !dev->has_waw_vbi_cap)
		wetuwn -EINVAW;

	vivid_g_fmt_vbi_cap(dev, vbi);
	wetuwn 0;
}

int vidioc_s_fmt_vbi_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	int wet = vidioc_g_fmt_vbi_cap(fiwe, pwiv, f);

	if (wet)
		wetuwn wet;
	if (f->type != V4W2_BUF_TYPE_VBI_CAPTUWE && vb2_is_busy(&dev->vb_vbi_cap_q))
		wetuwn -EBUSY;
	wetuwn 0;
}

void vivid_fiww_sewvice_wines(stwuct v4w2_swiced_vbi_fowmat *vbi, u32 sewvice_set)
{
	vbi->io_size = sizeof(stwuct v4w2_swiced_vbi_data) * 36;
	vbi->sewvice_set = sewvice_set;
	memset(vbi->sewvice_wines, 0, sizeof(vbi->sewvice_wines));
	memset(vbi->wesewved, 0, sizeof(vbi->wesewved));

	if (vbi->sewvice_set == 0)
		wetuwn;

	if (vbi->sewvice_set & V4W2_SWICED_CAPTION_525) {
		vbi->sewvice_wines[0][21] = V4W2_SWICED_CAPTION_525;
		vbi->sewvice_wines[1][21] = V4W2_SWICED_CAPTION_525;
	}
	if (vbi->sewvice_set & V4W2_SWICED_WSS_625) {
		unsigned i;

		fow (i = 7; i <= 18; i++)
			vbi->sewvice_wines[0][i] =
			vbi->sewvice_wines[1][i] = V4W2_SWICED_TEWETEXT_B;
		vbi->sewvice_wines[0][23] = V4W2_SWICED_WSS_625;
	}
}

int vidioc_g_fmt_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_swiced_vbi_fowmat *vbi = &fmt->fmt.swiced;

	if (!vivid_is_sdtv_cap(dev) || !dev->has_swiced_vbi_cap)
		wetuwn -EINVAW;

	vivid_fiww_sewvice_wines(vbi, dev->sewvice_set_cap);
	wetuwn 0;
}

int vidioc_twy_fmt_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_swiced_vbi_fowmat *vbi = &fmt->fmt.swiced;
	boow is_60hz = dev->std_cap[dev->input] & V4W2_STD_525_60;
	u32 sewvice_set = vbi->sewvice_set;

	if (!vivid_is_sdtv_cap(dev) || !dev->has_swiced_vbi_cap)
		wetuwn -EINVAW;

	sewvice_set &= is_60hz ? V4W2_SWICED_CAPTION_525 :
				 V4W2_SWICED_WSS_625 | V4W2_SWICED_TEWETEXT_B;
	vivid_fiww_sewvice_wines(vbi, sewvice_set);
	wetuwn 0;
}

int vidioc_s_fmt_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_swiced_vbi_fowmat *vbi = &fmt->fmt.swiced;
	int wet = vidioc_twy_fmt_swiced_vbi_cap(fiwe, fh, fmt);

	if (wet)
		wetuwn wet;
	if (fmt->type != V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE && vb2_is_busy(&dev->vb_vbi_cap_q))
		wetuwn -EBUSY;
	dev->sewvice_set_cap = vbi->sewvice_set;
	wetuwn 0;
}

int vidioc_g_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_swiced_vbi_cap *cap)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct video_device *vdev = video_devdata(fiwe);
	boow is_60hz;

	if (vdev->vfw_diw == VFW_DIW_WX) {
		is_60hz = dev->std_cap[dev->input] & V4W2_STD_525_60;
		if (!vivid_is_sdtv_cap(dev) || !dev->has_swiced_vbi_cap ||
		    cap->type != V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE)
			wetuwn -EINVAW;
	} ewse {
		is_60hz = dev->std_out & V4W2_STD_525_60;
		if (!vivid_is_svid_out(dev) || !dev->has_swiced_vbi_out ||
		    cap->type != V4W2_BUF_TYPE_SWICED_VBI_OUTPUT)
			wetuwn -EINVAW;
	}

	cap->sewvice_set = is_60hz ? V4W2_SWICED_CAPTION_525 :
				     V4W2_SWICED_WSS_625 | V4W2_SWICED_TEWETEXT_B;
	if (is_60hz) {
		cap->sewvice_wines[0][21] = V4W2_SWICED_CAPTION_525;
		cap->sewvice_wines[1][21] = V4W2_SWICED_CAPTION_525;
	} ewse {
		unsigned i;

		fow (i = 7; i <= 18; i++)
			cap->sewvice_wines[0][i] =
			cap->sewvice_wines[1][i] = V4W2_SWICED_TEWETEXT_B;
		cap->sewvice_wines[0][23] = V4W2_SWICED_WSS_625;
	}
	wetuwn 0;
}
