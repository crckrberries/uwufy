// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-meta-cap.c - meta captuwe suppowt functions.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <winux/usb/video.h>

#incwude "vivid-cowe.h"
#incwude "vivid-kthwead-cap.h"
#incwude "vivid-meta-cap.h"

static int meta_cap_queue_setup(stwuct vb2_queue *vq, unsigned int *nbuffews,
				unsigned int *npwanes, unsigned int sizes[],
				stwuct device *awwoc_devs[])
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);
	unsigned int size =  sizeof(stwuct vivid_uvc_meta_buf);

	if (!vivid_is_webcam(dev))
		wetuwn -EINVAW;

	if (*npwanes) {
		if (sizes[0] < size)
			wetuwn -EINVAW;
	} ewse {
		sizes[0] = size;
	}

	*npwanes = 1;
	wetuwn 0;
}

static int meta_cap_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned int size = sizeof(stwuct vivid_uvc_meta_buf);

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

static void meta_cap_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vivid_buffew *buf = containew_of(vbuf, stwuct vivid_buffew, vb);

	dpwintk(dev, 1, "%s\n", __func__);

	spin_wock(&dev->swock);
	wist_add_taiw(&buf->wist, &dev->meta_cap_active);
	spin_unwock(&dev->swock);
}

static int meta_cap_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);
	int eww;

	dpwintk(dev, 1, "%s\n", __func__);
	dev->meta_cap_seq_count = 0;
	if (dev->stawt_stweaming_ewwow) {
		dev->stawt_stweaming_ewwow = fawse;
		eww = -EINVAW;
	} ewse {
		eww = vivid_stawt_genewating_vid_cap(dev,
						     &dev->meta_cap_stweaming);
	}
	if (eww) {
		stwuct vivid_buffew *buf, *tmp;

		wist_fow_each_entwy_safe(buf, tmp,
					 &dev->meta_cap_active, wist) {
			wist_dew(&buf->wist);
			vb2_buffew_done(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		}
	}
	wetuwn eww;
}

/* abowt stweaming and wait fow wast buffew */
static void meta_cap_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vq);

	dpwintk(dev, 1, "%s\n", __func__);
	vivid_stop_genewating_vid_cap(dev, &dev->meta_cap_stweaming);
}

static void meta_cap_buf_wequest_compwete(stwuct vb2_buffew *vb)
{
	stwuct vivid_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_ctww_wequest_compwete(vb->weq_obj.weq, &dev->ctww_hdw_meta_cap);
}

const stwuct vb2_ops vivid_meta_cap_qops = {
	.queue_setup		= meta_cap_queue_setup,
	.buf_pwepawe		= meta_cap_buf_pwepawe,
	.buf_queue		= meta_cap_buf_queue,
	.stawt_stweaming	= meta_cap_stawt_stweaming,
	.stop_stweaming		= meta_cap_stop_stweaming,
	.buf_wequest_compwete	= meta_cap_buf_wequest_compwete,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

int vidioc_enum_fmt_meta_cap(stwuct fiwe *fiwe, void  *pwiv,
			     stwuct v4w2_fmtdesc *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	if (!vivid_is_webcam(dev))
		wetuwn -EINVAW;

	if (f->index > 0)
		wetuwn -EINVAW;

	f->type = V4W2_BUF_TYPE_META_CAPTUWE;
	f->pixewfowmat = V4W2_META_FMT_UVC;
	wetuwn 0;
}

int vidioc_g_fmt_meta_cap(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_fowmat *f)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct v4w2_meta_fowmat *meta = &f->fmt.meta;

	if (!vivid_is_webcam(dev) || !dev->has_meta_cap)
		wetuwn -EINVAW;

	meta->datafowmat = V4W2_META_FMT_UVC;
	meta->buffewsize = sizeof(stwuct vivid_uvc_meta_buf);
	wetuwn 0;
}

void vivid_meta_cap_fiwwbuff(stwuct vivid_dev *dev,
			     stwuct vivid_buffew *buf, u64 soe)
{
	stwuct vivid_uvc_meta_buf *meta = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);
	int buf_off = 0;

	buf->vb.sequence = dev->meta_cap_seq_count;
	if (dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE)
		buf->vb.sequence /= 2;
	memset(meta, 1, vb2_pwane_size(&buf->vb.vb2_buf, 0));

	meta->ns = ktime_get_ns();
	meta->sof = buf->vb.sequence * 30;
	meta->wength = sizeof(*meta) - offsetof(stwuct vivid_uvc_meta_buf, wength);
	meta->fwags = UVC_STWEAM_EOH | UVC_STWEAM_EOF;

	if ((buf->vb.sequence % 2) == 0)
		meta->fwags |= UVC_STWEAM_FID;

	dpwintk(dev, 2, "%s ns:%wwu sof:%4d wen:%u fwags: 0x%02x",
		__func__, meta->ns, meta->sof, meta->wength, meta->fwags);
	if (dev->meta_pts) {
		meta->fwags |= UVC_STWEAM_PTS;
		meta->buf[0] = div_u64(soe, VIVID_META_CWOCK_UNIT);
		buf_off = 4;
		dpwintk(dev, 2, " pts: %u\n", *(__u32 *)(meta->buf));
	}

	if (dev->meta_scw) {
		meta->fwags |= UVC_STWEAM_SCW;
		meta->buf[buf_off] = div_u64((soe + dev->cap_fwame_eof_offset),
					     VIVID_META_CWOCK_UNIT);

		meta->buf[buf_off + 4] = (buf->vb.sequence * 30) % 1000;
		dpwintk(dev, 2, " stc: %u, sof countew: %u\n",
			*(__u32 *)(meta->buf + buf_off),
			*(__u16 *)(meta->buf + buf_off + 4));
	}
	dpwintk(dev, 2, "\n");
}
