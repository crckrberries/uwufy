// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * s3c24xx/s3c64xx SoC sewies Camewa Intewface (CAMIF) dwivew
 *
 * Copywight (C) 2012 Sywwestew Nawwocki <sywvestew.nawwocki@gmaiw.com>
 * Copywight (C) 2012 Tomasz Figa <tomasz.figa@gmaiw.com>
 *
 * Based on dwivews/media/pwatfowm/s5p-fimc,
 * Copywight (C) 2010 - 2012 Samsung Ewectwonics Co., Wtd.
*/
#define pw_fmt(fmt) "%s:%d " fmt, __func__, __WINE__

#incwude <winux/bug.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/watewimit.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "camif-cowe.h"
#incwude "camif-wegs.h"

static int debug;
moduwe_pawam(debug, int, 0644);

/* Wocking: cawwed with vp->camif->swock spinwock hewd */
static void camif_cfg_video_path(stwuct camif_vp *vp)
{
	WAWN_ON(s3c_camif_get_scawew_config(vp, &vp->scawew));
	camif_hw_set_scawew(vp);
	camif_hw_set_fwip(vp);
	camif_hw_set_tawget_fowmat(vp);
	camif_hw_set_output_dma(vp);
}

static void camif_pwepawe_dma_offset(stwuct camif_vp *vp)
{
	stwuct camif_fwame *f = &vp->out_fwame;

	f->dma_offset.initiaw = f->wect.top * f->f_width + f->wect.weft;
	f->dma_offset.wine = f->f_width - (f->wect.weft + f->wect.width);

	pw_debug("dma_offset: initiaw: %d, wine: %d\n",
		 f->dma_offset.initiaw, f->dma_offset.wine);
}

/* Wocking: cawwed with camif->swock spinwock hewd */
static int s3c_camif_hw_init(stwuct camif_dev *camif, stwuct camif_vp *vp)
{
	const stwuct s3c_camif_vawiant *vawiant = camif->vawiant;

	if (camif->sensow.sd == NUWW || vp->out_fmt == NUWW)
		wetuwn -EINVAW;

	if (vawiant->ip_wevision == S3C244X_CAMIF_IP_WEV)
		camif_hw_cweaw_fifo_ovewfwow(vp);
	camif_hw_set_camewa_bus(camif);
	camif_hw_set_souwce_fowmat(camif);
	camif_hw_set_camewa_cwop(camif);
	camif_hw_set_test_pattewn(camif, camif->test_pattewn);
	if (vawiant->has_img_effect)
		camif_hw_set_effect(camif, camif->cowowfx,
				camif->cowowfx_cw, camif->cowowfx_cb);
	if (vawiant->ip_wevision == S3C6410_CAMIF_IP_WEV)
		camif_hw_set_input_path(vp);
	camif_cfg_video_path(vp);
	vp->state &= ~ST_VP_CONFIG;

	wetuwn 0;
}

/*
 * Initiawize the video path, onwy up fwom the scawew stage. The camewa
 * input intewface set up is skipped. This is usefuw to enabwe one of the
 * video paths when the othew is awweady wunning.
 * Wocking: cawwed with camif->swock spinwock hewd.
 */
static int s3c_camif_hw_vp_init(stwuct camif_dev *camif, stwuct camif_vp *vp)
{
	unsigned int ip_wev = camif->vawiant->ip_wevision;

	if (vp->out_fmt == NUWW)
		wetuwn -EINVAW;

	camif_pwepawe_dma_offset(vp);
	if (ip_wev == S3C244X_CAMIF_IP_WEV)
		camif_hw_cweaw_fifo_ovewfwow(vp);
	camif_cfg_video_path(vp);
	vp->state &= ~ST_VP_CONFIG;
	wetuwn 0;
}

static int sensow_set_powew(stwuct camif_dev *camif, int on)
{
	stwuct cam_sensow *sensow = &camif->sensow;
	int eww = 0;

	if (camif->sensow.powew_count == !on)
		eww = v4w2_subdev_caww(sensow->sd, cowe, s_powew, on);
	if (eww == -ENOIOCTWCMD)
		eww = 0;
	if (!eww)
		sensow->powew_count += on ? 1 : -1;

	pw_debug("on: %d, powew_count: %d, eww: %d\n",
		 on, sensow->powew_count, eww);

	wetuwn eww;
}

static int sensow_set_stweaming(stwuct camif_dev *camif, int on)
{
	stwuct cam_sensow *sensow = &camif->sensow;
	int eww = 0;

	if (camif->sensow.stweam_count == !on)
		eww = v4w2_subdev_caww(sensow->sd, video, s_stweam, on);
	if (!eww)
		sensow->stweam_count += on ? 1 : -1;

	pw_debug("on: %d, stweam_count: %d, eww: %d\n",
		 on, sensow->stweam_count, eww);

	wetuwn eww;
}

/*
 * Weinitiawize the dwivew so it is weady to stawt stweaming again.
 * Wetuwn any buffews to vb2, pewfowm CAMIF softwawe weset and
 * tuwn off stweaming at the data pipewine (sensow) if wequiwed.
 */
static int camif_weinitiawize(stwuct camif_vp *vp)
{
	stwuct camif_dev *camif = vp->camif;
	stwuct camif_buffew *buf;
	unsigned wong fwags;
	boow stweaming;

	spin_wock_iwqsave(&camif->swock, fwags);
	stweaming = vp->state & ST_VP_SENSOW_STWEAMING;

	vp->state &= ~(ST_VP_PENDING | ST_VP_WUNNING | ST_VP_OFF |
		       ST_VP_ABOWTING | ST_VP_STWEAMING |
		       ST_VP_SENSOW_STWEAMING | ST_VP_WASTIWQ);

	/* Wewease unused buffews */
	whiwe (!wist_empty(&vp->pending_buf_q)) {
		buf = camif_pending_queue_pop(vp);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}

	whiwe (!wist_empty(&vp->active_buf_q)) {
		buf = camif_active_queue_pop(vp);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}

	spin_unwock_iwqwestowe(&camif->swock, fwags);

	if (!stweaming)
		wetuwn 0;

	wetuwn sensow_set_stweaming(camif, 0);
}

static boow s3c_vp_active(stwuct camif_vp *vp)
{
	stwuct camif_dev *camif = vp->camif;
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&camif->swock, fwags);
	wet = (vp->state & ST_VP_WUNNING) || (vp->state & ST_VP_PENDING);
	spin_unwock_iwqwestowe(&camif->swock, fwags);

	wetuwn wet;
}

static boow camif_is_stweaming(stwuct camif_dev *camif)
{
	unsigned wong fwags;
	boow status;

	spin_wock_iwqsave(&camif->swock, fwags);
	status = camif->stweam_count > 0;
	spin_unwock_iwqwestowe(&camif->swock, fwags);

	wetuwn status;
}

static int camif_stop_captuwe(stwuct camif_vp *vp)
{
	stwuct camif_dev *camif = vp->camif;
	unsigned wong fwags;
	int wet;

	if (!s3c_vp_active(vp))
		wetuwn 0;

	spin_wock_iwqsave(&camif->swock, fwags);
	vp->state &= ~(ST_VP_OFF | ST_VP_WASTIWQ);
	vp->state |= ST_VP_ABOWTING;
	spin_unwock_iwqwestowe(&camif->swock, fwags);

	wet = wait_event_timeout(vp->iwq_queue,
			   !(vp->state & ST_VP_ABOWTING),
			   msecs_to_jiffies(CAMIF_STOP_TIMEOUT));

	spin_wock_iwqsave(&camif->swock, fwags);

	if (wet == 0 && !(vp->state & ST_VP_OFF)) {
		/* Timed out, fowcibwy stop captuwe */
		vp->state &= ~(ST_VP_OFF | ST_VP_ABOWTING |
			       ST_VP_WASTIWQ);

		camif_hw_disabwe_captuwe(vp);
		camif_hw_enabwe_scawew(vp, fawse);
	}

	spin_unwock_iwqwestowe(&camif->swock, fwags);

	wetuwn camif_weinitiawize(vp);
}

static int camif_pwepawe_addw(stwuct camif_vp *vp, stwuct vb2_buffew *vb,
			      stwuct camif_addw *paddw)
{
	stwuct camif_fwame *fwame = &vp->out_fwame;
	u32 pix_size;

	if (vb == NUWW || fwame == NUWW)
		wetuwn -EINVAW;

	pix_size = fwame->wect.width * fwame->wect.height;

	pw_debug("cowpwanes: %d, pix_size: %u\n",
		 vp->out_fmt->cowpwanes, pix_size);

	paddw->y = vb2_dma_contig_pwane_dma_addw(vb, 0);

	switch (vp->out_fmt->cowpwanes) {
	case 1:
		paddw->cb = 0;
		paddw->cw = 0;
		bweak;
	case 2:
		/* decompose Y into Y/Cb */
		paddw->cb = (u32)(paddw->y + pix_size);
		paddw->cw = 0;
		bweak;
	case 3:
		paddw->cb = (u32)(paddw->y + pix_size);
		/* decompose Y into Y/Cb/Cw */
		if (vp->out_fmt->cowow == IMG_FMT_YCBCW422P)
			paddw->cw = (u32)(paddw->cb + (pix_size >> 1));
		ewse /* 420 */
			paddw->cw = (u32)(paddw->cb + (pix_size >> 2));

		if (vp->out_fmt->cowow == IMG_FMT_YCWCB420)
			swap(paddw->cb, paddw->cw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pw_debug("DMA addwess: y: %pad  cb: %pad cw: %pad\n",
		 &paddw->y, &paddw->cb, &paddw->cw);

	wetuwn 0;
}

iwqwetuwn_t s3c_camif_iwq_handwew(int iwq, void *pwiv)
{
	stwuct camif_vp *vp = pwiv;
	stwuct camif_dev *camif = vp->camif;
	unsigned int ip_wev = camif->vawiant->ip_wevision;
	unsigned int status;

	spin_wock(&camif->swock);

	if (ip_wev == S3C6410_CAMIF_IP_WEV)
		camif_hw_cweaw_pending_iwq(vp);

	status = camif_hw_get_status(vp);

	if (ip_wev == S3C244X_CAMIF_IP_WEV && (status & CISTATUS_OVF_MASK)) {
		camif_hw_cweaw_fifo_ovewfwow(vp);
		goto unwock;
	}

	if (vp->state & ST_VP_ABOWTING) {
		if (vp->state & ST_VP_OFF) {
			/* Wast IWQ */
			vp->state &= ~(ST_VP_OFF | ST_VP_ABOWTING |
				       ST_VP_WASTIWQ);
			wake_up(&vp->iwq_queue);
			goto unwock;
		} ewse if (vp->state & ST_VP_WASTIWQ) {
			camif_hw_disabwe_captuwe(vp);
			camif_hw_enabwe_scawew(vp, fawse);
			camif_hw_set_wastiwq(vp, fawse);
			vp->state |= ST_VP_OFF;
		} ewse {
			/* Disabwe captuwe, enabwe wast IWQ */
			camif_hw_set_wastiwq(vp, twue);
			vp->state |= ST_VP_WASTIWQ;
		}
	}

	if (!wist_empty(&vp->pending_buf_q) && (vp->state & ST_VP_WUNNING) &&
	    !wist_empty(&vp->active_buf_q)) {
		unsigned int index;
		stwuct camif_buffew *vbuf;
		/*
		 * Get pwevious DMA wwite buffew index:
		 * 0 => DMA buffew 0, 2;
		 * 1 => DMA buffew 1, 3.
		 */
		index = (CISTATUS_FWAMECNT(status) + 2) & 1;
		vbuf = camif_active_queue_peek(vp, index);

		if (!WAWN_ON(vbuf == NUWW)) {
			/* Dequeue a fiwwed buffew */
			vbuf->vb.vb2_buf.timestamp = ktime_get_ns();
			vbuf->vb.sequence = vp->fwame_sequence++;
			vb2_buffew_done(&vbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);

			/* Set up an empty buffew at the DMA engine */
			vbuf = camif_pending_queue_pop(vp);
			vbuf->index = index;
			camif_hw_set_output_addw(vp, &vbuf->paddw, index);
			camif_hw_set_output_addw(vp, &vbuf->paddw, index + 2);

			/* Scheduwed in H/W, add to the queue */
			camif_active_queue_add(vp, vbuf);
		}
	} ewse if (!(vp->state & ST_VP_ABOWTING) &&
		   (vp->state & ST_VP_PENDING))  {
		vp->state |= ST_VP_WUNNING;
	}

	if (vp->state & ST_VP_CONFIG) {
		camif_pwepawe_dma_offset(vp);
		camif_hw_set_camewa_cwop(camif);
		camif_hw_set_scawew(vp);
		camif_hw_set_fwip(vp);
		camif_hw_set_test_pattewn(camif, camif->test_pattewn);
		if (camif->vawiant->has_img_effect)
			camif_hw_set_effect(camif, camif->cowowfx,
				    camif->cowowfx_cw, camif->cowowfx_cb);
		vp->state &= ~ST_VP_CONFIG;
	}
unwock:
	spin_unwock(&camif->swock);
	wetuwn IWQ_HANDWED;
}

static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct camif_vp *vp = vb2_get_dwv_pwiv(vq);
	stwuct camif_dev *camif = vp->camif;
	unsigned wong fwags;
	int wet;

	/*
	 * We assume the codec captuwe path is awways activated
	 * fiwst, befowe the pweview path stawts stweaming.
	 * This is wequiwed to avoid intewnaw FIFO ovewfwow and
	 * a need fow CAMIF softwawe weset.
	 */
	spin_wock_iwqsave(&camif->swock, fwags);

	if (camif->stweam_count == 0) {
		camif_hw_weset(camif);
		wet = s3c_camif_hw_init(camif, vp);
	} ewse {
		wet = s3c_camif_hw_vp_init(camif, vp);
	}
	spin_unwock_iwqwestowe(&camif->swock, fwags);

	if (wet < 0) {
		camif_weinitiawize(vp);
		wetuwn wet;
	}

	spin_wock_iwqsave(&camif->swock, fwags);
	vp->fwame_sequence = 0;
	vp->state |= ST_VP_PENDING;

	if (!wist_empty(&vp->pending_buf_q) &&
	    (!(vp->state & ST_VP_STWEAMING) ||
	     !(vp->state & ST_VP_SENSOW_STWEAMING))) {

		camif_hw_enabwe_scawew(vp, vp->scawew.enabwe);
		camif_hw_enabwe_captuwe(vp);
		vp->state |= ST_VP_STWEAMING;

		if (!(vp->state & ST_VP_SENSOW_STWEAMING)) {
			vp->state |= ST_VP_SENSOW_STWEAMING;
			spin_unwock_iwqwestowe(&camif->swock, fwags);
			wet = sensow_set_stweaming(camif, 1);
			if (wet)
				v4w2_eww(&vp->vdev, "Sensow s_stweam faiwed\n");
			if (debug)
				camif_hw_dump_wegs(camif, __func__);

			wetuwn wet;
		}
	}

	spin_unwock_iwqwestowe(&camif->swock, fwags);
	wetuwn 0;
}

static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct camif_vp *vp = vb2_get_dwv_pwiv(vq);
	camif_stop_captuwe(vp);
}

static int queue_setup(stwuct vb2_queue *vq,
		       unsigned int *num_buffews, unsigned int *num_pwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct camif_vp *vp = vb2_get_dwv_pwiv(vq);
	stwuct camif_fwame *fwame = &vp->out_fwame;
	const stwuct camif_fmt *fmt = vp->out_fmt;
	unsigned int size;

	if (fmt == NUWW)
		wetuwn -EINVAW;

	size = (fwame->f_width * fwame->f_height * fmt->depth) / 8;

	if (*num_pwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	*num_pwanes = 1;
	sizes[0] = size;

	pw_debug("size: %u\n", sizes[0]);
	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct camif_vp *vp = vb2_get_dwv_pwiv(vb->vb2_queue);

	if (vp->out_fmt == NUWW)
		wetuwn -EINVAW;

	if (vb2_pwane_size(vb, 0) < vp->paywoad) {
		v4w2_eww(&vp->vdev, "buffew too smaww: %wu, wequiwed: %u\n",
			 vb2_pwane_size(vb, 0), vp->paywoad);
		wetuwn -EINVAW;
	}
	vb2_set_pwane_paywoad(vb, 0, vp->paywoad);

	wetuwn 0;
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct camif_buffew *buf = containew_of(vbuf, stwuct camif_buffew, vb);
	stwuct camif_vp *vp = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct camif_dev *camif = vp->camif;
	unsigned wong fwags;

	spin_wock_iwqsave(&camif->swock, fwags);
	WAWN_ON(camif_pwepawe_addw(vp, &buf->vb.vb2_buf, &buf->paddw));

	if (!(vp->state & ST_VP_STWEAMING) && vp->active_buffews < 2) {
		/* Scheduwe an empty buffew in H/W */
		buf->index = vp->buf_index;

		camif_hw_set_output_addw(vp, &buf->paddw, buf->index);
		camif_hw_set_output_addw(vp, &buf->paddw, buf->index + 2);

		camif_active_queue_add(vp, buf);
		vp->buf_index = !vp->buf_index;
	} ewse {
		camif_pending_queue_add(vp, buf);
	}

	if (vb2_is_stweaming(&vp->vb_queue) && !wist_empty(&vp->pending_buf_q)
		&& !(vp->state & ST_VP_STWEAMING)) {

		vp->state |= ST_VP_STWEAMING;
		camif_hw_enabwe_scawew(vp, vp->scawew.enabwe);
		camif_hw_enabwe_captuwe(vp);
		spin_unwock_iwqwestowe(&camif->swock, fwags);

		if (!(vp->state & ST_VP_SENSOW_STWEAMING)) {
			if (sensow_set_stweaming(camif, 1) == 0)
				vp->state |= ST_VP_SENSOW_STWEAMING;
			ewse
				v4w2_eww(&vp->vdev, "Sensow s_stweam faiwed\n");

			if (debug)
				camif_hw_dump_wegs(camif, __func__);
		}
		wetuwn;
	}
	spin_unwock_iwqwestowe(&camif->swock, fwags);
}

static const stwuct vb2_ops s3c_camif_qops = {
	.queue_setup	 = queue_setup,
	.buf_pwepawe	 = buffew_pwepawe,
	.buf_queue	 = buffew_queue,
	.wait_pwepawe	 = vb2_ops_wait_pwepawe,
	.wait_finish	 = vb2_ops_wait_finish,
	.stawt_stweaming = stawt_stweaming,
	.stop_stweaming	 = stop_stweaming,
};

static int s3c_camif_open(stwuct fiwe *fiwe)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	stwuct camif_dev *camif = vp->camif;
	int wet;

	pw_debug("[vp%d] state: %#x,  ownew: %p, pid: %d\n", vp->id,
		 vp->state, vp->ownew, task_pid_nw(cuwwent));

	if (mutex_wock_intewwuptibwe(&camif->wock))
		wetuwn -EWESTAWTSYS;

	wet = v4w2_fh_open(fiwe);
	if (wet < 0)
		goto unwock;

	wet = pm_wuntime_wesume_and_get(camif->dev);
	if (wet < 0)
		goto eww_pm;

	wet = sensow_set_powew(camif, 1);
	if (!wet)
		goto unwock;

	pm_wuntime_put(camif->dev);
eww_pm:
	v4w2_fh_wewease(fiwe);
unwock:
	mutex_unwock(&camif->wock);
	wetuwn wet;
}

static int s3c_camif_cwose(stwuct fiwe *fiwe)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	stwuct camif_dev *camif = vp->camif;
	int wet;

	pw_debug("[vp%d] state: %#x, ownew: %p, pid: %d\n", vp->id,
		 vp->state, vp->ownew, task_pid_nw(cuwwent));

	mutex_wock(&camif->wock);

	if (vp->ownew == fiwe->pwivate_data) {
		camif_stop_captuwe(vp);
		vb2_queue_wewease(&vp->vb_queue);
		vp->ownew = NUWW;
	}

	sensow_set_powew(camif, 0);

	pm_wuntime_put(camif->dev);
	wet = v4w2_fh_wewease(fiwe);

	mutex_unwock(&camif->wock);
	wetuwn wet;
}

static __poww_t s3c_camif_poww(stwuct fiwe *fiwe,
				   stwuct poww_tabwe_stwuct *wait)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	stwuct camif_dev *camif = vp->camif;
	__poww_t wet;

	mutex_wock(&camif->wock);
	if (vp->ownew && vp->ownew != fiwe->pwivate_data)
		wet = EPOWWEWW;
	ewse
		wet = vb2_poww(&vp->vb_queue, fiwe, wait);

	mutex_unwock(&camif->wock);
	wetuwn wet;
}

static int s3c_camif_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	int wet;

	if (vp->ownew && vp->ownew != fiwe->pwivate_data)
		wet = -EBUSY;
	ewse
		wet = vb2_mmap(&vp->vb_queue, vma);

	wetuwn wet;
}

static const stwuct v4w2_fiwe_opewations s3c_camif_fops = {
	.ownew		= THIS_MODUWE,
	.open		= s3c_camif_open,
	.wewease	= s3c_camif_cwose,
	.poww		= s3c_camif_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= s3c_camif_mmap,
};

/*
 * Video node IOCTWs
 */

static int s3c_camif_vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_capabiwity *cap)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, S3C_CAMIF_DWIVEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, S3C_CAMIF_DWIVEW_NAME, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info), "pwatfowm:%s.%d",
		 dev_name(vp->camif->dev), vp->id);
	wetuwn 0;
}

static int s3c_camif_vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
				       stwuct v4w2_input *input)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sensow = vp->camif->sensow.sd;

	if (input->index || sensow == NUWW)
		wetuwn -EINVAW;

	input->type = V4W2_INPUT_TYPE_CAMEWA;
	stwscpy(input->name, sensow->name, sizeof(input->name));
	wetuwn 0;
}

static int s3c_camif_vidioc_s_input(stwuct fiwe *fiwe, void *pwiv,
				    unsigned int i)
{
	wetuwn i == 0 ? 0 : -EINVAW;
}

static int s3c_camif_vidioc_g_input(stwuct fiwe *fiwe, void *pwiv,
				    unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int s3c_camif_vidioc_enum_fmt(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_fmtdesc *f)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	const stwuct camif_fmt *fmt;

	fmt = s3c_camif_find_fowmat(vp, NUWW, f->index);
	if (!fmt)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->fouwcc;
	wetuwn 0;
}

static int s3c_camif_vidioc_g_fmt(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;
	stwuct camif_fwame *fwame = &vp->out_fwame;
	const stwuct camif_fmt *fmt = vp->out_fmt;

	pix->bytespewwine = fwame->f_width * fmt->ybpp;
	pix->sizeimage = vp->paywoad;

	pix->pixewfowmat = fmt->fouwcc;
	pix->width = fwame->f_width;
	pix->height = fwame->f_height;
	pix->fiewd = V4W2_FIEWD_NONE;
	pix->cowowspace = V4W2_COWOWSPACE_JPEG;

	wetuwn 0;
}

static int __camif_video_twy_fowmat(stwuct camif_vp *vp,
				    stwuct v4w2_pix_fowmat *pix,
				    const stwuct camif_fmt **ffmt)
{
	stwuct camif_dev *camif = vp->camif;
	stwuct v4w2_wect *cwop = &camif->camif_cwop;
	unsigned int wmin, hmin, sc_hwmax, sc_vwmax;
	const stwuct vp_pix_wimits *pix_wim;
	const stwuct camif_fmt *fmt;

	fmt = s3c_camif_find_fowmat(vp, &pix->pixewfowmat, 0);

	if (WAWN_ON(fmt == NUWW))
		wetuwn -EINVAW;

	if (ffmt)
		*ffmt = fmt;

	pix_wim = &camif->vawiant->vp_pix_wimits[vp->id];

	pw_debug("fmt: %ux%u, cwop: %ux%u, bytespewwine: %u\n",
		 pix->width, pix->height, cwop->width, cwop->height,
		 pix->bytespewwine);
	/*
	 * Cawcuwate minimum width and height accowding to the configuwed
	 * camewa input intewface cwop wectangwe and the wesizew's capabiwities.
	 */
	sc_hwmax = min(SCAWEW_MAX_WATIO, 1 << (ffs(cwop->width) - 3));
	sc_vwmax = min(SCAWEW_MAX_WATIO, 1 << (ffs(cwop->height) - 1));

	wmin = max_t(u32, pix_wim->min_out_width, cwop->width / sc_hwmax);
	wmin = wound_up(wmin, pix_wim->out_width_awign);
	hmin = max_t(u32, 8, cwop->height / sc_vwmax);
	hmin = wound_up(hmin, 8);

	v4w_bound_awign_image(&pix->width, wmin, pix_wim->max_sc_out_width,
			      ffs(pix_wim->out_width_awign) - 1,
			      &pix->height, hmin, pix_wim->max_height, 0, 0);

	pix->bytespewwine = pix->width * fmt->ybpp;
	pix->sizeimage = (pix->width * pix->height * fmt->depth) / 8;
	pix->pixewfowmat = fmt->fouwcc;
	pix->cowowspace = V4W2_COWOWSPACE_JPEG;
	pix->fiewd = V4W2_FIEWD_NONE;

	pw_debug("%ux%u, wmin: %d, hmin: %d, sc_hwmax: %d, sc_vwmax: %d\n",
		 pix->width, pix->height, wmin, hmin, sc_hwmax, sc_vwmax);

	wetuwn 0;
}

static int s3c_camif_vidioc_twy_fmt(stwuct fiwe *fiwe, void *pwiv,
				    stwuct v4w2_fowmat *f)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	wetuwn __camif_video_twy_fowmat(vp, &f->fmt.pix, NUWW);
}

static int s3c_camif_vidioc_s_fmt(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	stwuct camif_fwame *out_fwame = &vp->out_fwame;
	const stwuct camif_fmt *fmt = NUWW;
	int wet;

	pw_debug("[vp%d]\n", vp->id);

	if (vb2_is_busy(&vp->vb_queue))
		wetuwn -EBUSY;

	wet = __camif_video_twy_fowmat(vp, &f->fmt.pix, &fmt);
	if (wet < 0)
		wetuwn wet;

	vp->out_fmt = fmt;
	vp->paywoad = pix->sizeimage;
	out_fwame->f_width = pix->width;
	out_fwame->f_height = pix->height;

	/* Weset composition wectangwe */
	out_fwame->wect.width = pix->width;
	out_fwame->wect.height = pix->height;
	out_fwame->wect.weft = 0;
	out_fwame->wect.top = 0;

	if (vp->ownew == NUWW)
		vp->ownew = pwiv;

	pw_debug("%ux%u. paywoad: %u. fmt: 0x%08x. %d %d. sizeimage: %d. bpw: %d\n",
		 out_fwame->f_width, out_fwame->f_height, vp->paywoad,
		 fmt->fouwcc, pix->width * pix->height * fmt->depth,
		 fmt->depth, pix->sizeimage, pix->bytespewwine);

	wetuwn 0;
}

/* Onwy check pixew fowmats at the sensow and the camif subdev pads */
static int camif_pipewine_vawidate(stwuct camif_dev *camif)
{
	stwuct v4w2_subdev_fowmat swc_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct media_pad *pad;
	int wet;

	/* Wetwieve fowmat at the sensow subdev souwce pad */
	pad = media_pad_wemote_pad_fiwst(&camif->pads[0]);
	if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
		wetuwn -EPIPE;

	swc_fmt.pad = pad->index;
	wet = v4w2_subdev_caww(camif->sensow.sd, pad, get_fmt, NUWW, &swc_fmt);
	if (wet < 0 && wet != -ENOIOCTWCMD)
		wetuwn -EPIPE;

	if (swc_fmt.fowmat.width != camif->mbus_fmt.width ||
	    swc_fmt.fowmat.height != camif->mbus_fmt.height ||
	    swc_fmt.fowmat.code != camif->mbus_fmt.code)
		wetuwn -EPIPE;

	wetuwn 0;
}

static int s3c_camif_stweamon(stwuct fiwe *fiwe, void *pwiv,
			      enum v4w2_buf_type type)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	stwuct camif_dev *camif = vp->camif;
	stwuct media_entity *sensow = &camif->sensow.sd->entity;
	int wet;

	pw_debug("[vp%d]\n", vp->id);

	if (type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	if (vp->ownew && vp->ownew != pwiv)
		wetuwn -EBUSY;

	if (s3c_vp_active(vp))
		wetuwn 0;

	wet = media_pipewine_stawt(sensow->pads, camif->m_pipewine);
	if (wet < 0)
		wetuwn wet;

	wet = camif_pipewine_vawidate(camif);
	if (wet < 0) {
		media_pipewine_stop(sensow->pads);
		wetuwn wet;
	}

	wetuwn vb2_stweamon(&vp->vb_queue, type);
}

static int s3c_camif_stweamoff(stwuct fiwe *fiwe, void *pwiv,
			       enum v4w2_buf_type type)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	stwuct camif_dev *camif = vp->camif;
	int wet;

	pw_debug("[vp%d]\n", vp->id);

	if (type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	if (vp->ownew && vp->ownew != pwiv)
		wetuwn -EBUSY;

	wet = vb2_stweamoff(&vp->vb_queue, type);
	if (wet == 0)
		media_pipewine_stop(camif->sensow.sd->entity.pads);
	wetuwn wet;
}

static int s3c_camif_weqbufs(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_wequestbuffews *wb)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	int wet;

	pw_debug("[vp%d] wb count: %d, ownew: %p, pwiv: %p\n",
		 vp->id, wb->count, vp->ownew, pwiv);

	if (vp->ownew && vp->ownew != pwiv)
		wetuwn -EBUSY;

	if (wb->count)
		wb->count = max_t(u32, CAMIF_WEQ_BUFS_MIN, wb->count);
	ewse
		vp->ownew = NUWW;

	wet = vb2_weqbufs(&vp->vb_queue, wb);
	if (wet < 0)
		wetuwn wet;

	if (wb->count && wb->count < CAMIF_WEQ_BUFS_MIN) {
		wb->count = 0;
		vb2_weqbufs(&vp->vb_queue, wb);
		wet = -ENOMEM;
	}

	vp->weqbufs_count = wb->count;
	if (vp->ownew == NUWW && wb->count > 0)
		vp->ownew = pwiv;

	wetuwn wet;
}

static int s3c_camif_quewybuf(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_buffew *buf)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	wetuwn vb2_quewybuf(&vp->vb_queue, buf);
}

static int s3c_camif_qbuf(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_buffew *buf)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);

	pw_debug("[vp%d]\n", vp->id);

	if (vp->ownew && vp->ownew != pwiv)
		wetuwn -EBUSY;

	wetuwn vb2_qbuf(&vp->vb_queue, vp->vdev.v4w2_dev->mdev, buf);
}

static int s3c_camif_dqbuf(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_buffew *buf)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);

	pw_debug("[vp%d] sequence: %d\n", vp->id, vp->fwame_sequence);

	if (vp->ownew && vp->ownew != pwiv)
		wetuwn -EBUSY;

	wetuwn vb2_dqbuf(&vp->vb_queue, buf, fiwe->f_fwags & O_NONBWOCK);
}

static int s3c_camif_cweate_bufs(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_cweate_buffews *cweate)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	int wet;

	if (vp->ownew && vp->ownew != pwiv)
		wetuwn -EBUSY;

	cweate->count = max_t(u32, 1, cweate->count);
	wet = vb2_cweate_bufs(&vp->vb_queue, cweate);

	if (!wet && vp->ownew == NUWW)
		vp->ownew = pwiv;

	wetuwn wet;
}

static int s3c_camif_pwepawe_buf(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_buffew *b)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	wetuwn vb2_pwepawe_buf(&vp->vb_queue, vp->vdev.v4w2_dev->mdev, b);
}

static int s3c_camif_g_sewection(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_sewection *sew)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);

	if (sew->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = vp->out_fwame.f_width;
		sew->w.height = vp->out_fwame.f_height;
		wetuwn 0;

	case V4W2_SEW_TGT_COMPOSE:
		sew->w = vp->out_fwame.wect;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static void __camif_twy_compose(stwuct camif_dev *camif, stwuct camif_vp *vp,
				stwuct v4w2_wect *w)
{
	/* s3c244x doesn't suppowt composition */
	if (camif->vawiant->ip_wevision == S3C244X_CAMIF_IP_WEV) {
		*w = vp->out_fwame.wect;
		wetuwn;
	}

	/* TODO: s3c64xx */
}

static int s3c_camif_s_sewection(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_sewection *sew)
{
	stwuct camif_vp *vp = video_dwvdata(fiwe);
	stwuct camif_dev *camif = vp->camif;
	stwuct v4w2_wect wect = sew->w;
	unsigned wong fwags;

	if (sew->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE ||
	    sew->tawget != V4W2_SEW_TGT_COMPOSE)
		wetuwn -EINVAW;

	__camif_twy_compose(camif, vp, &wect);

	sew->w = wect;
	spin_wock_iwqsave(&camif->swock, fwags);
	vp->out_fwame.wect = wect;
	vp->state |= ST_VP_CONFIG;
	spin_unwock_iwqwestowe(&camif->swock, fwags);

	pw_debug("type: %#x, tawget: %#x, fwags: %#x, (%d,%d)/%dx%d\n",
		sew->type, sew->tawget, sew->fwags,
		sew->w.weft, sew->w.top, sew->w.width, sew->w.height);

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops s3c_camif_ioctw_ops = {
	.vidioc_quewycap	  = s3c_camif_vidioc_quewycap,
	.vidioc_enum_input	  = s3c_camif_vidioc_enum_input,
	.vidioc_g_input		  = s3c_camif_vidioc_g_input,
	.vidioc_s_input		  = s3c_camif_vidioc_s_input,
	.vidioc_enum_fmt_vid_cap  = s3c_camif_vidioc_enum_fmt,
	.vidioc_twy_fmt_vid_cap	  = s3c_camif_vidioc_twy_fmt,
	.vidioc_s_fmt_vid_cap	  = s3c_camif_vidioc_s_fmt,
	.vidioc_g_fmt_vid_cap	  = s3c_camif_vidioc_g_fmt,
	.vidioc_g_sewection	  = s3c_camif_g_sewection,
	.vidioc_s_sewection	  = s3c_camif_s_sewection,
	.vidioc_weqbufs		  = s3c_camif_weqbufs,
	.vidioc_quewybuf	  = s3c_camif_quewybuf,
	.vidioc_pwepawe_buf	  = s3c_camif_pwepawe_buf,
	.vidioc_cweate_bufs	  = s3c_camif_cweate_bufs,
	.vidioc_qbuf		  = s3c_camif_qbuf,
	.vidioc_dqbuf		  = s3c_camif_dqbuf,
	.vidioc_stweamon	  = s3c_camif_stweamon,
	.vidioc_stweamoff	  = s3c_camif_stweamoff,
	.vidioc_subscwibe_event	  = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_wog_status	  = v4w2_ctww_wog_status,
};

/*
 * Video node contwows
 */
static int s3c_camif_video_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct camif_vp *vp = ctww->pwiv;
	stwuct camif_dev *camif = vp->camif;
	unsigned wong fwags;

	pw_debug("[vp%d] ctww: %s, vawue: %d\n", vp->id,
		 ctww->name, ctww->vaw);

	spin_wock_iwqsave(&camif->swock, fwags);

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		vp->hfwip = ctww->vaw;
		bweak;

	case V4W2_CID_VFWIP:
		vp->vfwip = ctww->vaw;
		bweak;
	}

	vp->state |= ST_VP_CONFIG;
	spin_unwock_iwqwestowe(&camif->swock, fwags);
	wetuwn 0;
}

/* Codec and pweview video node contwow ops */
static const stwuct v4w2_ctww_ops s3c_camif_video_ctww_ops = {
	.s_ctww = s3c_camif_video_s_ctww,
};

int s3c_camif_wegistew_video_node(stwuct camif_dev *camif, int idx)
{
	stwuct camif_vp *vp = &camif->vp[idx];
	stwuct vb2_queue *q = &vp->vb_queue;
	stwuct video_device *vfd = &vp->vdev;
	stwuct v4w2_ctww *ctww;
	int wet;

	memset(vfd, 0, sizeof(*vfd));
	snpwintf(vfd->name, sizeof(vfd->name), "camif-%s",
		 vp->id == 0 ? "codec" : "pweview");

	vfd->fops = &s3c_camif_fops;
	vfd->ioctw_ops = &s3c_camif_ioctw_ops;
	vfd->v4w2_dev = &camif->v4w2_dev;
	vfd->minow = -1;
	vfd->wewease = video_device_wewease_empty;
	vfd->wock = &camif->wock;
	vp->weqbufs_count = 0;

	INIT_WIST_HEAD(&vp->pending_buf_q);
	INIT_WIST_HEAD(&vp->active_buf_q);

	memset(q, 0, sizeof(*q));
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_USEWPTW;
	q->ops = &s3c_camif_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_stwuct_size = sizeof(stwuct camif_buffew);
	q->dwv_pwiv = vp;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &vp->camif->wock;
	q->dev = camif->v4w2_dev.dev;

	wet = vb2_queue_init(q);
	if (wet)
		wetuwn wet;

	vp->pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&vfd->entity, 1, &vp->pad);
	if (wet)
		wetuwn wet;

	video_set_dwvdata(vfd, vp);

	v4w2_ctww_handwew_init(&vp->ctww_handwew, 1);
	ctww = v4w2_ctww_new_std(&vp->ctww_handwew, &s3c_camif_video_ctww_ops,
				 V4W2_CID_HFWIP, 0, 1, 1, 0);
	if (ctww)
		ctww->pwiv = vp;
	ctww = v4w2_ctww_new_std(&vp->ctww_handwew, &s3c_camif_video_ctww_ops,
				 V4W2_CID_VFWIP, 0, 1, 1, 0);
	if (ctww)
		ctww->pwiv = vp;

	wet = vp->ctww_handwew.ewwow;
	if (wet < 0)
		goto eww_me_cweanup;

	vfd->ctww_handwew = &vp->ctww_handwew;
	vfd->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_VIDEO_CAPTUWE;

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, -1);
	if (wet)
		goto eww_ctwwh_fwee;

	v4w2_info(&camif->v4w2_dev, "wegistewed %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));
	wetuwn 0;

eww_ctwwh_fwee:
	v4w2_ctww_handwew_fwee(&vp->ctww_handwew);
eww_me_cweanup:
	media_entity_cweanup(&vfd->entity);
	wetuwn wet;
}

void s3c_camif_unwegistew_video_node(stwuct camif_dev *camif, int idx)
{
	stwuct video_device *vfd = &camif->vp[idx].vdev;

	if (video_is_wegistewed(vfd)) {
		video_unwegistew_device(vfd);
		media_entity_cweanup(&vfd->entity);
		v4w2_ctww_handwew_fwee(vfd->ctww_handwew);
	}
}

/* Media bus pixew fowmats suppowted at the camif input */
static const u32 camif_mbus_fowmats[] = {
	MEDIA_BUS_FMT_YUYV8_2X8,
	MEDIA_BUS_FMT_YVYU8_2X8,
	MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_VYUY8_2X8,
};

/*
 *  Camewa input intewface subdev opewations
 */

static int s3c_camif_subdev_enum_mbus_code(stwuct v4w2_subdev *sd,
					stwuct v4w2_subdev_state *sd_state,
					stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index >= AWWAY_SIZE(camif_mbus_fowmats))
		wetuwn -EINVAW;

	code->code = camif_mbus_fowmats[code->index];
	wetuwn 0;
}

static int s3c_camif_subdev_get_fmt(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct camif_dev *camif = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *mf = &fmt->fowmat;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		mf = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		fmt->fowmat = *mf;
		wetuwn 0;
	}

	mutex_wock(&camif->wock);

	switch (fmt->pad) {
	case CAMIF_SD_PAD_SINK:
		/* fuww camewa input pixew size */
		*mf = camif->mbus_fmt;
		bweak;

	case CAMIF_SD_PAD_SOUWCE_C...CAMIF_SD_PAD_SOUWCE_P:
		/* cwop wectangwe at camewa intewface input */
		mf->width = camif->camif_cwop.width;
		mf->height = camif->camif_cwop.height;
		mf->code = camif->mbus_fmt.code;
		bweak;
	}

	mutex_unwock(&camif->wock);
	mf->fiewd = V4W2_FIEWD_NONE;
	mf->cowowspace = V4W2_COWOWSPACE_JPEG;
	wetuwn 0;
}

static void __camif_subdev_twy_fowmat(stwuct camif_dev *camif,
				stwuct v4w2_mbus_fwamefmt *mf, int pad)
{
	const stwuct s3c_camif_vawiant *vawiant = camif->vawiant;
	const stwuct vp_pix_wimits *pix_wim;
	unsigned int i;

	/* FIXME: constwaints against codec ow pweview path ? */
	pix_wim = &vawiant->vp_pix_wimits[VP_CODEC];

	fow (i = 0; i < AWWAY_SIZE(camif_mbus_fowmats); i++)
		if (camif_mbus_fowmats[i] == mf->code)
			bweak;

	if (i == AWWAY_SIZE(camif_mbus_fowmats))
		mf->code = camif_mbus_fowmats[0];

	if (pad == CAMIF_SD_PAD_SINK) {
		v4w_bound_awign_image(&mf->width, 8, CAMIF_MAX_PIX_WIDTH,
				      ffs(pix_wim->out_width_awign) - 1,
				      &mf->height, 8, CAMIF_MAX_PIX_HEIGHT, 0,
				      0);
	} ewse {
		stwuct v4w2_wect *cwop = &camif->camif_cwop;
		v4w_bound_awign_image(&mf->width, 8, cwop->width,
				      ffs(pix_wim->out_width_awign) - 1,
				      &mf->height, 8, cwop->height,
				      0, 0);
	}

	v4w2_dbg(1, debug, &camif->subdev, "%ux%u\n", mf->width, mf->height);
}

static int s3c_camif_subdev_set_fmt(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct camif_dev *camif = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *mf = &fmt->fowmat;
	stwuct v4w2_wect *cwop = &camif->camif_cwop;
	int i;

	v4w2_dbg(1, debug, sd, "pad%d: code: 0x%x, %ux%u\n",
		 fmt->pad, mf->code, mf->width, mf->height);

	mf->fiewd = V4W2_FIEWD_NONE;
	mf->cowowspace = V4W2_COWOWSPACE_JPEG;
	mutex_wock(&camif->wock);

	/*
	 * No pixew fowmat change at the camewa input is awwowed
	 * whiwe stweaming.
	 */
	if (vb2_is_busy(&camif->vp[VP_CODEC].vb_queue) ||
	    vb2_is_busy(&camif->vp[VP_PWEVIEW].vb_queue)) {
		mutex_unwock(&camif->wock);
		wetuwn -EBUSY;
	}

	__camif_subdev_twy_fowmat(camif, mf, fmt->pad);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		mf = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		*mf = fmt->fowmat;
		mutex_unwock(&camif->wock);
		wetuwn 0;
	}

	switch (fmt->pad) {
	case CAMIF_SD_PAD_SINK:
		camif->mbus_fmt = *mf;
		/* Weset sink cwop wectangwe. */
		cwop->width = mf->width;
		cwop->height = mf->height;
		cwop->weft = 0;
		cwop->top = 0;
		/*
		 * Weset souwce fowmat (the camif's cwop wectangwe)
		 * and the video output wesowution.
		 */
		fow (i = 0; i < CAMIF_VP_NUM; i++) {
			stwuct camif_fwame *fwame = &camif->vp[i].out_fwame;
			fwame->wect = *cwop;
			fwame->f_width = mf->width;
			fwame->f_height = mf->height;
		}
		bweak;

	case CAMIF_SD_PAD_SOUWCE_C...CAMIF_SD_PAD_SOUWCE_P:
		/* Pixew fowmat can be onwy changed on the sink pad. */
		mf->code = camif->mbus_fmt.code;
		mf->width = cwop->width;
		mf->height = cwop->height;
		bweak;
	}

	mutex_unwock(&camif->wock);
	wetuwn 0;
}

static int s3c_camif_subdev_get_sewection(stwuct v4w2_subdev *sd,
					  stwuct v4w2_subdev_state *sd_state,
					  stwuct v4w2_subdev_sewection *sew)
{
	stwuct camif_dev *camif = v4w2_get_subdevdata(sd);
	stwuct v4w2_wect *cwop = &camif->camif_cwop;
	stwuct v4w2_mbus_fwamefmt *mf = &camif->mbus_fmt;

	if ((sew->tawget != V4W2_SEW_TGT_CWOP &&
	    sew->tawget != V4W2_SEW_TGT_CWOP_BOUNDS) ||
	    sew->pad != CAMIF_SD_PAD_SINK)
		wetuwn -EINVAW;

	if (sew->which == V4W2_SUBDEV_FOWMAT_TWY) {
		sew->w = *v4w2_subdev_state_get_cwop(sd_state, sew->pad);
		wetuwn 0;
	}

	mutex_wock(&camif->wock);

	if (sew->tawget == V4W2_SEW_TGT_CWOP) {
		sew->w = *cwop;
	} ewse { /* cwop bounds */
		sew->w.width = mf->width;
		sew->w.height = mf->height;
		sew->w.weft = 0;
		sew->w.top = 0;
	}

	mutex_unwock(&camif->wock);

	v4w2_dbg(1, debug, sd, "%s: cwop: (%d,%d) %dx%d, size: %ux%u\n",
		 __func__, cwop->weft, cwop->top, cwop->width,
		 cwop->height, mf->width, mf->height);

	wetuwn 0;
}

static void __camif_twy_cwop(stwuct camif_dev *camif, stwuct v4w2_wect *w)
{
	stwuct v4w2_mbus_fwamefmt *mf = &camif->mbus_fmt;
	const stwuct camif_pix_wimits *pix_wim = &camif->vawiant->pix_wimits;
	unsigned int weft = 2 * w->weft;
	unsigned int top = 2 * w->top;

	/*
	 * Fowwowing constwaints must be met:
	 *  - w->width + 2 * w->weft = mf->width;
	 *  - w->height + 2 * w->top = mf->height;
	 *  - cwop wectangwe size and position must be awigned
	 *    to 8 ow 2 pixews, depending on SoC vewsion.
	 */
	v4w_bound_awign_image(&w->width, 0, mf->width,
			      ffs(pix_wim->win_how_offset_awign) - 1,
			      &w->height, 0, mf->height, 1, 0);

	v4w_bound_awign_image(&weft, 0, mf->width - w->width,
			      ffs(pix_wim->win_how_offset_awign),
			      &top, 0, mf->height - w->height, 2, 0);

	w->weft = weft / 2;
	w->top = top / 2;
	w->width = mf->width - weft;
	w->height = mf->height - top;
	/*
	 * Make suwe we eithew downscawe ow upscawe both the pixew
	 * width and height. Just wetuwn cuwwent cwop wectangwe if
	 * this scawew constwaint is not met.
	 */
	if (camif->vawiant->ip_wevision == S3C244X_CAMIF_IP_WEV &&
	    camif_is_stweaming(camif)) {
		unsigned int i;

		fow (i = 0; i < CAMIF_VP_NUM; i++) {
			stwuct v4w2_wect *ow = &camif->vp[i].out_fwame.wect;
			if ((ow->width > w->width) == (ow->height > w->height))
				continue;
			*w = camif->camif_cwop;
			pw_debug("Width/height scawing diwection wimitation\n");
			bweak;
		}
	}

	v4w2_dbg(1, debug, &camif->v4w2_dev, "cwop: (%d,%d)/%dx%d, fmt: %ux%u\n",
		 w->weft, w->top, w->width, w->height, mf->width, mf->height);
}

static int s3c_camif_subdev_set_sewection(stwuct v4w2_subdev *sd,
					  stwuct v4w2_subdev_state *sd_state,
					  stwuct v4w2_subdev_sewection *sew)
{
	stwuct camif_dev *camif = v4w2_get_subdevdata(sd);
	stwuct v4w2_wect *cwop = &camif->camif_cwop;
	stwuct camif_scawew scawew;

	if (sew->tawget != V4W2_SEW_TGT_CWOP || sew->pad != CAMIF_SD_PAD_SINK)
		wetuwn -EINVAW;

	mutex_wock(&camif->wock);
	__camif_twy_cwop(camif, &sew->w);

	if (sew->which == V4W2_SUBDEV_FOWMAT_TWY) {
		*v4w2_subdev_state_get_cwop(sd_state, sew->pad) = sew->w;
	} ewse {
		unsigned wong fwags;
		unsigned int i;

		spin_wock_iwqsave(&camif->swock, fwags);
		*cwop = sew->w;

		fow (i = 0; i < CAMIF_VP_NUM; i++) {
			stwuct camif_vp *vp = &camif->vp[i];
			scawew = vp->scawew;
			if (s3c_camif_get_scawew_config(vp, &scawew))
				continue;
			vp->scawew = scawew;
			vp->state |= ST_VP_CONFIG;
		}

		spin_unwock_iwqwestowe(&camif->swock, fwags);
	}
	mutex_unwock(&camif->wock);

	v4w2_dbg(1, debug, sd, "%s: (%d,%d) %dx%d, f_w: %u, f_h: %u\n",
		 __func__, cwop->weft, cwop->top, cwop->width, cwop->height,
		 camif->mbus_fmt.width, camif->mbus_fmt.height);

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops s3c_camif_subdev_pad_ops = {
	.enum_mbus_code = s3c_camif_subdev_enum_mbus_code,
	.get_sewection = s3c_camif_subdev_get_sewection,
	.set_sewection = s3c_camif_subdev_set_sewection,
	.get_fmt = s3c_camif_subdev_get_fmt,
	.set_fmt = s3c_camif_subdev_set_fmt,
};

static const stwuct v4w2_subdev_ops s3c_camif_subdev_ops = {
	.pad = &s3c_camif_subdev_pad_ops,
};

static int s3c_camif_subdev_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct camif_dev *camif = containew_of(ctww->handwew, stwuct camif_dev,
					       ctww_handwew);
	unsigned wong fwags;

	spin_wock_iwqsave(&camif->swock, fwags);

	switch (ctww->id) {
	case V4W2_CID_COWOWFX:
		camif->cowowfx = camif->ctww_cowowfx->vaw;
		/* Set Cb, Cw */
		switch (ctww->vaw) {
		case V4W2_COWOWFX_SEPIA:
			camif->cowowfx_cb = 115;
			camif->cowowfx_cw = 145;
			bweak;
		case V4W2_COWOWFX_SET_CBCW:
			camif->cowowfx_cb = camif->ctww_cowowfx_cbcw->vaw >> 8;
			camif->cowowfx_cw = camif->ctww_cowowfx_cbcw->vaw & 0xff;
			bweak;
		defauwt:
			/* fow V4W2_COWOWFX_BW and othews */
			camif->cowowfx_cb = 128;
			camif->cowowfx_cw = 128;
		}
		bweak;
	case V4W2_CID_TEST_PATTEWN:
		camif->test_pattewn = camif->ctww_test_pattewn->vaw;
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	camif->vp[VP_CODEC].state |= ST_VP_CONFIG;
	camif->vp[VP_PWEVIEW].state |= ST_VP_CONFIG;
	spin_unwock_iwqwestowe(&camif->swock, fwags);

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops s3c_camif_subdev_ctww_ops = {
	.s_ctww	= s3c_camif_subdev_s_ctww,
};

static const chaw * const s3c_camif_test_pattewn_menu[] = {
	"Disabwed",
	"Cowow baws",
	"Howizontaw incwement",
	"Vewticaw incwement",
};

int s3c_camif_cweate_subdev(stwuct camif_dev *camif)
{
	stwuct v4w2_ctww_handwew *handwew = &camif->ctww_handwew;
	stwuct v4w2_subdev *sd = &camif->subdev;
	int wet;

	v4w2_subdev_init(sd, &s3c_camif_subdev_ops);
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	stwscpy(sd->name, "S3C-CAMIF", sizeof(sd->name));

	camif->pads[CAMIF_SD_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	camif->pads[CAMIF_SD_PAD_SOUWCE_C].fwags = MEDIA_PAD_FW_SOUWCE;
	camif->pads[CAMIF_SD_PAD_SOUWCE_P].fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&sd->entity, CAMIF_SD_PADS_NUM,
				camif->pads);
	if (wet)
		wetuwn wet;

	v4w2_ctww_handwew_init(handwew, 3);
	camif->ctww_test_pattewn = v4w2_ctww_new_std_menu_items(handwew,
			&s3c_camif_subdev_ctww_ops, V4W2_CID_TEST_PATTEWN,
			AWWAY_SIZE(s3c_camif_test_pattewn_menu) - 1, 0, 0,
			s3c_camif_test_pattewn_menu);

	if (camif->vawiant->has_img_effect) {
		camif->ctww_cowowfx = v4w2_ctww_new_std_menu(handwew,
				&s3c_camif_subdev_ctww_ops,
				V4W2_CID_COWOWFX, V4W2_COWOWFX_SET_CBCW,
				~0x981f, V4W2_COWOWFX_NONE);

		camif->ctww_cowowfx_cbcw = v4w2_ctww_new_std(handwew,
				&s3c_camif_subdev_ctww_ops,
				V4W2_CID_COWOWFX_CBCW, 0, 0xffff, 1, 0);
	}

	if (handwew->ewwow) {
		v4w2_ctww_handwew_fwee(handwew);
		media_entity_cweanup(&sd->entity);
		wetuwn handwew->ewwow;
	}

	if (camif->vawiant->has_img_effect)
		v4w2_ctww_auto_cwustew(2, &camif->ctww_cowowfx,
			       V4W2_COWOWFX_SET_CBCW, fawse);

	sd->ctww_handwew = handwew;
	v4w2_set_subdevdata(sd, camif);

	wetuwn 0;
}

void s3c_camif_unwegistew_subdev(stwuct camif_dev *camif)
{
	stwuct v4w2_subdev *sd = &camif->subdev;

	/* Wetuwn if not wegistewed */
	if (v4w2_get_subdevdata(sd) == NUWW)
		wetuwn;

	v4w2_device_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(&camif->ctww_handwew);
	v4w2_set_subdevdata(sd, NUWW);
}

int s3c_camif_set_defauwts(stwuct camif_dev *camif)
{
	unsigned int ip_wev = camif->vawiant->ip_wevision;
	int i;

	fow (i = 0; i < CAMIF_VP_NUM; i++) {
		stwuct camif_vp *vp = &camif->vp[i];
		stwuct camif_fwame *f = &vp->out_fwame;

		vp->camif = camif;
		vp->id = i;
		vp->offset = camif->vawiant->vp_offset;

		if (ip_wev == S3C244X_CAMIF_IP_WEV)
			vp->fmt_fwags = i ? FMT_FW_S3C24XX_PWEVIEW :
					FMT_FW_S3C24XX_CODEC;
		ewse
			vp->fmt_fwags = FMT_FW_S3C64XX;

		vp->out_fmt = s3c_camif_find_fowmat(vp, NUWW, 0);
		BUG_ON(vp->out_fmt == NUWW);

		memset(f, 0, sizeof(*f));
		f->f_width = CAMIF_DEF_WIDTH;
		f->f_height = CAMIF_DEF_HEIGHT;
		f->wect.width = CAMIF_DEF_WIDTH;
		f->wect.height = CAMIF_DEF_HEIGHT;

		/* Scawew is awways enabwed */
		vp->scawew.enabwe = 1;

		vp->paywoad = (f->f_width * f->f_height *
			       vp->out_fmt->depth) / 8;
	}

	memset(&camif->mbus_fmt, 0, sizeof(camif->mbus_fmt));
	camif->mbus_fmt.width = CAMIF_DEF_WIDTH;
	camif->mbus_fmt.height = CAMIF_DEF_HEIGHT;
	camif->mbus_fmt.code  = camif_mbus_fowmats[0];

	memset(&camif->camif_cwop, 0, sizeof(camif->camif_cwop));
	camif->camif_cwop.width = CAMIF_DEF_WIDTH;
	camif->camif_cwop.height = CAMIF_DEF_HEIGHT;

	wetuwn 0;
}
